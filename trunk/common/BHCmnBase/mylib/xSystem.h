//---------------------------------------------------------------------------

#ifndef xSystemH
#define xSystemH

#include<tchar.h>
#include<classes.hpp>
#include<Controls.hpp>
#include<ComCtrls.hpp>
//---------------------------------------------------------------------------
AnsiString xGetTempPath(void);
AnsiString xGetTempFileName(const AnsiString PathName,const AnsiString PrefixString);
AnsiString xGetWindowPath(void);
AnsiString xGetSystemPath(void);
AnsiString xGetComputerName(void);

bool xMakeStartUp(const AnsiString Key,const AnsiString Value,bool Enable);
bool xValueExists(HKEY RootKey,const AnsiString Path,const AnsiString Key,const AnsiString Value);
bool xWriteValue(HKEY RootKey,const AnsiString Path,const AnsiString Key,const AnsiString Value);

void xMsgBox(const AnsiString Msg);
void xErrBox(const AnsiString Msg);
bool xYesNoBox(const AnsiString Msg,DWORD DefBtn = MB_DEFBUTTON1);
bool xYesNoCancelBox(const AnsiString Msg);
int  xAbortRetryCancelBox(const AnsiString Msg);

void xInvokeExe(const AnsiString aPathName,AnsiString aCmdLine="");
AnsiString DateToStrEx(TDate);
TDate StrToDateEx(AnsiString dt);
int GetAllDirectory(AnsiString path,TStrings * files,TStrings *dirs);
bool __fastcall xSaveListViewToFile(const AnsiString PathName,TListView *lv);
bool xSaveStringToFile(const AnsiString PathName,const AnsiString Text);
#endif
