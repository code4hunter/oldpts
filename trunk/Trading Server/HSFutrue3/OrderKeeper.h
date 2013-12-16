//---------------------------------------------------------------------------

#ifndef OrderKeeperH
#define OrderKeeperH

#include "UTrdItf_HSFF.h"
#include "TradeGateway.h"
#include "UTrdItfBase.h"
#include "UTrdStruct_Rm.h"
#include "DebugStr.h"
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
public:

	order_keeper()
	{
		_is_working = false;
		memset(&_account,0,sizeof(_account));
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
	}

	void stop(void)
	{
		if( _is_working == true )
		{
			_is_working = false;
			if( _thread != 0 )
			{
				_thread->join();
			}
		}
    }

	void execute(const TSetAccount_Req *)
	{
		std::cout << "->Thread Started:" << &_thread->get_id() << std::endl;

        TTrdItfBase *itf = new TTrdItf_HSFF( _setup_file.c_str(), _plogfunc);

        TRequest req;
        TAnswer *ans=NULL;
		int count = 0;

        bool bneedInit = true;
        DWORD oldtick1 = ::GetTickCount();
        DWORD oldtick2 = ::GetTickCount();
        DWORD oldtick3 = ::GetTickCount();

        try
        {

            while( _is_working )
            {
                //
                if( bneedInit )
                {
                    // init and setaccount
                    req.QryCurCsn.ReqHead.FuncType = ftInit;
                    if( itf->Request(req,&ans,count) != 0 )
                    {
                        ODS("->初始化接口失败");
                    }

                    req.QryCurCsn.ReqHead.FuncType = ftSetAccount;
                    memcpy(&req.SetAccount, &_account, sizeof(TSetAccount_Req));
                    if( itf->Request(req,&ans,count) != 0 )
                    {
                        ODS("->登陆柜台失败");
                    }
                }
                else
                {
                    //查询资金如果失败就重新连接
                    if( (::GetTickCount() - oldtick1)>=10000 )
                    {
                        //qry money
                        req.QryCurCsn.ReqHead.FuncType = ftQryMoney;
                        if( itf->Request(req,&ans,count) != 0 )
                        {
                            ODS("->查询资金失败");
                            bneedInit = true;
                        }

                        oldtick1 =  ::GetTickCount();
                    }

                    //每隔30秒
                    if( (::GetTickCount() - oldtick2)>=30000 )
                    {
                        //load working order from db

                        //Qry working order
                        oldtick2 =  ::GetTickCount();
                    }

                    //不断取需要查撤单的委托


                    //获得未成交的委托数量，如果>0则查成交
                }
                std::cout << &_thread->get_id() << ":" <<_account.Account << std::endl;
                Sleep(500);
            }
        }
        __finally
        {
		    std::cout << "->Thread Stopped:" << &_thread->get_id() << std::endl;
            delete itf;
        }
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
    }

	void clear(void)
	{
		boost::mutex::scoped_lock lock(_map_mutex);
		_keepers.clear();
	}
};


#endif
