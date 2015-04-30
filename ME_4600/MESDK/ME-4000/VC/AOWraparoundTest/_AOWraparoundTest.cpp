// _AOWraparounfTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include <math.h>

#include "..\me4000dll.h"

#include "..\sweep.h"

void _stdcall TestErrorFunction(char* function_name, int error_code);

void _stdcall AOTerminate (void* pTerminateContext);

BOOL b_wraparound_terminated = FALSE;

BOOL b_terminate_app = FALSE;

int main(int argc, char* argv[])
{
	me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

	unsigned long ul_version;
	
	me4000GetDLLVersion(&ul_version);

	printf("DLL Version: %08X\n", ul_version);

	me4000GetDriverVersion(&ul_version);

	printf("Driver Version: %08X\n\n", ul_version);

	printf(	"This program uses the me4000AOWraparound routine to emit a signal on a chosen\n"
			"DA channel\n\n"																	);

	printf("Press any key to begin\n\n");
	
	getch();
	
	unsigned int ui_board_number;

	char buffer[128];
	
	while(TRUE)
	{
		printf("Board Number (0 - 31): (RETURN to terminate) ");

		gets(&buffer[0]);

		printf("\n\n");
		
		if(buffer[0] == 0)
		{
			b_terminate_app = TRUE;
			
			break;
		}
		
		if( (sscanf(&buffer[0], "%u", &ui_board_number) == 1 ) )
		{
			break;
		}
	}
	
	if(b_terminate_app)
	{
		exit(0);
	}

	unsigned int ui_channel_number;

	while(TRUE)
	{
		printf("Channel Number (0 - 4): (RETURN to terminate) ");

		gets(&buffer[0]);

		printf("\n\n");
		
		if(buffer[0] == 0)
		{
			b_terminate_app = TRUE;
			
			break;
		}
		
		if( (sscanf(&buffer[0], "%u", &ui_channel_number) == 1 ) )
		{
			break;
		}
	}
	
	if(b_terminate_app)
	{
		exit(0);
	}

	unsigned long ul_buffer_size;

	while(TRUE)
	{
		printf("Buffer size: (RETURN to terminate) ");

		gets(&buffer[0]);

		printf("\n\n");
		
		if(buffer[0] == 0)
		{
			b_terminate_app = TRUE;
			
			break;
		}
		
		if( (sscanf(&buffer[0], "%lu", &ul_buffer_size) == 1 ) )
		{
			break;
		}
	}
	
	if(b_terminate_app)
	{
		exit(0);
	}

	double d_output_freq;

	while(TRUE)
	{
		printf("Output frequency in Hz: (RETURN to terminate) ");

		gets(&buffer[0]);

		printf("\n\n");
		
		if(buffer[0] == 0)
		{
			b_terminate_app = TRUE;
			
			break;
		}
		
		if( (sscanf(&buffer[0], "%lf", &d_output_freq) == 1 ) )
		{
			break;
		}
	}
	
	if(b_terminate_app)
	{
		exit(0);
	}

	unsigned long ul_number_of_loops;

	while(TRUE)
	{
		printf("Number of loops (0 = Endless) : (RETURN to terminate) ");

		gets(&buffer[0]);

		printf("\n\n");
		
		if(buffer[0] == 0)
		{
			b_terminate_app = TRUE;
			
			break;
		}
		
		if( (sscanf(&buffer[0], "%lu", &ul_number_of_loops) == 1 ) )
		{
			break;
		}
	}
	
	if(b_terminate_app)
	{
		exit(0);
	}

	int i_signal_type;
	
	while(TRUE)
	{
		printf(	"Signal type:\n"
				"A) Rectangle\n"
				"B) Triangle\n"
				"C) Sinus\n"
				"D) Positive ramp\n"
				"E) Negative ramp\n"
				"RETURN to terminate\n\n"
				"Your choice: "						);

		gets(&buffer[0]);

		printf("\n\n");
		
		if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
		{
			i_signal_type = SIGNAL_RECTANGLE;

			break;
		}
		else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
		{
			i_signal_type = SIGNAL_TRIANGLE;

			break;
		}
		else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
		{
			i_signal_type = SIGNAL_SINUS;

			break;
		}
		else if( (strcmp(&buffer[0], "d") == 0)||(strcmp(&buffer[0], "D") == 0) )
		{
			i_signal_type = SIGNAL_POS_RAMP;

			break;
		}
		else if( (strcmp(&buffer[0], "e") == 0)||(strcmp(&buffer[0], "E") == 0) )
		{
			i_signal_type = SIGNAL_NEG_RAMP;

			break;
		}
		else if(buffer[0] == 0)
		{
			b_terminate_app = TRUE;
			
			break;
		}
	}

	if(b_terminate_app)
	{
		exit(0);
	}
		
	double d_initial_signal_freq;

	while(TRUE)
	{
		printf("Initial signal frequency in Hz: (RETURN to terminate) ");

		gets(&buffer[0]);

		printf("\n\n");
		
		if(buffer[0] == 0)
		{
			b_terminate_app = TRUE;
			
			break;
		}
		
		if( (sscanf(&buffer[0], "%lf", &d_initial_signal_freq) == 1 ) )
		{
			break;
		}
	}
	
	if(b_terminate_app)
	{
		exit(0);
	}
		
	double d_final_signal_freq;

	while(TRUE)
	{
		printf("Final signal frequency in Hz: (RETURN to terminate) ");

		gets(&buffer[0]);

		printf("\n\n");
		
		if(buffer[0] == 0)
		{
			b_terminate_app = TRUE;
			
			break;
		}
		
		if( (sscanf(&buffer[0], "%lf", &d_final_signal_freq) == 1 ) )
		{
			break;
		}
	}
	
	if(b_terminate_app)
	{
		exit(0);
	}
		
	double d_initial_amplitude;

	while(TRUE)
	{
		printf("Initial signal amplitude in V (0 - 10.0): (RETURN to terminate) ");

		gets(&buffer[0]);

		printf("\n\n");
		
		if(buffer[0] == 0)
		{
			b_terminate_app = TRUE;
			
			break;
		}
		
		if( (sscanf(&buffer[0], "%lf", &d_initial_amplitude) == 1 ) )
		{
			break;
		}
	}
	
	if(b_terminate_app)
	{
		exit(0);
	}
		
	double d_final_amplitude;

	while(TRUE)
	{
		printf("Final signal amplitude in V (0 - 10.0): (RETURN to terminate) ");

		gets(&buffer[0]);

		printf("\n\n");
		
		if(buffer[0] == 0)
		{
			b_terminate_app = TRUE;
			
			break;
		}
		
		if( (sscanf(&buffer[0], "%lf", &d_final_amplitude) == 1 ) )
		{
			break;
		}
	}
	
	if(b_terminate_app)
	{
		exit(0);
	}
		
	short* p_s_buffer = new short[ul_buffer_size];
	
	Sweep(i_signal_type, d_initial_signal_freq, d_final_signal_freq, 
									d_initial_amplitude, d_final_amplitude,
												d_output_freq, ul_buffer_size, p_s_buffer, 1);	
	
	unsigned long ul_ticks_low;
	
	unsigned long ul_ticks_high;

	double d_achieved_freq;
	
	me4000FrequencyToTicks(d_output_freq, &ul_ticks_low, &ul_ticks_high, &d_achieved_freq);

	me4000AOConfig(ui_board_number, ui_channel_number, ul_ticks_low, ME4000_AO_TRIGGER_SOFTWARE, 0);

	me4000AOWraparound(ui_board_number, ui_channel_number, p_s_buffer, ul_buffer_size, ul_number_of_loops,  ME4000_AO_WRAPAROUND_ASYNCHRONOUS, AOTerminate, NULL, 0);

	printf("Press any key to begin\n\n");
	
	getch();
	
	b_wraparound_terminated = FALSE;
	
	me4000AOStart(ui_board_number, ui_channel_number);
											
	printf(	"I - Terminate immediately\n"
			"L - Terminate last value\n\n");

	if(ul_number_of_loops > 0)
	{
		printf("Or wait until all %lu loops have been executed\n\n", ul_number_of_loops);
	}
	
	while(TRUE)
	{
		int i_status;
		
		me4000AOGetStatus(ui_board_number, ui_channel_number, ME4000_AO_WAIT_NONE, &i_status);
		
		if(i_status == ME4000_AO_STATUS_IDLE)
		{
			break;
		}

		if( kbhit() )
		{
			char ch = getch();

			if( (ch == 'i')||(ch == 'I') )
			{
				me4000AOStop(ui_board_number, ui_channel_number, ME4000_AO_STOP_MODE_IMMEDIATE);
			}
			else if( (ch == 'l')||(ch == 'L') )
			{
				me4000AOStop(ui_board_number, ui_channel_number, ME4000_AO_STOP_MODE_LAST_VALUE);
			}
		}

		Sleep(100);
	}
	
	printf("Press any key to exit\n\n");
	
	getch();
	
	delete p_s_buffer;
	
	return 0;
}

void _stdcall AOTerminate (void* pTerminateContext)
{
	printf("***********************\n\n");
	printf("AOWrapAround terminated\n\n");
	printf("***********************\n\n");

	b_wraparound_terminated = TRUE;
}
