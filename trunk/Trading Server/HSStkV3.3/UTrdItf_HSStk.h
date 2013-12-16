//---------------------------------------------------------------------------
#ifndef UTrdItf_HSStkH
#define UTrdItf_HSStkH

#include <list>
#include <SysUtils.hpp>
#include <SyncObjs.hpp>
#include "UTrdItfBase.h"
#include "HsCommX_OCX.h"


#define ERR_UNKNOW_ACCOUNT_TYPE  -100
#define ERR_SEND_FAULT  		 -101
#define ERR_RECV_FAULT  		 -102
#define ERR_NO_ACK  			 -104  //����Ӧ
#define ERR_OTHERS  			 -103
#define ERR_UNIMPLEMENTED   	 -200  //δʵ��


#define PLUGINNAME "������Ʊ(����)3.3"
//���ڸ�ʽ YYYYMMDD
//ʱ���ʽ��HHMMSS

using namespace std;
////////////////////////////////////////////////////////////////////////////
class TTrdItf_HSStk : public TTrdItfBase
{
public:

	enum t_exchange_type
	{
		etqt	= '0',  //�� ǰ̨δ֪������
		etsh	= '1',  //��  �Ϻ�
		etsz	= '2',  //��  ����
	};

	enum t_entrust_way
	{
		ewzz	= '0',//: ����ί��
		ewdh	= '1',//: �绰ί��
		ewzl	= '2',//: פ��ί��
		ewyc	= '3',//: Զ��ί��
		ewgt	= '4',//: ��̨ί��
		ewmy	= '5',//: ����ί��
		ewfz	= '6',//: ��֧ί��
		ewin	= '7',//: internetί��
	};

	enum t_entrust_status
	{
		eswb		= '0',//δ��
		esdb        = '1',//����
		esyb		= '2',//�ѱ�
		esybdc		= '3',//�ѱ�����
		esbcdc		= '4',//���ɴ���
		esbc		= '5',//����
		esyc		= '6',//�ѳ�
		esbcn		= '7',//����
		esycn		= '8',//�ѳ�
		esfd		= '9',//�ϵ�
		escf        = 'A',//����
		esdmq       = 'W' //����ȷ

		/*
		'0'	δ��
		'1'	����
		'2'	�ѱ�
		'3'	�ѱ�����
		'4'	���ɴ���
		'5'	����
		'6'	�ѳ�
		'7'	����
		'8'	�ѳ�
		'9'	�ϵ�
		'A'	����
		'W'	����ȷ
		*/
	};

	enum t_money_type
	{
		mtrmb		= '0',//�����
		mtusd 	    = '1',// ��Բ
		mthkd		= '2',//�۱�
	};

	enum t_entrust_bs
	{
		ebbuy		= '1',//-- ����
		ebsell		= '2',//-- ����
	};

	enum t_query_direction
	{
		qdhis		= '0',//0.���󷭡���ָȡ����ʼ���ڻ���ʼ������С�ļ�¼������ѯ�Ѿ���ѯ���ļ�¼�����ο���Լ�����塯����λ����
		qdnext		= '1',//1.��ǰ������ָȡ����ʼ���ڻ���ʼ�����Ĵ�ļ�¼��
	};

	enum t_entrust_type
	{
		ettrd			= '0',// ����
		etqry			= '1',// ��ѯ
		etwithdraw		= '2',// ����
		etpatch			= '3',// ����
	};

	enum t_entrust_prop   //ί������
	{
		epbs = '0',	   //   ����
		/*
		eppg = '1',    //	���
		epzt = '2',    //	ת��
		epsg = '3',    //	�깺
		ephg = '4',    //	�ع�
		epps = '5',    //	����
		epzd = '6',    //	ָ��
		epzg = '7',    //	ת��
		ephs = '8',    //	����
		epgx = '9',    //	��Ϣ
		epszpsqr='A',    //	��������ȷ��
		eppsfq ='B',    //	���۷���
		epwdzy ='C',    //	�޶���Ѻ
		epdjzy ='D',    //	������Ѻ
		epwdjy ='E',    //	�޶���Ѻ
		epjdjy ='F',    //	�ⶳ��Ѻ
		*/
		epetfss='N',    //	etf�깺����ʱ���뷽��1�깺 2���
		/*
		eptp = 'H',    //	ͶƱ
		'Y',    //	ҪԼ�չ�Ԥ��
		'J',    //	Ԥ��ҪԼ���
		'K',    //	�������
		'L',    //	��������
		'M',    //	����ת��
		*/
		epetfqzxq = 'P'    //	Ȩ֤��Ȩ
		/*
		'Q',    //	���ַ����ż۸�
		'R',    //	�����嵵��ʱ�ɽ�ʣ��ת�޼�
		'S',    //	�������ż۸�
		'T',    //	��ʱ�ɽ�ʣ�೷��
		'U',    //	�����嵵��ʱ�ɽ�ʣ�೷��
		'V',    //	ȫ��ɽ�������
		'f',    //	��Ѻ�����
        */
	};

	enum t_real_status	//�ɽ�״̬
	{
		rscj = '0',//	�ɽ�
		rsfd = '2', //	�ϵ�
		rsqr = '4'	//ȷ��
	};

	enum t_stock_type	//֤ȯ���
	{
		st = '0'	//��Ʊ
	};

	enum t_entrust_direction	//ί�з���
	{
		edgpmr = '1', //  ��Ʊ����
		edgpmc = '2', //  ��Ʊ����
		//3	�����깺
		//4	�������
		//5	�����Ϲ�
		edqzxq = '6',//	Ȩ֤��Ȩ
		//A	ծȯ����
		//B	ծȯ����
		//(	��Ѻ����
		//)	��Ѻ���
		//C	���ʻع�
		//D	��ȯ�ع�
		//G	��ծת��
		//H	��ծת��
		//J	תծ����
		edetfrh = 'M',//	ETF���
		edetfsg = 'N'//	ETF�깺
		//T	����ͶƱ
		//g	�Ϻ��깺
		//h	�����깺
	};


	typedef struct
	{
		String	SvrIp;
		int		SvrPort;
		int     Protocol;         //1,2(TCP,SPX)
		int     TimeOut;          //���ͺͽ��ճ�ʱ��
		long    KeyCipher;        // 0,1 (unuse or use key)
		String  KeyDeKey;         //16λ����key
		bool    debug_mode;       //�Ƿ�Ϊ���ģʽ
		String  l_op_code ;       //��Ա��
		String  vc_op_password;   //��Ա����
		String  op_entrust_way;   //ί�з�ʽ
		String	op_station;       //����վ��/�绰����    MAC
		int  branch_no;        //Ӫҵ�����
	} THSFFSet;

private:	// User declarations
	TComm*		FItf;
	THSFFSet	FHSFFSet;
	AnsiString FAccount;
	int SendAndReceive();
	int QryAccount( t_exchange_type et );
    int login(void);
    bool FDisconnected;
public:		// User declarations
	TTrdItf_HSStk(const char *psetupfile,ADDLOG plogfunc);
	virtual ~TTrdItf_HSStk();

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
};

//---------------------------------------------------------------------------
#endif
