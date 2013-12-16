// XColorStatic.h  Version 1.0
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//          
// Modify:  CodeHunter 
//          CodeHunter@msn.com
//
// This software is released into the public domain.
// You are free to use it in any way you like.
//
// This software is provided "as is" with no expressed
// or implied warranty.  I accept no liability for any
// damage or loss of business that this software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef XCOLORSTATIC_H
#define XCOLORSTATIC_H


int GetFontPointSize(int nHeight);
int GetFontHeight(int nPointSize);
/////////////////////////////////////////////////////////////////////////////
// CXColorStatic window

class CXColorStatic : public CStatic
{
// Construction
public:
	CXColorStatic();
	virtual ~CXColorStatic();

// Attributes
public:
	void SetBackgroundColor(COLORREF rgb, BOOL bRedraw = TRUE);
	void SetTextColor(COLORREF rgb, BOOL bRedraw = TRUE);
	void SetBold(BOOL bFlag, BOOL bRedraw = TRUE);
	void SetFont(LPCTSTR lpszFaceName, int nPointSize, BOOL bRedraw = TRUE);
	void SetFont(LOGFONT * pLogFont, BOOL bRedraw = TRUE);
	void SetFont(CFont *pFont, BOOL bRedraw = TRUE);
	void SetIcon(HICON hIcon, BOOL bRedraw = TRUE);
	void SetMargins(int x, int y) { m_nXMargin = x; m_nYMargin = y; }
	void Set3D(COLORREF ShadowColor,BOOL bEnable,BOOL bRedraw = FALSE)
	{
		m_3DEnable=bEnable;
		m_3DColor=ShadowColor;
		if (bRedraw) RedrawWindow();
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXColorStatic)
protected:
    virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont		m_font;
	COLORREF	m_rgbText;
	COLORREF	m_rgbBackground;
	CBrush *	m_pBrush;
	BOOL		m_bBold;
	int			m_nXMargin, m_nYMargin;
	HICON		m_hIcon;

	//Make 3D
	BOOL        m_3DEnable;
	COLORREF    m_3DColor;
	// Generated message map functions
protected:
	//{{AFX_MSG(CXColorStatic)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XCOLORSTATIC_H
