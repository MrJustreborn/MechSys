
#include <stdio.h>
#include <windows.h>

#include "dll.h"

extern "C" {

/*--------------- new regular PCI API functions (without "_" prefix) --------------------*/

_declspec(dllexport) int _cdecl me1400GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl me1400GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl me1400GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl me1400GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl me1400GetIrqCnt(int iBoardNumber, int *piIrqCnt)
{
    return meGetIrqCnt(iBoardNumber, /*iIRQNum*/ 3, piIrqCnt);
}



_declspec(dllexport) int _cdecl me1400GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl me1400WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl me1400ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl me1400InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl me1400OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl me1400InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me1400OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me1400InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me1400OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me1400ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me1400InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me1400EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc, int iIRQNum)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, 0 /*iContext*/);
}



_declspec(dllexport) int _cdecl me1400DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}



_declspec(dllexport) int _cdecl me1400GetDrvErrMess(char *pcErrortext)
{
    return meGetDrvErrMess(pcErrortext, 64 /*iBufferSize*/);
}






_declspec(dllexport) int _cdecl me1400CntInitSrc(int iBoardNumber, int iCounter, int iCounterSource)
{
    return meCntInitSrc(iBoardNumber, iCounter, iCounterSource);
}



_declspec(dllexport) int _cdecl me1400CntWrite(int iBoardNumber, int iCounter, int iMode, int iValue)
{
    return meCntWrite(iBoardNumber, iCounter, iMode, iValue);
}



_declspec(dllexport) int _cdecl me1400CntRead(int iBoardNumber, int iCounter, int* piValue)
{
    return meCntRead(iBoardNumber, iCounter, piValue);
}



_declspec(dllexport) int _cdecl me1400DIOSetMode(int iBoardNumber, int iPio, int iMode)
{
    return meDIOSetMode(iBoardNumber, iPio, iMode);
}



_declspec(dllexport) int _cdecl me1400DIOSetPortDirection(int iBoardNumber, int iPort, int iDir)
{
    return meDIOSetPortDirection(iBoardNumber, iPort, iDir);
}



_declspec(dllexport) int _cdecl me1400DIGetBit(int iBoardNumber, int iPort, int iBitNo, int *piValue)
{
    return meDIGetBit(iBoardNumber, iPort, iBitNo, piValue);
}



_declspec(dllexport) int _cdecl me1400DOSetBit(int iBoardNumber, int iPort, int iBitNo, int iBitValue)
{
    return meDOSetBit(iBoardNumber, iPort, iBitNo, iBitValue);
}



_declspec(dllexport) int _cdecl me1400DIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
    return meDIGetByte(iBoardNumber, iPortNo, piValue);
}



_declspec(dllexport) int _cdecl me1400DOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
    return meDOSetByte(iBoardNumber, iPortNo, iValue);
}



_declspec(dllexport) int _cdecl me1400InitModeTimerA(int iBoardNumber, int iCtrlWordA)
{
    return meInitModeTimerA(iBoardNumber, iCtrlWordA);
}



_declspec(dllexport) int _cdecl me1400InitModeTimerB(int iBoardNumber, int iCtrlWordB)
{
    return meInitModeTimerB(iBoardNumber, iCtrlWordB);
}



_declspec(dllexport) int _cdecl me1400SetMultifunctionPin(int iBoardNumber, int MultiPin)
{
    return meSetMultifunctionPin(iBoardNumber, MultiPin);
}




/*--------------- new PCI API functions with "_" prefix --------------------*/

_declspec(dllexport) int _cdecl _me1400GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl _me1400GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl _me1400GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl _me1400GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl _me1400GetIrqCnt(int iBoardNumber, int *piIrqCnt)
{
    return meGetIrqCnt(iBoardNumber, 3 /*iIRQNum*/, piIrqCnt);
}



_declspec(dllexport) int _cdecl _me1400GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl _me1400WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl _me1400ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl _me1400InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl _me1400OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl _me1400InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl _me1400OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl _me1400InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl _me1400OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl _me1400ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me1400InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me1400EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc, int iIRQNum)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, 0 /*iContext*/);
}



_declspec(dllexport) int _cdecl _me1400DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}



_declspec(dllexport) int _cdecl _me1400GetDrvErrMess(char *pcErrortext)
{
    return meGetDrvErrMess(pcErrortext, 64 /*iBufferSize*/);
}






_declspec(dllexport) int _cdecl _me1400CntWrite(int iBoardNumber, int iCounter, int iMode, int iValue)
{
    return meCntWrite(iBoardNumber, iCounter, iMode, iValue);
}



_declspec(dllexport) int _cdecl _me1400CntRead(int iBoardNumber, int iCounter, int* piValue)
{
    return meCntRead(iBoardNumber, iCounter, piValue);
}



_declspec(dllexport) int _cdecl _me1400DIOSetMode(int iBoardNumber, int iPio, int iMode)
{
    return meDIOSetMode(iBoardNumber, iPio, iMode);
}



_declspec(dllexport) int _cdecl _me1400DIOSetPortDirection(int iBoardNumber, int iPort, int iDir)
{
    return meDIOSetPortDirection(iBoardNumber, iPort, iDir);
}



_declspec(dllexport) int _cdecl _me1400DIGetBit(int iBoardNumber, int iPort, int iBitNo, int *piValue)
{
    return meDIGetBit(iBoardNumber, iPort, iBitNo, piValue);
}



_declspec(dllexport) int _cdecl _me1400DOSetBit(int iBoardNumber, int iPort, int iBitNo, int iBitValue)
{
    return meDOSetBit(iBoardNumber, iPort, iBitNo, iBitValue);
}



_declspec(dllexport) int _cdecl _me1400DIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
    return meDIGetByte(iBoardNumber, iPortNo, piValue);
}



_declspec(dllexport) int _cdecl _me1400DOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
    return meDOSetByte(iBoardNumber, iPortNo, iValue);
}



_declspec(dllexport) int _cdecl _me1400InitModeTimerA(int iBoardNumber, int iCtrlWordA)
{
    return meInitModeTimerA(iBoardNumber, iCtrlWordA);
}



_declspec(dllexport) int _cdecl _me1400InitModeTimerB(int iBoardNumber, int iCtrlWordB)
{
    return meInitModeTimerB(iBoardNumber, iCtrlWordB);
}



_declspec(dllexport) int _cdecl _me1400SetMultifunctionPin(int iBoardNumber, int MultiPin)
{
    return meSetMultifunctionPin(iBoardNumber, MultiPin);
}



/*--------------- ISA board routines for compatability with earlier versions --------------------*/

_declspec(dllexport) int _cdecl _me14GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl _me14BoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl _me14EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc, int iIRQNum)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, 0 /*iContext*/);
}



_declspec(dllexport) int _cdecl _me14DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}



_declspec(dllexport) int _cdecl _me14GetDrvErrMess(char *pcErrortext)
{
    return meGetDrvErrMess(pcErrortext, 64 /*iBufferSize*/);
}



_declspec(dllexport) int _cdecl _me14InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl _me14OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl _me14InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl _me14OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl _me14CntWrite(int iBoardNumber, int iCounter,int iMode, int iValue)
{
    return meCntWrite(iBoardNumber, iCounter, iMode, iValue);
}



_declspec(dllexport) int _cdecl _me14CntRead(int iBoardNumber, int iCounter, int* piValue)
{
    return meCntRead(iBoardNumber, iCounter, piValue);
}



_declspec(dllexport) int _cdecl _me14DIOSetMode(int iBoardNumber,int iPio, int iMode)
{
    return meDIOSetMode(iBoardNumber, iPio, iMode);
}



_declspec(dllexport) int _cdecl _me14DIOSetPortDirection(int iBoardNumber, int iPort, int iDir)
{
    return meDIOSetPortDirection(iBoardNumber, iPort, iDir);
}



int _declspec(dllexport) _cdecl _me14DIGetBit(int iBoardNumber, int iPort,int iBitNo, int *piValue)
{
    return meDIGetBit(iBoardNumber, iPort, iBitNo, piValue);
}



int _declspec(dllexport) _cdecl _me14DIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
    return meDIGetByte(iBoardNumber, iPortNo, piValue);
}



int _declspec(dllexport) _cdecl _me14DOSetBit(int iBoardNumber,int iPort, int iBitNo, int iBitValue)
{
    return meDOSetBit(iBoardNumber, iPort, iBitNo, iBitValue);
}



int _declspec(dllexport) _cdecl _me14DOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
    return meDOSetByte(iBoardNumber, iPortNo, iValue);
}




// wrong name in the old driver:
_declspec(dllexport) int _cdecl me1400BoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl _me1400BoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}

} // extern "C"
