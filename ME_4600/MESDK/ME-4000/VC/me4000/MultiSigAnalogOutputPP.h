#if !defined(AFX_MultiSigAnalogOutputPP_H__27C6563D_356D_4E4A_B213_703CBC02915F__INCLUDED_)
#define AFX_MultiSigAnalogOutputPP_H__27C6563D_356D_4E4A_B213_703CBC02915F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultiSigAnalogOutputPP.h : header file
//

#include "ColourBox.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiSigAnalogOutputPP dialog

#define AO_SINGLE		0
#define AO_WRAPAROUND	1
#define AO_CONTINUOUS	2
#define AO_NONE			3

#define MIN_OUTPUT_RATE		1
#define MAX_OUTPUT_RATE		500000
	
#define MIN_SIGNAL_LENGTH	1
#define MAX_SIGNAL_LENGTH	3600
	
#define MIN_FREQ			1
#define MAX_FREQ			20
	
#define MIN_AMP				0
#define MAX_AMP				10
	
class CMultiSigAnalogOutputPP;

struct SMEBoardMultiSigAO
{
	CMultiSigAnalogOutputPP*	m_pMultiSigAnalogOutputPP;

	int							m_iIndexBoard;	
	
	// Control settings
	
	BOOL				m_bMultiSigAOOpen;
	
	int					m_iFunction;
	
	int					m_iTriggerMode;		

	int					m_iTriggerExtEdge;
	
	unsigned int		m_uiOutputRate;

	unsigned int		m_uiSignalLengthSeconds;

	BOOL				m_bChannelActive[4];

	unsigned int		m_uiDemuxChannelNumber[4];

	int					m_iOutputSignalForm[4];

	unsigned int		m_uiSweepFrequencyFrom[4];

	unsigned int		m_uiSweepFrequencyTo[4];

	unsigned int		m_uiSweepAmplitudeFrom[4];

	unsigned int		m_uiSweepAmplitudeTo[4];

	double				m_dSingleValue;

	BOOL				m_bInfiniteLoops;

	unsigned int		m_uiFiniteLoops;

	unsigned long		m_ulTimeout;

	// Internal state

	int					m_iLastOperation;

	BOOL				m_bAOActive;

	int					m_iLastError;

	// AOWraparound and AOContinuous

	short*				m_psDataBuffer;

	unsigned long		m_ulDataBufferSizeValues;

	// AOContinuous

	BOOL				m_bAppendBuffer;

	unsigned int		m_uiAppendOffset;

	unsigned long		m_ulSizeOfAppend;

	BOOL				m_bCurrentChannelActive[4];

	unsigned int		m_uiCurrentDemuxChanCount;
};

class CMultiSigAnalogOutputPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CMultiSigAnalogOutputPP)

// Construction
public:
	CMultiSigAnalogOutputPP();
	~CMultiSigAnalogOutputPP();

// Dialog Data
	//{{AFX_DATA(CMultiSigAnalogOutputPP)
	enum { IDD = IDD_MULTISIGAO_PP };
	CComboBox	m_comboBoardNumber;
	//}}AFX_DATA


	CPropertySheet*	m_pPropertySheet;

private:

	SMEBoardMultiSigAO	m_sBoardMultiSigAO[ME4000_MAX_DEVICES];

	int     m_iCheckChannelID[4];

	int     m_iComboDemuxChannelNumberID[4];

	int     m_iComboSignalFormID[4];

	int     m_iEditFrequencyFromID[4];
	int     m_iSpinFrequencyFromID[4];

	int     m_iEditFrequencyToID[4];
	int     m_iSpinFrequencyToID[4];

	int     m_iEditAmplitudeFromID[4];
	int     m_iSpinAmplitudeFromID[4];

	int     m_iEditAmplitudeToID[4];
	int     m_iSpinAmplitudeToID[4];

	CSpinButtonCtrl	m_spinOutputRate;

	CSpinButtonCtrl	m_spinSignalLength;

	CSpinButtonCtrl	m_spinLoopFinite;

	CSpinButtonCtrl	m_spinTimeout;
	
	CComboBox m_comboDemuxChannelNumber[4];

	CColourBox m_cbDemuxChannel[4];

	CComboBox m_comboSignalForm[4];

	CSpinButtonCtrl	m_spinFrequencyFrom[4];
	CSpinButtonCtrl	m_spinFrequencyTo[4];
	
	CSpinButtonCtrl	m_spinAmplitudeFrom[4];
	CSpinButtonCtrl	m_spinAmplitudeTo[4];

	CColourBox m_cbChannel[4];

	CWnd* m_pPlotWin;
	
	CRect m_rectPlotClient;

	CRect m_rectPlotChild;

	int m_iCurrentBoardIndex;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMultiSigAnalogOutputPP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMultiSigAnalogOutputPP)
	afx_msg void OnExit();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnRadioAOSingle();
	afx_msg void OnRadioAOWraparound();
	afx_msg void OnRadioAOContinuous();
	afx_msg void OnRadioTriggerSoftware();
	afx_msg void OnRadioTriggerDigital();
	afx_msg void OnRadioLoopEndless();
	afx_msg void OnRadioLoopFinite();
	afx_msg void OnKillfocusEditOutputRate();
	afx_msg void OnKillfocusEditSignalLength();
	afx_msg void OnDeltaposSpinOutputRate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSignalLength(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditOutputSingle();
	afx_msg void OnCheckChannel1();
	afx_msg void OnSelchangeComboSignalFormM1();
	afx_msg void OnKillfocusEditFrequencyFromM1();
	afx_msg void OnKillfocusEditFrequencyToM1();
	afx_msg void OnKillfocusEditAmplitudeFromM1();
	afx_msg void OnKillfocusEditAmplitudeToM1();
	afx_msg void OnDeltaposSpinFrequencyToM1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyFromM1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeFromM1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeToM1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckChannel2();
	afx_msg void OnSelchangeComboSignalFormM2();
	afx_msg void OnKillfocusEditFrequencyFromM2();
	afx_msg void OnKillfocusEditFrequencyToM2();
	afx_msg void OnKillfocusEditAmplitudeFromM2();
	afx_msg void OnKillfocusEditAmplitudeToM2();
	afx_msg void OnDeltaposSpinFrequencyToM2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyFromM2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeFromM2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeToM2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckChannel3();
	afx_msg void OnSelchangeComboSignalFormM3();
	afx_msg void OnKillfocusEditFrequencyFromM3();
	afx_msg void OnKillfocusEditFrequencyToM3();
	afx_msg void OnKillfocusEditAmplitudeFromM3();
	afx_msg void OnKillfocusEditAmplitudeToM3();
	afx_msg void OnDeltaposSpinFrequencyToM3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyFromM3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeFromM3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeToM3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckChannel4();
	afx_msg void OnSelchangeComboSignalFormM4();
	afx_msg void OnKillfocusEditFrequencyFromM4();
	afx_msg void OnKillfocusEditFrequencyToM4();
	afx_msg void OnKillfocusEditAmplitudeFromM4();
	afx_msg void OnKillfocusEditAmplitudeToM4();
	afx_msg void OnDeltaposSpinFrequencyToM4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinFrequencyFromM4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeFromM4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinAmplitudeToM4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMultisigaoOpenClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void OnCheckChannel(int index_channel);

	void OnSelchangeComboSignalForm(int index_channel);

	void OnKillfocusEditFrequencyFrom(int index_channel);
	
	void OnKillfocusEditFrequencyTo(int index_channel);
	
	void OnKillfocusEditAmplitudeFrom(int index_channel);
	
	void OnKillfocusEditAmplitudeTo(int index_channel);
	
	void OnDeltaposSpinFrequencyFrom(int index_channel, NM_UPDOWN* pNMUpDown);
	
	void OnDeltaposSpinFrequencyTo(int index_channel, NM_UPDOWN* pNMUpDown);
	
	void OnDeltaposSpinAmplitudeFrom(int index_channel, NM_UPDOWN* pNMUpDown);
	
	void OnDeltaposSpinAmplitudeTo(int index_channel, NM_UPDOWN* pNMUpDown);
	
	void SetControlStates(void);

	void RedrawPlot();

	static void _stdcall WraparoundTerminate(void* pTerminateContext);

	static void _stdcall ContinuousCallback(unsigned long ulBufferAvailable, void* pCallbackContext);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MultiSigAnalogOutputPP_H__27C6563D_356D_4E4A_B213_703CBC02915F__INCLUDED_)
