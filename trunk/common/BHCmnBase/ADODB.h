#ifndef ADODB_H
#define ADODB_H

#include <ole2.h>
#include <stdio.h>

#import "c:\Program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF", "EndOfFile")

class CADODB
{
public:
	TCHAR m_CnnStr[MAX_PATH+1];
	_ConnectionPtr  pConn ;
	_CommandPtr     pCmd  ;
	_RecordsetPtr   pRs  ;

	//function
	_bstr_t PrintProviderError(_ConnectionPtr pConnection);
	_bstr_t PrintComError(_com_error &e);
	inline void TESTHR(HRESULT x) {if FAILED(x) _com_issue_error(x);};

	_bstr_t m_LastADOError;
	_bstr_t m_LastCOMError;

	bool m_Connected;
public:
	CADODB(TCHAR * CnnStr=_T(""));

	virtual ~CADODB(void);

	bool ConnectDB(TCHAR * CnnStr=_T(""));	

	_bstr_t GetLastADOError() {return m_LastADOError;}
	_bstr_t GetLastCOMError() {return m_LastCOMError;}

	void Disconnect(void);

};

#endif
