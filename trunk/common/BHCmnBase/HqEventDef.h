#ifndef HQEventDefH
#define HQEventDefH

//
//创建：20060602
//说明：针对PTS行情发布，力求数据简洁实用，故对原来行情发送包进行精简
//参考：PTS2软件系统架构1.0
//

#include "UDynStr.h"
//---------------------------------------------------------------------------
//DBF文件头结构--------------------------------------------------------------
//---------------------------------------------------------------------------
//struct DbfHead 定义详见UDynStr.h

//---------------------------------------------------------------------------
//上证行情-------------------------------------------------------------------
//---------------------------------------------------------------------------
//struct TShow128 定义详见UDynStr.h
//---------------------------------------------------------------------------
//深券行情-------------------------------------------------------------------
//---------------------------------------------------------------------------
//struct TSjsHQ 定义详见UDynStr.h

//---------------------------------------------------------------------------
//深证证券信息---------------------------------------------------------------
//---------------------------------------------------------------------------
//struct TSjsXX 定义详见UDynStr.h

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//自定义结构和发送数据的组织-------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//enum TGuideType  定义详见UDynStr.h

#pragma pack(push, 1)

enum TFieldType{FT_COMBO=1, FT_COLOR=2, FT_FONT=3, FT_PATH=4, FT_FILENAME=5, FT_MULTFILENAME=6, FT_PICTURE=7, FT_CONNSTR=8, FT_INT=10,FT_DOUBLE=11,FT_BSTR=12};

struct THqEventHead
{
  int id;               //事件的id	与发布组件的ProgID一一对应，可以唯一的区分出事件的类型。详见数据字典event_id
  char type;            //事件类型	对于不同的事件,该值含义不尽相同，主要用于进一步区分该事件。
  int count;            //数据条数	发布事件的纪录条数
  int date;             //发布日期	表示该事件发生的日期
  int time;             //发布时间	事件发布的时间。比如即时行情发布的时间或成交回报返回的时间等
  char reserved[8];	    //保留字段
  int fieldcnt;         //后续数据包字段个数	字段描述详见event_desc
  int eventsize;        //后续数据包字段大小	后续event_data的数据包占用的字节数
};

struct THqEventFields
{
  char name[8];			//字段名	
  char type;			//字段类型	详见数据字典field_type
  int size;				//字段大小	该地段占用的字节数
};

#define ACT_SECUCODE_LEN	30

enum THqSrc{hsSh=101, hsSz=102, hsHk=201/*香港*/};
struct TSecuEventData
{
  unsigned long index;  //股票在内存中的序号--从0开始
  short src;		//参PTS,证券代码源THqSrc：101-上证，102-深证
  char code[ACT_SECUCODE_LEN+1];       //证券代码
  char desc[9];     //证券简称
  char type;            //证券种类        分  a股、b股
  unsigned long lc;     //前收盘价

  unsigned long vlm;    //今累计成交数量
  unsigned long cv;     //当前量
  unsigned long co;     //今开盘价
  unsigned long ch;     //最高价
  unsigned long cl;     //最低价
  unsigned long cp;     //最新价

  unsigned long bv1;    //买量一
  unsigned long bv2;    //买量二
  unsigned long bv3;    //买量三
  unsigned long bv4;    //买量四
  unsigned long bv5;    //买量五

  unsigned long bp1;    //买价一
  unsigned long bp2;    //买价二
  unsigned long bp3;    //买价三
  unsigned long bp4;    //买价四
  unsigned long bp5;    //买价五

  unsigned long sv1;    //卖量一
  unsigned long sv2;    //卖量二
  unsigned long sv3;    //卖量三
  unsigned long sv4;    //卖量四
  unsigned long sv5;    //卖量五
  
  unsigned long sp1;    //卖价一
  unsigned long sp2;    //卖价二
  unsigned long sp3;    //卖价三
  unsigned long sp4;    //卖价四
  unsigned long sp5;    //卖价五
};

struct TSecuEventData2:TSecuEventData
{
	unsigned long preSettlePrice;			//昨日结算
	
	//股指期货的当日结算价是期货合约最后一小时成交价格按照成交量的加权平均价。
	unsigned long settlePrice;				//今日结算
};

struct TSecuEventData3
{
  unsigned long index;  //股票在内存中的序号--从0开始
  short src;		    //参PTS,证券代码源THqSrc：101-上证，102-深证
  char code[ACT_SECUCODE_LEN+1];       //证券代码
  char desc[9];         //证券简称
  char type;            //证券种类        分  a股、b股
  float lc;     //昨日收盘价

  unsigned long vlm;    //今累计成交数量
  unsigned long cv;     //当前量
  float co;     //今开盘价
  float ch;     //最高价
  float cl;     //最低价
  float cp;     //最新价

  unsigned long bv1;    //买量一
  unsigned long bv2;    //买量二
  unsigned long bv3;    //买量三
  unsigned long bv4;    //买量四
  unsigned long bv5;    //买量五

  float bp1;    //买价一
  float bp2;    //买价二
  float bp3;    //买价三
  float bp4;    //买价四
  float bp5;    //买价五

  unsigned long sv1;    //卖量一
  unsigned long sv2;    //卖量二
  unsigned long sv3;    //卖量三
  unsigned long sv4;    //卖量四
  unsigned long sv5;    //卖量五
  
  float sp1;    //卖价一
  float sp2;    //卖价二
  float sp3;    //卖价三
  float sp4;    //卖价四
  float sp5;    //卖价五

  double turnover; //成交金额
  float preSettlePrice;	//昨日结算
  float settlePrice;    //今日结算
  //float closePrice;	    //收盘
  float chgPrice;       //涨跌
  float upperLimitPrice;//涨停板
  float lowerLimitPrice;//跌停板
  unsigned long ltime; //时间 hhmmss
};

//---------------------------------------------------------------------------
#pragma pack(pop)

#endif
