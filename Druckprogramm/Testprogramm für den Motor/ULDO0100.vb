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
Public Class frmSize
    Friend Ignore As Boolean

    Private Property DialogResult As DialogResult

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        'Abbrechen gedrückt
        Me.DialogResult = Windows.Forms.DialogResult.Cancel
        Me.Close()
    End Sub
    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        'OK gedrückt
        Me.DialogResult = Windows.Forms.DialogResult.OK
        Me.Close()
    End Sub
    Private Sub frmSize_FormClosing(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles Me.FormClosing
        'Form schließen abbrechen, wenn DialogResult nicht definiert ist.
        If Me.DialogResult = Windows.Forms.DialogResult.None Then
            e.Cancel = True
        End If
    End Sub
    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        frmMainForm.Open()
        If frmMainForm.FileSelected = True Then
            Ignore = True
            Me.DialogResult = Windows.Forms.DialogResult.OK
            Me.Close()
        End If
    End Sub

    Private Sub Close()
        Throw New NotImplementedException
    End Sub

    Private Function frmMainForm() As Object
        Throw New NotImplementedException
    End Function

End Class
Public Class frmSetDigOut
    Inherits System.Windows.Forms.Form

    Const PortNum As MccDaq.DigitalPortType = MccDaq.DigitalPortType.FirstPortA ' set port to use


    Const Direction As MccDaq.DigitalPortDirection = MccDaq.DigitalPortDirection.DigitalOut


    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Button2 As System.Windows.Forms.Button ' program digital port A for output

    'Create a new MccBoard object for Board 0 
    Private DaqBoard As MccDaq.MccBoard = New MccDaq.MccBoard(0)

    Private Property minLeange As Object

    Private Property Leange As Object

    Private Sub cmdEndProgram_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmdEndProgram.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16

        DataValue = Convert.ToUInt16(0)

        ULStat = DaqBoard.DOut(PortNum, DataValue)
        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop

        End

    End Sub

    Private Sub hsbSetDOutVal_Change(ByVal newScrollValue As Integer)
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16

        ' get a value to write to the port


        txtValSet.Text = DataValue.ToString("0")

        ' write the value to FirstPortA
        '  Parameters:
        '    PortNum    :the output port
        '    DataValue  :the value written to the port


        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
            Stop
        Else
            lblDataValOut.Text = "Value written to FirstPortA:"
            lblShowValOut.Text = DataValue.ToString("0")
        End If

    End Sub

    Private Sub txtValSet_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles txtValSet.TextChanged

        If Val(txtValSet.Text) > 255 Then txtValSet.Text = "255"
        hsbSetDOutVal.Value = Integer.Parse(txtValSet.Text)

    End Sub
    Private Sub hsbSetDOutVal_Scroll(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.ScrollEventArgs) Handles hsbSetDOutVal.Scroll
        Select Case eventArgs.Type
            Case System.Windows.Forms.ScrollEventType.EndScroll
                hsbSetDOutVal_Change(eventArgs.NewValue)
        End Select
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
    Public WithEvents cmdEndProgram As System.Windows.Forms.Button
    Public WithEvents txtValSet As System.Windows.Forms.TextBox
    Public WithEvents hsbSetDOutVal As System.Windows.Forms.HScrollBar
    Public WithEvents lblShowValOut As System.Windows.Forms.Label
    Public WithEvents lblDataValOut As System.Windows.Forms.Label
    Public WithEvents lblValSet As System.Windows.Forms.Label
    Public WithEvents lblInstruct As System.Windows.Forms.Label
    Public WithEvents lblDemoFunction As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cmdEndProgram = New System.Windows.Forms.Button()
        Me.txtValSet = New System.Windows.Forms.TextBox()
        Me.hsbSetDOutVal = New System.Windows.Forms.HScrollBar()
        Me.lblShowValOut = New System.Windows.Forms.Label()
        Me.lblDataValOut = New System.Windows.Forms.Label()
        Me.lblValSet = New System.Windows.Forms.Label()
        Me.lblInstruct = New System.Windows.Forms.Label()
        Me.lblDemoFunction = New System.Windows.Forms.Label()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'cmdEndProgram
        '
        Me.cmdEndProgram.BackColor = System.Drawing.SystemColors.Control
        Me.cmdEndProgram.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmdEndProgram.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmdEndProgram.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cmdEndProgram.Location = New System.Drawing.Point(248, 216)
        Me.cmdEndProgram.Name = "cmdEndProgram"
        Me.cmdEndProgram.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmdEndProgram.Size = New System.Drawing.Size(57, 33)
        Me.cmdEndProgram.TabIndex = 7
        Me.cmdEndProgram.Text = "Quit"
        Me.cmdEndProgram.UseVisualStyleBackColor = False
        '
        'txtValSet
        '
        Me.txtValSet.AcceptsReturn = True
        Me.txtValSet.BackColor = System.Drawing.SystemColors.Window
        Me.txtValSet.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.txtValSet.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtValSet.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtValSet.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtValSet.Location = New System.Drawing.Point(264, 120)
        Me.txtValSet.MaxLength = 0
        Me.txtValSet.Name = "txtValSet"
        Me.txtValSet.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtValSet.Size = New System.Drawing.Size(41, 20)
        Me.txtValSet.TabIndex = 4
        Me.txtValSet.Text = "0"
        '
        'hsbSetDOutVal
        '
        Me.hsbSetDOutVal.Cursor = System.Windows.Forms.Cursors.Default
        Me.hsbSetDOutVal.LargeChange = 51
        Me.hsbSetDOutVal.Location = New System.Drawing.Point(24, 120)
        Me.hsbSetDOutVal.Maximum = 305
        Me.hsbSetDOutVal.Name = "hsbSetDOutVal"
        Me.hsbSetDOutVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.hsbSetDOutVal.Size = New System.Drawing.Size(225, 17)
        Me.hsbSetDOutVal.TabIndex = 1
        Me.hsbSetDOutVal.TabStop = True
        '
        'lblShowValOut
        '
        Me.lblShowValOut.BackColor = System.Drawing.SystemColors.Window
        Me.lblShowValOut.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblShowValOut.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblShowValOut.ForeColor = System.Drawing.Color.Blue
        Me.lblShowValOut.Location = New System.Drawing.Point(224, 176)
        Me.lblShowValOut.Name = "lblShowValOut"
        Me.lblShowValOut.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblShowValOut.Size = New System.Drawing.Size(57, 17)
        Me.lblShowValOut.TabIndex = 3
        '
        'lblDataValOut
        '
        Me.lblDataValOut.BackColor = System.Drawing.SystemColors.Window
        Me.lblDataValOut.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDataValOut.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDataValOut.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDataValOut.Location = New System.Drawing.Point(32, 176)
        Me.lblDataValOut.Name = "lblDataValOut"
        Me.lblDataValOut.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDataValOut.Size = New System.Drawing.Size(185, 17)
        Me.lblDataValOut.TabIndex = 2
        '
        'lblValSet
        '
        Me.lblValSet.BackColor = System.Drawing.SystemColors.Window
        Me.lblValSet.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblValSet.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblValSet.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblValSet.Location = New System.Drawing.Point(256, 96)
        Me.lblValSet.Name = "lblValSet"
        Me.lblValSet.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblValSet.Size = New System.Drawing.Size(65, 17)
        Me.lblValSet.TabIndex = 6
        Me.lblValSet.Text = "Value set:"
        '
        'lblInstruct
        '
        Me.lblInstruct.BackColor = System.Drawing.SystemColors.Window
        Me.lblInstruct.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblInstruct.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblInstruct.ForeColor = System.Drawing.Color.Red
        Me.lblInstruct.Location = New System.Drawing.Point(56, 48)
        Me.lblInstruct.Name = "lblInstruct"
        Me.lblInstruct.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblInstruct.Size = New System.Drawing.Size(201, 48)
        Me.lblInstruct.TabIndex = 5
        Me.lblInstruct.Text = "Dies ist das testprogram für die Ports 21 bis 24 von rechts nach links kommt eine" & _
            " Signalausgabe des Rechteckmusters einfach auf Start klicken"
        Me.lblInstruct.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'lblDemoFunction
        '
        Me.lblDemoFunction.BackColor = System.Drawing.SystemColors.Window
        Me.lblDemoFunction.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblDemoFunction.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblDemoFunction.ForeColor = System.Drawing.SystemColors.WindowText
        Me.lblDemoFunction.Location = New System.Drawing.Point(24, 8)
        Me.lblDemoFunction.Name = "lblDemoFunction"
        Me.lblDemoFunction.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblDemoFunction.Size = New System.Drawing.Size(289, 25)
        Me.lblDemoFunction.TabIndex = 0
        Me.lblDemoFunction.Text = "Demonstration of MccDaq.MccBoard.DOut()"
        Me.lblDemoFunction.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(48, 216)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(75, 23)
        Me.Button1.TabIndex = 8
        Me.Button1.Text = "Start"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(152, 216)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(90, 39)
        Me.Button2.TabIndex = 9
        Me.Button2.Text = "Nichts passiert"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'frmSetDigOut
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 13)
        Me.BackColor = System.Drawing.SystemColors.Window
        Me.ClientSize = New System.Drawing.Size(331, 267)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.cmdEndProgram)
        Me.Controls.Add(Me.txtValSet)
        Me.Controls.Add(Me.hsbSetDOutVal)
        Me.Controls.Add(Me.lblShowValOut)
        Me.Controls.Add(Me.lblDataValOut)
        Me.Controls.Add(Me.lblValSet)
        Me.Controls.Add(Me.lblInstruct)
        Me.Controls.Add(Me.lblDemoFunction)
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Location = New System.Drawing.Point(7, 103)
        Me.Name = "frmSetDigOut"
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Universal Library Digital Output"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
#End Region

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

        If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then Stop


    End Sub
#End Region

    Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Dim ULStat As MccDaq.ErrorInfo
        Dim DataValue As UInt16


        DataValue = 0

        Dim k, i, z, Yfaktor, Xfaktor As Integer
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

        k = 0
        Yfaktor = 0
        Xfaktor = 0
        Dim anzschritte As Integer
        anzschritte = 10000
        Dim zaehler As Integer
        zaehler = 0
        Dim Restschritte As Integer
        Dim warte As Integer
        warte = 5

        Restschritte = anzschritte



        For i = 0 To anzschritte

            If anzschritte > 100 Then
                zaehler = zaehler + 1
                Restschritte = Restschritte - 1
                If Restschritte > 50 Then
                    If zaehler = 10 AndAlso warte > 2 Then
                        warte = warte - 1
                        zaehler = 0
                    End If
                End If
                If Restschritte < 50 Then
                    If zaehler >= 10 AndAlso warte < 5 Then
                        warte = warte + 1

                        zaehler = 0
                    End If
                End If
            End If

            k = k + 1

            Yfaktor = Yfaktor + 1
            If Yfaktor = 8 Then
                z = z + 1
                Yfaktor = 0
            End If


            If k = 5 Then
                k = 1
            End If
            If z = 5 Then
                z = 1
            End If
            DataValue = Motorx(k) + Motory(z)
            Sleep(warte)
            ULStat = DaqBoard.DOut(PortNum, DataValue)


            If ULStat.Value <> MccDaq.ErrorInfo.ErrorCode.NoErrors Then
                Stop
            End If

        Next i

        ' write the value to FirstPortA
        '  Parameters:
        '    PortNum    :the output port
        '    DataValue  :the value written to the port





    End Sub

    Private Sub frmSetDigOut_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click

        MsgBox("Hallo Studenten!")

    End Sub

    Private Sub lblInstruct_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles lblInstruct.Click

    End Sub
End Class