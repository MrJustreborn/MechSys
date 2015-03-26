// meScopeView.cpp : implementation of the CMeScopeView class
//

#include "stdafx.h"

#include <limits.h>

#include "meScope.h"

#include "meScopeDoc.h"
#include "meScopeView.h"

#include "Parameters.h"

#include "..\me4000dll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeScopeView

IMPLEMENT_DYNCREATE(CMeScopeView, CView)

BEGIN_MESSAGE_MAP(CMeScopeView, CView)
	//{{AFX_MSG_MAP(CMeScopeView)
	ON_COMMAND(ID_CHANNEL_SELECTION, OnChannelSelection)
	ON_COMMAND(ID_START_ACQUISITION, OnStartAcquisition)
	ON_UPDATE_COMMAND_UI(ID_START_ACQUISITION, OnUpdateStartAcquisition)
	ON_COMMAND(ID_STOP_ACQUISITION, OnStopAcquisition)
	ON_UPDATE_COMMAND_UI(ID_STOP_ACQUISITION, OnUpdateStopAcquisition)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeScopeView construction/destruction

#define ME_SCOPE_DURATION_INFINITE					0
#define ME_SCOPE_DURATION_FINITE					1

#define ME_SCOPE_AI_CONV_MODE_CONT_SW				0  
#define ME_SCOPE_AI_CONV_MODE_CONT_ET				1  
#define ME_SCOPE_AI_CONV_MODE_CONT_ET_VALUE			2  
#define ME_SCOPE_AI_CONV_MODE_CONT_ET_CHANLIST		3 

#define ME_SCOPE_AI_BIPOLAR_10						0
#define ME_SCOPE_AI_BIPOLAR_2_5						1
#define ME_SCOPE_AI_UNIPOLAR_10						2
#define ME_SCOPE_AI_UNIPOLAR_2_5					3

#define ME_SCOPE_AI_INPUT_SINGLE_ENDED				0
#define ME_SCOPE_AI_INPUT_DIFFERENTIAL				1

#define ME_SCOPE_AI_TRIGGER_EXT_DIGITAL				0
#define ME_SCOPE_AI_TRIGGER_EXT_ANALOG				1

// External trigger flank type for me4000AISingle and 
// me4000AIConfig - Parameter iExtTriggerEdge
#define ME_SCOPE_AI_TRIGGER_EXT_EDGE_RISING			0
#define ME_SCOPE_AI_TRIGGER_EXT_EDGE_FALLING		1
#define ME_SCOPE_AI_TRIGGER_EXT_EDGE_BOTH			2



#define ME_ERROR_NONE								0 


void _stdcall ME4000ErrorFunction(char * sz_func_name, int i_error_code)
{
	char msg_mess[256];

	me4000ErrorGetMessage(i_error_code, &msg_mess[0], 256);

	char win_mess[512];

	sprintf(&win_mess[0],	"Error calling ME4000 function: %s\n\n"
							"%s\n\n"
							"Error code: 0x%08X",
							sz_func_name,
							&msg_mess[0],
							i_error_code							);
	
	AfxMessageBox(&win_mess[0], MB_OK | MB_ICONEXCLAMATION);   
}

CMeScopeView::CMeScopeView()
{
	// TODO: add construction code here

	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		if(index_channel == 0)
		{
			m_arrChannels[index_channel].m_bChannelActive = TRUE;
		}
		else
		{
			m_arrChannels[index_channel].m_bChannelActive = FALSE;
		}
	
		m_arrChannels[index_channel].m_iChannelNumber	= index_channel;
		
		m_arrChannels[index_channel].m_iRange			= ME_SCOPE_AI_BIPOLAR_10;
		
		m_arrChannels[index_channel].m_dMin				= -10.0;
		m_arrChannels[index_channel].m_dMax				= +10.0;
	}

	m_bMultiplexing			= FALSE;

	m_bSampleAndHold		= FALSE;

	m_uiCount				= 100;
	
	m_uiSampleRate			= 100;
	
	m_iAcqDuration			= ME_SCOPE_DURATION_INFINITE;
	
	m_uiWindowWidthValues	= 1000;
	
	m_dWindowWidthSecs		= 4.0;
	
	m_iAcqMode				= ME_SCOPE_AI_CONV_MODE_CONT_SW;
	
	m_iExtTriggerMode		= ME_SCOPE_AI_TRIGGER_EXT_DIGITAL;
	
	m_iExtTriggerEdge		= ME_SCOPE_AI_TRIGGER_EXT_EDGE_RISING;
	
	m_iSingleDiffMode		= ME_SCOPE_AI_INPUT_SINGLE_ENDED;

	m_iBoardNumber			= 0;
	
	m_bAcquisitionRunning	= FALSE;

	m_psDataBuffer			= NULL;

	m_uiMaxBufferSize		= 0;

	m_uiCurrentBufferSize	= 0;

	m_uiNoOfDisplayChannels	= 0;
	
	for(index_channel = 0; index_channel < 4; index_channel++) 
	{
		m_arrDisplayChannels[index_channel].m_iRange = ME_SCOPE_AI_BIPOLAR_10;
	
		m_arrDisplayChannels[index_channel].m_dMin = -10.0;
		m_arrDisplayChannels[index_channel].m_dMax = +10.0;

		m_arrDisplayChannels[index_channel].m_crColor = channel_colors[index_channel];

		m_arrDisplayChannels[index_channel].m_dYFactor = 1.0;

		m_arrDisplayChannels[index_channel].m_dYConstant = 0.0;

		m_arrDisplayChannels[index_channel].m_iYLastPixel = 0;
	}

	m_dXIncrement			= 0;

	m_bFirstDraw			= TRUE;
	
	m_dXLastPixel			= 0.0;
	
	m_iXLastPixel			= 0;

	me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);
}

CMeScopeView::~CMeScopeView()
{
	if(m_psDataBuffer != NULL)
	{
		delete m_psDataBuffer;
	}
}

BOOL CMeScopeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// We want a window which doesn't paint the background, this avoids an 
	// unpleasant flicker
	
	const char* sz_class = AfxRegisterWndClass(0); 
	
	cs.lpszClass = sz_class;
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMeScopeView drawing

void CMeScopeView::OnDraw(CDC* pDC)
{
	CMeScopeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if( (m_rectPlot.Width() < 20)||(m_rectPlot.Height() < 20) )
	{
		return;
	}
	
	if( (!m_bAcquisitionRunning)&&(m_uiCurrentBufferSize > 0) )
	{
		SDisplayChannel* p_disp_chan = &m_arrDisplayChannels[0];
		
		unsigned int no_of_frames = m_uiCurrentBufferSize / m_uiNoOfDisplayChannels;

		if(no_of_frames < 2)
		{
			return;
		}
		
		// With a finite acquisition we do not know until the acquisition is 
		// finished how many frames are available (the user may abort the 
		// operation), so we calculate m_dXIncrement before each draw
		
		m_dXIncrement = (double)m_rectPlot.Width() / (double)(no_of_frames - 1);
		
		short* p_data_buffer = new short[no_of_frames];
		
		for(unsigned int index_channel = 0; index_channel < m_uiNoOfDisplayChannels; index_channel++)
		{
			unsigned long ul_no_of_values;
			
			if( !m_bMultiplexing )
			{
				me4000AIExtractValues( (unsigned int)(m_ucChanList[index_channel] & 0x1F), m_psDataBuffer, m_uiCurrentBufferSize, 
											&m_ucChanList[0], m_uiNoOfDisplayChannels, p_data_buffer, no_of_frames, &ul_no_of_values);
			}
			else
			{
				me4000MultiSigAIExtractValues( (unsigned int)(m_ucChanList[index_channel] & 0x1F), m_psDataBuffer, m_uiCurrentBufferSize,  
													&m_ucChanList[0], m_uiNoOfDisplayChannels, p_data_buffer, no_of_frames, &ul_no_of_values);
			}
				
			int i_range;
			
			switch(p_disp_chan->m_iRange)
			{
			case ME_SCOPE_AI_BIPOLAR_10:

				i_range = ME4000_AI_RANGE_BIPOLAR_10;

				break;
			
			case ME_SCOPE_AI_BIPOLAR_2_5:

				i_range = ME4000_AI_RANGE_BIPOLAR_2_5;

				break;
			
			case ME_SCOPE_AI_UNIPOLAR_10:

				i_range = ME4000_AI_RANGE_UNIPOLAR_10;

				break;
			
			case ME_SCOPE_AI_UNIPOLAR_2_5:

				i_range = ME4000_AI_RANGE_UNIPOLAR_2_5;

				break;
			}

			short* p_data = p_data_buffer;
		
			CPen draw_pen(PS_SOLID, 0, p_disp_chan->m_crColor);

			CPen* p_old_pen = pDC->SelectObject(&draw_pen);

			BOOL b_first_pix = TRUE;
			
			int x_old_pix = 0;
			
			int y_old_pix = 0;

			double d_x_pix = (double)m_rectPlot.left;
			
			for(unsigned long data_index = 0; data_index < ul_no_of_values; ++data_index)
			{
				int x_pix = (int)d_x_pix;

				double d_volt;

				if( !m_bMultiplexing )
				{
					me4000AIDigitToVolt(p_data[data_index], i_range, &d_volt);
				}
				else
				{
					me4000AIDigitToVolt(p_data[data_index], ME4000_AI_RANGE_BIPOLAR_10, &d_volt); // ???? me4000MultiSigAIDigitToSize
				}

				int y_pix = (int)( d_volt * p_disp_chan->m_dYFactor + p_disp_chan->m_dYConstant );

				if(!b_first_pix)
				{
					if( (x_pix != x_old_pix)||(y_pix != y_old_pix) )
					{
						pDC->LineTo(x_pix, y_pix);

						x_old_pix = x_pix;
				
						y_old_pix = y_pix;
					}
				}
				else
				{
					pDC->MoveTo(x_pix, y_pix);

					x_old_pix = x_pix;
			
					y_old_pix = y_pix;

					b_first_pix = FALSE;
				}
				
				d_x_pix+= m_dXIncrement;
			}
			
			pDC->SelectObject(p_old_pen);
			
			++p_disp_chan;
		}

		delete p_data_buffer;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMeScopeView printing

BOOL CMeScopeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMeScopeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMeScopeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMeScopeView diagnostics

#ifdef _DEBUG
void CMeScopeView::AssertValid() const
{
	CView::AssertValid();
}

void CMeScopeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMeScopeDoc* CMeScopeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMeScopeDoc)));
	return (CMeScopeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMeScopeView message handlers

void CMeScopeView::OnChannelSelection() 
{
	// TODO: Add your command handler code here
	
	CParameters dlg_parameter;

	if(m_bMultiplexing)
	{
		dlg_parameter.m_iNormalAnalog = 1;
	}
	else
	{
		dlg_parameter.m_iNormalAnalog = 0;
	}

	dlg_parameter.m_bChan1 = m_arrChannels[0].m_bChannelActive;
	dlg_parameter.m_bChan2 = m_arrChannels[1].m_bChannelActive;
	dlg_parameter.m_bChan3 = m_arrChannels[2].m_bChannelActive;
	dlg_parameter.m_bChan4 = m_arrChannels[3].m_bChannelActive;

	dlg_parameter.m_iChanNumber1 = m_arrChannels[0].m_iChannelNumber;
	dlg_parameter.m_iChanNumber2 = m_arrChannels[1].m_iChannelNumber;
	dlg_parameter.m_iChanNumber3 = m_arrChannels[2].m_iChannelNumber;
	dlg_parameter.m_iChanNumber4 = m_arrChannels[3].m_iChannelNumber;

	dlg_parameter.m_iRange1 = m_arrChannels[0].m_iRange;
	dlg_parameter.m_iRange2 = m_arrChannels[1].m_iRange;
	dlg_parameter.m_iRange3 = m_arrChannels[2].m_iRange;
	dlg_parameter.m_iRange4 = m_arrChannels[3].m_iRange;

	dlg_parameter.m_fMin1 = (float)m_arrChannels[0].m_dMin;
	dlg_parameter.m_fMin2 = (float)m_arrChannels[1].m_dMin;
	dlg_parameter.m_fMin3 = (float)m_arrChannels[2].m_dMin;
	dlg_parameter.m_fMin4 = (float)m_arrChannels[3].m_dMin;

	dlg_parameter.m_fMax1 = (float)m_arrChannels[0].m_dMax;
	dlg_parameter.m_fMax2 = (float)m_arrChannels[1].m_dMax;
	dlg_parameter.m_fMax3 = (float)m_arrChannels[2].m_dMax;
	dlg_parameter.m_fMax4 = (float)m_arrChannels[3].m_dMax;

	dlg_parameter.m_bSampleAndHold		= m_bSampleAndHold;

	dlg_parameter.m_uiCount				= m_uiCount;

	dlg_parameter.m_uiSampleRate		= m_uiSampleRate;

	dlg_parameter.m_iAcqDuration		= m_iAcqDuration;

	dlg_parameter.m_uiWindowWidthValues	= m_uiWindowWidthValues;
	
	dlg_parameter.m_fWindowWidthSecs	= (float)m_dWindowWidthSecs;
	
	dlg_parameter.m_iAcqMode			= m_iAcqMode;

	dlg_parameter.m_iTriggerMode		= m_iExtTriggerMode;

	dlg_parameter.m_iTriggerEdge		= m_iExtTriggerEdge;

	dlg_parameter.m_iSingleDiffMode		= m_iSingleDiffMode;

	if( dlg_parameter.DoModal() == IDOK)
	{
		if(dlg_parameter.m_iNormalAnalog == 1)
		{
			m_bMultiplexing = TRUE;
		}
		else
		{
			m_bMultiplexing = FALSE;
		}

		m_arrChannels[0].m_bChannelActive = dlg_parameter.m_bChan1;
		m_arrChannels[1].m_bChannelActive = dlg_parameter.m_bChan2;
		m_arrChannels[2].m_bChannelActive = dlg_parameter.m_bChan3;
		m_arrChannels[3].m_bChannelActive = dlg_parameter.m_bChan4;

		m_arrChannels[0].m_iChannelNumber = dlg_parameter.m_iChanNumber1;
		m_arrChannels[1].m_iChannelNumber = dlg_parameter.m_iChanNumber2;
		m_arrChannels[2].m_iChannelNumber = dlg_parameter.m_iChanNumber3;
		m_arrChannels[3].m_iChannelNumber = dlg_parameter.m_iChanNumber4;

		m_arrChannels[0].m_iRange = dlg_parameter.m_iRange1;
		m_arrChannels[1].m_iRange = dlg_parameter.m_iRange2;
		m_arrChannels[2].m_iRange = dlg_parameter.m_iRange3;
		m_arrChannels[3].m_iRange = dlg_parameter.m_iRange4;

		m_arrChannels[0].m_dMin = (double)dlg_parameter.m_fMin1;
		m_arrChannels[1].m_dMin = (double)dlg_parameter.m_fMin2;
		m_arrChannels[2].m_dMin = (double)dlg_parameter.m_fMin3;
		m_arrChannels[3].m_dMin = (double)dlg_parameter.m_fMin4;

		m_arrChannels[0].m_dMax = (double)dlg_parameter.m_fMax1;
		m_arrChannels[1].m_dMax = (double)dlg_parameter.m_fMax2;
		m_arrChannels[2].m_dMax = (double)dlg_parameter.m_fMax3;
		m_arrChannels[3].m_dMax = (double)dlg_parameter.m_fMax4;

		m_bSampleAndHold		= dlg_parameter.m_bSampleAndHold;

		m_uiCount				= dlg_parameter.m_uiCount;

		m_uiSampleRate			= dlg_parameter.m_uiSampleRate;

		m_iAcqDuration			= dlg_parameter.m_iAcqDuration;

		m_uiWindowWidthValues	= dlg_parameter.m_uiWindowWidthValues;
		
		m_dWindowWidthSecs		= (double)dlg_parameter.m_fWindowWidthSecs;
	
		m_iAcqMode				= dlg_parameter.m_iAcqMode;

		m_iExtTriggerMode		= dlg_parameter.m_iTriggerMode;

		m_iExtTriggerEdge		= dlg_parameter.m_iTriggerEdge;

		m_iSingleDiffMode		= dlg_parameter.m_iSingleDiffMode;
	}
}

void CMeScopeView::OnStartAcquisition() 
{
	// TODO: Add your command handler code here
	
	int i_me4000_error;
	
	int i_single_diff_mode = 0;

	switch(m_iSingleDiffMode)
	{
	case ME_SCOPE_AI_INPUT_SINGLE_ENDED:

		i_single_diff_mode = ME4000_AI_INPUT_SINGLE_ENDED;

		break;
	
	case ME_SCOPE_AI_INPUT_DIFFERENTIAL:

		i_single_diff_mode = ME4000_AI_INPUT_DIFFERENTIAL;

		break;
	}
	
	m_uiNoOfDisplayChannels = 0;
	
	for(int index_chan = 0; index_chan < 4; index_chan++)
	{
		if(m_arrChannels[index_chan].m_bChannelActive)
		{
			if(!m_bMultiplexing)
			{
				int i_range = 0;

				switch(m_arrChannels[index_chan].m_iRange)
				{
				case ME_SCOPE_AI_BIPOLAR_10:

					i_range = ME4000_AI_RANGE_BIPOLAR_10;

					break;
				
				case ME_SCOPE_AI_BIPOLAR_2_5:

					i_range = ME4000_AI_RANGE_BIPOLAR_2_5;

					break;
				
				case ME_SCOPE_AI_UNIPOLAR_10:

					i_range = ME4000_AI_RANGE_UNIPOLAR_10;

					break;
				
				case ME_SCOPE_AI_UNIPOLAR_2_5:

					i_range = ME4000_AI_RANGE_UNIPOLAR_2_5;

					break;
				}

				i_me4000_error = me4000AIMakeChannelListEntry(	m_arrChannels[index_chan].m_iChannelNumber, 
																i_range, 
																&m_ucChanList[m_uiNoOfDisplayChannels]		);

				if(i_me4000_error != ME_ERROR_NONE)
				{
					return;
				}
			}
			else
			{
				m_ucChanList[m_uiNoOfDisplayChannels] = (unsigned char)m_arrChannels[index_chan].m_iChannelNumber;
			}

			++m_uiNoOfDisplayChannels;
		}
	}

	int i_me4000_simultaneous;

	if(m_bSampleAndHold)
	{
		i_me4000_simultaneous = ME4000_AI_SIMULTANEOUS_ENABLE;
	}
	else
	{
		i_me4000_simultaneous = ME4000_AI_SIMULTANEOUS_DISABLE;
	}

	unsigned long ul_scan_ticks_low;
	
	unsigned long ul_scan_ticks_high;

	double d_achieved_freq;

	i_me4000_error = me4000FrequencyToTicks((double)m_uiSampleRate, 
								&ul_scan_ticks_low, &ul_scan_ticks_high, 
															&d_achieved_freq);

	if(i_me4000_error != ME_ERROR_NONE)
	{
		return;
	}

	int i_acq_mode;
	
	switch(m_iAcqMode)
	{
	case ME_SCOPE_AI_CONV_MODE_CONT_SW:

		i_acq_mode = ME4000_AI_ACQ_MODE_SOFTWARE;

		break;

	case ME_SCOPE_AI_CONV_MODE_CONT_ET:

		i_acq_mode = ME4000_AI_ACQ_MODE_EXT;

		break;

	case ME_SCOPE_AI_CONV_MODE_CONT_ET_VALUE:

		i_acq_mode = ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE;

		break;

	case ME_SCOPE_AI_CONV_MODE_CONT_ET_CHANLIST:

		i_acq_mode = ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST;

		break;

	}
	
	int i_ext_trigger_mode;

	switch(m_iExtTriggerMode)
	{
	case ME_SCOPE_AI_TRIGGER_EXT_DIGITAL:

		i_ext_trigger_mode = ME4000_AI_TRIGGER_EXT_DIGITAL;

		break;

	case ME_SCOPE_AI_TRIGGER_EXT_ANALOG:

		i_ext_trigger_mode = ME4000_AI_TRIGGER_EXT_ANALOG;

		break;
	}
	
	int i_ext_trigger_edge; 
		
	switch(m_iExtTriggerEdge)
	{
	case ME_SCOPE_AI_TRIGGER_EXT_EDGE_RISING:

		i_ext_trigger_edge = ME4000_AI_TRIGGER_EXT_EDGE_RISING;

		break;

	case ME_SCOPE_AI_TRIGGER_EXT_EDGE_FALLING:

		i_ext_trigger_edge = ME4000_AI_TRIGGER_EXT_EDGE_FALLING;

		break;

	case ME_SCOPE_AI_TRIGGER_EXT_EDGE_BOTH:

		i_ext_trigger_edge = ME4000_AI_TRIGGER_EXT_EDGE_BOTH;

		break;
	}

	if(m_iAcqMode == ME_SCOPE_AI_CONV_MODE_CONT_SW)
	{
		i_ext_trigger_mode	= 0;
		
		i_ext_trigger_edge	= 0;
	}
	else
	{
		ul_scan_ticks_low	= 0; 
		ul_scan_ticks_high	= 0; 
	}


	
	if(!m_bMultiplexing)
	{
		i_me4000_error = me4000AIConfig(m_iBoardNumber, 
										&m_ucChanList[0], 
										m_uiNoOfDisplayChannels,
										i_single_diff_mode, 
										i_me4000_simultaneous, 
 										0, 
										0,  
		  								ul_scan_ticks_low, 
		  								ul_scan_ticks_high, 
										i_acq_mode, 
										i_ext_trigger_mode, 
										i_ext_trigger_edge			);
	}
	else
	{
		i_me4000_error = me4000MultiSigAIOpen(m_iBoardNumber);
		
		if(i_me4000_error == ME_ERROR_NONE)
		{
			i_me4000_error = me4000MultiSigAIConfig(m_iBoardNumber,
													0,
													&m_ucChanList[0], 
													m_uiNoOfDisplayChannels,
	 												0, 
													0,  
			  										ul_scan_ticks_low, 
		  											ul_scan_ticks_high, 
													i_acq_mode, 
													i_ext_trigger_mode, 
													i_ext_trigger_edge		);

			if(i_me4000_error != ME_ERROR_NONE)
			{
				me4000MultiSigAIClose(m_iBoardNumber);
			}
		}
	}


	if(i_me4000_error != ME_ERROR_NONE)
	{
		return;
	}

	unsigned int ui_count					= 0;
	unsigned short* p_us_buffer				= NULL;
	ME4000_P_AI_CALLBACK_PROC p_callback	= NULL;

	if(m_iAcqDuration == ME_SCOPE_DURATION_FINITE)
	{
		ui_count = m_uiCount;

		if(ui_count * m_uiNoOfDisplayChannels > m_uiMaxBufferSize)
		{
			if(m_psDataBuffer != NULL)
			{
				delete m_psDataBuffer;
			}

			m_psDataBuffer = new short[ui_count * m_uiNoOfDisplayChannels];
		}
		
		p_callback = FiniteAcquisitionProc;

		if(!m_bMultiplexing)
		{
			i_me4000_error = me4000AIScan(	m_iBoardNumber, 
											m_uiCount, 
											m_psDataBuffer, 
											ui_count * m_uiNoOfDisplayChannels, 
						 					ME4000_AI_SCAN_ASYNCHRONOUS, 
											NULL,
											NULL, 
											0,
											FiniteAcquisitionProc, 
											this,
											0							);
		}
		else
		{
			i_me4000_error = me4000MultiSigAIScan(	m_iBoardNumber, 
													m_uiCount, 
													m_psDataBuffer, 
													ui_count * m_uiNoOfDisplayChannels, 
						 							ME4000_AI_SCAN_ASYNCHRONOUS, 
													NULL,
													NULL, 
													0,
													FiniteAcquisitionProc, 
													this,
													0							);

			if(i_me4000_error != ME_ERROR_NONE)
			{
				me4000MultiSigAIClose(m_iBoardNumber);
			}
		}

		if(i_me4000_error != ME_ERROR_NONE)
		{
			return;
		}
	}
	else
	{
		unsigned int ui_callback_count = m_uiSampleRate / 10;

		if(ui_callback_count < 1)
		{
			ui_callback_count = 1;
		}
		
		if(!m_bMultiplexing)
		{
			i_me4000_error = me4000AIContinuous(m_iBoardNumber, 
												InfiniteAcquisitionProc, 
 												this, 
												ui_callback_count,	
												0						);
		}
		else
		{
			i_me4000_error = me4000MultiSigAIContinuous(m_iBoardNumber, 
														InfiniteAcquisitionProc, 
 														this, 
														ui_callback_count,
														0						);

			if(i_me4000_error != ME_ERROR_NONE)
			{
				me4000MultiSigAIClose(m_iBoardNumber);
			}
		}
		
		if(i_me4000_error != ME_ERROR_NONE)
		{
			return;
		}
	}

	m_uiNoOfDisplayChannels = 0;
	
	for(index_chan = 0; index_chan < 4; index_chan++)
	{
		if(m_arrChannels[index_chan].m_bChannelActive)
		{
			m_arrDisplayChannels[m_uiNoOfDisplayChannels].m_crColor = channel_colors[index_chan];
			
			m_arrDisplayChannels[m_uiNoOfDisplayChannels].m_iRange = m_arrChannels[index_chan].m_iRange;
			
			m_arrDisplayChannels[m_uiNoOfDisplayChannels].m_dMin = m_arrChannels[index_chan].m_dMin;
			
			m_arrDisplayChannels[m_uiNoOfDisplayChannels].m_dMax = m_arrChannels[index_chan].m_dMax;

			++m_uiNoOfDisplayChannels;
		}
	}

	CalculateYFactorsAndConstants();

	m_uiCurrentBufferSize = 0;
	
	if(m_iAcqDuration == ME_SCOPE_DURATION_INFINITE)
	{
		m_bFirstDraw			= TRUE;
		
		m_iXLastPixel = m_rectPlot.left;

		m_dXLastPixel = (double)m_rectPlot.left;
	}
	
	Invalidate(TRUE);

	m_bAcquisitionRunning = TRUE;	
	
	if(!m_bMultiplexing)
	{
		i_me4000_error = me4000AIStart(m_iBoardNumber);
	}
	else
	{
		i_me4000_error = me4000MultiSigAIStart(m_iBoardNumber);

		if(i_me4000_error != ME_ERROR_NONE)
		{
			me4000MultiSigAIClose(m_iBoardNumber);
		}
	}
	
	if(i_me4000_error != ME_ERROR_NONE)
	{
		return;
	}
}

void CMeScopeView::OnUpdateStartAcquisition(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable( !m_bAcquisitionRunning );
}

void CMeScopeView::OnStopAcquisition() 
{
	// TODO: Add your command handler code here
	
	if(!m_bMultiplexing)
	{
		me4000AIStop(m_iBoardNumber, 0);
	}
	else
	{
		me4000MultiSigAIStop(m_iBoardNumber, 0);

		me4000MultiSigAIClose(m_iBoardNumber);
	}

	m_bAcquisitionRunning = FALSE;	
}

void CMeScopeView::OnUpdateStopAcquisition(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->Enable(m_bAcquisitionRunning);
}

int CMeScopeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

BOOL CMeScopeView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	CRect rect_client;

	GetClientRect(&rect_client);

	pDC->FillSolidRect( &rect_client, RGB(0, 0, 0) );

	return(TRUE);
}

void CMeScopeView :: FiniteAcquisitionProc(short* psValues, 
												unsigned int uiNumberOfValues, 
													void* pCallbackContext, int iLastError)
{
	CMeScopeView* p_view = (CMeScopeView*)pCallbackContext;

	if(iLastError != ME_ERROR_NONE)
	{
		ME4000ErrorFunction("FiniteAcquisitionProc", iLastError);
	
		p_view->m_uiCurrentBufferSize = 0;	
	}
	else
	{
		p_view->m_uiCurrentBufferSize = uiNumberOfValues;	
	}
	
	p_view->m_bAcquisitionRunning = FALSE;
	
	p_view->Invalidate(TRUE);
}

void CMeScopeView :: InfiniteAcquisitionProc(short* psValues, 
												unsigned int uiNumberOfValues, 
													void* pCallbackContext, int iLastError)
{
	CMeScopeView* p_view = (CMeScopeView*)pCallbackContext;

	if(iLastError != ME_ERROR_NONE)
	{
		ME4000ErrorFunction("InfiniteAcquisitionProc", iLastError);
	
		if(!p_view->m_bMultiplexing)
		{
			me4000AIStop(p_view->m_iBoardNumber, 0);
		}
		else
		{
			me4000MultiSigAIStop(p_view->m_iBoardNumber, 0);

			me4000MultiSigAIClose(p_view->m_iBoardNumber);
		}

		p_view->m_bAcquisitionRunning = FALSE;	
	}

	if(uiNumberOfValues == 0)
	{
		return;
	}
	
	CClientDC dc(p_view);
	
	dc.IntersectClipRect(p_view->m_rectPlot);
	
	CRect rect_erase = p_view->m_rectPlot;
	
	dc.SelectStockObject(BLACK_PEN);

	int no_frames = uiNumberOfValues / p_view->m_uiNoOfDisplayChannels;
	
	if( !p_view->m_bFirstDraw)
	{
		dc.MoveTo(p_view->m_iXLastPixel + 1, p_view->m_rectPlot.top);
		dc.LineTo(p_view->m_iXLastPixel + 1, p_view->m_rectPlot.bottom);

		int erase_from_pixel = p_view->m_iXLastPixel + 1;
		
		int erase_to_pixel = (int)(p_view->m_dXLastPixel + (double)no_frames * p_view->m_dXIncrement);

		if(erase_to_pixel > erase_from_pixel)
		{
			if( erase_to_pixel > p_view->m_rectPlot.right )
			{
				rect_erase.left = erase_from_pixel;
				
				dc.FillSolidRect( rect_erase, RGB(0, 0, 0) );

				erase_from_pixel = p_view->m_rectPlot.left;
				erase_to_pixel-= p_view->m_rectPlot.Width();
			}

			rect_erase.left = erase_from_pixel;
				
			rect_erase.right = erase_to_pixel + 1;
				
			dc.FillSolidRect( rect_erase, RGB(0, 0, 0) );
		}
	}

	double d_current_pix;
	
	int old_x_pix;
	
	SDisplayChannel* p_disp_chan = &p_view->m_arrDisplayChannels[0];
	
	short* p_data_buffer = new short[no_frames];
		
	for(unsigned int index_channel = 0; index_channel < p_view->m_uiNoOfDisplayChannels; index_channel++)
	{
		CPen pen_draw(PS_SOLID, 0, p_disp_chan->m_crColor);
		
		dc.SelectObject(&pen_draw);
		
		old_x_pix = p_view->m_iXLastPixel;
		
		d_current_pix = p_view->m_dXLastPixel;
		
		unsigned long ul_no_of_values;
		
		if( !p_view->m_bMultiplexing )
		{
			me4000AIExtractValues( (unsigned int)(p_view->m_ucChanList[index_channel] & 0x1F), psValues, uiNumberOfValues, 
															&p_view->m_ucChanList[0], p_view->m_uiNoOfDisplayChannels, 
																				p_data_buffer, no_frames, &ul_no_of_values);
		}
		else 
		{
			me4000MultiSigAIExtractValues( (unsigned int)(p_view->m_ucChanList[index_channel] & 0x1F), psValues, uiNumberOfValues, 
															&p_view->m_ucChanList[0], p_view->m_uiNoOfDisplayChannels, 
																				p_data_buffer, no_frames, &ul_no_of_values);
		}
		
		int i_range;
		
		switch(p_disp_chan->m_iRange)
		{
		case ME_SCOPE_AI_BIPOLAR_10:

			i_range = ME4000_AI_RANGE_BIPOLAR_10;

			break;
		
		case ME_SCOPE_AI_BIPOLAR_2_5:

			i_range = ME4000_AI_RANGE_BIPOLAR_2_5;

			break;
		
		case ME_SCOPE_AI_UNIPOLAR_10:

			i_range = ME4000_AI_RANGE_UNIPOLAR_10;

			break;
		
		case ME_SCOPE_AI_UNIPOLAR_2_5:

			i_range = ME4000_AI_RANGE_UNIPOLAR_2_5;

			break;
		}

		short* p_data = p_data_buffer;
		
		for(unsigned long frame = 0; frame < ul_no_of_values; frame++)
		{
			int x_pix = (int)d_current_pix;
				
			double d_volt;

			if( !p_view->m_bMultiplexing )
			{
				me4000AIDigitToVolt(*p_data, i_range, &d_volt);
			}
			else 
			{
				me4000AIDigitToVolt(*p_data, ME4000_AI_RANGE_BIPOLAR_10, &d_volt); // ???? me4000MultiSigAIDigitToSize
			}

			int y_pix = (int)( d_volt * p_disp_chan->m_dYFactor + p_disp_chan->m_dYConstant );

			if( (frame == 0)&&(!p_view->m_bFirstDraw) )
			{
				dc.MoveTo(old_x_pix, p_disp_chan->m_iYLastPixel );
			}

			if(!p_view->m_bFirstDraw)
			{
				if( (x_pix != old_x_pix)||(y_pix != p_disp_chan->m_iYLastPixel) )
				{
					dc.LineTo(x_pix, y_pix);
					
					old_x_pix = x_pix;
					
					p_disp_chan->m_iYLastPixel = y_pix;
				}
			}
			else
			{
				dc.MoveTo(x_pix, y_pix);
				
				old_x_pix = x_pix;
				
				p_disp_chan->m_iYLastPixel = y_pix;

				p_view->m_bFirstDraw = FALSE;
			}

//			p_data+= p_view->m_uiNoOfDisplayChannels;
			
			++p_data;
			
			d_current_pix+= p_view->m_dXIncrement;

			if( (int)d_current_pix > p_view->m_rectPlot.right )
			{
				d_current_pix-= p_view->m_rectPlot.Width();

				old_x_pix-= p_view->m_rectPlot.Width();

				dc.MoveTo(old_x_pix, p_disp_chan->m_iYLastPixel );
			}
		}

		++p_disp_chan;
	}
	
	delete p_data_buffer;
	
	p_view->m_dXLastPixel = d_current_pix;

	p_view->m_iXLastPixel = old_x_pix;
	
	dc.SelectStockObject(WHITE_PEN);

	dc.MoveTo(p_view->m_iXLastPixel + 1, p_view->m_rectPlot.top);
	dc.LineTo(p_view->m_iXLastPixel + 1, p_view->m_rectPlot.bottom);

	p_view->m_bFirstDraw = FALSE;
}

void CMeScopeView :: OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	GetClientRect(&m_rectPlot);

	CalculateYFactorsAndConstants();

	m_bFirstDraw			= TRUE;
	
	if( m_dXLastPixel >= (double)(m_rectPlot.right - 50) )
	{
		m_iXLastPixel = m_rectPlot.left;

		m_dXLastPixel = (double)m_rectPlot.left;
	}
}

void CMeScopeView :: CalculateYFactorsAndConstants()
{
	SDisplayChannel* p_disp_chan = &m_arrDisplayChannels[0];
	
	for(unsigned int index_channel = 0; index_channel < m_uiNoOfDisplayChannels; index_channel++)
	{
		double d_min_scale = 0.0;

		double d_max_scale = 0.0;

		switch(p_disp_chan->m_iRange)
		{
		case ME_SCOPE_AI_BIPOLAR_10:

			d_min_scale = -10.0;

			d_max_scale = +10.0;

			break;

		case ME_SCOPE_AI_BIPOLAR_2_5:

			d_min_scale = -2.5;

			d_max_scale = +2.5;

			break;

		case ME_SCOPE_AI_UNIPOLAR_10:

			d_min_scale = +0.0;

			d_max_scale = +10.0;

			break;

		case ME_SCOPE_AI_UNIPOLAR_2_5:

			d_min_scale = +0.0;

			d_max_scale = +2.5;

			break;
		}

		/*

		If		RVf = Raw to Volt factor,
				RVc	= Raw to Volt constant

				VPf = Volt to Pixel factor
				VPc	= Volt to Pixel constant
		
				RPf = Raw to Pixel factor
				RPc	= Raw to Pixel constant

		Then	Volt	= Raw * RVf + RVc

		and		Pixel	= Volt * VPf + VPc

		so		Pixel	= (Raw * RVf + RVc) * VPf + VPc = Raw * (RVf * VPf) + (RVc * VPf + VPc)

		and so	RPf = RVf * VPf

		and		RPc = RVc * VPf + VPc

		*/

		double d_RVf = (d_max_scale - d_min_scale) / (double)0x10000;

		// and since d_RVf * -(double)0x8000 + d_RVc = d_min_scale
		
		double d_RVc = d_min_scale + d_RVf * (double)0x8000;
		
		double d_VPf = (double)m_rectPlot.Height() / (double)(p_disp_chan->m_dMin - p_disp_chan->m_dMax);

		// and since d_VPf * p_disp_chan->m_dMin + d_VPc = m_rectPlot.Top
		
		double d_VPc = (double)m_rectPlot.top - d_VPf * p_disp_chan->m_dMax;
		
//		p_disp_chan->m_dYFactor = d_RVf * d_VPf;
		
//		p_disp_chan->m_dYConstant = d_RVc * d_VPf + d_VPc;
		
		p_disp_chan->m_dYFactor = d_VPf;
		
		p_disp_chan->m_dYConstant = d_VPc;
		
		++p_disp_chan;
	}

	// For a finite acquisition, the X increment will be calculated each time in
	// OnDraw. We only calculate it here in the case of an infinite acquisition
	
	if(m_iAcqDuration == ME_SCOPE_DURATION_INFINITE)
	{
		if(m_iAcqMode == ME_SCOPE_AI_CONV_MODE_CONT_SW)
		{
			// m_dXIncrement determined by m_uiSampleRate and m_dWindowWidthSecs
			
			m_dXIncrement = (double)m_rectPlot.Width() / ( (double)m_uiSampleRate * m_dWindowWidthSecs);
		}
		else // if(m_iAcqMode == ME_SCOPE_AI_CONV_MODE_CONT_ET)
		{
			// External trigger m_dXIncrement determined by m_uiWindowWidthValues
			
			m_dXIncrement = (double)m_rectPlot.Width() /(double)(m_uiWindowWidthValues - 1);
		}
	}
}
