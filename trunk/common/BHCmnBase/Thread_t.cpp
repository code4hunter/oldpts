#include "thread_t.h"

static DWORD WINAPI cThreadProc( CThread *pThis )
{
	return pThis->ThreadProc();
}

CThread::CThread(void)
{
	d_threadID = 0;
	d_threadHandle = NULL;
	d_bIsRunning = false;
}

CThread::~CThread(void)
{
	End();
}

void CThread::Begin()
{
	if( d_threadHandle == NULL )
	{
		// Start the thread.
		d_threadHandle = CreateThread( NULL,
			0,
			(LPTHREAD_START_ROUTINE)cThreadProc,
			this,
			0,
			(LPDWORD)&d_threadID );
		
	}
	if( d_threadHandle != NULL ) d_bIsRunning = true;
}

void CThread::End()
{
	if( d_threadHandle != NULL )
	{
		d_bIsRunning = false;
		WaitForSingleObject( d_threadHandle, INFINITE );
		CloseHandle( d_threadHandle );
		d_threadHandle = NULL;
	}
}

DWORD CThread::ThreadProc(void)
{
	return 0;
}

bool CThread::IsRunning()
{
	return d_bIsRunning;
}
