//---------------------------------------------------------------------------


#pragma hdrstop

#include "uDatabase.h"
#include "uPriceFunc.h"
#include "uTrdItfImp.h"
#include "uField.h"
#include <assert.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <stdio.h>

const char * REQ_HEAD = "GXFIXSTD";

#pragma package(smart_init)


int DateTimeToInt(const UnicodeString &dt)
{
	String a = ReplaceStr( dt,"-","");
	String b = ReplaceStr( a,":","");
	return b.ToIntDef(0);
}

std::string  TTrdItfImp::ReadFirstData(const std::string & cmd)
{
    AnsiString req;
    req.sprintf("%s%08d%s",REQ_HEAD,cmd.length(),cmd.c_str());

    TIdTCPClient *FidTcp = new TIdTCPClient(NULL);
    FidTcp->Host = FSetup.SvrIp;
    FidTcp->Port = FSetup.SvrPort;

	try
	{
        FidTcp->Connect();
		//if( FidTcp->Connected() !=true )
        //{
		//	SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"券商柜台连接断开! ");
		//    throw ERR_REMOTE_OTHER_FAILED;
        //}
	}
	catch (Exception *e)
	{
		SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"券商柜台连接意外断开! 错误信息:%s.",
			AnsiString(e->Message).c_str());
		throw ERR_REMOTE_OTHER_FAILED;
	}

    try
    {
        //清除上次的返回信息
        TByteDynArray da;
        try
        {
        /*
            if( FidTcp->Socket->Readable(10) == true )
            {
                FidTcp->Socket->ReadBytes(da,-1,true);
            }
            if( FSetup.debug_mode )
                ODS("REQ:%s",req.c_str());
        */
            FidTcp->Socket->Write(req.c_str());
        }
        catch( Exception &e )
        {
            SetLastError(ERR_REMOTE_SEND_FAILED,'E',PLUGINNAME,"券商柜台发送数据失败! 错误信息:%s.",
                AnsiString(e.Message).c_str());
            throw ERR_REMOTE_SEND_FAILED ;
        }

        da.set_length(0);

        try
        {
            char buf[255];
            //读头长度
            FidTcp->Socket->ReadBytes(da,16,false);
            strncpy(buf,(char*)&da[0],8);
            buf[8]=0;

            if( strcmpi(buf, REQ_HEAD) != 0 )
            {
                SetLastError(ERR_REMOTE_SEND_FAILED,'E',PLUGINNAME,"券商柜台接收到未知头数据! 错误信息:HEAD=%s.",
                    buf);
                throw ERR_REMOTE_RECV_FAILED ;
            }

            strncpy(buf,(char*)&da[0]+8,8);
            buf[8] =0;
            int next = atoi(buf);

            if( next <=2 )
            {
                SetLastError(ERR_REMOTE_RECV_FAILED,'E',PLUGINNAME,"券商柜台接收到的包长度太短! buf:%s.",buf);
                throw ERR_REMOTE_RECV_FAILED ;
            }

            //读数据
            FidTcp->Socket->ReadBytes(da,next,false);

        }
        catch(Exception &e)
        {
            SetLastError(ERR_REMOTE_RECV_FAILED,'E',PLUGINNAME,"券商柜台接收数据失败! 错误信息:%s.",
                AnsiString(e.Message).c_str());
            throw ERR_REMOTE_RECV_FAILED ;
        }

        if (da.Length == 0)
        {
            SetLastError(ERR_REMOTE_RECV_FAILED,'E',PLUGINNAME,"券商柜台接收数据量为0!");
            throw ERR_REMOTE_RECV_FAILED ;
        }
        std::string ret = (char*)&da[0];
        if( FSetup.debug_mode )
            ODS("ANS:%s",ret.c_str());
        return ret;
    }
    __finally
    {
        try
        {
            FidTcp->Disconnect();
        }
        catch(...)
        {

        }
        delete  FidTcp;
    }
}


TTrdItfImp::TTrdItfImp(const char *psetupfile,ADDLOG plogfunc) :
	TTrdItfBase( psetupfile,  plogfunc)
{

}

TTrdItfImp::~TTrdItfImp()
{
	CloseLink();
	//delete FidTcp;
}

//初始化
int TTrdItfImp::Init()
{
/*
    TIdTCPClient *FidTcp = new TIdTCPClient(NULL);
	try
	{
        FidTcp->Host = FSetup.SvrIp;
        FidTcp->Port = FSetup.SvrPort;
        FidTcp->Connect();
        FidTcp->Disconnect();
	}
	catch (...)
	{
		ODS('E',PLUGINNAME,"连接柜台失败!");
		return -1;
	}


    delete  FidTcp;
*/
	return 0;
}

//设置帐号
/*
股东查询(440207)
功能代码	440207
功能描述	客户查询，查询客户股东代码
请求数据	域名称	标识	类型及长度	必要	描述
	客户代码	custid	Int64	Y
	机构编码	orgid	Char(4)	Y
	资金帐户	fundid	int64	N
	交易市场	market	char(1)	N	不送查询全部
	股东代码	secuid	char(10)	N	不送查询全部
	请求行数	count	int 	Y	每次取的行数
	定位串  	poststr	char(64)	Y	第一次填空
返回数据	域名称	标识	类型及长度	描述
	定位串  	poststr	char(64)	查询返回定位值
	客户代码	custid	int64
	交易市场	market	char(1)
	股东代码	secuid	char(10)
	股东姓名	name	char(16)
	股东序号	secuseq	Int	0主股东
	指定交易标志	regflag	char(1)
错误描述	错误代码	错误信息
备注信息		指定交易标志：
	‘0’ 未A股指定,未回购指定
	‘1’ 未A股指定,已回购指定
	‘2’ 已A股指定,未回购指定
	‘3’ 已A股指定,已回购指定
*/
int TTrdItfImp::SetAccount()
{
    try
	{
		record_set rs(15,1);

        rs.add_field_name("FUNCID");
        rs.add_field_name("g_serverid");
        rs.add_field_name("g_funcid");
        rs.add_field_name("g_operid");
        rs.add_field_name("g_operpwd");
        rs.add_field_name("g_operway");
        rs.add_field_name("g_stationaddr");
        rs.add_field_name("g_checksno");

        rs.add_field_name("custid");
        rs.add_field_name("orgid");
        rs.add_field_name("count");
        rs.add_field_name("posstr");
        rs.add_field_name("fundid");
        rs.add_field_name("market");
        rs.add_field_name("secuid");

        rs.set_field_value("FUNCID","440207");
        rs.set_field_value("g_funcid","440207");
        rs.set_field_value("custid",FSetup.custid.c_str());
        rs.set_field_value("orgid",FSetup.Orgid.c_str());
        rs.set_field_value("count","100");
        rs.set_field_value("posstr","");
        //rs.set_field_value("fundid",FRequest.SetAccount.Account);

        std::string txt = rs.get_text();
        std::string ansText = ReadFirstData(txt);

        size_t pos = rs.set_text(ansText);

        if( atoi(rs.get_field_value("RETCODE").c_str())!= 0 )
        {
            SetLastError(-2,'E',PLUGINNAME,"柜台返回错误! 错误信息:%s.",
                rs.get_field_value("RETMESSAGE",1).c_str());
            return -2;
        }

        if( atoi(rs.get_field_value("RESULTSIZE").c_str())<=1 )
        {
            SetLastError(-3,'E',PLUGINNAME,"柜台没有返回更多的结果集");
            return -3;
        }

        rs.set_text(ansText,pos);

        for(size_t i =1; i<=rs.get_row_size(); i++ )
        {
            switch( ConvertMarketType(rs.get_field_value("market",i).c_str()))
            {
                case mtSHA:
                    lstrcpyn(FAccInfo.SH, rs.get_field_value("secuid",i).c_str(), ACC_LEN);
                    break;
                case mtSZA:
                    lstrcpyn(FAccInfo.SZ, rs.get_field_value("secuid",i).c_str(), ACC_LEN);
                    break;
            }
        }

        if(FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) { return -1; }

        lstrcpyn(FAccInfo.Capital,FRequest.SetAccount.Account,ACC_LEN);

        NewAns(1);
		memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));
        order_man.load_working_orders(this->FAccInfo.Capital);

	}
	catch( const char * err)
	{
        SetLastError(-1,'E',PLUGINNAME,"编列解列错误! 错误信息:%s.",err);
        return -1;
	}
    catch( const int errcode )
    {
        return errcode;
    }

	return 0;
}

//资金查询
/*资金查询(440206)
功能代码	440206
功能描述	资金查询
请求数据	域名称	标识	类型及长度	必要	描述
	客户代码	custid	Int64	Y
	机构编码	Orgid	Char(4)	Y
	资金账号	fundid	Int64	Y
	货币	moneytype	char(1)	N	不送查询全部
	计算市值标志	MvFlag	char(1)	N	0计算股票市值
1不算股票市值
返回数据	域名称	标识	类型及长度	描述
	客户代码	custid	Int64
	资金账户	fundid	Int64
	机构编码	orgid	char(4)
	货币	moneytype	char(1)
	资金余额	fundbal	numeric(15,2)
	资金可用金额	fundavl	numeric(15,2)
	资产总值	marketvalue	numeric(15,2)
	资金资产	fund	numeric(15,2)
	市值	stkvalue	numeric(15,2)
	主资金标志	fundseq	Int
	买入冻结数	fundbuyfrz	numeric(15,2)
错误描述	错误代码	错误信息
备注信息


*/
int TTrdItfImp::QryMoney()
{
    try
    {
        record_set rs(13,1);
        rs.add_field_name("FUNCID");
        rs.add_field_name("g_serverid");
        rs.add_field_name("g_funcid");
        rs.add_field_name("g_operid");
        rs.add_field_name("g_operpwd");
        rs.add_field_name("g_operway");
        rs.add_field_name("g_stationaddr");
        rs.add_field_name("g_checksno");

        rs.add_field_name("custid");
        rs.add_field_name("orgid");
        rs.add_field_name("fundid");
        rs.add_field_name("moneytype");
        rs.add_field_name("mvflag");

        rs.set_field_value("FUNCID","440206");
        rs.set_field_value("g_funcid","440206");
        rs.set_field_value("custid",FSetup.custid.c_str());
        rs.set_field_value("orgid",FSetup.Orgid.c_str());
        rs.set_field_value("fundid",this->FAccInfo.Capital);
        rs.set_field_value("moneytype",ConvertMoneyType(FRequest.QryMoney.MoneyType));

        std::string txt = rs.get_text();
        std::string ansText = ReadFirstData(txt);
        size_t pos = rs.set_text(ansText);

        if( atoi(rs.get_field_value("RETCODE").c_str())!= 0 )
        {
            SetLastError(-2,'E',PLUGINNAME,"柜台返回错误! 错误信息:%s.",
                rs.get_field_value("RETMESSAGE",1).c_str());
            return -2;
        }

        if( atoi(rs.get_field_value("RESULTSIZE").c_str())<=1 )
        {
            SetLastError(-3,'E',PLUGINNAME,"柜台没有返回更多的结果集");
            return -3;
        }

        rs.set_text(ansText,pos);

        for(size_t i =1; i<=rs.get_row_size(); i++ )
        {
            NewAns(1);
            (*FAnswer)[0].QryMoney.MoneyInfo.MoneyType =  ConvertMoneyType(rs.get_field_value("moneytype",i).c_str());
            (*FAnswer)[0].QryMoney.MoneyInfo.balance = atof(rs.get_field_value("marketvalue",i).c_str());
            (*FAnswer)[0].QryMoney.MoneyInfo.available = atof(rs.get_field_value("fundavl",i).c_str());
            break;
        }
	}
	catch( const char * err)
	{
        SetLastError(-1,'E',PLUGINNAME,"编列解列错误! 错误信息:%s.",err);
        return -1;
	}
    catch( const int errcode )
    {
        return errcode;
    }

	return 0;
}

//当日委托查询
/*
当日委托明细查询(440209)
功能代码	440209
功能描述	当日委托查询
请求数据	域名称	标识	类型及长度	必要	描述
	客户代码	custid	Int64	Y
	客户机构	Orgid	Char(4)	Y
	交易市场	market	char(1)	N	不送查询全部
	资金帐户	fundid	int64	N
	股东代码	secuid	char(10)	N	不送查询全部
	证券代码	stkcode	char(8)	N	不送查询全部
	委托序号	ordersno	Int	N	不送查询全部
	外部银行	bankcode	char(4)	N	三方交易时送
	请求行数	count	int 	Y	每次取的行数
	定位串  	poststr	char(32)	Y	第一次填空
	信用产品标识	creditid	Char(1)	N	空查全部
0 融资融券
1 IPO融资
	信用委托类型	creditflag	Char(1)	N	见备注
空查全部
	可撤单标志	cancelflag	Char(1)	N	空查全部
0查全部
1查可撤单委托
返回数据	域名称	标识	类型及长度	描述
	定位串  	poststr	char(32)
	委托日期	orderdate	Int
	委托序号	ordersno	Int
	客户代码	custid	int64
	客户姓名	custname	char(16)
	资金账户	fundid	int64
	货币	moneytype	char(1)
	机构编码	orgid	char(4)
	股东代码	secuid	char(10)
	买卖类别	Bsflag2	char(2)
	合同序号	orderid	char(10)
	报盘时间	reporttime	Int
	委托时间	opertime	Int
	交易市场	market	char(1)
	证券代码	stkcode	char(8)
	证券名称	stkname	char(8)
	委托价格	orderprice	Numeric(9,3)
	委托数量	orderqty	Int
	冻结金额	orderfrzamt	Numeric(15,2)
	成交数量	matchqty	Int
	成交金额	matchamt	Numeric(15,2)
	撤单数量	cancelqty	Int
	委托状态	orderstatus	char(1)
	交易席位	seat	char(6)
	撤单标识	cancelflag	char(1)
        F   	正常
        T   	撤单
	证券类别	stktype	char(1)
	信用产品标识	creditid	Char(1)	0 融资融券
1 IPO融资
	信用委托类型	creditflag	Char(1)	见备注
错误描述	错误代码	错误信息
备注信息	送证券代码必须送交易市场
'0','未报' 在lbm中委托成功写入未发标志
'1','正报' 在落地方式中,报盘扫描未发委托,并将委托置为正报状态
'2','已报' 报盘成功后,报盘机回写发送标志为已报
'3','已报待撤' 已报委托撤单
'4','部成待撤' 部分成交后委托撤单
'5','部撤' 部分成交后撤单成交
'6','已撤' 全部撤单成交
'7','部成' 已报委托部分成交
'8','已成' 委托或撤单全部成交
'9','废单' 委托确认为费单
'A','待报'
'B','正报' 国泰模式中，已报道接口库尚未处理返回库的阶段，标准模式不用。
信用委托类型：
0  融资开仓
1  融资平仓
2  融资强平
3  买入担保品
4  卖出担保品
5  非交易过户
A  融券开仓
B  融券平仓
C  融券强平

*/

int TTrdItfImp::QryCurCsn()
{
    try
    {
        record_set rs;
        rs.resize(21,1);
        rs.add_field_name("FUNCID");
        rs.add_field_name("g_serverid");
        rs.add_field_name("g_funcid");
        rs.add_field_name("g_operid");
        rs.add_field_name("g_operpwd");
        rs.add_field_name("g_operway");
        rs.add_field_name("g_stationaddr");
        rs.add_field_name("g_checksno");

        rs.add_field_name("custid");
        rs.add_field_name("orgid");
        rs.add_field_name("count");
        rs.add_field_name("poststr");

        rs.add_field_name("market");
        rs.add_field_name("fundid");
        rs.add_field_name("secuid");
        rs.add_field_name("stkcode");
        rs.add_field_name("ordersno");
        rs.add_field_name("bankcode");
        rs.add_field_name("creditid");
        rs.add_field_name("creditflag");
        rs.add_field_name("cancelflag");

        if(FRequest.QryCurCsn.OrderID[0]==0)
        {
            rs.set_field_value("FUNCID","440209");
            rs.set_field_value("g_funcid","440209");
            rs.set_field_value("custid",FSetup.custid.c_str());
            rs.set_field_value("orgid",FSetup.Orgid.c_str());
            rs.set_field_value("count",AnsiString(IntToStr((int)FRequest.QryCurCsn.MaxRecord)).c_str());
            rs.set_field_value("poststr",FRequest.QryCurCsn.SeqNum);

            std::string txt = rs.get_text();
            std::string ansText = ReadFirstData(txt);

            size_t pos = rs.set_text(ansText);

            if( atoi(rs.get_field_value("RETCODE").c_str())!= 0 )
            {
                SetLastError(-2,'E',PLUGINNAME,"柜台返回错误! 错误信息:%s.",
                    rs.get_field_value("RETMESSAGE",1).c_str());
                return -2;
            }

            if( atoi(rs.get_field_value("RESULTSIZE").c_str())<=1 )
            {
                return 0;
            }

            rs.set_text(ansText,pos);
            assert(rs.get_row_size()>0);
        }
        else //查单个委托
        {
            rs.set_field_value("FUNCID","440209");
            rs.set_field_value("g_funcid","440209");
            rs.set_field_value("custid",FSetup.custid.c_str());
            rs.set_field_value("orgid",FSetup.Orgid.c_str());
            rs.set_field_value("count","1");
            rs.set_field_value("poststr","");
            rs.set_field_value("ordersno",FRequest.QryCurCsn.OrderID);

            std::string txt = rs.get_text();
            std::string ansText = ReadFirstData(txt);

            size_t pos = rs.set_text(ansText);

            if( atoi(rs.get_field_value("RETCODE").c_str())!= 0 )
            {
                SetLastError(-2,'E',PLUGINNAME,"柜台返回错误! 错误信息:%s.",
                    rs.get_field_value("RETMESSAGE",1).c_str());
                return -2;
            }

            if( atoi(rs.get_field_value("RESULTSIZE").c_str())<=1 )
            {
                SetLastError(-3,'E',PLUGINNAME,"柜台没有返回结果集.");
                return -3;
            }
            rs.set_text(ansText,pos);

            assert( rs.get_row_size() == 1);
        }

        NewAns(rs.get_row_size());
        for(size_t i =1; i<=rs.get_row_size(); i++ )
        {
            TOrderInfo &oi=(*FAnswer)[i-1].QryCurCsn.OrderInfo;;
            strncpy(oi.ContractID,rs.get_field_value("ordersno",i).c_str(),SEQ_LEN);
            strncpy(oi.SecuID,rs.get_field_value("stkcode",i).c_str(), CODE_LEN);
            oi.Market = ConvertMarketType(rs.get_field_value("market",i).c_str());

            oi.Time =DateTimeToInt(rs.get_field_value("opertime",i).c_str())/100;
            oi.Date =DateTimeToInt(rs.get_field_value("orderdate",i).c_str());
            oi.Type =ConvertOrderType(rs.get_field_value("bsflag2",i).c_str());

            oi.CsnVol=atoi(rs.get_field_value("orderqty",i).c_str());
            oi.TrdVol =atoi(rs.get_field_value("matchqty",i).c_str());
            oi.CancelVol=atoi(rs.get_field_value("cancelqty",i).c_str());
            oi.CsnPrice=StrToFloatDef(rs.get_field_value("orderprice",i).c_str(),0);
            if(oi.TrdVol>0)
                oi.TrdPrice= StrToFloatDef(rs.get_field_value("matchamt",i).c_str(),0)/oi.TrdVol;
            else
                oi.TrdPrice=0;

            strncpy(oi.Account,rs.get_field_value("fundid",i).c_str(),ACC_LEN);
            strncpy(oi.SeqNum,rs.get_field_value("poststr",i).c_str(),SEQ_LEN);

            if( (oi.CsnVol== (oi.TrdVol +abs(oi.CancelVol))) &&
                oi.CancelVol>0 &&
                oi.TrdVol>0 )
                oi.State= osbw;
            else if(oi.CsnVol== oi.TrdVol)
                oi.State=oscj;
            else if( oi.CsnVol== abs(oi.CancelVol))
                oi.State=osyc;
            else if( oi.TrdVol>0 )
                oi.State=osbc;
            else oi.State=osyb ;

            if( FRequest.QryCurCsn.MaxRecord<0 )
            {
                strncpy(oi.SeqNum,rs.get_field_value("seat",i).c_str(),SEQ_LEN);
            }

            if(rs.get_field_value("cancelflag",i)=="T")  //表示撤单
            {
                oi.Type = otNo;
            }
        }
    }
    catch( const char * err)
    {
        SetLastError(-1,'E',PLUGINNAME,"编列解列错误! 错误信息:%s.",err);
        return -1;
    }
    catch( const int errcode )
    {
        return errcode;
    }
	return 0;
}

//当日成交查询
/*
当日成交明细查询(440211)
功能代码	440211
功能描述	当日成交查询
请求数据	域名称	标识	类型及长度	必要	描述
	客户代码	custid	Int64	Y
	客户机构	orgid	Char(4)	Y
	资金帐户	fundid	int64	Y
	交易市场	market	char(1)	N	不送查询全部
	股东代码	secuid	char(10)	N	不送查询全部
	证券代码	stkcode	char(8)	N	不送查询全部
	委托序号	ordersno	int	N	不送查询全部
	请求行数	count	int 	Y	每次取的行数
	定位串  	poststr	char(64)	Y	第一次填空
	信用产品标识	creditid	Char(1)	N	空查全部
0 融资融券
1 IPO融资
	信用委托类型  	creditflag	Char(1)	N	见备注
空查全部
返回数据	域名称	标识	类型及长度	描述
	定位串  	poststr	char(64)	查询返回定位值
	成交日期	trddate	int
	股东代码	secuid	char(10)
	买卖类别	Bsflag2	char(2)
	委托序号	ordersno	int
	合同序号	orderid	char(10)
	交易市场	market	char(1)
	证券代码	stkcode	char(8)
	证券名称	stkname	char(8)
	成交时间	matchtime	int
	成交序号	matchcode	int
	成交价格	matchprice	numeric(9,3)
	成交数量	matchqty	int
	成交金额	matchamt	numeric(15,2)
	成交类型	matchtype	char(1)	数据字典Cjlx
	委托数量	orderqty	int
	委托价格	orderprice	numeric(9,3)
	证券类别	stktype	char(1)
	信用产品标识	creditid	Char(1)	0 融资融券
1 IPO融资
	信用委托类型	creditflag	Char(1)	见备注
错误描述	错误代码	错误信息
备注信息	成交类型：
	'0'普通成交
	'1'撤单成交
	'2'废单
	'3'内部撤单
	'4'撤单废单
信用委托类型：
0  融资开仓
1  融资平仓
2  融资强平
3  买入担保品
4  卖出担保品
5  非交易过户
A  融券开仓
B  融券平仓
C  融券强平

*/
int TTrdItfImp::QryCurTrd()
{
/*
    if(FRequest.QryCurTrd.OrderID[0]!=0)
    {
        try
        {
            record_set rs;
            rs.resize(19,1);
            rs.add_field_name("FUNCID");
            rs.add_field_name("g_serverid");
            rs.add_field_name("g_funcid");
            rs.add_field_name("g_operid");
            rs.add_field_name("g_operpwd");
            rs.add_field_name("g_operway");
            rs.add_field_name("g_stationaddr");
            rs.add_field_name("g_checksno");

            rs.add_field_name("custid");
            rs.add_field_name("orgid");
            rs.add_field_name("fundid");
            rs.add_field_name("count");
            rs.add_field_name("poststr");

            rs.add_field_name("market");
            rs.add_field_name("secuid");
            rs.add_field_name("stkcode");
            rs.add_field_name("ordersno");
            rs.add_field_name("creditid");
            rs.add_field_name("creditflag");

            //查单个委托

            rs.set_field_value("FUNCID","440211");
            rs.set_field_value("g_funcid","440211");
            rs.set_field_value("custid",FSetup.custid.c_str());
            rs.set_field_value("orgid",FSetup.Orgid.c_str());
            rs.set_field_value("fundid",this->FAccInfo.Capital);
            rs.set_field_value("count","100");
            rs.set_field_value("poststr","");
            rs.set_field_value("ordersno",FRequest.QryCurTrd.OrderID);

            std::string txt = rs.get_text();
            std::string ansText = ReadFirstData(txt);

            size_t pos = rs.set_text(ansText);

            if( atoi(rs.get_field_value("RETCODE").c_str())!= 0 )
            {
                SetLastError(-2,'E',PLUGINNAME,"柜台返回错误! 错误信息:%s.",
                    rs.get_field_value("RETMESSAGE",1).c_str());
                return -2;
            }

            if( atoi(rs.get_field_value("RESULTSIZE").c_str())<=1 )
            {
                return 0;
            }

            rs.set_text(ansText,pos);

            assert(rs.get_row_size()>0);
            NewAns(rs.get_row_size());
            for(size_t i =1; i<=rs.get_row_size(); i++ )
            {
                TTradeInfo &ti = (*FAnswer)[i-1].QryCurTrd.TrdInfo;
                strncpy(ti.Account,rs.get_field_value("secuid",i).c_str(),ACC_LEN);
                strncpy(ti.ContractID,rs.get_field_value("ordersno",i).c_str(),SEQ_LEN);
                ti.Date=DateTimeToInt(rs.get_field_value("trddate",i).c_str());
                ti.Market=ConvertMarketType(rs.get_field_value("market",i).c_str());
                strncpy(ti.SecuID,rs.get_field_value("stkcode",i).c_str(),SEQ_LEN);
                strncpy(ti.SeqNum,rs.get_field_value("poststr",i).c_str(),SEQ_LEN);
                ti.Time=DateTimeToInt(rs.get_field_value("matchtime",i).c_str())/100;
                strncpy(ti.TrdID,rs.get_field_value("matchcode",i).c_str(),SEQ_LEN);
                ti.Type=otNo;

                std::string trdtype = rs.get_field_value("matchtype",i);
                if( trdtype=="1" || trdtype=="2" || trdtype=="3" )
                {
                    ti.Price = 0;
                    ti.Vol = -abs(atoi(rs.get_field_value("matchqty",i).c_str()));
                }
                else if( trdtype=="0" )
                {
                    ti.Price=atof(rs.get_field_value("matchprice",i).c_str());
                    ti.Vol=atoi(rs.get_field_value("matchqty",i).c_str());
                }
                else
                {
                    ti.Price = 0;
                    ti.Vol = 0;
                }

            }
        }
        catch( const char * err)
        {
            SetLastError(-1,'E',PLUGINNAME,"编列解列错误! 错误信息:%s.",err);
            return -1;
        }
        catch( const int errcode )
        {
            return errcode;
        }
    }
    else
    {
        AnsiString shseq="";
        AnsiString szseq="";
        if(FRequest.QryCurTrd.SeqNum[0]!=0)
        {
            AnsiString seq = FRequest.QryCurTrd.SeqNum;
            int id = seq.Pos("#");
            shseq=seq.SubString(1,id-1);
            szseq=seq.SubString(id+1,seq.Length());
            ODS("%s,%s\r\n", shseq.c_str(),szseq.c_str());
        }

        std::vector<TTradeInfo>  list;

        //sh
        try
        {
            record_set rs;
            rs.resize(19,1);
            rs.add_field_name("FUNCID");
            rs.add_field_name("g_serverid");
            rs.add_field_name("g_funcid");
            rs.add_field_name("g_operid");
            rs.add_field_name("g_operpwd");
            rs.add_field_name("g_operway");
            rs.add_field_name("g_stationaddr");
            rs.add_field_name("g_checksno");

            rs.add_field_name("custid");
            rs.add_field_name("orgid");
            rs.add_field_name("fundid");
            rs.add_field_name("count");
            rs.add_field_name("poststr");

            rs.add_field_name("market");
            rs.add_field_name("secuid");
            rs.add_field_name("stkcode");
            rs.add_field_name("ordersno");
            rs.add_field_name("creditid");
            rs.add_field_name("creditflag");


            rs.set_field_value("FUNCID","440211");
            rs.set_field_value("g_funcid","440211");
            rs.set_field_value("custid",FSetup.custid.c_str());
            rs.set_field_value("orgid",FSetup.Orgid.c_str());
            rs.set_field_value("market","1");
            rs.set_field_value("fundid",this->FAccInfo.Capital);
            rs.set_field_value("count",AnsiString(IntToStr((int)FRequest.QryCurTrd.MaxRecord)).c_str());
            rs.set_field_value("poststr",shseq.c_str());

            std::string txt = rs.get_text();
            std::string ansText = ReadFirstData(txt);

            size_t pos = rs.set_text(ansText);

            if( atoi(rs.get_field_value("RETCODE").c_str())!= 0 )
            {
                SetLastError(-2,'E',PLUGINNAME,"柜台返回错误! 错误信息:%s.",
                    rs.get_field_value("RETMESSAGE",1).c_str());
                return -2;
            }

            if( atoi(rs.get_field_value("RESULTSIZE").c_str())<=1 )
            {
                goto SZ;
            }

            rs.set_text(ansText,pos);

            assert(rs.get_row_size()>0);
            //NewAns(rs.get_row_size());
            for(size_t i =1; i<=rs.get_row_size(); i++ )
            {
                TTradeInfo ti ;
                strncpy(ti.Account,rs.get_field_value("secuid",i).c_str(),ACC_LEN);
                strncpy(ti.ContractID,rs.get_field_value("ordersno",i).c_str(),SEQ_LEN);
                ti.Date=DateTimeToInt(rs.get_field_value("trddate",i).c_str());
                ti.Market=ConvertMarketType(rs.get_field_value("market",i).c_str());
                strncpy(ti.SecuID,rs.get_field_value("stkcode",i).c_str(),SEQ_LEN);

                shseq = rs.get_field_value("poststr",i).c_str();
                snprintf(ti.SeqNum,SEQ_LEN,"%s#%s",shseq.c_str(),szseq.c_str());

                ti.Time=DateTimeToInt(rs.get_field_value("matchtime",i).c_str())/100;
                strncpy(ti.TrdID,rs.get_field_value("matchcode",i).c_str(),SEQ_LEN);
                ti.Type=otNo;

                std::string trdtype = rs.get_field_value("matchtype",i);
                if( trdtype=="1" || trdtype=="2" || trdtype=="3" )
                {
                    ti.Price = 0;
                    ti.Vol = -abs(atoi(rs.get_field_value("matchqty",i).c_str()));

                    TTradeInfo ti2;
                    memcpy(&ti2,&ti,sizeof(ti2));
                    ti2.Price = atof(rs.get_field_value("orderprice",i).c_str());
                    ti2.Vol = atoi(rs.get_field_value("orderqty",i).c_str())+ti.Vol;
                    if( ti2.Vol>0 )
                        list.push_back(ti2) ;
                }
                else if( trdtype=="0" )
                {
                    ti.Price=atof(rs.get_field_value("matchprice",i).c_str());
                    ti.Vol=atoi(rs.get_field_value("matchqty",i).c_str());
                    if( atoi(rs.get_field_value("orderqty",i).c_str())!= ti.Vol )
                        continue; //如果部分成交就忽略掉
                }
                else
                {
                    ti.Price = 0;
                    ti.Vol = 0;
                    continue;
                }
                list.push_back(ti) ;
                //ODS("sh:%d",list.size());
            }
        }
        catch( const char * err)
        {
            SetLastError(-1,'E',PLUGINNAME,"编列解列错误! 错误信息:%s.",err);
            return -1;
        }
        catch( const int errcode )
        {
            return errcode;
        }

SZ:
        //sz

        try
        {
            record_set rs;
            rs.resize(19,1);
            rs.add_field_name("FUNCID");
            rs.add_field_name("g_serverid");
            rs.add_field_name("g_funcid");
            rs.add_field_name("g_operid");
            rs.add_field_name("g_operpwd");
            rs.add_field_name("g_operway");
            rs.add_field_name("g_stationaddr");
            rs.add_field_name("g_checksno");

            rs.add_field_name("custid");
            rs.add_field_name("orgid");
            rs.add_field_name("fundid");
            rs.add_field_name("count");
            rs.add_field_name("poststr");

            rs.add_field_name("market");
            rs.add_field_name("secuid");
            rs.add_field_name("stkcode");
            rs.add_field_name("ordersno");
            rs.add_field_name("creditid");
            rs.add_field_name("creditflag");


            rs.set_field_value("FUNCID","440211");
            rs.set_field_value("g_funcid","440211");
            rs.set_field_value("custid",FSetup.custid.c_str());
            rs.set_field_value("orgid",FSetup.Orgid.c_str());
            rs.set_field_value("market","0");
            rs.set_field_value("fundid",this->FAccInfo.Capital);
            rs.set_field_value("count",AnsiString(IntToStr((int)FRequest.QryCurTrd.MaxRecord)).c_str());
            rs.set_field_value("poststr",szseq.c_str());

            std::string txt = rs.get_text();
            std::string ansText = ReadFirstData(txt);

            size_t pos = rs.set_text(ansText);

            if( atoi(rs.get_field_value("RETCODE").c_str())!= 0 )
            {
                SetLastError(-2,'E',PLUGINNAME,"柜台返回错误! 错误信息:%s.",
                    rs.get_field_value("RETMESSAGE",1).c_str());
                return -2;
            }

            if( atoi(rs.get_field_value("RESULTSIZE").c_str())<=1 )
            {
                goto end;
            }

            rs.set_text(ansText,pos);

            assert(rs.get_row_size()>0);
            //NewAns(rs.get_row_size());
            for(size_t i =1; i<=rs.get_row_size(); i++ )
            {
                TTradeInfo ti ;
                strncpy(ti.Account,rs.get_field_value("secuid",i).c_str(),ACC_LEN);
                strncpy(ti.ContractID,rs.get_field_value("ordersno",i).c_str(),SEQ_LEN);
                ti.Date=DateTimeToInt(rs.get_field_value("trddate",i).c_str());
                ti.Market=ConvertMarketType(rs.get_field_value("market",i).c_str());
                strncpy(ti.SecuID,rs.get_field_value("stkcode",i).c_str(),SEQ_LEN);
                snprintf(ti.SeqNum,SEQ_LEN,"%s#%s",shseq.c_str(),rs.get_field_value("poststr",i).c_str());
                //strncpy(ti.SeqNum,rs.get_field_value("poststr",i).c_str(),SEQ_LEN);
                ti.Time=DateTimeToInt(rs.get_field_value("matchtime",i).c_str())/100;
                strncpy(ti.TrdID,rs.get_field_value("matchcode",i).c_str(),SEQ_LEN);
                ti.Type=otNo;

                std::string trdtype = rs.get_field_value("matchtype",i);
                if( trdtype=="1" || trdtype=="2" || trdtype=="3" )
                {
                    ti.Price = 0;
                    ti.Vol = -abs(atoi(rs.get_field_value("matchqty",i).c_str()));

                    TTradeInfo ti2;
                    memcpy(&ti2,&ti,sizeof(ti2));
                    ti2.Price = atof(rs.get_field_value("orderprice",i).c_str());
                    ti2.Vol = atoi(rs.get_field_value("orderqty",i).c_str())+ti.Vol;
                    if( ti2.Vol>0 )
                        list.push_back(ti2) ;
                }
                else if( trdtype=="0" )
                {
                    ti.Price=atof(rs.get_field_value("matchprice",i).c_str());
                    ti.Vol=atoi(rs.get_field_value("matchqty",i).c_str());
                    if( atoi(rs.get_field_value("orderqty",i).c_str())!= ti.Vol )
                        continue; //如果部分成交就忽略掉
                }
                else
                {
                    ti.Price = 0;
                    ti.Vol = 0;
                    continue;
                }
                list.push_back(ti) ;
                //ODS("sz:%d",list.size());
            }
        }
        catch( const char * err)
        {
            SetLastError(-1,'E',PLUGINNAME,"编列解列错误! 错误信息:%s.",err);
            return -1;
        }
        catch( const int errcode )
        {
            return errcode;
        }

end:
        NewAns( list.size() );
        for(int i=0; i<list.size();i++)
        {
            memcpy(&(*FAnswer)[i].QryCurTrd.TrdInfo,&list[i],sizeof( TTradeInfo ));
            //ODS("ans:%d",i);
        }
    }

    */
    database db;
	TradeGateway::ExecutionReportSeq list;
	try
	{
		if(FRequest.QryCurTrd.OrderID[0]==0)
		{
			//增量查询
			db.qry_trades(this->FAccInfo.Capital,FRequest.QryCurTrd.SeqNum,
					FRequest.QryCurTrd.MaxRecord,
					Date().FormatString("yyyymmdd").ToInt(),
					list) ;
		}
		else
		{
			db.qry_trade_by_ordid(this->FAccInfo.Capital,FRequest.QryCurTrd.OrderID,
				Date().FormatString("yyyymmdd").ToInt(),
				list);
		}

		if( list.size()==0 ) return 0;

		NewAns(list.size());
		for( size_t i=0;i<list.size();i++)
		{
		    TTradeInfo &ti = (*FAnswer)[i].QryCurTrd.TrdInfo;
            TradeGateway::ExecutionReport &er = list[i];
            strncpy(ti.Account,er.accountId.c_str(),ACC_LEN);
            strncpy(ti.ContractID,er.ordId.c_str(),SEQ_LEN);
            ti.Date=er.tradeDate;
            ti.Market=mtNo;
            ti.Price=er.lastPx;
            strncpy(ti.SecuID,"",SEQ_LEN);
            strncpy(ti.SeqNum,er.seq.c_str(),SEQ_LEN);
            ti.Time=er.transactTime;
            strncpy(ti.TrdID,er.execId.c_str(),SEQ_LEN);
            ti.Type=otNo;
            ti.Vol=abs((int)er.lastQty);
            if( er.type == TradeGateway::EtCanceled ||
                er.type == TradeGateway::EtRejected ||
                er.type == TradeGateway::Stopped )
                ti.Vol= -ti.Vol;
		}
	}
	catch( std::string &err)
	{
		SetLastError(-1,'E',PLUGINNAME,err.c_str());
		return -1;
	}
 	return 0;

	return 0;
}

//查询帐号中所有的股份
/*
股份明细查询(440208)

功能代码	440208
功能描述	股份明细查询
请求数据	域名称	标识	类型及长度	必要	描述
	客户代码	custid	Int64	Y
	客户机构	orgid	Char(4)	Y
	交易市场	market	char(1)	N	不送查询全部
	资金帐户	fundid	int64	N
	股东代码	secuid	char(10)	N	不送查询全部
	证券代码	stkcode	char(8)	N	不送查询全部
	请求行数	count	int 	Y	每次取的行数
	定位串  	poststr	char(64)	Y	第一次填空
	业务标志	busiflag	char(1)	N	0 普通股份
1 普通帐户担保品
返回数据	域名称	标识	类型及长度	描述
	定位串  	poststr	char(64)
	客户代码	custid	int64
	资金账户	fundid	int64
	交易市场	market	char(1)
	股东代码	secuid	char(10)
	证券代码	stkcode	char(8)
	证券名称	stkname	char(8)
	机构编码	orgid	char(4)
	货币	moneytype	char(1)
	股份余额	stkbal	Int
	股份可用	stkavl	Int
	当前成本	buycost	Numeric(15,2)
	成本价格	costprice	Numeric(9,3)
	市值	mktval	Numeric(15,2)
	盈亏	income	numeric(15,2)
	市值计算标识	mtkcalflag	char(1)
	当前拥股数	stkqty	Int
	昨日余额	lastbal	Int
	卖出冻结数	stksale	Int
	人工冻结数	stkfrz	Int
	当前价	price	Numeric(9,3)
	今日买入数量	stkbuy	Int	注：stktrdfrz
	可申赎数量	stkdiff	int
	交易类型	trdid	char(1)
错误描述	错误代码	错误信息
备注信息		送证券代码必须送交易市场
	当前拥股数：目前帐户拥有的股数，包含买入成交，在途等，剔除卖出成交等
	成本价格：根据后台‘成本价格标志’的配置，可分别返回‘买入成本’或者‘持仓成本’。

*/
int TTrdItfImp::QryStocks()
{
	std::string posstr="";
	std::list<TStockInfo> list;
	try
	{
		while(1)
		{
			record_set rs(17,1);

			rs.add_field_name("FUNCID");
			rs.add_field_name("g_serverid");
			rs.add_field_name("g_funcid");
			rs.add_field_name("g_operid");
			rs.add_field_name("g_operpwd");
			rs.add_field_name("g_operway");
			rs.add_field_name("g_stationaddr");
			rs.add_field_name("g_checksno");

			rs.add_field_name("custid");
			rs.add_field_name("orgid");
			rs.add_field_name("market");
			rs.add_field_name("count");
			rs.add_field_name("poststr");

            rs.add_field_name("fundid");
            rs.add_field_name("secuid");
            rs.add_field_name("stkcode");
            rs.add_field_name("busiflag");

			rs.set_field_value("FUNCID","440208");
			rs.set_field_value("g_funcid","440208");
			rs.set_field_value("custid",FSetup.custid.c_str());
			rs.set_field_value("orgid",FSetup.Orgid.c_str());
			rs.set_field_value("market",this->ConvertMarketType(FRequest.QryStocks.Market));
			rs.set_field_value("count","100");
			rs.set_field_value("poststr",posstr.c_str());

			std::string txt = rs.get_text();
			std::string ansText = ReadFirstData(txt);

			size_t pos = rs.set_text(ansText);

			if( atoi(rs.get_field_value("RETCODE").c_str())!= 0 )
			{
				SetLastError(-2,'E',PLUGINNAME,"柜台返回错误! 错误信息:%s.",
					rs.get_field_value("RETMESSAGE",1).c_str());
				return -2;
			}

			if( atoi(rs.get_field_value("RESULTSIZE").c_str())<=1 )
			{
				break;
			}

			rs.set_text(ansText,pos);

			for(size_t i =1; i<=rs.get_row_size(); i++ )
			{
				posstr = rs.get_field_value("poststr",i) ;
				TStockInfo si;

				memset(&si, 0, sizeof(TStockInfo));
				strncpy(si.Account, rs.get_field_value("secuid",i).c_str(), ACC_LEN);
				strncpy(si.SecuID , rs.get_field_value("stkcode",i).c_str(), CODE_LEN);
				si.Market = this->ConvertMarketType(rs.get_field_value("market",i).c_str());
				si.Balance   = atoi(rs.get_field_value("stkbuy",i).c_str());
				si.Available = atoi(rs.get_field_value("stkavl",i).c_str());
				si.PosDir    = pdNet;
				si.PosNum    = atoi(rs.get_field_value("stkqty",i).c_str())  ;
				si.CostPrice = atof(rs.get_field_value("costprice",i).c_str());
				si.CurPrice  = atof(rs.get_field_value("price",i).c_str());

				list.push_back(si);
			}
		}

		if( list.size() >0 )
		{
			NewAns(list.size());
			int i=0;
			for( std::list<TStockInfo>::const_iterator iter=list.begin();
				iter!=list.end(); iter++)
			{
				memcpy(&((*FAnswer)[i++].QryStocks.StockInfo), &(*iter), sizeof(TStockInfo));
			}
		}

	}
	catch( const char * err)
	{
        SetLastError(-1,'E',PLUGINNAME,"编列解列错误! 错误信息:%s.",err);
        return -1;
	}
    catch( const int errcode )
    {
        return errcode;
    }

	return 0;
}

//委托
/*
委托(批量委托/普通买卖)(440303)
功能代码	440303
功能描述	出入参描述：
（1）包头包括：柜员代码、资金帐号、货币代码、买卖类别、压缩标志、委托资金计算方式、操作方式、总委托笔数、扣款金额（与委托资金计算方式匹配，默认填0，由后台计算）、备注信息
（2）包体包括：市场代码、股东代码、证券代码、买卖类别、委托数量、货币代码、委托价格、席位；循环打包。
（3）返回包括：批次号、委托总笔数、委托总金额、有效委托笔数、有效委托总金额、本次扣款金额
主要流程描述：
    批量委托后，要把相关的批次号记录下来，供440212查询使用。
委托包打包方式描述：
  入参之委托包（定长、不足后补0x00）：
struct tagskepOrderUnit{
  char market;             //交易市场
  char secuid[11];         //股东代码
  char stkcode[7];         //证券代码
  char bsflag[3];          //买卖标志
  char orderqty[11];       //委托数量
  char moneytype;          //货币代码
  char orderprice[10];     //委托价格，bsflag为市价委托时无效
  char seat[7];            //席位代码
  char ordersno[11];       //
  char cancelfalg;
};
  出参之失败股票列表：
Struct tagstklist{
  Char stkcode[7]
}

请求数据	域名称	标识	类型及长度	必要	描述
	客户代码	custid	Int64	Y
	客户机构	orgid	Char(4)	Y
	篮子类型	skeptype	Char(1)	Y	0-ETF买卖篮 1-普通批量委托 2-其他组合
	组合编号	Stkgroupid	Char(6)	N	普通批量委托填空，否则填写ETF基金代码或其他组合代码
	资金账号	Fundid	Int64	Y
	交易市场	market	char	Y
	股东代码	secuid	Char(10)	Y
	买卖类别	Bsflag	Char(2)	Y	见数据字典Emmlb
	币种	moneytype	Char(1)	Y
	批次号	Ordergroup	Int	N	一般为0或空，除非想把本委托加入到某个批次当中
	委托笔数	Ordernum	Int	Y
	委托数据包长度	datalen	Int	Y
	委托包	skeppackage	Varchar	Y

返回数据	域名称	标识	类型及长度	描述
	批次号	Ordergroup	Int
	成功笔数	OrderOkNum	Int
	失败笔数	OrderFailNum	Int
	本次扣款金额	OrderFrzAmt	Numeric(19,3)
	失败股票列表	StkErrList	Varchar
错误描述	错误代码	错误信息



ETF申购、赎回(440305)
功能代码	440305
功能描述	出入参描述：
功能描述：


请求数据	域名称	标识	类型及长度	必要	描述
	客户代码	custid	Int64	Y
	客户机构	orgid	Char(4)	Y
	资金账号	Fundid	Int64	Y
	基金代码	Ofcode	Char(6)	Y
	市场代码	Market	Char(1)	Y
	申购份额	Stkqty	Int	Y
	股东代码	Secuid	Char(10)	Y
	交易类型	bsflag	Char（2）	Y	01 申购
　 02 赎回
返回数据	域名称	标识	类型及长度	描述
	委托序号	Ordersno	Int
	合同号	Orderid	Char(10)
	冻结资金	FrzFundamt	Numeric(19,3)


错误描述	错误代码	错误信息



*/

#pragma pack(1)
///入参之委托包（定长、不足后补0x00）：
struct tagskepOrderUnit
{
  char market;             //交易市场
  char secuid[11];         //股东代码
  char stkcode[7];         //证券代码
  char bsflag[3];          //买卖标志
  char orderqty[11];       //委托数量
  char moneytype;          //货币代码
  char orderprice[10];     //委托价格，bsflag为市价委托时无效
  char seat[7];            //席位代码
  char ordersno[11];       //
  char cancelfalg;
};

//出参之失败股票列表：
struct tagstklist{
  Char stkcode[7];
};
#pragma pack()
int TTrdItfImp::Order()
{
	try
	{
		record_set rs(21,1);

        rs.add_field_name("FUNCID");
        rs.add_field_name("g_serverid");
        rs.add_field_name("g_funcid");
        rs.add_field_name("g_operid");
        rs.add_field_name("g_operpwd");
        rs.add_field_name("g_operway");
        rs.add_field_name("g_stationaddr");
        rs.add_field_name("g_checksno");

		rs.add_field_name("custid");
		rs.add_field_name("orgid");
		rs.add_field_name("skeptype");
        rs.add_field_name("stkgroupid");
		rs.add_field_name("fundid");
		rs.add_field_name("market");
		rs.add_field_name("secuid");
		rs.add_field_name("bsflag");
        rs.add_field_name("ordergroup");
		rs.add_field_name("moneytype");
		rs.add_field_name("ordernum");
		rs.add_field_name("datalen");
		rs.add_field_name("skeppackage");

		rs.set_field_value("FUNCID","440303");
		rs.set_field_value("g_funcid","440303");
        rs.set_field_value("custid",FSetup.custid.c_str());
        rs.set_field_value("orgid",FSetup.Orgid.c_str());
		rs.set_field_value("skeptype","1");
		rs.set_field_value("fundid",this->FAccInfo.Capital);
		rs.set_field_value("market",this->ConvertMarketType(FRequest.Order.Market));
		rs.set_field_value("bsflag",this->ConvertOrderType(FRequest.Order.Type));
		rs.set_field_value("moneytype",this->ConvertMoneyType(motRMB));
        rs.set_field_value("secuid",this->GetStockAccountByMarket(FRequest.Order.Market));
		rs.set_field_value("ordernum","1");
		AnsiString len =IntToStr((int)sizeof(tagskepOrderUnit));
		rs.set_field_value("datalen",len.c_str());
		AnsiString pkg;
		tagskepOrderUnit ord;
        memset(&ord,0,sizeof(ord));
		ord.market = this->ConvertMarketType(FRequest.Order.Market)[0];
		strncpy(ord.secuid,this->GetStockAccountByMarket(FRequest.Order.Market),11);
		strncpy(ord.stkcode,FRequest.Order.SecuID,7);
		strncpy(ord.bsflag,this->ConvertOrderType(FRequest.Order.Type),3);
		sprintf(ord.orderqty,"%d",FRequest.Order.Num);
		ord.moneytype = this->ConvertMoneyType(motRMB)[0];

		AnsiString sPrice;
		if( AnsiPos(AnsiString("510"),FRequest.Order.SecuID ) == 1 ||
			AnsiPos(AnsiString("1599"),FRequest.Order.SecuID ) == 1 )
		{
			sPrice  = ConvetDoubleToPrice( FRequest.Order.Price,3);
		}
		else
		{
			sPrice  = ConvetDoubleToPrice( FRequest.Order.Price,2);
		}
		sprintf(ord.orderprice,"%s",sPrice.c_str());
		strncpy(ord.seat,"",7);
		strncpy(ord.ordersno,"0",11);
		ord.cancelfalg=' ';

		pkg.printf("BINBEGIN%c%-11s%-7s%-3s%-11s%c%-10s%-7s%-11s%cBINEND",
			ord.market,
			ord.secuid,
			ord.stkcode,
			ord.bsflag,
			ord.orderqty,
			ord.moneytype,
			ord.orderprice,
			ord.seat,
			ord.ordersno,
			ord.cancelfalg);
		rs.set_field_value("skeppackage",pkg.c_str());

		std::string txt = rs.get_text();
		std::string ansText = ReadFirstData(txt);

        size_t pos = rs.set_text(ansText);

        if( atoi(rs.get_field_value("RETCODE").c_str())!= 0 )
        {
            SetLastError(-2,'E',PLUGINNAME,"柜台返回错误! 错误信息:%s.",
                rs.get_field_value("RETMESSAGE",1).c_str());
            return -2;
        }

        if( atoi(rs.get_field_value("RESULTSIZE").c_str())<=1 )
        {
            SetLastError(-3,'E',PLUGINNAME,"柜台没有返回更多的结果集");
            return -3;
        }

        rs.set_text(ansText,pos);
		assert(rs.get_row_size()==1);

		int succn = atoi(rs.get_field_value("orderoknum").c_str());
		//failn = atoi(rs.get_field_value("OrderFailNum").c_str());

		if( succn==1 )
		{
			NewAns(1);
			strncpy((*FAnswer)[0].Order.ContractID, rs.get_field_value("ordergroup").c_str() , SEQ_LEN);

            //add to db
			TradeGateway::OrderReport op;
			op.base.accountId = this->FAccInfo.Capital;
			op.base.inst.securityID = FRequest.Order.SecuID;
			switch (FRequest.Order.Market) {
			case mtSHA : op.base.inst.securityIDSource = TradeGateway::SSE;
			break;
			case mtSZA : op.base.inst.securityIDSource =  TradeGateway::SZSE;
			break;
			case mtJJS : op.base.inst.securityIDSource =  TradeGateway::SHFE;
			break;
			case mtFSH : op.base.inst.securityIDSource =  TradeGateway::DCE;
			break;
			case mtFZZ : op.base.inst.securityIDSource = TradeGateway::CZCE ;
			break;
			case mtFDL : op.base.inst.securityIDSource =  TradeGateway::CFFEX;
			break;
			case mtHK  : op.base.inst.securityIDSource =  TradeGateway::HKEX;
			break;
			case mtNo  : op.base.inst.securityIDSource = TradeGateway::MktUnknow ;
			break;
			}

			switch( FRequest.Order.Type )
			{
			case otBuy:
				op.base.s=TradeGateway::Buy;
				break;
			case otSell  :
				op.base.s=TradeGateway::Sell;
				break;
			case otETFSub:
				op.base.s=TradeGateway::Subscribe;
				break;
			case otETFRed:
				op.base.s=TradeGateway::Redeem;
				break;
			}

			op.base.posEfct = TradeGateway::PosEftUnknow;
			op.base.type = TradeGateway::Limit;
			op.base.lmtPrice =  FRequest.Order.Price;
			op.base.ordQty =FRequest.Order.Num;
			op.base.ordId = (*FAnswer)[0].Order.ContractID;
			op.base.date = Date().FormatString("yyyymmdd").ToInt();
			op.base.time = Time().FormatString("hhnnss").ToInt();
			op.ordStatus = TradeGateway::PendingNew;
			op.cumQty = 0;
			op.avgPx = 0;
			op.leavesQty =FRequest.Order.Num;

			database db;
            try
            {
			    db.add_order(&op.base);
			    order_man.add_order(op);
            }
            catch( std::string &err)
            {
                SetLastError(-1,'E',PLUGINNAME,"加入委托到本地数据库失败:%s",err.c_str());
                return -1;
            }
		}
		else return -1;
	}
	catch( const char * err)
	{
        SetLastError(-1,'E',PLUGINNAME,"编列解列错误! 错误信息:%s.",err);
        return -1;
	}
    catch( const int errcode )
    {
        return errcode;
    }

	return 0;
}

/*

批量撤单(440304)
功能代码	440304
功能描述	出入参描述：
（1）包头包括：批次号、柜员代码、资金帐号、货币代码、操作方式、总撤单笔数、备注信息
（2）包体包括：市场代码、股东代码、合同序号；循环打包
（3）返回包括：成功撤单笔数
功能描述：

委托包打包方式描述：
 struct tagskepOrderUnit{
  char market;             //交易市场
  char secuid[11];         //股东代码
  char stkcode[7];         //证券代码
  char bsflag[3];          //买卖标志
  char orderqty[11];       //委托数量
  char moneytype;          //货币代码
  char orderprice[10];     //委托价格，bsflag为市价委托时无效
  char seat[7];            //席位代码
  char ordersno[11];           //
  char cancelflag;
};
失败撤单列表为：委托序号#失败原因$(重复)
请求数据	域名称	标识	类型及长度	必要	描述
	客户代码	custid	Int64	Y
	营业部代码	orgid	Char(4)	Y
	资金账号	Fundid	Int64	Y
	批次号	Ordergroup	Int	Y
	委托笔数	Ordernum	Int	Y
	打包版本	PacketVer	Int	Y
	委托包	OrderPacket	Varchar	Y
	委托包长度	packlen	Int	Y
返回数据	域名称	标识	类型及长度	描述
	批次号	Ordergroup	Int
	成功笔数	CancelOkNum	Int
	失败笔数	CancelFailNum	Int
	失败撤单列表	CancelErrList	Varchar



错误描述	错误代码	错误信息



*/
int TTrdItfImp::Undo()
{
    TRequest req;
	req.QryCurCsn.ReqHead.FuncType = ftQryCurCsn;
	strncpy(req.QryCurCsn.OrderID, FRequest.Undo.ContractID,SEQ_LEN);
    req.QryCurCsn.MaxRecord = -1; // 查seat

	TAnswer *ans=NULL;
	int count=0;
	try
	{
		if( this->Request(req,&ans,count) != 0 || count <1)
		{
			SetLastError(-2,'E',PLUGINNAME,"该委托号不存在:%s.",FRequest.Undo.ContractID);
			return -2;
		}

		TOrderInfo &oi = ans[0].QryCurCsn.OrderInfo;

		try
		{
			record_set rs(16,1);

            rs.add_field_name("FUNCID");
            rs.add_field_name("g_serverid");
            rs.add_field_name("g_funcid");
            rs.add_field_name("g_operid");
            rs.add_field_name("g_operpwd");
            rs.add_field_name("g_operway");
            rs.add_field_name("g_stationaddr");
            rs.add_field_name("g_checksno");

            rs.add_field_name("custid");
            rs.add_field_name("orgid");
            rs.add_field_name("fundid");
            rs.add_field_name("ordergroup");
            rs.add_field_name("packetver");
            rs.add_field_name("ordernum");
            rs.add_field_name("packlen");
            rs.add_field_name("orderpacket");

			rs.set_field_value("FUNCID","440304");
			rs.set_field_value("g_funcid","440304");
			rs.set_field_value("custid",FSetup.custid.c_str());
			rs.set_field_value("orgid",FSetup.Orgid.c_str());
			rs.set_field_value("fundid",this->FAccInfo.Capital);
			rs.set_field_value("ordergroup",FRequest.Undo.ContractID);
			rs.set_field_value("packetver","0");
			rs.set_field_value("ordernum","1");
			AnsiString len =IntToStr((int)sizeof(tagskepOrderUnit));
			rs.set_field_value("packlen",len.c_str());

			AnsiString pkg;
			tagskepOrderUnit ord;
            memset(&ord,0,sizeof(ord));
			ord.market = this->ConvertMarketType(oi.Market)[0];
			strncpy(ord.secuid,this->GetStockAccountByMarket(oi.Market),11);
			strncpy(ord.stkcode,oi.SecuID,7);
			strncpy(ord.bsflag,this->ConvertOrderType(oi.Type),3);
			sprintf(ord.orderqty,"%d",oi.CsnVol);
			ord.moneytype = this->ConvertMoneyType(motRMB)[0];

			AnsiString sPrice="0.00";
			sprintf(ord.orderprice,"%s",sPrice.c_str());
			strncpy(ord.seat,oi.SeqNum,7);
			strncpy(ord.ordersno,FRequest.Undo.ContractID,11);
			ord.cancelfalg=' ';
			pkg.printf("BINBEGIN%c%-11s%-7s%-3s%-11s%c%-10s%-7s%-11s%cBINEND",
				ord.market,
				ord.secuid,
				ord.stkcode,
				ord.bsflag,
				ord.orderqty,
				ord.moneytype,
				ord.orderprice,
				ord.seat,
				ord.ordersno,
				ord.cancelfalg);
			rs.set_field_value("orderpacket",pkg.c_str());

			std::string txt = rs.get_text();
			std::string ansText = ReadFirstData(txt);

			size_t pos = rs.set_text(ansText);

			if( atoi(rs.get_field_value("RETCODE").c_str())!= 0 )
			{
				SetLastError(-2,'E',PLUGINNAME,"柜台返回错误! 错误信息:%s.",
					rs.get_field_value("RETMESSAGE",1).c_str());
				return -2;
			}

			if( atoi(rs.get_field_value("RESULTSIZE").c_str())<=1 )
			{
				SetLastError(-3,'E',PLUGINNAME,"柜台没有返回更多的结果集");
				return -3;
			}

			rs.set_text(ansText,pos);
			assert(rs.get_row_size()==1);

			int succn = atoi(rs.get_field_value("canceloknum").c_str());
			//int failn = atoi(rs.get_field_value("CancelFailNum").c_str());

			if( succn==1 )
			{
				return 0;
			}
			else
			{
				SetLastError(-3,'E',PLUGINNAME,"撤单失败,%s",
					rs.get_field_value("cancelerrlist").c_str());
				return -1;
			}
		}
		catch( const char * err)
		{
			SetLastError(-1,'E',PLUGINNAME,"编列解列错误! 错误信息:%s.",err);
			return -1;
		}
		catch( const int errcode )
		{
			return errcode;
		}
	}
	__finally
	{
		this->FreeAnswer(ans);
    }
	return 0;
}

market_type  TTrdItfImp::ConvertMarketType(const char *t)
{
	if( t==NULL || strlen(t)<1 ) return mtNo;
	if( t[0]=='1' )
	{
		return mtSHA;
	}
	else if( t[0] == '0' )
	{
		return mtSZA;
	}
	else return mtNo;
}

order_type   TTrdItfImp::ConvertOrderType(const char *t)
{
	if(t==NULL || strlen(t)<2 ) return otNo;
	switch (t[1]) {
		case 'B': return otBuy;
		case 'S': return otSell;
		case '1': return otETFSub;
		case '2': return otETFRed;
		default:
			return otNo;
	}
}

order_state  TTrdItfImp::ConvertOrderState(const char *t)
{
	//'0','未报' 在lbm中委托成功写入未发标志
	//'1','正报' 在落地方式中,报盘扫描未发委托,并将委托置为正报状态
	//'2','已报' 报盘成功后,报盘机回写发送标志为已报
	//'3','已报待撤' 已报委托撤单
	//'4','部成待撤' 部分成交后委托撤单
	//'5','部撤' 部分成交后撤单成交
	//'6','已撤' 全部撤单成交
	//'7','部成' 已报委托部分成交
	//'8','已成' 委托或撤单全部成交
	//'9','废单' 委托确认为费单
	//'A','待报'
	//'B','正报' 国泰模式中，已报道接口库尚未处理返回库的阶段，标准模式不用。
	if(t==NULL || strlen(t)<1 ) return osno;
	switch(t[0])
	{
	case '0':
	case '1':
	case 'A':
	case 'B':
		return oswb;
	case '2':
		return osyb;
	case '3':
	case '4':
		return osdc;
	case '5':
		return osbw;
	case '6':
		return osyc;
	case '7':
		return osbc;
	case '8':
		return oscj;
	case '9':
		return osyf;
	default:
		return osno;
	}
}

pos_direction TTrdItfImp::ConvertPosDir(const char *t)
{
	return pdNo;
}

money_type   TTrdItfImp::ConvertMoneyType(const char *t)
{
	return motRMB;
}

char *  TTrdItfImp::ConvertMarketType(market_type t)
{
    switch(t)
    {
        case mtSHA:
            return "1";
        break;
        case mtSZA:
            return "0";
        break;
        default:
			return " ";
	}
	return " ";
}

char *  TTrdItfImp::ConvertOrderType(order_type t)
{
/*
外围委托买卖类别bsflag
代码	货币名称
0B	买入
0S	卖出
0G	转股
0H	回售
01	ETF申购
02	ETF赎回
03	LOF申购
04	LOF赎回
07	认沽行权
08	认售行权
0a	对方买入
0b	本方买入
0c	即时买入
0d	五档买入
0e	全额买入
0f	对方卖出
0g	本方卖出
0h	即时卖出
0i	五档卖出
0j	全额卖出
0n	入质
0p	出质
0q	转限买入
0r	转限卖出

*/
	switch (t) {
	case 	otBuy      : return "0B";
	case 	otSell     : return "0S";
	case 	otETFSub   : return "01";
	case 	otETFRed   : return "02";
	default:
		return "";
	}
}

char *  TTrdItfImp::ConvertOrderState(order_state t)
{
	return "" ;
}

char *  TTrdItfImp::ConvertPosDir(pos_direction t)
{
	return "";
}

char *  TTrdItfImp::ConvertMoneyType(money_type t)
{
	switch (t)
	{
	case motRMB : return "0";
	case motUSD : return "2";
    case motHKD : return "1";
	default: return " ";
	}
}

//将配置信息读出来,如果没有获取完整的配置信息返回false
bool TTrdItfImp::GetConfig(void)
{
    if( FSetupFile== NULL ) return false;

    TMemIniFile *ini = new TMemIniFile( FSetupFile );
    try
    {
        // 判断是否存在插件的设置，没有的话返回false以便系统能够生成默认的设置
        if( ini->SectionExists(PLUGINNAME) == false ) return false;

		FSetup.SvrIp        = ini->ReadString (PLUGINNAME,"SvrIP",FSetup.SvrIp);
		FSetup.SvrPort      = ini->ReadInteger(PLUGINNAME,"SvrPort",FSetup.SvrPort);
		FSetup.PushPort      = ini->ReadInteger(PLUGINNAME,"PushPort",FSetup.PushPort);
		FSetup.TimeOut      = ini->ReadInteger(PLUGINNAME,"TimeOut",FSetup.TimeOut);
		FSetup.debug_mode   = ini->ReadBool(PLUGINNAME,"debug_mode",FSetup.debug_mode);
		FSetup.local_ip     = ini->ReadString(PLUGINNAME,"local_ip",FSetup.local_ip);
		FSetup.custid       = ini->ReadString (PLUGINNAME,"custid",FSetup.custid);
		FSetup.Orgid        = ini->ReadString (PLUGINNAME,"Orgid",FSetup.Orgid);
    }
	__finally
    {
        delete ini;
    }
	return true;
}

//将配置信息回写到配置文件
void TTrdItfImp::SetConfig(void)
{
	if( FSetupFile== NULL ) return ;

    TMemIniFile *ini = new TMemIniFile( FSetupFile );
    try
    {
		ini->WriteString (PLUGINNAME,"SvrIP",        FSetup.SvrIp);
		ini->WriteInteger(PLUGINNAME,"SvrPort",      FSetup.SvrPort);
		ini->WriteInteger(PLUGINNAME,"PushPort",     FSetup.PushPort);
		ini->WriteInteger(PLUGINNAME,"TimeOut",      FSetup.TimeOut);
		ini->WriteBool   (PLUGINNAME,"debug_mode",   FSetup.debug_mode);
		ini->WriteString (PLUGINNAME,"local_ip",     FSetup.local_ip);
		ini->WriteString (PLUGINNAME,"custid",       FSetup.custid);
		ini->WriteString (PLUGINNAME,"Orgid",        FSetup.Orgid);

        ini->UpdateFile();
    }
    __finally
    {
        delete ini;
	}
}

//关闭中间件链接
void TTrdItfImp::CloseLink(void)
{
/*
	try
    {
        FidTcp->Disconnect();
    }
    catch(...)
    {

	}
*/
}

int TTrdItfImp::KeepAlive(void)
{
    order_man.qry_orders(this);
	return 0;
}

std::map<std::string,int> order_manager::userid_list;
boost::mutex order_manager::_map_mutex;

void order_manager::load_working_orders(const std::string &userid)
{
	clear_all();

	if( add_user(userid) )
	{
		database db;
		std::string seq ="";
		TradeGateway::OrderReportSeq ors;
		try
		{
			int ret = 0;
			do
			{
				ret=db.qry_working_orders(userid,seq,100,
					Date().FormatString("yyyymmdd").ToInt(),ors);
			}
			while(ret==100);
		}
		catch( std::string &err)
		{
			ODS("查工作委托失败,%s",err.c_str()) ;
		}
		boost::mutex::scoped_lock lock(_mutex);
		for(size_t i=0;i<ors.size();i++)
		{
			FOrders.push_back(ors[i]);
		}
		_userid = userid;
	}
}

void order_manager::qry_orders(TTrdItfImp *itf)
{
	ORDERS work;
	ORDER_ITERATOR iter;

	_mutex.lock();
	for( iter=FOrders.begin(); iter!=FOrders.end(); iter++)
	{
		work.push_back(*iter) ;
	}
	FOrders.clear();
	_mutex.unlock();

	for( iter=work.begin(); iter!=work.end(); iter++)
	{
		//iter->base.ordId
		TRequest req;
		req.QryCurCsn.ReqHead.FuncType = ftQryCurCsn;
		strncpy(req.QryCurCsn.OrderID, iter->base.ordId.c_str(),SEQ_LEN);

		TAnswer *ans=NULL;
		int count = 0;
        itf->lock();
        try
        {
            if( itf->Request(req,&ans,count) == 0 )
            {
                if(  count == 1 )
                {
                    int trdvol = ans[0].QryCurCsn.OrderInfo.TrdVol;
                    double price = ans[0].QryCurCsn.OrderInfo.TrdPrice;
                    int ordvol = ans[0].QryCurCsn.OrderInfo.CsnVol;
                    int cancle = abs(ans[0].QryCurCsn.OrderInfo.CancelVol);
                    order_state os = ans[0].QryCurCsn.OrderInfo.State;
                    if( os==osyf )
                        cancle = ordvol-trdvol;

                    int oldtrdvol = iter->cumQty;
                    double oldprice  = iter->avgPx;
                    int oldordvol = iter->base.ordQty;
                    int oldleavesqty = iter->leavesQty;

                    assert(  oldordvol ==   ordvol);
                    assert(  oldtrdvol<=trdvol );

                    database db;

                    int trdnum = trdvol-oldtrdvol;
                    if( trdnum > 0 ) //有成交
                    {
                        double lastprice =(trdvol*price-oldtrdvol*oldprice)/trdnum;

                        //生成成交记录
                        TradeGateway::ExecutionReport er;
                        er.accountId = iter->base.accountId;
                        er.ordId = iter->base.ordId;
                        er.type =  TradeGateway::EtTrade;
                        er.lastQty = trdnum;
                        er.lastPx = lastprice;
                        er.tradeDate = iter->base.date;
                        er.transactTime = Time().FormatString("hhnnss").ToInt();
                        db.add_trade(&er);
                    }

                    iter->cumQty = trdvol;
                    iter->avgPx = price;
                    iter->leavesQty = ordvol-trdvol-cancle;
                    assert( iter->leavesQty>=0 );

                    if( cancle >0 )
                    {
                        assert(trdvol+cancle==ordvol) ;
                        //生成撤单记录
                        TradeGateway::ExecutionReport er;
                        er.accountId = iter->base.accountId;
                        er.ordId = iter->base.ordId;
                        er.type =  TradeGateway::EtCanceled;
                        er.lastQty = -cancle;
                        er.lastPx = 0;
                        er.tradeDate = iter->base.date;
                        er.transactTime = Time().FormatString("hhnnss").ToInt();
                        db.add_trade(&er);
                    }

                    //ODS("ordvol=%d,trdvol=%d,oldtrdvol=%d,cancle=%d,leavesQty=%d",
                    //    ordvol,trdvol,oldtrdvol,cancle,iter->leavesQty);
                    if( iter->leavesQty>0 )
                    {
                        iter->ordStatus = TradeGateway::Working;
                        this->add_order(*iter);
                    }
                }
                else
                    ODS("查询委托返回多个记录,ordid=%s",req.QryCurCsn.OrderID) ;
                itf->FreeAnswer(ans);
            }
            else
            {
                ODS("查询委托号失败,ordid=%s",req.QryCurCsn.OrderID) ;
                iter->ordStatus = TradeGateway::Working;
                this->add_order(*iter);
            }
        }
        catch(...)
        {
            ODS("查询委托号失败,意外错误,ordid=%s",req.QryCurCsn.OrderID) ;
            iter->ordStatus = TradeGateway::Working;
            this->add_order(*iter);
        }
        itf->unlock();
	}
}
