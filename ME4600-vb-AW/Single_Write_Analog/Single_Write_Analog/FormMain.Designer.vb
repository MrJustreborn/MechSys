<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class frmMain
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
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

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(frmMain))
        Me.btnAbout = New System.Windows.Forms.Button()
        Me.groupBox1 = New System.Windows.Forms.GroupBox()
        Me.CheckBox1 = New System.Windows.Forms.CheckBox()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.trackbarVal = New System.Windows.Forms.TrackBar()
        Me.txtBoxPhysValue = New System.Windows.Forms.TextBox()
        Me.label6 = New System.Windows.Forms.Label()
        Me.coBoxRange = New System.Windows.Forms.ComboBox()
        Me.label5 = New System.Windows.Forms.Label()
        Me.coBoxChannel = New System.Windows.Forms.ComboBox()
        Me.label4 = New System.Windows.Forms.Label()
        Me.btnSingleWrite = New System.Windows.Forms.Button()
        Me.coBoxSubDevs = New System.Windows.Forms.ComboBox()
        Me.label2 = New System.Windows.Forms.Label()
        Me.btnResetSubdev = New System.Windows.Forms.Button()
        Me.btnClearHwInfo = New System.Windows.Forms.Button()
        Me.label3 = New System.Windows.Forms.Label()
        Me.textBoxInfo = New System.Windows.Forms.TextBox()
        Me.btnClose = New System.Windows.Forms.Button()
        Me.TrackBar_WaitTime = New System.Windows.Forms.TrackBar()
        Me.groupBox1.SuspendLayout()
        CType(Me.trackbarVal, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.TrackBar_WaitTime, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'btnAbout
        '
        Me.btnAbout.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.btnAbout.Location = New System.Drawing.Point(123, 386)
        Me.btnAbout.Name = "btnAbout"
        Me.btnAbout.Size = New System.Drawing.Size(105, 23)
        Me.btnAbout.TabIndex = 20
        Me.btnAbout.Text = "Info"
        Me.btnAbout.UseVisualStyleBackColor = True
        '
        'groupBox1
        '
        Me.groupBox1.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.groupBox1.Controls.Add(Me.TrackBar_WaitTime)
        Me.groupBox1.Controls.Add(Me.CheckBox1)
        Me.groupBox1.Controls.Add(Me.Button1)
        Me.groupBox1.Controls.Add(Me.trackbarVal)
        Me.groupBox1.Controls.Add(Me.txtBoxPhysValue)
        Me.groupBox1.Controls.Add(Me.label6)
        Me.groupBox1.Controls.Add(Me.coBoxRange)
        Me.groupBox1.Controls.Add(Me.label5)
        Me.groupBox1.Controls.Add(Me.coBoxChannel)
        Me.groupBox1.Controls.Add(Me.label4)
        Me.groupBox1.Controls.Add(Me.btnSingleWrite)
        Me.groupBox1.Controls.Add(Me.coBoxSubDevs)
        Me.groupBox1.Controls.Add(Me.label2)
        Me.groupBox1.Controls.Add(Me.btnResetSubdev)
        Me.groupBox1.Location = New System.Drawing.Point(12, 12)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Size = New System.Drawing.Size(625, 134)
        Me.groupBox1.TabIndex = 23
        Me.groupBox1.TabStop = False
        Me.groupBox1.Text = " AO Subdevices "
        '
        'CheckBox1
        '
        Me.CheckBox1.AutoSize = True
        Me.CheckBox1.Location = New System.Drawing.Point(445, 111)
        Me.CheckBox1.Name = "CheckBox1"
        Me.CheckBox1.Size = New System.Drawing.Size(80, 17)
        Me.CheckBox1.TabIndex = 15
        Me.CheckBox1.Text = "2Threads? "
        Me.CheckBox1.UseVisualStyleBackColor = True
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(532, 109)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(75, 23)
        Me.Button1.TabIndex = 14
        Me.Button1.Text = "Start Test"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'trackbarVal
        '
        Me.trackbarVal.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.trackbarVal.Location = New System.Drawing.Point(228, 80)
        Me.trackbarVal.Maximum = 65535
        Me.trackbarVal.Name = "trackbarVal"
        Me.trackbarVal.Size = New System.Drawing.Size(280, 45)
        Me.trackbarVal.TabIndex = 13
        Me.trackbarVal.TickFrequency = 3276
        '
        'txtBoxPhysValue
        '
        Me.txtBoxPhysValue.Location = New System.Drawing.Point(101, 83)
        Me.txtBoxPhysValue.Name = "txtBoxPhysValue"
        Me.txtBoxPhysValue.Size = New System.Drawing.Size(100, 20)
        Me.txtBoxPhysValue.TabIndex = 12
        '
        'label6
        '
        Me.label6.AutoSize = True
        Me.label6.Location = New System.Drawing.Point(13, 86)
        Me.label6.Name = "label6"
        Me.label6.Size = New System.Drawing.Size(78, 13)
        Me.label6.TabIndex = 11
        Me.label6.Text = "Physical value:"
        '
        'coBoxRange
        '
        Me.coBoxRange.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.coBoxRange.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.coBoxRange.FormattingEnabled = True
        Me.coBoxRange.Location = New System.Drawing.Point(277, 51)
        Me.coBoxRange.Name = "coBoxRange"
        Me.coBoxRange.Size = New System.Drawing.Size(231, 21)
        Me.coBoxRange.TabIndex = 10
        '
        'label5
        '
        Me.label5.AutoSize = True
        Me.label5.Location = New System.Drawing.Point(225, 54)
        Me.label5.Name = "label5"
        Me.label5.Size = New System.Drawing.Size(42, 13)
        Me.label5.TabIndex = 9
        Me.label5.Text = "Range:"
        '
        'coBoxChannel
        '
        Me.coBoxChannel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.coBoxChannel.FormattingEnabled = True
        Me.coBoxChannel.Location = New System.Drawing.Point(101, 51)
        Me.coBoxChannel.Name = "coBoxChannel"
        Me.coBoxChannel.Size = New System.Drawing.Size(100, 21)
        Me.coBoxChannel.TabIndex = 8
        '
        'label4
        '
        Me.label4.AutoSize = True
        Me.label4.Location = New System.Drawing.Point(13, 54)
        Me.label4.Name = "label4"
        Me.label4.Size = New System.Drawing.Size(49, 13)
        Me.label4.TabIndex = 7
        Me.label4.Text = "Channel:"
        '
        'btnSingleWrite
        '
        Me.btnSingleWrite.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnSingleWrite.Enabled = False
        Me.btnSingleWrite.Location = New System.Drawing.Point(514, 80)
        Me.btnSingleWrite.Name = "btnSingleWrite"
        Me.btnSingleWrite.Size = New System.Drawing.Size(105, 23)
        Me.btnSingleWrite.TabIndex = 6
        Me.btnSingleWrite.Text = "Write Data"
        Me.btnSingleWrite.UseVisualStyleBackColor = True
        '
        'coBoxSubDevs
        '
        Me.coBoxSubDevs.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.coBoxSubDevs.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.coBoxSubDevs.FormattingEnabled = True
        Me.coBoxSubDevs.Location = New System.Drawing.Point(101, 21)
        Me.coBoxSubDevs.Name = "coBoxSubDevs"
        Me.coBoxSubDevs.Size = New System.Drawing.Size(407, 21)
        Me.coBoxSubDevs.TabIndex = 5
        '
        'label2
        '
        Me.label2.AutoSize = True
        Me.label2.Location = New System.Drawing.Point(13, 24)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(61, 13)
        Me.label2.TabIndex = 4
        Me.label2.Text = "Subdevice:"
        '
        'btnResetSubdev
        '
        Me.btnResetSubdev.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnResetSubdev.Enabled = False
        Me.btnResetSubdev.Location = New System.Drawing.Point(514, 19)
        Me.btnResetSubdev.Name = "btnResetSubdev"
        Me.btnResetSubdev.Size = New System.Drawing.Size(105, 23)
        Me.btnResetSubdev.TabIndex = 3
        Me.btnResetSubdev.Text = "Reset Subdevice"
        Me.btnResetSubdev.UseVisualStyleBackColor = True
        '
        'btnClearHwInfo
        '
        Me.btnClearHwInfo.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.btnClearHwInfo.Location = New System.Drawing.Point(12, 386)
        Me.btnClearHwInfo.Name = "btnClearHwInfo"
        Me.btnClearHwInfo.Size = New System.Drawing.Size(105, 23)
        Me.btnClearHwInfo.TabIndex = 27
        Me.btnClearHwInfo.Text = "Clear Output"
        Me.btnClearHwInfo.UseVisualStyleBackColor = True
        '
        'label3
        '
        Me.label3.AutoSize = True
        Me.label3.Location = New System.Drawing.Point(12, 149)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(151, 13)
        Me.label3.TabIndex = 26
        Me.label3.Text = "Hardware info and data output"
        '
        'textBoxInfo
        '
        Me.textBoxInfo.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.textBoxInfo.Location = New System.Drawing.Point(12, 165)
        Me.textBoxInfo.Multiline = True
        Me.textBoxInfo.Name = "textBoxInfo"
        Me.textBoxInfo.ScrollBars = System.Windows.Forms.ScrollBars.Both
        Me.textBoxInfo.Size = New System.Drawing.Size(628, 211)
        Me.textBoxInfo.TabIndex = 25
        Me.textBoxInfo.WordWrap = False
        '
        'btnClose
        '
        Me.btnClose.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.btnClose.Location = New System.Drawing.Point(535, 386)
        Me.btnClose.Name = "btnClose"
        Me.btnClose.Size = New System.Drawing.Size(105, 23)
        Me.btnClose.TabIndex = 24
        Me.btnClose.Text = "Close"
        Me.btnClose.UseVisualStyleBackColor = True
        '
        'TrackBar_WaitTime
        '
        Me.TrackBar_WaitTime.Location = New System.Drawing.Point(228, 109)
        Me.TrackBar_WaitTime.Maximum = 1000
        Me.TrackBar_WaitTime.Name = "TrackBar_WaitTime"
        Me.TrackBar_WaitTime.Size = New System.Drawing.Size(211, 45)
        Me.TrackBar_WaitTime.TabIndex = 16
        '
        'frmMain
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(652, 416)
        Me.Controls.Add(Me.btnClearHwInfo)
        Me.Controls.Add(Me.label3)
        Me.Controls.Add(Me.textBoxInfo)
        Me.Controls.Add(Me.btnClose)
        Me.Controls.Add(Me.groupBox1)
        Me.Controls.Add(Me.btnAbout)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MinimumSize = New System.Drawing.Size(600, 350)
        Me.Name = "frmMain"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "ME-iDS - Single Write Analog"
        Me.groupBox1.ResumeLayout(False)
        Me.groupBox1.PerformLayout()
        CType(Me.trackbarVal, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.TrackBar_WaitTime, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents btnAbout As System.Windows.Forms.Button
    Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
    Private WithEvents trackbarVal As System.Windows.Forms.TrackBar
    Private WithEvents txtBoxPhysValue As System.Windows.Forms.TextBox
    Private WithEvents label6 As System.Windows.Forms.Label
    Private WithEvents coBoxRange As System.Windows.Forms.ComboBox
    Private WithEvents label5 As System.Windows.Forms.Label
    Private WithEvents coBoxChannel As System.Windows.Forms.ComboBox
    Private WithEvents label4 As System.Windows.Forms.Label
    Private WithEvents btnSingleWrite As System.Windows.Forms.Button
    Private WithEvents coBoxSubDevs As System.Windows.Forms.ComboBox
    Private WithEvents label2 As System.Windows.Forms.Label
    Private WithEvents btnResetSubdev As System.Windows.Forms.Button
    Private WithEvents btnClearHwInfo As System.Windows.Forms.Button
    Private WithEvents label3 As System.Windows.Forms.Label
    Private WithEvents textBoxInfo As System.Windows.Forms.TextBox
    Private WithEvents btnClose As System.Windows.Forms.Button
    Friend WithEvents CheckBox1 As System.Windows.Forms.CheckBox
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents TrackBar_WaitTime As System.Windows.Forms.TrackBar

End Class
