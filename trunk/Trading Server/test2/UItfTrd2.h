#ifndef UItfTrd2H
#define UItfTrd2H
//---------------------------------------------------------------------------
#include <windows.h>
#include "UTrdStruct.h"
//---------------------------------------------------------------------------
class TItfTrd
{
private:
	typedef void*(*TNewTrdCot)(void);
	typedef void(*TDelTrdCot)(void *TrdCot);
	typedef int (*TInit)(void *TrdCot,const char * ServerInfo);
	typedef int (*TLogin)(void *TrdCot,const char * Account,account_type Type,const char* PW);
	typedef int (*TQryMoney)(void *TrdCot,money_type MoneyType,TMoneyInfo &MoneyInfo);
	typedef int (*TQryOrder)(void *TrdCot,const char* OrdId,const char * PosStr,TOrderInfo **OrdInfo,int &Num);
	typedef int (*TQryTrade)(void *TrdCot,const char*  OrdId,const char* PosStr,TTradeInfo **TrdInfo,int &Num);
	typedef int (*TQryStocks)(void *TrdCot,market_type Market,TStockInfo **StockInfo,int &Num);
	typedef int (*TOrder)(void *TrdCot,const char* SecuID,double Price,int Num,market_type Market,order_type OrdType,char * ContractID,int ContractLength);
	typedef int (*TUndo)(void *TrdCot,const char* ContractID, market_type Market);
	typedef int (*TGetAccInfo)(void *TrdCot,TAccountInfo &AccInfo);
	typedef void(*TFreeAnswer)(void *TrdCot,void *mem);
	typedef int (*TGetLastError)(void *TrdCot,char *ErrorText,int ErrorLength,char *Sender,int SenderLength);

private:

	void           *FTrdCot;   //ָ��DLL�еĹ�̨�ӿ�
	HINSTANCE      FDllHandle; //��̬���ӿ���

	TNewTrdCot     FNewTrdCot;
	TDelTrdCot     FDelTrdCot;
	TInit          FInit;
	TLogin         FLogin;
	TQryMoney      FQryMoney;
	TQryOrder      FQryOrder;
	TQryTrade      FQryTrade;
	TQryStocks     FQryStocks;
	TGetAccInfo    FGetAccInfo;
	TFreeAnswer    FFreeAnswer;
	TOrder         FOrder;
	TUndo          FUndo;
	TGetLastError  FGetLastError;

	bool load_libray(const char * dllname);

public:

	TItfTrd();
	~TItfTrd();

	//��ʼ��(ServerInfo = ip:port)
	int  Init        (const char * ServerInfo);
	//ʹ���ʺŵ�¼
	int  Login       (const char * Account,account_type Type,const char* PW);
	//�ʽ��ѯ
	int  QryMoney    (money_type MoneyType,TMoneyInfo &MoneyInfo);
	//��ѯ����ί��
	int  QryOrder    (const char* OrdId,const char * PosStr,TOrderInfo **OrdInfo,int &Num);
	//��ѯ���ս���
	int  QryTrade    (const char*  OrdId,const char* PosStr,TTradeInfo **TrdInfo,int &Num);
	//��ѯ�ɷ�
	int  QryStocks   (market_type Market,TStockInfo **StockInfo,int &Num);
	//ί��    ContractID����Ϊ�ջ�������һλ�۸񾫶�(1,2,3,4)
	int  Order       (const char* SecuID,double Price,int Num,market_type Market,order_type OrdType,char * ContractID,int ContractLength);
	//ί�г���
	//����ֵ
	// 0 : �����ɹ�
	// -100: ����ʧ�ܣ�ԭ�����Ѿ��ɽ�
	// -200: ����ʧ�ܣ�ԭ���Ǹ�ί���ѷ�
	int  Undo        (const char* ContractID, market_type Market=mtNo);
	//ȡ���ʺ���Ϣ
	int  GetAccInfo  (TAccountInfo &AccInfo);
	//�û��ͷŲ�ѯ�������ص��ڴ�
	void FreeAnswer  (void *mem);
	//��ȡ��������Ϣ
	int  GetLastError(char *ErrorText,int ErrorLength,char *Sender,int SenderLength);

	//�½�һ��Զ�̽ӿ�
	void Open(void)
	{
		if( NULL == FDllHandle )  return;
		if(FTrdCot) Close();
		FTrdCot = FNewTrdCot();
	}

	//�رյ�ǰԶ�̽ӿ�
	void Close(void)
	{
		if( NULL == FDllHandle )  return;
		if(FTrdCot) FDelTrdCot(FTrdCot);
		FTrdCot=NULL;
	}
};
//---------------------------------------------------------------------------
#endif
