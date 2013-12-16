//---------------------------------------------------------------------------

#ifndef OrderKeeperH
#define OrderKeeperH

#include "UTrdItf_GTJA.h"
#include "TradeGateway.h"
#include "UTrdItfBase.h"
#include "UTrdStruct_Rm.h"
#include "DebugStr.h"
#include "uDatabase.h"
#include <string>
#include <map>
#include <iostream>
#include <boost\thread\mutex.hpp>
#include <boost\shared_ptr.hpp>
#include <boost\scoped_ptr.hpp>
#include <boost\thread\thread.hpp>
#include <boost\bind.hpp>

//---------------------------------------------------------------------------

// order_keeper
class order_keeper
{
typedef  boost::scoped_ptr< boost::thread > THREADPTR;

private:
	bool _is_working;
	TSetAccount_Req _account;
	THREADPTR _thread;
    std::string _setup_file;
    ADDLOG _plogfunc;
    int _ref_count;
public:

	order_keeper()
	{
		_is_working = false;
		memset(&_account,0,sizeof(_account));
        _ref_count = 1;
	}

	~order_keeper()
	{
		stop();
	}

	void start(const char *psetupfile,ADDLOG plogfunc,const TSetAccount_Req *req)
	{
        _setup_file = psetupfile;
        _plogfunc =  plogfunc;
		_is_working = true;
		memcpy(&_account,req,sizeof(TSetAccount_Req));
		_thread.reset(new boost::thread(boost::bind(&order_keeper::execute,this,&_account)));
        //addRef();
	}

	void stop(void)
	{
		if( _is_working == true )
		{
			_is_working = false;
			if( _thread != 0 )
			{
                if( _thread->joinable() )
                {
                    while( _ref_count != 0 )
                    {
                        Sleep(200);
                    }
                }
			}
		}
    }

    void qry_orders(TTrdItfBase *itf,TradeGateway::OrderReportSeq &ors);

	void execute(const TSetAccount_Req *);

    void addRef(void)
    {
        //_ref_count++;
    }

    void release(void)
    {
        //_ref_count--;
        //if( _ref_count == 0)
        //{
        //    stop();
        //}
    }

};

// order_keeper_manager
class order_keeper_manager
{

typedef boost::shared_ptr<order_keeper> ORDERKEEPERPTR;
typedef std::map<std::string, ORDERKEEPERPTR> KEEPERS;
typedef std::pair<std::string, ORDERKEEPERPTR> KEEPERSPAIR;
typedef boost::shared_ptr<order_keeper_manager> KEEPERMANAGERPTR;

private:
	KEEPERS _keepers;
	static KEEPERMANAGERPTR _instance;
	static boost::mutex _map_mutex;
public:
	order_keeper_manager()
	{
		std::cout << "order_keeper_manager"  << std::endl;
	}

	static KEEPERMANAGERPTR &instance(void)
	{
		return _instance;
    }

	void start_keeper(const char *psetupfile,ADDLOG plogfunc, const TSetAccount_Req *req )
	{
		std::string key = req->Account;
		key = key + req->PW;

		boost::mutex::scoped_lock lock(_map_mutex);
		KEEPERS::iterator iter = _keepers.find(key);
		if( iter == _keepers.end() )
		{
			ORDERKEEPERPTR &keeper = ORDERKEEPERPTR(new order_keeper);
			keeper->start(psetupfile,plogfunc,req);
			_keepers.insert(KEEPERSPAIR(key,keeper));
		}
        else
            iter->second->addRef();
    }

    void stop_keeper(const TSetAccount_Req *req)
    {
        std::string key = req->Account;
		key = key + req->PW;

		boost::mutex::scoped_lock lock(_map_mutex);
		KEEPERS::iterator iter = _keepers.find(key);
		if( iter != _keepers.end() )
		{
            iter->second->release();
        }
    }

	void clear(void)
	{
		boost::mutex::scoped_lock lock(_map_mutex);
		_keepers.clear();
	}
};


#endif
