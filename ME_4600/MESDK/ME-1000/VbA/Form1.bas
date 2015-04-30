Attribute VB_Name = "Form1"
'Attribute VB_Name = "Declarations"'
Option Explicit

' General Routines
Declare Function me1000GetBoardVersion Lib "me1000.dll" Alias "_VBme1000GetBoardVersion@8" (ByVal iBoardNumber As Long, ByRef iVersion As Long) As Long
Declare Function me1000GetDLLVersion Lib "me1000.dll" Alias "_VBme1000GetDLLVersion@0" () As Long
Declare Function me1000GetDriverVersion Lib "me1000.dll" Alias "_VBme1000GetDriverVersion@4" (ByRef iDriverVersion As Long) As Long
Declare Function me1000GetSerialNumber Lib "me1000.dll" Alias "_VBme1000GetSerialNumber@8" (ByVal iBoardNumber As Long, ByRef iSerialNumber As Long) As Long
Declare Function me1000ReadUserString Lib "me1000.dll" Alias "_VBme1000ReadUserString@12" (ByVal iBoardNumber As Long, ByVal cUserText As String, ByVal iMaxString As Long) As Long
Declare Function me1000WriteUserString Lib "me1000.dll" Alias "_VBme1000WriteUserString@8" (ByVal iBoardNumber As Long, ByVal cUserText As String) As Long
Declare Function me1000GetDrvErrMess Lib "me1000.dll" Alias "_VBme1000GetDrvErrMess@8" (ByVal cErrortext As String, ByVal iBufferSize As Long) As Long

' Digital I/O Functions
Declare Function me1000DIOSetPortDirection Lib "me1000.dll" Alias "_VBme1000DIOSetPortDirection@12" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal iDirection As Long) As Long
Declare Function me1000DIOReset Lib "me1000.dll" Alias "_VBme1000DIOReset@4" (ByVal iBoardNumber As Long) As Long

Declare Function me1000DIGetBit Lib "me1000.dll" Alias "_VBme1000DIGetBit@16" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal iBitNo As Long, ByRef iValue As Long) As Long
Declare Function me1000DIGetByte Lib "me1000.dll" Alias "_VBme1000DIGetByte@16" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal iByteNo As Long, ByRef iValue As Long) As Long
Declare Function me1000DIGetWord Lib "me1000.dll" Alias "_VBme1000DIGetWord@16" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal iWordNo As Long, ByRef iValue As Long) As Long
Declare Function me1000DIGetLong Lib "me1000.dll" Alias "_VBme1000DIGetLong@12" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByRef iValue As Long) As Long

Declare Function me1000DOSetBit Lib "me1000.dll" Alias "_VBme1000DOSetBit@16" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal iBitNo As Long, ByVal iValue As Long) As Long
Declare Function me1000DOSetByte Lib "me1000.dll" Alias "_VBme1000DOSetByte@16" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal iByteNo As Long, ByVal iValue As Long) As Long
Declare Function me1000DOSetWord Lib "me1000.dll" Alias "_VBme1000DOSetWord@16" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal iWordNo As Long, ByVal iValue As Long) As Long
Declare Function me1000DOSetLong Lib "me1000.dll" Alias "_VBme1000DOSetLong@12" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal iValue As Long) As Long



' Maximum number of ME1000 Boards
Global Const ME_MAX_DEVICES = 32

' ME1000 Device IDs
Global Const ME1000A_PCI_DEV_ID = &H100A
Global Const ME1000B_PCI_DEV_ID = &H100B

' port direction
Global Const MEINPUT = 0
Global Const MEOUTPUT = 1

' port identifier
Global Const PORTA = 0
Global Const PORTB = 1
Global Const PORTC = 2
Global Const PORTD = 3

' word identifier
Global Const WORD_0 = 0
Global Const WORD_1 = 1

' byte identifier
Global Const BYTE_0 = 0
Global Const BYTE_1 = 1
Global Const BYTE_2 = 2
Global Const BYTE_3 = 3

' bit identifier
Global Const BIT_0 = 0
Global Const BIT_1 = 1
Global Const BIT_2 = 2
Global Const BIT_3 = 3
Global Const BIT_4 = 4
Global Const BIT_5 = 5
Global Const BIT_6 = 6
Global Const BIT_7 = 7
Global Const BIT_8 = 8
Global Const BIT_9 = 9
Global Const BIT_10 = 10
Global Const BIT_11 = 11
Global Const BIT_12 = 12
Global Const BIT_13 = 13
Global Const BIT_14 = 14
Global Const BIT_15 = 15
Global Const BIT_16 = 16
Global Const BIT_17 = 17
Global Const BIT_18 = 18
Global Const BIT_19 = 19
Global Const BIT_20 = 20
Global Const BIT_21 = 21
Global Const BIT_22 = 22
Global Const BIT_23 = 23
Global Const BIT_24 = 24
Global Const BIT_25 = 25
Global Const BIT_26 = 26
Global Const BIT_27 = 27
Global Const BIT_28 = 28
Global Const BIT_29 = 29
Global Const BIT_30 = 30
Global Const BIT_31 = 31




Sub me1000()

    'DEMO for ME 1000

    Dim board As Long               'number of board'
    Dim register_set As Long        'number of register set'
    Dim retval As Long              'Return value of the function'
    Dim dll As Long                 'DLL version'
    Dim iDrvVersion As Long
    Dim iBoardVersion As Long
    Dim iSerial As Long
    Dim val_32 As Long              '32 bit input/output value'
    Dim errtext As String * 255     'String for error'
    Dim bitn As Long                'number of bit'
    
    'default settings'
    board = 0
    retval = 0
    dll = 0
    val_32 = 0
    errtext = ""
    bitn = 0
    
    'String for TextBox
    Dim text_box_str As String
    
    'determine dll version
    dll = me1000GetDLLVersion()
    
    'MsgBox "ME1000 DLL Version: " + Hex(me1000GetDLLVersion()), vbInformation
    text_box_str = "DLL Version: "
    text_box_str = text_box_str & Hex(dll)
    text_box_str = text_box_str & vbCrLf
    
    retval = me1000GetDriverVersion(iDrvVersion)
    ' On every function call you have to check the error code on the
    ' value retval. For clarity and simplicity, this is not done here
    text_box_str = text_box_str & "Driver Version: "
    text_box_str = text_box_str & Hex(iDrvVersion)
    text_box_str = text_box_str & vbCrLf
    
    'determine board
    retval = me1000GetBoardVersion(board, iBoardVersion)
    text_box_str = text_box_str & "Board Version: "
    text_box_str = text_box_str & Hex(iBoardVersion)
    text_box_str = text_box_str & vbCrLf
   
    retval = me1000GetSerialNumber(board, iSerial)
    text_box_str = text_box_str & "Serial Number: "
    text_box_str = text_box_str & Hex(iSerial)
    text_box_str = text_box_str & vbCrLf
    
    'Display string
    MsgBox text_box_str, vbInformation
    
    retval = me1000DIOReset(board)
    MsgBox "Be careful not to cause a short circuit! Do not connect a output with a output!", vbInformation
   
   
    retval = me1000DIOSetPortDirection(board, PORTA, MEOUTPUT)
    retval = me1000DOSetByte(board, PORTA, BYTE_0, 255)
    retval = me1000DOSetByte(board, PORTA, BYTE_0, 0)
   
End Sub

