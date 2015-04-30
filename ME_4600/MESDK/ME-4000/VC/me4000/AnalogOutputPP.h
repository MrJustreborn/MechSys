#if !defined(AFX_ANALOGOUTPUTPP_H__98A23135_821E_4241_9786_98AEF3D91B50__INCLUDED_)
#define AFX_ANALOGOUTPUTPP_H__98A23135_821E_4241_9786_98AEF3D91B50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnalogOutputPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnalogOutputPP dialog

// Function

#define AO_FUNCTION_SINGLE					0
#define AO_FUNCTION_SINGLE_SIMULTANEOUS		1
#define AO_FUNCTION_START					2
#define AO_FUNCTION_START_SYNCHRONOUS		3
#define AO_FUNCTION_NONE					3
	
// Buffer mode

#define AO_BUFFER_MODE_WRAPAROUND			0
#define AO_BUFFER_MODE_CONTINUOUS			1
#define AO_BUFFER_MODE_NONE					2

// Trigger type

#define AO_TRIGGER_TYPE_SOFTWARE			0
#define AO_TRIGGER_TYPE_EXT_DIGITAL			1

// Trigger Ext Edge

#define AO_TRIGGER_EXT_EDGE_RISING			0
#define AO_TRIGGER_EXT_EDGE_FALLING			1
#define AO_TRIGGER_EXT_EDGE_BOTH			2

#define MIN_OUTPUT_RATE		1
#define MAX_OUTPUT_RATE		500000
	
#define MIN_SIGNAL_LENGTH	1
#define MAX_SIGNAL_LENGTH	3600
	
#define MIN_FREQ			1
#define MAX_FREQ			20
	
#define MIN_AMP				0
#define MAX_AMP				10
	
class CAnalogOutputPP;

struct SMEAOChannel
{
	CAnalogOutputPP*	m_pAnalogOutputPP;
	
	int					m_iIndexBoard;
	
	int					m_iIndexChannel;
	
	// Control settings
	
	int					m_iFunction;
	
	int					m_iBufferMode;			// AOWraparound, AOContinuous

	BOOL				m_bExtTriggerEnable;
	
	int					m_iTriggerType;
	
	int					m_iTriggerExtEdge;
	
	unsigned int		m_uiOutputRate;

	unsigned int		m_uiSignalLengthSeconds;

	int					m_iOutputSignalForm;

	unsigned int		m_uiSweepFrequencyFrom;

	unsigned int		m_uiSweepFrequencyTo;

	unsigned int		m_uiSweepAmplitudeFrom;

	unsigned int		m_uiSweepAmplitudeTo;

	double				m_dSingleValue;

	BOOL				m_bInfiniteLoops;

	unsigned int		m_uiFiniteLoops;

	unsigned long		m_ulTimeout;

	// Internal state

	int					m_iLastBufferMode;

	BOOL				m_bAOActive;

	int					m_iLastError;

	// AOWraparound and AOContinuous

	short*				m_psDataBuffer;

	unsigned long		m_ulDataBufferSizeValues;

	// AOContinuous

	BOOL				m_bAppendBuffer;

	unsigned int		m_uiAppendOffset;

	unsigned long		m_ulSizeOfAppend;
};

struct SMEBoardAO
{
	struct SMEAOChannel	m_sAOChannel[4];

	int					m_iSingleSimultaneousTrigger;

	unsigned long		m_ulSingleSimultaneousTimeout;

	int					m_iStartSynchronousTrigger;

	unsigned long		m_ulStartSynchronousTimeout;
};

class CAnalogOutputPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CAnalogOutputPP)

// Construction
public:
	CAnalogOutputPP();
	~CAnalogOutputPP();

// Dialog Data
	//{{AFX_DATA(CAnalogOutputPP)
	enum { IDD = IDD_AO_PP };
	CComboBox	m_comboBoardNumber;
	//}}AFX_DATA

public:

	CPropertySheet*	m_pPropertySheet;

private:

	SMEBoardAO	m_sBoardAO[ME4000_MAX_DEVICES];

	int		m_iComboFunctionID[4];

	int		m_iRadioAOModeWraparoundID[4];
	int		m_iRadioAOModeContinuousID[4];

	int		m_iCheckEnableExtTriggerID[4];

	int		m_iRadioTriggerSoftwareID[4];
	int		m_iRadioTriggerExtDigitalID[4];

	int		m_iRadioTriggerRisingID[4];
	int		m_iRadioTriggerFallingID[4];
	int		m_iRadioTriggerBothID[4];

	int		m_iEditOutputRateID[4];
	int		m_iSpinOutputRateID[4];

	int		m_iEditSignalLengthID[4];
	int		m_iSpinSignalLengthID[4];

	int     m_iComboSignalFormID[4];

	int     m_iEditFrequencyFromID[4];
	int     m_iSpinFrequencyFromID[4];

	int     m_iEditFrequencyToID[4];
	int     m_iSpinFrequencyToID[4];

	int     m_iEditAmplitudeFromID[4];
	int     m_iSpinAmplitudeFromID[4];

	int     m_iEditAmplitudeToID[4];
	int     m_iSpinAmplitudeToID[4];

	int		m_iEditOutputSingleID[4];

	int     m_iRadioLoopEndlessID[4];
	int     m_iRadioLoopFiniteID[4];
	int     m_iEditLoopFiniteID[4];
	int     m_iSpinLoopFiniteID[4];
	
	int     m_iEditTimeoutID[4];
	int     m_iSpinTimeoutID[4];

	int		m_iButtonStartAppendOutputID[4];
	int		m_iButtonStopID[4];

	int		m_iPlotID[4];	
	int		m_iScrollbarPlotID[4];	
	
	CComboBox m_comboFunction[4];

	CSpinButtonCtrl	m_spinOutputRate[4];
	
	CSpinButtonCtrl	m_spinSignalLength[4];
	
	CComboBox m_comboSignalForm[4];

	CSpinButtonCtrl	m_spinFrequencyFrom[4];
	CSpinButtonCtrl	m_spinFrequencyTo[4];
	
	CSpinButtonCtrl	m_spinAmplitudeFrom[4];
	CSpinButtonCtrl	m_spinAmplitudeTo[4];

	CSpinButtonCtrl	m_spinLoopFinite[4];

	CSpinButtonCtrl	m_spinTimeout[4];

	CSpinButtonCtrl	m_spinSingleSimultaneousTimeout;

	CSpinButtonCtrl	m_spinStartSynchronousTimeout;

	CWnd* m_pPlotWin[4];
	
	CRect m_rectPlotClient[4];

	CRect m_rectPlotChild[4];

	int m_iCurrentBoardIndex;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAnalogOutputPP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAnalogOutputPP)
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	afx_msg void OnRadioAoWraparound1();
	afx_msg void OnRadioAoContinuous1();
	afx_msg void OnRadioTriggerSoftware1();
	afx_msg void OnRadioTriggerDigital1();
	afx_msg void OnCheckEnableExtTrigger1();
	afx_msg void OnRadioLoopEndless1();
	afx_msg void OnRadioLoopFinite1();
	afx_msg void OnButtonStartAppendOutput1();
	afx_msg void OnButtonStop1();
	afx_msg void OnRadioAoWraparound2();
	afx_msg void OnRadioAoContinuous2();
	afx_msg void OnRadioTriggerSoftware2();
	afx_msg void OnRadioTriggerDigital2();
	afx_msg void OnCheckEnableExtTrigger2();
	afx_msg void OnRadioLoopEndless2();
	afx_msg void OnRadioLoopFinite2();
	afx_msg void OnButtonStartAppendOutput2();
	afx_msg void OnButtonStop2();
	afx_msg void OnRadioAoWraparound3();
	afx_msg void OnRadioAoContinuous3();
	afx_msg void OnRadioTriggerSoftware3();
	afx_msg void OnRadioTriggerDigital3();
	afx_msg void OnCheckEnableExtTrigger3();
	afx_msg void OnRadioLoopEndless3();
	afx_msg void OnRadioLoopFinite3();
	afx_msg void OnButtonStartAppendOutput3();
	afx_msg void OnButtonStop3();
	afx_msg void OnRadioAoWraparound4();
	afx_msg void OnRadioAoContinuous4();
	afx_msg void OnRadioTriggerSoftware4();
	afx_msg void OnRadioTriggerDigital4();
	afx_msg void OnCheckEnableExtTrigger4();
	afx_msg void OnRadioLoopEndless4();
	afx_msg void OnRadioLoopFinite4();
	afx_msg void OnButtonStartAppendOutput4();
	afx_msg void OnButtonStop4();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSingleSimultaneous();
	afx_msg void OnStartSynchronous();
	afx_msg void OnPaint();
	afx_msg void OnChangeEditOutputSingle1();
	afx_msg void OnSelchangeComboFunction1();
	afx_msg void OnSelchangeComboSignalForm1();
	afx_msg void OnKillfocusEditOutputRate1();
	afx_msg void OnKillfocusEditSignalLength1();
	afx_msg void OnKillfocusEditFrequencyFrom1();
	afx_msg void OnKillfocusEditFrequencyTo1();
	afx_msg void OnKillfocusEditAmplitudeFrom1();
	afx_msg void OnKillfocusEditAmplitudeTo1();
	afx_msg void OnChangeEditOutputSingle2();
	afx_msg void OnSelchangeComboFunction2();
	afx_msg void OnSelchangeComboSignalForm2();
	afx_msg void OnKillfocusEditOutputRate2();
	afx_msg void OnKillfocusEditSignalLength2();
	afx_msg void OnKillfocusEditFrequencyFrom2();
	afx_msg void OnKillfocusEditFrequencyTo2();
	afx_msg void OnKillfocusEditAmplitudeFrom2();
	afx_msg void OnKillfocusEditAmplitudeTo2();
	afx_msg void OnChangeEditOutputSingle3();
	afx_msg void OnSelchangeComboFunction3();
	afx_msg void OnSelchangeComboSignalForm3();
	afx_msg void OnKillfocusEditOutputRate3();
	afx_msg void OnKillfocusEditSignalLength3();
	afx_msg void OnKillfocusEditFrequencyFrom3();
	afx_msg void OnKillfocusEditFrequencyTo3();
	afx_msg void OnKillfocusEditAmplitudeFrom3();
	afx_msg void OnKillfocusEditAmplitudeTo3();
	afx_msg void OnChangeEditOutputSingle4();
	afx_msg void OnSelchangeComboFunction4();
	afx_msg void OnSelchangeComboSignalForm4();
	afx_msg void OnKillfocusEditOutputRate4();
	afx_msg void OnKillfocusEditSignalLength4();
	afx_msg void OnKillfocusEditFrequencyFrom4();
	afx_msg void OnKillfocusEditFrequencyTo4();
	afx_msg void OnKillfocusEditAmplitudeFrom4();
	afx_msg void OnKillfocusEditAmplitudeTo4();
	afx_msg void OnDeltaposSpinOutputRate1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSignalLength1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyFrom1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyTo1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeFrom1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeTo1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinOutputRate2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSignalLength2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyFrom2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyTo2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeFrom2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeTo2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinOutputRate3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSignalLength3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyFrom3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyTo3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeFrom3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeTo3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinOutputRate4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSignalLength4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyFrom4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyTo4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeFrom4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeTo4(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnRadioSingleSimultaneousSoftware();
	afx_msg void OnRadioSingleSimultaneousDigitalExt();

	afx_msg void OnRadioStartSynchronousSoftware();
	afx_msg void OnRadioStartSynchronousDigitalExt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void OnSelchangeComboFunction(int index_channel);

	void OnRadioAOWraparound(int index_channel);
	
	void OnRadioAOContinuous(int index_channel);
	
	void OnRadioTriggerSoftware(int index_channel);
	
	void OnRadioTriggerDigital(int index_channel);
	
	void OnCheckEnableExtTrigger(int index_channel);
	
	void OnRadioLoopEndless(int index_channel);
	
	void OnRadioLoopFinite(int index_channel);

	void OnButtonStartAppendOutput(int index_channel);
	
	void OnButtonStop(int index_channel);

	void OnChangeEditOutputSingle(int index_channel);

	void OnSelchangeComboSignalForm(int index_channel);

	void OnKillfocusEditOutputRate(int index_channel);

	void OnKillfocusEditSignalLength(int index_channel);

	void OnKillfocusEditFrequencyFrom(int index_channel);

	void OnKillfocusEditFrequencyTo(int index_channel);

	void OnKillfocusEditAmplitudeFrom(int index_channel);

	void OnKillfocusEditAmplitudeTo(int index_channel);

	void OnDeltaposSpinOutputRate(int index_channel, NM_UPDOWN* pNMUpDown);
		
	void OnDeltaposSpinSignalLength(int index_channel, NM_UPDOWN* pNMUpDown);
	
	void OnDeltaposSpinFrequencyFrom(int index_channel, NM_UPDOWN* pNMUpDown);
	
	void OnDeltaposSpinFrequencyTo(int index_channel, NM_UPDOWN* pNMUpDown);
	
	void OnDeltaposSpinAmplitudeFrom(int index_channel, NM_UPDOWN* pNMUpDown);
	
	void OnDeltaposSpinAmplitudeTo(int index_channel, NM_UPDOWN* pNMUpDown);

	void SetSimultaneousControls(void);
	
	void SetControlStates(void);

	static void _stdcall WraparoundTerminate(void* pTerminateContext);

	static void _stdcall ContinuousCallback(unsigned long ulBufferAvailable, void* pCallbackContext);

	int PrepareChannel(SMEAOChannel* p_ao_channel);

	void MarkChannelActive(SMEAOChannel* p_ao_channel);

	void RedrawPlot(int index_channel);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AnalogOutputPP_H__98A23135_821E_4241_9786_98AEF3D91B50__INCLUDED_)
