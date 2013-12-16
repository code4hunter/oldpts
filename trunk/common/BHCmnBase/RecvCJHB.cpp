#include "RecvCJHB.h"
//#include <stdio.h>

int	recv_cjhb::init(void)
{
	WSADATA wsaData;
	if( WSAStartup( MAKEWORD(2,1), &wsaData)== SOCKET_ERROR)
	{
		return -1; //WSAStartup failed
	}

	m_sock=INVALID_SOCKET;

	return 0;
}

DWORD recv_cjhb::ThreadProc(void)
{
	int exit_code=0;

	clhb_ans ca;
	while(this->IsRunning())
	{
		//recv cjhb
		if(RecvBuffer((char*)&ca,sizeof(ca)))
		{
			//invoke OnRecvCJHB
			OnRecvCJHB(&(ca.cr));
		}
		else
		{
			exit_code=-1;
			break;
		}
	}
	//invoke OnTerminate

	OnTerminate(exit_code);

	Disconnect();

	return 0;
}

void recv_cjhb::OnRecvCJHB(cjhb_rec * new_cjhb)
{

#ifdef _DEBUG

	//MessageBox(NULL,new_cjhb->gddm,new_cjhb->code,0);
	char buf[200];

	if(new_cjhb)
	{
		wsprintf(buf,"%c,%d,%d",new_cjhb->bs,
			new_cjhb->code,
			new_cjhb->date/*,
						  (float)new_cjhb->deal_money,
						  new_cjhb->deal_num,
						  new_cjhb->deal_price,
						  new_cjhb->deal_time,
						  new_cjhb->gddm,
						  new_cjhb->no,
						  new_cjhb->ord_id,
						  new_cjhb->ord_time,
						  new_cjhb->stk_bal*/);

						  OutputDebugString(buf);
	}
#endif
}

void recv_cjhb::OnTerminate(int exit_code)
{
}

recv_cjhb::recv_cjhb()
{
	if(init()!=0) throw cErrorb( "socket creation failed." );
}

recv_cjhb::~recv_cjhb()
{
	Disconnect();
	WSACleanup();
	End();
}

int recv_cjhb::Connect(char * svr,int port)
{
	Disconnect();

	if(INVALID_SOCKET!=m_sock) return -1; //已经连接

	m_svr_port=port;
	strcpy(m_svr_IP,svr);

	//create a socket;
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(m_sock == INVALID_SOCKET)
	{
		return -1;
	}

	//Init server addr;
	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(m_svr_port);
	local.sin_addr.S_un.S_addr = inet_addr(m_svr_IP);

	//connect server;
	if( connect(m_sock,(LPSOCKADDR)&local, sizeof(local)) == SOCKET_ERROR)
	{
		closesocket(m_sock);
		m_sock=INVALID_SOCKET;
		return -2;
	}

	return 0;
}

int recv_cjhb::login(char * gddm,int type)
{
	if(INVALID_SOCKET==m_sock) return -1;
	//send login req
	cjhb_req cr;
	cr.FuncType=ftLogin;
	strcpy(cr.login.gdzh,gddm);
	cr.login.type=type;
	//recv ret code
	if(!this->SendBuffer((char*)&cr,sizeof(cr)))
		return -1; //发送失败

	clhb_ans ca;
	if(!this->RecvBuffer((char*)&ca,sizeof(ca)))
		return -2; //接收失败

	if(ca.AnsCount==1 && ca.CurAnsNo==1 && ca.RetVal==0) 
	{
		strcpy(m_gddm,gddm);
		m_type=type;
		End();
		Begin();
		return 0;
	}
	return -3;
}

int recv_cjhb::logout(void)
{
	Disconnect();
	//End();
	return 0;
	//if(INVALID_SOCKET==m_sock) return -1;

	//End();
	////send login req
	//cjhb_req cr;
	//cr.FuncType=ftLogout;
	//strcpy(cr.logout.gdzh,m_gddm);
	//cr.logout.type=m_type;
	////recv ret code
	//if(!this->SendBuffer((char*)&cr,sizeof(cr)))
	//	return -1; //发送失败
	//
	//clhb_ans ca;
	//if(!this->RecvBuffer((char*)&ca,sizeof(ca)))
	//	return -2; //接收失败

	//if(ca.AnsCount==1 && ca.CurAnsNo==1 && ca.RetVal==0) return 0;
	//
	//return -3;
}

int recv_cjhb::Disconnect(void)
{
	if(INVALID_SOCKET!=m_sock)
	{
		shutdown(m_sock, 1);
		closesocket(m_sock);
		m_sock=INVALID_SOCKET;
	}

	return 0;
}

bool recv_cjhb::SendBuffer(char *ABuf, int ASize)
{
	int ret = 0;
	int iSendBytes = 0;
	while(iSendBytes < ASize)
	{
		ret = send(m_sock, ABuf + iSendBytes, ASize - iSendBytes, 0);
		if(ret == SOCKET_ERROR || ret == 0)
		{
			return false;
		}

		iSendBytes += ret;
	}
	return true;
}

bool recv_cjhb::RecvBuffer(char *ABuf, int ASize)
{
	int ret = 0;
	int iRecvBytes = 0;
	while(iRecvBytes < ASize)
	{
		ret = recv(m_sock, ABuf + iRecvBytes, ASize - iRecvBytes, 0);
		if(ret == SOCKET_ERROR || ret == 0)
		{
			return false;
		}

		iRecvBytes += ret;
	}
	return true;
}