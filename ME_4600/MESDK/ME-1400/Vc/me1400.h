// File Name 'me1400.h'
// Header File for me1400.dll

// IMPORTANT NOTE :
// Only for use with Microsoft Visual C++ V4.0 or later. For other 
// compilers you have to change the macro "_declspec(dllimport)" into 
// the form your compiler needs to import functions from an external dll !

#ifndef ME1400_H
#define ME1400_H

#include "meDefs.h"


// GET functions (general functions to get some information)
extern "C" int _declspec(dllimport) _cdecl me1400GetDLLVersion();
extern "C" int _declspec(dllimport) _cdecl me1400GetDriverVersion(int *piDriverVersion);
extern "C" int _declspec(dllimport) _cdecl me1400GetBoardVersion(int iBoardNumber, int *piVersion);
extern "C" int _declspec(dllimport) _cdecl me1400GetDrvErrMess(char *pcErrortext);

// INT functions (external interrupt functions)
extern "C" int _declspec(dllimport) _cdecl me1400EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc, int iServiceNo);
extern "C" int _declspec(dllimport) _cdecl me1400DisableInt(int iBoardNumber, int iServiceNo);
extern "C" int _declspec(dllimport) _cdecl me1400GetIrqCnt(int iBoardNumber, int *ipIrqCnt);

// CNT functions (counter functions)
extern "C" int _declspec(dllimport) _cdecl me1400CntInitSrc(int iBoardNumber, int iCounter, int iCounterSource);
extern "C" int _declspec(dllimport) _cdecl me1400CntWrite(int iBoardNumber, int iCounter, int iMode, int iValue);
extern "C" int _declspec(dllimport) _cdecl me1400CntRead(int iBoardNumber, int iCounter, int* piValue);

/*==============================================================*/
// PWM functions (pulse width modulation)
extern "C" int _declspec(dllimport) _cdecl me1400CntPWMStart(int iBoardNumber, int iDeviceNumber, int iClockSource, int iPrescaler, int iDutyCycle);
extern "C" int _declspec(dllimport) _cdecl me1400CntPWMStop(int iBoardNumber, int iDeviceNumber);
/*==============================================================*/

// DIO functions (digital input output)
extern "C" int _declspec(dllimport) _cdecl me1400DIOSetPortDirection(int iBoardNumber, int iPort, int iDir);
extern "C" int _declspec(dllimport) _cdecl me1400DIGetBit(int iBoardNumber, int iPort,int iBitNo, int *piValue);
extern "C" int _declspec(dllimport) _cdecl me1400DIGetByte(int iBoardNumber, int iPortNo, int *piValue);
extern "C" int _declspec(dllimport) _cdecl me1400DOSetBit(int iBoardNumber,int iPort, int iBitNo, int iBitValue);
extern "C" int _declspec(dllimport) _cdecl me1400DOSetByte(int iBoardNumber, int iPortNo, int iValue);

//------------------------------------------------------------------------------------------------------------------
// general function, for internal use only (unsupported)
extern "C" int _declspec(dllimport) _cdecl me1400GetSerialNumber(int iBoardNumber, int *piSerialNumber);
extern "C" int _declspec(dllimport) _cdecl me1400GetDevInfo(int iBoardNumber, PDEVICEINFOSTRUCT pDevInfo);
extern "C" int _declspec(dllimport) _cdecl me1400InportByte(int iBoardNumber, int iPortOffset, int* pbValue);
extern "C" int _declspec(dllimport) _cdecl me1400OutportByte(int iBoardNumber, int iPortOffset, int bValue);
extern "C" int _declspec(dllimport) _cdecl me1400InportWord(int iBoardNumber, int iPortOffset, int* pwValue);
extern "C" int _declspec(dllimport) _cdecl me1400OutportWord(int iBoardNumber, int iPortOffset, int wValue);
extern "C" int _declspec(dllimport) _cdecl me1400InportDWord(int iBoardNumber, int iPortOffset, int* pwValue);
extern "C" int _declspec(dllimport) _cdecl me1400OutportDWord(int iBoardNumber, int iPortOffset, int wValue);
extern "C" int _declspec(dllimport) _cdecl me1400ResetBoard(int iBoardNumber);
extern "C" int _declspec(dllimport) _cdecl me1400InitBoard(int iBoardNumber);

// obsolete functions for older board versions, do NOT use them in new projects !!
extern "C" int _declspec(dllimport) _cdecl me1400WriteUserString(int iBoardNumber, char* pcUserText);
extern "C" int _declspec(dllimport) _cdecl me1400ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength);
extern "C" int _declspec(dllimport) _cdecl me1400InitModeTimerA(int iBoardNumber, int CtrlWordA);
extern "C" int _declspec(dllimport) _cdecl me1400InitModeTimerB(int iBoardNumber, int CtrlWordB);
extern "C" int _declspec(dllimport) _cdecl me1400SetMultifunctionPin(int iBoardNumber, int MultiPin);
extern "C" int _declspec(dllimport) _cdecl me1400DIOSetMode(int iBoardNumber,int iPio, int iMode);

#endif