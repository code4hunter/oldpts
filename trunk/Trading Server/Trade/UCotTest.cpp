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

  //����ί�м�¼
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
  cmsRec->TrdVol    = 0;                //�ɽ�����
  cmsRec->CancelVol = 0;             //��������
  cmsRec->CsnPrice  = Price;              //ί�м۸�
  cmsRec->TrdPrice  = Price;              //�ɽ��۸�

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

  if(SecuID[1]=='H') { //�Ͻ���
    bourse     = bsSH;
    contractID = ++SHContractID;
  }
  else { //���
    bourse     = bsSZ;
    contractID = ++SZContractID;
  }

  SecuID.Delete(1,1);

/*  //�޸Ŀ��
  TStockRec *stockRec = FindStock(Capital,bourse,SecuID);
  if(stockRec) {
    //if(stockRec->Available<Num) { return -1; } //����������

    stockRec->Available  = stockRec->Available - Num;
    stockRec->SellFreeze = stockRec->SellFreeze + Num;
  }
  else { //��������
    stockRec = new TStockRec();
    memset(stockRec,0,sizeof(TStockRec));

    strcpy(stockRec->Capital,Capital.c_str());
    stockRec->Bourse = bourse;
    strcpy(stockRec->SecuID,SecuID.c_str());

    //T+0
    stockRec->Balance    = 0;         //���
    stockRec->Available  = stockRec->Available - Num;  //������
    stockRec->BuyFreeze  = 0;       //���붳��
    stockRec->SellFreeze = stockRec->SellFreeze + Num; //��������

    FStockRec->Add(stockRec);
  }           */

  //����ί�м�¼
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
  cmsRec->TrdVol    = 0;                //�ɽ�����
  cmsRec->CancelVol = 0;             //��������
  cmsRec->CsnPrice  = Price;              //ί�м۸�
  cmsRec->TrdPrice  = Price;              //�ɽ��۸�

  FCmsRec->Add(cmsRec);

/*  //���ӽ��׼�¼
  TBargainRec *bargainRec = new TBargainRec();
  memset(bargainRec,0,sizeof(TBargainRec));

  strcpy(bargainRec->Capital,Capital.c_str());
  bargainRec->Bourse = bourse;
  strcpy(bargainRec->ContractID,contractID.c_str());
  strcpy(bargainRec->SecuID,SecuID.c_str());
  strcpy(bargainRec->Time,TimeShortToSimp(Now()).c_str());               //�ɽ�ʱ��
  strcpy(bargainRec->Date,DateShortToSimp(Now()).c_str());               //ί������
  bargainRec->Type  = 'S';                  //�������
  bargainRec->Vol   = Num;                   //�ɽ�����
  bargainRec->Price = Price;                 //�ɽ��۸�

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

    if(cmsRec->CsnVol!=(cmsRec->TrdVol-cmsRec->CancelVol)) { //δ��ȫ�ɽ�
      cmsRec->CancelVol = -cmsRec->CsnVol;

      //���ӽ��׼�¼
      TBargainRec *bargainRec = new TBargainRec();
      memset(bargainRec,0,sizeof(TBargainRec));

      strcpy(bargainRec->Capital,cmsRec->Capital);
      bargainRec->Bourse = cmsRec->Bourse;
      strcpy(bargainRec->ContractID,cmsRec->ContractID);
      strcpy(bargainRec->SecuID,cmsRec->SecuID);
      strcpy(bargainRec->Time,TRjlFunc::TimeShortToSimp(Now()).c_str());               //�ɽ�ʱ��
      strcpy(bargainRec->Date,TRjlFunc::DateShortToSimp(Now()).c_str());               //ί������
      bargainRec->Type  = cmsRec->Type;                  //�������
      bargainRec->Vol   = -cmsRec->CsnVol;                   //�ɽ�����
      bargainRec->Price = 0;                 //�ɽ��۸�

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
      strcpy(CsgInfo.ContractID,cmsRec->ContractID); //��ͬ���
      strcpy(CsgInfo.SecuID,cmsRec->SecuID);     //֤ȯ����
      strcpy(CsgInfo.Time,cmsRec->Time);   //ί��ʱ��
      CsgInfo.Bourse    = cmsRec->Bourse;
      CsgInfo.Type      = cmsRec->Type;                   //�������
      CsgInfo.State     = cmsRec->State;                   //����״̬
      CsgInfo.CsnVol    = cmsRec->CsnVol;                   //ί������
      CsgInfo.TrdVol    = cmsRec->TrdVol;                   //�ɽ�����
      CsgInfo.CancelVol = cmsRec->CancelVol;                   //��������
      CsgInfo.CsnPrice  = cmsRec->CsnPrice;                   //ί�м۸�
      CsgInfo.TrdPrice  = cmsRec->TrdPrice;                   //�ɽ��۸�

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
        strcpy((*CsgInfo)[n].ContractID,cmsRec->ContractID); //��ͬ���
        strcpy((*CsgInfo)[n].SecuID,cmsRec->SecuID);     //֤ȯ����
        strcpy((*CsgInfo)[n].Time,cmsRec->Time);   //ί��ʱ��
        (*CsgInfo)[n].Bourse    = cmsRec->Bourse;
        (*CsgInfo)[n].Type      = cmsRec->Type;                   //�������
        (*CsgInfo)[n].State     = cmsRec->State;                   //����״̬
        (*CsgInfo)[n].CsnVol    = cmsRec->CsnVol;                   //ί������
        (*CsgInfo)[n].TrdVol    = cmsRec->TrdVol;                   //�ɽ�����
        (*CsgInfo)[n].CancelVol = cmsRec->CancelVol;                   //��������
        (*CsgInfo)[n].CsnPrice  = cmsRec->CsnPrice;                   //ί�м۸�
        (*CsgInfo)[n].TrdPrice  = cmsRec->TrdPrice;                   //�ɽ��۸�

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
        strcpy((*CsgInfo)[n].ContractID,cmsRec->ContractID); //��ͬ���
        strcpy((*CsgInfo)[n].SecuID,cmsRec->SecuID);     //֤ȯ����
        strcpy((*CsgInfo)[n].Date,cmsRec->Date);   //ί��ʱ��
        (*CsgInfo)[n].Bourse    = cmsRec->Bourse;
        (*CsgInfo)[n].Type      = cmsRec->Type;                   //�������
        (*CsgInfo)[n].State     = cmsRec->State;                   //����״̬
        (*CsgInfo)[n].CsnVol    = cmsRec->CsnVol;                   //ί������
        (*CsgInfo)[n].TrdVol    = cmsRec->TrdVol;                   //�ɽ�����
        (*CsgInfo)[n].CancelVol = cmsRec->CancelVol;                   //��������
        (*CsgInfo)[n].CsnPrice  = cmsRec->CsnPrice;                   //ί�м۸�
        (*CsgInfo)[n].TrdPrice  = cmsRec->TrdPrice;                   //�ɽ��۸�

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
    strcpy((*FundInfo)[i].SecuDesc,"������");
    strcpy((*FundInfo)[i].Type,"����");
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
        (*StockInfo)[n].Available  = tmpStock->Available;       //������
        (*StockInfo)[n].BuyFreeze  = tmpStock->BuyFreeze;       //���붳��
        (*StockInfo)[n].SellFreeze = tmpStock->SellFreeze;      //��������
        (*StockInfo)[n].CostPrice  = tmpStock->CostPrice;       //�ɱ���
        (*StockInfo)[n].Cost       = tmpStock->Balance*tmpStock->CostPrice; //�ɱ�

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



 