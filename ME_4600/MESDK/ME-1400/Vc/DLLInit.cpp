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



PF_ME1400GETDLLVERSION          pf_me1400GetDLLVersion;
PF_ME1400GETDRIVERVERSION       pf_me1400GetDriverVersion;
PF_ME1400GETBOARDVERSION        pf_me1400GetBoardVersion;
PF_ME1400GETDRVERRMESS          pf_me1400GetDrvErrMess;

PF_ME1400ENABLEINT              pf_me1400EnableInt;
PF_ME1400DISABLEINT             pf_me1400DisableInt;
PF_ME1400GETIRQCNT              pf_me1400GetIrqCnt;

PF_ME1400CNTINITSRC             pf_me1400CntInitSrc;
PF_ME1400CNTWRITE               pf_me1400CntWrite;
PF_ME1400CNTREAD                pf_me1400CntRead;

/*==============================================================*/
PF_ME1400CNTPWMSTART            pf_me1400CntPWMStart;
PF_ME1400CNTPWMSTOP             pf_me1400CntPWMStop;
/*==============================================================*/

PF_ME1400DIOSETPORTDIRECTION    pf_me1400DIOSetPortDirection;
PF_ME1400DIGETBIT               pf_me1400DIGetBit;
PF_ME1400DIGETBYTE              pf_me1400DIGetByte;
PF_ME1400DOSETBIT               pf_me1400DOSetBit;  
PF_ME1400DOSETBYTE              pf_me1400DOSetByte;

PF_ME1400GETSERIALNUMBER        pf_me1400GetSerialNumber;
PF_ME1400GETDEVINFO             pf_me1400GetDevInfo;    
PF_ME1400INPORTBYTE             pf_me1400InportByte;
PF_ME1400OUTPORTBYTE            pf_me1400OutportByte;
PF_ME1400INPORTWORD             pf_me1400InportWord;
PF_ME1400OUTPORTWORD            pf_me1400OutportWord;
PF_ME1400INPORTDWORD            pf_me1400InportDWord;
PF_ME1400OUTPORTDWORD           pf_me1400OutportDWord;
PF_ME1400RESETBOARD             pf_me1400ResetBoard;
PF_ME1400INITBOARD              pf_me1400InitBoard;

PF_ME1400WRITEUSERSTRING        pf_me1400WriteUserString;
PF_ME1400READUSERSTRING         pf_me1400ReadUserString;
PF_ME1400INITMODETIMERA         pf_me1400InitModeTimerA;
PF_ME1400INITMODETIMERB         pf_me1400InitModeTimerB;
PF_ME1400SETMULTIFUNCTIONPIN    pf_me1400SetMultifunctionPin;
PF_ME1400DIOSETMODE             pf_me1400DIOSetMode;



HINSTANCE hDll;


void meOpen(void)
{
    hDll = LoadLibrary(DLLNAME);    // load the library
    if (hDll == NULL)
    {
        MessageBox( NULL, "DLL not Found", "Error", MB_OK | MB_ICONINFORMATION );
        exit(1);
    }

    pf_me1400GetDLLVersion  = (PF_ME1400GETDLLVERSION)
                            (GetProcAddress (hDll,"me1400GetDLLVersion"));

    pf_me1400GetDriverVersion  = (PF_ME1400GETDRIVERVERSION)
                            (GetProcAddress (hDll,"me1400GetDriverVersion"));

    pf_me1400GetBoardVersion  = (PF_ME1400GETBOARDVERSION)
                            (GetProcAddress (hDll,"me1400GetBoardVersion"));

    pf_me1400GetDrvErrMess  = (PF_ME1400GETDRVERRMESS)
                            (GetProcAddress (hDll,"me1400GetDrvErrMess"));


    pf_me1400EnableInt      = (PF_ME1400ENABLEINT)
                            (GetProcAddress (hDll,"me1400EnableInt"));

    pf_me1400DisableInt     = (PF_ME1400DISABLEINT)
                            (GetProcAddress (hDll,"me1400DisableInt"));

    pf_me1400GetIrqCnt      = (PF_ME1400GETIRQCNT)
                            (GetProcAddress (hDll,"me1400GetIrqCnt"));


    pf_me1400CntInitSrc     = (PF_ME1400CNTINITSRC)
                            (GetProcAddress (hDll,"me1400CntInitSrc"));

    pf_me1400CntWrite       = (PF_ME1400CNTWRITE)
                            (GetProcAddress (hDll,"me1400CntWrite"));

    pf_me1400CntRead        = (PF_ME1400CNTREAD)
                            (GetProcAddress (hDll,"me1400CntRead"));

/*==============================================================*/
    pf_me1400CntPWMStart    = (PF_ME1400CNTPWMSTART)
                            (GetProcAddress (hDll,"me1400CntPWMStart"));
                            
    pf_me1400CntPWMStop        = (PF_ME1400CNTPWMSTOP)
                            (GetProcAddress (hDll,"me1400CntPWMStop"));
/*==============================================================*/



    pf_me1400DIOSetPortDirection   = (PF_ME1400DIOSETPORTDIRECTION)
                            (GetProcAddress (hDll,"me1400DIOSetPortDirection"));

    pf_me1400DIGetBit       = (PF_ME1400DIGETBIT)
                            (GetProcAddress (hDll,"me1400DIGetBit"));

    pf_me1400DIGetByte      = (PF_ME1400DIGETBYTE)
                            (GetProcAddress (hDll,"me1400DIGetByte"));

    pf_me1400DOSetBit       = (PF_ME1400DOSETBIT)
                            (GetProcAddress (hDll,"me1400DOSetBit"));

    pf_me1400DOSetByte      = (PF_ME1400DOSETBYTE)
                            (GetProcAddress (hDll,"me1400DOSetByte"));


    pf_me1400GetSerialNumber = (PF_ME1400GETSERIALNUMBER)
                            (GetProcAddress (hDll,"me1400GetSerialNumber"));
   
    pf_me1400GetDevInfo     = (PF_ME1400GETDEVINFO)
                            (GetProcAddress (hDll,"me1400GetDevInfo"));

    pf_me1400InportByte     = (PF_ME1400INPORTBYTE)
                            (GetProcAddress (hDll,"me1400InportByte"));
                            
    pf_me1400OutportByte    = (PF_ME1400OUTPORTBYTE)
                            (GetProcAddress (hDll,"me1400OutportByte"));
                            
    pf_me1400InportWord     = (PF_ME1400INPORTWORD)
                            (GetProcAddress (hDll,"me1400InportWord"));
                            
    pf_me1400OutportWord    = (PF_ME1400OUTPORTWORD)
                            (GetProcAddress (hDll,"me1400OutportWord"));
                            
    pf_me1400InportDWord    = (PF_ME1400INPORTDWORD)
                            (GetProcAddress (hDll,"me1400InportDWord"));
                            
    pf_me1400OutportDWord   = (PF_ME1400OUTPORTDWORD)
                            (GetProcAddress (hDll,"me1400OutportDWord"));
                            
    pf_me1400ResetBoard     = (PF_ME1400RESETBOARD)
                            (GetProcAddress (hDll,"me1400ResetBoard"));
                            
    pf_me1400InitBoard      = (PF_ME1400INITBOARD)
                            (GetProcAddress (hDll,"me1400InitBoard"));


    pf_me1400WriteUserString  = (PF_ME1400WRITEUSERSTRING) 
                            (GetProcAddress (hDll,"me1400WriteUserString"));

    pf_me1400ReadUserString = (PF_ME1400READUSERSTRING)  
                            (GetProcAddress (hDll,"me1400ReadUserString"));

    pf_me1400InitModeTimerA = (PF_ME1400INITMODETIMERA)
                            (GetProcAddress (hDll,"me1400InitModeTimerA"));

    pf_me1400InitModeTimerB = (PF_ME1400INITMODETIMERB)
                            (GetProcAddress (hDll,"me1400InitModeTimerB"));

    pf_me1400SetMultifunctionPin  = (PF_ME1400SETMULTIFUNCTIONPIN)
                            (GetProcAddress (hDll,"me1400SetMultifunctionPin"));

    pf_me1400DIOSetMode     = (PF_ME1400DIOSETMODE)
                            (GetProcAddress (hDll,"me1400DIOSetMode"));
}

//   -------------------- Wrappers for all Functions -------------------------

int me1400GetDLLVersion (void)
{
    if (pf_me1400GetDLLVersion)
        return (pf_me1400GetDLLVersion)();
    else
        return FUNCTIONNOTFOUND;
}


int me1400GetDriverVersion (int *piVersion)
{
    if (pf_me1400GetDriverVersion)
        return (pf_me1400GetDriverVersion)(piVersion);
    else
        return FUNCTIONNOTFOUND;
}


int me1400GetBoardVersion(int iBoardNumber, int *piVersion)
{
    if (pf_me1400GetBoardVersion)
        return (pf_me1400GetBoardVersion)(iBoardNumber, piVersion);
    else
        return FUNCTIONNOTFOUND;
}


int me1400GetDrvErrMess (char *pcErrorText)
{
    if (pf_me1400GetDrvErrMess)
        return (pf_me1400GetDrvErrMess)(pcErrorText);
    else
        return FUNCTIONNOTFOUND;
}



int me1400EnableInt  (int iBoardNumber, PSERVICE_PROC IrqFunc, int iServiceNo)
{
    if (pf_me1400EnableInt )
        return (pf_me1400EnableInt)(iBoardNumber, IrqFunc, iServiceNo);
    else
        return FUNCTIONNOTFOUND;
}


int me1400DisableInt (int iBoardNumber, int iServiceNo)
{
    if (pf_me1400DisableInt)
        return (pf_me1400DisableInt)(iBoardNumber, iServiceNo);
    else
        return FUNCTIONNOTFOUND;
}


int me1400GetIrqCnt (int iBoardNumber, int* IrqCnt)
{
    if (pf_me1400GetIrqCnt)
        return (pf_me1400GetIrqCnt)(iBoardNumber, IrqCnt);
    else
        return FUNCTIONNOTFOUND;
}



int me1400CntInitSrc (int iBoardNumber, int iCounter,int iCounterSource)
{
    if (pf_me1400CntInitSrc)
        return (pf_me1400CntInitSrc)(iBoardNumber, iCounter, iCounterSource);
    else
        return FUNCTIONNOTFOUND;
}


int me1400CntWrite (int iBoardNumber, int iCounter,int iMode, int iValue)
{
    if (pf_me1400CntWrite)
        return (pf_me1400CntWrite)(iBoardNumber, iCounter, iMode, iValue);
    else
        return FUNCTIONNOTFOUND;
}


int me1400CntRead (int iBoardNumber, int iCounter, int* piValue)
{
    if (pf_me1400CntRead)
        return (pf_me1400CntRead)(iBoardNumber, iCounter, piValue);
    else
        return FUNCTIONNOTFOUND;
}



/*==============================================================*/
// PWM functions (pulse width modulation)
int me1400CntPWMStart (int iBoardNumber, int iDeviceNumber, int iClockSource, int iPrescaler, int iDutyCycle)
{
    if (pf_me1400CntPWMStart)
        return (pf_me1400CntPWMStart)(iBoardNumber, iDeviceNumber, iClockSource, iPrescaler, iDutyCycle);
    else
        return FUNCTIONNOTFOUND;
}

int me1400CntPWMStop (int iBoardNumber, int iDeviceNumber)
{
    if (pf_me1400CntPWMStop)
        return (pf_me1400CntPWMStop)(iBoardNumber, iDeviceNumber);
    else
        return FUNCTIONNOTFOUND;
}
/*==============================================================*/



int me1400DIOSetPortDirection (int iBoardNumber, int iPort, int iDir)
{
    if (pf_me1400DIOSetPortDirection)
        return (pf_me1400DIOSetPortDirection)(iBoardNumber, iPort, iDir);
    else
        return FUNCTIONNOTFOUND;
}

int me1400DIGetBit (int iBoardNumber, int iPortNo, int iBitNo, int *piValue)
{
    if (pf_me1400DIGetBit)
        return (pf_me1400DIGetBit)(iBoardNumber, iPortNo, iBitNo, piValue);
    else
        return FUNCTIONNOTFOUND;
}

int me1400DIGetByte (int iBoardNumber, int iPortNo, int *piValue)
{
    if (pf_me1400DIGetByte)
        return (pf_me1400DIGetByte)(iBoardNumber, iPortNo, piValue);
    else
        return FUNCTIONNOTFOUND;
}

int me1400DOSetBit (int iBoardNumber, int iPortNo, int iBitNo, int iBitValue)
{
    if (pf_me1400DOSetBit)
        return (pf_me1400DOSetBit)(iBoardNumber, iPortNo, iBitNo, iBitValue);
    else
        return FUNCTIONNOTFOUND;
}

int me1400DOSetByte (int iBoardNumber, int iPortNo, int iValue)
{
    if (pf_me1400DOSetByte)
        return (pf_me1400DOSetByte)(iBoardNumber, iPortNo, iValue);
    else
        return FUNCTIONNOTFOUND;
}



int me1400GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    if (pf_me1400GetSerialNumber)
        return (pf_me1400GetSerialNumber)(iBoardNumber, piSerialNumber);
    else
        return FUNCTIONNOTFOUND;
}

int me1400GetDevInfo (int iBoardNumber, PDEVICEINFOSTRUCT DevInfo)
{
    if (pf_me1400GetDevInfo)
        return (pf_me1400GetDevInfo)(iBoardNumber, DevInfo);
    else
        return FUNCTIONNOTFOUND;
}

int me1400InportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    if (pf_me1400InportByte)
        return (pf_me1400InportByte)(iBoardNumber, iPortOffset, pbValue);
    else
        return FUNCTIONNOTFOUND;
}

int me1400OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    if (pf_me1400OutportByte)
        return (pf_me1400OutportByte)(iBoardNumber, iPortOffset, bValue);
    else
        return FUNCTIONNOTFOUND;
}

int me1400InportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    if (pf_me1400InportWord)
        return (pf_me1400InportWord)(iBoardNumber, iPortOffset, pwValue);
    else
        return FUNCTIONNOTFOUND;
}

int me1400OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    if (pf_me1400OutportWord)
        return (pf_me1400OutportWord)(iBoardNumber, iPortOffset, wValue);
    else
        return FUNCTIONNOTFOUND;
}

int me1400InportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    if (pf_me1400InportDWord)
        return (pf_me1400InportDWord)(iBoardNumber, iPortOffset, pwValue);
    else
        return FUNCTIONNOTFOUND;
}

int me1400OutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    if (pf_me1400OutportDWord)
        return (pf_me1400OutportDWord)(iBoardNumber, iPortOffset, wValue);
    else
        return FUNCTIONNOTFOUND;
}

int me1400ResetBoard(int iBoardNumber)
{
    if (pf_me1400ResetBoard)
        return (pf_me1400ResetBoard)(iBoardNumber);
    else
        return FUNCTIONNOTFOUND;
}

int me1400InitBoard(int iBoardNumber)
{
    if (pf_me1400InitBoard)
        return (pf_me1400InitBoard)(iBoardNumber);
    else
        return FUNCTIONNOTFOUND;
}



int me1400WriteUserString(int iBoardNumber, char* pcUserText)
{
    if (pf_me1400WriteUserString)
        return (pf_me1400WriteUserString)(iBoardNumber, pcUserText);
    else
        return FUNCTIONNOTFOUND;
}


int me1400ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    if (pf_me1400ReadUserString)
        return (pf_me1400ReadUserString)(iBoardNumber, pcUserText, iMaxLength);
    else
        return FUNCTIONNOTFOUND;
}

int me1400InitModeTimerA (int iBoardNumber, int CtrlWordA)
{
    if (pf_me1400InitModeTimerA)
        return (pf_me1400InitModeTimerA)(iBoardNumber, CtrlWordA);
    else
        return FUNCTIONNOTFOUND;
}

int me1400InitModeTimerB (int iBoardNumber, int CtrlWordB)
{
    if (pf_me1400InitModeTimerB)
        return (pf_me1400InitModeTimerB)(iBoardNumber, CtrlWordB);
    else
        return FUNCTIONNOTFOUND;
}

int me1400SetMultifunctionPin (int iBoardNumber, int MultiPin)
{
    if (pf_me1400SetMultifunctionPin)
        return (pf_me1400SetMultifunctionPin)(iBoardNumber,  MultiPin);
    else
        return FUNCTIONNOTFOUND;
}

int me1400DIOSetMode(int iBoardNumber,int iPio, int iMode)
{
    if (pf_me1400DIOSetMode)
        return (pf_me1400DIOSetMode)(iBoardNumber, iPio, iMode);
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
