//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdCot_HS.h"
//---------------------------------------------------------------------------
__fastcall TTrdCot_HS::TTrdCot_HS(TTrdItf_HS::THSSet * hs) : TTrdCot()
{
  FTrdItf = new TTrdItf_HS(hs);
}
//---------------------------------------------------------------------------
__fastcall TTrdCot_HS::~TTrdCot_HS()
{
  delete FTrdItf;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot_HS::Request(TRequest Request,TAnswer **Answer,int &AnsCount)
{
  return FTrdItf->Request(Request,Answer,AnsCount);
}
