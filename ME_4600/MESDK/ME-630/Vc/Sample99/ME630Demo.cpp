// ME630Demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ME630Demo.h"
#include "ME630DemoDlg.h"

#include "..\me630.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CME630DemoApp

BEGIN_MESSAGE_MAP(CME630DemoApp, CWinApp)
	//{{AFX_MSG_MAP(CME630DemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CME630DemoApp construction

CME630DemoDlg CME630DemoApp::dlg;
	
CME630DemoApp::CME630DemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CME630DemoApp object

CME630DemoApp theApp;

// IRQ-function
void CME630DemoApp::IRQ1TestFunction(int i_context)		
{
	// If the dialog ist not displayed at the moment we should return right away
	
	if(dlg.m_iCurrentBoardIndex == i_context)
	{
		dlg.UpdateIRQ1Count();
	}
}

// IRQ-function
void CME630DemoApp::IRQ2TestFunction(int i_context)		
{
	// If the dialog ist not displayed at the moment we should return right away
	
	if(dlg.m_iCurrentBoardIndex == i_context)
	{
		dlg.UpdateIRQ2Count();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CME630DemoApp initialization

BOOL CME630DemoApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// See if any ME630 boards have been found at system start.
	// If not we can save ourselves a lot of trouble by exiting
	// right away with an error message

	BOOL b_board_found = FALSE;
	
	for (int index_board = 0; index_board < ME_MAX_DEVICES; index_board++)
	{
		int i_version;			
		
		if( _me630GetBoardVersion(index_board, &i_version) )
		{
			b_board_found = TRUE;
		}
	}
	
	if(!b_board_found)
	{
		// Not a single ME630 board was found - exit with an error message			
		
		AfxMessageBox("No ME630 boards found!", MB_OK|MB_ICONSTOP, 0);

		return(FALSE);
	}
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
