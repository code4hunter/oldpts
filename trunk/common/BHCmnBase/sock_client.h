//---------------------------------------------------------------------------
#ifndef sock_clientH
#define sock_clientH
//---------------------------------------------------------------------------
#include <winsock.h>

#define MAX_HOST_NAME_LEN   50

class sock_client
{
private:
  SOCKET        m_Socket;
  char          m_Host[MAX_HOST_NAME_LEN];
  char          m_NetAddr[9];
  char          m_Node[13];
  unsigned int  m_Port;
  
  bool InitSocketTcp(void);
  bool InitSocketSpx(void);
protected:

public:
  sock_client(void);
  ~sock_client(void);

  //If no error occurs, returns 0
  //Otherwise, returns  -1
  int Disconnect(void);

  //If no error occurs, returns 0
  //Otherwise, returns  -1 
  int Connect(const char *szHost, unsigned int Port);//Tcp
  int Connect(const char *szNetAddr, const char *szNode, unsigned int Port);//Spx

  //
  //If no error occurs, send returns the total number of bytes sent.(must be = ASize)
  //Otherwise, a value of SOCKET_ERROR is returned, and a specific error code can be retrieved by calling
  // 
  int SendBuffer(char *ABuf, int ASize);

  //
  //If no error occurs, recv returns the number of bytes received.(must be = ASize)
  //If the connection has been gracefully closed, the return value is zero.
  //Otherwise, a value of SOCKET_ERROR is returned, and a specific error code can be retrieved by calling
  // 
  int RecvBuffer(char *ABuf, int ASize);

  //
  static void AscToHex(char *szDest, char *szSource, int nCount);
};

#endif
