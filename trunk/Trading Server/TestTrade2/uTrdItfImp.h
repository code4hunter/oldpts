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
        int   amount_per_match;          // ÿ�γɽ��ٷֱ�
        int   system_cancel_probability; // ϵͳ������
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

	//��ʼ��
	int Init();
	
	//�����ʺ�
	int SetAccount(); 

	//�ʽ��ѯ
	int QryMoney();

	//����ί�в�ѯ
	int QryCurCsn();

	//���ճɽ���ѯ
	int QryCurTrd();

	//��ѯ�ʺ������еĹɷ�
	int QryStocks();

	//ί�кͳ���
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

	//��������Ϣ������,���û�л�ȡ������������Ϣ����false
	virtual bool GetConfig(void);
	//��������Ϣ��д�������ļ�
	virtual void SetConfig(void);
	//�ر��м������
	virtual void CloseLink(void);

	virtual int KeepAlive(void);
};

//---------------------------------------------------------------------------
#endif
