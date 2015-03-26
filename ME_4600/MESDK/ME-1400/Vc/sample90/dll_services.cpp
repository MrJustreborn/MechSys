
#include <stdio.h>
#include <windows.h>

#include "dll.h"



int meGetDLLVersion()
{
    OutputDebugString("DLL : meGetDLLVersion\n");

    return 0x00090099;
}



int meGetDriverVersion(int *piDriverVersion)
{
    OutputDebugString("DLL : meGetDriverVersion\n");

    *piDriverVersion = 0x00090098;

    return TRUE;
}



int meGetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    OutputDebugString("DLL : meGetBoardVersion\n");

    *piBoardVersion = 0x00090097;

    return TRUE;
}



int meGetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    OutputDebugString("DLL : meGetSerialNumber\n");

    *piSerialNumber = 0x00090096;

    return TRUE;
}



int meGetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    OutputDebugString("DLL : meGetIrqCnt\n");

    *piCnt = 0;

    return TRUE;
}



int meGetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
	char szMsg[128];
	wsprintf(szMsg, "\tiBoardNumber: 0x%d", iBoardNumber);
    OutputDebugString("DLL : meGetDevInfo\n");
	OutputDebugString(szMsg);
    

    pDevInfo;

    return TRUE;
}



int meWriteUserString(int iBoardNumber, char* pcUserText)
{
    OutputDebugString("DLL : meWriteUserString\n");

    pcUserText;

    return TRUE;
}



int meReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    OutputDebugString("DLL : meReadUserString\n");

    pcUserText, iMaxLength;

    return TRUE;
}



int meInportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    OutputDebugString("DLL : meInportByte\n");

    iPortOffset, pbValue;

    return TRUE;
}



int meOutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    OutputDebugString("DLL : meOutportByte\n");

    iPortOffset, bValue;

    return TRUE;
}



int meInportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    OutputDebugString("DLL : meInportWord\n");

    iPortOffset, pwValue;

    return TRUE;
}



int meOutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    OutputDebugString("DLL : meOutportWord\n");

    iPortOffset, wValue;

    return TRUE;
}



int meInportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    OutputDebugString("DLL : meInportDWord\n");

    iPortOffset, pwValue;

    return TRUE;
}



int meOutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    OutputDebugString("DLL : meOutportDWord\n");

    iPortOffset, wValue;

    return TRUE;
}



int meResetBoard(int iBoardNumber)
{
    OutputDebugString("DLL : meResetBoard\n");

    return TRUE;
}



int meInitBoard(int iBoardNumber)
{
    OutputDebugString("DLL : meInitBoard\n");

    return TRUE;
}



int meEnableInt(int iBoardNumber, int iIRQNum, PSERVICE_PROC IrqFunc, int iContext)
{
    OutputDebugString("DLL : meEnableInt\n");

    iIRQNum, IrqFunc, iContext;

    return TRUE;
}



int meDisableInt(int iBoardNumber, int iIRQNum)
{
    OutputDebugString("DLL : meDisableInt\n");

    iIRQNum;

    return TRUE;
}



int meGetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    OutputDebugString("DLL : meGetDrvErrMess\n");

    pcErrortext[0] = 0;

    return TRUE;
}







int meCntInitSrc(int iBoardNumber, int iCounter, int iCounterSource)
{
    OutputDebugString("DLL : meCntInitSrc\n");

    iCounter, iCounterSource;
    return TRUE;
}



int meCntWrite(int iBoardNumber, int iCounter, int iMode, int iValue)
{
    OutputDebugString("DLL : meCntWrite\n");

    iCounter, iMode, iValue;
    return TRUE;
}



int meCntRead(int iBoardNumber, int iCounter, int* piValue)
{
    OutputDebugString("DLL : meCntRead\n");

    iCounter, piValue;
    return TRUE;
}



int meDIOSetMode(int iBoardNumber, int iPio, int iMode)
{
    OutputDebugString("DLL : meDIOSetMode\n");

    return false;
}



int meDIOSetPortDirection(int iBoardNumber, int iPort, int iDir)
{
    OutputDebugString("DLL : meDIOSetPortDirection\n");

    iPort, iDir;
    return TRUE;
}



int meDIGetBit(int iBoardNumber, int iPort, int iBitNo, int *piValue)
{
    OutputDebugString("DLL : meDIGetBit\n");

    iPort,iBitNo, piValue;
    return TRUE;
}



int meDOSetBit(int iBoardNumber, int iPort, int iBitNo, int iBitValue)
{
    OutputDebugString("DLL : meDOSetBit\n");

    iPort, iBitNo, iBitValue;
    return TRUE;
}



int meDIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
    OutputDebugString("DLL : meDIGetByte\n");

    iPortNo, piValue;
    return TRUE;
}



int meDOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
    OutputDebugString("DLL : meDOSetByte\n");

    iPortNo, iValue;
    return TRUE;
}



int meInitModeTimerA(int iBoardNumber, int iCtrlWordA)
{
    OutputDebugString("DLL : meInitModeTimerA\n");

    iCtrlWordA;
    return TRUE;
}



int meInitModeTimerB(int iBoardNumber, int iCtrlWordB)
{
    OutputDebugString("DLL : meInitModeTimerB\n");

    iCtrlWordB;
    return TRUE;
}



int meSetMultifunctionPin(int iBoardNumber, int MultiPin)
{
    OutputDebugString("DLL : meSetMultifunctionPin\n");

    MultiPin;
    return TRUE;
}
