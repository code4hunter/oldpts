//---------------------------------------------------------------------------


#pragma hdrstop

#include "uTrdItfImp.h"
#include "uDatabase.h"

#include <classes.hpp>
#include <IniFiles.hpp>
#include <stdio.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

TTrdItfImp::TTrdItfImp(const char *psetupfile,ADDLOG plogfunc)
    :TTrdItfBase(psetupfile,plogfunc)
{

}

TTrdItfImp::~TTrdItfImp()
{

}

//��ʼ��
int TTrdItfImp::Init()
{
    return 0;
}

//�����ʺ�
int TTrdItfImp::SetAccount()
{
    FSession = gSessionMan.get_session_by_name(FRequest.SetAccount.Account,
        FRequest.SetAccount.PW);

    if( FSession->isWorking() == false )
    {
        FSession->start_worker(FSetup.front_addr,FSetup.broker_id,
            FRequest.SetAccount.Account,
            FRequest.SetAccount.PW);
    }

    int timeout = 10;
    while(timeout-->0)
    {
        if( FSession->isLogin() )
        {
            FAccInfo.lt = FRequest.SetAccount.LoginType;
		    lstrcpyn(FAccInfo.PW, FRequest.SetAccount.PW, 13 );
            lstrcpyn(FAccInfo.Capital,FRequest.SetAccount.Account,ACC_LEN);
            return 0;
        }
        else
        {
            Sleep(1000);
        }
    }
    SetLastError(-1,'E',PLUGINNAME,"��¼��ʱ��");
    return FLastError.ErrorCode;
}

//�ʽ��ѯ
int TTrdItfImp::QryMoney()
{
    db d;
    try
    {
        d.connect();
        CThostFtdcTradingAccountField acct;
        if( d.qry_account( FAccInfo.Capital, acct ) == 0 )
        {
            NewAns( 1 );

            ( *FAnswer )[0].QryMoney.MoneyInfo.balance =acct.CurrMargin;
            ( *FAnswer )[0].QryMoney.MoneyInfo.available =acct.Available;
            ( *FAnswer )[0].QryMoney.MoneyInfo.MoneyType =motRMB;

            return 0;
        }
    }
    catch(std::string &err)
    {
        SetLastError(-1,'E',PLUGINNAME,"QryMoney:%s",err.c_str());
        return FLastError.ErrorCode;
    }

    return 0;
}

//����ί�в�ѯ
int TTrdItfImp::QryCurCsn()
{
    db d;
    try
    {
        d.connect();
        std::vector<CThostFtdcOrderField> list;
        if( FRequest.QryCurCsn.OrderID[0]!=0)  //�鵥��ί��
        {
            CThostFtdcOrderField ord;
            if( d.qry_order_by_ordid(FAccInfo.Capital,FRequest.QryCurCsn.OrderID,ord)==1)
            {
                list.push_back(ord);
            }
        }
        else
        {
            d.qry_orders(FAccInfo.Capital,FRequest.QryCurCsn.SeqNum,
                FRequest.QryCurCsn.MaxRecord,list);
        }

        if( list.size()> 0 )
        {
            NewAns( list.size() );
            for( int i=0; i<list.size(); i++)
            {
                //list[i].
            }
        }
    }
    catch(std::string &err)
    {
        SetLastError(-1,'E',PLUGINNAME,"QryCurCsn:%s",err.c_str());
        return FLastError.ErrorCode;
    }

    return 0;
}

//���ճɽ���ѯ
int TTrdItfImp::QryCurTrd()
{
    db d;
    try
    {
        d.connect();

        std::vector<CThostFtdcTradeField> list;
        if( FRequest.QryCurTrd.OrderID[0]!=0)  //�鵥��ί��
        {
            d.qry_trade_by_ordid(FAccInfo.Capital,FRequest.QryCurTrd.OrderID,list);
        }
        else
        {
            d.qry_trades(FAccInfo.Capital,FRequest.QryCurTrd.SeqNum,
                FRequest.QryCurTrd.MaxRecord,list);
        }

        if( list.size()> 0 )
        {
            NewAns( list.size() );
            for( int i=0; i<list.size(); i++)
            {
                //list[i].
            }
        }
    }
    catch(std::string &err)
    {
        SetLastError(-1,'E',PLUGINNAME,"QryCurTrd:%s",err.c_str());
        return FLastError.ErrorCode;
    }

    return 0;
}

//��ѯ�ʺ������еĹɷ�
int TTrdItfImp::QryStocks()
{
    db d;
    try
    {
        d.connect();
        std::vector<CThostFtdcInvestorPositionField> list;
        d.qry_positions(FAccInfo.Capital,list);
        if( list.size()> 0 )
        {
            NewAns( list.size() );
            for( int i=0; i<list.size(); i++)
            {
                //list[i].
            }
        }
    }
    catch(std::string &err)
    {
        SetLastError(-1,'E',PLUGINNAME,"QryStocks:%s",err.c_str());
        return FLastError.ErrorCode;
    }
    return 0;
}

//ί�г���
int TTrdItfImp::Order()
{
    if( FSession != NULL )
    {
        if( FSession->isLogin() )
        {
            int direction;              //���� 1,-1
            int openClose;              //��ƽ,ƽ�� 1,-1 ,-2
            int hedge=1;                //Ͷ���ױ�1,2

            switch (FRequest.Order.Type) {
                case otOpenBuy:
                    direction=1;
                    openClose=1;
                    break; //������
                case otOpenSell:
                    direction=-1;
                    openClose=1;
                    break; //������
                case otCloseBuy:
                    direction=1;
                    openClose=-1;
                    break;//ƽ����
                case otCloseSell:
                    direction=-1;
                    openClose=-1;
                    break;//ƽ����
                case otCloseTodayBuy:
                    direction=1;
                    openClose=-2;
                    break;// ƽ�����
                case otCloseTodaySell:
                    direction=-1;
                    openClose=-2;
                    break;// ƽ�����
            default:
                SetLastError(-1,'E',PLUGINNAME,"���������ƽ��־��֧��");
                return FLastError.ErrorCode;
            }

            int ordid = FSession->ReqOrderInsert(FRequest.Order.SecuID,
                direction,
                FRequest.Order.Price,
                FRequest.Order.Num,
                openClose,
                hedge);
            if( ordid<=0 )
            {
                SetLastError(-1,'E',PLUGINNAME,"ί��ʧ��");
                return FLastError.ErrorCode;
            }
            else
            {
                NewAns( 1 );
                sprintf( ( *FAnswer )[0].Order.ContractID,"%d",ordid);
				return 0;
            }
        }
        else
            SetLastError(-1,'E',PLUGINNAME,"Sessionδ��¼");
    }
    else
        SetLastError(-1,'E',PLUGINNAME,"Sessionδ����");
    return FLastError.ErrorCode;
}

int TTrdItfImp::Undo()
{
    if( FSession != NULL )
    {
        if( FSession->isLogin() )
        {
            return FSession->ReqOrderDelete("",FRequest.Undo.ContractID);
        }
        else
            SetLastError(-1,'E',PLUGINNAME,"Sessionδ��¼");
    }
    else
        SetLastError(-1,'E',PLUGINNAME,"Sessionδ����");
    return FLastError.ErrorCode;
}

market_type  TTrdItfImp::ConvertMarketType(const char *t)
{

}

order_type   TTrdItfImp::ConvertOrderType(const char *t)
{

}

order_state  TTrdItfImp::ConvertOrderState(const char *t)
{

}

pos_direction TTrdItfImp::ConvertPosDir(const char *t)
{

}

money_type   TTrdItfImp::ConvertMoneyType(const char *t)
{

}

char *  TTrdItfImp::ConvertMarketType(market_type t)
{

}

char *  TTrdItfImp::ConvertOrderType(order_type t)
{

}

char *  TTrdItfImp::ConvertOrderState(order_state t)
{

}

char *  TTrdItfImp::ConvertPosDir(pos_direction t)
{

}

char *  TTrdItfImp::ConvertMoneyType(money_type t)
{

}

//��������Ϣ������,���û�л�ȡ������������Ϣ����false
bool TTrdItfImp::GetConfig(void)
{
    if( FSetupFile== NULL ) return false;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		// �ж��Ƿ���ڲ�������ã�û�еĻ�����false�Ա�ϵͳ�ܹ�����Ĭ�ϵ�����
		if( ini->SectionExists(PLUGINNAME) == false ) return false;

		FSetup.front_addr = AnsiString(ini->ReadString(PLUGINNAME,"front_addr",FSetup.front_addr.c_str())).c_str();
        FSetup.broker_id  = AnsiString(ini->ReadString(PLUGINNAME,"broker_id",FSetup.broker_id.c_str())).c_str();

	}
	__finally
	{
		delete ini;
	}
	return true;
}

//��������Ϣ��д�������ļ�
void TTrdItfImp::SetConfig(void)
{
    if( FSetupFile== NULL ) return ;

	TMemIniFile *ini = new TMemIniFile( FSetupFile );
	try
	{
		ini->WriteString (PLUGINNAME,"front_addr",     FSetup.front_addr.c_str());
        ini->WriteString (PLUGINNAME,"broker_id", FSetup.broker_id.c_str());
		ini->UpdateFile();
	}
	__finally
	{
		delete ini;
	}
}

//�ر��м������
void TTrdItfImp::CloseLink(void)
{

}

int TTrdItfImp::KeepAlive(void)
{
    if( FSession != NULL )
    {
        if( FSession->isLogin() )
            FSession->ReqQry(false);
    }
    return 0;
}
