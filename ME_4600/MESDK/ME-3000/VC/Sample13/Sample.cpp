/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         rt (Ralph Timm)                                                                         */
/*                                                                                                          */
/*  Description:    ME 3000  Analog Input Scan Demo Program                                                 */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    981016  rt      create                                                             */
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
#define MODEPOLARITY AI3000_TRIGGER_TIMER       // set as internal trigger
#define MAXSIZE     1024                        // Max number of entries
#define MAXCOUNT    10                          // Max number of list processings
                                                //  (for this program only)

/*--- Prototypes --------------------------*/
void ErrorHandler (int iErrorCode);             // defines the error handler routine
void GetBoardInformation (int iBoardNumber);    // defines Board information routine


/*--- Define Global Variables -------------*/
int iBoardNumber;           // declare the BoardNumber variable
int iErrorCode;             // declare the data type for the returned error code
int iScanFreq;              // SCAN timer frequency variable
int iChanFreq;              // CHAN timer frequency variable



/*--- Main Program ------------------------*/
void main(void)
{
    int     iScan;                      // SCAN timer
    int     iChan;                      // CHAN timer
    int     iEntry;                     // channel list entry
    int     iChannel;                   // A/D channel number
    int     iRange;                     // input range setting
    int     iMode;                      // single ended or differential
    short   asBuffer[MAXSIZE*MAXCOUNT]; // pointer to array of measured values
    int     iSize;                      // number of channel list entries
    int     iCount;                     // number of times to process the channel list
    int     iOpMode;                    // operating mode (polling or interrupt)
    int     iScanIndex;                 // loop counter indicies
    int     iCountIndex;
    int     iArrayIndex;                // array index couner


    iBoardNumber = 0;       // select board 0
    iScan = 1000;           // SCAN time in Hz
    iChan = 10000;          // CHAN time in HZ

    meOpen();  // calls the initialize function

    GetBoardInformation(iBoardNumber);  // Call Board Information function


    /*  The following order of operations is used:  */
    /*                                              */
    /*      1. set trigger                          */
    /*      2. calculate timer divide factors       */
    /*      3. set timer                            */
    /*      4. clear channel list                   */
    /*      5. make channel list entry              */
    /*      6. add to channel list                  */
    /*      7. call the scan function               */
    /*      8. print out results

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
    /*  using the AddToChannelList function.

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


    iSize = 3;                  // 3 channel list entries
    iCount = 4;                 // number of times to process channel list
    iOpMode = AI3000_POLLING;   // polling mode
    iErrorCode = me3000AIScan(
        iBoardNumber,
        asBuffer,
        iSize,
        iCount,
        iOpMode);
    ErrorHandler (iErrorCode);
*/

ADCHANNEL Channel;
unsigned short Count;
double *Frequency;
bool SoftTrigger;
double *pBuffer;

    unsigned short Chan;
    short i;
    int ListEntry;
    unsigned long DigitalOutput;

    double *doublePtr = pBuffer + Count-1;
    short  *shortPtr  = (short*)(pBuffer) + Count-1;

    DigitalOutput = LastDigitalOutput & ~Multiplexer[Channel][1];
    DigitalOutput = DigitalOutput | Multiplexer[Channel][0];

    if (LastDigitalOutput != DigitalOutput) {
        if (!ME2600DigitalOut(DigitalOutput)) return(1);
//        Sleep(1);     // Delay
    }

 if (Count == 1){
  if (!me2600AISingle(0, static_cast<int>(Multiplexer[Channel][2]),
            AI2600_MINUS_10 | AI2600_DIFFERENTIAL, &i)) return(1);
  *pBuffer = static_cast<double>(i - 2048) * 10.0 / 2048.0;
 }
 else {
        if (SoftTrigger) {
   if (!me2600AISetTrigger(0, AI2600_TRIGGER_TIMER)) return(1);
        }
        else {
   if (!me2600AISetTrigger(0, AI2600_TRIGGER_EXT_LOW)) return(1);
        }

  Chan = static_cast<unsigned short>(me2600FrequencyToCounter(*Frequency));
  if (!me2600AISetTimer(0, 0, Chan)) return(1);
  *Frequency = ADC_BASE_FREQUENCY_1 / static_cast<double>(Chan);

  if (!me2600AIClearChannelList(0)) return(1);

        if (!me2600AIMakeChannelListEntry(static_cast<int>(Multiplexer[Channel][2]),
             AI2600_MINUS_10, AI2600_DIFFERENTIAL, &ListEntry)) return(1);

        if (!me2600AIAddToChannelList(0, ListEntry)) return(1);

  if (!me2600AIMultiple(0, (short*)(pBuffer), Count, AI2600_INTERRUPT)) return(1);

  for (i=0; i<Count; i++)
   *doublePtr-- = (*shortPtr-- - 2048) * 10.0 / 2048.0;
 }




















    /*  Print out the measured results on the screen    */
    iArrayIndex =0;
    for (iCountIndex=0; iCountIndex<iCount; iCountIndex++)
    {
        printf ("Scan %01d \n", iCountIndex);

        for (iScanIndex=0; iScanIndex<iSize; iScanIndex++)
        {
            printf ("Measured value: %04d \n", asBuffer[iArrayIndex]);
            iArrayIndex++;
        }
    }

    meClose();

    printf ("\n  ***** Press Return to quit *****");
    getchar ();
}



/*  This Function reads the Board Information   */
/*  which includes DLL Version, Driver Version, */
/*  serial number, VEC Model and active board   */

void GetBoardInformation (int iBoardNumber)
{
    /*  Define the variables and function data  */
    /*  types used in this function only        */

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
    printf ("-------------------------\n");

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
