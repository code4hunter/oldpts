//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uPTSDB.h"
#include "..\..\common\BHCmnBase\DebugStr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TdmPTSDB::TdmPTSDB(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
bool TdmPTSDB::ConnectToDB(WideString UDLFileName)
{
	try
	{
		if( cn->Connected == true )
		{
			cn->Close();
		}

		cn->ConnectionString =UDLFileName;
		cn->Connected = true;
	}
	catch( Exception &e )
	{
		ODS('E',"PTSDB","ConnectToDB Error,message is %s",e.Message.c_str());
	}
	return cn->Connected;
}

bool TdmPTSDB::AddOrderReport( String account,
											 String ordid,
											 String execid,
											 long cxlqty,
											 long exeqty,
											 double exepx,
											 long exedate,
											 long exetime,
											 String seqno,
											 String remark)
{
	bool ret = false;
	if( cn->Connected == false ) return false;
	TADOCommand * cmd = new TADOCommand( NULL );
	try
	{
		cmd->Connection = cn;
		cmd->CommandType = cmdStoredProc;
		cmd->CommandText = L"dp_sync_addexecreport2";
		cmd->Parameters->Refresh();
		cmd->Parameters->FindParam(L"@acctnum")->Value = account.c_str();
		cmd->Parameters->FindParam(L"@ordid")->Value = ordid.c_str();
		cmd->Parameters->FindParam(L"@exeid")->Value = execid.c_str();
		cmd->Parameters->FindParam(L"@cxlqty")->Value = cxlqty;
		cmd->Parameters->FindParam(L"@exeqty")->Value = exeqty;
		cmd->Parameters->FindParam(L"@exepx")->Value = exepx;
		cmd->Parameters->FindParam(L"@exedate")->Value = IntToStr(exedate);

		long h,m,s;
		h= exetime/10000;
		m= (exetime%10000) / 100;
		s = exetime % 100;
		String exet;
		exet.sprintf("%d:%02d:%02d",h,m,s);

		cmd->Parameters->FindParam(L"@exetime")->Value = exet;
		cmd->Parameters->FindParam(L"@seqno")->Value = seqno;
		cmd->Parameters->FindParam(L"@remark")->Value =remark;
		cmd->Execute();
		ret= true;
	}
	catch( Exception &e )
	{
		ODS('E',"PTSDB","AddOrderReport Error,message is %s",e.Message.c_str());
	}
	delete cmd;
	return ret;
}

void __fastcall TdmPTSDB::DataModuleDestroy(TObject *Sender)
{
	DisConnect();
}
//---------------------------------------------------------------------------

void TdmPTSDB::DisConnect(void)
{
	if( cn->Connected == true )
	{
		cn->Close();
	}
}
