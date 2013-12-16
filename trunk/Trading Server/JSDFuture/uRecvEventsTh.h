//---------------------------------------------------------------------------

#ifndef uRecvEventsThH
#define uRecvEventsThH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <winsock2.h>
#include "UTradeDB.h"

// push header
typedef struct {
	unsigned short usType;
	unsigned short usLength;
} ST_PUSHHEAD;

void SplitString(const char * Sour,int length,TStrings* strList,char DivSign);
//---------------------------------------------------------------------------
class RecvEventsTh : public TThread
{
private:
	//trade_db FDB;
	AnsiString SvrIp ;
	long PushPort;
	bool debug_mode;
	AnsiString JysID; 
	bool GetConfig(const char * setupfile);
	market_type ConvertMarketType(const char *t);
	SOCKET hSockContral;
	TStrings *FFields;
	int handlePushRecv(SOCKET sock) ;
	long last_ping_tick;
protected:
	void __fastcall Execute();
public:
	__fastcall RecvEventsTh(bool CreateSuspended,const char * setupfile);
	__fastcall virtual ~RecvEventsTh(void);
	void __fastcall Stop(void);
	void ConnectToServer(void);
	void SendPing(void);
};
//---------------------------------------------------------------------------

class RecvThFactory
{
private:
	RecvEventsTh *FWorker;
public:
	RecvThFactory(const char * setupfile)
	{
		FWorker = new  RecvEventsTh(True,setupfile);
	}

	~RecvThFactory()
	{
		FWorker->Stop();
		delete FWorker;
	}
	
	void SendPing(void)
	{
		FWorker->SendPing();	
	}
};

extern RecvThFactory *g_recvth;
#endif
