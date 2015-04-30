{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin Wisura)                                                                       */
/*                                                                                                          */
/*  Description:    AOContinuous                                                                            */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    020307  ew      Sample for AOContinuous                                         */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  me6x00 in '..\me6x00.pas',
  medefs in '..\medefs.pas',
  SysUtils;

var

  iBoardnumber  : Integer;
  iChannel      : Integer;
  dFreq         : double;
  iTicks        : Integer;
  iErrorCode    : Integer;
  iModePolarity : Integer;
  iSize         : integer;
  imaxWert      : Integer;
  psBuffer      : TMEAOBuffer;
  i             : integer;
  n             : integer;
  sErrortext    : errorstring;
  z             : integer;
  Maximum       : integer;
  iBuffer       : integer;


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

  iBoardnumber   := 0;
  iChannel       := 0;
  dFreq          := 3000;
  iModePolarity  := $0;
                    {AO6000_Trigger-Timer    = $0
                     AO6000_Trigger_Ext_Low ´= $10
                     AO6000_Trigger_Ext_High = $30}
   iSize         := 32768;
   imaxWert      := 65535;
   Maximum       := 0;
   iBuffer       := 32768;
   n             := 0;
   z             := 100;
  Writeln('Sample 03 - Continuous Mode');
  Writeln('---------------------------',#10);
  Writeln('Board                = ', iBoardnumber);
  Writeln('Channel              = ', ichannel);
  Writeln('Frequency            = ',dfreq:7:2);
  Writeln('Polarity             = Timer');
  Writeln('---------------------------',#10);

  iTicks := me6x00FrequencyToTimer(dFreq);




  iErrorCode := me6x00AOSetTimer (iBoardnumber, iChannel, iTicks);
  ChkErrCode ;

  {output will be started from software}

  iErrorCode := me6x00AOSetTrigger (iBoardnumber, iChannel, iModePolarity);
  ChkErrCode ;
  psBuffer[n] :=  psBuffer[n] +1;
  If  psBuffer[n] > Maximum  then Maximum := psBuffer[n];

  {Randomize;}
  for i  := 1 to iSize do
  begin
        n := Random (imaxWert);
        psBuffer[i] := n;
        {writeln (n); }
  end;


  writeln ('AOContinuous (preload) ...');
  iErrorCode := me6x00AOContinuous (iBoardnumber, iChannel, iSize, psBuffer);
  ChkErrCode ;
  writeln ('AOStart...');
  iErrorCode := me6x00AOStart (iBoardnumber, iChannel);
  ChkErrCode ;

  writeln ('AOContionuous (reload)...');
  Writeln('---------------------------',#10);

  while z <> 0 do begin
        iErrorCode := me6x00AOContinuous (iBoardnumber, iChannel, iSize, psBuffer);
        ChkErrCode ;
        z := z-1;
        write ('.');
  end;
   iErrorCode := me6x00AOStop (iBoardnumber, iChannel);
   ChkErrCode ;

  Writeln('Press any key to end!');

  Readln;
  iErrorCode := me6x00AOStop (iBoardnumber, iChannel);
  ChkErrCode ;

  Readln;
  Writeln('end!');
end.




