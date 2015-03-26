(*-----------------------------------------------------------------------------
    File: ME3000.PAS
-------------------------------------------------------------------------------

    Meilhaus Electronic GmbH

    This header file contains the prototypes of ME3000.DLL functions used by
    application programs.



    Version 0.500:      08.07.98    Basic implementation
            1.000:      06.08.98    Release of version 1

-------------------------------------------------------------------------------
    Author: Wagner Armin                    (c) 1998  WA
-----------------------------------------------------------------------------*)

unit me3000;

interface

type errorstring = array [0..255] of char;

Type DEVICEINFOSTRUCT = record
    dwBoardNumber      : integer;     {Board number of Board}
    dwVendorID         : integer;     {PCI vendor ID}
    dwDeviceID         : integer;     {PCI device ID}
    dwSystemSlotNumber : integer;     {Slot number in PCI bus}
    dwPortBase         : integer;     {base port address}
    dwPortCount        : integer;     {Count of I/O addresses used.}
    dwIntChannel       : integer;     {first Interrupt Channel}
    dwPortBasePLX      : integer;     {base port address}
    dwPortCountPLX     : integer;     {Count of I/O addresses used.}
    dwSerialNumber     : integer;     {Serial number of the board}
    dwBusNumber        : integer;     {Bus number of the PCI bus (in most cases 0)}
    dwHWRevision       : integer;     {hardware revision of board}
    dwIrqCnt           : integer;     {number of interrupts }
    dwVersion          : integer;     {which board of the board family}
end;


CONST AOBufferSize = 1024; (*Buffersize for AO-Functions*)
CONST AIBufferSize = 1024; (*Buffersize for AI-Functions*)

Type TMEstring = array [1..256] of char;
     TMEAOBuffer = array [1..AOBufferSize] of smallint;
     TMEAIBuffer = array [1..AIBufferSize] of smallint;
     TME3000_SIO       =     record
                Mode:Integer;
                InBufferSize:Integer;
                InBufferCount:Integer;
                InBufferReadPointer:Integer;
                InBufferWritePointer:Integer;
                InBufferOverwrite:Integer;
                InBufferOverwriteCount:Integer;
                InStop:Integer;
                InError:Integer;
                OutBufferSize:Integer;
                OutBufferCount:Integer;
                OutBufferEndPointer:Integer;
                OutError:Integer;
                pInBuffer:string;
                pOutBuffer:string;
                end;
     TME3000_SIO_REGS  =     record
                       RHR:char;        // Reveive Register
                       IER:char;        // Interrupt Enable Register
                       FCR:char;        // FIFI Control Register
                       LCR:char;        // Line Control Register
                       MCR:char;        // Modem Control Register
                       LSR:char;        // Line Status Register
                       MSR:char;        // Modem Satus Register
                       SPR:char;        // ScatchPad Register
                             end;
// Error handling
//------------------------------
//Function       me3000GetDriverErrorString(VAR pcErrorText:string):integer;cdecl;
Function       me3000GetDriverErrorString(VAR pcErrorText:TMEstring):integer;cdecl;
Function       me3000ErrorMessage(VAR ptAppName:TMEstring):integer;cdecl;
//
// General functions
//------------------------------
Function        me3000GeneralReset(iBoardNumber:integer):integer;cdecl;
Function    me3000GetDLLVersion:integer;cdecl;
//Function  me3000GetDriverVersion(VAR pBuffer:string):integer;cdecl;
Function    me3000GetDriverVersion(VAR pBuffer:TMEstring):integer;cdecl;
Function    me3000GetVECModel(iBoardnumber:Integer;VAR piMEVECModel : Integer )
                :integer;cdecl;
Function    me3000GetSerialNumber(iBoardnumber:Integer;VAR piSerialNumber:Integer)
                :integer;cdecl;
//
Function    me3000Initialize(iBoardnumber:Integer):integer;cdecl;
//
// Digial I/O functions
//------------------------------
Function    me3000DIOSetPortDirection(iBoardnumber,iPortNo,iDir:Integer)
                                          :integer;cdecl;
Function    me3000DIGetBit(iBoardnumber,iPortNo,iBitNo:Integer;
                               VAR piBitValue:Integer):integer;cdecl;
Function    me3000DIGetByte(iBoardnumber,iPortNo,iByteNo:Integer;
                               VAR piByteValue:Integer):integer;cdecl;
Function    me3000DIGetWord(iBoardnumber,iPortNo:Integer;
                               VAR piValue:Integer):integer;cdecl;
//
Function    me3000DOSetBit(iBoardnumber,iPortNo,iBitNo,iBitValue:Integer)
                               :integer;cdecl;
Function    me3000DOSetByte(iBoardnumber, iPortNo,iByteNo,iByteValue:Integer)
                               :integer;cdecl;
Function    me3000DOSetWord(iBoardnumber,iPortNo,iValue:Integer):integer;cdecl;
Function    me3000DOReset(iBoardnumber,iPortNo:Integer):integer;cdecl;
//
// Thread priority function
//------------------------------
Function    me3000SetPriority(iBoardnumber,iPriority:Integer):integer;cdecl;
//
// Analog input functions
//------------------------------
Function    me3000AIClearChannelList(iBoardnumber:Integer):integer;cdecl;
Function    me3000AIAddToChannelList(iBoardnumber,iEntry:Integer):integer;cdecl;
//
Function        me3000FileName(iBoardnumber,iType:Integer; VAR pFileName:TMEstring)
                :integer;cdecl;
Function    me3000FrequencyToCounter(dFreq:double):integer;cdecl;
//
Function        me3000AISetTimer(iBoardnumber,iScan,iChan:Integer):integer;cdecl;
Function        me3000AISetTrigger(iBoardnumber,iModePolarity:Integer):integer;cdecl;
//
//ToCheck:
Function    me3000AIMakeChannelListEntry(iChannel,iRange,iMode:Integer;
                VAR psEntry:smallint):integer;cdecl;
//Function  me3000AIMakeChannelListEntry(iChannel,iRange,iMode:Integer;VAR piEntry:integer):integer;cdecl;

//
Function    me3000AISetSimultaneous(iBoardnumber,iMode:Integer):integer;cdecl;
//
Function    me3000AIStop(iBoardnumber:Integer):integer;cdecl;
//
Function        me3000AISingle(iBoardnumber,iChannel,iMode:Integer;
                VAR psValue:smallint):integer;cdecl;
Function    me3000AISingleEx(iBoardnumber,iChannel,iMode,iLoops,iDelay:Integer
                ;VAR psValue:smallint; PSHORT_PROC:Pointer):integer;cdecl;
//
Function    me3000AIMultiple(iBoardnumber:Integer;VAR psBuffer:smallint;
                iCount,iMode:Integer):integer;cdecl;
Function    me3000AIMultipleEx(iBoardnumber:Integer;VAR psBuffer:smallint;
                iCount,iMode,iLoops,iDelay:Integer;P_1_PROC:Pointer):integer;cdecl;
//
Function    me3000AIQuick(iBoardnumber:Integer;VAR psBuffer:smallint;
                iCount,iMode:Integer):integer;cdecl;
Function    me3000AIQuickEx(iBoardnumber:Integer;VAR psBuffer:smallint;
                iCount,iMode,iLoops,iDelay:Integer;P_1_PROC:Pointer):integer;cdecl;
//
Function    me3000AIScan(iBoardnumber:Integer; VAR psBuffer:TMEAIBuffer;
                iSize,iCount,iMode:Integer):integer;cdecl;
Function    me3000AIScanEx(iBoardnumber:Integer;VAR psBuffer:smallint;iSize,
                iCount,iMode,iLoops,iDelay:Integer;P_1_PROC:Pointer):integer;cdecl;
//
// Analog output functions
//------------------------------
Function    me3000AOReset(iBoardnumber:Integer):integer;cdecl;
Function    me3000AOSetMode(iBoardnumber,iChannel,iRange,iMode:Integer)
                :integer;cdecl;
Function    me3000AOSingle(iBoardnumber,iChannel:Integer;
                sValue:smallint):integer;cdecl;
Function    me3000AOUpdate(iBoardnumber:Integer):integer;cdecl;
Function    me3000AOSetTimer(iBoardnumber,iTimer:Integer):integer;cdecl;
Function    me3000AOSetTrigger(iBoardnumber,iModePolarity:Integer):integer;cdecl;
Function    me3000AOClearDACFIFO(iBoardnumber:Integer):integer;cdecl;
Function    me3000AOAddToDACFIFO(iBoardnumber,iEntry:Integer):integer;cdecl;
Function    me3000AOWrapAround(iBoardnumber:Integer):integer;cdecl;
Function    me3000AOStop(iBoardnumber:Integer):integer;cdecl;
Function    me3000AOContinuous(iBoardnumber,iMode,iSize:Integer;
                VAR psBuffer:TMEAOBuffer):integer;cdecl;
Function    me3000AOStopEx(iBoardnumber:Integer):integer;cdecl;
Function    me3000AOContinuousEx(iBoardnumber,iMode,iSize:Integer;
                VAR psBuffer:TMEAOBuffer;iLoops,iDelay:Integer;
                PVOID_PROC:Pointer):integer;cdecl;
//
// PWM functions
//------------------------------
Function    me3000PWMSetMode(iBoardnumber:Integer;dFreq:double;
                iDutyCycle,iInverted:Integer):integer;cdecl;
Function    me3000PWMStart(iBoardnumber:Integer):integer;cdecl;
Function    me3000PWMStop(iBoardnumber:Integer):integer;cdecl;
//
// SIO functions
//------------------------------
Function    me3000SIOGetRegisters(iBoardnumber:Integer
                ;pBuffer:TME3000_SIO_REGS):integer;cdecl;
Function    me3000SIOLoopBackTest(iBoardnumber:Integer):integer;cdecl;
Function    me3000SIOSetup(iBoardnumber,iBaut,iLen,iStop:Integer;
                cParity:char):integer;cdecl;
Function    me3000SIOWriteRegister(iBoardnumber:Integer;cReg,cVal:char)
                :integer;cdecl;
Function    me3000SIOReadRegister(iBoardnumber:Integer;cReg:char):integer;cdecl;
Function    me3000SIOTransmit(iBoardnumber,iMode,iCount:Integer;
                VAR pcBuffer:TMEstring):integer;cdecl;
Function    me3000SIOReceive(iBoardnumber,iMode,iCount:Integer;
                VAR pcBuffer:TMEstring):integer;cdecl;
Function    me3000SIOOpen(iBoardnumber,iMode,iInBufferSize,
                iOutBufferSize:Integer):integer;cdecl;
Function    me3000SIOClose(iBoardnumber:Integer):integer;cdecl;
Function    me3000SIOClearBuffer(iBoardnumber:Integer):integer;cdecl;
Function    me3000SIOCheckBuffer(iBoardnumber:Integer;psio:TME3000_SIO):integer;cdecl;
Function    me3000SIOCheckError(iBoardnumber:Integer):integer;cdecl;
//
// External interrupt functions
//------------------------------
Function    me3000EnableExternalInt(iBoardnumber:Integer;
                PVOID_PROC:Pointer):integer;cdecl;
Function    me3000DisableExternalInt(iBoardnumber:Integer):integer;cdecl;
//
// Counter functions
//------------------------------
Function    me3000CNTStart(iBoardnumber,iCounter:Integer):integer;cdecl;
Function    me3000CNTRead(iBoardnumber,iCounter:Integer;
                VAR psCounterValue:smallint):integer;cdecl;
Function    me3000CNTInterrupt(iBoardnumber,Counter,iFlag:Integer
                ;PVOID_PROC:Pointer):integer;cdecl;
Function    me3000CNTReset(iBoardnumber,iCounter:Integer):integer;cdecl;
Function    me3000CNTSetRange(iBoardnumber,iCounter,iEndValue,
                iStartValue:Integer):integer;cdecl;

implementation

const dll = 'me3000.dll';

// Error handling
//------------------------------
Function       me3000GetDriverErrorString(VAR pcErrorText:TMEstring):integer;external dll
Function       me3000ErrorMessage(VAR ptAppName:TMEstring):integer;external dll
//
// General functions
//------------------------------
Function        me3000GeneralReset(iBoardNumber:integer):integer;external dll
Function    me3000GetDLLVersion:integer;external dll
//Function  me3000GetDriverVersion(VAR pBuffer:string):integer;external dll
Function    me3000GetDriverVersion(VAR pBuffer:TMEstring):integer;external dll

Function    me3000GetVECModel(iBoardnumber:Integer;VAR piMEVECModel : Integer )
                :integer;external dll
Function    me3000GetSerialNumber(iBoardnumber:Integer;VAR piSerialNumber:Integer)
                :integer;external dll
//
Function    me3000Initialize(iBoardnumber:Integer):integer;external dll
//
// Digial I/O functions
//------------------------------
Function    me3000DIOSetPortDirection(iBoardnumber,iPortNo,iDir:Integer)
                                          :integer;external dll
Function    me3000DIGetBit(iBoardnumber,iPortNo,iBitNo:Integer;
                               VAR piBitValue:Integer):integer;external dll
Function    me3000DIGetByte(iBoardnumber,iPortNo,iByteNo:Integer;
                               VAR piByteValue:Integer):integer;external dll
Function    me3000DIGetWord(iBoardnumber,iPortNo:Integer;
                               VAR piValue:Integer):integer;external dll
//
Function    me3000DOSetBit(iBoardnumber,iPortNo,iBitNo,iBitValue:Integer)
                               :integer;external dll
Function    me3000DOSetByte(iBoardnumber, iPortNo, iByteNo, iByteValue:Integer)
                               :integer;external dll
Function    me3000DOSetWord(iBoardnumber,iPortNo,iValue:Integer):integer;external dll
Function    me3000DOReset(iBoardnumber,iPortNo:Integer):integer;external dll
//
// Thread priority function
//------------------------------
Function    me3000SetPriority(iBoardnumber,iPriority:Integer):integer;external dll
//
// Analog input functions
//------------------------------
Function    me3000AIClearChannelList(iBoardnumber:Integer):integer;external dll
Function    me3000AIAddToChannelList(iBoardnumber,iEntry:Integer):integer;external dll
//
Function    me3000FileName(iBoardnumber,iType:Integer; VAR pFileName:TMEstring)
                :integer;external dll
Function    me3000FrequencyToCounter(dFreq:double):integer;external dll
//
Function    me3000AISetTimer(iBoardnumber,iScan,iChan:Integer):integer;external dll
Function    me3000AISetTrigger(iBoardnumber,iModePolarity:Integer):integer;external dll
//
Function    me3000AIMakeChannelListEntry(iChannel,iRange,iMode:Integer;
                VAR psEntry:smallint):integer;external dll
//
Function    me3000AISetSimultaneous(iBoardnumber,iMode:Integer):integer;external dll
//
Function    me3000AIStop(iBoardnumber:Integer):integer;external dll
//
Function    me3000AISingle(iBoardnumber,iChannel,iMode:Integer;
                VAR psValue:smallint):integer;external dll
Function    me3000AISingleEx(iBoardnumber,iChannel,iMode,iLoops,iDelay:Integer
                ;VAR psValue:smallint; PSHORT_PROC:Pointer):integer;external dll
//
Function    me3000AIMultiple(iBoardnumber:Integer;VAR psBuffer:smallint;
                iCount,iMode:Integer):integer;external dll
Function    me3000AIMultipleEx(iBoardnumber:Integer;VAR psBuffer:smallint;
                iCount,iMode,iLoops,iDelay:Integer;P_1_PROC:Pointer):integer;external dll
//
Function    me3000AIQuick(iBoardnumber:Integer;VAR psBuffer:smallint;
                iCount,iMode:Integer):integer;external dll
Function    me3000AIQuickEx(iBoardnumber:Integer;VAR psBuffer:smallint;
                iCount,iMode,iLoops,iDelay:Integer;P_1_PROC:Pointer):integer;external dll

Function    me3000AIScan(iBoardnumber:Integer; VAR psBuffer:TMEAIBuffer;
                iSize,iCount,iMode:Integer):integer;external dll

Function    me3000AIScanEx(iBoardnumber:Integer;VAR psBuffer:smallint;iSize,
                iCount,iMode,iLoops,iDelay:Integer;P_1_PROC:Pointer):integer;external dll
//
// Analog output functions
//------------------------------
Function    me3000AOReset(iBoardnumber:Integer):integer;external dll
Function    me3000AOSetMode(iBoardnumber,iChannel,iRange,iMode:Integer)
                :integer;external dll
Function    me3000AOSingle(iBoardnumber,iChannel:Integer;
                sValue:smallint):integer;external dll
Function    me3000AOUpdate(iBoardnumber:Integer):integer;external dll
Function    me3000AOSetTimer(iBoardnumber,iTimer:Integer):integer;external dll
Function    me3000AOSetTrigger(iBoardnumber,iModePolarity:Integer):integer;external dll
Function    me3000AOClearDACFIFO(iBoardnumber:Integer):integer;external dll
Function    me3000AOAddToDACFIFO(iBoardnumber,iEntry:Integer):integer;external dll
Function    me3000AOWrapAround(iBoardnumber:Integer):integer;external dll
Function    me3000AOStop(iBoardnumber:Integer):integer;external dll
Function    me3000AOContinuous(iBoardnumber,iMode,iSize:Integer
                ;VAR psBuffer:TMEAOBuffer):integer;external dll
Function    me3000AOStopEx(iBoardnumber:Integer):integer;external dll
Function    me3000AOContinuousEx(iBoardnumber,iMode,iSize:Integer;
                VAR psBuffer:TMEAOBuffer;iLoops,iDelay:Integer;
                PVOID_PROC:Pointer):integer;external dll
//
// PWM functions
//------------------------------
Function    me3000PWMSetMode(iBoardnumber:Integer;dFreq:double;
                iDutyCycle,iInverted:Integer):integer;external dll
Function    me3000PWMStart(iBoardnumber:Integer):integer;external dll
Function    me3000PWMStop(iBoardnumber:Integer):integer;external dll
//
// SIO functions
//------------------------------
Function    me3000SIOGetRegisters(iBoardnumber:Integer
                ;pBuffer:TME3000_SIO_REGS):integer;external dll
Function    me3000SIOLoopBackTest(iBoardnumber:Integer):integer;external dll
Function    me3000SIOSetup(iBoardnumber,iBaut,iLen,iStop:Integer;
                cParity:char):integer;external dll
Function        me3000SIOWriteRegister(iBoardnumber:Integer;cReg,cVal:char)
                :integer;external dll
Function        me3000SIOReadRegister(iBoardnumber:Integer;cReg:char):integer;external dll
Function        me3000SIOTransmit(iBoardnumber,iMode,iCount:Integer;
                VAR pcBuffer:TMEstring):integer;external dll
Function        me3000SIOReceive(iBoardnumber,iMode,iCount:Integer;
                VAR pcBuffer:TMEstring):integer;external dll
Function        me3000SIOOpen(iBoardnumber,iMode,iInBufferSize,
                iOutBufferSize:Integer):integer;external dll
Function        me3000SIOClose(iBoardnumber:Integer):integer;external dll
Function        me3000SIOClearBuffer(iBoardnumber:Integer):integer;external dll
Function        me3000SIOCheckBuffer(iBoardnumber:Integer;psio:TME3000_SIO):integer;external dll
Function        me3000SIOCheckError(iBoardnumber:Integer):integer;external dll
//
// External interrupt functions
//------------------------------
Function    me3000EnableExternalInt(iBoardnumber:Integer;
                PVOID_PROC:Pointer):integer;external dll
Function    me3000DisableExternalInt(iBoardnumber:Integer):integer;external dll
//
// Counter functions
//------------------------------
Function    me3000CNTStart(iBoardnumber,iCounter:Integer):integer;external dll
Function    me3000CNTRead(iBoardnumber,iCounter:Integer;
                VAR psCounterValue:smallint):integer;external dll
Function    me3000CNTInterrupt(iBoardnumber,Counter,iFlag:Integer
                ;PVOID_PROC:Pointer):integer;external dll
Function    me3000CNTReset(iBoardnumber,iCounter:Integer):integer;external dll
Function    me3000CNTSetRange(iBoardnumber,iCounter,iEndValue,
                iStartValue:Integer):integer;external dll

Function    me3000AIContinuous(iBoardNumber, iFrameSize, iBufferSize : Integer;
                P_1_PROC :Pointer):integer;external dll

end.
