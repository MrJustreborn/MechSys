
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

int mePROMVersion(int iBoardNumber, int *piVersion);
int meDIGetIntStatus(int iBoardNumber, int iRegisterSet, int *piValue);
int meDIOSetIntMode(int iBoardNumber, int iRegisterSet, int iMode);
int meDIOSetTristateON(int iBoardNumber, int iRegisterSet);
int meDIOSetTristateOFF(int iBoardNumber, int iRegisterSet);
int meDIOSetPattern(int iBoardNumber, int iRegisterSet, int iPattern);
int meDIOSetMask(int iBoardNumber, int iRegisterSet, int iMask);
int meDIGetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int *piBitValue);
int meDIGetWord(int iBoardNumber, int iRegisterSet, int *piValue);
int meDOSetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int iBitValue);
int meDOSetWord(int iBoardNumber, int iRegisterSet, int iValue);
int meCntWrite(int iBoardNumber, int iCounter, int iMode, int iValue);
int meCntRead(int iBoardNumber, int iCounter, int* piValue);
int meSetSinkSourceMode(int iBoardNumber, int iRegisterSet, int iMode);

#endif // DLL_H
