#include <vcl.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <dos.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "UCotTest.h"
#include "..\..\..\..\Common\UCmnLib.h"
//----------------------------------------------------------------------
void delay(long i)
{
  while(i>0) { i--; }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TCotTest::TCotTest() 
{
  FAccRec     = new TList();
  FStockRec   = new TList();
  FCmsRec     = new TList();
  FBargainRec = new TList();

  SHContractID = 0;
  SZContractID = 0;
}
//----------------------------------------------------------------------
__fastcall TCotTest::~TCotTest()
{
  for(int i=0;i<FAccRec->Count;i++) { delete (TAccRec*)(FAccRec->Items[i]); }
  delete FAccRec;
  for(int i=0;i<FStockRec->Count;i++) { delete (TStockRec*)(FStockRec->Items[i]); }
  delete FStockRec;
  for(int i=0;i<FCmsRec->Count;i++) { delete (TCmsRec*)(FCmsRec->Items[i]); }
  delete FCmsRec;
  for(int i=0;i<FBargainRec->Count;i++) { delete (TBargainRec*)(FBargainRec->Items[i]); }
  delete FBargainRec;
}
//----------------------------------------------------------------------
TAccRec* __fastcall TCotTest::FindAcc(String Capital)
{
  for(int i=0;i<FAccRec->Count;i++) {
    if(String(((TAccRec*)(FAccRec->Items[i]))->Capital)==Capital) {
      return (TAccRec*)(FAccRec->Items[i]);
    }
  }
  return NULL;
}
//----------------------------------------------------------------------
TStockRec* __fastcall TCotTest::FindStock(String Capital,TBourse Bourse,String SecuID)
{
  TStockRec *stockRec;
  for(int i=0;i<FStockRec->Count;i++) {
    stockRec = (TStockRec*)(FStockRec->Items[i]);
    if(String(stockRec->Capital)==Capital && stockRec->Bourse==Bourse &&
      String(stockRec->SecuID)==SecuID) {
      return stockRec;
    }
  }
  return NULL;
}
//----------------------------------------------------------------------
TCmsRec* __fastcall TCotTest::FindCms(String Date,TBourse Bourse,String ContractID)
{
  TCmsRec *cmsRec;

  for(int i=0;i<FCmsRec->Count;i++) {
    cmsRec = (TCmsRec*)(FCmsRec->Items[i]);
    if(String(cmsRec->Date)==Date && cmsRec->Bourse==Bourse &&
      String(cmsRec->ContractID)==ContractID) {
      return cmsRec;
    }
  }
  return NULL;
}
//----------------------------------------------------------------------
TBargainRec* __fastcall TCotTest::FindBargain(String Date,TBourse Bourse,String ContractID)
{
  TBargainRec *bargainRec;

  for(int i=0;i<FBargainRec->Count;i++) {
    bargainRec = (TBargainRec*)(FBargainRec->Items[i]);
    if(String(bargainRec->Date)==Date && bargainRec->Bourse==Bourse &&
      String(bargainRec->ContractID)==ContractID) {
      return bargainRec;
    }
  }
  return NULL;
}
//---------------- debug -----------------------------------------------
int __fastcall TCotTest::GetBuyInfo(String SecuID,TDealInfo &Info)
{
  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::GetSellInfo(String SecuID,TDealInfo &Info)
{
  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryMoney(double &Balance,double &Usable)
{
  Balance = 200000000;
  Usable  = 200000000;

  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryStock(String Capital,String SecuID,int &YE,int &KYS,int &MRDJS,int &MCDJS)
{
  TBourse bourse;

  if(SecuID[1]=='H') { bourse = bsSH; }
  else { bourse = bsSZ; }

  TStockRec *stockRec = FindStock(Capital,bourse,SecuID.Delete(1,1));
  if(stockRec) {
    YE    = stockRec->Balance;
    KYS   = stockRec->Available;
    MRDJS = stockRec->BuyFreeze;
    MCDJS = stockRec->SellFreeze;
  }
  else { return -1; }

  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryStock(String Capital,String SecuID,double Price,int &Num)
{
  Num = 999999;
  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::Buy(String Capital,String SecuID,double Price,int Num,String &HTXH)
{
  //IsCan(float Rate)

  String  contractID;
  TBourse bourse;
  
  if(SecuID[1]=='H') {
    contractID = ++SHContractID;
    bourse     = bsSH;
  }
  else {
    contractID = ++SZContractID;
    bourse     = bsSZ;
  }

  SecuID.Delete(1,1);

  //增加委托记录
  TCmsRec *cmsRec = new TCmsRec();
  memset(cmsRec,0,sizeof(TCmsRec));

  strcpy(cmsRec->Capital,Capital.c_str()); 
  cmsRec->Bourse = bourse;
  strcpy(cmsRec->ContractID,contractID.c_str());
  strcpy(cmsRec->SecuID,SecuID.c_str());
  strcpy(cmsRec->Time,TRjlFunc::TimeShortToSimp(Now()).c_str());
  strcpy(cmsRec->Date,TRjlFunc::DateShortToSimp(Now()).c_str());
  cmsRec->Type      = 'B';
  cmsRec->State     = '0';
  cmsRec->CsnVol    = Num;
  cmsRec->TrdVol    = 0;                //成交数量
  cmsRec->CancelVol = 0;             //撤单数量
  cmsRec->CsnPrice  = Price;              //委托价格
  cmsRec->TrdPrice  = Price;              //成交价格

  FCmsRec->Add(cmsRec);

  HTXH = contractID;
  Beep();
  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::Sell(String Capital,String SecuID,double Price,int Num,String &HTXH)
{
  TBourse bourse;
  String  contractID;

  if(SecuID[1]=='H') { //上交所
    bourse     = bsSH;
    contractID = ++SHContractID;
  }
  else { //深交所
    bourse     = bsSZ;
    contractID = ++SZContractID;
  }

  SecuID.Delete(1,1);

/*  //修改库存
  TStockRec *stockRec = FindStock(Capital,bourse,SecuID);
  if(stockRec) {
    //if(stockRec->Available<Num) { return -1; } //不允许卖空

    stockRec->Available  = stockRec->Available - Num;
    stockRec->SellFreeze = stockRec->SellFreeze + Num;
  }
  else { //允许卖空
    stockRec = new TStockRec();
    memset(stockRec,0,sizeof(TStockRec));

    strcpy(stockRec->Capital,Capital.c_str());
    stockRec->Bourse = bourse;
    strcpy(stockRec->SecuID,SecuID.c_str());

    //T+0
    stockRec->Balance    = 0;         //余额
    stockRec->Available  = stockRec->Available - Num;  //可用数
    stockRec->BuyFreeze  = 0;       //买入冻结
    stockRec->SellFreeze = stockRec->SellFreeze + Num; //卖出冻结

    FStockRec->Add(stockRec);
  }           */

  //增加委托记录
  TCmsRec *cmsRec = new TCmsRec();
  memset(cmsRec,0,sizeof(TCmsRec));

  strcpy(cmsRec->Capital,Capital.c_str());
  cmsRec->Bourse = bourse; 
  strcpy(cmsRec->ContractID,contractID.c_str());
  strcpy(cmsRec->SecuID,SecuID.c_str());
  strcpy(cmsRec->Time,TRjlFunc::TimeShortToSimp(Now()).c_str());
  strcpy(cmsRec->Date,TRjlFunc::DateShortToSimp(Now()).c_str());
  cmsRec->Type      = 'S';
  cmsRec->State     = '0';
  cmsRec->CsnVol    = Num;
  cmsRec->TrdVol    = 0;                //成交数量
  cmsRec->CancelVol = 0;             //撤单数量
  cmsRec->CsnPrice  = Price;              //委托价格
  cmsRec->TrdPrice  = Price;              //成交价格

  FCmsRec->Add(cmsRec);

/*  //增加交易记录
  TBargainRec *bargainRec = new TBargainRec();
  memset(bargainRec,0,sizeof(TBargainRec));

  strcpy(bargainRec->Capital,Capital.c_str());
  bargainRec->Bourse = bourse;
  strcpy(bargainRec->ContractID,contractID.c_str());
  strcpy(bargainRec->SecuID,SecuID.c_str());
  strcpy(bargainRec->Time,TimeShortToSimp(Now()).c_str());               //成交时间
  strcpy(bargainRec->Date,DateShortToSimp(Now()).c_str());               //委托日期
  bargainRec->Type  = 'S';                  //买卖类别
  bargainRec->Vol   = Num;                   //成交数量
  bargainRec->Price = Price;                 //成交价格

  FBargainRec->Add(bargainRec);        */

  HTXH = contractID;
  Beep();
  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::Undo(String HTXH,TBourse Bourse)
{
  for(int i=0;i<FCmsRec->Count;i++) {
    TCmsRec *cmsRec = (TCmsRec*)(FCmsRec->Items[i]);

    if(cmsRec->CsnVol!=(cmsRec->TrdVol-cmsRec->CancelVol)) { //未完全成交
      cmsRec->CancelVol = -cmsRec->CsnVol;

      //增加交易记录
      TBargainRec *bargainRec = new TBargainRec();
      memset(bargainRec,0,sizeof(TBargainRec));

      strcpy(bargainRec->Capital,cmsRec->Capital);
      bargainRec->Bourse = cmsRec->Bourse;
      strcpy(bargainRec->ContractID,cmsRec->ContractID);
      strcpy(bargainRec->SecuID,cmsRec->SecuID);
      strcpy(bargainRec->Time,TRjlFunc::TimeShortToSimp(Now()).c_str());               //成交时间
      strcpy(bargainRec->Date,TRjlFunc::DateShortToSimp(Now()).c_str());               //委托日期
      bargainRec->Type  = cmsRec->Type;                  //买卖类别
      bargainRec->Vol   = -cmsRec->CsnVol;                   //成交数量
      bargainRec->Price = 0;                 //成交价格

      FBargainRec->Add(bargainRec);

      return 0;
    }
  }    

  return -1;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryDetail(String HTXH,TBourse Bourse,double &Price,int &Num,int &UndoNum)
{
  TBargainRec *bargainRec = FindBargain(TRjlFunc::DateShortToSimp(Now()),Bourse,HTXH);
  if(bargainRec) {
    Price   = bargainRec->Price;
    Num     = bargainRec->Vol;
    UndoNum = 0;
  }
  else { return -1; }
  
  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryDetail(String DateStr,String ContractID,
  TBourse Bourse,double &Price,int &Num,int &UndoNum)
{
  TBargainRec *bargainRec = FindBargain(DateStr,Bourse,ContractID);
  if(bargainRec) {
    Price   = bargainRec->Price;
    Num     = bargainRec->Vol;
    UndoNum = 0;
  }
  else { return -1; }

  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::Init(String CotID,String CotPW)
{
  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::SetAccount(String KHBS,TAccountSort Sort,String PW)
{
  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryCsn(String ContractID,TBourse Bourse,TConsignInfo &CsgInfo)
{
  TCmsRec *cmsRec;
  
  for(int i=0;i<FCmsRec->Count;i++) {
    cmsRec = (TCmsRec*)(FCmsRec->Items[i]);
    
    if(strcmp(cmsRec->ContractID,ContractID.c_str())==0 && cmsRec->Bourse==Bourse) {
      strcpy(CsgInfo.ContractID,cmsRec->ContractID); //合同序号
      strcpy(CsgInfo.SecuID,cmsRec->SecuID);     //证券代码
      strcpy(CsgInfo.Time,cmsRec->Time);   //委托时间
      CsgInfo.Bourse    = cmsRec->Bourse;
      CsgInfo.Type      = cmsRec->Type;                   //买卖类别
      CsgInfo.State     = cmsRec->State;                   //撤单状态
      CsgInfo.CsnVol    = cmsRec->CsnVol;                   //委托数量
      CsgInfo.TrdVol    = cmsRec->TrdVol;                   //成交数量
      CsgInfo.CancelVol = cmsRec->CancelVol;                   //撤单数量
      CsgInfo.CsnPrice  = cmsRec->CsnPrice;                   //委托价格
      CsgInfo.TrdPrice  = cmsRec->TrdPrice;                   //成交价格

      return 0;
    }
  }

  return -1;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryCurCsn(String Capital,TConsignInfo **CsgInfo,int &Num)
{
  Num = 0;

  for(int i=0;i<FCmsRec->Count;i++) {
    if(strcmp(((TCmsRec*)(FCmsRec->Items[i]))->Capital,Capital.c_str())==0) { Num++; }
  }

  if(Num>0) {
    *CsgInfo = new TConsignInfo[Num];
    memset(*CsgInfo,0,Num*sizeof(TConsignInfo));
    int n = 0;
    TCmsRec *cmsRec;

    for(int i=0;i<FCmsRec->Count;i++) {
      cmsRec = (TCmsRec*)(FCmsRec->Items[i]);

      if(strcmp(cmsRec->Capital,Capital.c_str())==0) {
        strcpy((*CsgInfo)[n].ContractID,cmsRec->ContractID); //合同序号
        strcpy((*CsgInfo)[n].SecuID,cmsRec->SecuID);     //证券代码
        strcpy((*CsgInfo)[n].Time,cmsRec->Time);   //委托时间
        (*CsgInfo)[n].Bourse    = cmsRec->Bourse;
        (*CsgInfo)[n].Type      = cmsRec->Type;                   //买卖类别
        (*CsgInfo)[n].State     = cmsRec->State;                   //撤单状态
        (*CsgInfo)[n].CsnVol    = cmsRec->CsnVol;                   //委托数量
        (*CsgInfo)[n].TrdVol    = cmsRec->TrdVol;                   //成交数量
        (*CsgInfo)[n].CancelVol = cmsRec->CancelVol;                   //撤单数量
        (*CsgInfo)[n].CsnPrice  = cmsRec->CsnPrice;                   //委托价格
        (*CsgInfo)[n].TrdPrice  = cmsRec->TrdPrice;                   //成交价格

        n++;
      }
    }
  }
  else { return -1; }

  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryHisCsn(String Capital,String StartDay,String EndDay,
  TConsignInfo **CsgInfo,int &Num)
{
  Num = 0;
  TCmsRec *cmsRec;

  for(int i=0;i<FCmsRec->Count;i++) {
    cmsRec = (TCmsRec*)(FCmsRec->Items[i]);
    
    if(strcmp(cmsRec->Capital,Capital.c_str())==0 && String(cmsRec->Date)>=StartDay &&
      String(cmsRec->Date)<=EndDay) {
      Num++;
    }
  }

  if(Num>0) {
    *CsgInfo = new TConsignInfo[Num];
    memset(*CsgInfo,0,Num*sizeof(TConsignInfo));
    int n = 0;

    for(int i=0;i<FCmsRec->Count;i++) {
      cmsRec = (TCmsRec*)(FCmsRec->Items[i]);

      if(strcmp(cmsRec->Capital,Capital.c_str())==0 && String(cmsRec->Date)>=StartDay &&
        String(cmsRec->Date)<=EndDay) {
        strcpy((*CsgInfo)[n].ContractID,cmsRec->ContractID); //合同序号
        strcpy((*CsgInfo)[n].SecuID,cmsRec->SecuID);     //证券代码
        strcpy((*CsgInfo)[n].Date,cmsRec->Date);   //委托时间
        (*CsgInfo)[n].Bourse    = cmsRec->Bourse;
        (*CsgInfo)[n].Type      = cmsRec->Type;                   //买卖类别
        (*CsgInfo)[n].State     = cmsRec->State;                   //撤单状态
        (*CsgInfo)[n].CsnVol    = cmsRec->CsnVol;                   //委托数量
        (*CsgInfo)[n].TrdVol    = cmsRec->TrdVol;                   //成交数量
        (*CsgInfo)[n].CancelVol = cmsRec->CancelVol;                   //撤单数量
        (*CsgInfo)[n].CsnPrice  = cmsRec->CsnPrice;                   //委托价格
        (*CsgInfo)[n].TrdPrice  = cmsRec->TrdPrice;                   //成交价格

        n++;
      }
    }
  }
  else { return -1; }

  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryCurTrd(String Capital,TTradeInfo **TrdInfo,int &Num)
{
  Num = 0;

  for(int i=0;i<FBargainRec->Count;i++) {
    if(strcmp(((TBargainRec*)(FBargainRec->Items[i]))->Capital,Capital.c_str())==0) { Num++; }
  }

  if(Num>0) {
    *TrdInfo = new TTradeInfo[Num];
    memset(*TrdInfo,0,Num*sizeof(TTradeInfo));
    int n =0;
    TBargainRec *bargainRec;

    for(int i=0;i<FBargainRec->Count;i++) {
      bargainRec = (TBargainRec*)(FBargainRec->Items[i]);

      if(strcmp(bargainRec->Capital,Capital.c_str())==0) {
        strcpy((*TrdInfo)[n].SecuID,bargainRec->SecuID);
        strcpy((*TrdInfo)[n].Time,bargainRec->Time);
        (*TrdInfo)[n].Type  = bargainRec->Type;
        (*TrdInfo)[n].Vol   = bargainRec->Vol;
        (*TrdInfo)[n].Price = bargainRec->Price;

        n++;
      }
    }
  }
  else { return -1; }

  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryHisTrd(String Capital,String StartDay,String EndDay,
  TTradeInfo **TrdInfo,int &Num)
{
  Num = 0;
  TBargainRec *bargainRec;

  for(int i=0;i<FBargainRec->Count;i++) {
    bargainRec = (TBargainRec*)(FBargainRec->Items[i]); 
    if(strcmp(bargainRec->Capital,Capital.c_str())==0 &&
      String(bargainRec->Date)>=StartDay && String(bargainRec->Date)>=EndDay) {
      Num++;
    }
  }

  if(Num>0) {
    *TrdInfo = new TTradeInfo[Num];
    memset(*TrdInfo,0,Num*sizeof(TTradeInfo));
    int n =0;
    TBargainRec *bargainRec;

    for(int i=0;i<FBargainRec->Count;i++) {
      bargainRec = (TBargainRec*)(FBargainRec->Items[i]);

      if(strcmp(bargainRec->Capital,Capital.c_str())==0 &&
        String(bargainRec->Date)>=StartDay && String(bargainRec->Date)>=EndDay) {
        strcpy((*TrdInfo)[n].SecuID,bargainRec->SecuID);
        strcpy((*TrdInfo)[n].Date,bargainRec->Date);
        (*TrdInfo)[n].Type  = bargainRec->Type;
        (*TrdInfo)[n].Vol   = bargainRec->Vol;
        (*TrdInfo)[n].Price = bargainRec->Price;

        n++;
      }
    }
  }
  else { return -1; }

  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryBill(String StartDay,String EndDay,TFundInfo **FundInfo,int &Num)
{
  Num = 9;

  *FundInfo = new TFundInfo[Num];
  memset(*FundInfo,0,Num*sizeof(TFundInfo));

  for(int i=0;i<Num;i++) {
    strcpy((*FundInfo)[i].Date,StartDay.c_str());
    strcpy((*FundInfo)[i].SecuID,("00000"+IntToStr(i)).c_str());
    strcpy((*FundInfo)[i].SecuDesc,"黑衣人");
    strcpy((*FundInfo)[i].Type,"买入");
    (*FundInfo)[i].Vol     = 1000;
    (*FundInfo)[i].Price   = 12.24;
    (*FundInfo)[i].TrdMny  = 12240;
    (*FundInfo)[i].Balance = 15246;
  }

  return 0;
}
//----------------------------------------------------------------------
int __fastcall TCotTest::QryStocks(String Capital,TStockInfo **StockInfo,int &Num)
{
  Num = 0;

  for(int i=0;i<FStockRec->Count;i++) {
    if(strcmp(((TStockRec*)FStockRec->Items[i])->Capital,Capital.c_str())==0) { Num++; }
  }

  if(Num>0) {
    TStockRec  *tmpStock;
    *StockInfo = new TStockInfo[Num];
    int        n = 0;

    memset(*StockInfo,0,Num*sizeof(TStockInfo));

    for(int i=0;i<FStockRec->Count;i++) {
      tmpStock = (TStockRec*)FStockRec->Items[i];
      
      if(strcmp(tmpStock->Capital,Capital.c_str())==0) {
        strcpy((*StockInfo)[n].SecuID,tmpStock->SecuID);
        (*StockInfo)[n].Balance    = tmpStock->Balance;
        (*StockInfo)[n].Available  = tmpStock->Available;       //可用数
        (*StockInfo)[n].BuyFreeze  = tmpStock->BuyFreeze;       //买入冻结
        (*StockInfo)[n].SellFreeze = tmpStock->SellFreeze;      //卖出冻结
        (*StockInfo)[n].CostPrice  = tmpStock->CostPrice;       //成本价
        (*StockInfo)[n].Cost       = tmpStock->Balance*tmpStock->CostPrice; //成本

        n++;
      }
    }
  }   

  return 0;
}
//----------------------------------------------------------------------
bool __fastcall TCotTest::IsCan(float Rate)
{
  randomize();
  if(random(1000)<1000*Rate) { return true; }
  
  return false;
}
//----------------------------------------------------------------------



 