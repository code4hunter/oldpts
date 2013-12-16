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
        AnsiString custid;              //�ͻ�����
		AnsiString Orgid;               //�ͻ�����
		AnsiString local_ip;
		//AnsiString seat;                //ϯλ
        //AnsiString SESSIONID;           //�Ự��
        //AnsiString SOURCE;              //��������Ϣ

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
