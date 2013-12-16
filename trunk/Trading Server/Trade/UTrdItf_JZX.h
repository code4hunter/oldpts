//---------------------------------------------------------------------------
#ifndef UTrdItf_JZXH
#define UTrdItf_JZXH
//---------------------------------------------------------------------------

#include "UTrdItfBase.h"
#include "UTrdStruct.h"
#include <windows.h>
#include "kcbpcli.h"

#define JZX_MAX_REC_NUM     "20"//查询每次最多返回记录数
#define JZX_MAX_REC_NUM_INT  20//此值必须与GTJA_MAX_REC_NUM值保持同步
#define QL_MARKET_SH         "1"
#define QL_MARKET_SZ         "0"

//---------------------------------------------------------------------------
class TTrdItf_JZX : public TTrdItfBase
{
public:
    typedef struct
    {
      char ServerName[KCBP_SERVERNAME_MAX+1];/*用户自定义的KCBP服务器名称*/
      //int nProtocal; /*协议类型，0 表示使用TCP*/
      char ServerAddr[KCBP_DESCRIPTION_MAX+1]; /*服务端IP*/
      unsigned int ServerPort;/*服务端端口号*/

      char DptCode[20];//营业部代码
      unsigned int Timeout;//连接超时20

      char UserName[20];
      char Password[20];
      char Operway;//操作方式
      char SendQName[20];///*发送队列名称，由服务端指定*/
      char ReceiveQName[20];///*接收队列名称，由服务端指定*/
    } TJZXSet;
private:
  TJZXSet FGTJASet;
  KCBPCLIHANDLE FHandle;

  int SetSytemParams(char *Funid, bool IsLogin);
  int CheckSqlExecute(void);
  int CheckRsOpen(void);

  int InitRequest(char *Funid, bool IsLogin=false);
  int ExecuteRequest(char *Funid);//return:0--success,100--have more results,

  String FOrderDate;
  int Order(char *BsType, char *SecuID, int Num, double Price, int &OrderNo);

  String FAccountType;
  TStrings *FSrcList, *FDstList;
  int QueryMoreResults(TStrings *pSrcList, TStrings *pDstList);

  char FEnPassword[50];
  int Encrypt(char *pSrc, char *pDst);

  char FCustid[50];
  int GetStkAccount(char *LogType, char *Logid, char *ZJ, char *SH, char *SZ);

  char FBankCode[100];

  char FKey[50];

private:	// User declarations
    int  Init();  //初始化
    int  SetAccount(); //设置帐号

    //////查询函数//////
    int  GetTrdInfo();   //取得盘口数据
    int  QryMoney();     //资金查询
    int  QryStock();     //股份查询
    int  QryCanBuy();    //取可买数量
    int  QryDetail();    //成交查询
    int  QryHisDetail(); //历史成交查询
    int  QryCsn();       //查询某个委托合同
    int  QryCurCsn();    //当日委托查询
    int  QryHisCsn();    //历史委托查询
    int  QryCurTrd();    //当日成交查询
    int  QryHisTrd();    //历史成交查询
    int  QryBill();      //查询资金流水（对帐单）
    int  QryStocks();    //查询帐号中所有的股份

    //////交易函数/////
    int  Buy();
    int  Sell();
    int  Undo(); //委托撤单

    virtual bs_type ConvertType(char *type)
    {
      if(lstrcmpi(type, "B") == 0)
        return btBuy;
      else if(lstrcmpi(type, "S") == 0)
        return btSell;
      //else if(lstrcmpi(type, "1") == 0)//申购？
      //  return btBuy;
      //else if(lstrcmpi(type, "2") == 0)//赎回？
      //  return btSell;
      
      return btNo;
    }

    virtual wt_state ConvertState(char *state)
    {
      //'0','未报' 在lbm中委托成功写入未发标志
      //'1','正报' 在落地方式中,报盘扫描未发委托,并将委托置为正报状态
      // '2','已报' 报盘成功后,报盘机回写发送标志为已报
      //'3','已报待撤' 已报委托撤单
      //'4','部成待撤' 部分成交后委托撤单
      //'5','部撤' 部分成交后撤单成交
      //'6','已撤' 全部撤单成交
      //'7','部成' 已报委托部分成交
      //'8','已成' 委托或撤单全部成交
      //'9','废单' 委托确认为费单 'A','待报' 'B','正报' 国泰模式中，已报道接口库尚未处理返回库的阶段，标准模式不用。
      if(strlen(state)==0) return wsno;
      switch(state[0])
      {
        case '0':
        case '1':
        case 'A':
        case 'B':
          return wswb;
        case '2':
          return wsyb;
        case '3':
        case '4':
          return wsdc;
        case '5':
          return wsbw;
        case '6':
          return wsyc;
        case '7':
          return wsbc;
        case '8':
          return wscj;
        case '9':
          return wsyf;
        default:
          return wsno;
      }
    }
public:		// User declarations
    TTrdItf_JZX(TJZXSet *pSet);
    virtual  ~TTrdItf_JZX();
    void CloseLink(void);
};

#endif
