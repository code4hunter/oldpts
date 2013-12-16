//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#include "UTrdCot_Rm.h"
#include "USetup.h"
               
#define DLLEXP extern "C" __declspec(dllexport)

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
  return 1;
}

DLLEXP void * NewTrdCot()
{
	return new TTrdCot_Rm();
}
//---------------------------------------------------------------------------
DLLEXP void  DelTrdCot(void *TrdCot)
{
  if(TrdCot)
    delete (TTrdCot*)TrdCot;
}
//---------------------------------------------------------------------------

DLLEXP
int Init(void *TrdCot,const char * ServerInfo)
{
  if(!TrdCot) return -100;
	if( ServerInfo == NULL || strlen(ServerInfo)==0 )
  {
    TStp stp(IncludeTrailingBackslash(ExtractFilePath(Application->ExeName))+ "PTrdDll.ini");
    ((TTrdCot_Rm*)TrdCot)->SetRemote(stp.RM_Svr.c_str(),stp.RM_Port);
  }
	else
	{
		// serverinfo = IP:PORT
		char svrinfo[255];
		strncpy(svrinfo,ServerInfo,254);
		char *pport = strstr(svrinfo,":");
		if( pport!= NULL )
		{
			pport[0] = 0;
			pport++;
		}
		String ip =  svrinfo;
		int port = atoi(pport);
		((TTrdCot_Rm*)TrdCot)->SetRemote(ip.c_str(), port);
	}
	return ((TTrdCot*)TrdCot)->Init();
}

//---------------------------------------------------------------------------
DLLEXP
int Login(void *TrdCot,const char * Account,account_type Type,const char* PW)
{
	if(!TrdCot) return -100;
	return ((TTrdCot*)TrdCot)->Login(Account,Type,PW);
}
//---------------------------------------------------------------------------
DLLEXP
int QryMoney(void *TrdCot,money_type MoneyType,TMoneyInfo &MoneyInfo)
{
  if(!TrdCot) return -100;
	return ((TTrdCot*)TrdCot)->QryMoney(MoneyType,MoneyInfo);
}
//---------------------------------------------------------------------------
DLLEXP
int QryOrder(void *TrdCot,const char* OrdId,const char * PosStr,TOrderInfo **OrdInfo,int &Num)
{
  if(!TrdCot) return -100;
	return ((TTrdCot*)TrdCot)->QryOrder(OrdId,PosStr,OrdInfo,Num);
}
//---------------------------------------------------------------------------
DLLEXP
int QryTrade(void *TrdCot,const char*  OrdId,const char* PosStr,TTradeInfo **TrdInfo,int &Num)
{
  if(!TrdCot) return -100;
	return ((TTrdCot*)TrdCot)->QryTrade(OrdId,PosStr,TrdInfo,Num);
}
//---------------------------------------------------------------------------
DLLEXP
int QryStocks(void *TrdCot,market_type Market,TStockInfo **StockInfo,int &Num)
{
  if(!TrdCot) return -100;
  return ((TTrdCot*)TrdCot)->QryStocks(Market,StockInfo,Num);
}
//---------------------------------------------------------------------------
DLLEXP
int Order( void *TrdCot,const char* SecuID,
												double Price,
												int Num,
												market_type Market,
												order_type OrdType,
												char * ContractID,int ContractLength)
{
  if(!TrdCot) return -100;
  String tmp;
	int ret= ((TTrdCot*)TrdCot)->Order(SecuID,Price,Num,Market,OrdType,tmp);
	strncpy(ContractID,tmp.c_str(),ContractLength);
	return ret;
}

DLLEXP
int Undo( void *TrdCot,const char* ContractID, market_type Market)
{
  if(!TrdCot) return -100;
	return ((TTrdCot*)TrdCot)->Undo(ContractID,Market);
}

DLLEXP
int  GetAccInfo(void *TrdCot,TAccountInfo &AccInfo)
{
  if(!TrdCot) return -100;
	return ((TTrdCot*)TrdCot)->GetAccInfo(AccInfo);
}
//---------------------------------------------------------------------------
DLLEXP
void FreeAnswer(void *TrdCot,void *mem)
{
  if(!TrdCot) return;
  ((TTrdCot*)TrdCot)->FreeAnswer(mem);
}

DLLEXP
int GetLastItfError(void *TrdCot,char *ErrorText,int ErrorLength,char *Sender,int SenderLength)
{
	if(!TrdCot)
  {
    lstrcpy(Sender,"PTrdDll_RM");
		lstrcpy(ErrorText,"未建立接口实例");
		return -100;
	}

	String  err,snd;
	int ret= ((TTrdCot*)TrdCot)->GetLastError(err,snd);

	strncpy(ErrorText,err.c_str(),ErrorLength);
	strncpy(Sender,snd.c_str(),SenderLength);

	return ret;
}
