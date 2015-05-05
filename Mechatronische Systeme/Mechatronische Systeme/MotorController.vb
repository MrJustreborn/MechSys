Public Class MotorController
    Private Shared instance As MotorController
    Private datasCM As List(Of Integer())
    Private datasSteps As List(Of Integer())
    Private max_steps_x As Integer
    Private max_steps_y As Integer
    Private max_x As Integer 'die cm des blattes warscheinlich A4
    Private max_y As Integer
    Private steps_per_cm_x As Integer
    Private steps_per_cm_y As Integer

    Private cur_item As Integer

    Private xMotor As List(Of Integer())
    Private yMotor As List(Of Integer())
    Private cur_x As Integer
    Private cur_y As Integer

    'konstruktor als singelton
    Private Sub New()
        xMotor = New List(Of Integer())
        yMotor = New List(Of Integer())

        xMotor.Add({5, 5})
        xMotor.Add({5, -5})
        xMotor.Add({-5, -5})
        xMotor.Add({-5, 5})

        yMotor.Add({5, 5})
        yMotor.Add({5, -5})
        yMotor.Add({-5, -5})
        yMotor.Add({-5, 5})
        cur_item = 0
    End Sub
    Public Shared ReadOnly Property getInstance() As MotorController
        Get
            If IsNothing(instance) Then
                instance = New MotorController()
            End If
            Return instance
        End Get
    End Property

    Private Sub reset() 'reset Motoren, zähle die steps für einmal komplett ausfahren
    End Sub

    Public Sub setDatas(datas As List(Of Integer())) ' bekommt das Daten-Array mit den Linien und Stift zuständen
        'berechnet anhand der koordinaten des Arrays dir anzahl der Steps und konvertiert somit die cm in steps für die motorsteuerung
        Me.datasCM = datas
        Me.calDatas()
    End Sub
    Private Sub calDatas()
        Dim pos As Integer
        Dim xStep As Integer
        Dim yStep As Integer
        pos = 0
        Do
            xStep = Me.datasCM.Item(pos)(1) * steps_per_cm_x
            yStep = Me.datasCM.Item(pos)(2) * steps_per_cm_y
            Me.datasSteps.Add({Me.datasCM.Item(pos)(0), xStep, yStep})
            pos += 1
        Loop Until pos = Me.datasCM.Count
    End Sub

    Public Function drawNext() As Boolean 'solange Bool=true, hat noch ein datensatz im Array und kann weiter zeichnen
        Me.move(Me.datasSteps.Item(cur_item)(1), Me.datasSteps.Item(cur_item)(2), Me.datasSteps.Item(cur_item)(0))
        cur_item += 1
        Return Not (cur_item = Me.datasSteps.Count)
    End Function


    Private Sub move(ByVal x_steps As Integer, ByVal y_steps As Integer, ByVal status As Boolean)
        'bewegt den Stift in x,y richtig mit den angegebenen Steps so, dass die Motoren unterschiedlich schnell laufen damit die Endposition gleichzeitig erreicht wird
    End Sub

    Private Sub xMove(ByVal steps As Integer, ByVal speed As Integer) 'Thread 0

        Do Until steps = 0
            steps -= 1
            'wait
            xMotor.Item(cur_x)(0) 'ausgang 1 motorx
            xMotor.Item(cur_x)(1) 'ausgang 2 motorx

            cur_x += 1
            cur_x = cur_x Mod xMotor.Count
        Loop
    End Sub
    Private Sub yMove(ByVal steps As Integer, ByVal speed As Integer) 'Thread 1

        Do Until steps = 0
            steps -= 1
            'wait
            yMotor.Item(cur_y)(0) 'ausgang 3 motory
            yMotor.Item(cur_y)(1) 'ausgang 4 motory

            cur_y += 1
            cur_y = cur_y Mod yMotor.Count
        Loop
    End Sub
End Class
