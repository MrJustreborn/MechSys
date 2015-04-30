VERSION 5.00
Begin VB.Form Form1
   Caption         =   "Visual Basic Sample Program"
   ClientHeight    =   3195
   ClientLeft      =   14160
   ClientTop       =   7635
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   2  'Bildschirmmitte
   Begin VB.TextBox TextBox
      Height          =   2895
      Left            =   240
      MultiLine       =   -1  'True
      TabIndex        =   0
      Top             =   120
      Width           =   4215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()

    Dim BoardNumber As Long
    Dim DllVersion As Long          'DLL version'
    Dim BoardVersion As Long        'board version'
    Dim DriverVersion As Long       'driver version'
    Dim SerialNumber As Long        'serial number'
    Dim errtext As String
    Dim val_32 As Long              '32 bit input/output value'


    BoardNumber = BOARD_0


    '-----------------------------------------------------------------------
    ' General Functions
    '-----------------------------------------------------------------------

    'determine dll version
    DllVersion = me1000GetDLLVersion()
    MsgBox "DLL version: " + Hex(DllVersion), vbInformation

    'determine driver version
    If me1000GetDriverVersion(DriverVersion) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    Else
        MsgBox "driver version: " + (Hex(DriverVersion)), vbInformation
    End If

    'determine board version
    If me1000GetBoardVersion(BoardNumber, BoardVersion) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    Else
        MsgBox "Board version: " + (Hex(BoardVersion)), vbInformation
    End If

    'determine serial number
    If me1000GetSerialNumber(BoardNumber, SerialNumber) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    Else
        MsgBox "Board version: " + (Hex(SerialNumber)), vbInformation
    End If



    'general reset
    If me1000DIOReset(BoardNumber) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If

    'Write byte
    val_32 = 15
    If me1000DIOSetPortDirection(BoardNumber, PORTA, MEOUTPUT) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If me1000DOSetByte(BoardNumber, PORTA, BYTE_0, val_32) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    Else
        MsgBox "ME1000 Write value: " + Hex(val_32), vbInformation
    End If


    'Read byte
    If me1000DIOSetPortDirection(BoardNumber, PORTA, MEINPUT) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    End If
    If me1000DIGetByte(BoardNumber, PORTA, BYTE_0, val_32) = 0 Then
        Call me1000GetDrvErrMess(errtext, 128)
    Else
        MsgBox "ME1000 Read value: " + Hex(val_32), vbInformation
    End If
End Sub
