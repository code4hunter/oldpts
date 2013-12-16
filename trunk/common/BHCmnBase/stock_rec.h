#ifndef stkrec_h
#define stkrec_h

//STOCK ���ýṹ

#pragma pack(4)

/*
**��Ʊ/etf��״̬
*/

enum stock_state
{
	//���״̬
	ssComplete=100 ,        //ȫ���ɽ�
	ssUnConfirm=-100,       //δ��
	ssPartBargain=51,       //���ֳɽ�
	ssNothing=50,           //û���κγɽ�
	ssOrdFault=-50,         //�µ�ʧ��
	//�м�״̬
	ssOrdering=0,           //�µ��������ǰ
	ssQrying=1              //��ѯ�ȴ���
};

/*
**�����г����ƽ�����һ���г��깺���
**����
*/

enum operate_type
{
	otBuy=1,                //���깺
	otSell=2,               //�������
	otWithdrawBuy=-1,       //������
	otWithdrawSell=-2       //������
};

/*
**��Ʊ����ETFί�нṹ
*/

struct stock_order
{
	char code[10];          //����
	stock_state state;		  //��ǰ״̬		
	operate_type operate;		//���� 
	char ord_id[10];        //ί�к�
	int ord_num;            //ʵ�ʵ�ǰί������
	float ord_price;        //ʵ�ʵ�ǰί�м۸�
	int goal_num;           //Ŀ����
	float goal_price;       //�����۸�
	int date;               //���� 2004/8/1->20040801
	int time;               //����µ�ʱ�� 1:10:05->011005
};

/*
**��Ʊ����ETF���׵Ľṹ
*/

struct stock_trade
{
	int id;                 //��¼ID	
	stock_order so;         //ί��
	int deal_num;           //�ɽ�����
	float deal_price;	      //�ɽ�����	
	int time;               //���ɽ�ʱ��
};

#pragma pack()

#endif