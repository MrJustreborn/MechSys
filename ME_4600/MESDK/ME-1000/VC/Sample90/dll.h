
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
int meEnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext);
int meDisableInt(int iBoardNumber, int iIRQNum);
int meGetDrvErrMess(char *pcErrortext, int iBufferSize);

int meDIOSetPortDirection(int iBoardNumber, int iPortNumber, int iDirection);
int meDIOReset(int iBoardNumber);
int meDIGetBit(int iBoardNumber, int iPortNumber,  int iBitNo, int *piValue);
int meDIGetByte(int iBoardNumber, int iPortNumber, int iByteNo, int *piValue);
int meDIGetWord(int iBoardNumber, int iPortNumber, int iWordNo, int *piValue);
int meDIGetLong(int iBoardNumber, int iPortNumber, int *piValue);
int meDOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iValue);
int meDOSetByte(int iBoardNumber, int iPortNumber, int iByteNo, int iValue);
int meDOSetWord(int iBoardNumber, int iPortNumber, int iWordNo, int iValue);
int meDOSetLong(int iBoardNumber, int iPortNumber, int iValue);

#endif // DLL_H
