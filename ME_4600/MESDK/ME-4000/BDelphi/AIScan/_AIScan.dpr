program _AIScan;

{$APPTYPE CONSOLE}

uses
  me4000defs in '..\me4000defs.pas',
  me4000dll in '..\me4000dll.pas',
  SysUtils;

var

  arrbChannelList: array [0..3] of Byte;
  uiChannelNumber: Cardinal;
  lwScanTicksLowPart: LongWord;
  lwScanTicksHighPart: LongWord;
  dAchievedFreq: Double;
  arrsiScanData: array [0..79] of Smallint;
  arrsiChannelScanData: array [0..3, 0..19] of Smallint;
  lwNumberOfChannelScanData:  LongWord;
  iIndex: Integer;
  arrdVoltValue: array [0..3] of Double;

begin

  { TODO -oUser -cConsole Main : Hier Code einfügen }

  writeln('This program demonstrates the use of me4000AIScan in blocking mode.');
  writeln;
  writeln('During ten seconds values will be sampled at a sum sampling rate of');
  writeln('2Hz from the first four channels on board 0 using me4000AIScan.');
  writeln;
  writeln('Since me4000AIScan is used in blocking mode, the routine AIStart will');
  writeln('not return until all values have been sampled and are available in');
  writeln('the buffer provided');
  writeln;
  writeln('me4000AIExtractValues is then used to extract the values for each');
  writeln('individual channel from the buffer containing the digital values for');
  writeln('all the channels.');
  writeln;
  writeln('me4000AIDigitToVolt is then used to convert the digital values to');
  writeln('a physical potential.');
  writeln;
  writeln('The physical value for all four channels are displayed on the screen');
  writeln;
  writeln('Press RETURN to begin.');
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
    2.0,                        // Required frequency
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
    0,                                  // CXhannel ticks - use default
    lwScanTicksLowPart,                 // Scan ticks - low part
    lwScanTicksHighPart,                // Scan ticks - high part
    ME4000_AI_ACQ_MODE_SOFTWARE,        // Acquisition mode
    ME4000_VALUE_NOT_USED,              // External trigger mode - not required
    ME4000_VALUE_NOT_USED           );  // external trigger edge - not required

  // Next we call me4000AIScan to configure the software for the data
  // acquisition

  me4000AIScan(
    0,                                  // Board number
    20,                                 // Number of scans to make
    @arrsiScanData[0],                  // Data buffer
    80,                                 // Length of data buffer in values
    ME4000_AI_SCAN_BLOCKING,            // Execution mode - blocking
    ME4000_POINTER_NOT_USED,            // Callback routine - not used
    ME4000_POINTER_NOT_USED,            // Context for callback - not required
    ME4000_VALUE_NOT_USED,              // Refresh frequency - use default
    ME4000_POINTER_NOT_USED,            // Terminate routine - not used
    ME4000_POINTER_NOT_USED,            // Context for terminate - not required
    ME4000_VALUE_NOT_USED    );         // Timeout - not required

  // Finally we call me4000AIStart to begin the data acquisition
  // NOTE: Since we have used 'ME4000_AI_SCAN_BLOCKING' for the execution mode
  //       in me4000AIScan above, the routine AIStart will not return until the
  //       acquisition is complete. With 20 scan lists at a scan rate of 2 Hz
  //       this will take 10 seconds

  writeln('Please wait ten seconds until the acquisition is complete');
  writeln;

  me4000AIStart(0); // Board number

  // The acquisition is finished and the results are available, multiplexed, in
  // the buffer arrsiScanData

  // We now use the routine me4000AIExtractValues to extract the values for each
  // individual channel into its own buffer

  for  uiChannelNumber := 0 to 3 do

  begin

    me4000AIExtractValues(
      uiChannelNumber,                   // Channel number
      @arrsiScanData[0],                // Data buffer
      80,                               // Total number of data values
      @arrbChannelList[0],              // Start of channel list
      4,                                // Number of entries in the channel list
      @arrsiChannelScanData[uiChannelNumber][0], // Channel data returned here
      20,                               // Size of channel data buffer
      lwNumberOfChannelScanData);       // Number of values actually returned
                                        // for this channel here (must be 20)
   end;

  // Using me4000AIDigitToVolt to convert the digital values into physical
  // values we now print the results to the screen

  writeln('Channel 0 V        Channel 1 V        Channel 2 V        Channel 3 V');
  writeln('-----------        -----------        -----------        -----------');
  writeln;

  for iIndex := 0 to 19 do

  begin

    for  uiChannelNumber := 0 to 3 do

    begin

      me4000AIDigitToVolt(arrsiChannelScanData[uiChannelNumber][iIndex], // Digital value
                          ME4000_AI_RANGE_BIPOLAR_10,       // Range
                          arrdVoltValue[uiChannelNumber]);  // Physical value here


    end;

    writeln(    arrdVoltValue[0] : 8 : 3, '           ',
                arrdVoltValue[1] : 8 : 3, '           ',
                arrdVoltValue[2] : 8 : 3, '           ',
                arrdVoltValue[3] : 8 : 3                   );

  end;

  writeln;

  writeln('Press RETURN to terminate the programm');

  readln;

end.
