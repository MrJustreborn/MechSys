// ME1000TestView.cpp : Implementierung der Klasse CME1000TestView
//

#include "stdafx.h"
#include "ME1000Test.h"

#include "ME1000TestDoc.h"
#include "ME1000TestView.h"
#include "ME1000TestEx.h"
#include "ErrorDialog.h"

#include "..\DLLInit.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CME1000TestView

IMPLEMENT_DYNCREATE(CME1000TestView, CFormView)

BEGIN_MESSAGE_MAP(CME1000TestView, CFormView)
	//{{AFX_MSG_MAP(CME1000TestView)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_INFO, OnButtonDeviceInfo)
	ON_CBN_SELCHANGE(IDC_COMBO_BOARD_NUMBER, OnSelchangeComboBoardNumber)
	ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, OnButtonWrite)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNCTION_SELECT, OnSelchangeComboFunctionSelect)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CME1000TestView Konstruktion/Destruktion

CME1000TestView::CME1000TestView()
	: CFormView(CME1000TestView::IDD)
{
	//{{AFX_DATA_INIT(CME1000TestView)
		// HINWEIS: Der Klassenassistent fügt hier Member-Initialisierung ein
	//}}AFX_DATA_INIT
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

	meOpen();

}

CME1000TestView::~CME1000TestView()
{
	meClose();
}

void CME1000TestView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CME1000TestView)
		// HINWEIS: Der Klassenassistent fügt an dieser Stelle DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}

BOOL CME1000TestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CFormView::PreCreateWindow(cs);
}

void CME1000TestView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

//  The following code displays the initial Board information

	int iBoardNumber;
	int iVersion;
	int iErrorCode;
	int iDriverVersion ;
	int iBoardFound = FALSE;

	// String variables to format output of items 
	CString BoardVersion;
	CString DLLVersion;
	CString InitValue;
	CString DisplayValue;
	CWnd* p_wnd;

	DEVICEINFOSTRUCT pDevInfo;

	DWORD   dwBoardNumber;          // Board number of Board
    DWORD   dwVendorID;             // PCI vendor ID
    DWORD   dwDeviceID;             // PCI device ID
    DWORD   dwSystemSlotNumber;     // Slot number in PCI bus
    DWORD   dwPortBase;             // base port address
    DWORD   dwPortCount;            // Count of I/O addresses used.
//  DWORD   dwIntChannel;           // first Interrupt Channel
    DWORD   dwPortBasePLX;			// base port address
    DWORD   dwPortCountPLX;			// Count of I/O addresses used.
    DWORD   dwSerialNumber;         // Serial number of the board
    DWORD   dwBusNumber;            // Bus number of the PCI bus (in most cases 0)
    DWORD   dwHWRevision;           // hardware revision of board
//  DWORD   dwIrqCnt;               // number of interrupts 
    DWORD   dwVersion;              // which board of the board family


	// Check for a valid board
	iErrorCode = me1000GetBoardVersion (8, &iVersion);
	if (iErrorCode == 1) // valid board found
	{
		iBoardFound = TRUE;
		iBoardNumber = 8;
		// set the Board Number combo box to board 8
		CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
		p_Combo->SetCurSel(iBoardNumber);
	}

	iErrorCode = me1000GetBoardVersion (7, &iVersion);
	if (iErrorCode == 1) // valid board found
	{
		iBoardFound = TRUE;
		iBoardNumber = 7;
		// set the Board Number combo box to board 7
		CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
		p_Combo->SetCurSel(iBoardNumber);
	}

	iErrorCode = me1000GetBoardVersion (6, &iVersion);
	if (iErrorCode == 1) // valid board found
	{
		iBoardFound = TRUE;
		iBoardNumber = 6;
		// set the Board Number combo box to board 6
		CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
		p_Combo->SetCurSel(iBoardNumber);
	}

	iErrorCode = me1000GetBoardVersion (5, &iVersion);
	if (iErrorCode == 1) // valid board found
	{
		iBoardFound = TRUE;
		iBoardNumber = 5;
		// set the Board Number combo box to board 5
		CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
		p_Combo->SetCurSel(iBoardNumber);
	}
	
	iErrorCode = me1000GetBoardVersion (4, &iVersion);
	if (iErrorCode == 1) // valid board found
	{
		iBoardFound = TRUE;
		iBoardNumber = 4;
		// set the Board Number combo box to board 4
		CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
		p_Combo->SetCurSel(iBoardNumber);
	}

	iErrorCode = me1000GetBoardVersion (3, &iVersion);
	if (iErrorCode == 1) // valid board found
	{
		iBoardFound = TRUE;
		iBoardNumber = 3;
		// set the Board Number combo box to board 3
		CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
		p_Combo->SetCurSel(iBoardNumber);
	}

	iErrorCode = me1000GetBoardVersion (2, &iVersion);
	if (iErrorCode == 1) // valid board found
	{
		iBoardFound = TRUE;
		iBoardNumber = 2;
		// set the Board Number combo box to board 2
		CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
		p_Combo->SetCurSel(iBoardNumber);
	}

	iErrorCode = me1000GetBoardVersion (1, &iVersion);
	if (iErrorCode == 1) // valid board found
	{
		iBoardFound = TRUE;
		iBoardNumber = 1;
		// set the Board Number combo box to board 1
		CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
		p_Combo->SetCurSel(iBoardNumber);
	}
	
	iErrorCode = me1000GetBoardVersion (0, &iVersion);
	if (iErrorCode == 1) // valid board found
	{
		iBoardFound = TRUE;
		iBoardNumber = 0;
		// set the Board Number combo box to board 0
		CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
		p_Combo->SetCurSel(iBoardNumber);
	}

	if (iBoardFound == FALSE)	
	{
		// no valid board has been found so display a message 
		// and end the program
		AfxMessageBox(" No board found\nor DLL not installed!\n\nProgram cancelled",
				MB_OK|MB_ICONSTOP, 0);
		abort ();
	}
		
	// Format string 
	BoardVersion.Format("%4X", iVersion);

	// Board Version text to be set
	p_wnd = GetDlgItem(IDC_STATIC_BOARD_VERSION);

	// display the board version in the text window
	p_wnd->SetWindowText (BoardVersion);

	// return value for this function is the DLL Version
	iErrorCode = me1000GetDLLVersion ();

	// Format string 
	DLLVersion.Format("%4X", iErrorCode);

	// DLL Version text to be set
	p_wnd = GetDlgItem(IDC_STATIC_DLLVERSION);

	// display text
	p_wnd->SetWindowText (DLLVersion);

	iErrorCode = me1000GetDriverVersion (&iDriverVersion);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000GetDriverVersion";
		aErrorDialog.DoModal();		
	}

	// display the Driver version read in
	CEdit* p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_DRIVER_VERSION));
	DisplayValue.Format("%4X", iDriverVersion);
	p_Edit->SetWindowText(DisplayValue);

	//  set all of the selection boxes to the first list items
	//  as a starting point. 

	// set the function select combo box to first list item: bit functions
	CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FUNCTION_SELECT));
	p_Combo->SetCurSel(0);

	// set the bit number combo box to first list item: bit 0
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_NUMBER));
	p_Combo->SetCurSel(0);

	// set the bit port number combo box to first list item: port A
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_PORT_NUMBER));
	p_Combo->SetCurSel(0);

	// set the Byte number combo box to first list item: byte 1
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_NUMBER));
	p_Combo->SetCurSel(0);

	// set the byte port combo box to first list item: port A
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_PORT_NUMBER));
	p_Combo->SetCurSel(0);

	// set the Word combo box to first list item: Low word
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_NUMBER));
	p_Combo->SetCurSel(0);

	// set the word port combo box to first list item: port A
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_PORT_NUMBER));
	p_Combo->SetCurSel(0);

	// set the long port combo box to first list item: port A
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_LONG_PORT_NUMBER));
	p_Combo->SetCurSel(0);

/*	The following section of code retrieves internal device 
	information from the board via a data structure and 
	displays this informaion in the user screen
*/
	// Get the device information
	iErrorCode = me1000GetDevInfo (iBoardNumber, &pDevInfo);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000GetDevInfo";
		aErrorDialog.DoModal();				
	}

	// get the information from the structure
	dwBoardNumber = pDevInfo.dwBoardNumber;
    dwVendorID = pDevInfo.dwVendorID;           
    dwDeviceID = pDevInfo.dwDeviceID;           
    dwSystemSlotNumber = pDevInfo.dwSystemSlotNumber;    
    dwPortBase = pDevInfo.dwPortBase;            
    dwPortCount = pDevInfo.dwPortCount;           
//  dwIntChannel= pDevInfo.dwIntChannel;          
    dwPortBasePLX = pDevInfo.dwPortBasePLX;		
    dwPortCountPLX = pDevInfo.dwPortCountPLX;		
    dwSerialNumber = pDevInfo.dwSerialNumber;     
    dwBusNumber = pDevInfo.dwBusNumber;        
    dwHWRevision = pDevInfo.dwHWRevision;       
//  dwIrqCnt = pDevInfo.dwIrqCnt;           
    dwVersion = pDevInfo.dwVersion;        

	// Display the board number
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_BOARD_NUMBER));
	DisplayValue.Format("%4X", dwBoardNumber);
	p_Edit->SetWindowText(DisplayValue);

	// display the vendor ID 
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_VENDOR_ID));
	DisplayValue.Format("%4X", dwVendorID);
	p_Edit->SetWindowText(DisplayValue);

	// display the device ID 
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_DEVICE_ID));
	DisplayValue.Format("%4X", dwDeviceID);
	p_Edit->SetWindowText(DisplayValue);

	// display the system slot number
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_SLOT_NUMBER));
	DisplayValue.Format("%4X", dwSystemSlotNumber);
	p_Edit->SetWindowText(DisplayValue);

	// display the port base address
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_PORT_BASE));
	DisplayValue.Format("%4X", dwPortBase);
	p_Edit->SetWindowText(DisplayValue);

	// display the port count
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_PORT_COUNT));
	DisplayValue.Format("%4d", dwPortCount);
	p_Edit->SetWindowText(DisplayValue);

	// display the interrupt channel
//	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_INTERRUPT_CHANNEL));
//	DisplayValue.Format("%4X", dwIntChannel);
//	p_Edit->SetWindowText(DisplayValue);

	// display the PLX Port base address
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_PORT_BASE_PLX));
	DisplayValue.Format("%4X", dwPortBasePLX);
	p_Edit->SetWindowText(DisplayValue);

	// display the PLX Count
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_PORT_COUNT_PLX));
	DisplayValue.Format("%4X", dwPortCountPLX);
	p_Edit->SetWindowText(DisplayValue);

	// display the serial number
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_SERIAL_NUMBER));
	DisplayValue.Format("%8X", dwSerialNumber);
	p_Edit->SetWindowText(DisplayValue);

	// display the bus number
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_BUS_NUMBER));
	DisplayValue.Format("%4X", dwBusNumber);
	p_Edit->SetWindowText(DisplayValue);

	// display the hardware revision
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_HARDWARE_REVISION));
	DisplayValue.Format("%4X", dwHWRevision);
	p_Edit->SetWindowText(DisplayValue);

	// display the interrupt count
//	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_INTERRUPT_COUNT));
//	DisplayValue.Format("%4X", dwIrqCnt);
//	p_Edit->SetWindowText(DisplayValue);

	// display the board version
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_VERSION));
	DisplayValue.Format("%4X", dwVersion);
	p_Edit->SetWindowText(DisplayValue);
}

/////////////////////////////////////////////////////////////////////////////
// CME1000TestView Diagnose

#ifdef _DEBUG
void CME1000TestView::AssertValid() const
{
	CFormView::AssertValid();
}

void CME1000TestView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CME1000TestDoc* CME1000TestView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CME1000TestDoc)));
	return (CME1000TestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CME1000TestView Nachrichten-Handler

void CME1000TestView::OnButtonDeviceInfo() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}

void CME1000TestView::OnSelchangeComboBoardNumber() 
{
	//  The following code displays the initial Board information

	int iBoardNumber;
	int iVersion;
	int iErrorCode;
	int iBoardFound = FALSE;

	// String variables to format output of items 
	CString BoardVersion;
	CString DLLVersion;
	CString InitValue;
	CString DisplayValue;
	CWnd* p_wnd;

	DEVICEINFOSTRUCT pDevInfo;

	DWORD   dwBoardNumber;          // Board number of Board
    DWORD   dwVendorID;             // PCI vendor ID
    DWORD   dwDeviceID;             // PCI device ID
    DWORD   dwSystemSlotNumber;     // Slot number in PCI bus
    DWORD   dwPortBase;             // base port address
    DWORD   dwPortCount;            // Count of I/O addresses used.
//  DWORD   dwIntChannel;           // first Interrupt Channel
    DWORD   dwPortBasePLX;			// base port address
    DWORD   dwPortCountPLX;			// Count of I/O addresses used.
    DWORD   dwSerialNumber;         // Serial number of the board
    DWORD   dwBusNumber;            // Bus number of the PCI bus (in most cases 0)
    DWORD   dwHWRevision;           // hardware revision of board
//  DWORD   dwIrqCnt;               // number of interrupts 
    DWORD   dwVersion;              // which board of the board family

	// get the selected board number
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
	iBoardNumber = p_Combo->GetCurSel();

	// check if the selected board is found
	iErrorCode = me1000GetBoardVersion (iBoardNumber, &iVersion);
	if (iErrorCode == 0)
	{
		AfxMessageBox("No ME1000 Found ! \n\nUsing first board", 
											MB_OK|MB_ICONSTOP, 0);
		// Check for a valid board
		iErrorCode = me1000GetBoardVersion (8, &iVersion);
		if (iErrorCode == 1) // valid board found
		{
			iBoardFound = TRUE;
			iBoardNumber = 8;
			// set the Board Number combo box to board 8
			CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
			p_Combo->SetCurSel(iBoardNumber);
		}

		iErrorCode = me1000GetBoardVersion (7, &iVersion);
		if (iErrorCode == 1) // valid board found
		{
			iBoardFound = TRUE;
			iBoardNumber = 7;
			// set the Board Number combo box to board 7
			CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
			p_Combo->SetCurSel(iBoardNumber);
		}

		iErrorCode = me1000GetBoardVersion (6, &iVersion);
		if (iErrorCode == 1) // valid board found
		{
			iBoardFound = TRUE;
			iBoardNumber = 6;
			// set the Board Number combo box to board 6
			CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
			p_Combo->SetCurSel(iBoardNumber);
		}

		iErrorCode = me1000GetBoardVersion (5, &iVersion);
		if (iErrorCode == 1) // valid board found
		{
			iBoardFound = TRUE;
			iBoardNumber = 5;
			// set the Board Number combo box to board 5
			CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
			p_Combo->SetCurSel(iBoardNumber);
		}
	
		iErrorCode = me1000GetBoardVersion (4, &iVersion);
		if (iErrorCode == 1) // valid board found
			{
			iBoardFound = TRUE;
			iBoardNumber = 4;
			// set the Board Number combo box to board 4
			CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
			p_Combo->SetCurSel(iBoardNumber);
		}

		iErrorCode = me1000GetBoardVersion (3, &iVersion);
		if (iErrorCode == 1) // valid board found
		{
			iBoardFound = TRUE;
			iBoardNumber = 3;
			// set the Board Number combo box to board 3
			CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
			p_Combo->SetCurSel(iBoardNumber);
		}

		iErrorCode = me1000GetBoardVersion (2, &iVersion);
		if (iErrorCode == 1) // valid board found
		{
			iBoardFound = TRUE;
			iBoardNumber = 2;
			// set the Board Number combo box to board 2
			CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
			p_Combo->SetCurSel(iBoardNumber);
		}

		iErrorCode = me1000GetBoardVersion (1, &iVersion);
		if (iErrorCode == 1) // valid board found
		{
			iBoardFound = TRUE;
			iBoardNumber = 1;
			// set the Board Number combo box to board 1
			CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
			p_Combo->SetCurSel(iBoardNumber);
		}
		
		iErrorCode = me1000GetBoardVersion (0, &iVersion);
		if (iErrorCode == 1) // valid board found
		{
			iBoardFound = TRUE;
			iBoardNumber = 0;
			// set the Board Number combo box to board 0
			CComboBox* p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
			p_Combo->SetCurSel(iBoardNumber);
		}

		if (iBoardFound == FALSE)	
		{
			// no valid board has been found so display a message 
			// and end the program
			AfxMessageBox(" No board found\nor DLL not installed!\n\nProgram cancelled",
					MB_OK|MB_ICONSTOP, 0);
			abort ();
		}
	}
	
	iErrorCode = me1000GetBoardVersion (iBoardNumber, &iVersion);

	// Format string 
	BoardVersion.Format("%4X", iVersion);

	// PROM Version text to be set
	p_wnd = GetDlgItem(IDC_STATIC_BOARD_VERSION);

	// display the PROM version in the text window
	p_wnd->SetWindowText (BoardVersion);

	// return value for this function is the DLL Version
	iErrorCode = me1000GetDLLVersion ();

	// Format string 
	DLLVersion.Format("%4X", iErrorCode);

	// DLL Version text to be set
	p_wnd = GetDlgItem(IDC_STATIC_DLLVERSION);

	// display text
	p_wnd->SetWindowText (DLLVersion);

	//  set all of the selection boxes to the first list items
	//  as a starting point. 

	// set the Board Number combo box to the selected board
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
	p_Combo->SetCurSel(iBoardNumber);

	// set the function select combo box to first list item: bit functions
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FUNCTION_SELECT));
	p_Combo->SetCurSel(0);

	// set the bit number combo box to first list item: bit 0
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_NUMBER));
	p_Combo->SetCurSel(0);

	// set the bit port number combo box to first list item: port A
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_PORT_NUMBER));
	p_Combo->SetCurSel(0);

	// set the Byte number combo box to first list item: byte 1
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_NUMBER));
	p_Combo->SetCurSel(0);

	// set the byte port combo box to first list item: port A
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_PORT_NUMBER));
	p_Combo->SetCurSel(0);

	// set the Word combo box to first list item: Low word
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_NUMBER));
	p_Combo->SetCurSel(0);

	// set the word port combo box to first list item: port A
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_PORT_NUMBER));
	p_Combo->SetCurSel(0);

	// set the long port combo box to first list item: port A
	p_Combo = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_LONG_PORT_NUMBER));
	p_Combo->SetCurSel(0);

/*	The following section of code retrieves internal device 
	information from the board via a data structure and 
	displays this informaion in the user screen
*/
	// Get the device information
	iErrorCode = me1000GetDevInfo (iBoardNumber, &pDevInfo);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000GetDevInfo";
		aErrorDialog.DoModal();		
	}

	// get the information from the structure
	dwBoardNumber = pDevInfo.dwBoardNumber;
    dwVendorID = pDevInfo.dwVendorID;           
    dwDeviceID = pDevInfo.dwDeviceID;           
    dwSystemSlotNumber = pDevInfo.dwSystemSlotNumber;    
    dwPortBase = pDevInfo.dwPortBase;            
    dwPortCount = pDevInfo.dwPortCount;           
//  dwIntChannel= pDevInfo.dwIntChannel;          
    dwPortBasePLX = pDevInfo.dwPortBasePLX;		
    dwPortCountPLX = pDevInfo.dwPortCountPLX;		
    dwSerialNumber = pDevInfo.dwSerialNumber;     
    dwBusNumber = pDevInfo.dwBusNumber;        
    dwHWRevision = pDevInfo.dwHWRevision;       
//  dwIrqCnt = pDevInfo.dwIrqCnt;           
    dwVersion = pDevInfo.dwVersion;        

	// Display the board number
	CEdit* p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_BOARD_NUMBER));
	DisplayValue.Format("%4X", dwBoardNumber);
	p_Edit->SetWindowText(DisplayValue);

	// display the vendor ID 
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_VENDOR_ID));
	DisplayValue.Format("%4X", dwVendorID);
	p_Edit->SetWindowText(DisplayValue);

	// display the device ID 
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_DEVICE_ID));
	DisplayValue.Format("%4X", dwDeviceID);
	p_Edit->SetWindowText(DisplayValue);

	// display the system slot number
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_SLOT_NUMBER));
	DisplayValue.Format("%4X", dwSystemSlotNumber);
	p_Edit->SetWindowText(DisplayValue);

	// display the port base address
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_PORT_BASE));
	DisplayValue.Format("%4X", dwPortBase);
	p_Edit->SetWindowText(DisplayValue);

	// display the port count
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_PORT_COUNT));
	DisplayValue.Format("%4d", dwPortCount);
	p_Edit->SetWindowText(DisplayValue);

	// display the interrupt channel
//	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_INTERRUPT_CHANNEL));
//	DisplayValue.Format("%4X", dwIntChannel);
//	p_Edit->SetWindowText(DisplayValue);

	// display the PLX Port base address
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_PORT_BASE_PLX));
	DisplayValue.Format("%4X", dwPortBasePLX);
	p_Edit->SetWindowText(DisplayValue);

	// display the PLX Count
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_PORT_COUNT_PLX));
	DisplayValue.Format("%4X", dwPortCountPLX);
	p_Edit->SetWindowText(DisplayValue);

	// display the serial number
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_SERIAL_NUMBER));
	DisplayValue.Format("%8X", dwSerialNumber);
	p_Edit->SetWindowText(DisplayValue);

	// display the bus number
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_BUS_NUMBER));
	DisplayValue.Format("%4X", dwBusNumber);
	p_Edit->SetWindowText(DisplayValue);

	// display the hardware revision
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_HARDWARE_REVISION));
	DisplayValue.Format("%4X", dwHWRevision);
	p_Edit->SetWindowText(DisplayValue);

	// display the interrupt count
//	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_INTERRUPT_COUNT));
//	DisplayValue.Format("%4X", dwIrqCnt);
//	p_Edit->SetWindowText(DisplayValue);

	// display the board version
	p_Edit = static_cast<CEdit*>(GetDlgItem(IDC_STATIC_VERSION));
	DisplayValue.Format("%4X", dwVersion);
	p_Edit->SetWindowText(DisplayValue);
}

void CME1000TestView::OnButtonRead() 
{
	int iFunctionSetting;
		
	// get the current function setting (bit, byte, word, long)
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FUNCTION_SELECT));
	iFunctionSetting = p_Combo->GetCurSel();

	if (iFunctionSetting == BIT_FUNCTION) BitRead();
	if (iFunctionSetting == BYTE_FUNCTION) ByteRead();
	if (iFunctionSetting == WORD_FUNCTION) WordRead();
	if (iFunctionSetting == LONG_FUNCTION) LongRead();
}


void CME1000TestView::OnButtonWrite() 
{
	int iFunctionSetting;
	
	// get the current function setting (bit, byte, word, long)
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FUNCTION_SELECT));
	iFunctionSetting = p_Combo->GetCurSel();

	if (iFunctionSetting == BIT_FUNCTION) BitWrite();
	if (iFunctionSetting == BYTE_FUNCTION) ByteWrite();
	if (iFunctionSetting == WORD_FUNCTION) WordWrite();
	if (iFunctionSetting == LONG_FUNCTION) LongWrite();
}


void CME1000TestView::BitRead()
{
	int iBoardNumber;
	int iPortNumber;
	int iBitNo;
	int iErrorCode;
	int iBitValue;
	int iVersion;

	// get the current board number
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
	iBoardNumber = p_Combo->GetCurSel();

	// get the current port number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_PORT_NUMBER));
	iPortNumber = p_Combo->GetCurSel();

	// check the board version
	iErrorCode = me1000GetBoardVersion (iBoardNumber, &iVersion);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000GetBoardVersion";
		aErrorDialog.DoModal();		
	}

	// for board version 100A, ports C and D are not available
	if (iVersion == 0x100A)
	{
		if ((iPortNumber == PORTC) | (iPortNumber == PORTD))
		{
			// if the board version is 100A and port C or D is
			// selected, an error box is displayed and the 
			// function is not executed
			AfxMessageBox("Port C and D not available on ME1000A \n\n Choose port A or B", 
													MB_OK|MB_ICONSTOP, 0);
			return;
		}
	}

	// get the currrent bit number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_NUMBER));
	iBitNo = p_Combo->GetCurSel();

	// Set the port direction to input
	iErrorCode = me1000DIOSetPortDirection (iBoardNumber, iPortNumber, MEINPUT);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIOSetPortDirection";
		aErrorDialog.DoModal();		
	}

	iErrorCode = me1000DIGetBit (iBoardNumber, iPortNumber, iBitNo, &iBitValue);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIGetBit";
		aErrorDialog.DoModal();		
	}

	// set the state of the check box
	CButton* p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_CHECK_BIT_VALUE));
	if (iBitValue == 1)
	{
		// if a "1" is returned set the box state to checked
		p_CheckBox->SetCheck (CHECKED);
	}

	else
	{
		// if a "0" is returned set the box state to unchecked
		p_CheckBox->SetCheck (NOTCHECKED);
	}
}

void CME1000TestView::ByteRead()
{
	int iBoardNumber;
	int iPortNumber;
	int iByteNo;
	int iErrorCode;
	int iByteValue;
	int iVersion;
	int B0, B1, B2, B3, B4, B5, B6, B7;

	
	// get the current board number
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
	iBoardNumber = p_Combo->GetCurSel();

	// get the current port number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_PORT_NUMBER));
	iPortNumber = p_Combo->GetCurSel();

	// check the board version
	iErrorCode = me1000GetBoardVersion (iBoardNumber, &iVersion);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000GetBoardVersion";
		aErrorDialog.DoModal();		
	}

	// for board version 100A, ports C and D are not available
	if (iVersion == 0x100A)
	{
		if ((iPortNumber == PORTC) | (iPortNumber == PORTD))
		{
			// if the board version is 100A and port C or D is
			// selected, an error box is displayed and the 
			// function is not executed
			AfxMessageBox("Port C and D not available on ME1000A \n\n Choose port A or B", 
													MB_OK|MB_ICONSTOP, 0);
			return;
		}
	}

	// get the currrent byte number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_NUMBER));
	iByteNo = p_Combo->GetCurSel();

	// Set the port direction to input
	iErrorCode = me1000DIOSetPortDirection (iBoardNumber, iPortNumber, MEINPUT);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIOSetPortDirection";
		aErrorDialog.DoModal();		
	}

	iErrorCode = me1000DIGetByte (iBoardNumber, iPortNumber, iByteNo, &iByteValue);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIGetByte";
		aErrorDialog.DoModal();		
	}

	// Determine the state of the bit display boxes from the word value read in
	CButton* p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_0));
	B0 = (iByteValue & NUM_BIT_00) >> 0;
    if (B0 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_1));
	B1 = (iByteValue & NUM_BIT_01) >> 1;
    if (B1 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_2));
    B2 = (iByteValue & NUM_BIT_02) >> 2;
    if (B2 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_3));
    B3 = (iByteValue & NUM_BIT_03) >> 3;
    if (B3 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_4));
    B4 = (iByteValue & NUM_BIT_04) >> 4;
    if (B4 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_5));
    B5 = (iByteValue & NUM_BIT_05) >> 5;
    if (B5 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_6));
    B6 = (iByteValue & NUM_BIT_06) >> 6;
    if (B6 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_7));
    B7 = (iByteValue & NUM_BIT_07) >> 7;
    if (B7 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

}

void CME1000TestView::WordRead()
{
	int iBoardNumber;
	int iPortNumber;
	int iWordNo;
	int iErrorCode;
	int iWordValue;
	int iVersion;
	int B0, B1, B2, B3, B4, B5, B6, B7,
		B8, B9, B10, B11, B12, B13, B14, B15;

	// get the current board number
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
	iBoardNumber = p_Combo->GetCurSel();

	// get the current port number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_PORT_NUMBER));
	iPortNumber = p_Combo->GetCurSel();

	// check the board version
	iErrorCode = me1000GetBoardVersion (iBoardNumber, &iVersion);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000GetBoardVersion";
		aErrorDialog.DoModal();		
	}

	// for board version 100A, ports C and D are not available
	if (iVersion == 0x100A)
	{
		if ((iPortNumber == PORTC) | (iPortNumber == PORTD))
		{
			// if the board version is 100A and port C or D is
			// selected, an error box is displayed and the 
			// function is not executed
			AfxMessageBox("Port C and D not available on ME1000A \n\n Choose port A or B", 
													MB_OK|MB_ICONSTOP, 0);
			return;
		}
	}

	// get the currrent word number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_NUMBER));
	iWordNo = p_Combo->GetCurSel();

	// Set the port direction to input
	iErrorCode = me1000DIOSetPortDirection (iBoardNumber, iPortNumber, MEINPUT);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIOSetPortDirection";
		aErrorDialog.DoModal();	
	}

	iErrorCode = me1000DIGetWord (iBoardNumber, iPortNumber, iWordNo, &iWordValue);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DOGetWord";
		aErrorDialog.DoModal();		
	}

	// Determine the state of the bit display boxes from the word value read in
	CButton* p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_0));
	B0 = (iWordValue & NUM_BIT_00) >> 0;
    if (B0 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_1));
	B1 = (iWordValue & NUM_BIT_01) >> 1;
    if (B1 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_2));
    B2 = (iWordValue & NUM_BIT_02) >> 2;
    if (B2 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_3));
    B3 = (iWordValue & NUM_BIT_03) >> 3;
    if (B3 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_4));
    B4 = (iWordValue & NUM_BIT_04) >> 4;
    if (B4 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_5));
    B5 = (iWordValue & NUM_BIT_05) >> 5;
    if (B5 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_6));
    B6 = (iWordValue & NUM_BIT_06) >> 6;
    if (B6 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_7));
    B7 = (iWordValue & NUM_BIT_07) >> 7;
    if (B7 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_8));
	B8 = (iWordValue & NUM_BIT_08) >> 8;
    if (B8 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_9));
	B9 = (iWordValue & NUM_BIT_09) >> 9;
    if (B9 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_10));
    B10 = (iWordValue & NUM_BIT_10) >> 10;
    if (B10 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_11));
    B11 = (iWordValue & NUM_BIT_11) >> 11;
    if (B11 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_12));
    B12 = (iWordValue & NUM_BIT_12) >> 12;
    if (B12 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_13));
    B13 = (iWordValue & NUM_BIT_13) >> 13;
    if (B13 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_14));
    B14 = (iWordValue & NUM_BIT_14) >> 14;
    if (B14 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_15));
    B15 = (iWordValue & NUM_BIT_15) >> 15;
    if (B15 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);
}

void CME1000TestView::LongRead()
{
	int iBoardNumber;
	int iPortNumber;
	int iErrorCode;
	int iLongValue;
	int iVersion;
	int B0, B1, B2, B3, B4, B5, B6, B7,
		B8, B9, B10, B11, B12, B13, B14, B15,
		B16, B17, B18, B19, B20, B21, B22, B23,
		B24, B25, B26, B27, B28, B29, B30, B31 ;

	// get the current board number
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
	iBoardNumber = p_Combo->GetCurSel();

	// get the current port number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_LONG_PORT_NUMBER));
	iPortNumber = p_Combo->GetCurSel();

	// check the board version
	iErrorCode = me1000GetBoardVersion (iBoardNumber, &iVersion);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000GetBoardVersion";
		aErrorDialog.DoModal();		
	}

	// for board version 100A, ports C and D are not available
	if (iVersion == 0x100A)
	{
		if ((iPortNumber == PORTC) | (iPortNumber == PORTD))
		{
			// if the board version is 100A and port C or D is
			// selected, an error box is displayed and the 
			// function is not executed
			AfxMessageBox("Port C and D not available on ME1000A \n\n Choose port A or B", 
													MB_OK|MB_ICONSTOP, 0);
			return;
		}
	}

	// Set the port direction to input
	iErrorCode = me1000DIOSetPortDirection (iBoardNumber, iPortNumber, MEINPUT);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIOSetPortDirection";
		aErrorDialog.DoModal();		
	}

	iErrorCode = me1000DIGetLong (iBoardNumber, iPortNumber, &iLongValue);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIGetLong";
		aErrorDialog.DoModal();		
	}

	// Determine the state of the bit display boxes from the word value read in
	CButton* p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_0));
	B0 = (iLongValue & NUM_BIT_00) >> 0;
    if (B0 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_1));
	B1 = (iLongValue & NUM_BIT_01) >> 1;
    if (B1 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_2));
    B2 = (iLongValue & NUM_BIT_02) >> 2;
    if (B2 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_3));
    B3 = (iLongValue & NUM_BIT_03) >> 3;
    if (B3 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_4));
    B4 = (iLongValue & NUM_BIT_04) >> 4;
    if (B4 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_5));
    B5 = (iLongValue & NUM_BIT_05) >> 5;
    if (B5 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_6));
    B6 = (iLongValue & NUM_BIT_06) >> 6;
    if (B6 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_7));
    B7 = (iLongValue & NUM_BIT_07) >> 7;
    if (B7 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_8));
	B8 = (iLongValue & NUM_BIT_08) >> 8;
    if (B8 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_9));
	B9 = (iLongValue & NUM_BIT_09) >> 9;
    if (B9 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_10));
    B10 = (iLongValue & NUM_BIT_10) >> 10;
    if (B10 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_11));
    B11 = (iLongValue & NUM_BIT_11) >> 11;
    if (B11 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_12));
    B12 = (iLongValue & NUM_BIT_12) >> 12;
    if (B12 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_13));
    B13 = (iLongValue & NUM_BIT_13) >> 13;
    if (B13 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_14));
    B14 = (iLongValue & NUM_BIT_14) >> 14;
    if (B14 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_15));
    B15 = (iLongValue & NUM_BIT_15) >> 15;
    if (B15 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_16));
	B16 = (iLongValue & NUM_BIT_16) >> 16;
    if (B16 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_17));
	B17 = (iLongValue & NUM_BIT_17) >> 17;
    if (B17 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_18));
    B18 = (iLongValue & NUM_BIT_18) >> 18;
    if (B18 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_19));
    B19 = (iLongValue & NUM_BIT_19) >> 19;
    if (B19 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_20));
    B20 = (iLongValue & NUM_BIT_20) >> 20;
    if (B20 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_21));
    B21 = (iLongValue & NUM_BIT_21) >> 21;
    if (B21 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_22));
    B22 = (iLongValue & NUM_BIT_22) >> 22;
    if (B22 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_23));
    B23 = (iLongValue & NUM_BIT_23) >> 23;
    if (B23 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_24));
	B24 = (iLongValue & NUM_BIT_24) >> 24;
    if (B24 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_25));
	B25 = (iLongValue & NUM_BIT_25) >> 25;
    if (B25 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_26));
    B26 = (iLongValue & NUM_BIT_26) >> 26;
    if (B26 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_27));
    B27 = (iLongValue & NUM_BIT_27) >> 27;
    if (B27 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_28));
    B28 = (iLongValue & NUM_BIT_28) >> 28;
    if (B28 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_29));
    B29 = (iLongValue & NUM_BIT_29) >> 29;
    if (B29 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_30));
    B30 = (iLongValue & NUM_BIT_30) >> 30;
    if (B30 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_31));
    B31 = (iLongValue & NUM_BIT_31) >> 31;
    if (B31 == 1) p_CheckBox->SetCheck (CHECKED);
	else p_CheckBox->SetCheck (NOTCHECKED);
}

void CME1000TestView::BitWrite()
{
	int iBoardNumber;
	int iPortNumber;
	int iBitNo;
	int iErrorCode;
	int iBitValue;
	int iBoxState;
	int iVersion;

	// get the current board number
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
	iBoardNumber = p_Combo->GetCurSel();

	// get the current port number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_PORT_NUMBER));
	iPortNumber = p_Combo->GetCurSel();

	// check the board version
	iErrorCode = me1000GetBoardVersion (iBoardNumber, &iVersion);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000GetBoardVersion";
		aErrorDialog.DoModal();		
	}

	// for board version 100A, ports C and D are not available
	if (iVersion == 0x100A)
	{
		if ((iPortNumber == PORTC) | (iPortNumber == PORTD))
		{
			// if the board version is 100A and port C or D is
			// selected, an error box is displayed and the 
			// function is not executed
			AfxMessageBox("Port C and D not available on ME1000A \n\n Choose port A or B", 
													MB_OK|MB_ICONSTOP, 0);
			return;
		}
	}

	// get the currrent bit number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_NUMBER));
	iBitNo = p_Combo->GetCurSel();
	
	// Set the port direction to output
	iErrorCode = me1000DIOSetPortDirection (iBoardNumber, iPortNumber, MEOUTPUT);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIOSetPortDirection";
		aErrorDialog.DoModal();		
	}

	// get the current state of the bit check box	
	CButton* p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_CHECK_BIT_VALUE));
	iBoxState = p_CheckBox->GetState();
	if (iBoxState == CHECKED) iBitValue = 1;
	else iBitValue = 0;

	iErrorCode = me1000DOSetBit (iBoardNumber, iPortNumber, iBitNo, iBitValue);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DOSetBit";
		aErrorDialog.DoModal();		
	}
}

void CME1000TestView::ByteWrite()
{
	int iBoardNumber;
	int iPortNumber;
	int iByteNo;
	int iErrorCode;
	int iByteValue = 0;
	int iVersion;
	int B0, B1, B2, B3, B4, B5, B6, B7;
	
	// get the current board number
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
	iBoardNumber = p_Combo->GetCurSel();

	// get the current port number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_PORT_NUMBER));
	iPortNumber = p_Combo->GetCurSel();

	// check the board version
	iErrorCode = me1000GetBoardVersion (iBoardNumber, &iVersion);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000GetBoardVersion";
		aErrorDialog.DoModal();		
	}

	// for board version 100A, ports C and D are not available
	if (iVersion == 0x100A)
	{
		if ((iPortNumber == PORTC) | (iPortNumber == PORTD))
		{
			// if the board version is 100A and port C or D is
			// selected, an error box is displayed and the 
			// function is not executed
			AfxMessageBox("Port C and D not available on ME1000A \n\n Choose port A or B", 
													MB_OK|MB_ICONSTOP, 0);
			return;
		}
	}

	// get the currrent byte number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_NUMBER));
	iByteNo = p_Combo->GetCurSel();

	// Determine the state of the bit display boxes for a byte value
	CButton* p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_0));
	B0 = p_CheckBox->GetState();
	if (B0 == CHECKED) iByteValue = iByteValue + NUM_BIT_00;
	
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_1));
	B1 = p_CheckBox->GetState();
	if (B1 == CHECKED) iByteValue = iByteValue + NUM_BIT_01;
	
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_2));
	B2 = p_CheckBox->GetState();
	if (B2 == CHECKED) iByteValue = iByteValue + NUM_BIT_02;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_3));
	B3 = p_CheckBox->GetState();
	if (B3 == CHECKED) iByteValue = iByteValue + NUM_BIT_03;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_4));
	B4 = p_CheckBox->GetState();
	if (B4 == CHECKED) iByteValue = iByteValue + NUM_BIT_04;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_5));
	B5 = p_CheckBox->GetState();
	if (B5 == CHECKED) iByteValue = iByteValue + NUM_BIT_05;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_6));
	B6 = p_CheckBox->GetState();
	if (B6 == CHECKED) iByteValue = iByteValue + NUM_BIT_06;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_BYTE_BIT_7));
	B7 = p_CheckBox->GetState();
	if (B7 == CHECKED) iByteValue = iByteValue + NUM_BIT_07;

	// Set the port direction to output
	iErrorCode = me1000DIOSetPortDirection (iBoardNumber, iPortNumber, MEOUTPUT);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIOSetPortDirection";
		aErrorDialog.DoModal();		
	}

	// write the byte value to the selected port
	iErrorCode = me1000DOSetByte (iBoardNumber, iPortNumber, iByteNo, iByteValue);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DOSetByte";
		aErrorDialog.DoModal();		
	}

}

void CME1000TestView::WordWrite()
{

	int iBoardNumber;
	int iPortNumber;
	int iWordNo;
	int iErrorCode;
	int iWordValue = 0;
	int iVersion ;
	int B0, B1, B2, B3, B4, B5, B6, B7,
		B8, B9, B10, B11, B12, B13, B14, B15;

	// get the current board number
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
	iBoardNumber = p_Combo->GetCurSel();

	// get the current port number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_PORT_NUMBER));
	iPortNumber = p_Combo->GetCurSel();

	// check the board version
	iErrorCode = me1000GetBoardVersion (iBoardNumber, &iVersion);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000GetBoardVersion";
		aErrorDialog.DoModal();		
	}

	// for board version 100A, ports C and D are not available
	if (iVersion == 0x100A)
	{
		if ((iPortNumber == PORTC) | (iPortNumber == PORTD))
		{
			// if the board version is 100A and port C or D is
			// selected, an error box is displayed and the 
			// function is not executed
			AfxMessageBox("Port C and D not available on ME1000A \n\n Choose port A or B", 
													MB_OK|MB_ICONSTOP, 0);
			return;
		}
	}

	// get the currrent word number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_NUMBER));
	iWordNo = p_Combo->GetCurSel();

	// Determine the state of the bit display boxes from the word value read in
	CButton* p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_0));
	B0 = p_CheckBox->GetState();
	if (B0 == CHECKED) iWordValue = iWordValue + NUM_BIT_00; // set bit 0

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_1));
	B1 = p_CheckBox->GetState();
	if (B1 == CHECKED) iWordValue = iWordValue + NUM_BIT_01;
	
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_2));
    B2 = p_CheckBox->GetState();
	if (B2 == CHECKED) iWordValue = iWordValue + NUM_BIT_02;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_3));
    B3 = p_CheckBox->GetState();
	if (B3 == CHECKED) iWordValue = iWordValue + NUM_BIT_03;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_4));
    B4 = p_CheckBox->GetState();
	if (B4 == CHECKED) iWordValue = iWordValue + NUM_BIT_04;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_5));
    B5 = p_CheckBox->GetState();
	if (B5 == CHECKED) iWordValue = iWordValue + NUM_BIT_05;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_6));
    B6 = p_CheckBox->GetState();
	if (B6 == CHECKED) iWordValue = iWordValue + NUM_BIT_06;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_7));
    B7 = p_CheckBox->GetState();
	if (B7 == CHECKED) iWordValue = iWordValue + NUM_BIT_07;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_8));
	B8 = p_CheckBox->GetState();
	if (B8 == CHECKED) iWordValue = iWordValue + NUM_BIT_08;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_9));
	B9 = p_CheckBox->GetState();
	if (B9 == CHECKED) iWordValue = iWordValue + NUM_BIT_09;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_10));
	B10 = p_CheckBox->GetState();
	if (B10 == CHECKED) iWordValue = iWordValue + NUM_BIT_10;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_11));
	B11 = p_CheckBox->GetState();
	if (B11 == CHECKED) iWordValue = iWordValue + NUM_BIT_11;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_12));
	B12 = p_CheckBox->GetState();
	if (B12 == CHECKED) iWordValue = iWordValue + NUM_BIT_12;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_13));
	B13 = p_CheckBox->GetState();
	if (B13 == CHECKED) iWordValue = iWordValue + NUM_BIT_13;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_14));
	B14 = p_CheckBox->GetState();
	if (B14 == CHECKED) iWordValue = iWordValue + NUM_BIT_14;

	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_WORD_BIT_15));
	B15 = p_CheckBox->GetState();
	if (B15 == CHECKED) iWordValue = iWordValue + NUM_BIT_15;

	// Set the port direction to output
	iErrorCode = me1000DIOSetPortDirection (iBoardNumber, iPortNumber, MEOUTPUT);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIOSetPortDirection";
		aErrorDialog.DoModal();		
	}

	iErrorCode = me1000DOSetWord (iBoardNumber, iPortNumber, iWordNo, iWordValue);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DOSetWord";
		aErrorDialog.DoModal();		
	}
}

void CME1000TestView::LongWrite()
{
	int iBoardNumber;
	int iPortNumber;
	int iErrorCode;
	int iLongValue = 0;
	int iVersion;
	int B0, B1, B2, B3, B4, B5, B6, B7,
		B8, B9, B10, B11, B12, B13, B14, B15,
		B16, B17, B18, B19, B20, B21, B22, B23,
		B24, B25, B26, B27, B28, B29, B30, B31 ;

	// get the current board number
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
	iBoardNumber = p_Combo->GetCurSel();

	// get the current port number
	p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_LONG_PORT_NUMBER));
	iPortNumber = p_Combo->GetCurSel();

	// check the board version
	iErrorCode = me1000GetBoardVersion (iBoardNumber, &iVersion);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000GetBoardVersion";
		aErrorDialog.DoModal();		
	}

	// for board version 100A, ports C and D are not available
	if (iVersion == 0x100A)
	{
		if ((iPortNumber == PORTC) | (iPortNumber == PORTD))
		{
			// if the board version is 100A and port C or D is
			// selected, an error box is displayed and the
			// function is not executed
			AfxMessageBox("Port C and D not available on ME1000A \n\n Choose port A or B", 
													MB_OK|MB_ICONSTOP, 0);
			return;
		}
	}

	// Determine the state of the bit display boxes from the word value read in
	CButton* p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_0));
	B0 = p_CheckBox->GetState();
	if (B0 == CHECKED) iLongValue = iLongValue + NUM_BIT_00; // set bit 0
	
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_1));
	B1 = p_CheckBox->GetState();
	if (B1 == CHECKED) iLongValue = iLongValue + NUM_BIT_01;
	
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_2));
	B2 = p_CheckBox->GetState();
	if (B2 == CHECKED) iLongValue = iLongValue + NUM_BIT_02;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_3));
	B3 = p_CheckBox->GetState();
	if (B3 == CHECKED) iLongValue = iLongValue + NUM_BIT_03;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_4));
	B4 = p_CheckBox->GetState();
	if (B4 == CHECKED) iLongValue = iLongValue + NUM_BIT_04;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_5));
	B5 = p_CheckBox->GetState();
	if (B5 == CHECKED) iLongValue = iLongValue + NUM_BIT_05;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_6));
	B6 = p_CheckBox->GetState();
	if (B6 == CHECKED) iLongValue = iLongValue + NUM_BIT_06;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_7));
	B7 = p_CheckBox->GetState();
	if (B7 == CHECKED) iLongValue = iLongValue + NUM_BIT_07;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_8));
	B8 = p_CheckBox->GetState();
	if (B8 == CHECKED) iLongValue = iLongValue + NUM_BIT_08;
	
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_9));
	B9 = p_CheckBox->GetState();
	if (B9 == CHECKED) iLongValue = iLongValue + NUM_BIT_09;
	
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_10));
	B10 = p_CheckBox->GetState();
	if (B10 == CHECKED) iLongValue = iLongValue + NUM_BIT_10;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_11));
	B11 = p_CheckBox->GetState();
	if (B11 == CHECKED) iLongValue = iLongValue + NUM_BIT_11;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_12));
	B12 = p_CheckBox->GetState();
	if (B12 == CHECKED) iLongValue = iLongValue + NUM_BIT_12;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_13));
	B13 = p_CheckBox->GetState();
	if (B13 == CHECKED) iLongValue = iLongValue + NUM_BIT_13;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_14));
	B14 = p_CheckBox->GetState();
	if (B14 == CHECKED) iLongValue = iLongValue + NUM_BIT_14;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_15));
	B15 = p_CheckBox->GetState();
	if (B15 == CHECKED) iLongValue = iLongValue + NUM_BIT_15;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_16));
	B16 = p_CheckBox->GetState();
	if (B16 == CHECKED) iLongValue = iLongValue + NUM_BIT_16;
	
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_17));
	B17 = p_CheckBox->GetState();
	if (B17 == CHECKED) iLongValue = iLongValue + NUM_BIT_17;
	
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_18));
	B18 = p_CheckBox->GetState();
	if (B18 == CHECKED) iLongValue = iLongValue + NUM_BIT_18;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_19));
	B19 = p_CheckBox->GetState();
	if (B19 == CHECKED) iLongValue = iLongValue + NUM_BIT_19;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_20));
	B20 = p_CheckBox->GetState();
	if (B20 == CHECKED) iLongValue = iLongValue + NUM_BIT_20;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_21));
	B21 = p_CheckBox->GetState();
	if (B21 == CHECKED) iLongValue = iLongValue + NUM_BIT_21;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_22));
	B22 = p_CheckBox->GetState();
	if (B22 == CHECKED) iLongValue = iLongValue + NUM_BIT_22;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_23));
	B23 = p_CheckBox->GetState();
	if (B23 == CHECKED) iLongValue = iLongValue + NUM_BIT_23;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_24));
	B24 = p_CheckBox->GetState();
	if (B24 == CHECKED) iLongValue = iLongValue + NUM_BIT_24;
	
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_25));
	B25 = p_CheckBox->GetState();
	if (B25 == CHECKED) iLongValue = iLongValue + NUM_BIT_25;
	
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_26));
	B26 = p_CheckBox->GetState();
	if (B26 == CHECKED) iLongValue = iLongValue + NUM_BIT_26;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_27));
	B27 = p_CheckBox->GetState();
	if (B27 == CHECKED) iLongValue = iLongValue + NUM_BIT_27;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_28));
	B28 = p_CheckBox->GetState();
	if (B28 == CHECKED) iLongValue = iLongValue + NUM_BIT_28;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_29));
	B29 = p_CheckBox->GetState();
	if (B29 == CHECKED) iLongValue = iLongValue + NUM_BIT_29;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_30));
	B30 = p_CheckBox->GetState();
	if (B30 == CHECKED) iLongValue = iLongValue + NUM_BIT_30;
    
	p_CheckBox=static_cast<CButton*>(GetDlgItem(IDC_LONG_BIT_31));
	B31 = p_CheckBox->GetState();
	if (B31 == CHECKED) iLongValue = iLongValue + NUM_BIT_31;

	// Set the port direction to output
	iErrorCode = me1000DIOSetPortDirection (iBoardNumber, iPortNumber, MEOUTPUT);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIOSetPortDirection";
		aErrorDialog.DoModal();		
	}

	iErrorCode = me1000DOSetLong (iBoardNumber, iPortNumber, iLongValue);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DOSetLong";
		aErrorDialog.DoModal();		
	}
}

void CME1000TestView::OnSelchangeComboFunctionSelect() 
{
	int iFunctionSetting;
	
	// get the current function setting (bit, byte, word, long)
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_FUNCTION_SELECT));
	iFunctionSetting = p_Combo->GetCurSel();

	if (iFunctionSetting == BIT_FUNCTION) 
	{
		// activate the bit function combo boxes
		CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_NUMBER));
		p_Combo->EnableWindow (TRUE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_PORT_NUMBER));
		p_Combo->EnableWindow (TRUE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_BIT_FUNCTIONS));
		p_Combo->EnableWindow (TRUE);

	// de-activate the byte function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_BYTE_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_NUMBER));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);

	// de-activate the word function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_WORD_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_NUMBER));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);

	// de-activate the long function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_LONG_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_LONG_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);
	}

	if (iFunctionSetting == BYTE_FUNCTION)
	{
		// activate the byte function combo boxes
		CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_NUMBER));
		p_Combo->EnableWindow (TRUE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_PORT_NUMBER));
		p_Combo->EnableWindow (TRUE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_BYTE_FUNCTIONS));
		p_Combo->EnableWindow (TRUE);

	// de-activate the bit function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_BIT_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_NUMBER));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);

	// de-activate the word function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_WORD_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_NUMBER));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);

	// de-activate the long function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_LONG_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_LONG_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);
	}

	if (iFunctionSetting == WORD_FUNCTION) 
	{
		// activate the word function combo boxes
		CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_NUMBER));
		p_Combo->EnableWindow (TRUE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_PORT_NUMBER));
		p_Combo->EnableWindow (TRUE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_WORD_FUNCTIONS));
		p_Combo->EnableWindow (TRUE);

	// de-activate the bit function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_BIT_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_NUMBER));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);

	// de-activate the word function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_BYTE_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_NUMBER));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);

	// de-activate the long function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_LONG_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_LONG_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);		
	}

	if (iFunctionSetting == LONG_FUNCTION)
	{
		// activate the long function combo boxes
		CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_LONG_FUNCTIONS));
		p_Combo->EnableWindow (TRUE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_LONG_PORT_NUMBER));
		p_Combo->EnableWindow (TRUE);		

	// de-activate the bit function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_BIT_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_NUMBER));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BIT_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);

	// de-activate the word function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_BYTE_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_NUMBER));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BYTE_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);

		// de-activate the word function combo boxes
		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_NUMBER));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_WORD_PORT_NUMBER));
		p_Combo->EnableWindow (FALSE);

		p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_STATIC_WORD_FUNCTIONS));
		p_Combo->EnableWindow (FALSE);
	}
}

void CME1000TestView::OnButtonReset() 
{
	// doing a reset will set all ports to input
	int iBoardNumber;
	int iErrorCode;

	// get the current board number
	CComboBox* p_Combo=static_cast<CComboBox*>(GetDlgItem(IDC_COMBO_BOARD_NUMBER));
	iBoardNumber = p_Combo->GetCurSel();

	iErrorCode = me1000DIOReset (iBoardNumber);
	if (iErrorCode == 0)
	{
		// error, function not successfully completed  
		CErrorDialog aErrorDialog; 
		aErrorDialog.m_csErrorMessage = "me1000DIOReset";
		aErrorDialog.DoModal();		
	}
}
