//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdCot_DD.h"
//---------------------------------------------------------------------------
__fastcall TTrdCot_DD::TTrdCot_DD(TTrdItf_DD::TDDSet * ds) : TTrdCot()
{
  FTrdItf = new TTrdItf_DD(*ds);
}
//---------------------------------------------------------------------------
__fastcall TTrdCot_DD::~TTrdCot_DD()
{
  delete FTrdItf;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot_DD::Request(TRequest Request,TAnswer **Answer,int &AnsCount)
{
  return FTrdItf->Request(Request,Answer,AnsCount);
}
