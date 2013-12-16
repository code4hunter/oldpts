#ifndef TrdItfH
#define TrdItfH

#ifndef DLLEXP
#define DLLEXP	__declspec(dllexport)
#endif

#include "UTrdStruct.h"
//#include "UPacketPar.h"
//#include "EtfRec.h"
//extern "C" DLLEXP void SetHQ(TPacketParser * HQ);
/*
extern "C" DLLEXP void* NewTrdCot();
extern "C" DLLEXP void  DelTrdCot(void *TrdCot);
extern "C" DLLEXP int Init(void *TrdCot,char* CotID,char* CotPW);
extern "C" DLLEXP int SetAccount(void *TrdCot,char * Account,TAccountSort Sort,
                char * PW);
extern "C" DLLEXP int QryMoney(void *TrdCot,double *Balance,double &Available);
extern "C" DLLEXP int QryStock(void *TrdCot,char* SecuID,int &Balance,
                int &Available,int &BuyFreeze,int &SellFreeze);
extern "C" DLLEXP int CanBuy(void *TrdCot,char *SecuID,double Price,int &Num);
extern "C" DLLEXP int QryDetail(void *TrdCot,char *ContractID,TBourse Bourse,
                double &Price,int &Num,int &UndoNum);
extern "C" DLLEXP int QryHisDetail(void *TrdCot,char *DateStr,char* ContractID,
                TBourse Bourse,double &Price,int &Num,int &UndoNum);
extern "C" DLLEXP int QryCsn(void *TrdCot,char* ContractID,TBourse Bourse,
                TConsignInfo &CsgInfo);
extern "C" DLLEXP int QryCurCsn(void *TrdCot,TConsignInfo **CsgInfo,int &Num);
extern "C" DLLEXP int QryHisCsn(void *TrdCot,char* StartDay,char* EndDay,
                          TConsignInfo **CsgInfo,int &Num);
extern "C" DLLEXP int QryCurTrd(void *TrdCot,TTradeInfo **TrdInfo,int &Num);
extern "C" DLLEXP int QryHisTrd(void *TrdCot,char* StartDay,char* EndDay,
                          TTradeInfo **TrdInfo,int &Num);
extern "C" DLLEXP int QryBill(void *TrdCot,char* StartDay,char* EndDay,
                        TFundInfo **FundInfo,int &Num);
extern "C" DLLEXP int QryStocks(void *TrdCot,TStockInfo **StockInfo,int &Num);
extern "C" DLLEXP int Buy(void *TrdCot,char* SecuID,double Price,int Num,
              char **ContractID);
extern "C" DLLEXP int Sell(void *TrdCot,char* SecuID,double Price,int Num,
              char **ContractID);
extern "C" DLLEXP int Undo(void *TrdCot,char* ContractID,TBourse Bourse);
//extern "C" DLLEXP int SynBuy(void *TrdCot,char *SecuID,double &Price,int &Num,char **ContractID,int MilliSeconds);
//extern "C" DLLEXP int SynSell(void *TrdCot,char *SecuID,double &Price,int &Num,char **ContractID,int MilliSeconds);
//extern "C" DLLEXP int SynUndo(void *TrdCot,char *ContractID,TBourse Bourse,int MilliSeconds);
extern "C" DLLEXP int SetAccInfo(void *TrdCot,TAccountInfo *AccInfo);
extern "C" DLLEXP int GetAccInfo(void *TrdCot,TAccountInfo *AccInfo);
*/
//------------------------------------------------------------------------------
//simulation
//------------------------------------------------------------------------------

extern "C" DLLEXP void* NewTrdCotS(void  * ei,char *ShareName);
extern "C" DLLEXP void  DelTrdCotS(void *TrdCot);
extern "C" DLLEXP int InitS(void *TrdCot,char* CotID,char* CotPW);
extern "C" DLLEXP int SetAccountS(void *TrdCot,char * Account,TAccountSort Sort,
                char * PW/*,
                TAccountInfo *AccInfo*/);
extern "C" DLLEXP int QryMoneyS(void *TrdCot,double *Balance,double &Available);
extern "C" DLLEXP int QryStockS(void *TrdCot,char* SecuID,int &Balance,
                int &Available,int &BuyFreeze,int &SellFreeze);
extern "C" DLLEXP int CanBuyS(void *TrdCot,char *SecuID,double Price,int &Num);
extern "C" DLLEXP int QryDetailS(void *TrdCot,char *ContractID,TBourse Bourse,
                double &Price,int &Num,int &UndoNum);
extern "C" DLLEXP int QryHisDetailS(void *TrdCot,char *DateStr,char* ContractID,
                TBourse Bourse,double &Price,int &Num,int &UndoNum);
extern "C" DLLEXP int QryCsnS(void *TrdCot,char* ContractID,TBourse Bourse,
                TConsignInfo &CsgInfo);
extern "C" DLLEXP int QryCurCsnS(void *TrdCot,TConsignInfo **CsgInfo,int &Num);
extern "C" DLLEXP int QryHisCsnS(void *TrdCot,char* StartDay,char* EndDay,
                          TConsignInfo **CsgInfo,int &Num);
extern "C" DLLEXP int QryCurTrdS(void *TrdCot,TTradeInfo **TrdInfo,int &Num);
extern "C" DLLEXP int QryHisTrdS(void *TrdCot,char* StartDay,char* EndDay,
                          TTradeInfo **TrdInfo,int &Num);
extern "C" DLLEXP int QryBillS(void *TrdCot,char* StartDay,char* EndDay,
                        TFundInfo **FundInfo,int &Num);
extern "C" DLLEXP int QryStocksS(void *TrdCot,TStockInfo **StockInfo,int &Num,TBourse Bourse);
extern "C" DLLEXP int BuyS(void *TrdCot,char* SecuID,double Price,int Num,
              char *ContractID,void  * ei);
extern "C" DLLEXP int SellS(void *TrdCot,char* SecuID,double Price,int Num,
              char *ContractID,void  * ei);
extern "C" DLLEXP int UndoS(void *TrdCot,char* ContractID,TBourse Bourse);
extern "C" DLLEXP int SetAccInfoS(void *TrdCot,TAccountInfo *AccInfo);
extern "C" DLLEXP int GetAccInfoS(void *TrdCot,TAccountInfo *AccInfo);
extern "C" DLLEXP void FreeAnswerS(void *TrdCot,void *mem);
#endif