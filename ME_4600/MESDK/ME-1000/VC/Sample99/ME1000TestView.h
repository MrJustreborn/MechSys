// ME1000TestView.h : Schnittstelle der Klasse CME1000TestView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ME1000TESTVIEW_H__FB71774A_9759_11D3_97C7_D3365057804F__INCLUDED_)
#define AFX_ME1000TESTVIEW_H__FB71774A_9759_11D3_97C7_D3365057804F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CME1000TestView : public CFormView
{
protected: // Nur aus Serialisierung erzeugen
	CME1000TestView();
	DECLARE_DYNCREATE(CME1000TestView)

public:
	//{{AFX_DATA(CME1000TestView)
	enum{ IDD = IDD_ME1000TEST_FORM };
		// HINWEIS: der Klassenassistent fügt an dieser Stelle Datenelemente (Members) ein
	//}}AFX_DATA

// Attribute
public:
	CME1000TestDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CME1000TestView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnInitialUpdate(); // das erste mal nach der Konstruktion aufgerufen
	//}}AFX_VIRTUAL

// Implementierung
public:
	void LongWrite ();
	void WordWrite ();
	void ByteWrite ();
	void BitWrite ();
	void LongRead();
	void WordRead();
	void ByteRead ();
	void BitRead (void);
	virtual ~CME1000TestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CME1000TestView)
	afx_msg void OnButtonDeviceInfo();
	afx_msg void OnSelchangeComboBoardNumber();
	afx_msg void OnButtonRead();
	afx_msg void OnButtonWrite();
	afx_msg void OnSelchangeComboFunctionSelect();
	afx_msg void OnButtonReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in ME1000TestView.cpp
inline CME1000TestDoc* CME1000TestView::GetDocument()
   { return (CME1000TestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ME1000TESTVIEW_H__FB71774A_9759_11D3_97C7_D3365057804F__INCLUDED_)
