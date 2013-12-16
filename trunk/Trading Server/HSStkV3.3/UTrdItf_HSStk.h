//---------------------------------------------------------------------------
#ifndef UTrdItf_HSStkH
#define UTrdItf_HSStkH

#include <list>
#include <SysUtils.hpp>
#include <SyncObjs.hpp>
#include "UTrdItfBase.h"
#include "HsCommX_OCX.h"


#define ERR_UNKNOW_ACCOUNT_TYPE  -100
#define ERR_SEND_FAULT  		 -101
#define ERR_RECV_FAULT  		 -102
#define ERR_NO_ACK  			 -104  //无相应
#define ERR_OTHERS  			 -103
#define ERR_UNIMPLEMENTED   	 -200  //未实现


#define PLUGINNAME "恒生股票(华润)3.3"
//日期格式 YYYYMMDD
//时间格式：HHMMSS

using namespace std;
////////////////////////////////////////////////////////////////////////////
class TTrdItf_HSStk : public TTrdItfBase
{
public:

	enum t_exchange_type
	{
		etqt	= '0',  //－ 前台未知交易所
		etsh	= '1',  //－  上海
		etsz	= '2',  //－  深圳
	};

	enum t_entrust_way
	{
		ewzz	= '0',//: 自助委托
		ewdh	= '1',//: 电话委托
		ewzl	= '2',//: 驻留委托
		ewyc	= '3',//: 远程委托
		ewgt	= '4',//: 柜台委托
		ewmy	= '5',//: 漫游委托
		ewfz	= '6',//: 分支委托
		ewin	= '7',//: internet委托
	};

	enum t_entrust_status
	{
		eswb		= '0',//未报
		esdb        = '1',//待报
		esyb		= '2',//已报
		esybdc		= '3',//已报待撤
		esbcdc		= '4',//部成待撤
		esbc		= '5',//部撤
		esyc		= '6',//已撤
		esbcn		= '7',//部成
		esycn		= '8',//已成
		esfd		= '9',//废单
		escf        = 'A',//撤废
		esdmq       = 'W' //待明确

		/*
		'0'	未报
		'1'	待报
		'2'	已报
		'3'	已报待撤
		'4'	部成待撤
		'5'	部撤
		'6'	已撤
		'7'	部成
		'8'	已成
		'9'	废单
		'A'	撤废
		'W'	待明确
		*/
	};

	enum t_money_type
	{
		mtrmb		= '0',//人民币
		mtusd 	    = '1',// 美圆
		mthkd		= '2',//港币
	};

	enum t_entrust_bs
	{
		ebbuy		= '1',//-- 买入
		ebsell		= '2',//-- 卖出
	};

	enum t_query_direction
	{
		qdhis		= '0',//0.往后翻”是指取从起始日期或起始序号起的小的记录，即查询已经查询过的记录。（参考‘约定释义’—定位串）
		qdnext		= '1',//1.向前翻”是指取比起始日期或起始序号起的大的记录，
	};

	enum t_entrust_type
	{
		ettrd			= '0',// 买卖
		etqry			= '1',// 查询
		etwithdraw		= '2',// 撤单
		etpatch			= '3',// 补单
	};

	enum t_entrust_prop   //委托属性
	{
		epbs = '0',	   //   买卖
		/*
		eppg = '1',    //	配股
		epzt = '2',    //	转托
		epsg = '3',    //	申购
		ephg = '4',    //	回购
		epps = '5',    //	配售
		epzd = '6',    //	指定
		epzg = '7',    //	转股
		ephs = '8',    //	回售
		epgx = '9',    //	股息
		epszpsqr='A',    //	深圳配售确认
		eppsfq ='B',    //	配售放弃
		epwdzy ='C',    //	无冻质押
		epdjzy ='D',    //	冻结质押
		epwdjy ='E',    //	无冻解押
		epjdjy ='F',    //	解冻解押
		*/
		epetfss='N',    //	etf申购，此时买入方向1申购 2赎回
		/*
		eptp = 'H',    //	投票
		'Y',    //	要约收购预受
		'J',    //	预受要约解除
		'K',    //	基金设红
		'L',    //	基金申赎
		'M',    //	跨市转托
		*/
		epetfqzxq = 'P'    //	权证行权
		/*
		'Q',    //	对手方最优价格
		'R',    //	最优五档即时成交剩余转限价
		'S',    //	本方最优价格
		'T',    //	即时成交剩余撤销
		'U',    //	最优五档即时成交剩余撤销
		'V',    //	全额成交并撤单
		'f',    //	质押出入库
        */
	};

	enum t_real_status	//成交状态
	{
		rscj = '0',//	成交
		rsfd = '2', //	废单
		rsqr = '4'	//确认
	};

	enum t_stock_type	//证券类别
	{
		st = '0'	//股票
	};

	enum t_entrust_direction	//委托方向
	{
		edgpmr = '1', //  股票买入
		edgpmc = '2', //  股票卖出
		//3	开基申购
		//4	开基赎回
		//5	开基认购
		edqzxq = '6',//	权证行权
		//A	债券买入
		//B	债券卖出
		//(	质押出库
		//)	质押入库
		//C	融资回购
		//D	融券回购
		//G	沪债转股
		//H	深债转股
		//J	转债回售
		edetfrh = 'M',//	ETF赎回
		edetfsg = 'N'//	ETF申购
		//T	网络投票
		//g	上海申购
		//h	深圳申购
	};


	typedef struct
	{
		String	SvrIp;
		int		SvrPort;
		int     Protocol;         //1,2(TCP,SPX)
		int     TimeOut;          //发送和接收超时秒
		long    KeyCipher;        // 0,1 (unuse or use key)
		String  KeyDeKey;         //16位长度key
		bool    debug_mode;       //是否为诊断模式
		String  l_op_code ;       //柜员号
		String  vc_op_password;   //柜员密码
		String  op_entrust_way;   //委托方式
		String	op_station;       //操作站点/电话号码    MAC
		int  branch_no;        //营业部编号
	} THSFFSet;

private:	// User declarations
	TComm*		FItf;
	THSFFSet	FHSFFSet;
	AnsiString FAccount;
	int SendAndReceive();
	int QryAccount( t_exchange_type et );
    int login(void);
    bool FDisconnected;
public:		// User declarations
	TTrdItf_HSStk(const char *psetupfile,ADDLOG plogfunc);
	virtual ~TTrdItf_HSStk();

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
};

//---------------------------------------------------------------------------
#endif
