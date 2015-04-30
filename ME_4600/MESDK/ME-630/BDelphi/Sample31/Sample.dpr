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
/*                  1.01    020325  ew     IRQ call back function                                           */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  medefs in '..\medefs.pas',
  me630  in '..\me630.pas',
  SysUtils;

var
  iBoardnumber  : Integer;
  iErrorCode    : Integer;
  sErrorText    : errorstring;
  iContext      : Integer;
  iIrqNumber    : Integer;
  iCounter      : Integer;


Procedure IRQFKT(iContext: integer); stdcall;
Begin
     iCounter := iCounter + 1;
     Write('*');
End;


Procedure ChkErrCode;
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

Writeln('Sample 31 -  IRQ-Test');
  Writeln('----------------------------',#10);
  iBoardnumber := 0;
  iContext     := 1;
  iIrqNumber   := 1;


  Writeln ('IRQ 1 will be enabled');
  iErrorCode := _me630EnableInt (iBoardNumber, iIrqNumber,@IRQFKT, iContext);
  ChkErrCode;
  Writeln ('Waiting for Interrupts!!');
  Writeln ('Connect Pin 45 (VCC) with Pin 64 (IRQ 1)');
  readln;

  Writeln ('Number of interrupts = ',iCounter);
  Writeln ('IRQ 1 will be disabled');
  iErrorCode := _me630DisableInt (iBoardNumber, iIrqNumber);
  ChkErrCode;

  Writeln('Press any key to end!');
  Readln;

end.
