// _AODemuxTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include "..\me4000dll.h"

#include "..\sweep.h"

#define SIGNAL_FREQ			1000

#define SIGNAL_BUFFER_SIZE	10000

#define BASE_FREQ			32 * SIGNAL_FREQ

#define BUFFER_SIZE			32 * SIGNAL_BUFFER_SIZE

short s_buffer[BUFFER_SIZE];

void _stdcall TestErrorFunction(char* function_name, int error_code);

void _stdcall AOTerminate (void* pTerminateContext);

BOOL b_terminated = FALSE;

int main(int argc, char* argv[])
{
	me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

	unsigned long ul_version;
	
	me4000GetDLLVersion(&ul_version);

	printf("DLL Version: %08X\n", ul_version);

	me4000GetDriverVersion(&ul_version);

	printf("Driver Version: %08X\n\n", ul_version);

	printf(	"This program uses the me4000AODemux routines to emit a series of signals on\n"
			"Demux channels 0 to 32\n\n"													);

	int i_signal_type = SIGNAL_RECTANGLE;

	double d_from_freq = 100;
	
	double d_to_freq = 1;
	
	double d_from_amp = 1;
	
	double d_to_amp = 10;
	
	for(int index = 0; index < 32; index++)
	{
        Sweep(i_signal_type, d_from_freq, d_to_freq, 
									d_from_amp, d_to_amp, SIGNAL_FREQ, 
											SIGNAL_BUFFER_SIZE, &s_buffer[index], 32);
			
		if(++i_signal_type > SIGNAL_NEG_RAMP)
		{
			i_signal_type = SIGNAL_RECTANGLE;
		}

		d_from_freq-= 3.0;

		d_from_amp+= 0.25;

/*
        for(int count = 0; count < SIGNAL_BUFFER_SIZE; count++)
        {
            s_buffer[index + count * 32] = index * 2000;
        }
*/
  }
	
	unsigned char mux_list[32];

	for(index = 0; index < 32; index++)
	{
		mux_list[index] = index;
	}
	
	unsigned long ul_ticks_low;
	
	unsigned long ul_ticks_high;

	double d_achieved_freq;
	
	me4000FrequencyToTicks(BASE_FREQ, &ul_ticks_low, &ul_ticks_high, &d_achieved_freq);

	me4000MultiSigAOOpen(0);

	me4000MultiSigAOConfig(	0,								// uiBoardNumber,
							&mux_list[0],					// pucDemuxChanList, 
							32,								// uiDemuxChanListCount
							ul_ticks_low,					// ulIntervalTicks
							ME4000_AO_TRIGGER_SOFTWARE,		// iTriggerMode
							0							);	// iExtTriggerEdge - not required

	me4000MultiSigAOWraparound(	0,										// uiBoardNumber, 
								&s_buffer[0],							// pusAOBuffer
								BUFFER_SIZE,							// ulAONumberOfData, 
								0,										// ulLoops --> infinite
								ME4000_AO_WRAPAROUND_ASYNCHRONOUS,		// iExecutionMode, 
								AOTerminate,							// pTerminateFunc, 
								NULL,									// pTerminateContext 
								0									);	// ulTimeOutSeconds

	printf("Press any key to begin\n\n");
	
	getch();

	b_terminated = FALSE;
	
	me4000MultiSigAOStart(0);
											
	printf("Press any key to terminate\n\n");
	
	getch();
	
	me4000MultiSigAOStop(0, ME4000_AO_STOP_MODE_LAST_VALUE);

	printf("Please wait\n\n");

	while(TRUE)
	{
		if(b_terminated)
		{
			break;
		}

		Sleep(100);
	}
	
	me4000MultiSigAOClose(0);

	printf("Press any key to exit\n\n");
	
	getch();
	
	return 0;
}

void _stdcall AOTerminate (void* pTerminateContext)
{
	printf("**********************\n\n");
	printf("Demux terminated\n\n");
	printf("**********************\n\n");

	b_terminated = TRUE;
}
