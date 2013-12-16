#ifndef TRADEADAPTER_H
#define TRADEADAPTER_H

#include "UItfTrd2.h"
#include <IceUtil/IceUtil.h>
#include <list>
#include <Database.h>

namespace PTS2
{

class Trader : public IceUtil::Shared
{
public:
    Trader(const AccountInfo&, const Ice::LoggerPtr&);
    virtual ~Trader();
    void destroy();
    std::string sendOrder(const OrderInfo&);
    void cancelOrder(const std::string& orderId, const std::string& reason);
    OrderStatusInfo queryOrder(const std::string& orderId);
    TradeInfoSeq getTradeInfos(const std::string& seqNum, int maxCount);
    void check();
    int getCancelOrders() { return _cancelOrders.size(); }
	bool checkConnect();
private:
	std::string getOrderType(order_type ot);

    bool isSendOrRecvError(int ret)
    {	
		if( ret == ERR_REMOTE_SEND_FAILED || ret == ERR_REMOTE_RECV_FAILED ||  ERR_REMOTE_OTHER_FAILED )
            return true;
        else
            return false;
    }

    account_type stringToAccountType(const std::string&);
    
    const AccountInfo _acctInfo;
    const Ice::LoggerPtr _logger;

    IceUtil::Mutex _mutex;
    TItfTrd *_itftrd;
    std::list<std::string> _cancelOrders;
    bool _isConnected;
    bool _isSyncCancelOrder;
};

typedef IceUtil::Handle<Trader> TraderPtr;


} /* BlackBox */

#endif /* end of include guard: TRADEADAPTER_H */
