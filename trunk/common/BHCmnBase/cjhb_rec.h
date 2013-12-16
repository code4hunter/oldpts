#ifndef cjhb_rec_h
#define cjhb_rec_h


#define GDDM_LEN 11
typedef char GDDM[GDDM_LEN];


#pragma pack(1)
//�ɽ��ر���¼

//cjbh	Int		4	�ɽ���š�
//gddm	Char	10	�ɶ��ʺţ����ַ�Ϊ��д��ĸ��
//bcrq	Char	8	�ɽ����ڡ���ʽ��YYYYMMDD
//cjsl	Char	10	�ɽ�����������������ʾ��������
//bcye	Char	10	�������ɽ����������
//zqdm	Char	6	֤ȯ���롣
//sbsj	Char	6	�걨ʱ�䡣��ʽΪ:HHMMSS
//cjsj	Char	6	���γɽ�ʱ�䡣��ʽΪ:HHMMSS
//cjjg	Char	8	���γɽ��۸�
//cjje	Char	12	���γɽ���
//sqbh	Char	10	ͬashare_ordwth�ж�Ӧ��¼��reff�ֶΡ�
//bs	Char	1	ͬashare_ordwth�ж�Ӧ��¼��bs�ֶΡ�

struct cjhb_rec
{
	long	no;				//�ɽ����
	char	gddm[GDDM_LEN];	//�ɶ�����
	long	date;			//YYYYMMDD
	long	deal_num;		//�ɽ�����
	long	stk_bal;		//�������Ʊ���
	char	code[7];
	long	ord_time;		//HHMMSS
	long	deal_time;		//HHMMSS
	float	deal_price;
	double	deal_money;		//�ɽ����
	char	ord_id[11];		//ί�к�
	char	bs;				//B�������룬S��������, C ������, T ��������
							//����Ϊ������deal_numΪ������
};

enum CJHBFUNC 
{ //��������
	ftLogin        = 0,  //��½
	ftLogout	   = 1   //ע��
};

struct cjhb_login_req
{
	int  type;			//1 �Ͻ���A,2 ���A.... Ŀǰֻ֧��1
	char gdzh[20];		//�ɶ��˺� 
};

struct cjhb_req
{
	int FuncType;
	union
	{
		cjhb_login_req login;	
		cjhb_login_req logout;	
	};
};

struct clhb_ans
{
	int AnsCount; //�ظ����ݰ�����
	int CurAnsNo; //��ǰ�ظ����ݰ����
	int RetVal;   //����ֵ,'0'Ϊ��ȷ
	union
	{
		cjhb_rec cr;
	};
};

#pragma pack()

#endif