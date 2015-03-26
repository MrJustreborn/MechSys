Attribute VB_Name = "Modul1"
' File meInc.bas'
' Include File for 32-bit Driver DLL'

Rem The module "me630Inc.bas" allows the DLL "me630.dll to be used
Rem The follow steps describe how to include the module in your project
Rem - Start VB
Rem - Open  FILE -> NEW PROJECT
Rem - The compiler creates the form "FORM1"
Rem - Use the menu list "FILE -> ADD FILE"
Rem - Choose the directory in which this file, "me630Inc.bas", can be found.
Rem - double click on the file "me630Inc.bas"
Rem - the file should be shown in the project overview window
Rem - The "me630.dll" file can now be used in the project

Rem Die Funktionen me630EnableInt, me630DisableInt, me630DIGetIntStatus, me630DIOSetIntMode,
Rem me630DIOSetPattern, me630DIOSetMask. _me630GetIrqCnt and _me630GetDevInfo werden vorläufig
Rem unter Visual Basic nicht unterstützt.

Declare Function me630GetDLLVersion Lib "me630.dll" Alias "_VBme630GetDLLVersion@0" () As Long
Declare Function me630GetBoardVersion Lib "me630.dll" Alias "_VBme630GetBoardVersion@8" (ByVal iBoardNumber As Long, ByRef iVersion As Long) As Long
Declare Function me630GetDevInfo Lib "me630.dll" Alias "_VBme630GetDevInfo@8" (ByVal iBoardNumber As Long, DevInfo As DeviceInfoStruct) As Long
Declare Function me630GetDriverVersion Lib "me630.dll" Alias "_VBme630GetDriverVersion@4" (ByRef iDriverVersion As Long) As Long
Declare Function me630GetSerialNumber Lib "me630.dll" Alias "_VBme630GetSerialNumber@8" (ByVal iBoardNumber As Long, ByRef iSerialNumber As Long) As Long

Declare Function me630ResetRelays Lib "me630.dll" Alias "_VBme630ResetRelays@4" (ByVal iBoardNumber As Long) As Long
Declare Function me630GetDrvErrMess Lib "me630.dll" Alias "_VBme630GetDrvErrMess@8" (ByVal cErrortext As String, ByVal iBufferSize As Long) As Long

Declare Function me630DIGetTTLBit Lib "me630.dll" Alias "_VBme630DIGetTTLBit@12" (ByVal iBoardNumber As Long, ByVal iBitNo As Long, ByRef iBitValue As Long) As Long
Declare Function me630DIGetTTLByte Lib "me630.dll" Alias "_VBme630DIGetTTLByte@8" (ByVal iBoardNumber As Long, ByRef iByteValue As Integer) As Long
Declare Function me630DIGetOptoBit Lib "me630.dll" Alias "_VBme630DIGetOptoBit@12" (ByVal iBoardNumber As Long, ByVal iBitNo As Long, ByRef iBitValue As Long) As Long
Declare Function me630DIGetOptoByte Lib "me630.dll" Alias "_VBme630DIGetOptoByte@8" (ByVal iBoardNumber As Long, ByRef iByteValue As Integer) As Long

Declare Function me630DOSetRelayBit Lib "me630.dll" Alias "_VBme630DOSetRelayBit@12" (ByVal iBoardNumber As Long, ByVal iBitNo As Long, ByVal iBitValue As Long) As Long
Declare Function me630DOSetRelayWord Lib "me630.dll" Alias "_VBme630DOSetRelayWord@8" (ByVal iBoardNumber As Long, ByVal iWordValue As Integer) As Long
Declare Function me630DOSetRelayWord Lib "me630.dll" Alias "_VBme630DOSetRelayWord@6" (ByVal iBoardNumber As Long, ByVal iWordValue As Integer) As Long
Declare Function me630DIGetRelayBit Lib "me630.dll" Alias "_VBme630DIGetRelayBit@12" (ByVal iBoardNumber As Long, ByVal iBitNo As Long, ByRef iBitValue As Long) As Long
Declare Function me630DIGetRelayWord Lib "me630.dll" Alias "_VBme630DIGetRelayWord@8" (ByVal iBoardNumber As Long, ByRef iWordValue As Integer) As Long

Declare Function me630DIOResetAll Lib "me630.dll" Alias "_VBme630DIOResetAll@4" (ByVal iBoardNumber As Long) As Long
Declare Function me630DIOConfig Lib "me630.dll" Alias "_VBme630DIOConfig@12" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal iPortDirectio As Long) As Long
Declare Function me630DIOGetBit Lib "me630.dll" Alias "_VBme630DIOGetBit@16" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal iBitNo As Long, ByRef iBitValue As Long) As Long
Declare Function me630DIOGetByte Lib "me630.dll" Alias "_VBme630DIOGetByte@12" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByRef bByteValue As Byte) As Long
Declare Function me630DIOSetBit Lib "me630.dll" Alias "_VBme630DIOSetBit@16" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal iBitNo As Long, ByVal iBitValue As Long) As Long
Declare Function me630DIOSetByte Lib "me630.dll" Alias "_VBme630DIOSetByte@12" (ByVal iBoardNumber As Long, ByVal iPortNumber As Long, ByVal bByteValue As byte) As Long

Declare Function me630WriteUserString Lib "me630.dll" Alias "_VBme630WriteUserString@8" (ByVal iBoardNumber As Long, ByVal cUserText As String) As Long
Declare Function me630ReadUserString Lib "me630.dll" Alias "_VBme630ReadUserString@12" (ByVal iBoardNumber As Long, ByVal cUserText As String, ByVal iMaxString As Long) As Long
