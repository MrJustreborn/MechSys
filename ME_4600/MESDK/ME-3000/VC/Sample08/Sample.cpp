/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to Ralph Timm for the function wrapper                                   */
/*                                                                                                          */
/*  Description:    Sample to demonstrate the external interrupt input                                      */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    991230  ab      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/


/*--- system header files -------*/
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream.h>
#include <stdio.h>
#include <windows.h>

/*--- me3000 header files -------*/
#include ".\..\meDefs.h"
//#include ".\..\me3000.h"
#include ".\..\DLLInit.h"

/*--- Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEFILE("..\meDefs.h");
USEFILE("..\DLLInit.h");
USEUNIT("..\DLLInit.cpp");
#endif


// simple callback function to test interrupts
void _stdcall IrqHandler(void);

long count=0;       // IRQ Counter



void main (void)
{
    meOpen();  // calls the initialize function

    me3000EnableExternalInt(0, IrqHandler);

    while(!kbhit())
    {
        count=0;
        Sleep(1000);
        printf("Irq per Second: %4d\n", count);
    }
    me3000DisableExternalInt(0);

    meClose();

    printf ("\n  ***** Press Return to quit *****");
    getchar ();
}



// simple Callback function
void _stdcall IrqHandler(void)
{
    count++;
    //printf("<IRQ> ");
}