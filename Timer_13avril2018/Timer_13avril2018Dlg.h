
// Timer_13avril2018Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CPaintDlg.h"





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
	
	int m_iInterval;
	int m_iCount;
	afx_msg void OnChangeEinterval();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	

public:
	int m_1_posX;
	int m_1_posY;
	int m_2_posX;
	int m_2_posY;
	int m_1_speedX;
	int m_1_speedY;
	int m_2_speedX;
	int m_2_speedY;
	afx_msg void OnEnChangeEnombreEcho();
	int m_iNombreEcho;
	afx_msg void OnEnChangeEnombreEtoile();
	int m_iNombreEtoile;
	CPaintDlg m_paintDlg;

	struct ligne 
	{
		int point_1;
		int point_2;
		int point_3;
		int point_4;
	};

	int top, bottom, left, right;
	
	

	ligne m_Lignes[100];

	int m_pointeur_ligne =0;

};
