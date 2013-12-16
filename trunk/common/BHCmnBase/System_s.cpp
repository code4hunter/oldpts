#include "System_s.h"

#pragma comment(lib, "Iphlpapi.lib")

bool DirectoryExists(TCHAR * Directory)
{
	BOOL ret=GetFileAttributes(Directory);
	return (ret != FALSE) && ((FILE_ATTRIBUTE_DIRECTORY & ret) != 0);
}

bool FileExists(const TCHAR * File)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile(File, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		FindClose(hFind);
		return true;
	}
	return false;
}

int GetErrorMsg(TCHAR **buf)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL
	);

	LPCTSTR tmp= (LPCTSTR)lpMsgBuf;
	*buf=new TCHAR[_tcslen(tmp)];
	lstrcpy(*buf,tmp);
	LocalFree( lpMsgBuf );
	return sizeof(*buf);
}

bool GetExePath(TCHAR *path)
{
	TCHAR buf[MAX_PATH+1];
	GetModuleFileName(NULL,buf,MAX_PATH);
	return GetFilePath(buf,path,MAX_PATH);
}

void ShowErrorMsg(TCHAR * msg)
{
	LPVOID lpMsgBuf;
	if (!FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL ))
	{
	  return;
	}
	
	// Process any inserts in lpMsgBuf.
	TCHAR Caption[255];
	if(msg!=NULL && _tcslen(msg)>0)
	{
		lstrcpy(Caption,_T("Error:"));
		lstrcat(Caption,_T("msg"));
	}
	else
		lstrcpy(Caption,_T("Error"));

	// Display the string.
	MessageBox( NULL, (LPCTSTR)lpMsgBuf, Caption, MB_OK | MB_ICONINFORMATION );

	// Free the buffer.
	LocalFree( lpMsgBuf );
}

bool GetFilePath(const TCHAR*PathName,TCHAR *Path,int length)
{
	_tcsncpy_s(Path,length,PathName,length);
	size_t n=_tcslen(Path)-1;
	for(int i=(int)n;i>=0;i--)
	{
		if(Path[i]=='\\') 
		{
			Path[i+1]='\0';
			return true;
		}
	}
	return false;
}

bool ChangeFileExt(TCHAR *PathName,const TCHAR * ext)
{
	size_t n=_tcslen(PathName)-1;
	TCHAR *ptr;
	for(int i=(int)n;i>=0;i--)
	{
		if(PathName[i]=='.') 
		{
			ptr=PathName+i;
			_tcscpy_s(ptr,n,ext);
			return true;
		}
	}
	return false;
}

int Sock2Startup(void)
{
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;

  wVersionRequested = MAKEWORD( 2, 0 );

  err = WSAStartup( wVersionRequested, &wsaData );
  if ( err != 0 ) {
      /* Tell the user that we couldn't find a usable */
      /* WinSock DLL.                                  */
      return -1;
  }

  /* Confirm that the WinSock DLL supports 2.0.*/
  /* Note that if the DLL supports versions greater    */
  /* than 2.0 in addition to 2.0, it will still return */
  /* 2.0 in wVersion since that is the version we      */

  /* requested.                                        */

  if ( LOBYTE( wsaData.wVersion ) != 2 ||
          HIBYTE( wsaData.wVersion ) != 0 ) {
      /* Tell the user that we couldn't find a usable */
      /* WinSock DLL.                                  */
      WSACleanup( );
      return -1;
  }

  return 0;
}

int GetLocalIP(LPHOSTENT *ph,char *HostName)
{
	//sockaddr_in peer;

	if( gethostname(HostName, 128) != 0 )
	{
		return(-1);
	}

	if ((*ph = gethostbyname(HostName)) == NULL)
	{
		return(-2);
	}

  return 0;
}

int GetMac(IPAddr ipAddr,char * mac)
{
  HRESULT hr;
  ULONG   pulMac[2];
  ULONG   ulLen;

  memset (pulMac, 0xff, sizeof (pulMac));
  ulLen = 6;

  hr = SendARP (ipAddr, 0, pulMac, &ulLen);

  if(NO_ERROR==hr)
  {
    size_t i, j;
    char * szMac = new char[ulLen*3];
    PBYTE pbHexMac = (PBYTE) pulMac;

    //
    // Convert the binary MAC address into human-readable
    //
    for (i = 0, j = 0; i < ulLen - 1; ++i) {
        j += sprintf_s (szMac + j,2, "%02X:", pbHexMac[i]);
    }

    sprintf_s (szMac + j,2, "%02X", pbHexMac[i]);
    strcpy_s(mac,20,szMac);

    delete [] szMac;
  }
  else return -1;
  
  return 0;
}

int GetMac(char * ip,char * mac)
{
  IPAddr  ipAddr;
  ipAddr = inet_addr (ip);
  return GetMac(ipAddr,mac);
}

int GetNMac(int n,char *mac)
{
  LPHOSTENT ph;
  char hostname[128];
  if(Sock2Startup()==0)
  {
    if(GetLocalIP(&ph,hostname)==0)
    {
      if(n< ph->h_length / (int)sizeof(int))
      {
        if(GetMac(*((IPAddr *)ph->h_addr_list[n]),mac)==0)
          return 0;
        else
          return -4;
      }
      else return -3;
    }
    else
      return -1;
  }
  else
    return -2;
}

bool GetFileName(TCHAR *pathname,bool with_ext)
{
	TCHAR tmp[255] = {_T("\0")};
	size_t n=_tcslen(pathname);
	for(int i=(int)n;i>=0;i--)
	{
		if(pathname[i]==_T('\\')) 
		{
			_tcscpy_s(tmp,255,pathname+i+1);
			break;
		}
	}

	if(!with_ext)
	{
		n=_tcslen(tmp);
		for(size_t i=0;i<n;i++)
		{
			if(tmp[i]==_T('.'))
			{
				tmp[i]=_T('\0');
				break;
			}
		}
	}

	if(_tcslen(tmp)>0)
	{
		_tcscpy_s(pathname,255,tmp);
		return true;
	}

	return false;
}

// SetNewTime - sets system time
// Return value - TRUE if successful, FALSE otherwise
// hour     - new hour (0-23)
// minutes  - new minutes (0-59)
// second   - new second (0-59)

BOOL SetNewTime(WORD hour, WORD minutes,WORD second)
{
    SYSTEMTIME st;

    GetSystemTime(&st);       // gets current time
    st.wHour = hour;          // adjusts hours 
    st.wMinute = minutes;     // and minutes
	st.wSecond = second;
    if (!SetSystemTime(&st))  // sets system time
        return FALSE;
    return TRUE;
}
