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
USEFILE(".\medefs.h");
USEFILE(".\DLLInit.h");
#endif



PF_ME630GETDLLVERSION           pf_me630GetDLLVersion;
PF_ME630GETBOARDVERSION         pf_me630GetBoardVersion;
PF_ME630RESETRELAYS             pf_me630ResetRelays;
PF_ME630ENABLEINT               pf_me630EnableInt;
PF_ME630DISABLEINT              pf_me630DisableInt;
PF_ME630GETDRVERRMESS           pf_me630GetDrvErrMess;
PF_ME630DIGETTTLBIT             pf_me630DIGetTTLBit;
PF_ME630DIGETTTLBYTE            pf_me630DIGetTTLByte;
PF_ME630DIGETOPTOBIT            pf_me630DIGetOptoBit;
PF_ME630DIGETOPTOBYTE           pf_me630DIGetOptoByte;
PF_ME630DOSETRELAYBIT           pf_me630DOSetRelayBit;
PF_ME630DOSETRELAYWORD          pf_me630DOSetRelayWord;
PF_ME630DIGETRELAYBIT           pf_me630DIGetRelayBit;
PF_ME630DIGETRELAYWORD          pf_me630DIGetRelayWord;
PF_ME630GETIRQCNT               pf_me630GetIrqCnt;
PF_ME630GETDEVINFO              pf_me630GetDevInfo;
PF_ME630WRITEUSERSTRING         pf_me630WriteUserString;
PF_ME630READUSERSTRING          pf_me630ReadUserString;

PF_ME630DIORESETALL				pf_me630DIOResetAll;
PF_ME630DIOCONFIG				pf_me630DIOConfig;
PF_ME630DIOGETBIT				pf_me630DIOGetBit;
PF_ME630DIOGETBYTE				pf_me630DIOGetByte;
PF_ME630DIOSETBIT				pf_me630DIOSetBit;
PF_ME630DIOSETBYTE				pf_me630DIOSetByte;

HINSTANCE hDll;

void meOpen(void)
{
    hDll = LoadLibrary(DLLNAME);   // load the library
    if (hDll == NULL)
    {
        MessageBox( NULL, "DLL not Found", "Error", MB_OK | MB_ICONINFORMATION );
        exit(1);
    }

    pf_me630GetDLLVersion       = (PF_ME630GETDLLVERSION)   (GetProcAddress (hDll,"me630GetDLLVersion"));

    pf_me630GetBoardVersion     = (PF_ME630GETBOARDVERSION) (GetProcAddress (hDll,"me630GetBoardVersion"));

    pf_me630ResetRelays         = (PF_ME630RESETRELAYS)     (GetProcAddress (hDll,"me630ResetRelays"));

    pf_me630EnableInt           = (PF_ME630ENABLEINT)       (GetProcAddress (hDll,"me630EnableInt"));

    pf_me630DisableInt          = (PF_ME630DISABLEINT)      (GetProcAddress (hDll,"me630DisableInt"));

    pf_me630GetDrvErrMess       = (PF_ME630GETDRVERRMESS)   (GetProcAddress (hDll,"me630GetDrvErrMess"));

    pf_me630DIGetTTLBit         = (PF_ME630DIGETTTLBIT)     (GetProcAddress (hDll,"me630DIGetTTLBit"));

    pf_me630DIGetTTLByte        = (PF_ME630DIGETTTLBYTE)    (GetProcAddress (hDll,"me630DIGetTTLByte"));

    pf_me630DIGetOptoBit        = (PF_ME630DIGETOPTOBIT)    (GetProcAddress (hDll,"me630DIGetOptoBit"));

    pf_me630DIGetOptoByte       = (PF_ME630DIGETOPTOBYTE)   (GetProcAddress (hDll,"me630DIGetOptoByte"));

    pf_me630DOSetRelayBit       = (PF_ME630DOSETRELAYBIT)   (GetProcAddress (hDll,"me630DOSetRelayBit"));
    
    pf_me630DOSetRelayWord      = (PF_ME630DOSETRELAYWORD)  (GetProcAddress (hDll,"me630DOSetRelayWord"));

    pf_me630DIGetRelayBit       = (PF_ME630DIGETRELAYBIT)   (GetProcAddress (hDll,"me630DIGetRelayBit"));

    pf_me630DIGetRelayWord      = (PF_ME630DIGETRELAYWORD)  (GetProcAddress (hDll,"me630DIGetRelayWord"));

    pf_me630GetIrqCnt           = (PF_ME630GETIRQCNT)       (GetProcAddress (hDll,"me630GetIrqCnt"));

    pf_me630GetDevInfo          = (PF_ME630GETDEVINFO)      (GetProcAddress (hDll,"me630GetDevInfo"));

    pf_me630WriteUserString     = (PF_ME630WRITEUSERSTRING) (GetProcAddress (hDll,"me630WriteUserString"));

    pf_me630ReadUserString      = (PF_ME630READUSERSTRING)  (GetProcAddress (hDll,"me630ReadUserString"));

	pf_me630DIOResetAll			= (PF_ME630DIORESETALL)		(GetProcAddress (hDll,"me630DIOResetAll"));	
	
	pf_me630DIOConfig			= (PF_ME630DIOCONFIG)		(GetProcAddress (hDll,"me630DIOConfig"));
				
	pf_me630DIOGetBit			= (PF_ME630DIOGETBIT)		(GetProcAddress (hDll,"me630DIOGetBit"));
				
	pf_me630DIOGetByte			= (PF_ME630DIOGETBYTE)		(GetProcAddress (hDll,"me630DIOGetByte"));
				
	pf_me630DIOSetBit			= (PF_ME630DIOSETBIT)		(GetProcAddress (hDll,"me630DIOSetBit"));
				
	pf_me630DIOSetByte			= (PF_ME630DIOSETBYTE)		(GetProcAddress (hDll,"me630DIOSetByte"));				
}

//   -------------------- Wrappers for all Functions -------------------------

int me630GetDLLVersion(void)
{
    if (pf_me630GetDLLVersion)
        return (pf_me630GetDLLVersion)();
    else
        return FUNCTIONNOTFOUND;
}


int me630GetBoardVersion(int iBoardNumber, int *piVersion)
{
    if (pf_me630GetBoardVersion)
        return (pf_me630GetBoardVersion)(iBoardNumber, piVersion);
    else
        return FUNCTIONNOTFOUND;
}


int me630ResetRelays(int iBoardNumber)
{
    if (pf_me630ResetRelays)
        return (pf_me630ResetRelays)(iBoardNumber);
    else
        return FUNCTIONNOTFOUND;
}


int me630EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    if (pf_me630EnableInt)
        return (pf_me630EnableInt)(iBoardNumber, iIRQNum, IrqFunc, iContext);
    else
        return FUNCTIONNOTFOUND;
}


int me630DisableInt(int iBoardNumber, int iIRQNum)
{
    if (pf_me630DisableInt)
        return (pf_me630DisableInt)(iBoardNumber, iIRQNum);
    else
        return FUNCTIONNOTFOUND;
}


int me630GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    if (pf_me630GetDrvErrMess)
        return (pf_me630GetDrvErrMess)(pcErrortext, iBufferSize);
    else
        return FUNCTIONNOTFOUND;
}


int me630DIGetTTLBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    if (pf_me630DIGetTTLBit)
        return (pf_me630DIGetTTLBit)(iBoardNumber, iBitNo, piBitValue);
    else
        return FUNCTIONNOTFOUND;
}


int me630DIGetTTLByte(int iBoardNumber, unsigned char *pcValue)
{
    if (pf_me630DIGetTTLByte)
        return (pf_me630DIGetTTLByte)(iBoardNumber, pcValue);
    else
        return FUNCTIONNOTFOUND;
}


int me630DIGetOptoBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    if (pf_me630DIGetOptoBit)
        return (pf_me630DIGetOptoBit)(iBoardNumber, iBitNo, piBitValue);
    else
        return FUNCTIONNOTFOUND;
}


int me630DIGetOptoByte(int iBoardNumber, unsigned char *pcValue)
{
    if (pf_me630DIGetOptoByte)
        return (pf_me630DIGetOptoByte)(iBoardNumber, pcValue);
    else
        return FUNCTIONNOTFOUND;
}


int me630DOSetRelayBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    if (pf_me630DOSetRelayBit)
        return (pf_me630DOSetRelayBit)(iBoardNumber, iBitNo, iBitValue);
    else
        return FUNCTIONNOTFOUND;
}


int me630DOSetRelayWord(int iBoardNumber, unsigned short usValue)
{
    if (pf_me630DOSetRelayWord)
        return (pf_me630DOSetRelayWord)(iBoardNumber, usValue);
    else
        return FUNCTIONNOTFOUND;
}


int me630DIGetRelayBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    if (pf_me630DIGetRelayBit)
        return (pf_me630DIGetRelayBit)(iBoardNumber, iBitNo, piBitValue);
    else
        return FUNCTIONNOTFOUND;
}


int me630DIGetRelayWord(int iBoardNumber, unsigned short *pusValue)
{
    if (pf_me630DIGetRelayWord)
        return (pf_me630DIGetRelayWord)(iBoardNumber, pusValue);
    else
        return FUNCTIONNOTFOUND;
}


int me630GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    if (pf_me630GetIrqCnt)
        return (pf_me630GetIrqCnt)(iBoardNumber, iIRQNum, piCnt);
    else
        return FUNCTIONNOTFOUND;
}


int me630GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    if (pf_me630GetDevInfo)
        return (pf_me630GetDevInfo)(iBoardNumber, pDevInfo);
    else
        return FUNCTIONNOTFOUND;
}


int me630WriteUserString(int iBoardNumber, char* pcUserText)
{
    if (pf_me630WriteUserString)
        return (pf_me630WriteUserString)(iBoardNumber, pcUserText);
    else
        return FUNCTIONNOTFOUND;
}


int me630ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    if (pf_me630ReadUserString)
        return (pf_me630ReadUserString)(iBoardNumber, pcUserText, iMaxLength);
    else
        return FUNCTIONNOTFOUND;
}

int me630DIOResetAll(int iBoardNumber)
{
    if (pf_me630DIOResetAll)
        return (pf_me630DIOResetAll)(iBoardNumber);
    else
        return FUNCTIONNOTFOUND;
}

int me630DIOConfig(int iBoardNumber, int iPortNumber, int iPortDirection)
{
    if (pf_me630DIOConfig)
        return (pf_me630DIOConfig)(iBoardNumber, iPortNumber, iPortDirection);
    else
        return FUNCTIONNOTFOUND;
}

int me630DIOGetBit(int iBoardNumber, int iPortNumber, int iBitNo, int* piBitValue)
{
    if (pf_me630DIOGetBit)
        return (pf_me630DIOGetBit)(iBoardNumber, iPortNumber, iBitNo, piBitValue);
    else
        return FUNCTIONNOTFOUND;
}

int me630DIOGetByte(int iBoardNumber, int iPortNumber, unsigned char* pucByteValue)
{
    if (pf_me630DIOGetByte)
        return (pf_me630DIOGetByte)(iBoardNumber, iPortNumber, pucByteValue);
    else
        return FUNCTIONNOTFOUND;
}

int me630DIOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iBitValue)
{
    if (pf_me630DIOSetBit)
        return (pf_me630DIOSetBit)(iBoardNumber, iPortNumber, iBitNo, iBitValue);
    else
        return FUNCTIONNOTFOUND;
}

int me630DIOSetByte(int iBoardNumber, int iPortNumber, unsigned char ucByteValue)
{
    if (pf_me630DIOSetByte)
        return (pf_me630DIOSetByte)(iBoardNumber, iPortNumber, ucByteValue);
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
