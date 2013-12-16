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
// Gateway ���˴��ڻ����ؽӿ�
//---------------------------------------------------------------------------

JsdGateway::JsdGateway(int timeout)
{
  //��ʼ���������б���
  memset(m_szOP_SITE  , 0, DEF_SBUFLEN);   //����վ��
  memset(m_szOP_BRANCH, 0, DEF_SBUFLEN);   //������֧
  memset(m_szCHANNEL  , 0, DEF_SBUFLEN);   //��������

  memset(m_szRequestBuffer, 0, DEF_LBUFLEN_8192); //���󻺳���
  
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
//��KDGateway��������
bool JsdGateway::Connect(const char *p_pIPAddress, WORD p_wPort)
{
  //�رտ��ܵ�����

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
	
//��KDGateway�Ͽ�����
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
//Recv��������
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

//  ��ͷȡ�����ж����к��ֶΣ��Ա��⴮�����
  char szReqPakSN[DEF_SBUFLEN];
  sprintf(szReqPakSN,"%x:%x", GetCurrentThreadId(), m_dwReqPakSN);

  if (strcmp(szReqPakSN,sbuf.at(2).c_str())!=0)
  {
    //�������ִ����������Ϊ��λ�����Ի������ڵ�����ȫ�����
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
			m_iRecNo =  atoi( sbuf[countOffset+2].c_str() )+1;    //��¼����+������¼

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
    _retData.push_back(sbuf[i]);
  }

  if(unsigned(p_pAnswerPacket->iRecNum*(m_iFieldCount+3))!=_retData.size()) {
    return false;
  }


  return TRUE;
}

//---------------------------------------------------------------------------
//��������
int JsdGateway::WaitAnswer(const char *p_pszDataSect,int fieldCount,bool singlerecord,int countOffset)
{
	//m_dwTotalDataLen = 0;
	m_iRecNo = 0;

	_retData.clear();

	//��������
	if (SendRequest(p_pszDataSect)!=true)
		return ERR_REMOTE_SEND_FAILED;
  
	//����Ӧ��
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
	//��������
		if (SendRequest("0|")!=true) //ȡ��̰�
			return ERR_REMOTE_SEND_FAILED;
    
	//����Ӧ��
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
  return _retData[(row)*(m_iFieldCount+3)+(col-1+3)];     //+3  ��Ϊ���ݰ���ʼ��3�̶���
}
//---------------------------------------------------------------------------


