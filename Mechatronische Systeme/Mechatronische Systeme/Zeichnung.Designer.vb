<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Zeichnung
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
        Me.Btn_save = New System.Windows.Forms.Button()
        Me.Btn_cancel = New System.Windows.Forms.Button()
        Me.Btn_back = New System.Windows.Forms.Button()
        Me.Btn_line = New System.Windows.Forms.Button()
        Me.Btn_circle = New System.Windows.Forms.Button()
        Me.Btn_import = New System.Windows.Forms.Button()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Group_1 = New System.Windows.Forms.GroupBox()
        Me.SaveFileDialog = New System.Windows.Forms.SaveFileDialog()
        Me.SuspendLayout()
        '
        'Btn_save
        '
        Me.Btn_save.Location = New System.Drawing.Point(11, 315)
        Me.Btn_save.Name = "Btn_save"
        Me.Btn_save.Size = New System.Drawing.Size(95, 29)
        Me.Btn_save.TabIndex = 0
        Me.Btn_save.Text = "Speichern"
        Me.Btn_save.UseVisualStyleBackColor = True
        '
        'Btn_cancel
        '
        Me.Btn_cancel.Location = New System.Drawing.Point(233, 315)
        Me.Btn_cancel.Name = "Btn_cancel"
        Me.Btn_cancel.Size = New System.Drawing.Size(95, 29)
        Me.Btn_cancel.TabIndex = 1
        Me.Btn_cancel.Text = "Abbrechen"
        Me.Btn_cancel.UseVisualStyleBackColor = True
        '
        'Btn_back
        '
        Me.Btn_back.Location = New System.Drawing.Point(290, 49)
        Me.Btn_back.Name = "Btn_back"
        Me.Btn_back.Size = New System.Drawing.Size(36, 29)
        Me.Btn_back.TabIndex = 3
        Me.Btn_back.Text = "Button3"
        Me.Btn_back.UseVisualStyleBackColor = True
        '
        'Btn_line
        '
        Me.Btn_line.Location = New System.Drawing.Point(290, 94)
        Me.Btn_line.Name = "Btn_line"
        Me.Btn_line.Size = New System.Drawing.Size(36, 29)
        Me.Btn_line.TabIndex = 4
        Me.Btn_line.Text = "Button4"
        Me.Btn_line.UseVisualStyleBackColor = True
        '
        'Btn_circle
        '
        Me.Btn_circle.Location = New System.Drawing.Point(290, 142)
        Me.Btn_circle.Name = "Btn_circle"
        Me.Btn_circle.Size = New System.Drawing.Size(36, 29)
        Me.Btn_circle.TabIndex = 5
        Me.Btn_circle.Text = "Button5"
        Me.Btn_circle.UseVisualStyleBackColor = True
        '
        'Btn_import
        '
        Me.Btn_import.Location = New System.Drawing.Point(121, 315)
        Me.Btn_import.Name = "Btn_import"
        Me.Btn_import.Size = New System.Drawing.Size(104, 29)
        Me.Btn_import.TabIndex = 6
        Me.Btn_import.Text = "Drucken"
        Me.Btn_import.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(289, 204)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(39, 13)
        Me.Label1.TabIndex = 7
        Me.Label1.Text = "Label1"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(289, 267)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(39, 13)
        Me.Label2.TabIndex = 8
        Me.Label2.Text = "Label2"
        '
        'Group_1
        '
        Me.Group_1.BackColor = System.Drawing.Color.Black
        Me.Group_1.ForeColor = System.Drawing.Color.White
        Me.Group_1.Location = New System.Drawing.Point(12, 17)
        Me.Group_1.Name = "Group_1"
        Me.Group_1.Size = New System.Drawing.Size(246, 263)
        Me.Group_1.TabIndex = 11
        Me.Group_1.TabStop = False
        Me.Group_1.Text = "Zeichenbrett"
        '
        'SaveFileDialog
        '
        Me.SaveFileDialog.DefaultExt = "txt"
        '
        'Zeichnung
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(355, 352)
        Me.Controls.Add(Me.Group_1)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Btn_import)
        Me.Controls.Add(Me.Btn_circle)
        Me.Controls.Add(Me.Btn_line)
        Me.Controls.Add(Me.Btn_back)
        Me.Controls.Add(Me.Btn_cancel)
        Me.Controls.Add(Me.Btn_save)
        Me.Name = "Zeichnung"
        Me.Text = "Zeichnung"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Btn_save As System.Windows.Forms.Button
    Friend WithEvents Btn_cancel As System.Windows.Forms.Button
    Friend WithEvents Btn_back As System.Windows.Forms.Button
    Friend WithEvents Btn_line As System.Windows.Forms.Button
    Friend WithEvents Btn_circle As System.Windows.Forms.Button
    Friend WithEvents Btn_import As System.Windows.Forms.Button
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Group_1 As System.Windows.Forms.GroupBox
    Friend WithEvents SaveFileDialog As System.Windows.Forms.SaveFileDialog
End Class
