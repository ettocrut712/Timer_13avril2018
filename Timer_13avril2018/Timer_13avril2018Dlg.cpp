
// Timer_13avril2018Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Timer_13avril2018.h"
#include "Timer_13avril2018Dlg.h"
#include "afxdialogex.h"
#include "Etoile.h"
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



CTimer_13avril2018Dlg::CTimer_13avril2018Dlg(CWnd* pParent)
	: CDialogEx(IDD_TIMER_13AVRIL2018_DIALOG, pParent)
	, m_sCount(_T(""))
	,bottom(0)
	,left (0)
	,m_iOldNombreEtoile(0)
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
	, m_multi_lien(FALSE)
	, m_str_right(_T(""))
	, m_str_bottom(_T(""))
	, m_largeur(_T(""))
	, m_hauteur(_T(""))
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
	DDV_MinMaxInt(pDX, m_iInterval, 10, 10000);
	DDX_Text(pDX, IDC_ENOMBRE_ECHO, m_iNombreEcho);
	DDX_Text(pDX, IDC_ENOMBRE_ETOILE, m_iNombreEtoile);
	DDV_MinMaxInt(pDX, m_iNombreEtoile, 1, 100);
	DDX_Check(pDX, IDC_CHECK_MULTI_LIEN, m_multi_lien);
	DDX_Text(pDX, IDC_EDIT_RIGHT, m_str_right);
	DDX_Text(pDX, IDC_EDIT_BOTTOM, m_str_bottom);
	//DDX_Text(pDX, IDC_largeur, m_largeur);
	//DDX_Text(pDX, IDC_hauteur, m_hauteur);
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

	
	CRect rect;
	this->GetClientRect(rect);
	m_str_bottom.Format(_T("%d"), rect.bottom);
	oldBottom = rect.bottom;  //utilise pour verifier si les dimensions de la fenetre ont change

	m_str_right.Format(_T("%d"), rect.right);
	oldRight = rect.right;	//utilise pour verifier si les dimensions de la fenetre ont change

	

	//m_paintDlg.ShowWindow(SW_SHOW);
	
	bottom = 0.9*rect.bottom;
	
	
	left = 0.2* rect.right;
	
	right = 0.9* rect.right;
	

	top = 0.1*rect.bottom;

	CPaintDC dc(this); // device context for painting




	m_iInterval = 80;

	m_1_posX = (left + right) / 2 + m_1_speedX;
	m_1_posY = (top + bottom) / 2 + m_1_speedY;

	m_2_posX = (left + right) / 2 + m_2_speedX;
	m_2_posY = (top + bottom) / 2 + m_2_speedY;

	m_1_speedX = 5;
	m_1_speedY = 6;
	m_2_speedX = 7;
	m_2_speedY = 8;


	m_iNombreEtoile = 2;
	m_iNombreEcho = 1;
	
	UpdateData(FALSE);

	for (int id = 0; id < m_iNombreEtoile; id++)
	{

		m_starArray[id] = new CEtoile;
		m_starArray[id]->m_iID = id;

		m_starArray[id]->InitEcho(m_iNombreEcho);

		m_starArray[id]->InitPosition(m_1_posX, m_1_posY);

		m_1_speedX = (rand() % 10 + 1);
		m_1_speedY = (rand() % 10 + 1);

		m_starArray[id]->SetVitesse(m_1_speedX, m_1_speedY);

		m_starArray[id]->SetLimites(right, bottom, left, top);



	};

	m_multi_lien = FALSE;
	m_pointeur_echo = 0;  // pointe vers la premiere case du vecteur pour l'echo actif initialement.

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

	CPen crayon[10];

	crayon[0].CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	crayon[1].CreatePen(PS_SOLID, 1, RGB(25, 25, 0));
	crayon[2].CreatePen(PS_SOLID, 1, RGB(50, 50, 25));
	crayon[3].CreatePen(PS_SOLID, 1, RGB(50, 75, 50));
	crayon[4].CreatePen(PS_SOLID, 1, RGB(125, 100, 50));
	crayon[5].CreatePen(PS_SOLID, 1, RGB(125, 100, 75));
	crayon[6].CreatePen(PS_SOLID, 1, RGB(100, 155, 155));
	crayon[7].CreatePen(PS_SOLID, 1, RGB(180, 180, 100));
	crayon[8].CreatePen(PS_SOLID, 1, RGB(205, 180, 205));
	crayon[9].CreatePen(PS_SOLID, 1, RGB(230, 180, 230));
	







	crayon_rouge.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));  // rouge
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

		int i, echoNum = 0;
		int pointeurCrayon = 0;
		int pointeurEcho = 0;

		dc.SelectObject(crayon_rouge);  // dessine le cadre rouge

		dc.MoveTo(left, top);

		dc.LineTo(right, top);
		dc.LineTo(right, bottom);
		dc.LineTo(left, bottom);
		dc.LineTo(left, top);




		bool boucle_terminee = false;
		
		m_PenPointer++;

		if (m_PenPointer > 9) m_PenPointer = 0;

		pointeurCrayon = 0 ;

		for (echoNum = 0; echoNum < m_iNombreEcho; echoNum++)
		{

			
			if (echoNum <= (m_pointeur_echo-1))    //m_pointer_echo pointe vers le prochain echo. Pour l'echo actif (echo zéro), il faut soustraire "1".
			{
				
				pointeurCrayon = (m_pointeur_echo-1) - echoNum;
			}

			else
			{
				pointeurCrayon = m_iNombreEcho - (echoNum - (m_pointeur_echo-1));  // m_iNombreEcho limité à 9 (9 quand calculé à partir de zéro) est le nombre max de couleur pour le moment.

			};

			if (pointeurCrayon < 9) 
			{
				dc.SelectObject(crayon[pointeurCrayon]);
			}
			else
			{
				pointeurCrayon = 0;
				dc.SelectObject(crayon[pointeurCrayon]);
			};

			//if(m_pointeur_echo == echoNum) dc.SelectObject(crayon_rouge);

			

			

			for (int id = 0; id < (m_iNombreEtoile - 1); id++)
			{

				m_Lignes[1].point_1 = m_starArray[id]->m_positionX[echoNum];  
				m_Lignes[1].point_2 = m_starArray[id]->m_positionY[echoNum];

				dc.MoveTo(m_Lignes[1].point_1, m_Lignes[1].point_2);

				if (m_multi_lien)
				{
					for (int id2 = id; id2 < m_iNombreEtoile; id2++)
					{
						
						m_Lignes[1].point_3 = m_starArray[id2]->m_positionX[echoNum];
						m_Lignes[1].point_4 = m_starArray[id2]->m_positionY[echoNum];

						dc.MoveTo(m_Lignes[1].point_1, m_Lignes[1].point_2);

						dc.LineTo(m_Lignes[1].point_3, m_Lignes[1].point_4);
					};
				}
				else
				{
					m_Lignes[1].point_3 = m_starArray[id + 1]->m_positionX[echoNum];
					m_Lignes[1].point_4 = m_starArray[id + 1]->m_positionY[echoNum];
					dc.LineTo(m_Lignes[1].point_3, m_Lignes[1].point_4);


				};
			};

		};
		
	CDialogEx::OnPaint();
	};
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

	
	int posX, posY, Vx, Vy;
	int oldEchoNombre;

	oldEchoNombre = m_iNombreEcho;			// sauvegarde vieille valeur du nombre d'Echo...

	srand(time(NULL));

	

	UpdateData(TRUE);						// lit les parametres du dialogue.

	
	
	if (m_iNombreEcho > 19) m_iNombreEcho = 19;
	if (m_iNombreEtoile > 99) m_iNombreEtoile = 99;

	if (m_iNombreEcho != oldEchoNombre)
	{

		for (int id = 0; id < m_iNombreEtoile; id++)
		{
			m_starArray[id]->InitEcho(m_iNombreEcho);

			
		};

	};
	


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

	

	//UpdateData(TRUE);

	
}

//test
void CTimer_13avril2018Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	RECT rectToRedraw;
	//WINDOWPLACEMENT winPlace;
	CClientDC dc(this);
	CRect rect;

	bool bErase = TRUE;

	m_iCount++;

	int	oldEcho = m_iNombreEcho;

	m_sCount.Format(_T("%d"), m_iCount);

	//this->GetWindowPlacement(&winPlace);


	
	this->GetClientRect(rect);



	m_str_bottom.Format(_T("%d"), rect.bottom);
	m_str_right.Format(_T("%d"), rect.right);

	if (rect.bottom != oldBottom || rect.right != oldRight)
	{
		rectToRedraw.bottom = rect.bottom;
		rectToRedraw.right = rect.right;
		rectToRedraw.left = rect.left;
		rectToRedraw.top = rect.top;

		bottom = 0.9 * rect.bottom;
		left = 0.2 * rect.right;
		right = 0.9 * rect.right;
		top = 0.1 * rect.bottom;

		oldBottom = rect.bottom;
		oldRight = rect.right;

		for (int id = 0; id < m_iNombreEtoile; id++)
		{

			m_starArray[id]->SetLimites(right, bottom, left, top);



		};
	}
	else {
	
		rectToRedraw.bottom = bottom;
		rectToRedraw.right = right;
		rectToRedraw.left = left;
		rectToRedraw.top = top;
	
	};

	UpdateData(FALSE);
	UpdateData(TRUE);

	

	for (int id = 0; id < m_iNombreEtoile; id++)
	{

		m_starArray[id]->CalculePosition(m_pointeur_echo);

	};
	
	m_pointeur_echo++;
	if (m_pointeur_echo >= m_iNombreEcho) m_pointeur_echo = 0;


	
	/*rectToRedraw.bottom = bottom;
	rectToRedraw.right = right;
	rectToRedraw.left = left;
	rectToRedraw.top = top;*/

	InvalidateRect(&rectToRedraw, bErase);

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

	int oldEcho = m_iNombreEcho;
	
	UpdateData(TRUE);

	if (m_iNombreEcho > 19) m_iNombreEcho = 19;

	if (oldEcho != m_iNombreEcho)
	{
		for (int id = 0; id < m_iNombreEtoile; id++)
		{

			m_starArray[id]->InitEcho(m_iNombreEcho);


		};

	};

}


void CTimer_13avril2018Dlg::OnEnChangeEnombreEtoile()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	int posX, posY, Vx, Vy;

	m_iOldNombreEtoile = m_iNombreEtoile;

	UpdateData(TRUE);

	if (m_iNombreEtoile > 99) m_iNombreEtoile = 99;

	if (m_iNombreEtoile > m_iOldNombreEtoile)
	{
		for (int id = m_iOldNombreEtoile; id < m_iNombreEtoile; id++)
		{

			m_starArray[id] = new CEtoile;
			m_starArray[id]->m_iID = id;

			m_starArray[id]->InitEcho(m_iNombreEcho);

			posX = (left + right) / 2;
			posY = (top + bottom) / 2;

			m_starArray[id]->InitPosition(posX, posY);

			Vx = (rand() % 10 + 1);
			Vy = (rand() % 10 + 1);

			m_starArray[id]->SetVitesse(Vx, Vy);

			m_starArray[id]->SetLimites(right, bottom, left, top);



		};

		
	};

	if (m_iNombreEtoile < m_iOldNombreEtoile)
	{
		for (int id = (m_iOldNombreEtoile - 1); id > (m_iNombreEtoile - 1); id--)
		{
			delete m_starArray[id];


		};

		
	};
	
}
