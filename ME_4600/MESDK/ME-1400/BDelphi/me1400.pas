unit me1400;

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

  {general routines}
  function me1400GetDLLVersion: integer; Cdecl;
  function me1400GetDrvErrMess (var cErrortext: errorstring): integer; Cdecl;
  function me1400EnableInt (iBoardNumber: integer; IrqFunc: Pointer;Nummer: integer): integer; Cdecl;
  function me1400DisableInt (iBoardNumber,Nummer: integer): integer; Cdecl;
  function me1400GetBoardVersion (iBoardNumber: integer; var iVersion: integer): integer; Cdecl;

  function me1400GetIrqCnt(iBoardNumber: integer; var iIrqCnt: integer): integer; Cdecl;
  function me1400GetDevInfo(iBoardNumber: integer; var DevInfo: DEVICEINFOSTRUCT): integer; Cdecl;

  function me1400InitModeTimerA(iBoardNumber: integer; CtrlWordA: integer): integer; Cdecl;
  function me1400InitModeTimerB(iBoardNumber: integer; CtrlWordB: integer): integer; Cdecl;
  function me1400SetMultifunctionPin(iBoardNumber: integer; MultiPin: integer): integer; Cdecl;



  {----------------------------------------------------------------------------}
  { Counter 8254 functions}
  function me1400CntInitSrc(iBoardNumber, iCounterNo, iCounterSource: integer): integer; Cdecl;
  function me1400CntWrite (BoardNumber, iCounterNo, iMode, iValue: integer): integer; Cdecl;
  function me1400CntRead (BoardNumber, iCounterNo: integer; var iValue: integer): integer; Cdecl;
  
  /*==============================================================*/
  // PWM functions (pulse width modulation)
  function me1400CntPWMStart(iBoardNumber, iDeviceNumber, iClockSource, iPrescaler, iDutyCycle: integer): integer; Cdecl;
  function me1400CntPWMStop(iBoardNumber, iDeviceNumber: integer): integer; Cdecl;
  /*==============================================================*/
  

  {----------------------------------------------------------------------------}
  {Digital I/O general functions}
  function me1400DIOSetPortDirection (iBoardNumber, iPortNo, iDir: integer): integer; Cdecl;

  {----------------------------------------------------------------------------}
  {digital input functions}
  Function me1400DIGetBit (iBoardNumber, iPortNo, iBitNo: integer; var iBitValue: integer): integer; Cdecl;
  Function me1400DIGetByte (iBoardNumber, iPortNo: integer; var iValue: integer): integer; Cdecl;

  {----------------------------------------------------------------------------}
  {digital output functions}
  Function me1400DOSetBit (iBoardNumber, iPortNo, iBitNo, iBitValue: integer): integer; Cdecl;
  Function me1400DOSetByte (iBoardNumber, iPortNo, iValue: integer): integer; cdecl;

  {----------------------------------------------------------------------------}



implementation

const dll = 'me1400.dll';
  Function me1400GetDLLVersion: integer; external dll
  Function me1400GetDrvErrMess (var cErrortext: errorstring): integer; external dll
  Function me1400EnableInt (iBoardNumber: integer; IrqFunc: Pointer;Nummer: integer): integer; external dll
  Function me1400DisableInt (iBoardNumber,Nummer: integer): integer; external dll
  Function me1400GetBoardVersion (iBoardNumber: integer; var iVersion: integer): integer; external dll

  Function me1400GetIrqCnt(iBoardNumber: integer; var iIrqCnt: integer): integer; external dll
  Function me1400GetDevInfo(iBoardNumber: integer; var DevInfo: DEVICEINFOSTRUCT): integer; external dll

  Function me1400InitModeTimerA(iBoardNumber: integer; CtrlWordA: integer): integer; external dll
  Function me1400InitModeTimerB(iBoardNumber: integer; CtrlWordB: integer): integer; external dll
  Function me1400SetMultifunctionPin(iBoardNumber: integer; MultiPin: integer): integer; external dll

  Function me1400CntInitSrc(BoardNumber, iCounterNo, iCounterSource: integer): integer; external dll
  Function me1400CntWrite (BoardNumber, iCounterNo, iMode, iValue: integer): integer; external dll
  Function me1400CntRead (BoardNumber, iCounterNo: integer; var iValue: integer): integer; external dll

  /*==============================================================*/
  // PWM functions (pulse width modulation)
  function me1400CntPWMStart(iBoardNumber, iDeviceNumber, iClockSource, iPrescaler, iDutyCycle: integer): integer; external dll
  function me1400CntPWMStop(iBoardNumber, iDeviceNumber: integer): integer; external dll
  /*==============================================================*/

  Function me1400DIOSetPortDirection (iBoardNumber, iPortNo, iDir: integer): integer; external dll

  Function me1400DIGetBit (iBoardNumber, iPortNo, iBitNo: integer; var iBitValue: integer): integer; external dll
  Function me1400DIGetByte (iBoardNumber, iPortNo: integer; var iValue: integer): integer; external dll

  Function me1400DOSetBit (iBoardNumber, iPortNo, iBitNo, iBitValue: integer): integer; external dll
  Function me1400DOSetByte (iBoardNumber, iPortNo, iValue: integer): integer; external dll

end.
