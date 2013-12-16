#ifndef orderManageH
#define orderManageH

#include "TradeGateway.h"
#include "UTrdItfBase.h"
#include "UTrdStruct_Rm.h"
#include <string>
#include <list>
#include <map>
#include <boost\thread\mutex.hpp>
#include <boost\shared_ptr.hpp>
#include <boost\scoped_ptr.hpp>
#include <boost\thread\thread.hpp>
#include <boost\bind.hpp>

typedef std::list<TradeGateway::OrderReport> ORDERS;
typedef std::list<TradeGateway::OrderReport>::iterator ORDER_ITERATOR;

class order_manager
{
private:
	ORDERS FOrders;
	boost::mutex _mutex;
	std::string _userid;

	static std::map<std::string,int> userid_list;
	static boost::mutex _map_mutex;
public:
	static bool add_user( const std::string &userid )
	{
		boost::mutex::scoped_lock lock(_map_mutex);
		if( userid_list.count(userid)>0 )
			return false;
		else
		{
			userid_list[userid] = 1;
            ODS("add_user,%s",userid.c_str());
			return true;
        }
	}

	static void remove_user( const std::string &userid )
	{
		boost::mutex::scoped_lock lock(_map_mutex);
		userid_list.erase(userid);
        ODS("remove_user,%s",userid.c_str());
    }

	void load_working_orders(const std::string &userid);
	void qry_orders(TTrdItfBase *itf);
	void add_order(const TradeGateway::OrderReport &op)
	{
		boost::mutex::scoped_lock lock(_mutex);
        FOrders.push_back(op);
    }

	order_manager()
	{

	}

	~order_manager()
	{
		clear_all();
	}

	void clear_all()
	{
		boost::mutex::scoped_lock lock(_mutex);
		FOrders.clear();
        if( _userid.length() >0 )
        {
		    remove_user(_userid);
	    	_userid = "";
        }
    }
};



#endif