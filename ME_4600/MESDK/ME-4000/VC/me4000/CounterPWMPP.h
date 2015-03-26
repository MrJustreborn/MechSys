#if !defined(AFX_CounterPWMPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_)
#define AFX_CounterPWMPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CounterPWMPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCounterPWMPP dialog

class CCounterPWMPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CCounterPWMPP)

// Construction
public:
	CCounterPWMPP();
	~CCounterPWMPP();

// Dialog Data
	//{{AFX_DATA(CCounterPWMPP)
	enum { IDD = IDD_COUNTER_PWM_PP };
	CSpinButtonCtrl	m_spinPreScaler;
	CSpinButtonCtrl	m_spinDutyCycle;
	CSpinButtonCtrl	m_spinWriteValue1;
	CSpinButtonCtrl	m_spinWriteValue2;
	CSpinButtonCtrl	m_spinWriteValue3;
	CComboBox	m_comboMode1;
	CComboBox	m_comboMode2;
	CComboBox	m_comboMode3;
	CComboBox	m_comboBoardNumber;
	//}}AFX_DATA

	CPropertySheet*	m_pPropertySheet;

private:

	int m_iCurrentBoardIndex;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCounterPWMPP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCounterPWMPP)
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	afx_msg void OnButtonWrite1();
	afx_msg void OnButtonRead1();
	afx_msg void OnButtonWrite2();
	afx_msg void OnButtonRead2();
	afx_msg void OnButtonWrite3();
	afx_msg void OnButtonRead3();
	afx_msg void OnButtonPwmStart();
	afx_msg void OnButtonPwmStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void SetControlStates(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CounterPWMPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_)
