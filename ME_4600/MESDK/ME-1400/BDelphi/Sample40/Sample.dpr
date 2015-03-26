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
/*                  1.00    020326  ew     IRQ Test                                                         */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  medefs in '..\medefs.pas',
  me1400 in '..\me1400.pas',
  SysUtils;

var

  iBoardnumber : Integer;
  iErrorCode   : Integer;
  sErrorText   : errorstring;
  iCounter     : Integer;
  iIrqNumber   : Integer;
  multipin     : Integer;


Procedure IRQFKT ;
Begin
     iCounter := iCounter + 1;
     Write('*');
End;

Procedure ChkErrCode ;
Begin
  if iErrorCode<>1 then
  begin
    me1400GetDrvErrMess(sErrorText);
    Write('Error: ', sErrorText);
    Readln;
    exit;
  end;
End;


begin

  // Set the board number
  iBoardnumber := 0;

  // using interrupts:
  iIrqNumber := 1;
  Multipin := 0;
  // activate interrupt
  iErrorCode := me1400SetMultifunctionPin(iBoardNumber, MultiPin);
  ChkErrCode;
  iErrorCode := me1400EnableInt (iBoardnumber, @IRQFKT, iIrqNumber);
  ChkErrCode;

  Writeln('Waiting on interrupts');
  Writeln('Press any key to stop this!');
  Readln;
  Writeln('Number of interrupts: ', iCounter);

  // deactivate interrupt
  iErrorCode := me1400DisableInt (iBoardnumber, iIrqNumber);
  ChkErrCode;


  Writeln('Press any key to continue!');
  Readln;

end.
