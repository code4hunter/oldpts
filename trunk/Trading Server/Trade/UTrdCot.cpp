//---------------------------------------------------------------------------
#include "UTrdCot.h"
#include <vcl.h>
#include <math.h>
//---------------------------------------------------------------------------
__fastcall TTrdCot::TTrdCot()
{
}
//---------------------------------------------------------------------------
__fastcall TTrdCot::~TTrdCot()
{
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot::GetAccInfo(TAccountInfo &AccInfo)
{
	int      retVal;
	TRequest request;
	TAnswer  *answer;
	int      ansCount;

	request.Head.FuncType   = ftGetAccount;
	if((retVal=Request(request,&answer,ansCount))==0) {
	 if(ansCount>0)
	 {
		 memcpy(&AccInfo,&(answer[0].GetAccount.AccountInfo),sizeof(TAccountInfo));
		 DeleteAns(&answer);
	 }
	}

	return retVal;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot::Init(void)
{
  int      retVal;
  TRequest request;
  TAnswer  *answer;
  int      ansCount;

	request.Head.FuncType = ftInit;

  if((retVal=Request(request,&answer,ansCount))==0) {
    if(ansCount>0) { DeleteAns(&answer); }
  }

  return retVal;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot::Login(AnsiString Account,account_type Type,AnsiString PW)
{
	int      retVal;
	TRequest request;
	TAnswer  *answer;
	int      ansCount;

	request.Head.FuncType   = ftSetAccount;
	strcpy(request.SetAccount.Account,Account.c_str());
	request.SetAccount.LoginType = Type;
	strcpy(request.SetAccount.PW,PW.c_str());

	if((retVal=Request(request,&answer,ansCount))==0) {
	 if(ansCount>0)
	 {
		 DeleteAns(&answer);
	 }
	}

	return retVal;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot::QryMoney(money_type MoneyType,TMoneyInfo &MoneyInfo)
{
  int      retVal;
  TRequest request;
  TAnswer  *answer;
  int      ansCount;

  request.Head.FuncType = ftQryMoney;
	request.QryMoney.MoneyType =  MoneyType;
  if((retVal=Request(request,&answer,ansCount))==0) {
		if(ansCount>0)
		{
			MoneyInfo.MoneyType =  answer[0].QryMoney.MoneyInfo.MoneyType;
			MoneyInfo.balance   =  answer[0].QryMoney.MoneyInfo.balance;
			MoneyInfo.available = answer[0].QryMoney.MoneyInfo.available;
			DeleteAns(&answer);
    }
  }

  return retVal;

}
//---------------------------------------------------------------------------
int __fastcall TTrdCot::QryOrder(AnsiString OrdId,AnsiString PosStr,TOrderInfo **OrdInfo,int &Num)
{
	int      retVal;
	TRequest request;
	TAnswer  *answer;
	int      ansCount;

	request.Head.FuncType = ftQryCurCsn;
	lstrcpyn(request.QryCurCsn.OrderID ,OrdId.c_str(),SEQ_LEN);
	lstrcpyn(request.QryCurCsn.SeqNum,PosStr.c_str(),SEQ_LEN);
	request.QryCurCsn.MaxRecord = Num;

	Num = 0;
	
	if((retVal=Request(request,&answer,ansCount))==0)
	{
    Num = ansCount;

    if(ansCount>0) {
			*OrdInfo =new TOrderInfo[Num];

			for(int i=0;i<Num;i++)
			{
        memcpy(&((*OrdInfo)[i]),&(answer[i].QryCurCsn.OrderInfo),sizeof(TOrderInfo));
      }

      DeleteAns(&answer);
    }
  }

  return retVal;

}

int __fastcall TTrdCot::QryTrade(AnsiString OrdId,AnsiString PosStr,TTradeInfo **TrdInfo,int &Num)
{
	int      retVal;
	TRequest request;
	TAnswer  *answer;
	int      ansCount;

	request.Head.FuncType = ftQryCurTrd;
	lstrcpyn(request.QryCurTrd.OrderID ,OrdId.c_str(),SEQ_LEN);
	lstrcpyn(request.QryCurTrd.SeqNum,PosStr.c_str(),SEQ_LEN);
	request.QryCurTrd.MaxRecord = Num;
	Num = 0;
  if((retVal=Request(request,&answer,ansCount))==0) {
    Num = ansCount;

    if(ansCount>0) {
			*TrdInfo =new TTradeInfo[Num];

      for(int i=0;i<Num;i++) {
        memcpy(&((*TrdInfo)[i]),&(answer[i].QryCurTrd.TrdInfo),sizeof(TTradeInfo));
      }

      DeleteAns(&answer);
    }
  }

  return retVal;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot::QryStocks(market_type Market,TStockInfo **StockInfo,int &Num)
{
  int      retVal;
  TRequest request;
  TAnswer  *answer;
  int      ansCount;

  request.Head.FuncType = ftQryStocks;
	request.QryStocks.Market =Market;

  if((retVal=Request(request,&answer,ansCount))==0) {
    Num = ansCount;

    if(ansCount>0) {
      *StockInfo =new TStockInfo[Num];

      for(int i=0;i<Num;i++) {
        memcpy(&((*StockInfo)[i]),&(answer[i].QryStocks.StockInfo),sizeof(TStockInfo));
      }

      DeleteAns(&answer);
    }
  }

  return retVal;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot::Order( AnsiString SecuID,
												double Price,
												int Num,
												market_type Market,
												order_type OrdType,
												AnsiString &ContractID)
{
  int      retVal;
  TRequest request;
  TAnswer  *answer;
  int      ansCount;

	request.Head.FuncType = ftOrder;
	strcpy(request.Order.SecuID,SecuID.c_str());
	request.Order.Price = Price;
	request.Order.Num   = Num;
	request.Order.Type=OrdType;
	request.Order.Market = Market;

  if((retVal=Request(request,&answer,ansCount))==0) {
    if(ansCount>0) {
      ContractID = answer[0].Order.ContractID;
      DeleteAns(&answer);
    }
  }

  return retVal;
}
//---------------------------------------------------------------------------
int __fastcall TTrdCot::Undo( AnsiString ContractID, market_type Market)
{
  int      retVal;
  TRequest request;
  TAnswer  *answer;
  int      ansCount;

  request.Head.FuncType = ftUndo;
  strcpy(request.Undo.ContractID,ContractID.c_str());
	request.Undo.Market   = Market;

  if((retVal=Request(request,&answer,ansCount))==0) {
    if(ansCount>0) { DeleteAns(&answer); }
  }

  return retVal;
}
//---------------------------------------------------------------------------

int __fastcall TTrdCot::GetLastError(AnsiString &ErrorText,AnsiString &Sender)
{
  int      retVal;
  TRequest request;
  TAnswer  *answer;
  int      ansCount;

  request.Head.FuncType = ftGetLastErr;
	retVal=Request(request,&answer,ansCount);
	if(retVal==0) {

    if(ansCount>0)
		{

			retVal    = answer[0].GetLastError.Error.ErrorCode;
			Sender    = answer[0].GetLastError.Error.Sender;
			ErrorText = answer[0].GetLastError.Error.Text;

      DeleteAns(&answer);
      return retVal;
    }
    else
    {
			ErrorText="";
      Sender="";
      return 0;
    }
  }
  else
  {
		Sender="PTRDDLL_RM";
		ErrorText="Not support this function";
    return retVal;
  }
}
 