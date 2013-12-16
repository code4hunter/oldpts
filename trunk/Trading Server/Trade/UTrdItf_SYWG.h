//---------------------------------------------------------------------------
#ifndef UTrdItf_SYWGH
#define UTrdItf_SYWGH
//---------------------------------------------------------------------------

#include "UTrdItfBase.h"
#include "UTrdStruct.h"
#include <windows.h>
#include "SWI_Define.h"
#include "SWSockClient.h"

//---------------------------------------------------------------------------
class TTrdItf_SYWG : public TTrdItfBase
{
public:
    typedef struct
    {
      bool UseDesencrypt;//�Ƿ�ʹ��DES����
      char UseProtocol[4];//��AGXʹ��ͨѶЭ�飬Tcp,spx,���Դ�Сд,default:Spx
      unsigned int ServerPort;//�˿ں�
      //ʹ��TCP
      char ServerIP[16];//�����

      //ʹ��SPX
      char ServerAddr[9];//�����
      char ServerNode[13];
      
      char ClientAddr[9];//�ͻ���
      char ClientNode[13];

      WORD MajorVer;//�ͻ���Э��ӿ����汾�ţ����ڰ汾Э�̣�,default:2(???)
      WORD MinorVer;//�ͻ���Э��ӿڴΰ汾�ţ����ڰ汾Э�̣�,default:0(???)

      WORD SrcDpt;//ԴӪҵ�����
      WORD DestDpt; // Ŀ��Ӫҵ�����
      char EntrustMethod; //�ɿ�������������ȡ��
      //
    } TSYWGSet;
    //enum SWI_ReturnStatus {rsEqu=0, rsMoreEqu=1, rsMore=2 };//����״̬�ں�ʱ��ʾ�ɹ�����0���Ƚϣ���Ϊ==0, ��=0����0��������
private:
  TSYWGSet FSYWGSet;
  
  SWSockClient FSafeSock;
  long m_CnID;//���䵽�����ӱ�ʶ
  //WORD m_LocalDpt;//����Ӫҵ�����

  char m_AccType; //�ͻ��ʺ�����
  
  BYTE m_DesKey[16];
  //WORD m_KeyLength;

  int LocalInit(void);//��Ϊ���ӿ��г�ʱ����ֵΪ5���ӣ������������ʧ�ܣ������ͼ��������һ��
  int OpenAccount(char AccountType, char *Account, char *Password);
  bool GetQueryResult(TList *pList, WORD FunNo, int RecordSize, void *Answer, int AnsSize);
  bool CheckStatus(long Status);
  
  int SetRequest(void *ReqBuf, int ReqSize);

  void ReleaseList(TList *pList);
  void ReleaseMemory(char *pMem);

  //SWIMoney <--->double
  double SWIMoneyToDouble(SWIMoney &swMoney);
  void DoubleToSWIMoney(SWIMoney &swMoney, double Money);
  //SWISmallMoney <--->double
  double SWISmallMoneyToDouble(SWISmallMoney &swSMoney);
  void DoubleToSWISmallMoney(SWISmallMoney &swSMoney, double Money);

  TBourse GetBourse(BYTE ExchangeNo);
  BYTE GetExchangeNo(TBourse Bourse);
  //void InitRequest(SWI_BlockHead &Head, WORD Size, WORD FunNo);
  void InitRequest(void *Block, WORD Size, WORD FunNo);
  int Order(char BsType, const char *SecuID, int Num, double Price, TBourse Bourse, void *Block, int Size);
  int QueryEntrust(int StartDate, int EndDate);//yyyymmdd
  //int QueryStocks(char *SecuID, WORD MaxResults);
  void ShowErrorMsg(char *MsgHead, long ErrorNo);
  
private:	// User declarations
    int  Init();  //��ʼ��
    int  SetAccount(); //�����ʺ�++++

    //////��ѯ����//////
    int  GetTrdInfo();   //ȡ���̿�����++++
    int  QryMoney();     //�ʽ��ѯ++++
    int  QryStock();     //�ɷݲ�ѯ ?????
    int  QryCanBuy();    //ȡ��������   ++++++
    int  QryDetail();    //�ɽ���ѯ++++++
    int  QryHisDetail(); //��ʷ�ɽ���ѯ+++++
    int  QryCsn();       //��ѯĳ��ί�к�ͬ +++++
    int  QryCurCsn();    //����ί�в�ѯ  ++++++
    int  QryHisCsn();    //��ʷί�в�ѯ ++++++
    int  QryCurTrd();    //���ճɽ���ѯ  ------
    int  QryHisTrd();    //��ʷ�ɽ���ѯ +++++
    int  QryBill();      //��ѯ�ʽ���ˮ�����ʵ���++++++
    int  QryStocks();    //��ѯ�ʺ������еĹɷ� ------

    //////���׺���/////
    int  Buy();
    int  Sell();
    int  Undo(); //ί�г���

    virtual bs_type ConvertType(char *type)
    {
      return btNo;
    }

    virtual wt_state ConvertState(char *state)
    {
      return wsno;
    }
public:		// User declarations
    TTrdItf_SYWG(TSYWGSet *pSet);
    virtual  ~TTrdItf_SYWG();
    void CloseLink(void);
};

#endif
