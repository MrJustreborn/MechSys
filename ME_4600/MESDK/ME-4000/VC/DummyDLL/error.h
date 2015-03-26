/*------------------------------------------------------------------------------+
|	Source File:	error.h                                                     |
|	Destination:	me4000 - SYS WDM and VxD drivers, API-DLL					|
|	Compiler:		Visual C++ 6.0                                              |
|	Authors:		KRH (Keith Hartley), SW (Stefan Weidlich),                  |
|					AB(Andreas Bernau)											|
|	Copyright		(c) 1997-2002  Meilhaus Electronic GmbH                     |
|                                                                               |
|	Description:	Common header file providing #defines for the errors which  |
|                   can occur in kernel or user-mode                            |
|                                                                               |
|  File History:	Version		Date		Editor	Action                      |
+-------------------------------------------------------------------------------+
|					1.00.00     020826      KRH     Original version			|
|                                                                               |
+-------------------------------------------------------------------------------+
|                                                                               |
|	Description:                                                                |
|                                                                               |
|       Contains #defines for all the error codes used in the drivers and in	|                                                                               |
|       the API-DLL.                                                            |
|                                                                               |
+------------------------------------------------------------------------------*/

/*

	The error codes are 32 bit values constructed as follows:

	0x # # # # # # # #
       | | | | | | | | 
       | | | +-+-+-+-+--->	Error identifier (Bits 0-19)
       | | | 
       | | | 
	   | | +------------->  Parameter causing the error (Bits 20-23):
	   | |
	   | |					0			- Unspecified
	   | |					1, 2, 3,...	- Parameter number
	   | |
	   | |
	   | +--------------->  Error level (Bits 24-27):
	   |
	   |					1 - Warning (questionable use of function etc.)
	   |					2 - Caller error (incorrect parameter etc.)
	   |					3 - System error (not enough resources etc.)
	   |					4 - Hardware error (download failed etc.)
	   |					5 - Internal error (error in program logic etc.)
	   |
	   |
	   +----------------->	Where the error occurred (Bits 28-31):
							
							1 - In the API DLL (user-mode)
							2 - In the driver (kernel-mode)

*/

// Following defines are based on the above structure

// macro to retrieve the ID from an error code

#define GetErrorID(error)	(error) & 0x000FFFFF

// macro to retrieve the parameter from an error code

#define GetErrorParameter(error)	( (error) & 0x00F00000 ) >> 20

// macro to set parameter in an error code

#define SetErrorParameter(error, parameter)	\
						(error)&= ~0x00F00000;	\
						(error)|= ( (parameter) << 20 )

// macro to increment the parameter in an error code

#define IncrementErrorParameter(error)	\
	if( (error)&0x00F00000 ) error+= 0x00100000

// Error levels

#define ERROR_LEVEL_WARNING				0x01000000
#define ERROR_LEVEL_CALLER				0x02000000
#define ERROR_LEVEL_SYSTEM				0x03000000
#define ERROR_LEVEL_HARDWARE			0x04000000
#define ERROR_LEVEL_INTERNAL			0x05000000

// macro to retrieve the error level from an error code

#define GetErrorLevel(error)	( (error) & 0x0F000000 )

// Macro to set error level in an error code
// 'level' should be one of the defines ERROR_LEVEL_.. above

#define SetErrorLevel(error, level)	(error)|= (level)

// Error locations

#define ERROR_LOCATION_DLL				0x10000000
#define ERROR_LOCATION_KERNEL			0x20000000

// Macro to set error location in an error code
// 'location' should be one of the defines ERROR_LOCATION_.. above

#define SetErrorLocation(error, location)	(error)|= (location)

// Function carried out successfully
#define ME_ERROR_NONE												0x00000000		

// General error codes
// -------------------
// -------------------

// Unspecified error
#define ME_ERROR_UNSPECIFIED										0x00000001
	
// No boards of this type in the system
#define ME_ERROR_NO_BOARD_FOUND										0x00000002

// The board with this particular index is not present in the system
#define ME_ERROR_BOARD_NOT_PRESENT									0x00000003

// A pointer passed was not valid - Could not be read/written in the required 
// length
#define ME_ERROR_BAD_POINTER										0x00000004

// A buffer passed was not large enough
#define ME_ERROR_BUFFER_TOO_SMALL									0x00000005

// The requested function is not supported, or not supported in this form 
// (inspect parameter number)
#define ME_ERROR_UNSUPPORTED										0x00000006

// A parameter was not in the required range (inspect parameter number)
#define ME_ERROR_PARAMETER_OUT_OF_RANGE								0x00000007

// DeviceIoControl was called with an IOCTL code which the driver did not 
// recognise (different versions of DLL and driver?) - internal error
#define ME_ERROR_IOCTL_CODE_UNKNOWN									0x00000008

// The size of the input buffer to DeviceIoControl was smaller than expected
// (different versions of DLL and driver?) - internal error
#define ME_ERROR_IOCTL_INPUT_BUFFER_TOO_SMALL						0x00000009

// The size of the output buffer to DeviceIoControl was smaller than expected
// (different versions of DLL and driver?) - internal error
#define ME_ERROR_IOCTL_OUTPUT_BUFFER_TOO_SMALL						0x0000000A

// An internal thread could not be started - system error
#define ME_ERROR_CANNOT_CREATE_THREAD								0x0000000B

// An internal buffer could not be allocated - system error 
#define ME_ERROR_CANNOT_ALLOCATE_DATA_BUFFER						0x0000000C

// The event handle passed by the DLL to the kernel in DeviceIoControl,
// IOCTL_ME_AI_START was invalid - System error in kernel
#define ME_ERROR_INVALID_USER_EVENT_HANDLE							0x0000000D		

// The user buffer passed by the  DLL to the kernel in DeviceIoControl,
// IOCTL_ME_AI_START could not be mapped and locked - System error in kernel
#define ME_ERROR_UNABLE_TO_MAP_AND_LOCK_USER_BUFFER					0x0000000E	
		
// An operation timed out before it could run to compeltion - This may be an
// error or a warning (if the user has explicitly provided a time-out), and 
// may occur in the kernel or in the DLL. 
#define ME_ERROR_OPERATION_TIMED_OUT								0x0000000F	
		
// A reserved parameter was given a non-zero value - warning
#define ME_ERROR_RESERVED_PARAMETER_SHOULD_BE_ZERO					0x00000010	
		
// Error function error codes
// --------------------------
// --------------------------

// The parameter iDefaultProcStatus for the routine me4000ErrorSetDefaultProc
// was invalid
#define ME_ERROR_ERROR_INVALID_DEFAULT_ERROR_PROC_STATUS			0x00001000	
		
// AI specific error codes
// -----------------------
// -----------------------

// An AI channel number was invalid (for any board)  
#define ME_ERROR_AI_INVALID_CHANNEL									0x00002000

// An AI single-ended channel number was invalid for this board 
#define ME_ERROR_AI_INVALID_SINGLE_ENDED_CHANNEL					0x00002001

// An AI differential channel number was invalid for this board
#define ME_ERROR_AI_INVALID_DIFFERENTIAL_CHANNEL					0x00002002

// An AI input range was invalid - not one of ME4000_AI_BIPOLAR_10, 
// ME4000_AI_BIPOLAR_2_5, ME4000_AI_UNIPOLAR_10 or ME4000_AI_UNIPOLAR_2_5
#define ME_ERROR_AI_INVALID_RANGE									0x00002003

// An AI input range was invalid for a differential channel - neither 
// ME4000_AI_BIPOLAR_10 nor ME4000_AI_BIPOLAR_2_5
#define ME_ERROR_AI_INVALID_DIFFERENTIAL_RANGE						0x00002004

// An AI channel mode was invalid - neither ME4000_AI_INPUT_SINGLE_ENDED nor 
// ME4000_AI_INPUT_DIFFERENTIAL
#define ME_ERROR_AI_INVALID_INPUT_MODE								0x00002005

// The channel list was not well-formed - individual channels not 
// equidistant - Warning.
#define ME_ERROR_AI_CHAN_LIST_INCORRECT								0x00002006

// The acquisition mode for me4000AIConfig was not one of 
// ME4000_AI_ACQ_MODE_SOFTWARE, ME4000_AI_ACQ_MODE_EXT, 
// ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE or ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST
#define ME_ERROR_AI_INVALID_ACQ_MODE								0x00002007

// The trigger mode for me4000AISingle was not one of 
// ME4000_AI_TRIGGER_SOFTWARE, ME4000_AI_TRIGGER_EXT_DIGITAL or 
// ME4000_AI_TRIGGER_EXT_ANALOG
#define ME_ERROR_AI_INVALID_TRIGGER_MODE							0x00002008

// The trigger mode for me4000AIConfig with an acquisition triggered by an 
// external trigger (iAcqMode = ME4000_AI_ACQ_MODE_EXT, 
// ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE or ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST)
// was not one of ME4000_AI_TRIGGER_EXT_DIGITAL or ME4000_AI_TRIGGER_EXT_ANALOG
#define ME_ERROR_AI_INVALID_EXT_TRIGGER_MODE						0x00002009

// The external trigger edge for me4000AISingle or me4000AIConfig was not one of
// ME4000_AI_TRIGGER_EXT_EDGE_RISING, ME4000_AI_TRIGGER_EXT_EDGE_FALLING or 
// ME4000_AI_TRIGGER_EXT_BOTH
#define ME_ERROR_AI_INVALID_EXT_TRIGGER_EDGE						0x0000200A

// The simultaneous mode for AIConfig was neither AI4000_AI_SIMULTANEOUS_DISABLE,
// AI4000_AI_SIMULTANEOUS_ENABLE
#define ME_ERROR_AI_INVALID_SIMULTANEOUS_MODE						0x0000200B

// In AIConfig in simultaneous mode, none of the first eight channels may appear
// more than once in the channel list.
#define ME_ERROR_AI_SIMULTANEOUS_ENABLE_CHANNEL_REPEAT				0x0000200C

// In AIConfig in simultaneous mode, differential input is not allowed.
#define ME_ERROR_AI_SIMULTANEOUS_ENABLE_AND_DIFFERENTIAL			0x0000200D

// AISingle is being used without an external trigger and this parameter will 
// be ignored, it should be set to 0 - Warning
// (inspect parameter number)
#define ME_ERROR_AI_SINGLE_SW_TRIGGER_PARAMETER_IGNORED				0x0000200E

// AIConfig is being called with an aquisition mode which does not require an 
// external trigger and this parameter will be ignored, it should be set to 0 
// - Warning (inspect parameter number)
#define ME_ERROR_AI_CONFIG_SW_TRIGGER_PARAMETER_IGNORED				0x0000200F

// AIConfig is being called with a mode which samples a single value or a single
// channel list at each external trigger. The ScanTime parameter is not required 
// and will be ignored. 
// It should be set to 0 - Warning (inspect parameter number)
#define ME_ERROR_AI_CONFIG_EXT_TRIGGER_TIMER_PARAMETER_IGNORED		0x00002010

// AIConfig is being called with a scan time smaller than that required by the 
// requested chan time. Minimum scan time = Number of channels * chan time + 66
#define ME_ERROR_AI_INSUFFICIENT_SCAN_TIME							0x00002011

// One of the routines AIScan, AIContinuous or AIStart is being called before
// AIConfig has been called AT LEAST ONCE
#define ME_ERROR_AI_HW_NOT_CONFIGURED								0x00002012

// AIStart is being called before one of AIScan or AIContinuous has been called 
// AT LEAST ONCE
#define ME_ERROR_AI_SW_NOT_CONFIGURED								0x00002013

// In AIScan or AIContinuous a callback routine is NULL. The corresponding 
// context pointer will be ignored and should also be set to NULL - Warning
// (inspect parameter number)
#define ME_ERROR_AI_CALLBACK_CONTEXT_PARAMETER_IGNORED				0x00002014

// The execution mode for AIScan was neither ME4000_AI_SCAN_ASYNCHRONOUS nor
// ME4000_AI_SCAN_BLOCKING OR the execution mode for AIGetNewValues was neither
// ME4000_AI_GET_NEW_VALUES_BLOCKING nor ME4000_AI_GET_NEW_VALUES_NON_BLOCKING
#define ME_ERROR_AI_INVALID_EXECUTION_MODE							0x00002015

// An AI acquisition is currently active. This function cannot be executed until
// the current AI operation has been terminated
#define ME_ERROR_AI_BUSY											0x00002016

// AIStop has been called to terminate an AI operation, but no AI operation is
// currently running - Warning
#define ME_ERROR_AI_NOT_BUSY										0x00002017

// The iWaitIdle parameter for AIGetStatus was neither ME4000_AI_WAIT_IDLE nor 
// ME4000_AI_WAIT_NONE
#define ME_ERROR_AI_INVALID_WAIT									0x00002018

// The AI FIFO overflowed - Hardware error
#define ME_ERROR_AI_FIFO_OVERFLOW									0x00002019

// In the AI callback function, or on calling AIGetNewValues, the new data
// counter values are smaller than the old values - Internal error
#define ME_ERROR_AI_DATA_COUNTER_INCONSISTENCY						0x0000201A

// In the AI callback function, or on calling AIGetNewValues, some data has been
// overwritten before it could be transferred. This happens if the callback
// function takes too long to execute or if AIGetNewValues is not called 
//frequently enough or with a buffer which is too small - System error
#define ME_ERROR_AI_DATA_BUFFER_OVERFLOW							0x0000201B

// AIExtractValues was called with a channel number which was not found in the
// channel list supplied 
#define ME_ERROR_AI_CHANNEL_NOT_CONTAINED_IN_CHANLIST				0x0000201C

// AO specific error codes
// -----------------------
// -----------------------

// An AO channel number was invalid   
#define ME_ERROR_AO_INVALID_CHANNEL									0x00003000

// The execution mode for AOWraparound was neither ME4000_AO_WRAPAROUND_BLOCKING
// nor ME4000_AO_WRAPAROUND_ASYNCHRONOUS OR
// the execution mode for AOAppendNewValues was neither 
// ME4000_AO_APPEND_NEW_VALUES_BLOCKING nor 
// ME4000_AO_APPEND_NEW_VALUES_NON_BLOCKING
#define ME_ERROR_AO_INVALID_EXECUTION_MODE							0x00003001

// The trigger mode for AOSingle, AOSingleSimultaneous, AOConfig or 
// AOStartSynchronous was neither ME4000_AO_TRIGGER_SOFTWARE nor 
// ME4000_AO_TRIGGER_EXT_DIGITAL
#define ME_ERROR_AO_INVALID_TRIGGER_MODE							0x00003002

// The external trigger edge for AOSingle, AOSingleSimultaneous, AOConfig or 
// AOStartSynchronous was not one of ME4000_AO_TRIGGER_EXT_EDGE_RISING, 
// ME4000_AO_TRIGGER_EXT_EDGE_FALLING or ME_AO_TRIGGER_EXT_EDGE_BOTH
#define ME_ERROR_AO_INVALID_EXT_TRIGGER_EDGE						0x00003003

// The parameter ExtTriggerEnable for one of the channels in AOSingleSimultaneous
// or AOStartSynchronous was neither ME4000_AO_TRIGGER_EXT_DISABLE nor
// ME4000_AO_TRIGGER_EXT_ENABLE
#define ME_ERROR_AO_INVALID_EXT_TRIGGER_STATUS						0x00003004

// AOSingle, AOSingleSimultaneous, AOConfig or AOStartSynchronous is being used 
// without an external trigger and this parameter will be ignored, it should be 
// set to 0 - Warning (inspect parameter number)
#define ME_ERROR_AO_SW_TRIGGER_PARAMETER_IGNORED					0x00003005

// AOSingle has been called with an external trigger for a channel which does
// not have a trigger line
#define ME_ERROR_AO_SINGLE_NO_TRIGGER_LINE							0x00003006

// AOSingleSimultaneous or AOStartSynchronous is being called with an external
// trigger, but in the list of channels passed to the function there is none
// with a trigger line for which the trigger has been enabled - It would be 
// impossible to start the operation! 
#define ME_ERROR_AO_NO_VALID_TRIGGERED_CHANNEL						0x00003007

// When calling AOSingleSimultaneous or AOStartSynchronous with an external
// trigger, the parameter ExtTriggerEnable will be ignored for all those 
// channels for which the external trigger has not been enabled - it should
// be 0 for these channels - Warning
#define ME_ERROR_AO_DISABLED_TRIGGER								0x00003008

// On calling AOSingleSimultaneous, the external trigger has been enabled for 
// one or more channels which do not have an external trigger line - Warning
#define ME_ERROR_AO_INVALID_EXT_ENABLE								0x00003009

// The stop mode for AOStop was neither ME4000_AO_STOP_LAST_VALUE nor
// ME4000_AO_STOP_IMMEDIATE
#define ME_ERROR_AO_INVALID_STOP_MODE								0x0000300A

// AOWraparound is being called in blocking mode. An endless operation is not 
// allowed --> The ulLoops parameter may not be 0
#define ME_ERROR_AO_WRAPAROUND_BLOCKING_LOOPS_INVALID				0x0000300B

// The buffer data size for AOContinuous may not exceed 64K
#define ME_ERROR_AO_CONTINUOUS_BUFFER_TOO_LARGE						0x0000300C

// In AOWraparound the terminate routine is NULL or in AOContinuous the callback
// routine is NULL. The corresponding context pointer will be ignored and should 
// also be set to NULL - Warning
// (inspect parameter number)
#define ME_ERROR_AO_CALLBACK_CONTEXT_PARAMETER_IGNORED				0x0000300D

// In AOWaveGen the parameters 'dAmplitude' and 'dOffset' taken together lead to
// a signal that lies partly outside the range -10V - +10V
#define ME_ERROR_AO_INVALID_WAVE_RANGE								0x0000300E

// One of the routines AOWraparound, AOContinuous or AOStart is being called before
// AOConfig has been called AT LEAST ONCE for the channel concerned
#define ME_ERROR_AO_HW_NOT_CONFIGURED								0x0000300F

// AOStart or AOStartSynchronous is being called before one of AOWraparound or 
// AOContinuous has been called AT LEAST ONCE for the channel(s) concerned
#define ME_ERROR_AO_SW_NOT_CONFIGURED								0x00003010

// AOStart is being called for a particular channel which has been configured
// to be started simultaneously with other channels 
// NOTE: This error code is only required for compatibility with an earler 
// version 
#define ME_ERROR_AO_SIMULTANEOUS_TRIGGER							0x00003011

// AOStart is being called with the value ME4000_AO_SIMULTANEOUS_CHANNELS for 
// the parameter uiChannelNumber but no channels have been configured for a
// simultaneous start
// NOTE: This error code is only requierd for compatibility with an earler 
// version 
#define ME_ERROR_AO_NO_SIMULTANEOUS_CHANNELS						0x00003012

// AOAppendNewValues has been called for an AO channel on which a continuous AO
// operation (AOContinuous) is NOT currently running
#define ME_ERROR_AO_CONTINUOUS_NOT_RUNNING							0x00003013

// This AO channel is currently busy. This function cannot be executed until the
// current AO operation on this channel has been terminated
#define ME_ERROR_AO_BUSY											0x00003014

// AOStop has been called to terminate an AO operation, but no AO operation is
// currently running on this channel - Warning
#define ME_ERROR_AO_NOT_BUSY										0x00003015

// The iWaitIdle parameter for AOGetStatus was neither ME4000_AO_WAIT_IDLE nor 
// ME4000_AO_WAIT_NONE
#define ME_ERROR_AO_INVALID_WAIT									0x00003016

// AOStop has been called to terminate a simultaneous AO operation, but no AO 
// channel is currently running in simultaneous mode - Warning
// NOTE: This error code is only required for compatibility with an earler 
// version 
#define ME_ERROR_AO_NO_SIMULTANEOUS_CHANNEL_BUSY					0x00003017

// A function has been called which requires the use of DAC3, but this DAC is 
// being used for a normal AO operation on channel 3
#define ME_ERROR_AO_DAC0_IN_USE										0x00003018

// A function has been called which requires the use of DAC3, but this DAC is 
// being used for a normal AO operation on channel 3
#define ME_ERROR_AO_DAC3_IN_USE										0x00003019

// The AO FIFO underflowed (was empty on entering the FIFO half full interrupt)
// - Hardware error
#define ME_ERROR_AO_FIFO_UNDERFLOW									0x0000301A

// DIO specific error codes
// ------------------------
// ------------------------

// A DIO port number was invalid for this board  
#define ME_ERROR_DIO_INVALID_PORT_NUMBER							0x00004000

// An DIO port mode was invalid  
#define ME_ERROR_DIO_INVALID_PORT_DIRECTION							0x00004001

// The board is Optoisolated - the port mode is invalid for this port
#define ME_ERROR_DIO_OPTOISOLATED_INVALID_PORT_DIRECTION			0x00004002

// The board is Optoisolated - the port B can only be used for input
#define ME_ERROR_DIO_OPTOISOLATED_PORT_B_INPUT_ONLY					0x00004003


// External interrupt specific error codes
// ---------------------------------------
// ---------------------------------------

// For CntRead or CntWrite, the counter number was invalid
#define ME_ERROR_CNT_INVALID_COUNTER								0x00004100

// For CntRead or CntWrite, the counter mode was invalid
#define ME_ERROR_CNT_INVALID_MODE									0x00004101

// A PWM operation is running, This function cannot be executed until the PWM
// operation has been terminated 
#define ME_ERROR_CNT_PWM_BUSY										0x00004102

// CntPWMStop has been called to terminate a PWM operation, but a PWM operation 
// is not currently running - Warning
#define ME_ERROR_CNT_PWM_NOT_BUSY									0x00004103


// External interrupt specific error codes
// ---------------------------------------
// ---------------------------------------

// ExtIrqEnable was called although the external interrupt was already enabled  
#define ME_ERROR_EXT_IRQ_ENABLED									0x00004200

// ExtIrqDisable was called although the external interrupt was not enabled  
#define ME_ERROR_EXT_IRQ_NOT_ENABLED								0x00004201

// DIO Bit Pattern specific error codes
// ------------------------------------
// ------------------------------------

// The execution mode for DIOBitPatternWraparound was neither 
// ME4000_DIOBP_WRAPAROUND_BLOCKING nor ME4000_DIOBP_WRAPAROUND_ASYNCHRONOUS OR
// the execution mode for DIOBitPatternAppendNewValues was neither 
// ME4000_DIOBP_APPEND_NEW_VALUES_BLOCKING nor 
// ME4000_DIOBP_APPEND_NEW_VALUES_NON_BLOCKING
#define ME_ERROR_DIOBP_INVALID_EXECUTION_MODE						0x00005000

// The trigger mode for DIOBitPatternConfig was not one of 
// ME4000_DIOBP_TRIGGER_SOFTWARE, ME4000_DIOBP_TRIGGER_EXT_EDGE_RISING or 
// ME4000_DIOBP_TRIGGER_EXT_EDGE_FALLING
#define ME_ERROR_DIOBP_INVALID_TRIGGER_MODE							0x00005001

// The external trigger edge for me4000DIOBitPatternConfig was not one of
// ME4000_DIOBP_TRIGGER_EXT_EDGE_RISING, ME4000_DIOBP_TRIGGER_EXT_EDGE_FALLING
#define ME_ERROR_DIOBP_INVALID_EXT_TRIGGER_EDGE						0x00005002

// me4000DIOBitPatternConfig is being used without an external trigger and this 
// parameter will be ignored, it should be set to 0 - 
// Warning (inspect parameter number)
#define ME_ERROR_DIOBP_CONFIG_SW_TRIGGER_PARAMETER_IGNORED			0x00005003

// DIOBitPatternWraparound is being called in blocking mode. An endless 
// operation is not allowed --> The ulLoops parameter may not be 0
#define ME_ERROR_DIOBP_WRAPAROUND_BLOCKING_LOOPS_INVALID			0x00005004

// The buffer data size for DIOBitPatternContinuous may not exceed 64K
#define ME_ERROR_DIOBP_CONTINUOUS_BUFFER_TOO_LARGE					0x00005005

// In DIOBitPatternWraparound the terminate routine is NULL or in 
// DIOBitPatternContinuous the callback routine is NULL. The corresponding 
// context pointer will be ignored and should also be set to NULL - Warning
// (inspect parameter number)
#define ME_ERROR_DIOBP_CALLBACK_CONTEXT_PARAMETER_IGNORED			0x00005006

// One of the routines DIOBitPatternWraparound, DIOBitPatternContinuous or 
// DIOBitPatternStart is being called before DIOBitPatternConfig has been called
// AT LEAST ONCE
#define ME_ERROR_DIOBP_HW_NOT_CONFIGURED							0x00005007

// DIOBitPatternStart is being called before one of DIOBitPatternWraparound or 
// DIOBitPatternContinuous has been called AT LEAST ONCE
#define ME_ERROR_DIOBP_SW_NOT_CONFIGURED							0x00005008

// DIOBitPatternAppendNewValues has been called although a continuous 
// DIOBitPattern operation (DIOBitPatternContinuous) is NOT currently running
#define ME_ERROR_DIOBP_CONTINUOUS_NOT_RUNNING						0x00005009

// A DIOBitPattern operation is currently running. This function cannot be 
// executed until the DIOBitPattern operation has been terminated
#define ME_ERROR_DIOBP_BUSY											0x0000500A

// DIOBitPatternStop has been called to terminate a DIOBitPattern operation, but
// a  DIOBitPattern operation is not currently running - Warning
#define ME_ERROR_DIOBP_NOT_BUSY										0x0000500B

// The iWaitIdle parameter for DIOBPGetStatus was neither ME4000_DIOBP_WAIT_IDLE
// nor ME4000_DIOBP_WAIT_NONE
#define ME_ERROR_DIOBP_INVALID_WAIT									0x0000500C

// The stop mode for DIOBPStop was neither ME4000_DIOBP_STOP_LAST_VALUE nor
// ME4000_DIOBP_STOP_IMMEADIATE
#define ME_ERROR_DIOBP_INVALID_STOP_MODE							0x0000500D

// A function has been called which requires the use of DAC3, but this DAC is 
// being used for a DIO Bit Pattern operation
#define ME_ERROR_DIOBP_DAC3_IN_USE									0x0000500E

// A DIOBP port number was invalid for this board  
#define ME_ERROR_DIOBP_INVALID_PORT_NUMBER							0x0000500F

// The iOutputMode for DIOBPPortConfig was neither 
// ME4000_DIOBP_OUTPUT_MODE_BYTE_LOW nor ME4000_DIOBP_OUTPUT_MODE_BYTE_HIGH
#define ME_ERROR_DIOBP_INVALID_OUTPUT_MODE							0x00005010

// The board is Optoisolated - the function is not supported for this port
#define ME_ERROR_DIOBP_OPTOISOLATED_FUNCTION_UNSUPPORTED			0x00005011


// MultiSig specific error codes
// ------------------------------------
// ------------------------------------

// An attempt has been made to call a MultiSig routine although MultiSig has 
// been opened
#define ME_ERROR_MULTISIG_NOT_OPEN									0x00006000

// MultiSigOpen has been called although the MultiSig is already open
#define ME_ERROR_MULTISIG_OPEN										0x00006001

// The iLEDStatus parameter for MultiSigAddressLED was neither 
// ME4000_MULTISIG_LED_OFF nor ME4000_MULTISIG_LED_OFF
#define ME_ERROR_MULTISIG_INVALID_LED_STATUS						0x00006002

// The uiChannelGroup parameter for me4000MultiSigSetGain was neither 
// ME4000_MULTISIG_GROUP_A nor ME4000_MULTISIG_GROUP_B
#define ME_ERROR_MULTISIG_INVALID_CHANNEL_GROUP						0x00006003

// The iGain parameter for me4000MultiSigSetGain or me4000MultiSigAIDigitToSize 
// was not one of ME4000_MULTISIG_GAIN_1, ME4000_MULTISIG_GAIN_10 or 
// ME4000_MULTISIG_GAIN_100
#define ME_ERROR_MULTISIG_INVALID_GAIN								0x00006004

// The iModuleType parameter for me4000MultiSigAIDigitToSize was not one of
// ME4000_MULTISIG_MODULE_...
#define ME_ERROR_MULTISIG_INVALID_MODULE_TYPE						0x00006005

// A function has been called which requires the use of a IO port, but this port 
// is currently being used for MultiSig operations 
#define ME_ERROR_MULTISIG_PORT_IN_USE								0x00006006


// MultiSigAI specific error codes
// ------------------------------------
// ------------------------------------

// An Mux channel number was invalid  (> 255) - Error from MultiSigAISingle 
#define ME_ERROR_MULTISIGAI_INVALID_CHANNEL								0x00007000

// The MUX list was not well-formed - individual channels not 
// equidistant - Warning.
#define ME_ERROR_MULTISIGAI_CHAN_LIST_INCORRECT							0x00007001

// The acquisition mode for me4000MultiSigAIConfig was not one of 
// ME4000_AI_ACQ_MODE_SOFTWARE, ME4000_AI_ACQ_MODE_EXT, 
// ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE or ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST
#define ME_ERROR_MULTISIGAI_INVALID_ACQ_MODE							0x00007002

// The trigger mode for me4000MultiSigAISingle was not one of 
// ME4000_AI_TRIGGER_SOFTWARE, ME4000_AI_TRIGGER_EXT_DIGITAL or 
// ME4000_AI_TRIGGER_EXT_ANALOG
#define ME_ERROR_MULTISIGAI_INVALID_TRIGGER_MODE						0x00007003

// The trigger mode for me4000MultiSigAIConfig with an acquisition triggered by an 
// external trigger (iAcqMode = ME4000_AI_ACQ_MODE_EXT, 
// ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE or ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST)
// was not one of ME4000_AI_TRIGGER_EXT_DIGITAL or ME4000_AI_TRIGGER_EXT_ANALOG
#define ME_ERROR_MULTISIGAI_INVALID_EXT_TRIGGER_MODE					0x00007004

// The external trigger edge for me4000MultiSigAIConfig was not one of 
// ME4000_AI_TRIGGER_EXT_EDGE_RISING, ME4000_AI_TRIGGER_EXT_EDGE_FALLING or 
// ME4000_AI_TRIGGER_EXT_BOTH
#define ME_ERROR_MULTISIGAI_INVALID_EXT_TRIGGER_EDGE					0x00007005

// MultiSigAIConfig is being called with an aquisition mode which does not require an 
// external trigger and this parameter will be ignored, it should be set to 0 
// - Warning (inspect parameter number)
#define ME_ERROR_MULTISIGAI_CONFIG_SW_TRIGGER_PARAMETER_IGNORED			0x00007006

// MultiSigAIConfig is being called with a mode which samples a single value or
// a single channel list at each external trigger. The ScanTime parameter is not 
// required and will be ignored. 
// It should be set to 0 - Warning (inspect parameter number)
#define ME_ERROR_MULTISIGAI_CONFIG_EXT_TRIGGER_TIMER_PARAMETER_IGNORED	0x00007007

// MultiSigAIConfig is being called with a scan time smaller than that required by the 
// requested chan time. Minimum scan time = Number of channels * chan time + 66
#define ME_ERROR_MULTISIGAI_INSUFFICIENT_SCAN_TIME						0x00007008

// One of the routines MultiSigAIScan, MultiSigAIContinuous or MultiSigAIStart is being called 
// before MultiSigAIConfig has been called AT LEAST ONCE
#define ME_ERROR_MULTISIGAI_HW_NOT_CONFIGURED							0x00007009

// MultiSigAIStart is being called before one of MultiSigAIScan or MultiSigAIContinuous has 
// been called AT LEAST ONCE
#define ME_ERROR_MULTISIGAI_SW_NOT_CONFIGURED							0x0000700A

// In MultiSigAIScan or MultiSigAIContinuous a callback routine is NULL. The corresponding 
// context pointer will be ignored and should also be set to NULL - Warning
// (inspect parameter number)
#define ME_ERROR_MULTISIGAI_CALLBACK_CONTEXT_PARAMETER_IGNORED			0x0000700B

// In MultiSigAIScan or MultiSigAIContinuous a callback routine is NULL. The corresponding 
// callback counter will be ignored and should be set to 0 - Warning
#define ME_ERROR_MULTISIGAI_CALLBACK_FREQUENCY_PARAMETER_IGNORED		0x0000700C

// In MultiSigAISingle or MultiSigAIConfig the AI channel number was invalid
#define ME_ERROR_MULTISIGAI_INVALID_AI_CHANNEL							0x0000700D

// The execution mode for MultiSigAIScan was neither ME4000_AI_SCAN_ASYNCHRONOUS nor
// ME4000_AI_SCAN_BLOCKING  OR the execution mode for MultiSigAIGetNewValues was 
// neither ME4000_AI_GET_NEW_VALUES_BLOCKING nor 
// ME4000_AI_GET_NEW_VALUES_NON_BLOCKING
#define ME_ERROR_MULTISIGAI_INVALID_EXECUTION_MODE						0x0000700E

// The board's AI component is reserved for a MUX operation. This function 
// cannot be executed until the current MUX operation has been terminated
#define ME_ERROR_MULTISIGAI_BUSY										0x0000700F

// MultiSigAIStop has been called to terminate an MultiSigAI operation, but no MultiSigAI 
// operation is currently running - Warning
#define ME_ERROR_MULTISIGAI_NOT_BUSY									0x00007010

// The iWaitIdle parameter for MultiSigAIGetStatus was neither ME4000_AI_WAIT_IDLE
// nor ME4000_AI_WAIT_NONE
#define ME_ERROR_MULTISIGAI_INVALID_WAIT								0x00007011

// An attempt has been made to call an MultiSigAI routine although the AI Mux has
// not been enabled. MultiSigAIEnable MUST be called first
#define ME_ERROR_MULTISIGAI_NOT_OPEN									0x00007012

// MultiSigAIOpen has been called although the AI Mux is already open
#define ME_ERROR_MULTISIGAI_OPEN										0x00007013

// A function has been called which requires the use of the AI hardware but this
// is currently being used for AI Mux operations 
#define ME_ERROR_MULTISIGAI_AI_IN_USE									0x00007014

// A function has been called which requires the use of DAC3 but this DAC is 
// currently being used for AI Mux operations 
#define ME_ERROR_MULTISIGAI_DAC3_IN_USE									0x00007015

// A function has been called which requires the use of a IO port, but this port 
// is currently being used for AI Mux operations 
#define ME_ERROR_MULTISIGAI_PORT_IN_USE									0x00007016

// AO Demux specific error codes
// ------------------------------------
// ------------------------------------

// A Demux channel number was invalid  (> 255) - Error from MultiSigAOSingle 
#define ME_ERROR_MULTISIGAO_INVALID_CHANNEL								0x00008000

// The execution mode for MultiSigAOWraparound was neither 
// ME4000_AO_WRAPAROUND_BLOCKING nor ME4000_AO_WRAPAROUND_ASYNCHRONOUS OR
// the execution mode for MultiSigAOAppendNewValues was neither 
// ME4000_AO_APPEND_NEW_VALUES_BLOCKING nor 
// ME4000_AO_APPEND_NEW_VALUES_NON_BLOCKING
#define ME_ERROR_MULTISIGAO_INVALID_EXECUTION_MODE						0x00008001

// The trigger mode for MultiSigAOConfig was not one of 
// ME4000_AO_TRIGGER_SOFTWARE, ME4000_AO_TRIGGER_EXT_EDGE_RISING or 
// ME4000_AO_TRIGGER_EXT_EDGE_FALLING
#define ME_ERROR_MULTISIGAO_INVALID_TRIGGER_MODE						0x00008002

// The external trigger edge for me4000MultiSigAOSingle or me4000MultiSigAOConfig 
// was not one of ME4000_AO_TRIGGER_EXT_EDGE_RISING, ME4000_AI_TRIGGER_EXT_EDGE_FALLING
#define ME_ERROR_MULTISIGAO_INVALID_EXT_TRIGGER_EDGE					0x00008003

// MultiSigAOSingle is being used without an external trigger and this parameter will 
// be ignored, it should be set to 0 - Warning
// (inspect parameter number)
#define ME_ERROR_MULTISIGAO_SINGLE_SW_TRIGGER_PARAMETER_IGNORED			0x00008004

// MultiSigAOConfig is being used without an external trigger and this parameter will 
// be ignored, it should be set to 0 - Warning (inspect parameter number)
#define ME_ERROR_MULTISIGAO_CONFIG_SW_TRIGGER_PARAMETER_IGNORED			0x00008005

// MultiSigAOWraparound is being called in blocking mode. An endless 
// operation is not allowed --> The ulLoops parameter may not be 0
#define ME_ERROR_MULTISIGAO_WRAPAROUND_BLOCKING_LOOPS_INVALID			0x00008006

// In MultiSigAOWraparound the terminate routine is NULL or in 
// MultiSigAOContinuous the callback routine is NULL. The corresponding 
// context pointer will be ignored and should also be set to NULL - Warning
// (inspect parameter number)
#define ME_ERROR_MULTISIGAO_CALLBACK_CONTEXT_PARAMETER_IGNORED			0x00008007

// One of the routines MultiSigAOWraparound, MultiSigAOContinuous or 
// MultiSigAOStart is being called before MultiSigAOConfig has been called
// AT LEAST ONCE
#define ME_ERROR_MULTISIGAO_HW_NOT_CONFIGURED							0x00008008

// MultiSigAOStart is being called before one of MultiSigAOWraparound or 
// MultiSigAOContinuous has been called AT LEAST ONCE
#define ME_ERROR_MULTISIGAO_SW_NOT_CONFIGURED							0x00008009

// MultiSigAOAppendNewValues has been called although a continuous 
// MultiSigAO operation (MultiSigAOContinuous) is NOT currently running
#define ME_ERROR_MULTISIGAO_CONTINUOUS_NOT_RUNNING						0x0000800A

// An attempt has been made to call an MultiSigAO routine although the AO Demux has
// not been enabled. MultiSigAOEnable MUST be called first
#define ME_ERROR_MULTISIGAO_NOT_OPEN									0x0000800B

// MultiSigAOOpen has been called although the AO Demux is already open
#define ME_ERROR_MULTISIGAO_OPEN										0x0000800C

// A MultiSigAO operation is currently running. This function cannot be 
// executed until the MultiSigAO operation has been terminated
#define ME_ERROR_MULTISIGAO_BUSY										0x0000800D

// MultiSigAOStop has been called to terminate a MultiSigAO operation, but
// a  MultiSigAO operation is not currently running - Warning
#define ME_ERROR_MULTISIGAO_NOT_BUSY									0x0000800E

// The iWaitIdle parameter for MultiSigAOGetStatus was neither ME4000_AO_WAIT_IDLE
// nor ME4000_AO_WAIT_NONE
#define ME_ERROR_MULTISIGAO_INVALID_WAIT								0x0000800F

// A function has been called which requires the use of DAC0, but this DAC is 
// currently being used for AO Demux operations 
#define ME_ERROR_MULTISIGAO_DAC0_IN_USE									0x00008010

// A function has been called which requires the use of DAC3 but this DAC is 
// currently being used for AO Demux operations 
#define ME_ERROR_MULTISIGAO_DAC3_IN_USE									0x00008011

// A function has been called which requires the use of a IO port, but this port 
// is currently being used for AO Demux operations 
#define ME_ERROR_MULTISIGAO_PORT_IN_USE									0x00008012

// Error codes for internal IOCTL's
// --------------------------------
// --------------------------------

// NOTE:	For these error codes there is NO corresponding entry in 
// dll_error.cpp

// Unspecified error
#define ME_ERROR_UNKNOWN_CALIBRATION_ID									0x0000A000
	
