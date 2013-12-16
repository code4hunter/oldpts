//---------------------------------------------------------------------------
#pragma hdrstop

#include "uSession.h"
#include "DebugStr.h"
#include <Windows.h>
#include <stdio.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

session_manager gSessionMan;
const char* SENDER = "SESSION";
// 流控判断
bool IsFlowControl(int iResult)
{
	return ((iResult == -2) || (iResult == -3));
}

void session::OnFrontConnected()
{
	ODS('M',SENDER,"已连接前置机");
	///用户登录请求
	ReqUserLogin();
}

void session::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, _brokerId.c_str());
	strcpy(req.UserID, _investorId.c_str());
	strcpy(req.Password, _password.c_str());

	long id = InterlockedIncrement(&_request_id);
	int iResult = user_api->ReqUserLogin(&req, id);

	if( iResult != 0 )
		ODS('E',SENDER,"发送用户登录请求失败,result = %d",iResult);
}

void session::ReqUserLogout()
{

}

void session::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		// 保存会话参数
		_front_id = pRspUserLogin->FrontID;
		_session_id = pRspUserLogin->SessionID;
		_order_ref = atoi(pRspUserLogin->MaxOrderRef);
		_trd_date = atoi(pRspUserLogin->TradingDay);
		///获取当前交易日
		ODS('M',SENDER,"已登录,%d,%d,%d,%s,%d,%s",
			_front_id,_session_id,_order_ref,pRspUserLogin->UserID,_trd_date,
			pRspUserLogin->LoginTime);

		///投资者结算结果确认
		ReqSettlementInfoConfirm();
        ReqQry(true);
        _is_login = true;
	}
}

bool session::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		ODS('E',SENDER,"收到错误响应,%d,%s",pRspInfo->ErrorID ,pRspInfo->ErrorMsg);
	return bResult;
}

void session::ReqSettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, _brokerId.c_str());
	strcpy(req.InvestorID, _investorId.c_str());
	long id = InterlockedIncrement(&_request_id);
	int iResult = user_api->ReqSettlementInfoConfirm(&req, id);
	if( iResult != 0 )
		ODS('E',SENDER,"投资者结算结果确认失败,result = %d",iResult);
}

void session::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///请求查询合约
		ReqQryInstrument();
	}
}

void session::ReqQryInstrument()
{
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	//strcpy(req.InstrumentID, INSTRUMENT_ID);
	while (true)
	{
		long id = InterlockedIncrement(&_request_id);
		int iResult = user_api->ReqQryInstrument(&req, id);
		if (!IsFlowControl(iResult))
		{
			break;
		}
		else
		{
			ODS('M',SENDER,"受到流控...");
			Sleep(1000);
		}
	} // while
}

void session::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		//将代码表写入db


		///请求查询合约
		ReqQryTradingAccount();
	}
}

void session::ReqQryTradingAccount()
{
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, _brokerId.c_str());
	strcpy(req.InvestorID, _investorId.c_str());
	while (true)
	{
		long id = InterlockedIncrement(&_request_id);
		int iResult = user_api->ReqQryTradingAccount(&req, id);
		if (!IsFlowControl(iResult))
		{
			break;
		}
		else
		{
			ODS('M',SENDER,"受到流控...");
			Sleep(1000);
		}
	} // while
}

void session::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		//将资金信息写入db


		///请求查询投资者持仓
		ReqQryInvestorPosition();
	}
}

void session::ReqQryInvestorPosition()
{
	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, _brokerId.c_str());
	strcpy(req.InvestorID, _investorId.c_str());
	while (true)
	{
		long id = InterlockedIncrement(&_request_id);
		int iResult = user_api->ReqQryInvestorPosition(&req, id);
		if (!IsFlowControl(iResult))
		{
			break;
		}
		else
		{
			ODS('M',SENDER,"受到流控...");
			Sleep(1000);
		}
	} // while
}

void session::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		//将最新position写入db
	}
}

int session::ReqOrderInsert(	const std::string &instId,  //代码
						int direction,              //买卖 1,-1
						double price,               //price <0表示市价单
						int volume,
						int openClose,              //开平,平今 1,-1 ,-2
						int hedge                   //投机套保1,2
						)
{
 	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	///经纪公司代码
	strcpy(req.BrokerID, _brokerId.c_str());
	///投资者代码
	strcpy(req.InvestorID, _investorId.c_str());
	///合约代码
	strcpy(req.InstrumentID, instId.c_str());
	///报单引用
	long id = InterlockedIncrement(&_order_ref);
	sprintf(req.OrderRef,"%d",id);
	///用户代码
//	TThostFtdcUserIDType	UserID;
	///报单价格条件: 限价
	if( price <0 )
		req.OrderPriceType = THOST_FTDC_OPT_BestPrice;
	else
		req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	///买卖方向:
	if( direction==1 )//buy
		req.Direction = THOST_FTDC_D_Buy;
	else if( direction==-1) //sell
		req.Direction = THOST_FTDC_D_Sell;
	///组合开平标志: 开仓
	if( openClose == 1 )
		req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	else if( openClose == -1)
		req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
	else if( openClose == -2 )
        req.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;
	///组合投机套保标志
	if( hedge == 1 )
		req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	else if( hedge == 2 )
		req.CombHedgeFlag[0] =  THOST_FTDC_HF_Arbitrage ;
	///价格
	if( !(price<0) )
		req.LimitPrice = price;
	///数量: 1
	req.VolumeTotalOriginal = volume;
	///有效期类型: 当日有效
	req.TimeCondition = THOST_FTDC_TC_GFD;
	///GTD日期
//	TThostFtdcDateType	GTDDate;
	///成交量类型: 任何数量
	req.VolumeCondition = THOST_FTDC_VC_AV;
	///最小成交量: 1
	req.MinVolume = 1;
	///触发条件: 立即
	req.ContingentCondition = THOST_FTDC_CC_Immediately;
	///止损价
//	TThostFtdcPriceType	StopPrice;
	///强平原因: 非强平
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///自动挂起标志: 否
	req.IsAutoSuspend = 0;
	///业务单元
//	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
//	TThostFtdcRequestIDType	RequestID;
	///用户强评标志: 否
	req.UserForceClose = 0;

    while (true)
	{
		long id = InterlockedIncrement(&_request_id);
		int iResult = user_api->ReqOrderInsert(&req, id);
		if (!IsFlowControl(iResult))
		{
			if( iResult== 0)
                return id;
            else return -1;
		}
		else
		{
			ODS('M',SENDER,"受到流控...");
			Sleep(1000);
		}
	} // while


	//id = InterlockedIncrement(&_request_id);
	//int iResult = user_api->ReqOrderInsert(&req, id);

    return -2;
}

void session::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if( IsErrorRspInfo(pRspInfo) )
	{
        //如果保单错误，生成api撤单标记
    }
}

int session::ReqOrderDelete(const std::string &instId,const char* orderId)
{
	CThostFtdcInputOrderActionField req;
	memset(&req, 0, sizeof(req));
	///经纪公司代码
	strcpy(req.BrokerID, _brokerId.c_str());
	///投资者代码
	strcpy(req.InvestorID, _investorId.c_str());

	///报单引用
	strcpy(req.OrderRef, orderId);
	///前置编号
	req.FrontID = _front_id;
	///会话编号
	req.SessionID = _session_id;
	///操作标志
	req.ActionFlag = THOST_FTDC_AF_Delete;
	///合约代码
	strcpy(req.InstrumentID, instId.c_str());

    while (true)
	{
		long id = InterlockedIncrement(&_request_id);
		int iResult = user_api->ReqOrderAction(&req, id);
		if (!IsFlowControl(iResult))
		{
			if( iResult== 0)
                return 0;
            else return -1;
		}
		else
		{
			ODS('M',SENDER,"受到流控...");
			Sleep(1000);
		}
	} // while

	//long id = InterlockedIncrement(&_request_id);
	//int iResult = user_api->ReqOrderAction(&req, id);
    return -2;
}

void session::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	IsErrorRspInfo(pRspInfo);
}

///报单通知
void session::OnRtnOrder(CThostFtdcOrderField *pOrder)
{

}
///成交通知
void session::OnRtnTrade(CThostFtdcTradeField *pTrade)
{

}

void session:: OnFrontDisconnected(int nReason)
{
	ODS('M',SENDER,"OnFrontDisconnected(%d)...",nReason);
}

void session::OnHeartBeatWarning(int nTimeLapse)
{
	ODS('M',SENDER,"OnHeartBeatWarning(%d)...",nTimeLapse);
}

void session::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	IsErrorRspInfo(pRspInfo);
}

void session::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	ODS('M',SENDER,"%s已登出...",pUserLogout->UserID);
    _is_login = false;
}

void session::ReqQry(bool force)
{
    if( force || (_last_qry_time-::GetTickCount())>2000 )
    {
        ReqQryTradingAccount();
        ReqQryInvestorPosition();
        _last_qry_time = ::GetTickCount();
    }
}

