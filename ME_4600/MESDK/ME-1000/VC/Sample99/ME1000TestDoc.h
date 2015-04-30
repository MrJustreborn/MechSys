// ME1000TestDoc.h : Schnittstelle der Klasse CME1000TestDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ME1000TESTDOC_H__FB717748_9759_11D3_97C7_D3365057804F__INCLUDED_)
#define AFX_ME1000TESTDOC_H__FB717748_9759_11D3_97C7_D3365057804F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CME1000TestDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CME1000TestDoc();
	DECLARE_DYNCREATE(CME1000TestDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CME1000TestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CME1000TestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CME1000TestDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ME1000TESTDOC_H__FB717748_9759_11D3_97C7_D3365057804F__INCLUDED_)
