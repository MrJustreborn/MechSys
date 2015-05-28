

Public Class Intro
    Dim timeLeft As Integer

    ' Ist der Timer "Timer1" gestartet, so wird jede Sekunde der Wert der Variablen "timeLeft" dekrementiert
    ' sowie deren Wert im Label "Label2" angezeigt; ist dieser "0", so wird der Timer angehalten, die Form 
    ' "MainView" geladen, sowie die Form "intro" geschlossen
    Private Sub Timer1_Tick(sender As System.Object, e As System.EventArgs) Handles Timer1.Tick
        If (timeLeft = 0) Then
            Timer1.Stop()
            MainView.Show()
            Me.Hide()

        End If
        timeLeft -= 1
        'Just for fun ;-)
        Me.Label2.Text = "Druckersoftware startet in: " + timeLeft.ToString + " s"
    End Sub

    ' Beim Laden der Form "intro" wird der Timer "Timer1" gestartet, sowie die Integer Variable "timeLeft"
    ' gesetzt
    Private Sub intro_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        Timer1.Start()
        timeLeft = 5
       

    End Sub

   
End Class