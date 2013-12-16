//---------------------------------------------------------------------------

#ifndef uAtuoQryH
#define uAtuoQryH

#include "UTrdStruct.h"
#include "uDmPTSRF.h"
#include "UItfTrd1.0.h"
#include <SyncObjs.hpp>

#include <list>
using namespace std;

//---------------------------------------------------------------------------
class query_orders
{
private:
	TDataModule1 *m_dm;
	PTRDDLL1::TItfTrd1 * m_itf;
	TCriticalSection *m_cs;
	list<_ord_> m_orders;

	void lock(void)
	{
		m_cs->Enter();
	}

	void unlock(void)
	{
    m_cs->Leave();
  }
protected:

public:
	query_orders()
	{
    m_dm = NULL;
		m_itf= NULL;
		m_cs = new TCriticalSection();
	}

	void set_param(PTRDDLL1::TItfTrd1 *pitf,TDataModule1 * pdm,String &acc)
	{
		lock();
		m_orders.clear();
		m_dm = pdm;
		m_itf= pitf;
		unlock();

		_ord_ *poi=NULL;
		int ordnum = 0;
		m_dm->GetUnfilledOrders(acc,&poi,ordnum);
		if( ordnum > 0 )
		{
			assert(poi!= NULL );
			lock();
			for(int i=0;i<ordnum;i++)
			{
				m_orders.push_back(poi[i]);
			}
			unlock();
			delete[] poi;
    }
	}

	~query_orders()
	{
		delete m_cs;
	}

	void add_order( TOrderInfo &OrdInfo ,__int64 ordrepid )
	{
		_ord_ ord;
		ord.ordrepid = ordrepid;
		memcpy(&ord.oi,&OrdInfo,sizeof(TOrderInfo));
		lock();
		m_orders.push_back(ord);
		unlock();
	}

	void do_query( void );

	String get_exec_id(void)
	{
		return Now().FormatString("yyyymmddhhnnss.") + IntToStr(GetTickCount());
	}
};

#endif
