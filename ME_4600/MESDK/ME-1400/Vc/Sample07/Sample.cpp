#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include ".\..\medefs.h"
#include ".\..\me1400.h"          // for using with a lib

#define MAXNAME         0x10
#define ME_MAX_DEVICES  32

void CheckErrorCode(int iErrorCode, int iLine);

int main (void)
{   
    int iErrorCode;
    int iDLLVersion;
    int iBoardVersion;
    
    // determine current DLL version
    iDLLVersion = me1400GetDLLVersion ();
    printf(
        "iDLLVersion: Major: 0x%04x Minor: 0x%04x\n",
        (iDLLVersion>>16)& 0xFFFF,
        (iDLLVersion)    & 0xFFFF);
    
    // determine board version
    iErrorCode = me1400GetBoardVersion(
        BOARD_00, 
        &iBoardVersion);
    printf(
        "iBoardVersion: 0x%04x\n",
        iBoardVersion);

    // Digital Output
    printf("Press a key to DIO");
    getch();
    printf("Set Board0 PortA Bit0 to 1\n");
    iErrorCode = me1400DIOSetPortDirection(
        BOARD_00,
        PORTA,
        MEOUTPUT);
    CheckErrorCode(iErrorCode, __LINE__);
    iErrorCode = me1400DOSetBit(
        BOARD_00,
        PORTA,
        0,      // iBitNumber
        0x01);  // iValue
    CheckErrorCode(iErrorCode, __LINE__);

    // reset board
    printf("Press a key to reset");
    getch();
    iErrorCode = me1400ResetBoard(BOARD_00);
    CheckErrorCode(iErrorCode, __LINE__);

    // init board
    printf("Press a key to init");
    getch();
    iErrorCode = me1400InitBoard(BOARD_00);
    CheckErrorCode(iErrorCode, __LINE__);

    // Digital Output
    printf("Press a key to DIO");
    getch();
    printf("Set Board0 PortA Bit0 to 1\n");
    iErrorCode = me1400DIOSetPortDirection(
        BOARD_00,
        PORTA,
        MEOUTPUT);
    CheckErrorCode(iErrorCode, __LINE__);
    iErrorCode = me1400DOSetBit(
        BOARD_00,
        PORTA,
        0,      // iBitNumber
        0x01);  // iValue
    CheckErrorCode(iErrorCode, __LINE__);

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
    }
}
