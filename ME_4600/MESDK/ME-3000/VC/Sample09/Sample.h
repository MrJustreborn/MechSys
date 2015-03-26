// sample.h : main header file for the TESTAICONTINUOUS application
//

#if !defined(AFX_TESTAICONTINUOUS_H__AAE2C5AA_9665_4A50_A08C_C39DEB814D19__INCLUDED_)
#define AFX_TESTAICONTINUOUS_H__AAE2C5AA_9665_4A50_A08C_C39DEB814D19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

void _stdcall PlotValues(short* p_short, int count);

/////////////////////////////////////////////////////////////////////////////
// CTestAIContinuousApp:
// See TestAIContinuous.cpp for the implementation of this class
//

class CTestAIContinuousApp : public CWinApp
{
public:
	CTestAIContinuousApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAIContinuousApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestAIContinuousApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTAICONTINUOUS_H__AAE2C5AA_9665_4A50_A08C_C39DEB814D19__INCLUDED_)
