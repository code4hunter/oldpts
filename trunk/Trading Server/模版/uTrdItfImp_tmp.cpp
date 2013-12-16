//---------------------------------------------------------------------------


#pragma hdrstop

#include "uTrdItfImp.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TTrdItfImp::TTrdItfImp(const char *psetupfile,ADDLOG plogfunc)
{

}

TTrdItfImp::~TTrdItfImp()
{

}

//初始化
int TTrdItfImp::Init()
{

}

//设置帐号
int TTrdItfImp::SetAccount()
{

}

//资金查询
int TTrdItfImp::QryMoney()
{

}

//当日委托查询
int TTrdItfImp::QryCurCsn()
{

}

//当日成交查询
int TTrdItfImp::QryCurTrd()
{

}

//查询帐号中所有的股份
int TTrdItfImp::QryStocks()
{

}

//委托撤单
int TTrdItfImp::Order()
{

}

int TTrdItfImp::Undo()
{

}

market_type  TTrdItfImp::ConvertMarketType(const char *t)
{

}

order_type   TTrdItfImp::ConvertOrderType(const char *t)
{

}

order_state  TTrdItfImp::ConvertOrderState(const char *t)
{

}

pos_direction TTrdItfImp::ConvertPosDir(const char *t)
{

}

money_type   TTrdItfImp::ConvertMoneyType(const char *t)
{

}

char *  TTrdItfImp::ConvertMarketType(market_type t)
{

}

char *  TTrdItfImp::ConvertOrderType(order_type t)
{

}

char *  TTrdItfImp::ConvertOrderState(order_state t)
{

}

char *  TTrdItfImp::ConvertPosDir(pos_direction t)
{

}

char *  TTrdItfImp::ConvertMoneyType(money_type t)
{

}

//将配置信息读出来,如果没有获取完整的配置信息返回false
bool TTrdItfImp::GetConfig(void)
{

}

//将配置信息回写到配置文件
void TTrdItfImp::SetConfig(void)
{

}

//关闭中间件链接
void TTrdItfImp::CloseLink(void)
{

}

int TTrdItfImp::KeepAlive(void)
{

}
