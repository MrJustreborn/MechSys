// _AOContinuousTest_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include <math.h>

#include <time.h>

#include "..\me4000dll.h"

#include "..\sweep.h"

#define CONTINUOUS_BUFFER_SIZE	5000

short s_cont_buffer[CONTINUOUS_BUFFER_SIZE];

#define APPEND_BUFFER_SIZE		10000

short s_append_buffer[APPEND_BUFFER_SIZE];

#define BASE_FREQ	1000.0

int main(int argc, char* argv[])
{
	HANDLE  h_console = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord;

	coord.X = 120;
	
	coord.Y = 1000;
	
	SetConsoleScreenBufferSize(h_console, coord);

	me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

	unsigned long ul_version;
	
	me4000GetDLLVersion(&ul_version);

	printf("DLL Version: %08X\n", ul_version);

	me4000GetDriverVersion(&ul_version);

	printf("Driver Version: %08X\n\n", ul_version);

	printf(	"This program uses me4000AOContinuous WITHOUT a callback function and\n"
			"me4000AOAppendNewValues to emit a signal on DA channel 0 of board 0\n\n"																
			"If, before starting the output, you connect the DA channel directly\n"
			"to one of the AD channels and use the application 'meScope' to display\n"
			"the signal measured on the AD channel, you can observe the effect of the\n"
			"me4000AOContinuous and me4000AOAppendNewValues routines\n\n"											);
	
	srand( (unsigned)time( NULL ) );
	
	// Generating random sweep to begin

	int i_signal_type = ( rand() % (SIGNAL_NEG_RAMP + 1) );

	double d_from_freq = (double)( ( rand() % 10 ) + 1 );
	
	double d_to_freq = (double)( ( rand() % 10 ) + 1 );
	
	double d_from_amp = (double)( ( rand() % 9 ) + 1 );
	
	double d_to_amp = (double)( ( rand() % 9 ) + 1 );
	
	Sweep(i_signal_type, d_from_freq, d_to_freq, d_from_amp, d_to_amp, BASE_FREQ, CONTINUOUS_BUFFER_SIZE, &s_cont_buffer[0], 1);
	
	char* p_signal_type;

	switch(i_signal_type)
	{
	case SIGNAL_RECTANGLE:

		p_signal_type = "square wave";

		break;

	case SIGNAL_TRIANGLE:

		p_signal_type = "triangle wave";

		break;

	case SIGNAL_SINUS:

		p_signal_type = "sinus";

		break;

	case SIGNAL_POS_RAMP:

		p_signal_type = "positive ramp";

		break;

	case SIGNAL_NEG_RAMP:

		p_signal_type = "negative ramp";

		break;
	}

	unsigned long ul_ticks_low;
	
	unsigned long ul_ticks_high;

	double d_achieved_freq;
	
	me4000FrequencyToTicks(BASE_FREQ, &ul_ticks_low, &ul_ticks_high, &d_achieved_freq);

	me4000AOConfig(0, 0, ul_ticks_low, ME4000_AO_TRIGGER_SOFTWARE, ME4000_VALUE_NOT_USED);

	unsigned long ul_values_written;
		
	me4000AOContinuous(0, 0, &s_cont_buffer[0], CONTINUOUS_BUFFER_SIZE, ME4000_POINTER_NOT_USED, ME4000_POINTER_NOT_USED, ME4000_VALUE_NOT_USED, &ul_values_written);

	printf(	"Calling me4000AOContinuous to emit a %s signal for %d seconds\n"
			"Initial frequency: %f Hz    Final frequency: %f Hz\n"
			"Initial amplitude: %f V     Final amplitude: %f V\n\n",
			p_signal_type, (int)(CONTINUOUS_BUFFER_SIZE / BASE_FREQ), 
			d_from_freq, d_to_freq, d_from_amp, d_to_amp						);
	
	printf("Press any key to begin\n\n");
	
	getch();
	
	me4000AOStart(0, 0);
											
	printf("Press any key to stop calling me4000AOAppendNewValues\n\n");
	
	while(TRUE)
	{
		if( kbhit() )
		{
			getch();

			break;
		}

		i_signal_type = ( rand() % (SIGNAL_NEG_RAMP + 1) );

		d_from_freq = (double)( ( rand() % 10 ) + 1 );
		
		d_to_freq = (double)( ( rand() % 10 ) + 1 );
		
		d_from_amp = (double)( ( rand() % 9 ) + 1 );
		
		d_to_amp = (double)( ( rand() % 9 ) + 1 );
		
		Sweep(i_signal_type, d_from_freq, d_to_freq, d_from_amp, d_to_amp, BASE_FREQ, APPEND_BUFFER_SIZE, &s_append_buffer[0], 1);
	
		switch(i_signal_type)
		{
		case SIGNAL_RECTANGLE:

			p_signal_type = "square wave";

			break;

		case SIGNAL_TRIANGLE:

			p_signal_type = "triangle wave";

			break;

		case SIGNAL_SINUS:

			p_signal_type = "sinus";

			break;

		case SIGNAL_POS_RAMP:

			p_signal_type = "positive ramp";

			break;

		case SIGNAL_NEG_RAMP:

			p_signal_type = "negative ramp";

			break;
		}

		printf(	"Calling me4000AOAppendNewValues to emit a %s signal for %d seconds\n"
				"Initial frequency: %f Hz    Final frequency: %f Hz\n"
				"Initial amplitude: %f V     Final amplitude: %f V\n\n",
				p_signal_type, (int)(APPEND_BUFFER_SIZE / BASE_FREQ), 
				d_from_freq, d_to_freq, d_from_amp, d_to_amp						);
	
		unsigned long ul_values_appended;
		
		me4000AOAppendNewValues(0, 0, &s_append_buffer[0], APPEND_BUFFER_SIZE, 
									ME4000_AO_APPEND_NEW_VALUES_BLOCKING, &ul_values_appended);

		printf("%lu values appended\n\n", ul_values_appended);

		printf("Press any key to stop calling me4000AOAppendNewValues\n\n");
	}
	
	printf(	"Press any key to terminate the operation immediately or wait until\n"
			"the last value is output\n\n"											);
	
	while(TRUE)
	{
		int i_status;
		
		me4000AOGetStatus(0, 0, ME4000_AO_WAIT_NONE, &i_status);
		
		if(i_status == ME4000_AO_STATUS_IDLE)
		{
			break;
		}

		if( kbhit() )
		{
			me4000AOStop(0, 0, ME4000_AO_STOP_MODE_IMMEDIATE);
		}

		Sleep(50);
	}
	
	printf("Press any key to exit\n\n");
	
	getch();
	
	return 0;
}

