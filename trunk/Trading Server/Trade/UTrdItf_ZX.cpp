//---------------------------------------------------------------------------
#pragma hdrstop

#include "UTrdItf_ZX.h"
#include <assert.h>
#include <StrUtils.hpp>
#include <DateUtils.hpp>

#pragma package(smart_init)

#define DEF_HEAD_LEN            9
#define INDEX(field,record,n)   (DEF_HEAD_LEN + field + record*field + n - 1)
#define DEF_ACK_OK              0
#define DEF_ACK_ERROR           -1
#define DEF_TIMEOUT             -100
#define DEF_INVALID_STOCKCODE   -101
#define DEF_OTHER_ERROR         -504
#define _SH                     "10"
#define _SZ                     "00"

static HMODULE h_kdgtmm = NULL;

typedef (*pfunc_KDGT_CRC)(unsigned char* lpinbuf, int nlen, unsigned char *lpoutcrccode);
typedef (*pfunc_KDGT_Encrypt)(unsigned char *lpszkey, unsigned char* lpinbuf, int nlen, unsigned char *lpoutbuf);
typedef (*pfunc_KDGT_Decrypt)(unsigned char *lpszkey, unsigned char* lpinbuf, int nlen, unsigned char *lpoutbuf);

static pfunc_KDGT_CRC KDGT_CRC = NULL;
static pfunc_KDGT_Encrypt KDGT_Encrypt = NULL;
static pfunc_KDGT_Decrypt KDGT_Decrypt = NULL;
static LONG link_count_ZX=0;

unsigned char * KEY   = "SZKINGDOM";
const char * REQ_HEAD = "%%04d|%04d|%8s|KDGATEWAY1.0|%s|%s|%s|%c|%s|%s|%s|%s|";
const int  NEXT_FLAG  = 6;   // 后续包
//---------------------------------------------------------------------------
String GetDate(void)
{
	return Now().FormatString("yyyy-mm-dd");
}

String ReplaceCRC(const String cmd,const char* to)
{
	return cmd.SubString(1,10) + to + cmd.SubString(19,cmd.Length() - 18) ;//20051121---19==>18
}

String CRC(const String cmd)
{
	char szCRC[20];
	KDGT_CRC( cmd.c_str(),cmd.Length(),szCRC);
	// 更新crc字段
	return ReplaceCRC( cmd, szCRC );
}

String TTrdItf_ZX::GenCMD( int data_size, String data )
{
	AnsiString cmd;
	cmd.printf(REQ_HEAD,data_size,FWorkKey,FUSER_CODE.c_str(),FZXSet.branch_no,FBRANCH.c_str(),
		FZXSet.entrust_way,FSESSION.c_str(),"","","" ) ;

	cmd.printf(String(cmd).c_str(),cmd.Length());
	cmd=cmd+data ;

	return CRC(cmd);
}

TTrdItf_ZX::TTrdItf_ZX(TZXSet *set)
{
	CopyMemory(&FZXSet,set,sizeof(TZXSet));
	FidTcp = new TIdTCPClient(NULL);
	FWorkKey[0]= 0;
}

TTrdItf_ZX::~TTrdItf_ZX()
{
	FidTcp->Disconnect();
	delete FidTcp;

	InterlockedDecrement(&link_count_ZX);
	if( link_count_ZX<=0 && h_kdgtmm)
	{
		FreeLibrary(h_kdgtmm);
	}
}

AnsiString TTrdItf_ZX::ReadNextData()
{
	AnsiString cmd = GenCMD( 3, "99|" );
	return ReadFirstData(cmd);
}

AnsiString TTrdItf_ZX::ReadFirstData(AnsiString cmd)
{
	//cmd = "0040|0004|00000000|KDGATEWAY1.0|||||||||100|" ;
	//清除上次的返回信息
	int n = FidTcp->ReadFromStack(true, 1, true, NULL);
	if (n > 0) FidTcp->ReadString(n);
	//#ifndef _DEBUG//20051122
	//	ODS("send=%s",cmd.c_str());
	//#endif        
	FidTcp->Write(cmd);

	n = FidTcp->ReadFromStack(true, FZXSet.TimeOut, true, NULL);
	if (n <= 0)
	{
		ODS("接收数据超时");
		return ""  ;
	}

	AnsiString ret = FidTcp->ReadString(n);

	//#ifdef _DEBUG//20051121---查询股份信息时发现数据并没有收全

	int nTolLen = GetRecvingDataLen(ret);
	if(n < nTolLen)
	{
		int nCurLen = n;
		TDateTime dtTime = Now();
		for(;;)
		{
			n = FidTcp->ReadFromStack(true, FZXSet.TimeOut, true, NULL);
			if (n <= 0)
			{
				ODS("接收数据超时");
				return ""  ;
			}
			nCurLen += n;
			ret += FidTcp->ReadString(n);
			if(nCurLen >= nTolLen)
				break;

			if(MilliSecondsBetween(dtTime, Now()) > FZXSet.TimeOut)
			{
				ODS("接收数据超时");
				return ""  ;
			}
		}
	}
    
	//#endif
	//#ifndef _DEBUG//20051122
	//	ODS("ret=%s",ret.c_str());
	//#endif        

	return ret;
}

int TTrdItf_ZX::SplitData(AnsiString SD, TStringList *lstDD,int &fieldcount,int &reccount)
{
	//char seps[] = "|";
	//char *substr;
	//char *data;
	assert(lstDD != NULL);

	lstDD->Clear();
	try
	{
		SD = SD.Trim();
		/*		data = new char[SD.Length() + 1];
		memset(data, 0, SD.Length() + 1);
		strncpy(data, SD.c_str(), SD.Length());

		substr = strtok(data, seps);
		#ifndef _DEBUG
		while (substr != NULL)
		{
		lstDD->Add(substr);
		substr = strtok(NULL, seps);
		}
		#else*///20051122
		int nCurPos = 0;
		for(;;)//应答包头结构: 头长度 CHAR(4),前面以字符‘0’填充;数据长度 VARCHAR(n),前面以字符‘0’填充
		{
			nCurPos = SD.Pos("|");
			if(nCurPos > 1)
				lstDD->Add(SD.SubString(1, nCurPos-1));
			else if(nCurPos == 1)
				lstDD->Add("");
			else //if(nCurPos <= 0 )
			{
				//注:最后一个数据可以允许没有竖线"|"---
				if(!SD.IsEmpty())
				{
					lstDD->Add(SD);
				}

				break;
			}

			SD.Delete(1, nCurPos);
		}
		//#endif
	}
	__finally
	{
		//delete []data;
	}

	if (lstDD->Count < DEF_HEAD_LEN)
	{
		ODS("返回字段小于响应数据头字段数!");
		return DEF_ACK_ERROR;
	}

	if (lstDD->Strings[4] != "0")
	{
		ODS("返回码不是0，返回码:%s,错误信息为%s", lstDD->Strings[4].c_str(),
			lstDD->Strings[5].c_str());
		return DEF_ACK_ERROR;
	}

	reccount =  lstDD->Strings[8].ToIntDef(0);
	//if (lstDD->Count != lstDD->Strings[7].ToIntDef(0) * reccount)
	if(lstDD->Count-DEF_HEAD_LEN != lstDD->Strings[7].ToIntDef(0) * (1+reccount))//20051121---替代上一句
	{
		ODS("Count = %d,应答字段数=%s,应答记录数=%s",lstDD->Count,
			lstDD->Strings[7].c_str(),lstDD->Strings[8].c_str());
		return DEF_ACK_ERROR;///
	}

	if( fieldcount > lstDD->Strings[7].ToIntDef(0) )
	{
		return DEF_ACK_ERROR;
	}

	fieldcount = lstDD->Strings[7].ToIntDef(0);

	return DEF_ACK_OK;
}

int TTrdItf_ZX::Init()  //初始化
{
	if( h_kdgtmm == NULL )
		h_kdgtmm = LoadLibrary("KdGTmm.dll");

	if( KDGT_CRC ==  NULL )
	{
		KDGT_CRC = (pfunc_KDGT_CRC)GetProcAddress(h_kdgtmm, "KDGT_CRC");
	}

	if (KDGT_Encrypt == NULL)
	{
		KDGT_Encrypt = (pfunc_KDGT_Encrypt)GetProcAddress(h_kdgtmm, "KDGT_Encrypt");
	}

	if( KDGT_Decrypt == NULL )
	{
		KDGT_Decrypt = (pfunc_KDGT_Decrypt)GetProcAddress(h_kdgtmm, "KDGT_Decrypt");
	}

	if (KDGT_CRC == NULL || KDGT_Encrypt == NULL || KDGT_Decrypt == NULL)
	{
		return -1;
	}

	InterlockedIncrement(&link_count_ZX);

	try
	{
		if (!FidTcp->Connected())
		{
			FidTcp->Host = FZXSet.SvrIp;
			FidTcp->Port = FZXSet.SvrPort;
			FidTcp->Connect();

			AnsiString cmd;
			// 生成头
			cmd.printf(REQ_HEAD,4,"","",FZXSet.branch_no,"",FZXSet.entrust_way,"","","","" ) ;
			cmd.printf( String(cmd).c_str(), cmd.Length()) ;
			// 加入数据
			cmd += "100|" ;

			//cmd = "0069|0005|ac82aefb|KDGATEWAY1.0|2247|00909627a566|103|3|00000000|2|||201||";
			// 发送
			TStringList *lstDD = new TStringList();
			int fcount = 1;
			int reccount = 0;
			if (SplitData(ReadFirstData(cmd), lstDD, fcount,reccount) == DEF_ACK_OK)
			{
				if (lstDD->Strings[INDEX(fcount,0,1)].Length() > 0)
				{
					String szTmp = lstDD->Strings[INDEX(fcount,0,1)];
					KDGT_Decrypt( KEY,szTmp.c_str(),szTmp.Length(),FWorkKey);
				}
			}
			delete lstDD;
		}
	}
	catch (...)
	{
		ODS("连接柜台失败!");
	}

	return (FidTcp->Connected()==true && strlen(FWorkKey) == 8) ? 0 : -1;
}

//--------------------------------------------------------------------------
/*
用户登录(301)
功能代码	301
功能描述	用户登录
请求数据	域名称	标识	类型及长度	必要	描述
用户标识类型	USER_ID_CLS	CHAR（2）	Y
用户标识	USER_ID	CHAR（65）	Y
交易密码	USER_PWD	CHAR（32）	Y	加密后字符
返回数据	域名称	标识	类型及长度	描述
交易市场	MARKET	CHAR(2)
股东代码	SECU_ACC	CHAR(10)
股东姓名	SECU_ACC_NAME	VARCHAR(16)
缺省资产帐号	ACCOUNT	VARCHAR(20)
客户代码	USER_CODE	INT
客户姓名	USER_NAME	VARCHAR(16)
开户分支	BRANCH	INT
会话句柄	SESSION	CHAR(16)
错误描述	错误代码	错误信息
301	帐户登录失败
302	您的帐户状态不正常
303	磁卡号不存在
304	股东代码不存在
305	资产帐号不存在
306	用户代码不存在
307	交易市场不存在
309	密码错误
备注信息	用户标识类型:
?	'Z'表示以资产帐号登录  用户标识为资产帐号
?	'U'表示以用户代码登录  用户标识为用户代码
?	'C'表示以磁卡登录      用户标识为磁卡号
?	'01'…'12' 交易市场    用户标识为对应市场的股东代码

此返回为多结果集，用资产帐号，用户代码，磁卡登陆时返回每个市场的主股东，否则返回对应的股东
交易密码需加密送入，加密采用BlowFish加密
结果集为多记录

Send:0218|0029|280fa8ef|KDGATEWAY1.0|05857182|0010dc04fa9b|||||05857182||||301|U|10161|F9A0431B95567FDE|
RECV:0059|0000|d2c70905|KDGATEWAY1.0|611|认证信息没有设置|0|0|0|
Send:0052|0034|384595ab|KDGATEWAY1.0||0010dc04fa9b|||||||301|Z|2100801000|F9A0431B95567FDE|
RECV:0051|0000|ef4e9dea|KDGATEWAY1.0|313|密码有误|0|0|0|
*/
int TTrdItf_ZX::SetAccount() //设置帐号
{
	AnsiString cmd;


	TStringList *lstDD = new TStringList();

	try
	{
		String USER_ID_CLS;

		if(FRequest.SetAccount.Sort == asCA)
		{
			USER_ID_CLS="Z";
		}
		else if(FRequest.SetAccount.Sort==asSH)
		{
			USER_ID_CLS=_SH;
		}
		else if(FRequest.SetAccount.Sort==asSZ)
		{
			USER_ID_CLS=_SZ;
		}
		else
			return -1;

		char szEPwd[100];
		KDGT_Encrypt(/*KEY*/FWorkKey,FRequest.SetAccount.PW,strlen(FRequest.SetAccount.PW),
			szEPwd);//20051121---KEY==>FWorkKey

		String data;
		data.printf( "301|%2s|%s|%s|",USER_ID_CLS , FRequest.SetAccount.Account,szEPwd) ;

		cmd.printf(REQ_HEAD,data.Length(),FWorkKey,"",FZXSet.branch_no,"",FZXSet.entrust_way,"","","","" ) ;
		cmd.printf(String(cmd).c_str(),cmd.Length()) ;
		cmd+= data;

		cmd = CRC(cmd);

		int fcount = 8;
		int reccount = 0;

		if (SplitData(ReadFirstData(cmd), lstDD, fcount, reccount) == DEF_ACK_OK)
		{
			strncpy(FAccInfo.Capital, lstDD->Strings[INDEX(fcount,0,4)].c_str(), 13);
			strncpy(FAccInfo.PW, FRequest.SetAccount.PW, 13);

			FUSER_CODE = lstDD->Strings[INDEX(fcount,0,5)] ;
			FBRANCH    = lstDD->Strings[INDEX(fcount,0,7)] ;
			FSESSION   = lstDD->Strings[INDEX(fcount,0,8)] ;

			goto next;
			while (lstDD->Strings[NEXT_FLAG]=="1")
			{
				if (SplitData(ReadNextData(), lstDD, fcount, reccount) == DEF_ACK_OK)
				{
next:
					for( int i = 0; i<reccount; i++ )
					{
						if(  lstDD->Strings[INDEX(fcount,i,1)] == _SH )
						{
							//lstrcpyn(FAccInfo.SH,FRequest.SetAccount.Account,13);
							//#ifdef _DEBUG//20051121---用下面替代上面?
							lstrcpyn(FAccInfo.SH, lstDD->Strings[INDEX(fcount,i,2)].c_str(), 13);
							//#endif
						}
						else if ( lstDD->Strings[INDEX(fcount,i,1)] == _SZ  )
						{
							//lstrcpyn(FAccInfo.SZ,FRequest.SetAccount.Account,13);
							//#ifdef _DEBUG//20051121---用下面替代上面?
							lstrcpyn(FAccInfo.SZ, lstDD->Strings[INDEX(fcount,i,2)].c_str(), 13);
							//#endif

						}
					}
				}
			}


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
			return -1;
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
int TTrdItf_ZX::GetTrdInfo()   //取得盘口数据
{
	return -1;
}

/*查询资金余额和可用资金余额
资金查询(502)

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
货币	CURRENCY	CHAR(1)
资金余额	BALANCE	DECIMAL(16,2)
资金可用金额	AVAILABLE	DECIMAL(16,2)
异常冻结金额	FROZEN	DECIMAL(16,2)	
交易冻结金额	TRD_FRZ	DECIMAL(16,2)	
可提现金金额	DRAW_AVL_CASH	DECIMAL(16,2)	
可提支票金额	DRAW_AVL_CHEQUE	DECIMAL(16,2)	
可转账金额	TRANSFER_AVL	DECIMAL(16,2)
错误描述	错误代码	错误信息
306	用户代码不存在
305	资产帐号不存在
501	无查询结果
502	查询失败
备注信息	
*/
int TTrdItf_ZX::QryMoney()     //资金查询
{
	String data;
	data.printf("502|%s|%s|%c", FUSER_CODE.c_str() ,
		this->FAccInfo.Capital,
		FZXSet.money_type);

	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 11;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			NewAns(1);
			(*FAnswer)[0].QryMoney.Balance = StrToFloatDef(lstDD->Strings[INDEX(fcount,0,5)] ,0);
			(*FAnswer)[0].QryMoney.Available = StrToFloatDef(lstDD->Strings[INDEX(fcount,0,6)],0);
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

	return 0;
}

int TTrdItf_ZX::QryStock()     //股份查询
{
	return -1;
}

int TTrdItf_ZX::QryCanBuy()    //取可买数量
{
	return -1;
}

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

505|%10s|%10s|0|%s|%2s|||  ||%s||||
返回数据	域名称	标识	类型及长度	描述
1委托日期	ORDER_DATE	CHAR(10)
2交易日期	TRD_DATE	CHAR(10)
3客户代码	USER_CODE	VARCHAR(20)
-客户姓名	USER_NAME	VARCHAR(16)	删除20031228
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
-交易席位	SEAT	VARCHAR(6)	删除20031228
15价格	PRICE	DECIMAL(10,3)
16数量	QTY	INT
17委托金额	ORDER_AMT	DECIMAL(16,2)
18委托冻结金额	ORDER_FRZ_AMT	DECIMAL(16,2)
-资金可用金额	AVAILABLE	DECIMAL(16,2)	删除20031228
19股份可用	SHARE_AVL	INT	删除20031228
20撤单标志	IS_WITHDRAW	CHAR(1)
21已撤单标志	IS_WITHDRAWN	CHAR(1)
22可撤单标志	CAN_WITHDRAW	CHAR(1)	删除20031228 恢复该字段20040101
23发送标志	DCL_FLAG	CHAR(1)
-报盘时间	DCL_TIME	CHAR(8)	删除20031228
24合法标志	VALID_FLAG	CHAR(1)
25成交数量	MATCHED_QTY	INT
26已撤单数量	WITHDRAWN_QTY	INT
27成交金额	MATCHED_AMT	DECIMAL(16,2)
-实时清算金额	RLT_SETT_AMT	DECIMAL(16,2)	删除20031228
28操作备注	OP_REMARK	VARCHAR(64)
-发起方	INITIATOR	CHAR(1)	删除20031228
29外部机构	EXT_INST	SMALLINT
-外部账户	EXT_ACC	VARCHAR(32)	删除20031228
-外部子账户	EXT_SUB_ACC	VARCHAR(32)	删除20031228
-外部冻结金额	EXT_FRZ_AMT	DECIMAL(16,2)	删除20031228
30外部记录号	EXT_REC_NUM	INT
-已清算外部资金	EXT_SETT_AMT	DECIMAL(16,2)	删除20031228
31外部业务号	EXT_BIZ_NO	VARCHAR(10)	增加20031228
32外部合同号	EXT_ORDER_ID	VARCHAR(10)	增加20031228

错误描述	错误代码	错误信息
306	用户代码不存在
501	无查询结果
502	查询失败
备注信息	 	发起方              <I>:券商发起<O>:外部机构发起,<A>:双方发起
查询委托模式		<0>:所有委托，<1>:可撤委托，<2>:非法委托
撤单标志			<0>:正常委托，<1>:撤单委托
已撤单标志			<0>:未撤单，<1>:已撤单
可撤单标志			<0>:不允许撤单，<1>:允许撤单
发送标志			<0>:未发送，<1>:已发送
报盘时间			格式：HH:MM:SS
合法标志			<0>:合法，<1>:非法
送证券代码必须送交易市场

*/
int TTrdItf_ZX::QryDetail()    //成交查询
{
	if(FRequest.QryDetail.ContractID[0]==0) return -1;

	String market;
	switch (FRequest.QryDetail.Bourse)
	{
	case bsSH : market = _SH; break;
	case bsSZ : market = _SZ; break;
	default: return -1;
	}

	String data;
	String date = GetDate();

	//data.printf("505|%10s|%10s|0|%s|%2s|||||%s||||",date.c_str(),date.c_str(),
	//	FUSER_CODE ,market,
	//	FRequest.QryDetail.ContractID);
	//#ifdef _DEBUG//20051122---注:金证马庆海提示将合同号放在第9字段,文档上是第10字段
	data.printf("505|%10s|%10s|0|%s|%2s||||%s|||||",date.c_str(),date.c_str(),
		FUSER_CODE.c_str() ,market.c_str(),
		FRequest.QryDetail.ContractID);
	//#endif                

	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 32;
		int reccount = 0;

		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			NewAns(1);
			(*FAnswer)[0].QryDetail.Num  =  lstDD->Strings[INDEX(fcount,0,23)].ToIntDef(0);
			(*FAnswer)[0].QryDetail.UndoNum=lstDD->Strings[INDEX(fcount,0,32)].ToIntDef(0);//20051122---24(CAN_WITHDRAW)==>32(WITHDRAWN_QTY)
			if( (*FAnswer)[0].QryDetail.Num >0)
				(*FAnswer)[0].QryDetail.Price=  StrToFloatDef(lstDD->Strings[INDEX(fcount,0,25)],0)/
				(*FAnswer)[0].QryDetail.Num;
			else  (*FAnswer)[0].QryDetail.Price= 0;
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
	return 0;
}

int TTrdItf_ZX::QryHisDetail() //历史成交查询
{
	// 暂时不用
	return -1;
}

int TTrdItf_ZX::QryCsn()       //查询某个委托合同
{
	// 暂时不用
	return -1;
}

int TTrdItf_ZX::QryCurCsn()    //当日委托查询
{
	TList * lstAns = new TList();
	//if(FRequest.QryDetail.ContractID[0]==0) return -1;
	//if(FRequest.QryCurCsn.==0) return -1;//20051122---替代上一句 ,只能默认为一个交易所

	//String market;
	//#ifdef _DEBUG//20051122---
	//    market = _SH;//只能默认为一个交易所
	//#else
	/*	switch (FRequest.QryDetail.Bourse)
	{
	case bsSH : market = _SH; break;
	case bsSZ : market = _SZ; break;
	default: return -1;
	}*/
	//#endif

	String data;
	String date = GetDate();

	data.printf("505|%10s|%10s|0|%s||||  ||||||",date.c_str(),date.c_str(),
		FUSER_CODE.c_str());
	//#ifdef _DEBUG//20051122---要么默认上交所要么查询所有委托
	//       data.printf("505|%10s|%10s|0|%s||||||||||",date.c_str(),date.c_str(),
	//		FUSER_CODE);
	//#endif        

	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 32;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			goto ADD;

			while (lstDD->Strings[NEXT_FLAG]=="1")
			{
				if (SplitData(ReadNextData(), lstDD,  fcount,reccount) == DEF_ACK_OK)
				{
ADD:
					for ( int i =0; i<reccount; i++ )
					{
						TConsignInfo *ci = new TConsignInfo;
						memset(ci, 0, sizeof(TConsignInfo));

						strncpy(ci->ContractID,lstDD->Strings[INDEX(fcount,i,11)].c_str(), 8);
						strncpy(ci->SecuID,    lstDD->Strings[INDEX(fcount,i,14)].c_str(), 7);
						strncpy(ci->SecuDesc,  lstDD->Strings[INDEX(fcount,i,13)].c_str(), 8);
						strncpy(ci->Time,      "", 8);
						strncpy(ci->Date,      "", 8);

						ci->Bourse = (lstDD->Strings[INDEX(fcount,i,12)]==_SH) ? bsSH : bsSZ;

						ci->Type =ConvertType(lstDD->Strings[INDEX(fcount,i,9)].c_str());

						ci->State  = 'N';
						ci->CsnVol = StrToIntDef(lstDD->Strings[INDEX(fcount,i,16)], 0);
						ci->TrdVol = StrToIntDef(lstDD->Strings[INDEX(fcount,i,23)], 0);//20051122---25==>23
						ci->CancelVol = StrToIntDef(lstDD->Strings[INDEX(fcount,i,32)], 0);//20051122---26==>32
						ci->CsnPrice  = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,15)], 0);
						if( ci->TrdVol >0)
							ci->TrdPrice  = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,25)], 0) / ci->TrdVol;//20051122---27==>25

						lstAns->Add(ci);
					}
				}
			}

			if (lstAns->Count > 0)
			{
				NewAns(lstAns->Count);
				for ( int i = 0; i < lstAns->Count; i++ )
				{
					TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
					memcpy(&(*FAnswer)[i].QryCurCsn.CsgInfo, ci, sizeof(TConsignInfo));
				}
			}

			for ( int i = 0; i < lstAns->Count; i++ )
			{
				TConsignInfo *ci = (TConsignInfo *)lstAns->Items[i];
				delete ci;
			}
			lstAns->Clear();
		}
		else
		{
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

int TTrdItf_ZX::QryHisCsn()    //历史委托查询
{
	return -1;
}

/*
成交查询(506) [支持三方交易]
功能代码	506
功能描述	成交查询
请求数据	域名称	标识	类型及长度	必要	描述
起始日期	BEGIN_DATE	CHAR(10)	Y
终止日期	END_DATE	CHAR(10)	Y
客户代码	USER_CODE	INT	Y
交易市场	MARKET	CHAR(2)	N
股东代码	SECU_ACC	CHAR(10)	N
证券代码	SECU_CODE	VARCHAR（8）	N	
交易行为	TRD_ID	CHAR(2)        	N	
合同序号	ORDER_ID	VARCHAR(10)    	N	
分支机构	BRANCH	INT   	N	
资产账户	ACCOUNT	CHAR(20)        	N	
外部机构	EXT_INST	INT	N	三方交易时送
506|%10s|%10s|%s|%2s||||||||
返回数据	域名称	标识	类型及长度	描述
1委托日期	ORDER_DATE	CHAR(10)
2交易日期	TRD_DATE	CHAR(10)
3客户代码	USER_CODE	INT
-客户姓名	USER_NAME	VARCHAR(16)	删除20031229
4资产账户	ACCOUNT	VARCHAR(20)
5货币	CURRENCY	CHAR(1)
6分支机构	BRANCH	INT
7股东代码	SECU_ACC	VARCHAR(10)
8股东姓名	SECU_ACC_NAME	VARCHAR(16)	增加20031229
9交易行为	TRD_ID	CHAR(2)
10合同序号	ORDER_ID	VARCHAR(10)
11交易市场	MARKET	CHAR(2)
12证券名称	SECU_NAME	VARCHAR(16)
13证券代码	SECU_CODE	VARCHAR(8)
-交易席位	SEAT	VARCHAR(6)	删除20031228
14价格	PRICE	DECIMAL(10,3)
15数量	QTY	INT
-委托金额	ORDER_AMT	DECIMAL(16,2)	删除20031228
16委托冻结金额	ORDER_FRZ_AMT	DECIMAL(16,2)
-资金可用金额	AVAILABLE	DECIMAL(16,2)	删除20031228
17股份可用	SHARE_AVL	INT	删除20031228
-撤单标志	IS_WITHDRAW	CHAR(1)	删除20031228
-报盘时间	DCL_TIME	CHAR(8)	删除20031228
18成交时间	MATCHED_TIME	CHAR(8)
19成交序号	MATCHED_SN	VARCHAR(32)
20成交价格	MATCHED_PRICE	DECIMAL(10,3)
21成交数量	MATCHED_QTY	INT
22成交金额	MATCHED_AMT	DECIMAL(16,2)
23实时清算金额	RLT_SETT_AMT	DECIMAL(16,2)
24操作备注	OP_REMARK	VARCHAR(64)
-发起方	INITIATOR	CHAR(1)	删除20031228
25外部机构	EXT_INST	SMALLINT	
-外部账户	EXT_ACC	VARCHAR(32)	删除20031228
-外部子账户	EXT_SUB_ACC	VARCHAR(32)	删除20031228
-外部冻结金额	EXT_FRZ_AMT	DECIMAL(16,2)	删除20031228
-外部记录号	EXT_REC_NUM	INT	删除20031228
-已清算外部资金	EXT_SETT_AMT	DECIMAL(16,2)	删除20031228
错误描述	错误代码	错误信息
306	用户代码不存在
501	无查询结果
502	查询失败
备注信息	 	发起方              <I>:券商发起<O>:外部机构发起,<A>:双方发起
撤单标志			<0>:正常委托，<1>:撤单委托

*/
int TTrdItf_ZX::QryCurTrd()    //当日成交查询
{
	TList * lstAns = new TList();
	TStringList *lstDD = new TStringList();

	String data;
	String date = GetDate();
	data.printf("506|%10s|%10s|%s|||||||||",date.c_str(),date.c_str(),
		FUSER_CODE.c_str());

	AnsiString cmd = GenCMD( data.Length(), data  );

	try
	{
		int fcount = 25;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			goto ADD;
			while (lstDD->Strings[NEXT_FLAG]=="1")
			{
				if (SplitData(ReadNextData(), lstDD,  fcount,reccount) == DEF_ACK_OK)
				{
ADD:
					for( int i=0; i < reccount; i++ )
					{
						TTradeInfo *ti = new TTradeInfo;
						memset(ti, 0, sizeof(TTradeInfo));

						strncpy(ti->SecuID,   lstDD->Strings[INDEX(fcount,i,13)].c_str(), 7);
						strncpy(ti->SecuDesc, lstDD->Strings[INDEX(fcount,i,12)].c_str(), 8);
						strncpy(ti->Time,     lstDD->Strings[INDEX(fcount,i,18)].c_str(), 8);
						strncpy(ti->Date,     Now().FormatString("yyyymmdd").c_str(), 8);
						ti->Type  = ConvertType(lstDD->Strings[INDEX(fcount,i,9)].c_str());
						ti->Vol   = StrToIntDef(lstDD->Strings[INDEX(fcount,i,21)], 0);//20051122---成交量为负算正常?
						ti->Price = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,20)], 0);

						lstAns->Add(ti);
					}
				}
				else
				{
					return -1;
				}
			}

			if (lstAns->Count > 0)
			{
				NewAns(lstAns->Count);
				for( int i = 0; i < lstAns->Count; i++ )
				{
					TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
					memcpy(&(*FAnswer)[i].QryHisTrd.TrdInfo, ti, sizeof(TTradeInfo));
				}
			}

			for ( int i = 0; i < lstAns->Count; i++ )
			{
				TTradeInfo *ti = (TTradeInfo *)lstAns->Items[i];
				delete ti;
			}
			lstAns->Clear();
		}
		else
		{
			return -1 ;
		}
	}
	__finally
	{
		delete lstDD;
		delete lstAns;
	}

	return 0;
}

int TTrdItf_ZX::QryHisTrd()    //历史成交查询
{
	return -1;
}

int TTrdItf_ZX::QryBill()      //查询资金流水（对帐单）
{
	return -1;
}

/*
股份查询(504)[支持三方交易]

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
7交易席位	SEAT	VARCHAR(6)
8分支机构	BRANCH	INT
9外部机构	EXT_INST	INT
10货币	CURRENCY	CHAR(1)
11股份余额	SHARE_BLN	INT
12股份可用	SHARE_AVL	INT
13股份交易冻结数	SHARE_TRD_FRZ	INT
14股份在途数量	SHARE_OTD	INT
15股份在途可用数量	SHARE_OTD_AVL	INT	增加20040103
16股份异常冻结数	SHARE_FRZ	INT
17股份非流通数量	SHARE_UNTRADE_QTY	INT
18当前成本	CURRENT_COST	DECIMAL(16,2)
19市值	MKT_VAL	DECIMAL(16,2)	
错误描述	错误代码	错误信息
306	用户代码不存在
501	无查询结果
502	查询失败
备注信息	送证券代码必须送交易市场

*/
int TTrdItf_ZX::QryStocks()    //查询帐号中所有的股份
{
	TList * lstAns = new TList();
	TStringList *lstDD = new TStringList();

	String market;

	switch (FRequest.QryStocks.Bourse)//20051122----为什么一直是上海
	{
	case bsSH : market = _SH; break;
	case bsSZ : market = _SZ; break;
	default: market = _SH;//20051122----默认为上交所
	}

	String data;

	if(  FRequest.QryStocks.Bourse == bsSH )
		data.printf("504|%s||%2s|%s|||",FUSER_CODE.c_str() ,market.c_str(),this->FAccInfo.SH);//20051122---"504|%s|%s|%2s|%s|||"==>"504|%s||%s|%s|||"
	else if( FRequest.QryStocks.Bourse == bsSZ )
		data.printf("504|%s||%2s|%s|||",FUSER_CODE.c_str() ,market.c_str(),this->FAccInfo.SZ);//20051122---"504|%s|%s|%2s|%s|||"==>"504|%s||%s|%s|||"
	else
		data.printf("504|%s||||||",FUSER_CODE.c_str());//20051122---"504|%s|%s|%s|||||"==>"504|%s||%s|%s|||"


	AnsiString cmd = GenCMD( data.Length(), data  );

	String retMarket;
	try
	{
		int fcount = 19;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			goto ADD;
			while (lstDD->Strings[NEXT_FLAG]=="1")
			{
				if (SplitData(ReadNextData(), lstDD,  fcount,reccount) == DEF_ACK_OK)
				{
ADD:
					for( int i=0; i<reccount; i++ )
					{
						TStockInfo *si = new TStockInfo;
						memset(si, 0, sizeof(TStockInfo));

						retMarket = lstDD->Strings[INDEX(fcount,i,3)]  ;

						if( retMarket == _SH )
							si->SecuID[0] = 'H';
						else if( retMarket == _SZ )
							si->SecuID[0] = 'S';
						else
							si->SecuID[0] = 'H';

						strncpy(si->SecuID+1 , lstDD->Strings[INDEX(fcount,i,6)].c_str(), 6);
						strncpy(si->SecuDesc,   lstDD->Strings[INDEX(fcount,i,4)].c_str(), 12);

						si->Balance       = lstDD->Strings[INDEX(fcount,i,12)].ToIntDef(0);//20051122---11==>12
						si->Available     = lstDD->Strings[INDEX(fcount,i,13)].ToIntDef(0);//20051122---12==>13
						si->ProfitAndLoss = 0;
						si->CostPrice     = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,18)], 0);
						si->Cost          = si->Balance * si->CostPrice;
						si->CurPrice      = 0;
						si->CurVal        = StrToFloatDef(lstDD->Strings[INDEX(fcount,i,19)], 0);
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
/*
委托买卖业务(403)[支持三方交易]

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

404|%s|%2s|%s|||%s|%2s|%10.3f|%d||||
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
备注信息	 	如果进行批量委托，则将第一笔委托的合同序号作为第二笔以后委托的业务序号
交易席位 : 卖出时送
资产账户为可选项,可以用不同的资产帐户作委托,不送时用股东的缺省帐户
交易行为包括: 
0B	买入
0S	卖出
4B	配股缴款
5S	转债转股
6S	转债回售
7B	新股申购
8B	新股缴款
9B	融资
9S	融券

*/
int TTrdItf_ZX::Buy()
{
	String market;
	switch (FRequest.Buy.SecuID[0])
	{
	case 'H' : market = _SH; break;
	case 'S' : market = _SZ; break;
	default: return -1;
	}

	String data;
	String acc;
	/*  if(  FRequest.QryStocks.Bourse == bsSH )
	acc = this->FAccInfo.SH ;
	else if( FRequest.QryStocks.Bourse == bsSZ )
	acc = this->FAccInfo.SZ ;
	*/
	//#ifdef _DEBUG//20051122
	if(FRequest.Buy.SecuID[0] == 'H' || FRequest.Buy.SecuID[0] == 'h')
		acc = this->FAccInfo.SH ;
	else if(FRequest.Buy.SecuID[0] == 'S' || FRequest.Buy.SecuID[0] == 's')
		acc = this->FAccInfo.SZ ;
	else
		return -1;
	//#endif
	if (FRequest.Buy.Type == 1)  // 申购赎回
	{
		data.printf("403|%s|%2s|%s|||%s|%2s|%.3f|%d||||",FUSER_CODE.c_str() ,market,acc.c_str(),
			FRequest.Buy.SecuID+1, "7K", FRequest.Buy.Price,FRequest.Buy.Num);

	}
	else
	{
		data.printf("403|%s|%2s|%s|||%s|%2s|%.3f|%d||||",FUSER_CODE.c_str() ,market,acc.c_str(),
			FRequest.Buy.SecuID+1, "0B", FRequest.Buy.Price,FRequest.Buy.Num);//20051122---404==>403,10.3f===>.3f

	}

	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 12;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			NewAns(1);
			strncpy((*FAnswer)[0].Buy.ContractID, lstDD->Strings[INDEX(fcount,0,2)].c_str(), 10);
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

	return 0;
}

int TTrdItf_ZX::Sell()
{
	String market;
	switch (FRequest.Sell.SecuID[0])
	{
	case 'H' : market = _SH; break;
	case 'S' : market = _SZ; break;
	default: return -1;
	}

	String data;
	String acc;
	/*  if(  FRequest.QryStocks.Bourse == bsSH )
	acc = this->FAccInfo.SH ;
	else if( FRequest.QryStocks.Bourse == bsSZ )
	acc = this->FAccInfo.SZ ;
	*/
	//#ifdef _DEBUG//20051122
	if(FRequest.Sell.SecuID[0] == 'H' || FRequest.Sell.SecuID[0] == 'h')
		acc = this->FAccInfo.SH ;
	else if(FRequest.Sell.SecuID[0] == 'S' || FRequest.Sell.SecuID[0] == 's')
		acc = this->FAccInfo.SZ ;
	else
		return -1;
	//#endif

	if (FRequest.Sell.Type == 1)  // 申购赎回
	{
		data.printf("403|%s|%2s|%s|||%s|%2s|%10.3f|%d||||",FUSER_CODE.c_str() ,market.c_str(),acc.c_str(),
			FRequest.Sell.SecuID+1, "7L", FRequest.Sell.Price,FRequest.Sell.Num);
	}
	else
	{
		data.printf("403|%s|%2s|%s|||%s|%2s|%10.3f|%d||||",FUSER_CODE.c_str() ,market.c_str(),acc.c_str(),
			FRequest.Sell.SecuID+1, "0S", FRequest.Sell.Price,FRequest.Sell.Num);//20051122----404==>403
	}


	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 12;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) == DEF_ACK_OK)
		{
			NewAns(1);
			strncpy((*FAnswer)[0].Sell.ContractID, lstDD->Strings[INDEX(fcount,0,2)].c_str(), 10);
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

	return 0;
}


/*
委托撤单(404)[支持三方交易]
功能代码	404
功能描述	委托撤单, 支持三方交易
请求数据	域名称	标识	类型及长度	必要	描述
交易市场	MARKET	CHAR(2)	Y	
合同序号	ORDER_ID	VARCHAR(10)	Y	委托返回的
返回数据	域名称	标识	类型及长度	描述

错误描述	错误代码	错误信息
420	无此委托
421	此委托不能撤单
422	此委托已撤单
310	操作失败
备注信息	

*/
int TTrdItf_ZX::Undo() //委托撤单
{
	String market;
	switch (FRequest.Undo.Bourse)
	{
	case bsSH : market = _SH; break;
	case bsSZ : market = _SZ; break;
	default: return -1;
	}

	String data;
	data.printf("404|%2s|%s",market.c_str(),FRequest.Undo.ContractID ) ;
	AnsiString cmd = GenCMD( data.Length(), data  );

	TStringList *lstDD = new TStringList();
	try
	{
		int fcount = 0;
		int reccount = 0;
		if (SplitData(ReadFirstData(cmd), lstDD,  fcount,reccount) != DEF_ACK_OK)
		{
			return -1;
		}
	}
	__finally
	{
		delete lstDD;
	}

	return 0;
}

int TTrdItf_ZX::GetRecvingDataLen(String &InputStr, String TrimStr)
{
	String sInputStr = InputStr;

	int nDataLen = 0;
	int nCurPos = 0;
	for(int i=0;i<2;i++)//应答包头结构: 头长度 CHAR(4),前面以字符‘0’填充;数据长度 VARCHAR(n),前面以字符‘0’填充
	{
		nCurPos = sInputStr.Pos(TrimStr);
		if(nCurPos <= 0 )
		{
			//if(sInputStr.IsEmpty())
			//  return 0;

			return 0;
		}

		nDataLen += sInputStr.SubString(1, nCurPos-1).ToIntDef(0);

		sInputStr.Delete(1, nCurPos);
	}

	return nDataLen;  
}

