//---------------------------------------------------------------------------

#ifndef uSessionH
#define uSessionH

#include "ThostFtdcTraderApi.h"

#include <map>
#include <string>
#include <boost\shared_ptr.hpp>
#include <boost\scoped_ptr.hpp>
#include <boost\thread.hpp>
#include <boost\thread\mutex.hpp>

// class session
// 实现CThostFtdcTraderSpi，并建立一个线程为spi服务
class session : public CThostFtdcTraderSpi
{
private:
	CThostFtdcTraderApi* user_api;
	std::string _frontAddr;
	std::string _brokerId;
	std::string _investorId;
	std::string _password;

	TThostFtdcFrontIDType	_front_id;		//前置编号
	TThostFtdcSessionIDType	_session_id;	//会话编号
	long _order_ref;		//报单引用,当前的最大委托号
	long _request_id;
	long _trd_date;

    long _last_qry_time;
    bool _is_login;

    boost::mutex _mutex;
public:
	session():
		_front_id(0),
		_session_id(0),
		_order_ref(0),
		_request_id(0),
		_trd_date(0),
        _last_qry_time(0),
        _is_login(false)
	{

	}
	~session()
	{
    	end_worker();
    }

	//建立工作线程
	void start_worker(const std::string& frontAddr,
					  const std::string& brokerId,
					  const std::string& investorId,
					  const std::string& password)
	{
        boost::mutex::scoped_lock lock(_mutex);
		_frontAddr  = frontAddr;
		_brokerId   = brokerId;
		_investorId = investorId;
        _password   = password;
		end_worker();
		user_api = CThostFtdcTraderApi::CreateFtdcTraderApi(); 		// 创建UserApi
		user_api->RegisterSpi((CThostFtdcTraderSpi*)this);			// 注册事件类
		user_api->SubscribePublicTopic(THOST_TERT_QUICK);			// 注册公有流
		user_api->SubscribePrivateTopic(THOST_TERT_QUICK);			// 注册私有流
		user_api->RegisterFront(const_cast<char*>(_frontAddr.c_str()));	// connect
		user_api->Init();
	}
	//停止工作线程
	void end_worker(void)
	{
        boost::mutex::scoped_lock lock(_mutex);
    	if( user_api != NULL )
		{
			user_api->RegisterSpi(NULL);
			user_api->Join();
			user_api->Release();
			user_api = NULL;
            _is_login = false;
        }
	}

private:

// CThostFtdcTraderSpi
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();

	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///投资者结算结果确认响应
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单录入请求响应
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///报单操作请求响应
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	virtual void OnFrontDisconnected(int nReason);

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///报单通知
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

	///成交通知
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

private:
	///用户登录请求
	void ReqUserLogin();
	///用户登出请求
	void ReqUserLogout();
	///投资者结算结果确认
	void ReqSettlementInfoConfirm();
	///请求查询合约
	void ReqQryInstrument();
	///请求查询资金账户
	void ReqQryTradingAccount();
	///请求查询投资者持仓
	void ReqQryInvestorPosition();

	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo) ;
public:
	///报单录入请求  return orderid ,
	int ReqOrderInsert(	const std::string &instId,  //代码
						int direction,              //买卖 1,-1
						double price,               //price <0表示市价单
						int volume,
						int openClose,              //开平,平今 1,-1 ,-2
						int hedge                   //投机套保1,2
						);

	///报单操作请求
	int ReqOrderDelete(const std::string &instId,const char* orderId);

    //外部调用以更新账户和持仓信息,如果force=true则不管是否已经在很短的时间内查询
    //过也强制查询一次
    void ReqQry(bool force);

    bool isLogin(void)
    {
        return _is_login;
    }

    bool isWorking(void)
    {
        boost::mutex::scoped_lock lock(_mutex);
        return !(user_api==NULL);
    }
};

typedef boost::shared_ptr<session> SESSIONPTR;
typedef std::map<std::string,SESSIONPTR> SESSIONS;

// class session_manager
class session_manager
{
public:
	session_manager()
	{

	}

	~session_manager()
	{

    }

	// 根据用户名获取session，如果存在则返回该session，如果不存在则
	// 建立新的session并返回
	SESSIONPTR get_session_by_name(const std::string &userId,const std::string &pwd)
	{
        boost::mutex::scoped_lock lock(_mutex);
        std::string key = userId+ "#" + pwd;
		SESSIONS::iterator iter = _sessions.find( key );
		if( iter != _sessions.end() )
		{
			return iter->second;
		}
		else
		{
			SESSIONPTR ptr(new  session());
			_sessions[key] = ptr;
			return ptr;
        }
	}

	// 清除所有session
	void clear(void)
	{
        boost::mutex::scoped_lock lock(_mutex);
    	_sessions.clear();
	}

private:
	SESSIONS _sessions;
    boost::mutex _mutex;
};

extern session_manager gSessionMan;
//---------------------------------------------------------------------------



#endif
