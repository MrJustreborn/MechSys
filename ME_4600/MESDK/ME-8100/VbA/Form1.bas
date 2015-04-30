Attribute VB_Name = "Form1"
'Attribute VB_Name = "Declarations"'
Option Explicit

Declare Function me8100GetDLLVersion Lib "me8100Dll.dll" Alias "__me8100GetDLLVersion@0" () As Long
Declare Function me8100GetBoardVersion Lib "me8100Dll.dll" Alias "__me8100GetBoardVersion@8" (ByVal iBoardNumber As Long, ByRef iVersion As Long) As Long
Declare Function me8100PROMVersion Lib "me8100Dll.dll" Alias "__me8100PROMVersion@8" (ByVal iBoardNumber As Long, ByRef iVersion As Long) As Long

Declare Function me8100GetDrvErrMess Lib "me8100Dll.dll" Alias "__me8100GetDrvErrMess@8" (ByVal cErrortext As String, ByVal iBufferSize As Long) As Long

Declare Function me8100DIOSetTristateON Lib "me8100Dll.dll" Alias "__me8100DIOSetTristateON@8" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long) As Long
Declare Function me8100DIOSetTristateOFF Lib "me8100Dll.dll" Alias "__me8100DIOSetTristateON@8" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long) As Long

Declare Function me8100DIGetBit Lib "me8100Dll.dll" Alias "__me8100DIGetBit@16" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long, ByVal iBitNo As Long, ByRef iBitValue As Long) As Long
Declare Function me8100DIGetWord Lib "me8100Dll.dll" Alias "__me8100DIGetWord@12" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long, ByRef iValue As Long) As Long

Declare Function me8100DOSetBit Lib "me8100Dll.dll" Alias "__me8100DOSetBit@16" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long, ByVal iBitNo As Long, ByVal iBitValue As Long) As Long
Declare Function me8100DOSetWord Lib "me8100Dll.dll" Alias "__me8100DOSetWord@12" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long, ByVal iValue As Long) As Long

Declare Function me8100WriteUserString Lib "me8100Dll.dll" Alias "__me8100WriteUserString@8" (ByVal iBoardNumber As Long, ByVal cUserText As String) As Long
Declare Function me8100ReadUserString Lib "me8100Dll.dll" Alias "__me8100ReadUserString@12" (ByVal iBoardNumber As Long, ByVal cUserText As String, ByVal iMaxString As Long) As Long

Declare Function me8100CntWrite Lib "me8100Dll.dll" Alias "__me8100CntWrite@16" (ByVal iBoardNumber As Long, ByVal iCounter As Long, ByVal iMode As Long, ByVal iValue As Long) As Long
Declare Function me8100CntRead Lib "me8100Dll.dll" Alias "__me8100CntRead@12" (ByVal iBoardNumber As Long, ByVal iCounter As Long, ByRef iValue As Long) As Long

Declare Function me8100SetSinkSourceMode Lib "me8100Dll.dll" Alias "__me8100SetSinkSourceMode@12" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long, ByVal iMode As Long) As Long




' Maximum number of ME8100 Boards

Global Const ME8100_MAX_DEVICES = 32

' Register sets
Global Const REGISTER_SET_A = 0
Global Const REGISTER_SET_B = 1

' Source/Sink Mode
Global Const SINK_MODE = 0
Global Const SOURCE_MODE = 1




Sub me8100()

    'DEMO for ME 8100
    'The file ME8100DLL.LIB was included

    Dim board As Long               'number of board'
    Dim register_set As Long        'number of register set'
    Dim retval As Long              'Return value of the function'
    Dim dll As Long                 'DLL version'
    Dim val_32 As Long              '32 bit input/output value'
    Dim errtext As String * 255     'String for error'
    Dim bitn As Long                'number of bit'
    Dim version As Long             ''
    
    'default settings'
    board = 0
    register_set = REGISTER_SET_A
    retval = 0
    dll = 0
    val_32 = 0
    errtext = ""
    bitn = 0
    
    'String for TextBox
    Dim text_box_str As String
    
    'determine dll version
    dll = me8100GetDLLVersion()
    
    text_box_str = "DLL Version: "
    text_box_str = text_box_str & Hex(dll)
    text_box_str = text_box_str & vbCrLf & vbCrLf
    
    'determine board
    retval = me8100PROMVersion(board, version)

    text_box_str = text_box_str & "PROM Version: "
    text_box_str = text_box_str & Hex(retval)
    text_box_str = text_box_str & vbCrLf & vbCrLf
    
    'Set Tristate ON
    retval = me8100DIOSetTristateON(board, register_set)
    
    'Set SOURCE mode
    retval = me8100SetSinkSourceMode(board, register_set, SOURCE_MODE)
    
    'Write
    val_32 = &HABCD&
    retval = me8100DOSetWord(board, register_set, val_32)
 
    text_box_str = text_box_str & "Write word: "
    text_box_str = text_box_str & Hex(val_32)
    text_box_str = text_box_str & vbCrLf & vbCrLf
    
   'Read
    val_32 = &HFFFF&
    retval = me8100DIGetWord(board, register_set, val_32)
    
    text_box_str = text_box_str & "Read word: "
    text_box_str = text_box_str & Hex(val_32)
    text_box_str = text_box_str & vbCrLf & vbCrLf
    
    'Display string
    MsgBox text_box_str, vbInformation

End Sub

