// ComUtility.cpp : CComUtility 的实现
#include <stdio.h>
#include "ComSecurity.h"

// CComUtility


HRESULT  CComSecurity::get_UserName(BSTR* pVal)
{
  *pVal = m_UserName.Copy();
	return S_OK;
}

HRESULT  CComSecurity::put_UserName(BSTR newVal)
{
	m_UserName = WideString(newVal);
	return S_OK;
}

HRESULT  CComSecurity::get_Password(BSTR* pVal)
{
	*pVal=m_Password.Copy();
	return S_OK;
}

HRESULT  CComSecurity::put_Password(BSTR newVal)
{
	m_Password = WideString(newVal);
	return S_OK;
}

HRESULT  CComSecurity::get_Domain(BSTR* pVal)
{
	*pVal=m_Domain.Copy();
	return S_OK;
}

HRESULT  CComSecurity::put_Domain(BSTR newVal)
{
	m_Domain = WideString(newVal);
	return S_OK;
}

HRESULT  CComSecurity::get_AuthnSvc(LONG* pVal)
{
	*pVal = m_AuthnSvc;
	return S_OK;
}

HRESULT  CComSecurity::put_AuthnSvc(LONG newVal)
{
	m_AuthnSvc = newVal;
	return S_OK;
}

HRESULT  CComSecurity::get_AuthnLevel(LONG* pVal)
{
	*pVal = m_AuthnLevel;
	return S_OK;
}

HRESULT  CComSecurity::put_AuthnLevel(LONG newVal)
{
	m_AuthnLevel = newVal;
	return S_OK;
}

HRESULT  CComSecurity::get_ImpersonationLevel(LONG* pVal)
{
	*pVal =	m_ImpersonationgLevel;
	return S_OK;
}

HRESULT  CComSecurity::put_ImpersonationLevel(LONG newVal)
{
	m_ImpersonationgLevel = newVal;
	return S_OK;
}

HRESULT  CComSecurity::get_ClsCtx(LONG* pVal)
{
	*pVal = m_ClsCtx;
	return S_OK;
}

HRESULT  CComSecurity::put_ClsCtx(LONG newVal)
{
	m_ClsCtx = newVal;
	return S_OK;
}

HRESULT  CComSecurity::Reset(void)
{
	m_AuthnLevel = 2 ;
	m_AuthnSvc   = RPC_C_AUTHN_WINNT ;
	m_ImpersonationgLevel =  3 ;
	m_ClsCtx     = CLSCTX_ALL ;
	m_UserName = WideString(L"");
	m_Password = WideString(L"");
	m_Domain   = WideString(L"");
	m_Midd     = WideString(L"");
  m_UseDefaultSec = false;
	return S_OK;
}

void GenAuthInfo(SOLE_AUTHENTICATION_INFO * authInfo,WideString & UserName ,WideString & Password,WideString & Domain)
{
	// Auth Identity structure
	SEC_WINNT_AUTH_IDENTITY_W authidentity;
	ZeroMemory( &authidentity, sizeof(SEC_WINNT_AUTH_IDENTITY_W) );

	authidentity.User =(unsigned short *)(wchar_t*)UserName;
	authidentity.UserLength = UserName.Length();
	authidentity.Domain = (unsigned short *)(wchar_t*)Domain;
	authidentity.DomainLength = Domain.Length();
	authidentity.Password =(unsigned short *)(wchar_t *)Password;
	authidentity.PasswordLength = Password.Length();
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

HRESULT  CComSecurity::CreateInstance(BSTR Server, BSTR sCLSID,BSTR sIID, IUnknown** pInstance)
{
	HRESULT hr;
	*pInstance = NULL;

	IID IID_tmp;
	CLSID CLSID_tmp;
	TCHAR strErr[255];

	WideString svr = WideString(Server);
	if( svr.Length() == 0)
		svr = m_Midd;

	hr = CLSIDFromString(sCLSID,&CLSID_tmp) ;
	if( !SUCCEEDED(hr) )
	{
		//sprintf( strErr, _T("CLSIDFromString 调用失败！%s"),_com_error(hr).ErrorMessage());
		return hr;
	}

	hr = CLSIDFromString(sIID,&IID_tmp) ;
	if( !SUCCEEDED(hr) )
	{
		//sprintf( strErr, _T("CLSIDFromString 调用失败！%s"),_com_error(hr).ErrorMessage());
		return hr;
	}

  if (m_UseDefaultSec)
  {
    return CoCreateInstance( CLSID_tmp,NULL,CLSCTX_ALL,IID_tmp,(void**)pInstance);
  }
  else
  {

    MULTI_QI mqi[] = {{&IID_tmp,NULL,S_OK}};
    // Auth Identity structure
    COAUTHIDENTITY authidentity;
    ZeroMemory( &authidentity, sizeof(authidentity) );

    authidentity.User =(unsigned short *)(wchar_t *)m_UserName;
    authidentity.UserLength = m_UserName.Length();
    authidentity.Domain = (unsigned short *)(wchar_t *)m_Domain;
    authidentity.DomainLength =m_Domain.Length();
    authidentity.Password =(unsigned short *)(wchar_t *)m_Password;
    authidentity.PasswordLength = m_Password.Length();
    authidentity.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

    COAUTHINFO auth =  { m_AuthnSvc,
      RPC_C_AUTHZ_NONE,
      NULL,
      m_AuthnLevel,
      m_ImpersonationgLevel,
      &authidentity,
      EOAC_NONE};

		COSERVERINFO csi = {0,(BSTR)svr,&auth,0};


    hr = CoCreateInstanceEx(CLSID_tmp,NULL,m_ClsCtx,&csi,sizeof(mqi)/sizeof(mqi[0]),mqi);

    if(!SUCCEEDED(hr))
    {
      //sprintf( strErr, _T("无法建立指定对象的实例！%s"),_com_error(hr).ErrorMessage());
      return hr;
    }

    *pInstance = mqi[0].pItf;
  }

	return S_OK;
}


HRESULT CComSecurity::SetClientBlanket( IClientSecurity  * pSec,
									  IUnknown * pIUnknown,
									  WideString & UserName ,
									  WideString & Password,
									  WideString & Domain)
{
	HRESULT hr;

	// Auth Identity structure
	SEC_WINNT_AUTH_IDENTITY_W authidentity;
	ZeroMemory( &authidentity, sizeof(authidentity) );

	authidentity.User =(unsigned short *)(wchar_t *)UserName;
	authidentity.UserLength = UserName.Length();
	authidentity.Domain = (unsigned short *)(wchar_t *)Domain;
	authidentity.DomainLength = Domain.Length();
	authidentity.Password =(unsigned short *)(wchar_t *)Password;
	authidentity.PasswordLength = Password.Length();
	authidentity.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

	DWORD pAuthnSvc;
	DWORD pAuthzSvc;
	OLECHAR *pServerPrincName = NULL;
	DWORD pAuthnLevel;
	DWORD pImpLevel;
	//void *pAuthInfo;
	DWORD pCapabilites;

	hr = pSec->QueryBlanket(
		pIUnknown,
		&pAuthnSvc,
		&pAuthzSvc,
		/*&pServerPrincName*/NULL,
		&pAuthnLevel,
		&pImpLevel ,
		NULL,
		&pCapabilites
		);

	if( SUCCEEDED(hr) )
	{
		hr = pSec->SetBlanket(
			pIUnknown,
			m_AuthnSvc,
			pAuthzSvc ,
			/*pServerPrincName*/NULL,
			m_AuthnLevel,
			m_ImpersonationgLevel,
			&authidentity,
			pCapabilites
			);
	}

	if( pServerPrincName ) ::CoTaskMemFree( pServerPrincName );

	return hr;
}

HRESULT  CComSecurity::SetClientBlanket(IUnknown* pProxy, VARIANT_BOOL* Ret)
{
	*Ret = VARIANT_FALSE;

  if (m_UseDefaultSec)
  {
    *Ret = VARIANT_TRUE;
    return S_OK;
  }
  else
  {

    IClientSecurity  * pSec = NULL;
    HRESULT hr = pProxy->QueryInterface(IID_IClientSecurity,reinterpret_cast<void**>(&pSec));

    if( !SUCCEEDED(hr))
    {
      return hr;//Error(_T("获得IID_IClientSecurity失败！"));
    }

    hr = SetClientBlanket(pSec,
      pProxy,
      m_UserName,
      m_Password,
      m_Domain
      );

    pSec->Release();

    if( !SUCCEEDED(hr))
    {
      return hr;//Error(_T("设置代理级别的安全性失败！"));
    }

  }

	*Ret = VARIANT_TRUE;

	return S_OK;
}


HRESULT  CComSecurity::get_MiddSvr(BSTR* pVal)
{
	*pVal=m_Midd.Copy(  );
	return S_OK;
}

HRESULT  CComSecurity::put_MiddSvr(BSTR newVal)
{
	m_Midd =  WideString(newVal);
	return S_OK;
}
