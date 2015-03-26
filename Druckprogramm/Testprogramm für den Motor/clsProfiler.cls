VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsProfiler"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'*********************************************************************
' High Precision Profiler v1.00
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
Private Declare Function QueryPerformanceCounter Lib "Kernel32" _
   (lpPerformanceCount As Currency) _
   As Boolean
Private Declare Function QueryPerformanceFrequency Lib "Kernel32" _
   (lpPerformanceCount As Currency) _
   As Boolean


'*********************************************************************
' Private Vars
'*********************************************************************
Private CountsPerSecond As Currency
Private StartTime As Currency
Private StopTime As Currency


'*********************************************************************
' Public Properties
'*********************************************************************
Public Property Get getAPIOverhead() As Long
   Dim A As Currency, B As Currency, C As Currency
   If QueryPerformanceCounter(A) Then
      QueryPerformanceCounter B
      
      If CountsPerSecond = 0 Then QueryPerformanceFrequency CountsPerSecond
      
      C = B - A
      If C = 0 Then
         getAPIOverhead = 0
      Else
         getAPIOverhead = (C / CountsPerSecond) * 1000
      End If
   Else
      getAPIOverhead = -1
      Debug.Print "clsProfiler.getAPIOverhead(): High-resolution counter not supported."
   End If
End Property


'*********************************************************************
' Public Methods
'*********************************************************************
Public Function StartProfiler() As Boolean
   ' retrieving system depending counts per second
   If CountsPerSecond = 0 Then QueryPerformanceFrequency CountsPerSecond
   
   If CountsPerSecond = 0 Then
      StartProfiler = False
      Debug.Print "clsProfiler.StartProfiler(): High-resolution counter not supported."
      Exit Function
   End If
   
   StartProfiler = True
   QueryPerformanceCounter StartTime
End Function

'Returns the used time in ms
Public Function StopProfiler() As Long
   QueryPerformanceCounter StopTime
   
   If CountsPerSecond = 0 Then
      StopProfiler = False ' Handle no high-resolution timer
   Else
      StopProfiler = ((StopTime - StartTime) / CountsPerSecond) * 1000
   End If
End Function
