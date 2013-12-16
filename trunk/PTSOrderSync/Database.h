#ifndef DATABASE_H
#define DATABASE_H

#include <Ice/Ice.h>
#include <IceUtil/Mutex.h>
#include <IceUtil/Shared.h>
#include <Freeze/ConnectionF.h>
#include <StringStringDict.h>

#import "MSADO15.DLL" no_namespace rename("EOF", "adoEOF")

namespace PTS2
{

struct AccountInfo
{
    std::string account;
    std::string password;
    std::string host;
    long port;    
    long brokerId;
    long syncType;
};

typedef std::vector<AccountInfo> AccountInfoSeq;

enum OrderStatus
{
    New,
    Partial,
    Filled,
    Rejected,
    Canceled,
    Confirmed
};

struct OrderStatusInfo
{
    int orderQty;
    int tradeQty;
    int cancelQty;
    double orderPrice;
    double tradePrice;    
    OrderStatus status;    
};

struct TradeInfo
{
	int brokerId;
	std::string account;
	std::string instId;
    std::string orderId;
    std::string execId;
	std::string ordtype;
    int volume;
    double price;
    int tradeDate;
    int transactTime;
    std::string seqNum;
	int fillCount;
};

typedef std::vector<TradeInfo> TradeInfoSeq;

enum SideType
{
    Buy,
    Sell,
    Subscribe,
    Redeem,
    Other
};

enum PositionEffect
{
    Invalid,
    Open,
    Close
};

struct InstrumentId
{
    std::string code;
    int marketId;
};

struct OrderInfo
{
	long seqno;
	std::string type;
    std::string account;
	std::string orderId;
    long clOrdId;
    InstrumentId inst;
    SideType side;
    PositionEffect effect;
    int orderQty;
    double orderPrice;
	bool isTodayQty;
	int date;
};

typedef std::vector<OrderInfo> OrderInfoSeq;


class Database : public IceUtil::Shared
{
public:
	Database(const std::string&, const Ice::CommunicatorPtr&, const Ice::LoggerPtr&);

	int getInitializeDate();
    AccountInfoSeq getAccounts();
    OrderInfoSeq getOrders(int date, int startIndex, int maxCount = 100);
    void orderCanceled(long clordid, const std::string& ordid);
    void confirmOrder(long clordid, const std::string&);
    void rejectOrder(long clordid, const std::string&);
	void fillOrder(const TradeInfo&);

    void setProperty(const std::string& name, const std::string& value);
	void setLongProperty(const std::string& name, long value);
    std::string getProperty(const std::string& name);
    double getPropertyAsDouble(const std::string& name);
    int getPropertyAsInt(const std::string& name);
    //::Ice::StringSeq getAllPropertyNames() const;

	void saveLog(const std::string&);

    int getCheckDelay();

private:
	const std::string _envName;
    const std::string _connString;
    const Ice::LoggerPtr _logger;
    const Ice::CommunicatorPtr _communicator;
	IceUtil::Mutex _mutex;
	Freeze::ConnectionPtr _connection;
	StringStringDict _properties;
};

typedef IceUtil::Handle<Database> DatabasePtr;

} /* PTS2 */

#endif /* end of include guard: DATABASE_H */
