
{-------------------------------------------------------------------------------+
|   Source File:    defs.h                                                      |
|   Destination:    me4000 - SYS WDM and VxD drivers, API-DLL and other         |
|                   applications                                                |
|   Compiler:       Visual C++ 6.0                                              |
|   Authors:        KRH (Keith Hartley), SW (Stefan Weidlich),                  |
|                   AB(Andreas Bernau)                                          |
|   Copyright       (c) 1997-2002  Meilhaus Electronic GmbH                     |
|                                                                               |
|   Description:    Common header file providing consts to be used in DLL or  |
|                   applications which are connected to the 32-Bit driver       |
|                   running on Windows                                          |
|                                                                               |
|  File History:    Version     Date        Editor  Action                      |
+-------------------------------------------------------------------------------+
|                   1.00.00     020826      KRH     Original version            |
|                                                                               |
+-------------------------------------------------------------------------------+
|                                                                               |
|                                                                               |
+-------------------------------------------------------------------------------}

unit me4000defs;

interface

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                             ME4000 Interface                                  |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                              General consts                                 |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}


// Maximum number of boards supported
const ME4000_MAX_DEVICES = 32;

// Define for the return value from an API function that is executed
// successfully
const ME4000_NO_ERROR = $00000000;

// Define for a scalar parameter which is reserved or not used in a particular
// context
const ME4000_VALUE_NOT_USED = 0;

// Define for a pointer or callback-function parameter which is reserved or not
// used in a particular context
const ME4000_POINTER_NOT_USED = nil;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        consts for Error Routines                              |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

const ME4000_ERROR_DEFAULT_PROC_ENABLE	= $00010101;
const ME4000_ERROR_DEFAULT_PROC_DISABLE	= $00010102;

// Typedef for general API error procedure - used in me4000SetErrorFunction
type TME4000_P_ERROR_PROC =
  procedure (pcFunctionName: PChar; iErrorCode: Integer); stdcall;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        consts for AI Routines                                 |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

// Acquisition modes for me4000AIConfig - Parameter iAcqMode 
const ME4000_AI_ACQ_MODE_SOFTWARE            = $00020101;  // Continous sampling with software start
const ME4000_AI_ACQ_MODE_EXT                 = $00020102;  // Continous sampling with external trigger start
const ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE    = $00020103;  // Sample one value for each external trigger
const ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST = $00020104;  // Sample one channel for each external trigger

// Input range for me4000AISingle, me4000AIMakeChannelListEntry 
// and me4000AIDigitToVolt - Parameter iRange
const ME4000_AI_RANGE_BIPOLAR_10   = $00020201;
const ME4000_AI_RANGE_BIPOLAR_2_5  = $00020202;
const ME4000_AI_RANGE_UNIPOLAR_10  = $00020203;
const ME4000_AI_RANGE_UNIPOLAR_2_5 = $00020204;

// Input mode for me4000AISingle and me4000AIConfig -
// Parameter iSDMode
const ME4000_AI_INPUT_SINGLE_ENDED = $00020301;
const ME4000_AI_INPUT_DIFFERENTIAL = $00020302;

// Trigger mode for me4000AISingle - Parameter iTriggerMode
// Last two 'defines' - external trigger mode for 
// me4000AIConfig - Parameter iExtTriggerMode
const ME4000_AI_TRIGGER_SOFTWARE    = $00020401;
const ME4000_AI_TRIGGER_EXT_DIGITAL = $00020402;
const ME4000_AI_TRIGGER_EXT_ANALOG  = $00020403;

// External trigger flank type for me4000AISingle and 
// me4000AIConfig - Parameter iExtTriggerEdge
const ME4000_AI_TRIGGER_EXT_EDGE_RISING  = $00020501;
const ME4000_AI_TRIGGER_EXT_EDGE_FALLING = $00020502;
const ME4000_AI_TRIGGER_EXT_EDGE_BOTH    = $00020503;

// Simultaneous data acquisition off/on for meAIConfig
// - Parameter iSimultaneous
const ME4000_AI_SIMULTANEOUS_DISABLE = $00020601;
const ME4000_AI_SIMULTANEOUS_ENABLE  = $00020602;

// Execution mode for me4000AIScan - Parameter iExecutionMode
const ME4000_AI_SCAN_BLOCKING     = $00020701;
const ME4000_AI_SCAN_ASYNCHRONOUS = $00020702;

// Execution mode for me4000AIGetNewNewValues - Parameter iExecutionMode
const ME4000_AI_GET_NEW_VALUES_BLOCKING     = $00020801;
const ME4000_AI_GET_NEW_VALUES_NON_BLOCKING = $00020802;

// Wait modus for me4000AIGetStatus - Parameter iWaitIdle
const ME4000_AI_WAIT_IDLE = $00020901;
const ME4000_AI_WAIT_NONE =	$00020902;

// Return status for me4000AIGetStatus - Parameter piStatus
const ME4000_AI_STATUS_IDLE = $00020A01;
const ME4000_AI_STATUS_BUSY = $00020A02;

// Typedef for AI callback function - used in me4000AIScan and
// me4000AIContinuous
type TME4000_P_AI_CALLBACK_PROC =
  procedure (psValues: Pointer; uiNumberOfValues: Cardinal;
			   pCallbackContext: Pointer; iLastError: Integer); stdcall;

// Typedef for AI terminate function - used in me4000AIScan
type TME4000_P_AI_TERMINATE_PROC =
  procedure (psValues: Pointer; uiNumberOfValues: Cardinal;
               pTerminateContext: Pointer; iLastError: Integer); stdcall;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        consts for AO Routines                                 |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

// Trigger mode for me4000AOSingle, me4000AOSingleSimultaneous, me4000AOConfig 
// and me4000AOStartSynchronous.
//
// IMPORTANT NOTE: The value 0x00030102 is skipped here for reasons of
//		   compatibility - see ME4000_AO_TRIGGER_SOFTWARE_SIMULTANEOUS
//		   below
const ME4000_AO_TRIGGER_SOFTWARE              = $00030101;
const ME4000_AO_TRIGGER_EXT_DIGITAL           = $00030103;  
                                                                

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// NOTE:	The following constants are obsolete and are retained only for 
//			backward compatibility. They should no longer be used.
const ME4000_AO_TRIGGER_SOFTWARE_TRANSPARENT  = $00030101; // For ...AOSingle only
const ME4000_AO_TRIGGER_SOFTWARE_SIMULTANEOUS = $00030102;
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// External trigger flank type for me4000AOConfig - Parameter iExtTriggerEdge
const ME4000_AO_TRIGGER_EXT_EDGE_RISING  = $00030201;
const ME4000_AO_TRIGGER_EXT_EDGE_FALLING = $00030202;
const ME4000_AO_TRIGGER_EXT_EDGE_BOTH	 = $00030203;

// Execution mode for me4000AOWraparound - Parameter iExecutionMode
const ME4000_AO_WRAPAROUND_BLOCKING     = $00030301;
const ME4000_AO_WRAPAROUND_ASYNCHRONOUS = $00030302;

// const for an infinite (endless) execution for me4000AOWraparound -
// Parameter ulLoops
const ME4000_AO_WRAPAROUND_INFINITE = $00;

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// NOTE:	The following constant is obsolete and is retained only for 
//			backward compatibility. It should no longer be used.

// #define for the Parameter uiChannelNumber in me4000AOStart to start those 
// AO channels simultaneously which have been configured with 
// ME4000_AO_TRIGGER_SOFTWARE_SIMULTANEOUS for the parameter iTriggerMode in 
// me4000AOConfig
const ME4000_AO_SIMULTANEOUS_CHANNELS = $0F;
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


// Execution mode for me4000AOAppendNewValues - Parameter iExecutionMode
const ME4000_AO_APPEND_NEW_VALUES_BLOCKING     = $00030401;
const ME4000_AO_APPEND_NEW_VALUES_NON_BLOCKING = $00030402;

// Wait modus for me4000AOGetStatus - Parameter iWaitIdle
const ME4000_AO_WAIT_IDLE =	$00030501;
const ME4000_AO_WAIT_NONE = $00030502;

// Return status for me4000AOGetStatus - Parameter piStatus
const ME4000_AO_STATUS_IDLE = $00030601;
const ME4000_AO_STATUS_BUSY = $00030602;

// Stop mode for me4000AOStop - Parameter iStopMode
const ME4000_AO_STOP_MODE_LAST_VALUE = $00030701;
const ME4000_AO_STOP_MODE_IMMEDIATE  = $00030702;

// Signal forms for the function ME4000AOWaveGen - Parameter iShape
const ME4000_AO_SHAPE_RECTANGLE = $00030801;
const ME4000_AO_SHAPE_TRIANGLE  = $00030802;
const ME4000_AO_SHAPE_SINUS     = $00030803;
const ME4000_AO_SHAPE_COSINUS   = $00030804;
const ME4000_AO_SHAPE_POS_RAMP  = $00030805;
const ME4000_AO_SHAPE_NEG_RAMP  = $00030806;

// Trigger Enable/Disable for the array piExtTriggerEnable in
// me4000AOSingleSimultaneous and me4000AOStartSynchronous.
const ME4000_AO_TRIGGER_EXT_DISABLE	= $00030901;
const ME4000_AO_TRIGGER_EXT_ENABLE	= $00030902;

// Typedef for AO terminate function - used in me4000AOWraparound
type TME4000_P_AO_TERMINATE_PROC =
  procedure (pTerminateContext: Pointer); stdcall;

// Typedef for AO callback function - used in me4000AOContinuous
type TME4000_P_AO_CALLBACK_PROC =
  procedure (ulBufferAvailable: LongWord; pCallbackContext: Pointer); stdcall;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        consts for DIO Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

// Defines for port numbers
const ME4000_DIO_PORT_A = 0;
const ME4000_DIO_PORT_B = 1;
const ME4000_DIO_PORT_C = 2;
const ME4000_DIO_PORT_D = 3;

// Port direction for me4000DIOConfig - Parameter iDir
const ME4000_DIO_PORT_INPUT  = $00040201;
const ME4000_DIO_PORT_OUTPUT = $00040202;


{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                       consts for counter Routines                             |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

// Mode for me4000CntWrite - Parameter iMode
const ME4000_CNT_MODE_0 = $00050101;
const ME4000_CNT_MODE_1 = $00050102;
const ME4000_CNT_MODE_2 = $00050103;
const ME4000_CNT_MODE_3 = $00050104;
const ME4000_CNT_MODE_4 = $00050105;
const ME4000_CNT_MODE_5 = $00050106;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                 Defines for external interrupt Routines                       |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

// Typedef for external interrupt callback routine used in me4000ExtIrqEnable
type TME4000_P_EXT_IRQ_PROC =
  procedure (pExtIrqContext: Pointer); stdcall;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|             consts for DIO Bit Pattern Routines                               |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

// Defines for port numbers
const ME4000_DIOBP_PORT_A = 0;
const ME4000_DIOBP_PORT_B = 1;
const ME4000_DIOBP_PORT_C = 2;
const ME4000_DIOBP_PORT_D = 3;

// Output mode for me4000DIOBPPortConfig - Parameter iOutputMode
const ME4000_DIOBP_OUTPUT_MODE_BYTE_LOW  = $00060101;
const ME4000_DIOBP_OUTPUT_MODE_BYTE_HIGH = $00060102;

// Trigger mode for me4000DIOBPAOConfig - Parameter iTriggerMode
const ME4000_DIOBP_TRIGGER_SOFTWARE    = $00060201;
const ME4000_DIOBP_TRIGGER_EXT_DIGITAL = $00060202;

// External trigger flank type for me4000DIOBPAOConfig - Parameter 
// iExtTriggerEdge
const ME4000_DIOBP_TRIGGER_EXT_EDGE_RISING  = $00060301;
const ME4000_DIOBP_TRIGGER_EXT_EDGE_FALLING = $00060302;
const ME4000_DIOBP_TRIGGER_EXT_EDGE_BOTH    = $00060303;

// Execution mode for me4000DIOBPWraparound - Parameter iExecutionMode
const ME4000_DIOBP_WRAPAROUND_BLOCKING     = $00060401;
const ME4000_DIOBP_WRAPAROUND_ASYNCHRONOUS = $00060402;

// const for an infinite (endless) execution for me4000DIOBPWraparound - 
// Parameter ulLoops
const ME4000_DIOBP_WRAPAROUND_INFINITE = $00;

// Execution mode for me4000DIOBPAppendNewValues - Parameter iExecutionMode
const ME4000_DIOBP_APPEND_NEW_VALUES_BLOCKING     = $00060501;
const ME4000_DIOBP_APPEND_NEW_VALUES_NON_BLOCKING = $00060502;

// Wait modus for me4000DIOBPGetStatus - Parameter iWaitIdle
const ME4000_DIOBP_WAIT_IDLE = $00060601;
const ME4000_DIOBP_WAIT_NONE = $00060602;

// Return status for me4000DIOBPGetStatus - Parameter piStatus
const ME4000_DIOBP_STATUS_IDLE = $00060701;
const ME4000_DIOBP_STATUS_BUSY = $00060702;

// Stop mode for me4000DIOBPStop - Parameter iStopMode
const ME4000_DIOBP_STOP_MODE_LAST_VALUE = $00060801;
const ME4000_DIOBP_STOP_MODE_IMMEDIATE  = $00060802;

// Typedef for DIO BP terminate function - used in me4000DIOBPWraparound
type TME4000_P_DIOBP_TERMINATE_PROC =
  procedure (pTerminateContext: Pointer); stdcall;

// Typedef for DIO BP callback function - used in me4000DIOBPContinuous
type TME4000_P_DIOBP_CALLBACK_PROC =
  procedure (ulBufferAvailable: LongWord; pCallbackContext: Pointer); stdcall;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|              consts specifically for MultiSig routines                        |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

// LED status for me4000MultiSigAddressLED - Parameter iLEDStatus
const ME4000_MULTISIG_LED_OFF = $00070101;
const ME4000_MULTISIG_LED_ON  = $00070102;

// Channel group for me4000MultiSigSetGain - Parameter iChannelGroup
const ME4000_MULTISIG_GROUP_A = $00070201;
const ME4000_MULTISIG_GROUP_B = $00070202;

// Gain for me4000MultiSigSetGain and me4000MultiSigAIDigitToSize - 
// Parameter iGain
const ME4000_MULTISIG_GAIN_1   = $00070301;
const ME4000_MULTISIG_GAIN_10  = $00070302;
const ME4000_MULTISIG_GAIN_100 = $00070303;

// Module type for me4000MultiSigAIDigitToSize - Parameter iModuleType
const ME4000_MULTISIG_MODULE_NONE             = $00070401;
const ME4000_MULTISIG_MODULE_DIFF16_10V       = $00070402;
const ME4000_MULTISIG_MODULE_DIFF16_20V       = $00070403;
const ME4000_MULTISIG_MODULE_DIFF16_50V       = $00070404;
const ME4000_MULTISIG_MODULE_CURRENT16_0_20MA = $00070405;
const ME4000_MULTISIG_MODULE_RTD8_PT100       = $00070406;
const ME4000_MULTISIG_MODULE_RTD8_PT500       = $00070407;
const ME4000_MULTISIG_MODULE_RTD8_PT1000      = $00070408;

// Module type for me4000MultiSigAIDigitToSize - Parameter iModuleType
// 500 Milliampere
const ME4000_MULTISIG_I_MEASURED_DEFAULT = 0.0005;

implementation

end.
