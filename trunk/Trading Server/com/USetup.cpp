//---------------------------------------------------------------------------
#pragma hdrstop

#include "USetup.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall TStp::TStp(String IniFilePath):TAppSetup(IniFilePath)
{
#ifndef PTRDDLL
	ServerIP="";
	ServerPort=8888;
	MaxClient=1024;
	WorkThread=0;   //自动选择
	KeepAliveTime=0; //不起用
	PlugInName = "";
	SaveOrderFile = false;
	OrderFilePath  = "";
#endif
	//rm
	RM_Svr="";
	RM_Port=2003;

	if(FileExists(IniFilePath))
		ReadFromFile();

	SaveToFile(IniFilePath);
}

void __fastcall TStp::WriteIni(void)
{
	try
	{
	#ifndef PTRDDLL
		FIniFile->WriteString("SERVER","ServerIP",ServerIP);
		FIniFile->WriteInteger("SERVER","ServerPort",ServerPort);
		FIniFile->WriteInteger("SERVER","MaxClient",MaxClient);
		FIniFile->WriteInteger("SERVER","WorkThread",WorkThread);
		FIniFile->WriteString("SERVER","PlugInName",PlugInName);
		FIniFile->WriteString("ORDERFILE","OrderFilePath",OrderFilePath) ;
		FIniFile->WriteBool("ORDERFILE","SaveOrderFile",SaveOrderFile);
		FIniFile->WriteInteger("SERVER","KeepAliveTime",KeepAliveTime);
  #endif
		FIniFile->WriteString("RM","RM_Svr",RM_Svr);
		FIniFile->WriteInteger("RM","RM_Port",RM_Port);

  }
  catch(Exception &e)
  {
		MessageBoxA(NULL,AnsiString("配置文件写入失败!检测是否为只读.\r\n描述:" + e.Message).c_str(),
			"错误!", MB_ICONWARNING);
  }
}

void __fastcall TStp::ReadIni(void)
{
#ifndef PTRDDLL
	String tmp;
	ServerIP=FIniFile->ReadString("SERVER","ServerIP",ServerIP);
	ServerPort=FIniFile->ReadInteger("SERVER","ServerPort",ServerPort);
	MaxClient=FIniFile->ReadInteger("SERVER","MaxClient",MaxClient);
	WorkThread=FIniFile->ReadInteger("SERVER","WorkThread",WorkThread);
	PlugInName=FIniFile->ReadString("SERVER","PlugInName",PlugInName);
	OrderFilePath=FIniFile->ReadString("ORDERFILE","OrderFilePath",OrderFilePath) ;
	SaveOrderFile=FIniFile->ReadBool("ORDERFILE","SaveOrderFile",SaveOrderFile);
	KeepAliveTime=FIniFile->ReadInteger("SERVER","KeepAliveTime",KeepAliveTime);
#endif
  	RM_Svr=FIniFile->ReadString("RM","RM_Svr",RM_Svr);
	RM_Port=FIniFile->ReadInteger("RM","RM_Port",RM_Port);
}

__fastcall TStp::~TStp(void)
{
}
