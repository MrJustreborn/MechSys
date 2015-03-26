// _DioBitPatternTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include "..\me4000dll.h"

BOOL b_terminated = FALSE;

short s_buffer[0x10000];

void _stdcall TestErrorFunction(char* function_name, int error_code);

void _stdcall AOTerminate (void* pTerminateContext);

int main(int argc, char* argv[])
{
	me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

	unsigned long ul_version;
	
	me4000GetDLLVersion(&ul_version);

	printf("DLL Version: %08X\n", ul_version);

	me4000GetDriverVersion(&ul_version);

	printf("Driver Version: %08X\n\n", ul_version);

	printf(	"This program uses the me4000DioBitPattern routines to emit a series of square\n"
			"wave signals on each of the contacts DIO_A0 to DIO_A7 and DIO_B0 to DIO_B7\n"
			"with the following frequencies:\n\n"

			"DIO_A0:  32768 KHz\n"
			"DIO_A1:  16384 KHz\n"
			"DIO_A2:   8192 KHz\n"
			"... ... ... ... .\n"
			"DIO_A7:    256  Hz\n"  
			"DIO_B0:    128  Hz\n"  
			"DIO_B1:     64  Hz\n"  
			"... ... ... ... ..\n"
			"DIO_B6:      2  Hz\n"  
			"DIO_B7:      1  Hz\n\n" 															);

	me4000DIOBPPortConfig(0, ME4000_DIOBP_PORT_A, ME4000_DIOBP_OUTPUT_MODE_BYTE_LOW);

	me4000DIOBPPortConfig(0, ME4000_DIOBP_PORT_B, ME4000_DIOBP_OUTPUT_MODE_BYTE_HIGH);

	unsigned short us_value = 0;

	for(int index = 0; index < 0x10000; index++)
	{
		*( (unsigned short*)&s_buffer[index] ) = us_value++;
	}
	
	unsigned long ul_ticks_low;
	
	unsigned long ul_ticks_high;

	double d_achieved_freq;
	
	me4000FrequencyToTicks( (double)0x10000, &ul_ticks_low, &ul_ticks_high, &d_achieved_freq );

	me4000DIOBPConfig(0, ul_ticks_low, ME4000_DIOBP_TRIGGER_SOFTWARE, 0);

	me4000DIOBPWraparound(0, &s_buffer[0], 0x10000, 0,  ME4000_DIOBP_WRAPAROUND_ASYNCHRONOUS, AOTerminate, NULL, 0);

	printf("Press any key to begin\n\n");
	
	getch();
	
	b_terminated = FALSE;
	
	me4000DIOBPStart(0);
											
	printf("Press any key to terminate\n\n");
	
	getch();
	
	me4000DIOBPStop(0, ME4000_DIOBP_STOP_MODE_LAST_VALUE);

	printf("Please wait\n\n");

	while(TRUE)
	{
		if(b_terminated)
		{
			break;
		}

		Sleep(100);
	}
	
	printf("Press any key to exit\n\n");
	
	getch();
	
	return 0;
}

void _stdcall AOTerminate (void* pTerminateContext)
{
	printf("************************\n\n");
	printf("DIOBitPattern terminated\n\n");
	printf("************************\n\n");

	b_terminated = TRUE;
}
