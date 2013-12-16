#ifndef SystemH
#define SystemH

#include <stdio.h>
#include <windows.h>
#include <iphlpapi.h>
#include <winsock.h>

bool DirectoryExists(char * Directory);
bool FileExists(char * File);
int GetErrorMsg(char * buf,int sizeofbuf);
void ShowErrorMsg(char * msg=NULL);
bool GetFilePath(const char*PathName,char *Path,int length);
bool ChangeFileExt(char *PathName,const char * ext);

//获得当前程序路径，包含"\\"
bool GetExePath(char *path);
bool GetFileName(char *pathname,bool with_ext);

int Sock2Startup(void);
int GetLocalIP(LPHOSTENT *ph,char *HostName);
int GetMac(char * ip,char * mac);
int GetMac(IPAddr ipAddr,char * mac);
int GetNMac(int n,char *mac);  //获取第ｎ个网卡的ｍａｃ
BOOL SetNewTime(WORD hour, WORD minutes,WORD second);

#endif