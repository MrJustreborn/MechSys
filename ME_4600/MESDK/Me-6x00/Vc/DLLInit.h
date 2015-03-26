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
-----------------------------------------=-----------------------------------*/


#ifndef DLLINIT_H
#define DLLINIT_H

#define SUCCESS             0x01
#define DLLNOTFOUND         0x02
#define FUNCTIONNOTFOUND    0x03
#define DLLNAME             "me6x00.dll"
#define DLLDEBUGNAME        "me6x00d.dll"




typedef int(__cdecl *PF_ME6x00FREQUENCYTOTIMER)(double dFreq);
typedef int(__cdecl *PF_ME6x00GETBOARDVERSION)(int iBoardNumber, int *piVersion);
typedef int(__cdecl *PF_ME6x00GETDEVINFO)(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
typedef int(__cdecl *PF_ME6x00GETDLLVERSION)(void);
typedef int(__cdecl *PF_ME6x00GETDRIVERVERSION)(int *piDriverVersion);
typedef int(__cdecl *PF_ME6x00GETSERIALNUMBER)(int iBoardNumber, int *piSerialNumber);
typedef int(__cdecl *PF_ME6x00AOCONTINUOUS)(int iBoardNumber, int iChannel,int iSize, short *psBuffer);
typedef int(__cdecl *PF_ME6x00AOCONTINUOUSEX)(int iBoardNumber, int iChannel, int iSize, short *psBuffer,
                                              int iLoops, PVOID_PROC pCallback, void* pArgs);
typedef int(__cdecl *PF_ME6x00AORESET)(int iBoardNumber, int iChannel);
typedef int(__cdecl *PF_ME6x00AORESETALL)(int iBoardNumber);
typedef int(__cdecl *PF_ME6x00AOSETTIMER)(int iBoardNumber, int iChannel, int iTicks);
typedef int(__cdecl *PF_ME6x00AOSETTRIGGER)(int iBoardNumber, int iChannel, int iModePolarity);
typedef int(__cdecl *PF_ME6x00AOSINGLE)(int iBoardNumber, int iChannel, int iValue);
typedef int(__cdecl *PF_ME6x00AOSTART)(int iBoardNumber, int iChannel);
typedef int(__cdecl *PF_ME6x00AOSTART4)(int iBoardNumber);
typedef int(__cdecl *PF_ME6x00AOSTOP)(int iBoardNumber, int iChannel);
typedef int(__cdecl *PF_ME6x00AOSTOPEX)(int iBoardNumber, int iChannel);
typedef int(__cdecl *PF_ME6x00AOWAVEGEN)(int iBoardNumber, int iChannel, int iShape, double dAmplitude, 
                                         double dOffset, double dFreq);
typedef int(__cdecl *PF_ME6x00AOWRAPAROUND)(int iBoardNumber, int iChannel, int iSize, short *psBuffer);
typedef int(__cdecl *PF_ME6x00GETDRVERRMESS)(char *pcErrortext, int iBufferSize);

#include "meDefs.h"


// -------------------- Function Prototypes --------------------------------
void meOpen (void);                   // initialize function
void meClose (void);                  // shut down function

int me6x00FrequencyToTimer(double dFreq);
int me6x00GetBoardVersion(int iBoardNumber, int *piVersion);
int me6x00GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
int me6x00GetDLLVersion(void);
int me6x00GetDriverVersion(int *piDriverVersion);
int me6x00GetSerialNumber(int iBoardNumber, int *piSerialNumber);
int me6x00AOContinuous(int iBoardNumber, int iChannel, int iSize, short *psBuffer);
int me6x00AOContinuousEx(int iBoardNumber, int iChannel, int iSize, short *psBuffer,
                         int iLoops, PVOID_PROC pCallback, void* pArgs);
int me6x00AOReset(int iBoardNumber, int iChannel);
int me6x00AOResetAll(int iBoardNumber);
int me6x00AOSetTimer(int iBoardNumber, int iChannel, int iTicks);
int me6x00AOSetTrigger(int iBoardNumber, int iChannel, int iModePolarity);
int me6x00AOSingle( int iBoardNumber, int iChannel, int iValue);
int me6x00AOStart(int iBoardNumber, int iChannel);
int me6x00AOStart4(int iBoardNumber);
int me6x00AOStop(int iBoardNumber, int iChannel);
int me6x00AOStopEx(int iBoardNumber, int iChannel);
int me6x00AOWaveGen(int iBoardNumber, int iChannel, int iShape, double dAmplitude,
                    double dOffset, double dFreq);
int me6x00AOWrapAround(int iBoardNumber, int iChannel, int iSize, short *psBuffer);
int me6x00GetDrvErrMess(char *pcErrortext, int iBufferSize);

#endif