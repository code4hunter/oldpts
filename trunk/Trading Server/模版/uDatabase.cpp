//---------------------------------------------------------------------------


#pragma hdrstop

#include "uDatabase.h"
#include <boost/filesystem.hpp>
//---------------------------------------------------------------------------

#pragma package(smart_init)


// 连接数据库
void database::connect(const std::string &dbname)
{
	filename = dbname;

	bool bcreatedb = !boost::filesystem::exists(filename.c_str());

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

	sqlite3_busy_timeout(db,10000);
}

// 断开
void database::disconnect(void)
{
	if (this->is_connected()) {
		sqlite3_close(db);
		db = NULL;
	}
}

// 重新建立所有表
void database::reset_tables(void)
{
	if (this->is_connected()) {
		std::string sql = "\
CREATE TABLE \"dt_order\" (\"BrokerID\" VARCHAR,\"InvestorID\" VARCHAR,\"InstrumentID\" VARCHAR,\"OrderRef\" VARCHAR,\"UserID\" VARCHAR,\"OrderPriceType\" VARCHAR,\"Direction\" VARCHAR,\"CombOffsetFlag\" VARCHAR,\"CombHedgeFlag\" VARCHAR,\"LimitPrice\" VARCHAR,\"VolumeTotalOriginal\" VARCHAR,\"TimeCondition\" VARCHAR,\"GTDDate\" VARCHAR,\"VolumeCondition\" VARCHAR,\"MinVolume\" VARCHAR,\"ContingentCondition\" VARCHAR,\"StopPrice\" VARCHAR,\"ForceCloseReason\" VARCHAR,\"IsAutoSuspend\" VARCHAR,\"BusinessUnit\" VARCHAR,\"RequestID\" VARCHAR,\"OrderLocalID\" VARCHAR,\"ExchangeID\" VARCHAR,\"ParticipantID\" VARCHAR,\"ClientID\" VARCHAR,\"ExchangeInstID\" VARCHAR,\"TraderID\" VARCHAR,\"InstallID\" VARCHAR,\"OrderSubmitStatus\" VARCHAR,\"NotifySequence\" VARCHAR,\"TradingDay\" VARCHAR,\"SettlementID\" VARCHAR,\"OrderSysID\" VARCHAR,\"OrderSource\" VARCHAR,\"OrderStatus\" VARCHAR,\"OrderType\" VARCHAR,\"VolumeTraded\" VARCHAR,\"VolumeTotal\" VARCHAR,\"InsertDate\" VARCHAR,\"InsertTime\" VARCHAR,\"ActiveTime\" VARCHAR,\"SuspendTime\" VARCHAR,\"UpdateTime\" VARCHAR,\"CancelTime\" VARCHAR,\"ActiveTraderID\" VARCHAR,\"ClearingPartID\" VARCHAR,\"SequenceNo\" VARCHAR,\"FrontID\" VARCHAR,\"SessionID\" VARCHAR,\"UserProductInfo\" VARCHAR,\"StatusMsg\" VARCHAR,\"UserForceClose\" VARCHAR,\"ActiveUserID\" VARCHAR,\"BrokerOrderSeq\" VARCHAR,\"RelativeOrderSysID\" VARCHAR);\
CREATE TABLE \"dt_trade\" (\"InvestorID\" VARCHAR,\"InstrumentID\" VARCHAR,\"OrderRef\" VARCHAR,\"UserID\" VARCHAR,\"ExchangeID\" VARCHAR,\"TradeID\" VARCHAR,\"Direction\" VARCHAR,\"OrderSysID\" VARCHAR,\"ParticipantID\" VARCHAR,\"ClientID\" VARCHAR,\"TradingRole\" VARCHAR,\"ExchangeInstID\" VARCHAR,\"OffsetFlag\" VARCHAR,\"HedgeFlag\" VARCHAR,\"Price\" VARCHAR,\"Volume\" VARCHAR,\"TradeDate\" VARCHAR,\"TradeTime\" VARCHAR,\"TradeType\" VARCHAR,\"PriceSource\" VARCHAR,\"TraderID\" VARCHAR,\"OrderLocalID\" VARCHAR,\"ClearingPartID\" VARCHAR,\"BusinessUnit\" VARCHAR,\"SequenceNo\" VARCHAR,\"TradingDay\" VARCHAR,\"SettlementID\" VARCHAR,\"BrokerOrderSeq\" VARCHAR); \
CREATE TABLE \"dt_account\" (\"BrokerID\" VARCHAR,\"AccountID\" VARCHAR,\"PreMortgage\" VARCHAR,\"PreCredit\" VARCHAR,\"PreDeposit\" VARCHAR,\"PreBalance\" VARCHAR,\"PreMargin\" VARCHAR,\"InterestBase\" VARCHAR,\"Interest\" VARCHAR,\"Deposit\" VARCHAR,\"Withdraw\" VARCHAR,\"FrozenMargin\" VARCHAR,\"FrozenCash\" VARCHAR,\"FrozenCommission\" VARCHAR,\"CurrMargin\" VARCHAR,\"CashIn\" VARCHAR,\"Commission\" VARCHAR,\"CloseProfit\" VARCHAR,\"PositionProfit\" VARCHAR,\"Balance\" VARCHAR,\"Available\" VARCHAR,\"WithdrawQuota\" VARCHAR,\"Reserve\" VARCHAR,\"TradingDay\" VARCHAR,\"SettlementID\" VARCHAR,\"Credit\" VARCHAR,\"Mortgage\" VARCHAR,\"ExchangeMargin\" VARCHAR,\"DeliveryMargin\" VARCHAR,\"ExchangeDeliveryMargin\" VARCHAR);\
CREATE TABLE \"dt_position\" (\"InstrumentID\" VARCHAR,\"BrokerID\" VARCHAR,\"InvestorID\" VARCHAR,\"PosiDirection\" VARCHAR,\"HedgeFlag\" VARCHAR,\"PositionDate\" VARCHAR,\"YdPosition\" VARCHAR,\"Position\" VARCHAR,\"LongFrozen\" VARCHAR,\"ShortFrozen\" VARCHAR,\"LongFrozenAmount\" VARCHAR,\"ShortFrozenAmount\" VARCHAR,\"OpenVolume\" VARCHAR,\"CloseVolume\" VARCHAR,\"OpenAmount\" VARCHAR,\"CloseAmount\" VARCHAR,\"PositionCost\" VARCHAR,\"PreMargin\" VARCHAR,\"UseMargin\" VARCHAR,\"FrozenMargin\" VARCHAR,\"FrozenCash\" VARCHAR,\"FrozenCommission\" VARCHAR,\"CashIn\" VARCHAR,\"Commission\" VARCHAR,\"CloseProfit\" VARCHAR,\"PositionProfit\" VARCHAR,\"PreSettlementPrice\" VARCHAR,\"SettlementPrice\" VARCHAR,\"TradingDay\" VARCHAR,\"SettlementID\" VARCHAR,\"OpenCost\" VARCHAR,\"ExchangeMargin\" VARCHAR,\"CombPosition\" VARCHAR,\"CombLongFrozen\" VARCHAR,\"CombShortFrozen\" VARCHAR,\"CloseProfitByDate\" VARCHAR,\"CloseProfitByTrade\" VARCHAR,\"TodayPosition\" VARCHAR,\"MarginRateByMoney\" VARCHAR,\"MarginRateByVolume\" VARCHAR);\
CREATE UNIQUE INDEX \"idx_account\" ON \"dt_account\" (\"AccountID\" ASC);\
CREATE INDEX \"idx_order\" ON \"dt_order\" (\"InvestorID\" ASC, \"OrderRef\" ASC, \"UserID\" ASC, \"InsertDate\" ASC);\
CREATE INDEX \"idx_position\" ON \"dt_position\" (\"InvestorID\" ASC);\
CREATE INDEX \"idx_trade\" ON \"dt_trade\" (\"InvestorID\" ASC, \"OrderRef\" ASC, \"TradeDate\" ASC);\
";

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

long database::add_order(CThostFtdcOrderField *pOrder)
{
}

void database::update_order(CThostFtdcOrderField *pOrder)
{
}

void database::add_trade(CThostFtdcTradeField *pTrade)
{
}

void database::update_account(CThostFtdcTradingAccountField *pTradingAccount)
{
}

void database::update_position(CThostFtdcInvestorPositionField *pInvestorPosition)
{
}

int database::qry_order_by_ordid(const std::string &investorId,const std::string &id,
           CThostFtdcOrderField &ord)
{
}

int database::qry_orders(const std::string &investorId,
		   const std::string seqnum,
		   long maxrec,
		   std::vector<CThostFtdcOrderField> &list)
{
}

int database::qry_trade_by_ordid(const std::string &investorId,const std::string &id,
		   std::vector<CThostFtdcTradeField> &list)
{
}

int database::qry_trades(const std::string &investorId,
		   const std::string seqnum,
		   long maxrec,
		   std::vector<CThostFtdcTradeField> &list)
{
}

int database::qry_positions(const std::string &investorId,
		   std::vector<CThostFtdcInvestorPositionField> &list)
{
}

int database::qry_account(const std::string &investorId,
		   CThostFtdcTradingAccountField &acct)
{
}
