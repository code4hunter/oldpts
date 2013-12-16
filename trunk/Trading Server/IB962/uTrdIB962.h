//---------------------------------------------------------------------------

#ifndef uTrdIB962H
#define uTrdIB962H

#include "UTradeDB.h"
#include "uRecvEventsTh.h"
#include "PosixTestClient.h"
#include "UTrdItfBase.h"
#include <IniFiles.hpp>
#include <tchar.h>
//---------------------------------------------------------------------------

#define PLUGINNAME "InteractiveBrokers9.62"

class TTrdItf_IB962 : public TTrdItfBase
{
public:
	typedef struct
	{
		AnsiString host;     // ������ַ
		int port;            // ����˿�
		int seed_orderid;
	} TItfSetup;

private:	// User declarations
	TItfSetup _setup;
	PosixTestClient _client;
	int _clientId;
	RecvEventsTh *_worker;
    //trade_db _db;

public:		// User declarations
	TTrdItf_IB962(const char *psetupfile,ADDLOG plogfunc);
	virtual  ~TTrdItf_IB962();

public:
	int  Init();         //��ʼ��
	int  SetAccount();   //��¼��̨�м��

	//////��ѯ����//////
	int  QryMoney();     //�ʽ��ѯ
	int  QryCurCsn();    //����ί�в�ѯ
	int  QryCurTrd();    //���ճɽ���ѯ
	int  QryStocks();    //��ѯ�ʺ������еĹɷ�

	//////���׺���/////
	int  Order();        //ί��
	int  Undo();         //ί�г���

	//���ӿڲ���ת��ɱ�׼����
	/*�г�����
	0--�ͻ��ţ�*--����Ż�ſ��ţ�#--���д���
	1--�Ϻ�A�ɣ�2--����A�ɣ�3--�Ϻ�B�ɣ�4--����B�ɣ�
	*/
	market_type  ConvertMarketType(const char *t)
	{
		if(strlen(t)<1) return mtNo;
		switch(t[0]) {
		case '1': return mtSHA;
		case '2': return mtSZA;
		default:  return mtNo;
		}
	}

	order_type   ConvertOrderType(const char *t)
	{
		return otNo;
	}

	order_state  ConvertOrderState(const char *t)
	{
		return osno;
	}

	pos_direction ConvertPosDir(const char *t)
	{
		return pdNet;
	}

	/*
	1������ң�2����Ԫ��3���۱ң�4���۹ɸ۱�
	*/
	money_type   ConvertMoneyType(const char *t)
	{
		if( t == NULL ) return motNo;
		if( strcmpi( t ,"RMB" ) == 0 )
		{
			return motRMB;
		}
		else if(strcmpi(t,"USD") == 0)
		{
			return motUSD;
		}
		else  if(strcmpi(t,"HKD") == 0)
		{
			return motHKD;
		}
		else return motNo;
	}

	char *  ConvertMarketType(market_type t)
	{
		switch ( t )
		{
			case mtSHA :return "1";
			case mtSZA :return "2";
			default: return "";
		}
	}

	char *  ConvertOrderType(order_type t)
	{
		/*
        7.	�������ͣ�1���롢2����,0:LOFS�깺,9:LOFS���,Q:��Ȩ��5ת�ɣ�
			(�м�ί��ģʽ:XY,X��ʾ����,1��ʾ��,2��ʾ��,Y��ʾ�м�����,1��ʾ��һ���м�,2��ʾ�ڶ��֡�)

		*/
		switch (t) {
			case otBuy: return "1";
			case otSell: return "2";
			case otETFSub: return "1";
			case otETFRed: return "2";
		default:
			return "";
		}
	}

	char *  ConvertOrderState(order_state t)
	{
		return "";
	}

	char *  ConvertPosDir(pos_direction t)
	{
		return "";
	}

	char *  ConvertMoneyType(money_type t)
	{
		switch (t) {
			case motRMB:
				return "RMB";
			case motUSD:
				return "USD";
			case motHKD:
				return "HKD";
			case motNo:
				return "";
        default:
			;
		}
     	return "";
	}

	//��������Ϣ������,���û�л�ȡ������������Ϣ����false
	bool GetConfig(void)
	{
		if( FSetupFile== NULL ) return false;

		TMemIniFile *ini = new TMemIniFile( FSetupFile );
		try
		{
			// �ж��Ƿ���ڲ�������ã�û�еĻ�����false�Ա�ϵͳ�ܹ�����Ĭ�ϵ�����
			if( ini->SectionExists(PLUGINNAME) == false ) return false;
			_setup.host = ini->ReadString(PLUGINNAME,_T("host"),_setup.host);
			_setup.port = ini->ReadInteger(PLUGINNAME, _T("port"), _setup.port);
			_setup.seed_orderid = ini->ReadInteger(PLUGINNAME, _T("seed_orderid"), _setup.seed_orderid);
		}
		__finally
		{
			delete ini;
		}
		return true;
	}
	//��������Ϣ��д�������ļ�
	void SetConfig(void)
	{
		if( FSetupFile== NULL ) return ;

		TMemIniFile *ini = new TMemIniFile( FSetupFile );
		try
		{
			ini->WriteString(PLUGINNAME, _T("host"), _setup.host);
			ini->WriteInteger(PLUGINNAME, _T("port"), _setup.port);
			ini->WriteInteger(PLUGINNAME, _T("seed_orderid"), _setup.seed_orderid);
			ini->UpdateFile();
		}
		__finally
		{
			delete ini;
		}
	}
	//�ر��м������
	void CloseLink(void);

};


#endif
