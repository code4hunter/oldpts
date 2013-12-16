#include "server_socket.h"
#include "UFrmMain.h"

void server_socket::new_key(completion_key ** ck,int index)
{
  *ck=new server_client(this,index);
}

void server_socket::del_key(completion_key * ck)
{
  delete ck;
}

void server_socket::on_new_client(void)
{
  InterlockedIncrement(&m_client_num);
  //++ m_client_num;
}

void server_socket::on_del_client(void)
{
  InterlockedDecrement(&m_client_num);
  //-- m_client_num;
}

void server_socket::check_disconnect(void)
{

}

void server_socket::keep_alive(void)
{
	//this->post_key_cmd(KEEP_ALIVE);
	EnterCriticalSection(&m_cs);
	for(int i=0;i<m_max_client;i++)
	{
		if(m_keys[i]!=NULL)
		{
			if(m_keys[i]->flag>1)
			{
				m_keys[i]->OnFree(KEEP_ALIVE);
			}
		}
	}
	LeaveCriticalSection(&m_cs);
}
