// BmpButton.cpp : 实现文件
//

#include "stdafx.h"
#include "BmpButton.h"


// CBmpButton

IMPLEMENT_DYNAMIC(CBmpButton, CButton)
CBmpButton::CBmpButton()
{
}

// CBmpButton 消息处理程序

BOOL CBmpButton::LoadBitmaps(LPCTSTR lpszBitmapResource)
{
	m_bitmap.DeleteObject();
	if (!m_bitmap.LoadBitmap(lpszBitmapResource))
	{
		TRACE(traceAppMsg, 0, "Failed to load bitmap for normal image.\n");
		return FALSE;   // need this one image
	}
	
	return true;	
}

BOOL CBmpButton::LoadBitmaps(UINT nIDBitmapResource)
{
	m_bitmap.DeleteObject();
	if (!m_bitmap.LoadBitmap(nIDBitmapResource))
	{
		TRACE(traceAppMsg, 0, "Failed to load bitmap for normal image.\n");
		return FALSE;   // need this one image
	}
	return true;
}

void CBmpButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct != NULL);
	ASSERT(m_bitmap.m_hObject != NULL);     // required
	
	static COLORREF white=RGB(255,255,255);

	UINT state = lpDrawItemStruct->itemState;
	CBrush brush;
	CPen pen;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOld ;
	pOld = memDC.SelectObject(&m_bitmap);
	
	BITMAP bmp;
	m_bitmap.GetBitmap(&bmp);

	if (pOld == NULL)
		return;     // destructors will clean up

	CRect rect;
	rect.CopyRect(&lpDrawItemStruct->rcItem);
	
	CString text;
	this->GetWindowText(text);

	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);

	m_TxtCol=::GetSysColor(COLOR_WINDOWTEXT);
	if (state & ODS_SELECTED)
	{
		brush.CreateSysColorBrush(COLOR_BTNFACE);
		pen.CreatePen(PS_SOLID, 1,::GetSysColor(COLOR_3DSHADOW));		
	}
	else if (state & ODS_FOCUS)
	{	
		brush.CreateSysColorBrush(COLOR_WINDOW);
		pen.CreatePen(PS_SOLID, 1,::GetSysColor(COLOR_3DSHADOW));
	}
	else if (state & ODS_DISABLED)
	{	
		brush.CreateSysColorBrush(COLOR_BTNFACE);
		pen.CreatePen(PS_SOLID, 1,::GetSysColor(COLOR_GRAYTEXT));
		m_TxtCol=::GetSysColor(COLOR_GRAYTEXT);
		//ConvertDCToGray(memDC.GetSafeHdc(),0,0,bmp.bmWidth,bmp.bmHeight,white);
	}
	else
	{
		brush.CreateSysColorBrush(COLOR_BTNFACE);
		pen.CreatePen(PS_SOLID, 1,::GetSysColor(COLOR_3DSHADOW));	
	}
	// draw the whole button
	
	CPen * pOldPen=(CPen*)pDC->SelectObject(&pen);
	CBrush *pOldbsh=(CBrush*)pDC->SelectObject(&brush);	
	pDC->Rectangle(&rect);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_TxtCol);
	pDC->TextOut(rect.left+7+bmp.bmWidth,(rect.Height()-tm.tmHeight)/2,text);
	pDC->SelectObject(pOldbsh);
	pDC->SelectObject(pOldPen);

	pDC->TransparentBlt(rect.left+4, rect.top+ (rect.Height()-bmp.bmHeight)/2 , bmp.bmWidth, bmp.bmHeight,&memDC, 0, 0,bmp.bmWidth,bmp.bmHeight,white);
	
	memDC.SelectObject(pOld);
}
BEGIN_MESSAGE_MAP(CBmpButton, CButton)

END_MESSAGE_MAP()

