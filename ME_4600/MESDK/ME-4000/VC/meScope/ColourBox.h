#if !defined(AFX_COLOURBOX_H__3F7DA72C_1FBB_4681_BC4D_6BA5319B7216__INCLUDED_)
#define AFX_COLOURBOX_H__3F7DA72C_1FBB_4681_BC4D_6BA5319B7216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColourBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColourBox window

class CColourBox : public CStatic
{
// Construction
public:
	CColourBox();

// Attributes
public:

	COLORREF m_crBackground;

	COLORREF m_crForeground;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColourBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColourBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColourBox)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOURBOX_H__3F7DA72C_1FBB_4681_BC4D_6BA5319B7216__INCLUDED_)
