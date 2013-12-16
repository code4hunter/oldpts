//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdItf_JSDFF.h"
#include <assert.h>

#pragma package(smart_init)

#define REQUEST_NUM " "
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TTrdItf_JSDFF::TTrdItf_JSDFF(TJSDSet *set)
{
    CopyMemory(&FJSDSet,set,sizeof(TJSDSet));
    FJSDSet.JyCode[0]=' ';
    FJSDSet.JyCode[1]=0;

    FidTcp = new TIdTCPClient(NULL);
    FidIPWatch = new TIdIPWatch(NULL);
}
//---------------------------------------------------------------------------
TTrdItf_JSDFF::~TTrdItf_JSDFF()
{
    FidTcp->Disconnect();
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
AnsiString TTrdItf_JSDFF::GetErrorText(int code, char *error)
{
    strcpy(FLastError.Sender,"JSDFF");
    FLastError.ErrorCode = code;
    lstrcpyn( FLastError.Text,error,MAX_TEXT );
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
    //����ϴεķ�����Ϣ
    int n = FidTcp->ReadFromStack(true, 1, true);
    if (n > 0) FidTcp->ReadString(n);

    //ODS(cmd.c_str());
    FidTcp->Write(cmd);

    n = FidTcp->ReadFromStack(true, FJSDSet.TimeOut, true);
    if (n <= 0) return "A|192.168.0.1|100|N|�������ݳ�ʱ|-100"  ;

    AnsiString ret = FidTcp->ReadString(n);
    //ODS(ret.c_str());

    return ret;
}
//---------------------------------------------------------------------------
// count ��ʾ�����м���ֵ
int TTrdItf_JSDFF::SplitData(AnsiString SD, TStringList *lstDD, int count)
{
    assert(lstDD != NULL);

    lstDD->Clear();

    DeStr(SD.Trim(),lstDD,"|");

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
        if (lstDD->Count < 5)
            lstDD->Text = GetErrorText(-503, "δ֪���󣡣���");
        else if (lstDD->Count >= 5)
            lstDD->Text = GetErrorText(-503, lstDD->Strings[5].c_str());

        return DEF_ACK_ERROR;
    }

    if (lstDD->Count >= count)
        return DEF_ACK_OK;


    lstDD->Text = GetErrorText(-504, "δ֪���󣡣���");
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
            FidTcp->Connect();
        }
    }
    catch (Exception *e)
    {
        ODS(("���ӹ�̨ʧ��! ������Ϣ��" + e->Message).c_str() );
    }

    return FidTcp->Connected()==true ? 0 : -1;
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
        
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 4) == DEF_ACK_OK)
        {
            strncpy(FAccInfo.Capital, FRequest.SetAccount.Account, 20);
            strncpy(FAccInfo.PW, FRequest.SetAccount.PW, 13);

            if( FJSDSet.gw_ver == '6' )
            {
              AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
              cmd.cat_printf("%s|%c|",
              GetRequestHead("6040").c_str(),FJSDSet.jysID);

              if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 1) == DEF_ACK_OK)
              {
                int count = lstDD->Strings[4].ToIntDef(0);
                for (int i = 0; i < count; i++)
                {
                    if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 3) == DEF_ACK_OK)
                    {
                      if(lstrcmp(FRequest.SetAccount.Account,lstDD->Strings[INDEX(1)].c_str())==0 && FJSDSet.jysID==lstDD->Strings[INDEX(2)][1]){

                        NewAns(1);
                        memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));
                        strncpy(FJSDSet.JyCode, lstDD->Strings[INDEX(3)].c_str(), 20);
                        break;
                      }
                    }
                }

              }
              else
              {
                  ODS(lstDD->Strings[5].c_str());
                  return AnsiString(FRequest.SetAccount.Account).ToIntDef(DEF_OTHER_ERROR);
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
            ODS(lstDD->Strings[4].c_str());
            return -1;
        }

        
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}
//--------------------------------------------------------------------------
//////��ѯ����//////
//
//�����ѯ
//���ܺ� 6017|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|����������|��Լ����|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::GetTrdInfo()   //ȡ���̿�����
{
/*
    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%c|%s|",
        GetRequestHead("6017").c_str(),
        FJSDSet.jysID,                              //8
        FRequest.GetTrdInfo.SecuID + 1              //9        
    );

    TStringList *lstDD = new TStringList();
    try
    {
//    1.�ɹ���־  Y 2.���������� 3.����������  4.��Լ����    5.��Լ����  6.������ 7.����
//    8.�������  9.�������     10.���³ɽ��� 11.�ܳɽ���   12.�ɽ���� 13.�ǵ�(���¼ۣ�������)
//    14.�걨���� 15.�걨����    16.�걨������ 17.�걨������ 18.��ͣ��   19.��ͣ��
//    20.������

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 20) == DEF_ACK_OK)
        {
          NewAns(1);
          TQryQtn_Ans *qq = &(*FAnswer)[0].QryQtn;
          qq->QryQtnInfo.Open   = StrToFloatDef(lstDD->Strings[INDEX(7)], -1);
          qq->QryQtnInfo.Close  = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);
          qq->QryQtnInfo.High   = StrToFloatDef(lstDD->Strings[INDEX(8)], -1);
          qq->QryQtnInfo.Low    = StrToFloatDef(lstDD->Strings[INDEX(9)], -1);
          qq->QryQtnInfo.Last   = StrToFloatDef(lstDD->Strings[INDEX(10)], -1);
          qq->QryQtnInfo.Bid[0] = StrToFloatDef(lstDD->Strings[INDEX(14)], -1);
          qq->QryQtnInfo.BidV[0]= StrToFloatDef(lstDD->Strings[INDEX(16)], -1);
          qq->QryQtnInfo.Ask[0] = StrToFloatDef(lstDD->Strings[INDEX(15)], -1);
          qq->QryQtnInfo.AskV[0]= StrToFloatDef(lstDD->Strings[INDEX(17)], -1);
          qq->QryQtnInfo.Upper  = StrToFloatDef(lstDD->Strings[INDEX(18)], -1);
          qq->QryQtnInfo.Lower  = StrToFloatDef(lstDD->Strings[INDEX(19)], -1);
          qq->QryQtnInfo.Settle = StrToFloatDef(lstDD->Strings[INDEX(20)], -1);
          qq->QryQtnInfo.Volumn = StrToFloatDef(lstDD->Strings[INDEX(11)], -1);
        }
        else
        {
            ODS(lstDD->Strings[5].c_str());
            return lstDD->Strings[6].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }

*/
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
          (*FAnswer)[0].QryMoney.Balance = StrToFloatDef(lstDD->Strings[INDEX(22)] ,-1);     //�ܱ�֤��
          (*FAnswer)[0].QryMoney.Available = StrToFloatDef(lstDD->Strings[INDEX(10)],-1);    //�����ʽ�
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}
/*
//--------------------------------------------------------------------------
//��ѯ�����ʽ����,�ܱ�֤��
//���ܺ� 6012|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|����---YYYYMMDD|��7�� ����[�գ������]
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryMoneyFF()     //�ʽ��ѯ
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
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Last_jc     = StrToFloatDef(lstDD->Strings[INDEX(3)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.FreezeB     = StrToFloatDef(lstDD->Strings[INDEX(4)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.FreezeS     = StrToFloatDef(lstDD->Strings[INDEX(5)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MarginB     = StrToFloatDef(lstDD->Strings[INDEX(6)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MarginS     = StrToFloatDef(lstDD->Strings[INDEX(7)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Profit      = StrToFloatDef(lstDD->Strings[INDEX(8)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Loss        = StrToFloatDef(lstDD->Strings[INDEX(9)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Available   = StrToFloatDef(lstDD->Strings[INDEX(10)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.DymValue    = StrToFloatDef(lstDD->Strings[INDEX(11)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.DymVaR      = StrToFloatDef(lstDD->Strings[INDEX(12)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Payoff      = StrToFloatDef(lstDD->Strings[INDEX(15)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.ClosePayoff = StrToFloatDef(lstDD->Strings[INDEX(16)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MoneyOI     = StrToFloatDef(lstDD->Strings[INDEX(19)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MarginAll   = StrToFloatDef(lstDD->Strings[INDEX(22)] ,-1);   
        }
        else
        {
            ODS(lstDD->Strings[5].c_str());
            return lstDD->Strings[INDEX(10)].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}
*/
//--------------------------------------------------------------------------
//��ѯ������Լ�ֲ�
//���ܺ� 6014|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|����---YYYYMMDD|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryStock()     //�ɷݲ�ѯ
{
    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|",
        GetRequestHead("6014").c_str(),
        Now().FormatString("yyyymmdd").c_str());
    
    TStringList *lstDD = new TStringList();
    try
    {

//  v 1.1
//  1.����������  2.����������  3.��Լ����  4.Ͷ�����  5.��ֲ�  6.�����
//  7.���ֲ�      8.������      9.�򸡶�    10.������   11.���¼� 12.Ͷ������
//  13.����ӯ��   14.���ױ���   15.����ֲ� 16.�����ֲ�

//  v 1.5
/*
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
*/

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            if (count <= 0) return DEF_OTHER_ERROR;

            for (int i = 0; i < count; i++)
            {
              if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 16) == DEF_ACK_OK)
              {
                  if(lstrcmp(FRequest.QryStock.SecuID + 1,lstDD->Strings[INDEX(3)].c_str())==0){    //�����Ҫ��ѯ�ĺ�Լ

                    NewAns(1);
                    TQryStock_Ans *sa = &(*FAnswer)[0].QryStock;

                    sa->Balance    = StrToFloatDef(lstDD->Strings[INDEX(5)], 0);
                    sa->Available  = StrToFloatDef(lstDD->Strings[INDEX(7)], 0);
                    sa->BuyFreeze  = 0;
                    sa->SellFreeze = 0;
                  }
                  else continue;
              }
              else
              {
                  ODS(lstDD->Strings[4].c_str());
                  return -1;
              }
            }
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}
//--------------------------------------------------------------------------
//��ѯ���ɿ�������
//���ܺ� 6044
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryCanBuy()    //ȡ��������
{
    return -1;
}
//--------------------------------------------------------------------------
//��ѯί��״̬
//���ܺ� 6020|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|ί�е���
//��ѯ����ί��
//���ܺ� 6019|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|��ʼ����----YYYYMMDD|��������----YYYYMMDD
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryDetail()    //�ɽ���ѯ
{
  if( FJSDSet.qry_type == 6019 )
  {
    int reqry_num=0;
    AnsiString cmd;
    AnsiString date = Now().FormatString("yyyymmdd");
  HH:

    if(FRequest.QryDetail.ContractID[0]==0) return -1;

    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
        GetRequestHead("6019").c_str(),
        date.c_str(),
        date.c_str());

      TStringList *lstDD = new TStringList();
      try
      {
          //  1.�ɹ���־ Y  2.ί�е�״̬  3.�ɽ�����  4.δ�ɽ�����
        
          //*******************************
          //ί�е�״̬, wt_state, C1
          //*******************************
          //�����걨  Baodaning         n
          //�ѽ���(v6)                  s
          //�ѱ���    Already baodaned  a
          //���ֳɽ�  Partial completed p
          //ȫ���ɽ�  Completed         c
          //���ڳ���  Deleteing         f
          //ϵͳ����  System disable    m
          //�����ܾ�  User disable      q
          //�ѳ���    Total deleted     d
          //��������(v6)                g
          //��̨��������ί��(v6)        e
          //���ɲ���(v6)                b
          //δ֪״̬  Unknow            ����
          //------------------------------

  //    1.����������  2.����������  3.ί�е���  4.��Լ����  5.��Լ����  6.ί�е�״̬����
  //    7.ί�е�״̬���� [ȫ���ɽ�/���ֳɽ�/ȫ������/�Ѿ��걨/���ڴ���/δ�������]
  //    8.�������    9.�����������[����/����] 10.��ƽ�ֱ�־ 11.��ƽ������ [����/ƽ��/ƽ��]
  //    12.Ͷ�����   13.Ͷ������   14.ί������ 15.ί�м۸� 16.�ɽ����� 17.�ɽ��۸�
  //    18.δ�ɽ����� 19.ϵͳ���ĺ� 20.���ױ��� 21.ί������ [�ɽ����� + δ�ɽ����� + ��������]

          if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
          {
              int count = lstDD->Strings[4].ToIntDef(0);
              for (int i = 0; i < count; i++)
              {
                  if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                  {
                      if(lstrcmp(FRequest.QryDetail.ContractID,lstDD->Strings[INDEX(3)].c_str())==0)    //�����Ҫ��ѯ��ί�к�
                      {
                        NewAns(1);
                        (*FAnswer)[0].QryDetail.Num   = StrToIntDef(lstDD->Strings[INDEX(16)], -1);
                        (*FAnswer)[0].QryDetail.Price = StrToFloatDef(lstDD->Strings[INDEX(17)], -1);
                        (*FAnswer)[0].QryDetail.UndoNum = 0;
                        int csnnum = lstDD->Strings[INDEX(14)].ToIntDef(0);

                        String tmp = lstDD->Strings[INDEX(6)];
                        char ordstatus=' ';
                        if( tmp.Length()>0 )
                         ordstatus = tmp[1];
                        if (ordstatus == 'd' || ordstatus == 'b' ||
                            ordstatus == 'm' || ordstatus == 'q' ||
                            ordstatus == 'e')  //���ڳ���
                        {
                          if((ordstatus =='b') && (++reqry_num < 10)) //����ǲ������ٲ�ֱ�� reqry_num >3
                          {
                            delete lstDD;
                            Idglobal::Sleep(100);
                            goto HH;
                          }

                          (*FAnswer)[0].QryDetail.UndoNum = (*FAnswer)[0].QryDetail.Num - csnnum ;
                        }
                      }
                      else continue;
                  }
                  else
                  {
                      //ODS(lstDD->Strings[4].c_str());
                      ODS("QryDetail:%s",lstDD->Text.c_str());
                      return -1;
                  }
              }
          }
      }
      __finally
      {
          delete lstDD;
      }
    }
    else if (FJSDSet.qry_type == 6020 )
    {
      int reqry_num=0;
      AnsiString cmd;
      cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

      cmd.cat_printf("%s|%s|",
          GetRequestHead("6020").c_str(),
          FRequest.QryDetail.ContractID);
HH2:
      TStringList *lstDD = new TStringList();
      try
      {
          //  1.�ɹ���־ Y  2.ί�е�״̬  3.�ɽ�����  4.δ�ɽ�����

          //*******************************
          //ί�е�״̬, wt_state, C1
          //*******************************
          //�����걨  Baodaning         n
          //�ѽ���(v6)                  s
          //�ѱ���    Already baodaned  a
          //���ֳɽ�  Partial completed p
          //ȫ���ɽ�  Completed         c
          //���ڳ���  Deleteing         f
          //ϵͳ����  System disable    m
          //�����ܾ�  User disable      q
          //�ѳ���    Total deleted     d
          //��������(v6)                g
          //��̨��������ί��(v6)        e
          //���ɲ���(v6)                b
          //δ֪״̬  Unknow            ����
          //------------------------------

          if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
          {
            char ordstatus = lstDD->Strings[INDEX(2)][1];
            NewAns(1);
            (*FAnswer)[0].QryDetail.Num   = StrToIntDef(lstDD->Strings[INDEX(3)], -1);
            (*FAnswer)[0].QryDetail.Price = 0 ;
            if (ordstatus== 'd' || ordstatus == 'b' || ordstatus == 'm' ||
                ordstatus == 'q' || ordstatus == 'e' )
            {      //�ѳ��� ��  ���ɲ���
              if((ordstatus =='b') && (++reqry_num < 3)) //����ǲ������ٲ�ֱ�� reqry_num >3
              {
                delete lstDD;
                Idglobal::Sleep(100);
                goto HH2;
              }
              (*FAnswer)[0].QryDetail.UndoNum = (-1)*StrToIntDef(lstDD->Strings[INDEX(4)], -1);
            }
            else (*FAnswer)[0].QryDetail.UndoNum = 0;

            (*FAnswer)[0].QryDetail.status = ordstatus;
          }
          else
          {
            //ODS(lstDD->Strings[4].c_str());
            ODS("QryDetail:%s",lstDD->Text.c_str());
            return -1;
          }
      }
      __finally
      {
          delete lstDD;
      }
    }
    return 0;
}

int TTrdItf_JSDFF::QryHisDetail() //��ʷ�ɽ���ѯ
{
    // ��ʱ����
    return -1;
}

int TTrdItf_JSDFF::QryCsn()       //��ѯĳ��ί�к�ͬ
{
    // ��ʱ����
    return -1;
}
//--------------------------------------------------------------------------
//��ѯ����ί��
//���ܺ� 6019|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|��ʼ����----YYYYMMDD|��������----YYYYMMDD
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryCurCsn()    //����ί�в�ѯ
{
//    AnsiString idxDate = "";
//    AnsiString idxContractID = "";
//    AnsiString idxMartCode = "";
    
    AnsiString date = Now().FormatString("yyyymmdd");
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
        GetRequestHead("6019").c_str(),
        date.c_str(),
        date.c_str());


    try
    {
//    1.����������  2.����������  3.ί�е���  4.��Լ����  5.��Լ����  6.ί�е�״̬����
//    7.ί�е�״̬���� [ȫ���ɽ�/���ֳɽ�/ȫ������/�Ѿ��걨/���ڴ���/δ�������]
//    8.�������    9.�����������[����/����] 10.��ƽ�ֱ�־ 11.��ƽ������ [����/ƽ��/ƽ��]
//    12.Ͷ�����   13.Ͷ������   14.ί������ 15.ί�м۸� 16.�ɽ����� 17.�ɽ��۸�
//    18.δ�ɽ����� 19.ϵͳ���ĺ� 20.���ױ��� 21.ί������ [�ɽ����� + δ�ɽ����� + ��������]

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                {
                    TConsignInfo *ci = new TConsignInfo;
                    memset(ci, 0, sizeof(TConsignInfo));

                    strncpy(ci->ContractID,lstDD->Strings[INDEX(3)].c_str(), 6);
                    strncpy(ci->SecuID,    lstDD->Strings[INDEX(4)].c_str(), 8);
                    strncpy(ci->SecuDesc,  lstDD->Strings[INDEX(5)].c_str(), 8);
                    //strncpy(ci->Time,      lstDD->Strings[INDEX(12)].c_str(), 8);
                    //strncpy(ci->Date,      lstDD->Strings[INDEX(13)].c_str(), 8);

                    ci->Bourse = lstDD->Strings[INDEX(1)][1];

                    ci->Type   = ConvertType(lstDD->Strings[INDEX(8)].c_str());
                    ci->NoUse[0] = lstDD->Strings[INDEX(10)][1];
                    //ci->EoFlag = lstDD->Strings[INDEX(10)][1];
                    ci->State  = lstDD->Strings[INDEX(6)][1];
                    ci->CsnVol = StrToIntDef(lstDD->Strings[INDEX(14)], 0);
                    ci->TrdVol = StrToIntDef(lstDD->Strings[INDEX(16)], 0);
                    ci->CancelVol = 0;
                    ci->CsnPrice  = StrToFloatDef(lstDD->Strings[INDEX(15)], -1);;
                    ci->TrdPrice  = StrToFloatDef(lstDD->Strings[INDEX(17)], -1);;

//                    idxDate         = lstDD->Strings[INDEX(13)];
//                    idxContractID   = lstDD->Strings[INDEX(7)];
//                    idxMartCode     = lstDD->Strings[INDEX(16)];

                     if (lstDD->Strings[INDEX(7)] == "ȫ������")
                    {
                        int csnnum = lstDD->Strings[INDEX(14)].ToIntDef(0);
                        ci->CancelVol = ci->TrdVol - csnnum ;
                    }

                    lstAns->Add(ci);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return -1;
                }
            }
            
//            if (count > 0) goto _NEXT;

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
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}
//--------------------------------------------------------------------------
//��ѯ����ί��
//���ܺ� 6019|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|��ʼ����----YYYYMMDD|��������----YYYYMMDD
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryHisCsn()    //��ʷί�в�ѯ
{
//    AnsiString idxDate = "";
//    AnsiString idxContractID = "";
//    AnsiString idxMartCode = "";
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
        GetRequestHead("6019").c_str(),
        FRequest.QryHisCsn.StartDay,
        FRequest.QryHisCsn.EndDay);

    try
    {
//    1.����������  2.����������  3.ί�е���  4.��Լ����  5.��Լ����  6.ί�е�״̬����
//    7.ί�е�״̬���� [ȫ���ɽ�/���ֳɽ�/ȫ������/�Ѿ��걨/���ڴ���/δ�������]
//    8.�������    9.�����������[����/����] 10.��ƽ�ֱ�־ 11.��ƽ������ [����/ƽ��/ƽ��]
//    12.Ͷ�����   13.Ͷ������   14.ί������ 15.ί�м۸� 16.�ɽ����� 17.�ɽ��۸�
//    18.δ�ɽ����� 19.ϵͳ���ĺ� 20.���ױ��� 21.ί������ [�ɽ����� + δ�ɽ����� + ��������]

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                {
                    TConsignInfo *ci = new TConsignInfo;
                    memset(ci, 0, sizeof(TConsignInfo));

                    strncpy(ci->ContractID,lstDD->Strings[INDEX(3)].c_str(), 6);
                    strncpy(ci->SecuID,    lstDD->Strings[INDEX(4)].c_str(), 8);
                    strncpy(ci->SecuDesc,  lstDD->Strings[INDEX(5)].c_str(), 8);
                    //strncpy(ci->Time,      lstDD->Strings[INDEX(12)].c_str(), 8);
                    //strncpy(ci->Date,      lstDD->Strings[INDEX(13)].c_str(), 8);
                    strncpy(ci->Date,     Now().FormatString("yyyymmdd").c_str(), 8);
                    ci->Bourse = lstDD->Strings[INDEX(1)][1];

                    ci->Type   = ConvertType(lstDD->Strings[INDEX(8)].c_str());
                    //ci->EoFlag = lstDD->Strings[INDEX(10)][1];
                    ci->NoUse[0] =lstDD->Strings[INDEX(10)][1];
                    ci->State  = lstDD->Strings[INDEX(6)][1];
                    ci->CsnVol = StrToIntDef(lstDD->Strings[INDEX(14)], 0);
                    ci->TrdVol = StrToIntDef(lstDD->Strings[INDEX(16)], 0);
                    ci->CancelVol = 0;
                    ci->CsnPrice  = StrToFloatDef(lstDD->Strings[INDEX(15)], -1);;
                    ci->TrdPrice  = StrToFloatDef(lstDD->Strings[INDEX(17)], -1);;
          
//                    idxDate         = lstDD->Strings[INDEX(13)];
//                    idxContractID   = lstDD->Strings[INDEX(7)];
//                    idxMartCode     = lstDD->Strings[INDEX(16)];

                    lstAns->Add(ci);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return -1;
                }
            }
            
//            if (count > 0) goto _NEXT;

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
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}
//--------------------------------------------------------------------------
//��ѯ���ճɽ�
//���ܺ� 6013|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|��ʼ����----YYYYMMDD|��������----YYYYMMDD
//�������V6��������Ҫʹ��6053����ѯ��ʷ�ɽ���ϸ,6013ֻ������ѯ���ճɽ�
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryCurTrd()    //���ճɽ���ѯ
{
//    AnsiString idxStock  = "";
//    AnsiString idxTrdNo  = "";
//    AnsiString idxAccout = "";
//    AnsiString idxMartCode = "";
    AnsiString cmd;
    AnsiString date = Now().FormatString("yyyymmdd");

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();
    
_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
        GetRequestHead("6013").c_str(),
        date.c_str(),
        date.c_str());


    try
    {
//    1.����������  2.����������  3.ί�е���    4.��Լ����  5.��Լ����  6.�������
//    7.�����������[����/����]   8.��ƽ�ֱ�־  9.��ƽ������ [����/ƽ��/ƽ��]
//    10.Ͷ�����   11.Ͷ������   12.�ɽ�����   13.�ɽ��۸� 14.��������
//    15.���ױ���   16.ϵͳ��
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 16) == DEF_ACK_OK)
                {
                    TTradeInfo *ti = new TTradeInfo;
                    memset(ti, 0, sizeof(TTradeInfo));

                    strncpy(ti->SecuID,   lstDD->Strings[INDEX(4)].c_str(), 8);
                    strncpy(ti->SecuDesc, lstDD->Strings[INDEX(5)].c_str(), 8);
                    //strncpy(ti->Time,     lstDD->Strings[INDEX(7)].c_str(), 8);
                    strncpy(ti->Date,     Now().FormatString("yyyymmdd").c_str(), 8);
                    ti->Type  = ConvertType(lstDD->Strings[INDEX(6)].c_str());
                    //ti->EoFlag= lstDD->Strings[INDEX(8)][1];
                    ti->Vol   = StrToIntDef(lstDD->Strings[INDEX(12)], -1);
                    ti->Price = StrToFloatDef(lstDD->Strings[INDEX(13)], -1);
                    
                    lstAns->Add(ti);
                    
//                    idxStock    = lstDD->Strings[INDEX(3)];
//                    idxTrdNo    = lstDD->Strings[INDEX(8)];
//                    idxAccout   = lstDD->Strings[INDEX(1)];
//                    idxMartCode = lstDD->Strings[INDEX(10)];
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return -1;
                }
            }
            
//            if (count > 0) goto _NEXT;

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
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}
//--------------------------------------------------------------------------
//��ѯ��ʷ�ɽ�
//���ܺ� 6053|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|��ʼ����----YYYYMMDD|��������----YYYYMMDD
//�������V6��������Ҫʹ��6053����ѯ��ʷ�ɽ���ϸ,6013ֻ������ѯ���ճɽ�
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryHisTrd()    //��ʷ�ɽ���ѯ
{
//    AnsiString idxNo = "";
    AnsiString cmd;
    
    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
        GetRequestHead("6053").c_str(),
        FRequest.QryHisTrd.StartDay,
        FRequest.QryHisTrd.EndDay);


    try
    {
//    1.����������  2.����������  3.ί�е���    4.��Լ����  5.��Լ����  6.�������
//    7.�����������[����/����]   8.��ƽ�ֱ�־  9.��ƽ������[����/ƽ��/ƽ��]
//    10.Ͷ�����   11.Ͷ������   12.�ɽ�����   13.�ɽ��۸� 14.���ױ���
//    15.ϵͳ��     16.�ɽ���     17.����       18.������   19.���׷�

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[INDEX(2)].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 19) == DEF_ACK_OK)
                {
                    TTradeInfo *ti = new TTradeInfo;
                    memset(ti, 0, sizeof(TTradeInfo));

                    strncpy(ti->SecuID,   lstDD->Strings[INDEX( 4)].c_str(), 8);
                    strncpy(ti->SecuDesc, lstDD->Strings[INDEX( 5)].c_str(), 8);
                    //strncpy(ti->Time,     lstDD->Strings[INDEX(16)].c_str(), 8);
                    strncpy(ti->Date,     lstDD->Strings[INDEX(17)].c_str(), 8);
                    ti->Type  = ConvertType(lstDD->Strings[INDEX(6)].c_str());
                    //ti->EoFlag= lstDD->Strings[INDEX(8)][1];
                    ti->Vol   = StrToIntDef(lstDD->Strings[INDEX(12)], -1);
                    ti->Price = StrToFloatDef(lstDD->Strings[INDEX(13)], -1);

//                    idxNo = lstDD->Strings[INDEX(20)];
                    lstAns->Add(ti);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return -1;
                }
            }


//            if (count > 0) goto _NEXT;

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
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}
//--------------------------------------------------------------------------
//��ѯ�ʽ���ˮ
//���ܺ�XXX
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryBill()      //��ѯ�ʽ���ˮ�����ʵ���
{
    return -1;
}
//--------------------------------------------------------------------------
//��ѯ���гֲ�
//���ܺ� 6014|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|����---YYYYMMDD|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryStocks()    //��ѯ�ʺ������еĹɷ�
{
//    AnsiString idxStock = "";
//    AnsiString idxAcc   = "";
//    AnsiString idxMart  = "";

  //if (FRequest.QryStocks.Bourse !=  bsJJS ) return -1;

    AnsiString cmd;
    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();
    //int count;

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|",
        GetRequestHead("6014").c_str(),
        Now().FormatString("yyyymmdd").c_str());

    try
    {
//  1.����������  2.����������  3.��Լ����  4.Ͷ�����  5.��ֲ�  6.�����
//  7.���ֲ�      8.������      9.�򸡶�    10.������   11.���¼� 12.Ͷ������
//  13.����ӯ��   14.���ױ���   15.����ֲ� 16.�����ֲ�

        if (SplitData(ReadFirstData(cmd), lstDD, 5) == DEF_ACK_OK)
        {

            int count = lstDD->Strings[4].ToIntDef(0) - 2;  //���������¼Ϊ��С�ƺ���С�ƣ�����Ҫ��2
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 17) == DEF_ACK_OK)
                {
                    TStockInfo *si = new TStockInfo;
                    memset(si, 0, sizeof(TStockInfo));

                    si->SecuID[0] = 'F';

                    strncpy(si->SecuID + 1, lstDD->Strings[INDEX(3)].c_str(), 6);
                    strncpy(si->SecuDesc,   lstDD->Strings[INDEX(14)].c_str(),12);     //���뽻�ױ���

                    si->Balance       = lstDD->Strings[INDEX(5)].ToIntDef(0);          //��ֲ�
                    si->Available     = lstDD->Strings[INDEX(7)].ToIntDef(0);          //���ֲ�

                    si->ProfitAndLoss = StrToFloatDef(lstDD->Strings[INDEX(13)], 0);  //����ӯ��

                    si->CostPrice     = StrToFloatDef(lstDD->Strings[INDEX(6)], 0);   //�����
                    si->Cost          = si->Balance * si->CostPrice;
                    si->CurPrice      = StrToFloatDef(lstDD->Strings[INDEX(8)], 0);   //������
                    si->CurVal        = si->Available * si->CurPrice;

                    lstAns->Add(si);
                    
//                    idxMart  = lstDD->Strings[INDEX(1)];
//                    idxAcc   = lstDD->Strings[INDEX(2)];
//                    idxStock = lstDD->Strings[INDEX(3)];
                }
            }

//            if (count > 0) goto _NEXT;

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
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }
    
    return 0;
}

//--------------------------------------------------------------------------
//��ѯί��״̬
//���ܺ� 6020|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|ί�е���
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryTrdState(char *Cid)    //ί��״̬��ѯ
{
  //int reqry_num=0;
  AnsiString cmd;
HH:

  cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

  cmd.cat_printf("%s|%s|",
      GetRequestHead("6020").c_str(),
      Cid);

    TStringList *lstDD = new TStringList();
    try
    {
        //  1.�ɹ���־ Y  2.ί�е�״̬  3.�ɽ�����  4.δ�ɽ�����

        //*******************************
        //ί�е�״̬, wt_state, C1
        //*******************************
        //�����걨  Baodaning         n
        //�ѽ���(v6)                  s
        //�ѱ���    Already baodaned  a
        //���ֳɽ�  Partial completed p
        //ȫ���ɽ�  Completed         c
        //���ڳ���  Deleteing         f
        //ϵͳ����  System disable    m
        //�����ܾ�  User disable      q
        //�ѳ���    Total deleted     d
        //��������(v6)                g
        //��̨��������ί��(v6)        e
        //���ɲ���(v6)                b
        //δ֪״̬  Unknow            ����
        //------------------------------

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {

          if(lstDD->Strings[INDEX(2)] == "n" || lstDD->Strings[INDEX(2)] == "s") //����������걨���ٲ�ֱ�������ϵͳ�ܾ�
          {
            delete lstDD;
            Idglobal::Sleep(250);
            goto HH;
          }

          //ϵͳ�ܾ�
          if(lstDD->Strings[INDEX(2)] == "q" || lstDD->Strings[INDEX(2)] == "m")
          {
             return -1;
          }
        }
    }
    __finally
    {
        delete lstDD;
    }
    return 0;
}


//////���׺���/////
//---------------------------------------------------------------------------
//���ܺ� 6021|Ӫҵ������|ί�з�ʽ|�ͻ���|�ͻ�����|������----����|��Լ����|�������
//��ƽ�ֱ�־|Ͷ�����|ί������|ί�м۸�|���ױ���
//---------------------------------------------------------------------------
int TTrdItf_JSDFF::Buy()
{
    AnsiString cmd;
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%c|%s|%d|%d|%d|%d|%.3f|%s|",
        GetRequestHead("6021").c_str(),
        FJSDSet.jysID,                          //������
        FRequest.Buy.SecuID + 1,                //��Լ����
        0,                                      //�������
        FRequest.Buy.Type & 0x000F,            //��ƽ�ֱ�־
        FRequest.Buy.Type & 0x00F0,            //Ͷ�����
        FRequest.Buy.Num,                       //ί������
        FRequest.Buy.Price,                     //ί�м۸�
        FJSDSet.JyCode                                     //���ױ���
    );

    ODS("BUY,Code:%s,Price:%0.3f,Num:%d,Open:%d",
        FRequest.Buy.SecuID,FRequest.Buy.Price,FRequest.Buy.Num,FRequest.Buy.Type & 0x000F);

    TStringList *lstDD = new TStringList();
    try
    {
    //    1.�ɹ���־ Y  2.ί�е��� 3. ...... 8.ί�е�״̬����
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
			      NewAns(1);
            strncpy((*FAnswer)[0].Buy.ContractID, lstDD->Strings[INDEX(2)].c_str(), 6);
        }
        else
        {
            //ODS(lstDD->Strings[4].c_str());
            ODS("BUY:%s",lstDD->Text.c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
    }
    
    return 0;
}

int TTrdItf_JSDFF::Sell()
{
    AnsiString cmd;
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%c|%s|%d|%d|%d|%d|%.3f|%s|",
        GetRequestHead("6021").c_str(),
        FJSDSet.jysID,                          //������
        FRequest.Sell.SecuID + 1,               //��Լ����
        1,                                      //�������
        FRequest.Sell.Type & 0x000F,             //��ƽ�ֱ�־
        FRequest.Sell.Type & 0x00F0,             //Ͷ�����
        FRequest.Sell.Num,                      //ί������
        FRequest.Sell.Price,                    //ί�м۸�
        FJSDSet.JyCode                                      //���ױ���
    );
    ODS("SELL,Code:%s,Price:%0.3f,Num:%d,Open:%d",
        FRequest.Sell.SecuID,FRequest.Sell.Price,FRequest.Sell.Num,FRequest.Sell.Type & 0x000F);

    TStringList *lstDD = new TStringList();
    try
    {
    //    1.�ɹ���־ Y  2.ί�е��� 3......
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
			      NewAns(1);
            strncpy((*FAnswer)[0].Buy.ContractID, lstDD->Strings[INDEX(2)].c_str(), 6);
        }
        else
        {
            //ODS(lstDD->Strings[4].c_str());
            ODS("SELL:%s",lstDD->Text.c_str());
            return -1;
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
//---------------------------------------------------------------------------
int TTrdItf_JSDFF::Undo() //ί�г���
{
    AnsiString cmd;
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%c|||||||%s|||%s|",
        GetRequestHead("6022").c_str(),
        FJSDSet.jysID,                          //������
        FRequest.Undo.ContractID,               //��ͬ��
        FJSDSet.seatID                          //ϯλ�ţ�������
    );

    TStringList *lstDD = new TStringList();
    try
    {
    //  �ɹ���־ Y����ʾ�ѽ��ܳ�������|ί�е���
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) != DEF_ACK_OK)
        {
            //ODS(lstDD->Strings[4].c_str());
            ODS("UNDO:%s",lstDD->Text.c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

int TTrdItf_JSDFF::QryFutureCode()
{
  return 0;
}
