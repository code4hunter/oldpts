#ifndef SHAREMEM_H
#define SHAREMEM_H

#include <windows.h>

class CShareMem
{
public:
	CShareMem(void) {hmempage = NULL; lpvmem = NULL;}
	CShareMem(LPSTR szName, DWORD nsize,int type) 
	{ 
		AlreadyExists=false;
		Create(szName, nsize ,type);
	}

	~CShareMem(void) {Release();}
public:
	LPVOID Create(LPSTR szName, DWORD nsize,int type);
	LPVOID Handle(void) { return lpvmem; }
	void Release(void);
	bool IsCreated(void) { return lpvmem == NULL ? false : true; }

	bool AlreadyExists;

	DWORD GetSize(void){ return m_Size;}
private:
	HANDLE		hmempage;
	LPVOID		lpvmem;
	DWORD m_Size;
};

#endif
