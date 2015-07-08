Imports System.Threading
Imports System.Text

Public Class MotorController
    Private Shared instance As MotorController
    Private datasMM As List(Of Integer())
    Private datasSteps As List(Of Integer())
    Private max_steps_x As Integer
    'Private max_steps_y As Integer
    'Private max_x As Integer = 2000 'die mm des blattes warscheinlich A4
    'Private max_y As Integer = 2000
    Private steps_per_mm_x As Double = 2.85
    Private steps_per_mm_y As Double = 2.36 '2.36

    Private cur_item As Integer

    Private xMotor As List(Of Double())
    Private yMotor As List(Of Double())
    Private cur_x As Integer
    Private cur_y As Integer
    Dim VoltX = 1
    Dim VoltY = 1

    Private con As Controller
    Public Sub setController(ByRef con As Controller)
        Me.con = con
    End Sub
    'konstruktor als singelton
    Private Sub New()
        Control.CheckForIllegalCrossThreadCalls = False
        Console.WriteLine("new moCon")
        datasSteps = New List(Of Integer())
        OpenMEiDSDriver()
        WriteToSubdevice(subdeviceList(0), subdeviceList(0).GetRange(0), 0)
        WriteToSubdevice(subdeviceList(1), subdeviceList(1).GetRange(0), 0)
        WriteToSubdevice(subdeviceList(2), subdeviceList(2).GetRange(0), 0)
        WriteToSubdevice(subdeviceList(3), subdeviceList(3).GetRange(0), 0)
        WriteDigitalValue(dsubdeviceList(0), 0, 0)
        xMotor = New List(Of Double())
        yMotor = New List(Of Double())

        Console.WriteLine(subdeviceList.Count)
        Console.WriteLine(dsubdeviceList.Count)
        Console.WriteLine(disubdeviceList.Count)

        'xMotor

        xMotor.Add({VoltX, VoltX})
        xMotor.Add({VoltX / 2, VoltX})
        xMotor.Add({0, VoltX})
        xMotor.Add({-VoltX / 2, VoltX})

        xMotor.Add({-VoltX, VoltX})
        xMotor.Add({-VoltX, VoltX / 2})
        xMotor.Add({-VoltX, 0})
        xMotor.Add({-VoltX, -VoltX / 2})

        xMotor.Add({-VoltX, -VoltX})
        xMotor.Add({-VoltX / 2, -VoltX})
        xMotor.Add({0, -VoltX})
        xMotor.Add({VoltX / 2, -VoltX})

        xMotor.Add({VoltX, -VoltX})
        xMotor.Add({VoltX, -VoltX / 2})
        xMotor.Add({VoltX, 0})
        xMotor.Add({VoltX, VoltX / 2})

        'yMotor

        yMotor.Add({VoltY, 0})
        yMotor.Add({VoltY, -VoltY})

        yMotor.Add({0, -VoltY})
        yMotor.Add({-VoltY, -VoltY})

        yMotor.Add({-VoltY, 0})
        yMotor.Add({-VoltY, VoltY})

        yMotor.Add({0, VoltY})
        yMotor.Add({VoltY, VoltY})


        cur_item = 0

        reset()
        WriteToSubdevice(subdeviceList(0), subdeviceList(0).GetRange(0), 0)
        WriteToSubdevice(subdeviceList(1), subdeviceList(1).GetRange(0), 0)
        WriteToSubdevice(subdeviceList(2), subdeviceList(2).GetRange(0), 0)
        WriteToSubdevice(subdeviceList(3), subdeviceList(3).GetRange(0), 0)
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
        Console.WriteLine("reset motor")
        ' move(300, 0, False)
        'move(-10, 0, False)
        'move(0, -10, False)
        'move(0, 10, False)
        Thread.Sleep(250)
        'Dim a = 0
        'Dim b = 100
        'Do
        '    'move(100, 0, False)
        '    move(-100, 0, False)
        '    a += 1
        'Loop Until a >= b


        'move(0, Math.Round(500 * steps_per_mm_y), False)
        'Thread.Sleep(1000)
        'move(Math.Round(100 * steps_per_mm_x), 0, False)
        'move(0, -Math.Round(500 * steps_per_mm_y), False)

        'move(-Math.Round(500 * steps_per_mm_x), Math.Round(500 * steps_per_mm_y), False)
        'move(-Math.Round(500 * steps_per_mm_x), -Math.Round(500 * steps_per_mm_y), False)
        'move(Math.Round(500 * steps_per_mm_x), -Math.Round(500 * steps_per_mm_y), False)
        'move(Math.Round(500 * steps_per_mm_x), Math.Round(500 * steps_per_mm_y), False)

        'move(-Math.Round(500 * steps_per_mm_x), -Math.Round(500 * steps_per_mm_y), False)
        'move(-Math.Round(500 * steps_per_mm_x), Math.Round(500 * steps_per_mm_y), False)
        'move(Math.Round(500 * steps_per_mm_x), Math.Round(500 * steps_per_mm_y), False)
        'move(Math.Round(500 * steps_per_mm_x), -Math.Round(500 * steps_per_mm_y), False)

        'move(Math.Round(1000 * steps_per_mm_x), 0, False)
        'move(0, -Math.Round(1000 * steps_per_mm_y), False)
        'move(-Math.Round(2000 * steps_per_mm_x), Math.Round(1000 * steps_per_mm_y), False)

        'move(0, -Math.Round(500 * steps_per_mm_y), True)
        'move(Math.Round(1000 * steps_per_mm_x), -Math.Round(1000 * steps_per_mm_y), False)
        'move(-Math.Round(1000 * steps_per_mm_x), 0, True)
        'move(Math.Round(1000 * steps_per_mm_x), Math.Round(1000 * steps_per_mm_y), False)
        'move(-Math.Round(1000 * steps_per_mm_x), Math.Round(500 * steps_per_mm_y), True)
        'move(0, 0, False)

        'move(0, Math.Round(100 * steps_per_mm_y), False)
        'move(Math.Round(600 * steps_per_mm_x), Math.Round(600 * steps_per_mm_y), False)

        'move(0, Math.Round(100 * steps_per_mm_y), False)
        'move(-Math.Round(600 * steps_per_mm_x), Math.Round(600 * steps_per_mm_y), False)

        'move(0, Math.Round(100 * steps_per_mm_y), False)
        'move(Math.Round(300 * steps_per_mm_x), Math.Round(600 * steps_per_mm_y), False)

        'move(0, Math.Round(100 * steps_per_mm_y), False)
        'move(-Math.Round(600 * steps_per_mm_x), Math.Round(300 * steps_per_mm_y), False)

        'move(0, Math.Round(100 * steps_per_mm_y), False)
        'move(Math.Round(500 * steps_per_mm_x), 0, False)
        'move(0, Math.Round(100 * steps_per_mm_y), False)
        'move(Math.Round(500 * steps_per_mm_x), 0, False)
        'move(0, Math.Round(100 * steps_per_mm_y), False)
        'move(-Math.Round(500 * steps_per_mm_x), 0, False)
        'move(0, Math.Round(100 * steps_per_mm_y), False)
        'move(-Math.Round(500 * steps_per_mm_x), 0, False)
        'move(0, Math.Round(100 * steps_per_mm_y), False)

        'Return
        Dim dir = 1
        move(0, 0, True)
        'Do Until GetDigitalValue(disubdeviceList(0), 0) = 1
        '    xWait()
        '    WriteToSubdevice(subdeviceList(0), subdeviceList(0).GetRange(0), xMotor.Item(cur_x)(0))
        '    WriteToSubdevice(subdeviceList(1), subdeviceList(1).GetRange(0), xMotor.Item(cur_x)(1))

        '    cur_x += dir
        '    If dir < 0 Then
        '        If cur_x <= 0 Then
        '            cur_x = xMotor.Count - 1
        '        End If
        '    Else
        '        cur_x = cur_x Mod xMotor.Count
        '    End If
        '    max_steps_x += 1
        'Loop

        max_steps_x = 0
        dir = -1
        Do Until GetDigitalValue(disubdeviceList(0), 1) = 1
            xWait()
            WriteToSubdevice(subdeviceList(0), subdeviceList(0).GetRange(0), xMotor.Item(cur_x)(0))
            WriteToSubdevice(subdeviceList(1), subdeviceList(1).GetRange(0), xMotor.Item(cur_x)(1))

            cur_x += dir
            If dir < 0 Then
                If cur_x <= 0 Then
                    cur_x = xMotor.Count - 1
                End If
            Else
                cur_x = cur_x Mod xMotor.Count
            End If
            max_steps_x += 1
        Loop
        Console.WriteLine("Steps_x: " + max_steps_x.ToString)
        'steps_per_mm_x = max_steps_x / max_x
        move(Math.Round(398 * steps_per_mm_x), Math.Round(170 * steps_per_mm_y), True)
        move(0, 0, False)
        WriteToSubdevice(subdeviceList(0), subdeviceList(0).GetRange(0), 0)
        WriteToSubdevice(subdeviceList(1), subdeviceList(1).GetRange(0), 0)
        WriteToSubdevice(subdeviceList(2), subdeviceList(2).GetRange(0), 0)
        WriteToSubdevice(subdeviceList(3), subdeviceList(3).GetRange(0), 0)
    End Sub

    Public Sub setDatas(ByVal datas As List(Of Integer())) ' bekommt das Daten-Array mit den Linien und Stift zuständen
        'berechnet anhand der koordinaten des Arrays dir anzahl der Steps und konvertiert somit die cm in steps für die motorsteuerung
        Me.datasMM = datas
        Me.calDatas()
        cur_item = 0
    End Sub
    Private Sub calDatas()
        Dim pos As Integer
        Dim xStep As Integer
        Dim yStep As Integer
        pos = 0
        Do
            xStep = Math.Round(Me.datasMM.Item(pos)(1) * steps_per_mm_x)
            yStep = Math.Round(Me.datasMM.Item(pos)(2) * steps_per_mm_y)
            Me.datasSteps.Add({Me.datasMM.Item(pos)(0), xStep, yStep})
            pos += 1
        Loop Until pos = Me.datasMM.Count
    End Sub

#Region "Schnittstelle für die Ansteuerung"
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
    End Sub
    Public Sub pause()
        running_pause = True
    End Sub
    Public Sub unpause()
        running_pause = False
    End Sub

    Private Sub main()
        cur_item = 0
        While running And drawNext()
            'Console.WriteLine(cur_item)
            con.progress(Math.Floor(cur_item / Me.datasSteps.Count * 100))
            con.line_live_print(Me.datasMM(cur_item - 1)(1), Me.datasMM(cur_item - 1)(2), Me.datasMM(cur_item - 1)(0))
            'Console.WriteLine(cur_item / Me.datasSteps.Count * 100)
        End While
        con.line_live_print(Me.datasMM(cur_item - 1)(1), Me.datasMM(cur_item - 1)(2), Me.datasMM(cur_item - 1)(0))
        con.progress(Math.Floor(cur_item / Me.datasSteps.Count * 100))
        con.plotter_finished()
        Console.WriteLine("finished")
        con.progress(0)
        move(0, 2000, True)
        reset()
    End Sub

    Private Function drawNext() As Boolean 'solange Bool=true, hat noch ein datensatz im Array und kann weiter zeichnen
        Me.move(Me.datasSteps.Item(cur_item)(1), Me.datasSteps.Item(cur_item)(2), Me.datasSteps.Item(cur_item)(0))
        cur_item += 1
        Return Not (cur_item = Me.datasSteps.Count)
    End Function
#End Region

    Private xSteps As Integer
    Private xLastDir As Single = 0
    Private ySteps As Integer
    Private yLastDir As Integer = 0
    Private lastStatus As Boolean = True
    Private xThread As Thread ' = New Thread(AddressOf xMove)
    Private yThread As Thread ' = New Thread(AddressOf yMove)
    Private Sub move(ByVal x_steps As Integer, ByVal y_steps As Integer, ByVal status As Boolean)
        'Console.WriteLine("x: " + x_steps.ToString + "|y: " + y_steps.ToString + "|" + status.ToString)
        'bewegt den Stift in x,y richtig mit den angegebenen Steps so, dass die Motoren unterschiedlich schnell laufen damit die Endposition gleichzeitig erreicht wird
        Dim xmm = x_steps / steps_per_mm_x
        Dim ymm = y_steps / steps_per_mm_y

        'xmw = 90000 * 4.5
        'ymw = 900000

        'If y_steps > 0 Then
        '    xmw = 90000 * 8.35
        'End If

        WriteDigitalValue(dsubdeviceList(0), status, 0)
        If Not status = lastStatus Then
            Thread.Sleep(500)
        End If
        lastStatus = status

        xThread = New Thread(AddressOf xMove)
        xThread.IsBackground = True
        xThread.Priority = ThreadPriority.Highest
        yThread = New Thread(AddressOf yMove)
        yThread.IsBackground = True
        yThread.Priority = ThreadPriority.Highest

        Dim yDir = 1
        If y_steps < 0 Then
            yDir = -1
        End If
        If Not yDir = yLastDir Then
            y_steps = y_steps - (4 * steps_per_mm_y) 'umkehrspiel y 1.2
            yWait()
        End If
        yLastDir = yDir

        Dim xDir = 1
        If x_steps < 0 Then
            xDir = -1
        End If
        If Not xDir = xLastDir Then
            x_steps = x_steps '+ (2 * steps_per_mm_x) 'umkehrspiel x
            xWait()
        End If
        xLastDir = xDir

        ySteps = y_steps
        xSteps = x_steps

        If y_steps < 0 Then
            ySteps = y_steps '* 0.88 ' 0.88 '215 'scalierungsfaktor zur fehlerkorrektur y
        Else
            ySteps = y_steps
        End If
        If x_steps < 0 Then
            xSteps = x_steps '* 0.9442 'scalierungsfaktor zur fehlerkorrektur x
        Else
            xSteps = x_steps
        End If

        xw = xmw
        yw = ymw
        'If Not xmm = 0 And Not ymm = 0 Then
        '    Dim v As Double = Math.Abs(ymm / xmm)
        '    If v < 1 Then
        '        v += 1
        '        xw = Math.Round(xmw * 6.9)
        '        yw = Math.Round(v * ymw * 1.15)
        '    Else
        '        xw = Math.Round(v * xmw * 6.9)
        '    End If
        'End If
        'If Not xmm = 0 And Not ymm = 0 Then
        '    Dim v As Double = Math.Abs(ymm / xmm)
        '    Console.WriteLine(ymm)
        '    Console.WriteLine(xmm)
        '    Console.WriteLine(v)
        '    If v < 1 Then
        '        v += 1
        '        yw = Math.Round(v * ymw)
        '    Else
        '        xw = Math.Round(v * xmw)
        '    End If
        '    If y_steps > 0 Then
        '        If x_steps > 0 Then
        '            xw = xw + Math.Round(0.189 * xmw) 'links unten
        '        Else
        '            xw = xw + Math.Round(0.195 * xmw) 'rechts unten
        '        End If
        '    End If
        'End If
        If Not xmm = 0 And Not ymm = 0 Then
            Dim v As Double = Math.Abs(ymm / xmm)
            If v < 1 Then
                v = Math.Abs(xmm / ymm)
                yw = Math.Round(v * ymw)
            Else
                xw = Math.Round(v * xmw)
            End If
            'If y_steps > 0 Then
            '    If x_steps < 0 Then
            '        xw = xw '+ Math.Round(0.09 * xmw) 'rechts oben
            '    Else
            '        xw = xw '+ Math.Round(0.04 * xmw) 'links oben
            '    End If
            'Else
            '    If x_steps > 0 Then
            '        yw = yw '+ Math.Round(0.04 * ymw) 'rechts unten
            '    Else
            '        yw = yw + Math.Round(0.04 * ymw) 'links unten
            '    End If
            'End If
        End If

        If Not x_steps = 0 Then
            xThread.Start()
        Else
            WriteToSubdevice(subdeviceList(0), subdeviceList(0).GetRange(0), xMotor.Item(cur_x)(0) / 2)
            WriteToSubdevice(subdeviceList(1), subdeviceList(1).GetRange(0), xMotor.Item(cur_x)(1) / 2)
        End If
        If Not y_steps = 0 Then
            yThread.Start()
        Else
            WriteToSubdevice(subdeviceList(2), subdeviceList(2).GetRange(0), yMotor.Item(cur_y)(0) / 2)
            WriteToSubdevice(subdeviceList(3), subdeviceList(3).GetRange(0), yMotor.Item(cur_y)(1) / 2)
        End If

        If Not x_steps = 0 Then
            xThread.Join()
        End If
        If Not y_steps = 0 Then
            yThread.Join()
        End If
        If x_steps < 100 Or y_steps < 100 Then
            Thread.Sleep(10)
        End If
        Thread.Sleep(10)
    End Sub

    Private Function xVolt(ByVal wait As Integer) As Double
        Return 1824.8 * Math.Pow(wait, -0.543)
    End Function

    Private Function yVolt(ByVal wait As Integer) As Double
        Return 503.45 * Math.Pow(wait, -0.359)
    End Function

    'muss ich noch anders schreiben, weil ein thread keine parameter bekommen kann...
    Private Sub xMove() 'Thread 0
        Dim dir = 1
        If xSteps < 0 Then
            dir = -1
        End If

        Do Until xSteps = 0
            xSteps -= dir
            xWait()
            pause_waitX()


            'xMotor.Item(cur_x)(0) 'ausgang 1 motorx
            'xMotor.Item(cur_x)(1) 'ausgang 2 motorx
            'WriteSingleValue(subdeviceList(0), xMotor.Item(cur_x)(0)) 'ausgang 1 motorx
            'WriteSingleValue(subdeviceList(1), xMotor.Item(cur_x)(1)) 'ausgang 2 motorx
            WriteToSubdevice(subdeviceList(0), subdeviceList(0).GetRange(0), xMotor.Item(cur_x)(0) * xVolt(xw))
            WriteToSubdevice(subdeviceList(1), subdeviceList(1).GetRange(0), xMotor.Item(cur_x)(1) * xVolt(xw))

            cur_x += dir
            If dir < 0 Then
                If cur_x < 0 Then
                    cur_x = xMotor.Count - 1
                End If
            Else
                cur_x = cur_x Mod xMotor.Count
            End If
        Loop
        WriteToSubdevice(subdeviceList(0), subdeviceList(0).GetRange(0), 0)
        WriteToSubdevice(subdeviceList(1), subdeviceList(1).GetRange(0), 0)
    End Sub
    Private Sub yMove() 'Thread 1

        Dim dir = 1
        If ySteps < 0 Then
            dir = -1
        End If
        Do Until ySteps = 0
            ySteps -= dir
            yWait()
            pause_waitY()


            'yMotor.Item(cur_y)(0) 'ausgang 3 motory
            'yMotor.Item(cur_y)(1) 'ausgang 4 motory
            'WriteSingleValue(subdeviceList(2), xMotor.Item(cur_y)(0)) 'ausgang 3 motorx
            'WriteSingleValue(subdeviceList(3), xMotor.Item(cur_y)(1)) 'ausgang 4 motorx
            WriteToSubdevice(subdeviceList(2), subdeviceList(2).GetRange(0), yMotor.Item(cur_y)(0) * yVolt(yw))
            WriteToSubdevice(subdeviceList(3), subdeviceList(3).GetRange(0), yMotor.Item(cur_y)(1) * yVolt(yw))

            cur_y += dir
            If dir < 0 Then
                If cur_y < 0 Then
                    cur_y = yMotor.Count - 1
                End If
            Else
                cur_y = cur_y Mod yMotor.Count
            End If
        Loop
        WriteToSubdevice(subdeviceList(2), subdeviceList(2).GetRange(0), 0)
        WriteToSubdevice(subdeviceList(3), subdeviceList(3).GetRange(0), 0)
    End Sub

#Region "Waiting"
    'waits...
    Private Sub pause_waitX()
        While running_pause
            WriteToSubdevice(subdeviceList(0), subdeviceList(0).GetRange(0), 0)
            WriteToSubdevice(subdeviceList(1), subdeviceList(1).GetRange(0), 0)
            xWait()
        End While
    End Sub
    Private Sub pause_waitY()
        While running_pause
            WriteToSubdevice(subdeviceList(2), subdeviceList(2).GetRange(0), 0)
            WriteToSubdevice(subdeviceList(3), subdeviceList(3).GetRange(0), 0)
            yWait()
        End While
    End Sub

    Private xw As Integer
    Private yw As Integer
    Private xmw As Integer = 90000 * 8.35
    Private ymw As Integer = 900000
    Private Sub xWait()
        Dim t As Integer = 0
        Do
            t += 1
        Loop Until t >= xw
    End Sub
    Private Sub yWait()
        Dim t As Integer = 0
        Do
            t += 1
        Loop Until t >= yw
    End Sub
    'Private Sub xWait()
    'Dim t As Integer = 0
    '   Do
    '      t += 1
    ' Loop Until t >= xmw * xSpeed
    'End Sub
    'Private Sub yWait()
    'Dim t As Integer = 0
    '   Do
    '      t += 1
    ' Loop Until t >= ymw * ySpeed
    'End Sub
#End Region

#Region "MEiDSFunctions"
    'Hardware
    Private openErrSuccess As Integer = Constants.ME_IDS_NOTOPENED
    Private lineNumber As Integer
    Private subdeviceList As New List(Of AoSubdevice)
    Private dsubdeviceList As New List(Of DoSubdevice)
    Private disubdeviceList As New List(Of DiSubdevice)
    Private Sub OpenMEiDSDriver()
        Try
            'textBoxInfo.AppendText("Opening Maindriver..." & Environment.NewLine)
            openErrSuccess = meIDS.meOpen(meIDS.ME_OPEN_NO_FLAGS)

            If openErrSuccess = meIDS.ME_ERRNO_SUCCESS Then
                'DisplayVersionLibrary()
                'DisplayVersionMainDriver()

                'textBoxInfo.AppendText(Environment.NewLine)

                Dim numDevices As Integer
                meIDS.meQueryNumberDevices(numDevices)
                'textBoxInfo.AppendText("Number of devices found: " & numDevices.ToString() & Environment.NewLine)
                GetAoSubdevices(numDevices)
            Else
                'displayErrorMessage("meOpen - Error: ", openErrSuccess)
            End If
        Catch ex As DllNotFoundException
            'textBoxInfo.AppendText("The ME-iDS is not properly installed." & Environment.NewLine)
            'textBoxInfo.AppendText(ex.Message & Environment.NewLine)
        End Try
    End Sub
    Private Sub CloseMEiDSDriver()
        If openErrSuccess = meIDS.ME_ERRNO_SUCCESS Then
            meIDS.meClose(meIDS.ME_CLOSE_NO_FLAGS)
            openErrSuccess = Constants.ME_IDS_NOTOPENED
            'btnSingleWrite.Enabled = False
            'btnResetSubdev.Enabled = False
            subdeviceList.Clear()
            'coBoxSubDevs.Items.Clear()
            'coBoxChannel.Items.Clear()
            'coBoxRange.Items.Clear()
        End If
    End Sub
    Private Sub GetAoSubdevices(ByVal numDevices As Integer)
        Dim idxDevice As Integer

        If openErrSuccess = meIDS.ME_ERRNO_SUCCESS AndAlso numDevices > 0 Then
            'textBoxInfo.AppendText("Retrieving subdevices of type ME_TYPE_AO (Analog output)..." & Environment.NewLine)
            subdeviceList.Clear()
            'coBoxSubDevs.Items.Clear()
            For idxDevice = 0 To numDevices - 1
                Dim meError As Integer
                Dim plugged As Integer

                meError = GetDevicePlugged(idxDevice, plugged)
                If meError = meIDS.ME_ERRNO_SUCCESS AndAlso plugged = meIDS.ME_PLUGGED_IN Then
                    GetSubdevicesByType(idxDevice, meIDS.ME_TYPE_AO)
                    GetSubdevicesByType(idxDevice, meIDS.ME_TYPE_DO)
                    GetSubdevicesByType(idxDevice, meIDS.ME_TYPE_DI)
                Else
                    'textBoxInfo.AppendText("Device " & idxDevice.ToString() & " not plugged in" & Environment.NewLine)
                End If
            Next

        End If
        'DisplaySubdevices()
    End Sub
    Private Sub GetSubdevicesByType(ByVal idxDevice As Integer, ByVal subdeviceType As Integer)
        Dim meError As Integer
        Dim numSubdevices As Integer
        Dim idxMatchedSubdevice As Integer

        meError = meIDS.meQueryNumberSubdevices(idxDevice, numSubdevices)
        If meError = meIDS.ME_ERRNO_SUCCESS Then
            Dim deviceName = New StringBuilder(meIDS.ME_DEVICE_NAME_MAX_COUNT)
            meIDS.meQueryNameDevice(idxDevice, deviceName, meIDS.ME_DEVICE_NAME_MAX_COUNT)
            Dim idxSubdevice As Integer = 0
            While idxSubdevice < numSubdevices
                meError = meIDS.meQuerySubdeviceByType(idxDevice, _
                                                 idxSubdevice, _
                                                 subdeviceType, _
                                                 meIDS.ME_SUBTYPE_ANY, _
                                                 idxMatchedSubdevice)

                If meError = meIDS.ME_ERRNO_SUCCESS And subdeviceType = meIDS.ME_TYPE_AO Then
                    meError = AddAoSubdevice(deviceName.ToString(), idxDevice, idxMatchedSubdevice, subdeviceType)
                    idxSubdevice = idxMatchedSubdevice + 1
                ElseIf meError = meIDS.ME_ERRNO_SUCCESS And subdeviceType = meIDS.ME_TYPE_DO Then
                    meError = AddDoSubdevice(deviceName.ToString(), idxDevice, idxMatchedSubdevice, subdeviceType)
                    idxSubdevice = idxMatchedSubdevice + 1
                ElseIf meError = meIDS.ME_ERRNO_SUCCESS And subdeviceType = meIDS.ME_TYPE_DI Then
                    meError = AddDiSubdevice(deviceName.ToString(), idxDevice, idxMatchedSubdevice, subdeviceType)
                    idxSubdevice = idxMatchedSubdevice + 1
                Else
                    Exit While
                End If
            End While
        End If
    End Sub
    Private Function AddAoSubdevice(ByVal deviceName As String, ByVal idxDevice As Integer, ByVal idxSubdevice As Integer, ByVal subdeviceType As Integer) As Integer
        Dim meError As Integer
        Dim numOfChannels As Integer

        meIDS.meQueryNumberChannels(idxDevice, idxSubdevice, numOfChannels)
        If meError = meIDS.ME_ERRNO_SUCCESS Then
            Dim aoSubdev As AoSubdevice = New AoSubdevice(deviceName.ToString, idxDevice, idxSubdevice, numOfChannels)
            subdeviceList.Add(aoSubdev)
            AddAnalogRanges(aoSubdev)

            'coBoxSubDevs.Items.Add(deviceName.ToString _
            '                      & ",  Device " & idxDevice.ToString() _
            '                      & ",  Subdevice " & idxSubdevice.ToString() _
            '                      & ",  Type: " & GetSubDevTypeName(subdeviceType) _
            '                      & ",  Channels: " & numOfChannels.ToString() _
            '                      & ",  Ranges: " & aoSubdev.GetRangeCount().ToString())
        End If
        Return meError
    End Function
    Private Function AddDoSubdevice(ByVal deviceName As String, ByVal idxDevice As Integer, ByVal idxSubdevice As Integer, ByVal subdeviceType As Integer) As Integer
        Dim meError As Integer
        Dim numOfChannels As Integer

        meIDS.meQueryNumberChannels(idxDevice, idxSubdevice, numOfChannels)
        If meError = meIDS.ME_ERRNO_SUCCESS Then
            Dim doSubdev As DoSubdevice = New DoSubdevice(deviceName.ToString, idxDevice, idxSubdevice, numOfChannels)
            dsubdeviceList.Add(doSubdev)
        End If
        Return meError
    End Function
    Private Function AddDiSubdevice(ByVal deviceName As String, ByVal idxDevice As Integer, ByVal idxSubdevice As Integer, ByVal subdeviceType As Integer) As Integer
        Dim meError As Integer
        Dim numOfChannels As Integer

        meIDS.meQueryNumberChannels(idxDevice, idxSubdevice, numOfChannels)
        If meError = meIDS.ME_ERRNO_SUCCESS Then
            Dim diSubdev As DiSubdevice = New DiSubdevice(deviceName.ToString, idxDevice, idxSubdevice, numOfChannels)
            disubdeviceList.Add(diSubdev)
        End If
        Return meError
    End Function
    Private Sub AddAnalogRanges(ByVal aoSubdev As AoSubdevice)
        Dim idxRange As Integer
        Dim numOfRanges As Integer
        meIDS.meQueryNumberRanges(aoSubdev.deviceIndex, _
                                      aoSubdev.subdevIndex, _
                                      meIDS.ME_UNIT_ANY, _
                                      numOfRanges)
        idxRange = 0
        While (idxRange < numOfRanges)
            AddAnalogRange(aoSubdev, idxRange)
            idxRange = idxRange + 1
        End While
    End Sub
    Private Sub AddAnalogRange(ByVal aoSubdev As AoSubdevice, ByVal idxRange As Integer)
        Dim meError As Integer
        Dim unit As Integer
        Dim physMin As Double
        Dim physMax As Double
        Dim digitalMax As Integer
        meError = meIDS.meQueryRangeInfo(aoSubdev.deviceIndex, _
                                   aoSubdev.subdevIndex, _
                                   idxRange, _
                                   unit, _
                                   physMin, _
                                   physMax, _
                                   digitalMax)
        If meError = meIDS.ME_ERRNO_SUCCESS Then
            aoSubdev.AddRange(unit, digitalMax, physMin, physMax)
        End If
    End Sub
    Dim lock As New Object
    Private Sub WriteToSubdevice(ByVal aoSubDevice As AoSubdevice, ByVal aoRange As AnalogRange, ByVal valAnalog As Double)
        'SyncLock lock
        Dim meError As Integer
        Dim valDigital As Integer
        meError = ConvertPhysicalToDigital(aoSubDevice, aoRange, valAnalog, valDigital)

        If (meError = meIDS.ME_ERRNO_SUCCESS) Then

            meError = ConfigureSubdeviceForOutput(aoSubDevice)
            If (meError = meIDS.ME_ERRNO_SUCCESS) Then
                meError = WriteSingleValue(aoSubDevice, valDigital)
                If (meError = meIDS.ME_ERRNO_SUCCESS) Then
                    'DisplayValue(aoSubDevice, coBoxChannel.SelectedIndex, valAnalog, valDigital)
                    'Console.WriteLine("Write: " + aoSubDevice.subdevIndex.ToString + " ->" + valAnalog.ToString)
                End If
            End If
            If (meError <> meIDS.ME_ERRNO_SUCCESS) Then
                'displayErrorMessage("meIOSingle - Error: ", meError)
            End If
        Else
            'displayErrorMessage("meUtilityPhysicalToDigital - Error: ", meError)
        End If
        'End SyncLock
    End Sub
    Private Function ConvertPhysicalToDigital(ByVal aoSubDevice As AoSubdevice, ByVal aoRange As AnalogRange, ByVal valAnalog As Double, ByRef valDigital As Integer) As Integer
        Dim meError As Integer = meIDS.meUtilityPhysicalToDigital(aoRange.physicalMin,
                                                aoRange.physicalMax,
                                                aoRange.digitalMax,
                                                valAnalog,
                                                valDigital)
        Return meError
    End Function
    Private Function ConfigureSubdeviceForOutput(ByVal aoSubDevice As AoSubdevice) As Integer
        Dim meError As Integer = meIDS.meIOSingleConfig(aoSubDevice.deviceIndex,
                                      aoSubDevice.subdevIndex,
                                      0,
                                      0,
                                      meIDS.ME_REF_AO_GROUND,
                                      meIDS.ME_TRIG_CHAN_DEFAULT,
                                      meIDS.ME_TRIG_TYPE_SW,
                                      meIDS.ME_VALUE_NOT_USED,
                                      meIDS.ME_IO_SINGLE_CONFIG_NO_FLAGS)
        Return meError
    End Function
    Private Function ConfigureDSubdeviceForOutput(ByVal doSubDevice As DoSubdevice, ByVal channel As Integer) As Integer
        Dim meError As Integer = meIDS.meIOSingleConfig(doSubDevice.deviceIndex,
                                      doSubDevice.subdevIndex,
                                      channel,
                                      meIDS.ME_SINGLE_CONFIG_DIO_OUTPUT,
                                      meIDS.ME_REF_NONE,
                                      meIDS.ME_TRIG_CHAN_DEFAULT,
                                      meIDS.ME_TRIG_TYPE_SW,
                                      meIDS.ME_VALUE_NOT_USED,
                                      meIDS.ME_IO_SINGLE_CONFIG_NO_FLAGS)
        Return meError
    End Function
    Private Function ConfigureDiSubdeviceForOutput(ByVal diSubDevice As DiSubdevice, ByVal channel As Integer) As Integer
        Dim meError As Integer = meIDS.meIOSingleConfig(diSubDevice.deviceIndex,
                                      diSubDevice.subdevIndex,
                                      channel,
                                      meIDS.ME_SINGLE_CONFIG_DIO_INPUT,
                                      meIDS.ME_REF_NONE,
                                      meIDS.ME_TRIG_CHAN_DEFAULT,
                                      meIDS.ME_TRIG_TYPE_SW,
                                      meIDS.ME_VALUE_NOT_USED,
                                      meIDS.ME_IO_SINGLE_CONFIG_NO_FLAGS)
        'Console.WriteLine("Error-Cofnig: " + meError.ToString)
        Return meError
    End Function
    Private Function WriteSingleValue(ByVal aoSubDevice As AoSubdevice, ByVal valDigital As Integer) As Integer
        Dim io_single(1) As meIDS.meIOSingle_t

        io_single(0).iDevice = aoSubDevice.deviceIndex
        io_single(0).iSubdevice = aoSubDevice.subdevIndex
        io_single(0).iChannel = 0 'coBoxChannel.SelectedIndex
        io_single(0).iDir = meIDS.ME_DIR_OUTPUT
        io_single(0).iValue = valDigital
        io_single(0).iTimeOut = 0
        io_single(0).iFlags = meIDS.ME_IO_SINGLE_TYPE_NO_FLAGS
        io_single(0).iErrno = 0

        Dim meError As Integer = meIDS.meIOSingle(io_single(0),
                                   1,
                                   meIDS.ME_IO_SINGLE_NO_FLAGS)
        Return meError
    End Function
    Private Function WriteDigitalValue(ByVal doSubDevice As DoSubdevice, ByVal valDigital As Integer, ByVal channel As Integer) As Integer
        ConfigureDSubdeviceForOutput(doSubDevice, channel)
        Dim io_single(1) As meIDS.meIOSingle_t

        io_single(0).iDevice = doSubDevice.deviceIndex
        io_single(0).iSubdevice = doSubDevice.subdevIndex
        io_single(0).iChannel = channel
        io_single(0).iDir = meIDS.ME_DIR_OUTPUT
        io_single(0).iValue = valDigital
        io_single(0).iTimeOut = 0
        io_single(0).iFlags = meIDS.ME_IO_SINGLE_TYPE_DIO_BIT
        io_single(0).iErrno = 0

        Dim meError As Integer = meIDS.meIOSingle(io_single(0),
                                   1,
                                   meIDS.ME_IO_SINGLE_NO_FLAGS)
        Return meError
    End Function
    Private Function GetDigitalValue(ByVal diSubDevice As DiSubdevice, ByVal channel As Integer) As Integer
        ConfigureDiSubdeviceForOutput(diSubDevice, channel)
        Dim io_single(1) As meIDS.meIOSingle_t

        io_single(0).iDevice = diSubDevice.deviceIndex
        io_single(0).iSubdevice = diSubDevice.subdevIndex
        io_single(0).iChannel = channel
        io_single(0).iDir = meIDS.ME_DIR_INPUT
        io_single(0).iValue = 0
        io_single(0).iTimeOut = 0
        io_single(0).iFlags = meIDS.ME_IO_SINGLE_TYPE_DIO_BIT
        io_single(0).iErrno = 0

        Dim meError As Integer = meIDS.meIOSingle(io_single(0),
                                   1,
                                   meIDS.ME_IO_SINGLE_NO_FLAGS)
        'Console.WriteLine(io_single(0).iValue)
        Return io_single(0).iValue
    End Function
    Private Function GetDevicePlugged(ByVal idxDevice As Integer, ByRef plugged As Integer) As Integer

        Dim meError As Integer
        Dim vendorId As Integer
        Dim deviceId As Integer
        Dim serialNo As Integer
        Dim busType As Integer
        Dim busNo As Integer
        Dim devNo As Integer
        Dim funcNo As Integer

        meError = meIDS.meQueryInfoDevice(idxDevice, _
                                    vendorId, _
                                    deviceId, _
                                    serialNo, _
                                    busType, _
                                    busNo, _
                                    devNo, _
                                    funcNo, _
                                    plugged)
        Return meError
    End Function
#End Region

End Class

Public Class DoSubdevice
    Public deviceName As String
    Public deviceIndex As Integer
    Public subdevIndex As Integer
    Public numOfChannels As Integer

    Sub New(DevName As String, DeviceIdx As Integer, SubdevIdx As Integer, NumChannels As Integer)
        deviceName = DevName
        deviceIndex = DeviceIdx
        subdevIndex = SubdevIdx
        numOfChannels = NumChannels
    End Sub
End Class

Public Class DiSubdevice
    Public deviceName As String
    Public deviceIndex As Integer
    Public subdevIndex As Integer
    Public numOfChannels As Integer

    Sub New(ByVal DevName As String, ByVal DeviceIdx As Integer, ByVal SubdevIdx As Integer, ByVal NumChannels As Integer)
        deviceName = DevName
        deviceIndex = DeviceIdx
        subdevIndex = SubdevIdx
        numOfChannels = NumChannels
    End Sub
End Class

Public Class AoSubdevice
    Public deviceName As String
    Public deviceIndex As Integer
    Public subdevIndex As Integer
    Public numOfChannels As Integer
    Private analogRanges As New List(Of AnalogRange)

    Sub New(DevName As String, DeviceIdx As Integer, SubdevIdx As Integer, NumChannels As Integer)
        deviceName = DevName
        deviceIndex = DeviceIdx
        subdevIndex = SubdevIdx
        numOfChannels = NumChannels
    End Sub

    Public Sub AddRange(RangeUnit As Integer, DigitalMax As Integer, PhysicalMin As Double, PhysicalMax As Double)
        Dim aoRange As AnalogRange = New AnalogRange(RangeUnit, DigitalMax, PhysicalMin, PhysicalMax)
        analogRanges.Add(aoRange)
    End Sub

    Public Function GetRange(index As Integer) As AnalogRange
        Return analogRanges(index)
    End Function

    Public Function GetRangeCount() As Integer
        Return analogRanges.Count()
    End Function
End Class

Public Class AnalogRange
    Public rangeUnit As Integer
    Public digitalMax As Integer
    Public physicalMin As Double
    Public physicalMax As Double
    Public displayRange As String
    Public displayUnit As String

    Sub New(Unit As Integer, DigitMax As Integer, PhysMin As Double, PhysMax As Double)
        rangeUnit = Unit
        digitalMax = DigitMax
        physicalMin = PhysMin
        physicalMax = PhysMax
        SetRangeUnitTexts()
    End Sub

    Private Sub SetRangeUnitTexts()
        Dim sbRange As New StringBuilder
        Dim tmp As String = ""
        Dim tmpValMin As Double = Math.Abs(physicalMin)
        Dim tmpValMax As Double = Math.Abs(physicalMax)

        If (rangeUnit = meIDS.ME_UNIT_VOLT) Then
            displayUnit = "Volt"
            tmp = "V"
        ElseIf (rangeUnit = meIDS.ME_UNIT_AMPERE) Then
            displayUnit = "Ampere"
            tmp = "A"
        End If

        If (tmpValMin = 0) Then
            sbRange.Append("0")
        ElseIf (tmpValMin < 0.001) Then
            sbRange.Append(String.Format("{0:0.00}", physicalMin * 1000000))
            sbRange.Append("µ")
        ElseIf (tmpValMin < 1) Then
            sbRange.Append(String.Format("{0:0.00}", physicalMin * 1000))
            sbRange.Append("m")
        Else
            sbRange.Append(String.Format("{0:0.00}", Math.Round(physicalMin, 2)))
        End If
        sbRange.Append(tmp)

        If (tmpValMax = 0) Then
            sbRange.Append("...0")
        ElseIf (tmpValMax < 0.001) Then
            sbRange.Append(String.Format("...{0:0.00}", physicalMax * 1000000))
            sbRange.Append("µ")
        ElseIf (tmpValMax < 1) Then
            sbRange.Append(String.Format("...{0:0.00}", physicalMax * 1000))
            sbRange.Append("m")
        Else
            sbRange.Append(String.Format("...{0:0.00}", Math.Round(physicalMax, 2)))
        End If
        sbRange.Append(tmp)

        displayRange = sbRange.ToString()
    End Sub
End Class

Class Constants
    Public Shared ReadOnly ME_IDS_NOTOPENED As Integer = -1
End Class