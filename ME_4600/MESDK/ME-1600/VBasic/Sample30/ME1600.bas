Attribute VB_Name = "Module1"
Option Explicit

    Public Boardnumber As Long
    Public errtext As String
    
    Public DllVersion As Long          'DLL version'
    Public BoardVersion As Long        'board version'
    Public DriverVersion As Long       'driver version'
    Public SerialNumber As Long        'serial number'
    Public DevInfo As DeviceInfoStruct
    Public iValue As Long
    Public iChannelNumber As Long
    Public iRange As Long
    Public iChannelGroup As Long
    Public iOutMode As Long
    Public sValue As String
