/*-----------------------------------------------------------------------------
	File: ME3000EX.C   
------------------------------------------------------------------------------- 

	Meilhaus Electronic GmbH

	This module contains sample code for callback routines. 



	Version 1.000:		02.03.98	First version
											  
------------------------------------------------------------------------------- 
	Author: Max Kormaier                                        (c) 1998   MK 
-----------------------------------------------------------------------------*/
//
//
// The functionality of a callback routine depends on the application,  
// so it is up to you to define how your callbacks should work.
//
// The functions below are intended to demonstrate the parameters 
// of callback routines used by the ME3000 API DLL.
//
//
//
// This typedefs are to be found in meDefs.h. 
//--------------------------------------------------------------------
// typedef void (_stdcall *PVOID_PROC)  (void);
// typedef void (_stdcall *P_1_PROC)    (short*, int);
// typedef void (_stdcall *PSHORT_PROC) (short*);
//
void _stdcall ExternInterruptHandler(void);		//	PVOID_PROC
void _stdcall AOContinuousHandler(void);		//	PVOID_PROC
void _stdcall CounterAInterruptHandler(void);	//  PVOID_PROC
void _stdcall CounterBInterruptHandler(void);	//  PVOID_PROC
void _stdcall AIMultipleHandler(short*, int);	//  P_1_PROC
void _stdcall AISingleHandler(short*);			//  PSHORT_PROC



/*---------------------------------------------------------------

   ExternInterruptHandler

---------------------------------------------------------------*/
void _stdcall ExternInterruptHandler(void)
{
	glExtIrqCount++;
	MessageBeep(-1);
}



/*---------------------------------------------------------------

   CounterAInterruptHandler

---------------------------------------------------------------*/
void _stdcall CounterAInterruptHandler(void)
{
	glCounterAIrqCount++;
	MessageBeep(-1);
}



/*---------------------------------------------------------------

   CounterBInterruptHandler

---------------------------------------------------------------*/
void _stdcall CounterBInterruptHandler(void)
{
	glCounterBIrqCount++;
	MessageBeep(-1);
}



/*---------------------------------------------------------------

   AISingleHandler

---------------------------------------------------------------*/
void _stdcall AISingleHandler(short *psValue)
{
	sprintf(szText,"ADC channel %d = 0x%x %6.3f [V]", 
			 giADCChannel, 
			 *psValue,
			 ADC_TO_VOLT(*psValue,gdHalfRange,gdADCOffset));
	SetWindowText(hWndMain,(LPSTR)szText);
}



/*---------------------------------------------------------------

   AIMultipleHandler

---------------------------------------------------------------*/
void _stdcall AIMultipleHandler(short *psBuffer, int iCount)
{
	int i;

	for (i=0;i<iCount;i++)
	{
		... = psBuffer[i]; 
	}
}



/*---------------------------------------------------------------

   AOContinuousHandler

---------------------------------------------------------------*/
void _stdcall AOContinuousHandler(void)
{
	MessageBox(0,"Finish!","AOContinuousEx", MB_OK | MB_ICONINFORMATION); 
}

