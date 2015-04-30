program _AISingle;

{$APPTYPE CONSOLE}

uses
  me4000defs in '..\me4000defs.pas',
  me4000dll in '..\me4000dll.pas',
  SysUtils;

var

  iIndex: Integer;
  siDigitalValue: Smallint;
  dVoltValue: Double;

begin

  { TODO -oUser -cConsole Main : Hier Code einfügen }

  writeln('This program demonstrates the use of me4000AISingle.');
  writeln;
  writeln('Twice a second for ten seconds a single value is sampled');
  writeln('from channel 0 on board 0 using me4000AISingle.');
  writeln;
  writeln('me4000AIDigitToVolt is then used to convert the digital');
  writeln('value to a physical potential.');
  writeln;
  writeln('Both the digital value and the physical value are displayed');
  writeln('on the screen.');
  writeln;
  writeln('Press RETURN to begin.');
  writeln;

  readln;

  // Enable default error procedure

  me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

  writeln('Digital value          Physical value V');
  writeln('-------------          ----------------');
  writeln;

  for iIndex := 0 to 19 do

  begin

    // Acquire one value from channel 0 on board 0

    me4000AISingle(
      0,                                   // Board number
      0,                                   // Channel number
      ME4000_AI_RANGE_BIPOLAR_10,          // Range
      ME4000_AI_INPUT_SINGLE_ENDED,        // S/D Mode;
      ME4000_AI_TRIGGER_SOFTWARE,          // Trigger mode
      ME4000_VALUE_NOT_USED,               // Ext trigger edge
      ME4000_VALUE_NOT_USED,               // Timeout
      siDigitalValue               );      // Digital value here

    // Convert the digital value to a physical vale

    me4000AIDigitToVolt(
      siDigitalValue,                 // Digital value
      ME4000_AI_RANGE_BIPOLAR_10,     // Range
      dVoltValue                  );  // Physical value here


  writeln(siDigitalValue, '                     ', dVoltValue : 8 : 3, ' V');

  Sleep(500);

  end;

  writeln;

  writeln('Press RETURN to terminate the programm');

  readln;

end.
