#include <stdio.h>
#include <windows.h>
#include <conio.h>


#define COUNTER_SOURCE_SUBD     (0x00)
#define COUNTER_SOURCE_1MHZ     (0x01)
#define COUNTER_SOURCE_10MHZ    (0x02)
#define COUNTER_SOURCE_PREV     (0x03)


#include ".\..\medefs.h"
#include ".\..\me1400.h"          // for using with a lib



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







	int counter = 0;
	int source;
	int prescaler = 2;
	int duty = 50;

	source = COUNTER_SOURCE_1MHZ;
	source = COUNTER_SOURCE_SUBD;
    source = COUNTER_SOURCE_10MHZ;

	printf("Setup PWM with prescaler %d and duty cycle %d.\n", prescaler, duty);
	me1400CntPWMStart(BOARD_00, counter, source, prescaler, duty);


    printf ("\n  ***** Press Return to quit *****");
    getchar();
    getch();

	me1400CntPWMStop(BOARD_00, counter);

    return 0;
}
