//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uDmPTSRF.h"
#include "..\..\common\BHCmnBase\DebugStr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TDataModule1::TDataModule1(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
__int64 TDataModule1::AddOrder( String acc,
											 String instid,
											 double ordprice,
											 long ordqty,
											 String orgordid,
											 String ordtype,
											 String market,
											 char ordstate
											 )
{
	__int64 ret = -1;
	if( cn->Connected == false ) return -1;
	TADOCommand * cmd = new TADOCommand( NULL );
	try
	{
		cmd->Connection  = cn;
		cmd->CommandType = cmdStoredProc;
		cmd->CommandText = L"dp_AddOrders";
		cmd->Parameters->Refresh();
		cmd->Parameters->FindParam(L"@acc")->Value = acc;
		cmd->Parameters->FindParam(L"@instid")->Value = instid;
		cmd->Parameters->FindParam(L"@ordprice")->Value = ordprice;
		cmd->Parameters->FindParam(L"@ordqty")->Value = ordqty;
		cmd->Parameters->FindParam(L"@orgordid")->Value = orgordid;
		cmd->Parameters->FindParam(L"@ordtype")->Value = ordtype;
		cmd->Parameters->FindParam(L"@market")->Value = market;
		cmd->Parameters->FindParam(L"@ordstate")->Value = ordstate;
		cmd->Parameters->FindParam(L"@id")->Value =-1L;
		cmd->Execute();
		ret=  cmd->Parameters->FindParam(L"@id")->Value;
	}
	catch( Exception &e )
	{
		ODS('E',"PTSRF","AddOrder Error,message is %s",e.Message.c_str());
	}
	delete cmd;
	return ret;
}

bool TDataModule1::CancelOrder( __int64 ordid )
{
	bool ret= false;
	if( cn->Connected == false ) return false;
	TADOCommand * cmd = new TADOCommand( NULL );
	try
	{
  	cmd->Connection = cn;
		cmd->CommandType = cmdStoredProc;
		cmd->CommandText = L"dp_CancelOrder";
		cmd->Parameters->Refresh();
		cmd->Parameters->FindParam(L"@ordid")->Value = ordid;
		cmd->Execute();
		ret= (cmd->Parameters->FindParam(L"@return_value")->Value == 0);
	}
	catch( Exception &e )
	{
		ODS('E',"PTSRF","CancelOrder Error,message is %s",e.Message.c_str());
	}
	delete cmd;
	return ret;
}

bool TDataModule1::AddOrderReport( __int64 ordid,
											 String instid,
											 String execid,
											 long execqty,
											 double execprice)
{
	bool ret = false;
	if( cn->Connected == false ) return false;
	TADOCommand * cmd = new TADOCommand( NULL );
	try
	{
  	cmd->Connection = cn;
		cmd->CommandType = cmdStoredProc;
		cmd->CommandText = L"dp_AddExecReport";
		cmd->Parameters->Refresh();
		cmd->Parameters->FindParam(L"@ordid")->Value = ordid;
		cmd->Parameters->FindParam(L"@instid")->Value = instid;
		cmd->Parameters->FindParam(L"@execid")->Value = execid;
		cmd->Parameters->FindParam(L"@execqty")->Value = execqty;
		cmd->Parameters->FindParam(L"@execprice")->Value = execprice;
		cmd->Execute();
		ret= true;
	}
	catch( Exception &e )
	{
		ODS('E',"PTSRF","AddOrderReport Error,message is %s",e.Message.c_str());
	}
	delete cmd;
	return ret;
}

bool TDataModule1::ConnectToDB(WideString UDLFileName)
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
		ODS('E',"PTSRF","ConnectToDB Error,message is %s",e.Message.c_str());
	}
	return cn->Connected;
}

void __fastcall TDataModule1::DataModuleDestroy(TObject *Sender)
{
	if( cn->Connected == true )
  	cn->Close();
}
//---------------------------------------------------------------------------

int TDataModule1::GetOrders(AnsiString acc,AnsiString OrdId,AnsiString PosStr,
	TOrderInfo **OrdInfo,int &Num)
{
	int ret = 0;
	if( cn->Connected == false ) return -1;
	TADODataSet *rs = new TADODataSet(NULL);
	try
	{
		rs->Connection =cn;
		rs->CommandType = cmdStoredProc;
		rs->CommandText = L"dp_GetOrders";
		rs->Parameters->Refresh();
		rs->Parameters->FindParam(L"@acc")->Value = acc;
		if( OrdId.Length() > 0 )
		{
    	Num = 1;
			rs->Parameters->FindParam(L"@startindex")->Value = StrToInt(OrdId);
		}
		else
		{
			rs->Parameters->FindParam(L"@startindex")->Value = StrToInt64Def(PosStr,0);
			if( Num <= 1 ) Num = 2;
		}

		rs->Parameters->FindParam(L"@date")->Value = 0;
		rs->Parameters->FindParam(L"@maxcount")->Value = Num;
		rs->Open();
		Num = rs->Parameters->FindParam(L"@return_value")->Value;
		*OrdInfo = new TOrderInfo[Num];
		int i =0;
		while( !rs->Eof )
		{
			TOrderInfo &oi = (*OrdInfo)[i];
			ZeroMemory( &oi,sizeof(TOrderInfo));
			lstrcpyn(oi.ContractID ,IntToStr((__int64)rs->FieldByName(L"ID")->Value).c_str(),SEQ_LEN);
			lstrcpyn(oi.SecuID,rs->FieldByName(L"Instid")->AsString.c_str(),CODE_LEN);
			oi.Market = rs->FieldByName(L"Market")->AsString[1];
			oi.Time = rs->FieldByName(L"OrderTime")->AsInteger;
			oi.Date = rs->FieldByName(L"OrderDate")->AsInteger;
			oi.Type = rs->FieldByName(L"OrderType")->AsString[1];
			oi.State = rs->FieldByName(L"OrderState")->AsString[1];
			oi.CsnVol =rs->FieldByName(L"OrderQty")->AsFloat;
			oi.TrdVol =rs->FieldByName(L"ExecQty")->AsFloat;
			oi.CancelVol = rs->FieldByName(L"CancleQty")->AsFloat;
			oi.CsnPrice = rs->FieldByName(L"OrderPrice")->AsFloat;
			oi.TrdPrice = rs->FieldByName(L"ExecAvgPrice")->AsFloat;
			lstrcpyn(oi.Account,rs->FieldByName(L"Account")->AsString.c_str(),ACC_LEN);
			lstrcpyn(oi.SeqNum, oi.ContractID,SEQ_LEN);
			i++;
			rs->Next();
		}
	}
	catch( Exception &e )
	{
		ODS('E',"PTSRF","GetOrders Error,%s,%s,%s,%d,message is %s",acc.c_str(),
			OrdId.c_str(),PosStr.c_str(),Num,e.Message.c_str());
		ret=-1;
	}
	if( rs->Active == true )
		rs->Close();
	delete rs;
	return ret;
}

int TDataModule1::GetOrderReports(AnsiString acc,AnsiString OrdId,AnsiString PosStr,
	TTradeInfo **TrdInfo,int &Num)
{
	int ret = 0;
	if( cn->Connected == false ) return -1;
	TADODataSet *rs = new TADODataSet(NULL);
	try
	{
		rs->Connection = cn;
		rs->CommandType = cmdStoredProc;
		if( OrdId.Length() >0 )
			rs->CommandText = L"GetExecReportByOrdid";
		else
			rs->CommandText = L"dp_GetExecReport";
		rs->Parameters->Refresh();
		rs->Parameters->FindParam(L"@acc")->Value = acc;
		rs->Parameters->FindParam(L"@date")->Value = 0;
		if( OrdId.Length() > 0 )
		{
			rs->Parameters->FindParam(L"@ordid")->Value = StrToInt64(OrdId);
		}
		else
		{
			rs->Parameters->FindParam(L"@startindex")->Value = StrToInt64Def(PosStr,0);
			rs->Parameters->FindParam(L"@maxcount")->Value = Num;
		}

		rs->Open();
		Num = rs->Parameters->FindParam(L"@return_value")->Value;
		*TrdInfo = new TTradeInfo[Num];
		int i =0;
		while( !rs->Eof )
		{
			TTradeInfo &ti = (*TrdInfo)[i];
      ZeroMemory(&ti,sizeof(TTradeInfo));
			lstrcpyn(ti.ContractID ,IntToStr((__int64)rs->FieldByName(L"OrderID")->Value).c_str(),SEQ_LEN);
			lstrcpyn(ti.SecuID,rs->FieldByName(L"Instid")->AsString.c_str(),CODE_LEN);
			lstrcpyn(ti.TrdID,IntToStr((__int64)rs->FieldByName(L"ID")->Value).c_str(),SEQ_LEN);

			ti.Market = mtNo;
			//ti.Market = rs->FieldByName(L"Market")->AsString[1];
			ti.Time = rs->FieldByName(L"ExecTime")->AsInteger;
			ti.Date = rs->FieldByName(L"ExecDate")->AsInteger;
			ti.Type = rs->FieldByName(L"ExecType")->AsString[1];

			ti.Vol  =rs->FieldByName(L"ExecQty")->AsFloat;
			ti.Price=rs->FieldByName(L"ExecPrice")->AsFloat;
			lstrcpyn(ti.Account,rs->FieldByName(L"Account")->AsString.c_str(),ACC_LEN);
			lstrcpyn(ti.SeqNum, ti.TrdID,SEQ_LEN);
			i++;
			rs->Next();
    }
	}
	catch( Exception &e )
	{
		ODS('E',"PTSRF","GetOrderReports Error,%s,%s,%s,%d,message is %s",acc.c_str(),
			OrdId.c_str(),PosStr.c_str(),Num,e.Message.c_str());
		ret = -1;
	}
	if( rs->Active == true )
		rs->Close();
	delete rs;
	return ret;
}

int TDataModule1::GetUnfilledOrders(AnsiString acc,_ord_**OrdInfo,int &Num)
{
	int ret = 0;
	if( cn->Connected == false ) return -1;
	TADODataSet *rs = new TADODataSet(NULL);
	try
	{
		rs->Connection =cn;
		rs->CommandType = cmdStoredProc;
		rs->CommandText = L"dp_GetUnfilledOrder";
		rs->Parameters->Refresh();
		rs->Parameters->FindParam(L"@acc")->Value = acc;
		rs->Parameters->FindParam(L"@date")->Value = 0;

		rs->Open();
		Num = rs->Parameters->FindParam(L"@return_value")->Value;
		*OrdInfo = new _ord_[Num];
		int i =0;
		while( !rs->Eof )
		{
			TOrderInfo &oi = (*OrdInfo)[i].oi;
			ZeroMemory(&oi,sizeof(TOrderInfo));
			(*OrdInfo)[i].ordrepid =(__int64)rs->FieldByName(L"ID")->Value;
			lstrcpyn(oi.ContractID ,rs->FieldByName(L"OrgOrderID")->AsString.c_str(),SEQ_LEN);
			lstrcpyn(oi.SecuID,rs->FieldByName(L"Instid")->AsString.c_str(),CODE_LEN);
			oi.Market = rs->FieldByName(L"Market")->AsString[1];
			oi.Time = rs->FieldByName(L"OrderTime")->AsInteger;
			oi.Date = rs->FieldByName(L"OrderDate")->AsInteger;
			oi.Type = rs->FieldByName(L"OrderType")->AsString[1];
			oi.State = rs->FieldByName(L"OrderState")->AsString[1];
			oi.CsnVol =rs->FieldByName(L"OrderQty")->AsFloat;
			oi.TrdVol =rs->FieldByName(L"ExecQty")->AsFloat;
			oi.CancelVol = rs->FieldByName(L"CancleQty")->AsFloat;
			oi.CsnPrice = rs->FieldByName(L"OrderPrice")->AsFloat;
			oi.TrdPrice = rs->FieldByName(L"ExecAvgPrice")->AsFloat;
			lstrcpyn(oi.Account,rs->FieldByName(L"Account")->AsString.c_str(),ACC_LEN);
			lstrcpyn(oi.SeqNum, oi.ContractID,SEQ_LEN);
			i++;
			rs->Next();
		}
	}
	catch( Exception &e )
	{
		ODS('E',"PTSRF","GetUnfilledOrders Error,Account = %s,message is %s",acc.c_str(),e.Message.c_str());
		ret=-1;
	}
	if( rs->Active == true )
		rs->Close();
	delete rs;
	return ret;
}
