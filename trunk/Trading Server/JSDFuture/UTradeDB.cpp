//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTradeDB.h"
#include <vcl.h>
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
	if((hMutex = OpenMutex(MUTEX_ALL_ACCESS,FALSE,"kangxiaofang")) == NULL)

	{
		//如果没有其他进程创建这个互斥量，则重新创建
		hMutex = CreateMutex(NULL,FALSE,"SQLITEDB_JSD");
		WaitForSingleObject(hMutex,INFINITE);
	}
	else
	{
		WaitForSingleObject(hMutex,INFINITE);
	}
}

void trade_db::Unlock()
{
	//释放使用权
	ReleaseMutex(hMutex);
	//关闭句柄
	CloseHandle(hMutex);
}
// 连接数据库
void trade_db::connect(void)
{
	AnsiString dbfilename = FormatDateTime("yyyymmdd",Date()) + ".db";
	bool bcreatedb = !FileExists(dbfilename);

	// open and create db

	//filename = dbfilename;
	int rc = sqlite3_open(dbfilename.c_str(), &db);
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
		 ""ContractID"" VARCHAR NOT NULL , \
		 ""SecuID"" VARCHAR NOT NULL ,\
		 ""TradeID"" VARCHAR NOT NULL , \
		 ""Time"" INTEGER NOT NULL , \
		 ""Date"" INTEGER NOT NULL , \
		 ""Type"" CHAR NOT NULL , \
		 ""Vol"" INTEGER NOT NULL , \
		 ""Price"" DOUBLE NOT NULL , \
		 ""Market"" CHAR NOT NULL , \
		 ""Account"" VARCHAR NOT NULL) ;\
		 CREATE INDEX ""idx_ordexec_account"" ON ""ordexec"" (""Account"" ASC);\
		 \
		 CREATE TABLE ""orders"" ( \
		 ""TraderID"" VARCHAR,\
		 ""CID"" VARCHAR,\
		 ""Code"" VARCHAR,\
		 ""SystemID"" VARCHAR,\
		 ""OrdNum"" VARCHAR,\
		 ""OrdPrice"" VARCHAR,\
		 ""OrdID"" VARCHAR PRIMARY KEY  NOT NULL ,\
		 ""TradeNum"" VARCHAR,\
		 ""TradePrice"" VARCHAR,\
		 ""RemainNum"" VARCHAR,\
		 ""Market"" VARCHAR,\
		 ""State"" CHAR,\
		 ""BS"" CHAR,\
		 ""OC"" CHAR,\
		 ""TB"" CHAR,\
		 ""Account"" VARCHAR NOT NULL,\
		 ""OrdTime"" VARCHAR, \
		 ""PubTime"" VARCHAR, \
		 ""UndoUser"" VARCHAR, \
		 ""UndoTime"" VARCHAR, \
		 ""OrdSeat"" VARCHAR, \
		 ""LocalMark"" VARCHAR, \
		 ""Memo"" VARCGHAR);\
		 CREATE INDEX ""idx_orders_account"" ON ""orders"" (""Account"" ASC)";

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

// 加入一个委托记录
void trade_db::add_order(std::string ord)
{
	if (this->is_connected()) {
		std::ostringstream sql ;
		char values[1024];
		int field = 0;
		int j = 0;
		if( ord.size() >= 1000) throw  std::string("数据长度超过1000");
		for(int i=0;i<ord.size();i++)
		{
			if( ord[i] =='|' )
			{
				field++ ;
				if( field < 22 )
				{
					values[j++] = '\'';
					values[j++] = ',';
					values[j++] = '\'';
				}
				else
				{
					break;
                }
			}
			else
			{
				values[j++] = ord[i];
			}
		}
		values[j] = 0;
		sql <<  "INSERT INTO ""orders"" VALUES ('" << values << "','');";

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
long trade_db::qry_orders(std::string account,std::string ordid,std::string seqnum,long maxrec,
	std::vector<TOrderInfo> &list)
{
	list.clear();
	long retnum = 0;
	return retnum;
}

char trade_db::qry_order_market(std::string account,std::string ordid)
{
	char ret = 'N';
	if (this->is_connected()) {
		std::ostringstream sql ;
		sql << "SELECT * FROM orders WHERE (OrdID='" << ordid
				<< "') AND (CID = '" << account << "');";


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
							/* 获取数据
							 0""TraderID"" VARCHAR,\
							 1""CID"" VARCHAR,\
							 2""Code"" VARCHAR,\
							 3""SystemID"" VARCHAR,\
							 4""OrdNum"" VARCHAR,\
							 5""OrdPrice"" VARCHAR,\
							 6""OrdID"" VARCHAR PRIMARY KEY  NOT NULL ,\
							 7""TradeNum"" VARCHAR,\
							 8""TradePrice"" VARCHAR,\
							 9""RemainNum"" VARCHAR,\
							 10""Market"" VARCHAR,\
							 11""State"" CHAR,\
							 12""BS"" CHAR,\
							 13""OC"" CHAR,\
							 14""TB"" CHAR,\
							 15""Account"" VARCHAR NOT NULL,\
							 16""OrdTime"" VARCHAR, \
							 17""PubTime"" VARCHAR, \
							 18""UndoUser"" VARCHAR, \
							 19""UndoTime"" VARCHAR, \
							 20""OrdSeat"" VARCHAR, \
							 21""LocalMark"" VARCHAR, \
							 22""Memo"" VARCGHAR);\
							*/
							ret= sqlite3_column_text(pstmt,10)[0];

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
	return ret;
}
// 查询交易记录
long trade_db::qry_trades(std::string account,std::string ordid,std::string seqnum,long maxrec,
	std::vector<TTradeInfo> &list)
{
	long retnum = 0;
	list.clear();
	if (this->is_connected()) {
		std::ostringstream sql ;
		if (ordid.length()>0) {
			sql << "SELECT *,rowid FROM ordexec WHERE (ContractID='" << ordid
				<< "') AND (Account = '" << account << "');";
		}
		else
		{
			if (seqnum.length() == 0) {
				sql << "SELECT *,rowid FROM ordexec WHERE (rowid>0) AND (Account = '" << account << "') LIMIT " << maxrec << ";";
			}
			else
				sql << "SELECT *,rowid FROM ordexec WHERE (rowid>" << seqnum << ") AND (Account = '" << account << "') LIMIT " << maxrec << ";";
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

						strncpy(ti.ContractID,sqlite3_column_text(pstmt,0),SEQ_LEN);
						strncpy(ti.SecuID,sqlite3_column_text(pstmt,1),CODE_LEN);
						strncpy(ti.TrdID,sqlite3_column_text(pstmt,2),SEQ_LEN);
						ti.Time = sqlite3_column_int(pstmt,3);
						ti.Date = sqlite3_column_int(pstmt,4);
						ti.Type = sqlite3_column_text(pstmt,5)[0];
						ti.Vol =  sqlite3_column_int(pstmt,6);
						ti.Price = sqlite3_column_double(pstmt,7);
						ti.Market = sqlite3_column_text(pstmt,8)[0];
						strncpy(ti.Account,sqlite3_column_text(pstmt,9) ,ACC_LEN );
						strncpy(ti.SeqNum,sqlite3_column_text(pstmt,10),SEQ_LEN);
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
