//---------------------------------------------------------------------------


#pragma hdrstop

#include "uPriceFunc.h"
#include "uTrdItfImp.h"
#include "uDatabase.h"
#include <assert.h>

#define DEF_HEAD_LEN            9
#define INDEX(field,record,n)   (DEF_HEAD_LEN + field + record*field + n - 1)
#define DEF_ACK_OK              0
#define DEF_ACK_ERROR           -1
#define DEF_TIMEOUT             -100
#define DEF_INVALID_STOCKCODE   -101
#define DEF_OTHER_ERROR         -504
#define _SH                     "10"
#define _SZ                     "00"

unsigned char * KEY   = "SZKINGDOM";
const char * REQ_HEAD = "%%04d|%04d|%8s|KDGATEWAY1.0|%s|%s|%s|%s|%s|%s|%s|%s|";
const int  NEXT_FLAG  = 6;   // 后续包

class kdgtmm
{
private:
	typedef (*pfunc_KDGT_CRC)(unsigned char* lpinbuf, int nlen, unsigned char *lpoutcrccode);
	typedef (*pfunc_KDGT_Encrypt)(unsigned char *lpszkey, unsigned char* lpinbuf, int nlen, unsigned char *lpoutbuf);
	typedef (*pfunc_KDGT_Decrypt)(unsigned char *lpszkey, unsigned char* lpinbuf, int nlen, unsigned char *lpoutbuf);

	HMODULE h_kdgtmm;
	pfunc_KDGT_CRC FKDGT_CRC;
	pfunc_KDGT_Encrypt FKDGT_Encrypt;
	pfunc_KDGT_Decrypt FKDGT_Decrypt;
public:
	void KDGT_CRC(unsigned char* lpinbuf, int nlen, unsigned char *lpoutcrccode)
	{
		if( NULL !=FKDGT_CRC )
		{
			FKDGT_CRC(lpinbuf,  nlen, lpoutcrccode);
		}
	}

	void KDGT_Encrypt(unsigned char *lpszkey, unsigned char* lpinbuf, int nlen, unsigned char *lpoutbuf)
	{
		if( NULL != FKDGT_Encrypt)
		{
			FKDGT_Encrypt(lpszkey, lpinbuf,  nlen,lpoutbuf);
		}
	}

	void KDGT_Decrypt(unsigned char *lpszkey, unsigned char* lpinbuf, int nlen, unsigned char *lpoutbuf)
	{
		if( NULL != FKDGT_Decrypt )
		{
			FKDGT_Decrypt(lpszkey,  lpinbuf,  nlen, lpoutbuf);
        }
	}

	kdgtmm()
	{
		h_kdgtmm = LoadLibrary("KdGTmm.dll");
		if( NULL != h_kdgtmm )
		{
			FKDGT_CRC = (pfunc_KDGT_CRC)GetProcAddress(h_kdgtmm, "KDGT_CRC");
			FKDGT_Encrypt = (pfunc_KDGT_Encrypt)GetProcAddress(h_kdgtmm, "KDGT_Encrypt");
			FKDGT_Decrypt = (pfunc_KDGT_Decrypt)GetProcAddress(h_kdgtmm, "KDGT_Decrypt");
		}
	}

	~kdgtmm()
	{
    	if( NULL != h_kdgtmm )
		{
            FreeLibrary(h_kdgtmm);
        }
    }
};

kdgtmm g_kdgtmm;


AnsiString GetDate(void)
{
	return Now().FormatString("yyyy-mm-dd");
}

int DateTimeToInt(const UnicodeString &dt)
{
	String a = ReplaceStr( dt,"-","");
	String b = ReplaceStr( a,":","");
	return b.ToIntDef(0);
}

void ConvertDateTime( const UnicodeString &dt, long &date, long &time)
{
	//2010-09-28 21:02:37.089968

	String a = ReplaceStr(LeftStr(WideString(dt),10),"-","");
	String b = ReplaceStr(dt.SubString(12,8),":","");
	date= a.ToIntDef(0);
	time= b.ToIntDef(0);
}

AnsiString ReplaceCRC(const AnsiString cmd,const char* to)
{
	return cmd.SubString(1,10) + to + cmd.SubString(19,cmd.Length() - 18) ;//20051121---19==>18
}

AnsiString CRC(const AnsiString cmd)
{
	char szCRC[20];
	g_kdgtmm.KDGT_CRC( cmd.c_str(),cmd.Length(),szCRC);
	// 更新crc字段
	return ReplaceCRC( cmd, szCRC );
}

//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString TTrdItfImp::GenCMD( int data_size, AnsiString data )
{
	AnsiString cmd;
	cmd.printf(REQ_HEAD,data_size,FWorkKey,FUSER_CODE.c_str(),FZXSet.local_ip,FBRANCH.c_str(),
		FZXSet.entrust_way,FSESSION.c_str(),"","","" ) ;

	cmd.printf(AnsiString(cmd).c_str(),cmd.Length());
	cmd=cmd+data ;

	return CRC(cmd);
}

AnsiString TTrdItfImp::ReadNextData()
{
	AnsiString cmd = GenCMD( 3, "99|" );
	return ReadFirstData(cmd);
}

AnsiString TTrdItfImp::ReadFirstData(AnsiString cmd)
{
	try
	{
		if( FidTcp->Connected() !=true )
			throw ERR_REMOTE_OTHER_FAILED;
	}
	catch (Exception *e)
	{
		SetLastError(ERR_REMOTE_OTHER_FAILED,'E',PLUGINNAME,"券商柜台连接意外断开! 错误信息:%s.",
			AnsiString(e->Message).c_str());
		this->SetLogout();
		throw ERR_REMOTE_OTHER_FAILED;
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
        if( FZXSet.debug_mode )
            ODS(cmd.c_str());
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
        FidTcp->Socket->ReadBytes(da,4,true);
        strncpy(buf,(char*)&da[0],254);
        int nhead = atoi(buf);
        //0052|0000000368
        if( nhead <=15 )
        {
            SetLastError(ERR_REMOTE_RECV_FAILED,'E',PLUGINNAME,"券商柜台接收头数据失败! buf:%s.",buf);
            return IntToStr(ERR_REMOTE_RECV_FAILED) ;
        }

        //读数据体长度
        FidTcp->Socket->ReadBytes(da,nhead-4,true);
        strncpy(buf,((char*)&da[0])+5,254);
        for(int i=0;i<254;i++)
        {
            if( buf[i] == '|' )
            {
                buf[i]= 0;
                break;
            }
        }
        int ndata = atoi(buf);
        if( ndata > 0 )
        {
            FidTcp->Socket->ReadBytes(da,ndata,true);
        }

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
        throw ERR_REMOTE_RECV_FAILED  ;
    }
    AnsiString ret = (char*)&da[0];
    if( FZXSet.debug_mode )
        ODS(ret.c_str());
    return ret;
}

void SplitString(const char * Sour,int length,TStrings* strList,char DivSign)
{
	strList->Clear();
	long n= length;
	char field[1024];
	int j = 0;
	field[0] = '\0';
	for ( int i=0; i<n ;i++)
	{
		if( Sour[i] == DivSign ) //|| i == n-1 )
		{
			field[j] ='\0';
			strList->Add(Trim(AnsiString(field)));
			j=0;
			field[0] = '\0';
		}
		else
		{
			field[j++] = Sour[i];
        }
	}
}

int TTrdItfImp::SplitData(const std::string  &func,AnsiString SD, TStringList *lstDD,int &fieldcount,int &reccount)
{
	assert(lstDD != NULL);

	SplitString(SD.c_str(),SD.Length(),lstDD,'|');

	if (lstDD->Count < DEF_HEAD_LEN)
	{
		SetLastError(DEF_ACK_ERROR,'E',PLUGINNAME,"返回字段小于响应数据头字段数!");
		return DEF_ACK_ERROR;
	}

	if (lstDD->Strings[4] != "0")
	{
		SetLastError(DEF_ACK_ERROR,'E',PLUGINNAME,"请求号%s，返回码:%s,错误信息为%s",
            func.c_str(),
			AnsiString(lstDD->Strings[4]).c_str(),
			AnsiString(lstDD->Strings[5]).c_str());
		return DEF_ACK_ERROR;
	}

	reccount =  lstDD->Strings[8].ToIntDef(0);
	//if (lstDD->Count != lstDD->Strings[7].ToIntDef(0) * reccount)
	if(lstDD->Count-DEF_HEAD_LEN < lstDD->Strings[7].ToIntDef(0) * (1+reccount))//20051121---替代上一句
	{
		SetLastError(DEF_ACK_ERROR,'E',PLUGINNAME,"请求号%s，Count = %d,应答字段数=%s,应答记录数=%s",
            func.c_str(),
            lstDD->Count,
			AnsiString(lstDD->Strings[7]).c_str(),
            AnsiString(lstDD->Strings[8]).c_str());
		return DEF_ACK_ERROR;///
	}

	if( fieldcount > lstDD->Strings[7].ToIntDef(0) )
	{
		return DEF_ACK_ERROR;
	}

	fieldcount = lstDD->Strings[7].ToIntDef(0);

	return DEF_ACK_OK;
}


TTrdItfImp::TTrdItfImp(const char *psetupfile,ADDLOG plogfunc) :
	TTrdItfBase( psetupfile,  plogfunc)
{
	FidTcp = new TIdTCPClient(NULL);
	FWorkKey[0]= 0;
	_oldcount = ::GetTickCount();
	//FSessionOpened = false;
}

TTrdItfImp::~TTrdItfImp()
{
	CloseLink();
	delete FidTcp;
}

//初始化
int TTrdItfImp::Init()
{
	try
	{
		//if (!FidTcp->Connected())
		{
			FidTcp->Host = FZXSet.SvrIp;
			FidTcp->Port = FZXSet.SvrPort;
			FidTcp->Connect();

			AnsiString cmd;
			// 生成头
			cmd.printf(REQ_HEAD,4,"","",FZXSet.local_ip,"",FZXSet.entrust_way.c_str(),"","","","" ) ;
			cmd.printf( AnsiString(cmd).c_str(), cmd.Length()) ;
			// 加入数据
			cmd += "100|" ;

			//cmd = "0069|0005|ac82aefb|KDGATEWAY1.0|2247|00909627a566|103|3|00000000|2|||201||";
			// 发送
			TStringList *lstDD = new TStringList();
			try
			{
			int fcount = 1;
			int reccount = 0;
			if (SplitData("100",ReadFirstData(cmd), lstDD, fcount,reccount) == DEF_ACK_OK)
			{
				if (lstDD->Strings[INDEX(fcount,0,1)].Length() > 0)
				{
					AnsiString szTmp = lstDD->Strings[INDEX(fcount,0,1)];
					g_kdgtmm.KDGT_Decrypt( KEY,szTmp.c_str(),szTmp.Length(),FWorkKey);
					if(  strlen(FWorkKey) != 8 )
					{
                        ODS('E',PLUGINNAME,"获取KEY失败");
                    }
                    else
                        ODS('E',PLUGINNAME,"WORKKEY=%s",FWorkKey);
				}
			}
			}
			__finally
			{
				delete lstDD;
            }
		}
	}
	catch (...)
	{
		ODS('E',PLUGINNAME,"连接柜台失败!");
	}

	return (strlen(FWorkKey) == 8) ? 0 : -1;
}

//设置帐号
int TTrdItfImp::SetAccount(bool useOldSession)
{
    //0052|0000000234|447baac6|KDGATEWAY1.0|0|成功|0|10|2|MARKET|SECU_ACC|SECU_ACC_NAME|ACCOUNT|USER_CODE|USER_NAME|BRANCH|SESSION|EXT_INST|EXT_INST_NAME|00|0117677643|张宜君|85804549|18510106|张宜君|8070|716491555637442|||10|A608435548|张宜君|85804549|18510106|张宜君|8070|716491555637442|||
	AnsiString cmd;
	TStringList *lstDD = new TStringList();
    try
    {
	try
	{
		AnsiString USER_ID_CLS;

		if( useOldSession)
		{
            memcpy(&FRequest,&FSetAccRequest,sizeof(FRequest));
        }

		if(FRequest.SetAccount.LoginType == asCA)
		{
			USER_ID_CLS="Z";
		}
		else if(FRequest.SetAccount.LoginType==asSHA)
		{
			USER_ID_CLS=_SH;
		}
		else if(FRequest.SetAccount.LoginType==asSZA)
		{
			USER_ID_CLS=_SZ;
		}
		else
			return -1;

		char szEPwd[100];
		g_kdgtmm.KDGT_Encrypt(/*KEY*/FWorkKey,FRequest.SetAccount.PW,strlen(FRequest.SetAccount.PW),
			szEPwd);//20051121---KEY==>FWorkKey

		AnsiString data;
		data.printf( "301|%2s|%s|%s|",USER_ID_CLS , FRequest.SetAccount.Account,szEPwd) ;

		cmd.printf(REQ_HEAD,data.Length(),FWorkKey,"",FZXSet.local_ip,"",FZXSet.entrust_way,"","","","" ) ;
		cmd.printf(AnsiString(cmd).c_str(),cmd.Length()) ;
		cmd+= data;

		cmd = CRC(cmd);

		int fcount = 10;
		int reccount = 0;

		if (SplitData("301",ReadFirstData(cmd), lstDD, fcount, reccount) == DEF_ACK_OK)
		{
			strncpy(FAccInfo.Capital, AnsiString(lstDD->Strings[INDEX(fcount,0,4)]).c_str(), ACC_LEN);
			strncpy(FAccInfo.PW, FRequest.SetAccount.PW, PWD_LEN);

			FUSER_CODE = lstDD->Strings[INDEX(fcount,0,5)] ;
			FBRANCH    = lstDD->Strings[INDEX(fcount,0,7)] ;
			FSESSION   = lstDD->Strings[INDEX(fcount,0,8)] ;

			goto next;
			while (lstDD->Strings[NEXT_FLAG]=="1")
			{
				if (SplitData("99",ReadNextData(), lstDD, fcount, reccount) == DEF_ACK_OK)
				{
next:
					for( int i = 0; i<reccount; i++ )
					{
						if(  lstDD->Strings[INDEX(fcount,i,1)] == _SH )
						{
							//lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,13);
							//#ifdef _DEBUG//20051121---用下面替代上面?
							lstrcpyn(FAccInfo.SH, AnsiString(lstDD->Strings[INDEX(fcount,i,2)]).c_str(), ACC_LEN);
							//#endif
						}
						else if ( lstDD->Strings[INDEX(fcount,i,1)] == _SZ  )
						{
							//lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,13);
							//#ifdef _DEBUG//20051121---用下面替代上面?
							lstrcpyn(FAccInfo.SZ, AnsiString(lstDD->Strings[INDEX(fcount,i,2)]).c_str(), ACC_LEN);
							//#endif

						}
					}
				}
			}


			if(FRequest.SetAccount.LoginType==asSHA)
			{
				lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,ACC_LEN);
			}
			else if(FRequest.SetAccount.LoginType==asSZA)
			{
				lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,ACC_LEN);
			}

			if(FAccInfo.SH[0]==0 && FAccInfo.SZ[0]==0) { return -1; }

			NewAns(1);
			memcpy(&((*FAnswer)[0].SetAccount.AccountInfo), &FAccInfo, sizeof(TAccountInfo));
			order_man.load_working_orders(this->FAccInfo.Capital);
			//FSessionOpened = true;
		}
		else
		{
			return -1;
		}


	}
	__finally
	{
		delete lstDD;
	}
    }
    catch( const int err)
    {
        return err;
    }
	return 0;
}

bool TTrdItfImp::SessionAutoOpen(void)
{
	if( this->Init()==0 )
	{
		FRequest.SetAccount.LoginType = asCA;
		lstrcpyn(FRequest.SetAccount.Account,FAccInfo.Capital,sizeof(FRequest.SetAccount.Account));
		lstrcpyn(FRequest.SetAccount.PW,FAccInfo.PW,sizeof(FRequest.SetAccount.PW));
		if( SetAccount()==0 )
			return true;
		else return false;
	}
	else return false;
}

//资金查询
/*查询资金余额和可用资金余额
功能代码	502
功能描述	资金查询
请求数据	域名称	标识	类型及长度	必要	描述
	客户代码	USER_CODE	INT	Y
	资产账号	ACCOUNT	VARCHAR(20)       	N
	货币	CURRENCY	CHAR(1)	N
返回数据	域名称	标识	类型及长度	描述
	客户代码	USER_CODE	INT
	资产账户	ACCOUNT	VARCHAR(20)
	分支机构	BRANCH	INT
	货币	CURRENCY	CHAR(1)            0:人民币，1:港币，2:美元
	资金余额	BALANCE	DECIMAL(16,2)
	资金可用金额	AVAILABLE	DECIMAL(16,2)
	异常冻结金额	FROZEN	DECIMAL(16,2)
	交易冻结金额	TRD_FRZ	DECIMAL(16,2)
	可提现金金额	DRAW_AVL_CASH	DECIMAL(16,2)
	可提支票金额	DRAW_AVL_CHEQUE	DECIMAL(16,2)
	可转账金额	TRANSFER_AVL	DECIMAL(16,2)
	在途资金金额	OUTSTANDING	DECIMAL(16,2)	2004-7-22增加以下 6个字段
	在途可用金额	OTD_AVL	DECIMAL(16,2)
	债权金额	CR_AMT	DECIMAL(16,2)
	负债金额	DR_AMT	DECIMAL(16,2)
	利息	INTEREST	DECIMAL(16,2)
	利息税	INT_TAX	DECIMAL(16,2)
错误描述	错误代码	错误信息
	306	用户代码不存在
	305	资产帐号不存在
	501	无查询结果
	502	查询失败
备注信息

*/
int TTrdItfImp::QryMoney()
{
	AnsiString data;
	data.printf("502|%s|%s|%s|", FUSER_CODE.c_str() ,
	this->FAccInfo.Capital,
		FZXSet.money_type.c_str());

	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
    try
    {
	try
	{
		int fcount = 20;
		int reccount = 0;
		if (SplitData("502",ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			NewAns(1);
			(*FAnswer)[0].QryMoney.MoneyInfo.MoneyType =  motRMB;
			(*FAnswer)[0].QryMoney.MoneyInfo.balance = StrToFloatDef(lstDD->Strings[INDEX(fcount,0,20)] ,0);
			(*FAnswer)[0].QryMoney.MoneyInfo.available = StrToFloatDef(lstDD->Strings[INDEX(fcount,0,6)],0);
		}
		else
		{
			return -1;
		}
	}
	__finally
	{
		delete lstDD;
	}
    }
    catch(const int err)
    {
        return err;
    }

	return 0;
}

//当日委托查询
/*
功能代码	505
功能描述	委托查询
请求数据	域名称	标识	类型及长度	必要	描述
	起始日期	BEGIN_DATE	CHAR(10)	Y	1
	终止日期	END_DATE	CHAR(10)	Y	2
	查询委托模式	GET_ORDERS_MODE	CHAR(1)	Y	3
	客户代码	USER_CODE	INT	Y	4
	交易市场	MARKET	CHAR(2)        	N	5
	股东代码	SECU_ACC	VARCHAR(10)    	N	6
	证券代码	SECU_CODE	VARCHAR（8）	N	7
	交易行为	TRD_ID	CHAR(2)        	N	8
	业务序号	BIZ_NO	VARCHAR(10)    	N	9
	合同序号	ORDER_ID	VARCHAR(10)	N	10
	分支机构	BRANCH	INT   	N
	资产账户	ACCOUNT	VARCHAR(20)	N
	外部机构	EXT_INST	INT	N	三方交易时送
返回数据	域名称	标识	类型及长度	描述
	1委托日期	ORDER_DATE	CHAR(10)
	2交易日期	TRD_DATE	CHAR(10)
	3客户代码	USER_CODE	VARCHAR(20)
	客户姓名	USER_NAME	VARCHAR(16)	删除20031228
	4资产账户	ACCOUNT	VARCHAR(20)
	5货币	CURRENCY	CHAR(1)
	6分支机构	BRANCH	INT
	7股东代码	SECU_ACC	VARCHAR(10)
	8股东姓名	SECU_NAME	VARCHAR(16)	增加20031228
	9交易行为	TRD_ID	CHAR(2)
	10业务序号	BIZ_NO	VARCHAR(10)
	11合同序号	ORDER_ID	VARCHAR(10)
	12交易市场	MARKET	CHAR(2)
	13证券名称	SECU_NAME	VARCHAR(16)
	14证券代码	SECU_CODE	VARCHAR(8)
	交易席位	SEAT	VARCHAR(6)	删除20031228
	15价格	PRICE	DECIMAL(10,3)
	16数量	QTY	INT
	17委托金额	ORDER_AMT	DECIMAL(16,2)
	18委托冻结金额	ORDER_FRZ_AMT	DECIMAL(16,2)
	资金可用金额	AVAILABLE	DECIMAL(16,2)	删除20031228
	股份可用	SHARE_AVL	INT	删除20031228
	19撤单标志	IS_WITHDRAW	CHAR(1)
	20已撤单标志	IS_WITHDRAWN	CHAR(1)
	21可撤单标志	CAN_WITHDRAW	CHAR(1)	删除2003122 恢复该字段20040101
	22发送标志	DCL_FLAG	CHAR(1)
	报盘时间	DCL_TIME	CHAR(8)	删除20031228
	23合法标志	VALID_FLAG	CHAR(1)
	24成交数量	MATCHED_QTY	INT
	25已撤单数量	WITHDRAWN_QTY	INT
	26成交金额	MATCHED_AMT	DECIMAL(16,2)
	实时清算金额	RLT_SETT_AMT	DECIMAL(16,2)	删除20031228
	27操作备注	OP_REMARK	VARCHAR(64)
	发起方	INITIATOR	CHAR(1)	删除20031228
	28外部机构	EXT_INST	SMALLINT
	外部账户	EXT_ACC	VARCHAR(32)	删除20031228
	外部子账户	EXT_SUB_ACC	VARCHAR(32)	删除20031228
	外部冻结金额	EXT_FRZ_AMT	DECIMAL(16,2)	删除20031228
	29外部记录号	EXT_REC_NUM	INT
	已清算外部资金	EXT_SETT_AMT	DECIMAL(16,2)	删除20031228
	30外部业务号	EXT_BIZ_NO	VARCHAR(10)	增加20031228
	31外部合同号	EXT_ORDER_ID	VARCHAR(10)	增加20031228

错误描述	错误代码	错误信息
	306	用户代码不存在
	501	无查询结果
	502	查询失败
备注信息		发起方              <I>:券商发起<O>:外部机构发起,<A>:双方发起
	查询委托模式		<0>:所有委托，<1>:可撤委托，<2>:非法委托
	撤单标志			<0>:正常委托，<1>:撤单委托
	已撤单标志			<0>:未撤单，<1>:已撤单
	可撤单标志			<0>:不允许撤单，<1>:允许撤单
	发送标志			<0>:未发送，<1>:已发送
	报盘时间			格式：HH:MM:SS
	合法标志			<0>:合法，<1>:非法
送证券代码必须送交易市场


*/

market_type convert_market( TradeGateway::MarketIdSource ms )
{
    market_type ret = mtNo;
    switch( ms )
    {
    case TradeGateway::SSE:
        ret = mtSHA;
        break;
    case TradeGateway::SZSE:
        ret = mtSZA;
        break;
    case TradeGateway::SHFE:
        ret = mtFSH;
        break;
    case TradeGateway::DCE:
        ret = mtFZZ;
        break;
    case TradeGateway::CZCE:
        ret = mtFDL;
        break;
    case TradeGateway::CFFEX:
        ret = mtJJS;
        break;
    case TradeGateway::HKEX:
        ret = mtHK;
        break;
    case TradeGateway::MktUnknow:
        ret = mtNo;
        break;
    }
    return ret;
}


int TTrdItfImp::QryCurCsn()
{
	if(FRequest.QryCurCsn.OrderID[0]==0)
	{
		//增量查询
		database db;
		TradeGateway::OrderReportSeq list;
		try
		{
			db.qry_orders(this->FAccInfo.Capital,FRequest.QryCurCsn.SeqNum,
				FRequest.QryCurCsn.MaxRecord,
				Date().FormatString("yyyymmdd").ToInt(),list);

			if( list.size()==0 ) return 0;
			NewAns(list.size());
			for( size_t i=0;i<list.size();i++)
			{
                TOrderInfo &poi = (*FAnswer)[i].QryCurCsn.OrderInfo;
                TradeGateway::OrderReport &or = list[i];
                strncpy(poi.Account,or.base.accountId.c_str(),ACC_LEN);
                if( or.ordStatus == TradeGateway::Canceled ||
                    or.ordStatus == TradeGateway::Filled ||
                    or.ordStatus == TradeGateway::DoneForDay ||
                    or.ordStatus == TradeGateway::Canceled ||
                    or.ordStatus == TradeGateway::Stopped ||
                    or.ordStatus == TradeGateway::Rejected)
                    poi.CancelVol = or.cumQty-or.base.ordQty;
                strncpy(poi.ContractID, or.base.ordId.c_str(),SEQ_LEN);
                poi.CsnPrice = or.base.lmtPrice;
                poi.CsnVol = or.base.ordQty;
                poi.Date = or.base.date;
                poi.Market = convert_market(or.base.inst.securityIDSource);
                strncpy(poi.SecuID,or.base.inst.securityID.c_str(),CODE_LEN);
                strncpy(poi.SeqNum,or.seq.c_str(),SEQ_LEN);
                switch( or.ordStatus )
                {
                case TradeGateway::New:
                    poi.State = oswb;
                    break;
                case TradeGateway::PendingNew:
                    poi.State = osyb;
                    break;
                case TradeGateway::Working:
                    poi.State = osbc;
                    break;
                case TradeGateway::PendingCancel:
                    poi.State = osdc;
                    break;
                case TradeGateway::Filled:
                    poi.State = oscj;
                    break;
                case TradeGateway::DoneForDay:
                    poi.State;
                    break;
                case TradeGateway::Canceled:
                    if( abs(poi.CancelVol)==poi.CsnVol )
                        poi.State = osyc;
                    else
                        poi.State = osbw;
                    break;
                case TradeGateway::Stopped:
                    poi.State =  osyf;
                    break;
                case TradeGateway::Rejected:
                    poi.State = osyf;
                    break;
                case TradeGateway::OrdStatusUnknow:
                    poi.State =osno;
                    break;
                default:
                    poi.State =osno;
                }

                poi.Time = or.base.time;
                poi.TrdPrice = or.avgPx;
                poi.TrdVol = or.cumQty;

                if( or.base.s == TradeGateway::Buy )
                {
                    if( or.base.posEfct == TradeGateway::Open )
                        poi.Type = otOpenBuy;
                    else if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otCloseBuy;
                    }
                    else if( or.base.posEfct == TradeGateway::CloseToday )
                    {
                        poi.Type =otCloseTodayBuy;
                    }
                    //else if( or.base.posEfct == TradeGateway::CloseYesterday )
                    //{
                    //	poi.Type =otCloseBuy;
                    //}
                    else
                        poi.Type = otBuy;
                }
                else if( or.base.s == TradeGateway::Sell )
                {
                    if( or.base.posEfct == TradeGateway::Open )
                        poi.Type = otOpenSell;
                    else if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otCloseSell;
                    }
                    else if( or.base.posEfct == TradeGateway::CloseToday )
                    {
                        poi.Type =otCloseTodaySell;
                    }
                    //else if( or.base.posEfct == TradeGateway::CloseYesterday )
                    //{
                    //	poi.Type =otCloseSell;
                    //}
                    else
                        poi.Type = otSell;
                }
				else if(or.base.s == TradeGateway::Subscribe)
                {
                    poi.Type = otETFSub;
                }
				else if(or.base.s == TradeGateway::Redeem)
                {
                    poi.Type = otETFRed;
                }
				else if(or.base.s == TradeGateway::Lend)
                {
                    if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otSellRepay;
                    }
                    else
                        poi.Type = otLoanBuy;
                }
                else if(or.base.s == TradeGateway::Borrow)
                {
                    if( or.base.posEfct == TradeGateway::Close )
                    {
                        poi.Type =otBuyRepay;
                    }
                    else
                        poi.Type = otLoanSell;
                }
            }
		}
		catch( std::string &err)
		{
			SetLastError(-1,'E',PLUGINNAME,err.c_str());
			return -1;
        }
	}
	else
	{
        /*
        0077|0056|d72a3cef|KDGATEWAY1.0|18510106|127.0.0.1|8070|4|716491555637442||||505|2010-09-28|2010-09-28|0|18510106|  ||||17053533|||||
        0052|0000000527|73889bbf|KDGATEWAY1.0|0|成功|0|33|1|ORDER_DATE|TRD_DATE|USER_CODE|ACCOUNT|CURRENCY|BRANCH|SECU_ACC|SECU_ACC_NAME|TRD_ID|BIZ_NO|ORDER_ID|MARKET|SECU_NAME|SECU_CODE|PRICE|QTY|ORDER_AMT|ORDER_FRZ_AMT|IS_WITHDRAW|IS_WITHDRAWN|DCL_FLAG|VALID_FLAG|MATCHED_QTY|CAN_WITHDRAW|MATCHED_AMT|EXT_REC_NUM|EXT_INST|EXT_BIZ_NO|EXT_ORDER_ID|INITIATOR|OP_REMARK|WITHDRAWN_QTY|MATCHED_PRICE|2010-09-28 17:13:54.822017|2010-09-28|18510106|85804549|0|8070|A608435548|张宜君|0B|17053533|17053533|10|中国南车|601766|1.000|100|100.00|106.10|0|0|1|1|100|0|100.00|0|0|||I|委托合法|0|1.000|

        */
		AnsiString data;
		AnsiString date = GetDate();

		//data.printf("505|%10s|%10s|0|%s|%2s|||||%s||||",date.c_str(),date.c_str(),
		//	FUSER_CODE ,market,
		//	FRequest.QryDetail.ContractID);
		//#ifdef _DEBUG//20051122---注:金证马庆海提示将合同号放在第9字段,文档上是第10字段
		data.printf("505|%10s|%10s|0|%s|%2s||||%s|||||",date.c_str(),date.c_str(),
			FUSER_CODE.c_str() ,"",
			FRequest.QryCurCsn.OrderID);
		//#endif

		AnsiString cmd = GenCMD( data.Length(), data  );

		TStringList *lstDD = new TStringList();
        try
        {
		try
		{
			int fcount = 33;
			int reccount = 0;
			if (SplitData("505",ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
			{
				goto ADD;
				while (lstDD->Strings[NEXT_FLAG]=="1")
				{
					if (SplitData("99",ReadNextData(), lstDD,  fcount,reccount) == DEF_ACK_OK)
					{
ADD:
						for( int i=0; i<reccount; i++ )
						{
							if(  lstDD->Strings[INDEX(fcount,i,19)] == L"0")
							{
                            	NewAns(1);
								strncpy((*FAnswer)[0].QryCurCsn.OrderInfo.ContractID,
									AnsiString(lstDD->Strings[INDEX(fcount,i,11)]).c_str(),SEQ_LEN);
								strncpy((*FAnswer)[0].QryCurCsn.OrderInfo.SecuID,
									AnsiString(lstDD->Strings[INDEX(fcount,i,14)]).c_str(), CODE_LEN);
								(*FAnswer)[0].QryCurCsn.OrderInfo.Market =
									ConvertMarketType(AnsiString(lstDD->Strings[INDEX(fcount,i,12)]).c_str());

								ConvertDateTime(lstDD->Strings[INDEX(fcount,i,1)],
											(*FAnswer)[0].QryCurCsn.OrderInfo.Date,
											(*FAnswer)[0].QryCurCsn.OrderInfo.Time );
								//(*FAnswer)[0].QryCurCsn.OrderInfo.Time =DateTimeToInt(lstDD->Strings[INDEX(fcount,i,1)]);
								//(*FAnswer)[0].QryCurCsn.OrderInfo.Date =DateTimeToInt(lstDD->Strings[INDEX(fcount,i,1)]);
								(*FAnswer)[0].QryCurCsn.OrderInfo.Type =ConvertOrderType(AnsiString(lstDD->Strings[INDEX(fcount,i,9)]).c_str());

								(*FAnswer)[0].QryCurCsn.OrderInfo.CsnVol=lstDD->Strings[INDEX(fcount,i,16)].ToIntDef(0);
								(*FAnswer)[0].QryCurCsn.OrderInfo.TrdVol =lstDD->Strings[INDEX(fcount,i,23)].ToIntDef(0);
								(*FAnswer)[0].QryCurCsn.OrderInfo.CancelVol=lstDD->Strings[INDEX(fcount,i,32)].ToIntDef(0);;
								(*FAnswer)[0].QryCurCsn.OrderInfo.CsnPrice=StrToFloatDef(lstDD->Strings[INDEX(fcount,i,15)],0);
								//if((*FAnswer)[0].QryCurCsn.OrderInfo.TrdVol>0)
								//	(*FAnswer)[0].QryCurCsn.OrderInfo.TrdPrice=StrToFloatDef(lstDD->Strings[INDEX(fcount,i,26)],0)/
								//		(*FAnswer)[0].QryCurCsn.OrderInfo.TrdVol;
								//else
								//    (*FAnswer)[0].QryCurCsn.OrderInfo.TrdPrice=0;
								(*FAnswer)[0].QryCurCsn.OrderInfo.TrdPrice= StrToFloatDef(lstDD->Strings[INDEX(fcount,i,33)],0);

								strncpy((*FAnswer)[0].QryCurCsn.OrderInfo.Account,AnsiString(lstDD->Strings[INDEX(fcount,i,7)]).c_str(),ACC_LEN);
								strncpy((*FAnswer)[0].QryCurCsn.OrderInfo.SeqNum,AnsiString(lstDD->Strings[INDEX(fcount,i,10)]).c_str(),SEQ_LEN);

								if( ((*FAnswer)[0].QryCurCsn.OrderInfo.CsnVol== ((*FAnswer)[0].QryCurCsn.OrderInfo.TrdVol +abs((*FAnswer)[0].QryCurCsn.OrderInfo.CancelVol))) &&
                                    (*FAnswer)[0].QryCurCsn.OrderInfo.CancelVol>0 &&
                                    (*FAnswer)[0].QryCurCsn.OrderInfo.TrdVol>0 )
									(*FAnswer)[0].QryCurCsn.OrderInfo.State= osbw;
								else if((*FAnswer)[0].QryCurCsn.OrderInfo.CsnVol== ((*FAnswer)[0].QryCurCsn.OrderInfo.TrdVol))
									(*FAnswer)[0].QryCurCsn.OrderInfo.State=oscj;
								else if( (*FAnswer)[0].QryCurCsn.OrderInfo.CsnVol== abs((*FAnswer)[0].QryCurCsn.OrderInfo.CancelVol))
									(*FAnswer)[0].QryCurCsn.OrderInfo.State=osyc;
								else if( ((*FAnswer)[0].QryCurCsn.OrderInfo.TrdVol>0 ))
									(*FAnswer)[0].QryCurCsn.OrderInfo.State=osbc;
								else (*FAnswer)[0].QryCurCsn.OrderInfo.State=osyb ;
                            }
						}
					}
				}
			}
			else
			{
				return -1;
			}
		}
		__finally
		{
			delete lstDD;
		}
        }
        catch(const int err)
        {
            return err;
        }
	}
	return 0;
}

//当日成交查询
int TTrdItfImp::QryCurTrd()
{
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

}

//查询帐号中所有的股份
/*
功能代码	504
功能描述	股份查询
请求数据	域名称	标识	类型及长度	必要	描述
	客户代码	USER_CODE	INT	Y
	资产账户	ACCOUNT	VARCHAR(20)   	N
	交易市场	MARKET	CHAR(2)       	N
	股东代码	SECU_ACC	VARCHAR(10)   	N
	证券代码	SECU_CODE	VARCHAR（8）	N
	外部机构	EXT_INST	INT	N	三方交易时送
返回数据	域名称	标识	类型及长度	描述
	1客户代码	USER_CODE	INT
	2资产账户	ACCOUNT	VARCHAR(20)
	3交易市场	MARKET	CHAR(2)
	4股东代码	SECU_ACC	VARCHAR(10)
	5证券名称	SECU_NAME	VARCHAR(16)
	6证券代码	SECU_CODE 	VARCHAR(8)
	7证券内码	SECU_INTL 	INT
	8交易席位	SEAT	VARCHAR(6)
	9分支机构	BRANCH	INT
	10外部机构	EXT_INST	INT
	11货币	CURRENCY	CHAR(1)
	12股份余额	SHARE_BLN	INT
	13股份可用	SHARE_AVL	INT
	14股份交易冻结数	SHARE_TRD_FRZ	INT
	15股份在途数量	SHARE_OTD	INT
	16股份异常冻结数	SHARE_FRZ	INT
	17股份非流通数量	SHARE_UNTRADE_QTY	INT
	18当前成本	CURRENT_COST	DECIMAL(16,2)
	19市值	MKT_VAL	DECIMAL(16,2)	补充：第三方计算2004-6-29
	20持仓成本价	COST_PRICE
	21股份在途可用数量	SHARE_OTD_AVL	INT
	22市价	CURR_PRICE	DECIMAL(16,3)	2004-7-22 增加
	23买入成本价	COST2_PRICE		2004-7-22 增加
	24当前拥股	MKT_QTY	INT	2004-7-22 增加
错误描述	错误代码	错误信息
	306	用户代码不存在
	501	无查询结果
	502	查询失败
备注信息	送证券代码必须送交易市场
*/
int TTrdItfImp::QryStocks()
{
	TList * lstAns = new TList();
	TStringList *lstDD = new TStringList();

	AnsiString market= this->ConvertMarketType(FRequest.QryStocks.Market);

	AnsiString data;

	if(  FRequest.QryStocks.Market == mtSHA )
		data.printf("504|%s||%2s|%s|||",FUSER_CODE.c_str() ,market.c_str(),this->FAccInfo.SH);//20051122---"504|%s|%s|%2s|%s|||"==>"504|%s||%s|%s|||"
	else if( FRequest.QryStocks.Market == mtSZA )
		data.printf("504|%s||%2s|%s|||",FUSER_CODE.c_str() ,market.c_str(),this->FAccInfo.SZ);//20051122---"504|%s|%s|%2s|%s|||"==>"504|%s||%s|%s|||"
	else
		data.printf("504|%s||||||",FUSER_CODE.c_str());//20051122---"504|%s|%s|%s|||||"==>"504|%s||%s|%s|||"


	AnsiString cmd = GenCMD( data.Length(), data  );

	AnsiString retMarket;
    try
    {
	try
	{
		int fcount = 25;
		int reccount = 0;
		if (SplitData("504",ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			goto ADD;
			while (lstDD->Strings[NEXT_FLAG]=="1")
			{
				if (SplitData("99",ReadNextData(), lstDD,  fcount,reccount) == DEF_ACK_OK)
				{
ADD:
					for( int i=0; i<reccount; i++ )
					{
						TStockInfo *si = new TStockInfo;
						memset(si, 0, sizeof(TStockInfo));

						retMarket = lstDD->Strings[INDEX(fcount,i,3)]  ;


						strncpy(si->Account, AnsiString(lstDD->Strings[INDEX(fcount,i,4)]).c_str(), ACC_LEN);
						strncpy(si->SecuID , AnsiString(lstDD->Strings[INDEX(fcount,i,6)]).c_str(), CODE_LEN);
						si->Market = this->ConvertMarketType(AnsiString(lstDD->Strings[INDEX(fcount,i,3)]).c_str());
						si->Balance       = lstDD->Strings[INDEX(fcount,i,12)].ToIntDef(0);//20051122---11==>12
						si->Available     = lstDD->Strings[INDEX(fcount,i,13)].ToIntDef(0);//20051122---12==>13
						si->PosDir = pdNet;
						si->PosNum =        lstDD->Strings[INDEX(fcount,i,24)].ToIntDef(0);
						si->CostPrice     = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,20)], 0);

						si->CurPrice      = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,22)], 0);
						lstAns->Add(si);
					}
				}
			}

			if (lstAns->Count > 0)
			{
				NewAns(lstAns->Count);
				for ( int i = 0; i < lstAns->Count; i++ )
				{
					TStockInfo *ci = (TStockInfo *)lstAns->Items[i];
					memcpy(&(*FAnswer)[i].QryStocks.StockInfo, ci, sizeof(TStockInfo));
				}
			}

			for ( int i = 0; i < lstAns->Count; i++ )
			{
				TStockInfo *ci = (TStockInfo *)lstAns->Items[i];
				delete ci;
			}
			lstAns->Clear();
		}
		else
		{
			return lstDD->Strings[5].ToIntDef(DEF_OTHER_ERROR);
		}
	}
	__finally
	{
		delete lstDD;
		delete lstAns;
	}
    }
    catch(const int err)
    {
        return err;
    }

	return 0;
}

//委托撤单
/*
功能代码	403
功能描述	委托买卖业务,支持三方交易
请求数据	域名称	标识	类型及长度	必要	描述
	客户代码	USER_CODE	INT	Y
	交易市场	MARKET	CHAR(2)	Y
	股东代码	SECU_ACC	VARCHAR(10)	Y
	资产账户	ACCOUNT	VARCHAR(20)        	N
	交易席位	SEAT	VARCHAR(6)         	N
	证券代码	SECU_CODE	VARCHAR（8）	Y
	交易行为	TRD_ID	CHAR(2)	Y	交易行为定义
	价格	PRICE	DECIMAL(10,3)	Y
	数量	QTY	INT	Y
	业务序号	BIZ_NO	VARCHAR(10)	N
	外部机构	EXT_INST	INT	N	三方交易时送
	外部记录号	EXT_REC_NUM	INT	N
	备注信息	OP_REMARK	VARCHAR(20)	N
	对手席位	MATCH_SEAT	VARCHAR(6)         	N	三板报价
	约定号	MATCH_NUM	INT	N	三板报价
返回数据	域名称	标识	类型及长度	描述
	业务序号	BIZ_NO	VARCHAR(10)
	合同序号	ORDER_ID	VARCHAR(10)
	资产账户	ACCOUNT	VARCHAR(20)
	价格	PRICE	DECIMAL(10,3)
	数量	QTY	INT
	委托金额	ORDER_AMT	DECIMAL(16,2)
	委托冻结金额	ORDER_FRZ_AMT	DECIMAL(16,2)
	交易席位	SEAT	VARCHAR(6)
	外部机构	EXT_INST	INT
	外部账户	EXT_ACC	VARCHAR(32)
	外部子账户	EXT_SUB_ACC	VARCHAR(32)
	外部冻结金额	EXT_FRZ_AMT	DECIMAL(16,2)
错误描述	错误代码	错误信息
	304	股东代码不存在
	306	用户代码不存在
	402	您未作指定交易
	403	此股不能进行此类委托
	311	外部机构不存在
	404	委托失败
备注信息		如果进行批量委托，则将第一笔委托的合同序号作为第二笔以后委托的业务序号
	交易席位 : 卖出时送
	资产账户为可选项,可以用不同的资产帐户作委托,不送时用股东的缺省帐户
	交易行为包括:
	0B     买入
	0B     买入
	0S     卖出
	2B     即时成交剩撤买
	2S     即时成交剩撤卖
	3S     转托管
	4B     配股缴款
	4C     认购行权
	4M     权证创设
	4N     权证注销
	4P     认沽行权
	5S     转债转股
	6S     转债回售
	7B     新股申购
	7D     新股配售
	7H     新股增发
	7J     基金认购
	7K     ETF申购
	7L     ETF赎回
	7M     基金申购
	7N     基金赎回
	7O     基金分红方式
	7P     网下现金认购    (SEND_TO_EXCH:需要配置成0)
	7Q     网下股票认购    (SEND_TO_EXCH:需要配置成0)
	7S     承销卖出
	8B     配售缴款
	8C     放弃配售
	8S     主动放弃配售
	8X     放弃配售撤销
	9B     融资回购
	9D     融资购回
	9E     买断融资
	9F     买断资回
	9G     买断融券
	9H     买断券回
	9M     质押债券入库
	9N     质押债券出库
	9S     融券回购

		9S     融券回购
	9T     融券购回
	ES     预受要约
	FS     解除预受要约
	UB     最优成交转价买
	US     最优成交转价卖
	VB     最优成交剩撤买
	VS     最优成交剩撤卖
	WB     全成交或撤销买
	WS     全成交或撤销卖
	XB     本方最优价格买
	XS     本方最优价格卖
	YB     对手最优价格买
	YS     对手最优价格卖
	Z0     指定交易
	Z1     撤销指定
	Z2     回购指定
	Z3     回购撤指
三板报价交易行为
	HB:意向买入
	HS:意向卖出
	OB:定价买入
	OS:定价卖出
	1B:成交确认买入
	1S:成交确认卖出
三板报价需要填对方席位和约定号
--------------------20100320新增加基金盘后业务支持----------
	7R   基金分拆
	7T   基金合并
	7U   基金转换

如果MID没开行情,会报此股票不存在

*/
int TTrdItfImp::Order()
{
	AnsiString market = this->ConvertMarketType(FRequest.Order.Market);
	AnsiString data;
	AnsiString acc;

	acc = this->GetStockAccountByMarket(FRequest.Order.Market) ;

	AnsiString sPrice;
	if( AnsiPos(AnsiString("510"),FRequest.Order.SecuID ) == 1 ||
		AnsiPos(AnsiString("1599"),FRequest.Order.SecuID ) == 1 )
	{
		sPrice  = ConvetDoubleToPrice( FRequest.Order.Price,3);
		//ODS("%s,%s",FRequest.Order.SecuID,sPrice.c_str());
	}
	else
	{
		sPrice  = ConvetDoubleToPrice( FRequest.Order.Price,2);
		//ODS("%s,%s",FRequest.Order.SecuID,sPrice.c_str());
	}
	data.printf("403|%s|%2s|%s|||%s|%2s|%s|%d||||",FUSER_CODE.c_str() ,market,acc.c_str(),
			FRequest.Order.SecuID, ConvertOrderType(FRequest.Order.Type),
			sPrice.c_str(),FRequest.Order.Num);

	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
    try
    {
	try
	{
		int fcount = 12;
		int reccount = 0;
		if (SplitData("403",ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			NewAns(1);
			strncpy((*FAnswer)[0].Order.ContractID,
				AnsiString(lstDD->Strings[INDEX(fcount,0,2)]).c_str(), SEQ_LEN);
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
		else
		{
			return -1;
		}
	}
	__finally
	{
		delete lstDD;
	}
    }
    catch( const int err)
	{
        return err;
    }
	return 0;
}

int TTrdItfImp::Undo()
{

	AnsiString market=this->ConvertMarketType(FRequest.Undo.Market);

    if( market.Length()== 0)
    {
        database db;
        TradeGateway::OrderReport ord ;
        try
        {
            db.qry_order_by_ordid(this->FAccInfo.Capital,FRequest.Undo.ContractID,
                Date().FormatString("yyyymmdd").ToInt(),ord);
        }
        catch( std::string &err)
        {
            SetLastError(-1,'E',PLUGINNAME,"查询委托从本地数据库失败:%s",err.c_str());
            return -1;
        }
        switch (ord.base.inst.securityIDSource) {
            case TradeGateway::SSE:
                market = _SH;
            break;
            case TradeGateway::SZSE:
                market = _SZ;
            break;
        default:
            ;
        }
    }

	AnsiString data;
	data.printf("404|%2s|%s",market.c_str(),FRequest.Undo.ContractID ) ;
	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
    try
    {
	try
	{
		int fcount = 0;
		int reccount = 0;
		if (SplitData("404",ReadFirstData(cmd), lstDD,  fcount,reccount) != DEF_ACK_OK)
		{
			return -1;
		}
	}
	__finally
	{
		delete lstDD;
	}
    }
    catch(const int err)
    {
        return err;
    }

	return 0;
}

market_type  TTrdItfImp::ConvertMarketType(const char *t)
{
	if( t==NULL ) return mtNo;
	if( strcmp(_SH ,t)==0 )
	{
		return mtSHA;
	}
	else if( strcmp( _SZ,t)==0 )
	{
		return mtSZA;
	}
	else return mtNo;
}

order_type   TTrdItfImp::ConvertOrderType(const char *t)
{
/*
代码	交易行为
0B	买入
0S	卖出
4B	配股缴款
5S	转债转股
6S	转债回售
7B	新股申购
8B	新股缴款
9B	融资
9S	融券
4C	认购
4P	认估
7K	ETF申购
7L	ETF赎回
*/
	if( t==NULL ) return  otNo;
	if( strcmp(t,"0B")==0 )
	{
		return otBuy;
	}
	else if( strcmp(t,"0S")==0)
	{
		return otSell;
	}
	else if( strcmp(t,"7K")==0)
	{
		return otETFSub;
	}
	else if( strcmp(t,"7L") == 0)
	{
		return otETFRed;
	}
	else return otNo;
}

order_state  TTrdItfImp::ConvertOrderState(const char *t)
{
	return osno;
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
            return _SH;
        break;
        case mtSZA:
            return _SZ;
        break;
        default:
            return "";
	}
	return "";
}

char *  TTrdItfImp::ConvertOrderType(order_type t)
{
	/*
代码	交易行为
0B	买入
0S	卖出
4B	配股缴款
5S	转债转股
6S	转债回售
7B	新股申购
8B	新股缴款
9B	融资
9S	融券
4C	认购
4P	认估
7K	ETF申购
7L	ETF赎回
*/
	switch (t) {
	case otBuy:
		return "0B";

	case otSell:
		return "0S";

	case otETFSub:
		return "7K";

	case otETFRed:
		return "7L";

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
/*
0	人民币
1	港币
2	美元
*/
char *  TTrdItfImp::ConvertMoneyType(money_type t)
{
	switch (t)
	{
	case motRMB : return "0";
	case motUSD : return "2";
    case motHKD : return "1";
	default: return "";
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

		FZXSet.SvrIp            = ini->ReadString (PLUGINNAME,"SvrIP",FZXSet.SvrIp);
		FZXSet.SvrPort          = ini->ReadInteger(PLUGINNAME,"SvrPort",FZXSet.SvrPort);
		FZXSet.TimeOut          = ini->ReadInteger(PLUGINNAME,"TimeOut",FZXSet.TimeOut);
		FZXSet.debug_mode       = ini->ReadBool(PLUGINNAME,"debug_mode",FZXSet.debug_mode);
		FZXSet.local_ip        = ini->ReadString(PLUGINNAME,"local_ip",FZXSet.local_ip);
		FZXSet.entrust_way      = ini->ReadString (PLUGINNAME,"entrust_way",FZXSet.entrust_way);
		FZXSet.money_type       = ini->ReadString (PLUGINNAME,"money_type",FZXSet.money_type);
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
		ini->WriteString (PLUGINNAME,"SvrIP",            FZXSet.SvrIp);
        ini->WriteInteger(PLUGINNAME,"SvrPort",          FZXSet.SvrPort);
		ini->WriteInteger(PLUGINNAME,"TimeOut",          FZXSet.TimeOut);
		ini->WriteBool   (PLUGINNAME,"debug_mode",       FZXSet.debug_mode);
		ini->WriteString(PLUGINNAME,"local_ip",        FZXSet.local_ip);
		ini->WriteString (PLUGINNAME,"entrust_way",           FZXSet.entrust_way);
		ini->WriteString (PLUGINNAME,"money_type",        FZXSet.money_type);

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
	order_man.clear_all();
	try
    {
		FidTcp->Disconnect();
		//delete FidTcp;
		//FidTcp = new TIdTCPClient(NULL);
	}
    catch(...)
    {

	}
}

int TTrdItfImp::KeepAlive(void)
{
	order_man.qry_orders(this);

    if( (::GetTickCount()-_oldcount) > 1000*15 )
    {
        AnsiString data;
        data.printf("502|%s|%s|%s|", FUSER_CODE.c_str() ,
        this->FAccInfo.Capital,
            FZXSet.money_type.c_str());

        AnsiString cmd = GenCMD( data.Length(), data  );

        TStringList *lstDD = new TStringList();
        this->lock();
        try
        {
            try
            {
                int fcount = 20;
                int reccount = 0;
                if (SplitData("502",ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
                {
                    ODS("-KeepAlive-");
                }
                else
                {
				   ODS("-KeepAlive Error-");
				   /*
				   if( !this->SessionAutoOpen() )
				   {
					ODS("KeepAlive中SessionAutoOpen失败");
				   } */
				   this->SetLogout();
				}
            }
            __finally
            {
                delete lstDD;
            }
        }
        catch(const int err)
        {
			ODS("-KeepAlive Error-");
			/*
			if( !this->SessionAutoOpen() )
			{
				ODS("KeepAlive中SessionAutoOpen失败");
			}
			*/
			this->SetLogout();
        }
        this->unlock();
        _oldcount = ::GetTickCount();
    }
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
				itf->SetLogout();
				/*if( !itf->SessionAutoOpen() )
				{
					ODS("order_manager::qry_orders中SessionAutoOpen失败");
				}
				*/
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
