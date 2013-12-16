//---------------------------------------------------------------------------
#include "UTrdItf_TEST.h"
//---------------------------------------------------------------------------
void delay(long i)
{
  while(i>0) { i--; }
}
//---------------------------------------------------------------------------
 TTrdItf_TEST::TTrdItf_TEST() : TTrdItfBase()
{
  FHandle = LoadLibrary("PCotTestDll"); //"API_SHRJ");

  if(FHandle!=NULL) {
    FInit         = (TInit)GetProcAddress(FHandle,"_Init");
    FSetAccount   = (TSetAccount)GetProcAddress(FHandle,"_SetAccount");
    FGetBuyInfo   = (TGetBuyInfo)GetProcAddress(FHandle,"_GetBuyInfo");
    FGetSellInfo  = (TGetSellInfo)GetProcAddress(FHandle,"_GetSellInfo");
    FQryMoney     = (TQryMoney)GetProcAddress(FHandle,"_QryMoney");
    FQryStock     = (TQryStock)GetProcAddress(FHandle,"_QryStock");
    FQryCanBuy    = (TQryCanBuy)GetProcAddress(FHandle,"_QryCanBuy");
    FQryDetail    = (TQryDetail)GetProcAddress(FHandle,"_QryDetail");
    FQryHisDetail = (TQryHisDetail)GetProcAddress(FHandle,"_QryHisDetail");
    FQryCsn       = (TQryCsn)GetProcAddress(FHandle,"_QryCsn");
    FQryCurCsn    = (TQryCurCsn)GetProcAddress(FHandle,"_QryCurCsn");
    FQryHisCsn    = (TQryHisCsn)GetProcAddress(FHandle,"_QryHisCsn");
    FQryCurTrd    = (TQryCurTrd)GetProcAddress(FHandle,"_QryCurTrd");
    FQryHisTrd    = (TQryHisTrd)GetProcAddress(FHandle,"_QryHisTrd");
    FQryBill      = (TQryBill)GetProcAddress(FHandle,"_QryBill");
    FQryStocks    = (TQryStocks)GetProcAddress(FHandle,"_QryStocks");
    FBuy          = (TBuy)GetProcAddress(FHandle,"_Buy");
    FSell         = (TSell)GetProcAddress(FHandle,"_Sell");
    FUndo         = (TUndo)GetProcAddress(FHandle,"_Undo");
  }
  else {
    MessageBox(NULL,"找不到动态连接库\"PCotTestDll.dll\"！","Error!",MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------
 TTrdItf_TEST::~TTrdItf_TEST()
{
  FreeLibrary(FHandle);
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::GetTrdInfo()
{
  TDealInfo buyInfo;
  TDealInfo sellInfo;

  if(FGetBuyInfo(FRequest.GetTrdInfo.SecuID,buyInfo)!=0) { return -1; }
  if(FGetSellInfo(FRequest.GetTrdInfo.SecuID,sellInfo)!=0) { return -1; }

  NewAns(1);
  memcpy(&((*FAnswer)[0].GetTrdInfo.BuyInfo),&buyInfo,sizeof(TDealInfo));
  memcpy(&((*FAnswer)[0].GetTrdInfo.SellInfo),&sellInfo,sizeof(TDealInfo));

  return 0;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryMoney()
{
  NewAns(1);

  (*FAnswer)[0].QryMoney.Balance   = 200000000;
  (*FAnswer)[0].QryMoney.Available = 200000000;

  return 0;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryStock()
{
  int ye,kys,mrdjs,mcdjs;

  if(FQryStock(FAccInfo.Capital,FRequest.QryStock.SecuID,ye,kys,mrdjs,mcdjs)==0) {
    NewAns(1);
    (*FAnswer)[0].QryStock.Balance    = ye;
    (*FAnswer)[0].QryStock.Available  = kys;
    (*FAnswer)[0].QryStock.BuyFreeze  = mrdjs;
    (*FAnswer)[0].QryStock.SellFreeze = mcdjs;

    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryCanBuy()
{
  int num;

  if(FQryCanBuy(FAccInfo.Capital,FRequest.QryCanBuy.SecuID,FRequest.QryCanBuy.Price,num)==0) {
    NewAns(1);
    (*FAnswer)[0].QryCanBuy.Num = num;

    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::Buy()
{
  char *htxh;

  if(FBuy(FAccInfo.Capital,FRequest.Buy.SecuID,FRequest.Buy.Price,FRequest.Buy.Num,&htxh)==0) {
    NewAns(1);
    strcpy((*FAnswer)[0].Buy.ContractID,htxh);
    delete []htxh;

    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::Sell()
{
  char *htxh;
  
  if(FSell(FAccInfo.Capital,FRequest.Sell.SecuID,FRequest.Sell.Price,FRequest.Sell.Num,&htxh)==0) {
    NewAns(1);
    strcpy((*FAnswer)[0].Sell.ContractID,htxh);
    delete []htxh;
    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::Undo()
{
  return FUndo(FRequest.Undo.ContractID,FRequest.Undo.Bourse);
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryDetail()
{
  double price;
  int    num;
  int    undoNum;

  if(FQryDetail(FRequest.QryDetail.ContractID,FRequest.QryDetail.Bourse,price,num,undoNum)==0) {
    NewAns(1);
    (*FAnswer)[0].QryDetail.Price   = price;
    (*FAnswer)[0].QryDetail.Num     = num;
    (*FAnswer)[0].QryDetail.UndoNum = undoNum;

    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryHisDetail()
{
  double price;
  int    num;
  int    undoNum;

  if(FQryHisDetail(FRequest.QryHisDetail.DateStr,FRequest.QryHisDetail.ContractID,
    FRequest.QryHisDetail.Bourse,price,num,undoNum)==0) {
    NewAns(1);
    (*FAnswer)[0].QryHisDetail.Price   = price;
    (*FAnswer)[0].QryHisDetail.Num     = num;
    (*FAnswer)[0].QryHisDetail.UndoNum = undoNum;

    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::Init()
{
  return 0;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::SetAccount()
{
  strcpy(FAccInfo.Capital,FRequest.SetAccount.Account);

  if(FSetAccount(FRequest.SetAccount.Account,FRequest.SetAccount.Sort,
    FRequest.SetAccount.PW)==0) {
    NewAns(1);
    memcpy(&((*FAnswer)[0].SetAccount.AccountInfo),&FAccInfo,sizeof(TAccountInfo));

    return 0;
  }

  return -1;       
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryCsn()
{
  TConsignInfo csgInfo;

  if(FQryCsn(FRequest.QryCsn.ContractID,FRequest.QryCsn.Bourse,csgInfo)==0) {
    NewAns(1);
    memcpy(&((*FAnswer)[0].QryCsn.CsgInfo),&csgInfo,sizeof(TConsignInfo));

    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryCurCsn()
{
  TConsignInfo *csgInfo;
  int          num;

  if(FQryCurCsn(FAccInfo.Capital,&csgInfo,num)==0) {
    if(num>0) {
      NewAns(num);
      for(int i=0;i<num;i++) {
        memcpy(&((*FAnswer)[i].QryCurCsn.CsgInfo),&(csgInfo[i]),sizeof(TConsignInfo));
      }

      delete []csgInfo;
    }

    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryHisCsn()
{
  TConsignInfo *csgInfo;
  int          num;

  if(FQryHisCsn(FAccInfo.Capital,FRequest.QryHisCsn.StartDay,FRequest.QryHisCsn.EndDay,&csgInfo,num)==0) {
    if(num>0) {
      NewAns(num);
      for(int i=0;i<num;i++) {
        memcpy(&((*FAnswer)[i].QryCurCsn.CsgInfo),&(csgInfo[i]),sizeof(TConsignInfo));
      }

      delete []csgInfo;
    }

    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryCurTrd()
{
  TTradeInfo *trdInfo;
  int        num;

  if(FQryCurTrd(FAccInfo.Capital,&trdInfo,num)==0) {
    if(num>0) {
      NewAns(num);
      for(int i=0;i<num;i++) {
        memcpy(&((*FAnswer)[i].QryCurTrd.TrdInfo),&(trdInfo[i]),sizeof(TTradeInfo));
      }

      delete []trdInfo;
    }

    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryHisTrd()
{
  TTradeInfo *trdInfo;
  int        num;

  if(FQryHisTrd(FAccInfo.Capital,FRequest.QryHisTrd.StartDay,
    FRequest.QryHisTrd.EndDay,&trdInfo,num)==0) {
    if(num>0) {
      NewAns(num);
      for(int i=0;i<num;i++) {
        memcpy(&((*FAnswer)[i].QryCurTrd.TrdInfo),&(trdInfo[i]),sizeof(TTradeInfo));
      }

      delete []trdInfo;
    }

    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryBill()
{
  int num = 1000;

  NewAns(num);

  for(int i=0;i<num;i++)
  {
    strcpy((*FAnswer)[i].QryBill.FundInfo.Date,FRequest.QryBill.StartDay);
    strcpy((*FAnswer)[i].QryBill.FundInfo.SecuID,(String(i)).c_str());
    strcpy((*FAnswer)[i].QryBill.FundInfo.SecuDesc,"黑衣人");
    strcpy((*FAnswer)[i].QryBill.FundInfo.Type,"买入");
    (*FAnswer)[i].QryBill.FundInfo.Vol     = 1000;
    (*FAnswer)[i].QryBill.FundInfo.Price   = 12.24;
    (*FAnswer)[i].QryBill.FundInfo.TrdMny  = 12240;
    (*FAnswer)[i].QryBill.FundInfo.Balance = 15246;
  }

  return 0;
}
//---------------------------------------------------------------------------
int  TTrdItf_TEST::QryStocks()
{
  TStockInfo *stockInfo;
  int        num;

  if(FQryStocks(FAccInfo.Capital,&stockInfo,num)==0) {
    if(num>0) {
      NewAns(num);
      for(int i=0;i<num;i++) {
        memcpy(&((*FAnswer)[i].QryStocks.StockInfo),&(stockInfo[i]),sizeof(TStockInfo));
      }

      delete []stockInfo;
    }

    return 0;
  }

  return -1;
}
//---------------------------------------------------------------------------

