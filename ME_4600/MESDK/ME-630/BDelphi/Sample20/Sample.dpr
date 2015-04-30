 {*---------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin Wisura)                                                                       */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.01    020325  ew     Set Relay out                                                    */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  medefs in '..\medefs.pas',
  me630 in '..\me630.pas',
  SysUtils;

var
  iBoardnumber  : Integer;
  iErrorCode    : Integer;
  sErrorText    : errorstring;
  iBitNo        : Integer;
  iBitValue     : integer;
  iBitValueo    : integer;
  wBitValue     : integer;
  wValue        : word;


Procedure ChkErrCode ;
Begin
  if iErrorCode<>1 then
  begin
    _me630GetDrvErrMess(sErrorText,255);
    Write('Error: ', sErrorText);
    Readln;
    exit;
  end;
End;

begin

Writeln('Sample 20 -  Set Relay');
  Writeln('----------------------',#10);
  iBoardnumber := 0;
  iBitNo       := 0;
  iBitValue    := 1;
  wBitValue    := 255;

  iErrorCode := _me630DOSetRelayBit(iBoardNumber, iBitNo, iBitValue);
  ChkErrCode;
  Writeln ('Set Relay Bitnumber 0  = ',iBitValue);
  iErrorCode := _me630DOSetRelayWord(iBoardNumber, wBitValue);
  ChkErrCode;
  Writeln ('Set Relay Word         = ',wBitValue,#10);
  iErrorCode := _me630DIGetRelayBit(iBoardNumber, iBitNo, iBitValueo);
  ChkErrCode;
  Writeln ('Read Relay Bitnumber ',iBitNo,' = ',iBitValueo);
  iErrorCode := _me630DIGetRelayWord(iBoardNumber, wValue);
  ChkErrCode;
  Writeln ('Read Relay Byte        = ',wValue,#10);
  Writeln('Press any key to reset Relay');
  Readln;
  iErrorCode := _me630ResetRelays (iBoardNumber);
  ChkErrCode;


  Writeln('Press any key to end!');
  Readln;

end.
