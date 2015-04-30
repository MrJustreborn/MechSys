// AnalogOutputPP.cpp : implementation file
//
#include "stdafx.h"
#include "me4000.h"
#include "AnalogOutputPP.h"

#include "WinSweep.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnalogOutputPP property page

IMPLEMENT_DYNCREATE(CAnalogOutputPP, CPropertyPage)

static LOGFONT lf_text = {-36, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 
							OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
							DEFAULT_QUALITY, DEFAULT_PITCH|FF_ROMAN, "Arial" };

const COLORREF DISPLAY_COLOR = RGB(255, 0, 0);

CAnalogOutputPP::CAnalogOutputPP() : CPropertyPage(CAnalogOutputPP::IDD)
{
	//{{AFX_DATA_INIT(CAnalogOutputPP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	for(int index_board = 0; index_board < ME4000_MAX_DEVICES; index_board++)
	{
		for(int index_channel = 0; index_channel < 4; index_channel++)
		{
			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_pAnalogOutputPP = this;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_iIndexBoard = index_board;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_iIndexChannel = index_channel;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_iFunction = AO_FUNCTION_SINGLE;
			
			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_iBufferMode = AO_BUFFER_MODE_WRAPAROUND;	

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_bExtTriggerEnable = TRUE;	

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_iTriggerType = AO_TRIGGER_TYPE_SOFTWARE;	

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_iTriggerExtEdge = AO_TRIGGER_EXT_EDGE_RISING;
			
			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_uiOutputRate = 1000;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_uiSignalLengthSeconds = 10;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_dSingleValue = 0,0;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_bInfiniteLoops = FALSE;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_uiFiniteLoops = 1;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_ulTimeout = 5;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_iLastBufferMode = AO_FUNCTION_NONE;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_bAOActive = FALSE;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_iLastError = ME4000_NO_ERROR;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_psDataBuffer = NULL;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_ulDataBufferSizeValues = 0;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_bAppendBuffer = FALSE;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_uiAppendOffset = 0;

			m_sBoardAO[index_board].m_sAOChannel[index_channel].m_ulSizeOfAppend = 0;
		}

		// Make the default signals interesting
		
		m_sBoardAO[index_board].m_sAOChannel[0].m_iOutputSignalForm = SIGNAL_SINUS;

		m_sBoardAO[index_board].m_sAOChannel[0].m_uiSweepFrequencyFrom = 1;

		m_sBoardAO[index_board].m_sAOChannel[0].m_uiSweepFrequencyTo = 1;

		m_sBoardAO[index_board].m_sAOChannel[0].m_uiSweepAmplitudeFrom = 8;

		m_sBoardAO[index_board].m_sAOChannel[0].m_uiSweepAmplitudeTo = 8;

		m_sBoardAO[index_board].m_sAOChannel[1].m_iOutputSignalForm = SIGNAL_TRIANGLE;

		m_sBoardAO[index_board].m_sAOChannel[1].m_uiSweepFrequencyFrom = 5;

		m_sBoardAO[index_board].m_sAOChannel[1].m_uiSweepFrequencyTo = 1;

		m_sBoardAO[index_board].m_sAOChannel[1].m_uiSweepAmplitudeFrom = 1;

		m_sBoardAO[index_board].m_sAOChannel[1].m_uiSweepAmplitudeTo = 8;

		m_sBoardAO[index_board].m_sAOChannel[2].m_iOutputSignalForm = SIGNAL_RECTANGLE;

		m_sBoardAO[index_board].m_sAOChannel[2].m_uiSweepFrequencyFrom = 5;

		m_sBoardAO[index_board].m_sAOChannel[2].m_uiSweepFrequencyTo = 1;

		m_sBoardAO[index_board].m_sAOChannel[2].m_uiSweepAmplitudeFrom = 8;

		m_sBoardAO[index_board].m_sAOChannel[2].m_uiSweepAmplitudeTo = 1;

		m_sBoardAO[index_board].m_sAOChannel[3].m_iOutputSignalForm = SIGNAL_POS_RAMP;

		m_sBoardAO[index_board].m_sAOChannel[3].m_uiSweepFrequencyFrom = 1;

		m_sBoardAO[index_board].m_sAOChannel[3].m_uiSweepFrequencyTo = 5;

		m_sBoardAO[index_board].m_sAOChannel[3].m_uiSweepAmplitudeFrom = 8;

		m_sBoardAO[index_board].m_sAOChannel[3].m_uiSweepAmplitudeTo = 1;

		// Multiple output

		m_sBoardAO[index_board].m_iSingleSimultaneousTrigger = AO_TRIGGER_TYPE_SOFTWARE;

		m_sBoardAO[index_board].m_ulSingleSimultaneousTimeout = 5;

		m_sBoardAO[index_board].m_iStartSynchronousTrigger = AO_TRIGGER_TYPE_SOFTWARE;

		m_sBoardAO[index_board].m_ulStartSynchronousTimeout = 5;
	}
		
	m_iComboFunctionID[0]				= IDC_COMBO_FUNCTION_1;

	m_iRadioAOModeWraparoundID[0]		= IDC_RADIO_AO_WRAPAROUND_1;
	m_iRadioAOModeContinuousID[0]		= IDC_RADIO_AO_CONTINUOUS_1;

	m_iCheckEnableExtTriggerID[0]		= IDC_CHECK_ENABLE_EXT_TRIGGER_1;

	m_iRadioTriggerSoftwareID[0]		= IDC_RADIO_TRIGGER_SOFTWARE_1;
	m_iRadioTriggerExtDigitalID[0]		= IDC_RADIO_TRIGGER_DIGITAL_1;

	m_iRadioTriggerRisingID[0]			= IDC_RADIO_TRIGGER_RISING_1;
	m_iRadioTriggerFallingID[0]			= IDC_RADIO_TRIGGER_FALLING_1;
	m_iRadioTriggerBothID[0]			= IDC_RADIO_TRIGGER_BOTH_1;

	m_iEditOutputRateID[0]				= IDC_EDIT_OUTPUT_RATE_1;
	m_iSpinOutputRateID[0]				= IDC_SPIN_OUTPUT_RATE_1;

	m_iEditSignalLengthID[0]			= IDC_EDIT_SIGNAL_LENGTH_1;
	m_iSpinSignalLengthID[0]			= IDC_SPIN_SIGNAL_LENGTH_1;

	m_iComboSignalFormID[0]				= IDC_COMBO_SIGNAL_FORM_1;

	m_iEditFrequencyFromID[0]			= IDC_EDIT_FREQUENCY_FROM_1;
	m_iSpinFrequencyFromID[0]			= IDC_SPIN_FREQUENCY_FROM_1;

	m_iEditFrequencyToID[0]				= IDC_EDIT_FREQUENCY_TO_1;
	m_iSpinFrequencyToID[0]				= IDC_SPIN_FREQUENCY_TO_1;

	m_iEditAmplitudeFromID[0]			= IDC_EDIT_AMPLITUDE_FROM_1;
	m_iSpinAmplitudeFromID[0]			= IDC_SPIN_AMPLITUDE_FROM_1;

	m_iEditAmplitudeToID[0]				= IDC_EDIT_AMPLITUDE_TO_1;
	m_iSpinAmplitudeToID[0]				= IDC_SPIN_AMPLITUDE_TO_1;

	m_iEditOutputSingleID[0]			= IDC_EDIT_OUTPUT_SINGLE_1;

	m_iRadioLoopEndlessID[0]			= IDC_RADIO_LOOP_ENDLESS_1;
	m_iRadioLoopFiniteID[0]				= IDC_RADIO_LOOP_FINITE_1;
	m_iEditLoopFiniteID[0]				= IDC_EDIT_LOOP_FINITE_1;
	m_iSpinLoopFiniteID[0]				= IDC_SPIN_LOOP_FINITE_1;

	m_iEditTimeoutID[0]					= IDC_EDIT_TIMEOUT_1;
	m_iSpinTimeoutID[0]					= IDC_SPIN_TIMEOUT_1;

	m_iButtonStartAppendOutputID[0]		= IDC_BUTTON_START_APPEND_OUTPUT_1;
	m_iButtonStopID[0]					= IDC_BUTTON_STOP_1;

	m_iPlotID[0]						= IDC_PLOT_1;	

	m_iComboFunctionID[1]				= IDC_COMBO_FUNCTION_2;

	m_iRadioAOModeWraparoundID[1]		= IDC_RADIO_AO_WRAPAROUND_2;
	m_iRadioAOModeContinuousID[1]		= IDC_RADIO_AO_CONTINUOUS_2;

	m_iCheckEnableExtTriggerID[1]		= IDC_CHECK_ENABLE_EXT_TRIGGER_2;

	m_iRadioTriggerSoftwareID[1]		= IDC_RADIO_TRIGGER_SOFTWARE_2;
	m_iRadioTriggerExtDigitalID[1]		= IDC_RADIO_TRIGGER_DIGITAL_2;

	m_iRadioTriggerRisingID[1]			= IDC_RADIO_TRIGGER_RISING_2;
	m_iRadioTriggerFallingID[1]			= IDC_RADIO_TRIGGER_FALLING_2;
	m_iRadioTriggerBothID[1]			= IDC_RADIO_TRIGGER_BOTH_2;

	m_iEditOutputRateID[1]				= IDC_EDIT_OUTPUT_RATE_2;
	m_iSpinOutputRateID[1]				= IDC_SPIN_OUTPUT_RATE_2;

	m_iEditSignalLengthID[1]			= IDC_EDIT_SIGNAL_LENGTH_2;
	m_iSpinSignalLengthID[1]			= IDC_SPIN_SIGNAL_LENGTH_2;

	m_iComboSignalFormID[1]				= IDC_COMBO_SIGNAL_FORM_2;

	m_iEditFrequencyFromID[1]			= IDC_EDIT_FREQUENCY_FROM_2;
	m_iSpinFrequencyFromID[1]			= IDC_SPIN_FREQUENCY_FROM_2;

	m_iEditFrequencyToID[1]				= IDC_EDIT_FREQUENCY_TO_2;
	m_iSpinFrequencyToID[1]				= IDC_SPIN_FREQUENCY_TO_2;

	m_iEditAmplitudeFromID[1]			= IDC_EDIT_AMPLITUDE_FROM_2;
	m_iSpinAmplitudeFromID[1]			= IDC_SPIN_AMPLITUDE_FROM_2;

	m_iEditAmplitudeToID[1]				= IDC_EDIT_AMPLITUDE_TO_2;
	m_iSpinAmplitudeToID[1]				= IDC_SPIN_AMPLITUDE_TO_2;

	m_iEditOutputSingleID[1]			= IDC_EDIT_OUTPUT_SINGLE_2;

	m_iRadioLoopEndlessID[1]			= IDC_RADIO_LOOP_ENDLESS_2;
	m_iRadioLoopFiniteID[1]				= IDC_RADIO_LOOP_FINITE_2;
	m_iEditLoopFiniteID[1]				= IDC_EDIT_LOOP_FINITE_2;
	m_iSpinLoopFiniteID[1]				= IDC_SPIN_LOOP_FINITE_2;

	m_iEditTimeoutID[1]					= IDC_EDIT_TIMEOUT_2;
	m_iSpinTimeoutID[1]					= IDC_SPIN_TIMEOUT_2;

	m_iButtonStartAppendOutputID[1]		= IDC_BUTTON_START_APPEND_OUTPUT_2;
	m_iButtonStopID[1]					= IDC_BUTTON_STOP_2;

	m_iPlotID[1]						= IDC_PLOT_2;	

	m_iComboFunctionID[2]				= IDC_COMBO_FUNCTION_3;

	m_iRadioAOModeWraparoundID[2]		= IDC_RADIO_AO_WRAPAROUND_3;
	m_iRadioAOModeContinuousID[2]		= IDC_RADIO_AO_CONTINUOUS_3;

	m_iCheckEnableExtTriggerID[2]		= IDC_CHECK_ENABLE_EXT_TRIGGER_3;

	m_iRadioTriggerSoftwareID[2]		= IDC_RADIO_TRIGGER_SOFTWARE_3;
	m_iRadioTriggerExtDigitalID[2]		= IDC_RADIO_TRIGGER_DIGITAL_3;

	m_iRadioTriggerRisingID[2]			= IDC_RADIO_TRIGGER_RISING_3;
	m_iRadioTriggerFallingID[2]			= IDC_RADIO_TRIGGER_FALLING_3;
	m_iRadioTriggerBothID[2]			= IDC_RADIO_TRIGGER_BOTH_3;

	m_iEditOutputRateID[2]				= IDC_EDIT_OUTPUT_RATE_3;
	m_iSpinOutputRateID[2]				= IDC_SPIN_OUTPUT_RATE_3;

	m_iEditSignalLengthID[2]			= IDC_EDIT_SIGNAL_LENGTH_3;
	m_iSpinSignalLengthID[2]			= IDC_SPIN_SIGNAL_LENGTH_3;

	m_iComboSignalFormID[2]				= IDC_COMBO_SIGNAL_FORM_3;

	m_iEditFrequencyFromID[2]			= IDC_EDIT_FREQUENCY_FROM_3;
	m_iSpinFrequencyFromID[2]			= IDC_SPIN_FREQUENCY_FROM_3;

	m_iEditFrequencyToID[2]				= IDC_EDIT_FREQUENCY_TO_3;
	m_iSpinFrequencyToID[2]				= IDC_SPIN_FREQUENCY_TO_3;

	m_iEditAmplitudeFromID[2]			= IDC_EDIT_AMPLITUDE_FROM_3;
	m_iSpinAmplitudeFromID[2]			= IDC_SPIN_AMPLITUDE_FROM_3;

	m_iEditAmplitudeToID[2]				= IDC_EDIT_AMPLITUDE_TO_3;
	m_iSpinAmplitudeToID[2]				= IDC_SPIN_AMPLITUDE_TO_3;

	m_iEditOutputSingleID[2]			= IDC_EDIT_OUTPUT_SINGLE_3;

	m_iRadioLoopEndlessID[2]			= IDC_RADIO_LOOP_ENDLESS_3;
	m_iRadioLoopFiniteID[2]				= IDC_RADIO_LOOP_FINITE_3;
	m_iEditLoopFiniteID[2]				= IDC_EDIT_LOOP_FINITE_3;
	m_iSpinLoopFiniteID[2]				= IDC_SPIN_LOOP_FINITE_3;

	m_iEditTimeoutID[2]					= IDC_EDIT_TIMEOUT_3;
	m_iSpinTimeoutID[2]					= IDC_SPIN_TIMEOUT_3;

	m_iButtonStartAppendOutputID[2]		= IDC_BUTTON_START_APPEND_OUTPUT_3;
	m_iButtonStopID[2]					= IDC_BUTTON_STOP_3;

	m_iPlotID[2]						= IDC_PLOT_3;	

	m_iComboFunctionID[3]				= IDC_COMBO_FUNCTION_4;

	m_iRadioAOModeWraparoundID[3]		= IDC_RADIO_AO_WRAPAROUND_4;
	m_iRadioAOModeContinuousID[3]		= IDC_RADIO_AO_CONTINUOUS_4;

	m_iCheckEnableExtTriggerID[3]		= IDC_CHECK_ENABLE_EXT_TRIGGER_4;

	m_iRadioTriggerSoftwareID[3]		= IDC_RADIO_TRIGGER_SOFTWARE_4;
	m_iRadioTriggerExtDigitalID[3]		= IDC_RADIO_TRIGGER_DIGITAL_4;

	m_iRadioTriggerRisingID[3]			= IDC_RADIO_TRIGGER_RISING_4;
	m_iRadioTriggerFallingID[3]			= IDC_RADIO_TRIGGER_FALLING_4;
	m_iRadioTriggerBothID[3]			= IDC_RADIO_TRIGGER_BOTH_4;

	m_iEditOutputRateID[3]				= IDC_EDIT_OUTPUT_RATE_4;
	m_iSpinOutputRateID[3]				= IDC_SPIN_OUTPUT_RATE_4;

	m_iEditSignalLengthID[3]			= IDC_EDIT_SIGNAL_LENGTH_4;
	m_iSpinSignalLengthID[3]			= IDC_SPIN_SIGNAL_LENGTH_4;

	m_iComboSignalFormID[3]				= IDC_COMBO_SIGNAL_FORM_4;

	m_iEditFrequencyFromID[3]			= IDC_EDIT_FREQUENCY_FROM_4;
	m_iSpinFrequencyFromID[3]			= IDC_SPIN_FREQUENCY_FROM_4;

	m_iEditFrequencyToID[3]				= IDC_EDIT_FREQUENCY_TO_4;
	m_iSpinFrequencyToID[3]				= IDC_SPIN_FREQUENCY_TO_4;

	m_iEditAmplitudeFromID[3]			= IDC_EDIT_AMPLITUDE_FROM_4;
	m_iSpinAmplitudeFromID[3]			= IDC_SPIN_AMPLITUDE_FROM_4;

	m_iEditAmplitudeToID[3]				= IDC_EDIT_AMPLITUDE_TO_4;
	m_iSpinAmplitudeToID[3]				= IDC_SPIN_AMPLITUDE_TO_4;

	m_iEditOutputSingleID[3]			= IDC_EDIT_OUTPUT_SINGLE_4;

	m_iRadioLoopEndlessID[3]			= IDC_RADIO_LOOP_ENDLESS_4;
	m_iRadioLoopFiniteID[3]				= IDC_RADIO_LOOP_FINITE_4;
	m_iEditLoopFiniteID[3]				= IDC_EDIT_LOOP_FINITE_4;
	m_iSpinLoopFiniteID[3]				= IDC_SPIN_LOOP_FINITE_4;

	m_iEditTimeoutID[3]					= IDC_EDIT_TIMEOUT_4;
	m_iSpinTimeoutID[3]					= IDC_SPIN_TIMEOUT_4;

	m_iButtonStartAppendOutputID[3]		= IDC_BUTTON_START_APPEND_OUTPUT_4;
	m_iButtonStopID[3]					= IDC_BUTTON_STOP_4;

	m_iPlotID[3]						= IDC_PLOT_4;	

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		m_pPlotWin[index_channel] = NULL;
		
		m_rectPlotClient[index_channel].SetRectEmpty();

		m_rectPlotChild[index_channel].SetRectEmpty();
	}

	m_iCurrentBoardIndex = 0;

	m_pPropertySheet = NULL;
}

CAnalogOutputPP::~CAnalogOutputPP()
{
	for(int index_board = 0; index_board < ME4000_MAX_DEVICES; index_board++)
	{
		for(int index_channel = 0; index_channel < 4; index_channel++)
		{
			if(m_sBoardAO[index_board].m_sAOChannel[index_channel].m_psDataBuffer != NULL)
			{
				delete m_sBoardAO[index_board].m_sAOChannel[index_channel].m_psDataBuffer;
			}
		}
	}
}

void CAnalogOutputPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_FUNCTION_1, m_comboFunction[0]);

	DDX_Control(pDX, IDC_SPIN_OUTPUT_RATE_1, m_spinOutputRate[0]);
	
	DDX_Control(pDX, IDC_SPIN_SIGNAL_LENGTH_1, m_spinSignalLength[0]);
	
	DDX_Control(pDX, IDC_COMBO_SIGNAL_FORM_1, m_comboSignalForm[0]);
	
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_FROM_1, m_spinFrequencyFrom[0]);
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_TO_1, m_spinFrequencyTo[0]);
	
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_FROM_1, m_spinAmplitudeFrom[0]);
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_TO_1, m_spinAmplitudeTo[0]);

	DDX_Control(pDX, IDC_SPIN_LOOP_FINITE_1, m_spinLoopFinite[0]);

	DDX_Control(pDX, IDC_SPIN_TIMEOUT_1, m_spinTimeout[0]);

	DDX_Control(pDX, IDC_COMBO_FUNCTION_2, m_comboFunction[1]);

	DDX_Control(pDX, IDC_SPIN_OUTPUT_RATE_2, m_spinOutputRate[1]);
	
	DDX_Control(pDX, IDC_SPIN_SIGNAL_LENGTH_2, m_spinSignalLength[1]);
	
	DDX_Control(pDX, IDC_COMBO_SIGNAL_FORM_2, m_comboSignalForm[1]);
	
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_FROM_2, m_spinFrequencyFrom[1]);
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_TO_2, m_spinFrequencyTo[1]);
	
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_FROM_2, m_spinAmplitudeFrom[1]);
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_TO_2, m_spinAmplitudeTo[1]);

	DDX_Control(pDX, IDC_SPIN_LOOP_FINITE_2, m_spinLoopFinite[1]);

	DDX_Control(pDX, IDC_SPIN_TIMEOUT_2, m_spinTimeout[1]);

	DDX_Control(pDX, IDC_COMBO_FUNCTION_3, m_comboFunction[2]);

	DDX_Control(pDX, IDC_SPIN_OUTPUT_RATE_3, m_spinOutputRate[2]);
	
	DDX_Control(pDX, IDC_SPIN_SIGNAL_LENGTH_3, m_spinSignalLength[2]);
	
	DDX_Control(pDX, IDC_COMBO_SIGNAL_FORM_3, m_comboSignalForm[2]);
	
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_FROM_3, m_spinFrequencyFrom[2]);
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_TO_3, m_spinFrequencyTo[2]);
	
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_FROM_3, m_spinAmplitudeFrom[2]);
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_TO_3, m_spinAmplitudeTo[2]);

	DDX_Control(pDX, IDC_SPIN_LOOP_FINITE_3, m_spinLoopFinite[2]);

	DDX_Control(pDX, IDC_SPIN_TIMEOUT_3, m_spinTimeout[2]);

	DDX_Control(pDX, IDC_COMBO_FUNCTION_4, m_comboFunction[3]);

	DDX_Control(pDX, IDC_SPIN_OUTPUT_RATE_4, m_spinOutputRate[3]);
	
	DDX_Control(pDX, IDC_SPIN_SIGNAL_LENGTH_4, m_spinSignalLength[3]);
	
	DDX_Control(pDX, IDC_COMBO_SIGNAL_FORM_4, m_comboSignalForm[3]);
	
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_FROM_4, m_spinFrequencyFrom[3]);
	DDX_Control(pDX, IDC_SPIN_FREQUENCY_TO_4, m_spinFrequencyTo[3]);
	
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_FROM_4, m_spinAmplitudeFrom[3]);
	DDX_Control(pDX, IDC_SPIN_AMPLITUDE_TO_4, m_spinAmplitudeTo[3]);

	DDX_Control(pDX, IDC_SPIN_LOOP_FINITE_4, m_spinLoopFinite[3]);

	DDX_Control(pDX, IDC_SPIN_TIMEOUT_4, m_spinTimeout[3]);

	DDX_Control(pDX, IDC_SPIN_SINGLE_SIMULTANEOUS_TIMEOUT, m_spinSingleSimultaneousTimeout);

	DDX_Control(pDX, IDC_SPIN_START_SYNCHRONOUS_TIMEOUT, m_spinStartSynchronousTimeout);

	//{{AFX_DATA_MAP(CAnalogOutputPP)
	DDX_Control(pDX, IDC_COMBO_BOARD, m_comboBoardNumber);
	//}}AFX_DATA_MAP

	int i_loop_endless;
	
	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		if( !pDX->m_bSaveAndValidate )
		{
			m_comboFunction[index_channel].SetCurSel( (int)m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iFunction );
		
			m_comboSignalForm[index_channel].SetCurSel( (int)m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iOutputSignalForm );

			i_loop_endless = (m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_bInfiniteLoops ? 0 : 1); 
		}

		DDX_Radio(pDX, m_iRadioAOModeWraparoundID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iBufferMode);

		DDX_Radio(pDX, m_iRadioTriggerSoftwareID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iTriggerType);

		DDX_Radio(pDX, m_iRadioTriggerRisingID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iTriggerExtEdge);

		DDX_Check(pDX, m_iCheckEnableExtTriggerID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_bExtTriggerEnable);
		
		DDX_Text(pDX, m_iEditOutputRateID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_uiOutputRate);

		DDX_Text(pDX, m_iEditSignalLengthID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_uiSignalLengthSeconds);

		DDX_Text(pDX, m_iEditFrequencyFromID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_uiSweepFrequencyFrom);

		DDX_Text(pDX, m_iEditFrequencyToID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_uiSweepFrequencyTo);

		DDX_Text(pDX, m_iEditAmplitudeFromID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_uiSweepAmplitudeFrom);

		DDX_Text(pDX, m_iEditAmplitudeToID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_uiSweepAmplitudeTo);

		DDX_Text(pDX, m_iEditOutputSingleID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_dSingleValue);

		DDX_Radio(pDX, m_iRadioLoopEndlessID[index_channel], i_loop_endless);

		DDX_Text(pDX, m_iEditLoopFiniteID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_uiFiniteLoops);

		DDX_Text(pDX, m_iEditTimeoutID[index_channel], m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_ulTimeout);

		if(pDX->m_bSaveAndValidate)
		{
			m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iFunction = (int)m_comboFunction[index_channel].GetCurSel();
		
			m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iOutputSignalForm = (int)m_comboSignalForm[index_channel].GetCurSel();

			m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_bInfiniteLoops = ( (i_loop_endless == 0) ? TRUE : FALSE);
		}
	}

	DDX_Radio(pDX, IDC_RADIO_TRIGGER_SOFTWARE_SINGLE_SIMULTANEOUS, m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger);

	DDX_Text(pDX, IDC_EDIT_TIMEOUT_SINGLE_SIMULTANEOUS, m_sBoardAO[m_iCurrentBoardIndex].m_ulSingleSimultaneousTimeout);

	DDX_Radio(pDX, IDC_RADIO_TRIGGER_SOFTWARE_START_SYNCHRONOUS, m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger);

	DDX_Text(pDX, IDC_EDIT_TIMEOUT_START_SYNCHRONOUS, m_sBoardAO[m_iCurrentBoardIndex].m_ulStartSynchronousTimeout);
}

BEGIN_MESSAGE_MAP(CAnalogOutputPP, CPropertyPage)
	//{{AFX_MSG_MAP(CAnalogOutputPP)
	ON_BN_CLICKED(ID_EXIT, OnExit)
	ON_BN_CLICKED(IDC_RADIO_AO_WRAPAROUND_1, OnRadioAoWraparound1)
	ON_BN_CLICKED(IDC_RADIO_AO_CONTINUOUS_1, OnRadioAoContinuous1)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_SOFTWARE_1, OnRadioTriggerSoftware1)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_DIGITAL_1, OnRadioTriggerDigital1)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_EXT_TRIGGER_1, OnCheckEnableExtTrigger1)
	ON_BN_CLICKED(IDC_RADIO_LOOP_ENDLESS_1, OnRadioLoopEndless1)
	ON_BN_CLICKED(IDC_RADIO_LOOP_FINITE_1, OnRadioLoopFinite1)
	ON_BN_CLICKED(IDC_BUTTON_START_APPEND_OUTPUT_1, OnButtonStartAppendOutput1)
	ON_BN_CLICKED(IDC_BUTTON_STOP_1, OnButtonStop1)
	ON_BN_CLICKED(IDC_RADIO_AO_WRAPAROUND_2, OnRadioAoWraparound2)
	ON_BN_CLICKED(IDC_RADIO_AO_CONTINUOUS_2, OnRadioAoContinuous2)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_SOFTWARE_2, OnRadioTriggerSoftware2)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_DIGITAL_2, OnRadioTriggerDigital2)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_EXT_TRIGGER_2, OnCheckEnableExtTrigger2)
	ON_BN_CLICKED(IDC_RADIO_LOOP_ENDLESS_2, OnRadioLoopEndless2)
	ON_BN_CLICKED(IDC_RADIO_LOOP_FINITE_2, OnRadioLoopFinite2)
	ON_BN_CLICKED(IDC_BUTTON_START_APPEND_OUTPUT_2, OnButtonStartAppendOutput2)
	ON_BN_CLICKED(IDC_BUTTON_STOP_2, OnButtonStop2)
	ON_BN_CLICKED(IDC_RADIO_AO_WRAPAROUND_3, OnRadioAoWraparound3)
	ON_BN_CLICKED(IDC_RADIO_AO_CONTINUOUS_3, OnRadioAoContinuous3)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_SOFTWARE_3, OnRadioTriggerSoftware3)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_DIGITAL_3, OnRadioTriggerDigital3)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_EXT_TRIGGER_3, OnCheckEnableExtTrigger3)
	ON_BN_CLICKED(IDC_RADIO_LOOP_ENDLESS_3, OnRadioLoopEndless3)
	ON_BN_CLICKED(IDC_RADIO_LOOP_FINITE_3, OnRadioLoopFinite3)
	ON_BN_CLICKED(IDC_BUTTON_START_APPEND_OUTPUT_3, OnButtonStartAppendOutput3)
	ON_BN_CLICKED(IDC_BUTTON_STOP_3, OnButtonStop3)
	ON_BN_CLICKED(IDC_RADIO_AO_WRAPAROUND_4, OnRadioAoWraparound4)
	ON_BN_CLICKED(IDC_RADIO_AO_CONTINUOUS_4, OnRadioAoContinuous4)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_SOFTWARE_4, OnRadioTriggerSoftware4)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_DIGITAL_4, OnRadioTriggerDigital4)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_EXT_TRIGGER_4, OnCheckEnableExtTrigger4)
	ON_BN_CLICKED(IDC_RADIO_LOOP_ENDLESS_4, OnRadioLoopEndless4)
	ON_BN_CLICKED(IDC_RADIO_LOOP_FINITE_4, OnRadioLoopFinite4)
	ON_BN_CLICKED(IDC_BUTTON_START_APPEND_OUTPUT_4, OnButtonStartAppendOutput4)
	ON_BN_CLICKED(IDC_BUTTON_STOP_4, OnButtonStop4)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SINGLE_SIMULTANEOUS, OnSingleSimultaneous)
	ON_BN_CLICKED(IDC_START_SYNCHRONOUS, OnStartSynchronous)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT_OUTPUT_SINGLE_1, OnChangeEditOutputSingle1)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNCTION_1, OnSelchangeComboFunction1)
	ON_CBN_SELCHANGE(IDC_COMBO_SIGNAL_FORM_1, OnSelchangeComboSignalForm1)
	ON_EN_KILLFOCUS(IDC_EDIT_OUTPUT_RATE_1, OnKillfocusEditOutputRate1)
	ON_EN_KILLFOCUS(IDC_EDIT_SIGNAL_LENGTH_1, OnKillfocusEditSignalLength1)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_FROM_1, OnKillfocusEditFrequencyFrom1)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_TO_1, OnKillfocusEditFrequencyTo1)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_FROM_1, OnKillfocusEditAmplitudeFrom1)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_TO_1, OnKillfocusEditAmplitudeTo1)
	ON_EN_CHANGE(IDC_EDIT_OUTPUT_SINGLE_2, OnChangeEditOutputSingle2)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNCTION_2, OnSelchangeComboFunction2)
	ON_CBN_SELCHANGE(IDC_COMBO_SIGNAL_FORM_2, OnSelchangeComboSignalForm2)
	ON_EN_KILLFOCUS(IDC_EDIT_OUTPUT_RATE_2, OnKillfocusEditOutputRate2)
	ON_EN_KILLFOCUS(IDC_EDIT_SIGNAL_LENGTH_2, OnKillfocusEditSignalLength2)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_FROM_2, OnKillfocusEditFrequencyFrom2)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_TO_2, OnKillfocusEditFrequencyTo2)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_FROM_2, OnKillfocusEditAmplitudeFrom2)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_TO_2, OnKillfocusEditAmplitudeTo2)
	ON_EN_CHANGE(IDC_EDIT_OUTPUT_SINGLE_3, OnChangeEditOutputSingle3)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNCTION_3, OnSelchangeComboFunction3)
	ON_CBN_SELCHANGE(IDC_COMBO_SIGNAL_FORM_3, OnSelchangeComboSignalForm3)
	ON_EN_KILLFOCUS(IDC_EDIT_OUTPUT_RATE_3, OnKillfocusEditOutputRate3)
	ON_EN_KILLFOCUS(IDC_EDIT_SIGNAL_LENGTH_3, OnKillfocusEditSignalLength3)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_FROM_3, OnKillfocusEditFrequencyFrom3)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_TO_3, OnKillfocusEditFrequencyTo3)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_FROM_3, OnKillfocusEditAmplitudeFrom3)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_TO_3, OnKillfocusEditAmplitudeTo3)
	ON_EN_CHANGE(IDC_EDIT_OUTPUT_SINGLE_4, OnChangeEditOutputSingle4)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNCTION_4, OnSelchangeComboFunction4)
	ON_CBN_SELCHANGE(IDC_COMBO_SIGNAL_FORM_4, OnSelchangeComboSignalForm4)
	ON_EN_KILLFOCUS(IDC_EDIT_OUTPUT_RATE_4, OnKillfocusEditOutputRate4)
	ON_EN_KILLFOCUS(IDC_EDIT_SIGNAL_LENGTH_4, OnKillfocusEditSignalLength4)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_FROM_4, OnKillfocusEditFrequencyFrom4)
	ON_EN_KILLFOCUS(IDC_EDIT_FREQUENCY_TO_4, OnKillfocusEditFrequencyTo4)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_FROM_4, OnKillfocusEditAmplitudeFrom4)
	ON_EN_KILLFOCUS(IDC_EDIT_AMPLITUDE_TO_4, OnKillfocusEditAmplitudeTo4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OUTPUT_RATE_1, OnDeltaposSpinOutputRate1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIGNAL_LENGTH_1, OnDeltaposSpinSignalLength1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_FROM_1, OnDeltaposSpinFrequencyFrom1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_TO_1, OnDeltaposSpinFrequencyTo1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_FROM_1, OnDeltaposSpinAmplitudeFrom1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_TO_1, OnDeltaposSpinAmplitudeTo1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OUTPUT_RATE_2, OnDeltaposSpinOutputRate2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIGNAL_LENGTH_2, OnDeltaposSpinSignalLength2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_FROM_2, OnDeltaposSpinFrequencyFrom2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_TO_2, OnDeltaposSpinFrequencyTo2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_FROM_2, OnDeltaposSpinAmplitudeFrom2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_TO_2, OnDeltaposSpinAmplitudeTo2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OUTPUT_RATE_3, OnDeltaposSpinOutputRate3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIGNAL_LENGTH_3, OnDeltaposSpinSignalLength3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_FROM_3, OnDeltaposSpinFrequencyFrom3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_TO_3, OnDeltaposSpinFrequencyTo3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_FROM_3, OnDeltaposSpinAmplitudeFrom3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_TO_3, OnDeltaposSpinAmplitudeTo3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OUTPUT_RATE_4, OnDeltaposSpinOutputRate4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIGNAL_LENGTH_4, OnDeltaposSpinSignalLength4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_FROM_4, OnDeltaposSpinFrequencyFrom4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FREQUENCY_TO_4, OnDeltaposSpinFrequencyTo4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_FROM_4, OnDeltaposSpinAmplitudeFrom4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AMPLITUDE_TO_4, OnDeltaposSpinAmplitudeTo4)

	ON_BN_CLICKED(IDC_RADIO_TRIGGER_SOFTWARE_SINGLE_SIMULTANEOUS, OnRadioSingleSimultaneousSoftware)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_DIGITAL_SINGLE_SIMULTANEOUS, OnRadioSingleSimultaneousDigitalExt)

	ON_BN_CLICKED(IDC_RADIO_TRIGGER_SOFTWARE_START_SYNCHRONOUS, OnRadioStartSynchronousSoftware)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_DIGITAL_START_SYNCHRONOUS, OnRadioStartSynchronousDigitalExt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalogOutputPP message handlers

BOOL CAnalogOutputPP::OnInitDialog() 
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

	m_pPlotWin[0] = GetDlgItem(IDC_PLOT_1);
	
	m_pPlotWin[1] = GetDlgItem(IDC_PLOT_2);
	
	m_pPlotWin[2] = GetDlgItem(IDC_PLOT_3);
	
	m_pPlotWin[3] = GetDlgItem(IDC_PLOT_4);
	
	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		m_spinOutputRate[index_channel].SetRange32(MIN_OUTPUT_RATE, MAX_OUTPUT_RATE);
		
		m_spinSignalLength[index_channel].SetRange32(MIN_SIGNAL_LENGTH, MAX_SIGNAL_LENGTH);
		
		m_spinFrequencyFrom[index_channel].SetRange32(MIN_FREQ, MAX_FREQ);
		m_spinFrequencyTo[index_channel].SetRange32(MIN_FREQ, MAX_FREQ);
		
		m_spinAmplitudeFrom[index_channel].SetRange32(MIN_AMP, MAX_AMP);
		m_spinAmplitudeTo[index_channel].SetRange32(MIN_AMP, MAX_AMP);

		m_spinLoopFinite[index_channel].SetRange32(1, 100000);

		m_spinTimeout[index_channel].SetRange32(0, 300);

		CRect rect_plot;

		m_pPlotWin[index_channel]->GetClientRect(rect_plot);
		
		m_rectPlotClient[index_channel] = rect_plot;

		m_rectPlotClient[index_channel].DeflateRect(1, 1);

		m_pPlotWin[index_channel]->GetWindowRect(&rect_plot);

		ScreenToClient(&rect_plot);

		m_rectPlotChild[index_channel] = rect_plot;

		m_rectPlotChild[index_channel].DeflateRect(1, 1);
	}

	m_spinSingleSimultaneousTimeout.SetRange32(0, 300);
	
	m_spinStartSynchronousTimeout.SetRange32(0, 300);
	
	SetControlStates();

	SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAnalogOutputPP::OnExit() 
{
	// TODO: Add your control notification handler code here
	
	if(AfxMessageBox("This will terminate the test programm", MB_OKCANCEL) == IDOK)
	{
		m_pPropertySheet->EndDialog(0);
	}
}

void CAnalogOutputPP::OnSelchangeComboFunction(int index_channel)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	p_ao_channel->m_iFunction = m_comboFunction[index_channel].GetCurSel();

	if( (p_ao_channel->m_iFunction == AO_FUNCTION_SINGLE)||
					(p_ao_channel->m_iFunction == AO_FUNCTION_SINGLE_SIMULTANEOUS) )
	{
		GetDlgItem(m_iRadioAOModeWraparoundID[index_channel])->EnableWindow(FALSE);
		GetDlgItem(m_iRadioAOModeContinuousID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditOutputRateID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditSignalLengthID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iComboSignalFormID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditFrequencyFromID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditFrequencyToID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditAmplitudeFromID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditAmplitudeToID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditOutputSingleID[index_channel])->EnableWindow(TRUE);

		GetDlgItem(m_iRadioLoopEndlessID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iRadioLoopFiniteID[index_channel])->EnableWindow(FALSE);

		GetDlgItem(m_iEditLoopFiniteID[index_channel])->EnableWindow(FALSE);

		SetDlgItemText(m_iButtonStartAppendOutputID[index_channel], "Output");

		GetDlgItem(m_iButtonStopID[index_channel])->EnableWindow(FALSE);

		if(p_ao_channel->m_iFunction == AO_FUNCTION_SINGLE)
		{
			GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->ShowWindow(SW_HIDE);

			GetDlgItem(m_iRadioTriggerSoftwareID[index_channel])->ShowWindow(SW_SHOW);
			GetDlgItem(m_iRadioTriggerExtDigitalID[index_channel])->ShowWindow(SW_SHOW);

			if(p_ao_channel->m_iTriggerType == AO_TRIGGER_TYPE_SOFTWARE)
			{
				GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(FALSE);

				GetDlgItem(m_iEditTimeoutID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iSpinTimeoutID[index_channel])->EnableWindow(FALSE);
			}
			else // if(p_ao_channel->m_iTriggerType == AO_TRIGGER_TYPE_EXT_DIGITAL)
			{
				GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(TRUE);
				GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(TRUE);
				GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(TRUE);

				GetDlgItem(m_iEditTimeoutID[index_channel])->EnableWindow(TRUE);
				GetDlgItem(m_iSpinTimeoutID[index_channel])->EnableWindow(TRUE);
			}

			GetDlgItem(m_iButtonStartAppendOutputID[index_channel])->EnableWindow(TRUE);
		}
		else // if(p_ao_channel->m_iFunction == AO_FUNCTION_SINGLE_SIMULTANEOUS)
		{
			GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->ShowWindow(SW_SHOW);

			GetDlgItem(m_iRadioTriggerSoftwareID[index_channel])->ShowWindow(SW_HIDE);
			GetDlgItem(m_iRadioTriggerExtDigitalID[index_channel])->ShowWindow(SW_HIDE);

			if(m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger == AO_TRIGGER_TYPE_SOFTWARE)
			{
				GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->EnableWindow(FALSE);

				GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(FALSE);
			}
			else // if(m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger == AO_TRIGGER_TYPE_EXT_DIGITAL)
			{
				GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->EnableWindow(TRUE);

				if(p_ao_channel->m_bExtTriggerEnable)
				{
					GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(TRUE);
					GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(TRUE);
					GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(TRUE);
				}
				else // if(!p_ao_channel->m_bExtTriggerEnable)
				{
					GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(FALSE);
					GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(FALSE);
					GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(FALSE);
				}
			}

			GetDlgItem(m_iEditTimeoutID[index_channel])->EnableWindow(FALSE);
			GetDlgItem(m_iSpinTimeoutID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iButtonStartAppendOutputID[index_channel])->EnableWindow(FALSE);
		}
	}
	else // if( (p_ao_channel->m_iFunction == AO_FUNCTION_START)||
		 //			(p_ao_channel->m_iFunction == AO_FUNCTION_START_SYNCHRONOUS) )
	{
		GetDlgItem(m_iRadioAOModeWraparoundID[index_channel])->EnableWindow(TRUE);
		GetDlgItem(m_iRadioAOModeContinuousID[index_channel])->EnableWindow(TRUE);

		GetDlgItem(m_iEditOutputRateID[index_channel])->EnableWindow(TRUE);

		GetDlgItem(m_iEditSignalLengthID[index_channel])->EnableWindow(TRUE);

		GetDlgItem(m_iComboSignalFormID[index_channel])->EnableWindow(TRUE);

		GetDlgItem(m_iEditFrequencyFromID[index_channel])->EnableWindow(TRUE);

		GetDlgItem(m_iEditFrequencyToID[index_channel])->EnableWindow(TRUE);

		GetDlgItem(m_iEditAmplitudeFromID[index_channel])->EnableWindow(TRUE);

		GetDlgItem(m_iEditAmplitudeToID[index_channel])->EnableWindow(TRUE);

		GetDlgItem(m_iEditOutputSingleID[index_channel])->EnableWindow(FALSE);

		SetDlgItemText(m_iButtonStartAppendOutputID[index_channel], "Start");

		GetDlgItem(m_iButtonStopID[index_channel])->EnableWindow(FALSE);

		if(p_ao_channel->m_iBufferMode == AO_BUFFER_MODE_WRAPAROUND)
		{
			GetDlgItem(m_iRadioLoopEndlessID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iRadioLoopFiniteID[index_channel])->EnableWindow(TRUE);

			if(p_ao_channel->m_bInfiniteLoops)
			{
				GetDlgItem(m_iEditLoopFiniteID[index_channel])->EnableWindow(FALSE);
			}
			else
			{
				GetDlgItem(m_iEditLoopFiniteID[index_channel])->EnableWindow(TRUE);
			}
		}
		else // if(p_ao_channel->m_iBufferMode == AO_BUFFER_MODE_ONTINUOUS)
		{
			GetDlgItem(m_iRadioLoopEndlessID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iRadioLoopFiniteID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iEditLoopFiniteID[index_channel])->EnableWindow(FALSE);
		}

		if(p_ao_channel->m_iFunction == AO_FUNCTION_START)
		{
			GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->ShowWindow(SW_HIDE);

			GetDlgItem(m_iRadioTriggerSoftwareID[index_channel])->ShowWindow(SW_SHOW);
			GetDlgItem(m_iRadioTriggerExtDigitalID[index_channel])->ShowWindow(SW_SHOW);

			if(p_ao_channel->m_iTriggerType == AO_TRIGGER_TYPE_SOFTWARE)
			{
				GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(FALSE);

				GetDlgItem(m_iEditTimeoutID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iSpinTimeoutID[index_channel])->EnableWindow(FALSE);
			}
			else // if(p_ao_channel->m_iTriggerType == AO_TRIGGER_TYPE_EXT_DIGITAL)
			{
				GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(TRUE);
				GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(TRUE);
				GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(TRUE);

				GetDlgItem(m_iEditTimeoutID[index_channel])->EnableWindow(TRUE);
				GetDlgItem(m_iSpinTimeoutID[index_channel])->EnableWindow(TRUE);
			}

			GetDlgItem(m_iButtonStartAppendOutputID[index_channel])->EnableWindow(TRUE);
		}
		else // if(p_ao_channel->m_iFunction == AO_FUNCTION_START_SYNCHRONOUS)
		{
			GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->ShowWindow(SW_SHOW);

			GetDlgItem(m_iRadioTriggerSoftwareID[index_channel])->ShowWindow(SW_HIDE);
			GetDlgItem(m_iRadioTriggerExtDigitalID[index_channel])->ShowWindow(SW_HIDE);

			if(m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger == AO_TRIGGER_TYPE_SOFTWARE)
			{
				GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->EnableWindow(FALSE);

				GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(FALSE);
			}
			else // if(m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger == AO_TRIGGER_TYPE_EXT_DIGITAL)
			{
				GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->EnableWindow(TRUE);

				if(p_ao_channel->m_bExtTriggerEnable)
				{
					GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(TRUE);
					GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(TRUE);
					GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(TRUE);
				}
				else // if(!p_ao_channel->m_bExtTriggerEnable)
				{
					GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(FALSE);
					GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(FALSE);
					GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(FALSE);
				}
			}

			GetDlgItem(m_iEditTimeoutID[index_channel])->EnableWindow(FALSE);
			GetDlgItem(m_iSpinTimeoutID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iButtonStartAppendOutputID[index_channel])->EnableWindow(FALSE);
		}
	}

	SetSimultaneousControls();
	
	RedrawPlot(index_channel);
}

void CAnalogOutputPP::OnRadioAOWraparound(int index_channel)
{
	GetDlgItem(m_iRadioLoopEndlessID[index_channel])->EnableWindow(TRUE);

	GetDlgItem(m_iRadioLoopFiniteID[index_channel])->EnableWindow(TRUE);

	if(m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_bInfiniteLoops)
	{
		GetDlgItem(m_iEditLoopFiniteID[index_channel])->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(m_iEditLoopFiniteID[index_channel])->EnableWindow(TRUE);
	}

	m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iBufferMode = AO_BUFFER_MODE_WRAPAROUND;

	RedrawPlot(index_channel);
}

void CAnalogOutputPP::OnRadioAOContinuous(int index_channel)
{
	GetDlgItem(m_iRadioLoopEndlessID[index_channel])->EnableWindow(FALSE);

	GetDlgItem(m_iRadioLoopFiniteID[index_channel])->EnableWindow(FALSE);

	GetDlgItem(m_iEditLoopFiniteID[index_channel])->EnableWindow(FALSE);

	m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iBufferMode = AO_BUFFER_MODE_CONTINUOUS;

	RedrawPlot(index_channel);
}
	
	
void CAnalogOutputPP::OnRadioTriggerSoftware(int index_channel)
{
	GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(FALSE);
	GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(FALSE);
	GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(FALSE);

	GetDlgItem(m_iEditTimeoutID[index_channel])->EnableWindow(FALSE);
	GetDlgItem(m_iSpinTimeoutID[index_channel])->EnableWindow(FALSE);

	m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iTriggerType = AO_TRIGGER_TYPE_SOFTWARE;
}

void CAnalogOutputPP::OnRadioTriggerDigital(int index_channel)
{
	GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(TRUE);
	GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(TRUE);
	GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(TRUE);

	GetDlgItem(m_iEditTimeoutID[index_channel])->EnableWindow(TRUE);
	GetDlgItem(m_iSpinTimeoutID[index_channel])->EnableWindow(TRUE);

	m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iTriggerType = AO_TRIGGER_TYPE_EXT_DIGITAL;
}

void CAnalogOutputPP::OnCheckEnableExtTrigger(int index_channel)
{
	BOOL b_enable = IsDlgButtonChecked(m_iCheckEnableExtTriggerID[index_channel]);

	GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(b_enable);
	GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(b_enable);
	GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(b_enable);

	m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_bExtTriggerEnable = b_enable;
}
	
void CAnalogOutputPP::OnRadioLoopEndless(int index_channel)
{
	m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_bInfiniteLoops = TRUE;
	
	GetDlgItem(m_iEditLoopFiniteID[index_channel])->EnableWindow(FALSE);
}

void CAnalogOutputPP::OnRadioLoopFinite(int index_channel)
{
	m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_bInfiniteLoops = FALSE;
	
	GetDlgItem(m_iEditLoopFiniteID[index_channel])->EnableWindow(TRUE);
}

void CAnalogOutputPP::OnButtonStartAppendOutput(int index_channel)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	if( !p_ao_channel->m_bAOActive )
	{
		CDataExchange dx(this, TRUE);
		
		DoDataExchange(&dx);

		int i_error;
		
		if(p_ao_channel->m_iFunction == AO_FUNCTION_SINGLE)
		{
			short s_digit;
			
			i_error = me4000AOVoltToDigit(	p_ao_channel->m_dSingleValue,		// dVolt,
											&s_digit						);	// psDigit

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}
			
			int i_trigger_mode;

			if(p_ao_channel->m_iTriggerType == AO_TRIGGER_TYPE_SOFTWARE)
			{
				i_trigger_mode = ME4000_AO_TRIGGER_SOFTWARE;
			}
			else // if(p_ao_channel->m_iTriggerType == AO_TRIGGER_TYPE_EXT_DIGITAL)
			{
				i_trigger_mode = ME4000_AO_TRIGGER_EXT_DIGITAL;
			}
			
			int i_ext_trigger_edge;

			if(p_ao_channel->m_iTriggerType != AO_TRIGGER_TYPE_EXT_DIGITAL)
			{
				i_ext_trigger_edge = ME4000_VALUE_NOT_USED;
			}
			else if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_RISING)
			{
				i_ext_trigger_edge = ME4000_AO_TRIGGER_EXT_EDGE_RISING;
			}
			else if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_FALLING)
			{
				i_ext_trigger_edge = ME4000_AO_TRIGGER_EXT_EDGE_FALLING;
			}
			else if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_BOTH)
			{
				i_ext_trigger_edge = ME4000_AO_TRIGGER_EXT_EDGE_BOTH;
			}

			unsigned long ul_timeout_seconds = p_ao_channel->m_ulTimeout;

			if(p_ao_channel->m_iTriggerType != AO_TRIGGER_TYPE_EXT_DIGITAL)
			{
				ul_timeout_seconds = ME4000_VALUE_NOT_USED;
			}

			i_error = me4000AOSingle(	m_iCurrentBoardIndex,			// uiBoardNumber,
										index_channel,					// uiChannelNumber,
										i_trigger_mode,					// iTriggerMode,
										i_ext_trigger_edge,				// iExtTriggerEdge,
										ul_timeout_seconds,				// ulTimeOutSeconds,
										s_digit						);	// sValue	
		}
		else
		{
			i_error = PrepareChannel(p_ao_channel);

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}

			i_error = me4000AOStart(	m_iCurrentBoardIndex,		// uiBoardNumber,
										index_channel			);	// uiChannelNumber,

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}

			MarkChannelActive(p_ao_channel);
		}
	}
	else // if(p_ao_channel->m_bAOActive)
	{
		if(p_ao_channel->m_iLastBufferMode == AO_BUFFER_MODE_WRAPAROUND)
		{
			me4000AOStop(	m_iCurrentBoardIndex,				// uiBoardNumber,
							index_channel,						// uiChannelNumber,
							ME4000_AO_STOP_MODE_LAST_VALUE	);	// iStopMode		
		}
		else if( (p_ao_channel->m_iLastBufferMode == AO_BUFFER_MODE_CONTINUOUS)&&
														( !p_ao_channel->m_bAppendBuffer ) )
		{
			GetDlgItem(m_iButtonStartAppendOutputID[index_channel])->EnableWindow(FALSE);
			
			CDataExchange dx_read(this, TRUE);
		
			int i_output_signal_form;
			
			i_output_signal_form =  (int)m_comboSignalForm[index_channel].GetCurSel();

			double d_signal_length_seconds;

			DDX_Text(&dx_read, m_iEditSignalLengthID[index_channel], d_signal_length_seconds);

			unsigned int ui_frequency_from;
			
			DDX_Text(&dx_read, m_iEditFrequencyFromID[index_channel], ui_frequency_from);

			unsigned int ui_frequency_to;
			
			DDX_Text(&dx_read, m_iEditFrequencyToID[index_channel], ui_frequency_to);

			unsigned int ui_amplitude_from;
			
			DDX_Text(&dx_read, m_iEditAmplitudeFromID[index_channel], ui_amplitude_from);

			unsigned int ui_amplitude_to;
			
			DDX_Text(&dx_read, m_iEditAmplitudeToID[index_channel], ui_amplitude_to);

			unsigned long ul_data_count = (unsigned long)(d_signal_length_seconds * (double)p_ao_channel->m_uiOutputRate);
			
			if(p_ao_channel->m_ulDataBufferSizeValues < ul_data_count)
			{
				if(p_ao_channel->m_psDataBuffer != NULL)
				{
					delete p_ao_channel->m_psDataBuffer;
				}

				p_ao_channel->m_psDataBuffer = new short[ul_data_count];

				p_ao_channel->m_ulDataBufferSizeValues = ul_data_count;
			}
			
			WinSweepBuffer(	i_output_signal_form,					// signal_type 
							(double)ui_frequency_from,				// from_freq 
							(double)ui_frequency_to,				// to_freq 
							(double)ui_amplitude_from,				// from_amp 
							(double)ui_amplitude_to,				// to_amp 
							(double)p_ao_channel->m_uiOutputRate,	// base_freq, 
							ul_data_count,							// no_of_points 
							p_ao_channel->m_psDataBuffer,			// buffer
							1									);	// buffer_increment);

			p_ao_channel->m_ulSizeOfAppend = ul_data_count;

			p_ao_channel->m_uiAppendOffset = 0;
			
			p_ao_channel->m_bAppendBuffer = TRUE;	
		}
	}
}
	
void CAnalogOutputPP::OnButtonStop(int index_channel)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	if(p_ao_channel->m_bAOActive)
	{
		if( (p_ao_channel->m_iLastBufferMode == AO_BUFFER_MODE_WRAPAROUND)||
							(p_ao_channel->m_iLastBufferMode == AO_BUFFER_MODE_CONTINUOUS) )
		{
			me4000AOStop(	m_iCurrentBoardIndex,				// uiBoardNumber,
							index_channel,						// uiChannelNumber,
							ME4000_AO_STOP_MODE_IMMEDIATE	);	// iStopMode		
			
			p_ao_channel->m_bAOActive = FALSE;
		}

		if(p_ao_channel->m_iLastBufferMode == AO_BUFFER_MODE_CONTINUOUS)
		{
			SetDlgItemText(m_iButtonStartAppendOutputID[index_channel], "Start");

			GetDlgItem(m_iButtonStartAppendOutputID[index_channel])->EnableWindow(TRUE);

			GetDlgItem(m_iButtonStopID[index_channel])->EnableWindow(FALSE);
		}
	}
}

void CAnalogOutputPP::OnChangeEditOutputSingle(int index_channel)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	CDataExchange dx_read(this, TRUE);
		
	DDX_Text(&dx_read, m_iEditOutputSingleID[index_channel], p_ao_channel->m_dSingleValue);

	RedrawPlot(index_channel);
}
	
void CAnalogOutputPP::OnSelchangeComboSignalForm(int index_channel)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	p_ao_channel->m_iOutputSignalForm = m_comboSignalForm[index_channel].GetCurSel();
	
	RedrawPlot(index_channel);
}

void CAnalogOutputPP::OnKillfocusEditOutputRate(int index_channel)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_output_rate;
	
	DDX_Text(&dx_read, m_iEditOutputRateID[index_channel], ui_output_rate);

	if(p_ao_channel->m_uiOutputRate != ui_output_rate)
	{
		p_ao_channel->m_uiOutputRate = ui_output_rate;
		
		RedrawPlot(index_channel);
	}
}

void CAnalogOutputPP::OnKillfocusEditSignalLength(int index_channel)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_signal_length_seconds;
	
	DDX_Text(&dx_read, m_iEditSignalLengthID[index_channel], ui_signal_length_seconds);

	if(p_ao_channel->m_uiSignalLengthSeconds != ui_signal_length_seconds)
	{
		p_ao_channel->m_uiSignalLengthSeconds = ui_signal_length_seconds;

		RedrawPlot(index_channel);
	}
}

void CAnalogOutputPP::OnKillfocusEditFrequencyFrom(int index_channel)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	CDataExchange dx_read(this, TRUE);

	unsigned int ui_sweep_frequency_from;
		
	DDX_Text(&dx_read, m_iEditFrequencyFromID[index_channel], ui_sweep_frequency_from);

	if(p_ao_channel->m_uiSweepFrequencyFrom != ui_sweep_frequency_from)
	{
		p_ao_channel->m_uiSweepFrequencyFrom = ui_sweep_frequency_from;

		RedrawPlot(index_channel);
	}
}

void CAnalogOutputPP::OnKillfocusEditFrequencyTo(int index_channel)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_sweep_frequency_to;
		
	DDX_Text(&dx_read, m_iEditFrequencyToID[index_channel], ui_sweep_frequency_to);

	if(p_ao_channel->m_uiSweepFrequencyTo != ui_sweep_frequency_to)
	{
		p_ao_channel->m_uiSweepFrequencyTo = ui_sweep_frequency_to;

		RedrawPlot(index_channel);
	}
}

void CAnalogOutputPP::OnKillfocusEditAmplitudeFrom(int index_channel)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_sweep_amplitude_from;
		
	DDX_Text(&dx_read, m_iEditAmplitudeFromID[index_channel], ui_sweep_amplitude_from);

	if(p_ao_channel->m_uiSweepAmplitudeFrom != ui_sweep_amplitude_from)
	{
		p_ao_channel->m_uiSweepAmplitudeFrom = ui_sweep_amplitude_from;

		RedrawPlot(index_channel);
	}
}

void CAnalogOutputPP::OnKillfocusEditAmplitudeTo(int index_channel)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_sweep_amplitude_to;
		
	DDX_Text(&dx_read, m_iEditAmplitudeToID[index_channel], ui_sweep_amplitude_to);

	if(p_ao_channel->m_uiSweepAmplitudeTo != ui_sweep_amplitude_to)
	{
		p_ao_channel->m_uiSweepAmplitudeTo = ui_sweep_amplitude_to;

		RedrawPlot(index_channel);
	}
}

void CAnalogOutputPP::OnDeltaposSpinOutputRate(int index_channel, NM_UPDOWN* pNMUpDown)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	int i_new_output_rate = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_output_rate < MIN_OUTPUT_RATE)
	{
		i_new_output_rate = MIN_OUTPUT_RATE;
	}
	else if(i_new_output_rate > MAX_OUTPUT_RATE)
	{
		i_new_output_rate = MAX_OUTPUT_RATE;
	}

	if(p_ao_channel->m_uiOutputRate != (unsigned int)i_new_output_rate)
	{
		p_ao_channel->m_uiOutputRate = (unsigned int)i_new_output_rate;

		RedrawPlot(index_channel);
	}
}
	
void CAnalogOutputPP::OnDeltaposSpinSignalLength(int index_channel, NM_UPDOWN* pNMUpDown)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	int i_new_signal_length = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_signal_length < MIN_SIGNAL_LENGTH)
	{
		i_new_signal_length = MIN_SIGNAL_LENGTH;
	}
	else if(i_new_signal_length > MAX_SIGNAL_LENGTH)
	{
		i_new_signal_length = MAX_SIGNAL_LENGTH;
	}

	if(p_ao_channel->m_uiSignalLengthSeconds != (unsigned int)i_new_signal_length)
	{
		p_ao_channel->m_uiSignalLengthSeconds = (unsigned int)i_new_signal_length;

		RedrawPlot(index_channel);
	}
}

void CAnalogOutputPP::OnDeltaposSpinFrequencyFrom(int index_channel, NM_UPDOWN* pNMUpDown)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	int i_new_freq = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_freq < MIN_FREQ)
	{
		i_new_freq = MIN_FREQ;
	}
	else if(i_new_freq > MAX_FREQ)
	{
		i_new_freq = MAX_FREQ;
	}

	if(p_ao_channel->m_uiSweepFrequencyFrom != (unsigned int)i_new_freq)
	{
		p_ao_channel->m_uiSweepFrequencyFrom = (unsigned int)i_new_freq;

		RedrawPlot(index_channel);
	}
}

void CAnalogOutputPP::OnDeltaposSpinFrequencyTo(int index_channel, NM_UPDOWN* pNMUpDown)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	int i_new_freq = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_freq < MIN_FREQ)
	{
		i_new_freq = MIN_FREQ;
	}
	else if(i_new_freq > MAX_FREQ)
	{
		i_new_freq = MAX_FREQ;
	}

	if(p_ao_channel->m_uiSweepFrequencyTo != (unsigned int)i_new_freq)
	{
		p_ao_channel->m_uiSweepFrequencyTo = (unsigned int)i_new_freq;

		RedrawPlot(index_channel);
	}
}

void CAnalogOutputPP::OnDeltaposSpinAmplitudeFrom(int index_channel, NM_UPDOWN* pNMUpDown)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	int i_new_amp = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_amp < MIN_AMP)
	{
		i_new_amp = MIN_AMP;
	}
	else if(i_new_amp > MAX_AMP)
	{
		i_new_amp = MAX_AMP;
	}

	if(p_ao_channel->m_uiSweepAmplitudeFrom != (unsigned int)i_new_amp)
	{
		p_ao_channel->m_uiSweepAmplitudeFrom = (unsigned int)i_new_amp;

		RedrawPlot(index_channel);
	}
}

void CAnalogOutputPP::OnDeltaposSpinAmplitudeTo(int index_channel, NM_UPDOWN* pNMUpDown)
{
	SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

	int i_new_amp = pNMUpDown->iPos + pNMUpDown->iDelta;

	if(i_new_amp < MIN_AMP)
	{
		i_new_amp = MIN_AMP;
	}
	else if(i_new_amp > MAX_AMP)
	{
		i_new_amp = MAX_AMP;
	}

	if(p_ao_channel->m_uiSweepAmplitudeTo != (unsigned int)i_new_amp)
	{
		p_ao_channel->m_uiSweepAmplitudeTo = (unsigned int)i_new_amp;

		RedrawPlot(index_channel);
	}
}

void CAnalogOutputPP::SetSimultaneousControls(void)
{
	BOOL b_single_simultaneous = FALSE;

	BOOL b_start_synchronous = FALSE;

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		if(m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iFunction == AO_FUNCTION_SINGLE_SIMULTANEOUS)
		{
			b_single_simultaneous = TRUE;	
		}
		else if(m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iFunction == AO_FUNCTION_START_SYNCHRONOUS)
		{
			b_start_synchronous = TRUE;	
		}
	}

	GetDlgItem(IDC_RADIO_TRIGGER_SOFTWARE_SINGLE_SIMULTANEOUS)->EnableWindow(b_single_simultaneous);

	GetDlgItem(IDC_RADIO_TRIGGER_DIGITAL_SINGLE_SIMULTANEOUS)->EnableWindow(b_single_simultaneous);

	if( (b_single_simultaneous)&&(m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger == AO_TRIGGER_TYPE_EXT_DIGITAL) )
	{
		GetDlgItem(IDC_EDIT_TIMEOUT_SINGLE_SIMULTANEOUS)->EnableWindow(TRUE);

		GetDlgItem(IDC_SPIN_SINGLE_SIMULTANEOUS_TIMEOUT)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_TIMEOUT_SINGLE_SIMULTANEOUS)->EnableWindow(FALSE);

		GetDlgItem(IDC_SPIN_SINGLE_SIMULTANEOUS_TIMEOUT)->EnableWindow(FALSE);
	}

	GetDlgItem(IDC_SINGLE_SIMULTANEOUS)->EnableWindow(b_single_simultaneous);

	GetDlgItem(IDC_RADIO_TRIGGER_SOFTWARE_START_SYNCHRONOUS)->EnableWindow(b_start_synchronous);

	GetDlgItem(IDC_RADIO_TRIGGER_DIGITAL_START_SYNCHRONOUS)->EnableWindow(b_start_synchronous);

	if( (b_start_synchronous)&&(m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger == AO_TRIGGER_TYPE_EXT_DIGITAL) )
	{
		GetDlgItem(IDC_EDIT_TIMEOUT_START_SYNCHRONOUS)->EnableWindow(TRUE);

		GetDlgItem(IDC_SPIN_START_SYNCHRONOUS_TIMEOUT)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_TIMEOUT_START_SYNCHRONOUS)->EnableWindow(FALSE);

		GetDlgItem(IDC_SPIN_START_SYNCHRONOUS_TIMEOUT)->EnableWindow(FALSE);
	}

	GetDlgItem(IDC_START_SYNCHRONOUS)->EnableWindow(b_start_synchronous);
}

void CAnalogOutputPP::SetControlStates(void)
{
	Cme4000App* p_app = (Cme4000App*)AfxGetApp();

	ME4000Board* p_boards = p_app->GetBoardArray();

	CString cs_text;
	
	cs_text.Format( "%04X", p_boards[m_iCurrentBoardIndex].m_usDeviceID );
	
	SetDlgItemText(IDC_BOARD_VERSION, cs_text);
	
	cs_text.Format( "%08X", p_boards[m_iCurrentBoardIndex].m_ulSerialNumber );
	
	SetDlgItemText(IDC_SERIAL_NUMBER, cs_text);

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		m_comboFunction[index_channel].SetCurSel(m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel].m_iFunction);

		OnSelchangeComboFunction(index_channel);
	}

	SetSimultaneousControls();
}

void _stdcall CAnalogOutputPP::WraparoundTerminate(void* pTerminateContext)
{
	SMEAOChannel* p_ao_channel = (SMEAOChannel*)pTerminateContext;

	int id_stop_last_value = p_ao_channel->m_pAnalogOutputPP->m_iButtonStartAppendOutputID[p_ao_channel->m_iIndexChannel];

	p_ao_channel->m_pAnalogOutputPP->SetDlgItemText(id_stop_last_value, "Start");
	
	if(p_ao_channel->m_iFunction == AO_FUNCTION_START)
	{
		p_ao_channel->m_pAnalogOutputPP->GetDlgItem(id_stop_last_value)->EnableWindow(TRUE);
	}
	else // if(p_ao_channel->m_iFunction == AO_FUNCTION_START_SYNCHRONOUS)
	{
		p_ao_channel->m_pAnalogOutputPP->GetDlgItem(id_stop_last_value)->EnableWindow(FALSE);
	}

	int id_stop_immediate = p_ao_channel->m_pAnalogOutputPP->m_iButtonStopID[p_ao_channel->m_iIndexChannel];

	p_ao_channel->m_pAnalogOutputPP->GetDlgItem(id_stop_immediate)->EnableWindow(FALSE);

	p_ao_channel->m_bAOActive = FALSE;
}

void _stdcall CAnalogOutputPP::ContinuousCallback(unsigned long ulBufferAvailable, void* pCallbackContext)
{
	SMEAOChannel* p_ao_channel = (SMEAOChannel*)pCallbackContext;

	if(p_ao_channel->m_bAppendBuffer)
	{
		unsigned long ul_values_appended;
		
		me4000AOAppendNewValues(	p_ao_channel->m_iIndexBoard,										// uiBoardNumber,
									p_ao_channel->m_iIndexChannel,										// uiChannelNumber,
									p_ao_channel->m_psDataBuffer + p_ao_channel->m_uiAppendOffset,		// psBuffer,
									p_ao_channel->m_ulSizeOfAppend,										// ulNumberOfValuesToAppend,
									ME4000_AO_APPEND_NEW_VALUES_BLOCKING,								// iExecutionMode,
									&ul_values_appended												);	// pulNumberOfValuesAppended
	}

	p_ao_channel->m_bAppendBuffer = FALSE;

	int id_append = p_ao_channel->m_pAnalogOutputPP->m_iButtonStartAppendOutputID[p_ao_channel->m_iIndexChannel];

//	p_ao_channel->m_pAnalogOutputPP->GetDlgItem(id_append)->PostMessage(WM_ENABLE, TRUE, 0);

	p_ao_channel->m_pAnalogOutputPP->GetDlgItem(id_append)->EnableWindow(TRUE);
}

int CAnalogOutputPP::PrepareChannel(SMEAOChannel* p_ao_channel)
{
	unsigned long ul_ticks_low_part;

	unsigned long ul_ticks_high_part;

	me4000FrequencyToTicks(	(double)p_ao_channel->m_uiOutputRate,		// dRequiredFreq,
							&ul_ticks_low_part,							// pulTicksLowPart,
							&ul_ticks_high_part,						// pulTicksHighPart,
							ME4000_POINTER_NOT_USED					);	// pdAchievedFreq - not required
	
	int i_trigger_mode;

	if(p_ao_channel->m_iTriggerType == AO_TRIGGER_TYPE_SOFTWARE)
	{
		i_trigger_mode = ME4000_AO_TRIGGER_SOFTWARE;
	}
	else // if(p_ao_channel->m_iTriggerType == AO_TRIGGER_TYPE_EXT_DIGITAL)
	{
		i_trigger_mode = ME4000_AO_TRIGGER_EXT_DIGITAL;
	}
	
	int i_ext_trigger_edge;

	if(p_ao_channel->m_iTriggerType != AO_TRIGGER_TYPE_EXT_DIGITAL)
	{
		i_ext_trigger_edge = ME4000_VALUE_NOT_USED;
	}
	else if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_RISING)
	{
		i_ext_trigger_edge = ME4000_AO_TRIGGER_EXT_EDGE_RISING;
	}
	else if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_FALLING)
	{
		i_ext_trigger_edge = ME4000_AO_TRIGGER_EXT_EDGE_FALLING;
	}
	else if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_BOTH)
	{
		i_ext_trigger_edge = ME4000_AO_TRIGGER_EXT_EDGE_BOTH;
	}

	int i_error = me4000AOConfig(	m_iCurrentBoardIndex,				// uiBoardNumber,
									p_ao_channel->m_iIndexChannel,		// uiChannelNumber,
									ul_ticks_low_part,					// ulTicks,
									i_trigger_mode,						// iTriggerMode,
									i_ext_trigger_edge				);	// iExtTriggerEdge

	if(i_error != ME4000_NO_ERROR)
	{
		return(i_error);
	}

	unsigned long ul_data_count = p_ao_channel->m_uiSignalLengthSeconds * p_ao_channel->m_uiOutputRate;
	
	if(p_ao_channel->m_ulDataBufferSizeValues < ul_data_count)
	{
		if(p_ao_channel->m_psDataBuffer != NULL)
		{
			delete p_ao_channel->m_psDataBuffer;
		}

		p_ao_channel->m_psDataBuffer = new short[ul_data_count];

		p_ao_channel->m_ulDataBufferSizeValues = ul_data_count;
	}
	
	WinSweepBuffer(	p_ao_channel->m_iOutputSignalForm,					// signal_type 
					(double)p_ao_channel->m_uiSweepFrequencyFrom,		// from_freq 
					(double)p_ao_channel->m_uiSweepFrequencyTo,			// to_freq 
					(double)p_ao_channel->m_uiSweepAmplitudeFrom,		// from_amp 
					(double)p_ao_channel->m_uiSweepAmplitudeTo,			// to_amp 
					(double)p_ao_channel->m_uiOutputRate,				// base_freq, 
					ul_data_count,										// no_of_points 
					p_ao_channel->m_psDataBuffer,						// buffer
					1												);	// buffer_increment);
	
	unsigned long ul_timeout_seconds = p_ao_channel->m_ulTimeout;

	if(p_ao_channel->m_iTriggerType != AO_TRIGGER_TYPE_EXT_DIGITAL)
	{
		ul_timeout_seconds = ME4000_VALUE_NOT_USED;
	}

	if(p_ao_channel->m_iBufferMode == AO_BUFFER_MODE_WRAPAROUND)
	{
		unsigned long ul_loops = p_ao_channel->m_uiFiniteLoops;

		if( p_ao_channel->m_bInfiniteLoops )
		{
			ul_loops = ME4000_AO_WRAPAROUND_INFINITE;
		}
		
		i_error = me4000AOWraparound(	m_iCurrentBoardIndex,					// uiBoardNumber,
										p_ao_channel->m_iIndexChannel,			// uiChannelNumber,
										p_ao_channel->m_psDataBuffer,			// psBuffer,
										ul_data_count,							// ulDataCount,
										ul_loops,								// ulLoops,
										ME4000_AO_WRAPAROUND_ASYNCHRONOUS,		// iExecutionMode,
										WraparoundTerminate,					// pTerminateProc,
										p_ao_channel,							// pTerminateContext,
										ul_timeout_seconds					);	// ulTimeOutSeconds	
		
		if(i_error != ME4000_NO_ERROR)
		{
			return(i_error);
		}
	}
	else
	{
		unsigned long ul_number_of_values_written;
		
		i_error = me4000AOContinuous(	m_iCurrentBoardIndex,				// uiBoardNumber,
										p_ao_channel->m_iIndexChannel,		// uiChannelNumber,
										p_ao_channel->m_psDataBuffer,		// psBuffer,
										ul_data_count,						// ulDataCount,
										ContinuousCallback,					// pCallbackProc,
										p_ao_channel,						// pTerminateContext,
										ul_timeout_seconds,					// ulTimeOutSeconds	
										&ul_number_of_values_written	);	// pulNumberOfValuesWritten	

		if(ul_number_of_values_written == ul_data_count)
		{
			p_ao_channel->m_bAppendBuffer = FALSE;
		}
		else
		{
			p_ao_channel->m_ulSizeOfAppend = ul_data_count - ul_number_of_values_written;
			
			p_ao_channel->m_uiAppendOffset = ul_number_of_values_written;

			p_ao_channel->m_bAppendBuffer = TRUE;
		}
		
		if(i_error != ME4000_NO_ERROR)
		{
			return(i_error);
		}
	}

	return(ME4000_NO_ERROR);
}

void CAnalogOutputPP::MarkChannelActive(SMEAOChannel* p_ao_channel)
{
	p_ao_channel->m_bAOActive = TRUE;

	if(p_ao_channel->m_iBufferMode == AO_BUFFER_MODE_WRAPAROUND)
	{
		p_ao_channel->m_iLastBufferMode = AO_BUFFER_MODE_WRAPAROUND;
		
		SetDlgItemText(m_iButtonStartAppendOutputID[p_ao_channel->m_iIndexChannel], "Stop last value");
		
		GetDlgItem(m_iButtonStartAppendOutputID[p_ao_channel->m_iIndexChannel])->EnableWindow(TRUE);

		SetDlgItemText(m_iButtonStopID[p_ao_channel->m_iIndexChannel], "Stop immediate");

		GetDlgItem(m_iButtonStopID[p_ao_channel->m_iIndexChannel])->EnableWindow(TRUE);
	}
	else
	{
		p_ao_channel->m_iLastBufferMode = AO_BUFFER_MODE_CONTINUOUS;
		
		SetDlgItemText(m_iButtonStartAppendOutputID[p_ao_channel->m_iIndexChannel], "Append");

		if(p_ao_channel->m_bAppendBuffer)
		{
			GetDlgItem(m_iButtonStartAppendOutputID[p_ao_channel->m_iIndexChannel])->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(m_iButtonStartAppendOutputID[p_ao_channel->m_iIndexChannel])->EnableWindow(TRUE);
		}
		
		SetDlgItemText(m_iButtonStopID[p_ao_channel->m_iIndexChannel], "Stop");

		GetDlgItem(m_iButtonStopID[p_ao_channel->m_iIndexChannel])->EnableWindow(TRUE);
	}
}


void CAnalogOutputPP::RedrawPlot(int index_channel)
{
	InvalidateRect( m_rectPlotChild[index_channel] );
}

void CAnalogOutputPP::OnSelchangeComboFunction1() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboFunction(0);
}

void CAnalogOutputPP::OnRadioAoWraparound1() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioAOWraparound(0);
}

void CAnalogOutputPP::OnRadioAoContinuous1() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioAOContinuous(0);
}

void CAnalogOutputPP::OnRadioTriggerSoftware1() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioTriggerSoftware(0);
}

void CAnalogOutputPP::OnRadioTriggerDigital1() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioTriggerDigital(0);
}

void CAnalogOutputPP::OnCheckEnableExtTrigger1() 
{
	// TODO: Add your control notification handler code here
	
	OnCheckEnableExtTrigger(0);
}

void CAnalogOutputPP::OnRadioLoopEndless1() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioLoopEndless(0);
}

void CAnalogOutputPP::OnRadioLoopFinite1() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioLoopFinite(0);
}

void CAnalogOutputPP::OnButtonStartAppendOutput1() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonStartAppendOutput(0);
}

void CAnalogOutputPP::OnButtonStop1() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonStop(0);
}

void CAnalogOutputPP::OnSelchangeComboFunction2() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboFunction(1);
}

void CAnalogOutputPP::OnRadioAoWraparound2() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioAOWraparound(1);
}

void CAnalogOutputPP::OnRadioAoContinuous2() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioAOContinuous(1);
}

void CAnalogOutputPP::OnRadioTriggerSoftware2() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioTriggerSoftware(1);
}

void CAnalogOutputPP::OnRadioTriggerDigital2() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioTriggerDigital(1);
}

void CAnalogOutputPP::OnCheckEnableExtTrigger2() 
{
	// TODO: Add your control notification handler code here
	
	OnCheckEnableExtTrigger(1);
}

void CAnalogOutputPP::OnRadioLoopEndless2() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioLoopEndless(1);
}

void CAnalogOutputPP::OnRadioLoopFinite2() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioLoopFinite(1);
}

void CAnalogOutputPP::OnButtonStartAppendOutput2() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonStartAppendOutput(1);
}

void CAnalogOutputPP::OnButtonStop2() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonStop(1);
}

void CAnalogOutputPP::OnSelchangeComboFunction3() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboFunction(2);
}

void CAnalogOutputPP::OnRadioAoWraparound3() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioAOWraparound(2);
}

void CAnalogOutputPP::OnRadioAoContinuous3() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioAOContinuous(2);
}

void CAnalogOutputPP::OnRadioTriggerSoftware3() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioTriggerSoftware(2);
}

void CAnalogOutputPP::OnRadioTriggerDigital3() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioTriggerDigital(2);
}

void CAnalogOutputPP::OnCheckEnableExtTrigger3() 
{
	// TODO: Add your control notification handler code here
	
	OnCheckEnableExtTrigger(2);
}

void CAnalogOutputPP::OnRadioLoopEndless3() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioLoopEndless(2);
}

void CAnalogOutputPP::OnRadioLoopFinite3() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioLoopFinite(2);
}

void CAnalogOutputPP::OnButtonStartAppendOutput3() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonStartAppendOutput(2);
}

void CAnalogOutputPP::OnButtonStop3() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonStop(2);
}

void CAnalogOutputPP::OnSelchangeComboFunction4() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboFunction(3);
}

void CAnalogOutputPP::OnRadioAoWraparound4() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioAOWraparound(3);
}

void CAnalogOutputPP::OnRadioAoContinuous4() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioAOContinuous(3);
}

void CAnalogOutputPP::OnRadioTriggerSoftware4() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioTriggerSoftware(3);
}

void CAnalogOutputPP::OnRadioTriggerDigital4() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioTriggerDigital(3);
}

void CAnalogOutputPP::OnCheckEnableExtTrigger4() 
{
	// TODO: Add your control notification handler code here
	
	OnCheckEnableExtTrigger(3);
}

void CAnalogOutputPP::OnRadioLoopEndless4() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioLoopEndless(3);
}

void CAnalogOutputPP::OnRadioLoopFinite4() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioLoopFinite(3);
}

void CAnalogOutputPP::OnButtonStartAppendOutput4() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonStartAppendOutput(3);
}

void CAnalogOutputPP::OnButtonStop4() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonStop(3);
}

void CAnalogOutputPP::OnChangeEditOutputSingle1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	OnChangeEditOutputSingle(0);
}

void CAnalogOutputPP::OnSelchangeComboSignalForm1() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboSignalForm(0);
}

void CAnalogOutputPP::OnKillfocusEditOutputRate1() 
{
	// TODO: Add your control notification handler code here

	OnKillfocusEditOutputRate(0);
}

void CAnalogOutputPP::OnKillfocusEditSignalLength1() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditSignalLength(0);
}

void CAnalogOutputPP::OnKillfocusEditFrequencyFrom1() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyFrom(0);
}

void CAnalogOutputPP::OnKillfocusEditFrequencyTo1() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyTo(0);
}

void CAnalogOutputPP::OnKillfocusEditAmplitudeFrom1() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeFrom(0);
}

void CAnalogOutputPP::OnKillfocusEditAmplitudeTo1() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeTo(0);
}

void CAnalogOutputPP::OnChangeEditOutputSingle2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	OnChangeEditOutputSingle(1);
}

void CAnalogOutputPP::OnSelchangeComboSignalForm2() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboSignalForm(1);
}

void CAnalogOutputPP::OnKillfocusEditOutputRate2() 
{
	// TODO: Add your control notification handler code here

	OnKillfocusEditOutputRate(1);
}

void CAnalogOutputPP::OnKillfocusEditSignalLength2() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditSignalLength(1);
}

void CAnalogOutputPP::OnKillfocusEditFrequencyFrom2() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyFrom(1);
}

void CAnalogOutputPP::OnKillfocusEditFrequencyTo2() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyTo(1);
}

void CAnalogOutputPP::OnKillfocusEditAmplitudeFrom2() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeFrom(1);
}

void CAnalogOutputPP::OnKillfocusEditAmplitudeTo2() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeTo(1);
}

void CAnalogOutputPP::OnChangeEditOutputSingle3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	OnChangeEditOutputSingle(2);
}

void CAnalogOutputPP::OnSelchangeComboSignalForm3() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboSignalForm(2);
}

void CAnalogOutputPP::OnKillfocusEditOutputRate3() 
{
	// TODO: Add your control notification handler code here

	OnKillfocusEditOutputRate(2);
}

void CAnalogOutputPP::OnKillfocusEditSignalLength3() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditSignalLength(2);
}

void CAnalogOutputPP::OnKillfocusEditFrequencyFrom3() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyFrom(2);
}

void CAnalogOutputPP::OnKillfocusEditFrequencyTo3() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyTo(2);
}

void CAnalogOutputPP::OnKillfocusEditAmplitudeFrom3() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeFrom(2);
}

void CAnalogOutputPP::OnKillfocusEditAmplitudeTo3() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeTo(2);
}

void CAnalogOutputPP::OnChangeEditOutputSingle4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	OnChangeEditOutputSingle(3);
}

void CAnalogOutputPP::OnSelchangeComboSignalForm4() 
{
	// TODO: Add your control notification handler code here
	
	OnSelchangeComboSignalForm(3);
}

void CAnalogOutputPP::OnKillfocusEditOutputRate4() 
{
	// TODO: Add your control notification handler code here

	OnKillfocusEditOutputRate(3);
}

void CAnalogOutputPP::OnKillfocusEditSignalLength4() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditSignalLength(3);
}

void CAnalogOutputPP::OnKillfocusEditFrequencyFrom4() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyFrom(3);
}

void CAnalogOutputPP::OnKillfocusEditFrequencyTo4() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditFrequencyTo(3);
}

void CAnalogOutputPP::OnKillfocusEditAmplitudeFrom4() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeFrom(3);
}

void CAnalogOutputPP::OnKillfocusEditAmplitudeTo4() 
{
	// TODO: Add your control notification handler code here
	
	OnKillfocusEditAmplitudeTo(3);
}


void CAnalogOutputPP::OnDeltaposSpinOutputRate1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinOutputRate(0, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinSignalLength1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinSignalLength(0, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinFrequencyFrom1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinFrequencyFrom(0, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinFrequencyTo1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinFrequencyTo(0, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinAmplitudeFrom1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinAmplitudeFrom(0, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinAmplitudeTo1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinAmplitudeTo(0, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinOutputRate2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinOutputRate(1, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinSignalLength2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinSignalLength(1, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinFrequencyFrom2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinFrequencyFrom(1, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinFrequencyTo2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinFrequencyTo(1, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinAmplitudeFrom2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinAmplitudeFrom(1, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinAmplitudeTo2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinAmplitudeTo(1, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinOutputRate3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinOutputRate(2, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinSignalLength3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinSignalLength(2, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinFrequencyFrom3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinFrequencyFrom(2, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinFrequencyTo3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinFrequencyTo(2, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinAmplitudeFrom3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinAmplitudeFrom(2, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinAmplitudeTo3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinAmplitudeTo(2, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinOutputRate4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinOutputRate(3, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinSignalLength4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	OnDeltaposSpinSignalLength(3, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinFrequencyFrom4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinFrequencyFrom(3, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinFrequencyTo4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinFrequencyTo(3, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinAmplitudeFrom4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinAmplitudeFrom(3, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnDeltaposSpinAmplitudeTo4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	OnDeltaposSpinAmplitudeTo(3, pNMUpDown);
	
	*pResult = 0;
}

void CAnalogOutputPP::OnRadioSingleSimultaneousSoftware()
{
	m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger = AO_TRIGGER_TYPE_SOFTWARE;

	GetDlgItem(IDC_EDIT_TIMEOUT_SINGLE_SIMULTANEOUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_SINGLE_SIMULTANEOUS_TIMEOUT)->EnableWindow(FALSE);

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

		if(p_ao_channel->m_iFunction == AO_FUNCTION_SINGLE_SIMULTANEOUS)
		{
			GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(FALSE);
			GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(FALSE);
			GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(FALSE);
		}
	}
}

void CAnalogOutputPP::OnRadioSingleSimultaneousDigitalExt()
{
	m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger = AO_TRIGGER_TYPE_EXT_DIGITAL;

	GetDlgItem(IDC_EDIT_TIMEOUT_SINGLE_SIMULTANEOUS)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_SINGLE_SIMULTANEOUS_TIMEOUT)->EnableWindow(TRUE);

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

		if(p_ao_channel->m_iFunction == AO_FUNCTION_SINGLE_SIMULTANEOUS)
		{
			GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->EnableWindow(TRUE);

			if(p_ao_channel->m_bExtTriggerEnable)
			{
				GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(TRUE);
				GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(TRUE);
				GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(TRUE);
			}
			else // if(!p_ao_channel->m_bExtTriggerEnable)
			{
				GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(FALSE);
			}
		}
	}
}

void CAnalogOutputPP::OnRadioStartSynchronousSoftware()
{
	m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger = AO_TRIGGER_TYPE_SOFTWARE;

	GetDlgItem(IDC_EDIT_TIMEOUT_START_SYNCHRONOUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN_START_SYNCHRONOUS_TIMEOUT)->EnableWindow(FALSE);

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

		if(p_ao_channel->m_iFunction == AO_FUNCTION_START_SYNCHRONOUS)
		{
			GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->EnableWindow(FALSE);

			GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(FALSE);
			GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(FALSE);
			GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(FALSE);
		}
	}
}

void CAnalogOutputPP::OnRadioStartSynchronousDigitalExt()
{
	m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger = AO_TRIGGER_TYPE_EXT_DIGITAL;

	GetDlgItem(IDC_EDIT_TIMEOUT_START_SYNCHRONOUS)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_START_SYNCHRONOUS_TIMEOUT)->EnableWindow(TRUE);

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

		if(p_ao_channel->m_iFunction == AO_FUNCTION_START_SYNCHRONOUS)
		{
			GetDlgItem(m_iCheckEnableExtTriggerID[index_channel])->EnableWindow(TRUE);

			if(p_ao_channel->m_bExtTriggerEnable)
			{
				GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(TRUE);
				GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(TRUE);
				GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(TRUE);
			}
			else // if(!p_ao_channel->m_bExtTriggerEnable)
			{
				GetDlgItem(m_iRadioTriggerRisingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerFallingID[index_channel])->EnableWindow(FALSE);
				GetDlgItem(m_iRadioTriggerBothID[index_channel])->EnableWindow(FALSE);
			}
		}
	}
}

void CAnalogOutputPP::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];
		
		if( (p_ao_channel->m_iLastBufferMode == AO_BUFFER_MODE_CONTINUOUS)&&(p_ao_channel->m_bAOActive) )
		{
			int i_status;
			
			me4000AOGetStatus(	m_iCurrentBoardIndex,	// uiBoardNumber,
								index_channel,			// uiChannelNumber,
								ME4000_AO_WAIT_NONE,	// iWaitIdle,
								&i_status			);	// piStatus

			if(i_status == ME4000_AO_STATUS_IDLE)
			{
				p_ao_channel->m_bAOActive = FALSE;

				SetDlgItemText(m_iButtonStartAppendOutputID[index_channel], "Start");

				if(p_ao_channel->m_iFunction == AO_FUNCTION_START)
				{
					GetDlgItem(m_iButtonStartAppendOutputID[index_channel])->EnableWindow(TRUE);
				}
				else // if(p_ao_channel->m_iFunction == AO_FUNCTION_START_SYNCHRONOUS)
				{
					GetDlgItem(m_iButtonStartAppendOutputID[index_channel])->EnableWindow(FALSE);
				}

				GetDlgItem(m_iButtonStopID[index_channel])->EnableWindow(FALSE);
			}
		}
	}
	
	CPropertyPage::OnTimer(nIDEvent);
}

void CAnalogOutputPP::OnSingleSimultaneous() 
{
	// TODO: Add your control notification handler code here

	CDataExchange dx(this, TRUE);
	
	DoDataExchange(&dx);

	unsigned int ui_channel_number[4];

	unsigned long ul_count = 0;
	
	int i_trigger_mode;

	if(m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger == AO_TRIGGER_TYPE_SOFTWARE)
	{
		i_trigger_mode = ME4000_AO_TRIGGER_SOFTWARE;
	}
	else // if(m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger == AO_TRIGGER_TYPE_EXT_DIGITAL)
	{
		i_trigger_mode = ME4000_AO_TRIGGER_EXT_DIGITAL;
	}

	int i_ext_trigger_enable[4];
	int i_ext_trigger_edge[4];
							
	int* p_ext_trigger_enable;
	int* p_ext_trigger_edge;

	if(m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger == AO_TRIGGER_TYPE_SOFTWARE)
	{
		p_ext_trigger_enable = ME4000_POINTER_NOT_USED;

		p_ext_trigger_edge = ME4000_POINTER_NOT_USED;
	}
	else
	{
		p_ext_trigger_enable = &i_ext_trigger_enable[0];

		p_ext_trigger_edge = &i_ext_trigger_edge[0];
	}

	unsigned long ul_time_out_seconds;

	if(m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger == AO_TRIGGER_TYPE_SOFTWARE)
	{
		ul_time_out_seconds = ME4000_VALUE_NOT_USED;
	}
	else // if(m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger == AO_TRIGGER_TYPE_EXT_DIGITAL)
	{
		ul_time_out_seconds = m_sBoardAO[m_iCurrentBoardIndex].m_ulSingleSimultaneousTimeout;
	}

	short s_value[4];
	
	for(unsigned int index_channel = 0; index_channel < 4; index_channel++)
	{
		SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

		int i_error;
		
		if(p_ao_channel->m_iFunction == AO_FUNCTION_SINGLE_SIMULTANEOUS)
		{
			ui_channel_number[ul_count] = index_channel;
			
			if(m_sBoardAO[m_iCurrentBoardIndex].m_iSingleSimultaneousTrigger == AO_TRIGGER_TYPE_EXT_DIGITAL)
			{
				if(p_ao_channel->m_bExtTriggerEnable)
				{
					i_ext_trigger_enable[ul_count] = ME4000_AO_TRIGGER_EXT_ENABLE;

					if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_RISING)
					{
						i_ext_trigger_edge[ul_count] = ME4000_AO_TRIGGER_EXT_EDGE_RISING;
					}
					else if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_FALLING)
					{
						i_ext_trigger_edge[ul_count] = ME4000_AO_TRIGGER_EXT_EDGE_FALLING;
					}
					else // if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_BOTH)
					{
						i_ext_trigger_edge[ul_count] = ME4000_AO_TRIGGER_EXT_EDGE_BOTH;
					}
				}
				else // if(!p_ao_channel->m_bExtTriggerEnable)
				{
					i_ext_trigger_enable[ul_count] = ME4000_AO_TRIGGER_EXT_DISABLE;

					i_ext_trigger_edge[ul_count] = ME4000_VALUE_NOT_USED;
				}
			}

			i_error = me4000AOVoltToDigit(	p_ao_channel->m_dSingleValue,		// dVolt,
											&s_value[ul_count]				);	// psDigit

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}

			++ul_count;
		}
	}

	me4000AOSingleSimultaneous(	m_iCurrentBoardIndex,		// uiBoardNumber
								&ui_channel_number[0],		// puiChannelNumber
								ul_count,					// ulCount
								i_trigger_mode,				// iTriggerMode
								p_ext_trigger_enable,		// piExtTriggerEnable
								p_ext_trigger_edge,			// piExtTriggerEdge
								ul_time_out_seconds,		// ulTimeOutSeconds
								&s_value[0]				);	// psValue	
}

void CAnalogOutputPP::OnStartSynchronous() 
{
	// TODO: Add your control notification handler code here
	
	CDataExchange dx(this, TRUE);
	
	DoDataExchange(&dx);

	unsigned int ui_channel_number[4];

	unsigned long ul_count = 0;
	
	int i_trigger_mode;

	if(m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger == AO_TRIGGER_TYPE_SOFTWARE)
	{
		i_trigger_mode = ME4000_AO_TRIGGER_SOFTWARE;
	}
	else // if(m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger == AO_TRIGGER_TYPE_EXT_DIGITAL)
	{
		i_trigger_mode = ME4000_AO_TRIGGER_EXT_DIGITAL;
	}

	int i_ext_trigger_enable[4];
	int i_ext_trigger_edge[4];
							
	int* p_ext_trigger_enable;
	int* p_ext_trigger_edge;

	if(m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger == AO_TRIGGER_TYPE_SOFTWARE)
	{
		p_ext_trigger_enable = ME4000_POINTER_NOT_USED;

		p_ext_trigger_edge = ME4000_POINTER_NOT_USED;
	}
	else
	{
		p_ext_trigger_enable = &i_ext_trigger_enable[0];

		p_ext_trigger_edge = &i_ext_trigger_edge[0];
	}

	unsigned long ul_time_out_seconds;

	if(m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger == AO_TRIGGER_TYPE_SOFTWARE)
	{
		ul_time_out_seconds = ME4000_VALUE_NOT_USED;
	}
	else // if(m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger == AO_TRIGGER_TYPE_EXT_DIGITAL)
	{
		ul_time_out_seconds = m_sBoardAO[m_iCurrentBoardIndex].m_ulStartSynchronousTimeout;
	}

	for(unsigned int index_channel = 0; index_channel < 4; index_channel++)
	{
		SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

		int i_error;
		
		if(p_ao_channel->m_iFunction == AO_FUNCTION_START_SYNCHRONOUS)
		{
			i_error = PrepareChannel(p_ao_channel);

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}

			ui_channel_number[ul_count] = index_channel;
			
			if(m_sBoardAO[m_iCurrentBoardIndex].m_iStartSynchronousTrigger == AO_TRIGGER_TYPE_EXT_DIGITAL)
			{
				if(p_ao_channel->m_bExtTriggerEnable)
				{
					i_ext_trigger_enable[ul_count] = ME4000_AO_TRIGGER_EXT_ENABLE;

					if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_RISING)
					{
						i_ext_trigger_edge[ul_count] = ME4000_AO_TRIGGER_EXT_EDGE_RISING;
					}
					else if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_FALLING)
					{
						i_ext_trigger_edge[ul_count] = ME4000_AO_TRIGGER_EXT_EDGE_FALLING;
					}
					else // if(p_ao_channel->m_iTriggerExtEdge == AO_TRIGGER_EXT_EDGE_BOTH)
					{
						i_ext_trigger_edge[ul_count] = ME4000_AO_TRIGGER_EXT_EDGE_BOTH;
					}
				}
				else // if(!p_ao_channel->m_bExtTriggerEnable)
				{
					i_ext_trigger_enable[ul_count] = ME4000_AO_TRIGGER_EXT_DISABLE;

					i_ext_trigger_edge[ul_count] = ME4000_VALUE_NOT_USED;
				}
			}

			++ul_count;
		}
	}

	int i_error = me4000AOStartSynchronous(	m_iCurrentBoardIndex,		// uiBoardNumber
											&ui_channel_number[0],		// puiChannelNumber
											ul_count,					// ulCount
											i_trigger_mode,				// iTriggerMode
											p_ext_trigger_enable,		// piExtTriggerEnable
											p_ext_trigger_edge,			// piExtTriggerEdge
											ul_time_out_seconds		);	// psValue
	
	if(i_error == ME4000_NO_ERROR)
	{
		for(index_channel = 0; index_channel < 4; index_channel++)
		{
			SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

			if(p_ao_channel->m_iFunction == AO_FUNCTION_START_SYNCHRONOUS)
			{
				MarkChannelActive(p_ao_channel);
			}
		}
	}
}

void CAnalogOutputPP::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		CRect rect_intersect;
		
		if( !::IntersectRect(rect_intersect, &m_rectPlotChild[index_channel], &dc.m_ps.rcPaint ) )
		{
			continue;
		}

		CClientDC dc_plot(m_pPlotWin[index_channel]);

		dc_plot.FillSolidRect( m_rectPlotClient[index_channel], RGB(0, 0, 0) );
		
		SMEAOChannel* p_ao_channel = &m_sBoardAO[m_iCurrentBoardIndex].m_sAOChannel[index_channel];

		if( (p_ao_channel->m_iFunction == AO_FUNCTION_SINGLE)||
						(p_ao_channel->m_iFunction == AO_FUNCTION_SINGLE_SIMULTANEOUS) )
		{
			dc_plot.SetTextColor(DISPLAY_COLOR);

			dc_plot.SetBkMode(TRANSPARENT);

			CFont font_text;

			font_text.CreateFontIndirect(&lf_text);

			CFont* p_old_font = dc_plot.SelectObject(&font_text);
    
			CString cs_text;
			
			cs_text.Format("%7.3f V", p_ao_channel->m_dSingleValue);
			
			dc_plot.DrawText(cs_text, m_rectPlotClient[index_channel], DT_SINGLELINE | DT_CENTER | DT_VCENTER); 
		
			dc_plot.SelectObject(p_old_font);
		}
		else
		{
			unsigned long ul_data_count = p_ao_channel->m_uiSignalLengthSeconds * p_ao_channel->m_uiOutputRate;
	
			double d_x_factor = (double)m_rectPlotClient[index_channel].Width() / (double)ul_data_count;
			
			double d_x_const = (double)m_rectPlotClient[index_channel].left;

			double d_y_factor = ( (double)m_rectPlotClient[index_channel].Height() - 4.0 ) / -20.0;

			double d_y_const = ( (double)m_rectPlotClient[index_channel].top + 2.0 ) - 10.0 * d_y_factor;
			
			CPen disp_pen(PS_SOLID, 1, DISPLAY_COLOR);

			CPen* p_old_pen = (CPen*)dc_plot.SelectObject(&disp_pen);
			
			WinSweepDisplay(p_ao_channel->m_iOutputSignalForm,					// signal_type 
							(double)p_ao_channel->m_uiSweepFrequencyFrom,		// from_freq 
							(double)p_ao_channel->m_uiSweepFrequencyTo,			// to_freq 
							(double)p_ao_channel->m_uiSweepAmplitudeFrom,		// from_amp 
							(double)p_ao_channel->m_uiSweepAmplitudeTo,			// to_amp 
							(double)p_ao_channel->m_uiOutputRate,				// base_freq, 
							ul_data_count,										// no_of_points 
							&dc_plot,											// p_dc
							m_rectPlotClient[index_channel],					// rect_disp, 
							d_x_const,											// d_x_const, 
							d_x_factor,											// d_x-factor 
							d_y_const,											// d_y_const 
							d_y_factor										);	// d_y_factor

			dc_plot.SelectObject(p_old_pen);
		}
	}
	
	// Do not call CPropertyPage::OnPaint() for painting messages
}

