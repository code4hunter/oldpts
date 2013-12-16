#ifndef cjhb_rec_h
#define cjhb_rec_h


#define GDDM_LEN 11
typedef char GDDM[GDDM_LEN];


#pragma pack(1)
//成交回报记录

//cjbh	Int		4	成交编号。
//gddm	Char	10	股东帐号，首字符为大写字母。
//bcrq	Char	8	成交日期。格式：YYYYMMDD
//cjsl	Char	10	成交数量。不以正负表示买卖方向。
//bcye	Char	10	本次余额。成交过户后的余额。
//zqdm	Char	6	证券代码。
//sbsj	Char	6	申报时间。格式为:HHMMSS
//cjsj	Char	6	本次成交时间。格式为:HHMMSS
//cjjg	Char	8	本次成交价格。
//cjje	Char	12	本次成交金额。
//sqbh	Char	10	同ashare_ordwth中对应记录的reff字段。
//bs	Char	1	同ashare_ordwth中对应记录的bs字段。

struct cjhb_rec
{
	long	no;				//成交编号
	char	gddm[GDDM_LEN];	//股东代码
	long	date;			//YYYYMMDD
	long	deal_num;		//成交数量
	long	stk_bal;		//过户后股票余额
	char	code[7];
	long	ord_time;		//HHMMSS
	long	deal_time;		//HHMMSS
	float	deal_price;
	double	deal_money;		//成交金额
	char	ord_id[11];		//委托号
	char	bs;				//B代表买入，S代表卖出, C 代表撤买单, T 代表撤卖单
							//假如为撤单则deal_num为撤单量
};

enum CJHBFUNC 
{ //功能类型
	ftLogin        = 0,  //登陆
	ftLogout	   = 1   //注销
};

struct cjhb_login_req
{
	int  type;			//1 上交所A,2 深交所A.... 目前只支持1
	char gdzh[20];		//股东账号 
};

struct cjhb_req
{
	int FuncType;
	union
	{
		cjhb_login_req login;	
		cjhb_login_req logout;	
	};
};

struct clhb_ans
{
	int AnsCount; //回复数据包个数
	int CurAnsNo; //当前回复数据包序号
	int RetVal;   //返回值,'0'为正确
	union
	{
		cjhb_rec cr;
	};
};

#pragma pack()

#endif