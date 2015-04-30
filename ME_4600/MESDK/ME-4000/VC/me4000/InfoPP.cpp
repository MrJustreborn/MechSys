// InfoPP.cpp : implementation file
//

#include "stdafx.h"
#include "me4000.h"
#include "InfoPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoPP property page

IMPLEMENT_DYNCREATE(CInfoPP, CPropertyPage)

CInfoPP::CInfoPP() : CPropertyPage(CInfoPP::IDD)
{
	//{{AFX_DATA_INIT(CInfoPP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iCurrentBoardIndex = 0;

	m_pPropertySheet = NULL;
}

CInfoPP::~CInfoPP()
{
}

void CInfoPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoPP)
	DDX_Control(pDX, IDC_COMBO_BOARD, m_comboBoardNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoPP, CPropertyPage)
	//{{AFX_MSG_MAP(CInfoPP)
	ON_CBN_SELCHANGE(IDC_COMBO_BOARD, OnSelchangeComboBoard)
	ON_BN_CLICKED(ID_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoPP message handlers

BOOL CInfoPP::OnInitDialog() 
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

	cs_text.Format( "%08X", p_app->GetDLLVersion() );
	
	SetDlgItemText(IDC_DLL_VERSION, cs_text);
	
	if(i_number_of_boards > 0)
	{
		cs_text.Format( "%08X", p_app->GetDriverVersion() );
	}
	else
	{
		cs_text = "????????";
	}
	
	SetDlgItemText(IDC_DRIVER_VERSION, cs_text);
	
	cs_text.Format( "%2d", i_number_of_boards );
	
	SetDlgItemText(IDC_NUMBER_OF_BOARDS_IN_SYSTEM, cs_text);
	
	DisplayBoardInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInfoPP::OnSelchangeComboBoard() 
{
	// TODO: Add your control notification handler code here
	
	m_iCurrentBoardIndex = m_comboBoardNumber.GetCurSel();
	
	DisplayBoardInfo();
}

void CInfoPP :: DisplayBoardInfo(void)
{
	Cme4000App* p_app = (Cme4000App*)AfxGetApp();

	ME4000Board* p_boards = p_app->GetBoardArray();

	CString cs_text;
	
	cs_text.Format( "%04X", p_boards[m_iCurrentBoardIndex].m_usDeviceID );
	
	SetDlgItemText(IDC_BOARD_VERSION, cs_text);
	
	cs_text.Format( "%08X", p_boards[m_iCurrentBoardIndex].m_ulSerialNumber );
	
	SetDlgItemText(IDC_SERIAL_NUMBER, cs_text);

	if(p_boards[m_iCurrentBoardIndex].m_bME4000Board)
	{
		if(p_boards[m_iCurrentBoardIndex].m_bAIVariableRanges)
		{
			cs_text = "Meilhaus ME-FoXX (ME-4600 series) 16 Bit Multi-I/O board";
		}
		else
		{
			cs_text = "Meilhaus ME-Jekyll (ME-4610 series) 16 Bit A/D -Converter  board";
		}
	}
	else
	{
		cs_text = "Meilhaus ME-6000/6100 series 16 Bit D/A-Converter board";
	}
	
	if(p_boards[m_iCurrentBoardIndex].m_bOptoIsolated)
	{
		cs_text+= "  -  Opto-isolated";
	}
	
	SetDlgItemText(IDC_DESCRIPTION, cs_text);

	cs_text.Format("%2d", p_boards[m_iCurrentBoardIndex].m_uiAINoOfChannels);
	
	SetDlgItemText(IDC_AI_NUMBER_OF_CHANNELS, cs_text);

	if(p_boards[m_iCurrentBoardIndex].m_uiAINoOfChannels == 0)
	{
		cs_text = "None";
	}
	else if(p_boards[m_iCurrentBoardIndex].m_bAIVariableRanges)
	{
		cs_text = "-10V - +10V,  -2.5V - +2.5V,  0V - +10V,  0V - 2.5V";
	}
	else
	{
		cs_text = "-10V - +10V";
	}

	SetDlgItemText(IDC_AI_SUPPORTED_INPUT_RANGES, cs_text);

	if(p_boards[m_iCurrentBoardIndex].m_bAISampleAndHold)
	{
		cs_text = "Yes";
	}
	else
	{
		cs_text = "No";
	}

	SetDlgItemText(IDC_AI_SAMPLE_AND_HOLD, cs_text);

	if(p_boards[m_iCurrentBoardIndex].m_bAIDifferentialMode)
	{
		cs_text = "Yes";
	}
	else
	{
		cs_text = "No";
	}

	SetDlgItemText(IDC_AI_DIFFERENTIAL_MODE, cs_text);

	if(p_boards[m_iCurrentBoardIndex].m_bAIAnalogTrigger)
	{
		cs_text = "Yes";
	}
	else
	{
		cs_text = "No";
	}

	SetDlgItemText(IDC_AI_ANALOG_TRIGGER_UNIT, cs_text);

	cs_text.Format("%2d", p_boards[m_iCurrentBoardIndex].m_uiAONoOfChannels);

	SetDlgItemText(IDC_AO_NUMBER_OF_CHANNELS, cs_text);

	if(p_boards[m_iCurrentBoardIndex].m_uiNoOfAOFIFOs > 0)
	{
		cs_text.Format("First %2d channels", p_boards[m_iCurrentBoardIndex].m_uiNoOfAOFIFOs);
	}
	else
	{
		cs_text = "None";
	}

	SetDlgItemText(IDC_AO_NUMBER_OF_CHANNELS_WITH_FIFO, cs_text);

	if(p_boards[m_iCurrentBoardIndex].m_bME4000Board)
	{
		SetDlgItemText(IDC_DIO_NUMBER_OF_PORTS, "4");

		if(p_boards[m_iCurrentBoardIndex].m_bOptoIsolated)
		{
			SetDlgItemText(IDC_DIO_DIRECTION_PORT_A, "Output only");

			SetDlgItemText(IDC_DIO_DIRECTION_PORT_B, "Input only");
		}
		else
		{
			SetDlgItemText(IDC_DIO_DIRECTION_PORT_A, "Bidirectional");

			SetDlgItemText(IDC_DIO_DIRECTION_PORT_B, "Bidirectional");
		}

		SetDlgItemText(IDC_DIO_DIRECTION_PORT_C, "Bidirectional");

		SetDlgItemText(IDC_DIO_DIRECTION_PORT_D, "Bidirectional");
	}
	else
	{
		unsigned int ui_no_of_dio_ports = 0;
		
		if(p_boards[m_iCurrentBoardIndex].m_uiDIONumberOfPorts == 0)
		{
			SetDlgItemText(IDC_DIO_NUMBER_OF_PORTS, "None");

			SetDlgItemText(IDC_DIO_DIRECTION_PORT_A, "-");

			SetDlgItemText(IDC_DIO_DIRECTION_PORT_B, "-");
		}
		else
		{
			SetDlgItemText(IDC_DIO_NUMBER_OF_PORTS, "2");

			SetDlgItemText(IDC_DIO_DIRECTION_PORT_A, "Bidirectional");

			SetDlgItemText(IDC_DIO_DIRECTION_PORT_B, "Bidirectional");
		}
		
		SetDlgItemText(IDC_DIO_DIRECTION_PORT_C, "-");

		SetDlgItemText(IDC_DIO_DIRECTION_PORT_D, "-");
	}

	if(p_boards[m_iCurrentBoardIndex].m_uiNumberOfCounters > 0)
	{
		cs_text.Format("%2d", p_boards[m_iCurrentBoardIndex].m_uiNumberOfCounters);
	}
	else
	{
		cs_text = "None";
	}

	SetDlgItemText(IDC_CNT_NUMBER_OF_COUNTERS, cs_text);

	if(p_boards[m_iCurrentBoardIndex].m_bME4000Board > 0)
	{
		cs_text = "Yes";
	}
	else
	{
		cs_text = "No";
	}

	SetDlgItemText(IDC_EXT_INT, cs_text);
}

void CInfoPP::OnExit() 
{
	// TODO: Add your control notification handler code here

	if(AfxMessageBox("This will terminate the test programm", MB_OKCANCEL) == IDOK)
	{
		m_pPropertySheet->EndDialog(0);
	}
}
