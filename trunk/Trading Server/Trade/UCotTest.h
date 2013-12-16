#ifndef UCotTestH
#define UCotTestH
//------------------------------------------------------------------------------
#include "UTrdStruct.h"
//------------------------------------------------------------------------------
typedef struct { //帐号记录
  char   Capital[13];
  double Money;
}TAccRec;
//------------------------------------------------------------------------------
typedef struct { //股份记录
  char    Capital[13];
  TBourse Bourse;
  char    SecuID[8];
  int     Balance;         //余额
  int     Available;       //可用数
  int     BuyFreeze;       //买入冻结
  int     SellFreeze;      //卖出冻结
  double  CostPrice;       //成本价
}TStockRec;
//------------------------------------------------------------------------------
typedef struct { //委托记录
  char    Capital[13];
  TBourse Bourse;
  char    ContractID[8];
  char    SecuID[8];
  char    Time[9];               //委托时间
  char    Date[9];               //委托日期
  char    Type;                  //买卖类别
  char    State;                 //撤单状态
  long    CsnVol;                //委托数量
  long    TrdVol;                //成交数量
  long    CancelVol;             //撤单数量
  double  CsnPrice;              //委托价格
  double  TrdPrice;              //成交价格
}TCmsRec;
//------------------------------------------------------------------------------
typedef struct { //交易记录
  char    Capital[13];
  TBourse Bourse;
  char    ContractID[8];
  char    SecuID[8];
  char    Time[9];               //成交时间
  char    Date[9];               //委托日期
  char    Type;                  //买卖类别
  long    Vol;                   //成交数量
  double  Price;                 //成交价格
}TBargainRec;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
class TCotTest
{
public:
  TList *FAccRec;     //帐号列表
  TList *FStockRec;   //库存列表
  TList *FCmsRec;     //委托记录列表
  TList *FBargainRec; //交易记录列表

  TStockRec*   __fastcall FindStock(String Capital,TBourse Bourse,String SecuID);    //查找库存
  
private:	// User declarations
  int SHContractID; //上交所合同序号
  int SZContractID; //深交所合同序号

  TAccRec*     __fastcall FindAcc(String Capital); //查找匹配的帐号
  TCmsRec*     __fastcall FindCms(String Date,TBourse Bourse,String ContractID);     //查找委托
  TBargainRec* __fastcall FindBargain(String Date,TBourse Bourse,String ContractID); //查找交易

  bool         __fastcall IsCan(float Rate); //判断是否可以操作

public:		// User declarations
  __fastcall TCotTest();
  __fastcall ~TCotTest();

  int __fastcall Init(String CotID,String CotPW);  //初始化
  int __fastcall SetAccount(String KHBS,TAccountSort Sort,String PW);

  //////查询函数//////
  int __fastcall GetBuyInfo(String SecuID,TDealInfo &Info);   //取得买入的盘口数据
  int __fastcall GetSellInfo(String SecuID,TDealInfo &Info);  //取得买出的盘口数据
  int __fastcall QryMoney(double &Balance,double &Available); //资金查询
  int __fastcall QryStock(String Capital,String SecuID,int &Balance,int &Available,int &BuyFreeze,int &SellFreeze); //股份查询
  int __fastcall QryStock(String Capital,String SecuID,double Price,int &Num); //取可买数量
  int __fastcall QryDetail(String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //成交查询
  int __fastcall QryDetail(String DateStr,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //历史成交查询
  int __fastcall QryCsn(String ContractID,TBourse Bourse,TConsignInfo &CsgInfo);
  int __fastcall QryCurCsn(String Capital,TConsignInfo **CsgInfo,int &Num); //当日委托查询
  int __fastcall QryHisCsn(String Capital,String StartDay,String EndDay,TConsignInfo **CsgInfo,int &Num); //历史委托查询
  int __fastcall QryCurTrd(String Capital,TTradeInfo **TrdInfo,int &Num);   //当日成交查询
  int __fastcall QryHisTrd(String Capital,String StartDay,String EndDay,TTradeInfo **TrdInfo,int &Num); //历史成交查询
  int __fastcall QryBill(String StartDay,String EndDay,TFundInfo **FundInfo,int &Num); //查询资金流水（对帐单）
  int __fastcall QryStocks(String Capital,TStockInfo **StockInfo,int &Num); //查询帐号中所有的股份

  //////交易函数/////
  int __fastcall Buy(String Capital,String SecuID,double Price,int Num,String &ContractID);
  int __fastcall Sell(String Capital,String SecuID,double Price,int Num,String &ContractID);
  int __fastcall Undo(String ContractID,TBourse Bourse); //委托撤单
};
//---------------------------------------------------------------------------
#endif

 