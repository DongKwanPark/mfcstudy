
// ExtendStar.h : main header file for the ExtendStar application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CExtendStarApp:
// See ExtendStar.cpp for the implementation of this class
//

class CExtendStarApp : public CWinApp
{
public:
	CExtendStarApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CExtendStarApp theApp;
