//---------------------------------------------------------------------------
#ifndef UTrdItf_ZXH
#define UTrdItf_ZXH
//---------------------------------------------------------------------------
#include "UTrdStruct.h"
#include "UTrdItfBase.h"
#include <IdTCPClient.hpp>
#include <IdIPWatch.hpp>
//---------------------------------------------------------------------------

//?	���ڸ�ʽΪ:YYYY-MM-DD ʱ���ʽΪ:HH:MM:SS

/*
�������Ӧ��������зֱ��ʾ "����������"��"�������ʶ"��"����������"��
���ڸ�ʽΪ:YYYY-MM-DD ʱ���ʽΪ:HH:MM:SS
�������"����������"�������ұߵ�'X'��־��ʾ��������ɲ���,������ʱ�����ַ�����""���롣
���е������ֶΣ��������룬�����룬�����룬�ʽ����룬�������룩������ʹ��
BlowFish�����㷨���ܺ����룬����ʱKEYΪϵͳǩ���"������Կ"��

������	������Ϣ
101	ͨѶ����
110	��δǩ��ϵͳ
111	�޺������ݰ�
301	�ʻ���¼ʧ��
302	�����ʻ�״̬������
303	�ſ��Ų�����
304	�ɶ����벻����
305	�ʲ��ʺŲ�����
306	�û����벻����
307	�����г�������
308	�޸�����ʧ��
309	�������
310	����ʧ��
311	�ⲿ����������
312	���������
401	�˹�Ʊ������
402	��δ��ָ������
403	�˹ɲ��ܽ��д���ί��
404	ί��ʧ��
405	���ý���
406	��Ʊ����
420	�޴�ί��
421	��ί�в��ܳ���
422	��ί���ѳ���
501	�޲�ѯ���
502	��ѯʧ��
601	δ��ͨ����ת��ҵ��
602	δ��ͨ������ת��ҵ��
603	��������δ��ͨ����ҵ��
605	���в�����
604	ת��ʧ��
701	δ��ͨ���۳���ҵ��
801	���óɱ�ʧ��
999	��������

*/

class TTrdItf_ZX : public TTrdItfBase
{
public:
	typedef struct
	{
		char   SvrIp[16];
		int    SvrPort;
		int    TimeOut;

		//1	�绰ί��
		//2	ˢ��ί��
		//3	�ȼ�ί��
		//4	����ί��
		char   entrust_way;               //��������
		char   branch_no[21];             //����վ��
		char   money_type;                //0	�����

	} TZXSet;
	String GenCMD( int data_size, String data );
private:	// User declarations
	TIdTCPClient *FidTcp;
	TZXSet FZXSet;

	char FWorkKey[255];

	//�û�����"��"������֧","�Ự���
	String FUSER_CODE;
	String FBRANCH   ;
	String FSESSION  ;

	AnsiString GetErrorText(int code, char *error);
	AnsiString ReadNextData();
	AnsiString ReadFirstData(AnsiString cmd);
	int  SplitData(AnsiString SD, TStringList *lstDD, int &fieldcount,int &reccount);
        int GetRecvingDataLen(String &InputStr, String TrimStr="|");//20051121--

	int  Init();  //��ʼ��
	int  SetAccount(); //�����ʺ�

	//////��ѯ����//////
	int  GetTrdInfo();   //ȡ���̿�����
	int  QryMoney();     //�ʽ��ѯ -
	int  QryStock();     //�ɷݲ�ѯ
	int  QryCanBuy();    //ȡ��������
	int  QryDetail();    //�ɽ���ѯ -
	int  QryHisDetail(); //��ʷ�ɽ���ѯ
	int  QryCsn();       //��ѯĳ��ί�к�ͬ
	int  QryCurCsn();    //����ί�в�ѯ
	int  QryHisCsn();    //��ʷί�в�ѯ
	int  QryCurTrd();    //���ճɽ���ѯ
	int  QryHisTrd();    //��ʷ�ɽ���ѯ
	int  QryBill();      //��ѯ�ʽ���ˮ�����ʵ���
	int  QryStocks();    //��ѯ�ʺ������еĹɷ�-

	//////���׺���/////
	int  Buy();      //-
	int  Sell();     //-
	int  Undo(); //ί�г���-

	virtual bs_type ConvertType(char * type)
	{
		if(strlen(type)>0)
		{
			if (strcmp(type,"0B")==0)
				return btBuy;
			else if (strcmp(type, "0S")==0)
				return btSell;
			else
			{
				if(type[0]=='1') return btBuy;
				else if(type[0]=='2') return btSell;
			}
		}

		return btNo;
	}

	virtual wt_state ConvertState(char *state)
	{
		if(lstrcmp(state,"�ѳɽ�")==0)
			return wscj;
		else if(lstrcmp(state,"���ڳ���")==0)
			return wsyc;
		else if(lstrcmp(state,"���ֳ���")==0)
			return wsbw;
		else if(lstrcmp(state,"���⳷��")==0)
			return wsyc;
		else if(lstrcmp(state,"��Ʊ����")==0)
			return wsyf;
		else if(lstrcmp(state,"δ�ɽ�")==0)
			return wsyb;
		else if(lstrcmp(state,"���걨")==0)
			return wsyb;
		else if(lstrcmp(state,"��������")==0)
			return wsdc;
		else if(lstrcmp(state,"�����ѷ�")==0)
			return wsdc;
		else
			return wsno;
	}
public:		// User declarations
	TTrdItf_ZX(TZXSet *set);
	virtual  ~TTrdItf_ZX();
	void CloseLink(void)
	{
		FidTcp->Disconnect();
    TTrdItfBase::CloseLink();
	}

};

#endif
