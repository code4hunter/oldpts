//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdItf_JSD.h"
#include <assert.h>

#pragma package(smart_init)

const char * REQUEST_NUM = "100";
const char * ENTRUST_WAY[8]={"ZZWT","RJWT","DHWT","KSWT","WSWT",};

//---------------------------------------------------------------------------

TTrdItf_JSD::TTrdItf_JSD(TJSDSet *set)
{
    CopyMemory(&FJSDSet,set,sizeof(TJSDSet));
    FidTcp = new TIdTCPClient(NULL);
    FidIPWatch = new TIdIPWatch(NULL);
}

TTrdItf_JSD::~TTrdItf_JSD()
{
    FidTcp->Disconnect();
    delete FidTcp;
    delete FidIPWatch;
}

AnsiString TTrdItf_JSD::GetErrorText(int code, char *error)
{
    AnsiString text;
    text.printf("A\r\nLocal\r\n%d\r\nN\r\n%s\r\n%d", REQUEST_NUM, error, code);
    return text; 
}

AnsiString TTrdItf_JSD::ReadNextData()
{
    AnsiString cmd;
    cmd.printf("R|%s|%s|0|%s|%s|", FidIPWatch->LocalIP().c_str(),
        REQUEST_NUM, FJSDSet.branch_no, ENTRUST_WAY[FJSDSet.entrust_way]);
    return ReadFirstData(cmd);
}

AnsiString TTrdItf_JSD::ReadFirstData(AnsiString cmd)
{
    //����ϴεķ�����Ϣ
    int n = FidTcp->ReadFromStack(true, 1, true, NULL);
    if (n > 0) FidTcp->ReadString(n);

    //ODS(cmd.c_str());
    FidTcp->Write(cmd);

    n = FidTcp->ReadFromStack(true, FJSDSet.TimeOut, true, NULL);
    if (n <= 0) return "A|192.168.0.1|100|N|�������ݳ�ʱ|-100"  ;

    AnsiString ret = FidTcp->ReadString(n);
    //ODS(ret.c_str());

    return ret;
}

int TTrdItf_JSD::SplitData(AnsiString SD, TStringList *lstDD, int count)
{
    char seps[] = "|";
    char *substr;
    char *data;
    assert(lstDD != NULL);

    lstDD->Clear();
    try
    {
        SD = SD.Trim();
        data = new char[SD.Length() + 1];
        memset(data, 0, SD.Length() + 1);
        strncpy(data, SD.c_str(), SD.Length());

        substr = strtok(data, seps);
        while (substr != NULL)
        {
            lstDD->Add(substr);
            substr = strtok(NULL, seps);
        }
    }
    __finally
    {
        delete []data;
    }

    if (lstDD->Count < 4)
    {
        lstDD->Text = GetErrorText(-501, "���ݽ���ʧ��");
        return DEF_ACK_ERROR;
    }

    if (lstDD->Strings[0] != "A")
    {
        lstDD->Text = GetErrorText(-502, "���Ƿ�������");
        return DEF_ACK_ERROR;
    }
    
    if (lstDD->Strings[3] == "N" )
    {
        if (lstDD->Count == 4)
            lstDD->Text = GetErrorText(-503, "δ֪���󣡣���");
        else if (lstDD->Count == 5)
            lstDD->Text = GetErrorText(-503, lstDD->Strings[4].c_str());

        return DEF_ACK_ERROR;
    }

    //if (lstDD->Strings[3] == "Y" && lstDD->Count == count)
    //    return DEF_ACK_OK;
    if (lstDD->Count >= count)
        return DEF_ACK_OK;


    lstDD->Text = GetErrorText(-504, "δ֪���󣡣���");
    return DEF_ACK_ERROR;
}

int TTrdItf_JSD::Init()  //��ʼ��
{
    try
    {
        if (!FidTcp->Connected())
        {
            FidTcp->Host = FJSDSet.SvrIp;
            FidTcp->Port = FJSDSet.SvrPort;
            FidTcp->Connect();
        }
    }
    catch (...)
    {
        ODS("���ӹ�̨ʧ��!");
    }

    return FidTcp->Connected()==true ? 0 : -1;
}

//--------------------------------------------------------------------------
// CMD:���ܺ�(2)|����Ӫҵ������|�г�����|��ʱ����|�ʺ�|����|ί�з�ʽ|
// 

//--------------------------------------------------------------------------
int TTrdItf_JSD::SetAccount() //�����ʺ�
{
    AnsiString cmd;


    TStringList *lstDD = new TStringList();

    try
    {

        cmd.printf("R|%s|%d|1|%s|0||%s|%s|%s|",
            FidIPWatch->LocalIP().c_str(),
            REQUEST_NUM,
            FJSDSet.branch_no,
            FRequest.SetAccount.Account,
            ENTRUST_WAY[FJSDSet.entrust_way], "");

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 6) == DEF_ACK_OK)
        {
            if (lstDD->Strings[INDEX(5)].Length() > 0)
                FJSDSet.money_type = lstDD->Strings[INDEX(5)][1];
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }

        // 1. ���ܺ�(2)  2.����Ӫҵ������  3.�г�����  4.��ʱ����  5.�ʺ� 6.���� 7.ί�з�ʽ
        if(FRequest.SetAccount.Sort == asCA)
        {
            cmd.printf("R|%s|%s|2|%s|0||%s|%s|%s|", FidIPWatch->LocalIP().c_str(),
                REQUEST_NUM, FJSDSet.branch_no, FRequest.SetAccount.Account,
                FRequest.SetAccount.PW, ENTRUST_WAY[FJSDSet.entrust_way]);
        }
        else if(FRequest.SetAccount.Sort==asSH)
        {
            cmd.printf("R|%s|%s|2|%s|1||%s|%s|%s|", FidIPWatch->LocalIP().c_str(),
                REQUEST_NUM, FJSDSet.branch_no, FRequest.SetAccount.Account,
                FRequest.SetAccount.PW, ENTRUST_WAY[FJSDSet.entrust_way]);
        }
        else if(FRequest.SetAccount.Sort==asSZ)
        {
            cmd.printf("R|%s|%s|2|%s|2||%s|%s|%s|", FidIPWatch->LocalIP().c_str(),
                REQUEST_NUM, FJSDSet.branch_no, FRequest.SetAccount.Account,
                FRequest.SetAccount.PW, ENTRUST_WAY[FJSDSet.entrust_way]);
        }
        else
            return -1;

        //  �װ���1.�ɹ���־  2.����     3.�ͻ���   4.�г�����
        //��̰���1.�г�����  2.�г����� 3.�ɶ����� 4.���ִ���  5.��������

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 4) == DEF_ACK_OK)
        {
            strncpy(FAccInfo.Capital, lstDD->Strings[5].c_str(), 13);
            int count = lstDD->Strings[6].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 5) == DEF_ACK_OK)
                {
                    if (lstDD->Strings[3] == "1")
                        strncpy(FAccInfo.SH, lstDD->Strings[5].c_str(), 13);
                    else if (lstDD->Strings[3] == "2")
                        strncpy(FAccInfo.SZ, lstDD->Strings[5].c_str(), 13);

                    break;
                }
            }

            strncpy(FAccInfo.PW, FRequest.SetAccount.PW, 13);

            if(FRequest.SetAccount.Sort==asSH)
            {
              lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,13);
            }
            else if(FRequest.SetAccount.Sort==asSZ)
            {
              lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,13);
            }

            if(FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) { return -1; }

			      NewAns(1);
			      memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }

        
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

//////��ѯ����//////
// ��ʱ�����ѯ��v5.83����60
int TTrdItf_JSD::GetTrdInfo()   //ȡ���̿�����
{
	char et;

	switch (FRequest.GetTrdInfo.SecuID[0])
    {
        case 'H' : et = '1'; break;
        case 'S' : et = '2'; break;
        case 'P' : et = '1'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //      -----1----|------2-------|----3---|----4---|----5---|----6---|---7----|
    // CMD  ���ܺ�(60)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���  |֤ȯ����|ί�з�ʽ|
    //
    //               1| 2| 3|| 5| 6| 7|
    cmd.cat_printf("60|%s|%c||%s|%s|%s|",
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        FRequest.GetTrdInfo.SecuID + 1,            // 6
        ENTRUST_WAY[FJSDSet.entrust_way]           // 7
    );

    TStringList *lstDD = new TStringList();
    try
    {
        //  1.�ɹ���־    2.ָ��  3.֤ȯ����  4.֤ȯ����    5.���¼�  6.�ǵ�  7.�ǵ�ֵ
        //  8.����        9.���¼۳ɽ���     10.�ܳɽ���� 11.���� 12.�����̼�
        // 13.������߼� 14.������ͼ�       15.���1      16.����1  17.���2
        // 18.����2      19.���3            20.����3      21.����1  22.����1
        // 23.����2      24.����2            25.����3      26.����3  27.ͣ�Ʊ�־
        // 28.�ǵ�ֵ     29.���4            30.����4      31.����4  32.����4
        // 33.ÿ��ԪӦ����Ϣ��               34.��ծȫ��   35.֤ȯ��𣨴��࣫���

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 35) == DEF_ACK_OK)
        {
			NewAns(1);
			TGetTrdInfo_Ans *gi = &(*FAnswer)[0].GetTrdInfo;
			gi->BuyInfo.ZXJ    = StrToFloatDef(lstDD->Strings[INDEX(5)], -1);
			gi->BuyInfo.Price1 = StrToFloatDef(lstDD->Strings[INDEX(15)], -1);
			gi->BuyInfo.Price2 = StrToFloatDef(lstDD->Strings[INDEX(17)], -1);
			gi->BuyInfo.Price3 = StrToFloatDef(lstDD->Strings[INDEX(19)], -1);
			gi->BuyInfo.Volum1 = StrToIntDef(lstDD->Strings[INDEX(16)], -1);
			gi->BuyInfo.Volum2 = StrToIntDef(lstDD->Strings[INDEX(18)], -1);
			gi->BuyInfo.Volum3 = StrToIntDef(lstDD->Strings[INDEX(20)], -1);
			gi->BuyInfo.CJSL   = StrToIntDef(lstDD->Strings[INDEX(9)], -1);

			gi->SellInfo.ZXJ    = StrToFloatDef(lstDD->Strings[INDEX(5)], -1);
			gi->SellInfo.Price1 = StrToFloatDef(lstDD->Strings[INDEX(21)], -1);
			gi->SellInfo.Price2 = StrToFloatDef(lstDD->Strings[INDEX(23)], -1);
			gi->SellInfo.Price3 = StrToFloatDef(lstDD->Strings[INDEX(25)], -1);
			gi->SellInfo.Volum1 = StrToIntDef(lstDD->Strings[INDEX(22)], -1);
			gi->SellInfo.Volum2 = StrToIntDef(lstDD->Strings[INDEX(24)], -1);
			gi->SellInfo.Volum3 = StrToIntDef(lstDD->Strings[INDEX(26)], -1);
			gi->SellInfo.CJSL   = StrToIntDef(lstDD->Strings[INDEX(9)], -1);
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

//��ѯ�ʽ����Ϳ����ʽ���9
int TTrdItf_JSD::QryMoney()     //�ʽ��ѯ
{

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //      ----1----|------2-------|----3---|----4---|----5---|
    // CMD  ���ܺ�(9)|����Ӫҵ������|���Ҵ���|��ʱ����|�ͻ���  |
    //
    //              1| 2| 3|| 5|
    cmd.cat_printf("9|%s|%c||%s|",
        FJSDSet.branch_no,                         // 2
        FJSDSet.money_type,                        // 3
        FAccInfo.Capital);                         // 5

    TStringList *lstDD = new TStringList();
    try
    {
        // 1.�ɹ���־  2.�ʽ����  3.�����ʽ�  4.����δ���ս��  5.����δ���ս��
        // 6.ί��δ�ɽ�������    7.��������  8.�쳣�����ʽ�

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 8) == DEF_ACK_OK)
        {
			NewAns(1);
			(*FAnswer)[0].QryMoney.Balance = StrToFloatDef(lstDD->Strings[4] ,-1);
			(*FAnswer)[0].QryMoney.Available = StrToFloatDef(lstDD->Strings[5],-1);
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

int TTrdItf_JSD::QryStock()     //�ɷݲ�ѯ
{
	char et;
	switch (FRequest.QryStock.SecuID[0])
    {
        case 'H' : et = '1'; break;
        case 'S' : et = '2'; break;
        case 'P' : et = '1'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    //CMD 1.���ܺ�(56) 2.����Ӫҵ������ 3.�г����� 4.��ʱ���� 5.�ͻ��� 6.��ѯ�г����루�ո��ʾ�����г���|
    //    7.��ѯ֤ȯ���루Ϊ�ո�ʱ��ʾ��ѯ���й�Ʊ������ֻ��ѯĳһֻ��Ʊ�����|
    //    8.�ɶ����루�ո��ʾ���йɶ����룩9.�����г����� 10.����֤ȯ���� 11.�����ɶ��ʺ�
    //    12.��෵������ 13.�������ܣ�1��ϸ��2���ܣ�14.ί�з�ʽ
    //    15.���Ҵ��루v5.20.2ʵ�֣�����ѯ�г�����Ϊ�ն����Ҵ��벻Ϊ��ʱ�����ѯ�û��ҵ��г�{��A����A}��|
    //    16.�Ƿ񷵻غϼ�ֵ��1�����غϼ�ֵ�����������أ�17.������ʼ���ڣ�Ϊ�գ������������Ϣ��|
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|12| |14|15|16||
    cmd.cat_printf("56|%s|%c||%s|%c|%s|%s|%s|%s|%s|%d|1|%s|%c|-1||",
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        et,                                        // 6
        FRequest.QryStock.SecuID + 1,              // 7
        et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 8
        "",                                        // 9
        "",                                        // 10
        "",                                        // 11
        1,                                         // 12
        ENTRUST_WAY[FJSDSet.entrust_way],          // 14
        FJSDSet.money_type);                       // 15

    TStringList *lstDD = new TStringList();
    try
    {
        //  1.�г�����  2.�ɶ��ʺ�   3.֤ȯ���� 4.֤ȯ����  5.���(���ϵ��ճɽ�)
        //  6.�������  7.��������ɽ�����      8.��������δ�ɽ�����  9.��������ɽ����
        // 10.�ɱ��۸� 11.���¼�    12.��ֵ    13.����ӯ�� 14.���������ɽ����
        // 15.�������� 16.һ�仰������Ϣ       17.��ծ���� 18.ÿ��ԪӦ����Ϣ(���ǹ�ծΪ0)
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            if (count <= 0) return DEF_OTHER_ERROR;

            if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 18) == DEF_ACK_OK)
            {
                NewAns(1);
                TQryStock_Ans *sa = &(*FAnswer)[0].QryStock;

                sa->Balance    = StrToFloatDef(lstDD->Strings[INDEX(5)], -1);
                sa->Available  = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);
                sa->BuyFreeze  = 0;
                sa->SellFreeze = 0;
            }
            else
            {
                ODS(lstDD->Strings[4].c_str());
                return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
            }
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

int TTrdItf_JSD::QryCanBuy()    //ȡ��������
{
    return -1;
}

int TTrdItf_JSD::QryDetail()    //�ɽ���ѯ
{
  int reqry_num=0;

HH:

  if(FRequest.QryDetail.ContractID[0]==0) return -1;
	char et;
	switch (FRequest.QryDetail.Bourse)
    {
        case bsSH : et = '1'; break;
        case bsSZ : et = '2'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //      -----1----|------2-------|----3---|----4---|--5---|---6----|
    //      ���ܺ�(14)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ʼ����|
    //      -----7----|---------------8--------------|------------------9---------------|
    //      ��ֹ����  |��ͬ��(Ϊ�ո�ʱ��ѯ��������)  |֤ȯ����(Ϊ�ո�ʱ��ѯ���й�Ʊ����)|
    //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
    //      ��෵������|��������|������ͬ��|ί�з�ʽ|�����г�����|����ʽ(0-�г����롢1-ί��ʱ�䡢2-ί��ʱ�䵹��)|
    //
    //               1| 2| 3|| 5| 6| 7| 8|9| |||13|| |
    cmd.cat_printf("14|%s|%c||%s|%s|%s|%s| |1|||%s||0|",
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        Now().FormatString("yyyymmdd").c_str(),    // 6
        Now().FormatString("yyyymmdd").c_str(),    // 7
        FRequest.QryDetail.ContractID,             // 8
        ENTRUST_WAY[FJSDSet.entrust_way]           // 13
    );

    TStringList *lstDD = new TStringList();
    try
    {
        // 1.�ɶ��ʺ� 2.�������  3.֤ȯ����  4.֤ȯ����  5.ί������  6.ί�м۸�
        // 7.��ͬ��   8.�ɽ�����  9.�ɽ��۸� 10.ί��״̬ 11.�ɽ�״̬ 12.�ɽ�ʱ��
        //13.����    14.������Ϣ 15.�ɹ���־ 16.�г�����
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            //int count = lstDD->Strings[INDEX(2)].ToIntDef(0);
            //if (count <= 0) return -1;
            
            if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 16) == DEF_ACK_OK)
            {
			        NewAns(1);
			        (*FAnswer)[0].QryDetail.Num   = StrToIntDef(lstDD->Strings[INDEX(8)], -1);
			        (*FAnswer)[0].QryDetail.Price = StrToFloatDef(lstDD->Strings[INDEX(9)], -1);
                (*FAnswer)[0].QryDetail.UndoNum = 0;

                if (lstDD->Strings[INDEX(11)] == "���ڳ���" ||
                    lstDD->Strings[INDEX(11)] == "���⳷��" ||
                    (lstDD->Strings[INDEX(11)] == "���ֳ���" && (*FAnswer)[0].QryDetail.Num > 0))
                {
                  if(lstDD->Strings[INDEX(11)] == "���ֳ���" && ++reqry_num < 3 ) //����ǲ������ٲ�ֱ�� reqry_num >3
                  {
                    delete lstDD;
                    Idglobal::Sleep(100);
                    goto HH;
                  }

                  int csnnum = lstDD->Strings[INDEX(5)].ToIntDef(0);
                  (*FAnswer)[0].QryDetail.UndoNum = (*FAnswer)[0].QryDetail.Num - csnnum ;
                }

                //if((*FAnswer)[0].QryDetail.Price<0.001) (*FAnswer)[0].QryDetail.Num=0;
            }
            else
            {
                ODS(lstDD->Strings[4].c_str());
                return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
            }
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }
    return 0;
}

int TTrdItf_JSD::QryHisDetail() //��ʷ�ɽ���ѯ
{
    // ��ʱ����
    return -1;
}

int TTrdItf_JSD::QryCsn()       //��ѯĳ��ί�к�ͬ
{
    // ��ʱ����
    return -1;
}

int TTrdItf_JSD::QryCurCsn()    //����ί�в�ѯ
{
    AnsiString idxDate = "";
    AnsiString idxContractID = "";
    AnsiString idxMartCode = "";
    AnsiString date = Now().FormatString("yyyymmdd");
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //      -----1----|------2-------|----3---|----4---|--5---|---6----|
    //      ���ܺ�(14)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ʼ����|
    //      -----7----|---------------8--------------|------------------9---------------|
    //      ��ֹ����  |��ͬ��(Ϊ�ո�ʱ��ѯ��������)  |֤ȯ����(Ϊ�ո�ʱ��ѯ���й�Ʊ����)|
    //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
    //      ��෵������|��������|������ͬ��|ί�з�ʽ|�����г�����|����ʽ(0-�г����롢1-ί��ʱ�䡢2-ί��ʱ�䵹��)|
    //
    //               1| 2| 3|| 5| 6| 7|8|9|10|11|12|13|14| |
    cmd.cat_printf("14|%s|%c||%s|%s|%s| | |%d|%s|%s|%s|%s|0|",
        FJSDSet.branch_no,                          // 2
        ' ',                                        // 3
        FAccInfo.Capital,                           // 5
        date.c_str(),                               // 6
        date.c_str(),                               // 7
        1000,                                       // 10
        idxDate.c_str(),                            // 11
        idxContractID.c_str(),                      // 12
        ENTRUST_WAY[FJSDSet.entrust_way],           // 13
        idxMartCode.c_str()                         // 14
    );

    try
    {
        // 1.�ɶ��ʺ� 2.�������  3.֤ȯ����  4.֤ȯ����  5.ί������  6.ί�м۸�
        // 7.��ͬ��   8.�ɽ�����  9.�ɽ��۸� 10.ί��״̬ 11.�ɽ�״̬ 12.�ɽ�ʱ��
        //13.����    14.������Ϣ 15.�ɹ���־ 16.�г�����
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                {
                    TConsignInfo *ci = new TConsignInfo;
                    memset(ci, 0, sizeof(TConsignInfo));

                    strncpy(ci->ContractID,lstDD->Strings[INDEX( 7)].c_str(), 8);
                    strncpy(ci->SecuID,    lstDD->Strings[INDEX( 3)].c_str(), 7);
                    strncpy(ci->SecuDesc,  lstDD->Strings[INDEX( 4)].c_str(), 8);
                    strncpy(ci->Time,      lstDD->Strings[INDEX(12)].c_str(), 8);
                    strncpy(ci->Date,      lstDD->Strings[INDEX(13)].c_str(), 8);

                    //ODS(lstDD->Strings[INDEX(16)].c_str());
                    ci->Bourse = lstDD->Strings[INDEX(16)][1] - 1;

                    ci->Type =ConvertType(lstDD->Strings[INDEX(2)].c_str());
                        
                    ci->State  = 'N';
                    ci->CsnVol = StrToIntDef(lstDD->Strings[INDEX(5)], -1);
                    ci->TrdVol = StrToIntDef(lstDD->Strings[INDEX(8)], -1);
                    ci->CancelVol = 0;
                    ci->CsnPrice  = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);;
                    ci->TrdPrice  = StrToFloatDef(lstDD->Strings[INDEX(9)], -1);;

                    idxDate         = lstDD->Strings[INDEX(13)];
                    idxContractID   = lstDD->Strings[INDEX(7)];
                    idxMartCode     = lstDD->Strings[INDEX(16)];

                     if (lstDD->Strings[INDEX(11)] == "���ڳ���" ||
                        lstDD->Strings[INDEX(11)] == "���⳷��" ||
                        (lstDD->Strings[INDEX(11)] == "���ֳ���" && ci->TrdVol > 0))
                    {
                        int csnnum = lstDD->Strings[INDEX(5)].ToIntDef(0);
                        ci->CancelVol = ci->TrdVol - csnnum ;
                    }

                    lstAns->Add(ci);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
                }
            }
            
            if (count > 0) goto _NEXT;

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryCurCsn.CsgInfo, ci, sizeof(TConsignInfo));
                }
            }

            for (int i = 0; i < lstAns->Count; i++)
            {
                TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
                delete ci;
            }
            lstAns->Clear();
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}

int TTrdItf_JSD::QryHisCsn()    //��ʷί�в�ѯ
{
    AnsiString idxDate = "";
    AnsiString idxContractID = "";
    AnsiString idxMartCode = "";
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //      -----1----|------2-------|----3---|----4---|--5---|---6----|
    //      ���ܺ�(14)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ʼ����|
    //      -----7----|---------------8--------------|------------------9---------------|
    //      ��ֹ����  |��ͬ��(Ϊ�ո�ʱ��ѯ��������)  |֤ȯ����(Ϊ�ո�ʱ��ѯ���й�Ʊ����)|
    //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
    //      ��෵������|��������|������ͬ��|ί�з�ʽ|�����г�����|����ʽ(0-�г����롢1-ί��ʱ�䡢2-ί��ʱ�䵹��)|
    //
    //               1| 2| 3|| 5| 6| 7|8|9|10|11|12|13|14| |
    cmd.cat_printf("14|%s|%c||%s|%s|%s| | |%d|%s|%s|%s|%s|0|",
        FJSDSet.branch_no,                          // 2
        ' ',                                        // 3
        FAccInfo.Capital,                           // 5
        FRequest.QryHisCsn.StartDay,                // 6
        FRequest.QryHisCsn.EndDay,                  // 7
        1000,                                       // 10
        idxDate.c_str(),                            // 11
        idxContractID.c_str(),                      // 12
        ENTRUST_WAY[FJSDSet.entrust_way],           // 13
        idxMartCode.c_str()                         // 14
    );

    try
    {
        // 1.�ɶ��ʺ� 2.�������  3.֤ȯ����  4.֤ȯ����  5.ί������  6.ί�м۸�
        // 7.��ͬ��   8.�ɽ�����  9.�ɽ��۸� 10.ί��״̬ 11.�ɽ�״̬ 12.�ɽ�ʱ��
        //13.����    14.������Ϣ 15.�ɹ���־ 16.�г�����
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                {
                    TConsignInfo *ci = new TConsignInfo;
                    memset(ci, 0, sizeof(TConsignInfo));

                    strncpy(ci->ContractID,lstDD->Strings[INDEX( 7)].c_str(), 8);
                    strncpy(ci->SecuID,    lstDD->Strings[INDEX( 3)].c_str(), 7);
                    strncpy(ci->SecuDesc,  lstDD->Strings[INDEX( 4)].c_str(), 8);
                    strncpy(ci->Time,      lstDD->Strings[INDEX(12)].c_str(), 8);
                    strncpy(ci->Date,      lstDD->Strings[INDEX(13)].c_str(), 8);

                    ci->Bourse = lstDD->Strings[INDEX(16)][1] - 1;


                    ci->Type =ConvertType(lstDD->Strings[INDEX(2)].c_str());
                        
                    ci->State  = 'N';
                    ci->CsnVol = StrToIntDef(lstDD->Strings[INDEX(5)], -1);
                    ci->TrdVol = StrToIntDef(lstDD->Strings[INDEX(8)], -1);
                    ci->CancelVol = 0;
                    ci->CsnPrice  = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);
                    ci->TrdPrice  = StrToFloatDef(lstDD->Strings[INDEX(9)], -1);
                    
                    idxDate         = lstDD->Strings[INDEX(13)];
                    idxContractID   = lstDD->Strings[INDEX(7)];
                    idxMartCode     = lstDD->Strings[INDEX(16)];

                    lstAns->Add(ci);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
                }
            }
            
            if (count > 0) goto _NEXT;

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryHisCsn.CsgInfo, ci, sizeof(TConsignInfo));
                }
            }

            for (int i = 0; i < lstAns->Count; i++)
            {
                TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
                delete ci;
            }
            lstAns->Clear();
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}

int TTrdItf_JSD::QryCurTrd()    //���ճɽ���ѯ
{
    AnsiString idxStock  = "";
    AnsiString idxTrdNo  = "";
    AnsiString idxAccout = "";
    AnsiString idxMartCode = "";
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();
    
_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    //
    //  1.���ܺ�(13)   2.����Ӫҵ������  3.�г�����     4.��ʱ����      5.�ͻ���
    //  6.��෵������ 7.����֤ȯ����    8.�����ɶ��ʺ� 9.�����ɽ���� 10.ί�з�ʽ
    // 11.�����г����루v5.83�����г�����=0��ѯ����ʱ�������룩
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|
    cmd.cat_printf("13|%s|%c||%s|%d|%s|%s|%s|%d|%s|",
        FJSDSet.branch_no,                          // 2
        ' ',                                        // 3
        FAccInfo.Capital,                           // 5
        1000,                                       // 6
        idxStock.c_str(),                           // 7
        idxAccout.c_str(),                          // 8
        idxTrdNo.c_str(),                           // 9
        ENTRUST_WAY[FJSDSet.entrust_way],           // 10
        idxMartCode.c_str()                         // 11
    );

    try
    {
        //
        // 1.�ɶ��ʺ� 2.�������  3.֤ȯ����  4.֤ȯ����  5.�ɽ�����  6.�ɽ��۸�
        // 7.�ɽ�ʱ�� 8.�ɽ����  9.��ͬ���� 10.�г����루9-10Ϊv5.83ʵ�֣�
        //
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 10) == DEF_ACK_OK)
                {
                    TTradeInfo *ti = new TTradeInfo;
                    memset(ti, 0, sizeof(TTradeInfo));

                    strncpy(ti->SecuID,   lstDD->Strings[INDEX(3)].c_str(), 7);
                    strncpy(ti->SecuDesc, lstDD->Strings[INDEX(4)].c_str(), 8);
                    strncpy(ti->Time,     lstDD->Strings[INDEX(7)].c_str(), 8);
                    strncpy(ti->Date,     Now().FormatString("yyyymmdd").c_str(), 8);
                    ti->Type  = ConvertType(lstDD->Strings[INDEX(2)].c_str());
                    ti->Vol   = StrToIntDef(lstDD->Strings[INDEX(5)], -1);
                    ti->Price = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);
                    
                    lstAns->Add(ti);
                    
                    idxStock    = lstDD->Strings[INDEX(3)];
                    idxTrdNo    = lstDD->Strings[INDEX(8)];
                    idxAccout   = lstDD->Strings[INDEX(1)];
                    idxMartCode = lstDD->Strings[INDEX(10)];
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
                }
            }
            
            if (count > 0) goto _NEXT;

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryHisTrd.TrdInfo, ti, sizeof(TTradeInfo));
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
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}

int TTrdItf_JSD::QryHisTrd()    //��ʷ�ɽ���ѯ
{
    AnsiString idxNo = "";
    AnsiString cmd;
    
    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";


    //  1.���ܺ�(62)  2.����Ӫҵ������  3.���Ҵ���   4.��ʱ����      5.�ͻ���
    //  6.��ʼ����    7.��ֹ����        8.������ˮ�� 9.��෵������ 10.ί�з�ʽ
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|
    cmd.cat_printf("62|%s|%c||%s|%s|%s|%s|%d|%s|",
        FJSDSet.branch_no,                          // 2
        FJSDSet.money_type,                         // 3
        FAccInfo.Capital,                           // 5
        FRequest.QryHisTrd.StartDay,                // 6
        FRequest.QryHisTrd.EndDay,                  // 7
        idxNo.c_str(),                              // 8
        1000,                                       // 9
        ENTRUST_WAY[FJSDSet.entrust_way]            // 10
    );

    try
    {

        // 1.�ɽ�����  2.�ɶ�����  3.������־  4.֤ȯ����  5.֤ȯ����  6.�ɽ�����
        // 7.�ɽ��۸�  8.�ɽ����  9.�䶯��� 10.�ʽ���� 11.��Ʊ��� 12.Ӷ��
        //13.ӡ��˰   14.������   15.�������� 16.�ɽ�ʱ�� 17.��ͬ��� 18.�ɽ����
        //19."1"��"2"��           20.��ˮ��(=8λ����+6λ���)         21.�ɽ�����abs

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[INDEX(2)].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                {
                    TTradeInfo *ti = new TTradeInfo;
                    memset(ti, 0, sizeof(TTradeInfo));

                    strncpy(ti->SecuID,   lstDD->Strings[INDEX( 4)].c_str(), 7);
                    strncpy(ti->SecuDesc, lstDD->Strings[INDEX( 5)].c_str(), 8);
                    strncpy(ti->Time,     lstDD->Strings[INDEX(16)].c_str(), 8);
                    strncpy(ti->Date,     lstDD->Strings[INDEX( 1)].c_str(), 8);
                    ti->Type  = ConvertType(lstDD->Strings[INDEX(19)].c_str());
                    ti->Vol   = StrToIntDef(lstDD->Strings[INDEX(6)], -1);
                    ti->Price = StrToFloatDef(lstDD->Strings[INDEX(7)], -1);

                    idxNo = lstDD->Strings[INDEX(20)];
                    lstAns->Add(ti);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
                }
            }


            if (count > 0) goto _NEXT;

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryHisTrd.TrdInfo, ti, sizeof(TTradeInfo));
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
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}

int TTrdItf_JSD::QryBill()      //��ѯ�ʽ���ˮ�����ʵ���
{
    AnsiString idxNo = "";
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //
    //  1.���ܺ�(11)  2.����Ӫҵ������  3.�г�����  4.��ʱ����     5.�ͻ���
    //  6.���ִ���    7.��ʼ����        8.��ֹ����  9.������ˮ��  10.��෵������
    // 11.ί�з�ʽ
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|
    cmd.cat_printf("11|%s|%c||%s|%c|%s|%s|%s|%d|%s|",
        FJSDSet.branch_no,                          // 2
        ' ',                                        // 3
        FAccInfo.Capital,                           // 5
        FJSDSet.money_type,                         // 6
        FRequest.QryBill.StartDay,                  // 7
        FRequest.QryBill.EndDay,                    // 8
        idxNo.c_str(),                              // 9
        1000,                                       // 10
        ENTRUST_WAY[FJSDSet.entrust_way]            // 11
    );

    try
    {
        // 1.ժҪ   2.�䶯���  3.�������  4.�ɶ��ʺ�  5.֤ȯ����  6.�������
        // 7.�ɽ��� 8.�ɽ���    9.�ɽ���� 10.��ˮ��   11.ժҪ��� 12.��ͬ���루v5.81.2��

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[INDEX(2)].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 12) == DEF_ACK_OK)
                {
                    TFundInfo *fi = new TFundInfo;
                    memset(fi, 0, sizeof(TFundInfo));

                    strncpy(fi->SecuID,   lstDD->Strings[INDEX( 5)].c_str(), 7);
                    //strncpy(fi->SecuDesc, lstDD->Strings[INDEX( 5)].c_str(), 8);

                    strncpy(fi->Type, lstDD->Strings[INDEX(6)].c_str(), 12);
                    fi->Vol   = StrToIntDef(lstDD->Strings[INDEX(7)], -1);
                    fi->Price = StrToFloatDef(lstDD->Strings[INDEX(8)], -1);
                    fi->TrdMny  = StrToFloatDef(lstDD->Strings[INDEX(2)], -1);
                    fi->Balance = StrToFloatDef(lstDD->Strings[INDEX(3)], -1);

                    idxNo = lstDD->Strings[INDEX(10)];
                    lstAns->Add(fi);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
                }
            }
            
            if (count > 0) goto _NEXT;

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TFundInfo *fi = (TFundInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryBill.FundInfo, fi, sizeof(TFundInfo));
                }
            }

            for (int i = 0; i < lstAns->Count; i++)
            {
                TFundInfo *fi = (TFundInfo *)lstAns->Items[i];
                delete fi;
            }
            lstAns->Clear();
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}

int TTrdItf_JSD::QryStocks()    //��ѯ�ʺ������еĹɷ�
{
    AnsiString idxStock = "";
    AnsiString idxAcc   = "";
    AnsiString idxMart  = "";
    AnsiString cmd;
    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();
    //int count;

	char et;
	switch (FRequest.QryStocks.Bourse)
    {
        case bsSH : et = '1'; break;
        case bsSZ : et = '2'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    //    ----1-----|-------2------|----3---|---4----|---5--|----------------6---------------|
    //CMD ���ܺ�(10)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ѯ�г����루�ո��ʾ�����г���|
    //    --------------------------------7---------------------------------|
    //    ��ѯ֤ȯ���루Ϊ�ո�ʱ��ʾ��ѯ���й�Ʊ������ֻ��ѯĳһֻ��Ʊ�����|
    //    ---------------8----------------|-----9------|-----10-----|-----11-----|
    //    �ɶ����루�ո��ʾ���йɶ����룩|�����г�����|����֤ȯ����|�����ɶ��ʺ�|
    //    -----12-----|-----------13-----------|---14---|
    //    ��෵������|�������ܣ�1��ϸ��2���ܣ�|ί�з�ʽ|
    //    -----------------------------------------15------------------------------------------------|
    //    ���Ҵ��루v5.20.2ʵ�֣�����ѯ�г�����Ϊ�ն����Ҵ��벻Ϊ��ʱ�����ѯ�û��ҵ��г�{��A����A}��|
    //    -------------------16----------------------|-----------------17-------------------|
    //    �Ƿ񷵻غϼ�ֵ��1�����غϼ�ֵ�����������أ�|������ʼ���ڣ�Ϊ�գ������������Ϣ��|
    //
    //               1| 2| 3|| 5| 6|7| 8| 9|10|11|12| |14||16||
    cmd.cat_printf("10|%s|%c||%s|%c| |%s|%s|%s|%s|%d|1|%s||-1||",
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        et,                                        // 6
        et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 8
        idxMart.c_str(),                           // 9
        idxStock.c_str(),                          // 10
        idxAcc.c_str(),                            // 11
        1000,                                      // 12
        ENTRUST_WAY[FJSDSet.entrust_way]);         // 14

    try
    {
        //  1.�г�����  2.�ɶ��ʺ�   3.֤ȯ����        4.֤ȯ����  5.���(���ϵ��ճɽ�)
        //  6.�������  7.��ֵ(����) 8.����ӯ��(����)  9.�ɱ��۸� 10.�������¼�
        // 11.���տ������          12.��Ʊ��ֵ(����) 13.����ӯ��(���տ��)
        // 14.��������              15.һ�仰������Ϣ 16.��ծ���� 17.ÿ��ԪӦ����Ϣ(���ǹ�ծΪ0)
        if (SplitData(ReadFirstData(cmd), lstDD, 5) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 17) == DEF_ACK_OK)
                {
                    TStockInfo *si = new TStockInfo;
                    memset(si, 0, sizeof(TStockInfo));

                    if (et == '1')
                        si->SecuID[0] = 'H';
                    else
                        si->SecuID[0] = 'S';

                    strncpy(si->SecuID + 1, lstDD->Strings[INDEX(3)].c_str(), 7);
                    strncpy(si->SecuDesc,   lstDD->Strings[INDEX(2)].c_str(), 11);

                    si->Balance       = lstDD->Strings[INDEX(5)].ToIntDef(0);
                    si->Available     = lstDD->Strings[INDEX(6)].ToIntDef(0);
                    si->ProfitAndLoss = StrToFloatDef(lstDD->Strings[INDEX(8)], -1);
                    si->CostPrice     = StrToFloatDef(lstDD->Strings[INDEX(9)], -1);
                    si->Cost          = si->Balance * si->CostPrice;
                    si->CurPrice      = StrToFloatDef(lstDD->Strings[INDEX(10)], -1);
                    si->CurVal        = si->Balance * si->CurPrice;
                    lstAns->Add(si);
                    
                    idxMart  = lstDD->Strings[INDEX(1)];
                    idxAcc   = lstDD->Strings[INDEX(2)];
                    idxStock = lstDD->Strings[INDEX(3)];
                }
            }

            if (count > 0) goto _NEXT;

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
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
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
// CMD: ���ܺ�(3)|����Ӫҵ������|�г�����|��ʱ����|�ɶ��ʺ�|֤ȯ����|��������(1���롢2����)
//      |ί������|ί�м۸�|ί�з�ʽ|���б�־|���д���|
//---------------------------------------------------------------------------
int TTrdItf_JSD::Buy()
{
	char et;

	switch (FRequest.Buy.SecuID[0])
    {
        case 'H' : et = '1'; break;
        case 'S' : et = '2'; break;
        case 'P' : et = '1'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    if (FRequest.Buy.Type == 1)
    {
        // 1.���ܺ�(202)  2.Ӫҵ������  3.�г�����  4.��ʱ����  5.�ͻ���
        // 6.�ɶ�����     7.�깺/��ر�־��1���깺��2����أ�
        // 8.�������     9.�깺�ݶ�    10.ί�з�ʽ
        //                1| 2| 3|| 5| 6|7| 8| 9|10| 
        cmd.cat_printf("202|%s|%c||%s|%s|1|%s|%d|%s|",
            FJSDSet.branch_no,                          // 2
            et,                                         // 3
            FAccInfo.Capital,                           // 5
            et == '1' ? FAccInfo.SH : FAccInfo.SZ,      // 6
            FRequest.Buy.SecuID + 1,                    // 8
            FRequest.Buy.Num,                           // 9
            ENTRUST_WAY[FJSDSet.entrust_way]);          // 10
    }
    else
    {
        //      ----1----|------2-------|----3---|----4---|----5---|----6---|
        // CMD: ���ܺ�(3)|����Ӫҵ������|�г�����|��ʱ����|�ɶ��ʺ�|֤ȯ����|
        //
        //      ----------7-----------|----8---|----9---|---10---|---11---|---12---|
        //      ��������(1���롢2����)|ί������|ί�м۸�|ί�з�ʽ|���б�־|���д���|
        //
        //              1| 2| 3|| 5| 6|7| 8|   9|10|||
        cmd.cat_printf("3|%s|%c||%s|%s|1|%d|%.3f|%s|||",
            FJSDSet.branch_no,                         // 2
            et,                                        // 3
            et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 5
            FRequest.Buy.SecuID + 1,                   // 6
            FRequest.Buy.Num,                          // 8
            FRequest.Buy.Price,                        // 9
            ENTRUST_WAY[FJSDSet.entrust_way]);         // 10
    }

    TStringList *lstDD = new TStringList();
    try
    {
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
			NewAns(1);
            strncpy((*FAnswer)[0].Buy.ContractID, lstDD->Strings[INDEX(2)].c_str(), 19);
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }
    
    return 0;
}

int TTrdItf_JSD::Sell()
{
	char et;

	switch (FRequest.Sell.SecuID[0])
    {
        case 'H' : et = '1'; break;
        case 'S' : et = '2'; break;
        case 'P' : et = '1'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    if (FRequest.Buy.Type == 1)
    {
        // 1.���ܺ�(202)  2.Ӫҵ������  3.�г�����  4.��ʱ����  5.�ͻ���
        // 6.�ɶ�����     7.�깺/��ر�־��1���깺��2����أ�
        // 8.�������     9.�깺�ݶ�    10.ί�з�ʽ
        //                1| 2| 3|| 5| 6|7| 8| 9|10| 
        cmd.cat_printf("202|%s|%c||%s|%s|2|%s|%d|%s|",
            FJSDSet.branch_no,                          // 2
            et,                                         // 3
            FAccInfo.Capital,                           // 5
            et == '1' ? FAccInfo.SH : FAccInfo.SZ,      // 6
            FRequest.Buy.SecuID + 1,                    // 8
            FRequest.Buy.Num,                           // 9
            ENTRUST_WAY[FJSDSet.entrust_way]);          // 10
    }
    else
    {

        //      ----1----|------2-------|----3---|----4---|----5---|----6---|
        // CMD: ���ܺ�(3)|����Ӫҵ������|�г�����|��ʱ����|�ɶ��ʺ�|֤ȯ����|
        //
        //      ----------7-----------|----8---|----9---|---10---|---11---|---12---|
        //      ��������(1���롢2����)|ί������|ί�м۸�|ί�з�ʽ|���б�־|���д���|
        //
        //              1| 2| 3|| 5| 6|7| 8|   9|10|||
        cmd.cat_printf("3|%s|%c||%s|%s|2|%d|%.3f|%s|||",
            FJSDSet.branch_no,                        // 2
            et,                                       // 3
            et == '1' ? FAccInfo.SH : FAccInfo.SZ,    // 5
            FRequest.Sell.SecuID + 1,                 // 6
            FRequest.Sell.Num,                        // 8
            FRequest.Sell.Price,                      // 9
            ENTRUST_WAY[FJSDSet.entrust_way]);        // 10
    }

    TStringList *lstDD = new TStringList();
    try
    {
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
			NewAns(1);
            strncpy((*FAnswer)[0].Buy.ContractID, lstDD->Strings[INDEX(2)].c_str(), 19);
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }
    
    return 0;
}



int TTrdItf_JSD::Undo() //ί�г���
{

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    //
    //     ----1----|-------2------|----3---|----4---|---5--|---6--|----7---|
    //CMD: ���ܺ�(4)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ͬ��|ί�з�ʽ|
    //
    //              1| 2| 3|| 5| 6| 7|
    cmd.cat_printf("4|%s|%c||%s|%s|%s|",
        FJSDSet.branch_no,                          // 2
        FRequest.Undo.Bourse == bsSH ? '1' : '2',   // 3
        FAccInfo.Capital,                           // 5
        FRequest.Undo.ContractID,                   // 6
        ENTRUST_WAY[FJSDSet.entrust_way]);          // 7

    TStringList *lstDD = new TStringList();
    try
    {
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 1) != DEF_ACK_OK)
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }
    
    return 0;
}


