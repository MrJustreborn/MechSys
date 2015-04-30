// DIOBitPatternPP.cpp : implementation file
//

#include "stdafx.h"

#include <stdio.h>

#include "me4000.h"
#include "DIOBitPatternPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIOBitPatternPP property page

IMPLEMENT_DYNCREATE(CDIOBitPatternPP, CPropertyPage)

CDIOBitPatternPP::CDIOBitPatternPP() : CPropertyPage(CDIOBitPatternPP::IDD)
{
	//{{AFX_DATA_INIT(CDIOBitPatternPP)
	//}}AFX_DATA_INIT

	m_psGlobalDataBuffer = new short[0x10000];

	m_ulNumberOfGlobalData = 0x10000;

	for(int index = 0; index < 0x10000; index++)
	{
		*( (unsigned short*)&m_psGlobalDataBuffer[index] ) = (unsigned short)index;
	}

	Cme4000App* p_app = (Cme4000App*)AfxGetApp();

	ME4000Board* p_boards = p_app->GetBoardArray();

	for(int index_board = 0; index_board < ME4000_MAX_DEVICES; index_board++)
	{
		m_sBoardDIOBP[index_board].m_iIndexBoard = index_board;
	
		m_sBoardDIOBP[index_board].m_pDIOBitPatternPP = this;
	
		m_sBoardDIOBP[index_board].m_bOptoIsolated = p_boards[index_board].m_bOptoIsolated;
		
		m_sBoardDIOBP[index_board].m_bUsePort[ME4000_DIOBP_PORT_A] = TRUE;
		
		m_sBoardDIOBP[index_board].m_iPortOutputMode[ME4000_DIOBP_PORT_A] = ME4000_DIOBP_OUTPUT_MODE_BYTE_LOW;

		if(m_sBoardDIOBP[index_board].m_bOptoIsolated)
		{
			m_sBoardDIOBP[index_board].m_bUsePort[ME4000_DIOBP_PORT_B] = FALSE;

			m_sBoardDIOBP[index_board].m_bUsePort[ME4000_DIOBP_PORT_C] = TRUE;
		}
		else
		{
			m_sBoardDIOBP[index_board].m_bUsePort[ME4000_DIOBP_PORT_B] = TRUE;

			m_sBoardDIOBP[index_board].m_bUsePort[ME4000_DIOBP_PORT_C] = FALSE;
		}
			
		m_sBoardDIOBP[index_board].m_iPortOutputMode[ME4000_DIOBP_PORT_B] = ME4000_DIOBP_OUTPUT_MODE_BYTE_HIGH;
	
		m_sBoardDIOBP[index_board].m_iPortOutputMode[ME4000_DIOBP_PORT_C] = ME4000_DIOBP_OUTPUT_MODE_BYTE_HIGH;
	
		m_sBoardDIOBP[index_board].m_bUsePort[ME4000_DIOBP_PORT_D] = FALSE;
		
		m_sBoardDIOBP[index_board].m_iPortOutputMode[ME4000_DIOBP_PORT_D] = ME4000_DIOBP_OUTPUT_MODE_BYTE_LOW;

		m_sBoardDIOBP[index_board].m_iFunction	= DIOBP_WRAPAROUND;
	
		m_sBoardDIOBP[index_board].m_iTriggerMode = ME4000_DIOBP_TRIGGER_SOFTWARE;
		m_sBoardDIOBP[index_board].m_iTriggerExtEdge = ME4000_DIOBP_TRIGGER_EXT_EDGE_RISING;
	
		m_sBoardDIOBP[index_board].m_uiOutputRate = 1000;

		m_sBoardDIOBP[index_board].m_bInfiniteLoops = FALSE;

		m_sBoardDIOBP[index_board].m_uiFiniteLoops = 1;

		m_sBoardDIOBP[index_board].m_ulTimeout = 5;

		m_sBoardDIOBP[index_board].m_iLastOperation = DIOBP_NONE;

		m_sBoardDIOBP[index_board].m_bDIOBPActive = FALSE;

		m_sBoardDIOBP[index_board].m_iLastError = ME4000_NO_ERROR;

		m_sBoardDIOBP[index_board].m_psDataBuffer = m_psGlobalDataBuffer;

		m_sBoardDIOBP[index_board].m_ulNumberOfData = m_ulNumberOfGlobalData;

		m_sBoardDIOBP[index_board].m_ulDataBufferSizeValues = 0;

		m_sBoardDIOBP[index_board].m_bAppendBuffer = FALSE;

		m_sBoardDIOBP[index_board].m_uiAppendOffset = 0;

		m_sBoardDIOBP[index_board].m_ulSizeOfAppend = 0;
	}

	m_iCheckPortID[ME4000_DIOBP_PORT_A] = IDC_CHECK_PORT_A;
	m_iCheckPortID[ME4000_DIOBP_PORT_B] = IDC_CHECK_PORT_B;
	m_iCheckPortID[ME4000_DIOBP_PORT_C] = IDC_CHECK_PORT_C;
	m_iCheckPortID[ME4000_DIOBP_PORT_D] = IDC_CHECK_PORT_D;

	m_iRadioLowByteID[ME4000_DIOBP_PORT_A] = IDC_RADIO_LOW_BYTE_A;
	m_iRadioLowByteID[ME4000_DIOBP_PORT_B] = IDC_RADIO_LOW_BYTE_B;
	m_iRadioLowByteID[ME4000_DIOBP_PORT_C] = IDC_RADIO_LOW_BYTE_C;
	m_iRadioLowByteID[ME4000_DIOBP_PORT_D] = IDC_RADIO_LOW_BYTE_D;

	m_iRadioHighByteID[ME4000_DIOBP_PORT_A] = IDC_RADIO_HIGH_BYTE_A;
	m_iRadioHighByteID[ME4000_DIOBP_PORT_B] = IDC_RADIO_HIGH_BYTE_B;
	m_iRadioHighByteID[ME4000_DIOBP_PORT_C] = IDC_RADIO_HIGH_BYTE_C;
	m_iRadioHighByteID[ME4000_DIOBP_PORT_D] = IDC_RADIO_HIGH_BYTE_D;

	m_iCurrentBoardIndex = 0;

	m_pPropertySheet = NULL;
}

CDIOBitPatternPP::~CDIOBitPatternPP()
{
	delete m_psGlobalDataBuffer;
}

void CDIOBitPatternPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDIOBitPatternPP)
	DDX_Control(pDX, IDC_SPIN_TIMEOUT, m_spinTimeout);
	DDX_Control(pDX, IDC_SPIN_OUTPUT_RATE, m_spinOutputRate);
	DDX_Control(pDX, IDC_SPIN_LOOP_FINITE, m_spinLoopFinite);
	DDX_Control(pDX, IDC_LIST_DATA, m_listData);
	DDX_Control(pDX, IDC_COMBO_BOARD, m_comboBoardNumber);
	//}}AFX_DATA_MAP

	int i_trigger_type;
	
	int i_trigger_ext_edge;
	
	int i_loop_endless;

	int i_port_output_mode[4];
	
	if( !pDX->m_bSaveAndValidate )
	{
		switch(m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerMode)
		{
		case ME4000_DIOBP_TRIGGER_SOFTWARE:
			
			i_trigger_type = 0;

			break;

		case ME4000_DIOBP_TRIGGER_EXT_DIGITAL:
			
			i_trigger_type = 1;

			break;
		}

		switch(m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerExtEdge)
		{
		case ME4000_DIOBP_TRIGGER_EXT_EDGE_RISING:

			i_trigger_ext_edge = 0;

			break;

		case ME4000_DIOBP_TRIGGER_EXT_EDGE_FALLING:

			i_trigger_ext_edge = 1;

			break;

		case ME4000_DIOBP_TRIGGER_EXT_EDGE_BOTH:

			i_trigger_ext_edge = 2;

			break;
		}

		i_loop_endless = (m_sBoardDIOBP[m_iCurrentBoardIndex].m_bInfiniteLoops ? 0 : 1); 

		for(int index_port = 0; index_port < 4; index_port++)
		{
			i_port_output_mode[index_port] = 0;
			
			if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_iPortOutputMode[index_port] == ME4000_DIOBP_OUTPUT_MODE_BYTE_HIGH)
			{
				i_port_output_mode[index_port] = 1;
			}
		}
	}

	DDX_Radio(pDX, IDC_RADIO_DIOBP_WRAPAROUND, m_sBoardDIOBP[m_iCurrentBoardIndex].m_iFunction);

	DDX_Radio(pDX, IDC_RADIO_TRIGGER_SOFTWARE, i_trigger_type);

	DDX_Radio(pDX, IDC_RADIO_TRIGGER_RISING, i_trigger_ext_edge);

	DDX_Text(pDX, IDC_EDIT_OUTPUT_RATE, m_sBoardDIOBP[m_iCurrentBoardIndex].m_uiOutputRate);

	DDX_Radio(pDX, IDC_RADIO_LOOP_ENDLESS, i_loop_endless);

	DDX_Text(pDX, IDC_EDIT_LOOP_FINITE, m_sBoardDIOBP[m_iCurrentBoardIndex].m_uiFiniteLoops);

	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_sBoardDIOBP[m_iCurrentBoardIndex].m_ulTimeout);

	for(int index_port = 0; index_port < 4; index_port++)
	{
		DDX_Check(pDX, m_iCheckPortID[index_port], m_sBoardDIOBP[m_iCurrentBoardIndex].m_bUsePort[index_port]);
	
		DDX_Radio(pDX, m_iRadioLowByteID[index_port], i_port_output_mode[index_port]);
	}

	if(pDX->m_bSaveAndValidate)
	{
		switch(i_trigger_type)
		{
		case 0:
			
			m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerMode = ME4000_DIOBP_TRIGGER_SOFTWARE;

			break;

		case 1:
			
			m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerMode = ME4000_DIOBP_TRIGGER_EXT_DIGITAL;

			break;
		}

		switch(i_trigger_ext_edge)
		{
		case 0:

			m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerExtEdge = ME4000_DIOBP_TRIGGER_EXT_EDGE_RISING;

			break;

		case 1:

			m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerExtEdge = ME4000_DIOBP_TRIGGER_EXT_EDGE_FALLING;

			break;

		case 2:

			m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerExtEdge = ME4000_DIOBP_TRIGGER_EXT_EDGE_BOTH;

			break;
		}
	
		m_sBoardDIOBP[m_iCurrentBoardIndex].m_bInfiniteLoops = ( (i_loop_endless == 0) ? TRUE : FALSE);

		for(int index_port = 0; index_port < 4; index_port++)
		{
			m_sBoardDIOBP[m_iCurrentBoardIndex].m_iPortOutputMode[index_port] = ME4000_DIOBP_OUTPUT_MODE_BYTE_LOW;
			
			if(i_port_output_mode[index_port] == 1)
			{
				m_sBoardDIOBP[m_iCurrentBoardIndex].m_iPortOutputMode[index_port] = ME4000_DIOBP_OUTPUT_MODE_BYTE_HIGH;
			}
		}
	}
}

void CDIOBitPatternPP::OnCheckPort(int index_port)
{
	BOOL b_enable = IsDlgButtonChecked(m_iCheckPortID[index_port]);

	GetDlgItem(m_iRadioLowByteID[index_port])->EnableWindow(b_enable);

	GetDlgItem(m_iRadioHighByteID[index_port])->EnableWindow(b_enable);
}
	
void CDIOBitPatternPP::SetControlStates(void)
{
	Cme4000App* p_app = (Cme4000App*)AfxGetApp();

	ME4000Board* p_boards = p_app->GetBoardArray();

	CString cs_text;
	
	cs_text.Format( "%04X", p_boards[m_iCurrentBoardIndex].m_usDeviceID );
	
	SetDlgItemText(IDC_BOARD_VERSION, cs_text);
	
	cs_text.Format( "%08X", p_boards[m_iCurrentBoardIndex].m_ulSerialNumber );
	
	SetDlgItemText(IDC_SERIAL_NUMBER, cs_text);

	if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_iFunction == DIOBP_WRAPAROUND)
	{
		OnRadioDiobpWraparound();
	}
	else
	{
		OnRadioDiobpContinuous();
	}

	if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerMode == ME4000_DIOBP_TRIGGER_SOFTWARE)
	{
		OnRadioTriggerSoftware();
	}
	else
	{
		OnRadioTriggerDigital();
	}

	for(int index_port = 0; index_port < 4; index_port++)
	{
		OnCheckPort(index_port);
	}
}


BEGIN_MESSAGE_MAP(CDIOBitPatternPP, CPropertyPage)
	//{{AFX_MSG_MAP(CDIOBitPatternPP)
	ON_BN_CLICKED(ID_EXIT, OnExit)
	ON_BN_CLICKED(IDC_CHECK_PORT_A, OnCheckPortA)
	ON_BN_CLICKED(IDC_CHECK_PORT_B, OnCheckPortB)
	ON_BN_CLICKED(IDC_CHECK_PORT_C, OnCheckPortC)
	ON_BN_CLICKED(IDC_CHECK_PORT_D, OnCheckPortD)
	ON_BN_CLICKED(IDC_RADIO_DIOBP_WRAPAROUND, OnRadioDiobpWraparound)
	ON_BN_CLICKED(IDC_RADIO_DIOBP_CONTINUOUS, OnRadioDiobpContinuous)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_SOFTWARE, OnRadioTriggerSoftware)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_DIGITAL, OnRadioTriggerDigital)
	ON_BN_CLICKED(IDC_RADIO_LOOP_ENDLESS, OnRadioLoopEndless)
	ON_BN_CLICKED(IDC_RADIO_LOOP_FINITE, OnRadioLoopFinite)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDIOBitPatternPP::OnInitDialog() 
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

	m_spinOutputRate.SetRange32(1, 500000);
	
	m_spinLoopFinite.SetRange32(1, 100000);

	m_spinTimeout.SetRange32(0, 300);

	LVCOLUMN lv_column;

	memset(&lv_column, 0, sizeof(lv_column) );

	int index_display_column = 0;	

	lv_column.mask = LVCF_TEXT;
		
	lv_column.pszText = "High Byte";
		
	m_listData.InsertColumn(0, &lv_column);

	lv_column.pszText = "Low Byte";
		
	m_listData.InsertColumn(1, &lv_column);

	CRect rect_list;

	m_listData.GetClientRect(rect_list);
	
	m_listData.SetColumnWidth(0, rect_list.Width() / 2);

	m_listData.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	m_listData.SetItemCount(m_sBoardDIOBP[m_iCurrentBoardIndex].m_ulNumberOfData);

	SetDlgItemInt(IDC_NUMBER_OF_DATA, m_sBoardDIOBP[m_iCurrentBoardIndex].m_ulNumberOfData);

	if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_bOptoIsolated)
	{
		GetDlgItem( m_iCheckPortID[ME4000_DIOBP_PORT_B] )->EnableWindow(FALSE);
	}

	SetControlStates();

	SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDIOBitPatternPP::OnExit() 
{
	// TODO: Add your control notification handler code here
	
	if(AfxMessageBox("This will terminate the test programm", MB_OKCANCEL) == IDOK)
	{
		m_pPropertySheet->EndDialog(0);
	}
}



/////////////////////////////////////////////////////////////////////////////
// CDIOBitPatternPP message handlers

BOOL CDIOBitPatternPP::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	LPNMHDR lpnmh = (LPNMHDR)lParam;
	
	if(wParam == IDC_LIST_DATA)
	{
		if(lpnmh->code == LVN_GETDISPINFO)
		{
			LV_DISPINFO *lpdi = (LV_DISPINFO *)lParam;

			if( (lpdi->item.mask & LVIF_TEXT) == LVIF_TEXT )
			{
				unsigned short us_value = *(unsigned short*)&m_sBoardDIOBP[m_iCurrentBoardIndex].m_psDataBuffer[lpdi->item.iItem];

				int i_bits[8];

				unsigned short us_mask;
				
				if(lpdi->item.iSubItem == 0)
				{
					us_mask = 0x8000;
				}
				else
				{
					us_mask = 0x0080;
				}

				for(int index_bit = 7; index_bit >= 0; index_bit--)
				{
					if( (us_value & us_mask) == us_mask )
					{
						i_bits[index_bit] = 1;
					}
					else
					{
						i_bits[index_bit] = 0;
					}

					us_mask>>= 1;
				}
				
				char sz_text[64];

				sz_text[0] = 0;

				sprintf(sz_text, "%d %d %d %d %d %d %d %d",
						i_bits[7],
						i_bits[6],
						i_bits[5],
						i_bits[4],
						i_bits[3],
						i_bits[2],
						i_bits[1],
						i_bits[0]								);
				
				strcpy(lpdi->item.pszText, sz_text);
			}
		}
	}

	return CPropertyPage::OnNotify(wParam, lParam, pResult);
}


void CDIOBitPatternPP::OnCheckPortA() 
{
	// TODO: Add your control notification handler code here

	OnCheckPort(0);
}

void CDIOBitPatternPP::OnCheckPortB() 
{
	// TODO: Add your control notification handler code here

	OnCheckPort(1);
}

void CDIOBitPatternPP::OnCheckPortC() 
{
	// TODO: Add your control notification handler code here

	OnCheckPort(2);
}

void CDIOBitPatternPP::OnCheckPortD() 
{
	// TODO: Add your control notification handler code here

	OnCheckPort(3);
}

void CDIOBitPatternPP::OnRadioDiobpWraparound() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RADIO_LOOP_ENDLESS)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_LOOP_FINITE)->EnableWindow(TRUE);

	if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_bInfiniteLoops)
	{
		GetDlgItem(IDC_EDIT_LOOP_FINITE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_LOOP_FINITE)->EnableWindow(TRUE);
	}
}

void CDIOBitPatternPP::OnRadioDiobpContinuous() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RADIO_LOOP_ENDLESS)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO_LOOP_FINITE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_LOOP_FINITE)->EnableWindow(FALSE);
}

void CDIOBitPatternPP::OnRadioTriggerSoftware() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RADIO_TRIGGER_RISING)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_TRIGGER_FALLING)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_TRIGGER_BOTH)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(FALSE);

	m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerMode = ME4000_DIOBP_TRIGGER_SOFTWARE;
}

void CDIOBitPatternPP::OnRadioTriggerDigital() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RADIO_TRIGGER_RISING)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_TRIGGER_FALLING)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_TRIGGER_BOTH)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);

	m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerMode = ME4000_DIOBP_TRIGGER_EXT_DIGITAL;
}

void CDIOBitPatternPP::OnRadioLoopEndless() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_EDIT_LOOP_FINITE)->EnableWindow(FALSE);
	
	m_sBoardDIOBP[m_iCurrentBoardIndex].m_bInfiniteLoops = TRUE;
}

void CDIOBitPatternPP::OnRadioLoopFinite() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_EDIT_LOOP_FINITE)->EnableWindow(TRUE);
	
	m_sBoardDIOBP[m_iCurrentBoardIndex].m_bInfiniteLoops = FALSE;
}

void CDIOBitPatternPP::OnStart() 
{
	// TODO: Add your control notification handler code here
	
	if( !m_sBoardDIOBP[m_iCurrentBoardIndex].m_bDIOBPActive )
	{
		CDataExchange dx(this, TRUE);
		
		DoDataExchange(&dx);

		int i_error;
		
		for(int index_port = 0; index_port < 4; index_port++)
		{
			if( m_sBoardDIOBP[m_iCurrentBoardIndex].m_bUsePort[index_port] )
			{
				i_error = me4000DIOBPPortConfig(m_iCurrentBoardIndex,													// uiBoardNumber
												index_port,																// uiPortNumber,
												m_sBoardDIOBP[m_iCurrentBoardIndex].m_iPortOutputMode[index_port]	);	// iOutputMode

				if(i_error != ME4000_NO_ERROR)
				{
					return;
				}
			}
		}
		
		unsigned long ul_ticks_low_part;

		unsigned long ul_ticks_high_part;

		me4000FrequencyToTicks(	(double)m_sBoardDIOBP[m_iCurrentBoardIndex].m_uiOutputRate,		// dRequiredFreq,
								&ul_ticks_low_part,												// pulTicksLowPart,
								&ul_ticks_high_part,											// pulTicksHighPart,
								ME4000_POINTER_NOT_USED										);	// pdAchievedFreq - not required

		int i_ext_trigger_edge = m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerExtEdge;

		if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerMode != ME4000_DIOBP_TRIGGER_EXT_DIGITAL)
		{
			i_ext_trigger_edge = ME4000_VALUE_NOT_USED;
		}

		i_error = me4000DIOBPConfig(m_iCurrentBoardIndex,									// uiBoardNumber,
									ul_ticks_low_part,										// ulTicks,
									m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerMode,		// iTriggerMode,
									i_ext_trigger_edge									);	// iExtTriggerEdge

		if(i_error != ME4000_NO_ERROR)
		{
			return;
		}

		unsigned long ul_timeout_seconds = m_sBoardDIOBP[m_iCurrentBoardIndex].m_ulTimeout;

		if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_iTriggerMode != ME4000_DIOBP_TRIGGER_EXT_DIGITAL)
		{
			ul_timeout_seconds = ME4000_VALUE_NOT_USED;
		}

		if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_iFunction == DIOBP_WRAPAROUND)
		{
			unsigned long ul_loops = m_sBoardDIOBP[m_iCurrentBoardIndex].m_uiFiniteLoops;

			if( m_sBoardDIOBP[m_iCurrentBoardIndex].m_bInfiniteLoops )
			{
				ul_loops = ME4000_DIOBP_WRAPAROUND_INFINITE;
			}
		
			i_error = me4000DIOBPWraparound(m_iCurrentBoardIndex,										// uiBoardNumber,
											m_sBoardDIOBP[m_iCurrentBoardIndex].m_psDataBuffer,			// psBuffer,
											m_sBoardDIOBP[m_iCurrentBoardIndex].m_ulNumberOfData,		// ulDataCount,
											ul_loops,													// ulLoops,
											ME4000_DIOBP_WRAPAROUND_ASYNCHRONOUS,						// iExecutionMode,
											WraparoundTerminate,										// pTerminateProc,
											&m_sBoardDIOBP[m_iCurrentBoardIndex],						// pTerminateContext,
											ul_timeout_seconds										);	// ulTimeOutSeconds	
		
			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}
		}
		else
		{
			unsigned long ul_number_of_values_written;

			i_error = me4000DIOBPContinuous(m_iCurrentBoardIndex,										// uiBoardNumber,
											m_sBoardDIOBP[m_iCurrentBoardIndex].m_psDataBuffer,			// psBuffer,
											m_sBoardDIOBP[m_iCurrentBoardIndex].m_ulNumberOfData,		// ulDataCount,
											ContinuousCallback,											// pCallbackProc,
											&m_sBoardDIOBP[m_iCurrentBoardIndex],						// pTerminateContext,
											ul_timeout_seconds,											// ulTimeOutSeconds	
											&ul_number_of_values_written							);	// pulNumberOfValuesWritten	

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}

			if(ul_number_of_values_written == m_sBoardDIOBP[m_iCurrentBoardIndex].m_ulNumberOfData)
			{
				m_sBoardDIOBP[m_iCurrentBoardIndex].m_bAppendBuffer = FALSE;
			}
			else
			{
				m_sBoardDIOBP[m_iCurrentBoardIndex].m_ulSizeOfAppend = m_sBoardDIOBP[m_iCurrentBoardIndex].m_ulNumberOfData - ul_number_of_values_written;
				
				m_sBoardDIOBP[m_iCurrentBoardIndex].m_uiAppendOffset = ul_number_of_values_written;

				m_sBoardDIOBP[m_iCurrentBoardIndex].m_bAppendBuffer = TRUE;
			}
		}

		i_error = me4000DIOBPStart(m_iCurrentBoardIndex);
		
		if(i_error != ME4000_NO_ERROR)
		{
			return;
		}

		m_sBoardDIOBP[m_iCurrentBoardIndex].m_bDIOBPActive = TRUE;

		if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_iFunction == DIOBP_WRAPAROUND)
		{
			m_sBoardDIOBP[m_iCurrentBoardIndex].m_iLastOperation = DIOBP_WRAPAROUND;
	
			SetDlgItemText(IDC_START, "Stop last value");
	
			GetDlgItem(IDC_START)->EnableWindow(TRUE);

			SetDlgItemText(IDC_STOP, "Stop immediate");

			GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
		}
		else
		{
			m_sBoardDIOBP[m_iCurrentBoardIndex].m_iLastOperation = DIOBP_CONTINUOUS;
	
			SetDlgItemText(IDC_START, "Append");

			if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_bAppendBuffer)
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
	else // if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_bDIOBPActive)
	{
		if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_iLastOperation == DIOBP_WRAPAROUND)
		{
			me4000DIOBPStop(m_iCurrentBoardIndex,				// uiBoardNumber,
							ME4000_DIOBP_STOP_MODE_LAST_VALUE	);	// iStopMode		
		}
		else if( (m_sBoardDIOBP[m_iCurrentBoardIndex].m_iLastOperation == DIOBP_CONTINUOUS)&&
											( !m_sBoardDIOBP[m_iCurrentBoardIndex].m_bAppendBuffer ) )
		{
			GetDlgItem(IDC_START)->EnableWindow(FALSE);
			
			CDataExchange dx_read(this, TRUE);

			m_sBoardDIOBP[m_iCurrentBoardIndex].m_ulSizeOfAppend = m_sBoardDIOBP[m_iCurrentBoardIndex].m_ulNumberOfData;

			m_sBoardDIOBP[m_iCurrentBoardIndex].m_uiAppendOffset = 0;
			
			m_sBoardDIOBP[m_iCurrentBoardIndex].m_bAppendBuffer = TRUE;
		}
	}
}

void CDIOBitPatternPP::OnStop() 
{
	// TODO: Add your control notification handler code here
	
	if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_bDIOBPActive)
	{
		me4000DIOBPStop(m_iCurrentBoardIndex,					// uiBoardNumber
						ME4000_DIOBP_STOP_MODE_IMMEDIATE	);	// iStopMode		
		
		m_sBoardDIOBP[m_iCurrentBoardIndex].m_bDIOBPActive = FALSE;

		if(m_sBoardDIOBP[m_iCurrentBoardIndex].m_iLastOperation == DIOBP_CONTINUOUS)
		{
			SetDlgItemText(IDC_START, "Start");

			GetDlgItem(IDC_START)->EnableWindow(TRUE);

			GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		}
	}
}

void CDIOBitPatternPP::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if( (m_sBoardDIOBP[m_iCurrentBoardIndex].m_iLastOperation == DIOBP_CONTINUOUS)&&
											(m_sBoardDIOBP[m_iCurrentBoardIndex].m_bDIOBPActive) )
	{
		int i_status;
		
		me4000DIOBPGetStatus(	m_iCurrentBoardIndex,		// uiBoardNumber,
								ME4000_DIOBP_WAIT_NONE,		// iWaitIdle,
								&i_status				);	// piStatus

		if(i_status == ME4000_DIOBP_STATUS_IDLE)
		{
			m_sBoardDIOBP[m_iCurrentBoardIndex].m_bDIOBPActive = FALSE;

			SetDlgItemText(IDC_START, "Start");

			GetDlgItem(IDC_START)->EnableWindow(TRUE);

			GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		}
	}

	CPropertyPage::OnTimer(nIDEvent);
}

void _stdcall CDIOBitPatternPP::WraparoundTerminate(void* pTerminateContext)
{
	SMEBoardDIOBP* p_diobp_board = (SMEBoardDIOBP*)pTerminateContext;

	p_diobp_board->m_pDIOBitPatternPP->SetDlgItemText(IDC_START, "Start");
	
	p_diobp_board->m_pDIOBitPatternPP->GetDlgItem(IDC_STOP)->EnableWindow(FALSE);

	p_diobp_board->m_bDIOBPActive = FALSE;
}

void _stdcall CDIOBitPatternPP::ContinuousCallback(unsigned long ulBufferAvailable, void* pCallbackContext)
{
	SMEBoardDIOBP* p_diobp_board = (SMEBoardDIOBP*)pCallbackContext;

	if(p_diobp_board->m_bAppendBuffer)
	{
		unsigned long ul_values_appended;
		
		me4000DIOBPAppendNewValues(	p_diobp_board->m_iIndexBoard,										// uiBoardNumber,
									p_diobp_board->m_psDataBuffer + p_diobp_board->m_uiAppendOffset,	// psBuffer,
									p_diobp_board->m_ulSizeOfAppend,									// ulNumberOfValuesToAppend,
									ME4000_DIOBP_APPEND_NEW_VALUES_BLOCKING,							// iExecutionMode,
									&ul_values_appended												);	// pulNumberOfValuesAppended
	}

	p_diobp_board->m_bAppendBuffer = FALSE;

//	p_msao_board->m_pAnalogOutputPP->GetDlgItem(IDC_STOP)->PostMessage(WM_ENABLE, TRUE, 0);

	p_diobp_board->m_pDIOBitPatternPP->GetDlgItem(IDC_START)->EnableWindow(TRUE);
}


