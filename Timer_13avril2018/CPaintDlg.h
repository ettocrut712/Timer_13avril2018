#pragma once


// CPaintDlg dialog

class CPaintDlg : public CDialog
{
	DECLARE_DYNAMIC(CPaintDlg)

public:
	CPaintDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPaintDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPaintDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
