#include <stdio.h>
#include <windows.h>


#define MAXNAME         0x10
#define ME_MAX_DEVICES  32

#define ERROR_PIN           1
#define ERROR_BOARDNUMBER   2
#define ERROR_CONTROL       3



typedef struct _PCIENTRY
{
    WORD    wVenID;
    WORD    wDevID;
    DWORD   dwSlotNumber;
    BYTE    bRevision;
    DWORD   dwBaseIO;
    DWORD   dwBasePLX;
    BYTE    bIrqLine;
    DWORD   dwName;
    DWORD   dwSerialNumber;
    DWORD   bAssigned;
    DWORD   dwBusNumber;
    BYTE    szName[MAXNAME];    

} PCIENTRY, *PPCIENTRY;

PPCIENTRY   pPCIList[ME_MAX_DEVICES];
PCIENTRY   PCIEntry;
int iIrqCount = 0;


// Definition file and DLL header
#include ".\..\medefs.h"
#include ".\..\me1400.h"






//prototypes:
void CheckErrorCode(int iErrorCode, int iLine);
void WrongParameters(int iReason);


// Please use the manual for the description of the functions
int main (int argc, char *argv[])
{	
    int iErrorCode;
    int iBoardNumber;
    int iBoardVersion;
    int iFoundIt;
    int iControlByte;
    int iMultiPin;
    int iArgvCnt;

    printf("This program sets the counter register\n");
    printf("Use it only for upward compatibility with ME-14 ISA version\n\n");

    /*-- R E A D   U S E R   S P E C I F I E D   V A L U E S -*/
    /*--- Boardnumber ---*/
    iFoundIt = 0;
    for(iArgvCnt=1; iArgvCnt<argc; iArgvCnt++)
    {
        if (strstr(argv[iArgvCnt], "board"))
        {
            sscanf(1+strchr(argv[iArgvCnt],':'), "%d", &iBoardNumber);
            iFoundIt = 1;
            break;
        }
    }

    if (!iFoundIt)
    {
        WrongParameters(ERROR_BOARDNUMBER);
        return 1;
    }

    /*--- Control byte: ---*/
    iFoundIt = 0;
    for(iArgvCnt=1; iArgvCnt<argc; iArgvCnt++)
    {
        if (strstr(argv[iArgvCnt], "control"))
        {
            sscanf(1+strchr(argv[iArgvCnt],':'), "%x", &iControlByte);
            iFoundIt = 1;
            break;
        }
    }

    if (!iFoundIt)
    {
        WrongParameters(ERROR_CONTROL);
        return 1;
    }

    /*--- Multifunction pin: ---*/
    iFoundIt = 0;
    for(iArgvCnt=1; iArgvCnt<argc; iArgvCnt++)
    {
        if (strstr(argv[iArgvCnt], "pin"))
        {
            sscanf(1+strchr(argv[iArgvCnt],':'), "%d", &iMultiPin);
            iFoundIt = 1;
            break;
        }
    }

    if (!iFoundIt)
    {
        WrongParameters(ERROR_PIN);
        return 1;
    }


    /*--- Get general information --------------------*/

	// determine board version
	iErrorCode = me1400GetBoardVersion(
        iBoardNumber, 
        &iBoardVersion);

    CheckErrorCode(iErrorCode, __LINE__);



    /*--- Give all information to the user -----------*/

        printf(
        "BoardVersion: 0x%08x\n", 
        iBoardVersion);

        printf("Bord number is %d\n", iBoardNumber);
        printf("Control word is %02x\n", iControlByte);
        printf("Multifunction pin is %d\n", iMultiPin);

        printf("\nValues of part A (ME-1400 A & B only):\n");

        if (PartA(iControlByte) & ME1400_TIMERINTERNCLOCK_10MHZ)
            printf("Internal clock is 10 MHz\n");
        else
            printf("Internal clock is 1 MHz\n");



        if (PartA(iControlByte) & ME1400_TIMERCLOCKSOURCE0_SUBD)
            printf("Clock source of timer 0 is SUBD\n");
        else
            printf("Clock source of timer 0 is INTERN\n");


        if (PartA(iControlByte) & ME1400_TIMERCLOCKSOURCE1_SUBD)
            printf("Clock source of timer 1 is SUBD\n");
        else
            printf("Clock source of timer 1 is output of timer 0\n");


        if (PartA(iControlByte) & ME1400_TIMERCLOCKSOURCE2_SUBD)
            printf("Clock source of timer 2 is SUBD\n");
        else
            printf("Clock source of timer 2 is output of timer 1\n");


        printf("\nValues of part B (ME-1400 B only):\n");

        if (PartB(iControlByte) & ME1400_TIMERINTERNCLOCK_10MHZ)
            printf("Internal clock is 10 MHz\n");
        else
            printf("Internal clock is 1 MHz\n");


        if (PartB(iControlByte) & ME1400_TIMERCLOCKSOURCE0_SUBD)
            printf("Clock source of timer 0 is SUBD\n");
        else
            printf("Clock source of timer 0 is INTERN\n");


        if (PartB(iControlByte) & ME1400_TIMERCLOCKSOURCE1_SUBD)
            printf("Clock source of timer 1 is SUBD\n");
        else
            printf("Clock source of timer 1 is output of timer 0\n");


        if (PartB(iControlByte) & ME1400_TIMERCLOCKSOURCE2_SUBD)
            printf("Clock source of timer 2 is SUBD\n");
        else
            printf("Clock source of timer 2 is output of timer 1\n");


        if (iMultiPin & ME1400_MULTIPIN_INTERNALCLOCK)
            printf("\nMultipin is for Irq mode\n");
        else
            printf("\nMultipin is for internal clock mode\n");



    /*--- Set the specified register -----------------*/

    /* mean part: Set Register (former jumper) */
    iErrorCode = me1400InitModeTimerA(
        iBoardNumber, 
        (iControlByte>>4) & 0x0F);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400InitModeTimerB(
        iBoardNumber,
        iControlByte & 0x0F);
    CheckErrorCode(iErrorCode, __LINE__);

    iErrorCode = me1400SetMultifunctionPin(iBoardNumber, 1);
    CheckErrorCode(iErrorCode, __LINE__);

    /*--- End of test --------------------------------*/

    return 0;
}





void WrongParameters(int iReason)
{
    printf("Wrong parameters\n");

    switch (iReason)
    {
    case ERROR_PIN:
        printf("Missing value of multifunction pin !\n");
        break;
    case ERROR_BOARDNUMBER:
        printf("Missing number of board !\n");
        break;
    case ERROR_CONTROL:
        printf("Missing control byte !\n");
        break;
    default:
        break;
    }

    printf("Please using following format and values:\n");
    printf("Init32.exe /board:0 /control:0x88 /pin:0\n");
    printf("/board:     number of board\n");
    printf("/control:   control byte to initialize the specified board\n");
    printf("/pin:       Use of Multifunction pin\n");
    printf("Please refer readme.txt for detailed explanation\n");

   
    printf("Program aborted!\n");
}

void CheckErrorCode(int iErrorCode, int iLine)
{
    char pcErrorText[0xFF];

    if (iErrorCode != 1)
    {
        printf("Error in Line %d: ", iLine);
        me1400GetDrvErrMess(pcErrorText);
        printf("\t%s\n",pcErrorText);

        printf("\t%s\n",pcErrorText);
        printf("Possible reasons are:\n");
        printf("\t* This program runs only under a 32 bit Windows system\n");
        printf("\t  (Windows 9x / Windows NT)\n");
        printf("\t* 32 bit drivers must be installed beforehand properly\n");
        printf("\t* For 16 bit applications (i.e. MS DOS) use the 16 bit program\n");
        printf("\t* board number must be a valid number\n");
    }
}
