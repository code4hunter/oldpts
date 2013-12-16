#ifndef _CThreadH_
#define _CThreadH_

#include <windows.h>

class CThread
{
private:
	HANDLE  d_threadHandle;
	DWORD   d_threadID;
	bool    d_bIsRunning;

protected:
	char d_errorBuffer[ 1000 ];

public:

	void Begin();
	void End();
	bool IsRunning();

	virtual DWORD ThreadProc(void);


	void        SetError( const char *pBuffer );
	const char  *Error();

public:
	CThread(void);
	virtual ~CThread(void);
};

#endif