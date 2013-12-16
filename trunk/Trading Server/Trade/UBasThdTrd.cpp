//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UBasThdTrd.h"
#include "..\URjlFuncX.h"
#include "..\URjlSysVar.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TBasThdTrd::TBasThdTrd(bool CreateSuspended) : TThread(CreateSuspended)
{
  FItfTrdLst  = new TList();
  FLocalDtl   = new TList();
}
//---------------------------------------------------------------------------
__fastcall TBasThdTrd::~TBasThdTrd()
{
  for(int i=0;i<FLocalDtl->Count;i++)
    DeleteTrd(i);
  delete FLocalDtl;

  for(int i=0;i<FItfTrdLst->Count;i++)
    delete (TItfTrd *)(FItfTrdLst->Items[i]);
  delete FItfTrdLst;
}
//---------------------------------------------------------------------------
void __fastcall TBasThdTrd::Execute()
{
}
//---------------------------------------------------------------------------
void __fastcall TBasThdTrd::ShowErr()
{
  TRjlFunc::AddMsgLst(FErrMsg,hcWarning);
}
//---------------------------------------------------------------------------
void __fastcall TBasThdTrd::TrdRep()
{
  TRjlSysVar()()->AddTrdRep(TRjlSysVar()()->PnlTrdRep,FRepTime,FRepBuy,FRepSecuID,FRepVol,FRepPrice);
}
//---------------------------------------------------------------------------
int __fastcall TBasThdTrd::FindInLocal(String SecuID,String PtfName,TAccountInfo  AccountInfo)
{
  int retVal = -1;
  TAccountInfo *AccInfo;
  for(int i=0;i<FLocalDtl->Count;i++){
    TLocalDtl *l  = ((TLocalDtl*)FLocalDtl->Items[i]);
    TItfTrd   *it = (TItfTrd *)(FItfTrdLst->Items[l->ItfTrdPos]);
    if(it->GetAccInfo(AccInfo)<0) continue;
    if(l->SecuID == SecuID && l->PtfName == PtfName && memcmp(AccountInfo.Capital,AccInfo->Capital,12)==0){
      retVal = i;
      break;
    }
    else continue;
  }

  return retVal;
}
//---------------------------------------------------------------------------
int __fastcall TBasThdTrd::FindInLocal(TList *In,TQueItf *QueItf)
{
  int retVal = -1;
  int locate = -1;
  TAccountInfo *AccInfo;

  for(int i=0;i<In->Count;i++){
    TQueItf *q = (TQueItf*)(In->Items[i]);
    if(q==NULL || q != QueItf) continue;
    locate = i;
    break;
  }

  if(locate<0) return -1;

  for(int i=0;i<FLocalDtl->Count;i++){
    TLocalDtl *l  = ((TLocalDtl*)FLocalDtl->Items[i]);
    if(l->Locate == locate){
      retVal = i;
      break;
    }
  }

  return retVal;
}
//---------------------------------------------------------------------------
int __fastcall TBasThdTrd::FindItfTrd(TAccountInfo  AccountInfo)
{
  int           retVal = -1;
  TAccountInfo  AccInfo;

  for(int i=0;i<FItfTrdLst->Count;i++){
    TItfTrd   *it = (TItfTrd *)(FItfTrdLst->Items[i]);
    it->GetAccInfo(&AccInfo);
    if(memcmp(AccountInfo.Capital,AccInfo.Capital,12)==0) {retVal = i;break;}
  }

  return retVal;
}
//---------------------------------------------------------------------------
int __fastcall TBasThdTrd::UndoAllTrd(TLocalDtl *l)
{
  double  p;
  int     n=0,un=0;
  TBourse bourse;
  String  ContractID;
  long    Num;
  TItfTrd *it = (TItfTrd *)(FItfTrdLst->Items[l->ItfTrdPos]);

  if(l->SecuID.SubString(1,1).UpperCase() == "S") bourse = bsSZ;
  else                                            bourse = bsSH;
  
  for(int j=0;j<l->TrdInfo->Count;j++){
    ContractID = ((TTrdInfo *)(l->TrdInfo->Items[j]))->ContractID;
    Num        = ((TTrdInfo *)(l->TrdInfo->Items[j]))->Num;

    if(it->QryDetail(ContractID,bourse,p,n,un)<-1) {          //成交查询
      continue;
    }
    if(n+un>=Num) continue;
    if(it->Undo(ContractID,bourse)<-1) {
      FErrMsg = "成交完成后撤单未成功,合同号：" + ContractID;
      Synchronize(ShowErr);
    }
  }

  return 0;
}
//---------------------------------------------------------------------------
