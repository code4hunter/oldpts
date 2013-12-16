//---------------------------------------------------------------------------

#include "UTrdItfApi.h"
#include "versinfo.hpp"
#include "uTrdIB962.h"

#include <windows.h>
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
extern "C"
{
	PTRADE_API TTrdItfAPI* __stdcall create( const char *psetupfile,ADDLOG plogfunc )
	{
		set_addlog_callback(plogfunc);
		return new TTrdItf_IB962(psetupfile,plogfunc);
	}

	PTRADE_API void __stdcall free_itf( TTrdItfAPI* itf )
	{
		if( itf!= NULL )
			delete (TTrdItf_IB962*)itf;
	}

	PTRADE_API void __stdcall get_version( char * name, int name_size,char * version,int version_size)
	{
		lstrcpyn(name,PLUGINNAME,name_size);
		try
		{
			VersionInfo vi("PTrdIB962.dll");
			char strVer[100];
			sprintf(strVer,"%d.%d.%d.%d",vi.productMajorVersion(),
											 vi.productMinorVersion(),
											 vi.productBuild(),
											 vi.productSubBuild());
			lstrcpyn(version,strVer, version_size);
		}
		catch(...)
		{
			lstrcpyn(version,"0.0.0.0", version_size);
		}
	}
}