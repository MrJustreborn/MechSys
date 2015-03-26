Attribute VB_Name = "Modul1"
' File me9x.bas'
' Include File for 32-bit Driver DLL me9x_32.dll'


Rem The module "me9x.bas" allows the DLL "me9x_32.dll to be used

Rem The follow steps describe how to include the module in your project

Rem - Start VB
Rem - Open  FILE -> NEW PROJECT
Rem - The compiler creates the form "FORM1"
Rem - Use the menu list "FILE -> ADD FILE"
Rem - The file to be included "me9x.bas" is found in the path "C:\Meilhaus\ME-9x\".
Rem - double click on the file "me9x"
Rem - the file should be shown in the project overview window
Rem - The "me9x_32.dll" file can now be used in the project


Declare Function me9xGetDLLVersion Lib "me9x_32" Alias "_VBme9xGetDLLVersion@0" () As Long
Declare Function me9xGetBoardVersion Lib "me9x_32" Alias "_VBme9xGetBoardVersion@8" (ByVal iBoardNumber As Long, ByRef iVersion As Long) As Long
Declare Function me9xGetDrvErrMess Lib "me9x_32" Alias "_VBme9xGetDrvErrMess@4" (ByVal cErrortext As String) As Long

Declare Function me94DIGetBit Lib "me9x_32" Alias "_VBme94DIGetBit@12" (ByVal iBoardNumber As Long, ByVal iBitNo As Long, ByRef iBitValue As Long) As Long
Declare Function me96DIGetBit Lib "me9x_32" Alias "_VBme96DIGetBit@12" (ByVal iBoardNumber As Long, ByVal iBitNo As Long, ByRef iBitValue As Long) As Long
Declare Function me94DIGetByte Lib "me9x_32" Alias "_VBme94DIGetByte@12" (ByVal iBoardNumber As Long, ByVal iPortNo As Long, ByRef iValue As Long) As Long
Declare Function me96DIGetByte Lib "me9x_32" Alias "_VBme96DIGetByte@12" (ByVal iBoardNumber As Long, ByVal iPortNo As Long, ByRef iValue As Long) As Long

Declare Function me95DOSetBit Lib "me9x_32" Alias "_VBme95DOSetBit@12" (ByVal BoardNumber As Long, ByVal iBitNo As Long, ByVal iBitValue As Long) As Long
Declare Function me96DOSetBit Lib "me9x_32" Alias "_VBme96DOSetBit@12" (ByVal BoardNumber As Long, ByVal iBitNo As Long, ByVal iBitValue As Long) As Long
Declare Function me95DOSetByte Lib "me9x_32" Alias "_VBme95DOSetByte@12" (ByVal BoardNumber As Long, ByVal iPortNo As Long, ByVal iValue As Long) As Long
Declare Function me96DOSetByte Lib "me9x_32" Alias "_VBme96DOSetByte@12" (ByVal BoardNumber As Long, ByVal iPortNo As Long, ByVal iValue As Long) As Long


