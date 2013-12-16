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
  int    FCurConnectNO;

  double  SMToD(SmallMoney m); //��smallMoneyת����double
  double  MToD(Money m);       //��Moneyת����double

  int  Deal(String SecuID,double Price,int Num,char Sort,short type,String &HTXH); //ί��ȷ��

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



  //////���׺���/////
  int  Buy();
  int  Sell();
  int  Undo(); //ί�г���

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
  //�ر��м������
  virtual void CloseLink(void);

  int  Connect(void)  ;

public:		// User declarations
   TTrdItf_JZ(TJZSet *JZSet);
   virtual  ~TTrdItf_JZ();
};
//---------------------------------------------------------------------------
#endif
