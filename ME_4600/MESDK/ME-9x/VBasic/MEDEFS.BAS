' File medefs.bas'
' for MEILHAUS 32-bit Board Drivers'


Attribute VB_Name = "Module2"
'General types definition'

Global Const PORTA = 0
Global Const PORTB = 1
Global Const PORTC = 2
Global Const PORTCL = 3
Global Const PORTCH = 4
Global Const PORTD = 8
Global Const PORTE = 9
Global Const PORTF = 10
Global Const PORTFL = 11
Global Const PORTFH = 12

Global Const MEINPUT = 0
Global Const MEOUTPUT = 1

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
Global Const AI26_TRIGGER_TIMER = &H02
Global Const AI26_TRIGGER_EXT_LOW = &H06
Global Const AI26_TRIGGER_EXT_HIGH = &H0E

' Trigger Modes for ME-270 '
Global Const AI270_TRIGGER_TIMER = &H02
Global Const AI270_TRIGGER_EXT_LOW = &H06
Global Const AI270_TRIGGER_EXT_HIGH = &H0E

' Trigger Modes for ME-300 '
Global Const AI300_TRIGGER_TIMER = &H02
Global Const AI300_TRIGGER_EXT_LOW = &H03
Global Const AI300_TRIGGER_EXT_HIGH = &H13

' Interrupt Modes for ME-8x '
Global Const NO_INTERRUPT = &H10
Global Const INT_IF_PATTERN = &H20
Global Const INT_IF_MASK = &H60
Global Const INT_EXTERN = &H60

' Latch Modes for ME-80 '
Global Const REGMODE_DIRECT	= &H00
Global Const REGMODE_INTERNAL	=&H01
Global Const REGMODE_EXTERNAL	=&H10

' Scan Modes '
Global Const SCAN_SINGLE = &H01
Global Const SCAN_INFINITE = &H02
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
Global Const CH0_3	=&H00
Global Const CH4_7	=&H01
Global Const CH8_11	=&H02
Global Const CH12_15	=&H03





















