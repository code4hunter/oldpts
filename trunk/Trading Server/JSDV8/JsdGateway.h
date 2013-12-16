/***************************************************************************
  金仕达外围网关通讯类

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

#define DEF_SBUFLEN 32    //定义小缓冲区大小
#define DEF_LBUFLEN_8192 8192  //定义大缓冲区大小
#define DEF_LBUFLEN 256    //定义小缓冲区大小

using namespace std;


/////////////////////////////////////////////////////////////////////////////
// CKDGateway 金证新一代网关接口

class JsdGateway
{
private:

struct tagAnswerPacket //应答包
{
  char szRetCode[DEF_SBUFLEN];  //5返回码	VARCHAR(10), “0”表示正常
  char szRetMsg[DEF_LBUFLEN];   //6返回信息	VARCHAR(200),返回非0则表示交易处理出现某种交易错误或系统错误(见数据字典)
  char szReqFunNop[DEF_SBUFLEN]; //11原请求功能号	VARCHAR(20)       2006-4-12增加
  char szPacketID[DEF_SBUFLEN];      //11请求包序列号	VARCHAR(20)       2006-4-12增加
  char szReserved[DEF_SBUFLEN]; //保留字段3	VARCHAR(20)

  int bIsNext;    //后续包标示	CHAR(1),‘0’－无，‘1’－表示有后续包 (取后续包发99请求)
  int iFieldNum;  //应答字段数	VARCHAR(10)
  int iRecNum;    //应答记录数	VARCHAR(10)
  char *pBuffer;  //指到接收的数据缓冲区

  int iHeadLen;  //包头长度
  int iDataLen;  //数据长度
};

  TIdTCPClient *m_pSocket;

  //请求相关信息
  char m_szOP_SITE[DEF_SBUFLEN];   //操作站点
  char m_szOP_BRANCH[DEF_SBUFLEN]; //操作分支
  char m_szCHANNEL[DEF_SBUFLEN];   //操作渠道
  DWORD m_dwReqPakSN;              //包头序列号，防止串户

  char m_szRequestBuffer[DEF_LBUFLEN_8192]; //请求缓冲区

  char *m_pSingleRecvBuffer;   //单包缓冲区
  int m_iSingleRecvBufferSize; //单包缓冲区大小

  vector<string> _retData;


  int  m_iRecNo;           //记录总数
  int  m_iFieldCount;      //字段总数

  int m_timeout;
public:

	int GetRecCount() {return m_iRecNo; }


	JsdGateway(int timeout);
	~JsdGateway();

  //与KDGateway建立连接
	bool Connect(const char *p_pszIPAddress, WORD p_wPort);

	//与KDGateway断开连接
	bool Disconnect();

	//发送请求包
	bool SendRequest(const char *p_pszDataSect);

	//Recv接收请答包 //p_bCRC表示是否要对收包进行CRC校验，因为签入包是不需要校验的
	bool RecvAnswer(tagAnswerPacket *p_pAnswerPacket, bool singlerecord=true,int countOffset=2);

	//发送请求
  /*
  fieldCount    数据字段长度（长度可根据需要调）
  singlerecord  1-单条记录  0-多条记录
  countOffset   在singlerecord==0时有效  取首条记录中后续记录数（记录中位置）
  */
	int WaitAnswer(const char *request,int fieldCount,bool singlerecord=true,int countOffset=2);


  //*****************  处理接收到的包 *****************

  //得到应答记录数，如果是单结果集，则固定为1
  //DWORD GetRecNum();

  //得到指定记录的指定字段，并返回,如果为NULL，可以用GetLastError来得到最后的错误
  //char* GetFieldValue(DWORD p_dwRecNo, char *p_pszFieldName, char *p_pszValue, int p_iValueSize);

  string GetFieldValue(int row, int col);     //row 从0开始 col从1开始

	//为了程序简单，不设置地址入参，注意缓冲区长度
	//设置包头常量
  inline void SetOP_SITE  (char *p_pszOP_SITE  ) { strncpy(m_szOP_SITE  , p_pszOP_SITE  , DEF_SBUFLEN); };   //操作站点
  inline void SetOP_BRANCH(char *p_pszOP_BRANCH) { strncpy(m_szOP_BRANCH, p_pszOP_BRANCH, DEF_SBUFLEN); };   //操作分支
  inline void SetCHANNEL  (char *p_pszCHANNEL  ) { strncpy(m_szCHANNEL  , p_pszCHANNEL  , DEF_SBUFLEN); };   //操作渠道

	//得到包头常量
  inline char *GetOP_SITE  () { return m_szOP_SITE  ; };   //操作站点
  inline char *GetOP_BRANCH() { return m_szOP_BRANCH; };   //操作分支
  inline char *GetCHANNEL  () { return m_szCHANNEL  ; };   //操作渠道

  inline char *GetRequestBuffer() { return m_szRequestBuffer; }; //得到发送缓冲区
  inline char *GetReturnData() { return m_pSingleRecvBuffer; }; //得到发送缓冲区

};

#endif

