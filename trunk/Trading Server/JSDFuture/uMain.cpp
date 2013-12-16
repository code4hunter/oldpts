//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "UTrdItf_JSDFF.h"
#include "uRecvEventsTh.h"
#include "versinfo.hpp"
#pragma hdrstop
#pragma argsused

static LONG refcount = 0;
RecvThFactory *g_recvth = NULL;

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
		if (InterlockedIncrement(&refcount) == 1 ) {
			g_recvth = new RecvThFactory(psetupfile);
		}
		return new TTrdItf_JSDFF(psetupfile,plogfunc);
	}

	PTRADE_API void __stdcall free_itf( TTrdItfAPI* itf )
	{
		if( itf!= NULL )
			delete (TTrdItf_JSDFF*)itf;

		if (InterlockedDecrement(&refcount) == 0 ) {
			delete g_recvth ;
			g_recvth = NULL;
		}
	}

	PTRADE_API void __stdcall get_version( char * name, int name_size,char * version,int version_size)
	{
		lstrcpyn(name,PLUGINNAME,name_size);
		VersionInfo vi("PTrdJSDF.dll");
		String strVer;
		strVer.printf("%d.%d.%d.%d",vi.productMajorVersion(),
										 vi.productMinorVersion(),
										 vi.productBuild(),
										 vi.productSubBuild());
		lstrcpyn(version,strVer.c_str(), version_size);
	}
}