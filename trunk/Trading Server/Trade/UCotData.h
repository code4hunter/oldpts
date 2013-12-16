#ifndef UCotDataH
#define UCotDataH
//------------------------------------------------------------------------------
#include <Classes.hpp>
#include "UTrdStruct.h"
//------------------------------------------------------------------------------
typedef struct { //�ʺż�¼
  char   Capital[13];
  double Money;
}TAccRec;
//------------------------------------------------------------------------------
typedef struct { //�ɷݼ�¼
  char    Capital[13];
  TBourse Bourse;
  char    SecuID[8];
  int     Balance;         //���
  int     Available;       //������
  int     BuyFreeze;       //���붳��
  int     SellFreeze;      //��������
}TStockRec;
//------------------------------------------------------------------------------
typedef struct { //ί�м�¼
  char    Capital[13];
  TBourse Bourse;
  char    ContractID[8];
  char    SecuID[8];
  char    Time[9];               //ί��ʱ��
  char    Date[9];               //ί������
  char    Type;                  //�������
  char    State;                 //����״̬
  long    CsnVol;                //ί������
  long    TrdVol;                //�ɽ�����
  long    CancelVol;             //��������
  double  CsnPrice;              //ί�м۸�
  double  TrdPrice;              //�ɽ��۸�
}TCmsRec;
//------------------------------------------------------------------------------
typedef struct { //���׼�¼
  char    Capital[13];
  TBourse Bourse;
  char    ContractID[8];
  char    SecuID[8];
  char    Time[9];               //�ɽ�ʱ��
  char    Date[9];               //ί������
  char    Type;                  //�������
  long    Vol;                   //�ɽ�����
  double  Price;                 //�ɽ��۸�
}TBargainRec;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------  
class TCotData 
{
private:	// User declarations
  int SHContractID;
  int SZContractID;

  TList *FAccRec;
  TList *FStockRec;
  TList *FCmsRec;
  TList *FBargainRec;

public:		// User declarations
  __fastcall TCotData();
  __fastcall ~TCotData();

  void __fastcall Add(TAccRec *AccRec);
  void __fastcall Add(TStockRec *StockRec);
  void __fastcall Add(TCmsRec *CmsRec);
  void __fastcall Add(TBargainRec *BargainRec);

  TAccRec*     __fastcall FindAcc(String Capital);
  TStockRec*   __fastcall FindStock(String Capital,TBourse Bourse,String SecuID);
  TCmsRec*     __fastcall FindCms(String Date,TBourse Bourse,String ContractID);
  TBargainRec* __fastcall FindBargain(String Date,TBourse Bourse,String ContractID);

  int __fastcall GetNewSHID() { return ++SHContractID; }
  int __fastcall GetNewSZID() { return ++SZContractID; }
};
//---------------------------------------------------------------------------
#endif


 