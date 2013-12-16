#ifndef UItfTrd2H
#define UItfTrd2H
//---------------------------------------------------------------------------
#include <windows.h>
#include "UTrdStruct.h"
//---------------------------------------------------------------------------
class TItfTrd
{
private:
	typedef void*(*TNewTrdCot)(void);
	typedef void(*TDelTrdCot)(void *TrdCot);
	typedef int (*TInit)(void *TrdCot,const char * ServerInfo);
	typedef int (*TLogin)(void *TrdCot,const char * Account,account_type Type,const char* PW);
	typedef int (*TQryMoney)(void *TrdCot,money_type MoneyType,TMoneyInfo &MoneyInfo);
	typedef int (*TQryOrder)(void *TrdCot,const char* OrdId,const char * PosStr,TOrderInfo **OrdInfo,int &Num);
	typedef int (*TQryTrade)(void *TrdCot,const char*  OrdId,const char* PosStr,TTradeInfo **TrdInfo,int &Num);
	typedef int (*TQryStocks)(void *TrdCot,market_type Market,TStockInfo **StockInfo,int &Num);
	typedef int (*TOrder)(void *TrdCot,const char* SecuID,double Price,int Num,market_type Market,order_type OrdType,char * ContractID,int ContractLength);
	typedef int (*TUndo)(void *TrdCot,const char* ContractID, market_type Market);
	typedef int (*TGetAccInfo)(void *TrdCot,TAccountInfo &AccInfo);
	typedef void(*TFreeAnswer)(void *TrdCot,void *mem);
	typedef int (*TGetLastError)(void *TrdCot,char *ErrorText,int ErrorLength,char *Sender,int SenderLength);

private:

	void           *FTrdCot;   //指向DLL中的柜台接口
	HINSTANCE      FDllHandle; //动态链接库句柄

	TNewTrdCot     FNewTrdCot;
	TDelTrdCot     FDelTrdCot;
	TInit          FInit;
	TLogin         FLogin;
	TQryMoney      FQryMoney;
	TQryOrder      FQryOrder;
	TQryTrade      FQryTrade;
	TQryStocks     FQryStocks;
	TGetAccInfo    FGetAccInfo;
	TFreeAnswer    FFreeAnswer;
	TOrder         FOrder;
	TUndo          FUndo;
	TGetLastError  FGetLastError;

	bool load_libray(const char * dllname);

public:

	TItfTrd();
	~TItfTrd();

	//初始化(ServerInfo = ip:port)
	int  Init        (const char * ServerInfo);
	//使用帐号登录
	int  Login       (const char * Account,account_type Type,const char* PW);
	//资金查询
	int  QryMoney    (money_type MoneyType,TMoneyInfo &MoneyInfo);
	//查询当日委托
	int  QryOrder    (const char* OrdId,const char * PosStr,TOrderInfo **OrdInfo,int &Num);
	//查询当日交易
	int  QryTrade    (const char*  OrdId,const char* PosStr,TTradeInfo **TrdInfo,int &Num);
	//查询股份
	int  QryStocks   (market_type Market,TStockInfo **StockInfo,int &Num);
	//委托    ContractID输入为空或者输入一位价格精度(1,2,3,4)
	int  Order       (const char* SecuID,double Price,int Num,market_type Market,order_type OrdType,char * ContractID,int ContractLength);
	//委托撤单
	//返回值
	// 0 : 撤单成功
	// -100: 撤单失败，原因是已经成交
	// -200: 撤单失败，原因是该委托已废
	int  Undo        (const char* ContractID, market_type Market=mtNo);
	//取得帐号信息
	int  GetAccInfo  (TAccountInfo &AccInfo);
	//用户释放查询函数返回的内存
	void FreeAnswer  (void *mem);
	//获取最后错误信息
	int  GetLastError(char *ErrorText,int ErrorLength,char *Sender,int SenderLength);

	//新建一个远程接口
	void Open(void)
	{
		if( NULL == FDllHandle )  return;
		if(FTrdCot) Close();
		FTrdCot = FNewTrdCot();
	}

	//关闭当前远程接口
	void Close(void)
	{
		if( NULL == FDllHandle )  return;
		if(FTrdCot) FDelTrdCot(FTrdCot);
		FTrdCot=NULL;
	}
};
//---------------------------------------------------------------------------
#endif
