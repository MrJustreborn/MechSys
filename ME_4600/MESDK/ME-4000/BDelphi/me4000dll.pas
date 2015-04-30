unit me4000dll;

interface

uses me4000defs;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Version Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

function me4000GetDLLVersion(var pulVersion: LongWord): Integer;
  cdecl; external 'me4000.dll';

function me4000GetDriverVersion(var pulVersion: LongWord): Integer;
  cdecl; external 'me4000.dll';

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Utility Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

function me4000FrequencyToTicks(dRequiredFreq: Double;
  var pulTicksLowPart: LongWord; var pulTicksHighPart: LongWord;
  var pdAchievedFreq: Double): Integer; cdecl; external 'me4000.dll';

function me4000TimeToTicks(dRequiredTime: Double;
  var pulTicksLowPart: LongWord; var pulTicksHighPart: LongWord;
  var pdAchievedTime: Double): Integer; cdecl; external 'me4000.dll';


{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                         Board Specific Routines                               |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Error Routines                                  |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

function me4000ErrorSetDefaultProc(iDefaultProcStatus: Integer): Integer;
  cdecl; external 'me4000.dll';

function me4000ErrorSetUserProc(pErrorProc: TME4000_P_ERROR_PROC): Integer;
  cdecl; external 'me4000.dll';

function me4000ErrorGetMessage(iErrorCode: Integer;
  pcBuffer: PChar; uiBufferSize: Word): Integer; cdecl; external 'me4000.dll';

function me4000ErrorGetLastMessage(pcBuffer: PChar;
  uiBufferSize: Word): Integer; cdecl; external 'me4000.dll';


{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            General Routines                                   |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

function me4000GetBoardVersion(uiBoardNumber: Cardinal;
  var pusVersion: Word): Integer; cdecl; external 'me4000.dll';

function me4000GetSerialNumber(uiBoardNumber: Cardinal;
  var pulSerialNumber: LongWord): Integer; cdecl; external 'me4000.dll';

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               AI Routines                                     |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

function me4000AISingle(uiBoardNumber: Cardinal; uiChannelNumber: Cardinal;
  iRange: Integer; iSDMode: Integer; iTriggerMode: Integer;
  iExtTriggerEdge: Integer; ulTimeOutSeconds: LongWord;
  var psDigitalValue: Smallint): Integer; cdecl; external 'me4000.dll';

function me4000AIMakeChannelListEntry(uiChannelNumber: Cardinal; iRange: Integer;
  var pucChanListEntry: Byte): Integer; cdecl; external 'me4000.dll';

function me4000AIConfig(uiBoardNumber: Cardinal; pucChanList: PByte;
  uiChanListCount: Cardinal; iSDMode: Integer; iSimultaneous: Integer;
  ulReserved: LongWord; ulChanTicks: LongWord; ulScanTicksLow: LongWord;
  ulScanTicksHigh: LongWord; iAcqMode: Integer; iExtTriggerMode: Integer;
  iExtTriggerEdge: Integer): Integer; cdecl; external 'me4000.dll';

function me4000AIScan(uiBoardNumber: Cardinal; uiNumberOfChanLists: Cardinal;
  psBuffer: PSmallint; ulBufferSizeValues: LongWord;
  iExecutionMode: Integer; pCallbackProc: TME4000_P_AI_CALLBACK_PROC;
  pCallbackContext: Pointer; uiRefreshFrequency: Cardinal;
  pTerminateProc: TME4000_P_AI_TERMINATE_PROC; pTerminateContext: Pointer;
  ulTimeOutSeconds: LongWord): Integer; cdecl; external 'me4000.dll';

function me4000AIContinuous(uiBoardNumber: Cardinal;
  pCallbackProc: TME4000_P_AI_CALLBACK_PROC; pCallbackContext: Pointer;
  uiRefreshFrequency: Cardinal; ulTimeOutSeconds: LongWord): Integer;
  cdecl; external 'me4000.dll';

function me4000AIStart(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000AIGetNewValues(uiBoardNumber: Cardinal;
  psBuffer: PSmallint; ulNumberOfValuesToRead: LongWord;
  iExecutionMode: Integer; var pulNumberOfValuesRead: LongWord;
  var piLastError: Integer): Integer; cdecl; external 'me4000.dll';

function me4000AIStop(uiBoardNumber: Cardinal;
  iReserved: Integer): Integer; cdecl; external 'me4000.dll';

function me4000AIExtractValues(uiChannelNumber: Cardinal;
  psAIBuffer: PSmallint; ulAIDataCount: LongWord; pucChanList: PByte;
  uiChanListCount: Cardinal; psChanBuffer: PSmallint;
  ulChanBufferSizeValues: LongWord; var pulChanDataCount: LongWord): Integer;
  cdecl; external 'me4000.dll';

function me4000AIDigitToVolt(sDigit: Smallint; iRange: Integer;
  var pdVolt: Double): Integer; cdecl; external 'me4000.dll';

function me4000AIReset(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

{*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               AO Routines                                     |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*}

function me4000AOSingle(uiBoardNumber: Cardinal;
  uiChannelNumber: Cardinal; iTriggerMode: Integer;
  iExtTriggerEdge: Integer; ulTimeOutSeconds: LongWord;
  sValue: Smallint): Integer; cdecl; external 'me4000.dll';

function me4000AOSingleSimultaneous(uiBoardNumber: Cardinal;
  puiChannelNumber: PCardinal; ulCount: LongWord;
  iTriggerMode: Integer; piExtTriggerEnable: PInteger;
  piExtTriggerEdge: PInteger; ulTimeOutSeconds: LongWord;
  psValue: PSmallint): Integer; cdecl; external 'me4000.dll';

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// NOTE:	The following function is obsolete and is retained only for
//		backward compatibility. It should no longer be used.
function me4000AOUpdate(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

function me4000AOConfig(uiBoardNumber: Cardinal; uiChannelNumber: Cardinal;
  ulTicks: LongWord; iTriggerMode: Integer;
  iExtTriggerEdge: Integer): Integer; cdecl; external 'me4000.dll';

function me4000AOWraparound(uiBoardNumber: Cardinal; uiChannelNumber: Cardinal;
  psBuffer: PSmallint; ulDataCount: LongWord; ulLoops: LongWord;
  iExecutionMode: Integer; pTerminateProc: TME4000_P_AO_TERMINATE_PROC;
  pTerminateContext: Pointer; ulTimeOutSeconds: LongWord): Integer;
  cdecl; external 'me4000.dll';

function me4000AOContinuous(uiBoardNumber: Cardinal; uiChannelNumber: Cardinal;
  psBuffer: PSmallint; ulDataCount: LongWord;
  pCallbackProc: TME4000_P_AO_CALLBACK_PROC; pCallbackContext: Pointer;
  ulTimeOutSeconds: LongWord; var pulNumberOfValuesWritten: LongWord): Integer;
  cdecl; external 'me4000.dll';

function me4000AOStart(uiBoardNumber: Cardinal; uiChannelNumber: Cardinal):
  Integer; cdecl; external 'me4000.dll';

function me4000AOStartSynchronous(uiBoardNumber: Cardinal;
  puiChannelNumber: PCardinal; ulCount: LongWord;
  iTriggerMode: Integer; piExtTriggerEnable: PInteger;
  piExtTriggerEdge: PInteger; ulTimeOutSeconds: longWord): Integer;
  cdecl; external 'me4000.dll';

function me4000AOAppendNewValues(uiBoardNumber: Cardinal;
  uiChannelNumber: Cardinal; psBuffer: PSmallint;
  ulNumberOfValuesToAppend: LongWord; iExecutionMode: Integer;
  var pulNumberOfValuesAppended: LongWord): Integer;
  cdecl; external 'me4000.dll';

function me4000AOStop(uiBoardNumber: Cardinal; uiChannelNumber: Cardinal;
  iStopMode: Integer): Integer; cdecl; external 'me4000.dll';

function me4000AOVoltToDigit(dVolt: Double; var psDigit: Smallint): Integer;
  cdecl; external 'me4000.dll';

function me4000AOReset(uiBoardNumber: Cardinal; uiChannelNumber: Cardinal):
  Integer; cdecl; external 'me4000.dll';

function me4000AOWaveGen(uiBoardNumber: Cardinal; uiChannelNumber: Cardinal;
  iShape: Integer; dAmplitude: Double; dOffset: Double;
  dFrequency: Double): Integer; cdecl; external 'me4000.dll';

function me4000AOGetStatus(uiBoardNumber: Cardinal; uiChannelNumber: Cardinal;
  iWaitIdle: Integer; var piStatus: Integer): Integer;
  cdecl; external 'me4000.dll';

{*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               DIO Routines                                    |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*}

function me4000DIOConfig(uiBoardNumber: Cardinal; uiPortNumber: Cardinal;
  iPortDirection: Integer): Integer; cdecl; external 'me4000.dll';

function me4000DIOResetAll(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000DIOGetBit(uiBoardNumber: Cardinal; uiPortNumber: Cardinal;
  uiBitNumber: Cardinal; var piBitValue: Integer): Integer;
  cdecl; external 'me4000.dll';

function me4000DIOGetByte(uiBoardNumber: Cardinal; uiPortNumber: cardinal;
  var pucByteValue: Byte): Integer; cdecl; external 'me4000.dll';

function me4000DIOSetBit(uiBoardNumber: Cardinal;  uiPortNumber: Cardinal;
  uiBitNumber: Cardinal; iBitValue: Integer): Integer;
  cdecl; external 'me4000.dll';

function me4000DIOSetByte(uiBoardNumber: Cardinal;  uiPortNumber: Cardinal;
    ucByteValue: Byte): Integer; cdecl; external 'me4000.dll';

{*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            Counter Routines                                   |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*}

function me4000CntWrite(uiBoardNumber: Cardinal; uiCounterNumber: Cardinal;
  iMode: Integer; usValue: Word): Integer; cdecl; external 'me4000.dll';

function me4000CntRead(uiBoardNumber: Cardinal; uiCounterNumber: Cardinal;
    var pusValue: Word): Integer; cdecl; external 'me4000.dll';

function me4000CntPWMStart(uiBoardNumber: Cardinal; uiPreScaler: Cardinal;
  iDutyCycle: Integer): Integer; cdecl; external 'me4000.dll';

function me4000CntPWMStop(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

{*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                         External interrupt Routines                           |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*}

function me4000ExtIrqEnable(uiBoardNumber: Cardinal;
  pExtIrqProc: TME4000_P_EXT_IRQ_PROC; pExtIrqContext: Pointer): Integer;
  cdecl; external 'me4000.dll';

function me4000ExtIrqDisable(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000ExtIrqGetCount(uiBoardNumber: Cardinal;
  var puiIrqCount: LongWord): Integer; cdecl; external 'me4000.dll';

{*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                       DIO Bit Pattern Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*}

function me4000DIOBPPortConfig(uiBoardNumber: Cardinal; uiPortNumber: Cardinal;
  iOutputMode: Integer): Integer; cdecl; external 'me4000.dll';

function me4000DIOBPConfig(uiBoardNumber: Cardinal; ulTicks: LongWord;
  iTriggerMode: Integer; iExtTriggerEdge: Integer): Integer;
  cdecl; external 'me4000.dll';

function me4000DIOBPWraparound(uiBoardNumber: Cardinal;
  psBuffer: PSmallint; ulDataCount: LongWord; ulLoops: LongWord;
  iExecutionMode: Integer; pTerminateProc: TME4000_P_AO_TERMINATE_PROC;
  pTerminateContext: Pointer; ulTimeOutSeconds: LongWord): Integer;
  cdecl; external 'me4000.dll';

function me4000DIOBPContinuous(uiBoardNumber: Cardinal; psBuffer: PSmallint;
  ulDataCount: LongWord; pCallbackProc: TME4000_P_AO_CALLBACK_PROC;
  pCallbackContext: Pointer; ulTimeOutSeconds: LongWord;
  var pulNumberOfValuesWritten: LongWord): Integer; cdecl; external 'me4000.dll';

function me4000DIOBPStart(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000DIOBPAppendNewValues(uiBoardNumber: Cardinal; psBuffer: PSmallint;
  ulNumberOfValuesToAppend: LongWord; iExecutionMode: Integer;
  var pulNumberOfValuesAppended: LongWord): Integer; cdecl; external 'me4000.dll';

function me4000DIOBPStop(uiBoardNumber: Cardinal; iStopMode: Integer): Integer;
  cdecl; external 'me4000.dll';

function me4000DIOBPReset(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000DIOBPGetStatus(uiBoardNumber: Cardinal; iWaitIdle: Integer;
  var piStatus: Integer): Integer; cdecl; external 'me4000.dll';

{*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            MultiSig Routines                                  |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*}

function me4000MultiSigOpen(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigReset(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAddressLED(uiBoardNumber: Cardinal; uiBase: Cardinal;
  iLEDStatus: Integer): Integer; cdecl; external 'me4000.dll';

function me4000MultiSigSetGain(uiBoardNumber: Cardinal; uiBase: Cardinal;
  iChannelGroup: Integer; iGain: Integer): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigClose(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

{*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            MultiSigAI Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*}

function me4000MultiSigAIOpen(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAISingle(uiBoardNumber: Cardinal;
  uiAIChannelNumber: Cardinal; uiMuxChannelNumber: Cardinal;
  iGain: Integer; iTriggerMode: Integer; iExtTriggerEdge: Integer;
  ulTimeOutSeconds: LongWord; var psDigitalValue: Smallint): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAIConfig(uiBoardNumber: Cardinal;
  uiAIChannelNumber: Cardinal; pucMuxChanList: PByte;
  uiMuxChanListCount: Cardinal; ulReserved: LongWord; ulChanTicks: LongWord;
  ulScanTicksLow: LongWord; ulScanTicksHigh: LongWord; iAcqMode: Integer;
  iExtTriggerMode: Integer; iExtTriggerEdge: Integer): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAIScan(uiBoardNumber: Cardinal;
  uiNumberOfMuxLists: Cardinal; psBuffer: PSmallint;
  ulBufferSizeValues: LongWord; iExecutionMode: Integer;
  pCallbackProc: TME4000_P_AI_CALLBACK_PROC; pCallbackContext: Pointer;
  uiRefreshFrequency: Cardinal; pTerminateProc: TME4000_P_AI_TERMINATE_PROC;
  pTerminateContext: Pointer; ulTimeOutSeconds: LongWord): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAIContinuous(uiBoardNumber: Cardinal;
  pCallbackProc: TME4000_P_AI_CALLBACK_PROC; pCallbackContext: Pointer;
  uiRefreshFrequency: Cardinal; ulTimeOutSeconds: LongWord): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAIStart(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAIGetNewValues(uiBoardNumber: Cardinal;
  psBuffer: PSmallint; ulNumberOfValuesToRead: LongWord; iExecutionMode: Integer;
  var pulNumberOfValuesRead: LongWord; var piLastError: Integer): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAIStop(uiBoardNumber: Cardinal;
  iReserved: Integer): Integer; cdecl; external 'me4000.dll';

function me4000MultiSigAIExtractValues(uiMuxChannelNumber: cardinal;
  psAIBuffer: PSmallint; ulAIDataCount: LongWord; pucMuxChanList: PByte;
  uiMuxChanListCount: Cardinal; psChanBuffer: PSmallint;
  ulChanBufferSizeValues: LongWord; var pulChanDataCount: LongWord): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAIDigitToSize(sDigit: Smallint; iGain: Integer;
  iModuleType: Integer; dIMeasured: Double; var pdSize: Double): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAIReset(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAIGetStatus(uiBoardNumber: Cardinal; iWaitIdle: Integer;
var piStatus: Integer): Integer; cdecl; external 'me4000.dll';

function me4000MultiSigAIClose(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

{*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            MultiSigAO Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*}

function me4000MultiSigAOOpen(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAOSingle(uiBoardNumber: Cardinal;
  uiDemuxChannelNumber: cardinal; iTriggerMode: Integer;
  iExtTriggerEdge: Integer; ulTimeOutSeconds: LongWord;
  sValue: Smallint): Integer; cdecl; external 'me4000.dll';

function me4000MultiSigAOConfig(uiBoardNumber: Cardinal;
  pucDemuxChanList: PByte; uiDemuxChanListCount: Cardinal; ulTicks: LongWord;
  iTriggerMode: Integer; iExtTriggerEdge: Integer): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAOWraparound(uiBoardNumber: Cardinal; psBuffer: PSmallint;
  ulDataCount: LongWord; ulLoops: LongWord; iExecutionMode: Integer;
  pTerminateProc: TME4000_P_AO_TERMINATE_PROC; pTerminateContext: Pointer;
  ulTimeOutSeconds: LongWord): Integer; cdecl; external 'me4000.dll';

function me4000MultiSigAOContinuous(uiBoardNumber: Cardinal; psBuffer: PSmallint;
  ulDataCount: LongWord; pCallbackProc: TME4000_P_AO_CALLBACK_PROC;
  pCallbackContext: Pointer; ulTimeOutSeconds: LongWord;
  var pulNumberOfValuesWritten: LongWord): Integer; cdecl; external 'me4000.dll';

function me4000MultiSigAOStart(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAOAppendNewValues(uiBoardNumber: Cardinal;
  psBuffer: PSmallint; ulNumberOfValuesToAppend: LongWord; iExecutionMode: Integer;
  var pulNumberOfValuesAppended: LongWord): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAOStop(uiBoardNumber: Cardinal;
  iStopMode: Integer): Integer; cdecl; external 'me4000.dll';

function me4000MultiSigAOVoltToDigit(dVolt: Double; var
  psDigit: Smallint): Integer; cdecl; external 'me4000.dll';

function me4000MultiSigAOReset(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

function me4000MultiSigAOGetStatus(uiBoardNumber: Cardinal; iWaitIdle: Integer;
  var piStatus: Integer): Integer; cdecl; external 'me4000.dll';

function me4000MultiSigAOClose(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me4000.dll';

implementation

end.
