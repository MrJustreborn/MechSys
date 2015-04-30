unit me630;

interface

  type errorstring = array [0..255] of char;
  Type DEVICEINFOSTRUCT = record
    dwBoardNumber: integer;          {Board number of Board}
    dwVendorID: integer;             {PCI vendor ID}
    dwDeviceID: integer;             {PCI device ID}
    dwSystemSlotNumber: integer;     {Slot number in PCI bus}
    dwPortBase: integer;             {base port address}
    dwPortCount: integer;            {Count of I/O addresses used.}
    dwIntChannel: integer;           {first Interrupt Channel}
    dwPortBasePLX: integer;	     {base port address}
    dwPortCountPLX: integer;	     {Count of I/O addresses used.}
    dwSerialNumber: integer;         {Serial number of the board}
    dwBusNumber: integer;            {Bus number of the PCI bus (in most cases 0)}
    dwHWRevision: integer;           {hardware revision of board}
    dwIrqCnt: integer;               {number of interrupts }
    dwVersion: integer;              {which board of the board family}
end;
  {general routines}
  function _me630GetDLLVersion:  integer; Cdecl;
  function _me630GetDrvErrMess (var cErrortext: errorstring; iBufferSize: integer): integer; Cdecl;
  function _me630GetBoardVersion (iBoardNumber: integer; var iVersion: integer): integer; Cdecl;
  function _me630ResetRelays (iBoardNumber: integer): integer; Cdecl;
  function _me630EnableInt (iBoardNumber: integer; iIrqNumber: integer;  IrqFunc: Pointer; iContext: integer): integer; Cdecl;
  function _me630DisableInt (iBoardNumber: integer; iIrqNumber: integer): integer; Cdecl;
  
  {Digital I/O Input-Functions}
  function _me630DIGetTTLBit(iBoardNumber: integer; iBitNo: integer; var iBitValue: integer): integer; Cdecl;
  function _me630DIGetTTLByte(iBoardNumber: integer; var bValue: Byte): integer; Cdecl;
  function _me630DIGetOptoBit(iBoardNumber: integer; iBitNo: integer; var iBitValue: integer): integer; Cdecl;
  function _me630DIGetOptoByte(iBoardNumber: integer; var bValue: Byte): integer; Cdecl;

  {Digital I/O Output-Functions}
  function _me630DOSetRelayBit(iBoardNumber: integer; iBitNo: integer; iBitValue: integer): integer; Cdecl;
  function _me630DOSetRelayWord(iBoardNumber: integer; wBitValue: word): integer; Cdecl;
  function _me630DIGetRelayBit(iBoardNumber: integer; iBitNo: integer; var iBitValue: integer): integer; Cdecl;
  function _me630DIGetRelayWord(iBoardNumber: integer; var wValue: word): integer; Cdecl;

  {New Routines}
  function _me630GetIrqCnt(iBoardNumber: integer; iIRQNum: integer; var iCnt: integer): integer; Cdecl;
  function _me630GetDevInfo(iBoardNumber: integer; var DevInfo: DEVICEINFOSTRUCT): integer; Cdecl;
  function _me630WriteUserString(iBoardNumber: integer; pcUserText: Pointer): integer; Cdecl;
  function _me630ReadUserString(iBoardNumber: integer; pcUserText: Pointer; iMaxLength: integer): integer; Cdecl;

  {New DIO Routines}
  function _me630DIOResetAll(iBoardNumber: integer): integer; Cdecl;
  function _me630DIOConfig(iBoardNumber: integer; iPortNumber: integer; iPortDirection: integer): integer; Cdecl;
  function _me630DIOGetBit(iBoardNumber: integer; iPortNumber: integer; iBitNo: integer; var iBitValue: integer): integer; Cdecl;
  function _me630DIOGetByte(iBoardNumber: integer; iPortNumber: integer; var bByteValue: Byte): integer; Cdecl;
  function _me630DIOSetBit(iBoardNumber: integer; iPortNumber: integer; iBitNo: integer; iBitValue: integer): integer; Cdecl;
  function _me630DIOSetByte(int iBoardNumber; iPortNumber: integer; bByteValue: Byte): integer; Cdecl;

  {ME63 Routines for compatability with earlier versions}
  function _me63Reset (iBoardNumber: integer): integer; Cdecl;
  function _me63DIGetBit (iBoardNumber, iBitNo: integer; var iBitValue: integer): integer; Cdecl;
  function _me63DIGetByte (iBoardNumber: integer; var iValue: integer): integer; Cdecl ;
  function _me63DOSetBit (iBoardNumber, iBitNo, iBitValue: integer): integer; Cdecl;
  function _me63DOSetWord (iBoardNumber,iValue : Integer):Integer; Cdecl ;


implementation

const dll = 'me630.dll';
  {general routines}
  function _me630GetDLLVersion: integer; external dll
  function _me630GetDrvErrMess (var cErrortext: errorstring; iBufferSize: integer): integer; external dll
  function _me630GetBoardVersion (iBoardNumber: integer; var iVersion: integer): integer; external dll
  function _me630ResetRelays (iBoardNumber: integer): integer; external dll
  function _me630EnableInt (iBoardNumber: integer; iIrqNumber: integer;  IrqFunc: Pointer; iContext: integer): integer; external dll
  function _me630DisableInt (iBoardNumber: integer; iIrqNumber: integer): integer; external dll
  
  {Digital I/O Input-Functions}
  function _me630DIGetTTLBit(iBoardNumber: integer; iBitNo: integer; var iBitValue: integer): integer; external dll
  function _me630DIGetTTLByte(iBoardNumber: integer; var bValue: Byte): integer; external dll
  function _me630DIGetOptoBit(iBoardNumber: integer; iBitNo: integer; var iBitValue: integer): integer; external dll
  function _me630DIGetOptoByte(iBoardNumber: integer; var bValue: Byte): integer; external dll

  {Digital I/O Output-Functions}
  function _me630DOSetRelayBit(iBoardNumber: integer; iBitNo: integer; iBitValue: integer): integer; external dll
  function _me630DOSetRelayWord(iBoardNumber: integer; wBitValue: word): integer; external dll
  function _me630DIGetRelayBit(iBoardNumber: integer; iBitNo: integer; var iBitValue: integer): integer; external dll
  function _me630DIGetRelayWord(iBoardNumber: integer; var wValue: word): integer; external dll

  {New Routines}
  function _me630GetIrqCnt(iBoardNumber: integer; iIRQNum: integer; var iCnt: integer): integer; external dll
  function _me630GetDevInfo(iBoardNumber: integer; var DevInfo: DEVICEINFOSTRUCT): integer; external dll
  function _me630WriteUserString(iBoardNumber: integer; pcUserText: Pointer): integer; external dll
  function _me630ReadUserString(iBoardNumber: integer; pcUserText: Pointer; iMaxLength: integer): integer; external dll

  {New DIO Routines}
  function _me630DIOResetAll(iBoardNumber: integer): integer; external dll
  function _me630DIOConfig(iBoardNumber: integer; iPortNumber: integer; iPortDirection: integer): integer; external dll
  function _me630DIOGetBit(iBoardNumber: integer; iPortNumber: integer; iBitNo: integer; var iBitValue: integer): integer; external dll
  function _me630DIOGetByte(iBoardNumber: integer; iPortNumber: integer; var bByteValue: Byte): integer; external dll
  function _me630DIOSetBit(iBoardNumber: integer; iPortNumber: integer; iBitNo: integer; iBitValue: integer): integer; external dll
  function _me630DIOSetByte(int iBoardNumber; iPortNumber: integer; bByteValue: Byte): integer; external dll

  {ME63 Routines for compatability with earlier versions}
  function _me63Reset (iBoardNumber: integer): integer; external dll
  function _me63DIGetBit (iBoardNumber, iBitNo: integer; var iBitValue: integer): integer; external dll
  function _me63DIGetByte (iBoardNumber: integer; var iValue: integer): integer; external dll
  function _me63DOSetBit (iBoardNumber, iBitNo, iBitValue: integer): integer; external dll
  function _me63DOSetWord (iBoardNumber,iValue : Integer): integer; external dll

end.
