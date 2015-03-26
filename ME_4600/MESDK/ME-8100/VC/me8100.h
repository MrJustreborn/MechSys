// File Name 'me8100.h'
// Header File for me8100.dll
// using with the me8100.lib file


#ifndef ME8100_H
#define ME8100_H

#include "meDefs.h"

// Supports ME-8100, ME-8X

/* IMPORTANT NOTE :
		only for use with Microsoft Visual C++ V4.0 or later
		for other compilers you must change the macro
		"_declspec(dllimport)" into the form your compiler needs to
		import functions from an external dll !
*/

// ME8100 Routines

// General Routines

extern "C" int _declspec(dllimport) _cdecl me8100GetDLLVersion();
extern "C" int _declspec(dllimport) _cdecl me8100GetBoardVersion(int iBoardNumber, int *piVersion);
extern "C" int _declspec(dllimport) _cdecl me8100PROMVersion(int iBoardNumber, int *piVersion);
extern "C" int _declspec(dllimport) _cdecl me8100EnableInt(int iBoardNumber, int iRegisterSet, 
																		ME_PSERVICE_PROC IrqFunc, int iContext);

extern "C" int _declspec(dllimport) _cdecl me8100DisableInt(int iBoardNumber, int iRegisterSet);

// Error Handling

extern "C" int _declspec(dllimport) _cdecl me8100GetDrvErrMess(char *pcErrortext, int iBufferSize);

// Digital I/O General Functions

extern "C" int _declspec(dllimport) _cdecl me8100DIGetIntStatus(int iBoardNumber, int iRegisterSet, int *piValue);
extern "C" int _declspec(dllimport) _cdecl me8100DIOSetIntMode(int iBoardNumber, int iRegisterSet, int iMode);
extern "C" int _declspec(dllimport) _cdecl me8100DIOSetTristateON(int iBoardNumber, int iRegisterSet);
extern "C" int _declspec(dllimport) _cdecl me8100DIOSetTristateOFF(int iBoardNumber, int iRegisterSet);
extern "C" int _declspec(dllimport) _cdecl me8100DIOSetPattern(int iBoardNumber, int iRegisterSet, int iPattern);
extern "C" int _declspec(dllimport) _cdecl me8100DIOSetMask(int iBoardNumber, int iRegisterSet, int iMask);

// Digital I/O Input-Functions

extern "C" int _declspec(dllimport) _cdecl me8100DIGetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int *piBitValue);
extern "C" int _declspec(dllimport) _cdecl me8100DIGetWord(int iBoardNumber, int iRegisterSet, int *piValue);

// Digital I/O Output-Functions

extern "C" int _declspec(dllimport) _cdecl me8100DOSetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int iBitValue);
extern "C" int _declspec(dllimport) _cdecl me8100DOSetWord(int iBoardNumber, int iRegisterSet, int iValue);

// New Routines
extern "C" int _declspec(dllimport) _cdecl me8100GetIrqCnt(int iBoardNumber, int iRegisterSet, int* piCnt);
extern "C" int _declspec(dllimport) _cdecl me8100GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
extern "C" int _declspec(dllimport) _cdecl me8100WriteUserString(int iBoardNumber, char* pcUserText);
extern "C" int _declspec(dllimport) _cdecl me8100ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength);

// Counter 8254 functions
extern "C" int _declspec(dllimport) _cdecl me8100CntWrite(int iBoardNumber, int iCounter, int iMode, int iValue);
extern "C" int _declspec(dllimport) _cdecl me8100CntRead(int iBoardNumber, int iCounter, int* piValue);

// Sink/Source

extern "C" int _declspec(dllimport) _cdecl me8100SetSinkSourceMode(int iBoardNumber, int iRegisterSet, int imode);

// ME8X Routines for compatability with earlier versions

// General Routines
extern "C" int _declspec(dllimport) _cdecl _me8xGetDLLVersion();
extern "C" int _declspec(dllimport) _cdecl _me8xPROMVersion(int iBoardNumber, int *piVersion);
extern "C" int _declspec(dllimport) _cdecl _me8xEnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc);
extern "C" int _declspec(dllimport) _cdecl _me8xDisableInt(int iBoardNumber);

// Error Handling
extern "C" int _declspec(dllimport) _cdecl _me8xGetDrvErrMess(char *pcErrortext);

// Digital I/O General Functions
extern "C" int _declspec(dllimport) _cdecl _me81DIGetIntStatus(int iBoardNumber, int *piValue);
extern "C" int _declspec(dllimport) _cdecl _me8xDIOSetIntMode(int iBoardNumber, int iMode);
extern "C" int _declspec(dllimport) _cdecl _me80DIOSetMode(int iBoardNumber, int iMode, int iRegMode);
extern "C" int _declspec(dllimport) _cdecl _me8xDIOSetTristateON(int iBoardNumber);
extern "C" int _declspec(dllimport) _cdecl _me8xDIOSetTristateOFF(int iBoardNumber);
extern "C" int _declspec(dllimport) _cdecl _me8xDIOSetPattern(int iBoardNumber, int iPattern);
extern "C" int _declspec(dllimport) _cdecl _me81DIOSetMask(int iBoardNumber, int iMask);

// Digital I/O Input-Functions
extern "C" int _declspec(dllimport) _cdecl _me8xDIGetBit(int iBoardNumber, int iBitNo, int *piBitValue);
extern "C" int _declspec(dllimport) _cdecl _me8xDIGetWord(int iBoardNumber, int iPortNo, int *piValue);

// Digital I/O Output-Functions
extern "C" int _declspec(dllimport) _cdecl _me8xDOSetBit(int iBoardNumber, int iBitNo, int iBitValue);
extern "C" int _declspec(dllimport) _cdecl _me8xDOSetWord(int iBoardNumber, int iPortNo, int iValue);

// New Routines
extern "C" int _declspec(dllimport) _cdecl _me81GetIRQCount(int iBoardNumber, int iType, int* piCnt);
extern "C" int _declspec(dllimport) _cdecl _me81GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
extern "C" int _declspec(dllimport) _cdecl _me81WriteUserString(int iBoardNumber, char* pcUserText);

#endif // #ifndef ME8100_H
