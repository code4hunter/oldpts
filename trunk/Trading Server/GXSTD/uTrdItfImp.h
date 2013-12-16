//---------------------------------------------------------------------------

#ifndef uTrdItfImpH
#define uTrdItfImpH

#include "TradeGateway.h"
#include "UTrdItfBase.h"
#include <string>
#include <list>
#include <StrUtils.hpp>
#include <IniFiles.hpp>
#include <DateUtils.hpp>
#include "IdTCPClient.hpp"
#include <boost\thread\mutex.hpp>

#define PLUGINNAME "GXSTD"

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
        int    PushPort;
		int    TimeOut;
		bool   debug_mode;
        AnsiString custid;              //客户代码
		AnsiString Orgid;               //客户机构
		AnsiString local_ip;
		//AnsiString seat;                //席位
        //AnsiString SESSIONID;           //会话号
        //AnsiString SOURCE;              //发起者信息

		TSetup()
		{
            SvrIp = "127.0.0.1";
			SvrPort  =  0;
            PushPort =  0;
			TimeOut = 5000;
			debug_mode = false;
			custid = "";
			Orgid = "";
			local_ip="" ;
			//seat = "0";
            //SESSIONID = "1";
            //SOURCE = "BHTrdSvr";
        }
	} ;

private:	// User declarations
	TSetup FSetup;
    order_manager order_man;
	std::string ReadFirstData(const std::string & cmd);

public:		// User declarations
	TTrdItfImp(const char *psetupfile,ADDLOG plogfunc);
	virtual ~TTrdItfImp();

	//初始化
	int Init();
	
	//设置帐号
	int SetAccount(); 

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
};

//---------------------------------------------------------------------------
#endif
