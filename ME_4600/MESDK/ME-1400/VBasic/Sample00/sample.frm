VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   6105
   ClientLeft      =   1575
   ClientTop       =   2550
   ClientWidth     =   10650
   LinkTopic       =   "Form1"
   ScaleHeight     =   6105
   ScaleWidth      =   10650
   StartUpPosition =   2  'Bildschirmmitte
   Begin VB.CommandButton Command2 
      Caption         =   "Exit"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2040
      TabIndex        =   12
      Top             =   5160
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Start"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   480
      TabIndex        =   11
      Top             =   5160
      Width           =   1215
   End
   Begin VB.TextBox Text5 
      Height          =   3135
      Left            =   5160
      MultiLine       =   -1  'True
      TabIndex        =   10
      Top             =   1800
      Width           =   4815
   End
   Begin VB.TextBox Text4 
      Height          =   495
      Left            =   2160
      TabIndex        =   8
      Top             =   4320
      Width           =   1215
   End
   Begin VB.TextBox Text3 
      Height          =   495
      Left            =   2160
      TabIndex        =   7
      Top             =   3480
      Width           =   1215
   End
   Begin VB.TextBox Text2 
      Height          =   495
      Left            =   2160
      TabIndex        =   6
      Top             =   2640
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   495
      Left            =   2160
      TabIndex        =   5
      Top             =   1800
      Width           =   1215
   End
   Begin VB.Label Label6 
      Caption         =   "DevInfo: "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3720
      TabIndex        =   9
      Top             =   1800
      Width           =   1215
   End
   Begin VB.Label Label5 
      Caption         =   "Serial Number: "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   4
      Top             =   4320
      Width           =   1455
   End
   Begin VB.Label Label4 
      Caption         =   "Board Version: "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   3
      Top             =   3480
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "Driver Version: "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   2
      Top             =   2640
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "DLL Version: "
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   1
      Top             =   1800
      Width           =   1455
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Zentriert
      Caption         =   "ME-1400 Board Information"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   360
      TabIndex        =   0
      Top             =   360
      Width           =   9975
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'*----------------------------------------------------------------------------------------------------------*/
'*  Source File:    sample.vbp                                                                              */
'*  Compiler:       Visual Basic 6.0                                                                        */
'*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
'*  Author:         ew (Erwin Wisura)                                                                       */
'*                                                                                                          */
'*  Description:    General Example                                                                         */
'*                                                                                                          */
'*  File History:   Version Date    Editor  Action                                                          */
'*------------------------------------------------------------                                              */
'*                  1.0     020723  ew     Gerneral info of the board                                       */
'*                                                                                                          */
'*----------------------------------------------------------------------------------------------------------*}


Private Sub Command1_Click()
   Text1.Text = Visible
   Text2.Text = Visible
   Text3.Text = Visible
   Text4.Text = Visible
   Text5.Text = Visible
End Sub

Private Sub Command2_Click()
   End
End Sub

Private Sub Form_Load()
    Dim BoardNumber As Long
    Dim errtext As String
    Dim val_32 As Long              '32 bit input/output value'
    Dim DllVersion As Long          'DLL version'
    Dim BoardVersion As Long        'board version'
    Dim DriverVersion As Long       'driver version'
    Dim SerialNumber As Long        'serial number'
    Dim DevInfo As DeviceInfoStruct
    
    

    BoardNumber = BOARD_0

End Sub

Private Sub Text1_Change()
 'determine dll version
    DllVersion = me1400GetDLLVersion()
    Text1.Text = Hex(DllVersion)
End Sub

Private Sub Text2_Change()
'determine driver version
    If me1400GetDriverVersion(DriverVersion) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    Else
        Text2.Text = (Hex(DriverVersion))
    End If
End Sub

Private Sub Text3_Change()
'determine board version
    If me1400GetBoardVersion(BoardNumber, BoardVersion) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    Else
        Text3.Text = (Hex(BoardVersion))
    End If
End Sub

Private Sub Text4_Change()
'determine serial number
    If me1400GetSerialNumber(BoardNumber, SerialNumber) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    Else
        Text4.Text = (Hex(SerialNumber))
    End If
End Sub

Private Sub Text5_Change()

'determine DeviceInfoStruct
    Dim DevInfo As DeviceInfoStruct
    If me1400GetDevInfo(BoardNumber, DevInfo) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    Else
        Text5.Text = "BoardNumber : " & Chr(9) & Chr(9) & Chr(9) & (Hex(DevInfo.dwBoardNumber)) & (Chr(13) & Chr(10)) & _
               "Vendor ID : " & Chr(9) & Chr(9) & Chr(9) & (Hex(DevInfo.dwVendorID)) & (Chr(13) & Chr(10)) & _
               "Device ID : " & Chr(9) & Chr(9) & Chr(9) & (Hex(DevInfo.dwDeviceID)) & (Chr(13) & Chr(10)) & _
               "SystemSlotNumber : " & Chr(9) & Chr(9) & (Hex(DevInfo.dwSystemSlotNumber)) & (Chr(13) & Chr(10)) & _
               "Base Port Address : " & Chr(9) & Chr(9) & (Hex(DevInfo.dwPortBase)) & (Chr(13) & Chr(10)) & _
               "Count of I/O addresses used : " & Chr(9) & (Hex(DevInfo.dwPortCount)) & (Chr(13) & Chr(10)) & _
               "first Interrupt channel : " & Chr(9) & Chr(9) & (Hex(DevInfo.dwIntChannel)) & (Chr(13) & Chr(10)) & _
               "PLX Base Port Address : " & Chr(9) & Chr(9) & (Hex(DevInfo.dwPortBasePLX)) & (Chr(13) & Chr(10)) & _
               "PLX Count of I/O adresses used : " & Chr(9) & (Hex(DevInfo.dwPortCountPLX)) & (Chr(13) & Chr(10)) & _
               "Serial number of the board : " & Chr(9) & Chr(9) & (Hex(DevInfo.dwSerialNumber)) & (Chr(13) & Chr(10)) & _
               "Bus number of the PCI bus : " & Chr(9) & Chr(9) & (Hex(DevInfo.dwBusNumber)) & (Chr(13) & Chr(10)) & _
               "Hardware revision of the board : " & Chr(9) & (Hex(DevInfo.dwHWRevision)) & (Chr(13) & Chr(10)) & _
               "number of interrupts : " & Chr(9) & Chr(9) & (Hex(DevInfo.dwIrqCnt)) & (Chr(13) & Chr(10)) & _
               "Board Version : " & Chr(9) & Chr(9) & Chr(9) & (Hex(DevInfo.dwVersion))
           
     End If
End Sub
