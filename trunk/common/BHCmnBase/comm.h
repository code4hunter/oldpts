#ifndef comm_H
#define comm_H


#pragma pack(1)
//数据头
struct p_head
{
	long command;   //命令
	long value;     //返回值
	long next_byte; //后续包字节数
};

//command 

//校验用户名密码
#define CHECKPASS     0xF00D0001
//订阅，设置主题
#define SUBSCRIBER    0xF00D0002
//设置过滤器
#define SETFILTER     0xF00D0003
//解除订阅
#define UNSUBSCRIBER  0xF00D0004
//获得最后的错误信息
#define GETLASTERR    0xF00D0007
//获得当前运行的主题列表
#define GETCURTOPICS  0xF00D0005
//获得所有服务器注册的主题列表
#define GETREGTOPICS  0xF00D0006
//获得初始化数据
#define GETINITDATA   0xF00D0008
//事件发布
#define PUBEVENT      0xF00D000E

//后续数据的定义
struct req_check_pass
{
	char name[50];
	char password[50];
};

// value  返回值定义

#define R_ALLOK           0x00000000
#define R_OTHER_ERR       -1
#define R_INVALID_USER    -100
#define R_NOTOPIC         -101
#define R_REQUESTERROR    -104   //请求的格式不对 
#define R_INVALID_FILTER  -102
#define R_NOFILTER        -103
#define R_INVALID_CMD     -105
#define R_INVALID_TOPIC   -106   //没有主题

//返回的字符串列表统一使用如下格式
//字符串'\0'字符串'\0'字符串'\0'字符串'\0''\0'
//

// 订阅时的请求数据
struct req_subscriber
{
	long id;              // 订阅请求表中的ID
	GUID gid;             // 订阅请求表中的AuthID
	long topicid;         // 主题表中的主题ID
};


/*
事件发布通用头(event_head)				
id	int	4	事件的id	就是0开始的自动增长数值
type	char	1	事件类型	对于不同的事件,该值含义不尽相同，主要用于进一步区分该事件。
count	int	4	数据条数	发布事件的纪录条数
date	int	4	发布日期	表示该事件发生的日期
time	int	4	发布时间	事件发布的时间。比如即时行情发布的时间或成交回报返回的时间等
reserved	char	8	保留字段	
fieldcnt	int	4	后续数据包字段个数	字段描述详见event_desc
eventsize	int	4	后续数据包字段大小	后续数据包结构占用的字节数
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
后续数据包字段描述(event_desc)				
字段名	类型	长度	含义	备注
name	char	8	字段名	
type	char	1	字段类型	详见数据字典field_type
size	int	4	字段大小	该字段占用的字节数

字段类型（field_type）		
实际类型		         type
int		            n
char		        c
float		        f
double		        d
short		        s
__int64		        t
unsgined short		o
unsigned int		u
unsigned __int64    v
BYTE		        r  如果是此种类型则表明字段只有一个，记录只有一个，就是一个BUFFER,这个BUFFER是由ADO.Stream生成的
*/
struct event_desc
{
	char name[8];
	char type;
	int  size;
};

#pragma pack()

#endif