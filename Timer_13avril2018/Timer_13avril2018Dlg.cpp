
// Timer_13avril2018Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Timer_13avril2018.h"
#include "Timer_13avril2018Dlg.h"
#include "afxdialogex.h"
#include "Etoile.h"
#include <cstring>

#include <cstdlib>
#include <numeric>
#include <mutex>
#include <thread>
#include <vector>




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
	//, m_2_posX(0)
	//, m_2_posY(0)
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
	, m_distance_0_1(_T(""))
	, m_angle_0_1(_T(""))
	, m_angle_1_0(_T(""))
	, m_dessineCercle(FALSE)
	, m_dessineTriangle(FALSE)
	//, m_slider_D1(0)
	//, m_slider_D2(0)
	, m_3D_enable(FALSE)
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
	DDX_Text(pDX, IDC_DISTANCE, m_distance_0_1);
	DDX_Text(pDX, IDC_ANGLE_0_1, m_angle_0_1);
	//  DDX_Control(pDX, IDC_ANGLE_1_0, m_angle_1_0);
	DDX_Text(pDX, IDC_ANGLE_1_0, m_angle_1_0);
	DDX_Check(pDX, IDC_CHECK3, m_dessineCercle);
	DDX_Check(pDX, IDC_CHECK2, m_dessineTriangle);
	//  DDX_Slider(pDX, IDC_SLIDER1, m_slider_D1);
	//  DDV_MinMaxInt(pDX, m_slider_D1, 10, 200);
	//  DDX_Slider(pDX, IDC_SLIDER2, m_slider_D2);
	//  DDV_MinMaxInt(pDX, m_slider_D2, 0, 200);
	DDX_Check(pDX, IDC_CHECK4_3D, m_3D_enable);
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
	ON_WM_ERASEBKGND()
	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CTimer_13avril2018Dlg::OnCustomdrawSlider1)
	ON_BN_CLICKED(IDC_CHECK4_3D, &CTimer_13avril2018Dlg::OnBnClickedCheck43d)
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

	srand(time(NULL));

	//m_paintDlg.ShowWindow(SW_SHOW);
	
	bottom = 0.95*rect.bottom;
	
	
	left = 0.2* rect.right;
	
	right = 0.95* rect.right;
	

	top = 0.05*rect.bottom;


	//************************************ 3D
	front = bottom;
	back =  top;

	//************************************ 3D


	CPaintDC dc(this); // device context for painting




	m_iInterval = 40;

	m_1_posX = left +(rand() % (right-left));
	m_1_posY = top + (rand() % (bottom-top)); 
	m_1_posZ = back + (rand() % (front - back));

	

	m_iNombreEtoile = 3;
	m_iNombreEcho = 20;
	m_dessineTriangle = TRUE;
	
	UpdateData(FALSE);
	srand(time(NULL));

	for (int id = 0; id < m_iNombreEtoile; id++)
	{

		m_starArray[id] = new CEtoile;
		m_starArray[id]->m_iID = id;

		m_starArray[id]->InitEcho(m_iNombreEcho);

		m_1_posX = left + (rand() % (right - left)); 
		m_1_posY = top + (rand() % (bottom - top));
		m_1_posZ = back + (rand() % (front - back));

		m_starArray[id]->InitPosition(m_1_posX, m_1_posY, m_1_posZ);
		
		m_1_speedX = 5; 
		m_1_speedY = 5; 
		m_1_speedZ = 5;

		m_starArray[id]->SetVitesse(m_1_speedX, m_1_speedY, m_1_speedZ);

		m_starArray[id]->SetLimites(right, bottom, left, top, front, back);



	};

	m_multi_lien = FALSE;
	m_pointeur_echo = 20;  // pointe vers la premiere case du vecteur pour l'echo actif initialement.

	UpdateData(FALSE);

	m_running = false;


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
	
	
	CPen crayon_rouge, crayon_blanc, crayon_noir, crayon_orange, crayon_vert, crayon_bleu, crayon_jaune;
	crayon_rouge.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));  // rouge
	crayon_blanc.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));  //blanc
	crayon_noir.CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); 
	crayon_vert.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	crayon_bleu.CreatePen(PS_SOLID, 1, RGB(0, 0, 255)); 
	crayon_orange.CreatePen(PS_SOLID, 1, RGB(255, 128, 128));
	crayon_jaune.CreatePen(PS_SOLID, 1, RGB(255, 180, 180));
	CRect rect;
	GetClientRect(&rect);


	//CDC MemDC;
	//CBitmap MemBitmap;
	//pDC = this->GetDC();

/*	MemDC.CreateCompatibleDC(dc);
	MemBitmap.CreateCompatibleBitmap(&pDC, rect.right, rect.bottom);

	CBitmap* pOldBitmap = (CBitmap*)MemDC.SelectObject(&MemBitmap);

	//MemDC.FillSolidRect(0, 0, rect.right, rect.bottom, RGB(255, 255, 255));*/


	if (IsIconic())
	{
		//CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);  ///SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height()- cyIcon + 1) / 2;

		// Draw the icon


	}
	else
	{

		CString le_string;
		CRect le_rectangle;

		int echoNum, x, y, id, diviseur = 0;
		int pointeurCrayon = 0;
		int pointeurEcho = 0;
		
		int longueur_pointe = 50;
													// longueur de la fleche qui pointe la direction de deplacement.
		dc.SelectObject(crayon_noir);				// dessine le cadre    dc.SelectObject(crayon_noir);
		int signX = 1;
		int signY = 1;
		
		dc.MoveTo(left, bottom);
		dc.LineTo(right, bottom);
		dc.LineTo(right, top);
		dc.LineTo(left, top);
		dc.LineTo(left, bottom);

		bool boucle_terminee = false;
	
		int pointeur;

		for ( id = 0; id < (m_iNombreEtoile); id++)
		{
			pointeur = m_pointeur_echo;
			m_starArray[id]->Rotation();
			m_starArray[id]->Translation();
			
			//***********************************
			dc.SelectObject(crayon_noir);


			diviseur = 2;

			if (m_multi_lien)
			{
				diviseur = 4 * m_starArray[id]->m_niveau_correction;
				if (diviseur == 0) diviseur = 2;
			};

			
			x = m_starArray[id]->m_positionX[pointeur];
			y = bottom + top - m_starArray[id]->m_positionY[pointeur];

			switch (m_starArray[id]->m_niveau_correction)
			{
			case 0:dc.SelectObject(crayon_bleu);
				break;
			case 1:dc.SelectObject(crayon_vert);
				break;
			case 2:dc.SelectObject(crayon_orange);
				break;
			case 4:dc.SelectObject(crayon_orange);
				break;
			case 5:dc.SelectObject(crayon_rouge);
				break;
			default: dc.SelectObject(crayon_noir);

			};

			if (m_dessineCercle)
			{
				dc.Ellipse(x - m_distanceSecuritaire / diviseur, y - m_distanceSecuritaire / diviseur, x + m_distanceSecuritaire / diviseur, y + m_distanceSecuritaire / diviseur);
			};

			if (m_multi_lien)			// si multi_lien = true, alors dessine numero.
			{
				le_rectangle.SetRect(x - 10, y - 10, x + 10, y + 10);
				le_string.Format(_T("%2d"), id);
				//dc.SelectObject(crayon_noir);
				dc.DrawText(le_string, le_rectangle, DT_CENTER);
			};

			if (m_dessineTriangle)
				//Dessine la tete de l'objet (triangle avec rotation et translation)
			{
				dc.MoveTo(m_starArray[id]->m_tete_coordonnees[0].x, bottom + top - m_starArray[id]->m_tete_coordonnees[0].y);
				for (int a = 0; a < 3; a++)
				{
					dc.LineTo(m_starArray[id]->m_tete_coordonnees[a].x, bottom + top - m_starArray[id]->m_tete_coordonnees[a].y);

				};

				dc.LineTo(m_starArray[id]->m_tete_coordonnees[0].x, bottom + top - m_starArray[id]->m_tete_coordonnees[0].y);
			};
			
			//***************************************


			for (echoNum = 0; echoNum < m_iNombreEcho - 1; echoNum++)
			{

				


				if (m_starArray[id]->m_distance_devant < 50)
				{
					dc.SelectObject(crayon_rouge);
				};

				if (m_starArray[id]->m_distance_devant > 49)
				{
					dc.SelectObject(crayon_noir);
				};

				

				if (echoNum == 0)
				{
					


					pointeur++;
					if (pointeur > m_iNombreEcho - 1) pointeur = 0;


					x = m_starArray[id]->m_positionX[pointeur];
					y = bottom + top - m_starArray[id]->m_positionY[pointeur];
					dc.MoveTo(x, y);
					pointeur++;
					if (pointeur > m_iNombreEcho - 1) pointeur = 0;
				}
				else
				{

					int x = m_starArray[id]->m_positionX[pointeur];
					int y = bottom + top - m_starArray[id]->m_positionY[pointeur];
					dc.LineTo(x, y);
					pointeur++;
					if (pointeur > m_iNombreEcho - 1) pointeur = 0;


				};

				
			};

			
		};
		//dc.BitBlt(0, 0, rect.right, rect.bottom, &MemDC, 0, 0, SRCCOPY);
		//MemDC.SelectObject(pOldBitmap);

	//	ReleaseDC(&dc);
	//	ReleaseDC(&MemDC);


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

	
	
	int oldEchoNombre;

	oldEchoNombre = m_iNombreEcho;			// sauvegarde vieille valeur du nombre d'Echo...

	srand(time(NULL));

	// modification: DEBUT
	m_running = TRUE;

	// modification: FIN

	UpdateData(TRUE);						// lit les parametres du dialogue.

	
	
	if (m_iNombreEcho > 50) m_iNombreEcho = 50;
	if (m_iNombreEtoile > 99) m_iNombreEtoile = 99;

	if (m_iNombreEcho != oldEchoNombre)
	{

		for (int id = 0; id < m_iNombreEtoile; id++)
		{
			m_starArray[id]->InitEcho(m_iNombreEcho);
			
			
		};

	};
	


	m_iCount = 0;
	m_iCountLeader = 0;
	
	m_sCount.Format(_T("%d"), m_iCount);
	
	UpdateData(FALSE);

	SetTimer(ID_COUNT_TIMER, m_iInterval, NULL); 

}


void CTimer_13avril2018Dlg::OnBnClickedStopbutton()
{
	// TODO: Add your control notification handler code here

	// modification: DEBUT

	KillTimer(ID_COUNT_TIMER);

//	m_running = FALSE;

	
	// modification: FIN

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

void CTimer_13avril2018Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	RECT rectToRedraw;
	//WINDOWPLACEMENT winPlace;
	CClientDC dc(this);
	CRect rect;

	bool bErase = TRUE;

	m_iCount++;
	float temp1, temp2, correction;
	int	oldEcho = m_iNombreEcho;

	m_sCount.Format(_T("%d"), m_iCount);
	//UpdateData(FALSE);

	this->GetClientRect(rect);

	m_str_bottom.Format(_T("%d"), rect.bottom);				// m_str_...: affiche les dimensions dans le dialogue.
	m_str_right.Format(_T("%d"), rect.right);				// m_str_...: affiche les dimensions dans le dialogue.

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

			m_starArray[id]->SetLimites(right, bottom, left, top, front, back);



		};
	}
	else {

		rectToRedraw.bottom = bottom;
		rectToRedraw.right = right;
		rectToRedraw.left = left;
		rectToRedraw.top = top;

	};


	UpdateData(TRUE);

	m_str_bottom.Format(_T("%d"), rect.bottom);				// m_str_...: affiche les dimensions dans le dialogue.
	m_str_right.Format(_T("%d"), rect.right);				// m_str_...: affiche les dimensions dans le dialogue.

	UpdateData(FALSE);

	m_pointeur_echo++;  //  indique la position active pour les nouvelles coordonnees...
	if (m_pointeur_echo >= m_iNombreEcho) m_pointeur_echo = 0;

	for (int id = 0; id < m_iNombreEtoile; id++)
	{

		m_starArray[id]->Deplace(m_pointeur_echo);
		m_starArray[id]->VerifieLimites(m_pointeur_echo);

	};


	InitDistances();


	/*******************************************/
	int debut = 0, fin = m_iNombreEtoile, numThreads = 1;


	//CalculeDistances_Thread(m_pointeur_echo, debut, fin, numThreads);

	/*******************************************/
	CalculeDistances(m_pointeur_echo, debut, fin);

	CalculeDistance_leader(m_pointeur_echo);


	for (int id = 0; id < m_iNombreEtoile; id++)
	{
		m_starArray[id]->CorrectionTrajectoire();
	};

	if (m_iCount > m_iCountLeader)
	{

		m_iCountLeader = m_iCountLeader + rand() % 10 + 10;						// identifie le prochain point dans le temps pour le changement de trajectoire du leader...
		correction = rand() % 90 - 45;											// nombre aleatoire entre 0 et 10 pour le changement de trajectoire du leader ( -20 - +20 degres)
		temp1 = m_starArray[0]->m_Vx;
		temp2 = m_starArray[0]->m_Vy;

		m_starArray[0]->m_Vx = cos(correction / 180 * 3.14159) * temp1 - sin(correction / 180 * 3.14159) * temp2;
		m_starArray[0]->m_Vy = sin(correction / 180 * 3.14159) * temp1 + cos(correction / 180 * 3.14159) * temp2;
	};







	InvalidateRect(&rectToRedraw, bErase);

	UpdateData(FALSE);
	for (int i = 0; i < 10; i++)
	{

		NoTimer();
	};

	CDialogEx::OnTimer(nIDEvent);
}

void CTimer_13avril2018Dlg::NoTimer()
{
	// TODO: Add your message handler code here and/or call default
	RECT rectToRedraw;
	//WINDOWPLACEMENT winPlace;
	CClientDC dc(this);
	CRect rect;

	bool bErase = TRUE;

	m_iCount++;
	float temp1, temp2, correction;
	int	oldEcho = m_iNombreEcho;

	m_sCount.Format(_T("%d"), m_iCount);
	//UpdateData(FALSE);

	this->GetClientRect(rect);

	m_str_bottom.Format(_T("%d"), rect.bottom);				// m_str_...: affiche les dimensions dans le dialogue.
	m_str_right.Format(_T("%d"), rect.right);				// m_str_...: affiche les dimensions dans le dialogue.

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

			m_starArray[id]->SetLimites(right, bottom, left, top, front, back);



		};
	}
	else {
	
		rectToRedraw.bottom = bottom;
		rectToRedraw.right = right;
		rectToRedraw.left = left;
		rectToRedraw.top = top;
	
	};

	
	UpdateData(TRUE);

	m_str_bottom.Format(_T("%d"), rect.bottom);				// m_str_...: affiche les dimensions dans le dialogue.
	m_str_right.Format(_T("%d"), rect.right);				// m_str_...: affiche les dimensions dans le dialogue.

	UpdateData(FALSE);
	
	m_pointeur_echo++;  //  indique la position active pour les nouvelles coordonnees...
	if (m_pointeur_echo >= m_iNombreEcho) m_pointeur_echo = 0;

	for (int id = 0; id < m_iNombreEtoile; id++)
	{

		m_starArray[id]->Deplace(m_pointeur_echo);
		m_starArray[id]->VerifieLimites(m_pointeur_echo);

	};


	InitDistances();
	

	/*******************************************/
	int debut=0, fin= m_iNombreEtoile, numThreads=1;


	//CalculeDistances_Thread(m_pointeur_echo, debut, fin, numThreads);

	/*******************************************/
	CalculeDistances(m_pointeur_echo, debut, fin);

	CalculeDistance_leader(m_pointeur_echo);
	

	for (int id = 0; id < m_iNombreEtoile; id++)
	{
		m_starArray[id]->CorrectionTrajectoire();
	};
	
	if (m_iCount > m_iCountLeader)
	{

		m_iCountLeader = m_iCountLeader + rand() % 10 + 10;						// identifie le prochain point dans le temps pour le changement de trajectoire du leader...
		correction = rand() % 90 -45;											// nombre aleatoire entre 0 et 10 pour le changement de trajectoire du leader ( -20 - +20 degres)
		temp1 = m_starArray[0]->m_Vx;
		temp2 = m_starArray[0]->m_Vy;

		m_starArray[0]->m_Vx = cos(correction/180*3.14159) * temp1 - sin(correction/180*3.14159) * temp2;
		m_starArray[0]->m_Vy = sin(correction / 180 * 3.14159) * temp1 + cos(correction / 180 * 3.14159) * temp2;
	};

	


	


	InvalidateRect(&rectToRedraw, bErase);

	UpdateData(FALSE);

	
}


void CTimer_13avril2018Dlg::CalculeDistances_Thread(int echo, int debut, int fin, int numThreads)
{
	std::vector<std::thread> threadVect;
	int threadSpread = m_iNombreEtoile / numThreads;

	CTimer_13avril2018Dlg* TimerPtr = new CTimer_13avril2018Dlg;

	int newEnd = debut + threadSpread - 1;

	std::thread first (&CTimer_13avril2018Dlg::CalculeDistances, TimerPtr, echo, debut, fin);

	/*for (int x = 0; x < numThreads; x++)
	{

		threadVect.emplace_back ( &CTimer_13avril2018Dlg::CalculeDistances, TimerPtr, echo, debut, newEnd);
		debut += threadSpread;
		newEnd += threadSpread;
	};

	for (auto& t : threadVect)
	{
		t.join();
	};*/

	delete TimerPtr;
};

void CTimer_13avril2018Dlg::InitDistances() 
{
	int origine;
	
	for (origine = 0; origine < m_iNombreEtoile; origine++)
	{
		m_starArray[origine]->m_distance_devant = 2000;
		m_starArray[origine]->m_distance_droite = 2000;
		m_starArray[origine]->m_distance_gauche = 2000;
	};


};

void CTimer_13avril2018Dlg::CalculeDistance_leader(int echo) 
{
	double x1, x2, y1, y2, Vx, Vy, distance;
	int destination = 0;																		//rotation est la direction de la rotation a ajouter au calcul (+/1 90 degres).  +1 -> +90 degres, -1 -> -90 degres.
	double cos_teta = 0.0, sin_teta = 0.0, teta, deltaX1 = 0, deltaY1 = 0, rotation, tempx, tempy, horizonX, horizonY;

// 1- calcule de l'angle du vecteur vitesse de l'objet.  Ramener le vecteur vitesse dans le plan(x, 0) (y=0).  
// 2- Evalue si la rotation requise e
// 3- Sauvegarde nombre de rotation et correction de trajectoire requise pour se rapproche du leader...

																							

	


	for (destination = 1; destination < m_iNombreEtoile; destination++)
	{
		
		


		Vx = m_starArray[destination]->m_Vx;												// Etape 1: Calcul de l'angle du vecteur vitesse de l'objet "x"
		Vy = m_starArray[destination]->m_Vy;


		//***************************DONNEES POUR TEST**************

		//Vx = 2;
		//Vy = 2;

		//x1 = 2;		// position de l'objet qui doit rejoindre le leader.
		//y1 = 2;
		//x2 = 4;		// position du leader (la destination recherchee)
		//y2 = 3;

		//**************************FIN: DONNEES POUR TEST**************
																							//Vecteur vitesse = (0,0), (Vx, Vy)

		horizonX = 10.0;																	//Vecteur axe des "x" positif (10,0) : deltaX, deltaY.  Valeur constante pour calculer la rotation.
		horizonY = 0.0;

		rotation = 0;

		sin_teta = (horizonX * Vy - Vx * horizonY) / (sqrt(pow(Vx, 2) + pow(Vy, 2)) * sqrt(pow(horizonX, 2) + pow(horizonY, 2)));
		teta = asin(sin_teta) / 3.14159 * 180;


		if (Vx < 0 && Vy >0)																// Point situé dans le deuxième quadrand.  Angle entre 90 et 180 degres.
		{
			teta = 180 - abs(teta);															// ceci est l'angle entre l'axe des "x" et le vecteur vitesse de l'objet "x".
			rotation = 1;
		};

		if (Vx < 0 && Vy < 0)
		{
			teta = -1 * (180 - abs(teta));													// ceci est l'angle entre l'axe des "x" et le vecteur vitesse de l'objet "x"..
			rotation = -1;																	// Point situé dans le troisième quandrant. Angle entre -90 et -180 degrés.

		};

																							// Etape 2: calculer l'angle entre le vecteur vitesse de l'objet et l'axe des "x".


		cos_teta = cos(-teta / 180 * 3.14159);												//  -teta:la rotation du vecteur distance se fait dans la direction opposee (pour rapprocher les objets).
		sin_teta = sin(-teta / 180 * 3.14159);

																							// Etape 2: faire la rotation du vecteur distance pour permettre le calcul de l'angle entre l'objet "n" et le leader (objet "0").
		x1 = m_starArray[0]->m_positionX[echo];
		y1 = m_starArray[0]->m_positionY[echo];												// position du leader

		x2 = m_starArray[destination]->m_positionX[echo];
		y2 = m_starArray[destination]->m_positionY[echo];									// position de l'objet qui doit rejoindre le leader.

		


		deltaX1 = x1 -x2;																	// vecteur distance entre les deux objets (coordonnes destination - coordonnes du leader). Vecteur: coordonnees(0,0) - (deltaX1, deltaY1)
		deltaY1 = y1 -y2;																	// vecteur qui pointe de l'objet x vers le leader...

		tempx = deltaX1;
		tempy = deltaY1;

		//distance = sqrt(pow(deltaX1, 2) + pow(deltaY1, 2));

																							// Etape 3: rotation du vecteur distance par le meme angle que le vecteur vitesse...mais en direction opposee.

		deltaX1 = cos_teta * tempx - sin_teta * tempy;
		deltaY1 = sin_teta * tempx + cos_teta * tempy;										// Nouvelles coordonnes du vecteur distance, apres rotation.

		
		
																							// Calcule de l'angle entre le vecteur distance (apres rotation) et l'horizon.  Ceci donne l'angle entre les deux objets.
		
		sin_teta = (horizonX * deltaY1 - deltaX1 * horizonY) / (sqrt(pow(deltaX1, 2) + pow(deltaY1, 2)) * sqrt(pow(horizonX, 2) + pow(horizonY, 2)));
		teta = asin(sin_teta) / 3.14159 * 180;

		if (deltaX1 < 0 && deltaY1 >0)														// Point situé dans le deuxième quadrand.  Angle entre 90 et 180 degres.
		{
			teta = 180 - teta;																// ceci est l'angle entre l'axe des "x" et le vecteur vitesse de l'objet "x".
			rotation = 1;
		};

		if (deltaX1 < 0 && deltaY1 < 0)
		{
			teta = -1 * (180 - teta);														// ceci est l'angle entre l'axe des "x" et le vecteur vitesse de l'objet "x"..
			rotation = -1;																	// Point situé dans le troisième quandrant. Angle entre -90 et -180 degrés.

		};
		
		distance = sqrt(pow(deltaX1, 2) + pow(deltaY1, 2));
		
		m_starArray[destination]->SetDistanceLeader(distance, teta);
	};

};



void CTimer_13avril2018Dlg::CalculeDistances(int echo, int debut, int fin)
{
	std::mutex vectLock;

	int origine=0, destination=0, distance=0,  direction =0;
	double vitessex=0, vitessey=0, cos_teta=0.0,sin_teta =0.0,deltaX1 = 0, deltaY1 = 0, deltaX2 = 0, deltaY2 = 0;
	double temp_num, temp_denum, x1, x2, y1, y2, Vx, Vy;  

	//*************************************************//

	//Debut: Calcul des distance objet- limites du terrain
	
	int limite_max_X = m_starArray[origine]->m_maxX;											//m_maxXY: dimensions des limites du jeu
	int limite_max_Y = m_starArray[origine]->m_maxY;
	int limite_min_X = m_starArray[origine]->m_minX;
	int limite_min_Y = m_starArray[origine]->m_minY;

	for (origine = 0; origine < m_iNombreEtoile; origine++) 									// for (origine = 0; origine < m_iNombreEtoile; origine++)
	{
		
	
				x1 = m_starArray[origine]->m_positionX[echo];									// position de l'objet
				y1 = m_starArray[origine]->m_positionY[echo];

				deltaX1 = limite_max_X - x1;													// calcul des distances entre l'objet et les limites du terrain...
				deltaY1 = limite_max_Y - y1;
				deltaX2 = limite_min_X - x1;
				deltaY2 = limite_min_Y - y1;

				if (abs(deltaX2) < abs(deltaX1))
				{
					deltaX1 = deltaX2;															//trouve la plus courte distance en "X" et sauve dans deltaX1
				};
				if (abs(deltaY2) < abs(deltaY1))
				{
					deltaY1 = deltaY2;															//trouve la plus courte distance en "Y" et sauve dans deltaY1
				};


				if (abs(deltaY1) < abs(deltaX1))												//prendre la distance la plus courte entre un mur et l'objet...en ligne droite (perpendiculaire au mur)
				{
					deltaX1 = 0;
				}
				else
				{
					deltaY1 = 0;
				}
				

				distance = sqrt(pow(deltaX1, 2) + pow(deltaY1, 2));

				// calcul de l'angle entre la direction de l'objet et l'obstacle (objet 2).  Vecteur 1 = distance (deltax, deltay), vecteur 2 = vitesse de l'objet #1.


				//if (m_starArray[destination]->m_Vx == 0) m_starArray[destination]->m_Vx = 0.001;  // correction pour éviter de diviser par zero.

				Vx = m_starArray[origine]->m_Vx;
				Vy = m_starArray[origine]->m_Vy;

				sin_teta = (Vx * deltaY1 - deltaX1 * Vy) / (sqrt(pow(Vx, 2) + pow(Vy, 2)) * sqrt(pow(deltaX1, 2) + pow(deltaY1, 2)));

				

				// calcul de la direction pour eviter la collision (obstacle à gauche=1 , droite=2)

				if (sin_teta < 0) direction = 1;
				if (sin_teta > 0) direction = 2;


				m_starArray[origine]->UpdateDistance(distance, sin_teta, direction);

						

		

	};
	//Fin: Calcul des distance objet- limites du terrain

	//*************************************************//



	for (origine = 0; origine < m_iNombreEtoile; origine++) 					
	{
		for (destination = 0; destination < m_iNombreEtoile; destination++) ///for (destination = 0; destination < 15; destination++)   //for (destination = 0; destination < m_iNombreEtoile; destination++)
		{
			if (origine != destination)
			{
				
				x1 = m_starArray[origine]->m_positionX[echo];
				y1 = m_starArray[origine]->m_positionY[echo];

				x2 = m_starArray[destination]->m_positionX[echo];
				y2 = m_starArray[destination]->m_positionY[echo];
				
				

				deltaX1 = x2-x1;																	// vecteur distance entre les deux objets:  coordonnees(0,0) - (deltaX1, deltaY1)
				deltaY1 = y2-y1;

				distance = sqrt(pow(deltaX1, 2) + pow(deltaY1, 2));
				
				// calcul de l'angle entre la direction de l'objet et l'obstacle (objet 2).  Vecteur 1 = distance (deltax, deltay), vecteur 2 = vitesse de l'objet #1.

				
				if (m_starArray[destination]->m_Vx == 0) m_starArray[destination]->m_Vx = 0.001;	// correction pour éviter de diviser par zero.

				Vx = m_starArray[origine]->m_Vx;
				Vy = m_starArray[origine]->m_Vy;													// vecteur vitesse :  coordonnees(0,0) - (Vx, Vy)

				
				
				sin_teta = (Vx * deltaY1 - deltaX1 * Vy) / (sqrt(pow(Vx, 2) + pow(Vy, 2)) * sqrt(pow(deltaX1, 2) + pow(deltaY1, 2)));
				
				
				// calcul de l'angle entre les vecteurs:

				//temp_num = m_starArray[destination]->m_Vx * deltaX + m_starArray[destination]->m_Vy * deltaY;
				//temp_denum = sqrt(pow(m_starArray[destination]->m_Vx, 2) + pow(m_starArray[destination]->m_Vy, 2)) * sqrt(pow(deltaX, 2) + pow(deltaY, 2));

				//cos_teta = temp_num / temp_denum;

				// calcul de la direction pour eviter la collision (obstacle à gauche=1 , droite=2)

				if (sin_teta < 0) direction = 2;
				if (sin_teta > 0) direction = 1;

				
				m_starArray[origine]->UpdateDistance(distance, sin_teta, direction);

				if (origine == 0)
				{
					m_starArray[destination]->SetDistanceLeader(distance, sin_teta);

				};
			

				if (origine == 0 && destination == 1)
				{
					//m_distance_0_1.Format(_T("%d"), m_slider_D1);				// m_str_...: affiche les dimensions dans le dialogue.    distance
					m_angle_0_1.Format(_T("%6.3f"), asin(sin_teta)*180.0/3.14159);
					UpdateData(FALSE);

				};
				if (origine == 1 && destination == 0)
				{
					m_angle_1_0.Format(_T("%6.3f"), asin(sin_teta) * 180 / 3.14159);
					UpdateData(FALSE);
				}

				//m_starArray[destination]->UpdateDistance(distance, cos_teta, direction);  //met à jour les distances pour les deux objets.  Inverse la direction des deltaX,Y quand on mesure à partir de la destination...
			};

		};

	};

	
	
};

void CTimer_13avril2018Dlg::OnEnChangeEnombreEcho()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	int oldEcho = m_iNombreEcho;
	
	UpdateData(TRUE);

	if (m_iNombreEcho > 50) m_iNombreEcho = 50;

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

	int posX, posY, posZ, Vx, Vy, Vz;

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

			posX = (rand() % (right-left) + left); //(left + right) / 2;
			posY = (rand() % (top-bottom) + top); //(top + bottom) / 2;
			posZ = (rand() % (front - back) + back); //(top + bottom) / 2;

			m_starArray[id]->InitPosition(posX, posY, posZ);

			Vx = 5; // (rand() % 10 + 1);
			Vy = 5; // (rand() % 10 + 1);
			Vz = 5;

			m_starArray[id]->SetVitesse(Vx, Vy, Vz);

			m_starArray[id]->SetLimites(right, bottom, left, top, front, back);



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


BOOL CTimer_13avril2018Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialogEx::OnEraseBkgnd(pDC);
}


void CTimer_13avril2018Dlg::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CTimer_13avril2018Dlg::OnBnClickedCheck43d()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	for(int id=0; id< m_iNombreEtoile; id++)
	{
		m_starArray[id]->Set3D(m_3D_enable);


	};
}
