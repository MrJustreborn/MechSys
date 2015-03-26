
#ifndef DLL_H
#define DLL_H

#include ".\..\meDefs.h"     // User defines for the board concerned.
#include ".\Common.h"


// Error handling
int meGetDrvErrMess(char *pcErrorText, int iBufferSize);
int meErrorMessage(char *pcWindowTitle);

// General functions
int meGeneralReset(int iBoardNumber);
int meGetInterrupts(int iBoardNumber, PME_BOARD_ISR pInt);
int meGetBoardInfo(int iBoardNumber, PME_BOARD_INFO pBoardInfo);
int meDLLBoardInfo(int iBoardNumber, PME_BOARD_INFO pBoardInfo);
int meGetDLLVersion(void);
int meGetDLLTimeStamp(char *pcBuffer, int iBufferSize);
int meGetDriverVersion(char *pcBuffer, int iBufferSize);
int meGetDriverTimeStamp(char *pcBuffer, int iBufferSize);
int meGetPCIConfiguration(int iBoardNumber, PME_PLX9050_INFO pBoardData);
int meGetVECModel(int iBoardNumber, int *piMEVECModel);
int meGetSerialNumber(int iBoardNumber, int *piSerialNumber);
int meGetDriverStatus(int iBoardNumber, PME_DRIVER_STATUS pStatus);
int meInitialize(int iBoardNumber);

// Digital I/O functions
int meDIOSetPortDirection(int iBoardNumber, int iPortNo, int iDir);
int meDIGetBit(int iBoardNumber, int iPortNo, int iBitNo, int *piBitValue);
int meDIGetByte(int iBoardNumber, int iPortNo, int iByteNo, int *piByteValue);
int meDIGetWord(int iBoardNumber, int iPortNo, int *piValue);

int meDOSetBit(int iBoardNumber, int iPortNo, int iBitNo, int iBitValue);
int meDOSetByte(int iBoardNumber, int iPortNo, int iByteNo, int iByteValue);
int meDOSetWord(int iBoardNumber, int iPortNo, int iValue);
int meDOReset(int iBoardNumber, int iPortNo);

// Thread priority function
int meSetPriority(int iBoardNumber, int iPriority);

// Analog input functions
int meAIClearChannelList(int iBoardNumber);
int meAIAddToChannelList(int iBoardNumber, int iEntry);
int meFileName(int iBoardNumber, int iType, char *pcFileName);
int meFrequencyToCounter(double dFreq);
int meAISetTimer(int iBoardNumber, int iScan, int iChan);
int meAISetTrigger(int iBoardNumber, int iModePolarity);
int meAIMakeChannelListEntry(int iChannel, int iRange, int iMode, int *piEntry);
int meAISetSimultaneous(int iBoardNumber, int iMode);
int meAIStop(int iBoardNumber);
int meAISingle(int iBoardNumber, int iChannel, int iMode, short *psValue);
int meAISingleEx(int iBoardNumber, int iChannel, int iRange,
                int iLoops, int iDelay, short *psValue, PSHORT_PROC pCallback);
int meAIMultiple(int iBoardNumber, short *psBuffer, int iCount, int iMode);
int meAIMultipleEx(int iBoardNumber, short *psBuffer, int iCount,
                        int iMode, int iLoops, int iDelay, P_1_PROC pCallback);
int meAIQuick(int iBoardNumber, short *psBuffer, int iCount, int iMode);
int meAIQuickEx(int iBoardNumber, short *psBuffer, int iCount,
                        int iMode, int iLoops, int iDelay, P_1_PROC pCallback);
int meAIScan(int iBoardNumber, short *psBuffer, int iSize,
                                                        int iCount, int iMode);
int meAIScanEx(int iBoardNumber, short *psBuffer, int iSize, int iCount,
                        int iMode, int iLoops, int iDelay, P_1_PROC pCallback);
int meAIContinuous(int iBoardNumber, int iFrameSize, int iBufferSize, P_1_PROC pCallback);
int meAIClearDataFIFO(int iBoardNumber);
int meAIReadFIFO(int iBoardNumber, short *psBuffer, int iCount);
int meAIStartByExternalTrigger(int iBoardNumber, int iModePolarity);

// Analog output functions
int meAOReset(int iBoardNumber);
int meAOSetMode(int iBoardNumber, int iChannel, int iRange, int iMode);
int meAOSingle(int iBoardNumber, int iChannel, short sValue);
int meAOUpdate(int iBoardNumber);
int meAOSetTimer(int iBoardNumber, int iTime);
int meAOSetTrigger(int iBoardNumber, int iModePolarity);
int meAOClearDACFIFO(int iBoardNumber);
int meAOAddToDACFIFO(int iBoardNumber, int iEntry);
int meAOWrapAround(int iBoardNumber);
int meAOStop(int iBoardNumber);
int meAOContinuous(int iBoardNumber, int iMode, int iSize, short *psBuffer);
int meAOStopEx(int iBoardNumber);

int meAOContinuousEx(int iBoardNumber, int iMode, int iSize, short *psBuffer,
                                  int iLoops, int iDelay, PVOID_PROC pCallback);

// PWM functions
int mePWMSetMode(int iBoardNumber, double dFrequency,
                                                int iDutyCycle, int iInverted);

int mePWMStart(int iBoardNumber);
int mePWMStop(int iBoardNumber);

// SIO functions
int meSIOGetRegisters(int iBoardNumber, PME_BOARD_SIO_REGS pSIORegs);
int meSIOLoopBackTest(int iBoardNumber);
int meSIOSetup(int iBoardNumber, int iBaud, int iLen, int iStop, char cParity);
int meSIOWriteRegister(int iBoardNumber, char cReg, char cVal);
int meSIOReadRegister(int iBoardNumber, char cReg);
int meSIOTransmit(int iBoardNumber, int iMode, int iCount, char *pcBuffer);
int meSIOReceive(int iBoardNumber, int iMode, int iCount, char *pcBuffer);

int meSIOOpen(int iBoardNumber, int iMode,
                                        int iInBufferSize, int iOutBufferSize);

int meSIOClose(int iBoardNumber);
int meSIOClearBuffer(int iBoardNumber);
int meSIOCheckBuffer(int iBoardNumber, PME_BOARD_SIO pSio);
int meSIOCheckError(int iBoardNumber);

// External interrupt functions
int meEnableExternalInt(int iBoardNumber, PVOID_PROC pCallback);
int meDisableExternalInt(int iBoardNumber);

// Counter functions
int meCNTStart(int iBoardNumber, int iCounter);
int meCNTRead(int iBoardNumber, int iCounter, short *psCounterValue);

int meCNTInterrupt(int iBoardNumber, int iCounter,
                                            int iFlag, PVOID_PROC pCallback);
int meCNTReset(int iBoardNumber, int iCounter);

int meCNTSetRange(int iBoardNumber, int iCounter,
                                                int iEndValue, int iStartValue);

// New functions

int meLoadFirmware(int iBoardNumber, char* pcLicenceNumber);

int meAIContinuous(int iBoardNumber, int iFrameSize, int iBufferSize, P_1_PROC pCallback);

int meAOGenerateSignal(int iBoardNumber, int iChannel, int iSignalType, int iRange,
                                            int iMinimum, int iMaximum, double dFrequency);

#endif // DLL_H
