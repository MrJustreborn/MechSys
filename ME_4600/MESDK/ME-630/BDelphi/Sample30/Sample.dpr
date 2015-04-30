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
/*                  1.01    020325  ew     IRQ Test                                                         */
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
  iIRQNum       : Integer;
  iContext      : Integer;
  iCnt          : Integer;
  iIrqNumber    : Integer;
  iCounter      : Integer;




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

Writeln('Sample 30 -  IRQ-Test');
  Writeln('----------------------',#10);
  iBoardnumber := 0;
  iIRQNum      := 1;
  iContext     := 1;
  iIrqNumber   := 1;


  Writeln ('IRQ 1 will be enabled');
  iErrorCode := _me630EnableInt (iBoardNumber, iIrqNumber,0, iContext);
  ChkErrCode;
  iErrorCode := _me630GetIrqCnt(iBoardNumber, iIRQNum, iCnt);
  ChkErrCode;
  Writeln ('Number of interrupts = ',iCnt);
  Writeln ('Waiting for Interrupts!!');
  Writeln ('Connect Pin 45 (VCC) with Pin 64 (IRQ 1)');
  readln;
  iErrorCode := _me630GetIrqCnt(iBoardNumber, iIRQNum, iCnt);
  ChkErrCode;
  Writeln ('Number of interrupts = ',iCnt);
  Writeln ('IRQ 1 will be disabled');
  iErrorCode := _me630DisableInt (iBoardNumber, iIrqNumber);
  ChkErrCode;

  Writeln('Press any key to end!');
  Readln;

end.
