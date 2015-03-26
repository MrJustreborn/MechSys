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

#include <windows.h>  // für winbase.h
#include <winbase.h>  // für sleep
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

#define BOARD_0 0


int main(void)
{
    int retval = 0;
    DWORD   dwIdx;
    int dwIrqCnt1;
    int dwIrqCnt2;

    meOpen();

    // Vorabtest IRQ:
    _me9xGetIrqCnt(BOARD_0, 0, &dwIrqCnt1);

    // interrupt enablen
    retval = _me96EnableInt(BOARD_0,NULL);

    // Bytes schreiben
    for (dwIdx=0; dwIdx<10; dwIdx++)
    {
        retval = _me96DOSetByte(BOARD_0,0,0xAA);
        Sleep(30);
        retval = _me96DOSetByte(BOARD_0,0,0x55);
        Sleep(30);
    }

	// Irq abschalten
	retval = _me96DisableInt(BOARD_0);

    _me9xGetIrqCnt(BOARD_0, 0, &dwIrqCnt2);
    printf("IrqCnt1:\t%04d\n",dwIrqCnt1);
    printf("IrqCnt2:\t%04d\n",dwIrqCnt2);
    printf("IrqCntDiff:\t%04d\n",dwIrqCnt2-dwIrqCnt1);

    meClose();

	return retval;
}
