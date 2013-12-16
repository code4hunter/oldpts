#include "thread.h"
#include "cErrorb.h"

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
		if( d_threadHandle == NULL )
			throw cErrorb( "CThread() - Thread creation failed." );
	}
	d_bIsRunning = true;
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

void CThread::SetError( const char *pBuffer )
{
	if( pBuffer == NULL )
		strcpy( d_errorBuffer, "Unspecified." );
	else
	{
		if( sizeof( d_errorBuffer ) > strlen( pBuffer ) )
			strcpy( d_errorBuffer, pBuffer );
		else
		{
			strncpy( d_errorBuffer, pBuffer, sizeof( d_errorBuffer ) );
			d_errorBuffer[ sizeof( d_errorBuffer ) - 1 ] = '\0';
		}
	}
}

const char *CThread::Error()
{
	return (const char *)d_errorBuffer;
}

bool CThread::IsRunning()
{
	return d_bIsRunning;
}
