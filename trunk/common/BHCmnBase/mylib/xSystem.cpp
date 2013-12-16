//---------------------------------------------------------------------------
#pragma hdrstop

#include "xSystem.h"
#include <windows.h>
#include <shellapi.h>
#include <SysUtils.hpp>
#include <Registry.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

AnsiString xGetTempPath(void)
{
	TCHAR buf[MAX_PATH +1];
	if(GetTempPath(MAX_PATH,buf)>0)
	{
		return StrPas(buf);
	}
	else
		return _T("");
}

AnsiString xGetTempFileName(const AnsiString PathName,const AnsiString PrefixString)
{
	TCHAR buf[MAX_PATH +1];
	if(GetTempFileName(PathName.c_str(),PrefixString.c_str(),0,buf))
  {
		return StrPas(buf);
  }
	else
		return _T("");
}

AnsiString xGetWindowPath(void)
{
	TCHAR buf[MAX_PATH + 1];
	if(GetWindowsDirectory(buf,sizeof(buf))>0)
  {
		return StrPas(buf);
  }
  else
		return _T("");
}

AnsiString xGetSystemPath(void)
{
	TCHAR buf[MAX_PATH ];
	if(GetSystemDirectory(buf,sizeof(buf))>0)
  {
    return StrPas(buf);
	}
	else
		return _T("");
}

bool xMakeStartUp(const AnsiString Key,const AnsiString Value,bool Enable)
{
  TRegistry *Reg = new TRegistry;
  try
  {
    Reg->RootKey = HKEY_LOCAL_MACHINE;
    if(Enable)
    {
      if(Reg->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", true))
      {
        Reg->WriteString(Key,Value);
        Reg->CloseKey();
        return true;
      }
    }
    else
    {
      if(Reg->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", false))
      {
        bool ret;
        if(Reg->ValueExists(Key))
        {
          ret=Reg->DeleteValue(Key);
        }
        Reg->CloseKey();
        return ret;
      }
    }
  }
  __finally
  {
      delete Reg;
  }
  return false;
}

bool xValueExists(HKEY RootKey,const AnsiString Path,const AnsiString Key,const AnsiString Value)
{
  TRegistry *Reg = new TRegistry;
  bool ret=false;
  try
  {
    Reg->RootKey =RootKey;

    if(Reg->OpenKey(Path, false))
    {

      ret=Reg->ValueExists(Key);
      Reg->CloseKey();
    }
  }
  __finally
  {
      delete Reg;
  }
  return ret;
}

bool xWriteValue(HKEY RootKey,const AnsiString Path,const AnsiString Key,const AnsiString Value)
{
  TRegistry *Reg = new TRegistry ;
  bool ret=false;
  try
  {
    Reg->RootKey =RootKey;

    if(Reg->OpenKey(Path, true))
    {
      Reg->WriteString(Key,Value);
      Reg->CloseKey();
      ret=true;
    }
  }
  __finally
  {
      delete Reg;
  }
  return ret;
}

void xMsgBox(const AnsiString Msg)
{
	MessageBoxA(Application->Handle,Msg.c_str(), AnsiString(Application->Title).c_str(),
						 MB_ICONINFORMATION);
}

void xErrBox(const AnsiString Msg)
{
	MessageBoxA(Application->Handle,Msg.c_str(), AnsiString(Application->Title).c_str(),MB_ICONERROR);
}

bool xYesNoBox(const AnsiString Msg,DWORD DefBtn)
{
	return (MessageBoxA(Application->Handle,Msg.c_str(), AnsiString(Application->Title).c_str(),
			MB_ICONQUESTION | MB_YESNO | DefBtn) == IDYES);
}

bool xYesNoCancelBox(const AnsiString Msg)
{
	return (MessageBoxA(Application->Handle,Msg.c_str(),
	AnsiString(Application->Title).c_str(), MB_ICONQUESTION | MB_YESNOCANCEL | MB_DEFBUTTON1) == IDYES);
}

int  xAbortRetryCancelBox(const AnsiString Msg)
{
	return MessageBoxA(Application->Handle,Msg.c_str(),
    AnsiString(Application->Title).c_str(), MB_ICONQUESTION | MB_ABORTRETRYIGNORE);
}

void xInvokeExe(const AnsiString aPathName,AnsiString aCmdLine)
{
	if(aPathName!=_T(""))
		ShellExecuteA(Application->Handle,"open",
				aPathName.c_str(),
				aCmdLine.c_str(),NULL,SW_SHOWNORMAL);
}

AnsiString xGetComputerName(void)
{
	TCHAR buf[MAX_COMPUTERNAME_LENGTH + 1];
  DWORD len=MAX_COMPUTERNAME_LENGTH + 1;
	if(GetComputerName(buf,&len))
  {
    return AnsiString(buf);
	}
	return _T("");
}

AnsiString DateToStrEx(TDate dt)
{
  char oldsp=DateSeparator;
  AnsiString olddtfmt=ShortDateFormat;
  DateSeparator = '\0';
  ShortDateFormat = "yyyymmdd";
  AnsiString ret=DateToStr(dt);
  DateSeparator = oldsp;
  ShortDateFormat = olddtfmt;
  return ret;
}

TDate StrToDateEx(AnsiString dt)
{
  char oldsp=DateSeparator;
  AnsiString olddtfmt=ShortDateFormat;
  DateSeparator = '\0';
  ShortDateFormat = "yyyymmdd";
  TDate ret=StrToDate(dt);
  DateSeparator = oldsp;
  ShortDateFormat = olddtfmt;
  return ret;
}

int GetAllDirectory(AnsiString path,TStrings * files,TStrings *dirs)
{
	WIN32_FIND_DATA fd;
	HANDLE h=FindFirstFile(path.c_str(),&fd);

	int i=0;

	if(h!=INVALID_HANDLE_VALUE)
	{
		do
		{
			//检查是不是目录
			//如果不是,则进行处理
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
        if(files!=NULL)
        {
          files->Add(fd.cFileName);
        }
			}
			else if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
        if(dirs!=NULL)
				{
					if (lstrcmp(fd.cFileName,_T(".")) != 0 && lstrcmp(fd.cFileName,_T("..")) != 0)
          {
						dirs->Add(fd.cFileName);
          }
				}
			}
			i++;
		} while (FindNextFile(h,&fd) && i<1000);
		FindClose(h);
	}
  return i;
}

bool __fastcall xSaveListViewToFile(const AnsiString PathName,TListView *lv)
{
  if(!DirectoryExists(ExtractFilePath(PathName))) return false;
  ////将TListView转换成为text
  AnsiString szText="";
  TListItem * item;
  for (int i=0;i<lv->Items->Count ;i++)
  {
    item=lv->Items->Item[i];
    szText+=item->Caption + " " + StringReplace(item->SubItems->Text,"\r\n"," ",TReplaceFlags() << rfReplaceAll) + "\r\n";
  }

  if(szText.Length()==0) return true;

  szText="====================["+  DateTimeToStr(Now())  + "]====================\r\n" + szText;

  return xSaveStringToFile(PathName,szText);
}

bool xSaveStringToFile(const AnsiString PathName,const AnsiString Text)
{
  int iFileHandle;
  try
  {
    if(FileExists(PathName))
      iFileHandle = FileOpen(PathName, fmOpenReadWrite|fmShareDenyNone);
    else
      iFileHandle = FileCreate(PathName);

    if(iFileHandle==-1)
    {
      return false;
    }

    FileSeek(iFileHandle,0,2);

    FileWrite(iFileHandle,Text.c_str(),Text.Length());
  }
  __finally
  {
    FileClose(iFileHandle);
  }
  return true;
}

