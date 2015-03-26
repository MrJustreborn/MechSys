
#include <stdio.h>
#include <windows.h>

#include "dll.h"



int meGetDLLVersion()
{
    return 0x00090099;
}



int meGetDriverVersion(int *piDriverVersion)
{
    *piDriverVersion = 0x00090098;

    return TRUE;
}



int meGetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    *piBoardVersion = 0x00090097;

    return TRUE;
}



int meGetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    *piSerialNumber = 0x00090096;

    return TRUE;
}



int meGetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    *piCnt = 0;

    return TRUE;
}



int meGetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    pDevInfo;

    return TRUE;
}



int meWriteUserString(int iBoardNumber, char* pcUserText)
{
    pcUserText;

    return TRUE;
}



int meReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    pcUserText, iMaxLength;

    return TRUE;
}



int meInportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    iPortOffset, pbValue;

    return TRUE;
}



int meOutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    iPortOffset, bValue;

    return TRUE;
}



int meInportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    iPortOffset, pwValue;

    return TRUE;
}



int meOutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    iPortOffset, wValue;

    return TRUE;
}



int meInportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    iPortOffset, pwValue;

    return TRUE;
}



int meOutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    iPortOffset, wValue;

    return TRUE;
}



int meResetBoard(int iBoardNumber)
{
    return TRUE;
}



int meInitBoard(int iBoardNumber)
{
    return TRUE;
}



int meEnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    iIRQNum, IrqFunc, iContext;
    return TRUE;
}



int meDisableInt(int iBoardNumber, int iIRQNum)
{
    iIRQNum;

    return TRUE;
}



int meGetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    pcErrortext[0] = 0;

    return TRUE;
}






int mePROMVersion(int iBoardNumber, int *piVersion)
{
    piVersion;
    return TRUE;
}



int meDIGetIntStatus(int iBoardNumber, int iRegisterSet, int *piValue)
{
    iRegisterSet, piValue;
    return TRUE;
}



int meDIOSetIntMode(int iBoardNumber, int iRegisterSet, int iMode)
{
    iRegisterSet, iMode;
    return TRUE;
}



int meDIOSetTristateON(int iBoardNumber, int iRegisterSet)
{
    iRegisterSet;
    return TRUE;
}



int meDIOSetTristateOFF(int iBoardNumber, int iRegisterSet)
{
    iRegisterSet;
    return TRUE;
}



int meDIOSetPattern(int iBoardNumber, int iRegisterSet, int iPattern)
{
    iRegisterSet, iPattern;
    return TRUE;
}



int meDIOSetMask(int iBoardNumber, int iRegisterSet, int iMask)
{
    iRegisterSet, iMask;
    return TRUE;
}



// Digital I/O Input-Functions
int meDIGetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int *piBitValue)
{
    iRegisterSet, iBitNo, piBitValue;
    return TRUE;
}



int meDIGetWord(int iBoardNumber, int iRegisterSet, int *piValue)
{
    iRegisterSet, piValue ;
    return TRUE;
}



// Digital I/O Output-Functions
int meDOSetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int iBitValue)
{
    iRegisterSet, iBitNo, iBitValue;
    return TRUE;
}



int meDOSetWord(int iBoardNumber, int iRegisterSet, int iValue)
{
    iRegisterSet, iValue;
    return TRUE;
}



// Counter 8254 functions
int meCntWrite(int iBoardNumber, int iCounter, int iMode, int iValue)
{
    iCounter, iMode, iValue;
    return TRUE;
}



int meCntRead(int iBoardNumber, int iCounter, int* piValue)
{
    iCounter, piValue;
    return TRUE;
}



int meSetSinkSourceMode(int iBoardNumber, int iRegisterSet, int iMode)
{
    iRegisterSet, iMode;
    return TRUE;
}
