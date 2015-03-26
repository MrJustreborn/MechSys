program _AIWraparound;

{$APPTYPE CONSOLE}

uses
  me4000defs in '..\me4000defs.pas',
  me4000dll in '..\me4000dll.pas',
  signals in '..\signals.pas',
  SysUtils;

var

  bTerminate: Boolean;
  sText: String;
  cChannelNumber: Cardinal;
  iSignalForm: Integer;
  dFreqFrom: Double;
  dFreqTo: Double;
  dMinFrom: Double;
  dMinTo: Double;
  dMaxFrom: Double;
  dMaxTo: Double;
  iLoops: Integer;
  lwLoops: LongWord;

  arrsiSignal: array [0..9999] of Smallint;

  lwTicksLow: LongWord;
  lwTicksHigh: LongWord;

  dAchievedfreq: Double;

  iExecutionMode: Integer;

begin

  { TODO -oUser -cConsole Main : Hier Code einfügen }

  writeln('This program demonstrates the use of me4000AOWraparound to output');
  writeln('a constructed signal a definite number of times or indefinitely until');
  writeln('terminated by the user.');
  writeln;
  writeln('The signal which is generated is a sweep. You can choose from a');
  writeln('number of different basic forms. You can determine the start and end');
  writeln('frequencies and the signal limits at the start and at the end.');
  writeln('The signal will be generated on the hardware with 1000 Hz and will');
  writeln('run for ten seconds per cycle.');
  writeln;
  writeln('The signal will be output on the channel you choose of board 0.');
  writeln;
  writeln('You can choose to output a predetermined number of cycles or to');
  writeln('output the signal indefinitely, in which case you will have to press');
  writeln('RETURN to end signal generation.');
  writeln;
  writeln('By connecting the first four AO channels directly to the first four');
  writeln('AI channels and then starting the ME4600 test program you can check');
  writeln('that the signal is being output correctly.');
  writeln;
  writeln('At any time, instead of entering information you can simply press');
  writeln('RETURN to exit.');
  writeln;
  writeln('Press RETURN to begin.');

  readln;

  // Enable default error procedure

  me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

  bTerminate := False;

  cChannelNumber := 0;

  iSignalForm := 0;
  dFreqFrom := 1.0;
  dFreqTo := 4.0;
  dMinFrom :=  -2.0;
  dMinTo := -8.0;
  dMaxFrom := +2.0;
  dMaxTo :=  +8.0;

  lwLoops := 1;

  // we collect the input from the user

  repeat

    write('Channel number 0 - 3 (RETURN to exit): ');

    readln(sText);

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

  if bTerminate then Exit;

  repeat

    writeln('Signal Type: ');
    writeln('0) Rectangle');
    writeln('1) Triangle');
    writeln('2) Sinus');
    writeln('3) Positive Ramp');
    writeln('4) Negative Ramp');
    write('Your choice (RETURN to exit): ');

    readln(sText);

    if length(sText) = 0 then

    begin

      bTerminate := True;

      Break;

    end

    else if ( '0' <= sText[1] ) AND ( sText[1] <= '4' ) then

    begin

      iSignalForm := Integer (sText[1])  - Integer ('0');

      Break;

    end

  until 1 = 0;

  if bTerminate then Exit;

  repeat

    write('Start Frequency in Hz 0.1 - 10.0 (RETURN to exit): ');

    readln(sText);

    if length(sText) = 0 then

    begin

      bTerminate := True;

      Break;

    end;

    try
      dFreqFrom := StrToFloat(sText);
    except
      dFreqFrom := 0.0;
    end;

    if (+0.1 <= dFreqFrom) AND (dFreqFrom <= +10.0) then break;

  until 1 = 0;

  if bTerminate then Exit;

  repeat

    write('End Frequency in Hz 0.1 - 10.0 (RETURN to exit): ');

    readln(sText);

    if length(sText) = 0 then

    begin

      bTerminate := True;

      Break;

    end;

    try
      dFreqTo := StrToFloat(sText);
    except
      dFreqTo := 0.0;
    end;

    if (+0.1 <= dFreqTo) AND (dFreqTo <= +10.0) then break;

  until 1 = 0;

  if bTerminate then Exit;

  repeat

    write('Start Minimum -10.0 - +10.0 (RETURN to exit): ');

    readln(sText);

    if length(sText) = 0 then

    begin

      bTerminate := True;

      Break;

    end;

    try
      dMinFrom := StrToFloat(sText);
    except
      dMinFrom := -11.0;
    end;

    if (-10.0 <= dMinFrom) AND (dMinFrom <= +10.0) then break;

  until 1 = 0;

  if bTerminate then Exit;

  repeat

    write('End Minimum -10.0 - +10.0 (RETURN to exit): ');

    readln(sText);

    if length(sText) = 0 then

    begin

      bTerminate := True;

      Break;

    end;

    try
      dMinTo := StrToFloat(sText);
    except
      dMinTo := -11.0;
    end;

    if (-10.0 <= dMinTo) AND (dMinTo <= +10.0) then break;

  until 1 = 0;

  if bTerminate then Exit;

  repeat

    write('Start Maximum -10.0 - +10.0 (RETURN to exit): ');

    readln(sText);

    if length(sText) = 0 then

    begin

      bTerminate := True;

      Break;

    end;

    try
      dMaxFrom := StrToFloat(sText);
    except
      dMaxFrom := +11.0;
    end;

    if (-10.0 <= dMaxFrom) AND (dMaxFrom <= +10.0) then break;

  until 1 = 0;

  if bTerminate then Exit;

  repeat

    write('End Maximum -10.0 - +10.0 (RETURN to exit): ');

    readln(sText);

    if length(sText) = 0 then

    begin

      bTerminate := True;

      Break;

    end;

    try
      dMaxTo := StrToFloat(sText);
    except
      dMaxTo := +11.0;
    end;

    if (-10.0 <= dMaxTo) AND (dMaxTo <= +10.0) then break;

  until 1 = 0;

  if bTerminate then Exit;

  repeat

    write('Number of loops (0 = Endless) (RETURN to exit): ');

    readln(sText);

    if length(sText) = 0 then

    begin

      bTerminate := True;

      Break;

    end;

    try
      iLoops := StrToInt(sText);
    except
      iLoops := -1;
    end;

    if ( 0 <= iLoops ) then

    begin

      lwLoops := LongWord (iLoops);

      Break;

    end

  until 1 = 0;

  if bTerminate then Exit;

  // We use the Procedure Sweep in signals.pas to generate digital values
  // corresponding to the required signal in the buffer arrsiSignal

  Sweep(iSignalForm, dFreqFrom, dFreqTo, dMinFrom, dMinTo,
                           dMaxFrom, dMaxTo, 1000.0, 10000, arrsiSignal, 1);

  // We want to uutput our signal with 1000 Hz. We use the function
  // me4000FrequencyToTicks to convert the desired frequency to a number of
  // ticks which can then be passed to me4000AIConfig below

  me4000FrequencyToTicks(
    1000.0,                     // Required frequencydRequiredFreq: Double;
    lwTicksLow,                 // Low part of ticks
    lwTicksHigh,                // High part of ticks - will be 0 - not required
    dAchievedFreq );            // Achieved frequency returned here

  // We call me4000AOConfig to configure the hardware for the signal generation

  me4000AOConfig(
    0,                                // Board number
    cChannelNumber,                   // Channel number
    lwTicksLow,                       // Ticks for the AO clock
    ME4000_AO_TRIGGER_SOFTWARE,       // Trigger mode
    ME4000_VALUE_NOT_USED       );    // External trigger edge - not required

  writeln;

  writeln('Press RETURN to begin signal generation.');

  writeln;

  readln;

  if(lwLoops <> 0) then

  begin

    // A finite number of loops. We execute the wraparound operation in
    // blocking mode. The routine AOStart will not return until the operation
    // is completed

    iExecutionMode := ME4000_AO_WRAPAROUND_BLOCKING;

    writeln('Please wait ', 10 * lwLoops, ' Seconds until signal generation is complete');

    writeln;

  end

  else

  begin;

    // An endless wraparound operation. This can only be executed in
    // asynchronous mode. The routine AOStart will return immediately

    iExecutionMode := ME4000_AO_WRAPAROUND_ASYNCHRONOUS;

    writeln('Press RETURN at any time to end signal generation');

    writeln;

  end;

  // we now call me4000AOWraparound with the appropriate execution mode (see
  // above) to configure the software

  me4000AOWraparound(
    0,                          // Board number
    cChannelNumber,             // Channel number
    @arrsiSignal[0],            // Data buffer
    10000,                      // Number of data values in buffer
    lwLoops,                    // Number of loops
    iExecutionMode,             // Execution mode
    ME4000_POINTER_NOT_USED,    // Terminate routine - not used
    ME4000_POINTER_NOT_USED,    // Context for terminate - not required
    ME4000_VALUE_NOT_USED    ); // Timeout - not required

  // Finally we call AOStart to begin the output operation

  me4000AOStart(
    0,                  // Board number
    cChannelNumber);    // Channel number

  if(lwLoops = 0) then

  begin

    // Asynchronous output. AOStart will return immediately. We wait here for
    // the user to press RETURN

    readln;

    me4000AOStop(
      0,                                // Board number
      cChannelNumber,                   // Channel number
      ME4000_AO_STOP_MODE_IMMEDIATE);   // Stop mode

  end;

  writeln('Signal Generation Complete');
  writeln;
  writeln('Press RETURN to terminate the programm');

  readln;

end.
