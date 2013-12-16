/*
 *  DESC: 顶点中间件内部接口
 *  FILE: UTrdItf_DD
 *  BY:   CodeHunter
 */
 
//---------------------------------------------------------------------------
#include <SysUtils.hpp>

#include "UTrdItf_DD.h"
//---------------------------------------------------------------------------
#define jtsh  "SH"
#define jtsz  "SZ"
#define mtrmb "RMB"
#define mtusd "USD"
#define mthkd "HKD"
#define ERR_OTHERS               -103
#define ERR_UNIMPLEMENTED        -200  //未处理

static LONG link_count=0;
void TTrdItf_DD::YYYYMMDD2DingDian(char *s,char *d,char sp)
{
  char buf[11];
  int n=strlen(s);
  if (n==0)
  {
      d[0]=0;
      return;
  }

  for(int i=0,j=0;i<n;i++)
  {
    if(i==4|| i==6)
    {
      buf[j++]=sp;
    }

    buf[j++]=s[i];
  }
  buf[10]=0;
  strcpy(d,buf);
}

void TTrdItf_DD::DingDian2YYYYMMDD(char *s,char *d,char sp)
{
  int n=strlen(s);
  for(int i=0,j=0;i<n;i++)
  {
    if(s[i]!=sp)
    {
      d[j++]=s[i];
    }
  }
}

char TTrdItf_DD::DDTypeToType(char* dd_type)
{
  switch(atoi(dd_type))
  {
      case 1:
        return 'B';
      case -1:
        return 'B';
      case -2:
        return 'S';
      case 2:
        return 'S';
      default: return 'N';
  }
}

void TTrdItf_DD::ShowErr(void)
{
  if(FCot)
  {
    char buf[255];
    int ecode=FDll.GetLastErrMsg(FCot,buf);
    ODS("ErrCode=%d,Error Message:%s",ecode,buf);
  }
}

TTrdItf_DD::TTrdItf_DD(TDDSet & set)
{
  memcpy(&FSet,&set,sizeof(set));
  FCot=NULL;
}

TTrdItf_DD::~TTrdItf_DD()
{
  if(FCot!=NULL) FDll.ApexCloseLink(FCot);

  //link_count--;
  InterlockedDecrement(&link_count);
  if(link_count==0) FDll.Apex3rdExit();
}

int  TTrdItf_DD::Init()
{
  //假如是第一个连接
  if(link_count==0)
  {
    if(!FDll.Apex3rdInit(FSet.pUser,FSet.pWtfs,FSet.pYyb,FSet.pRight))
    {
      ShowErr();
      return -1;
    }
  }

  InterlockedIncrement(&link_count);
  //link_count++;

  if(FCot!=NULL)
  {
    FDll.ApexCloseLink(FCot);
    FCot=NULL;
  }

  FCot = FDll.ApexOpenLink( FSet.pDest,FSet.pRemote );
  if ( FCot ) return 0;
  else
  {
    ShowErr();
    return -2;
  }
}

int  TTrdItf_DD::SetAccount()
{
  char buffer[256],*pOut;
  int nIndex,nCount;
  char jys[8],bz[8],gdzh[16];

  //ZERO FAccInfo
  ZeroMemory(&FAccInfo,sizeof(FAccInfo));
  lstrcpyn(FAccInfo.PW,FRequest.SetAccount.PW,13);

  if(FRequest.SetAccount.Sort==asCA)
  {
    if(FDll.check_zjzh(FRequest.SetAccount.Account,
                       FRequest.SetAccount.PW,
                       FCot)>0)
    {
      lstrcpyn(FAccInfo.Capital,FRequest.SetAccount.Account,13);
      //取得股东代码
      nCount = FDll.read_gdzh(FRequest.SetAccount.Account,"",&pOut,FCot );
      if ( nCount > 0 )
      {
        //有nCount个股东号
        for ( nIndex = 0; nIndex < nCount; nIndex ++ )
        {
          if(FAccInfo.SH[0]!='\0' && FAccInfo.SZ[0]!='\0') break;

          FDll.QAGetRow( pOut,nIndex+1,buffer,sizeof(buffer) );
          FDll.QAGetString( buffer,1,gdzh,0 );
          FDll.QAGetString( buffer,2,jys,0 );
          FDll.QAGetString( buffer,3,bz,0 );
          if(strcmpi(bz,mtrmb)==0)  //is RMB
          {
            if(strlen(FAccInfo.SH)==0 &&
               strcmpi(jys,jtsh)==0 ) // is 上海
            {
              lstrcpyn(FAccInfo.SH,gdzh,13);
            }
            else if(strlen(FAccInfo.SZ)==0 &&
                    strcmpi(jys,jtsz)==0 ) //is 深圳
            {
              lstrcpyn(FAccInfo.SZ,gdzh,13);
            }
          }
        }
      }
    }
    else
    {
      ShowErr();
    }
  }
  else if(FRequest.SetAccount.Sort==asSH)
  {
    if(FDll.check_gdzh(FRequest.SetAccount.Account,
                       jtsh,
                       FRequest.SetAccount.PW,
                       FCot)>0)
    {
      lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,13);
      //取资金账号
      FDll.GetLastErrMsg( FCot,buffer );
      FDll.QAGetString( buffer,1,FAccInfo.Capital,sizeof(FAccInfo.Capital));
      //取得股东代码
      nCount = FDll.read_gdzh(FAccInfo.Capital,jtsz,&pOut,FCot );
      if ( nCount > 0 )
      {
        //有nCount个股东号
        for ( nIndex = 0; nIndex < nCount; nIndex ++ )
        {
          FDll.QAGetRow( pOut,nIndex+1,buffer,sizeof(buffer) );
          FDll.QAGetString( buffer,1,gdzh,0 );
          FDll.QAGetString( buffer,2,jys,0 );
          FDll.QAGetString( buffer,3,bz,0 );
          if(strcmpi(bz,mtrmb)==0)  //is RMB
          {
            if( strcmpi(jys,jtsz)==0 ) //is 深圳
            {
              lstrcpyn(FAccInfo.SZ,gdzh,13);
              break;
            }
          }
        }
      }
    }
    else
    {
      ShowErr();
    }
  }
  else if(FRequest.SetAccount.Sort==asSZ)
  {
    if(FDll.check_gdzh(FRequest.SetAccount.Account,
                       jtsz,
                       FRequest.SetAccount.PW,
                       FCot)>0)
    {
      lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,13);
      //取资金账号
      FDll.GetLastErrMsg( FCot,buffer );
      FDll.QAGetString( buffer,1,FAccInfo.Capital,sizeof(FAccInfo.Capital));
      //取得股东代码
      nCount = FDll.read_gdzh(FAccInfo.Capital,jtsh,&pOut,FCot );
      if ( nCount > 0 )
      {
        //有nCount个股东号
        for ( nIndex = 0; nIndex < nCount; nIndex ++ )
        {
          FDll.QAGetRow( pOut,nIndex+1,buffer,sizeof(buffer) );
          FDll.QAGetString( buffer,1,gdzh,0 );
          FDll.QAGetString( buffer,2,jys,0 );
          FDll.QAGetString( buffer,3,bz,0 );
          if(strcmpi(bz,mtrmb)==0)  //is RMB
          {
            if( strcmpi(jys,jtsh)==0) //is 上海
            {
              lstrcpyn(FAccInfo.SH,gdzh,13);
              break;
            }
          }
        }
      }
    }
    else
    {
      ShowErr();
    }
  }

  if(FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) { return -1; } 

  NewAns(1);
  memcpy(&((*FAnswer)[0].SetAccount.AccountInfo),&FAccInfo,sizeof(TAccountInfo));
  return 0;
}

//////查询函数//////
int  TTrdItf_DD::GetTrdInfo()
{
  return ERR_UNIMPLEMENTED;
}

int  TTrdItf_DD::QryMoney()
{
  char *pOut;
  char buffer[256];
  char bz[8],bal[20],av[20];
  int nCount=FDll.read_zjxx(FAccInfo.Capital,"",&pOut,FCot);
  if(nCount>0)
  {
    for ( int nIndex = 0; nIndex < nCount; nIndex ++ )
    {
      FDll.QAGetRow( pOut,nIndex+1,buffer,sizeof(buffer) );
      FDll.QAGetString( buffer,1,bz,8);
      FDll.QAGetString( buffer,2,bal,20);
      FDll.QAGetString( buffer,3,av,20);
      if(strcmpi(bz,mtrmb)==0)  //is RMB
      {
        NewAns(1);
        (*FAnswer)[0].QryMoney.Balance=StrToFloatDef(bal,-1);
        (*FAnswer)[0].QryMoney.Available=StrToFloatDef(av,-1);
        (*FAnswer)[0].QryMoney.asset_balance=0;  //这项无效
        return 0;
      }
    }
    return -2;
  }
  else
  {
    ShowErr();
    return -1;
  }
}

int  TTrdItf_DD::QryStock()
{
  return ERR_UNIMPLEMENTED;
}

int  TTrdItf_DD::QryCanBuy()
{
  return ERR_UNIMPLEMENTED;
}

int  TTrdItf_DD::QryDetail()
{
  char *pOut;
  char buffer[256];
  char num[20],price[20],undo[20];
  char status[10],ordnum[20];

  if(FRequest.QryDetail.ContractID[0]==0) return -1;

  int nCount=FDll.requestentrust(FAccInfo.Capital,
                      FRequest.QryDetail.Bourse==bsSH ? jtsh : jtsz,
                      //FRequest.QryDetail.Bourse==bsSH ? FAccInfo.SH : FAccInfo.SZ,
                      "",
                      FRequest.QryDetail.ContractID,
                      &pOut,FCot) ;


  if(nCount>0)
  {
    for ( int nIndex = 0; nIndex < nCount; nIndex ++ )
    {
      FDll.QAGetRow( pOut,nIndex+1,buffer,sizeof(buffer) );
      FDll.QAGetString( buffer,11,price,20);
      FDll.QAGetString( buffer,12,num,20);
      FDll.QAGetString( buffer,13,undo,20);
      FDll.QAGetString(buffer,15,status,10);
      FDll.QAGetString(buffer,9,ordnum,20);

      NewAns(1);
      (*FAnswer)[0].QryDetail.Num=StrToIntDef(num,0);
      (*FAnswer)[0].QryDetail.Price=StrToFloatDef(price,0);
      (*FAnswer)[0].QryDetail.UndoNum=-StrToIntDef(undo,0);

      if(atoi(status)<-10)
      {
        (*FAnswer)[0].QryDetail.UndoNum=-atoi(ordnum);
      }

      if((*FAnswer)[0].QryDetail.Num==-1 //|| (*FAnswer)[0].QryDetail.Price==-1
        ||
        (*FAnswer)[0].QryDetail.UndoNum==-1)
        return -2;
      return 0;
    }
    return -3;
  }
  else
  {
    ShowErr();
    return -1;
  }
/*
  int nCount=FDll.read_drcj_hth(FRequest.QryDetail.Bourse==bsSH ? FAccInfo.SH : FAccInfo.SZ,
                                FRequest.QryDetail.Bourse==bsSH ? jtsh : jtsz,
                                FRequest.QryDetail.ContractID,
                                &pOut,FCot);
  if(nCount>0)
  {
    for ( int nIndex = 0; nIndex < nCount; nIndex ++ )
    {
      return 0;
    }
  }
  else return -1; */
}

int  TTrdItf_DD::QryHisDetail()
{
  return ERR_UNIMPLEMENTED;
}

int  TTrdItf_DD::QryCsn()
{
  return ERR_UNIMPLEMENTED;
}
//////////////////////////////////////////////////////////////////////////////
int  TTrdItf_DD::QryCurCsn()
{
  char *pOut;
  char buffer[256];
  char tmp[20];
  int nCount=FDll.read_wt_zjzh(FAccInfo.Capital,
                      "",&pOut,FCot);

  if(nCount==0) return nCount;
  else if( nCount<0)
  {
    ShowErr();
    return nCount;
  }

  NewAns(nCount);
  try
  {
    for ( int nIndex = 0; nIndex < nCount; nIndex ++ )
    {
      FDll.QAGetRow( pOut,nIndex+1,buffer,sizeof(buffer) );
      FDll.QAGetString( buffer,4,(*FAnswer)[nIndex].QryCurCsn.CsgInfo.ContractID,20);
      FDll.QAGetString( buffer,6,(*FAnswer)[nIndex].QryCurCsn.CsgInfo.SecuID,8);
      FDll.QAGetString( buffer,7,(*FAnswer)[nIndex].QryCurCsn.CsgInfo.SecuDesc,9);

      FDll.QAGetString( buffer,3,tmp,20);
      if(strcmp(tmp,jtsh)==0)
        (*FAnswer)[nIndex].QryCurCsn.CsgInfo.Bourse='0';
      else if( strcmp(tmp,jtsz)==0)
        (*FAnswer)[nIndex].QryCurCsn.CsgInfo.Bourse='1';
      else
        (*FAnswer)[nIndex].QryCurCsn.CsgInfo.Bourse='N';


      (*FAnswer)[nIndex].QryCurCsn.CsgInfo.Time[0]=0;
      (*FAnswer)[nIndex].QryCurCsn.CsgInfo.Date[0]=0;
      FDll.QAGetString( buffer,5,tmp,10);
      (*FAnswer)[nIndex].QryCurCsn.CsgInfo.Type=DDTypeToType(tmp) ;
      (*FAnswer)[nIndex].QryCurCsn.CsgInfo.State='N';

      FDll.QAGetString( buffer,9,tmp,20);
      (*FAnswer)[nIndex].QryCurCsn.CsgInfo.CsnVol=StrToIntDef(tmp,0);
      FDll.QAGetString( buffer,12,tmp,20);
      (*FAnswer)[nIndex].QryCurCsn.CsgInfo.TrdVol=StrToIntDef(tmp,0);
      FDll.QAGetString( buffer,13,tmp,20);
      (*FAnswer)[nIndex].QryCurCsn.CsgInfo.CancelVol=StrToIntDef(tmp,0);
      FDll.QAGetString( buffer,8,tmp,20);
      (*FAnswer)[nIndex].QryCurCsn.CsgInfo.CsnPrice=StrToFloatDef(tmp,0);
      FDll.QAGetString( buffer,11,tmp,20);
      (*FAnswer)[nIndex].QryCurCsn.CsgInfo.TrdPrice=StrToFloatDef(tmp,0);
    }
  }
  catch(...)
  {
    return -2;
  }
  return 0;
}

int  TTrdItf_DD::QryHisCsn()
{
  char *pOut;
  char buffer[256];
  char tmp[20];
  char sd[11],ed[11];
  YYYYMMDD2DingDian(FRequest.QryHisCsn.StartDay,sd);
  YYYYMMDD2DingDian(FRequest.QryHisCsn.EndDay,ed);
  int nCount=FDll.read_lswt_zjzh(FAccInfo.Capital,
                      sd,ed,
                      &pOut,FCot);

  if(nCount==0) return nCount;
  else if( nCount<0)
  {
    ShowErr();
    return nCount;
  }

  NewAns(nCount);
  try
  {
    for ( int nIndex = 0; nIndex < nCount; nIndex ++ )
    {
      FDll.QAGetRow( pOut,nIndex+1,buffer,sizeof(buffer) );

      FDll.QAGetString( buffer,4,(*FAnswer)[nIndex].QryHisCsn.CsgInfo.ContractID,20);
      FDll.QAGetString( buffer,6,(*FAnswer)[nIndex].QryHisCsn.CsgInfo.SecuID,8);
      FDll.QAGetString( buffer,7,(*FAnswer)[nIndex].QryHisCsn.CsgInfo.SecuDesc,9);

      FDll.QAGetString( buffer,3,tmp,20);
      if(strcmp(tmp,jtsh)==0)
        (*FAnswer)[nIndex].QryHisCsn.CsgInfo.Bourse='0';
      else if( strcmp(tmp,jtsz)==0)
        (*FAnswer)[nIndex].QryHisCsn.CsgInfo.Bourse='1';
      else
        (*FAnswer)[nIndex].QryHisCsn.CsgInfo.Bourse='N';

      (*FAnswer)[nIndex].QryHisCsn.CsgInfo.Time[0]=0;
      (*FAnswer)[nIndex].QryHisCsn.CsgInfo.Date[0]=0;
      //--2004-12-24
      FDll.QAGetString( buffer,5,tmp,10);
      (*FAnswer)[nIndex].QryHisCsn.CsgInfo.Type=DDTypeToType(tmp);
      (*FAnswer)[nIndex].QryHisCsn.CsgInfo.State='N';

      FDll.QAGetString( buffer,9,tmp,20);
      (*FAnswer)[nIndex].QryHisCsn.CsgInfo.CsnVol=StrToIntDef(tmp,0);
      FDll.QAGetString( buffer,12,tmp,20);
      (*FAnswer)[nIndex].QryHisCsn.CsgInfo.TrdVol=StrToIntDef(tmp,0);
      FDll.QAGetString( buffer,13,tmp,20);
      (*FAnswer)[nIndex].QryHisCsn.CsgInfo.CancelVol=StrToIntDef(tmp,0);
      FDll.QAGetString( buffer,8,tmp,20);
      (*FAnswer)[nIndex].QryHisCsn.CsgInfo.CsnPrice=StrToFloatDef(tmp,0);
      FDll.QAGetString( buffer,11,tmp,20);
      (*FAnswer)[nIndex].QryHisCsn.CsgInfo.TrdPrice=StrToFloatDef(tmp,0);
    }
  }
  catch(...)
  {
    return -2;
  }
  return 0;
}

int  TTrdItf_DD::QryCurTrd()
{
  char *pOut;
  char buffer[256];
  char tmp[20];
  int nCount=FDll.read_drcj_zjzh(FAccInfo.Capital,"",&pOut,FCot);
  if(nCount==0) return nCount;
  else if( nCount<0)
  {
    ShowErr();
    return nCount;
  }
  NewAns(nCount);
  try
  {
    for ( int nIndex = 0; nIndex < nCount; nIndex ++ )
    {
      FDll.QAGetRow( pOut,nIndex+1,buffer,sizeof(buffer) );
      FDll.QAGetString( buffer,7,(*FAnswer)[nIndex].QryCurTrd.TrdInfo.SecuID,8);
      FDll.QAGetString( buffer,8,(*FAnswer)[nIndex].QryCurTrd.TrdInfo.SecuDesc,9);
      FDll.QAGetString( buffer,5,(*FAnswer)[nIndex].QryCurTrd.TrdInfo.Time,9);
      (*FAnswer)[nIndex].QryCurTrd.TrdInfo.Date[0]=0;
      //--2004-12-24
      FDll.QAGetString( buffer,6,tmp,10);
      (*FAnswer)[nIndex].QryCurTrd.TrdInfo.Type=DDTypeToType(tmp);
      FDll.QAGetString( buffer,9,tmp,20);
      (*FAnswer)[nIndex].QryCurTrd.TrdInfo.Vol=StrToIntDef(tmp,0);
      FDll.QAGetString( buffer,10,tmp,20);
      (*FAnswer)[nIndex].QryCurTrd.TrdInfo.Price=StrToFloatDef(tmp,0);
    }
  }
  catch(...)
  {
    return -2;
  }
  return 0;
}

int  TTrdItf_DD::QryHisTrd()
{
  char *pOut;
  char buffer[256];
  char tmp[20];
  char sd[11],ed[11];
  YYYYMMDD2DingDian(FRequest.QryHisTrd.StartDay,sd);
  YYYYMMDD2DingDian(FRequest.QryHisTrd.EndDay,ed);
  int nCount=FDll.read_lscj_zjzh(FAccInfo.Capital,"",
                      sd,ed,
                      &pOut,FCot);
  if(nCount==0) return nCount;
  else if( nCount<0)
  {
    ShowErr();
    return nCount;
  }
  NewAns(nCount);
  try
  {
    for ( int nIndex = 0; nIndex < nCount; nIndex ++ )
    {
      FDll.QAGetRow( pOut,nIndex+1,buffer,sizeof(buffer) );

      FDll.QAGetString( buffer,3,(*FAnswer)[nIndex].QryHisTrd.TrdInfo.SecuID,8);
      FDll.QAGetString( buffer,4,(*FAnswer)[nIndex].QryHisTrd.TrdInfo.SecuDesc,9);
      (*FAnswer)[nIndex].QryHisTrd.TrdInfo.Time[0]=0;
      FDll.QAGetString( buffer,1,tmp,20);
      DingDian2YYYYMMDD(tmp,(*FAnswer)[nIndex].QryHisTrd.TrdInfo.Date);

      FDll.QAGetString( buffer,2,tmp,10);
      (*FAnswer)[nIndex].QryHisTrd.TrdInfo.Type=DDTypeToType(tmp);
      FDll.QAGetString( buffer,7,tmp,20);
      (*FAnswer)[nIndex].QryHisTrd.TrdInfo.Vol=StrToIntDef(tmp,0);
      FDll.QAGetString( buffer,6,tmp,20);
      (*FAnswer)[nIndex].QryHisTrd.TrdInfo.Price=StrToFloatDef(tmp,0);
    }
  }
  catch(...)
  {
    return -2;
  }
  return 0;
}

int  TTrdItf_DD::QryBill()
{
  char *pOut;
  char buffer[256];
  char tmp[20];
  char sd[11],ed[11];
  YYYYMMDD2DingDian(FRequest.QryBill.StartDay,sd);
  YYYYMMDD2DingDian(FRequest.QryBill.EndDay,ed);
  int nCount=FDll.read_zjls(FAccInfo.Capital,
                      sd,ed,
                      &pOut,
                      FCot);
  if(nCount==0) return nCount;
  else if( nCount<0)
  {
    ShowErr();
    return nCount;
  }
  NewAns(nCount);
  try
  {
    for ( int nIndex = 0; nIndex < nCount; nIndex ++ )
    {
      FDll.QAGetRow( pOut,nIndex+1,buffer,sizeof(buffer) );

      FDll.QAGetString( buffer,1,tmp,20);
      DingDian2YYYYMMDD(tmp,(*FAnswer)[nIndex].QryBill.FundInfo.Date);
      FDll.QAGetString( buffer,2,(*FAnswer)[nIndex].QryBill.FundInfo.SecuID,8);  //流水号
      FDll.QAGetString( buffer,3,(*FAnswer)[nIndex].QryBill.FundInfo.SecuDesc,9);//业务科目
      FDll.QAGetString( buffer,4,(*FAnswer)[nIndex].QryBill.FundInfo.Type,13);//摘要
      //ll.QAGetString( buffer,1,tmp,9);
      (*FAnswer)[nIndex].QryBill.FundInfo.Vol=0;
      //ll.QAGetString( buffer,1,tmp,9);
      (*FAnswer)[nIndex].QryBill.FundInfo.Price=0;
      FDll.QAGetString( buffer,5,tmp,20);
      (*FAnswer)[nIndex].QryBill.FundInfo.TrdMny=StrToFloatDef(tmp,0);
      FDll.QAGetString( buffer,6,tmp,20);
      (*FAnswer)[nIndex].QryBill.FundInfo.Balance=StrToFloatDef(tmp,0);
    }
  }
  catch(...)
  {
    return -2;
  }
  return 0;
}
/////////////////////////////////////////////////////////////////////////

int  TTrdItf_DD::QryStocks()
{
  char *pOut;
  char buffer[256];
  char tmp[20];
  //FDll.read_gp_zqdm()
  int nCount=FDll.read_gp_zjzh(FAccInfo.Capital,
                      FRequest.QryStocks.Bourse==bsSH ? jtsh : jtsz,&pOut,FCot);

  if(nCount==0) return nCount;
  else if( nCount<0)
  {
    ShowErr();
    return nCount;
  }

  NewAns(nCount);
  try
  {
    for ( int nIndex = 0; nIndex < nCount; nIndex ++ )
    {
      FDll.QAGetRow( pOut,nIndex+1,buffer,sizeof(buffer) );
      FDll.QAGetString( buffer,2,tmp,20);
      if(lstrcmpi(jtsh,tmp)==0)
      {
        (*FAnswer)[nIndex].QryStocks.StockInfo.SecuID[0]='H';
      }
      else (*FAnswer)[nIndex].QryStocks.StockInfo.SecuID[0]='S';

      FDll.QAGetString( buffer,3,(*FAnswer)[nIndex].QryStocks.StockInfo.SecuID+1,7);
      FDll.QAGetString( buffer,1,(*FAnswer)[nIndex].QryStocks.StockInfo.SecuDesc,12);

      FDll.QAGetString( buffer,18,tmp,20);
      (*FAnswer)[nIndex].QryStocks.StockInfo.Balance=StrToIntDef(tmp,0);

      FDll.QAGetString( buffer,7,tmp,20);
      (*FAnswer)[nIndex].QryStocks.StockInfo.Available=StrToIntDef(tmp,0);

      //冻结信息无法获得
      //FDll.QAGetString( buffer,7,tmp,20);
      (*FAnswer)[nIndex].QryStocks.StockInfo.BuyFreeze=0;
      //FDll.QAGetString( buffer,7,tmp,20);
      (*FAnswer)[nIndex].QryStocks.StockInfo.SellFreeze=0;
      //FDll.QAGetString( buffer,7,tmp,20);
      (*FAnswer)[nIndex].QryStocks.StockInfo.AbnorFreeze=0;
      FDll.QAGetString( buffer,15,tmp,20);
      (*FAnswer)[nIndex].QryStocks.StockInfo.CostPrice=StrToFloatDef(tmp,0);
      //FDll.QAGetString( buffer,15,tmp,20);
      (*FAnswer)[nIndex].QryStocks.StockInfo.Cost=
        (*FAnswer)[nIndex].QryStocks.StockInfo.Balance *
        (*FAnswer)[nIndex].QryStocks.StockInfo.CostPrice;
      FDll.QAGetString( buffer,12,tmp,20);
      (*FAnswer)[nIndex].QryStocks.StockInfo.CurVal=StrToFloatDef(tmp,0);
      FDll.QAGetString( buffer,11,tmp,20);
      (*FAnswer)[nIndex].QryStocks.StockInfo.CurPrice=StrToFloatDef(tmp,0);
      FDll.QAGetString( buffer,17,tmp,20);
      (*FAnswer)[nIndex].QryStocks.StockInfo.ProfitAndLoss=StrToFloatDef(tmp,0);
    }
  }
  catch(...)
  {
    return -2;
  }
  return 0;
}

//////交易函数/////
int  TTrdItf_DD::Buy()
{
  TBourse et;
  if(FRequest.Buy.SecuID[0]=='H')
  {
    et=bsSH;
  }
  else if(FRequest.Buy.SecuID[0]=='S')
    et=bsSZ;

  int nCount;

  if(FRequest.Buy.Type==1)
  {
    nCount=FDll.etf_sgsh(et==bsSH ? jtsh : jtsz,
                        et==bsSH ? FAccInfo.SH : FAccInfo.SZ,
                        FRequest.Buy.SecuID+1,
                        FRequest.Buy.Num,
                        FRequest.Buy.Price,
                        FAccInfo.Capital,
                        FAccInfo.PW,
                        FCot);
  }
  else
  {
    nCount=FDll.trade_buy(FAccInfo.Capital,
                        et==bsSH ? jtsh : jtsz,
                        et==bsSH ? FAccInfo.SH : FAccInfo.SZ,
                        FRequest.Buy.SecuID+1,
                        FRequest.Buy.Price,
                        FRequest.Buy.Num,
                        FAccInfo.PW,
                        FCot);
  }
  if(nCount>0)
  {
    NewAns(1);
    strncpy((*FAnswer)[0].Buy.ContractID,IntToStr(nCount).c_str(),20);
    return 0;
  }
  else
  {
    ShowErr();
    return nCount;
  }
}

int  TTrdItf_DD::Sell()
{
  TBourse et;
  if(FRequest.Sell.SecuID[0]=='H')
  {
    et=bsSH;
  }
  else if(FRequest.Sell.SecuID[0]=='S')
    et=bsSZ;

  int nCount ;

  if(FRequest.Sell.Type==1)
  {
    nCount=FDll.etf_sgsh(et==bsSH ? jtsh : jtsz,
                        et==bsSH ? FAccInfo.SH : FAccInfo.SZ,
                        FRequest.Sell.SecuID+1,
                        -FRequest.Sell.Num, //赎回就是负值
                        FRequest.Sell.Price,
                        FAccInfo.Capital,
                        FAccInfo.PW,
                        FCot);
  }
  else
  {
    nCount=FDll.trade_sale(FAccInfo.Capital,
                      et==bsSH ? jtsh : jtsz,
                      et==bsSH ? FAccInfo.SH : FAccInfo.SZ,
                      FRequest.Sell.SecuID+1,
                      FRequest.Sell.Price,
                      FRequest.Sell.Num,
                      FAccInfo.PW
                      ,FCot);
  }
  if(nCount>0)
  {
    NewAns(1);
    strncpy((*FAnswer)[0].Sell.ContractID,IntToStr(nCount).c_str(),20);
    return 0;
  }
  else
  {
    ShowErr();
    return nCount;
  }
}

int  TTrdItf_DD::Undo()
{
  int nCount=FDll.trade_abort(FAccInfo.Capital,
                      FRequest.Undo.Bourse==bsSH ? jtsh : jtsz,
                      FRequest.Undo.Bourse==bsSH ? FAccInfo.SH : FAccInfo.SZ,
                      FAccInfo.PW,
                      FRequest.Undo.ContractID,
                      FCot);
  if(nCount>0)
  {
    return 0;
  }
  else
  {
    ShowErr();
    return nCount;
  }
}
