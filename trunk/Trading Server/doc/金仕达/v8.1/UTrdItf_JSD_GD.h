//---------------------------------------------------------------------------
#ifndef UTrdItf_JSD_GDH
#define UTrdItf_JSD_GDH
//---------------------------------------------------------------------------
#include "UTrdItfBase.h"
#include "JsdGateway.h"
//#include <Classes.hpp>
//---------------------------------------------------------------------------


//const char * DETAIL_STATE = {"已成交", "部分成交", "场内撤单", "部分撤单", "场外撤单", "股票不足", "未成交", "已申报", "撤单请求", "撤单已发"};



class TTrdItf_JSD_GD : public TTrdItfBase
{
public:
    //enum jsd_entrust_way {zzwt = 1, rjwt, dhwt, kswt, wswt,wzwt,bpwt};

    //;委托方式0--自助、1--热自助、2--电话、3--可视委托、4--网上委托 5-- ETF委托方式  6--bpwt
    typedef struct
    {
      char   SvrIp[16];
      int    SvrPort;
      int    TimeOut;
      //
      int    entrust_way;      //操作委托方式
      char   branch_no[4];              //营业部号
      char   money_type;

    } TJSDSet;
private:	// User declarations

  	JsdGateway *_gateway;

    string ClientIp;

    TJSDSet FJSDSet;

    int  Init();  //初始化
    int  SetAccount(); //设置帐号

    //////查询函数//////
    int  QryQtn();   //取得盘口数据
    int  QryMoney();     //资金查询 -
//    int  QryStock();     //股份查询
    int  QryDetail();    //成交查询 -
    int  QryCurCsn();    //当日委托查询
    int  QryHisCsn();    //历史委托查询
    int  QryCurTrd();    //当日成交查询
    int  QryHisTrd();    //历史成交查询
    int  QryBill();      //查询资金流水（对帐单）
    int  QryStocks();    //查询帐号中所有的股份-
    int  QryETFs();    //查询ETF篮子信息

    //////交易函数/////
    int  Entrust();      //-
    int  Undo(); //委托撤单-

    char ConvertBorS(char * type)
    {
      if(strlen(type)>0)
      {
        if (strcmp(type,"买")==0)
          return 'B';
        else if (strcmp(type, "卖")==0)
          return 'S';
        else
        {
          if(type[0]=='1') return 'B';
          else if(type[0]=='2') return 'S';
        }
      }

      return 'N';
    }

    wt_status ConvertState(char *state)
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

/*市场代码
  0--客户号，*--条码号或磁卡号，#--银行代码
  1--上海A股，2--深圳A股，3--上海B股，4--深圳B股，
*/

  TBourse ConvertBourse(const char *market)
  {
    if(strlen(market)<1) return bsXXX;
    switch(market[0]) {
      case '1': return bsSHS;
      case '2': return bsSZS;
      default:  return bsXXX;
    }
  }  
    
public:		// User declarations
    TTrdItf_JSD_GD(TJSDSet *set);
    virtual  ~TTrdItf_JSD_GD();
    void CloseLink(void)
    {
      _gateway->Disconnect();
    }

};

#endif
