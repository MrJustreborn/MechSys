/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to Ralph Timm for the function wrapper                                   */
/*                                                                                                          */
/*  Description:    General Example II                                                                      */
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
void _stdcall IRQFKT (void);



// Please use the manual for the description of the functions
int main (void)
{
    int iErrorCode;
    int iBoardNumber;
    int iBoardVersion;
    int iDLLVersion;
    int iBitNumber;
    int iValue;
    int iIrqChannel;
    int iIrqCnt;
    DEVICEINFOSTRUCT DevInfo;


    meOpen();  // calls the initialize function

    /*--- Get general information --------------------*/

    // determine current DLL version
    iDLLVersion = me1400GetDLLVersion ();

    printf(
        "iDLLVersion: Major: 0x%04x Minor: 0x%04x\n",
        (iDLLVersion>>16)& 0xFFFF,
        (iDLLVersion)    & 0xFFFF);

    // determine board typ
    iBoardNumber=0;                 // for the rest of the program

    iErrorCode = me1400GetBoardVersion(
        iBoardNumber,
        &iBoardVersion);
    CheckErrorCode(iErrorCode, __LINE__);

    printf(
        "BoardVersion is %04X\n",
        iBoardVersion);

    if (
        (iBoardVersion != 0x1400 ) &&
        (iBoardVersion != 0x1400A) &&
        (iBoardVersion != 0x1400B)
       )
    {
        printf("Error no board found!\n");
        return 1;
    }


    /*--- Digital Bit Input / Output -----------------*/

    iBitNumber  = 0;
    iValue      = 0x01;

    // Port A:
    iErrorCode = me1400DIOSetPortDirection(
        iBoardNumber,
        PORTA,
        MEOUTPUT);
    CheckErrorCode(iErrorCode, __LINE__);
    iErrorCode = me1400DOSetBit(
        iBoardNumber,
        PORTA,
        iBitNumber,
        iValue);
    CheckErrorCode(iErrorCode, __LINE__);

    // Port B:
    iErrorCode = me1400DIOSetPortDirection(
        iBoardNumber,
        PORTB,
        MEINPUT);
    CheckErrorCode(iErrorCode, __LINE__);
    iErrorCode = me1400DIGetBit(
        iBoardNumber,
        PORTB,
        iBitNumber,
        &iValue);
    CheckErrorCode(iErrorCode, __LINE__);
    printf(
        "Bit value is %x\n",
        iValue);



    /*--- Digital Byte Input / Output ------------------*/

    // Port C:
    iErrorCode = me1400DIOSetPortDirection(
        iBoardNumber,
        PORTC,
        MEOUTPUT);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400DOSetByte(
        iBoardNumber,
        PORTC,
        0x39);
    CheckErrorCode(iErrorCode, __LINE__);


    /*--- The following part is only for 1400A or 1400B ---*/

    if ((iBoardVersion != 0x1400A) && (iBoardVersion != 0x1400B))
    {
        return 0;
    }

    /*--- Set Timer ------------------*/

    /*
    ME1400_TIMERINTERNCLOCK_10MHZ   OR  ME1400_TIMERINTERNCLOCK_1MHZ
    ME1400_TIMERCLOCKSOURCE0_SUBD   OR  ME1400_TIMERCLOCKSOURCE0_INTERN
    ME1400_TIMERCLOCKSOURCE1_SUBD   OR  ME1400_TIMERCLOCKSOURCE1_OUT0
    ME1400_TIMERCLOCKSOURCE2_SUBD   OR  ME1400_TIMERCLOCKSOURCE2_OUT1

    ME1400_MULTIPIN_IRQ             OR  ME1400_MULTIPIN_INTERNALCLOCK
    */

    iErrorCode = me1400InitModeTimerA(
        iBoardNumber,
        ME1400_TIMERINTERNCLOCK_1MHZ |
        ME1400_TIMERCLOCKSOURCE0_INTERN |
        ME1400_TIMERCLOCKSOURCE1_OUT0 |
        ME1400_TIMERCLOCKSOURCE2_OUT1);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400CntWrite(
        iBoardNumber,
        0,      // Counter 0 (0..2)
        3,      // Modus
        1000);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400CntWrite(
        iBoardNumber,
        1,      // Counter 0 (0..2)
        3,      // Modus
        1000);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400CntWrite(
        iBoardNumber,
        2,      // Counter 0 (0..2)
        3,      // Modus
        10);
    CheckErrorCode(iErrorCode, __LINE__);

    /*--- Interrupt processing -----------------------*/

    // set interrupt input
    iErrorCode = me1400SetMultifunctionPin(
        iBoardNumber,
        ME1400_MULTIPIN_IRQ);
    CheckErrorCode(iErrorCode, __LINE__);

    // set channel 1
    iIrqChannel = 1;
    iErrorCode = me1400EnableInt(
        iBoardNumber,
        IRQFKT,
        iIrqChannel);
    CheckErrorCode(iErrorCode, __LINE__);

    //Reset Counters
    iErrorCode = me1400GetIrqCnt(iBoardNumber, &iIrqCnt);
    CheckErrorCode(iErrorCode, __LINE__);
    printf(
        "\nNumber of Interrupts befor: %d\n",
        iIrqCnt);
    iIrqCount = 0;

    // wait for interrupts
    Sleep(1000);

    //Reset Counters
    iErrorCode = me1400GetIrqCnt(iBoardNumber, &iIrqCnt);
    CheckErrorCode(iErrorCode, __LINE__);
    printf(
        "\nNumber of Interrupts after: %d\n",
        iIrqCnt);

    // reset channel 1
    iErrorCode = me1400DisableInt(
        iBoardNumber,
        iIrqChannel);
    CheckErrorCode(iErrorCode, __LINE__);

    printf("Number of interrupts: %d\n",iIrqCount);



    /*--- The following part is only for 1400A or 1400B ---*/

    if (iBoardVersion != 0x1400B)
    {
        return 0;
    }


    /*--- Digital Byte Input / Output ------------------*/

    // Port D:
    iErrorCode = me1400DIOSetPortDirection(
        iBoardNumber,
        PORTD,
        MEOUTPUT);
    CheckErrorCode(iErrorCode, __LINE__);
    iErrorCode = me1400DOSetByte(
        iBoardNumber,
        PORTD,
        0xAA);
    CheckErrorCode(iErrorCode, __LINE__);

    Sleep(1000);

    // Set the same port again
    iErrorCode = me1400DOSetByte(
        iBoardNumber,
        PORTD,
        0x55);
    CheckErrorCode(iErrorCode, __LINE__);


    // Port E:
    iErrorCode = me1400DIOSetPortDirection(
        iBoardNumber,
        PORTE,
        MEOUTPUT);
    CheckErrorCode(iErrorCode, __LINE__);
    iErrorCode = me1400DOSetByte(
        iBoardNumber,
        PORTE,
        0xF0);
    CheckErrorCode(iErrorCode, __LINE__);



    // Port F:
    iErrorCode = me1400DIOSetPortDirection(
        iBoardNumber,
        PORTF,
        MEINPUT);
    CheckErrorCode(iErrorCode, __LINE__);
    iErrorCode = me1400DIGetByte(
        iBoardNumber,
        PORTF,
        &iValue);
    CheckErrorCode(iErrorCode, __LINE__);
    printf("Value of Byte: 0x%x\n", iValue);


    // Port F:
    // You can read the set port back:
    iErrorCode = me1400DIOSetPortDirection(
        iBoardNumber,
        PORTF,
        MEOUTPUT);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400DOSetByte(
        iBoardNumber,
        PORTF,
        0x32);
    CheckErrorCode(iErrorCode, __LINE__);

    // no me1400DIOSetPortDirection here
    // note: the port is an output
    // don't use it as an input here
    iErrorCode = me1400DIGetByte(
        iBoardNumber,
        PORTF,
        &iValue);
    CheckErrorCode(iErrorCode, __LINE__);

    printf("Value = %x\n", iValue);



    /*--- Set Timer ------------------*/

    iErrorCode = me1400InitModeTimerB(
        iBoardNumber,
        ME1400_TIMERINTERNCLOCK_10MHZ |
        ME1400_TIMERCLOCKSOURCE0_INTERN |
        ME1400_TIMERCLOCKSOURCE1_OUT0 |
        ME1400_TIMERCLOCKSOURCE2_SUBD);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400CntWrite(
        iBoardNumber,
        3,      // Counter 0 (3..5 for B)
        3,      // Modus
        1000);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400CntWrite(
        iBoardNumber,
        4,      // Counter 0 (3..5)
        3,      // Modus
        1000);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400CntWrite(
        iBoardNumber,
        5,      // Counter 0 (3..5)
        3,      // Modus
        10);
    CheckErrorCode(iErrorCode, __LINE__);


    /*--- Get number of interrupts from driver since it started ---*/
    iErrorCode = me1400GetIrqCnt(iBoardNumber, &iIrqCnt);
    CheckErrorCode(iErrorCode, __LINE__);
    printf(
        "Number of Interrupts: %d\n",
        iIrqCnt);

    iErrorCode = me1400GetDevInfo(iBoardNumber, &DevInfo);
    CheckErrorCode(iErrorCode, __LINE__);
    if (iErrorCode)
    {
        printf("\nTechnical Values:\n");
        printf("Vendor ID: 0x%04x\n", DevInfo.dwVendorID);
        printf("Device ID: 0x%04x\n", DevInfo.dwDeviceID);
        printf("IOPortBase:0x%04x\n", DevInfo.dwPortBase);
        printf("IOPortPLX: 0x%04x\n", DevInfo.dwPortBasePLX);
        printf("IrqLine:   0x%04x\n", DevInfo.dwIntChannel);
        printf("SerialNo:  0x%04x\n", DevInfo.dwSerialNumber);
    }


   /*--- End of test --------------------------------*/
    meClose();

    printf ("\n  ***** Press Return to quit *****");
    getchar();
    getch();

    return 0;
}






// Simple interrupt callback function
void _stdcall IRQFKT (void)
{
    iIrqCount++;
    //if (iIrqCount==65000)
    //  iIrqCount = 0;
    printf("<IRQ>");
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

        getch();
        exit(1);
    }
}
