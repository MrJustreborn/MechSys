

Public Class Intro
    Dim timeLeft As Integer


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

    Private Sub intro_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        Timer1.Start()
        timeLeft = 5

    End Sub
End Class