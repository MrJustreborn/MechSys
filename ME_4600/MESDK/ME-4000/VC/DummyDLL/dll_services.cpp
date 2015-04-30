
#include <stdio.h>
#include <windows.h>

#include ".\me4000dll.h"

#include ".\dll.h"



int _declspec(dllexport) me4000GetDLLVersion(unsigned long* pulVersion)
{
    *pulVersion = 0x4321;
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000GetDriverVersion(unsigned long* pulVersion)
{
    *pulVersion = 0xCD;
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000FrequencyToTicks(
    double dRequiredFreq,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedFreq)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000TimeToTicks(double dRequiredTime,
                                                    unsigned long* pulTicksLowPart, unsigned long* pulTicksHighPart,
                                                                                                double* pdAchievedTime)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000GetBoardVersion(unsigned int uiBoardNumber, unsigned short* pusVersion)
{
    *pusVersion = 0x4683;
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000GetSerialNumber(unsigned int uiBoardNumber, unsigned long* pulSerialNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AISingle(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                            int iRange, int iSDMode, int iTriggerMode, int iExtTriggerEdge,
                                                        unsigned long ulTimeOutSeconds, short* psDigitalValue)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AIMakeChannelListEntry(unsigned int uiChannelNumber, int iRange,
                                                                        unsigned char* pucChanListEntry)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AIConfig(unsigned int uiBoardNumber, unsigned char* pucChanList,
                                            unsigned int uiChanListCount, int iSDMode, int iSimultaneous,
                                                        unsigned long ulReserved, unsigned long ulChanTicks,
                                                        unsigned long ulScanTicksLow, unsigned long ulScanTicksHigh,
                                                                int iAcqMode, int iExtTriggerMode, int iExtTriggerEdge)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AIScan(unsigned int uiBoardNumber, unsigned int uiNumberOfChanLists,
                                                    short* psBuffer, unsigned long ulBufferSizeValues,
                                                            int iExecutionMode, ME4000_P_AI_CALLBACK_PROC pCallbackProc,
                                                    void* pCallbackContext, unsigned int uiRefreshFrequency,
                                                            ME4000_P_AI_TERMINATE_PROC pTerminateProc, void* pTerminateContext,
                                                                                        unsigned long ulTimeOutSeconds)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AIContinuous(unsigned int uiBoardNumber, ME4000_P_AI_CALLBACK_PROC pCallbackProc,
                                                void* pCallbackContext, unsigned int uiRefreshFrequency,
                                                                                unsigned long ulTimeOutSeconds)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AIStart(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AIGetNewValues(unsigned int uiBoardNumber, short* psBuffer,
                                                unsigned long ulNumberOfValuesToRead, int iExecutionMode,
                                                            unsigned long* pulNumberOfValuesRead, int* piLastError)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AIStop(unsigned int uiBoardNumber, int iReserved)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AIExtractValues(unsigned int uiChannelNumber,
                                                        short* psAIBuffer, unsigned long ulAIDataCount,
                                                    unsigned char* pucChanList, unsigned int uiChanListCount,
                                                                short* psChanBuffer, unsigned long ulChanBufferSizeValues,
                                                                                        unsigned long* pulChanDataCount)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AIDigitToVolt(short sDigit, int iRange, double* pdVolt)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AIReset(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000AIGetStatus(unsigned int uiBoardNumber, int iWaitIdle, int* piStatus)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000AOSingle(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                                                int iTriggerMode, int iExtTriggerEdge,
                                                                    unsigned long ulTimeOutSeconds, short sValue)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AOSingleSimultaneous(unsigned int uiBoardNumber, unsigned int* puiChannelNumber,
                                                        unsigned long ulCount, int iTriggerMode, int* piExtTriggerEnable,
                                                            int* piExtTriggerEdge, unsigned long ulTimeOutSeconds, short* psValue)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000AOUpdate(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AOConfig(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                                    unsigned long ulTicks, int iTriggerMode, int iExtTriggerEdge)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AOWraparound(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                                short* psBuffer, unsigned long ulDataCount,
                                                                    unsigned long ulLoops, int iExecutionMode,
                                                        ME4000_P_AO_TERMINATE_PROC pTerminateProc, void* pTerminateContext,
                                                                                        unsigned long ulTimeOutSeconds)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AOContinuous(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                                    short* psBuffer, unsigned long ulDataCount,
                                                            ME4000_P_AO_CALLBACK_PROC pCallbackProc, void* pCallbackContext,
                                                    unsigned long ulTimeOutSeconds, unsigned long* pulNumberOfValuesWritten)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AOStart(unsigned int uiBoardNumber, unsigned int uiChannelNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AOStartSynchronous(unsigned int uiBoardNumber, unsigned int* puiChannelNumber,
                                                    unsigned long ulCount, int iTriggerMode, int* piExtTriggerEnable,
                                                                    int* piExtTriggerEdge, unsigned long ulTimeOutSeconds)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000AOAppendNewValues(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                                    short* psBuffer, unsigned long ulNumberOfValuesToAppend,
                                                            int iExecutionMode, unsigned long* pulNumberOfValuesAppended)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AOStop(unsigned int uiBoardNumber, unsigned int uiChannelNumber, int iStopMode)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AOVoltToDigit(double dVolt, short* psDigit)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AOReset(unsigned int uiBoardNumber, unsigned int uiChannelNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000AOWaveGen(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                            int iShape, double dAmplitude, double dOffset, double dFrequency)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000AOGetStatus(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                                                                int iWaitIdle, int* piStatus)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000DIOConfig(unsigned int uiBoardNumber,
                                                unsigned int uiPortNumber, int iPortDirection)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOResetAll(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOGetBit(unsigned int uiBoardNumber, unsigned int uiPortNumber,
                                                                unsigned int uiBitNumber, int* piBitValue)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOGetByte(unsigned int uiBoardNumber, unsigned int uiPortNumber,
                                                                                unsigned char* pucByteValue)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOSetBit(unsigned int uiBoardNumber, unsigned int uiPortNumber,
                                                                unsigned int uiBitNumber, int iBitValue)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOSetByte(unsigned int uiBoardNumber, unsigned int uiPortNumber,
                                                                                unsigned char ucByteValue)
{
    return(ME_ERROR_NONE);
}



int _declspec(dllexport) me4000CntWrite(unsigned int uiBoardNumber,
                                            unsigned int uiCounterNumber, int iMode, unsigned short usValue)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000CntRead(unsigned int uiBoardNumber,
                                                    unsigned int uiCounterNumber, unsigned short* pusValue)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000CntPWMStart(unsigned int uiBoardNumber, unsigned int uiPreScaler, int iDutyCycle)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000CntPWMStop(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000ExtIrqEnable(unsigned int uiBoardNumber,
                                                ME4000_P_EXT_IRQ_PROC pExtIrqProc, void* pExtIrqContext)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000ExtIrqDisable(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000ExtIrqGetCount(unsigned int uiBoardNumber, unsigned int* puiIrqCount)
{
    return(ME_ERROR_NONE);
}



int _declspec(dllexport) me4000DIOBPPortConfig(unsigned int uiBoardNumber, unsigned int uiPortNumber,
                                                                                        int iOutputMode)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOBPConfig(unsigned int uiBoardNumber, unsigned long ulTicks, int iTriggerMode, int iExtTriggerEdge)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOBPWraparound(unsigned int uiBoardNumber,
                                                short* psBuffer, unsigned long ulDataCount,
                                                                            unsigned long ulLoops, int iExecutionMode,
                                                                ME4000_P_DIOBP_TERMINATE_PROC pTerminateProc, void* pTerminateContext,
                                                                                                    unsigned long ulTimeOutSeconds)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOBPContinuous(unsigned int uiBoardNumber,
                                                    short* psBuffer, unsigned long ulDataCount,
                                                        ME4000_P_DIOBP_CALLBACK_PROC pCallbackProc, void* pCallbackContext,
                                                unsigned long ulTimeOutSeconds, unsigned long* pulNumberOfValuesWritten)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOBPStart(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOBPAppendNewValues(unsigned int uiBoardNumber,
                                                                short* psBuffer, unsigned long ulNumberOfValuesToAppend,
                                                                        int iExecutionMode, unsigned long* pulNumberOfValuesAppended)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOBPStop(unsigned int uiBoardNumber, int iStopMode)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000DIOBPReset(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000DIOBPGetStatus(unsigned int uiBoardNumber, int iWaitIdle, int* piStatus)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigOpen(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000MultiSigReset(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}

int  _declspec(dllexport) me4000MultiSigAddressLED(unsigned int uiBoardNumber, unsigned int uiBase, int iLEDStatus)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000MultiSigSetGain(unsigned int uiBoardNumber, unsigned int uiBase,
                                                                            int iChannelGroup, int iGain)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000MultiSigClose(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAIOpen(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAISingle(unsigned int uiBoardNumber, unsigned int uiAIChannelNumber,
                                                        unsigned int uiMuxChannelNumber,
                                                        int iGain, int iTriggerMode, int iExtTriggerEdge,
                                                        unsigned long ulTimeOutSeconds, short* psDigitalValue)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAIConfig(unsigned int uiBoardNumber, unsigned int uiAIChannelNumber,
                                                    unsigned char* pucMuxChanList, unsigned int uiMuxChanListCount,
                                                    unsigned long ulReserved, unsigned long ulChanTicks,
                                                        unsigned long ulScanTicksLow, unsigned long ulScanTicksHigh,
                                                                        int iAcqMode, int iExtTriggerMode, int iExtTriggerEdge)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAIScan(unsigned int uiBoardNumber, unsigned int uiNumberOfMuxLists,
                                                short* psBuffer, unsigned long ulBufferSizeValues,
                                                            int iExecutionMode, ME4000_P_AI_CALLBACK_PROC pCallbackProc,
                                                    void* pCallbackContext, unsigned int uiRefreshFrequency,
                                                            ME4000_P_AI_TERMINATE_PROC pTerminateProc, void* pTerminateContext,
                                                                                        unsigned long ulTimeOutSeconds)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAIContinuous(unsigned int uiBoardNumber, ME4000_P_AI_CALLBACK_PROC pCallbackProc,
                                                        void* pCallbackContext, unsigned int uiRefreshFrequency,
                                                                                        unsigned long ulTimeOutSeconds)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAIStart(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAIGetNewValues(unsigned int uiBoardNumber, short* psBuffer,
                                                        unsigned long ulNumberOfValuesToRead, int iExecutionMode,
                                                                unsigned long* pulNumberOfValuesRead, int* piLastError)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAIStop(unsigned int uiBoardNumber, int iReserved)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAIExtractValues(unsigned int uiMuxChannelNumber,
                                                        short* psAIBuffer, unsigned long ulAIDataCount,
                                                            unsigned char* pucMuxChanList, unsigned int uiMuxChanListCount,
                                                                    short* psChanBuffer, unsigned long ulChanBufferSizeValues,
                                                                                                unsigned long* pulChanDataCount)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAIDigitToSize(short sDigit, int iGain, int iModuleType, double dIMeasured, double* pdSize)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAIReset(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000MultiSigAIGetStatus(unsigned int uiBoardNumber, int iWaitIdle, int* piStatus)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000MultiSigAIClose(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAOOpen(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000MultiSigAOSingle(unsigned int uiBoardNumber, unsigned int uiDemuxChannelNumber,
                                                    int iTriggerMode, int iExtTriggerEdge, unsigned long ulTimeOutSeconds,
                                                                                                                short sValue)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAOConfig(unsigned int uiBoardNumber,
                                                unsigned char* pucDemuxChanList, unsigned int uiDemuxChanListCount,
                                                                unsigned long ulTicks, int iTriggerMode, int iExtTriggerEdge)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAOWraparound(unsigned int uiBoardNumber,
                                                            short* psBuffer, unsigned long ulDataCount,
                                                                                unsigned long ulLoops, int iExecutionMode,
                                                                ME4000_P_DIOBP_TERMINATE_PROC pTerminateProc, void* pTerminateContext,
                                                                                                    unsigned long ulTimeOutSeconds)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAOContinuous(unsigned int uiBoardNumber,
                                                        short* psBuffer, unsigned long ulDataCount,
                                                                    ME4000_P_DIOBP_CALLBACK_PROC pCallbackProc, void* pCallbackContext,
                                                        unsigned long ulTimeOutSeconds, unsigned long* pulNumberOfValuesWritten)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAOStart(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAOAppendNewValues(unsigned int uiBoardNumber,
                                                                short* psBuffer, unsigned long ulNumberOfValuesToAppend,
                                                                        int iExecutionMode, unsigned long* pulNumberOfValuesAppended)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAOStop(unsigned int uiBoardNumber, int iStopMode)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAOVoltToDigit(double dVolt, short* psDigit)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAOReset(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAOGetStatus(unsigned int uiBoardNumber, int iWaitIdle, int* piStatus)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me4000MultiSigAOClose(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000ErrorSetDefaultProc(int iDefaultProcStatus)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me6000ErrorSetUserProc(ME6000_P_ERROR_PROC pErrorProc)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me6000ErrorGetMessage(int iErrorCode, char* pcMessage, unsigned int uiBufferSize)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000ErrorGetLastMessage(char* pcMessage, unsigned int uiBufferSize)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000GetDLLVersion(unsigned long* pulVersion)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000GetDriverVersion(unsigned long* pulVersion)
{
    return(ME_ERROR_NONE);
}



int _declspec(dllexport) me6000FrequencyToTicks(double dRequiredFreq,
                                                    unsigned long* pulTicksLowPart, unsigned long* pulTicksHighPart,
                                                                                                double* pdAchievedFreq)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000TimeToTicks(double dRequiredTime,
                                                    unsigned long* pulTicksLowPart, unsigned long* pulTicksHighPart,
                                                                                                double* pdAchievedTime)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000GetBoardVersion(unsigned int uiBoardNumber, unsigned short* pusVersion)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me6000GetSerialNumber(unsigned int uiBoardNumber, unsigned long* pulSerialNumber)
{
    return(ME_ERROR_NONE);
}



int _declspec(dllexport) me6000AOSingle(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                            int iTriggerMode, int iReserved, unsigned long ulReserved,
                                                                                                short sValue)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000AOUpdate(unsigned int uiBoardNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000AOConfig(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                                    unsigned long ulTicks, int iTriggerMode, int iExtTriggerEdge)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000AOWraparound(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                                short* psBuffer, unsigned long ulDataCount,
                                                                    unsigned long ulLoops, int iExecutionMode,
                                                        ME6000_P_AO_TERMINATE_PROC pTerminateProc, void* pTerminateContext,
                                                                                        unsigned long ulTimeOutSeconds)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000AOContinuous(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                                    short* psBuffer, unsigned long ulDataCount,
                                                            ME6000_P_AO_CALLBACK_PROC pCallbackProc, void* pCallbackContext,
                                                    unsigned long ulTimeOutSeconds, unsigned long* pulNumberOfValuesWritten)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000AOStart(unsigned int uiBoardNumber, unsigned int uiChannelNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000AOAppendNewValues(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                                    short* psBuffer, unsigned long ulNumberOfValuesToAppend,
                                                            int iExecutionMode, unsigned long* pulNumberOfValuesAppended)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000AOStop(unsigned int uiBoardNumber, unsigned int uiChannelNumber, int iStopMode)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000AOVoltToDigit(double dVolt, short* psDigit)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000AOReset(unsigned int uiBoardNumber, unsigned int uiChannelNumber)
{
    return(ME_ERROR_NONE);
}


int _declspec(dllexport) me6000AOWaveGen(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                            int iShape, double dAmplitude, double dOffset, double dFrequency)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me6000AOGetStatus(unsigned int uiBoardNumber, unsigned int uiChannelNumber,
                                                                                int iWaitIdle, int* piStatus)
{
    return(ME_ERROR_NONE);
}

