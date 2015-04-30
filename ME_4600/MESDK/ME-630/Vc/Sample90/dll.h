
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

int meResetRelays(int iBoardNumber);
int meDIGetTTLBit(int iBoardNumber, int iBitNo, int *piBitValue);
int meDIGetTTLByte(int iBoardNumber, unsigned char *pcValue);
int meDIGetOptoBit(int iBoardNumber, int iBitNo, int *piBitValue);
int meDIGetOptoByte(int iBoardNumber, unsigned char *pcValue);
int meDOSetRelayBit(int iBoardNumber, int iBitNo, int iBitValue);
int meDOSetRelayWord(int iBoardNumber, unsigned short usValue);
int meDIGetRelayBit(int iBoardNumber, int iBitNo, int *piBitValue);
int meDIGetRelayWord(int iBoardNumber, unsigned short *pusValue);

int meDIOResetAll(int iBoardNumber);
int meDIOConfig(int iBoardNumber, int iPortNumber, int iPortDirection);
int meDIOGetBit(int iBoardNumber, int iPortNumber, int iBitNo, int* piBitValue);
int meDIOGetByte(int iBoardNumber, int iPortNumber, unsigned char* pucByteValue);
int meDIOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iBitValue);
int meDIOSetByte(int iBoardNumber, int iPortNumber, unsigned char ucByteValue);

#endif // DLL_H
