// File Name 'ME6x00.h'
// Header File for me6x00.dll
// using with the me6x00.lib file

#ifndef ME6x00_H
#define ME6x00_H

#include "meDefs.h"

// Supports ME-6x00

/* IMPORTANT NOTE :
		only for use with Microsoft Visual C++ V4.0 or later
		for other compilers you must change the macro
		"_declspec(dllimport)" into the form your compiler needs to
		import functions from an external dll !
*/

// General Routines
extern "C" int _declspec(dllimport) _cdecl me6x00FrequencyToTimer(double dFreq);

extern "C" int _declspec(dllimport) _cdecl me6x00GetBoardVersion( int iBoardNumber,
                                                                  int *piVersion);

extern "C" int _declspec(dllimport) _cdecl me6x00GetDevInfo(      int iBoardNumber,
                                                                  DEVICEINFOSTRUCT* pDevInfo);

extern "C" int _declspec(dllimport) _cdecl me6x00GetDLLVersion();

extern "C" int _declspec(dllimport) _cdecl me6x00GetDriverVersion(char *pBuffer);

extern "C" int _declspec(dllimport) _cdecl me6x00GetSerialNumber( int iBoardNumber,
                                                                  int *piSerialNumber);

// ME6x00 Routines
extern "C" int _declspec(dllimport) _cdecl me6x00AOContinuous(    int iBoardNumber,
                                                                  int iChannel,
                                                                  int iSize,
                                                                  short *psBuffer);

extern "C" int _declspec(dllimport) _cdecl me6x00AOContinuousEx(  int iBoardNumber,
                                                                  int iChannel,
                                                                  int iSize,
                                                                  short *psBuffer,
                                                                  int iLoops,
                                                                  PVOID_PROC pCallback,
                                                                  void* pArgs);

extern "C" int _declspec(dllimport) _cdecl me6x00AOReset(         int iBoardNumber,
                                                                  int iChannel);

extern "C" int _declspec(dllimport) _cdecl me6x00AOResetAll(      int iBoardNumber);

extern "C" int _declspec(dllimport) _cdecl me6x00AOSetTimer(      int iBoardNumber,
                                                                  int iChannel,
                                                                  int iTicks);

extern "C" int _declspec(dllimport) _cdecl me6x00AOSetTrigger(    int iBoardNumber,
                                                                  int iChannel,
                                                                  int iModePolarity);

extern "C" int _declspec(dllimport) _cdecl me6x00AOSingle(        int iBoardNumber,
                                                                  int iChannel,
                                                                  int iValue);

extern "C" int _declspec(dllimport) _cdecl me6x00AOStart(         int iBoardNumber,
                                                                  int iChannel);

extern "C" int _declspec(dllimport) _cdecl me6x00AOStart4(        int iBoardNumber);

extern "C" int _declspec(dllimport) _cdecl me6x00AOStop(          int iBoardNumber,
                                                                  int iChannel);

extern "C" int _declspec(dllimport) _cdecl me6x00AOStopEx(        int iBoardNumber,
                                                                  int iChannel);

extern "C" int _declspec(dllimport) _cdecl me6x00AOWaveGen(       int iBoardNumber,
                                                                  int iChannel,
                                                                  int iShape,
                                                                  double dAmplitude,
                                                                  double dOffset,
                                                                  double dFreq);

extern "C" int _declspec(dllimport) _cdecl me6x00AOWrapAround(    int iBoardNumber,
                                                                  int iChannel,
                                                                  int iSize,
                                                                  short *psBuffer);

// Error Handling
extern "C" int _declspec(dllimport) _cdecl me6x00GetDrvErrMess(   char *pcErrortext,
                                                                  int iBufferSize);

#endif // #ifndef ME6x00_H

