// meScopeDoc.h : interface of the CMeScopeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESCOPEDOC_H__70A3157A_DF0C_415E_AED1_139A344FF3EC__INCLUDED_)
#define AFX_MESCOPEDOC_H__70A3157A_DF0C_415E_AED1_139A344FF3EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMeScopeDoc : public CDocument
{
protected: // create from serialization only
	CMeScopeDoc();
	DECLARE_DYNCREATE(CMeScopeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeScopeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMeScopeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMeScopeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMeScopeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESCOPEDOC_H__70A3157A_DF0C_415E_AED1_139A344FF3EC__INCLUDED_)
