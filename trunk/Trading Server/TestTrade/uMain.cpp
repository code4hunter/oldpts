//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "uTrdItf_Test.h"
#include "versinfo.hpp"
#pragma hdrstop

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
extern "C"
{
	PTRADE_API TTrdItfAPI* __stdcall create( const char *psetupfile,ADDLOG plogfunc )
	{
		return new TTrdItfTest(psetupfile,plogfunc);
	}

	PTRADE_API void __stdcall free_itf( TTrdItfAPI* itf )
	{
		if( itf!= NULL )
			delete (TTrdItfTest*)itf;
	}

	PTRADE_API void __stdcall get_version( char * name, int name_size,char * version,int version_size)
	{
		lstrcpyn(name,PLUGINNAME,name_size);
		VersionInfo vi("PTrdTest.dll");
		String strVer;
		strVer.printf("%d.%d.%d.%d",vi.productMajorVersion(),
										 vi.productMinorVersion(),
										 vi.productBuild(),
										 vi.productSubBuild());
		lstrcpyn(version,strVer.c_str(), version_size);
	}
}