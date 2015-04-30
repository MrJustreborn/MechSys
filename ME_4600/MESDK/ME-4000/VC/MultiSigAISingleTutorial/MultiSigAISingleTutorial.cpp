// MultiSigAISingle.cpp : Defines the entry point for the console application.
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

	printf(	"This program tests and demonstrates the ME4000 API Funktion\n"
			"ME4000MultiSigAISingle\n\n"
			"You must have the necessary additional hardware in order to call this\n"
			"function. Please see the manual for details\n\n"
			"The various parameters can be entered here. The function AIMultiSigSingle\n" 
			"will then be called repeatedly.\n\n"
			"If a software trigger is used then there will be a 0.25 second interval\n"
			"between calls.\n\n"
			"If an external trigger is used then AIMultiSigAISingle will be called each\n"
			"time a trigger is recognised\n\n"
			"The digital and physical values measured will be displayed.\n\n"
			"Terminate each acquisition by pressing any key.\n\n" 
		
			"Press any key now to continue\n\n"														);

	_getch();
	
	char buffer[128];
		
	while(TRUE)
	{
		BOOL b_terminate = FALSE;

		printf(	"First of all, me4000MultiSigAIOpen must be called to reserve the\n"
				"hardware resources for a MultiSigAI operation\n\n");

		while(TRUE)
		{
			printf("Parameters for me4000MultiSigAIOpen:\n\n");

			unsigned int ui_board_number;

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

			printf(	"Press any key to call the function:\n\n"
					"me4000MultiSigAIOpen(%u);\n\n",
					ui_board_number									);

			getch();

			int i_error = me4000MultiSigAIOpen(ui_board_number);
	
		}

		if(b_terminate)
		{
			break;
		}

		printf(	"Now MultiSigAISingle can be called\n\n");

		printf("Parameters for me4000MultiSigAISingle:\n\n");

		unsigned int ui_board_number = 0;

		unsigned int ui_ai_channel_number = 0;

		unsigned int ui_mux_channel_number = 0;

		int i_gain;
		char sz_gain[64];

		int i_trigger_mode;
		char sz_trigger_mode[64];

		int i_ext_trigger_edge; 
		char sz_ext_trigger_edge[64];
		
		unsigned long ul_time_out_seconds;

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
			printf("uiAIChannelNumber - AI Channel Number (0 - 31): (RETURN to terminate) ");

			gets(&buffer[0]);

			printf("\n\n");
			
			if(buffer[0] == 0)
			{
				b_terminate = TRUE;
				
				break;
			}
			
			if( (sscanf(&buffer[0], "%u", &ui_ai_channel_number) == 1 ) )
			{
				break;
			}
		}
		
		while(TRUE)
		{
			printf("uiMuxChannelNumber - MUX Channel Number (0 - 255): (RETURN to terminate) ");

			gets(&buffer[0]);

			printf("\n\n");
			
			if(buffer[0] == 0)
			{
				b_terminate = TRUE;
				
				break;
			}
			
			if( (sscanf(&buffer[0], "%u", &ui_mux_channel_number) == 1 ) )
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
			printf(	"iGain - Input gain:\n"
					"A) ME4000_MULTISIG_GAIN_1\n"
					"B) ME4000_MULTISIG_GAIN_10\n"
					"C) ME4000_MULTISIG_GAIN_100\n"
					"RETURN to terminate\n\n"
					"Your choice: "						);

			gets(&buffer[0]);

			printf("\n\n");
			
			if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
			{
				i_gain = ME4000_MULTISIG_GAIN_1;
				strcpy(sz_gain, "ME4000_MULTISIG_GAIN_1");

				break;
			}
			else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
			{
				i_gain = ME4000_MULTISIG_GAIN_10;
				strcpy(sz_gain, "ME4000_MULTISIG_GAIN_10");

				break;
			}
			else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
			{
				i_gain = ME4000_MULTISIG_GAIN_100;
				strcpy(sz_gain, "ME4000_MULTISIG_GAIN_100");

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
				"me4000MultiSigAISingle(    %u,\n"
				"                           %u,\n"
				"                           %u,\n"
				"                           %s,\n" 
				"                           %s,\n" 
				"                           %s,\n" 
				"                           %lu,\n" 
				"                           &s_digital_value                       );\n\n"
				"repeatedly\n\n"
				"Press any key once to begin, press again to terminate\n\n",
				ui_board_number,
				ui_ai_channel_number,
				ui_mux_channel_number,
				sz_gain,
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
			
			int i_error = me4000MultiSigAISingle(ui_board_number, 
													ui_ai_channel_number, ui_mux_channel_number, 
															i_gain, i_trigger_mode, i_ext_trigger_edge, 
																	ul_time_out_seconds, &s_digital_value);

			if(i_error != 0)
			{
				printf(	"me4000MultiSigAISingle returned an error\n\n"
						"Press ESC to terminate, any other key to continue\n\n");

				char ch = getch();

				if(ch == 27)
				{
					break;
				}
			}
			else
			{
//					double d_volt;
				
//					i_error = me4000AIDigitToVolt(s_digital_value, i_range, &d_volt);

//					printf("Digital value: %6d    Physical Value: %7.3f V\n", s_digital_value, d_volt);  

				printf("Digital value: %6d\n", s_digital_value);  
			}

			if(i_trigger_mode == ME4000_AI_TRIGGER_SOFTWARE)
			{
				Sleep(500);
			}
		}
		
		printf("\n\n");
		
		printf(	"Lastly, me4000MultiSigAIClose should be called to free the\n"
				"hardware resources reserved above with me4000MultiSigAIOpen\n\n");

		while(TRUE)
		{
			printf("Parameters for me4000MultiSigAIClose:\n\n");

			unsigned int ui_board_number;

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

			printf(	"Press any key to call the function:\n\n"
					"me4000MultiSigAIClose(%u);\n\n",
					ui_board_number									);

			getch();

			int i_error = me4000MultiSigAIClose(ui_board_number);
	
			if(i_error == ME4000_NO_ERROR)
			{
				printf("me4000MultiSigAIClose called successfully\n\n");

				break;
			}
			else
			{
				char error_msg[256];

				me4000ErrorGetMessage(i_error, &error_msg[0], 256);

				printf("\n\n************   Error **************\n\n");

				printf("me4000MultiSigAIClose returned an error - Error code: 0x%08X\n", i_error);

				printf("    %s\n\n", &error_msg[0]);

				printf("************   Error **************\n\n");
			}
		}

		if(b_terminate)
		{
			break;
		}
	}
	
	printf("\nPress any key to terminate\n");

	_getch();

	return 0;
}

void _stdcall ErrorFunction(char* function_name, int error_code)
{
	char error_msg[256];

	me4000ErrorGetMessage(error_code, &error_msg[0], 256);

	printf("\n\n************   Error **************\n\n");

	printf("Error calling function: %s - Error code: 0x%08X\n", function_name, error_code);

	printf("    %s\n\n", &error_msg[0]);

	printf("Programm will be terminated - Press any key to continue\n\n");

	getch();

	exit(0);

	printf("************   Error **************\n\n");
}

