//---------------------------------------------------------------------------
#include "uDatabase.h"
#include "DebugStr.h"
#include <boost/filesystem.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
boost::mutex database::_db_mutex;
//---------------------------------------------------------------------------

std::string siconv(const std::string &atext,
    const std::string &fromcs, const std::string &tocs)
{
    iconv_t cd = iconv_open(tocs.c_str(), fromcs.c_str());

    if (((int) cd) != -1)
	{
		std::string r, text(atext);
		size_t inleft, outleft, soutleft;
		char *inbuf, *outbuf, *sinbuf, *soutbuf;

		//from iconv.c (libiconv)
		iconv(cd, NULL, NULL, NULL, NULL);

		while (!text.empty())
		{
			sinbuf = inbuf = strdup(text.c_str());
			inleft = strlen(inbuf);

			soutleft = outleft = inleft*4;
			soutbuf = outbuf = new char[outleft];

			size_t res = iconv(cd, (const char **)&inbuf, &inleft, &outbuf, &outleft);

			soutbuf[soutleft-outleft] = 0;
			r += soutbuf;
			text.erase(0, text.size()-inleft);

			delete soutbuf;
			delete sinbuf;

			if(res == -1 && errno != EILSEQ)
				break;

			if(!text.empty())
			{
				text.erase(0, 1);
				r += " ";
			}
		}

		iconv_close(cd);
		return r;
    }

    return atext;
}
// 连接数据库
void database::connect(const std::string &dbname)
{
    boost::mutex::scoped_lock lock(_db_mutex);
	filename = dbname;
	if( filename.length() == 0 )
	{
		boost::gregorian::date d(boost::gregorian::day_clock::local_day());
		std::ostringstream name;
		name << d.year() << "-" << d.month() << "-" << d.day() << ".sqlite";
		filename = name.str();
	}

	bool bcreatedb = !boost::filesystem::exists(filename.c_str());

	int rc = sqlite3_open(filename.c_str(), &pdb);
	if( rc ){
		std::ostringstream err ;
		err <<  "Can't open database: " <<  sqlite3_errmsg(pdb);
		sqlite3_close(pdb);
		pdb = NULL;
		throw err.str();
	}

	if (bcreatedb)
	{
		// create tables
		reset_tables();
	}
    sqlite3_exec(pdb,"PRAGMA synchronous = OFF;",0,0,0);
	sqlite3_busy_timeout(pdb,50000);
}

// 断开
void database::disconnect(void)
{
	if (this->is_connected()) {
		sqlite3_close(pdb);
		pdb = NULL;
	}
}

// 重新建立所有表
void database::reset_tables(void)
{
	if (this->is_connected()) {
		std::string sql = "\
CREATE TABLE IF NOT EXISTS dt_orders ( accountId VARCHAR,securityID VARCHAR, securityIDSource INTEGER,side INTEGER, positionEffect INTEGER, ordType INTEGER, lmtPrice DOUBLE, ordQty INTEGER,ordId VARCHAR, ordStatus INTEGER,date INTEGER,time INTEGER, cumQty INTEGER,avgPx DOUBLE,leavesQty INTEGER, text VARCHAR );\
CREATE TABLE IF NOT EXISTS dt_trades(accountId VARCHAR,ordId VARCHAR,execId VARCHAR,execType INTEGER, rejectReason VARCHAR,lastQty INTEGER,lastPx DOUBLE, tradeDate INTEGER, tradeTime INTEGER);\
CREATE TABLE IF NOT EXISTS \"main\".\"dt_sessions\" (\"accountId\" VARCHAR NOT NULL , \"date\" INTEGER NOT NULL , \"seq\" VARCHAR NOT NULL , \"lastUpdateTime\" INTEGER NOT NULL );\
CREATE TRIGGER \"tg_check_filled\" AFTER UPDATE ON dt_orders FOR EACH ROW  BEGIN SELECT RAISE(ROLLBACK,'Already filled!') WHERE ( new.leavesQty<0 or new.cumQty>new.ordQty);  END;\
CREATE INDEX idx_order ON dt_orders (accountId ASC, ordId ASC, date ASC);\
CREATE INDEX idx_trade ON dt_trades (accountId ASC, ordId ASC, tradeDate ASC);\
";

		char *zErrMsg = 0;
		int rc = sqlite3_exec(pdb, sql.c_str(), NULL, 0, &zErrMsg);
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

__int64 database::add_order(const ::TradeGateway::Order *pOrder)
{
	if( !this->is_connected() )
		this->connect();

	std::ostringstream sql;
	sql << "INSERT INTO dt_orders VALUES ("
		<< "'" << pOrder->accountId << "',"
		<< "'" << pOrder->inst.securityID << "',"
		<< ""  << pOrder->inst.securityIDSource<< ","
		<< ""  << pOrder->s << ","
		<< ""  << pOrder->posEfct << ","
		<< ""  << pOrder->type<< ","
		<< ""  << pOrder->lmtPrice<< ","
		<< ""  << pOrder->ordQty << ","
		<< "'" << pOrder->ordId<< "',"
		<< ""  << TradeGateway::New << ","
		<< ""  << pOrder->date<< ","
		<< ""  << pOrder->time<< ","
		<< ""  << 0<< ","
		<< ""  << 0<< ","
		<< ""  << pOrder->ordQty<< ","
		<< "\"" << ""<< "\");";
	
	char *zErrMsg = 0;

	int rc = sqlite3_exec(pdb, sql.str().c_str(), NULL, 0, &zErrMsg);
	if( rc!=SQLITE_OK )
	{
		std::ostringstream err ;
		err << "SQL error: " << zErrMsg;
		sqlite3_free(zErrMsg);
		throw err.str();
	}
	else
		return sqlite3_last_insert_rowid( pdb );
}
//
//void database::update_order(const TradeGateway::OrderReport *pOrder)
//{
//	if( !this->is_connected() )
//		this->connect();
//
//	std::ostringstream sql;
//	if( pOrder->avgPx < 0 )
//	{
//		sql << "UPDATE dt_orders SET "
//			<< "ordStatus =" << pOrder->ordStatus << ","
//			<< "cumQty=" << pOrder->cumQty<< ","
//			<< "leavesQty="  << pOrder->leavesQty<< ") WHERE (ordId='" <<  pOrder->base.ordId << "') AND (date=" << pOrder->base.date << ");";
//	}
//	else
//	{
//		sql << "UPDATE dt_orders SET "
//			<< "ordStatus =" << pOrder->ordStatus << ","
//			<< "cumQty=" << pOrder->cumQty<< ","
//			<< "avgPx=" << pOrder->avgPx << ","
//			<< "leavesQty="  << pOrder->leavesQty<< ") WHERE (ordId='" <<  pOrder->base.ordId << "') AND (date=" << pOrder->base.date << ");";
//	}
//	char *zErrMsg = 0;
//
//	int rc = sqlite3_exec(pdb, sql.str().c_str(), NULL, 0, &zErrMsg);
//	if( rc!=SQLITE_OK )
//	{
//		std::ostringstream err ;
//		err << "SQL error: " << zErrMsg;
//		sqlite3_free(zErrMsg);
//		throw err.str();
//	}
//}

void database::add_trade(const TradeGateway::ExecutionReport *pTrade,const std::string &seq,int updtime)
{
	if( !this->is_connected() )
		this->connect();

	if( pTrade->lastQty == 0 ) return;

	// gb2312 to utf8
	std::string text = siconv(pTrade->ordRejReason,"GB2312","UTF-8");

	std::ostringstream sql;
		
	sql << "BEGIN;";
	sql << "INSERT INTO dt_trades VALUES ("
		<< "'" << pTrade->accountId << "',"
		<< "'" << pTrade->ordId<< "',"
		<< "'" << pTrade->execId << "',"
		<< ""  << pTrade->type<< ","
		<< "\"" << text<< "\","
		<< ""  << pTrade->lastQty << ","
		<< ""  << pTrade->lastPx<< ","
		<< ""  << pTrade->tradeDate<< ","
		<< ""  << pTrade->transactTime<< ");";
	
	//更新委托表
	TradeGateway::OrderStatus os;
	switch( pTrade->type )
	{
	case TradeGateway::EtCanceled:
		os =  TradeGateway::Canceled;
		sql << "UPDATE dt_orders SET "
			<< "ordStatus =" << os << ","
			<< "cumQty=(ordQty-" << abs((int)pTrade->lastQty) << "),"
			<< "text=\"" << text << "\","
			<< "leavesQty="  <<  0 << " "
			<< "WHERE (ordId='" <<  pTrade->ordId << "') "
			<< "AND (accountId='" << pTrade->accountId << "') "
			<< "AND (date=" << pTrade->tradeDate << ");";
		break;
	case TradeGateway::EtRejected:
		os =  TradeGateway::Rejected;
		sql << "UPDATE dt_orders SET "
			<< "ordStatus =" << os << ","
			<< "cumQty=(ordQty-" << abs((int)pTrade->lastQty) << "),"
			<< "text=\"" << text << "\","
			<< "leavesQty="  <<  0 << " "
			<< "WHERE (ordId='" <<  pTrade->ordId << "') "
			<< "AND (accountId='" << pTrade->accountId << "') "
			<< "AND (date=" << pTrade->tradeDate << ");";
		break;
	case TradeGateway::EtStopped:
		os =  TradeGateway::Stopped;
		sql << "UPDATE dt_orders SET "
			<< "ordStatus =" << os << ","
			<< "cumQty=(ordQty-" << abs((int)pTrade->lastQty) << "),"
			<< "text=\"" << text << "\","
			<< "leavesQty="  <<  0 << " "
			<< "WHERE (ordId='" <<  pTrade->ordId << "') "
			<< "AND (accountId='" << pTrade->accountId << "') "
			<< "AND (date=" << pTrade->tradeDate << ");";
		break;
	case TradeGateway::EtTrade:
		sql << "UPDATE dt_orders SET "
			<< "avgPx=(cumQty*avgPx+" <<pTrade->lastQty*pTrade->lastPx<< ")/(cumQty+"<< pTrade->lastQty << "),"
			<< "cumQty=(cumQty+" << pTrade->lastQty << "),"
			<< "leavesQty=leavesQty-"  <<  pTrade->lastQty << ","
			<< "ordStatus = CASE (leavesQty-"<<pTrade->lastQty <<") WHEN 0 then " << TradeGateway::Filled << " ELSE "<<TradeGateway::Working <<" END "
			<< "WHERE (ordId='" <<  pTrade->ordId << "') "
			<< "AND (accountId='" << pTrade->accountId << "') "
			<< "AND (date=" << pTrade->tradeDate << ");";
		break;
	}

    // if seq != "" update seq

    if( seq.length() >0 )
    {
        sql << "UPDATE dt_sessions SET seq = '" << seq << "',"
            << "lastUpdateTime = " <<  updtime << " "
            << "WHERE (accountId='" << pTrade->accountId << "') "
			<< "AND (date=" << pTrade->tradeDate << ");";
    }

	sql << "COMMIT;";
	char *zErrMsg = 0;

	int rc = sqlite3_exec(pdb, sql.str().c_str(), NULL, 0, &zErrMsg);
	if( rc!=SQLITE_OK )
	{
		std::ostringstream err ;
		err << "SQL error: " << zErrMsg;
		sqlite3_free(zErrMsg);
		throw err.str();
	}
}

int database::qry_order_by_ordid(const std::string &investorId,const std::string &id,int date,
					   TradeGateway::OrderReport &ord)
{
	int retnum=0;
	if( !this->is_connected() )
		this->connect();

	std::ostringstream sql;
	sql << "SELECT *,rowid FROM dt_orders WHERE (accountId='" << investorId << "') AND (date=" << date 
		<< ") AND (((ordId='') AND (rowid='" << id << "')) OR (ordId='" << id << "'));";

	sqlite3_stmt *pstmt = NULL;
	const char * pzTail = NULL;
	int rc = sqlite3_prepare_v2(pdb,sql.str().c_str(),sql.str().length(),&pstmt,&pzTail);
	if (rc !=SQLITE_OK) {
		std::ostringstream err ;
		err <<  "Can't prepare query: " <<  sqlite3_errmsg(pdb);
		throw err.str();
	}
	else
	{
		while( 1 )
		{
			rc = sqlite3_step(pstmt);

			if (rc == SQLITE_ERROR) {
				std::ostringstream err ;
				err <<  "Can't step record: " <<  sqlite3_errmsg(pdb);
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
				ord.base.accountId=(const char*)sqlite3_column_text(pstmt,0);
				ord.base.inst.securityID = (const char*)sqlite3_column_text(pstmt,1);
				ord.base.inst.securityIDSource = (TradeGateway::MarketIdSource)sqlite3_column_int(pstmt,2);
				ord.base.s = (TradeGateway::Side)sqlite3_column_int(pstmt,3);
				ord.base.posEfct = (TradeGateway::PositionEffect)sqlite3_column_int(pstmt,4);
				ord.base.type = (TradeGateway::OrdType)sqlite3_column_int(pstmt,5);
				ord.base.lmtPrice = sqlite3_column_double(pstmt,6);
				ord.base.ordQty = sqlite3_column_int(pstmt,7);
				ord.base.ordId = (const char*)sqlite3_column_text(pstmt,8);
				if( ord.base.ordId.length()== 0 )
					ord.base.ordId = (const char*)sqlite3_column_text(pstmt,16);
				ord.ordStatus = (TradeGateway::OrderStatus)sqlite3_column_int(pstmt,9);
				ord.base.date = sqlite3_column_int(pstmt,10);
				ord.base.time = sqlite3_column_int(pstmt,11);
				ord.cumQty = sqlite3_column_int(pstmt,12);
				ord.avgPx = sqlite3_column_double(pstmt,13);
				ord.leavesQty = sqlite3_column_int(pstmt,14);
				ord.text =siconv((const char*)sqlite3_column_text(pstmt,15),"UTF-8","GB2312");
				ord.seq =  (const char*)sqlite3_column_text(pstmt,16);
				retnum++;
			}
		}

		sqlite3_finalize( pstmt );

	}
	return retnum;
}

int database::qry_orders(const std::string &investorId,
			   const std::string &seqnum,
			   long maxrec,int date,
			   TradeGateway::OrderReportSeq &list)
{
	int retnum=0;
	if( !this->is_connected() )
		this->connect();

	std::string seq(seqnum);
	if( seq.length() == 0 )
	{
		seq = "0";
	}

	std::ostringstream sql;
	sql << "SELECT *,rowid FROM dt_orders WHERE (accountId='" << investorId << "') AND (date=" << date 
		<< ") AND (rowid>" << seq << ") order by rowid LIMIT "<<maxrec ;
    //ODS(sql.str().c_str());
	sqlite3_stmt *pstmt = NULL;
	const char * pzTail = NULL;
	int rc = sqlite3_prepare_v2(pdb,sql.str().c_str(),sql.str().length(),&pstmt,&pzTail);
	if (rc !=SQLITE_OK) {
		std::ostringstream err ;
		err <<  "Can't prepare query: " <<  sqlite3_errmsg(pdb);
		throw err.str();
	}
	else
	{
		while( 1 )
		{
			rc = sqlite3_step(pstmt);

			if (rc == SQLITE_ERROR) {
				std::ostringstream err ;
				err <<  "Can't step record: " <<  sqlite3_errmsg(pdb);
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
				TradeGateway::OrderReport ord;
				ord.base.accountId=(const char*)sqlite3_column_text(pstmt,0);
				ord.base.inst.securityID = (const char*)sqlite3_column_text(pstmt,1);
				ord.base.inst.securityIDSource = (TradeGateway::MarketIdSource)sqlite3_column_int(pstmt,2);
				ord.base.s = (TradeGateway::Side)sqlite3_column_int(pstmt,3);
				ord.base.posEfct = (TradeGateway::PositionEffect)sqlite3_column_int(pstmt,4);
				ord.base.type = (TradeGateway::OrdType)sqlite3_column_int(pstmt,5);
				ord.base.lmtPrice = sqlite3_column_double(pstmt,6);
				ord.base.ordQty = sqlite3_column_int(pstmt,7);
				ord.base.ordId = (const char*)sqlite3_column_text(pstmt,8);
				if( ord.base.ordId.length()== 0 )
					ord.base.ordId = (const char*)sqlite3_column_text(pstmt,16);
				ord.ordStatus = (TradeGateway::OrderStatus)sqlite3_column_int(pstmt,9);
				ord.base.date = sqlite3_column_int(pstmt,10);
				ord.base.time = sqlite3_column_int(pstmt,11);
				ord.cumQty = sqlite3_column_int(pstmt,12);
				ord.avgPx = sqlite3_column_double(pstmt,13);
				ord.leavesQty = sqlite3_column_int(pstmt,14);
				ord.text = siconv((const char*)sqlite3_column_text(pstmt,15),"UTF-8","GB2312");
				ord.seq =  (const char*)sqlite3_column_text(pstmt,16);
				list.push_back(ord);
				retnum++;
			}
		}
		sqlite3_finalize( pstmt );
	}
	return retnum;
}

int database::qry_working_orders(const std::string &investorId,
				std::string &seqnum,
				long maxrec,int date,
				TradeGateway::OrderReportSeq &list)
{
	int retnum =0;
	if( !this->is_connected() )
		this->connect();

	std::string seq(seqnum);
	if( seq.length() == 0 )
	{
		seq = "0";
	}

	std::ostringstream sql;

	sql << "SELECT *,rowid FROM dt_orders WHERE (accountId='" << investorId << "') AND (date=" << date
		<< ") AND (rowid>" << seq << ") AND ( ordStatus < " << TradeGateway::PendingCancel
        <<") order by rowid" <<" LIMIT "<< maxrec;

	sqlite3_stmt *pstmt = NULL;
	const char * pzTail = NULL;
	int rc = sqlite3_prepare_v2(pdb,sql.str().c_str(),sql.str().length(),&pstmt,&pzTail);
	if (rc !=SQLITE_OK) {
		std::ostringstream err ;
		err <<  "Can't prepare query: " <<  sqlite3_errmsg(pdb);
		throw err.str();
	}
	else
	{
		while( 1 )
		{
			rc = sqlite3_step(pstmt);

			if (rc == SQLITE_ERROR) {
				std::ostringstream err ;
				err <<  "Can't step record: " <<  sqlite3_errmsg(pdb);
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
				TradeGateway::OrderReport ord;
				ord.base.accountId=(const char*)sqlite3_column_text(pstmt,0);
				ord.base.inst.securityID = (const char*)sqlite3_column_text(pstmt,1);
				ord.base.inst.securityIDSource = (TradeGateway::MarketIdSource)sqlite3_column_int(pstmt,2);
				ord.base.s = (TradeGateway::Side)sqlite3_column_int(pstmt,3);
				ord.base.posEfct = (TradeGateway::PositionEffect)sqlite3_column_int(pstmt,4);
				ord.base.type = (TradeGateway::OrdType)sqlite3_column_int(pstmt,5);
				ord.base.lmtPrice = sqlite3_column_double(pstmt,6);
				ord.base.ordQty = sqlite3_column_int(pstmt,7);
				ord.base.ordId = (const char*)sqlite3_column_text(pstmt,8);
				if( ord.base.ordId.length()== 0 )
					ord.base.ordId = (const char*)sqlite3_column_text(pstmt,16);
				ord.ordStatus = (TradeGateway::OrderStatus)sqlite3_column_int(pstmt,9);
				ord.base.date = sqlite3_column_int(pstmt,10);
				ord.base.time = sqlite3_column_int(pstmt,11);
				ord.cumQty = sqlite3_column_int(pstmt,12);
				ord.avgPx = sqlite3_column_double(pstmt,13);
				ord.leavesQty = sqlite3_column_int(pstmt,14);
				ord.text = (const char*)sqlite3_column_text(pstmt,15);
                ord.seq = (const char*)sqlite3_column_text(pstmt,16);
                seqnum=ord.seq;
				list.push_back(ord);
				retnum++;
			}
		}
		sqlite3_finalize( pstmt );
	}
	return retnum;
}

int database::qry_trade_by_ordid(const std::string &investorId,const std::string &id,int date,
					   TradeGateway::ExecutionReportSeq &list)
{
	int retnum =0;
	if( !this->is_connected() )
		this->connect();

	std::ostringstream sql;
	sql << "SELECT *,rowid FROM dt_trades WHERE (accountId='" << investorId << "') AND (tradeDate=" << date 
		<< ") AND (ordId='" << id << "');";

	sqlite3_stmt *pstmt = NULL;
	const char * pzTail = NULL;
	int rc = sqlite3_prepare_v2(pdb,sql.str().c_str(),sql.str().length(),&pstmt,&pzTail);
	if (rc !=SQLITE_OK) {
		std::ostringstream err ;
		err <<  "Can't prepare query: " <<  sqlite3_errmsg(pdb);
		throw err.str();
	}
	else
	{
		
		while( 1 )
		{
			rc = sqlite3_step(pstmt);

			if (rc == SQLITE_ERROR) {
				std::ostringstream err ;
				err <<  "Can't step record: " <<  sqlite3_errmsg(pdb);
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
				TradeGateway::ExecutionReport er;
				er.accountId = (const char*)sqlite3_column_text(pstmt,0);
				er.ordId = (const char*)sqlite3_column_text(pstmt,1);
				er.execId = (const char*)sqlite3_column_text(pstmt,2);
				er.type =(TradeGateway::ExecType)sqlite3_column_int(pstmt,3);
				er.ordRejReason = siconv((const char*)sqlite3_column_text(pstmt,4),"UTF-8","GB2312");
				er.lastQty = sqlite3_column_int(pstmt,5);
				er.lastPx=sqlite3_column_double(pstmt,6);
				er.tradeDate =sqlite3_column_int(pstmt,7);
				er.transactTime =sqlite3_column_int(pstmt,8);
				er.seq =  (const char*)sqlite3_column_text(pstmt,9);
				list.push_back(er);
				retnum++;
			}
		}
		
		sqlite3_finalize( pstmt );

	}
	return retnum;
}

int database::qry_trades(const std::string &investorId,
			   const std::string &seqnum,
			   long maxrec,int date,
			   TradeGateway::ExecutionReportSeq &list)
{
	int retnum =0;
	if( !this->is_connected() )
		this->connect();

	std::ostringstream sql;
	std::string seq = seqnum;
	if( seq.length() == 0 )
	{
		seq = "0";
	}
	sql << "SELECT *,rowid FROM dt_trades WHERE (accountId='" << investorId << "') AND (tradeDate=" << date 
		<< ") AND (rowid>" <<  seq << ") order by rowid LIMIT "<<maxrec;

	sqlite3_stmt *pstmt = NULL;
	const char * pzTail = NULL;
	int rc = sqlite3_prepare_v2(pdb,sql.str().c_str(),sql.str().length(),&pstmt,&pzTail);
	if (rc !=SQLITE_OK) {
		std::ostringstream err ;
		err <<  "Can't prepare query: " <<  sqlite3_errmsg(pdb);
		throw err.str();
	}
	else
	{

		while( 1 )
		{
			rc = sqlite3_step(pstmt);

			if (rc == SQLITE_ERROR) {
				std::ostringstream err ;
				err <<  "Can't step record: " <<  sqlite3_errmsg(pdb);
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
				TradeGateway::ExecutionReport er;
				er.accountId = (const char*)sqlite3_column_text(pstmt,0);
				er.ordId = (const char*)sqlite3_column_text(pstmt,1);
				er.execId = (const char*)sqlite3_column_text(pstmt,2);
				er.type = (TradeGateway::ExecType)sqlite3_column_int(pstmt,3);
				er.ordRejReason = siconv((const char*)sqlite3_column_text(pstmt,4),"UTF-8","GB2312");
				er.lastQty = sqlite3_column_int(pstmt,5);
				er.lastPx=sqlite3_column_double(pstmt,6);
				er.tradeDate =sqlite3_column_int(pstmt,7);
				er.transactTime =sqlite3_column_int(pstmt,8);
				er.seq =  (const char*)sqlite3_column_text(pstmt,9);
				list.push_back(er);
				retnum++;
			}
		}
		sqlite3_finalize( pstmt );

	}
	return retnum;
}

void database::get_seq(int date,std::string &seq,const std::string &account)
{
    seq = "-1";
    if( !this->is_connected() )
    this->connect();

	std::ostringstream sql;

	sql << "SELECT seq FROM dt_sessions WHERE (accountId='" << account << "') AND (date=" << date << ");";

	sqlite3_stmt *pstmt = NULL;
	const char * pzTail = NULL;
	int rc = sqlite3_prepare_v2(pdb,sql.str().c_str(),sql.str().length(),&pstmt,&pzTail);
	if (rc !=SQLITE_OK) {
		std::ostringstream err ;
		err <<  "Can't prepare query: " <<  sqlite3_errmsg(pdb);
		throw err.str();
	}
	else
	{

		while( 1 )
		{
			rc = sqlite3_step(pstmt);

			if (rc == SQLITE_ERROR) {
				std::ostringstream err ;
				err <<  "Can't step record: " <<  sqlite3_errmsg(pdb);
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
                seq = (const char*)sqlite3_column_text(pstmt,0);
			}
		}
		sqlite3_finalize( pstmt );
	}

    if( seq == "-1" )
    {
        seq = "";
        init_session_seq(date,0,seq,account);
    }
}

void database::init_session_seq(int date,int updtime,const std::string &seq,const std::string &account)
{
    if( !this->is_connected() )
		this->connect();

	std::ostringstream sql;

	sql << "BEGIN;";
    sql << "INSERT INTO dt_sessions VALUES ('" <<account<< "'," << date << ",'" <<seq<<"'," << updtime<< ");";
	sql << "COMMIT;";

	char *zErrMsg = 0;

	int rc = sqlite3_exec(pdb, sql.str().c_str(), NULL, 0, &zErrMsg);
	if( rc!=SQLITE_OK )
	{
		std::ostringstream err ;
		err << "SQL error: " << zErrMsg;
		sqlite3_free(zErrMsg);
		throw err.str();
	}
}
