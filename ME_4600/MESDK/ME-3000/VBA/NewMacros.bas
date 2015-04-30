Attribute VB_Name = "NewMacros1"
'Attribute VB_Name = "Declarations"'
Option Explicit

' Types used by the API DLL
'-------------------------------------------------------------------------------------------
Type ME3000_ISR
    ISR As Long
    AdcFifo As Long
    ChanList As Long
    Extern As Long
    CountA As Long
    CountB As Long
    UART As Long
    DacFifo As Long
End Type

Type ME3000_DRIVER_STATUS
    ' Take care of 4-bytes-alignment: Add padding bytes if necessary!
    Control1 As Integer
    Control2 As Integer
    Control3 As Integer
    IRQMask As Integer
    ISRMask As Integer
    Status As Integer
    DACStatus As Integer
    Padding As Integer
    DebugWord As Long
End Type

Type ME_PLX9050_INFO
                               '  offset  comment
    VendorID As Integer        '  0x00    vendor identifier
    DeviceID As Integer        '  0x02    device identifier
    Command As Integer         '  0x04    command register
    Status As Integer          '  0x06    status register
    Revision As Byte           '  0x08    revison number
    Class(0 To 2) As Byte      '  0x09    device class code
    CacheSize As Byte          '  0x0C    size of cache lines
    Latency As Byte            '  0x0D    latency time
    HeaderType As Byte         '  0x0E    header type
    Bist As Byte               '  0x0F    built-in self-test
    BaseAddr(0 To 5) As Long   '  0x10    base addr. 0-5
    Cis  As Long               '  0x28    CIS-pointer (cardbus)
    SubVendor As Integer       '  0x2C    subsystem vendor ID
    SubSystem  As Integer      '  0x2E    subsystem ID
    ROMAddr As Long            '  0x30    base addr. of Extension ROM
    Reserved(0 To 1) As Long   '  0x34
    IRQ As Byte                '  0x3C    number of IRQ
    IPin As Byte               '  0x3D    pin number of IRQ
    Min_Gnt As Byte            '  0x3E    min. burst in 1/4 micro secs.
    Max_Lat As Byte            '  0x3F    max. latency in 1/4 micro secs.
    Device(0 To 191) As Byte   '  0x40    device-specific data
End Type                       ' total size: 0x100


Type ME3000_BOARD_INFO
    ' Take care of 4-bytes-alignment: Add padding bytes if necessary!
    ErrorCode As Long       ' Driver error code
    NoOfBoards As Long      ' No. of boards detected by DriverEntry
    DeviceNumber As Long    ' Number of selected board
    Word As Long            ' General purpose debug value
    RTPhysAddr As Long      ' Phys. address of PLX RT registers
    XilinxPhysAddr As Long  '  Phys. address of XILINX
    SioPhysAddr As Long     ' Phys. address of SIO
    MEVECModel As Long      ' Actually loaded Firmware Model
    FileStatus As Long      ' Status after reading Firmware file
    FileLength As Long      ' Length of Firmware file
    FileVersion As Long     ' Version of Firmware file
    FileDate As Long        ' Date of Firmware file
    AdcFifo As Long         ' Size of ADC FIFO
    DacFifo As Long         ' Size of DAC FIFO
    ChanListFifo As Long    ' Size of channel list FIFO
    SerialNumber As Long
    Date As Long            ' Date when EEPROM was written
    SlotNumber As Long      ' PCI slot number
End Type


Type ME3000_SIO
    Mode  As Long
    InBufferSize As Long
    InBufferCount As Long
    InBufferReadPointer As Long
    InBufferWritePointer As Long
    InBufferOverwrite As Long
    InBufferOverwriteCount As Long
    InStop As Long
    InError As Long

    OutBufferSize As Long
    OutBufferCount As Long
    OutBufferEndPointer  As Long
    OutError As Long

    Dummy1 As Long  ' pointer to inbuffer, not needed
    Dummy2 As Long  ' pointer to outbuffer, not needed
End Type

Type ME3000_SIO_REGS
        RHR As Byte      ' Reveive Register
        IER As Byte      ' Interrupt Enable Register
        FCR As Byte      ' FIFI Control Register
        LCR As Byte      ' Line Control Register
        MCR As Byte      ' Modem Control Register
        LSR As Byte      ' Line Status Register
        MSR As Byte      ' Modem Satus Register
        SPR As Byte      'ScatchPad Register
End Type


' Constants used by the API DLL
'-------------------------------------------------------------------------------------------

' Thread priority
'--------------------------------------------------------------------
Global Const PRIORITY_HIGH = 1&
Global Const PRIORITY_LOW = 0&

' Defines used for the Serial Interface UART 16C550
'--------------------------------------------------------------------
Global Const SIO_RHR = 0
Global Const SIO_THR = 0
Global Const SIO_IER = 1
Global Const SIO_FCR = 2
Global Const SIO_ISR = 2
Global Const SIO_LCR = 3
Global Const SIO_MCR = 4
Global Const SIO_LSR = 5
Global Const SIO_MSR = 6
Global Const SIO_SPR = 7

Global Const SIO_DLL = 0
Global Const SIO_DLM = 1

Global Const SIO_NO_PARITY = &H0
Global Const SIO_ODD_PARITY = &H8
Global Const SIO_EVEN_PARITY = &H18
Global Const SIO_FORCE_ODD = &H28
Global Const SIO_FORCE_EVEN = &H38

Global Const SIO_LEN_7 = &H2
Global Const SIO_LEN_8 = &H3

Global Const SIO_STOP_1 = &H0
Global Const SIO_STOP_2 = &H4

Global Const SIO_LATCH_ENA = &H80

Global Const SIO_1200_DIV = &H60
Global Const SIO_2400_DIV = &H30
Global Const SIO_4800_DIV = &H18
Global Const SIO_9600_DIV = &HC
Global Const SIO_19200_DIV = &H6
Global Const SIO_38400_DIV = &H3
Global Const SIO_57600_DIV = &H2
Global Const SIO_115200_DIV = &H1
Global Const SIO_250000_DIV = &H0

Global Const SIO_LOOPBACK = &H10

Global Const SIO_ERROR = &HE&

Global Const SIO_POLLING = &H1&
Global Const SIO_INTERRUPT = &H2&

Global Const SIO_OVERWRITE = &H20&

Global Const SIO_RS485_HALF_DUPLEX = &H10&


' DIO
'--------------------------------------------------------------------
Global Const LOW_BYTE = 0&
Global Const HIGH_BYTE = 1&

Global Const MEINPUT = 0&
Global Const MEOUTPUT = 1&

Global Const PORTA = 0&
Global Const PORTB = 1&

' PWM
'--------------------------------------------------------------------
Global Const PWM3000_NORMAL = 1&
Global Const PWM3000_INVERTED = 2&

' Counter
'--------------------------------------------------------------------
Global Const COUNTER3000_A = 1&
Global Const COUNTER3000_B = 2&
Global Const COUNTER3000_ENABLE = 4&
Global Const COUNTER3000_DISABLE = 8&


' Analog Input Modes and Ranges
'--------------------------------------------------------------------
Global Const AI3000_DIFFERENTIAL = &H80&
Global Const AI3000_SINGLE_ENDED = &H0&
Global Const AI3000_PLUS_10 = &H40&
Global Const AI3000_PLUS_5 = &H50&
Global Const AI3000_PLUS_2 = &H60&
Global Const AI3000_PLUS_1 = &H70&
Global Const AI3000_MINUS_10 = &H0&
Global Const AI3000_MINUS_5 = &H10&
Global Const AI3000_MINUS_2 = &H20&
Global Const AI3000_MINUS_1 = &H30&


' AI Modes
'--------------------------------------------------------------------
Global Const AI3000_INFINITE = &HFFFFFFFF
Global Const AI3000_INTERRUPT = &H1&
Global Const AI3000_POLLING = &H2&
Global Const AI3000_ENABLE = &H10&
Global Const AI3000_DISABLE = &H20&
Global Const AI3000_SCAN_TO_DISK = &H10000
Global Const AI3000_SCAN_INFINITE = &H20000

 ' Analog Input Trigger Modes
 '--------------------------------------------------------------------
Global Const AI3000_TRIGGER_TIMER = &H1&
Global Const AI3000_TRIGGER_EXT_LOW = &H2&
Global Const AI3000_TRIGGER_EXT_HIGH = &H4&
Global Const AI3000_TRIGGER_CONTI = &H8&

' Analog Output Ranges
'--------------------------------------------------------------------
Global Const AO3000_PLUS_10 = &H1&
Global Const AO3000_MINUS_5 = &H4&
Global Const AO3000_MINUS_10 = &H8&

' Analog Output Modes
'--------------------------------------------------------------------
Global Const AO3000_BUFFERED = &H1&
Global Const AO3000_TRANSPARENT = &H2&

' Analog Output Trigger Modes
'--------------------------------------------------------------------
Global Const AO3000_TRIGGER_TIMER = &H1&
Global Const AO3000_TRIGGER_EXT_LOW = &H2&
Global Const AO3000_TRIGGER_EXT_HIGH = &H4&

' AO Modes
'--------------------------------------------------------------------
Global Const AO3000_INFINITE = &HFFFFFFFF
Global Const AO3000_INTERRUPT = &H1&
Global Const AO3000_POLLING = &H2&



'Note, that string arguments only work with initialized string variables
'      Dim gsTextBuffer As String * 256 or alternatively  sBuffer = String(25, Chr(0))
'-------------------------------------------------------------------------------------------
Declare Function me3000ErrorMessage Lib "me3000.dll" Alias "_VBme3000ErrorMessage@4" (ByVal lpBuffer As String) As Long
Declare Function me3000Initialize Lib "me3000.dll" Alias "_VBme3000Initialize@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000GeneralReset Lib "me3000.dll" Alias "_VBme3000GeneralReset@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000GetDLLVersion Lib "me3000.dll" Alias "_VBme3000GetDLLVersion@0" () As Long
Declare Function me3000GetDriverTimeStamp Lib "me3000.dll" Alias "_VBme3000GetDriverTimeStamp@4" (ByVal lpBuffer As String) As Long
Declare Function me3000GetDriverVersion Lib "me3000.dll" Alias "_VBme3000GetDriverVersion@4" (ByVal lpBuffer As String) As Long
Declare Function me3000GetSerialNumber Lib "me3000.dll" Alias "_VBme3000GetSerialNumber@8" (ByVal lBoardNumber As Long, ByRef lSerialNumber As Long) As Long
Declare Function me3000GetVECModel Lib "me3000.dll" Alias "_VBme3000GetVECModel@8" (ByVal lBoardNumber As Long, ByRef lMEVECModel As Long) As Long
Declare Function me3000GetInterrupts Lib "me3000.dll" Alias "_VBme3000GetInterrupts@8" (ByVal lBoardNumber As Long, ByRef pInt As ME3000_ISR) As Long
Declare Function me3000GetDriverStatus Lib "me3000.dll" Alias "_VBme3000GetDriverStatus@8" (ByVal lBoardNumber As Long, ByRef pStatus As ME3000_DRIVER_STATUS) As Long
Declare Function me3000GetPCIConfiguration Lib "me3000.dll" Alias "_VBme3000GetPCIConfiguration@8" (ByVal lBoardNumber As Long, ByRef pBoard As ME_PLX9050_INFO) As Long
Declare Function me3000DLLBoardInfo Lib "me3000.dll" Alias "_VBme3000DLLBoardInfo@8" (ByVal lBoardNumber As Long, ByRef pInfo As ME3000_BOARD_INFO) As Long
Declare Function me3000AIAddToChannelList Lib "me3000.dll" Alias "_VBme3000AIAddToChannelList@8" (ByVal lBoardNumber As Long, ByVal lEntry As Long) As Long
Declare Function me3000AIClearChannelList Lib "me3000.dll" Alias "_VBme3000AIClearChannelList@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000AIMakeChannelListEntry Lib "me3000.dll" Alias "_VBme3000AIMakeChannelListEntry@16" (ByVal lChannel As Long, ByVal lRange As Long, ByVal lMode As Long, ByRef plEntry As Long) As Long
Declare Function me3000FrequencyToCounter Lib "me3000.dll" Alias "_VBme3000FrequencyToCounter@8" (ByVal dFrequency As Double) As Long
Declare Function me3000FileName Lib "me3000.dll" Alias "_VBme3000FileName@12" (ByVal lBoardNumber As Long, ByVal lType As Long, ByVal lpBuffer As String) As Long
Declare Function me3000AISetTrigger Lib "me3000.dll" Alias "_VBme3000AISetTrigger@8" (ByVal lBoardNumber As Long, ByVal lModePolarity As Long) As Long
Declare Function me3000AISetTimer Lib "me3000.dll" Alias "_VBme3000AISetTimer@12" (ByVal lBoardNumber As Long, ByVal lScan As Long, ByVal lChan As Long) As Long
Declare Function me3000AISetSimultaneous Lib "me3000.dll" Alias "_VBme3000AISetSimultaneous@8" (ByVal lBoardNumber As Long, ByVal lMode As Long) As Long
Declare Function me3000AISingle Lib "me3000.dll" Alias "_VBme3000AISingle@16" (ByVal lBoardNumber As Long, ByVal lChannelNo As Long, ByVal lMode As Long, ByRef piValue As Integer) As Long
Declare Function me3000AIQuick Lib "me3000.dll" Alias "_VBme3000AIQuick@16" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal lCount As Long, ByVal lMode As Long) As Long
Declare Function me3000AIMultiple Lib "me3000.dll" Alias "_VBme3000AIMultiple@16" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal lCount As Long, ByVal lMode As Long) As Long
Declare Function me3000AIScan Lib "me3000.dll" Alias "_VBme3000AIScan@20" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal lSize As Long, ByVal lCount As Long, ByVal lMode As Long) As Long
Declare Function me3000AIStop Lib "me3000.dll" Alias "_VBme3000AIStop@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000AISingleEx Lib "me3000.dll" Alias "_VBme3000AISingleEx@28" (ByVal lBoardNumber As Long, ByVal lChannel As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByRef piBuffer As Integer, ByVal pCallBack As Long) As Long
Declare Function me3000AIQuickEx Lib "me3000.dll" Alias "_VBme3000AIQuickEx@28" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByVal pCallBack As Long) As Long
Declare Function me3000AIMultipleEx Lib "me3000.dll" Alias "_VBme3000AIMultipleEx@28" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByVal pCallBack As Long) As Long
Declare Function me3000AIScanEx Lib "me3000.dll" Alias "_VBme3000AIScanEx@32" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal lSize As Long, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByVal pCallBack As Long) As Long
Declare Function me3000SetPriority Lib "me3000.dll" Alias "_VBme3000SetPriority@8" (ByVal lBoardNumber As Long, ByVal lPriority As Long) As Long
Declare Function me3000AOAddToDACFIFO Lib "me3000.dll" Alias "_VBme3000AOAddToDACFIFO@8" (ByVal lBoardNumber As Long, ByVal lEntry As Long) As Long
Declare Function me3000AOClearDACFIFO Lib "me3000.dll" Alias "_VBme3000AOClearDACFIFO@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000AOReset Lib "me3000.dll" Alias "_VBme3000AOReset@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000AOSetTimer Lib "me3000.dll" Alias "_VBme3000AOSetTimer@8" (ByVal lBoardNumber As Long, ByVal lTime As Long) As Long
Declare Function me3000AOSetTrigger Lib "me3000.dll" Alias "_VBme3000AOSetTrigger@8" (ByVal lBoardNumber As Long, ByVal lModePolarity As Long) As Long
Declare Function me3000AOSetMode Lib "me3000.dll" Alias "_VBme3000AOSetMode@16" (ByVal lBoardNumber As Long, ByVal lChannel As Long, ByVal lRange As Long, ByVal lMode As Long) As Long
Declare Function me3000AOSingle Lib "me3000.dll" Alias "_VBme3000AOSingle@12" (ByVal lBoardNumber As Long, ByVal lChannel As Long, ByVal iValue As Integer) As Long
Declare Function me3000AOWrapAround Lib "me3000.dll" Alias "_VBme3000AOWrapAround@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000AOStop Lib "me3000.dll" Alias "_VBme3000AOStop@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000AOStopEx Lib "me3000.dll" Alias "_VBme3000AOStopEx@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000AOUpdate Lib "me3000.dll" Alias "_VBme3000AOUpdate@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000AOContinuous Lib "me3000.dll" Alias "_VBme3000AOContinuous@16" (ByVal lBoardNumber As Long, ByVal lMode As Long, ByVal lSize As Long, ByRef piBuffer As Integer) As Long
Declare Function me3000AOContinuousEx Lib "me3000.dll" Alias "_VBme3000AOContinuousEx@28" (ByVal lBoardNumber As Long, ByVal lMode As Long, ByVal lSize As Long, ByRef piBuffer As Integer, ByVal lLoops As Long, ByVal lDelay As Long, ByVal pCallBack As Long) As Long
Declare Function me3000DIOSetPortDirection Lib "me3000.dll" Alias "_VBme3000DIOSetPortDirection@12" (ByVal lBoardNumber As Long, ByVal lPortNo As Long, ByVal lDir As Long) As Long
Declare Function me3000DIGetBit Lib "me3000.dll" Alias "_VBme3000DIGetBit@16" (ByVal lBoardNumber As Long, ByVal lPortNo As Long, ByVal lBitNo As Long, ByRef pBitValue As Long) As Long
Declare Function me3000DIGetByte Lib "me3000.dll" Alias "_VBme3000DIGetByte@16" (ByVal lBoardNumber As Long, ByVal lPortNo As Long, ByVal lBitNo As Long, ByRef pByteValue As Long) As Long
Declare Function me3000DIGetWord Lib "me3000.dll" Alias "_VBme3000DIGetWord@12" (ByVal lBoardNumber As Long, ByVal lPortNo As Long, ByRef pValue As Long) As Long
Declare Function me3000DOSetBit Lib "me3000.dll" Alias "_VBme3000DOSetBit@16" (ByVal lBoardNumber As Long, ByVal lPortNo As Long, ByVal lBitNo As Long, ByVal lBitValue As Long) As Long
Declare Function me3000DOSetByte Lib "me3000.dll" Alias "_VBme3000DOSetByte@16" (ByVal lBoardNumber As Long, ByVal lPortNo As Long, ByVal lBitNo As Long, ByVal lByteValue As Long) As Long
Declare Function me3000DOSetWord Lib "me3000.dll" Alias "_VBme3000DOSetWord@12" (ByVal lBoardNumber As Long, ByVal lPortNo As Long, ByVal lValue As Long) As Long
Declare Function me3000DOReset Lib "me3000.dll" Alias "_VBme3000DOReset@8" (ByVal lBoardNumber As Long, ByVal lPortNo As Long) As Long
Declare Function me3000PWMStart Lib "me3000.dll" Alias "_VBme3000PWMStart@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000PWMStop Lib "me3000.dll" Alias "_VBme3000PWMStop@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000PWMSetMode Lib "me3000.dll" Alias "_VBme3000PWMSetMode@20" (ByVal lBoardNumber As Long, ByVal dFrequency As Double, ByVal lDutyCycle As Long, ByVal lInverted As Long) As Long
Declare Function me3000DisableExternalInt Lib "me3000.dll" Alias "_VBme3000DisableExternalInt@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000EnableExternalInt Lib "me3000.dll" Alias "_VBme3000EnableExternalInt@8" (ByVal lBoardNumber As Long, ByVal pCallBack As Long) As Long
Declare Function me3000CNTStart Lib "me3000.dll" Alias "_VBme3000CNTStart@8" (ByVal lBoardNumber As Long, ByVal lCounter As Long) As Long
Declare Function me3000CNTReset Lib "me3000.dll" Alias "_VBme3000CNTReset@8" (ByVal lBoardNumber As Long, ByVal lCounter As Long) As Long
Declare Function me3000CNTRead Lib "me3000.dll" Alias "_VBme3000CNTRead@12" (ByVal lBoardNumber As Long, ByVal lCounter As Long, ByRef piCounterValue As Integer) As Long
Declare Function me3000CNTSetRange Lib "me3000.dll" Alias "_VBme3000CNTSetRange@16" (ByVal lBoardNumber As Long, ByVal lCounter As Long, ByVal lEndVal As Long, ByVal lStartVal As Long) As Long
Declare Function me3000CNTInterrupt Lib "me3000.dll" Alias "_VBme3000CNTInterrupt@16" (ByVal lBoardNumber As Long, ByVal lCounter As Long, ByVal lFlag As Long, ByVal pCallBack As Long) As Long
Declare Function me3000SIOReadRegister Lib "me3000.dll" Alias "_VBme3000SIOReadRegister@8" (ByVal lBoardNumber As Long, ByVal cReg As Byte) As Byte
Declare Function me3000SIOWriteRegister Lib "me3000.dll" Alias "_VBme3000SIOWriteRegister@12" (ByVal lBoardNumber As Long, ByVal cReg As Byte, ByVal cVal As Byte) As Byte
Declare Function me3000SIOLoopBackTest Lib "me3000.dll" Alias "_VBme3000SIOLoopBackTest@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000SIOSetup Lib "me3000.dll" Alias "_VBme3000SIOSetup@20" (ByVal lBoardNumber As Long, ByVal lBaud As Long, ByVal lLen As Long, ByVal lStop As Long, ByVal cParity As Byte) As Long
Declare Function me3000SIOGetRegisters Lib "me3000.dll" Alias "_VBme3000SIOGetRegisters@8" (ByVal lBoardNumber As Long, ByRef Regs As ME3000_SIO_REGS) As Long
Declare Function me3000SIOTransmit Lib "me3000.dll" Alias "_VBme3000SIOTransmit@16" (ByVal lBoardNumber As Long, ByVal lMode As Long, ByVal lCount As Long, ByVal lpBuffer As String) As Long
Declare Function me3000SIOReceive Lib "me3000.dll" Alias "_VBme3000SIOReceive@16" (ByVal lBoardNumber As Long, ByVal lMode As Long, ByVal lCount As Long, ByVal lpBuffer As String) As Long
Declare Function me3000SIOOpen Lib "me3000.dll" Alias "_VBme3000SIOOpen@16" (ByVal lBoardNumber As Long, ByVal lMode As Long, ByVal lInbufferSize As Long, ByVal lOutBufferSize As Long) As Long
Declare Function me3000SIOClose Lib "me3000.dll" Alias "_VBme3000SIOClose@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000SIOCheckError Lib "me3000.dll" Alias "_VBme3000SIOCheckError@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000SIOClearBuffer Lib "me3000.dll" Alias "_VBme3000SIOClearBuffer@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000SIOCheckBuffer Lib "me3000.dll" Alias "_VBme3000SIOCheckBuffer@8" (ByVal lBoardNumber As Long, ByRef pSio As ME3000_SIO) As Long






Sub me3000()
Attribute me3000.VB_Description = "Makro erstellt am 07.05.99 von Andreas Bernau"
Attribute me3000.VB_ProcData.VB_Invoke_Func = "Normal.NewMacros.me1400"
    Const AppName = "VBTest"
    
    Dim sBigText As String * 256
    Dim glBoardNumber As Integer
    Dim glDACChannel As Integer
    Dim l As Integer
    
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


' Some helper functions
'--------------------------------------------------------------------
Function MAKE_DACFIFOENTRY(ByVal lCh As Long, ByVal lValue As Long) As Long
    MAKE_DACFIFOENTRY = lCh * 4096 + (lValue And &HFFF&)
End Function


