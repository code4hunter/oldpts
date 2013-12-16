//---------------------------------------------------------------------------
#ifndef UChangeNfy3H
#define UChangeNfy3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <sysdyn.h>
//---------------------------------------------------------------------------

class TDirectoryThread : public TThread
{
private:
  String path;      //Path to monitor
  HWND Hwnd;
  UINT FMsgID;
  int iFileHandle;
protected:
  void __fastcall Execute();
  void __fastcall ThreadFinish(TObject *Sender);
public:
  __fastcall TDirectoryThread(HWND handle,UINT MsgID);
  bool __fastcall SetMonitorPath(String path);
  bool __fastcall StopWatch(void);
  bool __fastcall StartWatch(void);
};

//---------------------------------------------------------------------------
#endif
