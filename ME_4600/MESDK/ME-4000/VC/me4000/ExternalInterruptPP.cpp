// ExternalInterruptPP.cpp : implementation file
//

#include "stdafx.h"
#include "me4000.h"
#include "ExternalInterruptPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExternalInterruptPP property page

IMPLEMENT_DYNCREATE(CExternalInterruptPP, CPropertyPage)

static LOGFONT lf_text = {-72, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 
							OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
							DEFAULT_QUALITY, DEFAULT_PITCH|FF_ROMAN, "Arial" };

const COLORREF DISPLAY_COLOR =  RGB(255, 0, 0);

CExternalInterruptPP::CExternalInterruptPP() : CPropertyPage(CExternalInterruptPP::IDD)
{
	//{{AFX_DATA_INIT(CExternalInterruptPP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iCurrentBoardIndex = 0;

	for(int index_board = 0; index_board < ME4000_MAX_DEVICES; index_board++)
	{
		m_sBoardExtInt[index_board].m_pExtIntPP = this;

		m_sBoardExtInt[index_board].m_iIndexBoard = index_board;
		
		m_sBoardExtInt[index_board].m_uiNumberOfInterrupts = 0;
	}
	
	m_pPlotWin = NULL;
	
	m_rectPlotClient.SetRectEmpty();

	m_rectPlotChild.SetRectEmpty();

	m_pPropertySheet = NULL;
}

CExternalInterruptPP::~CExternalInterruptPP()
{
}

void CExternalInterruptPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExternalInterruptPP)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_COMBO_BOARD, m_comboBoardNumber);
	//}}AFX_DATA_MAP
}


void CExternalInterruptPP::SetControlStates(void)
{
	Cme4000App* p_app = (Cme4000App*)AfxGetApp();

	ME4000Board* p_boards = p_app->GetBoardArray();

	CString cs_text;
	
	cs_text.Format( "%04X", p_boards[m_iCurrentBoardIndex].m_usDeviceID );
	
	SetDlgItemText(IDC_BOARD_VERSION, cs_text);
	
	cs_text.Format( "%08X", p_boards[m_iCurrentBoardIndex].m_ulSerialNumber );
	
	SetDlgItemText(IDC_SERIAL_NUMBER, cs_text);
}


BEGIN_MESSAGE_MAP(CExternalInterruptPP, CPropertyPage)
	//{{AFX_MSG_MAP(CExternalInterruptPP)
	ON_BN_CLICKED(ID_EXIT, OnExit)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_DISABLE_EXT_INT, OnButtonDisableExtInt)
	ON_BN_CLICKED(IDC_BUTTON_ENABLE_EXT_INT, OnButtonEnableExtInt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CExternalInterruptPP::OnInitDialog() 
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

	m_pPlotWin = GetDlgItem(IDC_PLOT);
	
	CRect rect_plot;

	m_pPlotWin->GetClientRect(rect_plot);
	
	m_rectPlotClient = rect_plot;

	m_rectPlotClient.DeflateRect(1, 1);

	m_pPlotWin->GetWindowRect(&rect_plot);

	ScreenToClient(&rect_plot);

	m_rectPlotChild = rect_plot;

	m_rectPlotChild.DeflateRect(1, 1);

	SetControlStates();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExternalInterruptPP::OnExit() 
{
	// TODO: Add your control notification handler code here
	
	if(AfxMessageBox("This will terminate the test programm", MB_OKCANCEL) == IDOK)
	{
		m_pPropertySheet->EndDialog(0);
	}
}



/////////////////////////////////////////////////////////////////////////////
// CExternalInterruptPP message handlers

void CExternalInterruptPP::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	CClientDC dc_plot(m_pPlotWin);

	dc_plot.FillSolidRect( m_rectPlotClient, RGB(0, 0, 0) );	
	
	dc_plot.SetTextColor(DISPLAY_COLOR);

	dc_plot.SetBkMode(TRANSPARENT);

	CFont font_text;

	font_text.CreateFontIndirect(&lf_text);

	CFont* p_old_font = dc_plot.SelectObject(&font_text);
    
	CString cs_value;

	cs_value.Format("%-10u Interrupts", m_sBoardExtInt[m_iCurrentBoardIndex].m_uiNumberOfInterrupts);

	dc_plot.DrawText(cs_value, m_rectPlotClient, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		
	dc_plot.SelectObject(p_old_font);
	
	// Do not call CPropertyPage::OnPaint() for painting messages
}

void CExternalInterruptPP::OnButtonEnableExtInt() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000ExtIrqEnable(	m_iCurrentBoardIndex,						// uiBoardNumber
										ExtIRQProc,									// pExtIrqProc
										&m_sBoardExtInt[m_iCurrentBoardIndex]	);	// pExtIrqContext

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	GetDlgItem(IDC_BUTTON_ENABLE_EXT_INT)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_DISABLE_EXT_INT)->EnableWindow(TRUE);
}

void CExternalInterruptPP::OnButtonDisableExtInt() 
{
	// TODO: Add your control notification handler code here
	
	int i_error = me4000ExtIrqDisable(m_iCurrentBoardIndex);	// uiBoardNumber

	if(i_error != ME4000_NO_ERROR)
	{
		return;
	}

	GetDlgItem(IDC_BUTTON_ENABLE_EXT_INT)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_DISABLE_EXT_INT)->EnableWindow(FALSE);
}

void CExternalInterruptPP::RedrawPlot(void)
{
	InvalidateRect(m_rectPlotChild);
}
	
void _stdcall CExternalInterruptPP::ExtIRQProc(void* pExtIrqContext)
{
	SMEBoardExtInt* p_board_ext_int = (SMEBoardExtInt*)pExtIrqContext;
	
	me4000ExtIrqGetCount(	p_board_ext_int->m_iIndexBoard,				// uiBoardNumber
							&p_board_ext_int->m_uiNumberOfInterrupts);	// puiIrqCount
																	

	p_board_ext_int->m_pExtIntPP->RedrawPlot();
}
