/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       Visual C++ 6.0                                                                          */
/*  Copyright:      2000 Meilhaus Electronic GmbH                                                           */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                                                                                                          */
/*  Description:    General Example for the board ME-96 (CP-380 IO)                                         */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    001013  ab      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#include <windows.h>
#include <conio.h>
#include <stdio.h>

/* Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEUNIT("..\medefs.h");
USEUNIT("..\DLLInit.h");
#endif

#include "..\medefs.h"
//#include "..\me9x.h"
#include "..\DLLInit.h"


#define BOARDNUMBER	    0
#define MAXGenIrqCnt	10
#define MAXBitNumber	16

// simple callback function to test interrupts
void _stdcall IrqHandler(void);


int count=0;		// IRQ Counter


int main(void)
{
	int iDLLVers;
	int iBoardTyp;
	int iErrCode;
	int iIOValueGet0;
	int iIOValueGet1;
	int iIrqSave;


    printf("ME-94 (CP380-I) programm for demonstration\n");
    printf("==========================================\n\n");

    meOpen();

	// read driver infos
	iDLLVers = _me9xGetDLLVersion();
	printf("DLLVers:  %08x (hex)\n\n", iDLLVers);

	// read board infos
	iErrCode = _me9xGetBoardVersion(BOARDNUMBER, &iBoardTyp);

    if (iErrCode != 1)
    {
        // Board not found
        printf("Board number %d does not exist!\n", BOARDNUMBER);
        printf("(Or not correctly installed)\n");
    }
    else
    {
        if (iBoardTyp != 0x94)
        {
            printf("Board number %d is not configured as ME-94 (CP380-I)\n", BOARDNUMBER);
            printf("Please use a other example !\n");
        }
        else
        {
            printf("Board number %d is configured as ME-94 (CP380-I)\n", BOARDNUMBER);

            // IO programming:
            printf("\nRead byte:\n");
            iErrCode = _me94DIGetByte(BOARDNUMBER, 0, &iIOValueGet0);
			iErrCode = _me94DIGetByte(BOARDNUMBER, 1, &iIOValueGet1);
			printf("Read 0x%02x%02x\n", iIOValueGet0, iIOValueGet1);
            Sleep(500);

            // IRQ programming:
			// set and enable interrupt mode
            iIrqSave = count;
			iErrCode = _me94EnableInt(BOARDNUMBER,IrqHandler);

            // generate interrupts yourself
            printf("\nInterrupt processing:\n");
			printf("\nNow we wait 5 seconds on external interrupts\n");
			Sleep(5000);
			if (iIrqSave == count)
				printf("No interrupts occured\n");

			// disable IRQ
			iErrCode = _me94DisableInt(BOARDNUMBER);
        }
    }

    meClose();

	return iErrCode;
}


// simple Callback function
void _stdcall IrqHandler(void)
{
	count++;
	if (count == 65000) 
		count = 0;
	printf("<IRQ> ");
    //printf("+");
    //printf(".%04d", count);
}