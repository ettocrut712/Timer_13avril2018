
// Timer_13avril2018.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTimer_13avril2018App:
// See Timer_13avril2018.cpp for the implementation of this class
//

class CTimer_13avril2018App : public CWinApp
{
public:
	CTimer_13avril2018App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTimer_13avril2018App theApp;