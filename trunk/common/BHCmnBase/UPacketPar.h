//---------------------------------------------------------------------------
#ifndef UPacketParH
#define UPacketParH

#include <assert.h>
#include "UDynStr.h"

#define USE5 1
//---------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct
{
  TUDPPriceList PLBuf;
  TUDPPriceListSta PLSBuf;
}TStkNowInfo;
#pragma pack(pop)

class TPacketParser
{
private:
  TUDPPriceList     *FUDPPl;                //报价单动态数据UDP包指针
  TUDPPriceListSta  *FUDPPlSta;             //报价单静态数据UDP包指针

  int SetMemPListDtlDlSta(TStkNowInfo *ptrDes,TUDPPriceListSta *ptrPl);
  int SetMemPListDtlDlDyn(TStkNowInfo *ptrDes,TUDPPriceList *ptrPl);

  int FStkCount;
public:
  char ReadUDPPackageData(char *Buf);

  TStkNowInfo * NowBuf;

  TPacketParser(int nStkCount)
  {
    if(nStkCount>0)
    {
      NowBuf=new TStkNowInfo[nStkCount];   //存储股票的实时数据
    }
    else
      NowBuf=NULL;
    FStkCount=nStkCount;
  };

  ~TPacketParser(void)
  {
    if(NowBuf) delete[] NowBuf;
  };

  int InitMem(int nStkCount);

  TStkNowInfo * GetStkInfo(char * Code); //获取指定股票的及时信息
  unsigned long GetSHZSDate(char * Code="H000001");

  virtual void OnNewStock(long index)//index 为新股票行情在内存中的位置
  {

  }

  TStkNowInfo * operator [](const int idx) const
  {
    assert(idx<FStkCount);   // Should Range-checking be optional to avoid overhead ??
    return &NowBuf[idx-1];
  }

  long GetStkCount(void)
  {
    return FStkCount;
  }
};

#endif
