#if !defined(AFX_ERRORDIALOG_H__735094E0_9CDD_11D3_97DB_C86D2ECC884F__INCLUDED_)
#define AFX_ERRORDIALOG_H__735094E0_9CDD_11D3_97DB_C86D2ECC884F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CErrorDialog 

class CErrorDialog : public CDialog
{
// Konstruktion
public:
	CString m_csErrorMessage;
	CErrorDialog(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CErrorDialog)
	enum { IDD = IDD_DIALOG_ERROR };
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CErrorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CErrorDialog)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_ERRORDIALOG_H__735094E0_9CDD_11D3_97DB_C86D2ECC884F__INCLUDED_
