//---------------------------------------------------------------------------

#ifndef uTrdIB962H
#define uTrdIB962H

#include "UTradeDB.h"
#include "uRecvEventsTh.h"
#include "PosixTestClient.h"
#include "UTrdItfBase.h"
#include <IniFiles.hpp>
#include <tchar.h>
//---------------------------------------------------------------------------

#define PLUGINNAME "InteractiveBrokers9.62"

class TTrdItf_IB962 : public TTrdItfBase
{
public:
	typedef struct
	{
		AnsiString host;     // 主机地址
		int port;            // 服务端口
		int seed_orderid;
	} TItfSetup;

private:	// User declarations
	TItfSetup _setup;
	PosixTestClient _client;
	int _clientId;
	RecvEventsTh *_worker;
    //trade_db _db;

public:		// User declarations
	TTrdItf_IB962(const char *psetupfile,ADDLOG plogfunc);
	virtual  ~TTrdItf_IB962();

public:
	int  Init();         //初始化
	int  SetAccount();   //登录柜台中间件

	//////查询函数//////
	int  QryMoney();     //资金查询
	int  QryCurCsn();    //当日委托查询
	int  QryCurTrd();    //当日成交查询
	int  QryStocks();    //查询帐号中所有的股份

	//////交易函数/////
	int  Order();        //委托
	int  Undo();         //委托撤单

	//将接口参数转变成标准参数
	/*市场代码
	0--客户号，*--条码号或磁卡号，#--银行代码
	1--上海A股，2--深圳A股，3--上海B股，4--深圳B股，
	*/
	market_type  ConvertMarketType(const char *t)
	{
		if(strlen(t)<1) return mtNo;
		switch(t[0]) {
		case '1': return mtSHA;
		case '2': return mtSZA;
		default:  return mtNo;
		}
	}

	order_type   ConvertOrderType(const char *t)
	{
		return otNo;
	}

	order_state  ConvertOrderState(const char *t)
	{
		return osno;
	}

	pos_direction ConvertPosDir(const char *t)
	{
		return pdNet;
	}

	/*
	1：人民币，2：美元，3：港币，4：港股港币
	*/
	money_type   ConvertMoneyType(const char *t)
	{
		if( t == NULL ) return motNo;
		if( strcmpi( t ,"RMB" ) == 0 )
		{
			return motRMB;
		}
		else if(strcmpi(t,"USD") == 0)
		{
			return motUSD;
		}
		else  if(strcmpi(t,"HKD") == 0)
		{
			return motHKD;
		}
		else return motNo;
	}

	char *  ConvertMarketType(market_type t)
	{
		switch ( t )
		{
			case mtSHA :return "1";
			case mtSZA :return "2";
			default: return "";
		}
	}

	char *  ConvertOrderType(order_type t)
	{
		/*
        7.	买卖类型（1买入、2卖出,0:LOFS申购,9:LOFS赎回,Q:行权，5转股）
			(市价委托模式:XY,X表示买卖,1表示买,2表示卖,Y表示市价类型,1表示第一种市价,2表示第二种…)

		*/
		switch (t) {
			case otBuy: return "1";
			case otSell: return "2";
			case otETFSub: return "1";
			case otETFRed: return "2";
		default:
			return "";
		}
	}

	char *  ConvertOrderState(order_state t)
	{
		return "";
	}

	char *  ConvertPosDir(pos_direction t)
	{
		return "";
	}

	char *  ConvertMoneyType(money_type t)
	{
		switch (t) {
			case motRMB:
				return "RMB";
			case motUSD:
				return "USD";
			case motHKD:
				return "HKD";
			case motNo:
				return "";
        default:
			;
		}
     	return "";
	}

	//将配置信息读出来,如果没有获取完整的配置信息返回false
	bool GetConfig(void)
	{
		if( FSetupFile== NULL ) return false;

		TMemIniFile *ini = new TMemIniFile( FSetupFile );
		try
		{
			// 判断是否存在插件的设置，没有的话返回false以便系统能够生成默认的设置
			if( ini->SectionExists(PLUGINNAME) == false ) return false;
			_setup.host = ini->ReadString(PLUGINNAME,_T("host"),_setup.host);
			_setup.port = ini->ReadInteger(PLUGINNAME, _T("port"), _setup.port);
			_setup.seed_orderid = ini->ReadInteger(PLUGINNAME, _T("seed_orderid"), _setup.seed_orderid);
		}
		__finally
		{
			delete ini;
		}
		return true;
	}
	//将配置信息回写到配置文件
	void SetConfig(void)
	{
		if( FSetupFile== NULL ) return ;

		TMemIniFile *ini = new TMemIniFile( FSetupFile );
		try
		{
			ini->WriteString(PLUGINNAME, _T("host"), _setup.host);
			ini->WriteInteger(PLUGINNAME, _T("port"), _setup.port);
			ini->WriteInteger(PLUGINNAME, _T("seed_orderid"), _setup.seed_orderid);
			ini->UpdateFile();
		}
		__finally
		{
			delete ini;
		}
	}
	//关闭中间件链接
	void CloseLink(void);

};


#endif
