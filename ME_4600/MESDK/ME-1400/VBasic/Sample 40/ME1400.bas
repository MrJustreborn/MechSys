Attribute VB_Name = "Module1"
Option Explicit

    Public Boardnumber As Long
    Public errortext As String
    
    Public DllVersion As Long          'DLL version'
    Public BoardVersion As Long        'board version'
    Public DriverVersion As Long       'driver version'
    Public SerialNumber As Long        'serial number'
    Public DevInfo As DeviceInfoStruct
    Public iWordValue As Integer
    Public iChannelNumber As Long
    Public iRange As Long
    Public iChannelGroup As Long
    Public iOutMode As Long
    Public usValue As String
    Public iByteValue As Integer
    Public pcValue As Integer
    Public Port_x As Long
    Public val_32 As Long
    Public CounterSource As Long
    Public Counter As Long
    Public iMode As Long
    
    Public iValueX_0 As Long
    Public iValueX_1 As Long
    Public iValueX_2 As Long
    Public iValueX_3 As Long
    Public iValueX_4 As Long
    Public iValueX_5 As Long
    Public iValueX_6 As Long
    Public iValueX_7 As Long



    Global Const COUNTER_SOURCE_SUBD = &H0
    Global Const COUNTER_SOURCE_1MHZ = &H1
    Global Const COUNTER_SOURCE_10MHZ = &H2
    Global Const COUNTER_SOURCE_PREV = &H3
    
