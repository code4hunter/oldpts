#ifndef COMPUTIL_H
#define COMPUTIL_H

#include <windows.h>

//ComLogin �ڽ��̵ķ�Χ��ʹ��ָ���İ�ȫ��½��Զ�̻�����
HRESULT ComLogin(char * UserName ,char * Password,char * Domain,
			 DWORD dwAuthnLevel = RPC_C_AUTHN_LEVEL_CONNECT,
			 DWORD dwImpLevel = RPC_C_IMP_LEVEL_IMPERSONATE);

// authInfo Ϊ2��SOLE_AUTHENTICATION_INFO��С������
void  GenAuthInfo(SOLE_AUTHENTICATION_INFO * authInfo,char * UserName ,char * Password,char * Domain);

#endif