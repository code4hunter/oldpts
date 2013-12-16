//---------------------------------------------------------------------------
#ifndef UHQRecvH
#define UHQRecvH

#include "UHQClient.h"

#ifndef ETFTRD
	#include "UPacketPar.h"
#else
	#include "..\..\Etfs\com\UEPacketPar.h"
#endif

#define HQ_MSG_INITOVER 1
#define HQ_MSG_TERMINATE 2
#define HQ_MSG_RECV 3
#define HQ_MSG_NEWSTOKE 4
//---------------------------------------------------------------------------
class THQRecv : public TPacketParser ,public THQTcpClient
{
private:
  HWND m_handle;
  int  m_msg;
  DWORD m_pack_num;
  bool m_bpostnew;

  virtual void OnNewStock(long index)//index 为新股票行情在内存中的位置
  {
    if(m_bpostnew) PostMessage(m_handle,m_msg,HQ_MSG_NEWSTOKE,index);
  }

public:
  THQRecv(char *host,int port,HWND handle,int msg,bool bpost_stk_msg);
  virtual  ~THQRecv();

  int OnRecv(char *buf, int size);
  void OnTerminate(bool Status);//true---normal,false---abnormal;
  void OnInitOver(void);
};

#endif
