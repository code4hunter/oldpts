//---------------------------------------------------------------------------
//���֤ȯ
//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdItf_JSD_GD.h"
#include "UMkhUtils.h"
using namespace TMkhUtils;
#pragma package(smart_init)

const char * ENTRUST_WAY_GD[8]={"ZZWT","RJWT","DHWT","KSWT","WSWT","WZWT","BPWT"};

//---------------------------------------------------------------------------

TTrdItf_JSD_GD::TTrdItf_JSD_GD(TJSDSet *set)
{
  CopyMemory(&FJSDSet,set,sizeof(TJSDSet));

  _gateway = new JsdGateway;
  if (_gateway==NULL)
  {
    ODS("����������ʧ�ܣ�");
    return ;
  }
}

TTrdItf_JSD_GD::~TTrdItf_JSD_GD()
{
	_gateway->Disconnect();
	delete _gateway;
}

//
//AnsiString TTrdItf_JSD_GD::ReadNextData()
//{
//    AnsiString cmd;
//    cmd = stringprintf("R|%s|%s|0|%s|%s|", ClientIp.c_str(),
//        REQUEST_NUM_GD, FJSDSet.branch_no, ENTRUST_WAY_GD[FJSDSet.entrust_way]);
//    return ReadFirstData(cmd);
//}
//




int TTrdItf_JSD_GD::Init()  //��ʼ��
{


  try
  {
    //����
    ClientIp = string(FRequest.Init.CltIP)+",,"+string(FRequest.Init.CltMAC);
    _gateway->SetOP_SITE  ((char*)ClientIp.c_str());           //����վ��
    _gateway->SetOP_BRANCH(FJSDSet.branch_no);         //������֧


    if (_gateway->Connect(FJSDSet.SvrIp,FJSDSet.SvrPort)!=TRUE)
    {
      ODS(_gateway->getErrorMsg());
      setErrorMsg(_gateway->getErrorMsg());
      return -1;
    }


  }
  catch (...)
  {
      ODS("���ӹ�̨ʧ��!");
  }

  return 0;
}

//--------------------------------------------------------------------------
// CMD:���ܺ�(2)|����Ӫҵ������|�г�����|��ʱ����|�ʺ�|����|ί�з�ʽ|
// 

//--------------------------------------------------------------------------
int TTrdItf_JSD_GD::SetAccount() //�����ʺ�
{
  string cmd;

  ZeroMemory(&FAccInfo,sizeof(FAccInfo));

  try
  {
   //1.	�ɹ���־��Y  2.	����  3.	ԭ�����ʺŵ�ʵ���г�����  4.	ԭ����������ʺŴ���
   //5.	���Ҵ��루Ч����ʺŶ�Ӧ�Ļ��Ҵ��뷵�أ��ͻ��ŷ�������ң�����Ϊ1�� 6.	�ͻ���

    cmd = stringprintf("1|%s|0||%s|%s|%s|",
        FJSDSet.branch_no,
        FRequest.SetAccount.Account,
        ENTRUST_WAY_GD[FJSDSet.entrust_way], "");

    if (_gateway->WaitAnswer(cmd.c_str(),7)!=TRUE)
    {
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    FJSDSet.money_type = _gateway->GetFieldValue(0,5)[0];

    // 1. ���ܺ�(2)  2.����Ӫҵ������  3.�г�����  4.��ʱ����  5.�ʺ� 6.���� 7.ί�з�ʽ
    if(FRequest.SetAccount.Sort == asCA)
    {
        cmd = stringprintf("2|%s|0||%s|%s|%s|", FJSDSet.branch_no, FRequest.SetAccount.Account,
            FRequest.SetAccount.PW, ENTRUST_WAY_GD[FJSDSet.entrust_way]);
    }
    else if(FRequest.SetAccount.Sort==asSH)
    {
        cmd = stringprintf("2|%s|1||%s|%s|%s|", FJSDSet.branch_no, FRequest.SetAccount.Account,
            FRequest.SetAccount.PW, ENTRUST_WAY_GD[FJSDSet.entrust_way]);
    }
    else if(FRequest.SetAccount.Sort==asSZ)
    {
        cmd = stringprintf("2|%s|2||%s|%s|%s|", FJSDSet.branch_no, FRequest.SetAccount.Account,
            FRequest.SetAccount.PW, ENTRUST_WAY_GD[FJSDSet.entrust_way]);
    }
    else
        return -1;

    //  �װ���1.�ɹ���־  2.����     3.�ͻ���   4.�г�����
    //��̰���1.�г�����  2.�г����� 3.�ɶ����� 4.���ִ���  5.��������
    if (_gateway->WaitAnswer(cmd.c_str(),5,0,4)!=TRUE)
    {
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }
    strncpy(FAccInfo.Capital, _gateway->GetFieldValue(0,3).c_str(), 13);

    for ( int i =1; i<_gateway->GetRecCount(); i++ )
    {
      if (_gateway->GetFieldValue(i,1)[0] == '1')
        strncpy(FAccInfo.SH, _gateway->GetFieldValue(i,3).c_str(), 13);
      else if (_gateway->GetFieldValue(i,1)[0] == '2')
        strncpy(FAccInfo.SZ, _gateway->GetFieldValue(i,3).c_str(), 13);
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

    if(FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) {
      setErrorMsg("�޹ɶ��ʺ�");
      ODS("�޹ɶ��ʺ�");
      return -1;
    }

    NewAns(1);
    memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));


  }
  __finally
  {
  }

  return 0;
}

//////��ѯ����//////
// ��ʱ�����ѯ��v5.83����60
int TTrdItf_JSD_GD::QryQtn()   //ȡ���̿�����
{
	char et;

	switch (FRequest.QryQtn.Bourse)
  {
      case bsSHS : et = '1'; break;
      case bsSZS : et = '2'; break;
      default: return -1;
  }

  //      -----1----|------2-------|----3---|----4---|----5---|----6---|---7----|
  // CMD  ���ܺ�(60)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���  |֤ȯ����|ί�з�ʽ|
  //
  //               1| 2| 3|| 5| 6| 7|
  string cmd;
  cmd = stringprintf("60|%s|%c||%s|%s|%s|",
      FJSDSet.branch_no,                         // 2
      et,                                        // 3
      FAccInfo.Capital,                          // 5
      FRequest.QryQtn.SecuID,            // 6
      ENTRUST_WAY_GD[FJSDSet.entrust_way]);

  try
  {
        //  1.�ɹ���־    2.ָ��  3.֤ȯ����  4.֤ȯ����    5.���¼�  6.�ǵ�  7.�ǵ�ֵ
        //  8.����        9.���¼۳ɽ���     10.�ܳɽ���� 11.���� 12.�����̼�
        // 13.������߼� 14.������ͼ�       15.���1      16.����1  17.���2
        // 18.����2      19.���3            20.����3      21.����1  22.����1
        // 23.����2      24.����2            25.����3      26.����3  27.ͣ�Ʊ�־
        // 28.�ǵ�ֵ     29.���4            30.����4      31.����4  32.����4
        // 33.ÿ��ԪӦ����Ϣ��               34.��ծȫ��   35.֤ȯ��𣨴��࣫���

    if (_gateway->WaitAnswer(cmd.c_str(),35)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    NewAns(1);
    TQryQtn_Ans *gi = &(*FAnswer)[0].QryQtn;
    gi->QtnTick.Last   = toDouble( _gateway->GetFieldValue(0,5).c_str(), -1);
    gi->QtnTick.BuyPrice = toDouble( _gateway->GetFieldValue(0,15).c_str(), -1);
    gi->QtnTick.BuyVol = toInt( _gateway->GetFieldValue(0,16).c_str(), -1);
    gi->QtnTick.SellPrice = toDouble( _gateway->GetFieldValue(0,21).c_str(), -1);
    gi->QtnTick.SellVol = toInt( _gateway->GetFieldValue(0,22).c_str(), -1);

  }
  __finally
  {
  }

  return 0;

}

//��ѯ�ʽ����Ϳ����ʽ���9
int TTrdItf_JSD_GD::QryMoney()     //�ʽ��ѯ
{

  string cmd;
  cmd = stringprintf("9|%s|%c||%s|",
        FJSDSet.branch_no,                         // 2
        FJSDSet.money_type,                        // 3
        FAccInfo.Capital);                         // 5

  try
  {
        // 1.�ɹ���־  2.�ʽ����  3.�����ʽ�  4.����δ���ս��  5.����δ���ս��
        // 6.ί��δ�ɽ�������    7.��������  8.�쳣�����ʽ�

    if (_gateway->WaitAnswer(cmd.c_str(),8)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    NewAns(1);
    (*FAnswer)[0].QryMoney.MoneyInfo.Balance = toDouble(_gateway->GetFieldValue(0,2).c_str() ,-1);
    (*FAnswer)[0].QryMoney.MoneyInfo.Available = toDouble(_gateway->GetFieldValue(0,3).c_str(),-1);

  }
  __finally
  {
  }

  return 0;
}




int TTrdItf_JSD_GD::QryDetail()    //�ɽ���ѯ
{
  int reqry_num=0;

HH:

  if(FRequest.QryOrder.OrderID[0]==0) return -1;
	char et;
	switch (FRequest.QryOrder.Bourse)
  {
      case bsSHS : et = '1'; break;
      case bsSZS : et = '2'; break;
      default: return -1;
  }

  string cmd;

  //      -----1----|------2-------|----3---|----4---|--5---|---6----|
  //      ���ܺ�(14)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ʼ����|
  //      -----7----|---------------8--------------|------------------9---------------|
  //      ��ֹ����  |��ͬ��(Ϊ�ո�ʱ��ѯ��������)  |֤ȯ����(Ϊ�ո�ʱ��ѯ���й�Ʊ����)|
  //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
  //      ��෵������|��������|������ͬ��|ί�з�ʽ|�����г�����|����ʽ(0-�г����롢1-ί��ʱ�䡢2-ί��ʱ�䵹��)|
  //


  //               1| 2| 3|| 5| 6| 7| 8|9| |||13|| |
  cmd = stringprintf("14|%s|%c||%s|%s|%s|%s| |1|||%s||0|",
      FJSDSet.branch_no,                         // 2
      et,                                        // 3
      FAccInfo.Capital,                          // 5
      TDateTimex::nowDateString().c_str(),    // 6
      TDateTimex::nowDateString().c_str(),    // 7
      FRequest.QryOrder.OrderID,             // 8
      ENTRUST_WAY_GD[FJSDSet.entrust_way]           // 13
  );

  try
  { //                                 3           5                  9       11                        15
    //A|10.0.38.11|100|B881136426|��|510050|50ETF|100|2.200|64433|0|0.000|0|δ�ɽ�|13:36:02  |20090818| |W|1|1| |��| |0| |0.00|
    //A|10.0.38.11|100|B881136426|��|510050|50ETF|100|2.200|64433|0|0.000|0|���ڳ���|13:36:02|20090818| |2|1|1| |��| |0| |0.00|

    //�װ���
    //1.	�ɹ���־��Y  2.	��¼������������������
    //��������
    //1.	�ɶ��ʺ�    2.	����������ƣ�V6��3.	֤ȯ����4.	֤ȯ����5.	ί������6.	ί�м۸�
    //7.	��ͬ��  8.	�ɽ�����9.	�ɽ��۸�10.	ί��״̬11.	�ɽ�״̬12.	ί��ʱ��13.	����14.	������Ϣ
    //15.	�ɹ���־  16.	�г�����17.	��������־���¹�̨��18.	�ɽ�״̬��־���¹�̨��19.	����������ƣ��¹�̨��
    //20.	������루�¹�̨��21.	����������V7.00��22.	ί������(������������,���������ȵ�,�������)

    if (_gateway->WaitAnswer(cmd.c_str(),20,0)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    int count = toInt(_gateway->GetFieldValue(0,2).c_str() ,0);
    if (count <= 0) return -1;

    NewAns(1);
    (*FAnswer)[0].QryOrder.OrderInfo.MatchQty   = toInt(_gateway->GetFieldValue(1,8).c_str(), 0);
    (*FAnswer)[0].QryOrder.OrderInfo.MatchPrice = toDouble(_gateway->GetFieldValue(1,9).c_str(), -1);
    (*FAnswer)[0].QryOrder.OrderInfo.CancelQty = 0;

    //�ɽ���־
    //0�ѳɽ�    1���ֳɽ�  2���ڳ���  3���ֳ���   4���⳷��   5��Ʊ����  C��������  D�����ѷ�
    //Wδ�ɽ�    9 ����ʧ��   A ���ֳɽ�ʧ��    E �����ѷ����ֳɽ�

    char ts =  _gateway->GetFieldValue(1,15)[0];
    if(ts=='2' || ts=='4' || (ts=='3' && ((*FAnswer)[0].QryOrder.OrderInfo.MatchQty > 0)))
    {
      if(ts == '3' && ++reqry_num < 3 ) //����ǲ������ٲ�ֱ�� reqry_num >3
      {
        Sleep(100);
        goto HH;
      }

      int csnnum = toInt(_gateway->GetFieldValue(1,5).c_str(), 0);
      (*FAnswer)[0].QryOrder.OrderInfo.CancelQty = (*FAnswer)[0].QryOrder.OrderInfo.MatchQty - csnnum ;
    }

  }
  __finally
  {
  }
  return 0;
}


int TTrdItf_JSD_GD::QryCurCsn()    //����ί�в�ѯ
{
  string cmd;

  //      -----1----|------2-------|----3---|----4---|--5---|---6----|
  //      ���ܺ�(14)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ʼ����|
  //      -----7----|---------------8--------------|------------------9---------------|
  //      ��ֹ����  |��ͬ��(Ϊ�ո�ʱ��ѯ��������)  |֤ȯ����(Ϊ�ո�ʱ��ѯ���й�Ʊ����)|
  //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
  //      ��෵������|��������|������ͬ��|ί�з�ʽ|�����г�����|����ʽ(0-�г����롢1-ί��ʱ�䡢2-ί��ʱ�䵹��)|
  //
  //               1| 2| 3|| 5| 6| 7|8|9|10|11|12|13|14| |
  cmd =stringprintf("14|%s|%c||%s|%s|%s| | |%d|%s|%s|%s|%s|0|",
      FJSDSet.branch_no,                          // 2
      ' ',                                        // 3
      FAccInfo.Capital,                           // 5
      TDateTimex::nowDateString().c_str(),                               // 6
      TDateTimex::nowDateString().c_str(),                               // 7
      100,                                       // 10
      "",                            // 11
      "",                      // 12
      ENTRUST_WAY_GD[FJSDSet.entrust_way],           // 13
      ""                         // 14
  );

  try
  {
        // 1.�ɶ��ʺ� 2.�������  3.֤ȯ����  4.֤ȯ����  5.ί������  6.ί�м۸�
        // 7.��ͬ��   8.�ɽ�����  9.�ɽ��۸� 10.ί��״̬ 11.�ɽ�״̬ 12.�ɽ�ʱ��
        //13.����    14.������Ϣ 15.�ɹ���־ 16.�г�����

    if (_gateway->WaitAnswer(cmd.c_str(),16,0)!=TRUE)
    {
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    int count = toInt(_gateway->GetFieldValue(0,2).c_str() ,0);
    if (count < 0) return -1;

    NewAns(_gateway->GetRecCount()-1);

    for ( int i =1; i<_gateway->GetRecCount(); i++ )
    {
      TOrderInfo *ci = &(*FAnswer)[i-1].QryOrder.OrderInfo;
      memset(ci, 0, sizeof(TOrderInfo));

      strncpy(ci->OrderID,_gateway->GetFieldValue(i,7).c_str(), 8);
      strncpy(ci->SecuID,    _gateway->GetFieldValue(i,3).c_str(), 7);
      strncpy(ci->SecuDesc,  _gateway->GetFieldValue(i,4).c_str(), 8);
      ci->Time = toInt(_gateway->GetFieldValue(i,12).c_str(), 0);
      ci->Date = toInt(_gateway->GetFieldValue(i,13).c_str(), 0);

      //ci->Bourse = _gateway->GetFieldValue(i,16)[0] - 1;

      ci->BorS =ConvertBorS((char*)_gateway->GetFieldValue(i,2).c_str());

      ci->OrderStatus  = 'N';
      ci->OrderQty = toInt(_gateway->GetFieldValue(i,5).c_str(), -1);
      ci->MatchQty = toInt(_gateway->GetFieldValue(i,8).c_str(), -1);
      ci->CancelQty = 0;
      ci->OrderPrice  = toDouble(_gateway->GetFieldValue(i,6).c_str(), -1);
      ci->MatchPrice  = toDouble(_gateway->GetFieldValue(i,9).c_str(), -1);

      char ts =  _gateway->GetFieldValue(i,15)[0];
      if(ts=='2' || ts=='4' || (ts=='3' && (*FAnswer)[0].QryOrder.OrderInfo.MatchQty > 0))
      {
        int csnnum = toInt(_gateway->GetFieldValue(i,5).c_str(), 0);
        ci->CancelQty = ci->MatchQty - csnnum ;
      }
      ci->Bourse = ConvertBourse(_gateway->GetFieldValue(i,16).c_str());

    }
  }
  __finally
  {
  }

  return 0;
}

int TTrdItf_JSD_GD::QryHisCsn()    //��ʷί�в�ѯ
{
  string cmd;

  //      -----1----|------2-------|----3---|----4---|--5---|---6----|
  //      ���ܺ�(14)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ʼ����|
  //      -----7----|---------------8--------------|------------------9---------------|
  //      ��ֹ����  |��ͬ��(Ϊ�ո�ʱ��ѯ��������)  |֤ȯ����(Ϊ�ո�ʱ��ѯ���й�Ʊ����)|
  //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
  //      ��෵������|��������|������ͬ��|ί�з�ʽ|�����г�����|����ʽ(0-�г����롢1-ί��ʱ�䡢2-ί��ʱ�䵹��)|
  //
  //               1| 2| 3|| 5| 6| 7|8|9|10|11|12|13|14| |
  cmd = stringprintf("14|%s|%c||%s|%d|%d| | |%d|%s|%s|%s|%s|0|",
      FJSDSet.branch_no,                          // 2
      ' ',                                        // 3
      FAccInfo.Capital,                           // 5
      FRequest.QryOrder.StartDate,                // 6
      FRequest.QryOrder.EndDate,                  // 7
      1000,                                       // 10
      "",                            // 11
      "",                      // 12
      ENTRUST_WAY_GD[FJSDSet.entrust_way],           // 13
      ""                         // 14
  );

  try
  {
        // 1.�ɶ��ʺ� 2.�������  3.֤ȯ����  4.֤ȯ����  5.ί������  6.ί�м۸�
        // 7.��ͬ��   8.�ɽ�����  9.�ɽ��۸� 10.ί��״̬ 11.�ɽ�״̬ 12.�ɽ�ʱ��
        //13.����    14.������Ϣ 15.�ɹ���־ 16.�г�����

    if (_gateway->WaitAnswer(cmd.c_str(),16,0)!=TRUE)
    {
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    int count = toInt(_gateway->GetFieldValue(0,2).c_str() ,0);
    if (count < 0) return -1;

    NewAns(_gateway->GetRecCount()-1);

    for ( int i =1; i<_gateway->GetRecCount(); i++ )
    {
      TOrderInfo *ci = &(*FAnswer)[i-1].QryOrder.OrderInfo;
      memset(ci, 0, sizeof(TOrderInfo));

      strncpy(ci->OrderID,_gateway->GetFieldValue(i,7).c_str(), 8);
      strncpy(ci->SecuID,    _gateway->GetFieldValue(i,3).c_str(), 7);
      strncpy(ci->SecuDesc,  _gateway->GetFieldValue(i,4).c_str(), 8);
      ci->Time = toInt(_gateway->GetFieldValue(i,12).c_str(), 0);
      ci->Date = toInt(_gateway->GetFieldValue(i,13).c_str(), 0);

      //ci->Bourse = _gateway->GetFieldValue(i,16)[0] - 1;

      ci->BorS =ConvertBorS((char*)_gateway->GetFieldValue(i,2).c_str());

      ci->OrderStatus  = 'N';
      ci->OrderQty = toInt(_gateway->GetFieldValue(i,5).c_str(), -1);
      ci->MatchQty = toInt(_gateway->GetFieldValue(i,8).c_str(), -1);
      ci->CancelQty = 0;
      ci->OrderPrice  = toDouble(_gateway->GetFieldValue(i,6).c_str(), -1);
      ci->MatchPrice  = toDouble(_gateway->GetFieldValue(i,9).c_str(), -1);

      char ts =  _gateway->GetFieldValue(i,15)[0];
      if(ts=='2' || ts=='4' || (ts=='3' && (*FAnswer)[0].QryOrder.OrderInfo.MatchQty > 0))
      {
        int csnnum = toInt(_gateway->GetFieldValue(i,5).c_str(), 0);
        ci->CancelQty = ci->MatchQty - csnnum ;
      }

      ci->Bourse = ConvertBourse(_gateway->GetFieldValue(i,16).c_str());
    }

  }
  __finally
  {
  }

  return 0;
}

int TTrdItf_JSD_GD::QryCurTrd()    //���ճɽ���ѯ
{
  string cmd;

    //  1.���ܺ�(13)   2.����Ӫҵ������  3.�г�����     4.��ʱ����      5.�ͻ���
    //  6.��෵������ 7.����֤ȯ����    8.�����ɶ��ʺ� 9.�����ɽ���� 10.ί�з�ʽ
    // 11.�����г����루v5.83�����г�����=0��ѯ����ʱ�������룩
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|
  cmd = stringprintf("13|%s|%c||%s|%d|%s|%s|%s|%s|%s|",
      FJSDSet.branch_no,                          // 2
      ' ',                                        // 3
      FAccInfo.Capital,                           // 5
      100,                                       // 6
      "",                           // 7
      "",                          // 8
      "",                           // 9
      ENTRUST_WAY_GD[FJSDSet.entrust_way],           // 10
      ""                         // 11
  );

  try
  {
      //
      // 1.�ɶ��ʺ� 2.�������  3.֤ȯ����  4.֤ȯ����  5.�ɽ�����  6.�ɽ��۸�
      // 7.�ɽ�ʱ�� 8.�ɽ����  9.��ͬ���� 10.�г����루9-10Ϊv5.83ʵ�֣�
      //
    if (_gateway->WaitAnswer(cmd.c_str(),10,false)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    int count = toInt(_gateway->GetFieldValue(0,2).c_str() ,0);
    if (count < 0) return -1;

    NewAns(_gateway->GetRecCount()-1);

    for (int i = 1; i < _gateway->GetRecCount(); i++)
    {
      TTradeInfo *ti = &(*FAnswer)[i-1].QryTrd.TrdInfo;
      memset(ti, 0, sizeof(TTradeInfo));

      strncpy(ti->SecuID,   _gateway->GetFieldValue(i,3).c_str(), 7);
      strncpy(ti->SecuDesc, _gateway->GetFieldValue(i,4).c_str(), 8);
      ti->Time=     toInt(_gateway->GetFieldValue(i,7).c_str(), 0);
      ti->Date=     TDateTimex::nowDateInt();
      ti->BorS  = ConvertBorS((char*)_gateway->GetFieldValue(i,2).c_str());
      ti->MatchQty   = toInt(_gateway->GetFieldValue(i,5).c_str(), -1);
      ti->MatchPrice = toDouble(_gateway->GetFieldValue(i,6).c_str(), -1);
      ti->Bourse = ConvertBourse(_gateway->GetFieldValue(i,10).c_str());

    }

  }
  __finally
  {
  }

  return 0;
}

int TTrdItf_JSD_GD::QryHisTrd()    //��ʷ�ɽ���ѯ
{
  string cmd;


  //  1.���ܺ�(62)  2.����Ӫҵ������  3.���Ҵ���   4.��ʱ����      5.�ͻ���
  //  6.��ʼ����    7.��ֹ����        8.������ˮ�� 9.��෵������ 10.ί�з�ʽ
  //
  //               1| 2| 3|| 5| 6| 7| 8| 9|10|
  cmd = stringprintf("62|%s|%c||%s|%d|%d|%s|%d|%s|",
      FJSDSet.branch_no,                          // 2
      FJSDSet.money_type,                         // 3
      FAccInfo.Capital,                           // 5
      FRequest.QryTrd.StartDate,                // 6
      FRequest.QryTrd.EndDate,                  // 7
      "",                              // 8
      1000,                                       // 9
      ENTRUST_WAY_GD[FJSDSet.entrust_way]            // 10
  );

  try
  {

        // 1.�ɽ�����  2.�ɶ�����  3.������־  4.֤ȯ����  5.֤ȯ����  6.�ɽ�����
        // 7.�ɽ��۸�  8.�ɽ����  9.�䶯��� 10.�ʽ���� 11.��Ʊ��� 12.Ӷ��
        //13.ӡ��˰   14.������   15.�������� 16.�ɽ�ʱ�� 17.��ͬ��� 18.�ɽ����
        //19."1"��"2"��           20.��ˮ��(=8λ����+6λ���)         21.�ɽ�����abs

    if (_gateway->WaitAnswer(cmd.c_str(),21,false)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    //int count = toInt(_gateway->GetFieldValue(0,2).c_str(),0);

    NewAns(_gateway->GetRecCount()-1);

    for (int i = 1; i < _gateway->GetRecCount(); i++)
    {
      TTradeInfo *ti = &(*FAnswer)[i-1].QryTrd.TrdInfo;
      memset(ti, 0, sizeof(TTradeInfo));

      strncpy(ti->SecuID,   _gateway->GetFieldValue(i,4).c_str(), 7);
      strncpy(ti->SecuDesc, _gateway->GetFieldValue(i,5).c_str(), 8);
      ti->Time=     toInt(_gateway->GetFieldValue(i,16).c_str(), 0);
      ti->Date=     toInt(_gateway->GetFieldValue(i,1).c_str(), 0);
      ti->BorS  = ConvertBorS((char*)_gateway->GetFieldValue(i,19).c_str());
      ti->MatchQty   = toInt(_gateway->GetFieldValue(i,6).c_str(), -1);
      ti->MatchPrice = toDouble(_gateway->GetFieldValue(i,7).c_str(), -1);

    }
  }
  __finally
  {
  }

  return 0;
}

int TTrdItf_JSD_GD::QryBill()      //��ѯ�ʽ���ˮ�����ʵ���
{
  string cmd;

  //
  //  1.���ܺ�(11)  2.����Ӫҵ������  3.�г�����  4.��ʱ����     5.�ͻ���
  //  6.���ִ���    7.��ʼ����        8.��ֹ����  9.������ˮ��  10.��෵������
  // 11.ί�з�ʽ
  //
  //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|
  cmd = stringprintf("11|%s|%c||%s|%c|%d|%d|%s|%d|%s|",
      FJSDSet.branch_no,                          // 2
      ' ',                                        // 3
      FAccInfo.Capital,                           // 5
      FJSDSet.money_type,                         // 6
      FRequest.QryBill.StartDate,                  // 7
      FRequest.QryBill.EndDate,                    // 8
      "",                              // 9
      100,                                       // 10
      ENTRUST_WAY_GD[FJSDSet.entrust_way]            // 11
  );

  try
  {
      // 1.ժҪ   2.�䶯���  3.�������  4.�ɶ��ʺ�  5.֤ȯ����  6.�������
      // 7.�ɽ��� 8.�ɽ���    9.�ɽ���� 10.��ˮ��   11.ժҪ��� 12.��ͬ���루v5.81.2��

    if (_gateway->WaitAnswer(cmd.c_str(),12,false)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    //int count = toInt(_gateway->GetFieldValue(0,2).c_str(),0);

    NewAns(_gateway->GetRecCount()-1);

    for (int i = 1; i < _gateway->GetRecCount(); i++)
    {
      TFundInfo *ti = &(*FAnswer)[i-1].QryBill.FundInfo;
      memset(ti, 0, sizeof(TFundInfo));

      strncpy(ti->SecuID,   _gateway->GetFieldValue(i,5).c_str(), 7);
//      strncpy(ti->SecuDesc, _gateway->GetFieldValue(i,5).c_str(), 8);
//      ti->Time=     toInt(_gateway->GetFieldValue(i,16).c_str(), 0);
//      ti->Date=     toInt(_gateway->GetFieldValue(i,1).c_str(), 0);
      ti->BorS  = ConvertBorS((char*)_gateway->GetFieldValue(i,6).c_str());
      ti->MatchQty   = toInt(_gateway->GetFieldValue(i,7).c_str(), -1);
      ti->MatchPrice = toDouble(_gateway->GetFieldValue(i,8).c_str(), -1);
      ti->FundEffect = toDouble(_gateway->GetFieldValue(i,2).c_str(), -1);
      ti->FundBal    = toDouble(_gateway->GetFieldValue(i,3).c_str(), -1);

      ti->Bourse = FRequest.QryStocks.Bourse;

    }
  }
  __finally
  {
  }

  return 0;
}


int TTrdItf_JSD_GD::QryStocks()    //��ѯ�ʺ������еĹɷ�
{
  if(FRequest.QryStocks.QryType==2 && FRequest.QryStocks.EtfUnit>0)
    return QryETFs();
  else if(FRequest.QryStocks.QryType==1) {

    char et;
    switch (FRequest.QryStocks.Bourse)
    {
      case bsSHS : et = '1'; break;
      case bsSZS : et = '2'; break;
      case bsXXX : et = '1'; break;
      default: return -1;
    }

    string cmd;
    //CMD 1.���ܺ�(56) 2.����Ӫҵ������ 3.�г����� 4.��ʱ���� 5.�ͻ��� 6.��ѯ�г����루�ո��ʾ�����г���|
    //    7.��ѯ֤ȯ���루Ϊ�ո�ʱ��ʾ��ѯ���й�Ʊ������ֻ��ѯĳһֻ��Ʊ�����|
    //    8.�ɶ����루�ո��ʾ���йɶ����룩9.�����г����� 10.����֤ȯ���� 11.�����ɶ��ʺ�
    //    12.��෵������ 13.�������ܣ�1��ϸ��2���ܣ�14.ί�з�ʽ
    //    15.���Ҵ��루v5.20.2ʵ�֣�����ѯ�г�����Ϊ�ն����Ҵ��벻Ϊ��ʱ�����ѯ�û��ҵ��г�{��A����A}��|
    //    16.�Ƿ񷵻غϼ�ֵ��1�����غϼ�ֵ�����������أ�17.������ʼ���ڣ�Ϊ�գ������������Ϣ��|
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|12| |14|15|16||
    cmd = stringprintf("56|%s|%c||%s|%c|%s|%s|%s|%s|%s|%d|1|%s|%c|-1||",
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        et,                                        // 6
        FRequest.QryStocks.SecuID,              // 7
        et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 8
        "",                                        // 9
        "",                                        // 10
        "",                                        // 11
        1,                                         // 12
        ENTRUST_WAY_GD[FJSDSet.entrust_way],          // 14
        FJSDSet.money_type);                       // 15

    try
    {
      //  1.�г�����  2.�ɶ��ʺ�   3.֤ȯ���� 4.֤ȯ����  5.���(���ϵ��ճɽ�)
      //  6.�������  7.��������ɽ�����      8.��������δ�ɽ�����  9.��������ɽ����
      // 10.�ɱ��۸� 11.���¼�    12.��ֵ    13.����ӯ�� 14.���������ɽ����
      // 15.�������� 16.һ�仰������Ϣ       17.��ծ���� 18.ÿ��ԪӦ����Ϣ(���ǹ�ծΪ0)

      if (_gateway->WaitAnswer(cmd.c_str(),18,false)!=TRUE)
      {
        setErrorMsg(_gateway->getErrorMsg());
        ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
        ODS("�����: [%s]",_gateway->GetRequestBuffer());

        return -1;
      }

      int count = toInt(_gateway->GetFieldValue(0,2).c_str(),0);
      if (count <= 0) return -1;

      NewAns(1);

      TStockInfo *ti = &(*FAnswer)[0].QryStocks.StockInfo;
      memset(ti, 0, sizeof(TStockInfo));

      ti->BalQty    = toInt(_gateway->GetFieldValue(1,5).c_str(), -1);
      ti->AvlQty    = toDouble(_gateway->GetFieldValue(1,6).c_str(), -1);
    }
    __finally
    {
    }

    return 0;

  }


  string idxStock = "";
  string idxAcc   = "";
  string idxMart  = "";
  string cmd;

	char et;
	switch (FRequest.QryStocks.Bourse)
    {
        case bsSHS : et = '1'; break;
        case bsSZS : et = '2'; break;
        default: return -1;
    }

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
    //                 1| 2| 3|| 5| 6|7| 8| 9|10|11|12| |14||16||
  cmd = stringprintf("10|%s|%c||%s|%c| |%s|%s|%s|%s|%d|1|%s||||",       //������ĵ�˵16�������
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        et,                                        // 6
        et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 8
        idxMart.c_str(),                           // 9
        idxStock.c_str(),                          // 10
        idxAcc.c_str(),                            // 11
        1000,                                      // 12
        ENTRUST_WAY_GD[FJSDSet.entrust_way]);         // 14

    try
    {

      //[3]A|10.0.38.11|100|2|0800044619|002282|�����|500|500|5750.000|0.000|11.500|11.500|500|5750.000|0.000| | |11.500|0.000|11.500| 
      //  1.�г�����  2.�ɶ��ʺ�   3.֤ȯ����        4.֤ȯ����  5.���(���ϵ��ճɽ�)
      //  6.�������  7.��ֵ(����) 8.����ӯ��(����)  9.�ɱ��۸� 10.�������¼�
      // 11.���տ������          12.��Ʊ��ֵ(����) 13.����ӯ��(���տ��)
      // 14.��������              15.һ�仰������Ϣ 16.��ծ���� 17.ÿ��ԪӦ����Ϣ(���ǹ�ծΪ0)

    if (_gateway->WaitAnswer(cmd.c_str(),17,false)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    //int count = toInt(_gateway->GetFieldValue(0,2).c_str(),0);

    NewAns(_gateway->GetRecCount()-1);

    for (int i = 1; i < _gateway->GetRecCount(); i++)
    {
      TStockInfo *ti = &(*FAnswer)[i-1].QryStocks.StockInfo;
      memset(ti, 0, sizeof(TStockInfo));

      strncpy(ti->SecuID,   _gateway->GetFieldValue(i,3).c_str(), 7);
      strncpy(ti->SecuDesc, _gateway->GetFieldValue(i,4).c_str(), 8);
      ti->BalQty    = toInt(_gateway->GetFieldValue(i,5).c_str(), -1);
      ti->AvlQty    = toDouble(_gateway->GetFieldValue(i,6).c_str(), -1);
      ti->FloatProfit  = toDouble(_gateway->GetFieldValue(i,8).c_str(), -1);
      ti->CostPrice     = toDouble(_gateway->GetFieldValue(i,9).c_str(), -1);
      ti->MktVal      = toDouble(_gateway->GetFieldValue(i,7).c_str(), -1);
      ti->Bourse = FRequest.QryStocks.Bourse;
    }
  }
  __finally
  {
  }

  return 0;
}


int TTrdItf_JSD_GD::QryETFs()    //��ѯETF������Ϣ
{
  string cmd;

  char et;
  switch (FRequest.QryStocks.Bourse)
  {
    case bsSHS : et = '1'; break;
    case bsSZS : et = '2'; break;
    default: return -1;
  }

  try
  {
    //******************************//
    //**   ��ѯETF���ӿ��깺���   *//
    //******************************//

    //    ----1-----|-------2------|----3---|---4----|---5--|
    //CMD ���ܺ�(205)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|
    //    ---------------6----------------|
    //    �ɶ����루�ո��ʾ���йɶ����룩|
    //    -----7-----|-----------8----------|---9----|
    //    �������   |��������              |ί�з�ʽ|

    //                1| 2| 3|| 5| 6|7 |8| 9|
    cmd = stringprintf("205|%s|%c||%s|%s|%s|%d|%s|",     //
      FJSDSet.branch_no,                         // 2
      et,                                        // 3
      FAccInfo.Capital,                          // 5
      et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 6
      FRequest.QryStocks.EtfIDL1,                 // 7
      FRequest.QryStocks.EtfUnit,
      ENTRUST_WAY_GD[FJSDSet.entrust_way]);         // 9

      //  1.�г�����  2.֤ȯ����    3.֤ȯ����  4.	����Ҫ������   5.	�����깺����
      //  6.	��Ҫ��������  7.	���滻��� 8.	����������
      //  9.	������δ�ɽ������蹺������������Ҫ�������������깺������������δ�ɽ�������

    if (_gateway->WaitAnswer(cmd.c_str(),9,false)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    int count = _gateway->GetRecCount();


    NewAns(_gateway->GetRecCount());

    for (int i = 1; i < _gateway->GetRecCount(); i++)
    {
      TStockInfo *ti = &(*FAnswer)[i-1].QryStocks.StockInfo;
      memset(ti, 0, sizeof(TStockInfo));

      strncpy(ti->SecuID,   _gateway->GetFieldValue(i,2).c_str(), 7);
      strncpy(ti->SecuDesc, _gateway->GetFieldValue(i,3).c_str(), 8);
      ti->BalQty   = toInt(_gateway->GetFieldValue(i,4).c_str(), -1);
      ti->AvlQty   = toDouble(_gateway->GetFieldValue(i,6).c_str(), -1);
      ti->TccQty   = toDouble(_gateway->GetFieldValue(i,5).c_str(), -1);
      ti->CostPrice = toDouble(_gateway->GetFieldValue(i,7).c_str(), -1);
      ti->FloatProfit = toDouble(_gateway->GetFieldValue(i,8).c_str(), -1);
      ti->Bourse = FRequest.QryStocks.Bourse;

    }

    //******************************//
    //**   ��ѯETF��������       *//
    //******************************//

    //    ----1-----|-------2------|----3---|---4----|---5--|
    //CMD ���ܺ�(201)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|
    //    ---------------6----------------|
    //    �ɶ����루�ո��ʾ���йɶ����룩|
    //    -----7-----|-----------8--------------------------|---9----|
    //    �������   |�깺��ر�־��1���깺��2����أ�      |ί�з�ʽ|

    //                1| 2| 3|| 5| 6|7 |8| 9|
    cmd = stringprintf("201|%s|%c||%s|%s|%s|2|%s|",     //
      FJSDSet.branch_no,                         // 2
      et,                                        // 3
      FAccInfo.Capital,                          // 5
      et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 6
      FRequest.QryStocks.EtfIDL1,                 // 7
      ENTRUST_WAY_GD[FJSDSet.entrust_way]);         // 9


        // 1.�ɹ���־  2.�ʽ����  3.�����ʽ�  4.����δ���ս��  5.����δ���ս��
        // 6.ί��δ�ɽ�������    7.��������  8.�쳣�����ʽ�
    if (_gateway->WaitAnswer(cmd.c_str(),8)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
      ODS("�����: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    TStockInfo *ti = &(*FAnswer)[count-1].QryStocks.StockInfo;
    memset(ti, 0, sizeof(TStockInfo));

//          if (et == '1')              si->SecuID[0] = 'H';
//          else              si->SecuID[0] = 'S';

    strncpy(ti->SecuID, FRequest.QryStocks.EtfIDL2, 7);
    ti->TccQty    = toInt(_gateway->GetFieldValue(0,2).c_str(), -1);
    ti->Bourse = FRequest.QryStocks.Bourse;

  }
  __finally
  {
  }

  return 0;
}



//////���׺���/////
//---------------------------------------------------------------------------
// CMD: ���ܺ�(3)|����Ӫҵ������|�г�����|��ʱ����|�ɶ��ʺ�|֤ȯ����|��������(1���롢2����)
//      |ί������|ί�м۸�|ί�з�ʽ|���б�־|���д���|
//---------------------------------------------------------------------------
int TTrdItf_JSD_GD::Entrust()
{
  string cmd;
	char et;

	switch (FRequest.Entrust.Bourse)
  {
      case bsSHS : et = '1'; break;
      case bsSZS : et = '2'; break;
      case bsXXX : et = '1'; break;
      default: return -1;
  }


  if (FRequest.Entrust.Prop == 1)
  {
      // 1.���ܺ�(202)  2.Ӫҵ������  3.�г�����  4.��ʱ����  5.�ͻ���
      // 6.�ɶ�����     7.�깺/��ر�־��1���깺��2����أ�
      // 8.�������     9.�깺�ݶ�    10.ί�з�ʽ
      //                1| 2| 3|| 5| 6|7| 8| 9|10|

      char ss;
      if(FRequest.Entrust.BorS=='B')  ss='1';
      else                            ss='2';


      cmd = stringprintf("202|%s|%c||%s|%s|%c|%s|%d|%s|",
          FJSDSet.branch_no,                          // 2
          et,                                         // 3
          FAccInfo.Capital,                           // 5
          et == '1' ? FAccInfo.SH : FAccInfo.SZ,      // 6
          ss,
          FRequest.Entrust.SecuID,                    // 8
          FRequest.Entrust.Num,                           // 9
          ENTRUST_WAY_GD[FJSDSet.entrust_way]);          // 10
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
      char ss;
      if(FRequest.Entrust.BorS=='B')  ss='1';
      else                            ss='2';


      cmd = stringprintf("3|%s|%c||%s|%s|%c|%d|%.3f|%s|||",
          FJSDSet.branch_no,                         // 2
          et,                                        // 3
          et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 5
          FRequest.Entrust.SecuID,                   // 6
          ss,
          FRequest.Entrust.Num,                          // 8
          FRequest.Entrust.Price,                        // 9
          ENTRUST_WAY_GD[FJSDSet.entrust_way]);         // 10
  }

  if (_gateway->WaitAnswer(cmd.c_str(),2)!=TRUE)
  {
    setErrorMsg(_gateway->getErrorMsg());
    ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
    ODS("�����: [%s]",_gateway->GetRequestBuffer());
    return -1;
  }
  NewAns(1);
  strncpy((*FAnswer)[0].Entrust.OrderID, _gateway->GetFieldValue(0,2).c_str(), 19);

  return 0;
}


int TTrdItf_JSD_GD::Undo() //ί�г���
{

  string cmd;
  //
  //     ----1----|-------2------|----3---|----4---|---5--|---6--|----7---|
  //CMD: ���ܺ�(4)|����Ӫҵ������|�г�����|��ʱ����|�ͻ���|��ͬ��|ί�з�ʽ|
  //
  //              1| 2| 3|| 5| 6| 7|
  cmd = stringprintf("4|%s|%c||%s|%s|%s|",
      FJSDSet.branch_no,                          // 2
      FRequest.Undo.Bourse == bsSHS ? '1' : '2',   // 3
      FAccInfo.Capital,                           // 5
      FRequest.Undo.OrderID,                   // 6
      ENTRUST_WAY_GD[FJSDSet.entrust_way]);          // 7

  if (_gateway->WaitAnswer(cmd.c_str(),2)!=TRUE)
  {
    setErrorMsg(_gateway->getErrorMsg());
    ODS("����ʧ�ܣ�[%s]",_gateway->getErrorMsg());
    ODS("�����: [%s]",_gateway->GetRequestBuffer());
    return -1;
  }
  NewAns(1);

  return 0;
}


