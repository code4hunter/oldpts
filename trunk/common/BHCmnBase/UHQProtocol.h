#ifndef UHQProtocolH
#define UHQProtocolH

#include "UDynStr.h"

//request:
#define CMD_LOGIN_REQ    101
#define CMD_CODE_REQ     102
#define CMD_DATA_REQ     103

//answer:
#define CMD_LOGIN_ACK    1001
#define CMD_CODE_ACK     1002
#define CMD_DATA_ACK     1003

//report:
#define CMD_INIT_OK      1004

//error:
#define CMD_LOGIN_ERR    -101
#define CMD_CODE_ERR     -102
#define CMD_DATA_ERR     -103

#define CMD_ERROR        -1
#define CMD_NOT_INIT     -2

struct THQCmd_Head
{
  int Cmd;  //命令
  int Len;  //包长度
  int Rsv; //reserve字段
};

#define MAX_NAME_LEN 20
#define MAX_PASS_LEN 20

struct THQLoginReq
{
  char Name[MAX_NAME_LEN];
  char Pass[MAX_PASS_LEN];
};

//---------------------------------------------------------------------------
enum TCodeType { ctSh=1, ctSz, ctAll, ctCustom };

struct THQCodeAHead
{
  int TolCnt;//总个数
  int ShCnt;
  int SzCnt;
};

struct THQCodeAData
{
  char SecuID[8];           //证券代码        上海  H+股票代码   深圳   S+股票代码
  long SecuNo; //股票在内存中的序号
};

//---------------------------------------------------------------------------

struct THQDataReq
{
  int Type;    //请求类型
  long TolCnt; //请求股票的总个数
  long *SecuNo;//股票在内存中的序号
};

struct THQDataAck
{
  int Count; //将发送的股票数据个数
};

//---------------------------------------------------------------------------

#endif
 