Public Class Calculator
    Private Shared instance As Calculator
    Private datas As List(Of Integer())
    Private cur_x As Integer
    Private cur_y As Integer

   

    Private Sub New()
        datas = New List(Of Integer())

    End Sub

    Public Shared ReadOnly Property getInstance() As Calculator
        Get
            If IsNothing(instance) Then
                instance = New Calculator()
            End If
            Return instance
        End Get
    End Property

    Public Sub addPA(ByVal x As Integer, ByVal y As Integer, ByVal status As Boolean)
        Dim arr(3) As Integer
        arr(0) = status
        arr(1) = x - cur_x
        arr(2) = y - cur_y
        datas.Add(arr)
        cur_x = x
        cur_y = y
    End Sub

    Public Sub addCS(ByVal x As Integer, ByVal y As Integer, ByVal phi As Integer, ByVal status As Boolean)
        'schleife teilstücke ausrechnen und addPA aufrufen
	radius As Integer

	new_x As Integer 'new_x und new_y sind die neuen endpunkte jeweils
	new_y As Integer
	tune As Integer 'tuningwert für die feinere Auflösung des Kreises -> GUI
	tune = 0
	
	radius = Math.Sqrt((Math.Abs(x - cur_x)) ^ 2 + (Math.Abs(y - cur_y)) ^ 2)

	beta As Single
	beta = (phi / phi) / tune
	Do
		new_x = (Math.Sin(beta) * radius) + x
		new_y = (Math.Cos(beta) * radius) + y
		Me.addPA(new_x,new_y,status)
		beta += beta
	loop until beta >= phi
    End Sub

    Public Function getDatas() As List(Of Integer())
        Return Me.datas
    End Function

End Class
