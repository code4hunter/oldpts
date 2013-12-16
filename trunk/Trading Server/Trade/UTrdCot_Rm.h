//------------------------------------------------------------------------------
#ifndef UTrdCot_RmH
#define UTrdCot_RmH
//------------------------------------------------------------------------------
#include <IdTCPClient.hpp>
#include <SyncObjs.hpp>
#include "UTrdCot.h"
#include "UTrdStruct_Rm.h"
//------------------------------------------------------------------------------
class TTrdCot_Rm : public TTrdCot
{
private:	// User declarations
  TIdTCPClient *FTcpClt;
  TCriticalSection *FCS;
  int __fastcall Request(TRequest Request,TAnswer **Answer,int &AnsCount);
  int __fastcall Connect();  //≥ı ºªØ
  int __fastcall DeleteAns(TAnswer **Answer)
  {
    delete [] (*Answer);
    return 0;
  }

  String FSvrIp;
  int FPort;

public:		// User declarations
  __fastcall TTrdCot_Rm();
  __fastcall ~TTrdCot_Rm();

	void SetRemote(char * SvrIP,int Port)
	{
		FSvrIp = SvrIP;
        FPort = Port;
  	}
};
//---------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

