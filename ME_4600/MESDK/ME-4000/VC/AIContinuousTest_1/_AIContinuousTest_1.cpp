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

	printf(	"This program demonstrates the use of the routine me4000AIContinuous\n"
			"WITHOUT a callback function to acquire analog data.\n\n"									
			"Data will be acquired with a sample rate of 10 Hz from the first four AD\n"
			"channels of the first me4000 board found in the system.\n"
			"The refresh frequency will be set to 5 and me4000GetNewValues will be called\n"
			"approximately every two seconds and the newly acquired data displayed on the\n"
			"screen.\n\n"
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
						ME4000_POINTER_NOT_USED,	// pCallbackProc - not used here
						ME4000_POINTER_NOT_USED,	// pCallbackContext - not required
						5,							// uiRefreshFrequency - 5 channel lists (frames)
						0						);	// ulTimeOutSeconds - not required


	// Allocate a buffer for the results.
	// At 10 Hz, if we collect the data every two seconds we expect 20 channel lists (frames)
	// We allocate a buffer large enough for 100

	short* p_s_buffer = new short[100 * 4];
	
	short* p_s_channel[4];

	for(index_channel = 0; index_channel < 4; index_channel++)
	{
		p_s_channel[index_channel] = new short[100];
	}
	
	printf(	"Press any key to start the acquisition\n\n"
			"Press any other key at any time to terminate the acquisition\n\n");

	getch();

	// Print the headers for the table columns
	
	printf(	"     channel 1          channel 2          channel 3          channel 4     \n"
			"     ---------          ---------          ---------          ---------     \n"
			"                                                                            \n"
			"  Digit    Volt      Digit    Volt      Digit    Volt      Digit    Volt    \n"
			"  -----    ----      -----    ----      -----    ----      -----    ----    \n\n");
	
	// Start the acquisition
	
	me4000AIStart(0);	// uiBoardNumber

	int i_sleep_count = 0;

	while(TRUE)
	{
		Sleep(250);	// 250 Milliseconds delay
		
		if( kbhit() )
		{
			getch();

			break;
		}

		if(++i_sleep_count >= 8)
		{
			// Every two seconds (8 * 250 milliseconds)

			i_sleep_count = 0;

			unsigned long ul_data_read;

			int i_last_error;
			
			me4000AIGetNewValues(	0,											// uiBoardNumber,
									p_s_buffer,									// psBuffer,
									100,										// ulNumberOfValuesToRead - maximum
									ME4000_AI_GET_NEW_VALUES_NON_BLOCKING,		// iExecutionMode - Non blocking --> return immediately with available data
									&ul_data_read,								// pulNumberOfValuesRead,
									&i_last_error							);	// piLastError);
			
			// Check last error - buffer overflow etc.

			if(i_last_error != ME4000_NO_ERROR)
			{
				break;
			}
		
			// Extract the data for the separate channels from our data buffer

			for(index_channel = 0; index_channel < 4; index_channel++)
			{
				unsigned long ul_num_data_extracted;
				
				me4000AIExtractValues(	index_channel,					// uiChannelNumber,
										p_s_buffer,						// psAIBuffer,
										ul_data_read,					// ulAIDataCount
										uc_chan_list,					// pucChanList
										4,								// uiChanListCount
										p_s_channel[index_channel],		// psChanBuffer,
										100,							// ulChanBufferSizeValues,
										&ul_num_data_extracted		);	// pulChanDataCount)
			}
			
			// Display the digital data and the corresponding voltage on the screen 
			// Use me4000AIDigitToVolt to convert the digital value to a voltage

			for(unsigned int index_data = 0; index_data < ul_data_read / 4; index_data++)
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

			printf("\n");
		}
	}

	me4000AIStop(	0,							// uiBoardNumber,
					ME4000_VALUE_NOT_USED	);	// iReserved

	for(index_channel = 0; index_channel < 4; index_channel++)
	{
		delete p_s_channel[index_channel];
	}
	
	delete p_s_buffer;
	
	printf("Press any key to exit\n\n");

	getch();
	
	return 0;
}

