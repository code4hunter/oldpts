#pragma once


// CBmpButton
inline void MaptoGray(BYTE & red, BYTE & green, BYTE & blue)
{
	red   = ( red * 77 + green * 150 + blue * 29 + 128 ) / 256;
	green = red;
	blue  = red;
}

inline void ConvertDCToGray(HDC hdc,int x,int y,int width,int height,COLORREF ignore_color)
{
	COLORREF pixel;
	BYTE red,green, blue;
	for (int i=0;i<height;i++)
		for (int j=0 ;j<width ; j++)
		{
			pixel=GetPixel(hdc,j,i);
			if(pixel==ignore_color) continue;
			red=GetRValue(pixel);
			green=GetGValue(pixel);
			blue=GetBValue(pixel);
			MaptoGray(red,green,blue);
			SetPixel(hdc,j,i,RGB(red,green,blue));
		}
}

class CBmpButton : public CButton
{
	DECLARE_DYNAMIC(CBmpButton)

public:
	CBmpButton();

	BOOL LoadBitmaps(LPCTSTR lpszBitmapResource);
	BOOL LoadBitmaps(UINT nIDBitmapResource);
protected:
	CBitmap m_bitmap;           // normal image (REQUIRED)
	COLORREF m_TxtCol;
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()

};


