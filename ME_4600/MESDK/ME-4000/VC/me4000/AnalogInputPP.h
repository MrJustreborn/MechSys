#if !defined(AFX_ANALOGINPUTPP_H__98A23135_821E_4241_9786_98AEF3D91B50__INCLUDED_)
#define AFX_ANALOGINPUTPP_H__98A23135_821E_4241_9786_98AEF3D91B50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnalogInputPP.h : header file
//

#include "ColourBox.h"

/////////////////////////////////////////////////////////////////////////////
// CAnalogInputPP dialog

#define AI_SINGLE		0
#define AI_SCAN			1
#define AI_CONTINUOUS	2
#define AI_NONE			3	// For m_iLastOperation
	
class CAnalogInputPP;

struct SMEBoardAI
{
	CAnalogInputPP*	m_pAnalogInputPP;	
	
	// Control settings
	
	int				m_iFunction;
	
	BOOL			m_bChannelActive[4];

	unsigned int	m_uiChannelNumber[4];
	
	int				m_iChannelRange[4];

	int				m_iSDMode;

	int				m_iTriggerSingleMode;		// For AISingle

	int				m_iTriggerExtMode;			// For AIScan and AIContinuous

	int				m_iTriggerExtEdge;

	unsigned int	m_uiNumberOfChannelLists;	// For AIScan

	double			m_dWindowWidthSeconds;		// For AIContinuous - Acq mode ME4000_AI_ACQ_MODE_SOFTWARE and ME4000_AI_ACQ_MODE_EXT

	unsigned int	m_uiWindowWidthValues;		// For AIContinuous - Acq mode ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE and ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST

	int				m_iAcquisitionMode;			

	double			m_dSampleRate;

	unsigned int	m_uiRefresh;	

	unsigned long	m_ulTimeout;

	BOOL			m_bSampleAndHold;

	// Internal state

	int				m_iLastOperation;

	BOOL			m_bAIActive;

	int				m_iLastError;

	// AISingle		
	
	unsigned int	m_uiSingleChannel;
	
	double			m_sSingleValueVolt;

	// AIScan and AIContinuous
	
	unsigned int	m_uiCurrentNumberOfChannels;
		
	COLORREF		m_crCurrentChanColours[4];
	
	unsigned int	m_uiCurrentChanNumber[4];

	int				m_iCurrentChanRange[4];

	unsigned char	m_ucChanList[4];

	double			m_dXIncrement;

	double			m_dYFactor[4];

	double			m_dYConstant[4];

	// AIScan

	short*			m_psScanBuffer;

	unsigned int	m_uiScanBufferSizeValues;

	unsigned int	m_uiNumberOfScanData;

	unsigned int	m_uiCurrentNumberofChanLists;

	// AIContinuous

	BOOL			m_bFirstDraw;
	
	double			m_dXLastPixel;
	
	int				m_iXLastPixel;
	
	int				m_iYLastPixel[4];
};

class CAnalogInputPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CAnalogInputPP)

// Construction
public:
	CAnalogInputPP();
	~CAnalogInputPP();

// Dialog Data
	//{{AFX_DATA(CAnalogInputPP)
	enum { IDD = IDD_AI_PP };
	CProgressCtrl	m_progressScan;
	CSpinButtonCtrl	m_spinRefresh;
	CSpinButtonCtrl	m_spinWindowWidthValue;
	CSpinButtonCtrl	m_spinTimeout;
	CSpinButtonCtrl	m_spinSampleRate;
	CSpinButtonCtrl	m_spinNoOfChannelLists;
	CComboBox	m_comboBoardNumber;
	//}}AFX_DATA

	CPropertySheet*	m_pPropertySheet;

private:

	SMEBoardAI	m_sBoardAI[ME4000_MAX_DEVICES];

	CComboBox	m_comboNumberChannel[4];
	CComboBox	m_comboRangeChannel[4];

	int m_iCurrentBoardIndex;

	CColourBox m_cbChannel[4];

	CWnd*		m_pPlotWin;
	
	CRect		m_rectPlotClient;

	CRect		m_rectPlotChild;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAnalogInputPP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAnalogInputPP)
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	afx_msg void OnRadioAISingle();
	afx_msg void OnRadioAIScan();
	afx_msg void OnRadioAIContinuous();
	afx_msg void OnCheckChannel1();
	afx_msg void OnCheckChannel2();
	afx_msg void OnCheckChannel3();
	afx_msg void OnCheckChannel4();
	afx_msg void OnRadioTriggerTypeAnalog();
	afx_msg void OnRadioTriggerTypeDigital();
	afx_msg void OnRadioTriggerTypeSoftware();
	afx_msg void OnRadioContSw();
	afx_msg void OnRadioContEt();
	afx_msg void OnRadioContEtValue();
	afx_msg void OnRadioContEtChanlist();
	afx_msg void OnStartSample();
	afx_msg void OnStop();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	static void _stdcall ScanCallback(short* psValues, unsigned int uiNumberOfValues, 
												void* pCallbackContext, int iLastError);

	static void _stdcall ScanTerminate(short* psValues, unsigned int uiNumberOfValues, 
												void* pTerminateContext, int iLastError);

	static void _stdcall ContinuousCallback(short* psValues, unsigned int uiNumberOfValues, 
														void* pCallbackContext, int iLastError);

	void SetControlStates(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALOGINPUTPP_H__98A23135_821E_4241_9786_98AEF3D91B50__INCLUDED_)
