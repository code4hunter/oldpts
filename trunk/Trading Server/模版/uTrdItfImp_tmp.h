//---------------------------------------------------------------------------

#ifndef uTrdItfImpH
#define uTrdItfImpH

#include "UTrdItfBase.h"
#include <string>

#define PLUGINNAME "xxx"

////////////////////////////////////////////////////////////////////////////
class TTrdItfImp : public TTrdItfBase
{
public:
	typedef struct
	{
		
	} TSetup;

private:	// User declarations

public:		// User declarations
	TTrdItfImp(const char *psetupfile,ADDLOG plogfunc);
	virtual ~TTrdItfImp();

	//初始化
	int Init();
	
	//设置帐号
	int SetAccount(); 

	//资金查询
	int QryMoney();

	//当日委托查询
	int QryCurCsn();

	//当日成交查询
	int QryCurTrd();

	//查询帐号中所有的股份
	int QryStocks();

	//委托和撤单
	int Order();
	int Undo();

	virtual market_type  ConvertMarketType(const char *t);
	virtual order_type   ConvertOrderType(const char *t);
	virtual order_state  ConvertOrderState(const char *t);
	virtual pos_direction ConvertPosDir(const char *t);
	virtual money_type   ConvertMoneyType(const char *t);

	virtual char *  ConvertMarketType(market_type t);
	virtual char *  ConvertOrderType(order_type t);
	virtual char *  ConvertOrderState(order_state t);
	virtual char *  ConvertPosDir(pos_direction t);
	virtual char *  ConvertMoneyType(money_type t);

	//将配置信息读出来,如果没有获取完整的配置信息返回false
	virtual bool GetConfig(void);
	//将配置信息回写到配置文件
	virtual void SetConfig(void);
	//关闭中间件链接
	virtual void CloseLink(void);

	virtual int KeepAlive(void);
};

//---------------------------------------------------------------------------
#endif
