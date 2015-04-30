// ME9000DDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ME9000MIO.h"
#include "ME9000MIODlg.h"

#include "..\me9000miodll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CME9000DDlg dialog

CME9000DDlg::CME9000DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CME9000DDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CME9000DDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CME9000DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CME9000DDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CME9000DDlg, CDialog)
	//{{AFX_MSG_MAP(CME9000DDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_DIO_OPEN, OnButtonDioOpen)
	ON_BN_CLICKED(ID_BUTTON_DIO_RESET, OnButtonDioReset)
	ON_BN_CLICKED(ID_BUTTON_DIO_CONFIG, OnButtonDioConfig)
	ON_BN_CLICKED(ID_BUTTON_DIO_GET_BIT, OnButtonDioGetBit)
	ON_BN_CLICKED(ID_BUTTON_DIO_SET_BIT, OnButtonDioSetBit)
	ON_BN_CLICKED(ID_BUTTON_DIO_GET_BYTE, OnButtonDioGetByte)
	ON_BN_CLICKED(ID_BUTTON_DIO_SET_BYTE, OnButtonDioSetByte)
	ON_BN_CLICKED(ID_BUTTON_DIO_OUTPUT, OnButtonDioOutput)
	ON_BN_CLICKED(ID_BUTTON_DIO_SET_CALLBACK, OnButtonDioSetCallback)
	ON_BN_CLICKED(ID_BUTTON_DIO_GET_IRQ_COUNT, OnButtonDioGetIrqCount)
	ON_BN_CLICKED(ID_BUTTON_DIO_CLOSE, OnButtonDioClose)
	ON_BN_CLICKED(ID_BUTTON_CNT_OPEN, OnButtonCntOpen)
	ON_BN_CLICKED(ID_BUTTON_CNT_RESET, OnButtonCntReset)
	ON_BN_CLICKED(ID_BUTTON_CNT_CONFIG, OnButtonCntConfig)
	ON_BN_CLICKED(ID_BUTTON_CNT_WRITE, OnButtonCntWrite)
	ON_BN_CLICKED(ID_BUTTON_CNT_START, OnButtonCntStart)
	ON_BN_CLICKED(ID_BUTTON_CNT_READ, OnButtonCntRead)
	ON_BN_CLICKED(ID_BUTTON_CNT_STOP, OnButtonCntStop)
	ON_BN_CLICKED(ID_BUTTON_CNT_GET_IRQ_CNT, OnButtonCntGetIrqCount)
	ON_BN_CLICKED(ID_BUTTON_CNT_CLOSE, OnButtonCntClose)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_DIO_CONFIG_DIRECTION, OnSelchangeComboDioConfigDirection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CME9000DDlg message handlers

BOOL CME9000DDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_CONFIG_BIT_NUMBER) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_CONFIG_DIRECTION) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_CONFIG_INVERT) )->SetCurSel(0);
	
    OnSelchangeComboDioConfigDirection();

	( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_CONFIG_INTERRUPT) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_GET_BIT_BIT_NUMBER) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_SET_BIT_BIT_NUMBER) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_SET_BIT_BIT_VALUE) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_OUTPUT_BIT_NUMBER) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_OUTPUT_OUTPUT_MODE) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_SET_CALLBACK_CALLBACK) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_CNT_CONFIG_TRIGGER) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_CNT_CONFIG_CNT_EVENT) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_CNT_CONFIG_CLOCK_SOURCE) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_CNT_CONFIG_INTERRUPT) )->SetCurSel(0);
	
	( (CComboBox*)GetDlgItem(IDC_COMBO_CNT_CONFIG_CALLBACK) )->SetCurSel(0);

	( (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_CNT_WRITE_VALUE) )->SetRange32(0, 0xffff);

	SetDlgItemInt(IDC_EDIT_CNT_WRITE_VALUE, 0xffff);

	CString cs_title = "ME9000MIO    -    ";
	
	unsigned long ul_dll_version;
	
	me9000mioGetDLLVersion(&ul_dll_version);

	CString cs_text;

	cs_text.Format("DLL Ver.: %08X", ul_dll_version);

	cs_title+= cs_text;

	unsigned int ui_board_count;
	
	me9000mioGetBoardCount(&ui_board_count);

	if(ui_board_count == 0)
	{
		cs_title+= "    No boards found!";
	}
	else
	{
		unsigned long ul_drv_version;
		
		me9000mioGetDriverVersion(&ul_drv_version);

		cs_text.Format("  DRV Ver.: %08X", ul_drv_version);

		cs_title+= cs_text;

		cs_text.Format("    %2u boards found.    Board 0:    ", ui_board_count);

		cs_title+= cs_text;

		unsigned short us_brd_version;
		
		me9000mioGetBoardVersion(0, &us_brd_version);

		unsigned long ul_serial_number;
		
		me9000mioGetSerialNumber(0, &ul_serial_number);

		cs_text.Format("Brd. Ver.: %04X  Ser. Num.: %04X", us_brd_version, ul_serial_number);

		cs_title+= cs_text;
	}

	SetWindowText(cs_title);

	GetDlgItem(IDC_STATIC_DIO_SET_CALLBACK_NUMBER)->ShowWindow(SW_HIDE);
	
	GetDlgItem(IDC_STATIC_CNT_CONFIG_NUMBER)->ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CME9000DDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CME9000DDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CME9000DDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CME9000DDlg::OnButtonDioOpen() 
{
	// TODO: Add your control notification handler code here

	int i_error = me9000mioDIOOpen(0);
}

void CME9000DDlg::OnButtonDioReset() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me9000mioDIOReset(0);

	GetDlgItem(IDC_STATIC_DIO_SET_CALLBACK_NUMBER)->ShowWindow(SW_HIDE);
}

void CME9000DDlg::OnButtonDioConfig() 
{
	// TODO: Add your control notification handler code here
	
	unsigned int ui_bit_number = ( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_CONFIG_BIT_NUMBER) )->GetCurSel();
	
	int i_direction = ME9000MIO_DIO_OUTPUT + ( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_CONFIG_DIRECTION) )->GetCurSel();
	
	int i_invert = ME9000MIO_DIO_INV_DISABLE + ( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_CONFIG_INVERT) )->GetCurSel();
	
	int i_interrupt = ME9000MIO_DIO_INT_DISABLE + ( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_CONFIG_INTERRUPT) )->GetCurSel();

	int i_error = me9000mioDIOConfig(0, ui_bit_number, i_direction, i_invert, i_interrupt);
}

void CME9000DDlg::OnButtonDioGetBit() 
{
	// TODO: Add your control notification handler code here
	
	unsigned int ui_bit_number = ( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_GET_BIT_BIT_NUMBER) )->GetCurSel();

	int i_bit_value = -1;
	
	int i_error = me9000mioDIOGetBit(0, ui_bit_number, &i_bit_value);

	SetDlgItemInt(IDC_STATIC_DIO_GET_BIT_BIT_VALUE, i_bit_value);
}

void CME9000DDlg::OnButtonDioSetBit() 
{
	// TODO: Add your control notification handler code here
	
	unsigned int ui_bit_number = ( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_SET_BIT_BIT_NUMBER) )->GetCurSel();

	unsigned int i_bit_value = ( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_SET_BIT_BIT_VALUE) )->GetCurSel();

	int i_error = me9000mioDIOSetBit(0, ui_bit_number, i_bit_value);
}

void CME9000DDlg::OnButtonDioGetByte() 
{
	// TODO: Add your control notification handler code here
	
	unsigned char uc_byte_value = 0x00;
	
	int i_error = me9000mioDIOGetByte(0, &uc_byte_value);

	CheckDlgButton(IDC_CHECK_DIO_GET_BYTE_7, ( (uc_byte_value & 0x80) ) ? BST_CHECKED : BST_UNCHECKED);   // 0

	CheckDlgButton(IDC_CHECK_DIO_GET_BYTE_6, ( (uc_byte_value & 0x40) ) ? BST_CHECKED : BST_UNCHECKED);   // 0

	CheckDlgButton(IDC_CHECK_DIO_GET_BYTE_5, ( (uc_byte_value & 0x20) ) ? BST_CHECKED : BST_UNCHECKED);   // 0

	CheckDlgButton(IDC_CHECK_DIO_GET_BYTE_4, ( (uc_byte_value & 0x10) ) ? BST_CHECKED : BST_UNCHECKED);   // 0

	CheckDlgButton(IDC_CHECK_DIO_GET_BYTE_3, ( (uc_byte_value & 0x08) ) ? BST_CHECKED : BST_UNCHECKED);   // 0

	CheckDlgButton(IDC_CHECK_DIO_GET_BYTE_2, ( (uc_byte_value & 0x04) ) ? BST_CHECKED : BST_UNCHECKED);   // 0

	CheckDlgButton(IDC_CHECK_DIO_GET_BYTE_1, ( (uc_byte_value & 0x02) ) ? BST_CHECKED : BST_UNCHECKED);   // 0

	CheckDlgButton(IDC_CHECK_DIO_GET_BYTE_0, ( (uc_byte_value & 0x01) ) ? BST_CHECKED : BST_UNCHECKED);   // 0
}

void CME9000DDlg::OnButtonDioSetByte() 
{
	// TODO: Add your control notification handler code here
	
	unsigned char uc_byte_value = 0x00;

	if( IsDlgButtonChecked(IDC_CHECK_DIO_SET_BYTE_7)  )
	{
		uc_byte_value|= 0x80;
	}

	if( IsDlgButtonChecked(IDC_CHECK_DIO_SET_BYTE_6)  )
	{
		uc_byte_value|= 0x40;
	}

	if( IsDlgButtonChecked(IDC_CHECK_DIO_SET_BYTE_5)  )
	{
		uc_byte_value|= 0x20;
	}

	if( IsDlgButtonChecked(IDC_CHECK_DIO_SET_BYTE_4)  )
	{
		uc_byte_value|= 0x10;
	}

	if( IsDlgButtonChecked(IDC_CHECK_DIO_SET_BYTE_3)  )
	{
		uc_byte_value|= 0x08;
	}

	if( IsDlgButtonChecked(IDC_CHECK_DIO_SET_BYTE_2)  )
	{
		uc_byte_value|= 0x04;
	}

	if( IsDlgButtonChecked(IDC_CHECK_DIO_SET_BYTE_1)  )
	{
		uc_byte_value|= 0x02;
	}

	if( IsDlgButtonChecked(IDC_CHECK_DIO_SET_BYTE_0)  )
	{
		uc_byte_value|= 0x01;
	}
	
	int i_error = me9000mioDIOSetByte(0, uc_byte_value);
}

void CME9000DDlg::OnButtonDioOutput() 
{
	// TODO: Add your control notification handler code here
	
	unsigned int ui_bit_number = ( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_OUTPUT_BIT_NUMBER) )->GetCurSel();

	unsigned int i_output_mode = ME9000MIO_DIO_OUTPUT_DISABLE + ( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_OUTPUT_OUTPUT_MODE) )->GetCurSel();

	int i_error = me9000mioDIOOutput(0, ui_bit_number, i_output_mode);
}

void CME9000DDlg::OnButtonDioSetCallback() 
{
	// TODO: Add your control notification handler code here 
	
	int i_function_number = ( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_SET_CALLBACK_CALLBACK) )->GetCurSel();

	ME9000MIO_P_DIO_PROC p_dio_irq_proc; 

	void* p_dio_irq_context;

	switch(i_function_number)
	{
	case 0:

		p_dio_irq_proc = NULL;

		p_dio_irq_context = NULL;

		GetDlgItem(IDC_STATIC_DIO_SET_CALLBACK_NUMBER)->ShowWindow(SW_HIDE);
	
		break;

	case 1:

		p_dio_irq_proc = CallbackDIOBeep;

		p_dio_irq_context = NULL;

		GetDlgItem(IDC_STATIC_DIO_SET_CALLBACK_NUMBER)->ShowWindow(SW_HIDE);
	
		break;

	case 2:

		p_dio_irq_proc = CallbackDIODisplayIrqCount;

		p_dio_irq_context = this;

		GetDlgItem(IDC_STATIC_DIO_SET_CALLBACK_NUMBER)->ShowWindow(SW_SHOW);
	
		break;
	}

	int i_error = me9000mioDIOSetCallback(0, p_dio_irq_proc, p_dio_irq_context);
}

void CME9000DDlg::OnButtonDioGetIrqCount() 
{
	// TODO: Add your control notification handler code here
	
	unsigned long ul_count = 0;
	
	me9000mioDIOGetIrqCount(0, &ul_count);

	SetDlgItemInt(IDC_STATIC_DIO_GET_IRQ_COUNT_NUMBER, ul_count);
}

void CME9000DDlg::OnButtonDioClose() 
{
	// TODO: Add your control notification handler code here
	
	me9000mioDIOClose(0);

	GetDlgItem(IDC_STATIC_DIO_SET_CALLBACK_NUMBER)->ShowWindow(SW_HIDE);
}

void CME9000DDlg::OnButtonCntOpen() 
{
	// TODO: Add your control notification handler code here
	
	me9000mioCntOpen(0);
}

void CME9000DDlg::OnButtonCntReset() 
{
	// TODO: Add your control notification handler code here
	
	me9000mioCntReset(0);

	GetDlgItem(IDC_STATIC_CNT_CONFIG_NUMBER)->ShowWindow(SW_HIDE);
}

void CME9000DDlg::OnButtonCntConfig() 
{
	// TODO: Add your control notification handler code here
	
	int i_retrigger = ME9000MIO_CNT_RETRIGGER_DISABLE + ( (CComboBox*)GetDlgItem(IDC_COMBO_CNT_CONFIG_TRIGGER) )->GetCurSel();
	
	int i_cnt_event = ME9000MIO_CNT_EVENT_DISABLE + ( (CComboBox*)GetDlgItem(IDC_COMBO_CNT_CONFIG_CNT_EVENT) )->GetCurSel();
	
	int i_clock_source = ME9000MIO_CNT_CLOCK_INTERNAL + ( (CComboBox*)GetDlgItem(IDC_COMBO_CNT_CONFIG_CLOCK_SOURCE) )->GetCurSel();

	int i_interrupt = ME9000MIO_CNT_INT_DISABLE + ( (CComboBox*)GetDlgItem(IDC_COMBO_CNT_CONFIG_INTERRUPT) )->GetCurSel();

	int i_function_number = ( (CComboBox*)GetDlgItem(IDC_COMBO_CNT_CONFIG_CALLBACK) )->GetCurSel();

	ME9000MIO_P_CNT_PROC p_cnt_irq_proc; 

	void* p_cnt_irq_context;

	switch(i_function_number)
	{
	case 0:

		p_cnt_irq_proc = NULL;

		p_cnt_irq_context = NULL;

		GetDlgItem(IDC_STATIC_CNT_CONFIG_NUMBER)->ShowWindow(SW_HIDE);

		break;

	case 1:

		p_cnt_irq_proc = CallbackCntBeep;

		p_cnt_irq_context = NULL;

		GetDlgItem(IDC_STATIC_CNT_CONFIG_NUMBER)->ShowWindow(SW_HIDE);

		break;

	case 2:

		p_cnt_irq_proc = CallbackCntDisplayIrqCount;

		p_cnt_irq_context = this;

		GetDlgItem(IDC_STATIC_CNT_CONFIG_NUMBER)->ShowWindow(SW_SHOW);

		break;
	}

	int i_error = me9000mioCntConfig(0, i_retrigger, i_cnt_event, i_clock_source, i_interrupt, 
																p_cnt_irq_proc, p_cnt_irq_context);
}

void CME9000DDlg::OnButtonCntWrite() 
{
	// TODO: Add your control notification handler code here
	
	unsigned short us_value = (unsigned short)GetDlgItemInt(IDC_EDIT_CNT_WRITE_VALUE);

	int i_error = me9000mioCntWrite(0, us_value);
}

void CME9000DDlg::OnButtonCntStart() 
{
	// TODO: Add your control notification handler code here
	
	me9000mioCntStart(0);
}

void CME9000DDlg::OnButtonCntRead() 
{
	// TODO: Add your control notification handler code here
	
	unsigned short us_value = 0;

	int i_error = me9000mioCntRead(0, &us_value);

	SetDlgItemInt(IDC_STATIC_CNT_READ_VALUE, (int)us_value);
}

void CME9000DDlg::OnButtonCntStop() 
{
	// TODO: Add your control notification handler code here
	
	me9000mioCntStop(0);
}

void CME9000DDlg::OnButtonCntGetIrqCount() 
{
	// TODO: Add your control notification handler code here
	
	unsigned long ul_count = 0;
	
	me9000mioCntGetIrqCount(0, &ul_count);

	SetDlgItemInt(IDC_STATIC_CNT_GET_IRQ_COUNT, ul_count);
}

void CME9000DDlg::OnButtonCntClose() 
{
	// TODO: Add your control notification handler code here
	
	me9000mioCntClose(0);

	GetDlgItem(IDC_STATIC_CNT_CONFIG_NUMBER)->ShowWindow(SW_HIDE);
}

void _stdcall CME9000DDlg::CallbackDIOBeep(void* pDIOIrqContext)
{
	Beep(1000, 50);
}

void _stdcall CME9000DDlg::CallbackDIODisplayIrqCount(void* pDIOIrqContext)
{
	CME9000DDlg* p_dlg = (CME9000DDlg*)pDIOIrqContext;
	
	unsigned long ul_count;
	
	me9000mioDIOGetIrqCount(0,	&ul_count);

	p_dlg->SetDlgItemInt(IDC_STATIC_DIO_SET_CALLBACK_NUMBER, ul_count);

	p_dlg->GetDlgItem(IDC_STATIC_DIO_SET_CALLBACK_NUMBER)->Invalidate();
}

void _stdcall CME9000DDlg::CallbackCntBeep(void* pDIOIrqContext)
{
	Beep(250, 50);
}

void _stdcall CME9000DDlg::CallbackCntDisplayIrqCount(void* pDIOIrqContext)
{
	CME9000DDlg* p_dlg = (CME9000DDlg*)pDIOIrqContext;
	
	unsigned long ul_count;
	
	me9000mioCntGetIrqCount(0,	&ul_count);

	p_dlg->SetDlgItemInt(IDC_STATIC_CNT_CONFIG_NUMBER, ul_count);

	p_dlg->GetDlgItem(IDC_STATIC_CNT_CONFIG_NUMBER)->Invalidate();
}


HBRUSH CME9000DDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here

	if( (pWnd->GetDlgCtrlID() == IDC_STATIC_DIO_SET_CALLBACK_NUMBER)||
								(pWnd->GetDlgCtrlID() == IDC_STATIC_CNT_CONFIG_NUMBER) )
	{
		// Set the text color to red
		pDC->SetTextColor(RGB(255, 0, 0));
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CME9000DDlg::OnSelchangeComboDioConfigDirection() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	int i_direction = ME9000MIO_DIO_OUTPUT + ( (CComboBox*)GetDlgItem(IDC_COMBO_DIO_CONFIG_DIRECTION) )->GetCurSel();
	
    GetDlgItem(IDC_COMBO_DIO_CONFIG_INVERT)->EnableWindow( (i_direction == ME9000MIO_DIO_OUTPUT) ? FALSE : TRUE );
}
