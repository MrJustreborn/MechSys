Public Class Settings
    Private con As Controller

    'Diese Funktion schließt bei Betaetigung des Buttons "Btn_cancel" die Form "Settings" ohne die getaetigten Aenderungen abzuspeichern
    Private Sub Btn_cancel_Click(sender As System.Object, e As System.EventArgs) Handles Btn_cancel.Click
        Me.Close()
    End Sub

    ' Diese Funktion ruft bei Betaetigung des Buttons "Btn_save" zunaechst die Funktion "save" auf um die
    ' getaetigten Aenderungen zunaechst zu speichern und schließt zum Abschluss die Form "Settings"
    Private Sub Btn_save_Click(sender As System.Object, e As System.EventArgs) Handles Btn_save.Click
        save()
        Me.Close()


    End Sub

    ' Beim Aufruf/Laden der Form "Settings" wird zunaechst die Instanz "con" vom Typ Controller zugewiesen 
    ' (Singleton Pattern), im Anschluss werden die Einstellungen durch Aufruf der Funktion "load_settings"
    ' geladen - es werden die gepeicherten Einstellungen in die Form geladen 
    Private Sub Settings_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        con = Controller.getInstance
        con.load_settings(Me)
    End Sub

    ' Diese Funktion setzt den Label "Lbl_4" mit dem Wert des uebergebenen Strings, sowie die Scrollbar
    ' "Scroll_1"; bei Letzteren ist dafuer noch eine vorherige Konvertierung in einen Integer-Wert erforderlich
    Public Sub setScrollBar(txt As String)
        Me.Lbl_4.Text = "Wert: " + txt
        Me.Scroll_1.Value = CInt(txt)
    End Sub

    ' Die Funktion "save_settings" wird im "Controller" aufgerufen, die dazu fuehrt die getaetigte
    ' Aenderung in einer Datei abzuspeichern
    Private Sub save()
        con.save_settings(Me.Scroll_1.Value)
    End Sub

    'Wird der Schieberegler der Scrollbar "Scroll_1" verschoben, so wird diese Funktion aufgerufen
    'Diese dient dazu den Wert der Scrollbar im Label "Lbl_4" noch einmal visuell darzustellen
    Private Sub Scroll_1_Scroll(sender As System.Object, e As System.Windows.Forms.ScrollEventArgs) Handles Scroll_1.Scroll
        Me.Lbl_4.Text = "Wert: " + Me.Scroll_1.Value.ToString
    End Sub

End Class