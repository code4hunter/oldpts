#ifndef UItfTrdH
#define UItfTrdH
//---------------------------------------------------------------------------
#include <windows.h>

#ifdef USESTRING
#include <Classes.hpp>
#endif

#include "UTrdStruct.h"
//---------------------------------------------------------------------------
class TItfTrd
{
#ifdef USESTRING
	typedef void* (*TNewTrdCot)();
	typedef void  (*TDelTrdCot)(void *TrdCot);

	typedef int (*TInit)(void *TrdCot,String CotID,String CotPW);  //��ʼ��
	typedef int (*TSetAccount)(void *TrdCot,String Account,TAccountSort Sort,String PW/*,TAccountInfo *AccInfo*/); //�����ʺ�
	typedef int (*TQryMoney)(void *TrdCot,double &Balance,double &Available); //�ʽ��ѯ
	typedef int (*TQryStock)(void *TrdCot,String SecuID,int &Balance,int &Available,
		int &BuyFreeze,int &SellFreeze); //�ɷݲ�ѯ
	typedef int (*TCanBuy)(void *TrdCot,String SecuID,double Price,int &Num); //ȡ��������
	typedef int (*TQryDetail)(void *TrdCot,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //�ɽ���ѯ
	typedef int (*TQryHisDetail)(void *TrdCot,String DateStr,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //�ɽ���ѯ
	typedef int (*TQryCsn)(void *TrdCot,String ContractID,TBourse Bourse,TConsignInfo &CsgInfo);
	typedef int (*TQryCurCsn)(void *TrdCot,TConsignInfo **CsgInfo,int &Num); //��ѯ����ί��
	typedef int (*TQryHisCsn)(void *TrdCot,String StartDay,String EndDay,
		TConsignInfo **CsgInfo,int &Num); //��ѯ��ʷί��
	typedef int (*TQryCurTrd)(void *TrdCot,TTradeInfo **TrdInfo,int &Num); //��ѯ���ս���
	typedef int (*TQryHisTrd)(void *TrdCot,String StartDay,String EndDay,
		TTradeInfo **TrdInfo,int &Num); //��ѯ��ʷ����
	typedef int (*TQryBill)(void *TrdCot,String StartDay,String EndDay,
		TFundInfo **FundInfo,int &Num);   //��ѯ�ʽ���ˮ
	typedef int (*TQryStocks)(void *TrdCot,TStockInfo **StockInfo,int &Num,TBourse Bourse); //��ѯ�ɷ�


	typedef int (*TBuy)(void *TrdCot,String SecuID,double Price,int Num,String &ContractID,short type);
	typedef int (*TSell)(void *TrdCot,String SecuID,double Price,int Num,String &ContractID,short type);
	typedef int (*TUndo)(void *TrdCot,String ContractID,TBourse Bourse); //ί�г���

	typedef int (*TSynBuy)(void *TrdCot,String SecuID,double &Price,int &Num,String &ContractID,int MilliSeconds);
	typedef int (*TSynSell)(void *TrdCot,String SecuID,double &Price,int &Num,String &ContractID,int MilliSeconds);
	typedef int (*TSynUndo)(void *TrdCot,String ContractID,TBourse Bourse,int MilliSeconds);

	typedef int (*TGetCapitalAcc)(void *TrdCot,String &Acc);
	typedef int (*TSetAccInfo)(void *TrdCot,TAccountInfo *AccInfo); //�����ʺ�
	typedef int (*TGetAccInfo)(void *TrdCot,TAccountInfo *AccInfo); //ȡ���ʺ���Ϣ
#else
	typedef void* (*TNewTrdCot)();
	typedef void  (*TDelTrdCot)(void *TrdCot);

	typedef int (*TInit)(void *TrdCot,char * CotID,char * CotPW);  //��ʼ��
	typedef int (*TSetAccount)(void *TrdCot,char * Account,TAccountSort Sort,char * PW/*,TAccountInfo *AccInfo*/); //�����ʺ�
	typedef int (*TQryMoney)(void *TrdCot,double &Balance,double &Available); //�ʽ��ѯ
	typedef int (*TQryStock)(void *TrdCot,char * SecuID,int &Balance,int &Available,
		int &BuyFreeze,int &SellFreeze); //�ɷݲ�ѯ
	typedef int (*TCanBuy)(void *TrdCot,char * SecuID,double Price,int &Num); //ȡ��������
	typedef int (*TQryDetail)(void *TrdCot,char * ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //�ɽ���ѯ
	typedef int (*TQryHisDetail)(void *TrdCot,char * DateStr,char * ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //�ɽ���ѯ
	typedef int (*TQryCsn)(void *TrdCot,char * ContractID,TBourse Bourse,TConsignInfo &CsgInfo);
	typedef int (*TQryCurCsn)(void *TrdCot,TConsignInfo **CsgInfo,int &Num); //��ѯ����ί��
	typedef int (*TQryHisCsn)(void *TrdCot,char * StartDay,char * EndDay,
		TConsignInfo **CsgInfo,int &Num); //��ѯ��ʷί��
	typedef int (*TQryCurTrd)(void *TrdCot,TTradeInfo **TrdInfo,int &Num); //��ѯ���ս���
	typedef int (*TQryHisTrd)(void *TrdCot,char * StartDay,char * EndDay,
		TTradeInfo **TrdInfo,int &Num); //��ѯ��ʷ����
	typedef int (*TQryBill)(void *TrdCot,char * StartDay,char * EndDay,
		TFundInfo **FundInfo,int &Num);   //��ѯ�ʽ���ˮ
	typedef int (*TQryStocks)(void *TrdCot,TStockInfo **StockInfo,int &Num,TBourse Bourse); //��ѯ�ɷ�


	typedef int (*TBuy)(void *TrdCot,char * SecuID,double Price,int Num,char * ContractID,short type);
	typedef int (*TSell)(void *TrdCot,char * SecuID,double Price,int Num,char * ContractID,short type);
	typedef int (*TUndo)(void *TrdCot,char * ContractID,TBourse Bourse); //ί�г���

	typedef int (*TSynBuy)(void *TrdCot,char * SecuID,double &Price,int &Num,char * ContractID,int MilliSeconds);
	typedef int (*TSynSell)(void *TrdCot,char * SecuID,double &Price,int &Num,char * ContractID,int MilliSeconds);
	typedef int (*TSynUndo)(void *TrdCot,char * ContractID,TBourse Bourse,int MilliSeconds);

	typedef int (*TGetCapitalAcc)(void *TrdCot,char *Acc);
	typedef int (*TSetAccInfo)(void *TrdCot,TAccountInfo *AccInfo); //�����ʺ�
	typedef int (*TGetAccInfo)(void *TrdCot,TAccountInfo *AccInfo); //ȡ���ʺ���Ϣ
#endif

	typedef void (*TFreeAnswer)(void *TrdCot,void *mem);
	typedef void* (*TNewTrdCotS)(void  * ei,char *ShareName);
	typedef int (*TBuyS)(void *TrdCot,char * SecuID,double Price,int Num,char * ContractID,void  * ei);
	typedef int (*TSellS)(void *TrdCot,char * SecuID,double Price,int Num,char * ContractID,void  * ei);
	typedef int (*TGetLastError)(void *TrdCot,char *ErrorText,char *Sender);
private:

	void *FEI;
	bool FSimulation;
	char FShareName[20];

	void           *FTrdCot;   //ָ��DLL�еĹ�̨�ӿ�
	HINSTANCE      FDllHandle; //��̬���ӿ���

	TNewTrdCot     FNewTrdCot;
	TDelTrdCot     FDelTrdCot;

	TInit          FInit;
	TSetAccount    FSetAccount;
	TQryMoney      FQryMoney;
	TQryStock      FQryStock;
	TCanBuy        FCanBuy;
	TQryDetail     FQryDetail;
	TQryHisDetail  FQryHisDetail;
	TQryCsn        FQryCsn;
	TQryCurCsn     FQryCurCsn;
	TQryHisCsn     FQryHisCsn;
	TQryCurTrd     FQryCurTrd;
	TQryHisTrd     FQryHisTrd;
	TQryBill       FQryBill;
	TQryStocks     FQryStocks;

	TBuy           FBuy;
	TSell          FSell;
	TUndo          FUndo;

	TGetCapitalAcc FGetCapitalAcc;
	TSetAccInfo    FSetAccInfo;
	TGetAccInfo    FGetAccInfo;

	TFreeAnswer    FFreeAnswer;
	TNewTrdCotS    FNewTrdCotS;
	TBuyS          FBuyS;
	TSellS         FSellS;

	TGetLastError  FGetLastError;

public:

	TItfTrd(bool simulation=false,void  * ei=NULL,char *ShareName="");
	~TItfTrd();
#ifdef USESTRING
	//�ڵ��ò�ѯ�������׺���֮ǰ�����ȳ�ʼ����̨�ӿ��������ʺ�
	int  Init(String CotID,String CotPW);  //��ʼ��
	int  SetAccount(String Account,TAccountSort Sort,String PW/*,TAccountInfo *AccInfo=NULL*/); //�����ʺ�

	//////��ѯ����//////
	int  QryStock(String SecuID,int &Balance,int &Available,
		int &BuyFreeze,int &SellFreeze);              //�ɷݲ�ѯ
	int  QryStock(String SecuID,double Price,int &Num); //ȡ��������
	int  QryDetail(String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //�ɽ���ѯ
	int  QryDetail(String DateStr,String ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //��ʷ�ɽ���ѯ
	int  QryCsn(String ContractID,TBourse Bourse,TConsignInfo &CsgInfo);
	int  QryHisCsn(String StartDay,String EndDay,TConsignInfo **CsgInfo,int &Num); //��ѯ��ʷί��
	int  QryHisTrd(String StartDay,String EndDay,TTradeInfo **TrdInfo,int &Num); //��ѯ��ʷ����
	int  QryBill(String StartDay,String EndDay,TFundInfo **FundInfo,int &Num);   //��ѯ�ʽ���ˮ

	//////���׺���/////
	//type 0,1
	//0 ��ʾ����,1��ʾ �깺���
	int  Buy(String SecuID,double Price,int Num,String &ContractID,short type);
	int  Sell(String SecuID,double Price,int Num,String &ContractID,short type);
	int  Undo(String ContractID,TBourse Bourse); //ί�г���

	int  GetCapitalAcc(String &Acc); //ȡ�ʽ��ʺ�
#else
	//�ڵ��ò�ѯ�������׺���֮ǰ�����ȳ�ʼ����̨�ӿ��������ʺ�
	int  Init(char *  CotID,char *  CotPW);  //��ʼ��
	int  SetAccount(char *  Account,TAccountSort Sort,char *  PW/*,TAccountInfo *AccInfo=NULL*/); //�����ʺ�

	//////��ѯ����//////
	int  QryStock(char *  SecuID,int &Balance,int &Available,
		int &BuyFreeze,int &SellFreeze);              //�ɷݲ�ѯ
	int  QryStock(char *  SecuID,double Price,int &Num); //ȡ��������
	int  QryDetail(char *  ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //�ɽ���ѯ
	int  QryDetail(char *  DateStr,char *  ContractID,TBourse Bourse,double &Price,int &Num,int &UndoNum); //��ʷ�ɽ���ѯ
	int  QryCsn(char *  ContractID,TBourse Bourse,TConsignInfo &CsgInfo);
	int  QryHisCsn(char *  StartDay,char *  EndDay,TConsignInfo **CsgInfo,int &Num); //��ѯ��ʷί��
	int  QryHisTrd(char *  StartDay,char *  EndDay,TTradeInfo **TrdInfo,int &Num); //��ѯ��ʷ����
	int  QryBill(char *  StartDay,char *  EndDay,TFundInfo **FundInfo,int &Num);   //��ѯ�ʽ���ˮ

	//////���׺���/////
  /*
  type ���÷�

  type = 1  ��ʾ�깺�������

  set ��ƽ��־ as a
  0  ����
  1  ƽ��
  2  ƽ��

  set Ͷ����־ as b
  0  Ͷ��
  1  ��ֵ

  type = a + b<<4 ��ʾ��ƽ��Ͷ�������

  */
	int  Buy(char *  SecuID,double Price,int Num,char * ContractID,short type);
	int  Sell(char *  SecuID,double Price,int Num,char * ContractID,short type);
	int  Undo(char *  ContractID,TBourse Bourse); //ί�г���

	int  GetCapitalAcc(char *Acc); //ȡ�ʽ��ʺ�
#endif
	int  QryStocks(TStockInfo **StockInfo,int &Num,TBourse Bourse/*=bsSH*/); //��ѯ�ɷ�
	int  QryCurTrd(TTradeInfo **TrdInfo,int &Num);      //��ѯ���ս���
	int  QryCurCsn(TConsignInfo **CsgInfo,int &Num);    //��ѯ����ί��
	int  QryMoney(double &Balance,double &Available); //�ʽ��ѯ

	int  SetAccInfo(TAccountInfo *AccInfo); //�����ʺ�
	int  GetAccInfo(TAccountInfo *AccInfo); //ȡ���ʺ���Ϣ

	void  FreeAnswer(void *mem);   //�ͷ��ڴ�

	void Open(void)
	{
		if(FTrdCot) Close();
		if(this->FSimulation)
			FTrdCot = FNewTrdCotS(FEI,FShareName);
		else
			FTrdCot = FNewTrdCot();
	}

	void Close(void)
	{
		if(FTrdCot) FDelTrdCot(FTrdCot);
		FTrdCot=NULL;
	}

	int GetLastError(char *ErrorText,char *Sender);
};
//---------------------------------------------------------------------------
#endif
