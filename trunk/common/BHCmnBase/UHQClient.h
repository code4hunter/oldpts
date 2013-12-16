#ifndef UHQClientH
#define UHQClientH

#include <windows.h>
#include <winsock.h>
#include "UHQProtocol.h"

class THQTcpClient;

struct TThParams
{
  THQTcpClient* cl;
  HANDLE event;
  SOCKET socket;  
};

class THQTcpClient
{
private:
  SOCKET FSocket;
  DWORD FHost;
  int FPort;

  THQCmd_Head FCmdMsg;

  bool FLoadSk;
  bool FInitSk;
  bool FLogin;
  bool FCanReq;
  
  bool InitSocket(void);

  HANDLE FThHandle;
  DWORD FThID;
  HANDLE FEvent;

  char *FCodeInfo;
  bool SendBuffer(char *ABuf, int ASize);
  bool RecvBuffer(char *ABuf, int ASize);

public:

  THQTcpClient(char* Host, int Port);
  virtual ~THQTcpClient(void);

  TThParams FThParams;
  int Login(void);
  int Init(int *ShCnt=NULL, int *SzCnt=NULL);
  virtual int Request(long *AIndex, int ACount);//AIndex---Index of chosed stocks;
  virtual int Request(int AType);//0---shanghai, 1---shenzhen, 2---all
  void Loginout(void);

  char * GetCodeInfo(void);
	
  virtual int OnRecv(char *buf, int size);
  virtual void OnTerminate(bool Status);//true---normal,false---abnormal;
  virtual void OnInitOver(void);

  virtual int Request(char **code,int count);

	void SetHost(char *Host,int Port)
	{
		FPort = Port;
		FHost = inet_addr(Host);
	}
};

#endif