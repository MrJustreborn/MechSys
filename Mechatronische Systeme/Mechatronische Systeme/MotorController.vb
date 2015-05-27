Imports System.Threading

Public Class MotorController
    Private Shared instance As MotorController
    Private datasMM As List(Of Integer())
    Private datasSteps As List(Of Integer())
    Private max_steps_x As Integer
    Private max_steps_y As Integer
    Private max_x As Integer 'die mm des blattes warscheinlich A4
    Private max_y As Integer
    Private steps_per_mm_x As Integer
    Private steps_per_mm_y As Integer

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
        Me.datasMM = datas
        Me.calDatas()
    End Sub
    Private Sub calDatas()
        Dim pos As Integer
        Dim xStep As Integer
        Dim yStep As Integer
        pos = 0
        Do
            xStep = Me.datasMM.Item(pos)(1) * steps_per_mm_x
            yStep = Me.datasMM.Item(pos)(2) * steps_per_mm_y
            Me.datasSteps.Add({Me.datasMM.Item(pos)(0), xStep, yStep})
            pos += 1
        Loop Until pos = Me.datasMM.Count
    End Sub

    Private running As Boolean = False
    Private running_pause As Boolean = False
    Private main_thread As Thread
    Public Sub start()
        running = True
        main_thread = New Thread(AddressOf main)
        main_thread.IsBackground = True
        main_thread.Start()
    End Sub
    Public Sub break()
        running = False
        'motoren resetten etc
    End Sub
    Public Sub pause()
        running_pause = True
    End Sub
    Public Sub unpause()
        running_pause = False
    End Sub

    Private Sub main()
        While running And drawNext()
            While running_pause
                Thread.Sleep(1)
            End While
        End While
    End Sub

    Private Function drawNext() As Boolean 'solange Bool=true, hat noch ein datensatz im Array und kann weiter zeichnen
        Me.move(Me.datasSteps.Item(cur_item)(1), Me.datasSteps.Item(cur_item)(2), Me.datasSteps.Item(cur_item)(0))
        cur_item += 1
        Return Not (cur_item = Me.datasSteps.Count)
    End Function

    Private xSteps As Integer
    Private xSpeed As Integer
    Private ySteps As Integer
    Private ySpeed As Integer
    Private xThread As Thread
    Private yThread As Thread
    Private Sub move(ByVal x_steps As Integer, ByVal y_steps As Integer, ByVal status As Boolean)
        'bewegt den Stift in x,y richtig mit den angegebenen Steps so, dass die Motoren unterschiedlich schnell laufen damit die Endposition gleichzeitig erreicht wird
        xThread = New Thread(AddressOf xMove)
        xThread.IsBackground = True
        yThread = New Thread(AddressOf yMove)
        yThread.IsBackground = True

        xSteps = x_steps
        ySteps = y_steps
        xSpeed = 1 'TODO: calc speed
        ySpeed = 1 'TODO: calc speed
        xThread.Start()
        yThread.Start()
    End Sub


    'muss ich noch anders schreiben, weil ein thread keine parameter bekommen kann...
    Private Sub xMove() 'Thread 0

        Dim dir = xSteps / xSteps
        Do Until xSteps = 0
            xSteps -= dir
            xMinWait()


            'xMotor.Item(cur_x)(0) 'ausgang 1 motorx
            'xMotor.Item(cur_x)(1) 'ausgang 2 motorx

            cur_x += dir
            cur_x = cur_x Mod xMotor.Count
        Loop
    End Sub
    Private Sub yMove() 'Thread 1

        Dim dir = ySteps / ySteps
        Do Until ySteps = 0
            ySteps -= dir
            yMinWait()


            'yMotor.Item(cur_y)(0) 'ausgang 3 motory
            'yMotor.Item(cur_y)(1) 'ausgang 4 motory

            cur_y += dir
            cur_y = cur_y Mod yMotor.Count
        Loop
    End Sub


    Private xmw As Integer = 3500000
    Private ymw As Integer = 3500000
    Private Sub xMinWait()
        Dim t As Integer = 0
        Do
            t += 1
        Loop Until t >= xmw
    End Sub
    Private Sub yMinWait()
        Dim t As Integer = 0
        Do
            t += 1
        Loop Until t >= ymw
    End Sub

End Class
