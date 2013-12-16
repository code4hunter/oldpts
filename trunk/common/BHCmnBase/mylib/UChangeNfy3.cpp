//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UChangeNfy3.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TDirectoryThread::TDirectoryThread(HWND handle,UINT MsgID)
  : TThread(true)
{
  path = "";
  Hwnd=handle;
  FMsgID=MsgID;
  iFileHandle = -1;
  OnTerminate = ThreadFinish;
  FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
void __fastcall TDirectoryThread::Execute()
{
  if (path.IsEmpty())
  {
    throw Exception("couldn't start");
  }

  if(path[path.Length()] != '\\')
    path += "\\";

  String sFileName = path+ Date().CurrentDate().FormatString("yyyymmdd")+".txt";

  bool bOpened = false;
  unsigned int iOldSize = 0;
  unsigned int iNewSize = 0;
  while (!Terminated)
  {
    if(!FileExists(sFileName))
    {
      Sleep(1000);
      continue;
    }
    if(!bOpened)
    {
      iFileHandle = FileOpen(sFileName, fmOpenRead|fmShareDenyNone);
      bOpened = true;
    }
    
    iNewSize = FileSeek(iFileHandle, 0, 2);
    if(iOldSize != iNewSize)
    {
      iOldSize = iNewSize;
      SendMessage(Hwnd,FMsgID,0,0);
    }
    Sleep(100);
  }
}
//---------------------------------------------------------------------------

bool __fastcall TDirectoryThread::SetMonitorPath(String Path)
{
  if (path != Path)
  {
    path = Path;
  }

  return true;
}

//---------------------------------------------------------------------------

bool __fastcall TDirectoryThread::StopWatch(void)
{
  this->Suspend();
  return this->Suspended;
}

//---------------------------------------------------------------------------

bool __fastcall TDirectoryThread::StartWatch(void)
{
  this->Resume();
  return !this->Suspended;
}
//---------------------------------------------------------------------------

void __fastcall TDirectoryThread::ThreadFinish(TObject *Sender)
{
  if(iFileHandle != -1)
    FileClose(iFileHandle);
}

//---------------------------------------------------------------------------
