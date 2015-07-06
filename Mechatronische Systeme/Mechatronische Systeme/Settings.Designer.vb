<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Settings
    Inherits System.Windows.Forms.Form

    'Das Formular überschreibt den Löschvorgang, um die Komponentenliste zu bereinigen.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Wird vom Windows Form-Designer benötigt.
    Private components As System.ComponentModel.IContainer

    'Hinweis: Die folgende Prozedur ist für den Windows Form-Designer erforderlich.
    'Das Bearbeiten ist mit dem Windows Form-Designer möglich.  
    'Das Bearbeiten mit dem Code-Editor ist nicht möglich.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.Lbl_1 = New System.Windows.Forms.Label()
        Me.Btn_save = New System.Windows.Forms.Button()
        Me.TxtBox_1 = New System.Windows.Forms.TextBox()
        Me.TxtBox_2 = New System.Windows.Forms.TextBox()
        Me.Lbl_2 = New System.Windows.Forms.Label()
        Me.Btn_cancel = New System.Windows.Forms.Button()
        Me.Scroll_1 = New System.Windows.Forms.HScrollBar()
        Me.Lbl_3 = New System.Windows.Forms.Label()
        Me.Lbl_4 = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'Lbl_1
        '
        Me.Lbl_1.AutoSize = True
        Me.Lbl_1.Location = New System.Drawing.Point(12, 35)
        Me.Lbl_1.Name = "Lbl_1"
        Me.Lbl_1.Size = New System.Drawing.Size(0, 13)
        Me.Lbl_1.TabIndex = 0
        '
        'Btn_save
        '
        Me.Btn_save.Location = New System.Drawing.Point(15, 221)
        Me.Btn_save.Name = "Btn_save"
        Me.Btn_save.Size = New System.Drawing.Size(88, 29)
        Me.Btn_save.TabIndex = 1
        Me.Btn_save.Text = "Speichern"
        Me.Btn_save.UseVisualStyleBackColor = True
        '
        'TxtBox_1
        '
        Me.TxtBox_1.Location = New System.Drawing.Point(174, 28)
        Me.TxtBox_1.Name = "TxtBox_1"
        Me.TxtBox_1.Size = New System.Drawing.Size(105, 20)
        Me.TxtBox_1.TabIndex = 2
        '
        'TxtBox_2
        '
        Me.TxtBox_2.Location = New System.Drawing.Point(174, 79)
        Me.TxtBox_2.Name = "TxtBox_2"
        Me.TxtBox_2.Size = New System.Drawing.Size(105, 20)
        Me.TxtBox_2.TabIndex = 3
        '
        'Lbl_2
        '
        Me.Lbl_2.AutoSize = True
        Me.Lbl_2.Location = New System.Drawing.Point(12, 79)
        Me.Lbl_2.Name = "Lbl_2"
        Me.Lbl_2.Size = New System.Drawing.Size(0, 13)
        Me.Lbl_2.TabIndex = 4
        '
        'Btn_cancel
        '
        Me.Btn_cancel.Location = New System.Drawing.Point(133, 221)
        Me.Btn_cancel.Name = "Btn_cancel"
        Me.Btn_cancel.Size = New System.Drawing.Size(88, 29)
        Me.Btn_cancel.TabIndex = 5
        Me.Btn_cancel.Text = "Abbrechen"
        Me.Btn_cancel.UseVisualStyleBackColor = True
        '
        'Scroll_1
        '
        Me.Scroll_1.Location = New System.Drawing.Point(15, 165)
        Me.Scroll_1.Name = "Scroll_1"
        Me.Scroll_1.Size = New System.Drawing.Size(206, 22)
        Me.Scroll_1.TabIndex = 6
        '
        'Lbl_3
        '
        Me.Lbl_3.AutoSize = True
        Me.Lbl_3.Location = New System.Drawing.Point(12, 152)
        Me.Lbl_3.Name = "Lbl_3"
        Me.Lbl_3.Size = New System.Drawing.Size(40, 13)
        Me.Lbl_3.TabIndex = 7
        Me.Lbl_3.Text = "Tuning"
        '
        'Lbl_4
        '
        Me.Lbl_4.AutoSize = True
        Me.Lbl_4.Location = New System.Drawing.Point(171, 152)
        Me.Lbl_4.Name = "Lbl_4"
        Me.Lbl_4.Size = New System.Drawing.Size(33, 13)
        Me.Lbl_4.TabIndex = 8
        Me.Lbl_4.Text = "Wert:"
        '
        'Settings
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(293, 262)
        Me.Controls.Add(Me.Lbl_4)
        Me.Controls.Add(Me.Lbl_3)
        Me.Controls.Add(Me.Scroll_1)
        Me.Controls.Add(Me.Btn_cancel)
        Me.Controls.Add(Me.Lbl_2)
        Me.Controls.Add(Me.TxtBox_2)
        Me.Controls.Add(Me.TxtBox_1)
        Me.Controls.Add(Me.Btn_save)
        Me.Controls.Add(Me.Lbl_1)
        Me.Name = "Settings"
        Me.Text = "Einstellungen"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Lbl_1 As System.Windows.Forms.Label
    Friend WithEvents Btn_save As System.Windows.Forms.Button
    Friend WithEvents TxtBox_1 As System.Windows.Forms.TextBox
    Friend WithEvents TxtBox_2 As System.Windows.Forms.TextBox
    Friend WithEvents Lbl_2 As System.Windows.Forms.Label
    Friend WithEvents Btn_cancel As System.Windows.Forms.Button
    Friend WithEvents Scroll_1 As System.Windows.Forms.HScrollBar
    Friend WithEvents Lbl_3 As System.Windows.Forms.Label
    Friend WithEvents Lbl_4 As System.Windows.Forms.Label
End Class
