/**************************************************
* Function:  Receive CJHB
* Desc:      Create a thread Recv all CJHB and Post message to the special Window
* Author:    CodeHunter 2004
* Create:    2004-11-27
* Modify:
**************************************************/

#ifndef RECVCJHB_H
#define RECVCJHB_H

#include <Winsock.h>
#include "Thread.h"
#include "cErrorb.h"
#include "cjhb_rec.h"

class recv_cjhb :public CThread
{
private:
	SOCKET m_sock;
	int	   m_svr_port;
	char   m_svr_IP[20];
	cjhb_rec m_cjhb_buf[10];

	int	init(void);

	bool SendBuffer(char *ABuf, int ASize);
	bool RecvBuffer(char *ABuf, int ASize);

	char   m_gddm[30];
	short  m_type;
protected:
	virtual DWORD ThreadProc(void);
	//接收到成交回报
	virtual void OnRecvCJHB(cjhb_rec * new_cjhb);
	virtual void OnTerminate(int exit_code);
public:
	recv_cjhb();
	~recv_cjhb();

	int Connect(char * svr,int port);

	int login(char * gddm,int type);  //it's block
	int logout(void);                 //it's block

	int Disconnect(void);
};

#endif