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
// �����ж�
bool IsFlowControl(int iResult)
{
	return ((iResult == -2) || (iResult == -3));
}

void session::OnFrontConnected()
{
	ODS('M',SENDER,"������ǰ�û�");
	///�û���¼����
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
		ODS('E',SENDER,"�����û���¼����ʧ��,result = %d",iResult);
}

void session::ReqUserLogout()
{

}

void session::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		// ����Ự����
		_front_id = pRspUserLogin->FrontID;
		_session_id = pRspUserLogin->SessionID;
		_order_ref = atoi(pRspUserLogin->MaxOrderRef);
		_trd_date = atoi(pRspUserLogin->TradingDay);
		///��ȡ��ǰ������
		ODS('M',SENDER,"�ѵ�¼,%d,%d,%d,%s,%d,%s",
			_front_id,_session_id,_order_ref,pRspUserLogin->UserID,_trd_date,
			pRspUserLogin->LoginTime);

		///Ͷ���߽�����ȷ��
		ReqSettlementInfoConfirm();
        ReqQry(true);
        _is_login = true;
	}
}

bool session::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// ���ErrorID != 0, ˵���յ��˴������Ӧ
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		ODS('E',SENDER,"�յ�������Ӧ,%d,%s",pRspInfo->ErrorID ,pRspInfo->ErrorMsg);
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
		ODS('E',SENDER,"Ͷ���߽�����ȷ��ʧ��,result = %d",iResult);
}

void session::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///�����ѯ��Լ
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
			ODS('M',SENDER,"�ܵ�����...");
			Sleep(1000);
		}
	} // while
}

void session::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		//�������д��db


		///�����ѯ��Լ
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
			ODS('M',SENDER,"�ܵ�����...");
			Sleep(1000);
		}
	} // while
}

void session::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		//���ʽ���Ϣд��db


		///�����ѯͶ���ֲ߳�
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
			ODS('M',SENDER,"�ܵ�����...");
			Sleep(1000);
		}
	} // while
}

void session::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		//������positionд��db
	}
}

int session::ReqOrderInsert(	const std::string &instId,  //����
						int direction,              //���� 1,-1
						double price,               //price <0��ʾ�м۵�
						int volume,
						int openClose,              //��ƽ,ƽ�� 1,-1 ,-2
						int hedge                   //Ͷ���ױ�1,2
						)
{
 	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	///���͹�˾����
	strcpy(req.BrokerID, _brokerId.c_str());
	///Ͷ���ߴ���
	strcpy(req.InvestorID, _investorId.c_str());
	///��Լ����
	strcpy(req.InstrumentID, instId.c_str());
	///��������
	long id = InterlockedIncrement(&_order_ref);
	sprintf(req.OrderRef,"%d",id);
	///�û�����
//	TThostFtdcUserIDType	UserID;
	///�����۸�����: �޼�
	if( price <0 )
		req.OrderPriceType = THOST_FTDC_OPT_BestPrice;
	else
		req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	///��������:
	if( direction==1 )//buy
		req.Direction = THOST_FTDC_D_Buy;
	else if( direction==-1) //sell
		req.Direction = THOST_FTDC_D_Sell;
	///��Ͽ�ƽ��־: ����
	if( openClose == 1 )
		req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	else if( openClose == -1)
		req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
	else if( openClose == -2 )
        req.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;
	///���Ͷ���ױ���־
	if( hedge == 1 )
		req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	else if( hedge == 2 )
		req.CombHedgeFlag[0] =  THOST_FTDC_HF_Arbitrage ;
	///�۸�
	if( !(price<0) )
		req.LimitPrice = price;
	///����: 1
	req.VolumeTotalOriginal = volume;
	///��Ч������: ������Ч
	req.TimeCondition = THOST_FTDC_TC_GFD;
	///GTD����
//	TThostFtdcDateType	GTDDate;
	///�ɽ�������: �κ�����
	req.VolumeCondition = THOST_FTDC_VC_AV;
	///��С�ɽ���: 1
	req.MinVolume = 1;
	///��������: ����
	req.ContingentCondition = THOST_FTDC_CC_Immediately;
	///ֹ���
//	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��: ��ǿƽ
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///�Զ������־: ��
	req.IsAutoSuspend = 0;
	///ҵ��Ԫ
//	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
//	TThostFtdcRequestIDType	RequestID;
	///�û�ǿ����־: ��
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
			ODS('M',SENDER,"�ܵ�����...");
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
        //���������������api�������
    }
}

int session::ReqOrderDelete(const std::string &instId,const char* orderId)
{
	CThostFtdcInputOrderActionField req;
	memset(&req, 0, sizeof(req));
	///���͹�˾����
	strcpy(req.BrokerID, _brokerId.c_str());
	///Ͷ���ߴ���
	strcpy(req.InvestorID, _investorId.c_str());

	///��������
	strcpy(req.OrderRef, orderId);
	///ǰ�ñ��
	req.FrontID = _front_id;
	///�Ự���
	req.SessionID = _session_id;
	///������־
	req.ActionFlag = THOST_FTDC_AF_Delete;
	///��Լ����
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
			ODS('M',SENDER,"�ܵ�����...");
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

///����֪ͨ
void session::OnRtnOrder(CThostFtdcOrderField *pOrder)
{

}
///�ɽ�֪ͨ
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
	ODS('M',SENDER,"%s�ѵǳ�...",pUserLogout->UserID);
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

