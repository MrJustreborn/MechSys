// ME630Demo.h : main header file for the ME630DEMO application
//

#if !defined(AFX_ME630DEMO_H__501A9C27_F65E_11D3_A05E_0020A90C91B5__INCLUDED_)
#define AFX_ME630DEMO_H__501A9C27_F65E_11D3_A05E_0020A90C91B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CME630DemoApp:
// See ME630Demo.cpp for the implementation of this class
//

#include "ME630DemoDlg.h"

class CME630DemoApp : public CWinApp
{
public:
	CME630DemoApp();

	static void _stdcall IRQ1TestFunction(int i_context);	// IRQ1-function

	static void _stdcall IRQ2TestFunction(int i_context);	// IRQ2-function

private:
	
	static CME630DemoDlg dlg;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CME630DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CME630DemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ME630DEMO_H__501A9C27_F65E_11D3_A05E_0020A90C91B5__INCLUDED_)
