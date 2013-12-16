#include "OrderManage.h"
#include "uDatabase.h"
#include <DateUtils.hpp>

std::map<std::string,int> order_manager::userid_list;
boost::mutex order_manager::_map_mutex;

void order_manager::load_working_orders(const std::string &userid)
{
	clear_all();

	if( add_user(userid) )
	{
		database db;
		std::string seq ="";
		TradeGateway::OrderReportSeq ors;
		try
		{
			int ret = 0;
			do
			{
				ret=db.qry_working_orders(userid,seq,100,
					Date().FormatString("yyyymmdd").ToInt(),ors);
			}
			while(ret==100);
		}
		catch( std::string &err)
		{
			ODS("查工作委托失败,%s",err.c_str()) ;
		}
		boost::mutex::scoped_lock lock(_mutex);
		for(size_t i=0;i<ors.size();i++)
		{
			FOrders.push_back(ors[i]);
		}
		_userid = userid;
	}
}

void order_manager::qry_orders(TTrdItfBase *itf)
{
	ORDERS work;
	ORDER_ITERATOR iter;

	_mutex.lock();
	for( iter=FOrders.begin(); iter!=FOrders.end(); iter++)
	{
		work.push_back(*iter) ;
	}
	FOrders.clear();
	_mutex.unlock();

	for( iter=work.begin(); iter!=work.end(); iter++)
	{
		//iter->base.ordId
		TRequest req;
		req.QryCurCsn.ReqHead.FuncType = ftQryCurCsn;
		strncpy(req.QryCurCsn.OrderID, iter->base.ordId.c_str(),SEQ_LEN);

		TAnswer *ans=NULL;
		int count = 0;
        itf->lock();
        try
        {
            if( itf->Request(req,&ans,count) == 0 )
            {
                if(  count == 1 )
                {
                    int trdvol = ans[0].QryCurCsn.OrderInfo.TrdVol;
                    double price = ans[0].QryCurCsn.OrderInfo.TrdPrice;
                    if( price <0.0001f && trdvol>0 )
                    {
                        price =  ans[0].QryCurCsn.OrderInfo.CsnPrice;
                    }
                    int ordvol = ans[0].QryCurCsn.OrderInfo.CsnVol;
                    int cancle = abs(ans[0].QryCurCsn.OrderInfo.CancelVol);
                    order_state os = ans[0].QryCurCsn.OrderInfo.State;
                    if( os==osyf )
                        cancle = ordvol-trdvol;

                    int oldtrdvol = iter->cumQty;
                    double oldprice  = iter->avgPx;
                    int oldordvol = iter->base.ordQty;
                    int oldleavesqty = iter->leavesQty;

                    assert(  oldordvol ==   ordvol);
                    assert(  oldtrdvol<=trdvol );

                    database db;

                    int trdnum = trdvol-oldtrdvol;
                    if( trdnum > 0 ) //有成交
                    {
                        double lastprice =(trdvol*price-oldtrdvol*oldprice)/trdnum;

                        //生成成交记录
                        TradeGateway::ExecutionReport er;
                        er.accountId = iter->base.accountId;
                        er.ordId = iter->base.ordId;
                        er.type =  TradeGateway::EtTrade;
                        er.lastQty = trdnum;
                        er.lastPx = lastprice;
                        er.tradeDate = iter->base.date;
                        er.transactTime = Time().FormatString("hhnnss").ToInt();
                        db.add_trade(&er);
                    }

                    iter->cumQty = trdvol;
                    iter->avgPx = price;
                    iter->leavesQty = ordvol-trdvol-cancle;
                    assert( iter->leavesQty>=0 );

                    if( cancle >0 )
                    {
                        assert(trdvol+cancle==ordvol) ;
                        //生成撤单记录
                        TradeGateway::ExecutionReport er;
                        er.accountId = iter->base.accountId;
                        er.ordId = iter->base.ordId;
                        er.type =  TradeGateway::EtCanceled;
                        er.lastQty = -cancle;
                        er.lastPx = 0;
                        er.tradeDate = iter->base.date;
                        er.transactTime = Time().FormatString("hhnnss").ToInt();
                        db.add_trade(&er);
                    }

                    //ODS("ordvol=%d,trdvol=%d,oldtrdvol=%d,cancle=%d,leavesQty=%d",
                    //    ordvol,trdvol,oldtrdvol,cancle,iter->leavesQty);
                    if( iter->leavesQty>0 )
                    {
                        iter->ordStatus = TradeGateway::Working;
                        this->add_order(*iter);
                    }
                }
                else
                    ODS("查询委托返回多个记录,ordid=%s",req.QryCurCsn.OrderID) ;
                itf->FreeAnswer(ans);
            }
            else
            {
                ODS("查询委托号失败,ordid=%s",req.QryCurCsn.OrderID) ;
                iter->ordStatus = TradeGateway::Working;
                this->add_order(*iter);
            }
        }
        catch(...)
        {
            ODS("查询委托号失败,意外错误,ordid=%s",req.QryCurCsn.OrderID) ;
            iter->ordStatus = TradeGateway::Working;
            this->add_order(*iter);
        }
        itf->unlock();
	}
}
