// meScopeDoc.cpp : implementation of the CMeScopeDoc class
//

#include "stdafx.h"
#include "meScope.h"

#include "meScopeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeScopeDoc

IMPLEMENT_DYNCREATE(CMeScopeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMeScopeDoc, CDocument)
	//{{AFX_MSG_MAP(CMeScopeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMeScopeDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CMeScopeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMeScope to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {C119B3EE-05BA-48D7-8845-63C729747697}
static const IID IID_IMeScope =
{ 0xc119b3ee, 0x5ba, 0x48d7, { 0x88, 0x45, 0x63, 0xc7, 0x29, 0x74, 0x76, 0x97 } };

BEGIN_INTERFACE_MAP(CMeScopeDoc, CDocument)
	INTERFACE_PART(CMeScopeDoc, IID_IMeScope, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeScopeDoc construction/destruction

CMeScopeDoc::CMeScopeDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CMeScopeDoc::~CMeScopeDoc()
{
	AfxOleUnlockApp();
}

BOOL CMeScopeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMeScopeDoc serialization

void CMeScopeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMeScopeDoc diagnostics

#ifdef _DEBUG
void CMeScopeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMeScopeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMeScopeDoc commands
