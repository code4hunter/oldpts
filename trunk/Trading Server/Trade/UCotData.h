#ifndef UCotDataH
#define UCotDataH
//------------------------------------------------------------------------------
#include <Classes.hpp>
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
class TCotData 
{
private:	// User declarations
  int SHContractID;
  int SZContractID;

  TList *FAccRec;
  TList *FStockRec;
  TList *FCmsRec;
  TList *FBargainRec;

public:		// User declarations
  __fastcall TCotData();
  __fastcall ~TCotData();

  void __fastcall Add(TAccRec *AccRec);
  void __fastcall Add(TStockRec *StockRec);
  void __fastcall Add(TCmsRec *CmsRec);
  void __fastcall Add(TBargainRec *BargainRec);

  TAccRec*     __fastcall FindAcc(String Capital);
  TStockRec*   __fastcall FindStock(String Capital,TBourse Bourse,String SecuID);
  TCmsRec*     __fastcall FindCms(String Date,TBourse Bourse,String ContractID);
  TBargainRec* __fastcall FindBargain(String Date,TBourse Bourse,String ContractID);

  int __fastcall GetNewSHID() { return ++SHContractID; }
  int __fastcall GetNewSZID() { return ++SZContractID; }
};
//---------------------------------------------------------------------------
#endif


 