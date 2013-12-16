//---------------------------------------------------------------------------

#ifndef uTrdItfImpH
#define uTrdItfImpH

#include "TradeGateway.h"
#include "UTrdItfBase.h"
#include <string>
#include <map>
#include <list>
#include <boost\thread\mutex.hpp>
#include <StrUtils.hpp>
#include <IniFiles.hpp>
#include <DateUtils.hpp>
#include "IdTCPClient.hpp"

#define PLUGINNAME "KDMID1.2"

typedef std::list<TradeGateway::OrderReport> ORDERS;
typedef std::list<TradeGateway::OrderReport>::iterator ORDER_ITERATOR;

class TTrdItfImp;
class order_manager
{
private:
	ORDERS FOrders;
	boost::mutex _mutex;
	std::string _userid;

	static std::map<std::string,int> userid_list;
	static boost::mutex _map_mutex;
public:
	static bool add_user( const std::string &userid )
	{
		boost::mutex::scoped_lock lock(_map_mutex);
		if( userid_list.count(userid)>0 )
			return false;
		else
		{
			userid_list[userid] = 1;
            ODS("add_user,%s",userid.c_str());
			return true;
        }
	}

	static void remove_user( const std::string &userid )
	{
		boost::mutex::scoped_lock lock(_map_mutex);
		userid_list.erase(userid);
        ODS("remove_user,%s",userid.c_str());
    }

	void load_working_orders(const std::string &userid);
	void qry_orders(TTrdItfImp *itf);
	void add_order(const TradeGateway::OrderReport &op)
	{
		boost::mutex::scoped_lock lock(_mutex);
        FOrders.push_back(op);
    }

	order_manager()
	{

	}

	~order_manager()
	{
		clear_all();
	}

	void clear_all()
	{
		boost::mutex::scoped_lock lock(_mutex);
		FOrders.clear();
		remove_user(_userid);
		_userid = "";
    }
};

////////////////////////////////////////////////////////////////////////////
class TTrdItfImp : public TTrdItfBase
{
public:
	struct TSetup
	{
		AnsiString SvrIp;
		int    SvrPort;
		int    TimeOut;
		bool   debug_mode;
		/*
		代码	操作渠道
		0	柜台委托
		1	电话委托
		2	驻留委托
		3	远程委托
		4	自助委托
		5	漫游委托
		6	银证交易
		7	网上交易
		8	分支委托
		9	小区委托
		A	移动证券
		B	VIP
		C	ETF委托

		*/
		AnsiString entrust_way;               //操作渠道
		AnsiString local_ip;                 //操作站点
		AnsiString money_type;                //0	人民币

		TSetup()
		{
			SvrPort = 9100;
			TimeOut = 5000;
			debug_mode = false;
			entrust_way = "4";
			local_ip = "127.0.0.1";
			money_type = "0";
        }
	} ;

private:	// User declarations
	AnsiString GenCMD( int data_size, AnsiString data );
	TIdTCPClient *FidTcp;
	char FWorkKey[255];
	TSetup FZXSet;
	order_manager order_man;
	//用户代码"，"开户分支","会话序号
	AnsiString FUSER_CODE;
	AnsiString FBRANCH   ;
	AnsiString FSESSION  ;

	AnsiString GetErrorText(int code, char *error);
	AnsiString ReadNextData();
	AnsiString ReadFirstData(AnsiString cmd);
	int  SplitData(const std::string &func,AnsiString SD, TStringList *lstDD, int &fieldcount,int &reccount);
	int GetRecvingDataLen(AnsiString &InputStr, AnsiString TrimStr="|");//20051121--
	DWORD _oldcount;
	//bool FSessionOpened;
public:		// User declarations
	TTrdItfImp(const char *psetupfile,ADDLOG plogfunc);
	virtual ~TTrdItfImp();

	//初始化
	int Init();
	
	//设置帐号
	int SetAccount(bool useOldSession=false);

	//资金查询
	int QryMoney();

	//当日委托查询
	int QryCurCsn();

	//当日成交查询
	int QryCurTrd();

	//查询帐号中所有的股份
	int QryStocks();

	//委托和撤单
	int Order();
	int Undo();

	virtual market_type  ConvertMarketType(const char *t);
	virtual order_type   ConvertOrderType(const char *t);
	virtual order_state  ConvertOrderState(const char *t);
	virtual pos_direction ConvertPosDir(const char *t);
	virtual money_type   ConvertMoneyType(const char *t);

	virtual char *  ConvertMarketType(market_type t);
	virtual char *  ConvertOrderType(order_type t);
	virtual char *  ConvertOrderState(order_state t);
	virtual char *  ConvertPosDir(pos_direction t);
	virtual char *  ConvertMoneyType(money_type t);

	//将配置信息读出来,如果没有获取完整的配置信息返回false
	virtual bool GetConfig(void);
	//将配置信息回写到配置文件
	virtual void SetConfig(void);
	//关闭中间件链接
	virtual void CloseLink(void);

	virtual int KeepAlive(void);
	bool SessionAutoOpen(void);
};

//---------------------------------------------------------------------------
#endif
