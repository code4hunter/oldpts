//---------------------------------------------------------------------------
#ifndef UTrdItf_HSFFH
#define UTrdItf_HSFFH


#include <SysUtils.hpp>
#include <SyncObjs.hpp>
#include "UTrdItfBase.h"
#include "t2sdk_interface.h"
#include <boost\shared_ptr.hpp>

#include <list>

#define ERR_UNKNOW_ACCOUNT_TYPE  -100
#define ERR_SEND_FAULT  		 -101
#define ERR_RECV_FAULT  		 -102
#define ERR_NO_ACK  			 -104  //无相应
#define ERR_OTHERS  			 -103
#define ERR_UNIMPLEMENTED   	 -200  //未实现


#define PLUGINNAME "恒生期货T2版"
//日期格式 YYYYMMDD
//时间格式：HHMMSS

using namespace std;

class order_keeper;
typedef boost::shared_ptr<order_keeper> ORDERKEEPERPTR;
////////////////////////////////////////////////////////////////////////////
class TTrdItf_HSFF : public TTrdItfBase
{
public:
	enum t_entrust_status
	{
		eswb		= '0',//未报
		esyb		= '2',//已报
		esdc1		= '3',//待撤
		esdc2		= '4',//待撤
		esbc		= '5',//部撤
		esyc1		= '6',//已撤
		esyc2		= '7',//已撤
		esyc		= '8',//已成
		esyf		= '9',//已废

		/*
		0 未报
		1 待报
		2 已报
		3 已报待撤
		4 部分待撤
		5 部撤
		6 已撤
		7 部成
		8 已成
		9 废单
		10 待确定


		0 未报
		1 待报
		2 已报
		3 已报待撤
		4 部成待撤
		5 部撤
		6 已撤
		7 部成
		8 已成
		9 废单
		C 正报
		D 撤废
		*/
	};

	enum t_money_type
	{
		mtrmb		= '0',//人民币
		mtusd 	= '1',// 美圆
		mthkd		= '2',//港币
	};

	enum t_entrust_bs
	{
		ebbuy		= '1',//-- 买入
		ebsell		= '2',// -- 卖出
	};

	enum t_order_direction
	{
		od_open = '1', //开仓
		od_close= '2',  //平仓
		od_close_today='4'//平今
	};

	enum t_query_direction
	{
		qdahead		= '0',//--往前翻（顺序）
		qdnext		= '1',//--往后翻（倒序）
	};

	enum t_entrust_type
	{
		ettrd			= '0',// 买卖
		etqry			= '1',// 查询
		etwithdraw		= '2',// 撤单
		etpatch			= '3',// 补单
	};

	struct THSFFSet
	{
		int     TimeOut;
		AnsiString	op_branch_no  ;   //操作分支号
		AnsiString	op_station;       //操作站点/电话号码    MAC
		AnsiString	op_entrust_way;   //操作委托方式		 t_entrust_way
		AnsiString	branch_no;  	  //营业部号			 0000
		AnsiString  hs_licence;       //交易功能授权串
		bool    gen_check_info;
	};
private:	// User declarations
	CConfigInterface * _config;
    CConnectionInterface *_connection ;
   	THSFFSet FHSFFSet;
	//AnsiString FAccount;
	bool _createKeeper;
	ORDERKEEPERPTR _ord_keeper;
	int SendAndReceive(int funid,IF2Packer *in,IF2UnPacker **out);
public:		// User declarations
	TTrdItf_HSFF(const char *psetupfile,ADDLOG plogfunc,bool createKeeper=true);
	virtual ~TTrdItf_HSFF();

	int Init();  //初始化
	int SetAccount(); //设置帐号

	//////查询函数//////
	int QryMoney(); 	//资金查询
	int QryCurCsn();	//当日委托查询
	int QryCurTrd();	//当日成交查询
	int QryStocks();	//查询帐号中所有的股份
	int Order();
	int Undo(); //委托撤单

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

	int QryOrderByOrdid(TTradeInfo * ti);
};

//---------------------------------------------------------------------------
#endif
