//---------------------------------------------------------------------------

#include <vcl.h>
#include <IniFiles.hpp>
#pragma hdrstop

#include "uRecvEventsTh.h"
#include "UTrdItf_JSDFF.h"
#include "..\..\common\BHCmnBase\DebugStr.h"


#define CMD_CONNECT	1		// ����
#define CMD_PING 20         // ping
#define MSG_MAXLEN 1024
#pragma package(smart_init)

//---------------------------------------------------------------------------

void SplitString(const char * Sour,int length,TStrings* strList,char DivSign)
{
	strList->Clear();
	long n= length;
	char field[1024];
	int j = 0;
	field[0] = '\0';
	for ( int i=0; i<n ;i++)
	{
		if( Sour[i] == DivSign || i == n-1 )
		{
			field[j] ='\0';
			strList->Add(Trim(AnsiString(field)));
			j=0;
			field[0] = '\0';
		}
		else
		{
			field[j++] = Sour[i];
        }
	}
}

void RecvEventsTh::ConnectToServer(void)
{
	int nReturn;
	sockaddr_in tagSockAddrServer;
	// Set values to server sockaddr
	memset (&tagSockAddrServer, 0, sizeof (tagSockAddrServer) );
	tagSockAddrServer.sin_family = AF_INET;
	tagSockAddrServer.sin_port = htons(PushPort);
	tagSockAddrServer.sin_addr.S_un.S_addr = inet_addr (SvrIp.c_str());

	// Create the socket
	hSockContral = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hSockContral == INVALID_SOCKET)
	{
		ODS('E',"JSDEventsRecv","Create socket Error Number: %d.",GetLastError());
		return;
	}
	
	// connect to server
	nReturn = connect (hSockContral, (sockaddr*) &tagSockAddrServer, sizeof (tagSockAddrServer) );
	if (nReturn == -1)
	{
		ODS('E',"JSDEventsRecv","Connect failed, Error Number: %d, Message : client connected to server %s.",
			GetLastError(),inet_ntoa (tagSockAddrServer.sin_addr));
		closesocket (hSockContral);
		hSockContral = INVALID_SOCKET;
		return;
	}

	last_ping_tick = 0;
	// send connect command to server
	char szSend[MSG_MAXLEN];
	memset(szSend, 0, sizeof(szSend));
	ST_PUSHHEAD* pstPushHead = (ST_PUSHHEAD *)szSend;
	pstPushHead->usType = htons(CMD_CONNECT);
	nReturn = ::send(hSockContral, szSend, sizeof(szSend), 0);
	if (nReturn == -1)
	{
		ODS('E',"JSDEventsRecv","login failed, Error Number: %d.",GetLastError());
		closesocket (hSockContral);
		hSockContral = INVALID_SOCKET;
		return;
	}
}

void RecvEventsTh::SendPing(void)
{
	if (hSockContral == INVALID_SOCKET) return;
	if( GetTickCount()-last_ping_tick<90000 ) return;
	char szSend[MSG_MAXLEN];
	memset(szSend, 0, sizeof(szSend));
	ST_PUSHHEAD* pstPushHead = (ST_PUSHHEAD *)szSend;
	pstPushHead->usType = htons(CMD_PING);
	int nReturn = ::send(hSockContral, szSend, sizeof(szSend), 0);
	if (nReturn == -1)
	{
		ODS('E',"JSDEventsRecv","Ping failed, Error Number: %d.",GetLastError());
		closesocket (hSockContral);
		hSockContral = INVALID_SOCKET;
		return;
	}
	else
		last_ping_tick=GetTickCount();	
}

__fastcall RecvEventsTh::RecvEventsTh(bool CreateSuspended,const char * setupfile)
	: TThread(CreateSuspended)
{
	SvrIp      = "127.0.0.1";
	PushPort   = 13158;
	debug_mode = false;
	this->FreeOnTerminate = false;
	GetConfig(setupfile);

	FFields = new TStringList();

	// start socket
	// initialize


	// WSAStartup	
	WSADATA wsaData;
	if (WSAStartup (MAKEWORD (2,2), &wsaData) )
	{
		ODS('E',"JSDEventsRecv","WSAStartup() failed, Error Number: %d.",GetLastError());
		return;
	}

	this->Resume();
}

__fastcall RecvEventsTh::~RecvEventsTh(void)
{
	// close socket
	closesocket (hSockContral);
	// WSACleanup
	WSACleanup ();
	delete FFields;
}
//---------------------------------------------------------------------------

bool RecvEventsTh::GetConfig(const char * setupfile)
{
	TMemIniFile *ini = new TMemIniFile( setupfile );
	try
	{
		// �ж��Ƿ���ڲ�������ã�û�еĻ�����false�Ա�ϵͳ�ܹ�����Ĭ�ϵ�����
		if( ini->SectionExists(PLUGINNAME) == false ) return false;

		SvrIp            = ini->ReadString (PLUGINNAME,"SvrIP",SvrIp);
		PushPort          = ini->ReadInteger(PLUGINNAME,"PushPort",PushPort);
		debug_mode       = ini->ReadBool(PLUGINNAME,"debug_mode",debug_mode);
		JysID            =ini->ReadString (PLUGINNAME,"jysID",JysID);
	}
	__finally
	{
		delete ini;
	}
	return true;
}

void __fastcall RecvEventsTh::Stop(void)
{
	if (hSockContral!=INVALID_SOCKET) {
		closesocket (hSockContral);
	}
	this->Terminate();
	this->WaitFor();
}

AnsiString GetSeatId(market_type t)
{
	switch(t)
	{
		case mtFZZ : return "czce";
		case mtFDL : return "dce";
		case mtFSH : return "sfe";
		case mtJJS : return "cffex";
	}
	return "";
}

market_type  RecvEventsTh::ConvertMarketType(const char *t)
{
	if(t==NULL || strlen(t)<1 ) return mtNo;

	if( strlen(t) == 1 )
	{
		if(t[0] == JysID[1])
			return mtFZZ;
		else if( t[0] == JysID[2])
			return mtFDL;
		else if( t[0] == JysID[3] )
			return mtFSH;
		else if( t[0] == JysID[4] )
			return mtJJS;
		else
			return mtNo;
	}
	else
	{
		if(lstrcmpi(t,  "czce")==0)
			return mtFZZ;
		else if( lstrcmpi(t , "dce")==0)
			return mtFDL;
		else if( lstrcmpi(t , "sfe")==0 )
			return mtFSH;
		else if( lstrcmpi(t , "cffex")==0 )
			return mtJJS;
		else
			return mtNo;
	}
}

// Handle push link receive 
int RecvEventsTh::handlePushRecv(SOCKET sock)
{
	ST_PUSHHEAD stPushHead;		// push header
	int nHeaderLen = sizeof(ST_PUSHHEAD);	// push header length
	int nDataLen = 0;			// recv data length
	int s_nReceived = 0;		// static para
	int nType;					// command type
	int nRead = 0;				// counter of recv char
	char szRecvBuffer[MSG_MAXLEN] = "";	// recv buffer


	// begin recv  ||  just recv a part of header
	if (s_nReceived < nHeaderLen)
	{
		nDataLen = 0;

		nRead = ::recv (sock, (char *) &stPushHead + s_nReceived, nHeaderLen - s_nReceived, 0);

		if (nRead <= 0)
		{
			// sock error occurs, must close
			if (GetLastError() != WSAEWOULDBLOCK)
			{
				s_nReceived = 0;
				return -1;
			}
		}

		s_nReceived += nRead;

		if (s_nReceived < nHeaderLen)
			return 0;

		nDataLen = ntohs(stPushHead.usLength);
		nType = ntohs(stPushHead.usType);
	}

	if (nDataLen > MSG_MAXLEN || nDataLen < 0)
	{
		s_nReceived = 0;
		return 0;
	}

	// just recv a part of whole pack
	if (s_nReceived < nHeaderLen + nDataLen)
	{
		nRead = ::recv (sock, szRecvBuffer + s_nReceived - nHeaderLen, 
						nDataLen + nHeaderLen - s_nReceived, 0);

		if (nRead <= 0)
		{
			if (GetLastError() != WSAEWOULDBLOCK)
			{
				s_nReceived = 0;
				return -1;
			}

		}

		s_nReceived += nRead;
	}

	// recv whole pack
	if (s_nReceived == nHeaderLen + nDataLen)
	{
		// print message
		if (this->debug_mode) {
			ODS('M',"JSDEventsRecv","Receive: [%d]%s", nType, szRecvBuffer);
		}

		try
		{
			//[8002]ibgate5|35812421|ru1011| |1|1.00|77|0|0.00|1|A|q|0|0|0|01419358|| |||0335c2c|0|���� �۸����С��λ�ı���|0|
			switch(nType)
			{
				case 8001: // login
					ODS('M',"JSDEventsRecv","�Ѿ���½����Ϣ���ͷ�����:%s:%d",
					this->SvrIp.c_str(),this->PushPort);
				break;
				case 8002: // ί��
				{
				//[8002]b2cwg  |9999999 |TA1001    |00000181|1|7000.00|181|0|0.00|1|C|a|0|0|0|99999999| |11:15:30| | |czce|0| |
				//[8002]ibgate5|35812421|ru1011| |1|1.00|77|0|0.00|1|A|q|0|0|0|01419358|| |||0335c2c|0|���� �۸����С��λ�ı���|0|
                    trade_db      FDB;
					FDB.connect();
					FDB.add_order(std::string(szRecvBuffer));

					SplitString(szRecvBuffer,nDataLen,FFields,'|');
					if(FFields->Count>=22)
					{
						AnsiString state= FFields->Strings[11];
						if( state.c_str()[0] == 'm' || state.c_str()[0] == 'q' )  //ϵͳ����
						{
							market_type mt = ConvertMarketType(FFields->Strings[10].c_str());
							//this->FDB.add_trade((GetSeatId(mt) + ":" + FFields->Strings[6]).c_str(),
							FDB.add_trade( FFields->Strings[6].c_str(),
								"-1",
								FFields->Strings[1].c_str(),
								TTrdItf_JSDFF::convert_to_PTS_code(FFields->Strings[2].c_str(),mt).c_str(),
								mt,
								convert_datetime_str_to_long(FFields->Strings[19].c_str()),
								convert_datetime_str_to_long(FormatDateTime("yyyymmdd",Date()).c_str()),
								-(FFields->Strings[4].ToInt()-FFields->Strings[7].ToInt()),
								0,
								SConvertOrderType((FFields->Strings[12]+ FFields->Strings[13]).c_str()));
						}
					}
				}
				break;
				case 8003: // ����
                if (Pos(AnsiString("����: ��ί�е��Ѿ��ɽ�"),AnsiString(szRecvBuffer))<1) {
                    //[8003]b2cwg|9999999|TA1001 |00000181|1|7000.00|181|0|0.00|1|C|d|0|0|0|99999999|||b2cwg|11:15:46|czce|0| |
					//[8003]b2cwg|31100005|TA0910|00337795|1|7806.00|873|0|0.00|1|C|a|0|0|0|05821540|||b2cwg|13:39:07|00030070|0|����: ��ί�е��Ѿ��ɽ�|0|
                    /*
                    7.3 ί�С������ر�
					��1������Ա��
					��2���ͻ���
					��3����Լ��
					��4��ϵͳ��
					��5��ί����
					��6��ί�м۸�
                    ��7��ί�к�
                    ��8���ɽ���
					��9���ɽ���
                    ��10��ʣ����
                    ��11��������
					��12��״̬
                    ��13������
                    ��14����ƽ
                    ��15��Ͷ��
                    ��16���������ͻ�����
                    ��17��ί��ʱ��
                    ��18���걨ʱ��
                    ��19�������û�
                    ��20������ʱ��
                    ��21���µ�ϯλ
                    ��22�����ر�־
                    */
					SplitString(szRecvBuffer,nDataLen,FFields,'|');
					if(FFields->Count>=22)
					{
						market_type mt = ConvertMarketType(FFields->Strings[10].c_str());
						//this->FDB.add_trade((GetSeatId(mt) + ":" + FFields->Strings[6]).c_str(),
                        trade_db      FDB;
						FDB.connect();
						FDB.add_trade( FFields->Strings[6].c_str(),
							"-1",
							FFields->Strings[1].c_str(),
							TTrdItf_JSDFF::convert_to_PTS_code(FFields->Strings[2].c_str(),mt).c_str(),
							mt,
							convert_datetime_str_to_long(FFields->Strings[19].c_str()),
							convert_datetime_str_to_long(FormatDateTime("yyyymmdd",Date()).c_str()),
							-(FFields->Strings[4].ToInt()-FFields->Strings[7].ToInt()),
							0,
							SConvertOrderType((FFields->Strings[12]+ FFields->Strings[13]).c_str()));
					}
				}
				break;
				case 8008: // �ɽ�
				//[8008]ibgate5|35812421|IF1011|128559  |17379|016802|0|12269|1|3570.80|0|20101108|13:12:32|0|c|0|1|0|01047725|016802|0|0|
				//[8008]b2cwg  |9999999 |TA1001|00000186|192  |czce  |0|186  |1|7060.00|0|20090608|11:18:32| |c|0|0|0|99999999|czce|0|
				SplitString(szRecvBuffer,nDataLen,FFields,'|');
				if(FFields->Count>=21)
				{
					/*
					�ɽ��ر�
					��1�� ����Ա��
					��2�� �ͻ���
					��3�� ��Լ��
					��4�� ϵͳ��
					��5�� �ɽ���
					��6�� ����
					��7�� ����
					��8�� ί�к�
					��9�� �ɽ���
					��10���ɽ���
					��11��ʣ����
					��12���ɽ�����
					��13���ɽ�ʱ��
					��14������
					��15��״̬
					��16������
					��17����ƽ
					��18��Ͷ��
					��19���������ͻ�����
					��20���µ�ϯλ
					��21�����ر�־
					*/
					market_type mt =  ConvertMarketType(FFields->Strings[19].c_str());
					//this->FDB.add_trade((GetSeatId(mt) + ":" + FFields->Strings[7]).c_str(),
                    trade_db      FDB;
					FDB.connect();
					FDB.add_trade( FFields->Strings[7].c_str(),
						FFields->Strings[4].c_str(),
						FFields->Strings[1].c_str(),
						TTrdItf_JSDFF::convert_to_PTS_code(FFields->Strings[2].c_str(),mt).c_str(),
						mt,
						convert_datetime_str_to_long(FFields->Strings[12].c_str()),
						convert_datetime_str_to_long(FFields->Strings[11].c_str()),
						FFields->Strings[8].ToInt(),
						FFields->Strings[9].ToDouble(),
						SConvertOrderType((FFields->Strings[15]+FFields->Strings[16]).c_str()));
				}
				break;
				case 8009: // ϵͳ״̬�ı�
					ODS('M',"JSDEventsRecv","ϵͳ״̬�ı�: [%d]%s", nType, szRecvBuffer);
				break;
				case 8010: // ��Ϣ����
					ODS('M',"JSDEventsRecv","��Ϣ����: [%d]%s", nType, szRecvBuffer);
				break;
				case 8020:
					ODS('M',"JSDEventsRecv","�յ�ping��Ӧ: [%d]%s", nType, szRecvBuffer);
					//last_ping_tick = GetTickCount();
				break;
			}
		}
		catch( std::string &err )
		{
			ODS('M',"JSDEventsRecv","������д�����ݿ����: %s", err.c_str());
		}
		catch( Exception &e)
		{
			ODS('M',"JSDEventsRecv","�������ݴ���: %s,DATA:[%d]%s", e.Message,nType,szRecvBuffer);
		}

		// reset param
		s_nReceived = 0;
		nDataLen = 0;

		memset(szRecvBuffer, 0, sizeof(MSG_MAXLEN));
	}
	return 0;
}

void __fastcall RecvEventsTh::Execute()
{
	ODS('M',"JSDEventsRecv","�¼������߳�����:%d",this->ThreadID);
	while( !this->Terminated )
	{
		if (hSockContral!=INVALID_SOCKET) {
			int ret = handlePushRecv(hSockContral);

			if (ret < 0) // recv error
			{
				closesocket (hSockContral);
				hSockContral = INVALID_SOCKET;
			}
		}
		else
		{
			if( this->Terminated) break;
			ODS('W',"JSDEventsRecv","�����ͷ�����������,����....");
			ConnectToServer();
			::Sleep(2000);
		}
	}
	ODS('M',"JSDEventsRecv","�¼������߳�ֹͣ:%d",this->ThreadID);
}
//---------------------------------------------------------------------------
