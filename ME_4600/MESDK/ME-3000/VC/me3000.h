/*-----------------------------------------------------------------------------
    File: me3000.h
-------------------------------------------------------------------------------

    Meilhaus Electronic GmbH

    This header file contains the prototypes of ME3000.DLL functions used by
    application programs.



    Version 0.500:      01.02.98    Basic implementation
            1.000:      25.03.98    Release of version 1
            1.100:      25.05.99    Special trigger mode added

-------------------------------------------------------------------------------
    Author: Max Kormaier                                        (c) 1997   MK
-----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif


// Error handling
//------------------------------
_declspec(dllexport) int  _cdecl    me3000GetDriverErrorString(char *);
_declspec(dllexport) int  _cdecl    me3000ErrorMessage(char *);
//
// General functions
//------------------------------
_declspec(dllexport) void _cdecl    me3000GeneralReset(int);
_declspec(dllexport) int  _cdecl    me3000GetInterrupts(int iBoardNumber, PME3000_ISR pInt);
_declspec(dllexport) int  _cdecl    me3000GetBoardInfo(int, PME3000_BOARD_INFO);
_declspec(dllexport) int  _cdecl    me3000DLLBoardInfo(int, PME3000_BOARD_INFO);
_declspec(dllexport) int  _cdecl    me3000GetDLLVersion(void);
_declspec(dllexport) int  _cdecl    me3000GetDLLTimeStamp(char *);
_declspec(dllexport) int  _cdecl    me3000GetDriverVersion(char *);
_declspec(dllexport) int  _cdecl    me3000GetDriverTimeStamp(char *);
_declspec(dllexport) int  _cdecl    me3000GetPCIConfiguration(int, PME_PLX9050_INFO);
_declspec(dllexport) int  _cdecl    me3000GetVECModel(int, int *);
_declspec(dllexport) int  _cdecl    me3000GetSerialNumber(int, int *);
_declspec(dllexport) int  _cdecl    me3000GetDriverStatus(int, PME3000_DRIVER_STATUS);
_declspec(dllexport) int  _cdecl    me3000LoadFirmware(int, char *);
//
_declspec(dllexport) int  _cdecl    me3000Initialize(int);
//
// Digial I/O functions
//------------------------------
_declspec(dllexport) int  _cdecl    me3000DIOSetPortDirection(int, int, int);
_declspec(dllexport) int  _cdecl    me3000DIGetBit(int, int, int, int *);
_declspec(dllexport) int  _cdecl    me3000DIGetByte(int, int, int, int *);
_declspec(dllexport) int  _cdecl    me3000DIGetWord(int, int, int *);
//
_declspec(dllexport) int  _cdecl    me3000DOSetBit(int, int, int, int);
_declspec(dllexport) int  _cdecl    me3000DOSetByte(int, int, int, int);
_declspec(dllexport) int  _cdecl    me3000DOSetWord(int, int, int);
_declspec(dllexport) int  _cdecl    me3000DOReset(int, int);
//
// Thread priority function
//------------------------------
_declspec(dllexport) int  _cdecl    me3000SetPriority(int, int);
//
// Analog input functions
//------------------------------
_declspec(dllexport) int  _cdecl    me3000AIClearChannelList(int);
_declspec(dllexport) int  _cdecl    me3000AIAddToChannelList(int, int);
//
_declspec(dllexport) int  _cdecl    me3000FileName(int, int, char *);
_declspec(dllexport) int  _cdecl    me3000FrequencyToCounter(double);
//
_declspec(dllexport) int  _cdecl    me3000AISetTimer(int, int, int);
_declspec(dllexport) int  _cdecl    me3000AISetTrigger(int, int);
//
_declspec(dllexport) int  _cdecl    me3000AIMakeChannelListEntry(int, int, int, int*);
//
_declspec(dllexport) int  _cdecl    me3000AISetSimultaneous(int, int);
//
_declspec(dllexport) int  _cdecl    me3000AIStop(int);
//
_declspec(dllexport) int  _cdecl    me3000AISingle(int, int, int, short *);
_declspec(dllexport) int  _cdecl    me3000AISingleEx(int, int, int, int,
                                                     int, short*, PSHORT_PROC);
//
_declspec(dllexport) int  _cdecl    me3000AIMultiple(int, short *, int, int);
_declspec(dllexport) int  _cdecl    me3000AIMultipleEx(int, short*, int, int,
                                                       int, int, P_1_PROC);
//
_declspec(dllexport) int  _cdecl    me3000AIQuick(int, short*, int, int);
_declspec(dllexport) int  _cdecl    me3000AIQuickEx(int, short*, int, int,
                                                    int, int, P_1_PROC);
//
_declspec(dllexport) int  _cdecl    me3000AIScan(int, short*, int, int, int);
_declspec(dllexport) int  _cdecl    me3000AIScanEx(int, short*, int, int, int,
                                                   int, int, P_1_PROC);
_declspec(dllexport) int  _cdecl    me3000AIContinuous(int, int, int, P_1_PROC);
//
_declspec(dllexport) int  _cdecl    me3000AIClearDataFIFO(int);
_declspec(dllexport) int  _cdecl    me3000AIReadFIFO(int, short*, int);
_declspec(dllexport) int  _cdecl    me3000AIStartByExternalTrigger(int, int);


//
// Analog output functions
//------------------------------
_declspec(dllexport) int  _cdecl    me3000AOReset(int);
_declspec(dllexport) int  _cdecl    me3000AOSetMode(int, int, int, int);
_declspec(dllexport) int  _cdecl    me3000AOSingle(int, int, short);
_declspec(dllexport) int  _cdecl    me3000AOUpdate(int);
_declspec(dllexport) int  _cdecl    me3000AOSetTimer(int, int);
_declspec(dllexport) int  _cdecl    me3000AOSetTrigger(int, int);
_declspec(dllexport) int  _cdecl    me3000AOClearDACFIFO(int);
_declspec(dllexport) int  _cdecl    me3000AOAddToDACFIFO(int, int);
_declspec(dllexport) int  _cdecl    me3000AOWrapAround(int);
_declspec(dllexport) int  _cdecl    me3000AOStop(int);
_declspec(dllexport) int  _cdecl    me3000AOContinuous(int, int, int, short*);
_declspec(dllexport) int  _cdecl    me3000AOStopEx(int);
_declspec(dllexport) int  _cdecl    me3000AOContinuousEx(int, int, int, short*,
                                                         int, int, PVOID_PROC);

_declspec(dllexport) int  _cdecl    me3000AOGenerateSignal(int, int, int, int, int, int, double);
//
// PWM functions
//------------------------------
_declspec(dllexport) int  _cdecl    me3000PWMSetMode(int, double, int, int);
_declspec(dllexport) int  _cdecl    me3000PWMStart(int);
_declspec(dllexport) int  _cdecl    me3000PWMStop(int);
//
// SIO functions
//------------------------------
_declspec(dllexport) int  _cdecl    me3000SIOGetRegisters(int, PME3000_SIO_REGS);
_declspec(dllexport) int  _cdecl    me3000SIOLoopBackTest(int);
_declspec(dllexport) int  _cdecl    me3000SIOSetup(int, int, int, int, char);
_declspec(dllexport) char _cdecl    me3000SIOWriteRegister(int, char, char);
_declspec(dllexport) char _cdecl    me3000SIOReadRegister(int, char);
_declspec(dllexport) int  _cdecl    me3000SIOTransmit(int, int, int, char *);
_declspec(dllexport) int  _cdecl    me3000SIOReceive(int, int, int, char *);
_declspec(dllexport) int  _cdecl    me3000SIOOpen(int, int, int, int);
_declspec(dllexport) int  _cdecl    me3000SIOClose(int);
_declspec(dllexport) int  _cdecl    me3000SIOClearBuffer(int);
_declspec(dllexport) int  _cdecl    me3000SIOCheckBuffer(int, PME3000_SIO);
_declspec(dllexport) int  _cdecl    me3000SIOCheckError(int);
//
// External interrupt functions
//------------------------------
_declspec(dllexport) int  _cdecl    me3000EnableExternalInt(int, PVOID_PROC Callback);
_declspec(dllexport) int  _cdecl    me3000DisableExternalInt(int);
//
// Counter functions
//------------------------------
_declspec(dllexport) int  _cdecl    me3000CNTStart(int, int);
_declspec(dllexport) int  _cdecl    me3000CNTRead(int, int, short *);
_declspec(dllexport) int  _cdecl    me3000CNTInterrupt(int, int, int, PVOID_PROC);
_declspec(dllexport) int  _cdecl    me3000CNTReset(int, int);
_declspec(dllexport) int  _cdecl    me3000CNTSetRange(int, int, int, int);


#ifdef __cplusplus
}
#endif


/*-----------------------------------------------------------------------------*/
