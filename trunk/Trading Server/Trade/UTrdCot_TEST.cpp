//---------------------------------------------------------------------------
#include "UTrdCot_TEST.h"
#include "JZAPI.H"
//---------------------------------------------------------------------------
__fastcall TTrdCot_TEST::TTrdCot_TEST() : TTrdCot()
{
  FTrdItf = new TTrdItf_TEST();
}
//---------------------------------------------------------------------------
__fastcall TTrdCot_TEST::~TTrdCot_TEST()
{
  delete FTrdItf;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot_TEST::Request(TRequest Request,TAnswer **Answer,int &AnsCount)
{
  return FTrdItf->Request(Request,Answer,AnsCount);
}
//---------------------------------------------------------------------------
