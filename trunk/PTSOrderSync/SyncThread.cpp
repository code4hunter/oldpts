#include <SyncThread.h>

using namespace IceUtil;

namespace PTS2
{

SyncThread::SyncThread(std::map<std::string, OrderQueuePtr>& queueMap, const Ice::CommunicatorPtr& communicator, const DatabasePtr& db):
    _queueMap(queueMap),
    _communicator(communicator),
    _logger(communicator->getLogger()),
    _db(db)
{
	_startIndex = _db->getPropertyAsInt("OSStartIndex");
	_currDate = _db->getPropertyAsInt("OSCurrDate");
    _delay = _db->getPropertyAsInt("OSDelay");
    if (_delay <= 0)
    {
        _db->setLongProperty("OSDelay", 500);
        _delay = 500;
    }
/*
    for (AccountInfoSeq::const_iterator p = accounts.begin(); p != accounts.end(); ++p)
    {
        int workerCount = _db->getPropertyAsInt(p->account + "_wrokerCount");
        if (workerCount <= 0)
        {
            _db->setLongProperty(p->account + "_wrokerCount", 1);
            workerCount = 1;
        }

        OrderQueuePtr queue = new OrderQueue(*p, _communicator->getLogger());
        queue->start(workerCount);
        _queueMap[p->account] = queue;
    }     
*/
    _terminated = false;    
}
    
void SyncThread::run()
{
    bool first = true;
    Time nowTime = Time::now();

	long systemDate = _db->getInitializeDate();

    while (!_terminated)
    {
        SYSTEMTIME st;
        GetLocalTime(&st);	
        long time = st.wHour * 10000 + st.wMinute * 100 + st.wSecond;
        long date = st.wYear * 10000 + st.wMonth * 100 + st.wDay;

		// ·ÀÖ¹ÖØ¸´±¨ÅÌ
		if (date != _currDate)
		{
			systemDate = _db->getInitializeDate();
			if (date == systemDate)
			{
				_startIndex = 0;
				_currDate = date;
                _syncInfos.clear();
				_db->setLongProperty("OSCurrDate", _currDate);
				_db->setLongProperty("OSStartIndex", 0);
			}
		}

        int oldStartIndex = _startIndex;
        OrderInfoSeq orders = _db->getOrders(_currDate, _startIndex);

        for (OrderInfoSeq::iterator p = orders.begin(); p != orders.end(); p++)
        {	
			if (p->date == _currDate)
			{
				OrderWorkItemPtr item = new OrderWorkItem(*p, _db, _logger);
				
                std::map<std::string, OrderQueuePtr>::iterator q = _queueMap.find(p->account);
                if (q != _queueMap.end()) 
                {
                    q->second->add(item);
                }

                {
                    std::map<std::string, SyncInfo>::iterator q = _syncInfos.find(p->account);
                    if (q != _syncInfos.end())
                    {
                        q->second.acceptCount++;
                    }
                    else
                    {
                        SyncInfo info = {};
                        info.acceptCount++;
                        _syncInfos[p->account] = info;
                    }
                }
			}
			else
			{
                std::map<std::string, SyncInfo>::iterator q = _syncInfos.find(p->account);
                if (q != _syncInfos.end())
                {
                    q->second.rejectCount++;
                }
                else
                {
                    SyncInfo info = {};
                    info.rejectCount++;
                    _syncInfos[p->account] = info;
                }
			}

			_startIndex = p->seqno;
        }

        if(oldStartIndex != _startIndex)
		    _db->setLongProperty("OSStartIndex", _startIndex);

        getThreadControl().sleep(Time().milliSeconds(_delay));
    }   
}

void SyncThread::terminate()
{
    _terminated = true;

    std::map<std::string, OrderQueuePtr>::iterator q = _queueMap.begin();
    while (q != _queueMap.end()) 
    {
        q->second->destroy();
        q->second->waitForJoin();
        q++;
    }
}

SyncInfo 
SyncThread::getSyncInfo(std::string account)
{
    SyncInfo info = {};
    std::map<std::string, SyncInfo>::iterator q = _syncInfos.find(account);
    if (q != _syncInfos.end())
    {
        info = q->second;
    }

    std::map<std::string, OrderQueuePtr>::iterator p = _queueMap.find(account);
    if (p != _queueMap.end())
    {
        info.workCount = p->second->workCount();
        info.workerCount = p->second->workerCount();
    }

    return info;
}

}