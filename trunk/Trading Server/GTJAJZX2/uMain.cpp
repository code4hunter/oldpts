//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "versinfo.hpp"
#include "UTrdItf_GTJA.h"
#pragma hdrstop
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
		return new TTrdItf_GTJA(psetupfile,plogfunc,true);
	}

	PTRADE_API void __stdcall free_itf( TTrdItfAPI* itf )
	{
		if( itf!= NULL )
			delete (TTrdItf_GTJA*)itf;
	}

	PTRADE_API void __stdcall get_version( char * name, int name_size,char * version,int version_size)
	{
		lstrcpyn(name,PLUGINNAME,name_size);
		VersionInfo vi("PTrdGTJAJZX2.dll");
		AnsiString strVer;
		strVer.printf("%d.%d.%d.%d",vi.productMajorVersion(),
										 vi.productMinorVersion(),
										 vi.productBuild(),
										 vi.productSubBuild());
		lstrcpyn(version,strVer.c_str(), version_size);
	}
}
