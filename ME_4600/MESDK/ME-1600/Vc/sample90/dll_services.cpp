
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






int meAOSetMode(int iBoardNumber, int iChannelGroup, int iOutMode)
{
    iChannelGroup, iOutMode;

    return TRUE;
}



int meAOSetRange(int iBoardNumber, int iChannelNumber, int iRange)
{
    iChannelNumber, iRange;

    return TRUE;
}



int meAOSingle(int iBoardNumber, int iChannelNumber, short iValue)
{
    iChannelNumber, iValue;

    return TRUE;
}



int meAOUpdate(int iBoardNumber, int iChannelGroup)
{
    iChannelGroup;

    return TRUE;
}



int meAOUpdateAll(int iBoardNumber)
{
    return TRUE;
}



int meAOSetCurrent(int iBoardNumber, int iChannelNumber, int iCurrentMode, int iRange)
{
    iChannelNumber, iCurrentMode, iRange;

    return TRUE;
}
