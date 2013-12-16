#ifndef System_sH
#define System_sH

#include <stdio.h>
#include <windows.h>
#include <iphlpapi.h>
#include <winsock.h>
#include <tchar.h>

bool DirectoryExists(TCHAR * Directory);
bool FileExists(const TCHAR * File);
int GetErrorMsg(TCHAR * buf,int sizeofbuf);
void ShowErrorMsg(TCHAR * msg=NULL);
bool GetFilePath(const TCHAR*PathName,TCHAR *Path,int length);
bool ChangeFileExt(TCHAR *PathName,const TCHAR * ext);

//��õ�ǰ����·��������"\\"
bool GetExePath(TCHAR *path);
bool GetFileName(TCHAR *pathname,bool with_ext);

int Sock2Startup(void);
int GetLocalIP(LPHOSTENT *ph,char *HostName);
int GetMac(char * ip,char * mac);
int GetMac(IPAddr ipAddr,char * mac);
int GetNMac(int n,char *mac);  //��ȡ�ڣ�������ģ���
BOOL SetNewTime(WORD hour, WORD minutes,WORD second);

#endif