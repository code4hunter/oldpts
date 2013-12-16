#include <ReportSyncThread.h>
#include <OrderSyncServer.h>

using namespace IceUtil;

namespace PTS2
{

    ReportSyncThread::ReportSyncThread(const std::string& account, const TraderPtr& trader,
								   const Ice::CommunicatorPtr& communicator, const DatabasePtr& db):
    _account(account),
    _trader(trader),
    _communicator(communicator),
    _db(db)
{
    Ice::PropertiesPtr properties = _communicator->getProperties();    
    _startIndex = _db->getProperty(_account+"_RSStartIndex");
	_currDate = _db->getPropertyAsInt(_account+"_RSCurrDate");
    _maxCount = _db->getPropertyAsInt(_account+"_RSMaxCount");
    if (_maxCount <= 0)
    {
        _db->setLongProperty(_account+"_RSMaxCount", 100);
        _maxCount = 100;
    }

    _delay = _db->getPropertyAsInt(_account+"_RSDelay");
    if (_delay <= 0)
    {
        _db->setLongProperty(_account+"_RSDelay", 1000);
        _delay = 1000;
    }

    _filledCount = 0;

    //_trader = new Trader(account, _communicator->getLogger());
    _terminated = false;
}
    
void 
ReportSyncThread::run()
{
    long systemDate = _db->getInitializeDate();
    while (!_terminated)
    {
        SYSTEMTIME st;
        GetLocalTime(&st);	
        long time = st.wHour * 10000 + st.wMinute * 100 + st.wSecond;
        long date = st.wYear * 10000 + st.wMonth * 100 + st.wDay;

		if (date != _currDate)
		{
            systemDate = _db->getInitializeDate();
            if(date == systemDate)
            {
			    _startIndex = "";
                _filledCount = 0;
			    _currDate = date;
			    _db->setLongProperty(_account+"_RSCurrDate", _currDate);
			    _db->setProperty(_account+"_RSStartIndex", "");
            }
		}

		if( time>160000 )
		{
			getThreadControl().sleep(Time().milliSeconds(1000));
			continue;
		}

        std::string oldStartIndex = _startIndex;
        TradeInfoSeq tis = _trader->getTradeInfos(_startIndex, _maxCount);
        for (TradeInfoSeq::iterator p = tis.begin(); p != tis.end(); ++p)
        {
			try
			{
				_db->fillOrder(*p);
                _filledCount++;
			}
			catch (const FailureException&)
			{
				_pendingTrades.push_back(*p);
			}

            if(p->seqNum != "")
                _startIndex = p->seqNum;
        }
        
		TradeInfoSeq::iterator q = _pendingTrades.begin();
		while (q != _pendingTrades.end())
		{
			if (q->fillCount < 6)
			{
				try
				{
					_db->fillOrder(*q);
                    _filledCount++;
					q = _pendingTrades.erase(q);
				}
				catch (const FailureException&)
				{
					q->fillCount++;
					++q;
				}
			}
			else
			{
				//write to file
				FILE * pFile;
				pFile = fopen ("unfill.txt" , "a+");
				if (pFile == NULL) 
					printf("open file unfill.txt error");
				else
				{
					fprintf(pFile,"%d-%d,%s,%s,%0.3f,%d\n",(*q).tradeDate,(*q).transactTime,(*q).orderId.c_str(),
						(*q).instId.c_str(),(*q).price,(*q).volume);
					fclose (pFile);
				}
				q = _pendingTrades.erase(q);
			}
		}

        if(oldStartIndex != _startIndex)
		    _db->setProperty(_account+"_RSStartIndex", _startIndex);        

        getThreadControl().sleep(Time().milliSeconds(_delay));
    }
}

void 
ReportSyncThread::terminate()
{
    _terminated = true;
}

ReportSyncInfo 
ReportSyncThread::getReportSyncInfo()
{
    ReportSyncInfo info = {};
    info.delay = _delay;
    info.filledCount = _filledCount;
    info.maxCount = _maxCount;
    info.pendingCount = _pendingTrades.size() + _trader->getCancelOrders();
    info.seqNum = _startIndex;

    return info;
}

} /* PTS2 */