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
		����	��������
		0	��̨ί��
		1	�绰ί��
		2	פ��ί��
		3	Զ��ί��
		4	����ί��
		5	����ί��
		6	��֤����
		7	���Ͻ���
		8	��֧ί��
		9	С��ί��
		A	�ƶ�֤ȯ
		B	VIP
		C	ETFί��

		*/
		AnsiString entrust_way;               //��������
		AnsiString local_ip;                 //����վ��
		AnsiString money_type;                //0	�����

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
	//�û�����"��"������֧","�Ự���
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

	//��ʼ��
	int Init();
	
	//�����ʺ�
	int SetAccount(bool useOldSession=false);

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
	bool SessionAutoOpen(void);
};

//---------------------------------------------------------------------------
#endif
