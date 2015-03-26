'==============================================================================

' File:                         ULDO01.VB

' Library Call Demonstrated:    MccDaq.MccBoard.DOut()

' Purpose:                      Writes a byte to digital output ports.

' Demonstration:                Configures FirstPortA for output and writes
'                               a value to the port.

' Other Library Calls:          MccDaq.MccBoard.DConfigPort()
'                               MccDaq.MccService.ErrHandling()

' Special Requirements:         Board 0 must have a digital output port.
'                               Board 0 must have programmable digital ports.

'==============================================================================
Option Strict Off
Option Explicit On
Imports System.IO

Public Class frmSetDigOut

    Inherits System.Windows.Forms.Form
    Public Vergleichswert As Single
    Public Koordinaten(2, 2) As Integer
    Public Befehlsnummer As Integer
    Public Stiftobenoderunten As Integer
    Const PortNum As MccDaq.DigitalPortType = MccDaq.DigitalPortType.FirstPortA ' set port A to use
    Const PortNum2 As MccDaq.DigitalPortType = MccDaq.DigitalPortType.FirstPortB ' set port B to use
    Const Direction As MccDaq.DigitalPortDirection = MccDaq.DigitalPortDirection.DigitalOut
    Public WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Button2 As System.Windows.Forms.Button ' program digital port A for output

    'Create a new MccBoard object for Board 0 
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)
    Friend WithEvents lblShowData As System.Windows.Forms.Label

    Private RangeSelected As MccDaq.Range
    Friend WithEvents tbpfad As System.Windows.Forms.TextBox
    Public WithEvents lblDataValOut As System.Windows.Forms.Label
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents Button4 As System.Windows.Forms.Button
    Friend WithEvents Button5 As System.Windows.Forms.Button
    Friend WithEvents Button6 As System.Windows.Forms.Button
    Friend WithEvents Stift As System.Windows.Forms.Button
    Friend WithEvents Button7 As System.Windows.Forms.Button
    Friend WithEvents Button8 As System.Windows.Forms.Button
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Button9 As System.Windows.Forms.Button
    Friend WithEvents skf As System.Windows.Forms.TextBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents zeit As System.Windows.Forms.TextBox
    Friend WithEvents Button10 As System.Windows.Forms.Button

    Private Property minLeange As Object


    Private Property Leange As Object
    Dim ULStat As MccDaq.ErrorInfo


    Private Sub cmdEndProgram_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs)

        Dim DataValue As UInt16
        DataValue = Convert.ToUInt16(0)

        ULStat = DaqBoard.DOut(PortNum, DataValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        End

    End Sub



#Region "Windows Form Designer generated code "
    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        InitUL()

    End Sub
    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal Disposing As Boolean)
        If Disposing Then
            If Not components Is Nothing Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(Disposing)
    End Sub
    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer
    Public ToolTip1 As System.Windows.Forms.ToolTip
    Public WithEvents tmrConvert As System.Windows.Forms.Timer
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.lblShowData = New System.Windows.Forms.Label()
        Me.tbpfad = New System.Windows.Forms.TextBox()
        Me.tmrConvert = New System.Windows.Forms.Timer(Me.components)
        Me.lblDataValOut = New System.Windows.Forms.Label()
        Me.Button3 = New System.Windows.Forms.Button()
        Me.Button4 = New System.Windows.Forms.Button()
        Me.Button5 = New System.Windows.Forms.Button()
        Me.Button6 = New System.Windows.Forms.Button()
        Me.Stift = New System.Windows.Forms.Button()
        Me.Button7 = New System.Windows.Forms.Button()
        Me.Button8 = New System.Windows.Forms.Button()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.TextBox1 = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Button9 = New System.Windows.Forms.Button()
        Me.skf = New System.Windows.Forms.TextBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.zeit = New System.Windows.Forms.TextBox()
        Me.Button10 = New System.Windows.Forms.Button()
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.SuspendLayout()
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(132, 183)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(75, 23)
        Me.Button1.TabIndex = 8
        Me.Button1.Text = "Drucken"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(190, 55)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(75, 23)
        Me.Button2.TabIndex = 9
        Me.Button2.Text = "Vorschau"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'lblShowData
        '
        Me.lblShowData.AutoSize = True
        Me.lblShowData.Location = New System.Drawing.Point(5, 14)
        Me.lblShowData.Name = "lblShowData"
        Me.lblShowData.Size = New System.Drawing.Size(185, 14)
        Me.lblShowData.TabIndex = 10
        Me.lblShowData.Text = "Dateipfad PA PU PD CS eingeben:"
        '
        'tbpfad
        '
        Me.tbpfad.Location = New System.Drawing.Point(8, 31)
        Me.tbpfad.Name = "tbpfad"
        Me.tbpfad.Size = New System.Drawing.Size(258, 20)
        Me.tbpfad.TabIndex = 11
        Me.tbpfad.Text = "C:\Users\student\Desktop\attachment.obj"
        '
        'tmrConvert
        '
        '
        'lblDataValOut
        '
        Me.lblDataValOut.BackColor = System.Drawing.SystemColors.Window
        Me.lblDataValOut.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDataValOut.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDataValOut.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDataValOut.Location = New System.Drawing.Point(653, 208)
        Me.lblDataValOut.Name = "lblDataValOut"
        Me.lblDataValOut.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDataValOut.Size = New System.Drawing.Size(185, 17)
        Me.lblDataValOut.TabIndex = 2
        '
        'Button3
        '
        Me.Button3.Location = New System.Drawing.Point(95, 116)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(88, 24)
        Me.Button3.TabIndex = 12
        Me.Button3.Text = "Papier vor"
        Me.Button3.UseVisualStyleBackColor = True
        '
        'Button4
        '
        Me.Button4.Location = New System.Drawing.Point(95, 75)
        Me.Button4.Name = "Button4"
        Me.Button4.Size = New System.Drawing.Size(88, 24)
        Me.Button4.TabIndex = 13
        Me.Button4.Text = "Papier hinter"
        Me.Button4.UseVisualStyleBackColor = True
        '
        'Button5
        '
        Me.Button5.Location = New System.Drawing.Point(14, 98)
        Me.Button5.Name = "Button5"
        Me.Button5.Size = New System.Drawing.Size(75, 23)
        Me.Button5.TabIndex = 14
        Me.Button5.Text = "links"
        Me.Button5.UseVisualStyleBackColor = True
        '
        'Button6
        '
        Me.Button6.Location = New System.Drawing.Point(189, 98)
        Me.Button6.Name = "Button6"
        Me.Button6.Size = New System.Drawing.Size(75, 23)
        Me.Button6.TabIndex = 15
        Me.Button6.Text = "rechts"
        Me.Button6.UseVisualStyleBackColor = True
        '
        'Stift
        '
        Me.Stift.Location = New System.Drawing.Point(153, 221)
        Me.Stift.Name = "Stift"
        Me.Stift.Size = New System.Drawing.Size(75, 23)
        Me.Stift.TabIndex = 16
        Me.Stift.Text = "Button7"
        Me.Stift.UseVisualStyleBackColor = True
        '
        'Button7
        '
        Me.Button7.Location = New System.Drawing.Point(159, 31)
        Me.Button7.Name = "Button7"
        Me.Button7.Size = New System.Drawing.Size(75, 23)
        Me.Button7.TabIndex = 16
        Me.Button7.Text = "Stift runter"
        Me.Button7.UseVisualStyleBackColor = True
        '
        'Button8
        '
        Me.Button8.Location = New System.Drawing.Point(33, 31)
        Me.Button8.Name = "Button8"
        Me.Button8.Size = New System.Drawing.Size(75, 23)
        Me.Button8.TabIndex = 17
        Me.Button8.Text = "Stift hoch"
        Me.Button8.UseVisualStyleBackColor = True
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.Button8)
        Me.GroupBox1.Controls.Add(Me.Button7)
        Me.GroupBox1.Controls.Add(Me.Button6)
        Me.GroupBox1.Controls.Add(Me.Button5)
        Me.GroupBox1.Controls.Add(Me.Button4)
        Me.GroupBox1.Controls.Add(Me.Button3)
        Me.GroupBox1.Location = New System.Drawing.Point(535, 11)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(275, 160)
        Me.GroupBox1.TabIndex = 18
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Navigation"
        '
        'TextBox1
        '
        Me.TextBox1.Location = New System.Drawing.Point(8, 104)
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.Size = New System.Drawing.Size(258, 20)
        Me.TextBox1.TabIndex = 19
        Me.TextBox1.Text = "C:\Users\student\Desktop\hallo.obj"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(8, 87)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(199, 14)
        Me.Label1.TabIndex = 20
        Me.Label1.Text = "Dateipfad einer Plotdatei eingeben:"
        '
        'Button9
        '
        Me.Button9.Location = New System.Drawing.Point(190, 143)
        Me.Button9.Name = "Button9"
        Me.Button9.Size = New System.Drawing.Size(75, 23)
        Me.Button9.TabIndex = 21
        Me.Button9.Text = "Vorschau"
        Me.Button9.UseVisualStyleBackColor = True
        '
        'skf
        '
        Me.skf.Location = New System.Drawing.Point(118, 144)
        Me.skf.Name = "skf"
        Me.skf.Size = New System.Drawing.Size(45, 20)
        Me.skf.TabIndex = 22
        Me.skf.Text = "1"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(18, 150)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(78, 14)
        Me.Label2.TabIndex = 23
        Me.Label2.Text = "Skalierfaktor"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.Label3)
        Me.GroupBox2.Controls.Add(Me.zeit)
        Me.GroupBox2.Controls.Add(Me.Label2)
        Me.GroupBox2.Controls.Add(Me.skf)
        Me.GroupBox2.Controls.Add(Me.Button9)
        Me.GroupBox2.Controls.Add(Me.Label1)
        Me.GroupBox2.Controls.Add(Me.TextBox1)
        Me.GroupBox2.Controls.Add(Me.tbpfad)
        Me.GroupBox2.Controls.Add(Me.lblShowData)
        Me.GroupBox2.Controls.Add(Me.Button2)
        Me.GroupBox2.Controls.Add(Me.Button1)
        Me.GroupBox2.Location = New System.Drawing.Point(538, 175)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(271, 222)
        Me.GroupBox2.TabIndex = 24
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Drucksoftware"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(8, 186)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(57, 14)
        Me.Label3.TabIndex = 24
        Me.Label3.Text = " Zeit[ms]"
        '
        'zeit
        '
        Me.zeit.Location = New System.Drawing.Point(71, 183)
        Me.zeit.Name = "zeit"
        Me.zeit.Size = New System.Drawing.Size(55, 20)
        Me.zeit.TabIndex = 18
        Me.zeit.Text = "4"
        '
        'Button10
        '
        Me.Button10.Location = New System.Drawing.Point(441, 343)
        Me.Button10.Name = "Button10"
        Me.Button10.Size = New System.Drawing.Size(91, 54)
        Me.Button10.TabIndex = 25
        Me.Button10.Text = "Drucker Einrichten"
        Me.Button10.UseVisualStyleBackColor = True
        '
        'frmSetDigOut
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(818, 404)
        Me.Controls.Add(Me.Button10)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.lblDataValOut)
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmSetDigOut"
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Druckprogramm"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
#End Region

    Private Sub Button10_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button10.Click


      
        tmrConvert.Enabled = True



    End Sub

#Region "Universal Library Initialization - Expand this region to change error handling, etc."

    Private Sub InitUL()
        Dim ULStat As MccDaq.ErrorInfo

        ' declare revision level of Universal Library

        ULStat = MccDaq.MccService.DeclareRevision(MccDaq.MccService.CurrentRevNum)

        ' Initiate error handling
        '  activating error handling will trap errors like
        '  bad channel numbers and non-configured conditions.
        '  Parameters:
        '    MccDaq.ErrorReporting.PrintAll :all warnings and errors encountered will be printed
        '    MccDaq.ErrorHandling.StopAll   :if any error is encountered, the program will stop


        ULStat = MccDaq.MccService.ErrHandling(MccDaq.ErrorReporting.PrintAll, MccDaq.ErrorHandling.StopAll)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        End If


        ' configure FirstPortA for digital output
        '  Parameters:
        '    PortNum    :the output port
        '    Direction  :sets the port for input or output
        ULStat = DaqBoard.DConfigPort(PortNum, Direction)
        ULStat = DaqBoard.DConfigPort(PortNum2, Direction)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop


    End Sub
#End Region

    Private Sub tmrConvert_Tick(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles tmrConvert.Tick

        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As System.Int32
        Dim Chan As Integer

        Dim Options As MccDaq.VInOptions
        Dim k As Integer
        Dim Motorx(4) As Integer
        Dim Motory(4) As Integer
        Dim i As Integer

        Dim ULStat2 As MccDaq.ErrorInfo
        Dim DataValue2 As UInt16
        k = 1


        Do



            ' Collect the data by calling VIn memeber function of MccBoard object

            '  Parameters:
            '    Chan       :the input channel number
            '    Range      :the Range for the board.
            '    DataValue  :the name for the value collected

            Chan = 0 ' set input channel
            Options = MccDaq.VInOptions.Default

            ULStat = DaqBoard.VIn(Chan, RangeSelected, DataValue, Options)
            If ULStat.Value = MccDaq.ErrorInfo.ErrorCode.BadRange Then
                MsgBox("Change the Range argument to one supported by this board.", 0, "Unsupported Range")
            End If

            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                Stop
            Else
                lblShowData.Text = DataValue.ToString()                ' print the counts

            End If



            Motorx(1) = 3
            Motorx(2) = 6
            Motorx(3) = 12
            Motorx(4) = 9
            Motory(1) = 48
            Motory(2) = 96
            Motory(3) = 192
            Motory(4) = 144







            k = k + 1

            If k = 5 Then
                k = 1
            End If
            If k = 0 Then
                k = 4
            End If
            DataValue2 = Motorx(k)

            ULStat2 = DaqBoard.DOut(PortNum, DataValue2)

            If ULStat2.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                Stop
            End If
            Sleep(2)

            If DataValue < 1 Then
                Exit Do
            End If
        Loop

        If DataValue < 1 Then
            For i = 0 To 9648
                k = k - 1

                If k = 5 Then
                    k = 1
                End If
                If k = 0 Then
                    k = 4
                End If
                DataValue2 = Motorx(k)

                ULStat2 = DaqBoard.DOut(PortNum, DataValue2)

                If ULStat2.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                    Stop
                End If
                Sleep(2)

            Next i

            tmrConvert.Enabled = False


        End If


    End Sub



    Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click

        Dim dateipfad As String
        Dim inhalt As String

        dateipfad = tbpfad.Text
        '*************************************** Beginn Dateiauslesen *************************
        Dim objDateiLeser As StreamReader

        objDateiLeser = New StreamReader(dateipfad)
        inhalt = objDateiLeser.ReadToEnd()


        Dim position1, position2, zaehler As Integer

        zaehler = 0
        position1 = 0
        position2 = InStr(inhalt, vbNewLine)
        If position2 > 0 Then
            Do
                position2 = InStr(position2 + 1, inhalt, vbNewLine)
                zaehler = zaehler + 1
            Loop Until zaehler = 0 Or position2 = 0

        End If
        Dim Zeile(0 To zaehler) As String
        zaehler = 0
        position2 = InStr(inhalt, vbNewLine)

        If position2 > 0 Then
            Zeile(zaehler) = Mid(inhalt, position1 + 1, position2 - 1)

            Do
                position1 = InStr(position1 + 1, inhalt, vbNewLine)
                position2 = InStr(position2 + 1, inhalt, vbNewLine)

                If position1 > 0 AndAlso position2 > 0 Then

                    zaehler = zaehler + 1

                    Zeile(zaehler) = Mid(inhalt, position1 + 2, position2 - position1 - 2)

                ElseIf position1 > position2 Then

                    zaehler = zaehler + 1

                    Zeile(zaehler) = Mid(inhalt, position1 + 2, Len(inhalt) - position1 - 1)

                End If

            Loop Until zaehler = 0 Or position1 = 0
        End If
        '****************************************Kreisbefehle zählen****************************
        Dim anzahlbefehle As Integer
        anzahlbefehle = zaehler
        Dim Kreisbefehlposition As Integer = 0
        Dim Kreisbefehlanzahl As Integer = 0
        Dim Kreislinien As Integer = 0
        Dim Anzahlkreislinien As Integer = 500
        Dim einenmehr As Integer
        einenmehr = 1

        Do
            Kreisbefehlposition = InStr(Kreisbefehlposition + 1, inhalt, "CS")
            If Kreisbefehlposition > 0 Then
                Kreislinien = Kreislinien + Anzahlkreislinien
                Kreisbefehlanzahl = Kreisbefehlanzahl + 1
            End If
        Loop Until Kreisbefehlposition = 0
        Dim Kreiskoordinaten(1, 0 To Kreislinien - 1) As Integer

        '**************************************Zähle die Anzahl der PA Befehle***********************

        Dim PositionPA As Integer = 0
        Dim AnzahlPABefehle As Integer = 0
        Do
            PositionPA = InStr(PositionPA + 1, inhalt, "PA")

            If PositionPA > 0 Then
                AnzahlPABefehle = AnzahlPABefehle + 1
            End If

        Loop Until PositionPA = 0

        '************************************Zähle Anzahl von PU/PD***********************************


        Dim PositionPU As Integer = 0
        Dim PositionPD As Integer = 0
        Dim AnzahlPUPDBefehle As Integer = 0
        Do
            PositionPU = InStr(PositionPU + 1, inhalt, "PU")

            If PositionPU > 0 Then
                AnzahlPUPDBefehle = AnzahlPUPDBefehle + 1
            End If

        Loop Until PositionPU = 0
        Do
            PositionPD = InStr(PositionPD + 1, inhalt, "PD")

            If PositionPD > 0 Then
                AnzahlPUPDBefehle = AnzahlPUPDBefehle + 1
            End If

        Loop Until PositionPD = 0



        objDateiLeser.Close()
        objDateiLeser = Nothing

        '************************Ende des Ausleseprogrammabschnittes*********************************

        '***********************Beginn Behfehlsauswertung ****************************************** 

        Dim befehl As String
        Dim n, PU, PA, PD, CS, Koordinatex, Koordinatey, Mittelpunktx, Mittelpunkty, Winkel As Integer

        Dim erstezahl, letztezahl As Integer
        Dim ObenUnten, MomentaneAnzahlPUPD, MomentaneAnzahlCS As Integer

        MomentaneAnzahlCS = 0
        MomentaneAnzahlPUPD = 0
        PU = 0
        PA = 0
        PD = 0
        CS = 0
        n = 0
        Befehlsnummer = 0

        Do

            befehl = Zeile(n)


            PU = InStr(befehl, "PU")
            PA = InStr(befehl, "PA")
            PD = InStr(befehl, "PD")
            CS = InStr(befehl, "CS")



            '***************Befehlsauswertung PU/PD ******************************************

            If PU = 1 AndAlso PD = 0 AndAlso PA = 0 AndAlso CS = 0 Then
                ObenUnten = 0


            ElseIf PU = 0 AndAlso PD = 1 AndAlso PA = 0 AndAlso CS = 0 Then

                ObenUnten = 1

                '********************************Ende PU / PD  Befehlsauswertung*********************





                '**********************************PA Befehlsauswertung******************************
            ElseIf PU = 0 AndAlso PD = 0 AndAlso PA = 1 AndAlso CS = 0 Then

                '***************************PA  X-Koordinate ************************
                erstezahl = 1                   'Position der Ersten Zahl der X-Koordinate wird von Links (1) gesucht

                letztezahl = InStr(befehl, ",") 'Position der Letzten Zahl der X-Koordinate wird vom Komma aus gesucht


                If Asc(Mid(befehl, erstezahl, 1)) < 48 Or Asc(Mid(befehl, erstezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, erstezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, erstezahl, 1)) <= 57  'Falls Leerzeichen oder Buchstaben zwischen Start und Zahl dann verschiebe Position um eins nach rechts

                        erstezahl = erstezahl + 1
                    Loop
                End If

                'letzteezahl ist position des Kommas
                If Asc(Mid(befehl, letztezahl, 1)) < 48 Or Asc(Mid(befehl, letztezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, letztezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, letztezahl, 1)) <= 57  'Beginne am Ende und gehe nach links bis x8 eine Zahl wird
                        letztezahl = letztezahl - 1
                    Loop
                End If


                Koordinatex = CInt(Mid(befehl, erstezahl, letztezahl - erstezahl + 1))

                Befehlsnummer = Befehlsnummer + 1

                ReDim Preserve Koordinaten(2, 0 To Befehlsnummer + 1)

                Koordinaten(0, Befehlsnummer) = ObenUnten
                Koordinaten(1, Befehlsnummer) = Koordinatex


                '*************************PA  Y-Koordinate *****************************

                erstezahl = InStr(befehl, ",")                   'Position der Ersten Zahl der X-Koordinate wird vom Komma aus gesucht

                letztezahl = Len(befehl)                         'Position der Letzten Zahl der Y-Koordinate wird vom Ende aus gesucht


                If Asc(Mid(befehl, erstezahl, 1)) < 48 Or Asc(Mid(befehl, erstezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, erstezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, erstezahl, 1)) <= 57  'Falls Leerzeichen oder Buchstaben zwischen Start und Zahl dann verschiebe Position um eins nach rechts

                        erstezahl = erstezahl + 1
                    Loop
                End If

                'letztezahl ist am Ende von befehl positioniert
                If Asc(Mid(befehl, letztezahl, 1)) < 48 Or Asc(Mid(befehl, letztezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, letztezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, letztezahl, 1)) <= 57  'Beginne am Ende und gehe nach links bis linkezahl eine Zahl wird
                        letztezahl = letztezahl - 1
                    Loop
                End If
                Koordinatey = CInt(Mid(befehl, erstezahl, letztezahl - erstezahl + 1))
                Koordinaten(2, Befehlsnummer) = Koordinatey


                '******************************Ende PA Befehlsauswertung********************************************



                '******************************Beginn des Kreisbefehlsauslesen*******************************************
            ElseIf PU = 0 AndAlso PD = 0 AndAlso PA = 0 AndAlso CS = 1 Then

                MomentaneAnzahlCS = MomentaneAnzahlCS + 1



                '***************************CS  X-Koordinate ************************
                erstezahl = 1                   'Position der Ersten Zahl der X-Koordinate wird von Links (1) gesucht

                letztezahl = InStr(befehl, ",") 'Position der Letzten Zahl der X-Koordinate wird vom Komma aus gesucht


                If Asc(Mid(befehl, erstezahl, 1)) < 48 Or Asc(Mid(befehl, erstezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, erstezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, erstezahl, 1)) <= 57  'Falls Leerzeichen oder Buchstaben zwischen Start und Zahl dann verschiebe Position um eins nach rechts

                        erstezahl = erstezahl + 1
                    Loop
                End If

                'letzteezahl ist position des Kommas
                If Asc(Mid(befehl, letztezahl, 1)) < 48 Or Asc(Mid(befehl, letztezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, letztezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, letztezahl, 1)) <= 57  'Beginne am Ende und gehe nach links bis x8 eine Zahl wird
                        letztezahl = letztezahl - 1
                    Loop
                End If
                Mittelpunktx = CInt(Mid(befehl, erstezahl, letztezahl - erstezahl + 1))

                '***************************CS Y-Koordinate ************************
                erstezahl = InStr(befehl, ",")                   'Position der Ersten Zahl der Y-Koordinate wird nach dem ersten Komma gesucht

                letztezahl = InStr(erstezahl + 1, befehl, ",") 'Mittelpunkt y-koordinate wird zwischen erstem und zweitem Komma gesucht


                If Asc(Mid(befehl, erstezahl, 1)) < 48 Or Asc(Mid(befehl, erstezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, erstezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, erstezahl, 1)) <= 57  'Falls Leerzeichen oder Buchstaben zwischen Start und Zahl dann verschiebe Position um eins nach rechts

                        erstezahl = erstezahl + 1
                    Loop
                End If

                'letzteezahl ist position des Kommas
                If Asc(Mid(befehl, letztezahl, 1)) < 48 Or Asc(Mid(befehl, letztezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, letztezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, letztezahl, 1)) <= 57  'Beginne am Ende und gehe nach links bis x8 eine Zahl wird
                        letztezahl = letztezahl - 1
                    Loop
                End If
                Mittelpunkty = CInt(Mid(befehl, erstezahl, letztezahl - erstezahl + 1))

                '************************Winkel CS *****************************

                erstezahl = letztezahl + 1                 'Position der ersten Zahl wird nach dem zweiten komma gesucht

                letztezahl = Len(befehl)                         'Position der Letzten Zahl des  Winkels wird vom Ende aus gesucht


                If Asc(Mid(befehl, erstezahl, 1)) < 48 Or Asc(Mid(befehl, erstezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, erstezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, erstezahl, 1)) <= 57  'Falls Leerzeichen oder Buchstaben zwischen Start und Zahl dann verschiebe Position um eins nach rechts

                        erstezahl = erstezahl + 1
                    Loop
                End If

                'letztezahl ist am Ende von befehl positioniert
                If Asc(Mid(befehl, letztezahl, 1)) < 48 Or Asc(Mid(befehl, letztezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, letztezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, letztezahl, 1)) <= 57  'Beginne am Ende und gehe nach links bis linkezahl eine Zahl wird
                        letztezahl = letztezahl - 1
                    Loop
                End If
                Winkel = CInt(Mid(befehl, erstezahl, letztezahl - erstezahl + 1))



                '*******************************Ende des kreisbefehlsauslesen********************************************


                '*******************************Beginn Berechnung des Kreises*************************************

                Dim APX, APY, MPX, MPY, radius As Integer

                APX = Koordinaten(1, Befehlsnummer)
                APY = Koordinaten(2, Befehlsnummer)

                MPX = Mittelpunktx
                MPY = Mittelpunkty
                radius = Math.Sqrt((Math.Abs(APX - MPX)) ^ 2 + (Math.Abs(APY - MPY)) ^ 2)

                Dim Anzlinienkreis, Teilwinkel, index As Integer


                Anzlinienkreis = (radius / 100) * (Winkel / 150)

                Teilwinkel = Winkel / (Anzlinienkreis * 10)

                index = 0

                Dim EPX, EPY, NPX, NPY, Anfangswinkel, NeuerWinkel As Integer

                NPX = APX - MPX
                NPY = APY - MPY
                Anfangswinkel = Math.Acos(NPX / radius) * (180 / Math.PI)
                If NPY < 0 Or NPX < 0 Then
                    NeuerWinkel = -Anfangswinkel


                    Do
                        NeuerWinkel = NeuerWinkel + Teilwinkel

                        NPX = (Math.Cos(NeuerWinkel / 180 * Math.PI)) * radius + MPX

                        NPY = (Math.Sin(NeuerWinkel / 180 * Math.PI)) * radius + MPY


                        index = index + 1

                        Befehlsnummer = Befehlsnummer + 1

                        ReDim Preserve Koordinaten(2, 0 To Befehlsnummer + 1)



                        Koordinaten(0, Befehlsnummer) = ObenUnten
                        Koordinaten(1, Befehlsnummer) = NPX
                        Koordinaten(2, Befehlsnummer) = NPY

                    Loop Until index = Anzlinienkreis - 1


                    EPX = (Math.Cos((Winkel / 10 - Anfangswinkel) / 180 * Math.PI)) * radius + MPX
                    EPY = (Math.Sin((Winkel / 10 - Anfangswinkel) / 180 * Math.PI)) * radius + MPY
                    ReDim Preserve Koordinaten(2, 0 To Befehlsnummer + 1)
                    Koordinaten(0, Befehlsnummer) = ObenUnten
                    Koordinaten(1, Befehlsnummer) = EPX
                    Koordinaten(2, Befehlsnummer) = EPY
                ElseIf NPY > 0 Or NPX > 0 Then
                    NeuerWinkel = Anfangswinkel


                    Do
                        NeuerWinkel = NeuerWinkel + Teilwinkel

                        NPX = (Math.Cos(NeuerWinkel / 180 * Math.PI)) * radius + MPX

                        NPY = (Math.Sin(NeuerWinkel / 180 * Math.PI)) * radius + MPY



                        index = index + 1

                        ReDim Preserve Koordinaten(2, 0 To Befehlsnummer + 1)

                        Befehlsnummer = Befehlsnummer + 1

                        Koordinaten(0, Befehlsnummer) = ObenUnten
                        Koordinaten(1, Befehlsnummer) = NPX
                        Koordinaten(2, Befehlsnummer) = NPY

                    Loop Until index = Anzlinienkreis - 1


                    EPX = (Math.Cos((Winkel / 10 + Anfangswinkel) / 180 * Math.PI)) * radius + MPX
                    EPY = (Math.Sin((Winkel / 10 + Anfangswinkel) / 180 * Math.PI)) * radius + MPY
                    Befehlsnummer = Befehlsnummer + 1
                    ReDim Preserve Koordinaten(2, 0 To Befehlsnummer + 1)
                    Koordinaten(0, Befehlsnummer) = ObenUnten
                    Koordinaten(1, Befehlsnummer) = EPX
                    Koordinaten(2, Befehlsnummer) = EPY
                End If



            End If
            n = n + 1


        Loop Until n = UBound(Zeile) + 1


        'Hier beginnt die Linienausgabe********************************************************************

        Dim stift1 As New Pen(Color.Red, 3)
        Dim stift2 As New Pen(Color.Blue, 3)
        Dim faktorzeichnen As Integer
        faktorzeichnen = skf.Text
        Dim g As Graphics
        g = Me.CreateGraphics
        Dim ko1, ko2, ko3, ko4, stz, m, j, koo1, koo2, koo3, koo4 As Integer
        Dim stift As Object
        j = 1

        For m = 0 To Befehlsnummer

            If m <= Befehlsnummer Then
                stz = Koordinaten(0, m + 1)
                If stz = 0 Then
                    stift = stift1
                Else
                    stift = stift2

                End If
            End If
            ko1 = Koordinaten(1, m) / 4
            ko2 = ((Koordinaten(2, m) + 400) / 4)
            If m <= Befehlsnummer Then
                ko3 = Koordinaten(1, m + 1) / 4
                ko4 = (Koordinaten(2, m + 1) + 400) / 4
                koo1 = ko1 / faktorzeichnen
                koo2 = ko2 / faktorzeichnen
                koo3 = ko3 / faktorzeichnen
                koo4 = ko4 / faktorzeichnen



                g.DrawLine(stift, koo3, koo4, koo1, koo2)
            End If

        Next m




    End Sub



    Private Sub Button9_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button9.Click

        Dim dateipfad As String
        Dim inhalt As String


        dateipfad = TextBox1.Text
        '*************************************** Beginn Dateiauslesen *************************
        Dim objDateiLeser As StreamReader

        objDateiLeser = New StreamReader(dateipfad)
        inhalt = objDateiLeser.ReadToEnd()


        Dim position1, position2, zaehler As Integer

        zaehler = 0
        position1 = 0
        position2 = InStr(inhalt, vbNewLine)
        If position2 > 0 Then
            Do
                position2 = InStr(position2 + 1, inhalt, vbNewLine)
                zaehler = zaehler + 1
            Loop Until zaehler = 0 Or position2 = 0

        End If
        Dim Zeile(0 To zaehler) As String
        zaehler = 0
        position2 = InStr(inhalt, vbNewLine)

        If position2 > 0 Then
            Zeile(zaehler) = Mid(inhalt, position1 + 1, position2 - 1)

            Do
                position1 = InStr(position1 + 1, inhalt, vbNewLine)
                position2 = InStr(position2 + 1, inhalt, vbNewLine)

                If position1 > 0 AndAlso position2 > 0 Then

                    zaehler = zaehler + 1

                    Zeile(zaehler) = Mid(inhalt, position1 + 2, position2 - position1 - 2)

                ElseIf position1 > position2 Then

                    zaehler = zaehler + 1

                    Zeile(zaehler) = Mid(inhalt, position1 + 2, Len(inhalt) - position1 - 1)

                End If

            Loop Until zaehler = 0 Or position1 = 0
        End If
        '****************************************Kreisbefehle zählen****************************
        Dim anzahlbefehle As Integer
        anzahlbefehle = zaehler
        Dim Kreisbefehlposition As Integer = 0
        Dim Kreisbefehlanzahl As Integer = 0
        Dim Kreislinien As Integer = 0
        Dim Anzahlkreislinien As Integer = 500
        Dim einenmehr As Integer
        einenmehr = 1

        Do
            Kreisbefehlposition = InStr(Kreisbefehlposition + 1, inhalt, "CS")
            If Kreisbefehlposition > 0 Then
                Kreislinien = Kreislinien + Anzahlkreislinien
                Kreisbefehlanzahl = Kreisbefehlanzahl + 1
            End If
        Loop Until Kreisbefehlposition = 0
        Dim Kreiskoordinaten(1, 0 To Kreislinien - 1) As Integer

        '**************************************Zähle die Anzahl der PA Befehle***********************

        Dim PositionPA As Integer = 0
        Dim AnzahlPABefehle As Integer = 0
        Do
            PositionPA = InStr(PositionPA + 1, inhalt, "PA")

            If PositionPA > 0 Then
                AnzahlPABefehle = AnzahlPABefehle + 1
            End If

        Loop Until PositionPA = 0

        '************************************Zähle Anzahl von PU/PD***********************************


        Dim PositionPU As Integer = 0
        Dim PositionPD As Integer = 0
        Dim AnzahlPUPDBefehle As Integer = 0
        Do
            PositionPU = InStr(PositionPU + 1, inhalt, "PU")

            If PositionPU > 0 Then
                AnzahlPUPDBefehle = AnzahlPUPDBefehle + 1
            End If

        Loop Until PositionPU = 0
        Do
            PositionPD = InStr(PositionPD + 1, inhalt, "PD")

            If PositionPD > 0 Then
                AnzahlPUPDBefehle = AnzahlPUPDBefehle + 1
            End If

        Loop Until PositionPD = 0



        objDateiLeser.Close()
        objDateiLeser = Nothing

        '************************Ende des Ausleseprogrammabschnittes*********************************

        '***********************Beginn Behfehlsauswertung ****************************************** 

        Dim befehl As String
        Dim n, PU, PA, PD, CS, Koordinatex, Koordinatey As Integer

        Dim erstezahl, letztezahl As Integer
        Dim ObenUnten, MomentaneAnzahlPUPD, MomentaneAnzahlCS As Integer

        MomentaneAnzahlCS = 0
        MomentaneAnzahlPUPD = 0
        PU = 0
        PA = 0
        PD = 0
        CS = 0
        n = 0
        Befehlsnummer = 0

        Do

            befehl = Zeile(n)


            PU = InStr(befehl, "PU")
            PA = InStr(befehl, "PA")
            PD = InStr(befehl, "PD")
            CS = InStr(befehl, "CS")



            '***************Befehlsauswertung PU/PD ******************************************

            If PU = 1 AndAlso PD = 0 AndAlso PA = 0 AndAlso CS = 0 Then
                ObenUnten = 0
                erstezahl = 1                   'Position der Ersten Zahl der X-Koordinate wird von Links (1) gesucht

                letztezahl = InStr(befehl, " ") 'Position der Letzten Zahl der X-Koordinate wird vom Komma aus gesucht


                If Asc(Mid(befehl, erstezahl, 1)) < 48 Or Asc(Mid(befehl, erstezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, erstezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, erstezahl, 1)) <= 57  'Falls Leerzeichen oder Buchstaben zwischen Start und Zahl dann verschiebe Position um eins nach rechts

                        erstezahl = erstezahl + 1
                    Loop
                End If

                'letzteezahl ist position des Kommas
                If Asc(Mid(befehl, letztezahl, 1)) < 48 Or Asc(Mid(befehl, letztezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, letztezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, letztezahl, 1)) <= 57  'Beginne am Ende und gehe nach links bis x8 eine Zahl wird
                        letztezahl = letztezahl - 1
                    Loop
                End If


                Koordinatex = CInt(Mid(befehl, erstezahl, letztezahl - erstezahl + 1))

                Befehlsnummer = Befehlsnummer + 1

                ReDim Preserve Koordinaten(2, 0 To Befehlsnummer + 1)

                Koordinaten(0, Befehlsnummer) = ObenUnten
                Koordinaten(1, Befehlsnummer) = Koordinatex
                erstezahl = InStr(befehl, " ")                   'Position der Ersten Zahl der X-Koordinate wird vom Komma aus gesucht

                letztezahl = Len(befehl)                         'Position der Letzten Zahl der Y-Koordinate wird vom Ende aus gesucht


                If Asc(Mid(befehl, erstezahl, 1)) < 48 Or Asc(Mid(befehl, erstezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, erstezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, erstezahl, 1)) <= 57  'Falls Leerzeichen oder Buchstaben zwischen Start und Zahl dann verschiebe Position um eins nach rechts

                        erstezahl = erstezahl + 1
                    Loop
                End If

                'letztezahl ist am Ende von befehl positioniert
                If Asc(Mid(befehl, letztezahl, 1)) < 48 Or Asc(Mid(befehl, letztezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, letztezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, letztezahl, 1)) <= 57  'Beginne am Ende und gehe nach links bis linkezahl eine Zahl wird
                        letztezahl = letztezahl - 1
                    Loop
                End If
                Koordinatey = CInt(Mid(befehl, erstezahl, letztezahl - erstezahl + 1))
                Koordinaten(2, Befehlsnummer) = Koordinatey

            ElseIf PU = 0 AndAlso PD = 1 AndAlso PA = 0 AndAlso CS = 0 Then

                ObenUnten = 1
                erstezahl = 1                   'Position der Ersten Zahl der X-Koordinate wird von Links (1) gesucht

                letztezahl = InStr(befehl, " ") 'Position der Letzten Zahl der X-Koordinate wird vom Komma aus gesucht


                If Asc(Mid(befehl, erstezahl, 1)) < 48 Or Asc(Mid(befehl, erstezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, erstezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, erstezahl, 1)) <= 57  'Falls Leerzeichen oder Buchstaben zwischen Start und Zahl dann verschiebe Position um eins nach rechts

                        erstezahl = erstezahl + 1
                    Loop
                End If

                'letzteezahl ist position des Kommas
                If Asc(Mid(befehl, letztezahl, 1)) < 48 Or Asc(Mid(befehl, letztezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, letztezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, letztezahl, 1)) <= 57  'Beginne am Ende und gehe nach links bis x8 eine Zahl wird
                        letztezahl = letztezahl - 1
                    Loop
                End If


                Koordinatex = CInt(Mid(befehl, erstezahl, letztezahl - erstezahl + 1))

                Befehlsnummer = Befehlsnummer + 1

                ReDim Preserve Koordinaten(2, 0 To Befehlsnummer + 1)

                Koordinaten(0, Befehlsnummer) = ObenUnten
                Koordinaten(1, Befehlsnummer) = Koordinatex

                erstezahl = InStr(befehl, " ")                   'Position der Ersten Zahl der X-Koordinate wird vom Komma aus gesucht

                letztezahl = Len(befehl)                         'Position der Letzten Zahl der Y-Koordinate wird vom Ende aus gesucht


                If Asc(Mid(befehl, erstezahl, 1)) < 48 Or Asc(Mid(befehl, erstezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, erstezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, erstezahl, 1)) <= 57  'Falls Leerzeichen oder Buchstaben zwischen Start und Zahl dann verschiebe Position um eins nach rechts

                        erstezahl = erstezahl + 1
                    Loop
                End If

                'letztezahl ist am Ende von befehl positioniert
                If Asc(Mid(befehl, letztezahl, 1)) < 48 Or Asc(Mid(befehl, letztezahl, 1)) > 57 Then
                    Do Until Asc(Mid(befehl, letztezahl, 1)) >= 48 AndAlso Asc(Mid(befehl, letztezahl, 1)) <= 57  'Beginne am Ende und gehe nach links bis linkezahl eine Zahl wird
                        letztezahl = letztezahl - 1
                    Loop
                End If
                Koordinatey = CInt(Mid(befehl, erstezahl, letztezahl - erstezahl + 1))
                Koordinaten(2, Befehlsnummer) = Koordinatey
                '********************************Ende PU / PD  Befehlsauswertung*********************






            End If
            n = n + 1


        Loop Until n = UBound(Zeile) + 1


        'Hier beginnt die Linienausgabe********************************************************************





        Dim faktorzeichnen As Integer
        faktorzeichnen = skf.Text






        Dim stift1 As New Pen(Color.Red, 3)
        Dim stift2 As New Pen(Color.Blue, 3)

        Dim g As Graphics
        g = Me.CreateGraphics
        Dim ko1, ko2, ko3, ko4, stz, m, j, koo1, koo2, koo3, koo4 As Integer
        Dim stift As Object
        j = 1

        For m = 0 To Befehlsnummer

            If m <= Befehlsnummer Then
                stz = Koordinaten(0, m + 1)
                If stz = 0 Then
                    stift = stift1
                Else
                    stift = stift2

                End If
            End If
            ko1 = Koordinaten(1, m) / 4
            ko2 = ((Koordinaten(2, m) + 400) / 4)
            If m <= Befehlsnummer Then
                ko3 = Koordinaten(1, m + 1) / 4
                ko4 = (Koordinaten(2, m + 1) + 400) / 4
                koo1 = ko1 / faktorzeichnen
                koo2 = ko2 / faktorzeichnen
                koo3 = ko3 / faktorzeichnen
                koo4 = ko4 / faktorzeichnen


                g.DrawLine(stift, koo3, koo4, koo1, koo2)
            End If

        Next m


    End Sub



    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16
        Dim Stiftobenoderunten As Integer

        Dim Faktorzeichnen As Double
        Faktorzeichnen = skf.Text * 2

        Dim wartezeit As Double
        wartezeit = zeit.Text


        If Befehlsnummer < 1 Then
            MsgBox("Zuerst auf Vorschau Klicken, sonst werden keine Linien eingelesen")
            GoTo Allesueberspringen
        End If

        Dim k, APX, APY, EPX, EPY, Anzlinien As Integer
        '*****************************Festlegung der Schrittfolge für beide Motoren*************************************
        Dim Motorx(4) As Integer
        Dim Motory(4) As Integer
        Motorx(1) = 3
        Motorx(2) = 6
        Motorx(3) = 12
        Motorx(4) = 9
        Motory(1) = 48
        Motory(2) = 96
        Motory(3) = 192
        Motory(4) = 144




        Stiftobenoderunten = 0


        Dim AnzzehntelSchritteX, AnzzehntelSchritteY, AnzahlMotorSchritteX, AnzahlMotorSchritteY, Schritte As Integer
        Dim UeberlaufX, Ueberlaufy, Gesamtueberlaufx, Gesamtueberlaufy As Double
        Dim Verhaeltnisxy As Double
        Dim index, z As Integer

        Dim Linienueberlaufx, Linienueberlaufy As Double
        Dim motorywert, zaehler As Integer
        zaehler = 0
        DataValue = 0

        Gesamtueberlaufx = 0
        k = 4
        z = 4
        Dim Zwischenspeicher As UInt16


        For Anzlinien = 0 To Befehlsnummer


            '***************************Hubmagnetbewegung******************************************
            If Koordinaten(0, Anzlinien + 1) <> Stiftobenoderunten Then
                Zwischenspeicher = DataValue

                If Stiftobenoderunten = 0 Then

                    DataValue = 255


                    ULStat = DaqBoard.DOut(PortNum2, DataValue)

                    If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                        Stop
                    End If
                    Stiftobenoderunten = 1

                ElseIf Stiftobenoderunten = 1 Then
                    DataValue = 0


                    ULStat = DaqBoard.DOut(PortNum2, DataValue)

                    If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                        Stop
                    End If
                    Stiftobenoderunten = 0
                End If
                DataValue = Zwischenspeicher
            End If


            '*******************************Berechnung der tats. Schritte****************************************
            APX = Koordinaten(1, Anzlinien)

            EPX = Koordinaten(1, Anzlinien + 1)


            If APX > EPX Then
                AnzzehntelSchritteX = APX - EPX
            ElseIf EPX > APX Then
                AnzzehntelSchritteX = EPX - APX
            End If
            AnzzehntelSchritteX = AnzzehntelSchritteX / Faktorzeichnen

            AnzahlMotorSchritteX = Int(AnzzehntelSchritteX / 0.113636)
            UeberlaufX = (AnzzehntelSchritteX / 0.113636) - AnzahlMotorSchritteX
            Gesamtueberlaufx = Gesamtueberlaufx + UeberlaufX

            APY = Koordinaten(2, Anzlinien)
            EPY = Koordinaten(2, Anzlinien + 1)
            If APY > EPY Then
                AnzzehntelSchritteY = APY - EPY
            ElseIf EPY > APY Then
                AnzzehntelSchritteY = EPY - APY
            End If

            AnzzehntelSchritteY = AnzzehntelSchritteY / Faktorzeichnen
            AnzahlMotorSchritteY = Int(AnzzehntelSchritteY)
            Ueberlaufy = (AnzzehntelSchritteY) - AnzahlMotorSchritteY
            Gesamtueberlaufy = Gesamtueberlaufy + Ueberlaufy


            '******************************Verhältnis für unterschiedliche Motorbewegungen berechnen*********************
            If AnzahlMotorSchritteX = 0 AndAlso AnzahlMotorSchritteY = 0 Then
                GoTo EndederMotorbewegung
            End If
            If AnzahlMotorSchritteY <> 0 AndAlso AnzahlMotorSchritteX > AnzahlMotorSchritteY Then
                Verhaeltnisxy = (AnzahlMotorSchritteX / AnzahlMotorSchritteY)
            ElseIf AnzahlMotorSchritteX <> 0 AndAlso AnzahlMotorSchritteX < AnzahlMotorSchritteY Then
                Verhaeltnisxy = (AnzahlMotorSchritteY / AnzahlMotorSchritteX)
            ElseIf AnzahlMotorSchritteX = 0 AndAlso AnzahlMotorSchritteY > 0 Then
                Verhaeltnisxy = 1

            ElseIf AnzahlMotorSchritteY = 0 AndAlso AnzahlMotorSchritteX > 0 Then
                Verhaeltnisxy = 1


            End If


            '***********************Festlegung der Schritte und Linienüberlauf***************************************
            If AnzahlMotorSchritteX < AnzahlMotorSchritteY Then
                Schritte = AnzahlMotorSchritteX

                Linienueberlaufy = Gesamtueberlaufy
                Gesamtueberlaufy = 0
                If Schritte = 0 Then
                    Schritte = 1
                    Linienueberlaufy = Gesamtueberlaufy + AnzahlMotorSchritteY
                End If
            ElseIf AnzahlMotorSchritteX > AnzahlMotorSchritteY Then
                Schritte = AnzahlMotorSchritteY
                Linienueberlaufx = Gesamtueberlaufx
                Gesamtueberlaufx = 0
                If Schritte = 0 Then
                    Schritte = 1
                    Linienueberlaufx = Gesamtueberlaufx + AnzahlMotorSchritteX

                End If
            End If

            For index = 1 To Schritte


                '*********************************Ausgabe wenn beide Motoren sich bewegen******************************

                If EPX > APX AndAlso EPX <> APX Then
                    k = k + 1
                End If
                If EPY > APY AndAlso EPY <> APY Then
                    z = z + 1
                End If
                If EPX < APX AndAlso EPX <> APX Then
                    k = k - 1
                End If
                If EPY < APY AndAlso EPY <> APY Then
                    z = z - 1
                End If


                If z = 5 Then
                    z = 1
                End If
                If z = 0 Then
                    z = 4
                End If
                If k = 5 Then
                    k = 1
                End If
                If k = 0 Then
                    k = 4
                End If
                DataValue = Motorx(k) + Motory(z)


                ULStat = DaqBoard.DOut(PortNum, DataValue)

                If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                    Stop
                End If

                Sleep(wartezeit)

                motorywert = Motory(z)

                '**************************Ausgabe wenn sich nur ein Motor bewegt***********************************
                If AnzahlMotorSchritteX > AnzahlMotorSchritteY Then
                    Linienueberlaufx = Linienueberlaufx + (Verhaeltnisxy - 1)
                End If
                If AnzahlMotorSchritteX < AnzahlMotorSchritteY Then
                    Linienueberlaufy = Linienueberlaufy + (Verhaeltnisxy - 1)
                End If
                If Linienueberlaufx > 1 Then

                    Do Until Linienueberlaufx < 1
                        zaehler = zaehler + 1



                        If EPX > APX Then
                            k = k + 1
                        End If
                        If EPX < APX Then
                            k = k - 1
                        End If
                        If k = 5 Then
                            k = 1
                        End If
                        If k = 0 Then
                            k = 4
                        End If
                        DataValue = Motorx(k) + motorywert

                        ULStat = DaqBoard.DOut(PortNum, DataValue)

                        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                            Stop
                        End If
                        Sleep(wartezeit)

                        Linienueberlaufx = Linienueberlaufx - 1



                        If zaehler = 1 Then
                            motorywert = 0
                            zaehler = 0
                        End If

                    Loop

                End If

                If Linienueberlaufy > 1 Then
                    Do Until Linienueberlaufy < 1

                        If EPY > APY Then
                            z = z + 1
                        End If
                        If EPY < APY Then
                            z = z - 1
                        End If
                        If z = 5 Then
                            z = 1
                        End If
                        If z = 0 Then
                            z = 4
                        End If
                        DataValue = Motory(z)


                        ULStat = DaqBoard.DOut(PortNum, DataValue)

                        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                            Stop
                        End If

                        Sleep(wartezeit)

                        Linienueberlaufy = Linienueberlaufy - 1
                    Loop
                End If

            Next index
            If AnzahlMotorSchritteX > AnzahlMotorSchritteY Then
                Gesamtueberlaufx = Linienueberlaufx
                Linienueberlaufx = 0
                Gesamtueberlaufy = Gesamtueberlaufy
            ElseIf AnzahlMotorSchritteX < AnzahlMotorSchritteY Then
                Gesamtueberlaufy = Linienueberlaufy
                Linienueberlaufy = 0
                Gesamtueberlaufx = Gesamtueberlaufx
            End If


EndederMotorbewegung:


        Next Anzlinien




        ' write the value to FirstPortA
        '  Parameters:
        '    PortNum    :the output port
        '    DataValue  :the value written to the port



Allesueberspringen:

    End Sub







    Private Sub Button8_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button8.Click
        
        Dim DataValue As UInt16
        Dim Stiftobenoderunten As Integer

        Stiftobenoderunten = 1
        DataValue = 0


        ULStat = DaqBoard.DOut(PortNum2, DataValue)

        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        End If

    End Sub

    Private Sub Button7_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button7.Click
        Dim DataValue As UInt16
        Dim Stiftobenoderunten As Integer

        Stiftobenoderunten = 0
        DataValue = 255


        ULStat = DaqBoard.DOut(PortNum2, DataValue)

        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        End If
    End Sub




    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16

        Dim Motorx(4) As Integer
        Dim Motory(4) As Integer
        Motorx(1) = 3
        Motorx(2) = 6
        Motorx(3) = 12
        Motorx(4) = 9
        Motory(1) = 48
        Motory(2) = 96
        Motory(3) = 192
        Motory(4) = 144
        Dim k As Integer
        k = 1

        Dim i As Integer

        For i = 0 To 250

           




            k = k - 1

            If k = 5 Then
                k = 1
            End If
            If k = 0 Then
                k = 4
            End If
            DataValue = Motory(k)

            ULStat = DaqBoard.DOut(PortNum, DataValue)

            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                Stop
            End If
            Sleep(6)
        Next i

    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16

        Dim Motorx(4) As Integer
        Dim Motory(4) As Integer
        Motorx(1) = 3
        Motorx(2) = 6
        Motorx(3) = 12
        Motorx(4) = 9
        Motory(1) = 48
        Motory(2) = 96
        Motory(3) = 192
        Motory(4) = 144
        Dim k As Integer
        k = 1

        Dim i As Integer

        For i = 0 To 200

           


            k = k + 1

            If k = 5 Then
                k = 1
            End If
            If k = 0 Then
                k = 4
            End If
            DataValue = Motory(k)

            ULStat = DaqBoard.DOut(PortNum, DataValue)

            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                Stop
            End If
            Sleep(4)
        Next i

    End Sub

    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16

        Dim Motorx(4) As Integer
        Dim Motory(4) As Integer
        Motorx(1) = 3
        Motorx(2) = 6
        Motorx(3) = 12
        Motorx(4) = 9
        Motory(1) = 48
        Motory(2) = 96
        Motory(3) = 192
        Motory(4) = 144
        Dim k As Integer
        k = 1

        Dim i As Integer

        For i = 0 To 2000


            k = k + 1

            If k = 5 Then
                k = 1
            End If
            If k = 0 Then
                k = 4
            End If
            DataValue = Motorx(k)

            ULStat = DaqBoard.DOut(PortNum, DataValue)

            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                Stop
            End If
            Sleep(2)
        Next i

    End Sub

    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16

        Dim Motorx(4) As Integer
        Dim Motory(4) As Integer
        Motorx(1) = 3
        Motorx(2) = 6
        Motorx(3) = 12
        Motorx(4) = 9
        Motory(1) = 48
        Motory(2) = 96
        Motory(3) = 192
        Motory(4) = 144
        Dim k As Integer
        k = 1

        Dim i As Integer

        For i = 0 To 2000

          

            k = k - 1

            If k = 5 Then
                k = 1
            End If
            If k = 0 Then
                k = 4
            End If
            DataValue = Motorx(k)

            ULStat = DaqBoard.DOut(PortNum, DataValue)

            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                Stop
            End If
            Sleep(2)
        Next i

    End Sub






   
    
End Class