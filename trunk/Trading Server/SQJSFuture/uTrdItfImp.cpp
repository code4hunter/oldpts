//---------------------------------------------------------------------------


#pragma hdrstop

#include "uTrdItfImp.h"
#include "uDatabase.h"

#include <classes.hpp>
#include <IniFiles.hpp>
#include <stdio.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

TTrdItfImp::TTrdItfImp(const char *psetupfile,ADDLOG plogfunc)
    :TTrdItfBase(psetupfile,plogfunc)
{

}

TTrdItfImp::~TTrdItfImp()
{

}

//初始化
int TTrdItfImp::Init()
{
    return 0;
}

//设置帐号
int TTrdItfImp::SetAccount()
{
    FSession = gSessionMan.get_session_by_name(FRequest.SetAccount.Account,
        FRequest.SetAccount.PW);

    if( FSession->isWorking() == false )
    {
        FSession->start_worker(FSetup.front_addr,FSetup.broker_id,
            FRequest.SetAccount.Account,
            FRequest.SetAccount.PW);
    }

    int timeout = 10;
    while(timeout-->0)
    {
        if( FSession->isLogin() )
        {
            FAccInfo.lt = FRequest.SetAccount.LoginType;
		    lstrcpyn(FAccInfo.PW, FRequest.SetAccount.PW, 13 );
            lstrcpyn(FAccInfo.Capital,FRequest.SetAccount.Account,ACC_LEN);
            return 0;
        }
        else
        {
            Sleep(1000);
        }
    }
    SetLastError(-1,'E',PLUGINNAME,"登录超时！");
    return FLastError.ErrorCode;
}

//资金查询
int TTrdItfImp::QryMoney()
{
    db d;
    try
    {
        d.connect();
        CThostFtdcTradingAccountField acct;
        if( d.qry_account( FAccInfo.Capital, acct ) == 0 )
        {
            NewAns( 1 );

            ( *FAnswer )[0].QryMoney.MoneyInfo.balance =acct.CurrMargin;
            ( *FAnswer )[0].QryMoney.MoneyInfo.available =acct.Available;
            ( *FAnswer )[0].QryMoney.MoneyInfo.MoneyType =motRMB;

            return 0;
        }
    }
    catch(std::string &err)
    {
        SetLastError(-1,'E',PLUGINNAME,"QryMoney:%s",err.c_str());
        return FLastError.ErrorCode;
    }

    return 0;
}

//当日委托查询
int TTrdItfImp::QryCurCsn()
{
    db d;
    try
    {
        d.connect();
        std::vector<CThostFtdcOrderField> list;
        if( FRequest.QryCurCsn.OrderID[0]!=0)  //查单个委托
        {
            CThostFtdcOrderField ord;
            if( d.qry_order_by_ordid(FAccInfo.Capital,FRequest.QryCurCsn.OrderID,ord)==1)
            {
                list.push_back(ord);
            }
        }
        else
        {
            d.qry_orders(FAccInfo.Capital,FRequest.QryCurCsn.SeqNum,
                FRequest.QryCurCsn.MaxRecord,list);
        }

        if( list.size()> 0 )
        {
            NewAns( list.size() );
            for( int i=0; i<list.size(); i++)
            {
                //list[i].
            }
        }
    }
    catch(std::string &err)
    {
        SetLastError(-1,'E',PLUGINNAME,"QryCurCsn:%s",err.c_str());
        return FLastError.ErrorCode;
    }

    return 0;
}

//当日成交查询
int TTrdItfImp::QryCurTrd()
{
    db d;
    try
    {
        d.connect();

        std::vector<CThostFtdcTradeField> list;
        if( FRequest.QryCurTrd.OrderID[0]!=0)  //查单个委托
        {
            d.qry_trade_by_ordid(FAccInfo.Capital,FRequest.QryCurTrd.OrderID,list);
        }
        else
        {
            d.qry_trades(FAccInfo.Capital,FRequest.QryCurTrd.SeqNum,
                FRequest.QryCurTrd.MaxRecord,list);
        }

        if( list.size()> 0 )
        {
            NewAns( list.size() );
            for( int i=0; i<list.size(); i++)
            {
                //list[i].
            }
        }
    }
    catch(std::string &err)
    {
        SetLastError(-1,'E',PLUGINNAME,"QryCurTrd:%s",err.c_str());
        return FLastError.ErrorCode;
    }

    return 0;
}

//查询帐号中所有的股份
int TTrdItfImp::QryStocks()
{
    db d;
    try
    {
        d.connect();
        std::vector<CThostFtdcInvestorPositionField> list;
        d.qry_positions(FAccInfo.Capital,list);
        if( list.size()> 0 )
        {
            NewAns( list.size() );
            for( int i=0; i<list.size(); i++)
            {
                //list[i].
            }
        }
    }
    catch(std::string &err)
    {
        SetLastError(-1,'E',PLUGINNAME,"QryStocks:%s",err.c_str());
        return FLastError.ErrorCode;
    }
    return 0;
}

//委托撤单
int TTrdItfImp::Order()
{
    if( FSession != NULL )
    {
        if( FSession->isLogin() )
        {
            int direction;              //买卖 1,-1
            int openClose;              //开平,平今 1,-1 ,-2
            int hedge=1;                //投机套保1,2

            switch (FRequest.Order.Type) {
                case otOpenBuy:
                    direction=1;
                    openClose=1;
                    break; //开仓买
                case otOpenSell:
                    direction=-1;
                    openClose=1;
                    break; //开仓卖
                case otCloseBuy:
                    direction=1;
                    openClose=-1;
                    break;//平仓买
                case otCloseSell:
                    direction=-1;
                    openClose=-1;
                    break;//平仓卖
                case otCloseTodayBuy:
                    direction=1;
                    openClose=-2;
                    break;// 平今仓买
                case otCloseTodaySell:
                    direction=-1;
                    openClose=-2;
                    break;// 平今仓卖
            default:
                SetLastError(-1,'E',PLUGINNAME,"买卖方向或开平标志不支持");
                return FLastError.ErrorCode;
            }

            int ordid = FSession->ReqOrderInsert(FRequest.Order.SecuID,
                direction,
                FRequest.Order.Price,
                FRequest.Order.Num,
                openClose,
                hedge);
            if( ordid<=0 )
            {
                SetLastError(-1,'E',PLUGINNAME,"委托失败");
                return FLastError.ErrorCode;
            }
            else
            {
                NewAns( 1 );
                sprintf( ( *FAnswer )[0].Order.ContractID,"%d",ordid);
				return 0;
            }
        }
        else
            SetLastError(-1,'E',PLUGINNAME,"Session未登录");
    }
    else
        SetLastError(-1,'E',PLUGINNAME,"Session未建立");
    return FLastError.ErrorCode;
}

int TTrdItfImp::Undo()
{
    if( FSession != NULL )
    {
        if( FSession->isLogin() )
        {
            return FSession->ReqOrderDelete("",FRequest.Undo.ContractID);
        }
        else
            SetLastError(-1,'E',PLUGINNAME,"Session未登录");
    }
    else
        SetLastError(-1,'E',PLUGINNAME,"Session未建立");
    return FLastError.ErrorCode;
}

market_type  TTrdItfImp::ConvertMarketType(const char *t)
{

}

order_type   TTrdItfImp::ConvertOrderType(const char *t)
{

}

order_state  TTrdItfImp::ConvertOrderState(const char *t)
{

}

pos_direction TTrdItfImp::ConvertPosDir(const char *t)
{

}

money_type   TTrdItfImp::ConvertMoneyType(const char *t)
{

}

char *  TTrdItfImp::ConvertMarketType(market_type t)
{

}

char *  TTrdItfImp::ConvertOrderType(order_type t)
{

}

char *  TTrdItfImp::ConvertOrderState(order_state t)
{

}

char *  TTrdItfImp::ConvertPosDir(pos_direction t)
{

}

char *  TTrdItfImp::ConvertMoneyType(money_type t)
{

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

		FSetup.front_addr = AnsiString(ini->ReadString(PLUGINNAME,"front_addr",FSetup.front_addr.c_str())).c_str();
        FSetup.broker_id  = AnsiString(ini->ReadString(PLUGINNAME,"broker_id",FSetup.broker_id.c_str())).c_str();

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
		ini->WriteString (PLUGINNAME,"front_addr",     FSetup.front_addr.c_str());
        ini->WriteString (PLUGINNAME,"broker_id", FSetup.broker_id.c_str());
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

}

int TTrdItfImp::KeepAlive(void)
{
    if( FSession != NULL )
    {
        if( FSession->isLogin() )
            FSession->ReqQry(false);
    }
    return 0;
}
