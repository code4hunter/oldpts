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
// ʵ��CThostFtdcTraderSpi��������һ���߳�Ϊspi����
class session : public CThostFtdcTraderSpi
{
private:
	CThostFtdcTraderApi* user_api;
	std::string _frontAddr;
	std::string _brokerId;
	std::string _investorId;
	std::string _password;

	TThostFtdcFrontIDType	_front_id;		//ǰ�ñ��
	TThostFtdcSessionIDType	_session_id;	//�Ự���
	long _order_ref;		//��������,��ǰ�����ί�к�
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

	//���������߳�
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
		user_api = CThostFtdcTraderApi::CreateFtdcTraderApi(); 		// ����UserApi
		user_api->RegisterSpi((CThostFtdcTraderSpi*)this);			// ע���¼���
		user_api->SubscribePublicTopic(THOST_TERT_QUICK);			// ע�ṫ����
		user_api->SubscribePrivateTopic(THOST_TERT_QUICK);			// ע��˽����
		user_api->RegisterFront(const_cast<char*>(_frontAddr.c_str()));	// connect
		user_api->Init();
	}
	//ֹͣ�����߳�
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
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///Ͷ���߽�����ȷ����Ӧ
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����¼��������Ӧ
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///��������������Ӧ
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	virtual void OnFrontDisconnected(int nReason);

	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///����֪ͨ
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

	///�ɽ�֪ͨ
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);

private:
	///�û���¼����
	void ReqUserLogin();
	///�û��ǳ�����
	void ReqUserLogout();
	///Ͷ���߽�����ȷ��
	void ReqSettlementInfoConfirm();
	///�����ѯ��Լ
	void ReqQryInstrument();
	///�����ѯ�ʽ��˻�
	void ReqQryTradingAccount();
	///�����ѯͶ���ֲ߳�
	void ReqQryInvestorPosition();

	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo) ;
public:
	///����¼������  return orderid ,
	int ReqOrderInsert(	const std::string &instId,  //����
						int direction,              //���� 1,-1
						double price,               //price <0��ʾ�м۵�
						int volume,
						int openClose,              //��ƽ,ƽ�� 1,-1 ,-2
						int hedge                   //Ͷ���ױ�1,2
						);

	///������������
	int ReqOrderDelete(const std::string &instId,const char* orderId);

    //�ⲿ�����Ը����˻��ͳֲ���Ϣ,���force=true�򲻹��Ƿ��Ѿ��ں̵ܶ�ʱ���ڲ�ѯ
    //��Ҳǿ�Ʋ�ѯһ��
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

	// �����û�����ȡsession����������򷵻ظ�session�������������
	// �����µ�session������
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

	// �������session
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
