// ME8100DemoDlg.h : header file
//

#if !defined(AFX_ME8100DEMODLG_H__AF20A16E_FFE8_11D2_9EF8_0020A90C91B5__INCLUDED_)
#define AFX_ME8100DEMODLG_H__AF20A16E_FFE8_11D2_9EF8_0020A90C91B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CME8100DemoDlg dialog

#define INT_DISABLED	0
#define INT_ENABLED		1

#define TRISTATE_OFF	0
#define TRISTATE_ON		1

class CME8100DemoDlg : public CDialog
{
// Construction
public:
	CME8100DemoDlg(CWnd* pParent = NULL);	// standard constructor

	// Routines for the irq-functions
	void BlinkIntAOn(void);

	void BlinkIntAOff(void);

// Dialog Data
	//{{AFX_DATA(CME8100DemoDlg)
	enum { IDD = IDD_ME8100DEMO_DIALOG };
	CComboBox	m_comboSetBitNumber;
	CComboBox	m_comboGetBitNumber;
	CComboBox	m_comboCounterNumber;
	CComboBox	m_comboCounterMode;
	CComboBox	m_comboBoards;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CME8100DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	public:
	
	BOOL m_bDisplayed;			// Prevents the IRQ-function from accessing the dialog before
								// or after it is displayed
	
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CME8100DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonReadInput();
	afx_msg void OnButtonWriteOutput();
	afx_msg void OnButtonSetMask();
	afx_msg void OnButtonSetPattern();
	afx_msg void OnRadioDisableInt();
	afx_msg void OnRadioEnableInt();
	afx_msg void OnRadioIntBitChange();
	afx_msg void OnRadioIntPatternCompare();
	afx_msg void OnRadioSink();
	afx_msg void OnRadioSource();
	afx_msg void OnRadioTristateOff();
	afx_msg void OnRadioTristateOn();
	afx_msg void OnClose();
	afx_msg void OnSelChangeBoardCombo();
	afx_msg void OnButtonChangeRegisterSet();
	afx_msg void OnButtonGetBit();
	afx_msg void OnButtonReadCounter();
	afx_msg void OnButtonWriteCounter();
	afx_msg void OnButtonSetBit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	int		m_iCurrentBoardIndex;	// Index of currently displayed board

	int		m_iCurrentRegisterSet;	// Currently displayed register set REGISTER_SET_A / REGISTER_SET_B

	int		m_iIntStatus;			// Int status /enabled/disabled) for current board and current register set.
	
	struct SBoardSettings
	{
		int		m_iIntMode;			// INTERRUPT_ON_PATTERN_COMPARE / INTERRUPT_ON_BIT_CHANGE
	
		int		m_iTristateMode;	// TRISTATE_OFF / TRISTATE_ON

		int		m_iSinkOrSource;	// SINK_MODE / SOURCE_MODE

		WORD	m_wPattern;

		WORD	m_wMask;

		CString m_csStatus;

		CString m_csIRQCount;
	}
	m_arrayBoardSettings[32][2];	// Structure for each register set for each board.

	void ReinitialiseBoard(int board_index);

	void SetDialogElements(void);

	void DlgSetDigitalInput(unsigned short w_set);

	unsigned short DlgGetDigitalOutput(void);

	void DlgClearDigitalOutput(void);

	unsigned short DlgGetPattern(void);

	void DlgSetPattern(void);
	
	unsigned short DlgGetMask(void);

	void DlgSetMask(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ME8100DEMODLG_H__AF20A16E_FFE8_11D2_9EF8_0020A90C91B5__INCLUDED_)
