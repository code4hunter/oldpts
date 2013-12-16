#if !defined _REG_H
#define _REG_H

/************************************************************************ 
* 文件名：    reg.h
* 文件描述：  注册表读写 
************************************************************************/ 



class CReg //: public CObject
{
public:
	CReg(HKEY hRootKey = HKEY_LOCAL_MACHINE); //构造函数带有默认参数
	virtual ~CReg();

public:
	BOOL VerifyKey (LPCSTR pszPath); 
	BOOL VerifyValue (LPCSTR pszValue);

	BOOL CreateKey (LPCSTR pszPath);
	void Close();

	BOOL DeleteValue (LPCSTR pszValue);
	BOOL DeleteKey (LPCSTR pszPath);

	BOOL Write (LPCSTR pszKey, int iVal);
	BOOL Write (LPCSTR pszKey, DWORD dwVal);
	BOOL Write (LPCSTR pszKey, LPCSTR pszVal);
	BOOL Write (LPCSTR pszKey, VARIANT Value);

	BOOL Read (LPCSTR pszKey, int& iVal);
	BOOL Read (LPCSTR pszKey, DWORD& dwVal);
	BOOL Read (LPCSTR pszKey, LPCSTR lpszVal);
	BOOL Read (LPCSTR pszKey, VARIANT* Value);

protected:	
	HKEY 	m_hSubKey;    //保存打开的子键句柄
	HKEY    m_hRootKey;   //保存根键句柄
};

#endif
