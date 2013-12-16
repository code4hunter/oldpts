#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

#include "DebugStr_s.h"

ADDLOG addlog=NULL;

void ODS(const TCHAR * fmt,...)
{
	va_list		argptr;
	TCHAR		text[1024];

	va_start (argptr, fmt);
	_vstprintf_s(text ,1023 , fmt, argptr);
	va_end (argptr);
#ifdef _DEBUG
	OutputDebugString(text);
#endif
	if(addlog)
	{
		addlog(text);
	}
}

void set_addlog_callback(ADDLOG func)
{
	addlog=func;
}

