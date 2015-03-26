
#ifndef DLL_H
#define DLL_H

#include ".\..\meDefs.h"     // User defines for the board concerned.

int meGetDLLVersion();
int meGetDriverVersion(int *piDriverVersion);
int meGetBoardVersion(int iBoardNumber, int *piBoardVersion);
int meGetSerialNumber(int iBoardNumber, int *piSerialNumber);
int meGetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt);
int meGetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
int meWriteUserString(int iBoardNumber, char* pcUserText);
int meReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength);
int meInportByte(int iBoardNumber, int iPortOffset, int* pbValue);
int meOutportByte(int iBoardNumber, int iPortOffset, int bValue);
int meInportWord(int iBoardNumber, int iPortOffset, int* pwValue);
int meOutportWord(int iBoardNumber, int iPortOffset, int wValue);
int meInportDWord(int iBoardNumber, int iPortOffset, int* pwValue);
int meOutportDWord(int iBoardNumber, int iPortOffset, int wValue);
int meResetBoard(int iBoardNumber);
int meInitBoard(int iBoardNumber);
int meGetDrvErrMess(char *pcErrortext, int iBufferSize);

int meFrequencyToTimer(double dFreq);
int meAOContinuous(int iBoardNumber, int iChannel, int iSize, short *psBuffer);
int meAOContinuousEx(int iBoardNumber, int iChannel, int iSize, short *psBuffer,
                     int iLoops, PVOID_PROC pCallback, VOID* pArgs);
int meAOReset(int iBoardNumber, int iChannel);
int meAOResetAll(int iBoardNumber);
int meAOSetTimer(int iBoardNumber, int iChannel, int iTicks);
int meAOSetTrigger(int iBoardNumber, int iChannel, int iModePolarity);
int meAOSingle( int iBoardNumber, int iChannel, int iValue);
int meAOStart(int iBoardNumber, int iChannel);
int meAOStop(int iBoardNumber, int iChannel);
int meAOStopEx(int iBoardNumber, int iChannel);
int meAOWaveGen(int iBoardNumber, int iChannel, int iShape, double dAmplitude,
                double dOffset, double dFreq);
int meAOWrapAround(int iBoardNumber, int iChannel, int iSize, short *psBuffer);

#endif // DLL_H
