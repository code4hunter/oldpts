//---------------------------------------------------------------------------
#ifndef UTrdItf_JSD_GDH
#define UTrdItf_JSD_GDH
//---------------------------------------------------------------------------
#include "UTrdItfBase.h"
#include "JsdGateway.h"
#include <IniFiles.hpp>
#include <tchar.h>

//---------------------------------------------------------------------------

#define PLUGINNAME "���˴�֤ȯv8"

class TTrdItf_JSD_GD : public TTrdItfBase
{
public:
	//enum jsd_entrust_way {zzwt = 1, rjwt, dhwt, kswt, wswt,wzwt,bpwt};

	typedef struct
	{
		AnsiString 	SvrIp;
		int    			SvrPort;
		int    			TimeOut;
		//ί�з�ʽ ��
		// 0--������1--��������2--�绰��3--����ί�С�
		// 4--����ί�� 5-- ETFί�з�ʽ  6--bpwt
		// "ZZWT","RJWT","DHWT","KSWT","WSWT","WZWT","BPWT"
		AnsiString  entrust_way;   //����ί�з�ʽ
		AnsiString 	branch_no;     //Ӫҵ����
		bool        debug_mode;

		AnsiString money_type; // ��ֵ�ڵ�½����̨ʱ��ȡ
	} TJSDSet;
private:	// User declarations

	JsdGateway *_gateway;

	AnsiString ClientIp;

	TJSDSet _setup;

public:		// User declarations
	TTrdItf_JSD_GD(const char *psetupfile,ADDLOG plogfunc);
	virtual  ~TTrdItf_JSD_GD();

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
		if(strlen(t)>0)
		{
			if (strcmp(t,"��")==0)
				return otBuy;
			else if (strcmp(t, "��")==0)
				return otSell;
			else if(strcmp(t, "�깺")==0)
				return otETFSub;
			else if(strcmp(t, "���")==0)
				return otETFRed;
			else
			{
				if(t[0]=='1') return otBuy;
				else if(t[0]=='2') return otSell;
			}
		}

		return otNo;
	}

	order_state  ConvertOrderState(const char *t)
	{
		if(lstrcmp(t,"�ѳɽ�")==0)
			return oscj;
		else if(lstrcmp(t,"���ڳ���")==0)
			return osyc;
		else if(lstrcmp(t,"���ֳ���")==0)
			return osbw;
		else if(lstrcmp(t,"���⳷��")==0)
			return osyc;
		else if(lstrcmp(t,"��Ʊ����")==0)
			return osyf;
		else if(lstrcmp(t,"δ�ɽ�")==0)
			return oswb;
		else if(lstrcmp(t,"���걨")==0)
			return osyb;
		else if(lstrcmp(t,"��������")==0)
			return osdc;
		else if(lstrcmp(t,"�����ѷ�")==0)
			return osdc;
		else
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
		if( strcmp( t ,"�����" ) == 0 )
		{
			return motRMB;
		}
		else if(strcmp(t,"��Ԫ") == 0)
		{
			return motUSD;
		}
		else  if(strcmp(t,"�۱�") == 0)
		{
			return motHKD;
		}
		else  if(strcmp(t,"�۹ɸ۱�") == 0)
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
			_setup.SvrIp = ini->ReadString(PLUGINNAME,_T("SvrIp"),_setup.SvrIp);
			_setup.SvrPort = ini->ReadInteger(PLUGINNAME, _T("SvrPort"), _setup.SvrPort);
			_setup.TimeOut = ini->ReadInteger(PLUGINNAME, _T("Timeout"), _setup.TimeOut);
			_setup.entrust_way = ini->ReadString(PLUGINNAME, _T("EntrustWay"), _setup.entrust_way);
			_setup.branch_no = ini->ReadString(PLUGINNAME, _T("BranchNo"), _setup.branch_no);
			_setup.debug_mode = ini->ReadBool(PLUGINNAME, _T("DebugMode"), _setup.debug_mode);
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
			ini->WriteString(PLUGINNAME, _T("SvrIp"), _setup.SvrIp);
			ini->WriteInteger(PLUGINNAME, _T("SvrPort"), _setup.SvrPort);
			ini->WriteInteger(PLUGINNAME, _T("Timeout"), _setup.TimeOut);
			ini->WriteString(PLUGINNAME, _T("EntrustWay"), _setup.entrust_way);
			ini->WriteString(PLUGINNAME, _T("BranchNo"), _setup.branch_no);
			ini->WriteBool(PLUGINNAME, _T("DebugMode"), _setup.debug_mode);
			ini->UpdateFile();
		}
		__finally
		{
			delete ini;
		}
	}
	//�ر��м������
	void CloseLink(void)
	{
		_gateway->Disconnect();
	}

};

#endif
