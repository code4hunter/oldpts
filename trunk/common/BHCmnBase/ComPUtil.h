#ifndef COMPUTIL_H
#define COMPUTIL_H

#include <windows.h>

//ComLogin 在进程的范围内使用指定的安全登陆到远程机器上
HRESULT ComLogin(char * UserName ,char * Password,char * Domain,
			 DWORD dwAuthnLevel = RPC_C_AUTHN_LEVEL_CONNECT,
			 DWORD dwImpLevel = RPC_C_IMP_LEVEL_IMPERSONATE);

// authInfo 为2个SOLE_AUTHENTICATION_INFO大小的数组
void  GenAuthInfo(SOLE_AUTHENTICATION_INFO * authInfo,char * UserName ,char * Password,char * Domain);

#endif