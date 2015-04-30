unit me9000miodll;

interface

uses me9000miodefs;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Version Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

function me9000mioGetDLLVersion(var pulVersion: LongWord): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioGetDriverVersion(var pulVersion: LongWord): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioGetBoardCount(var puiCount: Cardinal): Integer;
  cdecl; external 'me9000mio.dll';

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                         Board Specific Routines                               |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Error Routines                                  |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

function me9000mioErrorSetDefaultProc(iDefaultProcStatus: Integer): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioErrorSetUserProc(pErrorProc: TME9000MIO_P_ERROR_PROC): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioErrorGetMessage(iErrorCode: Integer;
  pcBuffer: PChar; uiBufferSize: Word): Integer; cdecl; external 'me9000mio.dll';

function me9000mioErrorGetLastMessage(pcBuffer: PChar;
  uiBufferSize: Word): Integer; cdecl; external 'me9000mio.dll';


{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            General Routines                                   |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

function me9000mioGetBoardVersion(uiBoardNumber: Cardinal;
  var pusVersion: Word): Integer; cdecl; external 'me9000mio.dll';

function me9000mioGetSerialNumber(uiBoardNumber: Cardinal;
  var pulSerialNumber: LongWord): Integer; cdecl; external 'me9000mio.dll';

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               DIO Routines                                    |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

function me9000mioDIOOpen(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioDIOReset(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioDIOConfig(uiBoardNumber: Cardinal; uiBitNumber: Cardinal;
    iDirection: Integer; iInvert: Integer; iInterrupt: Integer): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioDIOGetBit(uiBoardNumber: Cardinal;
    uiBitNumber: Cardinal; var piBitValue: Integer): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioDIOSetBit(uiBoardNumber: Cardinal;
    uiBitNumber: Cardinal; iBitValue: Integer): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioDIOGetByte(uiBoardNumber: Cardinal;
    var pucByteValue: Byte): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioDIOSetByte(uiBoardNumber: Cardinal;
    ucByteValue: Byte): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioDIOOutput(uiBoardNumber: Cardinal;
    uiBitNumber: Cardinal; iOutputMode: Integer): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioDIOSetCallback(uiBoardNumber: Cardinal;
    pDIOIrqProc: TME9000MIO_P_DIO_PROC;
    pDIOIrqContext: Pointer): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioDIOGetIrqCount(uiBoardNumber: Cardinal;
    var pulCount: LongWord): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioDIOClose(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me9000mio.dll';

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Counter Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

function me9000mioCntOpen(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioCntReset(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioCntConfig(uiBoardNumber: Cardinal;
    iRetrigger: Integer; iCntEvent: Integer; iClockSource: Integer;
    iInterrupt: Integer; pCntIrqProc: TME9000MIO_P_CNT_PROC;
    pCntIrqContext: Pointer): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioCntWrite(uiBoardNumber: Cardinal;
    usValue: Word): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioCntStart(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioCntRead(uiBoardNumber: Cardinal;
    var usValue: Word): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioCntStop(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioCntGetIrqCount(uiBoardNumber: Cardinal;
    var pulCount: LongWord): Integer;
  cdecl; external 'me9000mio.dll';

function me9000mioCntClose(uiBoardNumber: Cardinal): Integer;
  cdecl; external 'me9000mio.dll';

implementation

end.
