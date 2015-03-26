// ME8100Demo.h : main header file for the ME8100DEMO application
//

#if !defined(AFX_ME8100DEMO_H__AF20A16C_FFE8_11D2_9EF8_0020A90C91B5__INCLUDED_)
#define AFX_ME8100DEMO_H__AF20A16C_FFE8_11D2_9EF8_0020A90C91B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "ME8100DemoDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CME8100DemoApp:
// See ME8100Demo.cpp for the implementation of this class
//

class CME8100DemoApp : public CWinApp
{
public:
	CME8100DemoApp();

	static void _stdcall IRQTestFunction(int i_context);	// IRQ-function

private:
	
	static CME8100DemoDlg dlg;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CME8100DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CME8100DemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ME8100DEMO_H__AF20A16C_FFE8_11D2_9EF8_0020A90C91B5__INCLUDED_)
