// meConsoleTest.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#include "..\me4000dll.h"
#include "..\sweep.h"


void main(void)
{
    me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

	unsigned long ulDLLVersion;
	me4000GetDLLVersion(&ulDLLVersion);
    printf("DLL Version:\t%08X\n", ulDLLVersion);

    unsigned long ulDrvVersion;
    me4000GetDriverVersion(&ulDrvVersion);
	printf("Driver Version:\t%08X\n\n", ulDrvVersion);

    for (int iBoardNumber=0; iBoardNumber<32; iBoardNumber++)
    {
        unsigned short usBrdVersion;

        me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_DISABLE);
        int iErrorCode = me4000GetBoardVersion(iBoardNumber, &usBrdVersion);
        me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

        if (iErrorCode == 0)
        {
            printf("Found Board With Board Number: %d\n", iBoardNumber);

            printf("\tBoard version:\t%8X\n", usBrdVersion);

            unsigned long ulSrlNumber;
            me4000GetSerialNumber(
                iBoardNumber,       // uiBoardNumber
                &ulSrlNumber);      // pulSerialNumber
            printf("\tSerial number:\t%08X\n\n", ulSrlNumber);
        }        
    }

	printf("Press any key to terminate\n\n");
	getch();
}
