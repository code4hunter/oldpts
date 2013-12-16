//---------------------------------------------------------------------------
#ifndef uPTSTransH
#define uPTSTransH

#include <classes.hpp>

#include "PTSSMOLib_OCX.h"
#include "PTSSMOLib_TLB.h"

#include "UTrdStruct.h"
#include "UTrdStruct_Rm.h"
//---------------------------------------------------------------------------
class TPTSItf
{
private:
	TPTSSession * FSession;
	TTradeCoreSvc *FTCS;
	ITradeCoreSvc2*FTCS2;
	TAccountInfo  FAccInfo;
	TAccountSort  FAccSort;

	WideString FTrader;
	WideString FServerName;
	WideString FDomain;

	IAccount *FAccount;
	TInterfaceError FError;
protected:

public:
	TPTSItf();
	~TPTSItf();

	void init(WideString domain,WideString server,WideString trader);
	int login(WideString account,WideString password,TAccountSort as);
	int QryMoney(double &Balance,double &Available);
	int QryDetail(char * ContractID,TBourse Bourse,
									double &Price,int &Num,int &UndoNum);
	int QryCurCsn(TConsignInfo **CsgInfo,int &Num);

	int QryCurTrd(TTradeInfo **TrdInfo,int &Num) ;
	int QryStocks(TStockInfo **StockInfo,int &Num,TBourse Bourse);
	int BuyOrSell(WideString SecuID,double Price,int Num,WideString &ContractID,
				short type,TcOrderSide side) ;
	int Undo(WideString ContractID,TBourse Bourse) ;
	int GetCapitalAcc(WideString &Acc);
	int SetAccInfo(TAccountInfo *AccInfo);
	int GetAccInfo(TAccountInfo *AccInfo) ;
	void FreeAnswer(void *mem) ;

	int GetLastError(char *ErrorText,char *Sender);
	void SetLastError(char* ErrorText,long errcode);
};

#endif
