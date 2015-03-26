unit me8100;

interface

  type errorstring = array [0..255] of char;

  type DEVICEINFOSTRUCT = record
    dwBoardNumber: integer;          {Board number of Board}
    dwVendorID: integer;             {PCI vendor ID}
    dwDeviceID: integer;             {PCI device ID}
    dwSystemSlotNumber: integer;     {Slot number in PCI bus}
    dwPortBase: integer;             {base port address}
    dwPortCount: integer;            {Count of I/O addresses used.}
    dwIntChannel: integer;           {first Interrupt Channel}
    dwPortBasePLX: integer;          {base port address}
    dwPortCountPLX: integer;         {Count of I/O addresses used.}
    dwSerialNumber: integer;         {Serial number of the board}
    dwBusNumber: integer;            {Bus number of the PCI bus (in most cases 0)}
    dwHWRevision: integer;           {hardware revision of board}
    dwIrqCnt: integer;               {number of interrupts }
    dwVersion: integer;              {which board of the board family}
  end;

  {general routines}
  function me8100GetDLLVersion: integer; Cdecl;
  function me8100GetDrvErrMess(var cErrortext: errorstring; iBufferSize: integer): integer; Cdecl;
  function me8100GetBoardVersion(iBoardNumber: integer; var iVersion: integer): integer; Cdecl;
  function me8100PROMVersion(iBoardNumber: integer; var iVersion: integer): integer; Cdecl;
  function me8100EnableInt(iBoardNumber: integer; iRegisterSet: integer;  IrqFunc: Pointer; iContext: integer): integer; Cdecl;
  function me8100DisableInt(iBoardNumber: integer; iRegisterSet: integer): integer; Cdecl;

  {Digital I/O General Functions}
  Function me8100DIGetIntStatus(iBoardNumber: integer; iRegisterSet: integer; var piValue: integer): integer; Cdecl;
  Function me8100DIOSetIntMode(iBoardNumber: integer; iRegisterSet: integer; iMode: integer): integer; Cdecl;
  Function me8100DIOSetTristateON(iBoardNumber: integer; iRegisterSet: integer): integer; Cdecl;
  Function me8100DIOSetTristateOFF(iBoardNumber: integer; iRegisterSet: integer): integer; Cdecl;
  Function me8100DIOSetPattern(iBoardNumber: integer; iRegisterSet: integer; iPattern: integer): integer; Cdecl;
  Function me8100DIOSetMask(iBoardNumber: integer; iRegisterSet: integer; iMask: integer): integer; Cdecl;

  {Digital I/O Input-Functions}
  Function me8100DIGetBit(iBoardNumber: integer; iRegisterSet: integer; iBitNo: integer; var iBitValue: integer): integer; Cdecl;
  Function me8100DIGetWord(iBoardNumber: integer; iRegisterSet: integer; var iValue: integer): integer; Cdecl;

  {Digital I/O Output-Functions}
  Function me8100DOSetBit(iBoardNumber: integer; iRegisterSet: integer; iBitNo: integer; iBitValue: integer): integer; Cdecl;
  Function me8100DOSetWord(iBoardNumber: integer; iRegisterSet: integer; iValue: integer): integer; Cdecl;

  {New Routines}
  Function me8100GetIrqCnt(iBoardNumber: integer; iRegisterSet: integer; var iCnt: integer): integer; Cdecl;
  Function me8100GetDevInfo(iBoardNumber: integer; pDevInfo: DEVICEINFOSTRUCT): integer; Cdecl;
  Function me8100WriteUserString(iBoardNumber: integer; pcUserText: Pointer): integer; Cdecl;
  Function me8100ReadUserString(iBoardNumber: integer; pcUserText: Pointer; iMaxLength: integer): integer; Cdecl;

  {Counter 8254 functions}
  Function me8100CntWrite(iBoardNumber: integer; iCounter: integer; iMode: integer; iValue: integer): integer; Cdecl;
  Function me8100CntRead(iBoardNumber: integer; iCounter: integer; var iValue: integer): integer; Cdecl;

  {Sink/Source}
  Function me8100SetSinkSourceMode(iBoardNumber: integer; iRegisterSet: integer; imode: integer): integer; Cdecl;



implementation

const dll = 'me8100.dll';
  {general routines}
  function me8100GetDLLVersion: integer; external dll
  function me8100GetDrvErrMess(var cErrortext: errorstring; iBufferSize: integer): integer; external dll
  function me8100GetBoardVersion(iBoardNumber: integer; var iVersion: integer): integer; external dll
  function me8100PROMVersion(iBoardNumber: integer; var iVersion: integer): integer; external dll
  function me8100EnableInt(iBoardNumber: integer; iRegisterSet: integer;  IrqFunc: Pointer; iContext: integer): integer; external dll
  function me8100DisableInt(iBoardNumber: integer; iRegisterSet: integer): integer; external dll

  {Digital I/O General Functions}
  Function me8100DIGetIntStatus(iBoardNumber: integer; iRegisterSet: integer; var piValue: integer): integer; external dll
  Function me8100DIOSetIntMode(iBoardNumber: integer; iRegisterSet: integer; iMode: integer): integer; external dll
  Function me8100DIOSetTristateON(iBoardNumber: integer; iRegisterSet: integer): integer; external dll
  Function me8100DIOSetTristateOFF(iBoardNumber: integer; iRegisterSet: integer): integer; external dll
  Function me8100DIOSetPattern(iBoardNumber: integer; iRegisterSet: integer; iPattern: integer): integer; external dll
  Function me8100DIOSetMask(iBoardNumber: integer; iRegisterSet: integer; iMask: integer): integer; external dll

  {Digital I/O Input-Functions}
  Function me8100DIGetBit(iBoardNumber: integer; iRegisterSet: integer; iBitNo: integer; var iBitValue: integer): integer; external dll
  Function me8100DIGetWord(iBoardNumber: integer; iRegisterSet: integer; var iValue: integer): integer; external dll

  {Digital I/O Output-Functions}
  Function me8100DOSetBit(iBoardNumber: integer; iRegisterSet: integer; iBitNo: integer; iBitValue: integer): integer; external dll
  Function me8100DOSetWord(iBoardNumber: integer; iRegisterSet: integer; iValue: integer): integer; external dll

  {New Routines}
  Function me8100GetIrqCnt(iBoardNumber: integer; iRegisterSet: integer; var iCnt: integer): integer; external dll
  Function me8100GetDevInfo(iBoardNumber: integer; pDevInfo: DEVICEINFOSTRUCT): integer; external dll
  Function me8100WriteUserString(iBoardNumber: integer; pcUserText: Pointer): integer; external dll
  Function me8100ReadUserString(iBoardNumber: integer; pcUserText: Pointer; iMaxLength: integer): integer; external dll

  {Counter 8254 functions}
  Function me8100CntWrite(iBoardNumber: integer; iCounter: integer; iMode: integer; iValue: integer): integer; external dll
  Function me8100CntRead(iBoardNumber: integer; iCounter: integer; var iValue: integer): integer; external dll

  {Sink/Source}
  Function me8100SetSinkSourceMode(iBoardNumber: integer; iRegisterSet: integer; imode: integer): integer; external dll

end.
