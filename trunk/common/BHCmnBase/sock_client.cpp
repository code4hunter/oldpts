//---------------------------------------------------------------------------
#include <windows.h>
#include <wsipx.h>

#include "sock_client.h"

//---------------------------------------------------------------------------
sock_client::sock_client(void)
{
  m_Socket = INVALID_SOCKET;

  WSADATA wsaData;
  if( WSAStartup( MAKEWORD(2,1), &wsaData) == SOCKET_ERROR)
  {
    throw("WSAStartup failed!");//WSAStartup failed
  }
}
//---------------------------------------------------------------------------
sock_client::~sock_client(void)
{
  Disconnect();
  WSACleanup();
}
//---------------------------------------------------------------------------
int sock_client::Disconnect(void)
{
  if(m_Socket == INVALID_SOCKET)
    return -1;

  shutdown(m_Socket, 1);
  closesocket(m_Socket);
  m_Socket = INVALID_SOCKET;

  return 0;
}

//---------------------------------------------------------------------------
bool sock_client::InitSocketTcp(void)
{
  if(m_Socket != INVALID_SOCKET)
    return false;

  //create a socket;
  m_Socket = socket(AF_INET, SOCK_STREAM, 0);
  if(m_Socket == INVALID_SOCKET)
    return false;

  //Init server addr;
  sockaddr_in addrIn;
  addrIn.sin_family = AF_INET;
  addrIn.sin_port = htons(m_Port);
  addrIn.sin_addr.s_addr = inet_addr(m_Host);;
  if (addrIn.sin_addr.s_addr == INADDR_NONE)
  {
    struct hostent *host = gethostbyname(m_Host);
    CopyMemory(&addrIn.sin_addr, host->h_addr_list[0], host->h_length);
  }
  
  //connect to server;
  if( ::connect(m_Socket, (LPSOCKADDR)&addrIn, sizeof(sockaddr_in)) == SOCKET_ERROR)
    return false;

  return true;
}
//---------------------------------------------------------------------------
UCHAR BtoH(char ch)
{
  if ((ch >= '0') && (ch <= '9'))
  {
    return (ch - '0');
  }
  if ((ch >= 'A') && (ch <= 'F'))
  {
    return (ch - 'A' + 0xA);
  }
  if ((ch >= 'a') && (ch <= 'f'))
  {
    return (ch - 'a' + 0xA);
  }
  return 0;
}
//---------------------------------------------------------------------------
void sock_client::AscToHex(char *szDest, char *szSource, int nCount)
{
  while (nCount--)
  {
    *szDest++ = (BtoH(*szSource++) << 4) + BtoH(*szSource++);
  }

  return;
}
//---------------------------------------------------------------------------
/*int HexCharVal(char c)
{
	if('0' <= c && c <= '9')
		return c - '0';
	else if('A' <= c && c <= 'F')
		return c + 10 - 'A';
	else if('a' <= c && c <= 'f')
		return c + 10 - 'a';
	return 0;
}
//---------------------------------------------------------------------------
void AscToHex(const char* src, BYTE* dest, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		if(src[2 * i] ==0 || src[2 * i + 1] == 0)
			break;
		dest[i] = HexCharVal(src[2 * i])*16 + HexCharVal(src[2 * i + 1]);
	}
	for(; i<len; i++)
		dest[i] = 0;
} */
//---------------------------------------------------------------------------
bool sock_client::InitSocketSpx(void)
{
  //create a socket;
  if(m_Socket != INVALID_SOCKET)
    return false;

  m_Socket = socket(AF_IPX, SOCK_STREAM, NSPROTO_SPX);
  if(m_Socket == INVALID_SOCKET)
    return false;

  //Init server addr;
  SOCKADDR_IPX addrIPX;
  ZeroMemory(&addrIPX, sizeof(SOCKADDR_IPX));
  addrIPX.sa_family = AF_IPX;
  AscToHex(addrIPX.sa_netnum, m_NetAddr, 4);
  AscToHex(addrIPX.sa_nodenum, m_Node, 6);
  addrIPX.sa_socket = htons(m_Port);

  //connect to server;
  if( ::connect(m_Socket, (PSOCKADDR)&addrIPX, sizeof(SOCKADDR_IPX)) != 0)
  {
    int nError = WSAGetLastError();
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------
int sock_client::SendBuffer(char *ABuf, int ASize)
{
  int ret = 0;
  int iSendBytes = 0;
  while(iSendBytes < ASize)
  {
    ret = send(m_Socket, ABuf + iSendBytes, ASize - iSendBytes, 0);
    if(ret == SOCKET_ERROR || ret == 0)
      return ret;

    iSendBytes += ret;
    break;
  }

  return ASize;
}
//---------------------------------------------------------------------------
int sock_client::RecvBuffer(char *ABuf, int ASize)
{
  int ret = 0;
  int iRecvBytes = 0;
  while(iRecvBytes < ASize)
  {
    ret = ::recv(m_Socket, ABuf + iRecvBytes, ASize - iRecvBytes, 0);
    if(ret == SOCKET_ERROR || ret == 0)
    {
      int nError = WSAGetLastError();
      return ret;
    }
    iRecvBytes += ret;
  }
  
  return ASize;
}
//---------------------------------------------------------------------------
int sock_client::Connect(const char * szHost, unsigned int Port)
{
  Disconnect();
  strncpy(m_Host, szHost, MAX_HOST_NAME_LEN);
  m_Port = Port;
  
  if( InitSocketTcp())
    return 0;
  else
    return -1;
}
//---------------------------------------------------------------------------
int sock_client::Connect(const char *szNetAddr, const char *szNode, unsigned int Port)
{
  Disconnect();
  strncpy(m_NetAddr, szNetAddr, 9);
  strncpy(m_Node, szNode, 13);
  m_Port = Port;

  if(InitSocketSpx())
    return 0;
  else
    return -1;
}
//---------------------------------------------------------------------------

