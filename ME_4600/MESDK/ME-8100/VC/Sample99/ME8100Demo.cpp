// ME8100Demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ME8100Demo.h"
#include "ME8100DemoDlg.h"
#include ".\..\me8100.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CME8100DemoApp

BEGIN_MESSAGE_MAP(CME8100DemoApp, CWinApp)
	//{{AFX_MSG_MAP(CME8100DemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CME8100DemoApp construction

CME8100DemoDlg CME8100DemoApp::dlg;
	
CME8100DemoApp::CME8100DemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// IRQ-function
void CME8100DemoApp::IRQTestFunction(int i_context)		
{
	// If the dialog ist not displayed at the moment we should return right away
	
	if(!dlg.m_bDisplayed)
	{
		return;
	}

	dlg.BlinkIntAOn();

	::Sleep(20);

	// Its just possible that the dialog has been dismissed in the meantime!
	
	if(!dlg.m_bDisplayed)
	{
		return;
	}

	dlg.BlinkIntAOff();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CME8100DemoApp object

CME8100DemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CME8100DemoApp initialization

BOOL CME8100DemoApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// See if any ME8100 boards have been found at system start.
	// If not we can save ourselves a lot of trouble by exiting
	// right away with an error message

	BOOL b_board_found = FALSE;


	for (int index_board = 0; index_board < 32; index_board++)
	{
		// call me8100PROMVersion simply to see if the board is there
		
		int i_version;			
		
		if( me8100PROMVersion(index_board, &i_version) )
		{
			b_board_found = TRUE;
		}
	}
	
	if(!b_board_found)
	{
		// Not a single ME8100 board was found - exit with an error message			
		
		AfxMessageBox("No ME8100 boards found!", MB_OK|MB_ICONSTOP, 0);

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
