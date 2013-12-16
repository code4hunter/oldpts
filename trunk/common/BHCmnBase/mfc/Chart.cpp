/*
 * CChart  Version 1.0
 *
 * Author:  CodeHunter
 *          CodeHunter@msn.com
 *          
 * Modify:   
 * 
 *
 * This software is released into the public domain.
 * You are free to use it in any way you like.
 *
 * This software is provided "as is" with no expressed
 * or implied warranty.  I accept no liability for any
 * damage or loss of business that this software may cause.
 *
 */

#include "stdafx.h"
#include "Chart.h"
#include <math.h>
// CChart

const CTime TFMT(2000,12,30,10,50,50);

IMPLEMENT_DYNAMIC(CChart, CStatic)
CChart::CChart()
{
	m_Inited=false;
	m_bs.CreateSolidBrush(RGB(150,100,22));
	m_pen.CreatePen(PS_SOLID,1,RGB(255,255,0));
	m_LableFont.CreateFont(
		12,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		DEFAULT_CHARSET,           // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"宋体");                   // lpszFacename

	strcpy(m_Title,"CodeHunter Chart");

	m_MaxPoint=0;
	strcpy(m_YLableFormat,"%0.2f");
	strcpy(m_XLableFormat,"%d:%d:%d");

	m_YFormat=0;
	m_XFormat=1; //time
}

CChart::~CChart()
{
	m_Items.RemoveAll();
}

BEGIN_MESSAGE_MAP(CChart, CStatic)
	//{{AFX_MSG_MAP(CXColorStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CChart 消息处理程序

void CChart::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	PaintChart(&dc);
}

void CChart::PaintChart(CPaintDC * const dest)
{
	RECT rc;
	CDC &dc=m_memDC;
	CPen *oldpen=NULL;
	CFont *oldfont=NULL;
	CBrush *oldbsh =NULL;
	
	GetClientRect(&rc);

	if(dc.m_hDC==NULL)
	{
		m_bk.CreateCompatibleBitmap(dest,rc.right-rc.left,rc.bottom-rc.top);
		dc.CreateCompatibleDC(this->GetDC());
		dc.SelectObject(&m_bk);
	}

	oldbsh=dc.SelectObject(&m_bs);
	oldfont= dc.SelectObject(&m_LableFont);

	dc.SetTextAlign(TA_RIGHT);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(250,250,255));
	
	//draw frame
	dc.Rectangle(&rc);

	if(m_Inited)
	{
		//adjust
		int height=rc.bottom-rc.top;
		int width=rc.right-rc.left;

		double hv=m_Max.y - m_Min.y;
		double wv=m_Max.x - m_Min.x;

		if(hv!=0 && wv!=0)
		{
			int nitemcount=(int)m_Items.GetCount();
			int dy=20;
			int textht,textwd;
			int dx;
			char maxlentext[100];
			double_point dp;
			dp.x=0;
			dp.y=0;

			//Get lable width
			if(m_YFormat>0)
				GetLableText(maxlentext,(double)TFMT.GetTime(),1);	
			else
				GetLableText(maxlentext,fabs(m_Max.y)>fabs(m_Min.y) ? m_Max.y : m_Min.y,1);

			dx=AdjustNumWidth(&dc,(int)strlen(maxlentext),textht,textwd) + 20;
			dy=textht+20;	

			int x=dx;
			int y=height-dy;

			width-= 2*dx;
			height-=2*dy;

			//draw corrdinate
			CPen coorpen(PS_SOLID,2,RGB(132,0,0));
			oldpen = dc.SelectObject(&coorpen);
			dc.MoveTo(x,y);
			dc.LineTo(x,dy-1); //Dwaw Y Coordinate
			dc.MoveTo(x,dy);
			dc.LineTo(width+dx,dy);
			dc.LineTo(width+dx,y);
			dc.LineTo(x,y); //Dwaw X Coordinate
			dc.SelectObject(oldpen);

			//draw x grid and y lable
			LOGPEN pn;
			coorpen.GetLogPen(&pn);
			pn.lopnWidth.x=1;
			pn.lopnStyle=PS_DOT;
			coorpen.DeleteObject();
			coorpen.CreatePenIndirect(&pn);
			oldpen = dc.SelectObject(&coorpen);

			int linenum=textht==0 ? 0 : height/textht/2;
			double sep=linenum==0 ? 0 : hv/linenum; //draw ten grid
			double tmpv=m_Min.y;
			for(int i=0;i<linenum-1;i++)
			{
				tmpv+=sep;
				y=(int)((1-(tmpv-m_Min.y)/hv) * height)+dy;

				dc.MoveTo(dx,y);
				GetLableText(maxlentext,tmpv,1);
				//dc.SetTextColor(RGB(150,10,10));
				dc.TextOut(dx-5,y-textht/2,maxlentext);

				dc.LineTo(width+dx,y);	
			}

			//draw y grid and x lable

			if(m_XFormat>0)
				GetLableText(maxlentext,(double)TFMT.GetTime(),0);
			else
				GetLableText(maxlentext,fabs(m_Max.x)>fabs(m_Min.x) ? m_Max.x : m_Min.x,0);

			int n=(int)strlen(maxlentext);

			linenum=textwd==0 || n==0 ? 0 : width/(textwd*n+10);
			sep=linenum==0 ? 0 : wv/linenum; //draw ten grid
			tmpv=m_Min.x;
			for(int i=0;i<linenum-1;i++)
			{
				tmpv+=sep;
				x=dx+(int)((tmpv-m_Min.x)/wv * width);

				dc.MoveTo(x,height+dy);

				GetLableText(maxlentext,tmpv,0);

				n=(int)strlen(maxlentext);

				dc.TextOut(x+n*textwd/2,height+dy+5,maxlentext);

				dc.LineTo(x,dy);	
			}

			dc.SelectObject(oldpen);

			//draw line
			oldpen = dc.SelectObject(&m_pen);
			for(int i=0;i<nitemcount;i++)
			{
				dp=m_Items.ElementAt(i);
				x=dx+(int)((dp.x-m_Min.x)/wv * width);
				y=(int)((1-(dp.y-m_Min.y)/hv) * height)+dy;

				if(i==0) dc.MoveTo(x,y);
				else dc.LineTo(x,y);	
			}
			dc.SelectObject(oldpen);

			//draw last point text
			GetLableText(maxlentext,dp.y,1);
			dc.SetTextColor(RGB(255,255,255));
			dc.TextOut(x,y,maxlentext);

			//draw title
			x=(rc.right-textwd*(int)strlen(m_Title))/2;
			y=(dy-textht)/2;
			CRect trect(dx-1,y-2,width+dx+1,dy-8);
			CBrush tbs;
			tbs.CreateSolidBrush(RGB(132,0,0));
			dc.FillRect(&trect,&tbs);
			dc.SetTextAlign(TA_LEFT);
			dc.SetTextColor(RGB(255,255,255));
			dc.TextOut(x,y,m_Title,(int)strlen(m_Title));
		}
	}

	//flip
	dest->BitBlt(0,0,rc.right-rc.left,rc.bottom-rc.top,&dc,0,0,SRCCOPY);

	//restory soming
	dc.SelectObject(oldbsh);
	dc.SelectObject(oldfont);
}

void CChart::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	if(m_memDC.m_hDC!=NULL)
	{
		m_bk.DeleteObject();
		m_bk.CreateCompatibleBitmap(this->GetDC(),cx,cy);
		m_memDC.DeleteDC();
		m_memDC.CreateCompatibleDC(this->GetDC());
		m_memDC.SelectObject(&m_bk);
	}
	Invalidate();
}

void CChart::AddXY(double x,double y)
{
	if(y>-0.0001 && y<0.0001) return;

	double_point pt;

	if(m_Items.GetCount()>0)
	{
		pt=m_Items.ElementAt(m_Items.GetCount()-1);
		if(pt.x==x) return;
	}

	pt.x=x;
	pt.y=y;
	m_Items.Add(pt);

	//init max and min item
	if(! m_Inited)
	{		
		m_Max.x=x;
		m_Max.y=y;

		m_Min.x=x;
		m_Min.y=y;

		m_Inited=true;
	}
	else
	{
		//update max and min item
		if(m_Max.x<x) m_Max.x=x;
		if(m_Max.y<y) m_Max.y=y;

		if(m_Min.x>x) m_Min.x=x;
		if(m_Min.y>y) m_Min.y=y;

		//if(m_Max.x==m_Min.x) m_Min.x-=(m_Min.x/2);
		if(m_Max.y==m_Min.y) 
		{
			m_Min.y-=1;
			m_Max.y+=1;
		}

	}

	CompressArray();
}

void CChart::AddY(double y)
{
	double x;
	double_point pt;
	int n=(int)m_Items.GetCount();

	if(n>0)
	{
		pt=m_Items.ElementAt(n-1);
		x=++pt.x;
	}
	else
	{
		x=0;
	}

	AddXY(x,y);
}

/*
 * Function  AdjustNumWidth
 * 获取num的在指定DC上的输出宽度
 */
int CChart::AdjustNumWidth(CDC * const dest,int len, int &height,int &agvWidth)
{
	TEXTMETRIC tm;
	dest->GetTextMetrics(&tm);

	height=tm.tmHeight;
	agvWidth=tm.tmAveCharWidth;

	return tm.tmAveCharWidth*len;
}

/* Compress Array
 * When array size more than 100 ,it will be compressed to 50
 * To calculate the average of two close items, and swap two items for the average
 */
void CChart::CompressArray(void)
{
	int n=(int)m_Items.GetCount();
	if(n==m_MaxPoint)
	{
		double_point dp1,dp2;

		for(int i=n-1;i>=0;i-=2)
		{
			if(i-1>=0)
			{
				dp1=m_Items.ElementAt(i);
				dp2=m_Items.ElementAt(i-1);

				dp1.x=(dp1.x+dp2.x)/2;
				dp1.y=(dp1.y+dp2.y)/2;

				if(i==n-1)
				{
					m_Max.x=dp1.x;
					m_Max.y=dp1.y;
					m_Min.x=dp1.x;
					m_Min.y=dp1.y;
				}
				else
				{
					if(m_Max.x<dp1.x) m_Max.x=dp1.x;
					if(m_Max.y<dp1.y) m_Max.y=dp1.y;

					if(m_Min.x>dp1.x) m_Min.x=dp1.x;
					if(m_Min.y>dp1.y) m_Min.y=dp1.y;
				}
				m_Items.RemoveAt(i);
				m_Items.SetAt(i-1,dp1);
			}
			else break;
		}
	}
}

void CChart::GetLableText(char *Out,double value ,int x_or_y)
{
	char *buf = Out;	
	CTime t((__time64_t)value);

	if(x_or_y==0)
	{	
		switch (m_XFormat)
		{
		case 0:
			sprintf(buf,m_XLableFormat,value);
			break;

		case 1:
			sprintf(buf,m_XLableFormat,t.GetHour(),t.GetMinute(),t.GetSecond());
			break;

		case 2:
			sprintf(buf,m_XLableFormat,t.GetYear(),t.GetMonth(),t.GetDay());
			break;

		case 3:
			sprintf(buf,m_XLableFormat,t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
			break;
		}		
	}
	else if(x_or_y==1)
	{
		switch (m_YFormat)
		{
		case 0:
			sprintf(buf,m_YLableFormat,value);
			break;

		case 1:
			sprintf(buf,m_YLableFormat,t.GetHour(),t.GetMinute(),t.GetSecond());
			break;

		case 2:
			sprintf(buf,m_YLableFormat,t.GetYear(),t.GetMonth(),t.GetDay());
			break;

		case 3:
			sprintf(buf,m_YLableFormat,t.GetYear(),t.GetMonth(),t.GetDay(),t.GetHour(),t.GetMinute(),t.GetSecond());
			break;
		}		
	}
	else
		buf[0]='\0';
}