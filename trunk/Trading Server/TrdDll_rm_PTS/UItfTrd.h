#ifndef UItfTrdH
#define UItfTrdH
//---------------------------------------------------------------------------
#include <windows.h>

#ifdef USESTRING
#include <Classes.hpp>
#endif

#include "UTrdStruct.h"
//---------------------------------------------------------------------------
class TItfTrd
{
#ifdef USESTRING
	typedef void* (*TNewTrdCot)();
	typedef void  (*TDelTrdCot)(void *TrdCot);

	typedef int (*TInit)(void *TrdCot,String CotID,String CotPW);  //初始化
	typedef int (*TSetAccount)(void *TrdCot,String Account,TAccountSort Sort,String PW/*,TAccountInfo *AccInfo*/); //设置帐号
	typedef int (*TQryMoney)(void *TrdCot,double &Balance,double &Available); //资金查询
	typedef int (*TQryStock)(void *TrdCot,String SecuID,int &Balance,int &Available,
		int &BuyFreeze,int &SellFreeze); //股份查询
	typedef int (*TCanBuy)(void *TrdCot,String SecuID,double Price,int &Num); //取可买数量
	typedef int (*TQryDetail)(void *TrdCot,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //成交查询
	typedef int (*TQryHisDetail)(void *TrdCot,String DateStr,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //成交查询
	typedef int (*TQryCsn)(void *TrdCot,String ContractID,TBourse Bourse,TConsignInfo &CsgInfo);
	typedef int (*TQryCurCsn)(void *TrdCot,TConsignInfo **CsgInfo,int &Num); //查询当日委托
	typedef int (*TQryHisCsn)(void *TrdCot,String StartDay,String EndDay,
		TConsignInfo **CsgInfo,int &Num); //查询历史委托
	typedef int (*TQryCurTrd)(void *TrdCot,TTradeInfo **TrdInfo,int &Num); //查询当日交易
	typedef int (*TQryHisTrd)(void *TrdCot,String StartDay,String EndDay,
		TTradeInfo **TrdInfo,int &Num); //查询历史交易
	typedef int (*TQryBill)(void *TrdCot,String StartDay,String EndDay,
		TFundInfo **FundInfo,int &Num);   //查询资金流水
	typedef int (*TQryStocks)(void *TrdCot,TStockInfo **StockInfo,int &Num,TBourse Bourse); //查询股份


	typedef int (*TBuy)(void *TrdCot,String SecuID,double Price,int Num,String &ContractID,short type);
	typedef int (*TSell)(void *TrdCot,String SecuID,double Price,int Num,String &ContractID,short type);
	typedef int (*TUndo)(void *TrdCot,String ContractID,TBourse Bourse); //委托撤单

	typedef int (*TSynBuy)(void *TrdCot,String SecuID,double &Price,int &Num,String &ContractID,int MilliSeconds);
	typedef int (*TSynSell)(void *TrdCot,String SecuID,double &Price,int &Num,String &ContractID,int MilliSeconds);
	typedef int (*TSynUndo)(void *TrdCot,String ContractID,TBourse Bourse,int MilliSeconds);

	typedef int (*TGetCapitalAcc)(void *TrdCot,String &Acc);
	typedef int (*TSetAccInfo)(void *TrdCot,TAccountInfo *AccInfo); //设置帐号
	typedef int (*TGetAccInfo)(void *TrdCot,TAccountInfo *AccInfo); //取得帐号信息
#else
	typedef void* (*TNewTrdCot)();
	typedef void  (*TDelTrdCot)(void *TrdCot);

	typedef int (*TInit)(void *TrdCot,char * CotID,char * CotPW);  //初始化
	typedef int (*TSetAccount)(void *TrdCot,char * Account,TAccountSort Sort,char * PW/*,TAccountInfo *AccInfo*/); //设置帐号
	typedef int (*TQryMoney)(void *TrdCot,double &Balance,double &Available); //资金查询
	typedef int (*TQryStock)(void *TrdCot,char * SecuID,int &Balance,int &Available,
		int &BuyFreeze,int &SellFreeze); //股份查询
	typedef int (*TCanBuy)(void *TrdCot,char * SecuID,double Price,int &Num); //取可买数量
	typedef int (*TQryDetail)(void *TrdCot,char * ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //成交查询
	typedef int (*TQryHisDetail)(void *TrdCot,char * DateStr,char * ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //成交查询
	typedef int (*TQryCsn)(void *TrdCot,char * ContractID,TBourse Bourse,TConsignInfo &CsgInfo);
	typedef int (*TQryCurCsn)(void *TrdCot,TConsignInfo **CsgInfo,int &Num); //查询当日委托
	typedef int (*TQryHisCsn)(void *TrdCot,char * StartDay,char * EndDay,
		TConsignInfo **CsgInfo,int &Num); //查询历史委托
	typedef int (*TQryCurTrd)(void *TrdCot,TTradeInfo **TrdInfo,int &Num); //查询当日交易
	typedef int (*TQryHisTrd)(void *TrdCot,char * StartDay,char * EndDay,
		TTradeInfo **TrdInfo,int &Num); //查询历史交易
	typedef int (*TQryBill)(void *TrdCot,char * StartDay,char * EndDay,
		TFundInfo **FundInfo,int &Num);   //查询资金流水
	typedef int (*TQryStocks)(void *TrdCot,TStockInfo **StockInfo,int &Num,TBourse Bourse); //查询股份


	typedef int (*TBuy)(void *TrdCot,char * SecuID,double Price,int Num,char * ContractID,short type);
	typedef int (*TSell)(void *TrdCot,char * SecuID,double Price,int Num,char * ContractID,short type);
	typedef int (*TUndo)(void *TrdCot,char * ContractID,TBourse Bourse); //委托撤单

	typedef int (*TSynBuy)(void *TrdCot,char * SecuID,double &Price,int &Num,char * ContractID,int MilliSeconds);
	typedef int (*TSynSell)(void *TrdCot,char * SecuID,double &Price,int &Num,char * ContractID,int MilliSeconds);
	typedef int (*TSynUndo)(void *TrdCot,char * ContractID,TBourse Bourse,int MilliSeconds);

	typedef int (*TGetCapitalAcc)(void *TrdCot,char *Acc);
	typedef int (*TSetAccInfo)(void *TrdCot,TAccountInfo *AccInfo); //设置帐号
	typedef int (*TGetAccInfo)(void *TrdCot,TAccountInfo *AccInfo); //取得帐号信息
#endif

	typedef void (*TFreeAnswer)(void *TrdCot,void *mem);
	typedef void* (*TNewTrdCotS)(void  * ei,char *ShareName);
	typedef int (*TBuyS)(void *TrdCot,char * SecuID,double Price,int Num,char * ContractID,void  * ei);
	typedef int (*TSellS)(void *TrdCot,char * SecuID,double Price,int Num,char * ContractID,void  * ei);
	typedef int (*TGetLastError)(void *TrdCot,char *ErrorText,char *Sender);
private:

	void *FEI;
	bool FSimulation;
	char FShareName[20];

	void           *FTrdCot;   //指向DLL中的柜台接口
	HINSTANCE      FDllHandle; //动态链接库句柄

	TNewTrdCot     FNewTrdCot;
	TDelTrdCot     FDelTrdCot;

	TInit          FInit;
	TSetAccount    FSetAccount;
	TQryMoney      FQryMoney;
	TQryStock      FQryStock;
	TCanBuy        FCanBuy;
	TQryDetail     FQryDetail;
	TQryHisDetail  FQryHisDetail;
	TQryCsn        FQryCsn;
	TQryCurCsn     FQryCurCsn;
	TQryHisCsn     FQryHisCsn;
	TQryCurTrd     FQryCurTrd;
	TQryHisTrd     FQryHisTrd;
	TQryBill       FQryBill;
	TQryStocks     FQryStocks;

	TBuy           FBuy;
	TSell          FSell;
	TUndo          FUndo;

	TGetCapitalAcc FGetCapitalAcc;
	TSetAccInfo    FSetAccInfo;
	TGetAccInfo    FGetAccInfo;

	TFreeAnswer    FFreeAnswer;
	TNewTrdCotS    FNewTrdCotS;
	TBuyS          FBuyS;
	TSellS         FSellS;

	TGetLastError  FGetLastError;

public:

	TItfTrd(bool simulation=false,void  * ei=NULL,char *ShareName="");
	~TItfTrd();
#ifdef USESTRING
	//在调用查询函数或交易函数之前必须先初始化柜台接口再设置帐号
	int  Init(String CotID,String CotPW);  //初始化
	int  SetAccount(String Account,TAccountSort Sort,String PW/*,TAccountInfo *AccInfo=NULL*/); //设置帐号

	//////查询函数//////
	int  QryStock(String SecuID,int &Balance,int &Available,
		int &BuyFreeze,int &SellFreeze);              //股份查询
	int  QryStock(String SecuID,double Price,int &Num); //取可买数量
	int  QryDetail(String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //成交查询
	int  QryDetail(String DateStr,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //历史成交查询
	int  QryCsn(String ContractID,TBourse Bourse,TConsignInfo &CsgInfo);
	int  QryHisCsn(String StartDay,String EndDay,TConsignInfo **CsgInfo,int &Num); //查询历史委托
	int  QryHisTrd(String StartDay,String EndDay,TTradeInfo **TrdInfo,int &Num); //查询历史交易
	int  QryBill(String StartDay,String EndDay,TFundInfo **FundInfo,int &Num);   //查询资金流水

	//////交易函数/////
	//type 0,1
	//0 表示买卖,1表示 申购赎回
	int  Buy(String SecuID,double Price,int Num,String &ContractID,short type);
	int  Sell(String SecuID,double Price,int Num,String &ContractID,short type);
	int  Undo(String ContractID,TBourse Bourse); //委托撤单

	int  GetCapitalAcc(String &Acc); //取资金帐号
#else
	//在调用查询函数或交易函数之前必须先初始化柜台接口再设置帐号
	int  Init(char *  CotID,char *  CotPW);  //初始化
	int  SetAccount(char *  Account,TAccountSort Sort,char *  PW/*,TAccountInfo *AccInfo=NULL*/); //设置帐号

	//////查询函数//////
	int  QryStock(char *  SecuID,int &Balance,int &Available,
		int &BuyFreeze,int &SellFreeze);              //股份查询
	int  QryStock(char *  SecuID,double Price,int &Num); //取可买数量
	int  QryDetail(char *  ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //成交查询
	int  QryDetail(char *  DateStr,char *  ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //历史成交查询
	int  QryCsn(char *  ContractID,TBourse Bourse,TConsignInfo &CsgInfo);
	int  QryHisCsn(char *  StartDay,char *  EndDay,TConsignInfo **CsgInfo,int &Num); //查询历史委托
	int  QryHisTrd(char *  StartDay,char *  EndDay,TTradeInfo **TrdInfo,int &Num); //查询历史交易
	int  QryBill(char *  StartDay,char *  EndDay,TFundInfo **FundInfo,int &Num);   //查询资金流水

	//////交易函数/////
  /*
  type 的用法

  type = 1  表示申购赎回命令

  set 开平标志 as a
  0  开仓
  1  平仓
  2  平今

  set 投保标志 as b
  0  投机
  1  保值

  type = a + b<<4 表示开平和投保的组合

  */
	int  Buy(char *  SecuID,double Price,int Num,char * ContractID,short type);
	int  Sell(char *  SecuID,double Price,int Num,char * ContractID,short type);
	int  Undo(char *  ContractID,TBourse Bourse); //委托撤单

	int  GetCapitalAcc(char *Acc); //取资金帐号
#endif
	int  QryStocks(TStockInfo **StockInfo,int &Num,TBourse Bourse/*=bsSH*/); //查询股份
	int  QryCurTrd(TTradeInfo **TrdInfo,int &Num);      //查询当日交易
	int  QryCurCsn(TConsignInfo **CsgInfo,int &Num);    //查询当日委托
	int  QryMoney(double &Balance,double &Available); //资金查询

	int  SetAccInfo(TAccountInfo *AccInfo); //设置帐号
	int  GetAccInfo(TAccountInfo *AccInfo); //取得帐号信息

	void  FreeAnswer(void *mem);   //释放内存

	void Open(void)
	{
		if(FTrdCot) Close();
		if(this->FSimulation)
			FTrdCot = FNewTrdCotS(FEI,FShareName);
		else
			FTrdCot = FNewTrdCot();
	}

	void Close(void)
	{
		if(FTrdCot) FDelTrdCot(FTrdCot);
		FTrdCot=NULL;
	}

	int GetLastError(char *ErrorText,char *Sender);
};
//---------------------------------------------------------------------------
#endif
