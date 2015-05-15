<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class DrawingView
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
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(DrawingView))
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
        Me.Lbl_description = New System.Windows.Forms.Label()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.Lbl_order = New System.Windows.Forms.Label()
        Me.tip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.GroupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'Btn_save
        '
        Me.Btn_save.Location = New System.Drawing.Point(9, 397)
        Me.Btn_save.Name = "Btn_save"
        Me.Btn_save.Size = New System.Drawing.Size(95, 29)
        Me.Btn_save.TabIndex = 0
        Me.Btn_save.Text = "Speichern"
        Me.tip1.SetToolTip(Me.Btn_save, "Hier koennen Sie Ihr Werk abspeichern")
        Me.Btn_save.UseVisualStyleBackColor = True
        '
        'Btn_cancel
        '
        Me.Btn_cancel.Location = New System.Drawing.Point(231, 397)
        Me.Btn_cancel.Name = "Btn_cancel"
        Me.Btn_cancel.Size = New System.Drawing.Size(95, 29)
        Me.Btn_cancel.TabIndex = 1
        Me.Btn_cancel.Text = "Abbrechen"
        Me.tip1.SetToolTip(Me.Btn_cancel, "Hier koennen Sie zum Hauptprogramm zurueckkehren; die Daten werden dabei nicht ge" & _
        "speichert")
        Me.Btn_cancel.UseVisualStyleBackColor = True
        '
        'Btn_back
        '
        Me.Btn_back.Enabled = False
        Me.Btn_back.Image = CType(resources.GetObject("Btn_back.Image"), System.Drawing.Image)
        Me.Btn_back.Location = New System.Drawing.Point(290, 49)
        Me.Btn_back.Name = "Btn_back"
        Me.Btn_back.Size = New System.Drawing.Size(36, 29)
        Me.Btn_back.TabIndex = 3
        Me.Btn_back.UseVisualStyleBackColor = True
        '
        'Btn_line
        '
        Me.Btn_line.Image = CType(resources.GetObject("Btn_line.Image"), System.Drawing.Image)
        Me.Btn_line.Location = New System.Drawing.Point(290, 94)
        Me.Btn_line.Name = "Btn_line"
        Me.Btn_line.Size = New System.Drawing.Size(36, 29)
        Me.Btn_line.TabIndex = 4
        Me.tip1.SetToolTip(Me.Btn_line, """Linie""")
        Me.Btn_line.UseVisualStyleBackColor = True
        '
        'Btn_circle
        '
        Me.Btn_circle.Image = CType(resources.GetObject("Btn_circle.Image"), System.Drawing.Image)
        Me.Btn_circle.Location = New System.Drawing.Point(290, 142)
        Me.Btn_circle.Name = "Btn_circle"
        Me.Btn_circle.Size = New System.Drawing.Size(36, 29)
        Me.Btn_circle.TabIndex = 5
        Me.tip1.SetToolTip(Me.Btn_circle, "Viertelkreis")
        Me.Btn_circle.UseVisualStyleBackColor = True
        '
        'Btn_import
        '
        Me.Btn_import.Location = New System.Drawing.Point(119, 397)
        Me.Btn_import.Name = "Btn_import"
        Me.Btn_import.Size = New System.Drawing.Size(104, 29)
        Me.Btn_import.TabIndex = 6
        Me.Btn_import.Text = "Drucken"
        Me.tip1.SetToolTip(Me.Btn_import, "Hier koennen Sie Ihr Werk ausdrucken lassen, die Datei wird jedoch nicht gespeich" & _
        "ert")
        Me.Btn_import.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(270, 204)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(56, 13)
        Me.Label1.TabIndex = 7
        Me.Label1.Text = "X - Achse:"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(272, 248)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(56, 13)
        Me.Label2.TabIndex = 8
        Me.Label2.Text = "Y - Achse:"
        '
        'Group_1
        '
        Me.Group_1.BackColor = System.Drawing.Color.Black
        Me.Group_1.Cursor = System.Windows.Forms.Cursors.Arrow
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
        'Lbl_description
        '
        Me.Lbl_description.AutoSize = True
        Me.Lbl_description.Location = New System.Drawing.Point(264, 174)
        Me.Lbl_description.Name = "Lbl_description"
        Me.Lbl_description.Size = New System.Drawing.Size(0, 13)
        Me.Lbl_description.TabIndex = 12
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.Lbl_order)
        Me.GroupBox1.Location = New System.Drawing.Point(12, 298)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(342, 80)
        Me.GroupBox1.TabIndex = 13
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Anweisung fuer den naechsten Schritt"
        '
        'Lbl_order
        '
        Me.Lbl_order.AutoSize = True
        Me.Lbl_order.Location = New System.Drawing.Point(6, 25)
        Me.Lbl_order.Name = "Lbl_order"
        Me.Lbl_order.Size = New System.Drawing.Size(290, 13)
        Me.Lbl_order.TabIndex = 0
        Me.Lbl_order.Text = "Klicken Sie zum Zeichnen auf die Linie bzw. den Viertelkreis"
        '
        'DrawingView
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(356, 438)
        Me.ControlBox = False
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.Lbl_description)
        Me.Controls.Add(Me.Group_1)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Btn_import)
        Me.Controls.Add(Me.Btn_circle)
        Me.Controls.Add(Me.Btn_line)
        Me.Controls.Add(Me.Btn_back)
        Me.Controls.Add(Me.Btn_cancel)
        Me.Controls.Add(Me.Btn_save)
        Me.Name = "DrawingView"
        Me.Text = "Zeichnung"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
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
    Friend WithEvents Lbl_description As System.Windows.Forms.Label
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents Lbl_order As System.Windows.Forms.Label
    Friend WithEvents tip1 As System.Windows.Forms.ToolTip
End Class
