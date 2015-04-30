{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2001 Meilhaus Electronic GmbH                                                           */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    011024  ab     create (adapted from VC Sample)                                  */
/*                                         for a detailed explanation see the VC samples                    */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  medefs in '..\medefs.pas',
  me9x in '..\me9x.pas',
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

Procedure ChkErrCode ;
Begin
  if iErrorCode<>1 then
  begin
    me9xGetDrvErrMess(sErrorText);
    Write('Error: ', sErrorText);
    Readln;
    exit;
  end;
End;


begin
  // Get DLL Version
  iDllVersion := me9xGetDLLVersion;
  sDllVersion := IntToHex(iDllVersion, 10);
  Writeln('DLL version: ', sDllVersion);

  // Set the board number
  iBoardnumber := 0;

  // determine board version
  iErrorCode := me9xGetBoardVersion (iBoardnumber, iBoardVersion);
  ChkErrCode;   // Basically after every function call an error check by the function
  sBoardVersion := IntToHex(iBoardVersion, 10);
  Writeln('Board typ: ', sBoardVersion);





  // Digital output:

  iValue := 0;
  iBitNumber := 1;


  iErrorCode := me95DOSetBit (iBoardnumber,  iBitNumber, iValue );
  ChkErrCode;

  iErrorCode := me95DOSetByte (iBoardnumber, iPort, iValue);
  ChkErrCode;


  Writeln('Press any key to continue!');
  Readln;

end.
