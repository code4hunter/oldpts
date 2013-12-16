//---------------------------------------------------------------------------

#ifndef OrderKeeperH
#define OrderKeeperH

#include "UTrdItf_HSFF.h"
#include "TradeGateway.h"
#include "UTrdItfBase.h"
#include "UTrdStruct_Rm.h"
#include "DebugStr.h"
#include "uDatabase.h"

#include <string>
#include <map>
#include <list>
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
	bool _is_panding_qry_money;
	TMoneyInfo _money_ans;

	boost::mutex _mtorderlist;
	std::list<std::string> _orderlist;

	void get_orders(std::list<std::string> &list)
	{
		boost::mutex::scoped_lock lock(_mtorderlist);
		if( _orderlist.size() >0 )
		{
			list.assign(_orderlist.begin(),_orderlist.end());
			_orderlist.clear() ;
		}
	}

	void qry_orders(TTrdItfBase *itf);

	void qry_orders(TTrdItfBase *itf,TradeGateway::OrderReportSeq &ors);

public:

	order_keeper()
	{
		_is_working = false;
		memset(&_account,0,sizeof(_account));
		_ref_count = 1;
		_is_panding_qry_money = true;
		_money_ans.MoneyType = motNo;
		_money_ans.balance = 0;
		_money_ans.available = 0;
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

	void add_order(const std::string &ordid)
	{
		boost::mutex::scoped_lock lock(_mtorderlist);
		_orderlist.push_back(ordid);
	}

	void pendingQryMoney(void)
	{
    	_is_panding_qry_money = true;
	}

	void get_last_money( TMoneyInfo &ans)
	{
		memcpy(&ans,&_money_ans,sizeof(TMoneyInfo));
		pendingQryMoney();
    }
};

typedef boost::shared_ptr<order_keeper> ORDERKEEPERPTR;

// order_keeper_manager
class order_keeper_manager
{
public:
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

	ORDERKEEPERPTR start_keeper(const char *psetupfile,ADDLOG plogfunc, const TSetAccount_Req *req )
	{
		std::string key = req->Account;
		key = key + req->PW;

		boost::mutex::scoped_lock lock(_map_mutex);
		KEEPERS::iterator iter = _keepers.find(key);
		if( iter == _keepers.end() )
		{
			ORDERKEEPERPTR keeper = ORDERKEEPERPTR(new order_keeper);
			keeper->start(psetupfile,plogfunc,req);
			_keepers.insert(KEEPERSPAIR(key,keeper));
			return keeper;
		}
		else
		{
			iter->second->addRef();
			return iter->second;
		}
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
