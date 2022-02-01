
// Timer_13avril2018Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CPaintDlg.h"
#include "Etoile.h"
#include <array>
#include <math.h>




// CTimer_13avril2018Dlg dialog
class CTimer_13avril2018Dlg : public CDialogEx
{
// Construction
public:
	CTimer_13avril2018Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMER_13AVRIL2018_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartbutton();
	afx_msg void OnBnClickedStopbutton();
	CButton m_cStartCount;
	CButton m_cStopCount;

	CString m_sCount;
	
	int m_iInterval=50;
	int m_iCount=10;
	int m_iCountLeader = 0;


	afx_msg void OnChangeEinterval();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void CalculeDistances(int echo, int debut, int fin);
	void CalculeDistances_Thread(int echo, int debut, int fin, int numThreads);
	void CalculeDistance_leader(int echo);
	void InitDistances();

	void NoTimer();

private:
	

public:
	int m_1_posX;									//positions et vitesses des points
	int m_1_posY;
	int m_1_posZ;

	//int m_2_posY;
	
	float m_1_speedX;
	float m_1_speedY;
	float m_1_speedZ;

	float m_2_speedX;
	float m_2_speedY;
	float m_2_speedZ;

	afx_msg void OnEnChangeEnombreEcho();
	int m_iNombreEcho;								//nombre d'echo qui seront retenus pour afficher...		
	afx_msg void OnEnChangeEnombreEtoile();

	int m_iNombreEtoile, m_iOldNombreEtoile =0;
	int m_PenPointer=0;

	CPaintDlg m_paintDlg;

	struct ligne 
	{
		int point_1;
		int point_2;
		int point_3;
		int point_4;
	};

	int top, bottom, left, right, front, back, oldRight, oldBottom =0;
	
		
	CEtoile* m_starArray[100];


	ligne m_Lignes[5] = { 0 };

	int m_pointeur_ligne =0;
	int m_pointeur_echo = 0; // indique quel est l'écho actif.


	BOOL m_multi_lien, m_running;
	CString m_str_right;
	CString m_str_bottom;
	CString m_largeur;
	CString m_hauteur;

	int m_distanceSecuritaire = 150;
	CString m_distance_0_1;
	CString m_angle_0_1;

	CString m_angle_1_0;
	BOOL m_dessineCercle;
	BOOL m_dessineTriangle;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
//	int m_slider_D1;
//	int m_slider_D2;
	BOOL m_3D_enable;
	afx_msg void OnBnClickedCheck43d();
};
