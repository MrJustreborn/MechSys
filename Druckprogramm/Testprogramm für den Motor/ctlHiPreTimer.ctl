VERSION 5.00
Begin VB.UserControl ctlHiPreTimer 
   CanGetFocus     =   0   'False
   ClientHeight    =   480
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   2355
   HasDC           =   0   'False
   InvisibleAtRuntime=   -1  'True
   Picture         =   "ctlHiPreTimer.ctx":0000
   ScaleHeight     =   480
   ScaleWidth      =   2355
End
Attribute VB_Name = "ctlHiPreTimer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'*********************************************************************
' High Precision Timer v1.20
' Copyright ©2002 by Sebastian Thomschke, All Rights Reserved.
' http://www.sebthom.de
'*********************************************************************
' If you like this code, please vote for it at Planet-Source-Code.com:
' http://www.planet-source-code.com/vb/scripts/ShowCode.asp?txtCodeId=34374&lngWId=1
' Thank you
'*********************************************************************
' You are free to use this code within your own applications, but you
' are expressly forbidden from selling or otherwise distributing this
' source code without prior written consent.
'*********************************************************************
' WARNING: ANY USE BY YOU IS AT YOUR OWN RISK. I provide this code
' "as is" without warranty of any kind, either express or implied,
' including but not limited to the implied warranties of
' merchantability and/or fitness for a particular purpose.
'*********************************************************************
Option Explicit


'*********************************************************************
' Private API Declarations
'*********************************************************************
Private Declare Function timeGetDevCaps Lib "winmm" _
   (lpTimeCaps As TIMECAPS, ByVal uSize As Long) _
   As Long
Private Type TIMECAPS
   MinResolution As Long
   MaxResolution As Long
End Type


Private Declare Function timeKillEvent Lib "winmm" _
   (ByVal uID As Long) _
   As Long
Private Declare Function timeSetEvent Lib "winmm" _
   (ByVal dwInterval As Long, ByVal dwResolution As Long, ByVal lpFunction As Long, ByVal dwUser As Long, ByVal dwFlags As Long) _
   As Long
Private Const TIME_CALLBACK_FUNCTION = &H0      'When the timer expires, Windows calls the function pointed to by the lpTimeProc parameter. This is the default.
Private Const TIME_CALLBACK_EVENT_SET = &H10    'When the timer expires, Windows calls theSetEvent function to set the event pointed to by the lpTimeProc parameter. The dwUser parameter is ignored.
Private Const TIME_CALLBACK_EVENT_PULSE = &H20  'When the timer expires, Windows calls thePulseEvent function to pulse the event pointed to by the lpTimeProc parameter. The dwUser parameter is ignored.
Private Const TIME_ONESHOT = 0
Private Const TIME_PERIODIC = 1


'*********************************************************************
' Private Constants
'*********************************************************************
Private Const dwInterval_Default = 1000
Private Const dwResolution_Default = 10000
Private Const Periodic_Default = False
Private Const Enabled_Default = False


'*********************************************************************
' Private Vars
'*********************************************************************
Private dwHandle As Long
Private dwInterval As Long
Private dwResolution As Long
Private dwResolutionMin As Long
Private dwResolutionMax As Long
Private IsPeriodic As Boolean
Private IsEnabled As Boolean


'*********************************************************************
' Public Vars
'*********************************************************************
Public Tag As String


'*********************************************************************
' Public Vars
'*********************************************************************
Public Event Timer()


'*********************************************************************
' Public Properties
'*********************************************************************
Public Property Get hwnd() As Long
   hwnd = UserControl.hwnd
End Property

Public Property Get Enabled() As Boolean
   Enabled = IsEnabled
End Property

Public Property Let Enabled(EEnabled As Boolean)
   If EEnabled Then
      If Ambient.UserMode Then
         IsEnabled = StartTimer
      Else
         IsEnabled = True
      End If
   Else
      IsEnabled = Not StopTimer
   End If
End Property

Public Property Let Periodic(ByVal PPeriodic As Boolean)
   IsPeriodic = PPeriodic
End Property

Public Property Get Periodic() As Boolean
   Periodic = IsPeriodic
End Property

Public Property Get Interval() As Long
   Interval = dwInterval
End Property

Public Property Let Interval(ByVal Milliseconds As Long)

   If Milliseconds < 1 Then Milliseconds = 1
   dwInterval = Milliseconds
   
   ' restart if the timer is running
   Enabled = Enabled
End Property

Public Property Get Resolution() As Long
   Resolution = dwResolution
End Property

Public Property Let Resolution(ByVal Milliseconds As Long)
   ' description from MSDN: http://msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/mmfunc_5378.asp
   ' dwResolution of the timer event, in milliseconds.
   ' The dwResolution increases with smaller values; a dwResolution of 0 indicates
   ' periodic events should occur with the greatest possible accuracy.
   ' To reduce system overhead, however, you should use the maximum value
   ' appropriate for your application.
   If Milliseconds < dwResolutionMin Then
      dwResolution = dwResolutionMin
   ElseIf Milliseconds > dwResolutionMax Then
      dwResolution = dwResolutionMax
   Else
      dwResolution = Milliseconds
   End If
End Property


'*********************************************************************
' Public Methods
'
' all public methods return True on success and False on failure
'*********************************************************************
Private Function StartTimer() As Boolean
   StartTimer = False

   StopTimer
   dwHandle = timeSetEvent( _
      dwInterval, _
      dwResolution, _
      AddressOf TimerCallbackProc, _
      Me.hwnd, _
      IIf(IsPeriodic, TIME_PERIODIC, TIME_ONESHOT) Or TIME_CALLBACK_FUNCTION _
   )
   If dwHandle <> 0 Then
      StartTimer = True
   Else
      Debug.Print "clsTimer.StartTimer() : Couldn't create timer"
   End If
   Exit Function
   
StartTimer_Error:
   Debug.Print "clsTimer.StartTimer() : Error " & Err & " " & Error
   Exit Function
End Function

Private Function StopTimer() As Boolean
   StopTimer = False
   
   On Error GoTo StopTimer_Error
   
   If dwHandle <> 0 Then
      timeKillEvent dwHandle
      dwHandle = 0
   End If
   
   StopTimer = True
      
   Exit Function
   
StopTimer_Error:
   Debug.Print "clsTimer.StopTimer() : Error " & Err & " " & Error
   Exit Function
End Function


'*********************************************************************
' Private Usercontrol Events
'*********************************************************************
Private Sub UserControl_Initialize()
   ' get the system depending timer resolution
   Dim tc As TIMECAPS
   Call timeGetDevCaps(tc, LenB(tc))
   dwResolutionMin = tc.MinResolution
   dwResolutionMax = tc.MaxResolution
End Sub

Private Sub UserControl_KeyPress(KeyAscii As Integer)
   If KeyAscii = &HA Then RaiseEvent Timer
End Sub

Private Sub UserControl_Terminate()
   StopTimer
End Sub

Private Sub UserControl_Resize()
   Size 155 * Screen.TwipsPerPixelX, 30 * Screen.TwipsPerPixelY
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
   dwInterval = PropBag.ReadProperty("Interval", dwInterval_Default)
   IsPeriodic = PropBag.ReadProperty("Periodic", Periodic_Default)
   dwResolution = PropBag.ReadProperty("Resolution", dwResolution_Default)
   Tag = PropBag.ReadProperty("Tag", "")
   
   Enabled = PropBag.ReadProperty("Enabled", Enabled_Default)
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
   Call PropBag.WriteProperty("Interval", dwInterval, dwInterval_Default)
   Call PropBag.WriteProperty("Periodic", IsPeriodic, Periodic_Default)
   Call PropBag.WriteProperty("Resolution", dwResolution, dwResolution_Default)
   Call PropBag.WriteProperty("Tag", Tag, "")
   
   Call PropBag.WriteProperty("Enabled", Enabled, Enabled_Default)
End Sub

