//---------------------------------------------------------------------------
#pragma hdrstop

#include <assert.h>
#include "DES.CPP"
#include "SWSockClient.h"

#define MAX_RECV_BUF_LEN        512
//---------------------------------------------------------------------------
SWSockClient::SWSockClient(void)
{
  m_UseDesencrypt = false;
  memset(m_DesKey, 0, sizeof(m_DesKey));
}
//---------------------------------------------------------------------------
SWSockClient::~SWSockClient(void)
{
}
//---------------------------------------------------------------------------
void SWSockClient::SetKey(BYTE* szKey)
{
  memset(m_DesKey, 0, sizeof(m_DesKey));
  memcpy(m_DesKey, szKey, 8);
}
//---------------------------------------------------------------------------
int SWSockClient::SendBlock(void *Block, int Size, bool FirstSend)
{
  int nRet = 0;

  WORD wBlockSize = *((WORD*) Block); //WORD wBlockSize = Size;

  *(WORD*)(((char*)Block) + 2) = SWSockClient::CalCRC((char *)Block + 4, wBlockSize - 4);

//Added---20050103
//#ifdef USE_DES_ENCRYPT
  if(m_UseDesencrypt)
  {
    if(!FirstSend)
    {
      int nEncryptBytes = wBlockSize / 8 * 8;
      if(nEncryptBytes > 0)
      {
        SWSockClient::DesEncrypt(m_DesKey, (char*)Block, nEncryptBytes);//加密

        nRet = sock_client::SendBuffer((char *)Block, nEncryptBytes);
        if(nRet == 0 && nRet == SOCKET_ERROR)
          return 1;
      }

      int nRemBytes = wBlockSize % 8;
      if(nRemBytes > 0)
      {
        char szZero[8];
        memset(szZero, 0, 8);
        memcpy(szZero, (char *)Block + nEncryptBytes, nRemBytes);
        SWSockClient::DesEncrypt(m_DesKey, szZero, 8);//加密

        nRet = sock_client::SendBuffer(szZero, 8);
        if(nRet == 0 && nRet == SOCKET_ERROR)
          return 1;
      }
    }
    else
    {
      nRet = sock_client::SendBuffer((char *)Block, wBlockSize);
      if(nRet == 0 || nRet == SOCKET_ERROR)
        return 1;

      int nRemBytes = wBlockSize % 8;
      if(nRemBytes > 0)
      {
        char szZero[8];
        memset(szZero, 0, 8);
        nRet = sock_client::SendBuffer(szZero, 8 - nRemBytes);
        if(nRet == 0 || nRet == SOCKET_ERROR)
          return 1;
      }
    }
  }
  else
  {
//#else
    nRet = sock_client::SendBuffer((char *)Block, wBlockSize);
    if(nRet == 0 || nRet == SOCKET_ERROR)
      return 1;

    int nRemBytes = wBlockSize % 8;
    if(nRemBytes > 0)
    {
      char szZero[8];
      memset(szZero, 0, 8);
      nRet = sock_client::SendBuffer(szZero, 8 - nRemBytes);
      if(nRet == 0 || nRet == SOCKET_ERROR)
        return 1;
    }
  }
//#endif

  return 0;
  
/*
  ////20041231----OK!
  int nDebugSize = (wBlockSize + 7 )/8*8;
  char *pDstBuf = new char[nDebugSize];
  memset(pDstBuf, 0, nDebugSize);
  memcpy(pDstBuf, Block, wBlockSize);

  nRet = sock_client::SendBuffer(pDstBuf, nDebugSize);
  delete [] pDstBuf;

  if(nRet == 0 || nRet == SOCKET_ERROR)
    return 1;

  return 0;
*/
}
//---------------------------------------------------------------------------
int SWSockClient::RecvBlock(void *Block, int Size, bool FirstRecv)
{
  if(Size <= 8)
    return -1;
  
  int nRet = 0;
  WORD wBlockSize = 0;
  memset(Block, 0, Size);//Init;

  nRet = sock_client::RecvBuffer((char *)Block, 8);
  if(nRet == 0 || nRet == SOCKET_ERROR)
    return -1;

  if(!FirstRecv)
  {
//#ifdef USE_DES_ENCRYPT
    if(m_UseDesencrypt)
      SWSockClient::DesDecrypt(m_DesKey, (char*)Block, 8);//解密
//#endif
  }
  
  wBlockSize = *((WORD*) Block);
  if(wBlockSize <= 8)
    return -1;
    
  int nRemBytes = (wBlockSize - 8 + 7) / 8 * 8;
  if(nRemBytes <= MAX_RECV_BUF_LEN)
  {
    char cBuffer[MAX_RECV_BUF_LEN] = {0x0, };
    nRet = sock_client::RecvBuffer(cBuffer, nRemBytes);
    if(nRet == 0 || nRet == SOCKET_ERROR)
      return -1;

    if(!FirstRecv)
    {
//#ifdef USE_DES_ENCRYPT
      if(m_UseDesencrypt)
        SWSockClient::DesDecrypt(m_DesKey, cBuffer, nRemBytes);//解密
//#endif
    }
    memcpy((char *)Block + 8, cBuffer, Size - 8);
  }
  else
  {
    char *pNewBuffer = NULL;
    try
    {
      pNewBuffer = new char[nRemBytes];

      nRet = sock_client::RecvBuffer(pNewBuffer, nRemBytes);
      if(nRet == 0 || nRet == SOCKET_ERROR)
        return -1;

      if(!FirstRecv)
      {
//#ifdef USE_DES_ENCRYPT
        if(m_UseDesencrypt)
          SWSockClient::DesDecrypt(m_DesKey, pNewBuffer, nRemBytes);//解密
//#endif
      }
      memcpy((char *)Block + 8, pNewBuffer, Size - 8);
    }
    __finally
    {
      if(pNewBuffer != NULL)
      {
        delete [] pNewBuffer;
        pNewBuffer = NULL;
      }
    }
  }

  if(wBlockSize == Size)
  {
    WORD wCurCrc = SWSockClient::CalCRC((((char*)Block) + 4), Size - 4);
    WORD wSrcCrc = *(WORD*)(((char*)Block) + 2);
    if(wCurCrc != wSrcCrc)
      return -1;
  }

  return 0;

/*
//20041231----OK!
  if (Size < sizeof(WORD))
    return -1;

  int nRet = 0;
  WORD wBlockSize = 0;
  WORD wNewSize = 0;
  memset(Block, 0, Size);//Init;

  //nRet = sock_client::RecvBuffer((char *)&wBlockSize, sizeof(WORD));
  nRet = sock_client::RecvBuffer((char *)Block, sizeof(SWI_BlockHead));
  if(nRet == 0 || nRet == SOCKET_ERROR)
  {
    int nError = WSAGetLastError();
    return -1;
  }

  //if(UseDes)
  //  SWSockClient::DesDecrypt(m_DesKey, (char*)Block, sizeof(SWI_BlockHead));//解密

  wBlockSize = *((WORD*) Block);

  wNewSize = (wBlockSize <= Size) ?  wBlockSize : Size;

  nRet = sock_client::RecvBuffer(((char*)Block + sizeof(SWI_BlockHead)), wNewSize - sizeof(SWI_BlockHead));

  if(nRet == 0 || nRet == SOCKET_ERROR)
    return -1;

  //if(UseDes)
  //  SWSockClient::DesDecrypt(m_DesKey, (char*)Block+sizeof(SWI_BlockHead), Size-sizeof(SWI_BlockHead));//解密

  if(wBlockSize == wNewSize)
  {
#ifdef USE_CRC_CHECK
    WORD wCurCrc = SWSockClient::CalCRC((((char*)Block) + 4), wNewSize - 4);
    WORD wSrcCrc = *(WORD*)(((char*)Block) + 2);
    if(wCurCrc != wSrcCrc)
      return -1;
#endif

    if(wNewSize % 8 > 0)
    {
      int nRemBytes = 8 - wNewSize % 8;
      char szPad[8];
      sock_client::RecvBuffer(szPad, nRemBytes);
    }
  }
  else
  {
    int nRemBytes = (wBlockSize + 7) / 8 * 8 - wNewSize;
    char szPad[100] = {0x0, 0x0};
    int nRecvBytes = 0;
    while(nRemBytes > 0)
    {
      nRecvBytes = (nRemBytes >= 100) ? 100 : nRemBytes;
      sock_client::RecvBuffer(szPad, nRecvBytes);
      nRemBytes -= nRecvBytes;
    }
  }

  return 0;
  */
}
//---------------------------------------------------------------------------
void  SWSockClient::DesEncrypt(unsigned char *Key, char *Buf, int Size)
{
  if(Size <= 0 || Buf == NULL)
    return;

  desinit(0);//Init
  dessetkey(Key);//set key;(注：8位)
  
  for(int i=0; i<Size/8; i++)
  {
    endes(Buf);
    Buf += 8;
  }
  desdone();
  
/*
//20041231--OK!
  desinit(0);//Init
  dessetkey(Key);//set key;(注：8位)
  
  //加密
  while(Size >= 8)
  {
    endes(Buf);

    Buf += 8;
    Size -= 8;
  }
  
  if(Size > 0)
  {
    char szBuf[9];
    memset(szBuf, 0, 9);
    memcpy(szBuf, Buf, Size);

    endes(szBuf);
    memcpy(Buf, szBuf, 8);
  }
  
  desdone();
*/
}
//---------------------------------------------------------------------------
void  SWSockClient::DesDecrypt(unsigned char *Key, char *Buf, int Size)
{
#ifdef _DEBUG
  assert(Size%8 == 0);
#endif

  if(Size <= 0 || Buf == NULL)
    return;

  desinit(0);//Init
  dessetkey(Key);//set key;(注：8位)
  
  for(int i=0; i<Size/8; i++)
  {
    dedes(Buf);
    Buf += 8;
  }
  desdone();
  
/*
//20041231---OK!    
  desinit(0);//Init
  dessetkey(Key);//set key;(注：8位)
  
  //解密
  while(Size >= 8)
  {
    dedes(Buf);

    Buf += 8;
    Size -= 8;
  }
  
  if(Size > 0)
  {
    char szBuf[9];
    memset(szBuf, 0, 9);
    memcpy(szBuf, Buf, Size);

    dedes(szBuf);
    memcpy(Buf, szBuf, 8);
  }
  
  desdone();
*/
}
//---------------------------------------------------------------------------
int SWSockClient::Init(const char *szNetAddr, const char *szNode, unsigned int Port,  \
                           const char *szServerIP, const char *szUseProtocol, bool UseDesencrypt)
{
  m_UseDesencrypt = UseDesencrypt;
  if(lstrcmpi(szUseProtocol, "TCP") == 0)
    return sock_client::Connect(szServerIP, Port);
  else
    return sock_client::Connect(szNetAddr, szNode, Port);
}
//---------------------------------------------------------------------------
int SWSockClient::Connect(char *CnnReq, int ReqSize, char *CnnAns, int AnsSize)
{
  if(SendBlock(CnnReq, ReqSize, true) != 0)
    return -1;

  if(RecvBlock(CnnAns, AnsSize, true) != 0)
    return -2;

  return 0;
}
//---------------------------------------------------------------------------
int SWSockClient::SendRequest(void *ReqBuf, int ReqSize)
{
  int nRet = SendBlock(ReqBuf, ReqSize);
  if(nRet < 0)
    return -1;
  else if(nRet == 1)//network may be closed;
    return 1;

  return 0;  
}
//---------------------------------------------------------------------------
int SWSockClient::RecvAnswer(void *AnsBuf, int AnsSize)
{
  if( RecvBlock(AnsBuf, AnsSize) != 0)
    return -1;

  return 0;
}
//---------------------------------------------------------------------------
/*int SWSockClient::Request(void *ReqBuf, int ReqSize, void *AnsBuf, int AnsSize)
{
  int nRet = SendBlock(ReqBuf, ReqSize);
  if(nRet < 0)
    return -1;
  else if(nRet == 1)//network may be closed;
    return 1;

  if( RecvBlock(AnsBuf, AnsSize) != 0)
    return -2;

  return 0;
} */
//---------------------------------------------------------------------------
WORD SWSockClient::CalCRC(void *pData, int nDataLen)// provided by sywg;
{
  WORD acc = 0;
  int i;
  unsigned char* Data = (unsigned char*) pData;

  while(nDataLen--)
  {
    acc = acc ^ (*Data++ << 8);
    for(i = 0; i++ < 8; )
    {
      if(acc & 0x8000)
        acc = (acc << 1) ^ 0x1021;
      else
        acc <<= 1;
    }
  }

  // Swap High and Low byte
  i = ( (WORD) ( ((UCHAR)acc) << 8) ) | ((WORD)(acc >> 8));

  return i;
}
//----------------------------------------------------------------------------
