//---------------------------------------------------------------------------
#include <assert.h>
#include "UCpio.h"
//---------------------------------------------------------------------------
#pragma comment(lib, "ws2_32.lib")


DWORD WINAPI run( LPVOID lpParam )
{
  completion_socket *cs=(completion_socket *)lpParam;
  if(cs) return cs->RunProc();
  else return FALSE;
}

DWORD WINAPI work_th( LPVOID lpParam )
{
  completion_socket *cs=(completion_socket *)lpParam;
  if(cs) return cs->WorkTh();
  else return FALSE;
}

DWORD completion_socket::RunProc(void)
{
  #ifdef USECOM
		CoInitialize(NULL);
	#elif defined USECOMT
		CoInitializeEx(NULL,0);
	#endif

	SOCKET acc;
	completion_key *ck;

	HANDLE completion_port=this->m_completion_port;
	SOCKET listen_sock=this->m_lth.listen_sock;

	int index;

	while(1)
	{
		acc=WSAAccept(listen_sock,NULL,NULL,NULL,0);
		if(INVALID_SOCKET == acc) break;

		ck=get_free_key(acc,index);
		if(ck==NULL)
		{
			closesocket(acc);
			continue;
		}

		if(CreateIoCompletionPort((HANDLE)acc,completion_port,(ULONG_PTR)ck,0)==NULL)
		{
			break;
		}

		on_new_client();
		ck->OnConnected();
	}

#ifdef USECOM
	CoUninitialize();
#elif defined USECOMT
	CoUninitialize();
#endif
	return TRUE;
}

DWORD completion_socket::WorkTh(void)
{
	#ifdef USECOM
		CoInitialize(NULL);
	#elif defined USECOMT
		CoInitializeEx(NULL,0);
	#endif
	HANDLE completion_port=this->m_completion_port;
	DWORD byte_transed=0;
	per_overlapped * po=NULL;
	completion_key * ck=NULL;

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
						continue;
					}

					switch(po->operation)
					{
					case RECV_POSTED :
						//copy recv data from po
						ck->OnRecv(ck->po_recv->data_buf.buf,byte_transed);
						break;
					case SEND_POSTED :
						ck->OnSend(byte_transed);
						break;
					}
				}
				else ck->OnFree(byte_transed);
			}
		}
	}

#ifdef USECOM
	CoUninitialize();
#elif defined USECOMT
	CoUninitialize();
#endif
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
completion_key::completion_key( completion_socket *cs,int key_index)
{
	work_sock=INVALID_SOCKET;
	m_server=cs;
	po_send=&m_po_send;
	po_recv=&m_po_recv;
	m_key_index=key_index;
	m_bFireDisConnect=true;
}

completion_key::~completion_key()
{
	if(flag>1)
	{
		close_socket();
	}
}

bool completion_key::check_result(int &ret)
{
	ret= WSAGetLastError();
	if((SOCKET_ERROR==ret) && (ERROR_IO_PENDING != ret))
	{
		return false;
	}
	return true;
}

int completion_key::Send2(char *buf,int n)
{
	wsa_flag=0;
	ZeroMemory(&(po_send->op),sizeof(OVERLAPPED));

	po_send->operation=SEND_POSTED;
	po_send->data_buf.len=n;
	po_send->data_buf.buf=buf;

	return WSASend(work_sock,&po_send->data_buf,1,&send_num,wsa_flag,&po_send->op,NULL);
}

int completion_key::Recv2(char *buf,int n)
{
	wsa_flag=0;
	ZeroMemory(&(po_recv->op),sizeof(OVERLAPPED));

	po_recv->operation=RECV_POSTED;
	po_recv->data_buf.len=n;
	po_recv->data_buf.buf=buf;

	return WSARecv(work_sock,&po_recv->data_buf,1,&recv_num,&wsa_flag,&po_recv->op,NULL);
}

void completion_key::close_socket()
{
	if(flag==2)
	{
		InterlockedExchange(&flag,3);//closing
		shutdown(work_sock,1);
		closesocket(work_sock);
		work_sock=INVALID_SOCKET;
		if(flag>1)
		{
			InterlockedExchange(&flag,1);
			m_server->on_del_client();
			OnDisconnected();
		}
	}
}

void completion_key::OnConnected()
{
	//this->Recv();
	//printf("%d connected!\r\n",this->work_sock);
}

void completion_key::OnDisconnected()
{
	//printf("%d disconnected!\r\n",this->work_sock);
}

//前一个Send已经完成可以继续新的Send或则其他操作
void completion_key::OnSend(DWORD n)
{
	//printf("SEND:%s ,SEND COUNT:%d\r\n",po->buffer,n);
	//this->Recv();
}

//已经接收到数据
void completion_key::OnRecv(char * buf,DWORD n)
{
	//printf("RECV:%s ,RECV COUNT:%d\r\n",po->buffer,n);
	//this->Send(NULL,n);
}

BOOL completion_key::PostFree(DWORD opt)
{
	return PostQueuedCompletionStatus(m_server->get_completion_port(),opt,(ULONG_PTR)this,NULL);
}

void completion_key::OnFree(int opt)
{
}

bool completion_key::set_buffer(int recv,int send)
{
	return (setsockopt(this->work_sock,SOL_SOCKET,SO_RCVBUF,(const char*)&recv,sizeof(int))==0) &&
		(setsockopt(this->work_sock,SOL_SOCKET,SO_SNDBUF,(const char*)&send,sizeof(int))==0) ;
}

bool completion_key::get_buffer(int &recv,int &send)
{
	int n=sizeof(int);
	return (getsockopt(this->work_sock,SOL_SOCKET,SO_RCVBUF,(char*)&recv,&n)==0) &&
		(getsockopt(this->work_sock,SOL_SOCKET,SO_SNDBUF,(char*)&send,&n)==0) ;
}

bool completion_key::set_keep_alive(BOOL alive)
{
	return setsockopt(this->work_sock,SOL_SOCKET,SO_KEEPALIVE ,(const char*)&alive,sizeof(BOOL))==0;
}

bool completion_key::set_nagle(BOOL enabled)
{
	BOOL v= !enabled;
	return setsockopt(this->work_sock,IPPROTO_TCP,TCP_NODELAY ,(const char*)&v,sizeof(BOOL))==0;
}
///////////////////////////////////////////////////////////////////////////////
completion_key * completion_socket::get_free_key(SOCKET sock,int &index)
{
	completion_key * ret=NULL;
	index=-1;

	EnterCriticalSection(&m_cs);

	for(int i=0;i<m_max_client;i++)
	{
		if(m_keys[i]!=NULL)
		{
			if(m_keys[i]->flag==1)
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
			ret = m_keys[i];
			goto end;
		}
	}

end:
	if(ret)
	{
		ret->work_sock=sock;
		InterlockedExchange(&(ret->flag),2);
	}
	LeaveCriticalSection(&m_cs);
	return ret;
}

HANDLE completion_socket::get_completion_port(void)
{
	return m_completion_port;
}

completion_socket::completion_socket(char *svr_ip,
									 int svr_port,int nwork_thread,int max_client)
{
	m_max_client=max_client;
	strncpy(m_svr_ip,svr_ip,16);
	m_svr_port=svr_port;
	if(nwork_thread<= MAX_WORK_THREAD)
		m_nwork_th=nwork_thread;
	else
		m_nwork_th=MAX_WORK_THREAD;	

	m_keys=(completion_key**)malloc(m_max_client*sizeof(completion_key*));

	InitializeCriticalSection(&m_cs);
	init();
	start_winsock();

	m_active=false;
	//m_next_free=0;
}

void completion_socket::init()
{
	ZeroMemory(m_workth,sizeof(work_thread)*MAX_WORK_THREAD);
	m_completion_port=0;
	ZeroMemory(&m_lth,sizeof(listen_th));
	ZeroMemory(m_keys,sizeof(completion_key*)*m_max_client);
}

completion_socket::~completion_socket()
{
	stop();
	free_all();
	end_winsock();
	DeleteCriticalSection(&m_cs);
	free(m_keys);
}

int completion_socket::start_winsock()
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

int completion_socket::end_winsock()
{
	WSACleanup();
	return TRUE;
}

int completion_socket::init_cpio()
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
		m_workth[i].thread_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)work_th,this, 0,
			&(m_workth[i].thread_id));

		if ( m_workth[i].thread_handle == NULL)
		{
			return -2;
		}
	}

	return TRUE;
}

int completion_socket::init_listen()
{
	m_lth.listen_sock=WSASocket(AF_INET,SOCK_STREAM,0,NULL,0,
		WSA_FLAG_OVERLAPPED);

	if(m_lth.listen_sock==INVALID_SOCKET)
	{
		int errcode = WSAGetLastError();
		return FALSE;
	}

	const int on =1;
	if(setsockopt(m_lth.listen_sock,SOL_SOCKET,SO_REUSEADDR,(char *)&on,sizeof(on)))
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

int completion_socket::fina_listen()
{
	return closesocket(m_lth.listen_sock);
}

int completion_socket::fina_cpio()
{
	for(int i=0;i<MAX_WORK_THREAD;i++)
	{
		if(0!=m_workth[i].thread_handle)
		{
			PostQueuedCompletionStatus(m_completion_port,0,NULL,NULL);
		}
	}
	//wait for thread end
	//close thread handle
	//DWORD exitcode;
	for(int i=0;i<MAX_WORK_THREAD;i++)
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

int completion_socket::start()
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

	m_lth.thread_handle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)run,this,0,&id);

	if ( m_lth.thread_handle == NULL)
	{
		return ERR_CREATE_THREAD;
	}

	m_active=true;

	return TRUE;
}

int completion_socket::stop()
{
	if(NULL==m_lth.thread_handle) return FALSE;

	fina_listen();
	//wait for run end;
	WaitForSingleObject(m_lth.thread_handle,INFINITE);

	CloseHandle(m_lth.thread_handle);

	ZeroMemory(&m_lth,sizeof(listen_th));

	fina_cpio();

	disconnect_all();
	free_all();
	m_active=false;
	return TRUE;
}

int completion_socket::disconnect_all()
{
	EnterCriticalSection(&m_cs);
	for(int i=0;i<m_max_client;i++)
	{
		if(m_keys[i]!=NULL)
		{
			if(m_keys[i]->flag>1)
			{
				m_keys[i]->close_socket();
			}
			//del_key(m_keys[i]);
			//m_keys[i]=NULL;
		}
	}
	LeaveCriticalSection(&m_cs);
	return TRUE;
}

int completion_socket::free_all()
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

int completion_socket::post_key_cmd(DWORD cmd)
{
  EnterCriticalSection(&m_cs);
	for(int i=0;i<m_max_client;i++)
	{
		if(m_keys[i]!=NULL)
		{
			if(m_keys[i]->flag>1)
			{
				m_keys[i]->PostFree(cmd);
			}
		}
	}
	LeaveCriticalSection(&m_cs);
	return TRUE;
}

bool completion_socket::IsActive(void)
{
	return m_active;
}

void completion_socket::new_key(completion_key ** ck,int key_index)
{
	*ck=new completion_key(this,key_index);
}

void completion_socket::del_key(completion_key * ck)
{
	delete ck;
}

void completion_socket::on_new_client(void)
{
}

void completion_socket::on_del_client(void)
{
}

bool completion_socket::SetSvrParam(char *svr_ip,int svr_port,int work_th,
									int max_client)
{
	if( m_active==false)
	{
		strncpy(m_svr_ip,svr_ip,16);
		m_svr_port=svr_port;
		m_nwork_th=work_th;
		if(m_nwork_th>MAX_WORK_THREAD) m_nwork_th=MAX_WORK_THREAD;
		free(m_keys);
		m_max_client=max_client;
		m_keys=(completion_key**)malloc(max_client*sizeof(completion_key*));
	}
	else return false;
	return true;
}

char * completion_socket::get_local_ip()
{
	sockaddr sa;
	int size=sizeof( sockaddr );
	if(getsockname(m_lth.listen_sock,&sa,&size)==0)
	{
		return inet_ntoa(((sockaddr_in *)(&sa))->sin_addr);
	}
	else return "";
}

completion_key * completion_socket::get_key_by_sock(SOCKET sock)
{
	completion_key * ret=NULL;

	EnterCriticalSection(&m_cs);

	for(int i=0;i<m_max_client;i++)
	{
		if(m_keys[i]!=NULL && m_keys[i]->work_sock==sock && m_keys[i]->flag==2)
		{
			ret= m_keys[i];
			goto end;
		}
	}

end:
	LeaveCriticalSection(&m_cs);
	return ret;
}

completion_key * completion_socket::get_key_by_index(int index)
{
	completion_key * ret=NULL;
	if(index>=m_max_client) return NULL;

	EnterCriticalSection(&m_cs);

	if(m_keys[index]!=NULL && m_keys[index]->flag==2)
	{
		ret= m_keys[index];
	}

	LeaveCriticalSection(&m_cs);
	return ret;
}
