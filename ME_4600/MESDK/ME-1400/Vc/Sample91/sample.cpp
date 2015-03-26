/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to Ralph Timm for the function wrapper                                   */
/*                                                                                                          */
/*  Description:    calling all functions sequentiell                                                       */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    980706  ab      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/


/*--- system header files -------*/
#include <stdio.h>
#include <windows.h>
#include <conio.h>

/*--- me1400 header files -------*/
#include ".\..\medefs.h"
//#include ".\..\me1400.h"          // for using with a lib
#include ".\..\DLLInit.h"           // for using with dynamic DLL accessing

/*--- Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEFILE("..\medefs.h");
USEFILE("..\DLLInit.h");
USEUNIT("..\DLLInit.cpp");
#endif



void ErrorHandler ();
void _stdcall IrqFunc (void);   //user defined interrupt service routine

/* ------------------------  Main Program ------------------------------- */

/*  This program calls each of the functions for the me1400 once
    to test that the dll functions are found.  There is no useful
    function to the program other than to test that the functions
    are found.
*/

void main(void)
{
    int iErrorCode;
    char pcErrorText[0x100] ="";
    int piVersion;
    int piValue;
    int IrqCnt;
    int iDLLVersion;

    meOpen ();  // calls the initialize function

    // determine current DLL version
    iDLLVersion = me1400GetDLLVersion();

    printf(
        "DLL version is %04x.%04x\n",
        (iDLLVersion>>16)& 0xFFFF,
        (iDLLVersion)    & 0xFFFF);

    iErrorCode =  me1400GetBoardVersion (0, &piVersion);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400DIOSetPortDirection (0, 0, 0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400DIGetBit (0, 0, 0, &piValue);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400DIGetByte (0, 0, &piValue);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400DOSetBit (0, 0, 0, 0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400DOSetByte (0, 0, 0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400CntRead (0, 0, &piValue);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400CntWrite (0, 0, 0, 0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400EnableInt (0, IrqFunc, 1);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400DisableInt (0, 1);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400InitModeTimerA (0, 0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400InitModeTimerB (0, 0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400SetMultifunctionPin (0, 0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400GetIrqCnt (0, &IrqCnt);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode =  me1400GetDrvErrMess (pcErrorText);
    if (iErrorCode == 0)
    {
    }
    printf(pcErrorText);

    meClose();
}

void ErrorHandler (void)
{
    printf ("\n\n**** Error Occurred in DLL function call ****\n\n");
}

// interrupt service rountine just prints a message
void _stdcall IrqFunc ()
{
    printf("\n\n******************   INTERRUPT!   *****************\n\n");
}
/*  ------------------------------------------------------------ */
