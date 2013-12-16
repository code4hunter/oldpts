//------------------------------------------------------------------------------
#ifndef UTrdItfBaseH
#define UTrdItfBaseH
//------------------------------------------------------------------------------
#include "..\..\common\BHCmnBase\DebugStr.h"
#include "..\..\common\BHCmnBase\UTrdStruct.h"
#include "UTrdStruct_Rm.h"
#include "UTrdItfAPI.h"
//------------------------------------------------------------------------------

class TTrdItfBase : public TTrdItfAPI
{
public:
	CRITICAL_SECTION CS;

  bool FHasSetAccInfo;           //�Ƿ��Ѿ������ʺ�
  TRequest     FRequest;         //����
  TRequest     FSetAccRequest;
  TAnswer      **FAnswer;        //�ظ�
	TAnswer      *FAnsBuf;
  int          *FAnsCount;       //�ظ�����
  int          FBufCount;
	TInterfaceError FLastError;
	char FSetupFile[MAX_PATH+1];   //�����ļ�
	TAccountInfo FAccInfo;         //�ʺ���Ϣ
	void  NewAns(int AnsCount);    //����Ӧ���ڴ�ռ�
	bool  SetAnsCount(int AnsCount); // return true if AnsCount less than FBufCount
	virtual int  FreeAnswer( TAnswer *as=NULL);//����������ڴ棬�������ش˺���
	virtual int  Request(TRequest &Request,TAnswer **Answer,int &AnsCount);
	virtual char * GetStockAccountByType(account_type at); //��ȡ�ɶ��ʻ� ���������ش˺���
	virtual char * GetStockAccountByMarket(market_type mt);
	virtual void SetAccountByType(account_type at,const char* account,const char* pwd);

	TTrdItfBase(const char *psetupfile,ADDLOG plogfunc);
	virtual  ~TTrdItfBase();

	void lock(void);
	void unlock(void);
	int GetAccountInfo(void);
	void SetLogout(void);
	bool AutoLogin(void);
public:
	// ʵ�����º���
	virtual int  Init()=0;         //��ʼ��
	virtual int  SetAccount(bool useOldSession=false)=0;   //��¼��̨�м��
	//////��ѯ����//////
	virtual int  QryMoney()=0;     //�ʽ��ѯ
	virtual int  QryCurCsn()=0;    //����ί�в�ѯ
	virtual int  QryCurTrd()=0;    //���ճɽ���ѯ
	virtual int  QryStocks()=0;    //��ѯ�ʺ������еĹɷ�
	virtual int  GetLastError();   //��ȡ������
	virtual void SetLastError(int code ,TCHAR type ,const TCHAR* sender,const TCHAR * fmt,...);   //Set FLastError and ODS error

	//////���׺���/////
	virtual int  Order()=0;        //ί��
	virtual int  Undo()=0;         //ί�г���

  //���ӿڲ���ת��ɱ�׼����
	virtual market_type  ConvertMarketType(const char *t)=0;
	virtual order_type   ConvertOrderType(const char *t)=0;
	virtual order_state  ConvertOrderState(const char *t)=0;
	virtual pos_direction ConvertPosDir(const char *t)=0;
	virtual money_type   ConvertMoneyType(const char *t)=0;

	virtual char *  ConvertMarketType(market_type t)=0;
	virtual char *  ConvertOrderType(order_type t)=0;
	virtual char *  ConvertOrderState(order_state t)=0;
	virtual char *  ConvertPosDir(pos_direction t)=0;
	virtual char *  ConvertMoneyType(money_type t)=0;

	//��������Ϣ������,���û�л�ȡ������������Ϣ����false
	virtual bool GetConfig(void)=0;
	//��������Ϣ��д�������ļ�
	virtual void SetConfig(void)=0;
	//�ر��м������
	virtual void CloseLink(void);
	//����Ҫ����������ʵ�ִ˺���
	virtual int  KeepAlive(void){return 0;};

	//���ַ���ʱ��ת��������ʱ�� hhmmss yyyymmdd
	virtual long ConvertTimeToInt(const char *t );
	virtual long ConvertDateToInt(const char *t );
};
//------------------------------------------------------------------------------
#endif
