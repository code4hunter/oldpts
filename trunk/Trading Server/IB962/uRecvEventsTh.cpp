//---------------------------------------------------------------------------

#include <vcl.h>
#include <IniFiles.hpp>
#pragma hdrstop

#include "uRecvEventsTh.h"
#include "..\..\common\BHCmnBase\DebugStr.h"

#define MODULENAME ("Thread")
#pragma package(smart_init)

//---------------------------------------------------------------------------

void RecvEventsTh::ConnectToServer(void)
{
	_client->disconnect();
	_client->connect( _host.c_str(), _port, _clientId ) ;
}

__fastcall RecvEventsTh::RecvEventsTh(
	const char *host,int port,int clientId,PosixTestClient *client)
	: TThread(false)
	, _host(host)
	, _port(port)
	, _clientId(clientId)
	, _client(client)
{
	this->FreeOnTerminate = false;
	//this->Resume();
}

__fastcall RecvEventsTh::~RecvEventsTh(void)
{

}
//---------------------------------------------------------------------------

void __fastcall RecvEventsTh::Stop(void)
{
	this->Terminate();
	_client->disconnect();
	this->WaitFor();
}

void __fastcall RecvEventsTh::Execute()
{
	ODS('M',MODULENAME,"事件接收线程启动:%d",this->ThreadID);
	while( !this->Terminated )
	{
    	_client->processMessages();
		if( !_client->isConnected() )
		{
			if( this->Terminated) break;
			ODS('W',MODULENAME,"和服务器无连接,尝试重连....");
			ConnectToServer();
			for( int i=0;i<10;i++)
			{
				if( this->Terminated) break;
				::Sleep(300);
			}
		}
	}
	ODS('M',MODULENAME,"事件接收线程停止:%d",this->ThreadID);
}
//---------------------------------------------------------------------------
