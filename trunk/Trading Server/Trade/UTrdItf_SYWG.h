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
      bool UseDesencrypt;//是否使用DES加密
      char UseProtocol[4];//与AGX使用通讯协议，Tcp,spx,忽略大小写,default:Spx
      unsigned int ServerPort;//端口号
      //使用TCP
      char ServerIP[16];//服务端

      //使用SPX
      char ServerAddr[9];//服务端
      char ServerNode[13];
      
      char ClientAddr[9];//客户端
      char ClientNode[13];

      WORD MajorVer;//客户端协议接口主版本号（用于版本协商）,default:2(???)
      WORD MinorVer;//客户端协议接口次版本号（用于版本协商）,default:0(???)

      WORD SrcDpt;//源营业部编号
      WORD DestDpt; // 目的营业部编号
      char EntrustMethod; //由开发商向申万索取。
      //
    } TSYWGSet;
    //enum SWI_ReturnStatus {rsEqu=0, rsMoreEqu=1, rsMore=2 };//返回状态在何时表示成功，与0作比较，分为==0, 〉=0，〉0，，其他
private:
  TSYWGSet FSYWGSet;
  
  SWSockClient FSafeSock;
  long m_CnID;//分配到的连接标识
  //WORD m_LocalDpt;//本地营业部编号

  char m_AccType; //客户帐号类型
  
  BYTE m_DesKey[16];
  //WORD m_KeyLength;

  int LocalInit(void);//因为连接空闲超时限制值为5分钟，所以如果请求失败，则会试图重新连接一次
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
    int  Init();  //初始化
    int  SetAccount(); //设置帐号++++

    //////查询函数//////
    int  GetTrdInfo();   //取得盘口数据++++
    int  QryMoney();     //资金查询++++
    int  QryStock();     //股份查询 ?????
    int  QryCanBuy();    //取可买数量   ++++++
    int  QryDetail();    //成交查询++++++
    int  QryHisDetail(); //历史成交查询+++++
    int  QryCsn();       //查询某个委托合同 +++++
    int  QryCurCsn();    //当日委托查询  ++++++
    int  QryHisCsn();    //历史委托查询 ++++++
    int  QryCurTrd();    //当日成交查询  ------
    int  QryHisTrd();    //历史成交查询 +++++
    int  QryBill();      //查询资金流水（对帐单）++++++
    int  QryStocks();    //查询帐号中所有的股份 ------

    //////交易函数/////
    int  Buy();
    int  Sell();
    int  Undo(); //委托撤单

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
