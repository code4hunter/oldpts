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
			/*this->SetLastError(ERR_REMOTE_SEND_FAILED,'E',PLUGINNAME,"发送数据错误，试图恢复连接...,connection=%d",FItf->Connection);

            WideString buf(FItf->Buffer);

            this->CloseLink();
            this->Init();
            this->login();

            FItf->set_Buffer(buf.c_bstr());
            if ( FItf->Send()!=0 )   */
            {
                this->SetLastError(ERR_REMOTE_SEND_FAILED,'E',PLUGINNAME,"发送数据错误，恢复连接失败.,connection=%d",FItf->Connection);
			    return ERR_REMOTE_SEND_FAILED;
            }
		}

		FItf->FreePack();

		if ( FItf->Receive()!=0 )
		{
            /*
			this->SetLastError(ERR_REMOTE_RECV_FAILED,'E',PLUGINNAME,"接收数据错误,试图恢复连接...,connection=%d",FItf->Connection);
            WideString buf(FItf->Buffer);
            this->CloseLink();
            this->Init();
            this->login();
            FItf->set_Buffer(buf.c_bstr());
            if ( FItf->Send()!=0 )
            {
                this->SetLastError(ERR_REMOTE_SEND_FAILED,'E',PLUGINNAME,"发送数据错误，恢复连接失败。,connection=%d",FItf->Connection);
			    return ERR_REMOTE_SEND_FAILED;
            }
            if ( FItf->Receive()!=0 )*/
            {
                this->SetLastError(ERR_REMOTE_RECV_FAILED,'E',PLUGINNAME,"接收数据错误,恢复连接失败.,connection=%d",FItf->Connection);
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
			ODS('E',PLUGINNAME, "柜台提示:%s,ErrNo:%d",FLastError.Text,FLastError.ErrorCode );
			return FLastError.ErrorCode;
		}
	}
	catch( Exception &e )
	{
		lstrcpyn( FLastError.Sender ,"HSSTK", SEQ_LEN);
		FLastError.ErrorCode = ERR_REMOTE_OTHER_FAILED;
		lstrcpyn( FLastError.Text,AnsiString(e.Message).c_str(),MAX_TEXT );

		ODS('E',PLUGINNAME, "意外错误:%s",AnsiString(e.Message).c_str() );
		return ERR_REMOTE_OTHER_FAILED;
	}
	catch(...)
	{
		lstrcpyn( FLastError.Sender ,"HSSTK", SEQ_LEN);
		FLastError.ErrorCode = ERR_REMOTE_OTHER_FAILED;
		lstrcpyn( FLastError.Text,"未知错误",MAX_TEXT );

		ODS('E',PLUGINNAME, "意外错误:%s",FLastError.Text );
		return ERR_REMOTE_OTHER_FAILED;
	}
	return 0;
}


/*
功能号	200	版本号	3.6	更新日期	20051215
功能名称	客户登入密码校验			结果集返回	N
业务范围	公用			功能状态	公开
功能描述	客户登入密码校验
输入参数	参数名	类型	说明	长度	缺省值
	version	N3	版本号
柜员	l_op_code	N8	柜员号
柜员	vc_op_password	C8	柜员密码
	op_entrust_way	C1	委托方式
	op_station	C12	mac地址/ip
帐号	account_content	N9	资金帐号 同fund_account 含义
帐号	password	C10	交易密码
输出参数	参数名	类型	说明	长度	缺省值
	error_no	N4	错误号
	error_info	C255	错误原因
	branch_no	N5	分支代码
	fund_account	N9	资金账号
	client_name	C14	帐号名称
	money_count	C1
	money_type	C1	币种类别
	exchange_type	C4	交易类别，目前返回为空
	stock_account	C11	资金帐号，目前返回为空。
	client_rights	C64	资金帐号有权限的证券类别，表明在资产管理系统中，可以做的证券类别
业务说明	客户登入密码校验

出错说明	错误号	错误信息	错误说明	错误级别
	-41	资金密码到期未修改 （需提示，仍可登录）
	-42	“交易密码到期未修改”        （需提示，仍可登录）
	-51	无此帐户
	-63	密码错误
	-66	您的帐户状态不正常	（其他错误）
	-64	您没有此类委托的权限
	-61	帐户登录失败 （其他错误）

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
功能号	405	版本号	3.6	更新日期	20080708
功能名称	查询资金			结果集返回	Y
业务范围	交易			功能状态	公开
功能描述	查询资金
输入参数	参数名	类型	说明	长度	缺省值
	version	N3	版本号
柜员	l_op_code	N8	柜员号
柜员	vc_op_password	C8	柜员密码
	op_entrust_way	C1	委托方式
	op_station	C12	mac地址/ip
帐号	fund_account	N9	资金账号
帐号	password	C10	交易密码
输出参数	参数名	类型	说明	长度	缺省值
	money_type	C1	币种类别
	current_balance	N16.2	当前余额
	enable_balance	N16.2	可用金额
	fetch_balance	N16.2	可取金额
	interest	N16.2	待入账利息
	asset_balance	N16.2	资产总值
	pre_interest	N16.2	预计利息
业务说明

出错说明	错误号	错误信息	错误说明	错误级别
	-61	查询资金失败	（其他错误）
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
功能号	401	版本号	3.6	更新日期	20051215
功能名称	查询委托			结果集返回	Y
业务范围	交易			功能状态	公开
功能描述	查询委托
输入参数	参数名	类型	说明	长度	缺省值
	version	N3	版本号
柜员	l_op_code	N8	柜员号
柜员	vc_op_password	C8	柜员密码
	op_entrust_way	C1	委托方式
	op_station	C12	mac地址/ip
帐号	fund_account	N9	资金账号
帐号	password	C10	交易密码
	exchange_type	C4	交易类别，如果不为空格，查确定的，为空，查所有。
	stock_code	C6	证券代码，如果为空格，查所有，不为空，查确定的，此时exchange_type必须不为空
	locate_entrust_no	N8	指定委托号，查指定委托号的委托，且request_num为1，且前台在收到应答后要检查返回的委托的委托号是否与要求查询的一致，此时exchange_type和stock_code要为空串。
	query_direction	C1	查询方向
	sort_direction	C1	排序方式 '0' 正常 '1'倒序
	request_num	N8	请求行数，不送按50行处理，超过系统指定值（1000行）按系统指定值（1000行）处理
	position_str	C32	定位串
输出参数	参数名	类型	说明	长度	缺省值
	position_str	C32	定位串
	entrust_no	N8	委托序号
	batch_no	N8	委托批号
	exchange_type	C4	交易类别
	stock_account	C11	证券账号
	stock_code	C6	证券代码
	stock_name	C8	证券名称
	entrust_bs	C1	买卖方向
	bs_name	C60	买卖方向名称
	entrust_price	N9.3	委托价格
	entrust_amount	N16.2	委托数量
	business_amount	N16.2	成交数量
	business_price	N9.3	成交价格
	report_no	N8	申报号
	report_time	N8	申报时间
	entrust_type	C1	委托类别
	type_name	C64	委托类别名称
	entrust_status	C1	委托状态
	status_name	C60	状态名称
	cancel_info	C255	废单原因
	entrust_prop	C1	委托属性
	entrust_prop_name	C1	委托属性
业务说明

出错说明	错误号	错误信息	错误说明	错误级别
	-52	无此股票	（此错误可不作判断）
	-60	没有委托记录
	-61	查询委托失败	（其他错误）

*/

/*
##entrust_bs_name#hedge_type#hedge_type_name#futu_entrust_price#amount_per_hand#entrust_amount#business_amount#cancel_amount#hold_balance#entrust_time#report_time#entrust_status#status_name#futu_entrust_type#futu_entrust_type_name#confirm_no#frozen_fare#forceclose_reason#forceclose_reason_name#batch_no#error_message#
20070410000010000000092#20070410#92#100359#博弘#F4#金融交易#207130023052#IF0704#股指0704#0#1#开仓#1#买入#0#投机#3050.0000#300#1.0000#0#0#137350.0000#103339#103750#C#正报#0#委托# #100.0000#0##92# #


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

			//组建输出数据
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

功能号	402	版本号	3.6	更新日期	20051215
功能名称	查询成交			结果集返回	Y
业务范围	交易			功能状态	公开
功能描述	查询成交
输入参数	参数名	类型	说明	长度	缺省值
	version	N3	版本号
柜员	l_op_code	N8	柜员号
柜员	vc_op_password	C8	柜员密码
	op_entrust_way	C1	委托方式
	op_station	C12	mac地址/ip
帐号	fund_account	N9	资金账号
帐号	password	C10	交易密码
	exchange_type	C4	交易类别，不为空，查确定的，为空，查所有
	stock_code	C6	证券代码，为空，查所有，不为空，查确定的，此时exchange_type必须不为空
	query_mode	C1	查询模式 '0' 明细
	request_num	N8	请求行数，不送按50行处理，超过系统指定值（1000行）按系统指定值（1000行）处理
	serial_no	N8	委托号，为空查询全部
	batch_serial_no	N8	委托批号，不为0时为查该委托批号的成交信息
	position_str	C32	定位串
输出参数	参数名	类型	说明	长度	缺省值
	position_str	C32	定位串
	serial_no	N8	成交序号
	date	N8	日期
	exchange_type	C4	交易类别
	stock_account	C11	证券账号
	stock_code	C6	证券代码
	stock_name	C8	证券名称
	entrust_bs	C1	委托方向
	bs_name	C60	委托方向名称
	business_price	N9.3	成交价格
	business_amount	N16.2	成交数量
	business_time	N8	成交时间
	business_status	C1	成交状态 见数据字典
	status_name	C60	成交状态名称
	business_type	C1	成交类别，0：‘买卖’2：‘撤单’
	type_name	C64	成交类别名称
	business_times	N5	成交笔数
	entrust_no	N8	委托号
	report_no	N8	申报号
	business_balance	N16.2	成交金额
业务说明

出错说明	错误号	错误信息	错误说明	错误级别
	-52	无此股票	（此错误可不作判断）
	-60	没有成交记录
	-61	查询成交失败	（其他错误）


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

			//组建输出数据
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

			if( WideString(FItf->FieldByName( WideString( L"business_type" ).c_bstr() )) == L"2" ) //撤单
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

功能号	403	版本号	3.6	更新日期	20051215
功能名称	查询股票			结果集返回	Y
业务范围	交易			功能状态	公开
功能描述	查询股票
输入参数	参数名	类型	说明	长度	缺省值
	version	N3	版本号
柜员	l_op_code	N8	柜员号
柜员	vc_op_password	C8	柜员密码
	op_entrust_way	C1	委托方式
	op_station	C12	mac地址/ip
帐号	fund_account	N9	资金账号
帐号	password	C10	交易密码
	exchange_type	C4	交易类别，不为空，查确定的，为空，查所有。
	stock_code	C6	证券代码，为空，查所有，不为空，查确定的，此时exchange_type必须不为空。
	query_mode	C1	‘0’：证券余额明细显示；‘1’：证券代码汇总
	request_num	N8	请求行数，不送按50行处理，超过系统指定值（1000行）按系统指定值（1000行）处理
	position_str	C32	定位串，汇总查询时为exchange_type+stock_code，明细查询时为branch_no+exchange_type+stock_account+stock_code总长度为24个字节。
输出参数	参数名	类型	说明	长度	缺省值
	position_str	C32	定位串
	exchange_type	C4	交易类别
	stock_account	C11	证券账号
	stock_code	C6	证券代码
	stock_name	C8	证券名称
	current_amount	N16.2	当前数量
	enable_amount	N16.2	可卖股票
	last_price	N9.3	最新价
	cost_price	N9.3	成本价
	income_balance	N16.2	买卖盈亏(浮动盈亏)
	gain_income	N16.2	实现收益
	total_income	N16.2	总盈亏
	hand_flag	C1	股手标志，'0'--股   '1' -- 手。
	market_value	N16.2	证券市值，在明细下为每个股东帐号的市值，而在汇总下则为fund_account的，汇总下无stock_account。
	buy_balance	N16.2	当日买入金额
	sale_balance	N16.2	当日卖出金额
	stock_type	C1	证券类别
业务说明

出错说明	错误号	错误信息	错误说明	错误级别
	-52	无此股票	（此错误可不作判断）
	-60	没有股票记录
	-61	查询股票失败	（其他错误）


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

//////交易函数/////
/*
功能号	302	版本号	3.6	更新日期	20051215
功能名称	委托确认			结果集返回	N
业务范围	交易			功能状态	公开
功能描述	委托确认
输入参数	参数名	类型	说明	长度	缺省值
	version	N3	版本号
柜员	l_op_code	N8	柜员号
柜员	vc_op_password	C8	柜员密码
	op_entrust_way	C1	委托方式
	op_station	C12	mac地址/ip
帐号	fund_account	N9	资金账号
帐号	password	C10	交易密码
	exchange_type	C4	交易类别，必须输入确定的市场，不支持‘0‘或空格。
	stock_account	C12	证券帐号，如果输入'' ,系统取账号默认股东，没有默认股东，必须要送证券帐号
	stock_code	C6	证券代码，必须输入确定的股票代码，不支持内码。
	entrust_amount	N16.2	委托数量
	entrust_price	N9.3	委托价格
	entrust_prop	C1	委托属性，默认送'0'-买卖，对开放式基金申购赎回和权证行权等业务，需要传入特定的委托属性，以和普通买卖区分。
	entrust_bs	C1	买卖方向 1 买入 2 卖出
输出参数	参数名	类型	说明	长度	缺省值
	error_no	N4	错误号
	error_info	C255	错误原因
	entrust_no	N8	委托编号
业务说明
	注意：
出错说明	错误号	错误信息	错误说明	错误级别
	-51	未登记该交易所帐号
	-52	此股票不存在
	-55	数量不符合交易所规定
	-56	委托价格不符合交易所规定
	-57	可用金额不足
	-58	股票余额不足
	-59	闭市时间不能委托
	-64	此股不能进行此类委托
	-65	此股票停牌，不能委托	（如果停牌允许委托，不报错误）
	-66	帐户状态不正常
	-67	您未作指定交易
	-61	委托失败	（其他错误）

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
功能号	304	版本号	3.6	更新日期	20051215
功能名称	委托撤单			结果集返回	N
业务范围	交易			功能状态	公开
功能描述	委托撤单
输入参数	参数名	类型	说明	长度	缺省值
	version	N3	版本号
柜员	l_op_code	N8	柜员号
柜员	vc_op_password	C8	柜员密码
	op_entrust_way	C1	委托方式
	op_station	C12	mac地址/ip
帐号	fund_account	N9	资金账号
帐号	password	C10	交易密码
	batch_flag	C1	批量标志 '0'--单笔 '1'--批量
	entrust_no	N8	委托编号,使用批量撤单标志batch_flag为‘1‘，则将理解为批号，其它为委托编号，如果为0，则如果批量标志为‘1’，那么批量撤单账号整个市场的。
输出参数	参数名	类型	说明	长度	缺省值
	error_no	N4	错误号
	error_info	C255	错误原因
	entrust_no	N8	委托编号
业务说明

出错说明	错误号	错误信息	错误说明	错误级别
	-53	无此委托	（包含此委托不是该股民的）
	-54	此委托不能撤单

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
    if( lstrcmp(t,"股票买入" )==0)
        return  otBuy;
    else if( lstrcmp(t,"股票卖出" )==0)
        return  otSell;
    else if( lstrcmp(t,"ETF申购" )==0)
        return otETFSub;
    else if( lstrcmp(t,"ETF赎回" )==0)
        return otETFRed;
    else
	    return otNo;
}

order_state  TTrdItf_HSStk::ConvertOrderState(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return osno;
	switch (t[0])
	{
	case  eswb:   return oswb;        //未报
	case  esdb:   return oswb;        //待报
	case  esyb:   return osyb;        //已报
	case  esybdc: return osdc;        //已报待撤
	case  esbcdc: return osdc;        //部成待撤
	case  esbc:   return osbw;        //部撤
	case  esyc:   return osyc;        //已撤
	case  esbcn:  return osbc;        //部成
	case  esycn:  return oscj;        //已成
	case  esfd:   return osyf;        //废单
	case  escf:   return osyf;        //撤废
	case  esdmq:  return osno;        //待明确
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
		// 判断是否存在插件的设置，没有的话返回false以便系统能够生成默认的设置
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
