//---------------------------------------------------------------------------
#pragma hdrstop
#include "JsdGateway.h"
#include "uSpliter.h"
#include "UTrdStruct.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdTCPClient"
#pragma link "IdTCPConnection"
/////////////////////////////////////////////////////////////////////////////
// Gateway 金仕达期货网关接口
//---------------------------------------------------------------------------

JsdGateway::JsdGateway(int timeout)
{
  //初始化所有运行变量
  memset(m_szOP_SITE  , 0, DEF_SBUFLEN);   //操作站点
  memset(m_szOP_BRANCH, 0, DEF_SBUFLEN);   //操作分支
  memset(m_szCHANNEL  , 0, DEF_SBUFLEN);   //操作渠道

  memset(m_szRequestBuffer, 0, DEF_LBUFLEN_8192); //请求缓冲区
  
  m_dwReqPakSN = 0;
  m_pSocket = new TIdTCPClient(NULL);

  m_iSingleRecvBufferSize = 256*1024L;
  m_pSingleRecvBuffer = new char[m_iSingleRecvBufferSize];

  m_timeout = timeout;
  m_iRecNo = 0;
  m_iFieldCount = 0;

}

//---------------------------------------------------------------------------
JsdGateway::~JsdGateway()
{
  if (m_pSocket!=NULL)
    delete m_pSocket;
  delete []m_pSingleRecvBuffer;
}

//---------------------------------------------------------------------------
//与KDGateway建立连接
bool JsdGateway::Connect(const char *p_pIPAddress, WORD p_wPort)
{
  //关闭可能的连接

  try
  {
  	m_pSocket->Disconnect();
  }
  catch( ... )
  {

  }

  m_pSocket->Host = p_pIPAddress;
  m_pSocket->Port = p_wPort;

  try
  {
	m_pSocket->Connect();
	m_pSocket->IOHandler->ReadTimeout=m_timeout;
    return TRUE;
  }
  catch(...)
  {
  	return FALSE;
  }
}
	
//与KDGateway断开连接
//---------------------------------------------------------------------------
bool JsdGateway::Disconnect()
{
 	try
  {
  	m_pSocket->Disconnect();
  }
  catch( ... )
  {

  }
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

  try
  {
  	m_pSocket->IOHandler->Write(AnsiString(m_szRequestBuffer));
  }
  catch(...)
  {
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

  TByteDynArray da;
  da.set_length(0);

  try
  {
      m_pSocket->Socket->ReadBytes(da,-1,true);
  }
  catch(...)
  {
	 return false;
  }

  if (da.Length == 0)
  {
      return false;
  }
  
  const char *buf = (const char*)&da[0];

	spliter sbuf(buf,da.Length,'|');


	if(sbuf.at(0).length()==0 || sbuf.at(0)[0] != 'A') {
    return false;
  }

//  包头取到后，判断序列号字段，以避免串户情况
  char szReqPakSN[DEF_SBUFLEN];
  sprintf(szReqPakSN,"%x:%x", GetCurrentThreadId(), m_dwReqPakSN);

  if (strcmp(szReqPakSN,sbuf.at(2).c_str())!=0)
  {
    //出现这种错误可能是因为错位，所以缓冲区内的数据全部清掉
	  return false;
  }

	if(sbuf[3].c_str()[0]=='N') {

		strcpy(p_pAnswerPacket->szRetMsg, sbuf[4].c_str());
		strcpy(p_pAnswerPacket->szRetCode, sbuf[5].c_str());

		return true;
	}
	else {
		memset(p_pAnswerPacket->szRetCode,0,DEF_SBUFLEN);
  }

  if(singlerecord)  {
    p_pAnswerPacket->bIsNext = 0;
    m_iRecNo = 1;
  }
  else {

    if(p_pAnswerPacket->bIsNext==0) {
			m_iRecNo =  atoi( sbuf[countOffset+2].c_str() )+1;    //记录总数+首条记录

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
    _retData.push_back(sbuf[i]);
  }

  if(unsigned(p_pAnswerPacket->iRecNum*(m_iFieldCount+3))!=_retData.size()) {
    return false;
  }


  return TRUE;
}

//---------------------------------------------------------------------------
//发送请求
int JsdGateway::WaitAnswer(const char *p_pszDataSect,int fieldCount,bool singlerecord,int countOffset)
{
	//m_dwTotalDataLen = 0;
	m_iRecNo = 0;

	_retData.clear();

	//发送请求
	if (SendRequest(p_pszDataSect)!=true)
		return ERR_REMOTE_SEND_FAILED;
  
	//接收应答
	tagAnswerPacket AnswerPacket;
	memset(&AnswerPacket,0,sizeof(tagAnswerPacket));
	AnswerPacket.iFieldNum = fieldCount;
	m_iFieldCount         = fieldCount;

	if (RecvAnswer(&AnswerPacket,singlerecord,countOffset)!=true)
	return ERR_REMOTE_RECV_FAILED;
  
	if (atol(AnswerPacket.szRetCode)!=0)
	{
		return -1;
	}

	while(AnswerPacket.bIsNext)
	{
	//发送请求
		if (SendRequest("0|")!=true) //取后继包
			return ERR_REMOTE_SEND_FAILED;
    
	//接收应答
		if (RecvAnswer(&AnswerPacket,singlerecord)!=true)
			return ERR_REMOTE_RECV_FAILED;

		if (atol(AnswerPacket.szRetCode)!=0)
		{
			return -1;
		}
	}
	return 0;
}

//---------------------------------------------------------------------------
string JsdGateway::GetFieldValue(int row, int col)
{
  return _retData[(row)*(m_iFieldCount+3)+(col-1+3)];     //+3  因为数据包开始有3固定列
}
//---------------------------------------------------------------------------


