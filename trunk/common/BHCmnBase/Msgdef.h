//---------------------------------------------------------------------------

#ifndef MsgdefH
#define MsgdefH
//---------------------------------------------------------------------------
#include "..\..\etfs\com\TaskStp.h"


#define  NAME_SIZE  		  128
#define  FNM_COMMAND          "COMMAND"  //{TCommand(1)}

#define  CMD_START_SERVER     0x5050	//启动服务器 	{Param1=0,Param2=0}, 
#define  CMD_STOP_SERVER      0x5051    //停止
#define  CMD_SETUP_SERVER     0x5052    //设置

#define  CMD_START_TASK_ALL   0x5001	//启动所有任务	{Param1=0,Param2=0}, 
#define  CMD_STOP_TASK_ALL    0x5002	//停止所有任务	{Param1=0,Param2=0}, 
#define  CMD_PAUSE_TASK_ALL   0x5003	//暂停所有任务	{Param1=0,Param2=0}, 
#define  CMD_RESUME_TASK_ALL  0x5004	//继续所有任务	{Param1=0,Param2=0}, 

#define  CMD_START_TASK       0x5005	//启动指定任务	{Param1=TaskID, Param2=0}, 
#define  CMD_STOP_TASK        0x5006	//停止指定任务	{Param1=TaskID, Param2=0}, 
#define  CMD_PAUSE_TASK       0x5007	//暂停指定任务	{Param1=TaskID, Param2=0}, 
#define  CMD_RESUME_TASK      0x5008	//继续指定任务	{Param1=TaskID, Param2=0}, 
#define  CMD_TASK_STATE       0x5009	//任务的状态,当任务状态有改变的时候由服务端发给客户端
										//{Param1=TaskID, Param2=State}, 

#define  CMD_SETUP_TASK       0x5010	//任务的参数设置 
										//{Param1=TaskID, Param2=0; + [TTaskInfo(1)]}
										
#define  CMD_TASK_LOG         0x5011	//任务日志 
										//{Param1=TaskID, Param2=0; + [Message(0..n)]}
										//{Message="msg1" + "\r\n" + msg2 + "\r\n"..."} 
											
#define  CMD_SERVER_LOG	      0x5014	//服务器日志,同上；
#define  CMD_CREATE_TASK      0x5012	//新建任务 
										//Client ==> Server {Param1=0,Param2=0; +[TTaskInfo(1)]}  
							 			//Server ==> Client {Param1=Return ,Param2=TaskID + [TTaskInfo(1)]} $注意这里$
							 			//{Return= 1(成功), -1(失败)}
							 			
#define  CMD_LOGIN_SERVER     0x5013	//登陆时的初始化信息，当Param1=1时由客户端发给服务端请求登陆；当Param1=2时服务端响应客户端的登陆请求
										//Client ==> Server {Param1=1, Param2=0; +[TClientInfo(1)]}
										//Server ==> Client {Param1=2, Param2=Return; [TServerInfo(1) + TTaskInfo(0..n)]}
										//{Return=-1:不能登陆，1:可以登陆但不可以控制, 50:可以控制 }

#pragma pack(push, 1)
struct TClientInfo {  
	char ciUserName [NAME_SIZE];
  	char ciPassword [NAME_SIZE];
};

struct TServerInfo {
  	int  siState;// -1   服务停止了 1    正在交易 0    非开市期间 2    开盘中 3    收盘中 4    中午休市
  	WORD siTaskNums;
	//主程序要设定的
	char siHQSvr[16];            //行情服务器地址
	char siHQPath[MAX_PATH + 1]; //行情路径
	int  siHQPort;               //行情端口

	long siAMOpen;							 //上午开盘
	long siAMClose;              //上午收盘
	long siPMOpen;               //下午开盘
	long siPMClose;              //下午收盘

	int	 siMonPort;               //监控端口
	char siMonSvr[20];           //被控IP
	char siBulletinPath[MAX_PATH+1]; //ETF配方文件路径
	char siUDLPath[MAX_PATH+1];  //数据库访问文件路径
};

struct TTaskInfo {
  	WORD   tiTaskID;
  	WORD   tiState;					//0 非运行中，1可开仓运行中，2不可开仓运行中,3需要开盘,4需要收盘
  	char   tiName[NAME_SIZE];

  	// Add Task Setup Information
	float  tiEtfOverStkGate;      //溢价阀值
	float  tiStkOverEtfGate;      //折价阀值
	float  tiStopV;				 //涨停阀值
	float  tiStopFix;             //涨停缺口 分

	float  tiStkHandTax;			 //经手费
	float  tiFundHandTax;
	float  tiStkCost;			 //所有费用
	float  tiFundCost;
	float  tiFundCreateCost;      //创设
	float  tiFundRedeemCost;      //赎回

	int    tiQryInterval;         //每次查询间隔时间
	int    tiTimeout;             //查询最长等待时间
	int	   tiMaxPrcChgV;			 //委托价格变化？分时
	int    tiWaitTime;            //等待？秒撤单
	int    tiAfterMaxPrcChgV;	 //超过等待时间时如果价格变化在这个值内就不撤单
	int    tiSellType;			 //卖股票时，0--以整数手下单, 1---以整数手下单,且若剩余成交量<100,则默认全部成交,2 --彻底清仓，即最后一次下单允许下非整数手
	int    tiMinEtfTrdVol;		 //最小ETF交易量，比如=100000
	float  tiStkRed;			//股票盘口冗余度
	float  tiEtfRed;			 //Etfs盘口冗余度

	bool   tiEmunTrd;              //是否是模拟交易

	char   tiAccount[20];			 //账户名
	char   tiPassword[10];         //密码
	double tiMinAccMoney;        //最小的账户可用额

	int    tiBuySellMode;			 //下单方式 0，1，2，3,4,5,6
	int    tiCpUsePriceType;        //计算时使用的盘口价格类型

	int    tiNumEtf;				 //几个单位时执行申购赎回

	bool   tiUse6Vlm;				 //使用估计的六档盘口
	float  tiVlm6Agio;			 //计算六档盘口的折算比率
	float  tiVlm6Alpha;			 //计算六档盘口的Alpha
	int    tiVlm6EventN;			 //计算六档盘口的事件数
	int    tiVlm6LoadHisN;			 //计算六档盘口加载的历史数据量

	int    tiTrdMode;               //0表示溢价小额套利，1表示折价小额套利，
								 //2表示超过最小逃离单位的所有套利

	float  tiMinProfit;           //利润小于这个值就中断对冲
	int    tiMaxFault;            //连续多少次套利失败就暂停开仓
	int    tiMaxErr;              //出现多少个错误就停止该任务
	HOLDSECURITY tiInitHoldSecu[MAX_BIND_STKS+1];
};

struct TCommand {
  	WORD CmdID;
  	int	 Param1;
  	int  Param2;
};

#pragma pack(pop)

#endif
