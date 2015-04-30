#if !defined(AFX_MULTISIGPP_H__45285511_5765_4615_8593_D555A78867E3__INCLUDED_)
#define AFX_MULTISIGPP_H__45285511_5765_4615_8593_D555A78867E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultiSigPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultiSigPP dialog

class CMultiSigPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CMultiSigPP)

// Construction
public:
	CMultiSigPP();
	~CMultiSigPP();

// Dialog Data
	//{{AFX_DATA(CMultiSigPP)
	enum { IDD = IDD_MULTISIG_PP };
	CComboBox	m_comboBoardNumber;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

public:

	int m_iCurrentBoardIndex;

	CPropertySheet*	m_pPropertySheet;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMultiSigPP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMultiSigPP)
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	afx_msg void OnReset();

	afx_msg void OnButtonLedOff0();
	afx_msg void OnButtonLedOn0();
	afx_msg void OnButtonGain1A0();
	afx_msg void OnButtonGain10A0();
	afx_msg void OnButtonGain100A0();
	afx_msg void OnButtonGain1B0();
	afx_msg void OnButtonGain10B0();
	afx_msg void OnButtonGain100B0();

	afx_msg void OnButtonLedOff1();
	afx_msg void OnButtonLedOn1();
	afx_msg void OnButtonGain1A1();
	afx_msg void OnButtonGain10A1();
	afx_msg void OnButtonGain100A1();
	afx_msg void OnButtonGain1B1();
	afx_msg void OnButtonGain10B1();
	afx_msg void OnButtonGain100B1();

	afx_msg void OnButtonLedOff2();
	afx_msg void OnButtonLedOn2();
	afx_msg void OnButtonGain1A2();
	afx_msg void OnButtonGain10A2();
	afx_msg void OnButtonGain100A2();
	afx_msg void OnButtonGain1B2();
	afx_msg void OnButtonGain10B2();
	afx_msg void OnButtonGain100B2();

	afx_msg void OnButtonLedOff3();
	afx_msg void OnButtonLedOn3();
	afx_msg void OnButtonGain1A3();
	afx_msg void OnButtonGain10A3();
	afx_msg void OnButtonGain100A3();
	afx_msg void OnButtonGain1B3();
	afx_msg void OnButtonGain10B3();
	afx_msg void OnButtonGain100B3();

	afx_msg void OnButtonLedOff4();
	afx_msg void OnButtonLedOn4();
	afx_msg void OnButtonGain1A4();
	afx_msg void OnButtonGain10A4();
	afx_msg void OnButtonGain100A4();
	afx_msg void OnButtonGain1B4();
	afx_msg void OnButtonGain10B4();
	afx_msg void OnButtonGain100B4();

	afx_msg void OnButtonLedOff5();
	afx_msg void OnButtonLedOn5();
	afx_msg void OnButtonGain1A5();
	afx_msg void OnButtonGain10A5();
	afx_msg void OnButtonGain100A5();
	afx_msg void OnButtonGain1B5();
	afx_msg void OnButtonGain10B5();
	afx_msg void OnButtonGain100B5();

	afx_msg void OnButtonLedOff6();
	afx_msg void OnButtonLedOn6();
	afx_msg void OnButtonGain1A6();
	afx_msg void OnButtonGain10A6();
	afx_msg void OnButtonGain100A6();
	afx_msg void OnButtonGain1B6();
	afx_msg void OnButtonGain10B6();
	afx_msg void OnButtonGain100B6();

	afx_msg void OnButtonLedOff7();
	afx_msg void OnButtonLedOn7();
	afx_msg void OnButtonGain1A7();
	afx_msg void OnButtonGain10A7();
	afx_msg void OnButtonGain100A7();
	afx_msg void OnButtonGain1B7();
	afx_msg void OnButtonGain10B7();
	afx_msg void OnButtonGain100B7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTISIGPP_H__45285511_5765_4615_8593_D555A78867E3__INCLUDED_)
