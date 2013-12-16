//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <objbase.h>
#include "UKeepAliveTh.h"
#include "UFrmMain.h"
#pragma package(smart_init)

__fastcall keep_alive_th::keep_alive_th(bool CreateSuspended,
  server_socket* pss,long timeout)
  : TThread(CreateSuspended)
{
  this->FreeOnTerminate =false;
  pSvr_sock = pss ;
  ltimeout=timeout;
}
//---------------------------------------------------------------------------
void __fastcall keep_alive_th::Execute()
{
	if(pSvr_sock==NULL) return;
	FrmMain->LogIt("keep_alive_th Æô¶¯",ltMsg);
	#ifdef USECOM
		CoInitialize(NULL);
		FrmMain->LogIt("keep_alive_th Apartment",ltMsg);
	#elif defined USECOMT
		CoInitializeEx(NULL,0);
		FrmMain->LogIt("keep_alive_th MTH",ltMsg);
	#endif

	DWORD oldtick=GetTickCount();

  try
  {
    while( !this->Terminated )
    {
      if ((GetTickCount()-oldtick) >= ltimeout)
      {
				pSvr_sock->keep_alive();
        oldtick=GetTickCount();
			}
      else
        Sleep(50);
    }
  }
  __finally
  {
  #ifdef USECOM
		CoUninitialize();
	#elif defined USECOMT
		CoUninitialize();
	#endif
	}
	FrmMain->LogIt("keep_alive_th Í£Ö¹",ltMsg);
}
//---------------------------------------------------------------------------
