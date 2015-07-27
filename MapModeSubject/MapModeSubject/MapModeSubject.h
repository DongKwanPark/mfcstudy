
// MapModeSubject.h : main header file for the MapModeSubject application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMapModeSubjectApp:
// See MapModeSubject.cpp for the implementation of this class
//

class CMapModeSubjectApp : public CWinApp
{
public:
	CMapModeSubjectApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMapModeSubjectApp theApp;
