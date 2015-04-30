// CounterPWMPP.cpp : implementation file
//

#include "stdafx.h"
#include "me4000.h"
#include "CounterPWMPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCounterPWMPP property page

IMPLEMENT_DYNCREATE(CCounterPWMPP, CPropertyPage)

CCounterPWMPP::CCounterPWMPP() : CPropertyPage(CCounterPWMPP::IDD)
{
	//{{AFX_DATA_INIT(CCounterPWMPP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iCurrentBoardIndex = 0;

	m_pPropertySheet = NULL;
}

CCounterPWMPP::~CCounterPWMPP()
{
}

void CCounterPWMPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCounterPWMPP)
	DDX_Control(pDX, IDC_SPIN_PRE_SCALER, m_spinPreScaler);
	DDX_Control(pDX, IDC_SPIN_DUTY_CYCLE, m_spinDutyCycle);
	DDX_Control(pDX, IDC_SPIN_WRITE_VALUE_1, m_spinWriteValue1);
	DDX_Control(pDX, IDC_COMBO_COUNTER_MODE_1, m_comboMode1);
	DDX_Control(pDX, IDC_SPIN_WRITE_VALUE_2, m_spinWriteValue2);
	DDX_Control(pDX, IDC_COMBO_COUNTER_MODE_2, m_comboMode2);
	DDX_Control(pDX, IDC_SPIN_WRITE_VALUE_3, m_spinWriteValue3);
	DDX_Control(pDX, IDC_COMBO_COUNTER_MODE_3, m_comboMode3);
	DDX_Control(pDX, IDC_COMBO_BOARD, m_comboBoardNumber);
	//}}AFX_DATA_MAP
}


void CCounterPWMPP::SetControlStates(void)
{
	Cme4000App* p_app = (Cme4000App*)AfxGetApp();

	ME4000Board* p_boards = p_app->GetBoardArray();

	CString cs_text;
	
	cs_text.Format( "%04X", p_boards[m_iCurrentBoardIndex].m_usDeviceID );
	
	SetDlgItemText(IDC_BOARD_VERSION, cs_text);
	
	cs_text.Format( "%08X", p_boards[m_iCurrentBoardIndex].m_ulSerialNumber );
	
	SetDlgItemText(IDC_SERIAL_NUMBER, cs_text);
}


BEGIN_MESSAGE_MAP(CCounterPWMPP, CPropertyPage)
	//{{AFX_MSG_MAP(CCounterPWMPP)
	ON_BN_CLICKED(ID_EXIT, OnExit)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_1, OnButtonWrite1)
	ON_BN_CLICKED(IDC_BUTTON_READ_1, OnButtonRead1)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_2, OnButtonWrite2)
	ON_BN_CLICKED(IDC_BUTTON_READ_2, OnButtonRead2)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_3, OnButtonWrite3)
	ON_BN_CLICKED(IDC_BUTTON_READ_3, OnButtonRead3)
	ON_BN_CLICKED(IDC_BUTTON_PWM_START, OnButtonPwmStart)
	ON_BN_CLICKED(IDC_BUTTON_PWM_STOP, OnButtonPwmStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CCounterPWMPP::OnInitDialog() 
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

	m_comboMode1.SetCurSel(0);
	m_comboMode2.SetCurSel(0);
	m_comboMode3.SetCurSel(0);

	m_spinWriteValue1.SetRange32(0, 65535);
	m_spinWriteValue2.SetRange32(0, 65535);
	m_spinWriteValue3.SetRange32(0, 65535);

	UDACCEL arr_udaccel[4];

	arr_udaccel[0].nSec = 0; 
    arr_udaccel[0].nInc = 1;

	arr_udaccel[1].nSec = 2; 
    arr_udaccel[1].nInc = 10;

	arr_udaccel[2].nSec = 4; 
    arr_udaccel[2].nInc = 100;

	arr_udaccel[3].nSec = 6; 
    arr_udaccel[3].nInc = 1000;

	m_spinWriteValue1.SetAccel(4, &arr_udaccel[0]);
	m_spinWriteValue2.SetAccel(4, &arr_udaccel[0]);
	m_spinWriteValue3.SetAccel(4, &arr_udaccel[0]);

	m_spinPreScaler.SetRange32(2, 100);

	m_spinDutyCycle.SetRange32(1, 99);

	SetDlgItemText(IDC_EDIT_WRITE_VALUE_1, "0");
	SetDlgItemText(IDC_EDIT_WRITE_VALUE_2, "0");
	SetDlgItemText(IDC_EDIT_WRITE_VALUE_3, "0");

	SetDlgItemText(IDC_EDIT_READ_VALUE_1, "0");
	SetDlgItemText(IDC_EDIT_READ_VALUE_2, "0");
	SetDlgItemText(IDC_EDIT_READ_VALUE_3, "0");

	SetDlgItemText(IDC_EDIT_PRE_SCALER, "2");

	SetDlgItemText(IDC_EDIT_DUTY_CYCLE, "50");

	SetControlStates();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCounterPWMPP::OnExit() 
{
	// TODO: Add your control notification handler code here
	
	if(AfxMessageBox("This will terminate the test programm", MB_OKCANCEL) == IDOK)
	{
		m_pPropertySheet->EndDialog(0);
	}
}



/////////////////////////////////////////////////////////////////////////////
// CCounterPWMPP message handlers

void CCounterPWMPP::OnButtonWrite1() 
{
	// TODO: Add your control notification handler code here
	
	int i_mode_index = m_comboMode1.GetCurSel();

	int i_cnt_mode;

	switch(i_mode_index)
	{
	case 0:

		i_cnt_mode = ME4000_CNT_MODE_0;

		break;

	case 1:

		i_cnt_mode = ME4000_CNT_MODE_1;

		break;

	case 2:

		i_cnt_mode = ME4000_CNT_MODE_2;

		break;

	case 3:

		i_cnt_mode = ME4000_CNT_MODE_3;

		break;

	case 4:

		i_cnt_mode = ME4000_CNT_MODE_4;

		break;

	case 5:

		i_cnt_mode = ME4000_CNT_MODE_5;

		break;
	}

	CDataExchange dx_read(this, TRUE);
		
	int i_count;

	DDX_Text(&dx_read, IDC_EDIT_WRITE_VALUE_1, i_count);

	me4000CntWrite(	m_iCurrentBoardIndex,		// uiBoardNumber
					0,							// uiCounterNumber
					i_cnt_mode,					// iMode
					(unsigned short)i_count	);	// usValue
}

void CCounterPWMPP::OnButtonWrite2() 
{
	// TODO: Add your control notification handler code here
	
	int i_mode_index = m_comboMode2.GetCurSel();

	int i_cnt_mode;

	switch(i_mode_index)
	{
	case 0:

		i_cnt_mode = ME4000_CNT_MODE_0;

		break;

	case 1:

		i_cnt_mode = ME4000_CNT_MODE_1;

		break;

	case 2:

		i_cnt_mode = ME4000_CNT_MODE_2;

		break;

	case 3:

		i_cnt_mode = ME4000_CNT_MODE_3;

		break;

	case 4:

		i_cnt_mode = ME4000_CNT_MODE_4;

		break;

	case 5:

		i_cnt_mode = ME4000_CNT_MODE_5;

		break;
	}

	CDataExchange dx_read(this, TRUE);
		
	int i_count;

	DDX_Text(&dx_read, IDC_EDIT_WRITE_VALUE_2, i_count);

	me4000CntWrite(	m_iCurrentBoardIndex,		// uiBoardNumber
					1,							// uiCounterNumber
					i_cnt_mode,					// iMode
					(unsigned short)i_count	);	// usValue
}

void CCounterPWMPP::OnButtonWrite3() 
{
	// TODO: Add your control notification handler code here
	
	int i_mode_index = m_comboMode3.GetCurSel();

	int i_cnt_mode;

	switch(i_mode_index)
	{
	case 0:

		i_cnt_mode = ME4000_CNT_MODE_0;

		break;

	case 1:

		i_cnt_mode = ME4000_CNT_MODE_1;

		break;

	case 2:

		i_cnt_mode = ME4000_CNT_MODE_2;

		break;

	case 3:

		i_cnt_mode = ME4000_CNT_MODE_3;

		break;

	case 4:

		i_cnt_mode = ME4000_CNT_MODE_4;

		break;

	case 5:

		i_cnt_mode = ME4000_CNT_MODE_5;

		break;
	}

	CDataExchange dx_read(this, TRUE);
		
	int i_count;

	DDX_Text(&dx_read, IDC_EDIT_WRITE_VALUE_3, i_count);

	me4000CntWrite(	m_iCurrentBoardIndex,		// uiBoardNumber
					2,							// uiCounterNumber
					i_cnt_mode,					// iMode
					(unsigned short)i_count	);	// usValue
}

void CCounterPWMPP::OnButtonRead1() 
{
	// TODO: Add your control notification handler code here
	
	unsigned short us_count;

	int i_error = me4000CntRead(m_iCurrentBoardIndex,		// uiBoardNumber
								0,							// uiCounterNumber
								&us_count				);	// pusValue
	
	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	CDataExchange dx_write(this, FALSE);
		
	int i_count = (int)us_count;
	
	DDX_Text(&dx_write, IDC_EDIT_READ_VALUE_1, i_count);
}

void CCounterPWMPP::OnButtonRead2() 
{
	// TODO: Add your control notification handler code here
	
	unsigned short us_count;

	int i_error = me4000CntRead(m_iCurrentBoardIndex,		// uiBoardNumber
								1,							// uiCounterNumber
								&us_count				);	// pusValue
	
	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	CDataExchange dx_write(this, FALSE);
		
	int i_count = (int)us_count;
	
	DDX_Text(&dx_write, IDC_EDIT_READ_VALUE_2, i_count);
}

void CCounterPWMPP::OnButtonRead3() 
{
	// TODO: Add your control notification handler code here
	
	unsigned short us_count;

	int i_error = me4000CntRead(m_iCurrentBoardIndex,		// uiBoardNumber
								2,							// uiCounterNumber
								&us_count				);	// pusValue
	
	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	CDataExchange dx_write(this, FALSE);
		
	int i_count = (int)us_count;
	
	DDX_Text(&dx_write, IDC_EDIT_READ_VALUE_3, i_count);
}

void CCounterPWMPP::OnButtonPwmStart() 
{
	// TODO: Add your control notification handler code here
	
	CDataExchange dx_read(this, TRUE);
		
	unsigned int ui_pre_scaler;
	
	DDX_Text(&dx_read, IDC_EDIT_PRE_SCALER, ui_pre_scaler);

	int i_duty_cycle;
	
	DDX_Text(&dx_read, IDC_EDIT_DUTY_CYCLE, i_duty_cycle);

	int i_error = me4000CntPWMStart(m_iCurrentBoardIndex,		// uiBoardNumber
									ui_pre_scaler,				// uiPreScaler
									i_duty_cycle			);	// iDutyCycle

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	GetDlgItem(IDC_BUTTON_WRITE_1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_READ_1)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_WRITE_2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_READ_2)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_WRITE_3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_READ_3)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_PWM_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PWM_STOP)->EnableWindow(TRUE);
}

void CCounterPWMPP::OnButtonPwmStop() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000CntPWMStop(m_iCurrentBoardIndex);		// uiBoardNumber

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	GetDlgItem(IDC_BUTTON_WRITE_1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_READ_1)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_WRITE_2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_READ_2)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_WRITE_3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_READ_3)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_PWM_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PWM_STOP)->EnableWindow(FALSE);
}
