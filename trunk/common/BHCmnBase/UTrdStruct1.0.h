#ifndef UTrdStruct1.0H
#define UTrdStruct1.0H

namespace PTRDDLL1
{
////////////帐号类别////////////////////////////////////////////////////////////
enum TAccountSort
{
  asSH = '0',          //上海交易所的股东代码
  asSZ = '1',          //深圳交易所的股东代码
  asJJS = '2',         //上海金融交易所客户代码
  asCA = 'Z'           //资金帐号
};

////////////交易所////////////////////////////////////////////////////////////
enum TBourse
{
  bsSH = '0',  //上海交易所
  bsSZ = '1',   //深圳交易所
  bsJJS = '2'  //上海金融交易所
};

//买卖类别 Type
enum bs_type
{
  btBuy = 'B', //买
  btSell= 'S', //卖
  btNo  = 'N'  //其他
};

//委托状态
enum wt_state
{
  //'0'：未报  '1'：已报   '2'：待撤  '3'：部撤  '4'：已撤  '5'--已成  '6'--已废
  wswb = '0',
  wsyb = '1',
  wsdc = '2',
  wsbw = '3',
  wsyc = '4',
  wscj = '5',
  wsyf = '6',
  wsbc = '7',  //部成
  wsno = 'N'
};
// 时间    HHMMSS
// 日期    YYYYMMDD
// 证券代码格式 上交所的股票 前面加'H',深交所的加'S' ,金融期货'F'

////////////买卖信息（盘口数据）////////////////////////////////////////////////
#pragma pack(1)
typedef struct
{
  double ZXJ;         //最新价
  double Price1;      //申价1
  double Price2;      //申价2
  double Price3;      //申价3

  int   CJSL;        //成交数量
  int   Volum1;      //申量1
  int   Volum2;      //申量2
  int   Volum3;      //申量4
} TDealInfo;

///////////委托信息////////////////////////////////
typedef struct
{
   char     ContractID[8];         //合同序号 
   char     SecuID[8];             //证券代码 
   char     SecuDesc[9];           //证券名称
   char     Bourse;                //交易所
   char     NoUse[6];
   char     Time[9];               //委托时间
   char     Date[9];               //委托日期
   char     Type;                  //bs_type
   char     State;                 //wt_state
   long     CsnVol;                //委托数量
   long     TrdVol;                //成交数量
   long     CancelVol;             //撤单数量
   double   CsnPrice;              //委托价格
   double   TrdPrice;              //成交价格
} TConsignInfo;

//////////////成交信息//////////////////////////////////////////
typedef struct  {
   char     SecuID[8];             //证券代码 
   char     SecuDesc[9];           //证券名称
   char     Time[9];               //成交时间
   char     Date[9];               //委托日期
   char     Type;                  //买卖类别 B,S
   long     Vol;                   //成交数量
   double   Price;                 //成交价格
} TTradeInfo;

/////////////资金流水///////////////////////////////////////////
typedef struct  {
   char     Date[9];               //委托日期
   char     SecuID[8];             //证券代码
   char     SecuDesc[9];           //证券代码
   char     Type[13];              //买卖类别说明
   char     NoUse[5];
   long     Vol;                   //成交数量
   double   Price;                 //成交价格
   double   TrdMny;                //成交金额
   double   Balance;               //资金余额
}TFundInfo;

/////////////股份信息/////////////////////////////////////////////////////////
typedef struct {
  char   SecuID[8];       //证券代码            
  char   SecuDesc[12];    //证券股东代码或者交易者账号
  int    Balance;         //余额                F买持仓
  int    Available;       //可用数              F卖持仓
 
  int    BuyFreeze;       //买入冻结
  int    SellFreeze;      //卖出冻结
  int    AbnorFreeze;     //异常冻结 
  
  double Cost;            //参考成本            
  double CostPrice;       //参考成本价          F买均价
  double CurVal;          //参考市值
  double CurPrice;        //参考市价            F卖均价
  double ProfitAndLoss;   //参考盈亏
  
}TStockInfo;

////////////帐号信息/////////////////////////////////////////////////////////
typedef struct {
  char Capital[13]; //资金帐号
  char SH[13];      //上海交易所股东代码  ,或者期货帐号
  char SZ[13];      //深圳交易所股东代码
  char PW[13];      //帐号密码
}TAccountInfo;

typedef struct {
  char exchange[10];
//（1） 交易所代码
//（2） 交易所名称
//（3） 合约编码
//（4） 合约名称
//（5） 每手数量
//（6） 投机
//（7） 保值
//（8） 最后日期
//（9） 最大手数
//（10）最大持仓
}TFuctureCode;


#define MAX_TEXT 256

typedef struct {
  char Sender[10];         // 错误的发起者，空或者SYSTEM表示TRDSVR程序发出的错误
  long ErrorCode;          // ErrorCode为0表示没有错误
  char Text[MAX_TEXT+1];
}TInterfaceError;

#pragma pack()

}
//------------------------------------------------------------------------------
#endif
