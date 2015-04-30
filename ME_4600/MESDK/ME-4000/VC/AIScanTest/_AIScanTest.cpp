// _AIScanTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include <math.h>

#include "..\me4000dll.h"

void _stdcall ErrorFunction(char* function_name, int error_code);

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

	printf(	"This program demonstrates the use of the routine me4000AIScan to acquire a\n"
			"pre-determined amount of data,\n\n"									
			"Data will be acquired with a sample rate of 100 Hz from the first four AD\n"
			"channels of the first me4000 board found in the system.\n"
			"1000 values will be sampled from each channel, and on completion the data will\n"
			"be displayed on the screen.\n\n"
			"If you connect an appropriate signal to any or all of the first four AD\n" 
			"channels you will be able to observe the signal dynamic in the displayed values\n\n");
	
	printf("Press any key now to continue\n\n");

	getch();

	// Create a channel list to sample the first four channels with range -10V - +10V		

	unsigned char uc_chan_list[4];

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
	
	me4000FrequencyToTicks(	100.0,						// dRequiredFreq,
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

	// Allocate a buffer for the results.
	// We want to collect 1000 channel lists (frames) and the channel list 
	// contains 4 entries so we need a buffer large enough to contain 1000 * 4
	// shorts

	short* p_s_buffer = new short[1000 * 4];
	
	me4000AIScan(	0,							// uiBoardNumber,
					1000,						// uiNumberOfChanLists,
					p_s_buffer,					// psBuffer,
					1000 * 4,					// ulBufferSizeValues,
					ME4000_AI_SCAN_BLOCKING,	// iExecutionMode - Blocking --> we must wait until the acquisition is finished
					ME4000_POINTER_NOT_USED,	// pCallbackProc - not used here
					ME4000_POINTER_NOT_USED,	// pCallbackContext - not required
					0,							// uiRefreshFrequency - default --> API will supply a suitable value
					ME4000_POINTER_NOT_USED,	// pTerminateProc - not used here
					ME4000_POINTER_NOT_USED,	// pTerminateContext - not required
					ME4000_VALUE_NOT_USED	);	// ulTimeOutSeconds - not required


	
	printf("Press any key to start the acquisition - this will take 10 seconds\n\n");

	getch();

	printf("Please wait\n\n");

	// Start the acquisition
	
	me4000AIStart(0);	// uiBoardNumber

	// The next line of code will not be executed until all the data has been
	// acquired

	// Allocate a buffer for the data values for each channel
	
	short* p_s_channel[4];

	for(index_channel = 0; index_channel < 4; index_channel++)
	{
		p_s_channel[index_channel] = new short[1000];
	}
	
	// Extract the data for the separate channels from our data buffer

	for(index_channel = 0; index_channel < 4; index_channel++)
	{
		unsigned long ul_num_data_extracted;
		
		me4000AIExtractValues(	index_channel,					// uiChannelNumber,
								p_s_buffer,						// psAIBuffer,
								4 * 1000,						// ulAIDataCount
								uc_chan_list,					// pucChanList
								4,								// uiChanListCount
								p_s_channel[index_channel],		// psChanBuffer,
								1000,							// ulChanBufferSizeValues,
								&ul_num_data_extracted		);	// pulChanDataCount)
	}

	// Display the digital data and the corresponding voltage on the screen 
	// Use me4000AIDigitToVolt to convert the digital value to a voltage

	printf(	"     channel 1          channel 2          channel 3          channel 4     \n"
			"     ---------          ---------          ---------          ---------     \n"
			"                                                                            \n"
			"  Digit    Volt      Digit    Volt      Digit    Volt      Digit    Volt    \n"
			"  -----    ----      -----    ----      -----    ----      -----    ----    \n\n");
	
	for(unsigned int index_data = 0; index_data < 1000; index_data++)
	{
		double d_volt[4];

		for(index_channel = 0; index_channel < 4; index_channel++)
		{
			me4000AIDigitToVolt(p_s_channel[index_channel][index_data],		// sDigit,
								ME4000_AI_RANGE_BIPOLAR_10,					// iRange,
								&d_volt[index_channel]					);	// pdVolt);
		}

		printf(	"%7d  %7.3f   %7d  %7.3f   %7d  %7.3f   %7d  %7.3f\n",
				p_s_channel[0][index_data], d_volt[0],
				p_s_channel[1][index_data], d_volt[1],
				p_s_channel[2][index_data], d_volt[2],
				p_s_channel[3][index_data], d_volt[3]								);
	}

	for(index_channel = 0; index_channel < 4; index_channel++)
	{
		delete p_s_channel[index_channel];
	}
	
	delete p_s_buffer;
	
	printf("Press any key to exit\n\n");

	getch();
	
	return 0;
}

