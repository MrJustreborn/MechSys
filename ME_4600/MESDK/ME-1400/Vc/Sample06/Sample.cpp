/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to Ralph Timm for the function wrapper                                   */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
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


#define MAXNAME         0x10
#define ME_MAX_DEVICES  32

int iIrqCount = 0;


//prototypes:
void CheckErrorCode(int iErrorCode, int iLine);


// Please use the manual for the description of the functions
int main (void)
{
    int iErrorCode;
    int iBoardNumber=0;


    meOpen();  // calls the initialize function

    /*
    ME1400_TIMERINTERNCLOCK_10MHZ   0x08
    ME1400_TIMERINTERNCLOCK_1MHZ    0x00

    ME1400_MULTIPIN_IRQ             0x00
    ME1400_MULTIPIN_INTERNALCLOCK   0x01
    */

    iErrorCode = me1400InitModeTimerA(
        iBoardNumber,
        ME1400_TIMERINTERNCLOCK_10MHZ);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400SetMultifunctionPin(
        iBoardNumber,
        ME1400_MULTIPIN_INTERNALCLOCK);
    CheckErrorCode(iErrorCode, __LINE__);

    printf("Multifunction with 10 MHz\n");
    getch();


    iErrorCode = me1400InitModeTimerA(
        iBoardNumber,
        ME1400_TIMERINTERNCLOCK_1MHZ);
    CheckErrorCode(iErrorCode, __LINE__);

    printf("Multifunction with 1 MHz\n");
    getch();


    iErrorCode = me1400SetMultifunctionPin(
        iBoardNumber,
        ME1400_MULTIPIN_IRQ);
    CheckErrorCode(iErrorCode, __LINE__);

    printf("Multifunction pin is input (no signal)\n");
    getch();


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
