#ifndef DEBUGSTR_H
#define DEBUGSTR_H

#include <TCHAR.h>
#include <windows.h>

typedef void (* ADDLOG)(const TCHAR *log);
/*
ODS日志的格式有两种：

1)		#Type#Sender#Message
2)		Message

#为信息保留字
Type = [E(Error),W(Warning),M(Message)]
Message = 要现实的信息
*/
void ODS(const TCHAR * fmt,...);
void ODS(TCHAR type ,const TCHAR* sender,const TCHAR * fmt,...);
void add_log(const TCHAR * text);
void set_addlog_callback(ADDLOG func);
ADDLOG get_callback_fun(void);
#endif
