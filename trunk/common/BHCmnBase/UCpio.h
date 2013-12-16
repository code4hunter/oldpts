/*
*  完成端口I/O模型
*  By CodeHunter
*  Copyright 2004 BoHongFund
*
*/

//---------------------------------------------------------------------------
#ifndef UCpioH
#define UCpioH

#include <Winsock2.h>
//---------------------------------------------------------------------------
#define MAX_WORK_THREAD 100 //100个CPU
#define MAX_BUF_SIZE    1024
#define RECV_POSTED     0x0001
#define SEND_POSTED     0x0002
#define IO_FREE         0xFFFFFFFF
#define IO_DISCONNECTED 0xFFFFFFFE

/* ERROR CODE */
#define ERR_OTHER         -100
#define ERR_INIT_CPIO     -1
#define ERR_INIT_LISTEN   -2
#define ERR_CREATE_THREAD -3

//////////////////////////////////////////////////////////////////////////////
class completion_socket;
//////////////////////////////////////////////////////////////////////////////
struct per_overlapped
{
	WSAOVERLAPPED op;
	WSABUF     data_buf;
	//char       buffer[MAX_BUF_SIZE];
	short      operation;
};

struct work_thread
{
	DWORD thread_id;
	HANDLE thread_handle;
};

struct listen_th
{
	HANDLE thread_handle;
	SOCKET  listen_sock;
};

//////////////////////////////////////////////////////////////////////////////
/*  completion_key  */
class completion_key
{
protected:
	DWORD wsa_flag;
	DWORD recv_num;
	DWORD send_num;
	per_overlapped m_po_send,m_po_recv;
	completion_socket *m_server;
	int m_key_index;   //key 在 server_sock中的index
public:
	SOCKET work_sock;
	per_overlapped *po_send;
	per_overlapped *po_recv;
	bool    m_bFireDisConnect;
	/*
	* 0,对象未建立; 1，对象已经建立，但闲置;2正在被使用
	*/
	LONG flag;
public:
	completion_key( completion_socket *cs,int key_index);
	virtual ~completion_key();
	//int Send(char *buf,int n);
	//int Recv(int n=MAX_BUF_SIZE);

	int Send2(char *buf,int n);
	int Recv2(char *buf,int n);

	void close_socket();

	virtual void OnConnected();
	virtual void OnDisconnected();
	//前一个Send已经完成可以继续新的Send或则其他操作
	virtual void OnSend(DWORD n);
	//已经接收到数据
	virtual void OnRecv(char * buf,DWORD n);

	//检查IO操作是否失败
	bool check_result(int &ret);

	//投递一个空闲I/O    opt 为一个操作码
	BOOL PostFree(DWORD opt);
	virtual void OnFree(int opt);

	bool set_buffer(int recv,int send);
	bool get_buffer(int &recv,int &send);
	bool set_keep_alive(BOOL alive);
	bool set_nagle(BOOL enabled);
};

//////////////////////////////////////////////////////////////////////////////
/* completion_socket */
class completion_socket
{
protected:
	bool    m_active;
	char    m_svr_ip[16];
	int     m_svr_port;
	int     m_nwork_th;
	int     m_max_client;
	work_thread   m_workth[MAX_WORK_THREAD];
	HANDLE  m_completion_port;
	listen_th m_lth;
	//int     m_next_free;
protected:
	virtual void new_key(completion_key ** ck,int key_index);
	virtual void del_key(completion_key * ck);

public:
	completion_socket(char *svr_ip,int svr_port,int nwork_thread,int max_client);
	virtual ~completion_socket();

	int start();
	int stop();

	bool IsActive(void);

	bool SetSvrParam(char *svr_ip,int svr_port,int work_th,int max_client);

	virtual void on_new_client(void);
	virtual void on_del_client(void);

	char * get_local_ip() ;
	HANDLE get_completion_port(void);
private:
	void init();
	int start_winsock();
	int init_cpio();
	int init_listen();
	int fina_listen();
	int disconnect_all();
	int free_all();
	int fina_cpio();
	int end_winsock();

public:
	CRITICAL_SECTION m_cs;
	completion_key ** m_keys;
	completion_key * get_free_key(SOCKET sock,int &index);
	completion_key * get_key_by_sock(SOCKET sock);
	completion_key * get_key_by_index(int index);
  int post_key_cmd(DWORD cmd);
  virtual DWORD RunProc(void);
  virtual DWORD WorkTh(void);
};
#endif
