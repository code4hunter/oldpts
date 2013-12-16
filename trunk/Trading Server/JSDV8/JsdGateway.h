/***************************************************************************
  ���˴���Χ����ͨѶ��

  author: wayne 2009-04
  
****************************************************************************/
//---------------------------------------------------------------------------

#ifndef JsdGatewayH
#define JsdGatewayH
//---------------------------------------------------------------------------

#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>

#include <vector>
#include <string>
#include <iostream>

#define DEF_SBUFLEN 32    //����С��������С
#define DEF_LBUFLEN_8192 8192  //����󻺳�����С
#define DEF_LBUFLEN 256    //����С��������С

using namespace std;


/////////////////////////////////////////////////////////////////////////////
// CKDGateway ��֤��һ�����ؽӿ�

class JsdGateway
{
private:

struct tagAnswerPacket //Ӧ���
{
  char szRetCode[DEF_SBUFLEN];  //5������	VARCHAR(10), ��0����ʾ����
  char szRetMsg[DEF_LBUFLEN];   //6������Ϣ	VARCHAR(200),���ط�0���ʾ���״������ĳ�ֽ��״����ϵͳ����(�������ֵ�)
  char szReqFunNop[DEF_SBUFLEN]; //11ԭ�����ܺ�	VARCHAR(20)       2006-4-12����
  char szPacketID[DEF_SBUFLEN];      //11��������к�	VARCHAR(20)       2006-4-12����
  char szReserved[DEF_SBUFLEN]; //�����ֶ�3	VARCHAR(20)

  int bIsNext;    //��������ʾ	CHAR(1),��0�����ޣ���1������ʾ�к����� (ȡ��������99����)
  int iFieldNum;  //Ӧ���ֶ���	VARCHAR(10)
  int iRecNum;    //Ӧ���¼��	VARCHAR(10)
  char *pBuffer;  //ָ�����յ����ݻ�����

  int iHeadLen;  //��ͷ����
  int iDataLen;  //���ݳ���
};

  TIdTCPClient *m_pSocket;

  //���������Ϣ
  char m_szOP_SITE[DEF_SBUFLEN];   //����վ��
  char m_szOP_BRANCH[DEF_SBUFLEN]; //������֧
  char m_szCHANNEL[DEF_SBUFLEN];   //��������
  DWORD m_dwReqPakSN;              //��ͷ���кţ���ֹ����

  char m_szRequestBuffer[DEF_LBUFLEN_8192]; //���󻺳���

  char *m_pSingleRecvBuffer;   //����������
  int m_iSingleRecvBufferSize; //������������С

  vector<string> _retData;


  int  m_iRecNo;           //��¼����
  int  m_iFieldCount;      //�ֶ�����

  int m_timeout;
public:

	int GetRecCount() {return m_iRecNo; }


	JsdGateway(int timeout);
	~JsdGateway();

  //��KDGateway��������
	bool Connect(const char *p_pszIPAddress, WORD p_wPort);

	//��KDGateway�Ͽ�����
	bool Disconnect();

	//���������
	bool SendRequest(const char *p_pszDataSect);

	//Recv�������� //p_bCRC��ʾ�Ƿ�Ҫ���հ�����CRCУ�飬��Ϊǩ����ǲ���ҪУ���
	bool RecvAnswer(tagAnswerPacket *p_pAnswerPacket, bool singlerecord=true,int countOffset=2);

	//��������
  /*
  fieldCount    �����ֶγ��ȣ����ȿɸ�����Ҫ����
  singlerecord  1-������¼  0-������¼
  countOffset   ��singlerecord==0ʱ��Ч  ȡ������¼�к�����¼������¼��λ�ã�
  */
	int WaitAnswer(const char *request,int fieldCount,bool singlerecord=true,int countOffset=2);


  //*****************  ������յ��İ� *****************

  //�õ�Ӧ���¼��������ǵ����������̶�Ϊ1
  //DWORD GetRecNum();

  //�õ�ָ����¼��ָ���ֶΣ�������,���ΪNULL��������GetLastError���õ����Ĵ���
  //char* GetFieldValue(DWORD p_dwRecNo, char *p_pszFieldName, char *p_pszValue, int p_iValueSize);

  string GetFieldValue(int row, int col);     //row ��0��ʼ col��1��ʼ

	//Ϊ�˳���򵥣������õ�ַ��Σ�ע�⻺��������
	//���ð�ͷ����
  inline void SetOP_SITE  (char *p_pszOP_SITE  ) { strncpy(m_szOP_SITE  , p_pszOP_SITE  , DEF_SBUFLEN); };   //����վ��
  inline void SetOP_BRANCH(char *p_pszOP_BRANCH) { strncpy(m_szOP_BRANCH, p_pszOP_BRANCH, DEF_SBUFLEN); };   //������֧
  inline void SetCHANNEL  (char *p_pszCHANNEL  ) { strncpy(m_szCHANNEL  , p_pszCHANNEL  , DEF_SBUFLEN); };   //��������

	//�õ���ͷ����
  inline char *GetOP_SITE  () { return m_szOP_SITE  ; };   //����վ��
  inline char *GetOP_BRANCH() { return m_szOP_BRANCH; };   //������֧
  inline char *GetCHANNEL  () { return m_szCHANNEL  ; };   //��������

  inline char *GetRequestBuffer() { return m_szRequestBuffer; }; //�õ����ͻ�����
  inline char *GetReturnData() { return m_pSingleRecvBuffer; }; //�õ����ͻ�����

};

#endif

