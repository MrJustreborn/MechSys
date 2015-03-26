#if !defined(AFX_ExternalInterruptPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_)
#define AFX_ExternalInterruptPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExternalInterruptPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExternalInterruptPP dialog

class CExternalInterruptPP;

struct SMEBoardExtInt
{
	CExternalInterruptPP*	m_pExtIntPP;
	
	int	m_iIndexBoard;		
	
	unsigned int m_uiNumberOfInterrupts;
};

class CExternalInterruptPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CExternalInterruptPP)

// Construction
public:
	CExternalInterruptPP();
	~CExternalInterruptPP();

// Dialog Data
	//{{AFX_DATA(CExternalInterruptPP)
	enum { IDD = IDD_EXT_INTERRUPT_PP };
	CComboBox	m_comboBoardNumber;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	CPropertySheet*	m_pPropertySheet;

private:

	SMEBoardExtInt m_sBoardExtInt[ME4000_MAX_DEVICES];
	
	int m_iCurrentBoardIndex;

	CWnd*		m_pPlotWin;
	
	CRect		m_rectPlotClient;

	CRect		m_rectPlotChild;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CExternalInterruptPP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CExternalInterruptPP)
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	afx_msg void OnPaint();
	afx_msg void OnButtonDisableExtInt();
	afx_msg void OnButtonEnableExtInt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void SetControlStates(void);

	void RedrawPlot(void);
	
	static void _stdcall ExtIRQProc(void* pExtIrqContext);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ExternalInterruptPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_)
