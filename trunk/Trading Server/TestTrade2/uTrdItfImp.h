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
#include "uDatabase.h"

#define PLUGINNAME "TestTrade2"

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
    //database db;
public:
	static bool add_user( const std::string &userid )
	{
		boost::mutex::scoped_lock lock(_map_mutex);
		if( userid_list.count(userid)>0 )
			return false;
		else
		{
			userid_list[userid] = 1;
			//ODS("add_user,%s",userid.c_str());
			return true;
        }
	}

	static void remove_user( const std::string &userid )
	{
		boost::mutex::scoped_lock lock(_map_mutex);
		userid_list.erase(userid);
        //ODS("remove_user,%s",userid.c_str());
    }

	void load_working_orders(const std::string &userid);
	void qry_orders(TTrdItfImp *itf);
	void add_order(const TradeGateway::OrderReport &op)
	{
		boost::mutex::scoped_lock lock(_mutex);
        FOrders.push_back(op);
    }

    int undo_order(const std::string &ordId)
	{
		boost::mutex::scoped_lock lock(_mutex);
        for( ORDER_ITERATOR iter =  FOrders.begin(); iter!=FOrders.end(); iter++)
        {
            if( iter->base.ordId == ordId )
            {
                if( iter->ordStatus <= TradeGateway::Working)
                {
                    iter->ordStatus = TradeGateway::PendingCancel;
                    return 0;
                }
                else return -2;
            }
        }
        return -1;
    }

	order_manager()
	{
        //db.connect("PTrdTestTrd.sqlite");
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
        int   amount_per_match;          // 每次成交百分比
        int   system_cancel_probability; // 系统撤单率
		bool  debug_mode;

		TSetup()
		{
            amount_per_match = 50;
            system_cancel_probability = 1;
			debug_mode = false;
        }
	} ;
    TSetup FZXSet;
private:	// User declaration
	order_manager order_man;
    //database db;
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
