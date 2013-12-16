//---------------------------------------------------------------------------


#pragma hdrstop

#include "DebugStr.h"
#include "uAtuoQry.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


void query_orders::do_query( void )
{
	if( m_dm == NULL || m_itf== NULL ) return;
	list<_ord_>::iterator ite;

	lock();

	try
	{
		for (ite = m_orders.begin(); ite != m_orders.end(); ite++)
		{
			if( ite->oi.CsnVol == ite->oi.TrdVol + abs(ite->oi.CancelVol) )
			{
				m_orders.erase(ite);
			}
			else
			{
				PTRDDLL1::TBourse b;
				if( ite->oi.Market ==   mtSHA )
				{
					b = PTRDDLL1::bsSH ;
				}
				else if( ite->oi.Market == mtSZA)
				{
					b = PTRDDLL1::bsSZ ;
				}
				else if( ite->oi.Market == mtJJS )
				{
					b = PTRDDLL1::bsJJS ;
				}

				double price=0;
				int num=0;
				int undonum = 0;
				if( this->m_itf->QryDetail(ite->oi.ContractID,b,price,num,undonum) == 0 )
				{
					if( num >0 )
					{
						if( num ==  ite->oi.TrdVol)
						{
							if( abs(undonum) > 0 )
							{
								m_dm->AddOrderReport(ite->ordrepid,ite->oi.SecuID,get_exec_id(),undonum,0);
							}
						}
						else if( num > ite->oi.TrdVol )
						{
							long detnum = num-ite->oi.TrdVol;
							double detprice = ( (num * price) - (ite->oi.TrdPrice* ite->oi.TrdVol) )/ detnum;
							m_dm->AddOrderReport(ite->ordrepid,ite->oi.SecuID,get_exec_id(),detnum,detprice);
						}
						else
						{
							ODS('E',"PtrdTrdSvr","TrdVol > QryDetail(num),%d>%d",ite->oi.TrdVol,num);
						}
					}

					ite->oi.TrdVol = num;
					ite->oi.TrdPrice = price;
					ite->oi.CancelVol = undonum;
				}
			}
		}
	}
	catch( Exception  &e)
	{
		ODS('E',"PtrdTrdSvr","do_query error,%s",e.Message.c_str());
	}
	catch(...)
	{
  	ODS('E',"PtrdTrdSvr","do_query error,unknown error");
  }

	unlock();
}
