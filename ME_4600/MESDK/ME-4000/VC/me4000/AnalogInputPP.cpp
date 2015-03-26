// AnalogInputPP.cpp : implementation file
//

#include "stdafx.h"
#include "me4000.h"
#include "AnalogInputPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnalogInputPP property page

IMPLEMENT_DYNCREATE(CAnalogInputPP, CPropertyPage)

static LOGFONT lf_text = {-72, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 
							OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
							DEFAULT_QUALITY, DEFAULT_PITCH|FF_ROMAN, "Arial" };

const COLORREF channel_colors[4] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0) };

CAnalogInputPP::CAnalogInputPP() : CPropertyPage(CAnalogInputPP::IDD)
{
	//{{AFX_DATA_INIT(CAnalogInputPP)
	//}}AFX_DATA_INIT

	for(int index_board = 0; index_board < ME4000_MAX_DEVICES; index_board++)
	{
		m_sBoardAI[index_board].m_pAnalogInputPP = this;
		
		m_sBoardAI[index_board].m_iFunction = AI_SINGLE;
	
		for(int index_channel = 0; index_channel < 4; index_channel++)
		{
			m_sBoardAI[index_board].m_bChannelActive[index_channel]		= TRUE;

			m_sBoardAI[index_board].m_uiChannelNumber[index_channel]	= (unsigned int)index_channel;

			m_sBoardAI[index_board].m_iChannelRange[index_channel]		= ME4000_AI_RANGE_BIPOLAR_10;
		}

		m_sBoardAI[index_board].m_iSDMode					= ME4000_AI_INPUT_SINGLE_ENDED;

		m_sBoardAI[index_board].m_iTriggerSingleMode		= ME4000_AI_TRIGGER_SOFTWARE;

		m_sBoardAI[index_board].m_iTriggerExtMode			= ME4000_AI_TRIGGER_EXT_DIGITAL;

		m_sBoardAI[index_board].m_iTriggerExtEdge			= ME4000_AI_TRIGGER_EXT_EDGE_RISING;

		m_sBoardAI[index_board].m_uiNumberOfChannelLists	= 1000;

		m_sBoardAI[index_board].m_dWindowWidthSeconds		= 4;	

		m_sBoardAI[index_board].m_uiWindowWidthValues		= 1000;	

		m_sBoardAI[index_board].m_iAcquisitionMode			= ME4000_AI_ACQ_MODE_SOFTWARE;			

		m_sBoardAI[index_board].m_dSampleRate				= 1000;

		m_sBoardAI[index_board].m_uiRefresh					= 100;

		m_sBoardAI[index_board].m_ulTimeout					= 5;

		m_sBoardAI[index_board].m_bSampleAndHold			= FALSE;

		m_sBoardAI[index_board].m_iLastOperation			= AI_NONE;

		m_sBoardAI[index_board].m_bAIActive					= FALSE;

		m_sBoardAI[index_board].m_uiSingleChannel			= 0;
		
		m_sBoardAI[index_board].m_sSingleValueVolt			= 0.0;

		m_sBoardAI[index_board].m_uiCurrentNumberOfChannels = 0;
		
		for(index_channel = 0; index_channel < 4; index_channel++)
		{
			m_sBoardAI[index_board].m_crCurrentChanColours[index_channel]	= RGB(0, 0, 0);
			
			m_sBoardAI[index_board].m_uiCurrentChanNumber[index_channel]	= index_channel;
			
			m_sBoardAI[index_board].m_iCurrentChanRange[index_channel]		= ME4000_AI_RANGE_BIPOLAR_10;

			m_sBoardAI[index_board].m_ucChanList[index_channel]				= 0x00;
		}

		m_sBoardAI[index_board].m_dXIncrement								= 0;

		for(index_channel = 0; index_channel < 4; index_channel++)
		{
			m_sBoardAI[index_board].m_dYFactor[index_channel]				= 0;

			m_sBoardAI[index_board].m_dYConstant[index_channel]				= 0;
		}

		m_sBoardAI[index_board].m_psScanBuffer								= NULL;

		m_sBoardAI[index_board].m_uiScanBufferSizeValues					= 0;

		m_sBoardAI[index_board].m_uiNumberOfScanData						= 0;

		m_sBoardAI[index_board].m_uiCurrentNumberofChanLists				= 0;

		m_sBoardAI[index_board].m_bFirstDraw								= TRUE;

		m_sBoardAI[index_board].m_dXLastPixel								= 0.0;

		m_sBoardAI[index_board].m_iXLastPixel								= 0;

		for(index_channel = 0; index_channel < 4; index_channel++)
		{
			m_sBoardAI[index_board].m_iYLastPixel[index_channel] = 0;
		}
	}

	m_iCurrentBoardIndex = 0;

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		m_cbChannel[index_channel].m_crBackground = RGB(0, 0, 0);
		m_cbChannel[index_channel].m_crForeground = channel_colors[index_channel];
	}

	m_pPlotWin = NULL;
	
	m_rectPlotClient.SetRectEmpty();

	m_rectPlotChild.SetRectEmpty();

	m_pPropertySheet = NULL;
}

CAnalogInputPP::~CAnalogInputPP()
{
	for(int index_board = 0; index_board < ME4000_MAX_DEVICES; index_board++)
	{
		if(m_sBoardAI[index_board].m_psScanBuffer != NULL)
		{
			delete m_sBoardAI[index_board].m_psScanBuffer;
		}
	}
}

void CAnalogInputPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_NUMBER_CHANNEL_1, m_comboNumberChannel[0]);
	DDX_Control(pDX, IDC_NUMBER_CHANNEL_2, m_comboNumberChannel[1]);
	DDX_Control(pDX, IDC_NUMBER_CHANNEL_3, m_comboNumberChannel[2]);
	DDX_Control(pDX, IDC_NUMBER_CHANNEL_4, m_comboNumberChannel[3]);

	DDX_Control(pDX, IDC_RANGE_CHANNEL_1, m_comboRangeChannel[0]);
	DDX_Control(pDX, IDC_RANGE_CHANNEL_2, m_comboRangeChannel[1]);
	DDX_Control(pDX, IDC_RANGE_CHANNEL_3, m_comboRangeChannel[2]);
	DDX_Control(pDX, IDC_RANGE_CHANNEL_4, m_comboRangeChannel[3]);

	int i_sd_mode;

	int i_trigger_type;

	int i_trigger_ext_edge;

	int i_acq_mode;
	
	if( !pDX->m_bSaveAndValidate )
	{
		for(int index_channel = 0; index_channel < 4; index_channel++)
		{
			m_comboNumberChannel[index_channel].SetCurSel( (int)m_sBoardAI[m_iCurrentBoardIndex].m_uiChannelNumber[index_channel] );

			int i_range_index = 0;
		
			switch( m_sBoardAI[m_iCurrentBoardIndex].m_iChannelRange[index_channel] )	
			{
			case ME4000_AI_RANGE_BIPOLAR_10:

				i_range_index = 0;

				break;

			case ME4000_AI_RANGE_BIPOLAR_2_5:

				i_range_index = 1;

				break;

			case ME4000_AI_RANGE_UNIPOLAR_10:

				i_range_index = 2;

				break;

			case ME4000_AI_RANGE_UNIPOLAR_2_5:

				i_range_index = 3;

				break;
			}

			m_comboRangeChannel[index_channel].SetCurSel(i_range_index);
		}

		switch(m_sBoardAI[m_iCurrentBoardIndex].m_iSDMode)
		{
		case ME4000_AI_INPUT_SINGLE_ENDED:

			i_sd_mode = 0;

			break;

		case ME4000_AI_INPUT_DIFFERENTIAL:

			i_sd_mode = 1;

			break;
		}

		if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_SINGLE)
		{
			switch(m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode)
			{
			case ME4000_AI_TRIGGER_SOFTWARE:

				i_trigger_type = 0;

				break;

			case ME4000_AI_TRIGGER_EXT_DIGITAL:

				i_trigger_type = 1;

				break;

			case ME4000_AI_TRIGGER_EXT_ANALOG:

				i_trigger_type = 2;

				break;
			}
		}
		else
		{
			switch(m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtMode)
			{
			case ME4000_AI_TRIGGER_EXT_DIGITAL:

				i_trigger_type = 1;

				break;

			case ME4000_AI_TRIGGER_EXT_ANALOG:

				i_trigger_type = 2;

				break;
			}
		}
	
		switch(m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtEdge)
		{
		case ME4000_AI_TRIGGER_EXT_EDGE_RISING:

			i_trigger_ext_edge = 0;

			break;

		case ME4000_AI_TRIGGER_EXT_EDGE_FALLING:

			i_trigger_ext_edge = 1;

			break;

		case ME4000_AI_TRIGGER_EXT_EDGE_BOTH:

			i_trigger_ext_edge = 2;

			break;
		}
	
		switch(m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode)
		{
		case ME4000_AI_ACQ_MODE_SOFTWARE:

			i_acq_mode = 0;

			break;

		case ME4000_AI_ACQ_MODE_EXT:

			i_acq_mode = 1;

			break;

		case ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE:

			i_acq_mode = 2;

			break;

		case ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST:

			i_acq_mode = 3;

			break;
		}
	}

	//{{AFX_DATA_MAP(CAnalogInputPP)
	DDX_Control(pDX, IDC_SCAN_PROGRESS, m_progressScan);
	DDX_Control(pDX, IDC_SPIN_REFRESH, m_spinRefresh);
	DDX_Control(pDX, IDC_SPIN_WINDOW_WIDTH_VALUES, m_spinWindowWidthValue);
	DDX_Control(pDX, IDC_SPIN_TIMEOUT, m_spinTimeout);
	DDX_Control(pDX, IDC_SPIN_SAMPLE_RATE, m_spinSampleRate);
	DDX_Control(pDX, IDC_SPIN_NO_OF_CHANNEL_LISTS, m_spinNoOfChannelLists);
	DDX_Control(pDX, IDC_COMBO_BOARD, m_comboBoardNumber);
	//}}AFX_DATA_MAP

	DDX_Radio(pDX, IDC_RADIO_AI_SINGLE, m_sBoardAI[m_iCurrentBoardIndex].m_iFunction);

	DDX_Check(pDX, IDC_CHECK_CHANNEL_1, m_sBoardAI[m_iCurrentBoardIndex].m_bChannelActive[0]);
	DDX_Check(pDX, IDC_CHECK_CHANNEL_2, m_sBoardAI[m_iCurrentBoardIndex].m_bChannelActive[1]);
	DDX_Check(pDX, IDC_CHECK_CHANNEL_3, m_sBoardAI[m_iCurrentBoardIndex].m_bChannelActive[2]);
	DDX_Check(pDX, IDC_CHECK_CHANNEL_4, m_sBoardAI[m_iCurrentBoardIndex].m_bChannelActive[3]);

	DDX_Radio(pDX, IDC_RADIO_SINGLE_ENDED, i_sd_mode);

	DDX_Radio(pDX, IDC_RADIO_TRIGGER_TYPE_SOFTWARE, i_trigger_type);

	DDX_Radio(pDX, IDC_RADIO_EXT_TRIGGER_EDGE_RISING, i_trigger_ext_edge);

	DDX_Text(pDX, IDC_EDIT_NO_OF_CHANNEL_LISTS, m_sBoardAI[m_iCurrentBoardIndex].m_uiNumberOfChannelLists);

	DDX_Text(pDX, IDC_EDIT_WINDOW_WIDTH_SECONDS, m_sBoardAI[m_iCurrentBoardIndex].m_dWindowWidthSeconds);

	DDX_Text(pDX, IDC_EDIT_WINDOW_WIDTH_VALUES, m_sBoardAI[m_iCurrentBoardIndex].m_uiWindowWidthValues);

	DDX_Radio(pDX, IDC_RADIO_CONT_SW, i_acq_mode);

	DDX_Text(pDX, IDC_EDIT_SAMPLE_RATE, m_sBoardAI[m_iCurrentBoardIndex].m_dSampleRate);

	DDX_Text(pDX, IDC_EDIT_REFRESH, m_sBoardAI[m_iCurrentBoardIndex].m_uiRefresh);

	DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_sBoardAI[m_iCurrentBoardIndex].m_ulTimeout);

	DDX_Check(pDX, IDC_CHECK_SAMPLE_AND_HOLD, m_sBoardAI[m_iCurrentBoardIndex].m_bSampleAndHold);

	if(pDX->m_bSaveAndValidate)
	{
		for(int index_channel = 0; index_channel < 4; index_channel++)
		{
			m_sBoardAI[m_iCurrentBoardIndex].m_uiChannelNumber[index_channel] = (unsigned int)m_comboNumberChannel[index_channel].GetCurSel();

			int i_range_index = m_comboRangeChannel[index_channel].GetCurSel();
		
			switch(i_range_index)	
			{
			case 0:

				m_sBoardAI[m_iCurrentBoardIndex].m_iChannelRange[index_channel] = ME4000_AI_RANGE_BIPOLAR_10;

				break;

			case 1:

				m_sBoardAI[m_iCurrentBoardIndex].m_iChannelRange[index_channel] = ME4000_AI_RANGE_BIPOLAR_2_5;

				break;

			case 2:

				m_sBoardAI[m_iCurrentBoardIndex].m_iChannelRange[index_channel] = ME4000_AI_RANGE_UNIPOLAR_10;

				break;

			case 3:

				m_sBoardAI[m_iCurrentBoardIndex].m_iChannelRange[index_channel] = ME4000_AI_RANGE_UNIPOLAR_2_5;

				break;
			}
		}

		switch(i_sd_mode)
		{
		case 0:

			m_sBoardAI[m_iCurrentBoardIndex].m_iSDMode = ME4000_AI_INPUT_SINGLE_ENDED;

			break;

		case 1:

			m_sBoardAI[m_iCurrentBoardIndex].m_iSDMode = ME4000_AI_INPUT_DIFFERENTIAL;

			break;
		}

		if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_SINGLE)
		{
			switch(i_trigger_type)
			{
			case 0:

				m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode = ME4000_AI_TRIGGER_SOFTWARE;

				break;

			case 1:

				m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode = ME4000_AI_TRIGGER_EXT_DIGITAL;

				break;

			case 2:

				m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode = ME4000_AI_TRIGGER_EXT_ANALOG;

				break;
			}
		}
		else
		{
			switch(i_trigger_type)
			{
			case 1:

				m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtMode = ME4000_AI_TRIGGER_EXT_DIGITAL;

				break;

			case 2:

				m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtMode = ME4000_AI_TRIGGER_EXT_ANALOG;

				break;
			}
		}
	
		switch(i_trigger_ext_edge)
		{
		case 0:

			m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtEdge = ME4000_AI_TRIGGER_EXT_EDGE_RISING;

			break;

		case 1:

			m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtEdge = ME4000_AI_TRIGGER_EXT_EDGE_FALLING;

			break;

		case 2:

			m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtEdge = ME4000_AI_TRIGGER_EXT_EDGE_BOTH;

			break;
		}
	
		switch(i_acq_mode)
		{
		case 0:

			m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode = ME4000_AI_ACQ_MODE_SOFTWARE;

			break;

		case 1:

			m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode = ME4000_AI_ACQ_MODE_EXT;

			break;

		case 2:

			m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode = ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE;

			break;

		case 3:

			m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode = ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST;

			break;
		}
	}
}


void CAnalogInputPP :: ScanCallback(short* psValues, unsigned int uiNumberOfValues, 
													void* pCallbackContext, int iLastError)
{
	SMEBoardAI* p_board_ai = (SMEBoardAI*)pCallbackContext;

	p_board_ai->m_uiNumberOfScanData+= uiNumberOfValues;

//	p_board_ai->m_pAnalogInputPP->m_progressScan.SetPos(p_board_ai->m_uiNumberOfScanData);

	p_board_ai->m_pAnalogInputPP->m_progressScan.PostMessage(PBM_SETPOS, p_board_ai->m_uiNumberOfScanData, 0);

	if(iLastError != ME4000_NO_ERROR)
	{
		p_board_ai->m_iLastError = iLastError;
	}
}

void CAnalogInputPP :: ScanTerminate(short* psValues, unsigned int uiNumberOfValues, 
													void* pTerminateContext, int iLastError)
{
	SMEBoardAI* p_board_ai = (SMEBoardAI*)pTerminateContext;

	p_board_ai->m_bAIActive = FALSE;

	p_board_ai->m_uiCurrentNumberofChanLists = uiNumberOfValues / p_board_ai->m_uiCurrentNumberOfChannels;

	p_board_ai->m_pAnalogInputPP->SetRedraw(FALSE);

	p_board_ai->m_pAnalogInputPP->m_progressScan.ShowWindow(SW_HIDE);

	p_board_ai->m_pAnalogInputPP->SetRedraw(TRUE);
	
	p_board_ai->m_pAnalogInputPP->InvalidateRect(p_board_ai->m_pAnalogInputPP->m_rectPlotChild, TRUE);

	p_board_ai->m_pAnalogInputPP->GetDlgItem(ID_STOP)->EnableWindow(FALSE);

	p_board_ai->m_pAnalogInputPP->GetDlgItem(ID_START_SAMPLE)->EnableWindow(TRUE);

	if(iLastError != ME4000_NO_ERROR)
	{
		p_board_ai->m_iLastError = iLastError;
	}
}

void CAnalogInputPP :: ContinuousCallback(short* psValues, unsigned int uiNumberOfValues, 
													void* pCallbackContext, int iLastError)
{
	SMEBoardAI* p_board_ai = (SMEBoardAI*)pCallbackContext;

	if(iLastError != ME4000_NO_ERROR)
	{
		p_board_ai->m_iLastError = iLastError;

		p_board_ai->m_pAnalogInputPP->OnStop();

		p_board_ai->m_pAnalogInputPP->InvalidateRect(p_board_ai->m_pAnalogInputPP->m_rectPlotChild, TRUE);
	}

	if(uiNumberOfValues == 0)
	{
		return;
	}
	
	CClientDC dc(p_board_ai->m_pAnalogInputPP->m_pPlotWin);
	
	dc.IntersectClipRect(p_board_ai->m_pAnalogInputPP->m_rectPlotClient);
	
	CRect rect_erase = p_board_ai->m_pAnalogInputPP->m_rectPlotClient;
	
	CPen* p_old_pen = (CPen*)dc.SelectStockObject(BLACK_PEN);

	int no_of_frames = uiNumberOfValues / p_board_ai->m_uiCurrentNumberOfChannels;
	
	if( !p_board_ai->m_bFirstDraw )
	{
		dc.MoveTo(p_board_ai->m_iXLastPixel + 1, p_board_ai->m_pAnalogInputPP->m_rectPlotClient.top);
		dc.LineTo(p_board_ai->m_iXLastPixel + 1, p_board_ai->m_pAnalogInputPP->m_rectPlotClient.bottom);

		int erase_from_pixel = p_board_ai->m_iXLastPixel + 1;
		
		int erase_to_pixel = (int)(p_board_ai->m_iXLastPixel + (double)no_of_frames * p_board_ai->m_dXIncrement);

		if(erase_to_pixel > erase_from_pixel)
		{
			if( erase_to_pixel > p_board_ai->m_pAnalogInputPP->m_rectPlotClient.right )
			{
				rect_erase.left = erase_from_pixel;
				
				dc.FillSolidRect( rect_erase, RGB(0, 0, 0) );

				erase_from_pixel = p_board_ai->m_pAnalogInputPP->m_rectPlotClient.left;
				erase_to_pixel-= p_board_ai->m_pAnalogInputPP->m_rectPlotClient.Width();
			}

			rect_erase.left = erase_from_pixel;
				
			rect_erase.right = erase_to_pixel + 2;
				
			dc.FillSolidRect( rect_erase, RGB(0, 0, 0) );
		}
	}

	double d_current_pix;
	
	int old_x_pix;
	
	short* p_data_buffer = new short[no_of_frames];
		
	for(unsigned int index_channel = 0; index_channel < p_board_ai->m_uiCurrentNumberOfChannels; index_channel++)
	{
		CPen pen_draw( PS_SOLID, 0, p_board_ai->m_crCurrentChanColours[index_channel] );
		
		CPen* p_old_draw_pen =  (CPen*)dc.SelectObject(&pen_draw);
		
		old_x_pix = p_board_ai->m_iXLastPixel;
		
		d_current_pix = p_board_ai->m_dXLastPixel;
		
		unsigned long ul_no_of_values;
		
		me4000AIExtractValues(	p_board_ai->m_uiCurrentChanNumber[index_channel],			// uiChannelNumber,
								psValues,													// psAIBuffer,
								no_of_frames * p_board_ai->m_uiCurrentNumberOfChannels,		// unsigned long ulAIDataCount,
								&p_board_ai->m_ucChanList[0],								// pucChanList,
								p_board_ai->m_uiCurrentNumberOfChannels,					// uiChanListCount,
								p_data_buffer,												// psChanBuffer,
								no_of_frames,												// ulChanBufferSizeValues,
								&ul_no_of_values										);	// pulChanDataCount
				
		short* p_data = p_data_buffer;
		
		for(unsigned long frame = 0; frame < ul_no_of_values; frame++)
		{
			int x_pix = (int)d_current_pix;
				
			double d_volt;

			me4000AIDigitToVolt(*p_data,							// sDigit,
								p_board_ai->m_iChannelRange[0],		// iRange
								&d_volt							);	// pdVolt

			int y_pix = (int)( d_volt * p_board_ai->m_dYFactor[index_channel] + p_board_ai->m_dYConstant[index_channel] );

			if( (frame == 0)&&(!p_board_ai->m_bFirstDraw) )
			{
				dc.MoveTo(old_x_pix, p_board_ai->m_iYLastPixel[index_channel] );
			}

			if(!p_board_ai->m_bFirstDraw)
			{
				if( (x_pix != old_x_pix)||( y_pix != p_board_ai->m_iYLastPixel[index_channel] ) )
				{
					dc.LineTo(x_pix, y_pix);
					
					old_x_pix = x_pix;
					
					p_board_ai->m_iYLastPixel[index_channel] = y_pix;
				}
			}
			else
			{
				dc.MoveTo(x_pix, y_pix);
				
				old_x_pix = x_pix;
				
				p_board_ai->m_iYLastPixel[index_channel] = y_pix;

				p_board_ai->m_bFirstDraw = FALSE;
			}

			++p_data;
			
			d_current_pix+= p_board_ai->m_dXIncrement;

			if( (int)d_current_pix > p_board_ai->m_pAnalogInputPP->m_rectPlotClient.right )
			{
				d_current_pix-= p_board_ai->m_pAnalogInputPP->m_rectPlotClient.Width();

				old_x_pix-= p_board_ai->m_pAnalogInputPP->m_rectPlotClient.Width();

				dc.MoveTo(old_x_pix, p_board_ai->m_iYLastPixel[index_channel] );
			}
		}

		dc.SelectObject(p_old_draw_pen);
	}
	
	delete p_data_buffer;
	
	p_board_ai->m_dXLastPixel = d_current_pix;

	p_board_ai->m_iXLastPixel = old_x_pix;
	
	dc.SelectStockObject(WHITE_PEN);

	dc.MoveTo(p_board_ai->m_iXLastPixel + 1, p_board_ai->m_pAnalogInputPP->m_rectPlotClient.top);
	dc.LineTo(p_board_ai->m_iXLastPixel + 1, p_board_ai->m_pAnalogInputPP->m_rectPlotClient.bottom);

	dc.SelectObject(p_old_pen);
	
	p_board_ai->m_bFirstDraw = FALSE;
}


void CAnalogInputPP::SetControlStates(void)
{
	Cme4000App* p_app = (Cme4000App*)AfxGetApp();

	ME4000Board* p_boards = p_app->GetBoardArray();

	CString cs_text;
	
	cs_text.Format( "%04X", p_boards[m_iCurrentBoardIndex].m_usDeviceID );
	
	SetDlgItemText(IDC_BOARD_VERSION, cs_text);
	
	cs_text.Format( "%08X", p_boards[m_iCurrentBoardIndex].m_ulSerialNumber );
	
	SetDlgItemText(IDC_SERIAL_NUMBER, cs_text);

	for(int index_combo = 0; index_combo < 4; index_combo++)
	{
		m_comboNumberChannel[index_combo].ResetContent();
	}
	
	for(int index_channel = 0; index_channel < 32; index_channel++)
	{
		CString cs_text;

		cs_text.Format("Channel %2d", index_channel + 1);
		
		for(index_combo = 0; index_combo < 4; index_combo++)
		{
			m_comboNumberChannel[index_combo].AddString(cs_text);
		}
	}

	for(index_combo = 0; index_combo < 4; index_combo++)
	{
		m_comboNumberChannel[index_combo].SetCurSel( m_sBoardAI[m_iCurrentBoardIndex].m_uiChannelNumber[index_combo] );
	}
	
	switch(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction)
	{
	case AI_SINGLE:

		OnRadioAISingle();

		break;

	case AI_SCAN:

		OnRadioAIScan();

		break;

	case AI_CONTINUOUS:

		OnRadioAIContinuous();

		break;
	}

	if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction != AI_SINGLE)
	{
		OnCheckChannel1();

		OnCheckChannel2();

		OnCheckChannel3();

		OnCheckChannel4();
	}
}


BEGIN_MESSAGE_MAP(CAnalogInputPP, CPropertyPage)
	//{{AFX_MSG_MAP(CAnalogInputPP)
	ON_BN_CLICKED(ID_EXIT, OnExit)
	ON_BN_CLICKED(IDC_RADIO_AI_SINGLE, OnRadioAISingle)
	ON_BN_CLICKED(IDC_RADIO_AI_SCAN, OnRadioAIScan)
	ON_BN_CLICKED(IDC_RADIO_AI_CONTINUOUS, OnRadioAIContinuous)
	ON_BN_CLICKED(IDC_CHECK_CHANNEL_1, OnCheckChannel1)
	ON_BN_CLICKED(IDC_CHECK_CHANNEL_2, OnCheckChannel2)
	ON_BN_CLICKED(IDC_CHECK_CHANNEL_3, OnCheckChannel3)
	ON_BN_CLICKED(IDC_CHECK_CHANNEL_4, OnCheckChannel4)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_TYPE_ANALOG, OnRadioTriggerTypeAnalog)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_TYPE_DIGITAL, OnRadioTriggerTypeDigital)
	ON_BN_CLICKED(IDC_RADIO_TRIGGER_TYPE_SOFTWARE, OnRadioTriggerTypeSoftware)
	ON_BN_CLICKED(IDC_RADIO_CONT_SW, OnRadioContSw)
	ON_BN_CLICKED(IDC_RADIO_CONT_ET, OnRadioContEt)
	ON_BN_CLICKED(IDC_RADIO_CONT_ET_VALUE, OnRadioContEtValue)
	ON_BN_CLICKED(IDC_RADIO_CONT_ET_CHANLIST, OnRadioContEtChanlist)
	ON_BN_CLICKED(ID_START_SAMPLE, OnStartSample)
	ON_BN_CLICKED(ID_STOP, OnStop)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalogInputPP message handlers

BOOL CAnalogInputPP::OnInitDialog() 
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

	m_cbChannel[0].SubclassDlgItem(IDC_COLOUR_CHANNEL_1, this);
	
	m_cbChannel[1].SubclassDlgItem(IDC_COLOUR_CHANNEL_2, this);
	
	m_cbChannel[2].SubclassDlgItem(IDC_COLOUR_CHANNEL_3, this);
	
	m_cbChannel[3].SubclassDlgItem(IDC_COLOUR_CHANNEL_4, this);

	m_spinTimeout.SetRange32(0, 300);

	m_spinSampleRate.SetRange32(1, 500000);

	m_spinNoOfChannelLists.SetRange32(1, 1000000);

	m_spinRefresh.SetRange32(1, 100000);

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

void CAnalogInputPP::OnExit() 
{
	// TODO: Add your control notification handler code here
	
	if(AfxMessageBox("This will terminate the test programm", MB_OKCANCEL) == IDOK)
	{
		m_pPropertySheet->EndDialog(0);
	}
}

void CAnalogInputPP::OnRadioAISingle() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_CHECK_CHANNEL_1)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_NUMBER_CHANNEL_1)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RANGE_CHANNEL_1)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_CHECK_CHANNEL_2)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_NUMBER_CHANNEL_2)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RANGE_CHANNEL_2)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_CHECK_CHANNEL_3)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_NUMBER_CHANNEL_3)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RANGE_CHANNEL_3)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_CHECK_CHANNEL_4)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_NUMBER_CHANNEL_4)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RANGE_CHANNEL_4)->EnableWindow(FALSE);

	SetDlgItemText(IDC_STATIC_TRIGGER, "Trigger");

	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_SOFTWARE)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_DIGITAL)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_ANALOG)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECONDS)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPIN_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_NO_OF_CHANNEL_LISTS)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPIN_NO_OF_CHANNEL_LISTS)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO_CONT_SW)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO_CONT_ET)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO_CONT_ET_VALUE)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO_CONT_ET_CHANLIST)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPIN_REFRESH)->EnableWindow(FALSE);

	if(m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode == ME4000_AI_TRIGGER_SOFTWARE)
	{
		GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(FALSE);

		GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);

		GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(TRUE);
	}

	GetDlgItem(IDC_CHECK_SAMPLE_AND_HOLD)->EnableWindow(FALSE);

	SetDlgItemText(ID_START_SAMPLE, "Sample");

	GetDlgItem(ID_STOP)->EnableWindow(FALSE);

	if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction != AI_SINGLE)
	{
		int i_trigger_type;

		CDataExchange dx_read(this, TRUE);
		
		DDX_Radio(&dx_read, IDC_RADIO_TRIGGER_TYPE_SOFTWARE, i_trigger_type);

		switch(i_trigger_type)
		{
		case 1:

			m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtMode = ME4000_AI_TRIGGER_EXT_DIGITAL;

			break;

		case 2:

			m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtMode = ME4000_AI_TRIGGER_EXT_ANALOG;

			break;
		}
		
		switch(m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode)
		{
		case ME4000_AI_TRIGGER_SOFTWARE:

			i_trigger_type = 0;

			break;

		case ME4000_AI_TRIGGER_EXT_DIGITAL:

			i_trigger_type = 1;

			break;

		case ME4000_AI_TRIGGER_EXT_ANALOG:

			i_trigger_type = 2;

			break;
		}

		CDataExchange dx_write(this, FALSE);
		
		DDX_Radio(&dx_write, IDC_RADIO_TRIGGER_TYPE_SOFTWARE, i_trigger_type);
	}

	m_sBoardAI[m_iCurrentBoardIndex].m_iFunction = AI_SINGLE;
}

void CAnalogInputPP::OnRadioAIScan() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_CHECK_CHANNEL_1)->EnableWindow(TRUE);
	
	if( IsDlgButtonChecked(IDC_CHECK_CHANNEL_1) == BST_CHECKED )
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_1)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_1)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_1)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_1)->EnableWindow(FALSE);
	}
	
	GetDlgItem(IDC_CHECK_CHANNEL_2)->EnableWindow(TRUE);
	
	if( IsDlgButtonChecked(IDC_CHECK_CHANNEL_2) == BST_CHECKED )
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_2)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_2)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_2)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_2)->EnableWindow(FALSE);
	}
	
	GetDlgItem(IDC_CHECK_CHANNEL_3)->EnableWindow(TRUE);
	
	if( IsDlgButtonChecked(IDC_CHECK_CHANNEL_3) == BST_CHECKED )
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_3)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_3)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_3)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_3)->EnableWindow(FALSE);
	}
	
	GetDlgItem(IDC_CHECK_CHANNEL_4)->EnableWindow(TRUE);
	
	if( IsDlgButtonChecked(IDC_CHECK_CHANNEL_4) == BST_CHECKED )
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_4)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_4)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_4)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_4)->EnableWindow(FALSE);
	}
	
	SetDlgItemText(IDC_STATIC_TRIGGER, "External Trigger");

	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_SOFTWARE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECONDS)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_NO_OF_CHANNEL_LISTS)->EnableWindow(TRUE);

	GetDlgItem(IDC_SPIN_NO_OF_CHANNEL_LISTS)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_CONT_SW)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_CONT_ET)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_CONT_ET_VALUE)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_CONT_ET_CHANLIST)->EnableWindow(TRUE);

	if( (m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode == ME4000_AI_ACQ_MODE_SOFTWARE)||
				(m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode == ME4000_AI_ACQ_MODE_EXT) )
	{
		GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(TRUE);

		GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_REFRESH)->EnableWindow(FALSE);

		GetDlgItem(IDC_SPIN_REFRESH)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(FALSE);

		GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_REFRESH)->EnableWindow(TRUE);

		GetDlgItem(IDC_SPIN_REFRESH)->EnableWindow(TRUE);
	}

	if(m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode == ME4000_AI_ACQ_MODE_SOFTWARE)
	{
		GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(FALSE);

		GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_TRIGGER_TYPE_DIGITAL)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_TRIGGER_TYPE_ANALOG)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);

		GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_TRIGGER_TYPE_DIGITAL)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_TRIGGER_TYPE_ANALOG)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(TRUE);
	}

	GetDlgItem(IDC_CHECK_SAMPLE_AND_HOLD)->EnableWindow(TRUE);

	SetDlgItemText(ID_START_SAMPLE, "Start");

	if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_SINGLE)
	{
		int i_trigger_type;

		CDataExchange dx_read(this, TRUE);
		
		DDX_Radio(&dx_read, IDC_RADIO_TRIGGER_TYPE_SOFTWARE, i_trigger_type);

		switch(i_trigger_type)
		{
		case 0:

			m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode = ME4000_AI_TRIGGER_SOFTWARE;

			break;

		case 1:

			m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode = ME4000_AI_TRIGGER_EXT_DIGITAL;

			break;

		case 2:

			m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode = ME4000_AI_TRIGGER_EXT_ANALOG;

			break;
		}
		
		switch(m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtMode)
		{
		case ME4000_AI_TRIGGER_EXT_DIGITAL:

			i_trigger_type = 1;

			break;

		case ME4000_AI_TRIGGER_EXT_ANALOG:

			i_trigger_type = 2;

			break;
		}

		CDataExchange dx_write(this, FALSE);
		
		DDX_Radio(&dx_write, IDC_RADIO_TRIGGER_TYPE_SOFTWARE, i_trigger_type);
	}

	m_sBoardAI[m_iCurrentBoardIndex].m_iFunction = AI_SCAN;
}

void CAnalogInputPP::OnRadioAIContinuous() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_CHECK_CHANNEL_1)->EnableWindow(TRUE);
	
	if( IsDlgButtonChecked(IDC_CHECK_CHANNEL_1) == BST_CHECKED )
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_1)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_1)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_1)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_1)->EnableWindow(FALSE);
	}
	
	GetDlgItem(IDC_CHECK_CHANNEL_2)->EnableWindow(TRUE);
	
	if( IsDlgButtonChecked(IDC_CHECK_CHANNEL_2) == BST_CHECKED )
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_2)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_2)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_2)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_2)->EnableWindow(FALSE);
	}
	
	GetDlgItem(IDC_CHECK_CHANNEL_3)->EnableWindow(TRUE);
	
	if( IsDlgButtonChecked(IDC_CHECK_CHANNEL_3) == BST_CHECKED )
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_3)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_3)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_3)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_3)->EnableWindow(FALSE);
	}
	
	GetDlgItem(IDC_CHECK_CHANNEL_4)->EnableWindow(TRUE);
	
	if( IsDlgButtonChecked(IDC_CHECK_CHANNEL_4) == BST_CHECKED )
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_4)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_4)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_NUMBER_CHANNEL_4)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_RANGE_CHANNEL_4)->EnableWindow(FALSE);
	}
	
	SetDlgItemText(IDC_STATIC_TRIGGER, "External Trigger");

	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_SOFTWARE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_NO_OF_CHANNEL_LISTS)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPIN_NO_OF_CHANNEL_LISTS)->EnableWindow(FALSE);

	GetDlgItem(IDC_RADIO_CONT_SW)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_CONT_ET)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_CONT_ET_VALUE)->EnableWindow(TRUE);

	GetDlgItem(IDC_RADIO_CONT_ET_CHANLIST)->EnableWindow(TRUE);

	if( (m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode == ME4000_AI_ACQ_MODE_SOFTWARE)||
				(m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode == ME4000_AI_ACQ_MODE_EXT) )
	{
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECONDS)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(TRUE);

		GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_REFRESH)->EnableWindow(FALSE);

		GetDlgItem(IDC_SPIN_REFRESH)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECONDS)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(FALSE);

		GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_REFRESH)->EnableWindow(TRUE);

		GetDlgItem(IDC_SPIN_REFRESH)->EnableWindow(TRUE);
	}

	if(m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode == ME4000_AI_ACQ_MODE_SOFTWARE)
	{
		GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(FALSE);

		GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_TRIGGER_TYPE_DIGITAL)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_TRIGGER_TYPE_ANALOG)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(FALSE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);

		GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_TRIGGER_TYPE_DIGITAL)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_TRIGGER_TYPE_ANALOG)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(TRUE);

		GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(TRUE);
	}

	GetDlgItem(IDC_CHECK_SAMPLE_AND_HOLD)->EnableWindow(TRUE);

	SetDlgItemText(ID_START_SAMPLE, "Start");

	if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_SINGLE)
	{
		int i_trigger_type;

		CDataExchange dx_read(this, TRUE);
		
		DDX_Radio(&dx_read, IDC_RADIO_TRIGGER_TYPE_SOFTWARE, i_trigger_type);

		switch(i_trigger_type)
		{
		case 0:

			m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode = ME4000_AI_TRIGGER_SOFTWARE;

			break;

		case 1:

			m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode = ME4000_AI_TRIGGER_EXT_DIGITAL;

			break;

		case 2:

			m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode = ME4000_AI_TRIGGER_EXT_ANALOG;

			break;
		}

		switch(m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtMode)
		{
		case ME4000_AI_TRIGGER_EXT_DIGITAL:

			i_trigger_type = 1;

			break;

		case ME4000_AI_TRIGGER_EXT_ANALOG:

			i_trigger_type = 2;

			break;
		}

		CDataExchange dx_write(this, FALSE);
		
		DDX_Radio(&dx_write, IDC_RADIO_TRIGGER_TYPE_SOFTWARE, i_trigger_type);
	}
	
	m_sBoardAI[m_iCurrentBoardIndex].m_iFunction = AI_CONTINUOUS;
}

void CAnalogInputPP::OnCheckChannel1() 
{
	// TODO: Add your control notification handler code here
	
	BOOL b_enable = IsDlgButtonChecked(IDC_CHECK_CHANNEL_1);

	GetDlgItem(IDC_NUMBER_CHANNEL_1)->EnableWindow(b_enable);

	GetDlgItem(IDC_RANGE_CHANNEL_1)->EnableWindow(b_enable);
}

void CAnalogInputPP::OnCheckChannel2() 
{
	// TODO: Add your control notification handler code here
	
	BOOL b_enable = IsDlgButtonChecked(IDC_CHECK_CHANNEL_2);

	GetDlgItem(IDC_NUMBER_CHANNEL_2)->EnableWindow(b_enable);

	GetDlgItem(IDC_RANGE_CHANNEL_2)->EnableWindow(b_enable);
}

void CAnalogInputPP::OnCheckChannel3() 
{
	// TODO: Add your control notification handler code here
	
	BOOL b_enable = IsDlgButtonChecked(IDC_CHECK_CHANNEL_3);

	GetDlgItem(IDC_NUMBER_CHANNEL_3)->EnableWindow(b_enable);

	GetDlgItem(IDC_RANGE_CHANNEL_3)->EnableWindow(b_enable);
}

void CAnalogInputPP::OnCheckChannel4() 
{
	// TODO: Add your control notification handler code here
	
	BOOL b_enable = IsDlgButtonChecked(IDC_CHECK_CHANNEL_4);

	GetDlgItem(IDC_NUMBER_CHANNEL_4)->EnableWindow(b_enable);

	GetDlgItem(IDC_RANGE_CHANNEL_4)->EnableWindow(b_enable);
}

void CAnalogInputPP::OnRadioTriggerTypeSoftware() 
{
	// TODO: Add your control notification handler code here

	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(FALSE);
}

void CAnalogInputPP::OnRadioTriggerTypeAnalog() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(TRUE);

	if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_SINGLE)
	{
		GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(TRUE);
	}
}

void CAnalogInputPP::OnRadioTriggerTypeDigital() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(TRUE);

	if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_SINGLE)
	{
		GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(TRUE);
	}
}

void CAnalogInputPP::OnRadioContSw() 
{
	// TODO: Add your control notification handler code here
	
	if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_CONTINUOUS)
	{
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECONDS)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);
	}

	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_DIGITAL)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_ANALOG)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(TRUE);

	GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPIN_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(FALSE);

	m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode = ME4000_AI_ACQ_MODE_SOFTWARE;
}

void CAnalogInputPP::OnRadioContEt() 
{
	// TODO: Add your control notification handler code here
	
	if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_CONTINUOUS)
	{
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECONDS)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);
	}

	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_DIGITAL)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_ANALOG)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(TRUE);

	GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPIN_REFRESH)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);

	GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(TRUE);

	m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode = ME4000_AI_ACQ_MODE_EXT;
}

void CAnalogInputPP::OnRadioContEtValue() 
{
	// TODO: Add your control notification handler code here
	
	if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_CONTINUOUS)
	{
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECONDS)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(TRUE);
	}

	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_DIGITAL)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_ANALOG)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_REFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDC_SPIN_REFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);

	GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(TRUE);

	m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode = ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE;
}

void CAnalogInputPP::OnRadioContEtChanlist() 
{
	// TODO: Add your control notification handler code here
	
	if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_CONTINUOUS)
	{
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECONDS)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(TRUE);
	}

	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_DIGITAL)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_TRIGGER_TYPE_ANALOG)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_RISING)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_FALLING)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_EXT_TRIGGER_EDGE_BOTH)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(FALSE);

	GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_REFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDC_SPIN_REFRESH)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_TIMEOUT)->EnableWindow(TRUE);

	GetDlgItem(IDC_SPIN_TIMEOUT)->EnableWindow(TRUE);

	m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode = ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST;
}

void CAnalogInputPP::OnStartSample() 
{
	// TODO: Add your control notification handler code here
	
	CDataExchange dx(this, TRUE);
	
	DoDataExchange(&dx);
	
	CClientDC dc(m_pPlotWin);

	if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_SINGLE)
	{
		short s_digit;

		int i_ext_trigger_edge = m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtEdge;

		unsigned long ul_timeout = m_sBoardAI[m_iCurrentBoardIndex].m_ulTimeout;

		if(m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode == ME4000_AI_TRIGGER_SOFTWARE)
		{
			i_ext_trigger_edge = ME4000_VALUE_NOT_USED;

			ul_timeout = ME4000_VALUE_NOT_USED;
		}
		
		if(m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode != ME4000_AI_TRIGGER_SOFTWARE)
		{
			dc.FillSolidRect( m_rectPlotClient, RGB(0, 0, 0) );

			dc.SetTextColor( channel_colors[0] );

			dc.SetBkMode(TRANSPARENT);

			CFont font_text;

			font_text.CreateFontIndirect(&lf_text);

			CFont* p_old_font = dc.SelectObject(&font_text);
    
			dc.DrawText("Waiting for Trigger", m_rectPlotClient, DT_SINGLELINE | DT_CENTER | DT_VCENTER); 
		
			dc.SelectObject(p_old_font);
		}
		
		GetDlgItem(ID_START_SAMPLE)->EnableWindow(FALSE);

		m_sBoardAI[m_iCurrentBoardIndex].m_bAIActive = TRUE;
		
		int i_error = me4000AISingle(	m_iCurrentBoardIndex,										// uiBoardNumber,
										m_sBoardAI[m_iCurrentBoardIndex].m_uiChannelNumber[0],		// uiChannelNumber,
										m_sBoardAI[m_iCurrentBoardIndex].m_iChannelRange[0],		// iRange,
										m_sBoardAI[m_iCurrentBoardIndex].m_iSDMode,					// iSDMode,
										m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerSingleMode, 		// iTriggerMode,
										i_ext_trigger_edge,											// iExtTriggerEdge,
										ul_timeout,													// ulTimeOutSeconds,
										&s_digit													);	// psDigitalValue

		m_sBoardAI[m_iCurrentBoardIndex].m_iLastError = ME4000_NO_ERROR;
			
		if(i_error == ME4000_NO_ERROR)
		{
			me4000AIDigitToVolt(s_digit,														// sDigit,
								m_sBoardAI[m_iCurrentBoardIndex].m_iChannelRange[0],		// iRange
								&m_sBoardAI[m_iCurrentBoardIndex].m_sSingleValueVolt	);	// pdVolt

			m_sBoardAI[m_iCurrentBoardIndex].m_uiSingleChannel = m_sBoardAI[m_iCurrentBoardIndex].m_uiChannelNumber[0];
			
			m_sBoardAI[m_iCurrentBoardIndex].m_iLastOperation = AI_SINGLE;
		}
		else
		{
			m_sBoardAI[m_iCurrentBoardIndex].m_sSingleValueVolt = 0.0;

			m_sBoardAI[m_iCurrentBoardIndex].m_iLastOperation = AI_NONE;
		}
		
		InvalidateRect(m_rectPlotChild);
		
		m_sBoardAI[m_iCurrentBoardIndex].m_bAIActive = FALSE;
		
		GetDlgItem(ID_START_SAMPLE)->EnableWindow(TRUE);
	}
	else
	{
		int disp_channel = 0;
		
		for(int index_channel = 0; index_channel < 4; index_channel++)
		{
			if( m_sBoardAI[m_iCurrentBoardIndex].m_bChannelActive[index_channel] )
			{
				m_sBoardAI[m_iCurrentBoardIndex].m_crCurrentChanColours[disp_channel] = channel_colors[index_channel];
				
				m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentChanNumber[disp_channel] = m_sBoardAI[m_iCurrentBoardIndex].m_uiChannelNumber[index_channel];
				
				m_sBoardAI[m_iCurrentBoardIndex].m_iCurrentChanRange[disp_channel] = m_sBoardAI[m_iCurrentBoardIndex].m_iChannelRange[index_channel];
				
				me4000AIMakeChannelListEntry(	m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentChanNumber[disp_channel],	// uiChannelNumber,
												m_sBoardAI[m_iCurrentBoardIndex].m_iCurrentChanRange[disp_channel],		// int iRange,
												&m_sBoardAI[m_iCurrentBoardIndex].m_ucChanList[disp_channel]		);	// pucChanListEntry

				double d_min;

				double d_max;

				switch( m_sBoardAI[m_iCurrentBoardIndex].m_iCurrentChanRange[disp_channel] )
				{
				case ME4000_AI_RANGE_BIPOLAR_10:

					d_min = -10.0;
					d_max = +10.0;

					break;

				case ME4000_AI_RANGE_BIPOLAR_2_5:

					d_min = -2.5;
					d_max = +2.5;

					break;

				case ME4000_AI_RANGE_UNIPOLAR_10:

					d_min = 0;
					d_max = +10.0;

					break;

				case ME4000_AI_RANGE_UNIPOLAR_2_5:

					d_min = 0;
					d_max = +2.5;

					break;
				}

				m_sBoardAI[m_iCurrentBoardIndex].m_dYFactor[disp_channel] = (double)(m_rectPlotClient.Height() - 20) / (d_min - d_max);
				
				m_sBoardAI[m_iCurrentBoardIndex].m_dYConstant[disp_channel] = (double)(m_rectPlotClient.top + 10) - d_max * m_sBoardAI[m_iCurrentBoardIndex].m_dYFactor[disp_channel];
				
				++disp_channel;
			}

			if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_CONTINUOUS)
			{
				if( (m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode == ME4000_AI_ACQ_MODE_SOFTWARE)||
								(m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode == ME4000_AI_ACQ_MODE_EXT) )		
				{
					// m_dXIncrement determined by sample rate and window width in seconds
					
					m_sBoardAI[m_iCurrentBoardIndex].m_dXIncrement = 
											(double)m_rectPlotClient.Width() / 
												( m_sBoardAI[m_iCurrentBoardIndex].m_dSampleRate * m_sBoardAI[m_iCurrentBoardIndex].m_dWindowWidthSeconds);
				}
				else 
				{
					// External trigger m_dXIncrement determined by window width in values
					
					m_sBoardAI[m_iCurrentBoardIndex].m_dXIncrement = (double)m_rectPlotClient.Width() / (double)(m_sBoardAI[m_iCurrentBoardIndex].m_uiWindowWidthValues - 1);
				}
			}
		}
		
		m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentNumberOfChannels = disp_channel;
		
		int i_simultaneous = 0;
		
		if(m_sBoardAI[m_iCurrentBoardIndex].m_bSampleAndHold)
		{
			i_simultaneous = ME4000_AI_SIMULTANEOUS_ENABLE;
		}
		else
		{
			i_simultaneous = ME4000_AI_SIMULTANEOUS_DISABLE;
		}

		unsigned long ul_scan_ticks_low = ME4000_VALUE_NOT_USED;		
		
		unsigned long ul_scan_ticks_high = ME4000_VALUE_NOT_USED;

		unsigned int ui_refresh = 0;

		if( (m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode == ME4000_AI_ACQ_MODE_SOFTWARE)||
						(m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode == ME4000_AI_ACQ_MODE_EXT) )
		{
			me4000FrequencyToTicks(	m_sBoardAI[m_iCurrentBoardIndex].m_dSampleRate,		// dRequiredFreq,
									&ul_scan_ticks_low,									// pulTicksLowPart,
									&ul_scan_ticks_high,									// pulTicksHighPart,
									NULL											);	// pdAchievedFreq - not required

			ui_refresh = (unsigned int)(m_sBoardAI[m_iCurrentBoardIndex].m_dSampleRate / 10 ); // Refresh 10 Hz
		}
		else
		{
			ui_refresh = m_sBoardAI[m_iCurrentBoardIndex].m_uiRefresh;
		}

		if(ui_refresh < 1)
		{
			ui_refresh = 1;
		}

		int i_ext_trigger_mode = ME4000_VALUE_NOT_USED;

		int i_ext_trigger_edge = ME4000_VALUE_NOT_USED;

		unsigned long ul_timeout = ME4000_VALUE_NOT_USED;

		if(m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode != ME4000_AI_ACQ_MODE_SOFTWARE)
		{
			i_ext_trigger_mode = m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtMode;

			i_ext_trigger_edge = m_sBoardAI[m_iCurrentBoardIndex].m_iTriggerExtEdge;

			ul_timeout = m_sBoardAI[m_iCurrentBoardIndex].m_ulTimeout;
		}

		if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_SCAN)
		{
			unsigned long ul_buffer_size_values = m_sBoardAI[m_iCurrentBoardIndex].m_uiNumberOfChannelLists * 
															m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentNumberOfChannels;

			if(ul_buffer_size_values > m_sBoardAI[m_iCurrentBoardIndex].m_uiScanBufferSizeValues)
			{
				if(m_sBoardAI[m_iCurrentBoardIndex].m_psScanBuffer != NULL)
				{
					delete m_sBoardAI[m_iCurrentBoardIndex].m_psScanBuffer;
				}

				m_sBoardAI[m_iCurrentBoardIndex].m_iLastOperation = AI_NONE;

				m_sBoardAI[m_iCurrentBoardIndex].m_psScanBuffer = NULL;
			
				m_sBoardAI[m_iCurrentBoardIndex].m_uiScanBufferSizeValues = 0;
				
				m_sBoardAI[m_iCurrentBoardIndex].m_psScanBuffer = new short[ul_buffer_size_values];

				if(m_sBoardAI[m_iCurrentBoardIndex].m_psScanBuffer == NULL)
				{
					AfxMessageBox("Unable to allocate AIScan buffer");
					
					return;
				}

				m_sBoardAI[m_iCurrentBoardIndex].m_uiScanBufferSizeValues = ul_buffer_size_values;
			}
			
			int i_error = me4000AIConfig(	m_iCurrentBoardIndex,											// uiBoardNumber,
											&m_sBoardAI[m_iCurrentBoardIndex].m_ucChanList[0],				// pucChanList
											m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentNumberOfChannels,	// uiChanListCount
											m_sBoardAI[m_iCurrentBoardIndex].m_iSDMode,						// iSDMode
											i_simultaneous,													// iSimultaneous,
											ME4000_VALUE_NOT_USED,											// ulReserved,
											0,																// ulChanTicks,
											ul_scan_ticks_low,												// ulScanTicksLow,
											ul_scan_ticks_high,												// ulScanTicksHigh,
											m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode,			// iAcqMode,
											i_ext_trigger_mode,												// iExtTriggerMode,
											i_ext_trigger_edge											);	// iExtTriggerEdge

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}
			
			i_error = me4000AIScan(	m_iCurrentBoardIndex,											// uiBoardNumber,
									m_sBoardAI[m_iCurrentBoardIndex].m_uiNumberOfChannelLists,		// uiNumberOfChanLists,
									m_sBoardAI[m_iCurrentBoardIndex].m_psScanBuffer,					// psBuffer,
									ul_buffer_size_values,											// ulBufferSizeValues,
									ME4000_AI_SCAN_ASYNCHRONOUS,									// iExecutionMode,
									ScanCallback,													// pCallbackProc,
									&m_sBoardAI[m_iCurrentBoardIndex],								// pCallbackContext,
									ui_refresh,														// uiRefreshFrequency,
									ScanTerminate,													// pTerminateProc
									&m_sBoardAI[m_iCurrentBoardIndex],								// pTermianteContext,
									ul_timeout													);	// ulTimeOutSeconds

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}
			
			m_sBoardAI[m_iCurrentBoardIndex].m_uiNumberOfScanData = 0;
			
			m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentNumberofChanLists = m_sBoardAI[m_iCurrentBoardIndex].m_uiNumberOfChannelLists;
			
			m_sBoardAI[m_iCurrentBoardIndex].m_iLastError = ME4000_NO_ERROR;
			
			i_error = me4000AIStart(m_iCurrentBoardIndex);	// uiBoardNumber
			
			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}
			
			GetDlgItem(ID_START_SAMPLE)->EnableWindow(FALSE);
			
			GetDlgItem(ID_STOP)->EnableWindow(TRUE);
			
			m_progressScan.SetRange32(0, ul_buffer_size_values);

			m_progressScan.SetPos(0);

			m_progressScan.ShowWindow(SW_SHOW);

			m_sBoardAI[m_iCurrentBoardIndex].m_iLastOperation = AI_SCAN;

			m_sBoardAI[m_iCurrentBoardIndex].m_bAIActive = TRUE;
		}
		else if(m_sBoardAI[m_iCurrentBoardIndex].m_iFunction == AI_CONTINUOUS)
		{
			int i_error = me4000AIConfig(	m_iCurrentBoardIndex,											// uiBoardNumber,
											&m_sBoardAI[m_iCurrentBoardIndex].m_ucChanList[0],				// pucChanList
											m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentNumberOfChannels,	// uiChanListCount
											m_sBoardAI[m_iCurrentBoardIndex].m_iSDMode,						// iSDMode
											i_simultaneous,													// iSimultaneous,
											ME4000_VALUE_NOT_USED,											// ulReserved,
											0,																// ulChanTicks,
											ul_scan_ticks_low,												// ulScanTicksLow,
											ul_scan_ticks_high,												// ulScanTicksHigh,
											m_sBoardAI[m_iCurrentBoardIndex].m_iAcquisitionMode,			// iAcqMode,
											i_ext_trigger_mode,												// iExtTriggerMode,
											i_ext_trigger_edge											);	// iExtTriggerEdge

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}

			i_error = me4000AIContinuous(	m_iCurrentBoardIndex,											// uiBoardNumber,
											ContinuousCallback,												// pCallbackProc,
											&m_sBoardAI[m_iCurrentBoardIndex],								// pCallbackContext,
											ui_refresh,														// uiRefreshFrequency,
											ul_timeout													);	// ulTimeOutSeconds

			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}

			m_sBoardAI[m_iCurrentBoardIndex].m_bFirstDraw = TRUE;
		
			m_sBoardAI[m_iCurrentBoardIndex].m_iXLastPixel = m_rectPlotClient.left;

			m_sBoardAI[m_iCurrentBoardIndex].m_dXLastPixel = (double)m_rectPlotClient.left;

			dc.FillSolidRect( m_rectPlotClient, RGB(0, 0, 0) );

			m_sBoardAI[m_iCurrentBoardIndex].m_iLastError = ME4000_NO_ERROR;
			
			i_error = me4000AIStart(m_iCurrentBoardIndex);	// uiBoardNumber
			
			if(i_error != ME4000_NO_ERROR)
			{
				return;
			}
			
			GetDlgItem(ID_START_SAMPLE)->EnableWindow(FALSE);
			
			GetDlgItem(ID_STOP)->EnableWindow(TRUE);
			
			m_sBoardAI[m_iCurrentBoardIndex].m_iLastOperation = AI_CONTINUOUS;

			m_sBoardAI[m_iCurrentBoardIndex].m_bAIActive = TRUE;
		}
	}
}

void CAnalogInputPP::OnStop() 
{
	// TODO: Add your control notification handler code here
	
	me4000AIStop(	m_iCurrentBoardIndex,		// uiBoardNumber
					ME4000_VALUE_NOT_USED	);	// iReserved

	GetDlgItem(ID_STOP)->EnableWindow(FALSE);

	GetDlgItem(ID_START_SAMPLE)->EnableWindow(TRUE);
	
	m_sBoardAI[m_iCurrentBoardIndex].m_bAIActive = FALSE;
}

void CAnalogInputPP::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	CClientDC dc_plot(m_pPlotWin);

	dc_plot.FillSolidRect( m_rectPlotClient, RGB(0, 0, 0) );	
	
	if( !m_sBoardAI[m_iCurrentBoardIndex].m_bAIActive )
	{
		if(m_sBoardAI[m_iCurrentBoardIndex].m_iLastError != ME4000_NO_ERROR)
		{
			dc_plot.SetTextColor( channel_colors[0] );

			dc_plot.SetBkMode(TRANSPARENT);

			char error_message[256];

			me4000ErrorGetMessage(	m_sBoardAI[m_iCurrentBoardIndex].m_iLastError,		// iErrorCode,
									&error_message[0],									// pcBuffer
									256												);	// uiBufferSize);

			dc_plot.DrawText(&error_message[0], m_rectPlotClient, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
		else if(m_sBoardAI[m_iCurrentBoardIndex].m_iLastOperation == AI_SINGLE)
		{
			dc_plot.SetTextColor( channel_colors[0] );

			dc_plot.SetBkMode(TRANSPARENT);

			CFont font_text;

			font_text.CreateFontIndirect(&lf_text);

			CFont* p_old_font = dc_plot.SelectObject(&font_text);
    
			CString cs_value;

			cs_value.Format("Channel %2u:  %7.3f Volt", 
							m_sBoardAI[m_iCurrentBoardIndex].m_uiSingleChannel + 1,
							m_sBoardAI[m_iCurrentBoardIndex].m_sSingleValueVolt		);

			dc_plot.DrawText(cs_value, m_rectPlotClient, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		
			dc_plot.SelectObject(p_old_font);
		}
		else if(m_sBoardAI[m_iCurrentBoardIndex].m_iLastOperation == AI_SCAN)
		{
			int no_of_frames = m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentNumberofChanLists;
			
			if(no_of_frames < 2)
			{
				return;
			}
		
			// With a finite acquisition we do not know until the acquisition is 
			// finished how many frames are available (the user may abort the 
			// operation), so we calculate m_dXIncrement before each draw
		
			m_sBoardAI[m_iCurrentBoardIndex].m_dXIncrement = (double)m_rectPlotClient.Width() / (double)(m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentNumberofChanLists - 1);
		
			short* p_data_buffer = new short[no_of_frames];
		
			for(unsigned int index_channel = 0; index_channel < m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentNumberOfChannels; index_channel++)
			{
				unsigned long ul_no_of_values;
			
				me4000AIExtractValues(	m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentChanNumber[index_channel],			// uiChannelNumber,
										m_sBoardAI[m_iCurrentBoardIndex].m_psScanBuffer,								// psAIBuffer,
										no_of_frames * m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentNumberOfChannels,	// unsigned long ulAIDataCount,
										&m_sBoardAI[m_iCurrentBoardIndex].m_ucChanList[0],								// pucChanList,
										m_sBoardAI[m_iCurrentBoardIndex].m_uiCurrentNumberOfChannels,					// uiChanListCount,
										p_data_buffer,																	// psChanBuffer,
										no_of_frames,																	// ulChanBufferSizeValues,
										&ul_no_of_values															);	// pulChanDataCount
				
				short* p_data = p_data_buffer;
		
				CPen draw_pen(PS_SOLID, 0, m_sBoardAI[m_iCurrentBoardIndex].m_crCurrentChanColours[index_channel]);

				CPen* p_old_pen = dc_plot.SelectObject(&draw_pen);

				BOOL b_first_pix = TRUE;
			
				int x_old_pix = 0;
			
				int y_old_pix = 0;

				double d_x_pix = (double)m_rectPlotClient.left;
			
				for(unsigned long data_index = 0; data_index < ul_no_of_values; ++data_index)
				{
					int x_pix = (int)d_x_pix;

					double d_volt;

					me4000AIDigitToVolt(p_data[data_index],														// sDigit 
										m_sBoardAI[m_iCurrentBoardIndex].m_iCurrentChanRange[index_channel],	// iRange
										&d_volt																);	// pdVolt

					int y_pix = (int)( d_volt * m_sBoardAI[m_iCurrentBoardIndex].m_dYFactor[index_channel] + m_sBoardAI[m_iCurrentBoardIndex].m_dYConstant[index_channel] );

					if(!b_first_pix)
					{
						if( (x_pix != x_old_pix)||(y_pix != y_old_pix) )
						{
							dc_plot.LineTo(x_pix, y_pix);

							x_old_pix = x_pix;
					
							y_old_pix = y_pix;
						}
					}
					else
					{
						dc_plot.MoveTo(x_pix, y_pix);

						x_old_pix = x_pix;
				
						y_old_pix = y_pix;

						b_first_pix = FALSE;
					}
					
					d_x_pix+= m_sBoardAI[m_iCurrentBoardIndex].m_dXIncrement;
				}
				
				dc_plot.SelectObject(p_old_pen);
			}

			delete p_data_buffer;
		}
	}
		
	// Do not call CPropertyPage::OnPaint() for painting messages
}
