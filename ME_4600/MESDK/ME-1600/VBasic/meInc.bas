Attribute VB_Name = "Modul1"
' File meInc.bas'
' Include File for 32-bit Driver DLL'


' General Routines
Declare Function me1600GetBoardVersion Lib "me1600.dll" Alias "_VBme1600GetBoardVersion@8" (ByVal iBoardNumber As Long, ByRef iVersion As Long) As Long
Declare Function me1600GetDevInfo Lib "me1600.dll" Alias "_VBme1600GetDevInfo@8" (ByVal iBoardNumber As Long, DevInfo As DeviceInfoStruct) As Long
Declare Function me1600GetDLLVersion Lib "me1600.dll" Alias "_VBme1600GetDLLVersion@0" () As Long
Declare Function me1600GetDriverVersion Lib "me1600.dll" Alias "_VBme1600GetDriverVersion@4" (ByRef iDriverVersion As Long) As Long
Declare Function me1600GetSerialNumber Lib "me1600.dll" Alias "_VBme1600GetSerialNumber@8" (ByVal iBoardNumber As Long, ByRef iSerialNumber As Long) As Long
Declare Function me1600GetDrvErrMess Lib "me1600.dll" Alias "_VBme1600GetDrvErrMess@8" (ByVal cErrortext As String, ByVal iBufferSize As Long) As Long

' Analog Out Functions
Declare Function me1600AOResetAll Lib "me1600.dll" Alias "_VBme1600AOResetAll@4" (ByVal iBoardNumber As Long) As Long
Declare Function me1600AOSetCurrent Lib "me1600.dll" Alias "_VBme1600AOSetCurrent@16" (ByVal iBoardNumber As Long, ByVal iChannelNumber As Long, ByVal iCurrentMode As Long, ByVal iRange As Long) As Long
Declare Function me1600AOSetMode Lib "me1600.dll" Alias "_VBme1600AOSetMode@12" (ByVal iBoardNumber As Long, ByVal iChannelGroup As Long, ByVal iOutMode As Long) As Long
Declare Function me1600AOSetRange Lib "me1600.dll" Alias "_VBme1600AOSetRange@12" (ByVal iBoardNumber As Long, ByVal iChannelNumber As Long, ByVal iRange As Long) As Long
Declare Function me1600AOSingle Lib "me1600.dll" Alias "_VBme1600AOSingle@12" (ByVal iBoardNumber As Long, ByVal iChannelNumber As Long, ByVal sValue As Integer) As Long
Declare Function me1600AOUpdate Lib "me1600.dll" Alias "_VBme1600AOUpdate@8" (ByVal iBoardNumber As Long, ByVal iChannelGroup As Long) As Long
Declare Function me1600AOUpdateAll Lib "me1600.dll" Alias "_VBme1600AOUpdateAll@4" (ByVal iBoardNumber As Long) As Long
