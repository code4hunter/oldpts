//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "DebugStr.h"
#include "UTrdItf_HSFF.h"
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
        set_addlog_callback(plogfunc);
		return new TTrdItf_HSFF(psetupfile,plogfunc);
	}

	PTRADE_API void __stdcall free_itf( TTrdItfAPI* itf )
	{
		if( itf!= NULL )
			delete (TTrdItf_HSFF*)itf;
	}

	PTRADE_API void __stdcall get_version( char * name, int name_size,char * version,int version_size)
	{
		lstrcpyn(name,PLUGINNAME,name_size);
		try
		{
			VersionInfo vi("PTrdHSF3.dll");
			AnsiString strVer;
			strVer.printf("%d.%d.%d.%d",vi.productMajorVersion(),
											 vi.productMinorVersion(),
											 vi.productBuild(),
											 vi.productSubBuild());
			lstrcpyn(version,strVer.c_str(), version_size);
		}
		catch(...)
		{
			lstrcpyn(version,"0.0.0.0", version_size);
		}
	}
}