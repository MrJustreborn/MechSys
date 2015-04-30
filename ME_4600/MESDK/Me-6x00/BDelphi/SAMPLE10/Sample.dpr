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
  me6x00 in '..\me6x00.pas',
  medefs in '..\medefs.pas',
  SysUtils;

var
  iDllVersion  : Integer;
  sDllVersion  : string;
  iBoardnumber :Integer;
  iVersion     : Integer;
  iErrorCode   : Integer;
  iSerial      : Integer;
  iValue       : Integer;
  sVersion     : string;
  sErrortext   : errorstring;
  sSerial      : string;
  ichannel     : integer;
  dvolt        : extended;

Procedure ChkErrCode ;
Begin
  if iErrorCode<>1 then
  begin
    me6x00GetDrvErrMess(sErrorText,255);
    Write('Error: ', sErrorText);
    Readln;
    exit;
  end;
End;



begin

  {Function me6x00GetDllVersion}
  Writeln('Sample 01 - Board Parameter');
  Writeln('---------------------------',#10);
  {Get DLL Version}
  iDllVersion := me6x00GetDllVersion;
  sDllVersion := IntToHex(iDllVersion, 10);
  Writeln('DLL version   : ', sDllVersion);

  {Set the board number}
  iBoardnumber := 0;

  {Get Board Typ}
  iErrorCode := me6x00GetBoardVersion (iBoardnumber, iVersion);
  {Basically after every function call an error check by the function
   me6x00ErrorMessage should be done}
  ChkErrCode ;

  sVersion := IntToHex (iVersion, 10);
  Writeln('BoardVersion  : ', sVersion);


  {Get Driver SerialNumber}
  iErrorCode :=me6x00GetSerialNumber (iBoardnumber, iSerial);
  ChkErrCode ;
  sSerial := IntToHex(iSerial, 8);
  Writeln('SeriaNumber   : ', sSerial,#10,#10);


  {AO Single Out}
  Writeln('Sample 01 - AO Single Out');
  Writeln('-------------------------',#10);
  {Set Channel for Single Out}
  ichannel := 0;

  {Set Range for Single Out}
  dVolt := 4;
  ivalue := round(((2*(dVolt+10))/(20/65535))/2);
  iErrorCode := me6x00AOSingle (iBoardnumber, ichannel, ivalue);
  ChkErrCode ;
  writeln ('Volt output      = ',dVolt:8:5,' Volt   ''Hex = ',ivalue );
  writeln ('Channel number   =  ',ichannel);



   Writeln('Press any key to exit!');

  Readln;
end.

