//---------------------------------------------------------------------------
#ifndef SWSockClientH
#define SWSockClientH
//---------------------------------------------------------------------------
#include "sock_client.h"

//#define USE_CRC_CHECK
//#define USE_DES_ENCRYPT

///des encrpytion socket
class SWSockClient: public sock_client
{
private:
  bool m_UseDesencrypt;
  BYTE m_DesKey[16];

  //return value: 0---success; 1---need to reconnect to server; -1----error;
  int SendBlock(void *Block, int Size, bool FirstSend=false);

  //return value: 0---success; -1----error;
  int RecvBlock(void *Block, int Size, bool FirstRecv=false);
  
public:
  SWSockClient(void);
  ~SWSockClient(void);

  static void  DesEncrypt(BYTE *Key, char *Buf, int Size);
  static void  DesDecrypt(BYTE *Key, char *Buf, int Size);

  //If no error occurs, returns 0
  //Otherwise, returns  -1 
  int Init(const char *szNetAddr, const char *szNode, unsigned int Port,  \
                          const char *szServerIP, const char *szUseProtocol, bool UseDesencrypt);//建立网络连接
  void SetKey(BYTE* szKey);

  //return value: 0---success, -1---send error, -2---recv error
  int Connect(char *CnnReq, int ReqSize, char *CnnAns, int AnsSize);

  //return value: 0---success, 1---the connection has been gracefully closed, -1----error;
  //int Request(void *ReqBuf, int ReqSize, void *AnsBuf, int AnsSize);//general request and response(no result set)
  int SendRequest(void *ReqBuf, int ReqSize);

  //return value: 0---success, -1----error;
  int RecvAnswer(void *AnsBuf, int AnsSize);

  static WORD CalCRC(void *pData, int nDataLen);
  
};

#endif
