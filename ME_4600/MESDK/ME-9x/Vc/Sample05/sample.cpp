/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       Visual C++ 6.0                                                                          */
/*  Copyright:      1998 Meilhaus Electronic GmbH                                                           */
/*  Author:         rt                                                                                      */
/*                                                                                                          */
/*  Description:    General Example for the boards ME-94, ME-95 or/and ME-96 (CP-380)                       */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    981230  rt      create                                                          */
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

void ErrorHandler ();
void _stdcall IrqFunc (void);   //user defined interrupt service routine


/* ------------------------  Main Program ------------------------------- */
/*  This program calls each of the functions for the me9x once
    to test that the dll functions are found.  There is no useful
    function to the program other than to test that the functions
    are found.
*/

void main(void)
{
    int iErrorCode;
    int piVersion;
    int piBitValue;
    int iValue;
    char pcErrorText [20];

    meOpen ();  // calls the initialize function

    iErrorCode = me9xGetBoardVersion (0, &piVersion);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me9xGetDLLVersion ();
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me9xGetDrvErrMess (pcErrorText);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me94DIGetBit (0, 0, &piBitValue);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me94DIGetByte (0, 0, &iValue);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me94EnableInt (0, IrqFunc);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me94DisableInt (0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me95DOSetBit (0, 0, 0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }
    iErrorCode = me95DOSetByte (0, 0, 0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me96DIGetBit (0, 0, &piBitValue);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me96DIGetByte (0, 0, &iValue);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me96DOSetBit (0, 0, 0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me96DOSetByte (0, 0, 0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me96EnableInt (0, IrqFunc);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

    iErrorCode = me96DisableInt (0);
    if (iErrorCode == 0)
    {
        ErrorHandler ();
    }

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
