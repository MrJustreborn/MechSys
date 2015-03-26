Public Class MainView
    Private filepath As String
    Private con As Controller


    Private Sub DruckerdateiLadenToolStripMenuItem_Click(sender As System.Object, e As System.EventArgs) Handles ToolStripMenuItm_1.Click
        If (Opn_filepath.ShowDialog() = System.Windows.Forms.DialogResult.OK) Then
            filepath = Opn_filepath.FileName
            Lbl_filepath.Text = "Pfad der ausgewählten Druckerdatei: " + filepath
        End If
    End Sub

    Private Sub Btn_start_Click(sender As System.Object, e As System.EventArgs) Handles Btn_start.Click
        If Not (filepath Is Nothing) Then

            'Me.con.parse(filepath)
            disable_ToolStripItm()
            switch_disable_buttons()

        Else
            MsgBox("Wählen Sie bitte zuerst eine Datei aus, bevor Sie das Drucken anfangen wollen!")

        End If
        ' Nur zu Testzwecken 
        ' Me.con.progress(10)
        Dim test As Boolean = False
        Dim x As Integer
        x = test
        Console.Write(x)

    End Sub

   
    Private Sub EinstellungenToolStripMenuItem_Click(sender As System.Object, e As System.EventArgs) Handles ToolStripMenuItm_2.Click
        Settings.Show()
    End Sub

    Private Sub switch_disable_buttons()
        Me.Btn_pause.Enabled = Not (Me.Btn_pause.Enabled)
        Me.Btn_start.Enabled = Not (Me.Btn_start.Enabled)
    End Sub

    Private Sub disable_ToolStripItm()
        Me.ToolStripMenuItm_1.Enabled = False
        Me.ToolStripMenuItm_2.Enabled = False
    End Sub

    Private Sub enable_ToolStripItm()
        Me.ToolStripMenuItm_1.Enabled = True
        Me.ToolStripMenuItm_2.Enabled = True
    End Sub


    Public Sub draw_preview(ByVal x_old As Integer, ByVal y_old As Integer, ByVal x_new As Integer, ByVal y_new As Integer)
        Me.Group_1.CreateGraphics.DrawLine(Pens.White, x_old, y_old, x_new, y_new)
    End Sub

    Public Sub draw_live_print(ByVal x_old As Integer, ByVal y_old As Integer, ByVal x_new As Integer, ByVal y_new As Integer)
        Me.Group_2.CreateGraphics.DrawLine(Pens.White, x_old, y_old, x_new, y_new)
    End Sub

    Private Sub Btn_pause_Click(sender As System.Object, e As System.EventArgs) Handles Btn_pause.Click
        switch_disable_buttons()
    End Sub

    Private Sub Group_1_Enter(sender As System.Object, e As System.EventArgs) Handles Group_1.Enter

    End Sub

    Public Sub Progress(ByVal value As Integer)
        If (Progress_1.Value < 101) Then
            Me.Progress_1.Value += value
            Me.Lbl_progress.Text = "Fortschritt: " + Me.Progress_1.Value.ToString + "%"
        End If

    End Sub

    Private Sub MainView_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.con = Controller.getInstance
        Me.con.set_MainView(Me)
    End Sub
End Class
