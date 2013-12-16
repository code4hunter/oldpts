//------------------------------------------------------------------------------
#ifndef UTrdItf_JZH
#define UTrdItf_JZH
//------------------------------------------------------------------------------
#include <classes.hpp>
#include "JZAPI.H"
#include "UTrdItfBase.h"
//------------------------------------------------------------------------------
class TTrdItf_JZ : public TTrdItfBase
{
public:
  typedef struct
  {
    char MiddNode[20];
    char MiddAddress[20];
    int  MiddSocket;
    char CounterID[20];
    char CounterPW[20];
    char SHBourse;
    char SZBourse;
    char EntrustWay;
  }TJZSet;

private:	// User declaration

  TJZSet FJZSet; //系统设置

  double  SMToD(SmallMoney m); //将smallMoney转化成double
  double  MToD(Money m);       //将Money转化成double

  int  Deal(String SecuID,double Price,int Num,char Sort,short type,String &HTXH); //委托确认

  int  Connect(void) ;
  int  Request(tagREQUEST &request,tagRESULT **Results,int &ResNum);

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

  virtual bs_type ConvertType(char * type)
  {
    if(strlen(type)>0)
    {
      if(type[0]=='B')
        return btBuy;
      else if(type[0]=='S')
        return btSell;
    }
    return btNo;
  }

  virtual wt_state ConvertState(char * state)
  {
    //'0' 未撤
    //'1' 申撤
    //'4' 部撤
    //'5' 全撤
    //'6' 部成
    //'7' 全成
    //'8' 未发
    //'9' 已报
    if( strlen(state)==0) return wsno;
    switch(state[0])
    {
      case '0' :
        return wsdc;
      case '1' :
        return wsdc;
      case '4' :
        return wsbw;
      case '5' :
        return wsyc;
      case '6' :
        return wsbc;
      case '7' :
        return wscj;
      case '8' :
        return wswb;
      case '9' :
        return wsyb;
      default:
        return wsno;
    }
  }

  bs_type ConvertType(char type)
  {
    char buf[]={type,'\0'};
    return ConvertType(buf);
  }

  wt_state ConvertState(char state)
  {
    char buf[]={state,'\0'};
    return wt_state(buf);
  }
  //////交易函数/////
  int  Buy();
  int  Sell();
  int  Undo(); //委托撤单

public:		// User declarations
   TTrdItf_JZ(TJZSet *JZSet);
   virtual  ~TTrdItf_JZ();
   void CloseLink(void);
};
//---------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
/*注意点：不同市场的合同序号可能重复*/
//------------------------------------------------------------------------------
/* Example:
  tagNETWORKADD arrstAddr[3];
  strcpy(arrstAddr[0].Node, m_strNode);
  strcpy(arrstAddr[0].Address, m_strAddr);
  arrstAddr[0].Socket = 0x7111;
  strcpy(arrstAddr[1].Node, m_strNode);
  strcpy(arrstAddr[1].Address, m_strAddr);
  arrstAddr[1].Socket = 0x7111;
  strcpy(arrstAddr[2].Node, m_strNode);
  strcpy(arrstAddr[2].Address, m_strAddr);
  arrstAddr[2].Socket = 0x7111;

  int iRet = KDAPI_Connect(arrstAddr, (char *)(LPCSTR)m_strCode, (char *)(LPCSTR)m_strPwd);
  switch (iRet)
  {
  case 0:
    AfxMessageBox("操作员登录成功!", MB_OK|MB_ICONERROR);
    break;
  default:
    AfxMessageBox("操作员登录失败!", MB_OK|MB_ICONERROR);
    return;
  }
  tagREQUEST g_Query;
  tagRESULT g_Result;

  BOOL isEnd = FALSE;

  g_Query.head.function = funcYYB;
  g_Query.head.czfs = '0';

  iRet = KDAPI_Request(g_Query);
  if (iRet < 0)
  {
    AfxMessageBox("ERROR!");
  }
  else
  {
    for (int iIndex = 0; iIndex < iRet && !isEnd; iIndex++)
    {
      int iReturn = KDAPI_Answer(g_Result);
      if (iReturn > 0)
      {
        AfxMessageBox(g_Result.yyb.YYBMC);
      }
      else if (iReturn == 0)
      {
        isEnd = TRUE;
      }
      else
      {
        AfxMessageBox("FALSE!");
        return;
      }
    }
  }
*/
//------------------------------------------------------------------------------

 