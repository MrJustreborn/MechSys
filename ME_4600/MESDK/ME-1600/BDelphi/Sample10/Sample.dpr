{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin Wisura)                                                                       */
/*                                                                                                          */
/*  Description:    General Example AO Single Out                                                           */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    020228  ew    print board parameter and AO Single Out                           */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;
uses
  me1600 in '..\me1600.pas',
  medefs in '..\medefs.pas',
  SysUtils;

var
  iDllVersion    : Integer;
  sDllVersion    : string;
  iBoardnumber   :Integer;
  iVersion       : Integer;
  iErrorCode     : Integer;
  iSerial        : Integer;
  iValue         : Integer;
  sVersion       : string;
  sErrortext     : errorstring;
  sSerial        : string;
  dvolt          : extended;
  iChannelNumber : integer;
  iRange         : integer;
  iChannelGroup  : integer;
  iOutMode       : integer;
  ioffset        : integer;

  
Procedure ChkErrCode ;
Begin
  if iErrorCode<>1 then
  begin
    me1600GetDrvErrMess(sErrorText,255);
    Write('Error: ', sErrorText);
    Readln;
    exit;
  end;
End;

begin

  Writeln('Sample 10 - Board Parameter');
  Writeln('---------------------------',#10);

  {Get DLL Version}
  iDllVersion := me1600GetDllVersion;
  sDllVersion := IntToHex(iDllVersion, 10);
  Writeln('DLL version   : ', sDllVersion);

  {Set the board number}
  iBoardnumber := 0;

  {Get Board Typ}
  iErrorCode := me1600GetBoardVersion (iBoardnumber, iVersion);
  {Basically after every function call an error check by the function
   me1600ErrorMessage should be done}
  ChkErrCode ;
  sVersion := IntToHex (iVersion, 10);
  Writeln('BoardVersion  : ', sVersion);


  {Get Driver SerialNumber}
  iErrorCode :=me1600GetSerialNumber (iBoardnumber, iSerial);
  ChkErrCode ;
  sSerial := IntToHex(iSerial, 8);
  Writeln('SeriaNumber   : ', sSerial,#10,#10);
  Writeln('Sample 10 - AO Single Voltage Out');
  Writeln('---------------------------------',#10);
  {Set Channel for Single Out}

  {Reset board}
  iErrorCode := me1600AOResetAll( iBoardNumber );
  ChkErrCode ;
  Writeln ('Please input parameter for Single Out:');
  Write ('Channel       : ');
  read (iChannelNumber);
  Write ('Range         : ');
  read (iRange);
  { 0 = 0-10 Volt; 1 = +- 10 Volt}
  ioffset := 0  ;
  if irange = 1 then ioffset:=10;
  Write ('ChannelGroup  : ');
  read (iChannelGroup);
  { 00Hex = AO_Group_A = Channel 0...3
    01Hex = AO_Group_B = Channel 4...7
    02Hex = AO_Group_C = Channel 8...11
    03Hex = AO_Group_D = Channel 12...15}
  Writeln ('OutMode       : 0');
  iOutMode:= 0;
  { 00Hex = AO_Buffered
    01Hex = A=_Transparent};

  Write ('Volt Output   : ');
  read (dVolt);

  ivalue := round(((2*(dVolt+ioffset))/((10+ioffset)/4095))/2);

  iErrorCode := me1600AOSetRange( iBoardNumber, iChannelNumber, iRange);
  ChkErrCode ;
  iErrorCode := me1600AOSetMode(iBoardNumber, iChannelGroup, iOutMode);
  ChkErrCode ;
  iErrorCode := me1600AOSingle( iBoardNumber, iChannelNumber, iValue);
  ChkErrCode ;
  iErrorCode := me1600AOUpdate(iBoardNumber, iChannelGroup);
  ChkErrCode ;

  Readln;
  Writeln('Press any key to exit!');

  Readln;
end.

