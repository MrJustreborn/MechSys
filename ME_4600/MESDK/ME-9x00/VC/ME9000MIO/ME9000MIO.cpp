// ME9000mio.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ME9000MIO.h"
#include "ME9000MIODlg.h"

#include "..\me9000miodll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CME9000DApp

BEGIN_MESSAGE_MAP(CME9000DApp, CWinApp)
	//{{AFX_MSG_MAP(CME9000DApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CME9000DApp construction

CME9000DApp::CME9000DApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CME9000DApp object

CME9000DApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CME9000DApp initialization

BOOL CME9000DApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	me9000mioErrorSetDefaultProc(ME9000MIO_ERROR_DEFAULT_PROC_ENABLE);

	CME9000DDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
