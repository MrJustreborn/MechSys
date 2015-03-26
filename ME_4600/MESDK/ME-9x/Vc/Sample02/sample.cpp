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


#define BOARDNUMBER	    0
#define MAXBitNumber	16


int main(void)
{
	int iDLLVers;
	int iBoardTyp;
	int iErrCode;
	int iIOValueSet;
	int iBitNumber;


    printf("ME-95 (CP380-O) programm for demonstration\n");
    printf("==========================================\n\n");

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
        if (iBoardTyp != 0x95)
        {
            printf("Board number %d is not configured as ME-95 (CP380-O)\n", BOARDNUMBER);
            printf("Please use a other example !\n");
        }
        else
        {
            printf("Board number %d is configured as ME-95\n", BOARDNUMBER);

            // IO programming (Byte):
            printf("\nSet bytes:\n");
			iIOValueSet = 0x00;
			iErrCode = _me95DOSetByte(BOARDNUMBER, 0, iIOValueSet);
            iErrCode = _me95DOSetByte(BOARDNUMBER, 1, iIOValueSet);
			printf("Write 0x%02x%02x\n",iIOValueSet,iIOValueSet);
            Sleep(500);

			iIOValueSet = 0xFF;
			iErrCode = _me95DOSetByte(BOARDNUMBER, 0, iIOValueSet);
            iErrCode = _me95DOSetByte(BOARDNUMBER, 1, iIOValueSet);
			printf("Write 0x%02x%02x\n",iIOValueSet,iIOValueSet);
            Sleep(500);

			iIOValueSet = 0x55;
			iErrCode = _me95DOSetByte(BOARDNUMBER, 0, iIOValueSet);
            iErrCode = _me95DOSetByte(BOARDNUMBER, 1, iIOValueSet);
			printf("Write 0x%02x%02x\n",iIOValueSet,iIOValueSet);
            Sleep(500);

            iIOValueSet = 0x00;
			iErrCode = _me95DOSetByte(BOARDNUMBER, 0, iIOValueSet);
            iErrCode = _me95DOSetByte(BOARDNUMBER, 1, iIOValueSet);
			printf("Write 0x%02x%02x\n",iIOValueSet,iIOValueSet);
            Sleep(500);

            // IO programming (Bit):
			printf("\nSet bits:\n");
			for(iBitNumber=0; iBitNumber<MAXBitNumber; iBitNumber++)
			{
				Sleep(200);
				iErrCode = _me95DOSetBit(BOARDNUMBER,iBitNumber,1);
				printf("I");
			}

			printf("\nReset bits:\n");
			for(iBitNumber=0; iBitNumber<MAXBitNumber; iBitNumber++)
			{
				Sleep(100);
				iErrCode = _me95DOSetBit(BOARDNUMBER,iBitNumber,0);
				printf("0");
			}
			printf("\n");
        }
    }

    meClose();

	return iErrCode;
}
