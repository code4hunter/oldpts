//---------------------------------------------------------------------------
#ifndef uTrdItf_TestH
#define uTrdItf_TestH

#include <vector>
#include <list>
#include <iostream>
using namespace std;

#include "DebugStr.h"
#include "UTrdItfBase.h"
//#include "uPTSDB.h"

#include "HQPoolSvrLib_OCX.h"
//---------------------------------------------------------------------------
#define PLUGINNAME "����ģ��ӿ�"

class TTrdItfTest : public TTrdItfBase
{
private:
	static CRITICAL_SECTION m_CS;
	static vector<TOrderInfo> m_orders;
	static vector<TTradeInfo> m_deals;
	static LONG m_Order_ID;
	static LONG m_trd_id;
	static LONG m_ref_count;

	float m_rate_per_match;  // ÿ�γɽ��ı���ռ��ί����
	float m_system_cancel_probability; // ϵͳ�����İٷֱ�
	float m_cancel_fault_probability; // ����ʧ�ܵİٷֱȣ����������ֳɽ���
	bool  m_report_withdraw;
  bool  m_use_hq; // �Ƿ�ʹ����ʵ������

	vector<long> m_orderid;
	//TdmPTSDB *m_ptsdb;
	String PTSConStr;
	AnsiString FAccount;
	//vector<TStockInfo> m_positions;

	TPool *FPool;
public:
	TTrdItfTest(const char *psetupfile,ADDLOG plogfunc);
	virtual ~TTrdItfTest();

	// ʵ�����º���
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
	virtual market_type  ConvertMarketType(const char *t){};
	virtual order_type   ConvertOrderType(const char *t){};
	virtual order_state  ConvertOrderState(const char *t){};
	virtual pos_direction ConvertPosDir(const char *t){};
	virtual money_type   ConvertMoneyType(const char *t){};

	virtual char *  ConvertMarketType(market_type t){return "";};
	virtual char *  ConvertOrderType(order_type t){return "";};
	virtual char *  ConvertOrderState(order_state t){return "";};
	virtual char *  ConvertPosDir(pos_direction t){return "";};
	virtual char *  ConvertMoneyType(money_type t){return "";};

	//��������Ϣ������,���û�л�ȡ������������Ϣ����false
	virtual bool GetConfig(void);
	//��������Ϣ��д�������ļ�
	virtual void SetConfig(void);
	//�ر��м������
	virtual void CloseLink(void);
	virtual int  KeepAlive(void);

	void lock_g(void);
	void unlock_g(void);
};


#endif
