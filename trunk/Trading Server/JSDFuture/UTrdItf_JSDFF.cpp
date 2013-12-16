//---------------------------------------------------------------------------

#include <IniFiles.hpp>
#include <assert.h>
#include <stdio.h>

#pragma hdrstop
#include "UTrdItf_JSDFF.h"
#include "uRecvEventsTh.h"

#pragma package(smart_init)

/*
Buy_or_sale ˵��
״̬C ״̬E ��־
���� Buy 0
���� Sale 1
δ֪ Unknow ����
*/
const char BUY = '0';
const char SELL= '1';

/*
eo_flag ˵��
״̬C ״̬E ��־
���� open 0
ƽ�� close 1
ƽ�� close today 2
δ֪ unknow ����
*/
const char OPEN        = '0';
const char CLOSE       = '1';
const char CLOSE_TODAY = '2';
const char CLOSE_TODAY2= '3';
/*
sh_flag ˵��
״̬C ״̬E ��־
Ͷ�� tou 0
��ֵ bao 1
*/
const char * TOU = "0";
const char * BAO = "1";
/*
Wt_state ˵��
״̬C ״̬E               ��־
�ȴ����� Waiting           n
�����걨 Baodaning         s
�ѱ���   Already baodaned  a
���ֳɽ� Partial completed p
ȫ���ɽ� Completed         c
���ڳ��� Deleteing         f
ϵͳ���� System disable    m
ϵͳ���� User disable      q
�ѳ���   Total deleted     d
���ɲ��� Partial completed and deleted b
δ֪״̬ Unknow            ����
*/
const char WAITING = 'n';
const char SENDING = 's';
const char ACCEPTED= 'a';
const char FILLING = 'p';
const char FILLED  = 'c';
const char DELETEING='f';
const char SYS_REJECTED= 'm';
const char USER_REJECTED='q';
const char DELETED = 'd';
const char PCPD = 'b';

/*
����� : 1
��Ԫ:    2
�۱�:    3
*/
//---------------------------------------------------------------------------

long convert_datetime_str_to_long(const char * str)
{
    // remove non alpha characters
    char buf[255];
    int j = 0;
    for (_SIZE_T i = 0; i < strlen(str); i++) {
        if( isdigit(str[i]) )
        {
            buf[j++] = str[i];
        }
    }
    buf[j] = 0;

    return atoi(buf);
}

order_type  SConvertOrderType(const char *t)
{
    if (t == NULL || strlen(t) < 2 ) {
        return otNo;
    }

    char OC = t[1];
    char BS = t[0];

    if (OC == OPEN && BS == BUY )
    {
        return  otOpenBuy;
    }
    else if( OC == OPEN && BS == SELL )
    {
        return  otOpenSell;
    }
    else if(OC == CLOSE && BS == BUY)
    {
        return otCloseBuy;
    }
    else if(  OC == CLOSE && BS == SELL  )
    {
        return otCloseSell;
    }
    else if((OC == CLOSE_TODAY || OC == CLOSE_TODAY2) && BS == BUY)
    {
        return otCloseTodayBuy;
    }
    else if((OC == CLOSE_TODAY || OC == CLOSE_TODAY2) && BS == SELL )
    {
        return otCloseTodaySell;
    }
    else
    {
        ODS('E',PLUGINNAME,"%s", t);
        return otNo;
    }
}
//---------------------------------------------------------------------------
TTrdItf_JSDFF::TTrdItf_JSDFF(const char *psetupfile,ADDLOG plogfunc)
:TTrdItfBase(psetupfile,plogfunc)
{
    //memset(&FJSDSet,0,sizeof(TJSDSet));
    FJSDSet.SvrIp = "127.0.0.1";
    FJSDSet.SvrPort = 17990;
    FJSDSet.TimeOut = 5000;
    FJSDSet.debug_mode = false;
    FJSDSet.branch_no = "999";
    FJSDSet.gw_ver = "v6";
    strncpy(FJSDSet.jysID , "CBAG",5);

    FidTcp = new TIdTCPClient(NULL);
    FidIPWatch = new TIdIPWatch(NULL);
    FidIPWatch->HistoryEnabled =false;
}
//---------------------------------------------------------------------------
TTrdItf_JSDFF::~TTrdItf_JSDFF()
{
    CloseLink();
    delete FidTcp;
    delete FidIPWatch;
}
//---------------------------------------------------------------------------
AnsiString TTrdItf_JSDFF::GetRequestHead(AnsiString FuncNo)
{
    AnsiString text;

    //        ���ܺ�  | Ӫҵ������  | ί�з�ʽ  | �ͻ���                     | �ͻ����� |
    text = FuncNo +"|"+" "      +"|"+" "    +"|"+AnsiString(FAccInfo.Capital)+"|"+AnsiString(FAccInfo.PW);
    return text;
}
//---------------------------------------------------------------------------
void TTrdItf_JSDFF::SetError(int code,const char * error)
{
    lstrcpyn( FLastError.Sender ,"JSDFF", SEQ_LEN);
    FLastError.ErrorCode = code;
    lstrcpyn( FLastError.Text,error,MAX_TEXT );
    ODS('E',PLUGINNAME, "������ʾ:%s,ErrNo:%d",FLastError.Text,FLastError.ErrorCode );
}

AnsiString TTrdItf_JSDFF::GetErrorText(int code, const char *error)
{
    SetError(code,error);
    AnsiString text;
    text.printf("A\r\nLocal\r\n%d\r\nN\r\n%s\r\n%d", REQUEST_NUM, error, code);
    return text;
}
//---------------------------------------------------------------------------
AnsiString TTrdItf_JSDFF::ReadNextData()
{
    AnsiString cmd;
    cmd.printf("R|%s|%s|%s|", FidIPWatch->LocalIP().c_str(),REQUEST_NUM,GetRequestHead("0").c_str());
    return ReadFirstData(cmd);
}
//---------------------------------------------------------------------------
AnsiString TTrdItf_JSDFF::ReadFirstData(AnsiString cmd)
{
	try
	{
		if( FidTcp->Connected() !=true )
			return IntToStr(ERR_REMOTE_OTHER_FAILED);
	}
	catch (Exception *e)
	{
		ODS('E',PLUGINNAME,"ȯ�̹�̨��������Ͽ�! ������Ϣ:%s.",e->Message.c_str());
		return  IntToStr(ERR_REMOTE_OTHER_FAILED);
	}
    //����ϴεķ�����Ϣ
    TByteDynArray da;
    try
    {
        if( FidTcp->Socket->Readable(10) == true )
        {
            FidTcp->Socket->ReadBytes(da,-1,true);
        }
        FidTcp->Socket->Write(cmd);
    }
    catch( Exception &e )
    {
        ODS('E',PLUGINNAME,"ȯ�̹�̨��������ʧ��! ������Ϣ:%s.",e.Message.c_str());
        return  IntToStr(ERR_REMOTE_SEND_FAILED) ;
    }

    da.set_length(0);

    try
    {
        FidTcp->Socket->ReadBytes(da,-1,true);
    }
    catch(Exception &e)
    {
        ODS('E',PLUGINNAME,"ȯ�̹�̨��������ʧ��! ������Ϣ:%s.",e.Message.c_str());
        return  IntToStr(ERR_REMOTE_RECV_FAILED) ;
    }

    if (da.Length == 0)
    {
        ODS('E',PLUGINNAME,"ȯ�̹�̨����������Ϊ0!");
        return IntToStr(ERR_REMOTE_RECV_FAILED)  ;
    }
    AnsiString ret = (char*)&da[0];

    return ret;
}
//---------------------------------------------------------------------------
// count ��ʾ�����м���ֵ
int TTrdItf_JSDFF::SplitData(AnsiString SD, TStringList *lstDD, int count)
{
    assert(lstDD != NULL);

    SplitString(SD.c_str(),SD.Length(),lstDD,'|');

    if( lstDD->Count == 1 )
    {
        SetError(lstDD->Strings[0].ToIntDef(-2), "��̨���ݴ������");
        return FLastError.ErrorCode;
    }
    else if (lstDD->Count < 4)
    {
        SetError(-501, "���ݽ���ʧ��");
        return DEF_ACK_ERROR;
    }

    if (lstDD->Strings[0] != "A")
    {
        SetError(-502, "Answer Data Error");
        return DEF_ACK_ERROR;
    }

    if (lstDD->Strings[3] == "N" )
    {
        if (lstDD->Count < 5)
            SetError(-503, ("����N,���޴�������,DATA:"+ SD).c_str());
        else if (lstDD->Count >= 5)
            SetError(lstDD->Strings[4].ToIntDef(-503),lstDD->Strings[5].c_str());
        return DEF_ACK_ERROR;
    }

    if (lstDD->Count >= count)
        return DEF_ACK_OK;

    SetError(-504, ("���ص������������ԣ�,DATA:"+ SD).c_str());
    return DEF_ACK_ERROR;
}
//---------------------------------------------------------------------------
int TTrdItf_JSDFF::Init()  //��ʼ��
{
    try
    {
        if (!FidTcp->Connected())
        {
            FidTcp->Host = FJSDSet.SvrIp;
            FidTcp->Port = FJSDSet.SvrPort;
            FidTcp->ConnectTimeout = FJSDSet.TimeOut * 2;
            FidTcp->ReadTimeout =    FJSDSet.TimeOut;
            FidTcp->Connect();
        }
    }
    catch (Exception *e)
    {
        ODS('E',PLUGINNAME,"���ӹ�̨ʧ��! ������Ϣ:%s.",e->Message.c_str());
    }

    return FidTcp->Connected()==true ? 0 : -1;
}

void TTrdItf_JSDFF::CloseLink(void)
{
    try
	{
		FidTcp->Disconnect();
    }
    catch(...)
    {

    }

	//FDB.disconnect();
}
//--------------------------------------------------------------------------
// CMD:���ܺ�(6011)|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::SetAccount() //�����ʺ�
{
    AnsiString cmd;

    TStringList *lstDD = new TStringList();

    try
    {

        cmd.printf("R|%s|%s|6011| | |%s|%s|",
            FidIPWatch->LocalIP().c_str(),
            REQUEST_NUM,
            FRequest.SetAccount.Account,
            FRequest.SetAccount.PW);

        //  1.�ɹ���־
        //  2.�ͻ�����
        //  3.���ն�
        //  4.׷�ӱ�֤��
        //  5.�ͻ���ȫ���(0����ȫ��1������ȫ��3��Σ�ա�6������)
        //  6.δ�ã�����
        //  7.δ�ã�����
        //  8.δ�ã�����
        //  9.δ�ã�����
        //  10.δ�ã�����
        //  11.ȷ�Ͻ��㵥ģʽ ��0������ȡ���ʵ� ��1����ȡ���ʵ�������ȷ�� ��2����ȡ���ʵ�������ȷ��
        //  12.���㵥ȷ��״̬ ��1������ȡ����ȷ�ϡ�0����δȡ��δȷ��

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 12) == DEF_ACK_OK)
        {
            strncpy(FAccInfo.Capital, FRequest.SetAccount.Account, 20);
            strncpy(FAccInfo.PW, FRequest.SetAccount.PW, 13);

            if( strcmpi( FJSDSet.gw_ver.c_str(),  "v6" ) == 0 )
            {

                //6040 ��ѯ�ͻ����ױ���---GETCLIENTMAPNO
                //��1�� ���ܺ� 6040
                //��2�� Ӫҵ������
                //��3�� ί�з�ʽ
                //��4�� �ͻ���
                //��5�� �ͻ�����
                //��6�� ������
                //��7�� ϯλ�ţ��գ�ȫ����
                //����Ӧ��
                //�ɹ�
                //��һ������
                //��1�� �ɹ���־ Y
                //��2�� ��¼������������������
                //������
                //��1�� �ͻ���
                //��2�� ������
                //��3�� ���ױ���
                //��4�� �����ױ����־
                //��5�� ϯλ��
                //����
                //��1�� �����־ N
                //��2�� �������
                //��3�� ��������

                NewAns(1);
                memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));

                for( int i=0;i<strlen( FJSDSet.jysID );i++)
                {
                    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
                    cmd.cat_printf("%s|%c|",GetRequestHead("6040").c_str(),FJSDSet.jysID[i]);

                    if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
                    {
                        int count = lstDD->Strings[4].ToIntDef(0);
                        for (int j = 0; j < count; j++)
                        {
                            if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 5) == DEF_ACK_OK)
                            {
                                if( FJSDSet.jysID[i]==lstDD->Strings[INDEX(2)][1])
                                {
                                    //���ÿͻ����ױ���
                                    FJSDSet.JyCode[i]=lstDD->Strings[INDEX(3)];
                                    //����ϯλ��
                                    FJSDSet.seatID[i]=lstDD->Strings[INDEX(5)];
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        return AnsiString(FRequest.SetAccount.Account).ToIntDef(DEF_OTHER_ERROR);
                    }
                }
            }
            else
            {
                NewAns(1);
                memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));
            }
        }
        else
        {
            return FLastError.ErrorCode;
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}
//--------------------------------------------------------------------------
//��ѯ�����ʽ����,�ܱ�֤��
//���ܺ� 6012|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|����---YYYYMMDD|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryMoney()     //�ʽ��ѯ
{
	AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

	cmd.cat_printf("%s|%s|",
		GetRequestHead("6012").c_str(),
		Now().FormatString("yyyymmdd").c_str()
		);

    TStringList *lstDD = new TStringList();
    try
    {
        //  1.�ɹ���־ Y  2.�ͻ�����  3.���ս��  4.���붳��  5.��������  6.���뱣֤��
        //  7.������֤��  8.ӯ��      9.����      10.�����ʽ� 11.��̬Ȩ�� 12.��̬����
        //  13.�� ����    14.�� ����  15.����ӯ�� 16.ƽ��ӯ�� 17.�� ����  18.�� ����
        //  19.���ճ���� 20.�� ����  21.�� ����  22.�ܱ�֤��

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 22) == DEF_ACK_OK)
        {
            NewAns(1);
            (*FAnswer)[0].QryMoney.MoneyInfo.MoneyType = motRMB;
			(*FAnswer)[0].QryMoney.MoneyInfo.balance = StrToFloat(lstDD->Strings[INDEX(11)]);  //��̬Ȩ��
            (*FAnswer)[0].QryMoney.MoneyInfo.available= StrToFloat(lstDD->Strings[INDEX(10)]); //�����ʽ�
        }
		else
        {
            return FLastError.ErrorCode;
        }
    }
    __finally
    {
    		delete lstDD;
    }

    return 0;
}


//--------------------------------------------------------------------------
//��ѯ����ί��
//���ܺ� 6019|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|
//��ѯ����ί��
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryCurCsn()    //����ί�в�ѯ
{
    AnsiString cmd;

    if (FRequest.QryCurCsn.OrderID[0] != 0)
    {  // �鵥��ί��
        /*6.11 6020 ί��״̬��ѯ--- QUERYWTSTATE
        ��1�� ���ܺ� 6020
        ��2�� Ӫҵ������
        ��3�� ί�з�ʽ
        ��4�� �ͻ���
        ��5�� �ͻ�����
        ��6�� ί�е���
        ��7�� �µ�ϯλ
        ����Ӧ��
        �ɹ�
        ��1�� �ɹ���־ Y
        ��2�� ί�е�״̬
        ��3�� �ɽ�����
        ��4�� δ�ɽ�����
        ��5�� ί������
        ��6�� �ɽ��۸�
        ��7�� ����ʱ��
        ��8�� ί�е���
        ��9�� ϯλ��
        ��10���µ�ϯλ
        ����
        ��1�� �����־ N
        ��2�� �������
        ��3�� ��������
        */
        AnsiString seat,ordid  ;
        //splitOrdid(FRequest.QryCurCsn.OrderID,seat,ordid);
        ordid = FRequest.QryCurCsn.OrderID;
        cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
        cmd.cat_printf("%s|%s|%s|",GetRequestHead("6020").c_str(),ordid.c_str(),seat.c_str());
        TStringList *lstDD = new TStringList();
        try
        {
            //A|192.168.123.124| |Y|a|0|1|1|0| |51| |
            if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 9) == DEF_ACK_OK)
            {
                TOrderInfo ci;
                memset(&ci, 0, sizeof(TOrderInfo));
                AnsiString nordid;
                //nordid.printf("%s:%s",seat.c_str(),   //lstDD->Strings[INDEX(7)].c_str(),
                //	lstDD->Strings[INDEX(8)].c_str());
                //strncpy(ci.ContractID,nordid.c_str(), SEQ_LEN);

                strncpy(ci.ContractID,lstDD->Strings[INDEX(8)].c_str(), SEQ_LEN);
                strncpy(ci.SecuID,"", CODE_LEN);
                ci.Market = ConvertMarketType(seat.c_str());
                ci.Time =   convert_datetime_str_to_long(lstDD->Strings[INDEX(7)].c_str());
                ci.Date =   convert_datetime_str_to_long(FormatDateTime("yyyymmdd",Date()).c_str());
                ci.Type   = ConvertOrderType("");
                ci.State  = ConvertOrderState(lstDD->Strings[INDEX(2)].c_str());
                ci.CsnVol = MyStrToInt(lstDD->Strings[INDEX(5)]);
                ci.TrdVol = MyStrToInt(lstDD->Strings[INDEX(3)]);
                if ( ci.State == osbw || ci.State ==osyc || ci.State ==osyf)
                {
                    ci.CancelVol = ci.TrdVol - ci.CsnVol ;
                }
                ci.CsnPrice  = 0;
                ci.TrdPrice  = StrToFloat(lstDD->Strings[INDEX(6)]);
                strncpy(ci.Account,"",ACC_LEN);
                strncpy(ci.SeqNum,lstDD->Strings[INDEX(8)].c_str(),SEQ_LEN);

                NewAns(1);
                memcpy(&(*FAnswer)[0].QryCurCsn.OrderInfo, &ci, sizeof(TOrderInfo));
            }
            else
            {
                return FLastError.ErrorCode;
            }
        }
       	__finally
        {
        	delete lstDD;
        }
    }
    else if( FRequest.QryCurCsn.MaxRecord == 0 )  // ������
    {
        TList * lstAns = new TList();
        TStringList *lstDD = new TStringList();
        cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
        cmd.cat_printf("%s|",GetRequestHead("6019").c_str());

        try
        {
            /*
            ��1�� ����������
            ��2�� ����������
            ��3�� ί�е���
            ��4�� ��Լ����
            ��5�� ��Լ����
            ��6�� ί�е�״̬����
            ��7�� ί�е�״̬���� // ȫ���ɽ�/���ֳɽ�/ȫ������/�Ѿ��걨/���ڴ���/δ�������
            ��8�� �������
            ��9�� ����������� // ����/����
            ��10����ƽ�ֱ�־
            ��11����ƽ������ // ����/ƽ��/ƽ��
            ��12��Ͷ�����
            ��13��Ͷ������
            ��14��ί���������ɽ����� + δ�ɽ����� + ����������
            ��15��ί�м۸�
            ��16���ɽ�����
            ��17���ɽ��۸�
            ��18��δ�ɽ�����
            ��19��ϵͳ���ĺ�
            ��20�����ױ���
            ��21���� ����
            ��22��ί��ʱ��
            ��23���걨ʱ��
            ��24���� ����
            ��25���� ����
            ��26������ʱ��
            */
            if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
            {
                int count = lstDD->Strings[4].ToInt();
                AnsiString nordid;
                for (int i = 0; i < count; i++)
                {
                    if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 26) == DEF_ACK_OK)
                    {
                        TOrderInfo *ci = new TOrderInfo;
                        memset(ci, 0, sizeof(TOrderInfo));

                        ci->Market = ConvertMarketType(lstDD->Strings[INDEX(1)].c_str());

                        //nordid.printf("%s:%s",GetSeatId(ci->Market).c_str(),
                        //	lstDD->Strings[INDEX(3)].c_str());

                        //strncpy(ci->ContractID,nordid.c_str(), SEQ_LEN);
                        strncpy(ci->ContractID,lstDD->Strings[INDEX(3)].c_str(), SEQ_LEN);
                        //strncpy(ci->SecuID,    lstDD->Strings[INDEX(4)].c_str(), CODE_LEN);
                        strncpy(ci->SecuID, convert_to_PTS_code( lstDD->Strings[INDEX(4)].c_str(),ci->Market).c_str(), CODE_LEN);
                        ci->Time =   convert_datetime_str_to_long(lstDD->Strings[INDEX(22)].c_str());
                        ci->Date =   convert_datetime_str_to_long(FormatDateTime("yyyymmdd",Date()).c_str());
                        ci->Type   = ConvertOrderType((lstDD->Strings[INDEX(8)]+lstDD->Strings[INDEX(10)]).c_str());
                        ci->State  = ConvertOrderState(lstDD->Strings[INDEX(6)].c_str());
                        ci->CsnVol = MyStrToInt(lstDD->Strings[INDEX(14)]);
                        ci->TrdVol = MyStrToInt(lstDD->Strings[INDEX(16)]);
                        if ( ci->State == osbw || ci->State ==osyc || ci->State ==osyf)
                        {
                            ci->CancelVol = ci->TrdVol - ci->CsnVol ;
                        }
                        ci->CsnPrice  = StrToFloat(lstDD->Strings[INDEX(15)]);
                        ci->TrdPrice  = StrToFloat(lstDD->Strings[INDEX(17)]);
                        strncpy(ci->Account, lstDD->Strings[INDEX(20)].c_str(),ACC_LEN);
                        strncpy(ci->SeqNum,lstDD->Strings[INDEX(3)].c_str(),SEQ_LEN);
                        lstAns->Add(ci);
                    }
                    else
                    {
                        return FLastError.ErrorCode;
                    }
                }

                if (lstAns->Count > 0)
                {
                    NewAns(lstAns->Count);
                    for (int i = 0; i < lstAns->Count; i++)
                    {
                        TOrderInfo *ci = (TOrderInfo *)lstAns->Items[i];
                        memcpy(&(*FAnswer)[i].QryCurCsn.OrderInfo, ci, sizeof(TOrderInfo));
                    }
                }

                for (int i = 0; i < lstAns->Count; i++)
                {
                    TOrderInfo *ci = (TOrderInfo *)lstAns->Items[i];
                    delete ci;
                }
                lstAns->Clear();
            }
           	else
            {
                return FLastError.ErrorCode;
            }
        }
        __finally
        {

        		delete lstDD;
        		delete lstAns;
        }
    }
    else
    {
        SetError(-1, "��֧��������ѯ");
        return -1;
    }
    return 0;
}

//--------------------------------------------------------------------------
//��ѯ���ճɽ�
//���ܺ� 6013|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|��ʼ����----YYYYMMDD|��������----YYYYMMDD
//�������V6��������Ҫʹ��6053����ѯ��ʷ�ɽ���ϸ,6013ֻ������ѯ���ճɽ�
//--------------------------------------------------------------------------
/*
����Ӧ��
�ɹ�
��һ������
��1���ɹ���־ Y
��2����¼������������������
���ճɽ��ĺ��������£�
��1�� ����������
��2�� ����������
��3�� ί�е���
��4�� ��Լ����
��5�� ��Լ����
��6�� �������
��7�� ����������� // ����/����
��8�� ��ƽ�ֱ�־
��9�� ��ƽ������ // ����/ƽ��/ƽ��
��10��Ͷ�����
��11��Ͷ������
��12���ɽ�����
��13���ɽ��۸�
��14����������
��15�����ױ���
��16��ϵͳ��
��17���ɽ���
��18��������
��19���ɽ�ʱ��
��20��ϯλ��
��21������
*/
int TTrdItf_JSDFF::QryCurTrd()    //���ճɽ���ѯ
{
	try
	{
		if( FidTcp->Connected() !=true )
			return ERR_REMOTE_OTHER_FAILED;
	}
	catch (Exception *e)
	{
		ODS('E',PLUGINNAME,"ȯ�̹�̨��������Ͽ�! ������Ϣ:%s.",e->Message.c_str());
		return  ERR_REMOTE_OTHER_FAILED;
	}

    std::vector<TTradeInfo>  list;
    try
	{
		trade_db      FDB;
		FDB.connect();
        FDB.qry_trades(this->FAccInfo.Capital,FRequest.QryCurTrd.OrderID,FRequest.QryCurTrd.SeqNum,
            FRequest.QryCurTrd.MaxRecord,list);
    }
    catch(std::string &err)
    {
        this->SetError(-1,err.c_str());
        return -1;
    }

    if (list.size() > 0)
    {
        NewAns(list.size());
        for (int i = 0; i < list.size(); i++)
        {
            TTradeInfo *ti = (TTradeInfo *)&list[i];
            memcpy(&(*FAnswer)[i].QryCurTrd.TrdInfo, ti, sizeof(TTradeInfo));
        }
    }
    return 0;
    /*
    AnsiString cmd;
    AnsiString date = Now().FormatString("yyyymmdd");

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
    GetRequestHead("6013").c_str(),
    date.c_str(),
    date.c_str());


    try
    {

    if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
    {
    int count = lstDD->Strings[4].ToInt();
    for (int i = 0; i < count; i++)
    {
    if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
    {
    TTradeInfo *ti = new TTradeInfo;
    memset(ti, 0, sizeof(TTradeInfo));

    strncpy(ti->ContractID,lstDD->Strings[INDEX(3)].c_str(), SEQ_LEN);
    strncpy(ti->SecuID,   lstDD->Strings[INDEX(4)].c_str(), CODE_LEN);
    strncpy(ti->TrdID,  lstDD->Strings[INDEX(15)].c_str(), SEQ_LEN);
    ti->Time =   convert_datetime_str_to_long(lstDD->Strings[INDEX(19)].c_str());
    ti->Date =   convert_datetime_str_to_long(lstDD->Strings[INDEX(14)].c_str());
    ti->Type  = ConvertOrderType(lstDD->Strings[INDEX(6)].c_str());
    ti->Vol   = MyStrToInt(lstDD->Strings[INDEX(12)]);
    ti->Price = MyStrToFloat(lstDD->Strings[INDEX(13)]);
    ti->Market = ConvertMarketType(lstDD->Strings[INDEX(1)].c_str());
    strncpy(ti->Account , lstDD->Strings[INDEX(15)].c_str(),ACC_LEN);
    strncpy(ti->SeqNum, lstDD->Strings[INDEX(3)].c_str(),SEQ_LEN);
    lstAns->Add(ti);
    }
    else
    {
    return -1;
    }
    }

    if (lstAns->Count > 0)
    {
    NewAns(lstAns->Count);
    for (int i = 0; i < lstAns->Count; i++)
    {
    TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
    memcpy(&(*FAnswer)[i].QryCurTrd.TrdInfo, ti, sizeof(TTradeInfo));
    }
    }

    for (int i = 0; i < lstAns->Count; i++)
    {
    TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
    delete ti;
    }
    lstAns->Clear();
    }
    else
    {
    return -1;
    }
    }
    catch( Exception &e)
    {
    lstrcpyn( FLastError.Sender ,"JSDFF", SEQ_LEN);
    FLastError.ErrorCode = -1;
    lstrcpyn( FLastError.Text,e.Message.c_str(),MAX_TEXT );
    ODS('E',PLUGINNAME, "������ʾ:%s,ErrNo:%d",FLastError.Text,FLastError.ErrorCode );
    }

    delete lstDD;
    delete lstAns;

    */
}

//--------------------------------------------------------------------------
//��ѯ���гֲ�
//���ܺ� 6014|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|����---YYYYMMDD|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryStocks()    //��ѯ�ʺ������еĹɷ�
{
    AnsiString cmd;
    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    cmd.cat_printf("%s|%s|",
        GetRequestHead("6014").c_str(),
        Now().FormatString("yyyymmdd").c_str());

    try
    {
        /*
        ����Ӧ��
        �ɹ�
        ��һ����
        ��1���ɹ���־ Y
        ��2�� ��¼������������������
        ��������
        ��1�� ����������
        ��2�� ����������
        ��3����Լ����
        ��4�� Ͷ�����
        ��5����ֲ�
        ��6�� �����
        ��7�� ���ֲ�
        ��8�� ������
        ��9�� �򸡶�
        ��10��������
        ��11�����¼�
        ��12��Ͷ������
        ��13������ӯ��
        ��14�����ױ���
        ��15���� ����
        ��16���� ����
        ��17���� ����
        ��18������ֲ�
        ��19�������ֲ�
        ����
        ��1�������־ N
        ��2���������
        ��3����������
        */

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN+2) == DEF_ACK_OK)
        {

            //���������¼Ϊ��С�ƺ���С�ƣ�����Ҫ��2
            int count = lstDD->Strings[4].ToInt()-2;
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 19) == DEF_ACK_OK)
                {
                    TStockInfo *si = new TStockInfo;
                    memset(si, 0, sizeof(TStockInfo));
                    strncpy(si->Account,   lstDD->Strings[INDEX(14)].c_str(),ACC_LEN);     //���뽻�ױ���
                    si->PosDir = pdLong;
                    si->Market = ConvertMarketType(lstDD->Strings[INDEX(1)].c_str());
                    strncpy(si->SecuID, convert_to_PTS_code(lstDD->Strings[INDEX(3)].c_str(),si->Market).c_str(), CODE_LEN);
                    si->Balance =  MyStrToInt(lstDD->Strings[INDEX(5)]) -MyStrToInt(lstDD->Strings[INDEX(18)]);
                    si->PosNum =  MyStrToInt(lstDD->Strings[INDEX(5)]);
                    si->Available = si->PosNum;
                    si->CostPrice = MyStrToFloat(lstDD->Strings[INDEX(6)]);
                    si->CurPrice = MyStrToFloat(lstDD->Strings[INDEX(11)]);
                    if (si->PosNum>0) {
                        lstAns->Add(si);
                    }
                    else delete si;

                    si = new TStockInfo;
                    memset(si, 0, sizeof(TStockInfo));
                    //strncpy(si->SecuID, lstDD->Strings[INDEX(3)].c_str(), CODE_LEN);
                    strncpy(si->Account,   lstDD->Strings[INDEX(14)].c_str(),ACC_LEN);     //���뽻�ױ���
                    si->PosDir = pdShort;
                    si->Market = ConvertMarketType(lstDD->Strings[INDEX(1)].c_str());
                    strncpy(si->SecuID, convert_to_PTS_code(lstDD->Strings[INDEX(3)].c_str(),si->Market).c_str(), CODE_LEN);
                    si->Balance =  MyStrToInt(lstDD->Strings[INDEX(7)]) -MyStrToInt(lstDD->Strings[INDEX(19)]);
                    si->PosNum =  MyStrToInt(lstDD->Strings[INDEX(7)]);
                    si->Available = si->PosNum;
                    si->CostPrice = MyStrToFloat(lstDD->Strings[INDEX(8)]);
                    si->CurPrice = MyStrToFloat(lstDD->Strings[INDEX(11)]);
                    if (si->PosNum>0) {
                        lstAns->Add(si);
                    }
                    else delete si;

                }
                else
                {
                    return FLastError.ErrorCode;
                }
            }

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TStockInfo *ci = (TStockInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryStocks.StockInfo, ci, sizeof(TStockInfo));
                }
            }

            for (int i = 0; i < lstAns->Count; i++)
            {
                TStockInfo *ci = (TStockInfo *)lstAns->Items[i];
                delete ci;
            }
            lstAns->Clear();
        }
        else
        {
            return FLastError.ErrorCode;
        }
    }
    __finally
    {

    	delete lstDD;
    	delete lstAns;
    }
    return 0;
}

//////���׺���/////
//---------------------------------------------------------------------------
//���ܺ� 6021|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|������----����|��Լ����|�������
//��ƽ�ֱ�־|Ͷ�����|ί������|ί�м۸�|���ױ���
//��1�� ���ܺ� 6021
//��2�� Ӫҵ������
//��3�� ί�з�ʽ
//��4�� �ͻ���
//��5�� �ͻ�����
//��6�� ������
//��7�� ��Լ����
//��8�� �������
//��9�� ��ƽ�ֱ�־
//��10��Ͷ�����
//��11��ί������
//��12��ί�м۸�
//��13�����ױ���
//��14��ϯλ��
//---------------------------------------------------------------------------
int TTrdItf_JSDFF::Order()
{
    AnsiString cmd;
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    cmd.cat_printf("%s|%c|%s|%c|%c|%s|%d|%.3f|%s|%s|",
        GetRequestHead("6021").c_str(),
        ConvertMarketType(FRequest.Order.Market)[0],//������
		convert_to_JSD_code(FRequest.Order.SecuID,FRequest.Order.Market).c_str(),                //��Լ����
        ConvertOrderType(FRequest.Order.Type)[1],//�������
        ConvertOrderType(FRequest.Order.Type)[0],//��ƽ�ֱ�־
        TOU,             //Ͷ�����
        FRequest.Order.Num,                       //ί������
        FRequest.Order.Price,                     //ί�м۸�
        GetTradeCode(FRequest.Order.Market).c_str(),//���ױ���
        GetSeatId(FRequest.Order.Market).c_str()
        );

    //ODS("BUY,Code:%s,Price:%0.3f,Num:%d,Open:%d",
    //    FRequest.Buy.SecuID,FRequest.Buy.Price,FRequest.Buy.Num,FRequest.Buy.Type & 0x000F);

    TStringList *lstDD = new TStringList();
    try
    {
        /*
        ����Ӧ��
        ��ȷ
        ��1���ɹ���־ Y
        ��2��ί�е���
        ��3������������[v5 ��̨�ṩ]
        ��4�����������ƣ�v6 ���ṩ�����ش���
        ��5����Լ���루Ʒ�ִ���+�����ڣ����ش���
        ��6����Լ���ƣ�v6 ���ṩ�����ش���
        ��7��ί�е�״̬����[v5 ��̨�ṩ]
        ��8��ί�е�״̬���ƣ�v6 ���ṩ�����ش���
        ��9���������[v5 ��̨�ṩ]
        ��10�������������[����/����] ��v6 ���ṩ�����ش���
        ��11����ƽ�ֱ�־[v5 ��̨�ṩ]
        ��12����ƽ������[����/ƽ��/ƽ��] ��v6 ���ṩ�����ش���
        ��13��Ͷ�����[v5 ��̨�ṩ]
        ��14��Ͷ�����ƣ�v6 ���ṩ�����ش���
        ��15��ί������[v5 ��̨�ṩ]
        ��16��ί�м۸�[v5 ��̨�ṩ]
        ��17���ɽ�����[v5 ��̨�ṩ]
        ��18���ɽ��۸�[v5 ��̨�ṩ]
        ��19��δ�ɽ�����[v5 ��̨�ṩ]
        ��20��ϵͳ���ĺ�[v5 ��̨�ṩ]
        ��21�����ױ���[v5 ��̨�ṩ]
        ��22��������
        ��23��ί��ʱ��
        ��24���걨ʱ��
        ��25��ί�з�ʽ
        ��26�������û�
        ��27������ʱ��
        ��28��ί�е�����
        ��29��ϯλ��
        ��30������
        ��31���µ�ϯλ
        */
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 31) == DEF_ACK_OK)
        {
            NewAns(1);
            //sprintf( (*FAnswer)[0].Order.ContractID,"%s:%s",
            //GetSeatId(FRequest.Order.Market).c_str(),
            //			lstDD->Strings[INDEX(31)].c_str(),
            //		   lstDD->Strings[INDEX(2)].c_str(),SEQ_LEN );

            sprintf( (*FAnswer)[0].Order.ContractID,"%s",
				lstDD->Strings[INDEX(2)].c_str(),SEQ_LEN );
        }
        else
        {
            return FLastError.ErrorCode;
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

//---------------------------------------------------------------------------
//���ܺ� 6022|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|������|��Լ����|�������|��ƽ�ֱ�־
//Ͷ�����|ί������|ί�м۸�|ί�е���|��������|ϵͳ���ĺ�|ϯλ��(����v6���ر�����д)
/*
��1�� ���ܺ� 6022
��2�� Ӫҵ������
��3�� ί�з�ʽ
��4�� �ͻ���
��5�� �ͻ�����
��6�� ������
��7�� ��Լ����
��8�� �������
��9�� ��ƽ�ֱ�־
��10��Ͷ�����
��11��ί������
��12��ί�м۸�
��13��ί�е���
��14����������
��15��ϵͳ���ĺ�
��16��ϯλ��
��17���µ�ϯλ
����Ӧ��
��ȷ
��1�� �ɹ���־ Y����ʾ�ѽ��ܳ�������
��2���������ɹ���
��3�� ί�е���
��4�� ϯλ��
��5�� ί��״̬���
��6�� ί��״̬����
��7�� ί������
��8�� δ�ɽ�����
��9�� �ɽ�����
��10���ɽ��۸�
��11������ʱ��
��12������������
��13���µ�ϯλ
����
��1�� �����־ N
��2�� �������
��3�� ��������
*/
//---------------------------------------------------------------------------
int TTrdItf_JSDFF::Undo() //ί�г���
{
    AnsiString cmd;

    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    AnsiString seat,ordid  ;
    //splitOrdid(FRequest.Undo.ContractID,seat,ordid);
    ordid = FRequest.Undo.ContractID;
    seat = GetSeatId(FRequest.Undo.Market);
    if (seat.Length()==0)
    {
        // query from order table
        try
        {
            char mkt[2];
			mkt[1] = 0;
			trade_db      FDB;
			FDB.connect();
            mkt[0] = FDB.qry_order_market(this->FAccInfo.Capital,FRequest.Undo.ContractID);
            seat = GetSeatId(this->ConvertMarketType(mkt));
        }
        catch(std::string &err)
        {
			this->SetError(-1,err.c_str());
            return -1;
        }
    }
    cmd.cat_printf("%s||||||||%s|||%s||",
        GetRequestHead("6022").c_str(),
        ordid.c_str(),                //��ͬ��
        seat.c_str()        //ϯλ�ţ�������
        );

    TStringList *lstDD = new TStringList();
    try
    {
        //  �ɹ���־ Y����ʾ�ѽ��ܳ�������|ί�е���
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) != DEF_ACK_OK)
        {
            return FLastError.ErrorCode;
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

bool TTrdItf_JSDFF::GetConfig(void)
{
    if( FSetupFile== NULL ) return false;

    TMemIniFile *ini = new TMemIniFile( FSetupFile );
    try
    {
        // �ж��Ƿ���ڲ�������ã�û�еĻ�����false�Ա�ϵͳ�ܹ�����Ĭ�ϵ�����
        if( ini->SectionExists(PLUGINNAME) == false ) return false;

        FJSDSet.SvrIp            = ini->ReadString (PLUGINNAME,"SvrIP",FJSDSet.SvrIp);
        FJSDSet.SvrPort          = ini->ReadInteger(PLUGINNAME,"SvrPort",FJSDSet.SvrPort);
        FJSDSet.TimeOut          = ini->ReadInteger(PLUGINNAME,"TimeOut",FJSDSet.TimeOut);
        FJSDSet.debug_mode       = ini->ReadBool(PLUGINNAME,"debug_mode",FJSDSet.debug_mode);
        FJSDSet.branch_no        = ini->ReadString(PLUGINNAME,"branch_no",FJSDSet.branch_no);
        FJSDSet.gw_ver           = ini->ReadString (PLUGINNAME,"gw_ver",FJSDSet.gw_ver);
        FJSDSet.sysCenter        = ini->ReadString (PLUGINNAME,"sysCenter",FJSDSet.sysCenter);
        lstrcpyn(FJSDSet.jysID,ini->ReadString (PLUGINNAME,"jysID",FJSDSet.jysID).c_str(),5);
        /*
        for(int i=0;i<4;i++)
        {
        FJSDSet.seatID[i] =  ini->ReadString (PLUGINNAME,"seatID" + IntToStr(i),FJSDSet.seatID[i]);
        FJSDSet.JyCode[i] =  ini->ReadString (PLUGINNAME,"JyCode" + IntToStr(i),FJSDSet.JyCode[i]);
        }
        */
    }
    __finally
    {
        delete ini;
    }
    return true;
}

void TTrdItf_JSDFF::SetConfig(void)
{
    if( FSetupFile== NULL ) return ;

    TMemIniFile *ini = new TMemIniFile( FSetupFile );
    try
    {
        ini->WriteString (PLUGINNAME,"SvrIP",            FJSDSet.SvrIp);
        ini->WriteInteger(PLUGINNAME,"SvrPort",          FJSDSet.SvrPort);
        ini->WriteInteger(PLUGINNAME,"TimeOut",          FJSDSet.TimeOut);
        ini->WriteBool   (PLUGINNAME,"debug_mode",       FJSDSet.debug_mode);
        ini->WriteString(PLUGINNAME,"branch_no",        FJSDSet.branch_no);
        ini->WriteString (PLUGINNAME,"gw_ver",           FJSDSet.gw_ver);
        ini->WriteString (PLUGINNAME,"sysCenter",        FJSDSet.sysCenter);
        ini->WriteString (PLUGINNAME,"jysID",            FJSDSet.jysID);
        for(int i=0;i<strlen( FJSDSet.jysID );i++)
        {
            ini->WriteString (PLUGINNAME,"seatID" + IntToStr(i),FJSDSet.seatID[i]);
            ini->WriteString (PLUGINNAME,"JyCode" + IntToStr(i),FJSDSet.JyCode[i]);
        }

        ini->UpdateFile();
    }
    __finally
    {
        delete ini;
    }
}

market_type  TTrdItf_JSDFF::ConvertMarketType(const char *t)
{
    if(t==NULL || strlen(t)<1 ) return mtNo;

    if( strlen(t) == 1 )
    {
        if(t[0] ==  FJSDSet.jysID[0])
            return mtFZZ;
        else if( t[0] == FJSDSet.jysID[1])
            return mtFDL;
        else if( t[0] == FJSDSet.jysID[2] )
            return mtFSH;
        else if( t[0] == FJSDSet.jysID[3] )
            return mtJJS;
        else
            return mtNo;
    }
    else
    {
        if( lstrcmpi(t ,  FJSDSet.seatID[0].c_str())==0)
            return mtFZZ;
        else if( lstrcmpi(t , FJSDSet.seatID[1].c_str())==0)
            return mtFDL;
        else if( lstrcmpi(t , FJSDSet.seatID[2].c_str())==0 )
            return mtFSH;
        else if( lstrcmpi(t , FJSDSet.seatID[3].c_str())==0 )
            return mtJJS;
        else
            return mtNo;
    }
	return mtNo;
}

order_type   TTrdItf_JSDFF::ConvertOrderType(const char *t)
{
    return SConvertOrderType(t);
}

order_state  TTrdItf_JSDFF::ConvertOrderState(const char *t)
{
    /*
    oswb = '0', //δ��(�ȴ��걨��...)
    osyb = '1', //�ѱ�(�Ѿ�����,��û���κγɽ�,�ȴ��ɽ���...)
    osdc = '2', //����(�����������µȴ�����)
    osbw = '3', //����(ȷ��״̬,���ֳ��������ֳɽ�)
    osyc = '4', //�ѳ�(ȷ��״̬,ȫ��������)
    oscj = '5', //�ѳ�(ȷ��״̬,��ȫ�ɽ�)
    osyf = '6', //�ѷ�(ȷ��״̬,ϵͳ����)
    osbc = '7', //����(�Ѿ��гɽ���,���ڳɽ���...
    osno = 'N'  //δ֪
    */

    if( t==NULL || strlen(t) < 1 ) return osno;

    switch(t[0])
    {
    case WAITING:
    case SENDING:
        return oswb;
    case ACCEPTED:
        return osyb;
    case FILLING:
        return osbc;
    case FILLED:
        return oscj;
    case DELETEING:
        return osdc;
    case SYS_REJECTED:
        return osyf;
    case USER_REJECTED:
        return osyf;
    case DELETED:
        return osyc;
    case PCPD:
        return osbw;
    }
    return osno;
}

pos_direction TTrdItf_JSDFF::ConvertPosDir(const char *t)
{
    /*
    pdNo    = 'U', // δ֪
    pdNet   = 'N', // ��
    pdLong	= 'L', // ��ͷ
    pdShort = 'S'	 // ��ͷ
    */
    return pdNo;
}

money_type   TTrdItf_JSDFF::ConvertMoneyType(const char *t)
{
    /*
    motRMB = 'R', //RMB
    motUSD = 'U', //USD
    motHKD = 'H', //HKD
    motNo  = 'N'  //δ֪
    */
    return motNo;
}

char *  TTrdItf_JSDFF::ConvertMarketType(market_type t)
{
    char ret[2] = {'0','0'};
    switch(t)
    {
    case mtFZZ : ret[0] = FJSDSet.jysID[0];
        break;
    case mtFDL : ret[0] = FJSDSet.jysID[1];
        break;
    case mtFSH : ret[0] = FJSDSet.jysID[2];
        break;
    case mtJJS : ret[0] = FJSDSet.jysID[3];
        break;
    }
    return ret;
}

char *  TTrdItf_JSDFF::ConvertOrderType(order_type t)
{
    char ret[3]={'0','0','0'};
    switch(t)
    {
    case otOpenBuy:
        ret[0] = OPEN;
        ret[1] = BUY;
        break;
    case otOpenSell:
        ret[0] = OPEN;
        ret[1] = SELL;
        break;
    case otCloseBuy :
        ret[0] = CLOSE;
        ret[1] = BUY;
        break;
    case otCloseSell:
        ret[0] = CLOSE;
        ret[1] = SELL;
        break;
    case otCloseTodayBuy:
        ret[0] = CLOSE_TODAY;
        ret[1] = BUY;
        break;
    case otCloseTodaySell:
        ret[0] = CLOSE_TODAY;
        ret[1] = SELL;
        break;
    }
    return ret;
}

AnsiString TTrdItf_JSDFF::convert_to_PTS_code(const char * jsdcode,market_type mt)
{
    if (mt!= mtFZZ) {
        return jsdcode;
    }
    // ��֣�ݵĽ�ʿ�����ת��ΪPTS�Ĵ����� SR1001 to SR001 ,SR0909 to SR909
    assert(jsdcode != NULL );
    int len = strlen(jsdcode);
    AnsiString ret;
    for( int i=0;i<len;i++)
    {
        if (isalpha(jsdcode[i])) {
            ret = ret + jsdcode[i];
        }
        else
        {
            ret =ret + AnsiString(jsdcode + i+1);
            return ret;
        }
    }
    return ret;
}

AnsiString TTrdItf_JSDFF::convert_to_JSD_code(const char * ptscode,market_type mt)
{
    if (mt!= mtFZZ) {
        return ptscode;
    }
    // ��֣�ݵ�PTS�Ĵ���ת��Ϊ��ʿ��Ĵ����� SR001 to SR1001  ,SR909 to SR0909
    unsigned short y,m,d;
    DecodeDate(Date(),y,m,d);
	y = y % 100;

    assert(ptscode != NULL );
    int len = strlen(ptscode);

    AnsiString ret ="";

	char year[10] = {"\0"};
    const char *month = NULL;
    for( int i=0;i<len;i++)
    {
        if (isdigit(ptscode[i]))
        {
            // �ҵ�һ������Ϊ���
            year[0] = ptscode[i];
            year[1] = 0;
            month = ptscode + i +1;
            if (strlen(month)!=2) {
                return ptscode;
            }
            else
            {
                int lyear = atoi(year);
                if (abs(lyear-y)>=1) {
                    lyear=y+1;
                }
                ret.cat_printf("%02d%s",lyear,month);
                return ret;
            }
        }
        else
        {
            ret = ret + ptscode[i];
        }
    }
    return ret;
}

/*
6031 ��Ӫҵ������---GETYYBMC������Ӧ������������
��1��	���ܺ� 6031
��2��	Ӫҵ������
��3��	ί�з�ʽ
��4��	�ͻ���
��5��	�ͻ�����

����Ӧ��
 �ɹ�
��1��	�ɹ���־  Y
��2��	Ӫҵ������
����
��1��	�����־  N
��2��	�������
��3��	��������
*/
int TTrdItf_JSDFF::QryYYB(void)     //�ʽ��ѯ
{
	AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

	cmd.cat_printf("%s|%s|",
		GetRequestHead("6031").c_str()
		);

	TStringList *lstDD = new TStringList();
    try
	{
		if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
			ODS('M',PLUGINNAME,"Dogfood:%s",lstDD->Strings[INDEX(2)].c_str());
        }
        else
        {
            return FLastError.ErrorCode;
        }
    }
    __finally
    {
    		delete lstDD;
    }

    return 0;
}


int  TTrdItf_JSDFF::KeepAlive(void)
{
	g_recvth->SendPing();
	lock();
	try
	{
		if(FidTcp->Connected() !=true || FHasSetAccInfo==false) return -1;
        QryYYB();
	}
	__finally
	{
	unlock();
	}

	return 0;
}
