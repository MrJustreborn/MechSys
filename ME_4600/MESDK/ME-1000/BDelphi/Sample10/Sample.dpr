{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    Sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin wisura)                                                                       */
/*                                                                                                          */
/*  Description:    set Bit and read bit                                                                    */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    020319  ew     set Bit and read bit                                             */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  me1000  in '..\me1000.pas',
  medefs  in '..\medefs.pas',
  SysUtils;


var
  iBoardnumber : Integer;
  iErrorCode   : Integer;
  sErrorText   : errorstring;
  iValue_0     : Integer;
  iValue_8     : Integer;
  iValue_16    : Integer;
  iValue_24    : Integer;
  iCounter     : Integer;



Procedure ChkErrCode ;
Begin
  if iErrorCode<>1 then
  begin
    me1000GetDrvErrMess(sErrorText,255);
    Write('Error: ', sErrorText);
    Readln;
    exit;
  end;
End;
  
Procedure IRQFKT ;
Begin
     iCounter := iCounter + 1;
End;


begin
  Writeln('Sample 10, Set Bit and read Bit!');
  Writeln('--------------------------------',#10,#10);
  iBoardNumber := 0;
  iErrorCode := me1000DIOReset(iBoardNumber);
  // Basically after every function call an error check by the function
  ChkErrCode ;

  Writeln('Please connect following pin together:');
  Writeln('Pin 22 - Pin 30, Pin 24 - Pin 32, Pin 26 - Pin 34, Pin 28 - Pin 36',#10,#10);
  Writeln('Press any key to continue!');
  Readln;

  iErrorCode := me1000DIOSetPortDirection(iBoardNumber, PORTA, MEOUTPUT);
  ChkErrCode ;
  iErrorCode := me1000DIOSetPortDirection(iBoardNumber, PORTB, MEINPUT);
  ChkErrCode ;


   begin
    {Set Bit_0, Bit_8, Bit 16 and Bit_24 to logic 1 on PortA}
    Writeln(' Set Bit_0, Bit_8, Bit 16 and Bit_24 to logic 1 on PortA');
    iErrorCode := me1000DOSetBit(iBoardNumber, PORTA, Bit_0, 1);
    ChkErrCode ;
    iErrorCode := me1000DOSetBit(iBoardNumber, PORTA, Bit_8, 1);
    ChkErrCode ;
    iErrorCode := me1000DOSetBit(iBoardNumber, PORTA, Bit_16, 1);
    ChkErrCode ;
    iErrorCode := me1000DOSetBit(iBoardNumber, PORTA, Bit_24, 1);
    ChkErrCode ;

    {Read Bit_0, Bit_8, Bit 16 and Bit_24 on PortB}
    Writeln('Read Bit_0, Bit_8, Bit 16 and Bit_24 on PortB');
    iErrorCode := me1000DIGetBit(iBoardNumber, PORTB, Bit_0,  iValue_0);
    ChkErrCode ;
    iErrorCode := me1000DIGetBit(iBoardNumber, PORTB, Bit_8,  iValue_8);
    ChkErrCode ;
    iErrorCode := me1000DIGetBit(iBoardNumber, PORTB, Bit_16, iValue_16);
    ChkErrCode ;
    iErrorCode := me1000DIGetBit(iBoardNumber, PORTB, Bit_24, iValue_24);
    ChkErrCode ;

    Writeln('Bit_0  = ',iValue_0);
    Writeln('Bit_8  = ',iValue_8);
    Writeln('Bit_16 = ',iValue_16);
    Writeln('Bit_24 = ',iValue_24,#10);


    {Set Bit_0, Bit_8, Bit 16 and Bit_24 to logic 0 on PortA}
    Writeln(' Set Bit_0, Bit_8, Bit 16 and Bit_24 to logic 0 on PortA');
    iErrorCode := me1000DOSetBit(iBoardNumber, PORTA, Bit_0, 0);
    ChkErrCode ;
    iErrorCode := me1000DOSetBit(iBoardNumber, PORTA, Bit_8, 0);
    ChkErrCode ;
    iErrorCode := me1000DOSetBit(iBoardNumber, PORTA, Bit_16, 0);
    ChkErrCode ;
    iErrorCode := me1000DOSetBit(iBoardNumber, PORTA, Bit_24, 0);
    ChkErrCode ;

    {Read Bit_0, Bit_8, Bit 16 and Bit_24 on PortB}
    Writeln('Read Bit_0, Bit_8, Bit 16 and Bit_24 on PortB');
    iErrorCode := me1000DIGetBit(iBoardNumber, PORTB, Bit_0,  iValue_0);
    ChkErrCode ;
    iErrorCode := me1000DIGetBit(iBoardNumber, PORTB, Bit_8,  iValue_8);
    ChkErrCode ;
    iErrorCode := me1000DIGetBit(iBoardNumber, PORTB, Bit_16, iValue_16);
    ChkErrCode ;
    iErrorCode := me1000DIGetBit(iBoardNumber, PORTB, Bit_24, iValue_24);
    ChkErrCode ;
    Writeln('Bit_0  = ',iValue_0);
    Writeln('Bit_8  = ',iValue_8);
    Writeln('Bit_16 = ',iValue_16);
    Writeln('Bit_24 = ',iValue_24,#10);
   end;



  Writeln('Press any key to end!');
  Readln;

end.
