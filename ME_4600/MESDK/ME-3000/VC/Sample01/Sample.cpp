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

/*--- ME3000 header files -------*/
#include ".\..\meDefs.h"
//#include ".\..\me3000.h"          // for using with a lib
#include ".\..\DLLInit.h"           // for using with dynamic DLL accessing

/*--- Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEFILE("..\meDefs.h");
USEFILE("..\DLLInit.h");
USEUNIT("..\DLLInit.cpp");
#endif




void main (void)
{
    short wBuffer[1024];
    int iReturn;
    int DLLVersion;
    int iIdx;
    int iScan;
    int iChan;
    int iEntry;
    int iValue;
    int iBoardNumber = 0;       // In the following example all functions
                                // refer to the board with the logical <BoardNumber> "0"

    meOpen();  // calls the initialize function

    // Get DLL Version
    DLLVersion = me3000GetDLLVersion();
    printf("Version of DLL: %08x\n", DLLVersion);

    // Configure port A as output
    iReturn = me3000DIOSetPortDirection(iBoardNumber, PORTA, MEOUTPUT);
    // Basically after every function call an error check by the function
    // me3000ErrorMessage should be done
    if (iReturn == 0)
        me3000ErrorMessage("ME3000-Test");

    //Configure port B as input
    iReturn = me3000DIOSetPortDirection(iBoardNumber, PORTB, MEINPUT);

    //Start A/D conversion by software
    iReturn = me3000AISetTrigger(iBoardNumber, AI3000_TRIGGER_TIMER);

    //Set scan frequency to 1 kHz
    iScan = me3000FrequencyToCounter(1000);

    //Set chan frequency to 10 kHz
    iChan = me3000FrequencyToCounter(10000);

    //Programming timer
    iReturn = me3000AISetTimer(iBoardNumber, iScan, iChan);

    //Clear channel list FIFO completely
    iReturn = me3000AIClearChannelList(iBoardNumber);

    //Generate channel list with 10 entries
    //Channels 1 to 10 will be sampled
    for (iIdx=1; iIdx<=10; iIdx++)
    {
        //Generate channel list entry
        iReturn = me3000AIMakeChannelListEntry(iIdx, AI3000_PLUS_10, AI3000_SINGLE_ENDED, &iEntry);
        //Write channel list entry to channel list FIFO
        iReturn = me3000AIAddToChannelList(iBoardNumber, iEntry);
    }

    //Settings for D/A conversion: D/A channel number: 2, output level
    //range: 0-10V, buffered output
    iReturn = me3000AOSetMode(iBoardNumber, 2, AO3000_PLUS_10, AO3000_BUFFERED);

    //Write output value 0xFFF (=10V) to D/A converter
    iReturn = me3000AOSingle(iBoardNumber, 2, 0xFFF);

    //Now you can run e. g. the following operations in any order:
    //Set bit no. 8 of port A to high level
    iReturn = me3000DOSetBit(iBoardNumber, PORTA, 8, 1);

    //Read the lower byte of port B
    iReturn = me3000DIGetByte(iBoardNumber, PORTB, LOW_BYTE, &iValue);

    //Process the channel list with 10 entries two times. Values are
    //written to the array <Buffer> and fetched after interrupt
    iReturn = me3000AIScan(iBoardNumber, wBuffer, 10, 2, AI3000_INTERRUPT);

    //Update all D/A channels simultaneously
    iReturn = me3000AOUpdate(iBoardNumber);

    meClose();

    printf ("\n  ***** Press Return to quit *****");
    getchar ();
}