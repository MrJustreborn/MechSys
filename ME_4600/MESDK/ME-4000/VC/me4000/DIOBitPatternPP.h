#if !defined(AFX_DIOBitPatternPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_)
#define AFX_DIOBitPatternPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DIOBitPatternPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDIOBitPatternPP dialog

#define DIOBP_WRAPAROUND	0
#define DIOBP_CONTINUOUS	1
#define DIOBP_NONE			2

class CDIOBitPatternPP;

struct SMEBoardDIOBP
{
	CDIOBitPatternPP*	m_pDIOBitPatternPP;
	
	int					m_iIndexBoard;		
	
	BOOL				m_bOptoIsolated;
	
	// Control settings
	
	BOOL				m_bUsePort[4];
	
	int					m_iPortOutputMode[4];
	
	int					m_iFunction;
	
	int					m_iTriggerMode;	

	int					m_iTriggerExtEdge;
	
	unsigned int		m_uiOutputRate;

	BOOL				m_bInfiniteLoops;

	unsigned int		m_uiFiniteLoops;

	unsigned long		m_ulTimeout;

	// Internal state

	int					m_iLastOperation;

	BOOL				m_bDIOBPActive;

	int					m_iLastError;

	short*				m_psDataBuffer;

	unsigned long		m_ulNumberOfData;	

	unsigned long		m_ulDataBufferSizeValues;

	// AOContinuous

	BOOL				m_bAppendBuffer;

	unsigned int		m_uiAppendOffset;

	unsigned long		m_ulSizeOfAppend;
};

class CDIOBitPatternPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CDIOBitPatternPP)

// Construction
public:
	CDIOBitPatternPP();
	~CDIOBitPatternPP();

// Dialog Data
	//{{AFX_DATA(CDIOBitPatternPP)
	enum { IDD = IDD_DIO_BIT_PATTERN_PP };
	CSpinButtonCtrl	m_spinTimeout;
	CSpinButtonCtrl	m_spinOutputRate;
	CSpinButtonCtrl	m_spinLoopFinite;
	CListCtrl	m_listData;
	CComboBox	m_comboBoardNumber;
	//}}AFX_DATA

	CPropertySheet*	m_pPropertySheet;

private:

	SMEBoardDIOBP m_sBoardDIOBP[ME4000_MAX_DEVICES];
	
	int     m_iCheckPortID[4];

	int     m_iRadioLowByteID[4];

	int     m_iRadioHighByteID[4];

	short*			m_psGlobalDataBuffer;

	unsigned long	m_ulNumberOfGlobalData;

	int m_iCurrentBoardIndex;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDIOBitPatternPP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDIOBitPatternPP)
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	afx_msg void OnCheckPortA();
	afx_msg void OnCheckPortB();
	afx_msg void OnCheckPortC();
	afx_msg void OnCheckPortD();
	afx_msg void OnRadioDiobpWraparound();
	afx_msg void OnRadioDiobpContinuous();
	afx_msg void OnRadioTriggerSoftware();
	afx_msg void OnRadioTriggerDigital();
	afx_msg void OnRadioLoopEndless();
	afx_msg void OnRadioLoopFinite();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void OnCheckPort(int index_port);
	
	void SetControlStates(void);

	static void _stdcall WraparoundTerminate(void* pTerminateContext);

	static void _stdcall ContinuousCallback(unsigned long ulBufferAvailable, void* pCallbackContext);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIOBitPatternPP_H__7FFD6E96_C854_4EA8_B992_82189C145512__INCLUDED_)
