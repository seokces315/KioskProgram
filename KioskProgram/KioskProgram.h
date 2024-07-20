// KioskProgram.h : main header file for the KioskProgram application

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKioskProgramApp:

class CKioskProgramApp : public CWinApp
{
public:
	CKioskProgramApp() noexcept;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKioskProgramApp theApp;
