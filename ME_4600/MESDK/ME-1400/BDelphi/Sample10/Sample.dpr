{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin Wisura)                                                                       */
/*                                                                                                          */
/*  Description:    Set Bit and read Bit                                                                    */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    020320  ew     set Bit and read Bit                                             */
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
  iValue_0     : Integer;
  iValue_2     : Integer;
  iValue_4     : Integer;
  iValue_6     : Integer;

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
  Writeln('Sample 10, Set Bit and read Bit!');
  Writeln('--------------------------------',#10,#10);
  // Set the board number
  iBoardnumber := 0;
  Writeln('Please connect following pin together:');
  Writeln('Pin 21 - Pin  6, Pin 22 - Pin  7, Pin 23 - Pin  8, Pin 24 - Pin  9',#10,#10);
  Writeln('Press any key to continue!');
  Readln;
  iErrorCode := me1400DIOSetPortDirection(iBoardNumber, PORTA, MEOUTPUT);
  ChkErrCode;
  iErrorCode := me1400DIOSetPortDirection(iBoardNumber, PORTB, MEINPUT);
  ChkErrCode;
  begin
    {Set Bit_0, Bit_2, Bit_4 and Bit_6 to logic 1 on PortA}
    Writeln(' Set Bit_0, Bit_2, Bit_4 and Bit_6 to logic 1 on PortA');
    iErrorCode := me1400DOSetBit(iBoardNumber, PORTA, Bit_0, 1);
    ChkErrCode;
    iErrorCode := me1400DOSetBit(iBoardNumber, PORTA, Bit_2, 1);
    ChkErrCode;
    iErrorCode := me1400DOSetBit(iBoardNumber, PORTA, Bit_4, 1);
    ChkErrCode;
    iErrorCode := me1400DOSetBit(iBoardNumber, PORTA, Bit_6, 1);
    ChkErrCode;
    {Read Bit_0, Bit_2, Bit_4 and Bit_6 on PortB}
    Writeln('Read Bit_0, Bit_2, Bit_4 and Bit_6 on PortB');
    iErrorCode := me1400DIGetBit(iBoardNumber, PORTB, Bit_0,  iValue_0);
    ChkErrCode;
    iErrorCode := me1400DIGetBit(iBoardNumber, PORTB, Bit_2,  iValue_2);
    ChkErrCode;
    iErrorCode := me1400DIGetBit(iBoardNumber, PORTB, Bit_4, iValue_4);
    ChkErrCode;
    iErrorCode := me1400DIGetBit(iBoardNumber, PORTB, Bit_6, iValue_6);
    ChkErrCode;
    Writeln('Bit_0  = ',iValue_0);
    Writeln('Bit_2 =  ',iValue_2);
    Writeln('Bit_4 =  ',iValue_4);
    Writeln('Bit_6 =  ',iValue_6,#10);

    {Set Bit_0, Bit_2, Bit_4 and Bit_6 to logic 0 on PortA}
    Writeln(' Set Bit_0, Bit_2, Bit_4 and Bit_6 to logic 0 on PortA');
    iErrorCode := me1400DOSetBit(iBoardNumber, PORTA, Bit_0, 0);
    ChkErrCode;
    iErrorCode := me1400DOSetBit(iBoardNumber, PORTA, Bit_2, 0);
    ChkErrCode;
    iErrorCode := me1400DOSetBit(iBoardNumber, PORTA, Bit_4, 0);
    ChkErrCode;
    iErrorCode := me1400DOSetBit(iBoardNumber, PORTA, Bit_6, 0);
    ChkErrCode;
    {Read Bit_0, Bit_2, Bit_4 and Bit_6 on PortB}
    Writeln('Read Bit_0, Bit_2, Bit_4 and Bit_6 on PortB');
    iErrorCode := me1400DIGetBit(iBoardNumber, PORTB, Bit_0,  iValue_0);
    ChkErrCode;
    iErrorCode := me1400DIGetBit(iBoardNumber, PORTB, Bit_2,  iValue_2);
    ChkErrCode;
    iErrorCode := me1400DIGetBit(iBoardNumber, PORTB, Bit_4, iValue_4);
    ChkErrCode;
    iErrorCode := me1400DIGetBit(iBoardNumber, PORTB, Bit_6, iValue_6);
    ChkErrCode;
    Writeln('Bit_0  = ',iValue_0);
    Writeln('Bit_2 =  ',iValue_2);
    Writeln('Bit_4 =  ',iValue_4);
    Writeln('Bit_6 =  ',iValue_6,#10);


   end;







  Writeln('Press any key to end!');
  Readln;

end.

