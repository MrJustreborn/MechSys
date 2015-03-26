Attribute VB_Name = "Declarations"

Declare Function me1400GetDLLVersion Lib "me1400.dll" Alias "_VBme1400GetDLLVersion@0" () As Long
Declare Function me1400GetDriverVersion Lib "me1400.dll" Alias "_VBme1400GetDriverVersion@4" (ByRef iDriverVersion As Long) As Long
Declare Function me1400GetBoardVersion Lib "me1400.dll" Alias "_VBme1400GetBoardVersion@8" (ByVal iBoardNumber As Long, ByRef iVersion As Long) As Long
Declare Function me1400GetSerialNumber Lib "me1400.dll" Alias "_VBme1400GetSerialNumber@8" (ByVal iBoardNumber As Long, ByRef iSerialNumber As Long) As Long
Declare Function me1400GetDevInfo Lib "me1400.dll" Alias "_VBme1400GetDevInfo@8" (ByVal iBoardNumber As Long, DevInfo As DeviceInfoStruct) As Long
Declare Function me1400GetDrvErrMess Lib "me1400.dll" Alias "_VBme1400GetDrvErrMess@4" (ByVal cErrortext As String) As Long

Declare Function me1400EnableInt Lib "me1400.dll" Alias "_VBme1400EnableInt@12" (ByVal lBoardNumber As Long, ByVal pCallBack As Long, ByVal lServiceNo As Long) As Long
Declare Function me1400DisableInt Lib "me1400.dll" Alias "_VBme1400DisableInt@8" (ByVal lBoardNumber As Long, ByVal lServiceNo As Long) As Long
Declare Function me1400GetIrqCnt Lib "me1400.dll" Alias "_VBme1400GetIrqCnt@8" (ByVal iBoardNumber As Long, ByRef iIrqCnt As Long) As Long

Declare Function me1400InitModeTimerA Lib "me1400.dll" Alias "_VBme1400InitModeTimerA@8" (ByVal iBoardNumber As Long, ByVal CtrlWordA As Long) As Long
Declare Function me1400InitModeTimerB Lib "me1400.dll" Alias "_VBme1400InitModeTimerB@8" (ByVal iBoardNumber As Long, ByVal CtrlWordB As Long) As Long
Declare Function me1400SetMultifunctionPin Lib "me1400.dll" Alias "_VBme1400SetMultifunctionPin@8" (ByVal iBoardNumber As Long, ByVal MultiPin As Long) As Long

Declare Function me1400CntWrite Lib "me1400.dll" Alias "_VBme1400CntWrite@16" (ByVal iBoardNumber As Long, ByVal iCounterNo As Long, ByVal iMode As Long, ByVal iValue As Long) As Long
Declare Function me1400CntRead Lib "me1400.dll" Alias "_VBme1400CntRead@12" (ByVal iBoardNumber As Long, ByVal iCounterNo As Long, ByRef iValue As Long) As Long
Declare Function me1400CntInitSrc Lib "me1400.dll" Alias "_VBme1400CntInitSrc@12" (ByVal iBoardNumber As Long, ByVal Counter As Long, ByVal CounterSource As Long) As Long

/*==============================================================*/
Declare Function me1400CntPWMStart Lib "me1400.dll" Alias "_VBme1400CntPWMStart@20"(ByVal iBoardNumber As Long, ByVal iDeviceNumber As Long, ByVal iClockSource As Long, ByVal iPrescaler As Long, ByVal iDutyCycle As Long) As Long
Declare Function me1400CntPWMStop Lib "me1400.dll" Alias "_VBme1400CntPWMStop@8"(ByVal iBoardNumber As Long, ByVal iDeviceNumber As Long) As Long
/*==============================================================*/

Declare Function me1400DIOSetPortDirection Lib "me1400.dll" Alias "_VBme1400DIOSetPortDirection@12" (ByVal iBoardNumber As Long, ByVal iPortNo As Long, ByVal iDir As Long) As Long
Declare Function me1400DIOSetMode Lib "me1400.dll" Alias "_VBme1400DIOSetMode@12" (ByVal iBoardNumber As Long, ByVal iPIONo As Long, ByVal iMode As Long) As Long

Declare Function me1400DIGetBit Lib "me1400.dll" Alias "_VBme1400DIGetBit@16" (ByVal iBoardNumber As Long, ByVal iPortNo As Long, ByVal iBitNo As Long, ByRef iBitValue As Long) As Long
Declare Function me1400DIGetByte Lib "me1400.dll" Alias "_VBme1400DIGetByte@12" (ByVal iBoardNumber As Long, ByVal iPortNo As Long, ByRef iValue As Long) As Long

Declare Function me1400DOSetBit Lib "me1400.dll" Alias "_VBme1400DOSetBit@16" (ByVal BoardNumber As Long, ByVal iPortNo As Long, ByVal iBitNo As Long, ByVal iBitValue As Long) As Long
Declare Function me1400DOSetByte Lib "me1400.dll" Alias "_VBme1400DOSetByte@12" (ByVal BoardNumber As Long, ByVal iPortNo As Long, ByVal iValue As Long) As Long

Declare Function me1400ResetBoard Lib "me1400.dll" Alias "_VBme1400ResetBoard@4" (ByVal Boardnumber As Long) As Long
Declare Function me1400InitBoard Lib "me1400.dll" Alias "_VBme1400InitBoard@4" (ByVal Boardnumber As Long) As Long


