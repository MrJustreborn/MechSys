// MultiSigPP.cpp : implementation file
//

#include "stdafx.h"
#include "me4000.h"
#include "MultiSigPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiSigPP property page

IMPLEMENT_DYNCREATE(CMultiSigPP, CPropertyPage)

CMultiSigPP::CMultiSigPP() : CPropertyPage(CMultiSigPP::IDD)
{
	//{{AFX_DATA_INIT(CMultiSigPP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iCurrentBoardIndex = 0;

	m_pPropertySheet = NULL;
}

CMultiSigPP::~CMultiSigPP()
{
}

void CMultiSigPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiSigPP)
	DDX_Control(pDX, IDC_COMBO_BOARD, m_comboBoardNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMultiSigPP, CPropertyPage)
	//{{AFX_MSG_MAP(CMultiSigPP)
	ON_BN_CLICKED(ID_EXIT, OnExit)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDC_BUTTON_LED_OFF_0, OnButtonLedOff0)
	ON_BN_CLICKED(IDC_BUTTON_LED_ON_0, OnButtonLedOn0)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_A_0, OnButtonGain1A0)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_A_0, OnButtonGain10A0)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_A_0, OnButtonGain100A0)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_B_0, OnButtonGain1B0)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_B_0, OnButtonGain10B0)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_B_0, OnButtonGain100B0)

	ON_BN_CLICKED(IDC_BUTTON_LED_OFF_1, OnButtonLedOff1)
	ON_BN_CLICKED(IDC_BUTTON_LED_ON_1, OnButtonLedOn1)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_A_1, OnButtonGain1A1)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_A_1, OnButtonGain10A1)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_A_1, OnButtonGain100A1)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_B_1, OnButtonGain1B1)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_B_1, OnButtonGain10B1)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_B_1, OnButtonGain100B1)

	ON_BN_CLICKED(IDC_BUTTON_LED_OFF_2, OnButtonLedOff2)
	ON_BN_CLICKED(IDC_BUTTON_LED_ON_2, OnButtonLedOn2)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_A_2, OnButtonGain1A2)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_A_2, OnButtonGain10A2)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_A_2, OnButtonGain100A2)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_B_2, OnButtonGain1B2)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_B_2, OnButtonGain10B2)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_B_2, OnButtonGain100B2)

	ON_BN_CLICKED(IDC_BUTTON_LED_OFF_3, OnButtonLedOff3)
	ON_BN_CLICKED(IDC_BUTTON_LED_ON_3, OnButtonLedOn3)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_A_3, OnButtonGain1A3)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_A_3, OnButtonGain10A3)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_A_3, OnButtonGain100A3)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_B_3, OnButtonGain1B3)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_B_3, OnButtonGain10B3)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_B_3, OnButtonGain100B3)

	ON_BN_CLICKED(IDC_BUTTON_LED_OFF_4, OnButtonLedOff4)
	ON_BN_CLICKED(IDC_BUTTON_LED_ON_4, OnButtonLedOn4)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_A_4, OnButtonGain1A4)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_A_4, OnButtonGain10A4)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_A_4, OnButtonGain100A4)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_B_4, OnButtonGain1B4)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_B_4, OnButtonGain10B4)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_B_4, OnButtonGain100B4)

	ON_BN_CLICKED(IDC_BUTTON_LED_OFF_5, OnButtonLedOff5)
	ON_BN_CLICKED(IDC_BUTTON_LED_ON_5, OnButtonLedOn5)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_A_5, OnButtonGain1A5)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_A_5, OnButtonGain10A5)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_A_5, OnButtonGain100A5)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_B_5, OnButtonGain1B5)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_B_5, OnButtonGain10B5)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_B_5, OnButtonGain100B5)

	ON_BN_CLICKED(IDC_BUTTON_LED_OFF_6, OnButtonLedOff6)
	ON_BN_CLICKED(IDC_BUTTON_LED_ON_6, OnButtonLedOn6)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_A_6, OnButtonGain1A6)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_A_6, OnButtonGain10A6)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_A_6, OnButtonGain100A6)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_B_6, OnButtonGain1B6)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_B_6, OnButtonGain10B6)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_B_6, OnButtonGain100B6)

	ON_BN_CLICKED(IDC_BUTTON_LED_OFF_7, OnButtonLedOff7)
	ON_BN_CLICKED(IDC_BUTTON_LED_ON_7, OnButtonLedOn7)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_A_7, OnButtonGain1A7)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_A_7, OnButtonGain10A7)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_A_7, OnButtonGain100A7)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_1_B_7, OnButtonGain1B7)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_10_B_7, OnButtonGain10B7)
	ON_BN_CLICKED(IDC_BUTTON_GAIN_100_B_7, OnButtonGain100B7)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiSigPP message handlers

BOOL CMultiSigPP::OnInitDialog() 
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

	ME4000Board* p_boards = p_app->GetBoardArray();

	cs_text.Format( "%04X", p_boards[m_iCurrentBoardIndex].m_usDeviceID );
	
	SetDlgItemText(IDC_BOARD_VERSION, cs_text);
	
	cs_text.Format( "%08X", p_boards[m_iCurrentBoardIndex].m_ulSerialNumber );
	
	SetDlgItemText(IDC_SERIAL_NUMBER, cs_text);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMultiSigPP::OnExit() 
{
	// TODO: Add your control notification handler code here
	
	if(AfxMessageBox("This will terminate the test programm", MB_OKCANCEL) == IDOK)
	{
		m_pPropertySheet->EndDialog(0);
	}
}

void CMultiSigPP::OnReset() 
{
	// TODO: Add your control notification handler code here

	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigReset(m_iCurrentBoardIndex);		// uiBoardNumber;	

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}											

void CMultiSigPP::OnButtonLedOff0() 
{
	// TODO: Add your control notification handler code here

	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								0,							// uiBase
								ME4000_MULTISIG_LED_OFF	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOn0() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								0,							// uiBase
								ME4000_MULTISIG_LED_ON	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1A0() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							0,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10A0() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							0,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100A0() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							0,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1B0() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							0,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10B0() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							0,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100B0() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							0,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOff1() 
{
	// TODO: Add your control notification handler code here

	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								1,							// uiBase
								ME4000_MULTISIG_LED_OFF	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOn1() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								1,							// uiBase
								ME4000_MULTISIG_LED_ON	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1A1() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							1,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10A1() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							1,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100A1() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							1,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1B1() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							1,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10B1() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							1,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100B1() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							1,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOff2() 
{
	// TODO: Add your control notification handler code here

	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								2,							// uiBase
								ME4000_MULTISIG_LED_OFF	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOn2() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								2,							// uiBase
								ME4000_MULTISIG_LED_ON	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1A2() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							2,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10A2() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							2,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100A2() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							2,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1B2() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							2,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10B2() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							2,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100B2() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							2,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOff3() 
{
	// TODO: Add your control notification handler code here

	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								3,							// uiBase
								ME4000_MULTISIG_LED_OFF	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOn3() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								3,							// uiBase
								ME4000_MULTISIG_LED_ON	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1A3() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							3,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10A3() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							3,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100A3() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							3,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1B3() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							3,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10B3() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							3,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100B3() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							3,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOff4() 
{
	// TODO: Add your control notification handler code here

	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								4,							// uiBase
								ME4000_MULTISIG_LED_OFF	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOn4() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								4,							// uiBase
								ME4000_MULTISIG_LED_ON	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1A4() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							4,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10A4() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							4,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100A4() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							4,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1B4() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							4,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10B4() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							4,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100B4() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							4,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOff5() 
{
	// TODO: Add your control notification handler code here

	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								5,							// uiBase
								ME4000_MULTISIG_LED_OFF	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOn5() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								5,							// uiBase
								ME4000_MULTISIG_LED_ON	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1A5() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							5,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10A5() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							5,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100A5() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							5,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1B5() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							5,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10B5() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							5,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100B5() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							5,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOff6() 
{
	// TODO: Add your control notification handler code here

	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								6,							// uiBase
								ME4000_MULTISIG_LED_OFF	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOn6() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								6,							// uiBase
								ME4000_MULTISIG_LED_ON	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1A6() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							6,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10A6() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							6,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100A6() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							6,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1B6() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							6,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10B6() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							6,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100B6() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							6,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOff7() 
{
	// TODO: Add your control notification handler code here

	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								7,							// uiBase
								ME4000_MULTISIG_LED_OFF	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonLedOn7() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigAddressLED(	m_iCurrentBoardIndex,		// uiBoardNumber
								7,							// uiBase
								ME4000_MULTISIG_LED_ON	);	// iLEDStatus

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1A7() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							7,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10A7() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							7,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100A7() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							7,								// uiBase
							ME4000_MULTISIG_GROUP_A,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain1B7() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							7,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_1		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain10B7() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							7,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_10		);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

void CMultiSigPP::OnButtonGain100B7() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000MultiSigOpen(m_iCurrentBoardIndex);	// uiBoardNumber;

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	me4000MultiSigSetGain(	m_iCurrentBoardIndex,			// uiBoardNumber
							7,								// uiBase
							ME4000_MULTISIG_GROUP_B,		// iChannelGroup,
							ME4000_MULTISIG_GAIN_100	);	// iGain				

	me4000MultiSigClose(m_iCurrentBoardIndex);	// uiBoardNumber;
}

