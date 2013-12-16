/*
 *  DESC: 顶点中间件内部接口
 *  FILE: UTrdItf_DD
 *  BY:   CodeHunter
 */

//---------------------------------------------------------------------------
#ifndef UTrdItf_DDABOSSH
#define UTrdItf_DDABOSSH

#include "FixCommWapp.h"
#include "UTrdItfBase.h"
#include <Classes.hpp>

#define PLUGINNAME "顶点ABOSS"
//---------------------------------------------------------------------------
/*
  1 、交易所 := { SH,SZ }
  2 、买卖类别 := { 1,2,3,4,8,-1,-2,-3,-4 }  -----29 ETF 申购--30	ETF赎回

  3 、买卖类别说明 := { 买入,卖出,配股,转托,申购,撤买,撤卖,撤配,撤转 }
  4 、委托来源 := { GT,CK,RJ,DH,YC,IN }
	 	  GT :柜台,CK:磁卡,RJ:热键,DH:电话,YC:远程,IN:Internet
  5 、处理结果 := { 0,1,2,-1,-2,x }
	 	  0：表示委托没有申报到交易所，有未申报和撤消成功两种情况。
	 	  1：表示委托已申报到交易所而交易所还没有返回结果。
	 	  2：表示交易所已处理。应用程序应根据委托数量、成交数量和撤单数量作判断。
	 	  -1、-2：表示委托已撤消。
	 	  <-10：表示该委托为无效委托。
      处理结果说明 := { 未 申 报,申 报 中,已 申 报,撤消成功,全部成交,部份成交,无效委托 }
   6 、停牌标志 := { 0,1 } 1:停牌
	 7 、日期格式为yyyy:mm:dd
   8 、币种:={RMB,USD,HKD}
 */

#define FUNC_JY_ETFSGSH  13018

class TTrdItf_DDABOSS : public TTrdItfBase
{
public:
  typedef struct
  {
    char pUser[10];     //操作柜员
    char pWtfs[3];      //RJ:热键,DH:电话,YC:远程,CK:刷卡
    char pYyb[10];      //本地营业部
    char pRight[100];   //校验串(测试版未使用)
    char pDest[50];     //顶点处理机地址=地址,端口号/协议例如：
                        //00ABCDEF,0123456789AB,8001/spx
                        //或 200.200.200.200,9001/tcp
    char pRemote[100];  //未使用
  } TDDABOSSSet;

	//void YYYYMMDD2DingDian(char *s,char *d,char sp='.');
	//void DingDian2YYYYMMDD(char *s,char *d,char sp='.');
  //char DDTypeToType(char *dd_type);
private:
  aboss_3rd FDll;
	TDDABOSSSet FSet;
  void     *FFix;
  char      FKHH[13];

  int  GetGDZH(void* pFix, char *pKHH, TAccountInfo *ai);
  int  GetZJZH(void* pFix, char *pKHH, TAccountInfo *ai);

public:
  TTrdItf_DDABOSS(const char *psetupfile,ADDLOG plogfunc);
  virtual  ~TTrdItf_DDABOSS();

	virtual int  Init();         //初始化
	virtual int  SetAccount();   //登录柜台中间件

	//////查询函数//////
	virtual int  QryMoney();     //资金查询
	virtual int  QryCurCsn();    //当日委托查询
	virtual int  QryCurTrd();    //当日成交查询
	virtual int  QryStocks();    //查询帐号中所有的股份

	//////交易函数/////
	virtual int  Order();        //委托
	virtual int  Undo();         //委托撤单

  //将接口参数转变成标准参数
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
private:
  void SetError(void);
};

#endif
