/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       Visual C++ 6.0                                                                          */
/*  Copyright:      2000 Meilhaus Electronic GmbH                                                           */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                                                                                                          */
/*  Description:    General Example for the board ME-96 (CP-380 IO)                                         */
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
//#include "..\me9x.h"          // for static access with a lib file
#include "..\DLLInit.h"


#define BOARDNUMBER     0
#define MAXGenIrqCnt    10
#define MAXBitNumber    8


// simple callback function to test interrupts
void _stdcall IrqHandler(void);


int count=0;        // IRQ Counter


int main(void)
{
    int iDLLVers;
    int iBoardTyp;
    int iErrCode;
    int iIOValueSet;
    int iIOValueGet;
    int iGenIrqCnt;
    int iBitNumber;
    int iIrqSave;


    printf("ME-96 (CP380-IO) programm for demonstration\n");
    printf("===========================================\n\n");

    meOpen();

    // read driver infos
    iDLLVers = _me9xGetDLLVersion();
    printf("DLLVers:  %08x (hex)\n\n", iDLLVers);

    // read board infos
    iErrCode = _me9xGetBoardVersion(BOARDNUMBER, &iBoardTyp);

    if (iErrCode != 1)
    {
        // Board not found
        printf("Board number %d does not exist!\n", BOARDNUMBER);
        printf("(Or not correctly installed)\n");
    }
    else
    {
        if (iBoardTyp != 0x96)
        {
            printf("Board number %d is not configured as ME-96 (CP380-IO)\n", BOARDNUMBER);
            printf("Please use a other example !\n");
        }
        else
        {
            printf("Board number %d is configured as ME-96\n", BOARDNUMBER);

            // IO programming (Byte):
            printf("\nSet bytes:\n");
            iIOValueSet = 0x00;
            iErrCode = _me96DOSetByte(BOARDNUMBER, 0, iIOValueSet);
            Sleep(1);
            iErrCode = _me96DIGetByte(BOARDNUMBER, 1, &iIOValueGet);
            printf("Write 0x%02x and read 0x%02x\n",iIOValueSet, iIOValueGet);
            Sleep(500);

            iIOValueSet = 0xFF;
            iErrCode = _me96DOSetByte(BOARDNUMBER, 0, iIOValueSet);
            Sleep(1);
            iErrCode = _me96DIGetByte(BOARDNUMBER, 1, &iIOValueGet);
            printf("Write 0x%02x and read 0x%02x\n",iIOValueSet, iIOValueGet);
            Sleep(500);

            iIOValueSet = 0x55;
            iErrCode = _me96DOSetByte(BOARDNUMBER, 0, iIOValueSet);
            Sleep(1);
            iErrCode = _me96DIGetByte(BOARDNUMBER, 1, &iIOValueGet);
            printf("Write 0x%02x and read 0x%02x\n",iIOValueSet, iIOValueGet);
            Sleep(500);

            // IO programming (Bit):
            printf("\nSet bits:\n");
            for(iBitNumber=0; iBitNumber<MAXBitNumber; iBitNumber++)
            {
                Sleep(200);
                iErrCode = _me96DOSetBit(BOARDNUMBER,iBitNumber,1);
                printf("I");
            }

            printf("\nReset bits:\n");
            for(iBitNumber=0; iBitNumber<MAXBitNumber; iBitNumber++)
            {
                Sleep(100);
                iErrCode = _me96DOSetBit(BOARDNUMBER,iBitNumber,0);
                printf("0");
            }
            printf("\n");

            // IRQ programming:
            // set and enable interrupt mode
            iIrqSave = count;
            iErrCode = _me96EnableInt(BOARDNUMBER,IrqHandler);

            // generate interrupts with SetBit
            // if you have the apropriate adapter only
            // otherwise connect output pin 0 with irq input
            // or generate interrupts yourself
            printf("\nInterrupt processing:\n");
            for (iGenIrqCnt=0; iGenIrqCnt<MAXGenIrqCnt; iGenIrqCnt++)
            {
                iErrCode = _me96DOSetBit(BOARDNUMBER,0,1);
                Sleep(1);
                iErrCode = _me96DOSetBit(BOARDNUMBER,0,0);
                Sleep(1);
            }

            printf("\nNow we wait 5 seconds on external interrupts\n");
            Sleep(5000);
            if (iIrqSave == count)
                printf("No interrupts occured\n");

            // disable IRQ
            iErrCode = _me96DisableInt(BOARDNUMBER);
        }
    }

    meClose();

    return iErrCode;
}


// simple Callback function
void _stdcall IrqHandler(void)
{
    count++;
    if (count == 65000)
        count = 0;
    printf("<IRQ> ");
    //printf("+");
    //printf(".%04d", count);
}