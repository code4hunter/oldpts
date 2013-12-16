#ifndef stock_trd_h
#define stock_trd_h

/*
** @file stock_trd.h
** 股票交易
** 成交等消息自动相应
** @author codehunter <codehunter@bohongfund.com>
*/

#include <list>

#include "stock_rec.h"
#include "uitftrd.h"

using namespace std ;

typedef list<stock_trade> stock_list;

class stock_trd : private TItfTrd
{
private:
	
protected:
	stock_list m_stocks;
public:
	stock_trd(bool simulation=false,void  * ei=NULL);
	virtual ~stock_trd(void);

	virtual void on_order(const stock_trade *st)
	{
	}

	virtual void on_deal(const stock_trade *st,int deal_num,float deal_price)
	{
	}

	virtual void on_complete(const stock_trade *st)
	{
	}

	virtual void on_error(const stock_trade *st,int err_code)
	{
	}

	virtual DWORD check_deal_thread(void);

	int buy(char * code,int num,float price,char * order_id);
	int sell(char * code,int num,float price,char * order_id);
	int withdraw(char * order_id);
};

#endif