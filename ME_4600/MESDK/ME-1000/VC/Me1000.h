// File Name 'me1000.h'
// Header File for me1000.dll

// IMPORTANT NOTE :
// Only for use with Microsoft Visual C++ V4.0 or later. For other 
// compilers you have to change the macro "_declspec(dllimport)" into 
// the form your compiler needs to import functions from an external dll !

#ifndef ME1000_H
#define ME1000_H

#include "meDefs.h"


// General Routines
extern "C" int _declspec(dllimport) _cdecl me1000GetDLLVersion();
extern "C" int _declspec(dllimport) _cdecl me1000GetDriverVersion(int *piDriverVersion);
extern "C" int _declspec(dllimport) _cdecl me1000GetBoardVersion(int iBoardNumber, int *piVersion);
extern "C" int _declspec(dllimport) _cdecl me1000GetSerialNumber(int iBoardNumber, int *piSerialNumber);
extern "C" int _declspec(dllimport) _cdecl me1000GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
extern "C" int _declspec(dllimport) _cdecl me1000GetDrvErrMess(char *pcErrortext, int iBufferSize);

// general function, for internal use only (unsupported)
extern "C" int _declspec(dllimport) _cdecl me1000WriteUserString(int iBoardNumber, char* pcUserText);
extern "C" int _declspec(dllimport) _cdecl me1000ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength);
extern "C" int _declspec(dllimport) _cdecl me1000InportByte(int iBoardNumber, int iPortOffset, int* pbValue);
extern "C" int _declspec(dllimport) _cdecl me1000OutportByte(int iBoardNumber, int iPortOffset, int bValue);
extern "C" int _declspec(dllimport) _cdecl me1000InportWord(int iBoardNumber, int iPortOffset, int* pwValue);
extern "C" int _declspec(dllimport) _cdecl me1000OutportWord(int iBoardNumber, int iPortOffset, int wValue);
extern "C" int _declspec(dllimport) _cdecl me1000InportDWord(int iBoardNumber, int iPortOffset, int* pwValue);
extern "C" int _declspec(dllimport) _cdecl me1000OutportDWord(int iBoardNumber, int iPortOffset, int wValue);
extern "C" int _declspec(dllimport) _cdecl me1000ResetBoard(int iBoardNumber);
extern "C" int _declspec(dllimport) _cdecl me1000InitBoard(int iBoardNumber);

// Digital I/O Functions
extern "C" int _declspec(dllimport) _cdecl me1000DIOSetPortDirection(int iBoardNumber, int iPortNumber, int iDirection);
extern "C" int _declspec(dllimport) _cdecl me1000DIOReset(int iBoardNumber);

extern "C" int _declspec(dllimport) _cdecl me1000DIGetBit (int iBoardNumber, int iPortNumber, int iBitNo, int *piValue);
extern "C" int _declspec(dllimport) _cdecl me1000DIGetByte(int iBoardNumber, int iPortNumber, int iByteNo, int *piValue);
extern "C" int _declspec(dllimport) _cdecl me1000DIGetWord(int iBoardNumber, int iPortNumber, int iWordNo, int *piValue);
extern "C" int _declspec(dllimport) _cdecl me1000DIGetLong(int iBoardNumber, int iPortNumber, int *piValue);

extern "C" int _declspec(dllimport) _cdecl me1000DOSetBit (int iBoardNumber, int iPortNumber, int iBitNo,  int iValue);
extern "C" int _declspec(dllimport) _cdecl me1000DOSetByte(int iBoardNumber, int iPortNumber, int iByteNo, int iValue);
extern "C" int _declspec(dllimport) _cdecl me1000DOSetWord(int iBoardNumber, int iPortNumber, int iWordNo, int iValue);
extern "C" int _declspec(dllimport) _cdecl me1000DOSetLong(int iBoardNumber, int iPortNumber, int iValue);

#endif // #ifndef ME1000_H
