//---------------------------------------------------------------------------

#ifndef uTrdItfImpH
#define uTrdItfImpH

#include "uSession.h"
#include "UTrdItfBase.h"
#include <string>

#define PLUGINNAME "���ڼ���"

////////////////////////////////////////////////////////////////////////////
class TTrdItfImp : public TTrdItfBase
{
public:
	typedef struct
	{
		std::string front_addr;     // ǰ�õ�ַ
		std::string broker_id;		// ���͹�˾����
	} TSetup;

private:	// User declarations
    TSetup FSetup;
    SESSIONPTR FSession;
public:		// User declarations
	TTrdItfImp(const char *psetupfile,ADDLOG plogfunc);
	virtual ~TTrdItfImp();

    //��ʼ��
	int Init();

    //�����ʺ�
	int SetAccount();

	//�ʽ��ѯ
	int QryMoney();

	//����ί�в�ѯ
	int QryCurCsn();

	//���ճɽ���ѯ
	int QryCurTrd();

	//��ѯ�ʺ������еĹɷ�
	int QryStocks();

	//ί�г���
	int Order();
	int Undo();

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

	virtual int KeepAlive(void);
};

//---------------------------------------------------------------------------
#endif
