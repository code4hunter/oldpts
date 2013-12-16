//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTradeDB.h"

#include <classes.hpp>
#include <stdio.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
trade_db::trade_db()
{
	db = NULL;
}

trade_db::~trade_db()
{
	this->disconnect();
}

void trade_db::Lock()
{
}

void trade_db::Unlock()
{
}
// 连接数据库
void trade_db::connect(const std::string &dbname)
{
	filename = dbname;

	bool bcreatedb = !FileExists(filename.c_str());

	int rc = sqlite3_open(filename.c_str(), &db);
	if( rc ){
		std::ostringstream err ;
		err <<  "Can't open database: " <<  sqlite3_errmsg(db);
		sqlite3_close(db);
		db = NULL;
		throw err.str();
	}

	if (bcreatedb)
	{
		// create tables
		reset_tables();
	}
    sqlite3_exec(db,"PRAGMA synchronous = OFF;",0,0,0);
	sqlite3_busy_timeout(db,50000);
}

// 断开
void trade_db::disconnect(void)
{
	if (this->is_connected()) {
		sqlite3_close(db);
		db = NULL;
	}
}

// 重新建立所有表
void trade_db::reset_tables(void)
{
	Lock();
	try
	{
	if (this->is_connected()) {
		std::string sql = "CREATE  TABLE ""main"".""ordexec"" (\
		 ""TraderID"" INTEGER NOT NULL , \
		 ""ContractID"" VARCHAR NOT NULL , \
		 ""SecuID"" VARCHAR NOT NULL ,\
		 ""TradeID"" VARCHAR NOT NULL , \
		 ""Time"" INTEGER NOT NULL , \
		 ""Date"" INTEGER NOT NULL , \
		 ""Type"" VARCHAR NOT NULL , \
		 ""Vol"" INTEGER NOT NULL , \
		 ""Price"" DOUBLE NOT NULL , \
		 ""Market"" VARCHAR NOT NULL , \
		 ""Account"" VARCHAR NOT NULL) ;\
		 CREATE INDEX ""idx_ordexec_tradeid"" ON ""ordexec"" (""TradeId"" ASC);\
		 \
		 CREATE TABLE ""orders"" ( \
		 ""TraderID"" VARCHAR,\
		 ""CID"" VARCHAR,\
		 ""Code"" VARCHAR,\
		 ""SystemID"" VARCHAR,\
		 ""OrdNum"" VARCHAR,\
		 ""OrdPrice"" VARCHAR,\
		 ""OrdID"" VARCHAR NOT NULL ,\
		 ""TradeNum"" VARCHAR,\
		 ""TradePrice"" VARCHAR,\
		 ""RemainNum"" VARCHAR,\
		 ""Market"" VARCHAR,\
		 ""State"" VARCHAR,\
		 ""BS"" VARCHAR,\
		 ""OC"" VARCHAR,\
		 ""TB"" VARCHAR,\
		 ""Account"" VARCHAR NOT NULL,\
		 ""OrdTime"" VARCHAR, \
		 ""PubTime"" VARCHAR, \
		 ""UndoUser"" VARCHAR, \
		 ""UndoTime"" VARCHAR, \
		 ""OrdSeat"" VARCHAR, \
		 ""LocalMark"" VARCHAR, \
		 ""Memo"" VARCHAR, \
		 ""OrderDate"" VARCHAR);\
		 CREATE INDEX ""idx_orders_tradeid"" ON ""orders"" (""TraderID"" ASC)";

		char *zErrMsg = 0;
		int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			std::ostringstream err ;
			err << "SQL error: " << zErrMsg;
			sqlite3_free(zErrMsg);
			throw err.str();
		}
	}
	else
		throw std::string("Not connected to DB!") ;
	}
	__finally
	{
		Unlock();
    }
}

// 加入一个交易记录，包括撤单记录
void trade_db::add_trade(std::string ordid,std::string trdid,std::string cid,
		std::string code,char market,long time,long date,int trdnum,double trdprice,
		char ordtype)
{
	if (this->is_connected()) {
		std::ostringstream sql ;
		sql <<  "INSERT INTO ""ordexec"" VALUES ('"
			<< ordid << "','"
			<< code  << "','"
			<< trdid << "',"
			<< time << ","
			<< date << ",'"
			<< ordtype << "',"
			<< trdnum << ","
			<< trdprice << ",'"
			<< market << "','"
			<< cid << "');" ;

		char *zErrMsg = 0;
		Lock();
		try
		{
		int rc = sqlite3_exec(db, sql.str().c_str(), NULL, 0, &zErrMsg);
		if( rc!=SQLITE_OK ){
			std::ostringstream err ;
			err << "SQL error: " << zErrMsg;
			sqlite3_free(zErrMsg);
			throw err.str();
		}
		}
		__finally
		{
			Unlock();
        }
	}
	else
		throw std::string("Not connected to DB!") ;
}

// 查询委托记录
long trade_db::qry_orders(std::string ordid,std::string seqnum,long maxrec,
	std::vector<TOrderInfo> &list)
{
	long retnum = 0;
	list.clear();
	if (this->is_connected()) {
		std::ostringstream sql ;
		if (ordid.length()>0) {
			sql << "SELECT *,rowid FROM orders WHERE (OrdID='" << ordid
				<< "') AND ( OrderDate = '" << AnsiString(Date().FormatString("yyyymmdd")).c_str()
				<< "');";
		}
		else
		{
			if (seqnum.length() == 0) {
				sql << "SELECT *,rowid FROM orders WHERE (rowid>0) AND ( OrderDate = '" <<
					AnsiString(Date().FormatString("yyyymmdd")).c_str() << "') LIMIT " << maxrec << ";";
			}
			else
				sql << "SELECT *,rowid FROM orders WHERE (rowid>" << seqnum << ") AND ( OrderDate = '" << AnsiString(Date().FormatString("yyyymmdd")).c_str() << "') LIMIT " << maxrec << ";";
		}

		sqlite3_stmt *pstmt = NULL;
		const char * pzTail = NULL;
		Lock();
		try
		{
		int rc = sqlite3_prepare_v2(db,sql.str().c_str(),sql.str().length(),&pstmt,&pzTail);
		if (rc !=SQLITE_OK) {
			std::ostringstream err ;
			err <<  "Can't prepare query: " <<  sqlite3_errmsg(db);
			throw err.str();
		}
		else
		{
			try
			{
				while( 1 )
				{
					rc = sqlite3_step(pstmt);

					if (rc == SQLITE_ERROR) {
						std::ostringstream err ;
						err <<  "Can't step record: " <<  sqlite3_errmsg(db);
						sqlite3_finalize( pstmt );
						throw err.str();
					}
					else if( rc ==SQLITE_MISUSE || rc == SQLITE_DONE )
						break;
					else if( rc == SQLITE_BUSY )
					{
						continue;
					}
					else if( rc ==  SQLITE_ROW )
					{
						// 获取数据
						TOrderInfo oi;
						/*
						CREATE TABLE ""orders"" ( \
						0 ""TraderID"" VARCHAR,\
						1 ""CID"" VARCHAR,\
						2 ""Code"" VARCHAR,\
						3 ""SystemID"" VARCHAR,\
						4 ""OrdNum"" VARCHAR,\
						5 ""OrdPrice"" VARCHAR,\
						6 ""OrdID"" VARCHAR NOT NULL ,\
						7 ""TradeNum"" VARCHAR,\
						8 ""TradePrice"" VARCHAR,\
						9 ""RemainNum"" VARCHAR,\
						10 ""Market"" VARCHAR,\
						11 ""State"" VARCHAR,\
						12 ""BS"" VARCHAR,\
						13 ""OC"" VARCHAR,\
						14 ""TB"" VARCHAR,\
						15 ""Account"" VARCHAR NOT NULL,\
						16 ""OrdTime"" VARCHAR, \
						17 ""PubTime"" VARCHAR, \
						18 ""UndoUser"" VARCHAR, \
						19 ""UndoTime"" VARCHAR, \
						20 ""OrdSeat"" VARCHAR, \
						21 ""LocalMark"" VARCHAR, \
						22 ""Memo"" VARCGHAR);\
						23 ""OrderDate"" VARCHAR;\
						 CREATE INDEX ""idx_orders_account"" ON ""orders"" (""Account"" ASC)";
					*/
						strncpy(oi.ContractID,sqlite3_column_text(pstmt,6),SEQ_LEN);
						strncpy(oi.SecuID,sqlite3_column_text(pstmt,2),CODE_LEN);
						oi.Market = mtNo;
						oi.Time = sqlite3_column_int(pstmt,16);
						oi.Date = sqlite3_column_int(pstmt,23);
						const char * action = sqlite3_column_text(pstmt,12);
						if( strcmpi(action, "buy" )== 0 )
							oi.Type = otBuy;
						else if( strcmpi(action, "sell" )== 0)
							oi.Type = otSell;
						else
							oi.Type = otNo;

						oi.CsnVol = sqlite3_column_int(pstmt,4);
						oi.TrdVol = sqlite3_column_int(pstmt,7);
						oi.CancelVol = 0;
						oi.CsnPrice = sqlite3_column_double(pstmt,5);
						oi.TrdPrice = sqlite3_column_double(pstmt,8);
						/*
						1)PendingSubmit0
						2)PendingCancel0
						3)PendingSubmit
						4)PendingCancel
						5)PreSubmitted
						6)Submitted
						7)Cancelled
						8)Filled
						9)Inactive
						*/
						const char * status = sqlite3_column_text(pstmt,11);
						if( strcmpi(status,"PendingSubmit0") == 0 )
						{
							oi.State = oswb;
						}
						else if( strcmpi(status,"PendingCancel0") == 0 )
						{
							oi.State = osdc ;
						}
						else if( strcmpi(status,"PendingSubmit") == 0 )
						{
							oi.State = oswb;
						}
						else if( strcmpi(status,"PendingCancel") == 0 )
						{
							oi.State = osdc;
						}
						else if( strcmpi(status,"PreSubmitted") == 0 )
						{
							oi.State = oswb;
						}
						else if( strcmpi(status,"Submitted") == 0 )
						{
							oi.State = osyb;
						}
						else if( strcmpi(status,"Cancelled") == 0 )
						{
							oi.CancelVol = oi.CsnVol - oi.TrdVol;
							if( oi.TrdVol == 0 )
								oi.State = osyc;
							else
								oi.State = osbw;
						}
						else if( strcmpi(status,"Cancelled0") == 0 )
						{
							oi.CancelVol = oi.CsnVol;
							oi.State = osyf;
						}
						else if( strcmpi(status,"Filled") == 0 )
						{
							oi.CancelVol = oi.CsnVol - oi.TrdVol;
							if( oi.CancelVol>0 )
                               	oi.State = osbw;
							else
								oi.State = oscj;
						}
						else if( strcmpi(status,"Inactive") == 0 )
						{
							oi.State = osno;
						}
						else
							oi.State = osno;

						strncpy(oi.Account,sqlite3_column_text(pstmt,15) ,ACC_LEN );
						strncpy(oi.SeqNum,sqlite3_column_text(pstmt,24),SEQ_LEN);
						list.push_back(oi);
						retnum++;
					}
				}
			}
			__finally
			{
				sqlite3_finalize( pstmt );
            }
		}
		}
		__finally
		{
        	Unlock();
        }
	}
	else
		throw std::string("Not connected to DB!") ;
	return retnum;
}

// 查询交易记录
long trade_db::qry_trades(std::string ordid,std::string seqnum,long maxrec,
	std::vector<TTradeInfo> &list)
{
	long retnum = 0;
	list.clear();
	if (this->is_connected()) {
		std::ostringstream sql ;
		if (ordid.length()>0) {
			sql << "SELECT *,rowid FROM ordexec WHERE (ContractID='" << ordid
				<< "') AND (Date = "
				<< AnsiString(Date().FormatString("yyyymmdd")).c_str() <<  ")" << ";";
		}
		else
		{
			if (seqnum.length() == 0) {
				sql << "SELECT *,rowid FROM ordexec WHERE (rowid>0) AND (Date = "
					<< AnsiString(Date().FormatString("yyyymmdd")).c_str() <<  ") LIMIT " << maxrec << ";";
			}
			else
				sql << "SELECT *,rowid FROM ordexec WHERE (rowid>" << seqnum << ") AND (Date = "
					<< AnsiString(Date().FormatString("yyyymmdd")).c_str() <<  ") LIMIT " << maxrec << ";";
		}

		sqlite3_stmt *pstmt = NULL;
		const char * pzTail = NULL;
		Lock();
		try
		{
		int rc = sqlite3_prepare_v2(db,sql.str().c_str(),sql.str().length(),&pstmt,&pzTail);
		if (rc !=SQLITE_OK) {
			std::ostringstream err ;
			err <<  "Can't prepare query: " <<  sqlite3_errmsg(db);
			throw err.str();
		}
		else
		{
			try
			{
				while( 1 )
				{
					rc = sqlite3_step(pstmt);

					if (rc == SQLITE_ERROR) {
						std::ostringstream err ;
						err <<  "Can't step record: " <<  sqlite3_errmsg(db);
						sqlite3_finalize( pstmt );
						throw err.str();
					}
					else if( rc ==SQLITE_MISUSE || rc == SQLITE_DONE )
						break;
					else if( rc == SQLITE_BUSY )
					{
						continue;
					}
					else if( rc ==  SQLITE_ROW )
					{
						// 获取数据
						TTradeInfo ti;

						strncpy(ti.ContractID,sqlite3_column_text(pstmt,1),SEQ_LEN);
						strncpy(ti.SecuID,sqlite3_column_text(pstmt,2),CODE_LEN);
						strncpy(ti.TrdID,sqlite3_column_text(pstmt,3),SEQ_LEN);
						ti.Time = sqlite3_column_int(pstmt,4);
						ti.Date = sqlite3_column_int(pstmt,5);
						ti.Type = sqlite3_column_int(pstmt,6);
						ti.Vol =  sqlite3_column_int(pstmt,7);
						ti.Price = sqlite3_column_double(pstmt,8);
						ti.Market = sqlite3_column_text(pstmt,9)[0];
						strncpy(ti.Account,sqlite3_column_text(pstmt,10) ,ACC_LEN );
						strncpy(ti.SeqNum,sqlite3_column_text(pstmt,11),SEQ_LEN);
						list.push_back(ti);
						retnum++;
					}
				}
			}
			__finally
			{
				sqlite3_finalize( pstmt );
            }
		}
		}
		__finally
		{
        	Unlock();
        }
	}
	else
		throw std::string("Not connected to DB!") ;
	return retnum;
}

// 更新委托表
// 如果有成交就生成成交记录
/*
The order status. Possible values include:
codehunter added:
1)PendingSubmit0
2)PendingCancel0
3)Cancelled0

• PendingSubmit - indicates that you have
transmitted the order, but have not yet received
confirmation that it has been accepted by the
order destination. NOTE: This order status is not
sent by TWS and should be explicitly set by the
API developer when an order is submitted.
• PendingCancel - indicates that you have sent a
request to cancel the order but have not yet
received cancel confirmation from the order
destination. At this point, your order is not
confirmed canceled. You may still receive an
execution while your cancellation request is
pending. NOTE: This order status is not sent by
TWS and should be explicitly set by the API
developer when an order is canceled.
• PreSubmitted - indicates that a simulated order
type has been accepted by the IB system and that
this order has yet to be elected. The order is held
in the IB system until the election criteria are met.
At that time the order is transmitted to the order
destination as specified.
• Submitted - indicates that your order has been
accepted at the order destination and is working.
• Cancelled - indicates that the balance of your
order has been confirmed canceled by the IB
system. This could occur unexpectedly when IB or
the destination has rejected your order.
• Filled - indicates that the order has been
completely filled.
• Inactive - indicates that the order has been
accepted by the system (simulated orders) or an
exchange (native orders) but that currently the
order is inactive due to system, exchange or other
issues.

*/
void trade_db::update_order(OrderId orderId, const IBString &status, int filled,
	   int remaining, double avgFillPrice, int permId, int parentId,
	   double lastFillPrice, int clientId, const IBString& whyHeld)
{
/*
 	if (this->is_connected()) {
		std::ostringstream sql ;
		sql << "BEGIN;";

		std::vector<TOrderInfo> ords;
		char tmp[100];
		sprintf( tmp,"%d",orderId);
		Lock();
		if( qry_orders(tmp,"",0,ords ) == 1)
		{
			int trdnum = filled - ords[0].TrdVol ;
			if( trdnum >0 )
			{
				// 生成成交记录
				sql <<  "INSERT INTO ""ordexec"" VALUES ('"
                	<< clientId << "','"
					<< orderId << "','"
					<< ords[0].SecuID  << "',"
					<< "(SELECT ifnull(max(rowid),0)+1 FROM ordexec)" << ","
					<< Time().FormatString("hhnnss") << ","
					<< Date().FormatString("yyyymmdd") << ",'"
					<< ords[0].Type << "',"
					<< trdnum << ","
					<< lastFillPrice << ",'"
					<< "N" << "','"
					<< clientId << "');" ;
			}

			if(  status == "Cancelled" || status == "ApiCancelled")
			{
				int cancelnum = remaining - ords[0].CancelVol;
				if( cancelnum > 0  )
				{
					// 生成撤单记录
					sql <<  "INSERT INTO ""ordexec"" VALUES ('"
					<< clientId << "','"
					<< orderId << "','"
					<< ords[0].SecuID  << "',"
					<< "(SELECT ifnull(max(rowid),0)+1 FROM ordexec)" << ","
					<< Time().FormatString("hhnnss") << ","
					<< Date().FormatString("yyyymmdd") << ",'"
					<< ords[0].Type << "',"
					<< -cancelnum << ","
					<< 0 << ",'"
					<< "N" << "','"
					<< clientId << "');" ;
                }
			}
			else if ( status == "Cancelled0" || status == "Inactive")
			{
				int cancelnum = ords[0].CsnVol - ords[0].TrdVol ;
				if( ords[0].CsnVol > 0 )
				{
					sql <<  "INSERT INTO ""ordexec"" VALUES ('"
					<< clientId << "','"
					<< orderId << "','"
					<< ords[0].SecuID  << "',"
					<< "(SELECT ifnull(max(rowid),0)+1 FROM ordexec)"<< ","
					<< Time().FormatString("hhnnss") << ","
					<< Date().FormatString("yyyymmdd") << ",'"
					<< ords[0].Type << "',"
					<< -cancelnum << ","
					<< 0 << ",'"
					<< "N" << "','"
					<< clientId << "');" ;
                }
			}

			
			//0""TraderID"" VARCHAR,\
			//1""CID"" VARCHAR,\
			//2""Code"" VARCHAR,\
			//3""SystemID"" VARCHAR,\
			//4""OrdNum"" VARCHAR,\
			//5""OrdPrice"" VARCHAR,\
			//6""OrdID"" VARCHAR PRIMARY KEY  NOT NULL ,\
			//7""TradeNum"" VARCHAR,\
			//8""TradePrice"" VARCHAR,\
			//9""RemainNum"" VARCHAR,\
			//10""Market"" VARCHAR,\
			//11""State"" VARCHAR,\
			//12""BS"" VARCHAR,\
			//13""OC"" VARCHAR,\
			//14""TB"" VARCHAR,\
			//15""Account"" VARCHAR NOT NULL,\
			//16""OrdTime"" VARCHAR, \
			//17""PubTime"" VARCHAR, \
			//18""UndoUser"" VARCHAR, \
			//19""UndoTime"" VARCHAR, \
			//20""OrdSeat"" VARCHAR, \
			//21""LocalMark"" VARCHAR, \
			//22""Memo"" VARCGHAR);
			
			sql << "UPDATE orders SET " <<
				   "State = '" << status << "'," <<
				   "TradeNum = '" << filled << "'," <<
				   "RemainNum = '" << remaining << "'," <<
				   "TradePrice = '" << avgFillPrice << "'," <<
				   "SystemID = '" << permId << "'," <<
				   "Memo = '" << "" << "' " <<
				   "WHERE (OrdID ='" << orderId << "');"  ;

			sql << "COMMIT;";
			char *zErrMsg = 0;

			try
			{
				int rc = sqlite3_exec(db, sql.str().c_str(), NULL, 0, &zErrMsg);
				if( rc!=SQLITE_OK ){
					std::ostringstream err ;
					err << "SQL error: " << zErrMsg;
					sqlite3_free(zErrMsg);
					throw err.str();
				}
			}
			__finally
			{
				Unlock();
			}

		}
	}
	else
		throw std::string("Not connected to DB!") ;
	
*/
	if (this->is_connected()) {
		std::ostringstream sql ;
		sql << "BEGIN;";

		std::vector<TOrderInfo> ords;
		char tmp[100];
		sprintf( tmp,"%d",orderId);
		Lock();
		try
		{
			if(  status == "Cancelled" ||
				 status == "ApiCancelled" ||
				 //status == "Inactive" ||
				 status == "Filled" )
			{
				if( qry_orders(tmp,"",0,ords ) == 1)
				{
					if( ords[0].TrdVol+ abs(ords[0].CancelVol) >= ords[0].CsnVol )
					{
						throw std::string("Already filled!") ;
					}
					int trdnum = filled;
					if( trdnum >0 )
					{
						// 生成成交记录
						sql <<  "INSERT INTO ""ordexec"" VALUES ('"
							<< clientId << "','"
							<< orderId << "','"
							<< ords[0].SecuID  << "',"
							<< "(SELECT ifnull(max(rowid),0)+1 FROM ordexec)" << ","
							<< AnsiString(Time().FormatString("hhnnss")).c_str() << ","
							<< AnsiString(Date().FormatString("yyyymmdd")).c_str() << ",'"
							<< ords[0].Type << "',"
							<< trdnum << ","
							<< avgFillPrice << ",'"
							<< "N" << "','"
							<< clientId << "');" ;
					}

					int cancelnum = remaining;
					if( cancelnum > 0  )
					{
						// 生成撤单记录
						sql <<  "INSERT INTO ""ordexec"" VALUES ('"
						<< clientId << "','"
						<< orderId << "','"
						<< ords[0].SecuID  << "',"
						<< "(SELECT ifnull(max(rowid),0)+1 FROM ordexec)" << ","
						<< AnsiString(Time().FormatString("hhnnss")).c_str() << ","
						<< AnsiString(Date().FormatString("yyyymmdd")).c_str() << ",'"
						<< ords[0].Type << "',"
						<< -cancelnum << ","
						<< 0 << ",'"
						<< "N" << "','"
						<< clientId << "');" ;
					}

					sql << "UPDATE orders SET " <<
						   "State = '" << status << "'," <<
						   "TradeNum = '" << filled << "'," <<
						   "RemainNum = '" << remaining << "'," <<
						   "TradePrice = '" << avgFillPrice << "'," <<
						   "SystemID = '" << permId << "'," <<
						   "Memo = '" << "" << "' " <<
						   "WHERE (OrdID ='" << orderId << "');"  ;

					sql << "COMMIT;";
					char *zErrMsg = 0;

					int rc = sqlite3_exec(db, sql.str().c_str(), NULL, 0, &zErrMsg);
					if( rc!=SQLITE_OK ){
						std::ostringstream err ;
						err << "SQL error: " << zErrMsg;
						sqlite3_free(zErrMsg);
						throw err.str();
					}
				}
			}
			else if(status == "Cancelled0")
			{
				if( qry_orders(tmp,"",0,ords ) == 1)
				{
					if( ords[0].TrdVol+ abs(ords[0].CancelVol) >= ords[0].CsnVol )
					{
						throw std::string("Already filled!") ;
					}

					int cancelnum = ords[0].CsnVol;
					if( cancelnum > 0  )
					{
						// 生成撤单记录
						sql <<  "INSERT INTO ""ordexec"" VALUES ('"
						<< clientId << "','"
						<< orderId << "','"
						<< ords[0].SecuID  << "',"
						<< "(SELECT ifnull(max(rowid),0)+1 FROM ordexec)" << ","
						<< AnsiString(Time().FormatString("hhnnss")).c_str() << ","
						<< AnsiString(Date().FormatString("yyyymmdd")).c_str() << ",'"
						<< ords[0].Type << "',"
						<< -cancelnum << ","
						<< 0 << ",'"
						<< "N" << "','"
						<< clientId << "');" ;
					}

					sql << "UPDATE orders SET " <<
						   "State = '" << status << "'," <<
						   "TradeNum = '" << filled << "'," <<
						   "RemainNum = '" << remaining << "'," <<
						   "TradePrice = '" << avgFillPrice << "'," <<
						   "SystemID = '" << permId << "'," <<
						   "Memo = '" << "" << "' " <<
						   "WHERE (OrdID ='" << orderId << "');"  ;

					sql << "COMMIT;";
					char *zErrMsg = 0;

					int rc = sqlite3_exec(db, sql.str().c_str(), NULL, 0, &zErrMsg);
					if( rc!=SQLITE_OK ){
						std::ostringstream err ;
						err << "SQL error: " << zErrMsg;
						sqlite3_free(zErrMsg);
						throw err.str();
					}
				}
			}
		}
		__finally
		{
			Unlock();
		}
	}
	else
		throw std::string("Not connected to DB!") ;


}

// 加入一个委托记录

int trade_db::add_order(int traderId,OrderId orderId, const Contract& contract,
						 const Order& ord, const OrderState& ostate,int date,int time)
{
	if (this->is_connected()) {
		std::ostringstream sql ;
		char *zErrMsg = 0;
		sql <<  "INSERT INTO ""orders"" VALUES ('"
			<< traderId << "','"
			<< ord.clientId << "','"
			// code format:
			// symbol.secType.exchange.currency
			<< contract.symbol << "." <<
			   contract.secType << "." <<
			   contract.exchange << "." <<
			   contract.currency << "','"
			<< "" << "','"
			<< ord.totalQuantity << "','"
			<< ord.lmtPrice << "',"
			<< "(SELECT ifnull(max(rowid),0)+1 FROM orders)" << ",'"
			<< 0 << "','"
			<< 0.0f << "','"
			<< ord.totalQuantity << "','"
			<< contract.exchange << "','"
			<< ostate.status << "','"
			<< ord.action << "','"
			<< "N" << "','"
			<< "N" << "','"
			<<  ord.account<< "','"
			<< time << "','"
			<< 0 << "','"
			<< "" << "','"
			<< 0 << "','"
			<< "" << "','"
			<< ostate.commission << "','"
			<< ostate.warningText << "','"
			<< date << "'"
			<< ");" ;
		Lock();
		try
		{
			int rc = sqlite3_exec(db, sql.str().c_str(), NULL, 0, &zErrMsg);
			if( rc!=SQLITE_OK ){
				if( zErrMsg!=NULL )
				{
					std::ostringstream err ;
					err << "SQL error: " << zErrMsg;
					sqlite3_free(zErrMsg);
					throw err.str();
				}
			}

			return sqlite3_last_insert_rowid( db );
		}
		__finally
		{
			Unlock();
		}
	}
	else
		throw std::string("Not connected to DB!") ;

	return -1;
}
