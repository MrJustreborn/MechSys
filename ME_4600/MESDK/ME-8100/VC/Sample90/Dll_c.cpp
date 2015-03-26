
#include <stdio.h>
#include <windows.h>

#include "dll.h"

extern "C" {

/*--------------- new regular PCI API functions (without "_" prefix) --------------------*/

_declspec(dllexport) int _cdecl me8100GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl me8100GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl me8100GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl me8100GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl me8100GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _cdecl me8100GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl me8100WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl me8100ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl me8100InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl me8100OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl me8100InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me8100OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me8100InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl me8100OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl me8100ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me8100InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl me8100EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, iContext);
}



_declspec(dllexport) int _cdecl me8100DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}



_declspec(dllexport) int _cdecl me8100GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}






_declspec(dllexport) int _cdecl me8100PROMVersion(int iBoardNumber, int *piVersion)
{
    return mePROMVersion(iBoardNumber, piVersion);
}



_declspec(dllexport) int _cdecl me8100DIGetIntStatus(int iBoardNumber, int iRegisterSet, int *piValue)
{
    return meDIGetIntStatus(iBoardNumber, iRegisterSet, piValue);
}



_declspec(dllexport) int _cdecl me8100DIOSetIntMode(int iBoardNumber, int iRegisterSet, int iMode)
{
    return meDIOSetIntMode(iBoardNumber, iRegisterSet, iMode);
}



_declspec(dllexport) int _cdecl me8100DIOSetTristateON(int iBoardNumber, int iRegisterSet)
{
    return meDIOSetTristateON(iBoardNumber, iRegisterSet);
}



_declspec(dllexport) int _cdecl me8100DIOSetTristateOFF(int iBoardNumber, int iRegisterSet)
{
    return meDIOSetTristateOFF(iBoardNumber, iRegisterSet);
}



_declspec(dllexport) int _cdecl me8100DIOSetPattern(int iBoardNumber, int iRegisterSet, int iPattern)
{
    return meDIOSetPattern(iBoardNumber, iRegisterSet, iPattern);
}



_declspec(dllexport) int _cdecl me8100DIOSetMask(int iBoardNumber, int iRegisterSet, int iMask)
{
    return meDIOSetMask(iBoardNumber, iRegisterSet, iMask);
}



_declspec(dllexport) int _cdecl me8100DIGetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int *piBitValue)
{
    return meDIGetBit(iBoardNumber, iRegisterSet, iBitNo, piBitValue);
}



_declspec(dllexport) int _cdecl me8100DIGetWord(int iBoardNumber, int iRegisterSet, int *piValue)
{
    return meDIGetWord(iBoardNumber, iRegisterSet, piValue);
}



_declspec(dllexport) int _cdecl me8100DOSetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int iBitValue)
{
    return meDOSetBit(iBoardNumber, iRegisterSet, iBitNo, iBitValue);
}



_declspec(dllexport) int _cdecl me8100DOSetWord(int iBoardNumber, int iRegisterSet, int iValue)
{
    return meDOSetWord(iBoardNumber, iRegisterSet, iValue);
}



_declspec(dllexport) int _cdecl me8100CntWrite(int iBoardNumber, int iCounter, int iMode, int iValue)
{
    return meCntWrite(iBoardNumber, iCounter, iMode, iValue);
}



_declspec(dllexport) int _cdecl me8100CntRead(int iBoardNumber, int iCounter, int* piValue)
{
    return meCntRead(iBoardNumber, iCounter, piValue);
}



_declspec(dllexport) int _cdecl me8100SetSinkSourceMode(int iBoardNumber, int iRegisterSet, int iMode)
{
    return meSetSinkSourceMode(iBoardNumber, iRegisterSet, iMode);
}




/*--------------- new PCI API functions with "_" prefix --------------------*/

_declspec(dllexport) int _cdecl _me8100GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _cdecl _me8100GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _cdecl _me8100GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _cdecl _me8100GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _cdecl _me8100GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _cdecl _me8100GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _cdecl _me8100WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _cdecl _me8100ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _cdecl _me8100InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _cdecl _me8100OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _cdecl _me8100InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl _me8100OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl _me8100InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _cdecl _me8100OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _cdecl _me8100ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me8100InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _cdecl _me8100EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, iContext);
}



_declspec(dllexport) int _cdecl _me8100DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}



_declspec(dllexport) int _cdecl _me8100GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}




_declspec(dllexport) int _cdecl _me8100PROMVersion(int iBoardNumber, int *piVersion)
{
    return mePROMVersion(iBoardNumber, piVersion);
}



_declspec(dllexport) int _cdecl _me8100DIGetIntStatus(int iBoardNumber, int iRegisterSet, int *piValue)
{
    return meDIGetIntStatus(iBoardNumber, iRegisterSet, piValue);
}



_declspec(dllexport) int _cdecl _me8100DIOSetIntMode(int iBoardNumber, int iRegisterSet, int iMode)
{
    return meDIOSetIntMode(iBoardNumber, iRegisterSet, iMode);
}



_declspec(dllexport) int _cdecl _me8100DIOSetTristateON(int iBoardNumber, int iRegisterSet)
{
    return meDIOSetTristateON(iBoardNumber, iRegisterSet);
}



_declspec(dllexport) int _cdecl _me8100DIOSetTristateOFF(int iBoardNumber, int iRegisterSet)
{
    return meDIOSetTristateOFF(iBoardNumber, iRegisterSet);
}



_declspec(dllexport) int _cdecl _me8100DIOSetPattern(int iBoardNumber, int iRegisterSet, int iPattern)
{
    return meDIOSetPattern(iBoardNumber, iRegisterSet, iPattern);
}



_declspec(dllexport) int _cdecl _me8100DIOSetMask(int iBoardNumber, int iRegisterSet, int iMask)
{
    return meDIOSetMask(iBoardNumber, iRegisterSet, iMask);
}



_declspec(dllexport) int _cdecl _me8100DIGetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int *piBitValue)
{
    return meDIGetBit(iBoardNumber, iRegisterSet, iBitNo, piBitValue);
}



_declspec(dllexport) int _cdecl _me8100DIGetWord(int iBoardNumber, int iRegisterSet, int *piValue)
{
    return meDIGetWord(iBoardNumber, iRegisterSet, piValue);
}



_declspec(dllexport) int _cdecl _me8100DOSetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int iBitValue)
{
    return meDOSetBit(iBoardNumber, iRegisterSet, iBitNo, iBitValue);
}



_declspec(dllexport) int _cdecl _me8100DOSetWord(int iBoardNumber, int iRegisterSet, int iValue)
{
    return meDOSetWord(iBoardNumber, iRegisterSet, iValue);
}



_declspec(dllexport) int _cdecl _me8100CntWrite(int iBoardNumber, int iCounter, int iMode, int iValue)
{
    return meCntWrite(iBoardNumber, iCounter, iMode, iValue);
}



_declspec(dllexport) int _cdecl _me8100CntRead(int iBoardNumber, int iCounter, int* piValue)
{
    return meCntRead(iBoardNumber, iCounter, piValue);
}



_declspec(dllexport) int _cdecl _me8100SetSinkSourceMode(int iBoardNumber, int iRegisterSet, int iMode)
{
    return meSetSinkSourceMode(iBoardNumber, iRegisterSet, iMode);
}


















// ME8X Routines for compatability with earlier versions

// General Routines
_declspec(dllexport) int _cdecl _me8xGetDLLVersion()
{
    return meGetDLLVersion();
}

_declspec(dllexport) int _cdecl _me8xPROMVersion(int iBoardNumber, int *piVersion)
{
    return mePROMVersion(iBoardNumber, piVersion);
}


// me8xIrqFunc servees as the ME8100_PSERVICE_PROC parameter for _me8100EnableInt
// in _me8xEnableInt below to preserve compatibility.
void _stdcall me8xIrqFunc(int iContext)
{
    PSERVICE_PROC p_proc = (PSERVICE_PROC)iContext;

    p_proc();
}

_declspec(dllexport) int _cdecl _me8xEnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc)
{
    return( _me8100EnableInt(iBoardNumber, REGISTER_SET_A, me8xIrqFunc, (int)IrqFunc) );
}

_declspec(dllexport) int _cdecl _me8xDisableInt(int iBoardNumber)
{
    return( _me8100DisableInt(iBoardNumber, REGISTER_SET_A) );
}

// Error Handling
_declspec(dllexport) int _cdecl _me8xGetDrvErrMess(char *pcErrortext)
{
    return( _me8100GetDrvErrMess(pcErrortext, 256) );
}

// Digital I/O General Functions
_declspec(dllexport) int _cdecl _me81DIGetIntStatus(int iBoardNumber, int *piValue)
{
    return( _me8100DIGetIntStatus(iBoardNumber, REGISTER_SET_A, piValue) );
}



_declspec(dllexport) int _cdecl _me8xDIOSetIntMode(int iBoardNumber, int iMode)
{
    return( _me8100DIOSetIntMode(iBoardNumber, REGISTER_SET_A, iMode) );

}



_declspec(dllexport) int _cdecl _me80DIOSetMode(int iBoardNumber, int iMode, int iRegMode)
{
    // ???? - Noch zu machen

    return(TRUE);

    //  return( _me8100DIOSetMode(iBoardNumber, REGISTER_SET_A, iMode, iRegMode) );
}



_declspec(dllexport) int _cdecl _me8xDIOSetTristateON(int iBoardNumber)
{
    return( _me8100DIOSetTristateOFF(iBoardNumber, REGISTER_SET_A) );
}



_declspec(dllexport) int _cdecl _me8xDIOSetTristateOFF(int iBoardNumber)
{
    return( _me8100DIOSetTristateON(iBoardNumber, REGISTER_SET_A) );

}



_declspec(dllexport) int _cdecl _me8xDIOSetPattern(int iBoardNumber, int iPattern)
{
    return( _me8100DIOSetPattern(iBoardNumber, REGISTER_SET_A, iPattern) );
}



_declspec(dllexport) int _cdecl _me81DIOSetMask(int iBoardNumber, int iMask)
{
    return( _me8100DIOSetMask(iBoardNumber, REGISTER_SET_A, iMask) );
}



_declspec(dllexport) int _cdecl _me8xDIGetBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    if(iBitNo <= 15)
    {
        return( _me8100DIGetBit(iBoardNumber, REGISTER_SET_A, iBitNo, piBitValue) );
    }
    else
    {
        return( _me8100DIGetBit(iBoardNumber, REGISTER_SET_B, iBitNo - 16, piBitValue) );
    }
}



_declspec(dllexport) int _cdecl _me8xDIGetWord(int iBoardNumber, int iPortNo, int *piValue)
{
    if(iPortNo == PORTA)
    {
        return( _me8100DIGetWord(iBoardNumber, REGISTER_SET_A, piValue) );
    }
    else
    {
        return( _me8100DIGetWord(iBoardNumber, REGISTER_SET_A, piValue) );
    }
}



_declspec(dllexport) int _cdecl _me8xDOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    if(iBitNo <= 15)
    {
        return( _me8100DOSetBit(iBoardNumber, REGISTER_SET_A, iBitNo, iBitValue) );
    }
    else
    {
        return( _me8100DOSetBit(iBoardNumber, REGISTER_SET_B, iBitNo - 16, iBitValue) );
    }
}



_declspec(dllexport) int _cdecl _me8xDOSetWord(int iBoardNumber, int iPortNo, int iValue)
{
    if(iPortNo == PORTA)
    {
        return( _me8100DOSetWord(iBoardNumber, REGISTER_SET_A, iValue) );
    }
    else
    {
        return( _me8100DOSetWord(iBoardNumber, REGISTER_SET_A, iValue) );
    }
}



_declspec(dllexport) int _cdecl _me81GetIrqCnt(int iBoardNumber, int iType, int* piCnt)
{
    if(iType == PORTA)
    {
        return( _me8100GetIrqCnt(iBoardNumber, REGISTER_SET_A, piCnt) );
    }
    else
    {
        return( _me8100GetIrqCnt(iBoardNumber, REGISTER_SET_B, piCnt) );
    }
}



_declspec(dllexport) int _cdecl _me81GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return( _me8100GetDevInfo(iBoardNumber, pDevInfo) );
}



_declspec(dllexport) int _cdecl _me81WriteUserString(int iBoardNumber, char* pcUserText)
{
    return( _me8100WriteUserString(iBoardNumber, pcUserText) );
}

} // extern "C"
