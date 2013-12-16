#if !defined(AFX_TESTJZ_H__C193851A_6674_47C8_9C07_F31B77B4D2A4__INCLUDED_)
#define AFX_TESTJZ_H__C193851A_6674_47C8_9C07_F31B77B4D2A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//////////////////////////////////////////////////////////////

#include "resource.h"		// main symbols

//////////////////////////////////////////////////////////////

class CTestJZApp : public CWinApp
{
public:
	CTestJZApp();

	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////

#endif 