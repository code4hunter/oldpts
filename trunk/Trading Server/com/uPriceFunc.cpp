//---------------------------------------------------------------------------


#pragma hdrstop

#include "uPriceFunc.h"
#include <math.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString ConvetDoubleToPrice(double price,int precision)
{
	long lp = (long)(price * std::pow(10.0,precision+1));
	if( lp % 10 >=5 )
	lp = lp/10 + 1;
	else
	lp = lp/10;

	AnsiString s;
	long dx = pow(10.0,precision);
	AnsiString fmt;
	if( precision>0 )
	{
		fmt.printf("%%d.%%0%dd",precision);
		s.printf(fmt.c_str(),lp/dx,lp%dx);
	}
	else
	{
		s.printf("%d",lp/dx);
    }

	return s;
}