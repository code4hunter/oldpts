//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include <IniFiles.hpp>
#include "UTrdStruct_Rm.h"
#include "uPTSTrans.h"
#include "UItfTrd.h"

#pragma hdrstop
               
#define DLLEXP extern "C" __declspec(dllexport)

#pragma argsused


int g_type = 0;    // RM = 0 ,PTS = 1;

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	switch ( reason )
	{
		case DLL_PROCESS_ATTACH:
		{
			char szFile[MAX_PATH+1];
			String cfg;
			int ithreading = -1;
			GetModuleFileName(NULL,szFile,MAX_PATH);
			TIniFile * pini = new TIniFile(ExtractFilePath(szFile) + "PTrdDll.ini");
			try
			{
				cfg = pini->ReadString("DLL","dll_type","RM");
				ithreading = pini->ReadInteger("PTS","Threading",0);
			}
			catch(...)
			{
			}
			delete pini;

			if( CompareText(cfg,"PTS") == 0 )
				g_type = 1;
			else
				g_type = 0;

			if(g_type == 1)
			{
				if( ithreading == 0 )
					CoInitializeEx(NULL,COINIT_MULTITHREADED);
				else
					CoInitialize(NULL);
			}
		}
		break;
		case DLL_PROCESS_DETACH:
			if(g_type == 1)
    		CoUninitialize();
		break;
	}

	return 1;
}

DLLEXP void * NewTrdCot()
{
	if( g_type == 1 )
		return new TPTSItf();
	else
		return new TItfTrd(false,NULL,NULL);
}
//---------------------------------------------------------------------------
DLLEXP void  DelTrdCot(void *PTSItf)
{
	if(PTSItf)
		if( g_type == 1 )
			delete (TPTSItf*)PTSItf;
		else
			delete (TItfTrd*)PTSItf;
}
//---------------------------------------------------------------------------

#ifdef USESTRING
DLLEXP
int Init(void *PTSItf,String CotID,String CotPW)
{
	return -100;
}
#else
DLLEXP
int Init(void *PTSItf,char * CotID,char * CotPW)
{
	if( g_type == 1 )
	{
	//载入配置文件域和服务器
	WideString domain,server,trader;
	String cfg = CotID;

	if( cfg.Length() <= 0 )
	{
		char szFile[MAX_PATH+1];
		GetModuleFileName(NULL,szFile,MAX_PATH);
		TIniFile * pini = new TIniFile(ExtractFilePath(szFile) + "PTrdDll.ini");
		try
		{
			cfg = pini->ReadString("PTS","PTS_Setup","");
		}
		catch(...)
		{
		}
		delete pini;
	}

	if( cfg.Length() > 0  )
	{

		int ifield = 0;
		char field[100];
		int index=0;
		int count = cfg.Length();
		for( int i=1;i<=count+1;i++)
		{
			if(i==count+1 || cfg[i]==',')
			{
				field[index]=0;
				switch (ifield++ )
				{
					case 0: domain=WideString(field);
					break;
					case 1: server=WideString(field);
					break;
					case 2: trader=WideString(field);
					break;
				}

				index = 0;
			}
			else
			{
				if( index<100 )
					field[index++]=cfg[i];
			}
		}

		((TPTSItf*)PTSItf)->init(domain,server,trader);
	}

	return 0;
	}
	else return ((TItfTrd*)PTSItf)->Init(CotID, CotPW);
}
#endif
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int SetAccount(void *PTSItf,String Account,TAccountSort Sort,String PW)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int SetAccount(void *PTSItf,char* Account,TAccountSort Sort,char* PW)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
		return ((TPTSItf*)PTSItf)->login(Account,PW,Sort);
	else
		return ((TItfTrd*)PTSItf)->SetAccount(Account,Sort,PW);
}
#endif
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int GetBuyInfo(void *PTSItf,String SecuID,TDealInfo &Info)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int GetBuyInfo(void *PTSItf,char * SecuID,TDealInfo &Info)
{
	if(!PTSItf) return -100;
	return -1;
}
#endif
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int GetSellInfo(void *PTSItf,String SecuID,TDealInfo &Info)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int GetSellInfo(void *PTSItf,char * SecuID,TDealInfo &Info)
{
	if(!PTSItf) return -100;
	return -1;
}
#endif
//---------------------------------------------------------------------------
DLLEXP
int QryMoney(void *PTSItf,double &Balance,double &Available)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
		return ((TPTSItf*)PTSItf)->QryMoney(Balance,Available);
	else
		return ((TItfTrd*)PTSItf)->QryMoney(Balance,Available);
}
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int QryStock(void *PTSItf,String SecuID,int &Balance,int &Available,
  int &BuyFreeze,int &SellFreeze)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int QryStock(void *PTSItf,char * SecuID,int &Balance,int &Available,
  int &BuyFreeze,int &SellFreeze)
{
	if(!PTSItf) return -100;
	return -1;
}
#endif
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int CanBuy(void *PTSItf,String SecuID,double Price,int &Num)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int CanBuy(void *PTSItf,char * SecuID,double Price,int &Num)
{
	if(!PTSItf) return -100;
	return -1;
}
#endif
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int QryDetail(void *PTSItf,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int QryDetail(void *PTSItf,char * ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
		return ((TPTSItf*)PTSItf)->QryDetail(ContractID,Bourse,Price,Num,UndoNum);
	else
		return ((TItfTrd*)PTSItf)->QryDetail(ContractID,Bourse,Price,Num,UndoNum);
}
#endif
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int QryHisDetail(void *PTSItf,String DateStr,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int QryHisDetail(void *PTSItf,char* DateStr,char * ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum)
{
	if(!PTSItf) return -100;
	return -1;
}
#endif
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int QryCsn(void *PTSItf,String ContractID,TBourse Bourse,TConsignInfo &CsgInfo)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int QryCsn(void *PTSItf,char * ContractID,TBourse Bourse,TConsignInfo &CsgInfo)
{
	if(!PTSItf) return -100;
	return -1;
}
#endif
//---------------------------------------------------------------------------
DLLEXP
int QryCurCsn(void *PTSItf,TConsignInfo **CsgInfo,int &Num)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
		return ((TPTSItf*)PTSItf)->QryCurCsn(CsgInfo,Num);
	else
		return ((TItfTrd*)PTSItf)->QryCurCsn(CsgInfo,Num);
}
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int QryHisCsn(void *PTSItf,String StartDay,String EndDay,TConsignInfo **CsgInfo,int &Num)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int QryHisCsn(void *PTSItf,char * StartDay,char * EndDay,TConsignInfo **CsgInfo,int &Num)
{
	if(!PTSItf) return -100;
	return -1;
}
#endif
//---------------------------------------------------------------------------
DLLEXP
int QryCurTrd(void *PTSItf,TTradeInfo **TrdInfo,int &Num)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
		return ((TPTSItf*)PTSItf)->QryCurTrd(TrdInfo,Num);
	else
		return ((TItfTrd*)PTSItf)->QryCurTrd(TrdInfo,Num);
}
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int QryHisTrd(void *PTSItf,String StartDay,String EndDay,TTradeInfo **TrdInfo,int &Num)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int QryHisTrd(void *PTSItf,char * StartDay,char * EndDay,TTradeInfo **TrdInfo,int &Num)
{
	if(!PTSItf) return -100;
	return -1;
}
#endif
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int QryBill(void *PTSItf,String StartDay,String EndDay,TFundInfo **FundInfo,int &Num)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int QryBill(void *PTSItf,char * StartDay,char * EndDay,TFundInfo **FundInfo,int &Num)
{
	if(!PTSItf) return -100;
	return -1;
}
#endif
//---------------------------------------------------------------------------
DLLEXP
int QryStocks(void *PTSItf,TStockInfo **StockInfo,int &Num,TBourse Bourse)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
		return ((TPTSItf*)PTSItf)->QryStocks(StockInfo,Num,Bourse);
	else
		return ((TItfTrd*)PTSItf)->QryStocks(StockInfo,Num,Bourse);
}
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int Buy(void *PTSItf,String SecuID,double Price,int Num,String &ContractID,short type)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int Buy(void *PTSItf,char * SecuID,double Price,int Num,char* ContractID,short type)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
	{
		WideString tmp;
		int ret= ((TPTSItf*)PTSItf)->BuyOrSell(SecuID,Price,Num,tmp,type,tcOrderSideBuy);
		strcpy(ContractID,String(tmp).c_str());
		return ret;
	}
	else
		return ((TItfTrd*)PTSItf)->Buy(SecuID,Price,Num,ContractID,type);
}
#endif
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int Sell(void *PTSItf,String SecuID,double Price,int Num,String &ContractID,short type)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int Sell(void *PTSItf,char * SecuID,double Price,int Num,char * ContractID,short type)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
	{
		WideString tmp;
		int ret= ((TPTSItf*)PTSItf)->BuyOrSell(WideString(SecuID),Price,Num,tmp,type,tcOrderSideSell);
		strcpy(ContractID,String(tmp).c_str());
		return ret;
	}
	else
		return ((TItfTrd*)PTSItf)->Sell(SecuID,Price,Num,ContractID,type);
}
#endif
//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int Undo(void *PTSItf,String ContractID,TBourse Bourse)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int Undo(void *PTSItf,char * ContractID,TBourse Bourse)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
		return ((TPTSItf*)PTSItf)->Undo(ContractID,Bourse);
	else
		return ((TItfTrd*)PTSItf)->Undo(ContractID, Bourse);
}
#endif

//---------------------------------------------------------------------------
#ifdef USESTRING
DLLEXP
int GetCapitalAcc(void *PTSItf,String &Acc)
{
	if(!PTSItf) return -100;
	return -1;
}
#else
DLLEXP
int GetCapitalAcc(void *PTSItf,char *Acc)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
	{
		WideString tmp;
		int ret= ((TPTSItf*)PTSItf)->GetCapitalAcc(tmp);
		strcpy(Acc,String(tmp).c_str());
		return ret;
	}
	else
		return ((TItfTrd*)PTSItf)->GetCapitalAcc(Acc);
}
#endif
//---------------------------------------------------------------------------
DLLEXP
int SetAccInfo(void *PTSItf,TAccountInfo *AccInfo)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
		return ((TPTSItf*)PTSItf)->SetAccInfo(AccInfo);
	else
		return ((TItfTrd*)PTSItf)->SetAccInfo(AccInfo);
}
//---------------------------------------------------------------------------
DLLEXP
int  GetAccInfo(void *PTSItf,TAccountInfo *AccInfo)
{
	if(!PTSItf) return -100;
	if( g_type == 1 )
		return ((TPTSItf*)PTSItf)->GetAccInfo(AccInfo);
	else
		return ((TItfTrd*)PTSItf)->GetAccInfo(AccInfo);
}
//---------------------------------------------------------------------------
DLLEXP
void FreeAnswer(void *PTSItf,void *mem)
{
	if(!PTSItf) return;
	if( g_type == 1 )
		((TPTSItf*)PTSItf)->FreeAnswer(mem);
	else
   	((TItfTrd*)PTSItf)->FreeAnswer(mem);
}

DLLEXP
int GetLastItfError(void *PTSItf,char *ErrorText,char *Sender)
{
	if(!PTSItf)
	{
		lstrcpy(Sender,"PTrdDll");
		lstrcpy(ErrorText,"未建立接口实例");
		return -100;
	}
	if( g_type == 1 )
	{
		return ((TPTSItf*)PTSItf)->GetLastError(ErrorText,Sender);
	}
	else
		return ((TItfTrd*)PTSItf)->GetLastError(ErrorText,Sender);
}

