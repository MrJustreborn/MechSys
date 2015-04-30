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

#include <windows.h>    // winbase.h
#include <winbase.h>    // sleep
#include <stdio.h>      // 
#include <conio.h>      // _kbhit

/* Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEUNIT("..\medefs.h");
USEUNIT("..\DLLInit.h");
#endif

#include "..\medefs.h"
//#include "..\me9x.h"
#include "..\DLLInit.h"

#define BOARD_0 0

void _stdcall IrqHandler(void);

long count=0;		// IRQ Counter

int main (void)
{
    int retval = 0;

    meOpen();

	// enable interrupt
    retval = _me96EnableInt(BOARD_0, IrqHandler);

    printf("Press any key to stop processing.\n");
    while(!kbhit())
    {
        count=0;
        Sleep(1000);
        printf("Irq per Second: %4d\n", count);
    }

	// disable interrupt
	retval = _me96DisableInt(BOARD_0);

    meClose();

    return(retval);
}


void _stdcall IrqHandler(void)
{
	count++;
}
