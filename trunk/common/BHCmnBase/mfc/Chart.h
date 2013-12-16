#pragma once
#include <afxtempl.h>

// CChart
struct double_point
{
	double x;
	double y;
};

class CChart : public CStatic
{
	DECLARE_DYNAMIC(CChart)

public:
	CChart();
	virtual ~CChart();
protected:
	//{{AFX_MSG(CXColorStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void AddY(double y);
	void AddXY(double x,double y);

	void SetBackColor(COLORREF color)
	{
		LOGBRUSH lb;
		m_bs.GetLogBrush(&lb);
		if(color!=lb.lbColor)
		{
			m_bs.DeleteObject();
			lb.lbColor=color;
			m_bs.CreateBrushIndirect(&lb);
			this->Invalidate();
		}
	}

	void SetLineColor(COLORREF color)
	{
		LOGPEN lp;
		m_pen.GetLogPen(&lp);
		if(color!=lp.lopnColor)
		{
			m_pen.DeleteObject();
			lp.lopnColor=color;
			m_pen.CreatePenIndirect(&lp);
			this->Invalidate();
		}
	}

	void ClearAll(void)
	{
		m_Items.RemoveAll();
		m_Inited=false;
		this->Invalidate();
	}

	void SetTitleText(const char *text)
	{
		strcpy(m_Title,text);
		this->Invalidate();
	}

	void SetMaxPoint(int n)
	{
		m_MaxPoint=n%2 == 0 ? n : n+1; //偶数
	}

private:
	double_point m_Max;
	double_point m_Min;
	bool m_Inited;
	CArray <double_point,double_point> m_Items;
	CBitmap m_bk;
	CDC m_memDC;
	void PaintChart(CPaintDC * const dest);

	CBrush m_bs;
	CPen m_pen;
	CFont m_LableFont;

	int AdjustNumWidth( CDC * const dest,int len,int &height,int &agvWidth);

	char m_Title[100]; //title text

	void CompressArray(void);

	int m_MaxPoint; //最大显示点数 为0则无限制

	char m_XLableFormat[50]; // %0.2f
	char m_YLableFormat[50]; // %d:%d:%d  hh:mm:ss

	// format 0 as number ,1 as time hh:mm:ss ,2 as date year:month:day ,3 datetime year:month:day h:m:s
	short m_YFormat;
	short m_XFormat; 

	/*
	 *  x_or_y 表示x轴或者y轴 0=x,1=y
	 */
	void GetLableText(char *Out,double value ,int x_or_y);

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CArray <double_point,double_point> & GetItems(void)
	{
		return m_Items;
	}
};


