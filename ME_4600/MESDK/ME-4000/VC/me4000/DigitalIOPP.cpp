// DigitalIOPP.cpp : implementation file
//

#include "stdafx.h"
#include "me4000.h"
#include "DigitalIOPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDigitalIOPP property page

IMPLEMENT_DYNCREATE(CDigitalIOPP, CPropertyPage)

CDigitalIOPP::CDigitalIOPP() : CPropertyPage(CDigitalIOPP::IDD)
{
	//{{AFX_DATA_INIT(CDigitalIOPP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	Cme4000App* p_app = (Cme4000App*)AfxGetApp();

	ME4000Board* p_boards = p_app->GetBoardArray();

	for(int index_board = 0; index_board < ME4000_MAX_DEVICES; index_board++)
	{
		if( !p_boards[index_board].m_bME4000Board )
		{
			m_sBoardDIO[index_board].m_bPortsAandBBidirectional = TRUE;
		}
		else
		{
			m_sBoardDIO[index_board].m_bPortsAandBBidirectional = !p_boards[index_board].m_bOptoIsolated;
		}
	}

	m_iRadioDirectionInputID[ME4000_DIO_PORT_A] = IDC_RADIO_INPUT_A;
	m_iRadioDirectionInputID[ME4000_DIO_PORT_B] = IDC_RADIO_INPUT_B;
	m_iRadioDirectionInputID[ME4000_DIO_PORT_C] = IDC_RADIO_INPUT_C;
	m_iRadioDirectionInputID[ME4000_DIO_PORT_D] = IDC_RADIO_INPUT_D;

	m_iInputBitID[ME4000_DIO_PORT_A][0] = IDC_INPUT_BIT_0_A;
	m_iInputBitID[ME4000_DIO_PORT_A][1] = IDC_INPUT_BIT_1_A;
	m_iInputBitID[ME4000_DIO_PORT_A][2] = IDC_INPUT_BIT_2_A;
	m_iInputBitID[ME4000_DIO_PORT_A][3] = IDC_INPUT_BIT_3_A;
	m_iInputBitID[ME4000_DIO_PORT_A][4] = IDC_INPUT_BIT_4_A;
	m_iInputBitID[ME4000_DIO_PORT_A][5] = IDC_INPUT_BIT_5_A;
	m_iInputBitID[ME4000_DIO_PORT_A][6] = IDC_INPUT_BIT_6_A;
	m_iInputBitID[ME4000_DIO_PORT_A][7] = IDC_INPUT_BIT_7_A;

	m_iInputBitID[ME4000_DIO_PORT_B][0] = IDC_INPUT_BIT_0_B;
	m_iInputBitID[ME4000_DIO_PORT_B][1] = IDC_INPUT_BIT_1_B;
	m_iInputBitID[ME4000_DIO_PORT_B][2] = IDC_INPUT_BIT_2_B;
	m_iInputBitID[ME4000_DIO_PORT_B][3] = IDC_INPUT_BIT_3_B;
	m_iInputBitID[ME4000_DIO_PORT_B][4] = IDC_INPUT_BIT_4_B;
	m_iInputBitID[ME4000_DIO_PORT_B][5] = IDC_INPUT_BIT_5_B;
	m_iInputBitID[ME4000_DIO_PORT_B][6] = IDC_INPUT_BIT_6_B;
	m_iInputBitID[ME4000_DIO_PORT_B][7] = IDC_INPUT_BIT_7_B;

	m_iInputBitID[ME4000_DIO_PORT_C][0] = IDC_INPUT_BIT_0_C;
	m_iInputBitID[ME4000_DIO_PORT_C][1] = IDC_INPUT_BIT_1_C;
	m_iInputBitID[ME4000_DIO_PORT_C][2] = IDC_INPUT_BIT_2_C;
	m_iInputBitID[ME4000_DIO_PORT_C][3] = IDC_INPUT_BIT_3_C;
	m_iInputBitID[ME4000_DIO_PORT_C][4] = IDC_INPUT_BIT_4_C;
	m_iInputBitID[ME4000_DIO_PORT_C][5] = IDC_INPUT_BIT_5_C;
	m_iInputBitID[ME4000_DIO_PORT_C][6] = IDC_INPUT_BIT_6_C;
	m_iInputBitID[ME4000_DIO_PORT_C][7] = IDC_INPUT_BIT_7_C;

	m_iInputBitID[ME4000_DIO_PORT_D][0] = IDC_INPUT_BIT_0_D;
	m_iInputBitID[ME4000_DIO_PORT_D][1] = IDC_INPUT_BIT_1_D;
	m_iInputBitID[ME4000_DIO_PORT_D][2] = IDC_INPUT_BIT_2_D;
	m_iInputBitID[ME4000_DIO_PORT_D][3] = IDC_INPUT_BIT_3_D;
	m_iInputBitID[ME4000_DIO_PORT_D][4] = IDC_INPUT_BIT_4_D;
	m_iInputBitID[ME4000_DIO_PORT_D][5] = IDC_INPUT_BIT_5_D;
	m_iInputBitID[ME4000_DIO_PORT_D][6] = IDC_INPUT_BIT_6_D;
	m_iInputBitID[ME4000_DIO_PORT_D][7] = IDC_INPUT_BIT_7_D;

	m_iInputByteButtonID[ME4000_DIO_PORT_A] = IDC_BUTTON_INPUT_BYTE_A;
	m_iInputByteButtonID[ME4000_DIO_PORT_B] = IDC_BUTTON_INPUT_BYTE_B;
	m_iInputByteButtonID[ME4000_DIO_PORT_C] = IDC_BUTTON_INPUT_BYTE_C;
	m_iInputByteButtonID[ME4000_DIO_PORT_D] = IDC_BUTTON_INPUT_BYTE_D;

	m_iOutputBitID[ME4000_DIO_PORT_A][0] = IDC_OUTPUT_BIT_0_A;
	m_iOutputBitID[ME4000_DIO_PORT_A][1] = IDC_OUTPUT_BIT_1_A;
	m_iOutputBitID[ME4000_DIO_PORT_A][2] = IDC_OUTPUT_BIT_2_A;
	m_iOutputBitID[ME4000_DIO_PORT_A][3] = IDC_OUTPUT_BIT_3_A;
	m_iOutputBitID[ME4000_DIO_PORT_A][4] = IDC_OUTPUT_BIT_4_A;
	m_iOutputBitID[ME4000_DIO_PORT_A][5] = IDC_OUTPUT_BIT_5_A;
	m_iOutputBitID[ME4000_DIO_PORT_A][6] = IDC_OUTPUT_BIT_6_A;
	m_iOutputBitID[ME4000_DIO_PORT_A][7] = IDC_OUTPUT_BIT_7_A;

	m_iOutputBitID[ME4000_DIO_PORT_B][0] = IDC_OUTPUT_BIT_0_B;
	m_iOutputBitID[ME4000_DIO_PORT_B][1] = IDC_OUTPUT_BIT_1_B;
	m_iOutputBitID[ME4000_DIO_PORT_B][2] = IDC_OUTPUT_BIT_2_B;
	m_iOutputBitID[ME4000_DIO_PORT_B][3] = IDC_OUTPUT_BIT_3_B;
	m_iOutputBitID[ME4000_DIO_PORT_B][4] = IDC_OUTPUT_BIT_4_B;
	m_iOutputBitID[ME4000_DIO_PORT_B][5] = IDC_OUTPUT_BIT_5_B;
	m_iOutputBitID[ME4000_DIO_PORT_B][6] = IDC_OUTPUT_BIT_6_B;
	m_iOutputBitID[ME4000_DIO_PORT_B][7] = IDC_OUTPUT_BIT_7_B;

	m_iOutputBitID[ME4000_DIO_PORT_C][0] = IDC_OUTPUT_BIT_0_C;
	m_iOutputBitID[ME4000_DIO_PORT_C][1] = IDC_OUTPUT_BIT_1_C;
	m_iOutputBitID[ME4000_DIO_PORT_C][2] = IDC_OUTPUT_BIT_2_C;
	m_iOutputBitID[ME4000_DIO_PORT_C][3] = IDC_OUTPUT_BIT_3_C;
	m_iOutputBitID[ME4000_DIO_PORT_C][4] = IDC_OUTPUT_BIT_4_C;
	m_iOutputBitID[ME4000_DIO_PORT_C][5] = IDC_OUTPUT_BIT_5_C;
	m_iOutputBitID[ME4000_DIO_PORT_C][6] = IDC_OUTPUT_BIT_6_C;
	m_iOutputBitID[ME4000_DIO_PORT_C][7] = IDC_OUTPUT_BIT_7_C;

	m_iOutputBitID[ME4000_DIO_PORT_D][0] = IDC_OUTPUT_BIT_0_D;
	m_iOutputBitID[ME4000_DIO_PORT_D][1] = IDC_OUTPUT_BIT_1_D;
	m_iOutputBitID[ME4000_DIO_PORT_D][2] = IDC_OUTPUT_BIT_2_D;
	m_iOutputBitID[ME4000_DIO_PORT_D][3] = IDC_OUTPUT_BIT_3_D;
	m_iOutputBitID[ME4000_DIO_PORT_D][4] = IDC_OUTPUT_BIT_4_D;
	m_iOutputBitID[ME4000_DIO_PORT_D][5] = IDC_OUTPUT_BIT_5_D;
	m_iOutputBitID[ME4000_DIO_PORT_D][6] = IDC_OUTPUT_BIT_6_D;
	m_iOutputBitID[ME4000_DIO_PORT_D][7] = IDC_OUTPUT_BIT_7_D;

	m_iOutputByteButtonID[ME4000_DIO_PORT_A] = IDC_BUTTON_OUTPUT_BYTE_A;
	m_iOutputByteButtonID[ME4000_DIO_PORT_B] = IDC_BUTTON_OUTPUT_BYTE_B;
	m_iOutputByteButtonID[ME4000_DIO_PORT_C] = IDC_BUTTON_OUTPUT_BYTE_C;
	m_iOutputByteButtonID[ME4000_DIO_PORT_D] = IDC_BUTTON_OUTPUT_BYTE_D;

	m_iInputBitValueID[ME4000_DIO_PORT_A] = IDC_CHECK_INPUT_BIT_VALUE_A;
	m_iInputBitValueID[ME4000_DIO_PORT_B] = IDC_CHECK_INPUT_BIT_VALUE_B;
	m_iInputBitValueID[ME4000_DIO_PORT_C] = IDC_CHECK_INPUT_BIT_VALUE_C;
	m_iInputBitValueID[ME4000_DIO_PORT_D] = IDC_CHECK_INPUT_BIT_VALUE_D;

	m_iInputBitButtonID[ME4000_DIO_PORT_A] = IDC_BUTTON_INPUT_BIT_A;
	m_iInputBitButtonID[ME4000_DIO_PORT_B] = IDC_BUTTON_INPUT_BIT_B;
	m_iInputBitButtonID[ME4000_DIO_PORT_C] = IDC_BUTTON_INPUT_BIT_C;
	m_iInputBitButtonID[ME4000_DIO_PORT_D] = IDC_BUTTON_INPUT_BIT_D;

	m_iOutputBitValueID[ME4000_DIO_PORT_A] = IDC_CHECK_OUTPUT_BIT_VALUE_A;
	m_iOutputBitValueID[ME4000_DIO_PORT_B] = IDC_CHECK_OUTPUT_BIT_VALUE_B;
	m_iOutputBitValueID[ME4000_DIO_PORT_C] = IDC_CHECK_OUTPUT_BIT_VALUE_C;
	m_iOutputBitValueID[ME4000_DIO_PORT_D] = IDC_CHECK_OUTPUT_BIT_VALUE_D;

	m_iOutputBitButtonID[ME4000_DIO_PORT_A] = IDC_BUTTON_OUTPUT_BIT_A;
	m_iOutputBitButtonID[ME4000_DIO_PORT_B] = IDC_BUTTON_OUTPUT_BIT_B;
	m_iOutputBitButtonID[ME4000_DIO_PORT_C] = IDC_BUTTON_OUTPUT_BIT_C;
	m_iOutputBitButtonID[ME4000_DIO_PORT_D] = IDC_BUTTON_OUTPUT_BIT_D;

	m_iCurrentBoardIndex = 0;

	m_pPropertySheet = NULL;
}

CDigitalIOPP::~CDigitalIOPP()
{
}

void CDigitalIOPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDigitalIOPP)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_COMBO_BOARD, m_comboBoardNumber);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_COMBO_OUTPUT_BIT_NUMBER_A, m_comboOutputBitNumber[ME4000_DIO_PORT_A]);
	DDX_Control(pDX, IDC_COMBO_OUTPUT_BIT_NUMBER_B, m_comboOutputBitNumber[ME4000_DIO_PORT_B]);
	DDX_Control(pDX, IDC_COMBO_OUTPUT_BIT_NUMBER_C, m_comboOutputBitNumber[ME4000_DIO_PORT_C]);
	DDX_Control(pDX, IDC_COMBO_OUTPUT_BIT_NUMBER_D, m_comboOutputBitNumber[ME4000_DIO_PORT_D]);
	
	DDX_Control(pDX, IDC_COMBO_INPUT_BIT_NUMBER_A, m_comboInputBitNumber[ME4000_DIO_PORT_A]);
	DDX_Control(pDX, IDC_COMBO_INPUT_BIT_NUMBER_B, m_comboInputBitNumber[ME4000_DIO_PORT_B]);
	DDX_Control(pDX, IDC_COMBO_INPUT_BIT_NUMBER_C, m_comboInputBitNumber[ME4000_DIO_PORT_C]);
	DDX_Control(pDX, IDC_COMBO_INPUT_BIT_NUMBER_D, m_comboInputBitNumber[ME4000_DIO_PORT_D]);
}


void CDigitalIOPP::OnRadioInput(int index_port)
{
	int i_error = me4000DIOConfig(	m_iCurrentBoardIndex,		// uiBoardNumber
									index_port,					// uiPortNumber,
									ME4000_DIO_PORT_INPUT	);	// iPortDirection

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	SetDlgItemText(m_iInputByteButtonID[index_port], "Get Byte");

	GetDlgItem(m_iOutputByteButtonID[index_port])->EnableWindow(FALSE);

	SetDlgItemText(m_iInputBitButtonID[index_port], "Get Bit");

	GetDlgItem(m_iOutputBitButtonID[index_port])->EnableWindow(FALSE);
};

void CDigitalIOPP::OnRadioOutput(int index_port)
{
	int i_error = me4000DIOConfig(	m_iCurrentBoardIndex,		// uiBoardNumber
									index_port,					// uiPortNumber,
									ME4000_DIO_PORT_OUTPUT	);	// iPortDirection

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	SetDlgItemText(m_iInputByteButtonID[index_port], "Read Port");

	GetDlgItem(m_iOutputByteButtonID[index_port])->EnableWindow(TRUE);

	SetDlgItemText(m_iInputBitButtonID[index_port], "Read Bit");

	GetDlgItem(m_iOutputBitButtonID[index_port])->EnableWindow(TRUE);
};

void CDigitalIOPP::OnButtonInputByte(int index_port)
{
	unsigned char uc_byte;

	me4000DIOGetByte(	m_iCurrentBoardIndex,		// uiBoardNumber
						index_port,					// uiPortNumber
						&uc_byte				);	// pucByteValue

	unsigned char uc_bit_mask = 0x01;
	
	for(int bit_number = 0; bit_number < 8; bit_number++)
	{
		if( (uc_byte & uc_bit_mask) == uc_bit_mask )
		{
			CheckDlgButton(m_iInputBitID[index_port][bit_number], BST_CHECKED);
		}
		else
		{
			CheckDlgButton(m_iInputBitID[index_port][bit_number], BST_UNCHECKED);
		}

		uc_bit_mask<<= 1;
	}
}

void CDigitalIOPP::OnButtonOutputByte(int index_port)
{
	unsigned char uc_byte = 0x00;

	unsigned char uc_bit_mask = 0x01;
	
	for(int bit_number = 0; bit_number < 8; bit_number++)
	{
		if( IsDlgButtonChecked( m_iOutputBitID[index_port][bit_number] ) )
		{
			uc_byte|= uc_bit_mask;
		}

		uc_bit_mask<<= 1;
	}

	me4000DIOSetByte(	m_iCurrentBoardIndex,	// uiBoardNumber
						index_port,				// uiPortNumber
						uc_byte				);	// pucByteValue
}

void CDigitalIOPP::OnButtonInputBit(int index_port)
{
	unsigned int ui_bit_number = (unsigned int)m_comboInputBitNumber[index_port].GetCurSel(); 

	int i_bit_value;
		
	me4000DIOGetBit(m_iCurrentBoardIndex,		// uiBoardNumber
					index_port,					// uiPortNumber
					ui_bit_number,				// uiBitNumber
					&i_bit_value			);	// piBitValue


	if(i_bit_value == 0)
	{
		CheckDlgButton(m_iInputBitValueID[index_port], BST_UNCHECKED);
	}
	else
	{
		CheckDlgButton(m_iInputBitValueID[index_port], BST_CHECKED);
	}
}

void CDigitalIOPP::OnButtonOutputBit(int index_port)
{
	unsigned int ui_bit_number = (unsigned int)m_comboOutputBitNumber[index_port].GetCurSel();

	int i_bit_value;
	
	if( IsDlgButtonChecked( m_iOutputBitValueID[index_port] ) )
	{
		i_bit_value = 1;
	}
	else
	{
		i_bit_value = 0;
	}
	
	me4000DIOSetBit(m_iCurrentBoardIndex,		// uiBoardNumber
					index_port,					// uiPortNumber
					ui_bit_number,				// uiBitNumber
					i_bit_value				);	// iBitValue
}

void CDigitalIOPP::SetControlStates(void)
{
	Cme4000App* p_app = (Cme4000App*)AfxGetApp();

	ME4000Board* p_boards = p_app->GetBoardArray();

	CString cs_text;
	
	cs_text.Format( "%04X", p_boards[m_iCurrentBoardIndex].m_usDeviceID );
	
	SetDlgItemText(IDC_BOARD_VERSION, cs_text);
	
	cs_text.Format( "%08X", p_boards[m_iCurrentBoardIndex].m_ulSerialNumber );
	
	SetDlgItemText(IDC_SERIAL_NUMBER, cs_text);
}


BEGIN_MESSAGE_MAP(CDigitalIOPP, CPropertyPage)
	//{{AFX_MSG_MAP(CDigitalIOPP)
	ON_BN_CLICKED(ID_EXIT, OnExit)
	ON_BN_CLICKED(IDC_RADIO_INPUT_A, OnRadioInputA)
	ON_BN_CLICKED(IDC_RADIO_OUTPUT_A, OnRadioOutputA)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_BYTE_A, OnButtonInputByteA)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_BYTE_A, OnButtonOutputByteA)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_BIT_A, OnButtonInputBitA)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_BIT_A, OnButtonOutputBitA)
	ON_BN_CLICKED(IDC_RADIO_INPUT_B, OnRadioInputB)
	ON_BN_CLICKED(IDC_RADIO_OUTPUT_B, OnRadioOutputB)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_BYTE_B, OnButtonInputByteB)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_BYTE_B, OnButtonOutputByteB)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_BIT_B, OnButtonInputBitB)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_BIT_B, OnButtonOutputBitB)
	ON_BN_CLICKED(IDC_RADIO_INPUT_C, OnRadioInputC)
	ON_BN_CLICKED(IDC_RADIO_OUTPUT_C, OnRadioOutputC)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_BYTE_C, OnButtonInputByteC)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_BYTE_C, OnButtonOutputByteC)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_BIT_C, OnButtonInputBitC)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_BIT_C, OnButtonOutputBitC)
	ON_BN_CLICKED(IDC_RADIO_INPUT_D, OnRadioInputD)
	ON_BN_CLICKED(IDC_RADIO_OUTPUT_D, OnRadioOutputD)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_BYTE_D, OnButtonInputByteD)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_BYTE_D, OnButtonOutputByteD)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_BIT_D, OnButtonInputBitD)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_BIT_D, OnButtonOutputBitD)
	ON_BN_CLICKED(ID_RESET_ALL, OnResetAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDigitalIOPP::OnInitDialog() 
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

	CDataExchange dx_write(this, FALSE);
		
	for(int index_port = 0; index_port < 4; index_port++)
	{
		m_comboOutputBitNumber[index_port].SetCurSel(0);

		m_comboInputBitNumber[index_port].SetCurSel(0);

		int i_direction;
		
		if( ( !m_sBoardDIO[m_iCurrentBoardIndex].m_bPortsAandBBidirectional )&&(index_port == 0) )
		{
			i_direction = 1;
			
			DDX_Radio(&dx_write, m_iRadioDirectionInputID[index_port], i_direction);

			SetDlgItemText(m_iInputByteButtonID[index_port], "Read Port");

			GetDlgItem(m_iOutputByteButtonID[index_port])->EnableWindow(TRUE);

			SetDlgItemText(m_iInputBitButtonID[index_port], "Read Bit");

			GetDlgItem(m_iOutputBitButtonID[index_port])->EnableWindow(TRUE);
		}
		else
		{
			i_direction = 0;
			
			DDX_Radio(&dx_write, m_iRadioDirectionInputID[index_port], i_direction);

			SetDlgItemText(m_iInputByteButtonID[index_port], "Get Byte");

			GetDlgItem(m_iOutputByteButtonID[index_port])->EnableWindow(FALSE);

			SetDlgItemText(m_iInputBitButtonID[index_port], "Get Bit");

			GetDlgItem(m_iOutputBitButtonID[index_port])->EnableWindow(FALSE);
		}
		
		if( !m_sBoardDIO[m_iCurrentBoardIndex].m_bPortsAandBBidirectional )
		{
			if(index_port == 0)
			{
				GetDlgItem(IDC_RADIO_INPUT_A)->EnableWindow(FALSE);
			}
			else if(index_port == 1)
			{
				GetDlgItem(IDC_RADIO_OUTPUT_B)->EnableWindow(FALSE);
			}
		}
	}

	SetControlStates();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDigitalIOPP::OnExit() 
{
	// TODO: Add your control notification handler code here
	
	if(AfxMessageBox("This will terminate the test programm", MB_OKCANCEL) == IDOK)
	{
		m_pPropertySheet->EndDialog(0);
	}
}



/////////////////////////////////////////////////////////////////////////////
// CDigitalIOPP message handlers

void CDigitalIOPP::OnRadioInputA() 
{
	// TODO: Add your control notification handler code here

	OnRadioInput(ME4000_DIO_PORT_A);
}

void CDigitalIOPP::OnRadioOutputA() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioOutput(ME4000_DIO_PORT_A);
}

void CDigitalIOPP::OnButtonInputByteA() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonInputByte(ME4000_DIO_PORT_A);
}

void CDigitalIOPP::OnButtonOutputByteA() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonOutputByte(ME4000_DIO_PORT_A);
}

void CDigitalIOPP::OnButtonInputBitA() 
{
	// TODO: Add your control notification handler code here

	OnButtonInputBit(ME4000_DIO_PORT_A);
}

void CDigitalIOPP::OnButtonOutputBitA() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonOutputBit(ME4000_DIO_PORT_A);
}
void CDigitalIOPP::OnRadioInputB() 
{
	// TODO: Add your control notification handler code here

	OnRadioInput(ME4000_DIO_PORT_B);
}

void CDigitalIOPP::OnRadioOutputB() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioOutput(ME4000_DIO_PORT_B);
}

void CDigitalIOPP::OnButtonInputByteB() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonInputByte(ME4000_DIO_PORT_B);
}

void CDigitalIOPP::OnButtonOutputByteB() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonOutputByte(ME4000_DIO_PORT_B);
}

void CDigitalIOPP::OnButtonInputBitB() 
{
	// TODO: Add your control notification handler code here

	OnButtonInputBit(ME4000_DIO_PORT_B);
}

void CDigitalIOPP::OnButtonOutputBitB() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonOutputBit(ME4000_DIO_PORT_B);
}
void CDigitalIOPP::OnRadioInputC() 
{
	// TODO: Add your control notification handler code here

	OnRadioInput(ME4000_DIO_PORT_C);
}

void CDigitalIOPP::OnRadioOutputC() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioOutput(ME4000_DIO_PORT_C);
}

void CDigitalIOPP::OnButtonInputByteC() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonInputByte(ME4000_DIO_PORT_C);
}

void CDigitalIOPP::OnButtonOutputByteC() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonOutputByte(ME4000_DIO_PORT_C);
}

void CDigitalIOPP::OnButtonInputBitC() 
{
	// TODO: Add your control notification handler code here

	OnButtonInputBit(ME4000_DIO_PORT_C);
}

void CDigitalIOPP::OnButtonOutputBitC() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonOutputBit(ME4000_DIO_PORT_C);
}
void CDigitalIOPP::OnRadioInputD() 
{
	// TODO: Add your control notification handler code here

	OnRadioInput(ME4000_DIO_PORT_D);
}

void CDigitalIOPP::OnRadioOutputD() 
{
	// TODO: Add your control notification handler code here
	
	OnRadioOutput(ME4000_DIO_PORT_D);
}

void CDigitalIOPP::OnButtonInputByteD() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonInputByte(ME4000_DIO_PORT_D);
}

void CDigitalIOPP::OnButtonOutputByteD() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonOutputByte(ME4000_DIO_PORT_D);
}

void CDigitalIOPP::OnButtonInputBitD() 
{
	// TODO: Add your control notification handler code here

	OnButtonInputBit(ME4000_DIO_PORT_D);
}

void CDigitalIOPP::OnButtonOutputBitD() 
{
	// TODO: Add your control notification handler code here
	
	OnButtonOutputBit(ME4000_DIO_PORT_D);
}

void CDigitalIOPP::OnResetAll() 
{
	// TODO: Add your control notification handler code here
	
	me4000DIOResetAll(m_iCurrentBoardIndex);	// uiBoardNumber

	CDataExchange dx_write(this, FALSE);
		
	for(int index_port = 0; index_port < 4; index_port++)
	{
		int i_direction;
		
		if( ( !m_sBoardDIO[m_iCurrentBoardIndex].m_bPortsAandBBidirectional )&&(index_port == 0) )
		{
			i_direction = 1;
			
			DDX_Radio(&dx_write, m_iRadioDirectionInputID[index_port], i_direction);

			OnRadioOutput(index_port);
		}
		else
		{
			i_direction = 0;
			
			DDX_Radio(&dx_write, m_iRadioDirectionInputID[index_port], i_direction);

			OnRadioInput(index_port);
		}
	}
}
