{ File Name 'medefs.pas'  }
{ Defines for MEILHAUS 32-bit board drivers }


unit medefs;

interface

{ General Type Definitions }
const PORTA=0;
const PORTB=1;
const PORTC=2;
const PORTCL=3;
const PORTCH=4;
const PORTD=8;
const PORTE=9;
const PORTF=10;
const PORTFL=11;
const PORTFH=12;

const MEINPUT = 0;
const MEOUTPUT = 1;

const IN32=0;
const OUT32=1;
const IN16=2;
const OUT16=3;
const INOUT16=4;


{ ME-14A Register Set }
const ME14_PORT_A           = $00;
const ME14_PORT_B           = $01;
const ME14_PORT_C           = $02;
const ME14_PORT_CONTROL     = $03;
const ME14_TIMER_0          = $04;
const ME14_TIMER_1          = $05;
const ME14_TIMER_2          = $06;
const ME14_TIMER_CONTROL        = $07;

{ ME-14B Register Set }
const ME14_PORT_BA          = $08;
const ME14_PORT_BB          = $09;
const ME14_PORT_BC          = $0A;
const ME14_PORT_BCONTROL        = $0B;
const ME14_TIMER_B0         = $0C;
const ME14_TIMER_B1         = $0D;
const ME14_TIMER_B2         = $0E;
const ME14_TIMER_BCONTROL   = $0F;

{ ME-1400A Register Set }
const ME1400_PORT_A         = $00;
const ME1400_PORT_B         = $01;
const ME1400_PORT_C         = $02;
const ME1400_PORT_CONTROL       = $03;
const ME1400_TIMER_0            = $04;
const ME1400_TIMER_1            = $05;
const ME1400_TIMER_2            = $06;
const ME1400_TIMER_CONTROL      = $07;

{ ME-1400B Register Set }
const ME1400_PORT_BA            = $08;
const ME1400_PORT_BB            = $09;
const ME1400_PORT_BC            = $0A;
const ME1400_PORT_BCONTROL      = $0B;
const ME1400_TIMER_B0           = $0C;
const ME1400_TIMER_B1           = $0D;
const ME1400_TIMER_B2           = $0E;
const ME1400_TIMER_BCONTROL = $0F;

const ME1400_TIMERINTERNCLOCK_10MHZ   = $08;
const ME1400_TIMERINTERNCLOCK_1MHZ    = $00;

const ME1400_TIMERCLOCKSOURCE0_SUBD   = $00;
const ME1400_TIMERCLOCKSOURCE0_INTERN = $04;
const ME1400_TIMERCLOCKSOURCE1_SUBD   = $00;
const ME1400_TIMERCLOCKSOURCE1_OUT0   = $02;
const ME1400_TIMERCLOCKSOURCE2_SUBD   = $00;
const ME1400_TIMERCLOCKSOURCE2_OUT1   = $01;

const ME1400_MULTIPIN_IRQ             = $00;
const ME1400_MULTIPIN_INTERNALCLOCK   = $01;





{ ME-26 Register Set }
const ME26_ADDATL           = $00;  {R}
const ME26_ADDSR            = $01;  {R}
const ME26_CR_CONTROL       = $01;  {W}
const ME26_ADCCR            = $02;  {RW}
const ME26_AD_START         = $02;  {RW}
const ME26_FID              = $03;  {R}
const ME26_ADMDE            = $03;  {W}
const ME26_TIMER0           = $04;
const ME26_TIMER1           = $05;
const ME26_TIMER2           = $06;
const ME26_TIMERCONTROL     = $07;

{ ME-63 Register Set }
const ME63_RESET            = $00;
const ME63_RELAIS_OUTA      = $01;
const ME63_RELAIS_OUTB      = $02;
const ME63_TTL_INPUT        = $03;

{ ME-80 / ME-81 Register Set }
const ME8x_ID_REGISTER      = $00; {R}
const ME8x_CONTROL          = $00; {W}
const ME8x_RESET_INT        = $02;

const ME80_DIO_WORD_A       = $04;
const ME80_DIO_WORD_B       = $06;
const ME80_PATTERN_WORDA        = $08;
const ME80_PATTERN_WORDB        = $0A;

const ME81_INPUT_WORD       = $04;
const ME81_OUTPUT_WORD      = $06;
const ME81_PATTERN_WORD     = $08;
const ME81_MASK_WORD        = $0A;
const ME81_INT_STATUS       = $0A;

{ ME-94 Register Set }
const ME94_PORT_A           = $00;  {R}
const ME94_PORT_B           = $01;  {R}
const ME94_PORT_C           = $02;  {R}
const ME94_PORT_CONTROL     = $03;  {W}

{ ME-95 Register Set }
const ME95_OUTPUT_A         = $00;  {W}
const ME95_OUTPUT_B         = $01;  {W}

{ ME-96 Register Set }
const ME96_PORT_A           = $00;  {W}
const ME96_PORT_B           = $01;  {R}
const ME96_PORT_C           = $02;  {R}
const ME96_PORT_CONTROL     = $03;  {W}

{ ME-160 Register Set }
const ME160_PRELOAD_A       = $00;
const ME160_PRELOAD_B       = $02;
const ME160_PRELOAD_C       = $04;
const ME160_PRELOAD_D       = $06;
const ME160_UPDATE_DAC      = $08;
const ME160_UPDATE_MODE     = $09;
const ME160_UPDATE_ALL      = $0A;
const ME160_CONTROL         = $0B;
const ME160_PRELOAD_MODE        = $0C;

{ ME-270 Register Set }
    { 8-Bit Register }
const ME270_FID         = $00;   {R}
const ME270_CONTROL         = $01;   {W}
const ME270_STATUS          = $01;   {R}
const ME270_AD_START        = $02;  {W}
const ME270_AD_LOWBYTE      = $02;  {R}
const ME270_AD_HIGHBYTE     = $03;  {R}
const ME270_UPDATE_DA       = $04;  {R}
const ME270_PRELOAD_A_LOWB  = $04;  {W}
const ME270_PRELOAD_A_HIGHB = $05;  {W}
const ME270_PRELOAD_B_LOWB  = $06;  {W}
const ME270_PRELOAD_B_HIGHB = $07;  {W}
const ME270_TIMER0          = $08;  {RW}
const ME270_TIMER1          = $09;  {RW}
const ME270_TIMER2          = $0A;  {RW}
const ME270_TIMERCONTROL        = $0B;  {RW}
const ME270_PORT_A          = $0C;  {RW}
const ME270_PORT_B          = $0D;  {RW}
const ME270_PORT_C          = $0E;  {RW}
const ME270_PORT_CONTROL        = $0F;  {RW}

{ ME-300 Register Set }
    { 8-Bit Register }
const ME300_FID         = $00;   {R}
const ME300_ADSTART         = $00;   {W}
const ME300_STATUS          = $01;   {R}
const ME300_CONTROL1        = $01;   {W}
const ME300_RESETINT        = $02;   {R}
const ME300_CONTROL2        = $02;   {W}
const ME300_KANALLISTE      = $03;
const ME300_TIMER0DATA      = $04;
const ME300_TIMER1DATA      = $05;
const ME300_TIMER2DATA      = $06;
const ME300_TIMERCONTROL        = $07;
const ME300_DIGITAL_A       = $08;
const ME300_DIGITAL_B       = $09;
const ME300_DIGITAL_C       = $0A;
    { 16-Bit Register }
const ME300_FIFO                = $10;
const ME300_DA_CONTROL      = $14;
const ME300_DA_DATA_A       = $18;
const ME300_DA_DATA_B       = $1A;
const ME300_DA_DATA_C       = $1C;
const ME300_DA_DATA_D       = $1E;



{ Analog Input Ranges }
const AI_MINUS_10           = $00;
const AI_MINUS_5            = $10;
const AI_MINUS_2            = $20;
const AI_MINUS_1            = $30;
const AI_PLUS_10            = $40;
const AI_PLUS_5         = $50;
const AI_PLUS_2         = $60;
const AI_PLUS_1         = $70;

{ Trigger modes for ME-26 }
const AI26_TRIGGER_TIMER    = $02;
const AI26_TRIGGER_EXT_LOW  = $06;
const AI26_TRIGGER_EXT_HIGH     = $0E;

{ Trigger modes for ME-270 }
const AI270_TRIGGER_TIMER   = $02;
const AI270_TRIGGER_EXT_LOW = $06;
const AI270_TRIGGER_EXT_HIGH = $0E;

{ Trigger modes for ME-300 }
const AI300_TRIGGER_TIMER   = $02;
const AI300_TRIGGER_EXT_LOW = $03;
const AI300_TRIGGER_EXT_HIGH = $13;

{ Interrupt Modes for ME-8x }
const NO_INTERRUPT      = $00;
const INT_IF_PATTERN        = $20;
const INT_IF_MASK       = $60;
const INT_EXTERN        = $60;

{ Latch Modes for ME-80 }
const REGMODE_DIRECT    = $00;
const REGMODE_INTERNAL  =$01;
const REGMODE_EXTERNAL  =$10;

{ Scan Modes }
const SCAN_SINGLE       = $01;
const SCAN_INFINITE     = $02;
const SCAN_STREAMER = $10;

{ Data Buffer Access }
const FILE_BEGIN        = $00;
const FILE_CURRENT      = $01;
const FILE_END          = $02;

{ Analog Output Ranges }
const AO_PLUS_10        = $00;     { 0-10V }
const AO_MINUS_5        = $01;     { ±5V }
const AO_PLUS_5     = $02;     { 0-5V }
const AO_MINUS_10       = $03;     { ±10V }

{ Analog Output Modes for ME-160/x }
const AO_BUFFERED       = $00;
const AO_TRANSPARENT    = $01;

{ Analog I/O DAC Names for ME-160/x }
const CH0_3         = $00;
const CH4_7         = $01;
const CH8_11            = $02;
const CH12_15           = $03;


implementation

end.

