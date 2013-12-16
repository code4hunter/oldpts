//---------------------------------------------------------------------------
#pragma hdrstop

#include "UHQRecv.h"

//---------------------------------------------------------------------------
THQRecv::THQRecv(char *host,int port,HWND handle,int msg,bool bpost_stk_msg):
  TPacketParser(0),THQTcpClient(host,port)
{
  m_handle=handle;
  m_msg=msg;
  m_pack_num=0;
  m_bpostnew=bpost_stk_msg;
}

THQRecv::~THQRecv()
{
}

int THQRecv::OnRecv(char *buf, int size)
{
  this->m_pack_num++;
  this->ReadUDPPackageData(buf);
  PostMessage(m_handle,m_msg,HQ_MSG_RECV,m_pack_num);
  return 0;
}

void THQRecv::OnTerminate(bool Status)
{
  m_pack_num=0;
  PostMessage(m_handle,m_msg,HQ_MSG_TERMINATE,Status);
}

void THQRecv::OnInitOver(void)
{
  PostMessage(m_handle,m_msg,HQ_MSG_INITOVER,0);
}
