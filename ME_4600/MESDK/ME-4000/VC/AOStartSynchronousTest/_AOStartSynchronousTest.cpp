// _AOSimultaneousTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include <math.h>

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

	printf(	"This program demonstrates the use of the routine me4000AOStartSynchronous\n"
			"to synchronise data output on the four AO channels\n\n"
			"me4000AOWraparound will be called for each of the four channels with a\n"
			"buffer containing 4096 values defining a sinus curve. Because the buffer\n"
			"only contains 4096 values, the cyclical signal output takes place entirely\n"
			"on the firmware level and requires no system resources.\n\n"
			"NOTE - for this program to function correctly you must have an ME4000 board\n"
			"of the 468x class\n\n"															);
	
	printf("Press any key now to continue\n\n");

	getch();
	
	short s_buffer[4096];

	for(int index = 0; index < 4096; index++)
	{
		double d_volt = 6.2 * sin(2 * 3.14159 * (double)index / 4096.0);
		
		me4000AOVoltToDigit(d_volt,					// dVolt,
							&s_buffer[index]	);	// psDigit
	}
	
	for(int index_channel = 0; index_channel < 4; index_channel++)
	{
		me4000AOConfig(	0,								// uiBoardNumber,
						index_channel,					// uiChannelNumber,
						0,								// ulTicks - Minimum
						ME4000_AO_TRIGGER_SOFTWARE,		// iTriggerMode - will be overwritten in me4000AOStartSynchronous below
						0							);	// iExtTriggerEdge 					

		me4000AOWraparound(	0,										// uiBoardNumber,
							index_channel,							// uiChannelNumber,
							&s_buffer[0],							// psBuffer,
							4096,									// ulDataCount,
							ME4000_AO_WRAPAROUND_INFINITE,			// ulLoops,
							ME4000_AO_WRAPAROUND_ASYNCHRONOUS,		// iExecutionMode
							NULL,									// pTerminateFunc - not required
							NULL,									// pTerminateContext - not required
							0								);		// ulTimeOutSeconds - not required
	}


	printf("Press any key to start\n\n");
	
	_getch();

	unsigned int ui_channel_number[4];

	ui_channel_number[0] = 0;
	ui_channel_number[1] = 1;
	ui_channel_number[2] = 2;
	ui_channel_number[3] = 3;
	
	me4000AOStartSynchronous(	0,									// uiBoardNumber,
								&ui_channel_number[0],				// puiChannelNumber
								4,									// ulCount,
								ME4000_AO_TRIGGER_SOFTWARE,			// iTriggerMode
								ME4000_POINTER_NOT_USED,			// piExtTriggerEnable - not required
								ME4000_POINTER_NOT_USED,			// piExtTriggerEdge - not required
								ME4000_VALUE_NOT_USED		);		// ulTimeOutSeconds - not required

	printf("Press any key to stop\n\n");
	
	_getch();

	for(index_channel = 0; index_channel < 4; index_channel++)
	{
		me4000AOStop(	0,									// uiBoardNumber,
						index_channel,						// uiChannelNumber
						ME4000_AO_STOP_MODE_LAST_VALUE	);	// iStopMode
	}

	for(index_channel = 0; index_channel < 4; index_channel++)
	{
		int i_status;
		
		me4000AOGetStatus(	0,						// uiBoardNumber,
							index_channel,			// uiChannelNumber,
							ME4000_AO_WAIT_NONE,	// bWaitIdle,
							&i_status			);	// piStatus);
	}

	printf("Press any key to terminate\n\n");
	
	return 0;
}

