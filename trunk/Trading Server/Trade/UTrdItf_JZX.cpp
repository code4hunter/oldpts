//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <SysUtils.hpp>
#include "UTrdItf_JZX.h"
#include "KDEncodeCli.h"
#pragma package(smart_init)

//typedef char * (* DOGSKIN_ENCODE)(const char *);
///
//1,KCBPCLI_SQLNumResultCols
//2,CancelVol<=0
//3,KCBPCLI_GetErr
//---------------------------------------------------------------------------
TTrdItf_JZX::TTrdItf_JZX(TJZXSet *pSet)
{
  CopyMemory(&FGTJASet, pSet, sizeof(TJZXSet));
  FHandle = NULL;
  FOrderDate = "";
  FAccountType = "";
  FSrcList = new TStringList();
  FDstList = new TStringList();
  ZeroMemory(FEnPassword, 50);
  ZeroMemory(FCustid, 50);
  ZeroMemory(FBankCode,5);
}
//---------------------------------------------------------------------------
TTrdItf_JZX::~TTrdItf_JZX()
{
  CloseLink();

  delete FSrcList;
  delete FDstList;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::Init()  //��ʼ��
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

  CloseLink();

  //�½�KCBPʵ��
  if( KCBPCLI_Init( &FHandle ) != 0 )
  {
    ODS( "KCBPCLI_Init error" );
    return -1;
  }

  //����KCBP������
  if( KCBPCLI_SetConnectOption( FHandle, stKCBPConnection ) != 0)
  {
    KCBPCLI_Exit( FHandle );
    FHandle=NULL;
    ODS( "KCBPCLI_SetConnectOption error" );
    return -1;
  }

  if( KCBPCLI_SetCliTimeOut( FHandle, FGTJASet.Timeout ) != 0)
  {
    KCBPCLI_Exit( FHandle );
    FHandle=NULL;
    ODS( "KCBPCLI_SetCliTimeOut error" );
    return -1;
  }

  int nReturnCode = KCBPCLI_SQLConnect( FHandle, stKCBPConnection.szServerName, FGTJASet.UserName, FGTJASet.Password); 
  if(nReturnCode)
  {
    KCBPCLI_Exit( FHandle );
    FHandle=NULL;
    ODS("Sqlconnect return code %d", nReturnCode);
    return -1;
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::GetStkAccount(char *LogType, char *Logid, char *ZJ, char *SH, char *SZ)//������ɶ��˺�
{
  char szFunid[] = "410301";
  memset(FKey,0,10);
  strcpy(FKey,szFunid);
  ZeroMemory(FEnPassword, 50);
  if(Encrypt(FAccInfo.PW, FEnPassword) != 0)
    return -1;
        
  if(InitRequest(szFunid, true) != 0)
    return -1;

  KCBPCLI_SetValue(FHandle, "inputtype", LogType);//��¼����	inputtype	char(1)	Y	����ע
  KCBPCLI_SetValue(FHandle, "inputid", Logid);//��¼��ʶ	inputid	char(64)	Y	����ע

  int nReturnCode = ExecuteRequest(szFunid);
  if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
    return -1;

  char szTmpbuf[20];
  if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
  {		
    //KCBPCLI_SQLNumResultCols(FHandle, &nCol);
    bool bFlag[2] = {false, false};
    while( !KCBPCLI_RsFetchRow(FHandle) )
    {
      if( KCBPCLI_RsGetColByName( FHandle, "market", szTmpbuf ) == 0)
      {
        if(lstrcmpi(szTmpbuf, QL_MARKET_SH) == 0 && !bFlag[0])
        {
          bFlag[0] = true;
          if( KCBPCLI_RsGetColByName( FHandle, "secuid", SH) != 0)
            return -1;
        }
        else if(lstrcmpi(szTmpbuf, QL_MARKET_SZ) == 0 && !bFlag[1])
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

      ODS("���д���:%s", FBankCode);

      if(bFlag[0] && bFlag[1])
        break;
    }
  }
  else
    return -1;

  //���󷵻ؽ�����Ƿ���Ҫ�رգ�
  KCBPCLI_SQLCloseCursor(FHandle);

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::SetAccount() //�����ʺ�
{
  lstrcpyn(FAccInfo.PW, FRequest.SetAccount.PW, 13);//�ʺ�����

  char szSH[20] = {0x0, };
  char szSZ[20] = {0x0, };
  char szZJ[20] = {0x0, };
  String sLogType = "Z", sLogid = FRequest.SetAccount.Account;
  if(FRequest.SetAccount.Sort != asCA)
  {
    sLogType = "N";
    if(strlen(FRequest.SetAccount.Account) > 0 && !isdigit(FRequest.SetAccount.Account[0]))
      sLogid = FRequest.SetAccount.Account+1;
  }

  if(GetStkAccount(sLogType.c_str(), sLogid.c_str(), szZJ, szSH, szSZ) != 0)
    return -1;

  memset(FKey,0,50);
  strcpy(FKey,FCustid);
  ZeroMemory(FEnPassword, 50);
  if(Encrypt(FAccInfo.PW, FEnPassword) != 0)
    return -1;

  if(FRequest.SetAccount.Sort==asSH)
  {
    FAccountType = "1";
    lstrcpyn(FAccInfo.SH, FRequest.SetAccount.Account, 13);

    lstrcpyn(FAccInfo.SZ, szSZ, 13);
    lstrcpyn(FAccInfo.Capital, szZJ, 13);//�ʽ��ʺ�
  }
  else if(FRequest.SetAccount.Sort==asSZ)
  {
    FAccountType = "2";
    lstrcpyn(FAccInfo.SZ, FRequest.SetAccount.Account, 13);

    lstrcpyn(FAccInfo.SH, szSH, 13);
    lstrcpyn(FAccInfo.Capital, szZJ, 13);//�ʽ��ʺ�
  }
  else if(FRequest.SetAccount.Sort == asCA)//�ʽ��ʺ�
  {
    FAccountType = "";
    lstrcpyn(FAccInfo.Capital, FRequest.SetAccount.Account, 13);//�ʽ��ʺ�

    lstrcpyn(FAccInfo.SH, szSH, 13);
    lstrcpyn(FAccInfo.SZ, szSZ, 13);
  }
  else
  {
    ODS("��Ч���û��ʺ�����:%d", FRequest.SetAccount.Sort);
    return -1;
  }

  //ODS("�ʽ��˺�%s, SH:%s, SZ:%s", FAccInfo.Capital, FAccInfo.SH, FAccInfo.SZ);
  //if (FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) { return -1; } //Ŀǰ�����г����ʺ�ȱһ����

  NewAns(1);
  memcpy(&((*FAnswer)[0].SetAccount.AccountInfo),&FAccInfo,sizeof(TAccountInfo));

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::GetTrdInfo()   //ȡ���̿�����
{
  ODS("GetTrdInfo��ʱ����");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryMoney()     //�ʽ��ѯ
{
  char szFunid[] = "410530";

  if(InitRequest(szFunid) != 0)
    return -1;

  KCBPCLI_SetValue(FHandle, "fundid", "-1");//�ʽ��˺�
  KCBPCLI_SetValue(FHandle, "moneytype", "0"); //0	�����

  int nReturnCode = ExecuteRequest(szFunid);
  if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
    return -1;

  char szTmpbuf[20];
  if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
  {
    //KCBPCLI_SQLNumResultCols(FHandle, &nCol);
    if( KCBPCLI_RsFetchRow(FHandle) == 0)
    {
      NewAns(1);
      if( KCBPCLI_RsGetColByName( FHandle, "fundbal", szTmpbuf ) == 0)
        (*FAnswer)[0].QryMoney.Balance = StrToFloat(szTmpbuf);//�ʽ����
      else
        return -1;

      if( KCBPCLI_RsGetColByName( FHandle, "fundavl", szTmpbuf ) == 0)
        (*FAnswer)[0].QryMoney.Available = StrToFloat(szTmpbuf);//
      else
        return -1;

      if( KCBPCLI_RsGetColByName( FHandle, "marketvalue", szTmpbuf ) == 0)
        (*FAnswer)[0].QryMoney.asset_balance = StrToFloat(szTmpbuf);//�ʽ����
      else
        return -1;
    }
    else
      return -1;
  }
  else
    return -1;

  //���󷵻ؽ�����Ƿ���Ҫ�رգ�
  KCBPCLI_SQLCloseCursor(FHandle);
         
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryStock()     //�ɷݲ�ѯ
{
  char szFunid[] = "410503";
  if(InitRequest(szFunid) != 0)
    return -1;

  //�����г�		char(1)	N	���Ͳ�ѯȫ��
  if(FRequest.QryStock.SecuID[0] == 'H')
    KCBPCLI_SetValue(FHandle, "market", QL_MARKET_SH);//��A
  else if(FRequest.QryStock.SecuID[0] == 'S')
    KCBPCLI_SetValue(FHandle, "market", QL_MARKET_SZ);//��A
  else
    return -1;

  KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//�ʽ��ʻ�		int	N
  KCBPCLI_SetValue(FHandle, "secuid", "");//�ɶ�����		char(10)	N	���Ͳ�ѯȫ��
  KCBPCLI_SetValue(FHandle, "stkcode", FRequest.QryStock.SecuID+1);//֤ȯ����		char(8)	N	���Ͳ�ѯȫ��
  KCBPCLI_SetValue(FHandle, "qryflag", "1");//��ѯ����		char(1) 	Y	����/���ϲ�ѯ����,��һ�β�ѯ��1
  KCBPCLI_SetValue(FHandle, "count", "1");//��������		int 	Y	ÿ��ȡ������
  KCBPCLI_SetValue(FHandle, "poststr", "");//��λ��  		char(32)	Y	��һ�����

  int nReturnCode = ExecuteRequest(szFunid);
  if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
    return -1;

  char szTmpbuf[20];
  if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
  {
    if( KCBPCLI_RsFetchRow(FHandle) == 0)
    {
      NewAns(1);
      
      if( KCBPCLI_RsGetColByName( FHandle, "stkbal", szTmpbuf ) == 0)
        (*FAnswer)[0].QryStock.Balance = StrToInt(szTmpbuf);//��Ʊ���
      else
        return -1;

      if( KCBPCLI_RsGetColByName( FHandle, "stkavl", szTmpbuf ) == 0)
        (*FAnswer)[0].QryStock.Available = StrToInt(szTmpbuf);//�������
      else
        return -1;

      (*FAnswer)[0].QryStock.BuyFreeze = 0;
      (*FAnswer)[0].QryStock.SellFreeze = 0;
    }
    else
      return -1;
  }
  else
    return -1;

  //���󷵻ؽ�����Ƿ���Ҫ�رգ�
  KCBPCLI_SQLCloseCursor(FHandle);
    
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryCanBuy()    //ȡ��������
{
  // ��ʱ����
  ODS("QryCanBuy��ʱ����");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryDetail()    //�ɽ���ѯ
{
  char szFunid[] = "410510";
  if(FRequest.QryDetail.ContractID[0]==0)
  {
    ODS("ί�к�����%s",FRequest.QryDetail.ContractID);
    return -1;
  }

  if(InitRequest(szFunid) != 0)
    return -1;

  String sStkAcc = "";
  if(FAccountType == "1")
    sStkAcc = FAccInfo.SH;
  else if(FAccountType == "2")
    sStkAcc = FAccInfo.SZ;
  else
    sStkAcc = "";

  KCBPCLI_SetValue(FHandle, "market", (FRequest.QryDetail.Bourse==bsSH?QL_MARKET_SH:QL_MARKET_SZ));//�����г�		char(1)	N	���Ͳ�ѯȫ��
  KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//�ʽ��ʻ�		int	N
  KCBPCLI_SetValue(FHandle, "secuid", "");//sStkAcc.c_str());//�ɶ�����		char(10)	N	���Ͳ�ѯȫ��
  KCBPCLI_SetValue(FHandle, "stkcode", "");//֤ȯ����		char(8)	N	���Ͳ�ѯȫ��
  KCBPCLI_SetValue(FHandle, "ordersno", FRequest.QryDetail.ContractID);//ί�����	Ordersno	int	N	���Ͳ�ѯȫ��
  KCBPCLI_SetValue(FHandle, "bankcode", FBankCode);//�ⲿ����	Bankcode	char(4)	N	��������ʱ��
  KCBPCLI_SetValue(FHandle, "qryflag", "1");//��ѯ����		char(1) 	Y	����/���ϲ�ѯ����,��һ�β�ѯ��1
  KCBPCLI_SetValue(FHandle, "count", "1");//��������		int 	Y	ÿ��ȡ������
  KCBPCLI_SetValue(FHandle, "poststr", "");//��λ��  		char(32)	Y	��һ�����

  int nReturnCode = ExecuteRequest(szFunid);
  if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
  {
    ODS("ִ���������%d",nReturnCode);
    return -1;
  }
  
  char szTmpbuf[20];
  if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
  {
    if( KCBPCLI_RsFetchRow(FHandle) == 0)
    {
      NewAns(1);

      if( KCBPCLI_RsGetColByName( FHandle, "matchqty", szTmpbuf ) == 0)
        (*FAnswer)[0].QryDetail.Num = StrToInt(szTmpbuf);//�ɽ�����	matchqty	int
      else
        return -1;

      if( KCBPCLI_RsGetColByName( FHandle, "matchamt", szTmpbuf ) == 0)//�ɽ����	matchamt	numeric(15,2)
        (*FAnswer)[0].QryDetail.Price = ((*FAnswer)[0].QryDetail.Num > 0 ? StrToFloat(szTmpbuf)/(*FAnswer)[0].QryDetail.Num : 0);
      else
        return -1;
        
      if( KCBPCLI_RsGetColByName( FHandle, "cancelqty", szTmpbuf ) == 0)
        (*FAnswer)[0].QryDetail.UndoNum = -StrToInt(szTmpbuf);//��������	cancelqty	int
      else
        return -1;
    }
    else
      return -1;
  }
  else
    return -1;

  //���󷵻ؽ�����Ƿ���Ҫ�رգ�
  KCBPCLI_SQLCloseCursor(FHandle);
    
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryHisDetail() //��ʷ�ɽ���ѯ
{
  //��ʱ����
  ODS("QryHisDetail��ʱ����");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryCsn()       //��ѯĳ��ί�к�ͬ
{
  //��ʱ����
  ODS("QryCsn��ʱ����");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryCurCsn()    //����ί�в�ѯ
{
  char szFunid[] = "410510";
  //if(InitRequest(szFunid) != 0)
  //  return -1;
    
  String sPoststr = "";
  int nReturnCode = -1;//-1��ʾ��һ�ν���ѭ��
  FSrcList->Clear();
  FDstList->Clear();
  const int nFieldCount = 14;
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
  FSrcList->Add("poststr");

  String sStkAcc = "";
  if(FAccountType == "1")
    sStkAcc = FAccInfo.SH;
  else if(FAccountType == "2")
    sStkAcc = FAccInfo.SZ;
  else
    sStkAcc = "";

  while(nReturnCode == -1 || nReturnCode == 100 || nReturnCode == 0)
  {
    if(InitRequest(szFunid) != 0)
      return -1;

    //qryflagʵ��Ӧ��һֱ��1���ĵ�����
    KCBPCLI_SetValue(FHandle, "market", "");//FAccountType.c_str());//�����г�		char(1)	N	���Ͳ�ѯȫ��
    KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//�ʽ��ʻ�		int	N
    KCBPCLI_SetValue(FHandle, "secuid", sStkAcc.c_str());//sStkAcc.c_str());//�ɶ�����		char(10)	N	���Ͳ�ѯȫ��
    KCBPCLI_SetValue(FHandle, "stkcode", "");//֤ȯ����		char(8)	N	���Ͳ�ѯȫ��
    KCBPCLI_SetValue(FHandle, "ordersno", "");//ί�����	Ordersno	int	N	���Ͳ�ѯȫ��
    KCBPCLI_SetValue(FHandle, "bankcode", FBankCode);//�ⲿ����	Bankcode	char(4)	N	��������ʱ��
    KCBPCLI_SetValue(FHandle, "qryflag", "1");//(nReturnCode==-1?"1":"0"));//��ѯ����		char(1) 	Y	����/���ϲ�ѯ����,��һ�β�ѯ��1
    KCBPCLI_SetValue(FHandle, "count", JZX_MAX_REC_NUM);//��������		int 	Y	ÿ��ȡ������
    KCBPCLI_SetValue(FHandle, "poststr", sPoststr.c_str());//��λ��  		char(32)	Y	��һ�����

    nReturnCode = ExecuteRequest(szFunid);//����0Ҳ�����Ƕ��������ĵ���û���ἰ��
    if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
      return -1;
    
    int nReturnRow = QueryMoreResults(FSrcList, FDstList);
    ODS("QryCurCsn nReturnRow = %d", nReturnRow);

    if(nReturnRow == 0)
      break;
    else if(nReturnRow < 0)
      return -1;
    else if(nReturnRow < JZX_MAX_REC_NUM_INT && nReturnCode != 100)//�����Ǳ��ĵ�ʵ��ֵ�û��ɣ����ǰ�ȫһ���
      break;


    if(FDstList->Count > 0)
      sPoststr = FDstList->Strings[FDstList->Count - 1];
    
    //���󷵻ؽ�����Ƿ���Ҫ�رգ�
    KCBPCLI_SQLCloseCursor(FHandle);
  }

  if(FDstList->Count >= nFieldCount)
  {
    int nRows = FDstList->Count/nFieldCount;
    NewAns(nRows);

    //set value;
    for(int i=0; i<nRows; i++)
    {
      TConsignInfo *pConsInfo = &((*FAnswer)[i].QryCurCsn.CsgInfo);
      
      strcpy(pConsInfo->ContractID, FDstList->Strings[i*nFieldCount].Trim().c_str());//��ͬ���
      pConsInfo->SecuID[0] = (FDstList->Strings[i*nFieldCount+3].Trim() == "1") ? 'H' : 'S';
      lstrcpyn(pConsInfo->SecuID+1, FDstList->Strings[i*nFieldCount+1].Trim().c_str(), 7);//֤ȯ����
      lstrcpyn(pConsInfo->SecuDesc, FDstList->Strings[i*nFieldCount+2].Trim().c_str(), 9);//֤ȯ����
      pConsInfo->Bourse = (FDstList->Strings[i*nFieldCount+3].Trim() == "1") ? bsSH : bsSZ;//������
      lstrcpyn(pConsInfo->Time, FDstList->Strings[i*nFieldCount+4].Trim().c_str(), 9);//ί��ʱ��
      strcpy(pConsInfo->Date, FDstList->Strings[i*nFieldCount+5].Trim().c_str());//ί������
      pConsInfo->Type = ConvertType(FDstList->Strings[i*nFieldCount+6].Trim().c_str());//�������
      pConsInfo->State = ConvertState(FDstList->Strings[i*nFieldCount+7].Trim().c_str());///����״̬---��θ�ֵ 
      pConsInfo->CsnVol = StrToInt(FDstList->Strings[i*nFieldCount+8].Trim());//ί������
      pConsInfo->TrdVol = StrToInt(FDstList->Strings[i*nFieldCount+9].Trim());//�ɽ�����
      pConsInfo->CancelVol = -StrToInt(FDstList->Strings[i*nFieldCount+10].Trim());//��������=��ֵ
      pConsInfo->CsnPrice = StrToFloat(FDstList->Strings[i*nFieldCount+11].Trim());//ί�м۸�
      pConsInfo->TrdPrice = (pConsInfo->TrdVol >0 ? StrToFloat(FDstList->Strings[i*nFieldCount+12].Trim())/pConsInfo->TrdVol : 0);//�ɽ��۸�---???�ṹ����û����Ӧ�ֶ�
    }
  }
  
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryHisCsn()    //��ʷί�в�ѯ
{
  ODS("QryHisCsn��ʱ����");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryCurTrd()    //���ճɽ���ѯ
{
  char szFunid[] = "410512";
  //if(InitRequest(szFunid) != 0)
  //  return -1;

  int machtype;
  String sPoststr = "";
  int nReturnCode = -1;//-1��ʾ��һ�ν���ѭ��
  FSrcList->Clear();
  FDstList->Clear();
  const int nFieldCount = 9;

  FSrcList->Add("market");
  FSrcList->Add("stkcode");
  FSrcList->Add("stkname");
  FSrcList->Add("matchtime");
  FSrcList->Add("trddate");
  FSrcList->Add("bsflag");
  FSrcList->Add("matchqty");
  FSrcList->Add("matchprice");
  FSrcList->Add("poststr");

  String sStkAcc = "";
  if(FAccountType == "1")
    sStkAcc = FAccInfo.SH;
  else if(FAccountType == "2")
    sStkAcc = FAccInfo.SZ;
  else
    sStkAcc = "";

  while(nReturnCode == -1 || nReturnCode == 100 || nReturnCode == 0)
  {
    if(InitRequest(szFunid) != 0)
      return -1;

    KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//�ʽ��ʻ�		int	N
    KCBPCLI_SetValue(FHandle, "market", "");//FAccountType.c_str());//�����г�		char(1)	N	���Ͳ�ѯȫ��
    KCBPCLI_SetValue(FHandle, "secuid", "");//sStkAcc.c_str());//�ɶ�����		char(10)	N	���Ͳ�ѯȫ��
    KCBPCLI_SetValue(FHandle, "stkcode", "");//֤ȯ����		char(8)	N	���Ͳ�ѯȫ��
    KCBPCLI_SetValue(FHandle, "ordersno", "");//ί�����	Ordersno	int	N	���Ͳ�ѯȫ��
    KCBPCLI_SetValue(FHandle, "bankcode", FBankCode);//�ⲿ����	Bankcode	char(4)	N	��������ʱ��
    KCBPCLI_SetValue(FHandle, "qryflag", "1");//(nReturnCode==-1?"1":"0"));//��ѯ����		char(1) 	Y	����/���ϲ�ѯ����,��һ�β�ѯ��1
    KCBPCLI_SetValue(FHandle, "count", JZX_MAX_REC_NUM);//��������		int 	Y	ÿ��ȡ������
    KCBPCLI_SetValue(FHandle, "poststr", sPoststr.c_str());//��λ��  		char(32)	Y	��һ�����

    nReturnCode = ExecuteRequest(szFunid);
    if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
      return -1;
    
    int nReturnRow = QueryMoreResults(FSrcList, FDstList);
    if(nReturnRow == 0)
      break;
    else if(nReturnRow < 0)
      return -1;
    else if(nReturnRow < JZX_MAX_REC_NUM_INT && nReturnCode != 100)//�����Ǳ��ĵ�ʵ��ֵ�û��ɣ����ǰ�ȫһ���
      break;


    if(FDstList->Count > 0)
      sPoststr = FDstList->Strings[FDstList->Count - 1];
    
    //���󷵻ؽ�����Ƿ���Ҫ�رգ�
    KCBPCLI_SQLCloseCursor(FHandle);
  }

  if(FDstList->Count >= nFieldCount)
  {
    int nRows = FDstList->Count/nFieldCount;
    NewAns(nRows);

    //set value;
    for(int i=0; i<nRows; i++)
    {
      TTradeInfo *pTrdInfo = &((*FAnswer)[i].QryCurTrd.TrdInfo);

      pTrdInfo->SecuID[0] = (FDstList->Strings[i*nFieldCount].Trim() == "1") ? 'H' : 'S';
      lstrcpyn(pTrdInfo->SecuID+1, FDstList->Strings[i*nFieldCount+1].Trim().c_str(), 7);//֤ȯ����
      lstrcpyn(pTrdInfo->SecuDesc, FDstList->Strings[i*nFieldCount+2].Trim().c_str(), 9) ; //֤ȯ����

      lstrcpyn(pTrdInfo->Time, FDstList->Strings[i*nFieldCount+3].Trim().c_str(), 9);//�ɽ�ʱ��
      lstrcpyn(pTrdInfo->Date, FDstList->Strings[i*nFieldCount+4].Trim().c_str(), 9);//ί������
      pTrdInfo->Type = ConvertType(FDstList->Strings[i*nFieldCount+5].Trim().c_str());//�������
      pTrdInfo->Vol = StrToInt(FDstList->Strings[i*nFieldCount+6].Trim());//�ɽ�����
      pTrdInfo->Price = StrToFloat(FDstList->Strings[i*nFieldCount+7].Trim());//�ɽ��۸�
      machtype = StrToIntDef(FDstList->Strings[i*nFieldCount+9].Trim(),-1) ;
      if( machtype != 0 )
        pTrdInfo->Vol = -pTrdInfo->Vol;
    }
  }
  
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryHisTrd()    //��ʷ�ɽ���ѯ
{
  ODS("QryHisTrd��ʱ����");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryBill()      //��ѯ�ʽ���ˮ�����ʵ���
{
  ODS("QryBill��ʱ����");
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryStocks()    //��ѯ�ʺ������еĹɷ�
{
  char szFunid[] = "410503";
  //if(InitRequest(szFunid) != 0)
  //  return -1;

  String sPoststr = "";
  int nReturnCode = -1;//-1��ʾ��һ�ν���ѭ��
  FSrcList->Clear();
  FDstList->Clear();
  const int nFieldCount = 11;
  FSrcList->Add("market");
  FSrcList->Add("stkcode");
  FSrcList->Add("stkname");
  FSrcList->Add("stkbal");
  FSrcList->Add("stkavl");
  FSrcList->Add("buycost");
  FSrcList->Add("costprice");
  FSrcList->Add("mktval");
  FSrcList->Add("stkqty");
  FSrcList->Add("stkdiff");
  FSrcList->Add("poststr");

  String sStkAcc = "";   //(FRequest.QryStocks.Bourse==bsSH ? FAccInfo.SH : FAccInfo.SZ
  /*if(FAccountType == "1")
    sStkAcc = FAccInfo.SH;
  else if(FAccountType == "2")
    sStkAcc = FAccInfo.SZ;
  else
    sStkAcc = "";*/
  String sMarket = "";
  if(FRequest.QryStocks.Bourse == bsSH)
  {
    sStkAcc = FAccInfo.SH;
    sMarket = QL_MARKET_SH ;
  }
  else if(FRequest.QryStocks.Bourse==bsSZ)
  {
    sStkAcc = FAccInfo.SZ;
    sMarket = QL_MARKET_SZ;
  }
  else
    sStkAcc = "";

  while(nReturnCode == -1 || nReturnCode == 100 || nReturnCode == 0)
  {
    if(InitRequest(szFunid) != 0){
      return -1;
    }

    KCBPCLI_SetValue(FHandle, "market", sMarket.c_str());//FAccountType.c_str());//�����г�	market	char(1)	N	���Ͳ�ѯȫ��
    KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//�ʽ��ʻ�		int	N
    KCBPCLI_SetValue(FHandle, "secuid", sStkAcc.c_str());//sStkAcc.c_str());//�ɶ�����		char(10)	N	���Ͳ�ѯȫ��
    KCBPCLI_SetValue(FHandle, "stkcode", "");//֤ȯ����		char(8)	N	���Ͳ�ѯȫ��
    KCBPCLI_SetValue(FHandle, "qryflag", "1");//(nReturnCode==-1?"1":"0"));//��ѯ����		char(1) 	Y	����/���ϲ�ѯ����,��һ�β�ѯ��1
    KCBPCLI_SetValue(FHandle, "count", JZX_MAX_REC_NUM);//��������		int 	Y	ÿ��ȡ������
    KCBPCLI_SetValue(FHandle, "poststr", sPoststr.c_str());//��λ��  		char(32)	Y	��һ�����

    nReturnCode = ExecuteRequest(szFunid);
    if( nReturnCode != 0 && nReturnCode != 100 ){ //nReturnCode = 0 ȫ��������,=100��ʾ��������
      return -1;
    }

    int nReturnRow = QueryMoreResults(FSrcList, FDstList);
    if(nReturnRow == 0)
      break;
    else if(nReturnRow < 0) {
      return -1;
    }
    else if(nReturnRow < JZX_MAX_REC_NUM_INT && nReturnCode != 100)//�����Ǳ��ĵ�ʵ��ֵ�û��ɣ����ǰ�ȫһ���
      break;


    if(FDstList->Count > 0)
      sPoststr = FDstList->Strings[FDstList->Count - 1];
    
    //���󷵻ؽ�����Ƿ���Ҫ�رգ�
    KCBPCLI_SQLCloseCursor(FHandle);
  }

  if(FDstList->Count >= nFieldCount)
  {
    int nRows = FDstList->Count/nFieldCount;
    NewAns(nRows);
    //set value;
    for(int i=0; i<nRows; i++)
    {
      TStockInfo *pStock = &((*FAnswer)[i].QryStocks.StockInfo);
      
      pStock->SecuID[0] = (FDstList->Strings[i*nFieldCount].Trim() == "1") ? 'H' : 'S';
      lstrcpyn(pStock->SecuID+1, FDstList->Strings[i*nFieldCount+1].Trim().c_str(), 7);//֤ȯ����
      lstrcpyn(pStock->SecuDesc, FDstList->Strings[i*nFieldCount+2].Trim().c_str(), 9);    //֤ȯ����
      pStock->Balance = StrToIntDef(FDstList->Strings[i*nFieldCount+3].Trim(), 0);//���
      pStock->Available = StrToIntDef(FDstList->Strings[i*nFieldCount+4].Trim(), 0);//������
      int stkqty = StrToIntDef(FDstList->Strings[i*nFieldCount+8].Trim(), 0); //��ǰӵ����
      pStock->BuyFreeze = 0;//���붳��
      pStock->BuyFreeze = stkqty - pStock->Available;//���붳��
      pStock->SellFreeze = 0;//��������
      pStock->AbnorFreeze = 0 ;//�쳣����
      pStock->AbnorFreeze = StrToIntDef(FDstList->Strings[i*nFieldCount+9].Trim(), 0);//����������

      pStock->Cost = StrToFloatDef(FDstList->Strings[i*nFieldCount+5].Trim(), 0);//�ο��ɱ�
      pStock->CostPrice = StrToFloatDef(FDstList->Strings[i*nFieldCount+6].Trim(), 0);//�ο��ɱ���
      pStock->CurVal = StrToFloatDef(FDstList->Strings[i*nFieldCount+7].Trim(), 0);//�ο���ֵ
      pStock->CurPrice = 0;//�ο��м�
      pStock->ProfitAndLoss = 0;//�ο�ӯ��
    }  
  }
    
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::Undo() //ί�г���
{
  char szFunid[] = "410413";
  if(InitRequest(szFunid) != 0)
    return -1;

  KCBPCLI_SetValue(FHandle, "orderdate", FOrderDate.c_str());//ί������	orderdate	int	Y
  KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//�ʽ��˻�	fundid	int	Y
  KCBPCLI_SetValue(FHandle, "ordersno", FRequest.Undo.ContractID);//ί�����	ordersno	int	Y	ί�з��ص�

  int nReturnCode = ExecuteRequest(szFunid);
  if( nReturnCode != 0) 
    return -1;

  char szTmpbuf[20];
  if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
  {
    if( KCBPCLI_RsFetchRow(FHandle) != 0)
      return -1;
  }
  else
    return -1;

  //���󷵻ؽ�����Ƿ���Ҫ�رգ�
  KCBPCLI_SQLCloseCursor(FHandle);

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::Buy()
{
  //B:����,S:����,3�����깺,4�������
  String sBsType = "B";
  if(FRequest.Buy.Type == 1)
    sBsType = "1";//�ĵ���Ϊ3��ʵ��ӦΪ1�����ǿɶ�

  int nOrderID = 0;
  if(Order(sBsType.c_str(), FRequest.Buy.SecuID, FRequest.Buy.Num, FRequest.Buy.Price, nOrderID) != 0)
    return -1;

  NewAns(1);
  strcpy((*FAnswer)[0].Buy.ContractID, IntToStr(nOrderID).c_str());

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::Sell()
{
  //B:����,S:����,3�����깺,4�������
  String sBsType = "S";
  if(FRequest.Sell.Type == 1)
    sBsType = "2";//�ĵ���Ϊ4��ʵ��ӦΪ2��

  int nOrderID = 0;
  if(Order(sBsType.c_str(), FRequest.Sell.SecuID, FRequest.Sell.Num, FRequest.Sell.Price, nOrderID) != 0)
    return -1;

  NewAns(1);
  strcpy((*FAnswer)[0].Sell.ContractID, IntToStr(nOrderID).c_str());
    
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::Order(char *BsType, char *SecuID, int Num, double Price, int &OrderNo) //ί��
{
  //ע��������ʽ��˺ŵ�½��Ҫ��ȡ����֤����֤�ɶ��˺ţ�����������Ʊ���ܳ���
  char szFunid[] = "410411";
  if(InitRequest(szFunid) != 0)
    return -1;

  //�����г�	market	char(1)	Y
  if(SecuID[0] == 'H')
  {
    KCBPCLI_SetValue(FHandle, "market", QL_MARKET_SH);//��A
    KCBPCLI_SetValue(FHandle, "secuid", FAccInfo.SH);//�ɶ�����	secuid	char(10)	Y
  }
  else if(SecuID[0] == 'S')
  {
    KCBPCLI_SetValue(FHandle, "market", QL_MARKET_SZ);//��A
    KCBPCLI_SetValue(FHandle, "secuid", FAccInfo.SZ);//�ɶ�����	secuid	char(10)	Y
  }
  else
    return -1;

  String sPrice = FormatFloat("0.000", Price+0.0002);
  KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//�ʽ��˻�	fundid	int	Y
  KCBPCLI_SetValue(FHandle, "stkcode", SecuID+1);//֤ȯ����	stkcode	char(8)	Y
  KCBPCLI_SetValue(FHandle, "bsflag", BsType);//�������	bsflag	char(1)	Y	B:����S:����
  KCBPCLI_SetValue(FHandle, "price", sPrice.c_str());//�۸�	price	numeric(9,3)	Y
  KCBPCLI_SetValue(FHandle, "qty", IntToStr(Num).c_str());//����	qty	int	Y
  KCBPCLI_SetValue(FHandle, "ordergroup", "-1"/*"0"*/);//ί������	ordergroup	int	Y	0,
  KCBPCLI_SetValue(FHandle, "bankcode", FBankCode);//�ⲿ����	bankcode	char(4)	N	��������ʱ��
  KCBPCLI_SetValue(FHandle, "remark", "");//��ע��Ϣ	remark	char(64)	N

  int nReturnCode = ExecuteRequest(szFunid);
  if( nReturnCode != 0) 
    return -1;

  char szTmpbuf[20];
  if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
  {
    if( KCBPCLI_RsFetchRow(FHandle) == 0)
    {
      NewAns(1);
      
      if( KCBPCLI_RsGetColByName( FHandle, "ordersno", szTmpbuf ) == 0) //ί�����	ordersno	int	���ظ�����
        OrderNo = StrToInt(szTmpbuf);//��Ʊ���
      else
        return -1;
    }
    else
      return -1;
  }
  else
    return -1;

  //���󷵻ؽ�����Ƿ���Ҫ�رգ�
  KCBPCLI_SQLCloseCursor(FHandle);  

  return 0;
}
//---------------------------------------------------------------------------

int TTrdItf_JZX::SetSytemParams(char *Funid, bool IsLogin)
{
  int nReturnCode = KCBPCLI_SetSystemParam(FHandle, KCBP_PARAM_RESERVED, FGTJASet.DptCode);//��������Ӫҵ������
  if(nReturnCode != 0)   
  {
    ODS("KCBPCLI_SetSystemParam ErrCode=%d", nReturnCode);
    return -1;
  }

  if(!IsLogin)
  {
    KCBPCLI_SetValue(FHandle, "funcid", Funid);//���ܺ�, ������,������Ϊ��
    KCBPCLI_SetValue(FHandle, "custid", FCustid);//�ͻ�����,  ����Ϊ��119353,517486
    KCBPCLI_SetValue(FHandle, "custorgid", FGTJASet.DptCode);//�ͻ�����, ����Ϊ��
    KCBPCLI_SetValue(FHandle, "trdpwd", FEnPassword);//��������, ����Ϊ��
    KCBPCLI_SetValue(FHandle, "netaddr", "");//FGTJASet.ServerAddr);//����վ��, �����ͣ�������Ϊ��
    KCBPCLI_SetValue(FHandle, "orgid", FGTJASet.DptCode);//��������, �����ͣ�������Ϊ��
    KCBPCLI_SetValue(FHandle, "operway", String(FGTJASet.Operway).c_str());//������ʽ, �����ͣ�������Ϊ��
    KCBPCLI_SetValue(FHandle, "ext", "");//��չ�ֶ�, �����ͣ�����Ϊ��
  }
  else
  {
    KCBPCLI_SetValue(FHandle, "funcid", Funid);//���ܺ�, ������,������Ϊ��
    KCBPCLI_SetValue(FHandle, "custid", "");//�ͻ�����,  ����Ϊ�� 28014444,8237964
    KCBPCLI_SetValue(FHandle, "custorgid", "");//�ͻ�����, ����Ϊ��
    KCBPCLI_SetValue(FHandle, "trdpwd", FEnPassword);//��������, ����Ϊ��
    KCBPCLI_SetValue(FHandle, "netaddr", "");//FGTJASet.ServerAddr);//����վ��, �����ͣ�������Ϊ��
    KCBPCLI_SetValue(FHandle, "orgid", FGTJASet.DptCode);//��������, �����ͣ�������Ϊ��
    KCBPCLI_SetValue(FHandle, "operway", String(FGTJASet.Operway).c_str()/*"0"*/);//������ʽ, �����ͣ�������Ϊ��
    KCBPCLI_SetValue(FHandle, "ext", "");//��չ�ֶ�, �����ͣ�����Ϊ��
  }
      
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::CheckSqlExecute(void)
{
  int nErrCode = 0;
  char szErrMsg[256];

  if(KCBPCLI_GetErr(FHandle, &nErrCode, szErrMsg) == 0)
  {
    if(nErrCode != 0)
    {
      szErrMsg[255] = '\0';
      ODS("ErrCode:%d, ErrMsg:%s", nErrCode, szErrMsg );
      lstrcpyn(this->FLastError.Sender,"JZX",9);
      this->FLastError.ErrorCode = nErrCode;
      lstrcpyn(this->FLastError.Text,szErrMsg,MAX_TEXT);
      return -1;
    }
  }

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::CheckRsOpen(void)
{
  int nCol = 0;
  KCBPCLI_SQLNumResultCols(FHandle, &nCol); ///////////////
  if(KCBPCLI_SQLFetch(FHandle) != 0)
  {
    ODS( "KCBPCLI_SQLFetch error!" );
    return -1;
  }

  char szTmpbuf[1024];
  if( KCBPCLI_RsGetColByName( FHandle, "CODE", szTmpbuf ) != 0)
  {
    ODS( "Get CODE Fail\n" );
    return -1;
  }
		
  if( strcmp(szTmpbuf, "0") != 0 )
  {
    String sErrMsg = "";
    sErrMsg.cat_printf( "error code :%s ", szTmpbuf );
    KCBPCLI_RsGetColByName( FHandle, "LEVEL", szTmpbuf );
    sErrMsg.cat_printf( "error level :%s ", szTmpbuf );
    KCBPCLI_RsGetColByName( FHandle, "MSG", szTmpbuf );
    sErrMsg.cat_printf( "error msg :%s\n", szTmpbuf );
    lstrcpyn(this->FLastError.Sender,"JZX",9);
    this->FLastError.ErrorCode = -100;
    lstrcpyn(this->FLastError.Text,sErrMsg.c_str(),MAX_TEXT);
    ODS(sErrMsg.c_str());

    return -1;
  }
  
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::InitRequest(char *Funid, bool IsLogin)
{
  /*��ʼ���������������*/
  int nReturnCode = KCBPCLI_BeginWrite(FHandle);
  if( nReturnCode !=0 ) 
  {
    ODS("KCBPCLI_BeginWrite ErrCode=%d", nReturnCode);
    return -1;
  }

  if(SetSytemParams(Funid, IsLogin) != 0)
    return -1;

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::ExecuteRequest(char *Funid)
{
  /*�ͻ�����������ύ����*/
  int nReturnCode  = KCBPCLI_SQLExecute(FHandle, Funid);//
  if( nReturnCode != 0 ) 
  {
    ODS("SqlExecute Program ErrCode=%d", nReturnCode );
    return -1;
  }

  if(CheckSqlExecute() != 0)
    return -1;

  nReturnCode = KCBPCLI_RsOpen(FHandle);
  if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 ȫ��������,=100��ʾ��������
  {
    ODS("KCBPCLI_RsOpen ErrCode=%d", nReturnCode);
    return -1;
  }

  if(CheckRsOpen() != 0)
    return -1;

  return nReturnCode;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QueryMoreResults(TStrings *pSrcList, TStrings *pDstList)
{
  int nRows = 0, nCol = 0;;
  char szTmpbuf[100] = {0x0, };
  if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
  {
    KCBPCLI_SQLNumResultCols(FHandle, &nCol);
    while( !KCBPCLI_RsFetchRow(FHandle) )
    {
      for(int i=0; i<pSrcList->Count; i++ )
      {
        if(KCBPCLI_RsGetColByName( FHandle, pSrcList->Strings[i].c_str(), szTmpbuf ) == 0)
          pDstList->Add(szTmpbuf);
        else{
          return -1;//pDstList->Add("");
        }
      }
      nRows++;
    }
  }
    
  return nRows;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::Encrypt(char *pSrc, char *pDst)
{
  typedef int (*TKDEncode)(int nEncode_Level,
			  unsigned char *pSrcData, int nSrcDataLen, 
			  unsigned char *pDestData, int nDestDataBufLen, 
			  void *pKey, int nKeyLen);

  HMODULE hDll = NULL;

  hDll = LoadLibrary("KDEncodeCli.dll");
  if(!hDll)
  {
    ODS(" no LoadLibrary KDEncodeCli.dll!!");
    return -1;
  }
  TKDEncode EncodeFun = (TKDEncode)GetProcAddress(hDll, "KDEncode");
  if(!EncodeFun)
  {
    FreeLibrary(hDll);
    ODS( "Not get the address of the KDEncode function!!!" );
    return -1;
  }

  EncodeFun(KDCOMPLEX_ENCODE,
			  pSrc, strlen(pSrc),
			  pDst, 50,
			  FKey,strlen(FKey));
        //FRequest.SetAccount.Account, strlen(FRequest.SetAccount.Account)

  FreeLibrary(hDll);



  return 0;
}
//---------------------------------------------------------------------------

void TTrdItf_JZX::CloseLink(void)
{
  if(FHandle != NULL)
  {
    KCBPCLI_SQLDisconnect( FHandle);
    KCBPCLI_Exit( FHandle );
    FHandle = NULL;
  }
  TTrdItfBase::CloseLink();
}

