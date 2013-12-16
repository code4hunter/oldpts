#if !defined(AFX_TESTJZDLG_H__6041A1A4_CA97_46DC_AF31_D993428D0893__INCLUDED_)
#define AFX_TESTJZDLG_H__6041A1A4_CA97_46DC_AF31_D993428D0893__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

#include "JZAPI.H"
class CTestJZDlg : public CDialog
{
public:
	CTestJZDlg(CWnd* pParent = NULL);	// standard constructor

	enum { IDD = IDD_TESTJZ_DIALOG };
	CIPAddressCtrl	m_midAddr;
	UINT	m_nMidPort;
	CString m_strZjzh;
	CString m_strJysdm;
	CString	m_strZqdm;
	CString	m_strGddm;
	CString	m_dbWtjg;
	CString	m_nWtsl;
	CString	m_strGydm;
	CString	m_strGymm;
	UINT    m_nWtNum;

	tagNETWORKADD	m_servAddr[3];

public:
	virtual BOOL DestroyWindow();
	
protected:
	HICON m_hIcon;	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLogin();
	afx_msg void OnSbmr();
	DECLARE_MESSAGE_MAP()
};

#endif 
