#ifndef UTrdStruct_RmH
#define UTrdStruct_RmH

#include "UTrdStruct.h"

// Attention
// Use Interger-Sized enums to compile this header

//---------------------------------------------------------------------------
#pragma pack(push , 1)

enum TFuncType  //功能类型
{
	ftInit         = 0L,  //初始化
	ftSetAccount   = 1L,  //设置帐号
	ftGetAccount   = 2L,  //获取帐号信息
	ftQryMoney     = 3L,  //资金查询
	ftQryCurCsn    = 9L,  //当日委托查询
	ftQryCurTrd    = 11L, //当日成交查询
	ftQryStocks    = 14L, //查询帐号中所有的股份
	ftOrder        = 15L, //委托
	ftUndo         = 17L, //委托撤单
	ftGetLastErr   = 20L  //获取最后错误信息
};
///////////申请头信息//////////////////////////////////
typedef struct
{
	long    Version;       //协议版本2008
	long    FuncType;
}TReqHead;

///////////回复头信息////////////////////////////
typedef struct
{
	int          AnsCount;                  //回复数据包个数
	int          CurAnsNo;                  //当前回复数据包序号
	int          RetVal;                    //返回值,'0'为正确
}TAnsHead;


///////////初始化////////////////////////////
typedef struct
{
	TReqHead     ReqHead;
}TInit_Req;

typedef struct
{
	TAnsHead     AnsHead;
}TInit_Ans;

///////////设置帐号////////////////////////////
typedef struct
{
	TReqHead     ReqHead;
	char         Account[ACC_LEN]; //帐号
	account_type LoginType;        //登录类别
	char         PW[PWD_LEN];      //帐号密码
}TSetAccount_Req;

typedef struct
{
	TAnsHead     AnsHead;
	TAccountInfo AccountInfo;      //帐号信息
}TSetAccount_Ans;


///////////资金查询////////////////////////////
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

///////////当日委托查询////////////////////////////
typedef struct
{
	TReqHead     ReqHead;
	char         OrderID[SEQ_LEN+1];       //为空则查全部，指定某个委托号则查指定的委托
	char         SeqNum[SEQ_LEN+1];        //为空则从头开始查
	long         MaxRecord;                //最大返回记录数
}TQryCurCsn_Req;

typedef struct
{
	TAnsHead     AnsHead;
	TOrderInfo   OrderInfo;        //委托信息
}TQryCurCsn_Ans;

///////////当日成交查询////////////////////////////
typedef struct
{
	TReqHead     ReqHead;
	char         OrderID[SEQ_LEN+1];       //为空则查全部，指定某个委托号则查指定的委托
	char         SeqNum[SEQ_LEN+1];        //为空则从头开始查
	long         MaxRecord;                //最大返回记录数
}TQryCurTrd_Req;

typedef struct
{
	TAnsHead     AnsHead;
	TTradeInfo   TrdInfo;            //成交信息
}TQryCurTrd_Ans;

///////////查询帐号中所有的股份////////////////////////////
typedef struct
{
  TReqHead     ReqHead;
  market_type  Market;
}TQryStocks_Req;

typedef struct
{
	TAnsHead     AnsHead;
	TStockInfo   StockInfo;          //股份信息
}TQryStocks_Ans;

///////////委托股票////////////////////////////
typedef struct
{
  TReqHead     ReqHead;
  char         SecuID[CODE_LEN+1];//股票代码
  market_type  Market;
  double       Price;            //价格
  int          Num;              //数量
  order_type   Type;
}TOrder_Req;

typedef struct
{
	TAnsHead     AnsHead;
	char         ContractID[SEQ_LEN+1];
}TOrder_Ans;


///////////委托撤单////////////////////////////
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

///////////获取最后错误信息////////////////////
typedef struct
{
	TReqHead     ReqHead;
}TGetLastError_Req;

typedef struct {
	TAnsHead     AnsHead;
	TInterfaceError Error;
}TGetLastError_Ans;


///////////获取帐户信息////////////////////
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

 