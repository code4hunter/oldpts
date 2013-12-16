//---------------------------------------------------------------------------
#include "uDatabase.h"
#include <assert.h>
#include <IniFiles.hpp>
#include "UTrdItf_HSFF.h"
#include "OrderKeeper.h"
//---------------------------------------------------------------------------

#define HS_VERSION "111"


class checkinfo_wrapper
{

typedef int __stdcall(*GENCHECKINFO)(int,char*,int);

private:
	HINSTANCE  dllhandle; //动态链接库句柄
	GENCHECKINFO fccheckinfo;
public:
	checkinfo_wrapper()
	{
		dllhandle = NULL;

		dllhandle = LoadLibrary("ModuleCheck.dll");
		if( dllhandle == NULL )
			throw "Can not load ModuleCheck.dll";

		fccheckinfo = (GENCHECKINFO)GetProcAddress(dllhandle,"GenCheckInfo");
		if( fccheckinfo== NULL )
			throw "Can not find function GenCheckInfo";

	}
	~checkinfo_wrapper()
	{
    	if (dllhandle!=NULL) {
			FreeLibrary(dllhandle);
			dllhandle = NULL;
		}
    }

	int GenCheckInfo( int funcno,char*buf,int len )
	{
		assert( fccheckinfo != NULL );
		return fccheckinfo( funcno,buf,len);
    }
};

int TTrdItf_HSFF:: Init()
{
	this->CloseLink();

	assert(_config!=NULL );
	_config->Load(FSetupFile);
	_connection = NewConnection(_config);
	_connection->AddRef();

	int ret = 0;
	if (0 == (ret = _connection->Create(NULL)))
	{
     	if (ret = _connection->Connect(5000))
		{
			SetLastError(-1,'E',PLUGINNAME,"连接失败,%s", _connection->GetErrorMsg(ret));
			return -1;
		}
		else return 0;
	}
	else
	{
		SetLastError(-1,'E',PLUGINNAME,"建立连接失败,%s", _connection->GetErrorMsg(ret));
		return -1;
	}
}

void TTrdItf_HSFF::CloseLink( void )
{
	this->lock();
	try
	{
		if( _connection)
		{
			_connection->Release();
			_connection = NULL;
		}

		_ord_keeper.reset();
		TTrdItfBase::CloseLink();
	}
	__finally
	{
		this->unlock();
	}
}

int TTrdItf_HSFF::SendAndReceive(int funid,IF2Packer *in,IF2UnPacker **out)
{
#ifdef INCLUDECHECKINFO
	if( FHSFFSet. gen_check_info )
	{
		checkinfo_wrapper ck;
		ck.GenCheckInfo(funid,(char*)in->GetPackBuf(),in->GetPackLen());
	}
#endif
	*out = NULL;
	int ret = 0;
	if ((ret = _connection->SendBiz(funid, in)) < 0)
	{
		this->SetLastError(ERR_REMOTE_SEND_FAILED,'E',PLUGINNAME,"发送数据错误,%s",
			_connection->GetErrorMsg(ret));
		return ERR_REMOTE_SEND_FAILED;
	}
	else
	{
		// 默认超时时间为1秒
		ret = _connection->RecvBiz(ret,(void**)out,this->FHSFFSet.TimeOut);

		switch (ret)
		{
		case 0:
			{
				//puts("业务操作成功。");
				//ShowPacket((IF2UnPacker *)Pointer);
				if( *out!= NULL )
				{
					return 0;
				}
				else
				{
					this->SetLastError(-1,'E',PLUGINNAME,"返回结果集为NULL");
					return -1;
				}
			}

		case 1:
			{
				if( (*out)->GetDatasetCount() >0 )
				{
					(*out)->SetCurrentDatasetByIndex(0);
					int err_no = (*out)->GetIntByIndex(0);
					AnsiString err_info =(*out)->GetStr("error_info");
					this->SetLastError(err_no,'E',PLUGINNAME,"柜台返回错误,%d,%s", err_no,err_info.c_str());
					return -abs(err_no);
                    //(*out)->Release();
				}
				else
				{
					this->SetLastError(-1,'E',PLUGINNAME,"返回结果集GetDatasetCount=0");
					return -1;
				}
			}

		case 2:
			{
				ODS("柜台返回字符串,%s", (char *)(*out));
				return -100;
			}

		case 3:
			{
				this->SetLastError(ERR_REMOTE_RECV_FAILED,'E',PLUGINNAME,"解包失败");
				return ERR_REMOTE_RECV_FAILED;
			}

		default:
			{
				this->SetLastError(ERR_TRDSVR_OTHER_FAILED,'E',PLUGINNAME,"柜台其他错误,%s",
					_connection->GetErrorMsg(ret));
				return ERR_TRDSVR_OTHER_FAILED;
			}
		}
	}

	return 0;
}

int TTrdItf_HSFF::SetAccount()
{
	FAccInfo.lt = FRequest.SetAccount.LoginType;
	//FAccount = FRequest.SetAccount.Account;
	lstrcpyn( FAccInfo.PW, FRequest.SetAccount.PW, 13 );

	//获取打包器
	IF2Packer* pack = NewPacker(2);
	pack->AddRef();
	//创建一个业务包
	pack->BeginPack();

	pack->AddField("version");
	//pack->AddField("identity_type");
	pack->AddField("op_branch_no");
	pack->AddField("op_entrust_way");
	pack->AddField("op_station");
	pack->AddField("branch_no");
	pack->AddField("function_id");
	pack->AddField("input_content");
	pack->AddField("password");
	pack->AddField("content_type");
	pack->AddField("account_content");

	pack->AddStr(HS_VERSION);
	pack->AddStr(FHSFFSet.op_branch_no.c_str());
	pack->AddStr(FHSFFSet.op_entrust_way.c_str());
	pack->AddStr(FHSFFSet.op_station.c_str());
	pack->AddStr(FHSFFSet.branch_no.c_str());
	pack->AddStr("200");
	pack->AddStr("1");
	pack->AddStr(FRequest.SetAccount.PW);
	pack->AddStr("");
	pack->AddStr(FRequest.SetAccount.Account);
	pack->EndPack();

	IF2UnPacker *out = NULL;
	int	r	= SendAndReceive(200,pack,&out);

	//free(pack->GetPackBuf());
	pack->Release();

	if ( r < 0 || out == NULL )
	{
		return r;
	}
	else
	{
		try
		{
		if ( out->GetRowCount() > 0 )
		{
			AnsiString	acc	= out->GetStr("fund_account");
			lstrcpyn(FAccInfo.Capital,acc.c_str(),ACC_LEN);
			if( out->GetChar("tabconfirm_flag") == '0' )
			{
				NewAns( 1 );
				memcpy( &( ( *FAnswer )[0].SetAccount.AccountInfo ), &FAccInfo, sizeof( TAccountInfo ) );

				if( _createKeeper )
				{
					_ord_keeper = order_keeper_manager::instance()->start_keeper(this->FSetupFile,get_callback_fun(),
						&FRequest.SetAccount);
				}
				return 0;
			}
			else
			{
				//账单确认
				goto COMFIRM;
			}
		}
		else
		{
			this->SetLastError(ERR_NO_ACK,'E',PLUGINNAME,"GetRowCount=0");
			return ERR_NO_ACK;
		}
		}
		__finally
		{
			//out->Release();
		}
	}

COMFIRM:
			//获取打包器
	pack = NewPacker(2);
	pack->AddRef();
	//创建一个业务包
	pack->BeginPack();

	pack->AddField("version");
	pack->AddField("op_branch_no");
	pack->AddField("op_entrust_way");
	pack->AddField("op_station");
	pack->AddField("branch_no");
	pack->AddField("function_id");
	pack->AddField("fund_account");
	pack->AddField("password");
	pack->AddField("check_date");
	pack->AddField("check_time");
	pack->AddField("hs_license");

	pack->AddStr(HS_VERSION);
	pack->AddStr(FHSFFSet.op_branch_no.c_str());
	pack->AddStr(FHSFFSet.op_entrust_way.c_str());
	pack->AddStr(FHSFFSet.op_station.c_str());
	pack->AddStr(FHSFFSet.branch_no.c_str());
	pack->AddStr("622005");
	pack->AddStr(FRequest.SetAccount.Account);
	pack->AddStr(FRequest.SetAccount.PW);
	pack->AddStr(AnsiString(Date().FormatString(L"yyyymmdd")).c_str());
	pack->AddStr(AnsiString(Time().FormatString(L"hhnnss")).c_str());
	pack->AddStr(this->FHSFFSet.hs_licence.c_str());
	pack->EndPack();

	out = NULL;
	r	= SendAndReceive(622005,pack,&out);

	//free(pack->GetPackBuf());
	pack->Release();

	if ( r < 0 || out == NULL )
	{
		return r;
	}
	else
	{
		try
		{
		NewAns( 1 );
		memcpy( &( ( *FAnswer )[0].SetAccount.AccountInfo ), &FAccInfo, sizeof( TAccountInfo ) );

		if( _createKeeper )
		{
			_ord_keeper = order_keeper_manager::instance()->start_keeper(this->FSetupFile,get_callback_fun(),
				&FRequest.SetAccount);
		}
		}
		__finally
		{
			//out->Release();
		}
	}
    return 0;
}

int TTrdItf_HSFF::QryMoney()
{
	if( FRequest.QryMoney.ReqHead.Version == -100 )
	{
		//获取打包器
		IF2Packer* pack = NewPacker(2);
		pack->AddRef();
		//创建一个业务包
		pack->BeginPack();

		pack->AddField("version");
		pack->AddField("op_branch_no");
		pack->AddField("op_entrust_way");
		pack->AddField("op_station");
		pack->AddField("branch_no");
		pack->AddField("function_id");
		pack->AddField("fund_account");
		pack->AddField("password");
		pack->AddField("money_type");
		pack->AddField("hs_license");

		pack->AddStr(HS_VERSION);
		pack->AddStr(FHSFFSet.op_branch_no.c_str());
		pack->AddStr(FHSFFSet.op_entrust_way.c_str());
		pack->AddStr(FHSFFSet.op_station.c_str());
		pack->AddStr(FHSFFSet.branch_no.c_str());
		pack->AddStr("622504");
		pack->AddStr(this->FAccInfo.Capital);
		pack->AddStr(this->FAccInfo.PW);
		pack->AddStr(ConvertMoneyType(FRequest.QryMoney.MoneyType));
		pack->AddStr(this->FHSFFSet.hs_licence.c_str());
		pack->EndPack();

		IF2UnPacker *out = NULL;
		int	r	= SendAndReceive(622504,pack,&out);

		//free(pack->GetPackBuf());
		pack->Release();

		if ( r < 0 || out == NULL )
		{
			return r;
		}
		else
		{
			try
			{
			if ( out->GetRowCount() > 0 )
			{
				NewAns( 1 );
				( *FAnswer )[0].QryMoney.MoneyInfo.balance = out->GetDouble("rights_balance_float");
				( *FAnswer )[0].QryMoney.MoneyInfo.available = out->GetDouble("enable_balance");
				( *FAnswer )[0].QryMoney.MoneyInfo.MoneyType = ConvertMoneyType(out->GetStr("money_type"));

				return 0;
			}
			else
			{
				this->SetLastError(ERR_NO_ACK,'E',PLUGINNAME,"GetRowCount=0");
				return ERR_NO_ACK;
			}
			}
			__finally
			{
				//out->Release();
			}
		}
	}
	else
	{
		assert(_ord_keeper!=NULL );
		TMoneyInfo ans;
		_ord_keeper->get_last_money(ans);
		NewAns( 1 );
		( *FAnswer )[0].QryMoney.MoneyInfo.balance = ans.balance;
		( *FAnswer )[0].QryMoney.MoneyInfo.available = ans.available;
		( *FAnswer )[0].QryMoney.MoneyInfo.MoneyType = ans.MoneyType;
        //_ord_keeper->pendingQryMoney();
		return 0;
    }
	return -1;
}

market_type convert_market( TradeGateway::MarketIdSource ms )
{
    market_type ret = mtNo;
    switch( ms )
    {
    case TradeGateway::SSE:
        ret = mtSHA;
        break;
    case TradeGateway::SZSE:
        ret = mtSZA;
        break;
    case TradeGateway::SHFE:
        ret = mtFSH;
        break;
    case TradeGateway::DCE:
        ret = mtFZZ;
        break;
    case TradeGateway::CZCE:
        ret = mtFDL;
        break;
    case TradeGateway::CFFEX:
        ret = mtJJS;
        break;
    case TradeGateway::HKEX:
        ret = mtHK;
        break;
    case TradeGateway::MktUnknow:
        ret = mtNo;
        break;
    }
    return ret;
}

int TTrdItf_HSFF::QryCurCsn()
{
	if(FRequest.QryCurCsn.OrderID[0]==0)
	{
		//增量查询
		database db;
		TradeGateway::OrderReportSeq list;
		try
		{
			db.qry_orders(this->FAccInfo.Capital,FRequest.QryCurCsn.SeqNum,
				FRequest.QryCurCsn.MaxRecord,
				Date().FormatString("yyyymmdd").ToInt(),list);

			if( list.size()==0 ) return 0;
			NewAns(list.size());
			for( size_t i=0;i<list.size();i++)
			{
                TOrderInfo &poi = (*FAnswer)[i].QryCurCsn.OrderInfo;
                TradeGateway::OrderReport &or = list[i];
                strncpy(poi.Account,or.base.accountId.c_str(),ACC_LEN);
                if( or.ordStatus == TradeGateway::Canceled ||
                    or.ordStatus == TradeGateway::Filled ||
                    or.ordStatus == TradeGateway::DoneForDay ||
                    or.ordStatus == TradeGateway::Canceled ||
                    or.ordStatus == TradeGateway::Stopped ||
                    or.ordStatus == TradeGateway::Rejected)
                    poi.CancelVol = or.cumQty-or.base.ordQty;
                strncpy(poi.ContractID, or.base.ordId.c_str(),SEQ_LEN);
                poi.CsnPrice = or.base.lmtPrice;
                poi.CsnVol = or.base.ordQty;
                poi.Date = or.base.date;
                poi.Market = convert_market(or.base.inst.securityIDSource);
                strncpy(poi.SecuID,or.base.inst.securityID.c_str(),CODE_LEN);
                strncpy(poi.SeqNum,or.seq.c_str(),SEQ_LEN);
                switch( or.ordStatus )
                {
                case TradeGateway::New:
                    poi.State = oswb;
                    break;
                case TradeGateway::PendingNew:
                    poi.State = osyb;
                    break;
                case TradeGateway::Working:
                    poi.State = osbc;
                    break;
                case TradeGateway::PendingCancel:
                    poi.State = osdc;
                    break;
                case TradeGateway::Filled:
                    poi.State = oscj;
                    break;
                case TradeGateway::DoneForDay:
                    poi.State;
                    break;
                case TradeGateway::Canceled:
                    if( abs(poi.CancelVol)==poi.CsnVol )
                        poi.State = osyc;
                    else
                        poi.State = osbw;
                    break;
                case TradeGateway::Stopped:
                    poi.State =  osyf;
                    break;
                case TradeGateway::Rejected:
                    poi.State = osyf;
                    break;
                case TradeGateway::OrdStatusUnknow:
                    poi.State =osno;
                    break;
                default:
                    poi.State =osno;
                }

                poi.Time = or.base.time;
                poi.TrdPrice = or.avgPx;
                poi.TrdVol = or.cumQty;

                if( or.base.s == TradeGateway::Buy )
                {
                    if( or.base.posEfct == TradeGateway::Open )
                        poi.Type = otOpenBuy;
                    else if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otCloseBuy;
                    }
                    else if( or.base.posEfct == TradeGateway::CloseToday )
                    {
                        poi.Type =otCloseTodayBuy;
                    }
                    //else if( or.base.posEfct == TradeGateway::CloseYesterday )
                    //{
                    //	poi.Type =otCloseBuy;
                    //}
                    else
                        poi.Type = otBuy;
                }
                else if( or.base.s == TradeGateway::Sell )
                {
                    if( or.base.posEfct == TradeGateway::Open )
                        poi.Type = otOpenSell;
                    else if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otCloseSell;
                    }
                    else if( or.base.posEfct == TradeGateway::CloseToday )
                    {
                        poi.Type =otCloseTodaySell;
                    }
                    //else if( or.base.posEfct == TradeGateway::CloseYesterday )
                    //{
                    //	poi.Type =otCloseSell;
                    //}
                    else
                        poi.Type = otSell;
                }
				else if(or.base.s == TradeGateway::Subscribe)
                {
                    poi.Type = otETFSub;
                }
				else if(or.base.s == TradeGateway::Redeem)
                {
                    poi.Type = otETFRed;
                }
				else if(or.base.s == TradeGateway::Lend)
                {
                    if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otSellRepay;
                    }
                    else
                        poi.Type = otLoanBuy;
                }
                else if(or.base.s == TradeGateway::Borrow)
                {
                    if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otBuyRepay;
                    }
                    else
                        poi.Type = otLoanSell;
                }
            }
		}
		catch( std::string &err)
		{
			SetLastError(-1,'E',PLUGINNAME,err.c_str());
			return -1;
        }
	}
	else
	{
		if( FRequest.QryCurCsn.MaxRecord == -100 ) //从柜台查
		{
        	//获取打包器
			IF2Packer* pack = NewPacker(2);
			pack->AddRef();
			//创建一个业务包
			pack->BeginPack();

			pack->AddField("version");
			pack->AddField("op_branch_no");
			pack->AddField("op_entrust_way");
			pack->AddField("op_station");
			pack->AddField("function_id");
			pack->AddField("branch_no");
			pack->AddField("fund_account");
			pack->AddField("password");
			pack->AddField("futu_exch_type");
			pack->AddField("futures_account");
			pack->AddField("contract_code");
			pack->AddField("query_direction");
			pack->AddField("entrust_no");
			pack->AddField("request_num");
			pack->AddField("position_str");
			pack->AddField("hs_license");

			pack->AddStr(HS_VERSION);
			pack->AddStr(FHSFFSet.op_branch_no.c_str());
			pack->AddStr(FHSFFSet.op_entrust_way.c_str());
			pack->AddStr(FHSFFSet.op_station.c_str());
			pack->AddStr("622502");
			pack->AddStr(FHSFFSet.branch_no.c_str());
			pack->AddStr(this->FAccInfo.Capital);
			pack->AddStr(this->FAccInfo.PW);
			pack->AddStr("");
			pack->AddStr("");
			pack->AddStr("");
			pack->AddStr("0");
			pack->AddStr(FRequest.QryCurCsn.OrderID);
			pack->AddStr("1");
			pack->AddStr("");
			pack->AddStr(this->FHSFFSet.hs_licence.c_str());
			pack->EndPack();

			IF2UnPacker *out = NULL;
			int	r	= SendAndReceive(622502,pack,&out);

			//free(pack->GetPackBuf());
			pack->Release();

			if ( r < 0 || out == NULL )
			{
				return r;
			}
			else
			{
				try
				{
				if ( out->GetRowCount() == 1 )
				{
					NewAns(out->GetRowCount());
					for(int i=0;i<out->GetRowCount();i++)
					{
						TOrderInfo *oi =  &(*FAnswer)[i].QryCurCsn.OrderInfo;
						ZeroMemory(oi,sizeof(TOrderInfo));

						//组建输出数据
						lstrcpyn( oi->ContractID, out->GetStr("entrust_no" ),SEQ_LEN);
						lstrcpyn( oi->SecuID, out->GetStr("contract_code" ),CODE_LEN);
						lstrcpyn( oi->Account, out->GetStr("futures_account" ),ACC_LEN);
						oi->Market = this->ConvertMarketType(out->GetStr("futu_exch_type" ));
						oi->Time = this->ConvertTimeToInt(out->GetStr("entrust_time" ));
						oi->Date = this->ConvertDateToInt(out->GetStr("init_date" ));
						oi->Type = this->ConvertOrderType(
							(AnsiString( out->GetChar("entrust_bs" )) +
							 AnsiString( out->GetChar("futures_direction" ))).c_str());
						oi->State = this->ConvertOrderState(out->GetStr("entrust_status" ));
						oi->CsnVol = out->GetDouble("entrust_amount");
						oi->TrdVol = out->GetDouble("business_amount");
						oi->CsnPrice = out->GetDouble("futu_entrust_price");
						if( oi->State == osyf )
						{
							oi->CancelVol =  -oi->CsnVol;
						}
						else
							oi->CancelVol = - abs((int)out->GetDouble("cancel_amount"));
						oi->TrdPrice = 0;
						lstrcpyn(oi->SeqNum,out->GetStr("position_str" ),SEQ_LEN);
                        break;
						out->Next();
					}
					return 0;
				}
				else
				{
					return 0;
				}
				}
				__finally
				{
					//out->Release();
				}
			}
			return 0;
		}
		else
		{
			database db;
			TradeGateway::OrderReport ord;
			try
			{
				int ret = db.qry_order_by_ordid(this->FAccInfo.Capital,FRequest.QryCurCsn.OrderID,
					Date().FormatString("yyyymmdd").ToInt(),ord);

				if( ret<1 ) return 0;
				NewAns(1);

				TOrderInfo &poi = (*FAnswer)[0].QryCurCsn.OrderInfo;
				TradeGateway::OrderReport &or = ord;
				strncpy(poi.Account,or.base.accountId.c_str(),ACC_LEN);
				if( or.ordStatus == TradeGateway::Canceled ||
					or.ordStatus == TradeGateway::Filled ||
					or.ordStatus == TradeGateway::DoneForDay ||
					or.ordStatus == TradeGateway::Canceled ||
					or.ordStatus == TradeGateway::Stopped ||
					or.ordStatus == TradeGateway::Rejected)
					poi.CancelVol = or.cumQty-or.base.ordQty;
				strncpy(poi.ContractID, or.base.ordId.c_str(),SEQ_LEN);
				poi.CsnPrice = or.base.lmtPrice;
				poi.CsnVol = or.base.ordQty;
				poi.Date = or.base.date;
				poi.Market = convert_market(or.base.inst.securityIDSource);
				strncpy(poi.SecuID,or.base.inst.securityID.c_str(),CODE_LEN);
				strncpy(poi.SeqNum,or.seq.c_str(),SEQ_LEN);
				switch( or.ordStatus )
				{
				case TradeGateway::New:
					poi.State = oswb;
					break;
				case TradeGateway::PendingNew:
					poi.State = osyb;
					break;
				case TradeGateway::Working:
					poi.State = osbc;
					break;
				case TradeGateway::PendingCancel:
					poi.State = osdc;
					break;
				case TradeGateway::Filled:
					poi.State = oscj;
					break;
				case TradeGateway::DoneForDay:
					poi.State;
					break;
				case TradeGateway::Canceled:
					if( abs(poi.CancelVol)==poi.CsnVol )
						poi.State = osyc;
					else
						poi.State = osbw;
					break;
				case TradeGateway::Stopped:
					poi.State =  osyf;
					break;
				case TradeGateway::Rejected:
					poi.State = osyf;
					break;
				case TradeGateway::OrdStatusUnknow:
					poi.State =osno;
					break;
				default:
					poi.State =osno;
				}

				poi.Time = or.base.time;
				poi.TrdPrice = or.avgPx;
				poi.TrdVol = or.cumQty;

				if( or.base.s == TradeGateway::Buy )
				{
					if( or.base.posEfct == TradeGateway::Open )
						poi.Type = otOpenBuy;
					else if( or.base.posEfct == TradeGateway::Close )
					{
						poi.Type =otCloseBuy;
					}
					else if( or.base.posEfct == TradeGateway::CloseToday )
					{
						poi.Type =otCloseTodayBuy;
					}
					//else if( or.base.posEfct == TradeGateway::CloseYesterday )
					//{
					//	poi.Type =otCloseBuy;
					//}
					else
						poi.Type = otBuy;
				}
				else if( or.base.s == TradeGateway::Sell )
				{
					if( or.base.posEfct == TradeGateway::Open )
						poi.Type = otOpenSell;
					else if( or.base.posEfct == TradeGateway::Close )
					{
						poi.Type =otCloseSell;
					}
					else if( or.base.posEfct == TradeGateway::CloseToday )
					{
						poi.Type =otCloseTodaySell;
					}
					//else if( or.base.posEfct == TradeGateway::CloseYesterday )
					//{
					//	poi.Type =otCloseSell;
					//}
					else
						poi.Type = otSell;
				}
				else if(or.base.s == TradeGateway::Subscribe)
				{
					poi.Type = otETFSub;
				}
				else if(or.base.s == TradeGateway::Redeem)
				{
					poi.Type = otETFRed;
				}
				else if(or.base.s == TradeGateway::Lend)
				{
					if( or.base.posEfct == TradeGateway::Close )
					{
						poi.Type =otSellRepay;
					}
					else
						poi.Type = otLoanBuy;
				}
				else if(or.base.s == TradeGateway::Borrow)
				{
					if( or.base.posEfct == TradeGateway::Close )
					{
						poi.Type =otBuyRepay;
					}
					else
						poi.Type = otLoanSell;
				}
			}
			catch( std::string &err)
			{
				SetLastError(-1,'E',PLUGINNAME,err.c_str());
				return -1;
			}
		}
	}
	return 0;
}


int TTrdItf_HSFF::QryCurTrd()
{
	if( strcmp(FRequest.QryCurTrd.OrderID,"-100")==0)  // 如果-100则是供内部查成交用
	{
		//获取打包器
		IF2Packer* pack = NewPacker(2);
		pack->AddRef();
		//创建一个业务包
		pack->BeginPack();

		pack->AddField("version");
		pack->AddField("op_branch_no");
		pack->AddField("op_entrust_way");
		pack->AddField("op_station");
		pack->AddField("function_id");
		pack->AddField("branch_no");
		pack->AddField("fund_account");
		pack->AddField("password");
		pack->AddField("futu_exch_type");
		pack->AddField("futures_account");
		pack->AddField("contract_code");
		pack->AddField("query_mode");
		pack->AddField("query_direction");
		pack->AddField("request_num");
		pack->AddField("futu_position_str");
		pack->AddField("hs_license");

		pack->AddStr(HS_VERSION);
		pack->AddStr(FHSFFSet.op_branch_no.c_str());
		pack->AddStr(FHSFFSet.op_entrust_way.c_str());
		pack->AddStr(FHSFFSet.op_station.c_str());
		pack->AddStr("622503");
		pack->AddStr(FHSFFSet.branch_no.c_str());
		pack->AddStr(this->FAccInfo.Capital);
		pack->AddStr(this->FAccInfo.PW);
		pack->AddStr("");
		pack->AddStr("");
		pack->AddStr("");
		pack->AddStr("0");
		pack->AddStr("0");
		pack->AddStr(AnsiString(IntToStr((int)FRequest.QryCurTrd.MaxRecord)).c_str());
		pack->AddStr(FRequest.QryCurTrd.SeqNum);
		pack->AddStr(this->FHSFFSet.hs_licence.c_str());
		pack->EndPack();

		IF2UnPacker *out = NULL;
		int	r	= SendAndReceive(622503,pack,&out);

		//free(pack->GetPackBuf());
		pack->Release();

		if ( r < 0 || out == NULL )
		{
			return r;
		}
		else
		{
			try
			{
			if ( out->GetRowCount() > 0 )
			{
				NewAns(out->GetRowCount());
				for(int i=0;i<out->GetRowCount();i++)
				{
					TTradeInfo *ti =  &(*FAnswer)[i].QryCurTrd.TrdInfo;
					ZeroMemory(ti,sizeof(TTradeInfo));

					//组建输出数据
					lstrcpyn( ti->ContractID ,out->GetStr("entrust_no"),SEQ_LEN);
					lstrcpyn( ti->TrdID ,out->GetStr("futu_business_no"),SEQ_LEN);
					lstrcpyn( ti->SecuID,out->GetStr("contract_code"),CODE_LEN);
					lstrcpyn( ti->Account,out->GetStr("futures_account"),ACC_LEN);
					ti->Time = this->ConvertTimeToInt(out->GetStr("business_time"));
					ti->Date = this->ConvertDateToInt(out->GetStr("init_date"));
					ti->Type = this->ConvertOrderType(
						(AnsiString( out->GetChar("entrust_bs" )) +
						 AnsiString( out->GetChar("futures_direction") )).c_str()  );
					ti->Vol = abs((int)out->GetDouble("business_amount" ));
					ti->Price = out->GetDouble("futu_business_price" );
					ti->Market = this->ConvertMarketType(out->GetStr("futu_exch_type" ));
					lstrcpyn(ti->SeqNum ,out->GetStr("futu_position_str" ),SEQ_LEN);

					if (ti->Price <0 || ti->TrdID[0] == 0 || ti->Vol <=0 || ti->SeqNum[0] == 0 || ti->Time <=0)
					{
						ODS('E',PLUGINNAME,"*调用功能号622503返回数据异常");
						ti->Vol = 0;
					}

					out->Next();
				}
				return 0;
			}
			else
			{
				return 0;
			}
			}
			__finally
			{
                //out->Release();
            }
		}
		return 0;
	}
	else
	{
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
}

int TTrdItf_HSFF::QryStocks()
{
	//获取打包器
	IF2Packer* pack = NewPacker(2);
	pack->AddRef();
	//创建一个业务包
	pack->BeginPack();

	pack->AddField("version");
	pack->AddField("op_branch_no");
	pack->AddField("op_entrust_way");
	pack->AddField("op_station");
	pack->AddField("function_id");
	pack->AddField("branch_no");
	pack->AddField("fund_account");
	pack->AddField("password");
	pack->AddField("futu_exch_type");
	pack->AddField("futures_account");
	pack->AddField("contract_code");
	pack->AddField("entrust_bs");
	pack->AddField("query_direction");
	pack->AddField("query_mode");
	pack->AddField("request_num");
	pack->AddField("futu_position_str");
	pack->AddField("action_in");
	pack->AddField("hs_license");

	pack->AddStr(HS_VERSION);
	pack->AddStr(FHSFFSet.op_branch_no.c_str());
	pack->AddStr(FHSFFSet.op_entrust_way.c_str());
	pack->AddStr(FHSFFSet.op_station.c_str());
	pack->AddStr("622501");
	pack->AddStr(FHSFFSet.branch_no.c_str());
	pack->AddStr(this->FAccInfo.Capital);
	pack->AddStr(this->FAccInfo.PW);
	pack->AddStr(this->ConvertMarketType(FRequest.QryStocks.Market));
	pack->AddStr("");
	pack->AddStr("");
	pack->AddStr("");
	pack->AddStr("0");
	pack->AddStr("0");
	pack->AddStr("1000");
	pack->AddStr("");
	pack->AddStr("0");
	pack->AddStr(this->FHSFFSet.hs_licence.c_str());
	pack->EndPack();

	IF2UnPacker *out = NULL;
	int	r	= SendAndReceive(622501,pack,&out);

	//free(pack->GetPackBuf());
	pack->Release();

	if ( r < 0 || out == NULL )
	{
		return r;
	}
	else
	{
		try
		{
		if ( out->GetRowCount() > 0 )
		{
			NewAns(out->GetRowCount());
			for(int i=0;i<out->GetRowCount();i++)
			{
                TStockInfo *si =  &(*FAnswer)[i].QryStocks.StockInfo;
				ZeroMemory(si,sizeof(TStockInfo));

				si->Market = this->ConvertMarketType(out->GetStr("futu_exch_type"));
				lstrcpyn(si->SecuID,out->GetStr("contract_code"),CODE_LEN);
				lstrcpyn(si->Account,out->GetStr("futures_account"),ACC_LEN);
				si->Balance = out->GetDouble("begin_amount");
				si->Available =  out->GetDouble("enable_amount");
				si->PosNum  = out->GetDouble("real_amount");
				si->CostPrice = out->GetDouble("futu_average_price");
				si->CurPrice =  out->GetDouble("futu_last_price");
				si->PosDir = this->ConvertPosDir(out->GetStr("entrust_bs"));
				out->Next();
            }
			return 0;
		}
		else
		{
			return 0;
		}
		}__finally
		{
			//out->Release();
		}
	}
	return -1;
}

int TTrdItf_HSFF::Order()
{
	//获取打包器
	IF2Packer* pack = NewPacker(2);
	pack->AddRef();
	//创建一个业务包
	pack->BeginPack();

	pack->AddField("version");
	pack->AddField("op_branch_no");
	pack->AddField("op_entrust_way");
	pack->AddField("op_station");
	pack->AddField("function_id");
	pack->AddField("branch_no");
	pack->AddField("fund_account");
	pack->AddField("password");
	pack->AddField("futu_exch_type");
	pack->AddField("futures_account");
	pack->AddField("contract_code");
	pack->AddField("entrust_bs");
	pack->AddField("futures_direction");
	pack->AddField("hedge_type");
	pack->AddField("entrust_amount");
	pack->AddField("futu_entrust_price");
	pack->AddField("hs_license");

	pack->AddStr(HS_VERSION);
	pack->AddStr(FHSFFSet.op_branch_no.c_str());
	pack->AddStr(FHSFFSet.op_entrust_way.c_str());
	pack->AddStr(FHSFFSet.op_station.c_str());
	pack->AddStr("622003");
	pack->AddStr(FHSFFSet.branch_no.c_str());
	pack->AddStr(this->FAccInfo.Capital);
	pack->AddStr(this->FAccInfo.PW);
	pack->AddStr(this->ConvertMarketType(FRequest.Order.Market));
	pack->AddStr("");
	pack->AddStr(FRequest.Order.SecuID);
	pack->AddStr(AnsiString(this->ConvertOrderType( FRequest.Order.Type)[0]).c_str());
	pack->AddStr(AnsiString(this->ConvertOrderType( FRequest.Order.Type)[1]).c_str());
	pack->AddStr("0");
	pack->AddStr(AnsiString(IntToStr(FRequest.Order.Num)).c_str());

	long lp = (long)(FRequest.Order.Price * 100.0f);
	if( lp % 10 >=5 )
		lp = lp/10 + 1;
	else
		lp = lp/10;
	AnsiString s;
	s.printf("%d.%d",lp/10,lp%10);
	pack->AddStr(s.c_str());

	pack->AddStr(this->FHSFFSet.hs_licence.c_str());

	pack->EndPack();

	IF2UnPacker *out = NULL;
	int	r	= SendAndReceive(622003,pack,&out);

	//free(pack->GetPackBuf());
	pack->Release();

	if ( r < 0 || out == NULL )
	{
		return r;
	}
	else
	{
		try
		{
		if ( out->GetRowCount() > 0 )
		{
			NewAns( 1 );
			lstrcpyn( ( *FAnswer )[0].Order.ContractID, out->GetStr("entrust_no") , SEQ_LEN);

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
			}
			catch( std::string &err)
			{
				SetLastError(-1,'E',PLUGINNAME,"加入委托到本地数据库失败:%s",err.c_str());
				return -1;
			}
			return 0;
		}
		else
		{
			this->SetLastError(ERR_NO_ACK,'E',PLUGINNAME,"GetRowCount=0");
			return ERR_NO_ACK;
		}
		}
		__finally
		{
			//out->Release();
		}
	}
	return -1;
}

int TTrdItf_HSFF::Undo()
{
	//获取打包器
	IF2Packer* pack = NewPacker(2);
	pack->AddRef();
	//创建一个业务包
	pack->BeginPack();

	pack->AddField("version");
	pack->AddField("op_branch_no");
	pack->AddField("op_entrust_way");
	pack->AddField("op_station");
	pack->AddField("function_id");
	pack->AddField("branch_no");
	pack->AddField("fund_account");
	pack->AddField("password");
	pack->AddField("entrust_no");
	pack->AddField("hs_license");

	pack->AddStr(HS_VERSION);
	pack->AddStr(FHSFFSet.op_branch_no.c_str());
	pack->AddStr(FHSFFSet.op_entrust_way.c_str());
	pack->AddStr(FHSFFSet.op_station.c_str());
	pack->AddStr("622004");
	pack->AddStr(FHSFFSet.branch_no.c_str());
	pack->AddStr(this->FAccInfo.Capital);
	pack->AddStr(this->FAccInfo.PW);
	pack->AddStr(FRequest.Undo.ContractID);
	pack->AddStr(this->FHSFFSet.hs_licence.c_str());
	pack->EndPack();

	IF2UnPacker *out = NULL;
	int	r	= SendAndReceive(622004,pack,&out);

	//free(pack->GetPackBuf());
	pack->Release();

	if ( r < 0 || out == NULL )
	{
		if( out )
		{
            if( strstr(FLastError.Text, "p_old_entrust_status = 6") != NULL )
			{
				// 已经撤销了
				assert(_ord_keeper!=NULL);
				_ord_keeper->add_order(FRequest.Undo.ContractID);
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
				assert(_ord_keeper!=NULL);
				_ord_keeper->add_order(FRequest.Undo.ContractID);
				return ERR_UNDO_REPEAL;
			}
			else if (strstr(FLastError.Text, "p_old_entrust_status = 5") != NULL )
			{
				// 已经部撤了
				assert(_ord_keeper!=NULL);
				_ord_keeper->add_order(FRequest.Undo.ContractID);
				return ERR_UNDO_ALREADY_CANCLED;
			}
        }
		return r;
	}
	else
	{
		try
		{
		if ( out->GetRowCount() > 0 )
		{
			//if ( strcmp(out->GetStr("entrust_no"), FRequest.Undo.ContractID) == 0 )
			{
				assert(_ord_keeper!=NULL);
				_ord_keeper->add_order(FRequest.Undo.ContractID);
				return 0;
            }
			//else
			//{
			//	this->SetLastError(-3,'E',PLUGINNAME,"返回的委托号和撤单的委托号不符,%s<>%s",
			//		out->GetStr("entrust_no"),
			//		FRequest.Undo.ContractID	);
			//	return -3;
            //}
		}
		else
		{
			this->SetLastError(ERR_NO_ACK,'E',PLUGINNAME,"GetRowCount=0");
			return ERR_NO_ACK;
		}
		}
		__finally
		{
			//out->Release();
		}
	}
	return -1;
}

TTrdItf_HSFF::TTrdItf_HSFF( const char *psetupfile,ADDLOG plogfunc ,bool createKeeper)
:TTrdItfBase(psetupfile,plogfunc)
{
	//FAccount = "";
	_createKeeper = createKeeper;
	_config = NULL;

	if( _config== NULL )
	{
		_config = NewConfig();
		_config->AddRef();
	}

	_connection = NULL;

	FHSFFSet.TimeOut = 10000;
	FHSFFSet.gen_check_info=false;
}

TTrdItf_HSFF::~TTrdItf_HSFF()
{
	CloseLink();
	if(_config)
	{
		_config->Release();
		_config = NULL;
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
		FHSFFSet.TimeOut          = ini->ReadInteger(PLUGINNAME,"TimeOut",FHSFFSet.TimeOut);
		FHSFFSet.op_branch_no     = ini->ReadString(PLUGINNAME,"op_branch_no",FHSFFSet.op_branch_no);
		FHSFFSet.op_entrust_way   = ini->ReadString(PLUGINNAME,"op_entrust_way",FHSFFSet.op_entrust_way);
		FHSFFSet.branch_no        = ini->ReadString(PLUGINNAME,"branch_no",FHSFFSet.branch_no);
		FHSFFSet.op_station       = ini->ReadString(PLUGINNAME,"op_station",FHSFFSet.op_station);
		if (FHSFFSet.op_station.Length() < 7) {
			FHSFFSet.op_station.printf("192.168.1.%d",rand()%200+1);
			ODS("OPSTATION:%s",FHSFFSet.op_station.c_str());
		}

		FHSFFSet.hs_licence       = ini->ReadString(PLUGINNAME,"hs_licence",FHSFFSet.hs_licence);
		FHSFFSet. gen_check_info  = ini->ReadBool(PLUGINNAME,"gen_check_info",FHSFFSet. gen_check_info );
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
		ini->WriteInteger(PLUGINNAME,"TimeOut",          FHSFFSet.TimeOut);
		ini->WriteString(PLUGINNAME,"op_branch_no",     FHSFFSet.op_branch_no);
		ini->WriteString(PLUGINNAME,"op_entrust_way",   FHSFFSet.op_entrust_way);
		ini->WriteString(PLUGINNAME,"branch_no",        FHSFFSet.branch_no);
		ini->WriteString(PLUGINNAME,"op_station",       FHSFFSet.op_station);
		ini->WriteString(PLUGINNAME,"hs_licence",       FHSFFSet.hs_licence);
		ini->WriteBool(PLUGINNAME,"gen_check_info",FHSFFSet. gen_check_info);
		ini->UpdateFile();
	}
	__finally
	{
		delete ini;
	}
}

int TTrdItf_HSFF::KeepAlive(void)
{
	return 0;
}
