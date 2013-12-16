//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <SysUtils.hpp>
#include "UTrdItf_SYWG.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
TTrdItf_SYWG::TTrdItf_SYWG(TSYWGSet *pSet)
{
  m_CnID = 0;
  m_AccType = 0;
  CopyMemory(&FSYWGSet, pSet, sizeof(TSYWGSet));
}
//---------------------------------------------------------------------------
TTrdItf_SYWG::~TTrdItf_SYWG()
{
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::Init()  //��ʼ��
{
  return LocalInit();
}
//---------------------------------------------------------------------------
/*
1�� ���ܺ�0x101 У�����������, ���ʺ�
���ô˹��ܣ���У�����������ͨ�����ÿͻ����ʺŽ����������׵Ĵ�״̬��ֱ���������֮һ������
1�������ӵ��ù���0x103�ر��ʺ�
2�������ӹرա�
*/
/*
#pragma pack(push, 1)
//������Ϣ

struct SWI_OpenAccountRequest
{
	struct SWI_BlockHead head;	// function_no==0x101, block_type == 1
	char   account_type;     	// �ͻ��ʺ����ͣ��������ֵ�˵����
	char   account[16];      	// �ͻ��ʺ�
	char   pwd[8];           	// ��������
	//short  op_code;             // ����Ա����
	//unsigned  long   flag;         //"��������"�жϱ�־λ���,ÿһ��������λ��Ӧһ��"��������",ȱʡֵΪ0��ʾ���ж��κ�"��������"
	//char   productno [7];		    //��Ʒ��Ϣ��ţ�5λ�����������Ĳ�Ʒ����+2λ��
	//��Ʒ���루��7λ�ַ�����ȱʡֵΪ�ա�

        //char pad[7];
};
#pragma pack(pop)
*/

int TTrdItf_SYWG::SetAccount() //�����ʺ�
{
  if(FRequest.SetAccount.Sort == asCA)//�ʽ��ʺ�
    m_AccType = '0';//A���ʽ��ʺ�
  else if(FRequest.SetAccount.Sort == asSH)//�Ϻ��������Ĺɶ�����
    m_AccType = '1';//��A֤��
  else if(FRequest.SetAccount.Sort == asSZ)
    m_AccType = '2';//��A֤��
  else
  {
    ODS("��Ч���û��ʺ�����:%d", FRequest.SetAccount.Sort);
    return -1;
  }

  if(OpenAccount(m_AccType, FRequest.SetAccount.Account, FRequest.SetAccount.PW) != 0)
    return -1;

  lstrcpyn(FAccInfo.Capital, FRequest.SetAccount.Account, 13);//�ʽ��ʺ�
  lstrcpyn(FAccInfo.PW, FRequest.SetAccount.PW, 13);//�ʺ�����
  strcpy(FAccInfo.SH, "");//�Ϻ��������ɶ�����
  strcpy(FAccInfo.SZ, "");//���ڽ������ɶ�����

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::GetTrdInfo()   //ȡ���̿�����
{
  ////Checked200412302210!!!
  //Request;
  SWI_SecurityInfoRequest swSecurityReq;
  InitRequest(&swSecurityReq, sizeof(SWI_SecurityInfoRequest), SWI_FUNC_QUERY_SECURITY_INFO);

  swSecurityReq.exchange_no = 0;////��������ţ��������ֵ�˵����0 ----- ȫ��A�ɣ������ڲ�ѯ��
  //swSecurityReq.security_idx = ; //???֤ȯ��ţ���ע��
  lstrcpyn(swSecurityReq.security_code, FRequest.GetTrdInfo.SecuID+1, 7);// ֤ȯ����

  if(SetRequest(&swSecurityReq, sizeof(SWI_SecurityInfoRequest)) != 0)
  {
    ODS("����GetTrdInfo����ʧ��");
    return -1;
  }

    //Response;
  SWI_SecurityInfoReturn swSecurityAns;
  if(FSafeSock.RecvAnswer(&swSecurityAns, sizeof(SWI_SecurityInfoReturn)) != 0)
  {
    ODS("����GetTrdInfo������Ϣʧ��");
    return -2;
  }

  if(swSecurityAns.return_status <= 0)
  {
    ShowErrorMsg("GetTrdInfo����ʧ��", swSecurityAns.return_status);
    return -1;
  }

  //set value;
  NewAns(1);
  (*FAnswer)[0].GetTrdInfo.BuyInfo.ZXJ    = SWISmallMoneyToDouble(swSecurityAns.current_price);//���¼�
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Price1 = SWISmallMoneyToDouble(swSecurityAns.buy_price_1);//���1
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Price2 = SWISmallMoneyToDouble(swSecurityAns.buy_price_2);//���2
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Price3 = SWISmallMoneyToDouble(swSecurityAns.buy_price_3);//���3
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Volum1 = swSecurityAns.buy_amount_1;//����1
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Volum2 = swSecurityAns.buy_amount_2;//����2
  (*FAnswer)[0].GetTrdInfo.BuyInfo.Volum3 = swSecurityAns.buy_amount_3;//����3
  (*FAnswer)[0].GetTrdInfo.BuyInfo.CJSL   = swSecurityAns.amount; //�ɽ�����

  (*FAnswer)[0].GetTrdInfo.SellInfo.ZXJ    = SWISmallMoneyToDouble(swSecurityAns.current_price);
  (*FAnswer)[0].GetTrdInfo.SellInfo.Price1 = SWISmallMoneyToDouble(swSecurityAns.sale_price_1);
  (*FAnswer)[0].GetTrdInfo.SellInfo.Price2 = SWISmallMoneyToDouble(swSecurityAns.sale_price_2);
  (*FAnswer)[0].GetTrdInfo.SellInfo.Price3 = SWISmallMoneyToDouble(swSecurityAns.sale_price_3);
  (*FAnswer)[0].GetTrdInfo.SellInfo.Volum1 = swSecurityAns.sale_amount_1;
  (*FAnswer)[0].GetTrdInfo.SellInfo.Volum2 = swSecurityAns.sale_amount_2;
  (*FAnswer)[0].GetTrdInfo.SellInfo.Volum3 = swSecurityAns.sale_amount_3;
  (*FAnswer)[0].GetTrdInfo.SellInfo.CJSL   = swSecurityAns.amount;

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryMoney()     //�ʽ��ѯ
{
  ////Checked200412302210!!!
  //Request;
  SWI_QueryMoneyRequest swMoneyReq;
  InitRequest(&swMoneyReq, sizeof(SWI_QueryMoneyRequest), SWI_FUNC_QUERY_MONEY);

  swMoneyReq.account_type = m_AccType;// �ͻ��ʺ�����
  lstrcpyn(swMoneyReq.account, FAccInfo.Capital, 14);// �ͻ��ʺ�
  swMoneyReq.currency_type = '1'; //����----- �����

  if(SetRequest(&swMoneyReq, sizeof(SWI_QueryMoneyRequest)) != 0)
    return -1;

  //Response;
  SWI_QueryMoneyReturn swMoneyAns;
  if(FSafeSock.RecvAnswer(&swMoneyAns, sizeof(SWI_QueryMoneyReturn)) != 0)
    return -2;
      
  if(swMoneyAns.return_status < 0)// <0  ------ ��ѯʧ��
  {
    ("QryMoney����ʧ�ܣ�return status = %d", swMoneyAns.return_status);
    return -1;
  }

  //Set value;
  NewAns(1);
  (*FAnswer)[0].QryMoney.Balance = SWIMoneyToDouble(swMoneyAns.available);//�ʽ����
  (*FAnswer)[0].QryMoney.Available = SWIMoneyToDouble(swMoneyAns.buyable);//�ʽ���ö�
  (*FAnswer)[0].QryMoney.asset_balance = 0;//???�ʲ���ֵ---û�ж���

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryStock()     //�ɷݲ�ѯ
{
  //Checked200412302210!!!
  SWI_QueryStockRequest swStockReq;
  InitRequest(&swStockReq, sizeof(SWI_QueryStockRequest), SWI_FUNC_QUERY_STOCK);

  swStockReq.account_type = m_AccType;// �ͻ��ʺ�����
  lstrcpyn(swStockReq.account, FAccInfo.Capital, 16);// �ͻ��ʺ�
  swStockReq.exchange_no = 0;//��������ţ�0 ----- ȫ��A�ɣ������ڲ�ѯ��
  lstrcpyn(swStockReq.security_code, FRequest.QryStock.SecuID+1, 7);// ֤ȯ���루space(6)��ʾȫ����
  swStockReq.max_results = 1;// // ����ѯ��¼��---???ֻ��һ����¼
  //swStockReq.flag = ;//����ӯ���������ݱ�־  =0��ȱʡ�������ض�Ӧֵ����Ӧ�ֶ�Ϊ0  =1������ӯ����������  ����flag��Ҫ�����ٵ���flag=1,��������Ӱ��
  //swStockReq.stock_account = ;//��ѯ֤ȯ�ʺ�����,����֤ȯ�ʺ�Ϊ�������˽������ȱʡ

  if(SetRequest(&swStockReq, sizeof(SWI_QueryStockRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryStockReturn swStockAns;
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_STOCK, sizeof(SWI_QueryStockResult),  \
                            &swStockAns, sizeof(SWI_QueryStockReturn)))
      return -1;

    if(pResult->Count > 0)//�н��������
    {
      NewAns(1);
      //set value;
      (*FAnswer)[0].QryStock.Balance = ((SWI_QueryStockResult*)(pResult->Items[0]))->deposite;//????�ʽ����=��Ʊ���
      (*FAnswer)[0].QryStock.Available = ((SWI_QueryStockResult*)(pResult->Items[0]))->available;//???�ʽ���ö�=�������
      (*FAnswer)[0].QryStock.BuyFreeze = 0;
      (*FAnswer)[0].QryStock.SellFreeze = 0;
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryCanBuy()    //ȡ��������
{
  // ��ʱ����
  ODS("QryCanBuy��ʱ����");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryDetail()    //�ɽ���ѯ
{
  int reqry_num=0;

HH:
  //codehunter add 2005216
  if(FRequest.QryDetail.ContractID[0]==0) return -1;
  //Checked200412302210!!!
  SWI_QueryEntrustRequest swEntrustReq;
  InitRequest(&swEntrustReq, sizeof(SWI_QueryEntrustRequest), SWI_FUNC_QUERY_ENTRUST);
  
  swEntrustReq.account_type = m_AccType;// �ͻ��ʺ����ͣ��������ֵ�˵����
  lstrcpyn(swEntrustReq.account, FAccInfo.Capital, 16);// �ͻ��ʺ�
  swEntrustReq.exchange_no = GetExchangeNo(FRequest.QryDetail.Bourse);// ��������ţ��������ֵ�˵����
  swEntrustReq.begin_date =  StrToInt(Date().FormatString("yyyymmdd"));//��ʼ���ڣ����磺yyyymmdd��
  swEntrustReq.end_date = swEntrustReq.begin_date;// �������ڣ����磺yyyymmdd��---��ѯ���յ�����ί��
//  int nEntrustSn = StrToIntDef(String(FRequest.QryDetail.ContractID).Trim(), 0);
  //if(nEntrustSn == -1)
    //return -1;
  swEntrustReq.entrust_sn = StrToIntDef(String(FRequest.QryDetail.ContractID).Trim(), 0);// ί�б�ţ�0��ʾȫ����
  //swEntrustReq.security_code = ;// ��Ʊ���루�ձ�ʾȫ����
  swEntrustReq.max_results = 0;//����ѯ��¼��---???ֻ��һ����¼
  //swEntrustReq.stock_type = ;	// ֤ȯ���, ȱʡΪ�գ���ѯȫ��֤ȯ���.

  if(SetRequest(&swEntrustReq, sizeof(SWI_QueryEntrustRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryEntrustReturn swEntrustAns;
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_ENTRUST, sizeof(SWI_QueryEntrustResult),  \
                                  &swEntrustAns, sizeof(SWI_QueryEntrustReturn)))
      return -1;

    if(pResult->Count > 0)//�н��������
    {
      NewAns(1);//��Ϊֻ����һ����¼

      SWI_QueryEntrustResult *pRecord = NULL;
      for(int i=0; i<pResult->Count; i++)
      {
        pRecord = ((SWI_QueryEntrustResult*)(pResult->Items[i]));
        if(pResult->Count > 1 && lstrcmpi(pRecord->security_code, "510051") != 0)//????iֻ��Ҫ����ETF1��������¼
          continue;

        if(pResult->Count > 1 && lstrcmpi(pRecord->security_code, "510181") != 0)//????iֻ��Ҫ����ETF1��������¼
          continue;
        //set value;
        (*FAnswer)[0].QryDetail.Price = SWISmallMoneyToDouble(pRecord->price);//�ɽ��۸�---�鲻����,ֱ����ί�м۸���棨�����أ�
        (*FAnswer)[0].QryDetail.Num = pRecord->bargain_ammount;//�ɽ�����

        (*FAnswer)[0].QryDetail.UndoNum = 0;
        if(   pRecord->entrust_status == '4'
           || pRecord->entrust_status == '6'
           || (pRecord->entrust_status == '5' && pRecord->bargain_ammount > 0) )//'4'---��Чί��,'6'---�ѳ���,'5' ----- ���ֳ���
        {
          if(pRecord->entrust_status == '5' && ++reqry_num < 3 ) //����ǲ������ٲ�ֱ�� reqry_num >3
          {
            ReleaseList(pResult);
            Sleep(100);
            goto HH;
          }

          (*FAnswer)[0].QryDetail.UndoNum = pRecord->bargain_ammount - pRecord->stock_ammount;//��������
        }
        //(*FAnswer)[0].QryDetail.status = 0;//״̬---������д

        //if((*FAnswer)[0].QryDetail.Price<0.001) (*FAnswer)[0].QryDetail.Num=0;
        
        break;
      }
    }
    else
    {
      ODS("QryDetail���ز�ѯ�����Ϊ��");
      return -1;
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryHisDetail() //��ʷ�ɽ���ѯ
{
  //��ʱ����
  ODS("QryHisDetail��ʱ����");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryCsn()       //��ѯĳ��ί�к�ͬ
{
  //��ʱ����
  ODS("QryCsn��ʱ����");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryCurCsn()    //����ί�в�ѯ
{
  //Checked200412302210!!!
  int nDate = StrToInt(Date().FormatString("yyyymmdd"));

  return QueryEntrust(nDate, nDate);
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryHisCsn()    //��ʷί�в�ѯ
{
  //Checked200412302210!!!
  int nStartDate = StrToIntDef(FRequest.QryHisCsn.StartDay, StrToInt(Date().FormatString("yyyymmdd")));
  int nEndDate = StrToIntDef(FRequest.QryHisCsn.EndDay, StrToInt(Date().FormatString("yyyymmdd")));

  return QueryEntrust(nStartDate, nEndDate);
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryCurTrd()    //���ճɽ���ѯ
{
  SWI_QueryBusinessRequest swBussinessReq;
  InitRequest(&swBussinessReq, sizeof(SWI_QueryBusinessRequest), SWI_FUNC_QUERY_BUSINESS);

  swBussinessReq.account_type = m_AccType;// �ͻ��ʺ�����
  lstrcpyn(swBussinessReq.account, FAccInfo.Capital, 16);// �ͻ��ʺ�
  swBussinessReq.exchange_no = 0;//��������� ----- ȫ��A�ɣ������ڲ�ѯ��
  swBussinessReq.entrust_sn = 0;////ί�б�ţ�0��ʾȫ����
  strcpy(swBussinessReq.security_code, "      ");//��Ʊ���루space(6)��ʾȫ����
  swBussinessReq.flag = 1;              //�ϲ���ʽ 0�����ϲ�,1�����ڡ�֤ȯ�ʺš���Ʊ���롢��������ϲ�
  swBussinessReq.begin_serial_no = 0;//// �ɽ���ϸ��ʼ��ˮ�ţ�ȱʡֵ=0��
  
  if(SetRequest(&swBussinessReq, sizeof(SWI_QueryBusinessRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryBusinessReturn swBussinessAns;
  
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_BUSINESS, sizeof(SWI_QueryBusinessResult),  \
                                  &swBussinessAns, sizeof(SWI_QueryBusinessReturn)))//>0   ��ѯ�ɹ�
      return -1;
      
    if(pResult->Count > 0)//�н��������
    {
      NewAns(pResult->Count);
      TTradeInfo *pTrdInfo = NULL;
      SWI_QueryBusinessResult *pRecord = NULL;

      for(int i=0; i<pResult->Count; i++)//�н��������
      {
        pTrdInfo = &((*FAnswer)[i].QryCurTrd.TrdInfo);
        pRecord = ((SWI_QueryBusinessResult*)(pResult->Items[i]));

        pTrdInfo->SecuID[0] = (pRecord->exchange_no == 1) ? 'H' : 'S';
        lstrcpyn(pTrdInfo->SecuID+1, pRecord->security_code, 7);//֤ȯ����
        lstrcpyn(pTrdInfo->SecuDesc, pRecord->security_name, 9) ; //֤ȯ����

        lstrcpyn(pTrdInfo->Time, pRecord->bargain_time, 9);//�ɽ�ʱ��
        lstrcpyn(pTrdInfo->Date, Date().FormatString("yyyymmdd").c_str(), 9);//ί������

        if(pRecord->bs_type == '1')//'1' ----- ����//������� B,S
          pTrdInfo->Type = 'B';
        else if(pRecord->bs_type == '2')//'2' ----- ����
          pTrdInfo->Type = 'S';
        else
          pTrdInfo->Type = 'N';   //codehunter add

        pTrdInfo->Vol = pRecord->stock_ammount ;//�ɽ�����
        pTrdInfo->Price = SWISmallMoneyToDouble(pRecord->price);//�ɽ��۸�
      }
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;  
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryHisTrd()    //��ʷ�ɽ���ѯ
{
  ////Checked200412302210!!!
  SWI_QueryHisBusinessRequest swHisBussinessReq;
  InitRequest(&swHisBussinessReq, sizeof(SWI_QueryHisBusinessRequest), SWI_FUNC_QUERY_HISTORY_BUSINESS);

  swHisBussinessReq.account_type = m_AccType;// �ͻ��ʺ�����
  lstrcpyn(swHisBussinessReq.account, FAccInfo.Capital, 16);// �ͻ��ʺ�
  swHisBussinessReq.exchange_no = 0;//��������� ----- ȫ��A�ɣ������ڲ�ѯ��
  swHisBussinessReq.begin_date = StrToInt((String)FRequest.QryHisTrd.StartDay);// ��ʼ����
  swHisBussinessReq.end_date = StrToInt((String)FRequest.QryHisTrd.EndDay);// ��������
  strcpy(swHisBussinessReq.security_code, "      ");//��Ʊ���루space(6)��ʾȫ����
  swHisBussinessReq.flag = 1;//�ϲ���ʽ 0�����ϲ�,1�����ڡ�֤ȯ�ʺš���Ʊ���롢��������ϲ�
  swHisBussinessReq.max_results = 0;//����ѯ��¼��---???ֻ��һ����¼

  if(SetRequest(&swHisBussinessReq, sizeof(SWI_QueryHisBusinessRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryHisBusinessReturn swHisBussinessAns;
  
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_HISTORY_BUSINESS, sizeof(SWI_QueryHisBusinessResult),  \
                                  &swHisBussinessAns, sizeof(SWI_QueryHisBusinessReturn)))//>0   ��ѯ�ɹ�
      return -1;
      
    if(pResult->Count > 0)//�н��������
    {
      NewAns(pResult->Count);
      TTradeInfo *pTrdInfo = NULL;
      SWI_QueryHisBusinessResult *pRecord = NULL;

      for(int i=0; i<pResult->Count; i++)//�н��������
      {
        pTrdInfo = &((*FAnswer)[i].QryCurTrd.TrdInfo);
        pRecord = ((SWI_QueryHisBusinessResult*)(pResult->Items[i]));

        pTrdInfo->SecuID[0] = (pRecord->exchange_no == 1) ? 'H' : 'S';
        lstrcpyn(pTrdInfo->SecuID+1, pRecord->security_code, 7);//֤ȯ����
        lstrcpyn(pTrdInfo->SecuDesc, pRecord->security_name, 9) ; //֤ȯ����

        lstrcpyn(pTrdInfo->Time, pRecord->bargain_time, 9);//�ɽ�ʱ��
        lstrcpyn(pTrdInfo->Date, IntToStr(pRecord->bargain_date).c_str(), 9);//ί������

        if(pRecord->bs_type == '1')//'1' ----- ����//������� B,S
          pTrdInfo->Type = 'B';
        else if(pRecord->bs_type == '2')//'2' ----- ����
          pTrdInfo->Type = 'S';
        else
          pTrdInfo->Type = 'N';  //codehunter

        pTrdInfo->Vol = pRecord->stock_change;//�ɽ�����
        pTrdInfo->Price = SWISmallMoneyToDouble(pRecord->occur_price);//�ɽ��۸�
      }
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryBill()      //��ѯ�ʽ���ˮ�����ʵ���
{
  ////Checked200412302210!!!
  SWI_QueryFundDetailRequest swFundDetailReq;
  InitRequest(&swFundDetailReq, sizeof(SWI_QueryFundDetailRequest), SWI_FUNC_QUERY_FUND_DETAIL);

  swFundDetailReq.account_type = m_AccType;// �ͻ��ʺ�����
  lstrcpyn(swFundDetailReq.account, FAccInfo.Capital, 16); // �ͻ��ʺ�
  swFundDetailReq.exchange_no = 0;//��������� ----- ȫ��A�ɣ������ڲ�ѯ��
  swFundDetailReq.begin_date = StrToIntDef((String)FRequest.QryBill.StartDay, StrToInt(Date().FormatString("yyyymmdd")));// ��ʼ���ڣ����磺yyyymmdd��
  swFundDetailReq.end_date = StrToIntDef((String)FRequest.QryBill.EndDay, StrToInt(Date().FormatString("yyyymmdd")));// �������ڣ����磺yyyymmdd��
  swFundDetailReq.currency_type = '1';///����'1' ----- �����
  swFundDetailReq.max_results = 0;// ����ѯ��¼��
  swFundDetailReq.flag = 0;// ��ѯ��ʽ 0 - �ʽ���ϸ

  if(SetRequest(&swFundDetailReq, sizeof(SWI_QueryFundDetailRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryFundDetailReturn swFundDetailAns;
  
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_FUND_DETAIL, sizeof(SWI_QueryFundDetailResult),  \
                                  &swFundDetailAns, sizeof(SWI_QueryFundDetailReturn))) // >0 ------ ��ѯ�ɹ�
      return -1;
      
    if(pResult->Count > 0)//�н��������
    {
      NewAns(pResult->Count);
      TFundInfo *pFundInfo = NULL;
      SWI_QueryFundDetailResult *pRecord = NULL;

      for(int i=0; i<pResult->Count; i++)//�н��������
      {
        pFundInfo = &((*FAnswer)[i].QryBill.FundInfo);
        pRecord = ((SWI_QueryFundDetailResult*)(pResult->Items[i]));

        strcpy(pFundInfo->Date, IntToStr(pRecord->change_date).c_str());//ί������=�������ڣ����磺yyyymmdd��
        pFundInfo->SecuID[0] = 'H';//???Ĭ���Ͻ���
        lstrcpyn(pFundInfo->SecuID+1, pRecord->security_code, 7);//֤ȯ����
        lstrcpyn(pFundInfo->SecuDesc, pRecord->security_name, 9) ; //֤ȯ����
        if(pRecord->stock_ammount > 0)
          strcpy(pFundInfo->Type, "Buy"); //�������˵��---����ν
        else
         strcpy(pFundInfo->Type, "Sell");

        pFundInfo->Vol = abs(pRecord->stock_ammount);//�ɽ����� = ֤ȯ�ɽ��������������룻����������
        pFundInfo->Price = SWISmallMoneyToDouble(pRecord->price);//�ɽ��۸�= ֤ȯ�ɽ�����
        pFundInfo->TrdMny = SWIMoneyToDouble(pRecord->change);//�ɽ����=�������������
        pFundInfo->Balance = SWIMoneyToDouble(pRecord->deposite);//�ʽ����=���������η������ʽ����
      }
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QryStocks()    //��ѯ�ʺ������еĹɷ�
{
  //Checked200412302210!!!
  SWI_QueryStockRequest swStockReq;
  InitRequest(&swStockReq, sizeof(SWI_QueryStockRequest), SWI_FUNC_QUERY_STOCK);
  
  swStockReq.account_type = m_AccType;// �ͻ��ʺ�����
  lstrcpyn(swStockReq.account, FAccInfo.Capital, 16);// �ͻ��ʺ�
  swStockReq.exchange_no = 0;//��������ţ�0 ----- ȫ��A�ɣ������ڲ�ѯ��
  //strcpy(swStockReq.security_code, "");// ֤ȯ����,�ձ�ʾ��ѯ���й�Ʊ�ֲ������
  swStockReq.max_results = 0;// // ����ѯ��¼��---��0��ʾȫ����
  //swStockReq.flag = ;//����ӯ���������ݱ�־  =0��ȱʡ�������ض�Ӧֵ����Ӧ�ֶ�Ϊ0  =1������ӯ����������  ����flag��Ҫ�����ٵ���flag=1,��������Ӱ��
  //swStockReq.stock_account = ;//��ѯ֤ȯ�ʺ�����,����֤ȯ�ʺ�Ϊ�������˽������ȱʡ

  if(SetRequest(&swStockReq, sizeof(SWI_QueryStockRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryStockReturn swStockAns;
  try
  {
    pResult = new TList();
    if(!GetQueryResult(pResult, SWI_FUNC_QUERY_STOCK, sizeof(SWI_QueryStockResult),  \
                            &swStockAns, sizeof(SWI_QueryStockReturn)))
      return -1;

    if(pResult->Count > 0)//�н��������
    {
      NewAns(pResult->Count);
      //set value;
      for(int i=0; i<pResult->Count; i++)
      {
        TStockInfo *pStock = &(*FAnswer)[i].QryStocks.StockInfo;
        SWI_QueryStockResult *pRecord = ((SWI_QueryStockResult*)(pResult->Items[i]));

        pStock->SecuID[0] = (pRecord->exchange_no == 1) ? 'H' : 'S';
        lstrcpyn(pStock->SecuID+1, pRecord->security_code, 7);//֤ȯ����
        //pStock->SecuDesc = ;    //֤ȯ����
        pStock->Balance = pRecord->deposite;//���
        pStock->Available = pRecord->available;//������
        pStock->BuyFreeze = 0;//���붳��
        pStock->SellFreeze = 0;//��������
        pStock->AbnorFreeze = 0;//�쳣����

        pStock->Cost = 0;//�ο��ɱ�
        pStock->CostPrice = SWISmallMoneyToDouble(pRecord->hold_price);//�ο��ɱ���
        pStock->CurVal = 0;//�ο���ֵ
        pStock->CurPrice = SWISmallMoneyToDouble(pRecord->current_price);//�ο��м�
        pStock->ProfitAndLoss = 0;//�ο�ӯ��
      }
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }
  
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::Undo() //ί�г���
{
  ////Checked200412302210!!!
  //Request;
  SWI_WithdrawEntrustRequest swWithdrawReq;
  InitRequest(&swWithdrawReq, sizeof(SWI_WithdrawEntrustRequest), SWI_FUNC_WITHDRAW);
  
  swWithdrawReq.account_type = m_AccType;// �ͻ��ʺ�����
  lstrcpyn(swWithdrawReq.account, FAccInfo.Capital, 16);// �ͻ��ʺ�
  swWithdrawReq.exchange_no = GetExchangeNo(FRequest.Undo.Bourse);// ���������
  int nEntrustSn = StrToIntDef(String(FRequest.Undo.ContractID).Trim(), -1);
  if(nEntrustSn == -1)
    return -1;

  swWithdrawReq.entrust_sn = nEntrustSn;// ί�б��

  if(SetRequest(&swWithdrawReq, sizeof(SWI_WithdrawEntrustRequest)) != 0)
    return -1; 

  //Response;
  SWI_WithdrawEntrustReturn swWithdrawAns;
  if(FSafeSock.RecvAnswer(&swWithdrawAns, sizeof(SWI_WithdrawEntrustReturn)) != 0)
    return -2;
    
  if(swWithdrawAns.return_status < 0)//<0  ------ ����ʧ��
  {
    ShowErrorMsg("Undo����ʧ��", swWithdrawAns.return_status);
    return -1;
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::Buy()
{
  TBourse Bourse;
  if(FRequest.Buy.SecuID[0] == 'H' || FRequest.Buy.SecuID[0] == 'h')
    Bourse = bsSH;
  else if(FRequest.Buy.SecuID[0] == 'S' || FRequest.Buy.SecuID[0] == 's')
    Bourse = bsSZ;
  else
    return -1;

//#ifdef _DEBUG //
  if(lstrcmpi(FRequest.Buy.SecuID, "H510051") == 0)
  {
    FRequest.Buy.Price = 0;
  }
  else if(lstrcmpi(FRequest.Buy.SecuID, "H510181") == 0)
  {
    FRequest.Buy.Price = 0;
  }
//#endif
   
  SWI_AddEntrustReturn swAddAns;   
  if(Order('1', FRequest.Buy.SecuID+1, FRequest.Buy.Num, FRequest.Buy.Price, Bourse, &swAddAns, sizeof(SWI_AddEntrustReturn)) != 0)
    return -1;

  NewAns(1);
  strcpy((*FAnswer)[0].Buy.ContractID, IntToStr(swAddAns.entrust_sn).c_str());

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::Sell()
{
  TBourse Bourse;
  if(FRequest.Buy.SecuID[0] == 'H' || FRequest.Buy.SecuID[0] == 'h')
    Bourse = bsSH;
  else if(FRequest.Buy.SecuID[0] == 'S' || FRequest.Buy.SecuID[0] == 's')
    Bourse = bsSZ;
  else
    return -1;

//#ifdef _DEBUG
  if(lstrcmpi(FRequest.Buy.SecuID, "H510051") == 0)
  {
    FRequest.Buy.Price = 0;
  }
  else if(lstrcmpi(FRequest.Buy.SecuID, "H510181") == 0)
  {
    FRequest.Buy.Price = 0;
  }
//#endif
    
  SWI_AddEntrustReturn swAddAns;  
  if(Order('2', FRequest.Sell.SecuID+1, FRequest.Sell.Num, FRequest.Sell.Price, Bourse, &swAddAns, sizeof(SWI_AddEntrustReturn)) != 0)
    return -1;

  NewAns(1);
  strcpy((*FAnswer)[0].Sell.ContractID, IntToStr(swAddAns.entrust_sn).c_str());

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::Order(char BsType, const char *SecuID, int Num, double Price, TBourse Bourse, void *Block, int Size) //ί��
{
  ////Checked200412302210!!!
  //Request;
  SWI_AddEntrustRequest swAddReq;
  InitRequest(&swAddReq, sizeof(SWI_AddEntrustRequest), SWI_FUNC_ADD_ENTRUST);
  
  swAddReq.account_type = m_AccType;// �ͻ��ʺ�����
  lstrcpyn(swAddReq.account, FAccInfo.Capital, 16);// �ͻ��ʺ�
  swAddReq.exchange_no = GetExchangeNo(Bourse);// ���������
  swAddReq.bs_type = BsType;// �������
  lstrcpyn(swAddReq.security_code, SecuID, 7);// ֤ȯ����
  swAddReq.stock_amount = (long)Num;// ί������
  DoubleToSWISmallMoney(swAddReq.price, Price);// ί�м۸�
  swAddReq.effect_days = 1;//????--- ��Ч����
  //SWIMoney   apply_amount;  //������
  //BYTE    mark;             //�Ƿ�������� 1Ϊ�������,0Ϊ������ ȷʡΪ0
  //Int		Frozen_no ;        //֤ȯ���ʽ𶳽���ˮ��(��֤ͨר�ã�ȱʡΪ0)
  //SWIMoney		fund_amount;  //ί������(֧�ֿ���ʽ����С���ݶ�)
  //Char(10)    Entrust_sign; //����ǩ��(ȱʡΪ'')
  //SWIMoney    Cash_limit ;  //ί���ʽ���

  //Response;
  if(SetRequest(&swAddReq, sizeof(SWI_AddEntrustRequest)) != 0)
    return -1;

  if(FSafeSock.RecvAnswer(Block, Size) != 0)
    return -2;
    
  if( ((SWI_AddEntrustReturn *)Block)->return_status < 0) //  <0   ί��ʧ��
  {
    ShowErrorMsg("Order����ʧ��", ((SWI_AddEntrustReturn *)Block)->return_status);
    return -1;
  }

  return 0;
}
//---------------------------------------------------------------------------
void TTrdItf_SYWG::InitRequest(void *Block, WORD Size, WORD FunNo)
{
  memset(Block, 0, Size);
  ((SWI_BlockHead*)Block)->block_size  = Size;
  ((SWI_BlockHead*)Block)->block_type  = SWI_BT_REQUEST;
  ((SWI_BlockHead*)Block)->function_no = FunNo;
  ((SWI_BlockHead*)Block)->cn_id       = m_CnID;
  ((SWI_BlockHead*)Block)->source_dpt  = FSYWGSet.SrcDpt;//????�Ƿ���Ҫ��ֵΪ��һ�����������õ�������
  ((SWI_BlockHead*)Block)->dest_dpt    = FSYWGSet.DestDpt;//????
}
//---------------------------------------------------------------------------
BYTE TTrdItf_SYWG::GetExchangeNo(TBourse Bourse)
{
  if(Bourse == bsSH)
    return 1;
  else if(Bourse == bsSZ)
    return 2;
  else
    return 0;
}
//---------------------------------------------------------------------------
TBourse TTrdItf_SYWG::GetBourse(BYTE ExchangeNo)
{
  if(ExchangeNo == 1)
    return bsSH;
  else if(ExchangeNo == 2)
    return bsSZ;
  else
     return bsSH;
}
//---------------------------------------------------------------------------
//�����8�ֽ�SQLMONEY����ʾ���ڲ���ʾΪ__int64����ʮ���ƺ���λ������λС��, �磤12.32  ��ʾΪ 123200
double TTrdItf_SYWG::SWIMoneyToDouble(SWIMoney &swMoney)
{
  __int64 nMoney = *(__int64 *)&swMoney;
  return (double(nMoney))/10000.0;
}
//---------------------------------------------------------------------------
void TTrdItf_SYWG::DoubleToSWIMoney(SWIMoney &swMoney, double Money)
{
  __int64 nMoney = Money*10000;
  //memcpy(&swMoney, &nMoney, sizeof(SWIMoney));
  swMoney = *(SWIMoney *)&nMoney;
}
//---------------------------------------------------------------------------
//�۸�ʹ��LONG����ʾ����ʮ���ƺ���λ������λС������8.18��ʾΪ8180
double TTrdItf_SYWG::SWISmallMoneyToDouble(SWISmallMoney &swSMoney)
{
  return (double)swSMoney/1000.0;
}
//---------------------------------------------------------------------------
void TTrdItf_SYWG::DoubleToSWISmallMoney(SWISmallMoney &swSMoney, double Money)
{
  //long lMoney = (int)(Money * 1000.0 + 5)/10 * 10;
  long lMoney = (Money * 10000 + 1)/10;

  swSMoney = lMoney;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::LocalInit(void)
{
  int nRet = FSafeSock.Init(FSYWGSet.ServerAddr, FSYWGSet.ServerNode, FSYWGSet.ServerPort,  \
                            FSYWGSet.ServerIP, FSYWGSet.UseProtocol, FSYWGSet.UseDesencrypt);
  if(nRet != 0)
  {
    ODS("����AGX������ʧ�ܣ����������������");
    return -1;
  }

  //Init ConnectRequest
  //��Ϣͷ
  SWI_ConnectRequest swReqConnect;
  memset(&swReqConnect, 0, sizeof(SWI_ConnectRequest));
  
  swReqConnect.head.block_size =  sizeof(SWI_ConnectRequest);
  swReqConnect.head.block_type = SWI_BT_CN_REQUEST;//��������(������Կ) block_type == 6
  //swReqConnect.head.cn_id = 0;// �������Ӻ�
  //swReqConnect.head.source_dpt = 0;// ԴӪҵ�����
  swReqConnect.head.dest_dpt = 0;//FSYWGSet.DestDpt;//Ŀ��Ӫҵ�����

  //��Ϣ��
  swReqConnect.method = (FSYWGSet.UseDesencrypt) ? 1: 0;// �ͻ��˵ļ��ܷ�ʽ��method=1��
  swReqConnect.entrust_method = FSYWGSet.EntrustMethod; // ί�з�ʽ���������ֵ�˵����-=-????�ɿ�������������ȡ��
  swReqConnect.return_cp = BYTE(0);//�ͻ���ϣ���ķ��ؽṹ�������ֶεĴ���ҳ  0 -- MBCS  ��CP936�������ģ�, 1 -- Unicode(Java�ͻ���Ҫ)
  sock_client::AscToHex(swReqConnect.network, FSYWGSet.ClientAddr, 4); //�ͻ���Novell���κ�
  sock_client::AscToHex(swReqConnect.address, FSYWGSet.ClientNode, 6); //�ͻ���������ַ��Novell�ڵ��ַ��
  swReqConnect.client_major_ver = FSYWGSet.MajorVer;//???? �ͻ���Э��ӿ����汾�ţ����ڰ汾Э�̣�
  swReqConnect.client_minor_ver = FSYWGSet.MinorVer;//???? �ͻ���Э��ӿڴΰ汾�ţ����ڰ汾Э�̣�
  swReqConnect.key_length = 0;// RSA��Կ���ȣ���method 1, key_length=0��

  SWI_ConnectResponse swCnnAns;
  if(FSafeSock.Connect((char *)&swReqConnect, sizeof(SWI_ConnectRequest), (char *)&swCnnAns, sizeof(SWI_ConnectResponse)) != 0)
  {
    ODS("��AGX������������Э�̼��ܣ�ʧ��");
    return -2;
  }

  //Check Response;
  if(swCnnAns.head.block_type != SWI_BT_CN_RESPONSE )// ��Ϣͷ block_type == 7
  {
    ODS("��AGX������������Э�̼��ܣ�ʧ��");
    return -3;
  }

  //��Ϣͷ��
  m_CnID = swCnnAns.head.cn_id;
  //m_LocalDpt = swCnnAns.head.dest_dpt;
  //m_KeyLength = swCnnAns.key_length;

  if(FSYWGSet.UseDesencrypt)
  {
    SWSockClient::DesDecrypt("ExpressT", swCnnAns.des_key, 8);
    //lstrcpyn(m_DesKey, swCnnAns.des_key, 8);
    memcpy(m_DesKey, swCnnAns.des_key, 8);
    m_DesKey[8] = '\0';
    FSafeSock.SetKey(m_DesKey);//
  }

  //Ϊ��ʵ��"Ӧ�ó���汾ͳ��"��������
  //����"���ܺ�0x801"SWI_QueryCommon
  //SWI_BlockHead.cn_id=0
  //     function_id=1
  //     cmd_buf="��Ʒ����|������|�汾��|��������"
  //     ���أ�100�ɹ�  ��=0ʧ��
/*  SWI_QueryCommon swQryComm;
  memset(&swQryComm, 0 ,sizeof(SWI_QueryCommon));
  
  swQryComm.head.block_size = sizeof(SWI_QueryCommon);
  swQryComm.head.cn_id = 0;
  swQryComm.head.block_type = 1;//����
  swQryComm.head.function_no = 0x801;
  swQryComm.function_id = 1;
  sprintf(swQryComm.cmd_buf, ""); //???????

  SWI_QueryCommonReturn swQryResult;
  memset(&swQryResult, 0, sizeof(SWI_QueryCommonReturn));

  if(FSafeSock.Request(&swQryComm, sizeof(SWI_QueryCommon), &swQryResult, sizeof(SWI_QueryCommonReturn)) != 0)
    return -1;

  if(swQryResult.return_status != 100)//���أ�100�ɹ�  ��=0ʧ��
    return -1;
  */
  ODS("����AGX�ɹ�");
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::OpenAccount(char AccountType, char *Account, char *Password)
{
  //Request;
  SWI_OpenAccountRequest swAccReq;
  InitRequest(&swAccReq, sizeof(SWI_OpenAccountRequest), SWI_FUNC_OPEN_ACCOUNT);

  swAccReq.account_type = AccountType;
  lstrcpyn(swAccReq.account, Account, 16);// �ͻ��ʺ�
  lstrcpyn(swAccReq.pwd, Password, 8);// ��������
  //swAccReq.op_code = ;// ����Ա����
  ////////swAccReq.flag = 1;//"��������"�жϱ�־λ���,ÿһ��������λ��Ӧһ��"��������",ȱʡֵΪ0��ʾ���ж��κ�"��������"
  //swAccReq.productno = ;//��Ʒ��Ϣ��ţ�5λ�����������Ĳ�Ʒ����+2λ��

  if(FSafeSock.SendRequest(&swAccReq, sizeof(SWI_OpenAccountRequest)) != 0)
  {
    ODS("����SWI_OpenAccountRequest����ʧ��");
    return -1;
  }

  //Response;
  SWI_OpenAccountReturn swAccAns;
  if(FSafeSock.RecvAnswer(&swAccAns, sizeof(SWI_OpenAccountReturn)) != 0)
  {
    ODS("����SWI_OpenAccountReturnʧ��");
    return -2;
  }

  if(swAccAns.return_status <= 0)//>  0  �ɹ�
  {
    ShowErrorMsg("OpenAccount����ʧ��", swAccAns.return_status);
    return -1;
  }

  m_CnID = swAccAns.head.cn_id;//???��˵��ʱCn_ID����Ч

  NewAns(1);
  memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));

  ODS("���ʽ��ʺţ�%s�ɹ�", Account);
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::QueryEntrust(int StartDate, int EndDate)
{
  //Checked200412302210!!!
  SWI_QueryEntrustRequest swEntrustReq;
  InitRequest(&swEntrustReq, sizeof(SWI_QueryEntrustRequest), SWI_FUNC_QUERY_ENTRUST);

  swEntrustReq.account_type = m_AccType;// �ͻ��ʺ����ͣ��������ֵ�˵����
  lstrcpyn(swEntrustReq.account, FAccInfo.Capital, 16);// �ͻ��ʺ�
  swEntrustReq.exchange_no = GetExchangeNo(bsSH);//// ��������ţ��������ֵ�˵����---????�ٶ�Ϊ�Ͻ���
  swEntrustReq.begin_date = StartDate;// ��ʼ���ڣ����磺yyyymmdd��
  swEntrustReq.end_date = EndDate;// �������ڣ����磺yyyymmdd��
  swEntrustReq.entrust_sn = 0;// ί�б�ţ�0��ʾȫ����
  //swEntrustReq.security_code = ;// ��Ʊ���루�ձ�ʾȫ����
  swEntrustReq.max_results = 0;//����ѯ��¼�� ---- ??? 0��ʾ��ѯ���м�¼

  if(SetRequest(&swEntrustReq, sizeof(SWI_QueryEntrustRequest)) != 0)
    return -1;

  TList *pResult = NULL;
  SWI_QueryEntrustReturn swEntrustAns;
  
  try
  {
    pResult = new TList();
    if(! GetQueryResult(pResult, SWI_FUNC_QUERY_ENTRUST, sizeof(SWI_QueryEntrustResult),  \
                                  &swEntrustAns, sizeof(SWI_QueryEntrustReturn)))//>0 ------ ��ѯ�ɹ�
      return -1;

    if(pResult->Count > 0)//�н��������
    {
      NewAns(pResult->Count);
      TConsignInfo *pConsInfo = NULL;
      SWI_QueryEntrustResult *pRecord = NULL;
      bool bTodayQuery = (StartDate == EndDate == StrToInt(Date().FormatString("yyyymmdd")));

      for(int i=0; i<pResult->Count; i++)
      {
        pConsInfo = bTodayQuery ? (&(*FAnswer)[i].QryCurCsn.CsgInfo) : (&(*FAnswer)[i].QryHisCsn.CsgInfo);
        pRecord = ((SWI_QueryEntrustResult*)(pResult->Items[i]));

        strcpy(pConsInfo->ContractID, IntToStr(pRecord->entrust_sn).c_str());//��ͬ���
        pConsInfo->SecuID[0] = (GetBourse(pRecord->exchange_no) == bsSH) ? 'H' : 'S';
        lstrcpyn(pConsInfo->SecuID+1, pRecord->security_code, 7);//֤ȯ����
        lstrcpyn(pConsInfo->SecuDesc, pRecord->security_account, 11);//֤ȯ����
        pConsInfo->Bourse = GetBourse(pRecord->exchange_no);//������
        lstrcpyn(pConsInfo->Time, pRecord->entrust_time, 9);//ί��ʱ��
        strcpy(pConsInfo->Date, IntToStr(pRecord->entrust_date).c_str());//ί������
        pConsInfo->Type = (pRecord->bs_type == '1') ? 'B' : 'S';//�������
        //pConsInfo->State = ;///???? ����״̬---��θ�ֵ 
        pConsInfo->CsnVol = pRecord->stock_ammount;//ί������
        pConsInfo->TrdVol = pRecord->bargain_ammount;//�ɽ�����

        pConsInfo->CancelVol = 0;
        if(   pRecord->entrust_status == '4'
           || pRecord->entrust_status == '6'
           || (pRecord->entrust_status == '5' && pRecord->bargain_ammount > 0))////'4'---��Чί��,'6'---�ѳ���,'5' ----- ���ֳ���
        {
          pConsInfo->CancelVol = pRecord->bargain_ammount - pRecord->stock_ammount;//��������=��ֵ
        }
        //pConsInfo->CancelVol = (pRecord->entrust_status == '6') ? (pRecord->bargain_ammount - pRecord->stock_ammount) : 0; 

        pConsInfo->CsnPrice = SWISmallMoneyToDouble(pRecord->price);//ί�м۸�
        pConsInfo->TrdPrice = SWISmallMoneyToDouble(pRecord->price);//�ɽ��۸�---???�ṹ����û����Ӧ�ֶ�
      }
    }
  }
  __finally
  {
    ReleaseList(pResult);
  }

  return 0;
}
//---------------------------------------------------------------------------
void TTrdItf_SYWG::ReleaseMemory(char *pMem)
{
  if(pMem != NULL)
  {
    delete [] pMem;
    pMem = NULL;
  }
}
//---------------------------------------------------------------------------
void TTrdItf_SYWG::ReleaseList(TList *pList)
{
  if(pList != NULL)
  {
    char *pRecord = NULL;
    for(int i=0; i<pList->Count; i++)
    {
      pRecord = (char *)pList->Items[i];
      ReleaseMemory(pRecord);
    }
    delete pList;
    pList = NULL;
  }
}
//---------------------------------------------------------------------------
int TTrdItf_SYWG::SetRequest(void *ReqBuf, int ReqSize)
{
  int nRet = FSafeSock.SendRequest(ReqBuf, ReqSize);

  if(nRet == 0)//send request successfully
    return 0;
  else if(nRet == 1)//the connection has been gracefully closed,
  {

    ODS("��������ʧ��,������������ӿ���(���г�ʱ)�ѶϿ���ϵͳ��������������");

    //Connect agx;
    if(LocalInit() != 0)
      return -1;

    //Open account;
    if(OpenAccount(m_AccType, FAccInfo.Capital, FAccInfo.PW) != 0)
      return -1;

    //ODS("��������AGX�ɹ�");
    
    if(FSafeSock.SendRequest(ReqBuf, ReqSize) == 0)
      return 0;
    else
    {
      ODS("��������ʧ��");
      return -1;
    }
  }
  else//socket error
  {
    ODS("socket error����������ʧ��");
    return -1;
  }
}
//---------------------------------------------------------------------------
/*bool TTrdItf_SYWG::CheckStatus(long Status)
{
  if(Rs == rsEqu)
  {
    if(Status == 0)
      return true;
  }
  else if(Rs == rsMoreEqu)
  {
    if(Status >= 0)
      return true;
  }
  else if(Rs == rsMore)
  {
    if(Status > 0)
      return true;
  }

  return false;
}*/
//---------------------------------------------------------------------------
bool TTrdItf_SYWG::GetQueryResult(TList *pList, WORD FunNo, int RecordSize, void *Answer, int AnsSize)
{
  int nRet = 0;
  char *pRecord = NULL;
  int nNewSize = RecordSize >= AnsSize ? RecordSize : AnsSize;
  if(nNewSize <= 0)
    return false;

  try
  {
    for(;;)//ѭ�����ղ�ѯ���
    {
      pRecord = new char[nNewSize];
      nRet = FSafeSock.RecvAnswer(pRecord, nNewSize);
      if(nRet != 0)//��Ϊ֮ǰ�Ѿ�����������Բ����ڳ�ʱ5���ӵ�����
      {
        ReleaseMemory(pRecord);
        return false;
      }

      SWI_QueryResultHead *pHead = (SWI_QueryResultHead*)pRecord;
      if(pHead->head.block_type == SWI_BT_RESULT && pHead->head.function_no == FunNo)//block_type==3 -- ��ѯ�����   SWI_???Result
      {
        if(pHead->row_no != 0xFFFF)//0xFFFF -- ���������(�������������Ч)
        {
          pList->Add(pRecord);
        }
        else
        {
          ReleaseMemory(pRecord);
          continue;
        }
      }
      else if(pHead->head.block_type == SWI_BT_RETURN)//���صı�����¼��SWI_???Return;
      {
        if(pHead->head.function_no == FunNo && ((SWI_QueryReturnHead *)pRecord)->return_status > 0)
        {
          memcpy(Answer, pRecord, AnsSize);
          ReleaseMemory(pRecord);
          return true;
        }
        else
        {
          ReleaseMemory(pRecord);
          return false;
        }
      }
      else//any other errors occurs;
      {
        ReleaseMemory(pRecord);
        return false;
      }
    }

  /*
    //Added 20050109---the following codes are Unreachable;
    //Receive the SWI_???Return;
    nRet = FSafeSock.RecvAnswer(Answer, AnsSize);
    if(nRet == 0)
    {
      if (    ((SWI_QueryReturnHead *)pRecord)->head.block_type == 2
              && ((SWI_QueryReturnHead *)pRecord)->head.function_no == FunNo   \
              && ((SWI_QueryReturnHead *)pRecord)->return_status > 0)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    } */
  }
  catch(...)
  {
    return false;
  }
}

//---------------------------------------------------------------------------
void TTrdItf_SYWG::ShowErrorMsg(char *MsgHead, long ErrorNo)
{
  //Request;
  SWI_ErrorMsgRequest swErrMsgReq;
  InitRequest(&swErrMsgReq, sizeof(SWI_ErrorMsgRequest), SWI_FUNC_ERROR_MSG);

  swErrMsgReq.error_no = ErrorNo;//�������

  String sMsgAdded = "";
  if(FSafeSock.SendRequest(&swErrMsgReq, sizeof(SWI_ErrorMsgRequest)) != 0)
  {
    sMsgAdded.sprintf("return_status=%d(���������Ϣ���ʹ���)", ErrorNo);
    goto OUTPUT_ERR_MSG;
  }
    
  //Response;
  SWI_ErrorMsgReturn swErrMsgAns;
  if(FSafeSock.RecvAnswer(&swErrMsgAns, sizeof(SWI_ErrorMsgReturn)) != 0)
  {
    sMsgAdded.sprintf("return_status=%d(���������Ϣ���ʹ���)", ErrorNo);
    goto OUTPUT_ERR_MSG;
  }
    
  if(swErrMsgAns.return_status > 0)//>  0  �ɹ�
  {
    swErrMsgAns.error_msg[39] = '\0';
    sMsgAdded = (String)swErrMsgAns.error_msg;
  }
  else
    sMsgAdded.sprintf("return_status=%d, SWI_ErrorMsgReturn.return_status=%d(���������Ϣ���ʹ���)", ErrorNo, swErrMsgAns.return_status);

OUTPUT_ERR_MSG:
  sMsgAdded = (String)MsgHead + sMsgAdded;
  ODS(sMsgAdded.c_str());
}
//---------------------------------------------------------------------------

void TTrdItf_SYWG::CloseLink(void)
{
  FSafeSock.Disconnect();
}
