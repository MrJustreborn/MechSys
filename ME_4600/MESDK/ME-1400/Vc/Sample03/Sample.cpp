/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to Ralph Timm for the function wrapper                                   */
/*                                                                                                          */
/*  Description:    Using interrupts without a Interrupt Service Routine                                    */
/*                  You can not use a ISR in HP-Vee or LabVIEW,                                             */
/*                  so it needs a special adaption for this.                                                */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    980706  ab     create                                                           */
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


//prototypes:
void CheckErrorCode(int iErrorCode, int iLine);

// Please use the manual for the description of the functions
int main (void)
{
    int iErrorCode;
    int iBoardVersion;
    int iIrqCntBefore;
    int iIrqCntAfter;


    meOpen();  // calls the initialize function

    /*--- Get general information --------------------*/

    iErrorCode = me1400GetBoardVersion(
        0,                  // iBoardNumber
        &iBoardVersion);
    CheckErrorCode(iErrorCode, __LINE__);

    printf(
        "BoardVersion is %04X\n",
        iBoardVersion);

    if ((iBoardVersion != 0x1400A) && (iBoardVersion != 0x1400B))
    {
        return 0;
    }


    /*--- Interrupt processing -----------------------*/

    // set interrupt input (pin 39, ground 20)
    iErrorCode = me1400SetMultifunctionPin(
        0,                      // iBoardNumber
        ME1400_MULTIPIN_IRQ);
    CheckErrorCode(iErrorCode, __LINE__);

    // set channel 1
    iErrorCode = me1400EnableInt(
        0,      // iBoardNumber
        0,      // IRQFKT
        1);     // iIrqChannel
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400GetIrqCnt(
        0,      // iBoardNumber,
        &iIrqCntBefore);
    CheckErrorCode(iErrorCode, __LINE__);
    printf(
        "\nNumber of Interrupts befor: %d\n",
        iIrqCntBefore);

    // wait for interrupts
    Sleep(1000);

    iErrorCode = me1400GetIrqCnt(
        0,          // iBoardNumber
        &iIrqCntAfter);
    CheckErrorCode(iErrorCode, __LINE__);
    printf(
        "\nNumber of Interrupts after: %d\n",
        iIrqCntAfter);

    printf(
        "\nNumber of Interrupts between: %d\n",
        iIrqCntAfter-iIrqCntBefore);

    // reset channel 1
    iErrorCode = me1400DisableInt(
        0,      // iBoardNumber
        1);     // iIrqChannel
    CheckErrorCode(iErrorCode, __LINE__);




    /*--- Get general information --------------------*/
    // using a array, not a struct

    int DevInfo[20];
    /*
    0:  dwBoardNumber;          // Board number of Board
    1:  dwVendorID;             // PCI vendor ID
    2:  dwDeviceID;             // PCI device ID
    3:  dwSystemSlotNumber;     // Slot number in PCI bus
    4:  dwPortBase;             // base port address
    5:  dwPortCount;            // Count of I/O addresses used.
    6:  dwIntChannel;           // first Interrupt Channel
    7:  dwPortBasePLX;          // base port address
    8:  dwPortCountPLX;         // Count of I/O addresses used.
    9: dwSerialNumber;         // Serial number of the board
    10: dwBusNumber;            // Bus number of the PCI bus (in most cases 0)
    11: dwHWRevision;           // hardware revision of board
    12: dwIrqCnt;               // number of interrupts
    13: dwVersion;              // which board of the board family
    */


    iErrorCode = me1400GetDevInfo(
        0,      // iBoardNumber,
        (PDEVICEINFOSTRUCT)&DevInfo[0]);
    CheckErrorCode(iErrorCode, __LINE__);
    if (iErrorCode)
    {
        printf("\nTechnical Values:\n");
        printf("Vendor ID: 0x%04x\n", DevInfo[1]);
        printf("Device ID: 0x%04x\n", DevInfo[2]);
        printf("IOPortBase:0x%04x\n", DevInfo[5]);
        printf("IOPortPLX: 0x%04x\n", DevInfo[8]);
        printf("IrqLine:   0x%04x\n", DevInfo[7]);
        printf("SerialNo:  0x%04x\n", DevInfo[10]);
    }

    /*--- End of test --------------------------------*/
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

        getch();
        exit(1);
    }
}
