#ifndef UDynStrH
#define UDynStrH

//---------------------------------------------------------------------------
//DBF文件头结构--------------------------------------------------------------
//---------------------------------------------------------------------------
struct DbfHead {
  char  Flag;
  char  Year;
  char  Month;
  char  Day;
  int   RecNum;
  short HeadLen;
  short RecLen;
};
//---------------------------------------------------------------------------
//上证行情-------------------------------------------------------------------
//---------------------------------------------------------------------------
struct TShow128 {
  char DelFlag;
  char SecuID[6];           //股票代码                 S1 C 6
  char SecuDesc[8];         //股票名称                 S2 C 8
  char Lc[8];               //昨日收盘价               S3 N 8 3
  char Co[8];               //开盘价                   S4 N 8 3
  char Mny[12];             //累计成交金额             S5 N 12
  char Ch[8];               //最高价                   S6 N 8 3
  char Cl[8];               //最低价                   S7 N 8 3
  char Cp[8];               //最新价                   S8 N 8 3
  char Cbp[8];              //当前买入价               S9 N 8 3
  char Csp[8];              //当前卖出价               S10 N 8 3
  char Vlm[10];             //累计成交量               S11 N 10
  char Pe[8];               //市盈率                   S13 N 8 3
  char Bv1[10];             //买量一                   S15 N 10
  char Bp2[8];              //买价二                   S16 N 8 3
  char Bv2[10];             //买量二                   S17 N 10
  char Bp3[8];              //买价三                   S18 N 8 3
  char Bv3[10];             //买量三                   S19 N 10
  char Sv1[10];             //卖量一                   S21 N 10
  char Sp2[8];              //卖价二                   S22 N 8 3
  char Sv2[10];             //卖量二                   S23 N 10
  char Sp3[8];              //卖价三                   S24 N 8 3
  char Sv3[10];             //卖量三                   S25 N 10
  //新加
  char Bp4[8]; 	    //申买价四                 S26 N 8 3
  char Bv4[10];             //申买量四                 S27 N 10
  char Bp5[8]; 	    //申买价五                 S28 N 8 3
  char Bv5[10];             //申买量五                 S29 N 10
  char Sp4[8];              //申卖价四                 S30 N 8 3
  char Sv4[10];             //申卖量四                 S31 N 10
  char Sp5[8];              //申卖价五                 S32 N 8 3
  char Sv5[10];             //申卖量五                 S33 N 10

};
//---------------------------------------------------------------------------
//深券行情-------------------------------------------------------------------
//---------------------------------------------------------------------------
struct TSjsHQ {
  char DelFlag;
  char SecuID[6];           //证券代码                 HQZQDM C 6
  char SecuDesc[8];         //证券名称                 HQZQJC C 8
  char Lc[9];               //前收盘价                 HQZRSP N 9 3
  char Co[9];               //今开盘价                 HQJRKP N 9 3
  char Cp[9];               //最新价                   HQZJCJ N 9 3
  char Vlm[12];             //今累计成交数量           HQCJSL N 12 0
  char Mny[17];             //今累计成交金额  （元）   HQCJJE N 17 3
  char NotUsed1[9];         //成交笔数                 HQCJBS N 9 0
  char Ch[9];               //最高价                   HQZGCJ N 9 3
  char Cl[9];               //最低价                   HQZDCJ N 9 3
  char Pe[7];               //市盈率1                  HQSYL1 N 7 2
  char NotUsed2[7];         //市盈率2                  HQSYL2 N 7 2
  char NotUsed3[9];         //价格升跌1                HQJSD1 N 9 3
  char NotUsed4[9];         //价格升跌2                HQJSD2 N 9 3
  char NotUsed5[12];        //合约持仓量               HQHYCC N 12 0
  char Sp5[9];              //卖价五                   HQSJW5 N 9 3  +
  char Sv5[12];             //卖量五                   HQSSL5 N 12 0 +
  char Sp4[9];              //卖价四                   HQSJW4 N 9 3
  char Sv4[12];             //卖量四                   HQSSL4 N 12 0
  char Sp3[9];              //卖价三                   HQSJW3 N 9 3
  char Sv3[12];             //卖量三                   HQSSL3 N 12 0
  char Sp2[9];              //卖价二                   HQSJW2 N 9 3
  char Sv2[12];             //卖量二                   HQSSL2 N 12 0
  char Csp[9];              //卖价一                   HQSJW1 N 9 3
  char Sv1[12];             //卖量一                   HQSSL1 N 12 0
  char Cbp[9];              //买价一                   HQBJW1 N 9 3
  char Bv1[12];             //买量一                   HQBSL1 N 12 0
  char Bp2[9];              //买价二                   HQBJW2 N 9 3
  char Bv2[12];             //买量二                   HQBSL2 N 12 0
  char Bp3[9];              //买价三                   HQBJW3 N 9 3
  char Bv3[12];             //买量三                   HQBSL3 N 12 0
  char Bp4[9];              //买价四                   HQBJW4 N 9 3
  char Bv4[12];             //买量四                   HQBSL4 N 12 0
  char Bp5[9];              //买价五                   HQBJW5 N 9 3   +
  char Bv5[12];             //买量五                   HQBSL5 N 12 0  +
};
//---------------------------------------------------------------------------
//深证证券信息20060406-------------------------------------------------------------------
//---------------------------------------------------------------------------
struct TSjsXX {
  char DelFlag;
  char SecuID[6];//XXZQDM	证券代码	C	6
  char SecuDesc[8];//XXZQJC	证券简称	C	8
  char DescEn[20];//XXYWJC	英文简称	C	20
  char Unit[4];//XXJYDW	交易单位	N	4,0
  char IndType[3];//XXHYZL	行业种类	C	3
  char MnyType[2];//XXHBZL	货币种类	C	2
  char FaceVal[7];//XXMGMZ	每股面值	N	7,2
  char TolVol[12];//XXZFXL	总发行量	N	12,0
  char Turnover[12];//XXLTGS	流通股数	N	12,0
  char LProfit[9];//XXSNLR	上年每股利润	N	9,4
  char TProfit[9];//XXBNLR	本年每股利润	N	9,4
  char HandTax[7];//XXJSFL	经手费率	N	7,6  	按成交金额计算
  char PrtTax[7];//XXYHSL	印花税率	N	7,6  	按成交金额计算
  char TranTax[7];//XXGHFL	过户费率	N	7,6
  char IpoDate[8];//XXSSRQ	上市日期	D	8    	CCYYMMDD
  char ExpDate[8];//XXDJRQ	到期/交割日	D	8    	CCYYMMDD
  char LimitVol[9];//XXMBXL	每笔限量	N	9,0
  char BuyNum[6];//XXBLDW	买数量单位	N	6,0
  char SelNum[6];//XXSLDW	卖数量单位	N	6,0
  char PrcGrade[5];//XXJGDW	价格档位	N	5,3
  char SetPara[7];//XXJHCS	集合竞价限价参数	N	7,3
  char ConPara[7];//XXLXCS	连续竞价限价参数	N	7,3
  char LimitPro;//XXXJXZ	限价参数性质	N	1,0
  char MaxPrc[9];//XXZTJG	涨停价格	N	9,3
  char MinPrc[9];//XXDTJG	跌停价格	N	9,3
  char ConRatio[5];//XXZHBL	折合比例	N	5,2
  char TrdStatus;//XXJYZT	交易状态	C	1
  char SecuRank;//XXZQJB	证券级别	C	1
  char StopFlag;//XXTPBZ	停牌标志	C	1
  char BonusFlag;//XXCQCX	除权除息标志	C	1
  char ElemFlag;//XXCFBZ	成份股标志	C	1
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//自定义结构和发送数据的组织-------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#pragma pack(push, 1)

struct TPListHead  {        //CurPList文件的头
  long ShStockNum;          //上证股票数量（包括，A、B、F、I、D)
  long ShSendTime;          //上证行情发送时间
  long SzStockNum;          //深证股票数量
  long SzSendTime;          //深证行情发送时间
  long PtfNum;
  long NoUsed[3];
};
//---------------------------------------------------------------------------
struct TSecuDesc {
  char SecuID[8];           //证券代码        上海  H+股票代码   深圳   S+股票代码
  char SecuDesc[9];         //证券名称
};
//---------------------------------------------------------------------------
struct TUDPSecuDesc {
  long SecuNo;     	        //股票在内存中的序号
};
//---------------------------------------------------------------------------
//发送包结构-----------------------------------------------------------------
//---------------------------------------------------------------------------
struct TUDPPackage {
  long	PackageNo;			    //数据报的序号
  char	Type;				        //数据报类型P-报价单 D-分时数据 B排行榜
  long	Sum;				        //待发送的数据的记录总数
  void 	*Buf;				        //待发送的数据即报价单、分时数据、排行榜数据，大小不定，但应该<8k。
};
//---------------------------------------------------------------------------
//报价单---------------------------------------------------------------------
//---------------------------------------------------------------------------
struct TPriceListSta:TSecuDesc  {
  char          Type;       //证券种类        分  A股、B股
  char          Py[5];      //股票名称拼音
  unsigned long V5da;       //前5天平均每分钟成交量 Vlum of 5 Days Avg
  unsigned long FltStk;     //流通股（万）
  unsigned long Lc;         //前收盘价
  unsigned long Date;       //日期
};
//---------------------------------------------------------------------------
struct TPriceListDyn {
  unsigned long Vlm;        //今累计成交数量
  double  Mny;              //今累计成交金额  （元）
  unsigned long Co;         //今开盘价
  unsigned long Ch;         //最高价
  unsigned long Cl;         //最低价
  unsigned long Cp;         //最新价
  unsigned long Pe;         //市盈率
  unsigned long Bv1;        //买量一
  unsigned long Bv2;        //买量二
  unsigned long Bv3;        //买量三
#ifndef USE3
	unsigned long Bv4;        //买量四
  unsigned long Bv5;        //买量五
#endif
  unsigned long Cbp;        //买价一
  unsigned long Bp2;        //买价二
  unsigned long Bp3;        //买价三
#ifndef USE3
	unsigned long Bp4;        //买价四
  unsigned long Bp5;        //买价五
#endif
  unsigned long Sv1;        //卖量一
  unsigned long Sv2;        //卖量二
  unsigned long Sv3;        //卖量三
#ifndef USE3
	unsigned long Sv4;        //卖量四
  unsigned long Sv5;        //卖量五
#endif
  unsigned long Csp;        //卖价一
  unsigned long Sp2;        //卖价二
  unsigned long Sp3;        //卖价三
#ifndef USE3
	unsigned long Sp4;        //卖价四
  unsigned long Sp5;        //卖价五
#endif
  unsigned long Abv;        //外盘
  unsigned long Cv;         //当前量
  unsigned long C5ma;       //5分钟前收盘价  Close of 5 minutes ago
  unsigned long C4ma;       //4分钟前收盘价
  unsigned long C3ma;       //3分钟前收盘价
  unsigned long C2ma;       //2分钟前收盘价
  unsigned long C1ma;       //1分钟前收盘价
  unsigned long Time;       //时间
  unsigned long Cmv;        //最新的分钟成交量
  double        Cmm;        //最新的分钟成交金额
  unsigned long PVlm;       //上次累计成交数量
};
//---------------------------------------------------------------------------
struct TPriceList:TPriceListSta,TPriceListDyn {
};
//---------------------------------------------------------------------------
struct TUDPPriceListSta:TUDPSecuDesc,TPriceListSta{
};
//TUDPPriceList--------------------------------------------------------------
struct TUDPPriceList:TUDPSecuDesc,TPriceListDyn {
};
//---------------------------------------------------------------------------
//20050517----初始化行情请求时发送如下数据报Type='I'或者Type='S'
struct TUDPPriceListInit : TUDPSecuDesc,TPriceList{
};
//---------------------------------------------------------------------------
//#pragma pack(push, 4)	
struct TUDPPriceListT{
  long SecuNo;     	        //股票在内存中的序号
  unsigned long Vlm;        //今累计成交数量
  long me1;
  double  Mny;              //今累计成交金额  （元）
  unsigned long Co;         //今开盘价
  unsigned long Ch;         //最高价
  unsigned long Cl;         //最低价
  unsigned long Cp;         //最新价
  unsigned long Pe;         //市盈率
	unsigned long Bv1;        //买量一
  unsigned long Bv2;        //买量二
  unsigned long Bv3;        //买量三
#ifndef USE3
	unsigned long Bv4;        //买量四
  unsigned long Bv5;        //买量五
#endif
  unsigned long Cbp;        //买价一
  unsigned long Bp2;        //买价二
  unsigned long Bp3;        //买价三
#ifndef USE3
	unsigned long Bp4;        //买价四
  unsigned long Bp5;        //买价五
#endif
  unsigned long Sv1;        //卖量一
  unsigned long Sv2;        //卖量二
  unsigned long Sv3;        //卖量三
#ifndef USE3
	unsigned long Sv4;        //卖量四
  unsigned long Sv5;        //卖量五
#endif
  unsigned long Csp;        //卖价一
  unsigned long Sp2;        //卖价二
  unsigned long Sp3;        //卖价三
#ifndef USE3
	unsigned long Sp4;        //卖价四
  unsigned long Sp5;        //卖价五
#endif
  unsigned long Abv;        //外盘
  unsigned long Cv;         //当前量
  unsigned long C5ma;       //5分钟前收盘价  Close of 5 minutes ago
  unsigned long C4ma;       //4分钟前收盘价
  unsigned long C3ma;       //3分钟前收盘价
  unsigned long C2ma;       //2分钟前收盘价
  unsigned long C1ma;       //1分钟前收盘价
  unsigned long Time;       //时间
  unsigned long Cmv;        //最新的分钟成交量
  double        Cmm;        //最新的分钟成交金额
  unsigned long PVlm;       //上次累计成交数量
  long me2;
  long me3;
};
#pragma pack(pop)

//---------------------------------------------------------------------------
//成交明细-------------------------------------------------------------------
//---------------------------------------------------------------------------
struct  TDetailDeal {
  unsigned long Time;       //时间   HHMMSS
  unsigned long Cp;         //最新价格
  unsigned long Cv;         //数量
};
//---------------------------------------------------------------------------
struct TDetailHead {
  unsigned long Date;
  long ShStockNum;          //上证股票数量（包括，A、B、F、I、D)
  long SzStockNum;          //深证股票数量
  long PtfNum;
  long NoUsed[4];
  char IdxId[80000];
};
//---------------------------------------------------------------------------
struct TDetailTick {        //一支股票的名细数据
  int  ExgNum;              //交易次数
  unsigned long Lc;         //昨日收盘价
  TDetailDeal Dtl[2400];    //2400个分笔数据
};
//---------------------------------------------------------------------------
struct  TDetailMin {
  unsigned long Time;
  unsigned long Ch;         //一分钟最高
  unsigned long Cl;         //一分钟最低
  unsigned long Co;         //一分钟开盘
  unsigned long Ce;         //一分钟收盘
  unsigned long Vlm;        //一分钟数量
  double        Mny;        //一分钟金额
};
//---------------------------------------------------------------------------
struct TDetailSecu {        //一支股票的分钟数据
  unsigned long Date;       //交易日期
  TDetailMin Min[242];      //242个分钟数据
};
//---------------------------------------------------------------------------
struct TDetailDynMin {      //一支股票的分钟数据
  int RecNum;               //分钟记录数
  unsigned long Date;
  TDetailMin Min[242];      //242个分钟数据
};
//---------------------------------------------------------------------------
//TUDPDetailDeal-------------------------------------------------------------
struct TUDPDetailDeal:TUDPSecuDesc,TDetailDeal {
};
//---------------------------------------------------------------------------
//排行榜---------------------------------------------------------------------
//---------------------------------------------------------------------------
const int BrdStockAllNum = 480;    //12种指标*10个排名*4个种类
//---------------------------------------------------------------------------
struct TBillBoard:TSecuDesc{       //排行榜结构
  unsigned long Cp;         //最新价
  unsigned long Lc;         //昨日收盘
  long          IndexData;  //需要计算的指标数据
};
//TUDPBillBoard--------------------------------------------------------------
struct TUDPBillBoard:TUDPSecuDesc,TBillBoard  {
};
//---------------------------------------------------------------------------
struct TMemPListDtlDl:TPriceList	{
	//十个指标
	double Rc;   //委比                Ration of Commision
	double Dc;   //委差                Difference of commision
	double Rv;   //量比                Ratio of Volum
	double Ap;   //均价                Average price
	double Ef;   //涨跌幅              Extent of Fluctuate
	double Ft;   //涨跌                Fluctuate
	double Asv;  //外盘                Vlum of Sell
	double El;   //振幅                Extent of Librate
	double Re;   //换手率              Ratio of Exchange
};
//---------------------------------------------------------------------------
//枚举名，表示指标的类型-----------------------------------------------------
//---------------------------------------------------------------------------
enum TDynType{
  dtSecuID,     //股票代码
  dtSecuDesc,   //股票名称
  dtRc,         //委比
  dtDc,         //委差
  dtRv,         //量比
  dtAp,         //均价
  dtEf,         //涨跌幅（%）
  dtFt,         //涨跌
  dtAbv,        //外盘
  dtAsv,        //内盘
  dtEl,         //振幅
  dtRe,         //换手率
  dtCp,         //当天最新价
  dtCo,         //开盘价
  dtCh,         //最高价
  dtCl,         //最低价
  dtVlm,        //成交量
  dtMny,        //成交额
  dtPe,         //市盈率
  dtTime,       //时间
  dtDate,       //日期
  dtCv,         //当前量
  dtCbp,        //当前委买价
  dtBp2,        //买价二
  dtBp3,        //买价三
  dtBv1,        //买量一
  dtBv2,        //买量二
  dtBv3,        //买量三
  dtCsp,        //当前委卖价
  dtSp2,        //卖价二
  dtSp3,        //卖价三
  dtSv1,        //卖量一
  dtSv2,        //卖量二
  dtSv3,        //卖量三
  dtC5ma,       //5分钟前收盘价
  dtType,       //类型
  dtPy,         //拼音
  dtV5da,       //前5天平均每分钟成交量
  dtFltStk,     //流通股数
  dtLc,         //最日收盘价
  dtCmv,        //最新分钟成交量
  dtCmm,        //最新分钟成交金额
  dtPVlm
};
//---------------------------------------------------------------------------
enum TGuideType{gtIdx,gtHA,gtHB,gtSA,gtSB,gtFund,gtND};
//---------------------------------------------------------------------------
#endif
