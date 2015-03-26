
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






int meDIOSetPortDirection(int iBoardNumber, int iPortNumber, int iDirection)
{
    iPortNumber, iDirection;
    return TRUE;
}



int meDIOReset(int iBoardNumber)
{
    return TRUE;
}



int meDIGetBit(int iBoardNumber, int iPortNumber,  int iBitNo, int *piValue)
{
    iPortNumber, iBitNo, piValue;
    return TRUE;
}



int meDIGetByte(int iBoardNumber, int iPortNumber, int iByteNo, int *piValue)
{
    iPortNumber, iByteNo, piValue;
    return TRUE;
}



int meDIGetWord(int iBoardNumber, int iPortNumber, int iWordNo, int *piValue)
{
    iPortNumber, iWordNo, piValue;
    return TRUE;
}



int meDIGetLong(int iBoardNumber, int iPortNumber, int *piValue)
{
    iPortNumber, piValue;
    return TRUE;
}



int meDOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iValue)
{
    iPortNumber, iBitNo, iValue;
    return TRUE;
}



int meDOSetByte(int iBoardNumber, int iPortNumber, int iByteNo, int iValue)
{
    iPortNumber, iByteNo, iValue;
    return TRUE;
}



int meDOSetWord(int iBoardNumber, int iPortNumber, int iWordNo, int iValue)
{
    iPortNumber, iWordNo, iValue;
    return TRUE;
}



int meDOSetLong(int iBoardNumber, int iPortNumber, int iValue)
{
    iPortNumber, iValue;
    return TRUE;
}
