//---------------------------------------------------------------------------
#ifndef USetupH
#define USetupH

#include "AppSetup.h"
//---------------------------------------------------------------------------
#ifndef PTRDDLL
#endif

class TStp : public TAppSetup
{
protected:
  	void __fastcall WriteIni(void);
	void __fastcall ReadIni(void);
public:
	__fastcall TStp(String IniFilePath);
	__fastcall ~TStp(void);
#ifndef PTRDDLL
	AnsiString ServerIP;
	int    ServerPort;
	int    MaxClient;
	int    WorkThread;
	AnsiString PlugInName;
	bool SaveOrderFile;
	AnsiString OrderFilePath;
	//keep alive setup millisecond
	int KeepAliveTime;
#endif
	//remote
	AnsiString RM_Svr;     //下一个节点服务器地址
	int    RM_Port;
};
#endif
