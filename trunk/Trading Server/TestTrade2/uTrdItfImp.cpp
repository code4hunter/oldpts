//---------------------------------------------------------------------------
#pragma hdrstop

#include "uPriceFunc.h"
#include "uTrdItfImp.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


#pragma package(smart_init)

TTrdItfImp::TTrdItfImp(const char *psetupfile,ADDLOG plogfunc) :
	TTrdItfBase( psetupfile,  plogfunc)
{
    //db.connect("PTrdTestTrd.sqlite");
}

TTrdItfImp::~TTrdItfImp()
{
	CloseLink();
}

//初始化
int TTrdItfImp::Init()
{
    randomize();
    return 0;
}

//设置帐号
int TTrdItfImp::SetAccount()
{
    memset(&FAccInfo,0,sizeof(FAccInfo));
    FAccInfo.lt =  FRequest.SetAccount.LoginType;
    if(FRequest.SetAccount.LoginType==asSHA)
        lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,ACC_LEN);
    else if(FRequest.SetAccount.LoginType==asSZA)
        lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,ACC_LEN);
    else if(FRequest.SetAccount.LoginType==asCA)
        lstrcpyn(FAccInfo.Capital,FRequest.SetAccount.Account,ACC_LEN);

    NewAns(1);
    memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));
    order_man.load_working_orders(FRequest.SetAccount.Account);
	return 0;
}

int TTrdItfImp::QryMoney()
{
    NewAns(1);
    (*FAnswer)[0].QryMoney.MoneyInfo.MoneyType =  motRMB;
    (*FAnswer)[0].QryMoney.MoneyInfo.balance   = 10000000;
    (*FAnswer)[0].QryMoney.MoneyInfo.available = 10000000;

	return 0;
}

market_type convert_market( TradeGateway::MarketIdSource ms )
{
    market_type ret = mtNo;
    switch( ms )
    {
    case TradeGateway::SSE:
        ret = mtSHA;
        break;
    case TradeGateway::SZSE:
        ret = mtSZA;
        break;
    case TradeGateway::SHFE:
        ret = mtFSH;
        break;
    case TradeGateway::DCE:
        ret = mtFZZ;
        break;
    case TradeGateway::CZCE:
        ret = mtFDL;
        break;
    case TradeGateway::CFFEX:
        ret = mtJJS;
        break;
    case TradeGateway::HKEX:
        ret = mtHK;
        break;
    case TradeGateway::MktUnknow:
        ret = mtNo;
        break;
    }
    return ret;
}


int TTrdItfImp::QryCurCsn()
{
	if(FRequest.QryCurCsn.OrderID[0]==0)
	{
		//增量查询
		database db;
		TradeGateway::OrderReportSeq list;
		try
		{
			db.qry_orders(this->FAccInfo.Capital,FRequest.QryCurCsn.SeqNum,
				FRequest.QryCurCsn.MaxRecord,
				Date().FormatString("yyyymmdd").ToInt(),list);

			if( list.size()==0 ) return 0;
			NewAns(list.size());
			for( size_t i=0;i<list.size();i++)
			{
                TOrderInfo &poi = (*FAnswer)[i].QryCurCsn.OrderInfo;
                TradeGateway::OrderReport &or = list[i];
                strncpy(poi.Account,or.base.accountId.c_str(),ACC_LEN);
                if( or.ordStatus == TradeGateway::Canceled ||
                    or.ordStatus == TradeGateway::Filled ||
                    or.ordStatus == TradeGateway::DoneForDay ||
                    or.ordStatus == TradeGateway::Canceled ||
                    or.ordStatus == TradeGateway::Stopped ||
                    or.ordStatus == TradeGateway::Rejected)
                    poi.CancelVol = or.cumQty-or.base.ordQty;
                strncpy(poi.ContractID, or.base.ordId.c_str(),SEQ_LEN);
                poi.CsnPrice = or.base.lmtPrice;
                poi.CsnVol = or.base.ordQty;
                poi.Date = or.base.date;
                poi.Market = convert_market(or.base.inst.securityIDSource);
                strncpy(poi.SecuID,or.base.inst.securityID.c_str(),CODE_LEN);
                strncpy(poi.SeqNum,or.seq.c_str(),SEQ_LEN);
                switch( or.ordStatus )
                {
                case TradeGateway::New:
                    poi.State = oswb;
                    break;
                case TradeGateway::PendingNew:
                    poi.State = osyb;
                    break;
                case TradeGateway::Working:
                    poi.State = osbc;
                    break;
                case TradeGateway::PendingCancel:
                    poi.State = osdc;
                    break;
                case TradeGateway::Filled:
                    poi.State = oscj;
                    break;
                case TradeGateway::DoneForDay:
                    poi.State;
                    break;
                case TradeGateway::Canceled:
                    if( abs(poi.CancelVol)==poi.CsnVol )
                        poi.State = osyc;
                    else
                        poi.State = osbw;
                    break;
                case TradeGateway::Stopped:
                    poi.State =  osyf;
                    break;
                case TradeGateway::Rejected:
                    poi.State = osyf;
                    break;
                case TradeGateway::OrdStatusUnknow:
                    poi.State =osno;
                    break;
                default:
                    poi.State =osno;
                }

                poi.Time = or.base.time;
                poi.TrdPrice = or.avgPx;
                poi.TrdVol = or.cumQty;

                if( or.base.s == TradeGateway::Buy )
                {
                    if( or.base.posEfct == TradeGateway::Open )
                        poi.Type = otOpenBuy;
                    else if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otCloseBuy;
                    }
                    else if( or.base.posEfct == TradeGateway::CloseToday )
                    {
                        poi.Type =otCloseTodayBuy;
                    }
                    //else if( or.base.posEfct == TradeGateway::CloseYesterday )
                    //{
                    //	poi.Type =otCloseBuy;
                    //}
                    else
                        poi.Type = otBuy;
                }
                else if( or.base.s == TradeGateway::Sell )
                {
                    if( or.base.posEfct == TradeGateway::Open )
                        poi.Type = otOpenSell;
                    else if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otCloseSell;
                    }
                    else if( or.base.posEfct == TradeGateway::CloseToday )
                    {
                        poi.Type =otCloseTodaySell;
                    }
                    //else if( or.base.posEfct == TradeGateway::CloseYesterday )
                    //{
                    //	poi.Type =otCloseSell;
                    //}
                    else
                        poi.Type = otSell;
                }
				else if(or.base.s == TradeGateway::Subscribe)
                {
                    poi.Type = otETFSub;
                }
				else if(or.base.s == TradeGateway::Redeem)
                {
                    poi.Type = otETFRed;
                }
				else if(or.base.s == TradeGateway::Lend)
                {
                    if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otSellRepay;
                    }
                    else
                        poi.Type = otLoanBuy;
                }
                else if(or.base.s == TradeGateway::Borrow)
                {
                    if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otBuyRepay;
                    }
                    else
                        poi.Type = otLoanSell;
                }
            }
		}
		catch( std::string &err)
		{
			SetLastError(-1,'E',PLUGINNAME,err.c_str());
			return -1;
        }
	}
	else
	{
        int qry_order_by_ordid(const std::string &investorId,const std::string &id,int date,
				TradeGateway::OrderReport &ord);

        //增量查询
		database db;
		TradeGateway::OrderReport ord;
		try
		{
			int ret = db.qry_order_by_ordid(this->FAccInfo.Capital,FRequest.QryCurCsn.OrderID,
				Date().FormatString("yyyymmdd").ToInt(),ord);

			if( ret<1 ) return 0;
			NewAns(1);

            TOrderInfo &poi = (*FAnswer)[0].QryCurCsn.OrderInfo;
            TradeGateway::OrderReport &or = ord;
            strncpy(poi.Account,or.base.accountId.c_str(),ACC_LEN);
            if( or.ordStatus == TradeGateway::Canceled ||
                or.ordStatus == TradeGateway::Filled ||
                or.ordStatus == TradeGateway::DoneForDay ||
                or.ordStatus == TradeGateway::Canceled ||
                or.ordStatus == TradeGateway::Stopped ||
                or.ordStatus == TradeGateway::Rejected)
                poi.CancelVol = or.cumQty-or.base.ordQty;
            strncpy(poi.ContractID, or.base.ordId.c_str(),SEQ_LEN);
            poi.CsnPrice = or.base.lmtPrice;
            poi.CsnVol = or.base.ordQty;
            poi.Date = or.base.date;
            poi.Market = convert_market(or.base.inst.securityIDSource);
            strncpy(poi.SecuID,or.base.inst.securityID.c_str(),CODE_LEN);
            strncpy(poi.SeqNum,or.seq.c_str(),SEQ_LEN);
            switch( or.ordStatus )
            {
            case TradeGateway::New:
                poi.State = oswb;
                break;
            case TradeGateway::PendingNew:
                poi.State = osyb;
                break;
            case TradeGateway::Working:
                poi.State = osbc;
                break;
            case TradeGateway::PendingCancel:
                poi.State = osdc;
                break;
            case TradeGateway::Filled:
                poi.State = oscj;
                break;
            case TradeGateway::DoneForDay:
                poi.State;
                break;
            case TradeGateway::Canceled:
                if( abs(poi.CancelVol)==poi.CsnVol )
                    poi.State = osyc;
                else
                    poi.State = osbw;
                break;
            case TradeGateway::Stopped:
                poi.State =  osyf;
                break;
            case TradeGateway::Rejected:
                poi.State = osyf;
                break;
            case TradeGateway::OrdStatusUnknow:
                poi.State =osno;
                break;
            default:
                poi.State =osno;
            }

            poi.Time = or.base.time;
            poi.TrdPrice = or.avgPx;
            poi.TrdVol = or.cumQty;

            if( or.base.s == TradeGateway::Buy )
            {
                if( or.base.posEfct == TradeGateway::Open )
                    poi.Type = otOpenBuy;
                else if( or.base.posEfct == TradeGateway::Close )
                {
                    poi.Type =otCloseBuy;
                }
                else if( or.base.posEfct == TradeGateway::CloseToday )
                {
                    poi.Type =otCloseTodayBuy;
                }
                //else if( or.base.posEfct == TradeGateway::CloseYesterday )
                //{
                //	poi.Type =otCloseBuy;
                //}
                else
                    poi.Type = otBuy;
            }
            else if( or.base.s == TradeGateway::Sell )
            {
                if( or.base.posEfct == TradeGateway::Open )
                    poi.Type = otOpenSell;
                else if( or.base.posEfct == TradeGateway::Close )
                {
                    poi.Type =otCloseSell;
                }
                else if( or.base.posEfct == TradeGateway::CloseToday )
                {
                    poi.Type =otCloseTodaySell;
                }
                //else if( or.base.posEfct == TradeGateway::CloseYesterday )
                //{
                //	poi.Type =otCloseSell;
                //}
                else
                    poi.Type = otSell;
            }
            else if(or.base.s == TradeGateway::Subscribe)
            {
                poi.Type = otETFSub;
            }
            else if(or.base.s == TradeGateway::Redeem)
            {
                poi.Type = otETFRed;
            }
            else if(or.base.s == TradeGateway::Lend)
            {
                if( or.base.posEfct == TradeGateway::Close )
                {
                    poi.Type =otSellRepay;
                }
                else
                    poi.Type = otLoanBuy;
            }
            else if(or.base.s == TradeGateway::Borrow)
            {
                if( or.base.posEfct == TradeGateway::Close )
                {
                    poi.Type =otBuyRepay;
                }
                else
                    poi.Type = otLoanSell;
            }
		}
		catch( std::string &err)
		{
			SetLastError(-1,'E',PLUGINNAME,err.c_str());
			return -1;
        }
	}
	return 0;
}

//当日成交查询
int TTrdItfImp::QryCurTrd()
{
	database db;
	TradeGateway::ExecutionReportSeq list;
	try
	{
		if(FRequest.QryCurTrd.OrderID[0]==0)
		{
			//增量查询
			db.qry_trades(this->FAccInfo.Capital,FRequest.QryCurTrd.SeqNum,
					FRequest.QryCurTrd.MaxRecord,
					Date().FormatString("yyyymmdd").ToInt(),
					list) ;
		}
		else
		{
			db.qry_trade_by_ordid(this->FAccInfo.Capital,FRequest.QryCurTrd.OrderID,
				Date().FormatString("yyyymmdd").ToInt(),
				list);
		}

		if( list.size()==0 ) return 0;

		NewAns(list.size());
		for( size_t i=0;i<list.size();i++)
		{
		    TTradeInfo &ti = (*FAnswer)[i].QryCurTrd.TrdInfo;
            TradeGateway::ExecutionReport &er = list[i];
            strncpy(ti.Account,er.accountId.c_str(),ACC_LEN);
            strncpy(ti.ContractID,er.ordId.c_str(),SEQ_LEN);
            ti.Date=er.tradeDate;
            ti.Market=mtNo;
            ti.Price=er.lastPx;
            strncpy(ti.SecuID,"",SEQ_LEN);
            strncpy(ti.SeqNum,er.seq.c_str(),SEQ_LEN);
            ti.Time=er.transactTime;
            strncpy(ti.TrdID,er.execId.c_str(),SEQ_LEN);
            ti.Type=otNo;
            ti.Vol=abs((int)er.lastQty);
            if( er.type == TradeGateway::EtCanceled ||
                er.type == TradeGateway::EtRejected ||
                er.type == TradeGateway::Stopped )
                ti.Vol= -ti.Vol;
		}
	}
	catch( std::string &err)
	{
		SetLastError(-1,'E',PLUGINNAME,err.c_str());
		return -1;
	}
 	return 0;
}

int TTrdItfImp::QryStocks()
{
    NewAns(100);
    for( int i=0; i<100; i++ )
    {
        TStockInfo *si = &(*FAnswer)[i].QryStocks.StockInfo;
        memset(si, 0, sizeof(TStockInfo));

        strncpy(si->Account, "test", ACC_LEN);
        sprintf(si->SecuID ,"600%03d",i);
        si->Market =mtSHA ;
        si->Balance       = i+1;
        si->Available     = i+1;
        si->PosDir =      pdNet;
        si->PosNum =        i+1;
        si->CostPrice     = 1.001;
        si->CurPrice      = 1.002;
    }

	return 0;
}

int TTrdItfImp::Order()
{
	AnsiString market = this->ConvertMarketType(FRequest.Order.Market);
	AnsiString data;

	AnsiString sPrice;
	if( AnsiPos(AnsiString("510"),FRequest.Order.SecuID ) == 1 ||
		AnsiPos(AnsiString("1599"),FRequest.Order.SecuID ) == 1 )
	{
		sPrice  = ConvetDoubleToPrice( FRequest.Order.Price,3);
		//ODS("%s,%s",FRequest.Order.SecuID,sPrice.c_str());
	}
	else
	{
		sPrice  = ConvetDoubleToPrice( FRequest.Order.Price,2);
		//ODS("%s,%s",FRequest.Order.SecuID,sPrice.c_str());
	}


    try
    {
        //add to db
        TradeGateway::OrderReport op;
        op.base.accountId = this->FAccInfo.Capital;
        op.base.inst.securityID = FRequest.Order.SecuID;
        switch (FRequest.Order.Market) {
        case mtSHA : op.base.inst.securityIDSource = TradeGateway::SSE;
        break;
        case mtSZA : op.base.inst.securityIDSource =  TradeGateway::SZSE;
        break;
        case mtJJS : op.base.inst.securityIDSource =  TradeGateway::SHFE;
        break;
        case mtFSH : op.base.inst.securityIDSource =  TradeGateway::DCE;
        break;
        case mtFZZ : op.base.inst.securityIDSource = TradeGateway::CZCE ;
        break;
        case mtFDL : op.base.inst.securityIDSource =  TradeGateway::CFFEX;
        break;
        case mtHK  : op.base.inst.securityIDSource =  TradeGateway::HKEX;
        break;
        case mtNo  : op.base.inst.securityIDSource = TradeGateway::MktUnknow ;
        break;
        }

        switch( FRequest.Order.Type )
        {
        case otBuy:
            op.base.s=TradeGateway::Buy;
            break;
        case otSell  :
            op.base.s=TradeGateway::Sell;
            break;
        case otETFSub:
            op.base.s=TradeGateway::Subscribe;
            break;
        case otETFRed:
            op.base.s=TradeGateway::Redeem;
            break;
        }

        op.base.posEfct = TradeGateway::PosEftUnknow;
        op.base.type = TradeGateway::Limit;
        op.base.lmtPrice =  sPrice.ToDouble();
        op.base.ordQty =FRequest.Order.Num;
        op.base.ordId = "";
        op.base.date = Date().FormatString("yyyymmdd").ToInt();
        op.base.time = Time().FormatString("hhnnss").ToInt();
        op.ordStatus = TradeGateway::PendingNew;
        op.cumQty = 0;
        op.avgPx = 0;
        op.leavesQty =FRequest.Order.Num;

        database db;
        try
        {
            __int64 ordid = db.add_order(&op.base);
            NewAns(1);
            sprintf((*FAnswer)[0].Order.ContractID,"%d", ordid);
            op.base.ordId = (*FAnswer)[0].Order.ContractID;
            order_man.add_order(op);
        }
        catch( std::string &err)
        {
            SetLastError(-1,'E',PLUGINNAME,"加入委托到本地数据库失败:%s",err.c_str());
            return -1;
        }

    }
    catch( const int err)
    {
        return err;
    }
	return 0;
}

int TTrdItfImp::Undo()
{
	return order_man.undo_order(FRequest.Undo.ContractID);
}

market_type  TTrdItfImp::ConvertMarketType(const char *t)
{
	return mtNo;
}

order_type   TTrdItfImp::ConvertOrderType(const char *t)
{
    return otNo;
}

order_state  TTrdItfImp::ConvertOrderState(const char *t)
{
	return osno;
}

pos_direction TTrdItfImp::ConvertPosDir(const char *t)
{
	return pdNo;
}

money_type   TTrdItfImp::ConvertMoneyType(const char *t)
{
	return motRMB;
}

char *  TTrdItfImp::ConvertMarketType(market_type t)
{
	return "";
}

char *  TTrdItfImp::ConvertOrderType(order_type t)
{
    return "";
}

char *  TTrdItfImp::ConvertOrderState(order_state t)
{
	return "" ;
}

char *  TTrdItfImp::ConvertPosDir(pos_direction t)
{
	return "";
}
/*
0	人民币
1	港币
2	美元
*/
char *  TTrdItfImp::ConvertMoneyType(money_type t)
{
	return "";
}

//将配置信息读出来,如果没有获取完整的配置信息返回false
bool TTrdItfImp::GetConfig(void)
{
    if( FSetupFile== NULL ) return false;

    TMemIniFile *ini = new TMemIniFile( FSetupFile );
    try
    {
        // 判断是否存在插件的设置，没有的话返回false以便系统能够生成默认的设置
        if( ini->SectionExists(PLUGINNAME) == false ) return false;

		FZXSet.amount_per_match        = ini->ReadInteger(PLUGINNAME,"amount_per_match",FZXSet.amount_per_match);
		FZXSet.system_cancel_probability = ini->ReadInteger(PLUGINNAME,"system_cancel_probability",FZXSet.system_cancel_probability);
		FZXSet.debug_mode       = ini->ReadBool(PLUGINNAME,"debug_mode",FZXSet.debug_mode);
    }
	__finally
    {
        delete ini;
    }
	return true;
}

//将配置信息回写到配置文件
void TTrdItfImp::SetConfig(void)
{
	if( FSetupFile== NULL ) return ;

    TMemIniFile *ini = new TMemIniFile( FSetupFile );
    try
    {
		ini->WriteInteger(PLUGINNAME,"amount_per_match",            FZXSet.amount_per_match);
        ini->WriteInteger(PLUGINNAME,"system_cancel_probability",          FZXSet.system_cancel_probability);
		ini->WriteBool   (PLUGINNAME,"debug_mode",       FZXSet.debug_mode);

        ini->UpdateFile();
    }
    __finally
    {
        delete ini;
	}
}

//关闭中间件链接
void TTrdItfImp::CloseLink(void)
{
	order_man.clear_all();
}

int TTrdItfImp::KeepAlive(void)
{
	order_man.qry_orders(this);
	return 0;
}

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

void order_manager::qry_orders(TTrdItfImp *itf)
{
	//P[插件 2010/11/2 21:29:42] 撮合其他错误,Access violation at address 01E051D8 in module 'PTrdTestTrd2.DLL'. Read of address 00000238

	ORDER_ITERATOR iter;
	_mutex.lock();
	try
	{
    try
    {
		database db;
		int count = 10;
        for( iter=FOrders.begin(); iter!=FOrders.end(); ++iter)
		{
			count--;
			if( count <=0 ) break;
            int trdnum=0 ;
            int cancle=0 ;

            if( iter->ordStatus == TradeGateway::PendingCancel )
            {
                if( iter->leavesQty>0 )
                {
                    int rd = rand()/100+1;
                    if( rd >=50 )
                        trdnum = iter->leavesQty;
                    else
                        cancle = iter->leavesQty;
                }
            }
            else if( iter->ordStatus == TradeGateway::New ||
                     iter->ordStatus == TradeGateway::PendingNew)
            {
                int rd = rand()/100+1;
                if( rd <=itf->FZXSet.system_cancel_probability )
                    cancle = iter->leavesQty;
                else
                {
                    int v = iter->base.ordQty*itf->FZXSet.amount_per_match/100;
                    trdnum = v>iter->leavesQty? iter->leavesQty:v;
                }
            }
            else if( iter->ordStatus == TradeGateway::Working )
            {
                int v = iter->base.ordQty*itf->FZXSet.amount_per_match/100;
                trdnum = v>iter->leavesQty? iter->leavesQty:v;
            }

            if( trdnum > 0 ) //有成交
            {
                double lastprice =iter->base.lmtPrice;

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

            iter->cumQty += trdnum;
            iter->avgPx = iter->base.lmtPrice;
            iter->leavesQty = iter->base.ordQty-iter->cumQty-cancle;
            assert( iter->leavesQty>=0 );

            if( cancle >0 )
            {
                //assert(trdvol+cancle==ordvol) ;
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
            }
            else
                FOrders.erase(iter);
        }
    }
    __finally
	{
	    _mutex.unlock();
	}
	}
	catch( std::string &err)
	{
		ODS("更新到数据库失败,%s",err.c_str()) ;
	}
	catch( Exception &e )
	{
		ODS("撮合其他错误,%s",AnsiString(e.Message).c_str());
    }
}
