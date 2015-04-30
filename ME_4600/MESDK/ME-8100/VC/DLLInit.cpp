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



PF_ME8100GETDLLVERSION          pf_me8100GetDLLVersion;
PF_ME8100GETBOARDVERSION        pf_me8100GetBoardVersion;
PF_ME8100PROMVERSION            pf_me8100PROMVersion;
PF_ME8100ENABLEINT              pf_me8100EnableInt;
PF_ME8100DISABLEINT             pf_me8100DisableInt;
PF_ME8100GETDRVERRMESS          pf_me8100GetDrvErrMess;
PF_ME8100DIGETINTSTATUS         pf_me8100DIGetIntStatus;
PF_ME8100DIOSETINTMODE          pf_me8100DIOSetIntMode;
PF_ME8100DIOSETTRISTATEON       pf_me8100DIOSetTristateON;
PF_ME8100DIOSETTRISTATEOFF      pf_me8100DIOSetTristateOFF;
PF_ME8100DIOSETPATTERN          pf_me8100DIOSetPattern;
PF_ME8100DIOSETMASK             pf_me8100DIOSetMask;
PF_ME8100DIGETBIT               pf_me8100DIGetBit;
PF_ME8100DIGETWORD              pf_me8100DIGetWord;
PF_ME8100DOSETBIT               pf_me8100DOSetBit;
PF_ME8100DOSETWORD              pf_me8100DOSetWord;
PF_ME8100GETIRQCOUNT            pf_me8100GetIrqCnt;
PF_ME8100GETDEVINFO             pf_me8100GetDevInfo;
PF_ME8100WRITEUSERSTRING        pf_me8100WriteUserString;
PF_ME8100READUSERSTRING         pf_me8100ReadUserString;
PF_ME8100CNTWRITE               pf_me8100CntWrite;
PF_ME8100CNTREAD                pf_me8100CntRead;
PF_ME8100SETSINKSOURCEMODE      pf_me8100SetSinkSourceMode;



HINSTANCE hDll;


void meOpen(void)
{
    hDll = LoadLibrary(DLLNAME);
    if (hDll == NULL)
    {
        MessageBox( NULL, "DLL not Found", "Error", MB_OK | MB_ICONINFORMATION );
        exit(1);
    }

    pf_me8100GetDLLVersion =  (PF_ME8100GETDLLVERSION)
                        (GetProcAddress (hDll,"_me8100GetDLLVersion"));

    pf_me8100GetBoardVersion = (PF_ME8100GETBOARDVERSION)
                        (GetProcAddress (hDll,"_me8100GetBoardVersion"));

    pf_me8100PROMVersion =  (PF_ME8100PROMVERSION)
                        (GetProcAddress (hDll,"_me8100PROMVersion"));

    pf_me8100EnableInt =  (PF_ME8100ENABLEINT)
                        (GetProcAddress (hDll,"_me8100EnableInt"));

    pf_me8100DisableInt =  (PF_ME8100DISABLEINT)
                        (GetProcAddress (hDll,"_me8100DisableInt"));

    pf_me8100GetDrvErrMess =  (PF_ME8100GETDRVERRMESS)
                        (GetProcAddress (hDll,"_me8100GetDrvErrMess"));

    pf_me8100DIGetIntStatus = (PF_ME8100DIGETINTSTATUS)
                        (GetProcAddress (hDll,"_me8100DIGetIntStatus"));

    pf_me8100DIOSetIntMode =  (PF_ME8100DIOSETINTMODE)
                        (GetProcAddress (hDll,"_me8100DIOSetIntMode"));

    pf_me8100DIOSetTristateON = (PF_ME8100DIOSETTRISTATEON)
                        (GetProcAddress (hDll,"_me8100DIOSetTristateON"));

    pf_me8100DIOSetTristateOFF = (PF_ME8100DIOSETTRISTATEOFF)
                        (GetProcAddress (hDll,"_me8100DIOSetTristateOFF"));

    pf_me8100DIOSetPattern =  (PF_ME8100DIOSETPATTERN)
                        (GetProcAddress (hDll,"_me8100DIOSetPattern"));

    pf_me8100DIOSetMask =  (PF_ME8100DIOSETMASK)
                        (GetProcAddress (hDll,"_me8100DIOSetMask"));

    pf_me8100DIGetBit =  (PF_ME8100DIGETBIT)
                        (GetProcAddress (hDll,"_me8100DIGetBit"));

    pf_me8100DIGetWord = (PF_ME8100DIGETWORD)
                        (GetProcAddress (hDll,"_me8100DIGetWord"));

    pf_me8100DOSetBit =  (PF_ME8100DOSETBIT)
                        (GetProcAddress (hDll,"_me8100DOSetBit"));

    pf_me8100DOSetWord =  (PF_ME8100DOSETWORD)
                        (GetProcAddress (hDll,"_me8100DOSetWord"));

    pf_me8100GetIrqCnt =  (PF_ME8100GETIRQCOUNT)
                        (GetProcAddress (hDll,"_me8100GetIrqCnt"));

    pf_me8100GetDevInfo = (PF_ME8100GETDEVINFO)
                        (GetProcAddress (hDll,"_me8100GetDevInfo"));

    pf_me8100WriteUserString = (PF_ME8100WRITEUSERSTRING)
                        (GetProcAddress (hDll,"_me8100WriteUserString"));

    pf_me8100ReadUserString =  (PF_ME8100READUSERSTRING)
                        (GetProcAddress (hDll,"_me8100ReadUserString"));

    pf_me8100CntWrite = (PF_ME8100CNTWRITE)
                        (GetProcAddress (hDll,"_me8100CntWrite"));

    pf_me8100CntRead =  (PF_ME8100CNTREAD)
                        (GetProcAddress (hDll,"_me8100CntRead"));

    pf_me8100SetSinkSourceMode =  (PF_ME8100SETSINKSOURCEMODE)
                        (GetProcAddress (hDll,"_me8100SetSinkSourceMode"));
}




//   -------------------- Wrappers for all Functions -------------------------


/* ----------------------- General Functions ----------------------------- */

int me8100GetDLLVersion(void)
{
    if (pf_me8100GetDLLVersion)
        return (pf_me8100GetDLLVersion)();
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100GetBoardVersion(int iBoardNumber, int *piVersion)
{
    if (pf_me8100GetBoardVersion)
        return (pf_me8100GetBoardVersion)(iBoardNumber, piVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100PROMVersion(int iBoardNumber, int *piVersion)
{
    if (pf_me8100PROMVersion)
        return (pf_me8100PROMVersion)(iBoardNumber, piVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100EnableInt(int iBoardNumber, int iRegisterSet,
							ME_PSERVICE_PROC IrqFunc, int iContext)
{
    if (pf_me8100EnableInt)
        return (pf_me8100EnableInt)(iBoardNumber, iRegisterSet,
							                    IrqFunc, iContext);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100DisableInt(int iBoardNumber, int iRegisterSet)
{
    if (pf_me8100DisableInt)
        return (pf_me8100DisableInt)(iBoardNumber, iRegisterSet);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}
//---------------------------------------------------------------------------

// ---------------------  Error Routine  -------------------------------------

int me8100GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    if (pf_me8100GetDrvErrMess)
        return (pf_me8100GetDrvErrMess)(pcErrortext, iBufferSize);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}
//---------------------------------------------------------------------------


// -------------------- Digital I/O General Functions -------------------------

int me8100DIGetIntStatus(int iBoardNumber, int iRegisterSet, int *piValue)
{
    if (pf_me8100DIGetIntStatus)
        return (pf_me8100DIGetIntStatus)(iBoardNumber, iRegisterSet,piValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100DIOSetIntMode(int iBoardNumber, int iRegisterSet, int iMode)
{
    if (pf_me8100DIOSetIntMode)
        return (pf_me8100DIOSetIntMode)(iBoardNumber,iRegisterSet,iMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100DIOSetTristateON(int iBoardNumber, int iRegisterSet)
{
    if (pf_me8100DIOSetTristateON)
        return (pf_me8100DIOSetTristateON)(iBoardNumber,iRegisterSet);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100DIOSetTristateOFF(int iBoardNumber, int iRegisterSet)
{
    if (pf_me8100DIOSetTristateOFF)
        return (pf_me8100DIOSetTristateOFF)(iBoardNumber,iRegisterSet);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100DIOSetPattern(int iBoardNumber, int iRegisterSet, int iPattern)
{
    if (pf_me8100DIOSetPattern)
        return (pf_me8100DIOSetPattern)(iBoardNumber,iRegisterSet,iPattern);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100DIOSetMask(int iBoardNumber, int iRegisterSet, int iMask)
{
    if (pf_me8100DIOSetMask)
        return (pf_me8100DIOSetMask)(iBoardNumber,iRegisterSet,iMask);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}
//---------------------------------------------------------------------------


// ---------------------- Digital I/O Input-Functions -----------------------

int me8100DIGetBit (int iBoardNumber, int iRegisterSet, int iBitNo, int *piBitValue)
{
    if (pf_me8100DIGetBit)
        return (pf_me8100DIGetBit)(iBoardNumber,iRegisterSet,iBitNo,piBitValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100DIGetWord(int iBoardNumber, int iRegisterSet, int *piValue)
{
    if (pf_me8100DIGetWord)
        return (pf_me8100DIGetWord)(iBoardNumber,iRegisterSet,piValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}
//---------------------------------------------------------------------------

// -------------------------- Digital I/O Output-Functions ------------------

int me8100DOSetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int iBitValue)
{
    if (pf_me8100DOSetBit)
        return (pf_me8100DOSetBit)(iBoardNumber,iRegisterSet,iBitNo,iBitValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100DOSetWord(int iBoardNumber, int iRegisterSet, int iValue)
{
    if (pf_me8100DOSetWord)
        return (pf_me8100DOSetWord)(iBoardNumber,iRegisterSet,iValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}
//---------------------------------------------------------------------------

// ---------------------------- New Routines --------------------------------

int me8100GetIrqCnt(int iBoardNumber, int iRegisterSet, int* piCnt)
{
    if (pf_me8100GetIrqCnt)
        return (pf_me8100GetIrqCnt)(iBoardNumber,iRegisterSet, piCnt);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    if (pf_me8100GetDevInfo)
        return (pf_me8100GetDevInfo)(iBoardNumber,pDevInfo);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100WriteUserString(int iBoardNumber, char* pcUserText)
{
    if (pf_me8100WriteUserString)
        return (pf_me8100WriteUserString)(iBoardNumber, pcUserText);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    if (pf_me8100ReadUserString)
        return (pf_me8100ReadUserString)(iBoardNumber,pcUserText,iMaxLength);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}
//---------------------------------------------------------------------------


// ------------------------------- Counter 8254 functions --------------------

int me8100CntWrite(int iBoardNumber, int iCounter, int iMode, int iValue)
{
    if (pf_me8100CntWrite)
        return (pf_me8100CntWrite)(iBoardNumber,iCounter,iMode,iValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me8100CntRead(int iBoardNumber, int iCounter, int* piValue)
{
    if (pf_me8100CntRead)
        return (pf_me8100CntRead)(iBoardNumber, iCounter,piValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}
//---------------------------------------------------------------------------


// -------------------------------- Sink/Source ----------------------------

int me8100SetSinkSourceMode(int iBoardNumber, int iRegisterSet, int imode)
{
    if (pf_me8100SetSinkSourceMode)
        return (pf_me8100SetSinkSourceMode)(iBoardNumber,iRegisterSet,imode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

/* -----------------------------------------------------------------------*/

/* -----------------------------------------------------------------------*/


/* -------------------------  Close Function ----------------------------*/
void meClose (void)
{
    if (hDll)
    {
        FreeLibrary(hDll);
    }
}
