//---------------------------------------------------------------------------
#ifndef UTrdItf_Test2H
#define UTrdItf_Test2H
//---------------------------------------------------------------------------
#include "UTrdStruct.h"
#include "UTrdItfBase.h"

#include <system.hpp>
#include <stdlib.h>
#include <vector>
#include <systdate.h>


struct order
{
  long id;
  char code[20];
  double price;
  long num;
  long cancel;
  bool bcancel;
  long ord_num;
  TDateTime ord_time;
};

typedef std::vector<order> ORDERS;


//---------------------------------------------------------------------------
class TTrdItf_TEST2 : public TTrdItfBase
{
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

    static ORDERS FOrders;
    long FindID(char* id);
    static long FOrderID;

    virtual bs_type ConvertType(char *type)
    {
      return btNo;
    }

    virtual wt_state ConvertState(char *state)
    {
      return wsno;
    }

public:		// User declarations
    TTrdItf_TEST2();
    virtual  ~TTrdItf_TEST2();

    void CloseLink(void)
    {
      return;
    }

};

#endif
