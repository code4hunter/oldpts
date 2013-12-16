/*
 *  DESC: 顶点中间件内部接口
 *  FILE: UTrdItf_DD
 *  BY:   CodeHunter
 */

//---------------------------------------------------------------------------
#ifndef UTrdItf_DDH
#define UTrdItf_DDH

#include "DinDianWapp.h"
#include "UTrdItfBase.h"

//---------------------------------------------------------------------------
/*
  1 、交易所 := { SH,SZ }
  2 、买卖类别 := { 1,2,3,4,8,-1,-2,-3,-4 }
  3 、买卖类别说明 := { 买入,卖出,配股,转托,申购,撤买,撤卖,撤配,撤转 }
  4 、委托来源 := { GT,CK,RJ,DH,YC,IN }
	 	  GT :柜台,CK:磁卡,RJ:热键,DH:电话,YC:远程,IN:Internet
  5 、处理结果 := { 0,1,2,-1,-2,x }
	 	  0：表示委托没有申报到交易所，有未申报和撤消成功两种情况。
	 	  1：表示委托已申报到交易所而交易所还没有返回结果。
	 	  2：表示交易所已处理。应用程序应根据委托数量、成交数量和撤单数量作判断。
	 	  -1、-2：表示委托已撤消。
	 	  <-10：表示该委托为无效委托。
      处理结果说明 := { 未 申 报,申 报 中,已 申 报,撤消成功,全部成交,部份成交,无效委托 }
   6 、停牌标志 := { 0,1 } 1:停牌
	 7 、日期格式为yyyy:mm:dd
   8 、币种:={RMB,USD,HKD}
 */

class TTrdItf_DD : public TTrdItfBase
{
public:
  typedef struct
  {
    char pUser[10];     //操作柜员
    char pWtfs[3];      //RJ:热键,DH:电话,YC:远程,CK:刷卡
    char pYyb[10];      //本地营业部
    char pRight[100];   //校验串(测试版未使用)
    char pDest[50];     //顶点处理机地址=地址,端口号/协议例如：
                        //00ABCDEF,0123456789AB,8001/spx
                        //或 200.200.200.200,9001/tcp
    char pRemote[100];  //未使用
  } TDDSet;

  static void YYYYMMDD2DingDian(char *s,char *d,char sp='.');

  static void DingDian2YYYYMMDD(char *s,char *d,char sp='.');

  char DDTypeToType(char* dd_type);
private:
  CAPEX3RD FDll;
  TDDSet FSet;
  void *FCot;

  void ShowErr(void);
public:
  TTrdItf_DD(TDDSet & set);
  virtual  ~TTrdItf_DD();

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
  int  QryBill();      //查询资金流水（对帐单）
  int  QryStocks();    //查询帐号中所有的股份
  //////交易函数/////
  int  Buy();
  int  Sell();
  int  Undo(); //委托撤单

  virtual bs_type ConvertType(char *type)
  {
    return btNo;
  }

  virtual wt_state ConvertState(char *state)
  {
    return wsno;
  }

  void CloseLink(void)
  {
    if(FCot!=NULL)
    {
      FDll.ApexCloseLink(FCot);
      FCot=NULL;
    }
  }
};

#endif
