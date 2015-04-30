program _AIScan;

{$APPTYPE CONSOLE}

// Forward declaration for callback routine

uses
  me4000defs in '..\me4000defs.pas',
  me4000dll in '..\me4000dll.pas',
  SysUtils;

var

  arrbChannelList: array [0..3] of Byte;

  // Callback ist the routine which is installed with me4000AIContinuous below
  // and which will be called automatically at regular intervals to pass us the
  // newly acquired data

  procedure Callback(psValues: Pointer; uiNumberOfValues: Cardinal;
                      pCallbackContext: Pointer; iLastError: Integer); stdcall;

var

  uiChannelNumber: Cardinal;
  arrsiChannelScanData: array [0..3, 0..39] of Smallint;
  lwNumberOfChannelScanData:  LongWord;
  arrdVoltValue: array [0..3] of Double;
  lwIndex: longWord;

begin

  // The newest data is available, multiplexed, in the buffer psValues

  // We now use the routine me4000AIExtractValues to extract the values for each
  // individual channel into its own buffer.

  // Since we have set the refresh frequency t0 5, we would expect the buffer
  // psValues to contain 5 data values for each channel. We pass a buffer
  // long enough to hold up to 40 values and tghis should be large enough in any
  // case

  for  uiChannelNumber := 0 to 3 do

  begin

    me4000AIExtractValues(
      uiChannelNumber,                   // Channel number
      psValues,                         // Data buffer
      uiNumberOfValues,                 // Total number of data values
      @arrbChannelList[0],              // Start of channel list
      4,                                // Number of entries in the channel list
      @arrsiChannelScanData[uiChannelNumber][0], // Channel data returned here
      40,                               // Size of channel data buffer
      lwNumberOfChannelScanData);       // Number of values actually returned
                                        // for this channel here
   end;

  // Using me4000AIDigitToVolt to convert the digital values into physical
  // values we now print the results to the screen

  for lwIndex := 0 to lwNumberOfChannelScanData - 1 do

  begin

    for  uiChannelNumber := 0 to 3 do

    begin

      me4000AIDigitToVolt(arrsiChannelScanData[uiChannelNumber][lwIndex], // Digital value
                          ME4000_AI_RANGE_BIPOLAR_10,       // Range
                          arrdVoltValue[uiChannelNumber]);  // Physical value here


    end;

    writeln(    arrdVoltValue[0] : 8 : 3, '           ',
                arrdVoltValue[1] : 8 : 3, '           ',
                arrdVoltValue[2] : 8 : 3, '           ',
                arrdVoltValue[3] : 8 : 3                   );

  end;


  begin



  end

end;


var

  uiChannelNumber: Cardinal;
  lwScanTicksLowPart: LongWord;
  lwScanTicksHighPart: LongWord;
  dAchievedFreq: Double;

begin

  { TODO -oUser -cConsole Main : Hier Code einfügen }

  writeln('This program demonstrates the use of me4000AIContinuous together');
  writeln('with a callback routine.');
  writeln;
  writeln('Values will be sampled at a sum sampling rate of 10 Hz from the first');
  writeln('four channels on board 0 using me4000AIContinuous.');
  writeln;
  writeln('me4000AIContinuous will install a callback routine which will');
  writeln('be called automatically at regular intervals during the acquisition');
  writeln('and which receives as a parameter a pointer to the newly acquired data.');
  writeln;
  writeln('In the callback routine, me4000AIExtractValues will be used to');
  writeln('extract the values for each individual channel from the buffer');
  writeln('containing the digital values for all the channels.');
  writeln;
  writeln('me4000AIDigitToVolt is then used to convert the digital values to');
  writeln('a physical potential.');
  writeln;
  writeln('The physical value for all four channels are displayed on the screen.');
  writeln;
  writeln('Please press RETURN to start the data acquisition');
  writeln;
  writeln('Press RETURN again at any time to terminate the operation');
  writeln;

  readln;

  // Enable default error procedure

  me4000ErrorSetDefaultProc(ME4000_ERROR_DEFAULT_PROC_ENABLE);

  // First we construct our channel list using me4000AIMakeChannelListEntry
  // The channel list will be passed to me4000AIConfig below

  for  uiChannelNumber := 0 to 3 do

  begin

    me4000AIMakeChannelListEntry(
      uiChannelNumber,                          // Channel number
      ME4000_AI_RANGE_BIPOLAR_10,               // Range
      arrbChannelList[uiChannelNumber]);        // Channel list entry

  end;

  // Then we use me4000FrequencyToTicks to convert our required frequency (2Hz)
  // to a number of ticks which can be passed to me4000AIConfig below

  me4000FrequencyToTicks(
    10,                         // Required frequency
    lwScanTicksLowPart,         // Ticks low part here
    lwScanTicksHighPart,        // Ticks high part here
    dAchievedFreq          );            // Achieved frequency returned here

  // Now we call me4000AIConfig to configure the hardware for the data
  // acquisition

  me4000AIConfig(
    0,                                  // Board number
    @arrbChannelList[0],                // Start of channel list
    4,                                  // Number of entries in the channel list
    ME4000_AI_INPUT_SINGLE_ENDED,       // S/D mode
    ME4000_AI_SIMULTANEOUS_DISABLE,     // NOT using simultaneous acquisition
    ME4000_VALUE_NOT_USED,              // Reserved - must use this value
    0,                                  // Channel ticks - use default
    lwScanTicksLowPart,                 // Scan ticks - low part
    lwScanTicksHighPart,                // Scan ticks - high part
    ME4000_AI_ACQ_MODE_SOFTWARE,        // Acquisition mode
    ME4000_VALUE_NOT_USED,              // External trigger mode - not required
    ME4000_VALUE_NOT_USED           );  // external trigger edge - not required

  // Next we call me4000AIContinuous to configure the software for the data
  // acquisition.

  // NOTE: By setting the refresh frequency to 5 we are saying we would like our
  //       callback routine to be called every time 5 new values for each
  //       channel (4 x 5 = 20 data values altogether) have accumulated.
  //       Since we are acquiring data with a sum sampling rate of 10 Hz we
  //       would expect our routine to be called approximately twice a second

  me4000AIContinuous(
    0,                                  // Board number
    Callback,                           // Callback function
    ME4000_POINTER_NOT_USED,            // Callback context - not used
    5,                                  // Refresh frequency - see above
    ME4000_VALUE_NOT_USED    );         // Timeout - not required


  // Finally we call me4000AIStart to begin the data acquisition
  // NOTE: The routine AIStart will rerturn immediately and the data acquisition
  //       will take place in the background untill AIStop is called

  me4000AIStart(0); // Board number

  readln;

  // We call AIStop to terminate teh acquisitoion

  me4000AIStop(
    0,                          // Board number
    ME4000_VALUE_NOT_USED);     // Reserved - must use this value


  writeln('Acquisition terminated');

  writeln;

  writeln('Press RETURN to terminate the programm');

  readln;

end.


