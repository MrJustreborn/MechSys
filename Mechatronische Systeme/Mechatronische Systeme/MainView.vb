Public Class MainView
    Private filepath As String
    Private con As Controller
    Private moCon As MotorController
    Private plotterPause As Boolean = True

    'Bei Aufruf dieser Funktion wird zunaechst ein Dialogfenster angezeigt, bei dem der Benutzer die Druckerdatei auswaehlen 
    'kann; ist dies geschehen, so wird im Controller die "showPreview" Funktion aufgerufen, die dazu führt,
    'dass in der Preview des Hauptfensters eine Druckvorschau angezeigt wird
    Private Sub DruckerdateiLadenToolStripMenuItem_Click(sender As System.Object, e As System.EventArgs) Handles ToolStripMenuItm_1.Click
        If (Opn_filepath.ShowDialog() = System.Windows.Forms.DialogResult.OK) Then
            Me.Refresh()
            filepath = Opn_filepath.FileName
            Lbl_filepath.Text = "Pfad der ausgewählten Druckerdatei: " + filepath
            Me.con.showPreview(filepath)
        End If
    End Sub

    'Durch Betaetigung des Buttons "Btn_start" wird diese Funktion aufgerufen;
    'Diese ruft die Funktion "start_plotter" auf und startet somit den Drucker
    Private Sub Btn_start_Click(sender As System.Object, e As System.EventArgs) Handles Btn_start.Click
        Me.start_plotter()
    End Sub

    'Diese Funktion startet den Druckvorgang des Druckers; dazu wird zunaechst ueberprueft, ob eine 
    ' Druckdatei bereits ausgewaehlt worden ist; ist dies der Fall so wird der Druckvorgang gestartet,
    ' sowie die entsprechenden Buttons aktiviert/deaktiviert; ist keine Druckdatei vorher ausgewaehlt worden
    ' so wird eine entsprechende Meldung ausgegeben
    Public Sub start_plotter()
        If Not (filepath Is Nothing) Then

            disable_ToolStripItm()
            switch_disable_buttons()
            ' Me.con.start_plotter()

        Else
            MsgBox("Wählen Sie bitte zuerst eine Datei aus, bevor Sie das Drucken anfangen wollen!")

        End If
    End Sub

    'Bei Betaetigung des Buttons in der Menueleiste wird die Form "Settings" geladen und angezeigt
    Private Sub EinstellungenToolStripMenuItem_Click(sender As System.Object, e As System.EventArgs) Handles ToolStripMenuItm_2.Click
        Settings.Show()
    End Sub

    'Diese Funnktion ist zustaendig, um die Button "Btn_pause", sowie "Btn_start" abwechselnd zu aktivieren/deaktivieren
    Private Sub switch_disable_buttons()
        Me.Btn_pause.Enabled = Not (Me.Btn_pause.Enabled)
        Me.Btn_start.Enabled = Not (Me.Btn_start.Enabled)
    End Sub

    'Diese Funktion deaktiviert die beiden Buttons "ToolStripMenuItem_1", sowie "ToolStripMenuItem_2"
    Private Sub disable_ToolStripItm()
        Me.ToolStripMenuItm_1.Enabled = False
        Me.ToolStripMenuItm_2.Enabled = False
    End Sub

    'Diese Funktion aktiviert die beiden Buttons "ToolStripMenuItem_1", sowie "ToolStripMenuItem_2"
    Private Sub enable_ToolStripItm()
        Me.ToolStripMenuItm_1.Enabled = True
        Me.ToolStripMenuItm_2.Enabled = True
    End Sub
   
    'Diese Funktion dient dazu, Linien/Graphiken in der "Preview" zu zeichnen
    Public Sub draw_preview(ByVal p_old As Point, ByVal p_new As Point)

        Me.Group_1.CreateGraphics.DrawLine(Pens.White, p_old.X, p_old.Y, p_new.X, p_new.Y)
    End Sub

    'Diese Funktion dient dazu, Linien/Graphiken im "Live Printing" zu zeichnen
    Public Sub draw_live_print(ByVal p_old As Point, ByVal p_new As Point)
        Me.Group_2.CreateGraphics.DrawLine(Pens.White, p_old.X, p_old.Y, p_new.X, p_new.Y)
    End Sub

    'Bei Betaetigung des Buttons "Btn_pause" wird der Druckvorgang pausiert, sowie entsprechende Buttons
    'fuer ein Fortfahren des Vorgang aktiviert und entsprechend beschriftet
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

    'Der Fortschritt des Druckvorgangs wird durch diese Funktion gesteuert - die Progressbar "Progressbar"
    'kann hier je nach Fortschritt des Druckvorgangs auf einen bestimmten Wert eingestellt werden
    'zusaetzlich wird der Wert im Label "lbl_progress" angezeigt 
    Public Sub Progress(ByVal value As Integer)
        If (Progress_1.Value < 101) Then
            Me.Progress_1.Value += value
            Me.Lbl_progress.Text = "Fortschritt: " + Me.Progress_1.Value.ToString + "%"
        End If

    End Sub

    'Beim Laden der Form "MainView" wird die Controller Instanz der Variablen "con" zugewiesen, sowie dem Controller
    'die MainView mitgeteilt -gesetzt
    Private Sub MainView_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.con = Controller.getInstance
        Me.con.set_MainView(Me)
    End Sub

    'Bei Aufruf dieser Funktion wird die Form "DrawingView" geladen und angezeigt
    Private Sub KonstuierenToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles KonstuierenToolStripMenuItem.Click
        DrawingView.Show()
    End Sub

    'Diese Funktion setzt die Daten fuer den MotorController 
    Private Sub set_plotter_data(datas As List(Of Integer()))
        moCon.setDatas(datas)
    End Sub

    'Diese Funktion setzt den Pfad der Druckdatei
    Public Sub setFilepath(ByVal filepath As String)
        Me.filepath = filepath
    End Sub
   
    'Bei Klick auf dem Button "Btn_stop" wird diese Methode aufgerufen 
    'hierbei wird im Controller die Methode "stop_plotter" aufgerufen und somit der Druckvorgang 
    ' sofort beendet
    Private Sub Btn_stop_Click(sender As Object, e As EventArgs) Handles Btn_stop.Click
        Me.con.stop_plotter()
    End Sub
End Class
