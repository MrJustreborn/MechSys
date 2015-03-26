VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "ME-1600"
   ClientHeight    =   4020
   ClientLeft      =   3855
   ClientTop       =   3300
   ClientWidth     =   7950
   LinkTopic       =   "Form1"
   ScaleHeight     =   4020
   ScaleWidth      =   7950
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
   Begin VB.Menu AnalogOut 
      Caption         =   "Analog Out"
      Begin VB.Menu mnuResetAll 
         Caption         =   "ResetAll"
      End
      Begin VB.Menu Trennstrich 
         Caption         =   "-"
         Index           =   0
      End
      Begin VB.Menu mnuAOSetCurrent 
         Caption         =   "AOSetCurrent"
      End
      Begin VB.Menu mnuAOSetRange 
         Caption         =   "AOSetRange"
      End
      Begin VB.Menu mnuAOSetMode 
         Caption         =   "AOSetMode"
      End
      Begin VB.Menu mnuAOSingle 
         Caption         =   "AOSingle"
      End
      Begin VB.Menu Trennstrich1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuAOUpdate 
         Caption         =   "AOUpdate"
      End
      Begin VB.Menu mnuAOUpdateAll 
         Caption         =   "AOUpdateAll"
      End
   End
   Begin VB.Menu mnuExit 
      Caption         =   "Exit"
   End
   Begin VB.Menu Info 
      Caption         =   "?"
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Info_Click()
    Load FormAbout
    FormAbout.Show
End Sub

Private Sub mnuAOSetCurrent_Click()
    Load Form2
    Form2.Show
End Sub

Private Sub mnuAOSetMode_Click()
    Load Form7
    Form7.Show
End Sub

Private Sub mnuAOSetRange_Click()
    Load Form5
    Form5.Show
End Sub

Private Sub mnuAOSingle_Click()
    Load Form9
    Form9.Show
End Sub

Private Sub mnuAOUpdate_Click()
    Load Form11
    Form11.Show
End Sub

Private Sub mnuAOUpdateAll_Click()
    Load Form12
    Form12.Show
End Sub

Private Sub mnuExit_Click()
        me1600AOResetAll (Boardnumber)
    End
End Sub

Private Sub mnuGetBoardVersion_Click()
    'determine board version
    If me1600GetBoardVersion(Boardnumber, BoardVersion) = 0 Then
        Call me1600GetDrvErrMess(errtext, 128)
    Else
        MsgBox "Board Version: " + (Hex(BoardVersion)), , "Board Version"
    End If
End Sub

Private Sub mnuGetDevInfo_Click()
     'determine DeviceInfoStruct
    If me1600GetDevInfo(Boardnumber, DevInfo) = 0 Then
        Call me1600GetDrvErrMess(errtext, 128)
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
    DllVersion = me1600GetDLLVersion()
    MsgBox "DLL Version : " & (Hex(DllVersion)), , "DllVersion"
End Sub

Private Sub mnuGetDriverVersion_Click()
   'determine driver version
    If me1600GetDriverVersion(DriverVersion) = 0 Then
        Call me1600GetDrvErrMess(errtext, 128)
    Else
        MsgBox "Driver Version : " & (Hex(DriverVersion)), , "DriverVersion"
    End If
End Sub

Private Sub mnuGetSerialNumber_Click()
    'determine serial number
    If me1600GetSerialNumber(Boardnumber, SerialNumber) = 0 Then
        Call me1600GetDrvErrMess(errtext, 128)
    Else
        MsgBox "Serial Number: " & (Hex(SerialNumber)), , "Serial Number"
    End If
End Sub

Private Sub mnuResetAll_Click()
   'general reset
    If me1600AOResetAll(Boardnumber) = 0 Then
        Call me1600GetDrvErrMess(errtext, 128)
    End If
End Sub
