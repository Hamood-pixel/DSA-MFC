
// MFCassignment.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCassignmentApp:
// See MFCassignment.cpp for the implementation of this class
//

class CMFCassignmentApp : public CWinApp
{
public:
	CMFCassignmentApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCassignmentApp theApp;
