//---------------------------------------------------------------------------
#pragma hdrstop
#include "JsdGateway.h"
#include "UMkhUtils.h"
using namespace TMkhUtils;
//---------------------------------------------------------------------------
#pragma package(smart_init)
/////////////////////////////////////////////////////////////////////////////
// Gateway 金仕达期货网关接口
//---------------------------------------------------------------------------
JsdGateway::JsdGateway()
{
  //初始化所有运行变量
  memset(m_szOP_SITE  , 0, DEF_SBUFLEN);   //操作站点
  memset(m_szOP_BRANCH, 0, DEF_SBUFLEN);   //操作分支
  memset(m_szCHANNEL  , 0, DEF_SBUFLEN);   //操作渠道

  memset(m_szRequestBuffer, 0, DEF_LBUFLEN_8192); //请求缓冲区
  
  m_dwReqPakSN = 0;
  m_pSocket = NULL;
  setError(0,"OK.");


  m_iSingleRecvBufferSize = 256*1024L;
  m_pSingleRecvBuffer = new char[m_iSingleRecvBufferSize];
  
  m_iRecNo = 0;
  m_iFieldCount = 0;

}

//---------------------------------------------------------------------------
JsdGateway::~JsdGateway()
{
  if (m_pSocket!=NULL)
    delete m_pSocket;
  delete []m_pSingleRecvBuffer;
  //delete []m_pReturnData;
}

//---------------------------------------------------------------------------
//与KDGateway建立连接
bool JsdGateway::Connect(const char *p_pIPAddress, WORD p_wPort)
{
  if (m_pSocket==NULL)
  {//创建通讯类
    m_pSocket = new TTcpClient;
    if (m_pSocket==NULL)
    {
      setError(-1,"创建通讯类失败");
      return FALSE;
    }
  }
  
  //关闭可能的连接
  if (m_pSocket->getSocket()!= INVALID_SOCKET)
    m_pSocket->close();
  
	if (m_pSocket->connect((char *)p_pIPAddress,p_wPort)!=0)
	{
    setError(-2,"连接外围网关失败！");
		return FALSE;
	}
  return TRUE;
}
	
//与KDGateway断开连接
//---------------------------------------------------------------------------
bool JsdGateway::Disconnect()
{
  if (m_pSocket==NULL)
	{
    setError(-3,"尚未成功连接不能 Disconnect！");
		return FALSE;
	}
  
  //关闭可能的连接
  if (m_pSocket->getSocket()!= INVALID_SOCKET)
    m_pSocket->close();

  delete m_pSocket;
  m_pSocket = NULL;
  return TRUE;
}

//---------------------------------------------------------------------------
//发送请求包
bool JsdGateway::SendRequest(const char *p_pszDataSect)
{
  //在请求序列包内字段内填入 线程ID:请求包数

  if(strcmp(p_pszDataSect,"0|")!=0)
    m_dwReqPakSN++;

  char szReqPakSN[DEF_SBUFLEN];
  sprintf(szReqPakSN,"%x:%x", GetCurrentThreadId(), m_dwReqPakSN);

  sprintf(m_szRequestBuffer,"R|%s|%s|",
    m_szOP_SITE,
    szReqPakSN
  );

  strcat(m_szRequestBuffer,p_pszDataSect);

  if (m_pSocket->sendBuffer(m_szRequestBuffer, strlen(m_szRequestBuffer)+1)<=0)
  {
    setError(-2,"发送请求包失败!");
    return FALSE;
  }

  return TRUE;
}

//---------------------------------------------------------------------------
//Recv接收请答包
bool JsdGateway::RecvAnswer(tagAnswerPacket *p_pAnswerPacket, bool singlerecord,int countOffset)
{
  int iLen;
  int iPos;
  int iHeadLen;
  DWORD dwDataLen;
  char szTemp[DEF_SBUFLEN];
	memset(m_pSingleRecvBuffer, 0, DEF_LBUFLEN_8192);

  iLen = m_pSocket->waitReceive(3);
	if (iLen<=0)
	{
    setError(-4,"接收应答包超时！");
	  return FALSE;
  }

  iLen = m_pSocket->recvBuffer(m_pSingleRecvBuffer, iLen);

  if(iLen<=0)  {
    setError(-502,m_pSocket->getLastError());
    return false;
  }

  TSplit sbuf(m_pSingleRecvBuffer,'|');

  if(sbuf[0].toString()[0] != 'A') {
    setError(-502,"不是返回数据-502");
    return false;
  }

//  包头取到后，判断序列号字段，以避免串户情况
  char szReqPakSN[DEF_SBUFLEN];
  sprintf(szReqPakSN,"%x:%x", GetCurrentThreadId(), m_dwReqPakSN);

  if (strcmp(szReqPakSN,sbuf[2].toChar())!=0)
  {
    m_pSocket->clear(); //出现这种错误可能是因为错位，所以缓冲区内的数据全部清掉
    setError(-6,"应答包非请求包数据。");
	  return FALSE;
  }

  if(sbuf[3].toString()[0]=='N') {

    strcpy(p_pAnswerPacket->szRetMsg, sbuf[4].toChar());
    strcpy(p_pAnswerPacket->szRetCode, sbuf[5].toChar());

    return true;
  }
  else {
    memset(p_pAnswerPacket->szRetCode,0,DEF_SBUFLEN);
  }


  //判断是否还有因异常产生的剩余数据，如果有就清掉，为下一次接收做准备，因为协议依赖顺序关系
  if (m_pSocket->receiveLength()!=0)
  {
    m_pSocket->clear();
  }

  if(singlerecord)  {
    p_pAnswerPacket->bIsNext = 0;
    m_iRecNo = 1;
  }
  else {

    if(p_pAnswerPacket->bIsNext==0) {

      m_iRecNo = sbuf[countOffset+2].toInt()+1;    //记录总数+首条记录 

      if(m_iRecNo<=0) {
        p_pAnswerPacket->bIsNext = 0;
      }
      else {
        p_pAnswerPacket->bIsNext = 1;
      }

      //return true;
    }
  }
  p_pAnswerPacket->iRecNum ++;

  if(p_pAnswerPacket->iRecNum==m_iRecNo) {   //数据是否已满
    p_pAnswerPacket->bIsNext = 0;
  }

  //处理数据结果
  for(int i=0;i<(m_iFieldCount+3);i++)  {
    _retData.push_back(sbuf[i].toString());
  }

  if(unsigned(p_pAnswerPacket->iRecNum*(m_iFieldCount+3))!=_retData.size()) {
    setError(-501,"数据解析失败-501");
    return false;
  }


  return TRUE;
}

//---------------------------------------------------------------------------
//发送请求
bool JsdGateway::WaitAnswer(const char *p_pszDataSect,int fieldCount,bool singlerecord,int countOffset)
{
  //m_dwTotalDataLen = 0;
  m_iRecNo = 0;

  _retData.clear();

  //发送请求
  if (SendRequest(p_pszDataSect)!=TRUE)
    return FALSE;
  
  //接收应答
  tagAnswerPacket AnswerPacket;
  memset(&AnswerPacket,0,sizeof(tagAnswerPacket));
  AnswerPacket.iFieldNum = fieldCount;
  m_iFieldCount         = fieldCount;

  if (RecvAnswer(&AnswerPacket,singlerecord,countOffset)!=TRUE)
    return FALSE;
  
  if (atol(AnswerPacket.szRetCode)!=0)
  {
    setError(-8,"请求失败！ErrCode:%s ErrMsg:%s", AnswerPacket.szRetCode, AnswerPacket.szRetMsg);
    return FALSE;
  }

  while(AnswerPacket.bIsNext)
  {
    //发送请求
    if (SendRequest("0|")!=TRUE) //取后继包
      return FALSE;
    
    //接收应答
    if (RecvAnswer(&AnswerPacket,singlerecord)!=TRUE)
      return FALSE;
    
    if (atol(AnswerPacket.szRetCode)!=0)
    {
      setError(-8,"请求失败！ErrCode:%s ErrMsg:%s", AnswerPacket.szRetCode, AnswerPacket.szRetMsg);
      return FALSE;
    }
  }
  return TRUE;
}

//---------------------------------------------------------------------------
string JsdGateway::GetFieldValue(int row, int col)
{
  return _retData[(row)*(m_iFieldCount+3)+(col-1+3)];     //+3  因为数据包开始有3固定列
}
//---------------------------------------------------------------------------


