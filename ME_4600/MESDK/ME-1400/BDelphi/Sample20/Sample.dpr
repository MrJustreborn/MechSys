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
/*                  1.00    020320  ew     Set Byte and read Byte                                           */
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
  iByte        : Integer;
  iValue       : Integer;


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
  Writeln('Sample 20, Set Byte and read Byte!');
  Writeln('--------------------------------',#10,#10);
  // Set the board number
  iBoardnumber := 0;
  Writeln('Please connect following pin together:');
  Writeln('Pin 21 - Pin  6, Pin 22 - Pin  7, Pin 23 - Pin  8, Pin 24 - Pin  9',#10);
  Writeln('Pin 26 - Pin  2, Pin 27 - Pin  3, Pin 28 - Pin  4, Pin 29 - Pin  5',#10,#10);
  Writeln('Press any key to continue!');

  Readln;

  iErrorCode := me1400DIOSetPortDirection(iBoardNumber, PORTA, MEOUTPUT);
  ChkErrCode;
  iErrorCode := me1400DIOSetPortDirection(iBoardNumber, PORTB, MEINPUT);
  ChkErrCode;


   begin
    {Set PortA to a value}
    for ibyte:= 0 to 255 do
      begin
      iErrorCode := me1400DOSetByte(iBoardNumber, PORTA, ibyte);
      ChkErrCode;
      {Read PortB}
      iErrorCode := me1400DIGetByte(iBoardNumber, PORTB, iValue);
      ChkErrCode;
      Writeln('Set PortA to ', ibyte,' Read PortB  = ',iValue);
      end;
    {Set PortA to 0}
    Writeln(#10,'Set PortA to 0');
    ibyte := 0;
    iErrorCode := me1400DOSetByte(iBoardNumber, PORTA, ibyte);
    ChkErrCode;

    {Read PortB}
    Writeln('Read PortB');
    iErrorCode := me1400DIGetByte(iBoardNumber, PORTB, iValue);
    ChkErrCode;
    Writeln('Value  = ',iValue);


   end;
  Writeln('Press any key to end!');
  Readln;

end.
