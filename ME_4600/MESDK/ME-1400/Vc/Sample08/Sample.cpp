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
	int iPort;
	int iBit;
    
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
	iBit = 0;
	for (iPort=PORTA; iPort<=PORTFH; iPort++)
	{
		printf("Press a key to set Port %d to Out and Bit %d to High...",iPort , iBit);
		switch (iPort)
		{
		case PORTA:		printf("Port %d: PORTA\n", PORTA);		break;
		case PORTB:		printf("Port %d: PORTB\n", PORTB);		break;
		case PORTC:		printf("Port %d: PORTC\n", PORTC);		break;
		//case PORTCL:	printf("Port %d: PORTCL\n", PORTCL);	break;
		//case PORTCH:	printf("Port %d: PORTCH\n", PORTCH);	break;
		case PORTD:		printf("Port %d: PORTD\n", PORTD);		break;
		case PORTE:		printf("Port %d: PORTE\n", PORTE);		break;
		case PORTF:		printf("Port %d: PORTF\n", PORTF);		break;
		//case PORTFL:	printf("Port %d: PORTFL\n", PORTFL);	break;
		//case PORTFH:	printf("Port %d: PORTFH\n", PORTFH);	break;
		default : printf("Wrong port\n"); continue;
		}
		getch();
		iErrorCode = me1400DIOSetPortDirection(
			BOARD_00,
			iPort,
			MEOUTPUT);
		CheckErrorCode(iErrorCode, __LINE__);
		iErrorCode = me1400DOSetBit(
			BOARD_00,
			iPort,
			iBit,   // iBitNumber
			0x01);  // iValue
		CheckErrorCode(iErrorCode, __LINE__);

		iBit++;	if (iBit==8) iBit=0;
	}



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
