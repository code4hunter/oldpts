//---------------------------------------------------------------------------
//光大证券
//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdItf_JSD_GD.h"
#include "UMkhUtils.h"
using namespace TMkhUtils;
#pragma package(smart_init)

const char * ENTRUST_WAY_GD[8]={"ZZWT","RJWT","DHWT","KSWT","WSWT","WZWT","BPWT"};

//---------------------------------------------------------------------------

TTrdItf_JSD_GD::TTrdItf_JSD_GD(TJSDSet *set)
{
  CopyMemory(&FJSDSet,set,sizeof(TJSDSet));

  _gateway = new JsdGateway;
  if (_gateway==NULL)
  {
    ODS("创建网关类失败！");
    return ;
  }
}

TTrdItf_JSD_GD::~TTrdItf_JSD_GD()
{
	_gateway->Disconnect();
	delete _gateway;
}

//
//AnsiString TTrdItf_JSD_GD::ReadNextData()
//{
//    AnsiString cmd;
//    cmd = stringprintf("R|%s|%s|0|%s|%s|", ClientIp.c_str(),
//        REQUEST_NUM_GD, FJSDSet.branch_no, ENTRUST_WAY_GD[FJSDSet.entrust_way]);
//    return ReadFirstData(cmd);
//}
//




int TTrdItf_JSD_GD::Init()  //初始化
{


  try
  {
    //连接
    ClientIp = string(FRequest.Init.CltIP)+",,"+string(FRequest.Init.CltMAC);
    _gateway->SetOP_SITE  ((char*)ClientIp.c_str());           //操作站点
    _gateway->SetOP_BRANCH(FJSDSet.branch_no);         //操作分支


    if (_gateway->Connect(FJSDSet.SvrIp,FJSDSet.SvrPort)!=TRUE)
    {
      ODS(_gateway->getErrorMsg());
      setErrorMsg(_gateway->getErrorMsg());
      return -1;
    }


  }
  catch (...)
  {
      ODS("连接柜台失败!");
  }

  return 0;
}

//--------------------------------------------------------------------------
// CMD:功能号(2)|发起营业部代码|市场代码|暂时不用|帐号|密码|委托方式|
// 

//--------------------------------------------------------------------------
int TTrdItf_JSD_GD::SetAccount() //设置帐号
{
  string cmd;

  ZeroMemory(&FAccInfo,sizeof(FAccInfo));

  try
  {
   //1.	成功标志：Y  2.	姓名  3.	原输入帐号的实际市场代码  4.	原输入的完整帐号代码
   //5.	货币代码（效验的帐号对应的货币代码返回，客户号返回人民币，代码为1） 6.	客户号

    cmd = stringprintf("1|%s|0||%s|%s|%s|",
        FJSDSet.branch_no,
        FRequest.SetAccount.Account,
        ENTRUST_WAY_GD[FJSDSet.entrust_way], "");

    if (_gateway->WaitAnswer(cmd.c_str(),7)!=TRUE)
    {
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    FJSDSet.money_type = _gateway->GetFieldValue(0,5)[0];

    // 1. 功能号(2)  2.发起营业部代码  3.市场代码  4.暂时不用  5.帐号 6.密码 7.委托方式
    if(FRequest.SetAccount.Sort == asCA)
    {
        cmd = stringprintf("2|%s|0||%s|%s|%s|", FJSDSet.branch_no, FRequest.SetAccount.Account,
            FRequest.SetAccount.PW, ENTRUST_WAY_GD[FJSDSet.entrust_way]);
    }
    else if(FRequest.SetAccount.Sort==asSH)
    {
        cmd = stringprintf("2|%s|1||%s|%s|%s|", FJSDSet.branch_no, FRequest.SetAccount.Account,
            FRequest.SetAccount.PW, ENTRUST_WAY_GD[FJSDSet.entrust_way]);
    }
    else if(FRequest.SetAccount.Sort==asSZ)
    {
        cmd = stringprintf("2|%s|2||%s|%s|%s|", FJSDSet.branch_no, FRequest.SetAccount.Account,
            FRequest.SetAccount.PW, ENTRUST_WAY_GD[FJSDSet.entrust_way]);
    }
    else
        return -1;

    //  首包：1.成功标志  2.姓名     3.客户号   4.市场个数
    //后继包：1.市场代码  2.市场名称 3.股东代码 4.币种代码  5.币种名称
    if (_gateway->WaitAnswer(cmd.c_str(),5,0,4)!=TRUE)
    {
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }
    strncpy(FAccInfo.Capital, _gateway->GetFieldValue(0,3).c_str(), 13);

    for ( int i =1; i<_gateway->GetRecCount(); i++ )
    {
      if (_gateway->GetFieldValue(i,1)[0] == '1')
        strncpy(FAccInfo.SH, _gateway->GetFieldValue(i,3).c_str(), 13);
      else if (_gateway->GetFieldValue(i,1)[0] == '2')
        strncpy(FAccInfo.SZ, _gateway->GetFieldValue(i,3).c_str(), 13);
    }


    strncpy(FAccInfo.PW, FRequest.SetAccount.PW, 13);

    if(FRequest.SetAccount.Sort==asSH)
    {
      lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,13);
    }
    else if(FRequest.SetAccount.Sort==asSZ)
    {
      lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,13);
    }

    if(FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) {
      setErrorMsg("无股东帐号");
      ODS("无股东帐号");
      return -1;
    }

    NewAns(1);
    memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));


  }
  __finally
  {
  }

  return 0;
}

//////查询函数//////
// 即时行情查询（v5.83）－60
int TTrdItf_JSD_GD::QryQtn()   //取得盘口数据
{
	char et;

	switch (FRequest.QryQtn.Bourse)
  {
      case bsSHS : et = '1'; break;
      case bsSZS : et = '2'; break;
      default: return -1;
  }

  //      -----1----|------2-------|----3---|----4---|----5---|----6---|---7----|
  // CMD  功能号(60)|发起营业部代码|市场代码|暂时不用|客户号  |证券代码|委托方式|
  //
  //               1| 2| 3|| 5| 6| 7|
  string cmd;
  cmd = stringprintf("60|%s|%c||%s|%s|%s|",
      FJSDSet.branch_no,                         // 2
      et,                                        // 3
      FAccInfo.Capital,                          // 5
      FRequest.QryQtn.SecuID,            // 6
      ENTRUST_WAY_GD[FJSDSet.entrust_way]);

  try
  {
        //  1.成功标志    2.指数  3.证券代码  4.证券名称    5.最新价  6.涨跌  7.涨跌值
        //  8.幅度        9.最新价成交量     10.总成交金额 11.今开盘 12.昨收盘价
        // 13.当日最高价 14.当日最低价       15.买价1      16.买量1  17.买价2
        // 18.买量2      19.买价3            20.买量3      21.卖价1  22.卖量1
        // 23.卖价2      24.卖量2            25.卖价3      26.卖量3  27.停牌标志
        // 28.涨跌值     29.买价4            30.买量4      31.卖价4  32.卖量4
        // 33.每百元应计利息额               34.国债全价   35.证券类别（大类＋类别）

    if (_gateway->WaitAnswer(cmd.c_str(),35)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    NewAns(1);
    TQryQtn_Ans *gi = &(*FAnswer)[0].QryQtn;
    gi->QtnTick.Last   = toDouble( _gateway->GetFieldValue(0,5).c_str(), -1);
    gi->QtnTick.BuyPrice = toDouble( _gateway->GetFieldValue(0,15).c_str(), -1);
    gi->QtnTick.BuyVol = toInt( _gateway->GetFieldValue(0,16).c_str(), -1);
    gi->QtnTick.SellPrice = toDouble( _gateway->GetFieldValue(0,21).c_str(), -1);
    gi->QtnTick.SellVol = toInt( _gateway->GetFieldValue(0,22).c_str(), -1);

  }
  __finally
  {
  }

  return 0;

}

//查询资金余额和可用资金余额－9
int TTrdItf_JSD_GD::QryMoney()     //资金查询
{

  string cmd;
  cmd = stringprintf("9|%s|%c||%s|",
        FJSDSet.branch_no,                         // 2
        FJSDSet.money_type,                        // 3
        FAccInfo.Capital);                         // 5

  try
  {
        // 1.成功标志  2.资金余额  3.可用资金  4.买入未交收金额  5.卖出未交收金额
        // 6.委托未成交冻结金额    7.货币名称  8.异常冻结资金

    if (_gateway->WaitAnswer(cmd.c_str(),8)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    NewAns(1);
    (*FAnswer)[0].QryMoney.MoneyInfo.Balance = toDouble(_gateway->GetFieldValue(0,2).c_str() ,-1);
    (*FAnswer)[0].QryMoney.MoneyInfo.Available = toDouble(_gateway->GetFieldValue(0,3).c_str(),-1);

  }
  __finally
  {
  }

  return 0;
}




int TTrdItf_JSD_GD::QryDetail()    //成交查询
{
  int reqry_num=0;

HH:

  if(FRequest.QryOrder.OrderID[0]==0) return -1;
	char et;
	switch (FRequest.QryOrder.Bourse)
  {
      case bsSHS : et = '1'; break;
      case bsSZS : et = '2'; break;
      default: return -1;
  }

  string cmd;

  //      -----1----|------2-------|----3---|----4---|--5---|---6----|
  //      功能号(14)|发起营业部代码|市场代码|暂时不用|客户号|起始日期|
  //      -----7----|---------------8--------------|------------------9---------------|
  //      终止日期  |合同号(为空格时查询所有数据)  |证券代码(为空格时查询所有股票数据)|
  //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
  //      最多返回数量|索引日期|索引合同号|委托方式|索引市场代码|排序方式(0-市场代码、1-委托时间、2-委托时间倒序)|
  //


  //               1| 2| 3|| 5| 6| 7| 8|9| |||13|| |
  cmd = stringprintf("14|%s|%c||%s|%s|%s|%s| |1|||%s||0|",
      FJSDSet.branch_no,                         // 2
      et,                                        // 3
      FAccInfo.Capital,                          // 5
      TDateTimex::nowDateString().c_str(),    // 6
      TDateTimex::nowDateString().c_str(),    // 7
      FRequest.QryOrder.OrderID,             // 8
      ENTRUST_WAY_GD[FJSDSet.entrust_way]           // 13
  );

  try
  { //                                 3           5                  9       11                        15
    //A|10.0.38.11|100|B881136426|买|510050|50ETF|100|2.200|64433|0|0.000|0|未成交|13:36:02  |20090818| |W|1|1| |买| |0| |0.00|
    //A|10.0.38.11|100|B881136426|买|510050|50ETF|100|2.200|64433|0|0.000|0|场内撤单|13:36:02|20090818| |2|1|1| |买| |0| |0.00|

    //首包：
    //1.	成功标志：Y  2.	记录个数（后续包个数）
    //后续包：
    //1.	股东帐号    2.	买卖类别名称（V6）3.	证券代码4.	证券名称5.	委托数量6.	委托价格
    //7.	合同号  8.	成交数量9.	成交价格10.	委托状态11.	成交状态12.	委托时间13.	日期14.	出错信息
    //15.	成功标志  16.	市场代码17.	买卖类别标志（新柜台）18.	成交状态标志（新柜台）19.	买卖类别名称（新柜台）
    //20.	错误代码（新柜台）21.	撤单数量（V7.00）22.	委托属性(比如融资买入,融资卖出等等,中文输出)

    if (_gateway->WaitAnswer(cmd.c_str(),20,0)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    int count = toInt(_gateway->GetFieldValue(0,2).c_str() ,0);
    if (count <= 0) return -1;

    NewAns(1);
    (*FAnswer)[0].QryOrder.OrderInfo.MatchQty   = toInt(_gateway->GetFieldValue(1,8).c_str(), 0);
    (*FAnswer)[0].QryOrder.OrderInfo.MatchPrice = toDouble(_gateway->GetFieldValue(1,9).c_str(), -1);
    (*FAnswer)[0].QryOrder.OrderInfo.CancelQty = 0;

    //成交标志
    //0已成交    1部分成交  2场内撤单  3部分撤单   4场外撤单   5股票不足  C撤单请求  D撤单已发
    //W未成交    9 撤单失败   A 部分成交失败    E 撤单已发部分成交

    char ts =  _gateway->GetFieldValue(1,15)[0];
    if(ts=='2' || ts=='4' || (ts=='3' && ((*FAnswer)[0].QryOrder.OrderInfo.MatchQty > 0)))
    {
      if(ts == '3' && ++reqry_num < 3 ) //如果是部撤则再查直到 reqry_num >3
      {
        Sleep(100);
        goto HH;
      }

      int csnnum = toInt(_gateway->GetFieldValue(1,5).c_str(), 0);
      (*FAnswer)[0].QryOrder.OrderInfo.CancelQty = (*FAnswer)[0].QryOrder.OrderInfo.MatchQty - csnnum ;
    }

  }
  __finally
  {
  }
  return 0;
}


int TTrdItf_JSD_GD::QryCurCsn()    //当日委托查询
{
  string cmd;

  //      -----1----|------2-------|----3---|----4---|--5---|---6----|
  //      功能号(14)|发起营业部代码|市场代码|暂时不用|客户号|起始日期|
  //      -----7----|---------------8--------------|------------------9---------------|
  //      终止日期  |合同号(为空格时查询所有数据)  |证券代码(为空格时查询所有股票数据)|
  //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
  //      最多返回数量|索引日期|索引合同号|委托方式|索引市场代码|排序方式(0-市场代码、1-委托时间、2-委托时间倒序)|
  //
  //               1| 2| 3|| 5| 6| 7|8|9|10|11|12|13|14| |
  cmd =stringprintf("14|%s|%c||%s|%s|%s| | |%d|%s|%s|%s|%s|0|",
      FJSDSet.branch_no,                          // 2
      ' ',                                        // 3
      FAccInfo.Capital,                           // 5
      TDateTimex::nowDateString().c_str(),                               // 6
      TDateTimex::nowDateString().c_str(),                               // 7
      100,                                       // 10
      "",                            // 11
      "",                      // 12
      ENTRUST_WAY_GD[FJSDSet.entrust_way],           // 13
      ""                         // 14
  );

  try
  {
        // 1.股东帐号 2.买卖类别  3.证券代码  4.证券名称  5.委托数量  6.委托价格
        // 7.合同号   8.成交数量  9.成交价格 10.委托状态 11.成交状态 12.成交时间
        //13.日期    14.出错信息 15.成功标志 16.市场代码

    if (_gateway->WaitAnswer(cmd.c_str(),16,0)!=TRUE)
    {
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    int count = toInt(_gateway->GetFieldValue(0,2).c_str() ,0);
    if (count < 0) return -1;

    NewAns(_gateway->GetRecCount()-1);

    for ( int i =1; i<_gateway->GetRecCount(); i++ )
    {
      TOrderInfo *ci = &(*FAnswer)[i-1].QryOrder.OrderInfo;
      memset(ci, 0, sizeof(TOrderInfo));

      strncpy(ci->OrderID,_gateway->GetFieldValue(i,7).c_str(), 8);
      strncpy(ci->SecuID,    _gateway->GetFieldValue(i,3).c_str(), 7);
      strncpy(ci->SecuDesc,  _gateway->GetFieldValue(i,4).c_str(), 8);
      ci->Time = toInt(_gateway->GetFieldValue(i,12).c_str(), 0);
      ci->Date = toInt(_gateway->GetFieldValue(i,13).c_str(), 0);

      //ci->Bourse = _gateway->GetFieldValue(i,16)[0] - 1;

      ci->BorS =ConvertBorS((char*)_gateway->GetFieldValue(i,2).c_str());

      ci->OrderStatus  = 'N';
      ci->OrderQty = toInt(_gateway->GetFieldValue(i,5).c_str(), -1);
      ci->MatchQty = toInt(_gateway->GetFieldValue(i,8).c_str(), -1);
      ci->CancelQty = 0;
      ci->OrderPrice  = toDouble(_gateway->GetFieldValue(i,6).c_str(), -1);
      ci->MatchPrice  = toDouble(_gateway->GetFieldValue(i,9).c_str(), -1);

      char ts =  _gateway->GetFieldValue(i,15)[0];
      if(ts=='2' || ts=='4' || (ts=='3' && (*FAnswer)[0].QryOrder.OrderInfo.MatchQty > 0))
      {
        int csnnum = toInt(_gateway->GetFieldValue(i,5).c_str(), 0);
        ci->CancelQty = ci->MatchQty - csnnum ;
      }
      ci->Bourse = ConvertBourse(_gateway->GetFieldValue(i,16).c_str());

    }
  }
  __finally
  {
  }

  return 0;
}

int TTrdItf_JSD_GD::QryHisCsn()    //历史委托查询
{
  string cmd;

  //      -----1----|------2-------|----3---|----4---|--5---|---6----|
  //      功能号(14)|发起营业部代码|市场代码|暂时不用|客户号|起始日期|
  //      -----7----|---------------8--------------|------------------9---------------|
  //      终止日期  |合同号(为空格时查询所有数据)  |证券代码(为空格时查询所有股票数据)|
  //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
  //      最多返回数量|索引日期|索引合同号|委托方式|索引市场代码|排序方式(0-市场代码、1-委托时间、2-委托时间倒序)|
  //
  //               1| 2| 3|| 5| 6| 7|8|9|10|11|12|13|14| |
  cmd = stringprintf("14|%s|%c||%s|%d|%d| | |%d|%s|%s|%s|%s|0|",
      FJSDSet.branch_no,                          // 2
      ' ',                                        // 3
      FAccInfo.Capital,                           // 5
      FRequest.QryOrder.StartDate,                // 6
      FRequest.QryOrder.EndDate,                  // 7
      1000,                                       // 10
      "",                            // 11
      "",                      // 12
      ENTRUST_WAY_GD[FJSDSet.entrust_way],           // 13
      ""                         // 14
  );

  try
  {
        // 1.股东帐号 2.买卖类别  3.证券代码  4.证券名称  5.委托数量  6.委托价格
        // 7.合同号   8.成交数量  9.成交价格 10.委托状态 11.成交状态 12.成交时间
        //13.日期    14.出错信息 15.成功标志 16.市场代码

    if (_gateway->WaitAnswer(cmd.c_str(),16,0)!=TRUE)
    {
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());
      return -1;
    }

    int count = toInt(_gateway->GetFieldValue(0,2).c_str() ,0);
    if (count < 0) return -1;

    NewAns(_gateway->GetRecCount()-1);

    for ( int i =1; i<_gateway->GetRecCount(); i++ )
    {
      TOrderInfo *ci = &(*FAnswer)[i-1].QryOrder.OrderInfo;
      memset(ci, 0, sizeof(TOrderInfo));

      strncpy(ci->OrderID,_gateway->GetFieldValue(i,7).c_str(), 8);
      strncpy(ci->SecuID,    _gateway->GetFieldValue(i,3).c_str(), 7);
      strncpy(ci->SecuDesc,  _gateway->GetFieldValue(i,4).c_str(), 8);
      ci->Time = toInt(_gateway->GetFieldValue(i,12).c_str(), 0);
      ci->Date = toInt(_gateway->GetFieldValue(i,13).c_str(), 0);

      //ci->Bourse = _gateway->GetFieldValue(i,16)[0] - 1;

      ci->BorS =ConvertBorS((char*)_gateway->GetFieldValue(i,2).c_str());

      ci->OrderStatus  = 'N';
      ci->OrderQty = toInt(_gateway->GetFieldValue(i,5).c_str(), -1);
      ci->MatchQty = toInt(_gateway->GetFieldValue(i,8).c_str(), -1);
      ci->CancelQty = 0;
      ci->OrderPrice  = toDouble(_gateway->GetFieldValue(i,6).c_str(), -1);
      ci->MatchPrice  = toDouble(_gateway->GetFieldValue(i,9).c_str(), -1);

      char ts =  _gateway->GetFieldValue(i,15)[0];
      if(ts=='2' || ts=='4' || (ts=='3' && (*FAnswer)[0].QryOrder.OrderInfo.MatchQty > 0))
      {
        int csnnum = toInt(_gateway->GetFieldValue(i,5).c_str(), 0);
        ci->CancelQty = ci->MatchQty - csnnum ;
      }

      ci->Bourse = ConvertBourse(_gateway->GetFieldValue(i,16).c_str());
    }

  }
  __finally
  {
  }

  return 0;
}

int TTrdItf_JSD_GD::QryCurTrd()    //当日成交查询
{
  string cmd;

    //  1.功能号(13)   2.发起营业部代码  3.市场代码     4.暂时不用      5.客户号
    //  6.最多返回数量 7.索引证券代码    8.索引股东帐号 9.索引成交编号 10.委托方式
    // 11.索引市场代码（v5.83，当市场代码=0查询所有时必须添入）
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|
  cmd = stringprintf("13|%s|%c||%s|%d|%s|%s|%s|%s|%s|",
      FJSDSet.branch_no,                          // 2
      ' ',                                        // 3
      FAccInfo.Capital,                           // 5
      100,                                       // 6
      "",                           // 7
      "",                          // 8
      "",                           // 9
      ENTRUST_WAY_GD[FJSDSet.entrust_way],           // 10
      ""                         // 11
  );

  try
  {
      //
      // 1.股东帐号 2.买卖类别  3.证券代码  4.证券名称  5.成交数量  6.成交价格
      // 7.成交时间 8.成交编号  9.合同号码 10.市场代码（9-10为v5.83实现）
      //
    if (_gateway->WaitAnswer(cmd.c_str(),10,false)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    int count = toInt(_gateway->GetFieldValue(0,2).c_str() ,0);
    if (count < 0) return -1;

    NewAns(_gateway->GetRecCount()-1);

    for (int i = 1; i < _gateway->GetRecCount(); i++)
    {
      TTradeInfo *ti = &(*FAnswer)[i-1].QryTrd.TrdInfo;
      memset(ti, 0, sizeof(TTradeInfo));

      strncpy(ti->SecuID,   _gateway->GetFieldValue(i,3).c_str(), 7);
      strncpy(ti->SecuDesc, _gateway->GetFieldValue(i,4).c_str(), 8);
      ti->Time=     toInt(_gateway->GetFieldValue(i,7).c_str(), 0);
      ti->Date=     TDateTimex::nowDateInt();
      ti->BorS  = ConvertBorS((char*)_gateway->GetFieldValue(i,2).c_str());
      ti->MatchQty   = toInt(_gateway->GetFieldValue(i,5).c_str(), -1);
      ti->MatchPrice = toDouble(_gateway->GetFieldValue(i,6).c_str(), -1);
      ti->Bourse = ConvertBourse(_gateway->GetFieldValue(i,10).c_str());

    }

  }
  __finally
  {
  }

  return 0;
}

int TTrdItf_JSD_GD::QryHisTrd()    //历史成交查询
{
  string cmd;


  //  1.功能号(62)  2.发起营业部代码  3.货币代码   4.暂时不用      5.客户号
  //  6.起始日期    7.终止日期        8.索引流水号 9.最多返回数量 10.委托方式
  //
  //               1| 2| 3|| 5| 6| 7| 8| 9|10|
  cmd = stringprintf("62|%s|%c||%s|%d|%d|%s|%d|%s|",
      FJSDSet.branch_no,                          // 2
      FJSDSet.money_type,                         // 3
      FAccInfo.Capital,                           // 5
      FRequest.QryTrd.StartDate,                // 6
      FRequest.QryTrd.EndDate,                  // 7
      "",                              // 8
      1000,                                       // 9
      ENTRUST_WAY_GD[FJSDSet.entrust_way]            // 10
  );

  try
  {

        // 1.成交日期  2.股东代码  3.买卖标志  4.证券代码  5.证券名称  6.成交数量
        // 7.成交价格  8.成交金额  9.变动金额 10.资金余额 11.股票余额 12.佣金
        //13.印花税   14.过户费   15.其他费用 16.成交时间 17.合同编号 18.成交编号
        //19."1"买"2"卖           20.流水号(=8位日期+6位序号)         21.成交数量abs

    if (_gateway->WaitAnswer(cmd.c_str(),21,false)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    //int count = toInt(_gateway->GetFieldValue(0,2).c_str(),0);

    NewAns(_gateway->GetRecCount()-1);

    for (int i = 1; i < _gateway->GetRecCount(); i++)
    {
      TTradeInfo *ti = &(*FAnswer)[i-1].QryTrd.TrdInfo;
      memset(ti, 0, sizeof(TTradeInfo));

      strncpy(ti->SecuID,   _gateway->GetFieldValue(i,4).c_str(), 7);
      strncpy(ti->SecuDesc, _gateway->GetFieldValue(i,5).c_str(), 8);
      ti->Time=     toInt(_gateway->GetFieldValue(i,16).c_str(), 0);
      ti->Date=     toInt(_gateway->GetFieldValue(i,1).c_str(), 0);
      ti->BorS  = ConvertBorS((char*)_gateway->GetFieldValue(i,19).c_str());
      ti->MatchQty   = toInt(_gateway->GetFieldValue(i,6).c_str(), -1);
      ti->MatchPrice = toDouble(_gateway->GetFieldValue(i,7).c_str(), -1);

    }
  }
  __finally
  {
  }

  return 0;
}

int TTrdItf_JSD_GD::QryBill()      //查询资金流水（对帐单）
{
  string cmd;

  //
  //  1.功能号(11)  2.发起营业部代码  3.市场代码  4.暂时不用     5.客户号
  //  6.币种代码    7.起始日期        8.终止日期  9.索引流水号  10.最多返回数量
  // 11.委托方式
  //
  //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|
  cmd = stringprintf("11|%s|%c||%s|%c|%d|%d|%s|%d|%s|",
      FJSDSet.branch_no,                          // 2
      ' ',                                        // 3
      FAccInfo.Capital,                           // 5
      FJSDSet.money_type,                         // 6
      FRequest.QryBill.StartDate,                  // 7
      FRequest.QryBill.EndDate,                    // 8
      "",                              // 9
      100,                                       // 10
      ENTRUST_WAY_GD[FJSDSet.entrust_way]            // 11
  );

  try
  {
      // 1.摘要   2.变动金额  3.本次余额  4.股东帐号  5.证券代码  6.买卖类别
      // 7.成交数 8.成交价    9.成交编号 10.流水号   11.摘要类别 12.合同号码（v5.81.2）

    if (_gateway->WaitAnswer(cmd.c_str(),12,false)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    //int count = toInt(_gateway->GetFieldValue(0,2).c_str(),0);

    NewAns(_gateway->GetRecCount()-1);

    for (int i = 1; i < _gateway->GetRecCount(); i++)
    {
      TFundInfo *ti = &(*FAnswer)[i-1].QryBill.FundInfo;
      memset(ti, 0, sizeof(TFundInfo));

      strncpy(ti->SecuID,   _gateway->GetFieldValue(i,5).c_str(), 7);
//      strncpy(ti->SecuDesc, _gateway->GetFieldValue(i,5).c_str(), 8);
//      ti->Time=     toInt(_gateway->GetFieldValue(i,16).c_str(), 0);
//      ti->Date=     toInt(_gateway->GetFieldValue(i,1).c_str(), 0);
      ti->BorS  = ConvertBorS((char*)_gateway->GetFieldValue(i,6).c_str());
      ti->MatchQty   = toInt(_gateway->GetFieldValue(i,7).c_str(), -1);
      ti->MatchPrice = toDouble(_gateway->GetFieldValue(i,8).c_str(), -1);
      ti->FundEffect = toDouble(_gateway->GetFieldValue(i,2).c_str(), -1);
      ti->FundBal    = toDouble(_gateway->GetFieldValue(i,3).c_str(), -1);

      ti->Bourse = FRequest.QryStocks.Bourse;

    }
  }
  __finally
  {
  }

  return 0;
}


int TTrdItf_JSD_GD::QryStocks()    //查询帐号中所有的股份
{
  if(FRequest.QryStocks.QryType==2 && FRequest.QryStocks.EtfUnit>0)
    return QryETFs();
  else if(FRequest.QryStocks.QryType==1) {

    char et;
    switch (FRequest.QryStocks.Bourse)
    {
      case bsSHS : et = '1'; break;
      case bsSZS : et = '2'; break;
      case bsXXX : et = '1'; break;
      default: return -1;
    }

    string cmd;
    //CMD 1.功能号(56) 2.发起营业部代码 3.市场代码 4.暂时不用 5.客户号 6.查询市场代码（空格表示所有市场）|
    //    7.查询证券代码（为空格时表示查询所有股票，否则只查询某一只股票情况）|
    //    8.股东代码（空格表示所有股东代码）9.索引市场代码 10.索引证券代码 11.索引股东帐号
    //    12.最多返回数量 13.操作功能（1明细、2汇总）14.委托方式
    //    15.货币代码（v5.20.2实现：当查询市场代码为空而货币代码不为空时，则查询该货币的市场{沪A和深A}）|
    //    16.是否返回合计值（1：返回合计值，其他不返回）17.点评起始日期（为空，则不输出点评信息）|
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|12| |14|15|16||
    cmd = stringprintf("56|%s|%c||%s|%c|%s|%s|%s|%s|%s|%d|1|%s|%c|-1||",
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        et,                                        // 6
        FRequest.QryStocks.SecuID,              // 7
        et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 8
        "",                                        // 9
        "",                                        // 10
        "",                                        // 11
        1,                                         // 12
        ENTRUST_WAY_GD[FJSDSet.entrust_way],          // 14
        FJSDSet.money_type);                       // 15

    try
    {
      //  1.市场代码  2.股东帐号   3.证券代码 4.证券名称  5.余额(加上当日成交)
      //  6.可用余额  7.当日买入成交数量      8.当日卖出未成交数量  9.当日买入成交金额
      // 10.成本价格 11.最新价    12.市值    13.浮动盈亏 14.当日卖出成交金额
      // 15.点评日期 16.一句话点评信息       17.国债净价 18.每百元应计利息(不是国债为0)

      if (_gateway->WaitAnswer(cmd.c_str(),18,false)!=TRUE)
      {
        setErrorMsg(_gateway->getErrorMsg());
        ODS("请求失败！[%s]",_gateway->getErrorMsg());
        ODS("请求包: [%s]",_gateway->GetRequestBuffer());

        return -1;
      }

      int count = toInt(_gateway->GetFieldValue(0,2).c_str(),0);
      if (count <= 0) return -1;

      NewAns(1);

      TStockInfo *ti = &(*FAnswer)[0].QryStocks.StockInfo;
      memset(ti, 0, sizeof(TStockInfo));

      ti->BalQty    = toInt(_gateway->GetFieldValue(1,5).c_str(), -1);
      ti->AvlQty    = toDouble(_gateway->GetFieldValue(1,6).c_str(), -1);
    }
    __finally
    {
    }

    return 0;

  }


  string idxStock = "";
  string idxAcc   = "";
  string idxMart  = "";
  string cmd;

	char et;
	switch (FRequest.QryStocks.Bourse)
    {
        case bsSHS : et = '1'; break;
        case bsSZS : et = '2'; break;
        default: return -1;
    }

    //    ----1-----|-------2------|----3---|---4----|---5--|----------------6---------------|
    //CMD 功能号(10)|发起营业部代码|市场代码|暂时不用|客户号|查询市场代码（空格表示所有市场）|
    //    --------------------------------7---------------------------------|
    //    查询证券代码（为空格时表示查询所有股票，否则只查询某一只股票情况）|
    //    ---------------8----------------|-----9------|-----10-----|-----11-----|
    //    股东代码（空格表示所有股东代码）|索引市场代码|索引证券代码|索引股东帐号|
    //    -----12-----|-----------13-----------|---14---|
    //    最多返回数量|操作功能（1明细、2汇总）|委托方式|
    //    -----------------------------------------15------------------------------------------------|
    //    货币代码（v5.20.2实现：当查询市场代码为空而货币代码不为空时，则查询该货币的市场{沪A和深A}）|
    //    -------------------16----------------------|-----------------17-------------------|
    //    是否返回合计值（1：返回合计值，其他不返回）|点评起始日期（为空，则不输出点评信息）|
    //
    //                 1| 2| 3|| 5| 6|7| 8| 9|10|11|12| |14||16||
  cmd = stringprintf("10|%s|%c||%s|%c| |%s|%s|%s|%s|%d|1|%s||||",       //光大新文档说16必须填空
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        et,                                        // 6
        et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 8
        idxMart.c_str(),                           // 9
        idxStock.c_str(),                          // 10
        idxAcc.c_str(),                            // 11
        1000,                                      // 12
        ENTRUST_WAY_GD[FJSDSet.entrust_way]);         // 14

    try
    {

      //[3]A|10.0.38.11|100|2|0800044619|002282|博深工具|500|500|5750.000|0.000|11.500|11.500|500|5750.000|0.000| | |11.500|0.000|11.500| 
      //  1.市场代码  2.股东帐号   3.证券代码        4.证券名称  5.余额(加上当日成交)
      //  6.可用余额  7.市值(当日) 8.浮动盈亏(当日)  9.成本价格 10.行情最新价
      // 11.昨日库存数量          12.股票市值(昨日) 13.浮动盈亏(昨日库存)
      // 14.点评日期              15.一句话点评信息 16.国债净价 17.每百元应计利息(不是国债为0)

    if (_gateway->WaitAnswer(cmd.c_str(),17,false)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    //int count = toInt(_gateway->GetFieldValue(0,2).c_str(),0);

    NewAns(_gateway->GetRecCount()-1);

    for (int i = 1; i < _gateway->GetRecCount(); i++)
    {
      TStockInfo *ti = &(*FAnswer)[i-1].QryStocks.StockInfo;
      memset(ti, 0, sizeof(TStockInfo));

      strncpy(ti->SecuID,   _gateway->GetFieldValue(i,3).c_str(), 7);
      strncpy(ti->SecuDesc, _gateway->GetFieldValue(i,4).c_str(), 8);
      ti->BalQty    = toInt(_gateway->GetFieldValue(i,5).c_str(), -1);
      ti->AvlQty    = toDouble(_gateway->GetFieldValue(i,6).c_str(), -1);
      ti->FloatProfit  = toDouble(_gateway->GetFieldValue(i,8).c_str(), -1);
      ti->CostPrice     = toDouble(_gateway->GetFieldValue(i,9).c_str(), -1);
      ti->MktVal      = toDouble(_gateway->GetFieldValue(i,7).c_str(), -1);
      ti->Bourse = FRequest.QryStocks.Bourse;
    }
  }
  __finally
  {
  }

  return 0;
}


int TTrdItf_JSD_GD::QryETFs()    //查询ETF篮子信息
{
  string cmd;

  char et;
  switch (FRequest.QryStocks.Bourse)
  {
    case bsSHS : et = '1'; break;
    case bsSZS : et = '2'; break;
    default: return -1;
  }

  try
  {
    //******************************//
    //**   查询ETF篮子可申购余额   *//
    //******************************//

    //    ----1-----|-------2------|----3---|---4----|---5--|
    //CMD 功能号(205)|发起营业部代码|市场代码|暂时不用|客户号|
    //    ---------------6----------------|
    //    股东代码（空格表示所有股东代码）|
    //    -----7-----|-----------8----------|---9----|
    //    基金代码   |篮子数量              |委托方式|

    //                1| 2| 3|| 5| 6|7 |8| 9|
    cmd = stringprintf("205|%s|%c||%s|%s|%s|%d|%s|",     //
      FJSDSet.branch_no,                         // 2
      et,                                        // 3
      FAccInfo.Capital,                          // 5
      et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 6
      FRequest.QryStocks.EtfIDL1,                 // 7
      FRequest.QryStocks.EtfUnit,
      ENTRUST_WAY_GD[FJSDSet.entrust_way]);         // 9

      //  1.市场代码  2.证券代码    3.证券名称  4.	篮子要求数量   5.	可用申购数量
      //  6.	需要购买数量  7.	可替换金额 8.	必须替代金额
      //  9.	已买入未成交数量需购买数量＝篮子要求数量－可用申购数量－已买入未成交数量）

    if (_gateway->WaitAnswer(cmd.c_str(),9,false)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    int count = _gateway->GetRecCount();


    NewAns(_gateway->GetRecCount());

    for (int i = 1; i < _gateway->GetRecCount(); i++)
    {
      TStockInfo *ti = &(*FAnswer)[i-1].QryStocks.StockInfo;
      memset(ti, 0, sizeof(TStockInfo));

      strncpy(ti->SecuID,   _gateway->GetFieldValue(i,2).c_str(), 7);
      strncpy(ti->SecuDesc, _gateway->GetFieldValue(i,3).c_str(), 8);
      ti->BalQty   = toInt(_gateway->GetFieldValue(i,4).c_str(), -1);
      ti->AvlQty   = toDouble(_gateway->GetFieldValue(i,6).c_str(), -1);
      ti->TccQty   = toDouble(_gateway->GetFieldValue(i,5).c_str(), -1);
      ti->CostPrice = toDouble(_gateway->GetFieldValue(i,7).c_str(), -1);
      ti->FloatProfit = toDouble(_gateway->GetFieldValue(i,8).c_str(), -1);
      ti->Bourse = FRequest.QryStocks.Bourse;

    }

    //******************************//
    //**   查询ETF可赎回余额       *//
    //******************************//

    //    ----1-----|-------2------|----3---|---4----|---5--|
    //CMD 功能号(201)|发起营业部代码|市场代码|暂时不用|客户号|
    //    ---------------6----------------|
    //    股东代码（空格表示所有股东代码）|
    //    -----7-----|-----------8--------------------------|---9----|
    //    基金代码   |申购赎回标志（1：申购，2：赎回）      |委托方式|

    //                1| 2| 3|| 5| 6|7 |8| 9|
    cmd = stringprintf("201|%s|%c||%s|%s|%s|2|%s|",     //
      FJSDSet.branch_no,                         // 2
      et,                                        // 3
      FAccInfo.Capital,                          // 5
      et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 6
      FRequest.QryStocks.EtfIDL1,                 // 7
      ENTRUST_WAY_GD[FJSDSet.entrust_way]);         // 9


        // 1.成功标志  2.资金余额  3.可用资金  4.买入未交收金额  5.卖出未交收金额
        // 6.委托未成交冻结金额    7.货币名称  8.异常冻结资金
    if (_gateway->WaitAnswer(cmd.c_str(),8)!=TRUE)
    {
      setErrorMsg(_gateway->getErrorMsg());
      ODS("请求失败！[%s]",_gateway->getErrorMsg());
      ODS("请求包: [%s]",_gateway->GetRequestBuffer());

      return -1;
    }

    TStockInfo *ti = &(*FAnswer)[count-1].QryStocks.StockInfo;
    memset(ti, 0, sizeof(TStockInfo));

//          if (et == '1')              si->SecuID[0] = 'H';
//          else              si->SecuID[0] = 'S';

    strncpy(ti->SecuID, FRequest.QryStocks.EtfIDL2, 7);
    ti->TccQty    = toInt(_gateway->GetFieldValue(0,2).c_str(), -1);
    ti->Bourse = FRequest.QryStocks.Bourse;

  }
  __finally
  {
  }

  return 0;
}



//////交易函数/////
//---------------------------------------------------------------------------
// CMD: 功能号(3)|发起营业部代码|市场代码|暂时不用|股东帐号|证券代码|买卖类型(1买入、2卖出)
//      |委托数量|委托价格|委托方式|银行标志|银行代码|
//---------------------------------------------------------------------------
int TTrdItf_JSD_GD::Entrust()
{
  string cmd;
	char et;

	switch (FRequest.Entrust.Bourse)
  {
      case bsSHS : et = '1'; break;
      case bsSZS : et = '2'; break;
      case bsXXX : et = '1'; break;
      default: return -1;
  }


  if (FRequest.Entrust.Prop == 1)
  {
      // 1.功能号(202)  2.营业部代码  3.市场代码  4.暂时不用  5.客户号
      // 6.股东代码     7.申购/赎回标志（1：申购，2：赎回）
      // 8.基金代码     9.申购份额    10.委托方式
      //                1| 2| 3|| 5| 6|7| 8| 9|10|

      char ss;
      if(FRequest.Entrust.BorS=='B')  ss='1';
      else                            ss='2';


      cmd = stringprintf("202|%s|%c||%s|%s|%c|%s|%d|%s|",
          FJSDSet.branch_no,                          // 2
          et,                                         // 3
          FAccInfo.Capital,                           // 5
          et == '1' ? FAccInfo.SH : FAccInfo.SZ,      // 6
          ss,
          FRequest.Entrust.SecuID,                    // 8
          FRequest.Entrust.Num,                           // 9
          ENTRUST_WAY_GD[FJSDSet.entrust_way]);          // 10
  }
  else
  {
      //      ----1----|------2-------|----3---|----4---|----5---|----6---|
      // CMD: 功能号(3)|发起营业部代码|市场代码|暂时不用|股东帐号|证券代码|
      //
      //      ----------7-----------|----8---|----9---|---10---|---11---|---12---|
      //      买卖类型(1买入、2卖出)|委托数量|委托价格|委托方式|银行标志|银行代码|
      //
      //              1| 2| 3|| 5| 6|7| 8|   9|10|||
      char ss;
      if(FRequest.Entrust.BorS=='B')  ss='1';
      else                            ss='2';


      cmd = stringprintf("3|%s|%c||%s|%s|%c|%d|%.3f|%s|||",
          FJSDSet.branch_no,                         // 2
          et,                                        // 3
          et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 5
          FRequest.Entrust.SecuID,                   // 6
          ss,
          FRequest.Entrust.Num,                          // 8
          FRequest.Entrust.Price,                        // 9
          ENTRUST_WAY_GD[FJSDSet.entrust_way]);         // 10
  }

  if (_gateway->WaitAnswer(cmd.c_str(),2)!=TRUE)
  {
    setErrorMsg(_gateway->getErrorMsg());
    ODS("请求失败！[%s]",_gateway->getErrorMsg());
    ODS("请求包: [%s]",_gateway->GetRequestBuffer());
    return -1;
  }
  NewAns(1);
  strncpy((*FAnswer)[0].Entrust.OrderID, _gateway->GetFieldValue(0,2).c_str(), 19);

  return 0;
}


int TTrdItf_JSD_GD::Undo() //委托撤单
{

  string cmd;
  //
  //     ----1----|-------2------|----3---|----4---|---5--|---6--|----7---|
  //CMD: 功能号(4)|发起营业部代码|市场代码|暂时不用|客户号|合同号|委托方式|
  //
  //              1| 2| 3|| 5| 6| 7|
  cmd = stringprintf("4|%s|%c||%s|%s|%s|",
      FJSDSet.branch_no,                          // 2
      FRequest.Undo.Bourse == bsSHS ? '1' : '2',   // 3
      FAccInfo.Capital,                           // 5
      FRequest.Undo.OrderID,                   // 6
      ENTRUST_WAY_GD[FJSDSet.entrust_way]);          // 7

  if (_gateway->WaitAnswer(cmd.c_str(),2)!=TRUE)
  {
    setErrorMsg(_gateway->getErrorMsg());
    ODS("请求失败！[%s]",_gateway->getErrorMsg());
    ODS("请求包: [%s]",_gateway->GetRequestBuffer());
    return -1;
  }
  NewAns(1);

  return 0;
}


