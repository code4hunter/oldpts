//---------------------------------------------------------------------------
#ifndef UTradeDBH
#define UTradeDBH
//---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include "sqlite3.h"
#include "UTrdStruct.h"


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
	void connect(void);

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
	void add_order(std::string ord);

	// 加入一个交易记录，包括撤单记录,trdnum <0 表示撤单记录
	void add_trade(std::string ordid,std::string trdid,std::string cid,
		std::string code,char market,long time,long date,int trdnum,double trdprice,
		char ordtype);

	// 查询委托记录
	long qry_orders(std::string account,std::string ordid,std::string seqnum,long maxrec,
		std::vector<TOrderInfo> &list);

	// 查询交易记录
	long qry_trades(std::string account,std::string ordid,std::string seqnum,long maxrec,
		std::vector<TTradeInfo> &list );

	char qry_order_market(std::string account,std::string ordid);
};



#endif
