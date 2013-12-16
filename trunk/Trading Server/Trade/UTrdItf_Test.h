//---------------------------------------------------------------------------
#ifndef UTrdItf_TESTH
#define UTrdItf_TESTH
//---------------------------------------------------------------------------
#include "JZAPI.H"
#include "UTrdStruct.h"
#include "UTrdItfBase.h"
#include <system.hpp>
//---------------------------------------------------------------------------
class TTrdItf_TEST : public TTrdItfBase
{
private:	// User declarations
  typedef int (*TInit)(String CotID,String CotPW);  //��ʼ��
  typedef int (*TSetAccount)(String KHBS,TAccountSort Sort,String PW);
  typedef int (*TGetBuyInfo)(String SecuID,TDealInfo &Info);   //ȡ��������̿�����
  typedef int (*TGetSellInfo)(String SecuID,TDealInfo &Info);  //ȡ��������̿�����
  typedef int (*TQryMoney)(double &Balance,double &Available); //�ʽ��ѯ
  typedef int (*TQryStock)(String Capital,String SecuID,int &Balance,int &Available,int &BuyFreeze,int &SellFreeze); //�ɷݲ�ѯ
  typedef int (*TQryCanBuy)(String Capital,String SecuID,double Price,int &Num); //ȡ��������
  typedef int (*TQryDetail)(String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //�ɽ���ѯ
  typedef int (*TQryHisDetail)(String DateStr,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //��ʷ�ɽ���ѯ
  typedef int (*TQryCsn)(String ContractID,TBourse Bourse,TConsignInfo &CsgInfo); //��ѯĳ��ί�к�ͬ
  typedef int (*TQryCurCsn)(String Capital,TConsignInfo **CsgInfo,int &Num); //����ί�в�ѯ
  typedef int (*TQryHisCsn)(String Capital,String StartDay,String EndDay,TConsignInfo **CsgInfo,int &Num); //��ʷί�в�ѯ
  typedef int (*TQryCurTrd)(String Capital,TTradeInfo **TrdInfo,int &Num);   //���ճɽ���ѯ
  typedef int (*TQryHisTrd)(String Capital,String StartDay,String EndDay,TTradeInfo **TrdInfo,int &Num); //��ʷ�ɽ���ѯ
  typedef int (*TQryBill)(String StartDay,String EndDay,TFundInfo **FundInfo,int &Num); //��ѯ�ʽ���ˮ�����ʵ���
  typedef int (*TQryStocks)(String Capital,TStockInfo **StockInfo,int &Num); //��ѯ�ʺ������еĹɷ�
  typedef int (*TBuy)(String Capital,String SecuID,double Price,int Num,char **ContractID);
  typedef int (*TSell)(String Capital,String SecuID,double Price,int Num,char **ContractID);
  typedef int (*TUndo)(String ContractID,TBourse Bourse); //ί�г���

  TInit         FInit;
  TSetAccount   FSetAccount;
  TGetBuyInfo   FGetBuyInfo;
  TGetSellInfo  FGetSellInfo;
  TQryMoney     FQryMoney;
  TQryStock     FQryStock;
  TQryCanBuy    FQryCanBuy;
  TQryDetail    FQryDetail;
  TQryHisDetail FQryHisDetail;
  TQryCsn       FQryCsn;
  TQryCurCsn    FQryCurCsn;
  TQryHisCsn    FQryHisCsn;
  TQryCurTrd    FQryCurTrd;
  TQryHisTrd    FQryHisTrd;
  TQryBill      FQryBill;
  TQryStocks    FQryStocks;
  TBuy          FBuy;
  TSell         FSell;
  TUndo         FUndo;

  HINSTANCE FHandle;

  int  Init();  //��ʼ��
  int  SetAccount(); //�����ʺ�

  //////��ѯ����//////
  int  GetTrdInfo();   //ȡ���̿�����
  int  QryMoney();     //�ʽ��ѯ
  int  QryStock();     //�ɷݲ�ѯ
  int  QryCanBuy();    //ȡ��������
  int  QryDetail();    //�ɽ���ѯ
  int  QryHisDetail(); //��ʷ�ɽ���ѯ
  int  QryCsn();       //��ѯĳ��ί�к�ͬ
  int  QryCurCsn();    //����ί�в�ѯ
  int  QryHisCsn();    //��ʷί�в�ѯ
  int  QryCurTrd();    //���ճɽ���ѯ
  int  QryHisTrd();    //��ʷ�ɽ���ѯ
  int  QryBill();      //��ѯ�ʽ���ˮ�����ʵ���
  int  QryStocks();    //��ѯ�ʺ������еĹɷ�

  virtual bs_type ConvertType(char *type)
  {
    return btNo;
  }

  virtual wt_state ConvertState(char *state)
  {
    return wsno;
  }

  //////���׺���/////
  int  Buy();
  int  Sell();
  int  Undo(); //ί�г���

public:		// User declarations
  TTrdItf_TEST();
  virtual  ~TTrdItf_TEST();

  void CloseLink(void)
  {
    return;
  }

};
//---------------------------------------------------------------------------
#endif


