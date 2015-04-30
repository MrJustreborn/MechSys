/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to Ralph Timm for the function wrapper                                   */
/*                                                                                                          */
/*  Description:    Example for WriteToDisk                                                                 */
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


void ErrorHandler(int);


void main (void)
{
    short sBuffer[1024];
    int iReturn;

    meOpen();  // calls the initialize function

    /*--- Get DLL Version ---*/
    {
        int DLLVersion;

        DLLVersion = me3000GetDLLVersion();
        printf("Version of DLL: %08x\n", DLLVersion);
    }

    /*--- Prepare the ADC ---*/
    {
        int iScan;
        int iChan;
        int iEntry;

        iReturn = me3000AISetTrigger(0,AI3000_TRIGGER_TIMER);
        if (iReturn == 0)  ErrorHandler(__LINE__);

        iScan = me3000FrequencyToCounter(1000);
        iChan = me3000FrequencyToCounter(10000);
        iReturn = me3000AISetTimer(0,iScan,iChan);
        if (iReturn == 0)  ErrorHandler(__LINE__);

        iReturn = me3000AIClearChannelList(0);
        if (iReturn == 0)  ErrorHandler(__LINE__);


        // Kanal 0
        iReturn = me3000AIMakeChannelListEntry(0, AI3000_MINUS_10, AI3000_SINGLE_ENDED, &iEntry);
        if (iReturn == 0)  ErrorHandler(__LINE__);

        iReturn = me3000AIAddToChannelList(0, iEntry);
        if (iReturn == 0)  ErrorHandler(__LINE__);

        // Kanal 1
        iReturn = me3000AIMakeChannelListEntry(1, AI3000_MINUS_10, AI3000_SINGLE_ENDED, &iEntry);
        if (iReturn == 0)  ErrorHandler(__LINE__);

        iReturn = me3000AIAddToChannelList(0, iEntry);
        if (iReturn == 0)  ErrorHandler(__LINE__);

        iReturn = me3000FileName(0,0,"c:\\metest.dat");
        if (iReturn == 0)  ErrorHandler(__LINE__);
    }


    /*--- ADC ---------------*/
    iReturn = me3000AIScan(0, sBuffer, 2, 2, AI3000_INTERRUPT | AI3000_SCAN_TO_DISK);
    if (iReturn == 0)  ErrorHandler(__LINE__);


    /*--- Read the file -----*/
    // The file may be bigger than expected (The driver saves the whole FIFO).
    // The information is saved in the following format:
    //  1. value of 0. channel,
    //  1. value of 1. channel,
    //  2. value of 0. channel,
    //  2. value of 1. channel,
    {
        FILE *fp;
        short sVal;
        int iCnt = 0;

        fp = fopen("c:\\metest.dat", "rb");
        while (fread(&sVal, sizeof(short), 1, fp))
        {
            if ((iCnt%2)==0)
            {
                //getch();
                printf("\n %04d\t",iCnt);
            }
            iCnt++;
            printf("%03x\t",sVal);
        }
        printf("\n");
        fclose(fp);
    }

    meClose();

    printf ("\n  ***** Press Return to quit *****");
    getchar ();
}


void ErrorHandler(int iLine)
{
    printf("Error in file %s in line: %04d\n", __FILE__, iLine);
    exit(0);
}
