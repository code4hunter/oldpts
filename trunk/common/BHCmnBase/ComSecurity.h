#include <windows.h>
#include <system.hpp>


class CComSecurity
{
private:
	LONG m_AuthnLevel;
	LONG m_AuthnSvc;
	LONG m_ImpersonationgLevel;
	LONG m_ClsCtx;
	WideString m_UserName;
	WideString m_Password;
	WideString m_Domain;
	WideString m_Midd;          // 中间件地址

	HRESULT SetClientBlanket( IClientSecurity  * pSec,
		IUnknown * pIUnknown,
		WideString & UserName ,
		WideString & Password,
		WideString & Domain);
public:
	CComSecurity()
	{
		Reset();
	}

  bool m_UseDefaultSec;
public:

	HRESULT (get_UserName)(BSTR* pVal);
	HRESULT (put_UserName)(BSTR newVal);
	HRESULT (get_Password)(BSTR* pVal);
	HRESULT (put_Password)(BSTR newVal);
	HRESULT (get_Domain)(BSTR* pVal);
	HRESULT (put_Domain)(BSTR newVal);
	HRESULT (get_AuthnSvc)(LONG* pVal);
	HRESULT (put_AuthnSvc)(LONG newVal);
	HRESULT (get_AuthnLevel)(LONG* pVal);
	HRESULT (put_AuthnLevel)(LONG newVal);
	HRESULT (get_ImpersonationLevel)(LONG* pVal);
	HRESULT (put_ImpersonationLevel)(LONG newVal);
	HRESULT (CreateInstance)(BSTR Server,BSTR sCLSID,BSTR sIID, IUnknown** pInstance);
	HRESULT (SetClientBlanket)(IUnknown* pProxy, VARIANT_BOOL* Ret);
	HRESULT (get_ClsCtx)(LONG* pVal);
	HRESULT (put_ClsCtx)(LONG newVal);
	HRESULT (Reset)(void);
	HRESULT (get_MiddSvr)(BSTR* pVal);
	HRESULT (put_MiddSvr)(BSTR newVal);
};