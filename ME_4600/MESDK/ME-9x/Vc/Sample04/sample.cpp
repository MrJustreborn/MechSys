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
USEUNIT("..\medefs.h");
USEUNIT("..\DLLInit.h");
#endif

#include "..\medefs.h"
//#include "..\me9x.h"
#include "..\DLLInit.h"


#define MAXGenIrqCnt	10
#define MAXBitNumber	16
#define MAXNoOfBoards	32   // depends on driver version: 4 or 32(current)


// simple callback function to test interrupts
void _stdcall IrqHandler(void);


int count=0;		// IRQ Counter


int main(void)
{
	int iBoardNo;
	int iDLLVers;
	int iBoardTyp;
	int iErrCode;
	int iIOValueSet;
	int iIOValueGet;
	int iGenIrqCnt;
	int iBitNumber;
	int iIrqSave;

    meOpen();

	// read driver infos
	iDLLVers = _me9xGetDLLVersion();
	printf("DLLVers:  0x%08x\n", iDLLVers);

	for (iBoardNo=0; iBoardNo<MAXNoOfBoards; iBoardNo++)    // test every possiple board
	{
		// read board infos
		printf("\n========================================\n");
		iErrCode = _me9xGetBoardVersion(iBoardNo,&iBoardTyp);

        if (iErrCode != 1)
        {
            // Board not found
            iBoardTyp = 0;
        }

		switch (iBoardTyp)
		{
		case 0x96:
			{
				printf("Board number %d represents a ME-96\n", iBoardNo);
				// write and read bytes
				iIOValueSet = 0x00;
				iErrCode = _me96DOSetByte(iBoardNo, 0, iIOValueSet);
				Sleep(500);
				iErrCode = _me96DIGetByte(iBoardNo, 1, &iIOValueGet);
				printf("Write 0x%02x and read 0x%02x\n",iIOValueSet, iIOValueGet);

				iIOValueSet = 0xAA;
				iErrCode = _me96DOSetByte(iBoardNo, 0, iIOValueSet);
				Sleep(500);
				iErrCode = _me96DIGetByte(iBoardNo, 1, &iIOValueGet);
				printf("Write 0x%02x and read 0x%02x\n",iIOValueSet, iIOValueGet);

				iIOValueSet = 0x55;
				iErrCode = _me96DOSetByte(iBoardNo, 0, iIOValueSet);
				Sleep(500);
				iErrCode = _me96DIGetByte(iBoardNo, 1, &iIOValueGet);
				printf("Write 0x%02x and read 0x%02x\n",iIOValueSet, iIOValueGet);

				iIOValueSet = 0xFF;
				iErrCode = _me96DOSetByte(iBoardNo, 0, iIOValueSet);
				Sleep(500);
				iErrCode = _me96DIGetByte(iBoardNo, 1, &iIOValueGet);
				printf("Write 0x%02x and read 0x%02x\n",iIOValueSet, iIOValueGet);


				// set and enable interrupt mode
				iErrCode = _me96EnableInt(iBoardNo,IrqHandler);

				// generate interrupts with SetBit
				// (if you have the apropriate adapter only)
				// (connect output pin 0 with irq input)
				for (iGenIrqCnt=0; iGenIrqCnt<MAXGenIrqCnt; iGenIrqCnt++)
				{
					iErrCode = _me96DOSetBit(iBoardNo,0,1);
					Sleep(1);
					iErrCode = _me96DOSetBit(iBoardNo,0,0);
					Sleep(1);
				}

				// disable IRQ
				iErrCode = _me96DisableInt(iBoardNo);
			}
			break;

		case 0x95:
			{
				printf("Board number %d represents a ME-95\n", iBoardNo);

				// write Bytes 
				iIOValueSet = 0x00;
				iErrCode = _me95DOSetByte(iBoardNo, 0, iIOValueSet);
				iErrCode = _me95DOSetByte(iBoardNo, 1, iIOValueSet);
				Sleep(500);
				printf("Write 0x%02x\n",iIOValueSet);

				iIOValueSet = 0xAA;
				iErrCode = _me95DOSetByte(iBoardNo, 0, iIOValueSet);
				iErrCode = _me95DOSetByte(iBoardNo, 1, iIOValueSet);
				Sleep(500);
				printf("Write 0x%02x\n",iIOValueSet);

				iIOValueSet = 0x55;
				iErrCode = _me95DOSetByte(iBoardNo, 0, iIOValueSet);
				iErrCode = _me95DOSetByte(iBoardNo, 1, iIOValueSet);
				Sleep(500);
				printf("Write 0x%02x\n",iIOValueSet);

				iIOValueSet = 0xFF;
				iErrCode = _me95DOSetByte(iBoardNo, 0, iIOValueSet);
				iErrCode = _me95DOSetByte(iBoardNo, 1, iIOValueSet);
				Sleep(500);
				printf("Write 0x%02x\n",iIOValueSet);

				iIOValueSet = 0x00;
				iErrCode = _me95DOSetByte(iBoardNo, 0, iIOValueSet);
				iErrCode = _me95DOSetByte(iBoardNo, 1, iIOValueSet);
				Sleep(500);
				printf("Write 0x%02x\n",iIOValueSet);

				// Set the bits
				printf("Set the bits:\n");
				for(iBitNumber=0; iBitNumber<MAXBitNumber; iBitNumber++)
				{
					Sleep(100);
					iErrCode = _me95DOSetBit(iBoardNo,iBitNumber,1);
					printf("I");
				}

				printf("\nReset the bits:\n");
				for(iBitNumber=0; iBitNumber<MAXBitNumber; iBitNumber++)
				{
					Sleep(100);
					iErrCode = _me95DOSetBit(iBoardNo,iBitNumber,0);
					printf("0");
				}
				printf("\n");
			}
			break;

		case 0x94:
			{
				printf("Board number %d represents a ME-94\n", iBoardNo);

				// set and enable interrupt mode
				iErrCode = _me94EnableInt(iBoardNo,IrqHandler);

				// read Bytes
				iErrCode = _me94DIGetByte(iBoardNo, 0, &iIOValueGet);
				printf("Read: 0x%02x\n", iIOValueGet);

				printf("Now we wait 5 seconds on the interrupts\n");
				iIrqSave = count;
				Sleep(5000);
				if (iIrqSave == count)
					printf("No interrupts occured\n");

				// disable IRQ
				iErrCode = _me94DisableInt(iBoardNo);
			}
			break;

		default:
			{
				printf("Board number %d does not exist", iBoardNo);
			}
			break;
		}
	}

	printf("\n");

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