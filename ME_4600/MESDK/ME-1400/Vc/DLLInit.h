/*----------------------------------------------------------------------------
    File: DLLINIT.H
------------------------------------------------------------------------------

    Meilhaus Electronic GmbH

    Header file containing Typedefs for the board.  This header is
    for use in projects using dynamic function calls (no library file is
    included in the project)

    Version 1.01:   020626
-------------------------------------------------------------------------------
    Author: Andreas Bernau / Ralph Timm
-----------------------------------------------------------------------------*/


#ifndef DLLINIT_H
#define DLLINIT_H

#define SUCCESS             0x01
#define DLLNOTFOUND         0x02
#define FUNCTIONNOTFOUND    0x03
#define DLLNAME             "me1400.dll"


typedef   int(__cdecl *PF_ME1400GETDLLVERSION) (void);
typedef   int(__cdecl *PF_ME1400GETDRIVERVERSION) (int *piDriverVersion);
typedef   int(__cdecl *PF_ME1400GETBOARDVERSION) (int iBoardNumber, int *piVersion);
typedef   int(__cdecl *PF_ME1400GETDRVERRMESS) (char *pcErrorText);

typedef   int(__cdecl *PF_ME1400ENABLEINT) (int iBoardNumber, PSERVICE_PROC IrqFunc, int iServiceNo);
typedef   int(__cdecl *PF_ME1400DISABLEINT) (int iBoardNumber, int iServiceNo);
typedef   int(__cdecl *PF_ME1400GETIRQCNT) (int iBoardNumber, int* piCnt);

typedef   int(__cdecl *PF_ME1400CNTINITSRC) (int iBoardNumber, int iCounter, int iCounterSource);
typedef   int(__cdecl *PF_ME1400CNTWRITE) (int iBoardNumber, int iCounter,int iMode, int iValue);
typedef   int(__cdecl *PF_ME1400CNTREAD) (int iBoardNumber, int iCounter, int* piValue);

/*==============================================================*/
// PWM functions (pulse width modulation) 
typedef   int(__cdecl *PF_ME1400CNTPWMSTART) (int iBoardNumber, int iDeviceNumber, int iClockSource, int iPrescaler, int iDutyCycle);
typedef   int(__cdecl *PF_ME1400CNTPWMSTOP) (int iBoardNumber, int iDeviceNumber);
/*==============================================================*/

typedef   int(__cdecl *PF_ME1400DIOSETPORTDIRECTION) (int iBoardNumber, int iPort, int iDir);
typedef   int(__cdecl *PF_ME1400DIGETBIT) (int iBoardNumber, int iPortNo, int iBitNo, int *piValue);
typedef   int(__cdecl *PF_ME1400DIGETBYTE) (int iBoardNumber, int iPortNo, int *piValue);
typedef   int(__cdecl *PF_ME1400DOSETBIT) (int iBoardNumber, int iPortNo, int iBitNo, int iBitValue);
typedef   int(__cdecl *PF_ME1400DOSETBYTE) (int iBoardNumber, int iPortNo, int iValue);

typedef   int(__cdecl *PF_ME1400GETSERIALNUMBER) (int iBoardNumber, int *piSerialNumber);
typedef   int(__cdecl *PF_ME1400GETDEVINFO) (int iBoardNumber, PDEVICEINFOSTRUCT DevInfo);
typedef   int(__cdecl *PF_ME1400INPORTBYTE) (int iBoardNumber, int iPortOffset, int* pbValue);
typedef   int(__cdecl *PF_ME1400OUTPORTBYTE) (int iBoardNumber, int iPortOffset, int bValue);
typedef   int(__cdecl *PF_ME1400INPORTWORD) (int iBoardNumber, int iPortOffset, int* pwValue);
typedef   int(__cdecl *PF_ME1400OUTPORTWORD) (int iBoardNumber, int iPortOffset, int wValue);
typedef   int(__cdecl *PF_ME1400INPORTDWORD) (int iBoardNumber, int iPortOffset, int* pwValue);
typedef   int(__cdecl *PF_ME1400OUTPORTDWORD) (int iBoardNumber, int iPortOffset, int wValue);
typedef   int(__cdecl *PF_ME1400RESETBOARD) (int iBoardNumber);
typedef   int(__cdecl *PF_ME1400INITBOARD) (int iBoardNumber);

typedef   int(__cdecl *PF_ME1400WRITEUSERSTRING) (int iBoardNumber, char* pcUserText);
typedef   int(__cdecl *PF_ME1400READUSERSTRING) (int iBoardNumber, char* pcUserText, int iMaxLength);
typedef   int(__cdecl *PF_ME1400INITMODETIMERA) (int iBoardNumber, int CtrlWordA);
typedef   int(__cdecl *PF_ME1400INITMODETIMERB) (int iBoardNumber, int CtrlWordB);
typedef   int(__cdecl *PF_ME1400SETMULTIFUNCTIONPIN) (int iBoardNumber, int MultiPin);
typedef   int(__cdecl *PF_ME1400DIOSETMODE) (int iBoardNumber,int iPio, int iMode);



// -------------------- Function Prototypes --------------------------------

void meOpen (void);
void meClose (void);

int me1400GetDLLVersion (void);
int me1400GetDriverVersion(int *piDriverVersion);
int me1400GetBoardVersion(int iBoardNumber, int *piVersion);
int me1400GetDrvErrMess (char *pcErrorText);

int me1400EnableInt (int iBoardNumber, PSERVICE_PROC IrqFunc, int iServiceNo);
int me1400DisableInt (int iBoardNumber, int iServiceNo);
int me1400GetIrqCnt(int iBoardNumber, int *ipIrqCnt);

int me1400CntInitSrc(int iBoardNumber, int iCounter, int iCounterSource);
int me1400CntWrite (int iBoardNumber, int iCounter,int iMode, int iValue);
int me1400CntRead (int iBoardNumber, int iCounter, int* piValue);

/*==============================================================*/
// PWM functions (pulse width modulation)
int me1400CntPWMStart(int iBoardNumber, int iDeviceNumber, int iClockSource, int iPrescaler, int iDutyCycle);
int me1400CntPWMStop(int iBoardNumber, int iDeviceNumber);
/*==============================================================*/

int me1400DIOSetPortDirection (int iBoardNumber, int iPort, int iDir);
int me1400DIGetBit (int iBoardNumber, int iPortNo, int iBitNo, int *piValue);
int me1400DIGetByte (int iBoardNumber, int iPortNo, int *piValue);
int me1400DOSetBit (int iBoardNumber, int iPortNo, int iBitNo, int iBitValue);
int me1400DOSetByte (int iBoardNumber, int iPortNo, int iValue);

int me1400GetSerialNumber(int iBoardNumber, int *piSerialNumber);
int me1400GetDevInfo (int iBoardNumber, PDEVICEINFOSTRUCT DevInfo);
int me1400InportByte(int iBoardNumber, int iPortOffset, int* pbValue);
int me1400OutportByte(int iBoardNumber, int iPortOffset, int bValue);
int me1400InportWord(int iBoardNumber, int iPortOffset, int* pwValue);
int me1400OutportWord(int iBoardNumber, int iPortOffset, int wValue);
int me1400InportDWord(int iBoardNumber, int iPortOffset, int* pwValue);
int me1400OutportDWord(int iBoardNumber, int iPortOffset, int wValue);
int me1400ResetBoard(int iBoardNumber);
int me1400InitBoard(int iBoardNumber);

int me1400WriteUserString(int iBoardNumber, char* pcUserText);
int me1400ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength);
int me1400InitModeTimerA (int iBoardNumber, int CtrlWordA);
int me1400InitModeTimerB (int iBoardNumber, int CtrlWordB);
int me1400SetMultifunctionPin (int iBoardNumber, int MultiPin);
int me1400DIOSetMode(int iBoardNumber,int iPio, int iMode);

#endif
