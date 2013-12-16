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
  int Cmd;  //����
  int Len;  //������
  int Rsv; //reserve�ֶ�
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
  int TolCnt;//�ܸ���
  int ShCnt;
  int SzCnt;
};

struct THQCodeAData
{
  char SecuID[8];           //֤ȯ����        �Ϻ�  H+��Ʊ����   ����   S+��Ʊ����
  long SecuNo; //��Ʊ���ڴ��е����
};

//---------------------------------------------------------------------------

struct THQDataReq
{
  int Type;    //��������
  long TolCnt; //�����Ʊ���ܸ���
  long *SecuNo;//��Ʊ���ڴ��е����
};

struct THQDataAck
{
  int Count; //�����͵Ĺ�Ʊ���ݸ���
};

//---------------------------------------------------------------------------

#endif
 