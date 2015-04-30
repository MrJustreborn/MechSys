
#include <stdio.h>
#include <windows.h>

#include "dll.h"

extern "C" {

/*--------------- new regular PCI API functions (without "_" prefix) --------------------*/

_declspec(dllexport) int _cdecl me6x00GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl me6x00GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl me6x00GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl me6x00GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl me6x00GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _cdecl me6x00GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl me6x00WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl me6x00ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl me6x00InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl me6x00OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl me6x00InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me6x00OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me6x00InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me6x00OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me6x00ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me6x00InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me6x00GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}






_declspec(dllexport) int _cdecl me6x00FrequencyToTimer(double dFreq)
{
    return meFrequencyToTimer(dFreq);
}




_declspec(dllexport) int _cdecl me6x00AOContinuous(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
    return meAOContinuous(iBoardNumber, iChannel, iSize, psBuffer);
}



_declspec(dllexport) int _cdecl me6x00AOContinuousEx(int iBoardNumber, int iChannel, int iSize, short *psBuffer, int iLoops, PVOID_PROC pCallback, VOID* pArgs)
{
    return meAOContinuousEx(iBoardNumber, iChannel, iSize, psBuffer, iLoops, pCallback, pArgs);
}



_declspec(dllexport) int _cdecl me6x00AOReset(int iBoardNumber, int iChannel)
{
    return meAOReset(iBoardNumber, iChannel);
}



_declspec(dllexport) int _cdecl me6x00AOResetAll(int iBoardNumber)
{
    return meAOResetAll(iBoardNumber);
}



_declspec(dllexport) int _cdecl me6x00AOSetTimer(int iBoardNumber, int iChannel, int iTicks)
{
    return meAOSetTimer(iBoardNumber, iChannel, iTicks);
}



_declspec(dllexport) int _cdecl me6x00AOSetTrigger(int iBoardNumber, int iChannel, int iModePolarity)
{
    return meAOSetTrigger(iBoardNumber, iChannel, iModePolarity);
}



_declspec(dllexport) int _cdecl me6x00AOSingle( int iBoardNumber, int iChannel, int iValue)
{
    return meAOSingle(iBoardNumber, iChannel, iValue);
}



_declspec(dllexport) int _cdecl me6x00AOStart(int iBoardNumber, int iChannel)
{
    return meAOStart(iBoardNumber, iChannel);
}



_declspec(dllexport) int _cdecl me6x00AOStop(int iBoardNumber, int iChannel)
{
    return meAOStop(iBoardNumber, iChannel);
}



_declspec(dllexport) int _cdecl me6x00AOStopEx(int iBoardNumber, int iChannel)
{
    return meAOStopEx(iBoardNumber, iChannel);
}



_declspec(dllexport) int _cdecl me6x00AOWaveGen(int iBoardNumber, int iChannel, int iShape, double dAmplitude, double dOffset, double dFreq)
{
    return meAOWaveGen(iBoardNumber, iChannel, iShape, dAmplitude, dOffset, dFreq);
}



_declspec(dllexport) int _cdecl me6x00AOWrapAround(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
    return meAOWrapAround(iBoardNumber, iChannel, iSize, psBuffer);
}








_declspec(dllexport) int _cdecl me6000GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl me6000GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl me6000GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl me6000GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl me6000GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _cdecl me6000GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl me6000WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl me6000ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl me6000InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl me6000OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl me6000InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me6000OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me6000InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me6000OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me6000ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me6000InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me6000GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}






_declspec(dllexport) int _cdecl me6000FrequencyToTimer(double dFreq)
{
    return meFrequencyToTimer(dFreq);
}




_declspec(dllexport) int _cdecl me6000AOContinuous(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
    return meAOContinuous(iBoardNumber, iChannel, iSize, psBuffer);
}



_declspec(dllexport) int _cdecl me6000AOContinuousEx(int iBoardNumber, int iChannel, int iSize, short *psBuffer, int iLoops, PVOID_PROC pCallback, VOID* pArgs)
{
    return meAOContinuousEx(iBoardNumber, iChannel, iSize, psBuffer, iLoops, pCallback, pArgs);
}



_declspec(dllexport) int _cdecl me6000AOReset(int iBoardNumber, int iChannel)
{
    return meAOReset(iBoardNumber, iChannel);
}



_declspec(dllexport) int _cdecl me6000AOResetAll(int iBoardNumber)
{
    return meAOResetAll(iBoardNumber);
}



_declspec(dllexport) int _cdecl me6000AOSetTimer(int iBoardNumber, int iChannel, int iTicks)
{
    return meAOSetTimer(iBoardNumber, iChannel, iTicks);
}



_declspec(dllexport) int _cdecl me6000AOSetTrigger(int iBoardNumber, int iChannel, int iModePolarity)
{
    return meAOSetTrigger(iBoardNumber, iChannel, iModePolarity);
}



_declspec(dllexport) int _cdecl me6000AOSingle( int iBoardNumber, int iChannel, int iValue)
{
    return meAOSingle(iBoardNumber, iChannel, iValue);
}



_declspec(dllexport) int _cdecl me6000AOStart(int iBoardNumber, int iChannel)
{
    return meAOStart(iBoardNumber, iChannel);
}



_declspec(dllexport) int _cdecl me6000AOStop(int iBoardNumber, int iChannel)
{
    return meAOStop(iBoardNumber, iChannel);
}



_declspec(dllexport) int _cdecl me6000AOStopEx(int iBoardNumber, int iChannel)
{
    return meAOStopEx(iBoardNumber, iChannel);
}



_declspec(dllexport) int _cdecl me6000AOWaveGen(int iBoardNumber, int iChannel, int iShape, double dAmplitude, double dOffset, double dFreq)
{
    return meAOWaveGen(iBoardNumber, iChannel, iShape, dAmplitude, dOffset, dFreq);
}



_declspec(dllexport) int _cdecl me6000AOWrapAround(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
    return meAOWrapAround(iBoardNumber, iChannel, iSize, psBuffer);
}


} // extern "C"
