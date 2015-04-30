// File Name 'me630.h'
// Header File for me630.dll


#ifndef ME630_H
#define ME630_H

#include "MEdefs.h"

// Supports ME-630, ME-63

/* IMPORTANT NOTE :
		only for use with Microsoft Visual C++ V4.0 or later
		for other compilers you must change the macro
		"_declspec(dllimport)" into the form your compiler needs to
		import functions from an external dll !
*/

// ME630 Routines


// General Routines
extern "C" _declspec(dllimport) int _cdecl _me630GetDLLVersion();
extern "C" _declspec(dllimport) int _cdecl _me630GetBoardVersion(int iBoardNumber, int *piVersion);
extern "C" _declspec(dllimport) int _cdecl _me630ResetRelays(int iBoardNumber);
extern "C" _declspec(dllimport) int _cdecl _me630EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext);
extern "C" _declspec(dllimport) int _cdecl _me630DisableInt(int iBoardNumber, int iIRQNum);
extern "C" _declspec(dllimport) int _cdecl _me630GetDrvErrMess(char *pcErrortext, int iBufferSize);

// Digital I/O Input-Functions
extern "C" _declspec(dllimport) int _cdecl _me630DIGetTTLBit(int iBoardNumber, int iBitNo, int *piBitValue);
extern "C" _declspec(dllimport) int _cdecl _me630DIGetTTLByte(int iBoardNumber, unsigned char *pcValue);
extern "C" _declspec(dllimport) int _cdecl _me630DIGetOptoBit(int iBoardNumber, int iBitNo, int *piBitValue);
extern "C" _declspec(dllimport) int _cdecl _me630DIGetOptoByte(int iBoardNumber, unsigned char *pcValue);

// Digital I/O Output-Functions
extern "C" _declspec(dllimport) int _cdecl _me630DOSetRelayBit(int iBoardNumber, int iBitNo, int iBitValue);
extern "C" _declspec(dllimport) int _cdecl _me630DOSetRelayWord(int iBoardNumber, unsigned short usValue);
extern "C" _declspec(dllimport) int _cdecl _me630DIGetRelayBit(int iBoardNumber, int iBitNo, int *piBitValue);
extern "C" _declspec(dllimport) int _cdecl _me630DIGetRelayWord(int iBoardNumber, unsigned short *pusValue);

// Neue Digital I/O Output-Functions

extern "C" _declspec(dllimport) int _cdecl _me630DIOResetAll(int iBoardNumber);
extern "C" _declspec(dllimport) int _cdecl _me630DIOConfig(int iBoardNumber, int iPortNumber, int iPortDirection);
extern "C" _declspec(dllimport) int _cdecl _me630DIOGetBit(int iBoardNumber, int iPortNumber, int iBitNo, int* piBitValue);
extern "C" _declspec(dllimport) int _cdecl _me630DIOGetByte(int iBoardNumber, int iPortNumber, unsigned char* pucByteValue);
extern "C" _declspec(dllimport) int _cdecl _me630DIOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iBitValue);
extern "C" _declspec(dllimport) int _cdecl _me630DIOSetByte(int iBoardNumber, int iPortNumber, unsigned char ucByteValue);

// New Routines
extern "C" _declspec(dllimport) int _cdecl _me630GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt);
extern "C" _declspec(dllimport) int _cdecl _me630GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
extern "C" _declspec(dllimport) int _cdecl _me630WriteUserString(int iBoardNumber, char* pcUserText);
extern "C" _declspec(dllimport) int _cdecl _me630ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength);

// ME63 Routines for compatability with earlier versions
extern "C" _declspec(dllimport) int _cdecl _me63Reset(int iBoardNumber);

// Digital I/O Input-Functions
extern "C" _declspec(dllimport) int _cdecl _me63DIGetBit(int iBoardNumber, int iBitNo, int *piValue);
extern "C" _declspec(dllimport) int _cdecl _me63DIGetByte(int iBoardNumber, int* iValue);
extern "C" _declspec(dllimport) int _cdecl _me63DOSetBit(int iBoardNumber, int iBitNo, int iBitValue);
extern "C" _declspec(dllimport) int _cdecl _me63DOSetWord(int iBoardNumber, int iValue);

#endif // #ifndef ME630_H
