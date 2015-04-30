// ME630DemoDlg.h : header file
//

#if !defined(AFX_ME630DEMODLG_H__501A9C29_F65E_11D3_A05E_0020A90C91B5__INCLUDED_)
#define AFX_ME630DEMODLG_H__501A9C29_F65E_11D3_A05E_0020A90C91B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CME630DemoDlg dialog

#include "..\meDefs.h"

class CME630DemoDlg : public CDialog
{
// Construction
public:
	CME630DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CME630DemoDlg)
	enum { IDD = IDD_ME630DEMO_DIALOG };
	CComboBox	m_comboDIOSetBit;
	CComboBox	m_comboDIOGetBit;
	CComboBox	m_comboSetRelayBitNumber;
	CComboBox	m_comboGetTTLBitNumber;
	CComboBox	m_comboGetRelayBitNumber;
	CComboBox	m_comboGetOptoBitNumber;
	CComboBox	m_comboBoardNumber;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CME630DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CME630DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelChangeBoardCombo();
	afx_msg void OnButtonGetOptoBit();
	afx_msg void OnButtonGetOptoByte();
	afx_msg void OnButtonGetRelayBit();
	afx_msg void OnButtonGetRelayWord();
	afx_msg void OnButtonGetTtlBit();
	afx_msg void OnButtonGetTtlByte();
	afx_msg void OnButtonSetRelayBit();
	afx_msg void OnButtonSetRelayWord();
	afx_msg void OnRadioIRQ1Disable();
	afx_msg void OnRadioIRQ1Enable();
	afx_msg void OnRadioIRQ2Disable();
	afx_msg void OnRadioIRQ2Enable();
	afx_msg void OnButtonDioResetAll();
	afx_msg void OnButtonDioConfig();
	afx_msg void OnButtonDioGetByte();
	afx_msg void OnButtonDioGetBit();
	afx_msg void OnButtonDioSetByte();
	afx_msg void OnButtonDioSetBit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

	int		m_iCurrentBoardIndex;				// Index of currently displayed board

	void UpdateIRQ1Count(void);

	void UpdateIRQ2Count(void);

private:

	BOOL m_bIntEnabled[ME_MAX_DEVICES][2];	// Interrupt Enaabled/Disabled for each 
												// interrupt (1 or 2) on each board

	void ReinitialiseBoard(int board_index);

	void SetDialogElements(void);

	void InitialiseSetRelayWordCheckBoxes(unsigned short us_value);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ME630DEMODLG_H__501A9C29_F65E_11D3_A05E_0020A90C91B5__INCLUDED_)
