#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#include <TCHAR.h>
#include "DebugStr.h"

ADDLOG addlog=NULL;

void ODS(const TCHAR * fmt,...)
{
	va_list		argptr;
	TCHAR		text[1024];

	va_start (argptr, fmt);
#if defined(_MSC_VER)
	_vstprintf_s(text,1023, fmt, argptr);
#else
	_vsntprintf(text,1023, fmt, argptr);
#endif
	va_end (argptr);

	add_log(text);
}

void add_log(const TCHAR * text)
{
	#ifdef _DEBUG
		OutputDebugString(text);
	#endif
	if(addlog)
	{
		addlog(text);
	}
}

void ODS(TCHAR type ,const TCHAR* sender,const TCHAR * fmt,...)
{
 	va_list		argptr;
	TCHAR		text[1024];

	va_start (argptr, fmt);
#if defined(_MSC_VER)
	_vstprintf_s(text,1023, fmt, argptr);
#else
	_vsntprintf(text,1023, fmt, argptr);
#endif
	va_end (argptr);

	ODS(_T("#%c#%s#%s"),type,sender,text);
}

void set_addlog_callback(ADDLOG func)
{
    if( func != NULL )
        addlog=func;
}

ADDLOG get_callback_fun(void)
{
    return addlog;
}

