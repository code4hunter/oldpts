//---------------------------------------------------------------------------
#ifndef UTrdItf_ZXH
#define UTrdItf_ZXH
//---------------------------------------------------------------------------
#include "UTrdStruct.h"
#include "UTrdItfBase.h"
#include <IdTCPClient.hpp>
#include <IdIPWatch.hpp>
//---------------------------------------------------------------------------

//?	日期格式为:YYYY-MM-DD 时间格式为:HH:MM:SS

/*
请求包和应答包处三列分别表示 "数据域名称"，"数据域标识"，"数据域类型"。
日期格式为:YYYY-MM-DD 时间格式为:HH:MM:SS
在请求包"数据域类型"处的最右边的'X'标志表示此数据域可不送,不需送时请以字符串空""送入。
所有的密码字段（交易密码，老密码，新密码，资金密码，银行密码）都必须使用
BlowFish加密算法加密后送入，加密时KEY为系统签入的"工作密钥"。

错误码	错误信息
101	通讯错误
110	尚未签入系统
111	无后续数据包
301	帐户登录失败
302	您的帐户状态不正常
303	磁卡号不存在
304	股东代码不存在
305	资产帐号不存在
306	用户代码不存在
307	交易市场不存在
308	修改密码失败
309	密码错误
310	操作失败
311	外部机构不存在
312	银行密码错
401	此股票不存在
402	您未作指定交易
403	此股不能进行此类委托
404	委托失败
405	可用金额不足
406	股票余额不足
420	无此委托
421	此委托不能撤单
422	此委托已撤单
501	无查询结果
502	查询失败
601	未开通银行转帐业务
602	未开通此银行转帐业务
603	该银行尚未开通该项业务
605	银行不存在
604	转帐失败
701	未开通存折炒股业务
801	重置成本失败
999	其它错误

*/

class TTrdItf_ZX : public TTrdItfBase
{
public:
	typedef struct
	{
		char   SvrIp[16];
		int    SvrPort;
		int    TimeOut;

		//1	电话委托
		//2	刷卡委托
		//3	热键委托
		//4	网上委托
		char   entrust_way;               //操作渠道
		char   branch_no[21];             //操作站点
		char   money_type;                //0	人民币

	} TZXSet;
	String GenCMD( int data_size, String data );
private:	// User declarations
	TIdTCPClient *FidTcp;
	TZXSet FZXSet;

	char FWorkKey[255];

	//用户代码"，"开户分支","会话序号
	String FUSER_CODE;
	String FBRANCH   ;
	String FSESSION  ;

	AnsiString GetErrorText(int code, char *error);
	AnsiString ReadNextData();
	AnsiString ReadFirstData(AnsiString cmd);
	int  SplitData(AnsiString SD, TStringList *lstDD, int &fieldcount,int &reccount);
        int GetRecvingDataLen(String &InputStr, String TrimStr="|");//20051121--

	int  Init();  //初始化
	int  SetAccount(); //设置帐号

	//////查询函数//////
	int  GetTrdInfo();   //取得盘口数据
	int  QryMoney();     //资金查询 -
	int  QryStock();     //股份查询
	int  QryCanBuy();    //取可买数量
	int  QryDetail();    //成交查询 -
	int  QryHisDetail(); //历史成交查询
	int  QryCsn();       //查询某个委托合同
	int  QryCurCsn();    //当日委托查询
	int  QryHisCsn();    //历史委托查询
	int  QryCurTrd();    //当日成交查询
	int  QryHisTrd();    //历史成交查询
	int  QryBill();      //查询资金流水（对帐单）
	int  QryStocks();    //查询帐号中所有的股份-

	//////交易函数/////
	int  Buy();      //-
	int  Sell();     //-
	int  Undo(); //委托撤单-

	virtual bs_type ConvertType(char * type)
	{
		if(strlen(type)>0)
		{
			if (strcmp(type,"0B")==0)
				return btBuy;
			else if (strcmp(type, "0S")==0)
				return btSell;
			else
			{
				if(type[0]=='1') return btBuy;
				else if(type[0]=='2') return btSell;
			}
		}

		return btNo;
	}

	virtual wt_state ConvertState(char *state)
	{
		if(lstrcmp(state,"已成交")==0)
			return wscj;
		else if(lstrcmp(state,"场内撤单")==0)
			return wsyc;
		else if(lstrcmp(state,"部分撤单")==0)
			return wsbw;
		else if(lstrcmp(state,"场外撤单")==0)
			return wsyc;
		else if(lstrcmp(state,"股票不足")==0)
			return wsyf;
		else if(lstrcmp(state,"未成交")==0)
			return wsyb;
		else if(lstrcmp(state,"已申报")==0)
			return wsyb;
		else if(lstrcmp(state,"撤单请求")==0)
			return wsdc;
		else if(lstrcmp(state,"撤单已发")==0)
			return wsdc;
		else
			return wsno;
	}
public:		// User declarations
	TTrdItf_ZX(TZXSet *set);
	virtual  ~TTrdItf_ZX();
	void CloseLink(void)
	{
		FidTcp->Disconnect();
    TTrdItfBase::CloseLink();
	}

};

#endif
