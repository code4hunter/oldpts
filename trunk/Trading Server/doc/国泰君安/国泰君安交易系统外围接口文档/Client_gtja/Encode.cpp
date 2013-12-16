// Encode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <windows.h>


typedef char * ( __cdecl * DOGSKIN_ENCODE)(const char *);

DOGSKIN_ENCODE ApiEncode = NULL;

int main(int argc, char* argv[])
{
	HMODULE m_hDll = NULL;

	m_hDll = ::LoadLibrary("Dogskin.dll");
	if(!m_hDll)
	{
		cout << " no LoadLibrary Dogskin.dll!!" << endl;
		return -1;
	}
	ApiEncode = (DOGSKIN_ENCODE)::GetProcAddress(m_hDll, "Encode");
	if(!ApiEncode)
	{
		cout << "Not get the address of the Encode function!!!" << endl;
		return -1;
	}

	char szSource[] = "111119";
	char szResult[1024];

	memset(szResult, 0x0, sizeof(szResult));

	strcpy(szResult, ApiEncode((const char *)szSource));

	cout << szResult << endl;

	::FreeLibrary(m_hDll);

	return 0;
}
