//---------------------------------------------------------------------------
#include "UTrdItf_HS.h"
//---------------------------------------------------------------------------
t_exchange_type TBourse2t_exchange_type(TBourse br)
{
	if(br==bsSH) return etsh;
	if(br==bsSZ) return etsz;
	return etqt;
}

int  TTrdItf_HS::Init()
{
	long i=FItf->get_Connection();
	if(i>=0) FItf->DisConnect();
	return FItf->Connect1();
}

/*
功能编号： 200
版本编号: 1.00

请求:
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH> branch_no<SOH>input_content<SOH>
content_type<SOH>account_content<SOH>password<SOH>

应答:
error_no<SOH>error_info<SOH>
branch_no<SOH>fund_account<SOH>client_name<SOH>
money_count<SOH>money_type<SOH>exchange_type<SOH>stock_account<SOH>
client_rights<SOH>

请求注释：
op_branch_no：	操作分支营业部号，以追踪该请求来自哪个分支。周边可以通过配置
获得本操作分支营业部号，周边必须输入。
op_station：	该请求来自的站点以追踪请求的来源。一般在营业部内部该值置为工作
站的MAC地址，而对于电话接入可考虑置为来电号码。
branch_no：	是股民所在营业部号，用于通炒，可由股民自己选择输入，当股民不选择
分支号，则周边应将其置为op_branch_no以表示本营业部。
input_content：	'1'，'2'，'3'，4'，'5', '6'分别表示account_content代表资金帐
号，股东内码，和资金卡号，银行帐号，股东帐号，客户编号。
content_type：	当input_content为'4'，'5'时，则content_type明确银行号和股东
的市场类别，其它输入为'0'。

注意：
由于目前的系统必须由branch_no + fund_account决定一个客户，所以用户必须输入
branch_no。对于集中的数据库通炒系统来说，一个客户的分支在第一次输入时，可
以输入0，表示不确定该客户的branch_no，但在服务端返回后，必须重新置分支号，
以后的功能必须输入重置后的分支号，因为系统以下的功能必须按照分支与资金帐
号校验客户。
如果是分布型数据支持通炒方式，客户端必须要求客户输入确定的分支号，或者按
某个规则得到确定的分支号码branch_no，或通过调用功能号104得到相应的分支号。

应答注释：
money_count:  币种个数。
client_rights: 客户权限，主要用于680委托时返回其680委托权限，包含Y为托银客户；
注意：
如果account_content为'2'，'5'时，返回中的exchang_type和stock_account存在意义,
否则这两个域值无意义。
错误号：-41："资金密码到期未修改"        （需提示，仍可登录）
-42："交易密码到期未修改"        （需提示，仍可登录）
-51："无此帐户"
-63："密码错误"
-66："您的帐户状态不正常"
-64："您没有此类委托的权限"
-61："帐户登录失败"              （其他错误）
*/
int  TTrdItf_HS::SetAccount()
{
	char input_content;
	char content_type;

	if(FRequest.SetAccount.Sort==asCA)
	{
		input_content=(char)iczj;
		content_type=0;
		lstrcpyn(FAccInfo.Capital,FRequest.SetAccount.Account,13);
	}
	else if(FRequest.SetAccount.Sort==asSH)
	{
		input_content=icsa;
		content_type=etsh;
		lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,13);
	}
	else if(FRequest.SetAccount.Sort==asSZ)
	{
		input_content=icsa;
		content_type=etsz;
		lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,13);
	}
	else
		return ERR_UNKNOW_ACCOUNT_TYPE;

	lstrcpyn(FAccInfo.PW,FRequest.SetAccount.PW,13);

	FItf->SetHead(FHSSet.branch_no,200);
	FItf->SetRange(9,1);

	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("input_content").c_bstr());
	FItf->AddField(WideString("content_type").c_bstr());
	FItf->AddField(WideString("account_content").c_bstr());
	FItf->AddField(WideString("password").c_bstr());

	/*
	FItf->AddValue(WideString("1").c_bstr());
	FItf->AddValue(WideString("1000").c_bstr());
	FItf->AddValue(WideString("DEMO").c_bstr());
	FItf->AddValue(WideString("7").c_bstr());
	FItf->AddValue(WideString("1000").c_bstr());
	FItf->AddValue(WideString("1").c_bstr());
	FItf->AddValue(WideString("0").c_bstr());
	FItf->AddValue(WideString("1000007").c_bstr());
	FItf->AddValue(WideString("111111").c_bstr());
	*/

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(String(input_content).c_str()).c_bstr());
	FItf->AddValue(WideString(String(content_type).c_str()).c_bstr());
	FItf->AddValue(WideString(FRequest.SetAccount.Account).c_bstr());
	FItf->AddValue(WideString(FRequest.SetAccount.PW).c_bstr());

	if(FItf->Send()!=0) return ERR_SEND_FAULT;

	FItf->FreePack();

	if(FItf->Receive()!=0) return ERR_RECV_FAULT;

	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); return FItf->ErrorNo; }

	if(FItf->RecordCount>0)
	{
		String acc=String(FItf->FieldByName(WideString("fund_account")));
		if(acc.Length()>0)
		{
			if(FRequest.SetAccount.Sort==asCA)
			{
				QryAccount(etsh);
				QryAccount(etsz);
			}
			else if(FRequest.SetAccount.Sort==asSH)
			{
				lstrcpyn(FAccInfo.Capital,acc.c_str(),13);
				QryAccount(etsz);
			}
			else if(FRequest.SetAccount.Sort==asSZ)
			{
				lstrcpyn(FAccInfo.Capital,acc.c_str(),13);
				QryAccount(etsh);
			}
			if(FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) { return -1; }

			NewAns(1);
			memcpy(&((*FAnswer)[0].SetAccount.AccountInfo),&FAccInfo,sizeof(TAccountInfo));
			return 0;
		}
		else
		{
			return String(FItf->FieldByName(WideString("error_no"))).ToIntDef(ERR_OTHERS);
		}
	}
	else return ERR_NO_ACK;
}

/*
交易功能: 查询帐号
功能编号： 407
版本编号: 1

请求:
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH> branch_no<SOH>fund_account<SOH> password<SOH>
exchange_type<SOH>query_direction<SOH>request_num<SOH>position_str<SOH>

应答:
error_no<SOH>error_info<SOH>
position_str<SOH>exchange_type<SOH>exchange_name<SOH>stock_account<SOH>
main_flag <SOH>holder_status<SOH>register<SOH>

请求注释:
exchange_type：不支持0，为空，查所有交易所账号。
应答注释：
main_flag：主副标志，为'1'为主帐号。
holder_status：帐户状态，'0'为正常，其他为不正常；
register:指定标志  '0'未指定 '1'指定
错误号：-61："查询失败"      （包含所有错误）
*/
int  TTrdItf_HS::QryAccount(t_exchange_type et)
{
	FItf->SetHead(FHSSet.branch_no,407);
	FItf->SetRange(11,1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("exchange_type").c_bstr());
	FItf->AddField(WideString("query_direction").c_bstr());
	FItf->AddField(WideString("request_num").c_bstr());
	FItf->AddField(WideString("position_str").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FRequest.SetAccount.Account).c_bstr());
	FItf->AddValue(WideString(FRequest.SetAccount.PW).c_bstr());
	FItf->AddValue(WideString((char)et).c_bstr());  //上海股东账号
	FItf->AddValue(WideString((char)qdahead).c_bstr());
	FItf->AddValue(WideString("0").c_bstr());
	FItf->AddValue(WideString("").c_bstr());

	if(FItf->Send()!=0) return ERR_SEND_FAULT;

	FItf->FreePack();

	if(FItf->Receive()!=0) return ERR_RECV_FAULT;
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); return FItf->ErrorNo; }
	String tp;
	while (!FItf->EOF_)
	{
		tp=String(FItf->FieldByName(WideString("exchange_type")));
		if(tp==String((char)etsh))
		{
			if(String(FItf->FieldByName(WideString("main_flag")))=="1")
			{
				lstrcpyn(FAccInfo.SH,String(FItf->FieldByName(WideString("stock_account"))).c_str(),13);
				return 0;
			}
		}
		else if(tp==String((char)etsz))
		{
			if(String(FItf->FieldByName(WideString("main_flag")))=="1")
			{
				lstrcpyn(FAccInfo.SZ,String(FItf->FieldByName(WideString("stock_account"))).c_str(),13);
				return 0;
			}
		}

		FItf->MoveBy(1);
	}

	return -61;
}


//////查询函数//////
/*
*/
int  TTrdItf_HS::GetTrdInfo()
{
	FItf->SetHead(FHSSet.branch_no, 400);
	FItf->SetRange(3, 1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("exchange_type").c_bstr());
	FItf->AddField(WideString("stock_code").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString(FRequest.GetTrdInfo.SecuID+1).c_bstr());

	if (FItf->Send() != 0)
		return ERR_SEND_FAULT;

	FItf->FreePack();

	if (FItf->Receive() != 0)
		return ERR_RECV_FAULT;

	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); return FItf->ErrorNo; }

	if (FItf->RecordCount > 0)
	{
		//int ret = String(FItf->FieldByName(WideString("error_no"))).Length();
		//if (ret == 0)
		//{
			NewAns(1);
			TGetTrdInfo_Ans *gi = &(*FAnswer)[0].GetTrdInfo;
			gi->BuyInfo.ZXJ = StrToFloatDef(String(FItf->FieldByName(WideString("last_price"))), -1);
			gi->BuyInfo.Price1 = StrToFloatDef(String(FItf->FieldByName(WideString("buy_price1"))), -1);
			gi->BuyInfo.Price2 = StrToFloatDef(String(FItf->FieldByName(WideString("buy_price2"))), -1);
			gi->BuyInfo.Price3 = StrToFloatDef(String(FItf->FieldByName(WideString("buy_price3"))), -1);
			gi->BuyInfo.Volum1 = StrToIntDef(String(FItf->FieldByName(WideString("buy_amount1"))), -1);
			gi->BuyInfo.Volum2 = StrToIntDef(String(FItf->FieldByName(WideString("buy_amount2"))), -1);
			gi->BuyInfo.Volum3 = StrToIntDef(String(FItf->FieldByName(WideString("buy_amount3"))), -1);
			gi->BuyInfo.CJSL = StrToIntDef(String(FItf->FieldByName(WideString("business_amount"))), -1);

			gi->SellInfo.ZXJ = StrToFloatDef(String(FItf->FieldByName(WideString("last_price"))), -1);
			gi->SellInfo.Price1 = StrToFloatDef(String(FItf->FieldByName(WideString("sell_price1"))), -1);
			gi->SellInfo.Price2 = StrToFloatDef(String(FItf->FieldByName(WideString("sell_price2"))), -1);
			gi->SellInfo.Price3 = StrToFloatDef(String(FItf->FieldByName(WideString("sell_price3"))), -1);
			gi->SellInfo.Volum1 = StrToIntDef(String(FItf->FieldByName(WideString("sell_amount1"))), -1);
			gi->SellInfo.Volum2 = StrToIntDef(String(FItf->FieldByName(WideString("sell_amount2"))), -1);
			gi->SellInfo.Volum3 = StrToIntDef(String(FItf->FieldByName(WideString("sell_amount3"))), -1);
			gi->SellInfo.CJSL = StrToIntDef(String(FItf->FieldByName(WideString("business_amount"))), -1);

			return 0;
		//}
		//else
		//{
		//	return String(FItf->FieldByName(WideString("error_no"))).ToIntDef(ERR_OTHERS);
		//}
	}
	else
	{
		return ERR_NO_ACK;
	}

}

/*
功能编号： 405
版本编号: 1.00

请求:
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH>branch_no<SOH>fund_account<SOH> password<SOH>
money_type<SOH>

应答:
error_no<SOH>error_info<SOH>
money_type<SOH>current_balance<SOH>enable_balance<SOH>fetch_balance<SOH>
interest<SOH>asset_balance<SOH>

请求注释:

应答注释：
enable_balance: 可用资金；
fetch_balance: 可取资金；
interest:    预计利息；
asset_balance: 资产总值
错误号:
-61:"查询失败"           （包含所有错误）
*/
int  TTrdItf_HS::QryMoney()
{
	FItf->SetHead(FHSSet.branch_no,405);
	FItf->SetRange(8,1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("money_type").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString((char)mtrmb).c_bstr());

	if(FItf->Send()!=0) return ERR_SEND_FAULT;

	FItf->FreePack();

	if(FItf->Receive()!=0) return ERR_RECV_FAULT;
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); return FItf->ErrorNo; }
	if(FItf->RecordCount>0)
	{
		if(String(FItf->FieldByName(WideString("money_type")))==String((char)mtrmb))
		{
			NewAns(1);

			(*FAnswer)[0].QryMoney.Balance=StrToFloatDef(String(FItf->FieldByName(WideString("current_balance"))),-1);
			(*FAnswer)[0].QryMoney.Available=StrToFloatDef(String(FItf->FieldByName(WideString("enable_balance"))),-1);
			(*FAnswer)[0].QryMoney.asset_balance=StrToFloatDef(String(FItf->FieldByName(WideString("asset_balance"))),-1);

			return 0;
		}
		else
		{
			return String(FItf->FieldByName(WideString("error_no"))).ToIntDef(ERR_OTHERS);
		}
	}
	else return ERR_NO_ACK;
}

/*
功能编号：403
版本编号: 1.00
请求:
version<SOH>op_branch_no<SOH>op_station<SOH>op_entrust_way<SOH>
branch_no<SOH>fund_account<SOH>password<SOH>exchange_type<SOH>
stock_account<SOH>stock_code<SOH>query_direction<SOH>
request_num<SOH>position_str<SOH>query_mode<SOH>

应答: 
error_no<SOH>error_infoSOH>
position_str<SOH>exchange_type<SOH>stock_account<SOH>stock_code<SOH>stock_name<SOH>
current_amount<SOH>enable_amount<SOH>last_price<SOH>cost_price<SOH>
income_balance<SOH>hand_flag<SOH>market_value<SOH>

请求注释:
exchange_type   : 不为空，查确定的，为空，查所有。
stock_code      : 为空，查所有，不为空，查确定的，此时exchange_type必须不为空。
position_str    : exchange_type+stock_code+stock_account总长度为17个字节。
query_mode      :'0'：明细 '1'：汇总。

应答注释:
market_value    : 在明细下为每个股东帐号的市值，而在汇总下则为fund_account的，汇总下无stock_account。
hand_flag       : '0'--股   '1' -- 手。

错误号：
-52："无此股票"              （此错误可不作判断）
-60："没有股票记录"
-61："查询失败"              （其他错误）

*/

int  TTrdItf_HS::QryStock()
{
	FItf->SetHead(FHSSet.op_branch_no, 403);
	FItf->SetRange(14, 1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("exchange_type").c_bstr());
	FItf->AddField(WideString("stock_account").c_bstr());
	FItf->AddField(WideString("stock_code").c_bstr());
	FItf->AddField(WideString("query_direction").c_bstr());
	FItf->AddField(WideString("request_num").c_bstr());
	FItf->AddField(WideString("position_str").c_bstr());
	FItf->AddField(WideString("query_mode").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString(FRequest.QryStock.SecuID+1).c_bstr());
	FItf->AddValue(WideString((char)qdahead).c_bstr());
	FItf->AddValue(WideString("1").c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString("0").c_bstr());

	if (FItf->Send() != 0)
		return ERR_SEND_FAULT;

	FItf->FreePack();

	if (FItf->Receive() != 0)
		return ERR_RECV_FAULT;
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); return FItf->ErrorNo; }
	if (FItf->RecordCount > 0)
	{
		//int ret = String(FItf->FieldByName(WideString("error_no"))).Length();
		//if (ret == 0)
		//{
			NewAns(1);
			TQryStock_Ans *sa = &(*FAnswer)[0].QryStock;
			int n = String(FItf->FieldByName(WideString("hand_flag"))).ToIntDef(0)==0 ? 1 : 100;

			sa->Balance = String(FItf->FieldByName(WideString("current_amount"))).ToIntDef(-1) * n;
			sa->Available = String(FItf->FieldByName(WideString("enable_amount"))).ToIntDef(-1) * n;
			sa->BuyFreeze = 0;
			sa->SellFreeze = 0;
			return 0;
		//}
		//else
		//{
		//	return String(FItf->FieldByName(WideString("error_no"))).ToIntDef(ERR_OTHERS);
		//}
	}
	else
	{
		return ERR_NO_ACK;
	}

	//return ERR_UNIMPLEMENTED;
}

int  TTrdItf_HS::QryCanBuy()
{
	return ERR_UNIMPLEMENTED;
}

/*
功能编号： 402
版本编号: 1.00
请求:
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH> serial_no<SOH>branch_no<SOH>fund_account<SOH> password<SOH>
exchange_type<SOH>stock_account<SOH>stock_code<SOH>query_direction <SOH>
request_num<SOH>query_mode<SOH>position_str<SOH>
应答:
error_no<SOH>error_info<SOH>
position_str<SOH>serial_no<SOH>date<SOH>exchange_type<SOH>stock_account<SOH>
stock_code<SOH>stock_name<SOH>entrust_bs<SOH>
business_price<SOH>business_amount<SOH>
business_time<SOH>business_status<SOH>business_type<SOH>business_times <SOH>
entrust_no<SOH>report_no<SOH>business_balance<SOH>
请求注释:
exchange_type：不为空，查确定的，为空，查所有
stock_code：为空，查所有，不为空，查确定的，此时exchange_type必须不为空
serial_no：不为0表示按合同号查成交,但按合同号查成交时，应取被查合同号减1的值，
且request_num为1，且客户在收到应答后要检查返回的成交是否是合同号与要求查询的一致；
query_mode：'0'：明细'1'：合并'2'：汇总；
应答注释：
business_status:成交状态0：'成交'，2：'废单'4：'确认'
business_type:：0：'买卖'2：'撤单'
serial_no暂不使用
business_balance:成交金额
错误号：
-52："无此股票"      （此错误可不作判断）
-60："没有成交记录"
-61："查询失败"      （其他错误）
*/
/*
int  TTrdItf_HS::QryDetail()
{
FItf->SetHead(FHSSet.branch_no,402);
FItf->SetRange(15,1);
FItf->AddField(WideString("version");
FItf->AddField(WideString("op_branch_no");
FItf->AddField(WideString("op_station");
FItf->AddField(WideString("op_entrust_way");
FItf->AddField(WideString("serial_no");
FItf->AddField(WideString("branch_no");
FItf->AddField(WideString("fund_account");
FItf->AddField(WideString("password");
FItf->AddField(WideString("exchange_type");
FItf->AddField(WideString("stock_account");
FItf->AddField(WideString("stock_code");
FItf->AddField(WideString("query_direction");
FItf->AddField(WideString("request_num");
FItf->AddField(WideString("query_mode");
FItf->AddField(WideString("position_str");

FItf->AddValue(WideString(HS_VERSION);
FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str());
FItf->AddValue(WideString(FHSSet.op_station);
FItf->AddValue(WideString(FHSSet.op_entrust_way);
int id=StrToIntDef(FRequest.QryDetail.ContractID,-1);
if(id<0) return ERR_OTHER;
FItf->AddValue(WideString(IntToStr(--id).c_str());
FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str());
FItf->AddValue(WideString(FAccInfo.Capital);
FItf->AddValue(WideString(FAccInfo.PW);
FItf->AddValue(WideString(TBourse2t_exchange_type(FRequest.QryDetail.Bourse));
FItf->AddValue(WideString((FRequest.QryDetail.Bourse==bsSH ? FAccInfo.SH : FAccInfo.SZ));
FItf->AddValue(WideString("");
FItf->AddValue(WideString(qdahead);
FItf->AddValue(WideString("1");
FItf->AddValue(WideString("0");
FItf->AddValue(WideString("");

if(FItf->Send()!=0) return ERR_SEND_FAULT;

FItf->FreePack();

if(FItf->Receive()!=0) return ERR_RECV_FAULT;

if(FItf->RecordCount==1)
{
if(String(FItf->FieldByName(WideString("serial_no")).ToIntDef(-1)==id)
{
NewAns(1);
(*FAnswer)[0].QryDetail.Price=StrToFloatDef(String(FItf->FieldByName(WideString("current_balance")),-1);
(*FAnswer)[0].QryDetail.Num=StrToFloatDef(String(FItf->FieldByName(WideString("enable_balance")),-1);
(*FAnswer)[0].QryDetail.UndoNum=StrToFloatDef(String(FItf->FieldByName(WideString("asset_balance")),-1);

return 0;
}
else
{
return String(FItf->FieldByName(WideString("error_no")).ToIntDef(ERR_OTHER);
}
}
else return ERR_NO_ACK;
}
*/
/*
交易功能: 查询委托
功能编号： 401
版本编号: 1.00
请求:
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH> branch_no<SOH>fund_account<SOH> password<SOH>
exchange_type<SOH>stock_account<SOH>stock_code<SOH>query_direction<SOH>
request_num <SOH>position_str<SOH>sort_direction<SOH>locate_entrust_no<SOH>

应答:
error_no<SOH>error_info<SOH>
position_str<SOH>entrust_no<SOH>exchange_type<SOH>stock_account<SOH>
stock_code<SOH>stock_name<SOH>entrust_bs<SOH> entrust_price<SOH>
entrust_amount<SOH>business_amount<SOH>business_price<SOH>report_no<SOH>
report_time<SOH>entrust_type<SOH>entrust_status<SOH>status_name<SOH>
cancel_info<SOH>

请求注释:
exchange_type：如果不为空格，查确定的，为空，查所有。
stock_code：如果为空格，查所有，不为空，查确定的，此时exchange_type必须不为空
sort_direction：所得数据的排序方式，0：正序；1：倒序；
locate_entrust_no：查指定委托号的委托，且request_num为1，且前台在收到应答后要检查返回的委托的委托号是否与要求查询的一致，此时exchange_type和stock_code要为空串。

应答注释：

错误号:
-52："无此股票"        （此错误可不作判断）
-60："没有委托记录"
-61："查询失败"        （其他错误）
*/

/* 国泰君安
-交易功能: 查询委托
function_id: 401
版本编号: 1.00
请求: 
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH> branch_no<SOH>fund_account<SOH> password<SOH>
		exchange_type<SOH>stock_account<SOH>stock_code<SOH>query_direction<SOH>
request_num <SOH>position_str<SOH>
应答: 
error_no<SOH>error_info<SOH>
entrust_no<SOH>entrust_no<SOH>exchange_type<SOH>stock_account<SOH>stock_code<SOH>
stock_name<SOH>entrust_bs<SOH> entrust_price<SOH>entrust_amount<SOH>
business_amount<SOH>business_price<SOH>report_time<SOH>
entrust_status<SOH>entrust _name<SOH>cancel_info<SOH>
    注释: 
        exchange_type：不为空，查确定的，为空，查所有
stock_code：为空，查所有，不为空，查确定的，此时exchange_type必须不为空
		entrust_no：不为0，查该笔委托，此时exchange_type和stock_code不起作用
    错误号: -52："无此股票"        （此错误可不作判断）
       -60："没有委托记录"
       -61："查询失败"        （其他错误）

position_str=  entrust_no
*/

int  TTrdItf_HS::QryDetail()
{
  int reqry_num=0;

HH:

  if(FRequest.QryDetail.ContractID[0]==0) return -1;
  
	FItf->SetHead(FHSSet.branch_no,401);
  if(FHSSet.is_gtja)
  {
        FItf->SetRange(13,1);
        FItf->SetRange(13,1);
  }
  else
  {
        FItf->SetRange(15,1);
        FItf->SetRange(15,1);
  }

	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("exchange_type").c_bstr());
	FItf->AddField(WideString("stock_account").c_bstr());
	FItf->AddField(WideString("stock_code").c_bstr());
	FItf->AddField(WideString("query_direction").c_bstr());
	FItf->AddField(WideString("request_num").c_bstr());
    FItf->AddField(WideString("position_str").c_bstr());

  if(FHSSet.is_gtja)
  {
  }
  else
  {
	  FItf->AddField(WideString("sort_direction").c_bstr());
  	FItf->AddField(WideString("locate_entrust_no").c_bstr());
  }

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString((FRequest.QryDetail.Bourse==bsSH ? FAccInfo.SH : FAccInfo.SZ)).c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString((char)qdahead).c_bstr());
	FItf->AddValue(WideString("1").c_bstr());

  if(FHSSet.is_gtja)
  {
    long id=atoi(FRequest.QryDetail.ContractID)-1;
    FItf->AddValue(WideString(IntToStr(id)).c_bstr());
  }
  else
  {
    FItf->AddValue(WideString("").c_bstr());
	  FItf->AddValue(WideString("0").c_bstr());
	  FItf->AddValue(WideString(FRequest.QryDetail.ContractID).c_bstr());
  }

	if(FItf->Send()!=0) return ERR_SEND_FAULT;

	FItf->FreePack();

	if(FItf->Receive()!=0) return ERR_RECV_FAULT;
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); return FItf->ErrorNo; }
	if(FItf->RecordCount==1)
	{
    //ODS(String(FItf->FieldByName(WideString("entrust_no"))).c_str());
		if(lstrcmp(String(FItf->FieldByName(WideString("entrust_no"))).c_str(),FRequest.QryDetail.ContractID)==0)
		{
			NewAns(1);
			(*FAnswer)[0].QryDetail.Price=StrToFloatDef(String(FItf->FieldByName(WideString("business_price"))),-1);
			(*FAnswer)[0].QryDetail.Num=StrToIntDef(String(FItf->FieldByName(WideString("business_amount"))),-1);
			int ordnum=StrToIntDef(String(FItf->FieldByName(WideString("entrust_amount"))),-1);

			if((*FAnswer)[0].QryDetail.Price<0 || (*FAnswer)[0].QryDetail.Num<0 ||
				ordnum<0)
				return ERR_OTHERS;

			String et=FItf->FieldByName(WideString("entrust_status"));
			if(et.Length()==1)
			{
        (*FAnswer)[0].QryDetail.UndoNum=0;

        if(
                   et[1]==(char)esyc1  ||
                   et[1]==(char)esyf   ||
                   (et[1]==(char)esbc  && (*FAnswer)[0].QryDetail.Num>0 )
          )
				{
          if(et[1]==(char)esbc && ++reqry_num < 3 ) //如果是部撤则再查直到 reqry_num >3
          {
            Sleep(100);
            goto HH;
          }
          //必须为一个负数
          (*FAnswer)[0].QryDetail.UndoNum=(*FAnswer)[0].QryDetail.Num-ordnum;
				}

        //if((*FAnswer)[0].QryDetail.Price<0.001) (*FAnswer)[0].QryDetail.Num=0;

				return 0;
			}

			return ERR_OTHERS;
		}
		else return -1;
	}
	else return ERR_NO_ACK;
}

int  TTrdItf_HS::QryHisDetail()
{
	return ERR_UNIMPLEMENTED;
}

int  TTrdItf_HS::QryCsn()
{
	return ERR_UNIMPLEMENTED;
}

int  TTrdItf_HS::QryCurCsn()
{
	String date = Now().FormatString("YYYYMMDD");
	TList * Ans=new TList();
	int ret=0;
	String posstr="";
BB:
	FItf->SetHead(FHSSet.branch_no,401);
	FItf->SetRange(15,1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("exchange_type").c_bstr());
	FItf->AddField(WideString("stock_account").c_bstr());
	FItf->AddField(WideString("stock_code").c_bstr());
	FItf->AddField(WideString("query_direction").c_bstr());
	FItf->AddField(WideString("request_num").c_bstr());
	FItf->AddField(WideString("position_str").c_bstr());
	FItf->AddField(WideString("sort_direction").c_bstr());
	FItf->AddField(WideString("locate_entrust_no").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString(" ").c_bstr());
	FItf->AddValue(WideString(" ").c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString((char)qdahead).c_bstr());
	FItf->AddValue(WideString("0").c_bstr());
	FItf->AddValue(WideString(posstr).c_bstr());
	FItf->AddValue(WideString("0").c_bstr());
	FItf->AddValue(WideString(" ").c_bstr());

	if(FItf->Send()!=0) {ret= ERR_SEND_FAULT; goto HH;}

	FItf->FreePack();

	if(FItf->Receive()!=0) {ret= ERR_RECV_FAULT; goto HH;}
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); ret= FItf->ErrorNo;goto HH; }

	if(FItf->RecordCount<1) goto HH;

	for (int i = 0; i < FItf->RecordCount; i++)
	{
		TConsignInfo *ci = new TConsignInfo;
    ZeroMemory(ci,sizeof( TConsignInfo));
		Ans->Add(ci);

		posstr=String(FItf->FieldByName(WideString("position_str")));
		lstrcpy(ci->ContractID, String(FItf->FieldByName(WideString("entrust_no"))).c_str());
		lstrcpy(ci->SecuID, String(FItf->FieldByName(WideString("stock_code"))).c_str());
		lstrcpy(ci->SecuDesc, String(FItf->FieldByName(WideString("stock_name"))).c_str());
		lstrcpy(ci->Time, String(FItf->FieldByName(WideString("report_time"))).c_str());

    //2004/12/13
		//lstrcpy(ci->Date, String(FItf->FieldByName(WideString("entrust_date"))).c_str());
    String tmp;

    //if(!FHSSet.is_gtja)
    {
      tmp = String(FItf->FieldByName(WideString("entrust_bs")));
      if (tmp.Length() > 0)
      {
        ci->Type =ConvertType(tmp.c_str());
      }
      else
      {
        ci->Type =btNo;
      }
    }
    //else
    {
    //  ci->Type=btNo;
    }

		tmp = String(FItf->FieldByName(WideString("entrust_status")));
		if (tmp.Length() > 0)
			ci->State = ConvertState(tmp.c_str());
		else
		{
			ci->State = wsno;
		}

    ci->CsnVol = StrToIntDef(FItf->FieldByName(WideString("entrust_amount")), -1);
		ci->CsnPrice = StrToFloatDef(FItf->FieldByName(WideString("entrust_price")), -1);

		ci->TrdVol = StrToIntDef(FItf->FieldByName(WideString("business_amount")), -1);
		ci->TrdPrice = StrToFloatDef(FItf->FieldByName(WideString("business_price")), -1);

    if(
              tmp[1]==(char)esyc1  ||
              tmp[1]==(char)esyf   ||
              (tmp[1]==(char)esbc  && ci->TrdVol >0)
      )
    {
        //必须为一个负数
        ci->CancelVol=ci->TrdVol - ci->CsnVol;
    }

		FItf->MoveBy(1);
	}

	if(ret ==0) goto BB;

HH:
	if(ret==0 && Ans->Count>0)
	{
		NewAns(Ans->Count);
		for(int i=0;i<Ans->Count;i++)
		{
			TConsignInfo *ci = (TConsignInfo *)Ans->Items[i];
			memcpy(&(*FAnswer)[i].QryCurCsn.CsgInfo,ci,sizeof(TConsignInfo));
		}
	}

	for(int i=0;i<Ans->Count;i++)
	{
		TConsignInfo *ci = (TConsignInfo *)Ans->Items[i];
		delete ci;
	}
	Ans->Clear();
	delete Ans;

	return ret;
}

/*
交易功能: 查询历史委托
功能编号: 421
版本编号: 1.00
请求:
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH> branch_no<SOH>fund_account<SOH> password<SOH>
exchange_type<SOH>stock_account<SOH>stock_code<SOH>query_direction<SOH>
request_num<SOH>position_str<SOH>start_date<SOH>end_date<SOH>

应答:
error_no<SOH>error_info<SOH>
position_str<SOH>entrust_no<SOH>exchange_type<SOH>stock_account<SOH>
stock_code<SOH>stock_name<SOH>entrust_bs<SOH>entrust_price<SOH>
entrust_amount<SOH>business_amount<SOH>business_price<SOH>report_no<SOH>
entrust_date<SOH>entrust_time<SOH>report_time<SOH>entrust_type<SOH>
entrust_status<SOH>status_name<SOH>cancel_info<SOH> position_str<SOH>

请求注释:
exchange_type：如果不为空格，查确定的，为空，查所有。
stock_code：如果为空格，查所有，不为空，查确定的，此时exchange_type必须不为空
query_direction：查询方向 暂时只支持'1'顺序

应答注释：
错误号:
-52："无此股票"        （此错误可不作判断）
-60："没有委托记录"
-61："查询失败"        （其他错误）
*/

int  TTrdItf_HS::QryHisCsn()
{
	TList * Ans=new TList();
	int ret=0;
	String posstr="";
BB:
	FItf->SetHead(FHSSet.op_branch_no, 421);
	FItf->SetRange(15, 1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("exchange_type").c_bstr());
	FItf->AddField(WideString("stock_account").c_bstr());
	FItf->AddField(WideString("stock_code").c_bstr());
	FItf->AddField(WideString("query_direction").c_bstr());
	FItf->AddField(WideString("request_num").c_bstr());
	FItf->AddField(WideString("position_str").c_bstr());
	FItf->AddField(WideString("start_date").c_bstr());
	FItf->AddField(WideString("end_date").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());

	FItf->AddValue(WideString(" ").c_bstr());
	FItf->AddValue(WideString(" ").c_bstr());
	FItf->AddValue(WideString(" ").c_bstr());
	FItf->AddValue(WideString(qdahead).c_bstr());
	FItf->AddValue(WideString(" ").c_bstr());
	FItf->AddValue(WideString(posstr).c_bstr());
	FItf->AddValue(WideString(FRequest.QryHisCsn.StartDay).c_bstr());
	FItf->AddValue(WideString(FRequest.QryHisCsn.EndDay).c_bstr());

	if(FItf->Send()!=0) {ret= ERR_SEND_FAULT; goto HH;}

	FItf->FreePack();

	if(FItf->Receive()!=0) {ret= ERR_RECV_FAULT; goto HH;}
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); ret= FItf->ErrorNo;goto HH; }
	if(FItf->RecordCount<1) goto HH;
	for (int i = 0; i < FItf->RecordCount; i++)
	{
    String s=FItf->get_Buffer();
		TConsignInfo *ci = new TConsignInfo;
    ZeroMemory(ci,sizeof(TConsignInfo));
		Ans->Add(ci);

		posstr=String(FItf->FieldByName(WideString("position_str")));
		lstrcpy(ci->ContractID, String(FItf->FieldByName(WideString("entrust_no"))).c_str());
		lstrcpy(ci->SecuID, String(FItf->FieldByName(WideString("stock_code"))).c_str());
		lstrcpy(ci->SecuDesc, String(FItf->FieldByName(WideString("stock_name"))).c_str());
		lstrcpy(ci->Time, String(FItf->FieldByName(WideString("entrust_time"))).c_str());
        //2004/12/13
		//lstrcpy(ci->Date, String(FItf->FieldByName(WideString("entrust_date"))).c_str());
    String tmp;

		//if(FHSSet.is_gtja)
    //{

      tmp = String(FItf->FieldByName(WideString("entrust_bs")));
      if (tmp.Length() > 0)
      {
        ci->Type =ConvertType(tmp.c_str());
      }
      else
      {
        ci->Type =btNo;
      }
    //}
    //else
    //{
    //  ci->Type=btNo;
    //}

		tmp = String(FItf->FieldByName(WideString("entrust_status")));
		if (tmp.Length() > 0)
			ci->State = ConvertState(tmp.c_str());
		else {ci->State=wsno;};

		ci->CsnVol = StrToIntDef(FItf->FieldByName(WideString("entrust_amount")), -1);
		ci->CsnPrice = StrToFloatDef(FItf->FieldByName(WideString("entrust_price")), -1);

		ci->TrdVol = StrToIntDef(FItf->FieldByName(WideString("business_amount")), -1);
		ci->TrdPrice = StrToFloatDef(FItf->FieldByName(WideString("business_price")), -1);

		FItf->MoveBy(1);
	}

	if(ret ==0) goto BB;

HH:
	if(ret==0 && Ans->Count>0)
	{
		NewAns(Ans->Count);
		for(int i=0;i<Ans->Count;i++)
		{
			TConsignInfo *ci = (TConsignInfo *)Ans->Items[i];
			memcpy(&(*FAnswer)[i].QryHisCsn.CsgInfo,ci,sizeof(TConsignInfo));
		}
	}

	for(int i=0;i<Ans->Count;i++)
	{
		TConsignInfo *ci = (TConsignInfo *)Ans->Items[i];
		delete ci;
	}
	Ans->Clear();
	delete Ans;

	return ret;
}

int  TTrdItf_HS::QryCurTrd()
{
	String date = Now().FormatString("YYYYMMDD");

	TList * Ans=new TList();
	int ret=0;
	String posstr="";
BB:
	FItf->SetHead(FHSSet.branch_no,402);
	FItf->SetRange(15,1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("serial_no").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("exchange_type").c_bstr());
	FItf->AddField(WideString("stock_account").c_bstr());
	FItf->AddField(WideString("stock_code").c_bstr());
	FItf->AddField(WideString("query_direction").c_bstr());
	FItf->AddField(WideString("request_num").c_bstr());
	FItf->AddField(WideString("query_mode").c_bstr());
	FItf->AddField(WideString("position_str").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString("0").c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString((char)qdahead).c_bstr());
	FItf->AddValue(WideString("0").c_bstr());
	FItf->AddValue(WideString("0").c_bstr());
	FItf->AddValue(WideString(posstr).c_bstr());

	if(FItf->Send()!=0) {ret= ERR_SEND_FAULT; goto HH;}

	FItf->FreePack();

	if(FItf->Receive()!=0) {ret= ERR_RECV_FAULT; goto HH;}
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); ret= FItf->ErrorNo;goto HH; }
	if(FItf->RecordCount<1) goto HH;
	for(int i=0;i<FItf->RecordCount;i++)
	{
		TTradeInfo *ti = new TTradeInfo;
    ZeroMemory(ti,sizeof(TTradeInfo));
		Ans->Add(ti);

		posstr=String(FItf->FieldByName(WideString("position_str")));

		lstrcpy(ti->SecuID, String(FItf->FieldByName(WideString("stock_code"))).c_str());
		lstrcpy(ti->SecuDesc, String(FItf->FieldByName(WideString("stock_name"))).c_str());
		lstrcpy(ti->Time, String(FItf->FieldByName(WideString("business_time"))).c_str());
		//lstrcpy(ti->Date, String(FItf->FieldByName(WideString("business_date"))).c_str());

		String tmp=String(FItf->FieldByName(WideString("entrust_bs")));
		if(tmp.Length()>0)
			ti->Type=ConvertType(tmp.c_str());
		else {
			ti->Type=btNo;
		}

    if( String(FItf->FieldByName(WideString("entrust_type")))=="2" ) //撤单
		  ti->Vol = -StrToIntDef(FItf->FieldByName(WideString("business_amount")), -1);
    else
      ti->Vol = StrToIntDef(FItf->FieldByName(WideString("business_amount")), -1);

		ti->Price = StrToFloatDef(FItf->FieldByName(WideString("business_price")), -1);
		FItf->MoveBy(1);
	}
	if(ret ==0) goto BB;

HH:
	if(ret==0 && Ans->Count>0)
	{
		NewAns(Ans->Count);
		for(int i=0;i<Ans->Count;i++)
		{
			TTradeInfo *ci = (TTradeInfo *)Ans->Items[i];
			memcpy(&(*FAnswer)[i].QryCurTrd.TrdInfo,ci,sizeof(TTradeInfo));
		}
	}

	for(int i=0;i<Ans->Count;i++)
	{
		TTradeInfo *ci = (TTradeInfo *)Ans->Items[i];
		delete ci;
	}
	Ans->Clear();
	delete Ans;

	return ret;
}

/*
交易功能: 查询历史成交
功能编号: 411
版本编号: 1.00
请求:
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH> branch_no<SOH>fund_account<SOH> password<SOH>
start_date<SOH>end_date<SOH>
exchange_type<SOH>stock_account<SOH>stock_code<SOH>query_direction<SOH>
request_num<SOH>position_str<SOH>

应答:
error_no<SOH>error_info<SOH>date<SOH>serial_no<SOH>
position_str<SOH>exchange_type<SOH>stock_account<SOH>
stock_code<SOH>stock_name<SOH>entrust_bs<SOH>business_price<SOH>
occur_amount<SOH>business_time<SOH>business_status<SOH>
business_times<SOH>remark<SOH>entrust_no<SOH>report_no<SOH>

请求注释:
应答注释：

错误号：
-52："无此股票"      （此错误可不作判断）
-60："没有成交记录"
-61："查询失败"      （其他错误）

*/

int  TTrdItf_HS::QryHisTrd()
{
	TList * Ans=new TList();
	int ret=0;
	String posstr="";
BB:
	FItf->SetHead(FHSSet.op_branch_no, 411);
	FItf->SetRange(15, 1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("start_date").c_bstr());
	FItf->AddField(WideString("end_date").c_bstr());
	FItf->AddField(WideString("exchange_type").c_bstr());
	FItf->AddField(WideString("stock_account").c_bstr());
	FItf->AddField(WideString("stock_code").c_bstr());
	FItf->AddField(WideString("query_direction").c_bstr());
	FItf->AddField(WideString("request_num").c_bstr());
	FItf->AddField(WideString("position_str").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString(FRequest.QryHisTrd.StartDay).c_bstr());
	FItf->AddValue(WideString(FRequest.QryHisTrd.EndDay).c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString((char)qdahead).c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString(posstr).c_bstr());

	if(FItf->Send()!=0) {ret= ERR_SEND_FAULT; goto HH;}

	FItf->FreePack();

	if(FItf->Receive()!=0) {ret= ERR_RECV_FAULT; goto HH;}
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); ret= FItf->ErrorNo;goto HH; }
	if(FItf->RecordCount<1) goto HH;

	for (int i = 0; i < FItf->RecordCount; i++)
	{
		TTradeInfo *ti = new TTradeInfo;
    ZeroMemory(ti,sizeof(TTradeInfo));
		Ans->Add(ti);

		posstr=String(FItf->FieldByName(WideString("position_str")));

		lstrcpy(ti->SecuID, String(FItf->FieldByName(WideString("stock_code"))).c_str());
		lstrcpy(ti->SecuDesc, String(FItf->FieldByName(WideString("stock_name"))).c_str());
		lstrcpy(ti->Time, String(FItf->FieldByName(WideString("business_time"))).c_str());
		//lstrcpy(ti->Date, String(FItf->FieldByName(WideString("business_date"))).c_str());

		String tmp=String(FItf->FieldByName(WideString("entrust_bs")));
		if(tmp.Length()>0)
			ti->Type=ConvertType(tmp.c_str());
		else
		{
			ti->Type=btNo;
		}
		ti->Vol = StrToIntDef(FItf->FieldByName(WideString("occur_amount")), -1);
		ti->Price = StrToFloatDef(FItf->FieldByName(WideString("business_price")), -1);
		FItf->MoveBy(1);
	}
	if(ret ==0) goto BB;

HH:
	if(ret==0 && Ans->Count>0)
	{
		NewAns(Ans->Count);
		for(int i=0;i<Ans->Count;i++)
		{
			TTradeInfo  *ti = (TTradeInfo  *)Ans->Items[i];
			memcpy(&(*FAnswer)[i].QryHisTrd.TrdInfo,ti,sizeof(TTradeInfo));
		}
	}

	for(int i=0;i<Ans->Count;i++)
	{
		TTradeInfo *ti = (TTradeInfo *)Ans->Items[i];
		delete ti;
	}
	Ans->Clear();
	delete Ans;

	return ret;
}

/*
交易功能: 查询历史流水
功能编号: 412
版本编号: 1.00
请求:
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH> branch_no<SOH>fund_account<SOH> password<SOH>
money_type<SOH>start_date<SOH>end_date<SOH> query_direction<SOH>
request_num<SOH>position_str<SOH>
应答:
error_no<SOH>error_info<SOH>
position_str<SOH>serial_no<SOH>business_date<SOH>
business_flag<SOH>business_name<SOH>occur_balance<SOH>post_balance<SOH>
exchange_type<SOH>stock_account<SOH>stock_code<SOH>stock_name<SOH>
entrust_bs<SOH>business_price<SOH>occur_amount<SOH>remark<SOH>
money_type<SOH>

请求注释:
应答注释：
错误号：
-60："没有资金流水"
-61："查询失败"           （其他错误）
*/

int  TTrdItf_HS::QryBill()
{
	TList * Ans=new TList();
	int ret=0;
	String posstr="";
BB:
    if(FRequest.QryBill.StartDay[0]==0 || FRequest.QryBill.EndDay[0]==0)
    {
        //查询当日委托
    }
    else
    {
        FItf->SetHead(FHSSet.op_branch_no, 412);
        FItf->SetRange(13, 1);
        FItf->AddField(WideString("version").c_bstr());
        FItf->AddField(WideString("op_branch_no").c_bstr());
        FItf->AddField(WideString("op_station").c_bstr());
        FItf->AddField(WideString("op_entrust_way").c_bstr());
        FItf->AddField(WideString("branch_no").c_bstr());
        FItf->AddField(WideString("fund_account").c_bstr());
        FItf->AddField(WideString("password").c_bstr());
        FItf->AddField(WideString("money_type").c_bstr());
        FItf->AddField(WideString("start_date").c_bstr());
        FItf->AddField(WideString("end_date").c_bstr());
        FItf->AddField(WideString("query_direction").c_bstr());
        FItf->AddField(WideString("request_num").c_bstr());
        FItf->AddField(WideString("position_str").c_bstr());

        FItf->AddValue(WideString(HS_VERSION).c_bstr());
        FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
        FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
        FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
        FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
        FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
        FItf->AddValue(WideString(FAccInfo.PW).c_bstr());

        FItf->AddValue(WideString((char)mtrmb).c_bstr());
        FItf->AddValue(WideString(FRequest.QryBill.StartDay).c_bstr());
        FItf->AddValue(WideString(FRequest.QryBill.EndDay).c_bstr());
        FItf->AddValue(WideString("").c_bstr());
        FItf->AddValue(WideString("").c_bstr());
        FItf->AddValue(WideString(posstr).c_bstr());
    }
	if(FItf->Send()!=0) {ret= ERR_SEND_FAULT; goto HH;}

	FItf->FreePack();

	if(FItf->Receive()!=0) {ret= ERR_RECV_FAULT; goto HH;}
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); ret= FItf->ErrorNo;goto HH; }
	if(FItf->RecordCount<1) goto HH;

	for (int i = 0; i < FItf->RecordCount; i++)
	{
		TFundInfo *fi = new TFundInfo;
    ZeroMemory(fi,sizeof(TFundInfo));
		Ans->Add(fi);
		posstr=String(FItf->FieldByName(WideString("position_str")));
		//lstrcpy(fi->Date , String(FItf->FieldByName(WideString("business_date"))).c_str());
		lstrcpy(fi->SecuID,String(FItf->FieldByName(WideString("stock_code"))).c_str());
		lstrcpy(fi->SecuDesc ,String(FItf->FieldByName(WideString("stock_name"))).c_str());
		lstrcpy(fi->Type,String(FItf->FieldByName(WideString("entrust_bs"))).c_str());
		fi->Vol    =StrToIntDef(FItf->FieldByName(WideString("occur_amount")), -1);
		fi->Price  =StrToFloatDef(FItf->FieldByName(WideString("business_price")), -1);
		fi->TrdMny =StrToFloatDef(FItf->FieldByName(WideString("occur_balance")), -1);
		fi->Balance=StrToFloatDef(FItf->FieldByName(WideString("post_balance")), -1);
	}

	if(ret ==0) goto BB;

HH:
	if(ret==0 && Ans->Count>0)
	{
		NewAns(Ans->Count);
		for(int i=0;i<Ans->Count;i++)
		{
			TFundInfo *ci = (TFundInfo *)Ans->Items[i];
			memcpy(&(*FAnswer)[i].QryBill.FundInfo,ci,sizeof(TFundInfo));
		}
	}

	for(int i=0;i<Ans->Count;i++)
	{
		TFundInfo *ci = (TFundInfo *)Ans->Items[i];
		delete ci;
	}
	Ans->Clear();
	delete Ans;

	return ret;
}

/*
交易功能: 查询股票
功能编号： 403
版本编号: 1.00
请求:
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH>branch_no<SOH>fund_account<SOH>password<SOH>
exchange_type<SOH>stock_account<SOH>stock_code<SOH>
query_direction<SOH>request_num<SOH>position_str<SOH>query_mode<SOH>

应答:
error_no<SOH>error_infoSOH>
position_str<SOH>exchange_type<SOH>stock_account<SOH>stock_code<SOH>stock_name<SOH>
current_amount<SOH>enable_amount<SOH>last_price<SOH>cost_price<SOH>
income_balance<SOH>hand_flag<SOH>market_value<SOH>

请求注释:
exchange_type：不为空，查确定的，为空，查所有。
stock_code：为空，查所有，不为空，查确定的，此时exchange_type必须不为空。
position_str：exchange_type+stock_code+stock_account总长度为17个字节。
query_mode：'0'：明细 '1'：汇总。

应答注释:
market_value：在明细下为每个股东帐号的市值，而在汇总下则为fund_account的，汇总下无stock_account。
hand_flag: '0'--股   '1' -- 手。
错误号：
-52："无此股票"              （此错误可不作判断）
-60："没有股票记录"
-61："查询失败"              （其他错误）

*/
int  TTrdItf_HS::QryStocks()
{
	TList * Ans=new TList();
	int ret=0;
	String posstr="";

	TStockInfo *si;
	int n;
	t_exchange_type et;

    char tstr[8];
BB:
	FItf->SetHead(FHSSet.branch_no,403);
	FItf->SetRange(14,1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("exchange_type").c_bstr());
	FItf->AddField(WideString("stock_account").c_bstr());
	FItf->AddField(WideString("stock_code").c_bstr());
	FItf->AddField(WideString("query_direction").c_bstr());
	FItf->AddField(WideString("request_num").c_bstr());
	FItf->AddField(WideString("position_str").c_bstr());
	FItf->AddField(WideString("query_mode").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
    //modify by codehunter 2004-12-8
    //char p= (char)TBourse2t_exchange_type(FRequest.QryStocks.Bourse)  ;
    //FItf->AddValue(WideString((char)etsh).c_bstr());
    //FRequest.QryStocks.Bourse=bsSH;
	FItf->AddValue(WideString((char)TBourse2t_exchange_type(FRequest.QryStocks.Bourse)).c_bstr());
	FItf->AddValue(WideString((FRequest.QryStocks.Bourse==bsSH ? FAccInfo.SH : FAccInfo.SZ)).c_bstr());
	FItf->AddValue(WideString("").c_bstr());
	FItf->AddValue(WideString((char)qdahead).c_bstr());
	FItf->AddValue(WideString("1000").c_bstr());
	FItf->AddValue(WideString(posstr).c_bstr());
	FItf->AddValue(WideString("0").c_bstr());

	if(FItf->Send()!=0) {ret= ERR_SEND_FAULT; goto HH;}

	FItf->FreePack();

	if(FItf->Receive()!=0) {ret= ERR_RECV_FAULT; goto HH;}
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); ret= FItf->ErrorNo;goto HH; }
	if(FItf->RecordCount<1) goto HH;
	while(FItf->EOF_==0)
	{
		si=new TStockInfo;
    ZeroMemory(si,sizeof(TStockInfo));
		Ans->Add(si);
		posstr=String(FItf->FieldByName(WideString("position_str")));
		n=String(FItf->FieldByName(WideString("hand_flag"))).ToIntDef(0)==0 ? 1 : 100;
    //ODS(String(FItf->FieldByName(WideString("exchange_type"))).c_str());
    //ODS(si->SecuID,String(FItf->FieldByName(WideString("stock_code"))).c_str());
		//ODS(si->SecuDesc,String(FItf->FieldByName(WideString("stock_name"))).c_str());
		et=(t_exchange_type)String(FItf->FieldByName(WideString("exchange_type"))).c_str()[0];
		//两个市场的股票
		if(et==etsh) si->SecuID[0]='H';
		else if(et==etsz) si->SecuID[0]='S';
		else
		{
			FItf->MoveBy(1);
			continue;   //其余的不要
		}

    si->SecuID[1]=0;

    lstrcpyn(tstr,String(FItf->FieldByName(WideString("stock_code"))).c_str(),7);
		lstrcat(si->SecuID,tstr);
		lstrcpyn(si->SecuDesc,String(FItf->FieldByName(WideString("stock_account"))).c_str(),11);
		si->Balance=String(FItf->FieldByName(WideString("current_amount"))).ToIntDef(-1) * n;
		si->Available=String(FItf->FieldByName(WideString("enable_amount"))).ToIntDef(-1) * n;
		si->BuyFreeze=0 ;
		si->SellFreeze=0 ;
		si->AbnorFreeze=0 ;
		si->CostPrice=StrToFloatDef(FItf->FieldByName(WideString("cost_price")),-1) ;
		si->Cost=si->Balance*si->CostPrice;
		si->CurPrice=StrToFloatDef(FItf->FieldByName(WideString("last_price")),-1) ;
		si->CurVal=si->Balance * si->CurPrice;
		si->ProfitAndLoss=StrToFloatDef(FItf->FieldByName(WideString("income_balance")),-1) ;
		FItf->MoveBy(1);
	}
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
交易功能: 委托确认
功能编号： 302
版本编号: 1.00
请求:
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH> branch_no<SOH>fund_account<SOH> password<SOH>
stock_account<SOH>entrust_bs<SOH>exchange_type<SOH>stock_code<SOH>
entrust_price<SOH>entrsut_amount<SOH>bank_no<SOH>client_rights<SOH>
应答: 
error_no<SOH>error_info<SOH>
entrust_no<SOH>
请求注释: 
fund_account: 必须输入。
stock_account: 必须输入交易的股东代码，不支持内码。
exchange_type: 必须输入确定的市场，不支持'0'或空格。
stock_code: 必须输入确定的股票代码，不支持内码。
bank_no:用于区别是普通委托还是680委托，普通委托为'0'，680委托为相应的银行号。
client_rights：此参数可以不输入，如果输入，必须是200请求中系统返回的client_righs。
bank_no、client_rights暂不使用。
应答注释: 
entrust_no:一般为委托编号

错误号：
-52："此股票不存在"
-51："未登记该交易所帐号"
-64:"此股不能进行此类委托"
-66："帐户状态不正常"
-67："您未作指定交易"
-57："可用金额不足"
-58："股票余额不足"
-55："数量不符合交易所规定"
-56："委托价格不符合交易所规定"
-59："闭市时间不能委托"
-65："此股票停牌，不能委托"    （如果停牌允许委托，不报错误）
-61："委托失败"                （其他错误）

*/
int  TTrdItf_HS::Buy()
{
	char et;

	if(FRequest.Buy.SecuID[0]=='H')
	{
		et=etsh;
	}
	else if(FRequest.Buy.SecuID[0]=='S')
		et=etsz;
    else if(FRequest.Buy.SecuID[0]=='P')
        et=etsh;
	else
		et=etqt;

	FItf->SetHead(FHSSet.branch_no,302);
	FItf->SetRange(16,1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("stock_account").c_bstr());
	FItf->AddField(WideString("entrust_bs").c_bstr());
	FItf->AddField(WideString("exchange_type").c_bstr());
	FItf->AddField(WideString("stock_code").c_bstr());
	FItf->AddField(WideString("entrust_price").c_bstr());
	FItf->AddField(WideString("entrust_amount").c_bstr());
	FItf->AddField(WideString("bank_no").c_bstr());
	FItf->AddField(WideString("client_rights").c_bstr());
    FItf->AddField(WideString("entrust_prop").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no)).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no)).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString((et==etsh ? FAccInfo.SH : FAccInfo.SZ )).c_bstr());
	FItf->AddValue(WideString((char)ebbuy).c_bstr());
	FItf->AddValue(WideString(et).c_bstr());
	FItf->AddValue(WideString((FRequest.Buy.SecuID+1)).c_bstr());
	FItf->AddValue(WideString(FormatFloat("0.000",FRequest.Buy.Price)).c_bstr());
	FItf->AddValue(WideString(IntToStr(FRequest.Buy.Num)).c_bstr());
	FItf->AddValue(WideString("0").c_bstr());
	FItf->AddValue(WideString("").c_bstr());    //不输入

    if( FRequest.Buy.Type == '1' )
        FItf->AddValue(WideString("N").c_bstr());    //申购或者赎回
    else
        FItf->AddValue(WideString("0").c_bstr());    //买卖

	if(FItf->Send()!=0) return ERR_SEND_FAULT;

	FItf->FreePack();

	if(FItf->Receive()!=0) return ERR_RECV_FAULT;

	if(FItf->ErrorNo!=0)
	{
		ODS(String(FItf->ErrorMsg).c_str());
		return FItf->ErrorNo;
	}
	String id;
	if(FItf->RecordCount>0)
	{
		id=String(FItf->FieldByName(WideString("entrust_no")));
		if(id.Length()>0)
		{
			NewAns(1);
			strcpy((*FAnswer)[0].Buy.ContractID,id.c_str());
			return 0;
		}
		else
			return String(FItf->FieldByName(WideString("error_no"))).ToIntDef(ERR_OTHERS);
	}
	else return ERR_NO_ACK;
}

int  TTrdItf_HS::Sell()
{
	char et;

	if(FRequest.Buy.SecuID[0]=='H')
	{
		et=etsh;
	}
	else if(FRequest.Buy.SecuID[0]=='S')
		et=etsz;
    else if(FRequest.Buy.SecuID[0]=='P')
        et=etsh;
	else
		et=etqt;

	FItf->SetHead(FHSSet.branch_no,302);
	FItf->SetRange(16,1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("stock_account").c_bstr());
	FItf->AddField(WideString("entrust_bs").c_bstr());
	FItf->AddField(WideString("exchange_type").c_bstr());
	FItf->AddField(WideString("stock_code").c_bstr());
	FItf->AddField(WideString("entrust_price").c_bstr());
	FItf->AddField(WideString("entrust_amount").c_bstr());
	FItf->AddField(WideString("bank_no").c_bstr());
	FItf->AddField(WideString("client_rights").c_bstr());
    FItf->AddField(WideString("entrust_prop").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString((et==etsh ? FAccInfo.SH : FAccInfo.SZ )).c_bstr());
	FItf->AddValue(WideString((char)ebsell).c_bstr());
	FItf->AddValue(WideString(et).c_bstr());
	FItf->AddValue(WideString((FRequest.Sell.SecuID+1)).c_bstr());
	FItf->AddValue(WideString(FormatFloat("0.000",FRequest.Sell.Price).c_str()).c_bstr());
	FItf->AddValue(WideString(IntToStr(FRequest.Sell.Num).c_str()).c_bstr());
	FItf->AddValue(WideString("0").c_bstr());
	FItf->AddValue(WideString("").c_bstr());

    if( FRequest.Buy.Type == '1' )
        FItf->AddValue(WideString("N").c_bstr());    //申购或者赎回
    else
        FItf->AddValue(WideString("0").c_bstr());    //买卖

	if(FItf->Send()!=0) return ERR_SEND_FAULT;

	FItf->FreePack();

	if(FItf->Receive()!=0) return ERR_RECV_FAULT;
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); return FItf->ErrorNo; }
	String id;
	if(FItf->RecordCount>0)
	{
		id=String(FItf->FieldByName(WideString("entrust_no")));
		if(id.Length()>0)
		{
			NewAns(1);
			strcpy((*FAnswer)[0].Sell.ContractID,id.c_str());
			return 0;
		}
		else
			return String(FItf->FieldByName(WideString("error_no"))).ToIntDef(ERR_OTHERS);
	}
	else return ERR_NO_ACK;
}
/*
交易功能: 委托撤单
功能编号： 304
版本编号: 1.00
请求: 
version<SOH>op_branch_no<SOH>op_station<SOH>
op_entrust_way<SOH> branch_no<SOH>fund_account<SOH>password<SOH>
entrust_no<SOH>batch_flag<SOH>
应答: 
error_no<SOH>error_info<SOH>
entrust_no<SOH>
请求注释:
entrust_no：使用批量撤单标志batch_flag为'1'，则将理解为批号，其它为委托编号。
应答注释：

错误号: -53:"无此委托"            （包含此委托不是该股民的）
-54:"此委托不能撤单"      （包含其他错误）

*/
int  TTrdItf_HS::Undo()
{
	FItf->SetHead(FHSSet.branch_no,304);
	FItf->SetRange(9,1);
	FItf->AddField(WideString("version").c_bstr());
	FItf->AddField(WideString("op_branch_no").c_bstr());
	FItf->AddField(WideString("op_station").c_bstr());
	FItf->AddField(WideString("op_entrust_way").c_bstr());
	FItf->AddField(WideString("branch_no").c_bstr());
	FItf->AddField(WideString("fund_account").c_bstr());
	FItf->AddField(WideString("password").c_bstr());
	FItf->AddField(WideString("entrust_no").c_bstr());
	FItf->AddField(WideString("batch_flag").c_bstr());

	FItf->AddValue(WideString(HS_VERSION).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.op_branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_station).c_bstr());
	FItf->AddValue(WideString(FHSSet.op_entrust_way).c_bstr());
	FItf->AddValue(WideString(IntToStr(FHSSet.branch_no).c_str()).c_bstr());
	FItf->AddValue(WideString(FAccInfo.Capital).c_bstr());
	FItf->AddValue(WideString(FAccInfo.PW).c_bstr());
	FItf->AddValue(WideString(FRequest.Undo.ContractID).c_bstr());
	FItf->AddValue(WideString("0").c_bstr());

	if(FItf->Send()!=0) return ERR_SEND_FAULT;

	FItf->FreePack();

	if(FItf->Receive()!=0) return ERR_RECV_FAULT;
	if(FItf->ErrorNo!=0){ ODS(String(FItf->ErrorMsg).c_str()); return FItf->ErrorNo; }
	if(FItf->RecordCount>0)
	{
    return 0;
	}
	else return ERR_NO_ACK;
}

TTrdItf_HS::TTrdItf_HS(THSSet *set)
{
	CopyMemory(&FHSSet,set,sizeof(THSSet));
	FItf=new TComm(NULL);
	FItf->CreateX(0);
}

TTrdItf_HS::~TTrdItf_HS()
{
	long i=FItf->get_Connection();
	if(i>=0) FItf->DisConnect();
	FItf->Free();
	delete FItf;
}

bool TTrdItf_HS::RegHsCommX(String PathName)
{
	ShellExecute(NULL,"open","regsvr32.exe",
              String(String("\"") + PathName + String("\"")).c_str(),
              "",
              SW_SHOWNORMAL);
	return true;
}

bool TTrdItf_HS::SetupHsCommX(void)
{
	bool ret=false;
	TComm *cm;
	__try
	{
		cm=new TComm(NULL);
		cm->CreateX(0);
		cm->SetConnect();
		cm->Free();
		ret = true;
	}
	catch(...)
	{
	}
	delete cm;
	return ret;
}
