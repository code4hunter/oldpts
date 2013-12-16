//---------------------------------------------------------------------------

#ifndef uItfTrdTrdSvrH
#define uItfTrdTrdSvrH

#include <SysUtils.hpp>
#include <IniFiles.hpp>
#include <StrUtils.hpp>

#include "UItfTrd.h"
#include "UItfTrd1.0.h"
#include "UTrdItfBase.h"
#include "uDmPTSRF.h"
#include "uAtuoQry.h"

#define PLUGINNAME "BHTrdSvr"
//---------------------------------------------------------------------------
class TTrdItf_TrdSvr : public TTrdItfBase
{
private:
	String FUDLFile;
	//bool FAutoGetOrdRep; //if ture autu qry ord by orderid one by one,and save to database
	int FPTrdDllVersion; // 0,1,2 (0 means manual order and fill order no interface)
	String FDllName;// dynamic lib name of PTrdDll_RM.dll
	String FServerInfo; //Remote TrdSvr address and port like ip:port
	TItfTrd *FItfTrd;
	PTRDDLL1::TItfTrd1 *FItfTrd1;
	query_orders FQryOrder;
	TDataModule1 *DataModule1;
protected:
	String FAccount;
public:
	TTrdItf_TrdSvr(const char *psetupfile,ADDLOG plogfunc);
	virtual ~TTrdItf_TrdSvr();

	virtual int  Init();         //初始化

	virtual int  SetAccount();   //登录柜台中间件

	//////查询函数//////
	virtual int  QryMoney();     //资金查询

	virtual int  QryCurCsn();		//当日委托查询
	
	virtual int  QryCurTrd();    //当日成交查询

	virtual int  QryStocks();    //查询帐号中所有的股份
	
	virtual int  GetLastError();	 //获取最后错误

	//////交易函数/////
	virtual int  Order();        //委托

	virtual int  Undo();        //委托撤单

	//将接口参数转变成标准参数
	virtual market_type  ConvertMarketType(const char *t){return mtNo;}
	virtual order_type   ConvertOrderType(const char *t){return otNo;}
	virtual order_state  ConvertOrderState(const char *t){return osno;}
	virtual pos_direction ConvertPosDir(const char *t){return pdNo;}
	virtual money_type   ConvertMoneyType(const char *t){return motNo;}

	virtual char *  ConvertMarketType(market_type t){return "";}
	virtual char *  ConvertOrderType(order_type t){return "";}
	virtual char *  ConvertOrderState(order_state t){return "";}
	virtual char *  ConvertPosDir(pos_direction t){return "";}
	virtual char *  ConvertMoneyType(money_type t){return "";}

	//将配置信息读出来,如果没有获取完整的配置信息返回false
	virtual bool GetConfig(void);

	//将配置信息回写到配置文件
	virtual void SetConfig(void);

	//关闭中间件链接
	virtual void CloseLink(void);

	virtual int  KeepAlive(void);
};


#endif
