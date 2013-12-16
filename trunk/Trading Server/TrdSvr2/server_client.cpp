#include <assert.h>
#include <stdio.h>

#include "server_client.h"
#include "UFrmMain.h"
#include "uZlibFunc.h"

long g_req_num=0;
TSafeStrings *g_order_list = NULL;

server_client::server_client(completion_socket *cs,int index):completion_key(cs,index)
{
	FCS = new  TCriticalSection();
	answer=NULL;
	ansCount=0;
	m_trd =  NULL;

	if( pw.load_plugin( g_stp->PlugInName.c_str()) )
	{
		m_trd = pw.create(g_stp->FileName.c_str(),get_callback_fun());
	}
	send_bufs = NULL;
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

	if( send_bufs != NULL )
	{
		delete [] send_bufs;
		send_bufs = NULL;
	}
	delete FCS;
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

	if( m_trd == NULL )
	{
		this->close_socket();
		return;
	}

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
	if( send_bufs != NULL )
	{
		delete [] send_bufs;
		send_bufs = NULL;
    }
	//set send buffer and recv buffer to zero
	set_buffer(0,0);
	set_keep_alive(TRUE);
	this->set_nagle(FALSE);

	recv_pos=0;
	next_recv_count=sizeof(int);
	recv_state = 0;
	Recv2(recv_buf,next_recv_count);
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
	try
	{
	if(next_send_count==0)
	{
		if( send_bufs != NULL )
		{
			delete[]  send_bufs;
			send_bufs = NULL;
		}
		recv_pos=0;
		next_recv_count=sizeof(int);
		recv_state = 0;
		ret = Recv2(recv_buf,next_recv_count);
	}
	else if(next_send_count>0)
	{
		if(ansCount>1)
		{
			ret=Send2(send_bufs + send_pos,next_send_count);
		}
		else
		{
			ret=Send2(send_buf + send_pos,next_send_count);
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
	catch(...)
	{
    	this->close_socket();
    	FrmMain->LogIt("发送数据过程中的未知错误",ltErr);
    }
}

//已经接收到数据
void server_client::OnRecv(char * buf,DWORD n)
{
	int ret;
	next_recv_count-=n;
	recv_pos+=n;

	try
	{
	if(next_recv_count==0)
	{

		if( recv_state == 0 )
		{
			int block_size = ntohl( ((int*)recv_buf)[0] );
			if( block_size >0 && (block_size+sizeof(int)) <=MAX_RECV_BUFF_SIZE )
			{
            	recv_pos=0;
				next_recv_count=block_size;
				recv_state = 1;
				ret = Recv2(recv_buf+sizeof(int) ,block_size);
			}
			else
            {
				this->close_socket();
				FrmMain->LogIt(peer_ip + " PROTOCAL_ERROR",ltErr);
            }
		}
		else if( recv_state == 1 )
		{
			recv_state=2;
			int dret = zlib_decompress2((char*)recv_buf + sizeof(int), recv_pos,&request,sizeof(request) );
            recv_state=3;
			if (dret!=sizeof(request )  )
			{
            	this->close_socket();
				FrmMain->LogIt(peer_ip + " Decompress_ERROR",ltErr);
			}
			else
			{
				if( request.Head.Version != 2010 )
				{
					this->close_socket();
					FrmMain->LogIt(peer_ip + " PROTOCAL_ERROR",ltErr);
				}
				else
				{
					if( m_trd == NULL )
					{
						ans.Head.RetVal = -1;
						send_pos=0;
						next_send_count=zlib_compress2((char*)(&ans) ,sizeof(ans),send_buf,MAX_SEND_BUFF_SIZE);
						ret=Send2(send_buf,next_send_count);
					}
					else
					{
						ansCount = 0;
						memset(&ans,0,sizeof(TAnswer));
						InterlockedIncrement(&g_req_num);

						FCS->Enter();
						int reqret = 0;
						try
						{
							reqret = m_trd->Request(request,&answer,ansCount);
						}
						catch(Exception &e)
						{
							ODS("Request程中的未知错误,%s,\
							recv_pos=%d,next_recv_count=%d,recv_state=%d,FuncType=%d,send_pos=%d,next_send_count=%d",
							e.Message,
							recv_pos,
							next_recv_count,
							recv_state,
							request.Head.FuncType,
							send_pos,
							next_send_count);
							reqret=-1;
						}
						catch(...)
						{
							ODS("Request程中的未知错误,\
							recv_pos=%d,next_recv_count=%d,recv_state=%d,FuncType=%d,send_pos=%d,next_send_count=%d",
							recv_pos,
							next_recv_count,
							recv_state,
							request.Head.FuncType,
							send_pos,
							next_send_count);
							reqret=-1;
						}
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
								if( ansCount>1 )
								{
									//压缩answer
									send_pos=0;
									next_send_count = zlib_compress((void*)answer,sizeof(TAnswer)*ansCount,(void**)&send_bufs);
									ret=Send2(send_bufs,next_send_count);
								}
								else
								{
									send_pos=0;
									next_send_count=zlib_compress2((char*)answer ,sizeof(TAnswer),send_buf,MAX_SEND_BUFF_SIZE);
									ret=Send2(send_buf,next_send_count);
								}

								if(m_trd->FreeAnswer(answer)!=0)
									answer=NULL;
								else
									FrmMain->LogIt("FreeAnswer Error",ltErr);

							}
							else
							{
								send_pos=0;
								next_send_count=zlib_compress2((char*)(&ans) ,sizeof(ans),send_buf,MAX_SEND_BUFF_SIZE);
								ret=Send2(send_buf,next_send_count);
							}
						}
						else
						{ //执行错误
							ans.Head.RetVal = reqret;
							send_pos=0;
							next_send_count=zlib_compress2((char*)(&ans) ,sizeof(ans),send_buf,MAX_SEND_BUFF_SIZE);
							ret=Send2(send_buf,next_send_count);
						}
						FCS->Leave();
					}
				}
			}
		}
	//////////////////////////////////////////////////////////////////////////
	}
	else if(next_recv_count>0)
	{
		ret = Recv2(recv_buf + recv_pos,next_recv_count);
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
	catch( Exception &e )
	{
		//FrmMain->LogIt("接收数据过程中的未知错误,"+ e.Message,ltErr);
		ODS("接收数据过程中的未知错误,%s,\
		recv_pos=%d,next_recv_count=%d,recv_state=%d,FuncType=%d,send_pos=%d,next_send_count=%d",
		e.Message,
		recv_pos,
		next_recv_count,
		recv_state,
		request.Head.FuncType,
		send_pos,
		next_send_count);
		this->close_socket();
    }
	catch(...)
	{
		ODS("接收数据过程中的未知错误,\
		recv_pos=%d,next_recv_count=%d,recv_state=%d,FuncType=%d,send_pos=%d,next_send_count=%d",
		recv_pos,
		next_recv_count,
		recv_state,
		request.Head.FuncType,
		send_pos,
		next_send_count);
		this->close_socket();
		this->close_socket();
		//FrmMain->LogIt("接收数据过程中的未知错误",ltErr);
	}
}












