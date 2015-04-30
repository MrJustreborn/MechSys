{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    Sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin wisura)                                                                       */
/*                                                                                                          */
/*  Description:    set Byte and read Byte                                                                  */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    020319  ew     set Byte and read Byte                                           */
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
  iCounter     : Integer;
  ibyte        : Integer;
    

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
  Writeln('Sample 20, Set Byte and read Byte!');
  Writeln('--------------------------------',#10,#10);
  iBoardNumber := 0;
  iErrorCode := me1000DIOReset(iBoardNumber);
  // Basically after every function call an error check by the function
  ChkErrCode ;

  Writeln('Please connect following pin together:');
  Writeln('Pin 22 - Pin 30, Pin 61 - Pin 69, Pin  3 - Pin 11, Pin 42 - Pin 50',#10);
  Writeln('Pin 23 - Pin 31, Pin 62 - Pin 70, Pin  4 - Pin 12, Pin 43 - Pin 51',#10,#10);
  Writeln('Press any key to continue!');

  Readln;

  iErrorCode := me1000DIOSetPortDirection(iBoardNumber, PORTA, MEOUTPUT);
  ChkErrCode ;
  iErrorCode := me1000DIOSetPortDirection(iBoardNumber, PORTB, MEINPUT);
  ChkErrCode ;

   begin
    {Set Byte_0 PortA to a value}
    for ibyte:= 0 to 255 do
      begin
      iErrorCode := me1000DOSetByte(iBoardNumber, PORTA, Byte_0, ibyte);
      ChkErrCode ;
      {Read Byte_0 on PortB}
      iErrorCode := me1000DIGetByte(iBoardNumber, PORTB, Byte_0,  iValue_0);
      ChkErrCode ;
      Writeln('Set Byte_0 PortA to ', ibyte,' Read Byte_0  = ',iValue_0);
      end;
    {Set Byte_0 PortA to 0}
    Writeln(#10,'Set Byte_0 PortA to 0');
    ibyte := 0;
    iErrorCode := me1000DOSetByte(iBoardNumber, PORTA, Byte_0, ibyte);
    ChkErrCode ;

    {Read Byte_0 on PortB}
    Writeln('Read Byte_0 on PortB');
    iErrorCode := me1000DIGetByte(iBoardNumber, PORTB, Byte_0,  iValue_0);
    ChkErrCode ;

    Writeln('Byte_0  = ',iValue_0);


   end;
  Writeln('Press any key to end!');
  Readln;

end.
