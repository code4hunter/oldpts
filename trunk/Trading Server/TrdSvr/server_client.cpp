#include <assert.h>
#include <stdio.h>

#include "server_client.h"
#include "UFrmMain.h"


long g_req_num=0;
TSafeStrings *g_order_list = NULL;

server_client::server_client(completion_socket *cs,int index):completion_key(cs,index)
{
	answer=NULL;
	ansCount=0;
	m_trd =  NULL;

	if( pw.load_plugin( g_stp->PlugInName.c_str()) )
	{
		m_trd = pw.create(g_stp->FileName.c_str(),get_callback_fun());
	}
}

server_client::~server_client(void)
{
	if( m_trd )
	{
  	try
    {
			m_trd->CloseLink();
      pw.free_itf(m_trd);
    }
    catch(...)
    {

    }
    m_trd = NULL;
	}
}

void server_client::OnFree(int opt)
{
  switch(opt)
  {
    case IO_DISCONNECTED:
      this->close_socket();
    break;
    case KEEP_ALIVE:
      if(m_trd)
      {
      	try
        {
        	m_trd->KeepAlive();
        }
        catch(...)
        {
        	FrmMain->LogIt(">KeepAlive Error",ltErr);
        }
      }
    break;
  }
}

void server_client::OnConnected()
{
	if(WSAAsyncSelect(work_sock,FrmMain->Handle,MY_DISCONNECTED,FD_CLOSE))
  {
    FrmMain->LogIt(">WSAAsyncSelect error",ltErr);
  }
  
  sockaddr sa;
  int size=sizeof( sockaddr );
  if(getpeername(work_sock,&sa,&size)==0)
  {
    peer_ip.sprintf("%s:%d - %d ",inet_ntoa(((sockaddr_in *)(&sa))->sin_addr),
      ntohs(((sockaddr_in *)(&sa))->sin_port),
      this->work_sock);
    FrmMain->LogIt(peer_ip + "Peer Connected ",ltMsg);
  }
  else
  {
    FrmMain->LogIt(peer_ip + "getpeername error",ltErr);
    this->close_socket();
	}

	if( m_trd == NULL ) this->close_socket();

  ansCount = 0;
  memset(&request,0,sizeof(TRequest));
  memset(&ans,0,sizeof(TAnswer));
	if(answer!=NULL)
	{
		if(m_trd->FreeAnswer(answer)==TRUE)
			answer=NULL;
		else
			FrmMain->LogIt(">FreeAnswer Error",ltErr);
	}

  //set send buffer and recv buffer to zero
  set_buffer(0,0);
  set_keep_alive(TRUE);
	recv_pos=0;
  next_recv_count=sizeof(TRequest);
  Recv2((char*)(&request),next_recv_count);
}

void server_client::OnDisconnected()
{
	if( m_trd != NULL )
	{
  	try
    {
			m_trd->CloseLink();
    }
    catch(...)
    {
    	FrmMain->LogIt(">CloseLink Error",ltErr);
    }

		if(answer!=NULL)
		{
			if(m_trd->FreeAnswer(answer)==TRUE)
				answer=NULL;
			else
				FrmMain->LogIt("FreeAnswer Error",ltErr);
		}
	}
  FrmMain->LogIt( peer_ip + "Peer Disconnected "  ,ltMsg);
}

//前一个Send已经完成可以继续新的Send或则其他操作
void server_client::OnSend(DWORD n)
{
  int ret;
	next_send_count-=n;
  send_pos+=n;

  if(next_send_count==0)
  {
    if(ansCount>0)
    {
      assert(answer!=NULL);
      if(m_trd->FreeAnswer(answer)!=0)
        answer=NULL;
      else
        FrmMain->LogIt("FreeAnswer Error",ltErr);
    }
    //FrmMain->LogIt(peer_ip + "Answer Done "  ,ltMsg);
    recv_pos=0;
    next_recv_count=sizeof(TRequest);
    Recv2((char*)(&request),next_recv_count);
  }
  else if(next_send_count>0)
  {
    if(ansCount>0)
    {
			ret=Send2((char*)answer + send_pos,next_send_count);
    }
    else
    {
      ret=Send2((char*)(&ans) + send_pos,next_send_count);
    }
  }
  else
  {
    String s;
    s.printf("%s Send More send_count=%d send_pos=%d",peer_ip.c_str(),next_send_count,send_pos);
		FrmMain->LogIt(s  ,ltErr);
		this->close_socket();
  }

  if(check_result(ret)==false)
  {
    this->close_socket();
    FrmMain->LogIt("SOCKET_ERROR - " + IntToStr(ret),ltErr);
  }
}

//已经接收到数据
void server_client::OnRecv(char * buf,DWORD n)
{
  int ret;
  next_recv_count-=n;
  recv_pos+=n;
  //assert(answer==NULL);
  if(next_recv_count==0)
  {
    ansCount = 0;
    send_pos=0;
    memset(&ans,0,sizeof(TAnswer));
    InterlockedIncrement(&g_req_num);
    //////////////////////////////////////////////////////////////////////////
		next_send_count=sizeof(TAnswer);

		if( request.Head.Version != 2008 )
		{
    	this->close_socket();
			FrmMain->LogIt(peer_ip + " PROTOCAL_ERROR",ltErr);
		}
		else
		{
			if( m_trd == NULL )
			{
				ans.Head.RetVal = -1;
				ret=Send2((char*)(&ans),next_send_count);
			}
			else
			{
				int reqret = m_trd->Request(request,&answer,ansCount);
				if(reqret==0)
				{
					if( ansCount>0 )
					{
						if( g_order_list )
						{
							if( request.Head.FuncType == ftOrder )
							{
								String stmp;
								stmp.sprintf("%-15s %-10s %-15s %-15s %-30s %10.5f %10d %c %c",
								answer[0].Order.ContractID,
								Time().FormatString("hhnnss").c_str(),
								m_trd->GetStockAccountByType(asCA),
								m_trd->GetStockAccountByMarket(request.Order.Market),
								request.Order.SecuID,
								request.Order.Price,
								request.Order.Num,
								request.Order.Type,
								request.Order.Market);
								g_order_list->Lock();
								g_order_list->Add( stmp );
								g_order_list->Unlock();
							}
						}
						next_send_count=sizeof(TAnswer)*ansCount;
						ret=Send2((char*)answer,next_send_count);
					}
					else
					{
						ret=Send2((char*)(&ans),next_send_count);
					}
				}
				else
				{ //执行错误
					ans.Head.RetVal = reqret;
					ret=Send2((char*)(&ans),next_send_count);
				}
			}
		}
	//////////////////////////////////////////////////////////////////////////
  }
  else if(next_recv_count>0)
  {
    Recv2((char *)(&request) + recv_pos,next_recv_count);
  }
  else
  {
    String s;
    s.printf("%s Recv More next_recv_count=%d recv_pos=%d",peer_ip.c_str(),next_recv_count,recv_pos);
    FrmMain->LogIt(s  ,ltErr);
  }

  if(check_result(ret)==false)
  {
    this->close_socket();
    FrmMain->LogIt("SOCKET_ERROR - " + IntToStr(ret),ltErr);
  }
}











