#ifndef ME2600_H
#define ME2600_H


typedef struct _BOARD 
{
	HANDLE		hBoard;	
	DWORD		HandleID;
	USHORT		*psData;
	USHORT		*psDACData;
	DWORD		Size;
	DWORD		DACSize;
	DWORD		LastErrorCode;
	OVERLAPPED	SysOvl;

	USHORT		usDataPortA[4];
	USHORT		usDataPortB[4];
	USHORT		usDACControl[4];

	//char		FileName[512];
	BOOL		ADCIsBusy;
	DWORD		AITriggerMode;
	DWORD		AIInterrupt;
	DWORD		ThreadPriority;
	DWORD		AOTriggerMode;
	BOOL		DACIsBusy;
	DWORD		AOInterrupt;
	BOOL		ExtIntIsBusy;
	BOOL		CounterAIntIsBusy;
	BOOL		CounterBIntIsBusy;

	DWORD		NoOfBoards;
	DWORD		DeviceNumber;
	DWORD		Word;

	DWORD		RTPhysAddr;			// Phys. address of RT registers
	DWORD		XilinxPhysAddr;		// Phys. address of XILINX
	DWORD		SioPhysAddr;		// Phys. address of SIO

	DWORD		SizeOfADCFifo;
	DWORD		SizeOfDACFifo;
	DWORD		SizeOfChanListFifo;

	DWORD		FileStatus;
	DWORD		FileLength;
	DWORD		FileVersion;
	DWORD		FileDate;
	DWORD		Date;
	DWORD		LicenceKey;
	DWORD		SerialNumber;
	DWORD		MEVECModel;
	DWORD		SlotNumber;

} BOARD, *PBOARD;




extern "C" 
{
_declspec(dllexport) int  _cdecl	meTickTimer(int);
_declspec(dllexport) int  _cdecl    me2600ErrorMessage(char *);
_declspec(dllexport) int  _cdecl	me2600GeneralReset(int);
_declspec(dllexport) int  _cdecl	me2600GetInterrupts(int iBoardNumber, 
												      PME_BOARD_ISR pInt);
_declspec(dllexport) int  _cdecl	me2600GetBoardInfo(int, 
													  PME_BOARD_INFO);
_declspec(dllexport) int  _cdecl	me2600DLLBoardInfo(int, 
													  PME_BOARD_INFO);
_declspec(dllexport) int  _cdecl	me2600GetDriverErrorString(char *);
_declspec(dllexport) int  _cdecl	me2600GetDLLVersion(void);
_declspec(dllexport) int  _cdecl    me2600GetDLLTimeStamp(char *);
_declspec(dllexport) int  _cdecl	me2600GetDriverVersion(char *);
_declspec(dllexport) int  _cdecl	me2600GetDriverTimeStamp(char *);
_declspec(dllexport) int  _cdecl	me2600GetPCIConfiguration(int, 
														PME_PLX9050_INFO);
_declspec(dllexport) int  _cdecl	me2600GetVECModel(int, int *);
_declspec(dllexport) int  _cdecl	me2600GetSerialNumber(int, int *);
_declspec(dllexport) int  _cdecl    me2600GetDriverStatus(int, 
												 PME_DRIVER_STATUS);
_declspec(dllexport) int  _cdecl	me2600DIOSetPortDirection(int, int, int);

_declspec(dllexport) int  _cdecl	me2600DIGetBit(int, int, int, int *);
_declspec(dllexport) int  _cdecl    me2600DIGetByte(int, int, int, int *);
_declspec(dllexport) int  _cdecl	me2600DIGetWord(int, int, int *);

_declspec(dllexport) int  _cdecl	me2600DOSetBit(int, int, int, int);
_declspec(dllexport) int  _cdecl	me2600DOSetByte(int, int, int, int);
_declspec(dllexport) int  _cdecl	me2600DOSetWord(int, int, int);
_declspec(dllexport) int  _cdecl	me2600DOReset(int, int);

_declspec(dllexport) int  _cdecl	me2600AIClearChannelList(int);
_declspec(dllexport) int  _cdecl	me2600AIAddToChannelList(int, int);
_declspec(dllexport) int  _cdecl	me2600AIMakeChannelListEntry(int, int, int, int*);

_declspec(dllexport) int  _cdecl   me2600FileName(int, int, char *);

_declspec(dllexport) int  _cdecl	me2600FrequencyToCounter(double);
_declspec(dllexport) int  _cdecl    me2600AISetTimer(int, int, int);
_declspec(dllexport) int  _cdecl    me2600AISetTrigger(int, int);

_declspec(dllexport) int  _cdecl	me2600SetPriority(int, int); 												  

_declspec(dllexport) int  _cdecl	me2600AISetSimultaneous(int, int);
														
_declspec(dllexport) int  _cdecl	me2600AIStop(int); 
_declspec(dllexport) int  _cdecl    me2600AISingle(int, int, int, short *);
_declspec(dllexport) int  _cdecl	me2600AISingleEx(int, int, int, int, int, 
													 short*, PSHORT_PROC);
													 
_declspec(dllexport) int  _cdecl	me2600AIMultiple(int, short *, int, int);													 
_declspec(dllexport) int  _cdecl	me2600AIMultipleEx(int, short*, int, int,
													   int, int, P_1_PROC);
													   
_declspec(dllexport) int  _cdecl	me2600AIQuick(int, short*, int, int);												  
_declspec(dllexport) int  _cdecl	me2600AIQuickEx(int, short*, int, int, 
												    int, int, P_1_PROC);
													   
_declspec(dllexport) int  _cdecl	me2600AIScan(int, short*, int, int,  int);
_declspec(dllexport) int  _cdecl	me2600AIScanInt(int, short*, int, int, int);
_declspec(dllexport) int  _cdecl	me2600AIScanPoll(int, short*, int, int);
_declspec(dllexport) int  _cdecl	me2600AIScanEx(int, short*, int, int, int,
												   int, int, P_1_PROC);
										     
_declspec(dllexport) int  _cdecl    me2600AOReset(int);
_declspec(dllexport) int  _cdecl	me2600AOSetMode(int, int, int, int);
_declspec(dllexport) int  _cdecl	me2600AOSingle(int, int, short);
_declspec(dllexport) int  _cdecl	me2600AOUpdate(int);
_declspec(dllexport) int  _cdecl    me2600AOSetTimer(int, int);
_declspec(dllexport) int  _cdecl    me2600AOSetTrigger(int, int);
_declspec(dllexport) int  _cdecl	me2600AOClearDACFIFO(int);
_declspec(dllexport) int  _cdecl	me2600AOAddToDACFIFO(int, int);
_declspec(dllexport) int  _cdecl	me2600AOWrapAround(int);
_declspec(dllexport) int  _cdecl	me2600AOStop(int);
_declspec(dllexport) int  _cdecl	me2600AOContinuous(int, int, int, short*);
_declspec(dllexport) int  _cdecl	me2600AOStopEx(int);
_declspec(dllexport) int  _cdecl	me2600AOContinuousEx(int, int, int, short*, 
												        int, int, PVOID_PROC);
												        
_declspec(dllexport) int  _cdecl	me2600PWMSetMode(int, double, int, int);
_declspec(dllexport) int  _cdecl	me2600PWMStart(int);
_declspec(dllexport) int  _cdecl	me2600PWMStop(int);

_declspec(dllexport) int  _cdecl	me2600SetControlRegister(int, USHORT,
															 USHORT, USHORT);
_declspec(dllexport) int _cdecl		me2600SIOGetRegisters(int, 
														  PME_BOARD_SIO_REGS);
_declspec(dllexport) int  _cdecl	me2600SIOLoopBackTest(int);
_declspec(dllexport) int  _cdecl	me2600SIOSetup(int, int, int, int, char);
_declspec(dllexport) char _cdecl	me2600SIOWriteRegister(int, char, char);
_declspec(dllexport) char _cdecl	me2600SIOReadRegister(int, char);
_declspec(dllexport) int  _cdecl    me2600SIOTransmit(int, int, int, char *);
_declspec(dllexport) int  _cdecl    me2600SIOReceive(int, int, int, char *);
_declspec(dllexport) int  _cdecl    me2600SIOOpen(int, int, int, int);
_declspec(dllexport) int  _cdecl    me2600SIOClose(int);
_declspec(dllexport) int  _cdecl    me2600SIOClearBuffer(int);
_declspec(dllexport) int  _cdecl    me2600SIOCheckBuffer(int, PME_BOARD_SIO);
_declspec(dllexport) int  _cdecl    me2600SIOCheckError(int);

_declspec(dllexport) int  _cdecl	me2600Initialize(int);

_declspec(dllexport) int  _cdecl	me2600ReadWord(int, int, int*);
_declspec(dllexport) int  _cdecl	me2600WriteWord(int, int, int);

_declspec(dllexport) int  _cdecl	me2600EnableExternalInt(int, 
														PVOID_PROC Callback );
_declspec(dllexport) int  _cdecl	me2600DisableExternalInt(int);

_declspec(dllexport) int  _cdecl	me2600CNTStart(int, int);
_declspec(dllexport) int  _cdecl	me2600CNTRead(int, int, short *);
_declspec(dllexport) int  _cdecl	me2600CNTInterrupt(int, int, 
													   int, PVOID_PROC);
_declspec(dllexport) int  _cdecl	me2600CNTReset(int, int);
_declspec(dllexport) int  _cdecl	me2600CNTSetRange(int, int, int, int);
												  												   
}

#endif