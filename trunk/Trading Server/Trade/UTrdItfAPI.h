//------------------------------------------------------------------------------
#ifndef UTTrdItfAPIH
#define UTTrdItfAPIH
//------------------------------------------------------------------------------
#include "..\..\common\BHCmnBase\DebugStr.h"
#include "..\..\common\BHCmnBase\UTrdStruct.h"
#include "UTrdStruct_Rm.h"
//------------------------------------------------------------------------------

#ifdef PTRADEAPI_EXPORTS
#define PTRADE_API __declspec(dllexport)
#else
#define PTRADE_API __declspec(dllimport)
#endif

PTRADE_API class TTrdItfAPI
{
public:
	// ʵ�����º���
	virtual int  Request(TRequest &Request,TAnswer **Answer,int &AnsCount)=0;
	//����������ڴ棬�������ش˺���
	virtual int  FreeAnswer( TAnswer *as=NULL)=0;
	//�ر��м������
	virtual void CloseLink(void)=0;
	//����Ҫ����������ʵ�ִ˺���
	virtual int  KeepAlive(void)=0;
	//��ȡ�ɶ��ʻ� ���������ش˺���
	virtual char * GetStockAccountByType(account_type at)=0;
	virtual char * GetStockAccountByMarket(market_type mt)=0;
};
//------------------------------------------------------------------------------
#endif
