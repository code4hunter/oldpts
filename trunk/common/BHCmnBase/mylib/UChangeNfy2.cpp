//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UChangeNfy2.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TDirectoryThread::TDirectoryThread(HWND handle,UINT MsgID)
  : TThread(true)
{
  path = "";
  Hwnd=handle;
  FMsgID=MsgID;
  FreeOnTerminate = true;
  OnTerminate = ThreadFinish;
  hNotify = INVALID_HANDLE_VALUE;
}
//---------------------------------------------------------------------------
void __fastcall TDirectoryThread::Execute()
{
  if (path.IsEmpty() || (hNotify == INVALID_HANDLE_VALUE))
  {
    throw Exception("couldn't start");
  }
  bool to=true;  //time-out check
  //while we're still going...
  while (!Terminated && (hNotify != INVALID_HANDLE_VALUE))
  {
    //while we're still timed out...
    while (to && !Suspended && !Terminated)
    {
      unsigned long stat = WaitForSingleObject(hNotify,2000);
      //our call to WaitForSingleObject has a 2 second timeout to avoid thread-lock
      if (stat == WAIT_OBJECT_0) //if it got signalled
      {
        to=true;
        Update();
        if (!FindNextChangeNotification(hNotify)) //renew the handle
        {
          to=false;
          break;
        }
      }
      else if (stat == WAIT_TIMEOUT)      //just keep going
        to=true;
      else
      {
        to=false;
        break;
      }
    }
  }
}
//---------------------------------------------------------------------------
bool __fastcall TDirectoryThread::SetMonitorPath(String Path)
{
  if (path != Path)
  {
    path = Path;
    if (hNotify != INVALID_HANDLE_VALUE)    //关闭以前的句柄
      FindCloseChangeNotification(hNotify);

    hNotify = FindFirstChangeNotification(path.c_str(),false,dwFlags);
  }

  return(hNotify != INVALID_HANDLE_VALUE);
}
//---------------------------------------------------------------------------
void __fastcall TDirectoryThread::ThreadFinish(TObject *Sender)
{
  FindCloseChangeNotification(hNotify); //cleanup
}
//---------------------------------------------------------------------------
void __fastcall TDirectoryThread::Update()
{
  //Sleep(1000);
  SendMessage(Hwnd,FMsgID,0,0);
}

bool __fastcall TDirectoryThread::StopWatch(void)
{
  this->Suspend();
  return this->Suspended;
}

bool __fastcall TDirectoryThread::StartWatch(void)
{
  this->Resume();
  return !this->Suspended;
}
