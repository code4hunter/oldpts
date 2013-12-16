//---------------------------------------------------------------------------

#ifndef UKeepAliveThH
#define UKeepAliveThH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "server_socket.h"
//---------------------------------------------------------------------------
class keep_alive_th : public TThread
{            
private:
  server_socket *pSvr_sock;
	DWORD ltimeout;
protected:
  void __fastcall Execute();
public:
  __fastcall keep_alive_th(bool CreateSuspended,server_socket* pss,long timeout);
};
//---------------------------------------------------------------------------
#endif
