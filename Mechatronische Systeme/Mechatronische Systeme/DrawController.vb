'Kann man darüber streiten, ob zusätzlicher Controller erforderlich

Public Class DrawController
    Private x_preview As Integer
    Private y_preview As Integer


    Public Sub New()

    End Sub



    Public Sub draw(x As Integer, y As Integer)
        x_preview += x
        y_preview += y
    End Sub
End Class
