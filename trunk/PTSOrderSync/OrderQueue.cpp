#include <OrderQueue.h>
#include <cmath>
#include <Trader.h>
#include <OrderSyncServer.h>

using namespace std;

namespace PTS2
{

OrderWorkItem::OrderWorkItem(const OrderInfo& order, 
                             const DatabasePtr& db, 
                             const Ice::LoggerPtr& logger) :
    _order(order),
    _db(db),
    _logger(logger)
{
}

void 
OrderWorkItem::run(const TraderPtr& sendTrader, const TraderPtr& recvTrader)
{
    try
    {
	    if (_order.type == "C")
	    {
		    try
		    {
			    recvTrader->cancelOrder(_order.orderId, "");
                _db->orderCanceled(_order.clOrdId, _order.orderId);
		    }
		    catch (const FailureException& ex)
		    {
                Ice::Error err(_logger);
                err << "cancelOrder:" << ex.reason;
		    }
	    }
	    else
	    {
		    try
		    {
			    std::string orderId = sendTrader->sendOrder(_order);
			    _db->confirmOrder(_order.clOrdId, orderId);
		    }
		    catch (const FailureException& ex)
		    {
			    _db->rejectOrder(_order.clOrdId, ex.reason);
		    }
	    }
    }
    catch(const Ice::Exception& e)
    {
        Ice::Error out(_logger);
        out << "OrderWorkItem::run: " << e;
    }
    catch(...)
    {
        Ice::Error out(_logger);
        out << "OrderWorkItem::run:Î´Öª´íÎó";
    }
}

// OrderQueue
OrderQueue::OrderQueue(const AccountInfo& account, const TraderPtr& recvTrader, const Ice::LoggerPtr& logger) :
    _account(account),
    _recvTrader(recvTrader),
    _logger(logger),
    _destroy(false)
{
}

OrderQueue::~OrderQueue()
{
    cout << "~OrderQueue" << endl;
}

void
OrderQueue::start(int nworkers)
{
    for(int i = 0; i < nworkers; ++i)
    {
        TraderPtr trader = new Trader(_account, _logger);
        IceUtil::ThreadPtr t = new OrderThread(trader, _recvTrader, _logger, this);
        _workers.push_back(t);
        t->start();
    }
}

void
OrderQueue::add(const OrderWorkItemPtr& order)
{
    Lock sync(*this);
    _work.push_back(order);
    notify();
}

OrderWorkItemPtr
OrderQueue::get()
{
    Lock sync(*this);
    while(_work.empty() && !_destroy)
    {
        wait();
    }
    if(_destroy)
    {
        return 0;
    }

    OrderWorkItemPtr work = _work.front();
    _work.pop_front();
    return work;
}

void
OrderQueue::destroy()
{
    Lock sync(*this);
    _destroy = true;
    notifyAll();
}

void 
OrderQueue::cleanup()
{
    destroy();
    waitForJoin();
    {
        Lock sync(*this);
        _work.clear();
        _destroy = false;
    }
}

void
OrderQueue::waitForJoin()
{
    std::list<IceUtil::ThreadPtr> workers;
    {
        Lock sync(*this);
        workers = _workers;
        _workers.clear();
    }

    for(std::list<IceUtil::ThreadPtr>::const_iterator p = workers.begin(); p != workers.end(); ++p)
    {
        (*p)->getThreadControl().join();
    }
}

int 
OrderQueue::workCount()
{
    return _work.size();
}

int 
OrderQueue::workerCount()
{
    return _workers.size();
}


} /* BlackBox */
