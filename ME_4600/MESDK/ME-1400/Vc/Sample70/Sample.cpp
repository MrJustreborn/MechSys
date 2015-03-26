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
#include ".\..\DLLInit.h"           // for using with dynamic DLL accessing


int iIrqCount = 0;
int iBoardNumber  = 0;


//prototypes:
void CheckErrorCode(int iErrorCode, int iLine);
void _stdcall IRQFKT (void);
unsigned short Read(void);


// Please use the manual for the description of the functions
int main (void)
{
    int iErrorCode;
    int iDLLVersion;
    int iDrvVersion;
    int iBoardVersion;



    meOpen();  // calls the initialize function


    /*--- define board number here ------------------------------*/
    printf("All that stuff is valid for board %d\n", iBoardNumber);


    /*--- determine current DLL version -------------------------*/
    iDLLVersion = me1400GetDLLVersion ();

    printf(
        "iDLLVersion: Major: 0x%04x Minor: 0x%04x\n",
        (iDLLVersion>>16)& 0xFFFF,
        (iDLLVersion)    & 0xFFFF);


    /*--- determine current Drv version -------------------------*/
    iErrorCode = me1400GetDriverVersion(&iDrvVersion);
    CheckErrorCode(iErrorCode, __LINE__);

    printf(
        "iDrvVersion: Major: 0x%04x Minor: 0x%04x\n",
        (iDrvVersion>>16)& 0xFFFF,
        (iDrvVersion)    & 0xFFFF);


    /*--- determine board version -------------------------------*/
    iErrorCode = me1400GetBoardVersion(
        iBoardNumber,
        &iBoardVersion);
    CheckErrorCode(iErrorCode, __LINE__);

    printf("iBoardVersion: 0x%04x\n", iBoardVersion);


    /*--- some init stuff ---------------------------------------*/
    iErrorCode = me1400DIOSetPortDirection(
        iBoardNumber,
        PORTA,
        MEINPUT);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400DIOSetPortDirection(
        iBoardNumber,
        PORTB,
        MEINPUT);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400SetMultifunctionPin(
        iBoardNumber,
        ME1400_MULTIPIN_IRQ);
    CheckErrorCode(iErrorCode, __LINE__);


    /*--- read without IRQ --------------------------------------*/
    printf("\tValue outside ISR: 0x%04X\n", Read());


    /*--- read in ISR--------------------------------------------*/
    iErrorCode = me1400EnableInt(
        iBoardNumber,
        IRQFKT,
        /*iIrqChannel*/ 1);
    CheckErrorCode(iErrorCode, __LINE__);

    printf("Press any key to stop processing.\n");
    while(!kbhit())
    {
        iIrqCount=0;
        Sleep(1000);
        printf("\tValue outside ISR: 0x%04X IrqCnt: %4d\n", Read(), iIrqCount);
    }

    // reset channel 1
    iErrorCode = me1400DisableInt(
        iBoardNumber,
        /*iIrqChannel*/ 1);
    CheckErrorCode(iErrorCode, __LINE__);


    meClose();

    printf ("\n  ***** Press Return to quit *****");
    getchar();
    getch();
    return 0;
}






// Simple interrupt callback function
void _stdcall IRQFKT (void)
{
    printf("<IRQ>\tValue inside ISR: 0x%04X\n", Read());

    iIrqCount++;
    if (iIrqCount==65000)
        iIrqCount = 0;
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
    }
}



// Lesefunktion:
unsigned short Read()
{
    int iLowByte  = 0;
    int iHighByte = 0;
    BOOL bErrorCode;


    bErrorCode = me1400DIGetByte (iBoardNumber, PORTA, &iLowByte);
    bErrorCode = me1400DIGetByte (iBoardNumber, PORTB, &iHighByte);

    return (unsigned short ((iHighByte << 8) | iLowByte));
}
