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
#define ERR_NO_ACK               -104  //����Ӧ
#define ERR_OTHERS               -103
#define ERR_UNIMPLEMENTED        -200  //δʵ��

enum t_input_content
{
  iczj='1',     //��  �ʽ��˺�
  icia='2',     //�����ɶ����루internal_account��
	iccard_no='3',//�������׿��ţ�card_no��
  icba='4',     //���������ʺţ�bank_account��
	icsa='5',     //����֤ȯ�˺ţ�stock_account��
  iccn='6'      //�����ͻ���ʾ��customer_no��
};

/*
  content_type
  ���input_content  = ֤ȯ�˺�, ��content_type = exchange_type
	���input_content  = �����ʺ�, ��content_type = bank_no
*/

enum t_exchange_type
{
	etqt ='0'  ,  //�� ǰ̨δ֪������
  etsh ='1'  ,  //��  �Ϻ�
  etsz ='2'  ,  //��  ����
	etcy ='8' ,  //�� ��ҵ��
  etshb='D'  ,  //�����Ϻ�B
  etszb='H'  ,  //��������B
};

enum t_entrust_way
{
 	ewzz='0',//: ����ί��
  ewdh='1',//: �绰ί��
  ewzl='2',//: פ��ί��
  ewyc='3',//: Զ��ί��
	ewgt='4',//: ��̨ί��
  ewmy='5',//: ����ί��
  ewfz='6',//: ��֧ί��
  ewin='7',//: internetί��
};

enum t_entrust_status
{
  eswb='0'  ,//δ��
  esyb='2'  ,//�ѱ�
  esdc1='3' ,//����
  esdc2='4' ,//����
  esbc='5'  ,//����
  esyc1='6' ,//�ѳ�
  esyc2='7' ,//�ѳ�
  esyc='8'  ,//�ѳ�
  esyf='9'  ,//�ѷ�

  /*
  0 δ��
  1 ����
  2 �ѱ�
  3 �ѱ�����
  4 ���ִ���
  5 ����
  6 �ѳ�
  7 ����
  8 �ѳ�
  9 �ϵ�
  10 ��ȷ��
  */
};

enum t_money_type
{
  mtrmb='0'   ,//�����
  mtdollar='1',// ��Բ
  mthkd='2'   ,//�۱�
};

enum t_entrust_bs
{
  ebbuy='1' ,//-- ����
  ebsell='2',// -- ����
};

enum t_query_direction
{
  qdahead='1' ,//--��ǰ����˳��
  qdnext='0'  ,//--���󷭣�����
};

enum t_entrust_type
{
  ettrd='0',// ����
  etqry='1',// ��ѯ
  etwithdraw='2',// ����
  etpatch='3',// ����
};

//���ڸ�ʽ YYYYMMDD     ʱ���ʽ��HHMMSS


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
  int  QryBill();      //��ѯ�ʽ���ˮ�����ʵ���  ������ʼ���ڻ��߽�������Ϊ�����ѯ������ˮ
  int  QryStocks();    //��ѯ�ʺ������еĹɷ�
  int  QryMoneyFF();

  int  QryAccount(t_exchange_type et);
  //////���׺���/////
  int  Buy();
  int  Sell();
  int  Undo(); //ί�г���

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
