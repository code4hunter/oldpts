//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdItf_Test2.h"

#include <stdio.h>

#pragma package(smart_init)

//---------------------------------------------------------------------------
long TTrdItf_TEST2::FOrderID = 0;
ORDERS TTrdItf_TEST2::FOrders;

TTrdItf_TEST2::TTrdItf_TEST2()
{
  randomize();
}

TTrdItf_TEST2::~TTrdItf_TEST2()
{
}


int TTrdItf_TEST2::Init()  //初始化
{
  //FOrders.clear();
  return 0;
}

int TTrdItf_TEST2::SetAccount() //设置帐号
{
  return 0;
}

//////交易函数/////
int TTrdItf_TEST2::Buy()
{
  FOrders.push_back();
  InterlockedIncrement(&FOrderID);
  order &ord = FOrders[FOrders.size()-1];

  lstrcpyn(ord.code, FRequest.Buy.SecuID,20);
  ord.id = FOrderID;
  ord.price = FRequest.Buy.Price;

  ord.ord_num = FRequest.Buy.Num;
  ord.num   = 0 ;
  ord.cancel = 0;
  ord.bcancel = false;
  ord.ord_time = Now();

  String s = IntToStr(FOrderID);

  NewAns(1);
  strcpy((*FAnswer)[0].Buy.ContractID,s.c_str());

  return 0;
}

int TTrdItf_TEST2::Sell()
{
  FOrders.push_back();
  InterlockedIncrement(&FOrderID);
  order &ord = FOrders[FOrders.size()-1];

  lstrcpyn(ord.code, FRequest.Sell.SecuID,20);
  ord.id = FOrderID;

  ord.ord_num = FRequest.Sell.Num;
  ord.price = FRequest.Sell.Price;
  ord.num   = 0;
  ord.cancel = 0;
  ord.bcancel = false;
  ord.ord_time = Now();

  String s = IntToStr(FOrderID);

  NewAns(1);
  strcpy((*FAnswer)[0].Sell.ContractID,s.c_str());

  return 0;
}

int TTrdItf_TEST2::Undo() //委托撤单
{
  long index = FindID(FRequest.Undo.ContractID);
  if( index>=0 && index<FOrders.size() )
  {
    order &ord = FOrders[index];

    if(ord.bcancel==false && ord.num<ord.ord_num )
    {
      FOrders[index].bcancel = true;
      return 0;
    }
    else return -1;
  }
  else
    return -1;

}


//////查询函数//////

int TTrdItf_TEST2::QryMoney()     //资金查询
{
    NewAns(1);

    (*FAnswer)[0].QryMoney.Balance   = 100000000;
    (*FAnswer)[0].QryMoney.Available = 100000000;

    return 0;
}

long TTrdItf_TEST2::FindID(char* id)
{
  long index = atoi(id);

  for(int i=0;i<FOrders.size();i++)
  {
    if( FOrders[i].id == index )
    {
      return i;
    }
  }
  return -1;
}

int TTrdItf_TEST2::QryDetail()    //成交查询
{
  long index = FindID(FRequest.QryDetail.ContractID);
  if( index>=0 && index<FOrders.size() )
  {
    //从委托表中取得委托的成交信息
    order &ord = FOrders[index];

    if( (ord.num + abs(ord.cancel)) < ord.ord_num )
    {

    if( ord.bcancel == true)
    {
      //其他已撤销，1撤销失败，已经成交了
      switch( rand()%5 )
      {
        case 1:
          ord.num = ord.ord_num;
        break;
        default:
          ord.cancel = -(ord.ord_num-ord.num);
      }
    }
    else
    {
      //0保持不变，1系统撤单，2 部分成交
      switch( rand()%10 )
      {
        case 1:
          if( ord.num==0 )
            ord.cancel = ord.num-ord.ord_num;
        break;
        case 2,3,4,8:
          ord.num+= (rand() % (ord.ord_num-ord.num))+1;
        break;
      }

    }
    
    }

    NewAns(1);
    (*FAnswer)[0].QryDetail.Price   =ord.price;
    (*FAnswer)[0].QryDetail.Num     =ord.num;
    (*FAnswer)[0].QryDetail.UndoNum =ord.cancel;

    return 0;
  }
  else
    return -1;
}

int TTrdItf_TEST2::QryStocks()    //查询帐号中所有的股份
{
  if(  FOrders.size() > 0 )
  {
    NewAns(FOrders.size());
    for(int i=0;i<FOrders.size();i++)
    {
      lstrcpyn((*FAnswer)[i].QryStocks.StockInfo.SecuID,FOrders[i].code,8);
      (*FAnswer)[i].QryStocks.StockInfo.Balance=FOrders[i].num;
      (*FAnswer)[i].QryStocks.StockInfo.Available = FOrders[i].num;
      (*FAnswer)[i].QryStocks.StockInfo.CostPrice = FOrders[i].price;

    }
  }
  return 0;
}

//-------------------------------------------------------

int TTrdItf_TEST2::GetTrdInfo()   //取得盘口数据
{
    return -1;
}

int TTrdItf_TEST2::QryStock()     //股份查询
{
    return -1;
}

int TTrdItf_TEST2::QryCanBuy()    //取可买数量
{
    return -1;
}


int TTrdItf_TEST2::QryHisDetail() //历史成交查询
{
    return -1;
}

int TTrdItf_TEST2::QryCsn()       //查询某个委托合同
{
    return -1;
}

int TTrdItf_TEST2::QryCurCsn()    //当日委托查询
{
  if(  FOrders.size() > 0 )
  {
    NewAns(FOrders.size());
    for(int i=0;i<FOrders.size();i++)
    {
      TConsignInfo &ci = (*FAnswer)[i].QryCurCsn.CsgInfo;
      order &ord = FOrders[i];

      sprintf(ci.ContractID,"%d",ord.id);
      lstrcpyn( ci.SecuID,ord.code,8);

      ci.SecuDesc[0]=0;
      ci.Bourse = 'M';

      unsigned short h,m,s,ms;
      DecodeTime(ord.ord_time,h,m,s,ms);
      sprintf(ci.Time,"%02d%02d%02d",h,m,s);
      ci.Date[0] =0;
      ci.Type = ' ';
      ci.State = ord.bcancel?'T':'F';
      ci.CsnVol = ord.ord_num;
      ci.TrdVol = ord.num;
      ci.CancelVol = ord.cancel;
      ci.CsnPrice = ord.price;
      ci.TrdPrice = ord.price;

    }
    return 0;
  }
  return -1;
}

int TTrdItf_TEST2::QryHisCsn()    //历史委托查询
{
    return -1;
}

int TTrdItf_TEST2::QryCurTrd()    //当日成交查询
{
    return -1;
}

int TTrdItf_TEST2::QryHisTrd()    //历史成交查询
{
    return -1;
}

int TTrdItf_TEST2::QryBill()      //查询资金流水（对帐单）
{
    return -1;
}
