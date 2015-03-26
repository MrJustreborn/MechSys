/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       Visual C++ 6.0                                                                          */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                                                                                                          */
/*  Description:    SetBit with more than one applications                                                  */
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
#define MAXBitNumber	8




int main(void)
{
	int iDLLVers;
	int iBoardTyp;
	int iErrCode;
	int iIOValueSet;
	int iIOValueGet;
    int iBitValue;
	int iBitNumber;
    unsigned char ch;


    printf("ME-96 programm for demonstration\n");
    printf("===========================================\n\n");

    meOpen();

	// read driver infos
	iDLLVers = me9xGetDLLVersion();
	printf("DLLVers:   %08x (hex)\n\n", iDLLVers);

	// read board infos
	iErrCode = me9xGetBoardVersion(BOARDNUMBER, &iBoardTyp);
    printf("BoardVers: %08x (hex)\n\n", iBoardTyp);

    // IO programming (Byte):
	iIOValueSet = 0x00; 
    printf("\nSet port to 0x02x\n", iIOValueSet);
	iErrCode = me96DOSetByte(BOARDNUMBER, 0, iIOValueSet);
	Sleep(1);

    do
    {
        printf("Press a number between 0 and 7 or 8 to reset and 9 to exit!\n");
        ch = getch();
        ch = ch - '0';

        if (ch<8)
        {
            iBitValue =  1;
            iBitNumber = ch;
            me9xInportByte(BOARDNUMBER, 0, &iIOValueGet);
            if(iBitValue == 0)
                iIOValueGet |=  (0x01<<iBitNumber);
            else
                iIOValueGet &= ~(0x01<<iBitNumber);
            me9xOutportByte(BOARDNUMBER, 0, iIOValueGet);
        }

        if (ch==8)
        {
            me9xOutportByte(BOARDNUMBER, 0, 0xFF);
        }
    }
    while(!(ch==9));

    meClose();

	return iErrCode;
}


