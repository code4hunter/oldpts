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
	// 连接数据库
	void connect(const std::string &dbname="IB962.db");

	// 断开
	void disconnect(void);

	// 重新建立所有表
	void reset_tables(void);

	// 是否已连接
	bool is_connected(void) const
	{
		return (db!=NULL);
	}

	std::string& get_db_filename(void)
	{
        return filename;
    }

	// 加入一个委托记录
	int add_order(int traderId,OrderId orderId, const Contract&, const Order&, const OrderState& ostate
		,int date,int time);

	// 加入一个交易记录，包括撤单记录,trdnum <0 表示撤单记录
	void add_trade(std::string ordid,std::string trdid,std::string cid,
		std::string code,char market,long time,long date,int trdnum,double trdprice,
		char ordtype);

	// 查询委托记录
	long qry_orders(std::string ordid,std::string seqnum,long maxrec,
		std::vector<TOrderInfo> &list);

	// 查询交易记录
	long qry_trades(std::string ordid,std::string seqnum,long maxrec,
		std::vector<TTradeInfo> &list );

	// 更新委托状态
	void update_order(OrderId orderId, const IBString &status, int filled=0,
	   int remaining=0, double avgFillPrice=0, int permId=0, int parentId=0,
	   double lastFillPrice=0, int clientId=0, const IBString& whyHeld="");

};



#endif
