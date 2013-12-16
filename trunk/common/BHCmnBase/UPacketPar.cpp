//---------------------------------------------------------------------------
#include <string.h>
#include <stdlib.h>
#include <search.h>

#include "UPacketPar.h"
//--------------------------------------------------------------------------

int TPacketParser::SetMemPListDtlDlSta(TStkNowInfo *ptrDes,TUDPPriceListSta *ptrPl)
{
  TUDPPriceListSta * ptrMem=&ptrDes->PLSBuf;
  memcpy( ptrMem,ptrPl,sizeof(TUDPPriceListSta));
  /*
  TUDPPriceListSta * ptrMem=&ptrDes->PLSBuf;
  memset(ptrMem->SecuID,0,sizeof(ptrMem->SecuID));
  memcpy(ptrMem->SecuID,ptrPl->SecuID,sizeof(ptrMem->SecuID));
  memset(ptrMem->SecuDesc,0,sizeof(ptrMem->SecuDesc));
  memcpy(ptrMem->SecuDesc,ptrPl->SecuDesc,sizeof(ptrMem->SecuDesc));
  strcpy(ptrMem->Py ,ptrPl->Py);
  ptrMem->Type      = ptrPl->Type;
  ptrMem->Lc        = ptrPl->Lc;
  ptrMem->V5da      = ptrPl->V5da;
  ptrMem->FltStk    = ptrPl->FltStk;
  ptrMem->Date      = ptrPl->Date;
  */
  return 0;
}
//---------------------------------------------------------------------------
int TPacketParser::SetMemPListDtlDlDyn(TStkNowInfo *ptrDes,TUDPPriceList *ptrPl)
{
  TUDPPriceList * ptrMem=&ptrDes->PLBuf;
  memcpy(ptrMem,ptrPl,sizeof(TUDPPriceList));

  /*
  TUDPPriceList * ptrMem=&ptrDes->PLBuf;
  ptrMem->Vlm    = ptrPl->Vlm;
  ptrMem->PVlm    = ptrPl->PVlm;     //+
  ptrMem->Mny    = ptrPl->Mny;
  ptrMem->Co     = ptrPl->Co;
  ptrMem->Ch     = ptrPl->Ch;
  ptrMem->Cl     = ptrPl->Cl;
  ptrMem->Cp     = ptrPl->Cp;
  ptrMem->Pe     = ptrPl->Pe;
  ptrMem->Bv1    = ptrPl->Bv1;
  ptrMem->Bv2    = ptrPl->Bv2;
  ptrMem->Bv3    = ptrPl->Bv3;

#ifdef USE5
  ptrMem->Bv4    = ptrPl->Bv4;
  ptrMem->Bv5    = ptrPl->Bv5;
#endif
  ptrMem->Cbp    = ptrPl->Cbp;
  ptrMem->Bp2    = ptrPl->Bp2;
  ptrMem->Bp3    = ptrPl->Bp3;
#ifdef USE5	
  ptrMem->Bp4    = ptrPl->Bp4;
  ptrMem->Bp5    = ptrPl->Bp5;
#endif
  ptrMem->Sv1    = ptrPl->Sv1;
  ptrMem->Sv2    = ptrPl->Sv2;
  ptrMem->Sv3    = ptrPl->Sv3;
#ifdef USE5
  ptrMem->Sv4    = ptrPl->Sv4;
  ptrMem->Sv5    = ptrPl->Sv5;
#endif
  ptrMem->Csp    = ptrPl->Csp;
  ptrMem->Sp2    = ptrPl->Sp2;
  ptrMem->Sp3    = ptrPl->Sp3;
#ifdef USE5
  ptrMem->Sp4    = ptrPl->Sp4;
  ptrMem->Sp5    = ptrPl->Sp5;
#endif

  ptrMem->Abv    = ptrPl->Abv;
  ptrMem->Cv     = ptrPl->Cv;
  ptrMem->Time   = ptrPl->Time;
  ptrMem->Cmv    = ptrPl->Cmv;
  ptrMem->Cmm    = ptrPl->Cmm;
  ptrMem->C5ma   = ptrPl->C5ma;
  ptrMem->C4ma   = ptrPl->C4ma;
  ptrMem->C3ma   = ptrPl->C3ma;
  ptrMem->C2ma   = ptrPl->C2ma;
  ptrMem->C1ma   = ptrPl->C1ma;

  */

  return 0;
}

char TPacketParser::ReadUDPPackageData(char *Buf)
{
  long packageNo;
  int  datSum;
  char type;

  memcpy(&packageNo,Buf,sizeof(long));
  type = *(Buf+sizeof(long));
  memcpy(&datSum,Buf+sizeof(long)+sizeof(char),sizeof(long));
  switch (type)
  {
    case 'S': {
      FUDPPlSta = (TUDPPriceListSta *)(Buf+sizeof(long)*2+sizeof(char));
      for(int i=0;i<datSum;i++) {
        long no = FUDPPlSta[i].SecuNo;
        SetMemPListDtlDlSta(&NowBuf[no],&FUDPPlSta[i]);
      }
      break;
    }
    case 'P': {
      FUDPPl = (TUDPPriceList *)(Buf+sizeof(long)*2+sizeof(char));
      for(int i=0;i<datSum;i++)  {
        long no = FUDPPl[i].SecuNo;
        SetMemPListDtlDlDyn(&NowBuf[no],&FUDPPl[i]);
        OnNewStock(no);
      }
      break;
    }
  }
  return type;
}

int TPacketParser::InitMem(int nStkCount)
{
  if(FStkCount!=nStkCount)
  {
    if(NowBuf) delete[] NowBuf;
    if(nStkCount>0)
      NowBuf=new TStkNowInfo[nStkCount];
    else
      NowBuf=NULL;
    FStkCount=nStkCount;
  }
  return 0;
}

int CodeCmp(const void *arg1,const void *arg2)
{
  assert( arg1 );
  assert( arg2 );
  assert( ((TStkNowInfo*)arg2)->PLSBuf.SecuID);
  return(strcmpi((char*)arg1,((TStkNowInfo*)arg2)->PLSBuf.SecuID));
}

TStkNowInfo * TPacketParser::GetStkInfo(char * Code)
{
  if( NULL == NowBuf ) return NULL;
  size_t size=FStkCount;
  return (TStkNowInfo *)lfind(Code,NowBuf,&size,sizeof(TStkNowInfo),CodeCmp);
}

unsigned long TPacketParser::GetSHZSDate(char * Code)
{
  TStkNowInfo * si=GetStkInfo(Code);
  if(si)
  {
    return si->PLSBuf.Date;
  }
  return 0;
}



