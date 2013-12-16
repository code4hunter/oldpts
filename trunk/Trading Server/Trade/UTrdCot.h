//---------------------------------------------------------------------------
#ifndef UTrdCotH
#define UTrdCotH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "UTrdStruct.h"
#include "UTrdStruct_Rm.h"
//---------------------------------------------------------------------------
class TTrdCot
{
private:

protected:
  virtual int __fastcall Request(TRequest Request,TAnswer **Answer,int &AnsCount)=0; //��������
  virtual int __fastcall DeleteAns(TAnswer **Answer)=0;
public:
	__fastcall TTrdCot();
	virtual __fastcall ~TTrdCot();

	int __fastcall Init(void);  //��ʼ��
	int __fastcall Login(AnsiString Account,account_type Type,AnsiString PW); //�����ʺ�

  //////��ѯ����//////
	int __fastcall QryMoney(money_type MoneyType,TMoneyInfo &MoneyInfo); //�ʽ��ѯ
	int __fastcall QryOrder(AnsiString OrdId,AnsiString PosStr,TOrderInfo **OrdInfo,int &Num); //����ί�в�ѯ
	int __fastcall QryTrade(AnsiString OrdId,AnsiString PosStr,TTradeInfo **TrdInfo,int &Num); //���ճɽ���ѯ
	int __fastcall QryStocks(market_type Market,TStockInfo **StockInfo,int &Num); //��ѯ�ʺ������еĹɷ�
	int __fastcall GetAccInfo(TAccountInfo &AccInfo); //ȡ���ʺ���Ϣ
	//////���׺���/////
	int __fastcall Order( AnsiString SecuID,
												double Price,
												int Num,
												market_type Market,
												order_type OrdType,
												AnsiString &ContractID);

	int __fastcall Undo( AnsiString ContractID, market_type Market); //ί�г���
	//�ͷ��ڴ�
	int __fastcall FreeAnswer(void *mem)
	{
		delete [] mem;
		return 0;
	}
  //��ȡ������Ϣ
	int __fastcall GetLastError(AnsiString &ErrorText,AnsiString &Sender);
};
//---------------------------------------------------------------------------
#endif

