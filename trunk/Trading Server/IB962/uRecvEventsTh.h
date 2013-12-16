//---------------------------------------------------------------------------

#ifndef uRecvEventsThH
#define uRecvEventsThH
//---------------------------------------------------------------------------
#include "PosixTestClient.h"
#include <Classes.hpp>
#include <string>

//---------------------------------------------------------------------------
class RecvEventsTh : public TThread
{
private:
	std::string _host;
	int _port;
	int _clientId;

	PosixTestClient *_client;
protected:
	void __fastcall Execute();
public:
	__fastcall RecvEventsTh(const char *host,int port,int clientId,
		PosixTestClient *client);
	__fastcall virtual ~RecvEventsTh(void);
	void __fastcall Stop(void);
	void ConnectToServer(void);
};
//---------------------------------------------------------------------------
/*
class RecvThFactory
{
private:
	RecvEventsTh *FWorker;
public:
	RecvThFactory()
	{
		FWorker = new  RecvEventsTh(True);
	}

	~RecvThFactory()
	{
		FWorker->Stop();
		delete FWorker;
	}
};
*/
#endif
