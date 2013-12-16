#include "UCotData.h"
//----------------------------------------------------------------------
__fastcall TCotData::TCotData()
{
  FAccRec     = new TList();
  FStockRec   = new TList();
  FCmsRec     = new TList();
  FBargainRec = new TList();

  SHContractID = 0;
  SZContractID = 0;
}
//----------------------------------------------------------------------
__fastcall TCotData::~TCotData()
{
  for(int i=0;i<FAccRec->Count;i++) { delete (TAccRec*)(FAccRec->Items[i]); }
  delete FAccRec;
  for(int i=0;i<FStockRec->Count;i++) { delete (TStockRec*)(FStockRec->Items[i]); }
  delete FStockRec;
  for(int i=0;i<FCmsRec->Count;i++) { delete (TCmsRec*)(FCmsRec->Items[i]); }
  delete FCmsRec;
  for(int i=0;i<FBargainRec->Count;i++) { delete (TBargainRec*)(FBargainRec->Items[i]); }
  delete FBargainRec;
}
//----------------------------------------------------------------------
TAccRec* __fastcall TCotData::FindAcc(String Capital)
{
  for(int i=0;i<FAccRec->Count;i++) {
    if(String(((TAccRec*)(FAccRec->Items[i]))->Capital)==Capital) {
      return (TAccRec*)(FAccRec->Items[i]);
    }
  }
  return NULL;
}
//----------------------------------------------------------------------
TStockRec* __fastcall TCotData::FindStock(String Capital,TBourse Bourse,String SecuID)
{
  TStockRec *stockRec;
  for(int i=0;i<FStockRec->Count;i++) {
    stockRec = (TStockRec*)(FStockRec->Items[i]);
    if(String(stockRec->Capital)==Capital && stockRec->Bourse==Bourse &&
      String(stockRec->SecuID)==SecuID) {
      return stockRec;
    }
  }
  return NULL;
}
//----------------------------------------------------------------------
TCmsRec* __fastcall TCotData::FindCms(String Date,TBourse Bourse,String ContractID)
{
  TCmsRec *cmsRec;

  for(int i=0;i<FCmsRec->Count;i++) {
    cmsRec = (TCmsRec*)(FCmsRec->Items[i]);
    if(String(cmsRec->Date)==Date && cmsRec->Bourse==Bourse &&
      String(cmsRec->ContractID)==ContractID) {
      return cmsRec;
    }
  }
  return NULL;
}
//----------------------------------------------------------------------
TBargainRec* __fastcall TCotData::FindBargain(String Date,TBourse Bourse,String ContractID)
{
  TBargainRec *bargainRec;

  for(int i=0;i<FBargainRec->Count;i++) {
    bargainRec = (TBargainRec*)(FBargainRec->Items[i]);
    if(String(bargainRec->Date)==Date && bargainRec->Bourse==Bourse &&
      String(bargainRec->ContractID)==ContractID) {
      return bargainRec;
    }
  }
  return NULL;
}
//---------------- debug ----------------------------------------------- 