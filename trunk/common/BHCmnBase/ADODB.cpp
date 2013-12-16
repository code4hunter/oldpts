#include "StdAfx.h"
#include "ADODB.h"

CADODB::CADODB(TCHAR * CnnStr)
{
	m_Connected=false;
	lstrcpy(m_CnnStr,CnnStr);

	pConn = NULL;
	pCmd  = NULL;
	pRs  = NULL;

	// Open connection.
	TESTHR(pConn.CreateInstance(__uuidof(Connection)));
	pConn->CursorLocation = adUseClient;

	if(_tcslen(m_CnnStr)>0)
		pConn->ConnectionString=_bstr_t(m_CnnStr);

	//Command
	TESTHR(pCmd.CreateInstance(__uuidof(Command)));
	TESTHR(pRs.CreateInstance(__uuidof(Recordset)));
}

CADODB::~CADODB(void)
{
	Disconnect();
}

void CADODB::Disconnect(void)
{
	// Clean up objects before exit.
	if (pRs)
	{
		if (pRs->State == adStateOpen)
			pRs->Close();
	}
	if (pConn)
	{
		if (pConn->State == adStateOpen)
			pConn->Close();
	}

	m_Connected=false;
}

bool CADODB::ConnectDB(TCHAR * CnnStr)
{
	if( pConn->State == adStateOpen ) pConn->Close(); 

	if(_tcslen(CnnStr)>0)
	{
		lstrcpy(m_CnnStr,CnnStr);
	}

	try
	{

		if(_tcslen(m_CnnStr)>0)
			pConn->ConnectionString=_bstr_t(m_CnnStr);
		else
		{
			return false;
		}

		//pConn->CommandTimeout = 6000;
		pConn->Open ("", "", "", adConnectUnspecified);
		pCmd->ActiveConnection = pConn;
		m_Connected=(pConn->State==adStateOpen);
	}
	catch(_com_error &e)
	{
		m_LastADOError=PrintProviderError(pConn);
		m_LastCOMError=PrintComError(e);
	}
	return m_Connected;
}

///////////////////////////////////////////////
//      PrintProviderError Function          //
///////////////////////////////////////////////

_bstr_t CADODB::PrintProviderError(_ConnectionPtr pConnection)
{
	// Print Provider Errors from Connection object.
	// pErr is a record object in the Connection's Error collection.
	ErrorPtr  pErr = NULL;
	_bstr_t ret;

	if( (pConnection->Errors->Count) > 0)
	{
		long nCount = pConnection->Errors->Count;
		// Collection ranges from 0 to nCount -1.
		TCHAR buf[255];
		for(long i = 0; i < nCount; i++)
		{
			pErr = pConnection->Errors->GetItem(i);
			wsprintf(buf,_T("ADO Error:\n\tError number = %x \n\tDescription = %s"), pErr->Number,
				(LPCTSTR)pErr->Description);
			ret+=buf;
		}
	}

	return ret;
}

//////////////////////////////////////
//      PrintComError Function      //
//////////////////////////////////////

_bstr_t CADODB::PrintComError(_com_error &e)
{
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	_bstr_t ret;

	// Print Com errors.
	TCHAR buf[255];
	wsprintf(buf,_T("COM Error:\n")); 
	ret+=buf;
	wsprintf(buf,_T("\tCode = %08lx\n"),e.Error());
	ret+=buf;
	wsprintf(buf,_T("\tCode meaning = %s\n"), (LPCTSTR)e.ErrorMessage());
	ret+=buf;
	wsprintf(buf,_T("\tSource = %s\n"), (LPCTSTR) bstrSource);
	ret+=buf;
	wsprintf(buf,_T("\tDescription = %s\n"), (LPCTSTR) bstrDescription);
	ret+=buf;
	return ret;
}

