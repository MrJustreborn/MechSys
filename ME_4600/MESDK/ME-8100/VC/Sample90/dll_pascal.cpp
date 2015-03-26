
#include <stdio.h>
#include <windows.h>

#include "dll.h"

extern "C" {

/*--------------- new regular PCI API functions (without "_" prefix) --------------------*/

_declspec(dllexport) int _stdcall VBme8100GetDLLVersion()
{
    return meGetDLLVersion();
}



_declspec(dllexport) int _stdcall VBme8100GetDriverVersion(int *piDriverVersion)
{
    return meGetDriverVersion(piDriverVersion);
}



_declspec(dllexport) int _stdcall VBme8100GetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    return meGetBoardVersion(iBoardNumber, piBoardVersion);
}



_declspec(dllexport) int _stdcall VBme8100GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    return meGetSerialNumber(iBoardNumber, piSerialNumber);
}



_declspec(dllexport) int _stdcall VBme8100GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    return meGetIrqCnt(iBoardNumber, iIRQNum, piCnt);
}



_declspec(dllexport) int _stdcall VBme8100GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    return meGetDevInfo(iBoardNumber, pDevInfo);
}



_declspec(dllexport) int _stdcall VBme8100WriteUserString(int iBoardNumber, char* pcUserText)
{
    return meWriteUserString(iBoardNumber, pcUserText);
}



_declspec(dllexport) int _stdcall VBme8100ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    return meReadUserString(iBoardNumber, pcUserText, iMaxLength);
}



_declspec(dllexport) int _stdcall VBme8100InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    return meInportByte(iBoardNumber, iPortOffset, pbValue);
}



_declspec(dllexport) int _stdcall VBme8100OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    return meOutportByte(iBoardNumber, iPortOffset, bValue);
}



_declspec(dllexport) int _stdcall VBme8100InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _stdcall VBme8100OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _stdcall VBme8100InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    return meInportDWord(iBoardNumber, iPortOffset, pwValue);
}



_declspec(dllexport) int _stdcall VBme8100OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    return meOutportDWord(iBoardNumber, iPortOffset, wValue);
}



_declspec(dllexport) int _stdcall VBme8100ResetBoard(int iBoardNumber)
{
    return meResetBoard(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme8100InitBoard(int iBoardNumber)
{
    return meInitBoard(iBoardNumber);
}



_declspec(dllexport) int _stdcall VBme8100EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    return meEnableInt(iBoardNumber, iIRQNum, IrqFunc, iContext);
}



_declspec(dllexport) int _stdcall VBme8100DisableInt(int iBoardNumber, int iIRQNum)
{
    return meDisableInt(iBoardNumber, iIRQNum);
}



_declspec(dllexport) int _stdcall VBme8100GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    return meGetDrvErrMess(pcErrortext, iBufferSize);
}






_declspec(dllexport) int _stdcall VBme8100PROMVersion(int iBoardNumber, int *piVersion)
{
    return mePROMVersion(iBoardNumber, piVersion);
}



_declspec(dllexport) int _stdcall VBme8100DIGetIntStatus(int iBoardNumber, int iRegisterSet, int *piValue)
{
    return meDIGetIntStatus(iBoardNumber, iRegisterSet, piValue);
}



_declspec(dllexport) int _stdcall VBme8100DIOSetIntMode(int iBoardNumber, int iRegisterSet, int iMode)
{
    return meDIOSetIntMode(iBoardNumber, iRegisterSet, iMode);
}



_declspec(dllexport) int _stdcall VBme8100DIOSetTristateON(int iBoardNumber, int iRegisterSet)
{
    return meDIOSetTristateON(iBoardNumber, iRegisterSet);
}



_declspec(dllexport) int _stdcall VBme8100DIOSetTristateOFF(int iBoardNumber, int iRegisterSet)
{
    return meDIOSetTristateOFF(iBoardNumber, iRegisterSet);
}



_declspec(dllexport) int _stdcall VBme8100DIOSetPattern(int iBoardNumber, int iRegisterSet, int iPattern)
{
    return meDIOSetPattern(iBoardNumber, iRegisterSet, iPattern);
}



_declspec(dllexport) int _stdcall VBme8100DIOSetMask(int iBoardNumber, int iRegisterSet, int iMask)
{
    return meDIOSetMask(iBoardNumber, iRegisterSet, iMask);
}



_declspec(dllexport) int _stdcall VBme8100DIGetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int *piBitValue)
{
    return meDIGetBit(iBoardNumber, iRegisterSet, iBitNo, piBitValue);
}



_declspec(dllexport) int _stdcall VBme8100DIGetWord(int iBoardNumber, int iRegisterSet, int *piValue)
{
    return meDIGetWord(iBoardNumber, iRegisterSet, piValue);
}



_declspec(dllexport) int _stdcall VBme8100DOSetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int iBitValue)
{
    return meDOSetBit(iBoardNumber, iRegisterSet, iBitNo, iBitValue);
}



_declspec(dllexport) int _stdcall VBme8100DOSetWord(int iBoardNumber, int iRegisterSet, int iValue)
{
    return meDOSetWord(iBoardNumber, iRegisterSet, iValue);
}



_declspec(dllexport) int _stdcall VBme8100CntWrite(int iBoardNumber, int iCounter, int iMode, int iValue)
{
    return meCntWrite(iBoardNumber, iCounter, iMode, iValue);
}



_declspec(dllexport) int _stdcall VBme8100CntRead(int iBoardNumber, int iCounter, int* piValue)
{
    return meCntRead(iBoardNumber, iCounter, piValue);
}



_declspec(dllexport) int _stdcall VBme8100SetSinkSourceMode(int iBoardNumber, int iRegisterSet, int iMode)
{
    return meSetSinkSourceMode(iBoardNumber, iRegisterSet, iMode);
}









// me8xIrqFunc servees as the ME8100_PSERVICE_PROC parameter for VBme8100EnableInt
// in VBme8xEnableInt below to preserve compatibility.
void _stdcall me8xIrqFuncPascal(int iContext)
{
    PSERVICE_PROC p_proc = (PSERVICE_PROC)iContext;

    p_proc();
}

_declspec(dllexport) int _stdcall VBme8xEnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc)
{
    return( VBme8100EnableInt(iBoardNumber, REGISTER_SET_A, me8xIrqFuncPascal, (int)IrqFunc) );
}

_declspec(dllexport) int _stdcall VBme8xDisableInt(int iBoardNumber)
{
    return( VBme8100DisableInt(iBoardNumber, REGISTER_SET_A) );
}

// Error Handling
_declspec(dllexport) int _stdcall VBme8xGetDrvErrMess(char *pcErrortext)
{
    return( VBme8100GetDrvErrMess(pcErrortext, 256) );
}

// Digital I/O General Functions
_declspec(dllexport) int _stdcall VBme81DIGetIntStatus(int iBoardNumber, int *piValue)
{
    return( VBme8100DIGetIntStatus(iBoardNumber, REGISTER_SET_A, piValue) );
}

_declspec(dllexport) int _stdcall VBme8xDIOSetIntMode(int iBoardNumber, int iMode)
{
    return( VBme8100DIOSetIntMode(iBoardNumber, REGISTER_SET_A, iMode) );
}

_declspec(dllexport) int _stdcall VBme80DIOSetMode(int iBoardNumber, int iMode, int iRegMode)
{
    // ???? - Noch zu machen

    return(TRUE);

    //  return( VBme8100DIOSetMode(iBoardNumber, REGISTER_SET_A, iMode, iRegMode) );
}

_declspec(dllexport) int _stdcall VBme8xDIOSetTristateON(int iBoardNumber)
{
    return( VBme8100DIOSetTristateOFF(iBoardNumber, REGISTER_SET_A) );
}

_declspec(dllexport) int _stdcall VBme8xDIOSetTristateOFF(int iBoardNumber)
{
    return( VBme8100DIOSetTristateON(iBoardNumber, REGISTER_SET_A) );
}

_declspec(dllexport) int _stdcall VBme8xDIOSetPattern(int iBoardNumber, int iPattern)
{
    return( VBme8100DIOSetPattern(iBoardNumber, REGISTER_SET_A, iPattern) );
}

_declspec(dllexport) int _stdcall VBme81DIOSetMask(int iBoardNumber, int iMask)
{
    return( VBme8100DIOSetMask(iBoardNumber, REGISTER_SET_A, iMask) );
}

// Digital I/O Input-Functions
_declspec(dllexport) int _stdcall VBme8xDIGetBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    if(iBitNo <= 15)
    {
        return( VBme8100DIGetBit(iBoardNumber, REGISTER_SET_A, iBitNo, piBitValue) );
    }
    else
    {
        return( VBme8100DIGetBit(iBoardNumber, REGISTER_SET_B, iBitNo - 16, piBitValue) );
    }
}

_declspec(dllexport) int _stdcall VBme8xDIGetWord(int iBoardNumber, int iPortNo, int *piValue)
{
    if(iPortNo == PORTA)
    {
        return( VBme8100DIGetWord(iBoardNumber, REGISTER_SET_A, piValue) );
    }
    else
    {
        return( VBme8100DIGetWord(iBoardNumber, REGISTER_SET_A, piValue) );
    }
}

// Digital I/O Output-Functions
_declspec(dllexport) int _stdcall VBme8xDOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    if(iBitNo <= 15)
    {
        return( VBme8100DOSetBit(iBoardNumber, REGISTER_SET_A, iBitNo, iBitValue) );
    }
    else
    {
        return( VBme8100DOSetBit(iBoardNumber, REGISTER_SET_B, iBitNo - 16, iBitValue) );
    }
}

_declspec(dllexport) int _stdcall VBme8xDOSetWord(int iBoardNumber, int iPortNo, int iValue)
{
    if(iPortNo == PORTA)
    {
        return( VBme8100DOSetWord(iBoardNumber, REGISTER_SET_A, iValue) );
    }
    else
    {
        return( VBme8100DOSetWord(iBoardNumber, REGISTER_SET_A, iValue) );
    }
}

} // extern "C"
