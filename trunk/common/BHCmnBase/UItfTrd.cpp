//---------------------------------------------------------------------------
#include "UItfTrd.h"
//---------------------------------------------------------------------------
#define CHECK_HANDLE(x) if(NULL==x) return -1;

TItfTrd::TItfTrd(const char *DllName)
{
	FNewTrdCot     = NULL;
	FDelTrdCot     = NULL;
	FInit          = NULL;
	FLogin         = NULL;
	FQryMoney      = NULL;
	FQryOrder      = NULL;
	FQryTrade      = NULL;
	FQryStocks     = NULL;
	FGetAccInfo    = NULL;
	FFreeAnswer    = NULL;
	FOrder         = NULL;
	FGetLastError  = NULL;

	if( DllName == NULL || strlen(DllName)== 0)
		FDllHandle = LoadLibrary("PTrdDll.dll");
	else
		FDllHandle = LoadLibrary(DllName);

	if(!FDllHandle)
	{
		MessageBox(NULL,"导入动态链接库\"PTrdDll.dll\"失败！将退出应用程序。","ERROR!",MB_ICONERROR);
		return;
	}
	else
	{
		FNewTrdCot     = (TNewTrdCot)GetProcAddress(FDllHandle,"_NewTrdCot");
		FDelTrdCot     = (TDelTrdCot)GetProcAddress(FDllHandle,"_DelTrdCot");
		FInit          = (TInit)GetProcAddress(FDllHandle,"_Init");
		FLogin         = (TLogin)GetProcAddress(FDllHandle,"_Login");
		FQryMoney      = (TQryMoney)GetProcAddress(FDllHandle,"_QryMoney");
		FQryOrder      = (TQryOrder)GetProcAddress(FDllHandle,"_QryOrder");
		FQryTrade      = (TQryTrade)GetProcAddress(FDllHandle,"_QryTrade");
		FQryStocks     = (TQryStocks)GetProcAddress(FDllHandle,"_QryStocks");
		FOrder         = (TOrder)GetProcAddress(FDllHandle,"_Order");
		FUndo          = (TUndo)GetProcAddress(FDllHandle,"_Undo");
		FGetAccInfo    = (TGetAccInfo)GetProcAddress(FDllHandle,"_GetAccInfo");
		FFreeAnswer    = (TFreeAnswer)GetProcAddress(FDllHandle,"_FreeAnswer");
		FGetLastError  = (TGetLastError)GetProcAddress(FDllHandle,"_GetLastItfError");
	}

	if(
      	FNewTrdCot   == NULL ||
				FDelTrdCot   == NULL ||
				FInit        == NULL ||
				FLogin       == NULL ||
				FQryMoney    == NULL ||
				FQryOrder    == NULL ||
				FQryTrade    == NULL ||
				FQryStocks   == NULL ||
				FOrder       == NULL ||
				FUndo        == NULL ||
				FGetAccInfo  == NULL ||
				FFreeAnswer  == NULL ||
				FGetLastError== NULL
	)
	{
		MessageBox(NULL,"动态链接库某些函数不存在！","ERROR!",MB_ICONERROR);
	}

	FTrdCot=NULL;
}
//---------------------------------------------------------------------------
TItfTrd::~TItfTrd()
{
	if(FDllHandle)
	{
		Close();
		FreeLibrary(FDllHandle);
	}
}
//---------------------------------------------------------------------------
int  TItfTrd::Init(const char * ServerInfo)
{
	CHECK_HANDLE(FDllHandle);
	if(!FTrdCot)
	{
		Open();
	}
	return FInit(FTrdCot,ServerInfo);
}
//---------------------------------------------------------------------------
int  TItfTrd::Login(const char * Account,account_type Type,const char* PW)
{
	CHECK_HANDLE(FDllHandle);
	return FLogin(FTrdCot,Account,Type,PW);
}
//---------------------------------------------------------------------------
int  TItfTrd::Order(const char* SecuID,double Price,int Num,market_type Market,order_type OrdType,char * ContractID,int ContractLength)
{
	CHECK_HANDLE(FDllHandle);
	return FOrder(FTrdCot,SecuID,Price,Num,Market,OrdType,ContractID,ContractLength);
}
//---------------------------------------------------------------------------
int  TItfTrd::Undo(const char* ContractID, market_type Market)
{
	CHECK_HANDLE(FDllHandle);
	return FUndo(FTrdCot,ContractID,Market);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryStocks(market_type Market,TStockInfo **StockInfo,int &Num)
{
	*StockInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryStocks(FTrdCot,Market,StockInfo,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::GetAccInfo(TAccountInfo &AccInfo)
{
	CHECK_HANDLE(FGetAccInfo);
	return FGetAccInfo(FTrdCot,AccInfo);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryOrder(const char* OrdId,const char * PosStr,TOrderInfo **OrdInfo,int &Num)
{
	*OrdInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryOrder(FTrdCot,OrdId,PosStr,OrdInfo,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryTrade(const char*  OrdId,const char* PosStr,TTradeInfo **TrdInfo,int &Num)
{
	*TrdInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryTrade(FTrdCot,OrdId,PosStr,TrdInfo,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryMoney(money_type MoneyType,TMoneyInfo &MoneyInfo)
{
	CHECK_HANDLE(FDllHandle);
	return FQryMoney(FTrdCot,MoneyType,MoneyInfo);
}
//---------------------------------------------------------------------------
void   TItfTrd::FreeAnswer(void *mem)
{
	if(NULL==FDllHandle) return;
	FFreeAnswer(FTrdCot,mem);
}

int TItfTrd::GetLastError(char *ErrorText,int ErrorLength,char *Sender,int SenderLength)
{
	if( FGetLastError == NULL )
	{
		lstrcpyn(ErrorText,"不支持此功能",ErrorLength);
		lstrcpyn(Sender,"UItfTrd",SenderLength);
		return -1;
	}
	else
	{
		return FGetLastError(FTrdCot,ErrorText,ErrorLength,Sender,SenderLength);
	}
}
