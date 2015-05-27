Imports System.Threading
Imports System.Text

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
        OpenMEiDSDriver()
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
#End Region

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
            WriteSingleValue(subdeviceList(0), xMotor.Item(cur_x)(0)) 'ausgang 1 motorx
            WriteSingleValue(subdeviceList(1), xMotor.Item(cur_x)(1)) 'ausgang 2 motorx

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
            WriteSingleValue(subdeviceList(2), xMotor.Item(cur_y)(0)) 'ausgang 3 motorx
            WriteSingleValue(subdeviceList(3), xMotor.Item(cur_y)(1)) 'ausgang 4 motorx

            cur_y += dir
            cur_y = cur_y Mod yMotor.Count
        Loop
    End Sub

#Region "Waiting"
    'waits...
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
#End Region

#Region "MEiDSFunctions"
    'Hardware
    Private openErrSuccess As Integer = Constants.ME_IDS_NOTOPENED
    Private lineNumber As Integer
    Private subdeviceList As New List(Of AoSubdevice)
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
    Private Sub GetAoSubdevices(numDevices As Integer)
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
                Else
                    'textBoxInfo.AppendText("Device " & idxDevice.ToString() & " not plugged in" & Environment.NewLine)
                End If
            Next

        End If
        'DisplaySubdevices()
    End Sub
    Private Sub GetSubdevicesByType(idxDevice As Integer, subdeviceType As Integer)
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

                If meError = meIDS.ME_ERRNO_SUCCESS Then
                    meError = AddAoSubdevice(deviceName.ToString(), idxDevice, idxMatchedSubdevice, subdeviceType)
                    idxSubdevice = idxMatchedSubdevice + 1
                Else
                    Exit While
                End If
            End While
        End If
    End Sub
    Private Function AddAoSubdevice(deviceName As String, ByVal idxDevice As Integer, ByVal idxSubdevice As Integer, ByVal subdeviceType As Integer) As Integer
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
    Private Sub AddAnalogRanges(aoSubdev As AoSubdevice)
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
    Private Sub AddAnalogRange(aoSubdev As AoSubdevice, idxRange As Integer)
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

    Private Sub WriteToSubdevice(aoSubDevice As AoSubdevice, aoRange As AnalogRange, valAnalog As Double)

        Dim meError As Integer
        Dim valDigital As Integer
        meError = ConvertPhysicalToDigital(aoSubDevice, aoRange, valAnalog, valDigital)

        If (meError = meIDS.ME_ERRNO_SUCCESS) Then

            meError = 1 'ConfigureSubdeviceForOutput(aoSubDevice)
            If (meError = meIDS.ME_ERRNO_SUCCESS) Then
                meError = WriteSingleValue(aoSubDevice, valDigital)
                If (meError = meIDS.ME_ERRNO_SUCCESS) Then
                    'DisplayValue(aoSubDevice, coBoxChannel.SelectedIndex, valAnalog, valDigital)
                End If
            End If
            If (meError <> meIDS.ME_ERRNO_SUCCESS) Then
                'displayErrorMessage("meIOSingle - Error: ", meError)
            End If
        Else
            'displayErrorMessage("meUtilityPhysicalToDigital - Error: ", meError)
        End If
    End Sub
    Private Function ConvertPhysicalToDigital(aoSubDevice As AoSubdevice, aoRange As AnalogRange, valAnalog As Double, ByRef valDigital As Integer) As Integer
        Dim meError As Integer = meIDS.meUtilityPhysicalToDigital(aoRange.physicalMin,
                                                aoRange.physicalMax,
                                                aoRange.digitalMax,
                                                valAnalog,
                                                valDigital)
        Return meError
    End Function
    'Private Function ConfigureSubdeviceForOutput(aoSubDevice As AoSubdevice) As Integer
    '  Dim meError As Integer = meIDS.meIOSingleConfig(AoSubdevice.deviceIndex,
    '                                AoSubdevice.subdevIndex,
    '                                coBoxChannel.SelectedIndex,
    '                                coBoxRange.SelectedIndex,
    '                                meIDS.ME_REF_AO_GROUND,
    '                                meIDS.ME_TRIG_CHAN_DEFAULT,
    '                                meIDS.ME_TRIG_TYPE_SW,
    '                                meIDS.ME_VALUE_NOT_USED,
    '                                meIDS.ME_IO_SINGLE_CONFIG_NO_FLAGS)
    '  Return meError
    'End Function
    Private Function WriteSingleValue(aoSubDevice As AoSubdevice, valDigital As Integer) As Integer
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
#End Region

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