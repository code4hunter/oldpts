//---------------------------------------------------------------------------
#include <assert.h>
#include <IniFiles.hpp>
#include "uPriceFunc.h"
#include "UTrdItf_HSStk.h"
//---------------------------------------------------------------------------

#define HS_VERSION "111"

int TTrdItf_HSStk:: Init()
{
	this->CloseLink();

	FItf = new TComm( NULL );
	FItf->Create();
	FItf->set_SendTimeOut( FHSFFSet.TimeOut );
	FItf->set_ReceiveTimeOut( FHSFFSet.TimeOut );

	return FItf->ConnectX( FHSFFSet.Protocol,
		WideString(FHSFFSet.SvrIp).c_bstr(),
		FHSFFSet.SvrPort,
		FHSFFSet.KeyCipher,
		WideString(FHSFFSet.KeyDeKey).c_bstr(),
		FHSFFSet.KeyDeKey.Length());
}

int TTrdItf_HSStk::SendAndReceive()
{
	try
	{
        if( FHSFFSet.debug_mode )
		{
			char buf[1024];
			lstrcpyn(buf,AnsiString(FItf->Buffer).c_str(),1023);
			buf[1023]=0;
			int len = strlen(buf);
			for(int i=0;i<len;i++ )
			{
				if ( buf[i]=='\x01' )
					buf[i] = '#';
			}
			ODS('M',PLUGINNAME,"SEND BUF:%s",buf) ;
		}

		if ( FItf->Send()!=0 )
		{
			/*this->SetLastError(ERR_REMOTE_SEND_FAILED,'E',PLUGINNAME,"�������ݴ�����ͼ�ָ�����...,connection=%d",FItf->Connection);

            WideString buf(FItf->Buffer);

            this->CloseLink();
            this->Init();
            this->login();

            FItf->set_Buffer(buf.c_bstr());
            if ( FItf->Send()!=0 )   */
            {
                this->SetLastError(ERR_REMOTE_SEND_FAILED,'E',PLUGINNAME,"�������ݴ��󣬻ָ�����ʧ��.,connection=%d",FItf->Connection);
			    return ERR_REMOTE_SEND_FAILED;
            }
		}

		FItf->FreePack();

		if ( FItf->Receive()!=0 )
		{
            /*
			this->SetLastError(ERR_REMOTE_RECV_FAILED,'E',PLUGINNAME,"�������ݴ���,��ͼ�ָ�����...,connection=%d",FItf->Connection);
            WideString buf(FItf->Buffer);
            this->CloseLink();
            this->Init();
            this->login();
            FItf->set_Buffer(buf.c_bstr());
            if ( FItf->Send()!=0 )
            {
                this->SetLastError(ERR_REMOTE_SEND_FAILED,'E',PLUGINNAME,"�������ݴ��󣬻ָ�����ʧ�ܡ�,connection=%d",FItf->Connection);
			    return ERR_REMOTE_SEND_FAILED;
            }
            if ( FItf->Receive()!=0 )*/
            {
                this->SetLastError(ERR_REMOTE_RECV_FAILED,'E',PLUGINNAME,"�������ݴ���,�ָ�����ʧ��.,connection=%d",FItf->Connection);
			    return ERR_REMOTE_RECV_FAILED;
            }
		}

		if( FHSFFSet.debug_mode )
		{
			char buf[1024];
			lstrcpyn(buf,AnsiString(FItf->Buffer).c_str(),1023);
			buf[1023]=0;
			int len = strlen(buf);
			for(int i=0;i<len;i++ )
			{
				if ( buf[i]=='\x01' )
					buf[i] = '#';
			}
			ODS('M',PLUGINNAME,"RECV BUF:%s",buf) ;
		}

		if ( FItf->ErrorNo!=0 )
		{
			lstrcpyn( FLastError.Sender ,"HSSTK", SEQ_LEN);
			FLastError.ErrorCode = -abs(FItf->ErrorNo);
			lstrcpyn( FLastError.Text,AnsiString( FItf->ErrorMsg ).c_str(),MAX_TEXT );
			ODS('E',PLUGINNAME, "��̨��ʾ:%s,ErrNo:%d",FLastError.Text,FLastError.ErrorCode );
			return FLastError.ErrorCode;
		}
	}
	catch( Exception &e )
	{
		lstrcpyn( FLastError.Sender ,"HSSTK", SEQ_LEN);
		FLastError.ErrorCode = ERR_REMOTE_OTHER_FAILED;
		lstrcpyn( FLastError.Text,AnsiString(e.Message).c_str(),MAX_TEXT );

		ODS('E',PLUGINNAME, "�������:%s",AnsiString(e.Message).c_str() );
		return ERR_REMOTE_OTHER_FAILED;
	}
	catch(...)
	{
		lstrcpyn( FLastError.Sender ,"HSSTK", SEQ_LEN);
		FLastError.ErrorCode = ERR_REMOTE_OTHER_FAILED;
		lstrcpyn( FLastError.Text,"δ֪����",MAX_TEXT );

		ODS('E',PLUGINNAME, "�������:%s",FLastError.Text );
		return ERR_REMOTE_OTHER_FAILED;
	}
	return 0;
}


/*
���ܺ�	200	�汾��	3.6	��������	20051215
��������	�ͻ���������У��			���������	N
ҵ��Χ	����			����״̬	����
��������	�ͻ���������У��
�������	������	����	˵��	����	ȱʡֵ
	version	N3	�汾��
��Ա	l_op_code	N8	��Ա��
��Ա	vc_op_password	C8	��Ա����
	op_entrust_way	C1	ί�з�ʽ
	op_station	C12	mac��ַ/ip
�ʺ�	account_content	N9	�ʽ��ʺ� ͬfund_account ����
�ʺ�	password	C10	��������
�������	������	����	˵��	����	ȱʡֵ
	error_no	N4	�����
	error_info	C255	����ԭ��
	branch_no	N5	��֧����
	fund_account	N9	�ʽ��˺�
	client_name	C14	�ʺ�����
	money_count	C1
	money_type	C1	�������
	exchange_type	C4	�������Ŀǰ����Ϊ��
	stock_account	C11	�ʽ��ʺţ�Ŀǰ����Ϊ�ա�
	client_rights	C64	�ʽ��ʺ���Ȩ�޵�֤ȯ��𣬱������ʲ�����ϵͳ�У���������֤ȯ���
ҵ��˵��	�ͻ���������У��

����˵��	�����	������Ϣ	����˵��	���󼶱�
	-41	�ʽ����뵽��δ�޸� ������ʾ���Կɵ�¼��
	-42	���������뵽��δ�޸ġ�        ������ʾ���Կɵ�¼��
	-51	�޴��ʻ�
	-63	�������
	-66	�����ʻ�״̬������	����������
	-64	��û�д���ί�е�Ȩ��
	-61	�ʻ���¼ʧ�� ����������

*/

int TTrdItf_HSStk::login(void)
{
    try
	{
		FItf->SetHead( FHSFFSet.branch_no, 200 );
		FItf->SetRange( 7, 1 );

		FItf->AddField(WideString(L"version").c_bstr());
		FItf->AddField(WideString(L"l_op_code").c_bstr());
		FItf->AddField(WideString(L"vc_op_password").c_bstr());
		FItf->AddField(WideString(L"op_entrust_way").c_bstr());
		FItf->AddField(WideString(L"op_station").c_bstr());
		FItf->AddField(WideString(L"account_content").c_bstr());
		FItf->AddField(WideString(L"password").c_bstr());

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.l_op_code).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.vc_op_password).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
        FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
		FItf->AddValue(WideString(FAccInfo.PW).c_bstr());

		int	r	= SendAndReceive();

		if ( r < 0 )
		{
			return r;
		}
	}
	__finally
	{
		FItf->FreePack();
	}

	return 0;
}

int TTrdItf_HSStk::SetAccount()
{
	try
	{
		FAccInfo.lt = FRequest.SetAccount.LoginType;
		FAccount = FRequest.SetAccount.Account;
		lstrcpyn( FAccInfo.PW, FRequest.SetAccount.PW, 13 );

		FItf->SetHead( FHSFFSet.branch_no, 200 );
		FItf->SetRange( 7, 1 );

		FItf->AddField(WideString(L"version").c_bstr());
		FItf->AddField(WideString(L"l_op_code").c_bstr());
		FItf->AddField(WideString(L"vc_op_password").c_bstr());
		FItf->AddField(WideString(L"op_entrust_way").c_bstr());
		FItf->AddField(WideString(L"op_station").c_bstr());
		FItf->AddField(WideString(L"account_content").c_bstr());
		FItf->AddField(WideString(L"password").c_bstr());

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.l_op_code).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.vc_op_password).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
        FItf->AddValue(WideString(FRequest.SetAccount.Account).c_bstr());
		FItf->AddValue(WideString(FRequest.SetAccount.PW).c_bstr());

		int	r	= SendAndReceive();

		if ( r < 0 )
		{
			return r;
		}
		else
		{
			lstrcpyn(FAccInfo.Capital,FRequest.SetAccount.Account,ACC_LEN);
            FDisconnected = false;
		}
	}
	__finally
	{
		FItf->FreePack();
	}

	return 0;
}

/*
���ܺ�	405	�汾��	3.6	��������	20080708
��������	��ѯ�ʽ�			���������	Y
ҵ��Χ	����			����״̬	����
��������	��ѯ�ʽ�
�������	������	����	˵��	����	ȱʡֵ
	version	N3	�汾��
��Ա	l_op_code	N8	��Ա��
��Ա	vc_op_password	C8	��Ա����
	op_entrust_way	C1	ί�з�ʽ
	op_station	C12	mac��ַ/ip
�ʺ�	fund_account	N9	�ʽ��˺�
�ʺ�	password	C10	��������
�������	������	����	˵��	����	ȱʡֵ
	money_type	C1	�������
	current_balance	N16.2	��ǰ���
	enable_balance	N16.2	���ý��
	fetch_balance	N16.2	��ȡ���
	interest	N16.2	��������Ϣ
	asset_balance	N16.2	�ʲ���ֵ
	pre_interest	N16.2	Ԥ����Ϣ
ҵ��˵��

����˵��	�����	������Ϣ	����˵��	���󼶱�
	-61	��ѯ�ʽ�ʧ��	����������
*/
int TTrdItf_HSStk::QryMoney()
{
    if( FDisconnected == true )
        return   ERR_REMOTE_OTHER_FAILED;

	try
	{
		FItf->SetHead( FHSFFSet.branch_no, 405 );
		FItf->SetRange( 7, 1 );

		FItf->AddField(WideString(L"version").c_bstr());
		FItf->AddField(WideString(L"l_op_code").c_bstr());
		FItf->AddField(WideString(L"vc_op_password").c_bstr());
		FItf->AddField(WideString(L"op_entrust_way").c_bstr());
		FItf->AddField(WideString(L"op_station").c_bstr());
		FItf->AddField(WideString(L"fund_account").c_bstr());
		FItf->AddField(WideString(L"password").c_bstr());

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.l_op_code).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.vc_op_password).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
		FItf->AddValue(WideString(FAccInfo.PW).c_bstr());

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

				( *FAnswer )[0].QryMoney.MoneyInfo.balance =
					StrToFloatDef( String( FItf->FieldByName( WideString( L"current_balance" ).c_bstr() ) ), 0 );
				( *FAnswer )[0].QryMoney.MoneyInfo.available =
					StrToFloatDef( String( FItf->FieldByName( WideString( L"enable_balance" ).c_bstr() ) ), 0 );
				( *FAnswer )[0].QryMoney.MoneyInfo.MoneyType =
					ConvertMoneyType( AnsiString( FItf->FieldByName( WideString( L"money_type" ).c_bstr() ) ).c_str() );

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
���ܺ�	401	�汾��	3.6	��������	20051215
��������	��ѯί��			���������	Y
ҵ��Χ	����			����״̬	����
��������	��ѯί��
�������	������	����	˵��	����	ȱʡֵ
	version	N3	�汾��
��Ա	l_op_code	N8	��Ա��
��Ա	vc_op_password	C8	��Ա����
	op_entrust_way	C1	ί�з�ʽ
	op_station	C12	mac��ַ/ip
�ʺ�	fund_account	N9	�ʽ��˺�
�ʺ�	password	C10	��������
	exchange_type	C4	������������Ϊ�ո񣬲�ȷ���ģ�Ϊ�գ������С�
	stock_code	C6	֤ȯ���룬���Ϊ�ո񣬲����У���Ϊ�գ���ȷ���ģ���ʱexchange_type���벻Ϊ��
	locate_entrust_no	N8	ָ��ί�кţ���ָ��ί�кŵ�ί�У���request_numΪ1����ǰ̨���յ�Ӧ���Ҫ��鷵�ص�ί�е�ί�к��Ƿ���Ҫ���ѯ��һ�£���ʱexchange_type��stock_codeҪΪ�մ���
	query_direction	C1	��ѯ����
	sort_direction	C1	����ʽ '0' ���� '1'����
	request_num	N8	�������������Ͱ�50�д�������ϵͳָ��ֵ��1000�У���ϵͳָ��ֵ��1000�У�����
	position_str	C32	��λ��
�������	������	����	˵��	����	ȱʡֵ
	position_str	C32	��λ��
	entrust_no	N8	ί�����
	batch_no	N8	ί������
	exchange_type	C4	�������
	stock_account	C11	֤ȯ�˺�
	stock_code	C6	֤ȯ����
	stock_name	C8	֤ȯ����
	entrust_bs	C1	��������
	bs_name	C60	������������
	entrust_price	N9.3	ί�м۸�
	entrust_amount	N16.2	ί������
	business_amount	N16.2	�ɽ�����
	business_price	N9.3	�ɽ��۸�
	report_no	N8	�걨��
	report_time	N8	�걨ʱ��
	entrust_type	C1	ί�����
	type_name	C64	ί���������
	entrust_status	C1	ί��״̬
	status_name	C60	״̬����
	cancel_info	C255	�ϵ�ԭ��
	entrust_prop	C1	ί������
	entrust_prop_name	C1	ί������
ҵ��˵��

����˵��	�����	������Ϣ	����˵��	���󼶱�
	-52	�޴˹�Ʊ	���˴���ɲ����жϣ�
	-60	û��ί�м�¼
	-61	��ѯί��ʧ��	����������

*/

/*
##entrust_bs_name#hedge_type#hedge_type_name#futu_entrust_price#amount_per_hand#entrust_amount#business_amount#cancel_amount#hold_balance#entrust_time#report_time#entrust_status#status_name#futu_entrust_type#futu_entrust_type_name#confirm_no#frozen_fare#forceclose_reason#forceclose_reason_name#batch_no#error_message#
20070410000010000000092#20070410#92#100359#����#F4#���ڽ���#207130023052#IF0704#��ָ0704#0#1#����#1#����#0#Ͷ��#3050.0000#300#1.0000#0#0#137350.0000#103339#103750#C#����#0#ί��# #100.0000#0##92# #


*/
int TTrdItf_HSStk::QryCurCsn()
{
    if( FDisconnected == true )
        return   ERR_REMOTE_OTHER_FAILED;

	TList* ResultList = new TList();

	int r = 0;
	String position_str = FRequest.QryCurCsn.SeqNum;

	do
	{
		FItf->SetHead( FHSFFSet.branch_no, 401 );
		FItf->SetRange( 14, 1 );

        FItf->AddField(WideString(L"version").c_bstr());
		FItf->AddField(WideString(L"l_op_code").c_bstr());
		FItf->AddField(WideString(L"vc_op_password").c_bstr());
		FItf->AddField(WideString(L"op_entrust_way").c_bstr());
		FItf->AddField(WideString(L"op_station").c_bstr());
		FItf->AddField(WideString(L"fund_account").c_bstr());
		FItf->AddField(WideString(L"password").c_bstr());

        FItf->AddField(WideString(L"exchange_type").c_bstr());
        FItf->AddField(WideString(L"stock_code").c_bstr());

		FItf->AddField(WideString(L"locate_entrust_no").c_bstr());
		FItf->AddField(WideString(L"query_direction").c_bstr());
		FItf->AddField(WideString(L"sort_direction").c_bstr());
		FItf->AddField(WideString(L"request_num").c_bstr());
		FItf->AddField(WideString(L"position_str").c_bstr());


		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.l_op_code).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.vc_op_password).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
		FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
        FItf->AddValue(WideString(L" ").c_bstr() );
        FItf->AddValue(WideString(L" ").c_bstr() );
		FItf->AddValue(WideString(FRequest.QryCurCsn.OrderID).c_bstr() );
		FItf->AddValue(WideString(L'1').c_bstr() );
		FItf->AddValue(WideString(L'0').c_bstr() );
		FItf->AddValue(WideString(IntToStr((int)FRequest.QryCurCsn.MaxRecord)).c_bstr());
		FItf->AddValue(WideString( position_str ).c_bstr() );

		r = SendAndReceive();

		if ( FItf->RecordCount < 1 || r < 0 ) break;

		for ( int i = 0; i < FItf->RecordCount; ++i)
		{
			TOrderInfo*	ci	= new TOrderInfo;
			ZeroMemory( ci, sizeof( TOrderInfo ) );
			ResultList->Add(ci);

			//�齨�������
			lstrcpyn( ci->ContractID, AnsiString( FItf->FieldByName( WideString( L"entrust_no" ).c_bstr() ) ).c_str() ,SEQ_LEN);
			lstrcpyn( ci->SecuID, AnsiString( FItf->FieldByName( WideString( L"stock_code" ).c_bstr() ) ).c_str() ,CODE_LEN);
			lstrcpyn( ci->Account, AnsiString( FItf->FieldByName( WideString( L"stock_account" ).c_bstr() ) ).c_str() ,ACC_LEN);
			ci->Market = this->ConvertMarketType(
				AnsiString( FItf->FieldByName( WideString( L"exchange_type" ).c_bstr() ) ).c_str());
			ci->Time = this->ConvertTimeToInt(
				AnsiString( FItf->FieldByName( WideString( L"entrust_time" ).c_bstr() ) ).c_str() );
			ci->Date = FormatDateTime(L"yyyymmdd",Date()).ToIntDef(0);
			ci->Type = this->ConvertOrderType(
				AnsiString(
				//String( FItf->FieldByName( WideString( L"entrust_type" ).c_bstr() ) ) +
				//String( FItf->FieldByName( WideString( L"entrust_bs" ).c_bstr() ) ) +
				//String( FItf->FieldByName( WideString( L"entrust_prop" ).c_bstr() ) )
                String( FItf->FieldByName( WideString( L"bs_name" ).c_bstr() ) )
				).c_str()  );
			ci->State = this->ConvertOrderState(
				AnsiString( FItf->FieldByName( WideString( L"entrust_status" ).c_bstr() ) ).c_str());
			ci->CsnVol = StrToFloatDef(FItf->FieldByName( WideString( L"entrust_amount" ).c_bstr() ), 0 );
			ci->TrdVol = StrToFloatDef( FItf->FieldByName( WideString( L"business_amount" ).c_bstr() ), 0 );
			ci->CsnPrice = StrToFloatDef( FItf->FieldByName( WideString( L"entrust_price" ).c_bstr() ), 0 );
			ci->CancelVol = - StrToFloatDef( FItf->FieldByName( WideString( L"cancel_amount" ).c_bstr() ), 0 );
			ci->TrdPrice = StrToFloatDef( FItf->FieldByName( WideString( L"business_price" ).c_bstr() ), 0 );;
			lstrcpyn(ci->SeqNum,
				AnsiString( FItf->FieldByName( WideString( L"position_str" ).c_bstr())).c_str(),SEQ_LEN);
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

���ܺ�	402	�汾��	3.6	��������	20051215
��������	��ѯ�ɽ�			���������	Y
ҵ��Χ	����			����״̬	����
��������	��ѯ�ɽ�
�������	������	����	˵��	����	ȱʡֵ
	version	N3	�汾��
��Ա	l_op_code	N8	��Ա��
��Ա	vc_op_password	C8	��Ա����
	op_entrust_way	C1	ί�з�ʽ
	op_station	C12	mac��ַ/ip
�ʺ�	fund_account	N9	�ʽ��˺�
�ʺ�	password	C10	��������
	exchange_type	C4	������𣬲�Ϊ�գ���ȷ���ģ�Ϊ�գ�������
	stock_code	C6	֤ȯ���룬Ϊ�գ������У���Ϊ�գ���ȷ���ģ���ʱexchange_type���벻Ϊ��
	query_mode	C1	��ѯģʽ '0' ��ϸ
	request_num	N8	�������������Ͱ�50�д�������ϵͳָ��ֵ��1000�У���ϵͳָ��ֵ��1000�У�����
	serial_no	N8	ί�кţ�Ϊ�ղ�ѯȫ��
	batch_serial_no	N8	ί�����ţ���Ϊ0ʱΪ���ί�����ŵĳɽ���Ϣ
	position_str	C32	��λ��
�������	������	����	˵��	����	ȱʡֵ
	position_str	C32	��λ��
	serial_no	N8	�ɽ����
	date	N8	����
	exchange_type	C4	�������
	stock_account	C11	֤ȯ�˺�
	stock_code	C6	֤ȯ����
	stock_name	C8	֤ȯ����
	entrust_bs	C1	ί�з���
	bs_name	C60	ί�з�������
	business_price	N9.3	�ɽ��۸�
	business_amount	N16.2	�ɽ�����
	business_time	N8	�ɽ�ʱ��
	business_status	C1	�ɽ�״̬ �������ֵ�
	status_name	C60	�ɽ�״̬����
	business_type	C1	�ɽ����0����������2����������
	type_name	C64	�ɽ��������
	business_times	N5	�ɽ�����
	entrust_no	N8	ί�к�
	report_no	N8	�걨��
	business_balance	N16.2	�ɽ����
ҵ��˵��

����˵��	�����	������Ϣ	����˵��	���󼶱�
	-52	�޴˹�Ʊ	���˴���ɲ����жϣ�
	-60	û�гɽ���¼
	-61	��ѯ�ɽ�ʧ��	����������


*/
int TTrdItf_HSStk::QryCurTrd()
{
    if( FDisconnected == true )
        return   ERR_REMOTE_OTHER_FAILED;

	TList* ResultList = new TList();
	int r = 0;
	String position_str = FRequest.QryCurTrd.SeqNum;

	do
	{
		FItf->SetHead( FHSFFSet.branch_no, 402 );
		FItf->SetRange( 14, 1 );

		FItf->AddField(WideString(L"version").c_bstr());
		FItf->AddField(WideString(L"l_op_code").c_bstr());
		FItf->AddField(WideString(L"vc_op_password").c_bstr());
		FItf->AddField(WideString(L"op_entrust_way").c_bstr());
		FItf->AddField(WideString(L"op_station").c_bstr());
		FItf->AddField(WideString(L"fund_account").c_bstr());
		FItf->AddField(WideString(L"password").c_bstr());

        FItf->AddField(WideString(L"exchange_type").c_bstr());
        FItf->AddField(WideString(L"stock_code").c_bstr());

		FItf->AddField(WideString(L"query_mode").c_bstr());
		FItf->AddField(WideString(L"request_num").c_bstr());
		FItf->AddField(WideString(L"serial_no").c_bstr());
		FItf->AddField(WideString(L"batch_serial_no").c_bstr());
		FItf->AddField(WideString(L"position_str").c_bstr());

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.l_op_code).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.vc_op_password).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
		FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
        FItf->AddValue(WideString(L" ").c_bstr() );
        FItf->AddValue(WideString(L" ").c_bstr() );
        FItf->AddValue(WideString(L"0").c_bstr() );
		FItf->AddValue(WideString(IntToStr((int)FRequest.QryCurTrd.MaxRecord)).c_bstr());
        FItf->AddValue(WideString(FRequest.QryCurTrd.OrderID).c_bstr() );
        FItf->AddValue(WideString(L"0").c_bstr() );
		FItf->AddValue(WideString( position_str ).c_bstr() );

		r = SendAndReceive();

		if ( FItf->RecordCount < 1 || r < 0 ) break;

		for ( int i = 0; i < FItf->RecordCount; ++i)
		{
			TTradeInfo*	ti	= new TTradeInfo;
			ZeroMemory( ti, sizeof( TTradeInfo ) );

			//�齨�������
			lstrcpyn( ti->ContractID ,
				AnsiString( FItf->FieldByName( WideString( L"entrust_no" ).c_bstr() ) ).c_str(),SEQ_LEN);
			lstrcpyn( ti->TrdID ,
				AnsiString( FItf->FieldByName( WideString( L"serial_no" ).c_bstr() ) ).c_str(),SEQ_LEN);
			lstrcpyn( ti->SecuID,
				AnsiString( FItf->FieldByName( WideString( L"stock_code" ).c_bstr() ) ).c_str(),CODE_LEN);
			lstrcpyn( ti->Account,
				AnsiString( FItf->FieldByName( WideString( L"stock_account" ).c_bstr() ) ).c_str(),ACC_LEN);
			ti->Time = this->ConvertTimeToInt(
				AnsiString( FItf->FieldByName( WideString( L"business_time" ).c_bstr() ) ).c_str() );
			ti->Date =FormatDateTime(L"yyyymmdd",Date()).ToIntDef(0); //this->ConvertDateToInt(
				//AnsiString( FItf->FieldByName( WideString( L"date" ).c_bstr() ) ).c_str() );
            AnsiString ot = AnsiString(FItf->FieldByName( WideString( L"bs_name" ).c_bstr() ));
			ti->Type = this->ConvertOrderType(ot.c_str()  );
			ti->Vol = abs((long)StrToIntDef( FItf->FieldByName( WideString( L"business_amount" ).c_bstr() ), 0 ));

			if( WideString(FItf->FieldByName( WideString( L"business_type" ).c_bstr() )) == L"2" ) //����
			{
            	ti->Vol = -ti->Vol;
			}
			ti->Price = StrToFloatDef( FItf->FieldByName( WideString( L"business_price" ).c_bstr() ), -1 );
			ti->Market = this->ConvertMarketType(
				AnsiString( FItf->FieldByName( WideString( L"exchange_type" ).c_bstr() ) ).c_str());
			lstrcpyn(ti->SeqNum ,
				AnsiString( FItf->FieldByName( WideString( L"position_str" ).c_bstr() ) ).c_str(),SEQ_LEN);
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

���ܺ�	403	�汾��	3.6	��������	20051215
��������	��ѯ��Ʊ			���������	Y
ҵ��Χ	����			����״̬	����
��������	��ѯ��Ʊ
�������	������	����	˵��	����	ȱʡֵ
	version	N3	�汾��
��Ա	l_op_code	N8	��Ա��
��Ա	vc_op_password	C8	��Ա����
	op_entrust_way	C1	ί�з�ʽ
	op_station	C12	mac��ַ/ip
�ʺ�	fund_account	N9	�ʽ��˺�
�ʺ�	password	C10	��������
	exchange_type	C4	������𣬲�Ϊ�գ���ȷ���ģ�Ϊ�գ������С�
	stock_code	C6	֤ȯ���룬Ϊ�գ������У���Ϊ�գ���ȷ���ģ���ʱexchange_type���벻Ϊ�ա�
	query_mode	C1	��0����֤ȯ�����ϸ��ʾ����1����֤ȯ�������
	request_num	N8	�������������Ͱ�50�д�������ϵͳָ��ֵ��1000�У���ϵͳָ��ֵ��1000�У�����
	position_str	C32	��λ�������ܲ�ѯʱΪexchange_type+stock_code����ϸ��ѯʱΪbranch_no+exchange_type+stock_account+stock_code�ܳ���Ϊ24���ֽڡ�
�������	������	����	˵��	����	ȱʡֵ
	position_str	C32	��λ��
	exchange_type	C4	�������
	stock_account	C11	֤ȯ�˺�
	stock_code	C6	֤ȯ����
	stock_name	C8	֤ȯ����
	current_amount	N16.2	��ǰ����
	enable_amount	N16.2	������Ʊ
	last_price	N9.3	���¼�
	cost_price	N9.3	�ɱ���
	income_balance	N16.2	����ӯ��(����ӯ��)
	gain_income	N16.2	ʵ������
	total_income	N16.2	��ӯ��
	hand_flag	C1	���ֱ�־��'0'--��   '1' -- �֡�
	market_value	N16.2	֤ȯ��ֵ������ϸ��Ϊÿ���ɶ��ʺŵ���ֵ�����ڻ�������Ϊfund_account�ģ���������stock_account��
	buy_balance	N16.2	����������
	sale_balance	N16.2	�����������
	stock_type	C1	֤ȯ���
ҵ��˵��

����˵��	�����	������Ϣ	����˵��	���󼶱�
	-52	�޴˹�Ʊ	���˴���ɲ����жϣ�
	-60	û�й�Ʊ��¼
	-61	��ѯ��Ʊʧ��	����������


*/

int TTrdItf_HSStk::QryStocks()
{
    if( FDisconnected == true )
        return   ERR_REMOTE_OTHER_FAILED;

	TList * Ans=new TList();
	int ret=0;
	String posstr=L"";
	TStockInfo *si;

BB:
	FItf->SetHead(FHSFFSet.branch_no, 403);
	FItf->SetRange(12, 1);
	FItf->AddField(WideString(L"version").c_bstr());
	FItf->AddField(WideString(L"l_op_code").c_bstr());
	FItf->AddField(WideString(L"vc_op_password").c_bstr());
	FItf->AddField(WideString(L"op_entrust_way").c_bstr());
	FItf->AddField(WideString(L"op_station").c_bstr());
	FItf->AddField(WideString(L"fund_account").c_bstr());
	FItf->AddField(WideString(L"password").c_bstr());
	FItf->AddField(WideString(L"exchange_type").c_bstr());
    FItf->AddField(WideString(L"stock_code").c_bstr());
	FItf->AddField(WideString(L"query_mode").c_bstr());
	FItf->AddField(WideString(L"request_num").c_bstr());
	FItf->AddField(WideString(L"position_str").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.l_op_code).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.vc_op_password).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString(this->ConvertMarketType(FRequest.QryStocks.Market)).c_bstr());
    FItf->AddValue(WideString(L" ").c_bstr());
	FItf->AddValue(WideString(L"0").c_bstr());
	FItf->AddValue(WideString(L"100").c_bstr());
	FItf->AddValue(WideString(posstr).c_bstr());

	int r  = SendAndReceive();
	if ( FItf->RecordCount < 1 || r < 0 ) goto HH;

	while(FItf->EOF_==0)
	{
		si=new TStockInfo;
		ZeroMemory(si,sizeof(TStockInfo));
		Ans->Add(si);
		posstr=String(FItf->FieldByName(WideString(L"position_str").c_bstr()));
		si->Market = this->ConvertMarketType(
			AnsiString(FItf->FieldByName(WideString(L"exchange_type").c_bstr())).c_str());
		lstrcpyn(si->SecuID,
			AnsiString(FItf->FieldByName(WideString(L"stock_code").c_bstr())).c_str(),CODE_LEN);
		lstrcpyn(si->Account,
			AnsiString(FItf->FieldByName(WideString(L"stock_account").c_bstr())).c_str(),ACC_LEN);
		si->Balance = StrToFloatDef(FItf->FieldByName(WideString(L"current_amount").c_bstr()),0);
		si->Available =  StrToFloatDef(FItf->FieldByName(WideString(L"enable_amount").c_bstr()),0);
		si->PosNum  = StrToFloatDef(FItf->FieldByName(WideString(L"current_amount").c_bstr()),0);
		si->CostPrice = si->CurPrice=StrToFloatDef(FItf->FieldByName(WideString(L"cost_price").c_bstr()),0);
		si->CurPrice =  si->CurPrice=StrToFloatDef(FItf->FieldByName(WideString(L"last_price").c_bstr()),0);
		si->PosDir = pdNet;
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
���ܺ�	302	�汾��	3.6	��������	20051215
��������	ί��ȷ��			���������	N
ҵ��Χ	����			����״̬	����
��������	ί��ȷ��
�������	������	����	˵��	����	ȱʡֵ
	version	N3	�汾��
��Ա	l_op_code	N8	��Ա��
��Ա	vc_op_password	C8	��Ա����
	op_entrust_way	C1	ί�з�ʽ
	op_station	C12	mac��ַ/ip
�ʺ�	fund_account	N9	�ʽ��˺�
�ʺ�	password	C10	��������
	exchange_type	C4	������𣬱�������ȷ�����г�����֧�֡�0����ո�
	stock_account	C12	֤ȯ�ʺţ��������'' ,ϵͳȡ�˺�Ĭ�Ϲɶ���û��Ĭ�Ϲɶ�������Ҫ��֤ȯ�ʺ�
	stock_code	C6	֤ȯ���룬��������ȷ���Ĺ�Ʊ���룬��֧�����롣
	entrust_amount	N16.2	ί������
	entrust_price	N9.3	ί�м۸�
	entrust_prop	C1	ί�����ԣ�Ĭ����'0'-�������Կ���ʽ�����깺��غ�Ȩ֤��Ȩ��ҵ����Ҫ�����ض���ί�����ԣ��Ժ���ͨ�������֡�
	entrust_bs	C1	�������� 1 ���� 2 ����
�������	������	����	˵��	����	ȱʡֵ
	error_no	N4	�����
	error_info	C255	����ԭ��
	entrust_no	N8	ί�б��
ҵ��˵��
	ע�⣺
����˵��	�����	������Ϣ	����˵��	���󼶱�
	-51	δ�ǼǸý������ʺ�
	-52	�˹�Ʊ������
	-55	���������Ͻ������涨
	-56	ί�м۸񲻷��Ͻ������涨
	-57	���ý���
	-58	��Ʊ����
	-59	����ʱ�䲻��ί��
	-64	�˹ɲ��ܽ��д���ί��
	-65	�˹�Ʊͣ�ƣ�����ί��	�����ͣ������ί�У���������
	-66	�ʻ�״̬������
	-67	��δ��ָ������
	-61	ί��ʧ��	����������

*/

int TTrdItf_HSStk::Order()
{
    if( FDisconnected == true )
        return   ERR_REMOTE_OTHER_FAILED;

    try
    {
	FItf->SetHead( FHSFFSet.branch_no, 302 );
	FItf->SetRange( 14, 1 );

	FItf->AddField(WideString(L"version").c_bstr());
	FItf->AddField(WideString(L"l_op_code").c_bstr());
	FItf->AddField(WideString(L"vc_op_password").c_bstr());
	FItf->AddField(WideString(L"op_entrust_way").c_bstr());
	FItf->AddField(WideString(L"op_station").c_bstr());
	FItf->AddField(WideString(L"fund_account").c_bstr());
	FItf->AddField(WideString(L"password").c_bstr());
	FItf->AddField(WideString(L"exchange_type").c_bstr());
	FItf->AddField(WideString(L"stock_account").c_bstr());
	FItf->AddField(WideString(L"stock_code").c_bstr());
	FItf->AddField(WideString(L"entrust_amount").c_bstr());
	FItf->AddField(WideString(L"entrust_price").c_bstr());
	FItf->AddField(WideString(L"entrust_prop").c_bstr());
	FItf->AddField(WideString(L"entrust_bs").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.l_op_code).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.vc_op_password).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString(this->ConvertMarketType(FRequest.Order.Market)).c_bstr());
	FItf->AddValue( WideString(L" ").c_bstr());
	FItf->AddValue( WideString( FRequest.Order.SecuID ).c_bstr());
	FItf->AddValue( WideString( IntToStr( FRequest.Order.Num )).c_bstr());

	String sPrice;
	if( AnsiPos(AnsiString("510"),FRequest.Order.SecuID ) == 1 ||
		AnsiPos(AnsiString("1599"),FRequest.Order.SecuID ) == 1 )
	{
		sPrice  = ConvetDoubleToPrice( FRequest.Order.Price,3);
	}
	else
	{
		sPrice  = ConvetDoubleToPrice( FRequest.Order.Price,2);
	}
	FItf->AddValue( WideString( sPrice ).c_bstr() );
	FItf->AddValue( WideString( ConvertOrderType(FRequest.Order.Type)[1] ).c_bstr());
	FItf->AddValue( WideString( this->ConvertOrderType( FRequest.Order.Type)[0] ).c_bstr());

	int	r	= SendAndReceive();


	if ( r < 0 )
	{
		return r;
	}
	else
	{
		String	id;
		if ( FItf->RecordCount > 0 )
		{
			id = String( FItf->FieldByName( WideString( L"entrust_no" ).c_bstr() ) );
			if ( id.Length() > 0 )
			{
				NewAns( 1 );
				lstrcpyn( ( *FAnswer )[0].Order.ContractID, AnsiString(id).c_str(), SEQ_LEN);
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
���ܺ�	304	�汾��	3.6	��������	20051215
��������	ί�г���			���������	N
ҵ��Χ	����			����״̬	����
��������	ί�г���
�������	������	����	˵��	����	ȱʡֵ
	version	N3	�汾��
��Ա	l_op_code	N8	��Ա��
��Ա	vc_op_password	C8	��Ա����
	op_entrust_way	C1	ί�з�ʽ
	op_station	C12	mac��ַ/ip
�ʺ�	fund_account	N9	�ʽ��˺�
�ʺ�	password	C10	��������
	batch_flag	C1	������־ '0'--���� '1'--����
	entrust_no	N8	ί�б��,ʹ������������־batch_flagΪ��1���������Ϊ���ţ�����Ϊί�б�ţ����Ϊ0�������������־Ϊ��1������ô���������˺������г��ġ�
�������	������	����	˵��	����	ȱʡֵ
	error_no	N4	�����
	error_info	C255	����ԭ��
	entrust_no	N8	ί�б��
ҵ��˵��

����˵��	�����	������Ϣ	����˵��	���󼶱�
	-53	�޴�ί��	��������ί�в��Ǹù���ģ�
	-54	��ί�в��ܳ���

*/
int TTrdItf_HSStk::Undo()
{
    if( FDisconnected == true )
        return   ERR_REMOTE_OTHER_FAILED;

    if( FRequest.Undo.ContractID[0] == '\0' ||
        FRequest.Undo.ContractID[0] == '-' )
    {
        return -1;
    }

    try
    {
	FItf->SetHead( FHSFFSet.branch_no, 304 );
	FItf->SetRange( 9, 1 );

	FItf->AddField(WideString(L"version").c_bstr());
	FItf->AddField(WideString(L"l_op_code").c_bstr());
	FItf->AddField(WideString(L"vc_op_password").c_bstr());
	FItf->AddField(WideString(L"op_entrust_way").c_bstr());
	FItf->AddField(WideString(L"op_station").c_bstr());
	FItf->AddField(WideString(L"fund_account").c_bstr());
	FItf->AddField(WideString(L"password").c_bstr());
	FItf->AddField(WideString(L"batch_flag" ).c_bstr() );
	FItf->AddField(WideString(L"entrust_no" ).c_bstr() );


	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.l_op_code).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.vc_op_password).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString(L"0" ).c_bstr() );
	FItf->AddValue(WideString(FRequest.Undo.ContractID ).c_bstr() );

	int	r	= SendAndReceive();

	if ( r != 0 )
	{
		if( r == -54 )
		{
			return ERR_UNDO_CANNOT_CANCLE;
		}

		return r;
	}
	else
	{
		if ( FItf->RecordCount > 0 )
		{
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

TTrdItf_HSStk::TTrdItf_HSStk( const char *psetupfile,ADDLOG plogfunc )
:TTrdItfBase(psetupfile,plogfunc)
{
	FHSFFSet.SvrIp          = "127.0.0.1";
	FHSFFSet.SvrPort        = 8008;
	FHSFFSet.Protocol       = 1;
	FHSFFSet.TimeOut        = 10;
	FHSFFSet.KeyCipher      = 0;
	FHSFFSet.KeyDeKey       = "";
	FHSFFSet.debug_mode     = false;
	FHSFFSet.l_op_code      = "";
	FHSFFSet.vc_op_password = "";
	FHSFFSet.op_station     = "";
	FHSFFSet.op_entrust_way = "4";
	FHSFFSet.branch_no      = 0;

	FAccount = "";

	FItf = NULL;
}

TTrdItf_HSStk::~TTrdItf_HSStk()
{
	CloseLink();
}

void TTrdItf_HSStk::CloseLink( void )
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

market_type  TTrdItf_HSStk::ConvertMarketType(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return mtNo;
	switch(t[0])
	{
	case '0':  return mtNo;
	case '1':  return mtSHA;
	case '2':  return mtSZA;
	default:
		return mtNo;
	}
}

order_type   TTrdItf_HSStk::ConvertOrderType(const char *t)
{
/*
	if(t==NULL || strlen(t)<2 ) return otNo;

	if( t[1] == '0' )
	{
		if( t[0] == '1' ) return otBuy;
		else if( t[0] == '2' ) return otSell;
	}
	else if( t[1] == 'N' )
	{
		if( t[0] == '1' ) return otETFSub;
		else if( t[0] == '2' ) return otETFRed;
    }
*/
    if( t== NULL ) return otNo;
    if( lstrcmp(t,"��Ʊ����" )==0)
        return  otBuy;
    else if( lstrcmp(t,"��Ʊ����" )==0)
        return  otSell;
    else if( lstrcmp(t,"ETF�깺" )==0)
        return otETFSub;
    else if( lstrcmp(t,"ETF���" )==0)
        return otETFRed;
    else
	    return otNo;
}

order_state  TTrdItf_HSStk::ConvertOrderState(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return osno;
	switch (t[0])
	{
	case  eswb:   return oswb;        //δ��
	case  esdb:   return oswb;        //����
	case  esyb:   return osyb;        //�ѱ�
	case  esybdc: return osdc;        //�ѱ�����
	case  esbcdc: return osdc;        //���ɴ���
	case  esbc:   return osbw;        //����
	case  esyc:   return osyc;        //�ѳ�
	case  esbcn:  return osbc;        //����
	case  esycn:  return oscj;        //�ѳ�
	case  esfd:   return osyf;        //�ϵ�
	case  escf:   return osyf;        //����
	case  esdmq:  return osno;        //����ȷ
	default:
		return osno;
	}
}

pos_direction TTrdItf_HSStk::ConvertPosDir(const char *t)
{
	return pdNet;
}

money_type   TTrdItf_HSStk::ConvertMoneyType(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return motNo;

	switch( t[0] )
	{
	case '0': return motRMB;
	case '1': return motUSD;
	case '2': return motHKD;
	default: return motNo;
	}
}

char *  TTrdItf_HSStk::ConvertMarketType(market_type t)
{
	switch(t)
	{
	case mtSHA: return "1";
	case mtSZA: return "2";
	default:
		return " ";
	}
}

char *  TTrdItf_HSStk::ConvertOrderType(order_type t)
{
	switch( t )
	{
	case otBuy   :  return "10";
	case otSell  :  return "20";
	case otETFSub  :  return "1N";
	case otETFRed :  return "2N";
	default:
		return "00";
	}
}

char *  TTrdItf_HSStk::ConvertOrderState(order_state t)
{
	return "";
}

char *  TTrdItf_HSStk::ConvertPosDir(pos_direction t)
{
	return "";
}

char *  TTrdItf_HSStk::ConvertMoneyType(money_type t)
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

bool TTrdItf_HSStk::GetConfig(void)
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
		FHSFFSet.branch_no        = ini->ReadInteger(PLUGINNAME,"branch_no",FHSFFSet.branch_no);
		FHSFFSet.op_entrust_way   = ini->ReadString (PLUGINNAME,"op_entrust_way",FHSFFSet.op_entrust_way);
		FHSFFSet.op_station       = ini->ReadString (PLUGINNAME,"op_station",FHSFFSet.op_station);
		FHSFFSet.l_op_code        = ini->ReadString (PLUGINNAME,"l_op_code",FHSFFSet.l_op_code);
		FHSFFSet.vc_op_password   = ini->ReadString (PLUGINNAME,"vc_op_password",FHSFFSet.vc_op_password);
		if (FHSFFSet.op_station.Length() < 7) {
			FHSFFSet.op_station.printf(L"192.168.1.%d",rand()%200+1);
		}

		ODS("Svrver:%s:%d\r\nop_station:%s\r\ndebug_mode:%d\r\nbranch_no:%d\r\nop_entrust_way:%s\r\n",
			AnsiString(FHSFFSet.SvrIp).c_str(),FHSFFSet.SvrPort,
			AnsiString(FHSFFSet.op_station).c_str(),
			FHSFFSet.debug_mode,
			FHSFFSet.branch_no,
			AnsiString(FHSFFSet.op_entrust_way));
	}
	__finally
	{
		delete ini;
	}
	return true;
}

void TTrdItf_HSStk::SetConfig(void)
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
		ini->WriteString (PLUGINNAME,"op_entrust_way",   FHSFFSet.op_entrust_way);
		ini->WriteInteger(PLUGINNAME,"branch_no",        FHSFFSet.branch_no);
		ini->WriteString (PLUGINNAME,"op_station",       FHSFFSet.op_station);
		ini->WriteString(PLUGINNAME,"l_op_code",         FHSFFSet.l_op_code ) ;
		ini->WriteString(PLUGINNAME,"vc_op_password",    FHSFFSet.vc_op_password);
		ini->UpdateFile();
	}
	__finally
	{
		delete ini;
	}
}

int TTrdItf_HSStk::KeepAlive(void)
{
    this->lock();
    try
    {
        if( FItf!=NULL )
        {
            FItf->SetHead( FHSFFSet.branch_no, 105 );
            FItf->SetRange( 4, 1 );

            FItf->AddField(WideString(L"version").c_bstr());
            FItf->AddField(WideString(L"op_entrust_way").c_bstr());
            FItf->AddField(WideString(L"op_station").c_bstr());
            FItf->AddField(WideString(L"stock_code").c_bstr());

            FItf->AddValue(WideString(HS_VERSION).c_bstr());
            FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
            FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
            FItf->AddValue(WideString(L"600000").c_bstr());

            int	r	= SendAndReceive();
            FItf->FreePack();

            if ( r < 0 )
            {
                FDisconnected = true;
                ODS("->KeepAlive Error");
            }
            else
                ODS("->KeepAlive OK");

        }
    }
    __finally
    {
        this->unlock();
    }
	return 0;
}
