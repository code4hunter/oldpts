//---------------------------------------------------------------------------
#ifndef UTrdCotH
#define UTrdCotH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "UTrdStruct.h"
#include "UTrdStruct_Rm.h"
//---------------------------------------------------------------------------
class TTrdCot
{
private:

protected:
  virtual int __fastcall Request(TRequest Request,TAnswer **Answer,int &AnsCount)=0; //处理申请
  virtual int __fastcall DeleteAns(TAnswer **Answer)=0;
public:
	__fastcall TTrdCot();
	virtual __fastcall ~TTrdCot();

	int __fastcall Init(void);  //初始化
	int __fastcall Login(AnsiString Account,account_type Type,AnsiString PW); //设置帐号

  //////查询函数//////
	int __fastcall QryMoney(money_type MoneyType,TMoneyInfo &MoneyInfo); //资金查询
	int __fastcall QryOrder(AnsiString OrdId,AnsiString PosStr,TOrderInfo **OrdInfo,int &Num); //当日委托查询
	int __fastcall QryTrade(AnsiString OrdId,AnsiString PosStr,TTradeInfo **TrdInfo,int &Num); //当日成交查询
	int __fastcall QryStocks(market_type Market,TStockInfo **StockInfo,int &Num); //查询帐号中所有的股份
	int __fastcall GetAccInfo(TAccountInfo &AccInfo); //取得帐号信息
	//////交易函数/////
	int __fastcall Order( AnsiString SecuID,
												double Price,
												int Num,
												market_type Market,
												order_type OrdType,
												AnsiString &ContractID);

	int __fastcall Undo( AnsiString ContractID, market_type Market); //委托撤单
	//释放内存
	int __fastcall FreeAnswer(void *mem)
	{
		delete [] mem;
		return 0;
	}
  //获取错误信息
	int __fastcall GetLastError(AnsiString &ErrorText,AnsiString &Sender);
};
//---------------------------------------------------------------------------
#endif

