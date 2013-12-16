/*
 *  DESC: �����м���ڲ��ӿ�
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
  1 �������� := { SH,SZ }
  2 ��������� := { 1,2,3,4,8,-1,-2,-3,-4 }
  3 ���������˵�� := { ����,����,���,ת��,�깺,����,����,����,��ת }
  4 ��ί����Դ := { GT,CK,RJ,DH,YC,IN }
	 	  GT :��̨,CK:�ſ�,RJ:�ȼ�,DH:�绰,YC:Զ��,IN:Internet
  5 �������� := { 0,1,2,-1,-2,x }
	 	  0����ʾί��û���걨������������δ�걨�ͳ����ɹ����������
	 	  1����ʾί�����걨������������������û�з��ؽ����
	 	  2����ʾ�������Ѵ���Ӧ�ó���Ӧ����ί���������ɽ������ͳ����������жϡ�
	 	  -1��-2����ʾί���ѳ�����
	 	  <-10����ʾ��ί��Ϊ��Чί�С�
      ������˵�� := { δ �� ��,�� �� ��,�� �� ��,�����ɹ�,ȫ���ɽ�,���ݳɽ�,��Чί�� }
   6 ��ͣ�Ʊ�־ := { 0,1 } 1:ͣ��
	 7 �����ڸ�ʽΪyyyy:mm:dd
   8 ������:={RMB,USD,HKD}
 */

class TTrdItf_DD : public TTrdItfBase
{
public:
  typedef struct
  {
    char pUser[10];     //������Ա
    char pWtfs[3];      //RJ:�ȼ�,DH:�绰,YC:Զ��,CK:ˢ��
    char pYyb[10];      //����Ӫҵ��
    char pRight[100];   //У�鴮(���԰�δʹ��)
    char pDest[50];     //���㴦�����ַ=��ַ,�˿ں�/Э�����磺
                        //00ABCDEF,0123456789AB,8001/spx
                        //�� 200.200.200.200,9001/tcp
    char pRemote[100];  //δʹ��
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
