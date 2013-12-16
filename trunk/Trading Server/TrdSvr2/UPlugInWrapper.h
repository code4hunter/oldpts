//---------------------------------------------------------------------------

#ifndef UPlugInWrapperH
#define UPlugInWrapperH

#include "UTrdItfAPI.h"

class plugin_wrapper
{

typedef TTrdItfAPI* __stdcall (*CREATE)( const char*,ADDLOG);
typedef void __stdcall (*GET_VERSION)( char *, int,char * ,int );
typedef void __stdcall (*FREE_ITF)( TTrdItfAPI* );

private:
	HINSTANCE  dllhandle; //¶¯Ì¬Á´½Ó¿â¾ä±ú
	CREATE fcreate;
	GET_VERSION fget_version;
	FREE_ITF ffree;
public:
	plugin_wrapper();
	~plugin_wrapper();

	bool load_plugin( char *plugin_name);

	TTrdItfAPI* create( const char *psetupfile,ADDLOG plogfunc );
	void free_itf( TTrdItfAPI* itf);
	bool get_version( char * interface_name, int name_size,
										char * version,int version_size);
};



//---------------------------------------------------------------------------
#endif
