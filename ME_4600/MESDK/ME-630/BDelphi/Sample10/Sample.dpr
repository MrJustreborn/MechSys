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
/*                  1.01    020325  ew     Get digital Input                                                */
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
  bValue        : byte;
  iBitValue     : integer;
  bValueo       : byte;
  iBitValueo    : integer;



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

Writeln('Sample 10 -  Get Digital Input');
  Writeln('----------------------------',#10);
  iBoardnumber := 0;
  iBitNo       := 0;


  iErrorCode := _me630DIGetTTLBit(iBoardNumber, iBitNo, iBitValue);
  ChkErrCode;
  Writeln ('TTL Bitnumber 0  = ',iBitValue);
  iErrorCode := _me630DIGetTTLByte(iBoardNumber, bValue);
  ChkErrCode;
  Writeln ('TTL Byte         = ',bValue);
  iErrorCode := _me630DIGetOptoBit(iBoardNumber, iBitNo, iBitValueo);
  ChkErrCode;
  Writeln ('Opto Bitnumber 0 = ',iBitValueo);
  iErrorCode := _me630DIGetOptoByte(iBoardNumber, bValueo);
  ChkErrCode;
  Writeln ('Opto Byte        = ',bValueo);



  Writeln('Press any key to end!');
  Readln;

end.
