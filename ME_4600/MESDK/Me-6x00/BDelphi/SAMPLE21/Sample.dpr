{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin Wisura)                                                                       */
/*                                                                                                          */
/*  Description:    WaveGenerator                                                                           */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    020307  ew      Sample for WaveGen under Delphi 6.0 with input parameters       */
/*----------------------------------------------------------------------------------------------------------*}

program
  sample;

uses
  me6x00 in '..\me6x00.pas',
  medefs in '..\medefs.pas',
  SysUtils;

var
  iDllVersion  : Integer;
  sDllVersion  : string;
  iBoardnumber : Integer;
  iVersion     : Integer;
  iErrorCode   : Integer;
  iSerial      : Integer;
  ishape       : Integer;
  sVersion     : string;
  sErrortext   : errorstring;
  sSerial      : string;
  ichannel     : integer;
  dAmplitude   : double;
  dOffset      : double;
  dFreq        : double;


Procedure ChkErrCode ;
Begin
  if iErrorCode<>1 then
  begin
    me6x00GetDrvErrMess(sErrorText,255);
    Write('Error: ', sErrorText);
    Readln;
    exit;
  end;
End;


begin

  {Function me6x00GetDllVersion: integer; cdecl; }
  Writeln('Sample 01 - Board Parameter');
  Writeln('---------------------------',#10);
  // Get DLL Version
  iDllVersion := me6x00GetDllVersion;
  sDllVersion := IntToHex(iDllVersion, 10);
  Writeln('DLL version   : ', sDllVersion);

  // Set the board number
  iBoardnumber := 0;

  // Get Board Typ
  iErrorCode := me6x00GetBoardVersion (iBoardnumber, iVersion);
  // Basically after every function call an error check by the function
  // me6x00ErrorMessage should be done
 ChkErrCode ;
  sVersion := IntToHex (iVersion, 10);
  Writeln('BoardVersion  : ', sVersion);

  // Get Driver SerialNumber
 iErrorCode :=me6x00GetSerialNumber (iBoardnumber, iSerial);
 ChkErrCode ;
  sSerial := IntToHex(iSerial, 8);
  Writeln('SeriaNumber   : ', sSerial,#10,#10);


  // Input for WaveGen
  // AO WaveGenerator
  Writeln('Sample 02 - AO Wavegenerator');
  Writeln('-------------------------',#10);

  Writeln ('Please input parameter for WaveGenerator:');
  Write ('BoardNumber: ');
  read (iBoardNumber);
  Write ('Channel    : ');
  read (iChannel);
  Write ('Shape      : ');
  read (iShape);
  {0 = AO_Rectangle
   1 = AO_Triangle
   2 = AO_Sinus
   3 = AO_Cosinus
   4 = AO_Pos_Ramp
   5 = AO_Neg_Ramp}
  Write ('Amplitude  : ');
  read (dAmplitude);
  Write ('Offset     : ');
  read (dOffset);
  Write ('Frequency  : ');
  read (dFreq);
  {max. frequency = 100Khz; 250KHz for Rectangle}
   iErrorCode := me6x00AOWaveGen (iBoardnumber, iChannel, iShape, dAmplitude, dOffset, dFreq);
   ChkErrCode ;
  writeln ('WaveGen Output with ......');

  Readln;


   Writeln('Press any key to stop output!');
   Readln;

   iErrorCode := me6x00AOStop (iBoardnumber, iChannel);
   ChkErrCode ;


   Writeln('Press any key end!');

  Readln;

end.




