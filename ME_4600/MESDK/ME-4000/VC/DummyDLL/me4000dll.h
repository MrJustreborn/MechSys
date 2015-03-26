#include "me4000defs.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                             ME4000 Interface                                  |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                         Board Independant Routines                            |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Error Routines                                  |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000ErrorSetDefaultProc(
    int iDefaultProcStatus);

int _declspec(dllexport) me4000ErrorSetUserProc(
    ME4000_P_ERROR_PROC pErrorProc);

int _declspec(dllexport) me4000ErrorGetMessage(
    int iErrorCode,
    char* pcBuffer,
    unsigned int uiBufferSize);

int _declspec(dllexport) me4000ErrorGetLastMessage(
    char* pcBuffer,
    unsigned int uiBufferSize);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Version Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000GetDLLVersion(
    unsigned long* pulVersion);

int _declspec(dllexport) me4000GetDriverVersion(
    unsigned long* pulVersion);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Utility Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000FrequencyToTicks(
    double dRequiredFreq,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedFreq);

int _declspec(dllexport) me4000TimeToTicks(
    double dRequiredTime,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedTime);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                         Board Specific Routines                               |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            General Routines                                   |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000GetBoardVersion(
    unsigned int uiBoardNumber,
    unsigned short* pusVersion);

int _declspec(dllexport) me4000GetSerialNumber(
    unsigned int uiBoardNumber,
    unsigned long* pulSerialNumber);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               AI Routines                                     |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000AISingle(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iRange,
    int iSDMode,
    int iTriggerMode,
    int iExtTriggerEdge,
    unsigned long ulTimeOutSeconds,
    short* psDigitalValue);

int _declspec(dllexport) me4000AIMakeChannelListEntry(
    unsigned int uiChannelNumber,
    int iRange,
    unsigned char* pucChanListEntry);

int _declspec(dllexport) me4000AIConfig(
    unsigned int uiBoardNumber,
    unsigned char* pucChanList,
    unsigned int uiChanListCount,
    int iSDMode,
    int iSimultaneous,
    unsigned long ulReserved,
    unsigned long ulChanTicks,
    unsigned long ulScanTicksLow,
    unsigned long ulScanTicksHigh,
    int iAcqMode,
    int iExtTriggerMode,
    int iExtTriggerEdge);

int _declspec(dllexport) me4000AIScan(
    unsigned int uiBoardNumber,
    unsigned int uiNumberOfChanLists,
    short* psBuffer,
    unsigned long ulBufferSizeValues,
    int iExecutionMode,
    ME4000_P_AI_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned int uiRefreshFrequency,
    ME4000_P_AI_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds);

int _declspec(dllexport) me4000AIContinuous(
    unsigned int uiBoardNumber,
    ME4000_P_AI_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned int uiRefreshFrequency,
    unsigned long ulTimeOutSeconds);

int _declspec(dllexport) me4000AIStart(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000AIGetNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToRead,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesRead,
    int* piLastError);

int _declspec(dllexport) me4000AIStop(
    unsigned int uiBoardNumber,
    int iReserved);

int _declspec(dllexport) me4000AIExtractValues(
    unsigned int uiChannelNumber,
    short* psAIBuffer,
    unsigned long ulAIDataCount,
    unsigned char* pucChanList,
    unsigned int uiChanListCount,
    short* psChanBuffer,
    unsigned long ulChanBufferSizeValues,
    unsigned long* pulChanDataCount);

int _declspec(dllexport) me4000AIDigitToVolt(
    short sDigit,
    int iRange,
    double* pdVolt);

int _declspec(dllexport) me4000AIReset(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000AIGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               AO Routines                                     |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000AOSingle(
	unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iTriggerMode,
    int iExtTriggerEdge,
    unsigned long ulTimeOutSeconds,
    short sValue	);

int _declspec(dllexport) me4000AOSingleSimultaneous(
	unsigned int uiBoardNumber,
	unsigned int* puiChannelNumber,
	unsigned long ulCount,
	int iTriggerMode,
	int* piExtTriggerEnable,
	int* piExtTriggerEdge,
	unsigned long ulTimeOutSeconds,
	short* psValue	);


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// NOTE:	The following function is obsolete and is retained only for 
//			backward compatibility. It should no longer be used.
int _declspec(dllexport) me4000AOUpdate(
    unsigned int uiBoardNumber);
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

int _declspec(dllexport) me4000AOConfig(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge);

int _declspec(dllexport) me4000AOWraparound(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME4000_P_AO_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds);

int _declspec(dllexport) me4000AOContinuous(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    ME4000_P_AO_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned long ulTimeOutSeconds,
    unsigned long* pulNumberOfValuesWritten);

int _declspec(dllexport) me4000AOStart(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber);

int _declspec(dllexport) me4000AOStartSynchronous(
	unsigned int uiBoardNumber,
	unsigned int* puiChannelNumber,
	unsigned long ulCount,
	int iTriggerMode,
	int* piExtTriggerEnable,
	int* piExtTriggerEdge,
	unsigned long ulTimeOutSeconds);

int _declspec(dllexport) me4000AOAppendNewValues(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToAppend,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesAppended);

int _declspec(dllexport) me4000AOStop(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iStopMode);

int _declspec(dllexport) me4000AOVoltToDigit(
    double dVolt,
    short* psDigit);

int _declspec(dllexport) me4000AOReset(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber);

int _declspec(dllexport) me4000AOWaveGen(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iShape,
    double dAmplitude,
    double dOffset,
    double dFrequency);

int _declspec(dllexport) me4000AOGetStatus(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iWaitIdle,
    int* piStatus);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               DIO Routines                                    |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000DIOConfig(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    int iPortDirection);

int _declspec(dllexport) me4000DIOResetAll(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000DIOGetBit(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned int uiBitNumber,
    int* piBitValue);

int _declspec(dllexport) me4000DIOGetByte(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned char* pucByteValue);

int _declspec(dllexport) me4000DIOSetBit(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned int uiBitNumber,
    int iBitValue);

int _declspec(dllexport) me4000DIOSetByte(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned char ucByteValue);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            Counter Routines                                   |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000CntWrite(
    unsigned int uiBoardNumber,
    unsigned int uiCounterNumber,
    int iMode,
    unsigned short usValue);

int _declspec(dllexport) me4000CntRead(
    unsigned int uiBoardNumber,
    unsigned int uiCounterNumber,
    unsigned short* pusValue);

int _declspec(dllexport) me4000CntPWMStart(
    unsigned int uiBoardNumber,
	unsigned int uiPreScaler,
    int iDutyCycle);

int _declspec(dllexport) me4000CntPWMStop(
    unsigned int uiBoardNumber);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                         External interrupt Routines                           |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000ExtIrqEnable(
    unsigned int uiBoardNumber,
    ME4000_P_EXT_IRQ_PROC pExtIrqProc,
    void* pExtIrqContext);

int _declspec(dllexport) me4000ExtIrqDisable(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000ExtIrqGetCount(
    unsigned int uiBoardNumber,
    unsigned int* puiIrqCount);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                       DIO Bit Pattern Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000DIOBPPortConfig(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    int iOutputMode);

int _declspec(dllexport) me4000DIOBPConfig(
    unsigned int uiBoardNumber,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge);

int _declspec(dllexport) me4000DIOBPWraparound(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME4000_P_DIOBP_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds);

int _declspec(dllexport) me4000DIOBPContinuous(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    ME4000_P_DIOBP_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned long ulTimeOutSeconds,
    unsigned long* pulNumberOfValuesWritten);

int _declspec(dllexport) me4000DIOBPStart(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000DIOBPAppendNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToAppend,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesAppended);

int _declspec(dllexport) me4000DIOBPStop(
    unsigned int uiBoardNumber,
    int iStopMode);

int _declspec(dllexport) me4000DIOBPReset(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000DIOBPGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            MultiSig Routines                                  |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000MultiSigOpen(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000MultiSigReset(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000MultiSigAddressLED(
    unsigned int uiBoardNumber,
    unsigned int uiBase,
    int iLEDStatus);

int _declspec(dllexport) me4000MultiSigSetGain(
    unsigned int uiBoardNumber,
    unsigned int uiBase,
    int iChannelGroup,
    int iGain);

int _declspec(dllexport) me4000MultiSigClose(
    unsigned int uiBoardNumber);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            MultiSigAI Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000MultiSigAIOpen(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000MultiSigAISingle(
    unsigned int uiBoardNumber,
    unsigned int uiAIChannelNumber,
    unsigned int uiMuxChannelNumber,
    int iGain,
    int iTriggerMode,
    int iExtTriggerEdge,
    unsigned long ulTimeOutSeconds,
    short* psDigitalValue);

int _declspec(dllexport) me4000MultiSigAIConfig(
    unsigned int uiBoardNumber,
    unsigned int uiAIChannelNumber,
    unsigned char* pucMuxChanList,
    unsigned int uiMuxChanListCount,
    unsigned long ulReserved,
    unsigned long ulChanTicks,
    unsigned long ulScanTicksLow,
    unsigned long ulScanTicksHigh,
    int iAcqMode,
    int iExtTriggerMode,
    int iExtTriggerEdge);

int _declspec(dllexport) me4000MultiSigAIScan(
    unsigned int uiBoardNumber,
    unsigned int uiNumberOfMuxLists,
    short* psBuffer,
    unsigned long ulBufferSizeValues,
    int iExecutionMode,
    ME4000_P_AI_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned int uiRefreshFrequency,
    ME4000_P_AI_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds);

int _declspec(dllexport) me4000MultiSigAIContinuous(
    unsigned int uiBoardNumber,
    ME4000_P_AI_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned int uiRefreshFrequency,
    unsigned long ulTimeOutSeconds);

int _declspec(dllexport) me4000MultiSigAIStart(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000MultiSigAIGetNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToRead,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesRead,
    int* piLastError);

int _declspec(dllexport) me4000MultiSigAIStop(
    unsigned int uiBoardNumber,
    int iReserved);

int _declspec(dllexport) me4000MultiSigAIExtractValues(
    unsigned int uiMuxChannelNumber,
    short* psAIBuffer,
    unsigned long ulAIDataCount,
    unsigned char* pucMuxChanList,
    unsigned int uiMuxChanListCount,
    short* psChanBuffer,
    unsigned long ulChanBufferSizeValues,
    unsigned long* pulChanDataCount);

int _declspec(dllexport) me4000MultiSigAIDigitToSize(
    short sDigit,
    int iGain,
    int iModuleType,
    double dIMeasured,
    double* pdSize);

int _declspec(dllexport) me4000MultiSigAIReset(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000MultiSigAIGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus);

int _declspec(dllexport) me4000MultiSigAIClose(
    unsigned int uiBoardNumber);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            MultiSigAO Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me4000MultiSigAOOpen(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000MultiSigAOSingle(
    unsigned int uiBoardNumber,
    unsigned int uiDemuxChannelNumber,
    int iTriggerMode,
    int iExtTriggerEdge,
    unsigned long ulTimeOutSeconds,
    short sValue);

int _declspec(dllexport) me4000MultiSigAOConfig(
    unsigned int uiBoardNumber,
    unsigned char* pucDemuxChanList,
    unsigned int uiDemuxChanListCount,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge);

int _declspec(dllexport) me4000MultiSigAOWraparound(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME4000_P_AO_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds);

int _declspec(dllexport) me4000MultiSigAOContinuous(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    ME4000_P_AO_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned long ulTimeOutSeconds,
    unsigned long* pulNumberOfValuesWritten);

int _declspec(dllexport) me4000MultiSigAOStart(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000MultiSigAOAppendNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToAppend,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesAppended);

int _declspec(dllexport) me4000MultiSigAOStop(
    unsigned int uiBoardNumber,
    int iStopMode);

int _declspec(dllexport) me4000MultiSigAOVoltToDigit(
    double dVolt,
    short* psDigit);

int _declspec(dllexport) me4000MultiSigAOReset(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me4000MultiSigAOGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus);

int _declspec(dllexport) me4000MultiSigAOClose(
    unsigned int uiBoardNumber);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                             ME6000 Interface                                  |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                         Board Independant Routines                            |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Error Routines                                  |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me6000ErrorSetDefaultProc(
    int iDefaultProcStatus);

int _declspec(dllexport) me6000ErrorSetUserProc(
    ME4000_P_ERROR_PROC pErrorProc);

int _declspec(dllexport) me6000ErrorGetMessage(
    int iErrorCode,
    char* pcBuffer,
    unsigned int uiBufferSize);

int _declspec(dllexport) me6000ErrorGetLastMessage(
    char* pcBuffer,
    unsigned int uiBufferSize);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Version Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me6000GetDLLVersion(
    unsigned long* pulVersion);

int _declspec(dllexport) me6000GetDriverVersion(
    unsigned long* pulVersion);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Utility Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me6000FrequencyToTicks(
    double dRequiredFreq,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedFreq);

int _declspec(dllexport) me6000TimeToTicks(
    double dRequiredTime,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedTime);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                         Board Specific Routines                               |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            General Routines                                   |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me6000GetBoardVersion(
    unsigned int uiBoardNumber,
    unsigned short* pusVersion);

int _declspec(dllexport) me6000GetSerialNumber(
    unsigned int uiBoardNumber,
    unsigned long* pulSerialNumber);


/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               AO Routines                                     |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me6000AOSingle(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iTriggerMode,
    int iReserved,
    unsigned long ulReserved,
    short sValue	);

int _declspec(dllexport) me6000AOUpdate(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me6000AOConfig(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge);

int _declspec(dllexport) me6000AOWraparound(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME6000_P_AO_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds);

int _declspec(dllexport) me6000AOContinuous(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    ME6000_P_AO_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned long ulTimeOutSeconds,
    unsigned long* pulNumberOfValuesWritten);

int _declspec(dllexport) me6000AOStart(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber);

int _declspec(dllexport) me6000AOAppendNewValues(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToAppend,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesAppended);

int _declspec(dllexport) me6000AOStop(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iStopMode);

int _declspec(dllexport) me6000AOVoltToDigit(
    double dVolt,
    short* psDigit);

int _declspec(dllexport) me6000AOReset(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber);

int _declspec(dllexport) me6000AOWaveGen(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iShape,
    double dAmplitude,
    double dOffset,
    double dFrequency);

int _declspec(dllexport) me6000AOGetStatus(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iWaitIdle,
    int* piStatus);

#ifdef __cplusplus
} // extern "C"
#endif
