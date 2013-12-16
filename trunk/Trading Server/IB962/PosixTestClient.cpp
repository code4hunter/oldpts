#include "PosixTestClient.h"

#include <DateUtils.hpp>
const int PING_DEADLINE = 50; // seconds
const int SLEEP_BETWEEN_PINGS = 70; // seconds

///////////////////////////////////////////////////////////
// member funcs
PosixTestClient::PosixTestClient()
	: m_pClient(new EPosixClientSocket(this))
	, m_state(ST_CONNECT)
	, m_sleepDeadline(0)
	, m_orderId(0)
	, m_firstId(0)
	//, _db(NULL)
	, _clientId(0)
{
	m_cs = new TCriticalSection();
}

PosixTestClient::~PosixTestClient()
{
	disconnect();
	delete m_cs;
}

bool PosixTestClient::connect(const char *host, unsigned int port, int clientId)
{
	// trying to connect
	ODS( "Connecting to %s:%d clientId:%d\n", !( host && *host) ? "127.0.0.1" : host, port, clientId);

	bool bRes = m_pClient->eConnect( host, port, clientId);

	if (bRes) {
		ODS( "Connected to %s:%d clientId:%d\n", !( host && *host) ? "127.0.0.1" : host, port, clientId);
	}
	else
		ODS( "Cannot connect to %s:%d clientId:%d\n", !( host && *host) ? "127.0.0.1" : host, port, clientId);

	m_sleepDeadline = 0;
	_clientId =  clientId;
	return bRes;
}

void PosixTestClient::disconnect()
{
	m_firstId = 0;
	m_orderId = 0;
	m_pClient->eDisconnect();

	// 将未处理的命令执行完毕 ，并删除,需要更新本地数据库
    m_cs->Enter();
	try
	{
		for( int i=m_cmds.size(); i>0; i-- )
		{
			command_ptr &cmd = m_cmds.front();
			cmd->execute(this->m_pClient.get());
			m_cmds.pop();
			delete cmd;
		}
	}
	__finally
	{
		m_cs->Leave();
	}

	ODS ( "Disconnected\n");
}

bool PosixTestClient::isConnected() const
{
	return m_pClient->isConnected();
}

bool PosixTestClient::isOrderReady() const
{
	return (m_firstId>0);
}
/*
void PosixTestClient::setDB(trade_db *db)
{
	_db = db;
}
*/

OrderId PosixTestClient::sendOrder(Contract &contract,Order &order)
{
	//if( _db == NULL ) return -1;

	OrderId oid =0; //getNextValidId();
	//order.orderId = oid;
	m_cs->Enter();
	try
	{
		
		OrderState state;
		state.status = "PendingSubmit0";
		unsigned short y,m,d,h,min,s,ms;
		DecodeDateTime( Now(),y,m,d,h,min,s,ms);
		trade_db _db;
		try
		{
			_db.connect();
			oid = _db.add_order(order.clientId,oid,contract,order,state,y*10000+m*100+d,
				h*10000+min*100+s);
			command_ptr cmd = new CmdOrder(contract,order,oid);
			m_cmds.push(cmd);
		}
		catch(std::string &e)
		{
			ODS("sendOrder.add_order error:%s",e.c_str());
		}
	}
	__finally
	{
		m_cs->Leave();
	}
	return oid;
}

void PosixTestClient::cancelOrder( OrderId id )
{
	//if( _db == NULL ) return;
	command_ptr cmd = new CmdCancel(id);
	m_cs->Enter();
	try
	{
		trade_db _db;
		try
		{
			_db.connect();
			_db.update_order(id,"PendingCancel0") ;
		}
		catch(std::string &e)
		{
			ODS("cancelOrder.add_order update_order:%s",e.c_str());
		}
		m_cmds.push( cmd );
	}
	__finally
	{
		m_cs->Leave();
	}
}

void PosixTestClient::processTrade()
{
	m_cs->Enter();
	try
	{
		if( m_cmds.size()==0 ) return;
		command_ptr &cmd = m_cmds.front();
		cmd->execute(this->m_pClient.get());
		m_cmds.pop();
		delete cmd;
	}
	__finally
	{
		m_cs->Leave();
	}
}

void PosixTestClient::init()
{
	// subscribe account change
	this->m_pClient->reqAccountUpdates(true,/*m_accId*/"");
	//ExecutionFilter ef;
	//this->m_pClient->reqExecutions()
	m_state = ST_IDLE;
}

void PosixTestClient::processMessages()
{
	fd_set readSet, writeSet, errorSet;

	struct timeval tval;
	tval.tv_usec = 0;
	tval.tv_sec = 0;

	time_t now = time(NULL);

	switch (m_state) {
		case ST_CONNECT:
			init();
			break;
		case ST_PING:
			reqCurrentTime();
			break;
		case ST_PING_ACK:
			if( m_sleepDeadline < now && m_sleepDeadline!=0) {
				disconnect();
				ODS( "Timeout\n");
				return;
			}
			else
				m_state = ST_IDLE;
			break;
		case ST_IDLE:
			processTrade();
			if( m_sleepDeadline < now) {
				m_state = ST_PING;
				return;
			}
			break;
	}

	if( m_sleepDeadline > 0) {
		// initialize timeout with m_sleepDeadline - now
		tval.tv_sec = m_sleepDeadline - now;
	}

	if( m_pClient->fd() >= 0 ) {

		FD_ZERO( &readSet);
		errorSet = writeSet = readSet;

		FD_SET( m_pClient->fd(), &readSet);

		if( !m_pClient->isOutBufferEmpty())
			FD_SET( m_pClient->fd(), &writeSet);

		FD_CLR( m_pClient->fd(), &errorSet);

		//set poll timeout
		tval.tv_sec  = 0;
		tval.tv_usec = 500; //100 millsecond
		int ret = select( m_pClient->fd() + 1, &readSet, &writeSet, &errorSet, &tval);

		if( ret == 0) { // timeout
			return;
		}

		if( ret < 0) {	// error
			disconnect();
			return;
		}

		if( m_pClient->fd() < 0)
			return;

		if( FD_ISSET( m_pClient->fd(), &errorSet)) {
			// error on socket
			m_pClient->onError();
		}

		if( m_pClient->fd() < 0)
			return;

		if( FD_ISSET( m_pClient->fd(), &writeSet)) {
			// socket is ready for writing
			m_pClient->onSend();
		}

		if( m_pClient->fd() < 0)
			return;

		if( FD_ISSET( m_pClient->fd(), &readSet)) {
			// socket is ready for reading
			m_pClient->onReceive();
		}
	}
}

POSITIONS PosixTestClient::getPositions(const IBString &accName)
{
	return  m_positions.get_position( accName );
}

ACCOUNTS  PosixTestClient::getAccounts(const IBString &accName)
{
 	return m_accounts.get_account( accName);
}
//////////////////////////////////////////////////////////////////
// methods
void PosixTestClient::reqCurrentTime()
{
	ODS( "Requesting Current Time\n");

	// set ping deadline to "now + n seconds"
	m_sleepDeadline = time( NULL) + PING_DEADLINE;

	m_state = ST_PING_ACK;

	m_pClient->reqCurrentTime();
}

///////////////////////////////////////////////////////////////////
// events
void PosixTestClient::orderStatus( OrderId orderId, const IBString &status, int filled,
	   int remaining, double avgFillPrice, int permId, int parentId,
	   double lastFillPrice, int clientId, const IBString& whyHeld)

{
	//if( _db == NULL ) return ;
	//将状态信息更新到委托表
	ODS( "Order: id=%ld, status=%s\n", orderId, status.c_str());

	trade_db _db;
	try
	{
		_db.connect();
		if(  lastFillPrice >0.00001)
			_db.update_order(orderId,status,filled,remaining,avgFillPrice,permId,
				parentId,lastFillPrice,clientId,whyHeld) ;
		else
             _db.update_order(orderId,status,filled,remaining,avgFillPrice,permId,
				parentId,avgFillPrice,clientId,whyHeld) ;
	}
	catch(std::string &e)
	{
		ODS("orderStatus.update_order error:%s",e.c_str());
	}
}

void PosixTestClient::nextValidId( OrderId orderId)
{
	if(m_firstId==0)
	{
		m_orderId = orderId;
		m_firstId = orderId;
	}
}

long PosixTestClient::getNextValidId(void)
{
	return ::InterlockedIncrement(&m_orderId);
}

void PosixTestClient::currentTime( long time)
{
	if ( m_state == ST_PING_ACK) {
		time_t t = ( time_t)time;
		struct tm * timeinfo = localtime ( &t);
		ODS( "The current date/time is: %s", asctime( timeinfo));

		time_t now = ::time(NULL);
		m_sleepDeadline = now + SLEEP_BETWEEN_PINGS;

		m_state = ST_IDLE;
	}
}

void PosixTestClient::error(const int id, const int errorCode, const IBString errorString)
{
	ODS( "Error id=%d, errorCode=%d, msg=%s\n", id, errorCode, errorString.c_str());

	if (id <0 || errorCode == 404 || errorCode == 202 ||  errorCode == 399 || errorCode > 2000) {
		return;
	}
	trade_db _db;
	try
	{
		_db.connect();
		_db.update_order(id,"Cancelled0",0,0,0,0,0,0,_clientId,errorString);
	}
	catch(std::string &e)
	{
		ODS("error.update_order error:%s",e.c_str());
	}
	if( id == -1 && errorCode == 1100) // if "Connectivity between IB and TWS has been lost"
		disconnect();
}

void PosixTestClient::tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute) {}
void PosixTestClient::tickSize( TickerId tickerId, TickType field, int size) {}
void PosixTestClient::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
											 double modelPrice, double pvDividend) {}

void PosixTestClient::tickGeneric(TickerId tickerId, TickType tickType, double value) {}
void PosixTestClient::tickString(TickerId tickerId, TickType tickType, const IBString& value) {}
void PosixTestClient::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
							   double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) {}
void PosixTestClient::openOrder( OrderId orderId, const Contract&, const Order&, const OrderState& ostate) {}
void PosixTestClient::openOrderEnd() {}
void PosixTestClient::winError( const IBString &str, int lastError) {}
void PosixTestClient::connectionClosed() {}
void PosixTestClient::updateAccountValue(const IBString& key, const IBString& val,
										  const IBString& currency, const IBString& accountName)
{
	// to do 将账户信息更新到一个map中 key为accountName
	account acc;
	acc.key = key;
	acc.val = val;
	acc.currency = currency;
	acc.accountName = accountName;
	m_accounts.update(acc);
}

void PosixTestClient::updatePortfolio(const Contract& contract, int pos,
		double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const IBString& accountName)
{
	// to do 将持仓更新到一个key为accountName的map中
	position p;
	p.contract = contract;
	p.position = pos;
	p.marketPrice = marketPrice;
	p.marketValue = marketValue;
	p.averageCost = averageCost;
	p.unrealizedPNL = unrealizedPNL;
	p.realizedPNL = realizedPNL;
	p.accountName = accountName;
	m_positions.update(p);
}

void PosixTestClient::updateAccountTime(const IBString& timeStamp) {}
void PosixTestClient::accountDownloadEnd(const IBString& accountName) {}
void PosixTestClient::contractDetails( int reqId, const ContractDetails& contractDetails) {}
void PosixTestClient::bondContractDetails( int reqId, const ContractDetails& contractDetails) {}
void PosixTestClient::contractDetailsEnd( int reqId) {}
void PosixTestClient::execDetails( int reqId, const Contract& contract, const Execution& execution)
{

}

void PosixTestClient::execDetailsEnd( int reqId) {}

void PosixTestClient::updateMktDepth(TickerId id, int position, int operation, int side,
									  double price, int size) {}
void PosixTestClient::updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
										int side, double price, int size) {}
void PosixTestClient::updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {}
void PosixTestClient::managedAccounts( const IBString& accountsList) {}
void PosixTestClient::receiveFA(faDataType pFaDataType, const IBString& cxml) {}
void PosixTestClient::historicalData(TickerId reqId, const IBString& date, double open, double high,
									  double low, double close, int volume, int barCount, double WAP, int hasGaps) {}
void PosixTestClient::scannerParameters(const IBString &xml) {}
void PosixTestClient::scannerData(int reqId, int rank, const ContractDetails &contractDetails,
	   const IBString &distance, const IBString &benchmark, const IBString &projection,
	   const IBString &legsStr) {}
void PosixTestClient::scannerDataEnd(int reqId) {}
void PosixTestClient::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
								   long volume, double wap, int count) {}
void PosixTestClient::fundamentalData(TickerId reqId, const IBString& data) {}
void PosixTestClient::deltaNeutralValidation(int reqId, const UnderComp& underComp) {}
void PosixTestClient::tickSnapshotEnd(int reqId) {}

