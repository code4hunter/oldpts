//---------------------------------------------------------------------------
#pragma hdrstop
#include "JsdGateway.h"
#include "UMkhUtils.h"
using namespace TMkhUtils;
//---------------------------------------------------------------------------
#pragma package(smart_init)
/////////////////////////////////////////////////////////////////////////////
// Gateway ���˴��ڻ����ؽӿ�
//---------------------------------------------------------------------------
JsdGateway::JsdGateway()
{
  //��ʼ���������б���
  memset(m_szOP_SITE  , 0, DEF_SBUFLEN);   //����վ��
  memset(m_szOP_BRANCH, 0, DEF_SBUFLEN);   //������֧
  memset(m_szCHANNEL  , 0, DEF_SBUFLEN);   //��������

  memset(m_szRequestBuffer, 0, DEF_LBUFLEN_8192); //���󻺳���
  
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
//��KDGateway��������
bool JsdGateway::Connect(const char *p_pIPAddress, WORD p_wPort)
{
  if (m_pSocket==NULL)
  {//����ͨѶ��
    m_pSocket = new TTcpClient;
    if (m_pSocket==NULL)
    {
      setError(-1,"����ͨѶ��ʧ��");
      return FALSE;
    }
  }
  
  //�رտ��ܵ�����
  if (m_pSocket->getSocket()!= INVALID_SOCKET)
    m_pSocket->close();
  
	if (m_pSocket->connect((char *)p_pIPAddress,p_wPort)!=0)
	{
    setError(-2,"������Χ����ʧ�ܣ�");
		return FALSE;
	}
  return TRUE;
}
	
//��KDGateway�Ͽ�����
//---------------------------------------------------------------------------
bool JsdGateway::Disconnect()
{
  if (m_pSocket==NULL)
	{
    setError(-3,"��δ�ɹ����Ӳ��� Disconnect��");
		return FALSE;
	}
  
  //�رտ��ܵ�����
  if (m_pSocket->getSocket()!= INVALID_SOCKET)
    m_pSocket->close();

  delete m_pSocket;
  m_pSocket = NULL;
  return TRUE;
}

//---------------------------------------------------------------------------
//���������
bool JsdGateway::SendRequest(const char *p_pszDataSect)
{
  //���������а����ֶ������� �߳�ID:�������

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
    setError(-2,"���������ʧ��!");
    return FALSE;
  }

  return TRUE;
}

//---------------------------------------------------------------------------
//Recv��������
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
    setError(-4,"����Ӧ�����ʱ��");
	  return FALSE;
  }

  iLen = m_pSocket->recvBuffer(m_pSingleRecvBuffer, iLen);

  if(iLen<=0)  {
    setError(-502,m_pSocket->getLastError());
    return false;
  }

  TSplit sbuf(m_pSingleRecvBuffer,'|');

  if(sbuf[0].toString()[0] != 'A') {
    setError(-502,"���Ƿ�������-502");
    return false;
  }

//  ��ͷȡ�����ж����к��ֶΣ��Ա��⴮�����
  char szReqPakSN[DEF_SBUFLEN];
  sprintf(szReqPakSN,"%x:%x", GetCurrentThreadId(), m_dwReqPakSN);

  if (strcmp(szReqPakSN,sbuf[2].toChar())!=0)
  {
    m_pSocket->clear(); //�������ִ����������Ϊ��λ�����Ի������ڵ�����ȫ�����
    setError(-6,"Ӧ�������������ݡ�");
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


  //�ж��Ƿ������쳣������ʣ�����ݣ�����о������Ϊ��һ�ν�����׼������ΪЭ������˳���ϵ
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

      m_iRecNo = sbuf[countOffset+2].toInt()+1;    //��¼����+������¼ 

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

  if(p_pAnswerPacket->iRecNum==m_iRecNo) {   //�����Ƿ�����
    p_pAnswerPacket->bIsNext = 0;
  }

  //�������ݽ��
  for(int i=0;i<(m_iFieldCount+3);i++)  {
    _retData.push_back(sbuf[i].toString());
  }

  if(unsigned(p_pAnswerPacket->iRecNum*(m_iFieldCount+3))!=_retData.size()) {
    setError(-501,"���ݽ���ʧ��-501");
    return false;
  }


  return TRUE;
}

//---------------------------------------------------------------------------
//��������
bool JsdGateway::WaitAnswer(const char *p_pszDataSect,int fieldCount,bool singlerecord,int countOffset)
{
  //m_dwTotalDataLen = 0;
  m_iRecNo = 0;

  _retData.clear();

  //��������
  if (SendRequest(p_pszDataSect)!=TRUE)
    return FALSE;
  
  //����Ӧ��
  tagAnswerPacket AnswerPacket;
  memset(&AnswerPacket,0,sizeof(tagAnswerPacket));
  AnswerPacket.iFieldNum = fieldCount;
  m_iFieldCount         = fieldCount;

  if (RecvAnswer(&AnswerPacket,singlerecord,countOffset)!=TRUE)
    return FALSE;
  
  if (atol(AnswerPacket.szRetCode)!=0)
  {
    setError(-8,"����ʧ�ܣ�ErrCode:%s ErrMsg:%s", AnswerPacket.szRetCode, AnswerPacket.szRetMsg);
    return FALSE;
  }

  while(AnswerPacket.bIsNext)
  {
    //��������
    if (SendRequest("0|")!=TRUE) //ȡ��̰�
      return FALSE;
    
    //����Ӧ��
    if (RecvAnswer(&AnswerPacket,singlerecord)!=TRUE)
      return FALSE;
    
    if (atol(AnswerPacket.szRetCode)!=0)
    {
      setError(-8,"����ʧ�ܣ�ErrCode:%s ErrMsg:%s", AnswerPacket.szRetCode, AnswerPacket.szRetMsg);
      return FALSE;
    }
  }
  return TRUE;
}

//---------------------------------------------------------------------------
string JsdGateway::GetFieldValue(int row, int col)
{
  return _retData[(row)*(m_iFieldCount+3)+(col-1+3)];     //+3  ��Ϊ���ݰ���ʼ��3�̶���
}
//---------------------------------------------------------------------------


