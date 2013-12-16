//---------------------------------------------------------------------------

#ifndef uItfTrdTrdSvrH
#define uItfTrdTrdSvrH

#include <SysUtils.hpp>
#include <IniFiles.hpp>
#include <StrUtils.hpp>

#include "UItfTrd.h"
#include "UItfTrd1.0.h"
#include "UTrdItfBase.h"
#include "uDmPTSRF.h"
#include "uAtuoQry.h"

#define PLUGINNAME "BHTrdSvr"
//---------------------------------------------------------------------------
class TTrdItf_TrdSvr : public TTrdItfBase
{
private:
	String FUDLFile;
	//bool FAutoGetOrdRep; //if ture autu qry ord by orderid one by one,and save to database
	int FPTrdDllVersion; // 0,1,2 (0 means manual order and fill order no interface)
	String FDllName;// dynamic lib name of PTrdDll_RM.dll
	String FServerInfo; //Remote TrdSvr address and port like ip:port
	TItfTrd *FItfTrd;
	PTRDDLL1::TItfTrd1 *FItfTrd1;
	query_orders FQryOrder;
	TDataModule1 *DataModule1;
protected:
	String FAccount;
public:
	TTrdItf_TrdSvr(const char *psetupfile,ADDLOG plogfunc);
	virtual ~TTrdItf_TrdSvr();

	virtual int  Init();         //��ʼ��

	virtual int  SetAccount();   //��¼��̨�м��

	//////��ѯ����//////
	virtual int  QryMoney();     //�ʽ��ѯ

	virtual int  QryCurCsn();		//����ί�в�ѯ
	
	virtual int  QryCurTrd();    //���ճɽ���ѯ

	virtual int  QryStocks();    //��ѯ�ʺ������еĹɷ�
	
	virtual int  GetLastError();	 //��ȡ������

	//////���׺���/////
	virtual int  Order();        //ί��

	virtual int  Undo();        //ί�г���

	//���ӿڲ���ת��ɱ�׼����
	virtual market_type  ConvertMarketType(const char *t){return mtNo;}
	virtual order_type   ConvertOrderType(const char *t){return otNo;}
	virtual order_state  ConvertOrderState(const char *t){return osno;}
	virtual pos_direction ConvertPosDir(const char *t){return pdNo;}
	virtual money_type   ConvertMoneyType(const char *t){return motNo;}

	virtual char *  ConvertMarketType(market_type t){return "";}
	virtual char *  ConvertOrderType(order_type t){return "";}
	virtual char *  ConvertOrderState(order_state t){return "";}
	virtual char *  ConvertPosDir(pos_direction t){return "";}
	virtual char *  ConvertMoneyType(money_type t){return "";}

	//��������Ϣ������,���û�л�ȡ������������Ϣ����false
	virtual bool GetConfig(void);

	//��������Ϣ��д�������ļ�
	virtual void SetConfig(void);

	//�ر��м������
	virtual void CloseLink(void);

	virtual int  KeepAlive(void);
};


#endif
