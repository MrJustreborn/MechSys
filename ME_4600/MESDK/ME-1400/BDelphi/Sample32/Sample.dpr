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
/*                  1.00    020321  ew     Retriggerable "One-Shot"                                         */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  medefs in '..\medefs.pas',
  me1400 in '..\me1400.pas',
  SysUtils;

var
  Boardnumber  : Integer;
  iErrorCode   : Integer;
  sErrorText   : errorstring;
  CtrlWordA    : Integer;
  iMode        : Integer;
  iCounterNo_0 : integer;
  ivalue_0     : integer;
  

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
  Boardnumber  := 0;
  iMode        := 1;
  iCounterNo_0 := 0;
  CtrlWordA    := 4;
  {ME1400_TIMERINTERNCLOCK_1MHZ    =0
   ME1400_TIMERCLOCKSOURCE0_INTERN =4}

  Writeln('Sample 32: Retriggerable "One-Shoot"');
  Writeln('------------------------------------');


  Writeln('Timerclock is the internal 1MHz',#10);
   iErrorCode := me1400InitModeTimerA(BoardNumber, CtrlWordA);
   ChkErrCode;
   Write ('Please input a value for Counter 0 : ');
   readln (ivalue_0);


   iErrorCode := me1400CntWrite (BoardNumber, iCounterNo_0, iMode, iValue_0);
   ChkErrCode;



   {iErrorCode := me1400CntRead (BoardNumber, iCounterNo, var iValue);
   ChkErrCode;}


  Writeln('Press any key to end!');
  Readln;

end.
