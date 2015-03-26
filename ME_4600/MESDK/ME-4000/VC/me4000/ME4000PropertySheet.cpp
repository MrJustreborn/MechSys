// ME4000PropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "me4000.h"
#include "ME4000PropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CME4000PropertySheet

IMPLEMENT_DYNAMIC(CME4000PropertySheet, CPropertySheet)

CME4000PropertySheet::CME4000PropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CME4000PropertySheet::CME4000PropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CME4000PropertySheet::~CME4000PropertySheet()
{
}


BEGIN_MESSAGE_MAP(CME4000PropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CME4000PropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CME4000PropertySheet message handlers

BOOL CME4000PropertySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	
	// remove standard buttons for modeless dialogs

	HWND hWnd = ::GetDlgItem(m_hWnd, IDHELP);

	if (hWnd != NULL)
	{
		::ShowWindow(hWnd, SW_HIDE);
		::EnableWindow(hWnd, FALSE);
	}

	hWnd = ::GetDlgItem(m_hWnd, ID_APPLY_NOW);

	if (hWnd != NULL)
	{
		::ShowWindow(hWnd, SW_HIDE);
		::EnableWindow(hWnd, FALSE);
	}

	hWnd = ::GetDlgItem(m_hWnd, IDCANCEL);

	if (hWnd != NULL)
	{
		::ShowWindow(hWnd, SW_HIDE);
		::EnableWindow(hWnd, FALSE);
	}

	hWnd = ::GetDlgItem(m_hWnd, IDOK);

	if (hWnd != NULL)
	{
		::ShowWindow(hWnd, SW_HIDE);
		::EnableWindow(hWnd, FALSE);
	}

	// resize the tab control

	hWnd = (HWND)::GetDlgItem(m_hWnd, AFX_IDC_TAB_CONTROL);

	ASSERT(hWnd != NULL);

	CRect rectOld;

	::GetWindowRect(hWnd, &rectOld);

	ScreenToClient(rectOld);

/*
	CRect rectNew(0, 0, 0, 32);

	::MapDialogRect(m_hWnd, &rectNew);
*/
//	::SetWindowPos(hWnd, NULL, 0, 0, rectOld.Width(), rectOld.Height() + 30,
//		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	GetWindowRect(&rectOld);
	SetWindowPos(NULL, 0, 0, rectOld.Width(), rectOld.Height() - 32,
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	return bResult;
}
