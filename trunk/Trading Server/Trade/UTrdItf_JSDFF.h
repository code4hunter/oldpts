//---------------------------------------------------------------------------
#ifndef UTrdItf_JSDFFH
#define UTrdItf_JSDFFH
//---------------------------------------------------------------------------
//#include "UTrdStructFF.h"
#include "UTrdItfBase.h"
#include <IdTCPClient.hpp>
#include <IdIPWatch.hpp>
//---------------------------------------------------------------------------
#define DEF_HEAD_LEN            3
#define INDEX(n) n + DEF_HEAD_LEN - 1

#define DEF_ACK_OK              0
#define DEF_ACK_ERROR           -1
#define DEF_TIMEOUT             -100
#define DEF_INVALID_STOCKCODE   -101
#define DEF_OTHER_ERROR         -504

enum jsdff_entrust_way {zzwtff = 1, rjwtff, dhwtff, kswtff, wswtff};

class TTrdItf_JSDFF : public TTrdItfBase
{
public:
    typedef struct
    {
      char   SvrIp[16];
      int    SvrPort;
      int    TimeOut;
      //
      jsdff_entrust_way entrust_way;      //操作委托方式
      char   branch_no[4];              //营业部代码
      char   gw_ver;                    //V6还是V5。。
      char   jysID;                     //交易所代码
      char   seatID[20];                //席位号
      char   sysCenter[20];             //系统中心号
      int    qry_type;
      char   JyCode[20];                    //交易编码
    } TJSDSet;
private:	// User declarations
    TIdTCPClient *FidTcp;
    TIdIPWatch   *FidIPWatch;    
    TJSDSet       FJSDSet;

    AnsiString GetRequestHead(AnsiString FuncNo);
    AnsiString GetErrorText(int code, char *error);
    AnsiString ReadNextData();
    AnsiString ReadFirstData(AnsiString cmd);
    int  SplitData(AnsiString SD, TStringList *lstDD, int count);

    int  Init();  //初始化
    int  SetAccount(); //设置帐号

    //////查询函数//////
    int  GetTrdInfo();   //取得盘口数据
    int  QryMoney();     //资金查询 -
    int  QryStock();     //股份查询
    int  QryCanBuy();    //取可买数量
    int  QryDetail();    //成交查询 -
    int  QryHisDetail(); //历史成交查询
    int  QryCsn();       //查询某个委托合同
    int  QryCurCsn();    //当日委托查询
    int  QryHisCsn();    //历史委托查询
    int  QryCurTrd();    //当日成交查询
    int  QryHisTrd();    //历史成交查询
    int  QryBill();      //查询资金流水（对帐单）
    int  QryStocks();    //查询帐号中所有的股份-
    
    //int  QryMoneyFF();   //资金查询详细

    int QryTrdState(char *Cid);    //委托状态查询
    
    //////交易函数/////
    int  Buy();      //-
    int  Sell();     //-
    int  Undo(); //委托撤单-

    int  QryFutureCode(); //查询代码

    virtual bs_type ConvertType(char * type)
    {
      if(strlen(type)>0)
      {
        if (strcmp(type,"0")==0)
          return btBuy;
        else if (strcmp(type, "1")==0)
          return btSell;
        else
        {
          if(type[0]=='0') return btBuy;
          else if(type[0]=='1') return btSell;
        }
      }

      return btNo;
    }

    virtual wt_state ConvertState(char *state)
    {
      if(lstrcmp(state,"已成交")==0)
        return wscj;
      else if(lstrcmp(state,"场内撤单")==0)
        return wsyc;
      else if(lstrcmp(state,"部分撤单")==0)
        return wsbw;
      else if(lstrcmp(state,"场外撤单")==0)
        return wsyc;
      else if(lstrcmp(state,"股票不足")==0)
        return wsyf;
      else if(lstrcmp(state,"未成交")==0)
        return wsyb;
      else if(lstrcmp(state,"已申报")==0)
        return wsyb;
      else if(lstrcmp(state,"撤单请求")==0)
        return wsdc;
      else if(lstrcmp(state,"撤单已发")==0)
        return wsdc;
      else
        return wsno;
    }

  void DeStr(AnsiString Sour,TStringList* strList,AnsiString DivSign)
  {
    long n= Sour.Length();
    for ( int i=1; i<=n ;i++)
    {
      if( Sour[i] == DivSign[1] )
      {
        Sour[i] = '\r';
      }
    }

    strList->Text = Sour;

    /*
    AnsiString tmpStr;
    Sour  = Sour.Trim();

    for(;;) {
      if(Sour.AnsiPos(DivSign)==0) {break;}
      tmpStr = Sour.SubString(1,Sour.AnsiPos(DivSign)-1).Trim();
      if(tmpStr!="") { strList->Add(tmpStr);         }
      else           { strList->Add("byhd_null_str");}
      Sour = Sour.SubString(Sour.AnsiPos(DivSign)+DivSign.Length(),Sour.Length());
    }
    if(Sour.Trim()!="") {strList->Add(Sour.Trim());}
    */
  }

public:		// User declarations
    TTrdItf_JSDFF(TJSDSet *set);
    virtual  ~TTrdItf_JSDFF();
    void CloseLink(void)
    {
      FidTcp->Disconnect();
    }

};

#endif
