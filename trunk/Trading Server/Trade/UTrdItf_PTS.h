//---------------------------------------------------------------------------
#ifndef UTrdItf_PTSH
#define UTrdItf_PTSH

#include <SysUtils.hpp>
#include "UTrdItfBase.h"
#include "uPTSTrans.h"

#define HS_VERSION "111"

#define ERR_UNKNOW_ACCOUNT_TYPE  -100
#define ERR_SEND_FAULT           -101
#define ERR_RECV_FAULT           -102
#define ERR_NO_ACK               -104  //无相应
#define ERR_OTHERS               -103
#define ERR_UNIMPLEMENTED        -200  //未实现

enum t_input_content
{
  iczj='1',     //－  资金账号
  icia='2',     //－　股东代码（internal_account）
	iccard_no='3',//－　交易卡号（card_no）
  icba='4',     //－　银行帐号（bank_account）
	icsa='5',     //－　证券账号（stock_account）
  iccn='6'      //－　客户标示（customer_no）
};

/*
  content_type
  如果input_content  = 证券账号, 则content_type = exchange_type
	如果input_content  = 银行帐号, 则content_type = bank_no
*/

enum t_exchange_type
{
	etqt ='0'  ,  //－ 前台未知交易所
  etsh ='1'  ,  //－  上海
  etsz ='2'  ,  //－  深圳
	etcy ='8' ,  //－ 创业板
  etshb='D'  ,  //－　上海B
  etszb='H'  ,  //－　深圳B
};

enum t_entrust_way
{
 	ewzz='0',//: 自助委托
  ewdh='1',//: 电话委托
  ewzl='2',//: 驻留委托
  ewyc='3',//: 远程委托
	ewgt='4',//: 柜台委托
  ewmy='5',//: 漫游委托
  ewfz='6',//: 分支委托
  ewin='7',//: internet委托
};

enum t_entrust_status
{
  eswb='0'  ,//未报
  esyb='2'  ,//已报
  esdc1='3' ,//待撤
  esdc2='4' ,//待撤
  esbc='5'  ,//部撤
  esyc1='6' ,//已撤
  esyc2='7' ,//已撤
  esyc='8'  ,//已成
  esyf='9'  ,//已废

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
  */
};

enum t_money_type
{
  mtrmb='0'   ,//人民币
  mtdollar='1',// 美圆
  mthkd='2'   ,//港币
};

enum t_entrust_bs
{
  ebbuy='1' ,//-- 买入
  ebsell='2',// -- 卖出
};

enum t_query_direction
{
  qdahead='1' ,//--往前翻（顺序）
  qdnext='0'  ,//--往后翻（倒序）
};

enum t_entrust_type
{
  ettrd='0',// 买卖
  etqry='1',// 查询
  etwithdraw='2',// 撤单
  etpatch='3',// 补单
};

//日期格式 YYYYMMDD     时间格式：HHMMSS


////////////////////////////////////////////////////////////////////////////
class TTrdItf_PTS : public TTrdItfBase
{
public:
  typedef struct
  {
    char  PTS_Server[20];
    char  PTS_Domain[20];
    char  PTS_Trader[20]; 
  } TPTSSet;
    
private:	// User declarations
  TPTSItf *FItf;
  TPTSSet  FPTSSet;

  //int  Request(TRequest Request,TAnswer **Answer,int &AnsCount);


  int  Init();  //初始化
  int  SetAccount(); //设置帐号

  //////查询函数//////
  int  GetTrdInfo();   //取得盘口数据
  int  QryMoney();     //资金查询
  int  QryStock();     //股份查询
  int  QryCanBuy();    //取可买数量
  int  QryDetail();    //成交查询
  int  QryHisDetail(); //历史成交查询
  int  QryCsn();       //查询某个委托合同
  int  QryCurCsn();    //当日委托查询
  int  QryHisCsn();    //历史委托查询
  int  QryCurTrd();    //当日成交查询
  int  QryHisTrd();    //历史成交查询
  int  QryBill();      //查询资金流水（对帐单）  假如启始日期或者结束日期为空则查询当日流水
  int  QryStocks();    //查询帐号中所有的股份
  int  QryMoneyFF();

  int  QryAccount(t_exchange_type et);
  //////交易函数/////
  int  Buy();
  int  Sell();
  int  Undo(); //委托撤单

  virtual bs_type ConvertType(char *type)
  {
    if(strlen(type)>0)
    {
      if(type[0]==ebbuy)
        return btBuy;
      else if(type[0]==ebsell)
        return btSell;
    }
    return btNo;
  }

  virtual wt_state ConvertState(char *state)
  {
    if(strlen(state)==0) return wsno;
    switch(state[0])
    {
      case '0':
      return wswb;
      case '2':
      return wsyb;
      case '3':
      return wsdc;
      case '4':
      return wsdc;
      case '5':
      return wsbw;
      case '6':
      return wsyc;
      case '7':
      return wsyc;
      case '8':
      return wscj;
      case '9':
      return wsyf;
      default:
        return wsno;
    }
  }

public:		// User declarations
   TTrdItf_PTS(TPTSSet *set);
  virtual  ~TTrdItf_PTS();

  static bool RegCommX(String PathName);

  void CloseLink(void)
  {
  }
};

//---------------------------------------------------------------------------
#endif
