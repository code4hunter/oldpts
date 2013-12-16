/*-------------------------------------------------------------------------------
注意：
1.结构采用字节对齐
2.凡是字符应当以' '表示为空查询全部
3.凡是字符串应当以" "为空表示查询全部

  4.委托确定及撤单时需要交易密码(TTSC项目需求,20010628)
  5.修改密码请求结构改变（20010728,for all）
  6.客户查询增加股东状态 (FOR TTSC)
  7.约定日委托查询返回增加委托日期(FOR TTSC,20010822)
  8.当日、历史委托查询返回委托来源，区别大宗委托、约定日委托和普通委托(FOR TTSC)
  9.增加请求，funcKHYHXX, 取当前客户的开户银行信息
  ---------------------------------------------------------------------------------
*/

#ifndef __XS_JZApi_Include__
#define __XS_JZApi_Include__

#include <windows.h>

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;

#define JYSJC_WIDTH 		   7
#define JYSBS_WIDTH 		   5
#define HBBS_WIDTH			   5
#define HBMC_WIDTH			   9
#define GDDM_WIDTH			   11
#define ZJZH_WIDTH			   13
#define GDXM_WIDTH			   13
#define KHBS_WIDTH			   13
#define CKBH_WIDTH			   31
#define ZQDM_WIDTH			   8
#define ZQMC_WIDTH			   9
#define YHDM_WIDTH			   3
#define YHMC_WIDTH			   9
#define HTXH_WIDTH			   7
#define DATETIME_WIDTH		   9
#define WTJG_WIDTH			   9
#define WTSL_WIDTH			   9
#define ZYDM_WIDTH			   13
#define JYMM_WIDTH			   11
#define YHMM_WIDTH			   21
#define HBJE_WIDTH			   17
#define QTSM_WIDTH			   9
#define SGPH_WIDTH			   21
#define CXLB_WIDTH			   17
#define YYBDM_WIDTH 		   5
#define YYBMC_WIDTH 		   11
#define ZJZHQZ_WIDTH		   11
#define FZDM_WIDTH			   5
#define QQYXX_WIDTH 		   21

#define ZJBH_WIDTH				21
#define YYKH_XX_WIDTH			2049


typedef struct _Money
{
	DWORD lo_value;
	DWORD hi_value;
}Money;

#define MAX_LONG 0x80000000L

typedef union _U_dw
{
	DWORD dw;
	struct {WORD lo, hi;} w;
}U_dw;

typedef DWORD				   SmallMoney;

#define funcJYSXX			   0			   //取交易所信息
#define funcHBXX			   1			   //取货币信息
#define funcYHXX			   2			   //取银行信息
#define funcZQXX			   3			   //取证券信息
#define funcPLCDCX			   4			   //取可批量撤单信息

#define funcKHJY			   5			   //客户密码校验
#define funcKHCX			   6			   //查询客户信息（股东）
#define funcDMJY			   7			   //证券代码校验
#define funcKMSL			   8			   //取可买数量
#define funcWTQR			   9			   //委托确认
#define funcWTCD			   10			   //委托撤单
#define funcXGMM			   11			   //修改密码

#define funcZJCX			   12			   //资金查询
#define funcGFCX			   13			   //股份查询
#define funcWTCX			   14			   //委托查询
#define funcLSWTCX			   15			   //历史委托查询
#define funcCJCX			   16			   //成交查询
#define funcXGPH			   17			   //查询配号
#define funcLSCJCX			   18			   //历史成交查询
#define funcZJLS			   19			   //查询资金流水（对帐单）

#define funcZJHB			   20			   //资金划拨
#define funcYHYE			   21			   //查询银行余额
#define funcYHGM			   22			   //修改银行密码
#define funcHBCX			   23			   //划拨查询
#define funcHBCD			   24			   //划拨撤单

#define funcPLWTXX			   25			   //取批量委托信息
#define funcYKJS			   26			   //盈亏计算
#define funcXGCB			   27			   //修改成本
#define funcSFMX			   28			   //查询收费明细
#define funcMMJY			   29			   //密码校验（远程用）
#define funcYYB 			   30			   //营业部信息

#define funcXXGMM			   31			   //新修改密码(支持各种登录方式)
#define funcKHYHXX			   32			   //取客户开户银行信息

//TTSC SPECIAL INTERNET API, begin
#define funcYDRWTZJ 			35				//约定日委托增加
#define funcYDRWTXG 			36				//约定日委托修改
#define funcYDRWTSC 			37				//约定日委托删除
#define funcYDRWTCX 			38				//约定日委托查询
#define funcYYKH				39				//预约开户
#define funcYYKHCX				40				//预约开户查询
#define funcHGCX				41				//红股查询
#define funcPXCX				42				//派息查询
//TTSC SPECIAL INTERNET API, end

#define funcAGAIN				99

typedef struct
{
	unsigned short length;		 //长度  (整个数据包长度)
	unsigned short crc ;		 //CRC校验码 //从serio 开始计算 保留
	unsigned short serio;		 //序列号(按请求划分,1开始)
	unsigned char function; 	 //功能号
	unsigned char czfs; 		 //操作方式
	unsigned long status;		 //状态 0正确 其他错误(应答有效)
}tagBLOCK_HEAD;

///////////////////交易所信息//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
}tagJYSXX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM; 				 //交易所代码
	char JYSJC[JYSJC_WIDTH];	 //交易所简称
	char JYSBS[JYSBS_WIDTH];	 //交易所标识
	char HBDM;					 //货币代码
	short GDDMCD;				 //股东代码长度
	short NBGDDMCD; 			 //内部股东代码长度
	short ZQDMCD;				 //证券代码长度
	short NBZQDMCD; 			 //内部证券代码长度
}tagJYSXX_Result;


///////////////////货币信息//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
}tagHBXX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char HBDM;					 //货币代码
	char HBBS[HBBS_WIDTH];
	char HBMC[HBMC_WIDTH];		 //货币名称
}tagHBXX_Result;

///////////////////取营业部全部银行信息//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
}tagYHXX_Request;

///////////////////取客户开户银行信息(天同网上交易适用)
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 // 头信息
	char KHBSLX;			 // 'Z'
	char KHBS[KHBS_WIDTH];		 // 资金帐号
	char YHDM[YHDM_WIDTH];		 // 银行代码
	char HBDM;			 // 货币代码，如果资金帐号不为' '，需要提供正确的货币代码
}tagKHYHXX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char HBDM;					 //货币代码
	char YHDM[YHDM_WIDTH];		 //银行代码
	char YHMC[YHMC_WIDTH];		 //银行名称
	char FQFX;					 //'A' 双方发起 'Y' 银行发起 'Q' 券商发起
	short YHMMCD;				 //银行密码长度
	short ZRMM; 				 //转入需要密码  0不需要密码 1 需要取款密码 2 需要银行密码 3 需要取款/银行密码
	short ZCMM; 				 //转出需要密码 同上
	short YHGM; 				 //可修改银行密码 -1不能修改 0不需要密码 1 需要取款密码 2 需要银行密码 3 需要取款/银行密码
	short YHYE; 				 //查银行余额	  -1不能查	 0不需要密码 1 需要取款密码 2 需要银行密码 3 需要取款/银行密码
	short ZKJEXSCD; 			 //转款金额小数点位数
	short TIMEOUT;				 //等待延时
}tagYHXX_Result;

///////////////////取证券信息/////////////////

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
}tagZQXX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM; 				 //交易所代码
	char JYSJC[JYSJC_WIDTH];	 //交易所简称
	char ZQDM[ZQDM_WIDTH];		 //证券代码
	char ZQMC[ZQMC_WIDTH];		 //证券名称
	char NBZQDM[ZQDM_WIDTH];	 //内部证券代码
	char PYBM[5];				 //拼音编码
}tagZQXX_Result;

///////////////////批量撤单查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char KHBSLX;				 // '0'-'9'交易所代码(参看柜台设置)
	// 'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 // KHBS; 股东代码或资金帐号
	char ZQBSLX;				 // '0'-'9'交易所代码(参看柜台设置)
	char ZQBS[ZQDM_WIDTH];		 // KHBS  股东代码或资金帐号
	char WTJGXX[WTJG_WIDTH];		//委托价格下限
	char WTJGSX[WTJG_WIDTH];		//委托价格上限
}tagPLCDCX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM; 				 //交易所代码
	char GDDM[GDDM_WIDTH];		 //股东代码
	char HTXH[HTXH_WIDTH];		 //合同序号
}tagPLCDCX_Result;

///////////////////客户校验//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 // 头信息
	char GDMS;					 // '0'单股东
	// '1'同资金帐号且同身份证关联
	// '2'同资金帐号关联
	char KHBSLX;				 // '0'-'9'交易所代码(参看柜台设置)
	// 'Z' 资金帐号
	// 'C' 磁卡号
	char KHBS[CKBH_WIDTH];		 // KHBS  股东代码或资金帐号或磁卡号
	char JYMM[JYMM_WIDTH];		 // JYMM  交易密码
}tagKHJY_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char ZJZH[ZJZH_WIDTH];		 //资金帐号
	char JYSDM; 				 //交易所代码
	char JYSJC[JYSJC_WIDTH];	 //交易所简称
	char GDDM[GDDM_WIDTH];		 //股东代码
	char GDXM[GDXM_WIDTH];		 //股东姓名
}tagKHJY_Result;

///////////////////密码校验//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char KHBSLX;				 // '0'-'9'交易所代码(参看柜台设置)
	// 'Z' 资金帐号
	// 'C' 磁卡号
	char KHBS[CKBH_WIDTH];		 //KHBS  股东代码或资金帐号或磁卡号
	char JYMM[JYMM_WIDTH];		 //JYMM  交易密码
}tagMMJY_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
}tagMMJY_Result;

///////////////////客户查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char GDMS;					 // '0'单股东
	// '1'同资金帐号且同身份证关联
	// '2'同资金帐号关联, 有效状态的股东帐号
	// '4'同资金帐号关联, 所有股东帐号
	char KHBSLX;				 // '0'-'9'交易所代码(参看柜台设置)
	// 'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 // KHBS  股东代码或资金帐号
	char JYSDM; 				 // '0'-'9'交易所代码(参看柜台设置)
}tagKHCX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM; 				 //交易所代码
	char JYSJC[JYSJC_WIDTH];	 //交易所简称
	char GDDM[GDDM_WIDTH];		 //股东代码
	char GDXM[GDXM_WIDTH];		 //股东姓名
	char ZJZH[ZJZH_WIDTH];		 //资金帐号
	char ZHZT;				   //股东帐号状态,'0': 正常, 其他异常
}tagKHCX_Result;


///////////////////代码校验//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 // 头信息
	char JYSDM; 				 // '0'-'9'交易所代码(参看柜台设置)
	char GDDM[GDDM_WIDTH];		 // KHBS  股东代码或资金帐号
	char ZQDM[ZQDM_WIDTH];		 // ZQDM  证券代码
}tagDMJY_Request;

typedef struct{
	tagBLOCK_HEAD HEAD; 		 // 头信息
	char JYSDM; 				 //交易所代码
	char JYSJC[JYSJC_WIDTH];	 //交易所名称
	short JW;					 //价位(以厘为基数 1000为1元)
	char ZQDM[ZQDM_WIDTH];		 //证券代码
	char ZQMC[ZQMC_WIDTH];		 //证券名称
	short ZQLB; 				 //证券类别 0股票 1国债 2企业债券 3回购 4基金
	//		   5投资基金 6权证 9转换债券 10实物国债
	//		   11实物企债 12特殊证券
	short JYLX; 				 //交易类型 0正常交易 1申购 2购回 3配号 4还款
	//		   5 中签 6红利
	Money KYZJ; 				 //可用资金
	long KMGS;					 //可卖股票
	char WTGSBZ;				 //委托股手标志 'G' 股 'Z' 张 'S' 手
	char HQGSBZ;				 //行情股手标志
	SmallMoney ZJZS;			 //最近指数
	SmallMoney ZRSP;			 //昨日收盘
	SmallMoney JRKP;			 //今日开盘
	SmallMoney ZJCJ;			 //最新价
	SmallMoney ZGCJ;			 //最高价
	SmallMoney ZDCJ;			 //最低价
	Money CJJE; 				 //成交金额
	long CJSL;					 //成交数量
	SmallMoney MRJG1;			 //申买价1
	long MRSL1; 				 //申买量1
	SmallMoney MRJG2;			 //申买价2
	long MRSL2; 				 //申买量2
	SmallMoney MRJG3;			 //申买价3
	long MRSL3; 				 //申买量3
	SmallMoney MCJG1;			 //申卖价1
	long MCSL1; 				 //申卖量1
	SmallMoney MCJG2;			 //申卖价2
	long MCSL2; 				 //申卖量2
	SmallMoney MCJG3;			 //申卖价3
	long MCSL3; 				 //申卖量3
	SmallMoney ZTJG;			 //涨停价格
	SmallMoney DTJG;			 //跌停价格
	char JGBZ;					 //价格标志  '0'-浮动价 '1'--定价
}tagDMJY_Result;

///////////////////可买数量//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM; 				 // '0'-'9'交易所代码(参看柜台设置)
	char GDDM[GDDM_WIDTH];		 //KHBS  股东代码或资金帐号
	char ZQDM[ZQDM_WIDTH];		 //ZQDM  证券代码
	char WTJG[WTJG_WIDTH];		 //WTJG  委托价格
}tagKMSL_Request;

typedef struct{
	tagBLOCK_HEAD HEAD; 		 //头信息
	long KMSL;					 //可买数量
}tagKMSL_Result;

///////////////////委托确认//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM; 				 // '0'-'9'交易所代码(参看柜台设置)
	char GDDM[GDDM_WIDTH];		 //KHBS  股东代码或资金帐号
	char MMLB;
	char ZQDM[ZQDM_WIDTH];		 //ZQDM  证券代码
	char WTJG[WTJG_WIDTH];		 //WTJG  委托价格
	char WTSL[WTSL_WIDTH];		 //WTSL  委托价格
	char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
	char JYMM[JYMM_WIDTH];		 //JYMM  交易密码
}tagWTQR_Request;

typedef struct{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char HTXH[HTXH_WIDTH];		 //合同序号
	Money KYZJ; 				 //资金本次可用数
	long KYGF;					 //股份本次可用数
}tagWTQR_Result;

///////////////////委托撤单//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char GDMS;					 // '0'单股东
	// '1'同资金帐号且同身份证关联
	// '2'同资金帐号关联
	char JYSDM; 				 //'0'-'9'交易所代码(参看柜台设置)
	//	'Z' 资金帐号
	char GDDM[GDDM_WIDTH];		 // 股东代码或资金帐号
	char HTXH[HTXH_WIDTH];		 // 合同序号
	char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
	char JYMM[JYMM_WIDTH];		 //JYMM  交易密码
}tagWTCD_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
}tagWTCD_Result;

///////////////////修改密码//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM; 				 //'0'-'9'交易所代码(参看柜台设置)
	char GDDM[GDDM_WIDTH];		 // 股东代码或资金帐号
	char JYMM[JYMM_WIDTH];		 // 原密码
	char XJYMM[JYMM_WIDTH]; 	 // 新密码
}tagXGMM_Request;

///////////////////新修改密码//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char KHBSLX;				 // '0'-'9'交易所代码(参看柜台设置)
	//	'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 //KHBS  股东代码或资金帐号
	char JYMM[JYMM_WIDTH];		 // 原密码
	char XJYMM[JYMM_WIDTH]; 	 // 新密码
}tagXXGMM_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
}tagXGMM_Result;

///////////////////资金查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char KHBSLX;				 // '0'-'9'交易所代码(参看柜台设置)
	char KHBS[KHBS_WIDTH];		 //KHBS  股东代码或资金帐号
}tagZJCX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char ZJZH[ZJZH_WIDTH];		 //资金帐号
	char HBDM;					 //货币代码
	Money YE;					 //余额
	Money KYS;					 //可用数
}tagZJCX_Result;

///////////////////股份查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char GDMS;					 // '0' 单股东
	// '1'同资金帐号且同身份证关联
	// '2'同资金帐号关联
	char CXMS;					 // '0'股份
	// '1'资金同股份(ZQDM 为空)
	char KHBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	//	'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 // 股东代码或资金帐号
	char ZQBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	char ZQBS[ZQDM_WIDTH];		 //证券标识
}tagGFCX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM; 				 //交易所代码 'Z' 资金
	char JYSJC[JYSJC_WIDTH];	 //交易所简称
	char GDDM[GDDM_WIDTH];		 //股东代码   如为资金则为资金帐号
	char GDXM[GDXM_WIDTH];		 //股东姓名
	char ZQDM[ZQDM_WIDTH];		 //证券代码   如为资金则为货币代码
	char ZQMC[ZQMC_WIDTH];		 //证券名称   如为资金则为货币名称
	Money YE;					 //余额
	Money KYS;					 //可用数
	Money MRDJS;				 //买入冻结
	Money MCDJS;				 //卖出冻结
	Money YCDJS;				 //异常冻结
	Money CKCB; 				 //参考成本
	Money CKCBJG;				 //参考成本价
	Money CKSZ; 				 //参考市值
	Money CKSZJG;				 //参考市价
	Money CKYK; 				 //参考盈亏
}tagGFCX_Result;

///////////////////委托查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char GDMS;					 // '0' 单股东
	// '1'同资金帐号且同身份证关联
	// '2'同资金帐号关联
	char CXMS;					 // '0'全部委托
	// '1'可撤单委托
	// '2'全部委托(不包括撤单委托)[只适用于天同柜台]
	char KHBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	//	'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 // 股东代码或资金帐号
	char ZQBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	char ZQBS[ZQDM_WIDTH];		 // 证券标识
	char HTXH[HTXH_WIDTH];		 // 合同序号
}tagDRWTCX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char WTSJ[DATETIME_WIDTH];	 //委托时间 (HH:MM:SS)
	char HTXH[HTXH_WIDTH];		 //合同序号
	char JYSDM; 				 //交易所代码
	char JYSJC[JYSJC_WIDTH];	 //交易所简称
	char GDDM[GDDM_WIDTH];		 //股东代码
	char GDXM[GDXM_WIDTH];		 //股东姓名
	char ZQDM[ZQDM_WIDTH];		 //证券代码
	char ZQMC[ZQMC_WIDTH];		 //证券名称
	char MMLB;					 //买卖类别
	//'B' 买卖方向为买入
	//'S' 买卖方向为卖出
	//'Z' 买卖方向为转托
	//'G' 转股
	//'H' 回售
	char MMLBSM[QTSM_WIDTH];	 //买卖类别说明
	char CDBZ;					 //撤单状态
	//'0' 正常
	//'1' 申撤
	char CDBZSM[QTSM_WIDTH];	 //撤单状态说明
	SmallMoney WTJG;			 //委托价格
	long WTSL;					 //委托数量
	SmallMoney CJJG;			 //成交价格
	long CJSL;					 //成交数量
	long CDSL;					 //撤单数量
	char WTLY;			//委托来源，用于天同集中交易
	//'0':大宗委托，'1':约定日委托，其他：普通委托	
}tagDRWTCX_Result;

///////////////////历史委托查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char GDMS;					 // '0' 单股东
	// '1'同资金帐号且同身份证关联
	// '2'同资金帐号关联
	char KHBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	//	'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 // 股东代码或资金帐号
	char ZQBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	char ZQBS[ZQDM_WIDTH];		 //证券标识
	char QSRQ[DATETIME_WIDTH];	 //起始日期
	char ZZRQ[DATETIME_WIDTH];	 //终止日期
	char CXTS[DATETIME_WIDTH];	 //查询天数  (起止日期与查询天数只能有一)
}tagLSWTCX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char WTRQ[DATETIME_WIDTH];	 //委托日期
	char HTXH[HTXH_WIDTH];		 //合同序号
	char JYSJC[JYSJC_WIDTH];	 //交易所简称
	char GDDM[GDDM_WIDTH];		 //股东代码
	char GDXM[GDXM_WIDTH];		 //股东姓名
	char ZQDM[ZQDM_WIDTH];		 //证券代码
	char ZQMC[ZQMC_WIDTH];		 //证券名称
	char MMLB;					 //买卖类别
	//'B' 买卖方向为买入
	//'S' 买卖方向为卖出
	//'Z' 买卖方向为转托
	//'G' 转股
	//'H' 回售
	char MMLBSM[QTSM_WIDTH];	 //买卖类别说明
	SmallMoney WTJG;			 //委托价格
	long WTSL;					 //委托数量
	SmallMoney CJJG;			 //成交价格
	long CJSL;					 //成交数量
	long CDSL;					 //撤单数量
	char WTLY;			//委托来源，用于天同集中交易
	//'0':大宗委托，'1':约定日委托，其他：普通委托	
}tagLSWTCX_Result;

///////////////////成交查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char GDMS;					 // '0' 单股东
	// '1'同资金帐号且同身份证关联
	// '2'同资金帐号关联
	char KHBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	//	'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 // 股东代码或资金帐号
	char CXFS;					 // '1'按合同序号合并查询
	// '0'查明细
	// '2'查累计
	char ZQBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	char ZQBS[ZQDM_WIDTH];		 // 证券标识
	char HTXH[HTXH_WIDTH];		 // 合同序号
}tagDRCJCX_Request;

typedef struct {
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM;
	char HTXH[HTXH_WIDTH];		 //合同序号  若为成交累计无效
	char JYSJC[JYSJC_WIDTH];	 //交易所简称
	char GDDM[GDDM_WIDTH];		 //股东代码  若为成交累计无效
	char GDXM[GDXM_WIDTH];		 //股东姓名  若为成交累计无效
	char ZQDM[ZQDM_WIDTH];		 //证券代码
	char ZQMC[ZQMC_WIDTH];		 //证券名称
	char MMLB;
	char MMLBSM[QTSM_WIDTH];	 //买卖类别说明
	char WTSJ[DATETIME_WIDTH];	 //委托时间  若为成交累计无效
	char CJSJ[DATETIME_WIDTH];
	SmallMoney WTJG;			 //委托价格
	long WTSL;					 //委托数量
	SmallMoney CJJG;			 //成交价格
	long CJSL;					 //成交数量
	Money CJJE; 				 //成交金额
}tagDRCJCX_Result;

///////////////////配号查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char GDMS;					 // '0' 单股东
	// '1'同资金帐号且同身份证关联
	// '2'同资金帐号关联
	char KHBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	//	'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 // 股东代码或资金帐号
}tagXGPH_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 // 头信息
	char RQ[DATETIME_WIDTH];	 // 日期 (YYYYMMDD)
	char JYSJC[JYSJC_WIDTH];	 // 交易所简称
	char GDDM[GDDM_WIDTH];		 // 股东代码
	char GDXM[GDXM_WIDTH];		 // 股东姓名
	char HTXH[HTXH_WIDTH];		 // 合同序号
	char ZQDM[ZQDM_WIDTH];		 // 证券代码
	char ZQMC[ZQMC_WIDTH];		 // 证券名称
	long CJSL;					 // 成交数量
	char SGPH[SGPH_WIDTH];		 // 配号号
	char ZQBZSM[QTSM_WIDTH];	 // 中签标志说明
}tagXGPH_Result;

///////////////////历史成交查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char GDMS;					 // '0' 单股东
	// '1'同资金帐号且同身份证关联
	// '2'同资金帐号关联
	char KHBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	//	'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 // 股东代码或资金帐号
	char ZQBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	char ZQBS[ZQDM_WIDTH];		 //证券标识
	char QSRQ[DATETIME_WIDTH];	 //起始日期
	char ZZRQ[DATETIME_WIDTH];	 //终止日期
	char CXTS[DATETIME_WIDTH];	 //查询天数  (起止日期与查询天数只能有一)
	char CXFS;					 // '0'按合同序号合并查询
	// '1'查累计
}tagLSCJCX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char FSRQ[DATETIME_WIDTH];	 //委托日期   查累计无效
	char HTXH[HTXH_WIDTH];		 //合同序号   查累计无效
	char JYSDM;
	char JYSJC[JYSJC_WIDTH];	 //交易所简称 查累计无效
	char GDDM[GDDM_WIDTH];		 //股东代码   查累计无效
	char GDXM[GDXM_WIDTH];		 //股东姓名   查累计无效
	char ZQDM[ZQDM_WIDTH];		 //证券代码
	char ZQMC[ZQMC_WIDTH];		 //证券名称
	char ZYDMSM[ZYDM_WIDTH];	 //买卖类别说明
	char MMLB;
	SmallMoney WTJG;			 //委托价格
	long WTSL;					 //委托数量
	SmallMoney CJJG;			 //成交价格
	long CJSL;					 //成交数量
	Money CJJE; 				 //成交金额
	SmallMoney SXF; 			 //手续费
	SmallMoney YHS; 			 //印花税
	SmallMoney GHF; 			 //过户费
	SmallMoney QSF; 			 //清算费
	SmallMoney JYGF;			 //交易规费
	SmallMoney WTDF;			 //委托单费
	SmallMoney CJDF;			 //成交单费
	SmallMoney CDDF;			 //撤单单费
	Money HZJE; 				 //划帐金额
	Money ZJBCYE;				 //资金本次余额 查累计无效
	long GFBCYE;				 //股份本次余额 查累计无效
}tagLSCJCX_Result;

///////////////////资金流水查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char KHBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	//	'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 // 股东代码或资金帐号
	char QSRQ[DATETIME_WIDTH];	 //起始日期
	char ZZRQ[DATETIME_WIDTH];	 //终止日期
	char CXTS[DATETIME_WIDTH];	 //查询天数  (起止日期与查询天数只能有一)
}tagZJLS_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char FSRQ[DATETIME_WIDTH];	 //委托日期
	char HTXH[HTXH_WIDTH];		 //合同序号
	char JYSJC[JYSJC_WIDTH];	 //交易所简称
	char GDDM[GDDM_WIDTH];		 //股东代码
	char GDXM[GDXM_WIDTH];		 //股东姓名
	char ZQDM[ZQDM_WIDTH];		 //证券代码   如为存取则为银行代码
	char ZQMC[ZQMC_WIDTH];		 //证券名称   如为存取则为银行名称
	char ZYDMSM[ZYDM_WIDTH];	 //买卖类别说明
	SmallMoney WTJG;			 //委托价格
	long WTSL;					 //委托数量
	SmallMoney CJJG;			 //成交价格
	long CJSL;					 //成交数量
	Money CJJE; 				 //成交金额
	SmallMoney SXF; 			 //手续费
	SmallMoney YHS; 			 //印花税
	SmallMoney GHF; 			 //过户费
	SmallMoney QSF; 			 //清算费
	SmallMoney JYGF;			 //交易规费
	SmallMoney WTDF;			 //委托单费
	SmallMoney CJDF;			 //成交单费
	SmallMoney CDDF;			 //撤单单费
	Money HZJE; 				 //划帐金额
	Money ZJBCYE;				 //资金本次余额 查累计无效
	long GFBCYE;				 //股份本次余额 查累计无效
}tagZJLS_Result;


///////////////////划拨资金//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char ZJZH[ZJZH_WIDTH];		 //资金帐号
	char HBDM;					 //货币代码
	char HBFX;					 //划拨方向 'O' 划出到银行 'I'划入到证券
	char ZKJE[HBJE_WIDTH];		 //划拨金额
	char YHDM[YHDM_WIDTH];		 //银行代码
	char YHMM[YHMM_WIDTH];		 //银行密码
	char ZJMM[JYMM_WIDTH];		 //资金密码
	int WaitTime;				 //等待时间
	char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagZJHB_Request;

typedef struct{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char BZXX[80];				 //成交情况说明
}tagZJHB_Result;

///////////////////银行余额查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char ZJZH[ZJZH_WIDTH];		 //资金帐号
	char HBDM;					 //货币代码
	char YHDM[YHDM_WIDTH];		 //银行代码
	char YHMM[YHMM_WIDTH];		 //银行密码
	char ZJMM[JYMM_WIDTH];		 //资金密码
	int WaitTime;				 //等待时间
	char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagYHYE_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char BZXX[80];				 //成交情况说明
}tagYHYE_Result;

///////////////////银行更密//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char ZJZH[ZJZH_WIDTH];		 //资金帐号
	char HBDM;					 //货币代码
	char YHDM[YHDM_WIDTH];		 //银行代码
	char YHMM[YHMM_WIDTH];		 //银行密码
	char XYHMM[YHMM_WIDTH]; 	 //新银行密码
	char ZJMM[JYMM_WIDTH];		 //资金密码
	int  WaitTime;				 //等待时间
	char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagYHGM_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char BZXX[80];				 //成交情况说明
}tagYHGM_Result;

///////////////////划拨查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char KHBSLX;
	char KHBS[KHBS_WIDTH];
}tagHBCX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char WTSJ[DATETIME_WIDTH];	 //委托时间
	char YHDM[YHDM_WIDTH];		 //银行代码
	char YHMC[YHMC_WIDTH];		 //银行名称
	char HTXH[HTXH_WIDTH];		 //合同序号
	char CQLBSM[QTSM_WIDTH];	 //存取类别说明
	Money ZKJE; 				 //转款金额
	char ZTSM[QTSM_WIDTH];		 //状态说明
	Money YHYE; 				 //银行余额(银行余额查询用)
	char FQFXSM[8]; 			 //发起方向说明
}tagHBCX_Result;

///////////////////划拨撤单//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char HBDM;
	char ZJZH[ZJZH_WIDTH];
	char HTXH[HTXH_WIDTH];
}tagHBCD_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	Money ZJBCKYS;				 //资金本次可用数
}tagHBCD_Result;

///////////////////批量委托信息//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM;
	char GDDM[GDDM_WIDTH];
	char ZQDM[ZQDM_WIDTH];
}tagPLWTXX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	long GFKYS;
	long GDDMS;
	Money ZJKYS;
}tagPLWTXX_Result;

///////////////////盈亏计算//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM;
	char GDDM[GDDM_WIDTH];
	char ZQDM[ZQDM_WIDTH];
	char CKCBJ[WTJG_WIDTH];
	char ZJCJ[WTJG_WIDTH];
	char YGSL[WTSL_WIDTH];
}tagYKJS_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	SmallMoney PCJG;
	Money DTYK;
}tagYKJS_Result;


///////////////////修改成本//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM;
	char GDDM[GDDM_WIDTH];
	char ZQDM[ZQDM_WIDTH];
	char CBJG[WTJG_WIDTH];
	char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagXGCB_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
}tagXGCB_Result;


///////////////////收费明细//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char JYSDM;
	char GDDM[GDDM_WIDTH];
	char QSRQ[DATETIME_WIDTH];
	char ZZRQ[DATETIME_WIDTH];
	char CXTS[DATETIME_WIDTH];
}tagSFMX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char FSRQ[DATETIME_WIDTH];
	char FSSJ[DATETIME_WIDTH];
	char ZJZH[ZJZH_WIDTH];
	Money ZJFSS;
	char HBMC[HBMC_WIDTH];
	char CXFLBSM[CXLB_WIDTH];
	char CZFSSM[QTSM_WIDTH];
}tagSFMX_Result;

///////////////////营业部信息//////////////////
//通买通卖时需要
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
}tagYYB_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char YYBDM[YYBDM_WIDTH];
	char YYBMC[YYBMC_WIDTH];
	char ZJZHQZ[ZJZHQZ_WIDTH];
	char FZDM[FZDM_WIDTH];
}tagYYB_Result;

///////////////////约定日委托增加//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		//头信息
	char JYSDM; 				// '0'-'9'交易所代码(参看柜台设置)
	char GDDM[GDDM_WIDTH];		//股东代码
	char ZQDM[ZQDM_WIDTH];		//ZQDM	证券代码
	char MMLB;					//MMLB	买卖类别
	char WTSL[WTSL_WIDTH];		//WTSL	委托数量
	char WTJG[WTJG_WIDTH];		//WTJG	委托价格
	char YDRRQ[DATETIME_WIDTH]; //YDRRQ 约定日日期
	char JYMM[JYMM_WIDTH];		//JYMM	交易密码
}tagYDRWTZJ_Request;

typedef struct{
	tagBLOCK_HEAD HEAD; 		  // 头信息
	char HTXH[HTXH_WIDTH];		  // 约定日委托号
	char ZJZH[ZJZH_WIDTH];		  // 资金帐号
	char HBDM;					  // 货币代码
	char GDDM[GDDM_WIDTH];		// 股东代码
}tagYDRWTZJ_Result;

///////////////////约定日委托修改//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		//头信息
	char JYSDM; 				//'0'-'9'交易所代码(参看柜台设置)
	char GDDM[GDDM_WIDTH];		//股东代码
	char ZQDM[ZQDM_WIDTH];		//ZQDM	证券代码
	char MMLB;					//MMLB	买卖类别
	char WTSL[WTSL_WIDTH];		//WTSL	委托数量
	char WTJG[WTJG_WIDTH];		//WTJG	委托价格
	char YDRRQ[DATETIME_WIDTH]; //YDRRQ 约定日日期
	char HTXH[HTXH_WIDTH];		  // 约定日委托号
	char JYMM[JYMM_WIDTH];		//JYMM	交易密码
}tagYDRWTXG_Request;

typedef struct{
	tagBLOCK_HEAD HEAD; 		  // 头信息
	char HTXH[HTXH_WIDTH];		  // 约定日委托号
	char ZJZH[ZJZH_WIDTH];		  // 资金帐号
	char HBDM;					  // 货币代码
	char GDDM[GDDM_WIDTH];		// 股东代码
}tagYDRWTXG_Result;

///////////////////约定日委托删除//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		//头信息
	char JYSDM; 				//'0'-'9'交易所代码(参看柜台设置)
	char GDDM[GDDM_WIDTH];		//股东代码
	char HTXH[HTXH_WIDTH];		//约定日委托号
	char JYMM[JYMM_WIDTH];		//JYMM	交易密码
}tagYDRWTSC_Request;

typedef struct{
	tagBLOCK_HEAD HEAD; 		  // 头信息
	char HTXH[HTXH_WIDTH];		  // 约定日委托号
	char ZJZH[ZJZH_WIDTH];		  // 资金帐号
	char HBDM;					  // 货币代码
	char GDDM[GDDM_WIDTH];		// 股东代码
}tagYDRWTSC_Result;

///////////////////约定日委托查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		// 头信息
	char KHBSLX;				// '0'-'9'交易所代码(参看柜台设置)，'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		// 股东代码，或资金帐号
	char HTXH[HTXH_WIDTH];		// 约定日委托号,' '查全部，其它按合同号查
}tagYDRWTCX_Request;

typedef struct{
	tagBLOCK_HEAD HEAD; 		  // 头信息
	char ZJZH[ZJZH_WIDTH];	// 资金帐号  
	char JYSDM; 		// '0'-'9'交易所代码(参看柜台设置)
	char GDDM[GDDM_WIDTH];	// 股东代码
	char ZQDM[ZQDM_WIDTH];	// ZQDM  证券代码
	char ZQMC[ZQMC_WIDTH];		  // ZQMC  证券名称
	char MMLB;			// MMLB  买卖类别
	long WTSL;			// WTSL  委托数量
	SmallMoney WTJG;		// WTJG  委托价格
	char WTRQ[DATETIME_WIDTH];	// WTRQ  委托提交日期 
	char WTSJ[DATETIME_WIDTH];	  // 委托时间
	char YDRRQ[DATETIME_WIDTH]; // YDRRQ 委托生效日期
	char HTXH[HTXH_WIDTH];		  // 约定日委托号
	char ZTSM[QTSM_WIDTH];	// 状态说明
}tagYDRWTCX_Result;

///////////////////预约开户设置//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		//头信息
	//	char ZJLB;					//证件类别
	char ZJBH[ZJBH_WIDTH];		//证件编号
	char XX[YYKH_XX_WIDTH]; 	//预约信息
	//	char RQ[DATETIME_WIDTH];	//预约日期
}tagYYKH_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		//头信息
	int XYM;					//响应码
}tagYYKH_Result;

///////////////////预约开户查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		//头信息
	//	char ZJLB;					//证件类别
	char ZJBH[ZJBH_WIDTH];		//证件编号
	//	char QSRQ[DATETIME_WIDTH];	//起始日期
	//	char ZZRQ[DATETIME_WIDTH];	//终止日期
}tagYYKHCX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		//头信息
	char XX[YYKH_XX_WIDTH]; 	//预约信息
}tagYYKHCX_Result;
///////////////////红股查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 // 头信息
	char GDMS;					 // '0' 单股东
	// '1'同资金帐号且同身份证关联
	// '2'同资金帐号关联
	char KHBSLX;				 // '0'-'9'交易所代码(参看柜台设置)
	// 'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 // 股东代码或资金帐号
	char ZQBSLX;				 // '0'-'9'交易所代码(参看柜台设置)
	char ZQBS[ZQDM_WIDTH];		 // 证券标识
	char QSRQ[DATETIME_WIDTH];	 // 起始日期
	char ZZRQ[DATETIME_WIDTH];	 // 终止日期
	char CXTS[DATETIME_WIDTH];	 //查询天数  (起止日期与查询天数只能有一)
}tagHGCX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		// 头信息
	char RQ[DATETIME_WIDTH];		// 日期 (YYYYMMDD)
	char JYSDM; 				// '0'-'9'交易所代码(参看柜台设置)
	char JYSJC[JYSJC_WIDTH];		// 交易所简称
	char ZQDM[ZQDM_WIDTH];		// 证券代码
	char ZQMC[ZQMC_WIDTH];		// 证券名称
	char ZJZH[ZJZH_WIDTH];		// 资金帐号
	char GDDM[GDDM_WIDTH];		// 股东代码
	char GDXM[GDXM_WIDTH];		// 股东姓名
	long SL;						// 红股数量
}tagHGCX_Result;


///////////////////派息(红利)查询//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char GDMS;					 // '0' 单股东
	// '1'同资金帐号且同身份证关联
	// '2'同资金帐号关联
	char KHBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	//	'Z' 资金帐号
	char KHBS[KHBS_WIDTH];		 // 股东代码或资金帐号
	char ZQBSLX;				 //'0'-'9'交易所代码(参看柜台设置)
	char ZQBS[ZQDM_WIDTH];		 //证券标识
	char QSRQ[DATETIME_WIDTH];	 //起始日期
	char ZZRQ[DATETIME_WIDTH];	 //终止日期
	char CXTS[DATETIME_WIDTH];	 //查询天数  (起止日期与查询天数只能有一)
}tagPXCX_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD; 		//头信息
	char RQ[DATETIME_WIDTH];		//发生日期 (YYYYMMDD)
	char JYSDM; 				//'0'-'9'交易所代码(参看柜台设置)
	char JYSJC[JYSJC_WIDTH];		//交易所简称
	char ZQDM[ZQDM_WIDTH];		//证券代码
	char ZQMC[ZQMC_WIDTH];		//证券名称
	char ZJZH[ZJZH_WIDTH];		//资金帐号
	char GDDM[GDDM_WIDTH];		//股东代码
	char GDXM[GDXM_WIDTH];		//股东姓名
	Money PXJE; 				//派息金额
}tagPXCX_Result;

///////////////////请求重发信息//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	int serio;					 //重定位记录 0取消发送
}tagAGAIN_Request;

//无返回
typedef struct
{
	tagBLOCK_HEAD HEAD; 		 //头信息
	char ErrMsg[100];
}tagErrMsg_Result;

typedef union
{
	tagBLOCK_HEAD head;
	tagJYSXX_Request jysxx;
	tagHBXX_Request hbxx;
	tagYHXX_Request yhxx;
	tagKHYHXX_Request khyhxx;
	tagZQXX_Request zqxx;
	tagPLCDCX_Request plcdcx;
	tagKHJY_Request khjy;
	tagKHCX_Request khcx;
	tagDMJY_Request dmjy;
	tagKMSL_Request kmsl;
	tagWTQR_Request wtqr;
	tagWTCD_Request wtcd;
	tagXGMM_Request xgmm;
	tagXXGMM_Request xxgmm;
	tagZJCX_Request zjcx;
	tagGFCX_Request gfcx;
	tagDRWTCX_Request wtcx;
	tagLSWTCX_Request lswtcx;
	tagDRCJCX_Request cjcx;
	tagXGPH_Request xgph;
	tagLSCJCX_Request lscjcx;
	tagZJLS_Request zjls;
	tagZJHB_Request zjhb;
	tagYHYE_Request yhye;
	tagYHGM_Request yhgm;
	tagHBCX_Request hbcx;
	tagHBCD_Request hbcd;
	tagYKJS_Request ykjs;
	tagXGCB_Request xgcb;
	tagPLWTXX_Request plwtxx;
	tagSFMX_Request sfmx;
	tagMMJY_Request mmjy;
	tagYYB_Request	yyb;
	tagYDRWTZJ_Request ydrwtzj;
	tagYDRWTXG_Request ydrwtxg;
	tagYDRWTSC_Request ydrwtsc;
	tagYDRWTCX_Request ydrwtcx;
	tagHGCX_Request hgcx;
	tagPXCX_Request pxcx;
	tagYYKH_Request yykh;
	tagYYKHCX_Request	yykhcx;
	tagAGAIN_Request again;
}tagREQUEST;

typedef union
{
	tagBLOCK_HEAD head; 		 //头信息
	tagJYSXX_Result jysxx;
	tagHBXX_Result hbxx;
	tagYHXX_Result yhxx;
	tagZQXX_Result zqxx;
	tagPLCDCX_Result plcdcx;
	tagKHJY_Result khjy;
	tagKHCX_Result khcx;
	tagDMJY_Result dmjy;
	tagKMSL_Result kmsl;
	tagWTQR_Result wtqr;
	tagWTCD_Result wtcd;
	tagXGMM_Result xgmm;
	tagZJCX_Result zjcx;
	tagGFCX_Result gfcx;
	tagDRWTCX_Result wtcx;
	tagLSWTCX_Result lswtcx;
	tagDRCJCX_Result cjcx;
	tagXGPH_Result xgph;
	tagLSCJCX_Result lscjcx;
	tagZJLS_Result zjls;
	tagZJHB_Result zjhb;
	tagYHYE_Result yhye;
	tagYHGM_Result yhgm;
	tagHBCX_Result hbcx;
	tagHBCD_Result hbcd;
	tagYKJS_Result ykjs;
	tagXGCB_Result xgcb;
	tagPLWTXX_Result plwtxx;
	tagSFMX_Result sfmx;
	tagMMJY_Result mmjy;
	tagYYB_Result  yyb;
	tagYDRWTZJ_Result ydrwtzj;
	tagYDRWTXG_Result ydrwtxg;
	tagYDRWTSC_Result ydrwtsc;
	tagYDRWTCX_Result ydrwtcx;
	tagHGCX_Result	hgcx;
	tagPXCX_Result	pxcx;
	tagYYKH_Result	yykh;
	tagYYKHCX_Result	yykhcx;
	tagErrMsg_Result ErrMsg;
}tagRESULT;

typedef struct
{
	char Node[9];				 //网段号
	char Address[13];			 //网卡号
	unsigned int  Socket;		 //Socket
}tagNETWORKADD;

BOOL WINAPI KDAPI_InitSystem(long _TimeOut);
/*------------------------------
说明
初始化DLL
输入
_TimeOut	 响应时间
输出
TRUE 成功
其他 失败
-------------------------------*/
int WINAPI KDAPI_Connect(tagNETWORKADD serverAddress[3],char *GYDM,char *GYMM);
/*------------------------------
说明
连接中间件
输入
serverAddress	 中间件地址序列
GYDM			 柜员代码
GYMM			 柜员密码
OEM 			 OEM代码
输出
0  成功
-1 没有调用InitSystem
-2 中间件连接错误
-3 OEM未授权
其他返回：OEM检验失败时返回错误码
-------------------------------*/
int WINAPI KDAPI_Request(tagREQUEST &request);
/*------------------------------
说明
向中间件发请求
输入
request   请求包
输出
-1 没有调用InitSystem
-2 中间件连接错误 (未调用Connect)
-3 OEM未授权
-4 请求失败（应当取回一个包,该包为错误信息包）
-5 中间件连接错误(所有连接已断)
-6 发送数据错误
其他 成功，该笔请求返回应答记录数
-------------------------------*/

int WINAPI KDAPI_Request_fzdm(tagREQUEST &request,char *yfzdm,char *mdfzdm);
/*------------------------------
说明
向中间件发请求（用于通存通兑）
输入
request   请求包
yfzdm	  源分支代码（4位）'____'为本地
mdfzdm	  目的分支代码（4位）'____'为本地
输出
-1 没有调用InitSystem
-2 中间件连接错误 (未调用Connect)
-3 OEM未授权
-4 请求失败（应当取回一个包,该包为错误信息包）
-5 中间件连接错误(所有连接已断)
-6 发送数据错误
其他 成功，该笔请求返回应答记录数
-------------------------------*/

int WINAPI KDAPI_Answer(tagRESULT &result);
/*------------------------------
说明
取请求结果
输入
result	应答包
输出
-1 没有调用InitSystem
-2 中间件连接错误
-3 OEM未授权
-5 中间件连接错误(所有连接已断)
-6 发送数据错误
0	 结果已经取完
其他 成功，该笔请求返回字节数
-------------------------------*/

void WINAPI KDAPI_StrToMoney(char *s,Money *x1);
void WINAPI KDAPI_StrToSmallMoney(char *s,SmallMoney *x1);
char * WINAPI KDAPI_MoneyToStr( Money m);
char * WINAPI KDAPI_SmallMoneyToStr( SmallMoney m);

#endif
