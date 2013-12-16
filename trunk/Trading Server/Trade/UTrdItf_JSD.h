//---------------------------------------------------------------------------
#ifndef UTrdItf_JSDH
#define UTrdItf_JSDH
//---------------------------------------------------------------------------
#include "UTrdStruct.h"
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

//const char * DETAIL_STATE = {"已成交", "部分成交", "场内撤单", "部分撤单", "场外撤单", "股票不足", "未成交", "已申报", "撤单请求", "撤单已发"};

enum jsd_entrust_way {zzwt = 1, rjwt, dhwt, kswt, wswt};


class TTrdItf_JSD : public TTrdItfBase
{
public:
    typedef struct
    {
      char   SvrIp[16];
      int    SvrPort;
      int    TimeOut;
      //
      jsd_entrust_way entrust_way;      //操作委托方式
      char   branch_no[4];              //营业部号
      char   money_type;

    } TJSDSet;
private:	// User declarations
    TIdTCPClient *FidTcp;
    TIdIPWatch   *FidIPWatch;    
    TJSDSet FJSDSet;

    AnsiString GetErrorText(int code, char *error);
    //AnsiString ReadFirstData();
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

    //////交易函数/////
    int  Buy();      //-
    int  Sell();     //-
    int  Undo(); //委托撤单-

    virtual bs_type ConvertType(char * type)
    {
      if(strlen(type)>0)
      {
        if (strcmp(type,"买")==0)
          return btBuy;
        else if (strcmp(type, "卖")==0)
          return btSell;
        else
        {
          if(type[0]=='1') return btBuy;
          else if(type[0]=='2') return btSell;
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
public:		// User declarations
    TTrdItf_JSD(TJSDSet *set);
    virtual  ~TTrdItf_JSD();
    void CloseLink(void)
    {
      FidTcp->Disconnect();
    }

};

#endif
