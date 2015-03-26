VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   2556
   ClientLeft      =   48
   ClientTop       =   276
   ClientWidth     =   3744
   LinkTopic       =   "Form1"
   ScaleHeight     =   2556
   ScaleWidth      =   3744
   StartUpPosition =   3  'Windows Default
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
    Const AppName = "sample"
    
    Dim sTextBuffer As String * 256
    Dim lMEVECModel As Long
    Dim lBoardNumber As Long
    Dim lSerialNumber As Long
    Dim Interrupts As ME3000_ISR
    Dim BoardInfo As ME3000_BOARD_INFO
    Dim BoardData As ME_PLX9050_INFO
    Dim DriverStatus As ME3000_DRIVER_STATUS
    Dim dValue As Double
    Dim iSingleValue As Integer
    Dim iValue As Integer
    ReDim piADCBuffer(0 To 10) As Integer
    Dim lValueA As Long
    Dim iCounterValue As Integer
    
    
    lBoardNumber = 0&
    
    '-----------------------------------------------------------------------
    '
    ' General Functions
    '
    '-----------------------------------------------------------------------
If 1 Then
    ' Get DLL version
    MsgBox "ME3000 DLL Version: " + Hex(me3000GetDLLVersion()), vbInformation

    ' Get Driver version
    Call me3000GetDriverVersion(sTextBuffer)
    MsgBox "ME3000 Driver Version: " + sTextBuffer, vbInformation

    
    ' Get VEC model
    If me3000GetVECModel(lBoardNumber, lMEVECModel) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        MsgBox "MEVEC Model: " + Str(lMEVECModel), vbInformation
    End If
    
    
    ' Get serial number
    If me3000GetSerialNumber(lBoardNumber, lSerialNumber) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        MsgBox "Serial Number: " + Str(lSerialNumber), vbInformation
    End If
    

    ' Get PCI configuration
    If me3000GetPCIConfiguration(lBoardNumber, BoardData) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        sBigText = Chr(9) + "PCI Configuration Data of Board: " + Str(lBoardNumber) + Chr(9) + Chr(10) + Chr(13) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Vendor ID:" + Chr(9) + Chr(9) + "0x" + Hex(BoardData.VendorID) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Device ID:" + Chr(9) + Chr(9) + "0x" + Hex(BoardData.DeviceID) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Command:" + Chr(9) + "0x" + Hex(BoardData.Command) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Status:" + Chr(9) + Chr(9) + "0x" + Hex(BoardData.Status) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Revision:" + Chr(9) + Chr(9) + "0x" + Hex(BoardData.Revision) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Class:" + Chr(9) + Chr(9) + "0x" + Hex(BoardData.Class(0)) + " " + Hex(BoardData.Class(1)) + " " + Hex(BoardData.Class(2)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "CacheSize:" + Chr(9) + "0x" + Hex(BoardData.CacheSize) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Latency:" + Chr(9) + Chr(9) + "0x" + Hex(BoardData.Latency) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "HeaderType:" + Chr(9) + "0x" + Hex(BoardData.HeaderType) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Bist:" + Chr(9) + Chr(9) + "0x" + Hex(BoardData.Bist) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "RT Regs (memory):" + Chr(9) + "0x" + Hex(BoardData.BaseAddr(0)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "RT Regs (port):" + Chr(9) + "0x" + Hex(BoardData.BaseAddr(1)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "XILINX:" + Chr(9) + Chr(9) + "0x" + Hex(BoardData.BaseAddr(2)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "SIO:" + Chr(9) + Chr(9) + "0x" + Hex(BoardData.BaseAddr(3)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "BaseAddr 4:" + Chr(9) + "0x" + Hex(BoardData.BaseAddr(4)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "BaseAddr 5:" + Chr(9) + "0x" + Hex(BoardData.BaseAddr(5)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "CIS:" + Chr(9) + Chr(9) + "0x" + Hex(BoardData.Cis) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Sub Vendor ID:" + Chr(9) + "0x" + Hex(BoardData.SubVendor) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Sub Device ID:" + Chr(9) + "0x" + Hex(BoardData.SubSystem) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "ROMAddr:" + Chr(9) + Chr(9) + "0x" + Hex(BoardData.ROMAddr) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Reserved 0:" + Chr(9) + "0x" + Hex(BoardData.Reserved(0)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Reserved 1:" + Chr(9) + "0x" + Hex(BoardData.Reserved(1)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "INT:" + Chr(9) + Chr(9) + Trim(Str(BoardData.IRQ)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "IPin:" + Chr(9) + Chr(9) + Trim(Str(BoardData.IPin)) + Chr(10) + Chr(13)
        MsgBox sBigText, vbOKOnly
    End If


    ' Get Driver Status
     If me3000GetDriverStatus(lBoardNumber, DriverStatus) = 0 Then
        Call me3000ErrorMessage(AppName)
     Else
        sBigText = Chr(9) + "Driver status of board: " + Str(lBoardNumber) + Chr(10) + Chr(13) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Control1:" + Chr(9) + Chr(9) + "0x" + Hex(DriverStatus.Control1) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Control2:" + Chr(9) + Chr(9) + "0x" + Hex(DriverStatus.Control2) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Control3:" + Chr(9) + Chr(9) + "0x" + Hex(DriverStatus.Control3) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "IRQMask:" + Chr(9) + Chr(9) + "0x" + Hex(DriverStatus.IRQMask) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "ISRMask:" + Chr(9) + Chr(9) + "0x" + Hex(DriverStatus.ISRMask) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Status:" + Chr(9) + Chr(9) + "0x" + Hex(DriverStatus.Status) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "DACStatus:" + Chr(9) + "0x" + Hex(DriverStatus.DACStatus) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "DebugWord:" + Chr(9) + "0x" + Hex(DriverStatus.DebugWord) + Chr(10) + Chr(13)
        MsgBox sBigText, vbOKOnly
     End If


    ' Get Driver Interrupts
    If me3000GetInterrupts(lBoardNumber, Interrupts) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        sBigText = Chr(9) + "Interrupt counter of board: " + Str(lBoardNumber) + Chr(10) + Chr(13) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "ISR:" + Chr(9) + Chr(9) + Str(Interrupts.ISR) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "ADC FIFO half full:" + Chr(9) + Str(Interrupts.AdcFifo) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Channel List:" + Chr(9) + Str(Interrupts.ChanList) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Extern:" + Chr(9) + Chr(9) + Str(Interrupts.Extern) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Counter A:" + Chr(9) + Chr(9) + Str(Interrupts.CountA) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Counter B:" + Chr(9) + Chr(9) + Str(Interrupts.CountB) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "UART:" + Chr(9) + Chr(9) + Str(Interrupts.UART) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "DAC FIFO half full:" + Chr(9) + Str(Interrupts.DacFifo) + Chr(10) + Chr(13)
        MsgBox sBigText, vbOKOnly
    End If


    ' Get Board Info
        If me3000DLLBoardInfo(lBoardNumber, BoardInfo) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        sBigText = Chr(9) + "Information of Board: " + Chr(9) + Chr(9) + Trim(Str(BoardInfo.DeviceNumber)) + Chr(10) + Chr(13) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "PCI slot number:" + Chr(9) + Chr(9) + Trim(Str(BoardInfo.SlotNumber)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "RT phys. address:" + Chr(9) + Chr(9) + "0x" + Hex(BoardInfo.RTPhysAddr) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "XILINX phys. address:" + Chr(9) + "0x" + Hex(BoardInfo.XilinxPhysAddr) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "SIO phys. address:" + Chr(9) + Chr(9) + "0x" + Hex(BoardInfo.SioPhysAddr) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Boards found:" + Chr(9) + Chr(9) + Trim(Str(BoardInfo.NoOfBoards)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "General Debug Word:" + Chr(9) + "0x" + Hex(BoardInfo.Word) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Firmware File Status:" + Chr(9) + Chr(9) + Trim(Str(BoardInfo.FileStatus)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Firmware File Length:" + Chr(9) + Chr(9) + Trim(Str(BoardInfo.FileLength)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Firmware Version:" + Chr(9) + Chr(9) + "0x" + Hex(BoardInfo.FileVersion) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Firmware Date:" + Chr(9) + Chr(9) + "0x" + Hex(BoardInfo.FileDate) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Size of ADC FIFO:" + Chr(9) + Chr(9) + Trim(Str(BoardInfo.AdcFifo)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Size of DAC FIFO:" + Chr(9) + Chr(9) + Trim(Str(BoardInfo.DacFifo)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Size of Chan. List FIFO:" + Chr(9) + Trim(Str(BoardInfo.ChanListFifo)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "Serial Number:" + Chr(9) + Chr(9) + Trim(Str(BoardInfo.SerialNumber)) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "EEPROM date:" + Chr(9) + Chr(9) + "0x" + Hex(BoardInfo.Date) + Chr(10) + Chr(13)
        sBigText = sBigText + Chr(9) + "MEVEC Model:" + Chr(9) + Chr(9) + Trim(Str(BoardInfo.MEVECModel)) + Chr(10) + Chr(13)
        MsgBox sBigText, vbOKOnly
    End If
End If


If 0 Then
    ' Initialize ME3000
    If me3000Initialize(lBoardNumber) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
End If



    '-----------------------------------------------------------------------
    '
    ' Analog Input Functions
    '
    '-----------------------------------------------------------------------
If 1 Then
    ' me3000AISingle
    If me3000AISingle(lBoardNumber, 0, 0, iSingleValue) = 0 Then
        Call me3000ErrorMessage(AppName)
    Else
        dValue = iSingleValue * 0.00048828125 * 10# - 10#
        MsgBox "ADC " + Trim(Str(0)) + ": " + Str(iSingleValue) + "  " + Str(dValue) + " [V]"
    End If


    ' me3000AIQuick Polling
    If MakeChannelList(lBoardNumber, 10) = 1 Then
        If me3000AISetTimer(lBoardNumber, 0, me3000FrequencyToCounter(5000)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(lBoardNumber, AI3000_TRIGGER_TIMER) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AIQuick(lBoardNumber, piADCBuffer(0), 10, AI3000_POLLING) = 0 Then
            Call me3000ErrorMessage(AppName)
        Else
            sBigText = Chr(9) + "AIQuick.Polling @ Board: " + Chr(9) + Trim(Str(lBoardNumber)) + Chr(10) + Chr(13) + Chr(10) + Chr(13)
            dValue = piADCBuffer(0) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(0))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(1) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(1))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(2) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(2))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(3) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(3))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(4) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(4))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(5) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(5))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(6) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(6))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(7) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(7))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(8) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(8))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(9) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(9))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            MsgBox sBigText, vbOKOnly
        End If
    End If


    ' me3000AIMultiple Interrupt
    If MakeChannelList(lBoardNumber, 1) = 1 Then
        If me3000AISetTimer(lBoardNumber, 0, me3000FrequencyToCounter(5000)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(lBoardNumber, AI3000_TRIGGER_TIMER) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AIMultiple(lBoardNumber, piADCBuffer(0), 10, AI3000_INTERRUPT) = 0 Then
            Call me3000ErrorMessage(AppName)
        Else
            sBigText = Chr(9) + "AIMultiple.Interrupt @ Board: " + Chr(9) + Trim(Str(lBoardNumber)) + Chr(10) + Chr(13) + Chr(10) + Chr(13)
            dValue = piADCBuffer(0) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(0))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(1) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(1))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(2) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(2))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(3) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(3))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(4) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(4))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(5) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(5))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(6) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(6))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(7) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(7))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(8) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(8))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(9) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(9))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            MsgBox sBigText, vbOKOnly
        End If
    End If


    ' me3000AIScan Interrupt
    If MakeChannelList(glBoardNumber, 10) = 1 Then
        If me3000AISetTimer(lBoardNumber, 0, me3000FrequencyToCounter(5000)) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AISetTrigger(lBoardNumber, AI3000_TRIGGER_TIMER) = 0 Then
            Call me3000ErrorMessage(AppName)
        End If
        If me3000AIScan(lBoardNumber, piADCBuffer(0), 10, 1, AI3000_INTERRUPT) = 0 Then
            Call me3000ErrorMessage(AppName)
        Else
            sBigText = Chr(9) + "AIScan.Interrupt @ Board: " + Chr(9) + Trim(Str(lBoardNumber)) + Chr(10) + Chr(13) + Chr(10) + Chr(13)
            dValue = piADCBuffer(0) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(0))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(1) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(1))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(2) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(2))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(3) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(3))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(4) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(4))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(5) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(5))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(6) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(6))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(7) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(7))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(8) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(8))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            dValue = piADCBuffer(9) * 0.00048828125 * 10# - 10#
            sBigText = sBigText + Chr(9) + Trim(Str(piADCBuffer(9))) + Chr(9) + Trim(Str(dValue)) + Chr(10) + Chr(13)
            MsgBox sBigText, vbOKOnly
        End If
    End If
End If


    '-----------------------------------------------------------------------
    '
    ' Analog Output Functions
    '
    '-----------------------------------------------------------------------
If 1 Then

    ' me3000AOSingle
    If me3000AOSetMode(lBoardNumber, 0, AO3000_MINUS_10, AO3000_TRANSPARENT) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
    If me3000AOSingle(glBoardNumber, glDACChannel, 4095) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If

    ' WrapAround
    Call DACWrapAround
    MsgBox "Stop WrapAround now!"
    Call me3000AOStop(lBoardNumber)
    

    ' Continuous Polling Mode
    MsgBox "Start DACContinuous now!"
    Call DACContinuousPolling
End If
    
    
    '-----------------------------------------------------------------------
    '
    ' Digital I/O Functions
    '
    '-----------------------------------------------------------------------
If 1 Then
    ' Set Port Direction to output
    If me3000DIOSetPortDirection(glBoardNumber, PORTA, MEOUTPUT) = 0 Then
        me3000ErrorMessage (AppName)
    End If
        
    ' Set a single Bit
    If me3000DOSetBit(lBoardNumber, PORTA, l, 1&) = 0 Then
        me3000ErrorMessage (AppName)
        Exit Sub
    End If
    
    MsgBox "Next"
    
    ' Set a High Byte
    If me3000DOSetByte(lBoardNumber, PORTA, HIGH_BYTE, &HA5&) = 0 Then
        me3000ErrorMessage (AppName)
        Exit Sub
    End If
    
    MsgBox "Next"

    ' Set a Low Byte
    If me3000DOSetByte(lBoardNumber, PORTA, LOW_BYTE, &H5A&) = 0 Then
        me3000ErrorMessage (AppName)
        Exit Sub
    End If

    MsgBox "Next"

    ' Set a Word
    If me3000DOSetWord(lBoardNumber, PORTA, &HFF&) = 0 Then
        me3000ErrorMessage (AppName)
        Exit Sub
    End If

    
    ' Set Port Direction to input
    If me3000DIOSetPortDirection(lBoardNumber, PORTA, MEINPUT) = 0 Then
        me3000ErrorMessage (AppName)
    End If
    
    
    If me3000DIGetWord(glBoardNumber, PORTA, lValueA) = 0 Then
        me3000ErrorMessage (AppName)
        Exit Sub
    End If
    
    MsgBox "Get Word: " + Hex(lValueA)
        
        
    If me3000DIGetByte(glBoardNumber, PORTA, HIGH_BYTE, lValueA) = 0 Then
        me3000ErrorMessage (AppName)
        Exit Sub
    End If
    
    MsgBox "Get HighByte: " + Hex(lValueA)
    
    If me3000DIGetByte(glBoardNumber, PORTA, LOW_BYTE, lValueA) = 0 Then
        me3000ErrorMessage (AppName)
        Exit Sub
    End If
    
    MsgBox "Get LowByte: " + Hex(lValueA)
        
    If me3000DIGetBit(glBoardNumber, PORTA, 0, lValueA) = 0 Then
        me3000ErrorMessage (AppName)
        Exit Sub
    End If
    
    MsgBox "Bit 0: " + Hex(lValueA)
End If
    
    
    '-----------------------------------------------------------------------
    '
    ' PWM Functions
    '
    '-----------------------------------------------------------------------
If 1 Then

    If me3000PWMSetMode(lBoardNumber, 500#, 50&, PWM3000_NORMAL) = 0 Then
        me3000ErrorMessage (AppName)
        Exit Sub
    End If
    me3000PWMStart (lBoardNumber)
    MsgBox "Stop PWM now!"

    me3000PWMStop (lBoardNumber)
End If

    
    
    '-----------------------------------------------------------------------
    '
    ' Counter Functions
    '
    '-----------------------------------------------------------------------
If 1 Then
    If me3000CNTReset(lBoardNumber, COUNTER3000_A) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
    
    If me3000CNTStart(lBoardNumber, COUNTER3000_A) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
    
    If me3000CNTSetRange(lBoardNumber, COUNTER3000_A, 5, 0) = 0 Then
        Call me3000ErrorMessage(AppName)
    End If
    
    MsgBox "Counter A comes next!"
        
    If me3000CNTRead(lBoardNumber, COUNTER3000_A, iCounterValue) = 0 Then
        Call me3000ErrorMessage(AppName)
        Exit Sub
    Else
        MsgBox "Counter A = " + Str(iCounterValue)
    End If
End If

    ' Don't show form, exit immedeately
    End
End Sub
Function MakeChannelList(ByVal lNo As Long, ByVal lCount As Long) As Long
    Dim i As Integer
    Dim lEntry As Long
            
    ' Clear the current channel list
    '----------------------------------------------------
    Call me3000AIClearChannelList(lNo)

    ' Write n channel list entries to the board
    '----------------------------------------------------
    For i = 0 To lCount - 1
    
        If me3000AIMakeChannelListEntry(glADCChannel, glADCRange, glADCMode, lEntry) = 0 Then
            Call me3000ErrorMessage(AppName)
            MakeChannelList = 0
        End If
    
        If me3000AIAddToChannelList(lNo, lEntry) = 0 Then
            me3000ErrorMessage (AppName)
            MakeChannelList = 0
        End If
        
    Next i
    MakeChannelList = 1
End Function

Sub DACWrapAround()
    Dim i As Integer
    Dim lEntry As Long
    
    ' Clear the DAC FIFO
    '----------------------------------------------------
    If me3000AOClearDACFIFO(lBoardNumber) = 0 Then
        me3000ErrorMessage ("WrapAround")
    End If
    
    ' Create the new DAC FIFO contents
    '----------------------------------------------------
    For i = 0 To 1000 - 1
        lEntry = CLng(4095# / 1000 * i)
        If me3000AOAddToDACFIFO(lBoardNumber, lEntry) = 0 Then
            me3000ErrorMessage ("WrapAround")
            Exit Sub
        End If
    Next i

    ' Setup Mode
    '----------------------------------------------------
    If me3000AOSetMode(lBoardNumber, 0, AO3000_MINUS_10, AO3000_TRANSPARENT) = 0 Then
        me3000ErrorMessage ("WrapAround")
        Exit Sub
    End If

    ' Setup Timer
    '----------------------------------------------------
    Call me3000AOSetTimer(lBoardNumber, me3000FrequencyToCounter(50000))

    If me3000AOWrapAround(lBoardNumber) = 0 Then
        me3000ErrorMessage ("WrapAround")
    End If
    
End Sub

Sub DACContinuousPolling()
    Dim i As Integer
    Dim iVal As Integer
    Dim dVal As Double
    ReDim DummyX(0 To 5) As Integer
    Const lDACCount = 1000&
    ReDim piDACBuffer(0 To lDACCount) As Integer
        
    ' Calculate beautiful output values
    '----------------------------------------------------
    For i = 0 To lDACCount - 1
        dVal = 6.28318530718 / lDACCount * CDbl(i) * 5#
        iVal = CInt(2048# + 2048# * Sin(dVal))
        If iVal >= 4095 Then iVal = 4095

        piDACBuffer(i) = iVal
    Next i
    
    
    ' Setup Mode
    '----------------------------------------------------
    If me3000AOSetMode(lBoardNumber, 0, AO3000_MINUS_10, AO3000_TRANSPARENT) = 0 Then
        Call me3000ErrorMessage("DACContinuousPolling")
        Exit Sub
    End If

    ' Setup Timer
    '----------------------------------------------------
    Call me3000AOSetTimer(glBoardNumber, me3000FrequencyToCounter(500))
    
    If me3000AOContinuous(glBoardNumber, AO3000_POLLING, lDACCount, piDACBuffer(0)) = 0 Then
        Call me3000ErrorMessage("DACContinuousPolling")
    End If
    
    
End Sub

