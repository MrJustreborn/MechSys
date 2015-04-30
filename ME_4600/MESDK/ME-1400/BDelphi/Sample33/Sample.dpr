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
/*                  1.00    020321  ew     Regtriggerable "One Shot_1"                                      */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  medefs in '..\medefs.pas',
  me1400 in '..\me1400.pas',
  SysUtils;

var
  Boardnumber   : Integer;
  iErrorCode    : Integer;
  sErrorText    : errorstring;
  CtrlWordA     : Integer;
  iMode         : Integer;
  iCounterNo_0  : integer;
  iCounterNo_1  : integer;
  iCounterNo_2  : integer;
  iCounterNo_0B : integer;
  ivalue_0      : integer;
  ivalue_1      : integer;
  ivalue_2      : integer;
  ivalue_0B     : integer;
  value         : real;
  iModeb        : integer;
  CtrlWordB     : integer;

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
  iModeB       := 1;
  iCounterNo_0 := 0;
  iCounterNo_1 := 1;
  iCounterNo_2 := 2;
  iCounterNo_0B:= 3;
  CtrlWordA    := 7;
  {ME1400_TIMERINTERNCLOCK_10MHZ    = 0
   ME1400_TIMERCLOCKSOURCE0_INTERN = 4
   ME1400_TIMERCLOCKSOURCE1_OUT0   = 2
   ME1400_TIMERCLOCKSOURCE2_OUT1   = 1     }
  CtrlWordB    := 0;
  Writeln('Sample 33: Retriggerable "One Shot"');
  Writeln('----------------------------------');

  Writeln('Internal Clock 1MHz will be divieded to 100 Hz');
   iErrorCode := me1400InitModeTimerA(BoardNumber, CtrlWordA);
   ChkErrCode;
   ivalue_0 := 100;
   ivalue_1 := 10;
   ivalue_2 := 10;
   value := (1000000/(ivalue_0*ivalue_1*ivalue_2));
   Writeln(#10,'Output frequency on Pin 19 is ',value:9:2,' Hz',#10);
   iErrorCode := me1400CntWrite (BoardNumber, iCounterNo_0, iMode, iValue_0);
   ChkErrCode;

   iErrorCode := me1400CntWrite (BoardNumber, iCounterNo_1, iMode, iValue_1);
   ChkErrCode;

   iErrorCode := me1400CntWrite (BoardNumber, iCounterNo_2, iMode, iValue_2);
   ChkErrCode;
   Writeln('Connect Pin 19(Out2) with Pin 54(CLK3)');
   Writeln('--------------------------------------');
   iErrorCode := me1400InitModeTimerB(BoardNumber, CtrlWordB);
   ChkErrCode;

   ivalue_0B := 200;


   iErrorCode := me1400CntWrite (BoardNumber, iCounterNo_0B, iModeB, iValue_0B);
   ChkErrCode;
   Writeln('to start the "one Shot",',#10,'trigger with connecting Pin 74 with Pin 20');
   Writeln('Output will be low for 2 seconds!!');
   Writeln('------------------------------------------');

  Writeln('Press any key to end!');
  Readln;

end.
