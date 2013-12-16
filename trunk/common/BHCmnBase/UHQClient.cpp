#include "UHQClient.h"
//---------------------------------------------------------------------------
DWORD WINAPI RecvDataTh( LPVOID p);

bool g_Close = false;
//---------------------------------------------------------------------------
THQTcpClient::THQTcpClient(char* Host, int Port)
{
  FInitSk = false;
  FLogin = false;
  FCanReq = false;

  g_Close = false;

  FEvent = NULL;
  FThHandle = NULL;

  FCodeInfo = NULL;

  FPort = Port;
  FHost = inet_addr(Host);

  FLoadSk = true;
  WSADATA wsaData;
  if( WSAStartup( MAKEWORD(2,1), &wsaData)== SOCKET_ERROR)
  {
    FLoadSk = false;
  }
}
//---------------------------------------------------------------------------
THQTcpClient::~THQTcpClient(void)
{
  Loginout();
  WSACleanup();
}
//---------------------------------------------------------------------------
void THQTcpClient::Loginout(void)
{
  //close socket first;
  g_Close = true;

  if(FInitSk)
  {
    shutdown(FSocket, 1);
    closesocket(FSocket);
  }
  
  if(FCodeInfo != NULL)
  {
    delete [] FCodeInfo;
    FCodeInfo = NULL;
  }

  if(FThHandle != NULL)
  {
    WaitForSingleObject(FEvent, INFINITE);
    CloseHandle(FEvent);
    FEvent = NULL;

    CloseHandle(FThHandle);
    FThHandle = NULL;
  }
  else if(FEvent != NULL)
  {
    CloseHandle(FEvent);
    FEvent = NULL;
  }

  FInitSk = false;
}
//---------------------------------------------------------------------------
bool THQTcpClient::InitSocket(void)
{
  if(!FLoadSk)
    return false;

  //create a socket;
  FSocket = socket(AF_INET, SOCK_STREAM, 0);
  if(FSocket == INVALID_SOCKET)
  {
    return false;
  }
  //Init server addr;
  sockaddr_in local;
  local.sin_family = AF_INET;
  local.sin_port = htons(FPort);
  local.sin_addr.S_un.S_addr = FHost;

  //connect server;
  if( connect(FSocket, (LPSOCKADDR)&local, sizeof(local)) == SOCKET_ERROR)
  {
    closesocket(FSocket);
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------
int THQTcpClient::Login(void)
{
  Loginout();
  g_Close = false;

  FEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
  if(FEvent == NULL)
    return -1;

  if(!FInitSk)
    FInitSk = InitSocket();

  if(!FInitSk)
    return -1;
    
  //Init CommandMsg;  
  FCmdMsg.Cmd = CMD_LOGIN_REQ;
  FCmdMsg.Len = 0;
  FCmdMsg.Rsv = 0;

  if(!SendBuffer((char *)&FCmdMsg, sizeof(THQCmd_Head)))
    return -3;

  if(!RecvBuffer((char *)&FCmdMsg, sizeof(THQCmd_Head)))
    return -4;

  if(FCmdMsg.Cmd == CMD_LOGIN_ACK && FCmdMsg.Len == 0)
  {
    FLogin = true;
    return 0;
  }

  return -5;
}
//---------------------------------------------------------------------------
int THQTcpClient::Init(int *ShCnt, int *SzCnt)
{
  if(!FLogin)
    return -1;

  //Init CommandMsg;
  FCmdMsg.Cmd = CMD_CODE_REQ;
  FCmdMsg.Len = 0;
  FCmdMsg.Rsv = 0;

  if(!SendBuffer((char *)&FCmdMsg, sizeof(THQCmd_Head)))
    return -2;

  if(!RecvBuffer((char *)&FCmdMsg, sizeof(THQCmd_Head)))
    return -2;

  if(FCmdMsg.Cmd == CMD_CODE_ACK)
  {
    if(FCmdMsg.Len > 0)
    {
      if(FCodeInfo != NULL)
      {
        delete [] FCodeInfo;
        FCodeInfo = NULL;
      }

      FCodeInfo = new char[FCmdMsg.Len];

      if(!RecvBuffer(FCodeInfo, FCmdMsg.Len))
        return -2;

      if(ShCnt != NULL)
      {
        *ShCnt = ((THQCodeAHead*)FCodeInfo)->ShCnt;
      }
      if(SzCnt != NULL)
      {
        *SzCnt = ((THQCodeAHead*)FCodeInfo)->SzCnt;
      }
    }

    FCanReq = true;
    return 0;
  }

  return -3;
}
//---------------------------------------------------------------------------
char* THQTcpClient::GetCodeInfo(void)
{
  return FCodeInfo;
}
//---------------------------------------------------------------------------
int THQTcpClient::Request(int AType)
{
  if(!FCanReq)
    return -1;
    
  THQDataReq DataReq;
  memset(&DataReq, 0, sizeof(THQDataReq));

  switch(AType)
  {
    case 0:
      DataReq.Type = ctSh;
    break;
    case 1:
      DataReq.Type = ctSz;
    break;
    case 2:
      DataReq.Type = ctAll;
    break;
    default:
      DataReq.Type = ctSh;
  }

  //Init CommandMsg;  
  FCmdMsg.Cmd = CMD_DATA_REQ;
  FCmdMsg.Len = sizeof(THQDataReq);
  FCmdMsg.Rsv = 0;

  //send command;
  if(!SendBuffer((char *)&FCmdMsg, sizeof(THQCmd_Head)))
    return -2;

  //send request;
  if(!SendBuffer((char*)&DataReq, sizeof(THQDataReq)))
    return -3;

  if(FThHandle == NULL)
  {
    //create a thread;
    FThParams.cl = this;
    FThParams.event = FEvent;
    FThParams.socket = FSocket;
    
    FThHandle = CreateThread(NULL,0, RecvDataTh, &FThParams, 0, &FThID);
    if(FThHandle == NULL)
    {
      if(FEvent != NULL)
      {
        CloseHandle(FEvent);
        FEvent = NULL;
      }
      return -4;
    }
  }

  return 0;
}
//---------------------------------------------------------------------------
int THQTcpClient::Request(long *AIndex, int ACount)
{
  if(!FCanReq)
    return -1;

  if(AIndex == NULL || ACount <= 0)
    return -2;

  THQDataReq DataReq;
  memset(&DataReq, 0, sizeof(THQDataReq));

  DataReq.Type = ctCustom;
  DataReq.TolCnt = ACount;

  //Init CommandMsg;
  FCmdMsg.Cmd = CMD_DATA_REQ;
  FCmdMsg.Len = sizeof(THQDataReq)- sizeof(long *) + ACount*sizeof(long *);
  FCmdMsg.Rsv = 0;

  //send command;
  if(!SendBuffer((char*)&FCmdMsg, sizeof(THQCmd_Head)))
    return -2;

  //send request;
  if(!SendBuffer((char*)&DataReq, sizeof(THQDataReq)-sizeof(long *)))
    return -3;

  //send reqest data;
  if(!SendBuffer((char*)AIndex, ACount*sizeof(long *)))
    return -4;

  if(FThHandle == NULL)
  {
    //create a thread;
    FThParams.cl = this;
    FThParams.event = FEvent;
    FThParams.socket = FSocket;
    
    FThHandle = CreateThread(NULL,0, RecvDataTh, &FThParams, 0, &FThID);
    if(FThHandle == NULL)
    {
      if(FEvent != NULL)
      {
        CloseHandle(FEvent);
        FEvent = NULL;
      }
      return -5;
    }
  }
  return 0;
}

//---------------------------------------------------------------------------
bool THQTcpClient::SendBuffer(char *ABuf, int ASize)
{
  int ret = 0;
  int iSendBytes = 0;
  while(iSendBytes < ASize)
  {
    ret = send(FSocket, ABuf + iSendBytes, ASize - iSendBytes, 0);
    if(ret == SOCKET_ERROR || ret == 0)
    {
      return false;
    }

    iSendBytes += ret;
  }
  return true;
}
//---------------------------------------------------------------------------
bool THQTcpClient::RecvBuffer(char *ABuf, int ASize)
{
  int ret = 0;
  int iRecvBytes = 0;
  while(iRecvBytes < ASize)
  {
    ret = recv(FSocket, ABuf + iRecvBytes, ASize - iRecvBytes, 0);
    if(ret == SOCKET_ERROR || ret == 0)
    {
      return false;
    }

    iRecvBytes += ret;
  }
  return true;
}
//---------------------------------------------------------------------------
int THQTcpClient::OnRecv(char *buf, int size)
{
  return 0 ;
}
//---------------------------------------------------------------------------
void THQTcpClient::OnTerminate(bool Status)
{
}
//---------------------------------------------------------------------------
void THQTcpClient::OnInitOver(void)
{
}
//---------------------------------------------------------------------------
DWORD WINAPI RecvDataTh(LPVOID p)
{
  TThParams FParams;
  memcpy(&FParams, (TThParams *)p, sizeof(TThParams));

  THQTcpClient *pClient = FParams.cl;

  SOCKET FSocket;
  memcpy(&FSocket, &FParams.socket, sizeof(SOCKET));

  THQCmd_Head CmdMsg;
  char *pBuf = NULL;
  const int HEAD_SIZE = sizeof(THQCmd_Head);

  while(!g_Close)
  {
    //receive command;
    memset(&CmdMsg, 0, HEAD_SIZE);

    int ret1 = 0;
    int iRecvBytes1 = 0;
    while(!g_Close && iRecvBytes1 < HEAD_SIZE)
    {
      ret1 = recv(FSocket, ((char*)&CmdMsg) + iRecvBytes1, HEAD_SIZE - iRecvBytes1, 0);
      if(ret1 == SOCKET_ERROR || ret1 == 0)
      {
        break;
      }

      iRecvBytes1 += ret1;
    }
    if(iRecvBytes1 != HEAD_SIZE)
      break;

    //receive data;
    if(CmdMsg.Cmd == CMD_DATA_ACK)
    {
      if(CmdMsg.Len > 0)
      {
        __try
        {
          pBuf = new char[CmdMsg.Len];

          int ret2 = 0;
          int iRecvBytes2 = 0;
          while(!g_Close && iRecvBytes2 < CmdMsg.Len)
          {
            ret2 = recv(FSocket, pBuf+iRecvBytes2, CmdMsg.Len - iRecvBytes2, 0);
            if(ret2 == SOCKET_ERROR || ret2 == 0)
            {
              break;
            }

            iRecvBytes2 += ret2;
          }
          if(iRecvBytes2 == CmdMsg.Len)
            pClient->OnRecv(pBuf, CmdMsg.Len);
          else
            break;
        }
        __finally
        {
          if(pBuf != NULL)
          {
            delete [] pBuf;
            pBuf = NULL;
          }
        }
      }
    }
    else if(CmdMsg.Cmd == CMD_INIT_OK)
    {
      pClient->OnInitOver();
    }
  }
  pClient->OnTerminate(g_Close);
  SetEvent(FParams.event);

  return 0;
}
//---------------------------------------------------------------------------

int THQTcpClient::Request(char **code,int count)
{
	int ret=0;

	char * buf=GetCodeInfo();
	if(NULL==buf) 
	{
		ret= -1;
		return ret;
	}

        long *indexs = new long[count]; 
	int n=((THQCodeAHead*)buf)->TolCnt;
	THQCodeAData * cd=(THQCodeAData *)(buf+sizeof(THQCodeAHead));

	for(int j=0;j<count;j++)
	{
		indexs[j]=-1;
		for(int i=0;i<n;i++)
		{
			if(lstrcmpi(cd[i].SecuID,code[j])==0)
			{
				indexs[j]=cd[i].SecuNo;
				break;
			}
		}
	}
	
	ret = Request(indexs,count);

	delete [] indexs;
	return ret;
}