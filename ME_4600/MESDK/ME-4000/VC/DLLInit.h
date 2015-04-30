/*----------------------------------------------------------------------------
    File: DLLINIT.H
------------------------------------------------------------------------------

    Meilhaus Electronic GmbH

    Header file containing Typedefs for the board.  This header is
    for use in projects using dynamic function calls (no library file is
    included in the project)

    Version 1.01:   020626
-------------------------------------------------------------------------------
    Author: Andreas Bernau / Ralph Timm
-----------------------------------------------------------------------------*/


#ifndef DLLINIT_H
#define DLLINIT_H

#include "me4000defs.h"

#define SUCCESS             0x01
#define DLLNOTFOUND         0x02
#define FUNCTIONNOTFOUND    0x03
#define DLLNAME             "me4000.dll"


typedef   int(__cdecl *PF_ME4000ERRORSETDEFAULTPROC)(int iDefaultProcStatus);
typedef   int(__cdecl *PF_ME4000ERRORSETUSERPROC)(ME4000_P_ERROR_PROC pErrorProc);
typedef   int(__cdecl *PF_ME4000ERRORGETMESSAGE)(int iErrorCode, char* pcBuffer, unsigned int uiBufferSize);
typedef   int(__cdecl *PF_ME4000ERRORGETLASTMESSAGE)(char* pcBuffer, unsigned int uiBufferSize);
typedef   int(__cdecl *PF_ME4000GETDLLVERSION)(unsigned long* pulVersion);
typedef   int(__cdecl *PF_ME4000GETDRIVERVERSION)(unsigned long* pulVersion);
typedef   int(__cdecl *PF_ME4000FREQUENCYTOTICKS)(double dRequiredFreq, unsigned long* pulTicksLowPart, unsigned long* pulTicksHighPart, double* pdAchievedFreq);
typedef   int(__cdecl *PF_ME4000TIMETOTICKS)(double dRequiredTime, unsigned long* pulTicksLowPart, unsigned long* pulTicksHighPart, double* pdAchievedTime);
typedef   int(__cdecl *PF_ME4000GETBOARDVERSION)(unsigned int uiBoardNumber, unsigned short* pusVersion);
typedef   int(__cdecl *PF_ME4000GETSERIALNUMBER)(unsigned int uiBoardNumber, unsigned long* pulSerialNumber);
typedef   int(__cdecl *PF_ME4000AISINGLE)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, int iRange, int iSDMode, int iTriggerMode, int iExtTriggerEdge, unsigned long ulTimeOutSeconds, short* psDigitalValue);
typedef   int(__cdecl *PF_ME4000AIMAKECHANNELLISTENTRY)(unsigned int uiChannelNumber, int iRange, unsigned char* pucChanListEntry);
typedef   int(__cdecl *PF_ME4000AICONFIG)(unsigned int uiBoardNumber, unsigned char* pucChanList, unsigned int uiChanListCount, int iSDMode, int iSimultaneous, unsigned long ulReserved, unsigned long ulChanTicks, unsigned long ulScanTicksLow, unsigned long ulScanTicksHigh, int iAcqMode, int iExtTriggerMode, int iExtTriggerEdge);
typedef   int(__cdecl *PF_ME4000AISCAN)(unsigned int uiBoardNumber, unsigned int uiNumberOfChanLists, short* psBuffer, unsigned long ulBufferSizeValues, int iExecutionMode, ME4000_P_AI_CALLBACK_PROC pCallbackProc, void* pCallbackContext, unsigned int uiRefreshFrequency, ME4000_P_AI_TERMINATE_PROC pTerminateProc, void* pTerminateContext, unsigned long ulTimeOutSeconds);
typedef   int(__cdecl *PF_ME4000AICONTINUOUS)(unsigned int uiBoardNumber, ME4000_P_AI_CALLBACK_PROC pCallbackProc, void* pCallbackContext, unsigned int uiRefreshFrequency, unsigned long ulTimeOutSeconds);
typedef   int(__cdecl *PF_ME4000AISTART)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000AIGETNEWVALUES)(unsigned int uiBoardNumber, short* psBuffer, unsigned long ulNumberOfValuesToRead, int iExecutionMode, unsigned long* pulNumberOfValuesRead, int* piLastError);
typedef   int(__cdecl *PF_ME4000AISTOP)(unsigned int uiBoardNumber, int iReserved);
typedef   int(__cdecl *PF_ME4000AIEXTRACTVALUES)(unsigned int uiChannelNumber, short* psAIBuffer, unsigned long ulAIDataCount, unsigned char* pucChanList, unsigned int uiChanListCount, short* psChanBuffer, unsigned long ulChanBufferSizeValues, unsigned long* pulChanDataCount);
typedef   int(__cdecl *PF_ME4000AIDIGITTOVOLT)(short sDigit, int iRange, double* pdVolt);
typedef   int(__cdecl *PF_ME4000AIRESET)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000AIGETSTATUS)(unsigned int uiBoardNumber, int iWaitIdle, int* piStatus);
typedef   int(__cdecl *PF_ME4000AOSINGLE)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, int iTriggerMode, int iReserved, unsigned long ulReserved, short sValue );
typedef   int(__cdecl *PF_ME4000AOSINGLESIMULTANEOUS(unsigned int uiBoardNumber, unsigned int* puiChannelNumber, unsigned long ulCount, int iTriggerMode, int* piExtTriggerEnable, int* piExtTriggerEdge, unsigned long ulTimeOutSeconds, short* psValue);
typedef   int(__cdecl *PF_ME4000AOUPDATE)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000AOCONFIG)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, unsigned long ulTicks, int iTriggerMode, int iExtTriggerEdge);
typedef   int(__cdecl *PF_ME4000AOWRAPAROUND)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, short* psBuffer, unsigned long ulDataCount, unsigned long ulLoops, int iExecutionMode, ME4000_P_AO_TERMINATE_PROC pTerminateProc, void* pTerminateContext, unsigned long ulTimeOutSeconds);
typedef   int(__cdecl *PF_ME4000AOCONTINUOUS)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, short* psBuffer, unsigned long ulDataCount, ME4000_P_AO_CALLBACK_PROC pCallbackProc, void* pCallbackContext, unsigned long ulTimeOutSeconds, unsigned long* pulNumberOfValuesWritten);
typedef   int(__cdecl *PF_ME4000AOSTART)(unsigned int uiBoardNumber, unsigned int uiChannelNumber);
typedef   int(__cdecl *PF_ME4000AOSTARTSYNCHRONOUS(unsigned int uiBoardNumber, unsigned int* puiChannelNumber, unsigned long ulCount, int iTriggerMode, int* piExtTriggerEnable, int* piExtTriggerEdge, unsigned long ulTimeOutSeconds);
typedef   int(__cdecl *PF_ME4000AOAPPENDNEWVALUES)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, short* psBuffer, unsigned long ulNumberOfValuesToAppend, int iExecutionMode, unsigned long* pulNumberOfValuesAppended);
typedef   int(__cdecl *PF_ME4000AOSTOP)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, int iStopMode);
typedef   int(__cdecl *PF_ME4000AOVOLTTODIGIT)(double dVolt, short* psDigit);
typedef   int(__cdecl *PF_ME4000AORESET)(unsigned int uiBoardNumber, unsigned int uiChannelNumber);
typedef   int(__cdecl *PF_ME4000AOWAVEGEN)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, int iShape, double dAmplitude, double dOffset, double dFrequency);
typedef   int(__cdecl *PF_ME4000AOGETSTATUS)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, int iWaitIdle, int* piStatus);
typedef   int(__cdecl *PF_ME4000DIOCONFIG)(unsigned int uiBoardNumber, unsigned int uiPortNumber, int iPortDirection);
typedef   int(__cdecl *PF_ME4000DIORESETALL)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000DIOGETBIT)(unsigned int uiBoardNumber, unsigned int uiPortNumber, unsigned int uiBitNumber, int *piBitValue);
typedef   int(__cdecl *PF_ME4000DIOGETBYTE)(unsigned int uiBoardNumber, unsigned int uiPortNumber, unsigned char *pucByteValue);
typedef   int(__cdecl *PF_ME4000DIOSETBIT)(unsigned int uiBoardNumber, unsigned int uiPortNumber, unsigned int uiBitNumber, int iBitValue);
typedef   int(__cdecl *PF_ME4000DIOSETBYTE)(unsigned int uiBoardNumber, unsigned int uiPortNumber, unsigned char ucByteValue);
typedef   int(__cdecl *PF_ME4000CNTWRITE)(unsigned int uiBoardNumber, int iCounter, int iMode, unsigned short usValue);
typedef   int(__cdecl *PF_ME4000CNTREAD)(unsigned int uiBoardNumber, int iCounter, unsigned short *pusValue);
typedef   int(__cdecl *PF_ME4000CNTPWMSTART)(unsigned int uiBoardNumber,    unsigned int uiPreScaler, int iDutyCycle);
typedef   int(__cdecl *PF_ME4000CNTPWMSTOP)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000EXTIRQENABLE)(unsigned int uiBoardNumber, ME4000_P_EXT_IRQ_PROC pExtIrqProc, void* pExtIrqContext);
typedef   int(__cdecl *PF_ME4000EXTIRQDISABLE)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000EXTIRQGETCOUNT)(unsigned int uiBoardNumber, unsigned int *puiIrqCount);
typedef   int(__cdecl *PF_ME4000DIOBPPORTCONFIG)(unsigned int uiBoardNumber, unsigned int uiPortNumber, int iOutputMode);
typedef   int(__cdecl *PF_ME4000DIOBPCONFIG)(unsigned int uiBoardNumber, unsigned long ulTicks, int iTriggerMode, int iExtTriggerEdge);
typedef   int(__cdecl *PF_ME4000DIOBPWRAPAROUND)(unsigned int uiBoardNumber, short* psBuffer, unsigned long ulDataCount, unsigned long ulLoops, int iExecutionMode, ME4000_P_DIOBP_TERMINATE_PROC pTerminateProc, void* pTerminateContext, unsigned long ulTimeOutSeconds);
typedef   int(__cdecl *PF_ME4000DIOBPCONTINUOUS)(unsigned int uiBoardNumber, short* psBuffer, unsigned long ulDataCount, ME4000_P_DIOBP_CALLBACK_PROC pCallbackProc, void* pCallbackContext, unsigned long ulTimeOutSeconds, unsigned long* pulNumberOfValuesWritten);
typedef   int(__cdecl *PF_ME4000DIOBPSTART)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000DIOBPAPPENDNEWVALUES)(unsigned int uiBoardNumber, short* psBuffer, unsigned long ulNumberOfValuesToAppend, int iExecutionMode, unsigned long* pulNumberOfValuesAppended);
typedef   int(__cdecl *PF_ME4000DIOBPSTOP)(unsigned int uiBoardNumber, int iStopMode);
typedef   int(__cdecl *PF_ME4000DIOBPRESET)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000DIOBPGETSTATUS)(unsigned int uiBoardNumber, int iWaitIdle, int* piStatus);
typedef   int(__cdecl *PF_ME4000MULTISIGOPEN)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000MULTISIGRESET)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000MULTISIGADDRESSLED)(unsigned int uiBoardNumber, unsigned int uiBase, int iLEDStatus);
typedef   int(__cdecl *PF_ME4000MULTISIGSETGAIN)(unsigned int uiBoardNumber, unsigned int uiBase, int iChannelGroup, int iGain);
typedef   int(__cdecl *PF_ME4000MULTISIGCLOSE)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000MULTISIGAIOPEN)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000MULTISIGAISINGLE)(unsigned int uiBoardNumber, unsigned int uiAIChannelNumber, unsigned int uiMuxChannelNumber, int iGain, int iTriggerMode, int iExtTriggerEdge, unsigned long ulTimeOutSeconds, short* psDigitalValue);
typedef   int(__cdecl *PF_ME4000MULTISIGAICONFIG)(unsigned int uiBoardNumber, unsigned int uiAIChannelNumber, unsigned char *pucMuxChanList, unsigned int uiMuxChanListCount, unsigned long ulReserved, unsigned long ulChanTicks, unsigned long ulScanTicksLow, unsigned long ulScanTicksHigh, int iAcqMode, int iExtTriggerMode, int iExtTriggerEdge);
typedef   int(__cdecl *PF_ME4000MULTISIGAISCAN)(unsigned int uiBoardNumber, unsigned int uiNumberOfMuxLists, short* psBuffer, unsigned long ulBufferSizeValues, int iExecutionMode, ME4000_P_AI_CALLBACK_PROC pCallbackProc, void* pCallbackContext, unsigned int uiRefreshFrequency, ME4000_P_AI_TERMINATE_PROC pTerminateProc, void* pTerminateContext, unsigned long ulTimeOutSeconds);
typedef   int(__cdecl *PF_ME4000MULTISIGAICONTINUOUS)(unsigned int uiBoardNumber, ME4000_P_AI_CALLBACK_PROC pCallbackProc, void* pCallbackContext, unsigned int uiRefreshFrequency, unsigned long ulTimeOutSeconds);
typedef   int(__cdecl *PF_ME4000MULTISIGAISTART)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000MULTISIGAIGETNEWVALUES)(unsigned int uiBoardNumber, short* psBuffer, unsigned long ulNumberOfValuesToRead, int iExecutionMode, unsigned long* pulNumberOfValuesRead, int* piLastError);
typedef   int(__cdecl *PF_ME4000MULTISIGAISTOP)(unsigned int uiBoardNumber, int iReserved);
typedef   int(__cdecl *PF_ME4000MULTISIGAIEXTRACTVALUES)(unsigned int uiMuxChannelNumber, short* psAIBuffer, unsigned long ulAIDataCount, unsigned char *pucMuxChanList, unsigned int uiMuxChanListCount, short* psChanBuffer, unsigned long ulChanBufferSizeValues, unsigned long* pulChanDataCount);
typedef   int(__cdecl *PF_ME4000MULTISIGAIDIGITTOSIZE)(short sDigit, int iGain, int iModuleType, double dIMeasured, double* pdSize);
typedef   int(__cdecl *PF_ME4000MULTISIGAIRESET)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000MULTISIGAIGETSTATUS)(unsigned int uiBoardNumber, int iWaitIdle, int* piStatus);
typedef   int(__cdecl *PF_ME4000MULTISIGAICLOSE)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000MULTISIGAOOPEN)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000MULTISIGAOSINGLE)(unsigned int uiBoardNumber, unsigned int uiDemuxChannelNumber, int iTriggerMode, int iReserved, unsigned long ulReserved, short sValue);
typedef   int(__cdecl *PF_ME4000MULTISIGAOCONFIG)(unsigned int uiBoardNumber, unsigned char *pucDemuxChanList, unsigned int uiDemuxChanListCount, unsigned long ulTicks, int iTriggerMode, int iExtTriggerEdge);
typedef   int(__cdecl *PF_ME4000MULTISIGAOWRAPAROUND)(unsigned int uiBoardNumber, short* psBuffer, unsigned long ulDataCount, unsigned long ulLoops, int iExecutionMode, ME4000_P_AO_TERMINATE_PROC pTerminateProc, void* pTerminateContext, unsigned long ulTimeOutSeconds);
typedef   int(__cdecl *PF_ME4000MULTISIGAOCONTINUOUS)(unsigned int uiBoardNumber, short* psBuffer, unsigned long ulDataCount, ME4000_P_AO_CALLBACK_PROC pCallbackProc, void* pCallbackContext, unsigned long ulTimeOutSeconds, unsigned long* pulNumberOfValuesWritten);
typedef   int(__cdecl *PF_ME4000MULTISIGAOSTART)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000MULTISIGAOAPPENDNEWVALUES)(unsigned int uiBoardNumber, short* psBuffer, unsigned long ulNumberOfValuesToAppend, int iExecutionMode, unsigned long* pulNumberOfValuesAppended);
typedef   int(__cdecl *PF_ME4000MULTISIGAOSTOP)(unsigned int uiBoardNumber, int iStopMode);
typedef   int(__cdecl *PF_ME4000MULTISIGAOVOLTTODIGIT)(double dVolt, short* psDigit);
typedef   int(__cdecl *PF_ME4000MULTISIGAORESET)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME4000MULTISIGAOGETSTATUS)(unsigned int uiBoardNumber, int iWaitIdle, int* piStatus);
typedef   int(__cdecl *PF_ME4000MULTISIGAOCLOSE)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME6000ERRORSETDEFAULTPROC)(int iDefaultProcStatus);
typedef   int(__cdecl *PF_ME6000ERRORSETUSERPROC)(ME4000_P_ERROR_PROC pErrorProc);
typedef   int(__cdecl *PF_ME6000ERRORGETMESSAGE)(int iErrorCode, char* pcBuffer, unsigned int uiBufferSize);
typedef   int(__cdecl *PF_ME6000ERRORGETLASTMESSAGE)(char* pcBuffer, unsigned int uiBufferSize);
typedef   int(__cdecl *PF_ME6000GETDLLVERSION)(unsigned long* pulVersion);
typedef   int(__cdecl *PF_ME6000GETDRIVERVERSION)(unsigned long* pulVersion);
typedef   int(__cdecl *PF_ME6000FREQUENCYTOTICKS)(double dRequiredFreq, unsigned long* pulTicksLowPart, unsigned long* pulTicksHighPart, double* pdAchievedFreq);
typedef   int(__cdecl *PF_ME6000TIMETOTICKS)(double dRequiredTime, unsigned long* pulTicksLowPart, unsigned long* pulTicksHighPart, double* pdAchievedTime);
typedef   int(__cdecl *PF_ME6000GETBOARDVERSION)(unsigned int uiBoardNumber, unsigned short* pusVersion);
typedef   int(__cdecl *PF_ME6000GETSERIALNUMBER)(unsigned int uiBoardNumber, unsigned long* pulSerialNumber);
typedef   int(__cdecl *PF_ME6000AOSINGLE)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, int iTriggerMode, int iReserved, unsigned long ulReserved, short sValue );
typedef   int(__cdecl *PF_ME6000AOUPDATE)(unsigned int uiBoardNumber);
typedef   int(__cdecl *PF_ME6000AOCONFIG)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, unsigned long ulTicks, int iTriggerMode, int iExtTriggerEdge);
typedef   int(__cdecl *PF_ME6000AOWRAPAROUND)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, short* psBuffer, unsigned long ulDataCount, unsigned long ulLoops, int iExecutionMode, ME6000_P_AO_TERMINATE_PROC pTerminateProc, void* pTerminateContext, unsigned long ulTimeOutSeconds);
typedef   int(__cdecl *PF_ME6000AOCONTINUOUS)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, short* psBuffer, unsigned long ulDataCount, ME6000_P_AO_CALLBACK_PROC pCallbackProc, void* pCallbackContext, unsigned long ulTimeOutSeconds, unsigned long* pulNumberOfValuesWritten);
typedef   int(__cdecl *PF_ME6000AOSTART)(unsigned int uiBoardNumber, unsigned int uiChannelNumber);
typedef   int(__cdecl *PF_ME6000AOAPPENDNEWVALUES)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, short* psBuffer, unsigned long ulNumberOfValuesToAppend, int iExecutionMode, unsigned long* pulNumberOfValuesAppended);
typedef   int(__cdecl *PF_ME6000AOSTOP)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, int iStopMode);
typedef   int(__cdecl *PF_ME6000AOVOLTTODIGIT)(double dVolt, short* psDigit);
typedef   int(__cdecl *PF_ME6000AORESET)(unsigned int uiBoardNumber, unsigned int uiChannelNumber);
typedef   int(__cdecl *PF_ME6000AOWAVEGEN)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, int iShape, double dAmplitude, double dOffset, double dFrequency);
typedef   int(__cdecl *PF_ME6000AOGETSTATUS)(unsigned int uiBoardNumber, unsigned int uiChannelNumber, int iWaitIdle, int* piStatus);




// -------------------- Function Prototypes --------------------------------

void meOpen(void);
void meClose(void);

int me4000ErrorSetDefaultProc(
    int iDefaultProcStatus);

int me4000ErrorSetUserProc(
    ME4000_P_ERROR_PROC pErrorProc);

int me4000ErrorGetMessage(
    int iErrorCode,
    char* pcBuffer,
    unsigned int uiBufferSize);

int me4000ErrorGetLastMessage(
    char* pcBuffer,
    unsigned int uiBufferSize);

int me4000GetDLLVersion(
    unsigned long* pulVersion);

int me4000GetDriverVersion(
    unsigned long* pulVersion);

int me4000FrequencyToTicks(
    double dRequiredFreq,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedFreq);

int me4000TimeToTicks(
    double dRequiredTime,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedTime);

int me4000GetBoardVersion(
    unsigned int uiBoardNumber,
    unsigned short* pusVersion);

int me4000GetSerialNumber(
    unsigned int uiBoardNumber,
    unsigned long* pulSerialNumber);

int me4000AISingle(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iRange,
    int iSDMode,
    int iTriggerMode,
    int iExtTriggerEdge,
    unsigned long ulTimeOutSeconds,
    short* psDigitalValue);

int me4000AIMakeChannelListEntry(
    unsigned int uiChannelNumber,
    int iRange,
    unsigned char* pucChanListEntry);

int me4000AIConfig(
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

int me4000AIScan(
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

int me4000AIContinuous(
    unsigned int uiBoardNumber,
    ME4000_P_AI_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned int uiRefreshFrequency,
    unsigned long ulTimeOutSeconds);

int me4000AIStart(
    unsigned int uiBoardNumber);

int me4000AIGetNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToRead,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesRead,
    int* piLastError);

int me4000AIStop(
    unsigned int uiBoardNumber,
    int iReserved);

int me4000AIExtractValues(
    unsigned int uiChannelNumber,
    short* psAIBuffer,
    unsigned long ulAIDataCount,
    unsigned char* pucChanList,
    unsigned int uiChanListCount,
    short* psChanBuffer,
    unsigned long ulChanBufferSizeValues,
    unsigned long* pulChanDataCount);

int me4000AIDigitToVolt(
    short sDigit,
    int iRange,
    double* pdVolt);

int me4000AIReset(
    unsigned int uiBoardNumber);

int me4000AIGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus);

int me4000AOSingle(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iTriggerMode,
    int iReserved,
    unsigned long ulReserved,
    short sValue    );

int me4000AOSingleSimultaneous(
    unsigned int uiBoardNumber,
    unsigned int* puiChannelNumber,
    unsigned long ulCount,
    int iTriggerMode,
    int* piExtTriggerEnable,
    int* piExtTriggerEdge,
    unsigned long ulTimeOutSeconds,
    short* psValue);

int me4000AOUpdate(
    unsigned int uiBoardNumber);

int me4000AOConfig(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge);

int me4000AOWraparound(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME4000_P_AO_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds);

int me4000AOContinuous(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    ME4000_P_AO_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned long ulTimeOutSeconds,
    unsigned long* pulNumberOfValuesWritten);

int me4000AOStart(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber);
    
int me4000AOStartSynchronous(
    unsigned int uiBoardNumber, 
    unsigned int* puiChannelNumber, 
    unsigned long ulCount, 
    int iTriggerMode, 
    int* piExtTriggerEnable, 
    int* piExtTriggerEdge, 
    unsigned long ulTimeOutSeconds);

int me4000AOAppendNewValues(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToAppend,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesAppended);

int me4000AOStop(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iStopMode);

int me4000AOVoltToDigit(
    double dVolt,
    short* psDigit);

int me4000AOReset(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber);

int me4000AOWaveGen(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iShape,
    double dAmplitude,
    double dOffset,
    double dFrequency);

int me4000AOGetStatus(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iWaitIdle,
    int* piStatus);

int me4000DIOConfig(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    int iPortDirection);

int me4000DIOResetAll(
    unsigned int uiBoardNumber);

int me4000DIOGetBit(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned int uiBitNumber,
    int *piBitValue);

int me4000DIOGetByte(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned char *pucByteValue);

int me4000DIOSetBit(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned int uiBitNumber,
    int iBitValue);

int me4000DIOSetByte(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned char ucByteValue);

int me4000CntWrite(
    unsigned int uiBoardNumber,
    int iCounter,
    int iMode,
    unsigned short usValue);

int me4000CntRead(
    unsigned int uiBoardNumber,
    int iCounter,
    unsigned short *pusValue);

int me4000CntPWMStart(
    unsigned int uiBoardNumber,
    unsigned int uiPreScaler,
    int iDutyCycle);

int me4000CntPWMStop(
    unsigned int uiBoardNumber);

int me4000ExtIrqEnable(
    unsigned int uiBoardNumber,
    ME4000_P_EXT_IRQ_PROC pExtIrqProc,
    void* pExtIrqContext);

int me4000ExtIrqDisable(
    unsigned int uiBoardNumber);

int me4000ExtIrqGetCount(
    unsigned int uiBoardNumber,
    unsigned int *puiIrqCount);

int me4000DIOBPPortConfig(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    int iOutputMode);

int me4000DIOBPConfig(
    unsigned int uiBoardNumber,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge);

int me4000DIOBPWraparound(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME4000_P_DIOBP_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds);

int me4000DIOBPContinuous(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    ME4000_P_DIOBP_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned long ulTimeOutSeconds,
    unsigned long* pulNumberOfValuesWritten);

int me4000DIOBPStart(
    unsigned int uiBoardNumber);

int me4000DIOBPAppendNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToAppend,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesAppended);

int me4000DIOBPStop(
    unsigned int uiBoardNumber,
    int iStopMode);

int me4000DIOBPReset(
    unsigned int uiBoardNumber);

int me4000DIOBPGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus);

int me4000MultiSigOpen(
    unsigned int uiBoardNumber);

int me4000MultiSigReset(
    unsigned int uiBoardNumber);

int me4000MultiSigAddressLED(
    unsigned int uiBoardNumber,
    unsigned int uiBase,
    int iLEDStatus);

int me4000MultiSigSetGain(
    unsigned int uiBoardNumber,
    unsigned int uiBase,
    int iChannelGroup,
    int iGain);

int me4000MultiSigClose(
    unsigned int uiBoardNumber);

int me4000MultiSigAIOpen(
    unsigned int uiBoardNumber);

int me4000MultiSigAISingle(
    unsigned int uiBoardNumber,
    unsigned int uiAIChannelNumber,
    unsigned int uiMuxChannelNumber,
    int iGain,
    int iTriggerMode,
    int iExtTriggerEdge,
    unsigned long ulTimeOutSeconds,
    short* psDigitalValue);

int me4000MultiSigAIConfig(
    unsigned int uiBoardNumber,
    unsigned int uiAIChannelNumber,
    unsigned char *pucMuxChanList,
    unsigned int uiMuxChanListCount,
    unsigned long ulReserved,
    unsigned long ulChanTicks,
    unsigned long ulScanTicksLow,
    unsigned long ulScanTicksHigh,
    int iAcqMode,
    int iExtTriggerMode,
    int iExtTriggerEdge);

int me4000MultiSigAIScan(
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

int me4000MultiSigAIContinuous(
    unsigned int uiBoardNumber,
    ME4000_P_AI_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned int uiRefreshFrequency,
    unsigned long ulTimeOutSeconds);

int me4000MultiSigAIStart(
    unsigned int uiBoardNumber);

int me4000MultiSigAIGetNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToRead,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesRead,
    int* piLastError);

int me4000MultiSigAIStop(
    unsigned int uiBoardNumber,
    int iReserved);

int me4000MultiSigAIExtractValues(
    unsigned int uiMuxChannelNumber,
    short* psAIBuffer,
    unsigned long ulAIDataCount,
    unsigned char *pucMuxChanList,
    unsigned int uiMuxChanListCount,
    short* psChanBuffer,
    unsigned long ulChanBufferSizeValues,
    unsigned long* pulChanDataCount);

int me4000MultiSigAIDigitToSize(
    short sDigit,
    int iGain,
    int iModuleType,
    double dIMeasured,
    double* pdSize);

int me4000MultiSigAIReset(
    unsigned int uiBoardNumber);

int me4000MultiSigAIGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus);

int me4000MultiSigAIClose(
    unsigned int uiBoardNumber);

int me4000MultiSigAOOpen(
    unsigned int uiBoardNumber);

int me4000MultiSigAOSingle(
    unsigned int uiBoardNumber,
    unsigned int uiDemuxChannelNumber,
    int iTriggerMode,
    int iReserved,
    unsigned long ulReserved,
    short sValue);

int me4000MultiSigAOConfig(
    unsigned int uiBoardNumber,
    unsigned char *pucDemuxChanList,
    unsigned int uiDemuxChanListCount,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge);

int me4000MultiSigAOWraparound(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME4000_P_AO_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds);

int me4000MultiSigAOContinuous(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    ME4000_P_AO_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned long ulTimeOutSeconds,
    unsigned long* pulNumberOfValuesWritten);

int me4000MultiSigAOStart(
    unsigned int uiBoardNumber);

int me4000MultiSigAOAppendNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToAppend,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesAppended);

int me4000MultiSigAOStop(
    unsigned int uiBoardNumber,
    int iStopMode);

int me4000MultiSigAOVoltToDigit(
    double dVolt,
    short* psDigit);

int me4000MultiSigAOReset(
    unsigned int uiBoardNumber);

int me4000MultiSigAOGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus);

int me4000MultiSigAOClose(
    unsigned int uiBoardNumber);

int me6000ErrorSetDefaultProc(
    int iDefaultProcStatus);

int me6000ErrorSetUserProc(
    ME4000_P_ERROR_PROC pErrorProc);

int me6000ErrorGetMessage(
    int iErrorCode,
    char* pcBuffer,
    unsigned int uiBufferSize);

int me6000ErrorGetLastMessage(
    char* pcBuffer,
    unsigned int uiBufferSize);

int me6000GetDLLVersion(
    unsigned long* pulVersion);

int me6000GetDriverVersion(
    unsigned long* pulVersion);

int me6000FrequencyToTicks(
    double dRequiredFreq,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedFreq);

int me6000TimeToTicks(
    double dRequiredTime,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedTime);

int me6000GetBoardVersion(
    unsigned int uiBoardNumber,
    unsigned short* pusVersion);

int me6000GetSerialNumber(
    unsigned int uiBoardNumber,
    unsigned long* pulSerialNumber);

int me6000AOSingle(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iTriggerMode,
    int iReserved,
    unsigned long ulReserved,
    short sValue    );

int me6000AOUpdate(
    unsigned int uiBoardNumber);

int me6000AOConfig(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge);

int me6000AOWraparound(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME6000_P_AO_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds);

int me6000AOContinuous(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    ME6000_P_AO_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned long ulTimeOutSeconds,
    unsigned long* pulNumberOfValuesWritten);

int me6000AOStart(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber);

int me6000AOAppendNewValues(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToAppend,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesAppended);

int me6000AOStop(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iStopMode);

int me6000AOVoltToDigit(
    double dVolt,
    short* psDigit);

int me6000AOReset(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber);

int me6000AOWaveGen(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iShape,
    double dAmplitude,
    double dOffset,
    double dFrequency);

int me6000AOGetStatus(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iWaitIdle,
    int* piStatus);

#endif
