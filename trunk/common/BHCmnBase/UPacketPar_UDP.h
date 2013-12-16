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
  TUDPPriceList     *FUDPPl;                //���۵���̬����UDP��ָ��
  TUDPPriceListSta  *FUDPPlSta;             //���۵���̬����UDP��ָ��

  int __fastcall SetMemPListDtlDlSta(TStkNowInfo *ptrDes,TUDPPriceListSta *ptrPl);
  int __fastcall SetMemPListDtlDlDyn(TStkNowInfo *ptrDes,TUDPPriceList *ptrPl);

  int FStkCount;
  String FPath;
public:
  String __fastcall ReadUDPPackageData(char *Buf);

  TStkNowInfo * NowBuf;

  TPacketParser(String Path)
  {
    NowBuf=new TStkNowInfo[MAXSTOCKS];   //�洢��Ʊ��ʵʱ����
    FPath=Path;
    FStkCount=0;
    //InitMem();
  };

  ~TPacketParser(void)
  {
    delete[] NowBuf;
  };

  int __fastcall InitMem();

  TStkNowInfo * __fastcall GetStkInfo(String Code); //��ȡָ����Ʊ�ļ�ʱ��Ϣ
  //double __fastcall GetStkBuyOne(String Code);
  //double __fastcall GetStkVlum(String Code);
  unsigned long GetSHZSDate(String Code="H000001");

  int GetStkCode(TStrings *stks);
};

#endif
