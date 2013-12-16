//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "OrderKeeper.h"
#include "uDatabase.h"
#include "UTrdItf_GTJA.h"
#include "uPriceFunc.h"

#include <system.hpp>
#include <SysUtils.hpp>
#include <Inifiles.hpp>

#pragma package(smart_init)

static encode_dll_wrapper _encode_dll;
//---------------------------------------------------------------------------
TTrdItf_GTJA::TTrdItf_GTJA(const char *psetupfile,ADDLOG plogfunc,bool createKeeper)
:TTrdItfBase(psetupfile,plogfunc)
{
	ZeroMemory(&FGTJASet,sizeof(TGTJASet));
	FHandle = NULL;
	FOrderDate = "";
	FAccountType = "";
	ZeroMemory(FEnPassword, 255);
	ZeroMemory(FCustid, 50);
	ZeroMemory(FBankCode,100);
    _createKeeper =  createKeeper;
}
//---------------------------------------------------------------------------
TTrdItf_GTJA::~TTrdItf_GTJA()
{
	this->CloseLink();
}

//---------------------------------------------------------------------------
int TTrdItf_GTJA::Init()  //��ʼ��
{
	FOrderDate = Date().FormatString("yyyymmdd");

	tagKCBPConnectOption stKCBPConnection;
	memset(&stKCBPConnection, 0 , sizeof(stKCBPConnection));

	strcpy(stKCBPConnection.szServerName, FGTJASet.ServerName);
	stKCBPConnection.nProtocal = 0;//
	strcpy(stKCBPConnection.szAddress, FGTJASet.ServerAddr);
	stKCBPConnection.nPort = FGTJASet.ServerPort;
	strcpy(stKCBPConnection.szSendQName, FGTJASet.SendQName/*"req1"*/);
	strcpy(stKCBPConnection.szReceiveQName, FGTJASet.ReceiveQName/*"ans1"*/);

	this->CloseLink();

	int nReturnCode;
	//�½�KCBPʵ��
	if( (nReturnCode=KCBPCLI_Init( &FHandle )) != 0 )
	{
		FHandle=NULL;
		ODS('M',PLUGINNAME, "KCBPCLI_Init error,code=%d",nReturnCode );
		return -1;
	}
	//ODS('M',PLUGINNAME, "KCBPCLI_Init");

	//����KCBP������
	if( (nReturnCode=KCBPCLI_SetConnectOption( FHandle, stKCBPConnection )) != 0)
	{
		KCBPCLI_Exit( FHandle );
		FHandle=NULL;
		ODS('M',PLUGINNAME, "KCBPCLI_SetConnectOption error,code=%d",nReturnCode );
		return -1;
	}
	//ODS('M',PLUGINNAME, "KCBPCLI_SetConnectOption");

	if( (nReturnCode=KCBPCLI_SetCliTimeOut( FHandle, FGTJASet.Timeout )) != 0)
	{
		KCBPCLI_Exit( FHandle );
		FHandle=NULL;
		ODS('M',PLUGINNAME, "KCBPCLI_SetCliTimeOut error,code=%d",nReturnCode );
		return -1;
	}
	//ODS('M',PLUGINNAME, "KCBPCLI_SetCliTimeOut");

	if((nReturnCode = KCBPCLI_ConnectServer( FHandle, stKCBPConnection.szServerName,
		FGTJASet.UserName, FGTJASet.Password)) !=0)
	{
		KCBPCLI_Exit( FHandle );
		FHandle=NULL;
		ODS('M',PLUGINNAME,"KCBPCLI_ConnectServer error,code=%d", nReturnCode);
		return -1;
	}
	//ODS('M',PLUGINNAME, "KCBPCLI_ConnectServer");



	return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_GTJA::GetStkAccount(char *LogType, char *Logid, char *ZJ, char *SH, char *SZ)//������ɶ��˺�
{
	char szFunid[] = "410301";

	if(InitRequest(szFunid, true) != 0)
		return -1;

	KCBPCLI_SetValue(FHandle, "inputtype", LogType);//��¼����	inputtype	char(1)	Y	����ע
	KCBPCLI_SetValue(FHandle, "inputid", Logid);//��¼��ʶ	inputid	char(64)	Y	����ע

	int nReturnCode = ExecuteRequest(szFunid);
	if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
	{
		return nReturnCode;
	}
	char szTmpbuf[20];
	if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
	{

		try
		{
			bool bFlag[2] = {false, false};
			while( !KCBPCLI_RsFetchRow(FHandle) )
			{
				if( KCBPCLI_RsGetColByName( FHandle, "market", szTmpbuf ) == 0)
				{
					if(lstrcmpi(szTmpbuf, "1") == 0 && !bFlag[0])
					{
						bFlag[0] = true;
						if( KCBPCLI_RsGetColByName( FHandle, "secuid", SH) != 0)
							return -1;
					}
					else if(lstrcmpi(szTmpbuf,this->FGTJASet.bencrypt==true ? "2":"0") == 0 && !bFlag[1])
					{
						bFlag[1] = true;
						if( KCBPCLI_RsGetColByName( FHandle, "secuid", SZ) != 0)
							return -1;
					}
				}
				else
					return -1;

				if(KCBPCLI_RsGetColByName( FHandle, "fundid", ZJ ) != 0)
					return -1;

				if(KCBPCLI_RsGetColByName( FHandle, "custid", FCustid ) != 0)
					return -1;

				if(KCBPCLI_RsGetColByName( FHandle, "bankcode", FBankCode ) != 0)
					return -1;

				//ODS('M',PLUGINNAME,"���д���:%s", FBankCode);

				if(bFlag[0] && bFlag[1])
					break;
			}
		}
		__finally
		{
			KCBPCLI_SQLCloseCursor(FHandle);
		}
	}
	else
		return -1;

	return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_GTJA::SetAccount() //�����ʺ�
{
	//ODS("---SetAccount");
	_encode_dll.lock();
	try
	{
		AnsiString sLogType = "Z", sLogid = FRequest.SetAccount.Account;
		char szSH[20] = {0x0, };
		char szSZ[20] = {0x0, };
		char szZJ[20] = {0x0, };

		FAccInfo.lt = FRequest.SetAccount.LoginType;
		lstrcpyn(FAccInfo.PW, FRequest.SetAccount.PW, PWD_LEN);//�ʺ�����

		memset(FEnPassword,0,255);
		//ZeroMemory(FEnPassword, 255);
		if(Encrypt(FRequest.SetAccount.PW, FEnPassword,"410301") != 0)
			return -1;

		if(FRequest.SetAccount.LoginType!= asCA)
		{
			sLogType = "N";
			if(strlen(FRequest.SetAccount.Account) > 0 && !isdigit(FRequest.SetAccount.Account[0]))
				sLogid = FRequest.SetAccount.Account+1;
		}

		int ret =  GetStkAccount(sLogType.c_str(), sLogid.c_str(), szZJ, szSH, szSZ) ;
		if( ret != 0)
			return ret;

		if(FRequest.SetAccount.LoginType==asSHA)
		{
			FAccountType = "1";
			lstrcpyn(FAccInfo.SH, szSH, ACC_LEN);
			lstrcpyn(FAccInfo.SZ, szSZ, ACC_LEN);
			lstrcpyn(FAccInfo.Capital, szZJ, ACC_LEN);//�ʽ��ʺ�
		}
		else if(FRequest.SetAccount.LoginType==asSZA)
		{
			FAccountType = "2";
			lstrcpyn(FAccInfo.SZ, szSZ, ACC_LEN);
			lstrcpyn(FAccInfo.SH, szSH, ACC_LEN);
			lstrcpyn(FAccInfo.Capital, szZJ, ACC_LEN);//�ʽ��ʺ�
		}
		else if(FRequest.SetAccount.LoginType == asCA)//�ʽ��ʺ�
		{
			FAccountType = "";
			lstrcpyn(FAccInfo.SH, szSH, ACC_LEN);
			lstrcpyn(FAccInfo.SZ, szSZ, ACC_LEN);
			lstrcpyn(FAccInfo.Capital, szZJ, ACC_LEN);//�ʽ��ʺ�
		}
		else
		{
			ODS('M',PLUGINNAME,"��Ч���û��ʺ�����:%c", FRequest.SetAccount.LoginType);
			return -1;
		}

		NewAns(1);
		memcpy(&((*FAnswer)[0].SetAccount.AccountInfo),&FAccInfo,sizeof(TAccountInfo));

		//ZeroMemory(FEnPassword, 255);
		memset(FEnPassword,0,255);
		Encrypt(FRequest.SetAccount.PW, FEnPassword, FCustid);

        if( _createKeeper )
        {
            order_keeper_manager::instance()->start_keeper(this->FSetupFile,get_callback_fun(),
                &FRequest.SetAccount);
        }
		//ODS("---SetAccount--end");
	}
	__finally
	{
		_encode_dll.unlock();
	}
	return 0;
}

//---------------------------------------------------------------------------
int TTrdItf_GTJA::QryMoney()     //�ʽ��ѯ
{
	char szFunid[] = "410530";
	if(InitRequest(szFunid) != 0)
		return -1;

	KCBPCLI_SetValue(FHandle, "fundid", "-1");//�ʽ��˺�
	KCBPCLI_SetValue(FHandle, "moneytype",
		ConvertMoneyType(FRequest.QryMoney.MoneyType)); //0	�����

	int nReturnCode = ExecuteRequest(szFunid);
	if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
		return nReturnCode;

	char szTmpbuf[20];
	if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
	{
		try
		{
			if( KCBPCLI_RsFetchRow(FHandle) == 0)
			{
				NewAns(1);
				if( KCBPCLI_RsGetColByName( FHandle, "marketvalue", szTmpbuf ) == 0)
					(*FAnswer)[0].QryMoney.MoneyInfo.balance = StrToFloat(szTmpbuf);//�ʽ����
				else
					return -1;

				if( KCBPCLI_RsGetColByName( FHandle, "fundavl", szTmpbuf ) == 0)
					(*FAnswer)[0].QryMoney.MoneyInfo.available = StrToFloat(szTmpbuf);
				else
					return -1;

				if( KCBPCLI_RsGetColByName( FHandle, "moneytype", szTmpbuf ) == 0)
					(*FAnswer)[0].QryMoney.MoneyInfo.MoneyType = ConvertMoneyType(szTmpbuf);
				else
					return -1;
			}
			else
				return -1;
		}
		__finally
		{
			KCBPCLI_SQLCloseCursor(FHandle);
		}
	}
	else
		return -1;

	return 0;
}

//---------------------------------------------------------------------------
const char* get_field(TStrings *FDstList,int row,int col,int nFieldCount)
{
    assert( FDstList != NULL );
    return  AnsiString(FDstList->Strings[row*nFieldCount+col].Trim()).c_str() ;
}

int TTrdItf_GTJA::QryCurCsn()    //����ί�в�ѯ
{
	char szFunid[] = "410510";

    TStrings *FSrcList, *FDstList;
	FSrcList = new TStringList();
	FDstList = new TStringList();

    try
    {

	AnsiString sPoststr = FRequest.QryCurCsn.SeqNum;
	int nReturnCode = -1;//-1��ʾ��һ�ν���ѭ��
	const int nFieldCount = 15;
	FSrcList->Add("ordersno");
	FSrcList->Add("stkcode");
	FSrcList->Add("stkname");
	FSrcList->Add("market");
	FSrcList->Add("opertime");
	FSrcList->Add("orderdate");
	FSrcList->Add("bsflag");
	FSrcList->Add("orderstatus");
	FSrcList->Add("orderqty");
	FSrcList->Add("matchqty");
	FSrcList->Add("cancelqty");
	FSrcList->Add("orderprice");
	FSrcList->Add("matchamt");
	FSrcList->Add("secuid");
	FSrcList->Add("poststr");

	while(nReturnCode == -1 || nReturnCode == 100 || nReturnCode == 0)
	{
		if(InitRequest(szFunid) != 0)
			return -1;

		//qryflagʵ��Ӧ��һֱ��1���ĵ�����
		KCBPCLI_SetValue(FHandle, "market", "");//FAccountType.c_str());//�����г�		char(1)	N	���Ͳ�ѯȫ��
		KCBPCLI_SetValue(FHandle, "fundid", this->FAccInfo.Capital);//�ʽ��ʻ�		int	N
		KCBPCLI_SetValue(FHandle, "secuid", "");//sStkAcc.c_str());//�ɶ�����		char(10)	N	���Ͳ�ѯȫ��
		KCBPCLI_SetValue(FHandle, "stkcode", "");//֤ȯ����		char(8)	N	���Ͳ�ѯȫ��
		KCBPCLI_SetValue(FHandle, "ordersno", FRequest.QryCurCsn.OrderID);//ί�����	Ordersno	int	N	���Ͳ�ѯȫ��
		KCBPCLI_SetValue(FHandle, "bankcode",FBankCode);//�ⲿ����	Bankcode	char(4)	N	��������ʱ��
		KCBPCLI_SetValue(FHandle, "qryflag", "1");//(nReturnCode==-1?"1":"0"));//��ѯ����		char(1) 	Y	����/���ϲ�ѯ����,��һ�β�ѯ��1
		KCBPCLI_SetValue(FHandle, "count", AnsiString(IntToStr((int)FRequest.QryCurCsn.MaxRecord)).c_str());//��������		int 	Y	ÿ��ȡ������
		KCBPCLI_SetValue(FHandle, "poststr", sPoststr.c_str());//��λ��  		char(32)	Y	��һ�����

		nReturnCode = ExecuteRequest(szFunid);//����0Ҳ�����Ƕ��������ĵ���û���ἰ��
		if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
		{
			return nReturnCode;
		}
		int nReturnRow = QueryMoreResults(FSrcList, FDstList);
		if(nReturnRow == 0)
			break;
		else if(nReturnRow < 0)
		{
			ODS('M',PLUGINNAME," else if(nReturnRow < 0)");
			return -1;
		}
		else if(nReturnRow < FRequest.QryCurCsn.MaxRecord && nReturnCode != 100)//�����Ǳ��ĵ�ʵ��ֵ�û��ɣ����ǰ�ȫһ���
			break;


		if(FDstList->Count > 0)
			sPoststr = FDstList->Strings[FDstList->Count - 1];

		break;
	}

	if(FDstList->Count >= nFieldCount)
	{
		int nRows = FDstList->Count/nFieldCount;
		NewAns(nRows);

		//set value;
		for(int i=0; i<nRows; i++)
		{
			TOrderInfo *pConsInfo = &(*FAnswer)[i].QryCurCsn.OrderInfo;

			strcpy(pConsInfo->ContractID, get_field(FDstList,i,0,nFieldCount));//��ͬ���
			pConsInfo->Market = ConvertMarketType(get_field(FDstList,i,3,nFieldCount));
			lstrcpyn(pConsInfo->SecuID, get_field(FDstList,i,1,nFieldCount), CODE_LEN);//֤ȯ����
			pConsInfo->Time=ConvertTimeToInt(get_field(FDstList,i,4,nFieldCount));//ί��ʱ��
			pConsInfo->Date=ConvertDateToInt(get_field(FDstList,i,5,nFieldCount));//ί������
			pConsInfo->Type = ConvertOrderType(get_field(FDstList,i,6,nFieldCount));//�������
			pConsInfo->State = ConvertOrderState(get_field(FDstList,i,7,nFieldCount));///����״̬---��θ�ֵ
			pConsInfo->CsnVol = StrToInt(get_field(FDstList,i,8,nFieldCount));//ί������
			pConsInfo->TrdVol = StrToInt(get_field(FDstList,i,9,nFieldCount));//�ɽ�����
			pConsInfo->CancelVol = -StrToInt(get_field(FDstList,i,10,nFieldCount));//��������=��ֵ
			pConsInfo->CsnPrice = StrToFloat(get_field(FDstList,i,11,nFieldCount));//ί�м۸�
			pConsInfo->TrdPrice = (pConsInfo->TrdVol >0 ? StrToFloat(get_field(FDstList,i,12,nFieldCount))/pConsInfo->TrdVol : 0);//�ɽ��۸�---???�ṹ����û����Ӧ�ֶ�
			lstrcpyn(pConsInfo->Account,get_field(FDstList,i,13,nFieldCount),ACC_LEN);
			lstrcpyn(pConsInfo->SeqNum,get_field(FDstList,i,14,nFieldCount),SEQ_LEN);
		}
	}
    }
    __finally
    {
        delete FSrcList;
	    delete FDstList;
    }
	return 0;
}

//---------------------------------------------------------------------------
int TTrdItf_GTJA::QryCurTrd()    //���ճɽ���ѯ
{
    if( strcmp(FRequest.QryCurTrd.OrderID,"-100")==0)  // ���-100���ǹ��ڲ���ɽ���
    {
        char szFunid[] = "410512";
        int machtype;
        AnsiString sPoststr = FRequest.QryCurTrd.SeqNum;
        int nReturnCode = -1;//-1��ʾ��һ�ν���ѭ��
        const int nFieldCount = 13;

        TStrings *FSrcList, *FDstList;
        FSrcList = new TStringList();
        FDstList = new TStringList();

        try
        {

        FSrcList->Add("market");
        FSrcList->Add("stkcode");
        FSrcList->Add("stkname");
        FSrcList->Add("matchtime");
        FSrcList->Add("trddate");
        FSrcList->Add("bsflag");
        FSrcList->Add("matchqty");
        FSrcList->Add("matchprice");
        FSrcList->Add("matchtype");
        FSrcList->Add("matchcode");
        FSrcList->Add("ordersno");
        FSrcList->Add("poststr");
        FSrcList->Add("secuid");

        while(nReturnCode == -1 || nReturnCode == 100 || nReturnCode == 0)
        {
            if(InitRequest(szFunid) != 0)
                return -1;

            KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//�ʽ��ʻ�		int	N
            KCBPCLI_SetValue(FHandle, "market", "");//FAccountType.c_str());//�����г�		char(1)	N	���Ͳ�ѯȫ��
            KCBPCLI_SetValue(FHandle, "secuid", "");//sStkAcc.c_str());//�ɶ�����		char(10)	N	���Ͳ�ѯȫ��
            KCBPCLI_SetValue(FHandle, "stkcode", "");//֤ȯ����		char(8)	N	���Ͳ�ѯȫ��
            //KCBPCLI_SetValue(FHandle, "ordersno", FRequest.QryCurTrd.OrderID);//ί�����	Ordersno	int	N	���Ͳ�ѯȫ��
            KCBPCLI_SetValue(FHandle, "ordersno", "");
            KCBPCLI_SetValue(FHandle, "bankcode", FBankCode);//�ⲿ����	Bankcode	char(4)	N	��������ʱ��
            KCBPCLI_SetValue(FHandle, "qryflag", "1");//(nReturnCode==-1?"1":"0"));//��ѯ����		char(1) 	Y	����/���ϲ�ѯ����,��һ�β�ѯ��1
            KCBPCLI_SetValue(FHandle, "count", AnsiString(IntToStr((int)FRequest.QryCurTrd.MaxRecord)).c_str());//��������		int 	Y	ÿ��ȡ������
            KCBPCLI_SetValue(FHandle, "poststr", sPoststr.c_str());//��λ��  		char(32)	Y	��һ�����

            nReturnCode = ExecuteRequest(szFunid);
            if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
                return nReturnCode;

            int nReturnRow = QueryMoreResults(FSrcList, FDstList);
            if(nReturnRow == 0)
                break;
            else if(nReturnRow < 0)
                return -1;
            else if(nReturnRow < FRequest.QryCurTrd.MaxRecord && nReturnCode != 100)//�����Ǳ��ĵ�ʵ��ֵ�û��ɣ����ǰ�ȫһ���
                break;


            if(FDstList->Count > 0)
                sPoststr = FDstList->Strings[FDstList->Count - 1];

            break;
        }

        if(FDstList->Count >= nFieldCount)
        {
            int nRows = FDstList->Count/nFieldCount;
            NewAns(nRows);

            //set value;
            for(int i=0; i<nRows; i++)
            {
                TTradeInfo *pTrdInfo = &((*FAnswer)[i].QryCurTrd.TrdInfo);
                lstrcpyn(pTrdInfo->ContractID,get_field(FDstList,i,10,nFieldCount),SEQ_LEN);
                lstrcpyn(pTrdInfo->TrdID,get_field(FDstList,i,9,nFieldCount),SEQ_LEN);
                pTrdInfo->Market = ConvertMarketType(get_field(FDstList,i,0,nFieldCount));
                lstrcpyn(pTrdInfo->SecuID, get_field(FDstList,i,1,nFieldCount), CODE_LEN);//֤ȯ����
                pTrdInfo->Time = ConvertTimeToInt(get_field(FDstList,i,3,nFieldCount));//�ɽ�ʱ��
                pTrdInfo->Date = ConvertDateToInt(get_field(FDstList,i,4,nFieldCount));//ί������
                pTrdInfo->Type = ConvertOrderType(get_field(FDstList,i,5,nFieldCount));//�������
                pTrdInfo->Vol = StrToInt(get_field(FDstList,i,6,nFieldCount));//�ɽ�����
                pTrdInfo->Price = StrToFloat(get_field(FDstList,i,7,nFieldCount));//�ɽ��۸�
                machtype = StrToIntDef(get_field(FDstList,i,8,nFieldCount),-1) ;
                if( machtype != 0 )
                    pTrdInfo->Vol = -pTrdInfo->Vol;
                lstrcpyn(pTrdInfo->SeqNum,get_field(FDstList,i,11,nFieldCount),SEQ_LEN);
                lstrcpyn(pTrdInfo->Account,get_field(FDstList,i,12,nFieldCount),ACC_LEN);
            }
        }
        }
        __finally
        {
            delete FSrcList;
            delete FDstList;
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
                //������ѯ
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
//---------------------------------------------------------------------------
int TTrdItf_GTJA::QryStocks()    //��ѯ�ʺ������еĹɷ�
{
	char szFunid[] = "410503";

	AnsiString sPoststr = "";
	int nReturnCode = -1;//-1��ʾ��һ�ν���ѭ��

	TStrings *FSrcList, *FDstList;
	FSrcList = new TStringList();
	FDstList = new TStringList();
    try
    {

	const int nFieldCount = 13;
	FSrcList->Add("market");
	FSrcList->Add("stkcode");
	FSrcList->Add("stkname");
	FSrcList->Add("stkbal");
	FSrcList->Add("stkavl");
	FSrcList->Add("buycost");
	FSrcList->Add("costprice");
	FSrcList->Add("mktval");
	FSrcList->Add("lastprice");
	FSrcList->Add("income");
	FSrcList->Add("secuid");
	FSrcList->Add("stkqty");
	FSrcList->Add("poststr");

	AnsiString sStkAcc = this->GetStockAccountByMarket(FRequest.QryStocks.Market);
	AnsiString sMarket = ConvertMarketType(FRequest.QryStocks.Market);

	while(nReturnCode == -1 || nReturnCode == 100 || nReturnCode == 0)
	{
		if(InitRequest(szFunid) != 0)
			return -1;

		KCBPCLI_SetValue(FHandle, "market", sMarket.c_str());//FAccountType.c_str());//�����г�	market	char(1)	N	���Ͳ�ѯȫ��
		KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//�ʽ��ʻ�		int	N
		KCBPCLI_SetValue(FHandle, "secuid", "");//sStkAcc.c_str());//�ɶ�����		char(10)	N	���Ͳ�ѯȫ��
		KCBPCLI_SetValue(FHandle, "stkcode", "");//֤ȯ����		char(8)	N	���Ͳ�ѯȫ��
		KCBPCLI_SetValue(FHandle, "qryflag", "1");//(nReturnCode==-1?"1":"0"));//��ѯ����		char(1) 	Y	����/���ϲ�ѯ����,��һ�β�ѯ��1
		KCBPCLI_SetValue(FHandle, "count", GTJA_MAX_REC_NUM);//��������		int 	Y	ÿ��ȡ������
		KCBPCLI_SetValue(FHandle, "poststr", sPoststr.c_str());//��λ��  		char(32)	Y	��һ�����

		nReturnCode = ExecuteRequest(szFunid);
		if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
			return nReturnCode;

		int nReturnRow = QueryMoreResults(FSrcList, FDstList);
		if(nReturnRow == 0)
			break;
		else if(nReturnRow < 0)
			return -1;
		else if(nReturnRow < GTJA_MAX_REC_NUM_INT && nReturnCode != 100)//�����Ǳ��ĵ�ʵ��ֵ�û��ɣ����ǰ�ȫһ���
			break;


		if(FDstList->Count > 0)
			sPoststr = FDstList->Strings[FDstList->Count - 1];

	}

	if(FDstList->Count >= nFieldCount)
	{
		int nRows = FDstList->Count/nFieldCount;
		NewAns(nRows);
		//set value;
		for(int i=0; i<nRows; i++)
		{
			TStockInfo *pStock = &(*FAnswer)[i].QryStocks.StockInfo;

			pStock->PosDir = pdNet;
			pStock->Market = ConvertMarketType(get_field(FDstList,i,0,nFieldCount));
			lstrcpyn(pStock->SecuID, get_field(FDstList,i,1,nFieldCount), CODE_LEN);//֤ȯ����
			lstrcpyn(pStock->Account,get_field(FDstList,i,10,nFieldCount),ACC_LEN);

			pStock->PosNum = StrToIntDef(FDstList->Strings[i*nFieldCount+11].Trim(), 0);
			pStock->Balance = StrToIntDef(FDstList->Strings[i*nFieldCount+3].Trim(), 0);//���
			pStock->Available = StrToIntDef(FDstList->Strings[i*nFieldCount+4].Trim(), 0);//������
			pStock->CostPrice = StrToFloatDef(FDstList->Strings[i*nFieldCount+6].Trim(),0);//�ο��ɱ���
			pStock->CurPrice = StrToFloatDef(FDstList->Strings[i*nFieldCount+8].Trim(),0);//�ο��м�
		}
	}
    }
    __finally
    {
        delete FSrcList;
	    delete FDstList;
    }
	return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_GTJA::Undo() //ί�г���
{
    if( FRequest.Undo.ContractID[0] == '\0' || FRequest.Undo.ContractID[0] == '-' )
    {
        return -1;
    }

	char szFunid[] = "410413";
	if(InitRequest(szFunid) != 0)
		return -1;

	KCBPCLI_SetValue(FHandle, "orderdate", FOrderDate.c_str());//ί������	orderdate	int	Y
	KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//�ʽ��˻�	fundid	int	Y
	KCBPCLI_SetValue(FHandle, "ordersno", FRequest.Undo.ContractID);//ί�����	ordersno	int	Y	ί�з��ص�

	int nReturnCode = ExecuteRequest(szFunid);
	if( nReturnCode != 0)
	{
		ODS('M',PLUGINNAME,"Undo ExecuteRequest=%d", nReturnCode);
		if( -410413020 ==  nReturnCode )
			return ERR_UNDO_CANNOT_CANCLE;
		else
			return nReturnCode;
	}

	char szTmpbuf[20];
	if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
	{
		try
		{
			if( KCBPCLI_RsFetchRow(FHandle) != 0)
				return -1;
		}
		__finally
		{
			KCBPCLI_SQLCloseCursor(FHandle);
		}
	}
	else
		return -1;

	return 0;
}
//---------------------------------------------------------------------------

int  TTrdItf_GTJA::Order()
{
	//ע��������ʽ��˺ŵ�½��Ҫ��ȡ����֤����֤�ɶ��˺ţ�����������Ʊ���ܳ���
	char szFunid[] = "410411";
	if(InitRequest(szFunid) != 0)
		return -1;

	KCBPCLI_SetValue(FHandle, "market", ConvertMarketType(FRequest.Order.Market));
	KCBPCLI_SetValue(FHandle, "secuid", this->GetStockAccountByMarket(FRequest.Order.Market));

	AnsiString sPrice;
	if( AnsiPos(AnsiString("510"),FRequest.Order.SecuID ) == 1 ||
		AnsiPos(AnsiString("1599"),FRequest.Order.SecuID ) == 1 )
	{
		sPrice  = ConvetDoubleToPrice( FRequest.Order.Price,3);
		//ODS("%s,%s",FRequest.Order.SecuID,sPrice.c_str());
	}
	else
	{
		sPrice  = ConvetDoubleToPrice( FRequest.Order.Price,2);
		//ODS("%s,%s",FRequest.Order.SecuID,sPrice.c_str());
	}

	KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//�ʽ��˻�	fundid	int	Y
	KCBPCLI_SetValue(FHandle, "stkcode", FRequest.Order.SecuID);//֤ȯ����	stkcode	char(8)	Y
	KCBPCLI_SetValue(FHandle, "bsflag", ConvertOrderType(FRequest.Order.Type));//�������	bsflag	char(1)	Y	B:����S:����  3�����깺 4�������
	KCBPCLI_SetValue(FHandle, "price", sPrice.c_str());//�۸�	price	numeric(9,3)	Y
	KCBPCLI_SetValue(FHandle, "qty", AnsiString(IntToStr(FRequest.Order.Num)).c_str());//����	qty	int	Y
	KCBPCLI_SetValue(FHandle, "ordergroup", "-1"/*"0"*/);//ί������	ordergroup	int	Y	0,
	KCBPCLI_SetValue(FHandle, "bankcode",FBankCode);//�ⲿ����	bankcode	char(4)	N	��������ʱ��
	KCBPCLI_SetValue(FHandle, "remark", "");//��ע��Ϣ	remark	char(64)	N

	int nReturnCode = ExecuteRequest(szFunid);
	if( nReturnCode != 0)
	{
		return nReturnCode;
	}

	char szTmpbuf[20];
	if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
	{
		try
		{
			if( KCBPCLI_RsFetchRow(FHandle) == 0)
			{
				if( KCBPCLI_RsGetColByName( FHandle, "ordersno", szTmpbuf ) == 0) //ί�����	ordersno	int	���ظ�����
                {
                    NewAns(1);
					lstrcpyn((*FAnswer)[0].Order.ContractID ,szTmpbuf,SEQ_LEN);
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
                        //order_man.add_order(op);
                    }
                    catch( std::string &err)
                    {
                        SetLastError(-1,'E',PLUGINNAME,"����ί�е��������ݿ�ʧ��:%s",err.c_str());
                        return -1;
                    }
				}
                else
					return -1;
			}
			else
				return -1;
		}
		__finally
		{
			KCBPCLI_SQLCloseCursor(FHandle);
		}
	}
	else
		return -1;

	return 0;
}
//---------------------------------------------------------------------------

int TTrdItf_GTJA::SetSytemParams(char *Funid, bool IsLogin)
{
	int nReturnCode = KCBPCLI_SetSystemParam(FHandle, KCBP_PARAM_RESERVED, FGTJASet.DptCode);//��������Ӫҵ������
	if(nReturnCode != 0)   
	{
		ODS('M',PLUGINNAME,"KCBPCLI_SetSystemParam ErrCode=%d", nReturnCode);
		return -1;
	}

	if(!IsLogin)
	{
		KCBPCLI_SetValue(FHandle, "funcid", Funid);//���ܺ�, ������,������Ϊ��
		KCBPCLI_SetValue(FHandle, "custid", FCustid);//�ͻ�����,  ����Ϊ��119353,517486
		KCBPCLI_SetValue(FHandle, "custorgid", FGTJASet.DptCode);//�ͻ�����, ����Ϊ��
		KCBPCLI_SetValue(FHandle, "trdpwd", FEnPassword);//��������, ����Ϊ��
		KCBPCLI_SetValue(FHandle, "netaddr", FGTJASet.MAC.c_str());//FGTJASet.ServerAddr);//����վ��, �����ͣ�������Ϊ��
		KCBPCLI_SetValue(FHandle, "orgid", FGTJASet.DptCode);//��������, �����ͣ�������Ϊ��
		KCBPCLI_SetValue(FHandle, "operway", AnsiString(FGTJASet.Operway).c_str());//������ʽ, �����ͣ�������Ϊ��
		KCBPCLI_SetValue(FHandle, "ext", "");//��չ�ֶ�, �����ͣ�����Ϊ��
	}
	else
	{
		KCBPCLI_SetValue(FHandle, "funcid", Funid);//���ܺ�, ������,������Ϊ��
		KCBPCLI_SetValue(FHandle, "custid", "");//�ͻ�����,  ����Ϊ�� 28014444,8237964
		KCBPCLI_SetValue(FHandle, "custorgid", "");//�ͻ�����, ����Ϊ��
		KCBPCLI_SetValue(FHandle, "trdpwd", FEnPassword);//��������, ����Ϊ��
		KCBPCLI_SetValue(FHandle, "netaddr", FGTJASet.MAC.c_str());//FGTJASet.ServerAddr);//����վ��, �����ͣ�������Ϊ��
		KCBPCLI_SetValue(FHandle, "orgid", FGTJASet.DptCode);//��������, �����ͣ�������Ϊ��
		KCBPCLI_SetValue(FHandle, "operway", AnsiString(FGTJASet.Operway).c_str()/*"0"*/);//������ʽ, �����ͣ�������Ϊ��
		KCBPCLI_SetValue(FHandle, "ext", "");//��չ�ֶ�, �����ͣ�����Ϊ��
	}

	return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_GTJA::CheckSqlExecute(void)
{
	int nErrCode = 0;
	char szErrMsg[256];

	if(KCBPCLI_GetErr(FHandle, &nErrCode, szErrMsg) == 0)
	{
		if(nErrCode != 0)
		{
			szErrMsg[255] = '\0';
			ODS('M',PLUGINNAME,"CheckSqlExecute,ErrCode:%d, ErrMsg:%s", nErrCode, szErrMsg );
			lstrcpyn(this->FLastError.Sender,"GTJAJZX",SEQ_LEN);
			this->FLastError.ErrorCode = nErrCode;
			lstrcpyn(this->FLastError.Text,szErrMsg,MAX_TEXT);
			return nErrCode;
		}
	}

	return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_GTJA::CheckRsOpen(void)
{
	int nCol = 0;
	KCBPCLI_SQLNumResultCols(FHandle, &nCol); ///////////////
	if(KCBPCLI_SQLFetch(FHandle) != 0)
	{
		ODS('M',PLUGINNAME, "KCBPCLI_SQLFetch error!" );
		return -1;
	}

	char szTmpbuf[1024];
	if( KCBPCLI_RsGetColByName( FHandle, "CODE", szTmpbuf ) != 0)
	{
		ODS('M',PLUGINNAME, "Get CODE Fail\n" );
		return -1;
	}

	if( strcmp(szTmpbuf, "0") != 0 )
	{
		AnsiString sErrMsg = "";
		sErrMsg.cat_printf( "CheckRsOpen,error code :%s ", szTmpbuf );
		KCBPCLI_RsGetColByName( FHandle, "LEVEL", szTmpbuf );
		sErrMsg.cat_printf( "error level :%s ", szTmpbuf );
		KCBPCLI_RsGetColByName( FHandle, "MSG", szTmpbuf );
		sErrMsg.cat_printf( "error msg :%s\n", szTmpbuf );

		ODS('M',PLUGINNAME,sErrMsg.c_str());
		lstrcpyn(this->FLastError.Sender,"GTJAJZX",SEQ_LEN);
		this->FLastError.ErrorCode = atoi(szTmpbuf);
		lstrcpyn(this->FLastError.Text,sErrMsg.c_str(),MAX_TEXT);
		return this->FLastError.ErrorCode;
	}

	return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_GTJA::InitRequest(char *Funid, bool IsLogin)
{
	/*��ʼ���������������*/
	int nReturnCode = KCBPCLI_BeginWrite(FHandle);
	if( nReturnCode !=0 ) 
	{
		ODS('M',PLUGINNAME,"KCBPCLI_BeginWrite ErrCode=%d", nReturnCode);
		return -1;
	}

	if(SetSytemParams(Funid, IsLogin) != 0)
		return -1;

	return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_GTJA::ExecuteRequest(char *Funid)
{
	/*�ͻ�����������ύ����*/
	int nReturnCode  = KCBPCLI_SQLExecute(FHandle, Funid);//

	if(nReturnCode>2000)
	{
		ODS('E',PLUGINNAME,"KCBPCLI_SQLExecute=%d",nReturnCode);
		return ERR_REMOTE_OTHER_FAILED;
	}

	if( CheckSqlExecute()!=0 )
	{
		return ERR_REMOTE_OTHER_FAILED;
	}

	nReturnCode = KCBPCLI_RsOpen(FHandle);
	if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
	{
		ODS('M',PLUGINNAME,"KCBPCLI_RsOpen ErrCode=%d", nReturnCode);
		return ERR_REMOTE_OTHER_FAILED;
	}

	return  CheckRsOpen() ;
}
//---------------------------------------------------------------------------
int TTrdItf_GTJA::QueryMoreResults(TStrings *pSrcList, TStrings *pDstList)
{
	int nRows = 0, nCol = 0;;
	char szTmpbuf[100] = {0x0, };
	if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
	{
		try
		{
			KCBPCLI_SQLNumResultCols(FHandle, &nCol);
			while( !KCBPCLI_RsFetchRow(FHandle) )
			{
				for(int i=0; i<pSrcList->Count; i++ )
				{
					if(KCBPCLI_RsGetColByName( FHandle,
                        AnsiString(pSrcList->Strings[i]).c_str(),
                        szTmpbuf ) == 0)
						pDstList->Add(szTmpbuf);
					else
					{
						ODS('M',PLUGINNAME,"KCBPCLI_RsGetColByName(%s) != 0", pSrcList->Strings[i].c_str());
						return -1;
					}
				}
				nRows++;
			}
		}
		__finally
		{
			KCBPCLI_SQLCloseCursor(FHandle);
		}
	}

	//ODS('M',PLUGINNAME,"%s", pDstList->Text.c_str());
	return nRows;
}
//---------------------------------------------------------------------------
int TTrdItf_GTJA::Encrypt(char *pSrc, char *pDst, char *key)
{
	return _encode_dll.Encrypt(pSrc,pDst,key,FGTJASet.bencrypt);
}
//---------------------------------------------------------------------------

void TTrdItf_GTJA::CloseLink(void)
{
	lock();
	if(FHandle != NULL)
	{
		try
		{
			KCBPCLI_DisConnect( FHandle);
			KCBPCLI_Exit( FHandle );
			//ODS('M',PLUGINNAME, "KCBPCLI_Exit");
		}
		catch(Exception &e)
		{
			ODS('M',PLUGINNAME,"CloseLink error,%s",e.Message);
		}
		FHandle = NULL;
	}
	unlock();
	TTrdItfBase::CloseLink();
    //order_keeper_manager::instance()->stop_keeper(&FRequest.SetAccount);
	//ODS('M',PLUGINNAME,"CloseLink");
}

int  TTrdItf_GTJA::KeepAlive(void)
{
	lock();
	try
	{
		if(FHandle==NULL || FHasSetAccInfo==false) return -1;

		char szFunid[] = "410530";
		if(InitRequest(szFunid) != 0)
			return -1;

		KCBPCLI_SetValue(FHandle, "fundid",FAccInfo.Capital );//�ʽ��˺�
		KCBPCLI_SetValue(FHandle, "moneytype", "0"); //0	�����

		int nReturnCode = ExecuteRequest(szFunid);
		if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
			return nReturnCode;

		char szTmpbuf[20];
		if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
		{
			try
			{
				if( KCBPCLI_RsFetchRow(FHandle) == 0)
				{
					AnsiString txt="-Keep Alive-";
					/*
					if( KCBPCLI_RsGetColByName( FHandle, "custid", szTmpbuf ) == 0)
					txt.cat_printf("�ͻ�����:%s,",szTmpbuf);
					if( KCBPCLI_RsGetColByName( FHandle, "fundid", szTmpbuf ) == 0)
					txt.cat_printf("�ʽ��˻�:%s," , szTmpbuf);
					if( KCBPCLI_RsGetColByName( FHandle, "orgid", szTmpbuf ) == 0)
					txt.cat_printf("��������:%s," , szTmpbuf);
					if( KCBPCLI_RsGetColByName( FHandle, "moneytype", szTmpbuf ) == 0)
					txt.cat_printf("����:%s," , szTmpbuf);
					if( KCBPCLI_RsGetColByName( FHandle, "fundbal", szTmpbuf ) == 0)
					txt.cat_printf("���:%s," , szTmpbuf);
					if( KCBPCLI_RsGetColByName( FHandle, "fundavl", szTmpbuf ) == 0)
					txt.cat_printf("���ý��:%s," , szTmpbuf);
					if( KCBPCLI_RsGetColByName( FHandle, "marketvalue", szTmpbuf ) == 0)
					txt.cat_printf("�ʲ���ֵ:%s," , szTmpbuf);
					if( KCBPCLI_RsGetColByName( FHandle, "fund", szTmpbuf ) == 0)
					txt.cat_printf("�ʽ��ʲ�:%s," , szTmpbuf);
					if( KCBPCLI_RsGetColByName( FHandle, "stkvalue", szTmpbuf ) == 0)
					txt.cat_printf("��ֵ:%s," , szTmpbuf);
					if( KCBPCLI_RsGetColByName( FHandle, "fundseq", szTmpbuf ) == 0)
					txt.cat_printf("���ʽ��־:%s,", szTmpbuf);
					if( KCBPCLI_RsGetColByName( FHandle, "maxdraw", szTmpbuf ) == 0)
					txt.cat_printf("��ȡ���:%s." , szTmpbuf);
					*/
					ODS('M',PLUGINNAME,txt.c_str());
				}
				else
					return -1;
			}
			__finally
			{
				KCBPCLI_SQLCloseCursor(FHandle);
			}
		}
		else
			return -1;

	}
	__finally
	{
		unlock();
	}

	return 0;
}

market_type  TTrdItf_GTJA::ConvertMarketType(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return mtNo;

	if( FGTJASet.SHA == t ) return mtSHA;
	else if( FGTJASet.SZA == t) return mtSZA;
	return mtNo;
}

order_type   TTrdItf_GTJA::ConvertOrderType(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return otNo;
	switch (t[0]) {
		case 'B': return otBuy;
		case 'S': return otSell;
		case '1': return otETFSub;
		case '2': return otETFRed;
		default:
			return otNo;
	}
}

order_state  TTrdItf_GTJA::ConvertOrderState(const char *t)
{
	//'0','δ��' ��lbm��ί�гɹ�д��δ����־
	//'1','����' ����ط�ʽ��,����ɨ��δ��ί��,����ί����Ϊ����״̬
	//'2','�ѱ�' ���̳ɹ���,���̻���д���ͱ�־Ϊ�ѱ�
	//'3','�ѱ�����' �ѱ�ί�г���
	//'4','���ɴ���' ���ֳɽ���ί�г���
	//'5','����' ���ֳɽ��󳷵��ɽ�
	//'6','�ѳ�' ȫ�������ɽ�
	//'7','����' �ѱ�ί�в��ֳɽ�
	//'8','�ѳ�' ί�л򳷵�ȫ���ɽ�
	//'9','�ϵ�' ί��ȷ��Ϊ�ѵ� 'A','����' 'B','����' ��̩ģʽ�У��ѱ����ӿڿ���δ�����ؿ�Ľ׶Σ���׼ģʽ���á�
	if(t==NULL || strlen(t)<1 ) return osno;
	switch(t[0])
	{
	case '0':
	case '1':
	case 'A':
	case 'B':
		return oswb;
	case '2':
		return osyb;
	case '3':
	case '4':
		return osdc;
	case '5':
		return osbw;
	case '6':
		return osyc;
	case '7':
		return osbc;
	case '8':
		return oscj;
	case '9':
		return osyf;
	default:
		return osno;
	}
}

pos_direction TTrdItf_GTJA::ConvertPosDir(const char *t)
{
	return pdNet;
}

money_type   TTrdItf_GTJA::ConvertMoneyType(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return motNo;
	switch (t[0]) {
		case '0':return motRMB;
		case '1':return motUSD;
		case '2':return motHKD;
		default:
			return motNo;
	}
}

char *  TTrdItf_GTJA::ConvertMarketType(market_type t)
{
	switch (t) {
		case mtSHA : return FGTJASet.SHA.c_str();
		case mtSZA : return FGTJASet.SZA.c_str();
		default:
			return "";
	}
}

char *  TTrdItf_GTJA::ConvertOrderType(order_type t)
{
	switch (t) {
	case 	otBuy      : return "B";
	case 	otSell     : return "S";
	case 	otETFSub   : return "1";
	case 	otETFRed   : return "2";
	default:
		return "";
	}
}

char *  TTrdItf_GTJA::ConvertOrderState(order_state t)
{
	return "";
}

char *  TTrdItf_GTJA::ConvertPosDir(pos_direction t)
{
	return "";
}

char *  TTrdItf_GTJA::ConvertMoneyType(money_type t)
{
	switch (t) {
	case motRMB: return "0";
	case motUSD: return "1";
	case motHKD: return "2";
	default:
		return "";
	}
}

bool TTrdItf_GTJA::GetConfig(void)
{
	if( FSetupFile== NULL ) return false;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		// �ж��Ƿ���ڲ�������ã�û�еĻ�����false�Ա�ϵͳ�ܹ�����Ĭ�ϵ�����
		if( ini->SectionExists(PLUGINNAME) == false ) return false;
		lstrcpyn(FGTJASet.ServerName,
			AnsiString(ini->ReadString(PLUGINNAME, "ServerName", "RDC-ZHANGZ")).c_str(),
			KCBP_SERVERNAME_MAX);
		lstrcpyn(FGTJASet.ServerAddr,
			AnsiString(ini->ReadString(PLUGINNAME, "ServerAddr", "127.0.0.1")).c_str(),
			KCBP_DESCRIPTION_MAX);
		FGTJASet.ServerPort  = ini->ReadInteger(PLUGINNAME, "ServerPort", 21000);
		lstrcpyn(FGTJASet.DptCode,
			AnsiString(ini->ReadString(PLUGINNAME, "DptCode", "3104")).c_str(),
			20);
		FGTJASet.Timeout  = ini->ReadInteger(PLUGINNAME, "Timeout", 20);
		lstrcpyn(FGTJASet.UserName ,
			AnsiString(ini->ReadString(PLUGINNAME, "UserName", "KCXP00")).c_str(),
			20);
		lstrcpyn(FGTJASet.Password ,
			AnsiString(ini->ReadString(PLUGINNAME, "Password", "888888")).c_str(),
			20);
		AnsiString tmp = ini->ReadString(PLUGINNAME, "Operway", "0");
		FGTJASet.Operway = tmp.Length()>0 ? tmp[1] : '0';
		lstrcpyn(FGTJASet.SendQName  ,
			AnsiString(ini->ReadString(PLUGINNAME, "SendQName", "req1")).c_str(),
			20);
		lstrcpyn(FGTJASet.ReceiveQName ,
			AnsiString(ini->ReadString(PLUGINNAME, "ReceiveQName", "ans1")).c_str(),
			20);
		FGTJASet.bencrypt = ini->ReadBool(PLUGINNAME,"Encrypt",true);
		FGTJASet.SHA = ini->ReadString(PLUGINNAME,"SHA","1");
		FGTJASet.SZA = ini->ReadString(PLUGINNAME,"SZA","2");
		FGTJASet.MAC = ini->ReadString(PLUGINNAME,"MAC","");
	}
	__finally
	{
		delete ini;
	}
	return true;
}

void TTrdItf_GTJA::SetConfig(void)
{
	if( FSetupFile== NULL ) return ;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		ini->WriteString(PLUGINNAME, "ServerName", FGTJASet.ServerName);
		ini->WriteString(PLUGINNAME, "ServerAddr", FGTJASet.ServerAddr);
		ini->WriteInteger(PLUGINNAME, "ServerPort", FGTJASet.ServerPort);
		ini->WriteString(PLUGINNAME, "DptCode", FGTJASet.DptCode);
		ini->WriteInteger(PLUGINNAME, "Timeout", FGTJASet.Timeout);
		ini->WriteString(PLUGINNAME, "UserName", FGTJASet.UserName);
		ini->WriteString(PLUGINNAME, "Password", FGTJASet.Password);
		ini->WriteString(PLUGINNAME, "Operway", AnsiString(FGTJASet.Operway));
		ini->WriteString(PLUGINNAME, "SendQName", FGTJASet.SendQName);
		ini->WriteString(PLUGINNAME, "ReceiveQName", FGTJASet.ReceiveQName);
		ini->WriteBool(PLUGINNAME,"Encrypt",FGTJASet.bencrypt);
		ini->WriteString(PLUGINNAME,"SHA",FGTJASet.SHA);
		ini->WriteString(PLUGINNAME,"SZA",FGTJASet.SZA);
		ini->WriteString(PLUGINNAME,"MAC",FGTJASet.MAC);
		ini->UpdateFile();
	}
	__finally
	{
		delete ini;
	}
}
