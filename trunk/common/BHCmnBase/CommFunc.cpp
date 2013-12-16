//---------------------------------------------------------------------------


#pragma hdrstop

#include "CommFunc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

float FixPrice(int price)
{
    float fprice = price / 1000.0;
    int nPrice = (int)(fprice * 10000 + 5.0)/ 10 * 10;
    return (float)nPrice / 10000.0;
}
