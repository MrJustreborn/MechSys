// ME1000Test.h : Haupt-Header-Datei f�r die Anwendung ME1000TEST
//

#if !defined(AFX_ME1000TEST_H__FB717742_9759_11D3_97C7_D3365057804F__INCLUDED_)
#define AFX_ME1000TEST_H__FB717742_9759_11D3_97C7_D3365057804F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CME1000TestApp:
// Siehe ME1000Test.cpp f�r die Implementierung dieser Klasse
//

class CME1000TestApp : public CWinApp
{
public:
	CME1000TestApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CME1000TestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CME1000TestApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingef�gt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VER�NDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_ME1000TEST_H__FB717742_9759_11D3_97C7_D3365057804F__INCLUDED_)
