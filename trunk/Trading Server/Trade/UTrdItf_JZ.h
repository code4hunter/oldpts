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

  TJZSet FJZSet; //ϵͳ����

  double  SMToD(SmallMoney m); //��smallMoneyת����double
  double  MToD(Money m);       //��Moneyת����double

  int  Deal(String SecuID,double Price,int Num,char Sort,short type,String &HTXH); //ί��ȷ��

  int  Connect(void) ;
  int  Request(tagREQUEST &request,tagRESULT **Results,int &ResNum);

  int  Init();  //��ʼ��
  int  SetAccount(); //�����ʺ�

  //////��ѯ����//////
  int  GetTrdInfo();   //ȡ���̿�����
  int  QryMoney();     //�ʽ��ѯ
  int  QryStock();     //�ɷݲ�ѯ
  int  QryCanBuy();    //ȡ��������
  int  QryDetail();    //�ɽ���ѯ
  int  QryHisDetail(); //��ʷ�ɽ���ѯ
  int  QryCsn();       //��ѯĳ��ί�к�ͬ
  int  QryCurCsn();    //����ί�в�ѯ
  int  QryHisCsn();    //��ʷί�в�ѯ
  int  QryCurTrd();    //���ճɽ���ѯ
  int  QryHisTrd();    //��ʷ�ɽ���ѯ
  int  QryBill();      //��ѯ�ʽ���ˮ�����ʵ���
  int  QryStocks();    //��ѯ�ʺ������еĹɷ�

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
    //'0' δ��
    //'1' �곷
    //'4' ����
    //'5' ȫ��
    //'6' ����
    //'7' ȫ��
    //'8' δ��
    //'9' �ѱ�
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
  //////���׺���/////
  int  Buy();
  int  Sell();
  int  Undo(); //ί�г���

public:		// User declarations
   TTrdItf_JZ(TJZSet *JZSet);
   virtual  ~TTrdItf_JZ();
   void CloseLink(void);
};
//---------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
/*ע��㣺��ͬ�г��ĺ�ͬ��ſ����ظ�*/
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
    AfxMessageBox("����Ա��¼�ɹ�!", MB_OK|MB_ICONERROR);
    break;
  default:
    AfxMessageBox("����Ա��¼ʧ��!", MB_OK|MB_ICONERROR);
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

 