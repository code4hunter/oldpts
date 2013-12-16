#ifndef _CThread_tH_
#define _CThread_tH_

#include <windows.h>

class CThread
{
protected:
	HANDLE  d_threadHandle;
	DWORD   d_threadID;
	bool    d_bIsRunning;

public:

	void Begin();
	void End();
	bool IsRunning();

	virtual DWORD ThreadProc(void);

public:
	CThread(void);
	virtual ~CThread(void);
};

#endif