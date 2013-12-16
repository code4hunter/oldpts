#include <windows.h>

#include "stock_trd.h"

static DWORD WINAPI thread_proc( stock_trd * pthis )
{
  return pthis->check_deal_thread();
}

stock_trd::stock_trd(bool simulation,void  * ei)
	:TItfTrd(simulation,ei)
{
}

stock_trd::~stock_trd(void)
{

}

DWORD stock_trd::check_deal_thread(void)
{
	return 0;
}

int stock_trd::buy(char * code,int num,float price,char * order_id)
{
	return 0;
}

int stock_trd::sell(char * code,int num,float price,char * order_id)
{
	return 0;
}

int stock_trd::withdraw(char * order_id)
{
	return 0;
}