
#include <stdio.h>
#include <windows.h>

#include "dll.h"

extern "C" {

/*--------------- new regular PCI API functions (without "_" prefix) --------------------*/

_declspec(dllexport) int _cdecl me1000GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl me1000GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl me1000GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl me1000GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl me1000GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _cdecl me1000GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl me1000WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl me1000ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl me1000InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl me1000OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl me1000InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me1000OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me1000InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me1000OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me1000ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me1000InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me1000EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, iContext);
}



_declspec(dllexport) int _cdecl me1000DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}



_declspec(dllexport) int _cdecl me1000GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}



_declspec(dllexport) int _cdecl me1000DIOSetPortDirection(int iBoardNumber, int iPortNumber, int iDirection)
{
    return meDIOSetPortDirection(iBoardNumber, iPortNumber, iDirection);
}



_declspec(dllexport) int _cdecl me1000DIOReset(int iBoardNumber)
{
    return meDIOReset(iBoardNumber);
}



_declspec(dllexport) int _cdecl me1000DIGetBit(int iBoardNumber, int iPortNumber,  int iBitNo, int *piValue)
{
    return meDIGetBit(iBoardNumber, iPortNumber, iBitNo, piValue);
}



_declspec(dllexport) int _cdecl me1000DIGetByte(int iBoardNumber, int iPortNumber, int iByteNo, int *piValue)
{
    return meDIGetByte(iBoardNumber, iPortNumber, iByteNo, piValue);
}



_declspec(dllexport) int _cdecl me1000DIGetWord(int iBoardNumber, int iPortNumber, int iWordNo, int *piValue)
{
    return meDIGetWord(iBoardNumber, iPortNumber, iWordNo, piValue);
}



_declspec(dllexport) int _cdecl me1000DIGetLong(int iBoardNumber, int iPortNumber, int *piValue)
{
    return meDIGetLong(iBoardNumber, iPortNumber, piValue);
}



_declspec(dllexport) int _cdecl me1000DOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iValue)
{
    return meDOSetBit(iBoardNumber, iPortNumber, iBitNo, iValue);
}



_declspec(dllexport) int _cdecl me1000DOSetByte(int iBoardNumber, int iPortNumber, int iByteNo, int iValue)
{
    return meDOSetByte(iBoardNumber, iPortNumber, iByteNo, iValue);
}



_declspec(dllexport) int _cdecl me1000DOSetWord(int iBoardNumber, int iPortNumber, int iWordNo, int iValue)
{
    return meDOSetWord(iBoardNumber, iPortNumber, iWordNo, iValue);
}



_declspec(dllexport) int _cdecl me1000DOSetLong(int iBoardNumber, int iPortNumber, int iValue)
{
    return meDOSetLong(iBoardNumber, iPortNumber, iValue);
}





/*--------------- new regular PCI API functions (without "_" prefix) --------------------*/

_declspec(dllexport) int _cdecl _me1000GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl _me1000GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl _me1000GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl _me1000GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl _me1000GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _cdecl _me1000GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl _me1000WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl _me1000ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl _me1000InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl _me1000OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl _me1000InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl _me1000OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl _me1000InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl _me1000OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl _me1000ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me1000InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me1000EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, iContext);
}



_declspec(dllexport) int _cdecl _me1000DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}



_declspec(dllexport) int _cdecl _me1000GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}



_declspec(dllexport) int _cdecl _me1000DIOSetPortDirection(int iBoardNumber, int iPortNumber, int iDirection)
{
    return meDIOSetPortDirection(iBoardNumber, iPortNumber, iDirection);
}



_declspec(dllexport) int _cdecl _me1000DIOReset(int iBoardNumber)
{
    return meDIOReset(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me1000DIGetBit(int iBoardNumber, int iPortNumber,  int iBitNo, int *piValue)
{
    return meDIGetBit(iBoardNumber, iPortNumber, iBitNo, piValue);
}



_declspec(dllexport) int _cdecl _me1000DIGetByte(int iBoardNumber, int iPortNumber, int iByteNo, int *piValue)
{
    return meDIGetByte(iBoardNumber, iPortNumber, iByteNo, piValue);
}



_declspec(dllexport) int _cdecl _me1000DIGetWord(int iBoardNumber, int iPortNumber, int iWordNo, int *piValue)
{
    return meDIGetWord(iBoardNumber, iPortNumber, iWordNo, piValue);
}



_declspec(dllexport) int _cdecl _me1000DIGetLong(int iBoardNumber, int iPortNumber, int *piValue)
{
    return meDIGetLong(iBoardNumber, iPortNumber, piValue);
}



_declspec(dllexport) int _cdecl _me1000DOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iValue)
{
    return meDOSetBit(iBoardNumber, iPortNumber, iBitNo, iValue);
}



_declspec(dllexport) int _cdecl _me1000DOSetByte(int iBoardNumber, int iPortNumber, int iByteNo, int iValue)
{
    return meDOSetByte(iBoardNumber, iPortNumber, iByteNo, iValue);
}



_declspec(dllexport) int _cdecl _me1000DOSetWord(int iBoardNumber, int iPortNumber, int iWordNo, int iValue)
{
    return meDOSetWord(iBoardNumber, iPortNumber, iWordNo, iValue);
}



_declspec(dllexport) int _cdecl _me1000DOSetLong(int iBoardNumber, int iPortNumber, int iValue)
{
    return meDOSetLong(iBoardNumber, iPortNumber, iValue);
}

} // extern "C"
