#include "System.h"
#include <stdio.h>

#include "UHQGetData.h"
#include "UHQBackupDef.h"
//---------------------------------------------------------------------------
THQGetData::THQGetData(char *FilePath, PCALLBACK Func)
{
  strncpy(FFilePath, FilePath, HQ_FILE_PATH_LEN - 1);
  FCallBack = Func;
}
//---------------------------------------------------------------------------

THQGetData::~THQGetData(void)
{

}
//---------------------------------------------------------------------------
int THQGetData::GetData(TPriceListDyn *DataBuf, char *Code, int Count, bool Mode)
{
  try
  {
    if(!DirectoryExists(FFilePath))
      return -1;

    char cFileNameH[HQ_FILE_PATH_LEN + 5];
    strcpy(cFileNameH, FFilePath);
    if(FFilePath[strlen(cFileNameH) - 1] != '\\')
      strcat(cFileNameH, "\\");

    if(Code[0] == 'H' || Code [0] == 'h')
      strcat(cFileNameH, "Sh");
    else if(Code[0] == 'S' || Code [0] == 's')
      strcat(cFileNameH, "Sz");
    else
      return -2;

    SYSTEMTIME stCurTime;
    GetLocalTime(&stCurTime);

    SYSTEMTIME ORIGINAL_DATE = {2004, 8, 4, 5, 0, 0, 0, 0};
    int iLastDate = GetDate(stCurTime, 1);
    char cCurFileName[HQ_FILE_NAME_LEN] = {0x0, };

    int iCount = 0;
    THQBackFileHead FHead;
    THQBackPackHead PackHead;
    char *buffer = NULL;
    int SecuNo = 0;
    //int iFileHandle = -1;
    FILE *pFileHandle = NULL;
    while (iCount < Count)
    {
      if(pFileHandle != NULL)
      {
        fclose(pFileHandle);
        pFileHandle = NULL;
      }

      iLastDate = GetDate(stCurTime, -1);
      if( DateCmp(stCurTime, ORIGINAL_DATE) < 0)
        break;

      char cDate[10] = {0x0, };
      sprintf(cDate, "%d", iLastDate);
      strcpy(cCurFileName, cFileNameH);
      strcat(cCurFileName, cDate);
      strcat(cCurFileName, ".dat");

      char cMsg[100] = "正在获取";
      strcat(cMsg, cDate);
      strcat(cMsg, "历史数据……");
      FCallBack(cMsg, iCount);
      
      pFileHandle = fopen(cCurFileName, "rb");
      if(pFileHandle == NULL)
        continue;
      if(fseek(pFileHandle, 0, 0) == -1)
        continue;
      if( fread(&FHead, sizeof(THQBackFileHead), 1, pFileHandle) <= 0)
        continue;
      if(FHead.stock_num <= 0)
        continue;

      //Read static stock info;
      if( fread(&PackHead, sizeof(THQBackPackHead), 1, pFileHandle) <= 0)
        continue;

      if(buffer != NULL)
      {
        delete []  buffer;
        buffer = NULL;
      }
      //buffer = new char[PackHead.length];
      buffer = new char[ sizeof(TUDPPackage) + sizeof(TUDPPriceList)*FHead.stock_num ];
      if( fread((void*)buffer, PackHead.length, 1, pFileHandle) <= 0 )
        continue;

      SecuNo = GetSecuNo(Code, buffer);  
      if(SecuNo < 0)
        continue;

      int iCurCount = 0;
      int iLastCount = iCount;
      while(true)
      {
        FCallBack(cMsg, iCount);
        
        if( fread(&PackHead, sizeof(THQBackPackHead), 1, pFileHandle) <= 0)
          break;

        if(fread(buffer, PackHead.length, 1, pFileHandle)  <= 0)
          break;

        if(AddFreshData(buffer, DataBuf, iLastCount, iCount, SecuNo, Count))
        {
          if( iCount < Count)
          {
            iCount++;
            iCurCount++;
          }
        }
      }

      ReorderData(DataBuf, iCurCount, iCount);
    }

    if(pFileHandle != NULL)
    {
      fclose(pFileHandle);
      pFileHandle = NULL;
    }
      
    if(buffer != NULL)
    {
      delete []  buffer;
      buffer = NULL;
    }
    FCallBack("", iCount);

    return iCount;
  }
  catch(...)
  {
    return -1;
  }
}
//---------------------------------------------------------------------------

int THQGetData::GetSecuNo(char *Code, char *Buf)
{
  char cType;
  long lSum;

  cType = *(Buf+sizeof(long));
  lSum = *(long *)(Buf + sizeof(long) + sizeof(char));

  if (cType == 'S')
  {
    TUDPPriceListSta * FUDPPlSta = (TUDPPriceListSta *)(Buf+sizeof(long)*2+sizeof(char));
    for (int i=0;i<lSum;i++)
    {
      long no = FUDPPlSta[i].SecuNo;

      if (stricmp(Code, FUDPPlSta[i].SecuID) == 0)
        return no;
    }
  }

  return -1;
}
//---------------------------------------------------------------------------
bool THQGetData::AddFreshData(char *Buf, TPriceListDyn *DataBuf, const int LastCount, const int iCount, const int SecuNo, const int Count)
{
  char cType;
  long lSum;

  cType = *(Buf+sizeof(long));
  lSum = *(long *)(Buf + sizeof(long) + sizeof(char));
  
  if (cType == 'P' )
  {
    TUDPPriceList *FUDPPl = (TUDPPriceList *)(Buf+sizeof(long)*2+sizeof(char));
    for (int i=0; i<lSum; i++)
    {
      long no = FUDPPl[i].SecuNo;
      if(no == SecuNo)
      {
        int iIndex = iCount;
        if(iCount == Count)
        {
          //Move data;
          for(int i=LastCount; i<iCount-1; i++ )
          {
            memcpy(&DataBuf[i], &DataBuf[i+1], sizeof(TPriceListDyn));
          }
          iIndex -= 1;
        }

        DataBuf[iIndex].Vlm    = FUDPPl[i].Vlm;
        DataBuf[iIndex].PVlm    = FUDPPl[i].PVlm;     //+
        DataBuf[iIndex].Mny    = FUDPPl[i].Mny;
        DataBuf[iIndex].Co     = FUDPPl[i].Co;
        DataBuf[iIndex].Ch     = FUDPPl[i].Ch;
        DataBuf[iIndex].Cl     = FUDPPl[i].Cl;
        DataBuf[iIndex].Cp     = FUDPPl[i].Cp;
        DataBuf[iIndex].Pe     = FUDPPl[i].Pe;
        DataBuf[iIndex].Bv1    = FUDPPl[i].Bv1;
        DataBuf[iIndex].Bv2    = FUDPPl[i].Bv2;
        DataBuf[iIndex].Bv3    = FUDPPl[i].Bv3;

      #ifdef USE5
        DataBuf[iIndex].Bv4    = FUDPPl[i].Bv4;
        DataBuf[iIndex].Bv5    = FUDPPl[i].Bv5;
      #endif
        DataBuf[iIndex].Cbp    = FUDPPl[i].Cbp;
        DataBuf[iIndex].Bp2    = FUDPPl[i].Bp2;
        DataBuf[iIndex].Bp3    = FUDPPl[i].Bp3;
      #ifdef USE5
        DataBuf[iIndex].Bp4    = FUDPPl[i].Bp4;
        DataBuf[iIndex].Bp5    = FUDPPl[i].Bp5;
      #endif
        DataBuf[iIndex].Sv1    = FUDPPl[i].Sv1;
        DataBuf[iIndex].Sv2    = FUDPPl[i].Sv2;
        DataBuf[iIndex].Sv3    = FUDPPl[i].Sv3;
      #ifdef USE5
        DataBuf[iIndex].Sv4    = FUDPPl[i].Sv4;
        DataBuf[iIndex].Sv5    = FUDPPl[i].Sv5;
      #endif
        DataBuf[iIndex].Csp    = FUDPPl[i].Csp;
        DataBuf[iIndex].Sp2    = FUDPPl[i].Sp2;
        DataBuf[iIndex].Sp3    = FUDPPl[i].Sp3;
      #ifdef USE5
        DataBuf[iIndex].Sp4    = FUDPPl[i].Sp4;
        DataBuf[iIndex].Sp5    = FUDPPl[i].Sp5;
      #endif

        DataBuf[iIndex].Abv    = FUDPPl[i].Abv;
        DataBuf[iIndex].Cv     = FUDPPl[i].Cv;
        DataBuf[iIndex].Time   = FUDPPl[i].Time;
        DataBuf[iIndex].Cmv    = FUDPPl[i].Cmv;
        DataBuf[iIndex].Cmm    = FUDPPl[i].Cmm;
        DataBuf[iIndex].C5ma   = FUDPPl[i].C5ma;
        DataBuf[iIndex].C4ma   = FUDPPl[i].C4ma;
        DataBuf[iIndex].C3ma   = FUDPPl[i].C3ma;
        DataBuf[iIndex].C2ma   = FUDPPl[i].C2ma;
        DataBuf[iIndex].C1ma   = FUDPPl[i].C1ma;

        return true;
      }
    }
  }

  return false;//no data was updated;
}
//---------------------------------------------------------------------------
void THQGetData::ReorderData(TPriceListDyn *DataBuf, int iCurCount, int iCount)
{
  if(iCount == iCurCount)
    return;

  int iLastCount = iCount - iCurCount;
  TPriceListDyn *buf = NULL;
  buf = new TPriceListDyn[iCount];
  memcpy(buf, DataBuf, iCount * sizeof(TPriceListDyn) );
  memcpy(DataBuf, &buf[iLastCount], iCurCount * sizeof(TPriceListDyn));
  memcpy(&DataBuf[iCurCount], buf, iLastCount * sizeof(TPriceListDyn));
  delete [] buf;
}
//---------------------------------------------------------------------------
bool THQGetData::OutputDebugFile(char* FileName, TPriceListDyn *Data, int Count)
{
  FILE* pFileHandle = fopen(FileName, "wb");
  if(pFileHandle == NULL)
    return false;

  char buf[200] = {0x0, };
  for(int i=0; i<Count; i++)
  {
    sprintf(buf, "Cbp=%d, bp2=%d, bp3=%d, bp4=%d, bp5=%d, Time=%d\r\n", Data[i].Cbp, Data[i].Bp2, \
                        Data[i].Bp3, Data[i].Bp4, Data[i].Bp5, Data[i].Time);

    fwrite(buf, strlen(buf), 1, pFileHandle);
  }
  fclose(pFileHandle);
  return true;
}
//---------------------------------------------------------------------------
int THQGetData::GetDate(SYSTEMTIME &Time)//yyyymmdd
{
  return (Time.wYear*10000 + Time.wMonth*100 + Time.wDay);
}
//---------------------------------------------------------------------------
int THQGetData::GetDate(SYSTEMTIME &Time, int Increment)
{
  WORD wDay = Time.wDay;
  wDay += Increment;

  if(wDay > 0 && wDay <= 28)
  {
    Time.wDay = wDay;
  }
  else
  {
    int iSingal = Increment/abs(Increment);

    //WORD wMaxDays;
    for(int i=0; i<abs(Increment); i++)
    {
      wDay = Time.wDay;
      wDay += iSingal;
      if(wDay > 0 && wDay <= 28)
      {
        Time.wDay = wDay;
        continue;
      }

      if(iSingal > 0)
      {
        if(wDay <= DaysOfAMonth(Time))
          Time.wDay = wDay;
        else
        {
          Time.wDay = 1;
          
          if(Time.wMonth == 12)
          {
            Time.wMonth = 1;
            Time.wYear += 1;
          }
          else
          {
            Time.wMonth += 1;
          }
        }
      }
      else//iSignal < 0;
      {
        if(wDay > 0)
        {
          Time.wDay = wDay;
        }
        else//==0
        {
          if(Time.wMonth == 1)
          {
            Time.wMonth = 12;
            Time.wYear -= 1;
          }
          else//> 1
          {
            Time.wMonth -= 1;
          }

          Time.wDay = DaysOfAMonth(Time);
        }
      }
    }
  }

  return GetDate(Time);
}
//---------------------------------------------------------------------------
short THQGetData::DateCmp(const SYSTEMTIME &SrcT, const SYSTEMTIME &DstT)
{
  WORD wSrc = SrcT.wYear*10000 + SrcT.wMonth*100 + SrcT.wDay;
  WORD wDst = DstT.wYear*10000 + DstT.wMonth*100 + DstT.wDay;

  if(wSrc > wDst)
    return 1;
  else if(wSrc < wDst)
    return -1;
  else
    return 0;
}
//---------------------------------------------------------------------------
WORD THQGetData::DaysOfAMonth(const SYSTEMTIME &Time)
{
  WORD wMaxDays = 30;
  switch(Time.wMonth)
  {
    case 1: case 3: case 5:
    case 7: case 8: case 10: case 12:
      wMaxDays = 31;
    break;
    case 4: case 6: case 9: case 11:
      wMaxDays = 30;
    break;
    case 2:
      if(IsLeapYear(Time))
        wMaxDays = 29;
      else
        wMaxDays = 28;
    break;
  }

  return wMaxDays;
}
//---------------------------------------------------------------------------
bool THQGetData::IsLeapYear(const SYSTEMTIME &Time)
{
  WORD wYear = Time.wYear;

  if(wYear/4 * 4 == wYear)
  {
    if( wYear/100 * 100 != wYear )
      return true;
    else if( wYear/400 * 400 == wYear )
      return true;
  }

  return false;
}
//---------------------------------------------------------------------------
