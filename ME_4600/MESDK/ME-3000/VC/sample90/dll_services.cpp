
#include <stdio.h>
#include <windows.h>

#include "dll.h"



int meGetDLLVersion(void)
{
    return 0x00090099;
}


int meGetDriverVersion(char* pcBuffer, int iBufferSize)
{
    pcBuffer, iBufferSize;
	return(FALSE);
}


int meGetBoardInfo(int iBoardNumber, PME_BOARD_INFO pBoardInfo)
{
    pBoardInfo;
    return TRUE;
}


int meGetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    piSerialNumber;
    return TRUE;
}


int meGetInterrupts(int iBoardNumber, PME_BOARD_ISR pInt)
{
    pInt;
    return TRUE;
}


int meGetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    pcErrortext, iBufferSize;
    return TRUE;
}


int meErrorMessage(char *pcWindowTitle)
{
    pcWindowTitle = 0;
	return TRUE;
}


int meGeneralReset(int iBoardNumber)
{
    return TRUE;
}


int meDLLBoardInfo(int iBoardNumber, PME_BOARD_INFO pBoardInfo)
{
    pBoardInfo;
    return TRUE;
}



int meGetDLLTimeStamp(char *pcBuffer, int iBufferSize)
{
	pcBuffer, iBufferSize;
	return TRUE;
}



int meGetDriverTimeStamp(char* pcBuffer, int iBufferSize)
{
    pcBuffer, iBufferSize;
	return TRUE;
}


int meGetPCIConfiguration(int iBoardNumber, PME_PLX9050_INFO pBoardData)
{
    pBoardData;
    return TRUE;
}


int meGetVECModel(int iBoardNumber, int *piMEVECModel)
{
    piMEVECModel;
    return TRUE;
}


int meGetDriverStatus(int iBoardNumber, PME_DRIVER_STATUS pStatus)
{
    pStatus;
    return TRUE;
}


int meLoadFirmware(int iBoardNumber, char *pcLicenceNumber)
{
    pcLicenceNumber;
    return TRUE;
}


int meInitialize(int iBoardNumber)
{
    return TRUE;
}


// Digial I/O functions
int meDIOSetPortDirection(int iBoardNumber, int iPortNo, int iDir)
{
    iPortNo, iDir;
    return TRUE;
}


int meDIGetBit(int iBoardNumber, int iPortNo, int iBitNo, int *piBitValue)
{
    iPortNo, iBitNo, piBitValue;
    return TRUE;
}


int meDIGetByte(int iBoardNumber, int iPortNo, int iByteNo, int *piByteValue)
{
    iPortNo, iByteNo, piByteValue;
    return TRUE;
}


int meDIGetWord(int iBoardNumber, int iPortNo, int *piValue)
{
    iPortNo, piValue;
    return TRUE;
}



int meDOSetBit(int iBoardNumber, int iPortNo, int iBitNo, int iBitValue)
{
    iPortNo, iBitNo, iBitValue;
    return TRUE;
}


int meDOSetByte(int iBoardNumber, int iPortNo, int iByteNo, int iByteValue)
{
    iPortNo, iByteNo, iByteValue;
    return TRUE;
}


int meDOSetWord(int iBoardNumber, int iPortNo, int iValue)
{
    iPortNo, iValue;
    return TRUE;
}


int meDOReset(int iBoardNumber, int iPortNo)
{
    iPortNo;
    return TRUE;
}



// Thread priority function
int meSetPriority(int iBoardNumber, int iPriority)
{
    iPriority;
    return TRUE;
}

 												  

// Analog input functions
int meAIClearChannelList(int iBoardNumber)
{
    return TRUE;
}


int meAIAddToChannelList(int iBoardNumber, int iEntry)
{
    iEntry;
    return TRUE;
}



int meFileName(int iBoardNumber, int iType, char *pcFileName)
{
    iType, pcFileName;
    return TRUE;
}


int meFrequencyToCounter(double dFreq)
{
    dFreq;
    return TRUE;
}



int meAISetTimer(int iBoardNumber, int iScan, int iChan)
{
    iScan, iChan;
    return TRUE;
}


int meAISetTrigger(int iBoardNumber, int iModePolarity)
{
    iModePolarity;
    return TRUE;
}



int meAIMakeChannelListEntry(int iChannel, int iRange, int iMode, int *piEntry)
{
    iChannel, iRange, iMode, piEntry;
	return TRUE;
}



int meAISetSimultaneous(int iBoardNumber, int iMode)
{
    iMode;
    return TRUE;
}


					
int meAIStop(int iBoardNumber)
{
    return TRUE;
}

 

int meAISingle(int iBoardNumber, int iChannel, int iMode, short *psValue)
{
    iChannel, iMode, psValue, TRUE;
    return TRUE;
}



int meAISingleEx(int iBoardNumber, int iChannel, int iRange, 
				int iLoops, int iDelay, short *psValue, PSHORT_PROC pCallback)
{
    iChannel, iRange, iLoops, iDelay, psValue, pCallback;
    return TRUE;
}


				
int meAIMultiple(int iBoardNumber, short *psBuffer, int iCount, int	iMode)
{
    psBuffer, iCount, iMode, TRUE;
    return TRUE;
}

													 

int meAIMultipleEx(int iBoardNumber, short *psBuffer, int iCount, 
						int iMode, int iLoops, int iDelay, P_1_PROC pCallback)
{
    psBuffer, iCount, iMode, iLoops, iDelay, pCallback;
    return TRUE;
}


				   
int meAIQuick(int iBoardNumber, short *psBuffer, int iCount, int iMode)
{
    psBuffer, iCount, iMode, TRUE;
    return TRUE;
}

												  

int meAIQuickEx(int iBoardNumber, short *psBuffer, int iCount, 
						int iMode, int iLoops, int iDelay, P_1_PROC pCallback)
{
    psBuffer, iCount, iMode, iLoops, iDelay, pCallback;
    return TRUE;
}



int meAIScan(int iBoardNumber, short *psBuffer, int iSize, 
														int iCount, int iMode)
{
    psBuffer, iSize, iCount, iMode, TRUE;
    return TRUE;
}



int meAIScanEx(int iBoardNumber, short *psBuffer, int iSize, int iCount, 
						int iMode, int iLoops, int iDelay, P_1_PROC pCallback)
{
    psBuffer, iSize, iCount, iMode, iLoops, iDelay, pCallback;
    return TRUE;
}

int meAIContinuous(int iBoardNumber, int iFrameSize, int iBufferSize, P_1_PROC pCallback)
{
    iFrameSize, iBufferSize, pCallback;
    return TRUE;
}


int meAIClearDataFIFO(int iBoardNumber)
{
    return TRUE;
}

int meAIReadFIFO(int iBoardNumber, short *psBuffer, int iCount)
{
    psBuffer, iCount;
    return TRUE;
}

int meAIStartByExternalTrigger(int iBoardNumber, int iModePolarity)
{
    iModePolarity;
    return TRUE;
}

int meAOReset(int iBoardNumber)
{
    return TRUE;
}


int meAOSetMode(int iBoardNumber, int iChannel, int iRange, int iMode)
{
    iChannel, iRange, iMode;
    return TRUE;
}


int meAOSingle(int iBoardNumber, int iChannel, short sValue)
{
    iChannel, sValue;
    return TRUE;
}


int meAOUpdate(int iBoardNumber)
{
    return TRUE;
}


int meAOSetTimer(int iBoardNumber, int iTime)
{
    iTime;
    return TRUE;
}


int meAOSetTrigger(int iBoardNumber, int iModePolarity)
{
    iModePolarity;
    return TRUE;
}


int meAOClearDACFIFO(int iBoardNumber)
{
    return TRUE;
}


int meAOAddToDACFIFO(int iBoardNumber, int iEntry)
{
    iEntry;
    return TRUE;
}


int meAOWrapAround(int iBoardNumber)
{
    return TRUE;
}


int meAOStop(int iBoardNumber)
{
    return TRUE;
}


int meAOContinuous(int iBoardNumber, int iMode, int iSize, short *psBuffer)
{
    iMode, iSize, psBuffer, TRUE;
    return TRUE;
}


int meAOStopEx(int iBoardNumber)
{
    return TRUE;
}



int meAOContinuousEx(int iBoardNumber, int iMode, int iSize, short *psBuffer,	
								  int iLoops, int iDelay, PVOID_PROC pCallback)
{
    iMode, iSize, psBuffer,	iLoops, iDelay, pCallback;
    return TRUE;
}



int meAOGenerateSignal(int iBoardNumber, int iChannel, int iSignalForm, int iRange, int iMinimum, int iMaximum, double dFrequency)
{
    iChannel, iSignalForm, iRange, iMinimum, iMaximum, dFrequency;
    return TRUE;
}



int mePWMSetMode(int iBoardNumber, double dFrequency, 
												int iDutyCycle, int iInverted)
{
    dFrequency, iDutyCycle, iInverted;
    return TRUE;
}



int mePWMStart(int iBoardNumber)
{
    return TRUE;
}


int mePWMStop(int iBoardNumber)
{
    return TRUE;
}



int meSIOGetRegisters(int iBoardNumber, PME_BOARD_SIO_REGS pSIORegs)
{
    pSIORegs;
    return TRUE;
}


int meSIOLoopBackTest(int iBoardNumber)
{
    return TRUE;
}


int meSIOSetup(int iBoardNumber, int iBaud, int iLen, int iStop, char cParity)
{
    iBaud, iLen, iStop, cParity;
    return TRUE;
}


int meSIOWriteRegister(int iBoardNumber, char cReg, char cVal)
{
    cReg, cVal;
    return TRUE;
}


int meSIOReadRegister(int iBoardNumber, char cReg)
{
    cReg;
    return TRUE;
}


int meSIOTransmit(int iBoardNumber, int iMode, int iCount, char *pcBuffer)
{
    iMode, iCount, pcBuffer;
    return TRUE;
}


int meSIOReceive(int iBoardNumber, int iMode, int iCount, char *pcBuffer)
{
    iMode, iCount, pcBuffer;
    return TRUE;
}



int meSIOOpen(int iBoardNumber, int iMode, 
										int iInBufferSize, int iOutBufferSize)
{
    iMode, iInBufferSize, iOutBufferSize;
    return TRUE;
}



int meSIOClose(int iBoardNumber)
{
    return TRUE;
}


int meSIOClearBuffer(int iBoardNumber)
{
    return TRUE;
}


int meSIOCheckBuffer(int iBoardNumber, PME_BOARD_SIO pSio)
{
    pSio;
    return TRUE;
}


int meSIOCheckError(int iBoardNumber)
{
    return TRUE;
}



int meEnableExternalInt(int iBoardNumber, PVOID_PROC pCallback)
{
    pCallback;
    return TRUE;
}


int meDisableExternalInt(int iBoardNumber)
{
    return TRUE;
}



int meCNTStart(int iBoardNumber, int iCounter)
{
    iCounter;
    return TRUE;
}


int meCNTRead(int iBoardNumber, int iCounter, short *psCounterValue)
{
    iCounter, psCounterValue;
    return TRUE;
}



int meCNTInterrupt(int iBoardNumber, int iCounter, 
											int iFlag, PVOID_PROC pCallback)
{
    iCounter, iFlag, pCallback;
    return TRUE;
}


int meCNTReset(int iBoardNumber, int iCounter)
{
    iCounter;
    return TRUE;
}



int meCNTSetRange(int iBoardNumber, int iCounter, 
												int iEndValue, int iStartValue)
{
    iCounter, iEndValue, iStartValue;
    return TRUE;
}



