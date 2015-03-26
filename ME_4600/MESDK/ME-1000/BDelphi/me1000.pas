unit me1000;

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

  {General Routines}
  function me1000GetDLLVersion: integer; Cdecl;
  function me1000GetBoardVersion(iBoardNumber: integer; var iVersion: integer): integer; Cdecl;
  function me1000GetDevInfo(iBoardNumber: integer; Var DevInfo:DEVICEINFOSTRUCT): integer; Cdecl;
  function me1000GetDriverVersion(var iDriverVersion: integer): integer; Cdecl;
  function me1000GetSerialNumber(iBoardNumber: integer; var iSerialNumber: integer): integer; Cdecl;
  function me1000ReadUserString(iBoardNumber: integer; UserText: Pointer; iMaxLength: integer): integer; Cdecl;
  function me1000WriteUserString(iBoardNumber: integer; UserText: Pointer): integer; Cdecl;
  function me1000GetDrvErrMess(var Errortext: errorstring; iBufferSize: integer): integer; Cdecl;

  {Digital I/O Functions}
  function me1000DIOSetPortDirection(iBoardNumber: integer; iPortNumber: integer; iDirection: integer): integer; Cdecl;
  function me1000DIOReset(iBoardNumber: integer): integer; Cdecl;

  function me1000DIGetBit (iBoardNumber: integer; iPortNumber: integer; iBitNo:  integer; var iValue: integer): integer; Cdecl;
  function me1000DIGetByte(iBoardNumber: integer; iPortNumber: integer; iByteNo: integer; var iValue: integer): integer; Cdecl;
  function me1000DIGetWord(iBoardNumber: integer; iPortNumber: integer; iWordNo: integer; var iValue: integer): integer; Cdecl;
  function me1000DIGetLong(iBoardNumber: integer; iPortNumber: integer; var iValue: integer): integer; Cdecl;

  function me1000DOSetBit (iBoardNumber: integer; iPortNumber: integer; iBitNo:  integer; iValue: integer): integer; Cdecl;
  function me1000DOSetByte(iBoardNumber: integer; iPortNumber: integer; iByteNo: integer; iValue: integer): integer; Cdecl;
  function me1000DOSetWord(iBoardNumber: integer; iPortNumber: integer; iWordNo: integer; iValue: integer): integer; Cdecl;
  function me1000DOSetLong(iBoardNumber: integer; iPortNumber: integer; iValue: cardinal): integer; Cdecl;


implementation

const dll = 'me1000.dll';

  // General Routines
  function me1000GetBoardVersion(iBoardNumber: integer; var iVersion: integer): integer; external dll
  function me1000GetDevInfo(iBoardNumber: integer; Var DevInfo:DEVICEINFOSTRUCT): integer; external dll
  function me1000GetDLLVersion: integer; external dll
  function me1000GetDriverVersion(var iDriverVersion: integer): integer; external dll
  function me1000GetSerialNumber(iBoardNumber: integer; var iSerialNumber: integer): integer; external dll
  function me1000ReadUserString(iBoardNumber: integer; UserText: Pointer; iMaxLength: integer): integer; external dll
  function me1000WriteUserString(iBoardNumber: integer; UserText: Pointer): integer; external dll
  function me1000GetDrvErrMess(var Errortext: errorstring; iBufferSize: integer): integer; external dll

  // Digital I/O Functions
  function me1000DIOSetPortDirection(iBoardNumber: integer; iPortNumber: integer; iDirection: integer): integer; external dll
  function me1000DIOReset(iBoardNumber: integer): integer; external dll

  function me1000DIGetBit (iBoardNumber: integer; iPortNumber: integer; iBitNo:  integer; var iValue: integer): integer; external dll
  function me1000DIGetByte(iBoardNumber: integer; iPortNumber: integer; iByteNo: integer; var iValue: integer): integer; external dll
  function me1000DIGetWord(iBoardNumber: integer; iPortNumber: integer; iWordNo: integer; var iValue: integer): integer; external dll
  function me1000DIGetLong(iBoardNumber: integer; iPortNumber: integer; var iValue: integer): integer; external dll

  function me1000DOSetBit (iBoardNumber: integer; iPortNumber: integer; iBitNo:  integer; iValue: integer): integer; external dll
  function me1000DOSetByte(iBoardNumber: integer; iPortNumber: integer; iByteNo: integer; iValue: integer): integer; external dll
  function me1000DOSetWord(iBoardNumber: integer; iPortNumber: integer; iWordNo: integer; iValue: integer): integer; external dll
  function me1000DOSetLong(iBoardNumber: integer; iPortNumber: integer; iValue: cardinal): integer; external dll

end.
