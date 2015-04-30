Attribute VB_Name = "Declarations"
' Constants used by the API

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                             ME4000 Interface                                  |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                              General Global Consts                                 |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

' Maximum number of boards supported
Global Const ME4000_MAX_DEVICES = 32

' Define for the return value from an API function that is executed
' successfully
Global Const ME4000_NO_ERROR = &H0

' Define for a scalar parameter which is reserved or not used in a particular
' context
Global Const ME4000_VALUE_NOT_USED = 0

' Define for a pointer or callback-function parameter which is reserved or not
' used in a particular context
Global Const ME4000_POINTER_NOT_USED = 0

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                        Global Consts for Error Routines                            |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Global Const ME4000_ERROR_DEFAULT_PROC_ENABLE = &H10101
Global Const ME4000_ERROR_DEFAULT_PROC_DISABLE = &H10102

' The user error function passed to  me4000ErrorSetUserProc should have the
' following form:
'
' Public Sub ErrorFunction(ByRef sFunctionName As String, ByVal lErrorCode As Long)
'
' where:
'
'   sFunctionName is a BASIC STRING containing the namke of the function which
'   caused the error
'
'   lErrorCode is the error number

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                        Global Consts for AI Routines                               |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

' Acquisition modes for me4000AIConfig - Parameter iAcqMode
Global Const ME4000_AI_ACQ_MODE_SOFTWARE = &H20101                ' Continous sampling with software start
Global Const ME4000_AI_ACQ_MODE_EXT = &H20102                     ' Continous sampling with external trigger start
Global Const ME4000_AI_ACQ_MODE_EXT_SINGLE_VALUE = &H20103        ' Sample one value for each external trigger
Global Const ME4000_AI_ACQ_MODE_EXT_SINGLE_CHANLIST = &H20104     ' Sample one channel for each external trigger

' Input range for me4000AISingle, me4000AIMakeChannelListEntry
' and me4000AIDigitToVolt - Parameter iRange
Global Const ME4000_AI_RANGE_BIPOLAR_10 = &H20201
Global Const ME4000_AI_RANGE_BIPOLAR_2_5 = &H20202
Global Const ME4000_AI_RANGE_UNIPOLAR_10 = &H20203
Global Const ME4000_AI_RANGE_UNIPOLAR_2_5 = &H20204

' Input mode for me4000AISingle and me4000AIConfig -
' Parameter iSDMode
Global Const ME4000_AI_INPUT_SINGLE_ENDED = &H20301
Global Const ME4000_AI_INPUT_DIFFERENTIAL = &H20302

' Trigger mode for me4000AISingle - Parameter iTriggerMode
' Last two 'defines' - external trigger mode for
' me4000AIConfig - Parameter iExtTriggerMode
Global Const ME4000_AI_TRIGGER_SOFTWARE = &H20401
Global Const ME4000_AI_TRIGGER_EXT_DIGITAL = &H20402
Global Const ME4000_AI_TRIGGER_EXT_ANALOG = &H20403

' External trigger flank type for me4000AISingle and
' me4000AIConfig - Parameter iExtTriggerEdge
Global Const ME4000_AI_TRIGGER_EXT_EDGE_RISING = &H20501
Global Const ME4000_AI_TRIGGER_EXT_EDGE_FALLING = &H20502
Global Const ME4000_AI_TRIGGER_EXT_EDGE_BOTH = &H20503

' Simultaneous data acquisition off/on for meAIConfig
' - Parameter iSimultaneous
Global Const ME4000_AI_SIMULTANEOUS_DISABLE = &H20601
Global Const ME4000_AI_SIMULTANEOUS_ENABLE = &H20602

' Execution mode for me4000AIScan - Parameter iExecutionMode
Global Const ME4000_AI_SCAN_BLOCKING = &H20701
Global Const ME4000_AI_SCAN_ASYNCHRONOUS = &H20702

' Execution mode for me4000AIGetNewNewValues - Parameter iExecutionMode
Global Const ME4000_AI_GET_NEW_VALUES_BLOCKING = &H20801
Global Const ME4000_AI_GET_NEW_VALUES_NON_BLOCKING = &H20802

' Wait modus for me4000AIGetStatus - Parameter iWaitIdle
Global Const ME4000_AI_WAIT_IDLE = &H20901
Global Const ME4000_AI_WAIT_NONE = &H20902

' Return status for me4000AIGetStatus - Parameter piStatus
Global Const ME4000_AI_STATUS_IDLE = &H20A01
Global Const ME4000_AI_STATUS_BUSY = &H20A02

' The AI callback function passed to me4000AIScan and me4000AIContinuous should
' have the following form:
'
' Public Sub AICallback(ByRef piDataBuffer() As Integer,
'                                ByVal lNumberOfData As Long,
'                                   ByVal lCallbackContext As Long,
'                                                   ByVal lLastError As Long)
'
' where:
'
'   piDataBuffer is is a normal Basic array STARTING At INDEX 0
'
'   lNumberOfData is the number of data value in the array piDataBuffer
'
'   lCallbackContext is the callback context parameter previously passed to
'   AIScan or AIContinuous
'
'   lLastError is the last data acquisition error (ME4000_NO_ERROR if no error
'   occurred).

' The AI terminate function passed to me4000AIScan should have the following
' form:
'
' Public Sub AITerminate(ByRef piDataBuffer() As Integer,
'                                ByVal lNumberOfData As Long,
'                                   ByVal lTerminateContext As Long,
'                                                   ByVal lLastError As Long)
'
' where:
'
'   piDataBuffer is is a normal Basic array STARTING At INDEX 0
'
'   lNumberOfData is the number of data value in the array piDataBuffer
'
'   lTerminateContext is the terminate context parameter previously passed to
'   AIScan
'
'   lLastError is the last data acquisition error (ME4000_NO_ERROR if no error
'   occurred).

' NOTE: These functions which should be provided by the basic application and
'       which will be called automatically by the API at the appropriate time
'       must be placed in a standard .BAS module (not in a class module or
'       attached to a form) and the AddressOf keyword should be used to pass the
'       function pointer to the ME4000 API routine.


'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                        Global Consts for AO Routines                               |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

' Trigger mode for me4000AOSingle - Parameter iTriggerMode
Global Const ME4000_AO_TRIGGER_SOFTWARE = &H30101
Global Const ME4000_AO_TRIGGER_EXT_DIGITAL = &H30103

' ----------------------------------------------------------------------------
' ----------------------------------------------------------------------------
' NOTE:    The following constants are obsolete and are retained only for
'          backward compatibility. They should no longer be used.
Global Const ME4000_AO_TRIGGER_SOFTWARE_TRANSPARENT = &H30101
Global Const ME4000_AO_TRIGGER_SOFTWARE_SIMULTANEOUS = &H30102
' ----------------------------------------------------------------------------
' ----------------------------------------------------------------------------

' External trigger flank type for me4000AOSingle, me4000AOSingleSimultaneous,
' me4000AOConfig and me4000AOStartSynchronous.
Global Const ME4000_AO_TRIGGER_EXT_EDGE_RISING = &H30201
Global Const ME4000_AO_TRIGGER_EXT_EDGE_FALLING = &H30202
Global Const ME4000_AO_TRIGGER_EXT_EDGE_BOTH = &H30203

' Execution mode for me4000AOWraparound - Parameter iExecutionMode
Global Const ME4000_AO_WRAPAROUND_BLOCKING = &H30301
Global Const ME4000_AO_WRAPAROUND_ASYNCHRONOUS = &H30302

' Global Const for an infinite (endless) execution for me4000AOWraparound -
' Parameter ulLoops
Global Const ME4000_AO_WRAPAROUND_INFINITE = &H0

' ----------------------------------------------------------------------------
' ----------------------------------------------------------------------------
' NOTE:   The following constant is obsolete and is retained only for
'         backward compatibility. It should no longer be used.
Global Const ME4000_AO_SIMULTANEOUS_CHANNELS = &HF
' ----------------------------------------------------------------------------
' ----------------------------------------------------------------------------

' Execution mode for me4000AOAppendNewValues - Parameter iExecutionMode
Global Const ME4000_AO_APPEND_NEW_VALUES_BLOCKING = &H30401
Global Const ME4000_AO_APPEND_NEW_VALUES_NON_BLOCKING = &H30402

' Wait modus for me4000AOGetStatus - Parameter iWaitIdle
Global Const ME4000_AO_WAIT_IDLE = &H30501
Global Const ME4000_AO_WAIT_NONE = &H30502

' Return status for me4000AOGetStatus - Parameter piStatus
Global Const ME4000_AO_STATUS_IDLE = &H30601
Global Const ME4000_AO_STATUS_BUSY = &H30602

' Stop mode for me4000AOStop - Parameter iStopMode
Global Const ME4000_AO_STOP_MODE_LAST_VALUE = &H30701
Global Const ME4000_AO_STOP_MODE_IMMEDIATE = &H30702

' Signal forms for the function ME4000AOWaveGen - Parameter iShape
Global Const ME4000_AO_SHAPE_RECTANGLE = &H30801
Global Const ME4000_AO_SHAPE_TRIANGLE = &H30802
Global Const ME4000_AO_SHAPE_SINUS = &H30803
Global Const ME4000_AO_SHAPE_COSINUS = &H30804
Global Const ME4000_AO_SHAPE_POS_RAMP = &H30805
Global Const ME4000_AO_SHAPE_NEG_RAMP = &H30806

' Trigger Enable/Disable for the array piExtTriggerEnable in
' me4000AOSingleSimultaneous and me4000AOStartSynchronous.
Global Const ME4000_AO_TRIGGER_EXT_DISABLE = &H30901
Global Const ME4000_AO_TRIGGER_EXT_ENABLE = &H30902

' Typedef for AO terminate function - used in me4000AOWraparound
' typedef void (_stdcall * ME4000_P_AO_TERMINATE_PROC)(void* pTerminateContext);

' Typedef for AO callback function - used in me4000AOContinuous
'typedef void (_stdcall * ME4000_P_AO_CALLBACK_PROC)(unsigned long ulBufferAvailable,
 '                                                               void* pCallbackContext);

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                        Global Consts for DIO Routines                              |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

' Defines for port numbers
Global Const ME4000_DIO_PORT_A = 0
Global Const ME4000_DIO_PORT_B = 1
Global Const ME4000_DIO_PORT_C = 2
Global Const ME4000_DIO_PORT_D = 3

' Port direction for me4000DIOConfig - Parameter iDir
Global Const ME4000_DIO_PORT_INPUT = &H40201
Global Const ME4000_DIO_PORT_OUTPUT = &H40202


'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                       Defines for counter Routines                            |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

' Mode for me4000CntWrite - Parameter iMode
Global Const ME4000_CNT_MODE_0 = &H50101
Global Const ME4000_CNT_MODE_1 = &H50102
Global Const ME4000_CNT_MODE_2 = &H50103
Global Const ME4000_CNT_MODE_3 = &H50104
Global Const ME4000_CNT_MODE_4 = &H50105
Global Const ME4000_CNT_MODE_5 = &H50106

'------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                 Defines for external interrupt Routines                       |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

' Typedef for external interrupt callback routine used in me4000ExtIrqEnable
' typedef void (_stdcall * ME4000_P_EXT_IRQ_PROC)(void* pExtIrqContext);

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'             Global Consts for DIO Bit Pattern Routines                        |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

' Defines for port numbers
Global Const ME4000_DIOBP_PORT_A = 0
Global Const ME4000_DIOBP_PORT_B = 1
Global Const ME4000_DIOBP_PORT_C = 2
Global Const ME4000_DIOBP_PORT_D = 3

' Output mode for me4000DIOBPPortConfig - Parameter iOutputMode
Global Const ME4000_DIOBP_OUTPUT_MODE_BYTE_LOW = &H60101
Global Const ME4000_DIOBP_OUTPUT_MODE_BYTE_HIGH = &H60102

' Trigger mode for me4000DIOBPAOConfig - Parameter iTriggerMode
Global Const ME4000_DIOBP_TRIGGER_SOFTWARE = &H60201
Global Const ME4000_DIOBP_TRIGGER_EXT_DIGITAL = &H60202

' External trigger flank type for me4000DIOBPAOConfig - Parameter
' iExtTriggerEdge
Global Const ME4000_DIOBP_TRIGGER_EXT_EDGE_RISING = &H60301
Global Const ME4000_DIOBP_TRIGGER_EXT_EDGE_FALLING = &H60302
Global Const ME4000_DIOBP_TRIGGER_EXT_EDGE_BOTH = &H60303

' Execution mode for me4000DIOBPWraparound - Parameter iExecutionMode
Global Const ME4000_DIOBP_WRAPAROUND_BLOCKING = &H60401
Global Const ME4000_DIOBP_WRAPAROUND_ASYNCHRONOUS = &H60402

' Global Const for an infinite (endless) execution for me4000DIOBPWraparound -
' Parameter ulLoops
Global Const ME4000_DIOBP_WRAPAROUND_INFINITE = &H0

' Execution mode for me4000DIOBPAppendNewValues - Parameter iExecutionMode
Global Const ME4000_DIOBP_APPEND_NEW_VALUES_BLOCKING = &H60501
Global Const ME4000_DIOBP_APPEND_NEW_VALUES_NON_BLOCKING = &H60502

' Wait modus for me4000DIOBPGetStatus - Parameter iWaitIdle
Global Const ME4000_DIOBP_WAIT_IDLE = &H60601
Global Const ME4000_DIOBP_WAIT_NONE = &H60602

' Return status for me4000DIOBPGetStatus - Parameter piStatus
Global Const ME4000_DIOBP_STATUS_IDLE = &H60701
Global Const ME4000_DIOBP_STATUS_BUSY = &H60702

' Stop mode for me4000DIOBPStop - Parameter iStopMode
Global Const ME4000_DIOBP_STOP_MODE_LAST_VALUE = &H60801
Global Const ME4000_DIOBP_STOP_MODE_IMMEDIATE = &H60802

' Typedef for DIO BP terminate function - used in me4000DIOBPWraparound
' typedef void (_stdcall * ME4000_P_DIOBP_TERMINATE_PROC)(void* pTerminateContext);

' Typedef for DIO BP callback function - used in me4000DIOBPContinuous
' typedef void (_stdcall * ME4000_P_DIOBP_CALLBACK_PROC)(unsigned long ulBufferAvailable,
'                                                                    void* pCallbackContext);

'------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'              Global Consts specifically for MultiSig routines                      |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

' LED status for me4000MultiSigAddressLED - Parameter iLEDStatus
Global Const ME4000_MULTISIG_LED_OFF = &H70101
Global Const ME4000_MULTISIG_LED_ON = &H70102

' Channel group for me4000MultiSigSetGain - Parameter iChannelGroup
Global Const ME4000_MULTISIG_GROUP_A = &H70201
Global Const ME4000_MULTISIG_GROUP_B = &H70202

' Gain for me4000MultiSigSetGain and me4000MultiSigAIDigitToSize -
' Parameter iGain
Global Const ME4000_MULTISIG_GAIN_1 = &H70301
Global Const ME4000_MULTISIG_GAIN_10 = &H70302
Global Const ME4000_MULTISIG_GAIN_100 = &H70303

' Module type for me4000MultiSigAIDigitToSize - Parameter iModuleType
Global Const ME4000_MULTISIG_MODULE_NONE = &H70401
Global Const ME4000_MULTISIG_MODULE_DIFF16_10V = &H70402
Global Const ME4000_MULTISIG_MODULE_DIFF16_20V = &H70403
Global Const ME4000_MULTISIG_MODULE_DIFF16_50V = &H70404
Global Const ME4000_MULTISIG_MODULE_CURRENT16_0_20MA = &H70405
Global Const ME4000_MULTISIG_MODULE_RTD8_PT100 = &H70406
Global Const ME4000_MULTISIG_MODULE_RTD8_PT500 = &H70407
Global Const ME4000_MULTISIG_MODULE_RTD8_PT1000 = &H70408

' Module type for me4000MultiSigAIDigitToSize - Parameter iModuleType
' 500 Milliampere
Global Const ME4000_MULTISIG_I_MEASURED_DEFAULT = 0.0005




'Note, that string arguments only work with initialized string variables
'      Dim gsTextBuffer As String * 256 or alternatively  sBuffer = String(256, Chr(0))
'-------------------------------------------------------------------------------------------

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                             ME4000 Interface                                  |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                         Board Independant Routines                            |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                               Error Routines                                  |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000ErrorSetDefaultProc Lib "me4000Ex.dll" Alias "_me4000VB_ErrorSetDefaultProc@4" (ByVal lDefaultProcStatus As Long) As Long

Declare Function me4000ErrorSetUserProc Lib "me4000Ex.dll" Alias "_me4000VB_ErrorSetUserProc@4" (ByVal pErrorProc As Long) As Long

Declare Function me4000ErrorGetMessage Lib "me4000Ex.dll" Alias "_me4000VB_ErrorGetMessage@12" (ByVal lErrorCode As Long, ByVal pcBuffer As String, ByVal lBufferSize As Long) As Long

Declare Function me4000ErrorGetLastMessage Lib "me4000Ex.dll" Alias "_me4000VB_ErrorGetLastMessage@8" (ByVal pcBuffer As String, ByVal lBufferSize As Long) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                               Version Routines                                |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000GetDLLVersion Lib "me4000Ex.dll" Alias "_me4000VB_GetDLLVersion@4" (ByRef plVersion As Long) As Long

Declare Function me4000GetDriverVersion Lib "me4000Ex.dll" Alias "_me4000VB_GetDriverVersion@4" (ByRef plVersion As Long) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                               Utility Routines                                |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000FrequencyToTicks Lib "me4000Ex.dll" Alias "_me4000VB_FrequencyToTicks@20" (ByVal dRequiredFreq As Double, ByRef plTicksLowPart As Long, ByRef plTicksHighPart As Long, ByRef pdAchievedFreq As Double) As Long

Declare Function me4000TimeToTicks Lib "me4000Ex.dll" Alias "_me4000VB_TimeToTicks@20" (ByVal dRequiredTime As Double, ByRef plTicksLowPart As Long, ByRef plTicksHighPart As Long, ByRef pdAchievedTime As Double) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                         Board Specific Routines                               |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                            General Routines                                   |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000GetBoardVersion Lib "me4000Ex.dll" Alias "_me4000VB_GetBoardVersion@8" (ByVal lBoardNumber As Long, ByRef piVersion As Integer) As Long

Declare Function me4000GetSerialNumber Lib "me4000Ex.dll" Alias "_me4000VB_GetSerialNumber@8" (ByVal lBoardNumber As Long, ByRef plSeriakNumber As Long) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                               AI Routines                                     |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000AISingle Lib "me4000Ex.dll" Alias "_me4000VB_AISingle@32" (ByVal lBoardNumber As Long, ByVal lChannelNumber As Long, ByVal lRange As Long, ByVal lSDMode As Long, ByVal iTriggerMode As Long, ByVal lExtTriggerEdge As Long, ByVal lTimeOutSeconds As Long, ByRef piDigitalValue As Integer) As Long

Declare Function me4000AIMakeChannelListEntry Lib "me4000Ex.dll" Alias "_me4000VB_AIMakeChannelListEntry@12" (ByVal lChannelNumber As Long, ByVal lRange As Long, ByRef pbChanListEntry As Byte) As Long

Declare Function me4000AIConfig Lib "me4000Ex.dll" Alias "_me4000VB_AIConfig@48" (ByVal lBoardNumber As Long, ByRef pbChanList As Byte, ByVal lChanListCount As Long, ByVal lSDMode As Long, ByVal lSimultaneous As Long, ByVal lReserved As Long, ByVal lChanTicks As Long, ByVal lScanTicksLow As Long, ByVal lScanTicksHigh As Long, ByVal lAcMode As Long, ByVal lExtTriggerMode As Long, ByVal lExtTriggerEdge As Long) As Long

Declare Function me4000AIScan Lib "me4000Ex.dll" Alias "_me4000VB_AIScan@44" (ByVal lBoardNumber As Long, ByVal lNumberOfChanLists As Long, ByRef piBuffer As Integer, ByVal lBufferSizeValues As Long, ByVal lExecutionMode As Long, ByVal pCallbackProc As Long, ByVal lCallbackContext As Long, ByVal lRefreshFrequency As Long, ByVal pTerminateProc As Long, ByVal lTerminateContext As Long, ByVal lTimeOutSeconds As Long) As Long

Declare Function me4000AIContinuous Lib "me4000Ex.dll" Alias "_me4000VB_AIContinuous@20" (ByVal lBoardNumber As Long, ByVal pCallbackProc As Long, ByVal lCallbackContext As Long, ByVal lRefreshFrequency As Long, lTimeOutSeconds As Long) As Long

Declare Function me4000AIStart Lib "me4000Ex.dll" Alias "_me4000VB_AIStart@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000AIGetNewValues Lib "me4000Ex.dll" Alias "_me4000VB_AIGetNewValues@24" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal lNumberOfValuesToRead As Long, ByVal lExecutionMode As Long, ByRef plNumberofValuesRead As Long, ByRef piLastError As Long) As Long

Declare Function me4000AIStop Lib "me4000Ex.dll" Alias "_me4000VB_AIStop@8" (ByVal lBoardNumber As Long, ByVal lReserved As Long) As Long

Declare Function me4000AIExtractValues Lib "me4000Ex.dll" Alias "_me4000VB_AIExtractValues@32" (ByVal lChannelNumber As Long, ByRef piAIBuffer As Integer, ByVal lAIDataCount As Long, ByRef pbChanList As Byte, ByVal lChanListCount As Long, ByRef piChanBuffer As Integer, ByVal lChanBufferSizeValues As Long, ByRef plChanDataCount As Long) As Long

Declare Function me4000AIDigitToVolt Lib "me4000Ex.dll" Alias "_me4000VB_AIDigitToVolt@12" (ByVal iDigit As Integer, ByVal lRange As Long, ByRef pdVolt As Double) As Long

Declare Function me4000AIReset Lib "me4000Ex.dll" Alias "_me4000VB_AIReset@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000AIGetStatus Lib "me4000Ex.dll" Alias "_me4000VB_AIGetStatus@12" (ByVal lBoardNumber As Long, ByVal lWaitIdle As Long, ByRef plStatus As Long) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                               AO Routines                                     |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000AOSingle Lib "me4000Ex.dll" Alias "_me4000VB_AOSingle@24" (ByVal lBoardNumber As Long, ByVal lChannelNumber As Long, ByVal lTriggerMode As Long, ByVal lExtTriggerEdge As Long, ByVal lTimeOutSeconds As Long, ByVal iValue As Integer) As Long

Declare Function me4000AOSingleSimultaneous Lib "me4000Ex.dll" Alias "_me4000VB_AOSingleSimultaneous@32" (ByVal lBoardNumber As Long, ByRef plChannelNumber As Long, ByVal lCount As Long, ByVal lTriggerMode As Long, ByRef plExtTriggerEnable As Long, ByRef plExtTriggerEdge As Long, ByVal lTimeOutSeconds As Long, ByRef piValue As Integer) As Long

' ----------------------------------------------------------------------------
' ----------------------------------------------------------------------------
' NOTE:   The following function is obsolete and is retained only for
'         backward compatibility. It should no longer be used.
Declare Function me4000AOUpdate Lib "me4000Ex.dll" Alias "_me4000VB_AOUpdate@4" (ByVal lBoardNumvber As Long) As Long
' ----------------------------------------------------------------------------
' ----------------------------------------------------------------------------

Declare Function me4000AOConfig Lib "me4000Ex.dll" Alias "_me4000VB_AOConfig@20" (ByVal lBoardNumber As Long, ByVal lChannelNumber As Long, ByVal lTicks As Long, ByVal lTriggerMode As Long, ByVal lExtTriggerEdge As Long) As Long

Declare Function me4000AOWraparound Lib "me4000Ex.dll" Alias "_me4000VB_AOWraparound@36" (ByVal lBoardNumber As Long, ByVal lChannelNumber As Long, ByRef piDataBuffer As Integer, ByVal lDataCount As Long, ByVal lLoops As Long, ByVal lExecutionMode As Long, ByVal pTerminateProc As Long, ByVal lTerminateContext As Long, ByVal lTimeOutSeconds As Long) As Long

Declare Function me4000AOContinuous Lib "me4000Ex.dll" Alias "_me4000VB_AOContinuous@32" (ByVal lBoardNumber As Long, ByVal lChannelNumber As Long, ByRef piDataBuffer As Integer, ByVal lDataCount As Long, ByVal pCallbackProc As Long, ByVal lCallbackContext As Long, ByVal lTimeOutSeconds As Long, ByRef plNumberOfValuesWritten As Long) As Long

Declare Function me4000AOStart Lib "me4000Ex.dll" Alias "_me4000VB_AOStart@8" (ByVal lBoardNumber As Long, ByVal lChannelNumber As Long) As Long

Declare Function me4000AOStartSynchronous Lib "me4000Ex.dll" Alias "_me4000VB_AOStartSynchronous@28" (ByVal lBoardNumber As Long, ByRef plChannnelNumber As Long, ByVal lCount As Long, ByVal lTriggerMode As Long, ByRef plExtTriggerEnable As Long, ByRef plExtTriggerEdge As Long, ByVal lTimeOutSeconds As Long) As Long

Declare Function me4000AOAppendNewValues Lib "me4000Ex.dll" Alias "_me4000VB_AOAppendNewValues@24" (ByVal lBoardNumber As Long, ByVal lChannelNumber As Long, ByRef piDataBuffer As Integer, ByVal lNumberOfValuesToAppend As Long, ByVal lExecutionMode As Long, ByRef plNumberOfValuesAppended As Long) As Long

Declare Function me4000AOStop Lib "me4000Ex.dll" Alias "_me4000VB_AOStop@12" (ByVal lBoardNumber As Long, ByVal lChannelNumber As Long, ByVal lStopMode As Long) As Long

Declare Function me4000AOVoltToDigit Lib "me4000Ex.dll" Alias "_me4000VB_AOVoltToDigit@8" (ByVal dVolts As Double, ByRef piDigit As Integer) As Long

Declare Function me4000AOReset Lib "me4000Ex.dll" Alias "_me4000VB_AOReset@8" (ByVal lBoardNumber As Long, ByVal lChannelNumber As Long) As Long

Declare Function me4000AOWaveGen Lib "me4000Ex.dll" Alias "_me4000VB_AOWaveGen@24" (ByVal lBoardNumber As Long, ByVal lChannelNumber As Long, ByVal lShape As Long, ByVal dAmplitude As Double, ByVal dOffset As Double, ByVal dFrequency As Double) As Long

Declare Function me4000AOGetStatus Lib "me4000Ex.dll" Alias "_me4000VB_AOGetStatus@16" (ByVal lBoardNumber As Long, ByVal lChannelNumber As Long, ByVal lWaitIdle As Long, ByRef plStatus As Long) As Long

'*-----------------------------------------------------------------------------+
'------------------------------------------------------------------------------|
'                                                                              |
'                              DIO Routines                                    |
'                                                                              |
'------------------------------------------------------------------------------|
'-----------------------------------------------------------------------------*/

Declare Function me4000DIOConfig Lib "me4000Ex.dll" Alias "_me4000VB_DIOConfig@12" (ByVal lBoardNumber As Long, ByVal lPortNumber As Long, ByVal lPortDirection As Long) As Long

Declare Function me4000DIOResetAll Lib "me4000Ex.dll" Alias "_me4000VB_DIOResetAll@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000DIOGetBit Lib "me4000Ex.dll" Alias "_me4000VB_DIOGetBit@16" (ByVal lBoardNumber As Long, ByVal lPortNumber As Long, ByVal lBitNumber As Long, ByRef plBitValue As Long) As Long

Declare Function me4000DIOGetByte Lib "me4000Ex.dll" Alias "_me4000VB_DIOGetByte@12" (ByVal lBoardNumber As Long, ByVal lPortNumber As Long, ByRef pbByteValue As Byte) As Long

Declare Function me4000DIOSetBit Lib "me4000Ex.dll" Alias "_me4000VB_DIOSetBit@16" (ByVal lBoardNumber As Long, ByVal lPortNumber As Long, ByVal lBitNumber As Long, ByVal lBitValue As Long) As Long

Declare Function me4000DIOSetByte Lib "me4000Ex.dll" Alias "_me4000VB_DIOSetByte@12" (ByVal lBoardNumber As Long, ByVal lPortNumber As Long, ByVal bByteValue As Byte) As Long


'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                            Counter Routines                                   |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000CntWrite Lib "me4000Ex.dll" Alias "_me4000VB_CntWrite@16" (ByVal lBoardNumber As Long, ByVal lCounter As Long, ByVal lMode As Long, ByVal iValue As Long) As Long

Declare Function me4000CntRead Lib "me4000Ex.dll" Alias "_me4000VB_CntRead@12" (ByVal lBoardNumber As Long, ByVal lCounter As Long, ByRef plValue As Long) As Long

Declare Function me4000CntPWMStart Lib "me4000Ex.dll" Alias "_me4000VB_CntPWMStart@8" (ByVal lBoardNumber As Long, ByVal lPreScaler As Long, ByVal lDutyCycle As Long) As Long

Declare Function me4000CntPWMStop Lib "me4000Ex.dll" Alias "_me4000VB_CntPWMStop@4" (ByVal lBoardNumber As Long) As Long


'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                         External interrupt Routines                           |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000ExtIrqEnable Lib "me4000Ex.dll" Alias "_me4000VB_ExtIrqEnable@12" (ByVal lBoardNumber As Long, ByVal pExtIrqProc As Long, ByVal lExtIrqContext As Long) As Long

Declare Function me4000ExtIrqDisable Lib "me4000Ex.dll" Alias "_me4000VB_ExtIrqDisable@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000ExtIrqGetCount Lib "me4000Ex.dll" Alias "_me4000VB_ExtIrqGetCount@8" (ByVal lBoardNumber As Long, ByRef plIrqCount As Long) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                       DIO Bit Pattern Routines                                |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000DIOBPPortConfig Lib "me4000Ex.dll" Alias "_me4000VB_DIOBPPortConfig@12" (ByVal lBoardNumber As Long, ByVal lPortNumber As Long, ByVal lOutputMode As Long) As Long

Declare Function me4000DIOBPConfig Lib "me4000Ex.dll" Alias "_me4000VB_DIOBPConfig@16" (ByVal lBoardNumber As Long, ByVal lTicks As Long, ByVal lTriggerMode As Long, ByVal lExtTrigegrEdge As Long) As Long

Declare Function me4000DIOBPWraparound Lib "me4000Ex.dll" Alias "_me4000VB_DIOBPWraparound@32" (ByVal lBoardNumber As Long, ByRef piDataBuffer As Integer, ByVal lDataCount As Long, ByVal lLoops As Long, ByVal lExecutionMode As Long, ByVal pTerminateProc As Long, ByVal lTerminateContext As Long, ByVal lTimeOutSeconds As Long) As Long

Declare Function me4000IOBPContinuous Lib "me4000Ex.dll" Alias "_me4000VB_DIOBPContinuous@32" (ByVal lBoardNumber As Long, ByRef piDataBuffer As Integer, ByVal lDataCount As Long, ByVal pCallbackProc As Long, ByVal lCallbackContext As Long, ByVal lTimeOutSeconds As Long, ByRef plNumberOfValuesWritten As Long) As Long

Declare Function me4000DIOBPStart Lib "me4000Ex.dll" Alias "_me4000VB_DIOBPStart@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000DIOBPAppendNewValues Lib "me4000Ex.dll" Alias "_me4000VB_DIOBPAppendNewValues@20" (ByVal lBoardNumber As Long, ByRef piDataBuffer As Integer, ByVal lNumberOfValuesToAppend As Long, ByVal lExecutionMode As Long, ByRef plNumberOfValuesAppended As Long) As Long

Declare Function me4000DIOBPStop Lib "me4000Ex.dll" Alias "_me4000VB_DIOBPStop@8" (ByVal lBoardNumber As Long, lStopMode As Long) As Long

Declare Function me4000DIOBPReset Lib "me4000Ex.dll" Alias "_me4000VB_DIOBPReset@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000DIOBPGetStatus Lib "me4000Ex.dll" Alias "_me4000VB_DIOBPGetStatus@12" (ByVal lBoardNumber As Long, ByVal lWaitIdle As Long, ByRef plStatus As Long) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                            MultiSig Routines                                  |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000MultiSigOpen Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigOpen@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000MultiSigReset Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigReset@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000MultiSigAddressLED Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAddressLED@12" (ByVal lBoardNumber As Long, ByVal lBase As Long, ByVal lLEDStatus As Long) As Long

Declare Function me4000MultiSigSetGain Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigSetGain@16" (ByVal lBoardNumber As Long, ByVal lBase As Long, ByVal lChannelGroup As Long, ByVal lGain As Long) As Long

Declare Function me4000MultiSigClose Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigClose@4" (ByVal lBoardNumber As Long) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                            MultiSigAI Routines                                |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000MultiSigAIOpen Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIOpen@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000MultiSigAISingle Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAISingle@32" (ByVal lBoardNumber As Long, ByVal lAIChannelNumber As Long, ByVal lMuxChannelNumber, ByVal lGain As Long, ByVal lTriggerMode As Long, ByVal lExtTriggerEdge As Long, ByVal lTimeOutSeconds As Long, ByRef piDigitalValue As Integer) As Long

Declare Function me4000MultiSigAIConfig Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIConfig@44" (ByVal lBoardNumber As Long, ByVal lAIChannelNumber As Long, ByRef pbMuxChanList As Byte, ByVal lChanListCount As Long, ByVal lReserved As Long, ByVal lChanTicks As Long, ByVal lScanTicksLow As Long, ByVal lScanTicksHigh As Long, ByVal lAcMode As Long, ByVal lExtTriggerMode As Long, ByVal lExtTriggerEdge As Long) As Long

Declare Function me4000MultiSigAIScan Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIScan@44" (ByVal lBoardNumber As Long, ByVal lNumberOfMuxLists As Long, ByRef piBuffer As Integer, ByVal lBufferSizeValues As Long, ByVal lExecutionMode As Long, ByVal pCallbackProc As Long, ByVal lCallbackContext As Long, ByVal lRefreshFrequency As Long, ByVal pTerminateProc As Long, ByVal lTerminateContext As Long, ByVal lTimeOutSeconds As Long) As Long

Declare Function me4000MultiSigAIContinuous Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIContinuous@20" (ByVal lBoardNumber As Long, ByVal pCallbackProc As Long, ByVal lCallbackContext As Long, ByVal lRefreshFrequency As Long, lTimeOutSeconds As Long) As Long

Declare Function me4000MultiSigAIStart Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIStart@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000MultiSigAIGetNewValues Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIGetNewValues@24" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal lNumberOfValuesToRead As Long, ByVal lExecutionMode As Long, ByRef plNumberofValuesRead As Long, ByRef piLastError As Long) As Long

Declare Function me4000MultiSigAIStop Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIStop@8" (ByVal lBoardNumber As Long, ByVal lReserved As Long) As Long

Declare Function me4000MultiSigAIExtractValues Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIExtractValues@32" (ByVal lMuxChannelNumber As Long, ByRef piAIBuffer As Integer, ByVal lAIDataCount As Long, ByRef pbMuxChanList As Byte, ByVal lMuxChanListCount As Long, ByRef piChanBuffer As Integer, ByVal lChanBufferSizeValues As Long, ByRef plChanDataCount As Long) As Long

Declare Function me4000MultiSigAIDigitToSize Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIDigitToSize@20" (ByVal iDigit As Integer, ByVal lGain As Long, ByVal lModuleType As Long, ByVal dIMeasured As Double, ByRef pdSize As Double) As Long

Declare Function me4000MultiSigAIReset Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIReset@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000MultiSigAIGetStatus Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIGetStatus@12" (ByVal lBoardNumber As Long, ByVal lWaitIdle As Long, ByRef plStatus As Long) As Long

Declare Function me4000MultiSigAIClose Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAIClose@4" (ByVal lBoardNumber As Long) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                            MultiSigAO Routines                                |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me4000MultiSigAOOpen Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOOpen@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000MultiSigAOSingle Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOSingle@24" (ByVal lBoardNumber As Long, ByVal lDemuxChannelNumber As Long, ByVal lTriggerMode As Long, ByVal lExtTriggerEdge As Long, ByVal lTimeOutSeconds As Long, ByVal iValue As Integer) As Long

Declare Function me4000MultiSigAOConfig Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOConfig@24" (ByVal lBoardNumber As Long, ByRef pbDemuxChanList As Byte, ByVal lDemuxChanListCount As Long, ByVal lTicks As Long, ByVal lTriggerMode As Long, ByVal lExtTriggerEdge As Long) As Long

Declare Function me4000MultiSigAOWraparound Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOWraparound@32" (ByVal lBoardNumber As Long, ByRef piDataBuffer As Integer, ByVal lDataCount As Long, ByVal lLoops As Long, ByVal lExecutionMode As Long, ByVal pTerminateProc As Long, ByVal lTerminateContext As Long, ByVal lTimeOutSeconds As Long) As Long

Declare Function me4000MultiSigAOContinuous Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOContinuous@28" (ByVal lBoardNumber As Long, ByRef piDataBuffer As Integer, ByVal lDataCount As Long, ByVal pCallbackProc As Long, ByVal lCallbackContext As Long, ByVal lTimeOutSeconds As Long, ByRef plNumberOfValuesWritten As Long) As Long

Declare Function me4000MultiSigAOStart Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOStart@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000MultiSigAOAppendNewValues Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOAppendNewValues@20" (ByVal lBoardNumber As Long, ByRef piDataBuffer As Integer, ByVal lNumberOfValuesToAppend As Long, ByVal lExecutionMode As Long, ByRef plNumberOfValuesAppended As Long) As Long

Declare Function me4000MultiSigAOStop Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOStop@8" (ByVal lBoardNumber As Long, ByVal lStopMode As Long) As Long

Declare Function me4000MultiSigAOVoltToDigit Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOVoltToDigit@8" (ByVal dVolts As Double, ByRef piDigit As Integer) As Long

Declare Function me4000MultiSigAOReset Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOReset@4" (ByVal lBoardNumber As Long) As Long

Declare Function me4000MultiSigAOGetStatus Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOGetStatus@12" (ByVal lBoardNumber As Long, ByVal lWaitIdle As Long, ByRef plStatus As Long) As Long

Declare Function me4000MultiSigAOClose Lib "me4000Ex.dll" Alias "_me4000VB_MultiSigAOClose@4" (ByVal lBoardNumber As Long) As Long





