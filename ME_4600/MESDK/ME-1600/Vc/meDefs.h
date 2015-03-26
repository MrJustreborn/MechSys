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


// channel identifier
#define AO_CHAN_00   0
#define AO_CHAN_01   1
#define AO_CHAN_02   2
#define AO_CHAN_03   3
#define AO_CHAN_04   4
#define AO_CHAN_05   5
#define AO_CHAN_06   6
#define AO_CHAN_07   7
#define AO_CHAN_08   8
#define AO_CHAN_09   9
#define AO_CHAN_10  10
#define AO_CHAN_11  11
#define AO_CHAN_12  12
#define AO_CHAN_13  13
#define AO_CHAN_14  14
#define AO_CHAN_15  15


// channel group identifier
#define AO_GROUP_A  0
#define AO_GROUP_B  1
#define AO_GROUP_C  2
#define AO_GROUP_D  3


// output modes
#define AO_BUFFERED     0
#define AO_TRANSPARENT  1


// output ranges
#define AO_UNIPOLAR 0       //   0V ..  10V
#define AO_BIPOLAR  1       // -10V .. +10V


// current flow identifier
#define AO_CURRENT_OFF  0
#define AO_CURRENT_ON   1


// current mode identifier
#define AO_RANGE_0_20   0
#define AO_RANGE_4_20   1


// Interrupts
#define ME_IRQ_1            1
#define ME_IRQ_2            2


// ME160 defines for compatability with earlier versions
// Do not use them for new projects

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

// Analog Output Ranges for me160 family
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

#endif
