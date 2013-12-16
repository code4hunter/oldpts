//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdItf_JSD.h"
#include <assert.h>

#pragma package(smart_init)

const char * REQUEST_NUM = "100";
const char * ENTRUST_WAY[8]={"ZZWT","RJWT","DHWT","KSWT","WSWT",};

//---------------------------------------------------------------------------

TTrdItf_JSD::TTrdItf_JSD(TJSDSet *set)
{
    CopyMemory(&FJSDSet,set,sizeof(TJSDSet));
    FidTcp = new TIdTCPClient(NULL);
    FidIPWatch = new TIdIPWatch(NULL);
}

TTrdItf_JSD::~TTrdItf_JSD()
{
    FidTcp->Disconnect();
    delete FidTcp;
    delete FidIPWatch;
}

AnsiString TTrdItf_JSD::GetErrorText(int code, char *error)
{
    AnsiString text;
    text.printf("A\r\nLocal\r\n%d\r\nN\r\n%s\r\n%d", REQUEST_NUM, error, code);
    return text; 
}

AnsiString TTrdItf_JSD::ReadNextData()
{
    AnsiString cmd;
    cmd.printf("R|%s|%s|0|%s|%s|", FidIPWatch->LocalIP().c_str(),
        REQUEST_NUM, FJSDSet.branch_no, ENTRUST_WAY[FJSDSet.entrust_way]);
    return ReadFirstData(cmd);
}

AnsiString TTrdItf_JSD::ReadFirstData(AnsiString cmd)
{
    //清除上次的返回信息
    int n = FidTcp->ReadFromStack(true, 1, true, NULL);
    if (n > 0) FidTcp->ReadString(n);

    //ODS(cmd.c_str());
    FidTcp->Write(cmd);

    n = FidTcp->ReadFromStack(true, FJSDSet.TimeOut, true, NULL);
    if (n <= 0) return "A|192.168.0.1|100|N|接收数据超时|-100"  ;

    AnsiString ret = FidTcp->ReadString(n);
    //ODS(ret.c_str());

    return ret;
}

int TTrdItf_JSD::SplitData(AnsiString SD, TStringList *lstDD, int count)
{
    char seps[] = "|";
    char *substr;
    char *data;
    assert(lstDD != NULL);

    lstDD->Clear();
    try
    {
        SD = SD.Trim();
        data = new char[SD.Length() + 1];
        memset(data, 0, SD.Length() + 1);
        strncpy(data, SD.c_str(), SD.Length());

        substr = strtok(data, seps);
        while (substr != NULL)
        {
            lstDD->Add(substr);
            substr = strtok(NULL, seps);
        }
    }
    __finally
    {
        delete []data;
    }

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
        if (lstDD->Count == 4)
            lstDD->Text = GetErrorText(-503, "未知错误！！！");
        else if (lstDD->Count == 5)
            lstDD->Text = GetErrorText(-503, lstDD->Strings[4].c_str());

        return DEF_ACK_ERROR;
    }

    //if (lstDD->Strings[3] == "Y" && lstDD->Count == count)
    //    return DEF_ACK_OK;
    if (lstDD->Count >= count)
        return DEF_ACK_OK;


    lstDD->Text = GetErrorText(-504, "未知错误！！！");
    return DEF_ACK_ERROR;
}

int TTrdItf_JSD::Init()  //初始化
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
    catch (...)
    {
        ODS("连接柜台失败!");
    }

    return FidTcp->Connected()==true ? 0 : -1;
}

//--------------------------------------------------------------------------
// CMD:功能号(2)|发起营业部代码|市场代码|暂时不用|帐号|密码|委托方式|
// 

//--------------------------------------------------------------------------
int TTrdItf_JSD::SetAccount() //设置帐号
{
    AnsiString cmd;


    TStringList *lstDD = new TStringList();

    try
    {

        cmd.printf("R|%s|%d|1|%s|0||%s|%s|%s|",
            FidIPWatch->LocalIP().c_str(),
            REQUEST_NUM,
            FJSDSet.branch_no,
            FRequest.SetAccount.Account,
            ENTRUST_WAY[FJSDSet.entrust_way], "");

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 6) == DEF_ACK_OK)
        {
            if (lstDD->Strings[INDEX(5)].Length() > 0)
                FJSDSet.money_type = lstDD->Strings[INDEX(5)][1];
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }

        // 1. 功能号(2)  2.发起营业部代码  3.市场代码  4.暂时不用  5.帐号 6.密码 7.委托方式
        if(FRequest.SetAccount.Sort == asCA)
        {
            cmd.printf("R|%s|%s|2|%s|0||%s|%s|%s|", FidIPWatch->LocalIP().c_str(),
                REQUEST_NUM, FJSDSet.branch_no, FRequest.SetAccount.Account,
                FRequest.SetAccount.PW, ENTRUST_WAY[FJSDSet.entrust_way]);
        }
        else if(FRequest.SetAccount.Sort==asSH)
        {
            cmd.printf("R|%s|%s|2|%s|1||%s|%s|%s|", FidIPWatch->LocalIP().c_str(),
                REQUEST_NUM, FJSDSet.branch_no, FRequest.SetAccount.Account,
                FRequest.SetAccount.PW, ENTRUST_WAY[FJSDSet.entrust_way]);
        }
        else if(FRequest.SetAccount.Sort==asSZ)
        {
            cmd.printf("R|%s|%s|2|%s|2||%s|%s|%s|", FidIPWatch->LocalIP().c_str(),
                REQUEST_NUM, FJSDSet.branch_no, FRequest.SetAccount.Account,
                FRequest.SetAccount.PW, ENTRUST_WAY[FJSDSet.entrust_way]);
        }
        else
            return -1;

        //  首包：1.成功标志  2.姓名     3.客户号   4.市场个数
        //后继包：1.市场代码  2.市场名称 3.股东代码 4.币种代码  5.币种名称

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 4) == DEF_ACK_OK)
        {
            strncpy(FAccInfo.Capital, lstDD->Strings[5].c_str(), 13);
            int count = lstDD->Strings[6].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 5) == DEF_ACK_OK)
                {
                    if (lstDD->Strings[3] == "1")
                        strncpy(FAccInfo.SH, lstDD->Strings[5].c_str(), 13);
                    else if (lstDD->Strings[3] == "2")
                        strncpy(FAccInfo.SZ, lstDD->Strings[5].c_str(), 13);

                    break;
                }
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

            if(FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) { return -1; }

			      NewAns(1);
			      memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }

        
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

//////查询函数//////
// 即时行情查询（v5.83）－60
int TTrdItf_JSD::GetTrdInfo()   //取得盘口数据
{
	char et;

	switch (FRequest.GetTrdInfo.SecuID[0])
    {
        case 'H' : et = '1'; break;
        case 'S' : et = '2'; break;
        case 'P' : et = '1'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //      -----1----|------2-------|----3---|----4---|----5---|----6---|---7----|
    // CMD  功能号(60)|发起营业部代码|市场代码|暂时不用|客户号  |证券代码|委托方式|
    //
    //               1| 2| 3|| 5| 6| 7|
    cmd.cat_printf("60|%s|%c||%s|%s|%s|",
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        FRequest.GetTrdInfo.SecuID + 1,            // 6
        ENTRUST_WAY[FJSDSet.entrust_way]           // 7
    );

    TStringList *lstDD = new TStringList();
    try
    {
        //  1.成功标志    2.指数  3.证券代码  4.证券名称    5.最新价  6.涨跌  7.涨跌值
        //  8.幅度        9.最新价成交量     10.总成交金额 11.今开盘 12.昨收盘价
        // 13.当日最高价 14.当日最低价       15.买价1      16.买量1  17.买价2
        // 18.买量2      19.买价3            20.买量3      21.卖价1  22.卖量1
        // 23.卖价2      24.卖量2            25.卖价3      26.卖量3  27.停牌标志
        // 28.涨跌值     29.买价4            30.买量4      31.卖价4  32.卖量4
        // 33.每百元应计利息额               34.国债全价   35.证券类别（大类＋类别）

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 35) == DEF_ACK_OK)
        {
			NewAns(1);
			TGetTrdInfo_Ans *gi = &(*FAnswer)[0].GetTrdInfo;
			gi->BuyInfo.ZXJ    = StrToFloatDef(lstDD->Strings[INDEX(5)], -1);
			gi->BuyInfo.Price1 = StrToFloatDef(lstDD->Strings[INDEX(15)], -1);
			gi->BuyInfo.Price2 = StrToFloatDef(lstDD->Strings[INDEX(17)], -1);
			gi->BuyInfo.Price3 = StrToFloatDef(lstDD->Strings[INDEX(19)], -1);
			gi->BuyInfo.Volum1 = StrToIntDef(lstDD->Strings[INDEX(16)], -1);
			gi->BuyInfo.Volum2 = StrToIntDef(lstDD->Strings[INDEX(18)], -1);
			gi->BuyInfo.Volum3 = StrToIntDef(lstDD->Strings[INDEX(20)], -1);
			gi->BuyInfo.CJSL   = StrToIntDef(lstDD->Strings[INDEX(9)], -1);

			gi->SellInfo.ZXJ    = StrToFloatDef(lstDD->Strings[INDEX(5)], -1);
			gi->SellInfo.Price1 = StrToFloatDef(lstDD->Strings[INDEX(21)], -1);
			gi->SellInfo.Price2 = StrToFloatDef(lstDD->Strings[INDEX(23)], -1);
			gi->SellInfo.Price3 = StrToFloatDef(lstDD->Strings[INDEX(25)], -1);
			gi->SellInfo.Volum1 = StrToIntDef(lstDD->Strings[INDEX(22)], -1);
			gi->SellInfo.Volum2 = StrToIntDef(lstDD->Strings[INDEX(24)], -1);
			gi->SellInfo.Volum3 = StrToIntDef(lstDD->Strings[INDEX(26)], -1);
			gi->SellInfo.CJSL   = StrToIntDef(lstDD->Strings[INDEX(9)], -1);
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

//查询资金余额和可用资金余额－9
int TTrdItf_JSD::QryMoney()     //资金查询
{

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //      ----1----|------2-------|----3---|----4---|----5---|
    // CMD  功能号(9)|发起营业部代码|货币代码|暂时不用|客户号  |
    //
    //              1| 2| 3|| 5|
    cmd.cat_printf("9|%s|%c||%s|",
        FJSDSet.branch_no,                         // 2
        FJSDSet.money_type,                        // 3
        FAccInfo.Capital);                         // 5

    TStringList *lstDD = new TStringList();
    try
    {
        // 1.成功标志  2.资金余额  3.可用资金  4.买入未交收金额  5.卖出未交收金额
        // 6.委托未成交冻结金额    7.货币名称  8.异常冻结资金

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 8) == DEF_ACK_OK)
        {
			NewAns(1);
			(*FAnswer)[0].QryMoney.Balance = StrToFloatDef(lstDD->Strings[4] ,-1);
			(*FAnswer)[0].QryMoney.Available = StrToFloatDef(lstDD->Strings[5],-1);
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

int TTrdItf_JSD::QryStock()     //股份查询
{
	char et;
	switch (FRequest.QryStock.SecuID[0])
    {
        case 'H' : et = '1'; break;
        case 'S' : et = '2'; break;
        case 'P' : et = '1'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    //CMD 1.功能号(56) 2.发起营业部代码 3.市场代码 4.暂时不用 5.客户号 6.查询市场代码（空格表示所有市场）|
    //    7.查询证券代码（为空格时表示查询所有股票，否则只查询某一只股票情况）|
    //    8.股东代码（空格表示所有股东代码）9.索引市场代码 10.索引证券代码 11.索引股东帐号
    //    12.最多返回数量 13.操作功能（1明细、2汇总）14.委托方式
    //    15.货币代码（v5.20.2实现：当查询市场代码为空而货币代码不为空时，则查询该货币的市场{沪A和深A}）|
    //    16.是否返回合计值（1：返回合计值，其他不返回）17.点评起始日期（为空，则不输出点评信息）|
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|12| |14|15|16||
    cmd.cat_printf("56|%s|%c||%s|%c|%s|%s|%s|%s|%s|%d|1|%s|%c|-1||",
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        et,                                        // 6
        FRequest.QryStock.SecuID + 1,              // 7
        et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 8
        "",                                        // 9
        "",                                        // 10
        "",                                        // 11
        1,                                         // 12
        ENTRUST_WAY[FJSDSet.entrust_way],          // 14
        FJSDSet.money_type);                       // 15

    TStringList *lstDD = new TStringList();
    try
    {
        //  1.市场代码  2.股东帐号   3.证券代码 4.证券名称  5.余额(加上当日成交)
        //  6.可用余额  7.当日买入成交数量      8.当日卖出未成交数量  9.当日买入成交金额
        // 10.成本价格 11.最新价    12.市值    13.浮动盈亏 14.当日卖出成交金额
        // 15.点评日期 16.一句话点评信息       17.国债净价 18.每百元应计利息(不是国债为0)
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            if (count <= 0) return DEF_OTHER_ERROR;

            if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 18) == DEF_ACK_OK)
            {
                NewAns(1);
                TQryStock_Ans *sa = &(*FAnswer)[0].QryStock;

                sa->Balance    = StrToFloatDef(lstDD->Strings[INDEX(5)], -1);
                sa->Available  = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);
                sa->BuyFreeze  = 0;
                sa->SellFreeze = 0;
            }
            else
            {
                ODS(lstDD->Strings[4].c_str());
                return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
            }
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }

    return 0;
}

int TTrdItf_JSD::QryCanBuy()    //取可买数量
{
    return -1;
}

int TTrdItf_JSD::QryDetail()    //成交查询
{
  int reqry_num=0;

HH:

  if(FRequest.QryDetail.ContractID[0]==0) return -1;
	char et;
	switch (FRequest.QryDetail.Bourse)
    {
        case bsSH : et = '1'; break;
        case bsSZ : et = '2'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //      -----1----|------2-------|----3---|----4---|--5---|---6----|
    //      功能号(14)|发起营业部代码|市场代码|暂时不用|客户号|起始日期|
    //      -----7----|---------------8--------------|------------------9---------------|
    //      终止日期  |合同号(为空格时查询所有数据)  |证券代码(为空格时查询所有股票数据)|
    //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
    //      最多返回数量|索引日期|索引合同号|委托方式|索引市场代码|排序方式(0-市场代码、1-委托时间、2-委托时间倒序)|
    //
    //               1| 2| 3|| 5| 6| 7| 8|9| |||13|| |
    cmd.cat_printf("14|%s|%c||%s|%s|%s|%s| |1|||%s||0|",
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        Now().FormatString("yyyymmdd").c_str(),    // 6
        Now().FormatString("yyyymmdd").c_str(),    // 7
        FRequest.QryDetail.ContractID,             // 8
        ENTRUST_WAY[FJSDSet.entrust_way]           // 13
    );

    TStringList *lstDD = new TStringList();
    try
    {
        // 1.股东帐号 2.买卖类别  3.证券代码  4.证券名称  5.委托数量  6.委托价格
        // 7.合同号   8.成交数量  9.成交价格 10.委托状态 11.成交状态 12.成交时间
        //13.日期    14.出错信息 15.成功标志 16.市场代码
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            //int count = lstDD->Strings[INDEX(2)].ToIntDef(0);
            //if (count <= 0) return -1;
            
            if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 16) == DEF_ACK_OK)
            {
			        NewAns(1);
			        (*FAnswer)[0].QryDetail.Num   = StrToIntDef(lstDD->Strings[INDEX(8)], -1);
			        (*FAnswer)[0].QryDetail.Price = StrToFloatDef(lstDD->Strings[INDEX(9)], -1);
                (*FAnswer)[0].QryDetail.UndoNum = 0;

                if (lstDD->Strings[INDEX(11)] == "场内撤单" ||
                    lstDD->Strings[INDEX(11)] == "场外撤单" ||
                    (lstDD->Strings[INDEX(11)] == "部分撤单" && (*FAnswer)[0].QryDetail.Num > 0))
                {
                  if(lstDD->Strings[INDEX(11)] == "部分撤单" && ++reqry_num < 3 ) //如果是部撤则再查直到 reqry_num >3
                  {
                    delete lstDD;
                    Idglobal::Sleep(100);
                    goto HH;
                  }

                  int csnnum = lstDD->Strings[INDEX(5)].ToIntDef(0);
                  (*FAnswer)[0].QryDetail.UndoNum = (*FAnswer)[0].QryDetail.Num - csnnum ;
                }

                //if((*FAnswer)[0].QryDetail.Price<0.001) (*FAnswer)[0].QryDetail.Num=0;
            }
            else
            {
                ODS(lstDD->Strings[4].c_str());
                return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
            }
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }
    return 0;
}

int TTrdItf_JSD::QryHisDetail() //历史成交查询
{
    // 暂时不用
    return -1;
}

int TTrdItf_JSD::QryCsn()       //查询某个委托合同
{
    // 暂时不用
    return -1;
}

int TTrdItf_JSD::QryCurCsn()    //当日委托查询
{
    AnsiString idxDate = "";
    AnsiString idxContractID = "";
    AnsiString idxMartCode = "";
    AnsiString date = Now().FormatString("yyyymmdd");
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //      -----1----|------2-------|----3---|----4---|--5---|---6----|
    //      功能号(14)|发起营业部代码|市场代码|暂时不用|客户号|起始日期|
    //      -----7----|---------------8--------------|------------------9---------------|
    //      终止日期  |合同号(为空格时查询所有数据)  |证券代码(为空格时查询所有股票数据)|
    //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
    //      最多返回数量|索引日期|索引合同号|委托方式|索引市场代码|排序方式(0-市场代码、1-委托时间、2-委托时间倒序)|
    //
    //               1| 2| 3|| 5| 6| 7|8|9|10|11|12|13|14| |
    cmd.cat_printf("14|%s|%c||%s|%s|%s| | |%d|%s|%s|%s|%s|0|",
        FJSDSet.branch_no,                          // 2
        ' ',                                        // 3
        FAccInfo.Capital,                           // 5
        date.c_str(),                               // 6
        date.c_str(),                               // 7
        1000,                                       // 10
        idxDate.c_str(),                            // 11
        idxContractID.c_str(),                      // 12
        ENTRUST_WAY[FJSDSet.entrust_way],           // 13
        idxMartCode.c_str()                         // 14
    );

    try
    {
        // 1.股东帐号 2.买卖类别  3.证券代码  4.证券名称  5.委托数量  6.委托价格
        // 7.合同号   8.成交数量  9.成交价格 10.委托状态 11.成交状态 12.成交时间
        //13.日期    14.出错信息 15.成功标志 16.市场代码
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                {
                    TConsignInfo *ci = new TConsignInfo;
                    memset(ci, 0, sizeof(TConsignInfo));

                    strncpy(ci->ContractID,lstDD->Strings[INDEX( 7)].c_str(), 8);
                    strncpy(ci->SecuID,    lstDD->Strings[INDEX( 3)].c_str(), 7);
                    strncpy(ci->SecuDesc,  lstDD->Strings[INDEX( 4)].c_str(), 8);
                    strncpy(ci->Time,      lstDD->Strings[INDEX(12)].c_str(), 8);
                    strncpy(ci->Date,      lstDD->Strings[INDEX(13)].c_str(), 8);

                    //ODS(lstDD->Strings[INDEX(16)].c_str());
                    ci->Bourse = lstDD->Strings[INDEX(16)][1] - 1;

                    ci->Type =ConvertType(lstDD->Strings[INDEX(2)].c_str());
                        
                    ci->State  = 'N';
                    ci->CsnVol = StrToIntDef(lstDD->Strings[INDEX(5)], -1);
                    ci->TrdVol = StrToIntDef(lstDD->Strings[INDEX(8)], -1);
                    ci->CancelVol = 0;
                    ci->CsnPrice  = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);;
                    ci->TrdPrice  = StrToFloatDef(lstDD->Strings[INDEX(9)], -1);;

                    idxDate         = lstDD->Strings[INDEX(13)];
                    idxContractID   = lstDD->Strings[INDEX(7)];
                    idxMartCode     = lstDD->Strings[INDEX(16)];

                     if (lstDD->Strings[INDEX(11)] == "场内撤单" ||
                        lstDD->Strings[INDEX(11)] == "场外撤单" ||
                        (lstDD->Strings[INDEX(11)] == "部分撤单" && ci->TrdVol > 0))
                    {
                        int csnnum = lstDD->Strings[INDEX(5)].ToIntDef(0);
                        ci->CancelVol = ci->TrdVol - csnnum ;
                    }

                    lstAns->Add(ci);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
                }
            }
            
            if (count > 0) goto _NEXT;

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
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}

int TTrdItf_JSD::QryHisCsn()    //历史委托查询
{
    AnsiString idxDate = "";
    AnsiString idxContractID = "";
    AnsiString idxMartCode = "";
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //      -----1----|------2-------|----3---|----4---|--5---|---6----|
    //      功能号(14)|发起营业部代码|市场代码|暂时不用|客户号|起始日期|
    //      -----7----|---------------8--------------|------------------9---------------|
    //      终止日期  |合同号(为空格时查询所有数据)  |证券代码(为空格时查询所有股票数据)|
    //      -----10-----|---11---|----12----|---13---|-----14-----|-----------------------15-----------------------|
    //      最多返回数量|索引日期|索引合同号|委托方式|索引市场代码|排序方式(0-市场代码、1-委托时间、2-委托时间倒序)|
    //
    //               1| 2| 3|| 5| 6| 7|8|9|10|11|12|13|14| |
    cmd.cat_printf("14|%s|%c||%s|%s|%s| | |%d|%s|%s|%s|%s|0|",
        FJSDSet.branch_no,                          // 2
        ' ',                                        // 3
        FAccInfo.Capital,                           // 5
        FRequest.QryHisCsn.StartDay,                // 6
        FRequest.QryHisCsn.EndDay,                  // 7
        1000,                                       // 10
        idxDate.c_str(),                            // 11
        idxContractID.c_str(),                      // 12
        ENTRUST_WAY[FJSDSet.entrust_way],           // 13
        idxMartCode.c_str()                         // 14
    );

    try
    {
        // 1.股东帐号 2.买卖类别  3.证券代码  4.证券名称  5.委托数量  6.委托价格
        // 7.合同号   8.成交数量  9.成交价格 10.委托状态 11.成交状态 12.成交时间
        //13.日期    14.出错信息 15.成功标志 16.市场代码
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                {
                    TConsignInfo *ci = new TConsignInfo;
                    memset(ci, 0, sizeof(TConsignInfo));

                    strncpy(ci->ContractID,lstDD->Strings[INDEX( 7)].c_str(), 8);
                    strncpy(ci->SecuID,    lstDD->Strings[INDEX( 3)].c_str(), 7);
                    strncpy(ci->SecuDesc,  lstDD->Strings[INDEX( 4)].c_str(), 8);
                    strncpy(ci->Time,      lstDD->Strings[INDEX(12)].c_str(), 8);
                    strncpy(ci->Date,      lstDD->Strings[INDEX(13)].c_str(), 8);

                    ci->Bourse = lstDD->Strings[INDEX(16)][1] - 1;


                    ci->Type =ConvertType(lstDD->Strings[INDEX(2)].c_str());
                        
                    ci->State  = 'N';
                    ci->CsnVol = StrToIntDef(lstDD->Strings[INDEX(5)], -1);
                    ci->TrdVol = StrToIntDef(lstDD->Strings[INDEX(8)], -1);
                    ci->CancelVol = 0;
                    ci->CsnPrice  = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);
                    ci->TrdPrice  = StrToFloatDef(lstDD->Strings[INDEX(9)], -1);
                    
                    idxDate         = lstDD->Strings[INDEX(13)];
                    idxContractID   = lstDD->Strings[INDEX(7)];
                    idxMartCode     = lstDD->Strings[INDEX(16)];

                    lstAns->Add(ci);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
                }
            }
            
            if (count > 0) goto _NEXT;

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
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}

int TTrdItf_JSD::QryCurTrd()    //当日成交查询
{
    AnsiString idxStock  = "";
    AnsiString idxTrdNo  = "";
    AnsiString idxAccout = "";
    AnsiString idxMartCode = "";
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();
    
_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    //
    //  1.功能号(13)   2.发起营业部代码  3.市场代码     4.暂时不用      5.客户号
    //  6.最多返回数量 7.索引证券代码    8.索引股东帐号 9.索引成交编号 10.委托方式
    // 11.索引市场代码（v5.83，当市场代码=0查询所有时必须添入）
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|
    cmd.cat_printf("13|%s|%c||%s|%d|%s|%s|%s|%d|%s|",
        FJSDSet.branch_no,                          // 2
        ' ',                                        // 3
        FAccInfo.Capital,                           // 5
        1000,                                       // 6
        idxStock.c_str(),                           // 7
        idxAccout.c_str(),                          // 8
        idxTrdNo.c_str(),                           // 9
        ENTRUST_WAY[FJSDSet.entrust_way],           // 10
        idxMartCode.c_str()                         // 11
    );

    try
    {
        //
        // 1.股东帐号 2.买卖类别  3.证券代码  4.证券名称  5.成交数量  6.成交价格
        // 7.成交时间 8.成交编号  9.合同号码 10.市场代码（9-10为v5.83实现）
        //
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 10) == DEF_ACK_OK)
                {
                    TTradeInfo *ti = new TTradeInfo;
                    memset(ti, 0, sizeof(TTradeInfo));

                    strncpy(ti->SecuID,   lstDD->Strings[INDEX(3)].c_str(), 7);
                    strncpy(ti->SecuDesc, lstDD->Strings[INDEX(4)].c_str(), 8);
                    strncpy(ti->Time,     lstDD->Strings[INDEX(7)].c_str(), 8);
                    strncpy(ti->Date,     Now().FormatString("yyyymmdd").c_str(), 8);
                    ti->Type  = ConvertType(lstDD->Strings[INDEX(2)].c_str());
                    ti->Vol   = StrToIntDef(lstDD->Strings[INDEX(5)], -1);
                    ti->Price = StrToFloatDef(lstDD->Strings[INDEX(6)], -1);
                    
                    lstAns->Add(ti);
                    
                    idxStock    = lstDD->Strings[INDEX(3)];
                    idxTrdNo    = lstDD->Strings[INDEX(8)];
                    idxAccout   = lstDD->Strings[INDEX(1)];
                    idxMartCode = lstDD->Strings[INDEX(10)];
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
                }
            }
            
            if (count > 0) goto _NEXT;

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
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}

int TTrdItf_JSD::QryHisTrd()    //历史成交查询
{
    AnsiString idxNo = "";
    AnsiString cmd;
    
    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";


    //  1.功能号(62)  2.发起营业部代码  3.货币代码   4.暂时不用      5.客户号
    //  6.起始日期    7.终止日期        8.索引流水号 9.最多返回数量 10.委托方式
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|
    cmd.cat_printf("62|%s|%c||%s|%s|%s|%s|%d|%s|",
        FJSDSet.branch_no,                          // 2
        FJSDSet.money_type,                         // 3
        FAccInfo.Capital,                           // 5
        FRequest.QryHisTrd.StartDay,                // 6
        FRequest.QryHisTrd.EndDay,                  // 7
        idxNo.c_str(),                              // 8
        1000,                                       // 9
        ENTRUST_WAY[FJSDSet.entrust_way]            // 10
    );

    try
    {

        // 1.成交日期  2.股东代码  3.买卖标志  4.证券代码  5.证券名称  6.成交数量
        // 7.成交价格  8.成交金额  9.变动金额 10.资金余额 11.股票余额 12.佣金
        //13.印花税   14.过户费   15.其他费用 16.成交时间 17.合同编号 18.成交编号
        //19."1"买"2"卖           20.流水号(=8位日期+6位序号)         21.成交数量abs

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[INDEX(2)].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 21) == DEF_ACK_OK)
                {
                    TTradeInfo *ti = new TTradeInfo;
                    memset(ti, 0, sizeof(TTradeInfo));

                    strncpy(ti->SecuID,   lstDD->Strings[INDEX( 4)].c_str(), 7);
                    strncpy(ti->SecuDesc, lstDD->Strings[INDEX( 5)].c_str(), 8);
                    strncpy(ti->Time,     lstDD->Strings[INDEX(16)].c_str(), 8);
                    strncpy(ti->Date,     lstDD->Strings[INDEX( 1)].c_str(), 8);
                    ti->Type  = ConvertType(lstDD->Strings[INDEX(19)].c_str());
                    ti->Vol   = StrToIntDef(lstDD->Strings[INDEX(6)], -1);
                    ti->Price = StrToFloatDef(lstDD->Strings[INDEX(7)], -1);

                    idxNo = lstDD->Strings[INDEX(20)];
                    lstAns->Add(ti);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
                }
            }


            if (count > 0) goto _NEXT;

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
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}

int TTrdItf_JSD::QryBill()      //查询资金流水（对帐单）
{
    AnsiString idxNo = "";
    AnsiString cmd;

    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    //
    //  1.功能号(11)  2.发起营业部代码  3.市场代码  4.暂时不用     5.客户号
    //  6.币种代码    7.起始日期        8.终止日期  9.索引流水号  10.最多返回数量
    // 11.委托方式
    //
    //               1| 2| 3|| 5| 6| 7| 8| 9|10|11|
    cmd.cat_printf("11|%s|%c||%s|%c|%s|%s|%s|%d|%s|",
        FJSDSet.branch_no,                          // 2
        ' ',                                        // 3
        FAccInfo.Capital,                           // 5
        FJSDSet.money_type,                         // 6
        FRequest.QryBill.StartDay,                  // 7
        FRequest.QryBill.EndDay,                    // 8
        idxNo.c_str(),                              // 9
        1000,                                       // 10
        ENTRUST_WAY[FJSDSet.entrust_way]            // 11
    );

    try
    {
        // 1.摘要   2.变动金额  3.本次余额  4.股东帐号  5.证券代码  6.买卖类别
        // 7.成交数 8.成交价    9.成交编号 10.流水号   11.摘要类别 12.合同号码（v5.81.2）

        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[INDEX(2)].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 12) == DEF_ACK_OK)
                {
                    TFundInfo *fi = new TFundInfo;
                    memset(fi, 0, sizeof(TFundInfo));

                    strncpy(fi->SecuID,   lstDD->Strings[INDEX( 5)].c_str(), 7);
                    //strncpy(fi->SecuDesc, lstDD->Strings[INDEX( 5)].c_str(), 8);

                    strncpy(fi->Type, lstDD->Strings[INDEX(6)].c_str(), 12);
                    fi->Vol   = StrToIntDef(lstDD->Strings[INDEX(7)], -1);
                    fi->Price = StrToFloatDef(lstDD->Strings[INDEX(8)], -1);
                    fi->TrdMny  = StrToFloatDef(lstDD->Strings[INDEX(2)], -1);
                    fi->Balance = StrToFloatDef(lstDD->Strings[INDEX(3)], -1);

                    idxNo = lstDD->Strings[INDEX(10)];
                    lstAns->Add(fi);
                }
                else
                {
                    ODS(lstDD->Strings[4].c_str());
                    return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
                }
            }
            
            if (count > 0) goto _NEXT;

            if (lstAns->Count > 0)
            {
                NewAns(lstAns->Count);
                for (int i = 0; i < lstAns->Count; i++)
                {
                    TFundInfo *fi = (TFundInfo *)lstAns->Items[i];
                    memcpy(&(*FAnswer)[i].QryBill.FundInfo, fi, sizeof(TFundInfo));
                }
            }

            for (int i = 0; i < lstAns->Count; i++)
            {
                TFundInfo *fi = (TFundInfo *)lstAns->Items[i];
                delete fi;
            }
            lstAns->Clear();
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
        delete lstAns;
    }

    return 0;
}

int TTrdItf_JSD::QryStocks()    //查询帐号中所有的股份
{
    AnsiString idxStock = "";
    AnsiString idxAcc   = "";
    AnsiString idxMart  = "";
    AnsiString cmd;
    TList * lstAns = new TList();
    TStringList *lstDD = new TStringList();
    //int count;

	char et;
	switch (FRequest.QryStocks.Bourse)
    {
        case bsSH : et = '1'; break;
        case bsSZ : et = '2'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

_NEXT:
    cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
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
    //               1| 2| 3|| 5| 6|7| 8| 9|10|11|12| |14||16||
    cmd.cat_printf("10|%s|%c||%s|%c| |%s|%s|%s|%s|%d|1|%s||-1||",
        FJSDSet.branch_no,                         // 2
        et,                                        // 3
        FAccInfo.Capital,                          // 5
        et,                                        // 6
        et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 8
        idxMart.c_str(),                           // 9
        idxStock.c_str(),                          // 10
        idxAcc.c_str(),                            // 11
        1000,                                      // 12
        ENTRUST_WAY[FJSDSet.entrust_way]);         // 14

    try
    {
        //  1.市场代码  2.股东帐号   3.证券代码        4.证券名称  5.余额(加上当日成交)
        //  6.可用余额  7.市值(当日) 8.浮动盈亏(当日)  9.成本价格 10.行情最新价
        // 11.昨日库存数量          12.股票市值(昨日) 13.浮动盈亏(昨日库存)
        // 14.点评日期              15.一句话点评信息 16.国债净价 17.每百元应计利息(不是国债为0)
        if (SplitData(ReadFirstData(cmd), lstDD, 5) == DEF_ACK_OK)
        {
            int count = lstDD->Strings[4].ToIntDef(0);
            for (int i = 0; i < count; i++)
            {
                if (SplitData(ReadNextData(), lstDD, DEF_HEAD_LEN + 17) == DEF_ACK_OK)
                {
                    TStockInfo *si = new TStockInfo;
                    memset(si, 0, sizeof(TStockInfo));

                    if (et == '1')
                        si->SecuID[0] = 'H';
                    else
                        si->SecuID[0] = 'S';

                    strncpy(si->SecuID + 1, lstDD->Strings[INDEX(3)].c_str(), 7);
                    strncpy(si->SecuDesc,   lstDD->Strings[INDEX(2)].c_str(), 11);

                    si->Balance       = lstDD->Strings[INDEX(5)].ToIntDef(0);
                    si->Available     = lstDD->Strings[INDEX(6)].ToIntDef(0);
                    si->ProfitAndLoss = StrToFloatDef(lstDD->Strings[INDEX(8)], -1);
                    si->CostPrice     = StrToFloatDef(lstDD->Strings[INDEX(9)], -1);
                    si->Cost          = si->Balance * si->CostPrice;
                    si->CurPrice      = StrToFloatDef(lstDD->Strings[INDEX(10)], -1);
                    si->CurVal        = si->Balance * si->CurPrice;
                    lstAns->Add(si);
                    
                    idxMart  = lstDD->Strings[INDEX(1)];
                    idxAcc   = lstDD->Strings[INDEX(2)];
                    idxStock = lstDD->Strings[INDEX(3)];
                }
            }

            if (count > 0) goto _NEXT;

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
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
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
// CMD: 功能号(3)|发起营业部代码|市场代码|暂时不用|股东帐号|证券代码|买卖类型(1买入、2卖出)
//      |委托数量|委托价格|委托方式|银行标志|银行代码|
//---------------------------------------------------------------------------
int TTrdItf_JSD::Buy()
{
	char et;

	switch (FRequest.Buy.SecuID[0])
    {
        case 'H' : et = '1'; break;
        case 'S' : et = '2'; break;
        case 'P' : et = '1'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    if (FRequest.Buy.Type == 1)
    {
        // 1.功能号(202)  2.营业部代码  3.市场代码  4.暂时不用  5.客户号
        // 6.股东代码     7.申购/赎回标志（1：申购，2：赎回）
        // 8.基金代码     9.申购份额    10.委托方式
        //                1| 2| 3|| 5| 6|7| 8| 9|10| 
        cmd.cat_printf("202|%s|%c||%s|%s|1|%s|%d|%s|",
            FJSDSet.branch_no,                          // 2
            et,                                         // 3
            FAccInfo.Capital,                           // 5
            et == '1' ? FAccInfo.SH : FAccInfo.SZ,      // 6
            FRequest.Buy.SecuID + 1,                    // 8
            FRequest.Buy.Num,                           // 9
            ENTRUST_WAY[FJSDSet.entrust_way]);          // 10
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
        cmd.cat_printf("3|%s|%c||%s|%s|1|%d|%.3f|%s|||",
            FJSDSet.branch_no,                         // 2
            et,                                        // 3
            et == '1' ? FAccInfo.SH : FAccInfo.SZ,     // 5
            FRequest.Buy.SecuID + 1,                   // 6
            FRequest.Buy.Num,                          // 8
            FRequest.Buy.Price,                        // 9
            ENTRUST_WAY[FJSDSet.entrust_way]);         // 10
    }

    TStringList *lstDD = new TStringList();
    try
    {
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
			NewAns(1);
            strncpy((*FAnswer)[0].Buy.ContractID, lstDD->Strings[INDEX(2)].c_str(), 19);
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }
    
    return 0;
}

int TTrdItf_JSD::Sell()
{
	char et;

	switch (FRequest.Sell.SecuID[0])
    {
        case 'H' : et = '1'; break;
        case 'S' : et = '2'; break;
        case 'P' : et = '1'; break;
        default: return DEF_INVALID_STOCKCODE;
    }

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";

    if (FRequest.Buy.Type == 1)
    {
        // 1.功能号(202)  2.营业部代码  3.市场代码  4.暂时不用  5.客户号
        // 6.股东代码     7.申购/赎回标志（1：申购，2：赎回）
        // 8.基金代码     9.申购份额    10.委托方式
        //                1| 2| 3|| 5| 6|7| 8| 9|10| 
        cmd.cat_printf("202|%s|%c||%s|%s|2|%s|%d|%s|",
            FJSDSet.branch_no,                          // 2
            et,                                         // 3
            FAccInfo.Capital,                           // 5
            et == '1' ? FAccInfo.SH : FAccInfo.SZ,      // 6
            FRequest.Buy.SecuID + 1,                    // 8
            FRequest.Buy.Num,                           // 9
            ENTRUST_WAY[FJSDSet.entrust_way]);          // 10
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
        cmd.cat_printf("3|%s|%c||%s|%s|2|%d|%.3f|%s|||",
            FJSDSet.branch_no,                        // 2
            et,                                       // 3
            et == '1' ? FAccInfo.SH : FAccInfo.SZ,    // 5
            FRequest.Sell.SecuID + 1,                 // 6
            FRequest.Sell.Num,                        // 8
            FRequest.Sell.Price,                      // 9
            ENTRUST_WAY[FJSDSet.entrust_way]);        // 10
    }

    TStringList *lstDD = new TStringList();
    try
    {
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 2) == DEF_ACK_OK)
        {
			NewAns(1);
            strncpy((*FAnswer)[0].Buy.ContractID, lstDD->Strings[INDEX(2)].c_str(), 19);
        }
        else
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }
    
    return 0;
}



int TTrdItf_JSD::Undo() //委托撤单
{

    AnsiString cmd = "R|" + FidIPWatch->LocalIP() + "|" + REQUEST_NUM + "|";
    //
    //     ----1----|-------2------|----3---|----4---|---5--|---6--|----7---|
    //CMD: 功能号(4)|发起营业部代码|市场代码|暂时不用|客户号|合同号|委托方式|
    //
    //              1| 2| 3|| 5| 6| 7|
    cmd.cat_printf("4|%s|%c||%s|%s|%s|",
        FJSDSet.branch_no,                          // 2
        FRequest.Undo.Bourse == bsSH ? '1' : '2',   // 3
        FAccInfo.Capital,                           // 5
        FRequest.Undo.ContractID,                   // 6
        ENTRUST_WAY[FJSDSet.entrust_way]);          // 7

    TStringList *lstDD = new TStringList();
    try
    {
        if (SplitData(ReadFirstData(cmd), lstDD, DEF_HEAD_LEN + 1) != DEF_ACK_OK)
        {
            ODS(lstDD->Strings[4].c_str());
            return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
        }
    }
    __finally
    {
        delete lstDD;
    }
    
    return 0;
}


