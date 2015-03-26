Attribute VB_Name = "Modul1"
' File meInc.bas'
' Include File for 32-bit Driver DLL'

Rem Die Funktionen _meXXXXGetDevInfo werden vorläufig
Rem unter Visual Basic nicht unterstützt.
Rem Workaround: Man kann diese Structur auch als ein array of int sehen

' General Routines
Declare Function me1000GetBoardVersion Lib "me1000.dll" Alias "_VBme1000GetBoardVersion@8" (ByVal iBoardNumber As Long, ByRef iVersion As Long) As Long
Declare Function me1000GetDLLVersion Lib "me1000.dll" Alias "_VBme1000GetDLLVersion@0" () As Long
Declare Function me1000GetDriverVersion Lib "me1000.dll" Alias "_VBme1000GetDriverVersion@4" (ByRef iDriverVersion As Long) As Long
Declare Function me1000GetSerialNumber Lib "me1000.dll" Alias "_VBme1000GetSerialNumber@8" (ByVal iBoardNumber As Long, ByRef iSerialNumber As Long) As Long
Declare Function me1000GetDevInfo Lib "me1000.dll" Alias "_VBme1000GetDevInfo@8" (ByVal iBoardNumber As Long, DevInfo As DeviceInfoStruct) As Long
'Declare Function me1000ReadUserString Lib "me1000.dll" Alias "_VBme1000ReadUserString@12" (ByVal iBoardNumber As Long, ByVal cUserText As String, ByVal iMaxString As Long) As Long
'Declare Function me1000WriteUserString Lib "me1000.dll" Alias "_VBme1000WriteUserString@8" (ByVal iBoardNumber As Long, ByVal cUserText As String) As Long
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
