/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to Ralph Timm for the function wrapper                                   */
/*                                                                                                          */
/*  Description:    Example for port C and F                                                                */
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


#define BOARD_0         0

//prototypes:
void CheckErrorCode(int iErrorCode, int iLine);


int main (void)
{
    int iErrorCode;
    int iBoardVersion;
    int iDLLVersion;
    int iValue;


    meOpen();  // calls the initialize function

    // determine current DLL version
    iDLLVersion = me1400GetDLLVersion ();
    printf(
        "iDLLVersion: Major: 0x%04x Minor: 0x%04x\n",
        (iDLLVersion>>16)& 0xFFFF,
        (iDLLVersion)    & 0xFFFF);


    // determine board version
    iErrorCode = me1400GetBoardVersion(
        BOARD_0,
        &iBoardVersion);
    CheckErrorCode(iErrorCode, __LINE__);
    printf(
        "BoardVersion of board %02d is %04X\n",
        BOARD_0,
        iBoardVersion);


    /*--- Digital Input / Output ---------------------*/

    printf("Set port CL to output:\n");
    iErrorCode = me1400DIOSetPortDirection(
        BOARD_0,
        PORTCL,
        MEOUTPUT);
    CheckErrorCode(iErrorCode, __LINE__);

    printf("Set port CH to input:\n");
    iErrorCode = me1400DIOSetPortDirection(
        BOARD_0,
        PORTCH,
        MEINPUT);
    CheckErrorCode(iErrorCode, __LINE__);



    iValue = 0xC;

    printf("\tset Bit 0 (Pin 30) to %x\n", (iValue & 0x1));
    printf("\tset Bit 1 (Pin 11) to %x\n", (iValue & 0x2)>1);
    printf("\tset Bit 2 (Pin 31) to %x\n", (iValue & 0x4)>2);
    printf("\tset Bit 3 (Pin 12) to %x\n", (iValue & 0x8)>3);

    iErrorCode = me1400DOSetByte(
        BOARD_0,
        PORTCL,
        iValue);
    CheckErrorCode(iErrorCode, __LINE__);



    iErrorCode = me1400DIGetByte(
        BOARD_0,
        PORTCH,
        &iValue);
    CheckErrorCode(iErrorCode, __LINE__);

    printf("GetByte 0x%x\n", iValue);

    printf("\tget Bit 0 (Pin 32) to %x\n", (iValue & 0x10)>4);
    printf("\tget Bit 1 (Pin 13) to %x\n", (iValue & 0x20)>5);
    printf("\tget Bit 2 (Pin 33) to %x\n", (iValue & 0x40)>6);
    printf("\tget Bit 3 (Pin 14) to %x\n", (iValue & 0x80)>7);

    meClose();

    printf ("\n  ***** Press Return to quit *****");
    getchar();
    getch();

    return 0;
}







void CheckErrorCode(int iErrorCode, int iLine)
{
    char pcErrorText[0xFF];

    if (iErrorCode != 1)
    {
        printf("Error in Line %d: ", iLine);
        me1400GetDrvErrMess(pcErrorText);
        if (pcErrorText != NULL)
            printf("\t%s\n",pcErrorText);

        // It may be:
        //  * wrong board number: 2072656C
        //  * wrong irq channel : 57    = 87    The parameter is incorrect.     ERROR_INVALID_PARAMETER
        //  *                   : 9B    = 155   Cannot create another thread.   ERROR_TOO_MANY_TCBS
        //  *                   :
    }
}
