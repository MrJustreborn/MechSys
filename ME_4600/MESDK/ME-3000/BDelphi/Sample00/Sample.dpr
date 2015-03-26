
{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin Wisura)                                                                       */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    020327  ew     General Board Info                                               */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  medefs  in '..\medefs.pas',
  me3000  in '..\me3000.pas',
  SysUtils;

var
  iVersion      : Integer;           // DLL version number
  sVersion      : string;
  iBoardNumber  : Integer;           // board number, 0 if you use only one board
  iErrorCode    : Integer;           // error code, if 1 successfully
  iSerial       : Integer;           // serial number of the board
  sSerial       : string;
  iValue        : Integer;
  siValue       : smallint;
  sValue        : string;
  sAppl         : TMEstring;
  iScan         : Integer;
  iChan         : Integer;
  siChLstEntry  : Smallint;
  iBuffer       : tmeAIBuffer;       // array of measured data


Procedure ChkErrCode(iErrorCode: integer);
Begin
  if iErrorCode<>1 then
  begin
    Write('Error: ');
    me3000ErrorMessage(sAppl);
    Readln;
    exit;
  end;
End;


begin
  Writeln('Sample 00 - Board Parameter');
  Writeln('---------------------------',#10);

  {---------General Information---------}

  {Get DLL Version}
  iVersion := me3000GetDLLVersion;
  sVersion := IntToHex(iVersion, 8);
  Writeln('DLL version                   :   ',sVersion);

  {Set the board number}
  iBoardNumber := 0;

  sAppl[1] := 'E';
  sAppl[2] := 'r';
  sAppl[3] := 'r';
  sAppl[4] := 'o';
  sAppl[5] := 'r';

  {Get serial number}
  iErrorCode := me3000GetSerialNumber(iBoardNumber, iSerial);
  if (iErrorCode = 0) then me3000ErrorMessage(sAppl);
  sSerial := IntToHex(iSerial, 8);
  Writeln('Serial number                 :   ', sSerial,#10,#10);

  {---------DIO-------------------------}

  {Configure port A as output}
  iErrorCode := me3000DIOSetPortDirection(
        iBoardNumber,
        PORTA,
        MEOUTPUT);
  { Basically after every function call an error check ... }
  { ... by the function me3000ErrorMessage should be done  }
  if (iErrorCode = 0) then me3000ErrorMessage(sAppl);

  {Configure port B as input}
  iErrorCode := me3000DIOSetPortDirection(
        iBoardNumber,
        PORTB,
        MEINPUT);
  if (iErrorCode = 0) then me3000ErrorMessage(sAppl);

  //Set bit no. 8 of port A to high level
  iErrorCode := me3000DOSetByte(
        iBoardNumber,                   // iBoardNumber
        PORTA,                          // iPortNo
        0,                              // iByteNo
        $5);                            // iByteValue
  if (iErrorCode = 0) then me3000ErrorMessage(sAppl);
  iErrorCode := me3000DOSetBit(
        iBoardNumber,                   // iBoardNumber
        PORTA,                          // iPortNo
        12,                             // iBitNo
        1);                             // iBitValue
  if (iErrorCode = 0) then me3000ErrorMessage(sAppl);

  //Read the lower byte of port B
  iErrorCode := me3000DIGetByte(
        iBoardNumber,
        PORTB,
        LOW_BYTE,
        iValue);
  if (iErrorCode = 0) then me3000ErrorMessage(sAppl);
  sValue := IntToHex(iValue, 8);
  Writeln('DI value                 :   ', sValue,#10,#10);


  {---------AI Single --------------------------}
  iErrorCode := me3000AISingle(
        iBoardNumber,                   // iBoardNumber
        0,                              // iChannel
        AI3000_MINUS_10,                // iMode
        siValue);                       // psValue
  if (iErrorCode = 0) then me3000ErrorMessage(sAppl);
  sValue := IntToHex(siValue, 8);
  Writeln('AI value                 :   ', sValue,#10,#10);
  
  
  {---------AI Scan --------------------------}
  ChkErrCode(me3000GeneralReset(iBoardNumber));
  iErrorCode := me3000Initialize(iBoardNumber);

  //set up timer
  iScan:= me3000FrequencyToCounter(1000);
  iChan:= me3000FrequencyToCounter(300000);
  ChkErrCode(me3000AISetTimer(iBoardNumber, iScan, iChan));

  //trigger source is software timer
  ChkErrCode(me3000AISetTrigger(iBoardNumber, AI3000_Trigger_Timer));

  // set up channel list
  ChkErrCode(me3000AIClearChannelList(iBoardNumber));      // alles löschen
  ChkErrCode(me3000AIMakeChannelListEntry(0, AI3000_PLUS_10, AI3000_Single_Ended, siChLstEntry));
  ChkErrCode(me3000AIAddToChannelList(iBoardNumber, siChLstEntry));
  ChkErrCode(me3000AIMakeChannelListEntry(1, AI3000_PLUS_10, AI3000_Single_Ended, siChLstEntry));
  ChkErrCode(me3000AIAddToChannelList(iBoardNumber, siChLstEntry));

  // start scan
  ChkErrCode(me3000AIScan(iBoardNumber, iBuffer, 2, 1024, (AI3000_SCAN_TO_DISK or AI3000_INTERRUPT)));


  {---------AO--------------------------}
  //Settings for D/A conversion: D/A channel number: 2, output level
  //range: 0-10V, buffered output
  iErrorCode := me3000AOSetMode(
        iBoardNumber,                   // iBoardNumber
        0,                              // iChannel
        AO3000_MINUS_10,                // iRange
        AO3000_TRANSPARENT);            // iMode
  if (iErrorCode = 0) then me3000ErrorMessage(sAppl);

  //Write output value 0xFFF (=10V) to D/A converter
  iErrorCode := me3000AOSingle(
        iBoardNumber,                   // iBoardNumber
        0,                              // iChannel
        $C00);                          // sValue
  if (iErrorCode = 0) then me3000ErrorMessage(sAppl);

  Writeln('Press any key to end!');
  Readln;

end.
