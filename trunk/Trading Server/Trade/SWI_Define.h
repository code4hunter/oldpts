#ifndef SWI_DEFINE_H
#define SWI_DEFINE_H

/*
参：申银万国外围交易系统协议接口标准
V2.76版
For
External Application Gateway (AG-X) 
通信协议标准


一·  数据字典
1、客户帐号类别 account_type
'0' ------  A股资金帐号
'1' ------ 上A证号
'2' ------ 深A证号
'3' ------ 上B证号（小于等于6位，表示上海B股资金帐号）
'4' ------ 深B证号（小于等于6位，表示深圳B股资金帐号）
'5'  ------  A股特别转让市场证号
'6' -----  B股特别转让市场证号(小于等于6位，表示资金帐号)

注：
（1）	使用6位资金帐号（十位资金帐号的前4位营业部编号，由客户端分离后放入消息头的dest_dpt，分离后的6位资金帐号需全部去除左边顶格的"0"）。
（2）	"客户帐号类别"除201 委托、202撤单可以使用资金账号或证券帐号外，其余功能调用必须使用资金账号。

2、委托方式 entrust_method
由开发商向申万索取。
注：
有两个特殊委托方式定义如下：
（1）	'z'  用于交割打印，"打开帐号"调用时客户密码不校验
（2）	'Z'  用于交割打印，"打开帐号"调用时客户密码要校验

3、买卖类别  bs_type
'1' ----- 买入（包括开放式基金/LOFs的认购、申购/ETFs的申购）
'2' ----- 卖出（包括开放式基金/LOFs的赎回/ETFs的赎回）
'3' ----- 转托管（深圳）
'4' ----- 配股（深圳）
'5' ----- 撤买 (查询结果中出现，发出撤单请求应该用专用撤单调用)
'6' ----- 撤卖 (查询结果中出现)
'7'----- 认购（开放式基金）
'8'  -----转股（用于录入委托，查询结果中不出现）
'a'   ----  红利（用于交割）
'b'  ----  手续费（用于交割）
     
4、交易所编号 exchange_no
0 ----- 全部A股（仅用于查询）
1 ----- 上海A股
2 ----- 深圳A股
3 ----- 上海B股
4 ----- 深圳B股
5 ----- A股特别转让市场
6 ----- B股特别转让市场
7 ----- 开放式基金

5、委托状态  entrust_status？？（确定状态）
'L' ----- 委托取消
'l' ------ 委托临时状态（小写L）
'0' ----- 未申报
'1' ----- 待申报
'2' ----- 已申报
'4' ----- 无效委托
'5' ----- 部分撤单
'6' ----- 已撤单
'7' ----- 部分成交
'8' ----- 已成交

6、币种 currency_type
'1' ----- 人民币
'2' ----- 美圆
'3' ----- 港币

7、金额用8字节SQLMONEY来表示，内部表示为__int64，其十进制后四位代表四位小数, 如￥12.32  表示为 123200
typedef struct _SWIMoney    // Same as the type CURRENCY in VB
{
		DWORD lo_value;
		long  hi_value;
} SWIMoney;

注意： 对开放式基金的委托或查询返回股票数量(fund_amount，使用SWIMoney来表示)，其十进制后4位代表4位小数，如1000000.12表示为10000001200。

8、价格使用LONG来表示，其十进制后三位代表三位小数，如8.18表示为8180
typedef long	 SWISmallMoney;

9、帐号状态
10、客户类别
11、证券类别
'0'          配股缴款  
'1'          普通Ａ股  
'2'         基金      
'3'          红利      
'4'          投资基金  
'5'          转债      
'6'          特别转让  
'7'          分销国债  
'8'          新股申购  
'9'          国债(实券)
'a'          登记指定  
'b'          撤消指定  
'c'          国债回购  
'd'          国债(计帐)
'f'          市值申购  
'g'          回购登记  
'h'          回购撤消  
'i'          沪债转股  
'j'          企业债券
'k'          LOF交易
'l'          LOF/ETF发行
'm'         ETF交易
'n'          ETF申购/赎回

 
12、买卖类别补充bs_type2
对于一些查询或交割的返回结果集，无法通过目前"买卖类别bs_type"定义区分一些业务，新定义"买卖类别补充bs_type2"如下：
1         	买入
2		卖出
40		融券
41		融资购回
42		融券反售
43		融资
  其他------------待定，以后协议中对外公布
  特别注意：
本数据字典，目前只适用于"功能号0x505 查询交割单"。

13、ＤＥＳ加密算法说明
本接口中使用DES算法的源代码和申银万国外围交易系统协议接口一致，包括des.cpp、dll.h、crc.c；使用方法示意如下： 
desinit(0); 
dessetkey("8位长度密钥"); 
endes(char * block)；      //对block加密
dedes(char *block);  //对block解密 
desdone();
DES算法的源代码由营业部经电脑网络中心批准后提供给开发商。

14、证券组别
'1'          国债
'2'          基金
'3'          A股
'4'          回购

二· 安全性措施
在交换密钥之后，采用DES加密

三· 外部委托网络协议接口

说明:
	1. 客户端应用采用面向连接的网络协议 TCP 或 SPX 连接到申万交易网关
	2. 申万交易网关确省侦听端口
		TCP Listen socket: 18888
		SPX Listen socket: 18888

四, 外部委托网络协议接口开发包
	SWI Software Development Kit

	SWINDR.H   ---  网络数据流定义头文件
	SWIRES.H   ---  结果集定义头文件
*/

// 结构成员应字节对齐
#pragma pack(push, 1)

typedef long	SWISmallMoney;
typedef struct _SWIMoney
{
        DWORD lo_value;
        long  hi_value;
} SWIMoney;

//消息头
struct SWI_BlockHead
{
        WORD    block_size;
        WORD    crc;  		// 从下个字段block_type起 (不包括block_size和
                                // crc字段本身) 的CRC校验码
        BYTE     block_type;  	// 块类型  	1 - 请求         （SWI_???Request）
                                                //         	2 - 返回状态     （SWI_???Return）
                                                //          	3 - 查询结果行   （SWI_???Result）
                                                //          	5 - 取消查询
                                                //          	4 - 警报信息
                                                //          	5 - 网络对话
                                                //          	6 - 连接请求(交换密钥)
                                                //          	7 - 连接应答(交换密钥)
                                                //          	8 - 扩展请求消息
                                                //          	9 - 扩展应答消息
        BYTE   reserved1;    	// 保留，必须置0
        WORD   function_no;  	// 功能号
        long   cn_id;      	// 网关连接号
        WORD   source_dpt;      // 保留，内部使用（原营业部）
        WORD   dest_dpt;    	// 目的营业部编号
};

// 查询结果集通用头
struct SWI_QueryResultHead
{
	struct SWI_BlockHead head;
	WORD   row_no;
};

// 查询返回集通用头
struct SWI_QueryReturnHead
{
	struct SWI_BlockHead head;
	long return_status;//返回状态
};

//客户端发出"连接请求"消息
struct SWI_ConnectRequest
{
	SWI_BlockHead  head;    	// 消息头 block_type == 6
        WORD  method;     	   	// 客户端的加密方式（method=1）
        char  entrust_method;   	// 委托方式（见数据字典说明）
        BYTE  return_cp;        	// 客户端希望的返回结构中中文字段的代码页
                                        //   	0 -- MBCS  （CP936简体中文）
                                        //   	1 -- Unicode(Java客户需要)
        BYTE   network[4];      	// 客户端Novell网段号
        BYTE   address[6];      	// 客户端网卡地址（Novell节点地址）
        WORD   client_major_ver;	// 客户端协议接口主版本号（用于版本协商）
        WORD   client_minor_ver;// 客户端协议接口次版本号（用于版本协商）
        WORD   key_length;      // RSA密钥长度（对method 1, key_length=0）
};

//消息头中：
//block_type	6 - 连接请求(交换密钥)
//function_no  	忽略
//cn_id      	0
//dest_dpt    	忽略

//服务器端"连接应答"消息
struct SWI_ConnectResponse
{
        SWI_BlockHead  head;    	// 消息头 block_type == 7
        WORD return_value;		// 返回状态
        WORD method;             // 网关同意的加密方式
        char department_name[60];// 营业部名称（MBCS/Unicode）
        WORD key_length;         // DES密钥长度（key_length=8）
        BYTE des_key[8];         // DES密钥(请用"ExpressT"作为密钥des解密)
};
//消息头中：
//block_type	7
//function_no  	忽略
//cn_id      	分配到的连接标识，客户端应缓存此连接标识，用于填充后续请求  中的相应字段
//dest_dpt    	本地营业部编号

/*注：
1. 当前企业网内应用，规定密钥交换采用method == 1。服务器端生成一个随机的DES密钥，在连接应答中发送到客户端，以后的通信内容均采用DES加密。

2. 跨营业部(通买通卖)交易请求处理，从校验股民交易密码调用起在head的dest_dpt中指定客户指定交易所在营业部编号，（本营业部也可用0表示）。 但因为协商加密方式时客户端应用程序尚不知道客户帐号和所在营业部，所以SWI_ConnectRequest中dest_dpt不需指定。

3．约定请求中dest_dpt为目的营业部编号（客户指定交易所在营业部），应答中的dest_dpt为本地营业部编号（客户端应用程序直接连接的网关所在营业部）
*/

/*其他约定
为了实现"应用程序版本统计"工作，要求每个应用程序在启动时完成以下工作：
1、	与AGX建立网络连接，发送连接请求包。
2、	调用"功能号0x801"SWI_QueryCommon，参数如下：
     SWI_BlockHead.cn_id=0(????,建立连接后)
       function_id=1
       cmd_buf="产品名称|开发商|版本号|升版日期"
       返回：100成功  〈=0失败
*/

/*
//请求消息
struct SWI_QueryCommon
{
	struct SWI_BlockHead head;		// function_no = 0x801,block_type=1
	long   function_id;         		// 子功能号（见定义）
	char   cmd_buf[4096];     		// 查询条件（数据项之间以"|"分割）
};
//应答结果集
struct SWI_QueryCommonResult
{
	struct SWI_BlockHead head;	    // function_no==0x801,block_type==3
	WORD    row_no;                  // 记录号
	//short   len;                     //查询结果的长度
        //char    ret_buf[len];           //查询结果（数据项之间以"|"分割）
};
//RETURN应答
struct SWI_QueryCommonReturn
{
	struct SWI_BlockHead head; 		// function_no = 0x801,block_type==2
	long return_status;
};
//返回状态:
//  > 0   查询成功
//  <= 0  查询失败

*/

//功能号高字节表示功能大类：
//1 --- 帐号操作
//2 --- 交易
//3 --- 单条结果查询
//4 --- 当天多结果集查询
//5 --- 历史多结果集查询
//6 --- 查证券信息
//9 --- 辅助操作

//////////////////////////////////////////////////////////////////////////
//1、功能号0x101 校验股民交易密码, 打开帐号 SWI_FUNC_OPEN_ACCOUNT
//  调用此功能，如校验股民交易密码通过，该客户的帐号将处于允许交易的打开状态，
//  直到下列情况之一发生：
//	1．该连接调用功能20关闭帐号
//	2．该连接调用下一次功能2，打开另一个帐号
//	3．该连接关闭。
//////////////////////////////////////////////////////////////////////////

//请求消息
struct SWI_OpenAccountRequest
{
        struct SWI_BlockHead head;	// function_no==0x101, block_type == 1
        char   account_type;     	// 客户帐号类型（见数据字典说明）
        char   account[16];      	// 客户帐号
        char   pwd[8];           	// 交易密码
        short  op_code;             // 操作员工号
        unsigned  long   flag;         //"特殊条件"判断标志位组合,每一个二进制位对应一个"特殊条件",缺省值为0表示不判断任何"特殊条件"
        char   productno [7];		    //产品信息编号：5位电脑网络中心产品编码+2位子产品编码（共7位字符）；缺省值为空。

};

/*目前已定义flag的"特殊条件"判断，列表如下：
      二进制位         对应的十六进制数       对应的特殊条件         对应的返回状态
        1               0x0001              不允许使用"简单密码"     -159
        2               0x0002              未定义                   无
        3               0x0004              未定义                   无
        4               0x0008              未定义                   无
        5               0x0010              未定义，。。。           无

对跨营业部(通买通卖)交易请求，
在head中 dest_dpt中指定客户指定交易所在营业部编号（下同）。
*/
//应答消息
struct SWI_OpenAccountReturn
{
	struct SWI_BlockHead head; 	// function_no==0x101
	long    return_status;  	// 返回状态
};

//返回状态：
//  >  0  成功
//  <= 0  失败
//注：如果返回状态为-159，则说明用户输入的为简单密码

//////////////////////////////////////////////////////////////////////////
//
//4· 功能号0x201 录入委托SWI_FUNC_ADD_ENTRUST
//功能： 录入外部委托，资金与股票不允许透支
//
//////////////////////////////////////////////////////////////////////////
//请求消息
struct SWI_AddEntrustRequest
{
	struct SWI_BlockHead head;// function_no == 0x201, block_type==1
	char    account_type;     // 客户帐号类型（见数据字典说明）
	char    account[16];      // 客户帐号
	BYTE    exchange_no;      // 交易所编号（见数据字典说明）
	char    bs_type;          // 买卖类别（见数据字典说明）
	char    security_code[7]; // 证券代码
	long    stock_amount;     // 委托数量
	SWISmallMoney price;      // 委托价格（SWISmallMoney见数据字典说明，下同）
	short   effect_days;      // 有效天数 
        SWIMoney   apply_amount;  //申请金额
        BYTE    mark;             //是否连续赎回 1为连续赎回,0为非连续 确省为0
        int	Frozen_no ;        //证券端资金冻结流水号(银证通专用，缺省为0)
        SWIMoney fund_amount;  //委托数量(支持开放式基金小数份额)
        char    Entrust_sign[10]; //交易签名(缺省为'')
        SWIMoney    Cash_limit ;  //委托资金额度（缺省为0表示不控制委托资金额度;否则委托冻结资金超过委托资金额度时本笔委托失败,B股暂不控制）
};
/*
注意 
1）：要求外围发送请求时"委托数量"的数值和"委托数量(支持开放式基金小数份额)"
的整数部分必须相等，否则认为委托无效。
2）：对开放式基金的委托或查询返回股票数量(fund_amount，使用SWIMoney来表示)，
其十进制后4位代表4位小数，如1000000.12表示为10000001200，下同。
*/
//应答消息
struct SWI_AddEntrustReturn
{
	struct SWI_BlockHead head;
	long return_status;   	      	//  返回状态
	long entrust_sn;      		//  委托编号
        SWIMoney  frozen_money;    	//冻结资金金额
        long     frozen_amount;    	//冻结证券数量
};
//返回状态：
//  >  0  成功
//  <= 0  失败

///////////////////////////////////////////////////////////////////////////////
//
//5· 功能号0X202 撤单SWI_FUNC_WITHDRAW
//
//////////////////////////////////////////////////////////////////////////////
// 请求消息
struct SWI_WithdrawEntrustRequest
{
	struct SWI_BlockHead head; // function_no == 0x202, block_type==1
	char    account_type;      // 客户帐号类型
	char    account[16];       // 客户帐号
	BYTE    exchange_no;       // 交易所编号
	long    entrust_sn;        // 委托编号
};

//应答消息
struct SWI_WithdrawEntrustReturn
{
	struct SWI_BlockHead head; // function_no == 0x202, block_type==1
	long return_status;        // 返回状态
        long withdraw_sn;          //撤单编号
};
//返回状态：
//>0  ------ 撤单接受
//<=0 ------ 撤单失败

//////////////////////////////////////////////////////////////////////
//
//7· 0x301 查询资金余额 SWI_FUNC_QUERY_MONEY
//
//////////////////////////////////////////////////////////////////////

// 请求消息
struct SWI_QueryMoneyRequest
{
	struct  SWI_BlockHead head; // function_no == 0x301,block_type==1
	char    account_type;      // 客户帐号类型
	char    account[16];       // 客户帐号
	char    currency_type;     // 币种
};

//应答消息
struct SWI_QueryMoneyReturn
{
	struct	  SWI_BlockHead head; //function_no == 0x301,block_type==2
	long	  return_status; // ------ 返回状态
	char      name[20];   // ------ 股东姓名
	SWIMoney  deposite;   // ------ 入帐资金余额
	SWIMoney  available;  // ------ 可取资金余额
	SWIMoney  buyable;    // ------ 可买资金余额
};
//返回状态：
//>0 ------ 查询成功
//<= 0 ------ 查询失败

//////////////////////////////////////////////////////////////////////////////////
//
//  10、功能号0x401 查询股票SWI_FUNC_QUERY_STOCK
//
//////////////////////////////////////////////////////////////////////////////////

//请求消息
struct SWI_QueryStockRequest
{
        struct SWI_BlockHead head; // function_no == 0x401, block_type==1
        char   account_type;       	// 客户帐号类型（见数据字典说明）
        char   account[16];        	// 客户帐号
        BYTE   exchange_no;        	// 交易所编号（见数据字典说明）
        char   security_code[7];   	// 证券代码（空表示全部）
        WORD   max_results;        	// 最大查询记录数（0表示全部）
        BYTE   flag;      			// 返回盈亏分析数据标志 
                                                //  =0，缺省，不返回对应值，对应字段为0
                          			//  =1，返回盈亏分析数据
                          			//增加flag，要求尽量少调用flag=1,减少性能影响
	char stock_account[15];      	//查询证券帐号条件,即以证券帐号为条件过滤结果集，缺省
                                        //为字符串'0'，见详细说明
};
//查询结果行应答
struct SWI_QueryStockResult
{
	struct SWI_BlockHead head;  // function_no == 0x401,block_type==3
	WORD row_no;                //  记录号 ,  0xFFFF -- 结果集结束(本条结果数据无效)
	BYTE exchange_no;           //  交易所编号
	char security_code[7];      //  证券代码
	char security_name[18];     //  证券名称（MBCS/Unicode）
	long deposite;              //  股票余额
	long available;             //  可用余额
	SWISmallMoney hold_price;   //  持仓均价
	SWISmallMoney current_price;//  最新价
	SWIMoney past_profit;       //  已有赢利
	char security_account[11];  //  股东代码
	long last_month_balance_date; //B股增加 结余日期
	long last_month_balance;	//B股增加   上月结余
	long today_bought_amount; 	//B股增加	当日发生买
	long today_sell_amount;     //B股增加	当日发生卖
        char stock_account[20];     // 股东代码
        SWIMoney today_buy_money;   // 当日买入成交金额（AB股有效）(?)
        SWIMoney today_sell_money;  // 当日卖出成交金额（AB股有效）(?)
	SWIMoney cur_market_value;    // 动态上市证券市值（flag=0时，固定返回0）
	char    stock_type[1];        //证券类别
	BYTE report_unit_type;      // 申报单位类型（对于债券，=1，表示按手申报；对于股票基金等，=0，表示按股申报;对于B股，=0。）
	SWIMoney    fund_deposite;           // 上市昨日股票余额（支持开放式基金小数份额）
        SWIMoney    fund_available;          // 上市可用余额（支持开放式基金小数份额）
        SWIMoney    unlisted_amount;        //未上市股份数（flag=0时，固定返回0）
	SWISmallMoney   Unlisted_hold_price;     //未上市股份持仓价格（flag=0时，固定返回0）
	BYTE market_value_flag;           //参与计算市值标志（0：不计算 1：计算）
        char    bond_interest[12];        //国债百元应记利息(包括小数点)，非国债返回为‘0’
        SWIMoney    hold_money;           //上市金额
        SWIMoney    unlisted_hold_money;  //未上市金额
        long availableT;           //计算申购/赎回可用余额
                                //(针对ETFs：用来计算ETFs对应股票当日可用来申购的份额和ETFs可用来赎回的份额)； 
};
/*
注：当证券品种为国债时，市价不包括百元应记利息。
原0x801功能function_id=203返回结果集中可计算变量的关系为，
   	当report_unit_type=0时，每手股数=1
  	当report_unit_type=1时，每手股数=10

成本价=（上市昨日持仓均价*上市昨日股票余额*每手股数-上市已实现盈亏）/（上市昨日股票余额*每手股数）
  动态成本价=（成本价*上市昨日股票余额*每手股数+当日买入金额-当日卖出金额）/（（上市昨日股票余额+当日买入数量-当日卖出数量）*每手股数）

  动态上市证券市值=（上市昨日股票余额+当日买入数量-当日卖出数量）*每手股数*市价
	  当前上市证券市值=上市昨日股票余额*每手股数*市价
  （对于动态上市证券市值、当前上市证券市值： 若市价为0时应按上市昨日持仓均价计算； 如果证券类别是国债，还要在市价上加百元应记利息）

  按当天先买进后卖出计：
  动态持仓价=（上市昨日持仓均价*上市昨日股票余额*每手股数+当日买入金额）/（（上市昨日股票余额+当日买入数量）*每手股数）
  动态已实现赢亏=当日卖出金额-（动态持仓价*当日卖出数量）*每手股数+上市已实现盈亏
  动态浮动盈亏=动态证券市值-动态持仓价*（上市昨日股票余额+当日买入数量-当日卖出数量）*每手股数

以上计算公式均未考虑'未上市流通股份'部分，使用者可酌情修改。以上计算公式仅供参考。
*/
//RETURN应答
struct SWI_QueryStockReturn
{
        struct SWI_BlockHead head;              // function_no== 0x401, block_type==2
        long return_status;                     //  ------ 返回状态
};
//返回状态：
//>0 ------ 查询成功
//<= 0 ------ 查询失败
/*特别注意：
1、	当security_code=空时，表示查询所有股票持仓情况。
2、	stock_account为查询过滤字段：
（1）、当stock_account=空时，查询结果集不过滤（即包括关联分帐号信息）；
（2）、当stock_account<>空而且stock_account<>'0'时，查询结果集中的记录为"证券帐号=stock_account"的记录。
（3）、当stock_account='0'时，为网关内部使用的过渡状态，外围禁止使用（过渡期结束系统将不支持该状态）；表示查询结果和修改前相同。即为
3.1).  security_code=空： account为关联主帐号时，返回结果中包括关联分帐号记录；account为非关联主帐号时，返回结果中只包括对应帐号记录。
3.2).  security_code<>空: 不论account是否为关联主帐号，返回结果中只包括对应（参数）account帐号的一条记录（或无记录）。
3、扩充flag参数后，flag=0作为缺省值，不返回"动态上市证券市值"、'未上市股份数'、'未上市股份价格'等字段；flag=1时返回"动态上市证券市值"、 '未上市股份数'、'未上市股份价格'等字段，用于替代"功能号0x801,查询公共数据"的"function_id=203(查询客户的盈亏分析数据)"；对于成本价、动态成本价、动态持仓价、动态已实现赢亏、动态浮动盈亏数据，均可通过返回结果计算得到。
4、"功能号0x801,查询公共数据"的"function_id=203(查询客户的盈亏分析数据)" 将于2003年4月中旬取消该功能支持。
5、本协议从版本2.72开始，返回结果集中包含"上市昨日股票余额"、'未上市股份数'、"当日买入数量"、"当日卖出数量"其中之一不为0的记录。
*/

/////////////////////////////////////////////////////////////////////
//
// 11、功能号0x402· 查询委托SWI_FUNC_QUERY_ENTRUST
//
/////////////////////////////////////////////////////////////////////
struct SWI_QueryEntrustRequest
{
	struct SWI_BlockHead head; 	// function_no == 0x402 ,block_type==1
	char    account_type;    	// 客户帐号类型（见数据字典说明）
	char    account[16];     	// 客户帐号
	BYTE    exchange_no;     	// 交易所编号（见数据字典说明）
	long    begin_date;      	// 起始日期（形如：yyyymmdd）
	long    end_date;        	// 结束日期（形如：yyyymmdd）
	long    entrust_sn;      	// 委托编号（0表示全部）
	char    security_code[7];	// 股票代码（空表示全部）
	WORD    max_results;     	// 最大查询记录数
	char 	stock_type;		// 证券类别, 缺省为空，查询全部证券类别.
};
//起始日期begin_date	结束日期end_date	功能描述
//当日日期	        0	                查询当日的有效委托
//当日日期	        当日日期        	查询所有当日委托，既包括当日申报的所有委托、也包括下一工作日申报的夜市委托
//起始日期	        结束日期	        查询历史库中的所有历史委托，日期区间为"委托日期"，但不包括当日的委托


//  查委托结果集：
struct SWI_QueryEntrustResult
{
	struct SWI_BlockHead head; // function_no==0x402,block_type==3
	WORD   row_no;               //  记录号,  0xFFFF结果集结束
	long   entrust_date;         //  委托日期（形如：yyyymmdd）
	long   entrust_sn;           //  委托编号
	char   entrust_time[9];      //  委托时间（形如：hh:mm:ss）
	BYTE   exchange_no;          //  交易所编号（见数据字典说明）
	char   security_account[11]; //  股东代码
	char   security_code[7];     //  证券代码
	char   security_name[18];    //  证券名称（MBCS/Unicode）
	char   bs_type;              //  买卖类别（见数据字典说明）
	long   stock_ammount;        //  委托数量
	SWISmallMoney price;         //  委托价格
	SWIMoney frozen_money;       //  冻结金额
	char   entrust_method;       //  委托方式（见数据字典说明）
	char   entrust_status;       //  委托状态（见数据字典说明）
	short  operator_no;          //  操作员工号
	long   bargain_ammount;      //  已成交数量
	char   error_msg[32];		 //  委托失败原因

        unsigned char    mark;             //是否连续赎回 1为连续赎回,0为非连续

        char stock_account[20];        //开放式基金帐号
        SWIMoney fund_amount;   //委托数量（支持开放式基金小数份额）
        char entrust_sign[10];  //交易签名(缺省为'')
        long frozen_amount;      //冻结证券数量
};
//注： 对外围根据帐号和证券类别查询，若证券类别为'n'ETF申购(上证50ETF)，则查询委托结果中，对于申购委托返回的结果集中有1-51条委托记录，标识对应50只股票的冻结股份和对应申购委托冻结的金额（现金替代部分）；对于赎回委托返回的结果集合中有1条委托记录，标识ETF基金的冻结份额。

// RETURN应答
struct SWI_QueryEntrustReturn
{
	struct SWI_BlockHead head;
	long return_status;     // ------ 返回状态
};
//
//方式：
//  IF account_type和account正确 THEN
//      IF entrust_sn<>0 THEN
//         按“委托编号entrust_sn”和“起始日期begin_date”查询
//      ELSE
//         按“起始日期@begin_date”和“结束日期@end_date”查询，
//         并判断“证券代码@security_code”
//     ENDIF
//  ELSE
//     出错
//  ENDIF
//

//返回：
//>0    ------ 查询成功
//<=0   ------ 查询失败


/////////////////////////////////////////////////////////////////////////////
//
//12·功能号0x403 查询实时成交SWI_FUNC_QUERY_BUSINESS
//
////////////////////////////////////////////////////////////////////////////

//请求消息
struct SWI_QueryBusinessRequest
{
	struct SWI_BlockHead head;// function_no==0x403,block_type==1
	char    account_type;     //客户帐号类型
	char    account[16];      //客户帐号
	BYTE    exchange_no;      //交易所编号
	long    entrust_sn;       //委托编号（0表示全部）
	char    security_code[7]; //股票代码（6空格表示全部）
	BYTE    flag;             //合并方式 0:缺省，根据委托号合并
				              //           1:股票，买卖合并
        long    begin_serial_no;       // 成交明细开始流水号（缺省值=0）
                                //（flag=2返回大于begin_serial_no记录）
};
//当日成交结果集：
struct SWI_QueryBusinessResult
{
	SWI_BlockHead head;   	   // function_no==0x403, block_type==3
	WORD row_no;                 	// 记录号, 0xFFFF结果集结束
	BYTE exchange_no;            	   // 交易所编号（见数据字典说明）
	char security_account[11] ;  	// 股东代码
	char security_code[7];      	// 证券代码
	char security_name[18];     	// 证券名称（MBCS/Unicode）
	char bs_type;               	   // 买卖类别（见数据字典说明）
	int stock_ammount;           // 成交数量
	SWISmallMoney price;        	   // 成交价格
	SWIMoney money;                 // 成交金额
	char bargain_time [9];       	// 成交时间（形如：hh:mm:ss）
	unsigned char bargain_no[4];               // 成交编号
        unsigned char sale_profit[4];//SWIMoney ;            //卖出盈亏 v2.3
        unsigned char sale_profit1[4];//SWIMoney ;            //卖出盈亏 v2.3
        char sea[8] ;                   //席位号
        unsigned char report_serial_no[4];          //申报编号
        unsigned char entrust_no[4];                //委托编号

        char stock_account[20];  		// 股东代码
        SWIMoney unfrozen_money;          //解冻资金金额(A股有效，B股返回0)
        long   unfrozen_amount;         //解冻证券数量(A股有效，B股返回0)
        long   serial_no;               //成交明细流水号(对参数flag=2有效,其他=0)    
};
//（注：查询ETFs对应的4部分成交记录可以根据申购或赎回时候的委托编号进行查询, 返回结果集合中包括所有4部分ETFs成交明细. 
//RETURN应答
struct SWI_QueryBusinessReturn
{
	struct SWI_BlockHead head;//function_no==0x403, block_type==2
	long    return_status;    // ------ 返回状态
};

//返回状态：
//>0   ------ 查询成功
//<=0   ------ 查询失败

//处理方式：
//  IF"account_type和account正确"THEN
//      IF"entrust_sn<>0"THEN
//         按"委托编号entrust_sn"查询
//      ELSE
//         按"证券代码security_code"查询，
//      ENDIF
// ELSE
//     出错
// ENDIF
//
//注： 对于"电话委托"，通常不便于返回多条记录，可按"委托编号"查询。


/////////////////////////////////////////////////////////////////////
//
//13、功能号0x503·查询历史成交SWI_FUNC_QUERY_HISTORY_BUSINESS
//
///////////////////////////////////////////////////////////////////////

//请求消息
struct SWI_QueryHisBusinessRequest
{
	struct SWI_BlockHead head; //function_no==0x503,block_type==1
	char    account_type;      // 客户帐号类型
	char    account[16];       // 客户帐号
	BYTE    exchange_no;       // 交易所编号
	long    begin_date;        // 起始日期
	long    end_date;          // 结束日期
	char    security_code[7];  // 股票代码（space(6)表示全部）
	BYTE    flag;              // 查询方式
	WORD    max_results;       // 最大查询记录数
};
//历史成交结果集：
struct SWI_QueryHisBusinessResult
{
	struct SWI_BlockHead head;      // function_no==0x503,block_type==3
	WORD    row_no;                 // 记录号,  0xFFFF结果集结束
	BYTE    exchange_no;            // 交易所编号（见数据字典说明）
	char    security_account[11];   // 股东代码
	char    security_code[7];       // 证券代码
	char    security_name[18];      // 证券名称（MBCS/Unicode）
	char    bs_type;                // 买卖类别（见数据字典说明）
	long    stock_change;           // 发生数量
	long    stock_deposite;         // 本次发生后股票余额
	SWISmallMoney occur_price;      // 成交价
	long    bargain_date;           // 成交日期（形如：yyyymmdd）
	char    bargain_time[9];        // 成交时间（形如：hh:mm:ss）
	long    bargain_no;             // 成交编号
        
        SWIMoney sale_profit;           //卖出盈亏
	char    stock_account[20];      // 股东代码
        SWIMoney	fund_amount;   	   //发生数量（支持开放式基金小数份额）
        SWIMoney 	fund_deposite; 	   //本次发生后股票余额（支持开放式基金小数份额）
};
//查询ETFs对应的4部分成交记录可以根据申购或赎回时候的委托编号进行查询, 返回结果集合中包括所有4部分ETFs成交明细.

//RETURN应答
struct SWI_QueryHisBusinessReturn
{
	struct SWI_BlockHead head;// function_no==0x503, block_type==2
	long    return_status;    // ------ 返回状态
};

//返回状态:
//>0   查询成功
//<=0    查询失败
//
//	处理方式：
//	  IF"account_type和account正确"THEN
//			 按"起始日期begin_date"和"结束日期end_date"查询，
//			 并判断"证券代码security_code"
//	  ELSE
//		 出错
//	  ENDIF
//

/////////////////////////////////////////////////////////////////////////////////
//
//14、功能号0x504 查询资金明细/客户台帐SWI_FUNC_QUERY_FUND_DETAIL
//
//////////////////////////////////////////////////////////////////////////////////

//请求消息
struct SWI_QueryFundDetailRequest
{
	struct  SWI_BlockHead head; // function_no==0x504,block_type==1
	char    account_type;      // 客户帐号类型
	char    account[16];       // 客户帐号
	BYTE    exchange_no;       // 交易所编号
	long    begin_date;        // 起始日期（形如：yyyymmdd）
	long    end_date;          // 结束日期（形如：yyyymmdd）
	char    currency_type;     // 币种
	WORD    max_results;       // 最大查询记录数
	BYTE	flag;		   // 查询方式 0 - 资金明细
                                   //		   1 - 客户台帐(对帐单)
};
//对于几个参数做如下约定：（该约定针对查询明细）
//起始日期begin_date	结束日期end_date	功能描述
//当日日期	        >=当日日期	        查询所有当日资金明细，既包括当日到帐的所有资金变动，也包括下一工作日到帐的所有资金变动（严格按照自然日进行查询）
//起始日期	        结束日期	        查询已转入历史库的所有历史资金明细，日期区间为"发生日期"，但不包括当日资金明细

//资金明细/客户台帐结果集：
struct SWI_QueryFundDetailResult
{
	struct  SWI_BlockHead head;	// function_no==0x504,block_type==3
	WORD    row_no;             	// 记录号,  0xFFFF结果集结束
	long    change_date;        	// 发生日期（形如：yyyymmdd）
	char    change_time[9];     	// 发生时间（形如：hh:mm:ss）
	SWIMoney change;            	// 发生金额
	SWIMoney deposite;          	// 本次发生后资金余额
	char    abstract[32];       	// 摘要（MBCS/Unicode）
	long    serial_no;          	// 流水号
	char    security_code[7];       // 证券代码
	char    security_name[18];      // 证券名称（MBCS/Unicode）
	long 	stock_ammount;      	// 证券成交数量（正：买入；负：卖出）
	SWISmallMoney price;        	// 证券成交均价
        long    pre_amount;             // 前证券数量
        short business_flag;  //业务标志
        char stock_account[16];//股东帐号
        SWIMoney  fund_amount;   //证券成交数量（支持开放式基金小数份额）
        SWIMoney  fund_pre_amount; 	//前证券数量（支持开放式基金小数份额）

};
//RETURN应答
struct SWI_QueryFundDetailReturn
{
	struct SWI_BlockHead head; //   function_no==0x504, block_type==2
	long    return_status;  // ----- 返回状态
};

//方式：
//  IF"@account_type和@account正确"THEN
//         按"起始日期@begin_date"和"结束日期@end_date"查询，
//         并判断"证券代码@security_code"
//  ELSE
//     出错
//  ENDIF
//
//返回：
// >0   ------ 查询成功
// <=0   ------ 查询失败

//////////////////////////////////////////////////////////////////////
//
//16、功能号0x601,查询证券信息  SWI_FUNC_QUERY_SECURITY_INFO
//
//////////////////////////////////////////////////////////////////////

struct SWI_SecurityInfoRequest
{
	struct SWI_BlockHead head;		// function_no = 0x601,block_type==1
	BYTE   exchange_no;         	// 交易所编号（见数据字典说明）
	WORD   security_idx;       		// 证券序号（见注）
	char   security_code[7];   		// 证券代码
};
//注：当证券代码为空串时，按证券序号查询, 仅用于罗列股票。
//用从0开始递增的序号反复查询直到返回失败，可以罗列出所有股票。
//平时查行情请用证券代码进行查询以免行情库发生错位。

//应答
// 查证券信息返回结果
struct SWI_SecurityInfoReturn
{
	struct SWI_BlockHead head;	    // function_no==0x601,block_type==2
	long		  return_status;    // 返回状态
	char		  security_code[7]; // 证券代码
	char		  security_name[18];// 证券名称（MBCS/Unicode）
	SWISmallMoney prev_close_price; // 前收盘
	SWISmallMoney open_price;       // 今开盘
	SWISmallMoney top_price;        // 最高价
	SWISmallMoney bottom_price;     // 最低价
	SWISmallMoney current_price;    // 最新价
	long   	 	  amount;           // 成交数量
	SWIMoney 	  volume;           // 成交金额
	SWISmallMoney buy_price_1;      // 买价1
	long	 	  buy_amount_1;     // 买量1
	SWISmallMoney buy_price_2;		// 买价2
	long		  buy_amount_2;     // 买量2
	SWISmallMoney buy_price_3;      // 买价3
	long		  buy_amount_3;     // 买量3
	SWISmallMoney sale_price_1;     // 卖价1
	long		  sale_amount_1;    // 卖量1
	SWISmallMoney sale_price_2;     // 卖价2
	long		  sale_amount_2;    // 卖量2
	SWISmallMoney sale_price_3;     // 卖价3
	long		  sale_amount_3;    // 卖量3
	char		  security_type;    // 证券类别（保留）
	BYTE		  stop_trading_flag;// 停牌标志（非0：停牌）
	BYTE		  bs_allowed;       // 允许买卖（非0：允许）
	SWISmallMoney buy_price_4;      // 买价4（使用三档行情时返回0）
	long		  buy_amount_4;     // 买量4（使用三档行情时返回0）
	SWISmallMoney buy_price_5;      // 买价5（使用三档行情时返回0）
	long		  buy_amount_5;     // 买量5（使用三档行情时返回0）
	SWISmallMoney sale_price_4;     // 卖价4（使用三档行情时返回0）
	long		  sale_amount_4;    // 卖量4（使用三档行情时返回0）
	SWISmallMoney sale_price_5;     // 卖价5（使用三档行情时返回0）
	long		  sale_amount_5;    // 卖量5（使用三档行情时返回0）
};
//注：对于上海指数，使用show128.dbf中代码分别查询；对于深圳指数，使用特殊股票代码9000-9100查询，其中9000对应与z_zs.dbf中第一条记录.

//
//返回状态
//  >0 成功
//  <=0  失败


//////////////////////////////////////////////////////////////////////////
//
//17、功能号0x901 出错信息解释SWI_FUNC_ERROR_MSG
//
/////////////////////////////////////////////////////////////////////////
//请求消息
struct SWI_ErrorMsgRequest
{
	struct SWI_BlockHead head;  //function_no==0x901, block_type==1
	long    error_no;           //出错代码
};

//应答
struct SWI_ErrorMsgReturn
{
	struct SWI_BlockHead head;	//function_no==0x901,block_type==2
	long    return_status;      // 返回状态
	char    error_msg[40];      // 错误信息（MBCS/Unicode）
};
//返回状态
//  >0 成功
//  <=0  失败

//////////////////////////////////////////////////////////////////////
//
//18、功能号0x902, 重定位结果集  SWI_FUNC_RESULTSET_GOTO
//
//////////////////////////////////////////////////////////////////////

//请求消息
struct SWI_ResultsetGotoRequest
{
	struct SWI_BlockHead head;   //function_no == 0x902,block_type==1
	WORD   row_no;               //定位到记录号（0开始）
	WORD   max_results;          //最多记录数
};

//本调用无独立的应答，而是重发上次查询的结果集



//--------------------------------------------------------------------------------
// definiation on block_type
#define SWI_BT_REQUEST 1
#define SWI_BT_RETURN  2
#define SWI_BT_RESULT  3
//#define SWI_BT_CANCEL  4
//#define SWI_BT_ALERT   5
#define SWI_BT_CN_REQUEST  6
#define SWI_BT_CN_RESPONSE 7

//功能号宏定义
#define SWI_FUNC_OPEN_ACCOUNT                   0X101
#define SWI_FUNC_ADD_ENTRUST                    0X201
#define SWI_FUNC_WITHDRAW                       0X202
#define SWI_FUNC_QUERY_MONEY                    0X301
#define SWI_FUNC_QUERY_ACCOUNTINFO		0x302
#define SWI_FUNC_QUERY_STOCK			0x401
#define SWI_FUNC_QUERY_ENTRUST			0x402
#define SWI_FUNC_QUERY_BUSINESS			0X403

#define SWI_FUNC_QUERY_HISTORY_BUSINESS         0x503
#define SWI_FUNC_QUERY_FUND_DETAIL              0x504

#define SWI_FUNC_QUERY_SECURITY_INFO            0x601
#define SWI_FUNC_ERROR_MSG			0x901

//出错码
//在所有外部委托，使用全局唯一的出错码，出错码的含义由SWI_ErrorMsg来解释。
//我们可以在后继版本中增加其它出错码的含义。
//现已定义的出错码含义如下：

#define SWIE_GENERAL                    -100  // ------ 一般性错误（系统出错）
#define SWIE_INVALID_ACCOUNTTYPE        -101  // ------ 无此帐号类型
#define SWIE_INVALID_ACCOUNT            -102  // ------ 无此帐号
#define SWIE_INVALID_TRADE_METHOD       -103  // ------ 委托方式有误（或禁止）
#define SWIE_INVALID_EXCHANGE           -104  // ------ 无此交易所编号
#define SWIE_INVALID_BS_TYPE            -105  // ------ 无效买卖类别
#define SWIE_INVALID_STOCK_CODE         -106  // ------ 无效证券代码
#define SWIE_STOCK_STOP_TRADING         -107  // ------ 该股票停牌
#define SWIE_INVALID_STOCK_AMOUNT       -108  // ------ 无效委托数量，小于0，或股票余量不足
#define SWIE_NO_ENOUGH_MONEY            -109  // ------ 资金不足
#define SWIE_INVALID_PRICE              -110  // ------ 无效价格
#define SWIE_INVALID_EFFECT_DAYS    	-111  // ------ 无效有效天数（保留）
#define SWIE_INVALID_OPERATOR       	-112  // ------ 非法操作员
#define SWIE_INVALID_DEPARTMENT         -113  // ------ 非法营业部编号
#define SWIE_STOP_TRADING               -114  // ------ 股市闭市（非有效委托时间）
#define SWIE_FROZEN_ACCOUNT             -115  // ------ 帐号已冻结
#define SWIE_METHOD_DISALLOWED          -116  // ------ 该委托方式禁止买卖该种股票
#define SWIE_DEPARTMENT_CLOSED          -120  // ------ 营业部目前禁止操作
#define SWIE_INVALID_TRADE_SN           -130  // ------ 无效委托编号
#define SWIE_TRADE_WITHDRAWED           -131  // ------ 该委托已撤单
#define SWIE_INVALID_TRADE              -132  // ------ 该委托无效
#define SWIE_BARGAINED_TRADE            -133  // ------ 该委托已成交
#define SWIE_INVALIDE_DATE              -140  // ------ 无效日期
#define SWIE_INVALIDE_PWD               -150  // ------ 原密码有误
#define SWIE_VERSION_MISMATCH		-160  // ------ Version of Client and Server mismatch

#define SWIE_NET_ERROR			-180  // ------ 通信出错
#define SWIE_TMTM_NOTALLOWED		-181  // ------ 通买通卖未开通
#define SWIE_TMTM_REMOTE_INVALID	-182  // ------ 通买通卖对方营业部编号错或网络未通
#define SWIE_TMTM_REMOTE_NET_ERROR      -183  // ------ 通买通卖对方营业部网络故障
#define SWIE_REOPEN                     -184  // ------ 重复打开帐号
#define SWIE_DB_TIMEOUT                 -185  // ------ 数据库访问超时
#define SWIE_ACCOUNT_NOT_OPENED         -186  // ------ 未校验交易密码
#define SWIE_DB_ERROR                   -187  // ------ 数据库出错
#define SWIE_HQ_ERROR                   -190  // ------ 无法访问行情
#define SWIE_NO_MORE_SECURITY           -191  // ------ 按证券序号查行情时证券序号太大
#define SWIE_TIMEOUT                    -195  // ------ 超时

#define SWIE_CANT_ALLOC_SPID            -501  // ------ 无法分配进程号
#define SWIE_TABLE_OP_ERROR		-502  // ------ 表操作出错
#define SWIE_INVALID_SPID		-503  // ------ 进程号不存在
#define SWIE_INVALID_OPERATOR_2         -504  // ------ 非法操作员
#define SWIE_ACCOUNT_MISMATCH           -505  // ------ 客户帐号不一致

#pragma pack(pop)

#endif
