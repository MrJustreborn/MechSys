/*
M e i l h a u s   i n t e r n a l   r e m a r k :
-------------------------------------------------
This is a copy of the same file in _osi directory
Please make all changes in the original file
*/

#ifndef MEDEFS_H
#define MEDEFS_H

// Maximum number of Boards
#define ME_MAX_DEVICES      32


typedef void (_stdcall *ME_PSERVICE_PROC) (int i_context);
typedef void (_stdcall *PSERVICE_PROC) (void);

// general type definitions
typedef enum _PORTNAME {
    PORTA=0,
    PORTB=1,
    PORTC=2,
    PORTCL=3,
    PORTCH=4,
    PORTD=8,
    PORTE=9,
    PORTF=10,
    PORTFL=11,
    PORTFH=12
} PORTNAME;

typedef enum _PORTTYPE {
    MEINPUT = 0,
    MEOUTPUT = 1
} PORTTYPE;

typedef enum _PORTMODE {
    IN32=0,
    OUT32=1,
    IN16=2,
    OUT16=3,
    INOUT16=4
} PORTMODE;

typedef void (_stdcall *PSERVICE_PROC) (void);

// ME1400A Register Set
#define ME1400_PORT_A           0x00
#define ME1400_PORT_B           0x01
#define ME1400_PORT_C           0x02
#define ME1400_PORT_CONTROL     0x03
#define ME1400_TIMER_0          0x04
#define ME1400_TIMER_1          0x05
#define ME1400_TIMER_2          0x06
#define ME1400_TIMER_CONTROL    0x07

// ME14B Register Set
#define ME1400_PORT_BA          0x08
#define ME1400_PORT_BB          0x09
#define ME1400_PORT_BC          0x0A
#define ME1400_PORT_BCONTROL    0x0B
#define ME1400_TIMER_B0         0x0C
#define ME1400_TIMER_B1         0x0D
#define ME1400_TIMER_B2         0x0E
#define ME1400_TIMER_BCONTROL   0x0F

// Initialisation Register Set
#define PartA(X)    (X>>4)
#define PartB(X)    (X>>0)
#define ME1400_TIMERINTERNCLOCK_10MHZ   0x08
#define ME1400_TIMERINTERNCLOCK_1MHZ    0x00

#define ME1400_TIMERCLOCKSOURCE0_SUBD   0x00
#define ME1400_TIMERCLOCKSOURCE0_INTERN 0x04
#define ME1400_TIMERCLOCKSOURCE1_SUBD   0x00
#define ME1400_TIMERCLOCKSOURCE1_OUT0   0x02
#define ME1400_TIMERCLOCKSOURCE2_SUBD   0x00
#define ME1400_TIMERCLOCKSOURCE2_OUT1   0x01

#define ME1400_MULTIPIN_IRQ             0x00
#define ME1400_MULTIPIN_INTERNALCLOCK   0x01

typedef struct structDeviceInfoStruct
{
    DWORD   dwBoardNumber;          // Board number of Board
    DWORD   dwVendorID;             // PCI vendor ID
    DWORD   dwDeviceID;             // PCI device ID
    DWORD   dwSystemSlotNumber;     // Slot number in PCI bus
    DWORD   dwPortBase;             // base port address
    DWORD   dwPortCount;            // Count of I/O addresses used.
    DWORD   dwIntChannel;           // first Interrupt Channel
    DWORD   dwPortBasePLX;          // base port address
    DWORD   dwPortCountPLX;         // Count of I/O addresses used.
    DWORD   dwSerialNumber;         // Serial number of the board
    DWORD   dwBusNumber;            // Bus number of the PCI bus (in most cases 0)
    DWORD   dwHWRevision;           // hardware revision of board
    DWORD   dwIrqCnt;               // number of interrupts
    DWORD   dwVersion;              // which board of the board family

} DEVICEINFOSTRUCT, *PDEVICEINFOSTRUCT;


// ME14A Register Set
#define ME14_PORT_A         0x00
#define ME14_PORT_B         0x01
#define ME14_PORT_C         0x02
#define ME14_PORT_CONTROL   0x03
#define ME14_TIMER_0        0x04
#define ME14_TIMER_1        0x05
#define ME14_TIMER_2        0x06
#define ME14_TIMER_CONTROL  0x07

// ME14B Register Set
#define ME14_PORT_BA        0x08
#define ME14_PORT_BB        0x09
#define ME14_PORT_BC        0x0A
#define ME14_PORT_BCONTROL  0x0B
#define ME14_TIMER_B0       0x0C
#define ME14_TIMER_B1       0x0D
#define ME14_TIMER_B2       0x0E
#define ME14_TIMER_BCONTROL 0x0F

// ME63 Register Set
#define ME63_RESET          0x00
#define ME63_RELAIS_1       0x01
#define ME63_RELAIS_2       0x02
#define ME63_INPUTS         0x03

#define ME63_RELAIS_OUTA    0x01   //W
#define ME63_RELAIS_OUTB    0x02   //W
#define ME63_TTL_INPUT      0x03   //R


// ME80 / ME81 Register Set
#define ME8x_ID_REGISTER    0x00
#define ME8x_CONTROL        0x00
#define ME8x_RESET_INT      0x02

#define ME80_DIO_WORD_A     0x04
#define ME80_DIO_WORD_B     0x06
#define ME80_PATTERN_WORDA  0x08
#define ME80_PATTERN_WORDB  0x0A

#define ME81_INPUT_WORD     0x04
#define ME81_OUTPUT_WORD    0x06
#define ME81_PATTERN_WORD   0x08
#define ME81_MASK_WORD      0x0A
#define ME81_INT_STATUS     0x0A

// ME160 Register Set
#define ME160_PRELOAD_A     0x00
#define ME160_PRELOAD_B     0x02
#define ME160_PRELOAD_C     0x04
#define ME160_PRELOAD_D     0x06
#define ME160_UPDATE_DAC    0x08
#define ME160_UPDATE_MODE   0x09
#define ME160_UPDATE_ALL    0x0A
#define ME160_CONTROL       0x0B
#define ME160_PRELOAD_MODE  0x0C

// ME300 Register Set
    // 8-Bit Register
#define ME300_FID           0x00   //R
#define ME300_ADSTART       0x00   //W
#define ME300_STATUS        0x01   //R
#define ME300_CONTROL1      0x01   //W
#define ME300_RESETINT      0x02   //R
#define ME300_CONTROL2      0x02   //W
#define ME300_KANALLISTE    0x03
#define ME300_TIMER0DATA    0x04
#define ME300_TIMER1DATA    0x05
#define ME300_TIMER2DATA    0x06
#define ME300_TIMERCONTROL  0x07
#define ME300_DIGITAL_A     0x08
#define ME300_DIGITAL_B     0x09
#define ME300_DIGITAL_C     0x0A
    // 16-Bit Register
#define ME300_FIFO          0x10
#define ME300_DA_CONTROL    0x14
#define ME300_DA_DATA_A     0x18
#define ME300_DA_DATA_B     0x1A
#define ME300_DA_DATA_C     0x1C
#define ME300_DA_DATA_D     0x1E

// ME270 Register Set
// 8-Bit Register
#define ME270_FID           0x00   //R
#define ME270_CONTROL       0x01   //W
#define ME270_STATUS        0x01   //R
#define ME270_AD_START      0x02  //W
#define ME270_AD_LOWBYTE    0x02  //R
#define ME270_AD_HIGHBYTE   0x03  //R
#define ME270_UPDATE_DA     0x04  //R
#define ME270_PRELOAD_A_LOWB    0x04  //W
#define ME270_PRELOAD_A_HIGHB   0x05  //W
#define ME270_PRELOAD_B_LOWB    0x06  //W
#define ME270_PRELOAD_B_HIGHB   0x07  //W
#define ME270_TIMER0        0x08  //RW
#define ME270_TIMER1        0x09  //RW
#define ME270_TIMER2        0x0A  //RW
#define ME270_TIMERCONTROL  0x0B  //RW
#define ME270_PORT_A        0x0C  //RW
#define ME270_PORT_B        0x0D  //RW
#define ME270_PORT_C        0x0E  //RW
#define ME270_PORT_CONTROL  0x0F  //RW

// ME26 Register Set
#define ME26_ADDATL         0x00  //R
#define ME26_ADDSR          0x01  //R
#define ME26_CR_CONTROL     0x01  //W
#define ME26_ADCCR          0x02  //RW
#define ME26_AD_START       0x02  //RW
#define ME26_FID            0x03  //R
#define ME26_ADMDE          0x03  //W
#define ME26_TIMER0         0x04
#define ME26_TIMER1         0x05
#define ME26_TIMER2         0x06
#define ME26_TIMERCONTROL   0x07

// ME94 Register Set
#define ME94_PORT_A         0x00  //R
#define ME94_PORT_B         0x01  //R
#define ME94_PORT_C         0x02  //R
#define ME94_PORT_CONTROL   0x03  //W

// ME95 Register Set
#define ME95_OUTPUT_A       0x00  //W
#define ME95_OUTPUT_B       0x01  //W

// ME96 Register Set
#define ME96_PORT_A         0x00  //W
#define ME96_PORT_B         0x01  //R
#define ME96_PORT_C         0x02  //R
#define ME96_PORT_CONTROL   0x03  //W

// Analog Output Ranges for me160 / me300 family
#define AO_PLUS_10          0     //   0V ..  10V
#define AO_PLUS_5           2     //   0V ..   5V
#define AO_MINUS_5          1     // - 5V .. + 5V
#define AO_MINUS_10         3     // -10V .. +10V

// Analog Output Modes for me160
#define AO_BUFFERED         0
#define AO_TRANSPARENT      1

// Analog I/O DAC Names for me160
#define CH0_3               0
#define CH4_7               1
#define CH8_11              2
#define CH12_15             3

// Analog Input Ranges for me300 family
#define AI_PLUS_10          0x40
#define AI_PLUS_5           0x50
#define AI_PLUS_2           0x60
#define AI_PLUS_1           0x70
#define AI_MINUS_10         0x00
#define AI_MINUS_5          0x10
#define AI_MINUS_2          0x20
#define AI_MINUS_1          0x30

// Trigger modes me300/me260/me260d
#define AI300_TRIGGER_TIMER     0x02
#define AI300_TRIGGER_EXT_LOW   0x03
#define AI300_TRIGGER_EXT_HIGH  0x13

// Trigger modes me270
#define AI270_TRIGGER_TIMER     0x02
#define AI270_TRIGGER_EXT_LOW   0x06
#define AI270_TRIGGER_EXT_HIGH  0x0E

// Trigger modes me26
#define AI26_TRIGGER_TIMER      0x00
#define AI26_TRIGGER_EXT_LOW    0x50
#define AI26_TRIGGER_EXT_HIGH   0x10

// Interrupt Modes for me8x
#define NO_INTERRUPT        0x0000
#define INT_IF_PATTERN      0x0020
#define INT_IF_MASK         0x0060
#define INT_EXTERN          0x0060

// Latch modes for me80
#define REGMODE_DIRECT      0x0000
#define REGMODE_INTERNAL    0x0001
#define REGMODE_EXTERNAL    0x0010

// Scan Modes for me300 family
#define SCAN_SINGLE         0x00000001
#define SCAN_INFINITE       0x00000002
#define SCAN_STREAMER       0x00000010

// board identifier
#define BOARD_00   0
#define BOARD_01   1
#define BOARD_02   2
#define BOARD_03   3
#define BOARD_04   4
#define BOARD_05   5
#define BOARD_06   6
#define BOARD_07   7
#define BOARD_08   8
#define BOARD_09   9
#define BOARD_10  10
#define BOARD_11  11
#define BOARD_12  12
#define BOARD_13  13
#define BOARD_14  14
#define BOARD_15  15
#define BOARD_16  16
#define BOARD_17  17
#define BOARD_18  18
#define BOARD_19  19
#define BOARD_20  20
#define BOARD_21  21
#define BOARD_22  22
#define BOARD_23  23
#define BOARD_24  24
#define BOARD_25  25
#define BOARD_26  26
#define BOARD_27  27
#define BOARD_28  28
#define BOARD_29  29
#define BOARD_30  30
#define BOARD_31  31


#endif
