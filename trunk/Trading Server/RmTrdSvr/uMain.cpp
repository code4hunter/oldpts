//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop
//---------------------------------------------------------------------------

#include "versinfo.hpp"
#include "uItfTrdTrdSvr.h"

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
		return new TTrdItf_TrdSvr(psetupfile,plogfunc);
	}

	PTRADE_API void __stdcall free_itf( TTrdItfAPI* itf )
	{
		if( itf!= NULL )
			delete (TTrdItf_TrdSvr*)itf;
	}

	PTRADE_API void __stdcall get_version( char * name, int name_size,char * version,int version_size)
	{
		lstrcpyn(name,PLUGINNAME,name_size);
		VersionInfo vi("PTrdTrdSvr.dll");
		String strVer;
		strVer.printf("%d.%d.%d.%d",vi.productMajorVersion(),
										 vi.productMinorVersion(),
										 vi.productBuild(),
										 vi.productSubBuild());
		lstrcpyn(version,strVer.c_str(), version_size);
	}
}