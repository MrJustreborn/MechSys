Public Class Calculator
    Private Shared instance As Calculator
    Private datas As List(Of Integer())
    Private cur_x As Integer
    Private cur_y As Integer
    Private radius_circle As Integer 'Radius für den gezeichneten Kreis in der Drawing View 

   

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
        Dim arr(2) As Integer
        arr(0) = status
        arr(1) = x - cur_x
        arr(2) = y - cur_y
        datas.Add(arr)
        cur_x = x
        cur_y = y

    End Sub

    Public Sub addCS(ByVal x As Integer, ByVal y As Integer, ByVal phi As Integer, ByVal status As Boolean)

        'schleife teilstücke ausrechnen und addPA aufrufen
        Dim radius As Integer
        Dim beta As Double
        Dim phi2 As Double
        Dim new_x As Integer 'new_x und new_y sind die neuen endpunkte jeweils
        Dim new_y As Integer
        Dim tune As Integer 'tuningwert für die feinere Auflösung des Kreises -> GUI
        tune = 1
        phi2 = phi / 10

        radius = Math.Sqrt(Math.Pow(Math.Abs(x - cur_x), 2) + Math.Pow(Math.Abs(y - cur_y), 2))

	Dim offset As Single
        offset = Math.Atan((cur_y - y) / (cur_x - x))

        beta = (phi2 / phi2) / tune
        Dim pi As Single
        pi = Math.PI

        beta = ((2 * pi) / 360) * beta 'grad in rad convertieren
        phi2 = ((2 * pi) / 360) * phi2 'grad in rad convertieren
        new_x = (Math.Sin(beta - offset) * radius) + x
        new_y = (Math.Cos(beta - offset) * radius) + y
        Me.addPA(new_x, new_y, True)
        Do
            new_x = (Math.Sin(beta - offset) * radius) + x
            new_y = (Math.Cos(beta - offset) * radius) + y
            Me.addPA(new_x, new_y, status)
            beta += 0.05 'beta
        Loop Until beta > phi2
    End Sub

    Public Function getDatas() As List(Of Integer())
        Dim result As List(Of Integer())
        result = Me.datas
        Me.datas = Nothing
        Return result
    End Function

    ' ab hier Berechnung für den Kreis in der Drawing View 

    'Berechnung des Rechtecks für die DrawArc - Funktion in der DrawingView 
    Public Function calcRectangle(ByVal middle As Point, ByVal point As Point) As Rectangle

        Me.calc_radius_circle(point.X - middle.X, point.Y - middle.Y)
        Return New Rectangle(middle.X - Me.radius_circle, middle.Y - Me.radius_circle, Me.radius_circle * 2, Me.radius_circle * 2)
    End Function

    'Berechnung des Radius für den Kreis in der DrawingView 
    Private Sub calc_radius_circle(ByVal delta_x As Integer, ByVal delta_y As Integer)
        Me.radius_circle = Math.Sqrt(Math.Pow(delta_x, 2) + Math.Pow(delta_y, 2))
    End Sub

    Public Function calc_startAngle(ByVal m_x As Integer, ByVal p_x As Integer) As Single
        Dim calculation As Double
        calculation = Math.Acos((p_x - m_x) / (Me.radius_circle)) * (180 / Math.PI)
        Return 360 - calculation
    End Function





End Class
