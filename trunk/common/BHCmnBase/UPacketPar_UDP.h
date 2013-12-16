//---------------------------------------------------------------------------
#ifndef UPacketPar_UDPH
#define UPacketPar_UDPH

#include <Classes.hpp>
#include "UDynStr_OLD.h"
//---------------------------------------------------------------------------

#define MAXSTOCKS 2000
//#define CURPATH "\\\\1-is88yhqkq6b7v\\Current"

typedef struct
{
  TUDPPriceList PLBuf;
  TUDPPriceListSta PLSBuf;
}TStkNowInfo;

class TPacketParser
{
private:
  TUDPPriceList     *FUDPPl;                //报价单动态数据UDP包指针
  TUDPPriceListSta  *FUDPPlSta;             //报价单静态数据UDP包指针

  int __fastcall SetMemPListDtlDlSta(TStkNowInfo *ptrDes,TUDPPriceListSta *ptrPl);
  int __fastcall SetMemPListDtlDlDyn(TStkNowInfo *ptrDes,TUDPPriceList *ptrPl);

  int FStkCount;
  String FPath;
public:
  String __fastcall ReadUDPPackageData(char *Buf);

  TStkNowInfo * NowBuf;

  TPacketParser(String Path)
  {
    NowBuf=new TStkNowInfo[MAXSTOCKS];   //存储股票的实时数据
    FPath=Path;
    FStkCount=0;
    //InitMem();
  };

  ~TPacketParser(void)
  {
    delete[] NowBuf;
  };

  int __fastcall InitMem();

  TStkNowInfo * __fastcall GetStkInfo(String Code); //获取指定股票的及时信息
  //double __fastcall GetStkBuyOne(String Code);
  //double __fastcall GetStkVlum(String Code);
  unsigned long GetSHZSDate(String Code="H000001");

  int GetStkCode(TStrings *stks);
};

#endif
