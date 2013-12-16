#include "stdafx.h"
#include <time.h>
#include <sys/timeb.h>
#include "testJZ.h"
#include "testJZDlg.h"

#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
#pragma comment(lib, "API_BH.LIB")

CTestJZDlg::CTestJZDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestJZDlg::IDD, pParent)
{
	m_nMidPort = 28946;
	m_strZqdm = _T("000001");
	m_strGddm = _T("0000000001");
	m_dbWtjg = _T("6.20");
	m_nWtsl = _T("100");
	m_strGydm = _T("9999");
	m_strGymm = _T("888888");
	m_strJysdm = _T("0");
	m_strZjzh = _T("000000000001");
	m_nWtNum = 1000;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestJZDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_IPADDRESS1, m_midAddr);
	DDX_Text(pDX, IDC_EDIT2, m_nMidPort);
	DDX_Text(pDX, IDC_EDIT3, m_strZqdm);
	DDV_MaxChars(pDX, m_strZqdm, 6);
	DDX_Text(pDX, IDC_EDIT4, m_strGddm);
	DDV_MaxChars(pDX, m_strGddm, 10);
	DDX_Text(pDX, IDC_EDIT5, m_dbWtjg);
	DDX_Text(pDX, IDC_EDIT6, m_nWtsl);
	DDX_Text(pDX, IDC_EDIT7, m_strGydm);
	DDV_MaxChars(pDX, m_strGydm, 10);
	DDX_Text(pDX, IDC_EDIT8, m_strGymm);
	DDV_MaxChars(pDX, m_strGymm, 10);
	DDX_Text(pDX, IDC_EDIT9, m_strJysdm);	
	DDX_Text(pDX, IDC_EDIT10, m_strZjzh);
	DDX_Text(pDX, IDC_WTNUM, m_nWtNum);
}

BEGIN_MESSAGE_MAP(CTestJZDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnLogin)
	ON_BN_CLICKED(IDC_BUTTON2, OnSbmr)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

BOOL CTestJZDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
    KDAPI_OEMInit("API_","金证高科\1",0);

	if (!KDAPI_InitSystem_MT(20, 20))
	{
		MessageBox("初始化金证API失败!", NULL, MB_OK|MB_ICONERROR);
		return FALSE;
	}
	
	m_midAddr.SetAddress(192, 168, 40, 17);
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestJZDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


void CTestJZDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


HCURSOR CTestJZDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestJZDlg::OnLogin() 
{
	UpdateData(TRUE);

	DWORD	dwMidAddr = 0;
	char	szMidAddr[31] = {0};
	int		ret;
	CString	strError;

	m_midAddr.GetAddress(dwMidAddr);

	strcpy(m_servAddr[0].Node, "TCP");
	_snprintf(m_servAddr[0].Address, sizeof(m_servAddr[0].Address), "%03d%03d%03d%03d", 
		(dwMidAddr&0xff000000)>>8*3, (dwMidAddr&0x00ff0000)>>8*2, (dwMidAddr&0x0000ff00)>>8, (dwMidAddr&0x000000ff));
	m_servAddr[0].Socket = m_nMidPort;

	
	ret = KDAPI_Connect(m_servAddr, (LPSTR)(LPCTSTR)m_strGydm, (LPSTR)(LPCTSTR)m_strGymm);
		if (ret != 0)
		{
			switch( ret ) 
			{
			case -1: strError = "没有调用InitSystem!"; break;
			case -2: strError = "处理机连接柜台中间件失败!"; break;
			case -3: strError = "OEM未授权!"; break;
			case -4: strError = "请求失败（应当取回一个包），数据发送错误!"; break;
			case -7: strError = "调用reqOEM请求出现其他错误!";break;
			default: 
				strError.Format("未知错误:%-d!", ret); 
				break;
			}
			MessageBox(strError, NULL, MB_OK|MB_ICONERROR);
			return;
		}
		MessageBox("登陆成功!", NULL, MB_OK|MB_ICONINFORMATION);	
}

void CTestJZDlg::OnSbmr() 
{
	UpdateData();
	//委托确认
	tagREQUEST g_Query;
	tagRESULT g_Result;
	char sTemp[120];
	
	memset(&g_Query,0,sizeof(g_Query));
	g_Query.head.length = sizeof(g_Query.wtqr);
	g_Query.head.serio = 15;
	g_Query.head.crc = 0;
	g_Query.head.status = 0;
	g_Query.head.function = funcWTQR;
	g_Query.head.czfs = 2;
	
	g_Query.wtqr.JYSDM= m_strJysdm[0];
	sprintf(g_Query.wtqr.GDDM,m_strGddm);
	g_Query.wtqr.MMLB='B';
	sprintf(g_Query.wtqr.ZQDM, m_strZqdm);
	strcpy(g_Query.wtqr.WTJG,m_dbWtjg);
	strcpy(g_Query.wtqr.WTSL,m_nWtsl);
	strcpy(g_Query.wtqr.ReqSrcInfo,"");
	
	struct _timeb tstruct;
	_ftime(&tstruct);
	
	for(int i=0; i<(int)m_nWtNum; i++)
	{		
		int iRet = KDAPI_Request(g_Query);
		if(iRet>=0)
		{
			int iReturn = KDAPI_Answer(g_Result);
			if (iReturn > 0)
			{
				sprintf(sTemp,"委托确认 成功! 合同序号：%s",g_Result.wtqr.HTXH);
			}
		}
		else
		{
			int iReturn = KDAPI_Answer(g_Result);
			AfxMessageBox(g_Result.ErrMsg.ErrMsg);
			return;
		}	
	}
	
	struct _timeb tstruct1;
	long  millitm;
	_ftime(&tstruct1);
	millitm = (tstruct1.time - tstruct.time)*1000 + (tstruct1.millitm - tstruct.millitm);
	
	sprintf(sTemp,"委托确认成功, 共耗时:%d毫秒.",millitm);
	AfxMessageBox(sTemp);
}

BOOL CTestJZDlg::DestroyWindow() 
{
	if (KDAPI_GetConnect() == 0)
		KDAPI_Disconnect();
	
	return CDialog::DestroyWindow();
}
