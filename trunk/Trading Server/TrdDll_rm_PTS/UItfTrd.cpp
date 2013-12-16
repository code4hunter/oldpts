//---------------------------------------------------------------------------
#include "UItfTrd.h"
//---------------------------------------------------------------------------
#define CHECK_HANDLE(x) if(NULL==x) return -1;

TItfTrd::TItfTrd(bool simulation,void  * ei,char *ShareName)
{
	FSimulation=simulation;
	FEI=ei;
	//strcpy(FShareName,ShareName);

	FNewTrdCot       =NULL;
	FDelTrdCot       =NULL;
	FInit            =NULL;
	FSetAccount      =NULL;
	FQryMoney        =NULL;
	FQryStock        =NULL;
	FCanBuy          =NULL;
	FQryDetail       =NULL;
	FQryHisDetail    =NULL;
	FQryCsn          =NULL;
	FQryCurCsn       =NULL;
	FQryHisCsn       =NULL;
	FQryCurTrd       =NULL;
	FQryHisTrd       =NULL;
	FQryBill         =NULL;
	FQryStocks       =NULL;
	FBuy             =NULL;
	FSell            =NULL;
	FUndo            =NULL;
	FGetCapitalAcc   =NULL;
	FSetAccInfo      =NULL;
	FGetAccInfo      =NULL;
	FFreeAnswer      =NULL;
	FNewTrdCotS      =NULL;
	FBuyS            =NULL;
	FSellS           =NULL;
	FGetLastError    =NULL;

	if(FSimulation)
	{
		FDllHandle = LoadLibrary("StkTrdItf.dll");

		if(!FDllHandle) 
		{
			MessageBox(NULL,"导入动态链接库\"StkTrdItf.dll\"失败！将退出应用程序。","ERROR!",MB_ICONERROR);
			return;
		}
		else
		{
			FNewTrdCotS    = (TNewTrdCotS)GetProcAddress(FDllHandle,"_NewTrdCotS");
			FDelTrdCot     = (TDelTrdCot)GetProcAddress(FDllHandle,"_DelTrdCotS");
			FInit          = (TInit)GetProcAddress(FDllHandle,"_InitS");
			FSetAccount    = (TSetAccount)GetProcAddress(FDllHandle,"_SetAccountS");
			FQryMoney      = (TQryMoney)GetProcAddress(FDllHandle,"_QryMoneyS");
			FQryStock      = (TQryStock)GetProcAddress(FDllHandle,"_QryStockS");
			FCanBuy        = (TCanBuy)GetProcAddress(FDllHandle,"_CanBuyS");
			FQryDetail     = (TQryDetail)GetProcAddress(FDllHandle,"_QryDetailS");
			FQryHisDetail  = (TQryHisDetail)GetProcAddress(FDllHandle,"_QryHisDetailS");
			FQryCsn        = (TQryCsn)GetProcAddress(FDllHandle,"_QryCsnS");
			FQryCurCsn     = (TQryCurCsn)GetProcAddress(FDllHandle,"_QryCurCsnS");
			FQryHisCsn     = (TQryHisCsn)GetProcAddress(FDllHandle,"_QryHisCsnS");
			FQryCurTrd     = (TQryCurTrd)GetProcAddress(FDllHandle,"_QryCurTrdS");
			FQryHisTrd     = (TQryHisTrd)GetProcAddress(FDllHandle,"_QryHisTrdS");
			FQryBill       = (TQryBill)GetProcAddress(FDllHandle,"_QryBillS");
			FQryStocks     = (TQryStocks)GetProcAddress(FDllHandle,"_QryStocksS");
			FBuyS          = (TBuyS)GetProcAddress(FDllHandle,"_BuyS");
			FSellS         = (TSellS)GetProcAddress(FDllHandle,"_SellS");
			FUndo          = (TUndo)GetProcAddress(FDllHandle,"_UndoS");
			FSetAccInfo    = (TSetAccInfo)GetProcAddress(FDllHandle,"_SetAccInfoS");
			FGetAccInfo    = (TGetAccInfo)GetProcAddress(FDllHandle,"_GetAccInfoS");
			FFreeAnswer    = (TFreeAnswer)GetProcAddress(FDllHandle,"_FreeAnswerS");
			FGetCapitalAcc = (TGetCapitalAcc)GetProcAddress(FDllHandle,"_GetCapitalAccS");
		}
	}
	else
	{
		FDllHandle = LoadLibrary("PTrdDll_RM.dll");

		if(!FDllHandle)
		{
			MessageBox(NULL,"导入动态链接库\"PTrdDll_RM.dll\"失败！将退出应用程序。","ERROR!",MB_ICONERROR);
			return;
		}
		else
		{
			FNewTrdCot     = (TNewTrdCot)GetProcAddress(FDllHandle,"_NewTrdCot");
			FDelTrdCot     = (TDelTrdCot)GetProcAddress(FDllHandle,"_DelTrdCot");
			FInit          = (TInit)GetProcAddress(FDllHandle,"_Init");
			FSetAccount    = (TSetAccount)GetProcAddress(FDllHandle,"_SetAccount");
			FQryMoney      = (TQryMoney)GetProcAddress(FDllHandle,"_QryMoney");
			FQryStock      = (TQryStock)GetProcAddress(FDllHandle,"_QryStock");
			FCanBuy        = (TCanBuy)GetProcAddress(FDllHandle,"_CanBuy");
			FQryDetail     = (TQryDetail)GetProcAddress(FDllHandle,"_QryDetail");
			FQryHisDetail  = (TQryHisDetail)GetProcAddress(FDllHandle,"_QryHisDetail");
			FQryCsn        = (TQryCsn)GetProcAddress(FDllHandle,"_QryCsn");
			FQryCurCsn     = (TQryCurCsn)GetProcAddress(FDllHandle,"_QryCurCsn");
			FQryHisCsn     = (TQryHisCsn)GetProcAddress(FDllHandle,"_QryHisCsn");
			FQryCurTrd     = (TQryCurTrd)GetProcAddress(FDllHandle,"_QryCurTrd");
			FQryHisTrd     = (TQryHisTrd)GetProcAddress(FDllHandle,"_QryHisTrd");
			FQryBill       = (TQryBill)GetProcAddress(FDllHandle,"_QryBill");
			FQryStocks     = (TQryStocks)GetProcAddress(FDllHandle,"_QryStocks");
			FBuy           = (TBuy)GetProcAddress(FDllHandle,"_Buy");
			FSell          = (TSell)GetProcAddress(FDllHandle,"_Sell");
			FUndo          = (TUndo)GetProcAddress(FDllHandle,"_Undo");
			FGetCapitalAcc = (TGetCapitalAcc)GetProcAddress(FDllHandle,"_GetCapitalAcc");
			FSetAccInfo    = (TSetAccInfo)GetProcAddress(FDllHandle,"_SetAccInfo");
			FGetAccInfo    = (TGetAccInfo)GetProcAddress(FDllHandle,"_GetAccInfo");
			FFreeAnswer    = (TFreeAnswer)GetProcAddress(FDllHandle,"_FreeAnswer");
			FGetLastError  = (TGetLastError)GetProcAddress(FDllHandle,"_GetLastItfError");
		}
	}

	if(!FNewTrdCot && !FSimulation || !FNewTrdCotS && FSimulation|| !FDelTrdCot ||
		!FInit || !FSetAccount || !FQryMoney ||
		!FQryStock || !FCanBuy || !FQryDetail || !FQryCsn || !FQryCurCsn || !FQryHisCsn ||
		!FQryCurTrd || !FQryHisTrd || (!FBuy) && !FSimulation || (!FSell) && !FSimulation ||
		(!FBuyS) && FSimulation || (!FSellS) && FSimulation ||
		!FUndo || !FQryHisDetail || !FQryBill ||
		!FSetAccInfo || !FGetAccInfo || !FQryStocks || !FFreeAnswer || !FGetCapitalAcc) 
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
#ifdef USESTRING
int  TItfTrd::Init(String CotID,String CotPW)
{
	CHECK_HANDLE(FDllHandle);
	if(!FTrdCot)
	{
		Open();
	}
	return FInit(FTrdCot,CotID,CotPW);
}
//---------------------------------------------------------------------------
int  TItfTrd::SetAccount(String Account,TAccountSort Sort,String PW/*,TAccountInfo *AccInfo*/)
{
	CHECK_HANDLE(FDllHandle);
	return FSetAccount(FTrdCot,Account,Sort,PW/*,AccInfo*/);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryStock(String SecuID,int &Balance,int &Available,
					   int &BuyFreeze,int &SellFreeze)
{
	CHECK_HANDLE(FDllHandle);
	return FQryStock(FTrdCot,SecuID,Balance,Available,BuyFreeze,SellFreeze);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryStock(String SecuID,double Price,int &Num)
{
	CHECK_HANDLE(FDllHandle);
	return FCanBuy(FTrdCot,SecuID,Price,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryDetail(String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum)
{
	CHECK_HANDLE(FDllHandle);
	return FQryDetail(FTrdCot,ContractID,Bourse,Price,Num,UndoNum);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryDetail(String DateStr,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum)
{
	CHECK_HANDLE(FDllHandle);
	return FQryHisDetail(FTrdCot,DateStr,ContractID,Bourse,Price,Num,UndoNum);
}
//---------------------------------------------------------------------------
int  TItfTrd::Buy(String SecuID,double Price,int Num,String &ContractID,short type)
{
	CHECK_HANDLE(FDllHandle);
	return FBuy(FTrdCot,SecuID,Price,Num,ContractID,type);
}
//---------------------------------------------------------------------------
int  TItfTrd::Sell(String SecuID,double Price,int Num,String &ContractID,short type)
{
	CHECK_HANDLE(FDllHandle);
	return FSell(FTrdCot,SecuID,Price,Num,ContractID,type);
}
//---------------------------------------------------------------------------
int  TItfTrd::Undo(String ContractID,TBourse Bourse)
{
	CHECK_HANDLE(FDllHandle);
	return FUndo(FTrdCot,ContractID,Bourse);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryCsn(String ContractID,TBourse Bourse,TConsignInfo &CsgInfo)
{
	CHECK_HANDLE(FDllHandle);
	return FQryCsn(FTrdCot,ContractID,Bourse,CsgInfo);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryHisCsn(String StartDay,String EndDay,TConsignInfo **CsgInfo,int &Num)
{
	*CsgInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryHisCsn(FTrdCot,StartDay,EndDay,CsgInfo,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryHisTrd(String StartDay,String EndDay,TTradeInfo **TrdInfo,int &Num)
{
	*TrdInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryHisTrd(FTrdCot,StartDay,EndDay,TrdInfo,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryBill(String StartDay,String EndDay,TFundInfo **FundInfo,int &Num)
{
	*FundInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryBill(FTrdCot,StartDay,EndDay,FundInfo,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::GetCapitalAcc(String &Acc)
{
	CHECK_HANDLE(FDllHandle);
	return FGetCapitalAcc(FTrdCot,Acc);
}

/////////////////////////////////////////////////////////////////////////////////////
#else
int  TItfTrd::Init(char *  CotID,char *  CotPW)
{
	CHECK_HANDLE(FDllHandle);
	if(!FTrdCot)
	{
		Open();
	}
	return FInit(FTrdCot,CotID,CotPW);
}
//---------------------------------------------------------------------------
int  TItfTrd::SetAccount(char *  Account,TAccountSort Sort,char *  PW/*,TAccountInfo *AccInfo*/)
{
	CHECK_HANDLE(FDllHandle);
	return FSetAccount(FTrdCot,Account,Sort,PW/*,AccInfo*/);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryStock(char *  SecuID,int &Balance,int &Available,
					   int &BuyFreeze,int &SellFreeze)
{
	CHECK_HANDLE(FDllHandle);
	return FQryStock(FTrdCot,SecuID,Balance,Available,BuyFreeze,SellFreeze);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryStock(char *  SecuID,double Price,int &Num)
{
	CHECK_HANDLE(FDllHandle);
	return FCanBuy(FTrdCot,SecuID,Price,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryDetail(char *  ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum)
{
	CHECK_HANDLE(FDllHandle);
	return FQryDetail(FTrdCot,ContractID,Bourse,Price,Num,UndoNum);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryDetail(char *  DateStr,char *  ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum)
{
	CHECK_HANDLE(FDllHandle);
	return FQryHisDetail(FTrdCot,DateStr,ContractID,Bourse,Price,Num,UndoNum);
}
//---------------------------------------------------------------------------
int  TItfTrd::Buy(char *  SecuID,double Price,int Num,char *  ContractID,short type)
{
	CHECK_HANDLE(FDllHandle);
	if(this->FSimulation)
		return FBuyS(FTrdCot,SecuID,Price,Num,ContractID,FEI);
	else
		return FBuy(FTrdCot,SecuID,Price,Num,ContractID,type);
}
//---------------------------------------------------------------------------
int  TItfTrd::Sell(char *  SecuID,double Price,int Num,char *  ContractID,short type)
{
	CHECK_HANDLE(FDllHandle);
	if(this->FSimulation)
		return FSellS(FTrdCot,SecuID,Price,Num,ContractID,FEI);
	else
		return FSell(FTrdCot,SecuID,Price,Num,ContractID,type);
}
//---------------------------------------------------------------------------
int  TItfTrd::Undo(char *  ContractID,TBourse Bourse)
{
	CHECK_HANDLE(FDllHandle);
	return FUndo(FTrdCot,ContractID,Bourse);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryCsn(char *  ContractID,TBourse Bourse,TConsignInfo &CsgInfo)
{
	CHECK_HANDLE(FDllHandle);
	return FQryCsn(FTrdCot,ContractID,Bourse,CsgInfo);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryHisCsn(char *  StartDay,char *  EndDay,TConsignInfo **CsgInfo,int &Num)
{
	*CsgInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryHisCsn(FTrdCot,StartDay,EndDay,CsgInfo,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryHisTrd(char *  StartDay,char *  EndDay,TTradeInfo **TrdInfo,int &Num)
{
	*TrdInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryHisTrd(FTrdCot,StartDay,EndDay,TrdInfo,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryBill(char *  StartDay,char *  EndDay,TFundInfo **FundInfo,int &Num)
{
	*FundInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryBill(FTrdCot,StartDay,EndDay,FundInfo,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::GetCapitalAcc(char * Acc)
{
	CHECK_HANDLE(FDllHandle);
	return FGetCapitalAcc(FTrdCot,Acc);
}
#endif
/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
int  TItfTrd::QryStocks(TStockInfo **StockInfo,int &Num,TBourse Bourse)
{
	*StockInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryStocks(FTrdCot,StockInfo,Num,Bourse);
}
//---------------------------------------------------------------------------
int  TItfTrd::SetAccInfo(TAccountInfo *AccInfo)
{
	CHECK_HANDLE(FDllHandle);
	return FSetAccInfo(FTrdCot,AccInfo);
}
//---------------------------------------------------------------------------
int  TItfTrd::GetAccInfo(TAccountInfo *AccInfo)
{
	CHECK_HANDLE(FGetAccInfo);
	return FGetAccInfo(FTrdCot,AccInfo);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryCurTrd(TTradeInfo **TrdInfo,int &Num)
{
	*TrdInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryCurTrd(FTrdCot,TrdInfo,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryCurCsn(TConsignInfo **CsgInfo,int &Num)
{
	*CsgInfo = NULL;
	CHECK_HANDLE(FDllHandle);
	return FQryCurCsn(FTrdCot,CsgInfo,Num);
}
//---------------------------------------------------------------------------
int  TItfTrd::QryMoney(double &Balance,double &Available)
{
	CHECK_HANDLE(FDllHandle);
	return FQryMoney(FTrdCot,Balance,Available);
}
//---------------------------------------------------------------------------
void   TItfTrd::FreeAnswer(void *mem)
{
	if(NULL==FDllHandle) return;
	FFreeAnswer(FTrdCot,mem);
}

int TItfTrd::GetLastError(char *ErrorText,char *Sender)
{
	if( FGetLastError == NULL )
	{
		lstrcpy(ErrorText,"不支持此功能");
		lstrcpy(Sender,"UItfTrd");
		return -1;
	}
	else
	{
        return FGetLastError(FTrdCot,ErrorText,Sender);
    }
}
