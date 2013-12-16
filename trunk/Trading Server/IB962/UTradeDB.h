//---------------------------------------------------------------------------
#ifndef UTradeDBH
#define UTradeDBH
//---------------------------------------------------------------------------
//#define SQLITE_THREADSAFE 2
#include "sqlite3.h"
#include "UTrdStruct.h"
#include "EWrapper.h"
#include "Contract.h"
#include "Order.h"
#include "Execution.h"
#include "OrderState.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>


class trade_db
{
private:
	sqlite3     *db;
	std::string      filename;
	HANDLE hMutex;

public:
	trade_db();
	~trade_db();
	void Lock();
	void Unlock();
public:
	// �������ݿ�
	void connect(const std::string &dbname="IB962.db");

	// �Ͽ�
	void disconnect(void);

	// ���½������б�
	void reset_tables(void);

	// �Ƿ�������
	bool is_connected(void) const
	{
		return (db!=NULL);
	}

	std::string& get_db_filename(void)
	{
        return filename;
    }

	// ����һ��ί�м�¼
	int add_order(int traderId,OrderId orderId, const Contract&, const Order&, const OrderState& ostate
		,int date,int time);

	// ����һ�����׼�¼������������¼,trdnum <0 ��ʾ������¼
	void add_trade(std::string ordid,std::string trdid,std::string cid,
		std::string code,char market,long time,long date,int trdnum,double trdprice,
		char ordtype);

	// ��ѯί�м�¼
	long qry_orders(std::string ordid,std::string seqnum,long maxrec,
		std::vector<TOrderInfo> &list);

	// ��ѯ���׼�¼
	long qry_trades(std::string ordid,std::string seqnum,long maxrec,
		std::vector<TTradeInfo> &list );

	// ����ί��״̬
	void update_order(OrderId orderId, const IBString &status, int filled=0,
	   int remaining=0, double avgFillPrice=0, int permId=0, int parentId=0,
	   double lastFillPrice=0, int clientId=0, const IBString& whyHeld="");

};



#endif
