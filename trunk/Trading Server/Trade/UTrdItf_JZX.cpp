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
int TTrdItf_JZX::Init()  //初始化
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

  //新建KCBP实例
  if( KCBPCLI_Init( &FHandle ) != 0 )
  {
    ODS( "KCBPCLI_Init error" );
    return -1;
  }

  //连接KCBP服务器
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
int TTrdItf_JZX::GetStkAccount(char *LogType, char *Logid, char *ZJ, char *SH, char *SZ)//获得主股东账号
{
  char szFunid[] = "410301";
  memset(FKey,0,10);
  strcpy(FKey,szFunid);
  ZeroMemory(FEnPassword, 50);
  if(Encrypt(FAccInfo.PW, FEnPassword) != 0)
    return -1;
        
  if(InitRequest(szFunid, true) != 0)
    return -1;

  KCBPCLI_SetValue(FHandle, "inputtype", LogType);//登录类型	inputtype	char(1)	Y	见备注
  KCBPCLI_SetValue(FHandle, "inputid", Logid);//登录标识	inputid	char(64)	Y	见备注

  int nReturnCode = ExecuteRequest(szFunid);
  if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 全部返回了,=100表示还有数据
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

      ODS("银行代码:%s", FBankCode);

      if(bFlag[0] && bFlag[1])
        break;
    }
  }
  else
    return -1;

  //错误返回结果集是否需要关闭？
  KCBPCLI_SQLCloseCursor(FHandle);

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::SetAccount() //设置帐号
{
  lstrcpyn(FAccInfo.PW, FRequest.SetAccount.PW, 13);//帐号密码

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
    lstrcpyn(FAccInfo.Capital, szZJ, 13);//资金帐号
  }
  else if(FRequest.SetAccount.Sort==asSZ)
  {
    FAccountType = "2";
    lstrcpyn(FAccInfo.SZ, FRequest.SetAccount.Account, 13);

    lstrcpyn(FAccInfo.SH, szSH, 13);
    lstrcpyn(FAccInfo.Capital, szZJ, 13);//资金帐号
  }
  else if(FRequest.SetAccount.Sort == asCA)//资金帐号
  {
    FAccountType = "";
    lstrcpyn(FAccInfo.Capital, FRequest.SetAccount.Account, 13);//资金帐号

    lstrcpyn(FAccInfo.SH, szSH, 13);
    lstrcpyn(FAccInfo.SZ, szSZ, 13);
  }
  else
  {
    ODS("无效的用户帐号类型:%d", FRequest.SetAccount.Sort);
    return -1;
  }

  //ODS("资金账号%s, SH:%s, SZ:%s", FAccInfo.Capital, FAccInfo.SH, FAccInfo.SZ);
  //if (FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) { return -1; } //目前两个市场的帐号缺一不可

  NewAns(1);
  memcpy(&((*FAnswer)[0].SetAccount.AccountInfo),&FAccInfo,sizeof(TAccountInfo));

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::GetTrdInfo()   //取得盘口数据
{
  ODS("GetTrdInfo暂时不用");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryMoney()     //资金查询
{
  char szFunid[] = "410530";

  if(InitRequest(szFunid) != 0)
    return -1;

  KCBPCLI_SetValue(FHandle, "fundid", "-1");//资金账号
  KCBPCLI_SetValue(FHandle, "moneytype", "0"); //0	人民币

  int nReturnCode = ExecuteRequest(szFunid);
  if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 全部返回了,=100表示还有数据
    return -1;

  char szTmpbuf[20];
  if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
  {
    //KCBPCLI_SQLNumResultCols(FHandle, &nCol);
    if( KCBPCLI_RsFetchRow(FHandle) == 0)
    {
      NewAns(1);
      if( KCBPCLI_RsGetColByName( FHandle, "fundbal", szTmpbuf ) == 0)
        (*FAnswer)[0].QryMoney.Balance = StrToFloat(szTmpbuf);//资金余额
      else
        return -1;

      if( KCBPCLI_RsGetColByName( FHandle, "fundavl", szTmpbuf ) == 0)
        (*FAnswer)[0].QryMoney.Available = StrToFloat(szTmpbuf);//
      else
        return -1;

      if( KCBPCLI_RsGetColByName( FHandle, "marketvalue", szTmpbuf ) == 0)
        (*FAnswer)[0].QryMoney.asset_balance = StrToFloat(szTmpbuf);//资金余额
      else
        return -1;
    }
    else
      return -1;
  }
  else
    return -1;

  //错误返回结果集是否需要关闭？
  KCBPCLI_SQLCloseCursor(FHandle);
         
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryStock()     //股份查询
{
  char szFunid[] = "410503";
  if(InitRequest(szFunid) != 0)
    return -1;

  //交易市场		char(1)	N	不送查询全部
  if(FRequest.QryStock.SecuID[0] == 'H')
    KCBPCLI_SetValue(FHandle, "market", QL_MARKET_SH);//沪A
  else if(FRequest.QryStock.SecuID[0] == 'S')
    KCBPCLI_SetValue(FHandle, "market", QL_MARKET_SZ);//深A
  else
    return -1;

  KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//资金帐户		int	N
  KCBPCLI_SetValue(FHandle, "secuid", "");//股东代码		char(10)	N	不送查询全部
  KCBPCLI_SetValue(FHandle, "stkcode", FRequest.QryStock.SecuID+1);//证券代码		char(8)	N	不送查询全部
  KCBPCLI_SetValue(FHandle, "qryflag", "1");//查询方向		char(1) 	Y	向下/向上查询方向,第一次查询送1
  KCBPCLI_SetValue(FHandle, "count", "1");//请求行数		int 	Y	每次取的行数
  KCBPCLI_SetValue(FHandle, "poststr", "");//定位串  		char(32)	Y	第一次填空

  int nReturnCode = ExecuteRequest(szFunid);
  if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 全部返回了,=100表示还有数据
    return -1;

  char szTmpbuf[20];
  if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
  {
    if( KCBPCLI_RsFetchRow(FHandle) == 0)
    {
      NewAns(1);
      
      if( KCBPCLI_RsGetColByName( FHandle, "stkbal", szTmpbuf ) == 0)
        (*FAnswer)[0].QryStock.Balance = StrToInt(szTmpbuf);//股票余额
      else
        return -1;

      if( KCBPCLI_RsGetColByName( FHandle, "stkavl", szTmpbuf ) == 0)
        (*FAnswer)[0].QryStock.Available = StrToInt(szTmpbuf);//可用余额
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

  //错误返回结果集是否需要关闭？
  KCBPCLI_SQLCloseCursor(FHandle);
    
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryCanBuy()    //取可买数量
{
  // 暂时不用
  ODS("QryCanBuy暂时不用");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryDetail()    //成交查询
{
  char szFunid[] = "410510";
  if(FRequest.QryDetail.ContractID[0]==0)
  {
    ODS("委托号有误：%s",FRequest.QryDetail.ContractID);
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

  KCBPCLI_SetValue(FHandle, "market", (FRequest.QryDetail.Bourse==bsSH?QL_MARKET_SH:QL_MARKET_SZ));//交易市场		char(1)	N	不送查询全部
  KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//资金帐户		int	N
  KCBPCLI_SetValue(FHandle, "secuid", "");//sStkAcc.c_str());//股东代码		char(10)	N	不送查询全部
  KCBPCLI_SetValue(FHandle, "stkcode", "");//证券代码		char(8)	N	不送查询全部
  KCBPCLI_SetValue(FHandle, "ordersno", FRequest.QryDetail.ContractID);//委托序号	Ordersno	int	N	不送查询全部
  KCBPCLI_SetValue(FHandle, "bankcode", FBankCode);//外部银行	Bankcode	char(4)	N	三方交易时送
  KCBPCLI_SetValue(FHandle, "qryflag", "1");//查询方向		char(1) 	Y	向下/向上查询方向,第一次查询送1
  KCBPCLI_SetValue(FHandle, "count", "1");//请求行数		int 	Y	每次取的行数
  KCBPCLI_SetValue(FHandle, "poststr", "");//定位串  		char(32)	Y	第一次填空

  int nReturnCode = ExecuteRequest(szFunid);
  if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 全部返回了,=100表示还有数据
  {
    ODS("执行请求错误：%d",nReturnCode);
    return -1;
  }
  
  char szTmpbuf[20];
  if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
  {
    if( KCBPCLI_RsFetchRow(FHandle) == 0)
    {
      NewAns(1);

      if( KCBPCLI_RsGetColByName( FHandle, "matchqty", szTmpbuf ) == 0)
        (*FAnswer)[0].QryDetail.Num = StrToInt(szTmpbuf);//成交数量	matchqty	int
      else
        return -1;

      if( KCBPCLI_RsGetColByName( FHandle, "matchamt", szTmpbuf ) == 0)//成交金额	matchamt	numeric(15,2)
        (*FAnswer)[0].QryDetail.Price = ((*FAnswer)[0].QryDetail.Num > 0 ? StrToFloat(szTmpbuf)/(*FAnswer)[0].QryDetail.Num : 0);
      else
        return -1;
        
      if( KCBPCLI_RsGetColByName( FHandle, "cancelqty", szTmpbuf ) == 0)
        (*FAnswer)[0].QryDetail.UndoNum = -StrToInt(szTmpbuf);//撤单数量	cancelqty	int
      else
        return -1;
    }
    else
      return -1;
  }
  else
    return -1;

  //错误返回结果集是否需要关闭？
  KCBPCLI_SQLCloseCursor(FHandle);
    
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryHisDetail() //历史成交查询
{
  //暂时不用
  ODS("QryHisDetail暂时不用");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryCsn()       //查询某个委托合同
{
  //暂时不用
  ODS("QryCsn暂时不用");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryCurCsn()    //当日委托查询
{
  char szFunid[] = "410510";
  //if(InitRequest(szFunid) != 0)
  //  return -1;
    
  String sPoststr = "";
  int nReturnCode = -1;//-1表示第一次进入循环
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

    //qryflag实际应该一直送1，文档有误
    KCBPCLI_SetValue(FHandle, "market", "");//FAccountType.c_str());//交易市场		char(1)	N	不送查询全部
    KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//资金帐户		int	N
    KCBPCLI_SetValue(FHandle, "secuid", sStkAcc.c_str());//sStkAcc.c_str());//股东代码		char(10)	N	不送查询全部
    KCBPCLI_SetValue(FHandle, "stkcode", "");//证券代码		char(8)	N	不送查询全部
    KCBPCLI_SetValue(FHandle, "ordersno", "");//委托序号	Ordersno	int	N	不送查询全部
    KCBPCLI_SetValue(FHandle, "bankcode", FBankCode);//外部银行	Bankcode	char(4)	N	三方交易时送
    KCBPCLI_SetValue(FHandle, "qryflag", "1");//(nReturnCode==-1?"1":"0"));//查询方向		char(1) 	Y	向下/向上查询方向,第一次查询送1
    KCBPCLI_SetValue(FHandle, "count", JZX_MAX_REC_NUM);//请求行数		int 	Y	每次取的行数
    KCBPCLI_SetValue(FHandle, "poststr", sPoststr.c_str());//定位串  		char(32)	Y	第一次填空

    nReturnCode = ExecuteRequest(szFunid);//返回0也可能是多结果集，文档上没有提及啊
    if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 全部返回了,=100表示还有数据
      return -1;
    
    int nReturnRow = QueryMoreResults(FSrcList, FDstList);
    ODS("QryCurCsn nReturnRow = %d", nReturnRow);

    if(nReturnRow == 0)
      break;
    else if(nReturnRow < 0)
      return -1;
    else if(nReturnRow < JZX_MAX_REC_NUM_INT && nReturnCode != 100)//金正那边文档实在值得怀疑，还是安全一点吧
      break;


    if(FDstList->Count > 0)
      sPoststr = FDstList->Strings[FDstList->Count - 1];
    
    //错误返回结果集是否需要关闭？
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
      
      strcpy(pConsInfo->ContractID, FDstList->Strings[i*nFieldCount].Trim().c_str());//合同序号
      pConsInfo->SecuID[0] = (FDstList->Strings[i*nFieldCount+3].Trim() == "1") ? 'H' : 'S';
      lstrcpyn(pConsInfo->SecuID+1, FDstList->Strings[i*nFieldCount+1].Trim().c_str(), 7);//证券代码
      lstrcpyn(pConsInfo->SecuDesc, FDstList->Strings[i*nFieldCount+2].Trim().c_str(), 9);//证券名称
      pConsInfo->Bourse = (FDstList->Strings[i*nFieldCount+3].Trim() == "1") ? bsSH : bsSZ;//交易所
      lstrcpyn(pConsInfo->Time, FDstList->Strings[i*nFieldCount+4].Trim().c_str(), 9);//委托时间
      strcpy(pConsInfo->Date, FDstList->Strings[i*nFieldCount+5].Trim().c_str());//委托日期
      pConsInfo->Type = ConvertType(FDstList->Strings[i*nFieldCount+6].Trim().c_str());//买卖类别
      pConsInfo->State = ConvertState(FDstList->Strings[i*nFieldCount+7].Trim().c_str());///撤单状态---如何赋值 
      pConsInfo->CsnVol = StrToInt(FDstList->Strings[i*nFieldCount+8].Trim());//委托数量
      pConsInfo->TrdVol = StrToInt(FDstList->Strings[i*nFieldCount+9].Trim());//成交数量
      pConsInfo->CancelVol = -StrToInt(FDstList->Strings[i*nFieldCount+10].Trim());//撤单数量=负值
      pConsInfo->CsnPrice = StrToFloat(FDstList->Strings[i*nFieldCount+11].Trim());//委托价格
      pConsInfo->TrdPrice = (pConsInfo->TrdVol >0 ? StrToFloat(FDstList->Strings[i*nFieldCount+12].Trim())/pConsInfo->TrdVol : 0);//成交价格---???结构体中没有相应字段
    }
  }
  
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryHisCsn()    //历史委托查询
{
  ODS("QryHisCsn暂时不用");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryCurTrd()    //当日成交查询
{
  char szFunid[] = "410512";
  //if(InitRequest(szFunid) != 0)
  //  return -1;

  int machtype;
  String sPoststr = "";
  int nReturnCode = -1;//-1表示第一次进入循环
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

    KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//资金帐户		int	N
    KCBPCLI_SetValue(FHandle, "market", "");//FAccountType.c_str());//交易市场		char(1)	N	不送查询全部
    KCBPCLI_SetValue(FHandle, "secuid", "");//sStkAcc.c_str());//股东代码		char(10)	N	不送查询全部
    KCBPCLI_SetValue(FHandle, "stkcode", "");//证券代码		char(8)	N	不送查询全部
    KCBPCLI_SetValue(FHandle, "ordersno", "");//委托序号	Ordersno	int	N	不送查询全部
    KCBPCLI_SetValue(FHandle, "bankcode", FBankCode);//外部银行	Bankcode	char(4)	N	三方交易时送
    KCBPCLI_SetValue(FHandle, "qryflag", "1");//(nReturnCode==-1?"1":"0"));//查询方向		char(1) 	Y	向下/向上查询方向,第一次查询送1
    KCBPCLI_SetValue(FHandle, "count", JZX_MAX_REC_NUM);//请求行数		int 	Y	每次取的行数
    KCBPCLI_SetValue(FHandle, "poststr", sPoststr.c_str());//定位串  		char(32)	Y	第一次填空

    nReturnCode = ExecuteRequest(szFunid);
    if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 全部返回了,=100表示还有数据
      return -1;
    
    int nReturnRow = QueryMoreResults(FSrcList, FDstList);
    if(nReturnRow == 0)
      break;
    else if(nReturnRow < 0)
      return -1;
    else if(nReturnRow < JZX_MAX_REC_NUM_INT && nReturnCode != 100)//金正那边文档实在值得怀疑，还是安全一点吧
      break;


    if(FDstList->Count > 0)
      sPoststr = FDstList->Strings[FDstList->Count - 1];
    
    //错误返回结果集是否需要关闭？
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
      lstrcpyn(pTrdInfo->SecuID+1, FDstList->Strings[i*nFieldCount+1].Trim().c_str(), 7);//证券代码
      lstrcpyn(pTrdInfo->SecuDesc, FDstList->Strings[i*nFieldCount+2].Trim().c_str(), 9) ; //证券名称

      lstrcpyn(pTrdInfo->Time, FDstList->Strings[i*nFieldCount+3].Trim().c_str(), 9);//成交时间
      lstrcpyn(pTrdInfo->Date, FDstList->Strings[i*nFieldCount+4].Trim().c_str(), 9);//委托日期
      pTrdInfo->Type = ConvertType(FDstList->Strings[i*nFieldCount+5].Trim().c_str());//买卖类别
      pTrdInfo->Vol = StrToInt(FDstList->Strings[i*nFieldCount+6].Trim());//成交数量
      pTrdInfo->Price = StrToFloat(FDstList->Strings[i*nFieldCount+7].Trim());//成交价格
      machtype = StrToIntDef(FDstList->Strings[i*nFieldCount+9].Trim(),-1) ;
      if( machtype != 0 )
        pTrdInfo->Vol = -pTrdInfo->Vol;
    }
  }
  
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryHisTrd()    //历史成交查询
{
  ODS("QryHisTrd暂时不用");
  return -1;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryBill()      //查询资金流水（对帐单）
{
  ODS("QryBill暂时不用");
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::QryStocks()    //查询帐号中所有的股份
{
  char szFunid[] = "410503";
  //if(InitRequest(szFunid) != 0)
  //  return -1;

  String sPoststr = "";
  int nReturnCode = -1;//-1表示第一次进入循环
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

    KCBPCLI_SetValue(FHandle, "market", sMarket.c_str());//FAccountType.c_str());//交易市场	market	char(1)	N	不送查询全部
    KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//资金帐户		int	N
    KCBPCLI_SetValue(FHandle, "secuid", sStkAcc.c_str());//sStkAcc.c_str());//股东代码		char(10)	N	不送查询全部
    KCBPCLI_SetValue(FHandle, "stkcode", "");//证券代码		char(8)	N	不送查询全部
    KCBPCLI_SetValue(FHandle, "qryflag", "1");//(nReturnCode==-1?"1":"0"));//查询方向		char(1) 	Y	向下/向上查询方向,第一次查询送1
    KCBPCLI_SetValue(FHandle, "count", JZX_MAX_REC_NUM);//请求行数		int 	Y	每次取的行数
    KCBPCLI_SetValue(FHandle, "poststr", sPoststr.c_str());//定位串  		char(32)	Y	第一次填空

    nReturnCode = ExecuteRequest(szFunid);
    if( nReturnCode != 0 && nReturnCode != 100 ){ //nReturnCode = 0 全部返回了,=100表示还有数据
      return -1;
    }

    int nReturnRow = QueryMoreResults(FSrcList, FDstList);
    if(nReturnRow == 0)
      break;
    else if(nReturnRow < 0) {
      return -1;
    }
    else if(nReturnRow < JZX_MAX_REC_NUM_INT && nReturnCode != 100)//金正那边文档实在值得怀疑，还是安全一点吧
      break;


    if(FDstList->Count > 0)
      sPoststr = FDstList->Strings[FDstList->Count - 1];
    
    //错误返回结果集是否需要关闭？
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
      lstrcpyn(pStock->SecuID+1, FDstList->Strings[i*nFieldCount+1].Trim().c_str(), 7);//证券代码
      lstrcpyn(pStock->SecuDesc, FDstList->Strings[i*nFieldCount+2].Trim().c_str(), 9);    //证券名称
      pStock->Balance = StrToIntDef(FDstList->Strings[i*nFieldCount+3].Trim(), 0);//余额
      pStock->Available = StrToIntDef(FDstList->Strings[i*nFieldCount+4].Trim(), 0);//可用数
      int stkqty = StrToIntDef(FDstList->Strings[i*nFieldCount+8].Trim(), 0); //当前拥股数
      pStock->BuyFreeze = 0;//买入冻结
      pStock->BuyFreeze = stkqty - pStock->Available;//买入冻结
      pStock->SellFreeze = 0;//卖出冻结
      pStock->AbnorFreeze = 0 ;//异常冻结
      pStock->AbnorFreeze = StrToIntDef(FDstList->Strings[i*nFieldCount+9].Trim(), 0);//可申赎数量

      pStock->Cost = StrToFloatDef(FDstList->Strings[i*nFieldCount+5].Trim(), 0);//参考成本
      pStock->CostPrice = StrToFloatDef(FDstList->Strings[i*nFieldCount+6].Trim(), 0);//参考成本价
      pStock->CurVal = StrToFloatDef(FDstList->Strings[i*nFieldCount+7].Trim(), 0);//参考市值
      pStock->CurPrice = 0;//参考市价
      pStock->ProfitAndLoss = 0;//参考盈亏
    }  
  }
    
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::Undo() //委托撤单
{
  char szFunid[] = "410413";
  if(InitRequest(szFunid) != 0)
    return -1;

  KCBPCLI_SetValue(FHandle, "orderdate", FOrderDate.c_str());//委托日期	orderdate	int	Y
  KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//资金账户	fundid	int	Y
  KCBPCLI_SetValue(FHandle, "ordersno", FRequest.Undo.ContractID);//委托序号	ordersno	int	Y	委托返回的

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

  //错误返回结果集是否需要关闭？
  KCBPCLI_SQLCloseCursor(FHandle);

  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::Buy()
{
  //B:买入,S:卖出,3基金申购,4基金赎回
  String sBsType = "B";
  if(FRequest.Buy.Type == 1)
    sBsType = "1";//文档上为3，实际应为1，真是可恶

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
  //B:买入,S:卖出,3基金申购,4基金赎回
  String sBsType = "S";
  if(FRequest.Sell.Type == 1)
    sBsType = "2";//文档上为4，实际应为2，

  int nOrderID = 0;
  if(Order(sBsType.c_str(), FRequest.Sell.SecuID, FRequest.Sell.Num, FRequest.Sell.Price, nOrderID) != 0)
    return -1;

  NewAns(1);
  strcpy((*FAnswer)[0].Sell.ContractID, IntToStr(nOrderID).c_str());
    
  return 0;
}
//---------------------------------------------------------------------------
int TTrdItf_JZX::Order(char *BsType, char *SecuID, int Num, double Price, int &OrderNo) //委托
{
  //注：如果用资金账号登陆则要获取其上证及深证股东账号，否则买卖股票可能出错！
  char szFunid[] = "410411";
  if(InitRequest(szFunid) != 0)
    return -1;

  //交易市场	market	char(1)	Y
  if(SecuID[0] == 'H')
  {
    KCBPCLI_SetValue(FHandle, "market", QL_MARKET_SH);//沪A
    KCBPCLI_SetValue(FHandle, "secuid", FAccInfo.SH);//股东代码	secuid	char(10)	Y
  }
  else if(SecuID[0] == 'S')
  {
    KCBPCLI_SetValue(FHandle, "market", QL_MARKET_SZ);//深A
    KCBPCLI_SetValue(FHandle, "secuid", FAccInfo.SZ);//股东代码	secuid	char(10)	Y
  }
  else
    return -1;

  String sPrice = FormatFloat("0.000", Price+0.0002);
  KCBPCLI_SetValue(FHandle, "fundid", FAccInfo.Capital);//资金账户	fundid	int	Y
  KCBPCLI_SetValue(FHandle, "stkcode", SecuID+1);//证券代码	stkcode	char(8)	Y
  KCBPCLI_SetValue(FHandle, "bsflag", BsType);//买卖类别	bsflag	char(1)	Y	B:买入S:卖出
  KCBPCLI_SetValue(FHandle, "price", sPrice.c_str());//价格	price	numeric(9,3)	Y
  KCBPCLI_SetValue(FHandle, "qty", IntToStr(Num).c_str());//数量	qty	int	Y
  KCBPCLI_SetValue(FHandle, "ordergroup", "-1"/*"0"*/);//委托批号	ordergroup	int	Y	0,
  KCBPCLI_SetValue(FHandle, "bankcode", FBankCode);//外部银行	bankcode	char(4)	N	三方交易时送
  KCBPCLI_SetValue(FHandle, "remark", "");//备注信息	remark	char(64)	N

  int nReturnCode = ExecuteRequest(szFunid);
  if( nReturnCode != 0) 
    return -1;

  char szTmpbuf[20];
  if( KCBPCLI_SQLMoreResults(FHandle) == 0 )
  {
    if( KCBPCLI_RsFetchRow(FHandle) == 0)
    {
      NewAns(1);
      
      if( KCBPCLI_RsGetColByName( FHandle, "ordersno", szTmpbuf ) == 0) //委托序号	ordersno	int	返回给股民
        OrderNo = StrToInt(szTmpbuf);//股票余额
      else
        return -1;
    }
    else
      return -1;
  }
  else
    return -1;

  //错误返回结果集是否需要关闭？
  KCBPCLI_SQLCloseCursor(FHandle);  

  return 0;
}
//---------------------------------------------------------------------------

int TTrdItf_JZX::SetSytemParams(char *Funid, bool IsLogin)
{
  int nReturnCode = KCBPCLI_SetSystemParam(FHandle, KCBP_PARAM_RESERVED, FGTJASet.DptCode);//必须设置营业部代码
  if(nReturnCode != 0)   
  {
    ODS("KCBPCLI_SetSystemParam ErrCode=%d", nReturnCode);
    return -1;
  }

  if(!IsLogin)
  {
    KCBPCLI_SetValue(FHandle, "funcid", Funid);//功能号, 必须送,不可以为空
    KCBPCLI_SetValue(FHandle, "custid", FCustid);//客户代码,  可以为空119353,517486
    KCBPCLI_SetValue(FHandle, "custorgid", FGTJASet.DptCode);//客户机构, 可以为空
    KCBPCLI_SetValue(FHandle, "trdpwd", FEnPassword);//交易密码, 可以为空
    KCBPCLI_SetValue(FHandle, "netaddr", "");//FGTJASet.ServerAddr);//操作站点, 必须送，不可以为空
    KCBPCLI_SetValue(FHandle, "orgid", FGTJASet.DptCode);//操作机构, 必须送，不可以为空
    KCBPCLI_SetValue(FHandle, "operway", String(FGTJASet.Operway).c_str());//操作方式, 必须送，不可以为空
    KCBPCLI_SetValue(FHandle, "ext", "");//扩展字段, 必须送，可以为空
  }
  else
  {
    KCBPCLI_SetValue(FHandle, "funcid", Funid);//功能号, 必须送,不可以为空
    KCBPCLI_SetValue(FHandle, "custid", "");//客户代码,  可以为空 28014444,8237964
    KCBPCLI_SetValue(FHandle, "custorgid", "");//客户机构, 可以为空
    KCBPCLI_SetValue(FHandle, "trdpwd", FEnPassword);//交易密码, 可以为空
    KCBPCLI_SetValue(FHandle, "netaddr", "");//FGTJASet.ServerAddr);//操作站点, 必须送，不可以为空
    KCBPCLI_SetValue(FHandle, "orgid", FGTJASet.DptCode);//操作机构, 必须送，不可以为空
    KCBPCLI_SetValue(FHandle, "operway", String(FGTJASet.Operway).c_str()/*"0"*/);//操作方式, 必须送，不可以为空
    KCBPCLI_SetValue(FHandle, "ext", "");//扩展字段, 必须送，可以为空
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
  /*初始化传入参数缓冲区*/
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
  /*客户端向服务器提交请求*/
  int nReturnCode  = KCBPCLI_SQLExecute(FHandle, Funid);//
  if( nReturnCode != 0 ) 
  {
    ODS("SqlExecute Program ErrCode=%d", nReturnCode );
    return -1;
  }

  if(CheckSqlExecute() != 0)
    return -1;

  nReturnCode = KCBPCLI_RsOpen(FHandle);
  if( nReturnCode != 0 && nReturnCode != 100 ) //nReturnCode = 0 全部返回了,=100表示还有数据
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

