//---------------------------------------------------------------------------
#pragma hdrstop

#include "UPlugInWrapper.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
plugin_wrapper::plugin_wrapper()
{
	fcreate = NULL;
	fget_version=NULL;
	ffree = NULL;
	dllhandle = NULL;
}

plugin_wrapper::~plugin_wrapper()
{
	if (dllhandle!=NULL) {
		FreeLibrary(dllhandle);
		dllhandle = NULL;
	}
}

bool plugin_wrapper::load_plugin( char *plugin_name)
{
	if( dllhandle!= NULL )
	{
		FreeLibrary(dllhandle);
		dllhandle = NULL;
	}

	dllhandle = LoadLibrary(plugin_name);
	if( dllhandle == NULL ) return false;

	fcreate = (CREATE)GetProcAddress(dllhandle,"create");
	ffree   = (FREE_ITF)GetProcAddress(dllhandle,"free_itf");
	fget_version =  (GET_VERSION)GetProcAddress(dllhandle,"get_version");

	if( fcreate== NULL || fget_version==NULL ) return false;

	return true;
}

TTrdItfAPI* plugin_wrapper::create( const char *psetupfile,ADDLOG plogfunc )
{
	if ( fcreate!=NULL	) {
  	try
    {
			return fcreate(psetupfile,plogfunc);
    }
    catch(...)
    {
      return NULL;
    }
	}
	return NULL;
}

void plugin_wrapper::free_itf( TTrdItfAPI* itf)
{
	if( itf == NULL ) return;
	if( ffree!= NULL )
	{
  	try
    {
  		ffree(itf);
    }
    catch(...)
    {
    
    }
	}
}

bool plugin_wrapper::get_version( char * interface_name, int name_size,
										char * version,int version_size)
{
	if( fget_version!=NULL )
	{
		fget_version(interface_name,name_size,version,version_size);
		return true;
	}
  	return false;
}