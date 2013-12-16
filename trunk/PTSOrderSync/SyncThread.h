#ifndef SYNCTHREAD_H_OYOCDCGI
#define SYNCTHREAD_H_OYOCDCGI

#include <OrderQueue.h>

namespace PTS2
{
    
struct SyncInfo
{
	long acceptCount;
	long rejectCount;
    long workCount;
    long errorCount;
    long workerCount;
};

class SyncThread : public IceUtil::Thread
{
public:

    SyncThread(std::map<std::string, OrderQueuePtr>&, const Ice::CommunicatorPtr&, const DatabasePtr&);
    
    virtual void run();
    void terminate();
    SyncInfo getSyncInfo(std::string account);
    int getStartIndex() { return _startIndex; }
    int getCurrDate() { return _currDate; }

private:
    bool _terminated;
	int _startIndex;
	int _delay;
	int _currDate;
    const Ice::CommunicatorPtr _communicator;
    const DatabasePtr _db;
    const Ice::LoggerPtr _logger;
    std::map<std::string, OrderQueuePtr> _queueMap;
    std::map<std::string, SyncInfo> _syncInfos;
};
typedef IceUtil::Handle<SyncThread> SyncThreadPtr;

} /* PTS2 */

#endif /* end of include guard: SYNCTHREAD_H_OYOCDCGI */
