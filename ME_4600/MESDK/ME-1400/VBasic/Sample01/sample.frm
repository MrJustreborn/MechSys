VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Visual Basic Sample Program"
   ClientHeight    =   2565
   ClientLeft      =   45
   ClientTop       =   270
   ClientWidth     =   3750
   LinkTopic       =   "Form1"
   ScaleHeight     =   2565
   ScaleWidth      =   3750
   StartUpPosition =   3  'Windows-Standard
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
    Dim val_32 As Long              '32 Bit Ein / Ausgabewert '
    Dim dir As Long                 'Richtungsvariable'
    Dim port As Long                ''
    Dim bitn As Long                'Bitnummer'
    Dim kanal As Long               ''
    Dim errtext As String * 255     'String für Errortext'
    Dim range As Long               ''
    Dim mode As Long                'Modus des Counters'
    Dim counter_0 As Long           ''


    'Defaulteinstellungen'
    BoardNumber = BOARD_0
    dir = 0
    port = 0    'Port A'
    bitn = 0    'Bitnummer 0'
    kanal = 0
    val_32 = 0
    errtext = ""
    mode = 0    'IRQ on Terminal Count'
    counter_0 = 0





    '-----------------------------------------------------------------------
    ' General Functions
    '-----------------------------------------------------------------------

    'determine dll version
    DllVersion = me1400GetDLLVersion()
    MsgBox "DLL version: " + Hex(DllVersion), vbInformation

    'determine driver version
    If me1400GetDriverVersion(DriverVersion) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    Else
        MsgBox "driver version: " + (Hex(DriverVersion)), vbInformation
    End If

    'determine board version
    If me1400GetBoardVersion(BoardNumber, BoardVersion) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    Else
        MsgBox "Board version: " + (Hex(BoardVersion)), vbInformation
    End If

    'determine serial number
    If me1400GetSerialNumber(BoardNumber, SerialNumber) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    Else
        MsgBox "Serial Number: " + (Hex(SerialNumber)), vbInformation
    End If

    ''
    'See also Visual C samples'
    ''


    'Digitale Ein(Port A) / Ausgabe (Port B) '
    'Meßerg. in val_32'
    'Einlesen von Port A '
    If me1400DIOSetPortDirection(BoardNumber, port, dir) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If me1400DIGetBit(BoardNumber, port, bitno, val_32) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If me1400DIGetByte(BoardNumber, port, val_32) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    

    'Ausgeben auf Port B (AA) / Bitnummer 0 = 1'
    dir = 1
    port = 1
    val_16 = &HAA
    If me1400DIOSetPortDirection(BoardNumber, port, dir) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If me1400DIGetBit(BoardNumber, port, bitno, 1) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If
    If me1400DIGetByte(BoardNumber, port, val_32) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If

    'In Counter AAAAA schreiben'
    val_32 = &HAAAA
    If me1400CntWrite(BoardNumber, counter_0, mode, val_32) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If

    'Counter lesen'
    If me1400CntRead(BoardNumber, counter_0, val_32) = 0 Then
        Call me1400GetDrvErrMess(errtext)
    End If

End Sub
