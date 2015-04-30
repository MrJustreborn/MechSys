#ifndef COMMON_H
#define COMMON_H


	// 
	//--------------------------------------------------------------------
	typedef void (_stdcall *PVOID_PROC)  (void);
	typedef void (_stdcall *P_1_PROC)    (short*, int);
	typedef void (_stdcall *PSHORT_PROC) (short*);

	// SIO register structure 
	//---------------------------------------------------------------------
	typedef struct _ME_BOARD_SIO_REGS
	{
		char	RHR;		// Reveive Register
		char	IER;		// Interrupt Enable Register
		char	FCR;		// FIFI Control Register 
		char	LCR;		// Line Control Register
		char	MCR;		// Modem Control Register
		char	LSR;		// Line Status Register
		char	MSR;		// Modem Satus Register
		char	SPR;		// ScatchPad Register
	} ME_BOARD_SIO_REGS, *PME_BOARD_SIO_REGS;

	// SIO communication structure 
	//---------------------------------------------------------------------
	typedef struct _ME_BOARD_SIO
	{
		int		Mode;
		int		InBufferSize;
		int		InBufferCount;
		int		InBufferReadPointer;
		int		InBufferWritePointer;
		int		InBufferOverwrite;
		int		InBufferOverwriteCount;
		int		InStop;
		int		InError;

		int		OutBufferSize;
		int		OutBufferCount;
		int		OutBufferEndPointer;
		int		OutError;

		char	*pInBuffer;		
		char	*pOutBuffer;	
	} ME_BOARD_SIO, *PME_BOARD_SIO;


	// Driver Board Info structure 
	//---------------------------------------------------------------------
	typedef struct _ME_BOARD_INFO
	{
		// Take care of 4-bytes-alignment: Add padding bytes if necessary!
		ULONG	ErrorCode;		// Driver error code
		ULONG	NoOfBoards;		// No. of boards detected by DriverEntry
		ULONG	DeviceNumber;	// Number of selected board
		ULONG	Word;			// General purpose debug value
		ULONG	RTPhysAddr;		// Phys. address of PLX RT registers
		ULONG	XilinxPhysAddr;	// Phys. address of XILINX
		ULONG	SioPhysAddr;	// Phys. address of SIO
		ULONG	MEVECModel;		// Actually loaded Firmware Model     
		ULONG	FileStatus;		// Status after reading Firmware file
		ULONG	FileLength;		// Length of Firmware file
		ULONG	FileVersion;	// Version of Firmware file
		ULONG	FileDate;		// Date of Firmware file
		ULONG	ADCFifo;		// Size of ADC FIFO
		ULONG	DACFifo;		// Size of DAC FIFO
		ULONG	ChanListFifo;	// Size of channel list FIFO
		ULONG	SerialNumber;   
		ULONG	Date;			// Date when eeprom was written
		ULONG	SlotNumber;		// PCI slot number
	} ME_BOARD_INFO, *PME_BOARD_INFO;


	// Driver Interrupt Service Info structure 
	//---------------------------------------------------------------------
	typedef struct _ME_BOARD_ISR
	{
		// Take care of 4-bytes-alignment: Add padding bytes if necessary!
		ULONG	ISR;			
		ULONG	AdcFifo;			
		ULONG	ChanList;	
		ULONG	Extern;		
		ULONG	CountA;		
		ULONG	CountB;		
		ULONG	UART;		
		ULONG	DacFifo;		

	} ME_BOARD_ISR, *PME_BOARD_ISR;



	// Transfer structure DLL->Driver
	//---------------------------------------------------------------------
	typedef struct _ME_BOARD_TRANSFER_OBJECT
	{
		// Take care of 4-bytes-alignment: Add padding bytes if necessary!
		int		iBoardNumber;
		USHORT	usRegister;
		USHORT	usBits;
		USHORT	usMode;
		USHORT	usControl1;
		USHORT	usControl2;
		USHORT	usControl3;
		ULONG	ulValue;			
		ULONG	ulSize;			
		ULONG	ulBlocks;			
		ULONG	ulInterrupt;			
		ULONG	ulScanToDisk;
		ULONG	ulFileNameLength;
		char	FileName[256];
	} ME_BOARD_TRANSFER_OBJECT, *PME_BOARD_TRANSFER_OBJECT;
	

	// Control register debug structure 
	//---------------------------------------------------------------------
	typedef struct _ME_DRIVER_STATUS
	{
		// Take care of 4-bytes-alignment: Add padding bytes if necessary!
		USHORT	usControl1;
		USHORT	usControl2;
		USHORT	usControl3;
		USHORT	usIRQMask;
		USHORT	usISRMask;
		USHORT	usStatus;
		USHORT	usDACStatus;
		USHORT  usPadding;
		ULONG	ulDebugWord;
	} ME_DRIVER_STATUS, *PME_DRIVER_STATUS;

#endif
