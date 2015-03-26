#if !defined(AFX_INFOPP_H__94E19015_D35C_44B7_A31D_B72EC65E0AD4__INCLUDED_)
#define AFX_INFOPP_H__94E19015_D35C_44B7_A31D_B72EC65E0AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoPP dialog

class CInfoPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CInfoPP)

// Construction
public:
	CInfoPP();
	~CInfoPP();

// Dialog Data
	//{{AFX_DATA(CInfoPP)
	enum { IDD = IDD_INFO_PP };
	CComboBox	m_comboBoardNumber;
	//}}AFX_DATA

public:

	int m_iCurrentBoardIndex;

	CPropertySheet*	m_pPropertySheet;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInfoPP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInfoPP)
	afx_msg void OnSelchangeComboBoard();
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void DisplayBoardInfo(void);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOPP_H__94E19015_D35C_44B7_A31D_B72EC65E0AD4__INCLUDED_)
