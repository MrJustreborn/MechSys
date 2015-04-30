// _DIOTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#include <conio.h>

#include "..\me4000dll.h"

void _stdcall ErrorFunction(char* function_name, int error_code);

void _stdcall PrintIRQCount(void* pCallbackContext);

int main(int argc, char* argv[])
{
	me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

	unsigned long ul_version;
	
	me4000GetDLLVersion(&ul_version);

	printf("ME4000 - DLL Version: %08X\n", ul_version);

	me4000GetDriverVersion(&ul_version);

	printf("ME4000 - Driver Version: %08X\n\n", ul_version);

	printf(	"This program demonstrates the use of the routines me4000ExtIrqEnable and\n"
			"me4000ExtIrqDisable to install and deinstall a handler for the external\n"
			"interrupt on the first ME4000 board found on your system.\n\n" 
			"It also demonstrates the use of the routine me4000ExtIrqGetCount to determine\n"
			"how many external interrupts have occurred since the system was started\n\n");	
	
	printf("Press any key now to continue\n");

	getch();
	
	while(TRUE)
	{
		printf("\n\n");
		
		printf(	"Press ESC to exit or any other key to install a handler for the external\n"
				"interrupt which will call the routine me4000ExtIrqGetCount each time the\n"
				"interrupt is triggered and print the result on the screen.\n\n"				);


		char ch = getch();

		if(ch == 27)
		{
			break;
		}
		
		me4000ExtIrqEnable(0, PrintIRQCount, NULL);
	
		printf("External interrupt enabled\n\n");

		printf("Press any key to disable the external interrupt\n\n");

		getch();
	
		me4000ExtIrqDisable(0);
	
		printf("\n\n");
		
		printf("External interrupt disabled\n\n");
	}
	
	printf("\nPress any key to terminate\n");

	_getch();

	return 0;
}

void _stdcall PrintIRQCount(void* pCallbackContext)
{
	unsigned int ui_irq_count;
	
	me4000ExtIrqGetCount(0, &ui_irq_count);	

	printf("Interrupt handler called - IRQ count: %u\n", ui_irq_count);
}

