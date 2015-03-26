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

// Interrupts
#define ME630_IRQ_1     1
#define ME630_IRQ_2     2

// New functions

#define ME630_DIO_PORT_C		2
#define ME630_DIO_PORT_D		3


#define ME630_DIO_PORT_INPUT	0
#define ME630_DIO_PORT_OUTPUT	1


#endif
