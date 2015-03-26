// _DIOTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include "..\me4000dll.h"

void _stdcall ErrorFunction(char* function_name, int error_code);

int main(int argc, char* argv[])
{
	me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

	unsigned long ul_version;
	
	me4000GetDLLVersion(&ul_version);

	printf("ME4000 - DLL Version: %08X\n", ul_version);

	me4000GetDriverVersion(&ul_version);

	printf("ME4000 - Driver Version: %08X\n\n", ul_version);

	printf(	"This program demonstrates the use of the flag ME4000_AI_SIMULTANEOUS_ENABLE\n"
			"in me4000AIConfig to synchronise data acquisition on the first four AI\n"
			"channels\n"
			"NOTE - for this program to function correctly you must have an ME4000 board\n"
			"which supports Sample&Hold\n\n"												
			"Please apply the SAME HIGH FREQUENCY ( > 100 KHz ) periodic Signal\n"
			"(z.B Sinus, Triangle) to the FIRST FOUR CHANNELS\n\n"								);	
	
	printf(	"First an AI acquisition on the first four channels with the minimum ChanTime\n"
			"with the simultaneous mode DISabled\n\n"											);

	printf("Press any key now to continue\n\n");

	getch();
	
	unsigned char arr_uc_chan[4];

	me4000AIMakeChannelListEntry(	0,								// uiChannelNumber,
									ME4000_AI_RANGE_BIPOLAR_10,		// iRange,
									&arr_uc_chan[0]				);	// pucChanListEntry)

	me4000AIMakeChannelListEntry(	1,								// uiChannelNumber,
									ME4000_AI_RANGE_BIPOLAR_10,		// iRange,
									&arr_uc_chan[1]				);	// pucChanListEntry)

	me4000AIMakeChannelListEntry(	2,								// uiChannelNumber,
									ME4000_AI_RANGE_BIPOLAR_10,		// iRange,
									&arr_uc_chan[2]				);	// pucChanListEntry)

	me4000AIMakeChannelListEntry(	3,								// uiChannelNumber,
									ME4000_AI_RANGE_BIPOLAR_10,		// iRange,
									&arr_uc_chan[3]				);	// pucChanListEntry)

	unsigned long ul_scan_ticks_low;
	
	unsigned long ul_scan_ticks_high;
	
	me4000FrequencyToTicks(	100,						// dRequiredFreq,
							&ul_scan_ticks_low,			// pulTicksLowPart,
							&ul_scan_ticks_high,		// pulTicksHighPart,
							NULL				);		// pdAchievedFreq - not required

	me4000AIConfig(	0,									// uiBoardNumber,
					&arr_uc_chan[0],					// pucChanList,
					4,									// uiChanListCount,
					ME4000_AI_INPUT_SINGLE_ENDED,		// iSDMode,
					ME4000_AI_SIMULTANEOUS_DISABLE,		// iSimultaneous,
					0,									// ulReserved,
					0,									// ulChanTicks - minimum 
					ul_scan_ticks_low,					// ulScanTicksLow,
					ul_scan_ticks_high,					// ulScanTicksHigh,
					ME4000_AI_ACQ_MODE_SOFTWARE,		// iAcqMode,
					0,									// iExtTriggerMode - not required
					0								);	// iExtTriggerEdge - not required

	short s_buffer[40];	
	
	me4000AIScan(	0,									// uiBoardNumber,
					10,									// uiNumberOfChanLists,
					&s_buffer[0],						// psBuffer,
					40,									// ulBufferSizeValues,
					ME4000_AI_SCAN_BLOCKING,			// iExecutionMode,
					NULL,								// pCallback - not required
					NULL,								// pCallbackContext - not required
					0,									// uiRefreshFrequency - not required
					NULL,								// pTerminateFunc - not required
					NULL,								// pTerminateContext - not required
					0								);	// ulTimeOutSeconds - not required

	memset( &s_buffer[0], 0, 40 * sizeof(short) );
	
	me4000AIStart(0);

	printf("%10s  %10s  %10s  %10s\n",   "Channel 1", "Channel 2", "Channel 3", "Channel 4");
	printf("%10s  %10s  %10s  %10s\n\n", "---------", "---------", "---------", "---------");
	
	for(int index_data = 0; index_data < 10; index_data++)
	{
		printf("%10d  %10d  %10d  %10d\n", 
				s_buffer[4 * index_data], s_buffer[4 * index_data + 1], 
				s_buffer[4 * index_data + 2], s_buffer[4 * index_data + 3]		);
	}

	printf("\nNow the same AI acquisition with the simultaneous mode ENabled\n\n");

	printf("Press any key now to continue\n\n");

	getch();
	
	me4000AIConfig(	0,									// uiBoardNumber,
					&arr_uc_chan[0],					// pucChanList,
					4,									// uiChanListCount,
					ME4000_AI_INPUT_SINGLE_ENDED,		// iSDMode,
					ME4000_AI_SIMULTANEOUS_ENABLE,		// iSimultaneous,
					0,									// ulReserved,
					0,									// ulChanTicks - minimum 
					ul_scan_ticks_low,					// ulScanTicksLow,
					ul_scan_ticks_high,					// ulScanTicksHigh,
					ME4000_AI_ACQ_MODE_SOFTWARE,		// iAcqMode,
					0,									// iExtTriggerMode - not required
					0								);	// iExtTriggerEdge - not required

	me4000AIScan(	0,									// uiBoardNumber,
					10,									// uiNumberOfChanLists,
					&s_buffer[0],						// psBuffer,
					40,									// ulBufferSizeValues,
					ME4000_AI_SCAN_BLOCKING,			// iExecutionMode,
					NULL,								// pCallback - not required
					NULL,								// pCallbackContext - not required
					0,									// uiRefreshFrequency - not required
					NULL,								// pTerminateFunc - not required
					NULL,								// pTerminateContext - not required
					0								);	// ulTimeOutSeconds - not required

	memset( &s_buffer[0], 0, 40 * sizeof(short) );
	
	me4000AIStart(0);

	printf("%10s  %10s  %10s  %10s\n",   "Channel 1", "Channel 2", "Channel 3", "Channel 4");
	printf("%10s  %10s  %10s  %10s\n\n", "---------", "---------", "---------", "---------");
	
	for(index_data = 0; index_data < 10; index_data++)
	{
		printf("%10d  %10d  %10d  %10d\n", 
				s_buffer[4 * index_data], s_buffer[4 * index_data + 1], 
				s_buffer[4 * index_data + 2], s_buffer[4 * index_data + 3]		);
	}

	printf("\nPress any key to terminate\n");

	_getch();

	return 0;
}

