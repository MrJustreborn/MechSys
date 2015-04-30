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
void _stdcall IRQFKT (void);




// Please use the manual for the description of the functions
int main (void)
{
    int iErrorCode;
    int iBoardNumber;
    int iBoardVersion;
    int iDLLVersion;
    int iPort;
    int iDirection;
    int iBitNumber;
    int iValue;
    int iIrqChannel;
    int iIrqCnt;
    DEVICEINFOSTRUCT DevInfo;


    meOpen();  // calls the initialize function

    // determine current DLL version
    iDLLVersion = me1400GetDLLVersion ();

    printf(
        "iDLLVersion: Major: 0x%04x Minor: 0x%04x\n",
        (iDLLVersion>>16)& 0xFFFF,
        (iDLLVersion)    & 0xFFFF);

    iBoardNumber=0;
    //for (iBoardNumber=0; iBoardNumber<32; iBoardNumber++)
    {
        /*--- Get general information --------------------*/

        //printf("\nPress any key for next board!\n\n");
        //getch();

        // determine board version
        iErrorCode = me1400GetBoardVersion(
            iBoardNumber,
            &iBoardVersion);

        printf(
            "iBoardVersion: 0x%04x\n",
            iBoardVersion);

        if (
              (iErrorCode != 1)
            ||
              (
                (iBoardVersion != 0x1400)  &&
                (iBoardVersion != 0x1400A) &&
                (iBoardVersion != 0x1400B)
              )
           )
        {
            printf(
                "Board with number %02d don't exist!\n",
                iBoardNumber);

            //break;
            return 0;
        }
        else
        {
            printf(
                "BoardVersion of board %02d is %04X\n",
                iBoardNumber,
                iBoardVersion);


            /*--- Digital Input / Output ---------------------*/

            iPort = 0;          // wich port (0=A; 1=B; 2=C)
            iDirection = 1;     // direction (0=Input; 1=Output)
            iBitNumber = 0;     // Bit number
            iValue = 0x01;      // output value

            iErrorCode = me1400DIOSetPortDirection(
                iBoardNumber,
                iPort,
                iDirection);

            CheckErrorCode(iErrorCode, __LINE__);


            // number of bit is 0 with value 1
            iErrorCode = me1400DOSetBit(
                iBoardNumber,
                iPort,
                iBitNumber,
                iValue);

            CheckErrorCode(iErrorCode, __LINE__);

            printf("iValue of Bit: %1x\n", iValue);



            iValue = 0xFF;      // output value

            // Port B
            iErrorCode = me1400DOSetByte(
                iBoardNumber,
                iPort,
                iValue);
            CheckErrorCode(iErrorCode, __LINE__);

            printf("iValue of Byte: %2x\n", iValue);

            Sleep(1000);

            iErrorCode = me1400DOSetByte(
                iBoardNumber,
                iPort,
                00);
            Sleep(1000);
            iErrorCode = me1400DOSetByte(
                iBoardNumber,
                iPort,
                0xFF);




            iPort = 0;          // Port A
            iDirection = 0;     // Input
            iBitNumber = 0;     // Bit 0

            //  port A is input
            iErrorCode = me1400DIOSetPortDirection(
                iBoardNumber,
                iPort,
                iDirection);

            CheckErrorCode(iErrorCode, __LINE__);


            //  read bit number 0 on port A
            iErrorCode = me1400DIGetBit(
                iBoardNumber,
                iPort,
                iBitNumber,
                &iValue);

            CheckErrorCode(iErrorCode, __LINE__);

            printf("iValue of Bit: %1x\n", iValue);


            //  read byte on port A
            iErrorCode = me1400DIGetByte(
                iBoardNumber,
                iPort,
                &iValue);

            CheckErrorCode(iErrorCode, __LINE__);

            printf("iValue of Byte: %2x\n", iValue);




            /*
            ME1400_TIMERINTERNCLOCK_10MHZ   0x08
            ME1400_TIMERINTERNCLOCK_1MHZ    0x00
            ME1400_TIMERCLOCKSOURCE0_SUBD   0x04
            ME1400_TIMERCLOCKSOURCE0_INTERN 0x00
            ME1400_TIMERCLOCKSOURCE1_SUBD   0x02
            ME1400_TIMERCLOCKSOURCE1_OUT0   0x00
            ME1400_TIMERCLOCKSOURCE2_SUBD   0x01
            ME1400_TIMERCLOCKSOURCE2_OUT1   0x00

            ME1400_MULTIPIN_IRQ             0x00
            ME1400_MULTIPIN_INTERNALCLOCK   0x01
            */

            iErrorCode = me1400InitModeTimerA(
                iBoardNumber,
                ME1400_TIMERINTERNCLOCK_10MHZ |
                ME1400_TIMERCLOCKSOURCE0_SUBD |
                ME1400_TIMERCLOCKSOURCE1_SUBD |
                ME1400_TIMERCLOCKSOURCE2_SUBD);
            CheckErrorCode(iErrorCode, __LINE__);

            iErrorCode = me1400InitModeTimerB(
                iBoardNumber,
                ME1400_TIMERINTERNCLOCK_10MHZ |
                ME1400_TIMERCLOCKSOURCE0_SUBD |
                ME1400_TIMERCLOCKSOURCE1_SUBD |
                ME1400_TIMERCLOCKSOURCE2_SUBD);
            CheckErrorCode(iErrorCode, __LINE__);

            iErrorCode = me1400SetMultifunctionPin(iBoardNumber, ME1400_MULTIPIN_IRQ);
            CheckErrorCode(iErrorCode, __LINE__);


            /*--- Interrupt processing -----------------------*/

            // set channel 1

            iIrqChannel = 1;

            iErrorCode = me1400EnableInt(
                iBoardNumber,
                IRQFKT,
                iIrqChannel);

            CheckErrorCode(iErrorCode, __LINE__);

            printf("Press any key to stop processing.\n");
            while(!kbhit())
            {
                iIrqCount=0;
                Sleep(1000);
                printf("Irq per Second: %4d\n", iIrqCount);
            }

            // reset channel 1
            iErrorCode = me1400DisableInt(
                iBoardNumber,
                iIrqChannel);

            CheckErrorCode(iErrorCode, __LINE__);






            /**/

            iErrorCode = me1400GetIrqCnt(iBoardNumber, &iIrqCnt);
            CheckErrorCode(iErrorCode, __LINE__);
            printf(
                "Number of Interrupts: 0x%04x\n",
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
        }
    }

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
    if (iIrqCount==65000)
        iIrqCount = 0;
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

        // It may be:
        //  * wrong board number: 2072656C
        //  * wrong irq channel : 57    = 87    The parameter is incorrect.     ERROR_INVALID_PARAMETER
        //  *                   : 9B    = 155   Cannot create another thread.   ERROR_TOO_MANY_TCBS
        //  *                   :
    }
}
