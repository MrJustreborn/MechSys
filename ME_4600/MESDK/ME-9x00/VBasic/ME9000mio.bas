Attribute VB_Name = "Declarations"
' Constants used by the API

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                             ME9000MIO_ Interface                               |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                              General Global Consts                            |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

' Maximum number of boards supported
Global Const ME9000MIO_MAX_DEVICES = 32

' Define for the return value from an API function that is executed
' successfully
Global Const ME9000MIO_NO_ERROR = &H0

' Define for a pointer or callback-function parameter which is reserved or not
' used in a particular context
Global Const ME9000MIO_POINTER_NOT_USED = 0

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                        Global Consts for Error Routines                       |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Global Const ME9000MIO_ERROR_DEFAULT_PROC_ENABLE = &H10101
Global Const ME9000MIO_ERROR_DEFAULT_PROC_DISABLE = &H10102

' The user error function passed to  me9000mioErrorSetUserProc should have the
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
'                        Global Consts for DIO Routines                         |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

'Bit number for me9000mioDIOConfig - Parameter uiBitNumber
Global Const ME9000MIO_DIO_LINE_0 = 0
Global Const ME9000MIO_DIO_LINE_1 = 1
Global Const ME9000MIO_DIO_LINE_2 = 2
Global Const ME9000MIO_DIO_LINE_3 = 3
Global Const ME9000MIO_DIO_LINE_4 = 4
Global Const ME9000MIO_DIO_LINE_5 = 5
Global Const ME9000MIO_DIO_LINE_6 = 6
Global Const ME9000MIO_DIO_LINE_7 = 7

'Direction for me9000mioDIOConfig - Parameter iDirection
Global Const ME9000MIO_DIO_OUTPUT = &H20101
Global Const ME9000MIO_DIO_INPUT = &H20102

'Polarity for me9000mioDIOConfig - Parameter iInvert
Global Const ME9000MIO_DIO_INV_DISABLE = &H20201
Global Const ME9000MIO_DIO_INV_ENABLE = &H20202

'Interrupt status for me9000mioDIOConfig - Parameter iInterrupt
Global Const ME9000MIO_DIO_INT_DISABLE = &H20301
Global Const ME9000MIO_DIO_INT_ENABLE = &H20302

'Output status for me9000mioDIOOutput - Parameter iOutputMode
Global Const ME9000MIO_DIO_OUTPUT_DISABLE = &H20401
Global Const ME9000MIO_DIO_OUTPUT_ENABLE = &H20402

' The DIO callback function passed to me9000mioDIOSetCallback should have
' the following form:
'
' Public Sub DIOCallback(ByVal lCallbackContext As Long)
'
' where lCallbackContext is the callback context parameter previously passed to
' me9000mioDIOSetCallback
'

'-------------------------------------------------------------------------------|
'                                                                               |
'                        Global Consts for Counter Routines                     |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

'Trigger modus for me9000mioCntConfig - Parameter iRetrigger
Global Const ME9000MIO_CNT_RETRIGGER_DISABLE = &H30101
Global Const ME9000MIO_CNT_RETRIGGER_ENABLE = &H30102

'MIO Pin 0 event status for me9000mioCntConfig - Parameter iCntEvent
Global Const ME9000MIO_CNT_EVENT_DISABLE = &H30201
Global Const ME9000MIO_CNT_EVENT_ENABLE = &H30202

'Clock source for me9000mioCntConfig - Parameter iClockSource
Global Const ME9000MIO_CNT_CLOCK_INTERNAL = &H30301
Global Const ME9000MIO_CNT_CLOCK_EXTERNAL = &H30302

'Interrupt status for me9000mioCntConfig - Parameter iInterrupt
Global Const ME9000MIO_CNT_INT_DISABLE = &H30401
Global Const ME9000MIO_CNT_INT_ENABLE = &H30402

' The Cnt callback function passed to me9000mioCntConfig should have
' the following form:
'
' Public Sub CntCallback(ByVal lCallbackContext As Long)
'
' where lCallbackContext is the callback context parameter previously passed to
' me9000mioCntConfig
'


'Note, that string arguments only work with initialized string variables
'      Dim gsTextBuffer As String * 256 or alternatively  sBuffer = String(256, Chr(0))
'-------------------------------------------------------------------------------------------

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                             ME9000mio Interface                               |
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

Declare Function me9000mioErrorSetDefaultProc Lib "me9000mioEx.dll" Alias "_me9000mioVB_ErrorSetDefaultProc@4" (ByVal lDefaultProcStatus As Long) As Long

Declare Function me9000mioErrorSetUserProc Lib "me9000mioEx.dll" Alias "_me9000mioVB_ErrorSetUserProc@4" (ByVal pErrorProc As Long) As Long

Declare Function me9000mioErrorGetMessage Lib "me9000mioEx.dll" Alias "_me9000mioVB_ErrorGetMessage@12" (ByVal lErrorCode As Long, ByVal pcBuffer As String, ByVal lBufferSize As Long) As Long

Declare Function me9000mioErrorGetLastMessage Lib "me9000mioEx.dll" Alias "_me9000mioVB_ErrorGetLastMessage@8" (ByVal pcBuffer As String, ByVal lBufferSize As Long) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                               Version Routines                                |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me9000mioGetDLLVersion Lib "me9000mioEx.dll" Alias "_me9000mioVB_GetDLLVersion@4" (ByRef plVersion As Long) As Long

Declare Function me9000mioGetDriverVersion Lib "me9000mioEx.dll" Alias "_me9000mioVB_GetDriverVersion@4" (ByRef plVersion As Long) As Long

Declare Function me9000mioGetBoardCount Lib "me9000mioEx.dll" Alias "_me9000mioVB_GetBoardCount@4" (ByRef pCount As Long) As Long

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

Declare Function me9000mioGetBoardVersion Lib "me9000mioEx.dll" Alias "_me9000mioVB_GetBoardVersion@8" (ByVal lBoardNumber As Long, ByRef piVersion As Integer) As Long

Declare Function me9000mioGetSerialNumber Lib "me9000mioEx.dll" Alias "_me9000mioVB_GetSerialNumber@8" (ByVal lBoardNumber As Long, ByRef plSeriakNumber As Long) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                               DIO Routines                                    |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me9000mioDIOOpen Lib "me9000mioEx.dll" Alias "_me9000mioVB_DIOOpen@4" (ByVal lBoardNumber As Long) As Long

Declare Function me9000mioDIOReset Lib "me9000mioEx.dll" Alias "_me9000mioVB_DIOReset@4" (ByVal lBoardNumber As Long) As Long

Declare Function me9000mioDIOConfig Lib "me9000mioEx.dll" Alias "_me9000mioVB_DIOConfig20" (ByVal lBoardNumber As Long, ByVal lBitNumber As Long, ByVal lDirection As Long, ByVal lInvert As Long, ByVal lInterrupt As Long) As Long
    
Declare Function me9000mioDIOGetBit Lib "me9000mioEx.dll" Alias "_me9000mioVB_DIOGetBit@12" (ByVal lBoardNumber As Long, ByVal lBitNumber As Long, ByRef plBitValue As Long) As Long

Declare Function me9000mioDIOSetBit Lib "me9000mioEx.dll" Alias "_me9000mioVB_DIOSetBit@12" (ByVal lBoardNumber As Long, ByVal lBitNumber As Long, ByVal lBitValue As Long) As Long

Declare Function me9000mioDIOGetByte Lib "me9000mioEx.dll" Alias "_me9000mioVB_DIOGetByte@8" (ByVal lBoardNumber As Long, ByRef pbByteValue As Byte) As Long

Declare Function me9000mioDIOSetByte Lib "me9000mioEx.dll" Alias "_me9000mioVB_DIOSetByte@8" (ByVal lBoardNumber As Long, ByVal bByteValue) As Long

Declare Function me9000mioDIOOutput Lib "me9000mioEx.dll" Alias "_me9000mioVB_DIOOutput@12" (ByVal lBoardNumber As Long, ByVal lBitNumber As Long, ByVal lOutputMode As Long) As Long

Declare Function me9000mioDIOSetCallback Lib "me9000mioEx.dll" Alias "_me9000mioVB_DIOSetCallback@12" (ByVal lBoardNumber As Long, ByVal pIRQProc As Long, ByVal lIRQContext As Long) As Long

Declare Function me9000mioDIOGetIrqCount Lib "me9000mioEx.dll" Alias "_me9000mioVB_DIOGetIrqCount@8" (ByVal lBoardNumber As Long, ByRef plCount As Long) As Long

Declare Function me9000mioDIOClose Lib "me9000mioEx.dll" Alias "_me9000mioVB_DIOClose@4" (ByVal lBoardNumber As Long) As Long

'*------------------------------------------------------------------------------+
'-------------------------------------------------------------------------------|
'                                                                               |
'                               Counter Routines                                |
'                                                                               |
'-------------------------------------------------------------------------------|
'------------------------------------------------------------------------------*/

Declare Function me9000mioCntOpen Lib "me9000mioEx.dll" Alias "_me9000mioVB_CntOpen@4" (ByVal lBoardNumber As Long) As Long

Declare Function me9000mioCntReset Lib "me9000mioEx.dll" Alias "_me9000mioVB_CntReset@4" (ByVal lBoardNumber As Long) As Long

Declare Function me9000mioCntConfig Lib "me9000mioEx.dll" Alias "_me9000mioVB_CntConfig@28" (ByVal lBoardNumber As Long, ByVal lRetrigger As Long, ByVal lCntEvent As Long, ByVal lClockSource As Long, ByVal lInterrupt As Long, ByVal pIRQProc As Long, ByVal lIRQContext As Long) As Long

Declare Function me9000mioCntWrite Lib "me9000mioEx.dll" Alias "_me9000mioVB_CntWrite@8" (ByVal lBoardNumber As Long, ByVal lValue) As Long

Declare Function me9000mioCntStart Lib "me9000mioEx.dll" Alias "_me9000mioVB_CntStart@4" (ByVal lBoardNumber As Long) As Long

Declare Function me9000mioVBCntRead Lib "me9000mioEx.dll" Alias "_me9000mioVB_CntRead@8" (ByVal lBoardNumber As Long, ByRef plValue As Long) As Long

Declare Function me9000mioCntStop Lib "me9000mioEx.dll" Alias "_me9000mioVB_CntStop@4" (ByVal lBoardNumber As Long) As Long

Declare Function me9000mioCntGetIrqCount Lib "me9000mioEx.dll" Alias "_me9000mioVB_CntGetIrqCount@8" (ByVal lBoardNumber As Long, ByRef lCount As Long) As Long

Declare Function me9000mioCntClose Lib "me9000mioEx.dll" Alias "_me9000mioVB_CntClose@4" (ByVal lBoardNumber As Long) As Long

