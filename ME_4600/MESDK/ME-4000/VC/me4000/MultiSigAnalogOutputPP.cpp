// MultiSigAnalogOutputPP.cpp : implementation file
//

#include "stdafx.h"
#include "me4000.h"
#include "MultiSigAnalogOutputPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "WinSweep.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiSigAnalogOutputPP property page

IMPLEMENT_DYNCREATE(CMultiSigAnalogOutputPP, CPropertyPage)

static LOGFONT lf_text = {-72, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 
							OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
							DEFAULT_QUALITY, DEFAULT_PITCH|FF_ROMAN, "Arial" };

const COLORREF channel_colors[4] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0) };

CMultiSigAnalogOutputPP::CMultiSigAnalogOutputPP() : CPropertyPage(CMultiSigAnalogOutputPP::IDD)
{
	//{{AFX_DATA_INIT(CMultiSigAnalogOutputPP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	for(int index_board = 0; index_board < ME4000_MAX_DEVICES; index_board++)
	{
		m_sBoardMultiSigAO[index_board].m_pMultiSigAnalogOutputPP = this;
	
		m_sBoardMultiSigAO[index_board].m_iIndexBoard = index_board;
	
		m_sBoardMultiSigAO[index_board].m_bMultiSigAOOpen = FALSE;
	
		m_sBoardMultiSigAO[index_board].m_iFunction	= AO_SINGLE;
	
		m_sBoardMultiSigAO[index_board].m_iTriggerMode = ME4000_AO_TRIGGER_SOFTWARE;	

		m_sBoardMultiSigAO[index_board].m_iTriggerExtEdge = ME4000_AO_TRIGGER_EXT_EDGE_RISING;
	
		m_sBoardMultiSigAO[index_board].m_uiOutputRate = 1000;

		m_sBoardMultiSigAO[index_board].m_uiSignalLengthSeconds = 10;

		for(int index_channel = 0; index_channel < 4; index_channel++)
		{
			m_sBoardMultiSigAO[index_board].m_uiDemuxChannelNumber[index_channel] = index_channel;
		}

		// Make the default signals interesting
		
		m_sBoardMultiSigAO[index_board].m_bChannelActive[0] = TRUE;

		m_sBoardMultiSigAO[index_board].m_iOutputSignalForm[0] = SIGNAL_SINUS;

		m_sBoardMultiSigAO[index_board].m_uiSweepFrequencyFrom[0] = 1;

		m_sBoardMultiSigAO[index_board].m_uiSweepFrequencyTo[0] = 1;

		m_sBoardMultiSigAO[index_board].m_uiSweepAmplitudeFrom[0] = 8;

		m_sBoardMultiSigAO[index_board].m_uiSweepAmplitudeTo[0] = 8;

		m_sBoardMultiSigAO[index_board].m_bChannelActive[1] = TRUE;

		m_sBoardMultiSigAO[index_board].m_iOutputSignalForm[1] = SIGNAL_RECTANGLE;

		m_sBoardMultiSigAO[index_board].m_uiSweepFrequencyFrom[1] = 12;

		m_sBoardMultiSigAO[index_board].m_uiSweepFrequencyTo[1] = 1;

		m_sBoardMultiSigAO[index_board].m_uiSweepAmplitudeFrom[1] = 8;

		m_sBoardMultiSigAO[index_board].m_uiSweepAmplitudeTo[1] = 1;

		m_sBoardMultiSigAO[index_board].m_bChannelActive[2] = FALSE;

		m_sBoardMultiSigAO[index_board].m_iOutputSignalForm[2] = SIGNAL_TRIANGLE;

		m_sBoardMultiSigAO[index_board].m_uiSweepFrequencyFrom[2] = 12;

		m_sBoardMultiSigAO[index_board].m_uiSweepFrequencyTo[2] = 1;

		m_sBoardMultiSigAO[index_board].m_uiSweepAmplitudeFrom[2] = 1;

		m_sBoardMultiSigAO[index_board].m_uiSweepAmplitudeTo[2] = 8;

		m_sBoardMultiSigAO[index_board].m_bChannelActive[3] = FALSE;

		m_sBoardMultiSigAO[index_board].m_iOutputSignalForm[3] = SIGNAL_POS_RAMP;

		m_sBoardMultiSigAO[index_board].m_uiSweepFrequencyFrom[3] = 1;

		m_sBoardMultiSigAO[index_board].m_uiSweepFrequencyTo[3] = 12;

		m_sBoardMultiSigAO[index_board].m_uiSweepAmplitudeFrom[3] = 8;

		m_sBoardMultiSigAO[index_board].m_uiSweepAmplitudeTo[3] = 1;

		m_sBoardMultiSigAO[index_board].m_dSingleValue = 0.0;

		m_sBoardMultiSigAO[index_board].m_bInfiniteLoops = FALSE;

		m_sBoardMultiSigAO[index_board].m_uiFiniteLoops = 1;

		m_sBoardMultiSigAO[index_board].m_ulTimeout = 5;

		m_sBoardMultiSigAO[index_board].m_iLastOperation = AO_NONE;

		m_sBoardMultiSigAO[index_board].m_bAOActive = FALSE;

		m_sBoardMultiSigAO[index_board].m_iLastError = ME4000_NO_ERROR;

		m_sBoardMultiSigAO[index_board].m_psDataBuffer = NULL;

		m_sBoardMultiSigAO[index_board].m_ulDataBufferSizeValues = 0;

		m_sBoardMultiSigAO[index_board].m_bAppendBuffer = FALSE;

		m_sBoardMultiSigAO[index_board].m_uiAppendOffset = 0;

		m_sBoardMultiSigAO[index_board].m_ulSizeOfAppend = 0;
	}

	m_iCheckChannelID[0] = IDC_CHECK_CHANNEL_M1;

	m_iComboDemuxChannelNumberID[0] = IDC_COMBO_NUMBER_CHANNEL_M1;

	m_iComboSignalFormID[0] = IDC_COMBO_SIGNAL_FORM_M1;

	m_iEditFrequencyFromID[0] = IDC_EDIT_FREQUENCY_FROM_M1;
	m_iSpinFrequencyFromID[0] = IDC_SPIN_FREQUENCY_FROM_M1;

	m_iEditFrequencyToID[0] = IDC_EDIT_FREQUENCY_TO_M1;
	m_iSpinFrequencyToID[0] = IDC_SPIN_FREQUENCY_TO_M1;

	m_iEditAmplitudeFromID[0] = IDC_EDIT_AMPLITUDE_FROM_M1;
	m_iSpinAmplitudeFromID[0] = IDC_SPIN_AMPLITUDE_FROM_M1;

	m_iEditAmplitudeToID[0] = IDC_EDIT_AMPLITUDE_TO_M1;
	m_iSpinAmplitudeToID[0] = IDC_SPIN_AMPLITUDE_TO_M1;

	m_iCheckChannelID[1] = IDC_CHECK_CHANNEL_M2;

	m_iComboDemuxChannelNumberID[1] = IDC_COMBO_NUMBER_CHANNEL_M2;

	m_iComboSignalFormID[1] = IDC_COMBO_SIGNAL_FORM_M2;

	m_iEditFrequencyFromID[1] = IDC_EDIT_FREQUENCY_FROM_M2;
	m_iSpinFrequencyFromID[1] = IDC_SPIN_FREQUENCY_FROM_M2;

	m_iEditFrequencyToID[1] = IDC_EDIT_FREQUENCY_TO_M2;
	m_iSpinFrequencyToID[1] = IDC_SPIN_FREQUENCY_TO_M2;

	m_iEditAmplitudeFromID[1] = IDC_EDIT_AMPLITUDE_FROM_M2;
	m_iSpinAmplitudeFromID[1] = IDC_SPIN_AMPLITUDE_FROM_M2;

	m_iEditAmplitudeToID[1] = IDC_EDIT_AMPLITUDE_TO_M2;
	m_iSpinAmplitudeToID[1] = IDC_SPIN_AMPLITUDE_TO_M2;

	m_iCheckChannelID[2] = IDC_CHECK_CHANNEL_M3;

	m_iComboDemuxChannelNumberID[2] = IDC_COMBO_NUMBER_CHANNEL_M3;

	m_iComboSignalFormID[2] = IDC_COMBO_SIGNAL_FORM_M3;

	m_iEditFrequencyFromID[2] = IDC_EDIT_FREQUENCY_FROM_M3;
	m_iSpinFrequencyFromID[2] = IDC_SPIN_FREQUENCY_FROM_M3;

	m_iEditFrequencyToID[2] = IDC_EDIT_FREQUENCY_TO_M3;
	m_iSpinFrequencyToID[2] = IDC_SPIN_FREQUENCY_TO_M3;

	m_iEditAmplitudeFromID[2] = IDC_EDIT_AMPLITUDE_FROM_M3;
	m_iSpinAmplitudeFromID[2] = IDC_SPIN_AMPLITUDE_FROM_M3;

	m_iEditAmplitudeToID[2] = IDC_EDIT_AMPLITUDE_TO_M3;
	m_iSpinAmplitudeToID[2] = IDC_SPIN_AMPLITUDE_TO_M3;

	m_iCheckChannelID[3] = IDC_CHECK_CHANNEL_M4;

	m_iComboDemuxChannelNumberID[3] = IDC_COMBO_NUMBER_CHANNEL_M4;

	m_iComboSignalFormID[3] = IDC_COMBO_SIGNAL_FORM_M4;

	m_iEditFrequencyFromID[3] = IDC_EDIT_FREQUENCY_FROM_M4;
	m_iSpinFrequencyFromID[3] = IDC_SPIN_FREQUENCY_FROM_M4;

	m_iEditFrequencyToID[3] = IDC_EDIT_FREQUENCY_TO_M4;
	m_iSpinFrequencyToID[3] = IDC_SPIN_FREQUENCY_TO_M4;

	m_iEditAmplitudeFromID[3] = IDC_EDIT_AMPLITUDE_FROM_M4;
	m_iSpinAmplitudeFromID[3] = IDC_SPIN_AMPLITUDE_FROM_M4;

	m_iEditAmplitudeToID[3] = IDC_EDIT_AMPLITUDE_TO_M4;
	m_iSpinAmplitudeToID[3] = IDC_SPIN_AMPLITUDE_TO_M4;

	m_pPlotWin = NULL;
	
	m_rectPlotClient.SetRectEmpty();

	m_rectPlotChild.SetRectEmpty();

	m_iCurrentBoardIndex = 0;

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		m_cbChannel[index_channel].m_crBackground = RGB(0, 0, 0);
		m_cbChannel[index_channel].m_crForeground = channel_colors[index_channel];
	}

	m_pPropertySheet = NULL;
}

CMultiSigAnalogOutputPP::~CMultiSigAnalogOutputPP()
{
	for(int index_board = 0; index_board < ME4000_MAX_DEVICES; index_board++)
	{
		if(m_sBoardMultiSigAO[index_board].m_psDataBuffer != NULL)
		{
			delete m_sBoardMultiSigAO[index_board].m_psDataBuffer;
		}
	}
}

void CMultiSigAnalogOutputPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SPIN_OUTPUT_RATE, m_spinOutputRate);
	
	DDX_Control(pDX, IDC_SPIN_SIGNAL_LENGTH, m_spinSignalLength);
	
	DDX_Control(pDX, IDC_SPIN_LOOP_FINITE, m_spinLoopFinite);

	DDX_Control(pDX, IDC_SPIN_TIMEOUT, m_spinTimeout);

	DDX_Control(pDX, IDC_COMBO_NUMBER_CHANNEL_M1, m_comboDemuxChannelNumber[0]);
	
	DDX_Control(pDX, IDC_COMBO_SIGNAL_FORM_M1, m_comboSignalForm[0]);
	
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_FROM_M1, m_spinFrequencyFrom[0]);
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_TO_M1, m_spinFrequencyTo[0]);
	
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_FROM_M1, m_spinAmplitudeFrom[0]);
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_TO_M1, m_spinAmplitudeTo[0]);

	DDX_Control(pDX, IDC_COMBO_NUMBER_CHANNEL_M2, m_comboDemuxChannelNumber[1]);
	
	DDX_Control(pDX, IDC_COMBO_SIGNAL_FORM_M2, m_comboSignalForm[1]);
	
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_FROM_M2, m_spinFrequencyFrom[1]);
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_TO_M2, m_spinFrequencyTo[1]);
	
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_FROM_M2, m_spinAmplitudeFrom[1]);
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_TO_M2, m_spinAmplitudeTo[1]);

	DDX_Control(pDX, IDC_COMBO_NUMBER_CHANNEL_M3, m_comboDemuxChannelNumber[2]);
	
	DDX_Control(pDX, IDC_COMBO_SIGNAL_FORM_M3, m_comboSignalForm[2]);
	
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_FROM_M3, m_spinFrequencyFrom[2]);
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_TO_M3, m_spinFrequencyTo[2]);
	
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_FROM_M3, m_spinAmplitudeFrom[2]);
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_TO_M3, m_spinAmplitudeTo[2]);

	DDX_Control(pDX, IDC_COMBO_NUMBER_CHANNEL_M4, m_comboDemuxChannelNumber[3]);
	
	DDX_Control(pDX, IDC_COMBO_SIGNAL_FORM_M4, m_comboSignalForm[3]);
	
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_FROM_M4, m_spinFrequencyFrom[3]);
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_TO_M4, m_spinFrequencyTo[3]);
	
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_FROM_M4, m_spinAmplitudeFrom[3]);
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_TO_M4, m_spinAmplitudeTo[3]);

	//{{AFX_DATA_MAP(CMultiSigAnalogOutputPP)
	DDX_Control(pDX, IDC_COMBO_BOARD, m_comboBoardNumber);
	//}}AFX_DATA_MAP

	int i_trigger_type;
	
	int i_trigger_ext_edge;
	
	int i_loop_endless;
	
	if( !pDX->m_bSaveAndValidate )
	{
		if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction == AO_SINGLE)
		{
			i_trigger_type = 0;
		}
		else
		{
			switch(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode)
			{
			case ME4000_AO_TRIGGER_SOFTWARE:
				
				i_trigger_type = 0;

				break;

			case ME4000_AO_TRIGGER_EXT_DIGITAL:
				
				i_trigger_type = 1;

				break;
			}
		}

		switch(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerExtEdge)
		{
		case ME4000_AO_TRIGGER_EXT_EDGE_RISING:

			i_trigger_ext_edge = 0;

			break;

		case ME4000_AO_TRIGGER_EXT_EDGE_FALLING:

			i_trigger_ext_edge = 1;

			break;

		case ME4000_AO_TRIGGER_EXT_EDGE_BOTH:

			i_trigger_ext_edge = 2;

			break;
		}

		i_loop_endless = (m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bInfiniteLoops ? 0 : 1); 
	
		for(int index_channel = 0; index_channel < 4; index_channel++)
		{
			m_comboDemuxChannelNumber[index_channel].SetCurSel( (int)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiDemuxChannelNumber[index_channel] );

			m_comboSignalForm[index_channel].SetCurSel( (int)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iOutputSignalForm[index_channel] );
		}
	}

	DDX_Radio(pDX, IDC_RADIO_AO_SINGLE, m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction);

	DDX_Radio(pDX, IDC_RADIO_TRIGGER_SOFTWARE, i_trigger_type);

	DDX_Radio(pDX, IDC_RADIO_TRIGGER_RISING, i_trigger_ext_edge);

	DDX_Text(pDX, IDC_EDIT_OUTPUT_RATE, m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate);

	DDX_Text(pDX, IDC_EDIT_SIGNAL_LENGTH, m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSignalLengthSeconds);

	DDX_Radio(pDX, IDC_RADIO_LOOP_ENDLESS, i_loop_endless);

	DDX_Text(pDX, IDC_EDIT_LOOP_FINITE, m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiFiniteLoops);

	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_ulTimeout);

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		DDX_Check(pDX, m_iCheckChannelID[index_channel], m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bChannelActive[index_channel]);

		DDX_Text(pDX, m_iEditFrequencyFromID[index_channel], m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyFrom[index_channel]);

		DDX_Text(pDX, m_iEditFrequencyToID[index_channel], m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyTo[index_channel]);

		DDX_Text(pDX, m_iEditAmplitudeFromID[index_channel], m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeFrom[index_channel]);

		DDX_Text(pDX, m_iEditAmplitudeToID[index_channel], m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeTo[index_channel]);
	}

	DDX_Text(pDX, IDC_EDIT_OUTPUT_SINGLE, m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_dSingleValue);

	if(pDX->m_bSaveAndValidate)
	{
		if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction != AO_SINGLE)
		{
			switch(i_trigger_type)
			{
			case 0:
				
				m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode = ME4000_AO_TRIGGER_SOFTWARE;

				break;

			case 1:
				
				m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode = ME4000_AO_TRIGGER_EXT_DIGITAL;

				break;
			}
		}

		switch(i_trigger_ext_edge)
		{
		case 0:

			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerExtEdge = ME4000_AO_TRIGGER_EXT_EDGE_RISING;

			break;

		case 1:

			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerExtEdge = ME4000_AO_TRIGGER_EXT_EDGE_FALLING;

			break;

		case 2:

			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerExtEdge = ME4000_AO_TRIGGER_EXT_EDGE_BOTH;

			break;
		}
	
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bInfiniteLoops = ( (i_loop_endless == 0) ? TRUE : FALSE);
	
		for(int index_channel = 0; index_channel < 4; index_channel++)
		{
			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiDemuxChannelNumber[index_channel] = (unsigned int)m_comboDemuxChannelNumber[index_channel].GetCurSel();

			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iOutputSignalForm[index_channel] = (unsigned int)m_comboSignalForm[index_channel].GetCurSel();
		}
	}
}


BEGIN_MESSAGE_MAP(CMultiSigAnalogOutputPP, CPropertyPage)
	//{{AFX_MSG_MAP(CMultiSigAnalogOutputPP)
	ON_BN_CLICKED(ID_EXIT, OnExit)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_AO_SINGLE, OnRadioAOSingle)
	ON_BN_CLICKED(IDC_RADIO_AO_WRAPAROUND, OnRadioAOWraparound)
	ON_BN_CLICKED(IDC_RADIO_AO_CONTINUOUS, OnRadioAOContinuous)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_SOFTWARE, OnRadioTriggerSoftware)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_DIGITAL, OnRadioTriggerDigital)
	ON_BN_CLICKED(IDC_RADIO_LOOP_ENDLESS, OnRadioLoopEndless)
	ON_BN_CLICKED(IDC_RADIO_LOOP_FINITE, OnRadioLoopFinite)
	ON_EN_KILLFOCUS(IDC_EDIT_OUTPUT_RATE, OnKillfocusEditOutputRate)
	ON_EN_KILLFOCUS(IDC_EDIT_SIGNAL_LENGTH, OnKillfocusEditSignalLength)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OUTPUT_RATE, OnDeltaposSpinOutputRate)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIGNAL_LENGTH, OnDeltaposSpinSignalLength)
	ON_EN_CHANGE(IDC_EDIT_OUTPUT_SINGLE, OnChangeEditOutputSingle)
	ON_BN_CLICKED(IDC_CHECK_CHANNEL_M1, OnCheckChannel1)
	ON_CBN_SELCHANGE(IDC_COMBO_SIGNAL_FORM_M1, OnSelchangeComboSignalFormM1)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_FROM_M1, OnKillfocusEditFrequencyFromM1)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_TO_M1, OnKillfocusEditFrequencyToM1)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_FROM_M1, OnKillfocusEditAmplitudeFromM1)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_TO_M1, OnKillfocusEditAmplitudeToM1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_TO_M1, OnDeltaposSpinFrequencyToM1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_FROM_M1, OnDeltaposSpinFrequencyFromM1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_FROM_M1, OnDeltaposSpinAmplitudeFromM1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_TO_M1, OnDeltaposSpinAmplitudeToM1)
	ON_BN_CLICKED(IDC_CHECK_CHANNEL_M2, OnCheckChannel2)
	ON_CBN_SELCHANGE(IDC_COMBO_SIGNAL_FORM_M2, OnSelchangeComboSignalFormM2)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_FROM_M2, OnKillfocusEditFrequencyFromM2)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_TO_M2, OnKillfocusEditFrequencyToM2)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_FROM_M2, OnKillfocusEditAmplitudeFromM2)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_TO_M2, OnKillfocusEditAmplitudeToM2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_TO_M2, OnDeltaposSpinFrequencyToM2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_FROM_M2, OnDeltaposSpinFrequencyFromM2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_FROM_M2, OnDeltaposSpinAmplitudeFromM2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_TO_M2, OnDeltaposSpinAmplitudeToM2)
	ON_BN_CLICKED(IDC_CHECK_CHANNEL_M3, OnCheckChannel3)
	ON_CBN_SELCHANGE(IDC_COMBO_SIGNAL_FORM_M3, OnSelchangeComboSignalFormM3)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_FROM_M3, OnKillfocusEditFrequencyFromM3)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_TO_M3, OnKillfocusEditFrequencyToM3)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_FROM_M3, OnKillfocusEditAmplitudeFromM3)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_TO_M3, OnKillfocusEditAmplitudeToM3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_TO_M3, OnDeltaposSpinFrequencyToM3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_FROM_M3, OnDeltaposSpinFrequencyFromM3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_FROM_M3, OnDeltaposSpinAmplitudeFromM3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_TO_M3, OnDeltaposSpinAmplitudeToM3)
	ON_BN_CLICKED(IDC_CHECK_CHANNEL_M4, OnCheckChannel4)
	ON_CBN_SELCHANGE(IDC_COMBO_SIGNAL_FORM_M4, OnSelchangeComboSignalFormM4)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_FROM_M4, OnKillfocusEditFrequencyFromM4)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_TO_M4, OnKillfocusEditFrequencyToM4)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_FROM_M4, OnKillfocusEditAmplitudeFromM4)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_TO_M4, OnKillfocusEditAmplitudeToM4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_TO_M4, OnDeltaposSpinFrequencyToM4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_FROM_M4, OnDeltaposSpinFrequencyFromM4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_FROM_M4, OnDeltaposSpinAmplitudeFromM4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_TO_M4, OnDeltaposSpinAmplitudeToM4)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MULTISIGAO_OPEN_CLOSE, OnMultisigaoOpenClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiSigAnalogOutputPP message handlers

BOOL CMultiSigAnalogOutputPP::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	Cme4000App* p_app = (Cme4000App*)AfxGetApp();

	int i_number_of_boards = p_app->GetNumberOfBoards();

	CString cs_text;
	
	for(int index = 0; index < i_number_of_boards; index++)
	{
		cs_text.Format("Board %2d", index);
		
		m_comboBoardNumber.AddString(cs_text);
	}

	m_iCurrentBoardIndex = 0;
	
	m_comboBoardNumber.SetCurSel(m_iCurrentBoardIndex);

	m_pPlotWin = GetDlgItem(IDC_PLOT);
	
	CRect rect_plot;

	m_pPlotWin->GetClientRect(rect_plot);
	
	m_rectPlotClient = rect_plot;

	m_rectPlotClient.DeflateRect(1, 1);

	m_pPlotWin->GetWindowRect(&rect_plot);

	ScreenToClient(&rect_plot);

	m_rectPlotChild = rect_plot;

	m_rectPlotChild.DeflateRect(1, 1);

	m_spinOutputRate.SetRange32(MIN_OUTPUT_RATE, MAX_OUTPUT_RATE);
	
	m_spinSignalLength.SetRange32(MIN_SIGNAL_LENGTH, MAX_SIGNAL_LENGTH);
	
	m_spinLoopFinite.SetRange32(1, 100000);

	m_spinTimeout.SetRange32(0, 300);

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		for(int index_demux = 0; index_demux < 32; index_demux++)
		{
			CString cs_text;

			cs_text.Format("Channel %2d", index_demux + 1);
			
			m_comboDemuxChannelNumber[index_channel].AddString(cs_text);
		}

		m_comboDemuxChannelNumber[index_channel].SetCurSel(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiDemuxChannelNumber[index_channel]);

		m_spinFrequencyFrom[index_channel].SetRange32(MIN_FREQ, MAX_FREQ);
		m_spinFrequencyTo[index_channel].SetRange32(MIN_FREQ, MAX_FREQ);
		
		m_spinAmplitudeFrom[index_channel].SetRange32(MIN_AMP, MAX_AMP);
		m_spinAmplitudeTo[index_channel].SetRange32(MIN_AMP, MAX_AMP);
	}

	m_cbChannel[0].SubclassDlgItem(IDC_COLOUR_CHANNEL_M1, this);
	
	m_cbChannel[1].SubclassDlgItem(IDC_COLOUR_CHANNEL_M2, this);
	
	m_cbChannel[2].SubclassDlgItem(IDC_COLOUR_CHANNEL_M3, this);
	
	m_cbChannel[3].SubclassDlgItem(IDC_COLOUR_CHANNEL_M4, this);

	SetControlStates();

	SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMultiSigAnalogOutputPP::OnExit() 
{
	// TODO: Add your control notification handler code here
	
	if(AfxMessageBox("This will terminate the test programm", MB_OKCANCEL) == IDOK)
	{
		m_pPropertySheet->EndDialog(0);
	}
}

void CMultiSigAnalogOutputPP::OnCheckChannel(int index_channel)
{
	BOOL b_enable = IsDlgButtonChecked(m_iCheckChannelID[index_channel]);

	GetDlgItem(m_iComboDemuxChannelNumberID[index_channel])->EnableWindow(b_enable);

	GetDlgItem(m_iComboSignalFormID[index_channel])->EnableWindow(b_enable);

	GetDlgItem(m_iEditFrequencyFromID[index_channel])->EnableWindow(b_enable);

	GetDlgItem(m_iEditFrequencyToID[index_channel])->EnableWindow(b_enable);

	GetDlgItem(m_iEditAmplitudeFromID[index_channel])->EnableWindow(b_enable);

	GetDlgItem(m_iEditAmplitudeToID[index_channel])->EnableWindow(b_enable);

	m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bChannelActive[index_channel] = b_enable;

	RedrawPlot();
}
	
void CMultiSigAnalogOutputPP::OnSelchangeComboSignalForm(int index_channel)
{
	m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iOutputSignalForm[index_channel] = m_comboSignalForm[index_channel].GetCurSel();
	
	RedrawPlot();
}

void CMultiSigAnalogOutputPP::OnKillfocusEditFrequencyFrom(int index_channel)
{
	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_frequency_from;
	
	DDX_Text(&dx_read, m_iEditFrequencyFromID[index_channel], ui_frequency_from);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyFrom[index_channel] != ui_frequency_from)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyFrom[index_channel] = ui_frequency_from;
		
		RedrawPlot();
	}
}
	
void CMultiSigAnalogOutputPP::OnKillfocusEditFrequencyTo(int index_channel)
{
	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_frequency_to;
	
	DDX_Text(&dx_read, m_iEditFrequencyToID[index_channel], ui_frequency_to);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyTo[index_channel] != ui_frequency_to)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyTo[index_channel] = ui_frequency_to;
		
		RedrawPlot();
	}
}

void CMultiSigAnalogOutputPP::OnKillfocusEditAmplitudeFrom(int index_channel)
{
	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_amplitude_from;
	
	DDX_Text(&dx_read, m_iEditAmplitudeFromID[index_channel], ui_amplitude_from);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeFrom[index_channel] != ui_amplitude_from)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeFrom[index_channel] = ui_amplitude_from;
		
		RedrawPlot();
	}
}

void CMultiSigAnalogOutputPP::OnKillfocusEditAmplitudeTo(int index_channel)
{
	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_amplitude_to;
	
	DDX_Text(&dx_read, m_iEditAmplitudeToID[index_channel], ui_amplitude_to);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeTo[index_channel] != ui_amplitude_to)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeTo[index_channel] = ui_amplitude_to;
		
		RedrawPlot();
	}
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinFrequencyFrom(int index_channel, NM_UPDOWN* pNMUpDown)
{
	int i_new_freq = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_freq < MIN_FREQ)
	{
		i_new_freq = MIN_FREQ;
	}
	else if(i_new_freq > MAX_FREQ)
	{
		i_new_freq = MAX_FREQ;
	}

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyFrom[index_channel] != (unsigned int)i_new_freq)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyFrom[index_channel] = (unsigned int)i_new_freq;

		RedrawPlot();
	}
}
	
void CMultiSigAnalogOutputPP::OnDeltaposSpinFrequencyTo(int index_channel, NM_UPDOWN* pNMUpDown)
{
	int i_new_freq = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_freq < MIN_FREQ)
	{
		i_new_freq = MIN_FREQ;
	}
	else if(i_new_freq > MAX_FREQ)
	{
		i_new_freq = MAX_FREQ;
	}

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyTo[index_channel] != (unsigned int)i_new_freq)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyTo[index_channel] = (unsigned int)i_new_freq;

		RedrawPlot();
	}
}
	
void CMultiSigAnalogOutputPP::OnDeltaposSpinAmplitudeFrom(int index_channel, NM_UPDOWN* pNMUpDown)
{
	int i_new_amp = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_amp < MIN_AMP)
	{
		i_new_amp = MIN_AMP;
	}
	else if(i_new_amp > MAX_AMP)
	{
		i_new_amp = MAX_AMP;
	}

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeFrom[index_channel] != (unsigned int)i_new_amp)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeFrom[index_channel] = (unsigned int)i_new_amp;

		RedrawPlot();
	}
}
	
void CMultiSigAnalogOutputPP::OnDeltaposSpinAmplitudeTo(int index_channel, NM_UPDOWN* pNMUpDown)
{
	int i_new_amp = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_amp < MIN_AMP)
	{
		i_new_amp = MIN_AMP;
	}
	else if(i_new_amp > MAX_AMP)
	{
		i_new_amp = MAX_AMP;
	}

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeTo[index_channel] != (unsigned int)i_new_amp)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeTo[index_channel] = (unsigned int)i_new_amp;

		RedrawPlot();
	}
}
	
void CMultiSigAnalogOutputPP::SetControlStates(void)
{
	Cme4000App* p_app = (Cme4000App*)AfxGetApp();

	ME4000Board* p_boards = p_app->GetBoardArray();

	CString cs_text;
	
	cs_text.Format( "%04X", p_boards[m_iCurrentBoardIndex].m_usDeviceID );
	
	SetDlgItemText(IDC_BOARD_VERSION, cs_text);
	
	cs_text.Format( "%08X", p_boards[m_iCurrentBoardIndex].m_ulSerialNumber );
	
	SetDlgItemText(IDC_SERIAL_NUMBER, cs_text);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bMultiSigAOOpen)
	{
		SetDlgItemText(IDC_MULTISIGAO_OPEN_CLOSE, "MultiSigAOClose");

		GetDlgItem(IDC_START)->EnableWindow(TRUE);

		if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAOActive)
		{
			GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		}
	}
	else
	{
		SetDlgItemText(IDC_MULTISIGAO_OPEN_CLOSE, "MultiSigAOOpen");

		GetDlgItem(IDC_START)->EnableWindow(FALSE);

		GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
	}
	
	switch(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction)
	{
	case AO_SINGLE:

		OnRadioAOSingle();

		break;

	case AO_WRAPAROUND:

		OnRadioAOWraparound();

		break;

	case AO_CONTINUOUS:

		OnRadioAOContinuous();

		break;
	}

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction != AO_SINGLE)
	{
		for(int index_channel = 0; index_channel < 4; index_channel++)
		{
			OnCheckChannel(index_channel);
		}
	}

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode == ME4000_AO_TRIGGER_SOFTWARE)
	{
		OnRadioTriggerSoftware();
	}
	else
	{
		OnRadioTriggerDigital();
	}
}

void CMultiSigAnalogOutputPP::RedrawPlot()
{
	InvalidateRect(m_rectPlotChild);
}

void _stdcall CMultiSigAnalogOutputPP::WraparoundTerminate(void* pTerminateContext)
{
	SMEBoardMultiSigAO* p_msao_board = (SMEBoardMultiSigAO*)pTerminateContext;

	p_msao_board->m_pMultiSigAnalogOutputPP->SetDlgItemText(IDC_START, "Start");
	
	p_msao_board->m_pMultiSigAnalogOutputPP->GetDlgItem(IDC_STOP)->EnableWindow(FALSE);

	p_msao_board->m_bAOActive = FALSE;
}

void _stdcall CMultiSigAnalogOutputPP::ContinuousCallback(unsigned long ulBufferAvailable, void* pCallbackContext)
{
	SMEBoardMultiSigAO* p_msao_board = (SMEBoardMultiSigAO*)pCallbackContext;

	if(p_msao_board->m_bAppendBuffer)
	{
		unsigned long ul_values_appended;
		
		me4000MultiSigAOAppendNewValues(p_msao_board->m_iIndexBoard,										// uiBoardNumber,
										p_msao_board->m_psDataBuffer + p_msao_board->m_uiAppendOffset,		// psBuffer,
										p_msao_board->m_ulSizeOfAppend,										// ulNumberOfValuesToAppend,
										ME4000_AO_APPEND_NEW_VALUES_BLOCKING,								// iExecutionMode,
										&ul_values_appended												);	// pulNumberOfValuesAppended
	}

	p_msao_board->m_bAppendBuffer = FALSE;

//	p_msao_board->m_pAnalogOutputPP->GetDlgItem(IDC_STOP)->PostMessage(WM_ENABLE, TRUE, 0);

	p_msao_board->m_pMultiSigAnalogOutputPP->GetDlgItem(IDC_START)->EnableWindow(TRUE);
}

void CMultiSigAnalogOutputPP::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	CClientDC dc_plot(m_pPlotWin);

	dc_plot.FillSolidRect( m_rectPlotClient, RGB(0, 0, 0) );
		
	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction == AO_SINGLE)
	{
		dc_plot.SetTextColor(channel_colors[0]);

		dc_plot.SetBkMode(TRANSPARENT);

		CFont font_text;

		font_text.CreateFontIndirect(&lf_text);

		CFont* p_old_font = dc_plot.SelectObject(&font_text);

		CString cs_text;
		
		cs_text.Format("%7.3f V", m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_dSingleValue);
		
		dc_plot.DrawText(cs_text, m_rectPlotClient, DT_SINGLELINE | DT_CENTER | DT_VCENTER); 
	
		dc_plot.SelectObject(p_old_font);
	}
	else
	{
		unsigned long ul_data_count = m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSignalLengthSeconds * m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate;

		double d_x_factor = (double)m_rectPlotClient.Width() / (double)ul_data_count;
		
		double d_x_const = (double)m_rectPlotClient.left;

		double d_y_factor = ( (double)m_rectPlotClient.Height() - 4.0 ) / -20.0;

		double d_y_const = ( (double)m_rectPlotClient.top + 2.0 ) - 10.0 * d_y_factor;
		
		for(int index_channel = 0; index_channel < 4; index_channel++)
		{
			if( m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bChannelActive[index_channel] )
			{
				CPen disp_pen(PS_SOLID, 1, channel_colors[index_channel] );

				CPen* p_old_pen = (CPen*)dc_plot.SelectObject(&disp_pen);
				
				WinSweepDisplay(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iOutputSignalForm[index_channel],				// signal_type 
								(double)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyFrom[index_channel],		// from_freq 
								(double)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyTo[index_channel],		// to_freq 
								(double)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeFrom[index_channel],		// from_amp 
								(double)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeTo[index_channel],		// to_amp 
								(double)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate,							// base_freq, 
								ul_data_count,																				// no_of_points 
								&dc_plot,																					// p_dc
								m_rectPlotClient,																			// rect_disp, 
								d_x_const,																					// d_x_const, 
								d_x_factor,																					// d_x-factor 
								d_y_const,																					// d_y_const 
								d_y_factor																				);	// d_y_factor

				dc_plot.SelectObject(p_old_pen);
			}
		}
	}

	// Do not call CPropertyPage::OnPaint() for painting messages
}

void CMultiSigAnalogOutputPP::OnRadioAOSingle() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_EDIT_OUTPUT_RATE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_SIGNAL_LENGTH)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO_LOOP_ENDLESS)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO_LOOP_FINITE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_LOOP_FINITE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(FALSE);

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		GetDlgItem(m_iCheckChannelID[index_channel])->EnableWindow(FALSE);

		if(index_channel == 0)
		{
			GetDlgItem(m_iComboDemuxChannelNumberID[index_channel])->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(m_iComboDemuxChannelNumberID[index_channel])->EnableWindow(FALSE);
		}

		GetDlgItem(m_iComboSignalFormID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditFrequencyFromID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditFrequencyToID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditAmplitudeFromID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditAmplitudeToID[index_channel])->EnableWindow(FALSE);
	}

	GetDlgItem(m_iComboSignalFormID[0])->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_CONSTANT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_EDIT_OUTPUT_SINGLE)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATIC_VOLT)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_EDIT_OUTPUT_SINGLE)->EnableWindow(TRUE);

	SetDlgItemText(IDC_START, "Output");

	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction != AO_SINGLE)
	{
		int i_trigger_type;

		CDataExchange dx_read(this, TRUE);
		
		DDX_Radio(&dx_read, IDC_RADIO_TRIGGER_SOFTWARE, i_trigger_type);

		switch(i_trigger_type)
		{
		case 0:
			
			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode = ME4000_AO_TRIGGER_SOFTWARE;

			break;

		case 1:
			
			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode = ME4000_AO_TRIGGER_EXT_DIGITAL;

			break;
		}

		i_trigger_type = 0;

		CDataExchange dx_write(this, FALSE);
		
		DDX_Radio(&dx_write, IDC_RADIO_TRIGGER_SOFTWARE, i_trigger_type);
	}

	m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction = AO_SINGLE;

	RedrawPlot();
}

void CMultiSigAnalogOutputPP::OnRadioAOWraparound() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_EDIT_OUTPUT_RATE)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_SIGNAL_LENGTH)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_LOOP_ENDLESS)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_LOOP_FINITE)->EnableWindow(TRUE);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bInfiniteLoops)
	{
		GetDlgItem(IDC_EDIT_LOOP_FINITE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_LOOP_FINITE)->EnableWindow(TRUE);
	}

	GetDlgItem(IDC_STATIC_CONSTANT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_EDIT_OUTPUT_SINGLE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_VOLT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_EDIT_OUTPUT_SINGLE)->EnableWindow(TRUE);

	GetDlgItem(m_iComboSignalFormID[0])->ShowWindow(SW_SHOW);

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		GetDlgItem(m_iCheckChannelID[index_channel])->EnableWindow(TRUE);

		if( IsDlgButtonChecked(m_iCheckChannelID[index_channel]) == BST_CHECKED )
		{
			GetDlgItem(m_iComboDemuxChannelNumberID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iComboSignalFormID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iEditFrequencyFromID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iEditFrequencyToID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iEditAmplitudeFromID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iEditAmplitudeToID[index_channel])->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(m_iComboDemuxChannelNumberID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iComboSignalFormID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iEditFrequencyFromID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iEditFrequencyToID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iEditAmplitudeFromID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iEditAmplitudeToID[index_channel])->EnableWindow(FALSE);
		}
	}

	SetDlgItemText(IDC_START, "Start");

	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction == AO_SINGLE)
	{
		int i_trigger_type;

		CDataExchange dx_read(this, TRUE);
		
		DDX_Radio(&dx_read, IDC_RADIO_TRIGGER_SOFTWARE, i_trigger_type);

		switch(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode)
		{
		case ME4000_AO_TRIGGER_SOFTWARE:
			
			i_trigger_type = 0;

			break;

		case ME4000_AO_TRIGGER_EXT_DIGITAL:
			
			i_trigger_type = 1;

			break;
		}

		CDataExchange dx_write(this, FALSE);
		
		DDX_Radio(&dx_write, IDC_RADIO_TRIGGER_SOFTWARE, i_trigger_type);
	}

	m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction = AO_WRAPAROUND;

	RedrawPlot();
}

void CMultiSigAnalogOutputPP::OnRadioAOContinuous() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_EDIT_OUTPUT_RATE)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_SIGNAL_LENGTH)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_LOOP_ENDLESS)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO_LOOP_FINITE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_LOOP_FINITE)->EnableWindow(FALSE);

	GetDlgItem(IDC_STATIC_CONSTANT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_EDIT_OUTPUT_SINGLE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_VOLT)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_EDIT_OUTPUT_SINGLE)->EnableWindow(TRUE);

	GetDlgItem(m_iComboSignalFormID[0])->ShowWindow(SW_SHOW);

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		GetDlgItem(m_iCheckChannelID[index_channel])->EnableWindow(TRUE);

		if( IsDlgButtonChecked(m_iCheckChannelID[index_channel]) == BST_CHECKED )
		{
			GetDlgItem(m_iComboDemuxChannelNumberID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iComboSignalFormID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iEditFrequencyFromID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iEditFrequencyToID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iEditAmplitudeFromID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iEditAmplitudeToID[index_channel])->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(m_iComboDemuxChannelNumberID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iComboSignalFormID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iEditFrequencyFromID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iEditFrequencyToID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iEditAmplitudeFromID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iEditAmplitudeToID[index_channel])->EnableWindow(FALSE);
		}
	}

	SetDlgItemText(IDC_START, "Start");

	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction == AO_SINGLE)
	{
		int i_trigger_type;

		CDataExchange dx_read(this, TRUE);
		
		DDX_Radio(&dx_read, IDC_RADIO_TRIGGER_SOFTWARE, i_trigger_type);

		switch(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode)
		{
		case ME4000_AO_TRIGGER_SOFTWARE:
			
			i_trigger_type = 0;

			break;

		case ME4000_AO_TRIGGER_EXT_DIGITAL:
			
			i_trigger_type = 1;

			break;
		}

		CDataExchange dx_write(this, FALSE);
		
		DDX_Radio(&dx_write, IDC_RADIO_TRIGGER_SOFTWARE, i_trigger_type);
	}

	m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction = AO_CONTINUOUS;

	RedrawPlot();
}

void CMultiSigAnalogOutputPP::OnRadioTriggerSoftware() 
{
	// TODO: Add your control notification handler code here

	GetDlgItem(IDC_RADIO_TRIGGER_RISING)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_TRIGGER_FALLING)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_TRIGGER_BOTH)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(FALSE);

	m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode = ME4000_AO_TRIGGER_SOFTWARE;
}

void CMultiSigAnalogOutputPP::OnRadioTriggerDigital() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RADIO_TRIGGER_RISING)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_TRIGGER_FALLING)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_TRIGGER_BOTH)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);

	m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode = ME4000_AO_TRIGGER_EXT_DIGITAL;
}

void CMultiSigAnalogOutputPP::OnRadioLoopEndless() 
{
	// TODO: Add your control notification handler code here
	
	m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bInfiniteLoops = TRUE;
	
	GetDlgItem(IDC_EDIT_LOOP_FINITE)->EnableWindow(FALSE);
}

void CMultiSigAnalogOutputPP::OnRadioLoopFinite() 
{
	// TODO: Add your control notification handler code here
	
	m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bInfiniteLoops = FALSE;
	
	GetDlgItem(IDC_EDIT_LOOP_FINITE)->EnableWindow(TRUE);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditOutputRate() 
{
	// TODO: Add your control notification handler code here
	
	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_output_rate;
	
	DDX_Text(&dx_read, IDC_EDIT_OUTPUT_RATE, ui_output_rate);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate != ui_output_rate)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate = ui_output_rate;
		
		RedrawPlot();
	}
}

void CMultiSigAnalogOutputPP::OnKillfocusEditSignalLength() 
{
	// TODO: Add your control notification handler code here
	
	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_signal_length_seconds;
	
	DDX_Text(&dx_read, IDC_EDIT_SIGNAL_LENGTH, ui_signal_length_seconds);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSignalLengthSeconds != ui_signal_length_seconds)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSignalLengthSeconds = ui_signal_length_seconds;

		RedrawPlot();
	}
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinOutputRate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	int i_new_output_rate = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_output_rate < MIN_OUTPUT_RATE)
	{
		i_new_output_rate = MIN_OUTPUT_RATE;
	}
	else if(i_new_output_rate > MAX_OUTPUT_RATE)
	{
		i_new_output_rate = MAX_OUTPUT_RATE;
	}

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate != (unsigned int)i_new_output_rate)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate = (unsigned int)i_new_output_rate;

		RedrawPlot();
	}

	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinSignalLength(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	int i_new_signal_length = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_signal_length < MIN_SIGNAL_LENGTH)
	{
		i_new_signal_length = MIN_SIGNAL_LENGTH;
	}
	else if(i_new_signal_length > MAX_SIGNAL_LENGTH)
	{
		i_new_signal_length = MAX_SIGNAL_LENGTH;
	}

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSignalLengthSeconds != (unsigned int)i_new_signal_length)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSignalLengthSeconds = (unsigned int)i_new_signal_length;

		RedrawPlot();
	}

	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnChangeEditOutputSingle() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	CDataExchange dx_read(this, TRUE);
		
	double d_single_value;
	
	DDX_Text(&dx_read, IDC_EDIT_OUTPUT_SINGLE, d_single_value);

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_dSingleValue != d_single_value)
	{
		m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_dSingleValue = d_single_value;

		RedrawPlot();
	}
}

void CMultiSigAnalogOutputPP::OnCheckChannel1() 
{
	// TODO: Add your control notification handler code here

	OnCheckChannel(0);
}

void CMultiSigAnalogOutputPP::OnSelchangeComboSignalFormM1() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboSignalForm(0);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditFrequencyFromM1() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyFrom(0);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditFrequencyToM1() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyTo(0);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditAmplitudeFromM1() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeFrom(0);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditAmplitudeToM1() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeTo(0);
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinFrequencyFromM1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinFrequencyFrom(0, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinFrequencyToM1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinFrequencyTo(0, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinAmplitudeFromM1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinAmplitudeFrom(0, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinAmplitudeToM1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinAmplitudeTo(0, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnCheckChannel2() 
{
	// TODO: Add your control notification handler code here

	OnCheckChannel(1);
}

void CMultiSigAnalogOutputPP::OnSelchangeComboSignalFormM2() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboSignalForm(1);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditFrequencyFromM2() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyFrom(1);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditFrequencyToM2() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyTo(1);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditAmplitudeFromM2() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeFrom(1);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditAmplitudeToM2() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeTo(1);
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinFrequencyFromM2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinFrequencyFrom(1, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinFrequencyToM2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinFrequencyTo(1, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinAmplitudeFromM2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinAmplitudeFrom(1, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinAmplitudeToM2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinAmplitudeTo(1, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnCheckChannel3() 
{
	// TODO: Add your control notification handler code here

	OnCheckChannel(2);
}

void CMultiSigAnalogOutputPP::OnSelchangeComboSignalFormM3() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboSignalForm(2);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditFrequencyFromM3() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyFrom(2);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditFrequencyToM3() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyTo(2);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditAmplitudeFromM3() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeFrom(2);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditAmplitudeToM3() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeTo(2);
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinFrequencyFromM3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinFrequencyFrom(2, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinFrequencyToM3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinFrequencyTo(2, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinAmplitudeFromM3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinAmplitudeFrom(2, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinAmplitudeToM3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinAmplitudeTo(2, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnCheckChannel4() 
{
	// TODO: Add your control notification handler code here

	OnCheckChannel(3);
}

void CMultiSigAnalogOutputPP::OnSelchangeComboSignalFormM4() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboSignalForm(3);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditFrequencyFromM4() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyFrom(3);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditFrequencyToM4() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyTo(3);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditAmplitudeFromM4() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeFrom(3);
}

void CMultiSigAnalogOutputPP::OnKillfocusEditAmplitudeToM4() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeTo(3);
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinFrequencyFromM4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinFrequencyFrom(3, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinFrequencyToM4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinFrequencyTo(3, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinAmplitudeFromM4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinAmplitudeFrom(3, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnDeltaposSpinAmplitudeToM4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinAmplitudeTo(3, pNMUpDown);
	
	*pResult = 0;
}

void CMultiSigAnalogOutputPP::OnStart() 
{
	// TODO: Add your control notification handler code here
	
	if( !m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAOActive )
	{
		CDataExchange dx(this, TRUE);
		
		DoDataExchange(&dx);

		int i_error;
		
		int i_ext_trigger_edge = m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerExtEdge;

		if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode != ME4000_AO_TRIGGER_EXT_DIGITAL)
		{
			i_ext_trigger_edge = ME4000_VALUE_NOT_USED;
		}
	
		unsigned long ul_timeout_seconds = m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_ulTimeout;

		if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode != ME4000_AO_TRIGGER_EXT_DIGITAL)
		{
			ul_timeout_seconds = ME4000_VALUE_NOT_USED;
		}

		if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction == AO_SINGLE)
		{
			short s_digit;
			
			i_error = me4000MultiSigAOVoltToDigit(	m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_dSingleValue,	// dVolt,
													&s_digit												);	// psDigit

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}
			
			i_error = me4000MultiSigAOSingle(	m_iCurrentBoardIndex,													// uiBoardNumber,
												m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiDemuxChannelNumber[0],		// uiDemuxChannelNumber,
												m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode,				// iTriggerMode,
												i_ext_trigger_edge,														// iReserved,
												ul_timeout_seconds,														// ulReserved,
												s_digit																);	//  sValue	
			
		}
		else
		{
			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount = 0;

			unsigned char uc_demux_list[4];

			for(int index_channel = 0; index_channel < 4; index_channel++)
			{
				if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bChannelActive[index_channel])
				{
					uc_demux_list[ m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount ] = (unsigned char)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiDemuxChannelNumber[index_channel];

					m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount++;
				}
			}
			
			unsigned long ul_ticks_low_part;

			unsigned long ul_ticks_high_part;

			unsigned int total_output_rate = 
					m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * 
											m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate;

			me4000FrequencyToTicks(	(double)total_output_rate,		// dRequiredFreq,
									&ul_ticks_low_part,				// pulTicksLowPart,
									&ul_ticks_high_part,			// pulTicksHighPart,
									ME4000_POINTER_NOT_USED		);	// pdAchievedFreq - not required
	
			i_error = me4000MultiSigAOConfig(	m_iCurrentBoardIndex,													// uiBoardNumber,
												&uc_demux_list[0],														// pucDemuxChanList
												m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount,		// uiDemuxChanListCount,
												ul_ticks_low_part,														// ulTicks,
												m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iTriggerMode,			// iTriggerMode,
												i_ext_trigger_edge													);	// iExtTriggerEdge

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}

			unsigned long ul_data_count = m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSignalLengthSeconds * 
																m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate;
	
			if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_ulDataBufferSizeValues < 
								m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * ul_data_count)
			{
				if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer != NULL)
				{
					delete m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer;

					m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer = NULL;

					m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_ulDataBufferSizeValues = 0;
				}

				m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer = 
								new short[m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * ul_data_count];

				if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer == NULL)
				{
					AfxMessageBox(	"Unable to allocate data buffer\n\n"
									"Please reduce the output rate, the signal length or the number of DEMUX channels"	);

					return;
				}

				m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_ulDataBufferSizeValues = 
								m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * ul_data_count;
			}
	
			int index_signal = 0;
			
			for(index_channel = 0; index_channel < 4; index_channel++)
			{
				if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bChannelActive[index_channel])
				{
					WinSweepBuffer(	m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iOutputSignalForm[index_channel],				// signal_type 
									(double)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyFrom[index_channel],		// from_freq 
									(double)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepFrequencyTo[index_channel],		// to_freq 
									(double)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeFrom[index_channel],		// from_amp 
									(double)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiSweepAmplitudeTo[index_channel],		// to_amp 
									(double)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate,							// base_freq, 
									ul_data_count,																				// no_of_points 
									m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer + index_signal,						// buffer
									m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount						);	// buffer_increment);

					index_signal++;
				}
			}

			if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction == AO_WRAPAROUND)
			{
				unsigned long ul_loops = m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiFiniteLoops;

				if( m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bInfiniteLoops )
				{
					ul_loops = ME4000_AO_WRAPAROUND_INFINITE;
				}
			
				i_error = me4000MultiSigAOWraparound(	m_iCurrentBoardIndex,																	// uiBoardNumber,
														m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer,								// psBuffer,
														m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * ul_data_count,		// ulDataCount,
														ul_loops,																				// ulLoops,
														ME4000_AO_WRAPAROUND_ASYNCHRONOUS,														// iExecutionMode,
														WraparoundTerminate,																	// pTerminateProc,
														&m_sBoardMultiSigAO[m_iCurrentBoardIndex],												// pTerminateContext,
														ul_timeout_seconds																	);	// ulTimeOutSeconds	
			
				if(i_error != ME4000_NO_ERROR)
				{
					return;
				}
			}
			else
			{
				unsigned long ul_number_of_values_written;
		
				i_error = me4000MultiSigAOContinuous(	m_iCurrentBoardIndex,																	// uiBoardNumber,
														m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer,								// psBuffer,
														m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * ul_data_count,		// ulDataCount,
														ContinuousCallback,																		// pCallbackProc,
														&m_sBoardMultiSigAO[m_iCurrentBoardIndex],												// pTerminateContext,
														ul_timeout_seconds,																		// ulTimeOutSeconds	
														&ul_number_of_values_written														);	// pulNumberOfValuesWritten	
				
				if(i_error != ME4000_NO_ERROR)
				{
					return;
				}

				if(ul_number_of_values_written == m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * ul_data_count)
				{
					m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAppendBuffer = FALSE;
				}
				else
				{
					m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_ulSizeOfAppend = m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * ul_data_count - ul_number_of_values_written;
					
					m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiAppendOffset = ul_number_of_values_written;

					m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAppendBuffer = TRUE;
				}
			}

			i_error = me4000MultiSigAOStart(m_iCurrentBoardIndex);
			
			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}

			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAOActive = TRUE;

			if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iFunction == AO_WRAPAROUND)
			{
				m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iLastOperation = AO_WRAPAROUND;
		
				SetDlgItemText(IDC_START, "Stop last value");
		
				GetDlgItem(IDC_START)->EnableWindow(TRUE);

				SetDlgItemText(IDC_STOP, "Stop immediate");

				GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
			}
			else
			{
				m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iLastOperation = AO_CONTINUOUS;
		
				SetDlgItemText(IDC_START, "Append");

				if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAppendBuffer)
				{
					GetDlgItem(IDC_START)->EnableWindow(FALSE);
				}
				else
				{
					GetDlgItem(IDC_START)->EnableWindow(TRUE);
				}
		
				SetDlgItemText(IDC_STOP, "Stop");

				GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
			}
		}
	}
	else // if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAOActive)
	{
		if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iLastOperation == AO_WRAPAROUND)
		{
			me4000MultiSigAOStop(	m_iCurrentBoardIndex,				// uiBoardNumber,
									ME4000_AO_STOP_MODE_LAST_VALUE	);	// iStopMode		
		}
		else if( (m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iLastOperation == AO_CONTINUOUS)&&
											( !m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAppendBuffer ) )
		{
			GetDlgItem(IDC_START)->EnableWindow(FALSE);
			
			CDataExchange dx_read(this, TRUE);
		
			unsigned int ui_signal_length_seconds;

			DDX_Text(&dx_read, IDC_EDIT_SIGNAL_LENGTH, ui_signal_length_seconds);

			unsigned long ul_data_count = ui_signal_length_seconds * 
												m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate;
	
			if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_ulDataBufferSizeValues < 
							m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * ul_data_count)
			{
				if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer != NULL)
				{
					delete m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer;

					m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer = NULL;

					m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_ulDataBufferSizeValues = 0;
				}

				m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer = 
									new short[m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * ul_data_count];

				if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer == NULL)
				{
					AfxMessageBox(	"Unable to allocate data buffer\n\n"
									"Please reduce the output rate, the signal length or the number of Demux channels"	);
			
					return;
				}

				m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_ulDataBufferSizeValues = 
										m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * ul_data_count;
			}
	
			int index_signal = 0;
			
			for(int index_channel = 0; index_channel < 4; index_channel++)
			{
				if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bCurrentChannelActive[index_channel])
				{
					int i_output_signal_form;
					
					i_output_signal_form =  (int)m_comboSignalForm[index_channel].GetCurSel();

					unsigned int ui_frequency_from;
					
					DDX_Text(&dx_read, m_iEditFrequencyFromID[index_channel], ui_frequency_from);

					unsigned int ui_frequency_to;
					
					DDX_Text(&dx_read, m_iEditFrequencyToID[index_channel], ui_frequency_to);

					unsigned int ui_amplitude_from;
					
					DDX_Text(&dx_read, m_iEditAmplitudeFromID[index_channel], ui_amplitude_from);

					unsigned int ui_amplitude_to;
					
					DDX_Text(&dx_read, m_iEditAmplitudeToID[index_channel], ui_amplitude_to);

					WinSweepBuffer(	i_output_signal_form,														// signal_type 
									ui_frequency_from,															// from_freq 
									ui_frequency_to,															// to_freq 
									ui_amplitude_from,															// from_amp 
									ui_amplitude_to,															// to_amp 
									(double)m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiOutputRate,			// base_freq, 
									ul_data_count,																// no_of_points 
									m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_psDataBuffer + index_signal,		// buffer
									m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount		);	// buffer_increment);

					index_signal++;
				}
			}

			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_ulSizeOfAppend = m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiCurrentDemuxChanCount * ul_data_count;

			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_uiAppendOffset = 0;
			
			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAppendBuffer = TRUE;
		}
	}
}

void CMultiSigAnalogOutputPP::OnStop() 
{
	// TODO: Add your control notification handler code here
	
	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAOActive)
	{
		if( (m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iLastOperation == AO_WRAPAROUND)||
										(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iLastOperation == AO_CONTINUOUS) )
		{
			me4000MultiSigAOStop(	m_iCurrentBoardIndex,				// uiBoardNumber
									ME4000_AO_STOP_MODE_IMMEDIATE	);	// iStopMode		
			
			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAOActive = FALSE;
		}

		if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iLastOperation == AO_CONTINUOUS)
		{
			SetDlgItemText(IDC_START, "Start");

			GetDlgItem(IDC_START)->EnableWindow(TRUE);

			GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		}
	}
}

void CMultiSigAnalogOutputPP::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if( (m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_iLastOperation == AO_CONTINUOUS)&&
											(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAOActive) )
	{
		int i_status;
		
		me4000MultiSigAOGetStatus(	m_iCurrentBoardIndex,	// uiBoardNumber,
									ME4000_AO_WAIT_NONE,	// iWaitIdle,
									&i_status			);	// piStatus

		if(i_status == ME4000_AO_STATUS_IDLE)
		{
			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAOActive = FALSE;

			SetDlgItemText(IDC_START, "Start");

			GetDlgItem(IDC_START)->EnableWindow(TRUE);

			GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		}
	}

	CPropertyPage::OnTimer(nIDEvent);
}

void CMultiSigAnalogOutputPP::OnMultisigaoOpenClose() 
{
	// TODO: Add your control notification handler code here

	if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bMultiSigAOOpen)
	{
		int i_error = me4000MultiSigAOClose(m_iCurrentBoardIndex);	

		if(i_error == ME4000_NO_ERROR)
		{
			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bMultiSigAOOpen = FALSE;

			SetDlgItemText(IDC_MULTISIGAO_OPEN_CLOSE, "MultiSigAOOpen");

			GetDlgItem(IDC_START)->EnableWindow(FALSE);

			GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		}
	}
	else // if( !m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bMultiSigAOOpen )
	{
		int i_error = me4000MultiSigAOOpen(m_iCurrentBoardIndex);	

		if(i_error == ME4000_NO_ERROR)
		{
			m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bMultiSigAOOpen = TRUE;

			SetDlgItemText(IDC_MULTISIGAO_OPEN_CLOSE, "MultiSigAOClose");

			GetDlgItem(IDC_START)->EnableWindow(TRUE);

			if(m_sBoardMultiSigAO[m_iCurrentBoardIndex].m_bAOActive)
			{
				GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
			}
		}
	}
}
