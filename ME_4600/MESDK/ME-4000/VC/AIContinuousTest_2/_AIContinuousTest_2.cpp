// _AIScanTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include <math.h>

#include "..\me4000dll.h"

void _stdcall ErrorFunction(char* function_name, int error_code);

// Forward declaration for the callback routine

void _stdcall ContinuousCallback(short* psValues, unsigned int uiNumberOfValues, 
															void* pCallbackContext, int iLastError);
unsigned char uc_chan_list[4];

int main(int argc, char* argv[])
{
	HANDLE  h_console = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord;

	coord.X = 120;
	
	coord.Y = 2000;
	
	SetConsoleScreenBufferSize(h_console, coord);

	me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

	unsigned long ul_version;
	
	me4000GetDLLVersion(&ul_version);

	printf("ME4000 - DLL Version: %08X\n", ul_version);

	me4000GetDriverVersion(&ul_version);

	printf("ME4000 - Driver Version: %08X\n\n", ul_version);

	printf(	"This program demonstrates the use of the routine me4000AIContinuous\n"
			"WITH a callback function to acquire analog data.\n\n"									
			"Data will be acquired with a sample rate of 10 Hz from the first four AD\n"
			"channels of the first me4000 board found in the system.\n"
			"The refresh frequency will be set to 20 and so the callback function will\n"
			"be called approximately every two seconds and the newly acquired data displayed\n"
			"on the screen.\n\n"
			"If you connect an appropriate signal to any or all of the first four AD\n" 
			"channels you will be able to observe the signal dynamic in the displayed values\n\n");
	
	printf("Press any key now to continue\n\n");

	getch();

	// Create a channel list to sample the first four channels with range -10V - +10V		

	for(unsigned int index_channel = 0; index_channel < 4; index_channel++)
	{
		me4000AIMakeChannelListEntry(	index_channel,						// uiChannelNumber,
										ME4000_AI_RANGE_BIPOLAR_10,			// iRange
										&uc_chan_list[index_channel]	);	// pucChanListEntry
		
	}

	// Use me4000FrequencyToTicks to calculate the correct tick values for a
	// sum sampling rate (Scan rate) of 100 HZ

	unsigned long ul_scan_ticks_low;
	
	unsigned long ul_scan_ticks_high;
	
	me4000FrequencyToTicks(	10.0,						// dRequiredFreq,
							&ul_scan_ticks_low,			// pulTicksLowPart,
							&ul_scan_ticks_high,		// pulTicksHighPart,
							ME4000_POINTER_NOT_USED	);	// pdAchievedFreq);

	// Call me4000AIConfig 
	
	me4000AIConfig(	0,									// uiBoardNumber
					uc_chan_list,						// pucChanList
					4,									// uiChanListCount
					ME4000_AI_INPUT_SINGLE_ENDED,		// iSDMode 
					ME4000_AI_SIMULTANEOUS_DISABLE,		// iSimultaneous,
					ME4000_VALUE_NOT_USED,				// ulReserved,
					0,									// ulChanTicks - 0 --> use minimum value
					ul_scan_ticks_low,					// ulScanTicksLow,
					ul_scan_ticks_high,					// ulScanTicksHigh,
					ME4000_AI_ACQ_MODE_SOFTWARE,		// iAcqMode,
					ME4000_VALUE_NOT_USED,				// iExtTriggerMode,
					ME4000_VALUE_NOT_USED			);	// iExtTriggerEdge);

	me4000AIContinuous(	0,							// uiBoardNumber,
						ContinuousCallback,			// pCallbackProc
						ME4000_POINTER_NOT_USED,	// pCallbackContext - not required
						20,							// uiRefreshFrequency - 20 channel lists (frames)
						0						);	// ulTimeOutSeconds - not required


	printf(	"Press any key to start the acquisition\n\n");

	getch();

	printf(	"Press any key to terminate the acquisition\n\n");

	// Print the headers for the table columns
	
	printf(	"     channel 1          channel 2          channel 3          channel 4     \n"
			"     ---------          ---------          ---------          ---------     \n"
			"                                                                            \n"
			"  Digit    Volt      Digit    Volt      Digit    Volt      Digit    Volt    \n"
			"  -----    ----      -----    ----      -----    ----      -----    ----    \n\n");
	
	// Start the acquisition
	
	me4000AIStart(0);	// uiBoardNumber

	getch();

	me4000AIStop(	0,							// uiBoardNumber,
					ME4000_VALUE_NOT_USED	);	// iReserved

	printf("Press any key to exit\n\n");

	getch();
	
	return 0;
}

void _stdcall ContinuousCallback(short* psValues, unsigned int uiNumberOfValues, 
															void* pCallbackContext, int iLastError)
{
	// Check last error - buffer overflow etc.

	if(iLastError != ME4000_NO_ERROR)
	{
		return;
	}

	// Extract the data for the separate channels from our data buffer

	short s_channel[4][100];
	
	for(unsigned int index_channel = 0; index_channel < 4; index_channel++)
	{
		unsigned long ul_num_data_extracted;
		
		me4000AIExtractValues(	index_channel,					// uiChannelNumber,
								psValues,						// psAIBuffer,
								uiNumberOfValues,					// ulAIDataCount
								uc_chan_list,					// pucChanList
								4,								// uiChanListCount
								s_channel[index_channel],		// psChanBuffer,
								100,							// ulChanBufferSizeValues,
								&ul_num_data_extracted		);	// pulChanDataCount)
	}
	
	// Display the digital data and the corresponding voltage on the screen 
	// Use me4000AIDigitToVolt to convert the digital value to a voltage

	for(unsigned int index_data = 0; index_data < uiNumberOfValues / 4; index_data++)
	{
		double d_volt[4];

		for(index_channel = 0; index_channel < 4; index_channel++)
		{
			me4000AIDigitToVolt(s_channel[index_channel][index_data],		// sDigit,
								ME4000_AI_RANGE_BIPOLAR_10,					// iRange,
								&d_volt[index_channel]					);	// pdVolt);
		}

		printf(	"%7d  %7.3f   %7d  %7.3f   %7d  %7.3f   %7d  %7.3f\n",
				s_channel[0][index_data], d_volt[0],
				s_channel[1][index_data], d_volt[1],
				s_channel[2][index_data], d_volt[2],
				s_channel[3][index_data], d_volt[3]								);
	}

	printf("\n");
}
