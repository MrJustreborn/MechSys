/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to Ralph Timm for the function wrapper                                   */
/*                                                                                                          */
/*  Description:    Example for WrapAround (only in ME-VEC 2 and 3)                                         */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    980901  ab      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/


/*--- system header files -------*/
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

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



#define FIFOSIZE    (4 * 1024)
#define BOARDNO     (0)
#define PERIOD      (0x100)         // (No. of dots per curve)

void ErrorHandler(int);



void main (void)
{
    int iReturn;

    meOpen();  // calls the initialize function

    /*--- Get DLL Version ---*/
    {
        int DLLVersion;

        DLLVersion = me3000GetDLLVersion();
        printf("Version of DLL: %08x\n", DLLVersion);
    }


    /*--- Prepare the DAC ---*/
    {
        int iTime;
        int iEntry;
        int iValue;
        int iChanNo;
        int iSampleNo = 0;
        int iIdx;
        double pi = 3.1415926535;

        iReturn = me3000AOSetTrigger(BOARDNO, AO3000_TRIGGER_TIMER);
        if (iReturn == 0)  ErrorHandler(1);

        iTime = me3000FrequencyToCounter(100000);    // (100 kHz)
        iReturn = me3000AOSetTimer(BOARDNO, iTime);
        if (iReturn == 0)  ErrorHandler(2);

        iReturn = me3000AOClearDACFIFO(BOARDNO);
        if (iReturn == 0)  ErrorHandler(3);

        /* Set the FIFO */
        printf("\nPress any key to write the FIFO and start the generator!\n\n");
        getch();

        for (iIdx=0;  (iSampleNo<PERIOD) && (iIdx<FIFOSIZE);  iIdx++)
        {
            iChanNo   = iIdx % 4;
            iSampleNo = iIdx / 4;

            switch(iChanNo)
            {
                case 0:
                    printf("\n#%04d:\t\t",iSampleNo);
                    Sleep(10);

                    if (iSampleNo > (PERIOD/2))
                        iValue  = 0xFFF;
                    else
                        iValue  = 0x000;
                    break;

                case 1:
                    iValue = (0xFFF/PERIOD) * (iSampleNo % PERIOD);
                    break;

                case 2:
                    iValue = 0xFFF - (0xFFF/PERIOD) * (iSampleNo % PERIOD);
                    break;

                case 3:
                    iValue = (int) ((double)0xFFF * (sin(((double)(iSampleNo))/PERIOD * 2 * pi)+1)/2);
                    break;
            }

            iEntry = ((iChanNo<<12) + (iValue & (int)0xFFF));
            printf("%04x\t", iEntry);

            iReturn = me3000AOAddToDACFIFO(BOARDNO, iEntry);
            if (iReturn == 0)  ErrorHandler(4);
        }

        iReturn = me3000AOSetMode(BOARDNO, 0, AO3000_PLUS_10, 1);
        if (iReturn == 0)  ErrorHandler(5);
    }


    /*--- Start -------------*/
    iReturn = me3000AOWrapAround(BOARDNO);
    if (iReturn == 0)  ErrorHandler(6);


    /*--- Wait --------------*/
    printf("\n\n\n");
    printf("Channel A on pin 15: waveform is square\n");
    printf("Channel B on pin 34: waveform is ramp\n");
    printf("Channel C on pin 14: waveform is inverted ramp\n");
    printf("Channel D on pin 33: waveform is sine\n\n");
    printf("Please note that you connect the corresponding sense lines!\n\n");
    printf("Press any key to stop the generator!\n");
    while(!kbhit());


    /*--- Stop --------------*/
    me3000AOStop(BOARDNO);

    meClose();

    printf ("\n  ***** Press Return to quit *****");
    getchar ();
}



void ErrorHandler(int iLine)
{
    printf("Error in file sample3.c (Errorcode = %04d)\n", iLine);
}