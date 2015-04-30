VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "ME1600 Visual Basic Test Program"
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


    BoardNumber = BOARD_0


    '-----------------------------------------------------------------------
    ' General Functions
    '-----------------------------------------------------------------------

    'determine dll version
    DllVersion = me1600GetDLLVersion()
    MsgBox "DLL version: " + Hex(DllVersion), vbInformation

    'determine driver version
    If me1600GetDriverVersion(DriverVersion) = 0 Then
        Call me1600GetDrvErrMess(errtext, 128)
    Else
        MsgBox "driver version: " + (Hex(DriverVersion)), vbInformation
    End If

    'determine board version
    If me1600GetBoardVersion(BoardNumber, BoardVersion) = 0 Then
        Call me1600GetDrvErrMess(errtext, 128)
    Else
        MsgBox "board version: " + (Hex(BoardVersion)), vbInformation
    End If

    'determine serial number
    If me1600GetSerialNumber(BoardNumber, SerialNumber) = 0 Then
        Call me1600GetDrvErrMess(errtext, 128)
    Else
        MsgBox "serial number: " + (Hex(SerialNumber)), vbInformation
    End If

    ' Reset All
    If me1600AOResetAll(BoardNumber) = 1 Then
        MsgBox "reset ok", vbInformation
    Else
        Result = me1600GetDrvErrMess(errtext, 255)
    End If

    ' Set Range
    If me1600AOSetRange(BoardNumber, AO1600_CH00, AO1600_BIPOLAR) Then
        Call me1600GetDrvErrMess(errtext, 255)
    End If

    ' Set Mode
    If me1600AOSetMode(BoardNumber, AO1600_GROUP_A, AO1600_BUFFERED) Then
        Call me1600GetDrvErrMess(errtext, 255)
    End If

    ' Single Out
    If me1600AOSingle(BoardNumber, AO1600_CH00, &H0) Then
        Call me1600GetDrvErrMess(errtext, 255)
    End If

    ' Update
    If me1600AOUpdate(BoardNumber, AO1600_GROUP_A) Then
        Call me1600GetDrvErrMess(errtext, 255)
    End If

    ' Transparent
    If me1600AOSetRange(BoardNumber, AO1600_CH01, AO1600_UNIPOLAR) Then
        Call me1600GetDrvErrMess(errtext, 255)
    End If

    If me1600AOSetMode(BoardNumber, AO1600_GROUP_A, AO1600_TRANSPARENT) Then
        Call me1600GetDrvErrMess(errtext, 255)
    End If

    If me1600AOSingle(BoardNumber, AO1600_CH01, &H3FF) Then
        Call me1600GetDrvErrMess(errtext, 255)
    End If

End Sub
