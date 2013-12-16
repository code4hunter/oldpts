//---------------------------------------------------------------------------
#ifndef UTrdItf_JSDFFH
#define UTrdItf_JSDFFH
//---------------------------------------------------------------------------
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdIPWatch.hpp>
#include "UTradeDB.h"

#include "UTrdItfBase.h"
//---------------------------------------------------------------------------
#define DEF_HEAD_LEN            3
#define INDEX(n) (n + DEF_HEAD_LEN - 1)
#define PLUGINNAME "金仕达期货V1.14"

#define DEF_ACK_OK              0
#define DEF_ACK_ERROR           -1
#define DEF_TIMEOUT             -100
#define DEF_INVALID_STOCKCODE   -101
#define DEF_OTHER_ERROR         -504
#define REQUEST_NUM " "

long convert_datetime_str_to_long(const char * str);
order_type  SConvertOrderType(const char *t);

class TTrdItf_JSDFF : public TTrdItfBase
{
public:

	typedef struct
	{
		AnsiString   SvrIp;
		int          SvrPort;
		int          TimeOut;                     //读取超时
		bool         debug_mode;
		AnsiString   branch_no;                   //营业部代码
		AnsiString   gw_ver;                      //V6还是V5。。
		char         jysID[5];                    //交易所代码4个期货交易所（依次，郑州，大连,上海,金融期货）
		AnsiString   seatID[4];                   //席位号    自动获得
		AnsiString   JyCode[4];                   //交易编码  自动获得
		AnsiString   sysCenter;             	  //系统中心号
	} TJSDSet;

private:	// User declarations
	TIdTCPClient *FidTcp;
	TIdIPWatch   *FidIPWatch;
	TJSDSet       FJSDSet;
	//trade_db      FDB;

	AnsiString GetRequestHead(AnsiString FuncNo);
	AnsiString GetErrorText(int code, const char *error);
	void SetError(int code,const char * error);
	AnsiString ReadNextData();
	AnsiString ReadFirstData(AnsiString cmd);
	int  SplitData(AnsiString SD, TStringList *lstDD, int count);

	inline void DeStr(AnsiString Sour,TStringList* strList,AnsiString DivSign)
	{
		long n= Sour.Length();
		for ( int i=1; i<=n ;i++)
		{
			if( Sour[i] == DivSign[1] )
			{
				Sour[i] = '\r';
			}
		}
		strList->Text = Sour;
	}

public:		// User declarations
	TTrdItf_JSDFF(const char *psetupfile,ADDLOG plogfunc);
	virtual  ~TTrdItf_JSDFF();

	int Init();  //初始化
	int SetAccount(); //设置帐号

	//////查询函数//////
	int QryMoney(); 	//资金查询
	int QryCurCsn();	//当日委托查询
	int QryCurTrd();	//当日成交查询
	int QryStocks();	//查询帐号中所有的股份
	int Order();
	int Undo(); 		//委托撤单

	virtual market_type  ConvertMarketType(const char *t);

	virtual order_type   ConvertOrderType(const char *t);

	virtual order_state  ConvertOrderState(const char *t);

	virtual pos_direction ConvertPosDir(const char *t);

	virtual money_type   ConvertMoneyType(const char *t);

	virtual char *  ConvertMarketType(market_type t);

	virtual char *  ConvertOrderType(order_type t);

	virtual char *  ConvertOrderState(order_state t)
	{
		return "";
	}

	virtual char *  ConvertPosDir(pos_direction t)
	{
		return "";
	}

	virtual char *  ConvertMoneyType(money_type t)
	{
    	return "";
	}

	//将配置信息读出来,如果没有获取完整的配置信息返回false
	virtual bool GetConfig(void);
	//将配置信息回写到配置文件
	virtual void SetConfig(void);
	//关闭中间件链接
	virtual void CloseLink(void);

	AnsiString GetTradeCode(market_type t)
	{
		switch(t)
		{
			case mtFZZ : return FJSDSet.JyCode[0];
			case mtFDL : return FJSDSet.JyCode[1];
			case mtFSH : return FJSDSet.JyCode[2];
			case mtJJS : return FJSDSet.JyCode[3];
		}
		return "";
	}

	AnsiString GetSeatId(market_type t)
	{
		switch(t)
		{
			case mtFZZ : return FJSDSet.seatID[0];
			case mtFDL : return FJSDSet.seatID[1];
			case mtFSH : return FJSDSet.seatID[2];
			case mtJJS : return FJSDSet.seatID[3];
		}
		return "";
	}

	void splitOrdid(const char *ordid,AnsiString &seat,AnsiString &oldordid)
	{
		seat = "";
		oldordid = "";
		int len = strlen(ordid);
		char ret[100];
		ret[0]=0;
		int j=0;
		for(int i=0;i<len;i++)
		{
			if( ordid[i] == ':')
			{
				ret[j++] = 0;
				seat = ret;
				oldordid= ordid+i+1;
			}
			else
				ret[j++]=ordid[i];
		}
	}

	static long MyStrToInt(AnsiString  s)
	{
		s = s.Trim();
		if (s.Length()==0) {
			return 0;
		}
		else return s.ToInt();
	}

	static double MyStrToFloat(AnsiString s)
	{
    	s = s.Trim();
		if (s.Length()==0) {
			return 0.0;
		}
		else
			return s.ToDouble();
	}

	static AnsiString convert_to_PTS_code(const char * jsdcode,market_type mt);
	static AnsiString convert_to_JSD_code(const char * ptscode,market_type mt);

	int QryYYB(void);
	virtual int  KeepAlive(void);
};

#endif
