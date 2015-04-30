Attribute VB_Name = "Declarations"
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

' Please note the following important remarks concerning the use of
' callback-functions under Visual Basic

' 1)    These functions are provided by you, the user and will be called
'       automatically by the API at the appropriate time.

' 2)    Callback-functions MUST be placed in a standard .BAS module (NOT
'       in a class module or attached to a form).

' 3)    The 'AddressOf' keyword should be used to pass the function
'       pointer to the ME3000 API routine.

' The callback-functions must have the following form:

' For me3000AIContinuous, me3000AIQuickEx, me3000AIMultipleEx, me3000AIScanEx:

'       Public Sub Callback(ByRef piBuffer() As Integer, ByVal lSize As Long)
        
'       Where piBuffer is a normal Basic array STARTING At INDEX 0 which contains
'       the acquired data and lSize is the nunber of elements in this array.
'       The data can then be addresed as follows:
'       piBuffer(0), piBuffer(1), ... piBuffer(lSize - 1)

' For me3000SingleEx

'       Public Sub Callback(ByRef piValue As Integer)

'       where piValue contains the single data value which has just been acquired

' For me3000AOContinuousEx, me3000EnableExternalInt, me3000CNTInterrupt

'       Public Sub Callback()


' Sample02 and Sample03 demonstrate the use of callback-functions
        


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

Declare Function me3000AIContinuous Lib "me3000.dll" Alias "_VBme3000AIContinuous@16" (ByVal lBoardNumber As Long, ByVal lFrameSize As Long, ByVal lBufferSize As Long, ByVal pCallBack As Long) As Long

Declare Function me3000AIStop Lib "me3000.dll" Alias "_VBme3000AIStop@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000AISingleEx Lib "me3000.dll" Alias "_VBme3000AISingleEx@28" (ByVal lBoardNumber As Long, ByVal lChannel As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByRef piBuffer As Integer, ByVal pCallBack As Long) As Long
Declare Function me3000AIQuickEx Lib "me3000.dll" Alias "_VBme3000AIQuickEx@28" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByVal pCallBack As Long) As Long
Declare Function me3000AIMultipleEx Lib "me3000.dll" Alias "_VBme3000AIMultipleEx@28" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByVal pCallBack As Long) As Long
Declare Function me3000AIScanEx Lib "me3000.dll" Alias "_VBme3000AIScanEx@32" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal lSize As Long, ByVal lCount As Long, ByVal lMode As Long, ByVal lLoops As Long, ByVal lDelay As Long, ByVal pCallBack As Long) As Long

Declare Function me3000AIClearDataFIFO Lib "me3000.dll" Alias "_VBme3000AIClearDataFIFO@4" (ByVal lBoardNumber As Long) As Long
Declare Function me3000AIReadFIFO Lib "me3000.dll" Alias "_VBme3000AIReadFIFO@12" (ByVal lBoardNumber As Long, ByRef piBuffer As Integer, ByVal iCount As Long) As Long
Declare Function me3000AIStartByExternalTrigger Lib "me3000.dll" Alias "_VBme3000AIStartByExternalTrigger@8" (ByVal lBoardNumber As Long, ByVal iModePolarity As Long) As Long

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








' Some helper functions
'--------------------------------------------------------------------
Function MAKE_DACFIFOENTRY(ByVal lCh As Long, ByVal lValue As Long) As Long
    MAKE_DACFIFOENTRY = lCh * 4096 + (lValue And &HFFF&)
End Function

