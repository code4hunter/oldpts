#include "ShareMem.h"
//#include "System.h"

LPVOID CShareMem::Create(LPSTR szName, DWORD nsize,int type)
{
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;
	
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);

	sa.bInheritHandle=FALSE;
	sa.nLength=sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor=&sd;

	if(type==0) //create
	{
		hmempage = CreateFileMapping(INVALID_HANDLE_VALUE,
			&sa,                              // default security 
			PAGE_READWRITE,                    // read/write permission 
			0,                             // max. object size 
			nsize,                                 // size of hFile 
			szName);            // name of mapping object 
		
		if(hmempage==NULL) 
		{
			//ShowErrorMsg("CreateFileMapping");
			return NULL;
		}

		AlreadyExists=(GetLastError()==ERROR_ALREADY_EXISTS);
	}

	if (type==1) //open 
	{ 		
		hmempage = OpenFileMapping(FILE_MAP_ALL_ACCESS, // read/write permission 
			FALSE,                             // Do not inherit the name
			szName);            // of the mapping object. 
		
		if(hmempage==NULL) return NULL;
		
	}

	lpvmem = MapViewOfFile(hmempage, // handle to mapping object 
		FILE_MAP_ALL_ACCESS,               // read/write permission 
		0,								   // max. object size 
		0,                                 // size of hFile 
		0);                                // map entire file 
	
	m_Size=nsize;
	return lpvmem; 
}

void CShareMem::Release(void)
{
	if(IsCreated())
	{
		if(UnmapViewOfFile(lpvmem))
			lpvmem=NULL;
		else 
		{
			//ShowErrorMsg("UnmapViewOfFile");
		}
	}

	if(hmempage!=NULL)
	{
		CloseHandle(hmempage);
		hmempage=NULL;
	}
}