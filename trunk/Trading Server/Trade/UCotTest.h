#ifndef UCotTestH
#define UCotTestH
//------------------------------------------------------------------------------
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
  double  CostPrice;       //�ɱ���
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
class TCotTest
{
public:
  TList *FAccRec;     //�ʺ��б�
  TList *FStockRec;   //����б�
  TList *FCmsRec;     //ί�м�¼�б�
  TList *FBargainRec; //���׼�¼�б�

  TStockRec*   __fastcall FindStock(String Capital,TBourse Bourse,String SecuID);    //���ҿ��
  
private:	// User declarations
  int SHContractID; //�Ͻ�����ͬ���
  int SZContractID; //�����ͬ���

  TAccRec*     __fastcall FindAcc(String Capital); //����ƥ����ʺ�
  TCmsRec*     __fastcall FindCms(String Date,TBourse Bourse,String ContractID);     //����ί��
  TBargainRec* __fastcall FindBargain(String Date,TBourse Bourse,String ContractID); //���ҽ���

  bool         __fastcall IsCan(float Rate); //�ж��Ƿ���Բ���

public:		// User declarations
  __fastcall TCotTest();
  __fastcall ~TCotTest();

  int __fastcall Init(String CotID,String CotPW);  //��ʼ��
  int __fastcall SetAccount(String KHBS,TAccountSort Sort,String PW);

  //////��ѯ����//////
  int __fastcall GetBuyInfo(String SecuID,TDealInfo &Info);   //ȡ��������̿�����
  int __fastcall GetSellInfo(String SecuID,TDealInfo &Info);  //ȡ��������̿�����
  int __fastcall QryMoney(double &Balance,double &Available); //�ʽ��ѯ
  int __fastcall QryStock(String Capital,String SecuID,int &Balance,int &Available,int &BuyFreeze,int &SellFreeze); //�ɷݲ�ѯ
  int __fastcall QryStock(String Capital,String SecuID,double Price,int &Num); //ȡ��������
  int __fastcall QryDetail(String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //�ɽ���ѯ
  int __fastcall QryDetail(String DateStr,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //��ʷ�ɽ���ѯ
  int __fastcall QryCsn(String ContractID,TBourse Bourse,TConsignInfo &CsgInfo);
  int __fastcall QryCurCsn(String Capital,TConsignInfo **CsgInfo,int &Num); //����ί�в�ѯ
  int __fastcall QryHisCsn(String Capital,String StartDay,String EndDay,TConsignInfo **CsgInfo,int &Num); //��ʷί�в�ѯ
  int __fastcall QryCurTrd(String Capital,TTradeInfo **TrdInfo,int &Num);   //���ճɽ���ѯ
  int __fastcall QryHisTrd(String Capital,String StartDay,String EndDay,TTradeInfo **TrdInfo,int &Num); //��ʷ�ɽ���ѯ
  int __fastcall QryBill(String StartDay,String EndDay,TFundInfo **FundInfo,int &Num); //��ѯ�ʽ���ˮ�����ʵ���
  int __fastcall QryStocks(String Capital,TStockInfo **StockInfo,int &Num); //��ѯ�ʺ������еĹɷ�

  //////���׺���/////
  int __fastcall Buy(String Capital,String SecuID,double Price,int Num,String &ContractID);
  int __fastcall Sell(String Capital,String SecuID,double Price,int Num,String &ContractID);
  int __fastcall Undo(String ContractID,TBourse Bourse); //ί�г���
};
//---------------------------------------------------------------------------
#endif

 