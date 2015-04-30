/*------------------------------------------------------------------------------+
|   Source File:    defs.h                                                      |
|   Destination:    me4000 - SYS WDM and VxD drivers, API-DLL and other         |
|                   applications                                                |
|   Compiler:       Visual C++ 6.0                                              |
|   Authors:        KRH (Keith Hartley), SW (Stefan Weidlich),                  |
|                   AB(Andreas Bernau)                                          |
|   Copyright       (c) 1997-2002  Meilhaus Electronic GmbH                     |
|                                                                               |
|   Description:    Common header file providing #defines to be used in DLL or  |
|                   applications which are connected to the 32-Bit driver       |
|                   running on Windows                                          |
|                                                                               |
|  File History:    Version     Date        Editor  Action                      |
+-------------------------------------------------------------------------------+
|                   1.00.00     020826      KRH     Original version            |
|                                                                               |
+-------------------------------------------------------------------------------+
|                                                                               |
|   Description:                                                                |
|                                                                               |
|       A number of defines and structures which are used both in user mode     |
|       and in kernel mode for all operating systems and are also required by   |
|       the user calling functions in the DLL interface.                        |
|                                                                               |
|       This file contains:                                                     |
|                                                                               |
|           1.  A define for the maximum number of boards which can be          |
|               operated simultaneously. At present 32.                         |
|                                                                               |
+------------------------------------------------------------------------------*/


#ifndef DEFS_H
#define DEFS_H

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
|                              General #defines                                 |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Maximum number of boards supported
#define ME4000_MAX_DEVICES                          32

// Define for the return value from an API function that is executed 
// successfully
#define ME4000_NO_ERROR                             0x00000000

// Define for a scalar parameter which is reserved or not used in a particular
// context
#define ME4000_VALUE_NOT_USED						0

// Define for a pointer or callback-function parameter which is reserved or not 
// used in a particular context
#define ME4000_POINTER_NOT_USED						NULL

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        #defines for Error Routines                            |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

#define ME4000_ERROR_DEFAULT_PROC_ENABLE			0x00010101
#define ME4000_ERROR_DEFAULT_PROC_DISABLE			0x00010102

// Typedef for general API error procedure - used in me4000SetErrorFunction 
typedef void (_stdcall * ME4000_P_ERROR_PROC)(char* pcFunctionName, int iErrorCode);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        #defines for AI Routines                               |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Acquisition modes for me4000AIConfig - Parameter iAcqMode 
#define ME4000_AI_ACQ_MODE_SOFTWARE                 0x00020101  // Continous sampling with software start 
#define ME4000_AI_ACQ_MODE_EXT                      0x00020102  // Continous sampling with external trigger start
#define ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE         0x00020103  // Sample one value for each external trigger
#define ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST      0x00020104  // Sample one channel for each external trigger

// Input range for me4000AISingle, me4000AIMakeChannelListEntry 
// and me4000AIDigitToVolt - Parameter iRange
#define ME4000_AI_RANGE_BIPOLAR_10                  0x00020201
#define ME4000_AI_RANGE_BIPOLAR_2_5                 0x00020202
#define ME4000_AI_RANGE_UNIPOLAR_10                 0x00020203
#define ME4000_AI_RANGE_UNIPOLAR_2_5                0x00020204

// Input mode for me4000AISingle and me4000AIConfig -
// Parameter iSDMode
#define ME4000_AI_INPUT_SINGLE_ENDED                0x00020301
#define ME4000_AI_INPUT_DIFFERENTIAL                0x00020302

// Trigger mode for me4000AISingle - Parameter iTriggerMode
// Last two 'defines' - external trigger mode for 
// me4000AIConfig - Parameter iExtTriggerMode
#define ME4000_AI_TRIGGER_SOFTWARE                  0x00020401
#define ME4000_AI_TRIGGER_EXT_DIGITAL               0x00020402
#define ME4000_AI_TRIGGER_EXT_ANALOG                0x00020403

// External trigger flank type for me4000AISingle and 
// me4000AIConfig - Parameter iExtTriggerEdge
#define ME4000_AI_TRIGGER_EXT_EDGE_RISING           0x00020501
#define ME4000_AI_TRIGGER_EXT_EDGE_FALLING          0x00020502
#define ME4000_AI_TRIGGER_EXT_EDGE_BOTH             0x00020503

// Simultaneous data acquisition off/on for meAIConfig
// - Parameter iSimultaneous
#define ME4000_AI_SIMULTANEOUS_DISABLE              0x00020601
#define ME4000_AI_SIMULTANEOUS_ENABLE               0x00020602

// Execution mode for me4000AIScan - Parameter iExecutionMode
#define ME4000_AI_SCAN_BLOCKING                     0x00020701
#define ME4000_AI_SCAN_ASYNCHRONOUS                 0x00020702

// Execution mode for me4000AIGetNewNewValues - Parameter iExecutionMode
#define ME4000_AI_GET_NEW_VALUES_BLOCKING           0x00020801
#define ME4000_AI_GET_NEW_VALUES_NON_BLOCKING       0x00020802

// Wait modus for me4000AIGetStatus - Parameter iWaitIdle
#define ME4000_AI_WAIT_IDLE							0x00020901
#define ME4000_AI_WAIT_NONE							0x00020902

// Return status for me4000AIGetStatus - Parameter piStatus
#define ME4000_AI_STATUS_IDLE                       0x00020A01
#define ME4000_AI_STATUS_BUSY                       0x00020A02

// Typedef for AI callback function - used in me4000AIScan and 
// me4000AIContinuous 
typedef void (_stdcall * ME4000_P_AI_CALLBACK_PROC)(short* psValues, 
														unsigned int uiNumberOfValues, 
																	void* pCallbackContext, 
																				int iLastError);

// Typedef for AI terminate function - used in me4000AIScan 
typedef void (_stdcall * ME4000_P_AI_TERMINATE_PROC)(short* psValues, 
														unsigned int uiNumberOfValues, 
																	void* pTerminateContext, 
																				int iLastError);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        #defines for AO Routines                               |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Trigger mode for me4000AOSingle, me4000AOSingleSimultaneous, me4000AOConfig 
// and me4000AOStartSynchronous.
//
// IMPORTANT NOTE:	The value 0x00030102 is skipped here for reasons of 
//					compatibility - see ME4000_AO_TRIGGER_SOFTWARE_SIMULTANEOUS
//					below	
#define ME4000_AO_TRIGGER_SOFTWARE			0x00030101
#define ME4000_AO_TRIGGER_EXT_DIGITAL		0x00030103

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// NOTE:	The following constants are obsolete and are retained only for 
//			backward compatibility. They should no longer be used.
#define ME4000_AO_TRIGGER_SOFTWARE_TRANSPARENT      0x00030101  // For ...AOSingle only
#define ME4000_AO_TRIGGER_SOFTWARE_SIMULTANEOUS     0x00030102
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// External trigger flank type for me4000AOSingle, me4000AOSingleSimultaneous, 
// me4000AOConfig and me4000AOStartSynchronous.
#define ME4000_AO_TRIGGER_EXT_EDGE_RISING           0x00030201
#define ME4000_AO_TRIGGER_EXT_EDGE_FALLING          0x00030202
#define ME4000_AO_TRIGGER_EXT_EDGE_BOTH				0x00030203

// Execution mode for me4000AOWraparound - Parameter iExecutionMode
#define ME4000_AO_WRAPAROUND_BLOCKING               0x00030301
#define ME4000_AO_WRAPAROUND_ASYNCHRONOUS           0x00030302

// #define for an infinite (endless) execution for me4000AOWraparound - 
// Parameter ulLoops
#define ME4000_AO_WRAPAROUND_INFINITE               0x00

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// NOTE:	The following constant is obsolete and is retained only for 
//			backward compatibility. It should no longer be used.

// #define for the Parameter uiChannelNumber in me4000AOStart to start those 
// AO channels simultaneously which have been configured with 
// ME4000_AO_TRIGGER_SOFTWARE_SIMULTANEOUS for the parameter iTriggerMode in 
// me4000AOConfig
#define ME4000_AO_SIMULTANEOUS_CHANNELS             0x0F
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// Execution mode for me4000AOAppendNewValues - Parameter iExecutionMode
#define ME4000_AO_APPEND_NEW_VALUES_BLOCKING        0x00030401
#define ME4000_AO_APPEND_NEW_VALUES_NON_BLOCKING    0x00030402

// Wait modus for me4000AOGetStatus - Parameter iWaitIdle
#define ME4000_AO_WAIT_IDLE							0x00030501
#define ME4000_AO_WAIT_NONE							0x00030502

// Return status for me4000AOGetStatus - Parameter piStatus
#define ME4000_AO_STATUS_IDLE                       0x00030601
#define ME4000_AO_STATUS_BUSY                       0x00030602

// Stop mode for me4000AOStop - Parameter iStopMode
#define ME4000_AO_STOP_MODE_LAST_VALUE              0x00030701
#define ME4000_AO_STOP_MODE_IMMEDIATE               0x00030702

// Signal forms for the function me4000AOWaveGen - Parameter iShape
#define ME4000_AO_SHAPE_RECTANGLE                   0x00030801
#define ME4000_AO_SHAPE_TRIANGLE                    0x00030802
#define ME4000_AO_SHAPE_SINUS                       0x00030803
#define ME4000_AO_SHAPE_COSINUS                     0x00030804
#define ME4000_AO_SHAPE_POS_RAMP                    0x00030805
#define ME4000_AO_SHAPE_NEG_RAMP                    0x00030806

// Trigger Enable/Disable for the array piExtTriggerEnable in
// me4000AOSingleSimultaneous and me4000AOStartSynchronous.
#define ME4000_AO_TRIGGER_EXT_DISABLE				0x00030901
#define ME4000_AO_TRIGGER_EXT_ENABLE				0x00030902

// Typedef for AO terminate function - used in me4000AOWraparound
typedef void (_stdcall * ME4000_P_AO_TERMINATE_PROC)(void* pTerminateContext);

// Typedef for AO callback function - used in me4000AOContinuous
typedef void (_stdcall * ME4000_P_AO_CALLBACK_PROC)(unsigned long ulBufferAvailable, 
																void* pCallbackContext);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        #defines for DIO Routines                              |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Defines for port numbers
#define ME4000_DIO_PORT_A                           0
#define ME4000_DIO_PORT_B                           1
#define ME4000_DIO_PORT_C                           2
#define ME4000_DIO_PORT_D                           3                           

// Port direction for me4000DIOConfig - Parameter iDir
#define ME4000_DIO_PORT_INPUT                       0x00040201
#define ME4000_DIO_PORT_OUTPUT                      0x00040202


/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                       Defines for counter Routines                            |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Mode for me4000CntWrite - Parameter iMode
#define ME4000_CNT_MODE_0                           0x00050101
#define ME4000_CNT_MODE_1                           0x00050102
#define ME4000_CNT_MODE_2                           0x00050103
#define ME4000_CNT_MODE_3                           0x00050104
#define ME4000_CNT_MODE_4                           0x00050105
#define ME4000_CNT_MODE_5                           0x00050106

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                 Defines for external interrupt Routines                       |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Typedef for external interrupt callback routine used in me4000ExtIrqEnable
typedef void (_stdcall * ME4000_P_EXT_IRQ_PROC)(void* pExtIrqContext);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|             #defines for DIO Bit Pattern Routines                             |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Defines for port numbers
#define ME4000_DIOBP_PORT_A                         0
#define ME4000_DIOBP_PORT_B                         1
#define ME4000_DIOBP_PORT_C                         2
#define ME4000_DIOBP_PORT_D                         3

// Output mode for me4000DIOBPPortConfig - Parameter iOutputMode
#define ME4000_DIOBP_OUTPUT_MODE_BYTE_LOW           0x00060101
#define ME4000_DIOBP_OUTPUT_MODE_BYTE_HIGH          0x00060102

// Trigger mode for me4000DIOBPAOConfig - Parameter iTriggerMode
#define ME4000_DIOBP_TRIGGER_SOFTWARE               0x00060201  
#define ME4000_DIOBP_TRIGGER_EXT_DIGITAL            0x00060202       

// External trigger flank type for me4000DIOBPAOConfig - Parameter 
// iExtTriggerEdge
#define ME4000_DIOBP_TRIGGER_EXT_EDGE_RISING        0x00060301
#define ME4000_DIOBP_TRIGGER_EXT_EDGE_FALLING       0x00060302
#define ME4000_DIOBP_TRIGGER_EXT_EDGE_BOTH			0x00060303

// Execution mode for me4000DIOBPWraparound - Parameter iExecutionMode
#define ME4000_DIOBP_WRAPAROUND_BLOCKING            0x00060401
#define ME4000_DIOBP_WRAPAROUND_ASYNCHRONOUS        0x00060402

// #define for an infinite (endless) execution for me4000DIOBPWraparound - 
// Parameter ulLoops
#define ME4000_DIOBP_WRAPAROUND_INFINITE            0x00

// Execution mode for me4000DIOBPAppendNewValues - Parameter iExecutionMode
#define ME4000_DIOBP_APPEND_NEW_VALUES_BLOCKING     0x00060501
#define ME4000_DIOBP_APPEND_NEW_VALUES_NON_BLOCKING 0x00060502

// Wait modus for me4000DIOBPGetStatus - Parameter iWaitIdle
#define ME4000_DIOBP_WAIT_IDLE						0x00060601
#define ME4000_DIOBP_WAIT_NONE						0x00060602

// Return status for me4000DIOBPGetStatus - Parameter piStatus
#define ME4000_DIOBP_STATUS_IDLE                    0x00060701
#define ME4000_DIOBP_STATUS_BUSY                    0x00060702

// Stop mode for me4000DIOBPStop - Parameter iStopMode
#define ME4000_DIOBP_STOP_MODE_LAST_VALUE           0x00060801
#define ME4000_DIOBP_STOP_MODE_IMMEDIATE            0x00060802

// Typedef for DIO BP terminate function - used in me4000DIOBPWraparound
typedef void (_stdcall * ME4000_P_DIOBP_TERMINATE_PROC)(void* pTerminateContext);

// Typedef for DIO BP callback function - used in me4000DIOBPContinuous
typedef void (_stdcall * ME4000_P_DIOBP_CALLBACK_PROC)(unsigned long ulBufferAvailable, 
																	void* pCallbackContext);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|              #defines specifically for MultiSig routines                      |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// LED status for me4000MultiSigAddressLED - Parameter iLEDStatus
#define ME4000_MULTISIG_LED_OFF                     0x00070101
#define ME4000_MULTISIG_LED_ON                      0x00070102

// Channel group for me4000MultiSigSetGain - Parameter iChannelGroup
#define ME4000_MULTISIG_GROUP_A                     0x00070201
#define ME4000_MULTISIG_GROUP_B                     0x00070202

// Gain for me4000MultiSigSetGain and me4000MultiSigAIDigitToSize - 
// Parameter iGain
#define ME4000_MULTISIG_GAIN_1                      0x00070301
#define ME4000_MULTISIG_GAIN_10                     0x00070302
#define ME4000_MULTISIG_GAIN_100                    0x00070303

// Module type for me4000MultiSigAIDigitToSize - Parameter iModuleType
#define ME4000_MULTISIG_MODULE_NONE                 0x00070401
#define ME4000_MULTISIG_MODULE_DIFF16_10V           0x00070402
#define ME4000_MULTISIG_MODULE_DIFF16_20V           0x00070403
#define ME4000_MULTISIG_MODULE_DIFF16_50V           0x00070404
#define ME4000_MULTISIG_MODULE_CURRENT16_0_20MA     0x00070405
#define ME4000_MULTISIG_MODULE_RTD8_PT100           0x00070406
#define ME4000_MULTISIG_MODULE_RTD8_PT500           0x00070407
#define ME4000_MULTISIG_MODULE_RTD8_PT1000          0x00070408

#define ME4000_MULTISIG_MODULE_TE8_TYPE_B			0x00070409
#define ME4000_MULTISIG_MODULE_TE8_TYPE_E			0x0007040A
#define ME4000_MULTISIG_MODULE_TE8_TYPE_J			0x0007040B
#define ME4000_MULTISIG_MODULE_TE8_TYPE_K			0x0007040C
#define ME4000_MULTISIG_MODULE_TE8_TYPE_N			0x0007040D
#define ME4000_MULTISIG_MODULE_TE8_TYPE_R			0x0007040E
#define ME4000_MULTISIG_MODULE_TE8_TYPE_S			0x0007040F
#define ME4000_MULTISIG_MODULE_TE8_TYPE_T			0x00070410

#define ME4000_MULTISIG_MODULE_TE8_TYPE_SENSOR		0x00070411

// Module type for me4000MultiSigAIDigitToSize - Parameter iModuleType
// 500 Milliampere
#define ME4000_MULTISIG_I_MEASURED_DEFAULT          0.0005  


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
|                              General #defines                                 |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Maximum number of boards supported
#define ME6000_MAX_DEVICES                          32

// Define for the return value from an API function that is executed 
// successfully
#define ME6000_NO_ERROR                             0x00000000              

// Define for a scalar parameter which is reserved or not used in a particular
// context
#define ME6000_VALUE_NOT_USED						0

// Define for a pointer or callback-function parameter which is reserved or not 
// used in a particular context
#define ME6000_POINTER_NOT_USED						NULL

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        #defines for Error Routines                            |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

#define ME6000_ERROR_DEFAULT_PROC_ENABLE			0x00010101
#define ME6000_ERROR_DEFAULT_PROC_DISABLE			0x00010102

// Typedef for general API error procedure - used in me6000SetErrorFunction 
typedef void (_stdcall * ME6000_P_ERROR_PROC)(char* pcFunctionName, int iErrorCode);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        #defines for AO Routines                               |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Trigger mode for me6000AOSingle, me6000AOSingleSimultaneous, me6000AOConfig 
// and me6000AOStartSynchronous.
//
// IMPORTANT NOTE:	The value 0x00030102 is skipped here for reasons of 
//					compatibility - see ME6000_AO_TRIGGER_SOFTWARE_SIMULTANEOUS
//					below	
#define ME6000_AO_TRIGGER_SOFTWARE			0x00030101
#define ME6000_AO_TRIGGER_EXT_DIGITAL		0x00030103

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// NOTE:	The following constants are obsolete and are retained only for 
//			backward compatibility. They should no longer be used.
#define ME6000_AO_TRIGGER_SOFTWARE_TRANSPARENT      0x00030101  // For ...AOSingle only
#define ME6000_AO_TRIGGER_SOFTWARE_SIMULTANEOUS     0x00030102
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// External trigger flank type for me6000AOSingle, me6000AOSingleSimultaneous, 
// me6000AOConfig and me6000AOStartSynchronous.
#define ME6000_AO_TRIGGER_EXT_EDGE_RISING           0x00030201
#define ME6000_AO_TRIGGER_EXT_EDGE_FALLING          0x00030202
#define ME6000_AO_TRIGGER_EXT_EDGE_BOTH				0x00030203

// Execution mode for me6000AOWraparound - Parameter iExecutionMode
#define ME6000_AO_WRAPAROUND_BLOCKING               0x00030301
#define ME6000_AO_WRAPAROUND_ASYNCHRONOUS           0x00030302

// #define for an infinite (endless) execution for me6000AOWraparound - 
// Parameter ulLoops
#define ME6000_AO_WRAPAROUND_INFINITE               0x00

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// NOTE:	The following constant is obsolete and is retained only for 
//			backward compatibility. It should no longer be used.

// #define for the Parameter uiChannelNumber in me6000AOStart to start those 
// AO channels simultaneously which have been configured with 
// ME6000_AO_TRIGGER_SOFTWARE_SIMULTANEOUS for the parameter iTriggerMode in 
// me6000AOConfig
#define ME6000_AO_SIMULTANEOUS_CHANNELS             0x0F
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// Execution mode for me6000AOAppendNewValues - Parameter iExecutionMode
#define ME6000_AO_APPEND_NEW_VALUES_BLOCKING        0x00030401
#define ME6000_AO_APPEND_NEW_VALUES_NON_BLOCKING    0x00030402

// Wait modus for me6000AOGetStatus - Parameter iWaitIdle
#define ME6000_AO_WAIT_IDLE							0x00030501
#define ME6000_AO_WAIT_NONE							0x00030502

// Return status for me6000AOGetStatus - Parameter piStatus
#define ME6000_AO_STATUS_IDLE                       0x00030601
#define ME6000_AO_STATUS_BUSY                       0x00030602

// Stop mode for me6000AOStop - Parameter iStopMode
#define ME6000_AO_STOP_MODE_LAST_VALUE              0x00030701
#define ME6000_AO_STOP_MODE_IMMEDIATE               0x00030702

// Signal forms for the function me6000AOWaveGen - Parameter iShape
#define ME6000_AO_SHAPE_RECTANGLE                   0x00030801
#define ME6000_AO_SHAPE_TRIANGLE                    0x00030802
#define ME6000_AO_SHAPE_SINUS                       0x00030803
#define ME6000_AO_SHAPE_COSINUS                     0x00030804
#define ME6000_AO_SHAPE_POS_RAMP                    0x00030805
#define ME6000_AO_SHAPE_NEG_RAMP                    0x00030806

// Trigger Enable/Disable for the array piExtTriggerEnable in
// me6000AOSingleSimultaneous and me6000AOStartSynchronous.
#define ME6000_AO_TRIGGER_EXT_DISABLE				0x00030901
#define ME6000_AO_TRIGGER_EXT_ENABLE				0x00030902

// Typedef for AO terminate function - used in me6000AOWraparound
typedef void (_stdcall * ME6000_P_AO_TERMINATE_PROC)(void* pTerminateContext);

// Typedef for AO callback function - used in me6000AOContinuous
typedef void (_stdcall * ME6000_P_AO_CALLBACK_PROC)(unsigned long ulBufferAvailable, 
																void* pCallbackContext);



#endif
