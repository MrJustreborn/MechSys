program BoardInfo;

{$APPTYPE CONSOLE}

uses
  me4000defs in '..\me4000defs.pas',
  me4000dll in '..\me4000dll.pas',
  SysUtils;

var
  sText: string;
  lwDLLVersion: LongWord;
  lwDrvVersion: LongWord;
  cBoardNumber: Cardinal;
  wBoardVersion: Word;
  lwBoardSerialNumber: LongWord;
  iErrorCode: Integer;


begin

  { TODO -oUser -cConsole Main : Hier Code einfügen }

  // Enable default error procedure

  me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

  me4000GetDLLVersion(lwDLLVersion);

  sText := IntToHex(lwDLLVersion, 10);

  writeln('DLL Version:  ', sText);

  me4000GetDriverVersion(lwDrvVersion);

  sText := IntToHex(lwDrvVersion, 10);

  writeln('Driver Version:  ', sText);

  for cBoardNumber := 0 to  ME4000_MAX_DEVICES - 1 do

  begin

    // Temporarily disable default error procedure - we expect an error if the
    // corresponding board is not present in the system

    me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_DISABLE);

    iErrorCode := me4000GetBoardVersion(cBoardNumber, wBoardVersion);

    // Reenable default error procedure to catch errors

    me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

    if iErrorCode = ME4000_NO_ERROR then

    begin

      writeln('Found Board With Board Number: ', cBoardNumber);

      sText := IntToHex(wBoardVersion, 10);

      writeln('Board Version:  ', sText);

      me4000GetSerialNumber(cBoardNumber,            // uiBoardNumber
                            lwBoardSerialNumber  );  // pulSerialNumber

      sText := IntToHex(lwBoardSerialNumber, 10);

      writeln('Board Serial Number:  ', sText);

    end;

  end;

  writeln('Press RETURN to terminate');

  readln;

end.
