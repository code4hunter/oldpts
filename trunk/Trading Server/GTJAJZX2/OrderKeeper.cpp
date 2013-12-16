//---------------------------------------------------------------------------


#pragma hdrstop

#include "OrderKeeper.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

order_keeper_manager::KEEPERMANAGERPTR order_keeper_manager::_instance(new order_keeper_manager());
boost::mutex order_keeper_manager::_map_mutex;


void order_keeper::qry_orders(TTrdItfBase *itf,TradeGateway::OrderReportSeq &ors)
{
	for( int i=0; i<ors.size(); i++ )
	{
		TRequest req;
		TradeGateway::OrderReport *iter =  &ors[i];
		req.QryCurCsn.ReqHead.FuncType = ftQryCurCsn;
		strncpy(req.QryCurCsn.OrderID, iter->base.ordId.c_str(),SEQ_LEN);

		TAnswer *ans=NULL;
		int count = 0;
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

					int trdnum = trdvol-oldtrdvol;

					iter->cumQty = trdvol;
					iter->avgPx = price;
					iter->leavesQty = ordvol-trdvol-cancle;
					assert( iter->leavesQty>=0 );

					//ODS("ordvol=%d,trdvol=%d,oldtrdvol=%d,cancle=%d,leavesQty=%d",
					//    ordvol,trdvol,oldtrdvol,cancle,iter->leavesQty);
					if( iter->leavesQty==0 )
					{
						database db;
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
							db.add_trade(&er,"",er.transactTime);
						}

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
							db.add_trade(&er,"",er.transactTime);
						}
					}
				}
				else
					ODS("查询委托返回多个记录,ordid=%s",req.QryCurCsn.OrderID) ;
				itf->FreeAnswer(ans);
			}
			else
			{
				ODS("查询委托号失败,ordid=%s",req.QryCurCsn.OrderID) ;
			}
		}
		catch(...)
		{
			ODS("查询委托号失败,意外错误,ordid=%s",req.QryCurCsn.OrderID) ;
		}
	}
}

void order_keeper::execute(const TSetAccount_Req *)
{
	ODS("->Keeper Thread Started:%s" ,_account.Account);

	TTrdItfBase *itf = new TTrdItf_GTJA( _setup_file.c_str(), _plogfunc,false);

	TRequest request;
	TAnswer *ans=NULL;
	int count = 0;

	bool bneedInit = true;
	DWORD oldtick1 = ::GetTickCount();
	DWORD oldtick2 = ::GetTickCount();
	DWORD oldtick3 = ::GetTickCount();

	try
	{
		while( _is_working )
		{
            Sleep(100);
			// 需要重连
			if( bneedInit )
			{
				// init and setaccount
				request.Init.ReqHead.FuncType = ftInit;
				if( itf->Request(request,&ans,count) != 0 )
				{
					ODS("->初始化接口失败");
					Sleep(1000);
					continue;
				}

				request.QryCurCsn.ReqHead.FuncType = ftSetAccount;
				memcpy(&request.SetAccount, &_account, sizeof(TSetAccount_Req));
				if( itf->Request(request,&ans,count) != 0 )
				{
					ODS("->登陆柜台失败");
					Sleep(1000);
					continue;
				}

				bneedInit = false;
			}
			else
			{
				//查询资金如果失败就重新连接
				if( (::GetTickCount() - oldtick1)>=10000 )
				{
					//qry money
					request.QryMoney.ReqHead.FuncType = ftQryMoney;
					if( itf->Request(request,&ans,count) != 0 )
					{
						ODS("->查询资金失败");
						bneedInit = true;
					}
					itf->FreeAnswer(ans);

					oldtick1 =  ::GetTickCount();
				}

				//每隔30秒
				else if( (::GetTickCount() - oldtick2)>=40000 )
				{
					//load working order from db
					database db;
					std::string seq ="";
					TradeGateway::OrderReportSeq ors;
					try
					{
						int ret = 0;
						ret=db.qry_working_orders(_account.Account,seq,10,
							Date().FormatString("yyyymmdd").ToInt(),ors);
					}
					catch( std::string &err)
					{
						ODS("->查工作委托失败,%s",err.c_str()) ;
						continue;
					}

					//Qry working order
					if( ors.size() < 10 )
					{
						qry_orders(itf,ors);
					}

					oldtick2 =  ::GetTickCount();
				}

				//不断取需要查撤单的委托
				//获得未成交的委托数量，如果>0则查成交
				else if( (::GetTickCount() - oldtick3)>=1000 )
				{
					// 每隔一秒钟查询成交流水
					request.QryCurTrd.ReqHead.FuncType = ftQryCurTrd;
					strcpy(request.QryCurTrd.OrderID,"-100");
					request.QryCurTrd.MaxRecord=300;
					std::string seq;
					database db;
					try
					{
						db.get_seq(Date().FormatString("yyyymmdd").ToInt(),seq,_account.Account);
					}
					catch( std::string &err)
					{
						ODS("->查最新序号失败,%s",err.c_str()) ;
						continue;
					}
					strcpy(request.QryCurTrd.SeqNum, seq.c_str());

					if( itf->Request(request,&ans,count) != 0 )
					{
						ODS("->查询成交流水失败");
                        continue;
					}

					if( count>0 && ans!= NULL )
					{
						TTradeInfo *ti;
						for(int i=0; i<count; i++ )
						{
							ti = &(ans[i].QryCurTrd.TrdInfo);

							if( ti->Vol > 0 ) //有成交
							{
								//生成成交记录
								TradeGateway::ExecutionReport er;
								er.accountId = _account.Account ;
								er.ordId = ti->ContractID;
								er.type =  TradeGateway::EtTrade;
								er.lastQty = ti->Vol;
								er.lastPx = ti->Price;
								er.tradeDate = ti->Date;
                                er.execId = ti->TrdID;
								if( ti->Time<= 0 )
									er.transactTime = Time().FormatString("hhnnss").ToInt();
								else
                                   	er.transactTime = ti->Time;
                                try
                                {
								    db.add_trade(&er,ti->SeqNum,Time().FormatString("hhnnss").ToInt());
                                }
                                catch( std::string &err)
                                {
                                    ODS("->add_trade失败,%s,%s",ti->SeqNum,err.c_str()) ;
                                }
							}
							else if( ti->Vol < 0 )  //有撤单
							{
								//生成撤单记录
								TradeGateway::ExecutionReport er;
								er.accountId = _account.Account;
								er.ordId = ti->ContractID;
								er.type =  TradeGateway::EtCanceled;
								er.lastQty = ti->Vol;
								er.lastPx = 0;
								er.tradeDate = ti->Date;
                                er.execId = ti->TrdID;
								if( ti->Time<= 0 )
									er.transactTime = Time().FormatString("hhnnss").ToInt();
								else
                                   	er.transactTime = ti->Time;
                                try
                                {
								    db.add_trade(&er,ti->SeqNum,Time().FormatString("hhnnss").ToInt());
                                }
                                catch( std::string &err)
                                {
                                    ODS("->add_trade失败,%s,%s",ti->SeqNum,err.c_str()) ;
                                }
							}
                        }

						itf->FreeAnswer(ans);
					}
					oldtick3 =  ::GetTickCount();
				}
				else
				{
					Sleep(100);
				}
			}
		}
	}
	__finally
	{
		delete itf;
        ODS("->Keeper Thread Stopped:%s",_account.Account);
        _ref_count=0;
	}
}
