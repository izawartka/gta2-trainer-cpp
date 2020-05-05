// gta2dll.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "gta2dll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// Cgta2dllApp

BEGIN_MESSAGE_MAP(Cgta2dllApp, CWinApp)
END_MESSAGE_MAP()


// Cgta2dllApp construction

Cgta2dllApp::Cgta2dllApp() { }

Cgta2dllApp::~Cgta2dllApp() {
	if (m_mainWindow) {
		m_mainWindow->DestroyWindow();
		delete m_mainWindow;
	}
}


// The one and only Cgta2dllApp object

Cgta2dllApp theApp;

BOOL Cgta2dllApp::InitInstance()
{
	CWinApp::InitInstance();

	m_mainWindow = new MainWindow();

	m_mainWindow->Create(IDD_DIALOG1, CWnd::GetDesktopWindow());
	m_mainWindow->ShowWindow(SW_SHOW);

	return TRUE;
}


BOOL Cgta2dllApp::InitApplication()
{
	return CWinApp::InitApplication();
}
