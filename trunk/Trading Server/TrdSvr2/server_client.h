#ifndef server_clientH
#define server_clientH

#include <vcl.h>
#include <SyncObjs.hpp>
#include "uSafeString.h"

#include "ucpio.h"
#include "UTrdItfAPI.h"
#include "UtrdStruct_rm.h"
#include "UPlugInWrapper.h"

#define MY_DISCONNECTED  (WM_APP + 400)
#define KEEP_ALIVE 0xFFFFFFFD

#define MAX_RECV_BUFF_SIZE 1024
#define MAX_SEND_BUFF_SIZE 1024

extern long g_req_num; //requset num
extern TSafeStrings *g_order_list;

class server_client :public completion_key
{
private:
	TTrdItfAPI *m_trd;
	String peer_ip;
	plugin_wrapper pw;
	//---------------------------------------------------------------------
	TRequest    request;
	TAnswer     *answer;
	int         ansCount;
	TAnswer     ans;
	//----------------------------------------------------------------------
	int         send_pos;
	int         next_send_count;

	int         recv_pos;
	int         next_recv_count;

	char        *send_bufs;
	int         send_bufs_size;
	char        recv_buf[MAX_RECV_BUFF_SIZE];
	char        send_buf[MAX_SEND_BUFF_SIZE];
	int         recv_state;  // 0 recv blcok size,1 recv data

	TCriticalSection * FCS;
public:
	server_client(completion_socket *cs,int index);
	virtual ~server_client(void);

protected:
	virtual void OnConnected();
	virtual void OnDisconnected();
	virtual void OnSend(DWORD n);
	virtual void OnRecv(char * buf,DWORD n);
  	virtual void OnFree(int opt);
};
#endif