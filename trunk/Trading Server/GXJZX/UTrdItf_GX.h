//---------------------------------------------------------------------------
#ifndef UTrdItf_GXH
#define UTrdItf_GXH
//---------------------------------------------------------------------------

#include "UTrdItfBase.h"
#include "UTrdStruct.h"
#include <windows.h>
#include "kcbpcli.h"
#include "KDEncodeCli.h"

#define GTJA_MAX_REC_NUM     "20"//查询每次最多返回记录数
#define GTJA_MAX_REC_NUM_INT  20 //此值必须与GTJA_MAX_REC_NUM值保持同步

#define PLUGINNAME "国信金正新一代"
typedef char * (* DOGSKIN_ENCODE)(const char *);
typedef int (* KDENCODE)(int nEncode_Level,
			  unsigned char *pSrcData, int nSrcDataLen, 
			  unsigned char *pDestData, int nDestDataBufLen, 
			  void *pKey, int nKeyLen);

class encode_dll_wrapper
{
private:
	CRITICAL_SECTION CS;
	HMODULE hDll1,hDll2;
	DOGSKIN_ENCODE DEncodeFun ;
	KDENCODE KEncodeFun;
protected:

public:
	encode_dll_wrapper()
	{
		InitializeCriticalSection(&CS);
		hDll1 = NULL;
		hDll2 = NULL;
		DEncodeFun=NULL;
		KEncodeFun=NULL;

		if( hDll1 ==NULL )
			hDll1 = LoadLibrary("Dogskin.dll");
		if(!hDll1)
		{
			ODS('E',PLUGINNAME,"Could not LoadLibrary Dogskin.dll!!");
		}

		DEncodeFun = (DOGSKIN_ENCODE)::GetProcAddress(hDll1, "Encode");
		if(!DEncodeFun)
		{
			ODS('E',PLUGINNAME, "Could not get the address of the Encode function!!!" );
		}

		if( hDll2 ==NULL )
			hDll2 = LoadLibrary("KDEncodeCli.dll");
		if(!hDll2)
		{
			ODS('E',PLUGINNAME,"Could not Load Library KDEncodeCli.dll!!");
		}

		KEncodeFun = (KDENCODE)::GetProcAddress(hDll2, "KDEncode");
		if(!KEncodeFun)
		{
			ODS('E',PLUGINNAME, "Could not get the address of the KDEncode function!!!" );
		}
	}

	~encode_dll_wrapper()
	{
		if(hDll1 )
		{
			  FreeLibrary(hDll1);
			  hDll1= NULL;
		}

		if(hDll2 )
		{
			  FreeLibrary(hDll2);
			  hDll2= NULL;
		}
		DeleteCriticalSection(&CS);
	}

	int Encrypt(char *pSrc, char *pDst,char *key,bool bencrypt)
	{
    	if( bencrypt )
		{
			if( DEncodeFun!=NULL )
			{
				strcpy(pDst, DEncodeFun((const char *)pSrc));
			}
			else return -1;
			//ODS('M',PLUGINNAME,"国泰加密,%s",pDst);
		}
		else
		{
			//key的内容
			//第一次登录是登录请求号
			//以后的登录就是客户号
			if( KEncodeFun!=NULL )
			{
				KEncodeFun(KDCOMPLEX_ENCODE,pSrc,strlen(pSrc),pDst,PWD_LEN+1,key,strlen(key));
			}
			else return -1;
			//ODS('M',PLUGINNAME,"金正默认加密,%s",pDst);
		}

		return 0;
	}

	void lock(void)
	{
		EnterCriticalSection(&CS);
	}

	void unlock(void)
	{
		LeaveCriticalSection(&CS);
	}
};

extern  encode_dll_wrapper _encode_dll;
//---------------------------------------------------------------------------
class TTrdItf_GX : public TTrdItfBase
{
public:
	typedef struct
	{
		char ServerName[KCBP_SERVERNAME_MAX+1];/*用户自定义的KCBP服务器名称*/
		//int nProtocal; /*协议类型，0 表示使用TCP*/
		char ServerAddr[KCBP_DESCRIPTION_MAX+1]; /*服务端IP*/
		unsigned int ServerPort;/*服务端端口号*/

		char DptCode[20];//营业部代码
		unsigned int Timeout;//连接超时20

		char UserName[20];
		char Password[20];
		char Operway;//操作方式
		char SendQName[20];///*发送队列名称，由服务端指定*/
		char ReceiveQName[20];///*接收队列名称，由服务端指定*/

		bool bencrypt;//是否加密密码

		// market code
		String SHA;
		String SZA;

		String MAC; // MAC地址
	} TGTJASet;
private:
	TGTJASet FGTJASet;
	KCBPCLIHANDLE FHandle;

	int SetSytemParams(char *Funid, bool IsLogin);
	int CheckSqlExecute(void);
	int CheckRsOpen(void);

	int InitRequest(char *Funid, bool IsLogin=false);
	int ExecuteRequest(char *Funid);//return:0--success,100--have more results,

	String FOrderDate;

	String FAccountType;
	TStrings *FSrcList, *FDstList;
	int QueryMoreResults(TStrings *pSrcList, TStrings *pDstList);

	char FEnPassword[255];
	int Encrypt(char *pSrc, char *pDst,char *key);

	char FCustid[50];
	int GetStkAccount(char *LogType, char *Logid, char *ZJ, char *SH, char *SZ);

	char FBankCode[100];
	char FExt1[33];
public:	// User declarations
    int  Init();  //初始化
    int  SetAccount(); //设置帐号

		//////查询函数//////
		int  QryMoney();     //资金查询
		int  QryCurCsn();    //当日委托查询
		int  QryCurTrd();    //当日成交查询
    int  QryStocks();    //查询帐号中所有的股份

    //////交易函数/////
		int  Order();
		int  Undo(); //委托撤单

		virtual market_type  ConvertMarketType(const char *t);
		virtual order_type   ConvertOrderType(const char *t);
		virtual order_state  ConvertOrderState(const char *t);
		virtual pos_direction ConvertPosDir(const char *t);
		virtual money_type   ConvertMoneyType(const char *t);
		virtual char *  ConvertMarketType(market_type t);
		virtual char *  ConvertOrderType(order_type t);
		virtual char *  ConvertOrderState(order_state t);
		virtual char *  ConvertPosDir(pos_direction t);
		virtual char *  ConvertMoneyType(money_type t);

		virtual void CloseLink(void);
		virtual int  KeepAlive(void);

		virtual bool GetConfig(void);
		virtual void SetConfig(void);

public:		// User declarations
		TTrdItf_GX(const char *psetupfile,ADDLOG plogfunc);
		virtual  ~TTrdItf_GX();
};

#endif
