{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin Wisura)                                                                       */
/*                                                                                                          */
/*  Description:    WrapAround One channel                                                                  */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    020307  ew      Sample for WrapAround One Channel                               */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  me6x00 in '..\me6x00.pas',
  medefs in '..\medefs.pas',
  SysUtils;

var

  iBoardnumber:Integer;
  iChannel: Integer;
  dFreq : double;
  iTicks: Integer;
  iErrorCode: Integer;
  iModePolarity: Integer;
  iSize : integer;
  imaxWert: Integer;
  psBuffer: TMEAOBuffer;
  i: integer;
  n: integer;
  Maximum: Integer;
  sErrortext: errorstring;

  
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
  dFreq          := 300000;
  iModePolarity  := $0;
                    {AO6000_Trigger-Timer    = $0
                     AO6000_Trigger_Ext_Low ´= $10
                     AO6000_Trigger_Ext_High = $30}
   iSize         := 8192;
   imaxWert      := 65535;
   Maximum       := 0;
   //iBuffer       := 8192;
   n             := 0;

  Writeln('Sample 04 - Wrap Around Mode');
  Writeln('---------------------------',#10);
  Writeln('Board                = ', iBoardnumber);
  Writeln('Channel              = ', ichannel);
  Writeln('Frequency            = ',dfreq:7:2);
  Writeln('Polarity             = Timer');
  Writeln('---------------------------',#10);

  iTicks := me6x00FrequencyToTimer(dFreq);


  {Übergabe der Ticks 110) an die Funktion me6x00AOSetTimer
   zur Konfiguration des Timers}
  //iErrorCode := me6x00AOSetTimer (iBoardnumber, iChannel, iTicks);
  iErrorCode := me6x00AOSetTimer (iBoardnumber, iChannel, iTicks);

  {output will be started from software}

  iErrorCode := me6x00AOSetTrigger (iBoardnumber, iChannel, iModePolarity);

  psBuffer[n] :=  psBuffer[n] +1;
  If  psBuffer[n] > Maximum  then Maximum := psBuffer[n];


  writeln('generating waveform');
  for i  := 1 to iSize do
  begin
        n := round ((sin(i*0.2)+1)*(iMaxwert/2))+1;
        psBuffer[i] := n;
        {write (n,' ');}
  end;


  writeln ('AOWrapAround');
  iErrorCode := me6x00AOWrapAround (iBoardnumber, iChannel, iSize, psBuffer);
   if iErrorCode<>1 then
    begin
      me6x00GetDrvErrMess(sErrorText, 255);
      Write('Error: ', sErrorText);
      Readln;
      exit;
    end;
  writeln ('AOStart...');
  iErrorCode := me6x00AOStart (iBoardnumber, iChannel);
   if iErrorCode<>1 then
    begin
      me6x00GetDrvErrMess(sErrorText, 255);
      Write('Error: ', sErrorText);
      Readln;
      exit;
    end;
   writeln('press return to stop output');
   readln;

     

   iErrorCode := me6x00AOStop (iBoardnumber, iChannel);

  Writeln('Press any key to end!');

  Readln;
  
end.
