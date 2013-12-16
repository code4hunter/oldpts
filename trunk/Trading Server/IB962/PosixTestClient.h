#ifndef posixtestclient_h__INCLUDED
#define posixtestclient_h__INCLUDED

#include "UTradeDB.h"

#include "..\..\common\BHCmnBase\DebugStr.h"
#include "EWrapper.h"

#include "Contract.h"
#include "Order.h"
#include "Execution.h"
#include "OrderState.h"

#include "EPosixClientSocket.h"
#include "EPosixClientSocketPlatform.h"

#include <SyncObjs.hpp>

#include <time.h>
#include <stdio.h>
#include <memory>
#include <string>
#include <queue>
#include <memory>
#include <map>
#include <vector>

class EPosixClientSocket;

enum State {
	ST_CONNECT,
	ST_PING,
	ST_PING_ACK,
	ST_IDLE
};

struct position
{
	Contract contract;
	int position;
	double marketPrice;
	double marketValue;
	double averageCost;
	double unrealizedPNL;
	double realizedPNL;
	IBString accountName;
};

typedef std::vector< position > POSITIONS;

class positions
{
private:
	POSITIONS _poss;

public:
	void update(const position &pos)
	{
		bool bfind = false;
		if( pos.position == 0) return;
		for( int i=0; i<_poss.size(); i++ )
		{
			if( _poss[i].accountName == pos.accountName &&
				_poss[i].contract.conId == pos.contract.conId //&&
				//_poss[i].position/abs(_poss[i].position) == pos.position/abs(pos.position)
				)
			{
				// update
				_poss[i] = pos;
				bfind = true;
			}
		}

		if (bfind == false) {
			// append
			_poss.push_back(pos);
		}
	}

	POSITIONS get_position(const IBString &accountName)
	{
		POSITIONS ret;
		for( int i=0; i<_poss.size() ; i++ )
		{
			if( _poss[i].accountName == accountName )
			{
				ret.push_back(_poss[i]);
			}
		}
		return  ret;
	}
};

struct account
{
	IBString key;
	IBString val;
	IBString currency;
	IBString accountName;
};

typedef std::vector< account > ACCOUNTS;

class accounts
{
private:
	ACCOUNTS _accs;
public:
	void update(const account &acc )
	{
		bool bfind = false;
		for( int i=0; i< _accs.size(); i++ )
		{
			if( _accs[i].accountName == acc.accountName &&
				_accs[i].currency == acc.currency &&
				_accs[i].key == acc.key )
			{
				_accs[i].val = acc.val ;
				bfind = true;
			}
		}

		if( bfind == false )
		{
			_accs.push_back(acc);
        }
	}

	ACCOUNTS get_account(const IBString &accountName)
	{
		ACCOUNTS ret;
		for( int i=0; i<_accs.size() ; i++ )
		{
			if( _accs[i].accountName == accountName )
			{
				ret.push_back(_accs[i]);
			}
		}
		return  ret;
	}
};

class command
{
public:
	virtual void execute(EPosixClientSocket *client) = 0;
};

class CmdCancel :public command
{
private:
	OrderId _oid;
public:
	CmdCancel( OrderId oid )
		:_oid(oid)
	{
	}

	virtual void execute(EPosixClientSocket *client)
	{
		client->cancelOrder(_oid);
	}
};

class CmdOrder :public command
{
private:
	OrderId _oid;
	Contract _contract;
	Order _order;
public:
	CmdOrder( const Contract &contract, const Order &order ,OrderId oid)
		:_contract(contract)
		,_order(order)
		,_oid(oid)
	{
	}

	virtual void execute(EPosixClientSocket *client)
	{
		client->placeOrder( _oid, _contract, _order);
    }
};

typedef command* command_ptr;

typedef std::queue< command_ptr > CMDS;

class PosixTestClient : public EWrapper
{
public:

	PosixTestClient();
	~PosixTestClient();

	void processMessages();

public:

	bool connect(const char * host, unsigned int port, int clientId = 0);
	void disconnect();
	bool isConnected() const;
	bool isOrderReady() const;
	//void setDB(trade_db *db);

public:
	OrderId sendOrder(Contract &contract,Order &order);
	void cancelOrder( OrderId id );
	POSITIONS getPositions(const IBString &accName);
	ACCOUNTS  getAccounts(const IBString &accName);
private:
	CMDS m_cmds;
	positions m_positions;
	accounts  m_accounts;
	int _clientId;

	//trade_db *_db;

	TCriticalSection *m_cs;

	long getNextValidId(void);
	void init();
	void reqCurrentTime();
	void processTrade();
public:
	// events
	void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute);
	void tickSize(TickerId tickerId, TickType field, int size);
	void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
		double modelPrice, double pvDividend);
	void tickGeneric(TickerId tickerId, TickType tickType, double value);
	void tickString(TickerId tickerId, TickType tickType, const IBString& value);
	void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
		double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry);
	void orderStatus(OrderId orderId, const IBString &status, int filled,
		int remaining, double avgFillPrice, int permId, int parentId,
		double lastFillPrice, int clientId, const IBString& whyHeld);
	void openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&);
	void openOrderEnd();
	void winError(const IBString &str, int lastError);
	void connectionClosed();
	void updateAccountValue(const IBString& key, const IBString& val,
		const IBString& currency, const IBString& accountName);
	void updatePortfolio(const Contract& contract, int position,
		double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const IBString& accountName);
	void updateAccountTime(const IBString& timeStamp);
	void accountDownloadEnd(const IBString& accountName);
	void nextValidId(OrderId orderId);
	void contractDetails(int reqId, const ContractDetails& contractDetails);
	void bondContractDetails(int reqId, const ContractDetails& contractDetails);
	void contractDetailsEnd(int reqId);
	void execDetails(int reqId, const Contract& contract, const Execution& execution);
	void execDetailsEnd(int reqId);
	void error(const int id, const int errorCode, const IBString errorString);
	void updateMktDepth(TickerId id, int position, int operation, int side,
		double price, int size);
	void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
		int side, double price, int size);
	void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch);
	void managedAccounts(const IBString& accountsList);
	void receiveFA(faDataType pFaDataType, const IBString& cxml);
	void historicalData(TickerId reqId, const IBString& date, double open, double high,
		double low, double close, int volume, int barCount, double WAP, int hasGaps);
	void scannerParameters(const IBString &xml);
	void scannerData(int reqId, int rank, const ContractDetails &contractDetails,
		const IBString &distance, const IBString &benchmark, const IBString &projection,
		const IBString &legsStr);
	void scannerDataEnd(int reqId);
	void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
		long volume, double wap, int count);
	void currentTime(long time);
	void fundamentalData(TickerId reqId, const IBString& data);
	void deltaNeutralValidation(int reqId, const UnderComp& underComp);
	void tickSnapshotEnd(int reqId);

private:

	std::auto_ptr<EPosixClientSocket> m_pClient;
	State m_state;
	time_t m_sleepDeadline;

	OrderId m_orderId;
	OrderId m_firstId;
};

#endif

