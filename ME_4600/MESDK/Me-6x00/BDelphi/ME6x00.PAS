(*-----------------------------------------------------------------------------
	File: ME6x00.PAS
-------------------------------------------------------------------------------

	Meilhaus Electronic GmbH

	This header file contains the prototypes of ME6x00.DLL functions used by
	application programs.



	Version 0.500:		01.02.2002	Basic implementation


-------------------------------------------------------------------------------
	Author: Wisura Erwin  					(c) 2002  EW
-----------------------------------------------------------------------------*)
unit me6x00;

interface

CONST AOBufferSize = 65535; (*Buffeesize for AO-Functions*)

Type TMEstring = array [0..256] of char;
Type TMEAOBuffer = array [0..AOBufferSize] of smallint;
Type errorstring = array [0..255] of char;
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

    // General functions
    Function	me6x00FrequencyToTimer(dFreq:double): integer; Cdecl;
    Function	me6x00GetBoardVersion(iBoardNumber: integer; var iVersion: integer): integer; Cdecl;
    Function	me6x00GetDevInfo(iBoardNumber:integer; Var DevInfo:DEVICEINFOSTRUCT):integer;Cdecl;
    Function	me6x00GetDLLVersion: integer; Cdecl;
    Function	me6x00GetDriverVersion(VAR pBuffer:string):integer;Cdecl;
    Function	me6x00GetSerialNumber(iBoardnumber:Integer;VAR piSerialNumber:integer):integer;Cdecl;
    Function	me6x00GetDrvErrMess(Var Errortext:errorstring; iBufferSize:integer):integer;Cdecl;
    
    // Analog output
    Function    me6x00AOContinuous(iBoardNumber,iChannel,iSize:integer;psBuffer: TMEAOBuffer):integer;Cdecl;
    Function	me6x00AOContinuousEx(iBoardNumber,iChannel,iSize:integer;psBuffer: TMEAOBuffer;iLoops:integer;pCallback, pArgs:Pointer):integer;Cdecl;
    Function	me6x00AOReset(iBoardNumber,iChannel:integer):integer;Cdecl;
    Function	me6x00AOSetTimer(iBoardNumber,iChannel,iTicks:integer):integer;Cdecl;
    Function	me6x00AOSetTrigger(iBoardNumber,iChannel,iModePolarity:integer):integer;Cdecl;
    Function	me6x00AOSingle(iBoardNumber,iChannel,iValue:integer):integer;Cdecl;
    Function	me6x00AOStart(iBoardNumber,iChannel:integer):integer;Cdecl;
    Function	me6x00AOStop(iBoardNumber,iChannel:integer):integer;Cdecl;
    Function	me6x00AOStopEx(iBoardNumber,iChannel:integer):integer;Cdecl;
    Function	me6x00AOWaveGen(iBoardNumber,iChannel,iShape:integer;dAmplitude,dOffset,dFreq:double):integer;Cdecl;
    Function	me6x00AOWrapAround(iBoardNumber,iChannel,iSize:integer;psBuffer: TMEAOBuffer):integer;Cdecl;
    
    
implementation

const dll = 'me6x00.dll';

    // General functions
    Function	me6x00FrequencyToTimer(dFreq:double): integer; external dll
    Function	me6x00GetBoardVersion(iBoardNumber: integer; VAR iVersion: integer):integer;external dll
    Function	me6x00GetDevInfo(iBoardNumber:integer; Var DevInfo:DEVICEINFOSTRUCT):integer;external dll
    Function	me6x00GetDLLVersion: integer; external dll
    Function	me6x00GetDriverVersion(VAR pBuffer:string):integer;external dll
    Function	me6x00GetSerialNumber(iBoardnumber:Integer;VAR piSerialNumber:integer):integer;external dll
    Function	me6x00GetDrvErrMess(Var Errortext:errorstring; iBufferSize:integer):integer;external dll
    
    // Analog output
    Function    me6x00AOContinuous(iBoardNumber,iChannel,iSize:integer;psBuffer: TMEAOBuffer):integer;external dll
    Function	me6x00AOContinuousEx(iBoardNumber,iChannel,iSize:integer;psBuffer: TMEAOBuffer;iLoops:integer;pCallback, pArgs:Pointer):integer;external dll
    Function	me6x00AOReset(iBoardNumber,iChannel:integer):integer;external dll
    Function	me6x00AOSetTimer(iBoardNumber,iChannel,iTicks:integer):integer;external dll
    Function	me6x00AOSetTrigger(iBoardNumber,iChannel,iModePolarity:integer):integer;external dll
    Function	me6x00AOSingle(iBoardNumber,iChannel,iValue:integer):integer;external dll
    Function	me6x00AOStart(iBoardNumber,iChannel:integer):integer;external dll
    Function	me6x00AOStop(iBoardNumber,iChannel:integer):integer;external dll
    Function	me6x00AOStopEx(iBoardNumber,iChannel:integer):integer;external dll
    Function	me6x00AOWaveGen(iBoardNumber,iChannel,iShape:integer;dAmplitude,dOffset,dFreq:double):integer;external dll
    Function	me6x00AOWrapAround(iBoardNumber,iChannel,iSize:integer;psBuffer: TMEAOBuffer):integer;external dll
    
   
end.
