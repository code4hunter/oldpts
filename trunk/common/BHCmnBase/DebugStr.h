#ifndef DEBUGSTR_H
#define DEBUGSTR_H

#include <TCHAR.h>
#include <windows.h>

typedef void (* ADDLOG)(const TCHAR *log);
/*
ODS��־�ĸ�ʽ�����֣�

1)		#Type#Sender#Message
2)		Message

#Ϊ��Ϣ������
Type = [E(Error),W(Warning),M(Message)]
Message = Ҫ��ʵ����Ϣ
*/
void ODS(const TCHAR * fmt,...);
void ODS(TCHAR type ,const TCHAR* sender,const TCHAR * fmt,...);
void add_log(const TCHAR * text);
void set_addlog_callback(ADDLOG func);
ADDLOG get_callback_fun(void);
#endif
