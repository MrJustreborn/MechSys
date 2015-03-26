VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "ME-1000"
   ClientHeight    =   5835
   ClientLeft      =   2295
   ClientTop       =   2310
   ClientWidth     =   9570
   LinkTopic       =   "Form1"
   ScaleHeight     =   5835
   ScaleWidth      =   9570
   Begin VB.Menu Boardparameter 
      Caption         =   "Boardparameter"
      Begin VB.Menu mnuGetBoardVersion 
         Caption         =   "GetBoardVersion"
      End
      Begin VB.Menu mnuGetDevInfo 
         Caption         =   "GetDevInfo"
      End
      Begin VB.Menu mnuGetDLLVersion 
         Caption         =   "GetDLLVersion"
      End
      Begin VB.Menu mnuGetDriverVersion 
         Caption         =   "GetDriverVersion"
      End
      Begin VB.Menu mnuGetSerialNumber 
         Caption         =   "GetSerialNumber"
      End
   End
   Begin VB.Menu DigitalIO 
      Caption         =   "Digital I/O"
      Begin VB.Menu mnuDIOReset 
         Caption         =   "DIOReset"
      End
      Begin VB.Menu Trennstrich 
         Caption         =   "-"
         Index           =   0
      End
      Begin VB.Menu mnuDIGetBit 
         Caption         =   "DIGetBit"
      End
      Begin VB.Menu mnuDIGetByte 
         Caption         =   "DIGetByte"
      End
      Begin VB.Menu mnuDIGetWord 
         Caption         =   "DIGetWord"
      End
      Begin VB.Menu mnuDIGetLong 
         Caption         =   "DIGetLong"
      End
      Begin VB.Menu Trennstrich1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDOSetBit 
         Caption         =   "DOSetBit"
      End
      Begin VB.Menu mnuDOSetByte 
         Caption         =   "DOSetByte"
      End
      Begin VB.Menu mnuDOSetWord 
         Caption         =   "DOSetWord"
      End
      Begin VB.Menu mnuDOSetLong 
         Caption         =   "DOSetLong"
      End
   End
   Begin VB.Menu mnuExit 
      Caption         =   "Exit"
   End
   Begin VB.Menu Help 
      Caption         =   "?"
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
    
Sub Form_Load()
    Boardnumber = 0
    
End Sub



Private Sub Help_Click()
Load FormAbout
FormAbout.Show
   
End Sub

Private Sub mnuDIGetBit_Click()
    Load Form3
    Form3.Show
    Load Form2
    Form2.Show
End Sub

Private Sub mnuDIGetByte_Click()
    Load Form4
    Form4.Show
    Load Form2
    Form2.Show
End Sub

Private Sub mnuDIGetLong_Click()
    Load Form10
    Form10.Show
    Load Form2
    Form2.Show
End Sub

Private Sub mnuDIGetWord_Click()
    Load Form5
    Form5.Show
    Load Form2
    Form2.Show
End Sub

Private Sub mnuDIOReset_Click()
    'general reset
    If me1000DIOReset(Boardnumber) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
End Sub

Private Sub mnuDOSetBit_Click()
    Load Form6
    Form6.Show
    Load Form2
    Form2.Show
End Sub

Private Sub mnuDOSetByte_Click()
    Load Form7
    Form7.Show
    Load Form2
    Form2.Show
End Sub

Private Sub mnuDOSetLong_Click()
    Load Form9
    Form9.Show
    Load Form2
    Form2.Show
End Sub

Private Sub mnuDOSetWord_Click()
    Load Form8
    Form8.Show
    Load Form2
    Form2.Show
End Sub

Private Sub mnuExit_Click()
    End
End Sub

Private Sub mnuGetBoardVersion_Click()
    'determine board version
    If me1000GetBoardVersion(Boardnumber, BoardVersion) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    Else
        MsgBox "Board Version: " + (Hex(BoardVersion)), , "Board Version"
    End If
End Sub

Private Sub mnuGetDevInfo_Click()
     'determine DeviceInfoStruct
    If me1000GetDevInfo(Boardnumber, DevInfo) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    Else
        MsgBox "BoardNumber : " & (Chr(9)) & (Chr(9)) & (Chr(9)) & (Hex(DevInfo.dwBoardNumber)) + (Chr(13) & Chr(10)) + _
               "Vendor ID : " & (Chr(9)) & (Chr(9)) & (Chr(9)) & (Hex(DevInfo.dwVendorID)) + (Chr(13) & Chr(10)) + _
               "Device ID : " & (Chr(9)) & (Chr(9)) & (Chr(9)) & (Hex(DevInfo.dwDeviceID)) + (Chr(13) & Chr(10)) + _
               "SystemSlotNumber : " & (Chr(9)) & (Chr(9)) & (Hex(DevInfo.dwSystemSlotNumber)) + (Chr(13) & Chr(10)) + _
               "Base Port Address : " & (Chr(9)) & (Chr(9)) & (Hex(DevInfo.dwPortBase)) + (Chr(13) & Chr(10)) + _
               "Count of I/O addresses used : " & (Chr(9)) & (Hex(DevInfo.dwPortCount)) + (Chr(13) & Chr(10)) + _
               "first Interrupt channel : " & (Chr(9)) & (Chr(9)) & (Hex(DevInfo.dwIntChannel)) + (Chr(13) & Chr(10)) + _
               "PLX Base Port Address : " & (Chr(9)) & (Chr(9)) & (Hex(DevInfo.dwPortBasePLX)) + (Chr(13) & Chr(10)) + _
               "PLX Count of I/O adresses used : " & (Chr(9)) & (Hex(DevInfo.dwPortCountPLX)) + (Chr(13) & Chr(10)) + _
               "Serial number of the board : " & (Chr(9)) & (Chr(9)) & (Hex(DevInfo.dwSerialNumber)) + (Chr(13) & Chr(10)) + _
               "Bus number of the PCI bus : " & (Chr(9)) & (Chr(9)) & (Hex(DevInfo.dwBusNumber)) + (Chr(13) & Chr(10)) + _
               "Hardware revision of the board : " & (Chr(9)) & (Hex(DevInfo.dwHWRevision)) + (Chr(13) & Chr(10)) + _
               "number of interrupts : " & (Chr(9)) & (Chr(9)) & (Hex(DevInfo.dwIrqCnt)) + (Chr(13) & Chr(10)) + _
               "Board Version : " & (Chr(9)) & (Chr(9)) & (Chr(9)) & (Hex(DevInfo.dwVersion)), , "DevInfo"
           
     End If
End Sub

Private Sub mnuGetDLLVersion_Click()
    'determine dll version
    DllVersion = me1000GetDLLVersion()
    MsgBox "DLL Version : " & (Hex(DllVersion)), , "DllVersion"
End Sub

Private Sub mnuGetDriverVersion_Click()
    'determine driver version
    If me1000GetDriverVersion(DriverVersion) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    Else
        MsgBox "Driver Version : " & (Hex(DriverVersion)), , "DriverVersion"
    End If
End Sub

Private Sub mnuGetSerialNumber_Click()
    'determine serial number
    If me1000GetSerialNumber(Boardnumber, SerialNumber) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    Else
        MsgBox "Serial Number: " & (Hex(SerialNumber)), , "Serial Number"
    End If
End Sub

