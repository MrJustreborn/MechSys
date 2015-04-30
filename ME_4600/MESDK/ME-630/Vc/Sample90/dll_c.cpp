
#include <stdio.h>
#include <windows.h>

#include "dll.h"

extern "C" {

/*--------------- new regular PCI API functions (without "_" prefix) --------------------*/

_declspec(dllexport) int _cdecl me630GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl me630GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl me630GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl me630GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl me630GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _cdecl me630GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl me630WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl me630ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl me630InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl me630OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl me630InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me630OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me630InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me630OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me630ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me630InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me630EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, iContext);
}



_declspec(dllexport) int _cdecl me630DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}



_declspec(dllexport) int _cdecl me630GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}






_declspec(dllexport) int _cdecl me630ResetRelays(int iBoardNumber)
{
    return meResetRelays(iBoardNumber);
}



_declspec(dllexport) int _cdecl me630DIGetTTLBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    return meDIGetTTLBit(iBoardNumber, iBitNo, piBitValue);
}



_declspec(dllexport) int _cdecl me630DIGetTTLByte(int iBoardNumber, unsigned char *pcValue)
{
    return meDIGetTTLByte(iBoardNumber, pcValue);
}



_declspec(dllexport) int _cdecl me630DIGetOptoBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    return meDIGetOptoBit(iBoardNumber, iBitNo, piBitValue);
}



_declspec(dllexport) int _cdecl me630DIGetOptoByte(int iBoardNumber, unsigned char *pcValue)
{
    return meDIGetOptoByte(iBoardNumber, pcValue);
}



_declspec(dllexport) int _cdecl me630DOSetRelayBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    return meDOSetRelayBit(iBoardNumber, iBitNo, iBitValue);
}



_declspec(dllexport) int _cdecl me630DOSetRelayWord(int iBoardNumber, unsigned short usValue)
{
    return meDOSetRelayWord(iBoardNumber, usValue);
}



_declspec(dllexport) int _cdecl me630DIGetRelayBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    return meDIGetRelayBit(iBoardNumber, iBitNo, piBitValue);
}



_declspec(dllexport) int _cdecl me630DIGetRelayWord(int iBoardNumber, unsigned short *pusValue)
{
    return meDIGetRelayWord(iBoardNumber, pusValue);
}


_declspec(dllexport) int _cdecl me630DIOResetAll(int iBoardNumber)
{
    return meDIOResetAll(iBoardNumber);
}


_declspec(dllexport) int _cdecl me630DIOConfig(int iBoardNumber, int iPortNumber, int iPortDirection)
{
    return meDIOConfig(iBoardNumber, iPortNumber, iPortDirection);
}


_declspec(dllexport) int _cdecl me630DIOGetBit(int iBoardNumber, int iPortNumber, int iBitNo, int* piBitValue)
{
    return meDIOGetBit(iBoardNumber, iPortNumber, iBitNo, piBitValue);
}


_declspec(dllexport) int _cdecl me630DIOGetByte(int iBoardNumber, int iPortNumber, unsigned char* pucByteValue)
{
    return meDIOGetByte(iBoardNumber, iPortNumber, pucByteValue);
}


_declspec(dllexport) int _cdecl me630DIOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iBitValue)
{
    return meDIOSetBit(iBoardNumber, iPortNumber, iBitNo, iBitValue);
}


_declspec(dllexport) int _cdecl me630DIOSetByte(int iBoardNumber, int iPortNumber, unsigned char ucByteValue)
{
    return meDIOSetByte(iBoardNumber, iPortNumber, ucByteValue);
}


/*--------------- new PCI API functions with "_" prefix --------------------*/

_declspec(dllexport) int _cdecl _me630GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl _me630GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl _me630GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl _me630GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl _me630GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _cdecl _me630GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl _me630WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl _me630ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl _me630InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl _me630OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl _me630InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl _me630OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl _me630InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl _me630OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl _me630ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me630InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me630EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, iContext);
}



_declspec(dllexport) int _cdecl _me630DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}



_declspec(dllexport) int _cdecl _me630GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}






_declspec(dllexport) int _cdecl _me630ResetRelays(int iBoardNumber)
{
    return meResetRelays(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me630DIGetTTLBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    return meDIGetTTLBit(iBoardNumber, iBitNo, piBitValue);
}



_declspec(dllexport) int _cdecl _me630DIGetTTLByte(int iBoardNumber, unsigned char *pcValue)
{
    return meDIGetTTLByte(iBoardNumber, pcValue);
}



_declspec(dllexport) int _cdecl _me630DIGetOptoBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    return meDIGetOptoBit(iBoardNumber, iBitNo, piBitValue);
}



_declspec(dllexport) int _cdecl _me630DIGetOptoByte(int iBoardNumber, unsigned char *pcValue)
{
    return meDIGetOptoByte(iBoardNumber, pcValue);
}



_declspec(dllexport) int _cdecl _me630DOSetRelayBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    return meDOSetRelayBit(iBoardNumber, iBitNo, iBitValue);
}



_declspec(dllexport) int _cdecl _me630DOSetRelayWord(int iBoardNumber, unsigned short usValue)
{
    return meDOSetRelayWord(iBoardNumber, usValue);
}



_declspec(dllexport) int _cdecl _me630DIGetRelayBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    return meDIGetRelayBit(iBoardNumber, iBitNo, piBitValue);
}



_declspec(dllexport) int _cdecl _me630DIGetRelayWord(int iBoardNumber, unsigned short *pusValue)
{
    return meDIGetRelayWord(iBoardNumber, pusValue);
}




_declspec(dllexport) int _cdecl _me630DIOResetAll(int iBoardNumber)
{
    return meDIOResetAll(iBoardNumber);
}


_declspec(dllexport) int _cdecl _me630DIOConfig(int iBoardNumber, int iPortNumber, int iPortDirection)
{
    return meDIOConfig(iBoardNumber, iPortNumber, iPortDirection);
}


_declspec(dllexport) int _cdecl _me630DIOGetBit(int iBoardNumber, int iPortNumber, int iBitNo, int* piBitValue)
{
    return meDIOGetBit(iBoardNumber, iPortNumber, iBitNo, piBitValue);
}


_declspec(dllexport) int _cdecl _me630DIOGetByte(int iBoardNumber, int iPortNumber, unsigned char* pucByteValue)
{
    return meDIOGetByte(iBoardNumber, iPortNumber, pucByteValue);
}


_declspec(dllexport) int _cdecl _me630DIOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iBitValue)
{
    return meDIOSetBit(iBoardNumber, iPortNumber, iBitNo, iBitValue);
}


_declspec(dllexport) int _cdecl _me630DIOSetByte(int iBoardNumber, int iPortNumber, unsigned char ucByteValue)
{
    return meDIOSetByte(iBoardNumber, iPortNumber, ucByteValue);
}







/*--------------- ISA board routines for compatability with earlier versions --------------------*/

_declspec(dllexport) int _cdecl _me8xGetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl _me63Reset(int iBoardNumber)
{
    return meResetRelays(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me63DIGetBit(int iBoardNumber, int iBitNo, int *piValue)
{
    return meDIGetTTLBit(iBoardNumber, iBitNo, piValue);
}



_declspec(dllexport) int _cdecl _me63DIGetByte(int iBoardNumber, int* iValue)
{
    unsigned char uc_value;

    int i_error = meDIGetTTLByte(iBoardNumber, &uc_value);

    *iValue = (int)uc_value;

    return i_error;
}



_declspec(dllexport) int _cdecl _me63DOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    return meDOSetRelayBit(iBoardNumber, iBitNo, iBitValue);
}



_declspec(dllexport) int _cdecl _me63DOSetWord(int iBoardNumber, int iValue)
{
    return meDOSetRelayWord( iBoardNumber, (unsigned short)(iValue & 0xffff) );
}

} // extern "C"
