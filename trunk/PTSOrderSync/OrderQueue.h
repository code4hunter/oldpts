#ifndef _ORDERQUEUE_H_
#define _ORDERQUEUE_H_

#include <Ice/Ice.h>
#include <IceUtil/Monitor.h>
#include <IceUtil/Shared.h>
#include <Database.h>
#include <Trader.h>
#include <list>

namespace PTS2
{

class OrderWorkItem : public virtual IceUtil::Shared
{
public:
    OrderWorkItem(const OrderInfo&, const DatabasePtr&, const Ice::LoggerPtr&);
    void run(const TraderPtr&, const TraderPtr&);

private:
    const OrderInfo _order;
    const DatabasePtr _db;
    const Ice::LoggerPtr _logger;
};

typedef IceUtil::Handle<OrderWorkItem> OrderWorkItemPtr;

class OrderQueue : public IceUtil::Monitor<IceUtil::Mutex>, public IceUtil::Shared
{
public:

    OrderQueue(const AccountInfo&, const TraderPtr&, const Ice::LoggerPtr&);
    ~OrderQueue();

    void start(int);

    void add(const OrderWorkItemPtr&);
    OrderWorkItemPtr get();
    void waitForJoin();
    void destroy();
    void cleanup();

    int workCount();
    int workerCount();

private:
    const AccountInfo _account;
    const Ice::LoggerPtr _logger;
    std::list<IceUtil::ThreadPtr> _workers;
    std::list<OrderWorkItemPtr> _work;
    bool _destroy;
    const TraderPtr _recvTrader;
};

typedef IceUtil::Handle<OrderQueue> OrderQueuePtr;

class OrderThread : public IceUtil::Thread
{
public:

    OrderThread(const TraderPtr& sendTrader, const TraderPtr& recvTrader, const Ice::LoggerPtr& logger, const OrderQueuePtr& manager) :
        _sendTrader(sendTrader),
        _recvTrader(recvTrader),
        _logger(logger),
        _manager(manager)
    {
        
    }

    virtual void run()
    {
        for(;;)
        {
            OrderWorkItemPtr work = _manager->get();
            if(!work)
            {
                return;
            }
            try
            {
                work->run(_sendTrader, _recvTrader);
            }
            catch(const Ice::Exception& e)
            {
                Ice::Warning warn(_logger);
                warn << "OrderThread::run: " << e.what();
            }
        }
    }

private:
    const TraderPtr _sendTrader;
    const TraderPtr _recvTrader;
    const Ice::LoggerPtr _logger;
    const OrderQueuePtr _manager;
};

} /* BlackBox */


#endif /* _ORDERQUEUE_H_ */
