Public Class DrawingView
    Private p_start As Point
    Private p_end As Point
    Private mouse As Boolean = False
    Private first_point_selected_line As Boolean = False
    Private first_point_selected_circle As Boolean = False
    Private btn_selected As Integer = -1
    Private con As Controller

    'Bei Betaetigung des Buttons "Btn_cancel" wird diese Funktion aufgerufen; diese fuehrt dazu, durch Funktionsaufruf
    'im Controller die temporaere Datei zu loeschen, sowie die Form "DrawingView" zu schließen
    Private Sub Btn_cancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_cancel.Click
        Me.con.delete_drawing_file()
        Me.Close()
    End Sub

    'Bei Betaetigung des Buttons "Btn_back" wird diese Funktion aufgerufen; diese fuehrt dazu, den Wert der Variable "btn_selected"
    'auf "1" zu setzen, den Button zu deaktivieren, das Zeichenbrett zu leeren, sowie durch Funktionsaufruf "back_drawing" im Controller
    'das bereits gezeichnete, bis auf den letzten Schritt in die Zeichenebene zu laden
    Private Sub Btn_back_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_back.Click
        Me.btn_selected = 1
        Me.Btn_back.Enabled() = False
        Me.Refresh()
        Me.con.back_drawing()
    End Sub

    'Bei Betaetigung des Buttons "Btn_line" wird diese Funktion aufgerufen; diese fuehrt dazu, den Text im Label "Lbl_order"
    'zu setzen, sowie der Variablen "btn_selected" den Wert "2" zuzuweisen 
    Private Sub Btn_line_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_line.Click
        Me.Lbl_order.Text = "Markieren Sie den Startpunkt der Linie auf der Zeichenebene"
        Me.btn_selected = 2

    End Sub

    'Bei Betaetigung des Buttons "Btn_circle" wird diese Funktion aufgerufen; diese fuehrt dazu, den Text im Label "Lbl_order"
    'zu setzen, sowie der Variablen "btn_selected" den Wert 3 zuzuweisen
    Private Sub Btn_circle_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_circle.Click
        Me.Lbl_order.Text = "Markieren Sie den Startpunkt des Kreises auf der Zeichenebene"
        Me.btn_selected = 3
    End Sub


    'Diese Funktion ist fuer das Zeichnen von Linien zustaendig; dazu wird die Funktion "DrawLine" verwendet
    Public Sub draw_line(ByVal p_start As Point, ByVal p_end As Point)
        Me.Group_1.CreateGraphics.DrawLine(Pens.White, p_start.X, p_start.Y, p_end.X, p_end.Y)
    End Sub

    'Wird in die Zeichenebene geklickt, so wird diese Funktion aufgerufen; diese ermittelt zunaechst anhand der Variablen 
    '"btn_selected", ob eine Line/Kreis gezeichnet werden soll bzw. der vorherige Zeichenvorgang rueckgaengig gemacht werden soll;
    'ist dies geschehen, so wird ueberprueft, ob ein Klick mit dieser Auswahl (Kreis /Linie) vorher schon erfolgt ist
    'Ist dies nicht der Fall, so wird der Text des Labels "Lbl_order" gesetzt, und der Startpunkt an der Stelle des Mausklicks
    'gesetzt;im anderen Fall wird der Kreis/Linie in die Zeichenebene gezeichnet
    Private Sub Group_1_MouseClick(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles Group_1.MouseClick
        If (Me.btn_selected = 2) Then ' Line Button wurde zuvor aktiviert
            If (Me.first_point_selected_line) Then
                Me.Lbl_order.Text = "Klicken Sie zum Zeichnen auf die Linie bzw. den Viertelkreis"
                Me.draw_line(p_start, New Point(e.X, e.Y))
                Me.con.save_drawing_steps(p_start, New Point(e.X, e.Y))
                Me.Btn_back_Enabled()
                p_end.X = e.X
                p_end.Y = e.Y
                Me.first_point_selected_line = False
            Else
                Me.Lbl_order.Text = "Markieren Sie nun den Endpunkt der Linie auf der Zeichenebene"
                Me.first_point_selected_line = True
                Me.first_point_selected_circle = False
                p_start = New Point(e.X, e.Y)

            End If


        ElseIf (Me.btn_selected = 3) Then 'Circle Button wurde zuvor aktiviert 
            If (Me.first_point_selected_circle) Then
                Dim swapAngle As Integer = Me.show_MsgBox_for_swapAngle()
                Me.Lbl_order.Text = "Klicken Sie zum Zeichnen auf die Linie bzw. den Viertelkreis"
                Me.Btn_back_Enabled()
                Me.con.draw_circle_drawingView(New Point(e.X, e.Y), p_start, swapAngle)
                Me.first_point_selected_circle = False
            Else
                Me.Lbl_order.Text = "Markieren Sie nun den Mittelpunkt auf der Zeichenebene"
                Me.first_point_selected_circle = True
                Me.first_point_selected_line = False
                p_start = New Point(e.X, e.Y)

            End If
        End If
    End Sub

    'Zur Orientierung auf der Zeichenebene wird diese Funktion verwendet; diese dient dazu die Koordinaten des Mauszeigers,
    'getrennt nach X + Y Koordinaten, in den Labeln "Label1" + "Label2" anzuzeigen
    Private Sub Group_1_MouseMove(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles Group_1.MouseMove
       
        Label1.Text = "X - Achse: " + e.X.ToString
        Label2.Text = "Y - Achse: " + (260 - e.Y).ToString
    End Sub

    'Beim Laden der Form "Zeichnung" wird diese Funktion aufgerufen; diese initialisiert die Variable con, uebergibt sich selbst dieser 
    'Variablen und veranlasst die temporaere Datei im Speicher zu loeschen
    Private Sub Zeichnung_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.con = Controller.getInstance
        Me.con.set_DrawingView(Me)
        Me.con.delete_drawing_file()
    End Sub

    
    'Bei Betaetigung des Buttons "Btn_save" wird diese Funktion aufgerufen; diese dient dazu die temporaere Datei in einem
    'vom Benutzer gewuenschten Verzeichnis unter dem gewuenschten Namen abzuspeichern; hierzu wird ein Dialog angezeigt, in dem 
    'diese Taetigkeiten erledigt werden koennen; ist dies geschehen, so wird der neue Pfad zu dieser Datei im Controller 
    'neu gesetzt, die Preview in der "MainView" aktualisiert und die Form "Zeichnung" geschlossen
    Private Sub Btn_save_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Btn_save.Click
        Dim filepath As String
        If (SaveFileDialog.ShowDialog() = System.Windows.Forms.DialogResult.OK) Then
            filepath = SaveFileDialog.FileName
            Me.con.save_drawing_to_file(filepath)
            Me.con.refreshPreview()
            Me.con.showPreview(filepath)
            Me.Hide()
        End If

    End Sub

    'Durch Betaetigung des Buttons "Btn_back" wird diese Funktion aufgerufen; diese dient dazu, den Button "Btn_back" zu
    'aktivieren/deaktivieren
    Public Sub Btn_back_Enabled()
        If Not (Me.Btn_back.Enabled) Then
            Me.Btn_back.Enabled = Not (Me.Btn_back.Enabled)
        End If

    End Sub

    'Bei Aufruf dieser Funktion wird ein Kreis mittels der uebergebenen Parameter gezeichnet
    Public Sub draw_circle(ByVal rect As Rectangle, ByVal startAngle As Single, ByVal swapAngle As Single)
        Me.Group_1.CreateGraphics.DrawArc(Pens.White, rect, -1 * startAngle, swapAngle)
    End Sub

    'Fuer das Zeichnen eines Kreises wird neben dem Start- und Mittelpunkt auch der Winkel des Kreis benoetigt; dazu wird in dieser
    'Funktion eine MessageBox angezeigt, in dem der Winkel eingegeben wird; nach der Eingabe erfolgt eine Ueberpruefung, ob diese auch eine
    'Zahl ist; falls nicht wird eine entsprechende Meldung ausgegeben und der Benutzer hat erneut die Chance die Eingabe zu wiederholen;
    'bei richtiger Eingabe wird der Winkel als Integer-Wert zurueckgegeben
    Private Function show_MsgBox_for_swapAngle() As Integer
        Dim angle_string As String
        Dim angle As Integer
        angle_string = InputBox(Prompt:="Bitte Kreiswinkel eingeben!", Title:="Abfrage Kreiswinkel")

        If Not IsNumeric(angle_string) Then
            MsgBox("Fehler bei der Eingabe! Versuchen Sie es erneut")
            Me.show_MsgBox_for_swapAngle()
        Else
            angle = Val(angle_string)
            angle = angle
        End If
        Return angle
    End Function

    'Bei Betaetigung des Buttons "Btn_import" wird diese Funktion aufgerufen; diese dient dazu, die in der Form "Zeichnung"
    'erstellte Zeichnung in die MainView zuladen("refreshPreview" + "showPreview"), sowie den Druckvorgang zu starten ("start_printing");
    'der Abschluss bildet das Schließen der Form "Zeichnung" ("Hide")
    Private Sub Btn_import_Click(sender As Object, e As EventArgs) Handles Btn_import.Click
        Me.con.refreshPreview()
        Me.con.set_path_mainView()
        Dim path As String
        path = Me.con.getPath()
        Me.Hide()
        Me.con.showPreview(path)
        'Me.con.switch_Buttons_MainView()
        ' Me.con.start_printing_from_drawingView()

    End Sub


End Class