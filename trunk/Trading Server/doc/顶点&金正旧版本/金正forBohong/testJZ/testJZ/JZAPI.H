/*---------------------------------------
注意：
	0.此版本是新版(Ver 3.0.0.0),首次发行日期：2003.06.01
    1.结构采用字节对齐
    2.凡是字符应当以' '表示为空查询全部
    3.凡是字符串应当以" "为空表示查询全部
    4.支持多线程,线程数小于150
	5.支持IPX、TCPIP协议
	6.最近修改日期:2004.12.17
	7.版本：3.0.0.20
-----------------------------------------*/

#ifndef __XS_JZApi_Include__
#define __XS_JZApi_Include__

#include <windows.h>

//金证3.2柜台接口使用
//#ifndef _KD3X
//#define _KD3X
//#endif

//银河证券B股转发到顶点柜台,合同序号为8位
//#ifndef _DDBGZF
//#define _DDBGZF      
//#endif

//光大证券三板市场
//#ifndef _GDSB
//#define _GDSB
//#endif

//汉唐证券总部合作配售和集中国债回购使用
//#ifndef _HTPSGZ
//#define _HTPSGZ
//#endif

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef DWORD          SmallMoney;

#define JYSJC_WIDTH            7
#define JYSBS_WIDTH            5
#define HBBS_WIDTH             5
#define HBMC_WIDTH             9
#define GDDM_WIDTH             11
#define ZJZH_WIDTH             13
#define GDXM_WIDTH             13
#define KHBS_WIDTH             13
#define CKBH_WIDTH             31
#define ZQDM_WIDTH             7
#define ZQMC_WIDTH             9
#define YHDM_WIDTH             3
#define YHMC_WIDTH             9
#ifdef _KD3X
#define HTXH_WIDTH             9
#else
#ifdef _DDBGZF
#define HTXH_WIDTH             9
#else
#define HTXH_WIDTH             7
#endif
#endif
#define DATETIME_WIDTH         9
#define WTJG_WIDTH             9
#define WTSL_WIDTH             9
#define ZYDM_WIDTH             13
#define JYMM_WIDTH             11
#define YHMM_WIDTH             21
#define HBJE_WIDTH             17
#define QTSM_WIDTH             9
#define SGPH_WIDTH             21
#define CXLB_WIDTH             17
#define YYBDM_WIDTH            5
#define YYBMC_WIDTH            11
#define ZJZHQZ_WIDTH           11
#define FZDM_WIDTH             5
#define FZMC_WIDTH             17
#define YHLSH_WIDTH            21
#define YHZH_WIDTH             31
#define CZZH_WIDTH             31
#define BZXX_WIDTH             41
#define YWLB_WIDTH             5
#define ZJXM_WIDTH             9
#define SFZH_WIDTH             21
#define LXDH_WIDTH             21
#define LXDZ_WIDTH             81
#define EMAIL_WIDTH            41
#define XMQC_WIDTH             41
#define YZBM_WIDTH             9   
#define CJHM_WIDTH             17
#define QQYXX_WIDTH            21
#define CQLB_WIDTH             31
#define CQLBSM_WIDTH           13
#define FSBZSM_WIDTH           9
#define CLJGMC_WIDTH           11
#define GYDM_WIDTH             5
#define DEVICE_WIDTH           21
#define CZFSSM_WIDTH           9
#define ZJS_WIDTH              13              //金额--在入参中使用

#define MAX_LONG 0x80000000L

//系统参数类
#define funcJYSXX              0               //取交易所信息
#define funcHBXX               1               //取货币信息
#define funcYHXX               2               //取银行信息
#define funcZQXX               3               //取证券信息
#define funcYYB                30              //取营业部信息
//客户管理类
#define funcKHJY               5               //客户密码校验
#define funcKHCX               6               //查询客户信息（股东）
#define funcXGMM               11              //修改密码
#define funcXGZJMM             66              //修改资金密码
#define funcMMJY               29              //密码校验（远程用）
//三板交易类
#define funcSBZJKH             89              //三板资金开户------KB32柜台使用(光大证券)
#define funcSBDLRSZ            90              //三板代理人设置----KB32柜台使用(光大证券)
#define funcSBGDKH             91              //三板股东开户------KB32柜台使用(光大证券)
#define funcSBZJXH             92              //三板资金销户------KB32柜台使用(光大证券)
#define funcSBGDXH             93              //三板股东销户------KB32柜台使用(光大证券)
#define funcSBZJXG             94              //三板资金基本资料修改--KB32柜台使用(光大证券)
#define funcSBGDXG             95              //三板股东基本资料修改--KB32柜台使用(光大证券)
#define funcSBGDYYBSZ          96              //三板股东所属营业部设置--KB32柜台使用(光大证券)
#define funcSBGDYYBQX          97              //三板股东所属营业部取消--KB32柜台使用(光大证券)
//交易查询类
#define funcPLCDCX             4               //取可批量撤单信息
#define funcZJCX               12              //资金查询
#define funcGFCX               13              //股份查询
#define funcGZHGBZQCX          67              //国债回购标准券查询
#define funcMCGFCX             64              //卖出股份查询--KB32柜台
#define funcPLWTXX             25              //取批量委托信息
#define funcWTCX               14              //委托查询
#define funcCJCX               16              //成交查询
#define funcLSWTCX             15              //历史委托查询
#define funcLSCJCX             18              //历史成交查询
#define funcXGPH               17              //查询新股配号
#define funcZJLS               19              //查询资金流水（对帐单）
#define funcSFMX               28              //查询收费明细
#define funcDMJY               7               //证券代码校验
#define funcZQDMCX             56              //查询证券代码--江南证券金仕达使用
#define funcSSCJCX             57              //实时成交查询--江南证券金仕达使用
#define funcSSCDCX             58              //实时撤单查询--江南证券金仕达使用
#define funcZJLSCX             61              //资金流水查询--天同证券
#define funcZJYECX             62              //资金余额查询--天同证券
#define funcKHZLCX             63              //资金资料查询--天同证券
#define funcJZGZHGKHSZ         85              //集中国债回购客户设置--KB32柜台使用(汉唐证券)
#define funcJZGZHGZJHB         86              //集中国债回购资金划拨--KB32柜台使用(汉唐证券)
#define funcJZGZHGSYCX         87              //集中国债回购收益查询--KB32柜台使用(汉唐证券)
#define funcKQZJCX             88              //资金可取资料查询(资金库)--湘财证券总部使用
#define funcWDQHGCX           102              //未到期回购查询--KB32柜台使用(华林证券)
//委托类
#define funcKMSL               8               //取可买数量
#define funcWTQR               9               //委托确认
#define funcWTCD               10              //委托撤单
#define funcPLWTQR             59              //委托确认
#define funcZQZGHS             65              //债券的转股和回售
//银证转账类
#define funcZJHB               20              //银证转帐资金划拨
#define funcHBCD               24              //银证转帐资金划拨撤单
#define funcHBCXLSH            47              //银证转帐资金划拨查询--流水号
#define funcYHYE               21              //查询银行余额
#define funcYHGM               22              //修改银行密码
#define funcHBCX               23              //银证转帐资金划拨查询
#define funcQZZJYE             76              //期证转账期货资金余额----恒远证券使用
#define funcQZQSXX             77              //期证转账期货基本信息----恒远证券使用
#define funcQYZJHB             78              //期银转账期资金划拨------恒远证券使用
#define funcZZYHCX             98              //银证转帐银行查询--联合证券使用
#define funcZZMXCX             99              //银证转帐明细查询--联合证券使用
//存折炒股类
#define funcCZCGSFYZ           35              //存折炒股身份验证
#define funcCZCGCXGDXX         34              //存折炒股查询股东信息
#define funcCZCGWTCD           33              //存折炒股委托撤单                
#define funcCZCGCXJKK          32              //存折炒股根据流水号取czcg_jkk信息,即查询此记录的处理情况
#define funcCZCGWTQR           31              //存折炒股委托
#define funcCZCGYHZJCX         36              //存折炒股银行资金查询                   
#define funcCZCGKTYHCX         37              //存折炒股股东开通银行查询
#define funcCZCGKMSL           51              //存折炒股取可(卖)买数量
#define funcCZCGHZHBZJ         100             //存折抄股设置合作配售标志
#define funcCZCGYHCGD          101             //存折抄股根据银行帐户查股东信息(东莞证券)
#define funcCZCGSZHZPS         68              //存折炒股设置合作配售------KB32柜台使用(广东证券)
#define funcCZCGQXHZPS         69              //存折炒股取消合作配售------KB32柜台使用(广东证券)
#define funcCZCGHZSGHBZJ       70              //存折炒股合作申购划拨资金--KB32柜台使用(广东证券)
#define funcCZCGHZHGHBZJ       71              //存折炒股合作回购划拨资金--KB32柜台使用(广东证券)
#define funcCZCGSZHZHGSG       72              //存折炒股设置合作申购回购--KB32柜台使用(广东证券)
#define funcHZHGSGCX           81              //存折炒股合作回购申购查询--KB32柜台使用(广东证券)
#define funcCZCGJNFDJZJ        73              //存折炒股交年费冻结资金
#define funcCZCGJNFSZHFBZ      74              //存折炒股交年费设置合法标志
#define funcCZCGHZPSKH         82              //存折炒股合作配售开户--KB32柜台使用(汉唐证券)
#define funcCZCGHZPSXH         83              //存折炒股合作配售销户--KB32柜台使用(汉唐证券)
#define funcCZCGHZPSCX         84              //存折炒股合作配售查询--KB32柜台使用(汉唐证券)
//其它业务类
#define funcXGCB               27              //修改成本
#define funcYKJS               26              //浮动盈亏计算
#define funcZLCX               44              //资料查询    联合证券年费制客户判断可用
#define funcXXZLCX             79              //详细资料查询 
#define funcZLXG               80              //资料修改
#define funcZJZL               48              //资金资料
#define funcZHYZ               45              //单帐号开通的银证转帐信息
#define funcSZZDPS             46              //设置股东的自动配售标志
#define funcYCDJZJ             49              //异常冻结资金
#define funcYCJDZJ             50              //异常解冻资料
#define funcZJNBZZ             60              //资金内部转帐------泰阳证券
//预委托类
#define funcYWTQR              52              //预委托业务
#define funcYWTCD              53              //删除预委托
#define funcYWTFS              54              //发送预委托
#define funcYWTCX              55              //预委托查询
//ETF业务
#define funcETFXJRG            103             //ETF网下现金认购
#define funcETFGPRG            104             //ETF网下股票认购
#define funcETFRGCD            105             //ETF网下认购撤单
#define funcETFRGCX            106             //ETF网下认购查询
#define funcETFKMSL            107             //ETF取可申购赎回数量
#define funcETFSGSH            108             //ETF申购赎回委托
#define funcETFDMJY            109             //ETF代码校验
#define funcETFSGSHPZ          110             //ETF申购赎回清单文件的配置信息
#define funcETFSGSHQD          111             //ETF申购赎回股票蓝

#define funcAGAIN              200

typedef struct _Money
{
  DWORD lo_value;                              //低位
  DWORD hi_value;                              //高位
}Money;

typedef union _U_dw
{
  DWORD dw;
  struct {WORD lo, hi;} w;
}U_dw;

typedef struct				   // 本结构中功能号(function)与操作方式(czfs)是必须的，其它可选			
{
  unsigned short length;       //长度  (整个数据包长度)
  unsigned short crc ;         //CRC校验码,从serio 开始计算,暂时保留
  unsigned short serio;        //序列号(按请求划分,从1开始)
  unsigned char function;      //功能号
  unsigned char czfs;          //操作方式(与柜台中的设置相同)
  unsigned long status;        //状态 0正确 其他错误(应答有效)
}tagBLOCK_HEAD;

typedef struct
{
  char Node[9];                //IPX:网段号; TCP:填写字符串"TCP"
  char Address[13];            //IPX:网卡地址; TCP:IP地址
  unsigned int  Socket;        //Socket
}tagNETWORKADD;

/*****************************
		基本交易业务
*****************************/
///////////////////交易所信息//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagJYSXX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //交易所代码
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char JYSBS[JYSBS_WIDTH];     //交易所标识
  char HBDM;                   //货币代码
  short GDDMCD;                //股东代码长度
  short NBGDDMCD;              //内部股东代码长度
  short ZQDMCD;                //证券代码长度
  short NBZQDMCD;              //内部证券代码长度
  short JYMMCD;                //交易密码长度
}tagJYSXX_Result;

///////////////////货币信息//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagHBXX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char HBDM;                   //货币代码
  char HBBS[HBBS_WIDTH];       //货币标识
  char HBMC[HBMC_WIDTH];       //货币名称
}tagHBXX_Result;

///////////////////银行信息//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagYHXX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char HBDM;                   //货币代码
  char YHDM[YHDM_WIDTH];       //银行代码
  char YHMC[YHMC_WIDTH];       //银行名称
  char FQFX;                   //'A' 双方发起 'Y' 银行发起 'Q' 券商发起
  short YHMMCD;                //银行密码长度
  short ZRMM;                  //转入需要密码  
							   //0不需要密码 1 需要取款密码 2 需要银行密码 3 需要取款/银行密码
  short ZCMM;                  //转出需要密码 同上
  short YHGM;                  //可修改银行密码 '0' 不需要 '1' 需要
  short YHYE;                  //查银行余额     '0' 不需要 '1' 需要
  short ZKJEXSCD;              //转款金额小数点位数
  short TIMEOUT;               //等待延时
}tagYHXX_Result;

///////////////////营业部信息//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
}tagYYB_Request;

typedef struct
{
	tagBLOCK_HEAD HEAD;                //头信息
	char YYBDM[YYBDM_WIDTH];           //营业部代码
	char YYBMC[YYBMC_WIDTH];           //营业部名称
	char ZJZHQZ[ZJZHQZ_WIDTH];         //资金帐号前缀(参看柜台设置)
	char FZDM[FZDM_WIDTH];             //银行代码
}tagYYB_Result;

///////////////////取证券信息/////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagZQXX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //交易所代码
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char ZQMC[ZQMC_WIDTH];       //证券名称
  char NBZQDM[ZQDM_WIDTH];     //内部证券代码
  char PYBM[5];                //拼音编码
}tagZQXX_Result;

///////////////////查询证券代码/////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //交易所代码(参看柜台设置),为空格查询全部
  char ZQDM[ZQDM_WIDTH];       //证券代码,为空格查询全部
  short ZQLB;                  //证券类别 0股票 1国债 2企业债券 3回购 4基金
                               //         5投资基金 6权证 9转换债券 10实物国债
                               //         11实物企债 12特殊证券
	                             //为-1查询全部
  char JYLX[5];                //交易类型,为空格查询全部
							   //'PT'正常交易 'SG'申购 'PS' 配售 'PH'配号 'PP' 配售配号 'JK' 缴款
}tagZQDMCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //交易所代码
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char ZQMC[ZQMC_WIDTH];       //证券名称
  char NBZQDM[ZQDM_WIDTH];     //内部证券代码
  char PYBM[5];                //拼音编码
  long SGSX;                   //申购上限
  SmallMoney SGJG;             //申购价格
  short ZQLB;                  //证券类别
}tagZQDMCX_Result;

///////////////////客户校验//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char GDMS;                   // '0'单股东(只校验单个股东代码的交易密码)
                               // '1'同资金帐号且同身份证关联(同
	                             // 资金帐号且同身份证号下的股东全部校验，暂时未用)
                               // '2'同资金帐号关联(同资金帐号下的股东全部校验)

  char KHBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
                               // 'Z' 资金帐号
                               // 'C' 磁卡号
  char KHBS[CKBH_WIDTH];       //KHBS  股东代码或资金帐号或磁卡号
  char JYMM[JYMM_WIDTH];       //JYMM  交易密码
}tagKHJY_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char JYSDM;                  //交易所代码
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码
  char GDXM[GDXM_WIDTH];       //股东姓名
}tagKHJY_Result;

///////////////////密码校验//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
                               // 'Z' 资金帐号
                               // 'C' 磁卡号
  char KHBS[CKBH_WIDTH];       //KHBS  股东代码或资金帐号或磁卡号
  char JYMM[JYMM_WIDTH];       //JYMM  交易密码
}tagMMJY_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagMMJY_Result;

///////////////////代码校验//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          // 头信息
  char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置)
  char GDDM[GDDM_WIDTH];       // GDDM  股东代码
  char ZQDM[ZQDM_WIDTH];       // ZQDM  证券代码
}tagDMJY_Request;

typedef struct{
  tagBLOCK_HEAD HEAD;          // 头信息
  char JYSDM;                  //'0'-'9'交易所代码(参看柜台设置)
  char JYSJC[JYSJC_WIDTH];     //交易所名称(参看柜台设置)
  short JW;                    //价位(以厘为基数 1000为1元)
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char ZQMC[ZQMC_WIDTH];       //证券名称
  short ZQLB;                  //证券类别 0股票 1国债 2企业债券 3回购 4基金
                               //         5投资基金 6权证 9转换债券 10实物国债
                               //         11实物企债 12特殊证券
  char JYLX[5];                //交易类型 'PT'正常交易 'SG'申购 'PS' 配售 'PH'配号 'PP' 配售配号 'JK' 缴款
  Money KYZJ;                  //可用资金
  long KMGS;                   //可卖股票
  char WTGSBZ;                 //委托股手标志 'G' 股 'Z' 张 'S' 手
  char HQGSBZ;                 //行情股手标志
  SmallMoney ZJZS;             //最近指数
  SmallMoney ZRSP;             //昨日收盘
  SmallMoney JRKP;             //今日开盘
  SmallMoney ZJCJ;             //最新价
  SmallMoney ZGCJ;             //最高价
  SmallMoney ZDCJ;             //最低价
  Money CJJE;                  //成交金额
  long CJSL;                   //成交数量
  SmallMoney MRJG1;            //申买价1
  long MRSL1;                  //申买量1
  SmallMoney MRJG2;            //申买价2
  long MRSL2;                  //申买量2
  SmallMoney MRJG3;            //申买价3
  long MRSL3;                  //申买量3
  SmallMoney MCJG1;            //申卖价1
  long MCSL1;                  //申卖量1
  SmallMoney MCJG2;            //申卖价2
  long MCSL2;                  //申卖量2
  SmallMoney MCJG3;            //申卖价3
  long MCSL3;                  //申卖量3
  SmallMoney ZTJG;             //涨停价格
  SmallMoney DTJG;             //跌停价格
  char JGBZ;                   //价格标志  '0'-浮动价 '1'--定价
  char YJLX[30];               //国债净价交易中的国债利息额
  char TPBZ;                   //停牌标志  'T'-停牌, 'F'-正常
#ifndef _GDSB
  SmallMoney MRJG4;            //申买价4
  long MRSL4;                  //申买量4
  SmallMoney MRJG5;            //申买价5
  long MRSL5;                  //申买量5
  SmallMoney MCJG4;            //申卖价4
  long MCSL4;                  //申卖量4
  SmallMoney MCJG5;            //申卖价5
  long MCSL5;                  //申卖量5
#endif
}tagDMJY_Result;

///////////////////可买数量//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置)
  char GDDM[GDDM_WIDTH];       //GDDM  股东代码
  char ZQDM[ZQDM_WIDTH];       //ZQDM  证券代码
  char WTJG[WTJG_WIDTH];       //WTJG  委托价格
}tagKMSL_Request;

typedef struct{
  tagBLOCK_HEAD HEAD;          //头信息
  long KMSL;                   //可买数量
}tagKMSL_Result;

///////////////////委托确认[包括债券的回售和转股调用]//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置)
  char GDDM[GDDM_WIDTH];       //GDDM  股东代码
  char MMLB;                   //买卖类别
  char ZQDM[ZQDM_WIDTH];       //ZQDM  证券代码
  char WTJG[WTJG_WIDTH];       //WTJG  委托价格
  char WTSL[WTSL_WIDTH];       //WTSL  委托数量
  char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagWTQR_Request;

typedef struct{
  tagBLOCK_HEAD HEAD;          //头信息
  char HTXH[HTXH_WIDTH];       //合同序号
  Money KYZJ;                  //资金本次可用数
  long KYGF;                   //股份本次可用数
}tagWTQR_Result;

///////////////////委托撤单[包括债券的回售和转股调用]//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char GDMS;                   // '0'单股东
                               // '1'同资金帐号且同身份证关联
                               // '2'同资金帐号关联

  char JYSDM;                  //'0'-'9'交易所代码(参看柜台设置)                        
  char GDDM[GDDM_WIDTH];       // 股东代码
  char HTXH[HTXH_WIDTH];       // 合同序号
  char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagWTCD_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagWTCD_Result;

///////////////////债券的转股和回售//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //'0'-'9'交易所代码(参看柜台设置)
  char MMLB;                   //'G'--转股, 'H'--回售
  char GDDM[GDDM_WIDTH];       // 股东代码
  char HTXH[HTXH_WIDTH];       // 合同序号, 为‘ ’时自动生成
  char ZQDM[ZQDM_WIDTH];       // 证券代码
  char WTSL[WTSL_WIDTH];       // 委托数量
  char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagZQZGHS_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char HTXH[HTXH_WIDTH];       //合同序号
  char ZJZH[ZJZH_WIDTH];       //资金账号
  Money WTJE;                  //委托金额
  Money WTDJJE;                //委托冻结金额
  Money KYZJ;                  //资金本次可用数
  long GFFSS;                  //股份发生数
  long KYGF;                   //股份本次可用数
}tagZQZGHS_Result;

///////////////////修改密码//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                  //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char JYMM[JYMM_WIDTH];       // 原密码
  char XJYMM[JYMM_WIDTH];      //新密码
}tagXGMM_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagXGMM_Result;

///////////////////修改资金密码//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                  //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char ZJMM[JYMM_WIDTH];       // 原资金密码
  char XZJMM[JYMM_WIDTH];      //新资金密码
}tagXGZJMM_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagXGZJMM_Result;


///////////////////盈亏计算//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
                               //  'C' 磁卡号
  char KHBS[CKBH_WIDTH];       //股东代码或资金帐号或磁卡号
  char ZQBSLX;                 //证券标识类型
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char CKCBJ[WTJG_WIDTH];      //参考成本价
  char ZJCJ[WTJG_WIDTH];       //最近成交价
  char YGSL[WTSL_WIDTH];       //拥股数量
}tagYKJS_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  SmallMoney PCJG;             //平仓价格
  Money DTYK;                  //动态盈亏(系统根据买入均价与平仓价格计算出来的结果)
}tagYKJS_Result;


///////////////////修改成本//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;            //头信息
  char JYSDM;                    // 交易所代码
  char GDDM[GDDM_WIDTH];         // 股东代码
  char ZQDM[ZQDM_WIDTH];         //证券代码
  char CBJG[WTJG_WIDTH];         //成本价格
  char ReqSrcInfo[QQYXX_WIDTH];  // 请求源信息，如：网卡地址
}tagXGCB_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagXGCB_Result;

///////////////////收费明细//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 //0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
                               //  'C' 磁卡号
  char KHBS[CKBH_WIDTH];       //客户标识
  char QSRQ[DATETIME_WIDTH];   //起始日期(格式为:yyyymmdd)
  char ZZRQ[DATETIME_WIDTH];   //终止日期(格式为:yyyymmdd)
  char CXTS[DATETIME_WIDTH];   //查询天数
}tagSFMX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char FSRQ[DATETIME_WIDTH];   //发生日期(格式为:yyyymmdd)
  char FSSJ[DATETIME_WIDTH];   //发生时间
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  Money ZJFSS;                 //资金发生数
  char HBMC[HBMC_WIDTH];       //货币名称(如人民币、港币、美圆)
  char CXFLBSM[CXLB_WIDTH];    //查询费类别说明
  char CZFSSM[QTSM_WIDTH];     //操作方式说明
}tagSFMX_Result;

//////////////设置股东的自动配售标志///////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;           //头信息
	char KHBSLX;                  // '0'-'9'交易所代码(参看柜台设置)
                                  // 'Z' 资金帐号
	char KHBS[KHBS_WIDTH];        //股东代码或资金帐号
	int  PSBZ;                    //配售标志 0:为设置自动配售 1:取消自动配售
															  //如果送的是资金帐号,则更改该资金帐号下所有股东的自动配售标志
																//如果送的是股东代码,则只更改该股东的自动配售标志
	char BZXX[BZXX_WIDTH];        //备注信息
}tagSZZDPS_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagSZZDPS_Result;

//////////////存折抄股设置合作配售///////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;           //头信息
  char   JYSDM;                 // '0'-'9'交易所代码(参看柜台设置)
  char   GDDM[GDDM_WIDTH];       //股东代码
  char   FZDM[FZDM_WIDTH];       //银行代码 
  char   YHZH[YHZH_WIDTH];       //银行帐号, (可以填'')
  char   CZZH[CZZH_WIDTH];       //存折帐号, (可以填'')
  char   CZMM[YHMM_WIDTH];       //存折密码, (可以填'')
  char   DJJE[ZJS_WIDTH];        //冻结金额
  char   ZJZH[ZJZH_WIDTH];       //资金账号
  char   HBDM;                   //货币代码
}tagCZCG_SZHZPS_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
	char    CLJG;                //处理结果  '0'-成功, '1'-失败
	char    QSLSH[HTXH_WIDTH];   //券商流水号
	char    YHLSH[YHLSH_WIDTH];  //银行流水号  cljg为'0'保存银行流水号
	char    YYXXDM[11];          //银行错误代码 当p_cljg!='0'时, 填银行错误代码
	char    YHCJSJ[9];           //银行成交时间
	char    BZXX[BZXX_WIDTH];    //错误信息  cjlg='1'时保存具体的错误信息
	Money   ZJFSS;               //划入金额
}tagCZCG_SZHZPS_Result;

//////////////存折抄股取消合作配售///////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;            //头信息
  char   FZDM[FZDM_WIDTH];       //银行代码 
  char   YHZH[YHZH_WIDTH];       //银行帐号, (可以填'')
  char   CZZH[CZZH_WIDTH];       //存折帐号, (可以填'')
  char   KHBSLX;                 // '0'-'9'交易所代码,'Z' 资金帐号 (参看柜台设置)
  char   KHBS[KHBS_WIDTH];       //股东代码或资金帐号
  int    XHZPSBZ;                //取消配售标志
  char   BZXX[BZXX_WIDTH];       //备注信息
}tagCZCG_QXHZPS_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagCZCG_QXHZPS_Result;

//////////////设置存折抄股合作申购划拨金额///////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;           //头信息
  char   JYSDM;                 // '0'-'9'交易所代码(参看柜台设置)
  char   GDDM[GDDM_WIDTH];       //股东代码
  char   FZDM[FZDM_WIDTH];       //银行代码 
  char   YHZH[YHZH_WIDTH];       //银行帐号, (可以填'')
  char   CZZH[CZZH_WIDTH];       //存折帐号, (可以填'')
  char   CZMM[YHMM_WIDTH];       //存折密码, (可以填'')
  char   DJJE[ZJS_WIDTH];        //冻结金额
  char   ZJZH[ZJZH_WIDTH];       //资金账号
  char   HBDM;                   //货币代码
	//char   KHLB;                   //客户类别
	//char   ZQDM[ZQDM_WIDTH];       //证券代码
	//int    MMLB;                   //买卖类别  1--设置，0--取消
	//char   WTSL[WTSL_WIDTH];       //委托数量
	//char   WTJG[WTJG_WIDTH];       //委托价格
	//char   ZYDM[ZYDM_WIDTH];       //摘要代码
}tagCZCG_HZSGHBZJ_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char    CLJG;                //处理结果  '0'-成功, '1'-失败
  char    QSLSH[HTXH_WIDTH];   //券商流水号
  char    YHLSH[YHLSH_WIDTH];  //银行流水号  cljg为'0'保存银行流水号
  char    YYXXDM[11];          //银行错误代码 当p_cljg!='0'时, 填银行错误代码
  char    YHCJSJ[9];           //银行成交时间
  char    BZXX[BZXX_WIDTH];    //错误信息  cjlg='1'时保存具体的错误信息
  Money   ZJFSS;               //划入金额
}tagCZCG_HZSGHBZJ_Result;

//////////////设置存折抄股合作回购划拨金额///////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;           //头信息
  char   JYSDM;                 // '0'-'9'交易所代码(参看柜台设置)
  char   GDDM[GDDM_WIDTH];       //股东代码
  char   FZDM[FZDM_WIDTH];       //银行代码 
  char   YHZH[YHZH_WIDTH];       //银行帐号, (可以填'')
  char   CZZH[CZZH_WIDTH];       //存折帐号, (可以填'')
  char   CZMM[YHMM_WIDTH];       //存折密码, (可以填'')
  char   DJJE[ZJS_WIDTH];        //冻结金额
  char   ZJZH[ZJZH_WIDTH];       //资金账号
  char   HBDM;                   //货币代码
	//char   KHLB;                   //客户类别
	//char   ZQDM[ZQDM_WIDTH];       //证券代码
	//int    MMLB;                   //买卖类别  1--设置，0--取消
	//char   WTSL[WTSL_WIDTH];       //委托数量
	//char   WTJG[WTJG_WIDTH];       //委托价格
	//char   ZYDM[ZYDM_WIDTH];       //摘要代码
}tagCZCG_HZHGHBZJ_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char    CLJG;                //处理结果  '0'-成功, '1'-失败
  char    QSLSH[HTXH_WIDTH];   //券商流水号
  char    YHLSH[YHLSH_WIDTH];  //银行流水号  cljg为'0'保存银行流水号
  char    YYXXDM[11];          //银行错误代码 当p_cljg!='0'时, 填银行错误代码
  char    YHCJSJ[9];           //银行成交时间
  char    BZXX[BZXX_WIDTH];    //错误信息  cjlg='1'时保存具体的错误信息
  Money   ZJFSS;               //划入金额
}tagCZCG_HZHGHBZJ_Result;

//////////////设置存折抄股设置合作回购、申购///////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;           //头信息
	//第一组
	char    DKHDM[13];            //大客户代码
	//第二组
	char    ZJZH[ZJZH_WIDTH];     //资金账号
	char    HBDM;                 //货币代码
	//第三组
	char    JYSDM;                //交易所代码
	char    GDDM[GDDM_WIDTH];     //股东代码
	//以上客户信息由大到小,逐组有效,如：大客户代码有效，则另两组无效,送''值即可
	char    XXLX[5];              //信息类型  HZSG--合作申购, HZHG合作回购
	char    HKJE[ZJS_WIDTH];      //划款金额
	int     XXBZ;                 //信息备注  1-设置, 0-取消
	char    BZXX[BZXX_WIDTH];     //备注信息
}tagCZCG_SZHZHGSG_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagCZCG_SZHZHGSG_Result;

//////////////////存折抄股合作回购申购查询////////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char ZJZH[ZJZH_WIDTH];       //资金账号
	char HBDM;                   //货币代码
	char QSRQ[DATETIME_WIDTH];   //起始日期(格式为:yyyymmdd)
    char JSRQ[DATETIME_WIDTH];   //结束日期(格式为:yyyymmdd)
	char HZLX;                   //合作类型：'0',合作回购划款 '1' 合作申购划款 '2' 合作配售划款
}tagHZHGSGCX_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
	char QSRQ[DATETIME_WIDTH];   //起始日期(格式为:yyyymmdd)
	char ZJZH[ZJZH_WIDTH];       //资金账号
	char ZQDM[ZQDM_WIDTH];       //证券代码
    char ZQMC[ZQMC_WIDTH];       //证券名称
	int  ZQQS;                   //周期期数
	Money HKJE;                  //划款金额
    Money KCHKJE;                //开仓还款金额
    Money HGJE;                  //回购金额
    Money PCHKJE;                //平仓还款金额
    Money SYJE;                  //受益金额
}tagHZHGSGCX_Result;

//////////////存折抄股交年费冻结资金 ------ 联合证券///////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;           //头信息
  char   FZDM[FZDM_WIDTH];       //银行代码 
  char   YHZH[YHZH_WIDTH];       //银行帐号, (可以填'')
  char   CZZH[CZZH_WIDTH];       //存折帐号, (可以填'')
  char   KHBSLX;                 // '0'-'9'交易所代码,'Z' 资金帐号 (参看柜台设置)
  char   KHBS[KHBS_WIDTH];       //股东代码或资金帐号
}tagCZCG_JNFDJZJ_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  Money         NFJE;                   //年费金额
  char          LSH[HTXH_WIDTH];        //流水号
  char          ZJZH[ZJZH_WIDTH];       //资金账号
  char          JYSDM;                  //交易所代码
  char          GDDM[GDDM_WIDTH];       //股东代码
  char          YHZH[YHZH_WIDTH];       //银行账号
  char          CZZH[CZZH_WIDTH];       //存折账号
  char          HBDM;                   //货币代码
  char          KHLB[3];                //客户类别
  char          ZQDM[ZQDM_WIDTH];       //证券代码  '797801'
  char          MMLB;                   //买卖类别  'B'--交年费
  long          WTSL;                   //委托数量  @nfje
  SmallMoney    WTJG;                   //委托价格  1.00元
}tagCZCG_JNFDJZJ_Result;

//////////////存折抄股交年费设置合法标志 ------ 联合证券///////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;           //头信息
	char          LSH[HTXH_WIDTH];        //流水号   yzt_bzb中券商流水号
	//char          CLJG;                   //处理结果 '0' 成功 '1' 失败 '2' 主动冲帐
	char          YHLSH[YHLSH_WIDTH];     //可以为''  银行流水号, cljg为'0'保存银行流水号   *****/模拟发起时，填写银行合同序号/*****
	char          YHXXDM[10];             //可以为''  当p_cljg != '0'时, 填银行错误代码
	char          CJSJ[DATETIME_WIDTH];   //银行成交时间
	char          BZXX[BZXX_WIDTH];       //cjlg = '1' 时保存具体的错误信息
	char          ZJFSS[ZJS_WIDTH];       //年费的缴纳费用
}tagCZCG_JNFSZHFBZ_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char          CLJG;                   //处理结果 '0' 成功 '1' 失败 '2' 主动冲帐
  char          QSLSH[HTXH_WIDTH];      //流水号   yzt_bzb中券商流水号
  char          YHLSH[YHLSH_WIDTH];     //银行流水号, cljg为'0'保存银行流水号   *****/模拟发起时，填写银行合同序号/*****
  char          YHXXDM[10];             //当p_cljg != '0'时, 填银行错误代码
  char          CJSJ[DATETIME_WIDTH];   //银行成交时间
  char          BZXX[BZXX_WIDTH];       //cjlg = '1' 时保存具体的错误信息
  Money         ZJFSS;                  //年费的缴纳费用
  char          DZRQ[DATETIME_WIDTH];   //到帐日期
}tagCZCG_JNFSZHFBZ_Result;

///////////////////请求重发信息//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  int serio;                   //重定位记录 0取消发送
}tagAGAIN_Request;

//无返回
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ErrMsg[100];            //错误号
}tagErrMsg_Result;

///////////////////异常冻结资金//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码
  char ZJFSS[ZJS_WIDTH];       //冻结资金的金额
  char BZXX[BZXX_WIDTH];       //备注信息
}tagYCDJZJ_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;                //头信息
  Money ZJYE;                        //资金余额
  Money ZJKYS;                       //资金可用数
  Money ZJDJS;                       //资金冻结数
}tagYCDJZJ_Result;

///////////////////异常解冻资金//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码
  char ZJFSS[ZJS_WIDTH];       //解冻资金的金额
  char BZXX[BZXX_WIDTH];       //备注信息
}tagYCJDZJ_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;                //头信息
  Money ZJYE;                        //资金余额
  Money ZJKYS;                       //资金可用数
  Money ZJJDS;                       //资金解冻数
}tagYCJDZJ_Result;

/*****************************
		基本查询业务
*****************************/
///////////////////资金账号资料//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
}tagZJZL_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char ZJXM[9];                //资金姓名
  char SFZH[19];               //身份件码
  char DHHM[21];               //电话号码
  char YZBM[7];                //邮政编码
  char TXDZ[81];               //通讯地址
  char EMAIL[41];              //电子邮件
  char ZJLB;                   //证件类别
}tagZJZL_Result;

///////////////////客户资料查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 // 0'-'9'交易所代码(参看柜台设置)
                               // 'Z' 资金帐号
                               // 'C' 磁卡号
  char KHBS[CKBH_WIDTH];       //KHBS  股东代码或资金帐号或磁卡号
}tagZLCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char ZJXM[ZJXM_WIDTH];       //资金姓名
  char SFZH[SFZH_WIDTH];       //身份证号
  char EMAIL[EMAIL_WIDTH];     //Email地址 
  char XMQC[XMQC_WIDTH];       //中文名
  char YZBM[YZBM_WIDTH];       //邮编
  char LXDH[LXDH_WIDTH];       //联系电话
  char LXDZ[LXDZ_WIDTH];       //联系地址
  char KHLB[3];                //客户类别 00-散户 01-中户 02-大户 03-机构户 04-自营户 15-发展银行炒股户 99-特殊户
#ifdef  _KD3X
  char YYBDM[YYBDM_WIDTH];     //营业部代码
  char YYBMC[YYBMC_WIDTH];     //营业部名称
#endif
}tagZLCX_Result;

///////////////////客户详细资料查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
}tagXXZLCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char ZJXM[ZJXM_WIDTH];       //资金姓名
  char XMQC[XMQC_WIDTH];       //中文名
  char SFZH[SFZH_WIDTH];       //身份证号
  char LXDH[LXDH_WIDTH];       //联系电话
  char YZBM[YZBM_WIDTH];       //邮编
  char LXDZ[LXDZ_WIDTH];       //联系地址
  char EMAIL[EMAIL_WIDTH];     //Email地址 
  char BP[21];                 //BP机号码
  int  CZFS;                   //允许操作方式
  char YYBDM[YYBDM_WIDTH];     //营业部代码
  char KHLB[3];                //客户类别  
                               //00-散户 01-中户 02-大户 03-机构户 04-自营户 15-发展银行炒股户 99-特殊户 NF-联合年费制客户
  char JJRDM[5];               //经纪人代码
  char BZXX[BZXX_WIDTH];       //备注信息
  char GDDM0[GDDM_WIDTH];      //股东代码0
  char GDDM1[GDDM_WIDTH];      //股东代码1
  char GDDM2[GDDM_WIDTH];      //股东代码2
  char GDDM3[GDDM_WIDTH];      //股东代码3
  char GDDM4[GDDM_WIDTH];      //股东代码4
  char GDDM5[GDDM_WIDTH];      //股东代码5
}tagXXZLCX_Result;

///////////////////客户资料修改//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char ZJXM[ZJXM_WIDTH];       //资金姓名
  char XMQC[XMQC_WIDTH];       //中文名
  char SFZH[SFZH_WIDTH];       //身份证号
  char LXDH[LXDH_WIDTH];       //联系电话
  char YZBM[YZBM_WIDTH];       //邮编
  char LXDZ[LXDZ_WIDTH];       //联系地址
  char EMAIL[EMAIL_WIDTH];     //Email地址 
  char BP[21];                 //BP机号码
  char KHLB[3];                //客户类别
  char JJRDM[5];               //经纪人代码
}tagZLXG_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagZLXG_Result;

///////////////////客户查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char GDMS;                   // '0'单股东(只校验单个股东代码的交易密码)
                               // '1'同资金帐号且同身份证关联(同
	                             // 资金帐号且同身份证号下的股东全部校验，暂时未用)
                               // '2'同资金帐号关联(同资金帐号下的股东全部校验)

  char KHBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
                               // 'Z' 资金帐号
							   // 'C' 磁卡号
  char KHBS[CKBH_WIDTH];       // KHBS  股东代码或资金帐号或磁卡号
  char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置) 
	                             // ' ' 表示全部 (股东模式'2'时有效)

}tagKHCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //交易所代码
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码
  char GDXM[GDXM_WIDTH];       //股东姓名
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码(0:人民币　1:港币　2:美圆　参看柜台设置)
  int  ZDJY;                   //指定交易
	                             //-- 0:未指定
	                             //-- Bit0(=1) 首日指定
                               //-- Bit1(=2) 指定交易
                               //-- Bit2(=4) 首日回购指定
                               //-- Bit3(=8) 回购指定
  char GDZT;                   //股东状态(0:正常 1: 销户 2:冻结 3:锁定 4:挂失)
  int  ZGDBZ;                  //0:主股东 其它为副股东
  int  PGBZ;                   //1配A1权,2配A2权,3配A3权,8新股配售,32合作配售
}tagKHCX_Result;

//by zjt start
///////////////////客户查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char YYBDM[YYBDM_WIDTH];     //营业部代码

}tagKHZLCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //交易所代码
  char GDDM[GDDM_WIDTH];       //股东代码
  char GDXM[GDXM_WIDTH];       //股东姓名
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char TXDZ[81];       //资金帐号
  char SFZH[21];       //资金帐号
}tagKHZLCX_Result;

//by zjt end

///////////////////股份查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char GDMS;                   // '0' 单股东
                               // '1'同资金帐号且同身份证关联
                               // '2'同资金帐号关联
  char CXMS;                   // '0'股份
                               // '1'资金同股份(ZQDM 为空)
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char ZQBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
  char ZQBS[ZQDM_WIDTH];       //证券标识
}tagGFCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //交易所代码 'Z' 资金
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码   如为资金则为资金帐号
  char GDXM[GDXM_WIDTH];       //股东姓名
  char ZQDM[ZQDM_WIDTH];       //证券代码   如为资金则为货币代码
  char ZQMC[ZQMC_WIDTH];       //证券名称   如为资金则为货币名称
  Money YE;                    //余额
  Money KYS;                   //可用数
  Money MRDJS;                 //买入冻结
  Money MCDJS;                 //卖出冻结
  Money YCDJS;                 //异常冻结
  Money CKCB;                  //参考成本
  SmallMoney CKCBJG;           //参考成本价
  Money CKSZ;                  //参考市值
  SmallMoney CKSZJG;           //参考市价
  Money CKYK;                  //参考盈亏
}tagGFCX_Result;

///////////////////国债回购标准券查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;         //头信息
  char JYSDM;                 //'0'-'9'交易所代码(参看柜台设置)
  char GDDM[GDDM_WIDTH];      // 股东代码或资金帐号
  char BZQLB;                 //标准券类别 '0'国债标准券,'1'企债标准券,'2'国债+企债
}tagGZHGBZQCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char JYSDM;                  //交易所代码
  char GDDM[GDDM_WIDTH];       //股东代码
  char GDXM[GDXM_WIDTH];       //股东姓名
  Money BZQKYS;                //标准券可用数
  char BZQLBSM[12];            //标准券类别说明
}tagGZHGBZQCX_Result;

///////////////////卖出股份查询--KB32柜台//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char ZQBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
  char ZQBS[ZQDM_WIDTH];       //证券标识
  char GDMS;                   // '0' 单股东
                               // '1'同资金帐号且同身份证关联
                               // '2'同资金帐号关联
}tagMCGFCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //交易所代码 'Z' 资金
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码   如为资金则为资金帐号
  char GDXM[GDXM_WIDTH];       //股东姓名
  char ZQDM[ZQDM_WIDTH];       //证券代码   如为资金则为货币代码
  char ZQMC[ZQMC_WIDTH];       //证券名称   如为资金则为货币名称
  Money GFKYS;                 //股份可用数
}tagMCGFCX_Result;

///////////////////资金查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
  char KHBS[CKBH_WIDTH];       //KHBS  股东代码或资金帐号
}tagZJCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码
  Money YE;                    //余额
  Money KYS;                   //可用数
  Money ZJYCDJS;               //异常冻结数  指长期冻结的金额
  Money ZJMRDJS;               //买入冻结数  
  Money ZJMCDJS;               //卖出冻结数  
  Money ZQSZ;                  //证券市值
  Money ZJZRYE;                //资金昨日余额
  Money ZZC;                   //总资产
}tagZJCX_Result;

//by zjt start
///////////////////资金查询--天同//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
  char YYBDM[YYBDM_WIDTH];
  char KHBS[CKBH_WIDTH];       //KHBS  股东代码或资金帐号
}tagZJYECX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码
  Money YE;                    //余额
  Money KYS;                   //可用数
  Money ZJYCDJS;               //异常冻结数  指长期冻结的金额
  Money ZJMRDJS;               //买入冻结数  
  Money ZJMCDJS;               //卖出冻结数  
}tagZJYECX_Result;

//by zjt end

///////////////////当日委托查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char GDMS;                   // '0' 单股东
                               // '1'同资金帐号且同身份证关联
                               // '2'同资金帐号关联
  char CXMS;                   // '0'全部委托
                               // '1'可撤单委托
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号

  char ZQBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
  char ZQBS[ZQDM_WIDTH];       // 证券标识
  char HTXH[HTXH_WIDTH];       // 合同序号
}tagDRWTCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char WTSJ[DATETIME_WIDTH];   //委托时间 (HH:MM:SS)
  char HTXH[HTXH_WIDTH];       //合同序号
  char JYSDM;                  //交易所代码
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码
  char GDXM[GDXM_WIDTH];       //股东姓名
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char ZQMC[ZQMC_WIDTH];       //证券名称
  char MMLB;                   //买卖类别
                               //'B' 买卖方向为买入
                               //'S' 买卖方向为卖出
                               //'Z' 买卖方向为转托
                               //'G' 转股
                               //'H' 回售
  char MMLBSM[QTSM_WIDTH];     //买卖类别说明
  char CDBZ;                   //撤单状态
                               //'0' 未撤
                               //'1' 申撤
                               //'4' 部撤
                               //'5' 全撤
                               //'6' 部成
                               //'7' 全成
                               //'8' 未发
                               //'9' 已报
  char CDBZSM[QTSM_WIDTH];     //撤单状态说明
  SmallMoney WTJG;             //委托价格
  long WTSL;                   //委托数量
  SmallMoney CJJG;             //成交价格
  long CJSL;                   //成交数量
  long CDSL;                   //撤单数量
  //char YHLSH[YHLSH_WIDTH];		 //银行流水号(银行的合同序号)
  //char FZMC[FZMC_WIDTH];       //存折炒股银行的名称
}tagDRWTCX_Result;
 
///////////////////历史委托查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char GDMS;                   // '0' 单股东
                               // '1'同资金帐号且同身份证关联
                               // '2'同资金帐号关联
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char ZQBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
  char ZQBS[ZQDM_WIDTH];       //证券标识
  char QSRQ[DATETIME_WIDTH];   //起始日期(格式为yyyymmdd)
  char ZZRQ[DATETIME_WIDTH];   //终止日期(格式为yyyymmdd)
  char CXTS[DATETIME_WIDTH];   //查询天数  (起止日期与查询天数只能有一)
}tagLSWTCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char WTRQ[DATETIME_WIDTH];   //委托日期(格式为yyyymmdd)
  char HTXH[HTXH_WIDTH];       //合同序号
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码
  char GDXM[GDXM_WIDTH];       //股东姓名
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char ZQMC[ZQMC_WIDTH];       //证券名称
  char MMLB;                   //买卖类别
                               //'B' 买卖方向为买入
                               //'S' 买卖方向为卖出
                               //'Z' 买卖方向为转托
                               //'G' 转股
                               //'H' 回售
  char MMLBSM[QTSM_WIDTH];     //买卖类别说明
  SmallMoney WTJG;             //委托价格
  long WTSL;                   //委托数量
  SmallMoney CJJG;             //成交价格
  long CJSL;                   //成交数量
  long CDSL;                   //撤单数量
  char WTSJ[DATETIME_WIDTH];   //委托时间 (HH:MM:SS)
  //char FZMC[FZMC_WIDTH];       //存折炒股银行的名称
}tagLSWTCX_Result;

///////////////////当日成交查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char GDMS;                   // '0' 单股东
                               // '1'同资金帐号且同身份证关联
                               // '2'同资金帐号关联
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char CXFS;                   // '1'按合同序号合并查询
                               // '0'查明细
                               // '2'查累计
  char ZQBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
  char ZQBS[ZQDM_WIDTH];       // 证券标识
  char HTXH[HTXH_WIDTH];       // 合同序号
}tagDRCJCX_Request;

typedef struct {
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;
  char HTXH[HTXH_WIDTH];       //合同序号  若为成交累计无效
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码  若为成交累计无效
  char GDXM[GDXM_WIDTH];       //股东姓名  若为成交累计无效
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char ZQMC[ZQMC_WIDTH];       //证券名称
  char MMLB;                   //买卖类别
  char MMLBSM[QTSM_WIDTH];     //买卖类别说明
  char WTSJ[DATETIME_WIDTH];   //委托时间  若为成交累计无效
  char CJSJ[DATETIME_WIDTH];
  SmallMoney WTJG;             //委托价格
  long WTSL;                   //委托数量
  SmallMoney CJJG;             //成交价格
  long CJSL;                   //成交数量
  Money CJJE;                  //成交金额
  char FZDM[FZDM_WIDTH];       //分支代码
                               // '' 券商本地
                               //其它参见 "查询开办了存折炒股的银行的信息"
  char CJHM[CJHM_WIDTH];       //成交号码  //add by liyj 2002.06.11
}tagDRCJCX_Result;

///////////////////查询实时成交//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
	long  LSH;                   //流水号
	int   CZFS;                  //操作方式,-1标示查询全部
}tagSSCJCX_Request;

typedef struct {
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;
  char HTXH[HTXH_WIDTH];       //合同序号  若为成交累计无效
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码  若为成交累计无效
  char GDXM[GDXM_WIDTH];       //股东姓名  若为成交累计无效
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char ZQMC[ZQMC_WIDTH];       //证券名称
  char MMLB;                   //买卖类别
  char MMLBSM[QTSM_WIDTH];     //买卖类别说明
  char WTSJ[DATETIME_WIDTH];   //委托时间  若为成交累计无效
  char CJSJ[DATETIME_WIDTH];
  SmallMoney WTJG;             //委托价格
  long WTSL;                   //委托数量
  SmallMoney CJJG;             //成交价格
  long CJSL;                   //成交数量
  Money CJJE;                  //成交金额
  char FZDM[FZDM_WIDTH];       //分支代码
                               // '' 券商本地
                               //其它参见 "查询开办了存折炒股的银行的信息"
  char CJHM[CJHM_WIDTH];       //成交号码
  int  LSH;                    //流水号
}tagSSCJCX_Result;

///////////////////查询实时撤单//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  long  LSH;                   //流水号
  int   CZFS;                  //操作方式,-1标示查询全部
}tagSSCDCX_Request;

typedef struct {
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;
  char HTXH[HTXH_WIDTH];       //合同序号  若为成交累计无效
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码  若为成交累计无效
  char GDXM[GDXM_WIDTH];       //股东姓名  若为成交累计无效
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char ZQMC[ZQMC_WIDTH];       //证券名称
  char MMLB;                   //买卖类别
  char MMLBSM[QTSM_WIDTH];     //买卖类别说明
  char WTSJ[DATETIME_WIDTH];   //委托时间  若为成交累计无效
  char CJSJ[DATETIME_WIDTH];
  SmallMoney WTJG;             //委托价格
  long WTSL;                   //委托数量
  SmallMoney CJJG;             //成交价格
  long CJSL;                   //成交数量
  Money CJJE;                  //成交金额
  char FZDM[FZDM_WIDTH];       //分支代码
                               // '' 券商本地
                               //其它参见 "查询开办了存折炒股的银行的信息"
  char CJHM[CJHM_WIDTH];       //成交号码
  int  LSH;                    //流水号
}tagSSCDCX_Result;

///////////////////历史成交查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char GDMS;                   // '0' 单股东
                               // '1'同资金帐号且同身份证关联
                               // '2'同资金帐号关联
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char ZQBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
  char ZQBS[ZQDM_WIDTH];       //证券标识
  char QSRQ[DATETIME_WIDTH];   //起始日期(YYYYMMDD)
  char ZZRQ[DATETIME_WIDTH];   //终止日期(YYYYMMDD)
  char CXTS[DATETIME_WIDTH];   //查询天数  (起止日期与查询天数只能有一)
  char CXFS;                   // '0'按合同序号合并查询
                               // '1'查累计
}tagLSCJCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char FSRQ[DATETIME_WIDTH];   //委托日期   查累计无效
  char HTXH[HTXH_WIDTH];       //合同序号   查累计无效
  char JYSDM;                  //'0'-'9'交易所代码(参看柜台设置)
  char JYSJC[JYSJC_WIDTH];     //交易所简称 查累计无效
  char GDDM[GDDM_WIDTH];       //股东代码   查累计无效
  char GDXM[GDXM_WIDTH];       //股东姓名   查累计无效
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char ZQMC[ZQMC_WIDTH];       //证券名称
  char ZYDMSM[ZYDM_WIDTH];     //买卖类别说明
  char MMLB;                   //买卖类别
  SmallMoney WTJG;             //委托价格
  long WTSL;                   //委托数量
  SmallMoney CJJG;             //成交价格
  long CJSL;                   //成交数量
  Money CJJE;                  //成交金额
  SmallMoney SXF;              //手续费
  SmallMoney YHS;              //印花税
  SmallMoney GHF;              //过户费
  SmallMoney QSF;              //清算费
  SmallMoney JYGF;             //交易规费
  SmallMoney WTDF;             //委托单费
  SmallMoney CJDF;             //成交单费
  SmallMoney CDDF;             //撤单单费
  Money HZJE;                  //划帐金额
  Money ZJBCYE;                //资金本次余额 查累计无效
  long GFBCYE;                 //股份本次余额 查累计无效
  char CJSJ[DATETIME_WIDTH];	 //成交时间
  char FZDM[FZDM_WIDTH];       //分支代码
                               // '' 券商本地
                               //其它参见 "查询开办了存折炒股的银行的信息"
}tagLSCJCX_Result;

///////////////////配号查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char GDMS;                   // '0' 单股东
                               // '1'同资金帐号且同身份证关联
                               // '2'同资金帐号关联
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char ZQBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
  char ZQBS[ZQDM_WIDTH];       //证券标识
  char QSRQ[DATETIME_WIDTH];   //起始日期(YYYYMMDD)
  char ZZRQ[DATETIME_WIDTH];   //终止日期(YYYYMMDD)
  char CXTS[DATETIME_WIDTH];   //查询天数  (起止日期与查询天数只能有一)
}tagXGPH_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char PHRQ[DATETIME_WIDTH];     //日期 (YYYYMMDD)
  char ZJZH[ZJZH_WIDTH];       //资金帐户
  char JYSDM;                  //交易所代码
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char ZQMC[ZQMC_WIDTH];       //证券名称
  char HTXH[HTXH_WIDTH];       //合同序号
  long CJSL;                   //成交数量
  char SGPH[SGPH_WIDTH];       //配号
  char ZQBZ;                   //中签标志 '0' 配号 '1' 中签
  char ZQBZSM[QTSM_WIDTH];     //中签标志说明
}tagXGPH_Result;

///////////////////资金流水查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char QSRQ[DATETIME_WIDTH];   //起始日期(yyyymmdd)
  char ZZRQ[DATETIME_WIDTH];   //终止日期(yyyymmdd)
  char CXTS[DATETIME_WIDTH];   //查询天数  (起止日期与查询天数只能有一)
}tagZJLS_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char FSRQ[DATETIME_WIDTH];   //委托日期(yyyymmdd)
  char HTXH[HTXH_WIDTH];       //合同序号
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码
  char GDXM[GDXM_WIDTH];       //股东姓名
  char ZQDM[ZQDM_WIDTH];       //证券代码( 如为存取则为银行代码)
  char ZQMC[ZQMC_WIDTH];       //证券名称( 如为存取则为银行名称)
  char ZYDMSM[ZYDM_WIDTH];     //买卖类别说明,摘要代码说明
  SmallMoney WTJG;             //委托价格
  long WTSL;                   //委托数量
  SmallMoney CJJG;             //成交价格
  long CJSL;                   //成交数量
  Money CJJE;                  //成交金额
  Money ZJFSS;                 //资金发生数
  SmallMoney SXF;              //手续费
  SmallMoney YHS;              //印花税
  SmallMoney GHF;              //过户费
  SmallMoney QSF;              //清算费
  SmallMoney JYGF;             //交易规费
  SmallMoney WTDF;             //委托单费
  SmallMoney CJDF;             //成交单费
  SmallMoney CDDF;             //撤单单费
  Money HZJE;                  //划帐金额(如果是派息,则为派息金额)
  Money ZJBCYE;                //资金本次余额 (查累计时无效)
  long GFBCYE;                 //股份本次余额 (查累计时无效)
  //char FZMC[FZMC_WIDTH];       //存折炒股银行的名称
  char HBDM;                   //货币代码
  char ZYDM[6];                //摘要代码
  char JYLX[3];                //交易代码
  char JYLXSM[8];              //交易代码说明
}tagZJLS_Result;

//by zjt start
///////////////////资金流水查询--天同//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char YYBDM[YYBDM_WIDTH];
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char QSRQ[DATETIME_WIDTH];   //起始日期(yyyymmdd)
  char ZZRQ[DATETIME_WIDTH];   //终止日期(yyyymmdd)
  char CXTS[DATETIME_WIDTH];   //查询天数  (起止日期与查询天数只能有一)
}tagZJLSCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char FSRQ[DATETIME_WIDTH];   //委托日期(yyyymmdd)
  char HTXH[HTXH_WIDTH];       //合同序号
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码
  char GDXM[GDXM_WIDTH];       //股东姓名
  char ZQDM[ZQDM_WIDTH];       //证券代码( 如为存取则为银行代码)
  char ZQMC[ZQMC_WIDTH];       //证券名称( 如为存取则为银行名称)
  char ZYDMSM[ZYDM_WIDTH];     //买卖类别说明
  SmallMoney WTJG;             //委托价格
  long WTSL;                   //委托数量
  SmallMoney CJJG;             //成交价格
  long CJSL;                   //成交数量
  Money CJJE;                  //成交金额
  Money ZJFSS;                 //资金发生数
  SmallMoney SXF;              //手续费
  SmallMoney YHS;              //印花税
  SmallMoney GHF;              //过户费
  SmallMoney QSF;              //清算费
  SmallMoney JYGF;             //交易规费
  SmallMoney WTDF;             //委托单费
  SmallMoney CJDF;             //成交单费
  SmallMoney CDDF;             //撤单单费
  Money HZJE;                  //划帐金额(如果是派息,则为派息金额)
  Money ZJBCYE;                //资金本次余额 (查累计时无效)
  long GFBCYE;                 //股份本次余额 (查累计时无效)
  char FZMC[FZMC_WIDTH];       //存折炒股银行的名称
  char HBDM;                   //货币代码
}tagZJLSCX_Result;
//by zjt end

///////////////////批量委托信息//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //交易所代码
  char GDDM[GDDM_WIDTH];       //股东代码
  char ZQDM[ZQDM_WIDTH];       //证券代码
}tagPLWTXX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  long GFKYS;                  //股份可用数
  long GDDMS;                  //股东模式
  Money ZJKYS;                 //资金可用数 
}tagPLWTXX_Result;

///////////////////批量撤单查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
                               // 'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       //KHBS; 股东代码或资金帐号
  char ZQBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
  char ZQBS[ZQDM_WIDTH];       //ZQBS  证券代码
  char WTJGXX[WTJG_WIDTH];     //委托价格下限
  char WTJGSX[WTJG_WIDTH];     //委托价格上限
}tagPLCDCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //交易所代码
  char GDDM[GDDM_WIDTH];       //股东代码
  char HTXH[HTXH_WIDTH];       //合同序号
}tagPLCDCX_Result;


/*****************************
		银证转账业务
*****************************/
///////////////////划拨资金//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码
  char HBFX;                   //划拨方向 ('O' 划出到银行 'I'划入到证券)
  char ZKJE[HBJE_WIDTH];       //划拨金额
  char YHDM[YHDM_WIDTH];       //银行代码
  char YHMM[YHMM_WIDTH];       //银行密码
  char ZJMM[JYMM_WIDTH];       //资金密码
  int  WaitTime;               //等待时间
  char ReqSrcInfo[QQYXX_WIDTH];  //请求源信息，如：网卡地址
}tagZJHB_Request;

typedef struct{
  tagBLOCK_HEAD HEAD;          //头信息
  char HTXH[HTXH_WIDTH];       //合同序号
  char BZXX[BZXX_WIDTH];       //成交情况说明, 内容格式：
	                           //              合同序号是xxxxxx正在处理
	                           //              合同序号是xxxxxx资金划拨成功
	                           //              合同序号是xxxxxx其他情况:,cjbz=x
}tagZJHB_Result;

///////////////////银行余额查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码
  char YHDM[YHDM_WIDTH];       //银行代码
  char YHMM[YHMM_WIDTH];       //银行密码
  char ZJMM[JYMM_WIDTH];       //资金密码
  int WaitTime;                //等待时间
  char ReqSrcInfo[QQYXX_WIDTH];  //请求源信息，如：网卡地址
}tagYHYE_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char BZXX[80];               //成交情况说明, 内容格式：
	                             //              合同序号是xxxxxx正在处理
	                             //              合同序号是xxxxxx银行余额是：100.00
	                             //              合同序号是xxxxxx其他情况:,cjbz=x
}tagYHYE_Result;

///////////////////银行更密//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码
  char YHDM[YHDM_WIDTH];       //银行代码
  char YHMM[YHMM_WIDTH];       //银行密码
  char XYHMM[YHMM_WIDTH];      //新银行密码
  char ZJMM[JYMM_WIDTH];       //资金密码
  int  WaitTime;               //等待时间
  char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagYHGM_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char BZXX[80];               //成交情况说明, 内容格式：
	                             //              合同序号是xxxxxx正在处理
	                             //              合同序号是xxxxxx银行更密成功
	                             //              合同序号是xxxxxx其他情况:,cjbz=x
}tagYHGM_Result;

///////////////////划拨查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char HTXH[HTXH_WIDTH];       //合同序号, ""查询全部
}tagHBCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char WTSJ[DATETIME_WIDTH];   //委托时间
  char YHDM[YHDM_WIDTH];       //银行代码
  char YHMC[YHMC_WIDTH];       //银行名称
  char HTXH[HTXH_WIDTH];       //合同序号
  char CQLB[3];                //存取类别
                               //-- 'KH' 开户 'XH' 销户 'CR' 存入'QC' 取出
                               //-- 'CZ' 冲正 'YE' 查询银行余额 'MM' 修改存折密码
                               //-- 'YM' 取银行端转帐明细
  char CQLBSM[QTSM_WIDTH];     //存取类别说明
  Money ZKJE;                  //转款金额
  char ZTSM[QTSM_WIDTH];       //状态说明
  Money YHYE;                  //银行余额(银行余额查询用)
  char FQFX;                   //'A' 双方发起 'Y' 银行发起 'Q' 券商发起
  char FQFXSM[8];              //发起方向说明
  char HBDM;                   //货币代码
  char CJBZ;                   //处理结果:0--成功; ''--未处理; 其他--失败
}tagHBCX_Result;

///////////////////划拨查询--流水号//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 //'0'-'9'交易所代码(参看柜台设置)
                               //  'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // 股东代码或资金帐号
  char LSH[HTXH_WIDTH];        // 流水号
}tagHBCXLSH_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char WTSJ[DATETIME_WIDTH];   //委托时间
  char YHDM[YHDM_WIDTH];       //银行代码
  char YHMC[YHMC_WIDTH];       //银行名称
  char HTXH[HTXH_WIDTH];       //合同序号
  char CQLB[3];                //存取类别
                               //-- 'KH' 开户 'XH' 销户 'CR' 存入'QC' 取出
                               //-- 'CZ' 冲正 'YE' 查询银行余额 'MM' 修改存折密码
                               //-- 'YM' 取银行端转帐明细
  char CQLBSM[QTSM_WIDTH];     //存取类别说明
  Money ZKJE;                  //转款金额
  char ZTSM[QTSM_WIDTH];       //状态说明--备注信息
  Money YHYE;                  //银行余额(银行余额查询用)
  char FQFX;                   //'A' 双方发起 'Y' 银行发起 'Q' 券商发起
  char FQFXSM[8];              //发起方向说明
  char HBDM;                   //货币代码
  char CJBZ;                   //处理结果:0--成功; 其他--失败
}tagHBCXLSH_Result;

///////////////////划拨撤单//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char HBDM;                   //货币代码(参考柜台设置) 
  char ZJZH[ZJZH_WIDTH];       //资金帐号 
  char HTXH[HTXH_WIDTH];       //合同序号　　　　
}tagHBCD_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  Money ZJBCKYS;               //资金本次可用数
}tagHBCD_Result;

///////////////////帐号开通的银证转帐信息//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBS[KHBS_WIDTH];       //KHBS  资金帐号
}tagZHYZ_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char HBDM;                   //货币代码
  char YHDM[YHDM_WIDTH];       //银行代码
  char YHMC[YHMC_WIDTH];       //银行名称
}tagZHYZ_Result;

///////////////////期证转账  资金划拨   恒远证券使用//////////////////
//typedef struct
//{
//  tagBLOCK_HEAD HEAD;          //头信息
//  char ZJZH[ZJZH_WIDTH];       //资金帐号
//	char HBDM;                   //货币代码
//  char ZJMM[JYMM_WIDTH];       //资金密码
//	char YHDM[YHDM_WIDTH];       //银行代码
//  char YHMM[YHMM_WIDTH];       //银行密码
//  char DSFQSDM[YHDM_WIDTH];    //第三方(期货)代码
//  char DSFMM[YHMM_WIDTH];      //第三方(期货)密码
//  char HBFX;                   //划拨方向 ('O' 划出到银行 'I'划入到证券)
//  char ZJFSS[HBJE_WIDTH];      //划拨金额
//  char BZXX[BZXX_WIDTH];       //备注信息
//}tagQZZJHB_Request;

//typedef struct
//{
//  tagBLOCK_HEAD HEAD;          //头信息
//  char  DSfCQLSH[HTXH_WIDTH];  //第三方存取流水号  转出时扫描
//	char  CQKLSH[HTXH_WIDTH];    //存取流水号  转入时扫描
//}tagQZZJHB_Result;

///////////////////期证转账  资金余额   恒远证券使用//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码
  char ZJMM[JYMM_WIDTH];       //资金密码
  char YHDM[YHDM_WIDTH];       //银行代码
  char DSFQSDM[YHDM_WIDTH];    //第三方(期货)代码
  char ReqSrcInfo[QQYXX_WIDTH];//请求源信息，如：网卡地址
  char BZXX[BZXX_WIDTH];       //备注信息
}tagQZZJYE_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char  LSH[HTXH_WIDTH];       //流水号
  char  CQKLSH[HTXH_WIDTH];    //存取流水号
}tagQZZJYE_Result;

///////////////////期证转账  第三方(期货)基本信息   恒远证券使用//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char HBDM;                   //货币代码
  char YHDM[YHDM_WIDTH];       //银行代码
  char DSFQSDM[YHDM_WIDTH];    //第三方(期货)代码,可以为空，为空则查全部
}tagQZQSXX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char HBDM;                   //货币代码
  char YHDM[YHDM_WIDTH];       //银行代码
  char DSFQSDM[YHDM_WIDTH];    //第三方(期货)代码
  char DSFQSDC[YHMC_WIDTH];    //第三方(期货)名称
}tagQZQSXX_Result;

///////////////////期银转账  资金划拨   恒远证券使用//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码
  char ZJMM[JYMM_WIDTH];       //资金密码
  char YHDM[YHDM_WIDTH];       //银行代码
  char YHMM[YHMM_WIDTH];       //银行密码
  char DSFQSDM[YHDM_WIDTH];    //第三方(期货)代码
  char DSFMM[YHMM_WIDTH];      //第三方(期货)密码
  char HBFX;                   //划拨方向 ('O' 划出到银行 'I'划入到证券)
  char ZJFSS[HBJE_WIDTH];      //划拨金额
  char BZXX[BZXX_WIDTH];       //备注信息
}tagQYZJHB_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char  LSH[HTXH_WIDTH];       //流水号
  char  CQKLSH[HTXH_WIDTH];    //存取流水号
}tagQYZJHB_Result;


/*****************************
		存折炒股业务
*****************************/
///////////////////委托确认[包括普通委托和存折炒股的委托]//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;              //头信息
  char JYSDM;                      // '0'-'9'交易所代码(参看柜台设置)
  char GDDM[GDDM_WIDTH];           //KHBS  股东代码或资金帐号
  char ZQDM[ZQDM_WIDTH];           //ZQDM  证券代码
  char MMLB;                       //买卖类别
  char WTSL[WTSL_WIDTH];           //WTSL  委托数量
  char WTJG[WTJG_WIDTH];           //WTJG  委托价格
  char HTXH[HTXH_WIDTH];           //合同序号  为‘ ’时自动生成
  char JYDD;                       // 'Q' 券商本地委托，与银行无关
  char FZDM[FZDM_WIDTH];           //FZDM 银行代码                                                 
  char ZJLX;                       //ZJLX 资金流向 'Q' 券商 'Y' 银行 如果券商保留银行资金可
  	                                 // 用数,取'Q'，否则，取‘Y’                              
                                   //mmlb = 'B' 是用@p_zjlx(资金流向值)资金买股票到fzdm(银行值)                       
                                   //mmlb = 'S' 是卖fzdm股票，资金回@p_zjlx(资金流向值) 
  	
  char YHZH[YHZH_WIDTH];           //YHZH 银行帐号(可以不填,否则必须提供正确的值)                  
  char CZZH[CZZH_WIDTH];           //CZZH 存折帐号（银行帐号的子帐号,可以不填,否则必须提供正确的值) 
  char CZMM[YHMM_WIDTH];           //存折密码(当银行委托要求较验密码时使用),一般可不填
  char ReqSrcInfo[QQYXX_WIDTH];    //请求源信息，如：网卡地址
//  char BZXX[BZXX_WIDTH];           //备注信息
}tagCZCGWTQR_Request;

#ifndef _GDSB
typedef struct{
  tagBLOCK_HEAD HEAD;          //头信息
  char HTXH[HTXH_WIDTH];       //合同序号:若为空则取LSH,然后去扫描接口库(czcgcxjkk),该情况针对KD25,KB32不用
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码
  Money WTJE;                  //委托金额
  Money DJJE;                  //冻结金额
  Money KYZJ;                  //资金本次可用数
  long GFFSS;                  //股份发生数
  long KYGF;                   //股份本次可用数
#ifndef _KD3X
  int LSH;                     //流水号 
#endif
}tagCZCGWTQR_Result;

#else

typedef struct{
  tagBLOCK_HEAD HEAD;          //头信息
  char HTXH[HTXH_WIDTH];       //合同序号  如果等于1,则出错,其他值成功
  long KYGF;                   //股份本次可用数 HTXH!=1时,本字段才有内容
  char CWXX[50];               //错误信息  当HTXH==1时,本字段才有内容
}tagCZCGWTQR_Result;
#endif

///////////////////存折炒股委托撤单[包括普通委托和存折炒股的委托]//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置)
  char GDDM[GDDM_WIDTH];       //KHBS  股东代码或资金帐号
  char HTXH[HTXH_WIDTH];       // 合同序号
  int  LSH;                    //券商czcg_jkk 流水号 撤销未处理请求时使用 
  char FZDM[FZDM_WIDTH];       //FZDM 银行代码
                               //     mmlb = 'B' 是用@p_zjlx(资金流向值)资金买股票到fzdm(银行值)                       
                               //     mmlb = 'S' 是卖fzdm股票，资金回@p_zjlx                   
  char YHLSH[YHLSH_WIDTH];     //YHLSH 银行生成的合同序号                                               
                               //      fqf = 'Q' 可以不填                                       
                               //      fqf = 'Y' 必须填写，并保证唯一性                         
  char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagCZCGWTCD_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagCZCGWTCD_Result;

///////////////////根据流水号取czcg_jkk信息//////////////////
//金证2.5柜台存折炒股业务用到，金证3.2柜台存折炒股业务不要使用。
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  int LSH;                     //查询接口库的流水号
}tagCZCGCXJKK_Request;

typedef struct{
  tagBLOCK_HEAD HEAD;				        //头信息
  char CLJG;                        //处理结果 '' 未处理 '0' 合法 '1' 非法 '2' 主动冲正
  char FSBZ;                        //发送标志 '0' 未发 'X' 正在发送 '1' 已经发送
  char YHLSH[YHLSH_WIDTH];          //对应的银行流水号
  char YHZH[YHZH_WIDTH];            //银行帐号
  char CZZH[CZZH_WIDTH];            //存折帐号（银行帐号的子帐号)
  char BZXX[BZXX_WIDTH];            //备注信息
  char YWLB[YWLB_WIDTH];            //业务类别
  char YH_CLJG;                     //银行处理结果
  char QS_HTXH[HTXH_WIDTH];         //券商合同序号
  Money ZJFSS;                      //资金发生数(委托冻结金额)
  Money BYJE1;                      //备用1(银行资金可取余额)
  Money BYJE2;                      //备用2(银行资金可用余额)
  char HBDM;						//货币代码
  int  GLLSH;						//关联流水号，主要用于异步操作。如买入操作，在资金成功冻结之前不能发送。>0 向前关联，<0 向后关联
}tagCZCGCXJKK_Result;

///////////////////存折炒股查询股东信息//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char GDMS;                   // '0'单股东
                               // '1'同资金帐号且同身份证关联
                               // '2'同资金帐号关联
  char KHBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
                               // 'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       // KHBS  股东代码或资金帐号
  char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置) ' ' 全部 (股东模式'2'有效)
  char FZDM[FZDM_WIDTH];       // 银行代码
}tagCZCGCXGDXX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //交易所代码
  char GDDM[GDDM_WIDTH];       //股东代码
  char GDXM[GDXM_WIDTH];       //股东姓名
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char FZDM[FZDM_WIDTH];       //银行代码
  char YHZH[YHZH_WIDTH];       //银行帐号
  char CZZH[CZZH_WIDTH];       //存折帐号
  char ZJDJMM;								 //券商发起买入向银行冻结资金是否要检验存折密码(1:是0:否)
  char GPMCMM;								 //券商发起卖出股票送银行是否要检验存折密码(1:是0:否)
}tagCZCGCXGDXX_Result;

///////////////////存折炒股身份验证//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
                               // 'Z' 资金帐号
  char KHBS[CKBH_WIDTH];       //KHBS; 股东代码或资金帐号
  char FZDM[FZDM_WIDTH];       //银行代码 
  char YHZH[YHZH_WIDTH];       //银行帐号
  char YHMM[YHMM_WIDTH];       //银行密码
  char BZXX[BZXX_WIDTH];       //备注信息
}tagCZCGSFYZ_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  int  LSH;                    //待处理的记录在存折炒股接口库中记录号,根据此lsh查询是否处理成功
  char GDDM[GDDM_WIDTH];       //股东代码
}tagCZCGSFYZ_Result;

///////////////////存折炒股银行资金查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char KHBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
  char KHBS[KHBS_WIDTH];       //股东代码
  char FZDM[FZDM_WIDTH];       //银行代码 
  char YHZH[YHZH_WIDTH];       //银行帐号, (可以填'')
  char CZZH[CZZH_WIDTH];       //存折帐号, (可以填'')
  char YHMM[YHMM_WIDTH];       //银行密码
}tagCZCGYHZJCX_Request;

#ifndef _GDSB
typedef struct
{
  tagBLOCK_HEAD HEAD;            //头信息
#ifdef _KD3X
  char  cljg;                     // 0---成功  1---失败
  Money yhye;                     //银行资金余额
  Money yhkys;                    //银行可用数
  char  bzxx[BZXX_WIDTH];         //失败时银行返回的错误信息 
  Money bdzjkys;                  //本地资金可用数
#else
  int  LSH;                      //待处理的记录在存折炒股接口库中记录号,根据此lsh查询是否处理成功
  char HBDM;                     //货币代码(参看柜台设置)
#endif
}tagCZCGYHZJCX_Result;

#else

typedef struct
{
  tagBLOCK_HEAD HEAD;            //头信息
  char  cljg;                     // 0---成功  1---失败
  Money yhye;                     //银行资金余额
}tagCZCGYHZJCX_Result;
#endif

//////////////存折炒股股东开通银行查询///////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;           //头信息
	char ZJZH[ZJZH_WIDTH];        //资金帐号(输入资金帐号 或 交易所代码和股东代码)
	char JYSDM;                   //交易所代码
	char GDDM[GDDM_WIDTH];        //股东代码
}tagCZCGKTYHCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char  ZJZH[ZJZH_WIDTH];      //资金帐号
  char  FZDM[FZDM_WIDTH];      //银行代码
}tagCZCGKTYHCX_Result;

//////////////存折炒股取可(卖)买数量///////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;           //头信息
  char FZDM[FZDM_WIDTH];        //银行代码
  char YHZH[YHZH_WIDTH];        //银行帐号(可以不填,否则必须提供正确的值)                  
  char CZZH[CZZH_WIDTH];        //存折帐号(银行帐号的子帐号,可以不填,否则必须提供正确的值) 
  char JYSDM;                   //'0'-'9'交易所代码(参看柜台设置)
  char GDDM[GDDM_WIDTH];        //股东代码
  char ZQDM[ZQDM_WIDTH];        //证券代码
  char WTJG[WTJG_WIDTH];        //委托价格
  char ZJKYS[ZJS_WIDTH];        //资金可用数
  char BZXX[BZXX_WIDTH];        //备注信息
}tagCZCGKMSL_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  long KMSL;                   //可买数量
  long GFKYS;                  //股份可用数
}tagCZCGKMSL_Result;

/*****************************
		预委托类业务
*****************************/
///////////////////预委托业务//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;           //头信息
  char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置)
  char GDDM[GDDM_WIDTH];       //股东代码
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char MMLB;                   //买卖类别
  char WTSL[WTSL_WIDTH];       //委托数量
  char WTJG[WTJG_WIDTH];       //委托价格
  char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagYWTQR_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  long JLXH;                   //记录序号
}tagYWTQR_Result;

///////////////////删除预委托//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;           //头信息
  long JLXH;                   //记录序号
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置)
  char GDDM[GDDM_WIDTH];       //股东代码
  char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagYWTCD_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
}tagYWTCD_Result;

///////////////////发送预委托//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  long JLXH;                   //记录序号
  char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置)
  char GDDM[GDDM_WIDTH];       //股东代码
  char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagYWTFS_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char HTXH[HTXH_WIDTH];       //合同序号
  char ZJZH[ZJZH_WIDTH];       //资金帐号
  char HBDM;                   //货币代码(参看柜台设置)
  Money WTJE;                  //委托金额
  Money WTDJJE;                //委托冻结金额
  Money ZJBCKYS;               //资金本次可用数
  long GFFSS;                  //股份发生数
  long GFBCKYS;                //股份本次可用数
}tagYWTFS_Result;

///////////////////预委托查询//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;           //头信息
  char KHBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
                               // 'Z' 资金帐号
  char KHBS[KHBS_WIDTH];       //KHBS; 股东代码或资金帐号
  char GDMS;                   // '0'单股东
                               // '1'同资金帐号且同身份证关联
                               // '2'同资金帐号关联
}tagYWTCX_Request;

typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  long JLXH;                   //记录序号
  char WTRQ[DATETIME_WIDTH];   //委托日期(格式为yyyymmdd)
  char WTSJ[DATETIME_WIDTH];   //委托时间 (HH:MM:SS)
  char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置)
  char JYSJC[JYSJC_WIDTH];     //交易所简称
  char GDDM[GDDM_WIDTH];       //股东代码
  char GDXM[GDXM_WIDTH];       //股东姓名
  char HBDM;                   //货币代码(参看柜台设置)
  char HBMC[HBMC_WIDTH];       //货币名称(如人民币、港币、美圆)
  char ZQDM[ZQDM_WIDTH];       //证券代码
  char ZQMC[ZQMC_WIDTH];       //证券名称( 如为存取则为银行名称)
  short ZQLB;                  //证券类别 0股票 1国债 2企业债券 3回购 4基金
                               //         5投资基金 6权证 9转换债券 10实物国债
                               //         11实物企债 12特殊证券
  char JYLX[5];                //交易类型 'PT'正常交易 'SG'申购 'PS' 配售 'PH'配号 'PP' 配售配号 'JK' 缴款
  char MMLB;                   //买卖类别
  SmallMoney WTJG;             //委托价格
  long WTSL;                   //委托数量
}tagYWTCX_Result;

///////////////////批量委托确认-----江南证券金仕达使用//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char JYSDM;                  //'0'-'9'交易所代码(参看柜台设置)
  char GDDM[GDDM_WIDTH];       //股东代码
  short GDGS;                  //股东代码个数
  char MMLB;                   //买卖类别
  char ZQDM[ZQDM_WIDTH];       //ZQDM  证券代码
  char WTJG[WTJG_WIDTH];       //WTJG  委托价格
  char WTSL[WTSL_WIDTH];       //WTSL  委托数量
  char ReqSrcInfo[QQYXX_WIDTH];// 请求源信息，如：网卡地址
}tagPLWTQR_Request;

typedef struct{
  tagBLOCK_HEAD HEAD;          //头信息
  char HTXH[HTXH_WIDTH];       //合同序号
  char JYSDM;                  //'0'-'9'交易所代码
  char GDDM[GDDM_WIDTH];       //股东代码
  char ZJZH[ZJZH_WIDTH];       //资金账号
  char HBDM;                   //'0'-'9'交易所代码
	SmallMoney WTJG;             //委托价格
  Money WTDJJE;                //委托冻结金额
  Money KYZJ;                  //资金本次可用数
  long GFFSS;                  //股份发生数
  long KYGF;                   //股份本次可用数
}tagPLWTQR_Result;

///////////////////资金内部转帐-----泰阳证券//////////////////
typedef struct
{
  tagBLOCK_HEAD HEAD;          //头信息
  char ZJZH[ZJZH_WIDTH];       //资金账号
  char HBDM;                   //货币代码
  char ZJFSS[ZJS_WIDTH];       //资金发生数
  char ReqSrcInfo[QQYXX_WIDTH];//请求源信息，如：网卡地址
}tagZJNBZZ_Request;

typedef struct{
  tagBLOCK_HEAD HEAD;          //头信息
  char  cqklsh[11];            //存取款流水号
  Money zjbcye;                //资金本次可用数
}tagZJNBZZ_Result;

/*****************************
  汉唐合作配售和集中国债业务
*****************************/
//////////////存折炒股合作配售开户--汉唐证券总部//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char FZDM[FZDM_WIDTH];       //银行代码
    char KHBSLX;                 //'0'-'9'交易所代码,'Z' 资金帐号 (参看柜台设置)
	char KHBS[KHBS_WIDTH];       //股东代码或资金帐号或磁卡号
}tagCZCGHZPSKH_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagCZCGHZPSKH_Result;

//////////////存折炒股合作配售销户--汉唐证券总部//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char FZDM[FZDM_WIDTH];       //银行代码
    char KHBSLX;                 // '0'-'9'交易所代码,'Z' 资金帐号 (参看柜台设置)
	char KHBS[KHBS_WIDTH];       //股东代码或资金帐号或磁卡号
	char BZXX[BZXX_WIDTH];       //备注信息
}tagCZCGHZPSXH_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagCZCGHZPSXH_Result;

//////////////存折炒股合作配售查询--汉唐证券总部//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char FZDM[FZDM_WIDTH];       //银行代码
    char KHBSLX;                 // '0'-'9'交易所代码,'Z' 资金帐号 (参看柜台设置)
	char KHBS[KHBS_WIDTH];       //股东代码或资金帐号或磁卡号
}tagCZCGHZPSCX_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
	char ZJZH[ZJZH_WIDTH];       //资金帐户
	char FZDM[FZDM_WIDTH];       //银行代码
	char YHZH[YHZH_WIDTH];       //银行帐户
	char CZZH[CZZH_WIDTH];       //存折帐户
	Money CZYE;                  //存折余额
	Money CZKYS;                 //存折可用数
	int  PGBZ;                   //配股标识
	char YYBDM[YYBDM_WIDTH];     //营业部代码
	char KHLB[3];                //客户类别
	int  XHZPSBZ;                //新合作配售标识
}tagCZCGHZPSCX_Result;

//////////////集中国债回购客户设置--汉唐证券总部//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char ZJZH[ZJZH_WIDTH];       //资金帐户
	char HBDM;                   //货币代码
    char XXBZ;                   //协议标志：设置协议'1'，解除协议'0'
}tagJZGZHGKHSZ_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagJZGZHGKHSZ_Result;

//////////////集中国债回购资金划拨--汉唐证券总部//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码
	char GDDM[GDDM_WIDTH];       //股东代码
	char HGDM[ZQDM_WIDTH];       //回购代码:797811
	char MMLB;                   //买卖类别:转入是B，转出是S
	char WTSL[WTSL_WIDTH];       //委托数量
	char FZDM[FZDM_WIDTH];       //银行代码
	char ZJLX;                   //资金流向
}tagJZGZHGZJZH_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagJZGZHGZJHB_Result;

//////////////集中国债回购收益查询--汉唐证券总部//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char QSRQ[DATETIME_WIDTH];   //起始日期
	char ZZRQ[DATETIME_WIDTH];   //终止日期
	char ZJZH[ZJZH_WIDTH];       //资金帐户
}tagJZGZHGSYCX_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
	char QSRQ[DATETIME_WIDTH];   //起始日期
	char ZJZH[ZJZH_WIDTH];       //资金帐户
	char HBDM;                   //货币代码
	char FZDM[FZDM_WIDTH];       //银行代码
	char YHZH[YHZH_WIDTH];       //银行帐户
	char CZZH[CZZH_WIDTH];       //存折帐户
	char ZJLX;                   //资金流向
	Money ZJFSS;                 //资金发生数
	Money HKJE;                  //现金发生数
	Money SYL;                   //结算价格
}tagJZGZHGSYCX_Result;

//////////////资金可取资料查询--湘财总部///////////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char ZJZH[ZJZH_WIDTH];       //资金帐户
	char HBDM;                   //货币代码
}tagKQZJCX_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
	Money XJKQJE;                //现金可取金额
	Money ZPKQJE;                //支票可取金额
}tagKQZJCX_Result;

/*****************************
          三板交易类
*****************************/
//////////////三板资金开户--光大证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char ZJZH[ZJZH_WIDTH];       //资金账号
    char HBDM;                   //货币代码
	char ZJXM[ZJXM_WIDTH];       //资金姓名
	char XMQC[XMQC_WIDTH];       //中文名 可为空
    char SFZH[SFZH_WIDTH];       //身份证号 
	char DHHM[21];               //电话号码 可为空 
    char YZBM[7];                //邮政编码 可为空
    char TXDZ[81];               //通讯地址 可为空
    char EMAIL[EMAIL_WIDTH];     //Email地址 可为空
	char BP[21];                 //BP机号码 可为空
    char KHLB[3];                //客户类别 
	                              //00-散户 01-中户 02-大户 03-机构户 04-自营户 15-发展银行炒股户 99-特殊户
	char JJRDM[5];               //经纪人代码 可为空
    char BZXX[BZXX_WIDTH];       //备注信息 可为空
}tagSBZJKH_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagSBZJKH_Result;

//////////////三板代理人设置--光大证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char ZJZH[ZJZH_WIDTH];       //资金账号
    char HBDM;                   //货币代码
	char DLRXM[ZJXM_WIDTH];      //代理人资金姓名
    char DLRSFZH[SFZH_WIDTH];    //代理人身份证号 
	char DLRDHHM[21];            //代理人电话号码 可为空 
    char DLRTXDZ[81];            //代理人通讯地址 可为空
    int  DLRQX;                  //代理人权限
	char DLRJSRQ[DATETIME_WIDTH];//代理人结束日期(格式为:yyyymmdd)
    char BZXX[BZXX_WIDTH];       //备注信息 可为空
}tagSBDLRSZ_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagSBDLRSZ_Result;

//////////////三板股东开户--光大证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码
	char GDDM[GDDM_WIDTH];       //股东代码
	char GDXM[GDXM_WIDTH];       //股东姓名
	char XMQC[XMQC_WIDTH];       //中文名 可为空
	char SFZH[SFZH_WIDTH];       //身份证号 
	char ZJZH[ZJZH_WIDTH];       //资金账号
	char BYXX[BZXX_WIDTH];       //备注信息 可为空
    char BZXX[BZXX_WIDTH];       //备注信息 可为空
}tagSBGDKH_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagSBGDKH_Result;

//////////////三板资金销户--光大证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char ZJZH[ZJZH_WIDTH];       //资金账号
    char HBDM;                   //货币代码
    char BZXX[BZXX_WIDTH];       //备注信息 可为空
}tagSBZJXH_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagSBZJXH_Result;

//////////////三板股东销户--光大证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码
	char GDDM[GDDM_WIDTH];       //股东代码
	char ZJZH[ZJZH_WIDTH];       //资金账号
    char BZXX[BZXX_WIDTH];       //备注信息 可为空
}tagSBGDXH_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagSBGDXH_Result;

//////////////三板资金基本资料修改--光大证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char ZJZH[ZJZH_WIDTH];       //资金账号
	char ZJXM[ZJXM_WIDTH];       //资金姓名
	char XMQC[XMQC_WIDTH];       //中文名 可为空
    char SFZH[SFZH_WIDTH];       //身份证号 
	char DHHM[21];               //电话号码 可为空 
    char YZBM[7];                //邮政编码 可为空
    char TXDZ[81];               //通讯地址 可为空
    char EMAIL[EMAIL_WIDTH];     //Email地址 可为空
	char BP[21];                 //BP机号码 可为空
    char KHLB[3];                //客户类别 
	                              //00-散户 01-中户 02-大户 03-机构户 04-自营户 15-发展银行炒股户 99-特殊户
	char JJRDM[5];               //经纪人代码 可为空
    char BZXX[BZXX_WIDTH];       //备注信息 可为空
}tagSBZJXG_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagSBZJXG_Result;

//////////////三板股东基本资料修改--光大证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码
	char GDDM[GDDM_WIDTH];       //股东代码
	char GDXM[GDXM_WIDTH];       //股东姓名
	char XMQC[XMQC_WIDTH];       //中文名 可为空
	char SFZH[SFZH_WIDTH];       //身份证号 
	char BYXX[BZXX_WIDTH];       //备注信息 可为空
    char BZXX[BZXX_WIDTH];       //备注信息 可为空
}tagSBGDXG_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagSBGDXG_Result;

//////////////三板股东所属营业部设置--光大证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码
	char GDDM[GDDM_WIDTH];       //股东代码
	char ZJMM[JYMM_WIDTH];       //资金密码
	char FZDM[FZDM_WIDTH];       //营业部代码
	char YHMM[YHMM_WIDTH];       //营业部密码 可为空
	char YHZH[YHZH_WIDTH];       //主板资金帐号
	char CZZH[CZZH_WIDTH];       //存折帐号（营业部帐号的子帐号) 可为空
    char BZXX[BZXX_WIDTH];       //备注信息 可为空
}tagSBGDYYBSZ_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
	char    CLJG;                //处理结果  '0'-成功, '1'-失败
}tagSBGDYYBSZ_Result;

//////////////三板股东所属营业部取消--光大证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char KHBSLX;                 // '0'-'9'交易所代码(参看柜台设置)
                               // 'Z' 资金帐号
                               // 'C' 磁卡号
    char KHBS[CKBH_WIDTH];       //KHBS  股东代码或资金帐号或磁卡号
	char ZJMM[JYMM_WIDTH];       //资金密码
	char FZDM[FZDM_WIDTH];       //营业部代码
	char YHMM[YHMM_WIDTH];       //营业部密码 可为空
    char BZXX[BZXX_WIDTH];       //备注信息 可为空
}tagSBGDYYBQX_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
	char    CLJG;                //处理结果  '0'-成功, '1'-失败
}tagSBGDYYBQX_Result;

//////////////转帐银行查询--联合证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char ZJZH[ZJZH_WIDTH];       //资金账号
}tagZZYHCX_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
    char HBDM;                   //货币代码
	char YHDM[YHDM_WIDTH];       //银行代码
	char YHMC[YHMC_WIDTH];       //银行名称
	char FQFX;                   //'A' 双方发起 'Y' 银行发起 'Q' 券商发起
	short YHMMCD;                //银行密码长度
	short ZRMM;                  //转入需要密码  0不需要密码 1 需要取款密码 2 需要银行密码 3 需要取款/银行密码
	short ZCMM;                  //转出需要密码 同上
	short YHGM;                  //可修改银行密码 -1不能修改 0不需要密码 1 需要取款密码 2 需要银行密码 3 需要取款/银行密码
	short YHYE;                  //查银行余额     -1不能查   0不需要密码 1 需要取款密码 2 需要银行密码 3 需要取款/银行密码
	short ZKJEXSCD;              //转款金额小数点位数
	short TIMEOUT;               //等待延时
}tagZZYHCX_Result;

//////////////转帐明细查询--联合证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char QSRQ[DATETIME_WIDTH];   //起始日期(格式为:yyyymmdd)
    char ZZRQ[DATETIME_WIDTH];   //终止日期(格式为:yyyymmdd)
	char ZJZH[ZJZH_WIDTH];       //资金账号
	char HBDM;                   //货币代码
	char YHDM[YHDM_WIDTH];       //银行代码
	char YHZH[YHZH_WIDTH];       //银行帐号
	char CQKLSH[HTXH_WIDTH];     //存取款流水号
	char CQLB[CQLB_WIDTH];       //存取类别
	                             //CR--转入  QC--取出  KH--开户  XH--销户
	                             //CZ--冲正  YM--修改银行密码  YE--查询银行余额
	                             //可组合使用，用逗号分开，比如CR,QC
	char CLJG;                   //处理结果 '' 未处理 '0' 合法 '1' 非法 '2' 主动冲正,'A' 查全部
	char KHLB[30];               //客户类别 00-散户 01-中户 02-大户 03-机构户 04-自营户 15-发展银行炒股户 99-特殊户
	                             //可组合使用，用逗号分开，比如00,01,02
	char YYBDM[50];              //营业部代码
	                             //可组合使用，用逗号分开，比如0000,0001
#ifdef  _KD3X
	char YYBTJBZ;                //营业部统计标志 0-按客户营业部统计 1-按柜员营业部查询
#endif
}tagZZMXCX_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
#ifdef _KD3X
	char CX_JLSH[33];             //流水号
#endif
	char CJSJ[DATETIME_WIDTH];   //成交时间
	char HTXH[HTXH_WIDTH];       //合同序号
	char ZJZH[ZJZH_WIDTH];       //资金帐户
	char ZJXM[ZJXM_WIDTH];       //资金姓名
	char HBDM;                   //货币代码
	char HBMC[HBMC_WIDTH];       //货币名称
	char YHDM[YHDM_WIDTH];       //银行代码
	char YHMC[YHMC_WIDTH];       //银行名称
	char CQLB[3];                //存取类别
	char CQLBSM[CQLBSM_WIDTH];  //存取类别说明
	Money JFFS;                  //转入发生金额
	Money DFFS;                  //转出发生金额
	char FSBZ;                   //发送标志
	char FSBZSM[FSBZSM_WIDTH];   //发送标志说明
	char CLJG;                   //处理结果
	char CLJGMC[CLJGMC_WIDTH];   //处理结果说明
	char FSSJ[DATETIME_WIDTH];   //发生时间
	char YHZH[YHDM_WIDTH];       //银行帐号
	char FSRQ[DATETIME_WIDTH];   //发生日期
	char GYDM[GYDM_WIDTH];       //柜员代码
	char DYCQKLSH[HTXH_WIDTH];   //冲帐对应的存取款流水号
	char YHLSH[YHLSH_WIDTH];     //对应的银行流水号
	char DEVICE[DEVICE_WIDTH];   //网卡地址或银行终端设备标识
	char CZFS[3];                //操作方式
	char CZFSSM[CZFSSM_WIDTH];   //操作方式说明
	char BZXX[BZXX_WIDTH];       //备注信息
}tagZZMXCX_Result;


//////////////存折抄股设置合作配售时划拨金额--广东证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码
	char GDDM[GDDM_WIDTH];       //股东代码
	int  PGBZ;                   //32合作配售,0是取消合作配售
	char BZXX[BZXX_WIDTH];       //备注信息
}tagCZCGHZHBZJ_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
}tagCZCGHZHBZJ_Result;


//////////////存折抄股根据银行帐户查股东信息--东莞证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码,为空查全部
	char FZDM[FZDM_WIDTH];       //银行代码,为空查全部
	char YHZH[YHZH_WIDTH];       //银行帐号
}tagCZCGYHCGD_Request;

typedef struct{
	tagBLOCK_HEAD HEAD;          //头信息
	char ZJZH[ZJZH_WIDTH];       //资金帐号
    char JYSDM;                  //交易所代码
	char GDDM[GDDM_WIDTH];       //股东代码
	char FZDM[FZDM_WIDTH];       //银行代码
	char YHZH[YHZH_WIDTH];       //银行帐号
	char CZZH[CZZH_WIDTH];       //存折帐号  
}tagCZCGYHCGD_Result;


//////////////未到期回购查询--华林证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char QSRQ[DATETIME_WIDTH];   //开始日期
	char ZZRQ[DATETIME_WIDTH];   //结束日期
	char JYSDM[10];              //交易所代码，可以复选
	                             //比如深A是0、沪A是1，若要查两个市场则设置为01
    char GDDM[GDDM_WIDTH];       //股东代码，可为空
	char ZJZH[ZJZH_WIDTH];       //资金账号，可为空
	char ZQDM[ZQDM_WIDTH];       //证券代码，可为空
	char BZQBZ;                  //标准券类别 ‘0’ － 国债标准券，‘1’－企债标准券，‘2’－国债+企债
	char MMLB;                   //查询方式：全部(0)，买(B)，卖(S)(字母必须大写)
	char RQLX;                   //查询日期类型，‘W’－按委托日期查、‘G’－‘按购回日期查’(字母必须大写) 	
}tagWDQHGCX_Request;

typedef struct{
    tagBLOCK_HEAD HEAD;          //头信息
    char CJRQ[DATETIME_WIDTH];   //委托日期
	char ZJZH[ZJZH_WIDTH];       //资金账号
	char JYSDM;                  //交易所代码
    char GDDM[GDDM_WIDTH];       //股东代码
	char ZQDM[ZQDM_WIDTH];       //证券代码
	long CJSL;                   //成交数量
	SmallMoney CJJG;             //成交价格
	Money ZJFSS;                 //清算金额( > 0买入融资 <0卖出融券)
	char HTXH[HTXH_WIDTH];       //合同序号
	char XWDM[7];                //席位代码
	Money GHJE;                  //购回金额
	char GHRQ[DATETIME_WIDTH];   //购回日期
}tagWDQHGCX_Result;

/*****************************
		ETF业务
*****************************/
//////////////ETF网下现金认购--银河证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码,送上海A的市场代码
	char ETFDM[ZQDM_WIDTH];      //ETF认购代码
	char ZJZH[ZJZH_WIDTH];       //资金帐户
	char GDDM[GDDM_WIDTH];       //股东代码,送上海A的股东代码
	char WTJG[WTJG_WIDTH];       //WTJG  认购价格,先通过ETFDMJY取得价格标志,若是定价则取得ZRSP
	char WTSL[WTSL_WIDTH];       //WTSL  认购数量
}tagETFXJRG_Request;

typedef struct{
	tagBLOCK_HEAD HEAD;          //头信息
	Money ZJDJS;                 //资金冻结数  
	char ZJZH[ZJZH_WIDTH];       //资金帐号
	Money ZJBCKYS;               //资金本次可用数
	long LSH;                    //流水号
}tagETFXJRG_Result;

//////////////ETF网下股票认购--银河证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码,送上海A的市场代码
	char ZJZH[ZJZH_WIDTH];       //资金帐户
	char GDDM[GDDM_WIDTH];       //股东代码,送上海A的股东代码
	char ETFDM[ZQDM_WIDTH];      //ETF认购代码
	char ZQDM[ZQDM_WIDTH];       //成份股代码
	char WTSL[WTSL_WIDTH];       //WTSL  认购数量
}tagETFGPRG_Request;

typedef struct{
	tagBLOCK_HEAD HEAD;          //头信息
	Money GFDJS;                 //股份冻结数  
	char ZJZH[ZJZH_WIDTH];       //资金帐号
	Money GFBCKYS;               //股份本次可用数
	long  LSH;                   //流水号
}tagETFGPRG_Result;

//////////////ETF网下认购撤单--银河证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	long LSH;                    //流水号
	char GDDM[GDDM_WIDTH];       //股东代码,送上海A的股东代码
}tagETFRGCD_Request;

typedef struct{
	tagBLOCK_HEAD HEAD;          //头信息
}tagETFRGCD_Result;

//////////////ETF网下认购流水查询--银河证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码,送上海A的市场代码,可送空
	char ETFDM[ZQDM_WIDTH];      //ETF认购代码,可送空
	char ZQDM[ZQDM_WIDTH];       //成份股代码,可送空
	char ZJZH[ZJZH_WIDTH];       //资金帐户,可送空
	char GDDM[GDDM_WIDTH];       //股东代码,送上海A的股东代码,可送空	
	char YWLB;                   //业务类别 ‘0’ 现金认购， '1' 股票认购， '' 所有现金认购股票认购数据
	char CXFW;                   //查询范围 '1' 只查当天的数据(用于撤单)， 其他值查询所有数据
}tagETFRGCX_Request;

typedef struct{
	tagBLOCK_HEAD HEAD;          //头信息
	long LSH;                    //流水号
	char FSRQ[DATETIME_WIDTH];   //发生日期(格式为:yyyymmdd)
    char JYSDM;                  //交易所代码
	char ETFDM[ZQDM_WIDTH];      //ETF认购代码
	char ZQDM[ZQDM_WIDTH];       //成份股代码
	char GDDM[GDDM_WIDTH];       //股东代码
	char YWLB;                   //业务类别,‘0’ 网下现金认购 ‘1’网下股票认购  '2' 预估金额
	Money ZJFSS;                 //资金发生数
	Money GFDJS;                 //股份冻结数 
	char CDBZ;                   //撤单标志,‘0’ 未撤单 ‘1’已经撤单
	char CLBZ;                   //转换标志,缺省填'0',‘3’网下已经转网上报盘 ‘4’股份认购数据份额已经过户
}tagETFRGCX_Result;

//////////////取ETF可申购赎回数量--银河证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码,送上海A的市场代码
	char GDDM[GDDM_WIDTH];       //股东代码,送上海A的股东代码
	char ETFDM[ZQDM_WIDTH];      //ETF申购赎回代码
	char MMLB;                   //买卖类别,B-申购,S-赎回
}tagETFKMSL_Request;

typedef struct{
	tagBLOCK_HEAD HEAD;          //头信息
	Money KSGSHSL;               //可申购赎回数量
}tagETFKMSL_Result;

//////////////ETF申购赎回委托业务--银河证券//////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          //头信息
	char JYSDM;                  //交易所代码,送上海A的市场代码
	char GDDM[GDDM_WIDTH];       //股东代码,送上海A的股东代码
	char ETFDM[ZQDM_WIDTH];      //ETF申购赎回代码
	char MMLB;                   //买卖类别,B-申购,S-赎回
	char WTSL[WTSL_WIDTH];       //WTSL  委托数量
}tagETFSGSH_Request;

typedef struct{
	tagBLOCK_HEAD HEAD;          //头信息
	CHAR HTXH[HTXH_WIDTH];       //合同序号
	char ZJZH[ZJZH_WIDTH];       //资金帐号
	char HBDM;                   //货币代码
	Money WTJE;                  //委托金额
	Money WTDJJE;                //委托冻结金额
	Money ZJBCKYS;               //资金本次可用数
	Money GFFSS;                 //股份发生数量 
	Money GFBCKYS;               //股份本次可用数
}tagETFSGSH_Result;

///////////////////ETF代码校验--银河证券//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          // 头信息
	char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置)
	char GDDM[GDDM_WIDTH];       // GDDM  股东代码
	char ZQDM[ZQDM_WIDTH];       // ZQDM  ETF代码
}tagETFDMJY_Request;

typedef struct{
	tagBLOCK_HEAD HEAD;          // 头信息
	char JYSDM;                  //'0'-'9'交易所代码(参看柜台设置)
	char JYSJC[JYSJC_WIDTH];     //交易所名称(参看柜台设置)
	short JW;                    //价位(以厘为基数 1000为1元)
	char ZQDM[ZQDM_WIDTH];       //证券代码
	char ZQMC[ZQMC_WIDTH];       //证券名称
	short ZQLB;                  //证券类别 0股票 1国债 2企业债券 3回购 4基金
	//         5投资基金 6权证 9转换债券 10实物国债
	//         11实物企债 12特殊证券
	char JYLX[5];                //交易类型 'PT'正常交易 'SG'申购 'PS' 配售 'PH'配号 'PP' 配售配号 'JK' 缴款
	char TPBZ;                   //停牌标志  'T'-停牌, 'F'-正常
	SmallMoney ZRSP;             //昨日收盘
	char JGBZ;                   //价格标志  '0'-浮动价 '1'--定价
	char YJLX[30];               //国债净价交易中的国债利息额	
}tagETFDMJY_Result;

///////////////////取ETF申购赎回清单文件的配置信息--银河证券//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          // 头信息
	char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置) 送空查全部
	char ETFDM[ZQDM_WIDTH];      //ETF申购赎回代码 送空查全部
}tagETFSGSHPZ_Request;

typedef struct{
	tagBLOCK_HEAD HEAD;          // 头信息
	char  JYSDM;                 //'0'-'9'交易所代码(参看柜台设置)
	char  ETFDM[ZQDM_WIDTH];     //指数基金的一级市场代码 如'510051'等 fundid1 
	long  SGSHZXFE;              //申购赎回最小份额    CreationRedemptionUnit
	SmallMoney ZDXJTDBL;         //最大现金替代比例        maxCashratio  
	char  SFFBIOPV;              //是否发布IOPV值        Publish
	char  SGSHYXZT;              //申购赎回允许状态 CreationRedemption 
	                             //'1'表示允许申购和赎回，'2'表示允许申购、不允许赎回，'3'表示不允许申购、允许赎回
	int   GPLJLS;                //股票篮记录数     Recordnum 
	char  TRRQ[DATETIME_WIDTH];  //T日日期         TradingDay 
	char  TJYRRQ[DATETIME_WIDTH];//T-1日日期       PreTradingDay
	Money YGXJCE;                //预估现金差额(T日冻结资金使用) Estimatecashcomponet 
	Money TJYRXJCE;              //T-1日现金差额        CashComponent 
	Money TJYRSGSHJZ;            //T-1日申购赎回基准单位净值   NAVperCU
	SmallMoney TJYRJJDWJZ;       //T-1日每基金份额单位净值   NAV: 小数点精确到后5位
}tagETFSGSHPZ_Result;

///////////////////取ETF申购赎回股票蓝信息--银河证券//////////////////
typedef struct
{
	tagBLOCK_HEAD HEAD;          // 头信息
	char JYSDM;                  // '0'-'9'交易所代码(参看柜台设置) 送空查全部
	char ETFDM[ZQDM_WIDTH];      //ETF申购赎回代码 送空查全部
}tagETFSGSHQD_Request;

typedef struct{
	tagBLOCK_HEAD HEAD;          // 头信息
	char  JYSDM;                 //'0'-'9'交易所代码(参看柜台设置)
	char  ZQDM[ZQDM_WIDTH];      //证券代码 
	char  ZQMC[ZQMC_WIDTH];      //证券名称
	long  GFSL;                  //股份数量
	SmallMoney YJBL;             //溢价比例: 小数点精确到后5位
	char  XJTDBZ;                //现金替代标志 '0' 不可现金替代, '1' 不足部分可现金替代, '2' 强制现金替代
	Money XJTDJE;                //现金替代金额   
}tagETFSGSHQD_Result;


////////////////////////////////////////////////////////////////////////////////
typedef union
{
  tagBLOCK_HEAD head;
  tagJYSXX_Request jysxx;
  tagHBXX_Request hbxx;
  tagYHXX_Request yhxx;
  tagZQXX_Request zqxx;
  tagPLCDCX_Request plcdcx;
  tagKHJY_Request khjy;
  tagZJZL_Request zjzl;
  tagKHCX_Request khcx;
  tagDMJY_Request dmjy;
  tagKMSL_Request kmsl;
  tagWTQR_Request wtqr;
  tagWTCD_Request wtcd;
  tagXGMM_Request xgmm;
  tagXGZJMM_Request xgzjmm;
  tagZJCX_Request zjcx;
  tagZLCX_Request zlcx;
  tagXXZLCX_Request xxzlcx;
  tagZLXG_Request zlxg;
  tagZHYZ_Request zhyz;
  tagGFCX_Request gfcx;
  tagGZHGBZQCX_Request gzhgbzqcx;
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
  tagHBCXLSH_Request hbcxlsh;
  tagHBCD_Request hbcd;
  tagQZZJYE_Request qzzjye;
  tagQZQSXX_Request qzqsxx;
  tagQYZJHB_Request qyzjhb;
  tagYKJS_Request ykjs;
  tagXGCB_Request xgcb;
  tagPLWTXX_Request plwtxx;
  tagSFMX_Request sfmx;
  tagMMJY_Request mmjy;
  tagYYB_Request  yyb;
  tagAGAIN_Request again;
  tagCZCGWTQR_Request czcgwtqr;
  tagCZCGWTCD_Request czcgwtcd;
  tagCZCGCXJKK_Request czcgcxjkk;
  tagCZCGCXGDXX_Request czcgcxgdxx;
  tagCZCGSFYZ_Request   czcgsfyz;
  tagCZCGYHZJCX_Request czcgyhzjcx;
  tagCZCGKTYHCX_Request czcgktyhcx; 
  tagSZZDPS_Request szzdps;
  tagCZCG_SZHZPS_Request czcgszhzps;
  tagCZCG_HZSGHBZJ_Request czcghzsghbzj;
  tagCZCG_HZHGHBZJ_Request czcghzhghbzj;
  tagCZCG_SZHZHGSG_Request czcgszhzhgsg;
  tagCZCG_JNFDJZJ_Request czcgjnfdjzj;
  tagCZCG_JNFSZHFBZ_Request czcgjnfszhfbz;
  tagYCDJZJ_Request ycdjzj;  
  tagYCJDZJ_Request ycjdzj;  
  tagCZCGKMSL_Request czcgkmsl;
  tagYWTQR_Request ywtqr;
  tagYWTCD_Request ywtcd;
  tagYWTFS_Request ywtfs;
  tagYWTCX_Request ywtcx;
  tagSSCJCX_Request sscjcx;
  tagSSCDCX_Request sscdcx;
  tagZQDMCX_Request zqdmcx;
  tagPLWTQR_Request plwtqr;
  tagZJYECX_Request zjyecx;
  tagZJLSCX_Request zjlscx;
  tagKHZLCX_Request khzlcx;
  tagZJNBZZ_Request zjnbzz;
  tagMCGFCX_Request mcgfcx;
  tagZQZGHS_Request zqzghs;
  tagHZHGSGCX_Request hzhgsgcx;
  tagCZCGHZPSKH_Request czcghzpskh;
  tagCZCGHZPSXH_Request czcghzpsxh;
  tagCZCGHZPSCX_Request czcghzpscx;
  tagJZGZHGKHSZ_Request jzgzhgkhsz;
  tagJZGZHGZJZH_Request jzgzhgzjhb;
  tagJZGZHGSYCX_Request jzgzhgsycx;
  tagKQZJCX_Request kqzjcx;
  tagSBZJKH_Request sbzjkh;
  tagSBDLRSZ_Request sbdlrsz;
  tagSBGDKH_Request sbgdkh;
  tagSBZJXH_Request sbzjxh;
  tagSBGDXH_Request sbgdxh;
  tagSBZJXG_Request sbzjxg;
  tagSBGDXG_Request sbgdxg;
  tagSBGDYYBSZ_Request sbgdyybsz;
  tagSBGDYYBQX_Request sbgdyybqx;
  tagZZYHCX_Request zzyhcx;
  tagZZMXCX_Request zzmxcx;
  tagCZCGHZHBZJ_Request czcghzhbzj;
  tagCZCGYHCGD_Request czcgyhcgd;
  tagWDQHGCX_Request wdqhgcx;
  tagETFXJRG_Request etfxjrg;
  tagETFGPRG_Request etfgprg;
  tagETFRGCD_Request etfrgcd;
  tagETFRGCX_Request etfrgcx;
  tagETFKMSL_Request etfkmsl;
  tagETFSGSH_Request etfsgsh;
  tagETFDMJY_Request etfdmjy;
  tagETFSGSHPZ_Request etfsgshpz;
  tagETFSGSHQD_Request etfsgshqd;
}tagREQUEST;

typedef union
{
  tagBLOCK_HEAD head;          //头信息
  tagJYSXX_Result jysxx;
  tagHBXX_Result hbxx;
  tagYHXX_Result yhxx;
  tagZQXX_Result zqxx;
  tagPLCDCX_Result plcdcx;
  tagKHJY_Result khjy;
  tagZJZL_Result zjzl;
  tagKHCX_Result khcx;
  tagDMJY_Result dmjy;
  tagKMSL_Result kmsl;
  tagWTQR_Result wtqr;
  tagWTCD_Result wtcd;
  tagXGMM_Result xgmm;
  tagXGZJMM_Result xgzjmm;
  tagZJCX_Result zjcx;
  tagZLCX_Result zlcx;
  tagXXZLCX_Result xxzlcx;
  tagZLXG_Result zlxg;
  tagZHYZ_Result zhyz;
  tagGFCX_Result gfcx;
  tagGZHGBZQCX_Result gzhgbzqcx;
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
  tagHBCXLSH_Result hbcxlsh;
  tagHBCD_Result hbcd;
  tagQZZJYE_Result qzzjye;
  tagQZQSXX_Result qzqsxx;
  tagQYZJHB_Result qyzjhb;
  tagYKJS_Result ykjs;
  tagXGCB_Result xgcb;
  tagPLWTXX_Result plwtxx;
  tagSFMX_Result sfmx;
  tagMMJY_Result mmjy;
  tagYYB_Result  yyb;
  tagErrMsg_Result ErrMsg;
  tagCZCGWTQR_Result czcgwtqr;
  tagCZCGWTCD_Result czcgwtcd;
  tagCZCGCXJKK_Result czcgcxjkk;
  tagCZCGCXGDXX_Result czcgcxgdxx;
  tagCZCGSFYZ_Result czcgsfyz;
  tagCZCGYHZJCX_Result czcgyhzjcx;
  tagCZCGKTYHCX_Result czcgktyhcx;  
  tagSZZDPS_Result szzdps;  
  tagCZCG_SZHZPS_Result czcgszhzps;
  tagCZCG_HZSGHBZJ_Result czcghzsghbzj;
  tagCZCG_HZHGHBZJ_Result czcghzhghbzj;
  tagCZCG_SZHZHGSG_Result czcgszhzhgsg;
  tagCZCG_JNFDJZJ_Result czcgjnfdjzj;
  tagCZCG_JNFSZHFBZ_Result czcgjnfszhfbz;
  tagYCDJZJ_Result ycdjzj;  
  tagYCJDZJ_Result ycjdzj;  
  tagCZCGKMSL_Result czcgkmsl;
  tagYWTQR_Result ywtqr;
  tagYWTCD_Result ywtcd;
  tagYWTFS_Result ywtfs;
  tagYWTCX_Result ywtcx;
  tagSSCJCX_Result sscjcx;	
  tagSSCDCX_Result sscdcx;
  tagZQDMCX_Result zqdmcx;
  tagPLWTQR_Result plwtqr;
  tagZJYECX_Result zjyecx;
  tagZJLSCX_Result zjlscx;
  tagKHZLCX_Result khzlcx;
  tagZJNBZZ_Result zjnbzz;
  tagMCGFCX_Result mcgfcx;
  tagZQZGHS_Result zqzghs;
  tagHZHGSGCX_Result hzhgsgcx;
  tagCZCGHZPSKH_Result czcghzpskh;
  tagCZCGHZPSXH_Result czcghzpsxh;
  tagCZCGHZPSCX_Result czcghzpscx;
  tagJZGZHGKHSZ_Result jzgzhgkhsz;
  tagJZGZHGZJHB_Result jzgzhgzjhb;
  tagJZGZHGSYCX_Result jzgzhgsycx;
  tagKQZJCX_Result kqzjcx;
  tagSBZJKH_Result sbzjkh;
  tagSBDLRSZ_Result sbdlrsz;
  tagSBGDKH_Result sbgdkh;
  tagSBZJXH_Result sbzjxh;
  tagSBGDXH_Result sbgdxh;
  tagSBZJXG_Result sbzjxg;
  tagSBGDXG_Result sbgdxg;
  tagSBGDYYBSZ_Result sbgdyybsz;
  tagSBGDYYBQX_Result sbgdyybqx;
  tagZZYHCX_Result zzyhcx;
  tagZZMXCX_Result zzmxcx;
  tagCZCGHZHBZJ_Result czcghzhbzj;
  tagCZCGYHCGD_Result czcgyhcgd;
  tagWDQHGCX_Result wdqhgcx;
  tagETFXJRG_Result etfxjrg;
  tagETFGPRG_Result etfgprg;
  tagETFRGCD_Result etfrgcd;
  tagETFRGCX_Result etfrgcx;
  tagETFKMSL_Result etfkmsl;
  tagETFSGSH_Result etfsgsh;
  tagETFDMJY_Result etfdmjy;
  tagETFSGSHPZ_Result etfsgshpz;
  tagETFSGSHQD_Result etfsgshqd;
}tagRESULT;

BOOL WINAPI KDAPI_InitSystem(long _TimeOut);
BOOL WINAPI KDAPI_InitSystem_MT(long _TimeOut, int nConnections);
/*------------------------------
说明
  初始化DLL
  KDAPI_InitSystem	   初始化单个连接(单线程)
  KDAPI_InitSystem_MT  初始化多个连接(多线程)
输入
  _TimeOut      响应时间
  nConnectionNo	连接号(连接数,从1开始,应小于20)
输出
   TRUE 成功
   其他 失败
-------------------------------*/
int WINAPI KDAPI_Connect(tagNETWORKADD serverAddress[3],char *GYDM,char *GYMM);
int WINAPI KDAPI_Connect_MT(tagNETWORKADD serverAddress[3],char *GYDM,char *GYMM, int nConnectionNo);
/*------------------------------
说明
  连接中间件
  KDAPI_Connect	   单线程时调用
  KDAPI_Connect_MT 多线程时调用
输入
  serverAddress    中间件地址序列
  GYDM             柜员代码
  GYMM             柜员密码
  nConnectionNo	   连接号(0--连接数-1)
输出
   0  成功
   -1 没有调用InitSystem
   -2 中间件连接错误
   -3 OEM未授权
   -4 请求失败（应当取回一个包），数据发送错误
   -7 调用reqOEM请求出现其他错误
   -10 nConnectionNo 不合法
-------------------------------*/
int WINAPI KDAPI_Disconnect();
int WINAPI KDAPI_Disconnect_MT(int nConnectionNo);
/*------------------------------
说明
  断开中间件连接
  KDAPI_Disconnect	  单线程时调用
  KDAPI_Disconnect_MT 多线程时调用
输入
  nConnectionNo	连接号(0--连接数-1)
输出
   0  成功
   -1 没有调用InitSystem
   -10 nConnectionNo 不合法
-------------------------------*/
int WINAPI KDAPI_GetConnect();
int WINAPI KDAPI_GetConnect_MT(int nConnectionNo);
/*------------------------------
说明
  获取中间件连接状态
  KDAPI_GetConnect	  单线程时调用
  KDAPI_GetConnect_MT 多线程时调用
输入
  nConnectionNo	连接号(0--连接数-1)
输出
  0    连接状态
  -10  nConnectionNo 不合法
  其他 断开状态
-------------------------------*/
int WINAPI KDAPI_Request(tagREQUEST &request);
int WINAPI KDAPI_Request_MT(tagREQUEST &request, int nConnectionNo, unsigned int *sClientSocket=NULL);
/*------------------------------
说明
  向中间件发请求
  KDAPI_Request    单线程时调用
  KDAPI_Request_MT 多线程时调用
输入
   request        请求包
   nConnectionNo  连接号(0--连接数-1)
   sClientSocket  返回的线程序号
输出
   -1 没有调用InitSystem
   -2 中间件连接错误 (未调用Connect)
   -3 OEM未授权
   -4 请求失败（应当取回一个包,该包为错误信息包或没有设置第三方OEM）
   -5 中间件连接错误(所有连接已断)
   -6 发送数据错误
   -10 nConnectionNo 不合法
   其他 成功，该笔请求返回应答记录数
-------------------------------*/

int WINAPI KDAPI_Request_fzdm(tagREQUEST &request,char *yfzdm,char *mdfzdm);
int WINAPI KDAPI_Request_fzdm_MT(tagREQUEST &request,char *yfzdm,char *mdfzdm, int nConnectionNo, unsigned int *sClientSocket=NULL);
/*------------------------------
说明
  向中间件发请求（用于通存通兑）
  KDAPI_Request_fzdm     单线程时调用（用于通存通兑）
  KDAPI_Request_fzdm_MT  多线程时调用（用于通存通兑）
输入
   request        请求包
   yfzdm          源分支代码（4位）'____'为本地
   mdfzdm         目的分支代码（4位）'____'为本地
   nConnectionNo  连接号(0--连接数-1)
   sClientSocket  返回的线程序号
输出
   -1 没有调用InitSystem
   -2 中间件连接错误 (未调用Connect)
   -3 OEM未授权
   -4 请求失败（应当取回一个包,该包为错误信息包或没有设置第三方OEM）
   -5 中间件连接错误(所有连接已断)
   -6 发送数据错误
   -10 nConnectionNo 不合法
   其他 成功，该笔请求返回应答记录数
-------------------------------*/

int WINAPI KDAPI_Answer(tagRESULT &result);
int WINAPI KDAPI_Answer_MT(tagRESULT &result, int nConnectionNo);
/*------------------------------
说明
  取请求结果
  KDAPI_Answer     单线程时调用
  KDAPI_Answer_MT  多线程时调用
输入
   result           应答包
   nConnectionNo	连接号(0--连接数-1)
输出
   -1 没有调用InitSystem
   -2 中间件连接错误
   -3 OEM未授权
   -4 请求失败（应当取回一个包,该包为错误信息包或没有设置第三方OEM）
   -5 中间件连接错误(所有连接已断)
   -6 发送数据错误
   -10 nConnectionNo 不合法
   0    结果已经取完
   其他 成功，该笔请求返回字节数
-------------------------------*/

char * WINAPI KDAPI_MoneyToStr( Money m);
char * WINAPI KDAPI_SmallMoneyToStr( SmallMoney m);
char * WINAPI KDAPI_SmallMoneyToStr5( SmallMoney m);
/*------------------------------
说明
  类型转换,只能用于单线程
  KDAPI_MoneyToStr       单线程时调用
  KDAPI_SmallMoneyToStr  单线程时调用
  KDAPI_SmallMoneyToStr5 单线程时调用:小数点精确到后5位
-------------------------------*/

bool WINAPI KDAPI_MoneyToStr_MT(Money m, char *szStr);
bool WINAPI KDAPI_SmallMoneyToStr_MT(SmallMoney m, char *szStr);
bool WINAPI KDAPI_SmallMoneyToStr5_MT(SmallMoney m, char *szStr);
/*------------------------------
说明
  取请求结果----第三方不能使用
  KDAPI_MoneyToStr_MT       多线程时调用
  KDAPI_SmallMoneyToStr_MT  多线程时调用
  KDAPI_SmallMoneyToStr5_MT 多线程时调用: 小数点精确到后5位
-------------------------------*/
void WINAPI KDAPI_StrToMoney(char *s,Money *x1);
void WINAPI KDAPI_StrToSmallMoney(char *s,SmallMoney *x1);
void WINAPI KDAPI_StrToSmallMoney5(char *s,SmallMoney *x1);
/*------------------------------
说明
  类型转换,只能用于单线程
  KDAPI_StrToMoney       单线程时调用
  KDAPI_StrToSmallMoney  单线程时调用
  KDAPI_StrToSmallMoney5 单线程时调用: 小数点精确到后5位
-------------------------------*/

bool WINAPI KDAPI_OEMInit(char *szDEF_API_NAME,char * szDEF_OEM_NAME,int iDEF_OEM_PIN);
bool WINAPI KDAPI_SetSecretLevel(int nLevel);
/*------------------------------
说明
		金证内部专用,第三方请勿使用
------------------------------*/

#endif
