//---------------------------------------------------------------------------
#ifndef UChangeNfy2H
#define UChangeNfy2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <sysdyn.h>
//---------------------------------------------------------------------------
const unsigned long dwFlags =FILE_NOTIFY_CHANGE_LAST_WRITE;

class TDirectoryThread : public TThread
{
private:
  HANDLE hNotify;   //Event object handle
  String path;      //Path to monitor
  HWND Hwnd;
  UINT FMsgID;
  void __fastcall Update();
  void __fastcall ThreadFinish(TObject *Sender);
protected:
  void __fastcall Execute();
public:
  __fastcall TDirectoryThread(HWND handle,UINT MsgID);
  bool __fastcall SetMonitorPath(String path);
  bool __fastcall StopWatch(void);
  bool __fastcall StartWatch(void);
};

//---------------------------------------------------------------------------
#endif
