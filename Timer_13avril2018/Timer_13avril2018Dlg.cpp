
// Timer_13avril2018Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Timer_13avril2018.h"
#include "Timer_13avril2018Dlg.h"
#include "afxdialogex.h"
//test
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About




class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTimer_13avril2018Dlg dialog



CTimer_13avril2018Dlg::CTimer_13avril2018Dlg(CWnd* pParent )
	: CDialogEx(IDD_TIMER_13AVRIL2018_DIALOG, pParent)
	, m_sCount(_T(""))

	, m_iInterval(0)
	, m_iCount(0)
	, m_1_posX(0)
	, m_1_posY(0)
	, m_2_posX(0)
	, m_2_posY(0)
	, m_1_speedX(0)
	, m_1_speedY(0)
	, m_2_speedX(0)
	, m_2_speedY(0)
	, m_iNombreEcho(0)
	, m_iNombreEtoile(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimer_13avril2018Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STARTBUTTON, m_cStartCount);
	DDX_Control(pDX, IDC_STOPBUTTON, m_cStopCount);


	DDX_Text(pDX, IDC_STATICCOUNT, m_sCount);

	DDX_Text(pDX, IDC_EINTERVAL, m_iInterval);
	DDV_MinMaxInt(pDX, m_iInterval, 0, 10000);
	DDX_Text(pDX, IDC_ENOMBRE_ECHO, m_iNombreEcho);
	DDX_Text(pDX, IDC_ENOMBRE_ETOILE, m_iNombreEtoile);
	DDV_MinMaxInt(pDX, m_iNombreEtoile, 1, 10);
}

BEGIN_MESSAGE_MAP(CTimer_13avril2018Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTBUTTON, &CTimer_13avril2018Dlg::OnBnClickedStartbutton)
	ON_BN_CLICKED(IDC_STOPBUTTON, &CTimer_13avril2018Dlg::OnBnClickedStopbutton)
	ON_EN_CHANGE(IDC_EINTERVAL, &CTimer_13avril2018Dlg::OnChangeEinterval)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_ENOMBRE_ECHO, &CTimer_13avril2018Dlg::OnEnChangeEnombreEcho)
	ON_EN_CHANGE(IDC_ENOMBRE_ETOILE, &CTimer_13avril2018Dlg::OnEnChangeEnombreEtoile)
END_MESSAGE_MAP()


// CTimer_13avril2018Dlg message handlers

BOOL CTimer_13avril2018Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	
	

	//m_paintDlg.ShowWindow(SW_SHOW);
	


	m_iInterval = 20;

	m_1_posX = (left + right) / 2 + m_1_speedX;
	m_1_posY = (top + bottom) / 2 + m_1_speedY;

	m_2_posX = (left + right) / 2 + m_2_speedX;
	m_2_posY = (top + bottom) / 2 + m_2_speedY;

	m_1_speedX = 5;
	m_1_speedY = 6;
	m_2_speedX = 7;
	m_2_speedY = 8;


	// nouveau code qui fonctionne avec constellation et CEtoile
	m_iNombreEcho = 1;
	m_iNombreEtoile = 2;

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimer_13avril2018Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTimer_13avril2018Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting


	COLORREF couleur;
	couleur = (100, 255, 0);
	
	
	CPen crayon_rouge, crayon_blanc;
	crayon_rouge.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));  // noir
	crayon_blanc.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));  //blanc



	if (IsIconic())
	{
		//CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon



		
		
	}
	else
	{

		int i = 0;
		dc.SelectObject(crayon_rouge);
		bool boucle_terminee = false;

		i= m_pointeur_ligne;

		while (!boucle_terminee)
		{
			
			dc.MoveTo(m_Lignes[i].point_1, m_Lignes[i].point_2);
			dc.LineTo(m_Lignes[i].point_3, m_Lignes[i].point_4);

			i = i + 1;
			
			if (i > m_iNombreEcho)
				i = 0;

			if (i == m_pointeur_ligne)
				boucle_terminee = true;
			
		

		};
		
		

		
		
		
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTimer_13avril2018Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTimer_13avril2018Dlg::OnBnClickedStartbutton()
{
	// TODO: Add your control notification handler code here

	bottom = 862;
	left = 220;
	right = 1530;
	top = 95;
	
	
	UpdateData(TRUE);
	m_iCount = 0;
	
	m_sCount.Format(_T("%d"), m_iCount);
	m_1_posX = (left+right)/2 + m_1_speedX;
	m_1_posY = (top + bottom)/2 +m_1_speedY;

	m_2_posX = (left+right)/2 +m_2_speedX;
	m_2_posY = (top+bottom)/2 + m_2_speedY;

	UpdateData(FALSE);

	SetTimer(ID_COUNT_TIMER, m_iInterval, NULL);
}


void CTimer_13avril2018Dlg::OnBnClickedStopbutton()
{
	// TODO: Add your control notification handler code here

	KillTimer(ID_COUNT_TIMER);
}


void CTimer_13avril2018Dlg::OnChangeEinterval()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	

	UpdateData(TRUE);
}

//test
void CTimer_13avril2018Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	m_iCount++;

	

	m_sCount.Format(_T("%d"), m_iCount);

	CClientDC dc(this);
	bool bErase = TRUE;
	
	RECT lpRect;

	lpRect.bottom = bottom;
	lpRect.left = left;
	lpRect.right = right;
	lpRect.top = top;

	

	


	m_1_posX = m_1_posX + m_1_speedX;
	m_1_posY = m_1_posY + m_1_speedY;

	m_2_posX = m_2_posX + m_2_speedX;
	m_2_posY = m_2_posY + m_2_speedY;

	if (m_1_posX > right )
	{
		m_1_speedX = -1 *(rand()%10+1);
		if (m_1_speedX == 0) m_1_speedX = -1;
		
	};

	if ( m_1_posX < left)
	{
		m_1_speedX = rand() % 10 + 1;
		if (m_1_speedX == 0) m_1_speedX = 1;

	};


	if (m_1_posY > bottom )
	{
		m_1_speedY = -1 * (rand() % 10 + 1);
		if (m_1_speedY == 0) m_1_speedY = -1;
	};

	if ( m_1_posY < top)
	{
		m_1_speedY = rand() % 10 + 1;
		if (m_1_speedY == 0) m_1_speedY = 1;
	};

	if (m_2_posX > right ) 
	{
		m_2_speedX = -1 * (rand() % 10 + 1);
		if (m_2_speedX == 0) m_2_speedX = -1;
	};

	if ( m_2_posX < left)
	{
		m_2_speedX = rand() % 10 + 1;
		if (m_2_speedX == 0) m_2_speedX = 1;
	};

	if (m_2_posY > bottom ) 
	{
		m_2_speedY = -1 * (rand() % 10 + 1);
		if (m_2_speedY == 0) m_2_speedY = -1;
	};

	if ( m_2_posY < top)
	{
		m_2_speedY = rand() % 10 + 1;
		if (m_2_speedY == 0) m_2_speedY = 1;
	};

	m_Lignes[m_pointeur_ligne].point_1 = m_1_posX;
	m_Lignes[m_pointeur_ligne].point_2 = m_1_posY;
	m_Lignes[m_pointeur_ligne].point_3 = m_2_posX;
	m_Lignes[m_pointeur_ligne].point_4 = m_2_posY;

	m_pointeur_ligne++;
	   
	if (m_pointeur_ligne > m_iNombreEcho)
		m_pointeur_ligne = 0;

	InvalidateRect(&lpRect, bErase);

	UpdateData(FALSE);


	CDialogEx::OnTimer(nIDEvent);
}


void CTimer_13avril2018Dlg::OnEnChangeEnombreEcho()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);
	


}


void CTimer_13avril2018Dlg::OnEnChangeEnombreEtoile()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	UpdateData(TRUE);

	
}
