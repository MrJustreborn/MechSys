
#include <stdio.h>
#include <windows.h>

#include "dll.h"

extern "C" {

/*--------------- new regular PCI API functions (without "_" prefix) --------------------*/

_declspec(dllexport) int _cdecl me1600GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl me1600GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl me1600GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl me1600GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl me1600GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _cdecl me1600GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl me1600WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl me1600ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl me1600InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl me1600OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl me1600InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me1600OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me1600InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me1600OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me1600ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me1600InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



/*_declspec(dllexport) int _cdecl me1600EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, iContext);
}



_declspec(dllexport) int _cdecl me1600DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}*/



_declspec(dllexport) int _cdecl me1600GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}






_declspec(dllexport) int _cdecl me1600AOResetAll(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me1600AOSetMode(int iBoardNumber,
                                                int iChannelGroup,
                                                int iOutMode)
{
    return meAOSetMode(iBoardNumber, iChannelGroup, iOutMode);
}



_declspec(dllexport) int _cdecl me1600AOSetRange(int iBoardNumber,
                                                 int iChannelNumber,
                                                 int iRange)
{
    return meAOSetRange(iBoardNumber, iChannelNumber, iRange);
}



_declspec(dllexport) int _cdecl me1600AOSingle(int iBoardNumber,
                                               int iChannelNumber,
                                               short iValue)
{
    return meAOSingle(iBoardNumber, iChannelNumber, (int)iValue);
}



_declspec(dllexport) int _cdecl me1600AOUpdate(int iBoardNumber,
                                               int iChannelGroup)
{
    return meAOUpdate(iBoardNumber, iChannelGroup);
}



_declspec(dllexport) int _cdecl me1600AOUpdateAll(int iBoardNumber)
{
    return meAOUpdateAll(iBoardNumber);
}



_declspec(dllexport) int _cdecl me1600AOSetCurrent(int iBoardNumber,
                                                    int iChannelNumber,
                                                    int iCurrentMode,
                                                    int iRange)
{
    return meAOSetCurrent(iBoardNumber, iChannelNumber, iCurrentMode, iRange);
}










_declspec(dllexport) int _cdecl _me1600GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl _me1600GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl _me1600GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl _me1600GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl _me1600GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _cdecl _me1600GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl _me1600WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl _me1600ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl _me1600InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl _me1600OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl _me1600InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl _me1600OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl _me1600InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl _me1600OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl _me1600ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me1600InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



/*_declspec(dllexport) int _cdecl _me1600EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, iContext);
}



_declspec(dllexport) int _cdecl _me1600DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}*/



_declspec(dllexport) int _cdecl _me1600GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}






_declspec(dllexport) int _cdecl _me1600AOResetAll(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me1600AOSetMode(int iBoardNumber,
                                                 int iChannelGroup,
                                                 int iOutMode)
{
    return meAOSetMode(iBoardNumber, iChannelGroup, iOutMode);
}



_declspec(dllexport) int _cdecl _me1600AOSetRange(int iBoardNumber,
                                                  int iChannelNumber,
                                                  int iRange)
{
    return meAOSetRange(iBoardNumber, iChannelNumber, iRange);
}



_declspec(dllexport) int _cdecl _me1600AOSingle(int iBoardNumber,
                                                int iChannelNumber,
                                                short iValue)
{
    return meAOSingle(iBoardNumber, iChannelNumber, iValue);
}



_declspec(dllexport) int _cdecl _me1600AOUpdate(int iBoardNumber,
                                                int iChannelGroup)
{
    return meAOUpdate(iBoardNumber, iChannelGroup);
}



_declspec(dllexport) int _cdecl _me1600AOUpdateAll(int iBoardNumber)
{
    return meAOUpdateAll(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me1600AOSetCurrent(int iBoardNumber,
                                                    int iChannelNumber,
                                                    int iCurrentMode,
                                                    int iRange)
{
    return meAOSetCurrent(iBoardNumber, iChannelNumber, iCurrentMode, iRange);
}













// ISA board routines for compatability with earlier versions
_declspec(dllexport) int _cdecl _me160GetDLLVersion()
{
    return meGetDLLVersion();
}


_declspec(dllexport) int _cdecl _me160GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl _me160GetDrvErrMess(char *pcErrortext)
{
    return meGetDrvErrMess(pcErrortext, 64 /*iBufferSize*/);
}



_declspec(dllexport) int _cdecl _me160AOSetMode(int iBoardNumber,
                                                int iChannelGroup,
                                                int iOutMode)
{
    return meAOSetMode(iBoardNumber, iChannelGroup, iOutMode);
}



_declspec(dllexport) int _cdecl _me160AOSingle(int iBoardNumber,
                                               int iChannelNumber,
                                               int iRange,
                                               short iValue)
{
    switch (iRange)
    {
    case AO_PLUS_10:
        iRange = AO_UNIPOLAR;
        break;
    case AO_PLUS_5:
        iRange = AO_UNIPOLAR;
        iValue = iValue / 2;
        break;
    case AO_MINUS_5:
        iRange = AO_BIPOLAR;
        iValue = iValue / 2;
        break;
    case AO_MINUS_10:
        iRange = AO_BIPOLAR;
        break;
    }

    meAOSetRange(iBoardNumber, iChannelNumber, iRange);
    return meAOSingle(iBoardNumber, iChannelNumber, iValue);
}



_declspec(dllexport) int _cdecl _me160AOUpdate(int iBoardNumber,
                                               int iChannelGroup)
{
    return meAOUpdate(iBoardNumber, iChannelGroup);
}



_declspec(dllexport) int _cdecl _me160AOUpdateAll(int iBoardNumber)
{
    return meAOUpdateAll(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me160AOResetAll(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}

} // extern "C"
