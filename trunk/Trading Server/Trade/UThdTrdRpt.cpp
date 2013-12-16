//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UThdTrdRpt.h"
#include "UTrdStruct.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TThdTrdRpt::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TThdTrdRpt::TThdTrdRpt(bool CreateSuspended,TItfTrd *ItfTrd)
  : TThread(CreateSuspended)
{
  FreeOnTerminate = true;
  FItfTrd         = new TItfTrd();
  FItfTrd->Init("","");
  TAccountInfo accInfo;
  ItfTrd->GetAccInfo(&accInfo);
  FItfTrd->SetAccInfo(&accInfo);

  FMutex=CreateSemaphore(NULL,1,1,"mutex_ThdTrdRpt");
}
//---------------------------------------------------------------------------
void __fastcall TThdTrdRpt::Execute()
{
  CoInitialize(NULL);

  int        infoCount = 0;

  memset(FTradeInfo,0,5000*sizeof(TTradeInfo));

  for(;;) {
    if(Terminated) { break; }
    WaitForSingleObject(FMutex,INFINITE);

    TTradeInfo *trdInfo;
    int        num;

    FItfTrd->QryCurTrd(&trdInfo,num);

    for(int i=0;i<num;i++) {
      bool addRec = true;

      for(int j=0;j<infoCount;j++) {
        if(memcmp(&trdInfo[i],&FTradeInfo[j],sizeof(TTradeInfo))==0) { addRec = false;  break; }
      }

      if(addRec) {
        memcpy(&FTradeInfo[infoCount],&trdInfo[i],sizeof(TTradeInfo));
        infoCount++;

        FTrdInfo = trdInfo[i];
        Synchronize(TrdReport);
      }
    }

    delete []trdInfo;

    ReleaseSemaphore(FMutex,1,NULL);

    Sleep(15000);
    /*for(int i=0;i<500000;i++) {
      Application->ProcessMessages();
    } */
  }

  ExitExecute:
  CoInitialize(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TThdTrdRpt::TrdReport()
{
  TRjlSysVar()()->AddTrdRep(NULL,FTrdInfo.Time,FTrdInfo.Type=='B'?true:false,"H"+String(FTrdInfo.SecuID),
    FTrdInfo.Vol,FTrdInfo.Price);
}
//---------------------------------------------------------------------------
void __fastcall TThdTrdRpt::ChangeAccount(TItfTrd *ItfTrd)
{
  WaitForSingleObject(FMutex,INFINITE);                             //等待被接收进程唤醒

  TAccountInfo accInfo;
  ItfTrd->GetAccInfo(&accInfo);
  FItfTrd->SetAccInfo(&accInfo);

  memset(FTradeInfo,0,5000*sizeof(TTradeInfo));

  ReleaseSemaphore(FMutex,1,NULL);
}
//---------------------------------------------------------------------------
 
