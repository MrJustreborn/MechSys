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

// port direction
#define MEINPUT     0
#define MEOUTPUT    1

// port identifier
#define PORTA   0
#define PORTB   1
#define PORTC   2
#define PORTD   3

// word identifier
#define WORD_0  0
#define WORD_1  1

// byte identifier
#define BYTE_0  0
#define BYTE_1  1
#define BYTE_2  2
#define BYTE_3  3

// bit identifier
#define BIT_0   0
#define BIT_1   1
#define BIT_2   2
#define BIT_3   3
#define BIT_4   4
#define BIT_5   5
#define BIT_6   6
#define BIT_7   7
#define BIT_8   8
#define BIT_9   9
#define BIT_10  10
#define BIT_11  11
#define BIT_12  12
#define BIT_13  13
#define BIT_14  14
#define BIT_15  15
#define BIT_16  16
#define BIT_17  17
#define BIT_18  18
#define BIT_19  19
#define BIT_20  20
#define BIT_21  21
#define BIT_22  22
#define BIT_23  23
#define BIT_24  24
#define BIT_25  25
#define BIT_26  26
#define BIT_27  27
#define BIT_28  28
#define BIT_29  29
#define BIT_30  30
#define BIT_31  31



#endif