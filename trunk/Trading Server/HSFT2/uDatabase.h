//---------------------------------------------------------------------------

#ifndef uDatabaseH
#define uDatabaseH

//#define SQLITE_THREADSAFE 0
#include "TradeGateway.h"
#include "sqlite3.h"
#include "iconv.h"
#include <boost\thread\mutex.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class database
{
public:
	database()
	{
		pdb = NULL;
	}

	~database()
	{
    	this->disconnect();
    }

	// 连接数据库
	void connect(const std::string &dbname="");

	// 断开
	void disconnect(void);

	// 重新建立所有表
	void reset_tables(void);

	// 是否已连接
	bool is_connected(void) const
	{
		return (pdb!=NULL);
	}

	std::string& get_db_filename(void)
	{
        return filename;
    }

	//返回rowid
	__int64 add_order(const ::TradeGateway::Order *pOrder);
	//void update_order(const TradeGateway::OrderReport *pOrder);
	void add_trade(const TradeGateway::ExecutionReport *pTrade,const std::string &seq,int updtime);

	//返回结果个数
	int qry_order_by_ordid(const std::string &investorId,const std::string &id,int date,
				TradeGateway::OrderReport &ord);

	int qry_orders(const std::string &investorId,
				const std::string &seqnum,
				long maxrec,int date,
				TradeGateway::OrderReportSeq &list);

	int qry_working_orders(const std::string &investorId,
				std::string &seqnum,
				long maxrec,int date,
				TradeGateway::OrderReportSeq &list);
	int qry_trade_by_ordid(const std::string &investorId,const std::string &id,int date,
				TradeGateway::ExecutionReportSeq &list);

	int qry_trades(const std::string &investorId,
				const std::string &seqnum,
				long maxrec,int date,
				TradeGateway::ExecutionReportSeq &list);
    void get_seq(int date,std::string &seq,const std::string &account);
private:
	sqlite3     	 *pdb;
	std::string      filename;
    static boost::mutex _db_mutex;
    void init_session_seq(int date,int updtime,const std::string &seq,const std::string &account);
};
//---------------------------------------------------------------------------
#endif
