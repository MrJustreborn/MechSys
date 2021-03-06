VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "ME 630"
   ClientHeight    =   3495
   ClientLeft      =   4455
   ClientTop       =   4890
   ClientWidth     =   6825
   LinkTopic       =   "Form1"
   ScaleHeight     =   3495
   ScaleWidth      =   6825
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
   Begin VB.Menu mnuRelaisFunktionen 
      Caption         =   "Relay Function"
      Begin VB.Menu mnuResetRelays 
         Caption         =   "ResetRelays"
      End
      Begin VB.Menu Trennstrich0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSetGetRelayBit 
         Caption         =   "SetGetRelayBit"
      End
      Begin VB.Menu mnuSetGetRelayWord 
         Caption         =   "SetGetRelayWord"
      End
   End
   Begin VB.Menu mnuTTLEingänge 
      Caption         =   "TTL Inputs"
      Begin VB.Menu mnuGetTTLBit 
         Caption         =   "GetTTLBit"
      End
      Begin VB.Menu mnuGetTTLByte 
         Caption         =   "GetTTLByte"
      End
      Begin VB.Menu Trennstrich1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuGetOptoBit 
         Caption         =   "GetOptoBit"
      End
      Begin VB.Menu mnuGetOptoByte 
         Caption         =   "GetOptoByte"
      End
   End
   Begin VB.Menu mnuExit 
      Caption         =   "Exit"
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "?"
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub mnuExit_Click()
        retval = me630ResetRelays(Boardnumber)
        Unload Form1
    End
End Sub

Private Sub mnuGetBoardVersion_Click()
    'determine board version
    If me630GetBoardVersion(Boardnumber, BoardVersion) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    Else
        MsgBox "Board Version: " + (Hex(BoardVersion)), , "Board Version"
    End If
End Sub

Private Sub mnuGetDevInfo_Click()
    'determine DeviceInfoStruct
    If me630GetDevInfo(Boardnumber, DevInfo) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
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
    DllVersion = me630GetDLLVersion()
    MsgBox "DLL Version : " & (Hex(DllVersion)), , "DllVersion"
End Sub

Private Sub mnuGetDriverVersion_Click()
   'determine driver version
    If me630GetDriverVersion(DriverVersion) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    Else
        MsgBox "Driver Version : " & (Hex(DriverVersion)), , "DriverVersion"
    End If
End Sub

Private Sub mnuGetOptoBit_Click()
    Load Form6
    Form6.Show
End Sub

Private Sub mnuGetOptoByte_Click()
    Load Form7
    Form7.Show
End Sub

Private Sub mnuGetSerialNumber_Click()
    'determine serial number
    If me630GetSerialNumber(Boardnumber, SerialNumber) = 0 Then
        Call me630GetDrvErrMess(errtext, 128)
    Else
        MsgBox "Serial Number: " & (Hex(SerialNumber)), , "Serial Number"
    End If
End Sub

Private Sub mnuGetTTLBit_Click()
    Load Form4
    Form4.Show
End Sub

Private Sub mnuGetTTLByte_Click()
    Load Form5
    Form5.Show
End Sub

Private Sub mnuHelp_Click()
    Load FormAbout
    FormAbout.Show
End Sub

Private Sub mnuResetRelays_Click()
    retval = me630ResetRelays(Boardnumber)
End Sub

Private Sub mnuSetGetRelayBit_Click()
    Load Form2
    Form2.Show
End Sub

Private Sub mnuSetGetRelayWord_Click()
    Load Form3
    Form3.Show
End Sub
