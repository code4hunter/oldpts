//---------------------------------------------------------------------------
#ifndef UTrdItf_HSFFH
#define UTrdItf_HSFFH


#include <SysUtils.hpp>
#include <SyncObjs.hpp>
#include "UTrdItfBase.h"
#include "t2sdk_interface.h"
#include <boost\shared_ptr.hpp>

#include <list>

#define ERR_UNKNOW_ACCOUNT_TYPE  -100
#define ERR_SEND_FAULT  		 -101
#define ERR_RECV_FAULT  		 -102
#define ERR_NO_ACK  			 -104  //����Ӧ
#define ERR_OTHERS  			 -103
#define ERR_UNIMPLEMENTED   	 -200  //δʵ��


#define PLUGINNAME "�����ڻ�T2��"
//���ڸ�ʽ YYYYMMDD
//ʱ���ʽ��HHMMSS

using namespace std;

class order_keeper;
typedef boost::shared_ptr<order_keeper> ORDERKEEPERPTR;
////////////////////////////////////////////////////////////////////////////
class TTrdItf_HSFF : public TTrdItfBase
{
public:
	enum t_entrust_status
	{
		eswb		= '0',//δ��
		esyb		= '2',//�ѱ�
		esdc1		= '3',//����
		esdc2		= '4',//����
		esbc		= '5',//����
		esyc1		= '6',//�ѳ�
		esyc2		= '7',//�ѳ�
		esyc		= '8',//�ѳ�
		esyf		= '9',//�ѷ�

		/*
		0 δ��
		1 ����
		2 �ѱ�
		3 �ѱ�����
		4 ���ִ���
		5 ����
		6 �ѳ�
		7 ����
		8 �ѳ�
		9 �ϵ�
		10 ��ȷ��


		0 δ��
		1 ����
		2 �ѱ�
		3 �ѱ�����
		4 ���ɴ���
		5 ����
		6 �ѳ�
		7 ����
		8 �ѳ�
		9 �ϵ�
		C ����
		D ����
		*/
	};

	enum t_money_type
	{
		mtrmb		= '0',//�����
		mtusd 	= '1',// ��Բ
		mthkd		= '2',//�۱�
	};

	enum t_entrust_bs
	{
		ebbuy		= '1',//-- ����
		ebsell		= '2',// -- ����
	};

	enum t_order_direction
	{
		od_open = '1', //����
		od_close= '2',  //ƽ��
		od_close_today='4'//ƽ��
	};

	enum t_query_direction
	{
		qdahead		= '0',//--��ǰ����˳��
		qdnext		= '1',//--���󷭣�����
	};

	enum t_entrust_type
	{
		ettrd			= '0',// ����
		etqry			= '1',// ��ѯ
		etwithdraw		= '2',// ����
		etpatch			= '3',// ����
	};

	struct THSFFSet
	{
		int     TimeOut;
		AnsiString	op_branch_no  ;   //������֧��
		AnsiString	op_station;       //����վ��/�绰����    MAC
		AnsiString	op_entrust_way;   //����ί�з�ʽ		 t_entrust_way
		AnsiString	branch_no;  	  //Ӫҵ����			 0000
		AnsiString  hs_licence;       //���׹�����Ȩ��
		bool    gen_check_info;
	};
private:	// User declarations
	CConfigInterface * _config;
    CConnectionInterface *_connection ;
   	THSFFSet FHSFFSet;
	//AnsiString FAccount;
	bool _createKeeper;
	ORDERKEEPERPTR _ord_keeper;
	int SendAndReceive(int funid,IF2Packer *in,IF2UnPacker **out);
public:		// User declarations
	TTrdItf_HSFF(const char *psetupfile,ADDLOG plogfunc,bool createKeeper=true);
	virtual ~TTrdItf_HSFF();

	int Init();  //��ʼ��
	int SetAccount(); //�����ʺ�

	//////��ѯ����//////
	int QryMoney(); 	//�ʽ��ѯ
	int QryCurCsn();	//����ί�в�ѯ
	int QryCurTrd();	//���ճɽ���ѯ
	int QryStocks();	//��ѯ�ʺ������еĹɷ�
	int Order();
	int Undo(); //ί�г���

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

	//��������Ϣ������,���û�л�ȡ������������Ϣ����false
	virtual bool GetConfig(void);
	//��������Ϣ��д�������ļ�
	virtual void SetConfig(void);
	//�ر��м������
	virtual void CloseLink(void);

	virtual int KeepAlive(void);

	int QryOrderByOrdid(TTradeInfo * ti);
};

//---------------------------------------------------------------------------
#endif
