//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdItf_JSDFF.h"
#include <assert.h>

#pragma package(smart_init)

#define REQUEST_NUM " "
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TTrdItf_JSDFF::TTrdItf_JSDFF(TJSDSet *set)
{
    CopyMemory(&FJSDSet,set,sizeof(TJSDSet));
    FJSDSet.JyCode[0]=' ';
    FJSDSet.JyCode[1]=0;

    FidTcp = new TIdTCPClient(NULL);
    FidIPWatch = new TIdIPWatch(NULL);
}
//---------------------------------------------------------------------------
TTrdItf_JSDFF::~TTrdItf_JSDFF()
{
    FidTcp->Disconnect();
    delete FidTcp;
    delete FidIPWatch;
}
//---------------------------------------------------------------------------
AnsiString TTrdItf_JSDFF::GetRequestHead(AnsiString FuncNo)
{
  AnsiString text;

//        功能号  | 营业部代码  | 委托方式  | 客户号                     | 客户密码 |
  text = FuncNo +"|"+" "      +"|"+" "    +"|"+AnsiString(FAccInfo.Capital)+"|"+AnsiString(FAccInfo.PW);
  return text;
}
//---------------------------------------------------------------------------
AnsiString TTrdItf_JSDFF::GetErrorText(int code, char *error)
{
    strcpy(FLastError.Sender,"JSDFF");
    FLastError.ErrorCode = code;
    lstrcpyn( FLastError.Text,error,MAX_TEXT );
    AnsiString text;
    text.printf("A\r\nLocal\r\n%d\r\nN\r\n%s\r\n%d", REQUEST_NUM, error, code);
    return text; 
}
//---------------------------------------------------------------------------
AnsiString TTrdItf_JSDFF::ReadNextData()
{
    AnsiString cmd;
    cmd.printf("R|%s|%s|%s|", FidIPWatch->LocalIP().c_str(),REQUEST_NUM,GetRequestHead("0").c_str());
    return ReadFirstData(cmd);
}
//---------------------------------------------------------------------------
AnsiString TTrdItf_JSDFF::ReadFirstData(AnsiString cmd)
{
    //清除上次的返回信息
    int n = FidTcp->ReadFromStack(true, 1, true);
    if (n > 0) FidTcp->ReadString(n);

    //ODS(cmd.c_str());
    FidTcp->Write(cmd);

    n = FidTcp->ReadFromStack(true, FJSDSet.TimeOut, true);
    if (n <= 0) return "A|192.168.0.1|100|N|接收数据超时|-100"  ;

    AnsiString ret = FidTcp->ReadString(n);
    //ODS(ret.c_str());

    return ret;
}
//---------------------------------------------------------------------------
// count 表示至少有几个值
int TTrdItf_JSDFF::SplitData(AnsiString SD, TStringList *lstDD, int count)
{
    assert(lstDD != NULL);

    lstDD->Clear();

    DeStr(SD.Trim(),lstDD,"|");

    if (lstDD->Count < 4)
    {
        lstDD->Text = GetErrorText(-501, "数据解析失败");
        return DEF_ACK_ERROR;
    }

    if (lstDD->Strings[0] != "A")
    {
        lstDD->Text = GetErrorText(-502, "不是返回数据");
        return DEF_ACK_ERROR;
    }

    if (lstDD->Strings[3] == "N" )
    {
        if (lstDD->Count < 5)
            lstDD->Text = GetErrorText(-503, "未知错误！！！");
        else if (lstDD->Count >= 5)
            lstDD->Text = GetErrorText(-503, lstDD->Strings[5].c_str());

        return DEF_ACK_ERROR;
    }

    if (lstDD->Count >= count)
        return DEF_ACK_OK;


    lstDD->Text = GetErrorText(-504, "未知错误！！！");
    return DEF_ACK_ERROR;
}
//---------------------------------------------------------------------------
int TTrdItf_JSDFF::Init()  //初始化
{
    try
    {
        if (!FidTcp->Connected())
        {
            FidTcp->Host = FJSDSet.SvrIp;
            FidTcp->Port = FJSDSet.SvrPort;
            FidTcp->Connect();
        }
    }
    catch (Exception *e)
    {
        ODS(("连接柜台失败! 错误信息：" + e->Message).c_str() );
    }

    return FidTcp->Connected()==true ? 0 : -1;
}

//--------------------------------------------------------------------------
// CMD:功能号(6011)|营业部代码|委托方式|客户号|客户密码|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::SetAccount() //设置帐号
{
    AnsiString cmd;


    TStringList *lstDD = new TStringList();

    try
    {

        cmd.printf("R|%s|%s|6011| | |%s|%s|",
            FidIPWatch->LocalIP().c_str(),
            REQUEST_NUM,
            FRequest.SetAccount.Account,
            FRequest.SetAccount.PW);

        //  1.成功标志
        //  2.客户名称
        //  3.风险度
        //  4.追加保证金
        //  5.客户安全类别(0：安全、1：不安全、3：危险、6：冻结)
        //  6.未用，保留
        //  7.未用，保留
        //  8.未用，保留
        //  9.未用，保留
        //  10.未用，保留
        //  11.确认结算单模式 ’0’：不取对帐单 ’1’：取对帐单，不必确认 ’2’：取对帐单，必须确认
        //  12.结算单确认状态 ’1’：已取或已确认’0’：未取或未确认
        
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 4) == DEF_ACK_OK)
        {
            strncpy(FAccInfo.Capital, FRequest.SetAccount.Account, 20);
            strncpy(FAccInfo.PW, FRequest.SetAccount.PW, 13);

            if( FJSDSet.gw_ver == '6' )
            {
              AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
              cmd.cat_printf("%s|%c|",
              GetRequestHead("6040").c_str(),FJSDSet.jysID);

              if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 1) == DEF_ACK_OK)
              {
                int count = lstDD->Strings[4].ToIntDef(0);
                for (int i = 0; i < count; i++)
                {
                    if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 3) == DEF_ACK_OK)
                    {
                      if(lstrcmp(FRequest.SetAccount.Account,lstDD->Strings[INDEX(1)].c_str())==0 && FJSDSet.jysID==lstDD->Strings[INDEX(2)][1]){

                        NewAns(1);
                        memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));
                        strncpy(FJSDSet.JyCode, lstDD->Strings[INDEX(3)].c_str(), 20);
                        break;
                      }
                    }
                }

              }
              else
              {
                  ODS(lstDD->Strings[5].c_str());
                  return AnsiString(FRequest.SetAccount.Account).ToIntDef(DEF_OTHER_ERROR);
              }
            }
            else
            {
              NewAns(1);
			        memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));
            }
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return -1;
        }

        
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}
//--------------------------------------------------------------------------
//////查询函数//////
//
//行情查询
//功能号 6017|营业部代码|委托方式|客户号|客户密码|交易所代码|合约编码|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::GetTrdInfo()   //取得盘口数据
{
/*
    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%c|%s|",
        GetRequestHead("6017").c_str(),
        FJSDSet.jysID,                              //8
        FRequest.GetTrdInfo.SecuID + 1              //9        
    );

    TStringList *lstDD = new TStringList();
    try
    {
//    1.成功标志  Y 2.交易所代码 3.交易所名称  4.合约编码    5.合约名称  6.昨收盘 7.今开盘
//    8.当日最高  9.当日最低     10.最新成交价 11.总成交量   12.成交金额 13.涨跌(最新价－昨收盘)
//    14.申报买入 15.申报卖出    16.申报买入量 17.申报卖出量 18.涨停版   19.跌停版
//    20.昨结算价

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 20) == DEF_ACK_OK)
        {
          NewAns(1);
          TQryQtn_Ans *qq = &(*FAnswer)[0].QryQtn;
          qq->QryQtnInfo.Open   = StrToFloatDef(lstDD->Strings[INDEX(7)], -1);
          qq->QryQtnInfo.Close  = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);
          qq->QryQtnInfo.High   = StrToFloatDef(lstDD->Strings[INDEX(8)], -1);
          qq->QryQtnInfo.Low    = StrToFloatDef(lstDD->Strings[INDEX(9)], -1);
          qq->QryQtnInfo.Last   = StrToFloatDef(lstDD->Strings[INDEX(10)], -1);
          qq->QryQtnInfo.Bid[0] = StrToFloatDef(lstDD->Strings[INDEX(14)], -1);
          qq->QryQtnInfo.BidV[0]= StrToFloatDef(lstDD->Strings[INDEX(16)], -1);
          qq->QryQtnInfo.Ask[0] = StrToFloatDef(lstDD->Strings[INDEX(15)], -1);
          qq->QryQtnInfo.AskV[0]= StrToFloatDef(lstDD->Strings[INDEX(17)], -1);
          qq->QryQtnInfo.Upper  = StrToFloatDef(lstDD->Strings[INDEX(18)], -1);
          qq->QryQtnInfo.Lower  = StrToFloatDef(lstDD->Strings[INDEX(19)], -1);
          qq->QryQtnInfo.Settle = StrToFloatDef(lstDD->Strings[INDEX(20)], -1);
          qq->QryQtnInfo.Volumn = StrToFloatDef(lstDD->Strings[INDEX(11)], -1);
        }
        else
        {
            ODS(lstDD->Strings[5].c_str());
            return lstDD->Strings[6].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }

*/
    return 0;
}
//--------------------------------------------------------------------------
//查询可用资金余额,总保证金
//功能号 6012|营业部代码|委托方式|客户号|客户密码|日期---YYYYMMDD|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryMoney()     //资金查询
{
    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|",
        GetRequestHead("6012").c_str(),
        Now().FormatString("yyyymmdd").c_str()
    );
    
    TStringList *lstDD = new TStringList();
    try
    {
//  1.成功标志 Y  2.客户名称  3.上日结存  4.买入冻结  5.卖出冻结  6.买入保证金
//  7.卖出保证金  8.盈利      9.亏损      10.可用资金 11.动态权益 12.动态风险
//  13.空 保留    14.空 保留  15.浮动盈亏 16.平仓盈亏 17.空 保留  18.空 保留
//  19.当日出入金 20.空 保留  21.空 保留  22.总保证金

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 22) == DEF_ACK_OK)
        {
          NewAns(1);
          (*FAnswer)[0].QryMoney.Balance = StrToFloatDef(lstDD->Strings[INDEX(22)] ,-1);     //总保证金
          (*FAnswer)[0].QryMoney.Available = StrToFloatDef(lstDD->Strings[INDEX(10)],-1);    //可用资金
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}
/*
//--------------------------------------------------------------------------
//查询可用资金余额,总保证金
//功能号 6012|营业部代码|委托方式|客户号|客户密码|日期---YYYYMMDD|（7） 币种[空：人民币]
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryMoneyFF()     //资金查询
{
    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|",
        GetRequestHead("6012").c_str(),
        Now().FormatString("yyyymmdd").c_str()
    );
    
    TStringList *lstDD = new TStringList();
    try
    {
//  1.成功标志 Y  2.客户名称  3.上日结存  4.买入冻结  5.卖出冻结  6.买入保证金
//  7.卖出保证金  8.盈利      9.亏损      10.可用资金 11.动态权益 12.动态风险
//  13.空 保留    14.空 保留  15.浮动盈亏 16.平仓盈亏 17.空 保留  18.空 保留
//  19.当日出入金 20.空 保留  21.空 保留  22.总保证金

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 22) == DEF_ACK_OK)
        {
          NewAns(1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Last_jc     = StrToFloatDef(lstDD->Strings[INDEX(3)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.FreezeB     = StrToFloatDef(lstDD->Strings[INDEX(4)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.FreezeS     = StrToFloatDef(lstDD->Strings[INDEX(5)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MarginB     = StrToFloatDef(lstDD->Strings[INDEX(6)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MarginS     = StrToFloatDef(lstDD->Strings[INDEX(7)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Profit      = StrToFloatDef(lstDD->Strings[INDEX(8)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Loss        = StrToFloatDef(lstDD->Strings[INDEX(9)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Available   = StrToFloatDef(lstDD->Strings[INDEX(10)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.DymValue    = StrToFloatDef(lstDD->Strings[INDEX(11)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.DymVaR      = StrToFloatDef(lstDD->Strings[INDEX(12)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.Payoff      = StrToFloatDef(lstDD->Strings[INDEX(15)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.ClosePayoff = StrToFloatDef(lstDD->Strings[INDEX(16)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MoneyOI     = StrToFloatDef(lstDD->Strings[INDEX(19)],-1);
          (*FAnswer)[0].QryMoneyFF.QryMoneyIF.MarginAll   = StrToFloatDef(lstDD->Strings[INDEX(22)] ,-1);   
        }
        else
        {
            ODS(lstDD->Strings[5].c_str());
            return lstDD->Strings[INDEX(10)].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}
*/
//--------------------------------------------------------------------------
//查询单个合约持仓
//功能号 6014|营业部代码|委托方式|客户号|客户密码|日期---YYYYMMDD|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryStock()     //股份查询
{
    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|",
        GetRequestHead("6014").c_str(),
        Now().FormatString("yyyymmdd").c_str());
    
    TStringList *lstDD = new TStringList();
    try
    {

//  v 1.1
//  1.交易所代码  2.交易所名称  3.合约编码  4.投保标记  5.买持仓  6.买均价
//  7.卖持仓      8.卖均价      9.买浮动    10.卖浮动   11.最新价 12.投保名称
//  13.浮动盈亏   14.交易编码   15.今买持仓 16.今卖持仓

//  v 1.5
/*
（1） 交易所代码
（2） 交易所名称
（3）合约编码
（4） 投保标记
（5）买持仓
（6） 买均价
（7） 卖持仓
（8） 卖均价
（9） 买浮动
（10）卖浮动
（11）最新价
（12）投保名称
（13）浮动盈亏
（14）交易编码
（15）空 保留
（16）空 保留
（17）空 保留
（18）今买持仓
（19）今卖持仓
*/

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            if (count <= 0) return DEF_OTHER_ERROR;

            for (int i = 0; i < count; i++)
            {
              if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 16) == DEF_ACK_OK)
              {
                  if(lstrcmp(FRequest.QryStock.SecuID + 1,lstDD->Strings[INDEX(3)].c_str())==0){    //如果是要查询的合约

                    NewAns(1);
                    TQryStock_Ans *sa = &(*FAnswer)[0].QryStock;

                    sa->Balance    = StrToFloatDef(lstDD->Strings[INDEX(5)], 0);
                    sa->Available  = StrToFloatDef(lstDD->Strings[INDEX(7)], 0);
                    sa->BuyFreeze  = 0;
                    sa->SellFreeze = 0;
                  }
                  else continue;
              }
              else
              {
                  ODS(lstDD->Strings[4].c_str());
                  return -1;
              }
            }
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}
//--------------------------------------------------------------------------
//查询最大可开仓手数
//功能号 6044
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryCanBuy()    //取可买数量
{
    return -1;
}
//--------------------------------------------------------------------------
//查询委托状态
//功能号 6020|营业部代码|委托方式|客户号|客户密码|委托单号
//查询当日委托
//功能号 6019|营业部代码|委托方式|客户号|客户密码|起始日期----YYYYMMDD|结束日期----YYYYMMDD
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryDetail()    //成交查询
{
  if( FJSDSet.qry_type == 6019 )
  {
    int reqry_num=0;
    AnsiString cmd;
    AnsiString date = Now().FormatString("yyyymmdd");
  HH:

    if(FRequest.QryDetail.ContractID[0]==0) return -1;

    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
        GetRequestHead("6019").c_str(),
        date.c_str(),
        date.c_str());

      TStringList *lstDD = new TStringList();
      try
      {
          //  1.成功标志 Y  2.委托单状态  3.成交数量  4.未成交数量
        
          //*******************************
          //委托单状态, wt_state, C1
          //*******************************
          //正在申报  Baodaning         n
          //已接收(v6)                  s
          //已报入    Already baodaned  a
          //部分成交  Partial completed p
          //全部成交  Completed         c
          //正在撤销  Deleteing         f
          //系统撤销  System disable    m
          //主机拒绝  User disable      q
          //已撤消    Total deleted     d
          //撤单发出(v6)                g
          //柜台发出错误委托(v6)        e
          //部成部撤(v6)                b
          //未知状态  Unknow            其它
          //------------------------------

  //    1.交易所代码  2.交易所名称  3.委托单号  4.合约编码  5.合约名称  6.委托单状态代码
  //    7.委托单状态名称 [全部成交/部分成交/全部撤单/已经申报/正在处理/未处理错误]
  //    8.买卖标记    9.买卖类别名称[买入/卖出] 10.开平仓标志 11.开平仓名称 [开仓/平仓/平今]
  //    12.投保标记   13.投保名称   14.委托数量 15.委托价格 16.成交数量 17.成交价格
  //    18.未成交数量 19.系统中心号 20.交易编码 21.委托数量 [成交数量 + 未成交数量 + 撤消数量]

          if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
          {
              int count = lstDD->Strings[4].ToIntDef(0);
              for (int i = 0; i < count; i++)
              {
                  if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                  {
                      if(lstrcmp(FRequest.QryDetail.ContractID,lstDD->Strings[INDEX(3)].c_str())==0)    //如果是要查询的委托号
                      {
                        NewAns(1);
                        (*FAnswer)[0].QryDetail.Num   = StrToIntDef(lstDD->Strings[INDEX(16)], -1);
                        (*FAnswer)[0].QryDetail.Price = StrToFloatDef(lstDD->Strings[INDEX(17)], -1);
                        (*FAnswer)[0].QryDetail.UndoNum = 0;
                        int csnnum = lstDD->Strings[INDEX(14)].ToIntDef(0);

                        String tmp = lstDD->Strings[INDEX(6)];
                        char ordstatus=' ';
                        if( tmp.Length()>0 )
                         ordstatus = tmp[1];
                        if (ordstatus == 'd' || ordstatus == 'b' ||
                            ordstatus == 'm' || ordstatus == 'q' ||
                            ordstatus == 'e')  //正在撤单
                        {
                          if((ordstatus =='b') && (++reqry_num < 10)) //如果是部撤则再查直到 reqry_num >3
                          {
                            delete lstDD;
                            Idglobal::Sleep(100);
                            goto HH;
                          }

                          (*FAnswer)[0].QryDetail.UndoNum = (*FAnswer)[0].QryDetail.Num - csnnum ;
                        }
                      }
                      else continue;
                  }
                  else
                  {
                      //ODS(lstDD->Strings[4].c_str());
                      ODS("QryDetail:%s",lstDD->Text.c_str());
                      return -1;
                  }
              }
          }
      }
      __finally
      {
          delete lstDD;
      }
    }
    else if (FJSDSet.qry_type == 6020 )
    {
      int reqry_num=0;
      AnsiString cmd;
      cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

      cmd.cat_printf("%s|%s|",
          GetRequestHead("6020").c_str(),
          FRequest.QryDetail.ContractID);
HH2:
      TStringList *lstDD = new TStringList();
      try
      {
          //  1.成功标志 Y  2.委托单状态  3.成交数量  4.未成交数量

          //*******************************
          //委托单状态, wt_state, C1
          //*******************************
          //正在申报  Baodaning         n
          //已接收(v6)                  s
          //已报入    Already baodaned  a
          //部分成交  Partial completed p
          //全部成交  Completed         c
          //正在撤销  Deleteing         f
          //系统撤销  System disable    m
          //主机拒绝  User disable      q
          //已撤消    Total deleted     d
          //撤单发出(v6)                g
          //柜台发出错误委托(v6)        e
          //部成部撤(v6)                b
          //未知状态  Unknow            其它
          //------------------------------

          if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
          {
            char ordstatus = lstDD->Strings[INDEX(2)][1];
            NewAns(1);
            (*FAnswer)[0].QryDetail.Num   = StrToIntDef(lstDD->Strings[INDEX(3)], -1);
            (*FAnswer)[0].QryDetail.Price = 0 ;
            if (ordstatus== 'd' || ordstatus == 'b' || ordstatus == 'm' ||
                ordstatus == 'q' || ordstatus == 'e' )
            {      //已撤消 或  部成部撤
              if((ordstatus =='b') && (++reqry_num < 3)) //如果是部撤则再查直到 reqry_num >3
              {
                delete lstDD;
                Idglobal::Sleep(100);
                goto HH2;
              }
              (*FAnswer)[0].QryDetail.UndoNum = (-1)*StrToIntDef(lstDD->Strings[INDEX(4)], -1);
            }
            else (*FAnswer)[0].QryDetail.UndoNum = 0;

            (*FAnswer)[0].QryDetail.status = ordstatus;
          }
          else
          {
            //ODS(lstDD->Strings[4].c_str());
            ODS("QryDetail:%s",lstDD->Text.c_str());
            return -1;
          }
      }
      __finally
      {
          delete lstDD;
      }
    }
    return 0;
}

int TTrdItf_JSDFF::QryHisDetail() //历史成交查询
{
    // 暂时不用
    return -1;
}

int TTrdItf_JSDFF::QryCsn()       //查询某个委托合同
{
    // 暂时不用
    return -1;
}
//--------------------------------------------------------------------------
//查询当日委托
//功能号 6019|营业部代码|委托方式|客户号|客户密码|起始日期----YYYYMMDD|结束日期----YYYYMMDD
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryCurCsn()    //当日委托查询
{
//    AnsiString idxDate = "";
//    AnsiString idxContractID = "";
//    AnsiString idxMartCode = "";
    
    AnsiString date = Now().FormatString("yyyymmdd");
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
        GetRequestHead("6019").c_str(),
        date.c_str(),
        date.c_str());


    try
    {
//    1.交易所代码  2.交易所名称  3.委托单号  4.合约编码  5.合约名称  6.委托单状态代码
//    7.委托单状态名称 [全部成交/部分成交/全部撤单/已经申报/正在处理/未处理错误]
//    8.买卖标记    9.买卖类别名称[买入/卖出] 10.开平仓标志 11.开平仓名称 [开仓/平仓/平今]
//    12.投保标记   13.投保名称   14.委托数量 15.委托价格 16.成交数量 17.成交价格
//    18.未成交数量 19.系统中心号 20.交易编码 21.委托数量 [成交数量 + 未成交数量 + 撤消数量]

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                {
                    TConsignInfo *ci = new TConsignInfo;
                    memset(ci, 0, sizeof(TConsignInfo));

                    strncpy(ci->ContractID,lstDD->Strings[INDEX(3)].c_str(), 6);
                    strncpy(ci->SecuID,    lstDD->Strings[INDEX(4)].c_str(), 8);
                    strncpy(ci->SecuDesc,  lstDD->Strings[INDEX(5)].c_str(), 8);
                    //strncpy(ci->Time,      lstDD->Strings[INDEX(12)].c_str(), 8);
                    //strncpy(ci->Date,      lstDD->Strings[INDEX(13)].c_str(), 8);

                    ci->Bourse = lstDD->Strings[INDEX(1)][1];

                    ci->Type   = ConvertType(lstDD->Strings[INDEX(8)].c_str());
                    ci->NoUse[0] = lstDD->Strings[INDEX(10)][1];
                    //ci->EoFlag = lstDD->Strings[INDEX(10)][1];
                    ci->State  = lstDD->Strings[INDEX(6)][1];
                    ci->CsnVol = StrToIntDef(lstDD->Strings[INDEX(14)], 0);
                    ci->TrdVol = StrToIntDef(lstDD->Strings[INDEX(16)], 0);
                    ci->CancelVol = 0;
                    ci->CsnPrice  = StrToFloatDef(lstDD->Strings[INDEX(15)], -1);;
                    ci->TrdPrice  = StrToFloatDef(lstDD->Strings[INDEX(17)], -1);;

//                    idxDate         = lstDD->Strings[INDEX(13)];
//                    idxContractID   = lstDD->Strings[INDEX(7)];
//                    idxMartCode     = lstDD->Strings[INDEX(16)];

                     if (lstDD->Strings[INDEX(7)] == "全部撤单")
                    {
                        int csnnum = lstDD->Strings[INDEX(14)].ToIntDef(0);
                        ci->CancelVol = ci->TrdVol - csnnum ;
                    }

                    lstAns->Add(ci);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return -1;
                }
            }
            
//            if (count > 0) goto _NEXT;

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryCurCsn.CsgInfo, ci, sizeof(TConsignInfo));
                }
            }

            for (int i = 0; i < lstAns->Count; i++)
            {
                TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
                delete ci;
            }
            lstAns->Clear();
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}
//--------------------------------------------------------------------------
//查询当日委托
//功能号 6019|营业部代码|委托方式|客户号|客户密码|起始日期----YYYYMMDD|结束日期----YYYYMMDD
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryHisCsn()    //历史委托查询
{
//    AnsiString idxDate = "";
//    AnsiString idxContractID = "";
//    AnsiString idxMartCode = "";
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
        GetRequestHead("6019").c_str(),
        FRequest.QryHisCsn.StartDay,
        FRequest.QryHisCsn.EndDay);

    try
    {
//    1.交易所代码  2.交易所名称  3.委托单号  4.合约编码  5.合约名称  6.委托单状态代码
//    7.委托单状态名称 [全部成交/部分成交/全部撤单/已经申报/正在处理/未处理错误]
//    8.买卖标记    9.买卖类别名称[买入/卖出] 10.开平仓标志 11.开平仓名称 [开仓/平仓/平今]
//    12.投保标记   13.投保名称   14.委托数量 15.委托价格 16.成交数量 17.成交价格
//    18.未成交数量 19.系统中心号 20.交易编码 21.委托数量 [成交数量 + 未成交数量 + 撤消数量]

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                {
                    TConsignInfo *ci = new TConsignInfo;
                    memset(ci, 0, sizeof(TConsignInfo));

                    strncpy(ci->ContractID,lstDD->Strings[INDEX(3)].c_str(), 6);
                    strncpy(ci->SecuID,    lstDD->Strings[INDEX(4)].c_str(), 8);
                    strncpy(ci->SecuDesc,  lstDD->Strings[INDEX(5)].c_str(), 8);
                    //strncpy(ci->Time,      lstDD->Strings[INDEX(12)].c_str(), 8);
                    //strncpy(ci->Date,      lstDD->Strings[INDEX(13)].c_str(), 8);
                    strncpy(ci->Date,     Now().FormatString("yyyymmdd").c_str(), 8);
                    ci->Bourse = lstDD->Strings[INDEX(1)][1];

                    ci->Type   = ConvertType(lstDD->Strings[INDEX(8)].c_str());
                    //ci->EoFlag = lstDD->Strings[INDEX(10)][1];
                    ci->NoUse[0] =lstDD->Strings[INDEX(10)][1];
                    ci->State  = lstDD->Strings[INDEX(6)][1];
                    ci->CsnVol = StrToIntDef(lstDD->Strings[INDEX(14)], 0);
                    ci->TrdVol = StrToIntDef(lstDD->Strings[INDEX(16)], 0);
                    ci->CancelVol = 0;
                    ci->CsnPrice  = StrToFloatDef(lstDD->Strings[INDEX(15)], -1);;
                    ci->TrdPrice  = StrToFloatDef(lstDD->Strings[INDEX(17)], -1);;
          
//                    idxDate         = lstDD->Strings[INDEX(13)];
//                    idxContractID   = lstDD->Strings[INDEX(7)];
//                    idxMartCode     = lstDD->Strings[INDEX(16)];

                    lstAns->Add(ci);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return -1;
                }
            }
            
//            if (count > 0) goto _NEXT;

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryHisCsn.CsgInfo, ci, sizeof(TConsignInfo));
                }
            }

            for (int i = 0; i < lstAns->Count; i++)
            {
                TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
                delete ci;
            }
            lstAns->Clear();
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}
//--------------------------------------------------------------------------
//查询当日成交
//功能号 6013|营业部代码|委托方式|客户号|客户密码|起始日期----YYYYMMDD|结束日期----YYYYMMDD
//如果连接V6的网关需要使用6053来查询历史成交明细,6013只用来查询当日成交
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryCurTrd()    //当日成交查询
{
//    AnsiString idxStock  = "";
//    AnsiString idxTrdNo  = "";
//    AnsiString idxAccout = "";
//    AnsiString idxMartCode = "";
    AnsiString cmd;
    AnsiString date = Now().FormatString("yyyymmdd");

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();
    
_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
        GetRequestHead("6013").c_str(),
        date.c_str(),
        date.c_str());


    try
    {
//    1.交易所代码  2.交易所名称  3.委托单号    4.合约编码  5.合约名称  6.买卖标记
//    7.买卖类别名称[买入/卖出]   8.开平仓标志  9.开平仓名称 [开仓/平仓/平今]
//    10.投保标记   11.投保名称   12.成交数量   13.成交价格 14.当日日期
//    15.交易编码   16.系统号
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 16) == DEF_ACK_OK)
                {
                    TTradeInfo *ti = new TTradeInfo;
                    memset(ti, 0, sizeof(TTradeInfo));

                    strncpy(ti->SecuID,   lstDD->Strings[INDEX(4)].c_str(), 8);
                    strncpy(ti->SecuDesc, lstDD->Strings[INDEX(5)].c_str(), 8);
                    //strncpy(ti->Time,     lstDD->Strings[INDEX(7)].c_str(), 8);
                    strncpy(ti->Date,     Now().FormatString("yyyymmdd").c_str(), 8);
                    ti->Type  = ConvertType(lstDD->Strings[INDEX(6)].c_str());
                    //ti->EoFlag= lstDD->Strings[INDEX(8)][1];
                    ti->Vol   = StrToIntDef(lstDD->Strings[INDEX(12)], -1);
                    ti->Price = StrToFloatDef(lstDD->Strings[INDEX(13)], -1);
                    
                    lstAns->Add(ti);
                    
//                    idxStock    = lstDD->Strings[INDEX(3)];
//                    idxTrdNo    = lstDD->Strings[INDEX(8)];
//                    idxAccout   = lstDD->Strings[INDEX(1)];
//                    idxMartCode = lstDD->Strings[INDEX(10)];
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return -1;
                }
            }
            
//            if (count > 0) goto _NEXT;

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryHisTrd.TrdInfo, ti, sizeof(TTradeInfo));
                }
            }

            for (int i = 0; i < lstAns->Count; i++)
            {
                TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
                delete ti;
            }
            lstAns->Clear();
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}
//--------------------------------------------------------------------------
//查询历史成交
//功能号 6053|营业部代码|委托方式|客户号|客户密码|起始日期----YYYYMMDD|结束日期----YYYYMMDD
//如果连接V6的网关需要使用6053来查询历史成交明细,6013只用来查询当日成交
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryHisTrd()    //历史成交查询
{
//    AnsiString idxNo = "";
    AnsiString cmd;
    
    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
        GetRequestHead("6053").c_str(),
        FRequest.QryHisTrd.StartDay,
        FRequest.QryHisTrd.EndDay);


    try
    {
//    1.交易所代码  2.交易所名称  3.委托单号    4.合约编码  5.合约名称  6.买卖标记
//    7.买卖类别名称[买入/卖出]   8.开平仓标志  9.开平仓名称[开仓/平仓/平今]
//    10.投保标记   11.投保名称   12.成交数量   13.成交价格 14.交易编码
//    15.系统号     16.成交号     17.日期       18.手续费   19.交易费

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[INDEX(2)].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 19) == DEF_ACK_OK)
                {
                    TTradeInfo *ti = new TTradeInfo;
                    memset(ti, 0, sizeof(TTradeInfo));

                    strncpy(ti->SecuID,   lstDD->Strings[INDEX( 4)].c_str(), 8);
                    strncpy(ti->SecuDesc, lstDD->Strings[INDEX( 5)].c_str(), 8);
                    //strncpy(ti->Time,     lstDD->Strings[INDEX(16)].c_str(), 8);
                    strncpy(ti->Date,     lstDD->Strings[INDEX(17)].c_str(), 8);
                    ti->Type  = ConvertType(lstDD->Strings[INDEX(6)].c_str());
                    //ti->EoFlag= lstDD->Strings[INDEX(8)][1];
                    ti->Vol   = StrToIntDef(lstDD->Strings[INDEX(12)], -1);
                    ti->Price = StrToFloatDef(lstDD->Strings[INDEX(13)], -1);

//                    idxNo = lstDD->Strings[INDEX(20)];
                    lstAns->Add(ti);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return -1;
                }
            }


//            if (count > 0) goto _NEXT;

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryHisTrd.TrdInfo, ti, sizeof(TTradeInfo));
                }
            }

            for (int i = 0; i < lstAns->Count; i++)
            {
                TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
                delete ti;
            }
            lstAns->Clear();
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}
//--------------------------------------------------------------------------
//查询资金流水
//功能号XXX
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryBill()      //查询资金流水（对帐单）
{
    return -1;
}
//--------------------------------------------------------------------------
//查询所有持仓
//功能号 6014|营业部代码|委托方式|客户号|客户密码|日期---YYYYMMDD|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryStocks()    //查询帐号中所有的股份
{
//    AnsiString idxStock = "";
//    AnsiString idxAcc   = "";
//    AnsiString idxMart  = "";

  //if (FRequest.QryStocks.Bourse !=  bsJJS ) return -1;

    AnsiString cmd;
    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();
    //int count;

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|",
        GetRequestHead("6014").c_str(),
        Now().FormatString("yyyymmdd").c_str());

    try
    {
//  1.交易所代码  2.交易所名称  3.合约编码  4.投保标记  5.买持仓  6.买均价
//  7.卖持仓      8.卖均价      9.买浮动    10.卖浮动   11.最新价 12.投保名称
//  13.浮动盈亏   14.交易编码   15.今买持仓 16.今卖持仓

        if (SplitData(ReadFirstData(cmd), lstDD, 5) == DEF_ACK_OK)
        {

            int count = lstDD->Strings[4].ToIntDef(0) - 2;  //最后两条记录为买小计和卖小计，所以要减2
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 17) == DEF_ACK_OK)
                {
                    TStockInfo *si = new TStockInfo;
                    memset(si, 0, sizeof(TStockInfo));

                    si->SecuID[0] = 'F';

                    strncpy(si->SecuID + 1, lstDD->Strings[INDEX(3)].c_str(), 6);
                    strncpy(si->SecuDesc,   lstDD->Strings[INDEX(14)].c_str(),12);     //存入交易编码

                    si->Balance       = lstDD->Strings[INDEX(5)].ToIntDef(0);          //买持仓
                    si->Available     = lstDD->Strings[INDEX(7)].ToIntDef(0);          //卖持仓

                    si->ProfitAndLoss = StrToFloatDef(lstDD->Strings[INDEX(13)], 0);  //浮动盈亏

                    si->CostPrice     = StrToFloatDef(lstDD->Strings[INDEX(6)], 0);   //买均价
                    si->Cost          = si->Balance * si->CostPrice;
                    si->CurPrice      = StrToFloatDef(lstDD->Strings[INDEX(8)], 0);   //卖均价
                    si->CurVal        = si->Available * si->CurPrice;

                    lstAns->Add(si);
                    
//                    idxMart  = lstDD->Strings[INDEX(1)];
//                    idxAcc   = lstDD->Strings[INDEX(2)];
//                    idxStock = lstDD->Strings[INDEX(3)];
                }
            }

//            if (count > 0) goto _NEXT;

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TStockInfo *ci = (TStockInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryStocks.StockInfo, ci, sizeof(TStockInfo));
                }
            }

            for (int i = 0; i < lstAns->Count; i++)
            {
                TStockInfo *ci = (TStockInfo *)lstAns->Items[i];
                delete ci;
            }
            lstAns->Clear();
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }
    
    return 0;
}

//--------------------------------------------------------------------------
//查询委托状态
//功能号 6020|营业部代码|委托方式|客户号|客户密码|委托单号
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryTrdState(char *Cid)    //委托状态查询
{
  //int reqry_num=0;
  AnsiString cmd;
HH:

  cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

  cmd.cat_printf("%s|%s|",
      GetRequestHead("6020").c_str(),
      Cid);

    TStringList *lstDD = new TStringList();
    try
    {
        //  1.成功标志 Y  2.委托单状态  3.成交数量  4.未成交数量

        //*******************************
        //委托单状态, wt_state, C1
        //*******************************
        //正在申报  Baodaning         n
        //已接收(v6)                  s
        //已报入    Already baodaned  a
        //部分成交  Partial completed p
        //全部成交  Completed         c
        //正在撤销  Deleteing         f
        //系统撤销  System disable    m
        //主机拒绝  User disable      q
        //已撤消    Total deleted     d
        //撤单发出(v6)                g
        //柜台发出错误委托(v6)        e
        //部成部撤(v6)                b
        //未知状态  Unknow            其它
        //------------------------------

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {

          if(lstDD->Strings[INDEX(2)] == "n" || lstDD->Strings[INDEX(2)] == "s") //如果是正在申报则再查直到报入或系统拒绝
          {
            delete lstDD;
            Idglobal::Sleep(250);
            goto HH;
          }

          //系统拒绝
          if(lstDD->Strings[INDEX(2)] == "q" || lstDD->Strings[INDEX(2)] == "m")
          {
             return -1;
          }
        }
    }
    __finally
    {
        delete lstDD;
    }
    return 0;
}


//////交易函数/////
//---------------------------------------------------------------------------
//功能号 6021|营业部代码|委托方式|客户号|客户密码|交易所----数字|合约编码|买卖标记
//开平仓标志|投保标记|委托数量|委托价格|交易编码
//---------------------------------------------------------------------------
int TTrdItf_JSDFF::Buy()
{
    AnsiString cmd;
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%c|%s|%d|%d|%d|%d|%.3f|%s|",
        GetRequestHead("6021").c_str(),
        FJSDSet.jysID,                          //交易所
        FRequest.Buy.SecuID + 1,                //合约编码
        0,                                      //买卖标记
        FRequest.Buy.Type & 0x000F,            //开平仓标志
        FRequest.Buy.Type & 0x00F0,            //投保标记
        FRequest.Buy.Num,                       //委托数量
        FRequest.Buy.Price,                     //委托价格
        FJSDSet.JyCode                                     //交易编码
    );

    ODS("BUY,Code:%s,Price:%0.3f,Num:%d,Open:%d",
        FRequest.Buy.SecuID,FRequest.Buy.Price,FRequest.Buy.Num,FRequest.Buy.Type & 0x000F);

    TStringList *lstDD = new TStringList();
    try
    {
    //    1.成功标志 Y  2.委托单号 3. ...... 8.委托单状态代码
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
			      NewAns(1);
            strncpy((*FAnswer)[0].Buy.ContractID, lstDD->Strings[INDEX(2)].c_str(), 6);
        }
        else
        {
            //ODS(lstDD->Strings[4].c_str());
            ODS("BUY:%s",lstDD->Text.c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
    }
    
    return 0;
}

int TTrdItf_JSDFF::Sell()
{
    AnsiString cmd;
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%c|%s|%d|%d|%d|%d|%.3f|%s|",
        GetRequestHead("6021").c_str(),
        FJSDSet.jysID,                          //交易所
        FRequest.Sell.SecuID + 1,               //合约编码
        1,                                      //买卖标记
        FRequest.Sell.Type & 0x000F,             //开平仓标志
        FRequest.Sell.Type & 0x00F0,             //投保标记
        FRequest.Sell.Num,                      //委托数量
        FRequest.Sell.Price,                    //委托价格
        FJSDSet.JyCode                                      //交易编码
    );
    ODS("SELL,Code:%s,Price:%0.3f,Num:%d,Open:%d",
        FRequest.Sell.SecuID,FRequest.Sell.Price,FRequest.Sell.Num,FRequest.Sell.Type & 0x000F);

    TStringList *lstDD = new TStringList();
    try
    {
    //    1.成功标志 Y  2.委托单号 3......
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
			      NewAns(1);
            strncpy((*FAnswer)[0].Buy.ContractID, lstDD->Strings[INDEX(2)].c_str(), 6);
        }
        else
        {
            //ODS(lstDD->Strings[4].c_str());
            ODS("SELL:%s",lstDD->Text.c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
    }
    
    return 0;
}


//---------------------------------------------------------------------------
//功能号 6022|营业部代码|委托方式|客户号|客户密码|交易所|合约编码|买卖标记|开平仓标志
//投保标记|委托数量|委托价格|委托单号|撤销数量|系统中心号|席位号(连接v6网关必须填写)
//---------------------------------------------------------------------------
int TTrdItf_JSDFF::Undo() //委托撤单
{
    AnsiString cmd;
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%c|||||||%s|||%s|",
        GetRequestHead("6022").c_str(),
        FJSDSet.jysID,                          //交易所
        FRequest.Undo.ContractID,               //合同号
        FJSDSet.seatID                          //席位号，必须填
    );

    TStringList *lstDD = new TStringList();
    try
    {
    //  成功标志 Y（表示已接受撤单请求）|委托单号
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) != DEF_ACK_OK)
        {
            //ODS(lstDD->Strings[4].c_str());
            ODS("UNDO:%s",lstDD->Text.c_str());
            return -1;
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

int TTrdItf_JSDFF::QryFutureCode()
{
  return 0;
}
