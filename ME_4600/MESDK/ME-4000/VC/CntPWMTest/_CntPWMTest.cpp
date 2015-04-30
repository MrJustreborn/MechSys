// _DIOTest.cpp : Defines the entry point for the console application.
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

	printf(	"This program demonstrates the use of the routines me4000CntPWMStart and\n"
			"me4000PWMStop to generate a pulse-width modulated signal on the first\n"
			"ME4000 board found on your system.\n\n" 
			"Please note, for this to function correctly you must setup your hardware\n"
			"as described in the chapter 'Pule-wide modulation' of your handbook\n\n"		);	
	
	printf("Press any key now to continue\n\n");

	_getch();
	
	while(TRUE)
	{
		char buffer[128];

		unsigned int ui_pre_scaler;

		int i_duty_cycle;

		BOOL b_terminate = FALSE;
		
		while(TRUE)
		{
			printf("Pre-scaler ( 2 - 100 ) (RETURN to terminate) :");

			gets(&buffer[0]);

			printf("\n\n");
			
			if(buffer[0] == 0)
			{
				b_terminate = TRUE;
				
				break;
			}
			else if(sscanf(&buffer[0], "%u", &ui_pre_scaler) == 1)
			{
				if( (2 <= ui_pre_scaler)&&(ui_pre_scaler <= 100 ) )
				{
					break;
				}
			}
		}

		if(b_terminate)
		{
			break;
		}
		
		while(TRUE)
		{
			printf("Duty cycle ( 1 - 99 %) (RETURN to terminate) :");

			gets(&buffer[0]);

			printf("\n\n");
			
			if(buffer[0] == 0)
			{
				b_terminate = TRUE;
				
				break;
			}
			else if(sscanf(&buffer[0], "%d", &i_duty_cycle) == 1)
			{
				if( (1 <= i_duty_cycle)&&(i_duty_cycle <=99 ) )
				{
					break;
				}
			}
		}

		if(b_terminate)
		{
			break;
		}
		
		printf("Press RETURN to exit or any other key to start the pulse wide modulation\n\n");

		char ch = getch();

		if(ch == '\r')
		{
			break;
		}
		
		me4000CntPWMStart(0, ui_pre_scaler, i_duty_cycle);
	
		printf("Press any key to terminate the pulse-wide modulation\n\n");

		getch();

		me4000CntPWMStop(0);
	}
	
	printf("\nPress any key to terminate\n");

	_getch();

	return 0;
}

