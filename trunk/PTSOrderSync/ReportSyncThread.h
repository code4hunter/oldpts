#ifndef REPORTSYNCTHREAD_H_GNT65BP5
#define REPORTSYNCTHREAD_H_GNT65BP5

#include <Trader.h>

namespace PTS2
{

struct ReportSyncInfo
{
    std::string seqNum;
    int maxCount;
    int delay;
    int filledCount;
    int pendingCount;
};

class ReportSyncThread : public IceUtil::Thread
{
public:

    ReportSyncThread(const std::string& account, const TraderPtr& trader, const Ice::CommunicatorPtr&, const DatabasePtr&);
    
    virtual void run();
    void terminate();

    ReportSyncInfo getReportSyncInfo();

private:
    bool _terminated;
	std::string _startIndex;
	std::string _account;
	int _currDate;
	int _maxCount;
	int _delay;
    int _filledCount;
    const Ice::CommunicatorPtr _communicator;
    const DatabasePtr _db;
    const Ice::LoggerPtr _logger;
    TraderPtr _trader;
    TradeInfoSeq _pendingTrades;

};
typedef IceUtil::Handle<ReportSyncThread> ReportSyncThreadPtr;

} /* PTS2 */

#endif /* end of include guard: REPORTSYNCTHREAD_H_GNT65BP5 */
