// _me4000.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "me4000.h"

#include "ME4000PropertySheet.h"

#include "InfoPP.h"
#include "AnalogInputPP.h"
#include "AnalogOutputPP.h"
#include "DigitalIOPP.h"
#include "CounterPWMPP.h"
#include "ExternalInterruptPP.h"
#include "DIOBitPatternPP.h"
#include "MultiSigPP.h"
#include "MultiSigAnalogInputPP.h"
#include "MultiSigAnalogOutputPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cme4000App

BEGIN_MESSAGE_MAP(Cme4000App, CWinApp)
	//{{AFX_MSG_MAP(Cme4000App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cme4000App construction

Cme4000App::Cme4000App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	m_ulDLLVersion		= 0;
	
	m_ulDriverVersion	= 0;
	
	memset( &m_arrBoards[0], 0, ME4000_MAX_DEVICES * sizeof(ME4000Board) );
	
	m_iNoOfBoards = 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only Cme4000App object

Cme4000App theApp;

/////////////////////////////////////////////////////////////////////////////
// Cme4000App initialization

BOOL Cme4000App::InitInstance()
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

	if(me4000GetDLLVersion(&m_ulDLLVersion) != ME4000_NO_ERROR)
	{
		return(FALSE);
	}

	if(me4000GetDriverVersion(&m_ulDriverVersion) != ME4000_NO_ERROR)
	{
//		return(FALSE);
	}

	for(m_iNoOfBoards = 0; m_iNoOfBoards < ME4000_MAX_DEVICES; m_iNoOfBoards++)
	{
		if( me4000GetBoardVersion(m_iNoOfBoards, &m_arrBoards[m_iNoOfBoards].m_usDeviceID) != ME4000_NO_ERROR )
		{
			break;
		}

		me4000GetSerialNumber(m_iNoOfBoards, &m_arrBoards[m_iNoOfBoards].m_ulSerialNumber);

		if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x6F00) == 0x4600)
		{
			m_arrBoards[m_iNoOfBoards].m_bME4000Board = TRUE;
		}
		else
		{
			m_arrBoards[m_iNoOfBoards].m_bME4000Board = FALSE;
		}

		m_arrBoards[m_iNoOfBoards].m_bOptoIsolated = FALSE;

		if( ( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x6F01) == 0x4601)||
								( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x6010) == 0x6010) )
		{
			m_arrBoards[m_iNoOfBoards].m_bOptoIsolated = TRUE;
		}

		if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID == 0x4610)||
					(m_arrBoards[m_iNoOfBoards].m_usDeviceID == 0x4650)||
							( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0xFFF0) == 0x4660 ) )
		{
			m_arrBoards[m_iNoOfBoards].m_uiAINoOfChannels = 16;
		}
		else if(m_arrBoards[m_iNoOfBoards].m_bME4000Board)
		{
			m_arrBoards[m_iNoOfBoards].m_uiAINoOfChannels = 32;
		}
		else
		{
			m_arrBoards[m_iNoOfBoards].m_uiAINoOfChannels = 0;
		}

		if( (m_arrBoards[m_iNoOfBoards].m_bME4000Board)&&
						(m_arrBoards[m_iNoOfBoards].m_usDeviceID != 0x4610) )
		{
			m_arrBoards[m_iNoOfBoards].m_bAIVariableRanges = TRUE;
		}
		else
		{
			m_arrBoards[m_iNoOfBoards].m_bAIVariableRanges = FALSE;
		}

		if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x6F02) == 0x4602)
		{
			m_arrBoards[m_iNoOfBoards].m_bAISampleAndHold = TRUE;
		}
		else
		{
			m_arrBoards[m_iNoOfBoards].m_bAISampleAndHold = FALSE;
		}

		if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID == 0x4610)||
					(m_arrBoards[m_iNoOfBoards].m_usDeviceID == 0x4650)||
							( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0xFFF0) == 0x4660 ) )
		{
			m_arrBoards[m_iNoOfBoards].m_bAIDifferentialMode = FALSE;			
		}
		else if(m_arrBoards[m_iNoOfBoards].m_bME4000Board)
		{
			m_arrBoards[m_iNoOfBoards].m_bAIDifferentialMode = TRUE;			
		}
		else
		{
			m_arrBoards[m_iNoOfBoards].m_bAIDifferentialMode = FALSE;			
		}
    
		if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID == 0x4610)||
					(m_arrBoards[m_iNoOfBoards].m_usDeviceID == 0x4650)||
						( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0xFFF0) == 0x4660 ) )
		{
			m_arrBoards[m_iNoOfBoards].m_bAIAnalogTrigger = FALSE;			
		}
		else if(m_arrBoards[m_iNoOfBoards].m_bME4000Board)
		{
			m_arrBoards[m_iNoOfBoards].m_bAIAnalogTrigger = TRUE;			
		}
		else
		{
			m_arrBoards[m_iNoOfBoards].m_bAIAnalogTrigger = FALSE;			
		}
    
		if(m_arrBoards[m_iNoOfBoards].m_bME4000Board)
		{
			if( ( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x00F0) == 0x0070 )
									||( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x00F0) == 0x0080 ) )
			{
				m_arrBoards[m_iNoOfBoards].m_uiAONoOfChannels = 4;

				if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x00F0) == 0x0080 )
				{
					m_arrBoards[m_iNoOfBoards].m_uiNoOfAOFIFOs = 4;
				}
				else
				{
					m_arrBoards[m_iNoOfBoards].m_uiNoOfAOFIFOs = 0;
				}
			}
			else if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x00F0) == 0x0060 )
			{
				m_arrBoards[m_iNoOfBoards].m_uiAONoOfChannels	= 2;

				m_arrBoards[m_iNoOfBoards].m_uiNoOfAOFIFOs = 0;
			}
			else
			{
				m_arrBoards[m_iNoOfBoards].m_uiAONoOfChannels	= 0;

				m_arrBoards[m_iNoOfBoards].m_uiNoOfAOFIFOs = 0;
			}
		}
		else
		{
			// ME6000 Board

			if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x6100) == 0x6100 )
			{
				m_arrBoards[m_iNoOfBoards].m_uiNoOfAOFIFOs = 4;
			}
			else
			{
				m_arrBoards[m_iNoOfBoards].m_uiNoOfAOFIFOs = 0;
			}
				
			if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x600F) == 0x6004 ) 
			{
				m_arrBoards[m_iNoOfBoards].m_uiAONoOfChannels	= 4;
			}
			else if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x600F) == 0x6008 ) 
			{
				m_arrBoards[m_iNoOfBoards].m_uiAONoOfChannels	= 8;
			}
			else if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x600F) == 0x600F ) 
			{
				m_arrBoards[m_iNoOfBoards].m_uiAONoOfChannels	= 16;
			}
		}

		if(m_arrBoards[m_iNoOfBoards].m_bME4000Board)
		{
			m_arrBoards[m_iNoOfBoards].m_uiDIONumberOfPorts = 4;
		}
		else if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x0040) == 0x0040 )
		{
			m_arrBoards[m_iNoOfBoards].m_uiDIONumberOfPorts = 2;
		}
		else
		{
			m_arrBoards[m_iNoOfBoards].m_uiDIONumberOfPorts = 0;
		}

		if(m_arrBoards[m_iNoOfBoards].m_usDeviceID == 0x4650)
		{
			m_arrBoards[m_iNoOfBoards].m_uiNumberOfCounters = 0;			
		}
		else  if( (m_arrBoards[m_iNoOfBoards].m_usDeviceID & 0x6F00) == 0x4600 )
		{
			m_arrBoards[m_iNoOfBoards].m_uiNumberOfCounters = 3;			
		}
		else
		{
			m_arrBoards[m_iNoOfBoards].m_uiNumberOfCounters = 0;			
		}
	}
	
/*
	m_iNoOfBoards = 4;

	m_arrBoards[0].m_usDeviceID		= 0x4650;
	m_arrBoards[0].m_ulSerialNumber	= 0x10001000;

	m_arrBoards[1].m_usDeviceID		= 0x4661;
	m_arrBoards[1].m_ulSerialNumber	= 0x20002000;

	m_arrBoards[2].m_usDeviceID		= 0x4672;
	m_arrBoards[2].m_ulSerialNumber	= 0x30003000;

	m_arrBoards[3].m_usDeviceID		= 0x4683;
	m_arrBoards[3].m_ulSerialNumber	= 0x40004000;
*/

	me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

	CME4000PropertySheet me4000_ps("Meilhaus Electronic    -    ME4000 Test Programm");

	CInfoPP info_pp;

	info_pp.m_pPropertySheet = &me4000_ps;
		
	me4000_ps.AddPage(&info_pp);

	CAnalogInputPP ai_pp;
		
	ai_pp.m_pPropertySheet = &me4000_ps;

	me4000_ps.AddPage(&ai_pp);

	CAnalogOutputPP ao_pp;
		
	ao_pp.m_pPropertySheet = &me4000_ps;
		
	me4000_ps.AddPage(&ao_pp);

	CDigitalIOPP dio_pp;
		
	dio_pp.m_pPropertySheet = &me4000_ps;
		
	me4000_ps.AddPage(&dio_pp);

	CCounterPWMPP c_pwm_pp;
		
	c_pwm_pp.m_pPropertySheet = &me4000_ps;
		
	me4000_ps.AddPage(&c_pwm_pp);

	CExternalInterruptPP ext_int_pp;
		
	ext_int_pp.m_pPropertySheet = &me4000_ps;
		
	me4000_ps.AddPage(&ext_int_pp);

	CDIOBitPatternPP dio_bp_pp;
		
	dio_bp_pp.m_pPropertySheet = &me4000_ps;
		
	me4000_ps.AddPage(&dio_bp_pp);

	CMultiSigPP multisig_pp;
		
	multisig_pp.m_pPropertySheet = &me4000_ps;
		
	me4000_ps.AddPage(&multisig_pp);

	CMultiSigAnalogInputPP multisig_ai_pp;
		
	multisig_ai_pp.m_pPropertySheet = &me4000_ps;
		
	me4000_ps.AddPage(&multisig_ai_pp);

	CMultiSigAnalogOutputPP multisig_ao_pp;
		
	multisig_ao_pp.m_pPropertySheet = &me4000_ps;
		
	me4000_ps.AddPage(&multisig_ao_pp);

	m_pMainWnd = &me4000_ps;

	int nResponse = me4000_ps.DoModal();

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
