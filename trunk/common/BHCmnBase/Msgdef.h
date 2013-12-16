//---------------------------------------------------------------------------

#ifndef MsgdefH
#define MsgdefH
//---------------------------------------------------------------------------
#include "..\..\etfs\com\TaskStp.h"


#define  NAME_SIZE  		  128
#define  FNM_COMMAND          "COMMAND"  //{TCommand(1)}

#define  CMD_START_SERVER     0x5050	//���������� 	{Param1=0,Param2=0}, 
#define  CMD_STOP_SERVER      0x5051    //ֹͣ
#define  CMD_SETUP_SERVER     0x5052    //����

#define  CMD_START_TASK_ALL   0x5001	//������������	{Param1=0,Param2=0}, 
#define  CMD_STOP_TASK_ALL    0x5002	//ֹͣ��������	{Param1=0,Param2=0}, 
#define  CMD_PAUSE_TASK_ALL   0x5003	//��ͣ��������	{Param1=0,Param2=0}, 
#define  CMD_RESUME_TASK_ALL  0x5004	//������������	{Param1=0,Param2=0}, 

#define  CMD_START_TASK       0x5005	//����ָ������	{Param1=TaskID, Param2=0}, 
#define  CMD_STOP_TASK        0x5006	//ָֹͣ������	{Param1=TaskID, Param2=0}, 
#define  CMD_PAUSE_TASK       0x5007	//��ָͣ������	{Param1=TaskID, Param2=0}, 
#define  CMD_RESUME_TASK      0x5008	//����ָ������	{Param1=TaskID, Param2=0}, 
#define  CMD_TASK_STATE       0x5009	//�����״̬,������״̬�иı��ʱ���ɷ���˷����ͻ���
										//{Param1=TaskID, Param2=State}, 

#define  CMD_SETUP_TASK       0x5010	//����Ĳ������� 
										//{Param1=TaskID, Param2=0; + [TTaskInfo(1)]}
										
#define  CMD_TASK_LOG         0x5011	//������־ 
										//{Param1=TaskID, Param2=0; + [Message(0..n)]}
										//{Message="msg1" + "\r\n" + msg2 + "\r\n"..."} 
											
#define  CMD_SERVER_LOG	      0x5014	//��������־,ͬ�ϣ�
#define  CMD_CREATE_TASK      0x5012	//�½����� 
										//Client ==> Server {Param1=0,Param2=0; +[TTaskInfo(1)]}  
							 			//Server ==> Client {Param1=Return ,Param2=TaskID + [TTaskInfo(1)]} $ע������$
							 			//{Return= 1(�ɹ�), -1(ʧ��)}
							 			
#define  CMD_LOGIN_SERVER     0x5013	//��½ʱ�ĳ�ʼ����Ϣ����Param1=1ʱ�ɿͻ��˷�������������½����Param1=2ʱ�������Ӧ�ͻ��˵ĵ�½����
										//Client ==> Server {Param1=1, Param2=0; +[TClientInfo(1)]}
										//Server ==> Client {Param1=2, Param2=Return; [TServerInfo(1) + TTaskInfo(0..n)]}
										//{Return=-1:���ܵ�½��1:���Ե�½�������Կ���, 50:���Կ��� }

#pragma pack(push, 1)
struct TClientInfo {  
	char ciUserName [NAME_SIZE];
  	char ciPassword [NAME_SIZE];
};

struct TServerInfo {
  	int  siState;// -1   ����ֹͣ�� 1    ���ڽ��� 0    �ǿ����ڼ� 2    ������ 3    ������ 4    ��������
  	WORD siTaskNums;
	//������Ҫ�趨��
	char siHQSvr[16];            //�����������ַ
	char siHQPath[MAX_PATH + 1]; //����·��
	int  siHQPort;               //����˿�

	long siAMOpen;							 //���翪��
	long siAMClose;              //��������
	long siPMOpen;               //���翪��
	long siPMClose;              //��������

	int	 siMonPort;               //��ض˿�
	char siMonSvr[20];           //����IP
	char siBulletinPath[MAX_PATH+1]; //ETF�䷽�ļ�·��
	char siUDLPath[MAX_PATH+1];  //���ݿ�����ļ�·��
};

struct TTaskInfo {
  	WORD   tiTaskID;
  	WORD   tiState;					//0 �������У�1�ɿ��������У�2���ɿ���������,3��Ҫ����,4��Ҫ����
  	char   tiName[NAME_SIZE];

  	// Add Task Setup Information
	float  tiEtfOverStkGate;      //��۷�ֵ
	float  tiStkOverEtfGate;      //�ۼ۷�ֵ
	float  tiStopV;				 //��ͣ��ֵ
	float  tiStopFix;             //��ͣȱ�� ��

	float  tiStkHandTax;			 //���ַ�
	float  tiFundHandTax;
	float  tiStkCost;			 //���з���
	float  tiFundCost;
	float  tiFundCreateCost;      //����
	float  tiFundRedeemCost;      //���

	int    tiQryInterval;         //ÿ�β�ѯ���ʱ��
	int    tiTimeout;             //��ѯ��ȴ�ʱ��
	int	   tiMaxPrcChgV;			 //ί�м۸�仯����ʱ
	int    tiWaitTime;            //�ȴ����볷��
	int    tiAfterMaxPrcChgV;	 //�����ȴ�ʱ��ʱ����۸�仯�����ֵ�ھͲ�����
	int    tiSellType;			 //����Ʊʱ��0--���������µ�, 1---���������µ�,����ʣ��ɽ���<100,��Ĭ��ȫ���ɽ�,2 --������֣������һ���µ������·�������
	int    tiMinEtfTrdVol;		 //��СETF������������=100000
	float  tiStkRed;			//��Ʊ�̿������
	float  tiEtfRed;			 //Etfs�̿������

	bool   tiEmunTrd;              //�Ƿ���ģ�⽻��

	char   tiAccount[20];			 //�˻���
	char   tiPassword[10];         //����
	double tiMinAccMoney;        //��С���˻����ö�

	int    tiBuySellMode;			 //�µ���ʽ 0��1��2��3,4,5,6
	int    tiCpUsePriceType;        //����ʱʹ�õ��̿ڼ۸�����

	int    tiNumEtf;				 //������λʱִ���깺���

	bool   tiUse6Vlm;				 //ʹ�ù��Ƶ������̿�
	float  tiVlm6Agio;			 //���������̿ڵ��������
	float  tiVlm6Alpha;			 //���������̿ڵ�Alpha
	int    tiVlm6EventN;			 //���������̿ڵ��¼���
	int    tiVlm6LoadHisN;			 //���������̿ڼ��ص���ʷ������

	int    tiTrdMode;               //0��ʾ���С��������1��ʾ�ۼ�С��������
								 //2��ʾ������С���뵥λ����������

	float  tiMinProfit;           //����С�����ֵ���ж϶Գ�
	int    tiMaxFault;            //�������ٴ�����ʧ�ܾ���ͣ����
	int    tiMaxErr;              //���ֶ��ٸ������ֹͣ������
	HOLDSECURITY tiInitHoldSecu[MAX_BIND_STKS+1];
};

struct TCommand {
  	WORD CmdID;
  	int	 Param1;
  	int  Param2;
};

#pragma pack(pop)

#endif
