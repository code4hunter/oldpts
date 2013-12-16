//---------------------------------------------------------------------------
#include "uDatabase.h"
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
			this->SetLastError(ERR_REMOTE_SEND_FAILED,'E',PLUGINNAME,"发送数据错误,connection=%d",FItf->Connection);
			return ERR_REMOTE_SEND_FAILED;
		}

		//FItf->FreePack();

		if ( FItf->Receive()!=0 )
		{
			this->SetLastError(ERR_REMOTE_RECV_FAILED,'E',PLUGINNAME,"接收数据错误,connection=%d",FItf->Connection);
			return ERR_REMOTE_RECV_FAILED;
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
			ODS('M',PLUGINNAME,"BUF:%s",buf) ;
		}

		if ( FItf->ErrorNo!=0 )
		{
			lstrcpyn( FLastError.Sender ,"HSF", SEQ_LEN);
			FLastError.ErrorCode = -abs(FItf->ErrorNo);
			lstrcpyn( FLastError.Text,AnsiString( FItf->ErrorMsg ).c_str(),MAX_TEXT );
			ODS('E',PLUGINNAME, "柜台提示:%s,ErrNo:%d",FLastError.Text,FLastError.ErrorCode );
			return FLastError.ErrorCode;
		}
	}
	catch( Exception &e )
	{
		lstrcpyn( FLastError.Sender ,"HSF", SEQ_LEN);
		FLastError.ErrorCode = ERR_REMOTE_OTHER_FAILED;
		lstrcpyn( FLastError.Text,AnsiString(e.Message).c_str(),MAX_TEXT );

		ODS('E',PLUGINNAME, "意外错误:%s",AnsiString(e.Message).c_str() );
		return ERR_REMOTE_OTHER_FAILED;
	}
	catch(...)
	{
		lstrcpyn( FLastError.Sender ,"HSF", SEQ_LEN);
		FLastError.ErrorCode = ERR_REMOTE_OTHER_FAILED;
		lstrcpyn( FLastError.Text,"未知错误",MAX_TEXT );

		ODS('E',PLUGINNAME, "意外错误:%s",FLastError.Text );
		return ERR_REMOTE_OTHER_FAILED;
	}
	return 0;
}


/*
功能号	200
功能描述	客户登录校验
输入参数	参数名	类型	说明	长度	缺省值
version	N3	版本号
identity_type	C1	账户身份类别 1 调拨人 2 指令人 3 查询 默认不输入
op_branch_no	N5	操作分支营业部号，以追踪该请求来自哪个分支。周边可以通过配置获得本操作分支营业部号，周边必须输入
op_entrust_way	C1	委托方式
op_station	C12	该请求来自的站点以追踪请求的来源。一般在营业部内部该值置为工作站的MAC地址，而对于电话接入可考虑置为来电号码
branch_no 	N5	是股民所在营业部号，用于通炒，可由股民自己选择输入，当股民不选择分支号，则周边应将其置为op_branch_no以表示本营业部
function_id	N6	系统功能
input_content	C1	帐号类型，‘1’，‘2’，‘3’，4’，‘5’, ‘6’, ‘A’分别表示account_content代表资金帐号，股东内码，和资金卡号，银行帐号，股东帐号，客户编号，期货帐号
password	C10	交易密码
content_type	C6	帐号校验方式，当input_content为‘4’，‘5’时，则content_type明确银行号和股东的市场类别，其它输入为‘0’。
account_content	C30	输入内容
输出参数	参数名	类型	说明	长度	缺省值
error_no	N4	错误号
error_info	C20	错误原因
fund_account	N9	资金账号
出错说明	错误号	错误信息	错误说明	错误级别
-41	资金密码到期未修改	需提示，仍可登录
-42	交易密码到期未修改	需提示，仍可登录		
-51	无此帐户			
-61	帐户登录失败			
-63	密码错误			
-64	您没有此类委托的权限			
-66	您的帐户状态不正常			

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

		FItf->AddField(WideString(L"version").c_bstr());
		FItf->AddField(WideString(L"op_branch_no").c_bstr());
		FItf->AddField(WideString(L"op_entrust_way").c_bstr());
		FItf->AddField(WideString(L"op_station").c_bstr());
		FItf->AddField(WideString(L"function_id").c_bstr());
		FItf->AddField(WideString(L"branch_no").c_bstr());
		FItf->AddField(WideString(L"input_content").c_bstr());
		FItf->AddField(WideString(L"content_type").c_bstr());
		FItf->AddField(WideString(L"account_content").c_bstr());
		FItf->AddField(WideString(L"password").c_bstr());

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue(WideString(L"200").c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());

		switch( FRequest.SetAccount.LoginType )
		{
		case asCA:
			FItf->AddValue(WideString(L"1").c_bstr());
			break;
			//case asSHA,asSZA:
			//	FItf->AddValue(WideString(L"2").c_bstr());
		case asJJS,asFDL,asFZZ,asFSH:
			FItf->AddValue(WideString(L"A").c_bstr());
			break;
		default:
			FItf->AddValue(WideString(L"").c_bstr());
		}

		FItf->AddValue(WideString(L"0").c_bstr());
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
				AnsiString	acc	= FItf->FieldByName( WideString( L"fund_account" ).c_bstr());

				if ( acc.Length() > 0 )
				{
					lstrcpyn(FAccInfo.Capital,acc.c_str(),ACC_LEN);

					NewAns( 1 );
					memcpy( &( ( *FAnswer )[0].SetAccount.AccountInfo ), &FAccInfo, sizeof( TAccountInfo ) );
                    order_man.load_working_orders(this->FAccInfo.Capital);
					AnsiString tabconfirm_flag=AnsiString(FItf->FieldByName( WideString(L"tabconfirm_flag" ).c_bstr()));
					ODS('M',PLUGINNAME,"tabconfirm_flag:%s",tabconfirm_flag.c_str());
					if( tabconfirm_flag == "0")
						return 0;
					else
						goto COMFIRM;

				}
				else
				{
					return AnsiString( FItf->FieldByName( WideString(L"error_no" ).c_bstr() ) ).ToIntDef( ERR_OTHERS );
				}
			}
			else
			{
				return ERR_NO_ACK;
			}
		}

COMFIRM:
		//账单确认
		FItf->SetHead( FHSFFSet.branch_no, 1008 );
		FItf->SetRange( 10, 1 );

		FItf->AddField(WideString(L"version").c_bstr());
		FItf->AddField(WideString(L"op_branch_no").c_bstr());
		FItf->AddField(WideString(L"op_entrust_way").c_bstr());
		FItf->AddField(WideString(L"op_station").c_bstr());
		FItf->AddField(WideString(L"function_id").c_bstr());
		FItf->AddField(WideString(L"branch_no").c_bstr());
		FItf->AddField(WideString(L"fund_account").c_bstr());
		FItf->AddField(WideString(L"password").c_bstr());
		FItf->AddField(WideString(L"check_date").c_bstr());
		FItf->AddField(WideString(L"check_time").c_bstr());

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue(WideString(L"1008").c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());
		FItf->AddValue(WideString(FRequest.SetAccount.Account).c_bstr());
		FItf->AddValue(WideString(FRequest.SetAccount.PW).c_bstr());
		FItf->AddValue(WideString(Date().FormatString("yyyymmdd")).c_bstr());
		FItf->AddValue(WideString(Time().FormatString("hhnnss")).c_bstr());

		r	= SendAndReceive();

		if ( r < 0 )
		{
			ODS('M',PLUGINNAME,"确认账单失败");
			return r;
		}
		else
		{
			ODS('M',PLUGINNAME,"确认账单成功");
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
功能号
功能描述	期货客户资金查询
money_type	C1	币种类别
输出参数	参数名	类型	说明	长度	缺省值
money_type	C1	币种类别
current_balance	N16.2	资金余额		
enable_balance	N16.2	可用资金		
fetch_balance	N16.2	可用资金
出错说明	错误号	错误信息	错误说明	错误级别	
-51	无此帐户			
-61	期货客户资金查询失败	（其他错误）	

*/
int TTrdItf_HSFF::QryMoney()
{
	try
	{
		FItf->SetHead( FHSFFSet.branch_no, 1508 );
		FItf->SetRange( 9, 1 );

		FItf->AddField( WideString(L"version" ).c_bstr() );
		FItf->AddField( WideString(L"op_branch_no" ).c_bstr() );
		FItf->AddField( WideString(L"op_entrust_way" ).c_bstr() );
		FItf->AddField( WideString(L"op_station" ).c_bstr() );
		FItf->AddField( WideString(L"branch_no" ).c_bstr() );
		FItf->AddField( WideString(L"fund_account" ).c_bstr() );
		FItf->AddField( WideString(L"password" ).c_bstr() );
		FItf->AddField( WideString(L"function_id" ).c_bstr() );
		FItf->AddField( WideString(L"money_type" ).c_bstr() );

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());
		FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
		FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
		FItf->AddValue(WideString(L"1508" ).c_bstr() );
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
					( *FAnswer )[0].QryMoney.MoneyInfo.balance = StrToFloatDef( AnsiString( FItf->FieldByName( WideString(L"rights_balance_float" ).c_bstr() ) ), 0 );
					//( *FAnswer )[0].QryMoney.MoneyInfo.balance = StrToFloatDef( AnsiString( FItf->FieldByName( WideString(L"current_balance" ).c_bstr() ) ), 0 );
					( *FAnswer )[0].QryMoney.MoneyInfo.available = StrToFloatDef( AnsiString( FItf->FieldByName( WideString(L"enable_balance" ).c_bstr() ) ), 0 );
					( *FAnswer )[0].QryMoney.MoneyInfo.MoneyType = ConvertMoneyType( AnsiString( FItf->FieldByName( WideString(L"money_type" ).c_bstr() ) ).c_str() );

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
功能号	1504
功能描述	期货当日委托查询
输入参数	参数名	类型	说明	长度	缺省值
futu_exch_type	C4	交易类别		
futures_account	C12	期货账号		
contract_code	C30	合约代码
en_entrust_status	C10	允许委托状态		
query_direction	C1	查询方向，0：顺查；1：倒查		
batch_no	N8	委托批号		
futu_entrust_type	C1	委托类型		
request_num	N8	查询条数
position_str	C32	定位串		
输出参数	参数名	类型	说明	长度	缺省值
position_str	C32	定位串
entrust_no	N8	委托编号
futu_exch_type	C4	交易类别
futu_entrust_price	N12.6	期货委托价格
entrust_bs	C1	委托买卖方向
entrust_status	C1	委托状态
report_time	N8	申报时间
business_amount	N16.2	成交数量
entrust_amount	N16.2	委托数量
cancel_amount	N16.2	撤单数量

出错说明	错误号	错误信息	错误说明	错误级别	
-51	无此帐户			
-61	期货当日委托查询失败	（其他错误）
*/

/*
##entrust_bs_name#hedge_type#hedge_type_name#futu_entrust_price#amount_per_hand#entrust_amount#business_amount#cancel_amount#hold_balance#entrust_time#report_time#entrust_status#status_name#futu_entrust_type#futu_entrust_type_name#confirm_no#frozen_fare#forceclose_reason#forceclose_reason_name#batch_no#error_message#
20070410000010000000092#20070410#92#100359#博弘#F4#金融交易#207130023052#IF0704#股指0704#0#1#开仓#1#买入#0#投机#3050.0000#300#1.0000#0#0#137350.0000#103339#103750#C#正报#0#委托# #100.0000#0##92# #


*/
int TTrdItf_HSFF::QryCurCsn()
{
	TList* ResultList = new TList();

	int r = 0;
	AnsiString position_str = FRequest.QryCurCsn.SeqNum;

	do
	{
		FItf->SetHead( FHSFFSet.branch_no, 1504 );
		FItf->SetRange( 17, 1 );

		FItf->AddField(WideString(L"version").c_bstr());
		FItf->AddField(WideString(L"op_branch_no").c_bstr());
		FItf->AddField(WideString(L"op_entrust_way").c_bstr());
		FItf->AddField(WideString(L"op_station").c_bstr());
		FItf->AddField(WideString(L"function_id").c_bstr());
		FItf->AddField(WideString(L"branch_no").c_bstr());

		FItf->AddField(WideString(L"fund_account").c_bstr());
		FItf->AddField(WideString(L"password").c_bstr());
		FItf->AddField(WideString(L"futu_exch_type").c_bstr());
		FItf->AddField(WideString(L"futures_account").c_bstr());

		FItf->AddField(WideString(L"contract_code").c_bstr());
		FItf->AddField(WideString(L"en_entrust_status").c_bstr());         //en_entrust_status有疑问
		FItf->AddField(WideString(L"query_direction").c_bstr());
		FItf->AddField(WideString(L"batch_no").c_bstr());
		FItf->AddField(WideString(L"futu_entrust_type").c_bstr());
		FItf->AddField(WideString(L"request_num").c_bstr());
		FItf->AddField(WideString(L"position_str").c_bstr());


		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue( WideString(L"1504" ).c_bstr() );
		FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());

		FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
		FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
		FItf->AddValue( WideString(L""/*FHSFFSet.futu_exch_type*/ ).c_bstr() );
		FItf->AddValue( WideString(L""/*this->FAccInfo.FJJS*/ ).c_bstr());  //期货帐户
		FItf->AddValue( WideString(L"" ).c_bstr() );
		FItf->AddValue( WideString(L"" ).c_bstr() );
		FItf->AddValue( WideString( ( char ) qdahead ).c_bstr() );
		FItf->AddValue( WideString( FRequest.QryCurCsn.OrderID).c_bstr() );
		FItf->AddValue( WideString( FHSFFSet.futu_entrust_type ).c_bstr() );
		FItf->AddValue( WideString( IntToStr((int)FRequest.QryCurCsn.MaxRecord) ).c_bstr() );
		FItf->AddValue( WideString( position_str ).c_bstr() );

		r = SendAndReceive();

		if ( FItf->RecordCount < 1 || r < 0 ) break;

		for ( int i = 0; i < FItf->RecordCount; ++i)
		{
			TOrderInfo*	ci	= new TOrderInfo;
			ZeroMemory( ci, sizeof( TOrderInfo ) );
			ResultList->Add(ci);

			//组建输出数据
			lstrcpyn( ci->ContractID, AnsiString( FItf->FieldByName( WideString(L"entrust_no" ).c_bstr() ) ).c_str() ,SEQ_LEN);
			lstrcpyn( ci->SecuID, AnsiString( FItf->FieldByName( WideString(L"contract_code" ).c_bstr() ) ).c_str() ,CODE_LEN);
			lstrcpyn( ci->Account, AnsiString( FItf->FieldByName( WideString(L"futures_account" ).c_bstr() ) ).c_str() ,ACC_LEN);
			ci->Market = this->ConvertMarketType(
				AnsiString( FItf->FieldByName( WideString(L"futu_exch_type" ).c_bstr() ) ).c_str());
			ci->Time = this->ConvertTimeToInt(
				AnsiString( FItf->FieldByName( WideString(L"entrust_time" ).c_bstr() ) ).c_str() );
			ci->Date = this->ConvertDateToInt(
				AnsiString( FItf->FieldByName( WideString(L"init_date" ).c_bstr() ) ).c_str() );
			ci->Type = this->ConvertOrderType(
				(AnsiString( FItf->FieldByName( WideString(L"entrust_bs" ).c_bstr() ) ) +
				AnsiString( FItf->FieldByName( WideString(L"futures_direction" ).c_bstr() ) )).c_str()  );
			ci->State = this->ConvertOrderState(
				AnsiString( FItf->FieldByName( WideString(L"entrust_status" ).c_bstr() ) ).c_str());
			ci->CsnVol = StrToFloatDef(FItf->FieldByName( WideString(L"entrust_amount" ).c_bstr() ), 0 );
			ci->TrdVol = StrToFloatDef( FItf->FieldByName( WideString(L"business_amount" ).c_bstr() ), 0 );
			ci->CsnPrice = StrToFloatDef( FItf->FieldByName( WideString(L"futu_entrust_price" ).c_bstr() ), 0 );
			ci->CancelVol = - StrToFloatDef( FItf->FieldByName( WideString(L"cancel_amount" ).c_bstr() ), 0 );
			ci->TrdPrice = 0;
			lstrcpyn(ci->SeqNum,
				AnsiString( FItf->FieldByName( WideString(L"position_str" ).c_bstr())).c_str(),SEQ_LEN);
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

功能号	1506	版本号	3.2	更新日期	20060816
功能名称	期货当日成交查询			结果集返回	Y
输入参数	参数名	类型	说明	长度	缺省值
version	N3	版本号
op_branch_no	N5	操作员分支代码
op_entrust_way	C1	委托方式
identity_type	C1	账户身份类别 1 调拨人 2 指令人 3 查询 默认不输入
op_station	C12	站点/电话
function_id	N6	系统功能
branch_no	N5	分支代码
fund_account	N9	资金账号
password	C10	交易密码
futu_exch_type	C4	交易类别
futures_account	C12	期货账号
contract_code	C30	合约代码
query_mode	C1	查询模式
0 明细
1 按[委托编号+交易类别+期货交易帐号+合约代码+开平仓方向+买卖方向+业务标志]汇总
2 按[委托编号+交易类别+期货交易帐号+合约代码+开平仓方向+买卖方向+业务标志+成交价格]汇总
3 按[交易类别+期货交易帐号+合约代码+开平仓方向+买卖方向+业务标志]汇总
query_direction	C1	查询方向，0：顺查；1：倒查
request_num	N8	查询条数
futu_position_str	C100	定位串
输出参数	参数名	类型	说明	长度	缺省值
futu_position_str	C100	定位串		
init_date	N8	发生日期
serial_no	N8	流水编号		
entrust_no	N8	委托编号		
futu_exch_type	C4	交易类别		
exchange_name	C8	交易名称		
futures_account	C12	期货账号
contract_code	C30	合约代码
contract_name	C12	品种简称
money_type	C1	币种类别
futures_direction	C1	开平仓方向		
futures_direction_name	C12	开平仓方向		
entrust_bs	C1	买卖方向		
entrust_bs_name	C12	买卖方向		
futu_business_price	N12.6	期货成交价格		
amount_per_hand	N10	每手吨数		
futu_entrust_type	C1	委托类别		
futu_entrust_type_name	C12	委托类别名称		
business_time	N8	成交时间		
business_amount	N16.2	回报数量		
frozen_fare	N16.2	冻结总费用		
futu_business_no	C20	成交编号		
业务说明					

出错说明	错误号	错误信息	错误说明	错误级别	
-51	无此帐户			
-61	期货当日成交查询失败	（其他错误）		

*/
int TTrdItf_HSFF::QryCurTrd()
{
/*
	TList* ResultList = new TList();
	int r = 0;
	AnsiString position_str = FRequest.QryCurTrd.SeqNum;

	do
	{
		FItf->SetHead( FHSFFSet.branch_no, 1506 );
		FItf->SetRange( 15, 1 );

		FItf->AddField(WideString(L"version").c_bstr());
		FItf->AddField(WideString(L"op_branch_no").c_bstr());
		FItf->AddField(WideString(L"op_entrust_way").c_bstr());
		FItf->AddField(WideString(L"op_station").c_bstr());
		FItf->AddField(WideString(L"function_id").c_bstr());
		FItf->AddField(WideString(L"branch_no").c_bstr());

		FItf->AddField(WideString(L"fund_account").c_bstr());
		FItf->AddField(WideString(L"password").c_bstr());

		FItf->AddField( WideString(L"futu_exch_type" ).c_bstr() );
		FItf->AddField( WideString(L"futures_account" ).c_bstr() );
		FItf->AddField( WideString(L"contract_code" ).c_bstr() );
		FItf->AddField( WideString(L"query_mode" ).c_bstr() );
		FItf->AddField( WideString(L"query_direction" ).c_bstr() );
		FItf->AddField( WideString(L"request_num" ).c_bstr() );
		FItf->AddField( WideString(L"futu_position_str" ).c_bstr() );

		FItf->AddValue(WideString(HS_VERSION).c_bstr());
		FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
		FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
		FItf->AddValue( WideString(L"1506" ).c_bstr() );
		FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());

		FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
		FItf->AddValue(WideString(FAccInfo.PW).c_bstr());

		FItf->AddValue( WideString(L""  ).c_bstr() );
		FItf->AddValue( WideString(L"").c_bstr() );  //期货帐户
		FItf->AddValue( WideString(L"").c_bstr() );
		FItf->AddValue( WideString(L"0" ).c_bstr() );
		FItf->AddValue( WideString( ( char ) qdahead ).c_bstr() );
		FItf->AddValue( WideString( IntToStr((int)FRequest.QryCurTrd.MaxRecord) ).c_bstr() );
		FItf->AddValue( WideString( position_str ).c_bstr() );

		r = SendAndReceive();

		if ( FItf->RecordCount < 1 || r < 0 ) break;

		for ( int i = 0; i < FItf->RecordCount; ++i)
		{
			TTradeInfo*	ti	= new TTradeInfo;
			ZeroMemory( ti, sizeof( TTradeInfo ) );

			//组建输出数据
			lstrcpyn( ti->ContractID ,
				AnsiString( FItf->FieldByName( WideString(L"entrust_no" ).c_bstr() ) ).c_str(),SEQ_LEN);
			lstrcpyn( ti->TrdID ,
				AnsiString( FItf->FieldByName( WideString(L"futu_business_no" ).c_bstr() ) ).c_str(),SEQ_LEN);
			lstrcpyn( ti->SecuID,
				AnsiString( FItf->FieldByName( WideString(L"contract_code" ).c_bstr() ) ).c_str(),CODE_LEN);
			lstrcpyn( ti->Account,
				AnsiString( FItf->FieldByName( WideString(L"futures_account" ).c_bstr() ) ).c_str(),ACC_LEN);
			ti->Time = this->ConvertTimeToInt(
				AnsiString( FItf->FieldByName( WideString(L"business_time" ).c_bstr() ) ).c_str() );
			ti->Date = this->ConvertDateToInt(
				AnsiString( FItf->FieldByName( WideString(L"init_date" ).c_bstr() ) ).c_str() );
			ti->Type = this->ConvertOrderType(
				(AnsiString( FItf->FieldByName( WideString(L"entrust_bs" ).c_bstr() ) ) +
				AnsiString( FItf->FieldByName( WideString(L"futures_direction" ).c_bstr() ) )).c_str()  );
			ti->Vol = abs(StrToIntDef( FItf->FieldByName( WideString(L"business_amount" ).c_bstr() ), 0 ));
			//if (ti->Vol==0) {
			//	ti->Vol = -abs(StrToFloatDef( FItf->FieldByName( WideString(L"cancel_amount" ) ), 0 ));
			//}
			ti->Price = StrToFloatDef( FItf->FieldByName( WideString(L"futu_business_price" ).c_bstr() ), -1 );
			ti->Market = this->ConvertMarketType(
				AnsiString( FItf->FieldByName( WideString(L"futu_exch_type" ).c_bstr() ) ).c_str());
			lstrcpyn(ti->SeqNum ,
				AnsiString( FItf->FieldByName( WideString(L"futu_position_str" ).c_bstr() ) ).c_str(),SEQ_LEN);

			if (ti->Price <0 || ti->TrdID[0] == 0 || ti->Vol <=0 || ti->SeqNum[0] == 0 || ti->Time <=0)
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
				ODS('E',PLUGINNAME,"*异常错误,buf=:%s",buf);
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
*/
    database db;
	TradeGateway::ExecutionReportSeq list;
	try
	{
		if(FRequest.QryCurTrd.OrderID[0]==0)
		{
			//增量查询
			db.qry_trades(this->FAccInfo.Capital,FRequest.QryCurTrd.SeqNum,
					FRequest.QryCurTrd.MaxRecord,
					Date().FormatString("yyyymmdd").ToInt(),
					list) ;
		}
		else
		{
			db.qry_trade_by_ordid(this->FAccInfo.Capital,FRequest.QryCurTrd.OrderID,
				Date().FormatString("yyyymmdd").ToInt(),
				list);
		}

		if( list.size()==0 ) return 0;

		NewAns(list.size());
		for( size_t i=0;i<list.size();i++)
		{
		    TTradeInfo &ti = (*FAnswer)[i].QryCurTrd.TrdInfo;
            TradeGateway::ExecutionReport &er = list[i];
            strncpy(ti.Account,er.accountId.c_str(),ACC_LEN);
            strncpy(ti.ContractID,er.ordId.c_str(),SEQ_LEN);
            ti.Date=er.tradeDate;
            ti.Market=mtNo;
            ti.Price=er.lastPx;
            strncpy(ti.SecuID,"",SEQ_LEN);
            strncpy(ti.SeqNum,er.seq.c_str(),SEQ_LEN);
            ti.Time=er.transactTime;
            strncpy(ti.TrdID,er.execId.c_str(),SEQ_LEN);
            ti.Type=otNo;
            ti.Vol=abs((int)er.lastQty);
            if( er.type == TradeGateway::EtCanceled ||
                er.type == TradeGateway::EtRejected ||
                er.type == TradeGateway::Stopped )
                ti.Vol= -ti.Vol;
		}
	}
	catch( std::string &err)
	{
		SetLastError(-1,'E',PLUGINNAME,err.c_str());
		return -1;
	}
 	return 0;
}

/*

功能号	1503	版本号	3.2	更新日期	20060816
功能名称	期货持仓查询			结果集返回	Y
功能描述	期货持仓查询				
输入参数	参数名	类型	说明	长度	缺省值
version	N3	版本号		
op_branch_no	N5	操作员分支代码		
op_entrust_way	C1	委托方式		
identity_type	C1	账户身份类别 1 调拨人 2 指令人 3 查询 默认不输入		
op_station	C12	站点/电话		
function_id	N6	系统功能		
branch_no	N5	分支代码		
fund_account	N9	资金账号		
password	C10	交易密码		
futu_exch_type	C4	交易类别		
futures_account	C12	期货账号		
contract_code	C30	合约代码		
entrust_bs	C1	买卖方向		
query_direction	C1	查询方向，0：顺查；1：倒查		
query_mode	C1	查询模式 0 过滤持仓为0的数据 1 不过滤持仓为0的数据		
request_num	N8	查询条数		
futu_position_str	C100	定位串		
输出参数	参数名	类型	说明	长度	缺省值
futu_position_str	C100	定位串		
futu_exch_type	C4	交易类别		
exchange_name	C8	交易名称		
futures_account	C12	期货账号
contract_code	C30	合约代码		
contract_name	C12	品种简称		
money_type	C1	币种类别		
entrust_bs	C1	买卖方向		
begin_amount	N16.2	期初数量		
enable_amount	N16.2	可用数量		
real_amount	N16.2	当日可平仓数量		
hold_profit_float	N16.2	持仓浮动盈亏		
hold_profit	N16.2	盯市盈亏		
hold_balance	N16.2	上交易日保证金		
today_open_amount	N16.2	当日开仓可用数量		
pre_drop_amount	N16.2	实际上日平仓数量		
futu_average_price	N12.6	平均价		
futu_last_price	N12.6	最新价格		
业务说明					

出错说明	错误号	错误信息	错误说明	错误级别	
-51	无此帐户			
-61	期货预备委托查询失败	（其他错误）

*/

int TTrdItf_HSFF::QryStocks()
{
	TList * Ans=new TList();
	int ret=0;
	AnsiString posstr="";
	TStockInfo *si;

BB:
	FItf->SetHead(FHSFFSet.op_branch_no, 1503);
	FItf->SetRange(17, 1);
	FItf->AddField(WideString(L"version").c_bstr());
	FItf->AddField(WideString(L"op_branch_no").c_bstr());
	FItf->AddField(WideString(L"op_entrust_way").c_bstr());
	FItf->AddField(WideString(L"op_station").c_bstr());
	FItf->AddField(WideString(L"function_id").c_bstr());
	FItf->AddField(WideString(L"branch_no").c_bstr());
	FItf->AddField(WideString(L"fund_account").c_bstr());
	FItf->AddField(WideString(L"password").c_bstr());
	FItf->AddField(WideString(L"identity_type").c_bstr());
	FItf->AddField(WideString(L"futu_exch_type").c_bstr());
	FItf->AddField(WideString(L"futures_account").c_bstr());
	FItf->AddField(WideString(L"contract_code").c_bstr());             //可不可以为空代表全查
	FItf->AddField(WideString(L"entrust_bs").c_bstr());                //可不可以为空代表全查
	FItf->AddField(WideString(L"query_direction").c_bstr());
	FItf->AddField(WideString(L"query_mode").c_bstr());
	FItf->AddField(WideString(L"request_num").c_bstr());
	FItf->AddField(WideString(L"futu_position_str").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
	FItf->AddValue(WideString(L"1503").c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());

	FItf->AddValue(WideString(L"").c_bstr());
	FItf->AddValue(WideString(this->ConvertMarketType(FRequest.QryStocks.Market)).c_bstr()); //FUTU_EXCH_TYPE
	FItf->AddValue(WideString(L"").c_bstr());
	FItf->AddValue(WideString(L"").c_bstr());
	FItf->AddValue(WideString(L"").c_bstr());                          //entrust_bs  1-买
	FItf->AddValue(WideString(L"0").c_bstr());                           //(char)qdahead
	FItf->AddValue(WideString(L"0").c_bstr());                         //query_mode 有疑问
	FItf->AddValue(WideString(L"20").c_bstr());
	FItf->AddValue(WideString(posstr).c_bstr());

	int r  = SendAndReceive();
	if ( FItf->RecordCount < 1 || r < 0 ) goto HH;

	while(FItf->EOF_==0)
	{
		si=new TStockInfo;
		ZeroMemory(si,sizeof(TStockInfo));
		Ans->Add(si);
		posstr=AnsiString(FItf->FieldByName(WideString(L"futu_position_str").c_bstr()));
		si->Market = this->ConvertMarketType(
			AnsiString(FItf->FieldByName(WideString(L"futu_exch_type").c_bstr())).c_str());
		lstrcpyn(si->SecuID,
			AnsiString(FItf->FieldByName(WideString(L"contract_code").c_bstr())).c_str(),CODE_LEN);
		lstrcpyn(si->Account,
			AnsiString(FItf->FieldByName(WideString(L"futures_account").c_bstr())).c_str(),ACC_LEN);
		si->Balance = StrToFloatDef(FItf->FieldByName(WideString(L"begin_amount").c_bstr()),0);
		si->Available =  StrToFloatDef(FItf->FieldByName(WideString(L"enable_amount").c_bstr()),0);
		si->PosNum  = StrToFloatDef(FItf->FieldByName(WideString(L"real_amount").c_bstr()),0);
		si->CostPrice = si->CurPrice=StrToFloatDef(FItf->FieldByName(WideString(L"futu_average_price").c_bstr()),0);
		si->CurPrice =  si->CurPrice=StrToFloatDef(FItf->FieldByName(WideString(L"futu_last_price").c_bstr()),0);
		si->PosDir = this->ConvertPosDir(
			AnsiString(FItf->FieldByName(WideString(L"entrust_bs").c_bstr())).c_str());
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
功能号	1004	版本号	3.2	更新日期	20060816
功能名称	期货委托确认			结果集返回	N
功能描述	期货委托确认				
输入参数	参数名	类型	说明	长度	缺省值
version	N3	版本号		
op_branch_no	N5	操作员分支代码		
op_entrust_way	C1	委托方式		
identity_type	C1	账户身份类别 1 调拨人 2 指令人 3 查询 默认不输入		
op_station	C12	站点/电话		
function_id	N6	系统功能		
branch_no	N5	分支代码		
fund_account	N9	资金账号		
password	C10	交易密码		
futu_exch_type	C4	交易类别		
futures_account	C12	期货账号		
contract_code	C30	合约代码		
entrust_bs	C1	买卖方向		
futures_direction	C1	买卖方向		
hedge_type	C1	套保标志		
entrust_amount	N16.2	期货委托数量		
futu_entrust_price	N12.6	期货委托价格		
输出参数	参数名	类型	说明	长度	缺省值
error_no	N4	错误号		
error_info	C20	错误原因		
entrust_no	N8	委托编号		
业务说明					

出错说明	错误号	错误信息	错误说明	错误级别
-51	无此帐户			
-61	期货委托确认失败	（其他错误）
*/

int TTrdItf_HSFF::Order()
{
	FItf->SetHead( FHSFFSet.branch_no, 1004 );
	FItf->SetRange( 16, 1 );

	FItf->AddField( WideString(L"version" ).c_bstr() );
	FItf->AddField( WideString(L"op_branch_no" ).c_bstr() );
	FItf->AddField( WideString(L"op_entrust_way" ).c_bstr() );
	FItf->AddField( WideString(L"op_station" ).c_bstr() );
	FItf->AddField( WideString(L"branch_no" ).c_bstr() );
	FItf->AddField( WideString(L"fund_account" ).c_bstr() );
	FItf->AddField( WideString(L"password" ).c_bstr() );
	FItf->AddField( WideString(L"function_id" ).c_bstr() );
	FItf->AddField( WideString(L"futu_exch_type" ).c_bstr() );
	FItf->AddField( WideString(L"futures_account" ).c_bstr() );
	FItf->AddField( WideString(L"contract_code" ).c_bstr() );
	FItf->AddField( WideString(L"entrust_bs" ).c_bstr() );
	FItf->AddField( WideString(L"futures_direction" ).c_bstr() );
	FItf->AddField( WideString(L"hedge_type" ).c_bstr() );
	FItf->AddField( WideString(L"entrust_amount" ).c_bstr() );
	FItf->AddField( WideString(L"futu_entrust_price" ).c_bstr() );


	FItf->AddValue( WideString(HS_VERSION).c_bstr());
	FItf->AddValue( WideString(IntToStr(FHSFFSet.op_branch_no)).c_bstr());
	FItf->AddValue( WideString(FHSFFSet.op_entrust_way).c_bstr());
	FItf->AddValue( WideString(FHSFFSet.op_station).c_bstr());
	FItf->AddValue( WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());
	FItf->AddValue( WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue( WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue( WideString(L"1004" ).c_bstr() );
	FItf->AddValue( WideString( this->ConvertMarketType(FRequest.Order.Market)).c_bstr());
	FItf->AddValue( WideString( this->GetStockAccountByMarket(FRequest.Order.Market)).c_bstr());
	FItf->AddValue( WideString( FRequest.Order.SecuID ).c_bstr());
	FItf->AddValue( WideString( this->ConvertOrderType( FRequest.Order.Type)[0] ).c_bstr());
	FItf->AddValue( WideString( this->ConvertOrderType( FRequest.Order.Type)[1] ).c_bstr());   //open or close 1,2 ,4
	FItf->AddValue( WideString(L"0").c_bstr());   //'0'	投机'1'	套保
	FItf->AddValue( WideString( IntToStr( FRequest.Order.Num )).c_bstr());

	long lp = (long)(FRequest.Order.Price * 100.0f);
	if( lp % 10 >=5 )
		lp = lp/10 + 1;
	else
		lp = lp/10;

	AnsiString s;
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
			AnsiString	id;
			if ( FItf->RecordCount > 0 )
			{
				id = AnsiString( FItf->FieldByName( WideString(L"entrust_no" ).c_bstr() ) );
				if ( id.Length() > 0 )
				{
					NewAns( 1 );
					lstrcpyn( ( *FAnswer )[0].Order.ContractID, id.c_str(), SEQ_LEN);
                    //add to db
                    TradeGateway::OrderReport op;
                    op.base.accountId = this->FAccInfo.Capital;
                    op.base.inst.securityID = FRequest.Order.SecuID;
                    switch (FRequest.Order.Market) {
                    case mtSHA : op.base.inst.securityIDSource = TradeGateway::SSE;
                    break;
                    case mtSZA : op.base.inst.securityIDSource =  TradeGateway::SZSE;
                    break;
                    case mtJJS : op.base.inst.securityIDSource =  TradeGateway::SHFE;
                    break;
                    case mtFSH : op.base.inst.securityIDSource =  TradeGateway::DCE;
                    break;
                    case mtFZZ : op.base.inst.securityIDSource = TradeGateway::CZCE ;
                    break;
                    case mtFDL : op.base.inst.securityIDSource =  TradeGateway::CFFEX;
                    break;
                    case mtHK  : op.base.inst.securityIDSource =  TradeGateway::HKEX;
                    break;
                    case mtNo  : op.base.inst.securityIDSource = TradeGateway::MktUnknow ;
                    break;
                    }

                    op.base.posEfct = TradeGateway::PosEftUnknow;
                    switch( FRequest.Order.Type )
                    {
                    case otBuy:
                        op.base.s=TradeGateway::Buy;
                        break;
                    case otSell  :
                        op.base.s=TradeGateway::Sell;
                        break;
                    case otETFSub:
                        op.base.s=TradeGateway::Subscribe;
                        break;
                    case otETFRed:
                        op.base.s=TradeGateway::Redeem;
                        break;
                    case otOpenBuy:
                        op.base.s=TradeGateway::Buy;
                        op.base.posEfct = TradeGateway::Open;
                        break;
                    case otOpenSell:
                        op.base.s=TradeGateway::Sell;
                        op.base.posEfct = TradeGateway::Open;
                        break;
                    case otCloseBuy:
                        op.base.s=TradeGateway::Buy;
                        op.base.posEfct = TradeGateway::Close;
                        break;
                    case otCloseSell:
                        op.base.s=TradeGateway::Sell;
                        op.base.posEfct = TradeGateway::Close;
                        break;
                    case otCloseTodayBuy :
                        op.base.s=TradeGateway::Buy;
                        op.base.posEfct = TradeGateway::CloseToday;
                        break;
                    case otCloseTodaySell:
                        op.base.s=TradeGateway::Sell;
                        op.base.posEfct = TradeGateway::CloseToday;
                        break;
                    default:
                        op.base.s=TradeGateway::SideUnknow;
                    }

                    op.base.type = TradeGateway::Limit;
                    op.base.lmtPrice =  FRequest.Order.Price;
                    op.base.ordQty =FRequest.Order.Num;
                    op.base.ordId = (*FAnswer)[0].Order.ContractID;
                    op.base.date = Date().FormatString("yyyymmdd").ToInt();
                    op.base.time = Time().FormatString("hhnnss").ToInt();
                    op.ordStatus = TradeGateway::PendingNew;
                    op.cumQty = 0;
                    op.avgPx = 0;
                    op.leavesQty =FRequest.Order.Num;

                    database db;
                    try
                    {
                        db.add_order(&op.base);
                        order_man.add_order(op);
                    }
                    catch( std::string &err)
                    {
                        SetLastError(-1,'E',PLUGINNAME,"加入委托到本地数据库失败:%s",err.c_str());
                        return -1;
                    }

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
功能号	1005	版本号	3.2	更新日期	20060816
功能名称	期货委托撤单			结果集返回	N
功能描述	期货委托撤单				
输入参数	参数名	类型	说明	长度	缺省值
version	N3	版本号		
op_branch_no	N5	操作员分支代码		
op_entrust_way	C1	委托方式		
identity_type	C1	账户身份类别 1 调拨人 2 指令人 3 查询 默认不输入
op_station	C12	站点/电话		
function_id	N6	系统功能
branch_no	N5	分支代码
fund_account	N9	资金账号		
password	C10	交易密码		
entrust_no	N8	委托编号		
输出参数	参数名	类型	说明	长度	缺省值
error_no	N4	错误号		
error_info	C20	错误原因		
entrust_no	N8	委托编号		
业务说明					

出错说明	错误号	错误信息	错误说明	错误级别	
-51	无此帐户			
-61	期货委托撤单失败	（其他错误）
*/
int TTrdItf_HSFF::Undo()
{
	FItf->SetHead( FHSFFSet.branch_no, 1005 );
	FItf->SetRange( 9, 1 );

	FItf->AddField( WideString(L"version" ).c_bstr() );
	FItf->AddField( WideString(L"op_branch_no" ).c_bstr() );
	FItf->AddField( WideString(L"op_entrust_way" ).c_bstr() );
	FItf->AddField( WideString(L"op_station" ).c_bstr() );
	FItf->AddField( WideString(L"branch_no" ).c_bstr() );
	FItf->AddField( WideString(L"fund_account" ).c_bstr() );
	FItf->AddField( WideString(L"password" ).c_bstr() );
	FItf->AddField( WideString(L"function_id" ).c_bstr() );
	FItf->AddField( WideString(L"entrust_no" ).c_bstr() );


	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSFFSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(FHSFFSet.op_station).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSFFSet.branch_no)).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString(L"1005" ).c_bstr() );
	FItf->AddValue(WideString( FRequest.Undo.ContractID ).c_bstr() );

	int	r	= SendAndReceive();
	try
	{
		if ( r != 0 )
		{
			if( strstr(FLastError.Text, "p_old_entrust_status = 6") != NULL )
			{
				// 已经撤销了
				return ERR_UNDO_ALREADY_CANCLED;
			}
			else if (strstr(FLastError.Text, "p_old_entrust_status = 8") != NULL )
			{
				// 表示已经成交，无法撤单
				return ERR_UNDO_ALREADY_FILLED;
			}
			else if (strstr(FLastError.Text, "p_old_entrust_status = 9") != NULL )
			{
				// ？表示废单
				return ERR_UNDO_REPEAL;
			}
			else if (strstr(FLastError.Text, "p_old_entrust_status = 5") != NULL )
			{
				// 已经部撤了
				return ERR_UNDO_ALREADY_CANCLED;
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
	FHSFFSet.futu_entrust_type ="0"; //0-普通策略委托

	FAccount = "";

	FItf = NULL;
}

TTrdItf_HSFF::~TTrdItf_HSFF()
{
	if( FItf )
	{
		CloseLink();
	}
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
	//ODS('M',PLUGINNAME,"市场类型:%s",t);
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
	//ODS('M',PLUGINNAME,"委托类型:%s",t);
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
	//ODS('M',PLUGINNAME,"委托状态:%s",t);
	switch (t[0])
	{
	case eswb    :   return oswb;      //未报
	case esyb    :   return osyb;      //已报
	case esdc1   :   return osdc;      //待撤
	case esdc2   :   return osdc;      //待撤
	case esbc    :   return osbw;      //部撤
	case esyc1   :   return osyc;      //已撤
	case esyc2   :   return osyc;      //已撤
	case esyc    :   return oscj;      //已成
	case esyf    :   return osyf;      //已废
	default:
		return osno;
	}
}

pos_direction TTrdItf_HSFF::ConvertPosDir(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return pdNo;
	//ODS('M',PLUGINNAME,"部位类型:%s",t);
	switch( t[0] )
	{
	case '1': // 多头
		return pdLong;
	case '2': // 空头
		return pdShort;
	default:
		return pdNo;
	}
}

money_type   TTrdItf_HSFF::ConvertMoneyType(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return motNo;

	//ODS('M',PLUGINNAME,"资金类型:%s",t);
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
		// 判断是否存在插件的设置，没有的话返回false以便系统能够生成默认的设置
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
		FHSFFSet.futu_exch_type   = ini->ReadString (PLUGINNAME,"futu_exch_type",FHSFFSet.futu_exch_type);
		FHSFFSet.futu_entrust_type= ini->ReadString (PLUGINNAME,"futu_entrust_type",FHSFFSet.futu_entrust_type);
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
		ini->WriteString (PLUGINNAME,"futu_exch_type",   FHSFFSet.futu_exch_type);
		ini->WriteString (PLUGINNAME,"futu_entrust_type",FHSFFSet.futu_entrust_type);
		ini->UpdateFile();
	}
	__finally
	{
		delete ini;
	}
}

int TTrdItf_HSFF::KeepAlive(void)
{
    order_man.qry_orders(this);
	return 0;
}
