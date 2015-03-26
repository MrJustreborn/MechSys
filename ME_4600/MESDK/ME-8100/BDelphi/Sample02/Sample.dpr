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
  sPROMVersion :string;
  iPROMVersion :Integer;
  //iDirection: Integer;
  //iBitNumber: Integer;
  //iPort: Integer;
  //iValue: Integer;
  //sValue: string;
  iIrqCnt: Integer;
  //iIrqNumber: Integer;
  DevInfo: DEVICEINFOSTRUCT;


// Basically after every function call an error check by the function
function ChkErr(ErrorCode: Integer): Boolean;
var sErrorText:ErrorString;
Begin;
  if ErrorCode<>1 then
  begin
    me8100GetDrvErrMess(sErrorText, 255);
    Writeln('Error: ', sErrorText);
    Write('Press any key to exit!');
    Readln;
    Result:=False;
    halt;
  end
  else
    Result:=True;
end;


//procedure IrqCallBack(Context: Integer); Cdecl;       // so gehts nicht !!!
procedure IrqCallBack(Context: Integer); stdcall;
var
   InWord :Integer;
   iIrqCntAbs : Integer;
Begin
   iIrqCnt := iIrqCnt + 1;
   ChkErr(me8100DIGetIntStatus(iBoardNumber, REGISTER_SET_A, InWord));
   ChkErr(me8100GetIrqCnt(iBoardNumber, REGISTER_SET_A, iIrqCntAbs));
   Write(' >', iIrqCnt);
end;


begin

  // Set the board number
  iBoardnumber := 0;

  // Reset interrupt counter
  iIrqCnt := 0;

  // Get DLL Version
  iDllVersion := me8100GetDLLVersion;
  sDllVersion := IntToHex(iDllVersion, 8);
  Writeln('DLL version: ', sDllVersion);

  // determine board version
  ChkErr(me8100GetBoardVersion (iBoardNumber, iBoardVersion));
  sBoardVersion := IntToHex(iBoardVersion, 4);
  Writeln('Board typ:   ', sBoardVersion);

  // determine PROM version
  ChkErr(me8100PROMVersion(iBoardNumber, iPROMVersion));
  sPROMVersion := IntToHex(iPROMVersion, 4);
  Writeln('PROM:        ', sPROMVersion);

  //ChkErr(me8100GetDevInfo( iBoardNumber, DevInfo));

  ChkErr(me8100DIOSetIntMode(    iBoardNumber, REGISTER_SET_A, INTERRUPT_ON_BIT_CHANGE));
  ChkErr(me8100EnableInt(        iBoardNumber, REGISTER_SET_A, Addr(IrqCallBack), 0));
  // ChkErr(me8100EnableInt(        iBoardNumber, REGISTER_SET_A, @IrqCallBack, 0));
  ChkErr(me8100DIOSetTristateOFF(iBoardNumber, REGISTER_SET_A));
  ChkErr(me8100SetSinkSourceMode(iBoardNumber, REGISTER_SET_A, SOURCE_MODE));

  ChkErr(me8100DIOSetMask(       iBoardNumber, REGISTER_SET_A, $01));
  Readln;
  ChkErr(me8100DOSetWord(        iBoardNumber, REGISTER_SET_A, $00));
  Readln;
  ChkErr(me8100DOSetWord(        iBoardNumber, REGISTER_SET_A, $01));
  Readln;

  Writeln('For further details see the VC samples!');
  Writeln('Press any key to continue!');
  Readln;

  ChkErr(me8100DisableInt(       iBoardNumber, REGISTER_SET_A));
end.
