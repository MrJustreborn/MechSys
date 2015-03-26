#if !defined(AFX_DIGITALIOPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_)
#define AFX_DIGITALIOPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DigitalIOPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDigitalIOPP dialog

struct SMEDIOPort
{
	int	m_iDirection;

	unsigned char	m_ucInputByteValue;

	unsigned int	m_uiInputBit;

	BOOL			m_bInputBitValue;

	unsigned char	m_ucOutputByteValue;

	unsigned int	m_uiOutputBit;

	unsigned int	m_bOutputBitValue;
};

struct SMEBoardDIO
{
	BOOL		m_bPortsAandBBidirectional;
	
	SMEDIOPort	m_sDIOPort[4];
};


	
class CDigitalIOPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CDigitalIOPP)

// Construction
public:
	CDigitalIOPP();
	~CDigitalIOPP();

// Dialog Data
	//{{AFX_DATA(CDigitalIOPP)
	enum { IDD = IDD_DIGITALIO_PP };
	CComboBox	m_comboBoardNumber;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	CPropertySheet*	m_pPropertySheet;

private:

	SMEBoardDIO	m_sBoardDIO[ME4000_MAX_DEVICES];

	int m_iRadioDirectionInputID[4];

	int m_iInputBitID[4][8];

	int m_iInputByteButtonID[4];

	int m_iOutputBitID[4][8];

	int m_iOutputByteButtonID[4];

	int m_iInputBitValueID[4];

	int m_iInputBitButtonID[4];

	int m_iOutputBitValueID[4];

	int m_iOutputBitButtonID[4];

	int m_iCurrentBoardIndex;

	CComboBox m_comboOutputBitNumber[4];
	CComboBox m_comboInputBitNumber[4];


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDigitalIOPP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDigitalIOPP)
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	afx_msg void OnRadioInputA();
	afx_msg void OnRadioOutputA();
	afx_msg void OnButtonInputByteA();
	afx_msg void OnButtonOutputByteA();
	afx_msg void OnButtonInputBitA();
	afx_msg void OnButtonOutputBitA();
	afx_msg void OnRadioInputB();
	afx_msg void OnRadioOutputB();
	afx_msg void OnButtonInputByteB();
	afx_msg void OnButtonOutputByteB();
	afx_msg void OnButtonInputBitB();
	afx_msg void OnButtonOutputBitB();
	afx_msg void OnRadioInputC();
	afx_msg void OnRadioOutputC();
	afx_msg void OnButtonInputByteC();
	afx_msg void OnButtonOutputByteC();
	afx_msg void OnButtonInputBitC();
	afx_msg void OnButtonOutputBitC();
	afx_msg void OnRadioInputD();
	afx_msg void OnRadioOutputD();
	afx_msg void OnButtonInputByteD();
	afx_msg void OnButtonOutputByteD();
	afx_msg void OnButtonInputBitD();
	afx_msg void OnButtonOutputBitD();
	afx_msg void OnResetAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void OnRadioInput(int index_port);
	
	void OnRadioOutput(int index_port);
	
	void OnButtonInputByte(int index_port);
	
	void OnButtonOutputByte(int index_port);
	
	void OnButtonInputBit(int index_port);
	
	void OnButtonOutputBit(int index_port);

	void SetControlStates(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGITALIOPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_)
