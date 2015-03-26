// _AITest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include "..\me4000dll.h"

unsigned char chanList[128];

int iRange[128];

unsigned int ui_number_of_entries;

short* p_s_buffer = NULL;

#define SIZE_OF_SCAN_BUFFER		10000

short sScanBuffer[SIZE_OF_SCAN_BUFFER];

void _stdcall TestCallback(short* psValues, unsigned int uiNumberOfValues, 
	                                         void* pCallbackContext, int iLastError);

void _stdcall TestTerminate(short* psValues, unsigned int uiNumberOfValues, 
	                                         void* pCallbackContext, int iLastError);

int main(int argc, char* argv[])
{
	unsigned long ul_version;
	
	me4000GetDLLVersion(&ul_version);

	printf("ME4000 - DLL Version: %08X\n", ul_version);

	me4000GetDriverVersion(&ul_version);

	printf("ME4000 - Driver Version: %08X\n\n", ul_version);

	printf(	"This program tests and demonstrates the ME4000 Analog Input API\n\n"
			"The function me4000AIConfig will be called first, followed by the\n"
			"function me4000AIScan or me4000AIContinuous. You can start the\n"
			"acquisition by calling AIStart and, for a non-blocking acquisition\n"
			"terminate it at any time by calling me4000AIStop or me4000AIReset\n\n"
			"If you require a Callback function, then the function TestCallback\n"
			"is available which prints the number of data values passed to it and\n"
			"the first value of each channel in the channel list\n\n"
			"If you require a Terminate function, then the function TestTerminate\n"
			"is available which prints the number of data values passed to it and\n"
			"the first value of each channel in the channel list\n\n"
			"During a non-blocking acquisition, you can call the routine\n"
			"me4000GetNewValues at any time and print the number of values passed to\n"
			"it and the first value of each channel in the channel list\n\n"
		
			"Press any key now to continue\n\n"														);

	_getch();
	
	BOOL b_terminate = FALSE;
	
	char buffer[128];
			
	while(TRUE)
	{
		// me4000AIConfig

		int i_acq_mode;

		unsigned long ul_timeout_seconds;

		while(TRUE)
		{
			printf("Parameters for me4000AIConfig:\n\n");

			unsigned int ui_board_number;

			int i_sd_mode;
			char sz_sd_mode[64];
			
			int i_simultaneous;
			char sz_simultaneous[64];

			unsigned long ul_chan_ticks;

			unsigned long ul_scan_ticks_low;
			unsigned long ul_scan_ticks_high;

			char sz_acq_mode[64];
			
			int i_ext_trigger_mode;
			char sz_ext_trigger_mode[64];

			int i_ext_trigger_edge; 
			char sz_ext_trigger_edge[64];
		
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

			printf("Now we build the channel list ucChanList[]\n\n");

			ui_number_of_entries = 0;

			BOOL b_end_channel_list = FALSE;

			while(TRUE)
			{
				unsigned int ui_channel_number = 0;

				int i_range = ME4000_AI_RANGE_BIPOLAR_10;
				
				while(TRUE)
				{
					printf("Channel list entry %u - Channel Number (0 - 31): (RETURN - No more entries) ", ui_number_of_entries + 1);

					gets(&buffer[0]);

					printf("\n\n");
					
					if(buffer[0] == 0)
					{
						b_end_channel_list = TRUE;
						
						break;
					}
					
					if( (sscanf(&buffer[0], "%u", &ui_channel_number) == 1 ) )
					{
						break;
					}
				}

				if(b_end_channel_list)
				{
					break;
				}

				while(TRUE)
				{
					printf(	"Channel list entry %d - Input Range:\n"
							"A) ME4000_AI_RANGE_BIPOLAR_10\n"
							"B) ME4000_AI_RANGE_BIPOLAR_2_5\n"
							"C) ME4000_AI_RANGE_UNIPOLAR_10\n"
							"D) ME4000_AI_RANGE_UNIPOLAR_2_5\n"
							"RETURN - No more entries\n\n"
							"Your choice: ",
							ui_number_of_entries + 1					);

					gets(&buffer[0]);

					printf("\n\n");
					
					if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
					{
						i_range = ME4000_AI_RANGE_BIPOLAR_10;

						break;
					}
					else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
					{
						i_range = ME4000_AI_RANGE_BIPOLAR_2_5;

						break;
					}
					else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
					{
						i_range = ME4000_AI_RANGE_UNIPOLAR_10;

						break;
					}
					else if( (strcmp(&buffer[0], "d") == 0)||(strcmp(&buffer[0], "D") == 0) )
					{
						i_range = ME4000_AI_RANGE_UNIPOLAR_2_5;

						break;
					}
					else if(buffer[0] == 0)
					{
						b_end_channel_list = TRUE;
						
						break;
					}
				}
			
				if(b_end_channel_list)
				{
					break;
				}

				me4000AIMakeChannelListEntry( ui_channel_number, i_range, &chanList[ui_number_of_entries] );

				iRange[ui_number_of_entries] = i_range;
				
				++ui_number_of_entries;
			}

			printf("Channel list ucChanList[] contains %u entries:\n\n", ui_number_of_entries);

			for(unsigned int index_channel = 0; index_channel < ui_number_of_entries; index_channel++)
			{
				char* sz_range;

				switch(iRange[index_channel])
				{
				case ME4000_AI_RANGE_BIPOLAR_10:

					sz_range = "ME4000_AI_RANGE_BIPOLAR_10";

					break;

				case ME4000_AI_RANGE_BIPOLAR_2_5:

					sz_range = "ME4000_AI_RANGE_BIPOLAR_2_5";

					break;

				case ME4000_AI_RANGE_UNIPOLAR_10:

					sz_range = "ME4000_AI_RANGE_UNIPOLAR_10";

					break;

				case ME4000_AI_RANGE_UNIPOLAR_2_5:

					sz_range = "ME4000_AI_RANGE_UNIPOLAR_2_5";

					break;
				}
				
				printf("    %3d:    Channel number: %2u    Input range: %s\n", 
								index_channel + 1, chanList[index_channel] & 0x1F, sz_range);
			}

			printf("\n\n");

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
				printf(	"iSimultaneous - Simultaneous Mode:\n"
						"A) ME4000_AI_SIMULTANEOUS_DISABLE\n"
						"B) ME4000_AI_SIMULTANEOUS_ENABLE\n"
						"RETURN to terminate\n\n"
						"Your choice: "						);

				gets(&buffer[0]);

				printf("\n\n");
				
				if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
				{
					i_simultaneous = ME4000_AI_SIMULTANEOUS_DISABLE;
					strcpy(sz_simultaneous, "ME4000_AI_SIMULTANEOUS_DISABLE");

					break;
				}
				else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
				{
					i_simultaneous = ME4000_AI_SIMULTANEOUS_ENABLE;
					strcpy(sz_simultaneous, "ME4000_AI_SIMULTANEOUS_ENABLE");

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
				printf("ulChanTicks - Chan ticks: (RETURN to terminate) ");

				gets(&buffer[0]);

				printf("\n\n");
				
				if(buffer[0] == 0)
				{
					b_terminate = TRUE;
					
					break;
				}
				
				if( (sscanf(&buffer[0], "%lu", &ul_chan_ticks) == 1 ) )
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
				printf("ulScanTicksLow - Scan ticks low part: (RETURN to terminate) ");

				gets(&buffer[0]);

				printf("\n\n");
				
				if(buffer[0] == 0)
				{
					b_terminate = TRUE;
					
					break;
				}
				
				if( (sscanf(&buffer[0], "%lu", &ul_scan_ticks_low) == 1 ) )
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
				printf("ulScanTicksHigh - Scan ticks high part: (RETURN to terminate) ");

				gets(&buffer[0]);

				printf("\n\n");
				
				if(buffer[0] == 0)
				{
					b_terminate = TRUE;
					
					break;
				}
				
				if( (sscanf(&buffer[0], "%lu", &ul_scan_ticks_high) == 1 ) )
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
				printf(	"iAcqMode - Acquisition Mode:\n"
						"A) ME4000_AI_ACQ_MODE_SOFTWARE\n"
						"B) ME4000_AI_ACQ_MODE_EXT\n"
						"C) ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE\n"
						"D) ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST\n"
						"RETURN to terminate\n\n"
						"Your choice: "						);

				gets(&buffer[0]);

				printf("\n\n");
				
				if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
				{
					i_acq_mode = ME4000_AI_ACQ_MODE_SOFTWARE;
					strcpy(sz_acq_mode, "ME4000_AI_ACQ_MODE_SOFTWARE");

					break;
				}
				else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
				{
					i_acq_mode = ME4000_AI_ACQ_MODE_EXT;
					strcpy(sz_acq_mode, "ME4000_AI_ACQ_MODE_EXT");

					break;
				}
				else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
				{
					i_acq_mode = ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE;
					strcpy(sz_acq_mode, "ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE");

					break;
				}
				else if( (strcmp(&buffer[0], "d") == 0)||(strcmp(&buffer[0], "D") == 0) )
				{
					i_acq_mode = ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST;
					strcpy(sz_acq_mode, "ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST");

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
		
			if(i_acq_mode == ME4000_AI_ACQ_MODE_SOFTWARE)
			{
				printf("As iAcqMode == ME4000_AI_ACQ_MODE_SOFTWARE we set iExtTriggerMode = 0\n\n");
				
				i_ext_trigger_mode = 0;
				strcpy(sz_ext_trigger_mode, "0");
			}
			else
			{
				while(TRUE)
				{
					printf(	"iExtTriggerMode - External Trigger Mode:\n"
							"A) ME4000_AI_TRIGGER_EXT_DIGITAL\n"
							"B) ME4000_AI_TRIGGER_EXT_ANALOG\n"
							"RETURN to terminate\n\n"
							"Your choice: "						);

					gets(&buffer[0]);

					printf("\n\n");
					
					if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
					{
						i_ext_trigger_mode = ME4000_AI_TRIGGER_EXT_DIGITAL;
						strcpy(sz_ext_trigger_mode, "ME4000_AI_TRIGGER_EXT_DIGITAL");

						break;
					}
					else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
					{
						i_ext_trigger_mode = ME4000_AI_TRIGGER_EXT_ANALOG;
						strcpy(sz_ext_trigger_mode, "ME4000_AI_TRIGGER_EXT_ANALOG");

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
		
			if(i_acq_mode == ME4000_AI_ACQ_MODE_SOFTWARE)
			{
				printf("As iAcqMode == ME4000_AI_ACQ_MODE_SOFTWARE we set iExtTriggerEdge = 0\n\n");
				
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
						strcpy(sz_ext_trigger_edge, "ME4000_AI_TRIGGER_EXT_EDGE_FALLING");

						break;
					}
					else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
					{
						i_ext_trigger_edge = ME4000_AI_TRIGGER_EXT_EDGE_RISING;
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
		
			printf(	"Press any key to call the function:\n\n"
					"me4000AIConfig(    %u,\n"
					"                   ucChanList,\n"
					"                   %u,\n" 
					"                   %s,\n" 
					"                   %s,\n"
					"                   0,\n"
					"                   %lu,\n" 
					"                   %lu,\n" 
					"                   %lu,\n"
					"                   %s,\n"
					"                   %s,\n"
					"                   %s  	                       );\n\n",
					ui_board_number,
					ui_number_of_entries,
					sz_sd_mode,
					sz_simultaneous,
					ul_chan_ticks,
					ul_scan_ticks_low,
					ul_scan_ticks_high,
					sz_acq_mode,
					sz_ext_trigger_mode,
					sz_ext_trigger_edge													);

			getch();

			int i_error = me4000AIConfig(ui_board_number, &chanList[0], ui_number_of_entries, 
													i_sd_mode, i_simultaneous, 0, ul_chan_ticks, 
																	ul_scan_ticks_low, ul_scan_ticks_high,
																		i_acq_mode, i_ext_trigger_mode, i_ext_trigger_edge);
			if(i_error == ME4000_NO_ERROR)
			{
				printf("me4000AIConfig called successfully\n\n");
			}
			else
			{
				char error_msg[256];

				me4000ErrorGetMessage(i_error, &error_msg[0], 256);

				printf("\n\n************   Error **************\n\n");

				printf("me4000AIConfig returned an error - Error code: 0x%08X\n", i_error);

				printf("    %s\n\n", &error_msg[0]);

				printf("************   Error **************\n\n");

			}

			printf("Press RETURN to call me4000AIConfig again or any other key to continue\n\n");

			char ch= getch();

			if(ch != '\r')
			{
				break;
			}
		}

		if(b_terminate)
		{
			break;
		}

		BOOL b_ai_scan = FALSE;
			
		while(TRUE)
		{
			printf("Now you should call either me4000AIScan or me4000AIContinuous:\n"
					"A) me4000AIScan\n"
					"B) me4000AIContinuous\n"
					"RETURN to terminate\n\n"
					"Your choice: "						);

			gets(&buffer[0]);

			printf("\n\n");
			
			if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
			{
				b_ai_scan = TRUE;

				break;
			}
			else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
			{
				b_ai_scan = FALSE;

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

		BOOL b_blocking = FALSE;
	
		if(b_ai_scan)
		{
			// me4000AIScan

			while(TRUE)
			{
				printf("Parameters for me4000AIScan:\n\n");

				unsigned int ui_board_number;

				unsigned int ui_count;

				ME4000_P_AI_CALLBACK_PROC p_callback;
				char sz_callback_name[64];

				unsigned int ui_callback_count;

				ME4000_P_AI_TERMINATE_PROC p_terminate;
				char sz_terminate_name[64];

				int i_exec_mode;
				char sz_exec_mode[64];
				
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
					printf("uiCount - : Number of channel lists (RETURN to terminate) ");

					gets(&buffer[0]);

					printf("\n\n");
					
					if(buffer[0] == 0)
					{
						b_terminate = TRUE;
						
						break;
					}
					
					if( (sscanf(&buffer[0], "%u", &ui_count) == 1 ) )
					{
						break;
					}
				}
				
				if(b_terminate)
				{
					break;
				}

				printf(	"The minimum buffer size required here is:\n"
						"    Number of channel lists * length of channel list\n"
						"    in this case %u * %u = %u\n\n"
						"This is the size in values ('shorts') that we require\n\n"
						"So we allocate a buffer 'p_s_buffer' of this size and pass\n"
						"the buffer together with its size in VALUES as the third and\n"
						"fourth parameters to the function me4000AIScan\n\n",
						ui_count,
						ui_number_of_entries,
						ui_count * ui_number_of_entries									);

				if(p_s_buffer != NULL)
				{
					delete p_s_buffer;
				}

				p_s_buffer = new short[ui_count * ui_number_of_entries];

				while(TRUE)
				{
					printf(	"iExecutionMode - Execution Mode:\n"
							"A) ME4000_AI_SCAN_BLOCKING\n"
							"B) ME4000_AI_SCAN_ASYNCHRONOUS\n"
							"RETURN to terminate\n\n"
							"Your choice: "						);

					gets(&buffer[0]);

					printf("\n\n");
					
					if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
					{
						i_exec_mode = ME4000_AI_SCAN_BLOCKING;
						strcpy(sz_exec_mode, "ME4000_AI_SCAN_BLOCKING");

						b_blocking = TRUE;

						break;
					}
					else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
					{
						i_exec_mode = ME4000_AI_SCAN_ASYNCHRONOUS;
						strcpy(sz_exec_mode, "ME4000_AI_SCAN_ASYNCHRONOUS");

						b_blocking = FALSE;

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
					printf(	"pCallbackProc - Callback function:\n"
							"A) TestCallback (example callback function)\n"
							"B) NULL (no callback function)\n"
							"RETURN to terminate\n\n"
							"Your choice: "						);

					gets(&buffer[0]);

					printf("\n\n");
					
					if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
					{
						p_callback = TestCallback;
						strcpy(sz_callback_name, "TestCallback");

						break;
					}
					else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
					{
						p_callback = NULL;
						strcpy(sz_callback_name, "NULL");

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
			
				printf(	"We set the callback context 'pCallbackContext' to NULL\n"
						"If you are using a callback function you can pass a\n"
						"pointer to anx data structure you like here\n\n"			);  
				
				while(TRUE)
				{
					printf("uiCallbackCount - Callback count: (RETURN to terminate) ");

					gets(&buffer[0]);

					printf("\n\n");
					
					if(buffer[0] == 0)
					{
						b_terminate = TRUE;
						
						break;
					}
					
					if( (sscanf(&buffer[0], "%u", &ui_callback_count) == 1 ) )
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
					printf(	"pTerminateProc - Termination function:\n"
							"A) TestTerminate (example termination function)\n"
							"B) NULL (no termination function)\n"
							"RETURN to terminate\n\n"
							"Your choice: "						);

					gets(&buffer[0]);

					printf("\n\n");
					
					if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
					{
						p_terminate = TestTerminate;
						strcpy(sz_terminate_name, "TestTerminate");

						break;
					}
					else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
					{
						p_terminate = NULL;
						strcpy(sz_terminate_name, "NULL");

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
			
				printf(	"We set the terminate context 'pTerminateContext' to NULL\n"
						"If you are using a terminate function you can pass a\n"
						"pointer to any data structure you like here\n\n"			);  
				
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
					
					if( (sscanf(&buffer[0], "%lu", &ul_timeout_seconds) == 1 ) )
					{
						break;
					}
				}

				printf(	"Press any key to call the function:\n\n"
						"me4000AIScan(%u,\n"
						"             %u,\n"
						"             p_s_buffer,\n" 
						"             %u,\n" 
						"             %s,\n" 
						"             %s,\n" 
						"             NULL,\n" 
						"             %u,\n"
						"             %s,\n"
						"             %u                            );\n\n",
						ui_board_number,
						ui_count,
						ui_count * ui_number_of_entries,
						sz_exec_mode,
						sz_callback_name,
						ui_callback_count,
						sz_terminate_name,
						ul_timeout_seconds								);

				getch();

				int i_error = me4000AIScan(ui_board_number, ui_count, 
												p_s_buffer, ui_count * ui_number_of_entries, 
 														i_exec_mode, p_callback, NULL, ui_callback_count,
 																		p_terminate, NULL, ul_timeout_seconds);
		
				if(i_error == ME4000_NO_ERROR)
				{
					printf("me4000AIScan called successfully\n\n");
				}
				else
				{
					char error_msg[256];

					me4000ErrorGetMessage(i_error, &error_msg[0], 256);

					printf("\n\n************   Error **************\n\n");

					printf("me4000AIScan returned an error - Error code: 0x%08X\n", i_error);

					printf("    %s\n\n", &error_msg[0]);

					printf("************   Error **************\n\n");
				}

				printf("Press RETURN to call me4000AIScan again or any other key to continue\n\n");

				char ch= getch();

				if(ch != '\r')
				{
					break;
				}
			}

			if(b_terminate)
			{
				break;
			}
		}
		else
		{
			// me4000AIContinuous

			while(TRUE)
			{
				printf("Parameters for me4000AIContinuous:\n\n");

				unsigned int ui_board_number;

				ME4000_P_AI_CALLBACK_PROC p_callback;
				char sz_callback_name[64];

				unsigned int ui_callback_freq;

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
					printf(	"pCallbackProc - Callback function:\n"
							"A) TestCallback (example callback function)\n"
							"B) NULL (no callback function)\n"
							"RETURN to terminate\n\n"
							"Your choice: "						);

					gets(&buffer[0]);

					printf("\n\n");
					
					if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
					{
						p_callback = TestCallback;
						strcpy(sz_callback_name, "TestCallback");

						break;
					}
					else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
					{
						p_callback = NULL;
						strcpy(sz_callback_name, "NULL");

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
			
				printf(	"We set the callback context 'pCallbackContext' to NULL\n"
						"If you are using a callback function you can pass a\n"
						"pointer to any data structure you like here\n\n"			);  
				
				while(TRUE)
				{
					printf("uiCallbackFrequency - Callback frequency: (RETURN to terminate) ");

					gets(&buffer[0]);

					printf("\n\n");
					
					if(buffer[0] == 0)
					{
						b_terminate = TRUE;
						
						break;
					}
					
					if( (sscanf(&buffer[0], "%u", &ui_callback_freq) == 1 ) )
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
					printf("ulTimeOutSeconds - Time out in seconds: (RETURN to terminate) ");

					gets(&buffer[0]);

					printf("\n\n");
					
					if(buffer[0] == 0)
					{
						b_terminate = TRUE;
						
						break;
					}
					
					if( (sscanf(&buffer[0], "%lu", &ul_timeout_seconds) == 1 ) )
					{
						break;
					}
				}

				printf(	"Press any key to call the function:\n\n"
						"me4000AIContinuous(%u,\n"
						"                   %s,\n"
						"                   NULL,\n" 
						"                   %u,\n"
						"                   %lu                         );\n\n",
						ui_board_number,
						sz_callback_name,
						ui_callback_freq,
						ul_timeout_seconds								);

				getch();

				int i_error = me4000AIContinuous(ui_board_number, p_callback, NULL, ui_callback_freq, ul_timeout_seconds);
		
				if(i_error == ME4000_NO_ERROR)
				{
					printf("me4000AIContinuous called successfully\n\n");
				}
				else
				{
					char error_msg[256];

					me4000ErrorGetMessage(i_error, &error_msg[0], 256);

					printf("\n\n************   Error **************\n\n");

					printf("me4000AIContinuous returned an error - Error code: 0x%08X\n", i_error);

					printf("    %s\n\n", &error_msg[0]);

					printf("************   Error **************\n\n");
				}

				printf("Press RETURN to call me4000AIContinuous again or any other key to continue\n\n");

				char ch= getch();

				if(ch != '\r')
				{
					break;
				}
			}

			if(b_terminate)
			{
				break;
			}
		}

		if(b_terminate)
		{
			break;
		}

		printf("Now you should call me4000AIStart to start the acquisition\n");

		while(TRUE)
		{
			printf("Parameters for me4000AIStart:\n\n");

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

			if(b_ai_scan)
			{
				if(b_blocking)
				{
					printf(	"You have called me4000AIScan in blocking mode.\n\n"
							"The routine AIStart will not return until the acquisition\n"
							"is complete!\n\n"												);
				}
				else
				{
					printf(	"You have called me4000AIScan in non blocking mode.\n\n"
							"The routine AIStart will return immediately and the\n" 
							"acquisition will end automatically when all data has\n"
							"been collected\n\n"										);
				}
			}
			else
			{
				printf(	"You have called me4000AIContinuous.\n\n"
						"The acquisition will continue to run until you end it by\n"
						"pressing 'S' for AIStop or 'R' for AIReset\n\n"
						"Pressing 'G' will cause me4000GetNewValues to be called\n\n");
			}

			printf(	"Press any key to call the function:\n\n"
					"me4000AIStart(%u);\n\n",
					ui_board_number									);

			if( (i_acq_mode != ME4000_AI_ACQ_MODE_SOFTWARE)&&(ul_timeout_seconds > 0) )
			{
				printf(	"me4000AIStart will not return until the trigger is recognised or\n"
						"the operation times out\n\n"										);
			}
			
			getch();

			int i_error = me4000AIStart(ui_board_number);
	
			if(i_error == ME4000_NO_ERROR)
			{
				printf("me4000AIStart called successfully\n\n");
				
				if( (i_acq_mode != ME4000_AI_ACQ_MODE_SOFTWARE)&&(ul_timeout_seconds > 0) )
				{
					printf("Trigger recognised\n\n");
				}

				if(!b_ai_scan)
				{
					while(TRUE)
					{
						if( kbhit() )
						{
							char ch = getch();

							if( (ch == 's')||(ch == 'S') )
							{
								me4000AIStop(ui_board_number, 0);

								b_terminate = TRUE;

								break;
							}
							else if( (ch == 'r')||(ch == 'R') )
							{
								me4000AIReset(ui_board_number);

								b_terminate = TRUE;

								break;
							}
							else if( (ch == 'g')||(ch == 'G') )
							{
								int i_last_error;

								unsigned long ul_number_of_data;
								
								me4000AIGetNewValues(ui_board_number, sScanBuffer, SIZE_OF_SCAN_BUFFER, 
															ME4000_AI_GET_NEW_VALUES_NON_BLOCKING, &ul_number_of_data, &i_last_error);

								printf(	"    me4000AIGetNewValues called\n");

								if(i_last_error == ME4000_NO_ERROR)
								{
									printf("Number of values: %lu\n\n", ul_number_of_data);

									for(unsigned int index_channel = 0; index_channel < ui_number_of_entries; index_channel++)
									{
										double d_volt;

										me4000AIDigitToVolt(sScanBuffer[index_channel], iRange[index_channel], &d_volt);

										printf("Channel: %2d    -    Value: %f\n", (int)(chanList[index_channel] & 0x1f), d_volt ); 
									}

									printf("\n\n");
								}
								else
								{
									char error_msg[256];

									me4000ErrorGetMessage(i_last_error, &error_msg[0], 256);

									printf("me4000AIGetNewValues returned an error - Error code: 0x%08X\n", i_last_error);
									printf("    %s\n\n", &error_msg[0]);
								}
							}
						}
					}
				}
			}
			else
			{
				char error_msg[256];

				me4000ErrorGetMessage(i_error, &error_msg[0], 256);

				printf("\n\n************   Error **************\n\n");

				printf("me4000AIStart returned an error - Error code: 0x%08X\n", i_error);

				printf("    %s\n\n", &error_msg[0]);

				printf("************   Error **************\n\n");
			}

			if(b_terminate)
			{
				break;
			}
		}

		
		printf("Press RETURN to terminate or any other key to continue\n\n");

		char ch = getch();

		if(ch == '\r')
		{
			break;
		}
	}

	if(p_s_buffer != NULL)
	{
		delete p_s_buffer;
	}

	return(0);
}


void _stdcall TestCallback(short* psValues, unsigned int uiNumberOfValues, 
	                                         void* pCallbackContext, int iLastError)
{
	printf(	"    TestCallback called\n");

	if(iLastError == ME4000_NO_ERROR)
	{
		printf("Number of values: %u\n\n", uiNumberOfValues);

		for(unsigned int index_channel = 0; index_channel < ui_number_of_entries; index_channel++)
		{
			double d_volt;

			int i_range = (int)(chanList[index_channel] & 0xC0);
			
			me4000AIDigitToVolt(psValues[index_channel], i_range, &d_volt);

			printf("Channel: %2d    -    Value: %f\n", (int)(chanList[index_channel] & 0x1f), d_volt ); 
		}

		printf("\n\n");
	}
	else
	{
		char error_msg[256];

		me4000ErrorGetMessage(iLastError, &error_msg[0], 256);

		printf("TestCallback returned an error - Error code: 0x%08X\n", iLastError);
		printf("    %s\n\n", &error_msg[0]);
	}
}


void _stdcall TestTerminate(short* psValues, unsigned int uiNumberOfValues, 
	                                         void* pCallbackContext, int iLastError)
{
	printf(	"    TestTerminate called\n");

	if(iLastError == ME4000_NO_ERROR)
	{
		printf("Number of values: %u\n\n", uiNumberOfValues);

		for(unsigned int index_channel = 0; index_channel < ui_number_of_entries; index_channel++)
		{
			double d_volt;

			int i_range = (int)(chanList[index_channel] & 0xC0);
			
			me4000AIDigitToVolt(psValues[index_channel], i_range, &d_volt);

			printf("Channel: %2d    -    Value: %f\n", (int)(chanList[index_channel] & 0x1f), d_volt ); 
		}

		printf("\n\n");
	}
	else
	{
		char error_msg[256];

		me4000ErrorGetMessage(iLastError, &error_msg[0], 256);

		printf("TestTerminate returned an error - Error code: 0x%08X\n", iLastError);
		printf("    %s\n\n", &error_msg[0]);
	}
}

