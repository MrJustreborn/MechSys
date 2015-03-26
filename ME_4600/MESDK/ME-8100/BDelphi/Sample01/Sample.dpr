{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 4.0                                                                              */
/*  Copyright:      1999 Meilhaus Electronic GmbH                                                           */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    991008  ab     create (adapted from VC Sample)                                  */
/*                                         for a detailed explanation see the VC samples                    */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  medefs  in '..\medefs.pas',
  me8100  in '..\me8100.pas',
  SysUtils;


var
  iDllVersion: Integer;
  sDllVersion: string;
  iBoardnumber:Integer;
  iBoardVersion:Integer;
  sBoardVersion:string;
  iErrorCode: Integer;
  sErrorText:errorstring;
  iDirection: Integer;
  iBitNumber: Integer;
  iPort: Integer;
  iValue: Integer;
  sValue: string;
  iCounter: Integer;
  iIrqNumber: Integer;



Procedure IRQFKT ;
Begin
     iCounter := iCounter + 1;
End;



begin
  // Get DLL Version
  iDllVersion := me8100GetDLLVersion;
  sDllVersion := IntToHex(iDllVersion, 10);
  Writeln('DLL version: ', sDllVersion);

  // Set the board number
  iBoardnumber := 0;

  // determine board version
  iErrorCode := me8100GetBoardVersion (iBoardnumber, iBoardVersion);

  // Basically after every function call an error check by the function
  if iErrorCode<>1 then
  begin
    me8100GetDrvErrMess(sErrorText, 255);
    Write('Error: ', sErrorText);
    Readln;
    exit;
  end;

  sBoardVersion := IntToHex(iBoardVersion, 10);
  Writeln('Board typ: ', sBoardVersion);


  iErrorCode := me8100DIOSetTristateOFF (iBoardNumber, REGISTER_SET_A);
  {Errorcheck!!!}

  iErrorCode := me8100SetSinkSourceMode (iBoardNumber, REGISTER_SET_A, SOURCE_MODE);
  {Errorcheck!!!}

  iErrorCode := me8100DOSetBit(iBoardNumber, REGISTER_SET_A, {iBitNo=} 0, {iBitValue=} 1);

  {
  !!!!!!!!!!!!!!!!!!!!  !!!!!!!!!!!!!!!!!!!!
  For further details see the VC samples
  !!!!!!!!!!!!!!!!!!!!  !!!!!!!!!!!!!!!!!!!!
  }

  Writeln('For further details see the VC samples!');

  Writeln('Press any key to continue!');
  Readln;

end.
