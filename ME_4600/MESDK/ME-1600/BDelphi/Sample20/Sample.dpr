{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin Wisura)                                                                       */
/*                                                                                                          */
/*  Description:    General Example AO Current Single Out                                                   */
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
  iBoardnumber   : Integer;
  iVersion       : Integer;
  iErrorCode     : Integer;
  iSerial        : Integer;
  iValue         : Integer;
  sVersion       : string;
  sErrortext     : errorstring;
  sSerial        : string;
  dCurrent       : extended;
  iChannelNumber : integer;
  iRange         : integer;
  iChannelGroup  : integer;
  iOutMode       : integer;
  ioffset        : integer;
  icurrentmode   : integer;


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

  {Function me1600GetDllVersion}
  Writeln('Sample 20 - Board Parameter');
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
  
  Writeln('Sample 20 - AO Single Current Out');
  Writeln('---------------------------------',#10);
  {Set Channel for Single Out}
  {Reset board}
  iErrorCode := me1600AOResetAll( iBoardNumber );
  ChkErrCode ;
  Writeln ('Please input parameter for Current Single Out:');
  Writeln('-----------------------------------------------',#10);

  iCurrentMode := 1;
  { AO_Current_Off = 0
    AO-Current_On  = 1}
  Write ('Channel       : ');
  read (iChannelNumber);
  Write ('Range         : ');
  read (iRange);
  { 0 = 0-20mA; 1 = 4-20mA}
  ioffset := 0  ;
  if irange = 1 then ioffset:=4;
  Write ('ChannelGroup  : ');
  read (iChannelGroup);
  { 00Hex = AO_Group_A = Channel 0...3
    01Hex = AO_Group_B = Channel 4...7
    02Hex = AO_Group_C = Channel 8...11
    03Hex = AO_Group_D = Channel 12...15}
  Writeln ('OutMode       : 0');
  iOutMode:=0;
  { 00Hex = AO_Buffered
    01Hex = A=_Transparent};

  Write ('Current Output   : ');
  read (dCurrent);

  ivalue := round(((2*(dCurrent-ioffset))/((20-ioffset)/4095))/2);

  iErrorCode := me1600AOSetCurrent( iBoardNumber, iChannelNumber, iCurrentMode, iRange);
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


