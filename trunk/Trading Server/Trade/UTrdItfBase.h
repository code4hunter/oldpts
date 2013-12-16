//------------------------------------------------------------------------------
#ifndef UTrdItfBaseH
#define UTrdItfBaseH
//------------------------------------------------------------------------------
#include "..\..\common\BHCmnBase\DebugStr.h"
#include "..\..\common\BHCmnBase\UTrdStruct.h"
#include "UTrdStruct_Rm.h"
#include "UTrdItfAPI.h"
//------------------------------------------------------------------------------

class TTrdItfBase : public TTrdItfAPI
{
public:
	CRITICAL_SECTION CS;

  bool FHasSetAccInfo;           //是否已经设置帐号
  TRequest     FRequest;         //申请
  TRequest     FSetAccRequest;
  TAnswer      **FAnswer;        //回复
	TAnswer      *FAnsBuf;
  int          *FAnsCount;       //回复数量
  int          FBufCount;
	TInterfaceError FLastError;
	char FSetupFile[MAX_PATH+1];   //配置文件
	TAccountInfo FAccInfo;         //帐号信息
	void  NewAns(int AnsCount);    //生成应答内存空间
	bool  SetAnsCount(int AnsCount); // return true if AnsCount less than FBufCount
	virtual int  FreeAnswer( TAnswer *as=NULL);//销毁申请的内存，无需重载此函数
	virtual int  Request(TRequest &Request,TAnswer **Answer,int &AnsCount);
	virtual char * GetStockAccountByType(account_type at); //获取股东帐户 ，无需重载此函数
	virtual char * GetStockAccountByMarket(market_type mt);
	virtual void SetAccountByType(account_type at,const char* account,const char* pwd);

	TTrdItfBase(const char *psetupfile,ADDLOG plogfunc);
	virtual  ~TTrdItfBase();

	void lock(void);
	void unlock(void);
	int GetAccountInfo(void);
	void SetLogout(void);
	bool AutoLogin(void);
public:
	// 实现如下函数
	virtual int  Init()=0;         //初始化
	virtual int  SetAccount(bool useOldSession=false)=0;   //登录柜台中间件
	//////查询函数//////
	virtual int  QryMoney()=0;     //资金查询
	virtual int  QryCurCsn()=0;    //当日委托查询
	virtual int  QryCurTrd()=0;    //当日成交查询
	virtual int  QryStocks()=0;    //查询帐号中所有的股份
	virtual int  GetLastError();   //获取最后错误
	virtual void SetLastError(int code ,TCHAR type ,const TCHAR* sender,const TCHAR * fmt,...);   //Set FLastError and ODS error

	//////交易函数/////
	virtual int  Order()=0;        //委托
	virtual int  Undo()=0;         //委托撤单

  //将接口参数转变成标准参数
	virtual market_type  ConvertMarketType(const char *t)=0;
	virtual order_type   ConvertOrderType(const char *t)=0;
	virtual order_state  ConvertOrderState(const char *t)=0;
	virtual pos_direction ConvertPosDir(const char *t)=0;
	virtual money_type   ConvertMoneyType(const char *t)=0;

	virtual char *  ConvertMarketType(market_type t)=0;
	virtual char *  ConvertOrderType(order_type t)=0;
	virtual char *  ConvertOrderState(order_state t)=0;
	virtual char *  ConvertPosDir(pos_direction t)=0;
	virtual char *  ConvertMoneyType(money_type t)=0;

	//将配置信息读出来,如果没有获取完整的配置信息返回false
	virtual bool GetConfig(void)=0;
	//将配置信息回写到配置文件
	virtual void SetConfig(void)=0;
	//关闭中间件链接
	virtual void CloseLink(void);
	//如需要发送心跳则实现此函数
	virtual int  KeepAlive(void){return 0;};

	//将字符串时间转换到整型时间 hhmmss yyyymmdd
	virtual long ConvertTimeToInt(const char *t );
	virtual long ConvertDateToInt(const char *t );
};
//------------------------------------------------------------------------------
#endif
