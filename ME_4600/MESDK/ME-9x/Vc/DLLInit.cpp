/*----------------------------------------------------------------------------
    File: DLLINIT.CPP
------------------------------------------------------------------------------ 

    Meilhaus Electronic GmbH

    C source file containing wrapper for all DLL functions.  This file is
    for use in projects using dynamic function calls (no library file is
    included in the project)

    Version 1.00:   001012
-------------------------------------------------------------------------------
    Author: Andreas Bernau / Ralph Timm
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include ".\meDefs.h"
#include ".\DLLInit.h"

/*  Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEFILE(".\meDefs.h");
USEFILE(".\DLLInit.h");
#endif



PF_ME9XGETDLLVERSION            pf_me9xGetDLLVersion;
PF_ME9XGETDRIVERVERSION         pf_me9xGetDriverVersion;
PF_ME9XGETBOARDVERSION          pf_me9xGetBoardVersion;
PF_ME9XGETDRVERRMESS            pf_me9xGetDrvErrMess;

PF_ME9XENABLEINT                pf_me9xEnableInt;
PF_ME9XDISABLEINT               pf_me9xDisableInt;
PF_ME9XGETIRQCNT                pf_me9xGetIrqCnt;

PF_ME9XDIGETBIT                 pf_me9xDIGetBit;
PF_ME9XDIGETBYTE                pf_me9xDIGetByte;
PF_ME9XDOSETBIT                 pf_me9xDOSetBit;
PF_ME9XDOSETBYTE                pf_me9xDOSetByte;

PF_ME9XGETSERIALNUMBER          pf_me9xGetSerialNumber;
PF_ME9XGETDEVINFO               pf_me9xGetDevInfo;    
PF_ME9XINPORTBYTE               pf_me9xInportByte;
PF_ME9XOUTPORTBYTE              pf_me9xOutportByte;
PF_ME9XINPORTWORD               pf_me9xInportWord;
PF_ME9XOUTPORTWORD              pf_me9xOutportWord;
PF_ME9XINPORTDWORD              pf_me9xInportDWord;
PF_ME9XOUTPORTDWORD             pf_me9xOutportDWord;
PF_ME9XRESETBOARD               pf_me9xResetBoard;
PF_ME9XINITBOARD                pf_me9xInitBoard;

PF_ME9XWRITEUSERSTRING          pf_me9xWriteUserString;
PF_ME9XREADUSERSTRING           pf_me9xReadUserString;



HINSTANCE hDll;


void meOpen(void)
{
    hDll = LoadLibrary(DLLNAME);
    if (hDll == NULL)
    {
        MessageBox( NULL, "DLL not Found", "Error", MB_OK | MB_ICONINFORMATION );
        exit(1);
    }

    pf_me9xGetDLLVersion    = (PF_ME9XGETDLLVERSION)
                            (GetProcAddress (hDll,"me9xGetDLLVersion"));

    pf_me9xGetDriverVersion  = (PF_ME9XGETDRIVERVERSION)
                            (GetProcAddress (hDll,"me9xGetDriverVersion"));

    pf_me9xGetBoardVersion  = (PF_ME9XGETBOARDVERSION)
                            (GetProcAddress (hDll,"me9xGetBoardVersion"));

    pf_me9xGetDrvErrMess    = (PF_ME9XGETDRVERRMESS)
                            (GetProcAddress (hDll,"me9xGetDrvErrMess"));


    pf_me9xEnableInt        = (PF_ME9XENABLEINT)
                            (GetProcAddress (hDll,"me9xEnableInt"));

    pf_me9xDisableInt       = (PF_ME9XDISABLEINT)
                            (GetProcAddress (hDll,"me9xDisableInt"));

    pf_me9xGetIrqCnt        = (PF_ME9XGETIRQCNT)
                            (GetProcAddress (hDll,"me9xGetIrqCnt"));


    pf_me9xDIGetBit         = (PF_ME9XDIGETBIT)
                            (GetProcAddress (hDll,"me9xDIGetBit"));

    pf_me9xDIGetByte        = (PF_ME9XDIGETBYTE)
                            (GetProcAddress (hDll,"me9xDIGetByte"));
    
    pf_me9xDOSetBit         = (PF_ME9XDOSETBIT)
                            (GetProcAddress (hDll,"me9xDOSetBit"));

    pf_me9xDOSetByte        = (PF_ME9XDOSETBYTE)
                            (GetProcAddress (hDll,"me9xDOSetByte"));


    pf_me9xGetSerialNumber  = (PF_ME9XGETSERIALNUMBER)
                            (GetProcAddress (hDll,"me9xGetSerialNumber"));

    pf_me9xGetDevInfo       = (PF_ME9XGETDEVINFO)
                            (GetProcAddress (hDll,"me9xGetDevInfo"));

    pf_me9xInportByte       = (PF_ME9XINPORTBYTE)
                            (GetProcAddress (hDll,"me9xInportByte"));

    pf_me9xOutportByte      = (PF_ME9XOUTPORTBYTE)
                            (GetProcAddress (hDll,"me9xOutportByte"));

    pf_me9xInportWord       = (PF_ME9XINPORTWORD)
                            (GetProcAddress (hDll,"me9xInportWord"));

    pf_me9xOutportWord      = (PF_ME9XOUTPORTWORD)
                            (GetProcAddress (hDll,"me9xOutportWord"));

    pf_me9xInportDWord      = (PF_ME9XINPORTDWORD)
                            (GetProcAddress (hDll,"me9xInportDWord"));
                            
    pf_me9xOutportDWord     = (PF_ME9XOUTPORTDWORD)
                            (GetProcAddress (hDll,"me9xOutportDWord"));
                            
    pf_me9xResetBoard       = (PF_ME9XRESETBOARD)
                            (GetProcAddress (hDll,"me9xResetBoard"));
                            
    pf_me9xInitBoard        = (PF_ME9XINITBOARD)
                            (GetProcAddress (hDll,"me9xInitBoard"));


    pf_me9xWriteUserString  = (PF_ME9XWRITEUSERSTRING) 
                            (GetProcAddress (hDll,"me9xWriteUserString"));

    pf_me9xReadUserString   = (PF_ME9XREADUSERSTRING)  
                            (GetProcAddress (hDll,"me9xReadUserString"));
}

//   -------------------- Wrappers for all Functions -------------------------

int me9xGetDLLVersion(void)
{
    if (pf_me9xGetDLLVersion)
        return (pf_me9xGetDLLVersion)();
    else
        return FUNCTIONNOTFOUND;
}


int me9xGetDriverVersion (int *piVersion)
{
    if (pf_me9xGetDriverVersion)
        return (pf_me9xGetDriverVersion)(piVersion);
    else
        return FUNCTIONNOTFOUND;
}


int me9xGetBoardVersion(int iBoardNumber, int *piVersion)
{
    if (pf_me9xGetBoardVersion)
        return (pf_me9xGetBoardVersion)(iBoardNumber, piVersion);
    else
        return FUNCTIONNOTFOUND;
}


int me9xGetDrvErrMess(char *pcErrorText)
{
    if (pf_me9xGetDrvErrMess)
        return (pf_me9xGetDrvErrMess)(pcErrorText);
    else
        return FUNCTIONNOTFOUND;
}



int me9xEnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc)
{
    if (pf_me9xEnableInt)
        return (pf_me9xEnableInt)(iBoardNumber, IrqFunc);
    else
        return FUNCTIONNOTFOUND;
}
int me94EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc)
{
    if (pf_me9xEnableInt)
        return (pf_me9xEnableInt)(iBoardNumber, IrqFunc);
    else
        return FUNCTIONNOTFOUND;
}
int me96EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc)
{
    if (pf_me9xEnableInt)
        return (pf_me9xEnableInt)(iBoardNumber, IrqFunc);
    else
        return FUNCTIONNOTFOUND;
}


int me9xDisableInt(int iBoardNumber)
{
    if (pf_me9xDisableInt)
        return (pf_me9xDisableInt)(iBoardNumber);
    else
        return FUNCTIONNOTFOUND;
}
int me94DisableInt(int iBoardNumber)
{
    if (pf_me9xDisableInt)
        return (pf_me9xDisableInt)(iBoardNumber);
    else
        return FUNCTIONNOTFOUND;
}
int me96DisableInt(int iBoardNumber)
{
    if (pf_me9xDisableInt)
        return (pf_me9xDisableInt)(iBoardNumber);
    else
        return FUNCTIONNOTFOUND;
}

int me9xGetIrqCnt(int iBoardNumber, int dwTyp, int* dwCnt)
{
    if (pf_me9xGetIrqCnt)
        return (pf_me9xGetIrqCnt)(iBoardNumber, dwTyp, dwCnt);
    else
        return FUNCTIONNOTFOUND;
}



int me9xDIGetBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    if (pf_me9xDIGetBit)
        return (pf_me9xDIGetBit)(iBoardNumber, iBitNo, piBitValue);
    else
        return FUNCTIONNOTFOUND;
}
int me94DIGetBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    if (pf_me9xDIGetBit)
        return (pf_me9xDIGetBit)(iBoardNumber, iBitNo, piBitValue);
    else
        return FUNCTIONNOTFOUND;
}
int me96DIGetBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    if (pf_me9xDIGetBit)
        return (pf_me9xDIGetBit)(iBoardNumber, iBitNo, piBitValue);
    else
        return FUNCTIONNOTFOUND;
}


int me9xDIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
    if (pf_me9xDIGetByte)
        return (pf_me9xDIGetByte)(iBoardNumber, iPortNo, piValue);
    else
        return FUNCTIONNOTFOUND;
}
int me94DIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
    if (pf_me9xDIGetByte)
        return (pf_me9xDIGetByte)(iBoardNumber, iPortNo, piValue);
    else
        return FUNCTIONNOTFOUND;
}
int me96DIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
    if (pf_me9xDIGetByte)
        return (pf_me9xDIGetByte)(iBoardNumber, iPortNo, piValue);
    else
        return FUNCTIONNOTFOUND;
}


int me9xDOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    if (pf_me9xDOSetBit)
        return (pf_me9xDOSetBit)(iBoardNumber, iBitNo, iBitValue);
    else
        return FUNCTIONNOTFOUND;
}
int me95DOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    if (pf_me9xDOSetBit)
        return (pf_me9xDOSetBit)(iBoardNumber, iBitNo, iBitValue);
    else
        return FUNCTIONNOTFOUND;
}
int me96DOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    if (pf_me9xDOSetBit)
        return (pf_me9xDOSetBit)(iBoardNumber, iBitNo, iBitValue);
    else
        return FUNCTIONNOTFOUND;
}


int me9xDOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
    if (pf_me9xDOSetByte)
        return (pf_me9xDOSetByte)(iBoardNumber, iPortNo, iValue);
    else
        return FUNCTIONNOTFOUND;
}
int me95DOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
    if (pf_me9xDOSetByte)
        return (pf_me9xDOSetByte)(iBoardNumber, iPortNo, iValue);
    else
        return FUNCTIONNOTFOUND;
}
int me96DOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
    if (pf_me9xDOSetByte)
        return (pf_me9xDOSetByte)(iBoardNumber, iPortNo, iValue);
    else
        return FUNCTIONNOTFOUND;
}



int me9xGetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    if (pf_me9xGetSerialNumber)
        return (pf_me9xGetSerialNumber)(iBoardNumber, piSerialNumber);
    else
        return FUNCTIONNOTFOUND;
}

int me9xGetDevInfo (int iBoardNumber, PDEVICEINFOSTRUCT DevInfo)
{
    if (pf_me9xGetDevInfo)
        return (pf_me9xGetDevInfo)(iBoardNumber, DevInfo);
    else
        return FUNCTIONNOTFOUND;
}

int me9xInportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    if (pf_me9xInportByte)
        return (pf_me9xInportByte)(iBoardNumber, iPortOffset, pbValue);
    else
        return FUNCTIONNOTFOUND;
}

int me9xOutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    if (pf_me9xOutportByte)
        return (pf_me9xOutportByte)(iBoardNumber, iPortOffset, bValue);
    else
        return FUNCTIONNOTFOUND;
}

int me9xInportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    if (pf_me9xInportWord)
        return (pf_me9xInportWord)(iBoardNumber, iPortOffset, pwValue);
    else
        return FUNCTIONNOTFOUND;
}

int me9xOutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    if (pf_me9xOutportWord)
        return (pf_me9xOutportWord)(iBoardNumber, iPortOffset, wValue);
    else
        return FUNCTIONNOTFOUND;
}

int me9xInportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    if (pf_me9xInportDWord)
        return (pf_me9xInportDWord)(iBoardNumber, iPortOffset, pwValue);
    else
        return FUNCTIONNOTFOUND;
}

int me9xOutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    if (pf_me9xOutportDWord)
        return (pf_me9xOutportDWord)(iBoardNumber, iPortOffset, wValue);
    else
        return FUNCTIONNOTFOUND;
}

int me9xResetBoard(int iBoardNumber)
{
    if (pf_me9xResetBoard)
        return (pf_me9xResetBoard)(iBoardNumber);
    else
        return FUNCTIONNOTFOUND;
}

int me9xInitBoard(int iBoardNumber)
{
    if (pf_me9xInitBoard)
        return (pf_me9xInitBoard)(iBoardNumber);
    else
        return FUNCTIONNOTFOUND;
}



int me9xWriteUserString(int iBoardNumber, char* pcUserText)
{
    if (pf_me9xWriteUserString)
        return (pf_me9xWriteUserString)(iBoardNumber, pcUserText);
    else
        return FUNCTIONNOTFOUND;
}


int me9xReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    if (pf_me9xReadUserString)
        return (pf_me9xReadUserString)(iBoardNumber, pcUserText, iMaxLength);
    else
        return FUNCTIONNOTFOUND;
}



/* -------------------------  Close Function ----------------------------*/
void meClose (void)
{
    if (hDll)
    {
        FreeLibrary(hDll);
    }
}
