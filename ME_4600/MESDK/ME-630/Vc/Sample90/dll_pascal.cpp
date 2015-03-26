
#include <stdio.h>
#include <windows.h>

#include "dll.h"

extern "C" {

/*--------------- new regular PCI API functions (without "_" prefix) --------------------*/

_declspec(dllexport) int _stdcall VBme630GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _stdcall VBme630GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _stdcall VBme630GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _stdcall VBme630GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _stdcall VBme630GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _stdcall VBme630GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _stdcall VBme630WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _stdcall VBme630ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _stdcall VBme630InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _stdcall VBme630OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _stdcall VBme630InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _stdcall VBme630OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _stdcall VBme630InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _stdcall VBme630OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _stdcall VBme630ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme630InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme630EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, iContext);
}



_declspec(dllexport) int _stdcall VBme630DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}



_declspec(dllexport) int _stdcall VBme630GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}






_declspec(dllexport) int _stdcall VBme630ResetRelays(int iBoardNumber)
{
    return meResetRelays(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme630DIGetTTLBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    return meDIGetTTLBit(iBoardNumber, iBitNo, piBitValue);
}



_declspec(dllexport) int _stdcall VBme630DIGetTTLByte(int iBoardNumber, unsigned char *pcValue)
{
    return meDIGetTTLByte(iBoardNumber, pcValue);
}



_declspec(dllexport) int _stdcall VBme630DIGetOptoBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    return meDIGetOptoBit(iBoardNumber, iBitNo, piBitValue);
}



_declspec(dllexport) int _stdcall VBme630DIGetOptoByte(int iBoardNumber, unsigned char *pcValue)
{
    return meDIGetOptoByte(iBoardNumber, pcValue);
}



_declspec(dllexport) int _stdcall VBme630DOSetRelayBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    return meDOSetRelayBit(iBoardNumber, iBitNo, iBitValue);
}



_declspec(dllexport) int _stdcall VBme630DOSetRelayWord(int iBoardNumber, unsigned short usValue)
{
    return meDOSetRelayWord(iBoardNumber, usValue);
}



_declspec(dllexport) int _stdcall VBme630DIGetRelayBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    return meDIGetRelayBit(iBoardNumber, iBitNo, piBitValue);
}



_declspec(dllexport) int _stdcall VBme630DIGetRelayWord(int iBoardNumber, unsigned short *pusValue)
{
    return meDIGetRelayWord(iBoardNumber, pusValue);
}




_declspec(dllexport) int _stdcall VBme630DIOResetAll(int iBoardNumber)
{
    return meDIOResetAll(iBoardNumber);
}


_declspec(dllexport) int _stdcall VBme630DIOConfig(int iBoardNumber, int iPortNumber, int iPortDirection)
{
    return meDIOConfig(iBoardNumber, iPortNumber, iPortDirection);
}


_declspec(dllexport) int _stdcall VBme630DIOGetBit(int iBoardNumber, int iPortNumber, int iBitNo, int* piBitValue)
{
    return meDIOGetBit(iBoardNumber, iPortNumber, iBitNo, piBitValue);
}


_declspec(dllexport) int _stdcall VBme630DIOGetByte(int iBoardNumber, int iPortNumber, unsigned char* pucByteValue)
{
    return meDIOGetByte(iBoardNumber, iPortNumber, pucByteValue);
}


_declspec(dllexport) int _stdcall VBme630DIOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iBitValue)
{
    return meDIOSetBit(iBoardNumber, iPortNumber, iBitNo, iBitValue);
}


_declspec(dllexport) int _stdcall VBme630DIOSetByte(int iBoardNumber, int iPortNumber, unsigned char ucByteValue)
{
    return meDIOSetByte(iBoardNumber, iPortNumber, ucByteValue);
}



/*--------------- ISA board routines for compatability with earlier versions --------------------*/

_declspec(dllexport) int _stdcall VBme8xGetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _stdcall VBme63Reset(int iBoardNumber)
{
    return meResetRelays(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme63DIGetBit(int iBoardNumber, int iBitNo, int *piValue)
{
    return meDIGetTTLBit(iBoardNumber, iBitNo, piValue);
}



_declspec(dllexport) int _stdcall VBme63DIGetByte(int iBoardNumber, int* iValue)
{
    unsigned char uc_value;

    int i_error = meDIGetTTLByte(iBoardNumber, &uc_value);

    *iValue = (int)uc_value;

    return i_error;
}



_declspec(dllexport) int _stdcall VBme63DOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    return meDOSetRelayBit(iBoardNumber, iBitNo, iBitValue);
}



_declspec(dllexport) int _stdcall VBme63DOSetWord(int iBoardNumber, int iValue)
{
    return meDOSetRelayWord( iBoardNumber, (unsigned short)(iValue & 0xffff) );
}



/*--------------------     end of interface  -------------------------*/

} // extern "C"
