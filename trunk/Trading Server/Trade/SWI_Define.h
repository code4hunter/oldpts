#ifndef SWI_DEFINE_H
#define SWI_DEFINE_H

/*
�Σ����������Χ����ϵͳЭ��ӿڱ�׼
V2.76��
For
External Application Gateway (AG-X) 
ͨ��Э���׼


һ��  �����ֵ�
1���ͻ��ʺ���� account_type
'0' ------  A���ʽ��ʺ�
'1' ------ ��A֤��
'2' ------ ��A֤��
'3' ------ ��B֤�ţ�С�ڵ���6λ����ʾ�Ϻ�B���ʽ��ʺţ�
'4' ------ ��B֤�ţ�С�ڵ���6λ����ʾ����B���ʽ��ʺţ�
'5'  ------  A���ر�ת���г�֤��
'6' -----  B���ر�ת���г�֤��(С�ڵ���6λ����ʾ�ʽ��ʺ�)

ע��
��1��	ʹ��6λ�ʽ��ʺţ�ʮλ�ʽ��ʺŵ�ǰ4λӪҵ����ţ��ɿͻ��˷���������Ϣͷ��dest_dpt��������6λ�ʽ��ʺ���ȫ��ȥ����߶����"0"����
��2��	"�ͻ��ʺ����"��201 ί�С�202��������ʹ���ʽ��˺Ż�֤ȯ�ʺ��⣬���๦�ܵ��ñ���ʹ���ʽ��˺š�

2��ί�з�ʽ entrust_method
�ɿ�������������ȡ��
ע��
����������ί�з�ʽ�������£�
��1��	'z'  ���ڽ����ӡ��"���ʺ�"����ʱ�ͻ����벻У��
��2��	'Z'  ���ڽ����ӡ��"���ʺ�"����ʱ�ͻ�����ҪУ��

3���������  bs_type
'1' ----- ���루��������ʽ����/LOFs���Ϲ����깺/ETFs���깺��
'2' ----- ��������������ʽ����/LOFs�����/ETFs����أ�
'3' ----- ת�йܣ����ڣ�
'4' ----- ��ɣ����ڣ�
'5' ----- ���� (��ѯ����г��֣�������������Ӧ����ר�ó�������)
'6' ----- ���� (��ѯ����г���)
'7'----- �Ϲ�������ʽ����
'8'  -----ת�ɣ�����¼��ί�У���ѯ����в����֣�
'a'   ----  ���������ڽ��
'b'  ----  �����ѣ����ڽ��
     
4����������� exchange_no
0 ----- ȫ��A�ɣ������ڲ�ѯ��
1 ----- �Ϻ�A��
2 ----- ����A��
3 ----- �Ϻ�B��
4 ----- ����B��
5 ----- A���ر�ת���г�
6 ----- B���ر�ת���г�
7 ----- ����ʽ����

5��ί��״̬  entrust_status������ȷ��״̬��
'L' ----- ί��ȡ��
'l' ------ ί����ʱ״̬��СдL��
'0' ----- δ�걨
'1' ----- ���걨
'2' ----- ���걨
'4' ----- ��Чί��
'5' ----- ���ֳ���
'6' ----- �ѳ���
'7' ----- ���ֳɽ�
'8' ----- �ѳɽ�

6������ currency_type
'1' ----- �����
'2' ----- ��Բ
'3' ----- �۱�

7�������8�ֽ�SQLMONEY����ʾ���ڲ���ʾΪ__int64����ʮ���ƺ���λ������λС��, �磤12.32  ��ʾΪ 123200
typedef struct _SWIMoney    // Same as the type CURRENCY in VB
{
		DWORD lo_value;
		long  hi_value;
} SWIMoney;

ע�⣺ �Կ���ʽ�����ί�л��ѯ���ع�Ʊ����(fund_amount��ʹ��SWIMoney����ʾ)����ʮ���ƺ�4λ����4λС������1000000.12��ʾΪ10000001200��

8���۸�ʹ��LONG����ʾ����ʮ���ƺ���λ������λС������8.18��ʾΪ8180
typedef long	 SWISmallMoney;

9���ʺ�״̬
10���ͻ����
11��֤ȯ���
'0'          ��ɽɿ�  
'1'          ��ͨ����  
'2'         ����      
'3'          ����      
'4'          Ͷ�ʻ���  
'5'          תծ      
'6'          �ر�ת��  
'7'          ������ծ  
'8'          �¹��깺  
'9'          ��ծ(ʵȯ)
'a'          �Ǽ�ָ��  
'b'          ����ָ��  
'c'          ��ծ�ع�  
'd'          ��ծ(����)
'f'          ��ֵ�깺  
'g'          �ع��Ǽ�  
'h'          �ع�����  
'i'          ��ծת��  
'j'          ��ҵծȯ
'k'          LOF����
'l'          LOF/ETF����
'm'         ETF����
'n'          ETF�깺/���

 
12��������𲹳�bs_type2
����һЩ��ѯ�򽻸�ķ��ؽ�������޷�ͨ��Ŀǰ"�������bs_type"��������һЩҵ���¶���"������𲹳�bs_type2"���£�
1         	����
2		����
40		��ȯ
41		���ʹ���
42		��ȯ����
43		����
  ����------------�������Ժ�Э���ж��⹫��
  �ر�ע�⣺
�������ֵ䣬Ŀǰֻ������"���ܺ�0x505 ��ѯ���"��

13���ģţӼ����㷨˵��
���ӿ���ʹ��DES�㷨��Դ��������������Χ����ϵͳЭ��ӿ�һ�£�����des.cpp��dll.h��crc.c��ʹ�÷���ʾ�����£� 
desinit(0); 
dessetkey("8λ������Կ"); 
endes(char * block)��      //��block����
dedes(char *block);  //��block���� 
desdone();
DES�㷨��Դ������Ӫҵ������������������׼���ṩ�������̡�

14��֤ȯ���
'1'          ��ծ
'2'          ����
'3'          A��
'4'          �ع�

���� ��ȫ�Դ�ʩ
�ڽ�����Կ֮�󣬲���DES����

���� �ⲿί������Э��ӿ�

˵��:
	1. �ͻ���Ӧ�ò����������ӵ�����Э�� TCP �� SPX ���ӵ�����������
	2. ����������ȷʡ�����˿�
		TCP Listen socket: 18888
		SPX Listen socket: 18888

��, �ⲿί������Э��ӿڿ�����
	SWI Software Development Kit

	SWINDR.H   ---  ��������������ͷ�ļ�
	SWIRES.H   ---  ���������ͷ�ļ�
*/

// �ṹ��ԱӦ�ֽڶ���
#pragma pack(push, 1)

typedef long	SWISmallMoney;
typedef struct _SWIMoney
{
        DWORD lo_value;
        long  hi_value;
} SWIMoney;

//��Ϣͷ
struct SWI_BlockHead
{
        WORD    block_size;
        WORD    crc;  		// ���¸��ֶ�block_type�� (������block_size��
                                // crc�ֶα���) ��CRCУ����
        BYTE     block_type;  	// ������  	1 - ����         ��SWI_???Request��
                                                //         	2 - ����״̬     ��SWI_???Return��
                                                //          	3 - ��ѯ�����   ��SWI_???Result��
                                                //          	5 - ȡ����ѯ
                                                //          	4 - ������Ϣ
                                                //          	5 - ����Ի�
                                                //          	6 - ��������(������Կ)
                                                //          	7 - ����Ӧ��(������Կ)
                                                //          	8 - ��չ������Ϣ
                                                //          	9 - ��չӦ����Ϣ
        BYTE   reserved1;    	// ������������0
        WORD   function_no;  	// ���ܺ�
        long   cn_id;      	// �������Ӻ�
        WORD   source_dpt;      // �������ڲ�ʹ�ã�ԭӪҵ����
        WORD   dest_dpt;    	// Ŀ��Ӫҵ�����
};

// ��ѯ�����ͨ��ͷ
struct SWI_QueryResultHead
{
	struct SWI_BlockHead head;
	WORD   row_no;
};

// ��ѯ���ؼ�ͨ��ͷ
struct SWI_QueryReturnHead
{
	struct SWI_BlockHead head;
	long return_status;//����״̬
};

//�ͻ��˷���"��������"��Ϣ
struct SWI_ConnectRequest
{
	SWI_BlockHead  head;    	// ��Ϣͷ block_type == 6
        WORD  method;     	   	// �ͻ��˵ļ��ܷ�ʽ��method=1��
        char  entrust_method;   	// ί�з�ʽ���������ֵ�˵����
        BYTE  return_cp;        	// �ͻ���ϣ���ķ��ؽṹ�������ֶεĴ���ҳ
                                        //   	0 -- MBCS  ��CP936�������ģ�
                                        //   	1 -- Unicode(Java�ͻ���Ҫ)
        BYTE   network[4];      	// �ͻ���Novell���κ�
        BYTE   address[6];      	// �ͻ���������ַ��Novell�ڵ��ַ��
        WORD   client_major_ver;	// �ͻ���Э��ӿ����汾�ţ����ڰ汾Э�̣�
        WORD   client_minor_ver;// �ͻ���Э��ӿڴΰ汾�ţ����ڰ汾Э�̣�
        WORD   key_length;      // RSA��Կ���ȣ���method 1, key_length=0��
};

//��Ϣͷ�У�
//block_type	6 - ��������(������Կ)
//function_no  	����
//cn_id      	0
//dest_dpt    	����

//��������"����Ӧ��"��Ϣ
struct SWI_ConnectResponse
{
        SWI_BlockHead  head;    	// ��Ϣͷ block_type == 7
        WORD return_value;		// ����״̬
        WORD method;             // ����ͬ��ļ��ܷ�ʽ
        char department_name[60];// Ӫҵ�����ƣ�MBCS/Unicode��
        WORD key_length;         // DES��Կ���ȣ�key_length=8��
        BYTE des_key[8];         // DES��Կ(����"ExpressT"��Ϊ��Կdes����)
};
//��Ϣͷ�У�
//block_type	7
//function_no  	����
//cn_id      	���䵽�����ӱ�ʶ���ͻ���Ӧ��������ӱ�ʶ����������������  �е���Ӧ�ֶ�
//dest_dpt    	����Ӫҵ�����

/*ע��
1. ��ǰ��ҵ����Ӧ�ã��涨��Կ��������method == 1��������������һ�������DES��Կ��������Ӧ���з��͵��ͻ��ˣ��Ժ��ͨ�����ݾ�����DES���ܡ�

2. ��Ӫҵ��(ͨ��ͨ��)������������У������������������head��dest_dpt��ָ���ͻ�ָ����������Ӫҵ����ţ�����Ӫҵ��Ҳ����0��ʾ���� ����ΪЭ�̼��ܷ�ʽʱ�ͻ���Ӧ�ó����в�֪���ͻ��ʺź�����Ӫҵ��������SWI_ConnectRequest��dest_dpt����ָ����

3��Լ��������dest_dptΪĿ��Ӫҵ����ţ��ͻ�ָ����������Ӫҵ������Ӧ���е�dest_dptΪ����Ӫҵ����ţ��ͻ���Ӧ�ó���ֱ�����ӵ���������Ӫҵ����
*/

/*����Լ��
Ϊ��ʵ��"Ӧ�ó���汾ͳ��"������Ҫ��ÿ��Ӧ�ó���������ʱ������¹�����
1��	��AGX�����������ӣ����������������
2��	����"���ܺ�0x801"SWI_QueryCommon���������£�
     SWI_BlockHead.cn_id=0(????,�������Ӻ�)
       function_id=1
       cmd_buf="��Ʒ����|������|�汾��|��������"
       ���أ�100�ɹ�  ��=0ʧ��
*/

/*
//������Ϣ
struct SWI_QueryCommon
{
	struct SWI_BlockHead head;		// function_no = 0x801,block_type=1
	long   function_id;         		// �ӹ��ܺţ������壩
	char   cmd_buf[4096];     		// ��ѯ������������֮����"|"�ָ
};
//Ӧ������
struct SWI_QueryCommonResult
{
	struct SWI_BlockHead head;	    // function_no==0x801,block_type==3
	WORD    row_no;                  // ��¼��
	//short   len;                     //��ѯ����ĳ���
        //char    ret_buf[len];           //��ѯ�����������֮����"|"�ָ
};
//RETURNӦ��
struct SWI_QueryCommonReturn
{
	struct SWI_BlockHead head; 		// function_no = 0x801,block_type==2
	long return_status;
};
//����״̬:
//  > 0   ��ѯ�ɹ�
//  <= 0  ��ѯʧ��

*/

//���ܺŸ��ֽڱ�ʾ���ܴ��ࣺ
//1 --- �ʺŲ���
//2 --- ����
//3 --- ���������ѯ
//4 --- �����������ѯ
//5 --- ��ʷ��������ѯ
//6 --- ��֤ȯ��Ϣ
//9 --- ��������

//////////////////////////////////////////////////////////////////////////
//1�����ܺ�0x101 У�����������, ���ʺ� SWI_FUNC_OPEN_ACCOUNT
//  ���ô˹��ܣ���У�����������ͨ�����ÿͻ����ʺŽ����������׵Ĵ�״̬��
//  ֱ���������֮һ������
//	1�������ӵ��ù���20�ر��ʺ�
//	2�������ӵ�����һ�ι���2������һ���ʺ�
//	3�������ӹرա�
//////////////////////////////////////////////////////////////////////////

//������Ϣ
struct SWI_OpenAccountRequest
{
        struct SWI_BlockHead head;	// function_no==0x101, block_type == 1
        char   account_type;     	// �ͻ��ʺ����ͣ��������ֵ�˵����
        char   account[16];      	// �ͻ��ʺ�
        char   pwd[8];           	// ��������
        short  op_code;             // ����Ա����
        unsigned  long   flag;         //"��������"�жϱ�־λ���,ÿһ��������λ��Ӧһ��"��������",ȱʡֵΪ0��ʾ���ж��κ�"��������"
        char   productno [7];		    //��Ʒ��Ϣ��ţ�5λ�����������Ĳ�Ʒ����+2λ�Ӳ�Ʒ���루��7λ�ַ�����ȱʡֵΪ�ա�

};

/*Ŀǰ�Ѷ���flag��"��������"�жϣ��б����£�
      ������λ         ��Ӧ��ʮ��������       ��Ӧ����������         ��Ӧ�ķ���״̬
        1               0x0001              ������ʹ��"������"     -159
        2               0x0002              δ����                   ��
        3               0x0004              δ����                   ��
        4               0x0008              δ����                   ��
        5               0x0010              δ���壬������           ��

�Կ�Ӫҵ��(ͨ��ͨ��)��������
��head�� dest_dpt��ָ���ͻ�ָ����������Ӫҵ����ţ���ͬ����
*/
//Ӧ����Ϣ
struct SWI_OpenAccountReturn
{
	struct SWI_BlockHead head; 	// function_no==0x101
	long    return_status;  	// ����״̬
};

//����״̬��
//  >  0  �ɹ�
//  <= 0  ʧ��
//ע���������״̬Ϊ-159����˵���û������Ϊ������

//////////////////////////////////////////////////////////////////////////
//
//4�� ���ܺ�0x201 ¼��ί��SWI_FUNC_ADD_ENTRUST
//���ܣ� ¼���ⲿί�У��ʽ����Ʊ������͸֧
//
//////////////////////////////////////////////////////////////////////////
//������Ϣ
struct SWI_AddEntrustRequest
{
	struct SWI_BlockHead head;// function_no == 0x201, block_type==1
	char    account_type;     // �ͻ��ʺ����ͣ��������ֵ�˵����
	char    account[16];      // �ͻ��ʺ�
	BYTE    exchange_no;      // ��������ţ��������ֵ�˵����
	char    bs_type;          // ������𣨼������ֵ�˵����
	char    security_code[7]; // ֤ȯ����
	long    stock_amount;     // ί������
	SWISmallMoney price;      // ί�м۸�SWISmallMoney�������ֵ�˵������ͬ��
	short   effect_days;      // ��Ч���� 
        SWIMoney   apply_amount;  //������
        BYTE    mark;             //�Ƿ�������� 1Ϊ�������,0Ϊ������ ȷʡΪ0
        int	Frozen_no ;        //֤ȯ���ʽ𶳽���ˮ��(��֤ͨר�ã�ȱʡΪ0)
        SWIMoney fund_amount;  //ί������(֧�ֿ���ʽ����С���ݶ�)
        char    Entrust_sign[10]; //����ǩ��(ȱʡΪ'')
        SWIMoney    Cash_limit ;  //ί���ʽ��ȣ�ȱʡΪ0��ʾ������ί���ʽ���;����ί�ж����ʽ𳬹�ί���ʽ���ʱ����ί��ʧ��,B���ݲ����ƣ�
};
/*
ע�� 
1����Ҫ����Χ��������ʱ"ί������"����ֵ��"ί������(֧�ֿ���ʽ����С���ݶ�)"
���������ֱ�����ȣ�������Ϊί����Ч��
2�����Կ���ʽ�����ί�л��ѯ���ع�Ʊ����(fund_amount��ʹ��SWIMoney����ʾ)��
��ʮ���ƺ�4λ����4λС������1000000.12��ʾΪ10000001200����ͬ��
*/
//Ӧ����Ϣ
struct SWI_AddEntrustReturn
{
	struct SWI_BlockHead head;
	long return_status;   	      	//  ����״̬
	long entrust_sn;      		//  ί�б��
        SWIMoney  frozen_money;    	//�����ʽ���
        long     frozen_amount;    	//����֤ȯ����
};
//����״̬��
//  >  0  �ɹ�
//  <= 0  ʧ��

///////////////////////////////////////////////////////////////////////////////
//
//5�� ���ܺ�0X202 ����SWI_FUNC_WITHDRAW
//
//////////////////////////////////////////////////////////////////////////////
// ������Ϣ
struct SWI_WithdrawEntrustRequest
{
	struct SWI_BlockHead head; // function_no == 0x202, block_type==1
	char    account_type;      // �ͻ��ʺ�����
	char    account[16];       // �ͻ��ʺ�
	BYTE    exchange_no;       // ���������
	long    entrust_sn;        // ί�б��
};

//Ӧ����Ϣ
struct SWI_WithdrawEntrustReturn
{
	struct SWI_BlockHead head; // function_no == 0x202, block_type==1
	long return_status;        // ����״̬
        long withdraw_sn;          //�������
};
//����״̬��
//>0  ------ ��������
//<=0 ------ ����ʧ��

//////////////////////////////////////////////////////////////////////
//
//7�� 0x301 ��ѯ�ʽ���� SWI_FUNC_QUERY_MONEY
//
//////////////////////////////////////////////////////////////////////

// ������Ϣ
struct SWI_QueryMoneyRequest
{
	struct  SWI_BlockHead head; // function_no == 0x301,block_type==1
	char    account_type;      // �ͻ��ʺ�����
	char    account[16];       // �ͻ��ʺ�
	char    currency_type;     // ����
};

//Ӧ����Ϣ
struct SWI_QueryMoneyReturn
{
	struct	  SWI_BlockHead head; //function_no == 0x301,block_type==2
	long	  return_status; // ------ ����״̬
	char      name[20];   // ------ �ɶ�����
	SWIMoney  deposite;   // ------ �����ʽ����
	SWIMoney  available;  // ------ ��ȡ�ʽ����
	SWIMoney  buyable;    // ------ �����ʽ����
};
//����״̬��
//>0 ------ ��ѯ�ɹ�
//<= 0 ------ ��ѯʧ��

//////////////////////////////////////////////////////////////////////////////////
//
//  10�����ܺ�0x401 ��ѯ��ƱSWI_FUNC_QUERY_STOCK
//
//////////////////////////////////////////////////////////////////////////////////

//������Ϣ
struct SWI_QueryStockRequest
{
        struct SWI_BlockHead head; // function_no == 0x401, block_type==1
        char   account_type;       	// �ͻ��ʺ����ͣ��������ֵ�˵����
        char   account[16];        	// �ͻ��ʺ�
        BYTE   exchange_no;        	// ��������ţ��������ֵ�˵����
        char   security_code[7];   	// ֤ȯ���루�ձ�ʾȫ����
        WORD   max_results;        	// ����ѯ��¼����0��ʾȫ����
        BYTE   flag;      			// ����ӯ���������ݱ�־ 
                                                //  =0��ȱʡ�������ض�Ӧֵ����Ӧ�ֶ�Ϊ0
                          			//  =1������ӯ����������
                          			//����flag��Ҫ�����ٵ���flag=1,��������Ӱ��
	char stock_account[15];      	//��ѯ֤ȯ�ʺ�����,����֤ȯ�ʺ�Ϊ�������˽������ȱʡ
                                        //Ϊ�ַ���'0'������ϸ˵��
};
//��ѯ�����Ӧ��
struct SWI_QueryStockResult
{
	struct SWI_BlockHead head;  // function_no == 0x401,block_type==3
	WORD row_no;                //  ��¼�� ,  0xFFFF -- ���������(�������������Ч)
	BYTE exchange_no;           //  ���������
	char security_code[7];      //  ֤ȯ����
	char security_name[18];     //  ֤ȯ���ƣ�MBCS/Unicode��
	long deposite;              //  ��Ʊ���
	long available;             //  �������
	SWISmallMoney hold_price;   //  �ֲ־���
	SWISmallMoney current_price;//  ���¼�
	SWIMoney past_profit;       //  ����Ӯ��
	char security_account[11];  //  �ɶ�����
	long last_month_balance_date; //B������ ��������
	long last_month_balance;	//B������   ���½���
	long today_bought_amount; 	//B������	���շ�����
	long today_sell_amount;     //B������	���շ�����
        char stock_account[20];     // �ɶ�����
        SWIMoney today_buy_money;   // ��������ɽ���AB����Ч��(?)
        SWIMoney today_sell_money;  // ���������ɽ���AB����Ч��(?)
	SWIMoney cur_market_value;    // ��̬����֤ȯ��ֵ��flag=0ʱ���̶�����0��
	char    stock_type[1];        //֤ȯ���
	BYTE report_unit_type;      // �걨��λ���ͣ�����ծȯ��=1����ʾ�����걨�����ڹ�Ʊ����ȣ�=0����ʾ�����걨;����B�ɣ�=0����
	SWIMoney    fund_deposite;           // �������չ�Ʊ��֧�ֿ���ʽ����С���ݶ
        SWIMoney    fund_available;          // ���п�����֧�ֿ���ʽ����С���ݶ
        SWIMoney    unlisted_amount;        //δ���йɷ�����flag=0ʱ���̶�����0��
	SWISmallMoney   Unlisted_hold_price;     //δ���йɷݳֲּ۸�flag=0ʱ���̶�����0��
	BYTE market_value_flag;           //���������ֵ��־��0�������� 1�����㣩
        char    bond_interest[12];        //��ծ��ԪӦ����Ϣ(����С����)���ǹ�ծ����Ϊ��0��
        SWIMoney    hold_money;           //���н��
        SWIMoney    unlisted_hold_money;  //δ���н��
        long availableT;           //�����깺/��ؿ������
                                //(���ETFs����������ETFs��Ӧ��Ʊ���տ������깺�ķݶ��ETFs��������صķݶ�)�� 
};
/*
ע����֤ȯƷ��Ϊ��ծʱ���м۲�������ԪӦ����Ϣ��
ԭ0x801����function_id=203���ؽ�����пɼ�������Ĺ�ϵΪ��
   	��report_unit_type=0ʱ��ÿ�ֹ���=1
  	��report_unit_type=1ʱ��ÿ�ֹ���=10

�ɱ���=���������ճֲ־���*�������չ�Ʊ���*ÿ�ֹ���-������ʵ��ӯ����/���������չ�Ʊ���*ÿ�ֹ�����
  ��̬�ɱ���=���ɱ���*�������չ�Ʊ���*ÿ�ֹ���+����������-����������/�����������չ�Ʊ���+������������-��������������*ÿ�ֹ�����

  ��̬����֤ȯ��ֵ=���������չ�Ʊ���+������������-��������������*ÿ�ֹ���*�м�
	  ��ǰ����֤ȯ��ֵ=�������չ�Ʊ���*ÿ�ֹ���*�м�
  �����ڶ�̬����֤ȯ��ֵ����ǰ����֤ȯ��ֵ�� ���м�Ϊ0ʱӦ���������ճֲ־��ۼ��㣻 ���֤ȯ����ǹ�ծ����Ҫ���м��ϼӰ�ԪӦ����Ϣ��

  ������������������ƣ�
  ��̬�ֲּ�=���������ճֲ־���*�������չ�Ʊ���*ÿ�ֹ���+���������/�����������չ�Ʊ���+��������������*ÿ�ֹ�����
  ��̬��ʵ��Ӯ��=�����������-����̬�ֲּ�*��������������*ÿ�ֹ���+������ʵ��ӯ��
  ��̬����ӯ��=��̬֤ȯ��ֵ-��̬�ֲּ�*���������չ�Ʊ���+������������-��������������*ÿ�ֹ���

���ϼ��㹫ʽ��δ����'δ������ͨ�ɷ�'���֣�ʹ���߿������޸ġ����ϼ��㹫ʽ�����ο���
*/
//RETURNӦ��
struct SWI_QueryStockReturn
{
        struct SWI_BlockHead head;              // function_no== 0x401, block_type==2
        long return_status;                     //  ------ ����״̬
};
//����״̬��
//>0 ------ ��ѯ�ɹ�
//<= 0 ------ ��ѯʧ��
/*�ر�ע�⣺
1��	��security_code=��ʱ����ʾ��ѯ���й�Ʊ�ֲ������
2��	stock_accountΪ��ѯ�����ֶΣ�
��1������stock_account=��ʱ����ѯ����������ˣ��������������ʺ���Ϣ����
��2������stock_account<>�ն���stock_account<>'0'ʱ����ѯ������еļ�¼Ϊ"֤ȯ�ʺ�=stock_account"�ļ�¼��
��3������stock_account='0'ʱ��Ϊ�����ڲ�ʹ�õĹ���״̬����Χ��ֹʹ�ã������ڽ���ϵͳ����֧�ָ�״̬������ʾ��ѯ������޸�ǰ��ͬ����Ϊ
3.1).  security_code=�գ� accountΪ�������ʺ�ʱ�����ؽ���а����������ʺż�¼��accountΪ�ǹ������ʺ�ʱ�����ؽ����ֻ������Ӧ�ʺż�¼��
3.2).  security_code<>��: ����account�Ƿ�Ϊ�������ʺţ����ؽ����ֻ������Ӧ��������account�ʺŵ�һ����¼�����޼�¼����
3������flag������flag=0��Ϊȱʡֵ��������"��̬����֤ȯ��ֵ"��'δ���йɷ���'��'δ���йɷݼ۸�'���ֶΣ�flag=1ʱ����"��̬����֤ȯ��ֵ"�� 'δ���йɷ���'��'δ���йɷݼ۸�'���ֶΣ��������"���ܺ�0x801,��ѯ��������"��"function_id=203(��ѯ�ͻ���ӯ����������)"�����ڳɱ��ۡ���̬�ɱ��ۡ���̬�ֲּۡ���̬��ʵ��Ӯ������̬����ӯ�����ݣ�����ͨ�����ؽ������õ���
4��"���ܺ�0x801,��ѯ��������"��"function_id=203(��ѯ�ͻ���ӯ����������)" ����2003��4����Ѯȡ���ù���֧�֡�
5����Э��Ӱ汾2.72��ʼ�����ؽ�����а���"�������չ�Ʊ���"��'δ���йɷ���'��"������������"��"������������"����֮һ��Ϊ0�ļ�¼��
*/

/////////////////////////////////////////////////////////////////////
//
// 11�����ܺ�0x402�� ��ѯί��SWI_FUNC_QUERY_ENTRUST
//
/////////////////////////////////////////////////////////////////////
struct SWI_QueryEntrustRequest
{
	struct SWI_BlockHead head; 	// function_no == 0x402 ,block_type==1
	char    account_type;    	// �ͻ��ʺ����ͣ��������ֵ�˵����
	char    account[16];     	// �ͻ��ʺ�
	BYTE    exchange_no;     	// ��������ţ��������ֵ�˵����
	long    begin_date;      	// ��ʼ���ڣ����磺yyyymmdd��
	long    end_date;        	// �������ڣ����磺yyyymmdd��
	long    entrust_sn;      	// ί�б�ţ�0��ʾȫ����
	char    security_code[7];	// ��Ʊ���루�ձ�ʾȫ����
	WORD    max_results;     	// ����ѯ��¼��
	char 	stock_type;		// ֤ȯ���, ȱʡΪ�գ���ѯȫ��֤ȯ���.
};
//��ʼ����begin_date	��������end_date	��������
//��������	        0	                ��ѯ���յ���Чί��
//��������	        ��������        	��ѯ���е���ί�У��Ȱ��������걨������ί�С�Ҳ������һ�������걨��ҹ��ί��
//��ʼ����	        ��������	        ��ѯ��ʷ���е�������ʷί�У���������Ϊ"ί������"�������������յ�ί��


//  ��ί�н������
struct SWI_QueryEntrustResult
{
	struct SWI_BlockHead head; // function_no==0x402,block_type==3
	WORD   row_no;               //  ��¼��,  0xFFFF���������
	long   entrust_date;         //  ί�����ڣ����磺yyyymmdd��
	long   entrust_sn;           //  ί�б��
	char   entrust_time[9];      //  ί��ʱ�䣨���磺hh:mm:ss��
	BYTE   exchange_no;          //  ��������ţ��������ֵ�˵����
	char   security_account[11]; //  �ɶ�����
	char   security_code[7];     //  ֤ȯ����
	char   security_name[18];    //  ֤ȯ���ƣ�MBCS/Unicode��
	char   bs_type;              //  ������𣨼������ֵ�˵����
	long   stock_ammount;        //  ί������
	SWISmallMoney price;         //  ί�м۸�
	SWIMoney frozen_money;       //  ������
	char   entrust_method;       //  ί�з�ʽ���������ֵ�˵����
	char   entrust_status;       //  ί��״̬���������ֵ�˵����
	short  operator_no;          //  ����Ա����
	long   bargain_ammount;      //  �ѳɽ�����
	char   error_msg[32];		 //  ί��ʧ��ԭ��

        unsigned char    mark;             //�Ƿ�������� 1Ϊ�������,0Ϊ������

        char stock_account[20];        //����ʽ�����ʺ�
        SWIMoney fund_amount;   //ί��������֧�ֿ���ʽ����С���ݶ
        char entrust_sign[10];  //����ǩ��(ȱʡΪ'')
        long frozen_amount;      //����֤ȯ����
};
//ע�� ����Χ�����ʺź�֤ȯ����ѯ����֤ȯ���Ϊ'n'ETF�깺(��֤50ETF)�����ѯί�н���У������깺ί�з��صĽ��������1-51��ί�м�¼����ʶ��Ӧ50ֻ��Ʊ�Ķ���ɷݺͶ�Ӧ�깺ί�ж���Ľ��ֽ�������֣����������ί�з��صĽ����������1��ί�м�¼����ʶETF����Ķ���ݶ

// RETURNӦ��
struct SWI_QueryEntrustReturn
{
	struct SWI_BlockHead head;
	long return_status;     // ------ ����״̬
};
//
//��ʽ��
//  IF account_type��account��ȷ THEN
//      IF entrust_sn<>0 THEN
//         ����ί�б��entrust_sn���͡���ʼ����begin_date����ѯ
//      ELSE
//         ������ʼ����@begin_date���͡���������@end_date����ѯ��
//         ���жϡ�֤ȯ����@security_code��
//     ENDIF
//  ELSE
//     ����
//  ENDIF
//

//���أ�
//>0    ------ ��ѯ�ɹ�
//<=0   ------ ��ѯʧ��


/////////////////////////////////////////////////////////////////////////////
//
//12�����ܺ�0x403 ��ѯʵʱ�ɽ�SWI_FUNC_QUERY_BUSINESS
//
////////////////////////////////////////////////////////////////////////////

//������Ϣ
struct SWI_QueryBusinessRequest
{
	struct SWI_BlockHead head;// function_no==0x403,block_type==1
	char    account_type;     //�ͻ��ʺ�����
	char    account[16];      //�ͻ��ʺ�
	BYTE    exchange_no;      //���������
	long    entrust_sn;       //ί�б�ţ�0��ʾȫ����
	char    security_code[7]; //��Ʊ���루6�ո��ʾȫ����
	BYTE    flag;             //�ϲ���ʽ 0:ȱʡ������ί�кźϲ�
				              //           1:��Ʊ�������ϲ�
        long    begin_serial_no;       // �ɽ���ϸ��ʼ��ˮ�ţ�ȱʡֵ=0��
                                //��flag=2���ش���begin_serial_no��¼��
};
//���ճɽ��������
struct SWI_QueryBusinessResult
{
	SWI_BlockHead head;   	   // function_no==0x403, block_type==3
	WORD row_no;                 	// ��¼��, 0xFFFF���������
	BYTE exchange_no;            	   // ��������ţ��������ֵ�˵����
	char security_account[11] ;  	// �ɶ�����
	char security_code[7];      	// ֤ȯ����
	char security_name[18];     	// ֤ȯ���ƣ�MBCS/Unicode��
	char bs_type;               	   // ������𣨼������ֵ�˵����
	int stock_ammount;           // �ɽ�����
	SWISmallMoney price;        	   // �ɽ��۸�
	SWIMoney money;                 // �ɽ����
	char bargain_time [9];       	// �ɽ�ʱ�䣨���磺hh:mm:ss��
	unsigned char bargain_no[4];               // �ɽ����
        unsigned char sale_profit[4];//SWIMoney ;            //����ӯ�� v2.3
        unsigned char sale_profit1[4];//SWIMoney ;            //����ӯ�� v2.3
        char sea[8] ;                   //ϯλ��
        unsigned char report_serial_no[4];          //�걨���
        unsigned char entrust_no[4];                //ί�б��

        char stock_account[20];  		// �ɶ�����
        SWIMoney unfrozen_money;          //�ⶳ�ʽ���(A����Ч��B�ɷ���0)
        long   unfrozen_amount;         //�ⶳ֤ȯ����(A����Ч��B�ɷ���0)
        long   serial_no;               //�ɽ���ϸ��ˮ��(�Բ���flag=2��Ч,����=0)    
};
//��ע����ѯETFs��Ӧ��4���ֳɽ���¼���Ը����깺�����ʱ���ί�б�Ž��в�ѯ, ���ؽ�������а�������4����ETFs�ɽ���ϸ. 
//RETURNӦ��
struct SWI_QueryBusinessReturn
{
	struct SWI_BlockHead head;//function_no==0x403, block_type==2
	long    return_status;    // ------ ����״̬
};

//����״̬��
//>0   ------ ��ѯ�ɹ�
//<=0   ------ ��ѯʧ��

//����ʽ��
//  IF"account_type��account��ȷ"THEN
//      IF"entrust_sn<>0"THEN
//         ��"ί�б��entrust_sn"��ѯ
//      ELSE
//         ��"֤ȯ����security_code"��ѯ��
//      ENDIF
// ELSE
//     ����
// ENDIF
//
//ע�� ����"�绰ί��"��ͨ�������ڷ��ض�����¼���ɰ�"ί�б��"��ѯ��


/////////////////////////////////////////////////////////////////////
//
//13�����ܺ�0x503����ѯ��ʷ�ɽ�SWI_FUNC_QUERY_HISTORY_BUSINESS
//
///////////////////////////////////////////////////////////////////////

//������Ϣ
struct SWI_QueryHisBusinessRequest
{
	struct SWI_BlockHead head; //function_no==0x503,block_type==1
	char    account_type;      // �ͻ��ʺ�����
	char    account[16];       // �ͻ��ʺ�
	BYTE    exchange_no;       // ���������
	long    begin_date;        // ��ʼ����
	long    end_date;          // ��������
	char    security_code[7];  // ��Ʊ���루space(6)��ʾȫ����
	BYTE    flag;              // ��ѯ��ʽ
	WORD    max_results;       // ����ѯ��¼��
};
//��ʷ�ɽ��������
struct SWI_QueryHisBusinessResult
{
	struct SWI_BlockHead head;      // function_no==0x503,block_type==3
	WORD    row_no;                 // ��¼��,  0xFFFF���������
	BYTE    exchange_no;            // ��������ţ��������ֵ�˵����
	char    security_account[11];   // �ɶ�����
	char    security_code[7];       // ֤ȯ����
	char    security_name[18];      // ֤ȯ���ƣ�MBCS/Unicode��
	char    bs_type;                // ������𣨼������ֵ�˵����
	long    stock_change;           // ��������
	long    stock_deposite;         // ���η������Ʊ���
	SWISmallMoney occur_price;      // �ɽ���
	long    bargain_date;           // �ɽ����ڣ����磺yyyymmdd��
	char    bargain_time[9];        // �ɽ�ʱ�䣨���磺hh:mm:ss��
	long    bargain_no;             // �ɽ����
        
        SWIMoney sale_profit;           //����ӯ��
	char    stock_account[20];      // �ɶ�����
        SWIMoney	fund_amount;   	   //����������֧�ֿ���ʽ����С���ݶ
        SWIMoney 	fund_deposite; 	   //���η������Ʊ��֧�ֿ���ʽ����С���ݶ
};
//��ѯETFs��Ӧ��4���ֳɽ���¼���Ը����깺�����ʱ���ί�б�Ž��в�ѯ, ���ؽ�������а�������4����ETFs�ɽ���ϸ.

//RETURNӦ��
struct SWI_QueryHisBusinessReturn
{
	struct SWI_BlockHead head;// function_no==0x503, block_type==2
	long    return_status;    // ------ ����״̬
};

//����״̬:
//>0   ��ѯ�ɹ�
//<=0    ��ѯʧ��
//
//	����ʽ��
//	  IF"account_type��account��ȷ"THEN
//			 ��"��ʼ����begin_date"��"��������end_date"��ѯ��
//			 ���ж�"֤ȯ����security_code"
//	  ELSE
//		 ����
//	  ENDIF
//

/////////////////////////////////////////////////////////////////////////////////
//
//14�����ܺ�0x504 ��ѯ�ʽ���ϸ/�ͻ�̨��SWI_FUNC_QUERY_FUND_DETAIL
//
//////////////////////////////////////////////////////////////////////////////////

//������Ϣ
struct SWI_QueryFundDetailRequest
{
	struct  SWI_BlockHead head; // function_no==0x504,block_type==1
	char    account_type;      // �ͻ��ʺ�����
	char    account[16];       // �ͻ��ʺ�
	BYTE    exchange_no;       // ���������
	long    begin_date;        // ��ʼ���ڣ����磺yyyymmdd��
	long    end_date;          // �������ڣ����磺yyyymmdd��
	char    currency_type;     // ����
	WORD    max_results;       // ����ѯ��¼��
	BYTE	flag;		   // ��ѯ��ʽ 0 - �ʽ���ϸ
                                   //		   1 - �ͻ�̨��(���ʵ�)
};
//���ڼ�������������Լ��������Լ����Բ�ѯ��ϸ��
//��ʼ����begin_date	��������end_date	��������
//��������	        >=��������	        ��ѯ���е����ʽ���ϸ���Ȱ������յ��ʵ������ʽ�䶯��Ҳ������һ�����յ��ʵ������ʽ�䶯���ϸ�����Ȼ�ս��в�ѯ��
//��ʼ����	        ��������	        ��ѯ��ת����ʷ���������ʷ�ʽ���ϸ����������Ϊ"��������"���������������ʽ���ϸ

//�ʽ���ϸ/�ͻ�̨�ʽ������
struct SWI_QueryFundDetailResult
{
	struct  SWI_BlockHead head;	// function_no==0x504,block_type==3
	WORD    row_no;             	// ��¼��,  0xFFFF���������
	long    change_date;        	// �������ڣ����磺yyyymmdd��
	char    change_time[9];     	// ����ʱ�䣨���磺hh:mm:ss��
	SWIMoney change;            	// �������
	SWIMoney deposite;          	// ���η������ʽ����
	char    abstract[32];       	// ժҪ��MBCS/Unicode��
	long    serial_no;          	// ��ˮ��
	char    security_code[7];       // ֤ȯ����
	char    security_name[18];      // ֤ȯ���ƣ�MBCS/Unicode��
	long 	stock_ammount;      	// ֤ȯ�ɽ��������������룻����������
	SWISmallMoney price;        	// ֤ȯ�ɽ�����
        long    pre_amount;             // ǰ֤ȯ����
        short business_flag;  //ҵ���־
        char stock_account[16];//�ɶ��ʺ�
        SWIMoney  fund_amount;   //֤ȯ�ɽ�������֧�ֿ���ʽ����С���ݶ
        SWIMoney  fund_pre_amount; 	//ǰ֤ȯ������֧�ֿ���ʽ����С���ݶ

};
//RETURNӦ��
struct SWI_QueryFundDetailReturn
{
	struct SWI_BlockHead head; //   function_no==0x504, block_type==2
	long    return_status;  // ----- ����״̬
};

//��ʽ��
//  IF"@account_type��@account��ȷ"THEN
//         ��"��ʼ����@begin_date"��"��������@end_date"��ѯ��
//         ���ж�"֤ȯ����@security_code"
//  ELSE
//     ����
//  ENDIF
//
//���أ�
// >0   ------ ��ѯ�ɹ�
// <=0   ------ ��ѯʧ��

//////////////////////////////////////////////////////////////////////
//
//16�����ܺ�0x601,��ѯ֤ȯ��Ϣ  SWI_FUNC_QUERY_SECURITY_INFO
//
//////////////////////////////////////////////////////////////////////

struct SWI_SecurityInfoRequest
{
	struct SWI_BlockHead head;		// function_no = 0x601,block_type==1
	BYTE   exchange_no;         	// ��������ţ��������ֵ�˵����
	WORD   security_idx;       		// ֤ȯ��ţ���ע��
	char   security_code[7];   		// ֤ȯ����
};
//ע����֤ȯ����Ϊ�մ�ʱ����֤ȯ��Ų�ѯ, ���������й�Ʊ��
//�ô�0��ʼ��������ŷ�����ѯֱ������ʧ�ܣ��������г����й�Ʊ��
//ƽʱ����������֤ȯ������в�ѯ��������ⷢ����λ��

//Ӧ��
// ��֤ȯ��Ϣ���ؽ��
struct SWI_SecurityInfoReturn
{
	struct SWI_BlockHead head;	    // function_no==0x601,block_type==2
	long		  return_status;    // ����״̬
	char		  security_code[7]; // ֤ȯ����
	char		  security_name[18];// ֤ȯ���ƣ�MBCS/Unicode��
	SWISmallMoney prev_close_price; // ǰ����
	SWISmallMoney open_price;       // ����
	SWISmallMoney top_price;        // ��߼�
	SWISmallMoney bottom_price;     // ��ͼ�
	SWISmallMoney current_price;    // ���¼�
	long   	 	  amount;           // �ɽ�����
	SWIMoney 	  volume;           // �ɽ����
	SWISmallMoney buy_price_1;      // ���1
	long	 	  buy_amount_1;     // ����1
	SWISmallMoney buy_price_2;		// ���2
	long		  buy_amount_2;     // ����2
	SWISmallMoney buy_price_3;      // ���3
	long		  buy_amount_3;     // ����3
	SWISmallMoney sale_price_1;     // ����1
	long		  sale_amount_1;    // ����1
	SWISmallMoney sale_price_2;     // ����2
	long		  sale_amount_2;    // ����2
	SWISmallMoney sale_price_3;     // ����3
	long		  sale_amount_3;    // ����3
	char		  security_type;    // ֤ȯ��𣨱�����
	BYTE		  stop_trading_flag;// ͣ�Ʊ�־����0��ͣ�ƣ�
	BYTE		  bs_allowed;       // ������������0������
	SWISmallMoney buy_price_4;      // ���4��ʹ����������ʱ����0��
	long		  buy_amount_4;     // ����4��ʹ����������ʱ����0��
	SWISmallMoney buy_price_5;      // ���5��ʹ����������ʱ����0��
	long		  buy_amount_5;     // ����5��ʹ����������ʱ����0��
	SWISmallMoney sale_price_4;     // ����4��ʹ����������ʱ����0��
	long		  sale_amount_4;    // ����4��ʹ����������ʱ����0��
	SWISmallMoney sale_price_5;     // ����5��ʹ����������ʱ����0��
	long		  sale_amount_5;    // ����5��ʹ����������ʱ����0��
};
//ע�������Ϻ�ָ����ʹ��show128.dbf�д���ֱ��ѯ����������ָ����ʹ�������Ʊ����9000-9100��ѯ������9000��Ӧ��z_zs.dbf�е�һ����¼.

//
//����״̬
//  >0 �ɹ�
//  <=0  ʧ��


//////////////////////////////////////////////////////////////////////////
//
//17�����ܺ�0x901 ������Ϣ����SWI_FUNC_ERROR_MSG
//
/////////////////////////////////////////////////////////////////////////
//������Ϣ
struct SWI_ErrorMsgRequest
{
	struct SWI_BlockHead head;  //function_no==0x901, block_type==1
	long    error_no;           //�������
};

//Ӧ��
struct SWI_ErrorMsgReturn
{
	struct SWI_BlockHead head;	//function_no==0x901,block_type==2
	long    return_status;      // ����״̬
	char    error_msg[40];      // ������Ϣ��MBCS/Unicode��
};
//����״̬
//  >0 �ɹ�
//  <=0  ʧ��

//////////////////////////////////////////////////////////////////////
//
//18�����ܺ�0x902, �ض�λ�����  SWI_FUNC_RESULTSET_GOTO
//
//////////////////////////////////////////////////////////////////////

//������Ϣ
struct SWI_ResultsetGotoRequest
{
	struct SWI_BlockHead head;   //function_no == 0x902,block_type==1
	WORD   row_no;               //��λ����¼�ţ�0��ʼ��
	WORD   max_results;          //����¼��
};

//�������޶�����Ӧ�𣬶����ط��ϴβ�ѯ�Ľ����



//--------------------------------------------------------------------------------
// definiation on block_type
#define SWI_BT_REQUEST 1
#define SWI_BT_RETURN  2
#define SWI_BT_RESULT  3
//#define SWI_BT_CANCEL  4
//#define SWI_BT_ALERT   5
#define SWI_BT_CN_REQUEST  6
#define SWI_BT_CN_RESPONSE 7

//���ܺź궨��
#define SWI_FUNC_OPEN_ACCOUNT                   0X101
#define SWI_FUNC_ADD_ENTRUST                    0X201
#define SWI_FUNC_WITHDRAW                       0X202
#define SWI_FUNC_QUERY_MONEY                    0X301
#define SWI_FUNC_QUERY_ACCOUNTINFO		0x302
#define SWI_FUNC_QUERY_STOCK			0x401
#define SWI_FUNC_QUERY_ENTRUST			0x402
#define SWI_FUNC_QUERY_BUSINESS			0X403

#define SWI_FUNC_QUERY_HISTORY_BUSINESS         0x503
#define SWI_FUNC_QUERY_FUND_DETAIL              0x504

#define SWI_FUNC_QUERY_SECURITY_INFO            0x601
#define SWI_FUNC_ERROR_MSG			0x901

//������
//�������ⲿί�У�ʹ��ȫ��Ψһ�ĳ����룬������ĺ�����SWI_ErrorMsg�����͡�
//���ǿ����ں�̰汾����������������ĺ��塣
//���Ѷ���ĳ����뺬�����£�

#define SWIE_GENERAL                    -100  // ------ һ���Դ���ϵͳ����
#define SWIE_INVALID_ACCOUNTTYPE        -101  // ------ �޴��ʺ�����
#define SWIE_INVALID_ACCOUNT            -102  // ------ �޴��ʺ�
#define SWIE_INVALID_TRADE_METHOD       -103  // ------ ί�з�ʽ���󣨻��ֹ��
#define SWIE_INVALID_EXCHANGE           -104  // ------ �޴˽��������
#define SWIE_INVALID_BS_TYPE            -105  // ------ ��Ч�������
#define SWIE_INVALID_STOCK_CODE         -106  // ------ ��Ч֤ȯ����
#define SWIE_STOCK_STOP_TRADING         -107  // ------ �ù�Ʊͣ��
#define SWIE_INVALID_STOCK_AMOUNT       -108  // ------ ��Чί��������С��0�����Ʊ��������
#define SWIE_NO_ENOUGH_MONEY            -109  // ------ �ʽ���
#define SWIE_INVALID_PRICE              -110  // ------ ��Ч�۸�
#define SWIE_INVALID_EFFECT_DAYS    	-111  // ------ ��Ч��Ч������������
#define SWIE_INVALID_OPERATOR       	-112  // ------ �Ƿ�����Ա
#define SWIE_INVALID_DEPARTMENT         -113  // ------ �Ƿ�Ӫҵ�����
#define SWIE_STOP_TRADING               -114  // ------ ���б��У�����Чί��ʱ�䣩
#define SWIE_FROZEN_ACCOUNT             -115  // ------ �ʺ��Ѷ���
#define SWIE_METHOD_DISALLOWED          -116  // ------ ��ί�з�ʽ��ֹ�������ֹ�Ʊ
#define SWIE_DEPARTMENT_CLOSED          -120  // ------ Ӫҵ��Ŀǰ��ֹ����
#define SWIE_INVALID_TRADE_SN           -130  // ------ ��Чί�б��
#define SWIE_TRADE_WITHDRAWED           -131  // ------ ��ί���ѳ���
#define SWIE_INVALID_TRADE              -132  // ------ ��ί����Ч
#define SWIE_BARGAINED_TRADE            -133  // ------ ��ί���ѳɽ�
#define SWIE_INVALIDE_DATE              -140  // ------ ��Ч����
#define SWIE_INVALIDE_PWD               -150  // ------ ԭ��������
#define SWIE_VERSION_MISMATCH		-160  // ------ Version of Client and Server mismatch

#define SWIE_NET_ERROR			-180  // ------ ͨ�ų���
#define SWIE_TMTM_NOTALLOWED		-181  // ------ ͨ��ͨ��δ��ͨ
#define SWIE_TMTM_REMOTE_INVALID	-182  // ------ ͨ��ͨ���Է�Ӫҵ����Ŵ������δͨ
#define SWIE_TMTM_REMOTE_NET_ERROR      -183  // ------ ͨ��ͨ���Է�Ӫҵ���������
#define SWIE_REOPEN                     -184  // ------ �ظ����ʺ�
#define SWIE_DB_TIMEOUT                 -185  // ------ ���ݿ���ʳ�ʱ
#define SWIE_ACCOUNT_NOT_OPENED         -186  // ------ δУ�齻������
#define SWIE_DB_ERROR                   -187  // ------ ���ݿ����
#define SWIE_HQ_ERROR                   -190  // ------ �޷���������
#define SWIE_NO_MORE_SECURITY           -191  // ------ ��֤ȯ��Ų�����ʱ֤ȯ���̫��
#define SWIE_TIMEOUT                    -195  // ------ ��ʱ

#define SWIE_CANT_ALLOC_SPID            -501  // ------ �޷�������̺�
#define SWIE_TABLE_OP_ERROR		-502  // ------ ���������
#define SWIE_INVALID_SPID		-503  // ------ ���̺Ų�����
#define SWIE_INVALID_OPERATOR_2         -504  // ------ �Ƿ�����Ա
#define SWIE_ACCOUNT_MISMATCH           -505  // ------ �ͻ��ʺŲ�һ��

#pragma pack(pop)

#endif
