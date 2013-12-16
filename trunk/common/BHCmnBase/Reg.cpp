#include "stdafx.h"
#include "reg.h"
#include <comutil.h>
#pragma comment(lib, "comsupp.lib")
#pragma comment(lib, "comsuppw.lib")

/*================================================================ 
* 函数名：    CReg
* 参数：      (HKEY hRootKey) 
* 说明：      如果构造函数不带参数，则使用默认的参数，m_hRootKey被初始化
			  为HKEY_LOCAL_MACHINE, 如果带有参数则 m_hRootKey为指定的值
================================================================*/ 
CReg::CReg(HKEY hRootKey) 
{
	m_hRootKey = hRootKey; 
}

CReg::~CReg() //在析构函数中关闭打开注册表句柄
{
	Close();
}



/*================================================================ 
* 函数名：    VerifyKey
* 参数：      (HKEY hRootKey, LPCSTR pszPath) 
* 功能描述:   判断给定的路径是否存在 (兼有打开的功能)
			  如果第一个参数为NULL，则使用默认的根键。
* 返回值：    BOOL
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
* 函数名：    VerifyValue
* 参数：      (LPCSTR pszValue)
* 功能描述:   判断给定的值是否存在 （请先调用VerifyKey，然后在使用该函数）
* 返回值：    BOOL
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
* 函数名：    CreateKey
* 参数：      (HKEY hRootKey, LPCSTR pszPath)
* 功能描述:   创建路径
* 返回值：    BOOL
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
* 函数名：    Write
* 参数：      (LPCSTR lpszKeyName, int iVal)
* 功能描述:   写入整型值
* 返回值：    BOOL
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
* 函数名：    Write
* 参数：      (LPCSTR lpszKeyName, DWORD dwVal)
* 功能描述:   写入DWORD值
* 返回值：    BOOL
================================================================*/ 
BOOL CReg::Write (LPCSTR lpszKeyName, DWORD dwVal)
{
	return ::RegSetValueExA (m_hSubKey, lpszKeyName, 0L, REG_DWORD,
		(CONST BYTE*) &dwVal, sizeof(DWORD));
}


/*================================================================ 
* 函数名：    Write
* 参数：      (LPCSTR lpszKeyName, LPCSTR pszData)
* 功能描述:   写入字符串值
* 返回值：    BOOL
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
* 函数名：    Write
* 参数：      (LPCSTR lpszKeyName, VARIANT Value)
* 功能描述:   写入VARIANT
* 返回值：    BOOL
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
* 函数名：    Read
* 参数：      (LPCSTR lpszKeyName, int& iVal) 第2个参数通过引用传递，可以在函数中修改实参
* 功能描述:   读取整数
* 返回值：    BOOL
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
* 函数名：    Read
* 参数：      (LPCSTR lpszKeyName, DWORD& dwVal) 第2个参数通过引用传递，可以在函数中修改实参
* 功能描述:   读取DWORD值
* 返回值：    BOOL
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
* 函数名：    Read
* 参数：      (LPCSTR lpszKeyName, LPCSTR lpszVal) 第2个参数通过引用传递，可以在函数中修改实参
* 功能描述:   读取字符串值
* 返回值：    BOOL
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
* 函数名：    Read
* 参数：      (LPCSTR lpszKeyName, VARIANT* Value) 
* 功能描述:   读取事先不知道类型的值，如果为REG_DWORD则放入Value->，若为REG_SZ则放入
* 返回值：    BOOL
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
* 函数名：    DeleteValue
* 参数：      (LPCSTR pszValue) 
* 功能描述:   删除值
* 返回值：    BOOL
================================================================*/ 
BOOL CReg::DeleteValue (LPCSTR pszValue)
{
	if(::RegDeleteValueA(m_hSubKey, pszValue)== ERROR_SUCCESS)		
		return TRUE;
	else
		return FALSE;
}

/*================================================================ 
* 函数名：    DeleteKey
* 参数：      (HKEY hRootKey, LPCSTR pszPath) 
* 功能描述:   删除路径
* 返回值：    BOOL
================================================================*/ 
BOOL CReg::DeleteKey (LPCSTR pszPath)
{

	if(::RegDeleteKeyA (m_hRootKey, pszPath) == ERROR_SUCCESS)
		return TRUE;
	else
		return FALSE;
}


/*================================================================ 
* 函数名：    Close
* 参数：      
* 功能描述:   关闭注册表
* 返回值：    void
================================================================*/ 
 void CReg::Close()
{
	if (m_hSubKey)
	{
		::RegCloseKey (m_hSubKey);
		m_hSubKey = NULL;
	}
}

