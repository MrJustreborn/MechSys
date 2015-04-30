Attribute VB_Name = "Module2"
' file meDefs.bas'
' for MEILHAUS 32-bit board drivers'


' general definition'

' maximum number of boards
Global Const ME_MAX_DEVICES = 32

' board identifier
Global Const BOARD_0 = 0
Global Const BOARD_1 = 1
Global Const BOARD_2 = 2
Global Const BOARD_3 = 3
Global Const BOARD_4 = 4
Global Const BOARD_5 = 5
Global Const BOARD_6 = 6
Global Const BOARD_7 = 7
Global Const BOARD_8 = 8
Global Const BOARD_9 = 9
Global Const BOARD_10 = 10
Global Const BOARD_11 = 11
Global Const BOARD_12 = 12
Global Const BOARD_13 = 13
Global Const BOARD_14 = 14
Global Const BOARD_15 = 15
Global Const BOARD_16 = 16
Global Const BOARD_17 = 17
Global Const BOARD_18 = 18
Global Const BOARD_19 = 19
Global Const BOARD_20 = 20
Global Const BOARD_21 = 21
Global Const BOARD_22 = 22
Global Const BOARD_23 = 23
Global Const BOARD_24 = 24
Global Const BOARD_25 = 25
Global Const BOARD_26 = 26
Global Const BOARD_27 = 27
Global Const BOARD_28 = 28
Global Const BOARD_29 = 29
Global Const BOARD_30 = 30
Global Const BOARD_31 = 31



' ME-1400 (ME-14)
'--------------------------------------------------------------------

'Initialisation Register Set'
Global Const ME1400_TIMERINTERNCLOCK_10MHZ = &H8
Global Const ME1400_TIMERINTERNCLOCK_1MHZ = &H0

Global Const ME1400_TIMERCLOCKSOURCE0_SUBD = &H0
Global Const ME1400_TIMERCLOCKSOURCE0_INTERN = &H4
Global Const ME1400_TIMERCLOCKSOURCE1_SUBD = &H0
Global Const ME1400_TIMERCLOCKSOURCE1_OUT0 = &H2
Global Const ME1400_TIMERCLOCKSOURCE2_SUBD = &H0
Global Const ME1400_TIMERCLOCKSOURCE2_OUT1 = &H1

Global Const ME1400_MULTIPIN_IRQ = &H0
Global Const ME1400_MULTIPIN_INTERNALCLOCK = &H1

Global Const ME1400_PORTA = 0
Global Const ME1400_PORTB = 1
Global Const ME1400_PORTC = 2
Global Const ME1400_PORTCL = 3
Global Const ME1400_PORTCH = 4
Global Const ME1400_PORTD = 8
Global Const ME1400_PORTE = 9
Global Const ME1400_PORTF = 10
Global Const ME1400_PORTFL = 11
Global Const ME1400_PORTFH = 12

Global Const ME1400_INPUT = 0
Global Const ME1400_OUTPUT = 1

Global Const IN32 = 0
Global Const OUT32 = 1
Global Const IN16 = 2
Global Const OUT16 = 3
Global Const INOUT16 = 4

' ME-14A Register Set '

Global Const ME14_PORT_A = &H0
Global Const ME14_PORT_B = &H1
Global Const ME14_PORT_C = &H2
Global Const ME14_PORT_CONTROL = &H3
Global Const ME14_TIMER_0 = &H4
Global Const ME14_TIMER_1 = &H5
Global Const ME14_TIMER_2 = &H6
Global Const ME14_TIMER_CONTROL = &H7

' ME-14B Register Set '

Global Const ME14_PORT_BA = &H8
Global Const ME14_PORT_BB = &H9
Global Const ME14_PORT_BC = &HA
Global Const ME14_PORT_BCONTROL = &HB
Global Const ME14_TIMER_B0 = &HC
Global Const ME14_TIMER_B1 = &HD
Global Const ME14_TIMER_B2 = &HE
Global Const ME14_TIMER_BCONTROL = &HF


' ME-14A Register Set '

Global Const ME1400_PORT_A = &H0
Global Const ME1400_PORT_B = &H1
Global Const ME1400_PORT_C = &H2
Global Const ME1400_PORT_CONTROL = &H3
Global Const ME1400_TIMER_0 = &H4
Global Const ME1400_TIMER_1 = &H5
Global Const ME1400_TIMER_2 = &H6
Global Const ME1400_TIMER_CONTROL = &H7

' ME-14B Register Set '

Global Const ME1400_PORT_BA = &H8
Global Const ME1400_PORT_BB = &H9
Global Const ME1400_PORT_BC = &HA
Global Const ME1400_PORT_BCONTROL = &HB
Global Const ME1400_TIMER_B0 = &HC
Global Const ME1400_TIMER_B1 = &HD
Global Const ME1400_TIMER_B2 = &HE
Global Const ME1400_TIMER_BCONTROL = &HF



' ME-1600
'--------------------------------------------------------------------

' Analog Output Ranges
Global Const AO1600_UNIPOLAR = 0  ' 0-10 Volt
Global Const AO1600_BIPOLAR = 1   ' ± 10 Volt

' Analog Output Modes
Global Const AO1600_BUFFERED = 0
Global Const AO1600_TRANSPARENT = 1

' Channel Group
Global Const AO1600_GROUP_A = 0 ' 0-3
Global Const AO1600_GROUP_B = 1 ' 4-7
Global Const AO1600_GROUP_C = 2 ' 8-11
Global Const AO1600_GROUP_D = 3 ' 12-15

' Channel
Global Const AO1600_CH00 = &H0
Global Const AO1600_CH01 = &H1
Global Const AO1600_CH02 = &H2
Global Const AO1600_CH03 = &H3
Global Const AO1600_CH04 = &H4
Global Const AO1600_CH05 = &H5
Global Const AO1600_CH06 = &H6
Global Const AO1600_CH07 = &H7
Global Const AO1600_CH08 = &H8
Global Const AO1600_CH09 = &H9
Global Const AO1600_CH10 = &HA
Global Const AO1600_CH11 = &HB
Global Const AO1600_CH12 = &HC
Global Const AO1600_CH13 = &HD
Global Const AO1600_CH14 = &HE
Global Const AO1600_CH15 = &HF



' ME-8100
'--------------------------------------------------------------------

' Register sets
Global Const REGISTER_SET_A = 0
Global Const REGISTER_SET_B = 1

' Source/Sink Mode
Global Const SINK_MODE = 0
Global Const SOURCE_MODE = 1





' port direction
Global Const MEINPUT = 0
Global Const MEOUTPUT = 1

' port identifier
Global Const PORTA = 0
Global Const PORTB = 1
Global Const PORTC = 2
Global Const PORTD = 3

' word identifier
Global Const WORD_0 = 0
Global Const WORD_1 = 1

' byte identifier
Global Const BYTE_0 = 0
Global Const BYTE_1 = 1
Global Const BYTE_2 = 2
Global Const BYTE_3 = 3

' bit identifier
Global Const BIT_0 = 0
Global Const BIT_1 = 1
Global Const BIT_2 = 2
Global Const BIT_3 = 3
Global Const BIT_4 = 4
Global Const BIT_5 = 5
Global Const BIT_6 = 6
Global Const BIT_7 = 7
Global Const BIT_8 = 8
Global Const BIT_9 = 9
Global Const BIT_10 = 10
Global Const BIT_11 = 11
Global Const BIT_12 = 12
Global Const BIT_13 = 13
Global Const BIT_14 = 14
Global Const BIT_15 = 15
Global Const BIT_16 = 16
Global Const BIT_17 = 17
Global Const BIT_18 = 18
Global Const BIT_19 = 19
Global Const BIT_20 = 20
Global Const BIT_21 = 21
Global Const BIT_22 = 22
Global Const BIT_23 = 23
Global Const BIT_24 = 24
Global Const BIT_25 = 25
Global Const BIT_26 = 26
Global Const BIT_27 = 27
Global Const BIT_28 = 28
Global Const BIT_29 = 29
Global Const BIT_30 = 30
Global Const BIT_31 = 31


'General types definition'





' ME-63 Register Set '

Global Const ME63_RESET = &H0
Global Const ME63_RELAIS_OUTA = &H1
Global Const ME63_RELAIS_OUTB = &H2
Global Const ME63_TTL_INPUT = &H3

' ME-80/81 Register Set '

Global Const ME8x_ID_REGISTER = &H0
Global Const ME8x_CONTROL = &H0
Global Const ME8x_RESET_INT = &H2

Global Const ME80_DIO_WORD_A = &H4
Global Const ME80_DIO_WORD_B = &H6
Global Const ME80_PATTERN_WORDA = &H8
Global Const ME80_PATTERN_WORDB = &HA

Global Const ME81_INPUT_WORD = &H4
Global Const ME81_OUTPUT_WORD = &H6
Global Const ME81_PATTERN_WORD = &H8
Global Const ME81_MASK_WORD = &HA
Global Const ME81_INT_STATUS = &HA

' ME-94 Register Set '
Global Const ME94_PORT_A = &H0
Global Const ME94_PORT_B = &H1
Global Const ME94_PORT_C = &H2
Global Const ME94_PORT_CONTROL = &H3

' ME-95 Register Set '
Global Const ME95_OUTPUT_A = &H0
Global Const ME95_OUTPUT_B = &H1

' ME-96 Register Set '
Global Const ME96_PORT_A = &H0
Global Const ME96_PORT_B = &H1
Global Const ME96_PORT_C = &H2
Global Const ME96_PORT_CONTROL = &H3

' ME-26 Register Set '
Global Const ME26_ADDATL = &H0
Global Const ME26_ADDSR = &H1   'R'
Global Const ME26_CR_CONTROL = &H1      'W'
Global Const ME26_ADCCR = &H2   'RW'
Global Const ME26_AD_START = &H2        'RW'
Global Const ME26_FID = &H3     'R'
Global Const ME26_ADMDE = &H3   'W'
Global Const ME26_TIMER0 = &H4
Global Const ME26_TIMER1 = &H5
Global Const ME26_TIMER2 = &H6
Global Const ME26_TIMERCONTROL = &H7

' ME-160 Register Set '

Global Const ME160_PRELOAD_A = &H0
Global Const ME160_PRELOAD_B = &H2
Global Const ME160_PRELOAD_C = &H4
Global Const ME160_PRELOAD_D = &H6
Global Const ME160_UPDATE_DAC = &H8
Global Const ME160_UPDATE_MODE = &H9
Global Const ME160_UPDATE_ALL = &HA
Global Const ME160_CONTROL = &HB
Global Const ME160_PRELOAD_MODE = &HC

' ME-270 Register Set '
        '8-Bit Register'
Global Const ME270_FID = &H0
Global Const ME270_CONTROL = &H1        'W'
Global Const ME270_STATUS = &H1 'R'
Global Const ME270_AD_START = &H2       'W'
Global Const ME270_AD_LOWBYTE = &H2     'R'
Global Const ME270_AD_HIGHBYTE = &H3    'R'
Global Const ME270_UPDATE_DA = &H4      'R'
Global Const ME270_PRELOAD_A_LOWB = &H4 'W'
Global Const ME270_PRELOAD_A_HIGHB = &H5        'W'
Global Const ME270_PRELOAD_B_LOWB = &H6 'W'
Global Const ME270_PRELOAD_B_HIGHB = &H7        'W'
Global Const ME270_TIMER0 = &H8 'RW'
Global Const ME270_TIMER1 = &H9 'RW'
Global Const ME270_TIMER2 = &HA 'RW'
Global Const ME270_TIMERCONTROL = &HB  'RW'
Global Const ME270_PORT_A = &HC 'RW'
Global Const ME270_PORT_B = &HD 'RW'
Global Const ME270_PORT_C = &HE 'RW'
Global Const ME270_PORT_CONTROL = &HF   'RW'

' ME-260/260D/300 Register Set '
        '8-Bit Register'

Global Const ME300_FID = &H0    'R'
Global Const ME300_ADSTART = &H0        'W'
Global Const ME300_STATUS = &H1 'R'
Global Const ME300_CONTROL1 = &H1       'W'
Global Const ME300_RESETINT = &H2       'R'
Global Const ME300_CONTROL2 = &H2       'W'
Global Const ME300_KANALLISTE = &H3
Global Const ME300_TIMER0DATA = &H4
Global Const ME300_TIMER1DATA = &H5
Global Const ME300_TIMER2DATA = &H6
Global Const ME300_TIMERCONTROL = &H7
Global Const ME300_DIGITAL_A = &H8
Global Const ME300_DIGITAL_B = &H9
Global Const ME300_DIGITAL_C = &HA
        '16-Bit register'
Global Const ME300_FIFO = &H10
Global Const ME300_DA_CONTROL = &H14
Global Const ME300_DA_DATA_A = &H18
Global Const ME300_DA_DATA_B = &H1A
Global Const ME300_DA_DATA_C = &H1C
Global Const ME300_DA_DATA_D = &H1E


' Analog Input Ranges for ME-300 '
Global Const AI_MINUS_10 = &H0
Global Const AI_MINUS_5 = &H10
Global Const AI_MINUS_2 = &H20
Global Const AI_MINUS_1 = &H30
Global Const AI_PLUS_10 = &H40
Global Const AI_PLUS_5 = &H50
Global Const AI_PLUS_2 = &H60
Global Const AI_PLUS_1 = &H70

' Trigger Modes for ME-26 '
Global Const AI26_TRIGGER_TIMER = &H2
Global Const AI26_TRIGGER_EXT_LOW = &H6
Global Const AI26_TRIGGER_EXT_HIGH = &HE

' Trigger Modes for ME-270 '
Global Const AI270_TRIGGER_TIMER = &H2
Global Const AI270_TRIGGER_EXT_LOW = &H6
Global Const AI270_TRIGGER_EXT_HIGH = &HE

' Trigger Modes for ME-300 '
Global Const AI300_TRIGGER_TIMER = &H2
Global Const AI300_TRIGGER_EXT_LOW = &H3
Global Const AI300_TRIGGER_EXT_HIGH = &H13

' Interrupt Modes for ME-8x '
Global Const NO_INTERRUPT = &H10
Global Const INT_IF_PATTERN = &H20
Global Const INT_IF_MASK = &H60
Global Const INT_EXTERN = &H60

' Latch Modes for ME-80 '
Global Const REGMODE_DIRECT = &H0
Global Const REGMODE_INTERNAL = &H1
Global Const REGMODE_EXTERNAL = &H10

' Scan Modes '
Global Const SCAN_SINGLE = &H1
Global Const SCAN_INFINITE = &H2
Global Const SCAN_STREAMER = &H10

' Data Buffer Access '
Global Const FILE_BEGIN = &H0
Global Const FILE_CURRENT = &H1
Global Const FILE_END = &H2

'Analog Output Ranges '
Global Const AO_PLUS_10 = &H0
Global Const AO_MINUS_5 = &H1
Global Const AO_PLUS_5 = &H2
Global Const AO_MINUS_10 = &H3

'Analog Output Modes for ME-160/x '
Global Const AO_BUFFERED = &H0
Global Const AO_TRANSPARENT = &H1

'Analog I/O DAC Names for ME-160/x '
Global Const CH0_3 = &H0
Global Const CH4_7 = &H1
Global Const CH8_11 = &H2
Global Const CH12_15 = &H3
