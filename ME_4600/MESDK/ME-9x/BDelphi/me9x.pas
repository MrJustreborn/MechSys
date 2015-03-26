unit me9x;

interface

  type errorstring = array [0..255] of char; (* For Errortext in me9xGetDrvErrMess *)

  {general routines}
  function me9xGetDLLVersion: integer; Cdecl;
  function me9xGetBoardVersion (iBoardNumber: integer; var iVersion: integer): integer; Cdecl;
  function me9xGetDrvErrMess (var cErrortext: errorstring): integer; Cdecl;
  function me94EnableInt (iBoardNumber: integer; IrqFunc: Pointer): integer; Cdecl;
  function me96EnableInt (iBoardNumber: integer; IrqFunc: Pointer): integer; Cdecl;
  function me94DisableInt (iBoardNumber: integer): integer; Cdecl;
  function me96DisableInt (iBoardNumber: integer): integer; Cdecl;

  {----------------------------------------------------------------------------}
  {digital input functions}
  Function me94DIGetBit (iBoardNumber, iBitNo: integer; var iBitValue: integer): integer; Cdecl;
  Function me96DIGetBit (iBoardNumber, iBitNo: integer; var iBitValue: integer): integer; Cdecl;
  Function me94DIGetByte (iBoardNumber, iPortNo: integer; var iValue: integer): integer; Cdecl;
  Function me96DIGetByte (iBoardNumber, iPortNo: integer; var iValue: integer): integer; Cdecl;

  {----------------------------------------------------------------------------}
  {digital output functions}
  Function me95DOSetBit (iBoardNumber, iBitNo, iBitValue: integer): integer; Cdecl;
  Function me96DOSetBit (iBoardNumber, iBitNo, iBitValue: integer): integer; Cdecl;
  Function me95DOSetByte (iBoardNumber, iPortNo, iValue: integer): integer; Cdecl;
  Function me96DOSetByte (iBoardNumber, iPortNo, iValue: integer): integer;Cdecl;


implementation

const dll = 'me9x_32.dll';   (* Name of the DLL driver file *)
  Function me9xGetDLLVersion: integer; external dll
  Function me9xGetBoardVersion (iBoardNumber: integer; var iVersion: integer): integer; external dll
  Function me9xGetDrvErrMess (var cErrortext: errorstring): integer; external dll
  Function me94EnableInt (iBoardNumber: integer; IrqFunc: Pointer): integer; external dll
  Function me96EnableInt (iBoardNumber: integer; IrqFunc: Pointer): integer; external dll
  Function me94DisableInt (iBoardNumber: integer): integer; external dll
  Function me96DisableInt (iBoardNumber: integer): integer; external dll

  Function me94DIGetBit (iBoardNumber, iBitNo: integer; var iBitValue: integer): integer; external dll
  Function me96DIGetBit (iBoardNumber, iBitNo: integer; var iBitValue: integer): integer; external dll
  Function me94DIGetByte (iBoardNumber, iPortNo: integer; var iValue: integer): integer; external dll
  Function me96DIGetByte (iBoardNumber, iPortNo: integer; var iValue: integer): integer; external dll

  Function me95DOSetBit (iBoardNumber, iBitNo, iBitValue: integer): integer; external dll
  Function me96DOSetBit (iBoardNumber, iBitNo, iBitValue: integer): integer; external dll
  Function me95DOSetByte (iBoardNumber, iPortNo, iValue: integer): integer; external dll
  Function me96DOSetByte (iBoardNumber, iPortNo, iValue: integer): integer; external dll

end.
