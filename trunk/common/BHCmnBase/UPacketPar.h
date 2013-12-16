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
  TUDPPriceList     *FUDPPl;                //���۵���̬����UDP��ָ��
  TUDPPriceListSta  *FUDPPlSta;             //���۵���̬����UDP��ָ��

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
      NowBuf=new TStkNowInfo[nStkCount];   //�洢��Ʊ��ʵʱ����
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

  TStkNowInfo * GetStkInfo(char * Code); //��ȡָ����Ʊ�ļ�ʱ��Ϣ
  unsigned long GetSHZSDate(char * Code="H000001");

  virtual void OnNewStock(long index)//index Ϊ�¹�Ʊ�������ڴ��е�λ��
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
