#ifndef UTrdStructH
#define UTrdStructH

// Attention
// Use Interger-Sized enums to compile this header

#define CODE_LEN    30        // 代码长度
#define SEQ_LEN     100       // 序号长度
#define ACC_LEN     20        // 帐号长度
#define PWD_LEN     20        // 密码长度
#define MAX_TEXT    256

#pragma pack(1)
// 时间    HHMMSS
// 日期    YYYYMMDD

//资金类别
enum money_type
{
	motRMB = 'R', //RMB
	motUSD = 'U', //USD
	motHKD = 'H', //HKD
	motNo  = 'N'  //未知
};

//帐号类别
enum account_type
{
	asSHA = '0',  //上海交易所的股东代码
	asSZA = '1',  //深圳交易所的股东代码
	asJJS = '2',  //上海金融交易所客户代码
	asFDL = '3',  //大连商品期货交易所
	asFZZ = '4',  //郑州商品期货交易所
	asFSH = '5',  //上海商品期货交易所
	asHK  = '6',  //香港联交所账户
	//融券专用证券账户
	//客户信用交易担保证券账户
	//融资专用资金账户
	//客户信用交易担保资金账户
	asCA  = 'Z'   //资金帐号
};

//交易所
enum market_type
{
	mtSHA = 'e',  //上海证券交易所
	mtSZA = 'f',  //深圳证券交易所
	mtJJS = 'j',  //上海金融交易所
	mtFSH = 'g',  //上海商品期货交易所
	mtFZZ = 'i',  //郑州商品期货交易所
	mtFDL = 'h',  //大连商品期货交易所
	mtHK  = 'k',  //香港联合交易所
	mtNo  = 'N'
};

//买卖类别 Type
enum order_type
{
	otBuy      = 'B', //买
	otSell     = 'S', //卖
	otETFSub   = 'C', //ETF申购
	otETFRed   = 'R', //ETF赎回
	otOpenBuy  = '1', //开仓买
	otOpenSell = '2', //开仓卖
	otCloseBuy = '3', //平仓买
	otCloseSell= '4', //平仓卖
	otLoanBuy  = '5', //融资买
	otLoanSell = '6', //融券卖
	otBuyRepay = '7', //买券还券
	otSellRepay= '8', //卖券还款
	otCloseTodayBuy ='b',// 平今仓买
	otCloseTodaySell='s',// 平今仓卖
	otNo       = 'N'  //其他
};

//委托状态
enum order_state
{
	oswb = '0', //未报(等待申报中...)
	osyb = '1', //已报(已经报了,但没有任何成交,等待成交中...)
	osdc = '2', //待撤(撤单命令已下等待撤单)
	osbw = '3', //部撤(确定状态,部分撤销，部分成交)
	osyc = '4', //已撤(确定状态,全部撤销了)
	oscj = '5', //已成(确定状态,完全成交)
	osyf = '6', //已废(确定状态,系统撤单)
  osbc = '7', //部成(已经有成交了,正在成交中...
  osno = 'N'  //未知
};

//仓位类别
enum pos_direction
{
	pdNo    = 'U', // 未知
	pdNet   = 'N', // 净
	pdLong	= 'L', // 多头
	pdShort = 'S'	 // 空头
};

//委托信息
typedef struct
{
	 char     ContractID[SEQ_LEN+1];         //合同序号
	 char     SecuID[CODE_LEN+1];            //证券代码
	 market_type  Market;                    //交易市场
	 long     Time;                          //委托时间  hhmmss
	 long     Date;                          //委托日期  yyyymmdd
	 order_type  Type;                       //委托类型
	 order_state State;                      //委托状态
	 long     CsnVol;                        //委托数量
	 long     TrdVol;                        //成交数量
	 long     CancelVol;                     //撤单数量
	 double   CsnPrice;                      //委托价格
	 double   TrdPrice;                      //成交价格
	 char     Account[ACC_LEN+1];            //股东代码或者期货交易编号
	 char     SeqNum[SEQ_LEN+1];
} TOrderInfo;

//成交信息
typedef struct  {
   char     ContractID[SEQ_LEN+1];         //合同序号
   char     SecuID[CODE_LEN+1];            //证券代码
   char     TrdID[SEQ_LEN+1];              //成交编号号
   long     Time;                          //成交时间 hhmmss
   long     Date;                          //成交日期 yyyymmdd
   order_type Type;                        //买卖类别 B,S
   long     Vol;                           //成交数量为负数表示撤单
   double   Price;                         //成交价格
   market_type Market;                     //市场
   char     Account[ACC_LEN+1];            //股东代码或者期货交易编号
   char     SeqNum[SEQ_LEN+1];             //定位串


} TTradeInfo;

//股份信息
typedef struct {
  char   SecuID[CODE_LEN+1];              //代码
  char   Account[ACC_LEN+1];              //证券股东帐号或者交易者账号
  pos_direction PosDir;                   //部位方向
  market_type  Market;

  int    Balance;                         //昨日余额
  int    PosNum;                          //当前拥股数
  int    Available;                       //股份可平仓数

  double CostPrice;                       //参考成本价
  double CurPrice;                        //参考市价
}TStockInfo;

//帐号信息
typedef struct {
  account_type lt;         //存储登录时的账户类型
  char Capital[ACC_LEN+1]; //资金帐号
  char SH[ACC_LEN+1];      //上海交易所股东代码
  char SZ[ACC_LEN+1];      //深圳交易所股东代码
  char FJJS[ACC_LEN+1];    //金融期货交易所交易者账号
  char FDL[ACC_LEN+1];     //大连期货交易所交易者账号
  char FZZ[ACC_LEN+1];     //郑州期货交易所交易者账号
  char FSH[ACC_LEN+1];     //上海期货交易所交易者账号
  char FHK[ACC_LEN+1];     //香港联交所投资者账户
  char PW[PWD_LEN+1];      //帐号密码
}TAccountInfo;

//资金信息
typedef struct{
	money_type MoneyType;
  double balance;     //资金余额
  double available;   //可用资金
}TMoneyInfo;

//错误信息
typedef struct {
	char Sender[SEQ_LEN+1];         // 错误的发起者，空或者SYSTEM表示TRDSVR程序发出的错误
	long ErrorCode;          // ErrorCode为0表示没有错误
  char Text[MAX_TEXT+1];
}TInterfaceError;


//Error Code 定义
#define ERR_UNDO_ALREADY_FILLED -888100      // 已经成交了
#define ERR_UNDO_REPEAL         -888200      // 废单无法撤销
#define ERR_UNDO_ALREADY_CANCLED -888300     // 已经撤销了
#define ERR_UNDO_CANNOT_CANCLE  -888301      // 无法撤单(无需再撤单了)
#define ERR_TRDSVR_SEND_FAILED  -888904      // TRDSVR 发送请求失败
#define ERR_TRDSVR_RECV_FAILED  -888905      // TRDSVR 接收请求失败
#define ERR_TRDSVR_OTHER_FAILED -888906      // TRDSVR 收发过程中的其他错误
#define ERR_REMOTE_SEND_FAILED  -888901      // 远程柜台发送请求失败（请求未发送成功）
#define ERR_REMOTE_RECV_FAILED  -888902      // 远程柜台接收请求失败（请求可能已经发送成功）
#define ERR_REMOTE_OTHER_FAILED -888903      // 远程柜台收发过程中的其他错误
#pragma pack()
//------------------------------------------------------------------------------
#endif
