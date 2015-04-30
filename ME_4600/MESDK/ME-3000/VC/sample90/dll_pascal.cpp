
#include <stdio.h>
#include <windows.h>

#include "dll.h"

extern "C" {

/*--------------------Existing  ME3000 Functions ----------------------------------*/

// Error handling
_declspec(dllexport) int _stdcall VBme3000GetDriverErrorString(char *pcErrorText)
{
	return( meGetDrvErrMess(pcErrorText, 256) );
}

_declspec(dllexport) int _stdcall VBme3000ErrorMessage(char *pcWindowTitle)
{
	return( meErrorMessage(pcWindowTitle) );
}

// General functions
_declspec(dllexport) int _stdcall VBme3000GeneralReset(int iBoardNumber)
{
	return( meGeneralReset(iBoardNumber) );
}

_declspec(dllexport) int _stdcall VBme3000GetInterrupts(int iBoardNumber, PME_BOARD_ISR pInt)
{
	return( meGetInterrupts(iBoardNumber, pInt) );
}


_declspec(dllexport) int _stdcall VBme3000GetBoardInfo(int iBoardNumber, PME_BOARD_INFO pBoardInfo)
{
	return( meGetBoardInfo(iBoardNumber, pBoardInfo) );
}


_declspec(dllexport) int _stdcall VBme3000DLLBoardInfo(int iBoardNumber, PME_BOARD_INFO pBoardInfo)
{
	return( meDLLBoardInfo(iBoardNumber, pBoardInfo) );
}


_declspec(dllexport) int _stdcall VBme3000GetDLLVersion(void)
{
	return( meGetDLLVersion() );
}

_declspec(dllexport) int _stdcall VBme3000GetDLLTimeStamp(char *pcBuffer)
{
	return( meGetDLLTimeStamp(pcBuffer, 25) );
}

_declspec(dllexport) int _stdcall VBme3000GetDriverVersion(char *pcBuffer)
{
	return( meGetDriverVersion(pcBuffer, 10) );
}

_declspec(dllexport) int _stdcall VBme3000GetDriverTimeStamp(char *pcBuffer)
{
	return( meGetDriverTimeStamp(pcBuffer, 25) );
}

_declspec(dllexport) int _stdcall VBme3000GetPCIConfiguration(int iBoardNumber, PME_PLX9050_INFO pBoardData)
{
	return( meGetPCIConfiguration(iBoardNumber, pBoardData) );
}


_declspec(dllexport) int _stdcall VBme3000GetVECModel(int iBoardNumber, int *piMEVECModel)
{
	return( meGetVECModel(iBoardNumber, piMEVECModel) );
}


_declspec(dllexport) int _stdcall VBme3000GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
	return( meGetSerialNumber(iBoardNumber, piSerialNumber) );
}


_declspec(dllexport) int _stdcall VBme3000GetDriverStatus(int iBoardNumber, PME_DRIVER_STATUS pStatus)
{
	return( meGetDriverStatus(iBoardNumber, pStatus) );
}


_declspec(dllexport) int _stdcall VBme3000Initialize(int iBoardNumber)
{
	return( meInitialize(iBoardNumber) );
}



// Digial I/O functions
_declspec(dllexport) int _stdcall VBme3000DIOSetPortDirection(int iBoardNumber, int iPortNo, int iDir)
{
	return( meDIOSetPortDirection(iBoardNumber, iPortNo, iDir) );
}


_declspec(dllexport) int _stdcall VBme3000DIGetBit(int iBoardNumber, int iPortNo, int iBitNo, int *piBitValue)
{
	return( meDIGetBit(iBoardNumber, iPortNo, iBitNo, piBitValue) );
}


_declspec(dllexport) int _stdcall VBme3000DIGetByte(int iBoardNumber, int iPortNo, int iByteNo, int *piByteValue)
{
	return( meDIGetByte(iBoardNumber, iPortNo, iByteNo, piByteValue) );
}


_declspec(dllexport) int _stdcall VBme3000DIGetWord(int iBoardNumber, int iPortNo, int *piValue)
{
	return( meDIGetWord(iBoardNumber, iPortNo, piValue) );
}



_declspec(dllexport) int _stdcall VBme3000DOSetBit(int iBoardNumber, int iPortNo, int iBitNo, int iBitValue)
{
	return( meDOSetBit(iBoardNumber, iPortNo, iBitNo, iBitValue) );
}


_declspec(dllexport) int _stdcall VBme3000DOSetByte(int iBoardNumber, int iPortNo, int iByteNo, int iByteValue)
{
	return( meDOSetByte(iBoardNumber, iPortNo, iByteNo, iByteValue) );
}


_declspec(dllexport) int _stdcall VBme3000DOSetWord(int iBoardNumber, int iPortNo, int iValue)
{
	return( meDOSetWord(iBoardNumber, iPortNo, iValue) );
}


_declspec(dllexport) int _stdcall VBme3000DOReset(int iBoardNumber, int iPortNo)
{
	return( meDOReset(iBoardNumber, iPortNo) );
}



// Thread priority function
_declspec(dllexport) int _stdcall VBme3000SetPriority(int iBoardNumber, int iPriority)
{
	return( meSetPriority(iBoardNumber, iPriority) );
}

 												  

// Analog input functions
_declspec(dllexport) int _stdcall VBme3000AIClearChannelList(int iBoardNumber)
{
	return( meAIClearChannelList(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme3000AIAddToChannelList(int iBoardNumber, int iEntry)
{
	return( meAIAddToChannelList(iBoardNumber, iEntry) );
}



_declspec(dllexport) int _stdcall VBme3000FileName(int iBoardNumber, int iType, char *pcFileName)
{
	return( meFileName(iBoardNumber, iType, pcFileName) );
}


_declspec(dllexport) int _stdcall VBme3000FrequencyToCounter(double dFreq)
{
	return( meFrequencyToCounter(dFreq) );
}



_declspec(dllexport) int _stdcall VBme3000AISetTimer(int iBoardNumber, int iScan, int iChan)
{
	return( meAISetTimer(iBoardNumber, iScan, iChan) );
}


_declspec(dllexport) int _stdcall VBme3000AISetTrigger(int iBoardNumber, int iModePolarity)
{
	return( meAISetTrigger(iBoardNumber, iModePolarity) );
}



_declspec(dllexport) int _stdcall VBme3000AIMakeChannelListEntry(int iChannel, int iRange, int iMode, int *piEntry)
{
	return( meAIMakeChannelListEntry(iChannel, iRange, iMode, piEntry) );
}



_declspec(dllexport) int _stdcall VBme3000AISetSimultaneous(int iBoardNumber, int iMode)
{
	return( meAISetSimultaneous(iBoardNumber, iMode) );
}


					
_declspec(dllexport) int _stdcall VBme3000AIStop(int iBoardNumber)
{
	return( meAIStop(iBoardNumber) );
}

 

_declspec(dllexport) int _stdcall VBme3000AISingle(int iBoardNumber, int iChannel, int iMode, short *psValue)
{
	return( meAISingle(iBoardNumber, iChannel, iMode, psValue) );
}



_declspec(dllexport) int _stdcall VBme3000AISingleEx(int iBoardNumber, int iChannel, int iRange, 
													int iLoops, int iDelay, short *psValue, PSHORT_PROC pCallback)
{
	return( meAISingleEx(iBoardNumber, iChannel, iRange, iLoops, iDelay, psValue, pCallback) );
}


				
_declspec(dllexport) int _stdcall VBme3000AIMultiple(int iBoardNumber, short *psBuffer, int iCount, int	iMode)
{
	return( meAIMultiple(iBoardNumber, psBuffer, iCount, iMode) );
}

													 

_declspec(dllexport) int _stdcall VBme3000AIMultipleEx(int iBoardNumber, short *psBuffer, int iCount, 
														int iMode, int iLoops, int iDelay, P_1_PROC pCallback)
{
	return( meAIMultipleEx(iBoardNumber, psBuffer, iCount, iMode, iLoops, iDelay, pCallback) );
}


				   
_declspec(dllexport) int _stdcall VBme3000AIQuick(int iBoardNumber, short *psBuffer, int iCount, int iMode)
{
	return( meAIQuick(iBoardNumber, psBuffer, iCount, iMode) );
}

												  

_declspec(dllexport) int _stdcall VBme3000AIQuickEx(int iBoardNumber, short *psBuffer, int iCount, 
														int iMode, int iLoops, int iDelay, P_1_PROC pCallback)
{
	return( meAIQuickEx(iBoardNumber, psBuffer, iCount, iMode, iLoops, iDelay, pCallback) );
}



_declspec(dllexport) int _stdcall VBme3000AIScan(int iBoardNumber, short *psBuffer, int iSize, 
														int iCount, int iMode)
{
	return( meAIScan(iBoardNumber, psBuffer, iSize, iCount, iMode) );
}



_declspec(dllexport) int _stdcall VBme3000AIScanEx(int iBoardNumber, short *psBuffer, int iSize, int iCount, 
														int iMode, int iLoops, int iDelay, P_1_PROC pCallback)
{
	return( meAIScanEx(iBoardNumber, psBuffer, iSize, iCount, iMode, iLoops, iDelay, pCallback) );
}

_declspec(dllexport) int _stdcall VBme3000AIClearDataFIFO(int iBoardNumber)
{
	return( meAIClearDataFIFO(iBoardNumber) );
}

_declspec(dllexport) int _stdcall VBme3000AIReadFIFO(int iBoardNumber, short *psBuffer, int iCount)
{
	return( meAIReadFIFO(iBoardNumber, psBuffer, iCount) );
}

_declspec(dllexport) int _stdcall VBme3000AIStartByExternalTrigger(int iBoardNumber, int iModePolarity)
{
	return( meAIStartByExternalTrigger(iBoardNumber, iModePolarity) );
}


// Analog output functions
_declspec(dllexport) int _stdcall VBme3000AOReset(int iBoardNumber)
{
	return( meAOReset(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme3000AOSetMode(int iBoardNumber, int iChannel, int iRange, int iMode)
{
	return( meAOSetMode(iBoardNumber, iChannel, iRange, iMode) );
}


_declspec(dllexport) int _stdcall VBme3000AOSingle(int iBoardNumber, int iChannel, short sValue)
{
	return( meAOSingle(iBoardNumber, iChannel, sValue) );
}


_declspec(dllexport) int _stdcall VBme3000AOUpdate(int iBoardNumber)
{
	return( meAOUpdate(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme3000AOSetTimer(int iBoardNumber, int iTime)
{
	return( meAOSetTimer(iBoardNumber, iTime) );
}


_declspec(dllexport) int _stdcall VBme3000AOSetTrigger(int iBoardNumber, int iModePolarity)
{
	return( meAOSetTrigger(iBoardNumber, iModePolarity) );
}


_declspec(dllexport) int _stdcall VBme3000AOClearDACFIFO(int iBoardNumber)
{
	return( meAOClearDACFIFO(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme3000AOAddToDACFIFO(int iBoardNumber, int iEntry)
{
	return( meAOAddToDACFIFO(iBoardNumber, iEntry) );
}


_declspec(dllexport) int _stdcall VBme3000AOWrapAround(int iBoardNumber)
{
	return( meAOWrapAround(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme3000AOStop(int iBoardNumber)
{
	return( meAOStop(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme3000AOContinuous(int iBoardNumber, int iMode, int iSize, short *psBuffer)
{
	return( meAOContinuous(iBoardNumber, iMode, iSize, psBuffer) );
}


_declspec(dllexport) int _stdcall VBme3000AOStopEx(int iBoardNumber)
{
	return( meAOStopEx(iBoardNumber) );
}



_declspec(dllexport) int _stdcall VBme3000AOContinuousEx(int iBoardNumber, int iMode, int iSize, short *psBuffer,	
																		int iLoops, int iDelay, PVOID_PROC pCallback)
{
	return( meAOContinuousEx(iBoardNumber, iMode, iSize, psBuffer, iLoops, iDelay, pCallback) );
}



// PWM functions
_declspec(dllexport) int _stdcall VBme3000PWMSetMode(int iBoardNumber, double dFrequency, 
															int iDutyCycle, int iInverted)
{
	return( mePWMSetMode(iBoardNumber, dFrequency, iDutyCycle, iInverted) );
}



_declspec(dllexport) int _stdcall VBme3000PWMStart(int iBoardNumber)
{
	return( mePWMStart(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme3000PWMStop(int iBoardNumber)
{
	return( mePWMStop(iBoardNumber) );
}



// SIO functions
_declspec(dllexport) int _stdcall VBme3000SIOGetRegisters(int iBoardNumber, PME_BOARD_SIO_REGS pSIORegs)
{
	return( meSIOGetRegisters(iBoardNumber, pSIORegs) );
}


_declspec(dllexport) int _stdcall VBme3000SIOLoopBackTest(int iBoardNumber)
{
	return( meSIOLoopBackTest(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme3000SIOSetup(int iBoardNumber, int iBaud, int iLen, int iStop, char cParity)
{
	return( meSIOSetup(iBoardNumber, iBaud, iLen, iStop, cParity) );
}


_declspec(dllexport) int _stdcall VBme3000SIOWriteRegister(int iBoardNumber, char cReg, char cVal)
{
	return( meSIOWriteRegister(iBoardNumber, cReg, cVal) );
}


_declspec(dllexport) int _stdcall VBme3000SIOReadRegister(int iBoardNumber, char cReg)
{
	return( meSIOReadRegister(iBoardNumber, cReg) );
}


_declspec(dllexport) int _stdcall VBme3000SIOTransmit(int iBoardNumber, int iMode, int iCount, char *pcBuffer)
{
	return( meSIOTransmit(iBoardNumber, iMode, iCount, pcBuffer) );
}


_declspec(dllexport) int _stdcall VBme3000SIOReceive(int iBoardNumber, int iMode, int iCount, char *pcBuffer)
{
	return( meSIOReceive(iBoardNumber, iMode, iCount, pcBuffer) );
}



_declspec(dllexport) int _stdcall VBme3000SIOOpen(int iBoardNumber, int iMode, 
													int iInBufferSize, int iOutBufferSize)
{
	return( meSIOOpen(iBoardNumber, iMode, iInBufferSize, iOutBufferSize) );
}



_declspec(dllexport) int _stdcall VBme3000SIOClose(int iBoardNumber)
{
	return( meSIOClose(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme3000SIOClearBuffer(int iBoardNumber)
{
	return( meSIOClearBuffer(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme3000SIOCheckBuffer(int iBoardNumber, PME_BOARD_SIO pSio)
{
	return( meSIOCheckBuffer(iBoardNumber, pSio) );
}


_declspec(dllexport) int _stdcall VBme3000SIOCheckError(int iBoardNumber)
{
	return( meSIOCheckError(iBoardNumber) );
}



// External interrupt functions
_declspec(dllexport) int _stdcall VBme3000EnableExternalInt(int iBoardNumber, PVOID_PROC pCallback)
{
	return( meEnableExternalInt(iBoardNumber, pCallback) );
}


_declspec(dllexport) int _stdcall VBme3000DisableExternalInt(int iBoardNumber)
{
	return( meDisableExternalInt(iBoardNumber) );
}



// Counter functions
_declspec(dllexport) int _stdcall VBme3000CNTStart(int iBoardNumber, int iCounter)
{
	return( meCNTStart(iBoardNumber, iCounter) );
}


_declspec(dllexport) int _stdcall VBme3000CNTRead(int iBoardNumber, int iCounter, short *psCounterValue)
{
	return( meCNTRead(iBoardNumber, iCounter, psCounterValue) );
}



_declspec(dllexport) int _stdcall VBme3000CNTInterrupt(int iBoardNumber, int iCounter, 
															int iFlag, PVOID_PROC pCallback)
{
	return( meCNTInterrupt(iBoardNumber, iCounter, iFlag, pCallback) );
}


_declspec(dllexport) int _stdcall VBme3000CNTReset(int iBoardNumber, int iCounter)
{
	return( meCNTReset(iBoardNumber, iCounter) );
}



_declspec(dllexport) int _stdcall VBme3000CNTSetRange(int iBoardNumber, int iCounter, 
														int iEndValue, int iStartValue)
{
	return( meCNTSetRange(iBoardNumber, iCounter, iEndValue, iStartValue) );
}

/*-------------------- Existing  ME2600 Functions ----------------------------------*/


// Error handling
_declspec(dllexport) int _cdecl VBme2600GetDriverErrorString(char *pcErrorText)
{
	return( meGetDrvErrMess(pcErrorText, 256) );
}

_declspec(dllexport) int _stdcall VBme2600ErrorMessage(char *pcWindowTitle)
{
	return( meErrorMessage(pcWindowTitle) );
}

// General functions
_declspec(dllexport) int _stdcall VBme2600GeneralReset(int iBoardNumber)
{
	return( meGeneralReset(iBoardNumber) );
}

_declspec(dllexport) int _stdcall VBme2600GetInterrupts(int iBoardNumber, PME_BOARD_ISR pInt)
{
	return( meGetInterrupts(iBoardNumber, pInt) );
}


_declspec(dllexport) int _stdcall VBme2600GetBoardInfo(int iBoardNumber, PME_BOARD_INFO pBoardInfo)
{
	return( meGetBoardInfo(iBoardNumber, pBoardInfo) );
}


_declspec(dllexport) int _stdcall VBme2600DLLBoardInfo(int iBoardNumber, PME_BOARD_INFO pBoardInfo)
{
	return( meDLLBoardInfo(iBoardNumber, pBoardInfo) );
}


_declspec(dllexport) int _stdcall VBme2600GetDLLVersion(void)
{
	return( meGetDLLVersion() );
}

_declspec(dllexport) int _stdcall VBme2600GetDLLTimeStamp(char *pcBuffer)
{
	return( meGetDLLTimeStamp(pcBuffer, 25) );
}

_declspec(dllexport) int _stdcall VBme2600GetDriverVersion(char *pcBuffer)
{
	return( meGetDriverVersion(pcBuffer, 10) );
}

_declspec(dllexport) int _stdcall VBme2600GetDriverTimeStamp(char *pcBuffer)
{
	return( meGetDriverTimeStamp(pcBuffer, 25) );
}

_declspec(dllexport) int _stdcall VBme2600GetPCIConfiguration(int iBoardNumber, PME_PLX9050_INFO pBoardData)
{
	return( meGetPCIConfiguration(iBoardNumber, pBoardData) );
}


_declspec(dllexport) int _stdcall VBme2600GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
	return( meGetSerialNumber(iBoardNumber, piSerialNumber) );
}


_declspec(dllexport) int _stdcall VBme2600GetDriverStatus(int iBoardNumber, PME_DRIVER_STATUS pStatus)
{
	return( meGetDriverStatus(iBoardNumber, pStatus) );
}


_declspec(dllexport) int _stdcall VBme2600Initialize(int iBoardNumber)
{
	return( meInitialize(iBoardNumber) );
}



// Digital I/O functions
_declspec(dllexport) int _stdcall VBme2600DIOSetPortDirection(int iBoardNumber, int iPortNo, int iDir)
{
	return( meDIOSetPortDirection(iBoardNumber, iPortNo, iDir) );
}


_declspec(dllexport) int _stdcall VBme2600DIGetBit(int iBoardNumber, int iPortNo, int iBitNo, int *piBitValue)
{
	return( meDIGetBit(iBoardNumber, iPortNo, iBitNo, piBitValue) );
}


_declspec(dllexport) int _stdcall VBme2600DIGetByte(int iBoardNumber, int iPortNo, int iByteNo, int *piByteValue)
{
	return( meDIGetByte(iBoardNumber, iPortNo, iByteNo, piByteValue) );
}


_declspec(dllexport) int _stdcall VBme2600DIGetWord(int iBoardNumber, int iPortNo, int *piValue)
{
	return( meDIGetWord(iBoardNumber, iPortNo, piValue) );
}



_declspec(dllexport) int _stdcall VBme2600DOSetBit(int iBoardNumber, int iPortNo, int iBitNo, int iBitValue)
{
	return( meDOSetBit(iBoardNumber, iPortNo, iBitNo, iBitValue) );
}


_declspec(dllexport) int _stdcall VBme2600DOSetByte(int iBoardNumber, int iPortNo, int iByteNo, int iByteValue)
{
	return( meDOSetByte(iBoardNumber, iPortNo, iByteNo, iByteValue) );
}


_declspec(dllexport) int _stdcall VBme2600DOSetWord(int iBoardNumber, int iPortNo, int iValue)
{
	return( meDOSetWord(iBoardNumber, iPortNo, iValue) );
}


_declspec(dllexport) int _stdcall VBme2600DOReset(int iBoardNumber, int iPortNo)
{
	return( meDOReset(iBoardNumber, iPortNo) );
}



// Thread priority function
_declspec(dllexport) int _stdcall VBme2600SetPriority(int iBoardNumber, int iPriority)
{
	return( meSetPriority(iBoardNumber, iPriority) );
}

 												  

// Analog input functions
_declspec(dllexport) int _stdcall VBme2600AIClearChannelList(int iBoardNumber)
{
	return( meAIClearChannelList(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme2600AIAddToChannelList(int iBoardNumber, int iEntry)
{
	return( meAIAddToChannelList(iBoardNumber, iEntry) );
}



_declspec(dllexport) int _stdcall VBme2600FileName(int iBoardNumber, int iType, char *pcFileName)
{
	return( meFileName(iBoardNumber, iType, pcFileName) );
}


_declspec(dllexport) int _stdcall VBme2600FrequencyToCounter(double dFreq)
{
	return( meFrequencyToCounter(dFreq) );
}



_declspec(dllexport) int _stdcall VBme2600AISetTimer(int iBoardNumber, int iScan, int iChan)
{
	return( meAISetTimer(iBoardNumber, iScan, iChan) );
}


_declspec(dllexport) int _stdcall VBme2600AISetTrigger(int iBoardNumber, int iModePolarity)
{
	return( meAISetTrigger(iBoardNumber, iModePolarity) );
}



_declspec(dllexport) int _stdcall VBme2600AIMakeChannelListEntry(int iChannel, int iRange, int iMode, int *piEntry)
{
	return( meAIMakeChannelListEntry(iChannel, iRange, iMode, piEntry) );
}



_declspec(dllexport) int _stdcall VBme2600AIStop(int iBoardNumber)
{
	return( meAIStop(iBoardNumber) );
}

 

_declspec(dllexport) int _stdcall VBme2600AISingle(int iBoardNumber, int iChannel, int iMode, short *psValue)
{
	return( meAISingle(iBoardNumber, iChannel, iMode, psValue) );
}



_declspec(dllexport) int _stdcall VBme2600AISingleEx(int iBoardNumber, int iChannel, int iRange, 
													int iLoops, int iDelay, short *psValue, PSHORT_PROC pCallback)
{
	return( meAISingleEx(iBoardNumber, iChannel, iRange, iLoops, iDelay, psValue, pCallback) );
}


				
_declspec(dllexport) int _stdcall VBme2600AIMultiple(int iBoardNumber, short *psBuffer, int iCount, int	iMode)
{
	return( meAIMultiple(iBoardNumber, psBuffer, iCount, iMode) );
}

													 

_declspec(dllexport) int _stdcall VBme2600AIMultipleEx(int iBoardNumber, short *psBuffer, int iCount, 
														int iMode, int iLoops, int iDelay, P_1_PROC pCallback)
{
	return( meAIMultipleEx(iBoardNumber, psBuffer, iCount, iMode, iLoops, iDelay, pCallback) );
}


				   
_declspec(dllexport) int _stdcall VBme2600AIQuick(int iBoardNumber, short *psBuffer, int iCount, int iMode)
{
	return( meAIQuick(iBoardNumber, psBuffer, iCount, iMode) );
}

												  

_declspec(dllexport) int _stdcall VBme2600AIQuickEx(int iBoardNumber, short *psBuffer, int iCount, 
														int iMode, int iLoops, int iDelay, P_1_PROC pCallback)
{
	return( meAIQuickEx(iBoardNumber, psBuffer, iCount, iMode, iLoops, iDelay, pCallback) );
}



_declspec(dllexport) int _stdcall VBme2600AIScan(int iBoardNumber, short *psBuffer, int iSize, 
														int iCount, int iMode)
{
	return( meAIScan(iBoardNumber, psBuffer, iSize, iCount, iMode) );
}



_declspec(dllexport) int _stdcall VBme2600AIScanEx(int iBoardNumber, short *psBuffer, int iSize, int iCount, 
														int iMode, int iLoops, int iDelay, P_1_PROC pCallback)
{
	return( meAIScanEx(iBoardNumber, psBuffer, iSize, iCount, iMode, iLoops, iDelay, pCallback) );
}

_declspec(dllexport) int _stdcall VBme2600AIClearDataFIFO(int iBoardNumber)
{
	return( meAIClearDataFIFO(iBoardNumber) );
}

_declspec(dllexport) int _stdcall VBme2600AIReadFIFO(int iBoardNumber, short *psBuffer, int iCount)
{
	return( meAIReadFIFO(iBoardNumber, psBuffer, iCount) );
}

_declspec(dllexport) int _stdcall VBme2600AIStartByExternalTrigger(int iBoardNumber, int iModePolarity)
{
	return( meAIStartByExternalTrigger(iBoardNumber, iModePolarity) );
}


// Analog output functions
_declspec(dllexport) int _stdcall VBme2600AOReset(int iBoardNumber)
{
	return( meAOReset(iBoardNumber) );
}


_declspec(dllexport) int _stdcall VBme2600AOSetMode(int iBoardNumber, int iChannel, int iRange, int iMode)
{
	return( meAOSetMode(iBoardNumber, iChannel, iRange, iMode) );
}


_declspec(dllexport) int _stdcall VBme2600AOSingle(int iBoardNumber, int iChannel, short sValue)
{
	return( meAOSingle(iBoardNumber, iChannel, sValue) );
}


_declspec(dllexport) int _stdcall VBme2600AOUpdate(int iBoardNumber)
{
	return( meAOUpdate(iBoardNumber) );
}



// External interrupt functions
_declspec(dllexport) int _stdcall VBme2600EnableExternalInt(int iBoardNumber, PVOID_PROC pCallback)
{
	return( meEnableExternalInt(iBoardNumber, pCallback) );
}


_declspec(dllexport) int _stdcall VBme2600DisableExternalInt(int iBoardNumber)
{
	return( meDisableExternalInt(iBoardNumber) );
}



/*------------------------- New  me3000 Functions ----------------------------------*/


_declspec(dllexport) int _stdcall VBme3000LoadFirmware(int iBoardNumber, char *pcLicenceNumber)
{
	return( meLoadFirmware(iBoardNumber, pcLicenceNumber) );
}


_declspec(dllexport) int _stdcall VBme3000AIContinuous(int iBoardNumber, int iFrameSize, 
																int iBufferSize, P_1_PROC pCallback)
{
	return( meAIContinuous(iBoardNumber, iFrameSize, iBufferSize, pCallback) );
}


_declspec(dllexport) int _stdcall VBme3000AOGenerateSignal(int iBoardNumber, int iChannel, int iSignalForm, 
															int iRange, int iMinimum, int iMaximum, double dFrequency)
{
	return( meAOGenerateSignal(iBoardNumber, iChannel, iSignalForm, iRange, iMinimum, iMaximum, dFrequency) );
}


_declspec(dllexport) int _stdcall VBme2600LoadFirmware(int iBoardNumber, char *pcLicenceNumber)
{
	return( meLoadFirmware(iBoardNumber, pcLicenceNumber) );
}


_declspec(dllexport) int _stdcall VBme2600AIContinuous(int iBoardNumber, int iFrameSize, 
																int iBufferSize, P_1_PROC pCallback)
{
	return( meAIContinuous(iBoardNumber, iFrameSize, iBufferSize, pCallback) );
}


_declspec(dllexport) int _stdcall VBme2600AOGenerateSignal(int iBoardNumber, int iChannel, int iSignalForm, 
															int iRange, int iMinimum, int iMaximum, double dFrequency)
{
	return( meAOGenerateSignal(iBoardNumber, iChannel, iSignalForm, iRange, iMinimum, iMaximum, dFrequency) );
}


} // extern "C"
