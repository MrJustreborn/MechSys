
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
int meEnableInt(int iBoardNumber, int iIRQNum, PSERVICE_PROC IrqFunc, int iContext);
int meDisableInt(int iBoardNumber, int iIRQNum);
int meGetDrvErrMess(char *pcErrortext, int iBufferSize);

int meCntInitSrc(int iBoardNumber, int iCounter, int iCounterSource);
int meCntWrite(int iBoardNumber, int iCounter, int iMode, int iValue);
int meCntRead(int iBoardNumber, int iCounter, int* piValue);
int meDIOSetMode(int iBoardNumber, int iPio, int iMode);
int meDIOSetPortDirection(int iBoardNumber, int iPort, int iDir);
int meDIGetBit(int iBoardNumber, int iPort, int iBitNo, int *piValue);
int meDOSetBit(int iBoardNumber, int iPort, int iBitNo, int iBitValue);
int meDIGetByte(int iBoardNumber, int iPortNo, int *piValue);
int meDOSetByte(int iBoardNumber, int iPortNo, int iValue);
int meInitModeTimerA(int iBoardNumber, int iCtrlWordA);
int meInitModeTimerB(int iBoardNumber, int iCtrlWordB);
int meSetMultifunctionPin(int iBoardNumber, int MultiPin);

#endif // DLL_H
