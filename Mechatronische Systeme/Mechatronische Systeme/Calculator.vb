Public Class Calculator
    Private Shared instance As Calculator
    Private datas As List(Of Integer())
    Private cur_x As Integer
    Private cur_y As Integer
    Private radius_circle As Integer 'Radius für den gezeichneten Kreis in der Drawing View 
    Private settings As Save_read_settings

    Private Sub New()
        datas = New List(Of Integer())
        Me.settings = Save_read_settings.getInstance()
    End Sub

    Public Shared ReadOnly Property getInstance() As Calculator
        Get
            If IsNothing(instance) Then
                instance = New Calculator()
            End If
            Return instance
        End Get
    End Property
    'Fügt eine neue Lini hinzu
    Public Sub addPA(ByVal x As Integer, ByVal y As Integer, ByVal status As Boolean)
        Dim arr(2) As Integer

        If (Me.datas Is Nothing) Then
            Me.datas = New List(Of Integer())
            cur_x = 0
            cur_y = 0
        End If
        arr(0) = status
        arr(1) = x - cur_x
        arr(2) = y - cur_y
        datas.Add(arr)
        cur_x = x
        cur_y = y

    End Sub
    'Fügt einen neuen Kreis hinzu
    Public Sub addCS(ByVal x As Integer, ByVal y As Integer, ByVal phi As Integer, ByVal status As Boolean)
        Dim radius As Integer
        Dim beta As Double
        Dim resolution As Double
        Dim phi2 As Double
        Dim new_x As Integer 'new_x und new_y sind die neuen endpunkte jeweils
        Dim new_y As Integer
        Dim tune As Integer 'tuningwert für die feinere Auflösung des Kreises -> GUI
        tune = Me.settings.get_tuning()
        phi2 = phi / 10

        radius = Math.Sqrt(Math.Pow(Math.Abs(x - cur_x), 2) + Math.Pow(Math.Abs(y - cur_y), 2))

        Dim x2 = cur_x 'x + radius
        Dim y2 = cur_y 'y

        Dim offset As Single
        offset = Math.Atan((cur_x - x) / (cur_y - y)) '+ Math.PI / 2 '(Math.Atan((cur_y - y) / (cur_x - x)))
        If y > cur_y And x < cur_x Then
            offset = Math.PI / 2 - Math.Atan((cur_y - y) / (cur_x - x)) '+ Math.PI
        End If
        If y > cur_y And x > cur_x Then
            offset = Math.PI / 2 - Math.Atan((cur_x - x) / (cur_y - y)) '+ Math.PI
        End If
        If y < cur_y And x > cur_x Then
            offset = Math.Atan((cur_y - y) / (cur_x - x)) '+ Math.PI
        End If
        If y < cur_y And x < cur_x Then
            offset = Math.Atan((cur_x - x) / (cur_y - y)) '+ Math.PI
        End If

        resolution = (phi2 / phi2) / (radius / 100) / tune

        Dim pi As Single
        pi = Math.PI

        beta = ((2 * pi) / 360) * beta 'grad in rad convertieren
        phi2 = ((2 * pi) / 360) * phi2 'grad in rad convertieren
        
        Do  'Fügt die einzelnen Teillinien des Kreises hinzu
            new_x = (Math.Sin(beta + offset) * radius) + x
            new_y = (Math.Cos(beta + offset) * radius) + y
            Me.addPA(new_x, new_y, status)
            beta += resolution
        Loop Until beta > phi2

        new_x = (Math.Sin(phi2 + offset) * radius) + x
        new_y = (Math.Cos(phi2 + offset) * radius) + y
        Me.addPA(new_x, new_y, status)

    End Sub

    Public Function calc_startAngleCS(ByVal m_x As Integer, ByVal p_x As Integer, ByVal r As Integer, ByVal y As Integer) As Single
        Dim calculation As Double
        If y < cur_y Then
            calculation = Math.Acos((p_x - m_x) / r) ' * (180 / Math.PI)
            Return calculation
        Else
            calculation = Math.Acos((p_x - m_x) / r) '* (180 / Math.PI)
            Return calculation
        End If
    End Function

    Public Function getDatas() As List(Of Integer())
        Dim result As List(Of Integer())
        result = New List(Of Integer())
        'result = Me.datas 'TODO: func für deep-copy
        For Each item In Me.datas 'temporaly workaround...
            result.Add(item.Clone())
        Next
        Me.datas = Nothing
        Return result
    End Function

    ' ab hier Berechnung für den Kreis in der Drawing View 

    'Berechnung des Rechtecks für die DrawArc - Funktion in der DrawingView 
    Public Function calcRectangle(ByVal middle As Point, ByVal point As Point) As Rectangle

        Me.calc_radius_circle(point.X - middle.X, point.Y - middle.Y)
        Return New Rectangle(middle.X - Me.radius_circle, 260 - middle.Y - Me.radius_circle, Me.radius_circle * 2, Me.radius_circle * 2)
    End Function

    'Berechnung des Radius für den Kreis in der DrawingView 
    Private Sub calc_radius_circle(ByVal delta_x As Integer, ByVal delta_y As Integer)
        Me.radius_circle = Math.Sqrt(Math.Pow(delta_x, 2) + Math.Pow(delta_y, 2))
    End Sub

    'Berechnung des Winkels, ab dem der Kreis gezeichnet werden soll
    Public Function calc_startAngle(ByVal middle As Point, ByVal p_start As Point) As Single  'As Integer
        Return (Math.Atan2((middle.Y - p_start.Y), (p_start.X - middle.X)) / (Math.PI / 180))
    End Function

End Class
