// AISingle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include "..\me4000dll.h"

int main(int argc, char* argv[])
{
	me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

	unsigned long ul_version;
	
	me4000GetDLLVersion(&ul_version);

	printf("ME4000 - DLL Version: %08X\n", ul_version);

	me4000GetDriverVersion(&ul_version);

	printf("ME4000 - Driver Version: %08X\n\n", ul_version);

	printf(	"This program tests and demonstrates the ME4000 API Funktion ME4000AISingle\n\n"
			"The various parameters can be entered here. The function AISingle will then\n" 
			"be called repeatedly.\n\n"
			"If a software trigger is used then there will be a 0.5 second interval\n"
			"between calls.\n\n"
			"If an external trigger is used then AIStart will be called each time a\n"
			"trigger is recognised\n\n"
			"The digital and physical values measured will be displayed.\n\n"
			"Terminate each acquisition by pressing any key.\n\n" 
		
			"Press any key now to continue\n\n"														);

	_getch();
	
	while(TRUE)
	{
		BOOL b_terminate = FALSE;
		
		unsigned int ui_board_number = 0;

		unsigned int ui_channel_number = 0;

		int i_range;
		char sz_range[64];

		int i_sd_mode;
		char sz_sd_mode[64];

		int i_trigger_mode;
		char sz_trigger_mode[64];

		int i_ext_trigger_edge; 
		char sz_ext_trigger_edge[64];
		
		unsigned long ul_time_out_seconds;

		char buffer[128];
		
		while(TRUE)
		{
			printf("uiBoardNumber - Board Number (0 - 31): (RETURN to terminate) ");

			gets(&buffer[0]);

			printf("\n\n");
			
			if(buffer[0] == 0)
			{
				b_terminate = TRUE;
				
				break;
			}
			
			if( (sscanf(&buffer[0], "%u", &ui_board_number) == 1 ) )
			{
				break;
			}
		}
		
		if(b_terminate)
		{
			break;
		}
		
		while(TRUE)
		{
			printf("uiChannelNumber - Channel Number (0 - 31): (RETURN to terminate) ");

			gets(&buffer[0]);

			printf("\n\n");
			
			if(buffer[0] == 0)
			{
				b_terminate = TRUE;
				
				break;
			}
			
			if( (sscanf(&buffer[0], "%u", &ui_channel_number) == 1 ) )
			{
				break;
			}
		}
		
		if(b_terminate)
		{
			break;
		}
		
		while(TRUE)
		{
			printf(	"iRange - Input Range:\n"
					"A) ME4000_AI_RANGE_BIPOLAR_10\n"
					"B) ME4000_AI_RANGE_BIPOLAR_2_5\n"
					"C) ME4000_AI_RANGE_UNIPOLAR_10\n"
					"D) ME4000_AI_RANGE_UNIPOLAR_2_5\n"
					"RETURN to terminate\n\n"
					"Your choice: "						);

			gets(&buffer[0]);

			printf("\n\n");
			
			if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
			{
				i_range = ME4000_AI_RANGE_BIPOLAR_10;
				strcpy(sz_range, "ME4000_AI_RANGE_BIPOLAR_10");

				break;
			}
			else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
			{
				i_range = ME4000_AI_RANGE_BIPOLAR_2_5;
				strcpy(sz_range, "ME4000_AI_RANGE_BIPOLAR_10");

				break;
			}
			else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
			{
				i_range = ME4000_AI_RANGE_UNIPOLAR_10;
				strcpy(sz_range, "ME4000_AI_RANGE_UNIPOLAR_10");

				break;
			}
			else if( (strcmp(&buffer[0], "d") == 0)||(strcmp(&buffer[0], "D") == 0) )
			{
				i_range = ME4000_AI_RANGE_UNIPOLAR_2_5;
				strcpy(sz_range, "ME4000_AI_RANGE_UNIPOLAR_2_5");

				break;
			}
			else if(buffer[0] == 0)
			{
				b_terminate = TRUE;
				
				break;
			}
		}
		
		if(b_terminate)
		{
			break;
		}
		
		while(TRUE)
		{
			printf(	"iSDMode - Input Mode:\n"
					"A) ME4000_AI_INPUT_SINGLE_ENDED\n"
					"B) ME4000_AI_INPUT_DIFFERENTIAL\n"
					"RETURN to terminate\n\n"
					"Your choice: "						);

			gets(&buffer[0]);

			printf("\n\n");
			
			if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
			{
				i_sd_mode = ME4000_AI_INPUT_SINGLE_ENDED;
				strcpy(sz_sd_mode, "ME4000_AI_INPUT_SINGLE_ENDED");

				break;
			}
			else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
			{
				i_sd_mode = ME4000_AI_INPUT_DIFFERENTIAL;
				strcpy(sz_sd_mode, "ME4000_AI_INPUT_DIFFERENTIAL");

				break;
			}
			else if(buffer[0] == 0)
			{
				b_terminate = TRUE;
				
				break;
			}
		}
		
		if(b_terminate)
		{
			break;
		}
		
		while(TRUE)
		{
			printf(	"iTriggerMode - Trigger Mode:\n"
					"A) ME4000_AI_TRIGGER_SOFTWARE\n"
					"B) ME4000_AI_TRIGGER_EXT_DIGITAL\n"
					"C) ME4000_AI_TRIGGER_EXT_ANALOG\n"
					"RETURN to terminate\n\n"
					"Your choice: "						);

			gets(&buffer[0]);

			printf("\n\n");
			
			if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
			{
				i_trigger_mode = ME4000_AI_TRIGGER_SOFTWARE;
				strcpy(sz_trigger_mode, "ME4000_AI_TRIGGER_SOFTWARE");

				break;
			}
			else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
			{
				i_trigger_mode = ME4000_AI_TRIGGER_EXT_DIGITAL;
				strcpy(sz_trigger_mode, "ME4000_AI_TRIGGER_EXT_DIGITAL");

				break;
			}
			else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
			{
				i_trigger_mode = ME4000_AI_TRIGGER_EXT_ANALOG;
				strcpy(sz_trigger_mode, "ME4000_AI_TRIGGER_EXT_ANALOG");

				break;
			}
			else if(buffer[0] == 0)
			{
				b_terminate = TRUE;
				
				break;
			}
		}
		
		if(b_terminate)
		{
			break;
		}
		
		if(i_trigger_mode == ME4000_AI_TRIGGER_SOFTWARE)
		{
			printf("As iTriggerMode == ME4000_AI_TRIGGER_SOFTWARE we set iExtTriggerEdge = 0\n\n");
			
			i_ext_trigger_edge = 0;
			strcpy(sz_ext_trigger_edge, "0");
		}
		else
		{
			while(TRUE)
			{
				printf(	"iExtTriggerEdge - External Trigger Edge:\n"
						"A) ME4000_AI_TRIGGER_EXT_EDGE_RISING\n"
						"B) ME4000_AI_TRIGGER_EXT_EDGE_FALLING\n"
						"C) ME4000_AI_TRIGGER_EXT_EDGE_BOTH\n"
						"RETURN to terminate\n\n"
						"Your choice: "						);

				gets(&buffer[0]);

				printf("\n\n");
				
				if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
				{
					i_ext_trigger_edge = ME4000_AI_TRIGGER_EXT_EDGE_RISING;
					strcpy(sz_ext_trigger_edge, "ME4000_AI_TRIGGER_EXT_EDGE_RISING");

					break;
				}
				else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
				{
					i_ext_trigger_edge = ME4000_AI_TRIGGER_EXT_EDGE_FALLING;
					strcpy(sz_ext_trigger_edge, "ME4000_AI_TRIGGER_EXT_EDGE_FALLING");

					break;
				}
				else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
				{
					i_ext_trigger_edge = ME4000_AI_TRIGGER_EXT_EDGE_BOTH;
					strcpy(sz_ext_trigger_edge, "ME4000_AI_TRIGGER_EXT_EDGE_BOTH");

					break;
				}
				else if(buffer[0] == 0)
				{
					b_terminate = TRUE;
					
					break;
				}
			}
		}
		
		if(b_terminate)
		{
			break;
		}
		
		if(i_trigger_mode == ME4000_AI_TRIGGER_SOFTWARE)
		{
			printf("As iTriggerMode == ME4000_AI_TRIGGER_SOFTWARE we set ul_time_out_seconds = 0\n\n");
			
			ul_time_out_seconds = 0;
		}
		else
		{
			while(TRUE)
			{
				printf("ulTimeOutSeconds - Time out in seconds (0 - 31): (RETURN to terminate) ");

				gets(&buffer[0]);

				printf("\n\n");
				
				if(buffer[0] == 0)
				{
					b_terminate = TRUE;
					
					break;
				}
				
				if( (sscanf(&buffer[0], "%lu", &ul_time_out_seconds) == 1 ) )
				{
					break;
				}
			}
		}
		
		if(b_terminate)
		{
			break;
		}
		
		printf("The result will be stored in the 'short' variable 's_digital_value'\n\n");
		
		printf(	"Calling the function:\n\n"
				"me4000AISingle(    %u,\n"
				"                   %u,\n"
                "                   %s,\n" 
                "                   %s,\n" 
                "                   %s,\n" 
                "                   %s,\n" 
                "                   %lu,\n" 
                "                   &s_digital_value                       );\n\n"
				"repeatedly\n\n"
				"Press any key once to begin, press again to terminate\n\n",
				ui_board_number,
				ui_channel_number,
				sz_range,
				sz_sd_mode,
				sz_trigger_mode,
				sz_ext_trigger_edge,
				ul_time_out_seconds													);

		getch();

		while(TRUE)
		{
			if( kbhit() )
			{
				getch();

				break;
			}
			
			short s_digital_value;

			if(i_trigger_mode != ME4000_AI_TRIGGER_SOFTWARE)
			{
				printf("\nWaiting for external trigger.......\n");
			}
			
			int i_error = me4000AISingle(ui_board_number, 
													ui_channel_number, i_range, i_sd_mode, 
															i_trigger_mode, i_ext_trigger_edge, 
																ul_time_out_seconds, &s_digital_value);

			if(i_error != 0)
			{
				printf(	"me4000AISingle returned an error\n\n"
						"Press ESC to terminate, any other key to continue\n\n");

				char ch = getch();

				if(ch == 27)
				{
					break;
				}
			}
			else
			{
				double d_volt;
				
				i_error = me4000AIDigitToVolt(s_digital_value, i_range, &d_volt);

				printf("Digital value: %6d    Physical Value: %7.3f V\n", s_digital_value, d_volt);  
			}

			if(i_trigger_mode == ME4000_AI_TRIGGER_SOFTWARE)
			{
				Sleep(500);
			}
		}
	
		printf("\n\n");
	}
	
	printf("\nPress any key to terminate\n");

	_getch();

	return 0;
}


