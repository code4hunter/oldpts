//---------------------------------------------------------------------------
#ifndef uTrdItf_TestH
#define uTrdItf_TestH

#include <vector>
#include <list>
#include <iostream>
using namespace std;

#include "DebugStr.h"
#include "UTrdItfBase.h"
//#include "uPTSDB.h"

#include "HQPoolSvrLib_OCX.h"
//---------------------------------------------------------------------------
#define PLUGINNAME "测试模拟接口"

class TTrdItfTest : public TTrdItfBase
{
private:
	static CRITICAL_SECTION m_CS;
	static vector<TOrderInfo> m_orders;
	static vector<TTradeInfo> m_deals;
	static LONG m_Order_ID;
	static LONG m_trd_id;
	static LONG m_ref_count;

	float m_rate_per_match;  // 每次成交的比率占总委托量
	float m_system_cancel_probability; // 系统撤单的百分比
	float m_cancel_fault_probability; // 撤单失败的百分比，即撤单后又成交了
	bool  m_report_withdraw;
  bool  m_use_hq; // 是否使用真实行情撮合

	vector<long> m_orderid;
	//TdmPTSDB *m_ptsdb;
	String PTSConStr;
	AnsiString FAccount;
	//vector<TStockInfo> m_positions;

	TPool *FPool;
public:
	TTrdItfTest(const char *psetupfile,ADDLOG plogfunc);
	virtual ~TTrdItfTest();

	// 实现如下函数
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
	virtual market_type  ConvertMarketType(const char *t){};
	virtual order_type   ConvertOrderType(const char *t){};
	virtual order_state  ConvertOrderState(const char *t){};
	virtual pos_direction ConvertPosDir(const char *t){};
	virtual money_type   ConvertMoneyType(const char *t){};

	virtual char *  ConvertMarketType(market_type t){return "";};
	virtual char *  ConvertOrderType(order_type t){return "";};
	virtual char *  ConvertOrderState(order_state t){return "";};
	virtual char *  ConvertPosDir(pos_direction t){return "";};
	virtual char *  ConvertMoneyType(money_type t){return "";};

	//将配置信息读出来,如果没有获取完整的配置信息返回false
	virtual bool GetConfig(void);
	//将配置信息回写到配置文件
	virtual void SetConfig(void);
	//关闭中间件链接
	virtual void CloseLink(void);
	virtual int  KeepAlive(void);

	void lock_g(void);
	void unlock_g(void);
};


#endif
