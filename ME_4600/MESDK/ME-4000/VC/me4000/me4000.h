// _me4000.h : main header file for the _ME4000 application
//

#if !defined(AFX__ME4000_H__90771E15_B949_42D0_9949_416748E4A743__INCLUDED_)
#define AFX__ME4000_H__90771E15_B949_42D0_9949_416748E4A743__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "..\me4000dll.h"



/////////////////////////////////////////////////////////////////////////////
// Cme4000App:
// See _me4000.cpp for the implementation of this class
//

struct ME4000Board
{
	unsigned short	m_usDeviceID;

	unsigned long	m_ulSerialNumber;

	BOOL			m_bME4000Board;

	BOOL			m_bOptoIsolated;

	// AI Teil

	unsigned int	m_uiAINoOfChannels;		// Number of single-ended AI 
											// channels on the board - depends 
											// on the device ID. 
											// There are exactly half as many  
											// differential AI channels

	BOOL			m_bAIVariableRanges;	// TRUE -	Board supports four AI 
											//			ranges: -10 - +10,
											//			-2.5 - +2.5, 0 - 10 and
											//			0 - 2.5
											//
											// FALSE -	Board only supports 
											//			AI range -10 - +10
	
	BOOL			m_bAISampleAndHold;		// TRUE - Board supports 
											// SamplaAndHold (simultaneous 
											// acquisition) on the first eight
											// AI channels - depends on the 
											// device ID

	BOOL			m_bAIDifferentialMode;	// TRUE - Board supports 
											// differential input mode for AI
											// operations
	
	BOOL			m_bAIAnalogTrigger;		// TRUE - Board has an analog 
											// trigger unit - supports 
											// ME4000_AI_TRIGGER_EXT_ANALOG
											// as iExtTriggerMode in the 
											// routines AICofig and 
											// MultiSigAIConfig

	// AO Teil

	unsigned int	m_uiAONoOfChannels;		// Number of AO channels on the 
											// board (0, 4, 8 or 16) depends on 
											// the device ID
	
	BOOL			m_uiNoOfAOFIFOs;		// Each of the first four AO channels 
											// has a FIFO attached - depends on 
											// the device ID

	// DIOTeil

	unsigned int	m_uiDIONumberOfPorts;	// Number of DIO Ports. 
											// 4 on all 46xx boards
											// 2 on some 6xxx Boards, 0 on the 
											// rest
	
	// Counter variables

    BOOL			m_uiNumberOfCounters;	// TRUE - Board contains three
											// counter chips and supports 
											// the Cnt... routines

	// External Interrupt

	BOOL			m_bExternalInterrupt;
};

class Cme4000App : public CWinApp
{
public:
	Cme4000App();

	unsigned long GetDLLVersion(void) { return(m_ulDLLVersion); }
	
	unsigned long GetDriverVersion(void) { return(m_ulDriverVersion); }
	
	int GetNumberOfBoards(void) { return(m_iNoOfBoards); }

	ME4000Board* GetBoardArray(void) { return( &m_arrBoards[0] ); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cme4000App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(Cme4000App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	unsigned long	m_ulDLLVersion;
	
	unsigned long	m_ulDriverVersion;
	
	ME4000Board		m_arrBoards[ME4000_MAX_DEVICES];
	
	int				m_iNoOfBoards;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__ME4000_H__90771E15_B949_42D0_9949_416748E4A743__INCLUDED_)
