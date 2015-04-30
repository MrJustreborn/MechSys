/*
M e i l h a u s   i n t e r n a l   r e m a r k :
-------------------------------------------------
This is a copy of the same file in _osi directory
Please make all changes in the original file
*/

#ifndef MEDEFS_H
#define MEDEFS_H

// Maximum number of Boards
#define ME_MAX_DEVICES	32

typedef void (_stdcall *PSERVICE_PROC) (void);
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
    DWORD   dwPortBasePLX;			// base port address
    DWORD   dwPortCountPLX;			// Count of I/O addresses used.
    DWORD   dwSerialNumber;         // Serial number of the board
    DWORD   dwBusNumber;            // Bus number of the PCI bus (in most cases 0)
    DWORD   dwHWRevision;           // hardware revision of board
    DWORD   dwIrqCnt;               // number of interrupts 
    DWORD   dwVersion;              // which board of the board family

} DEVICEINFOSTRUCT, *PDEVICEINFOSTRUCT;

// Register sets
#define REGISTER_SET_A	0
#define REGISTER_SET_B	1

// Source/Sink Mode
#define SINK_MODE		0
#define SOURCE_MODE		1

// Interrupt modes
#define INTERRUPT_ON_PATTERN_COMPARE	0
#define INTERRUPT_ON_BIT_CHANGE			1
	

// me8x definitions for compatability

typedef enum _PORTMODE 
{
	IN32=0, 
	OUT32=1, 
	IN16=2, 
	OUT16=3, 
	INOUT16=4
} PORTMODE;

typedef enum _PORTNAME 
{
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

#endif
