<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class MainView
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(MainView))
        Me.Btn_start = New System.Windows.Forms.Button()
        Me.Lbl_progress = New System.Windows.Forms.Label()
        Me.Lbl_filepath = New System.Windows.Forms.Label()
        Me.Progress_1 = New System.Windows.Forms.ProgressBar()
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip()
        Me.DateiToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItm_1 = New System.Windows.Forms.ToolStripMenuItem()
        Me.BeendenToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BearbeitenToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItm_2 = New System.Windows.Forms.ToolStripMenuItem()
        Me.Opn_filepath = New System.Windows.Forms.OpenFileDialog()
        Me.Lbl_preview = New System.Windows.Forms.Label()
        Me.Group_1 = New System.Windows.Forms.GroupBox()
        Me.Group_2 = New System.Windows.Forms.GroupBox()
        Me.Btn_pause = New System.Windows.Forms.Button()
        Me.Btn_stop = New System.Windows.Forms.Button()
        Me.MenuStrip1.SuspendLayout()
        Me.SuspendLayout()
        '
        'Btn_start
        '
        Me.Btn_start.ForeColor = System.Drawing.Color.Black
        Me.Btn_start.Location = New System.Drawing.Point(12, 433)
        Me.Btn_start.Name = "Btn_start"
        Me.Btn_start.Size = New System.Drawing.Size(164, 34)
        Me.Btn_start.TabIndex = 0
        Me.Btn_start.Text = "Start"
        Me.Btn_start.UseVisualStyleBackColor = True
        '
        'Lbl_progress
        '
        Me.Lbl_progress.AutoSize = True
        Me.Lbl_progress.ForeColor = System.Drawing.Color.Black
        Me.Lbl_progress.Location = New System.Drawing.Point(12, 380)
        Me.Lbl_progress.Name = "Lbl_progress"
        Me.Lbl_progress.Size = New System.Drawing.Size(53, 13)
        Me.Lbl_progress.TabIndex = 2
        Me.Lbl_progress.Text = "Fortschritt"
        '
        'Lbl_filepath
        '
        Me.Lbl_filepath.AutoSize = True
        Me.Lbl_filepath.ForeColor = System.Drawing.Color.Black
        Me.Lbl_filepath.Location = New System.Drawing.Point(15, 339)
        Me.Lbl_filepath.Name = "Lbl_filepath"
        Me.Lbl_filepath.Size = New System.Drawing.Size(270, 13)
        Me.Lbl_filepath.TabIndex = 3
        Me.Lbl_filepath.Text = "Pfad der ausgewählten Druckerdatei: Keine ausgewählt"
        '
        'Progress_1
        '
        Me.Progress_1.Location = New System.Drawing.Point(12, 393)
        Me.Progress_1.Name = "Progress_1"
        Me.Progress_1.Size = New System.Drawing.Size(467, 18)
        Me.Progress_1.TabIndex = 4
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.DateiToolStripMenuItem, Me.BearbeitenToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(3, 3)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(608, 24)
        Me.MenuStrip1.TabIndex = 5
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'DateiToolStripMenuItem
        '
        Me.DateiToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ToolStripMenuItm_1, Me.BeendenToolStripMenuItem})
        Me.DateiToolStripMenuItem.Name = "DateiToolStripMenuItem"
        Me.DateiToolStripMenuItem.Size = New System.Drawing.Size(46, 20)
        Me.DateiToolStripMenuItem.Text = "Datei"
        '
        'ToolStripMenuItm_1
        '
        Me.ToolStripMenuItm_1.Name = "ToolStripMenuItm_1"
        Me.ToolStripMenuItm_1.Size = New System.Drawing.Size(173, 22)
        Me.ToolStripMenuItm_1.Text = "Druckerdatei laden"
        '
        'BeendenToolStripMenuItem
        '
        Me.BeendenToolStripMenuItem.Name = "BeendenToolStripMenuItem"
        Me.BeendenToolStripMenuItem.Size = New System.Drawing.Size(173, 22)
        Me.BeendenToolStripMenuItem.Text = "Beenden"
        '
        'BearbeitenToolStripMenuItem
        '
        Me.BearbeitenToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ToolStripMenuItm_2})
        Me.BearbeitenToolStripMenuItem.Name = "BearbeitenToolStripMenuItem"
        Me.BearbeitenToolStripMenuItem.Size = New System.Drawing.Size(75, 20)
        Me.BearbeitenToolStripMenuItem.Text = "Bearbeiten"
        '
        'ToolStripMenuItm_2
        '
        Me.ToolStripMenuItm_2.Name = "ToolStripMenuItm_2"
        Me.ToolStripMenuItm_2.Size = New System.Drawing.Size(145, 22)
        Me.ToolStripMenuItm_2.Text = "Einstellungen"
        '
        'Opn_filepath
        '
        Me.Opn_filepath.Filter = "txt Dateien (*.txt)|*.txt|All files (*.*)|*.*"""
        '
        'Lbl_preview
        '
        Me.Lbl_preview.AutoSize = True
        Me.Lbl_preview.Location = New System.Drawing.Point(12, 48)
        Me.Lbl_preview.Name = "Lbl_preview"
        Me.Lbl_preview.Size = New System.Drawing.Size(0, 13)
        Me.Lbl_preview.TabIndex = 7
        '
        'Group_1
        '
        Me.Group_1.BackColor = System.Drawing.Color.Black
        Me.Group_1.ForeColor = System.Drawing.Color.White
        Me.Group_1.Location = New System.Drawing.Point(27, 45)
        Me.Group_1.Name = "Group_1"
        Me.Group_1.Size = New System.Drawing.Size(246, 263)
        Me.Group_1.TabIndex = 10
        Me.Group_1.TabStop = False
        Me.Group_1.Text = "Preview"
        '
        'Group_2
        '
        Me.Group_2.BackColor = System.Drawing.Color.Black
        Me.Group_2.ForeColor = System.Drawing.Color.White
        Me.Group_2.Location = New System.Drawing.Point(350, 45)
        Me.Group_2.Name = "Group_2"
        Me.Group_2.Padding = New System.Windows.Forms.Padding(0)
        Me.Group_2.Size = New System.Drawing.Size(243, 263)
        Me.Group_2.TabIndex = 11
        Me.Group_2.TabStop = False
        Me.Group_2.Text = "Live Printing"
        '
        'Btn_pause
        '
        Me.Btn_pause.Enabled = False
        Me.Btn_pause.ForeColor = System.Drawing.Color.Black
        Me.Btn_pause.Location = New System.Drawing.Point(315, 433)
        Me.Btn_pause.Name = "Btn_pause"
        Me.Btn_pause.Size = New System.Drawing.Size(164, 34)
        Me.Btn_pause.TabIndex = 12
        Me.Btn_pause.Text = "Pause"
        Me.Btn_pause.UseVisualStyleBackColor = True
        '
        'Btn_stop
        '
        Me.Btn_stop.ForeColor = System.Drawing.Color.Black
        Me.Btn_stop.Image = CType(resources.GetObject("Btn_stop.Image"), System.Drawing.Image)
        Me.Btn_stop.Location = New System.Drawing.Point(496, 377)
        Me.Btn_stop.Name = "Btn_stop"
        Me.Btn_stop.Size = New System.Drawing.Size(118, 102)
        Me.Btn_stop.TabIndex = 1
        Me.Btn_stop.UseVisualStyleBackColor = True
        '
        'MainView
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(614, 482)
        Me.Controls.Add(Me.Btn_pause)
        Me.Controls.Add(Me.Group_2)
        Me.Controls.Add(Me.Group_1)
        Me.Controls.Add(Me.Lbl_preview)
        Me.Controls.Add(Me.Progress_1)
        Me.Controls.Add(Me.Lbl_filepath)
        Me.Controls.Add(Me.Lbl_progress)
        Me.Controls.Add(Me.Btn_stop)
        Me.Controls.Add(Me.Btn_start)
        Me.Controls.Add(Me.MenuStrip1)
        Me.ForeColor = System.Drawing.Color.White
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Name = "MainView"
        Me.Padding = New System.Windows.Forms.Padding(3)
        Me.Text = "2D Plotter"
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Btn_start As System.Windows.Forms.Button
    Friend WithEvents Btn_stop As System.Windows.Forms.Button
    Friend WithEvents Lbl_progress As System.Windows.Forms.Label
    Friend WithEvents Lbl_filepath As System.Windows.Forms.Label
    Friend WithEvents Progress_1 As System.Windows.Forms.ProgressBar
    Friend WithEvents MenuStrip1 As System.Windows.Forms.MenuStrip
    Friend WithEvents DateiToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ToolStripMenuItm_1 As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents BeendenToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents BearbeitenToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ToolStripMenuItm_2 As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents Opn_filepath As System.Windows.Forms.OpenFileDialog
    Friend WithEvents Lbl_preview As System.Windows.Forms.Label
    Friend WithEvents Group_1 As System.Windows.Forms.GroupBox
    Friend WithEvents Group_2 As System.Windows.Forms.GroupBox
    Friend WithEvents Btn_pause As System.Windows.Forms.Button

End Class
