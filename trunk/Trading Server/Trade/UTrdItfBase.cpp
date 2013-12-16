//------------------------------------------------------------------------------
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <TCHAR.h>
#include <assert.h>
#include <SysUtils.hpp>
#include <math.h>
#include "UTrdItfBase.h"

#define CHECKSTR(str) (str[sizeof(str)-1]=0)
//---------------------------------------------------------------------------

TTrdItfBase::TTrdItfBase(const char *psetupfile,ADDLOG plogfunc)
{
	InitializeCriticalSection(&CS);
	if( psetupfile!= NULL )
		strncpy(FSetupFile,psetupfile,MAX_PATH);
	else
		FSetupFile[0]=0;

	set_addlog_callback(plogfunc);

	FHasSetAccInfo = false;
	memset(&FAccInfo,0,sizeof(TAccountInfo));
	FBufCount=100; //预留100个缓存
	FAnsBuf=new TAnswer[FBufCount];

	FLastError.Sender[0] = 0;
	FLastError.ErrorCode = 0;
	FLastError.Text[0]=0;
	FSetAccRequest.Head.FuncType =  -1;
}
//---------------------------------------------------------------------------
TTrdItfBase::~TTrdItfBase()
{
	delete[] FAnsBuf;
	DeleteCriticalSection(&CS);
}

void TTrdItfBase::lock(void)
{
	EnterCriticalSection(&CS);
}

void TTrdItfBase::unlock(void)
{
	LeaveCriticalSection(&CS);
}

char * TTrdItfBase::GetStockAccountByType(account_type at)
{
	switch (at)
	{
	case asSHA:return FAccInfo.SH;
	case asSZA:return FAccInfo.SZ;
	case asJJS:return FAccInfo.FJJS;
	case asFDL:return FAccInfo.FDL;
	case asFZZ:return FAccInfo.FZZ;
	case asFSH:return FAccInfo.FSH;
	case asCA: return FAccInfo.Capital;
	}
	return "";
}

void TTrdItfBase::SetAccountByType(account_type at,const char* account,const char* pwd)
{
	this->FAccInfo.lt = at;
	lstrcpyn(this->FAccInfo.PW,pwd,PWD_LEN);

	switch (at)
	{
	case asSHA:lstrcpyn(FAccInfo.SH,account,ACC_LEN);break;
	case asSZA:lstrcpyn(FAccInfo.SZ,account,ACC_LEN);break;
	case asJJS:lstrcpyn(FAccInfo.FJJS,account,ACC_LEN);break;
	case asFDL:lstrcpyn(FAccInfo.FDL,account,ACC_LEN);break;
	case asFZZ:lstrcpyn(FAccInfo.FZZ,account,ACC_LEN);break;
	case asFSH:lstrcpyn(FAccInfo.FSH,account,ACC_LEN);break;
	case asCA: lstrcpyn(FAccInfo.Capital,account,ACC_LEN);break;
	}
}

char * TTrdItfBase::GetStockAccountByMarket(market_type mt)
{
	switch (mt)
	{
	case 	mtSHA  :return FAccInfo.SH;
	case 	mtSZA  :return FAccInfo.SZ;
	case 	mtJJS :return FAccInfo.FJJS;
	case 	mtFDL :return FAccInfo.FDL;
	case 	mtFZZ :return FAccInfo.FZZ;
	case 	mtFSH :return FAccInfo.FSH;
	case  mtNo  :return "";
	}
	return "";
}

void TTrdItfBase::SetLogout(void)
{
	lock();
	FHasSetAccInfo=false;
	unlock();
}

bool TTrdItfBase::AutoLogin(void)
{
	if( FHasSetAccInfo == false )
	{
		if( FSetAccRequest.Head.FuncType == ftSetAccount )
		{
			this->CloseLink();
			if( Init()== 0 )
			{
				if( SetAccount(true)==0 )
				{
                	FHasSetAccInfo = true;
                }
			}
        }
	}

	return FHasSetAccInfo;
}
//---------------------------------------------------------------------------
int  TTrdItfBase::Request(TRequest &Request,TAnswer **Answer,int &AnsCount)
{
	int retVal = -1;
	try
	{
		lock();
		memcpy( &FRequest,&Request,sizeof(TRequest));
		//FRequest   = Request;   //申请
		FAnswer    = Answer;    //回复
		*FAnswer   = FAnsBuf;
		FAnsCount  = &AnsCount; //回复数量
		*FAnsCount = 0;

		try
		{
			switch(Request.Head.FuncType) {
		case ftInit:
			{
				FHasSetAccInfo = false;
				FLastError.Sender[0] = 0;
				FLastError.ErrorCode = 0;
				FLastError.Text[0]=0;
				if( GetConfig() == false )
					SetConfig();
				retVal = Init();
				break;
			}
		case ftSetAccount:
			{
				CHECKSTR(Request.SetAccount.Account);
				CHECKSTR(Request.SetAccount.PW);
				retVal = SetAccount();
				if(retVal==0)
				{
					CHECKSTR(FAccInfo.Capital);
					CHECKSTR(FAccInfo.SH);
					CHECKSTR(FAccInfo.SZ);
					memcpy(&FSetAccRequest,&Request,sizeof(Request));
					FHasSetAccInfo = true;
				}
				else
					FHasSetAccInfo = false;
				break;
			}
		case ftGetAccount:
			{
				retVal = GetAccountInfo();
				break;
			}
		case ftQryMoney:     { if(AutoLogin()) { retVal = QryMoney(); }     break; }
		case ftQryCurCsn:    { if(AutoLogin()) { retVal = QryCurCsn(); }    break; }
		case ftQryCurTrd:    { if(AutoLogin()) { retVal = QryCurTrd(); }    break; }
		case ftQryStocks:    { if(AutoLogin()) { retVal = QryStocks(); }    break; }
		case ftOrder:        { if(AutoLogin()) {
			CHECKSTR(Request.Order.SecuID);
#ifdef TRACEORDER
			ODS('M',"--委托--","资金帐号:%s,代码:%s,价格:%f,量:%d,市场:%c,类型:%c",
				FAccInfo.Capital,
				Request.Order.SecuID,
				Request.Order.Price,
				Request.Order.Num,
				Request.Order.Market,
				Request.Order.Type);
#endif
			retVal = Order();
							 } break; }
		case ftUndo:         { if(AutoLogin()) {
			CHECKSTR(Request.Undo.ContractID);
			retVal = Undo(); }         break; }
		case ftGetLastErr:   { retVal = GetLastError(); break; }
			}
		}
		__finally
		{
			unlock();
		}
	}
	catch( Exception &e )
	{
		ODS("请求过程中异常错误,Function=%d,Error=%s",Request.Head.FuncType,e.Message);
		if( Request.Head.FuncType == 1 )
		{
			ODS("Account= %s,pass=%s,type=%d", Request.SetAccount.Account ,
				Request.SetAccount.PW,
				Request.SetAccount.LoginType) ;
        }
	}
	catch( ... )
	{
		ODS("请求过程中未知错误,Function=%d",Request.Head.FuncType);
	}

	return retVal;
}
//---------------------------------------------------------------------------
int TTrdItfBase::GetAccountInfo(void)
{
	if(FHasSetAccInfo)
	{
		NewAns(1);
		memcpy(&( *FAnswer )[0].GetAccount.AccountInfo ,&FAccInfo,sizeof(TAccountInfo));
		return 0;
	}
	else return -1;
}

void  TTrdItfBase::NewAns(int AnsCount)
{
	*FAnsCount = AnsCount;

	if(FBufCount<AnsCount)
	{
		delete[] FAnsBuf;
		FAnsBuf=new TAnswer[AnsCount];

		FBufCount=AnsCount;
		*FAnswer=FAnsBuf;
	}

	assert((FAnswer)!=NULL);

	for(int i=0;i<AnsCount;i++)
	{
		memset(&(*FAnswer)[i],0,sizeof(TAnswer));
		(*FAnswer)[i].Head.AnsCount = AnsCount;
		(*FAnswer)[i].Head.CurAnsNo = i+1;
		(*FAnswer)[i].Head.RetVal   = 0;
	}
}

bool  TTrdItfBase::SetAnsCount(int AnsCount)
{
	if(FBufCount<AnsCount)
	{
		return false;
	}

	*FAnsCount = AnsCount;

	for(int i=0;i<AnsCount;i++)
	{
		(*FAnswer)[i].Head.AnsCount = AnsCount;
		(*FAnswer)[i].Head.CurAnsNo = i+1;
		(*FAnswer)[i].Head.RetVal   = 0;
	}
	return true;
}
//---------------------------------------------------------------------------

int  TTrdItfBase::FreeAnswer(TAnswer *as)
{
	return 1;
}

int  TTrdItfBase::GetLastError()
{
	if( FLastError.ErrorCode != 0 )
	{
		NewAns(1);
		( *FAnswer )[0].GetLastError.Error.ErrorCode = FLastError.ErrorCode;
		lstrcpyn(  ( *FAnswer )[0].GetLastError.Error.Sender,FLastError.Sender,SEQ_LEN);
		lstrcpyn(  ( *FAnswer )[0].GetLastError.Error.Text,FLastError.Text,MAX_TEXT);
	}
	return 0;
}

void TTrdItfBase::CloseLink(void)
{
	FHasSetAccInfo = false;
	FLastError.Sender[0] = 0;
	FLastError.ErrorCode = 0;
	FLastError.Text[0]=0;
}

//支持 hh:mm:ss,hhmmss
//不支持h:m:s
long TTrdItfBase::ConvertTimeToInt(const char *t )
{
	if( t==NULL || strlen(t) < 1 ) return 0;
	char sztmp[100];
	int j=0;
	for( int i=0 ;i<20;i++ )
	{
		if (t[i] == 0 )
			break;

		if( isdigit(t[i]) )
		{
			sztmp[j++] = t[i];
		}
	}
	if( j==7 || j==8 )
		sztmp[j-2] = 0; //去掉后面两位
	else
		sztmp[6]=0;     // 去掉多出的字符，使其保持6位
	return atoi(sztmp);
}

//支持 yyyymmdd,yyyy-mm-dd,yyyy/mm/dd等形如yyyy#mm#dd,#为任何非数字字符
//不支持y#m#d如1900-1-1将无法转换
long TTrdItfBase::ConvertDateToInt(const char *t )
{
	if( t==NULL || strlen(t) < 1 ) return 0;
	char sztmp[100];
	int j=0;
	for( int i=0 ;;i++ )
	{
		if (t[i] == 0 )
			break;
		if( isdigit(t[i]) )
		{
			sztmp[j++] = t[i];
		}
	}
	sztmp[8] = 0;  // 去掉多出的字符，使其保持8位
	return atoi(sztmp);
}

void TTrdItfBase::SetLastError(int code,TCHAR type ,const TCHAR* sender,const TCHAR * fmt,...)
{
	va_list		argptr;
	TCHAR		text[1024];

	va_start (argptr, fmt);
#ifdef MSCRT8
	_vstprintf_s(text,1023, fmt, argptr);
#else
	_vsntprintf(text,1023, fmt, argptr);
#endif
	va_end (argptr);

	ODS("#%c#%s#%s",type,sender,text);

	lstrcpyn(FLastError.Sender,sender,SEQ_LEN);
	FLastError.ErrorCode = code;
	lstrcpyn(FLastError.Text,text,MAX_TEXT);
}
