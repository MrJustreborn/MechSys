/*------------------------------------------------------------------------------+
|  Source File:    dll_pascal.cpp                                               |
|  Destination:    me6x00.dll                                                   |
|  Compiler:       Visual C++ 6.0                                               |
|  Authors:        KRH(Keith Hartley), SW(Stefan Weidlich), AB(Andreas Bernau)  |
|                                                                               |
|  Description:    Meilhaus DLL for user mode (ring 3)                          |
|                                                                               |
|  File History:   Version      Date        Editor  Action                      |
+-------------------------------------------------------------------------------+
|                  1.00.00      011016      SW      first release               |
|                  1.00.08      240102      SW      first complete release      |
|                                                                               |
+-------------------------------------------------------------------------------+
|                                                                               |
|  Description:                                                                 |
|                                                                               |
|       Contains the Pascal API interface to the DLL.                           |
|                                                                               |
+------------------------------------------------------------------------------*/


#include <stdio.h>
#include <windows.h>

#include "dll.h"

extern "C" {

/*--------------- new regular PCI API functions (without "_" prefix) --------------------*/

_declspec(dllexport) int _stdcall VBme6x00GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _stdcall VBme6x00GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _stdcall VBme6x00GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _stdcall VBme6x00GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _stdcall VBme6x00GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _stdcall VBme6x00GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _stdcall VBme6x00WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _stdcall VBme6x00ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _stdcall VBme6x00InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _stdcall VBme6x00OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _stdcall VBme6x00InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _stdcall VBme6x00OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _stdcall VBme6x00InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _stdcall VBme6x00OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _stdcall VBme6x00ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme6x00InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme6x00GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}



_declspec(dllexport) int _stdcall VBme6x00FrequencyToTimer(double dFreq)
{
    return meFrequencyToTimer(dFreq);
}



_declspec(dllexport) int _stdcall VBme6x00AOContinuous(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
    return meAOContinuous(iBoardNumber,iChannel, iSize, psBuffer);
}



_declspec(dllexport) int _stdcall VBme6x00AOContinuousEx(int iBoardNumber, int iChannel, int iSize, short *psBuffer, int iLoops, PVOID_PROC pCallback, VOID* pArgs)
{
    return meAOContinuousEx(iBoardNumber, iChannel, iSize, psBuffer, iLoops, pCallback, pArgs);
}



_declspec(dllexport) int _stdcall VBme6x00AOReset(int iBoardNumber, int iChannel)
{
    return meAOReset(iBoardNumber, iChannel);
}



_declspec(dllexport) int _stdcall VBme6x00AOResetAll(int iBoardNumber)
{
    return meAOResetAll(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme6x00AOSetTimer(int iBoardNumber, int iChannel, int iTicks)
{
    return meAOSetTimer(iBoardNumber, iChannel, iTicks);
}



_declspec(dllexport) int _stdcall VBme6x00AOSetTrigger(int iBoardNumber, int iChannel, int iModePolarity)
{
    return meAOSetTrigger(iBoardNumber, iChannel, iModePolarity);
}



_declspec(dllexport) int _stdcall VBme6x00AOSingle( int iBoardNumber, int iChannel, int iValue)
{
    return meAOSingle( iBoardNumber, iChannel, iValue);
}



_declspec(dllexport) int _stdcall VBme6x00AOStart(int iBoardNumber, int iChannel)
{
    return meAOStart(iBoardNumber, iChannel);
}



_declspec(dllexport) int _stdcall VBme6x00AOStop(int iBoardNumber, int iChannel)
{
    return meAOStop(iBoardNumber, iChannel);
}



_declspec(dllexport) int _stdcall VBme6x00AOStopEx(int iBoardNumber, int iChannel)
{
    return meAOStopEx(iBoardNumber, iChannel);
}



_declspec(dllexport) int _stdcall VBme6x00AOWaveGen(int iBoardNumber, int iChannel, int iShape, double dAmplitude, double dOffset, double dFreq)
{
    return meAOWaveGen(iBoardNumber, iChannel, iShape, dAmplitude, dOffset, dFreq);
}



_declspec(dllexport) int _stdcall VBme6x00AOWrapAround(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
    return meAOWrapAround(iBoardNumber, iChannel, iSize, psBuffer);
}





_declspec(dllexport) int _stdcall VBme6000GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _stdcall VBme6000GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _stdcall VBme6000GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _stdcall VBme6000GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _stdcall VBme6000GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _stdcall VBme6000GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _stdcall VBme6000WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _stdcall VBme6000ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _stdcall VBme6000InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _stdcall VBme6000OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _stdcall VBme6000InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _stdcall VBme6000OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _stdcall VBme6000InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _stdcall VBme6000OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _stdcall VBme6000ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme6000InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme6000GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}



_declspec(dllexport) int _stdcall VBme6000FrequencyToTimer(double dFreq)
{
    return meFrequencyToTimer(dFreq);
}



_declspec(dllexport) int _stdcall VBme6000AOContinuous(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
    return meAOContinuous(iBoardNumber,iChannel, iSize, psBuffer);
}



_declspec(dllexport) int _stdcall VBme6000AOContinuousEx(int iBoardNumber, int iChannel, int iSize, short *psBuffer, int iLoops, PVOID_PROC pCallback, VOID* pArgs)
{
    return meAOContinuousEx(iBoardNumber, iChannel, iSize, psBuffer, iLoops, pCallback, pArgs);
}



_declspec(dllexport) int _stdcall VBme6000AOReset(int iBoardNumber, int iChannel)
{
    return meAOReset(iBoardNumber, iChannel);
}



_declspec(dllexport) int _stdcall VBme6000AOResetAll(int iBoardNumber)
{
    return meAOResetAll(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme6000AOSetTimer(int iBoardNumber, int iChannel, int iTicks)
{
    return meAOSetTimer(iBoardNumber, iChannel, iTicks);
}



_declspec(dllexport) int _stdcall VBme6000AOSetTrigger(int iBoardNumber, int iChannel, int iModePolarity)
{
    return meAOSetTrigger(iBoardNumber, iChannel, iModePolarity);
}



_declspec(dllexport) int _stdcall VBme6000AOSingle( int iBoardNumber, int iChannel, int iValue)
{
    return meAOSingle( iBoardNumber, iChannel, iValue);
}



_declspec(dllexport) int _stdcall VBme6000AOStart(int iBoardNumber, int iChannel)
{
    return meAOStart(iBoardNumber, iChannel);
}



_declspec(dllexport) int _stdcall VBme6000AOStop(int iBoardNumber, int iChannel)
{
    return meAOStop(iBoardNumber, iChannel);
}



_declspec(dllexport) int _stdcall VBme6000AOStopEx(int iBoardNumber, int iChannel)
{
    return meAOStopEx(iBoardNumber, iChannel);
}



_declspec(dllexport) int _stdcall VBme6000AOWaveGen(int iBoardNumber, int iChannel, int iShape, double dAmplitude, double dOffset, double dFreq)
{
    return meAOWaveGen(iBoardNumber, iChannel, iShape, dAmplitude, dOffset, dFreq);
}



_declspec(dllexport) int _stdcall VBme6000AOWrapAround(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
    return meAOWrapAround(iBoardNumber, iChannel, iSize, psBuffer);
}
} // extern "C"
