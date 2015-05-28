'==============================================================================
'Copyright(c), Meilhaus Electronic GmbH
'              http://www.meilhaus.de
'              support@meilhaus.de
'
'Source File : FormMain.vb
'Description : Example program for writing single values to AO devices
'              - Open ME-iDS main driver when program is started
'              - Go through the list of all devices and find AO subdevices
'              - Find AO subdevices and information about channels and ranges
'              - Add AO subdevices to the combobox, so the user can select one
'              - Write data to selected subdevice when user clicks on button "Write Data"
'              - Close main driver when program is closed
'==============================================================================
Imports System.Text  'for using StringBuilder
Imports System.Threading

Public Class frmMain
    Private openErrSuccess As Integer = Constants.ME_IDS_NOTOPENED
    Private lineNumber As Integer
    Private subdeviceList As New List(Of AoSubdevice)
    Private t1 As Thread
    Private t2 As Thread
    Private aoSubDev_t1 As AoSubdevice
    Private aoRange_t1 As AnalogRange
    Private aoSubDev_t2 As AoSubdevice
    Private aoRange_t2 As AnalogRange

    Private Sub Test(cnt As Integer)
        If (coBoxSubDevs.SelectedIndex >= 0 And coBoxSubDevs.SelectedIndex < 3) Then
            aoSubDev_t1 = subdeviceList(0)
            aoRange_t1 = aoSubDev_t1.GetRange(coBoxRange.SelectedIndex)
            aoSubDev_t2 = subdeviceList(1)
            aoRange_t2 = aoSubDev_t2.GetRange(coBoxRange.SelectedIndex)
            t1 = New Thread(AddressOf ThreadTask)
            t2 = New Thread(AddressOf ThreadTask2)
            t1.IsBackground = True
            t2.IsBackground = True
            If (cnt = 1) Then
                Console.WriteLine("Start 1 Thread")
                t1.Start()
            ElseIf (cnt = 2) Then
                Console.WriteLine("Start 2 Threads")
                't1.Start()
                't2.Start()
                Dim aoSubDev As AoSubdevice = subdeviceList(coBoxSubDevs.SelectedIndex)
                Dim aoRange As AnalogRange = aoSubDev.GetRange(0)
                WriteToSubdevice(aoSubDev, aoRange, 7.5)

                meIDS.meIOStreamWrite(1, 10, meIDS.ME_WRITE_MODE_NONBLOCKING, 1, 10000000, meIDS.ME_IO_STREAM_WRITE_NO_FLAGS)

            End If
        End If
    End Sub
    Private Sub ThreadTask()
        'Dim aoSubDev As AoSubdevice = subdeviceList(coBoxSubDevs.SelectedIndex)
        'Dim aoRange As AnalogRange = aoSubDev.GetRange(coBoxRange.SelectedIndex)
        Dim volt As Integer
        Dim wait As Integer
        Dim wait_b As Integer
        Dim wait_a As Integer

        Dim cnt As Integer
        Dim max As Integer
        cnt = 800 / 4
        max = 0

        wait_b = 35000000
        wait_a = 0

        wait = 1
        volt = 5
        WriteSingleValue(aoSubDev_t2, volt)
        WriteSingleValue(aoSubDev_t1, volt)
        Do
            max += 1
            'WriteToSubdevice(aoSubDev_t1, aoRange_t1, 10) 'trackbarVal.Value)
            'ConvertPhysicalToDigital(aoSubDev_t1, aoRange_t1, 5, 5)
            WriteSingleValue(aoSubDev_t1, -volt)
            'Console.WriteLine("Thread1-A1: +5")
            'Thread.Sleep(wait)
            Do
                wait_a += 1
            Loop Until wait_a >= wait_b
            wait_a = 0
            'ConvertPhysicalToDigital(aoSubDev_t1, aoRange_t1, -5, 5)
            WriteSingleValue(aoSubDev_t2, -volt)
            'Console.WriteLine("Thread1-A2: -5")
            'Thread.Sleep(wait)
            Do
                wait_a += 1
            Loop Until wait_a >= wait_b
            wait_a = 0
            WriteSingleValue(aoSubDev_t1, volt)
            'Console.WriteLine("Thread1-A1: +5")
            'Thread.Sleep(wait)
            Do
                wait_a += 1
            Loop Until wait_a >= wait_b
            wait_a = 0
            WriteSingleValue(aoSubDev_t2, volt)
            'Console.WriteLine("Thread1-A2: -5")
            'Thread.Sleep(wait)
            Do
                wait_a += 1
            Loop Until wait_a >= wait_b
            wait_a = 0
            'WriteToSubdevice(aoSubDev_t1, aoRange_t1, -10) 'trackbarVal.Value * -1)
        Loop Until max = cnt
    End Sub
    Private Sub ThreadTask2()
        'Dim aoSubDev As AoSubdevice = subdeviceList(coBoxSubDevs.SelectedIndex)
        'Dim aoRange As AnalogRange = aoSubDev.GetRange(coBoxRange.SelectedIndex)
        Dim volt As Integer
        Dim wait As Integer
        wait = 1
        volt = 1
        WriteSingleValue(aoSubDev_t2, volt)
        WriteSingleValue(aoSubDev_t1, volt)
        Do
            'WriteToSubdevice(aoSubDev_t1, aoRange_t1, 10) 'trackbarVal.Value)
            'ConvertPhysicalToDigital(aoSubDev_t1, aoRange_t1, 5, 5)
            WriteSingleValue(aoSubDev_t1, -volt)
            'Console.WriteLine("Thread1-A1: +5")
            Thread.Sleep(wait)
            'ConvertPhysicalToDigital(aoSubDev_t1, aoRange_t1, -5, 5)
            WriteSingleValue(aoSubDev_t2, -volt)
            'Console.WriteLine("Thread1-A2: -5")
            Thread.Sleep(wait)
            WriteSingleValue(aoSubDev_t1, volt)
            'Console.WriteLine("Thread1-A1: +5")
            Thread.Sleep(wait)
            WriteSingleValue(aoSubDev_t2, volt)
            'Console.WriteLine("Thread1-A2: -5")
            Thread.Sleep(wait)
            'WriteToSubdevice(aoSubDev_t1, aoRange_t1, -10) 'trackbarVal.Value * -1)
        Loop
    End Sub

    Private Sub frmMain_Shown(sender As System.Object, e As System.EventArgs) Handles MyBase.Shown
        OpenMEiDSDriver()
    End Sub

    Private Sub frmMain_FormClosing(sender As System.Object, e As System.Windows.Forms.FormClosingEventArgs) Handles MyBase.FormClosing
        CloseMEiDSDriver()
    End Sub

    Private Sub btnClose_Click(sender As System.Object, e As System.EventArgs) Handles btnClose.Click
        Close()
    End Sub

    Private Sub OpenMEiDSDriver()
        Try
            textBoxInfo.AppendText("Opening Maindriver..." & Environment.NewLine)
            openErrSuccess = meIDS.meOpen(meIDS.ME_OPEN_NO_FLAGS)

            If openErrSuccess = meIDS.ME_ERRNO_SUCCESS Then
                DisplayVersionLibrary()
                DisplayVersionMainDriver()

                textBoxInfo.AppendText(Environment.NewLine)

                Dim numDevices As Integer
                meIDS.meQueryNumberDevices(numDevices)
                textBoxInfo.AppendText("Number of devices found: " & numDevices.ToString() & Environment.NewLine)
                GetAoSubdevices(numDevices)
            Else
                displayErrorMessage("meOpen - Error: ", openErrSuccess)
            End If
        Catch ex As DllNotFoundException
            textBoxInfo.AppendText("The ME-iDS is not properly installed." & Environment.NewLine)
            textBoxInfo.AppendText(ex.Message & Environment.NewLine)
        End Try
    End Sub

    Private Sub GetAoSubdevices(numDevices As Integer)
        Dim idxDevice As Integer

        If openErrSuccess = meIDS.ME_ERRNO_SUCCESS AndAlso numDevices > 0 Then
            textBoxInfo.AppendText("Retrieving subdevices of type ME_TYPE_AO (Analog output)..." & Environment.NewLine)
            subdeviceList.Clear()
            coBoxSubDevs.Items.Clear()
            For idxDevice = 0 To numDevices - 1
                Dim meError As Integer
                Dim plugged As Integer

                meError = GetDevicePlugged(idxDevice, plugged)
                If meError = meIDS.ME_ERRNO_SUCCESS AndAlso plugged = meIDS.ME_PLUGGED_IN Then
                    GetSubdevicesByType(idxDevice, meIDS.ME_TYPE_AO)
                Else
                    textBoxInfo.AppendText("Device " & idxDevice.ToString() & " not plugged in" & Environment.NewLine)
                End If
            Next

        End If
        DisplaySubdevices()
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

            coBoxSubDevs.Items.Add(deviceName.ToString _
                                   & ",  Device " & idxDevice.ToString() _
                                   & ",  Subdevice " & idxSubdevice.ToString() _
                                   & ",  Type: " & GetSubDevTypeName(subdeviceType) _
                                   & ",  Channels: " & numOfChannels.ToString() _
                                   & ",  Ranges: " & aoSubdev.GetRangeCount().ToString())
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
    Private Sub coBoxSubDevs_SelectedIndexChanged(sender As System.Object, e As System.EventArgs) Handles coBoxSubDevs.SelectedIndexChanged
        FillSubdeviceProperties(coBoxSubDevs.SelectedIndex)
    End Sub

    Private Sub FillSubdeviceProperties(idxSelectedSubdev As Integer)
        If idxSelectedSubdev >= 0 Then
            Dim aoSubdev As AoSubdevice = subdeviceList(idxSelectedSubdev)
            FillSubdeviceChannels(aoSubdev)
            FillSubdeviceRanges(aoSubdev)
            InitTrackbarPosition(coBoxRange.SelectedIndex)
        End If
    End Sub

    Private Sub FillSubdeviceChannels(aoSubdev As AoSubdevice)
        Dim i As Integer

        coBoxChannel.Items.Clear()
        For i = 0 To aoSubdev.numOfChannels - 1
            coBoxChannel.Items.Add("Channel " & i.ToString())
        Next
        coBoxChannel.SelectedIndex = 0
    End Sub

    Private Sub FillSubdeviceRanges(aoSubdev As AoSubdevice)
        Dim aiRange As AnalogRange
        Dim i As Integer

        coBoxRange.Items.Clear()
        For i = 0 To aoSubdev.GetRangeCount() - 1
            aiRange = aoSubdev.GetRange(i)
            coBoxRange.Items.Add("Range " & i.ToString() & ": " & aiRange.displayRange)
        Next
        coBoxRange.SelectedIndex = 0
    End Sub

    Private Sub coBoxRange_SelectedIndexChanged(sender As System.Object, e As System.EventArgs) Handles coBoxRange.SelectedIndexChanged
        InitTrackbarPosition(coBoxRange.SelectedIndex)
    End Sub

    Private Sub InitTrackbarPosition(idxSelectedRange As Integer)
        If (idxSelectedRange >= 0) Then
            Dim aoSubdev As AoSubdevice = subdeviceList(coBoxSubDevs.SelectedIndex)
            Dim aoRange As AnalogRange = aoSubdev.GetRange(idxSelectedRange)

            trackbarVal.SetRange(0, aoRange.digitalMax)
            SetTrackPosition(0, aoRange)
            trackbarVal.TickFrequency = trackbarVal.Maximum / 20

            txtBoxPhysValue.Text = "0"
        End If
    End Sub

    Private Sub txtBoxPhysValue_KeyDown(sender As System.Object, e As System.Windows.Forms.KeyEventArgs) Handles txtBoxPhysValue.KeyDown
        If ((e.KeyCode = Keys.Return) AndAlso (coBoxSubDevs.Items.Count > 0)) Then
            Dim valAnalog As Double
            Dim aoSubDev As AoSubdevice = subdeviceList(coBoxSubDevs.SelectedIndex)
            Dim aoRange As AnalogRange = aoSubDev.GetRange(coBoxRange.SelectedIndex)

            Try
                valAnalog = CheckValueMinMax(Double.Parse(txtBoxPhysValue.Text), aoRange)
                SetTrackPosition(valAnalog, aoRange)
            Catch ex As Exception
                MessageBox.Show("Error: " + ex.Message)
                txtBoxPhysValue.Focus()
            End Try
        End If
    End Sub

    Private Sub SetTrackPosition(valAnalog As Double, aoRange As AnalogRange)
        Dim trckVal As Integer
        trckVal = ((valAnalog - aoRange.physicalMin) * aoRange.digitalMax / (aoRange.physicalMax - aoRange.physicalMin))
        trackbarVal.Value = trckVal
    End Sub

    Private Function CheckValueMinMax(valAnalog As Double, aoRange As AnalogRange) As Double
        If (valAnalog < aoRange.physicalMin) Then
            valAnalog = aoRange.physicalMin
            txtBoxPhysValue.Text = String.Format("{0:0.000}", valAnalog)
        ElseIf (valAnalog > aoRange.physicalMax) Then
            valAnalog = aoRange.physicalMax
            txtBoxPhysValue.Text = String.Format("{0:0.000}", valAnalog)
        End If
        Return valAnalog
    End Function

    Private Sub trackbarVal_ValueChanged(sender As System.Object, e As System.EventArgs) Handles trackbarVal.ValueChanged
        If (coBoxSubDevs.Items.Count > 0) Then
            Dim valAnalog As Double
            Dim aoSubDev As AoSubdevice = subdeviceList(coBoxSubDevs.SelectedIndex)
            Dim aoRange As AnalogRange = aoSubDev.GetRange(coBoxRange.SelectedIndex)
            Dim physRange As Double = aoRange.physicalMax - aoRange.physicalMin
            valAnalog = aoRange.physicalMin + (physRange / (trackbarVal.Maximum - trackbarVal.Minimum)) * trackbarVal.Value
            txtBoxPhysValue.Text = String.Format("{0:0.000}", valAnalog)
        End If
    End Sub

    Private Sub btnSingleWrite_Click(sender As System.Object, e As System.EventArgs) Handles btnSingleWrite.Click
        If (coBoxSubDevs.SelectedIndex >= 0) Then
            Dim aoSubDev As AoSubdevice = subdeviceList(coBoxSubDevs.SelectedIndex)
            Dim aoRange As AnalogRange = aoSubDev.GetRange(coBoxRange.SelectedIndex)

            Try
                Dim valAnalog As Double
                valAnalog = CheckValueMinMax(Double.Parse(txtBoxPhysValue.Text), aoRange)
                SetTrackPosition(valAnalog, aoRange)
                WriteToSubdevice(aoSubDev, aoRange, valAnalog)
            Catch ex As Exception
                MessageBox.Show("Error: " + ex.Message)
                txtBoxPhysValue.Focus()
            End Try
        End If
    End Sub

    Private Sub WriteToSubdevice(aoSubDevice As AoSubdevice, aoRange As AnalogRange, valAnalog As Double)

        Dim meError As Integer
        Dim valDigital As Integer
        meError = ConvertPhysicalToDigital(aoSubDevice, aoRange, valAnalog, valDigital)

        If (meError = meIDS.ME_ERRNO_SUCCESS) Then

            meError = ConfigureSubdeviceForOutput(aoSubDevice)
            If (meError = meIDS.ME_ERRNO_SUCCESS) Then
                meError = WriteSingleValue(aoSubDevice, valDigital)
                If (meError = meIDS.ME_ERRNO_SUCCESS) Then
                    DisplayValue(aoSubDevice, coBoxChannel.SelectedIndex, valAnalog, valDigital)
                End If
            End If
            If (meError <> meIDS.ME_ERRNO_SUCCESS) Then
                displayErrorMessage("meIOSingle - Error: ", meError)
            End If
        Else
            displayErrorMessage("meUtilityPhysicalToDigital - Error: ", meError)
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

    Private Function ConfigureSubdeviceForOutput(aoSubDevice As AoSubdevice) As Integer
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

    Private Sub DisplayValue(aoSubDevice As AoSubdevice, idxRange As Integer, valAnalog As Double, valDigital As Integer)
        lineNumber = lineNumber + 1
        textBoxInfo.AppendText(String.Format("{0:00}", lineNumber) _
                    & " Write to " & aoSubDevice.deviceName _
                    & ",  Device: " & aoSubDevice.deviceIndex.ToString() _
                    & ",  Subdevice: " & aoSubDevice.subdevIndex.ToString() _
                    & ",  Digital value: " & valDigital.ToString() _
                    & ",  Physical value: " & String.Format("{0:0.000}", valAnalog) _
                    & " " & aoSubDevice.GetRange(idxRange).displayUnit _
                    & Environment.NewLine)
    End Sub
    Private Sub btnResetSubdev_Click(sender As System.Object, e As System.EventArgs) Handles btnResetSubdev.Click
        Dim aoSubdev As AoSubdevice
        Dim meError As Integer
        aoSubdev = subdeviceList(coBoxSubDevs.SelectedIndex)

        meError = meIDS.meIOResetSubdevice(aoSubdev.deviceIndex, _
                                     aoSubdev.subdevIndex, _
                                     meIDS.ME_IO_RESET_SUBDEVICE_NO_FLAGS)
        If meError = meIDS.ME_ERRNO_SUCCESS Then
            textBoxInfo.AppendText("Reset Device " & aoSubdev.deviceIndex.ToString() & ", Subdevice " & aoSubdev.subdevIndex.ToString() & Environment.NewLine)
        Else
            displayErrorMessage("Error resetting Subdevice ", meError)
        End If
    End Sub

    Private Sub CloseMEiDSDriver()
        If openErrSuccess = meIDS.ME_ERRNO_SUCCESS Then
            meIDS.meClose(meIDS.ME_CLOSE_NO_FLAGS)
            openErrSuccess = Constants.ME_IDS_NOTOPENED
            btnSingleWrite.Enabled = False
            btnResetSubdev.Enabled = False
            subdeviceList.Clear()
            coBoxSubDevs.Items.Clear()
            coBoxChannel.Items.Clear()
            coBoxRange.Items.Clear()
        End If
    End Sub

    Private Sub DisplaySubdevices()
        If coBoxSubDevs.Items.Count > 0 Then
            textBoxInfo.AppendText("Number of analog output subdevices found: " & coBoxSubDevs.Items.Count.ToString() & Environment.NewLine)
            Dim i As Integer
            For i = 0 To coBoxSubDevs.Items.Count - 1
                textBoxInfo.AppendText(coBoxSubDevs.Items(i) & Environment.NewLine)
            Next
            textBoxInfo.AppendText(Environment.NewLine)
            coBoxSubDevs.SelectedIndex = 0
            btnSingleWrite.Enabled = True
            btnResetSubdev.Enabled = True
        Else
            textBoxInfo.AppendText("No analog output subdevices found in system." & Environment.NewLine)
            CloseMEiDSDriver()
        End If
    End Sub

    Private Function GetDevicePlugged(idxDevice As Integer, ByRef plugged As Integer) As Integer

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

    Private Function GetSubDevTypeName(subdeviceType As Integer)
        Dim tmpType As String
        Select Case subdeviceType
            Case meIDS.ME_TYPE_INVALID
                tmpType = "ME_TYPE_INVALID"
            Case meIDS.ME_TYPE_AI
                tmpType = "ME_TYPE_AI"
            Case meIDS.ME_TYPE_AO
                tmpType = "ME_TYPE_AO"
            Case meIDS.ME_TYPE_DIO
                tmpType = "ME_TYPE_DIO"
            Case meIDS.ME_TYPE_DO
                tmpType = "ME_TYPE_DO"
            Case meIDS.ME_TYPE_DI
                tmpType = "ME_TYPE_DI"
            Case meIDS.ME_TYPE_CTR
                tmpType = "ME_TYPE_CTR"
            Case meIDS.ME_TYPE_EXT_IRQ
                tmpType = "ME_TYPE_EXT_IRQ"
            Case meIDS.ME_TYPE_FIO
                tmpType = "ME_TYPE_FIO"
            Case meIDS.ME_TYPE_FO
                tmpType = "ME_TYPE_FO"
            Case meIDS.ME_TYPE_FI
                tmpType = "ME_TYPE_FI"
            Case meIDS.ME_TYPE_FPGA
                tmpType = "ME_TYPE_FPGA"
            Case Else
                tmpType = String.Format("&H{0:X}", subdeviceType)
        End Select
        Return tmpType
    End Function

    Private Sub DisplayVersionLibrary()
        Dim tmpVersion As Integer
        meIDS.meQueryVersionLibrary(tmpVersion)
        textBoxInfo.AppendText("Library version: " & MeVersionToString(tmpVersion) & Environment.NewLine)
    End Sub

    Private Sub DisplayVersionMainDriver()
        Dim tmpVersion As Integer
        meIDS.meQueryVersionMainDriver(tmpVersion)
        textBoxInfo.AppendText("Maindriver version: " & MeVersionToString(tmpVersion) & Environment.NewLine)
    End Sub

    Private Function MeVersionToString(version As Integer) As String
        Return String.Format("{0}.{1}.{2}.{3}", version >> 24, &HFF And (version >> 16), &HFF And (version >> 8), &HFF And version)
    End Function

    Private Sub displayErrorMessage(message As String, meError As Integer)
        Dim errMessage = New StringBuilder(vbNullChar, meIDS.ME_ERROR_MSG_MAX_COUNT)
        textBoxInfo.AppendText(message & meError.ToString() & Environment.NewLine)
        meIDS.meErrorGetMessage(meError, errMessage, meIDS.ME_ERROR_MSG_MAX_COUNT)
        textBoxInfo.AppendText("ErrorMessage: " & errMessage.ToString & Environment.NewLine)
    End Sub

    Private Sub btnClearHwInfo_Click(sender As System.Object, e As System.EventArgs) Handles btnClearHwInfo.Click
        textBoxInfo.Clear()
        lineNumber = 0
    End Sub

    Private Sub btnAbout_Click(sender As System.Object, e As System.EventArgs) Handles btnAbout.Click
        AboutBox1.ShowDialog()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        If CheckBox1.Checked Then
            Test(2)
        Else
            Test(1)
        End If
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