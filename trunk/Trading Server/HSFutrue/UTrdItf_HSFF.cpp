//---------------------------------------------------------------------------                            33
#include <assert.h>
#include <IniFiles.hpp>
#include "UTrdItf_HSFF.h"
//---------------------------------------------------------------------------

#define HS_VERSION "111"

int TTrdItf_HSFF:: Init()
{
	this->CloseLink();

	FItf = new TComm( NULL );
	FItf->Create();
	//FItf->set_SendTimeOut( FHSFFSet.TimeOut );
	//FItf->set_ReceiveTimeOut( FHSFFSet.TimeOut );

	return FItf->ConnectX( FHSFFSet.Protocol,
		WideString(FHSFFSet.SvrIp).c_bstr(),
		FHSFFSet.SvrPort,
		FHSFFSet.KeyCipher,
		WideString(FHSFFSet.KeyDeKey).c_bstr(),
		FHSFFSet.KeyDeKey.Length());
}

int TTrdItf_HSFF::SendAndReceive()
{
	try
	{
		if ( FItf->Send()!=0 )
		{
			this->SetLastError(ERR_REMOTE_SEND_FAILED,'E',PLUGINNAME,"�������ݴ���,connection=%d",FItf->Connection);
			return ERR_REMOTE_SEND_FAILED;
		}

		FItf->FreePack();

		if ( FItf->Receive()!=0 )
		{
			this->SetLastError(ERR_REMOTE_RECV_FAILED,'E',PLUGINNAME,"�������ݴ���,connection=%d",FItf->Connection);
			return ERR_REMOTE_RECV_FAILED;
		}

		if( FHSFFSet.debug_mode )
		{
			char buf[1024];
			lstrcpyn(buf,String(FItf->Buffer).c_str(),1023);
			buf[1023]=0;
			int len = strlen(buf);
			for(int i=0;i<len;i++ )
			{
				if ( buf[i]=='\x01' )
					buf[i] = '#';
			}
			ODS('M',PLUGINNAME,"BUF:%s",buf) ;
		}

		if ( FItf->ErrorNo!=0 )
		{
			lstrcpyn( FLastError.Sender ,"HSF", SEQ_LEN);
			FLastError.ErrorCode = -abs(FItf->ErrorNo);
			lstrcpyn( FLastError.Text,String( FItf->ErrorMsg ).c_str(),MAX_TEXT );
			ODS('E',PLUGINNAME, "��̨��ʾ:%s,ErrNo:%d",FLastError.Text,FLastError.ErrorCode );
			return FLastError.ErrorCode;
		}
	}
	catch( Exception &e )
	{
		lstrcpyn( FLastError.Sender ,"HSF", SEQ_LEN);
		FLastError.ErrorCode = ERR_REMOTE_OTHER_FAILED;
		lstrcpyn( FLastError.Text,e.Message.c_str(),MAX_TEXT );

		ODS('E',PLUGINNAME, "�������:%s",e.Message.c_str() );
		return ERR_REMOTE_OTHER_FAILED;
	}
	catch(...)
	{
		lstrcpyn( FLastError.Sender ,"HSF", SEQ_LEN);
		FLastError.ErrorCode = ERR_REMOTE_OTHER_FAILED;
		lstrcpyn( FLastError.Text,"δ֪����",MAX_TEXT );

		ODS('E',PLUGINNAME, "�������:%s",FLastError.Text );
		return ERR_REMOTE_OTHER_FAILED;
	}
	return 0;
}


/*
���ܺ�	200
��������	�ͻ���¼У��
�������	������	����	˵��	����	ȱʡֵ
version	N3	�汾��
identity_type	C1	�˻������� 1 ������ 2 ָ���� 3 ��ѯ Ĭ�ϲ�����
op_branch_no	N5	������֧Ӫҵ���ţ���׷�ٸ����������ĸ���֧���ܱ߿���ͨ�����û�ñ�������֧Ӫҵ���ţ��ܱ߱�������
op_entrust_way	C1	ί�з�ʽ
op_station	C12	���������Ե�վ����׷���������Դ��һ����Ӫҵ���ڲ���ֵ��Ϊ����վ��MAC��ַ�������ڵ绰����ɿ�����Ϊ�������
branch_no 	N5	�ǹ�������Ӫҵ���ţ�����ͨ�������ɹ����Լ�ѡ�����룬������ѡ���֧�ţ����ܱ�Ӧ������Ϊop_branch_no�Ա�ʾ��Ӫҵ��
function_id	N6	ϵͳ����
input_content	C1	�ʺ����ͣ���1������2������3����4������5��, ��6��, ��A���ֱ��ʾaccount_content�����ʽ��ʺţ��ɶ����룬���ʽ𿨺ţ������ʺţ��ɶ��ʺţ��ͻ���ţ��ڻ��ʺ�
password	C10	��������
content_type	C6	�ʺ�У�鷽ʽ����input_contentΪ��4������5��ʱ����content_type��ȷ���кź͹ɶ����г������������Ϊ��0����
account_content	C30	��������
�������	������	����	˵��	����	ȱʡֵ
error_no	N4	�����
error_info	C20	����ԭ��
fund_account	N9	�ʽ��˺�
����˵��	�����	������Ϣ	����˵��	���󼶱�
-41	�ʽ����뵽��δ�޸�	����ʾ���Կɵ�¼
-42	�������뵽��δ�޸�	����ʾ���Կɵ�¼		
-51	�޴��ʻ�			
-61	�ʻ���¼ʧ��			
-63	�������			
-64	��û�д���ί�е�Ȩ��			
-66	�����ʻ�״̬������			

*/
int TTrdItf_HSFF::SetAccount()
{
	try
	{
		FAccInfo.lt = FRequest.SetAccount.LoginType;
		FAccount = FRequest.SetAccount.Account;
		lstrcpyn( FAccInfo.PW, FRequest.SetAccount.PW, 13 );

		FItf->SetHead( FHSFFSet.branch_no, 200 );
		FItf->SetRange( 10, 1 );

		FItf->AddField(WideString("version").c_bstr());
		FItf->AddField(WideString("op_branch_no").c_bstr());
		FItf->AddField(WideString("op_entrust_way").c_bstr());
		FItf->AddField(WideString("op_station").c_bstr());
		FItf->AddField(WideString("function_id").c_bstr());
		FItf->AddField(WideString("branch_no").c_bstr());
		FItf->AddField(WideString("input_content").c_bstr());
		FItf->AddField(WideString("content_type").c_bstr());
		FItf->AddField(WideString("account_content").c_bstr());
		FItf->AddField(WideString("password").c_bstr());

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue(WideString("200").c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());

		switch( FRequest.SetAccount.LoginType )
		{
		case asCA:
			FItf->AddValue(WideString("1").c_bstr());
			break;
			//case asSHA,asSZA:
			//	FItf->AddValue(WideString("2").c_bstr());
		case asJJS,asFDL,asFZZ,asFSH:
			FItf->AddValue(WideString("A").c_bstr());
			break;
		default:
			FItf->AddValue(WideString("").c_bstr());
		}

		FItf->AddValue(WideString("0").c_bstr());
		FItf->AddValue(WideString(FRequest.SetAccount.Account).c_bstr());
		FItf->AddValue(WideString(FRequest.SetAccount.PW).c_bstr());

		int	r	= SendAndReceive();

		if ( r < 0 )
		{
			return r;
		}
		else
		{
			if ( FItf->RecordCount > 0 )
			{
				String	acc	= String( FItf->FieldByName( WideString( "fund_account" )));
				String  facc= String( FItf->FieldByName( WideString( "stock_account")));

				FHSFFSet.futu_exch_type =
					String(FItf->FieldByName( WideString( "exchange_type" )));

				if ( acc.Length() > 0 )
				{
					lstrcpyn(FAccInfo.Capital,acc.c_str(),ACC_LEN);
					switch( ConvertMarketType( FHSFFSet.futu_exch_type.c_str() ))
					{
					case mtJJS :  lstrcpyn(FAccInfo.FJJS,facc.c_str(),ACC_LEN);
						break;
					case mtFDL :  lstrcpyn(FAccInfo.FDL,facc.c_str(),ACC_LEN);
						break;
					case mtFZZ :  lstrcpyn(FAccInfo.FZZ,facc.c_str(),ACC_LEN);
						break;
					case mtFSH :  lstrcpyn(FAccInfo.FSH,facc.c_str(),ACC_LEN);
						break;
					}

					NewAns( 1 );
					memcpy( &( ( *FAnswer )[0].SetAccount.AccountInfo ), &FAccInfo, sizeof( TAccountInfo ) );

					String tabconfirm_flag=String(FItf->FieldByName( WideString( "tabconfirm_flag" )));
					ODS('M',PLUGINNAME,"tabconfirm_flag:%s",tabconfirm_flag.c_str());
					if( tabconfirm_flag == "0")
						return 0;
					else
						goto COMFIRM;

				}
				else
				{
					return String( FItf->FieldByName( WideString( "error_no" ) ) ).ToIntDef( ERR_OTHERS );
				}
			}
			else
			{
				return ERR_NO_ACK;
			}
		}

COMFIRM:
		//�˵�ȷ��
		FItf->SetHead( FHSFFSet.branch_no, 1008 );
		FItf->SetRange( 10, 1 );

		FItf->AddField(WideString("version").c_bstr());
		FItf->AddField(WideString("op_branch_no").c_bstr());
		FItf->AddField(WideString("op_entrust_way").c_bstr());
		FItf->AddField(WideString("op_station").c_bstr());
		FItf->AddField(WideString("function_id").c_bstr());
		FItf->AddField(WideString("branch_no").c_bstr());
		FItf->AddField(WideString("fund_account").c_bstr());
		FItf->AddField(WideString("password").c_bstr());
		FItf->AddField(WideString("check_date").c_bstr());
		FItf->AddField(WideString("check_time").c_bstr());

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue(WideString("1008").c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());
		FItf->AddValue(WideString(FRequest.SetAccount.Account).c_bstr());
		FItf->AddValue(WideString(FRequest.SetAccount.PW).c_bstr());
		FItf->AddValue(WideString(Date().FormatString("yyyymmdd")));
		FItf->AddValue(WideString(Time().FormatString("hhnnss")));

		r	= SendAndReceive();

		if ( r < 0 )
		{
			ODS('M',PLUGINNAME,"ȷ���˵�ʧ��");
			return r;
		}
		else
		{
			ODS('M',PLUGINNAME,"ȷ���˵��ɹ�");
			return 0;
		}
	}
	__finally
	{
		FItf->FreePack();
	}
	return 0;
}

/*
���ܺ�
��������	�ڻ��ͻ��ʽ��ѯ
money_type	C1	�������
�������	������	����	˵��	����	ȱʡֵ
money_type	C1	�������
current_balance	N16.2	�ʽ����		
enable_balance	N16.2	�����ʽ�		
fetch_balance	N16.2	�����ʽ�
����˵��	�����	������Ϣ	����˵��	���󼶱�	
-51	�޴��ʻ�			
-61	�ڻ��ͻ��ʽ��ѯʧ��	����������	

*/
int TTrdItf_HSFF::QryMoney()
{
	try
	{
		FItf->SetHead( FHSFFSet.branch_no, 1508 );
		FItf->SetRange( 9, 1 );

		FItf->AddField( WideString( "version" ).c_bstr() );
		FItf->AddField( WideString( "op_branch_no" ).c_bstr() );
		FItf->AddField( WideString( "op_entrust_way" ).c_bstr() );
		FItf->AddField( WideString( "op_station" ).c_bstr() );
		FItf->AddField( WideString( "branch_no" ).c_bstr() );
		FItf->AddField( WideString( "fund_account" ).c_bstr() );
		FItf->AddField( WideString( "password" ).c_bstr() );
		FItf->AddField( WideString( "function_id" ).c_bstr() );
		FItf->AddField( WideString( "money_type" ).c_bstr() );

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());
		FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
		FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
		FItf->AddValue(WideString( "1508" ).c_bstr() );
		FItf->AddValue(WideString( ConvertMoneyType(FRequest.QryMoney.MoneyType)).c_bstr() );

		int	r	= SendAndReceive();

		if ( r < 0 )
		{
			return r;
		}
		else
		{
			if ( FItf->RecordCount > 0 )
			{
					NewAns( 1 );
					( *FAnswer )[0].QryMoney.MoneyInfo.balance = StrToFloatDef( String( FItf->FieldByName( WideString( "rights_balance_float" ).c_bstr() ) ), 0 );
					//( *FAnswer )[0].QryMoney.MoneyInfo.balance = StrToFloatDef( String( FItf->FieldByName( WideString( "current_balance" ).c_bstr() ) ), 0 );
					( *FAnswer )[0].QryMoney.MoneyInfo.available = StrToFloatDef( String( FItf->FieldByName( WideString( "enable_balance" ).c_bstr() ) ), 0 );
					( *FAnswer )[0].QryMoney.MoneyInfo.MoneyType = ConvertMoneyType( String( FItf->FieldByName( WideString( "money_type" ).c_bstr() ) ).c_str() );

					return 0;
			}
			else
			{
				return ERR_NO_ACK;
			}
		}
	}
	__finally
	{
		FItf->FreePack();
	}
	return 0;
}

/*
���ܺ�	1504
��������	�ڻ�����ί�в�ѯ
�������	������	����	˵��	����	ȱʡֵ
futu_exch_type	C4	�������		
futures_account	C12	�ڻ��˺�		
contract_code	C30	��Լ����
en_entrust_status	C10	����ί��״̬		
query_direction	C1	��ѯ����0��˳�飻1������		
batch_no	N8	ί������		
futu_entrust_type	C1	ί������		
request_num	N8	��ѯ����
position_str	C32	��λ��		
�������	������	����	˵��	����	ȱʡֵ
position_str	C32	��λ��
entrust_no	N8	ί�б��
futu_exch_type	C4	�������
futu_entrust_price	N12.6	�ڻ�ί�м۸�
entrust_bs	C1	ί����������
entrust_status	C1	ί��״̬
report_time	N8	�걨ʱ��
business_amount	N16.2	�ɽ�����
entrust_amount	N16.2	ί������
cancel_amount	N16.2	��������

����˵��	�����	������Ϣ	����˵��	���󼶱�	
-51	�޴��ʻ�			
-61	�ڻ�����ί�в�ѯʧ��	����������
*/

/*
##entrust_bs_name#hedge_type#hedge_type_name#futu_entrust_price#amount_per_hand#entrust_amount#business_amount#cancel_amount#hold_balance#entrust_time#report_time#entrust_status#status_name#futu_entrust_type#futu_entrust_type_name#confirm_no#frozen_fare#forceclose_reason#forceclose_reason_name#batch_no#error_message#
20070410000010000000092#20070410#92#100359#����#F4#���ڽ���#207130023052#IF0704#��ָ0704#0#1#����#1#����#0#Ͷ��#3050.0000#300#1.0000#0#0#137350.0000#103339#103750#C#����#0#ί��# #100.0000#0##92# #


*/
int TTrdItf_HSFF::QryCurCsn()
{
	TList* ResultList = new TList();

	int r;
	String position_str = FRequest.QryCurCsn.SeqNum;

	do
	{
		FItf->SetHead( FHSFFSet.branch_no, 1504 );
		FItf->SetRange( 17, 1 );

		FItf->AddField(WideString("version").c_bstr());
		FItf->AddField(WideString("op_branch_no").c_bstr());
		FItf->AddField(WideString("op_entrust_way").c_bstr());
		FItf->AddField(WideString("op_station").c_bstr());
		FItf->AddField(WideString("function_id").c_bstr());
		FItf->AddField(WideString("branch_no").c_bstr());

		FItf->AddField(WideString("fund_account").c_bstr());
		FItf->AddField(WideString("password").c_bstr());
		FItf->AddField(WideString("futu_exch_type").c_bstr());
		FItf->AddField(WideString("futures_account").c_bstr());

		FItf->AddField(WideString("contract_code").c_bstr());
		FItf->AddField(WideString("en_entrust_status").c_bstr());         //en_entrust_status������
		FItf->AddField(WideString("query_direction").c_bstr());
		FItf->AddField(WideString("batch_no").c_bstr());
		FItf->AddField(WideString("futu_entrust_type").c_bstr());
		FItf->AddField(WideString("request_num").c_bstr());
		FItf->AddField(WideString("position_str").c_bstr());


		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue( WideString( "1504" ) );
		FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());

		FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
		FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
		FItf->AddValue( WideString( ""/*FHSFFSet.futu_exch_type*/ ) );
		FItf->AddValue( WideString( ""/*this->FAccInfo.FJJS*/ ));  //�ڻ��ʻ�
		FItf->AddValue( WideString( "" ) );
		FItf->AddValue( WideString( "" ) );
		FItf->AddValue( WideString( ( char ) qdahead ) );
		FItf->AddValue( WideString( FRequest.QryCurCsn.OrderID) );
		FItf->AddValue( WideString( FHSFFSet.futu_entrust_type ) );
		FItf->AddValue( WideString( IntToStr(FRequest.QryCurCsn.MaxRecord) ) );
		FItf->AddValue( WideString( position_str ) );

		r = SendAndReceive();

		if ( FItf->RecordCount < 1 || r < 0 ) break;

		for ( int i = 0; i < FItf->RecordCount; ++i)
		{
			TOrderInfo*	ci	= new TOrderInfo;
			ZeroMemory( ci, sizeof( TOrderInfo ) );
			ResultList->Add(ci);

			//�齨�������
			lstrcpyn( ci->ContractID, String( FItf->FieldByName( WideString( "entrust_no" ) ) ).c_str() ,SEQ_LEN);
			lstrcpyn( ci->SecuID, String( FItf->FieldByName( WideString( "contract_code" ) ) ).c_str() ,CODE_LEN);
			lstrcpyn( ci->Account, String( FItf->FieldByName( WideString( "futures_account" ) ) ).c_str() ,ACC_LEN);
			ci->Market = this->ConvertMarketType(
				String( FItf->FieldByName( WideString( "futu_exch_type" ) ) ).c_str());
			ci->Time = this->ConvertTimeToInt(
				String( FItf->FieldByName( WideString( "entrust_time" ) ) ).c_str() );
			ci->Date = this->ConvertDateToInt(
				String( FItf->FieldByName( WideString( "init_date" ) ) ).c_str() );
			ci->Type = this->ConvertOrderType(
				(String( FItf->FieldByName( WideString( "entrust_bs" ) ) ) +
				String( FItf->FieldByName( WideString( "futures_direction" ) ) )).c_str()  );
			ci->State = this->ConvertOrderState(
				String( FItf->FieldByName( WideString( "entrust_status" ) ) ).c_str());
			ci->CsnVol = StrToFloatDef(FItf->FieldByName( WideString( "entrust_amount" ) ), 0 );
			ci->TrdVol = StrToFloatDef( FItf->FieldByName( WideString( "business_amount" ) ), 0 );
			ci->CsnPrice = StrToFloatDef( FItf->FieldByName( WideString( "futu_entrust_price" ) ), 0 );
			ci->CancelVol = - StrToFloatDef( FItf->FieldByName( WideString( "cancel_amount" ) ), 0 );
			ci->TrdPrice = 0;
			lstrcpyn(ci->SeqNum,
				String( FItf->FieldByName( WideString( "position_str" ))).c_str(),SEQ_LEN);
			FItf->MoveBy(1);
		}
		FItf->FreePack();
		break;
	} while ( FItf->RecordCount < 1 );

	if ( ResultList->Count > 0 )
	{
		NewAns( ResultList->Count );
		for ( int i = 0; i < ResultList->Count; ++i )
		{
			memcpy( &( *FAnswer )[i].QryCurCsn.OrderInfo, ResultList->Items[i],
				sizeof( TOrderInfo ) );
		}
	}

	for ( int i = 0; i < ResultList->Count; ++i )
		delete ( TOrderInfo* ) ResultList->Items[i];

	delete ResultList;

	return r;
}

/*

���ܺ�	1506	�汾��	3.2	��������	20060816
��������	�ڻ����ճɽ���ѯ			���������	Y
�������	������	����	˵��	����	ȱʡֵ
version	N3	�汾��
op_branch_no	N5	����Ա��֧����
op_entrust_way	C1	ί�з�ʽ
identity_type	C1	�˻������� 1 ������ 2 ָ���� 3 ��ѯ Ĭ�ϲ�����
op_station	C12	վ��/�绰
function_id	N6	ϵͳ����
branch_no	N5	��֧����
fund_account	N9	�ʽ��˺�
password	C10	��������
futu_exch_type	C4	�������
futures_account	C12	�ڻ��˺�
contract_code	C30	��Լ����
query_mode	C1	��ѯģʽ
0 ��ϸ
1 ��[ί�б��+�������+�ڻ������ʺ�+��Լ����+��ƽ�ַ���+��������+ҵ���־]����
2 ��[ί�б��+�������+�ڻ������ʺ�+��Լ����+��ƽ�ַ���+��������+ҵ���־+�ɽ��۸�]����
3 ��[�������+�ڻ������ʺ�+��Լ����+��ƽ�ַ���+��������+ҵ���־]����
query_direction	C1	��ѯ����0��˳�飻1������
request_num	N8	��ѯ����
futu_position_str	C100	��λ��
�������	������	����	˵��	����	ȱʡֵ
futu_position_str	C100	��λ��		
init_date	N8	��������
serial_no	N8	��ˮ���		
entrust_no	N8	ί�б��		
futu_exch_type	C4	�������		
exchange_name	C8	��������		
futures_account	C12	�ڻ��˺�
contract_code	C30	��Լ����
contract_name	C12	Ʒ�ּ��
money_type	C1	�������
futures_direction	C1	��ƽ�ַ���		
futures_direction_name	C12	��ƽ�ַ���		
entrust_bs	C1	��������		
entrust_bs_name	C12	��������		
futu_business_price	N12.6	�ڻ��ɽ��۸�		
amount_per_hand	N10	ÿ�ֶ���		
futu_entrust_type	C1	ί�����		
futu_entrust_type_name	C12	ί���������		
business_time	N8	�ɽ�ʱ��		
business_amount	N16.2	�ر�����		
frozen_fare	N16.2	�����ܷ���		
futu_business_no	C20	�ɽ����		
ҵ��˵��					

����˵��	�����	������Ϣ	����˵��	���󼶱�	
-51	�޴��ʻ�			
-61	�ڻ����ճɽ���ѯʧ��	����������		

*/
int TTrdItf_HSFF::QryCurTrd()
{
	TList* ResultList = new TList();
	int r;
	String position_str = FRequest.QryCurTrd.SeqNum;

	do
	{
		FItf->SetHead( FHSFFSet.branch_no, 1506 );
		FItf->SetRange( 15, 1 );

		FItf->AddField(WideString("version").c_bstr());
		FItf->AddField(WideString("op_branch_no").c_bstr());
		FItf->AddField(WideString("op_entrust_way").c_bstr());
		FItf->AddField(WideString("op_station").c_bstr());
		FItf->AddField(WideString("function_id").c_bstr());
		FItf->AddField(WideString("branch_no").c_bstr());

		FItf->AddField(WideString("fund_account").c_bstr());
		FItf->AddField(WideString("password").c_bstr());

		FItf->AddField( WideString( "futu_exch_type" ).c_bstr() );
		FItf->AddField( WideString( "futures_account" ).c_bstr() );
		FItf->AddField( WideString( "contract_code" ).c_bstr() );
		FItf->AddField( WideString( "query_mode" ).c_bstr() );
		FItf->AddField( WideString( "query_direction" ).c_bstr() );
		FItf->AddField( WideString( "request_num" ).c_bstr() );
		FItf->AddField( WideString( "futu_position_str" ).c_bstr() );

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue( WideString( "1506" ) );
		FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());

		FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
		FItf->AddValue(WideString(FAccInfo.PW).c_bstr());

		FItf->AddValue( WideString( "" /*FHSFFSet.futu_exch_type*/ ) );
		FItf->AddValue( WideString( "") );  //�ڻ��ʻ�
		FItf->AddValue( WideString( "") );
		FItf->AddValue( WideString( "0" ) );
		FItf->AddValue( WideString( ( char ) qdahead ) );
		FItf->AddValue( WideString( IntToStr(FRequest.QryCurTrd.MaxRecord) ) );
		FItf->AddValue( WideString( position_str ) );

		r = SendAndReceive();

		if ( FItf->RecordCount < 1 || r < 0 ) break;

		for ( int i = 0; i < FItf->RecordCount; ++i)
		{
			TTradeInfo*	ti	= new TTradeInfo;
			ZeroMemory( ti, sizeof( TTradeInfo ) );

			//�齨�������
			lstrcpyn( ti->ContractID ,
				String( FItf->FieldByName( WideString( "entrust_no" ) ) ).c_str(),SEQ_LEN);
			lstrcpyn( ti->TrdID ,
				String( FItf->FieldByName( WideString( "futu_business_no" ) ) ).c_str(),SEQ_LEN);
			lstrcpyn( ti->SecuID,
				String( FItf->FieldByName( WideString( "contract_code" ) ) ).c_str(),CODE_LEN);
			lstrcpyn( ti->Account,
				String( FItf->FieldByName( WideString( "futures_account" ) ) ).c_str(),ACC_LEN);
			ti->Time = this->ConvertTimeToInt(
				String( FItf->FieldByName( WideString( "business_time" ) ) ).c_str() );
			ti->Date = this->ConvertDateToInt(
				String( FItf->FieldByName( WideString( "init_date" ) ) ).c_str() );
			ti->Type = this->ConvertOrderType(
				(String( FItf->FieldByName( WideString( "entrust_bs" ) ) ) +
				String( FItf->FieldByName( WideString( "futures_direction" ) ) )).c_str()  );
			ti->Vol = abs(StrToFloatDef( FItf->FieldByName( WideString( "business_amount" ) ), 0 ));
			//if (ti->Vol==0) {
			//	ti->Vol = -abs(StrToFloatDef( FItf->FieldByName( WideString( "cancel_amount" ) ), 0 ));
			//}
			ti->Price = StrToFloatDef( FItf->FieldByName( WideString( "futu_business_price" ) ), -1 );
			ti->Market = this->ConvertMarketType(
				String( FItf->FieldByName( WideString( "futu_exch_type" ) ) ).c_str());
			lstrcpyn(ti->SeqNum ,
				String( FItf->FieldByName( WideString( "futu_position_str" ) ) ).c_str(),SEQ_LEN);

			if (ti->Price <0 || ti->TrdID[0] == 0 || ti->Vol <=0 || ti->SeqNum[0] == 0 || ti->Time <=0)
			{

				char buf[1024];
				lstrcpyn(buf,String(FItf->Buffer).c_str(),1023);
				buf[1023]=0;
				int len = strlen(buf);
				for(int i=0;i<len;i++ )
				{
					if ( buf[i]=='\x01' )
						buf[i] = '#';
				}
				ODS('E',PLUGINNAME,"*�쳣����,buf=:%s",buf);
				delete ti;
			}
			else
				ResultList->Add( ti );

			FItf->MoveBy(1);
		}
		FItf->FreePack();
		break;
	} while ( FItf->RecordCount < 1 );

	if ( ResultList->Count > 0 )
	{
		NewAns( ResultList->Count );
		for ( int i = 0; i < ResultList->Count; ++i )
		{
			memcpy( &( *FAnswer )[i].QryCurTrd.TrdInfo, ResultList->Items[i], sizeof( TTradeInfo ) );
		}
	}

	for ( int i = 0; i < ResultList->Count; ++i )
		delete ( TTradeInfo* ) ResultList->Items[i];

	delete ResultList;

	return r;
}

/*

���ܺ�	1503	�汾��	3.2	��������	20060816
��������	�ڻ��ֲֲ�ѯ			���������	Y
��������	�ڻ��ֲֲ�ѯ				
�������	������	����	˵��	����	ȱʡֵ
version	N3	�汾��		
op_branch_no	N5	����Ա��֧����		
op_entrust_way	C1	ί�з�ʽ		
identity_type	C1	�˻������� 1 ������ 2 ָ���� 3 ��ѯ Ĭ�ϲ�����		
op_station	C12	վ��/�绰		
function_id	N6	ϵͳ����		
branch_no	N5	��֧����		
fund_account	N9	�ʽ��˺�		
password	C10	��������		
futu_exch_type	C4	�������		
futures_account	C12	�ڻ��˺�		
contract_code	C30	��Լ����		
entrust_bs	C1	��������		
query_direction	C1	��ѯ����0��˳�飻1������		
query_mode	C1	��ѯģʽ 0 ���˳ֲ�Ϊ0������ 1 �����˳ֲ�Ϊ0������		
request_num	N8	��ѯ����		
futu_position_str	C100	��λ��		
�������	������	����	˵��	����	ȱʡֵ
futu_position_str	C100	��λ��		
futu_exch_type	C4	�������		
exchange_name	C8	��������		
futures_account	C12	�ڻ��˺�
contract_code	C30	��Լ����		
contract_name	C12	Ʒ�ּ��		
money_type	C1	�������		
entrust_bs	C1	��������		
begin_amount	N16.2	�ڳ�����		
enable_amount	N16.2	��������		
real_amount	N16.2	���տ�ƽ������		
hold_profit_float	N16.2	�ֲָ���ӯ��		
hold_profit	N16.2	����ӯ��		
hold_balance	N16.2	�Ͻ����ձ�֤��		
today_open_amount	N16.2	���տ��ֿ�������		
pre_drop_amount	N16.2	ʵ������ƽ������		
futu_average_price	N12.6	ƽ����		
futu_last_price	N12.6	���¼۸�		
ҵ��˵��					

����˵��	�����	������Ϣ	����˵��	���󼶱�	
-51	�޴��ʻ�			
-61	�ڻ�Ԥ��ί�в�ѯʧ��	����������

*/

int TTrdItf_HSFF::QryStocks()
{
	TList * Ans=new TList();
	int ret=0;
	String posstr="";
	TStockInfo *si;

BB:
	FItf->SetHead(FHSFFSet.op_branch_no, 1503);
	FItf->SetRange(17, 1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("function_id").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("identity_type").c_bstr());
	FItf->AddField(WideString("futu_exch_type").c_bstr());
	FItf->AddField(WideString("futures_account").c_bstr());
	FItf->AddField(WideString("contract_code").c_bstr());             //�ɲ�����Ϊ�մ���ȫ��
	FItf->AddField(WideString("entrust_bs").c_bstr());                //�ɲ�����Ϊ�մ���ȫ��
	FItf->AddField(WideString("query_direction").c_bstr());
	FItf->AddField(WideString("query_mode").c_bstr());
	FItf->AddField(WideString("request_num").c_bstr());
	FItf->AddField(WideString("futu_position_str").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
	FItf->AddValue(WideString("1503").c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());

	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString(this->ConvertMarketType(FRequest.QryStocks.Market))); //FUTU_EXCH_TYPE
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString("").c_bstr());                          //entrust_bs  1-��
	FItf->AddValue(WideString("0").c_bstr());                           //(char)qdahead
	FItf->AddValue(WideString("0").c_bstr());                         //query_mode ������
	FItf->AddValue(WideString("20").c_bstr());
	FItf->AddValue(WideString(posstr).c_bstr());

	int r  = SendAndReceive();
	if ( FItf->RecordCount < 1 || r < 0 ) goto HH;

	while(FItf->EOF_==0)
	{
		si=new TStockInfo;
		ZeroMemory(si,sizeof(TStockInfo));
		Ans->Add(si);
		posstr=String(FItf->FieldByName(WideString("futu_position_str")));
		si->Market = this->ConvertMarketType(
			String(FItf->FieldByName(WideString("futu_exch_type"))).c_str());
		lstrcpyn(si->SecuID,
			String(FItf->FieldByName(WideString("contract_code"))).c_str(),CODE_LEN);
		lstrcpyn(si->Account,
			String(FItf->FieldByName(WideString("futures_account"))).c_str(),ACC_LEN);
		si->Balance = StrToFloatDef(FItf->FieldByName(WideString("begin_amount")),0);
		si->Available =  StrToFloatDef(FItf->FieldByName(WideString("enable_amount")),0);
		si->PosNum  = StrToFloatDef(FItf->FieldByName(WideString("real_amount")),0);
		si->CostPrice = si->CurPrice=StrToFloatDef(FItf->FieldByName(WideString("futu_average_price")),0);
		si->CurPrice =  si->CurPrice=StrToFloatDef(FItf->FieldByName(WideString("futu_last_price")),0);
		si->PosDir = this->ConvertPosDir(
			String(FItf->FieldByName(WideString("entrust_bs"))).c_str());
		FItf->MoveBy(1);
	}
	FItf->FreePack();
	if(ret ==0) goto BB;

HH:
	if(ret==0 && Ans->Count>0)
	{
		NewAns(Ans->Count);
		for(int i=0;i<Ans->Count;i++)
		{
			TStockInfo *ci = (TStockInfo *)Ans->Items[i];
			memcpy(&(*FAnswer)[i].QryStocks.StockInfo,ci,sizeof(TStockInfo));
		}
	}

	for(int i=0;i<Ans->Count;i++)
	{
		TStockInfo *ci = (TStockInfo *)Ans->Items[i];
		delete ci;
	}
	Ans->Clear();
	delete Ans;

	return ret;
}

//////���׺���/////
/*
���ܺ�	1004	�汾��	3.2	��������	20060816
��������	�ڻ�ί��ȷ��			���������	N
��������	�ڻ�ί��ȷ��				
�������	������	����	˵��	����	ȱʡֵ
version	N3	�汾��		
op_branch_no	N5	����Ա��֧����		
op_entrust_way	C1	ί�з�ʽ		
identity_type	C1	�˻������� 1 ������ 2 ָ���� 3 ��ѯ Ĭ�ϲ�����		
op_station	C12	վ��/�绰		
function_id	N6	ϵͳ����		
branch_no	N5	��֧����		
fund_account	N9	�ʽ��˺�		
password	C10	��������		
futu_exch_type	C4	�������		
futures_account	C12	�ڻ��˺�		
contract_code	C30	��Լ����		
entrust_bs	C1	��������		
futures_direction	C1	��������		
hedge_type	C1	�ױ���־		
entrust_amount	N16.2	�ڻ�ί������		
futu_entrust_price	N12.6	�ڻ�ί�м۸�		
�������	������	����	˵��	����	ȱʡֵ
error_no	N4	�����		
error_info	C20	����ԭ��		
entrust_no	N8	ί�б��		
ҵ��˵��					

����˵��	�����	������Ϣ	����˵��	���󼶱�
-51	�޴��ʻ�			
-61	�ڻ�ί��ȷ��ʧ��	����������
*/

int TTrdItf_HSFF::Order()
{
	FItf->SetHead( FHSFFSet.branch_no, 1004 );
	FItf->SetRange( 16, 1 );

	FItf->AddField( WideString( "version" ).c_bstr() );
	FItf->AddField( WideString( "op_branch_no" ).c_bstr() );
	FItf->AddField( WideString( "op_entrust_way" ).c_bstr() );
	FItf->AddField( WideString( "op_station" ).c_bstr() );
	FItf->AddField( WideString( "branch_no" ).c_bstr() );
	FItf->AddField( WideString( "fund_account" ).c_bstr() );
	FItf->AddField( WideString( "password" ).c_bstr() );
	FItf->AddField( WideString( "function_id" ).c_bstr() );
	FItf->AddField( WideString( "futu_exch_type" ).c_bstr() );
	FItf->AddField( WideString( "futures_account" ).c_bstr() );
	FItf->AddField( WideString( "contract_code" ).c_bstr() );
	FItf->AddField( WideString( "entrust_bs" ).c_bstr() );
	FItf->AddField( WideString( "futures_direction" ).c_bstr() );
	FItf->AddField( WideString( "hedge_type" ).c_bstr() );
	FItf->AddField( WideString( "entrust_amount" ).c_bstr() );
	FItf->AddField( WideString( "futu_entrust_price" ).c_bstr() );


	FItf->AddValue( WideString(HS_VERSION).c_bstr());
	FItf->AddValue( WideString(IntToStr(FHSFFSet.op_branch_no)).c_bstr());
	FItf->AddValue( WideString(FHSFFSet.op_entrust_way).c_bstr());
	FItf->AddValue( WideString(FHSFFSet.op_station).c_bstr());
	FItf->AddValue( WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());
	FItf->AddValue( WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue( WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue( WideString( "1004" ) );
	FItf->AddValue( WideString( this->ConvertMarketType(FRequest.Order.Market)));
	FItf->AddValue( WideString( this->GetStockAccountByMarket(FRequest.Order.Market)));
	FItf->AddValue( WideString( FRequest.Order.SecuID ));
	FItf->AddValue( WideString( this->ConvertOrderType( FRequest.Order.Type)[0] ));
	FItf->AddValue( WideString( this->ConvertOrderType( FRequest.Order.Type)[1] ));   //open or close 1,2 ,4
	FItf->AddValue( WideString( "0"));   //'0'	Ͷ��'1'	�ױ�
	FItf->AddValue( WideString( IntToStr( FRequest.Order.Num )).c_bstr());

	long lp = (long)(FRequest.Order.Price * 100.0f);
	if( lp % 10 >=5 )
		lp = lp/10 + 1;
	else
		lp = lp/10;

	String s;
	s.printf("%d.%d",lp/10,lp%10);
	FItf->AddValue( WideString( s ).c_bstr() );
	int	r	= SendAndReceive();
	try
	{
		if ( r < 0 )
		{
			return r;
		}
		else
		{
			String	id;
			if ( FItf->RecordCount > 0 )
			{
				id = String( FItf->FieldByName( WideString( "entrust_no" ) ) );
				if ( id.Length() > 0 )
				{
					NewAns( 1 );
					lstrcpyn( ( *FAnswer )[0].Order.ContractID, id.c_str(), SEQ_LEN);
					return 0;
				}
				return ERR_OTHERS;
			}
			else
			{
				return ERR_NO_ACK;
			}
		}
	}
	__finally
	{
		FItf->FreePack();
	}
	return 0;
}

/*
���ܺ�	1005	�汾��	3.2	��������	20060816
��������	�ڻ�ί�г���			���������	N
��������	�ڻ�ί�г���				
�������	������	����	˵��	����	ȱʡֵ
version	N3	�汾��		
op_branch_no	N5	����Ա��֧����		
op_entrust_way	C1	ί�з�ʽ		
identity_type	C1	�˻������� 1 ������ 2 ָ���� 3 ��ѯ Ĭ�ϲ�����
op_station	C12	վ��/�绰		
function_id	N6	ϵͳ����
branch_no	N5	��֧����
fund_account	N9	�ʽ��˺�		
password	C10	��������		
entrust_no	N8	ί�б��		
�������	������	����	˵��	����	ȱʡֵ
error_no	N4	�����		
error_info	C20	����ԭ��		
entrust_no	N8	ί�б��		
ҵ��˵��					

����˵��	�����	������Ϣ	����˵��	���󼶱�	
-51	�޴��ʻ�			
-61	�ڻ�ί�г���ʧ��	����������
*/
int TTrdItf_HSFF::Undo()
{
	FItf->SetHead( FHSFFSet.branch_no, 1005 );
	FItf->SetRange( 9, 1 );

	FItf->AddField( WideString( "version" ).c_bstr() );
	FItf->AddField( WideString( "op_branch_no" ).c_bstr() );
	FItf->AddField( WideString( "op_entrust_way" ).c_bstr() );
	FItf->AddField( WideString( "op_station" ).c_bstr() );
	FItf->AddField( WideString( "branch_no" ).c_bstr() );
	FItf->AddField( WideString( "fund_account" ).c_bstr() );
	FItf->AddField( WideString( "password" ).c_bstr() );
	FItf->AddField( WideString( "function_id" ).c_bstr() );
	FItf->AddField( WideString( "entrust_no" ).c_bstr() );


	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString( "1005" ).c_bstr() );
	FItf->AddValue(WideString( FRequest.Undo.ContractID ).c_bstr() );

	int	r	= SendAndReceive();
	try
	{
		if ( r != 0 )
		{
			if( strstr(FLastError.Text, "p_old_entrust_status = 6") != NULL )
			{
				// �Ѿ�������
				return ERR_UNDO_ALREADY_CANCLED;
			}
			else if (strstr(FLastError.Text, "p_old_entrust_status = 8") != NULL )
			{
				// ��ʾ�Ѿ��ɽ����޷�����
				return ERR_UNDO_ALREADY_FILLED;
			}
			else if (strstr(FLastError.Text, "p_old_entrust_status = 9") != NULL )
			{
				// ����ʾ�ϵ�
				return ERR_UNDO_REPEAL;
			}
			else if (strstr(FLastError.Text, "p_old_entrust_status = 5") != NULL )
			{
				// �Ѿ�������
				return ERR_UNDO_ALREADY_CANCLED;
			}

			return r;
		}
		else
		{
			if ( FItf->RecordCount > 0 )
			{
				//add_withdraw(FRequest.Undo.ContractID);
				return 0;
			}
			else
			{
				return ERR_NO_ACK;
			}
		}
	}
	__finally
	{
		FItf->FreePack();
	}
	return 0;
}

TTrdItf_HSFF::TTrdItf_HSFF( const char *psetupfile,ADDLOG plogfunc )
:TTrdItfBase(psetupfile,plogfunc)
{
	FHSFFSet.SvrIp          = "127.0.0.1";
	FHSFFSet.SvrPort        = 8008;
	FHSFFSet.Protocol       = 1;
	FHSFFSet.TimeOut        = 10000;
	FHSFFSet.KeyCipher      = 0;
	FHSFFSet.KeyDeKey       = "";
	FHSFFSet.debug_mode     = false;
	FHSFFSet.op_branch_no   = 0;
	FHSFFSet.op_station     = "";
	FHSFFSet.op_entrust_way = "4";
	FHSFFSet.branch_no      = 0;
	FHSFFSet.futu_exch_type = "";    
	FHSFFSet.futu_entrust_type ="0"; //0-��ͨ����ί��

	FAccount = "";

	FItf = NULL;
}

TTrdItf_HSFF::~TTrdItf_HSFF()
{
	CloseLink();
}

void TTrdItf_HSFF::CloseLink( void )
{
	this->lock();
	try
	{
		if( FItf!= NULL )
		{
			try
			{
				FItf->DisConnect();
			}
			catch(...)
			{
			}

			try
			{
				delete FItf;
			}
			catch(...)
			{

			}
			FItf = NULL;
		}

		TTrdItfBase::CloseLink();
	}
	__finally
	{
		this->unlock();
	}
}

market_type  TTrdItf_HSFF::ConvertMarketType(const char *t)
{
	// F1 F2 F3 F4
	if(t==NULL || strlen(t)<2 ) return mtNo;
	//ODS('M',PLUGINNAME,"�г�����:%s",t);
	switch(t[1])
	{
	case '1':  return mtFZZ;
	case '2':  return mtFDL;
	case '3':  return mtFSH;
	case '4':  return mtJJS;
	default:
		return mtNo;
	}
}

order_type   TTrdItf_HSFF::ConvertOrderType(const char *t)
{
	if(t==NULL || strlen(t)<2 ) return otNo;
	//ODS('M',PLUGINNAME,"ί������:%s",t);
	if( t[0]== ebbuy && t[1] == od_open ) return  otOpenBuy;
	if( t[0]== ebbuy && t[1] == od_close) return  otCloseBuy;
	if( t[0]== ebbuy && t[1] == od_close_today) return  otCloseTodayBuy;
	if( t[0]== ebsell && t[1] == od_open ) return  otOpenSell;
	if( t[0]== ebsell && t[1] == od_close) return  otCloseSell;
	if( t[0]== ebsell && t[1] == od_close_today) return  otCloseTodaySell;

	return otNo;
}

order_state  TTrdItf_HSFF::ConvertOrderState(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return osno;
	//ODS('M',PLUGINNAME,"ί��״̬:%s",t);
	switch (t[0])
	{
	case eswb    :   return oswb;      //δ��
	case esyb    :   return osyb;      //�ѱ�
	case esdc1   :   return osdc;      //����
	case esdc2   :   return osdc;      //����
	case esbc    :   return osbw;      //����
	case esyc1   :   return osyc;      //�ѳ�
	case esyc2   :   return osyc;      //�ѳ�
	case esyc    :   return oscj;      //�ѳ�
	case esyf    :   return osyf;      //�ѷ�
	default:
		return osno;
	}
}

pos_direction TTrdItf_HSFF::ConvertPosDir(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return pdNo;
	//ODS('M',PLUGINNAME,"��λ����:%s",t);
	switch( t[0] )
	{
	case '1': // ��ͷ
		return pdLong;
	case '2': // ��ͷ
		return pdShort;
	default:
		return pdNo;
	}
}

money_type   TTrdItf_HSFF::ConvertMoneyType(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return motNo;

	//ODS('M',PLUGINNAME,"�ʽ�����:%s",t);
	switch( t[0] )
	{
	case '0': return motRMB;
	case '1': return motUSD;
	case '2': return motHKD;
	default: return motNo;
	}
}

char *  TTrdItf_HSFF::ConvertMarketType(market_type t)
{
	switch(t)
	{
	case mtJJS: return "F4";
	case mtFDL: return "F2";
	case mtFZZ: return "F1";
	case mtFSH: return "F3";
	default:
		return "";
	}
}

char *  TTrdItf_HSFF::ConvertOrderType(order_type t)
{
	switch( t )
	{
	case otOpenBuy   :  return "11";
	case otOpenSell  :  return "21";
	case otCloseBuy  :  return "12";
	case otCloseSell :  return "22";
	case otCloseTodayBuy : return "14";
	case otCloseTodaySell: return "24";
	default:
		return "00";
	}
}

char *  TTrdItf_HSFF::ConvertOrderState(order_state t)
{
	return "";
}

char *  TTrdItf_HSFF::ConvertPosDir(pos_direction t)
{
	return "";
}

char *  TTrdItf_HSFF::ConvertMoneyType(money_type t)
{
	switch ( t )
	{
	case motRMB: return "0";
	case motUSD: return "1";
	case motHKD: return "2";
	default:
		return "0";
	}
}

bool TTrdItf_HSFF::GetConfig(void)
{
	if( FSetupFile== NULL ) return false;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		// �ж��Ƿ���ڲ�������ã�û�еĻ�����false�Ա�ϵͳ�ܹ�����Ĭ�ϵ�����
		if( ini->SectionExists(PLUGINNAME) == false ) return false;

		FHSFFSet.SvrIp            = ini->ReadString (PLUGINNAME,"SvrIP",FHSFFSet.SvrIp);
		FHSFFSet.SvrPort          = ini->ReadInteger(PLUGINNAME,"SvrPort",FHSFFSet.SvrPort);
		FHSFFSet.Protocol         = ini->ReadInteger(PLUGINNAME,"Protocol",FHSFFSet.Protocol);
		FHSFFSet.TimeOut          = ini->ReadInteger(PLUGINNAME,"TimeOut",FHSFFSet.TimeOut);
		FHSFFSet.KeyCipher        = ini->ReadInteger(PLUGINNAME,"KeyCipher",FHSFFSet.KeyCipher);
		FHSFFSet.KeyDeKey         = ini->ReadString (PLUGINNAME,"KeyDeKey",FHSFFSet.KeyDeKey);
		FHSFFSet.debug_mode       = ini->ReadBool(PLUGINNAME,"debug_mode",FHSFFSet.debug_mode);
		FHSFFSet.op_branch_no     = ini->ReadInteger(PLUGINNAME,"op_branch_no",FHSFFSet.op_branch_no);
		FHSFFSet.op_entrust_way   = ini->ReadString (PLUGINNAME,"op_entrust_way",FHSFFSet.op_entrust_way);
		FHSFFSet.branch_no        = ini->ReadInteger(PLUGINNAME,"branch_no",FHSFFSet.branch_no);
		FHSFFSet.op_station       = ini->ReadString (PLUGINNAME,"op_station",FHSFFSet.op_station);
		if (FHSFFSet.op_station.Length() < 7) {
			FHSFFSet.op_station.printf("192.168.1.%d",rand()%200+1);
			ODS("OPSTATION:%s",FHSFFSet.op_station.c_str());
		}
		//FHSFFSet.futu_exch_type   = ini->ReadString (PLUGINNAME,"futu_exch_type",FHSFFSet.futu_exch_type);
		//FHSFFSet.futu_entrust_type= ini->ReadString (PLUGINNAME,"futu_entrust_type",FHSFFSet.futu_entrust_type);
		PTSConStr = ini->ReadString(PLUGINNAME,"PTSDB",PTSConStr) ;
		m_report_withdraw = ini->ReadBool(PLUGINNAME,"ReportWithdraw",m_report_withdraw);
	}
	__finally
	{
		delete ini;
	}
	return true;
}

void TTrdItf_HSFF::SetConfig(void)
{
	if( FSetupFile== NULL ) return ;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		ini->WriteString (PLUGINNAME,"SvrIP",            FHSFFSet.SvrIp);
		ini->WriteInteger(PLUGINNAME,"SvrPort",          FHSFFSet.SvrPort);
		ini->WriteInteger(PLUGINNAME,"Protocol",         FHSFFSet.Protocol);
		ini->WriteInteger(PLUGINNAME,"TimeOut",          FHSFFSet.TimeOut);
		ini->WriteInteger(PLUGINNAME,"KeyCipher",        FHSFFSet.KeyCipher);
		ini->WriteString (PLUGINNAME,"KeyDeKey",         FHSFFSet.KeyDeKey);
		ini->WriteBool   (PLUGINNAME,"debug_mode",       FHSFFSet.debug_mode);
		ini->WriteInteger(PLUGINNAME,"op_branch_no",     FHSFFSet.op_branch_no);
		ini->WriteString (PLUGINNAME,"op_entrust_way",   FHSFFSet.op_entrust_way);
		ini->WriteInteger(PLUGINNAME,"branch_no",        FHSFFSet.branch_no);
		ini->WriteString (PLUGINNAME,"op_station",       FHSFFSet.op_station);
		ini->WriteString(PLUGINNAME,"PTSDB",PTSConStr) ;
		ini->WriteBool(PLUGINNAME,"ReportWithdraw",m_report_withdraw);
		//ini->WriteString (PLUGINNAME,"futu_exch_type",   FHSFFSet.futu_exch_type);
		//ini->WriteString (PLUGINNAME,"futu_entrust_type",FHSFFSet.futu_entrust_type);
		ini->UpdateFile();
	}
	__finally
	{
		delete ini;
	}
}

int TTrdItf_HSFF::KeepAlive(void)
{
	this->lock();
	try
	{
		if( FHasSetAccInfo )
		{
		/*
			TRequest req={};
			TAnswer *ans=NULL;
			int anscount= 0;
			req.Head.FuncType=ftQryMoney;
			req.QryMoney.MoneyType=motRMB;
			int ret = this->Request(req,&ans,anscount);
			if( ans!=NULL )
			{
				this->FreeAnswer(ans);
				ans = NULL;
				ODS("KEEPALIVE,%d,%d",ans[0].QryMoney.MoneyInfo.balance,
					ans[0].QryMoney.MoneyInfo.available);
			}
			if( ret != 0 )
			{
				ODS("Auto Reconnect...");
				req.Head.FuncType = ftInit;
				ret = this->Request(req,&ans,anscount);
				if( ret == 0)
				{
					ODS("Auto Reconnected.");
				}
			}
		*/
			try
			{
				FItf->SetHead( FHSFFSet.branch_no, 1508 );
				FItf->SetRange( 9, 1 );

				FItf->AddField( WideString( "version" ).c_bstr() );
				FItf->AddField( WideString( "op_branch_no" ).c_bstr() );
				FItf->AddField( WideString( "op_entrust_way" ).c_bstr() );
				FItf->AddField( WideString( "op_station" ).c_bstr() );
				FItf->AddField( WideString( "branch_no" ).c_bstr() );
				FItf->AddField( WideString( "fund_account" ).c_bstr() );
				FItf->AddField( WideString( "password" ).c_bstr() );
				FItf->AddField( WideString( "function_id" ).c_bstr() );
				FItf->AddField( WideString( "money_type" ).c_bstr() );

				FItf->AddValue(WideString(HS_VERSION).c_bstr());
				FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
				FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
				FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
				FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());
				FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
				FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
				FItf->AddValue(WideString( "1508" ).c_bstr() );
				FItf->AddValue(WideString( ConvertMoneyType(motRMB)).c_bstr() );

				int	r	= SendAndReceive();

				if ( r < 0 )
				{
					return r;
				}
				else
				{
					if ( FItf->RecordCount > 0 )
					{
						ODS("KEEPALIVE:OK");
						return 0;
					}
					else
					{
						ODS("KEEPALIVE:Try to reconnect...") ;
						r = this->Init();
						if( r==0 )
						{
                        	ODS("KEEPALIVE:Connected!") ;
						}
						else
						{
                        	return -1;
						}
					}
				}
			}
			__finally
			{
				FItf->FreePack();
			}

		}
	}
	__finally
	{
		this->unlock();
	}
	return 0;
}

int TTrdItf_HSFF::QryOrderByOrdid(TTradeInfo * ti)
{
	int r = 0;
	String position_str = "";

	lock();

	try
	{
		FItf->SetHead( FHSFFSet.branch_no, 1504 );
		FItf->SetRange( 17, 1 );

		FItf->AddField(WideString("version").c_bstr());
		FItf->AddField(WideString("op_branch_no").c_bstr());
		FItf->AddField(WideString("op_entrust_way").c_bstr());
		FItf->AddField(WideString("op_station").c_bstr());
		FItf->AddField(WideString("function_id").c_bstr());
		FItf->AddField(WideString("branch_no").c_bstr());

		FItf->AddField(WideString("fund_account").c_bstr());
		FItf->AddField(WideString("password").c_bstr());
		FItf->AddField(WideString("futu_exch_type").c_bstr());
		FItf->AddField(WideString("futures_account").c_bstr());

		FItf->AddField(WideString("contract_code").c_bstr());
		FItf->AddField(WideString("en_entrust_status").c_bstr());         //en_entrust_status������
		FItf->AddField(WideString("query_direction").c_bstr());
		FItf->AddField(WideString("batch_no").c_bstr());
		FItf->AddField(WideString("futu_entrust_type").c_bstr());
		FItf->AddField(WideString("request_num").c_bstr());
		FItf->AddField(WideString("position_str").c_bstr());


		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue( WideString( "1504" ) );
		FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());

		FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
		FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
		FItf->AddValue( WideString( ""/*FHSFFSet.futu_exch_type*/ ) );
		FItf->AddValue( WideString( ""/*this->FAccInfo.FJJS*/ ));  //�ڻ��ʻ�
		FItf->AddValue( WideString( "" ) );
		FItf->AddValue( WideString( "" ) );
		FItf->AddValue( WideString( ( char ) qdahead ) );
		FItf->AddValue( WideString( ti->ContractID ) );
		FItf->AddValue( WideString( FHSFFSet.futu_entrust_type ) );
		FItf->AddValue( WideString( IntToStr(FRequest.QryCurCsn.MaxRecord) ) );
		FItf->AddValue( WideString( position_str ) );

		r = SendAndReceive();

		if ( FItf->RecordCount < 1 || r < 0 ) return r;

		for ( int i = 0; i < FItf->RecordCount; ++i)
		{

			//�齨�������
			lstrcpyn( ti->SecuID, String( FItf->FieldByName( WideString( "contract_code" ) ) ).c_str() ,CODE_LEN);
			lstrcpyn( ti->Account, String( FItf->FieldByName( WideString( "futures_account" ) ) ).c_str() ,ACC_LEN);
			ti->Market = this->ConvertMarketType(
				String( FItf->FieldByName( WideString( "futu_exch_type" ) ) ).c_str());
			ti->Time = this->ConvertTimeToInt(
				String( FItf->FieldByName( WideString( "report_time" ) ) ).c_str() );
			ti->Date = this->ConvertDateToInt(
				String( FItf->FieldByName( WideString( "init_date" ) ) ).c_str() );
			ti->Type = this->ConvertOrderType(
				(String( FItf->FieldByName( WideString( "entrust_bs" ) ) ) +
				String( FItf->FieldByName( WideString( "futures_direction" ) ) )).c_str()  );

			long CsnVol = StrToFloatDef(FItf->FieldByName( WideString( "entrust_amount" ) ), 0 );
			long TrdVol = StrToFloatDef( FItf->FieldByName( WideString( "business_amount" ) ), 0 );
			long CancelVol = - StrToFloatDef( FItf->FieldByName( WideString( "cancel_amount" ) ), 0 );

			if( CsnVol == TrdVol  )     //�ѳɽ�
			{
				ti->Vol = TrdVol;
				/*
				ODS('U',PLUGINNAME, "%s,%s,%d,%d,%d,%c,%f,%c,%s",
				ti->ContractID,
				ti->SecuID,
				ti->Time,
				ti->Date,
				ti->Vol,
				ti->Type,
				ti->Price,
				ti->Market,
				ti->Account);
				*/
			}
			else if(  CancelVol <  0)   //�ѳ���
			{
				ti->Vol = CancelVol;
				ODS('Q',PLUGINNAME, "%s,%s,%d,%d,%d,%c,%f,%c,%s",
					ti->ContractID,
					ti->SecuID,
					ti->Time,
					ti->Date,
					ti->Vol,
					ti->Type,
					ti->Price,
					ti->Market,
					ti->Account);
			}

			//lstrcpyn(ti->SeqNum,FLastSeq.c_str(),SEQ_LEN);
			break;
		}
	}
	__finally
	{
		unlock();
	}
	return r;
}

