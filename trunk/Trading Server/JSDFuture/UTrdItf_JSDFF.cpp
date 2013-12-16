//---------------------------------------------------------------------------

#include <IniFiles.hpp>
#include <assert.h>
#include <stdio.h>

#pragma hdrstop
#include "UTrdItf_JSDFF.h"
#include "uRecvEventsTh.h"

#pragma package(smart_init)

/*
Buy_or_sale 说明
状态C 状态E 标志
买入 Buy 0
卖出 Sale 1
未知 Unknow 其他
*/
const char BUY = '0';
const char SELL= '1';

/*
eo_flag 说明
状态C 状态E 标志
开仓 open 0
平仓 close 1
平今 close today 2
未知 unknow 其他
*/
const char OPEN        = '0';
const char CLOSE       = '1';
const char CLOSE_TODAY = '2';
const char CLOSE_TODAY2= '3';
/*
sh_flag 说明
状态C 状态E 标志
投机 tou 0
保值 bao 1
*/
const char * TOU = "0";
const char * BAO = "1";
/*
Wt_state 说明
状态C 状态E               标志
等待报入 Waiting           n
正在申报 Baodaning         s
已报入   Already baodaned  a
部分成交 Partial completed p
全部成交 Completed         c
正在撤销 Deleteing         f
系统撤销 System disable    m
系统撤销 User disable      q
已撤消   Total deleted     d
部成部撤 Partial completed and deleted b
未知状态 Unknow            其它
*/
const char WAITING = 'n';
const char SENDING = 's';
const char ACCEPTED= 'a';
const char FILLING = 'p';
const char FILLED  = 'c';
const char DELETEING='f';
const char SYS_REJECTED= 'm';
const char USER_REJECTED='q';
const char DELETED = 'd';
const char PCPD = 'b';

/*
人民币 : 1
美元:    2
港币:    3
*/
//---------------------------------------------------------------------------

long convert_datetime_str_to_long(const char * str)
{
    // remove non alpha characters
    char buf[255];
    int j = 0;
    for (_SIZE_T i = 0; i < strlen(str); i++) {
        if( isdigit(str[i]) )
        {
            buf[j++] = str[i];
        }
    }
    buf[j] = 0;

    return atoi(buf);
}

order_type  SConvertOrderType(const char *t)
{
    if (t == NULL || strlen(t) < 2 ) {
        return otNo;
    }

    char OC = t[1];
    char BS = t[0];

    if (OC == OPEN && BS == BUY )
    {
        return  otOpenBuy;
    }
    else if( OC == OPEN && BS == SELL )
    {
        return  otOpenSell;
    }
    else if(OC == CLOSE && BS == BUY)
    {
        return otCloseBuy;
    }
    else if(  OC == CLOSE && BS == SELL  )
    {
        return otCloseSell;
    }
    else if((OC == CLOSE_TODAY || OC == CLOSE_TODAY2) && BS == BUY)
    {
        return otCloseTodayBuy;
    }
    else if((OC == CLOSE_TODAY || OC == CLOSE_TODAY2) && BS == SELL )
    {
        return otCloseTodaySell;
    }
    else
    {
        ODS('E',PLUGINNAME,"%s", t);
        return otNo;
    }
}
//---------------------------------------------------------------------------
TTrdItf_JSDFF::TTrdItf_JSDFF(const char *psetupfile,ADDLOG plogfunc)
:TTrdItfBase(psetupfile,plogfunc)
{
    //memset(&FJSDSet,0,sizeof(TJSDSet));
    FJSDSet.SvrIp = "127.0.0.1";
    FJSDSet.SvrPort = 17990;
    FJSDSet.TimeOut = 5000;
    FJSDSet.debug_mode = false;
    FJSDSet.branch_no = "999";
    FJSDSet.gw_ver = "v6";
    strncpy(FJSDSet.jysID , "CBAG",5);

    FidTcp = new TIdTCPClient(NULL);
    FidIPWatch = new TIdIPWatch(NULL);
    FidIPWatch->HistoryEnabled =false;
}
//---------------------------------------------------------------------------
TTrdItf_JSDFF::~TTrdItf_JSDFF()
{
    CloseLink();
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
void TTrdItf_JSDFF::SetError(int code,const char * error)
{
    lstrcpyn( FLastError.Sender ,"JSDFF", SEQ_LEN);
    FLastError.ErrorCode = code;
    lstrcpyn( FLastError.Text,error,MAX_TEXT );
    ODS('E',PLUGINNAME, "错误提示:%s,ErrNo:%d",FLastError.Text,FLastError.ErrorCode );
}

AnsiString TTrdItf_JSDFF::GetErrorText(int code, const char *error)
{
    SetError(code,error);
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
	try
	{
		if( FidTcp->Connected() !=true )
			return IntToStr(ERR_REMOTE_OTHER_FAILED);
	}
	catch (Exception *e)
	{
		ODS('E',PLUGINNAME,"券商柜台连接意外断开! 错误信息:%s.",e->Message.c_str());
		return  IntToStr(ERR_REMOTE_OTHER_FAILED);
	}
    //清除上次的返回信息
    TByteDynArray da;
    try
    {
        if( FidTcp->Socket->Readable(10) == true )
        {
            FidTcp->Socket->ReadBytes(da,-1,true);
        }
        FidTcp->Socket->Write(cmd);
    }
    catch( Exception &e )
    {
        ODS('E',PLUGINNAME,"券商柜台发送数据失败! 错误信息:%s.",e.Message.c_str());
        return  IntToStr(ERR_REMOTE_SEND_FAILED) ;
    }

    da.set_length(0);

    try
    {
        FidTcp->Socket->ReadBytes(da,-1,true);
    }
    catch(Exception &e)
    {
        ODS('E',PLUGINNAME,"券商柜台接收数据失败! 错误信息:%s.",e.Message.c_str());
        return  IntToStr(ERR_REMOTE_RECV_FAILED) ;
    }

    if (da.Length == 0)
    {
        ODS('E',PLUGINNAME,"券商柜台接收数据量为0!");
        return IntToStr(ERR_REMOTE_RECV_FAILED)  ;
    }
    AnsiString ret = (char*)&da[0];

    return ret;
}
//---------------------------------------------------------------------------
// count 表示至少有几个值
int TTrdItf_JSDFF::SplitData(AnsiString SD, TStringList *lstDD, int count)
{
    assert(lstDD != NULL);

    SplitString(SD.c_str(),SD.Length(),lstDD,'|');

    if( lstDD->Count == 1 )
    {
        SetError(lstDD->Strings[0].ToIntDef(-2), "柜台数据传输错误");
        return FLastError.ErrorCode;
    }
    else if (lstDD->Count < 4)
    {
        SetError(-501, "数据解析失败");
        return DEF_ACK_ERROR;
    }

    if (lstDD->Strings[0] != "A")
    {
        SetError(-502, "Answer Data Error");
        return DEF_ACK_ERROR;
    }

    if (lstDD->Strings[3] == "N" )
    {
        if (lstDD->Count < 5)
            SetError(-503, ("返回N,但无错误描述,DATA:"+ SD).c_str());
        else if (lstDD->Count >= 5)
            SetError(lstDD->Strings[4].ToIntDef(-503),lstDD->Strings[5].c_str());
        return DEF_ACK_ERROR;
    }

    if (lstDD->Count >= count)
        return DEF_ACK_OK;

    SetError(-504, ("返回的数据条数不对！,DATA:"+ SD).c_str());
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
            FidTcp->ConnectTimeout = FJSDSet.TimeOut * 2;
            FidTcp->ReadTimeout =    FJSDSet.TimeOut;
            FidTcp->Connect();
        }
    }
    catch (Exception *e)
    {
        ODS('E',PLUGINNAME,"连接柜台失败! 错误信息:%s.",e->Message.c_str());
    }

    return FidTcp->Connected()==true ? 0 : -1;
}

void TTrdItf_JSDFF::CloseLink(void)
{
    try
	{
		FidTcp->Disconnect();
    }
    catch(...)
    {

    }

	//FDB.disconnect();
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

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 12) == DEF_ACK_OK)
        {
            strncpy(FAccInfo.Capital, FRequest.SetAccount.Account, 20);
            strncpy(FAccInfo.PW, FRequest.SetAccount.PW, 13);

            if( strcmpi( FJSDSet.gw_ver.c_str(),  "v6" ) == 0 )
            {

                //6040 查询客户交易编码---GETCLIENTMAPNO
                //（1） 功能号 6040
                //（2） 营业部代码
                //（3） 委托方式
                //（4） 客户号
                //（5） 客户密码
                //（6） 交易所
                //（7） 席位号（空：全部）
                //返回应答：
                //成功
                //第一个包：
                //（1） 成功标志 Y
                //（2） 记录个数（后续包个数）
                //后续包
                //（1） 客户号
                //（2） 交易所
                //（3） 交易编码
                //（4） 主交易编码标志
                //（5） 席位号
                //错误
                //（1） 出错标志 N
                //（2） 错误代码
                //（3） 出错内容

                NewAns(1);
                memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));

                for( int i=0;i<strlen( FJSDSet.jysID );i++)
                {
                    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
                    cmd.cat_printf("%s|%c|",GetRequestHead("6040").c_str(),FJSDSet.jysID[i]);

                    if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
                    {
                        int count = lstDD->Strings[4].ToIntDef(0);
                        for (int j = 0; j < count; j++)
                        {
                            if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 5) == DEF_ACK_OK)
                            {
                                if( FJSDSet.jysID[i]==lstDD->Strings[INDEX(2)][1])
                                {
                                    //设置客户交易编码
                                    FJSDSet.JyCode[i]=lstDD->Strings[INDEX(3)];
                                    //设置席位号
                                    FJSDSet.seatID[i]=lstDD->Strings[INDEX(5)];
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        return AnsiString(FRequest.SetAccount.Account).ToIntDef(DEF_OTHER_ERROR);
                    }
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
            return FLastError.ErrorCode;
        }
    }
    __finally
    {
        delete lstDD;
    }

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
            (*FAnswer)[0].QryMoney.MoneyInfo.MoneyType = motRMB;
			(*FAnswer)[0].QryMoney.MoneyInfo.balance = StrToFloat(lstDD->Strings[INDEX(11)]);  //动态权益
            (*FAnswer)[0].QryMoney.MoneyInfo.available= StrToFloat(lstDD->Strings[INDEX(10)]); //可用资金
        }
		else
        {
            return FLastError.ErrorCode;
        }
    }
    __finally
    {
    		delete lstDD;
    }

    return 0;
}


//--------------------------------------------------------------------------
//查询当日委托
//功能号 6019|营业部代码|委托方式|客户号|客户密码|
//查询单个委托
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryCurCsn()    //当日委托查询
{
    AnsiString cmd;

    if (FRequest.QryCurCsn.OrderID[0] != 0)
    {  // 查单个委托
        /*6.11 6020 委托状态查询--- QUERYWTSTATE
        （1） 功能号 6020
        （2） 营业部代码
        （3） 委托方式
        （4） 客户号
        （5） 客户密码
        （6） 委托单号
        （7） 下单席位
        返回应答：
        成功
        （1） 成功标志 Y
        （2） 委托单状态
        （3） 成交数量
        （4） 未成交数量
        （5） 委托数量
        （6） 成交价格
        （7） 撤单时间
        （8） 委托单号
        （9） 席位号
        （10）下单席位
        错误
        （1） 出错标志 N
        （2） 错误代码
        （3） 出错内容
        */
        AnsiString seat,ordid  ;
        //splitOrdid(FRequest.QryCurCsn.OrderID,seat,ordid);
        ordid = FRequest.QryCurCsn.OrderID;
        cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
        cmd.cat_printf("%s|%s|%s|",GetRequestHead("6020").c_str(),ordid.c_str(),seat.c_str());
        TStringList *lstDD = new TStringList();
        try
        {
            //A|192.168.123.124| |Y|a|0|1|1|0| |51| |
            if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 9) == DEF_ACK_OK)
            {
                TOrderInfo ci;
                memset(&ci, 0, sizeof(TOrderInfo));
                AnsiString nordid;
                //nordid.printf("%s:%s",seat.c_str(),   //lstDD->Strings[INDEX(7)].c_str(),
                //	lstDD->Strings[INDEX(8)].c_str());
                //strncpy(ci.ContractID,nordid.c_str(), SEQ_LEN);

                strncpy(ci.ContractID,lstDD->Strings[INDEX(8)].c_str(), SEQ_LEN);
                strncpy(ci.SecuID,"", CODE_LEN);
                ci.Market = ConvertMarketType(seat.c_str());
                ci.Time =   convert_datetime_str_to_long(lstDD->Strings[INDEX(7)].c_str());
                ci.Date =   convert_datetime_str_to_long(FormatDateTime("yyyymmdd",Date()).c_str());
                ci.Type   = ConvertOrderType("");
                ci.State  = ConvertOrderState(lstDD->Strings[INDEX(2)].c_str());
                ci.CsnVol = MyStrToInt(lstDD->Strings[INDEX(5)]);
                ci.TrdVol = MyStrToInt(lstDD->Strings[INDEX(3)]);
                if ( ci.State == osbw || ci.State ==osyc || ci.State ==osyf)
                {
                    ci.CancelVol = ci.TrdVol - ci.CsnVol ;
                }
                ci.CsnPrice  = 0;
                ci.TrdPrice  = StrToFloat(lstDD->Strings[INDEX(6)]);
                strncpy(ci.Account,"",ACC_LEN);
                strncpy(ci.SeqNum,lstDD->Strings[INDEX(8)].c_str(),SEQ_LEN);

                NewAns(1);
                memcpy(&(*FAnswer)[0].QryCurCsn.OrderInfo, &ci, sizeof(TOrderInfo));
            }
            else
            {
                return FLastError.ErrorCode;
            }
        }
       	__finally
        {
        	delete lstDD;
        }
    }
    else if( FRequest.QryCurCsn.MaxRecord == 0 )  // 查所有
    {
        TList * lstAns = new TList();
        TStringList *lstDD = new TStringList();
        cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
        cmd.cat_printf("%s|",GetRequestHead("6019").c_str());

        try
        {
            /*
            （1） 交易所代码
            （2） 交易所名称
            （3） 委托单号
            （4） 合约编码
            （5） 合约名称
            （6） 委托单状态代码
            （7） 委托单状态名称 // 全部成交/部分成交/全部撤单/已经申报/正在处理/未处理错误
            （8） 买卖标记
            （9） 买卖类别名称 // 买入/卖出
            （10）开平仓标志
            （11）开平仓名称 // 开仓/平仓/平今
            （12）投保标记
            （13）投保名称
            （14）委托数量（成交数量 + 未成交数量 + 撤消数量）
            （15）委托价格
            （16）成交数量
            （17）成交价格
            （18）未成交数量
            （19）系统中心号
            （20）交易编码
            （21）空 保留
            （22）委托时间
            （23）申报时间
            （24）空 保留
            （25）空 保留
            （26）撤单时间
            */
            if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
            {
                int count = lstDD->Strings[4].ToInt();
                AnsiString nordid;
                for (int i = 0; i < count; i++)
                {
                    if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 26) == DEF_ACK_OK)
                    {
                        TOrderInfo *ci = new TOrderInfo;
                        memset(ci, 0, sizeof(TOrderInfo));

                        ci->Market = ConvertMarketType(lstDD->Strings[INDEX(1)].c_str());

                        //nordid.printf("%s:%s",GetSeatId(ci->Market).c_str(),
                        //	lstDD->Strings[INDEX(3)].c_str());

                        //strncpy(ci->ContractID,nordid.c_str(), SEQ_LEN);
                        strncpy(ci->ContractID,lstDD->Strings[INDEX(3)].c_str(), SEQ_LEN);
                        //strncpy(ci->SecuID,    lstDD->Strings[INDEX(4)].c_str(), CODE_LEN);
                        strncpy(ci->SecuID, convert_to_PTS_code( lstDD->Strings[INDEX(4)].c_str(),ci->Market).c_str(), CODE_LEN);
                        ci->Time =   convert_datetime_str_to_long(lstDD->Strings[INDEX(22)].c_str());
                        ci->Date =   convert_datetime_str_to_long(FormatDateTime("yyyymmdd",Date()).c_str());
                        ci->Type   = ConvertOrderType((lstDD->Strings[INDEX(8)]+lstDD->Strings[INDEX(10)]).c_str());
                        ci->State  = ConvertOrderState(lstDD->Strings[INDEX(6)].c_str());
                        ci->CsnVol = MyStrToInt(lstDD->Strings[INDEX(14)]);
                        ci->TrdVol = MyStrToInt(lstDD->Strings[INDEX(16)]);
                        if ( ci->State == osbw || ci->State ==osyc || ci->State ==osyf)
                        {
                            ci->CancelVol = ci->TrdVol - ci->CsnVol ;
                        }
                        ci->CsnPrice  = StrToFloat(lstDD->Strings[INDEX(15)]);
                        ci->TrdPrice  = StrToFloat(lstDD->Strings[INDEX(17)]);
                        strncpy(ci->Account, lstDD->Strings[INDEX(20)].c_str(),ACC_LEN);
                        strncpy(ci->SeqNum,lstDD->Strings[INDEX(3)].c_str(),SEQ_LEN);
                        lstAns->Add(ci);
                    }
                    else
                    {
                        return FLastError.ErrorCode;
                    }
                }

                if (lstAns->Count > 0)
                {
                    NewAns(lstAns->Count);
                    for (int i = 0; i < lstAns->Count; i++)
                    {
                        TOrderInfo *ci = (TOrderInfo *)lstAns->Items[i];
                        memcpy(&(*FAnswer)[i].QryCurCsn.OrderInfo, ci, sizeof(TOrderInfo));
                    }
                }

                for (int i = 0; i < lstAns->Count; i++)
                {
                    TOrderInfo *ci = (TOrderInfo *)lstAns->Items[i];
                    delete ci;
                }
                lstAns->Clear();
            }
           	else
            {
                return FLastError.ErrorCode;
            }
        }
        __finally
        {

        		delete lstDD;
        		delete lstAns;
        }
    }
    else
    {
        SetError(-1, "不支持增量查询");
        return -1;
    }
    return 0;
}

//--------------------------------------------------------------------------
//查询当日成交
//功能号 6013|营业部代码|委托方式|客户号|客户密码|起始日期----YYYYMMDD|结束日期----YYYYMMDD
//如果连接V6的网关需要使用6053来查询历史成交明细,6013只用来查询当日成交
//--------------------------------------------------------------------------
/*
返回应答：
成功
第一个包：
（1）成功标志 Y
（2）记录个数（后续包个数）
当日成交的后续包如下：
（1） 交易所代码
（2） 交易所名称
（3） 委托单号
（4） 合约编码
（5） 合约名称
（6） 买卖标记
（7） 买卖类别名称 // 买入/卖出
（8） 开平仓标志
（9） 开平仓名称 // 开仓/平仓/平今
（10）投保标记
（11）投保名称
（12）成交数量
（13）成交价格
（14）当日日期
（15）交易编码
（16）系统号
（17）成交号
（18）交割期
（19）成交时间
（20）席位号
（21）币种
*/
int TTrdItf_JSDFF::QryCurTrd()    //当日成交查询
{
	try
	{
		if( FidTcp->Connected() !=true )
			return ERR_REMOTE_OTHER_FAILED;
	}
	catch (Exception *e)
	{
		ODS('E',PLUGINNAME,"券商柜台连接意外断开! 错误信息:%s.",e->Message.c_str());
		return  ERR_REMOTE_OTHER_FAILED;
	}

    std::vector<TTradeInfo>  list;
    try
	{
		trade_db      FDB;
		FDB.connect();
        FDB.qry_trades(this->FAccInfo.Capital,FRequest.QryCurTrd.OrderID,FRequest.QryCurTrd.SeqNum,
            FRequest.QryCurTrd.MaxRecord,list);
    }
    catch(std::string &err)
    {
        this->SetError(-1,err.c_str());
        return -1;
    }

    if (list.size() > 0)
    {
        NewAns(list.size());
        for (int i = 0; i < list.size(); i++)
        {
            TTradeInfo *ti = (TTradeInfo *)&list[i];
            memcpy(&(*FAnswer)[i].QryCurTrd.TrdInfo, ti, sizeof(TTradeInfo));
        }
    }
    return 0;
    /*
    AnsiString cmd;
    AnsiString date = Now().FormatString("yyyymmdd");

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    cmd.cat_printf("%s|%s|%s|",
    GetRequestHead("6013").c_str(),
    date.c_str(),
    date.c_str());


    try
    {

    if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
    {
    int count = lstDD->Strings[4].ToInt();
    for (int i = 0; i < count; i++)
    {
    if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
    {
    TTradeInfo *ti = new TTradeInfo;
    memset(ti, 0, sizeof(TTradeInfo));

    strncpy(ti->ContractID,lstDD->Strings[INDEX(3)].c_str(), SEQ_LEN);
    strncpy(ti->SecuID,   lstDD->Strings[INDEX(4)].c_str(), CODE_LEN);
    strncpy(ti->TrdID,  lstDD->Strings[INDEX(15)].c_str(), SEQ_LEN);
    ti->Time =   convert_datetime_str_to_long(lstDD->Strings[INDEX(19)].c_str());
    ti->Date =   convert_datetime_str_to_long(lstDD->Strings[INDEX(14)].c_str());
    ti->Type  = ConvertOrderType(lstDD->Strings[INDEX(6)].c_str());
    ti->Vol   = MyStrToInt(lstDD->Strings[INDEX(12)]);
    ti->Price = MyStrToFloat(lstDD->Strings[INDEX(13)]);
    ti->Market = ConvertMarketType(lstDD->Strings[INDEX(1)].c_str());
    strncpy(ti->Account , lstDD->Strings[INDEX(15)].c_str(),ACC_LEN);
    strncpy(ti->SeqNum, lstDD->Strings[INDEX(3)].c_str(),SEQ_LEN);
    lstAns->Add(ti);
    }
    else
    {
    return -1;
    }
    }

    if (lstAns->Count > 0)
    {
    NewAns(lstAns->Count);
    for (int i = 0; i < lstAns->Count; i++)
    {
    TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
    memcpy(&(*FAnswer)[i].QryCurTrd.TrdInfo, ti, sizeof(TTradeInfo));
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
    return -1;
    }
    }
    catch( Exception &e)
    {
    lstrcpyn( FLastError.Sender ,"JSDFF", SEQ_LEN);
    FLastError.ErrorCode = -1;
    lstrcpyn( FLastError.Text,e.Message.c_str(),MAX_TEXT );
    ODS('E',PLUGINNAME, "错误提示:%s,ErrNo:%d",FLastError.Text,FLastError.ErrorCode );
    }

    delete lstDD;
    delete lstAns;

    */
}

//--------------------------------------------------------------------------
//查询所有持仓
//功能号 6014|营业部代码|委托方式|客户号|客户密码|日期---YYYYMMDD|
//--------------------------------------------------------------------------
int TTrdItf_JSDFF::QryStocks()    //查询帐号中所有的股份
{
    AnsiString cmd;
    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    cmd.cat_printf("%s|%s|",
        GetRequestHead("6014").c_str(),
        Now().FormatString("yyyymmdd").c_str());

    try
    {
        /*
        返回应答：
        成功
        第一个包
        （1）成功标志 Y
        （2） 记录个数（后续包个数）
        后续包：
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
        错误
        （1）出错标志 N
        （2）错误代码
        （3）出错内容
        */

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN+2) == DEF_ACK_OK)
        {

            //最后两条记录为买小计和卖小计，所以要减2
            int count = lstDD->Strings[4].ToInt()-2;
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 19) == DEF_ACK_OK)
                {
                    TStockInfo *si = new TStockInfo;
                    memset(si, 0, sizeof(TStockInfo));
                    strncpy(si->Account,   lstDD->Strings[INDEX(14)].c_str(),ACC_LEN);     //存入交易编码
                    si->PosDir = pdLong;
                    si->Market = ConvertMarketType(lstDD->Strings[INDEX(1)].c_str());
                    strncpy(si->SecuID, convert_to_PTS_code(lstDD->Strings[INDEX(3)].c_str(),si->Market).c_str(), CODE_LEN);
                    si->Balance =  MyStrToInt(lstDD->Strings[INDEX(5)]) -MyStrToInt(lstDD->Strings[INDEX(18)]);
                    si->PosNum =  MyStrToInt(lstDD->Strings[INDEX(5)]);
                    si->Available = si->PosNum;
                    si->CostPrice = MyStrToFloat(lstDD->Strings[INDEX(6)]);
                    si->CurPrice = MyStrToFloat(lstDD->Strings[INDEX(11)]);
                    if (si->PosNum>0) {
                        lstAns->Add(si);
                    }
                    else delete si;

                    si = new TStockInfo;
                    memset(si, 0, sizeof(TStockInfo));
                    //strncpy(si->SecuID, lstDD->Strings[INDEX(3)].c_str(), CODE_LEN);
                    strncpy(si->Account,   lstDD->Strings[INDEX(14)].c_str(),ACC_LEN);     //存入交易编码
                    si->PosDir = pdShort;
                    si->Market = ConvertMarketType(lstDD->Strings[INDEX(1)].c_str());
                    strncpy(si->SecuID, convert_to_PTS_code(lstDD->Strings[INDEX(3)].c_str(),si->Market).c_str(), CODE_LEN);
                    si->Balance =  MyStrToInt(lstDD->Strings[INDEX(7)]) -MyStrToInt(lstDD->Strings[INDEX(19)]);
                    si->PosNum =  MyStrToInt(lstDD->Strings[INDEX(7)]);
                    si->Available = si->PosNum;
                    si->CostPrice = MyStrToFloat(lstDD->Strings[INDEX(8)]);
                    si->CurPrice = MyStrToFloat(lstDD->Strings[INDEX(11)]);
                    if (si->PosNum>0) {
                        lstAns->Add(si);
                    }
                    else delete si;

                }
                else
                {
                    return FLastError.ErrorCode;
                }
            }

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
            return FLastError.ErrorCode;
        }
    }
    __finally
    {

    	delete lstDD;
    	delete lstAns;
    }
    return 0;
}

//////交易函数/////
//---------------------------------------------------------------------------
//功能号 6021|营业部代码|委托方式|客户号|客户密码|交易所----数字|合约编码|买卖标记
//开平仓标志|投保标记|委托数量|委托价格|交易编码
//（1） 功能号 6021
//（2） 营业部代码
//（3） 委托方式
//（4） 客户号
//（5） 客户密码
//（6） 交易所
//（7） 合约编码
//（8） 买卖标记
//（9） 开平仓标志
//（10）投保标记
//（11）委托数量
//（12）委托价格
//（13）交易编码
//（14）席位号
//---------------------------------------------------------------------------
int TTrdItf_JSDFF::Order()
{
    AnsiString cmd;
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    cmd.cat_printf("%s|%c|%s|%c|%c|%s|%d|%.3f|%s|%s|",
        GetRequestHead("6021").c_str(),
        ConvertMarketType(FRequest.Order.Market)[0],//交易所
		convert_to_JSD_code(FRequest.Order.SecuID,FRequest.Order.Market).c_str(),                //合约编码
        ConvertOrderType(FRequest.Order.Type)[1],//买卖标记
        ConvertOrderType(FRequest.Order.Type)[0],//开平仓标志
        TOU,             //投保标记
        FRequest.Order.Num,                       //委托数量
        FRequest.Order.Price,                     //委托价格
        GetTradeCode(FRequest.Order.Market).c_str(),//交易编码
        GetSeatId(FRequest.Order.Market).c_str()
        );

    //ODS("BUY,Code:%s,Price:%0.3f,Num:%d,Open:%d",
    //    FRequest.Buy.SecuID,FRequest.Buy.Price,FRequest.Buy.Num,FRequest.Buy.Type & 0x000F);

    TStringList *lstDD = new TStringList();
    try
    {
        /*
        返回应答：
        正确
        （1）成功标志 Y
        （2）委托单号
        （3）交易所代码[v5 柜台提供]
        （4）交易所名称（v6 不提供，网关处理）
        （5）合约编码（品种代码+交割期，网关处理）
        （6）合约名称（v6 不提供，网关处理）
        （7）委托单状态代码[v5 柜台提供]
        （8）委托单状态名称（v6 不提供，网关处理）
        （9）买卖标记[v5 柜台提供]
        （10）买卖类别名称[买入/卖出] （v6 不提供，网关处理）
        （11）开平仓标志[v5 柜台提供]
        （12）开平仓名称[开仓/平仓/平今] （v6 不提供，网关处理）
        （13）投保标记[v5 柜台提供]
        （14）投保名称（v6 不提供，网关处理）
        （15）委托数量[v5 柜台提供]
        （16）委托价格[v5 柜台提供]
        （17）成交数量[v5 柜台提供]
        （18）成交价格[v5 柜台提供]
        （19）未成交数量[v5 柜台提供]
        （20）系统中心号[v5 柜台提供]
        （21）交易编码[v5 柜台提供]
        （22）交割期
        （23）委托时间
        （24）申报时间
        （25）委托方式
        （26）撤单用户
        （27）撤单时间
        （28）委托单类型
        （29）席位号
        （30）币种
        （31）下单席位
        */
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 31) == DEF_ACK_OK)
        {
            NewAns(1);
            //sprintf( (*FAnswer)[0].Order.ContractID,"%s:%s",
            //GetSeatId(FRequest.Order.Market).c_str(),
            //			lstDD->Strings[INDEX(31)].c_str(),
            //		   lstDD->Strings[INDEX(2)].c_str(),SEQ_LEN );

            sprintf( (*FAnswer)[0].Order.ContractID,"%s",
				lstDD->Strings[INDEX(2)].c_str(),SEQ_LEN );
        }
        else
        {
            return FLastError.ErrorCode;
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
/*
（1） 功能号 6022
（2） 营业部代码
（3） 委托方式
（4） 客户号
（5） 客户密码
（6） 交易所
（7） 合约编码
（8） 买卖标记
（9） 开平仓标志
（10）投保标记
（11）委托数量
（12）委托价格
（13）委托单号
（14）撤销数量
（15）系统中心号
（16）席位号
（17）下单席位
返回应答：
正确
（1） 成功标志 Y（表示已接受撤单请求）
（2）“撤单成功”
（3） 委托单号
（4） 席位号
（5） 委托状态标记
（6） 委托状态名称
（7） 委托数量
（8） 未成交数量
（9） 成交数量
（10）成交价格
（11）撤单时间
（12）交易所代码
（13）下单席位
错误
（1） 出错标志 N
（2） 错误代码
（3） 出错内容
*/
//---------------------------------------------------------------------------
int TTrdItf_JSDFF::Undo() //委托撤单
{
    AnsiString cmd;

    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    AnsiString seat,ordid  ;
    //splitOrdid(FRequest.Undo.ContractID,seat,ordid);
    ordid = FRequest.Undo.ContractID;
    seat = GetSeatId(FRequest.Undo.Market);
    if (seat.Length()==0)
    {
        // query from order table
        try
        {
            char mkt[2];
			mkt[1] = 0;
			trade_db      FDB;
			FDB.connect();
            mkt[0] = FDB.qry_order_market(this->FAccInfo.Capital,FRequest.Undo.ContractID);
            seat = GetSeatId(this->ConvertMarketType(mkt));
        }
        catch(std::string &err)
        {
			this->SetError(-1,err.c_str());
            return -1;
        }
    }
    cmd.cat_printf("%s||||||||%s|||%s||",
        GetRequestHead("6022").c_str(),
        ordid.c_str(),                //合同号
        seat.c_str()        //席位号，必须填
        );

    TStringList *lstDD = new TStringList();
    try
    {
        //  成功标志 Y（表示已接受撤单请求）|委托单号
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) != DEF_ACK_OK)
        {
            return FLastError.ErrorCode;
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

bool TTrdItf_JSDFF::GetConfig(void)
{
    if( FSetupFile== NULL ) return false;

    TMemIniFile *ini = new TMemIniFile( FSetupFile );
    try
    {
        // 判断是否存在插件的设置，没有的话返回false以便系统能够生成默认的设置
        if( ini->SectionExists(PLUGINNAME) == false ) return false;

        FJSDSet.SvrIp            = ini->ReadString (PLUGINNAME,"SvrIP",FJSDSet.SvrIp);
        FJSDSet.SvrPort          = ini->ReadInteger(PLUGINNAME,"SvrPort",FJSDSet.SvrPort);
        FJSDSet.TimeOut          = ini->ReadInteger(PLUGINNAME,"TimeOut",FJSDSet.TimeOut);
        FJSDSet.debug_mode       = ini->ReadBool(PLUGINNAME,"debug_mode",FJSDSet.debug_mode);
        FJSDSet.branch_no        = ini->ReadString(PLUGINNAME,"branch_no",FJSDSet.branch_no);
        FJSDSet.gw_ver           = ini->ReadString (PLUGINNAME,"gw_ver",FJSDSet.gw_ver);
        FJSDSet.sysCenter        = ini->ReadString (PLUGINNAME,"sysCenter",FJSDSet.sysCenter);
        lstrcpyn(FJSDSet.jysID,ini->ReadString (PLUGINNAME,"jysID",FJSDSet.jysID).c_str(),5);
        /*
        for(int i=0;i<4;i++)
        {
        FJSDSet.seatID[i] =  ini->ReadString (PLUGINNAME,"seatID" + IntToStr(i),FJSDSet.seatID[i]);
        FJSDSet.JyCode[i] =  ini->ReadString (PLUGINNAME,"JyCode" + IntToStr(i),FJSDSet.JyCode[i]);
        }
        */
    }
    __finally
    {
        delete ini;
    }
    return true;
}

void TTrdItf_JSDFF::SetConfig(void)
{
    if( FSetupFile== NULL ) return ;

    TMemIniFile *ini = new TMemIniFile( FSetupFile );
    try
    {
        ini->WriteString (PLUGINNAME,"SvrIP",            FJSDSet.SvrIp);
        ini->WriteInteger(PLUGINNAME,"SvrPort",          FJSDSet.SvrPort);
        ini->WriteInteger(PLUGINNAME,"TimeOut",          FJSDSet.TimeOut);
        ini->WriteBool   (PLUGINNAME,"debug_mode",       FJSDSet.debug_mode);
        ini->WriteString(PLUGINNAME,"branch_no",        FJSDSet.branch_no);
        ini->WriteString (PLUGINNAME,"gw_ver",           FJSDSet.gw_ver);
        ini->WriteString (PLUGINNAME,"sysCenter",        FJSDSet.sysCenter);
        ini->WriteString (PLUGINNAME,"jysID",            FJSDSet.jysID);
        for(int i=0;i<strlen( FJSDSet.jysID );i++)
        {
            ini->WriteString (PLUGINNAME,"seatID" + IntToStr(i),FJSDSet.seatID[i]);
            ini->WriteString (PLUGINNAME,"JyCode" + IntToStr(i),FJSDSet.JyCode[i]);
        }

        ini->UpdateFile();
    }
    __finally
    {
        delete ini;
    }
}

market_type  TTrdItf_JSDFF::ConvertMarketType(const char *t)
{
    if(t==NULL || strlen(t)<1 ) return mtNo;

    if( strlen(t) == 1 )
    {
        if(t[0] ==  FJSDSet.jysID[0])
            return mtFZZ;
        else if( t[0] == FJSDSet.jysID[1])
            return mtFDL;
        else if( t[0] == FJSDSet.jysID[2] )
            return mtFSH;
        else if( t[0] == FJSDSet.jysID[3] )
            return mtJJS;
        else
            return mtNo;
    }
    else
    {
        if( lstrcmpi(t ,  FJSDSet.seatID[0].c_str())==0)
            return mtFZZ;
        else if( lstrcmpi(t , FJSDSet.seatID[1].c_str())==0)
            return mtFDL;
        else if( lstrcmpi(t , FJSDSet.seatID[2].c_str())==0 )
            return mtFSH;
        else if( lstrcmpi(t , FJSDSet.seatID[3].c_str())==0 )
            return mtJJS;
        else
            return mtNo;
    }
	return mtNo;
}

order_type   TTrdItf_JSDFF::ConvertOrderType(const char *t)
{
    return SConvertOrderType(t);
}

order_state  TTrdItf_JSDFF::ConvertOrderState(const char *t)
{
    /*
    oswb = '0', //未报(等待申报中...)
    osyb = '1', //已报(已经报了,但没有任何成交,等待成交中...)
    osdc = '2', //待撤(撤单命令已下等待撤单)
    osbw = '3', //部撤(确定状态,部分撤销，部分成交)
    osyc = '4', //已撤(确定状态,全部撤销了)
    oscj = '5', //已成(确定状态,完全成交)
    osyf = '6', //已废(确定状态,系统撤单)
    osbc = '7', //部成(已经有成交了,正在成交中...
    osno = 'N'  //未知
    */

    if( t==NULL || strlen(t) < 1 ) return osno;

    switch(t[0])
    {
    case WAITING:
    case SENDING:
        return oswb;
    case ACCEPTED:
        return osyb;
    case FILLING:
        return osbc;
    case FILLED:
        return oscj;
    case DELETEING:
        return osdc;
    case SYS_REJECTED:
        return osyf;
    case USER_REJECTED:
        return osyf;
    case DELETED:
        return osyc;
    case PCPD:
        return osbw;
    }
    return osno;
}

pos_direction TTrdItf_JSDFF::ConvertPosDir(const char *t)
{
    /*
    pdNo    = 'U', // 未知
    pdNet   = 'N', // 净
    pdLong	= 'L', // 多头
    pdShort = 'S'	 // 空头
    */
    return pdNo;
}

money_type   TTrdItf_JSDFF::ConvertMoneyType(const char *t)
{
    /*
    motRMB = 'R', //RMB
    motUSD = 'U', //USD
    motHKD = 'H', //HKD
    motNo  = 'N'  //未知
    */
    return motNo;
}

char *  TTrdItf_JSDFF::ConvertMarketType(market_type t)
{
    char ret[2] = {'0','0'};
    switch(t)
    {
    case mtFZZ : ret[0] = FJSDSet.jysID[0];
        break;
    case mtFDL : ret[0] = FJSDSet.jysID[1];
        break;
    case mtFSH : ret[0] = FJSDSet.jysID[2];
        break;
    case mtJJS : ret[0] = FJSDSet.jysID[3];
        break;
    }
    return ret;
}

char *  TTrdItf_JSDFF::ConvertOrderType(order_type t)
{
    char ret[3]={'0','0','0'};
    switch(t)
    {
    case otOpenBuy:
        ret[0] = OPEN;
        ret[1] = BUY;
        break;
    case otOpenSell:
        ret[0] = OPEN;
        ret[1] = SELL;
        break;
    case otCloseBuy :
        ret[0] = CLOSE;
        ret[1] = BUY;
        break;
    case otCloseSell:
        ret[0] = CLOSE;
        ret[1] = SELL;
        break;
    case otCloseTodayBuy:
        ret[0] = CLOSE_TODAY;
        ret[1] = BUY;
        break;
    case otCloseTodaySell:
        ret[0] = CLOSE_TODAY;
        ret[1] = SELL;
        break;
    }
    return ret;
}

AnsiString TTrdItf_JSDFF::convert_to_PTS_code(const char * jsdcode,market_type mt)
{
    if (mt!= mtFZZ) {
        return jsdcode;
    }
    // 将郑州的金士达代码转换为PTS的代码如 SR1001 to SR001 ,SR0909 to SR909
    assert(jsdcode != NULL );
    int len = strlen(jsdcode);
    AnsiString ret;
    for( int i=0;i<len;i++)
    {
        if (isalpha(jsdcode[i])) {
            ret = ret + jsdcode[i];
        }
        else
        {
            ret =ret + AnsiString(jsdcode + i+1);
            return ret;
        }
    }
    return ret;
}

AnsiString TTrdItf_JSDFF::convert_to_JSD_code(const char * ptscode,market_type mt)
{
    if (mt!= mtFZZ) {
        return ptscode;
    }
    // 将郑州的PTS的代码转换为金士达的代码如 SR001 to SR1001  ,SR909 to SR0909
    unsigned short y,m,d;
    DecodeDate(Date(),y,m,d);
	y = y % 100;

    assert(ptscode != NULL );
    int len = strlen(ptscode);

    AnsiString ret ="";

	char year[10] = {"\0"};
    const char *month = NULL;
    for( int i=0;i<len;i++)
    {
        if (isdigit(ptscode[i]))
        {
            // 找第一个数字为年份
            year[0] = ptscode[i];
            year[1] = 0;
            month = ptscode + i +1;
            if (strlen(month)!=2) {
                return ptscode;
            }
            else
            {
                int lyear = atoi(year);
                if (abs(lyear-y)>=1) {
                    lyear=y+1;
                }
                ret.cat_printf("%02d%s",lyear,month);
                return ret;
            }
        }
        else
        {
            ret = ret + ptscode[i];
        }
    }
    return ret;
}

/*
6031 读营业部名称---GETYYBMC（请求应答连接心跳）
（1）	功能号 6031
（2）	营业部代码
（3）	委托方式
（4）	客户号
（5）	客户密码

返回应答：
 成功
（1）	成功标志  Y
（2）	营业部名称
错误
（1）	出错标志  N
（2）	错误代码
（3）	出错内容
*/
int TTrdItf_JSDFF::QryYYB(void)     //资金查询
{
	AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

	cmd.cat_printf("%s|%s|",
		GetRequestHead("6031").c_str()
		);

	TStringList *lstDD = new TStringList();
    try
	{
		if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
			ODS('M',PLUGINNAME,"Dogfood:%s",lstDD->Strings[INDEX(2)].c_str());
        }
        else
        {
            return FLastError.ErrorCode;
        }
    }
    __finally
    {
    		delete lstDD;
    }

    return 0;
}


int  TTrdItf_JSDFF::KeepAlive(void)
{
	g_recvth->SendPing();
	lock();
	try
	{
		if(FidTcp->Connected() !=true || FHasSetAccInfo==false) return -1;
        QryYYB();
	}
	__finally
	{
	unlock();
	}

	return 0;
}
