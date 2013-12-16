#if !defined _REG_H
#define _REG_H

/************************************************************************ 
* �ļ�����    reg.h
* �ļ�������  ע����д 
************************************************************************/ 



class CReg //: public CObject
{
public:
	CReg(HKEY hRootKey = HKEY_LOCAL_MACHINE); //���캯������Ĭ�ϲ���
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
	HKEY 	m_hSubKey;    //����򿪵��Ӽ����
	HKEY    m_hRootKey;   //����������
};

#endif
