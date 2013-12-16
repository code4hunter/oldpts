/*
 *  DESC: �����м���ڲ��ӿ�
 *  FILE: UTrdItf_DD
 *  BY:   CodeHunter
 */

//---------------------------------------------------------------------------
#ifndef UTrdItf_DDABOSSH
#define UTrdItf_DDABOSSH

#include "FixCommWapp.h"
#include "UTrdItfBase.h"
#include <Classes.hpp>

#define PLUGINNAME "����ABOSS"
//---------------------------------------------------------------------------
/*
  1 �������� := { SH,SZ }
  2 ��������� := { 1,2,3,4,8,-1,-2,-3,-4 }  -----29 ETF �깺--30	ETF���

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

#define FUNC_JY_ETFSGSH  13018

class TTrdItf_DDABOSS : public TTrdItfBase
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
  } TDDABOSSSet;

	//void YYYYMMDD2DingDian(char *s,char *d,char sp='.');
	//void DingDian2YYYYMMDD(char *s,char *d,char sp='.');
  //char DDTypeToType(char *dd_type);
private:
  aboss_3rd FDll;
	TDDABOSSSet FSet;
  void     *FFix;
  char      FKHH[13];

  int  GetGDZH(void* pFix, char *pKHH, TAccountInfo *ai);
  int  GetZJZH(void* pFix, char *pKHH, TAccountInfo *ai);

public:
  TTrdItf_DDABOSS(const char *psetupfile,ADDLOG plogfunc);
  virtual  ~TTrdItf_DDABOSS();

	virtual int  Init();         //��ʼ��
	virtual int  SetAccount();   //��¼��̨�м��

	//////��ѯ����//////
	virtual int  QryMoney();     //�ʽ��ѯ
	virtual int  QryCurCsn();    //����ί�в�ѯ
	virtual int  QryCurTrd();    //���ճɽ���ѯ
	virtual int  QryStocks();    //��ѯ�ʺ������еĹɷ�

	//////���׺���/////
	virtual int  Order();        //ί��
	virtual int  Undo();         //ί�г���

  //���ӿڲ���ת��ɱ�׼����
	virtual market_type  ConvertMarketType(const char *t);
	virtual order_type   ConvertOrderType(const char *t);
	virtual order_state  ConvertOrderState(const char *t);
	virtual pos_direction ConvertPosDir(const char *t);
	virtual money_type   ConvertMoneyType(const char *t);

	virtual char *  ConvertMarketType(market_type t);
	virtual char *  ConvertOrderType(order_type t);
	virtual char *  ConvertOrderState(order_state t);
	virtual char *  ConvertPosDir(pos_direction t);
	virtual char *  ConvertMoneyType(money_type t);

	//��������Ϣ������,���û�л�ȡ������������Ϣ����false
	virtual bool GetConfig(void);
	//��������Ϣ��д�������ļ�
	virtual void SetConfig(void);
	//�ر��м������
	virtual void CloseLink(void);
private:
  void SetError(void);
};

#endif
