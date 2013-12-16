//---------------------------------------------------------------------------
#ifndef UTrdItf_JSD_GDH
#define UTrdItf_JSD_GDH
//---------------------------------------------------------------------------
#include "UTrdItfBase.h"
#include "JsdGateway.h"
#include <IniFiles.hpp>
#include <tchar.h>

//---------------------------------------------------------------------------

#define PLUGINNAME "金仕达证券v8"

class TTrdItf_JSD_GD : public TTrdItfBase
{
public:
	//enum jsd_entrust_way {zzwt = 1, rjwt, dhwt, kswt, wswt,wzwt,bpwt};

	typedef struct
	{
		AnsiString 	SvrIp;
		int    			SvrPort;
		int    			TimeOut;
		//委托方式 ：
		// 0--自助、1--热自助、2--电话、3--可视委托、
		// 4--网上委托 5-- ETF委托方式  6--bpwt
		// "ZZWT","RJWT","DHWT","KSWT","WSWT","WZWT","BPWT"
		AnsiString  entrust_way;   //操作委托方式
		AnsiString 	branch_no;     //营业部号
		bool        debug_mode;

		AnsiString money_type; // 该值在登陆到柜台时获取
	} TJSDSet;
private:	// User declarations

	JsdGateway *_gateway;

	AnsiString ClientIp;

	TJSDSet _setup;

public:		// User declarations
	TTrdItf_JSD_GD(const char *psetupfile,ADDLOG plogfunc);
	virtual  ~TTrdItf_JSD_GD();

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
		if(strlen(t)>0)
		{
			if (strcmp(t,"买")==0)
				return otBuy;
			else if (strcmp(t, "卖")==0)
				return otSell;
			else if(strcmp(t, "申购")==0)
				return otETFSub;
			else if(strcmp(t, "赎回")==0)
				return otETFRed;
			else
			{
				if(t[0]=='1') return otBuy;
				else if(t[0]=='2') return otSell;
			}
		}

		return otNo;
	}

	order_state  ConvertOrderState(const char *t)
	{
		if(lstrcmp(t,"已成交")==0)
			return oscj;
		else if(lstrcmp(t,"场内撤单")==0)
			return osyc;
		else if(lstrcmp(t,"部分撤单")==0)
			return osbw;
		else if(lstrcmp(t,"场外撤单")==0)
			return osyc;
		else if(lstrcmp(t,"股票不足")==0)
			return osyf;
		else if(lstrcmp(t,"未成交")==0)
			return oswb;
		else if(lstrcmp(t,"已申报")==0)
			return osyb;
		else if(lstrcmp(t,"撤单请求")==0)
			return osdc;
		else if(lstrcmp(t,"撤单已发")==0)
			return osdc;
		else
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
		if( strcmp( t ,"人民币" ) == 0 )
		{
			return motRMB;
		}
		else if(strcmp(t,"美元") == 0)
		{
			return motUSD;
		}
		else  if(strcmp(t,"港币") == 0)
		{
			return motHKD;
		}
		else  if(strcmp(t,"港股港币") == 0)
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
			_setup.SvrIp = ini->ReadString(PLUGINNAME,_T("SvrIp"),_setup.SvrIp);
			_setup.SvrPort = ini->ReadInteger(PLUGINNAME, _T("SvrPort"), _setup.SvrPort);
			_setup.TimeOut = ini->ReadInteger(PLUGINNAME, _T("Timeout"), _setup.TimeOut);
			_setup.entrust_way = ini->ReadString(PLUGINNAME, _T("EntrustWay"), _setup.entrust_way);
			_setup.branch_no = ini->ReadString(PLUGINNAME, _T("BranchNo"), _setup.branch_no);
			_setup.debug_mode = ini->ReadBool(PLUGINNAME, _T("DebugMode"), _setup.debug_mode);
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
			ini->WriteString(PLUGINNAME, _T("SvrIp"), _setup.SvrIp);
			ini->WriteInteger(PLUGINNAME, _T("SvrPort"), _setup.SvrPort);
			ini->WriteInteger(PLUGINNAME, _T("Timeout"), _setup.TimeOut);
			ini->WriteString(PLUGINNAME, _T("EntrustWay"), _setup.entrust_way);
			ini->WriteString(PLUGINNAME, _T("BranchNo"), _setup.branch_no);
			ini->WriteBool(PLUGINNAME, _T("DebugMode"), _setup.debug_mode);
			ini->UpdateFile();
		}
		__finally
		{
			delete ini;
		}
	}
	//关闭中间件链接
	void CloseLink(void)
	{
		_gateway->Disconnect();
	}

};

#endif
