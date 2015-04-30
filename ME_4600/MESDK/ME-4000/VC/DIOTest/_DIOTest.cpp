// _DIOTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include "..\me4000dll.h"

void _stdcall ErrorFunction(char* function_name, int error_code);

#define FUNCTION_DIOConfig		0
#define FUNCTION_DIOResetAll	1
#define FUNCTION_DIOGetBit		2
#define FUNCTION_DIOGetByte		3
#define FUNCTION_DIOSetBit		4
#define FUNCTION_DIOSetByte		5

int main(int argc, char* argv[])
{
	me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

	unsigned long ul_version;
	
	me4000GetDLLVersion(&ul_version);

	printf("ME4000 - DLL Version: %08X\n", ul_version);

	me4000GetDriverVersion(&ul_version);

	printf("ME4000 - Driver Version: %08X\n\n", ul_version);

	printf("Press any key now to continue\n\n");

	_getch();
	
	while(TRUE)
	{
		char buffer[128];

		BOOL b_terminate = FALSE;
		
		int i_function = 0;
		
		while(TRUE)
		{
			printf(	"Function:\n"
					"A) me4000DIOConfig\n"
					"B) me4000DIOResetAll\n"
					"C) me4000DIOGetBit\n"
					"D) me4000DIOGetByte\n"
					"E) me4000DIOSetBit\n"
					"F) me4000DIOSetByte\n"
					"RETURN to terminate\n\n"
					"Your choice: "						);

			gets(&buffer[0]);

			printf("\n\n");
			
			if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
			{
				i_function = FUNCTION_DIOConfig;

				break;
			}
			else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
			{
				i_function = FUNCTION_DIOResetAll;

				break;
			}
			else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
			{
				i_function = FUNCTION_DIOGetBit;

				break;
			}
			else if( (strcmp(&buffer[0], "d") == 0)||(strcmp(&buffer[0], "D") == 0) )
			{
				i_function = FUNCTION_DIOGetByte;

				break;
			}
			else if( (strcmp(&buffer[0], "e") == 0)||(strcmp(&buffer[0], "E") == 0) )
			{
				i_function = FUNCTION_DIOSetBit;

				break;
			}
			else if( (strcmp(&buffer[0], "f") == 0)||(strcmp(&buffer[0], "F") == 0) )
			{
				i_function = FUNCTION_DIOSetByte;

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
		
		if(i_function == FUNCTION_DIOConfig)
		{
			unsigned int ui_port_number;
			
			int i_port_mode;
			
			while(TRUE)
			{
				printf(	"Port number:\n"
						"A) Port A\n"
						"B) Port B\n"
						"C) Port C\n"
						"D) Port D\n"
						"RETURN to terminate\n\n"
						"Your choice: "						);

				gets(&buffer[0]);

				printf("\n\n");
				
				if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_A;

					break;
				}
				else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_B;

					break;
				}
				else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_C;

					break;
				}
				else if( (strcmp(&buffer[0], "d") == 0)||(strcmp(&buffer[0], "D") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_D;

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
				printf(	"Port mode:\n"
						"A) Input\n"
						"B) Output\n"
						"RETURN to terminate\n\n"
						"Your choice: "						);

				gets(&buffer[0]);

				printf("\n\n");
				
				if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
				{
					i_port_mode = ME4000_DIO_PORT_INPUT;

					break;
				}
				else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
				{
					i_port_mode = ME4000_DIO_PORT_OUTPUT;

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
		
			me4000DIOConfig(0, ui_port_number, i_port_mode);	
		}
		else if(i_function == FUNCTION_DIOResetAll)
		{
			me4000DIOResetAll(0);	

			printf("me4000DIOResetAll called\n\n"
				   "Press RETURN to exit or any other key to continue\n\n");

			char ch = getch();

			if(ch == 27)
			{
				break;
			}
		}
		else if(i_function == FUNCTION_DIOGetBit)
		{
			unsigned int ui_port_number;
			
			unsigned int ui_bit_number;

			while(TRUE)
			{
				printf(	"Port number:\n"
						"A) Port A\n"
						"B) Port B\n"
						"C) Port C\n"
						"D) Port D\n"
						"RETURN to terminate\n\n"
						"Your choice: "						);

				gets(&buffer[0]);

				printf("\n\n");
				
				if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_A;

					break;
				}
				else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_B;

					break;
				}
				else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_C;

					break;
				}
				else if( (strcmp(&buffer[0], "d") == 0)||(strcmp(&buffer[0], "D") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_D;

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
				printf(	"Bit number (RETURN to terminate): ");

				gets(&buffer[0]);

				printf("\n\n");
				
				if(buffer[0] == 0)
				{
					b_terminate = TRUE;
					
					break;
				}
				else if(sscanf(&buffer[0], "%u", &ui_bit_number) == 1)
				{
					break;
				}
			}

			if(b_terminate)
			{
				break;
			}
		
			int i_bit_value;
			
			me4000DIOGetBit(0, ui_port_number, ui_bit_number, &i_bit_value);
			
			printf("Bit value: %d\n\n", i_bit_value);

			printf("Press RETURN to exit or any other key to continue\n\n");

			char ch = getch();

			if(ch == 27)
			{
				break;
			}
		}
		else if(i_function == FUNCTION_DIOGetByte)
		{
			unsigned int ui_port_number;
			
			while(TRUE)
			{
				printf(	"Port number:\n"
						"A) Port A\n"
						"B) Port B\n"
						"C) Port C\n"
						"D) Port D\n"
						"RETURN to terminate\n\n"
						"Your choice: "						);

				gets(&buffer[0]);

				printf("\n\n");
				
				if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_A;

					break;
				}
				else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_B;

					break;
				}
				else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_C;

					break;
				}
				else if( (strcmp(&buffer[0], "d") == 0)||(strcmp(&buffer[0], "D") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_D;

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
		
			unsigned char uc_byte_value;
			
			me4000DIOGetByte(0, ui_port_number, &uc_byte_value);	
			
			printf("Byte value: 0x%02X\n\n", uc_byte_value);

			printf("Press RETURN to exit or any other key to continue\n\n");

			char ch = getch();

			if(ch == 27)
			{
				break;
			}
		}
		else if(i_function == FUNCTION_DIOSetBit)
		{
			unsigned int ui_port_number;
			
			unsigned int ui_bit_number;

			int i_bit_value;
			
			while(TRUE)
			{
				printf(	"Port number:\n"
						"A) Port A\n"
						"B) Port B\n"
						"C) Port C\n"
						"D) Port D\n"
						"RETURN to terminate\n\n"
						"Your choice: "						);

				gets(&buffer[0]);

				printf("\n\n");
				
				if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_A;

					break;
				}
				else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_B;

					break;
				}
				else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_C;

					break;
				}
				else if( (strcmp(&buffer[0], "d") == 0)||(strcmp(&buffer[0], "D") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_D;

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
				printf(	"Bit number (RETURN to terminate): ");

				gets(&buffer[0]);

				printf("\n\n");
				
				if(buffer[0] == 0)
				{
					b_terminate = TRUE;
					
					break;
				}
				else if(sscanf(&buffer[0], "%u", &ui_bit_number) == 1)
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
				printf(	"Bit value:\n"
						"A) 0\n"
						"B) 1\n"
						"RETURN to terminate\n\n"
						"Your choice: "						);

				gets(&buffer[0]);

				printf("\n\n");
				
				if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
				{
					i_bit_value = 0;

					break;
				}
				else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
				{
					i_bit_value = 1;

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
		
			me4000DIOSetBit(0, ui_port_number, ui_bit_number, i_bit_value);	
		}
		else if(i_function == FUNCTION_DIOSetByte)
		{
			unsigned int ui_port_number;
			
			unsigned char uc_byte_value;
			
			while(TRUE)
			{
				printf(	"Port number:\n"
						"A) Port A\n"
						"B) Port B\n"
						"C) Port C\n"
						"D) Port D\n"
						"RETURN to terminate\n\n"
						"Your choice: "						);

				gets(&buffer[0]);

				printf("\n\n");
				
				if( (strcmp(&buffer[0], "a") == 0)||(strcmp(&buffer[0], "A") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_A;

					break;
				}
				else if( (strcmp(&buffer[0], "b") == 0)||(strcmp(&buffer[0], "B") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_B;

					break;
				}
				else if( (strcmp(&buffer[0], "c") == 0)||(strcmp(&buffer[0], "C") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_C;

					break;
				}
				else if( (strcmp(&buffer[0], "d") == 0)||(strcmp(&buffer[0], "D") == 0) )
				{
					ui_port_number = ME4000_DIO_PORT_D;

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
				printf(	"Byte value (RETURN to terminate): 0x");

				gets(&buffer[0]);

				printf("\n\n");
				
				if(buffer[0] == 0)
				{
					b_terminate = TRUE;
					
					break;
				}
				else if(sscanf(&buffer[0], "%X", &uc_byte_value) == 1)
				{
					break;
				}
			}

			if(b_terminate)
			{
				break;
			}
		
			if(b_terminate)
			{
				break;
			}
		
			me4000DIOSetByte(0, ui_port_number, uc_byte_value);	
		}
	}
	
	printf("\nPress any key to terminate\n");

	_getch();

	return 0;
}

