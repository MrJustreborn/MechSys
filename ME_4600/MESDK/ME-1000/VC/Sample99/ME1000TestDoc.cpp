// ME1000TestDoc.cpp : Implementierung der Klasse CME1000TestDoc
//

#include "stdafx.h"
#include "ME1000Test.h"

#include "ME1000TestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CME1000TestDoc

IMPLEMENT_DYNCREATE(CME1000TestDoc, CDocument)

BEGIN_MESSAGE_MAP(CME1000TestDoc, CDocument)
	//{{AFX_MSG_MAP(CME1000TestDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CME1000TestDoc Konstruktion/Destruktion

CME1000TestDoc::CME1000TestDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CME1000TestDoc::~CME1000TestDoc()
{
}

BOOL CME1000TestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CME1000TestDoc Serialisierung

void CME1000TestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Hier Code zum Speichern einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Hier Code zum Laden einfügen
	}
}

/////////////////////////////////////////////////////////////////////////////
// CME1000TestDoc Diagnose

#ifdef _DEBUG
void CME1000TestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CME1000TestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CME1000TestDoc Befehle
