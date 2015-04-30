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
/*                  1.00    020320  ew     Symetric divider                                                 */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  medefs in '..\medefs.pas',
  me1400 in '..\me1400.pas',
  SysUtils;

var
  Boardnumber  :Integer;
  iErrorCode   : Integer;
  sErrorText   : errorstring;
  CtrlWordA    : Integer;
  iMode        : Integer;
  iCounterNo_0 : integer;
  iCounterNo_1 : integer;
  iCounterNo_2 : integer;
  ivalue_0     : integer;
  ivalue_1     : integer;
  ivalue_2     : integer;
  value        : real;

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
  iMode        := 3;
  iCounterNo_0 := 0;
  iCounterNo_1 := 1;
  iCounterNo_2 := 2;
  CtrlWordA    := 7;
  {ME1400_TIMERINTERNCLOCK_1MHZ    =0
   ME1400_TIMERCLOCKSOURCE0_INTERN =4
   ME1400_TIMERCLOCKSOURCE1_OUT0   =2
   ME1400_TIMERCLOCKSOURCE2_OUT1   =1     }

  Writeln('Sample 30: Frequncy divider');
  Writeln('---------------------------');
  
  Writeln('Counter will be defined as a "Symetrical divider"');
  Writeln('Timerclock is the internal 1MHz',#10);
   iErrorCode := me1400InitModeTimerA(BoardNumber, CtrlWordA);
   ChkErrCode;
   Write ('Please input a value for Counter 0 : ');
   readln (ivalue_0);
   Write ('Please input a value for Counter 1 : ');
   readln (ivalue_1);
   Write ('Please input a value for Counter 2 : ');
   readln (ivalue_2);
   value := (1000000/(ivalue_0*ivalue_1*ivalue_2));
   Writeln(#10,'Output frequency on Pin 19 is ',value:9:2,' Hz');
   iErrorCode := me1400CntWrite (BoardNumber, iCounterNo_0, iMode, iValue_0);
   ChkErrCode;

   iErrorCode := me1400CntWrite (BoardNumber, iCounterNo_1, iMode, iValue_1);
   ChkErrCode;

   iErrorCode := me1400CntWrite (BoardNumber, iCounterNo_2, iMode, iValue_2);
   ChkErrCode;

   {iErrorCode := me1400CntRead (BoardNumber, iCounterNo, var iValue);
   ChkErrCode;}


  Writeln('Press any key to end!');
  Readln;

end.
