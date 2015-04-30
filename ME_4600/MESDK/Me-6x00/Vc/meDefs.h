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

typedef void (_cdecl *PVOID_PROC)( void* );


//------ ME6x00_TRIGGER_MODE ------
typedef enum
{
    AO6x00_TRIGGER_TIMER    = 0x00,
    AO6x00_TRIGGER_EXT_HIGH = 0x10,
    AO6x00_TRIGGER_EXT_LOW  = 0x30
} ME6x00_TRIGGER_MODE;

//------ ME6x00_SIGNAL_SHAPE ------
typedef enum
{
    AO_RECTANGLE, AO_TRIANGLE, AO_SINUS, AO_COSINUS, AO_POS_RAMP, AO_NEG_RAMP
} ME6x00_SIGNAL_SHAPE;

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


#endif
