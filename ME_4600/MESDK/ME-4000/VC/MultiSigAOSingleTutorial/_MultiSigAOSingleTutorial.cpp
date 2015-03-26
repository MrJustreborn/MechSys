// _AOSingle.cpp : Defines the entry point for the console application.
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

	printf(	"This program tests and demonstrates the ME4000 API Funktion me4000MultiSigAOSingle\n\n"
			"You must have the necessary additional hardware in order to call this\n"
			"function. Please see the manual for details\n\n"
		
			"Press any key now to continue\n\n"														);

	_getch();
	
	char buffer[128];
	
	while(TRUE)
	{
		BOOL b_terminate = FALSE;

		printf(	"First of all, me4000MultiSigAOOpen must be called to reserve the\n"
				"hardware resources for a MultiSigAO operation\n\n");

		while(TRUE)
		{
			printf("Parameters for me4000MultiSigAOOpen:\n\n");

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
					"me4000MultiSigAOOpen(%u);\n\n",
					ui_board_number									);

			getch();

			int i_error = me4000MultiSigAOOpen(ui_board_number);

			if(i_error == ME4000_NO_ERROR)
			{
				break;
			}
		}

		if(b_terminate)
		{
			break;
		}


		printf(	"Now MultiSigAOSingle can be called\n\n");

		while(TRUE)
		{
			printf("Parameters for me4000MultiSigAOSingle:\n\n");

			unsigned int ui_board_number;

			unsigned int ui_demux_channel_number;

			int i_trigger_mode;
			char sz_trigger_mode[64];

			int i_ext_trigger_edge;
			char sz_ext_trigger_edge[64];

			unsigned long ul_time_out_seconds;
			char sz_time_out_seconds[64];

			short s_value;

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
				printf("uiDemuxChannelNumber - Channel Number (0 - 255): (RETURN to terminate) ");

				gets(&buffer[0]);

				printf("\n\n");
				
				if(buffer[0] == 0)
				{
					b_terminate = TRUE;
					
					break;
				}
				
				if( (sscanf(&buffer[0], "%u", &ui_demux_channel_number) == 1 ) )
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
				printf(	"iTriggerMode - Software or External digital trigger:\n"
						"A) ME4000_AO_TRIGGER_SOFTWARE\n"
						"B) ME4000_AO_TRIGGER_EXT_DIGITAL\n"
						"RETURN to terminate\n\n"
						"Your choice: "						);

				gets(&buffer[0]);

				printf("\n\n");
				
				if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
				{
					i_trigger_mode = ME4000_AO_TRIGGER_SOFTWARE;
					strcpy(sz_trigger_mode, "ME4000_AO_TRIGGER_SOFTWARE");

					break;
				}
				else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
				{
					i_trigger_mode = ME4000_AO_TRIGGER_EXT_DIGITAL;
					strcpy(sz_trigger_mode, "ME4000_AO_TRIGGER_EXT_DIGITAL");

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

			if(i_trigger_mode == ME4000_AO_TRIGGER_SOFTWARE)
			{
				printf("You have chosen a software trigger and so the following two parameters,\n");
				printf("iExtTriggerEdge and ulTimeOutSeconds must both be set to\n");
				printf("ME4000_VALUE_NOT_USED (0)\n\n");

				i_ext_trigger_edge = ME4000_VALUE_NOT_USED;
				strcpy(&sz_ext_trigger_edge[0], "ME4000_VALUE_NOT_USED");


				ul_time_out_seconds = ME4000_VALUE_NOT_USED;
				strcpy(&sz_time_out_seconds[0], "ME4000_VALUE_NOT_USED");
			}
			else
			{
				while(TRUE)
				{
					printf(	"iExtTriggerEdge - Trigger on rising, falling or both flanks:\n"
							"A) ME4000_AO_TRIGGER_EXT_EDGE_RISING\n"
							"B) ME4000_AO_TRIGGER_EXT_EDGE_FALLING\n"
							"B) ME4000_AO_TRIGGER_EXT_EDGE_BOTH\n"
							"RETURN to terminate\n\n"
							"Your choice: "						);

					gets(&buffer[0]);

					printf("\n\n");
					
					if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
					{
						i_ext_trigger_edge = ME4000_AO_TRIGGER_EXT_EDGE_RISING;
						strcpy(sz_ext_trigger_edge, "ME4000_AO_TRIGGER_EXT_EDGE_RISING");

						break;
					}
					else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
					{
						i_ext_trigger_edge = ME4000_AO_TRIGGER_EXT_EDGE_FALLING;
						strcpy(sz_ext_trigger_edge, "ME4000_AO_TRIGGER_EXT_EDGE_FALLING");

						break;
					}
					else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
					{
						i_ext_trigger_edge = ME4000_AO_TRIGGER_EXT_EDGE_BOTH;
						strcpy(sz_ext_trigger_edge, "ME4000_AO_TRIGGER_EXT_EDGE_BOTH");

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
					printf("ulTimeOutSeconds - Time out in seconds: (RETURN to terminate) ");

					gets(&buffer[0]);

					printf("\n\n");
					
					if(buffer[0] == 0)
					{
						b_terminate = TRUE;
						
						break;
					}
					
					if( (sscanf(&buffer[0], "%lu", &ul_time_out_seconds) == 1 ) )
					{
						sprintf(&sz_time_out_seconds[0], "%lu", ul_time_out_seconds); 
						
						break;
					}
				}
				
				if(b_terminate)
				{
					break;
				}
			}
			
			while(TRUE)
			{
				printf("sValue - Output Value (-32768 - 32767): (RETURN to terminate) ");

				gets(&buffer[0]);

				printf("\n\n");
				
				if(buffer[0] == 0)
				{
					b_terminate = TRUE;
					
					break;
				}
				
				if( (sscanf(&buffer[0], "%hd", &s_value) == 1 ) )
				{
					break;
				}
			}
			
			if(b_terminate)
			{
				break;
			}

			printf(	"Press any key to call the function:\n\n"
					"me4000MultiSigAOSingle(    %u,\n"
					"                           %u,\n"
					"                           %s,\n" 
					"                           %s,\n" 
					"                           %s,\n" 
					"                           %hd                                   );\n\n",
					ui_board_number,
					ui_demux_channel_number,
					sz_trigger_mode,
					sz_ext_trigger_edge,
					sz_time_out_seconds,
					s_value											);

			getch();

			int i_error = me4000MultiSigAOSingle(ui_board_number, ui_demux_channel_number, i_trigger_mode, i_ext_trigger_edge, ul_time_out_seconds, s_value);
		}
	
		if(b_terminate)
		{
			break;
		}

		printf(	"Lastly, me4000MultiSigAOClose should be called to free the\n"
				"hardware resources reserved above with me4000MultiSigAOOpen\n\n");

		while(TRUE)
		{
			printf("Parameters for me4000MultiSigAOClose:\n\n");

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
					"me4000MultiSigAOClose(%u);\n\n",
					ui_board_number									);

			getch();

			int i_error = me4000MultiSigAOClose(ui_board_number);
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

