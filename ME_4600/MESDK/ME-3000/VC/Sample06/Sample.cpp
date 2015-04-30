/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         rt (Ralph Timm)                                                                         */
/*                                                                                                          */
/*  Description:    ME 3000  Analog Input Scan Demo Program, using the Background Function                  */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                  This program explicitly defines all board settings for demonstration purposes.          */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    981016  rt      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/

/*      This Program uses dynamic function calls    */
/*      and Wrappers for all the ME3000 functions   */
/*
/*      All Function names can be used exactly as   */
/*      they are described in the ME3000 handbook   */

/*      Notes:

        1.  The header file "Typedefs.h" must be included along
            with the other standard header files required by the
            me3000 ("meDefs.h").

        2.  The source code file "DLLInit.cpp" must be included
            in the project.  This file contains the "meOpen" and
            "meClose" functions which must be called from the
            main program.  The "meOpen" function opens the library
            and gets the address of all the DLL functions.  The "meClose"
            function simply closes the library at the end of the program.

        3.  The source code file "DLLInit" also has all of the "Wrapper"
            functions.  This allows the user to use the full and proper
            function names when calling them from the main program.


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

/*--- General defines ---------------------*/
#define MODEPOLARITY AI3000_TRIGGER_TIMER       // set as internal trigger
#define MAXSIZE     1024                        // Max number of entries
#define MAXCOUNT    10                          // Max number of list processings
                                                //  (for this program only)

/*--- Prototypes --------------------------*/
void ErrorHandler (int iErrorCode);             // defines the error handler routine
void GetBoardInformation (int iBoardNumber);    // defines Board information routine
//typedef void (_stdcall *P_1_PROC)    (short*, int);
void _stdcall CallBackFct (short* , int );      // user defined callback routine

/*--- Define Global Variables -------------*/
int iErrorCode;                 // declare the data type for the returned error code
int iBoardNumber;               // declare the BoardNumber variable
int iScanFreq;                  // SCAN timer frequency variable
int iChanFreq;                  // CHAN timer frequency variable
BOOL gbBreak;                   // break variable

int   iLoopCount;               // loop counter for callback function
int   iSize;                    // number of channel list entries
int   iCount;                   // number of times to process the channel list
int   iLoops;                   // number of loops for background function


void main(void)
{
    int     iScan;                      // SCAN timer
    int     iChan;                      // CHAN timer
    int     iEntry;                     // channel list entry
    int     iChannel;                   // A/D channel number
    int     iRange;                     // input range setting
    int     iMode;                      // single ended or differential
    short   asBuffer[MAXSIZE*MAXCOUNT]; // pointer to array of measured value
    int     iOpMode;                    // operating mode (polling or interrupt)
    int     iDelay;                     // delay time (in ms) between loops


    iBoardNumber = 0;      // select board 0
    iScan = 1000;           // SCAN time in Hz
    iChan = 10000;          // CHAN time in Hz

    meOpen();  // calls the initialize function

    GetBoardInformation (iBoardNumber);    // Call Board Information function

    /*  The following order of operations is used:  */
    /*                                              */
    /*      1. set trigger                          */
    /*      2. calculate timer divide factors       */
    /*      3. set timer                            */
    /*      4. clear channel list                   */
    /*      5. make channel list entry              */
    /*      6. add to channel list                  */
    /*      7. call the scan background function    */
    /*      8. on return execute callback fucntion  */
    /*         which prints the measured values     */
    /*         the defined number of times          */

    iErrorCode = me3000AISetTrigger (iBoardNumber, MODEPOLARITY);
    ErrorHandler (iErrorCode);

    iScanFreq = me3000FrequencyToCounter (iScan);
    iChanFreq = me3000FrequencyToCounter (iChan);

    iErrorCode = me3000AISetTimer (iBoardNumber, iScanFreq, iChanFreq);
    ErrorHandler (iErrorCode);

    iErrorCode = me3000AIClearChannelList (iBoardNumber);
    ErrorHandler (iErrorCode);

    /*  The channel list entries are explicitly defined     */
    /*  and are intended for demonstration purposes only.   */
    /*  There are 3 channel list entries.  Each is          */
    /*  separately prepared using the MakeChannelListEntry  */
    /*  function and written into the channel list FIFO     */
    /*  using the AddToChannelList function.                */

    iChannel = 0;               // channel 0, +/-10Volts, single ended
    iRange = AI3000_MINUS_10;
    iMode = AI3000_SINGLE_ENDED;
    iErrorCode = me3000AIMakeChannelListEntry (iChannel, iRange,
                                                    iMode, &iEntry);
    ErrorHandler (iErrorCode);

    iErrorCode = me3000AIAddToChannelList (iBoardNumber, iEntry);
    ErrorHandler (iErrorCode);

    iChannel = 1;               // channel 1, +/-5Volts, single ended
    iRange = AI3000_MINUS_5;
    iErrorCode = me3000AIMakeChannelListEntry (iChannel, iRange,
                                                    iMode, &iEntry);
    ErrorHandler (iErrorCode);

    iErrorCode = me3000AIAddToChannelList (iBoardNumber, iEntry);
    ErrorHandler (iErrorCode);

    iChannel = 0;               // channel 0, 0...10Volts, single ended
    iRange = AI3000_PLUS_10;
    iErrorCode = me3000AIMakeChannelListEntry (iChannel, iRange,
                                                    iMode, &iEntry);
    ErrorHandler (iErrorCode);

    iErrorCode = me3000AIAddToChannelList (iBoardNumber, iEntry);
    ErrorHandler (iErrorCode);

    printf ("Press key to start scanning\n");
    getch();                    // scanning starts when a key is pressed

    iSize = 3;                  // number of channel list entries
    iCount = 4;                 // number of times to process channel list
    iOpMode = AI3000_POLLING;   // polling mode is chosen
    iLoops = 5;                 // number of loops
    iDelay = 300;               // delay between scans (in ms)
    iLoopCount = 1;             // initialize loop counter
    iErrorCode = me3000AIScanEx(
        iBoardNumber,
        asBuffer,
        iSize,
        iCount,
        iOpMode,
        iLoops,
        iDelay,
        CallBackFct);

    ErrorHandler (iErrorCode);

    while(_kbhit()) getch();                            // get old characters
    while((gbBreak != TRUE) && (!_kbhit()));            // end if done or key pressed

    printf ("\nScanning Complete..... Press key to continue\n");  // end message
    getch ();

    iErrorCode = me3000AIStop (iBoardNumber);         // stop scanning and end program
    ErrorHandler (iErrorCode);

    meClose();

    printf ("\n  ***** Press Return to quit *****");
    getchar ();
}


/*  This Function reads the Board Information   */
/*  which includes DLL Version, Driver Version, */
/*  serial number, VEC Model and active board   */
void GetBoardInformation (int iBoardNumber)
{
    int iDLLVersion;     // declare data type for DLLVersion function
    char bBuffer [100];     // "buffer" points to an array of charactors
    int iSerialNumber;      // declare the data type for  SerialNumber
    int iMEVECModel;        // declare the data type for MEVECModel

    iDLLVersion = me3000GetDLLVersion ();

    iErrorCode = me3000GetDriverVersion (bBuffer);
    ErrorHandler (iErrorCode);                     // check if an error occurred

    iErrorCode = me3000GetSerialNumber (iBoardNumber, &iSerialNumber);
    ErrorHandler (iErrorCode);

    iErrorCode = me3000GetVECModel (iBoardNumber, &iMEVECModel);
    ErrorHandler (iErrorCode);                                     // check for error

    /*  Print an Introductory Message  */
    printf ("Current Board Information\n");
    printf ("-------------------------\n");

    /*  Print out the Board Information   */
    printf ("Active board #: %01d \n", iBoardNumber);  // active board number
    printf ("Version of DLL: %08x\n", iDLLVersion);    // DLL version
    printf ("Version of Driver: %s \n" , bBuffer);      // Driver version
    printf ("Serial Number: %02x \n", iSerialNumber);   // Serial Number
    printf ("ME VEC Model:  %x \n", iMEVECModel);       // ME VEC Model
    printf ("\n");
}


/*  This is the error Handler Routine   */
/*  If a DLL function call returns a    */
/*  "1", an error occurs and this       */
/*  Routine is executed.                */
void ErrorHandler (int iErrorCode)
{
    if (iErrorCode != 1)
    {
        printf("*** Error Ocurred ***\n");
        me3000ErrorMessage("Error:  ");
    }
}


/*     User Defined Callback Routine        */
/*                                          */
/*   This routine is executed when the      */
/*   defined number of scans is completed.  */
/*   It initializes the variables, prints   */
/*   a message, prints the measured values, */
/*   checks for the end condition and then  */
/*   returns control to the main program    */

void _stdcall CallBackFct (short *psBuffer, int iCount2)
{
    int iCountIndex;
    int iScanIndex;
    int iArrayIndex = 0;
    int iSize = 3;          // number of channel list entries
    int iCount = 4;         // number of times to process channel list


    printf("\n             *** User Defined Callback Function ***\n");

    for (iCountIndex=0; iCountIndex<iCount; iCountIndex++)
    {
        printf ("Scan %01d \n", iCountIndex);

        for (iScanIndex=0; iScanIndex<iSize; iScanIndex++)
        {
            printf ("Measured value: %04d \n", psBuffer[iArrayIndex]);
            iArrayIndex++;
        }

    }

    if (iLoopCount == iLoops)
    {
        gbBreak = TRUE;
    }
    iLoopCount++;
}