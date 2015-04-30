// meConsoleTest.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#include "..\me4000dll.h"
#include "..\sweep.h"

void _stdcall TestErrorFunction(char* function_name, int error_code);


void main(void)
{
	me4000ErrorSetUserProc(TestErrorFunction);
    
	unsigned long ul_version;
	me4000GetDLLVersion(&ul_version);
	printf("DLL Version: %08X\n", ul_version);
	me4000GetDriverVersion(&ul_version);
	printf("Driver Version: %08X\n", ul_version);

    me4000MultiSigAIOpen(0);
    me4000MultiSigReset(0);
    Sleep(300);
    me4000MultiSigAddressLED(0, 0, ME4000_MULTISIG_LED_ON);
    Sleep(300);
    me4000MultiSigAddressLED(0, 0, ME4000_MULTISIG_LED_OFF);
    Sleep(300);
    me4000MultiSigAddressLED(0, 0, ME4000_MULTISIG_LED_ON);
    Sleep(300);
    me4000MultiSigAIClose(0);
    
	printf("Press any key to terminate\n\n");
	getch();
}

void _stdcall TestErrorFunction(char* function_name, int error_code)
{
	char error_msg[256];

	me4000ErrorGetMessage(error_code, &error_msg[0], 256);
	printf("\n\n************   Error **************\n\n");
	printf("Error calling function: %s - Error code: 0x%08X\n", function_name, error_code);
	printf("    %s\n\n", &error_msg[0]);
	printf("************   Error **************\n\n");
}

