#ifndef UTrdStruct_RmH
#define UTrdStruct_RmH

#include "UTrdStruct.h"

// Attention
// Use Interger-Sized enums to compile this header

//---------------------------------------------------------------------------
#pragma pack(push , 1)

enum TFuncType  //��������
{
	ftInit         = 0L,  //��ʼ��
	ftSetAccount   = 1L,  //�����ʺ�
	ftGetAccount   = 2L,  //��ȡ�ʺ���Ϣ
	ftQryMoney     = 3L,  //�ʽ��ѯ
	ftQryCurCsn    = 9L,  //����ί�в�ѯ
	ftQryCurTrd    = 11L, //���ճɽ���ѯ
	ftQryStocks    = 14L, //��ѯ�ʺ������еĹɷ�
	ftOrder        = 15L, //ί��
	ftUndo         = 17L, //ί�г���
	ftGetLastErr   = 20L  //��ȡ��������Ϣ
};
///////////����ͷ��Ϣ//////////////////////////////////
typedef struct
{
	long    Version;       //Э��汾2008
	long    FuncType;
}TReqHead;

///////////�ظ�ͷ��Ϣ////////////////////////////
typedef struct
{
	int          AnsCount;                  //�ظ����ݰ�����
	int          CurAnsNo;                  //��ǰ�ظ����ݰ����
	int          RetVal;                    //����ֵ,'0'Ϊ��ȷ
}TAnsHead;


///////////��ʼ��////////////////////////////
typedef struct
{
	TReqHead     ReqHead;
}TInit_Req;

typedef struct
{
	TAnsHead     AnsHead;
}TInit_Ans;

///////////�����ʺ�////////////////////////////
typedef struct
{
	TReqHead     ReqHead;
	char         Account[ACC_LEN]; //�ʺ�
	account_type LoginType;        //��¼���
	char         PW[PWD_LEN];      //�ʺ�����
}TSetAccount_Req;

typedef struct
{
	TAnsHead     AnsHead;
	TAccountInfo AccountInfo;      //�ʺ���Ϣ
}TSetAccount_Ans;


///////////�ʽ��ѯ////////////////////////////
typedef struct
{
	TReqHead     ReqHead;
	money_type   MoneyType;
}TQryMoney_Req;

typedef struct
{
	TAnsHead     AnsHead;
	TMoneyInfo   MoneyInfo;
}TQryMoney_Ans;

///////////����ί�в�ѯ////////////////////////////
typedef struct
{
	TReqHead     ReqHead;
	char         OrderID[SEQ_LEN+1];       //Ϊ�����ȫ����ָ��ĳ��ί�к����ָ����ί��
	char         SeqNum[SEQ_LEN+1];        //Ϊ�����ͷ��ʼ��
	long         MaxRecord;                //��󷵻ؼ�¼��
}TQryCurCsn_Req;

typedef struct
{
	TAnsHead     AnsHead;
	TOrderInfo   OrderInfo;        //ί����Ϣ
}TQryCurCsn_Ans;

///////////���ճɽ���ѯ////////////////////////////
typedef struct
{
	TReqHead     ReqHead;
	char         OrderID[SEQ_LEN+1];       //Ϊ�����ȫ����ָ��ĳ��ί�к����ָ����ί��
	char         SeqNum[SEQ_LEN+1];        //Ϊ�����ͷ��ʼ��
	long         MaxRecord;                //��󷵻ؼ�¼��
}TQryCurTrd_Req;

typedef struct
{
	TAnsHead     AnsHead;
	TTradeInfo   TrdInfo;            //�ɽ���Ϣ
}TQryCurTrd_Ans;

///////////��ѯ�ʺ������еĹɷ�////////////////////////////
typedef struct
{
  TReqHead     ReqHead;
  market_type  Market;
}TQryStocks_Req;

typedef struct
{
	TAnsHead     AnsHead;
	TStockInfo   StockInfo;          //�ɷ���Ϣ
}TQryStocks_Ans;

///////////ί�й�Ʊ////////////////////////////
typedef struct
{
  TReqHead     ReqHead;
  char         SecuID[CODE_LEN+1];//��Ʊ����
  market_type  Market;
  double       Price;            //�۸�
  int          Num;              //����
  order_type   Type;
}TOrder_Req;

typedef struct
{
	TAnsHead     AnsHead;
	char         ContractID[SEQ_LEN+1];
}TOrder_Ans;


///////////ί�г���////////////////////////////
typedef struct
{
	TReqHead     ReqHead;
	char         ContractID[SEQ_LEN+1];
	market_type  Market;
}TUndo_Req;

typedef struct
{
	TAnsHead     AnsHead;
}TUndo_Ans;

///////////��ȡ��������Ϣ////////////////////
typedef struct
{
	TReqHead     ReqHead;
}TGetLastError_Req;

typedef struct {
	TAnsHead     AnsHead;
	TInterfaceError Error;
}TGetLastError_Ans;


///////////��ȡ�ʻ���Ϣ////////////////////
typedef struct
{
	TReqHead     ReqHead;
}TGetAccountInfo_Req;

typedef struct
{
	TAnsHead     AnsHead;
	TAccountInfo AccountInfo;
}TGetAccountInfo_Ans;

///////////////////////////////////////////////////
typedef union
{
  TReqHead             Head;
	TInit_Req            Init;
	TSetAccount_Req      SetAccount;
	TGetAccountInfo_Req  GetAccount;
	TQryMoney_Req        QryMoney;
	TQryCurCsn_Req       QryCurCsn;
	TQryCurTrd_Req       QryCurTrd;
	TQryStocks_Req       QryStocks;
	TOrder_Req           Order;
	TUndo_Req            Undo;
	TGetLastError_Req    GetLastError;
}TRequest;

typedef union
{
	TAnsHead             Head;
	TInit_Ans            Init;
	TSetAccount_Ans      SetAccount;
	TGetAccountInfo_Ans  GetAccount;
	TQryMoney_Ans        QryMoney;
	TQryCurCsn_Ans       QryCurCsn;
	TQryCurTrd_Ans       QryCurTrd;
	TQryStocks_Ans       QryStocks;
	TOrder_Ans           Order;
	TUndo_Ans            Undo;
  TGetLastError_Ans GetLastError;
}TAnswer;

#pragma pack(pop)
//---------------------------------------------------------------------------
#endif

 