//---------------------------------------------------------------------------
#pragma hdrstop

#include "UPacketPar_UDP.h"
//--------------------------------------------------------------------------

#pragma package(smart_init)
int __fastcall TPacketParser::SetMemPListDtlDlSta(TStkNowInfo *ptrDes,TUDPPriceListSta *ptrPl)
{
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
  return 0;
}
//---------------------------------------------------------------------------
int __fastcall TPacketParser::SetMemPListDtlDlDyn(TStkNowInfo *ptrDes,TUDPPriceList *ptrPl)
{
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



  return 0;
}

String __fastcall TPacketParser::ReadUDPPackageData(char *Buf)
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
      }
      break;
    }
  }
  return String(type);
}

int __fastcall TPacketParser::InitMem()
{
  int hf;
  TPListHead hd;
  TPriceList rec;
  String netPath;
  //int secuNum;

  //netPath = CURPATH;
  netPath=FPath;
  if(!DirectoryExists(netPath))
  {
    return -3;
  }

  if(FileExists(netPath+"\\qtninit.tmp"))
  {
    //MessageBox(NULL,"服务器正在初始化行情，请稍后更新!","错误!",MB_ICONERROR);
    return -1;
  }

  hf = FileOpen(netPath + "\\CurPList.dat",fmOpenRead|fmShareDenyNone);
  if(hf == -1)
  {
    //MessageBox(NULL,"文件CurPList打开失败!","错误!",MB_ICONERROR);
    return -2;
  }

  FileSeek(hf,0,0);
  FileRead(hf,&hd,sizeof(TPListHead));
  FStkCount = hd.ShStockNum + hd.SzStockNum + hd.PtfNum;

  memset(NowBuf,0,sizeof(TStkNowInfo)* MAXSTOCKS);

  FileSeek(hf,int(sizeof(TPListHead)),0);
  for(int i=0; i<FStkCount; i++)
  {
    FileRead(hf,&rec,sizeof(TPriceList));
    strcpy(NowBuf[i].PLSBuf.SecuID,rec.SecuID);
    strcpy(NowBuf[i].PLSBuf.SecuDesc,rec.SecuDesc);
    strcpy(NowBuf[i].PLSBuf.Py,rec.Py);

    NowBuf[i].PLSBuf.Type   = rec.Type;
    NowBuf[i].PLSBuf.Lc     = rec.Lc;
    NowBuf[i].PLSBuf.V5da   = rec.V5da;
    NowBuf[i].PLSBuf.FltStk = rec.FltStk;
    NowBuf[i].PLSBuf.Date   = rec.Date;

    NowBuf[i].PLBuf.Co     = rec.Co;
    NowBuf[i].PLBuf.Ch     = rec.Ch;
    NowBuf[i].PLBuf.Cl     = rec.Cl;
    NowBuf[i].PLBuf.Cp     = rec.Cp;
    NowBuf[i].PLBuf.Vlm    = rec.Vlm;
    NowBuf[i].PLBuf.PVlm    = rec.PVlm;  //++
    NowBuf[i].PLBuf.Mny    = rec.Mny;

    NowBuf[i].PLBuf.Bv1    = rec.Bv1;
    NowBuf[i].PLBuf.Bv2    = rec.Bv2;
    NowBuf[i].PLBuf.Bv3    = rec.Bv3;

#ifdef USE5
    NowBuf[i].PLBuf.Bv4    = rec.Bv4;
    NowBuf[i].PLBuf.Bv5    = rec.Bv5;
#endif
    NowBuf[i].PLBuf.Cbp    = rec.Cbp;
    NowBuf[i].PLBuf.Bp2    = rec.Bp2;
    NowBuf[i].PLBuf.Bp3    = rec.Bp3;
#ifdef USE5
    NowBuf[i].PLBuf.Bp4    = rec.Bp4;
    NowBuf[i].PLBuf.Bp5    = rec.Bp5;
#endif
    NowBuf[i].PLBuf.Sv1    = rec.Sv1;
    NowBuf[i].PLBuf.Sv2    = rec.Sv2;
    NowBuf[i].PLBuf.Sv3    = rec.Sv3;
#ifdef USE5	
    NowBuf[i].PLBuf.Sv4    = rec.Sv4;
    NowBuf[i].PLBuf.Sv5    = rec.Sv5;
#endif
    NowBuf[i].PLBuf.Csp    = rec.Csp;
    NowBuf[i].PLBuf.Sp2    = rec.Sp2;
    NowBuf[i].PLBuf.Sp3    = rec.Sp3;
#ifdef USE5
    NowBuf[i].PLBuf.Sp4    = rec.Sp4;
    NowBuf[i].PLBuf.Sp5    = rec.Sp5;
#endif

    NowBuf[i].PLBuf.Abv    = rec.Abv;
    NowBuf[i].PLBuf.Cv     = rec.Cv;
    NowBuf[i].PLBuf.Time   = rec.Time;
  }

  FileClose(hf);
  return 0;
}

#include <assert.h>
int CodeCmp(const void *arg1,const void *arg2)
{
  return(strcmp((char*)arg1,((TStkNowInfo*)arg2)->PLSBuf.SecuID));
}

TStkNowInfo * __fastcall TPacketParser::GetStkInfo(String Code)
{
  size_t size=FStkCount;
  return (TStkNowInfo *)lfind(Code.c_str(),NowBuf,&size,sizeof(TStkNowInfo),CodeCmp);
}

unsigned long TPacketParser::GetSHZSDate(String Code)
{
  TStkNowInfo * si=GetStkInfo(Code);
  if(si)
  {
    return si->PLSBuf.Date;
  }
  return 0;
}

int TPacketParser::GetStkCode(TStrings *stks)
{
  stks->Clear();
  for(int i=0;i<FStkCount;i++)
  {
    if(strstr(NowBuf[i].PLSBuf.SecuDesc,"国债")!=NULL)
      stks->Add(NowBuf[i].PLSBuf.SecuID);
  }
  return FStkCount;
}



