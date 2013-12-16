#ifndef stkrec_h
#define stkrec_h

//STOCK 公用结构

#pragma pack(4)

/*
**股票/etf等状态
*/

enum stock_state
{
	//最后状态
	ssComplete=100 ,        //全部成交
	ssUnConfirm=-100,       //未决
	ssPartBargain=51,       //部分成交
	ssNothing=50,           //没有任何成交
	ssOrdFault=-50,         //下单失败
	//中间状态
	ssOrdering=0,           //下单任务完成前
	ssQrying=1              //查询等待中
};

/*
**二级市场挂牌交易与一级市场申购赎回
**操作
*/

enum operate_type
{
	otBuy=1,                //买，申购
	otSell=2,               //卖，赎回
	otWithdrawBuy=-1,       //撤销买
	otWithdrawSell=-2       //撤销卖
};

/*
**股票或者ETF委托结构
*/

struct stock_order
{
	char code[10];          //代码
	stock_state state;		  //当前状态		
	operate_type operate;		//操作 
	char ord_id[10];        //委托号
	int ord_num;            //实际当前委托数量
	float ord_price;        //实际当前委托价格
	int goal_num;           //目标量
	float goal_price;       //期望价格
	int date;               //日期 2004/8/1->20040801
	int time;               //最初下单时间 1:10:05->011005
};

/*
**股票或者ETF交易的结构
*/

struct stock_trade
{
	int id;                 //纪录ID	
	stock_order so;         //委托
	int deal_num;           //成交数量
	float deal_price;	      //成交均价	
	int time;               //最后成交时间
};

#pragma pack()

#endif