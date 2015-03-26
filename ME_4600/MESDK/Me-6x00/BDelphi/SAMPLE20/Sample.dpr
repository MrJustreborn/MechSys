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
/*                  1.00    020307  ew      Sample for WaveGen under Delphi 6.0                             */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

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


  // AO WaveGenerator
  Writeln('Sample 02 - AO Wavegenerator');
  Writeln('-------------------------',#10);
  // Set Channel
  ichannel := 0;

  // Set Shape
  iShape := 1;
   {0 = AO_Rectangle
   1 = AO_Triangle
   2 = AO_Sinus
   3 = AO_Cosinus
   4 = AO_Pos_Ramp
   5 = AO_Neg_Ramp}

   dAmplitude := 5;
   dOffset := 0;
   dFreq := 2500;

   iErrorCode := me6x00AOWaveGen (iBoardnumber, iChannel, iShape, dAmplitude, dOffset, dFreq);
   ChkErrCode ;

   writeln ('WaveGen Output with ......');
   writeln ('BoardNumber    = ',iBoardnumber);
   writeln ('Channel        = ',ichannel);
   writeln ('Shape          = ', iShape);
   Writeln ('Amplitude      = ',dAmplitude:8:5);
   writeln ('Offset         = ',dOffset:8:5);
   writeln ('Frequency      = ',dFreq:8:2);
   writeln ;
   Writeln('Press any key to stop output!');

   Readln;

   iErrorCode := me6x00AOStop (iBoardnumber, iChannel);
   ChkErrCode ;
   
   Writeln('Press any key to continue!');

  Readln;

end.




