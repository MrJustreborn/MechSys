program _AISingle;

{$APPTYPE CONSOLE}

uses
  me4000defs in '..\me4000defs.pas',
  me4000dll in '..\me4000dll.pas',
  SysUtils;

var

  bTerminate: Boolean;
  sText: String;
  cChannelNumber: Cardinal;
  dVolt: Double;
  sDigit: Smallint;


begin

  { TODO -oUser -cConsole Main : Hier Code einfügen }

  writeln('This program demonstrates the use of me4000AOSingle.');
  writeln;
  writeln('You will be repeatedly asked to enter a channel number');
  writeln('from 0 to 3 followed by a potential in Volts between -10');
  writeln('and +10.');
  writeln;
  writeln('On pressing return a third time the required potential');
  writeln('will be output to the selected channel.');
  writeln;
  writeln('By connecting the first four AO channels directly to the');
  writeln('first four AI channels and then starting the ME4600 test');
  writeln('program you can check that the correct voltage is output.');
  writeln;
  writeln('At any time, instead of entering a channel number or a');
  writeln('potential you can simply press RETURN to exit');
  writeln;
  writeln('Press RETURN to begin.');
  writeln;

  readln;

  // Enable default error procedure

  me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

  cChannelNumber := 0;

  dVolt := 0.0;

  bTerminate := False;

  repeat

    // we collect the input from the user

    repeat

      write('Channel number 0 - 3 (RETURN to exit): ');

      readln(sText);

      writeln;

      if length(sText) = 0 then

      begin

        bTerminate := True;

        Break;

      end

      else if ( '0' <= sText[1] ) AND ( sText[1] <= '3' ) then

      begin

        cChannelNumber := Cardinal (sText[1])  - Cardinal ('0');

        Break;

      end

    until 1 = 0;

    if bTerminate then Break;

    repeat

      write('Potential in Volt -10 - +10 (RETURN to exit): ');

      readln(sText);

      writeln;

      if length(sText) = 0 then

      begin

        bTerminate := True;

        Break;

      end;

      try
        dVolt := StrToFloat(sText);
      except
        dVolt := -11.0;
      end;

      if (-10.0 <= dVolt) AND (dVolt <= +10.0) then break;

    until 1 = 0;

    if bTerminate then Break;

    writeln('Press RETURN to output ', dVolt : 8 : 3,
                         ' Volts to channel ', cChannelNumber);

    readln;

    // we use me4000AOVoltToDigit to convert the physical value to a digital
    // value which can be passed to me4000AOSingle

    me4000AOVoltToDigit(dVolt,          // Physical value
                        sDigit );       // Digital value returned here

    // Now we output the required potential to the selected cahnnel on board 0
    // by calling me4000AOSingle

    me4000AOSingle(
      0,                                // Board number
      cChannelNumber,                   // Channel number
      ME4000_AO_TRIGGER_SOFTWARE,       // Trigger mode
      ME4000_VALUE_NOT_USED,            // External trigger edge - not required
      ME4000_VALUE_NOT_USED,            // Timeout - not required
      sDigit                     );     // Digital value to output

    writeln;

  until 1 = 0;

  writeln('Press RETURN to terminate the programm');

  readln;

end.
