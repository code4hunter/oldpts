//---------------------------------------------------------------------------
#include "UTrdCot_JSD.h"
//---------------------------------------------------------------------------
__fastcall TTrdCot_JSD::TTrdCot_JSD(TTrdItf_JSD::TJSDSet *js) : TTrdCot()
{
  FTrdItf = new TTrdItf_JSD(js);
}
//---------------------------------------------------------------------------
__fastcall TTrdCot_JSD::~TTrdCot_JSD()
{
  delete FTrdItf;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot_JSD::Request(TRequest Request,TAnswer **Answer,int &AnsCount)
{
  return FTrdItf->Request(Request,Answer,AnsCount);
}
//---------------------------------------------------------------------------
