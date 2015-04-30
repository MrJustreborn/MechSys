Attribute VB_Name = "Modul1"
' File meInc.bas'
' Include File for 32-bit Driver DLL'


Rem The module "me8100Inc.bas" allows the DLL "me8100.dll to be used

Rem The follow steps describe how to include the module in your project

Rem - Start VB
Rem - Open  FILE -> NEW PROJECT
Rem - The compiler creates the form "FORM1"
Rem - Use the menu list "FILE -> ADD FILE"
Rem - Choose the directory in which this file, "me8100Inc.bas", can be found.
Rem - double click on the file "me8100Inc.bas"
Rem - the file should be shown in the project overview window
Rem - The "me8100.dll" file can now be used in the project

Rem Die Funktionen me8100EnableInt, me8100DisableInt, me8100DIGetIntStatus, me8100DIOSetIntMode,
Rem me8100DIOSetPattern, me8100DIOSetMask. _me8100GetIrqCnt and _me8100GetDevInfo werden vorläufig
Rem unter Visual Basic nicht unterstützt.

Declare Function me8100GetDLLVersion Lib "me8100.dll" Alias "_VBme8100GetDLLVersion@0" () As Long
Declare Function me8100GetBoardVersion Lib "me8100.dll" Alias "_VBme8100GetBoardVersion@8" (ByVal iBoardNumber As Long, ByRef iVersion As Long) As Long
Declare Function me8100PROMVersion Lib "me8100.dll" Alias "_VBme8100PROMVersion@8" (ByVal iBoardNumber As Long, ByRef iVersion As Long) As Long

Declare Function me8100GetDrvErrMess Lib "me8100.dll" Alias "_VBme8100GetDrvErrMess@8" (ByVal cErrortext As String, ByVal iBufferSize As Long) As Long

Declare Function me8100DIOSetTristateON Lib "me8100.dll" Alias "_VBme8100DIOSetTristateON@8" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long) As Long
Declare Function me8100DIOSetTristateOFF Lib "me8100.dll" Alias "_VBme8100DIOSetTristateOFF@8" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long) As Long

Declare Function me8100DIGetBit Lib "me8100.dll" Alias "_VBme8100DIGetBit@16" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long, ByVal iBitNo As Long, ByRef iBitValue As Long) As Long
Declare Function me8100DIGetWord Lib "me8100.dll" Alias "_VBme8100DIGetWord@12" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long, ByRef iValue As Long) As Long

Declare Function me8100DOSetBit Lib "me8100.dll" Alias "_VBme8100DOSetBit@16" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long, ByVal iBitNo As Long, ByVal iBitValue As Long) As Long
Declare Function me8100DOSetWord Lib "me8100.dll" Alias "_VBme8100DOSetWord@12" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long, ByVal iValue As Long) As Long

Declare Function me8100WriteUserString Lib "me8100.dll" Alias "_VBme8100WriteUserString@8" (ByVal iBoardNumber As Long, ByVal cUserText As String) As Long
Declare Function me8100ReadUserString Lib "me8100.dll" Alias "_VBme8100ReadUserString@12" (ByVal iBoardNumber As Long, ByVal cUserText As String, ByVal iMaxString As Long) As Long

Declare Function me8100CntWrite Lib "me8100.dll" Alias "_VBme8100CntWrite@16" (ByVal iBoardNumber As Long, ByVal iCounter As Long, ByVal iMode As Long, ByVal iValue As Long) As Long
Declare Function me8100CntRead Lib "me8100.dll" Alias "_VBme8100CntRead@12" (ByVal iBoardNumber As Long, ByVal iCounter As Long, ByRef iValue As Long) As Long

Declare Function me8100SetSinkSourceMode Lib "me8100.dll" Alias "_VBme8100SetSinkSourceMode@12" (ByVal iBoardNumber As Long, ByVal iRegisterSet As Long, ByVal iMode As Long) As Long
