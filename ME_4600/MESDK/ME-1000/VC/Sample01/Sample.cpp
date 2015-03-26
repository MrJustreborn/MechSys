/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       Visual C++ 6.0                                                                          */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                                                                                                          */
/*  Description:    General Example for the board ME-1000                                                   */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    001013  ab      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/


#include <windows.h>
#include <conio.h>
#include <stdio.h>

/* Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEUNIT("..\meDefs.h");
USEUNIT("..\DLLInit.h");
#endif

#include "..\medefs.h"
//#include ".\..\me1000.h"      // for static access with a lib file
#include ".\..\DLLInit.h"    // for dynamic access

void CheckErrorCode(int iErrorCode, int iLine);


void main(void)
{
    int iBoardNumber;
    int iDLLVersion;
    int iDrvVersion;
    int iBoardVersion;
    int iSerial;
    int iErrorCode;
    DEVICEINFOSTRUCT DevInfo;
    int iPortCnt;
    int iMaxPort;
    int iCnt;
    int iBitCnt;
    int iValue;

    meOpen ();  // calls the initialize function

    iDLLVersion = me1000GetDLLVersion();
    printf(
        "Version of DLL is %04x.%04x\n",
        (iDLLVersion>>16)& 0xFFFF,
        (iDLLVersion)    & 0xFFFF);

    iErrorCode = me1000GetDriverVersion(&iDrvVersion);
    CheckErrorCode(iErrorCode,__LINE__);
    printf(
        "Version of Driver is %04x.%04x\n",
        (iDrvVersion>>16)& 0xFFFF,
        (iDrvVersion)    & 0xFFFF);

    for(iBoardNumber=0; iBoardNumber<32; iBoardNumber++)
    {
        iErrorCode = me1000GetBoardVersion (iBoardNumber, &iBoardVersion);
        // CheckErrorCode(iErrorCode,__LINE__); // we check it with the following lines

        if(iErrorCode != 1)
        {
            continue;   // There is no board on the specified iBoardNumber
        }

        switch (iBoardVersion)
        {
            case 0x100a:
                printf("We found a ME-1000 A with 64 lines\n");
                break;

            case 0x100b:
                printf("We found a ME-1000 B with 128 lines\n");
                break;

            default:
                printf("We found a unknown typ of ME-1000 \n");
                printf(
                    "\tBoard %d has a Board version of 0x%04X:\n",
                    iBoardNumber,
                    iBoardVersion);
                continue;   // There is no board on the specified BoardNumber ?
        }


        // Now we can start the work:
        iErrorCode = me1000GetSerialNumber(iBoardNumber, &iSerial);
        CheckErrorCode(iErrorCode,__LINE__);
        printf("Serial Number of the board is %08x\n", iSerial);

        iErrorCode = me1000GetDevInfo(iBoardNumber, &DevInfo);
        CheckErrorCode(iErrorCode,__LINE__);
        printf("\n");
        printf("Board: %2d Device Info\n", iBoardNumber);
        printf("----------------------\n");
        printf("\tVendor ID:          0x%04X\n",  DevInfo.dwVendorID);
        printf("\tDevice ID:          0x%04X\n",  DevInfo.dwDeviceID);
        printf("\tBus Number:         %u\n",      DevInfo.dwBusNumber);
        printf("\tSystem Slot Number: %u\n",      DevInfo.dwSystemSlotNumber);
        printf("\tPort Base:          0x%04X\n",  DevInfo.dwPortBase);
        printf("\tPort Count:         %u\n",      DevInfo.dwPortCount);
        printf("\tPLX Port Base:      0x%04X\n",  DevInfo.dwPortBasePLX);
        printf("\tPLX Port Count:     %u\n",      DevInfo.dwPortCountPLX);
        printf("\tSerial Number:      0x%08X\n",  DevInfo.dwSerialNumber);
        printf("\tHardware Revision:  0x%04X\n",  DevInfo.dwHWRevision);
        printf("\tVersion:            0x%04X\n",  DevInfo.dwVersion);

        iErrorCode = me1000DIOReset(iBoardNumber);
        CheckErrorCode(iErrorCode,__LINE__);

        printf("Be careful not to cause a short circuit!\n");
        printf("Do not connect a output with a output!\n");
        printf("Press any key to continue\n");
        getch();


        iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTA, MEOUTPUT);
        CheckErrorCode(iErrorCode,__LINE__);
        iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTB, MEOUTPUT);
        CheckErrorCode(iErrorCode,__LINE__);

        if(iBoardVersion == 0x100b)
        {
            iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTC, MEOUTPUT);
            CheckErrorCode(iErrorCode,__LINE__);
            iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTD, MEOUTPUT);
            CheckErrorCode(iErrorCode,__LINE__);
        }

        iErrorCode = me1000DOSetLong(iBoardNumber, PORTA, 0xFFFFFFFF);
        CheckErrorCode(iErrorCode,__LINE__);
        iErrorCode = me1000DOSetLong(iBoardNumber, PORTB, 0xFFFFFFFF);
        CheckErrorCode(iErrorCode,__LINE__);

        if(iBoardVersion == 0x100b)
        {
            iErrorCode = me1000DOSetLong(iBoardNumber, PORTC, 0xFFFFFFFF);
            CheckErrorCode(iErrorCode,__LINE__);
            iErrorCode = me1000DOSetLong(iBoardNumber, PORTD, 0xFFFFFFFF);
            CheckErrorCode(iErrorCode,__LINE__);
        }


        if(iBoardVersion == 0x100a)
        {
            iMaxPort = PORTB;
        }
        else
        {
            iMaxPort = PORTD;
        }

        for (iPortCnt=PORTA; iPortCnt<=iMaxPort; iPortCnt++)
        {
            for (iCnt=0; iCnt<2; iCnt++)
            {
                iErrorCode = me1000DOSetWord(iBoardNumber, iPortCnt, WORD_0, 0x3333);
                Sleep(200);
                iErrorCode = me1000DOSetWord(iBoardNumber, iPortCnt, WORD_1, 0x3333);
                Sleep(200);
                iErrorCode = me1000DOSetWord(iBoardNumber, iPortCnt, WORD_0, 0xCCCC);
                Sleep(200);
                iErrorCode = me1000DOSetWord(iBoardNumber, iPortCnt, WORD_1, 0xCCCC);
                Sleep(200);
            }
            iErrorCode = me1000DOSetLong(iBoardNumber, iPortCnt, 0xFFFFFFFF);
            CheckErrorCode(iErrorCode,__LINE__);
        }


        for (iPortCnt=PORTA; iPortCnt<=iMaxPort; iPortCnt++)
        {
            for (iCnt=0; iCnt<2; iCnt++)
            {
                iErrorCode = me1000DOSetByte(iBoardNumber, iPortCnt, BYTE_0, 0x00);
                Sleep(100);
                iErrorCode = me1000DOSetByte(iBoardNumber, iPortCnt, BYTE_1, 0x00);
                Sleep(100);
                iErrorCode = me1000DOSetByte(iBoardNumber, iPortCnt, BYTE_2, 0x00);
                Sleep(100);
                iErrorCode = me1000DOSetByte(iBoardNumber, iPortCnt, BYTE_3, 0x00);
                Sleep(100);
                iErrorCode = me1000DOSetByte(iBoardNumber, iPortCnt, BYTE_0, 0xFF);
                Sleep(100);
                iErrorCode = me1000DOSetByte(iBoardNumber, iPortCnt, BYTE_1, 0xFF);
                Sleep(100);
                iErrorCode = me1000DOSetByte(iBoardNumber, iPortCnt, BYTE_2, 0xFF);
                Sleep(100);
                iErrorCode = me1000DOSetByte(iBoardNumber, iPortCnt, BYTE_3, 0xFF);
                Sleep(100);
            }
            iErrorCode = me1000DOSetLong(iBoardNumber, iPortCnt, 0xFFFFFFFF);
            CheckErrorCode(iErrorCode,__LINE__);
        }


        for (iPortCnt=PORTA; iPortCnt<=iMaxPort; iPortCnt++)
        {
            for (iCnt=0; iCnt<2; iCnt++)
            {
                for(iBitCnt=BIT_0; iBitCnt<BIT_31; iBitCnt++)
                {
                    iErrorCode = me1000DOSetBit(iBoardNumber, iPortCnt, iBitCnt, 0);
                    Sleep(10);
                }
                for(iBitCnt=BIT_0; iBitCnt<BIT_31; iBitCnt++)
                {
                    iErrorCode = me1000DOSetBit(iBoardNumber, iPortCnt, iBitCnt, 1);
                    Sleep(10);
                }
            }
            iErrorCode = me1000DOSetLong(iBoardNumber, iPortCnt, 0xFFFFFFFF);
            CheckErrorCode(iErrorCode,__LINE__);
        }


        iErrorCode = me1000DOSetLong(iBoardNumber, PORTA, 0xFEDCBA98);
        CheckErrorCode(iErrorCode,__LINE__);
        iErrorCode = me1000DOSetLong(iBoardNumber, PORTB, 0x12345678);
        CheckErrorCode(iErrorCode,__LINE__);

/*      // we can read back the written values, if we dont apply me1000DIOSetPortDirection
        // in the default application you have to use me1000DIOSetPortDirection !!!
        iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTA, MEINPUT);
        CheckErrorCode(iErrorCode,__LINE__);
        iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTB, MEINPUT);
        CheckErrorCode(iErrorCode,__LINE__);
*/
        if(iBoardVersion == 0x100b)
        {
            iErrorCode = me1000DOSetLong(iBoardNumber, PORTC, 0xFFFFFFFF);
            CheckErrorCode(iErrorCode,__LINE__);
            iErrorCode = me1000DOSetLong(iBoardNumber, PORTD, 0x00000000);
            CheckErrorCode(iErrorCode,__LINE__);

/*      // we can read back the written values, if we dont apply me1000DIOSetPortDirection
        // in the default application you have to use me1000DIOSetPortDirection !!!
            iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTC, MEINPUT);
            CheckErrorCode(iErrorCode,__LINE__);
            iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTD, MEINPUT);
            CheckErrorCode(iErrorCode,__LINE__);
*/
        }

        for (iPortCnt=PORTA; iPortCnt<=iMaxPort; iPortCnt++)
        {
            iErrorCode = me1000DIGetLong(iBoardNumber, iPortCnt, &iValue);
            CheckErrorCode(iErrorCode,__LINE__);
            printf("On port %d is a long value of 0x%08x\n",iPortCnt,iValue);
        }

        for (iPortCnt=PORTA; iPortCnt<=iMaxPort; iPortCnt++)
        {
            iErrorCode = me1000DIGetWord(iBoardNumber, iPortCnt, WORD_0, &iValue);
            CheckErrorCode(iErrorCode,__LINE__);
            printf("On port %d is a word value of 0x%04x (WORD_0)\n",iPortCnt,iValue);

            iErrorCode = me1000DIGetWord(iBoardNumber, iPortCnt, WORD_1, &iValue);
            CheckErrorCode(iErrorCode,__LINE__);
            printf("On port %d is a word value of 0x%04x (WORD_1)\n",iPortCnt,iValue);
        }

        for (iPortCnt=PORTA; iPortCnt<=iMaxPort; iPortCnt++)
        {
            iErrorCode = me1000DIGetByte(iBoardNumber, iPortCnt, BYTE_0, &iValue);
            CheckErrorCode(iErrorCode,__LINE__);
            printf("On port %d is a byte value of 0x%02x (BYTE_0)\n",iPortCnt,iValue);

            iErrorCode = me1000DIGetByte(iBoardNumber, iPortCnt, BYTE_1, &iValue);
            CheckErrorCode(iErrorCode,__LINE__);
            printf("On port %d is a byte value of 0x%02x (BYTE_1)\n",iPortCnt,iValue);

            iErrorCode = me1000DIGetByte(iBoardNumber, iPortCnt, BYTE_2, &iValue);
            CheckErrorCode(iErrorCode,__LINE__);
            printf("On port %d is a byte value of 0x%02x (BYTE_2)\n",iPortCnt,iValue);

            iErrorCode = me1000DIGetByte(iBoardNumber, iPortCnt, BYTE_3, &iValue);
            CheckErrorCode(iErrorCode,__LINE__);
            printf("On port %d is a byte value of 0x%02x (BYTE_3)\n",iPortCnt,iValue);
        }

        for (iPortCnt=PORTA; iPortCnt<=iMaxPort; iPortCnt++)
        {
            printf("On port %d is a bit value of: ",iPortCnt);
            for(iBitCnt=BIT_31; iBitCnt>=BIT_0; iBitCnt--)
            {
                iErrorCode = me1000DIGetBit(iBoardNumber, iPortCnt, iBitCnt, &iValue);
                CheckErrorCode(iErrorCode,__LINE__);
                printf("%d",iValue);
            }
            printf("\n");
        }

        {
#define MAX_STR_CNT 0xFF
            char pcUserTextIn[] = "(Only a Example:)This is our first board on the right slot of the rear";
            int iMaxLength = MAX_STR_CNT;
            char pcUserTextOut[MAX_STR_CNT];

            iErrorCode = me1000WriteUserString(iBoardNumber, pcUserTextIn);
            CheckErrorCode(iErrorCode,__LINE__);

            iErrorCode = me1000ReadUserString(iBoardNumber, pcUserTextOut, iMaxLength);
            CheckErrorCode(iErrorCode,__LINE__);
            printf(
                "User String of the board is\n\t%s\n",
                pcUserTextOut);
        }
    }

    meClose();

    printf("Press any key to continue\n");
    getch();
}



void CheckErrorCode(int iErrorCode, int iLine)
{
#define MAX_STR_CNT 0xFF
    int iMaxLength = MAX_STR_CNT;
    char pcErrortext[MAX_STR_CNT];

    if(iErrorCode != 1)
    {
        printf("Error in module %s in line %d\n", __FILE__, iLine);
        printf("Or there is no board on the spezified board number!\n");

        iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
        printf(
            "Error String of the board is\n\t%s\n",
            pcErrortext);
        printf("Press any key to continue\n");
        getch();

    }
}


