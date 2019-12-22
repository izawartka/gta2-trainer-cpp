// gta2dll.h : main header file for the gta2dll DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "MainWindow.h"


// Cgta2dllApp
// See gta2dll.cpp for the implementation of this class
//

class Cgta2dllApp : public CWinApp
{
public:
	Cgta2dllApp();
	~Cgta2dllApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	MainWindow *m_mainWindow;
	virtual BOOL InitApplication();
};
