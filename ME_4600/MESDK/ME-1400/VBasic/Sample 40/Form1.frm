VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "ME 1400"
   ClientHeight    =   3630
   ClientLeft      =   5040
   ClientTop       =   3705
   ClientWidth     =   6420
   LinkTopic       =   "Form1"
   ScaleHeight     =   3630
   ScaleWidth      =   6420
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
      Begin VB.Menu mnu 
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
      Begin VB.Menu Trennstrich1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDIGetBit 
         Caption         =   "DIGetBit"
      End
      Begin VB.Menu mnuDIGetByte 
         Caption         =   "DIGetByte"
      End
      Begin VB.Menu Trennstrich2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDOSetBit 
         Caption         =   "DOSetBit"
      End
      Begin VB.Menu mnuDOSetByte 
         Caption         =   "DOSetByte"
      End
   End
   Begin VB.Menu mnuCounter 
      Caption         =   "Counter"
      Begin VB.Menu mnuCntInitSrc 
         Caption         =   "CntInitSrc"
      End
      Begin VB.Menu mnuCntWrite 
         Caption         =   "CntWrite"
      End
      Begin VB.Menu mnuCntRead 
         Caption         =   "CntRead"
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
Private Sub Help_Click()
    Load FormAbout
    FormAbout.Show
End Sub

Private Sub mnu_Click()
   'determine driver version
    If me1400GetDriverVersion(DriverVersion) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    Else
        MsgBox "Driver Version : " & (Hex(DriverVersion)), , "DriverVersion"
    End If
End Sub



Private Sub mnuCntInitSrc_Click()
    Load Form6
    Form6.Show
End Sub

Private Sub mnuCntRead_Click()
    Load Form8
    Form8.Show
End Sub

Private Sub mnuCntWrite_Click()
    Load Form7
    Form7.Show
End Sub

Private Sub mnuDIGetBit_Click()
    Load Form2
    Form2.Show
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTA, 0)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTB, 0)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTC, 0)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTD, 0)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTE, 0)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTF, 0)
End Sub

Private Sub mnuDIGetByte_Click()
    Load Form3
    Form3.Show
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTA, 0)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTB, 0)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTC, 0)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTD, 0)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTE, 0)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTF, 0)
End Sub

Private Sub mnuDIOReset_Click()
    retval = me1400ResetBoard(Boardnumber)
    retval = me1400InitBoard(Boardnumber)
End Sub

Private Sub mnuDOSetBit_Click()
    Load Form4
    Form4.Show
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTA, 1)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTB, 1)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTC, 1)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTD, 1)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTE, 1)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTF, 1)
End Sub

Private Sub mnuDOSetByte_Click()
    Load Form5
    Form5.Show
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTA, 1)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTB, 1)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTC, 1)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTD, 1)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTE, 1)
    retval = me1400DIOSetPortDirection(Boardnumber, ME1400_PORTF, 1)
End Sub

Private Sub mnuExit_Click()
    retval = me1400ResetBoard(Boardnumber)
    retval = me1400InitBoard(Boardnumber)
    End
End Sub

Private Sub mnuGetBoardVersion_Click()
  'determine board version
    If me1400GetBoardVersion(Boardnumber, BoardVersion) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    Else
        MsgBox "Board Version: " + (Hex(BoardVersion)), , "Board Version"
    End If
End Sub

Private Sub mnuGetDevInfo_Click()
    'determine DeviceInfoStruct
    If me1400GetDevInfo(Boardnumber, DevInfo) = 0 Then
        Call me1400GetDrvErrMess(errtext)
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
    DllVersion = me1400GetDLLVersion()
    MsgBox "DLL Version : " & (Hex(DllVersion)), , "DllVersion"
End Sub

Private Sub mnuGetSerialNumber_Click()
'determine serial number
    If me1400GetSerialNumber(Boardnumber, SerialNumber) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    Else
        MsgBox "Serial Number: " & (Hex(SerialNumber)), , "Serial Number"
    End If
End Sub
