// sample.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "sample.h"
#include "sampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTestAIContinuousDlg* m_pDlg;

///////////////////////////////////////////////////////////////////////////////
// CTestAIContinuousApp

BEGIN_MESSAGE_MAP(CTestAIContinuousApp, CWinApp)
	//{{AFX_MSG_MAP(CTestAIContinuousApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAIContinuousApp construction

CTestAIContinuousApp::CTestAIContinuousApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestAIContinuousApp object

CTestAIContinuousApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestAIContinuousApp initialization

BOOL CTestAIContinuousApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTestAIContinuousDlg dlg;

	m_pDlg = &dlg;

	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void _stdcall PlotValues(short* p_short, int count)
{
	CClientDC dc( m_pDlg->GetDlgItem(IDC_PLOT) );

	CRect rect_plot;
	
	m_pDlg->GetDlgItem(IDC_PLOT)->GetClientRect(rect_plot);

	dc.IntersectClipRect(rect_plot);
	dc.SelectStockObject(WHITE_PEN);
	
	CRect rect_erase = rect_plot;
	
	dc.SelectStockObject(BLACK_PEN);

	dc.MoveTo(rect_plot.left + m_pDlg->m_iLastXPixel + 1, rect_plot.top);
	dc.LineTo(rect_plot.left + m_pDlg->m_iLastXPixel + 1, rect_plot.bottom);

	int erase_from_pixel = m_pDlg->m_iLastXPixel + 1;
	
	int no_frames = count / m_pDlg->m_iNumberOfChannels;
	
	int erase_to_pixel = (int)(m_pDlg->m_dCurrentXPix + (double)no_frames * m_pDlg->m_dXPixIncrement);

	if(erase_to_pixel > erase_from_pixel)
	{
		if( erase_to_pixel > rect_plot.Width() )
		{
			rect_erase.left = rect_plot.left + erase_from_pixel;
			
			dc.FillSolidRect( rect_erase, RGB(0, 0, 0) );

			erase_from_pixel = 0;
			erase_to_pixel-= rect_plot.Width();
		}

		rect_erase.left = rect_plot.left + erase_from_pixel;
			
		rect_erase.right = rect_plot.left + erase_to_pixel + 1;
			
		dc.FillSolidRect( rect_erase, RGB(0, 0, 0) );
	}

	CPen* pen[4];
	
	CPen red_pen( PS_SOLID, 0, RGB(255, 0, 0) );
	CPen blue_pen( PS_SOLID, 0, RGB(0, 255, 0) );
	CPen green_pen( PS_SOLID, 0, RGB(0, 0, 255) );
	CPen yellow_pen( PS_SOLID, 0, RGB(255, 255, 0) );
	
	pen[0] = &red_pen;
	pen[1] = &blue_pen;
	pen[2] = &green_pen;
	pen[3] = &yellow_pen;

	double d_current_pix;
	
	int old_x_pix;
	
	for(int channel = 0; channel < m_pDlg->m_iNumberOfChannels; channel++)
	{
		dc.SelectObject(pen[channel]);
		
		old_x_pix = m_pDlg->m_iLastXPixel;
		
		d_current_pix = m_pDlg->m_dCurrentXPix;
		
		short* p_data = p_short;
		
		for(int frame = 0; frame < no_frames; frame++)
		{
			int x_pix = rect_plot.left + (int)d_current_pix;
				
			int y_pix;
			
			y_pix = rect_plot.bottom - (int)( m_pDlg->m_dYPixelFactor * (double)p_data[channel] ) - 10;

			if(old_x_pix != -1)
			{
				dc.MoveTo( old_x_pix, m_pDlg->m_iLastYPixel[channel] );
				dc.LineTo(x_pix, y_pix);
			}

			m_pDlg->m_iLastYPixel[channel]  = y_pix;

			p_data+= m_pDlg->m_iNumberOfChannels;
			
			old_x_pix = x_pix;
			
			d_current_pix+= m_pDlg->m_dXPixIncrement;

			if( (int)d_current_pix > rect_plot.Width() )
			{
				d_current_pix-= (double)rect_plot.Width();

				old_x_pix-= rect_plot.Width();
			}
		}
	}
	
	m_pDlg->m_dCurrentXPix = d_current_pix;

	m_pDlg->m_iLastXPixel = old_x_pix;
	
	dc.SelectStockObject(WHITE_PEN);

	dc.MoveTo(rect_plot.left + m_pDlg->m_iLastXPixel + 1, rect_plot.top);
	dc.LineTo(rect_plot.left + m_pDlg->m_iLastXPixel + 1, rect_plot.bottom);
}
