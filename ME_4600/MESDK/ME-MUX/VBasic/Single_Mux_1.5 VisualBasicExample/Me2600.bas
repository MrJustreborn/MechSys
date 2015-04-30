Attribute VB_Name = "Declarations"
Option Explicit

' Types used by the API DLL
'-------------------------------------------------------------------------------------------
Type ME2600_ISR
    ISR As Long
    AdcFifo As Long
    ChanList As Long
    Extern As Long
    CountA As Long
    CountB As Long
    UART As Long
    DacFifo As Long
End Type

Type ME2600_DRIVER_STATUS
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


Type ME2600_BOARD_INFO
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


Type ME2600_SIO
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

Type ME2600_SIO_REGS
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
Global Const PWM2600_NORMAL = 1&
Global Const PWM2600_INVERTED = 2&

' Counter
'--------------------------------------------------------------------
Global Const COUNTER2600_A = 1&
Global Const COUNTER2600_B = 2&
Global Const COUNTER2600_ENABLE = 4&
Global Const COUNTER2600_DISABLE = 8&


' Analog Input Modes and Ranges
'--------------------------------------------------------------------
Global Const AI2600_DIFFERENTIAL = &H80&
Global Const AI2600_SINGLE_ENDED = &H0&
Global Const AI2600_PLUS_10 = &H40&
Global Const AI2600_PLUS_5 = &H50&
Global Const AI2600_PLUS_2 = &H60&
Global Const AI2600_PLUS_1 = &H70&
Global Const AI2600_MINUS_10 = &H0&
Global Const AI2600_MINUS_5 = &H10&
Global Const AI2600_MINUS_2 = &H20&
Global Const AI2600_MINUS_1 = &H30&


' AI Modes
'--------------------------------------------------------------------
Global Const AI2600_INFINITE = &HFFFFFFFF
Global Const AI2600_INTERRUPT = &H1&
Global Const AI2600_POLLING = &H2&
Global Const AI2600_ENABLE = &H10&
Global Const AI2600_DISABLE = &H20&
Global Const AI2600_SCAN_TO_DISK = &H10000
Global Const AI2600_SCAN_INFINITE = &H20000

 ' Analog Input Trigger Modes
 '--------------------------------------------------------------------
Global Const AI2600_TRIGGER_TIMER = &H1&
Global Const AI2600_TRIGGER_EXT_LOW = &H2&
Global Const AI2600_TRIGGER_EXT_HIGH = &H4&
Global Const AI2600_TRIGGER_CONTI = &H8&

' Analog Output Ranges
'--------------------------------------------------------------------
Global Const AO2600_PLUS_10 = &H1&
Global Const AO2600_MINUS_5 = &H4&
Global Const AO2600_MINUS_10 = &H8&

' Analog Output Modes
'--------------------------------------------------------------------
Global Const AO2600_BUFFERED = &H1&
Global Const AO2600_TRANSPARENT = &H2&

' Analog Output Trigger Modes
'--------------------------------------------------------------------
Global Const AO2600_TRIGGER_TIMER = &H1&
Global Const AO2600_TRIGGER_EXT_LOW = &H2&
Global Const AO2600_TRIGGER_EXT_HIGH = &H4&

' AO Modes
'--------------------------------------------------------------------
Global Const AO2600_INFINITE = &HFFFFFFFF
Global Const AO2600_INTERRUPT = &H1&
Global Const AO2600_POLLING = &H2&

'Note, that string arguments only work with initialized string variables
'      Dim gsTextBuffer As String * 256 or alternatively  sBuffer = String(25, Chr(0))
'-------------------------------------------------------------------------------------------
Declare Function me2600ErrorMessage Lib "me2600.dll" Alias "_VBme2600ErrorMessage@4" (ByVal lpBuffer As String) As Long
Declare Function me2600Initialize Lib "me2600.dll" Alias "_VBme2600Initialize@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600GeneralReset Lib "me2600.dll" Alias "_VBme2600GeneralReset@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600GetDLLVersion Lib "me2600.dll" Alias "_VBme2600GetDLLVersion@0" () As Long
Declare Function me2600GetDriverTimeStamp Lib "me2600.dll" Alias "_VBme2600GetDriverTimeStamp@4" (ByVal lpBuffer As String) As Long
Declare Function me2600GetDriverVersion Lib "me2600.dll" Alias "_VBme2600GetDriverVersion@4" (ByVal lpBuffer As String) As Long
Declare Function me2600GetSerialNumber Lib "me2600.dll" Alias "_VBme2600GetSerialNumber@8" (ByVal lBoardnumber As Long, ByRef lSerialNumber As Long) As Long
Declare Function me2600GetVECModel Lib "me2600.dll" Alias "_VBme2600GetVECModel@8" (ByVal lBoardnumber As Long, ByRef lMEVECModel As Long) As Long
Declare Function me2600GetInterrupts Lib "me2600.dll" Alias "_VBme2600GetInterrupts@8" (ByVal lBoardnumber As Long, ByRef pInt As ME2600_ISR) As Long
Declare Function me2600GetDriverStatus Lib "me2600.dll" Alias "_VBme2600GetDriverStatus@8" (ByVal lBoardnumber As Long, ByRef pStatus As ME2600_DRIVER_STATUS) As Long
Declare Function me2600GetPCIConfiguration Lib "me2600.dll" Alias "_VBme2600GetPCIConfiguration@8" (ByVal lBoardnumber As Long, ByRef pBoard As ME_PLX9050_INFO) As Long
Declare Function me2600DLLBoardInfo Lib "me2600.dll" Alias "_VBme2600DLLBoardInfo@8" (ByVal lBoardnumber As Long, ByRef pInfo As ME2600_BOARD_INFO) As Long
Declare Function me2600AIAddToChannelList Lib "me2600.dll" Alias "_VBme2600AIAddToChannelList@8" (ByVal lBoardnumber As Long, ByVal lEntry As Long) As Long
Declare Function me2600AIClearChannelList Lib "me2600.dll" Alias "_VBme2600AIClearChannelList@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600AIMakeChannelListEntry Lib "me2600.dll" Alias "_VBme2600AIMakeChannelListEntry@16" (ByVal lChannel As Long, ByVal lRange As Long, ByVal lMode As Long, ByRef plEntry As Long) As Long
Declare Function me2600FrequencyToCounter Lib "me2600.dll" Alias "_VBme2600FrequencyToCounter@8" (ByVal dFrequency As Double) As Long
Declare Function me2600FileName Lib "me2600.dll" Alias "_VBme2600FileName@12" (ByVal lBoardnumber As Long, ByVal lType As Long, ByVal lpBuffer As String) As Long
Declare Function me2600AISetTrigger Lib "me2600.dll" Alias "_VBme2600AISetTrigger@8" (ByVal lBoardnumber As Long, ByVal lModePolarity As Long) As Long
Declare Function me2600AISetTimer Lib "me2600.dll" Alias "_VBme2600AISetTimer@12" (ByVal lBoardnumber As Long, ByVal lScan As Long, ByVal lChan As Long) As Long
Declare Function me2600AISetSimultaneous Lib "me2600.dll" Alias "_VBme2600AISetSimultaneous@8" (ByVal lBoardnumber As Long, ByVal lMode As Long) As Long
Declare Function me2600AISingle Lib "me2600.dll" Alias "_VBme2600AISingle@16" (ByVal lBoardnumber As Long, ByVal lChannelNo As Long, ByVal lMode As Long, ByRef piValue As Integer) As Long
Declare Function me2600AIQuick Lib "me2600.dll" Alias "_VBme2600AIQuick@16" (ByVal lBoardnumber As Long, ByRef piBuffer As Integer, ByVal lCount As Long, ByVal lMode As Long) As Long
Declare Function me2600AIMultiple Lib "me2600.dll" Alias "_VBme2600AIMultiple@16" (ByVal lBoardnumber As Long, ByRef piBuffer As Integer, ByVal lCount As Long, ByVal lMode As Long) As Long
Declare Function me2600AIScan Lib "me2600.dll" Alias "_VBme2600AIScan@20" (ByVal lBoardnumber As Long, ByRef piBuffer As Integer, ByVal lSize As Long, ByVal lCount As Long, ByVal lMode As Long) As Long
Declare Function me2600AIStop Lib "me2600.dll" Alias "_VBme2600AIStop@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600AISingleEx Lib "me2600.dll" Alias "_VBme2600AISingleEx@28" (ByVal lBoardnumber As Long, ByVal lChannel As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByRef piBuffer As Integer, ByVal pCallBack As Long) As Long
Declare Function me2600AIQuickEx Lib "me2600.dll" Alias "_VBme2600AIQuickEx@28" (ByVal lBoardnumber As Long, ByRef piBuffer As Integer, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByVal pCallBack As Long) As Long
Declare Function me2600AIMultipleEx Lib "me2600.dll" Alias "_VBme2600AIMultipleEx@28" (ByVal lBoardnumber As Long, ByRef piBuffer As Integer, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByVal pCallBack As Long) As Long
Declare Function me2600AIScanEx Lib "me2600.dll" Alias "_VBme2600AIScanEx@32" (ByVal lBoardnumber As Long, ByRef piBuffer As Integer, ByVal lSize As Long, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByVal pCallBack As Long) As Long
Declare Function me2600SetPriority Lib "me2600.dll" Alias "_VBme2600SetPriority@8" (ByVal lBoardnumber As Long, ByVal lPriority As Long) As Long
Declare Function me2600AOAddToDACFIFO Lib "me2600.dll" Alias "_VBme2600AOAddToDACFIFO@8" (ByVal lBoardnumber As Long, ByVal lEntry As Long) As Long
Declare Function me2600AOClearDACFIFO Lib "me2600.dll" Alias "_VBme2600AOClearDACFIFO@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600AOReset Lib "me2600.dll" Alias "_VBme2600AOReset@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600AOSetTimer Lib "me2600.dll" Alias "_VBme2600AOSetTimer@8" (ByVal lBoardnumber As Long, ByVal lTime As Long) As Long
Declare Function me2600AOSetTrigger Lib "me2600.dll" Alias "_VBme2600AOSetTrigger@8" (ByVal lBoardnumber As Long, ByVal lModePolarity As Long) As Long
Declare Function me2600AOSetMode Lib "me2600.dll" Alias "_VBme2600AOSetMode@16" (ByVal lBoardnumber As Long, ByVal lChannel As Long, ByVal lRange As Long, ByVal lMode As Long) As Long
Declare Function me2600AOSingle Lib "me2600.dll" Alias "_VBme2600AOSingle@12" (ByVal lBoardnumber As Long, ByVal lChannel As Long, ByVal iValue As Integer) As Long
Declare Function me2600AOWrapAround Lib "me2600.dll" Alias "_VBme2600AOWrapAround@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600AOStop Lib "me2600.dll" Alias "_VBme2600AOStop@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600AOStopEx Lib "me2600.dll" Alias "_VBme2600AOStopEx@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600AOUpdate Lib "me2600.dll" Alias "_VBme2600AOUpdate@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600AOContinuous Lib "me2600.dll" Alias "_VBme2600AOContinuous@16" (ByVal lBoardnumber As Long, ByVal lMode As Long, ByVal lSize As Long, ByRef piBuffer As Integer) As Long
Declare Function me2600AOContinuousEx Lib "me2600.dll" Alias "_VBme2600AOContinuousEx@28" (ByVal lBoardnumber As Long, ByVal lMode As Long, ByVal lSize As Long, ByRef piBuffer As Integer, ByVal lLoops As Long, ByVal lDelay As Long, ByVal pCallBack As Long) As Long
Declare Function me2600DIOSetPortDirection Lib "me2600.dll" Alias "_VBme2600DIOSetPortDirection@12" (ByVal lBoardnumber As Long, ByVal lPortNo As Long, ByVal lDir As Long) As Long
Declare Function me2600DIGetBit Lib "me2600.dll" Alias "_VBme2600DIGetBit@16" (ByVal lBoardnumber As Long, ByVal lPortNo As Long, ByVal lBitNo As Long, ByRef pBitValue As Long) As Long
Declare Function me2600DIGetByte Lib "me2600.dll" Alias "_VBme2600DIGetByte@16" (ByVal lBoardnumber As Long, ByVal lPortNo As Long, ByVal lBitNo As Long, ByRef pByteValue As Long) As Long
Declare Function me2600DIGetWord Lib "me2600.dll" Alias "_VBme2600DIGetWord@12" (ByVal lBoardnumber As Long, ByVal lPortNo As Long, ByRef pValue As Long) As Long
Declare Function me2600DOSetBit Lib "me2600.dll" Alias "_VBme2600DOSetBit@16" (ByVal lBoardnumber As Long, ByVal lPortNo As Long, ByVal lBitNo As Long, ByVal lBitValue As Long) As Long
Declare Function me2600DOSetByte Lib "me2600.dll" Alias "_VBme2600DOSetByte@16" (ByVal lBoardnumber As Long, ByVal lPortNo As Long, ByVal lBitNo As Long, ByVal lByteValue As Long) As Long
Declare Function me2600DOSetWord Lib "me2600.dll" Alias "_VBme2600DOSetWord@12" (ByVal lBoardnumber As Long, ByVal lPortNo As Long, ByVal lValue As Long) As Long
Declare Function me2600DOReset Lib "me2600.dll" Alias "_VBme2600DOReset@8" (ByVal lBoardnumber As Long, ByVal lPortNo As Long) As Long
Declare Function me2600PWMStart Lib "me2600.dll" Alias "_VBme2600PWMStart@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600PWMStop Lib "me2600.dll" Alias "_VBme2600PWMStop@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600PWMSetMode Lib "me2600.dll" Alias "_VBme2600PWMSetMode@20" (ByVal lBoardnumber As Long, ByVal dFrequency As Double, ByVal lDutyCycle As Long, ByVal lInverted As Long) As Long
Declare Function me2600DisableExternalInt Lib "me2600.dll" Alias "_VBme2600DisableExternalInt@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600EnableExternalInt Lib "me2600.dll" Alias "_VBme2600EnableExternalInt@8" (ByVal lBoardnumber As Long, ByVal pCallBack As Long) As Long
Declare Function me2600CNTStart Lib "me2600.dll" Alias "_VBme2600CNTStart@8" (ByVal lBoardnumber As Long, ByVal lCounter As Long) As Long
Declare Function me2600CNTReset Lib "me2600.dll" Alias "_VBme2600CNTReset@8" (ByVal lBoardnumber As Long, ByVal lCounter As Long) As Long
Declare Function me2600CNTRead Lib "me2600.dll" Alias "_VBme2600CNTRead@12" (ByVal lBoardnumber As Long, ByVal lCounter As Long, ByRef piCounterValue As Integer) As Long
Declare Function me2600CNTSetRange Lib "me2600.dll" Alias "_VBme2600CNTSetRange@16" (ByVal lBoardnumber As Long, ByVal lCounter As Long, ByVal lEndVal As Long, ByVal lStartVal As Long) As Long
Declare Function me2600CNTInterrupt Lib "me2600.dll" Alias "_VBme2600CNTInterrupt@16" (ByVal lBoardnumber As Long, ByVal lCounter As Long, ByVal lFlag As Long, ByVal pCallBack As Long) As Long
Declare Function me2600SIOReadRegister Lib "me2600.dll" Alias "_VBme2600SIOReadRegister@8" (ByVal lBoardnumber As Long, ByVal cReg As Byte) As Byte
Declare Function me2600SIOWriteRegister Lib "me2600.dll" Alias "_VBme2600SIOWriteRegister@12" (ByVal lBoardnumber As Long, ByVal cReg As Byte, ByVal cVal As Byte) As Byte
Declare Function me2600SIOLoopBackTest Lib "me2600.dll" Alias "_VBme2600SIOLoopBackTest@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600SIOSetup Lib "me2600.dll" Alias "_VBme2600SIOSetup@20" (ByVal lBoardnumber As Long, ByVal lBaud As Long, ByVal lLen As Long, ByVal lStop As Long, ByVal cParity As Byte) As Long
Declare Function me2600SIOGetRegisters Lib "me2600.dll" Alias "_VBme2600SIOGetRegisters@8" (ByVal lBoardnumber As Long, ByRef Regs As ME2600_SIO_REGS) As Long
Declare Function me2600SIOTransmit Lib "me2600.dll" Alias "_VBme2600SIOTransmit@16" (ByVal lBoardnumber As Long, ByVal lMode As Long, ByVal lCount As Long, ByVal lpBuffer As String) As Long
Declare Function me2600SIOReceive Lib "me2600.dll" Alias "_VBme2600SIOReceive@16" (ByVal lBoardnumber As Long, ByVal lMode As Long, ByVal lCount As Long, ByVal lpBuffer As String) As Long
Declare Function me2600SIOOpen Lib "me2600.dll" Alias "_VBme2600SIOOpen@16" (ByVal lBoardnumber As Long, ByVal lMode As Long, ByVal lInbufferSize As Long, ByVal lOutBufferSize As Long) As Long
Declare Function me2600SIOClose Lib "me2600.dll" Alias "_VBme2600SIOClose@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600SIOCheckError Lib "me2600.dll" Alias "_VBme2600SIOCheckError@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600SIOClearBuffer Lib "me2600.dll" Alias "_VBme2600SIOClearBuffer@4" (ByVal lBoardnumber As Long) As Long
Declare Function me2600SIOCheckBuffer Lib "me2600.dll" Alias "_VBme2600SIOCheckBuffer@8" (ByVal lBoardnumber As Long, ByRef pSio As ME2600_SIO) As Long








' Some helper functions
'--------------------------------------------------------------------
Function MAKE_DACFIFOENTRY(ByVal lCh As Long, ByVal lValue As Long) As Long
    MAKE_DACFIFOENTRY = lCh * 4096 + (lValue And &HFFF&)
End Function

