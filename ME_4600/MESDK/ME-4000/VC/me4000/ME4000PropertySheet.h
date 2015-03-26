#if !defined(AFX_ME4000PROPERTYSHEET_H__FC13C35B_9426_4B60_891F_EA9042EB28B8__INCLUDED_)
#define AFX_ME4000PROPERTYSHEET_H__FC13C35B_9426_4B60_891F_EA9042EB28B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ME4000PropertySheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CME4000PropertySheet

class CME4000PropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CME4000PropertySheet)

// Construction
public:
	CME4000PropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CME4000PropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CME4000PropertySheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CME4000PropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CME4000PropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ME4000PROPERTYSHEET_H__FC13C35B_9426_4B60_891F_EA9042EB28B8__INCLUDED_)
