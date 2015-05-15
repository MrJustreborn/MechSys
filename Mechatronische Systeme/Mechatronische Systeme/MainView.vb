Public Class MainView
    Private filepath As String
    Private con As Controller
    Private moCon As MotorController
    Private plotterPause As Boolean = True


    Private Sub DruckerdateiLadenToolStripMenuItem_Click(sender As System.Object, e As System.EventArgs) Handles ToolStripMenuItm_1.Click
        If (Opn_filepath.ShowDialog() = System.Windows.Forms.DialogResult.OK) Then
            Me.Refresh()
            filepath = Opn_filepath.FileName
            Lbl_filepath.Text = "Pfad der ausgewählten Druckerdatei: " + filepath
            Me.con.showPreview(filepath)
        End If
    End Sub

    Private Sub Btn_start_Click(sender As System.Object, e As System.EventArgs) Handles Btn_start.Click
        Me.start_plotter()
    End Sub

    Public Sub start_plotter()
        If Not (filepath Is Nothing) Then

            disable_ToolStripItm()
            switch_disable_buttons()
            ' Me.con.start_plotter()

        Else
            MsgBox("Wählen Sie bitte zuerst eine Datei aus, bevor Sie das Drucken anfangen wollen!")

        End If
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


    Public Sub draw_preview(ByVal p_old As Point, ByVal p_new As Point)

        Me.Group_1.CreateGraphics.DrawLine(Pens.White, p_old.X, p_old.Y, p_new.X, p_new.Y)
    End Sub

    Public Sub draw_live_print(ByVal p_old As Point, ByVal p_new As Point)
        Me.Group_2.CreateGraphics.DrawLine(Pens.White, p_old.X, p_old.Y, p_new.X, p_new.Y)
    End Sub

    Private Sub Btn_pause_Click(sender As System.Object, e As System.EventArgs) Handles Btn_pause.Click
        If (Me.plotterPause) Then
            '  Me.con.unpause_plotter()
            Me.Btn_pause.Text = "Fortfahren"
        Else
            ' Me.con.pause_plotter()
            Me.Btn_pause.Text = "Pause"
        End If
        Me.plotterPause = Not Me.plotterPause
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

    Private Sub KonstuierenToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles KonstuierenToolStripMenuItem.Click
        DrawingView.Show()
    End Sub



    Private Sub Group_1_Enter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Group_1.Enter

    End Sub

    'Schnittstelle für Motorcontroller
    Private Sub set_plotter_data(datas As List(Of Integer()))
        moCon.setDatas(datas)
    End Sub
   
    Public Sub setFilepath(ByVal filepath As String)
        Me.filepath = filepath
    End Sub
   

    Private Sub Btn_stop_Click(sender As Object, e As EventArgs) Handles Btn_stop.Click
        Me.con.stop_plotter()
    End Sub
End Class
