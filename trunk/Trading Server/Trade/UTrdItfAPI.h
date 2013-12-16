//------------------------------------------------------------------------------
#ifndef UTTrdItfAPIH
#define UTTrdItfAPIH
//------------------------------------------------------------------------------
#include "..\..\common\BHCmnBase\DebugStr.h"
#include "..\..\common\BHCmnBase\UTrdStruct.h"
#include "UTrdStruct_Rm.h"
//------------------------------------------------------------------------------

#ifdef PTRADEAPI_EXPORTS
#define PTRADE_API __declspec(dllexport)
#else
#define PTRADE_API __declspec(dllimport)
#endif

PTRADE_API class TTrdItfAPI
{
public:
	// 实现如下函数
	virtual int  Request(TRequest &Request,TAnswer **Answer,int &AnsCount)=0;
	//销毁申请的内存，无需重载此函数
	virtual int  FreeAnswer( TAnswer *as=NULL)=0;
	//关闭中间件链接
	virtual void CloseLink(void)=0;
	//如需要发送心跳则实现此函数
	virtual int  KeepAlive(void)=0;
	//获取股东帐户 ，无需重载此函数
	virtual char * GetStockAccountByType(account_type at)=0;
	virtual char * GetStockAccountByMarket(market_type mt)=0;
};
//------------------------------------------------------------------------------
#endif
