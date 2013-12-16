// ------------------------------------------------------------------------------
#ifndef UTrdCot_RmH
#define UTrdCot_RmH
// ------------------------------------------------------------------------------
#include <SyncObjs.hpp>
#include "UTrdCot.h"
#include "UTrdStruct_Rm.h"
#include "UPlugInWrapper.h"
#include <stdio.h>

void addlog(const char *log)
{
//
	FILE * pFile;
	AnsiString logf = AnsiString(Date().FormatString(L"yyyymmdd")+L".txt");
	pFile = fopen(logf.c_str(),"a+");
	if (pFile!=NULL)
	{
		fprintf(pFile,"%s\r\n",log);
		fclose (pFile);
	}
}
// ------------------------------------------------------------------------------
class TTrdCot_Rm : public TTrdCot {
private: // User declarations
    plugin_wrapper _pw;
	TCriticalSection *FCS;
	AnsiString _plugin;
	TTrdItfAPI* _trditf;
	int __fastcall Request(TRequest Request, TAnswer **Answer, int &AnsCount);

	int __fastcall DeleteAns(TAnswer **Answer) {
		if(_trditf)
		{
			_trditf->FreeAnswer(*Answer);
        }
		return 0;
	}

public: // User declarations

	__fastcall TTrdCot_Rm();
	__fastcall ~TTrdCot_Rm();

	void set_plugin(const char * plugin)
	{
		_plugin = plugin;

		if( _trditf!=NULL )
		{
			_trditf->CloseLink();
			_pw.free_itf(_trditf);
			_trditf = NULL;
		}

		if( _pw.load_plugin(_plugin.c_str()) == true )
		{
			_trditf = _pw.create((_plugin+".ini").c_str(),addlog);
        }
    }
};
// ---------------------------------------------------------------------------
#endif
// ------------------------------------------------------------------------------
