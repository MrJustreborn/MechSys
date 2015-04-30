

// Supports ME-1600, ME-160

{
    IMPORTANT NOTE :
        only for use with Borland Delphi V4.0 or later
        for other compilers you must change the macro
         into the form your compiler needs to
        import functions from an external dll !
}
unit me1600;

interface
Type errorstring = array [0..255] of char;
Type DeviceInfoStruct = record

       dwBoardNumber      : integer;     {Board number of Board}
       dwVendorID         : integer;     {PCI vendor ID}
       dwDeviceID         : integer;     {PCI device ID}
       dwSystemSlotNumber : integer;     {Slot number in PCI bus}
       dwPortBase         : integer;     {base port address}
       dwPortCount        : integer;     {Count of I/O addresses used.}
       dwIntChannel       : integer;     {first Interrupt Channel}
       dwPortBasePLX      : integer;     {base port address }
       dwPortCountPLX     : integer;     {Count of I/O addresses used}
       dwSerialNumber     : integer;     {Serial number of the board }
       dwBusNumber        : integer;     {Bus number of the PCI bus (in most cases 0)}
       dwHWRevision       : integer;     {hardware revision of board}
       dwIrqCnt           : integer;     {number of interrupts}
       dwVersion          : integer;     {which board of the board family}
       end;

   // ME-1600 Routines

   // General Routines

   Function me1600GetDLLVersion : integer; Cdecl;

   Function me1600GetDriverVersion(Var pBuffer : string) : integer; Cdecl;

   Function me1600GetBoardVersion(iBoardNumber : integer; Var iVersion : integer) : integer; Cdecl;

   Function me1600GetSerialNumber(iBoardNumber : integer; Var piSerialNumber : integer) : integer; Cdecl;

   Function me1600GetDevInfo(iBoardNumber : integer; Var DevInfo : DEVICEINFOSTRUCT) : integer; Cdecl;

   Function me1600WriteUserString(iBoardNumber : integer; pcUserText: Pointer) : integer; Cdecl;

   Function me1600ReadUserString(iBoardNumber : integer; pcUserText: Pointer; iMaxLength : integer) : integer; Cdecl;

   Function me1600GetDrvErrMess(Var Errortext : errorstring; iBufferSize : integer) : integer; Cdecl;



   // Analog I/O output Functions

   Function me1600AOSetMode(iBoardNumber, iChannelGroup, iOutMode : integer) : integer; Cdecl;
                              {iBoardNumber  = BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                               iChannelGroup = AO_GROUP_A, AO_GROUP_B, AO_GROUP_C, AO_GROUP_D
                               iOutMode      = AO_BUFFERED, AO_TRANSPARENT}


   Function me1600AOSetRange( iBoardNumber, iChannelNumber, iRange : integer) : integer; Cdecl;
                              {iBoardNumber   = BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                               iChannelNumber = AO_CHAN_00, AO_CHAN_01, ..., AO_CHAN_15
                               iRange         = AO_BIPOLAR, AO_UNIPOLAR}

   Function me1600AOSingle( iBoardNumber, iChannelNumber, iValue : integer) : integer; Cdecl;
                              {iBoardNumber   = BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                               iChannelNumber = AO_CHAN_00, AO_CHAN_01, ..., AO_CHAN_15
                               iValue         = 0x000..0xFFF}

   Function me1600AOUpdate( iBoardNumber,  iChannelGroup : integer) : integer; Cdecl;
                              {iBoardNumber  = BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                              iChannelGroup = AO_GROUP_A, AO_GROUP_B, AO_GROUP_C, AO_GROUP_D}

   Function me1600AOUpdateAll( iBoardNumber : integer ) : integer; Cdecl;
                              {iBoardNumber   = BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31}

   Function me1600AOResetAll( iBoardNumber : integer) : integer; Cdecl;
                              {iBoardNumber   = BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31}


   Function me1600AOSetCurrent( iBoardNumber, iChannelNumber,  iCurrentMode, iRange : integer) : integer; Cdecl;
                              {iBoardNumber   = BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                               iChannelNumber = AO_CHAN_00, AO_CHAN_01, ..., AO_CHAN_15
                               iCurrentMode   = AO_CURRENT_ON, AO_CURRENT_OFF
                               iRange         = AO_RANGE_0_20, AO_RANGE_4_20}

implementation

const dll = 'me1600.dll';

// General Routines

   Function me1600GetDLLVersion : integer; external dll

   Function me1600GetDriverVersion(Var pBuffer : string) : integer; external dll

   Function me1600GetBoardVersion(iBoardNumber : integer; Var iVersion : integer) : integer; external dll

   Function me1600GetSerialNumber(iBoardNumber : integer; Var piSerialNumber : integer) : integer; external dll

   Function me1600GetDevInfo(iBoardNumber : integer; Var DevInfo : DEVICEINFOSTRUCT) : integer; external dll

   Function me1600WriteUserString(iBoardNumber : integer; pcUserText: Pointer) : integer; external dll

   Function me1600ReadUserString(iBoardNumber : integer; pcUserText: Pointer; iMaxLength : integer) : integer; external dll

   Function me1600GetDrvErrMess(Var Errortext : errorstring; iBufferSize : integer) : integer;external dll




   // Analog I/O output Functions

   Function me1600AOSetMode(iBoardNumber, iChannelGroup, iOutMode : integer) : integer; external dll

   Function me1600AOSetRange( iBoardNumber, iChannelNumber, iRange : integer) : integer; external dll

   Function me1600AOSingle( iBoardNumber, iChannelNumber, iValue : integer) : integer; external dll

   Function me1600AOUpdate( iBoardNumber,  iChannelGroup : integer) : integer; external dll

   Function me1600AOUpdateAll( iBoardNumber : integer) : integer; external dll

   Function me1600AOResetAll( iBoardNumber : integer) : integer; external dll

   Function me1600AOSetCurrent( iBoardNumber, iChannelNumber,  iCurrentMode, iRange : integer) : integer; external dll


end.
