//---------------------------------------------------------------------------
#ifndef UTrdItf_TESTH
#define UTrdItf_TESTH
//---------------------------------------------------------------------------
#include "JZAPI.H"
#include "UTrdStruct.h"
#include "UTrdItfBase.h"
#include <system.hpp>
//---------------------------------------------------------------------------
class TTrdItf_TEST : public TTrdItfBase
{
private:	// User declarations
  typedef int (*TInit)(String CotID,String CotPW);  //初始化
  typedef int (*TSetAccount)(String KHBS,TAccountSort Sort,String PW);
  typedef int (*TGetBuyInfo)(String SecuID,TDealInfo &Info);   //取得买入的盘口数据
  typedef int (*TGetSellInfo)(String SecuID,TDealInfo &Info);  //取得买出的盘口数据
  typedef int (*TQryMoney)(double &Balance,double &Available); //资金查询
  typedef int (*TQryStock)(String Capital,String SecuID,int &Balance,int &Available,int &BuyFreeze,int &SellFreeze); //股份查询
  typedef int (*TQryCanBuy)(String Capital,String SecuID,double Price,int &Num); //取可买数量
  typedef int (*TQryDetail)(String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //成交查询
  typedef int (*TQryHisDetail)(String DateStr,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //历史成交查询
  typedef int (*TQryCsn)(String ContractID,TBourse Bourse,TConsignInfo &CsgInfo); //查询某个委托合同
  typedef int (*TQryCurCsn)(String Capital,TConsignInfo **CsgInfo,int &Num); //当日委托查询
  typedef int (*TQryHisCsn)(String Capital,String StartDay,String EndDay,TConsignInfo **CsgInfo,int &Num); //历史委托查询
  typedef int (*TQryCurTrd)(String Capital,TTradeInfo **TrdInfo,int &Num);   //当日成交查询
  typedef int (*TQryHisTrd)(String Capital,String StartDay,String EndDay,TTradeInfo **TrdInfo,int &Num); //历史成交查询
  typedef int (*TQryBill)(String StartDay,String EndDay,TFundInfo **FundInfo,int &Num); //查询资金流水（对帐单）
  typedef int (*TQryStocks)(String Capital,TStockInfo **StockInfo,int &Num); //查询帐号中所有的股份
  typedef int (*TBuy)(String Capital,String SecuID,double Price,int Num,char **ContractID);
  typedef int (*TSell)(String Capital,String SecuID,double Price,int Num,char **ContractID);
  typedef int (*TUndo)(String ContractID,TBourse Bourse); //委托撤单

  TInit         FInit;
  TSetAccount   FSetAccount;
  TGetBuyInfo   FGetBuyInfo;
  TGetSellInfo  FGetSellInfo;
  TQryMoney     FQryMoney;
  TQryStock     FQryStock;
  TQryCanBuy    FQryCanBuy;
  TQryDetail    FQryDetail;
  TQryHisDetail FQryHisDetail;
  TQryCsn       FQryCsn;
  TQryCurCsn    FQryCurCsn;
  TQryHisCsn    FQryHisCsn;
  TQryCurTrd    FQryCurTrd;
  TQryHisTrd    FQryHisTrd;
  TQryBill      FQryBill;
  TQryStocks    FQryStocks;
  TBuy          FBuy;
  TSell         FSell;
  TUndo         FUndo;

  HINSTANCE FHandle;

  int  Init();  //初始化
  int  SetAccount(); //设置帐号

  //////查询函数//////
  int  GetTrdInfo();   //取得盘口数据
  int  QryMoney();     //资金查询
  int  QryStock();     //股份查询
  int  QryCanBuy();    //取可买数量
  int  QryDetail();    //成交查询
  int  QryHisDetail(); //历史成交查询
  int  QryCsn();       //查询某个委托合同
  int  QryCurCsn();    //当日委托查询
  int  QryHisCsn();    //历史委托查询
  int  QryCurTrd();    //当日成交查询
  int  QryHisTrd();    //历史成交查询
  int  QryBill();      //查询资金流水（对帐单）
  int  QryStocks();    //查询帐号中所有的股份

  virtual bs_type ConvertType(char *type)
  {
    return btNo;
  }

  virtual wt_state ConvertState(char *state)
  {
    return wsno;
  }

  //////交易函数/////
  int  Buy();
  int  Sell();
  int  Undo(); //委托撤单

public:		// User declarations
  TTrdItf_TEST();
  virtual  ~TTrdItf_TEST();

  void CloseLink(void)
  {
    return;
  }

};
//---------------------------------------------------------------------------
#endif


