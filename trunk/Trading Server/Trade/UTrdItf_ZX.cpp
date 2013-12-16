//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdItf_ZX.h"
#include <assert.h>
#include <StrUtils.hpp>
#include <DateUtils.hpp>

#pragma package(smart_init)

#define DEF_HEAD_LEN            9
#define INDEX(field,record,n)   (DEF_HEAD_LEN + field + record*field + n - 1)
#define DEF_ACK_OK              0
#define DEF_ACK_ERROR           -1
#define DEF_TIMEOUT             -100
#define DEF_INVALID_STOCKCODE   -101
#define DEF_OTHER_ERROR         -504
#define _SH                     "10"
#define _SZ                     "00"

static HMODULE h_kdgtmm = NULL;

typedef (*pfunc_KDGT_CRC)(unsigned char* lpinbuf, int nlen, unsigned char *lpoutcrccode);
typedef (*pfunc_KDGT_Encrypt)(unsigned char *lpszkey, unsigned char* lpinbuf, int nlen, unsigned char *lpoutbuf);
typedef (*pfunc_KDGT_Decrypt)(unsigned char *lpszkey, unsigned char* lpinbuf, int nlen, unsigned char *lpoutbuf);

static pfunc_KDGT_CRC KDGT_CRC = NULL;
static pfunc_KDGT_Encrypt KDGT_Encrypt = NULL;
static pfunc_KDGT_Decrypt KDGT_Decrypt = NULL;
static LONG link_count_ZX=0;

unsigned char * KEY   = "SZKINGDOM";
const char * REQ_HEAD = "%%04d|%04d|%8s|KDGATEWAY1.0|%s|%s|%s|%c|%s|%s|%s|%s|";
const int  NEXT_FLAG  = 6;   // ������
//---------------------------------------------------------------------------
String GetDate(void)
{
	return Now().FormatString("yyyy-mm-dd");
}

String ReplaceCRC(const String cmd,const char* to)
{
	return cmd.SubString(1,10) + to + cmd.SubString(19,cmd.Length() - 18) ;//20051121---19==>18
}

String CRC(const String cmd)
{
	char szCRC[20];
	KDGT_CRC( cmd.c_str(),cmd.Length(),szCRC);
	// ����crc�ֶ�
	return ReplaceCRC( cmd, szCRC );
}

String TTrdItf_ZX::GenCMD( int data_size, String data )
{
	AnsiString cmd;
	cmd.printf(REQ_HEAD,data_size,FWorkKey,FUSER_CODE.c_str(),FZXSet.branch_no,FBRANCH.c_str(),
		FZXSet.entrust_way,FSESSION.c_str(),"","","" ) ;

	cmd.printf(String(cmd).c_str(),cmd.Length());
	cmd=cmd+data ;

	return CRC(cmd);
}

TTrdItf_ZX::TTrdItf_ZX(TZXSet *set)
{
	CopyMemory(&FZXSet,set,sizeof(TZXSet));
	FidTcp = new TIdTCPClient(NULL);
	FWorkKey[0]= 0;
}

TTrdItf_ZX::~TTrdItf_ZX()
{
	FidTcp->Disconnect();
	delete FidTcp;

	InterlockedDecrement(&link_count_ZX);
	if( link_count_ZX<=0 && h_kdgtmm)
	{
		FreeLibrary(h_kdgtmm);
	}
}

AnsiString TTrdItf_ZX::ReadNextData()
{
	AnsiString cmd = GenCMD( 3, "99|" );
	return ReadFirstData(cmd);
}

AnsiString TTrdItf_ZX::ReadFirstData(AnsiString cmd)
{
	//cmd = "0040|0004|00000000|KDGATEWAY1.0|||||||||100|" ;
	//����ϴεķ�����Ϣ
	int n = FidTcp->ReadFromStack(true, 1, true, NULL);
	if (n > 0) FidTcp->ReadString(n);
	//#ifndef _DEBUG//20051122
	//	ODS("send=%s",cmd.c_str());
	//#endif        
	FidTcp->Write(cmd);

	n = FidTcp->ReadFromStack(true, FZXSet.TimeOut, true, NULL);
	if (n <= 0)
	{
		ODS("�������ݳ�ʱ");
		return ""  ;
	}

	AnsiString ret = FidTcp->ReadString(n);

	//#ifdef _DEBUG//20051121---��ѯ�ɷ���Ϣʱ�������ݲ�û����ȫ

	int nTolLen = GetRecvingDataLen(ret);
	if(n < nTolLen)
	{
		int nCurLen = n;
		TDateTime dtTime = Now();
		for(;;)
		{
			n = FidTcp->ReadFromStack(true, FZXSet.TimeOut, true, NULL);
			if (n <= 0)
			{
				ODS("�������ݳ�ʱ");
				return ""  ;
			}
			nCurLen += n;
			ret += FidTcp->ReadString(n);
			if(nCurLen >= nTolLen)
				break;

			if(MilliSecondsBetween(dtTime, Now()) > FZXSet.TimeOut)
			{
				ODS("�������ݳ�ʱ");
				return ""  ;
			}
		}
	}
    
	//#endif
	//#ifndef _DEBUG//20051122
	//	ODS("ret=%s",ret.c_str());
	//#endif        

	return ret;
}

int TTrdItf_ZX::SplitData(AnsiString SD, TStringList *lstDD,int &fieldcount,int &reccount)
{
	//char seps[] = "|";
	//char *substr;
	//char *data;
	assert(lstDD != NULL);

	lstDD->Clear();
	try
	{
		SD = SD.Trim();
		/*		data = new char[SD.Length() + 1];
		memset(data, 0, SD.Length() + 1);
		strncpy(data, SD.c_str(), SD.Length());

		substr = strtok(data, seps);
		#ifndef _DEBUG
		while (substr != NULL)
		{
		lstDD->Add(substr);
		substr = strtok(NULL, seps);
		}
		#else*///20051122
		int nCurPos = 0;
		for(;;)//Ӧ���ͷ�ṹ: ͷ���� CHAR(4),ǰ�����ַ���0�����;���ݳ��� VARCHAR(n),ǰ�����ַ���0�����
		{
			nCurPos = SD.Pos("|");
			if(nCurPos > 1)
				lstDD->Add(SD.SubString(1, nCurPos-1));
			else if(nCurPos == 1)
				lstDD->Add("");
			else //if(nCurPos <= 0 )
			{
				//ע:���һ�����ݿ�������û������"|"---
				if(!SD.IsEmpty())
				{
					lstDD->Add(SD);
				}

				break;
			}

			SD.Delete(1, nCurPos);
		}
		//#endif
	}
	__finally
	{
		//delete []data;
	}

	if (lstDD->Count < DEF_HEAD_LEN)
	{
		ODS("�����ֶ�С����Ӧ����ͷ�ֶ���!");
		return DEF_ACK_ERROR;
	}

	if (lstDD->Strings[4] != "0")
	{
		ODS("�����벻��0��������:%s,������ϢΪ%s", lstDD->Strings[4].c_str(),
			lstDD->Strings[5].c_str());
		return DEF_ACK_ERROR;
	}

	reccount =  lstDD->Strings[8].ToIntDef(0);
	//if (lstDD->Count != lstDD->Strings[7].ToIntDef(0) * reccount)
	if(lstDD->Count-DEF_HEAD_LEN != lstDD->Strings[7].ToIntDef(0) * (1+reccount))//20051121---�����һ��
	{
		ODS("Count = %d,Ӧ���ֶ���=%s,Ӧ���¼��=%s",lstDD->Count,
			lstDD->Strings[7].c_str(),lstDD->Strings[8].c_str());
		return DEF_ACK_ERROR;///
	}

	if( fieldcount > lstDD->Strings[7].ToIntDef(0) )
	{
		return DEF_ACK_ERROR;
	}

	fieldcount = lstDD->Strings[7].ToIntDef(0);

	return DEF_ACK_OK;
}

int TTrdItf_ZX::Init()  //��ʼ��
{
	if( h_kdgtmm == NULL )
		h_kdgtmm = LoadLibrary("KdGTmm.dll");

	if( KDGT_CRC ==  NULL )
	{
		KDGT_CRC = (pfunc_KDGT_CRC)GetProcAddress(h_kdgtmm, "KDGT_CRC");
	}

	if (KDGT_Encrypt == NULL)
	{
		KDGT_Encrypt = (pfunc_KDGT_Encrypt)GetProcAddress(h_kdgtmm, "KDGT_Encrypt");
	}

	if( KDGT_Decrypt == NULL )
	{
		KDGT_Decrypt = (pfunc_KDGT_Decrypt)GetProcAddress(h_kdgtmm, "KDGT_Decrypt");
	}

	if (KDGT_CRC == NULL || KDGT_Encrypt == NULL || KDGT_Decrypt == NULL)
	{
		return -1;
	}

	InterlockedIncrement(&link_count_ZX);

	try
	{
		if (!FidTcp->Connected())
		{
			FidTcp->Host = FZXSet.SvrIp;
			FidTcp->Port = FZXSet.SvrPort;
			FidTcp->Connect();

			AnsiString cmd;
			// ����ͷ
			cmd.printf(REQ_HEAD,4,"","",FZXSet.branch_no,"",FZXSet.entrust_way,"","","","" ) ;
			cmd.printf( String(cmd).c_str(), cmd.Length()) ;
			// ��������
			cmd += "100|" ;

			//cmd = "0069|0005|ac82aefb|KDGATEWAY1.0|2247|00909627a566|103|3|00000000|2|||201||";
			// ����
			TStringList *lstDD = new TStringList();
			int fcount = 1;
			int reccount = 0;
			if (SplitData(ReadFirstData(cmd), lstDD, fcount,reccount) == DEF_ACK_OK)
			{
				if (lstDD->Strings[INDEX(fcount,0,1)].Length() > 0)
				{
					String szTmp = lstDD->Strings[INDEX(fcount,0,1)];
					KDGT_Decrypt( KEY,szTmp.c_str(),szTmp.Length(),FWorkKey);
				}
			}
			delete lstDD;
		}
	}
	catch (...)
	{
		ODS("���ӹ�̨ʧ��!");
	}

	return (FidTcp->Connected()==true && strlen(FWorkKey) == 8) ? 0 : -1;
}

//--------------------------------------------------------------------------
/*
�û���¼(301)
���ܴ���	301
��������	�û���¼
��������	������	��ʶ	���ͼ�����	��Ҫ	����
�û���ʶ����	USER_ID_CLS	CHAR��2��	Y
�û���ʶ	USER_ID	CHAR��65��	Y
��������	USER_PWD	CHAR��32��	Y	���ܺ��ַ�
��������	������	��ʶ	���ͼ�����	����
�����г�	MARKET	CHAR(2)
�ɶ�����	SECU_ACC	CHAR(10)
�ɶ�����	SECU_ACC_NAME	VARCHAR(16)
ȱʡ�ʲ��ʺ�	ACCOUNT	VARCHAR(20)
�ͻ�����	USER_CODE	INT
�ͻ�����	USER_NAME	VARCHAR(16)
������֧	BRANCH	INT
�Ự���	SESSION	CHAR(16)
��������	�������	������Ϣ
301	�ʻ���¼ʧ��
302	�����ʻ�״̬������
303	�ſ��Ų�����
304	�ɶ����벻����
305	�ʲ��ʺŲ�����
306	�û����벻����
307	�����г�������
309	�������
��ע��Ϣ	�û���ʶ����:
?	'Z'��ʾ���ʲ��ʺŵ�¼  �û���ʶΪ�ʲ��ʺ�
?	'U'��ʾ���û������¼  �û���ʶΪ�û�����
?	'C'��ʾ�Դſ���¼      �û���ʶΪ�ſ���
?	'01'��'12' �����г�    �û���ʶΪ��Ӧ�г��Ĺɶ�����

�˷���Ϊ�����������ʲ��ʺţ��û����룬�ſ���½ʱ����ÿ���г������ɶ������򷵻ض�Ӧ�Ĺɶ�
����������������룬���ܲ���BlowFish����
�����Ϊ���¼

Send:0218|0029|280fa8ef|KDGATEWAY1.0|05857182|0010dc04fa9b|||||05857182||||301|U|10161|F9A0431B95567FDE|
RECV:0059|0000|d2c70905|KDGATEWAY1.0|611|��֤��Ϣû������|0|0|0|
Send:0052|0034|384595ab|KDGATEWAY1.0||0010dc04fa9b|||||||301|Z|2100801000|F9A0431B95567FDE|
RECV:0051|0000|ef4e9dea|KDGATEWAY1.0|313|��������|0|0|0|
*/
int TTrdItf_ZX::SetAccount() //�����ʺ�
{
	AnsiString cmd;


	TStringList *lstDD = new TStringList();

	try
	{
		String USER_ID_CLS;

		if(FRequest.SetAccount.Sort == asCA)
		{
			USER_ID_CLS="Z";
		}
		else if(FRequest.SetAccount.Sort==asSH)
		{
			USER_ID_CLS=_SH;
		}
		else if(FRequest.SetAccount.Sort==asSZ)
		{
			USER_ID_CLS=_SZ;
		}
		else
			return -1;

		char szEPwd[100];
		KDGT_Encrypt(/*KEY*/FWorkKey,FRequest.SetAccount.PW,strlen(FRequest.SetAccount.PW),
			szEPwd);//20051121---KEY==>FWorkKey

		String data;
		data.printf( "301|%2s|%s|%s|",USER_ID_CLS , FRequest.SetAccount.Account,szEPwd) ;

		cmd.printf(REQ_HEAD,data.Length(),FWorkKey,"",FZXSet.branch_no,"",FZXSet.entrust_way,"","","","" ) ;
		cmd.printf(String(cmd).c_str(),cmd.Length()) ;
		cmd+= data;

		cmd = CRC(cmd);

		int fcount = 8;
		int reccount = 0;

		if (SplitData(ReadFirstData(cmd), lstDD, fcount, reccount) == DEF_ACK_OK)
		{
			strncpy(FAccInfo.Capital, lstDD->Strings[INDEX(fcount,0,4)].c_str(), 13);
			strncpy(FAccInfo.PW, FRequest.SetAccount.PW, 13);

			FUSER_CODE = lstDD->Strings[INDEX(fcount,0,5)] ;
			FBRANCH    = lstDD->Strings[INDEX(fcount,0,7)] ;
			FSESSION   = lstDD->Strings[INDEX(fcount,0,8)] ;

			goto next;
			while (lstDD->Strings[NEXT_FLAG]=="1")
			{
				if (SplitData(ReadNextData(), lstDD, fcount, reccount) == DEF_ACK_OK)
				{
next:
					for( int i = 0; i<reccount; i++ )
					{
						if(  lstDD->Strings[INDEX(fcount,i,1)] == _SH )
						{
							//lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,13);
							//#ifdef _DEBUG//20051121---�������������?
							lstrcpyn(FAccInfo.SH, lstDD->Strings[INDEX(fcount,i,2)].c_str(), 13);
							//#endif
						}
						else if ( lstDD->Strings[INDEX(fcount,i,1)] == _SZ  )
						{
							//lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,13);
							//#ifdef _DEBUG//20051121---�������������?
							lstrcpyn(FAccInfo.SZ, lstDD->Strings[INDEX(fcount,i,2)].c_str(), 13);
							//#endif

						}
					}
				}
			}


			if(FRequest.SetAccount.Sort==asSH)
			{
				lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,13);
			}
			else if(FRequest.SetAccount.Sort==asSZ)
			{
				lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,13);
			}

			if(FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) { return -1; }

			NewAns(1);
			memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));
		}
		else
		{
			return -1;
		}


	}
	__finally
	{
		delete lstDD;
	}

	return 0;
}

//////��ѯ����//////
// ��ʱ�����ѯ��v5.83����60
int TTrdItf_ZX::GetTrdInfo()   //ȡ���̿�����
{
	return -1;
}

/*��ѯ�ʽ����Ϳ����ʽ����
�ʽ��ѯ(502)

���ܴ���	502
��������	�ʽ��ѯ
��������	������	��ʶ	���ͼ�����	��Ҫ	����
�ͻ�����	USER_CODE	INT	Y	
�ʲ��˺�	ACCOUNT	VARCHAR(20)       	N	
����	CURRENCY	CHAR(1)	N	
��������	������	��ʶ	���ͼ�����	����
�ͻ�����	USER_CODE	INT
�ʲ��˻�	ACCOUNT	VARCHAR(20)
��֧����	BRANCH	INT
����	CURRENCY	CHAR(1)
�ʽ����	BALANCE	DECIMAL(16,2)
�ʽ���ý��	AVAILABLE	DECIMAL(16,2)
�쳣������	FROZEN	DECIMAL(16,2)	
���׶�����	TRD_FRZ	DECIMAL(16,2)	
�����ֽ���	DRAW_AVL_CASH	DECIMAL(16,2)	
����֧Ʊ���	DRAW_AVL_CHEQUE	DECIMAL(16,2)	
��ת�˽��	TRANSFER_AVL	DECIMAL(16,2)
��������	�������	������Ϣ
306	�û����벻����
305	�ʲ��ʺŲ�����
501	�޲�ѯ���
502	��ѯʧ��
��ע��Ϣ	
*/
int TTrdItf_ZX::QryMoney()     //�ʽ��ѯ
{
	String data;
	data.printf("502|%s|%s|%c", FUSER_CODE.c_str() ,
		this->FAccInfo.Capital,
		FZXSet.money_type);

	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 11;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			NewAns(1);
			(*FAnswer)[0].QryMoney.Balance = StrToFloatDef(lstDD->Strings[INDEX(fcount,0,5)] ,0);
			(*FAnswer)[0].QryMoney.Available = StrToFloatDef(lstDD->Strings[INDEX(fcount,0,6)],0);
		}
		else
		{
			return -1;
		}
	}
	__finally
	{
		delete lstDD;
	}

	return 0;
}

int TTrdItf_ZX::QryStock()     //�ɷݲ�ѯ
{
	return -1;
}

int TTrdItf_ZX::QryCanBuy()    //ȡ��������
{
	return -1;
}

/*
���ܴ���	505
��������	ί�в�ѯ
��������	������	��ʶ	���ͼ�����	��Ҫ	����
��ʼ����	BEGIN_DATE	CHAR(10)	Y	1
��ֹ����	END_DATE	CHAR(10)	Y	2
��ѯί��ģʽ	GET_ORDERS_MODE	CHAR(1)	Y	3
�ͻ�����	USER_CODE	INT	Y	4
�����г�	MARKET	CHAR(2)        	N	5
�ɶ�����	SECU_ACC	VARCHAR(10)    	N	6
֤ȯ����	SECU_CODE	VARCHAR��8��	N	7
������Ϊ	TRD_ID	CHAR(2)        	N	8
ҵ�����	BIZ_NO	VARCHAR(10)    	N	9
��ͬ���	ORDER_ID	VARCHAR(10)	N	10
��֧����	BRANCH	INT   	N
�ʲ��˻�	ACCOUNT	VARCHAR(20)	N
�ⲿ����	EXT_INST	INT	N	��������ʱ��

505|%10s|%10s|0|%s|%2s|||  ||%s||||
��������	������	��ʶ	���ͼ�����	����
1ί������	ORDER_DATE	CHAR(10)
2��������	TRD_DATE	CHAR(10)
3�ͻ�����	USER_CODE	VARCHAR(20)
-�ͻ�����	USER_NAME	VARCHAR(16)	ɾ��20031228
4�ʲ��˻�	ACCOUNT	VARCHAR(20)
5����	CURRENCY	CHAR(1)
6��֧����	BRANCH	INT
7�ɶ�����	SECU_ACC	VARCHAR(10)
8�ɶ�����	SECU_NAME	VARCHAR(16)	����20031228
9������Ϊ	TRD_ID	CHAR(2)
10ҵ�����	BIZ_NO	VARCHAR(10)
11��ͬ���	ORDER_ID	VARCHAR(10)
12�����г�	MARKET	CHAR(2)
13֤ȯ����	SECU_NAME	VARCHAR(16)
14֤ȯ����	SECU_CODE	VARCHAR(8)
-����ϯλ	SEAT	VARCHAR(6)	ɾ��20031228
15�۸�	PRICE	DECIMAL(10,3)
16����	QTY	INT
17ί�н��	ORDER_AMT	DECIMAL(16,2)
18ί�ж�����	ORDER_FRZ_AMT	DECIMAL(16,2)
-�ʽ���ý��	AVAILABLE	DECIMAL(16,2)	ɾ��20031228
19�ɷݿ���	SHARE_AVL	INT	ɾ��20031228
20������־	IS_WITHDRAW	CHAR(1)
21�ѳ�����־	IS_WITHDRAWN	CHAR(1)
22�ɳ�����־	CAN_WITHDRAW	CHAR(1)	ɾ��20031228 �ָ����ֶ�20040101
23���ͱ�־	DCL_FLAG	CHAR(1)
-����ʱ��	DCL_TIME	CHAR(8)	ɾ��20031228
24�Ϸ���־	VALID_FLAG	CHAR(1)
25�ɽ�����	MATCHED_QTY	INT
26�ѳ�������	WITHDRAWN_QTY	INT
27�ɽ����	MATCHED_AMT	DECIMAL(16,2)
-ʵʱ������	RLT_SETT_AMT	DECIMAL(16,2)	ɾ��20031228
28������ע	OP_REMARK	VARCHAR(64)
-����	INITIATOR	CHAR(1)	ɾ��20031228
29�ⲿ����	EXT_INST	SMALLINT
-�ⲿ�˻�	EXT_ACC	VARCHAR(32)	ɾ��20031228
-�ⲿ���˻�	EXT_SUB_ACC	VARCHAR(32)	ɾ��20031228
-�ⲿ������	EXT_FRZ_AMT	DECIMAL(16,2)	ɾ��20031228
30�ⲿ��¼��	EXT_REC_NUM	INT
-�������ⲿ�ʽ�	EXT_SETT_AMT	DECIMAL(16,2)	ɾ��20031228
31�ⲿҵ���	EXT_BIZ_NO	VARCHAR(10)	����20031228
32�ⲿ��ͬ��	EXT_ORDER_ID	VARCHAR(10)	����20031228

��������	�������	������Ϣ
306	�û����벻����
501	�޲�ѯ���
502	��ѯʧ��
��ע��Ϣ	 	����              <I>:ȯ�̷���<O>:�ⲿ��������,<A>:˫������
��ѯί��ģʽ		<0>:����ί�У�<1>:�ɳ�ί�У�<2>:�Ƿ�ί��
������־			<0>:����ί�У�<1>:����ί��
�ѳ�����־			<0>:δ������<1>:�ѳ���
�ɳ�����־			<0>:����������<1>:������
���ͱ�־			<0>:δ���ͣ�<1>:�ѷ���
����ʱ��			��ʽ��HH:MM:SS
�Ϸ���־			<0>:�Ϸ���<1>:�Ƿ�
��֤ȯ��������ͽ����г�

*/
int TTrdItf_ZX::QryDetail()    //�ɽ���ѯ
{
	if(FRequest.QryDetail.ContractID[0]==0) return -1;

	String market;
	switch (FRequest.QryDetail.Bourse)
	{
	case bsSH : market = _SH; break;
	case bsSZ : market = _SZ; break;
	default: return -1;
	}

	String data;
	String date = GetDate();

	//data.printf("505|%10s|%10s|0|%s|%2s|||||%s||||",date.c_str(),date.c_str(),
	//	FUSER_CODE ,market,
	//	FRequest.QryDetail.ContractID);
	//#ifdef _DEBUG//20051122---ע:��֤���캣��ʾ����ͬ�ŷ��ڵ�9�ֶ�,�ĵ����ǵ�10�ֶ�
	data.printf("505|%10s|%10s|0|%s|%2s||||%s|||||",date.c_str(),date.c_str(),
		FUSER_CODE.c_str() ,market.c_str(),
		FRequest.QryDetail.ContractID);
	//#endif                

	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 32;
		int reccount = 0;

		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			NewAns(1);
			(*FAnswer)[0].QryDetail.Num  =  lstDD->Strings[INDEX(fcount,0,23)].ToIntDef(0);
			(*FAnswer)[0].QryDetail.UndoNum=lstDD->Strings[INDEX(fcount,0,32)].ToIntDef(0);//20051122---24(CAN_WITHDRAW)==>32(WITHDRAWN_QTY)
			if( (*FAnswer)[0].QryDetail.Num >0)
				(*FAnswer)[0].QryDetail.Price=  StrToFloatDef(lstDD->Strings[INDEX(fcount,0,25)],0)/
				(*FAnswer)[0].QryDetail.Num;
			else  (*FAnswer)[0].QryDetail.Price= 0;
		}
		else
		{
			return -1;
		}
	}
	__finally
	{
		delete lstDD;
	}
	return 0;
}

int TTrdItf_ZX::QryHisDetail() //��ʷ�ɽ���ѯ
{
	// ��ʱ����
	return -1;
}

int TTrdItf_ZX::QryCsn()       //��ѯĳ��ί�к�ͬ
{
	// ��ʱ����
	return -1;
}

int TTrdItf_ZX::QryCurCsn()    //����ί�в�ѯ
{
	TList * lstAns = new TList();
	//if(FRequest.QryDetail.ContractID[0]==0) return -1;
	//if(FRequest.QryCurCsn.==0) return -1;//20051122---�����һ�� ,ֻ��Ĭ��Ϊһ��������

	//String market;
	//#ifdef _DEBUG//20051122---
	//    market = _SH;//ֻ��Ĭ��Ϊһ��������
	//#else
	/*	switch (FRequest.QryDetail.Bourse)
	{
	case bsSH : market = _SH; break;
	case bsSZ : market = _SZ; break;
	default: return -1;
	}*/
	//#endif

	String data;
	String date = GetDate();

	data.printf("505|%10s|%10s|0|%s||||  ||||||",date.c_str(),date.c_str(),
		FUSER_CODE.c_str());
	//#ifdef _DEBUG//20051122---ҪôĬ���Ͻ���Ҫô��ѯ����ί��
	//       data.printf("505|%10s|%10s|0|%s||||||||||",date.c_str(),date.c_str(),
	//		FUSER_CODE);
	//#endif        

	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 32;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			goto ADD;

			while (lstDD->Strings[NEXT_FLAG]=="1")
			{
				if (SplitData(ReadNextData(), lstDD,  fcount,reccount) == DEF_ACK_OK)
				{
ADD:
					for ( int i =0; i<reccount; i++ )
					{
						TConsignInfo *ci = new TConsignInfo;
						memset(ci, 0, sizeof(TConsignInfo));

						strncpy(ci->ContractID,lstDD->Strings[INDEX(fcount,i,11)].c_str(), 8);
						strncpy(ci->SecuID,    lstDD->Strings[INDEX(fcount,i,14)].c_str(), 7);
						strncpy(ci->SecuDesc,  lstDD->Strings[INDEX(fcount,i,13)].c_str(), 8);
						strncpy(ci->Time,      "", 8);
						strncpy(ci->Date,      "", 8);

						ci->Bourse = (lstDD->Strings[INDEX(fcount,i,12)]==_SH) ? bsSH : bsSZ;

						ci->Type =ConvertType(lstDD->Strings[INDEX(fcount,i,9)].c_str());

						ci->State  = 'N';
						ci->CsnVol = StrToIntDef(lstDD->Strings[INDEX(fcount,i,16)], 0);
						ci->TrdVol = StrToIntDef(lstDD->Strings[INDEX(fcount,i,23)], 0);//20051122---25==>23
						ci->CancelVol = StrToIntDef(lstDD->Strings[INDEX(fcount,i,32)], 0);//20051122---26==>32
						ci->CsnPrice  = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,15)], 0);
						if( ci->TrdVol >0)
							ci->TrdPrice  = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,25)], 0) / ci->TrdVol;//20051122---27==>25

						lstAns->Add(ci);
					}
				}
			}

			if (lstAns->Count > 0)
			{
				NewAns(lstAns->Count);
				for ( int i = 0; i < lstAns->Count; i++ )
				{
					TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
					memcpy(&(*FAnswer)[i].QryCurCsn.CsgInfo, ci, sizeof(TConsignInfo));
				}
			}

			for ( int i = 0; i < lstAns->Count; i++ )
			{
				TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
				delete ci;
			}
			lstAns->Clear();
		}
		else
		{
			return -1;
		}
	}
	__finally
	{
		delete lstDD;
		delete lstAns;
	}
	return 0;

}

int TTrdItf_ZX::QryHisCsn()    //��ʷί�в�ѯ
{
	return -1;
}

/*
�ɽ���ѯ(506) [֧����������]
���ܴ���	506
��������	�ɽ���ѯ
��������	������	��ʶ	���ͼ�����	��Ҫ	����
��ʼ����	BEGIN_DATE	CHAR(10)	Y
��ֹ����	END_DATE	CHAR(10)	Y
�ͻ�����	USER_CODE	INT	Y
�����г�	MARKET	CHAR(2)	N
�ɶ�����	SECU_ACC	CHAR(10)	N
֤ȯ����	SECU_CODE	VARCHAR��8��	N	
������Ϊ	TRD_ID	CHAR(2)        	N	
��ͬ���	ORDER_ID	VARCHAR(10)    	N	
��֧����	BRANCH	INT   	N	
�ʲ��˻�	ACCOUNT	CHAR(20)        	N	
�ⲿ����	EXT_INST	INT	N	��������ʱ��
506|%10s|%10s|%s|%2s||||||||
��������	������	��ʶ	���ͼ�����	����
1ί������	ORDER_DATE	CHAR(10)
2��������	TRD_DATE	CHAR(10)
3�ͻ�����	USER_CODE	INT
-�ͻ�����	USER_NAME	VARCHAR(16)	ɾ��20031229
4�ʲ��˻�	ACCOUNT	VARCHAR(20)
5����	CURRENCY	CHAR(1)
6��֧����	BRANCH	INT
7�ɶ�����	SECU_ACC	VARCHAR(10)
8�ɶ�����	SECU_ACC_NAME	VARCHAR(16)	����20031229
9������Ϊ	TRD_ID	CHAR(2)
10��ͬ���	ORDER_ID	VARCHAR(10)
11�����г�	MARKET	CHAR(2)
12֤ȯ����	SECU_NAME	VARCHAR(16)
13֤ȯ����	SECU_CODE	VARCHAR(8)
-����ϯλ	SEAT	VARCHAR(6)	ɾ��20031228
14�۸�	PRICE	DECIMAL(10,3)
15����	QTY	INT
-ί�н��	ORDER_AMT	DECIMAL(16,2)	ɾ��20031228
16ί�ж�����	ORDER_FRZ_AMT	DECIMAL(16,2)
-�ʽ���ý��	AVAILABLE	DECIMAL(16,2)	ɾ��20031228
17�ɷݿ���	SHARE_AVL	INT	ɾ��20031228
-������־	IS_WITHDRAW	CHAR(1)	ɾ��20031228
-����ʱ��	DCL_TIME	CHAR(8)	ɾ��20031228
18�ɽ�ʱ��	MATCHED_TIME	CHAR(8)
19�ɽ����	MATCHED_SN	VARCHAR(32)
20�ɽ��۸�	MATCHED_PRICE	DECIMAL(10,3)
21�ɽ�����	MATCHED_QTY	INT
22�ɽ����	MATCHED_AMT	DECIMAL(16,2)
23ʵʱ������	RLT_SETT_AMT	DECIMAL(16,2)
24������ע	OP_REMARK	VARCHAR(64)
-����	INITIATOR	CHAR(1)	ɾ��20031228
25�ⲿ����	EXT_INST	SMALLINT	
-�ⲿ�˻�	EXT_ACC	VARCHAR(32)	ɾ��20031228
-�ⲿ���˻�	EXT_SUB_ACC	VARCHAR(32)	ɾ��20031228
-�ⲿ������	EXT_FRZ_AMT	DECIMAL(16,2)	ɾ��20031228
-�ⲿ��¼��	EXT_REC_NUM	INT	ɾ��20031228
-�������ⲿ�ʽ�	EXT_SETT_AMT	DECIMAL(16,2)	ɾ��20031228
��������	�������	������Ϣ
306	�û����벻����
501	�޲�ѯ���
502	��ѯʧ��
��ע��Ϣ	 	����              <I>:ȯ�̷���<O>:�ⲿ��������,<A>:˫������
������־			<0>:����ί�У�<1>:����ί��

*/
int TTrdItf_ZX::QryCurTrd()    //���ճɽ���ѯ
{
	TList * lstAns = new TList();
	TStringList *lstDD = new TStringList();

	String data;
	String date = GetDate();
	data.printf("506|%10s|%10s|%s|||||||||",date.c_str(),date.c_str(),
		FUSER_CODE.c_str());

	AnsiString cmd = GenCMD( data.Length(), data  );

	try
	{
		int fcount = 25;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			goto ADD;
			while (lstDD->Strings[NEXT_FLAG]=="1")
			{
				if (SplitData(ReadNextData(), lstDD,  fcount,reccount) == DEF_ACK_OK)
				{
ADD:
					for( int i=0; i < reccount; i++ )
					{
						TTradeInfo *ti = new TTradeInfo;
						memset(ti, 0, sizeof(TTradeInfo));

						strncpy(ti->SecuID,   lstDD->Strings[INDEX(fcount,i,13)].c_str(), 7);
						strncpy(ti->SecuDesc, lstDD->Strings[INDEX(fcount,i,12)].c_str(), 8);
						strncpy(ti->Time,     lstDD->Strings[INDEX(fcount,i,18)].c_str(), 8);
						strncpy(ti->Date,     Now().FormatString("yyyymmdd").c_str(), 8);
						ti->Type  = ConvertType(lstDD->Strings[INDEX(fcount,i,9)].c_str());
						ti->Vol   = StrToIntDef(lstDD->Strings[INDEX(fcount,i,21)], 0);//20051122---�ɽ���Ϊ��������?
						ti->Price = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,20)], 0);

						lstAns->Add(ti);
					}
				}
				else
				{
					return -1;
				}
			}

			if (lstAns->Count > 0)
			{
				NewAns(lstAns->Count);
				for( int i = 0; i < lstAns->Count; i++ )
				{
					TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
					memcpy(&(*FAnswer)[i].QryHisTrd.TrdInfo, ti, sizeof(TTradeInfo));
				}
			}

			for ( int i = 0; i < lstAns->Count; i++ )
			{
				TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
				delete ti;
			}
			lstAns->Clear();
		}
		else
		{
			return -1 ;
		}
	}
	__finally
	{
		delete lstDD;
		delete lstAns;
	}

	return 0;
}

int TTrdItf_ZX::QryHisTrd()    //��ʷ�ɽ���ѯ
{
	return -1;
}

int TTrdItf_ZX::QryBill()      //��ѯ�ʽ���ˮ�����ʵ���
{
	return -1;
}

/*
�ɷݲ�ѯ(504)[֧����������]

���ܴ���	504
��������	�ɷݲ�ѯ
��������	������	��ʶ	���ͼ�����	��Ҫ	����
�ͻ�����	USER_CODE	INT	Y	
�ʲ��˻�	ACCOUNT	VARCHAR(20)   	N	
�����г�	MARKET	CHAR(2)       	N	
�ɶ�����	SECU_ACC	VARCHAR(10)   	N	
֤ȯ����	SECU_CODE	VARCHAR��8��	N	
�ⲿ����	EXT_INST	INT	N	��������ʱ��
��������	������	��ʶ	���ͼ�����	����
1�ͻ�����	USER_CODE	INT
2�ʲ��˻�	ACCOUNT	VARCHAR(20)
3�����г�	MARKET	CHAR(2)
4�ɶ�����	SECU_ACC	VARCHAR(10)
5֤ȯ����	SECU_NAME	VARCHAR(16)
6֤ȯ����	SECU_CODE 	VARCHAR(8)
7����ϯλ	SEAT	VARCHAR(6)
8��֧����	BRANCH	INT
9�ⲿ����	EXT_INST	INT
10����	CURRENCY	CHAR(1)
11�ɷ����	SHARE_BLN	INT
12�ɷݿ���	SHARE_AVL	INT
13�ɷݽ��׶�����	SHARE_TRD_FRZ	INT
14�ɷ���;����	SHARE_OTD	INT
15�ɷ���;��������	SHARE_OTD_AVL	INT	����20040103
16�ɷ��쳣������	SHARE_FRZ	INT
17�ɷݷ���ͨ����	SHARE_UNTRADE_QTY	INT
18��ǰ�ɱ�	CURRENT_COST	DECIMAL(16,2)
19��ֵ	MKT_VAL	DECIMAL(16,2)	
��������	�������	������Ϣ
306	�û����벻����
501	�޲�ѯ���
502	��ѯʧ��
��ע��Ϣ	��֤ȯ��������ͽ����г�

*/
int TTrdItf_ZX::QryStocks()    //��ѯ�ʺ������еĹɷ�
{
	TList * lstAns = new TList();
	TStringList *lstDD = new TStringList();

	String market;

	switch (FRequest.QryStocks.Bourse)//20051122----Ϊʲôһֱ���Ϻ�
	{
	case bsSH : market = _SH; break;
	case bsSZ : market = _SZ; break;
	default: market = _SH;//20051122----Ĭ��Ϊ�Ͻ���
	}

	String data;

	if(  FRequest.QryStocks.Bourse == bsSH )
		data.printf("504|%s||%2s|%s|||",FUSER_CODE.c_str() ,market.c_str(),this->FAccInfo.SH);//20051122---"504|%s|%s|%2s|%s|||"==>"504|%s||%s|%s|||"
	else if( FRequest.QryStocks.Bourse == bsSZ )
		data.printf("504|%s||%2s|%s|||",FUSER_CODE.c_str() ,market.c_str(),this->FAccInfo.SZ);//20051122---"504|%s|%s|%2s|%s|||"==>"504|%s||%s|%s|||"
	else
		data.printf("504|%s||||||",FUSER_CODE.c_str());//20051122---"504|%s|%s|%s|||||"==>"504|%s||%s|%s|||"


	AnsiString cmd = GenCMD( data.Length(), data  );

	String retMarket;
	try
	{
		int fcount = 19;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			goto ADD;
			while (lstDD->Strings[NEXT_FLAG]=="1")
			{
				if (SplitData(ReadNextData(), lstDD,  fcount,reccount) == DEF_ACK_OK)
				{
ADD:
					for( int i=0; i<reccount; i++ )
					{
						TStockInfo *si = new TStockInfo;
						memset(si, 0, sizeof(TStockInfo));

						retMarket = lstDD->Strings[INDEX(fcount,i,3)]  ;

						if( retMarket == _SH )
							si->SecuID[0] = 'H';
						else if( retMarket == _SZ )
							si->SecuID[0] = 'S';
						else
							si->SecuID[0] = 'H';

						strncpy(si->SecuID+1 , lstDD->Strings[INDEX(fcount,i,6)].c_str(), 6);
						strncpy(si->SecuDesc,   lstDD->Strings[INDEX(fcount,i,4)].c_str(), 12);

						si->Balance       = lstDD->Strings[INDEX(fcount,i,12)].ToIntDef(0);//20051122---11==>12
						si->Available     = lstDD->Strings[INDEX(fcount,i,13)].ToIntDef(0);//20051122---12==>13
						si->ProfitAndLoss = 0;
						si->CostPrice     = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,18)], 0);
						si->Cost          = si->Balance * si->CostPrice;
						si->CurPrice      = 0;
						si->CurVal        = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,19)], 0);
						lstAns->Add(si);
					}
				}
			}

			if (lstAns->Count > 0)
			{
				NewAns(lstAns->Count);
				for ( int i = 0; i < lstAns->Count; i++ )
				{
					TStockInfo *ci = (TStockInfo *)lstAns->Items[i];
					memcpy(&(*FAnswer)[i].QryStocks.StockInfo, ci, sizeof(TStockInfo));
				}
			}

			for ( int i = 0; i < lstAns->Count; i++ )
			{
				TStockInfo *ci = (TStockInfo *)lstAns->Items[i];
				delete ci;
			}
			lstAns->Clear();
		}
		else
		{
			ODS(lstDD->Strings[4].c_str());
			return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
		}
	}
	__finally
	{
		delete lstDD;
		delete lstAns;
	}

	return 0;
}

//////���׺���/////
/*
ί������ҵ��(403)[֧����������]

���ܴ���	403
��������	ί������ҵ��,֧����������
��������	������	��ʶ	���ͼ�����	��Ҫ	����
�ͻ�����	USER_CODE	INT	Y	
�����г�	MARKET	CHAR(2)	Y	
�ɶ�����	SECU_ACC	VARCHAR(10)	Y	
�ʲ��˻�	ACCOUNT	VARCHAR(20)        	N	
����ϯλ	SEAT	VARCHAR(6)         	N
֤ȯ����	SECU_CODE	VARCHAR��8��	Y
������Ϊ	TRD_ID	CHAR(2)	Y	������Ϊ����
�۸�	PRICE	DECIMAL(10,3)	Y	
����	QTY	INT	Y	
ҵ�����	BIZ_NO	VARCHAR(10)	N	
�ⲿ����	EXT_INST	INT	N	��������ʱ��
�ⲿ��¼��	EXT_REC_NUM	INT	N

404|%s|%2s|%s|||%s|%2s|%10.3f|%d||||
��������	������	��ʶ	���ͼ�����	����
ҵ�����	BIZ_NO	VARCHAR(10)	
��ͬ���	ORDER_ID	VARCHAR(10)	
�ʲ��˻�	ACCOUNT	VARCHAR(20)	
�۸�	PRICE	DECIMAL(10,3)	
����	QTY	INT	
ί�н��	ORDER_AMT	DECIMAL(16,2)	
ί�ж�����	ORDER_FRZ_AMT	DECIMAL(16,2)	
����ϯλ	SEAT	VARCHAR(6)	
�ⲿ����	EXT_INST	INT	
�ⲿ�˻�	EXT_ACC	VARCHAR(32)	
�ⲿ���˻�	EXT_SUB_ACC	VARCHAR(32)	
�ⲿ������	EXT_FRZ_AMT	DECIMAL(16,2)	
��������	�������	������Ϣ
304	�ɶ����벻����
306	�û����벻����
402	��δ��ָ������
403	�˹ɲ��ܽ��д���ί��
311	�ⲿ����������
404	ί��ʧ��
��ע��Ϣ	 	�����������ί�У��򽫵�һ��ί�еĺ�ͬ�����Ϊ�ڶ����Ժ�ί�е�ҵ�����
����ϯλ : ����ʱ��
�ʲ��˻�Ϊ��ѡ��,�����ò�ͬ���ʲ��ʻ���ί��,����ʱ�ùɶ���ȱʡ�ʻ�
������Ϊ����: 
0B	����
0S	����
4B	��ɽɿ�
5S	תծת��
6S	תծ����
7B	�¹��깺
8B	�¹ɽɿ�
9B	����
9S	��ȯ

*/
int TTrdItf_ZX::Buy()
{
	String market;
	switch (FRequest.Buy.SecuID[0])
	{
	case 'H' : market = _SH; break;
	case 'S' : market = _SZ; break;
	default: return -1;
	}

	String data;
	String acc;
	/*  if(  FRequest.QryStocks.Bourse == bsSH )
	acc = this->FAccInfo.SH ;
	else if( FRequest.QryStocks.Bourse == bsSZ )
	acc = this->FAccInfo.SZ ;
	*/
	//#ifdef _DEBUG//20051122
	if(FRequest.Buy.SecuID[0] == 'H' || FRequest.Buy.SecuID[0] == 'h')
		acc = this->FAccInfo.SH ;
	else if(FRequest.Buy.SecuID[0] == 'S' || FRequest.Buy.SecuID[0] == 's')
		acc = this->FAccInfo.SZ ;
	else
		return -1;
	//#endif
	if (FRequest.Buy.Type == 1)  // �깺���
	{
		data.printf("403|%s|%2s|%s|||%s|%2s|%.3f|%d||||",FUSER_CODE.c_str() ,market,acc.c_str(),
			FRequest.Buy.SecuID+1, "7K", FRequest.Buy.Price,FRequest.Buy.Num);

	}
	else
	{
		data.printf("403|%s|%2s|%s|||%s|%2s|%.3f|%d||||",FUSER_CODE.c_str() ,market,acc.c_str(),
			FRequest.Buy.SecuID+1, "0B", FRequest.Buy.Price,FRequest.Buy.Num);//20051122---404==>403,10.3f===>.3f

	}

	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 12;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			NewAns(1);
			strncpy((*FAnswer)[0].Buy.ContractID, lstDD->Strings[INDEX(fcount,0,2)].c_str(), 10);
		}
		else
		{
			return -1;
		}
	}
	__finally
	{
		delete lstDD;
	}

	return 0;
}

int TTrdItf_ZX::Sell()
{
	String market;
	switch (FRequest.Sell.SecuID[0])
	{
	case 'H' : market = _SH; break;
	case 'S' : market = _SZ; break;
	default: return -1;
	}

	String data;
	String acc;
	/*  if(  FRequest.QryStocks.Bourse == bsSH )
	acc = this->FAccInfo.SH ;
	else if( FRequest.QryStocks.Bourse == bsSZ )
	acc = this->FAccInfo.SZ ;
	*/
	//#ifdef _DEBUG//20051122
	if(FRequest.Sell.SecuID[0] == 'H' || FRequest.Sell.SecuID[0] == 'h')
		acc = this->FAccInfo.SH ;
	else if(FRequest.Sell.SecuID[0] == 'S' || FRequest.Sell.SecuID[0] == 's')
		acc = this->FAccInfo.SZ ;
	else
		return -1;
	//#endif

	if (FRequest.Sell.Type == 1)  // �깺���
	{
		data.printf("403|%s|%2s|%s|||%s|%2s|%10.3f|%d||||",FUSER_CODE.c_str() ,market.c_str(),acc.c_str(),
			FRequest.Sell.SecuID+1, "7L", FRequest.Sell.Price,FRequest.Sell.Num);
	}
	else
	{
		data.printf("403|%s|%2s|%s|||%s|%2s|%10.3f|%d||||",FUSER_CODE.c_str() ,market.c_str(),acc.c_str(),
			FRequest.Sell.SecuID+1, "0S", FRequest.Sell.Price,FRequest.Sell.Num);//20051122----404==>403
	}


	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 12;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			NewAns(1);
			strncpy((*FAnswer)[0].Sell.ContractID, lstDD->Strings[INDEX(fcount,0,2)].c_str(), 10);
		}
		else
		{
			return -1;
		}
	}
	__finally
	{
		delete lstDD;
	}

	return 0;
}


/*
ί�г���(404)[֧����������]
���ܴ���	404
��������	ί�г���, ֧����������
��������	������	��ʶ	���ͼ�����	��Ҫ	����
�����г�	MARKET	CHAR(2)	Y	
��ͬ���	ORDER_ID	VARCHAR(10)	Y	ί�з��ص�
��������	������	��ʶ	���ͼ�����	����

��������	�������	������Ϣ
420	�޴�ί��
421	��ί�в��ܳ���
422	��ί���ѳ���
310	����ʧ��
��ע��Ϣ	

*/
int TTrdItf_ZX::Undo() //ί�г���
{
	String market;
	switch (FRequest.Undo.Bourse)
	{
	case bsSH : market = _SH; break;
	case bsSZ : market = _SZ; break;
	default: return -1;
	}

	String data;
	data.printf("404|%2s|%s",market.c_str(),FRequest.Undo.ContractID ) ;
	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 0;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) != DEF_ACK_OK)
		{
			return -1;
		}
	}
	__finally
	{
		delete lstDD;
	}

	return 0;
}

int TTrdItf_ZX::GetRecvingDataLen(String &InputStr, String TrimStr)
{
	String sInputStr = InputStr;

	int nDataLen = 0;
	int nCurPos = 0;
	for(int i=0;i<2;i++)//Ӧ���ͷ�ṹ: ͷ���� CHAR(4),ǰ�����ַ���0�����;���ݳ��� VARCHAR(n),ǰ�����ַ���0�����
	{
		nCurPos = sInputStr.Pos(TrimStr);
		if(nCurPos <= 0 )
		{
			//if(sInputStr.IsEmpty())
			//  return 0;

			return 0;
		}

		nDataLen += sInputStr.SubString(1, nCurPos-1).ToIntDef(0);

		sInputStr.Delete(1, nCurPos);
	}

	return nDataLen;  
}

