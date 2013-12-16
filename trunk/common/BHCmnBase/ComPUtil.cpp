#include "ComPUtil.h"

#include <objidl.h>

void GenAuthInfo(SOLE_AUTHENTICATION_INFO * authInfo,char * UserName ,char * Password,char * Domain)
{
	wchar_t un[100];
	wchar_t ps[20];
	wchar_t dm[20];

	// Convert ANSI user name and domain to Unicode

  MultiByteToWideChar( CP_ACP, 0, UserName,strlen(UserName)+1, un,sizeof(un)/sizeof(un[0]) );
  MultiByteToWideChar( CP_ACP, 0, Password, strlen(Password)+1, ps, sizeof(ps)/sizeof(ps[0]) );
	MultiByteToWideChar( CP_ACP, 0, Domain, strlen(Domain)+1, dm, sizeof(dm)/sizeof(dm[0]) );

	// Auth Identity structure
	SEC_WINNT_AUTH_IDENTITY_W authidentity;
	ZeroMemory( &authidentity, sizeof(authidentity) );

	authidentity.User =(unsigned short *)un;
	authidentity.UserLength = wcslen( (wchar_t *)authidentity.User );
	authidentity.Domain = (unsigned short *)dm;
	authidentity.DomainLength = wcslen( (wchar_t *)authidentity.Domain );
	authidentity.Password =(unsigned short *)ps;
	authidentity.PasswordLength = wcslen( (wchar_t *)authidentity.Password );
	authidentity.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

	ZeroMemory( authInfo, sizeof( SOLE_AUTHENTICATION_INFO ) * 2 );

	// Kerberos Settings
	authInfo[0].dwAuthnSvc = RPC_C_AUTHN_GSS_KERBEROS ;
	authInfo[0].dwAuthzSvc = RPC_C_AUTHZ_NONE;
	authInfo[0].pAuthInfo = &authidentity;

	// NTLM Settings
	authInfo[1].dwAuthnSvc = RPC_C_AUTHN_WINNT;
	authInfo[1].dwAuthzSvc = RPC_C_AUTHZ_NONE;
	authInfo[1].pAuthInfo = &authidentity;
}

HRESULT ComLogin(char * UserName ,char * Password,char * Domain,
			 DWORD dwAuthnLevel,DWORD dwImpLevel)
{
  SOLE_AUTHENTICATION_INFO ai[2];
  GenAuthInfo(ai,UserName,Password,Domain);
  SOLE_AUTHENTICATION_LIST    authList;
	authList.cAuthInfo = 2;
	authList.aAuthInfo =ai;
	HRESULT hr = CoInitializeSecurity(
		NULL,                            // Security descriptor
		-1,                              // Count of entries in asAuthSvc
		NULL,                            // asAuthSvc array
		NULL,                            // Reserved for future use
		dwAuthnLevel,                    // Authentication level
		dwImpLevel,                      // Impersonation level
		&authList,                       // Authentication Information
		EOAC_NONE,                       // Additional capabilities
		NULL                             // Reserved
		);

    return hr;
	//return ( SUCCEEDED(hr) || RPC_E_TOO_LATE == hr);
}