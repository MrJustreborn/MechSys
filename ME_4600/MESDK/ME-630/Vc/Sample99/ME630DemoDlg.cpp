// ME630DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ME630Demo.h"
#include "ME630DemoDlg.h"

#include "..\me630.h"

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
// CME630DemoDlg dialog

CME630DemoDlg::CME630DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CME630DemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CME630DemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iCurrentBoardIndex = 0;

	memset(&m_bIntEnabled[0][0], 0, sizeof(BOOL) * ME_MAX_DEVICES * 2);
}

void CME630DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CME630DemoDlg)
	DDX_Control(pDX, IDC_COMBO_DIO_SET_BIT, m_comboDIOSetBit);
	DDX_Control(pDX, IDC_COMBO_DIO_GET_BIT, m_comboDIOGetBit);
	DDX_Control(pDX, IDC_COMBO_SET_RELAY_BIT_NUMBER, m_comboSetRelayBitNumber);
	DDX_Control(pDX, IDC_COMBO_GET_TTL_BIT_NUMBER, m_comboGetTTLBitNumber);
	DDX_Control(pDX, IDC_COMBO_GET_RELAY_BIT_NUMBER, m_comboGetRelayBitNumber);
	DDX_Control(pDX, IDC_COMBO_GET_OPTO_BIT_NUMBER, m_comboGetOptoBitNumber);
	DDX_Control(pDX, IDC_BOARD_COMBO, m_comboBoardNumber);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CME630DemoDlg, CDialog)
	//{{AFX_MSG_MAP(CME630DemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_BOARD_COMBO, OnSelChangeBoardCombo)
	ON_BN_CLICKED(IDC_BUTTON_GET_OPTO_BIT, OnButtonGetOptoBit)
	ON_BN_CLICKED(IDC_BUTTON_GET_OPTO_BYTE, OnButtonGetOptoByte)
	ON_BN_CLICKED(IDC_BUTTON_GET_RELAY_BIT, OnButtonGetRelayBit)
	ON_BN_CLICKED(IDC_BUTTON_GET_RELAY_WORD, OnButtonGetRelayWord)
	ON_BN_CLICKED(IDC_BUTTON_GET_TTL_BIT, OnButtonGetTtlBit)
	ON_BN_CLICKED(IDC_BUTTON_GET_TTL_BYTE, OnButtonGetTtlByte)
	ON_BN_CLICKED(IDC_BUTTON_SET_RELAY_BIT, OnButtonSetRelayBit)
	ON_BN_CLICKED(IDC_BUTTON_SET_RELAY_WORD, OnButtonSetRelayWord)
	ON_BN_CLICKED(IDC_RADIO_IRQ1_DISABLE, OnRadioIRQ1Disable)
	ON_BN_CLICKED(IDC_RADIO_IRQ1_ENABLE, OnRadioIRQ1Enable)
	ON_BN_CLICKED(IDC_RADIO_IRQ2_DISABLE, OnRadioIRQ2Disable)
	ON_BN_CLICKED(IDC_RADIO_IRQ2_ENABLE, OnRadioIRQ2Enable)
	ON_BN_CLICKED(IDC_BUTTON_DIO_RESET_ALL, OnButtonDioResetAll)
	ON_BN_CLICKED(IDC_BUTTON_DIO_CONFIG, OnButtonDioConfig)
	ON_BN_CLICKED(IDC_BUTTON_DIO_GET_BYTE, OnButtonDioGetByte)
	ON_BN_CLICKED(IDC_BUTTON_DIO_GET_BIT, OnButtonDioGetBit)
	ON_BN_CLICKED(IDC_BUTTON_DIO_SET_BYTE, OnButtonDioSetByte)
	ON_BN_CLICKED(IDC_BUTTON_DIO_SET_BIT, OnButtonDioSetBit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CME630DemoDlg message handlers

BOOL CME630DemoDlg::OnInitDialog()
{
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	// Make an entry in the combo box for each board found
	for (int index_board = 0; index_board < ME_MAX_DEVICES; index_board++)
	{
		// call _me630GetBoardVersion simply to see if the board is there
		
		int i_version;			
		
		if( _me630GetBoardVersion(index_board, &i_version) )
		{
			CString cs_board;

			// Build a string with the board number
			
			cs_board.Format("Board %d", index_board);
			
			int combo_index = m_comboBoardNumber.AddString(cs_board);

			// Associate the combo entry with the board number as item data
			// We will use this to get the board number every time an element
			// is selected from the combo list
			m_comboBoardNumber.SetItemData(combo_index, (DWORD)index_board);
		}
	}

	// We know we must have found at least one board, otherwise we would have exited 
	// the application already in Cme630DemoApp::InitInstance with an error message

	// Select the first combo item into the combo box
	m_comboBoardNumber.SetCurSel(0);

	// Set the current board index. This is the item data for the selected item
	m_iCurrentBoardIndex = (int)m_comboBoardNumber.GetItemData(0);

	// Reset all dialog elements to correspond to the current board.
	SetDialogElements();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CME630DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CME630DemoDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CME630DemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CME630DemoDlg::OnSelChangeBoardCombo() 
{
	// TODO: Add your control notification handler code here
	
	// Find combo-box index of newly selected board
	int new_index = m_comboBoardNumber.GetCurSel();
	
	// Set the new current board
	m_iCurrentBoardIndex = (int)m_comboBoardNumber.GetItemData(new_index);

	// Reset all dialog elements to correspond to the current board.
	SetDialogElements();
}

void CME630DemoDlg::OnButtonGetOptoBit() 
{
	// TODO: Add your control notification handler code here
	
	// Get the chosen bit number	
	int i_bit_no = m_comboGetOptoBitNumber.GetCurSel();
	
	int i_value;
	
	// Get the bit value
	_me630DIGetOptoBit(m_iCurrentBoardIndex, i_bit_no, &i_value);

	if(i_value == 0)
	{
		// Bit value 0, uncheck the check box
		CheckDlgButton(IDC_CHECK_GET_OPTO_BIT_VALUE, 0);
	}
	else
	{
		// Bit value 1, check the check box
		CheckDlgButton(IDC_CHECK_GET_OPTO_BIT_VALUE, 1);
	}
}

void CME630DemoDlg::OnButtonGetOptoByte() 
{
	// TODO: Add your control notification handler code here
	
	// Read from the register of set m_iCurrentRegisterSet with an me630 call
	unsigned char uc_value;
	_me630DIGetOptoByte(m_iCurrentBoardIndex, &uc_value);

	// Set the appropriate check boxes in the dialog
	
	
	// Check the appropriate check box if the last bit of w_set is 1
	// Otherwise leave the check box unchecked
	CheckDlgButton(IDC_GET_OPTO_BIT_0, uc_value&0x01);

	// Shift w_set left to handle the next bit
	uc_value>>= 1;

	// Continue in this way with each bit of w_set and the appropriate check box
	
	CheckDlgButton(IDC_GET_OPTO_BIT_1, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_OPTO_BIT_2, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_OPTO_BIT_3, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_OPTO_BIT_4, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_OPTO_BIT_5, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_OPTO_BIT_6, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_OPTO_BIT_7, uc_value&0x01);
}

void CME630DemoDlg::OnButtonGetRelayBit() 
{
	// TODO: Add your control notification handler code here
	
	// Get the chosen bit number	
	int i_bit_no = m_comboGetRelayBitNumber.GetCurSel();
	
	int i_value;
	
	// Get the bit value
	_me630DIGetRelayBit(m_iCurrentBoardIndex, i_bit_no, &i_value);

	if(i_value == 0)
	{
		// Bit value 0, uncheck the check box
		CheckDlgButton(IDC_CHECK_GET_RELAY_BIT_VALUE, 0);
	}
	else
	{
		// Bit value 1, check the check box
		CheckDlgButton(IDC_CHECK_GET_RELAY_BIT_VALUE, 1);
	}
}

void CME630DemoDlg::OnButtonGetRelayWord() 
{
	// TODO: Add your control notification handler code here
	
	// Read from the register of set m_iCurrentRegisterSet with an me630 call
	unsigned short us_value;
	_me630DIGetRelayWord(m_iCurrentBoardIndex, &us_value);

	// Set the appropriate check boxes in the dialog
	
	
	// Check the appropriate check box if the last bit of us_value is 1
	// Otherwise leave the check box unchecked
	CheckDlgButton(IDC_GET_RELAY_BIT_0, us_value&0x01);

	// Shift w_set left to handle the next bit
	us_value>>= 1;

	// Continue in this way with each bit of w_set and the appropriate check box
	
	CheckDlgButton(IDC_GET_RELAY_BIT_1, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_2, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_3, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_4, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_5, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_6, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_7, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_8, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_9, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_10, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_11, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_12, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_13, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_14, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_GET_RELAY_BIT_15, us_value&0x01);
}

void CME630DemoDlg::OnButtonGetTtlBit() 
{
	// TODO: Add your control notification handler code here
	
	// Get the chosen bit number	
	int i_bit_no = m_comboGetTTLBitNumber.GetCurSel();
	
	int i_value;
	
	// Get the bit value
	_me630DIGetTTLBit(m_iCurrentBoardIndex, i_bit_no, &i_value);

	if(i_value == 0)
	{
		// Bit value 0, uncheck the check box
		CheckDlgButton(IDC_CHECK_GET_TTL_BIT_VALUE, 0);
	}
	else
	{
		// Bit value 1, check the check box
		CheckDlgButton(IDC_CHECK_GET_TTL_BIT_VALUE, 1);
	}
}

void CME630DemoDlg::OnButtonGetTtlByte() 
{
	// TODO: Add your control notification handler code here
	
	// Read from the register of set m_iCurrentRegisterSet with an me630 call
	unsigned char uc_value;
	_me630DIGetTTLByte(m_iCurrentBoardIndex, &uc_value);

	// Set the appropriate check boxes in the dialog
	
	
	// Check the appropriate check box if the last bit of w_set is 1
	// Otherwise leave the check box unchecked
	CheckDlgButton(IDC_GET_TTL_BIT_0, uc_value&0x01);

	// Shift w_set left to handle the next bit
	uc_value>>= 1;

	// Continue in this way with each bit of w_set and the appropriate check box
	
	CheckDlgButton(IDC_GET_TTL_BIT_1, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_TTL_BIT_2, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_TTL_BIT_3, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_TTL_BIT_4, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_TTL_BIT_5, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_TTL_BIT_6, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_GET_TTL_BIT_7, uc_value&0x01);
}

void CME630DemoDlg::OnButtonSetRelayBit() 
{
	// TODO: Add your control notification handler code here
	
	// Get the chosen bit number	
	int i_bit_no = m_comboSetRelayBitNumber.GetCurSel();
	
	// Get the bit value
	int i_value;
	
	if( IsDlgButtonChecked(IDC_CHECK_SET_RELAY_BIT_VALUE) )
	{
		// Check box is checked - bit value = 1.
		i_value = 1;
	}
	else
	{
		// Check box not checked - bit value = 0.
		i_value = 0;
	}

	// Set the bit value
	_me630DOSetRelayBit(m_iCurrentBoardIndex, i_bit_no, i_value);
}

void CME630DemoDlg::OnButtonSetRelayWord() 
{
	// TODO: Add your control notification handler code here
	
	// Initialise the relay word 
	unsigned short us_relay = 0;
	
	// Initialise a bit mask
	unsigned short us_mask = 0x0001;
	
	// If the check box corresponding to the first bit is checked, then set
	// the first bit in our result
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_0) )
	{
		us_relay|= us_mask;
	}

	// Shift the mask to handle the next bit
	us_mask<<= 1;

	// Continue in this way for each check box and the appropriate bit of our result
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_1) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_2) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_3) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_4) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_5) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_6) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_7) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_8) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_9) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_10) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_11) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_12) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_13) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_14) )
	{
		us_relay|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_SET_RELAY_BIT_15) )
	{
		us_relay|= us_mask;
	}
	
	// Write the relay word to the appropriate me630 register with an me630 call
	 _me630DOSetRelayWord(m_iCurrentBoardIndex, us_relay);
}


void CME630DemoDlg :: UpdateIRQ1Count(void)
{
	// Set int count for IRQ 1
	CWnd* p_wnd = p_wnd = GetDlgItem(IDC_IRQ1_COUNT);

	int i_cnt;
	
	_me630GetIrqCnt(m_iCurrentBoardIndex, ME630_IRQ_1, &i_cnt);

	CString cs_count;

	cs_count.Format("%7d", i_cnt);
	
	p_wnd->SetWindowText(cs_count);
}

void CME630DemoDlg :: UpdateIRQ2Count(void)
{
	// Set int count for IRQ 2
	CWnd* p_wnd = p_wnd = GetDlgItem(IDC_IRQ2_COUNT);

	int i_cnt;
	
	_me630GetIrqCnt(m_iCurrentBoardIndex, ME630_IRQ_2, &i_cnt);

	CString cs_count;

	cs_count.Format("%7d", i_cnt);
	
	p_wnd->SetWindowText(cs_count);
}


void CME630DemoDlg :: ReinitialiseBoard(int board_index)
{
	// Disable int in hardware
	_me630DisableInt(board_index, ME630_IRQ_1);
	_me630DisableInt(board_index, ME630_IRQ_2);

	// Reset Relays
	_me630ResetRelays(board_index);
}

void CME630DemoDlg :: SetDialogElements(void)
{
	// First get the device info.

	// Temporary structure for the information
	DEVICEINFOSTRUCT dev_info_struct;

	// Set all structure components to zero
	memset( (void *)&dev_info_struct, 0, sizeof(dev_info_struct) ); 

	// And fetch the information with an me630 call
	_me630GetDevInfo(m_iCurrentBoardIndex, &dev_info_struct);

	// Display the information obtained in the device info group box.

	// Temporary string for formatting
	CString cs_info;
	
	// Vendor ID
	
	// Format string with required information
	cs_info.Format("%X", dev_info_struct.dwVendorID);

	// Get the static text that we are going to set
	CWnd* p_wnd = GetDlgItem(IDC_VENDOR_ID);

	// Set the text
	p_wnd->SetWindowText(cs_info);

	// And do the same for all the other items in the group box
	
	// Device ID
	
	cs_info.Format("%X", dev_info_struct.dwDeviceID);

	p_wnd = GetDlgItem(IDC_DEVICE_ID);

	p_wnd->SetWindowText(cs_info);
	
	// System slot number
	
	cs_info.Format("%d", dev_info_struct.dwSystemSlotNumber);

	p_wnd = GetDlgItem(IDC_SYSTEM_SLOT_NUMBER);

	p_wnd->SetWindowText(cs_info);
	
	// Port base
	
	cs_info.Format("%X", dev_info_struct.dwPortBase);

	p_wnd = GetDlgItem(IDC_PORT_BASE);

	p_wnd->SetWindowText(cs_info);
	
	// Port count
	
	cs_info.Format("%d", dev_info_struct.dwPortCount);

	p_wnd = GetDlgItem(IDC_PORT_COUNT);

	p_wnd->SetWindowText(cs_info);

	// Interrupt channel
	
	cs_info.Format("%d", dev_info_struct.dwIntChannel);

	p_wnd = GetDlgItem(IDC_INTERRUPT_CHANNEL);

	p_wnd->SetWindowText(cs_info);

	// PLX port base
	
	cs_info.Format("%X", dev_info_struct.dwPortBasePLX);

	p_wnd = GetDlgItem(IDC_PLX_PORT_BASE);

	p_wnd->SetWindowText(cs_info);

	// PLX port count
	
	cs_info.Format("%d", dev_info_struct.dwPortCountPLX);

	p_wnd = GetDlgItem(IDC_PLX_PORT_COUNT);

	p_wnd->SetWindowText(cs_info);

	// Serial number
	
	cs_info.Format("%X", dev_info_struct.dwSerialNumber);

	p_wnd = GetDlgItem(IDC_SERIAL_NUMBER);

	p_wnd->SetWindowText(cs_info);

	// Bus number
	
	cs_info.Format("%X", dev_info_struct.dwBusNumber);

	p_wnd = GetDlgItem(IDC_BUS_NUMBER);

	p_wnd->SetWindowText(cs_info);

	// HW revision
	
	cs_info.Format("%d", dev_info_struct.dwHWRevision);

	p_wnd = GetDlgItem(IDC_HW_REVISION);

	p_wnd->SetWindowText(cs_info);

	// IRQ count
	
	cs_info.Format("%d", dev_info_struct.dwIrqCnt);

	p_wnd = GetDlgItem(IDC_IRQ_COUNT);

	p_wnd->SetWindowText(cs_info);

	// Version
	
	cs_info.Format("%X", dev_info_struct.dwVersion);

	p_wnd = GetDlgItem(IDC_VERSION);

	p_wnd->SetWindowText(cs_info);

	m_comboSetRelayBitNumber.SetCurSel(0);

	m_comboGetRelayBitNumber.SetCurSel(0);
	
	m_comboGetTTLBitNumber.SetCurSel(0);
	
	m_comboGetOptoBitNumber.SetCurSel(0);

	m_comboDIOGetBit.SetCurSel(0);

	m_comboDIOSetBit.SetCurSel(0);

	// Fill check boxes mit current values
	OnButtonGetRelayWord();
	OnButtonGetRelayBit();
	
	OnButtonGetTtlByte();
	OnButtonGetTtlBit();
	
	OnButtonGetOptoByte();
	OnButtonGetOptoBit();
	
	OnButtonDioGetByte();
	OnButtonDioGetBit();
	
	// Set the check boxes for 'Set Relay Word' to the current relay settings	
	unsigned short relay_word;

	_me630DIGetRelayWord(m_iCurrentBoardIndex, &relay_word);

	InitialiseSetRelayWordCheckBoxes(relay_word);
	
	// Set the check box for 'Set Relay Bit' to the current relay setting
	
	// Get the chosen bit number	
	int i_bit_no = m_comboSetRelayBitNumber.GetCurSel();
	
	int i_value;
	
	// Get the bit value
	_me630DIGetRelayBit(m_iCurrentBoardIndex, i_bit_no, &i_value);

	if(i_value == 0)
	{
		// Bit value 0, uncheck the check box
		CheckDlgButton(IDC_CHECK_SET_RELAY_BIT_VALUE, 0);
	}
	else
	{
		// Bit value 1, check the check box
		CheckDlgButton(IDC_CHECK_SET_RELAY_BIT_VALUE, 1);
	}

	CheckRadioButton(IDC_RADIO_DIO_CONFIG_PORT_C, IDC_RADIO_DIO_CONFIG_PORT_D, IDC_RADIO_DIO_CONFIG_PORT_C);
	
	CheckRadioButton(IDC_RADIO_DIO_CONFIG_INPUT, IDC_RADIO_DIO_CONFIG_OUTPUT, IDC_RADIO_DIO_CONFIG_INPUT);
	
	CheckRadioButton(IDC_RADIO_DIO_GET_BYTE_PORT_C, IDC_RADIO_DIO_GET_BYTE_PORT_D, IDC_RADIO_DIO_GET_BYTE_PORT_C);
	
	CheckRadioButton(IDC_RADIO_DIO_SET_BYTE_PORT_C, IDC_RADIO_DIO_SET_BYTE_PORT_D, IDC_RADIO_DIO_SET_BYTE_PORT_C);
	
	CheckRadioButton(IDC_RADIO_DIO_GET_BIT_PORT_C, IDC_RADIO_DIO_GET_BIT_PORT_D, IDC_RADIO_DIO_GET_BIT_PORT_C);
	
	CheckRadioButton(IDC_RADIO_DIO_SET_BIT_PORT_C, IDC_RADIO_DIO_SET_BIT_PORT_D, IDC_RADIO_DIO_SET_BIT_PORT_C);
	
	// Set interrupt to disabled/enabled for IRQ 1
	CheckRadioButton(IDC_RADIO_IRQ1_DISABLE, IDC_RADIO_IRQ1_ENABLE, 
							m_bIntEnabled[m_iCurrentBoardIndex][0] ? IDC_RADIO_IRQ1_ENABLE : IDC_RADIO_IRQ1_DISABLE);

	// Set interrupt to disabled/enabled for IRQ 2
	CheckRadioButton(IDC_RADIO_IRQ2_DISABLE, IDC_RADIO_IRQ2_ENABLE, 
							m_bIntEnabled[m_iCurrentBoardIndex][1] ? IDC_RADIO_IRQ2_ENABLE : IDC_RADIO_IRQ2_DISABLE);

	UpdateIRQ1Count();

	UpdateIRQ2Count();
}


void CME630DemoDlg :: InitialiseSetRelayWordCheckBoxes(unsigned short us_value)
{
	// Check the appropriate check box if the last bit of us_value is 1
	// Otherwise leave the check box unchecked
	CheckDlgButton(IDC_SET_RELAY_BIT_0, us_value&0x01);

	// Shift w_set left to handle the next bit
	us_value>>= 1;

	// Continue in this way with each bit of w_set and the appropriate check box
	
	CheckDlgButton(IDC_SET_RELAY_BIT_1, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_2, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_3, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_4, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_5, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_6, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_7, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_8, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_9, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_10, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_11, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_12, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_13, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_14, us_value&0x01);

	us_value>>= 1;
	
	CheckDlgButton(IDC_SET_RELAY_BIT_15, us_value&0x01);
}

void CME630DemoDlg::OnRadioIRQ1Disable() 
{
	// TODO: Add your control notification handler code here
	
	m_bIntEnabled[m_iCurrentBoardIndex][0] = FALSE;

	_me630DisableInt(m_iCurrentBoardIndex, ME630_IRQ_1);
}

void CME630DemoDlg::OnRadioIRQ1Enable() 
{
	// TODO: Add your control notification handler code here

	_me630EnableInt(m_iCurrentBoardIndex, ME630_IRQ_1, CME630DemoApp::IRQ1TestFunction, m_iCurrentBoardIndex);
	
	m_bIntEnabled[m_iCurrentBoardIndex][0] = TRUE;
}

void CME630DemoDlg::OnRadioIRQ2Disable() 
{
	// TODO: Add your control notification handler code here
	
	m_bIntEnabled[m_iCurrentBoardIndex][1] = FALSE;

	_me630DisableInt(m_iCurrentBoardIndex, ME630_IRQ_2);
}

void CME630DemoDlg::OnRadioIRQ2Enable() 
{
	// TODO: Add your control notification handler code here
	
	_me630EnableInt(m_iCurrentBoardIndex, ME630_IRQ_2, CME630DemoApp::IRQ2TestFunction, m_iCurrentBoardIndex);
	
	m_bIntEnabled[m_iCurrentBoardIndex][1] = TRUE;
}

void CME630DemoDlg::OnButtonDioResetAll() 
{
	// TODO: Add your control notification handler code here
	
	_me630DIOResetAll(m_iCurrentBoardIndex);
}

void CME630DemoDlg::OnButtonDioConfig() 
{
	// TODO: Add your control notification handler code here
	
	int i_port_number;

	if(IsDlgButtonChecked(IDC_RADIO_DIO_CONFIG_PORT_C) != 0)
	{
		i_port_number = ME630_DIO_PORT_C;
	}
	else
	{
		i_port_number = ME630_DIO_PORT_D;
	}

	int i_port_dir;

	if(IsDlgButtonChecked(IDC_RADIO_CONFIG_INPUT) != 0)
	{
		i_port_dir = ME630_DIO_PORT_INPUT;
	}
	else
	{
		i_port_dir = ME630_DIO_PORT_OUTPUT;
	}

	_me630DIOConfig(m_iCurrentBoardIndex, i_port_number, i_port_dir);

}

void CME630DemoDlg::OnButtonDioGetByte() 
{
	// TODO: Add your control notification handler code here
	
	int i_port_number;

	if(IsDlgButtonChecked(IDC_RADIO_DIO_GET_BYTE_PORT_C) != 0)
	{
		i_port_number = ME630_DIO_PORT_C;
	}
	else
	{
		i_port_number = ME630_DIO_PORT_D;
	}

	unsigned char uc_value;
	_me630DIOGetByte(m_iCurrentBoardIndex, i_port_number, &uc_value);

	// Set the appropriate check boxes in the dialog
	
	
	// Check the appropriate check box if the last bit of w_set is 1
	// Otherwise leave the check box unchecked
	CheckDlgButton(IDC_DIO_GET_BYTE_0, uc_value&0x01);

	// Shift w_set left to handle the next bit
	uc_value>>= 1;

	// Continue in this way with each bit of w_set and the appropriate check box
	
	CheckDlgButton(IDC_DIO_GET_BYTE_1, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_DIO_GET_BYTE_2, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_DIO_GET_BYTE_3, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_DIO_GET_BYTE_4, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_DIO_GET_BYTE_5, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_DIO_GET_BYTE_6, uc_value&0x01);

	uc_value>>= 1;
	
	CheckDlgButton(IDC_DIO_GET_BYTE_7, uc_value&0x01);
}

void CME630DemoDlg::OnButtonDioGetBit() 
{
	// TODO: Add your control notification handler code here
	
	int i_port_number;

	if(IsDlgButtonChecked(IDC_RADIO_DIO_GET_BIT_PORT_C) != 0)
	{
		i_port_number = ME630_DIO_PORT_C;
	}
	else
	{
		i_port_number = ME630_DIO_PORT_D;
	}

	// Get the chosen bit number	
	int i_bit_no = m_comboDIOGetBit.GetCurSel();
	
	int i_value;
	
	// Get the bit value
	_me630DIOGetBit(m_iCurrentBoardIndex, i_port_number, i_bit_no, &i_value);

	if(i_value == 0)
	{
		// Bit value 0, uncheck the check box
		CheckDlgButton(IDC_CHECK_DIO_GET_BIT, 0);
	}
	else
	{
		// Bit value 1, check the check box
		CheckDlgButton(IDC_CHECK_DIO_GET_BIT, 1);
	}
}

void CME630DemoDlg::OnButtonDioSetByte() 
{
	// TODO: Add your control notification handler code here
	
	int i_port_number;

	if(IsDlgButtonChecked(IDC_RADIO_DIO_SET_BYTE_PORT_C) != 0)
	{
		i_port_number = ME630_DIO_PORT_C;
	}
	else
	{
		i_port_number = ME630_DIO_PORT_D;
	}

	// Initialise the output byte 
	unsigned char uc_value = 0;
	
	// Initialise a bit mask
	unsigned char uc_mask = 0x01;
	
	// If the check box corresponding to the first bit is checked, then set
	// the first bit in our result
	if( IsDlgButtonChecked(IDC_DIO_SET_BYTE_0) )
	{
		uc_value|= uc_mask;
	}

	// Shift the mask to handle the next bit
	uc_mask<<= 1;

	// Continue in this way for each check box and the appropriate bit of our result
	
	if( IsDlgButtonChecked(IDC_DIO_SET_BYTE_1) )
	{
		uc_value|= uc_mask;
	}
	
	uc_mask<<= 1;

	if( IsDlgButtonChecked(IDC_DIO_SET_BYTE_2) )
	{
		uc_value|= uc_mask;
	}
	
	uc_mask<<= 1;

	if( IsDlgButtonChecked(IDC_DIO_SET_BYTE_3) )
	{
		uc_value|= uc_mask;
	}
	
	uc_mask<<= 1;

	if( IsDlgButtonChecked(IDC_DIO_SET_BYTE_4) )
	{
		uc_value|= uc_mask;
	}
	
	uc_mask<<= 1;

	if( IsDlgButtonChecked(IDC_DIO_SET_BYTE_5) )
	{
		uc_value|= uc_mask;
	}
	
	uc_mask<<= 1;

	if( IsDlgButtonChecked(IDC_DIO_SET_BYTE_6) )
	{
		uc_value|= uc_mask;
	}
	
	uc_mask<<= 1;

	if( IsDlgButtonChecked(IDC_DIO_SET_BYTE_7) )
	{
		uc_value|= uc_mask;
	}
	
	// Write the relay word to the appropriate me630 register with an me630 call
	 _me630DIOSetByte(m_iCurrentBoardIndex, i_port_number, uc_value);
}

void CME630DemoDlg::OnButtonDioSetBit() 
{
	// TODO: Add your control notification handler code here
	
	int i_port_number;

	if(IsDlgButtonChecked(IDC_RADIO_DIO_SET_BIT_PORT_C) != 0)
	{
		i_port_number = ME630_DIO_PORT_C;
	}
	else
	{
		i_port_number = ME630_DIO_PORT_D;
	}
	
	// Get the chosen bit number	
	int i_bit_no = m_comboDIOSetBit.GetCurSel();
	
	// Get the bit value
	int i_value;
	
	if( IsDlgButtonChecked(IDC_CHECK_DIO_SET_BIT) )
	{
		// Check box is checked - bit value = 1.
		i_value = 1;
	}
	else
	{
		// Check box not checked - bit value = 0.
		i_value = 0;
	}

	// Set the bit value
	_me630DIOSetBit(m_iCurrentBoardIndex, i_port_number, i_bit_no, i_value);
}
