//---------------------------------------------------------------------------

#ifndef uDatabaseH
#define uDatabaseH

#include "ThostFtdcUserApiStruct.h"
//#include "UTrdStruct.h"
#include "sqlite3.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class database
{
public:
	database()
	{
		db = NULL;
	}

	~database()
	{
    	this->disconnect();
    }

	// 连接数据库
	void connect(const std::string &dbname="data.sqlite");

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

	long add_order(CThostFtdcOrderField *pOrder);
	void update_order(CThostFtdcOrderField *pOrder);
	void add_trade(CThostFtdcTradeField *pTrade);
	void update_account(CThostFtdcTradingAccountField *pTradingAccount);
	void update_position(CThostFtdcInvestorPositionField *pInvestorPosition);

	int qry_order_by_ordid(const std::string &investorId,const std::string &id,
	           CThostFtdcOrderField &ord);

	int qry_orders(const std::string &investorId,
			   const std::string seqnum,
			   long maxrec,
			   std::vector<CThostFtdcOrderField> &list);

	int qry_trade_by_ordid(const std::string &investorId,const std::string &id,
			   std::vector<CThostFtdcTradeField> &list);

	int qry_trades(const std::string &investorId,
			   const std::string seqnum,
			   long maxrec,
			   std::vector<CThostFtdcTradeField> &list);

	int qry_positions(const std::string &investorId,
	           std::vector<CThostFtdcInvestorPositionField> &list);

	int qry_account(const std::string &investorId,
	           CThostFtdcTradingAccountField &acct);

private:
	sqlite3     	 *db;
	std::string      filename;
};
//---------------------------------------------------------------------------
#endif
