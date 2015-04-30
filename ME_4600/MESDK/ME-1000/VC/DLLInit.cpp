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
USEFILE("..\Common.h");
USEFILE("..\meDefs.h");
USEFILE(".\DLLInit.h");
USEUNIT(".\DLLInit.cpp");
#endif


PF_ME1000GETBOARDVERSION        pf_me1000GetBoardVersion;
PF_ME1000GETDEVINFO             pf_me1000GetDevInfo;
PF_ME1000GETDLLVERSION          pf_me1000GetDLLVersion;
PF_ME1000GETDRIVERVERSION       pf_me1000GetDriverVersion;
PF_ME1000GETSERIALNUMBER        pf_me1000GetSerialNumber;
PF_ME1000READUSERSTRING         pf_me1000ReadUserString;
PF_ME1000WRITEUSERSTRING        pf_me1000WriteUserString;
PF_ME1000GETDRVERRMESS          pf_me1000GetDrvErrMess;
PF_ME1000DIOSETPORTDIRECTION    pf_me1000DIOSetPortDirection;
PF_ME1000DIORESET               pf_me1000DIOReset;
PF_ME1000DIGETBIT               pf_me1000DIGetBit;
PF_ME1000DIGETBYTE              pf_me1000DIGetByte;
PF_ME1000DIGETWORD              pf_me1000DIGetWord;
PF_ME1000DIGETLONG              pf_me1000DIGetLong;
PF_ME1000DOSETBIT               pf_me1000DOSetBit;
PF_ME1000DOSETBYTE              pf_me1000DOSetByte;
PF_ME1000DOSETWORD              pf_me1000DOSetWord;
PF_ME1000DOSETLONG              pf_me1000DOSetLong;


HINSTANCE hDll;


void meOpen(void)
{
    hDll = LoadLibrary(DLLNAME);
    if (hDll == NULL)
    {
        MessageBox( NULL, "DLL not Found", "Error", MB_OK | MB_ICONINFORMATION );
        exit(1);
    }

    pf_me1000GetBoardVersion = (PF_ME1000GETBOARDVERSION)
                        (GetProcAddress (hDll,"me1000GetBoardVersion"));

    pf_me1000GetDevInfo = (PF_ME1000GETDEVINFO)
                        (GetProcAddress (hDll,"me1000GetDevInfo"));

    pf_me1000GetDLLVersion =  (PF_ME1000GETDLLVERSION)
                        (GetProcAddress (hDll,"me1000GetDLLVersion"));

    pf_me1000GetDriverVersion =  (PF_ME1000GETDRIVERVERSION)
                        (GetProcAddress (hDll,"me1000GetDriverVersion"));

    pf_me1000GetSerialNumber =  (PF_ME1000GETSERIALNUMBER)
                        (GetProcAddress (hDll,"me1000GetSerialNumber"));

    pf_me1000ReadUserString =  (PF_ME1000READUSERSTRING)
                        (GetProcAddress (hDll,"me1000ReadUserString"));

    pf_me1000WriteUserString = (PF_ME1000WRITEUSERSTRING)
                        (GetProcAddress (hDll,"me1000WriteUserString"));

    pf_me1000GetDrvErrMess =  (PF_ME1000GETDRVERRMESS)
                        (GetProcAddress (hDll,"me1000GetDrvErrMess"));

    pf_me1000DIOSetPortDirection =  (PF_ME1000DIOSETPORTDIRECTION)
                        (GetProcAddress (hDll,"me1000DIOSetPortDirection"));

    pf_me1000DIOReset =  (PF_ME1000DIORESET)
                        (GetProcAddress (hDll,"me1000DIOReset"));

    pf_me1000DIGetBit =  (PF_ME1000DIGETBIT)
                        (GetProcAddress (hDll,"me1000DIGetBit"));

    pf_me1000DIGetByte =  (PF_ME1000DIGETBYTE)
                        (GetProcAddress (hDll,"me1000DIGetByte"));

    pf_me1000DIGetWord = (PF_ME1000DIGETWORD)
                        (GetProcAddress (hDll,"me1000DIGetWord"));

    pf_me1000DIGetLong = (PF_ME1000DIGETLONG)
                        (GetProcAddress (hDll,"me1000DIGetLong"));

    pf_me1000DOSetBit =  (PF_ME1000DOSETBIT)
                        (GetProcAddress (hDll,"me1000DOSetBit"));

    pf_me1000DOSetByte =  (PF_ME1000DOSETBYTE)
                        (GetProcAddress (hDll,"me1000DOSetByte"));

    pf_me1000DOSetWord =  (PF_ME1000DOSETWORD)
                        (GetProcAddress (hDll,"me1000DOSetWord"));

    pf_me1000DOSetLong =  (PF_ME1000DOSETLONG)
                        (GetProcAddress (hDll,"me1000DOSetLong"));

}





//   -------------------- Wrappers for all Functions -------------------------

int me1000GetBoardVersion(int iBoardNumber, int *piVersion)
{
    if (pf_me1000GetBoardVersion)
        return (pf_me1000GetBoardVersion)(iBoardNumber, piVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}



int me1000GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    if (pf_me1000GetDevInfo)
        return (pf_me1000GetDevInfo)(iBoardNumber,pDevInfo);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me1000GetDLLVersion(void)
{
    if (pf_me1000GetDLLVersion)
        return (pf_me1000GetDLLVersion)();
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me1000GetDriverVersion(int *piVersion)
{
    if (pf_me1000GetDriverVersion)
        return (pf_me1000GetDriverVersion)(piVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me1000GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    if (pf_me1000GetSerialNumber)
        return (pf_me1000GetSerialNumber)(iBoardNumber, piSerialNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me1000ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    if (pf_me1000ReadUserString)
        return (pf_me1000ReadUserString)(iBoardNumber,pcUserText,iMaxLength);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me1000WriteUserString(int iBoardNumber, char* pcUserText)
{
    if (pf_me1000WriteUserString)
        return (pf_me1000WriteUserString)(iBoardNumber, pcUserText);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me1000GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    if (pf_me1000GetDrvErrMess)
        return (pf_me1000GetDrvErrMess)(pcErrortext, iBufferSize);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}



// -------------------- Digital I/O General Functions -------------------------
int me1000DIOSetPortDirection(int iBoardNumber, int iPortNumber, int iDirection)
{
    if (pf_me1000DIOSetPortDirection)
        return (pf_me1000DIOSetPortDirection)(iBoardNumber, iPortNumber, iDirection);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me1000DIOReset(int iBoardNumber)
{
    if (pf_me1000DIOReset)
        return (pf_me1000DIOReset)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

// ---------------------- Digital I/O Input-Functions -----------------------

int me1000DIGetBit (int iBoardNumber, int iPortNumber, int iBitNo, int *piValue)
{
    if (pf_me1000DIGetBit)
        return (pf_me1000DIGetBit)(iBoardNumber,iPortNumber,iBitNo,piValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me1000DIGetByte (int iBoardNumber, int iPortNumber, int iByteNo, int *piValue)
{
    if (pf_me1000DIGetByte)
        return (pf_me1000DIGetByte)(iBoardNumber,iPortNumber,iByteNo,piValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me1000DIGetWord(int iBoardNumber, int iPortNumber, int iWordNo, int *piValue)
{
    if (pf_me1000DIGetWord)
        return (pf_me1000DIGetWord)(iBoardNumber,iPortNumber,iWordNo,piValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me1000DIGetLong(int iBoardNumber, int iPortNumber, int *piValue)
{
    if (pf_me1000DIGetLong)
        return (pf_me1000DIGetLong)(iBoardNumber,iPortNumber,piValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


// -------------------------- Digital I/O Output-Functions ------------------

int me1000DOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iValue)
{
    if (pf_me1000DOSetBit)
        return (pf_me1000DOSetBit)(iBoardNumber,iPortNumber,iBitNo,iValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me1000DOSetByte(int iBoardNumber, int iPortNumber, int iByteNo, int iValue)
{
    if (pf_me1000DOSetByte)
        return (pf_me1000DOSetByte)(iBoardNumber,iPortNumber,iByteNo,iValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me1000DOSetWord(int iBoardNumber, int iPortNumber, int iWordNo, int iValue)
{
    if (pf_me1000DOSetWord)
        return (pf_me1000DOSetWord)(iBoardNumber,iPortNumber,iWordNo,iValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me1000DOSetLong(int iBoardNumber, int iPortNumber, int iValue)
{
    if (pf_me1000DOSetLong)
        return (pf_me1000DOSetLong)(iBoardNumber,iPortNumber,iValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


/* -------------------------  Close Function ----------------------------*/
void meClose (void)
{
    if (hDll)
    {
        FreeLibrary(hDll);
    }
}
