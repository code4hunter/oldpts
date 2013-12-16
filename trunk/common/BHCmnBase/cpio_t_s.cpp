//---------------------------------------------------------------------------
#include <assert.h>
#include "cpio_t_s.h"
//---------------------------------------------------------------------------
#pragma comment(lib, "ws2_32.lib")

class CLIENT  : public completion_key< completion_socket<CLIENT> >
{

public:

	CLIENT( completion_socket<CLIENT> *cs,int key_index): 
	  completion_key< completion_socket<CLIENT> >(cs,key_index){}
};

typedef completion_socket< CLIENT > SERVER ;

DWORD WINAPI run( LPVOID lpParam )
{
	SERVER *cs=(SERVER *)lpParam;
	if(cs) return cs->run_proc();
	else return FALSE;
}

DWORD WINAPI work_th( LPVOID lpParam )
{
	SERVER *cs=(SERVER *)lpParam;
	if(cs) return cs->workth();
	else return FALSE;
}

static SERVER *instance = NULL;
DWORD WINAPI select_th ( LPVOID lpParam )
{
	SERVER *cs=(SERVER *)lpParam;
	instance = cs;
	if(cs) return cs->selectth();
	else return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SOCKET :
		{
			unsigned short errcode=WSAGETSELECTERROR(lParam);
			if(errcode==WSAECONNRESET	|| errcode==WSAECONNABORTED || errcode==WSAENETDOWN)
			{
				if(instance)
				{
					CLIENT * ct = instance->get_key_by_sock(wParam);
					if(ct)
					{
						ct->close_socket();
					}
				}
			}
		}

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
