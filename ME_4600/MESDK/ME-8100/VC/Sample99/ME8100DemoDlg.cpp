// ME8100DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ME8100Demo.h"
#include "ME8100DemoDlg.h"

#include ".\..\me8100.h"
//#include ".\..\me8100io.h"

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
// CME8100DemoDlg dialog

CME8100DemoDlg::CME8100DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CME8100DemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CME8100DemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// Deny access to irq-functions
	m_bDisplayed			= FALSE;

	m_iCurrentBoardIndex	= 0;

	m_iCurrentRegisterSet	= REGISTER_SET_A;

	for(int index_board = 0; index_board < 32; index_board++)
	{
		m_arrayBoardSettings[index_board][0].m_iIntMode = INTERRUPT_ON_PATTERN_COMPARE;
		m_arrayBoardSettings[index_board][1].m_iIntMode = INTERRUPT_ON_PATTERN_COMPARE;
	
		m_arrayBoardSettings[index_board][0].m_iTristateMode = TRISTATE_ON;
		m_arrayBoardSettings[index_board][1].m_iTristateMode = TRISTATE_ON;
	
		m_arrayBoardSettings[index_board][0].m_iSinkOrSource = SINK_MODE;
		m_arrayBoardSettings[index_board][1].m_iSinkOrSource = SINK_MODE;
	
		m_arrayBoardSettings[index_board][0].m_wPattern = 0;
		m_arrayBoardSettings[index_board][1].m_wPattern = 0;
	
		m_arrayBoardSettings[index_board][0].m_wMask = 0;
		m_arrayBoardSettings[index_board][1].m_wMask = 0;
	
		m_arrayBoardSettings[index_board][0].m_csStatus = "Invalid";
		m_arrayBoardSettings[index_board][1].m_csStatus = "Invalid";
	
		m_arrayBoardSettings[index_board][0].m_csIRQCount = "0";
		m_arrayBoardSettings[index_board][1].m_csIRQCount = "0";
	}
}

void CME8100DemoDlg::BlinkIntAOn(void)
{
	CWnd* p_wnd = GetDlgItem(IDC_INT_RECTANGLE);

	p_wnd->ShowWindow(SW_SHOW);

	CString cs_info;
	
	// Get Int Status with a me8100 call
	int i_status;
	
	me8100DIGetIntStatus(m_iCurrentBoardIndex, m_iCurrentRegisterSet, &i_status);
	
	cs_info.Format( "0x%X", (unsigned short)i_status );

	p_wnd = GetDlgItem(IDC_INT_STATUS);

	p_wnd->SetWindowText(cs_info);

	int i_count;
	
	me8100GetIrqCnt(m_iCurrentBoardIndex, m_iCurrentRegisterSet, &i_count);	
	
	cs_info.Format( "%d", (unsigned short)i_count );

	p_wnd = GetDlgItem(IDC_INT_COUNT);

	p_wnd->SetWindowText(cs_info);
}

void CME8100DemoDlg::BlinkIntAOff(void)
{
	CWnd* p_wnd = GetDlgItem(IDC_INT_RECTANGLE);

	p_wnd->ShowWindow(SW_HIDE);
}

void CME8100DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CME8100DemoDlg)
	DDX_Control(pDX, IDC_COMBO_SET_BIT_NUMBER, m_comboSetBitNumber);
	DDX_Control(pDX, IDC_COMBO_GET_BIT_NUMBER, m_comboGetBitNumber);
	DDX_Control(pDX, IDC_COMBO_COUNTER_NO, m_comboCounterNumber);
	DDX_Control(pDX, IDC_COMBO_COUNTER_MODE, m_comboCounterMode);
	DDX_Control(pDX, IDC_BOARD_COMBO, m_comboBoards);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CME8100DemoDlg, CDialog)
	//{{AFX_MSG_MAP(CME8100DemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INPUT, OnButtonReadInput)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, OnButtonWriteOutput)
	ON_BN_CLICKED(IDC_BUTTON_MASK, OnButtonSetMask)
	ON_BN_CLICKED(IDC_BUTTON_PATTERN, OnButtonSetPattern)
	ON_BN_CLICKED(IDC_RADIO_DISABLE_INT, OnRadioDisableInt)
	ON_BN_CLICKED(IDC_RADIO_ENABLE_INT, OnRadioEnableInt)
	ON_BN_CLICKED(IDC_RADIO_INT_BIT_CHANGE, OnRadioIntBitChange)
	ON_BN_CLICKED(IDC_RADIO_INT_PATTERN_COMPARE, OnRadioIntPatternCompare)
	ON_BN_CLICKED(IDC_RADIO_SINK, OnRadioSink)
	ON_BN_CLICKED(IDC_RADIO_SOURCE, OnRadioSource)
	ON_BN_CLICKED(IDC_RADIO_TRISTATE_OFF, OnRadioTristateOff)
	ON_BN_CLICKED(IDC_RADIO_TRISTATE_ON, OnRadioTristateOn)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_BOARD_COMBO, OnSelChangeBoardCombo)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_REGISTER_SET, OnButtonChangeRegisterSet)
	ON_BN_CLICKED(IDC_BUTTON_GET_BIT, OnButtonGetBit)
	ON_BN_CLICKED(IDC_BUTTON_READ_COUNTER, OnButtonReadCounter)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_COUNTER, OnButtonWriteCounter)
	ON_BN_CLICKED(IDC_BUTTON_SET_BIT, OnButtonSetBit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CME8100DemoDlg message handlers

BOOL CME8100DemoDlg::OnInitDialog()
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
	
	// Make an entry in the combo box for each board found
	for (int index_board = 0; index_board < 32; index_board++)
	{
		// call me8100PROMVersion simply to see if the board is there
		
		int i_version;			
		
		if( me8100PROMVersion(index_board, &i_version) )
		{
			CString cs_board;

			// Build a string with the board number
			
			cs_board.Format("Board %d", index_board);
			
			int combo_index = m_comboBoards.AddString(cs_board);

			// Associate the combo entry with the board number as item data
			// We will use this to get the board number every time an element
			// is selected from the combo list
			m_comboBoards.SetItemData(combo_index, (DWORD)index_board);
		}
	}

	// We know we must have found at least one board, otherwise we would have exited 
	// the application already in CME8100DemoApp::InitInstance with an error message

	// Select the first combo item into the combo box
	m_comboBoards.SetCurSel(0);

	// Set the current board index. This is the item data for the selected item
	m_iCurrentBoardIndex = (int)m_comboBoards.GetItemData(0);

	// Reset all dialog elements to correspond to the current board.
	SetDialogElements();

	// Allow access to irq-functions
	m_bDisplayed = TRUE;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CME8100DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CME8100DemoDlg::OnPaint() 
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
HCURSOR CME8100DemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CME8100DemoDlg::OnButtonReadInput() 
{
	// Read from the register of set m_iCurrentRegisterSet with an me8100 call
	int i_value;
	me8100DIGetWord(m_iCurrentBoardIndex, m_iCurrentRegisterSet, &i_value);

	// Set the appropriate check boxes in the dialog
	DlgSetDigitalInput( (unsigned short)i_value );
}

void CME8100DemoDlg::OnButtonWriteOutput() 
{
	// Read the current user value from the dialog check boxes
	unsigned short w_out = 	DlgGetDigitalOutput();

	// Write the result to the DO register of set m_iCurrentRegisterSet with an me8100 call
	 me8100DOSetWord(m_iCurrentBoardIndex, m_iCurrentRegisterSet, (int)w_out);
}

void CME8100DemoDlg::OnButtonSetMask() 
{
	// Read the current user value from the dialog check boxes
	unsigned short w_mask = DlgGetMask();
	
	// Write the result to the mask register of set m_iCurrentRegisterSet with an me8100 call
	 me8100DIOSetMask(m_iCurrentBoardIndex, m_iCurrentRegisterSet, (int)w_mask);

	// Note the current value in the appropriate local variable
	m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_wMask = w_mask;
}

void CME8100DemoDlg::OnButtonSetPattern() 
{
	// Read the current user value from the dialog check boxes
	unsigned short w_pattern = 	DlgGetPattern();

	// Write the result to the mask register of set m_iCurrentRegisterSet with an me8100 call
	 me8100DIOSetPattern(m_iCurrentBoardIndex, m_iCurrentRegisterSet, (int)w_pattern);

	// Note the current value in the appropriate local variable
	m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_wPattern = w_pattern;
}

void CME8100DemoDlg::OnRadioDisableInt() 
{
	if(m_iIntStatus == INT_DISABLED)
	{
		// Nothing to do, already disabled

		return;
	}

	// Disable int in dialog  - radio button is set automatically 
	m_iIntStatus = INT_DISABLED;

	// Disable int in hardware
	me8100DisableInt(m_iCurrentBoardIndex, m_iCurrentRegisterSet);

	// Enable radio buttons	for setting the int modus
	GetDlgItem(IDC_RADIO_INT_PATTERN_COMPARE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_INT_BIT_CHANGE)->EnableWindow(TRUE);
}

void CME8100DemoDlg::OnRadioEnableInt() 
{
	if(m_iIntStatus == INT_ENABLED)
	{
		// Nothing to do, already enabled

		return;
	}

	// Enable int in dialog  - radio button is set automatically 
	m_iIntStatus = INT_ENABLED;

	// Disable int in hardware
	me8100EnableInt(m_iCurrentBoardIndex, m_iCurrentRegisterSet, CME8100DemoApp::IRQTestFunction, 0);
	
	// Disable radio buttons for setting the int modus
	GetDlgItem(IDC_RADIO_INT_PATTERN_COMPARE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_INT_BIT_CHANGE)->EnableWindow(FALSE);
}

void CME8100DemoDlg::OnRadioIntBitChange() 
{
	if(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iIntMode == INTERRUPT_ON_BIT_CHANGE)
	{
		// Nothing to do, mode already set

		return;
	}

	// Set interrupt mode to interrupt on bit change in dialog  - radio button is set automatically 
	m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iIntMode = INTERRUPT_ON_BIT_CHANGE;  

	// Set interrupt mode to interrupt on bit_change in hardware
	me8100DIOSetIntMode(m_iCurrentBoardIndex, m_iCurrentRegisterSet, INTERRUPT_ON_BIT_CHANGE);
}

void CME8100DemoDlg::OnRadioIntPatternCompare() 
{
	if(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iIntMode == INTERRUPT_ON_PATTERN_COMPARE)
	{
		// Nothing to do, mode already set

		return;
	}

	// Set interrupt mode to interrupt on pattern compare in dialog  - radio button is set automatically 
	m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iIntMode = INTERRUPT_ON_PATTERN_COMPARE;  

	// Set interrupt mode to interrupt on pattern compare in hardware
	me8100DIOSetIntMode(m_iCurrentBoardIndex, m_iCurrentRegisterSet, INTERRUPT_ON_PATTERN_COMPARE);
}

void CME8100DemoDlg::OnRadioSink() 
{
	if(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iSinkOrSource == SINK_MODE)
	{
		// Nothing to do, sink mode already set

		return;
	}
	
	// Set sink mode in hardware in dialog - radio button is set automatically 
	m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iSinkOrSource = SINK_MODE;

	// Set sink mode in hardware
	me8100SetSinkSourceMode(m_iCurrentBoardIndex, m_iCurrentRegisterSet, SINK_MODE);
}

void CME8100DemoDlg::OnRadioSource() 
{
	if(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iSinkOrSource == SOURCE_MODE)
	{
		// Nothing to do, source mode already set

		return;
	}
	
	// Set source mode in dialog - radio button is set automatically 
	m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iSinkOrSource = SOURCE_MODE;

	// Set source mode in hardware
	me8100SetSinkSourceMode(m_iCurrentBoardIndex, m_iCurrentRegisterSet, SOURCE_MODE);
}

void CME8100DemoDlg::OnRadioTristateOff() 
{
	if(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iTristateMode == TRISTATE_OFF)
	{
		// Nothing to do, tristate already off

		return;
	}
	
	// Set tristate off in dialog - radio button is set automatically 
	m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iTristateMode = TRISTATE_OFF;  
	
	// Set tristate off in hardware
	me8100DIOSetTristateOFF(m_iCurrentBoardIndex, m_iCurrentRegisterSet);
}

void CME8100DemoDlg::OnRadioTristateOn() 
{
	if(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iTristateMode == TRISTATE_ON)
	{
		// Nothing to do, tristate already on

		return;
	}
	
	// Set tristate on in dialog - radio button is set automatically 
	m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iTristateMode = TRISTATE_ON;  
	
	// Set tristate off in hardware
	me8100DIOSetTristateON(m_iCurrentBoardIndex, m_iCurrentRegisterSet);
}

void CME8100DemoDlg::OnClose() 
{
	// Disable interrupt on current board
	OnRadioDisableInt();
	
	// Deny access to irq functions
	m_bDisplayed = FALSE;	// Access denied to irq-functions	
	
	// Reset registers for all boards
	for (int index_board = 0; index_board < 32; index_board++)
	{
		// call me8100PROMVersion simply to see if the board is there
		
		int i_version;			
		
		if( me8100PROMVersion(index_board, &i_version) )
		{
			ReinitialiseBoard(index_board);
		}
	}

	CDialog::OnClose();
}

void CME8100DemoDlg::OnSelChangeBoardCombo() 
{
	// Disable interrupt on outgoing board
	OnRadioDisableInt();
	
	// Get int status and count from outgoing board
	CWnd* p_wnd = GetDlgItem(IDC_INT_STATUS);

	p_wnd->GetWindowText(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_csStatus);

	p_wnd = GetDlgItem(IDC_INT_COUNT);

	p_wnd->GetWindowText(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_csIRQCount);
	
	// Find combo-box index of newly selected board
	int new_index = m_comboBoards.GetCurSel();
	
	// Set the new current board
	m_iCurrentBoardIndex = (int)m_comboBoards.GetItemData(new_index);

	// Star with register set A
	m_iCurrentRegisterSet = REGISTER_SET_A;
	
	// Reset all dialog elements to correspond to the current board.
	SetDialogElements();
}

void CME8100DemoDlg::OnButtonChangeRegisterSet() 
{
	// Disable interrupt on outgoing register
	OnRadioDisableInt();
	
	// Get int status and count from outgoing register
	CWnd* p_wnd = GetDlgItem(IDC_INT_STATUS);

	p_wnd->GetWindowText(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_csStatus);

	p_wnd = GetDlgItem(IDC_INT_COUNT);

	p_wnd->GetWindowText(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_csIRQCount);
	
	// Get a pointer to the button
	
	CWnd* p_btn = GetDlgItem(IDC_BUTTON_CHANGE_REGISTER_SET);	
	
	// Get a pointer to the register set group box
	
	CWnd* p_grp_box = GetDlgItem(IDC_GROUP_BOX_REGISTER_SET);	
	
	if(m_iCurrentRegisterSet == REGISTER_SET_A)
	{
		// Change the register set
		m_iCurrentRegisterSet = REGISTER_SET_B;
	
		// Set the button text
		p_btn->SetWindowText("Register Set &A");
	
		// Set the group box text
		p_grp_box->SetWindowText("Register set B");
	}
	else // if(m_iCurrentRegisterSet == REGISTER_SET_B)
	{
		// Change the register set
		m_iCurrentRegisterSet = REGISTER_SET_A;
	
		// Set the button text
		p_btn->SetWindowText("Register Set &B");
	
		// Set the group box text
		p_grp_box->SetWindowText("Register set A");
	}

	// Update dialog elements to correspond to the current register set
	SetDialogElements();
}

void CME8100DemoDlg::OnButtonGetBit() 
{
	// Get the chosen bit number	
	int i_bit_no = m_comboGetBitNumber.GetCurSel();
	
	int i_value;
	
	// Get the bit value
	me8100DIGetBit(m_iCurrentBoardIndex, m_iCurrentRegisterSet, i_bit_no, &i_value);

	if(i_value == 0)
	{
		// Bit value 0, uncheck the check box
		CheckDlgButton(IDC_CHECK_GET_BIT_VALUE, 0);
	}
	else
	{
		// Bit value 1, check the check box
		CheckDlgButton(IDC_CHECK_GET_BIT_VALUE, 1);
	}
}

void CME8100DemoDlg::OnButtonSetBit() 
{
	// Get the chosen bit number	
	int i_bit_no = m_comboSetBitNumber.GetCurSel();
	
	// Get the bit value
	int i_value;
	
	if( IsDlgButtonChecked(IDC_CHECK_SET_BIT_VALUE) )
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
	me8100DOSetBit(m_iCurrentBoardIndex, m_iCurrentRegisterSet, i_bit_no, i_value);
}

void CME8100DemoDlg::OnButtonReadCounter() 
{
	// Get the chosen counter number.	
	int i_counter_no = m_comboCounterNumber.GetCurSel();
	
	// Read the counter value.
	int i_value;
	
	me8100CntRead(m_iCurrentBoardIndex, i_counter_no, &i_value);

	// Set the edit box.
	char buffer[24];
	
	sprintf(buffer, "%u", (unsigned short)i_value);

	GetDlgItem(IDC_EDIT_COUNTER_VALUE)->SetWindowText(buffer);
}

void CME8100DemoDlg::OnButtonWriteCounter() 
{
	// Get the chosen bit number.	
	int i_counter_no = m_comboCounterNumber.GetCurSel();
	
	// Get the chosen mode	
	int i_mode = m_comboCounterMode.GetCurSel();
	
	// Get the required value from the edit box.
	int i_value;
	
	CString cs_value;
	
	GetDlgItem(IDC_EDIT_COUNTER_VALUE)->GetWindowText(cs_value);

	if( sscanf(cs_value, "%d", &i_value) != 1)
	{
		i_value = 0;
	}

	// Write the counter value.
	me8100CntWrite(m_iCurrentBoardIndex, i_counter_no, i_mode, i_value);
}

void CME8100DemoDlg::ReinitialiseBoard(int board_index)
{
	// Disable int in hardware
	me8100DisableInt(board_index, REGISTER_SET_A);
	me8100DisableInt(board_index, REGISTER_SET_B);

	// Set interrupt mode to interrupt on pattern compare in hardware
	me8100DIOSetIntMode(board_index, REGISTER_SET_A, INTERRUPT_ON_PATTERN_COMPARE);
	me8100DIOSetIntMode(board_index, REGISTER_SET_B, INTERRUPT_ON_PATTERN_COMPARE);

	// Set tristate on in hardware
	me8100DIOSetTristateON(board_index, REGISTER_SET_A);
	me8100DIOSetTristateON(board_index, REGISTER_SET_B);
	
	// Set sink mode in hardware
	me8100SetSinkSourceMode(board_index, REGISTER_SET_A, SINK_MODE);
	me8100SetSinkSourceMode(board_index, REGISTER_SET_B, SINK_MODE);
	
	// Now clear pattern and mask
	
	// Clear the pattern in hardware
	 me8100DIOSetPattern(board_index, REGISTER_SET_A, 0);
	 me8100DIOSetPattern(board_index, REGISTER_SET_B, 0);

	// Clear the mask in hardware
	 me8100DIOSetMask(board_index, REGISTER_SET_A, 0);
	 me8100DIOSetMask(board_index, REGISTER_SET_B, 0);
}

void CME8100DemoDlg::SetDialogElements(void)
{
	// First get the device info.

	// Temporary structure for the information
	DEVICEINFOSTRUCT dev_info_struct;

	// Set all structure components to zero
	memset( (void *)&dev_info_struct, 0, sizeof(dev_info_struct) ); 

	// And fetch the information with an me1800 call
	me8100GetDevInfo(m_iCurrentBoardIndex, &dev_info_struct);

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


	m_comboSetBitNumber.SetCurSel(0);

	m_comboGetBitNumber.SetCurSel(0);
	
	m_comboCounterNumber.SetCurSel(0);
	
	m_comboCounterMode.SetCurSel(0);

	// Set Pattern in dialog
	DlgSetPattern();
	
	// Set Mask in dialog
	DlgSetMask();
	
	// Set interrupt to disabled in dialog
	CheckRadioButton(IDC_RADIO_DISABLE_INT, IDC_RADIO_ENABLE_INT, IDC_RADIO_DISABLE_INT);

	// Enable radio buttons	for setting the int modus
	GetDlgItem(IDC_RADIO_INT_PATTERN_COMPARE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_INT_BIT_CHANGE)->EnableWindow(TRUE);
		
	// Set int mode appropriately in dialog
	int i_int_mode  = m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iIntMode;

	int set_radio_button = 
			(i_int_mode == INTERRUPT_ON_PATTERN_COMPARE) ? IDC_RADIO_INT_PATTERN_COMPARE : IDC_RADIO_INT_BIT_CHANGE; 
	
	CheckRadioButton(IDC_RADIO_INT_PATTERN_COMPARE, IDC_RADIO_INT_BIT_CHANGE, set_radio_button);
	
	// Set tristate mode appropriately in dialog
	int i_tristate_mode  = m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iTristateMode;

	set_radio_button = 
			(i_tristate_mode == TRISTATE_OFF) ? IDC_RADIO_TRISTATE_OFF : IDC_RADIO_TRISTATE_ON; 
	
	CheckRadioButton(IDC_RADIO_TRISTATE_OFF, IDC_RADIO_TRISTATE_ON, set_radio_button);
	
	// Set sink or source  appropriately in dialog
	int i_sink_or_source  = m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_iSinkOrSource;

	set_radio_button = 
			(i_sink_or_source == SINK_MODE) ? IDC_RADIO_SINK : IDC_RADIO_SOURCE; 
	
	CheckRadioButton(IDC_RADIO_SINK, IDC_RADIO_SOURCE, set_radio_button);
	
	// Get a pointer to the button for changing the register set
	CWnd* p_btn = GetDlgItem(IDC_BUTTON_CHANGE_REGISTER_SET);	

	if(dev_info_struct.dwDeviceID == 0x810B)
	{
		// Double register set - Enable button to change registers set
		p_btn->EnableWindow(TRUE);	
	}
	else
	{
		// Single register set - Disable button to change registers set
		p_btn->EnableWindow(FALSE);	
	}

	// Set int status and count
	p_wnd = GetDlgItem(IDC_INT_STATUS);

	p_wnd->SetWindowText(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_csStatus);

	p_wnd = GetDlgItem(IDC_INT_COUNT);

	p_wnd->SetWindowText(m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_csIRQCount);
}



void CME8100DemoDlg::DlgSetDigitalInput(unsigned short w_set)
{
	// Check the appropriate check box if the last bit of w_set is 1
	// Otherwise leave the check box unchecked
	CheckDlgButton(IDC_INPUT_BIT_0, w_set&0x0001);

	// Shift w_set left to handle the next bit
	w_set>>= 1;

	// Continue in this way with each bit of w_set and the appropriate check box
	
	CheckDlgButton(IDC_INPUT_BIT_1, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_2, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_3, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_4, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_5, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_6, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_7, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_8, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_9, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_10, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_11, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_12, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_13, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_14, w_set&0x0001);

	w_set>>= 1;

	CheckDlgButton(IDC_INPUT_BIT_15, w_set&0x0001);
}

unsigned short CME8100DemoDlg::DlgGetDigitalOutput(void)
{
	// Initialise the return value 
	unsigned short us_result = 0;
	
	// Initialise a bit mask
	unsigned short us_mask = 0x0001;
	
	// If the check box corresponding to the first bit is checked, then set
	// the first bit in our result
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_0) )
	{
		us_result|= us_mask;
	}

	// Shift the mask to handle the next bit
	us_mask<<= 1;

	// Continue in this way for each check box and the appropriate bit of our result
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_1) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_2) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_3) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_4) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_5) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_6) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_7) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_8) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_9) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_10) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_11) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_12) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_13) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_14) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_OUTPUT_BIT_15) )
	{
		us_result|= us_mask;
	}

	return(us_result);
}

void CME8100DemoDlg::DlgClearDigitalOutput(void)
{
	// Uncheck each check box
	
	CheckDlgButton(IDC_OUTPUT_BIT_0, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_1, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_2, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_3, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_4, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_5, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_6, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_7, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_8, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_9, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_10, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_11, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_12, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_13, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_14, 0);
	CheckDlgButton(IDC_OUTPUT_BIT_15, 0);
}

unsigned short CME8100DemoDlg::DlgGetPattern(void)
{
	// This function is similar to DlgGetDigitalOutputA above
	
	// Initialise the return value 
	unsigned short us_result = 0;
	
	// Initialise a bit mask
	unsigned short us_mask = 0x0001;
	
	// If the check box corresponding to the first bit is checked, then set
	// the first bit in our result
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_0) )
	{
		us_result|= us_mask;
	}

	// Shift the mask to handle the next bit
	us_mask<<= 1;

	// Continue in this way for each check box and the appropriate bit of our result
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_1) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_2) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_3) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_4) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_5) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_6) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_7) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_8) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_9) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_10) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_11) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_12) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_13) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_14) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_PATTERN_BIT_15) )
	{
		us_result|= us_mask;
	}

	return(us_result);
}

void CME8100DemoDlg::DlgSetPattern(void)
{
	// Find the pattern which should be set.
	
	WORD pattern = m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_wPattern;
	
	// Check the appropriate check box if the last bit of pattern is 1
	// Otherwise leave the check box unchecked
	CheckDlgButton(IDC_PATTERN_BIT_0, pattern&0x0001);

	// Shift pattern left to handle the next bit
	pattern>>= 1;

	// Continue in this way with each bit of pattern and the appropriate check box
	
	CheckDlgButton(IDC_PATTERN_BIT_1, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_2, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_3, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_4, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_5, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_6, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_7, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_8, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_9, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_10, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_11, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_12, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_13, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_14, pattern&0x0001);

	pattern>>= 1;

	CheckDlgButton(IDC_PATTERN_BIT_15, pattern&0x0001);
}
	
unsigned short CME8100DemoDlg::DlgGetMask(void)
{
	// This function is similar to DlgGetDigitalOutputA above
	
	// Initialise the return value 
	unsigned short us_result = 0;
	
	// Initialise a bit mask
	unsigned short us_mask = 0x0001;
	
	// If the check box corresponding to the first bit is checked, then set
	// the first bit in our result
	if( IsDlgButtonChecked(IDC_MASK_BIT_0) )
	{
		us_result|= us_mask;
	}

	// Shift the mask to handle the next bit
	us_mask<<= 1;

	// Continue in this way for each check box and the appropriate bit of our result
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_1) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_2) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_3) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_4) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_5) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_6) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_7) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_8) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_9) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_10) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_11) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_12) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_13) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_14) )
	{
		us_result|= us_mask;
	}

	us_mask<<= 1;
	
	if( IsDlgButtonChecked(IDC_MASK_BIT_15) )
	{
		us_result|= us_mask;
	}

	return(us_result);
}

void CME8100DemoDlg::DlgSetMask(void)
{
	// Find the pattern which should be set.
	
	WORD mask = m_arrayBoardSettings[m_iCurrentBoardIndex][m_iCurrentRegisterSet].m_wMask;
	
	// Check the appropriate check box if the last bit of pattern is 1
	// Otherwise leave the check box unchecked
	CheckDlgButton(IDC_MASK_BIT_0, mask&0x0001);

	// Shift pattern left to handle the next bit
	mask>>= 1;

	// Continue in this way with each bit of mask and the appropriate check box
	
	CheckDlgButton(IDC_MASK_BIT_1, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_2, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_3, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_4, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_5, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_6, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_7, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_8, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_9, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_10, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_11, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_12, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_13, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_14, mask&0x0001);

	mask>>= 1;

	CheckDlgButton(IDC_MASK_BIT_15, mask&0x0001);
}


