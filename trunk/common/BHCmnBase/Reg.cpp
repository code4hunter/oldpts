#include "stdafx.h"
#include "reg.h"
#include <comutil.h>
#pragma comment(lib, "comsupp.lib")
#pragma comment(lib, "comsuppw.lib")

/*================================================================ 
* ��������    CReg
* ������      (HKEY hRootKey) 
* ˵����      ������캯��������������ʹ��Ĭ�ϵĲ�����m_hRootKey����ʼ��
			  ΪHKEY_LOCAL_MACHINE, ������в����� m_hRootKeyΪָ����ֵ
================================================================*/ 
CReg::CReg(HKEY hRootKey) 
{
	m_hRootKey = hRootKey; 
}

CReg::~CReg() //�����������йرմ�ע�����
{
	Close();
}



/*================================================================ 
* ��������    VerifyKey
* ������      (HKEY hRootKey, LPCSTR pszPath) 
* ��������:   �жϸ�����·���Ƿ���� (���д򿪵Ĺ���)
			  �����һ������ΪNULL����ʹ��Ĭ�ϵĸ�����
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::VerifyKey (LPCSTR pszPath)
{
 	LONG ReturnValue = ::RegOpenKeyExA (m_hRootKey, pszPath, 0L,
										KEY_ALL_ACCESS, &m_hSubKey);

	if(ReturnValue == ERROR_SUCCESS)
		return TRUE;

	return FALSE;
}


/*================================================================ 
* ��������    VerifyValue
* ������      (LPCSTR pszValue)
* ��������:   �жϸ�����ֵ�Ƿ���� �����ȵ���VerifyKey��Ȼ����ʹ�øú�����
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::VerifyValue (LPCSTR pszValue)
{
	LONG lReturn = ::RegQueryValueExA ( m_hSubKey, pszValue, NULL,
		NULL, NULL, NULL);

	if(lReturn == ERROR_SUCCESS)
		return TRUE;

	return FALSE;
}

/*================================================================ 
* ��������    CreateKey
* ������      (HKEY hRootKey, LPCSTR pszPath)
* ��������:   ����·��
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::CreateKey (LPCSTR pszPath)
{
	DWORD dw;

	LONG ReturnValue = ::RegCreateKeyExA (m_hRootKey, pszPath, 0L, NULL,
							REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, 
							&m_hSubKey, &dw);

	if(ReturnValue == ERROR_SUCCESS)
		return TRUE;

	return FALSE;
}



/*================================================================ 
* ��������    Write
* ������      (LPCSTR lpszKeyName, int iVal)
* ��������:   д������ֵ
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::Write (LPCSTR lpszKeyName, int iVal)
{
	DWORD dwValue;

	dwValue = (DWORD)iVal;
	LONG ReturnValue = ::RegSetValueExA (m_hSubKey, lpszKeyName, 0L, REG_DWORD,
		(CONST BYTE*) &dwValue, sizeof(DWORD));


	if(ReturnValue == ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
}

/*================================================================ 
* ��������    Write
* ������      (LPCSTR lpszKeyName, DWORD dwVal)
* ��������:   д��DWORDֵ
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::Write (LPCSTR lpszKeyName, DWORD dwVal)
{
	return ::RegSetValueExA (m_hSubKey, lpszKeyName, 0L, REG_DWORD,
		(CONST BYTE*) &dwVal, sizeof(DWORD));
}


/*================================================================ 
* ��������    Write
* ������      (LPCSTR lpszKeyName, LPCSTR pszData)
* ��������:   д���ַ���ֵ
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::Write (LPCSTR lpszKeyName, LPCSTR pszData)
{
	LONG ReturnValue = ::RegSetValueExA (m_hSubKey, lpszKeyName, 0L, REG_SZ,
		(CONST BYTE*) pszData, DWORD(strlen(pszData)*2 + 1));


	if(ReturnValue == ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
}


/*================================================================ 
* ��������    Write
* ������      (LPCSTR lpszKeyName, VARIANT Value)
* ��������:   д��VARIANT
* ����ֵ��    BOOL
================================================================*/ 

BOOL CReg::Write (LPCSTR lpszKeyName, VARIANT Value)
{
	DWORD dwValue = 0;
	switch(Value.vt)
	{
	case VT_I4:		dwValue = (DWORD)Value.lVal;
	case VT_I2:		dwValue = (DWORD)Value.iVal;
	case VT_I1:		dwValue = (DWORD)Value.cVal;
	case VT_INT:	dwValue = (DWORD)Value.intVal;
		
		return Write(lpszKeyName, dwValue);
	break;

	case VT_BSTR:
		return Write(lpszKeyName, _com_util::ConvertBSTRToString(Value.bstrVal));
	break;
	default:
		return FALSE;
	}

	return FALSE;
}

/*================================================================ 
* ��������    Read
* ������      (LPCSTR lpszKeyName, int& iVal) ��2������ͨ�����ô��ݣ������ں������޸�ʵ��
* ��������:   ��ȡ����
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::Read(LPCSTR lpszKeyName, int& iVal)
{

	DWORD dwType;
	DWORD dwSize = sizeof (DWORD);
	DWORD dwDest;

	LONG lReturn = ::RegQueryValueExA (m_hSubKey, lpszKeyName, NULL,
		&dwType, (BYTE *) &dwDest, &dwSize);

	if(lReturn == ERROR_SUCCESS)
	{
		iVal = (int)dwDest;
		return TRUE;
	}

	return FALSE;
}


/*================================================================ 
* ��������    Read
* ������      (LPCSTR lpszKeyName, DWORD& dwVal) ��2������ͨ�����ô��ݣ������ں������޸�ʵ��
* ��������:   ��ȡDWORDֵ
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::Read (LPCSTR lpszKeyName, DWORD& dwVal)
{

	DWORD dwType;
	DWORD dwSize = sizeof (DWORD);
	DWORD dwDest;

	LONG lReturn = ::RegQueryValueExA (m_hSubKey, lpszKeyName, NULL, 
		&dwType, (BYTE *) &dwDest, &dwSize);


	if(lReturn == ERROR_SUCCESS)
	{
		dwVal = dwDest;
		return TRUE;
	}

	return FALSE;
}


/*================================================================ 
* ��������    Read
* ������      (LPCSTR lpszKeyName, LPCSTR lpszVal) ��2������ͨ�����ô��ݣ������ں������޸�ʵ��
* ��������:   ��ȡ�ַ���ֵ
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::Read (LPCSTR lpszKeyName, LPCSTR lpszVal)
{

	DWORD dwType;
	DWORD dwSize = 200;

	LONG lReturn = ::RegQueryValueExA (m_hSubKey, lpszKeyName, NULL,
		&dwType, (BYTE *) lpszVal, &dwSize);

	if(lReturn == ERROR_SUCCESS)
	{
		return TRUE;
	}

	return FALSE;
}


/*================================================================ 
* ��������    Read
* ������      (LPCSTR lpszKeyName, VARIANT* Value) 
* ��������:   ��ȡ���Ȳ�֪�����͵�ֵ�����ΪREG_DWORD�����Value->����ΪREG_SZ�����
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::Read(LPCSTR lpszKeyName, VARIANT* Value)
{
	DWORD dwValue;
	if(Read(lpszKeyName, dwValue) == TRUE)
	{
		Value->vt = VT_I4;
		Value->lVal = dwValue;
		return TRUE;
	}

	char  szString[255];
	if(Read(lpszKeyName, szString) == TRUE)
	{
		CString sValue(szString);
		Value->vt = VT_BSTR;
		Value->bstrVal = sValue.AllocSysString();
		return TRUE;
	}

	return FALSE;
}

/*================================================================ 
* ��������    DeleteValue
* ������      (LPCSTR pszValue) 
* ��������:   ɾ��ֵ
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::DeleteValue (LPCSTR pszValue)
{
	if(::RegDeleteValueA(m_hSubKey, pszValue)== ERROR_SUCCESS)		
		return TRUE;
	else
		return FALSE;
}

/*================================================================ 
* ��������    DeleteKey
* ������      (HKEY hRootKey, LPCSTR pszPath) 
* ��������:   ɾ��·��
* ����ֵ��    BOOL
================================================================*/ 
BOOL CReg::DeleteKey (LPCSTR pszPath)
{

	if(::RegDeleteKeyA (m_hRootKey, pszPath) == ERROR_SUCCESS)
		return TRUE;
	else
		return FALSE;
}


/*================================================================ 
* ��������    Close
* ������      
* ��������:   �ر�ע���
* ����ֵ��    void
================================================================*/ 
 void CReg::Close()
{
	if (m_hSubKey)
	{
		::RegCloseKey (m_hSubKey);
		m_hSubKey = NULL;
	}
}

