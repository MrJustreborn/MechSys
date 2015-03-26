/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau), rt (Ralph Timm)                                                    */
/*                                                                                                          */
/*  Description:    Simple example for testing the counter for the ME 3000 (only in ME-VEC 1 and 3)         */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  1. The proper hardware connections must be made before the program will function.       */
/*                     See handbook.                                                                        */
/*                  2. Choosing counter A or B is done by changing the define statement for "COUNTER"       */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    981001  ab/rt   create                                                          */
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

/*--- General defines ---------------------*/
#define MAXCNT  0x100               // constant for number of counter values to read
#define COUNTER COUNTER3000_B       // constant for selecting Counter A or Counter B

/*--- Prototypes --------------------------*/
void ErrorHandler (int iErrorCode);          // defines the error handler routine
void GetBoardInformation (int iBoardNumber); // defines Board information routine

/*--- Define Global Variables -------------*/
int iErrorCode;                  // declare the data type for the returned error code
int iBoardNumber;                // declare the BoardNumber variable
short sCounterValue;                // declare the CounterValue pointer variable
short sCounterArray[0xFFFF];        // declare the Counter Array variable



/*--- Main Program ------------------------*/
void main(void)
{
    int iStartValue;            // declare the variable to select startíng counter value
    int iEndValue;              // declare the variable to select ending counter value
    register int iIdx;          // declare the register array index variable
    int iDelay;                 // declare the delay variable


    iBoardNumber = 0;          // select board 0
    iStartValue = 0x0020;       // set start value for selected counter
    iEndValue   = 0x0025;       // set end value for selected counter

    meOpen();  // calls the initialize function

    GetBoardInformation (iBoardNumber);

    iErrorCode = me3000CNTReset (iBoardNumber, COUNTER);      // reset counter

    iErrorCode = me3000CNTStart (iBoardNumber, COUNTER);      // enable the counter

    iErrorCode = me3000CNTSetRange (iBoardNumber, COUNTER,    // load start/end values
                                     iEndValue, iStartValue);

    //iErrorCode = me3000CNTRead (iBoardNumber, COUNTER,
    //                                      &sCounterValue);

    for (iIdx=0; iIdx<MAXCNT; iIdx++)
    {
        iErrorCode = me3000CNTRead (iBoardNumber, COUNTER,    // read contents
                                    &(sCounterArray [iIdx]));   // of the counter

        for (iDelay=0; iDelay<0x4FF; iDelay++);                 // Delay
    }

    printf("Press any key to show the values !\n");             // loop to print contents of
    for (iIdx=0; iIdx<MAXCNT; iIdx++)                           // array of counter values
    {
        if ((iIdx % 0x0F) == 0)
        {
            printf("----------------------------------\n");     // format output
            getch();
        }

        printf("CounterValue: 0x%04x\n", sCounterArray [iIdx]); // print array
    }

    meClose();

    printf ("\n  ***** Press Return to quit *****");
    getchar ();
}



/*  This Function reads the Board Information   */
/*  which includes DLL Version, Driver Version, */
/*  serial number, VEC Model and active board.  */

void GetBoardInformation (int iBoardNumber)
{
    int iDLLVersion;     // declare data type for DLLVersion function
    char bBuffer [100];     // "buffer" points to an array of charactors
    int iSerialNumber;      // declare the data type for  SerialNumber
    int iMEVECModel;        // declare the data type for MEVECModel


    iDLLVersion = me3000GetDLLVersion ();          // function call (no parameters)

    iErrorCode = me3000GetDriverVersion (bBuffer); // function call
    ErrorHandler (iErrorCode);                     // check if an error occurred

    iErrorCode = me3000GetSerialNumber (iBoardNumber, &iSerialNumber);
    ErrorHandler (iErrorCode);

    iErrorCode = me3000GetVECModel (iBoardNumber, &iMEVECModel);  // function call
    ErrorHandler (iErrorCode);                                     // check for error

    /*  Print an Introductory Message  */
    printf ("Current Board Information\n");
    printf ("\n");

    /*  Print out the Board Information   */
    printf ("Active board #: %01d \n", iBoardNumber);  // active board number
    printf ("Version of DLL: %08x\n", iDLLVersion);    // print DLL version
    printf ("Version of Driver: %s \n" , bBuffer);      // print Driver version
    printf ("Serial Number: %02x \n", iSerialNumber);   // Print Serial Number
    printf ("ME VEC Model:  %x \n", iMEVECModel);       // Print ME VEC Model
    printf ("\n");                                      // blank line

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
        me3000ErrorMessage("Error     :");
    }
}