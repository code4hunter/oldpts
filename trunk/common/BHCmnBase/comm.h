#ifndef comm_H
#define comm_H


#pragma pack(1)
//����ͷ
struct p_head
{
	long command;   //����
	long value;     //����ֵ
	long next_byte; //�������ֽ���
};

//command 

//У���û�������
#define CHECKPASS     0xF00D0001
//���ģ���������
#define SUBSCRIBER    0xF00D0002
//���ù�����
#define SETFILTER     0xF00D0003
//�������
#define UNSUBSCRIBER  0xF00D0004
//������Ĵ�����Ϣ
#define GETLASTERR    0xF00D0007
//��õ�ǰ���е������б�
#define GETCURTOPICS  0xF00D0005
//������з�����ע��������б�
#define GETREGTOPICS  0xF00D0006
//��ó�ʼ������
#define GETINITDATA   0xF00D0008
//�¼�����
#define PUBEVENT      0xF00D000E

//�������ݵĶ���
struct req_check_pass
{
	char name[50];
	char password[50];
};

// value  ����ֵ����

#define R_ALLOK           0x00000000
#define R_OTHER_ERR       -1
#define R_INVALID_USER    -100
#define R_NOTOPIC         -101
#define R_REQUESTERROR    -104   //����ĸ�ʽ���� 
#define R_INVALID_FILTER  -102
#define R_NOFILTER        -103
#define R_INVALID_CMD     -105
#define R_INVALID_TOPIC   -106   //û������

//���ص��ַ����б�ͳһʹ�����¸�ʽ
//�ַ���'\0'�ַ���'\0'�ַ���'\0'�ַ���'\0''\0'
//

// ����ʱ����������
struct req_subscriber
{
	long id;              // ����������е�ID
	GUID gid;             // ����������е�AuthID
	long topicid;         // ������е�����ID
};


/*
�¼�����ͨ��ͷ(event_head)				
id	int	4	�¼���id	����0��ʼ���Զ�������ֵ
type	char	1	�¼�����	���ڲ�ͬ���¼�,��ֵ���岻����ͬ����Ҫ���ڽ�һ�����ָ��¼���
count	int	4	��������	�����¼��ļ�¼����
date	int	4	��������	��ʾ���¼�����������
time	int	4	����ʱ��	�¼�������ʱ�䡣���缴ʱ���鷢����ʱ���ɽ��ر����ص�ʱ���
reserved	char	8	�����ֶ�	
fieldcnt	int	4	�������ݰ��ֶθ���	�ֶ��������event_desc
eventsize	int	4	�������ݰ��ֶδ�С	�������ݰ��ṹռ�õ��ֽ���
*/
struct event_head
{
	int id;
	char type;
	int count;
	int date;
	int time;
	char reserved[8];
	int fieldcnt;
	int eventsize;
};

/*
�������ݰ��ֶ�����(event_desc)				
�ֶ���	����	����	����	��ע
name	char	8	�ֶ���	
type	char	1	�ֶ�����	��������ֵ�field_type
size	int	4	�ֶδ�С	���ֶ�ռ�õ��ֽ���

�ֶ����ͣ�field_type��		
ʵ������		         type
int		            n
char		        c
float		        f
double		        d
short		        s
__int64		        t
unsgined short		o
unsigned int		u
unsigned __int64    v
BYTE		        r  ����Ǵ�������������ֶ�ֻ��һ������¼ֻ��һ��������һ��BUFFER,���BUFFER����ADO.Stream���ɵ�
*/
struct event_desc
{
	char name[8];
	char type;
	int  size;
};

#pragma pack()

#endif