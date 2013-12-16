#ifndef DEBUGSTR_s_H
#define DEBUGSTR_s_H

#include <tchar.h>

typedef void (* ADDLOG)(TCHAR *log);

void ODS(const TCHAR * fmt,...);
void set_addlog_callback(ADDLOG func);

#endif
