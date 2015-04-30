// ME9000D.h : main header file for the ME9000D application
//

#if !defined(AFX_ME9000D_H__D6C8593F_2FD3_4107_A6D9_B4B64EF3CE96__INCLUDED_)
#define AFX_ME9000D_H__D6C8593F_2FD3_4107_A6D9_B4B64EF3CE96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CME9000DApp:
// See ME9000D.cpp for the implementation of this class
//

class CME9000DApp : public CWinApp
{
public:
	CME9000DApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CME9000DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CME9000DApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ME9000D_H__D6C8593F_2FD3_4107_A6D9_B4B64EF3CE96__INCLUDED_)
