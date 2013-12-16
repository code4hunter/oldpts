/*
*  完成端口I/O模型
*  By CodeHunter
*  Copyright 2004 BoHongFund
*  使用标准C++模板
*/

//---------------------------------------------------------------------------
#ifndef cpio_t_s_H
#define cpio_t_s_H

#define _WIN32_DCOM

#include <assert.h>
#include <Winsock2.h>
#include <objbase.h>
#include <tchar.h>
//---------------------------------------------------------------------------
#define MAX_WORK_THREAD 16 //16个CPU
#define MAX_BUF_SIZE    1024
#define RECV_POSTED     0x0001
#define SEND_POSTED     0x0002
#define FREE            0x0000
#define IO_FREE         0xFFFFFFFF
#define IO_DISCONNECTED 0xFFFFFFFE

#define BUFNUM          100 

/* ERROR CODE */
#define ERR_OTHER         -100
#define ERR_INIT_CPIO     -1
#define ERR_INIT_LISTEN   -2
#define ERR_CREATE_THREAD -3
#define ERR_PO_FULL       -4   //发送队列已满
#define ERR_DISCONNECTED  -5
#define ERR_OVERBUFFER    -6

#define WM_SOCKET       WM_USER + 1

//#define MULTTH 1
//////////////////////////////////////////////////////////////////////////////
struct per_overlapped
{
	WSAOVERLAPPED	op;
	WSABUF          data_buf[BUFNUM];
	int             nbuf;
	short			operation;
	void            * sender;
	LONG            refcount;

	per_overlapped(void)
	{
		ZeroMemory(&op,sizeof(op));
		ZeroMemory(data_buf,sizeof(WSABUF)*BUFNUM);
		nbuf=0;
		operation = FREE;
		sender =NULL;
		refcount = 0;
	}
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

template < class T >class completion_key;
template < class T >class completion_socket ;

DWORD WINAPI run( LPVOID lpParam );
DWORD WINAPI work_th( LPVOID lpParam );
DWORD WINAPI select_th ( LPVOID lpParam );
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//////////////////////////////////////////////////////////////////////////////
/* completion_socket */
template < class T >
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
	HANDLE  m_selectth;

	LONG    m_client_count; //客户数
public:

	CRITICAL_SECTION m_cs;
	T ** m_keys;

	HANDLE get_completion_port(void)
	{
		return m_completion_port;
	}

	virtual DWORD run_proc(void)
	{
#ifdef USECOM
#ifdef MULTTH
		CoInitializeEx(NULL,COINIT_MULTITHREADED);
#else
		CoInitialize(NULL);
#endif
#endif

		SOCKET acc;
		T *ck;

		HANDLE completion_port=this->m_completion_port;
		SOCKET listen_sock=this->m_lth.listen_sock;

		int index;

		while(1)
		{
			acc=WSAAccept(listen_sock,NULL,NULL,NULL,0);
			if(INVALID_SOCKET == acc) break;

			if(::WSAAsyncSelect(acc,m_hWnd,WM_SOCKET,FD_CLOSE) )
			{
				closesocket(acc);
				continue;
			}

			ck=get_free_key(acc,index);
			if(ck==NULL)
			{
				closesocket(acc);
				continue;
			}

			if(CreateIoCompletionPort((HANDLE)acc,completion_port,(ULONG_PTR)ck,0)==NULL)
			{
				ck->close_socket();
				continue;
			}

			on_new_client();
			ck->OnConnected();
		}

#ifdef USECOM
		CoUninitialize();
#endif
		return TRUE;
	}

	//work thread
	virtual DWORD workth(void)
	{
#ifdef USECOM
#ifdef MULTTH
		CoInitializeEx(NULL,COINIT_MULTITHREADED);
#else
		CoInitialize(NULL);
#endif
#endif
		HANDLE completion_port=this->m_completion_port;
		DWORD byte_transed=0;
		per_overlapped * po=NULL;
		T * ck=NULL;

		while(1)
		{
			if(GetQueuedCompletionStatus(completion_port,&byte_transed,(LPDWORD)&ck,
				(LPOVERLAPPED*)(&po),INFINITE)==TRUE)
			{
				if(ck==NULL)
				{
					if(byte_transed==0 && po==NULL) break;
				}
				else
				{
					if(po!=NULL)
					{
						if(byte_transed==0 && (po->operation==RECV_POSTED ||
							po->operation==SEND_POSTED))
						{
							if(ck->m_bFireDisConnect)
							{
								ck->close_socket();
							}
						}
						else
						{
							if(ck->GetFlag()!=2) continue;

							switch(po->operation)
							{
							case RECV_POSTED :
			
								ck->OnRecv(po->data_buf[0].buf,byte_transed,po);
								//ck->OnOperated(po->sender);
								break;
							case SEND_POSTED :

								ck->OnSend(byte_transed,po);
								//ck->OnOperated(po->sender);
							
								break;
							}
						}
					}
					else 
						ck->OnFree(byte_transed);
				}
			}
		}

#ifdef USECOM
		CoUninitialize();
#endif
		return 0;
	}

	HWND m_hWnd;

	virtual DWORD selectth(void)
	{
#ifdef USECOM
#ifdef MULTTH
		CoInitializeEx(NULL,COINIT_MULTITHREADED);
#else
		CoInitialize(NULL);
#endif
#endif
		TCHAR szWindowClass[20];
		MSG msg;
		WNDCLASSEX wcex;

		lstrcpy(szWindowClass,_T("UCPIO"));
		wcex.cbSize = sizeof(WNDCLASSEX); 

		wcex.style			= 0;
		wcex.lpfnWndProc	= (WNDPROC)WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= 0;
		wcex.hIcon			= 0;
		wcex.hCursor		= 0;
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= 0;
		wcex.lpszClassName	= szWindowClass;
		wcex.hIconSm		= 0;

		RegisterClassEx(&wcex);

		m_hWnd = CreateWindow(szWindowClass, _T("") , 0, 0, 0, 0, 0, NULL, NULL, 0, NULL);

		if (!m_hWnd)
		{
			return FALSE;
		}

		while (GetMessage(&msg, NULL, 0, 0)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

#ifdef USECOM
		CoUninitialize();
#endif
		return 0;
	}


	T * get_free_key(SOCKET sock,int &index)
	{
		T * ret=NULL;
		index=-1;

		EnterCriticalSection(&m_cs);

		for(int i=0;i<m_max_client;i++)
		{
			if(m_keys[i]!=NULL)
			{
				if(m_keys[i]->CompareExchangeFlag(2,1)==1)
				{
					ret= m_keys[i];
					index=i;
					goto end;
				}
			}
			else
			{
				index=i;
				new_key(&m_keys[i],i);
				m_keys[i]->AddRef();
				ret = m_keys[i];
				goto end;
			}
		}

end:
		if(ret)
		{
			ret->work_sock=sock;
		}

		LeaveCriticalSection(&m_cs);
		return ret;
	}

	completion_socket(char *svr_ip,
		int svr_port,int nwork_thread,int max_client)
	{
		m_max_client=max_client;
		lstrcpynA(m_svr_ip,svr_ip,16);
		m_svr_port=svr_port;
		if(nwork_thread<= MAX_WORK_THREAD)
			m_nwork_th=nwork_thread;
		else
			m_nwork_th=MAX_WORK_THREAD;

		m_keys=(T**)malloc(m_max_client*sizeof(T*));

		m_hWnd = NULL;

		InitializeCriticalSection(&m_cs);
		init();
		start_winsock();

		m_active=false;
	}

	void init()
	{
		ZeroMemory(m_workth,sizeof(work_thread)*MAX_WORK_THREAD);
		m_completion_port=0;
		ZeroMemory(&m_lth,sizeof(listen_th));
		ZeroMemory(m_keys,sizeof(T*)*m_max_client);
		m_selectth=NULL;

		this->m_client_count = 0;
		this->m_hWnd = NULL;
	}

	~completion_socket()
	{
		stop();
		free_all();
		end_winsock();
		DeleteCriticalSection(&m_cs);
		free(m_keys);
	}

	int start_winsock()
	{
		WORD wVersionRequested;
		WSADATA wsaData;

		wVersionRequested = MAKEWORD( 2, 2);

		if ( WSAStartup( wVersionRequested, &wsaData ) != 0 )
		{
			return FALSE;
		}

		return TRUE;
	}

	int end_winsock()
	{
		WSACleanup();
		return TRUE;
	}

	int init_cpio()
	{
		//Detemine how many processors on the system
		SYSTEM_INFO si;
		GetSystemInfo(&si);

		if((unsigned long)m_nwork_th ==0)
			m_nwork_th = si.dwNumberOfProcessors;

		//create an i/o completion port
		m_completion_port=CreateIoCompletionPort(INVALID_HANDLE_VALUE,
			NULL,0,m_nwork_th);

		if(m_completion_port==NULL) return -1;

		//create work thread
		for(int i=0;i<m_nwork_th;i++)
		{
			m_workth[i].thread_handle = CreateThread( NULL,
				0,
				(LPTHREAD_START_ROUTINE)work_th,
				this,
				0,
				&(m_workth[i].thread_id));

			if ( m_workth[i].thread_handle == NULL)
			{
				return -2;
			}
		}

		return TRUE;
	}

	int init_listen()
	{
		m_lth.listen_sock=WSASocket(AF_INET,SOCK_STREAM,0,NULL,0,
			WSA_FLAG_OVERLAPPED);

		if(m_lth.listen_sock==INVALID_SOCKET)
		{
			return FALSE;
		}

		const int on =1;
		if(setsockopt( m_lth.listen_sock,
			SOL_SOCKET,
			SO_REUSEADDR,
			(char *)&on,
			sizeof(on)))
			return FALSE;

		sockaddr_in peer;
		peer.sin_family=AF_INET;
		if(strlen(m_svr_ip)==0)
			peer.sin_addr.s_addr=htonl(INADDR_ANY);
		else
			peer.sin_addr.s_addr=inet_addr(m_svr_ip);

		peer.sin_port=htons(m_svr_port);

		if(bind(m_lth.listen_sock,(PSOCKADDR) &peer,sizeof(peer))==SOCKET_ERROR)
		{
			return FALSE;
		}

		if(listen(m_lth.listen_sock,SOMAXCONN)==SOCKET_ERROR)
		{
			return FALSE;
		}

		return TRUE;
	}

	int fina_listen()
	{
		return closesocket(m_lth.listen_sock);
	}

	int fina_cpio()
	{
		int i = 0;

		for( i=0;i<MAX_WORK_THREAD;i++)
		{
			if(0!=m_workth[i].thread_handle)
			{
				PostQueuedCompletionStatus(m_completion_port,0,NULL,NULL);
			}
		}
		//wait for thread end
		//close thread handle

		for( i=0; i< MAX_WORK_THREAD; i++ )
		{
			if(0!=m_workth[i].thread_handle)
			{
				WaitForSingleObject(m_workth[i].thread_handle,INFINITE);
				CloseHandle(m_workth[i].thread_handle);
				m_workth[i].thread_handle=0;
			}
		}
		//close iocp handle
		CloseHandle(m_completion_port);

		return TRUE;
	}

	/////////////////////////////////////////////////////////////////////
public:

	int start()
	{
		if(NULL!=m_lth.thread_handle) return ERR_OTHER;

		init();

		if(init_cpio()!=TRUE)
		{
			return ERR_INIT_CPIO;
		}

		if(init_listen()!=TRUE)
		{
			return ERR_INIT_LISTEN;
		}

		DWORD id;

		m_lth.thread_handle = CreateThread(  NULL,
			0,
			(LPTHREAD_START_ROUTINE)run,
			this,
			0,
			&id);

		if ( m_lth.thread_handle == NULL)
		{
			return ERR_CREATE_THREAD;
		}

		m_selectth = CreateThread(  NULL,
			0,
			(LPTHREAD_START_ROUTINE)select_th,
			this,
			0,
			&id);

		if ( m_selectth == NULL)
		{
			return ERR_CREATE_THREAD;
		}

		m_active=true;

		return TRUE;
	}

	int stop()
	{
		if(NULL==m_lth.thread_handle) return FALSE;

		fina_listen();
		//wait for run end;
		WaitForSingleObject(m_lth.thread_handle,INFINITE);

		CloseHandle(m_lth.thread_handle);

		ZeroMemory(&m_lth,sizeof(listen_th));

		fina_cpio();

		disconnect_all();

		::PostMessage(this->m_hWnd,WM_QUIT,0,0);
		if(NULL != m_selectth)
		{
			WaitForSingleObject(m_selectth,INFINITE);
			CloseHandle(m_selectth);
			m_selectth=NULL;
		}

		m_hWnd = NULL;

		m_active=false;
		return TRUE;
	}

	int disconnect_all()
	{
		EnterCriticalSection(&m_cs);
		for(int i=0;i<m_max_client;i++)
		{
			if(m_keys[i]!=NULL)
			{
				m_keys[i]->close_socket();
			}
		}
		LeaveCriticalSection(&m_cs);
		return TRUE;
	}

	int free_all()
	{
		EnterCriticalSection(&m_cs);
		for(int i=0;i<m_max_client;i++)
		{
			if(m_keys[i]!=NULL)
			{
				del_key(m_keys[i]);
				m_keys[i]=NULL;
			}
		}
		LeaveCriticalSection(&m_cs);
		return TRUE;
	}

	bool is_active(void)
	{
		return m_active;
	}

	bool set_svr_param(char *svr_ip,int svr_port,int work_th,
		int max_client)
	{
		if( m_active==false)
		{
			strncpy_s(m_svr_ip,16,svr_ip,15);
			m_svr_port=svr_port;
			m_nwork_th=work_th;
			if(m_nwork_th>MAX_WORK_THREAD) m_nwork_th=MAX_WORK_THREAD;
			free(m_keys);
			m_max_client=max_client;
			m_keys=(T**)malloc(max_client*sizeof(T*));
		}
		else return false;
		return true;
	}

	char * get_local_ip()
	{
		sockaddr sa;
		int size=sizeof( sockaddr );
		if(getsockname(m_lth.listen_sock,&sa,&size)==0)
		{
			return inet_ntoa(((sockaddr_in *)(&sa))->sin_addr);
		}
		else return "";
	}

	T * get_key_by_sock(SOCKET sock)
	{
		T * ret=NULL;

		EnterCriticalSection(&m_cs);

		for(int i=0;i<m_max_client;i++)
		{
			if(m_keys[i]!=NULL && m_keys[i]->work_sock==sock && m_keys[i]->GetFlag()==2)
			{
				ret= m_keys[i];
				goto end;
			}
		}

end:
		LeaveCriticalSection(&m_cs);
		return ret;
	}

	T * get_key_by_index(int index)
	{
		T * ret=NULL;
		if(index>=m_max_client) return NULL;

		EnterCriticalSection(&m_cs);

		if(m_keys[index]!=NULL && m_keys[index]->GetFlag()==2)
		{
			ret= m_keys[index];
		}

		LeaveCriticalSection(&m_cs);
		return ret;
	}

	void new_key(T ** ck,int key_index)
	{
		*ck=new T(this,key_index);
	}

	void del_key(T * ck)
	{
		delete ck;
	}

	virtual void on_new_client(void)
	{
		InterlockedIncrement(&m_client_count);
	}

	virtual void on_del_client(void)
	{
		InterlockedDecrement(&m_client_count);
	}

	//return client count
	LONG get_client_count(void)
	{
		return m_client_count;
	}
};

//////////////////////////////////////////////////////////////////////////////
/*  completion_key  */
template < class T >
class completion_key
{

protected:

	DWORD wsa_flag;
	DWORD recv_num;
	DWORD send_num;
	per_overlapped m_po_send,m_po_recv;
	T *m_server;
	int m_key_index;   //key 在 server_sock中的index
	LONG flag;

public:

	SOCKET work_sock;
	bool    m_bFireDisConnect;  //是否激发完成事件里面的断开事件
	
	LONG AddRef(void)
	{
		return ::InterlockedIncrement(&flag);
	}

	LONG Release(void)
	{
		return ::InterlockedDecrement(&flag);
	}

	LONG CompareExchangeFlag(LONG  Exchange,LONG  Comparand)
	{
		return ::InterlockedCompareExchange(&flag,Exchange,Comparand);
	}

	LONG GetFlag(void)
	{
		return flag;
	}

public:

	completion_key( T *cs,int key_index)
	{
		work_sock=INVALID_SOCKET;
		m_server=cs;
		m_key_index=key_index;
		m_bFireDisConnect=true;

		flag = 1;
	}

	virtual ~completion_key()
	{
		close_socket();
	}

	bool check_result(int &ret)
	{
		ret= WSAGetLastError();
		if((SOCKET_ERROR==ret) && (ERROR_IO_PENDING != ret))
		{
			return false;
		}
		return true;
	}

	int Send( per_overlapped * po)
	{
		//assert(flag == 2);
		if(flag != 2) return ERR_DISCONNECTED ;
		wsa_flag=0;
		po->operation =SEND_POSTED;

		return WSASend( work_sock,
			po->data_buf,
			po->nbuf,
			&send_num,
			wsa_flag,
			&po->op,
			NULL);
	}

	int Send( WSABUF * buf,int n)
	{
		assert( n<= BUFNUM);

		memcpy(m_po_send.data_buf,buf,sizeof(WSABUF)*n);
		m_po_send.nbuf= n;

		ZeroMemory(&(m_po_send.op),sizeof(OVERLAPPED));
		
		return Send(&m_po_send);	
	}

	int Recv(char *buf,int n,void * sender)
	{
		//assert(flag == 2);
		if(flag != 2) return ERR_DISCONNECTED ;
		wsa_flag=0;
		per_overlapped * po_ptr = &m_po_recv;
		if(!po_ptr) return ERR_PO_FULL;

		ZeroMemory(&(po_ptr->op),sizeof(OVERLAPPED));
		po_ptr->operation=RECV_POSTED;
		po_ptr->data_buf[0].len=n;
		po_ptr->data_buf[0].buf=buf;
		po_ptr->sender= sender;

		return WSARecv( work_sock,
			po_ptr->data_buf,
			1,
			&recv_num,
			&wsa_flag,
			&po_ptr->op,
			NULL);
	}

	void close_socket()
	{
		LONG ret = Release();
		if(ret == 1)
		{
			shutdown(work_sock,1);
			closesocket(work_sock);
			work_sock=INVALID_SOCKET;
			m_server->on_del_client();
			OnDisconnected();
		}
	}

	bool PostFree(DWORD opt)
	{
		return (PostQueuedCompletionStatus( m_server->get_completion_port(),
			opt,
			(ULONG_PTR)this,
			NULL) != 0);
	}

	bool set_buffer(int recv,int send)
	{
		return (setsockopt( this->work_sock,
			SOL_SOCKET,
			SO_RCVBUF,
			(const char*)&recv,
			sizeof(int))==0) &&
			(setsockopt(this->work_sock,
			SOL_SOCKET,
			SO_SNDBUF,
			(const char*)&send,
			sizeof(int))==0) ;
	}

	bool get_buffer(int &recv,int &send)
	{
		int n=sizeof(int);
		return (getsockopt( this->work_sock,
			SOL_SOCKET,
			SO_RCVBUF,
			(char*)&recv,
			&n)==0) &&
			(getsockopt( this->work_sock,
			SOL_SOCKET,
			SO_SNDBUF,
			(char*)&send,
			&n)==0) ;
	}

	bool set_keep_alive(BOOL alive)
	{
		return setsockopt( this->work_sock,SOL_SOCKET,
			SO_KEEPALIVE ,
			(const char*)&alive,sizeof(BOOL)
			)==0;
	}

	//////////////////////////////////////////////////////////////////////////////
	//实现如下函数
	virtual void OnConnected()
	{
		//this->Recv2();
	}

	virtual void OnDisconnected()
	{
	}

	//前一个Send已经完成可以继续新的Send或则其他操作
	virtual void OnSend(DWORD n,void * sender)
	{
		//this->Recv2();
	}

	//已经接收到数据
	virtual void OnRecv(char * buf,DWORD n,void *sender)
	{
		//this->Send2(NULL,n);
	}

	virtual void OnFree(DWORD opt)
	{
	}

	virtual void OnOperated(void * sender)
	{
	}

};

#endif
