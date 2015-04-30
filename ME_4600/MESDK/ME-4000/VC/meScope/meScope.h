// meScope.h : main header file for the MESCOPE application
//

#if !defined(AFX_MESCOPE_H__8EA4A00F_2367_4EDA_9441_A3BCE469159A__INCLUDED_)
#define AFX_MESCOPE_H__8EA4A00F_2367_4EDA_9441_A3BCE469159A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMeScopeApp:
// See meScope.cpp for the implementation of this class
//

class CMeScopeApp : public CWinApp
{
public:
	CMeScopeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeScopeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CMeScopeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESCOPE_H__8EA4A00F_2367_4EDA_9441_A3BCE469159A__INCLUDED_)
