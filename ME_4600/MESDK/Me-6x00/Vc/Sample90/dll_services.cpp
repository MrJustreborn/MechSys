
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



int meGetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    pcErrortext[0] = 0;

    return TRUE;
}



int meFrequencyToTimer(double dFreq)
{
    return 66;
}



int meAOContinuous(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
    iChannel;
    iSize;
    psBuffer;

    return TRUE;
}



int meAOContinuousEx(int iBoardNumber, int iChannel, int iSize, short *psBuffer,
                     int iLoops, PVOID_PROC pCallback, VOID* pArgs)
{
    iChannel;
    iSize;
    psBuffer;
    iLoops;
    pCallback;
    pArgs;

    return TRUE;
}



int meAOReset(int iBoardNumber, int iChannel)
{
    iChannel;

    return TRUE;
}



int meAOResetAll(int iBoardNumber)
{
    return TRUE;
}



int meAOSetTimer(int iBoardNumber, int iChannel, int iTicks)
{
    iChannel;
    iTicks;

    return TRUE;
}



int meAOSetTrigger(int iBoardNumber, int iChannel, int iModePolarity)
{
    iChannel;
    iModePolarity;

    return TRUE;
}



int meAOSingle(int iBoardNumber, int iChannel, int iValue)
{
    iChannel;
    iValue;

    return TRUE;
}



int meAOStart(int iBoardNumber, int iChannel)
{
    iChannel;

    return TRUE;
}



int meAOStop(int iBoardNumber, int iChannel)
{
    iChannel;

    return TRUE;
}



int meAOStopEx(int iBoardNumber, int iChannel)
{
    iChannel;

    return TRUE;
}



int meAOWaveGen(int iBoardNumber, int iChannel, int iShape, double dAmplitude,
                double dOffset, double dFreq)
{
    iChannel;
    iShape;
    dAmplitude;
    dOffset;
    dFreq;

    return TRUE;
}



int meAOWrapAround(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
    iChannel;
    iSize;
    psBuffer;

    return TRUE;
}
