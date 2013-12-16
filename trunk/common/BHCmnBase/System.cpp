#include "System.h"

#pragma comment(lib, "Iphlpapi.lib")

bool DirectoryExists(char * Directory)
{
	BOOL ret=GetFileAttributes(Directory);
	return (ret != FALSE) && ((FILE_ATTRIBUTE_DIRECTORY & ret) != 0);
}

bool FileExists(char * File)
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

int GetErrorMsg(char **buf)
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

	LPCSTR tmp= (LPCSTR)lpMsgBuf;
	*buf=new char[strlen(tmp)];
	lstrcpy(*buf,tmp);
	LocalFree( lpMsgBuf );
	return sizeof(*buf);
}

bool GetExePath(char *path)
{
	TCHAR buf[MAX_PATH+1];
	GetModuleFileName(NULL,buf,MAX_PATH);
	return GetFilePath(buf,path,MAX_PATH);
}

void ShowErrorMsg(char * msg)
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
	char Caption[255];
	if(msg!=NULL && strlen(msg)>0)
	{
		strcpy(Caption,"Error:");
		strcat(Caption,msg);
	}
	else
		strcpy(Caption,"Error");

	// Display the string.
	MessageBox( NULL, (LPCTSTR)lpMsgBuf, Caption, MB_OK | MB_ICONINFORMATION );

	// Free the buffer.
	LocalFree( lpMsgBuf );
}

bool GetFilePath(const char*PathName,char *Path,int length)
{
	strncpy(Path,PathName,length);
	size_t n=strlen(Path)-1;
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

bool ChangeFileExt(char *PathName,const char * ext)
{
	size_t n=strlen(PathName)-1;
	char *ptr;
	for(int i=(int)n;i>=0;i--)
	{
		if(PathName[i]=='.') 
		{
			ptr=PathName+i;
			strcpy(ptr,ext);
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
        j += sprintf (szMac + j, "%02X:", pbHexMac[i]);
    }

    sprintf (szMac + j, "%02X", pbHexMac[i]);
    strcpy(mac,szMac);

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

bool GetFileName(char *pathname,bool with_ext)
{
	char tmp[255];
	size_t n=strlen(pathname);
	for(int i=(int)n;i>=0;i--)
	{
		if(pathname[i]=='\\') 
		{
			strcpy(tmp,pathname+i+1);
			break;
		}
	}

	if(!with_ext)
	{
		n=strlen(tmp);
		for(size_t i=0;i<n;i++)
		{
			if(tmp[i]=='.')
			{
				tmp[i]='\0';
				break;
			}
		}
	}

	if(strlen(tmp)>0)
	{
		strcpy(pathname,tmp);
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
