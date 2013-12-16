//---------------------------------------------------------------------------
#include "UTrdItf_PTS.h"
//---------------------------------------------------------------------------
t_exchange_type TBourse2t_exchange_type(TBourse br)
{
	if(br==bsSH) return etsh;
	if(br==bsSZ) return etsz;
	return etqt;
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::Init()
{
  FItf->init(FPTSSet.PTS_Domain,FPTSSet.PTS_Server,FPTSSet.PTS_Trader);

  return 0;
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::SetAccount()
{
  try{
    if(FItf->login(FRequest.SetAccount.Account,FRequest.SetAccount.PW,FRequest.SetAccount.Sort)==0){
      NewAns(1);

      lstrcpyn(FAccInfo.Capital,FRequest.SetAccount.Account,20);
      lstrcpyn(FAccInfo.PW,FRequest.SetAccount.PW,20);
      //lstrcpyn(FAccInfo.Sort,FRequest.SetAccount.Sort,20);

      memcpy(&((*FAnswer)[0].SetAccount.AccountInfo),&FAccInfo,sizeof(TAccountInfo));

      return 0;
    }
    else return -1;
  }
  catch(Exception &e){
    ODS(e.Message.c_str());
    return -1;
  }

}
//---------------------------------------------------------------------------
//////查询函数//////
/*
*/
int  TTrdItf_PTS::GetTrdInfo()
{
  return ERR_UNIMPLEMENTED;

}
//---------------------------------------------------------------------------

/*
****需要查询更详细的资金信息，需要修改类TPTSItf，从IAccountDetail获取

procedure FillMoneyDetail(accd: IAccount;
  list: TRzListBox);
var
  bd:IAccountDetail;
begin
  bd:=accd.GetDetail(tcCurrencyTypeRMB);
  if bd<> nil then
  begin
    if bd.Initial>0 then
    begin
    list.Items.Add('RMB资金:');
    list.Items.Add(Format(' 初始:%0.3f',[bd.Initial]));
    list.Items.Add(Format(' 可用余额:%0.3f',[bd.Available]));
    list.Items.Add(Format(' 昨日余额:%0.3f',[bd.Yesterday]));
    list.Items.Add(Format(' 入金:%0.3f',[bd.Credited]));
    list.Items.Add(Format(' 出金:%0.3f',[bd.Debited]));
    list.Items.Add(Format(' 冻结:%0.3f',[bd.Frozen]));
    list.Items.Add(Format(' 占用的保证金:%0.3f',[bd.MaintenanceMargin]));
    list.Items.Add(Format(' 费用:%0.3f',[bd.Fee]));
    list.Items.Add(Format(' 持仓成本/初始保证金:%0.3f',[bd.PositionCost]));
    list.Items.Add(Format(' 持仓市值/持仓浮亏:%0.3f',[bd.Positio
  ...  
*/
int  TTrdItf_PTS::QryMoney()
{
  double bal = 0,ava = 0,asset = 0;
  int ret =-999;

  try{
    if((ret=FItf->QryMoney(bal,ava,asset))==0)
    {
      NewAns(1);

      (*FAnswer)[0].QryMoney.Balance=bal;
      (*FAnswer)[0].QryMoney.Available=ava;
      (*FAnswer)[0].QryMoney.asset_balance=asset;

      return 0;
    }
    else { ODS(String("请重新登陆帐号"+String(FAccInfo.Capital)).c_str());return -1; }
  }
  catch(Exception &e){
    ODS(e.Message.c_str());
    return -1;
  }
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::QryMoneyFF()
{
  double bal = 0,ava = 0,asset = 0;
  int ret =-999;

  try{
    if((ret=FItf->QryMoney(bal,ava,asset))==0)
    {
      NewAns(1);
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Last_jc     = bal;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.FreezeB     = -1;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.FreezeS     = -1;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MarginB     = -1;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MarginS     = -1;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Profit      = -1;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Loss        = -1;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Available   = ava;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.DymValue    = asset;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.DymVaR      = -1;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Payoff      = -1;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.ClosePayoff = -1;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MoneyOI     = -1;
      (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MarginAll   = -1;
      
      return 0;
    }
    else { ODS(String("请重新登陆帐号"+String(FAccInfo.Capital)).c_str());return -1; }
  }
  catch(Exception &e){
    ODS(e.Message.c_str());
    return -1;
  }
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::QryStock()
{
  return ERR_UNIMPLEMENTED;
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::QryCanBuy()
{
	return ERR_UNIMPLEMENTED;
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::QryDetail()
{
  try{
    if(FRequest.QryDetail.ContractID[0]==0) return -1;

    double price = 0;
    int    num = 0;
    int    undonum = 0;

    if(FItf->QryDetail(FRequest.QryDetail.ContractID,FRequest.QryDetail.Bourse,price,num,undonum)==0){
      NewAns(1);
      (*FAnswer)[0].QryDetail.Price   = price;
      (*FAnswer)[0].QryDetail.Num     = num;
      (*FAnswer)[0].QryDetail.UndoNum = undonum;

      return 0;
    }
    else return -1;

  }
  catch(Exception &e){
    ODS(e.Message.c_str());
    return -1;
  }
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::QryHisDetail()
{
	return ERR_UNIMPLEMENTED;
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::QryCsn()
{
	return ERR_UNIMPLEMENTED;
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::QryCurCsn()
{
  TConsignInfo *csninfo = NULL;
  int num = 0;

  try{
    if(FItf->QryCurCsn(&csninfo,num)!=0) return -1;

    if(num<1) return 0;

    NewAns(num);
    for(int i=0;i<num;i++)
    {
        TConsignInfo *ci = &csninfo[i];

        memcpy(&(*FAnswer)[i].QryCurCsn.CsgInfo,ci,sizeof(TConsignInfo));
    }

    return 0;
  }
  catch(Exception &e){
    ODS(e.Message.c_str());
    return -1;
  }
}
//---------------------------------------------------------------------------

int  TTrdItf_PTS::QryHisCsn()
{
  return ERR_UNIMPLEMENTED;
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::QryCurTrd()
{
  TTradeInfo *trdinfo = NULL;
  int num = 0;

  try{
    if(FItf->QryCurTrd(&trdinfo,num)!=0) return -1;

    if(num>0)
    {
      NewAns(num);
      for(int i=0;i<num;i++)
      {
        TTradeInfo *ci = &trdinfo[i];
        memcpy(&(*FAnswer)[i].QryHisTrd.TrdInfo,ci,sizeof(TTradeInfo));
      }
    }

    return 0;
  }
  catch(Exception &e){
    ODS(e.Message.c_str());
    return -1;
  }
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::QryHisTrd()
{
	return ERR_UNIMPLEMENTED;
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::QryBill()
{
	return ERR_UNIMPLEMENTED;
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::QryStocks()
{
  TStockInfo *stkinfo = NULL;
  int num = 0;

  try{
    if(FItf->QryStocks(&stkinfo,num,FRequest.QryStocks.Bourse)!=0) return -1;

    if(num>0)
    {
      NewAns(num);
      for(int i=0;i<num;i++)
      {
        TStockInfo *ci = &stkinfo[i];
        TStockInfo *si = &(*FAnswer)[i].QryStocks.StockInfo;
        memcpy(si,ci,sizeof(TStockInfo));
        if (FRequest.QryStocks.Bourse == bsSH)
            si->SecuID[0] = 'H';
        else if (FRequest.QryStocks.Bourse == bsSZ)
            si->SecuID[0] = 'S';
        else if (FRequest.QryStocks.Bourse == bsFF)
            si->SecuID[0] = 'T';

        strncpy(si->SecuID + 1, ci->SecuID, 7);


      }
    }

    return 0;
  }
  catch(Exception &e){
    ODS(e.Message.c_str());
    return -1;
  }
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::Buy()
{
  char cid[20];
  short type   = FRequest.Buy.Type;

  memset(cid,0,20);

  if(FRequest.Buy.SecuID[0]=='T'){
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

    type = a + (b<<4) 表示开平和投保的组合

    */
    TTrdTypeFF tt = TTrdTypeFF(FRequest.Buy.Type);
    int a = GetEoType(tt);
    int b = GetShType(tt);

    type = a + (b<<4);
  }

  try{
    if(FItf->BuyOrSell(FRequest.Buy.SecuID,FRequest.Buy.Price,FRequest.Buy.Num,cid,type,tcOrderSideBuy)!=0)
      return -1;

    NewAns(1);
    strcpy((*FAnswer)[0].Buy.ContractID,cid);

    return 0;
  }
  catch(Exception &e){
    ODS(e.Message.c_str());
    return -1;
  }
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::Sell()
{
//  WideString cid = "";
  char cid[20];
  short type     = FRequest.Sell.Type;

  memset(cid,0,20);

  if(FRequest.Sell.SecuID[0]=='T'){
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

    type = a + (b<<4) 表示开平和投保的组合

    */
    TTrdTypeFF tt = TTrdTypeFF(FRequest.Sell.Type);
    int a = GetEoType(tt);
    int b = GetShType(tt);

    type = a + (b<<4);
  }

  try{
    if(FItf->BuyOrSell(FRequest.Sell.SecuID,FRequest.Sell.Price,FRequest.Sell.Num,cid,type,tcOrderSideSell)!=0)
      return -1;

    NewAns(1);
    strcpy((*FAnswer)[0].Sell.ContractID,cid);

    return 0;
  }
  catch(Exception &e){
    ODS(e.Message.c_str());
    return -1;
  }
}
//---------------------------------------------------------------------------
int  TTrdItf_PTS::Undo()
{
  return FItf->Undo(FRequest.Undo.ContractID,FRequest.Undo.Bourse);
}
//---------------------------------------------------------------------------
TTrdItf_PTS::TTrdItf_PTS(TPTSSet *set)
{
	CopyMemory(&FPTSSet,set,sizeof(TPTSSet));
	FItf = new TPTSItf();
}

TTrdItf_PTS::~TTrdItf_PTS()
{
	delete FItf;
}

bool TTrdItf_PTS::RegCommX(String PathName)
{
	ShellExecute(NULL,"open","regsvr32.exe",
              String(String("\"") + PathName + String("\"")).c_str(),
              "",
              SW_SHOWNORMAL);
	return true;
}

