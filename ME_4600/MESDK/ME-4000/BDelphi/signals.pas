unit signals;

interface

const SIGNAL_RECTANGLE = $00;
const SIGNAL_TRIANGLE  = $01;
const SIGNAL_SINUS     = $02;
const SIGNAL_POS_RAMP  = $03;
const SIGNAL_NEG_RAMP  = $04;

Procedure
  Sweep(iSignalType: Integer; dFromFreq: Double; dToFreq: Double;
          dFromMin: Double; dToMin: Double; dFromMax: Double; dToMax: Double;
                                    dBaseFreq: Double; lwNoOfPoints: LongWord;
                        var arrsiBuffer: array of Smallint; iBufferIncrement: Integer);


implementation

uses

  Math;

Procedure
  Sweep(iSignalType: Integer; dFromFreq: Double; dToFreq: Double;
          dFromMin: Double; dToMin: Double; dFromMax: Double; dToMax: Double;
                                    dBaseFreq: Double; lwNoOfPoints: LongWord;
                        var arrsiBuffer: array of Smallint; iBufferIncrement: Integer);

var

  dTotalTime: Double;
  iIndex : Integer;
  dIndex : Double;
  dNoOfPoints: Double;
  dTime: Double;
  dArg: Double;
  dMin: Double;
  dMax: Double;
  dSignal: Double;

begin

  dSignal := 0.0;

  dNoOfPoints := lwNoOfPoints;

  dTotalTime := dNoOfPoints / dBaseFreq;
	
  for iIndex := 0 to lwNoOfPoints - 1 do

  begin

    dIndex := iIndex;

    dTime := dIndex / dBaseFreq;

    dArg :=  (0.5 * dTime * dTime * (dToFreq - dFromFreq) + dTime * dFromFreq * dTotalTime) / dTotalTime;

    dArg := dArg - Floor(dArg);

    dMin := dFromMin + dIndex * (dToMin - dFromMin) / dNoOfPoints;

    dMax := dFromMax + dIndex * (dToMax - dFromMax) / dNoOfPoints;

    if (iSignalType = SIGNAL_RECTANGLE) then

    begin

        if (dArg < 0.5) then dSignal := +1.0
        else dSignal := 0.0;

    end

    else if (iSignalType = SIGNAL_TRIANGLE) then

    begin

        if (dArg < 0.5) then dSignal := 2 * dArg
        else dSignal := +1.0 - 2 * (dArg - 0.5);

    end

    else if (iSignalType = SIGNAL_SINUS) then

    begin

        dSignal := 0.5 + 0.5 * sin( (dArg - 0.5) * 2 * 3.14153 );

    end

    else if (iSignalType = SIGNAL_POS_RAMP) then

    begin

        dSignal := dArg;

    end

    else if (iSignalType = SIGNAL_NEG_RAMP) then

    begin

        dSignal := 1 - dArg;

    end;

    dSignal := dMin + dSignal * (dMax - dMin);

    arrsiBuffer[iIndex * iBufferIncrement] := floor( dSignal * 32767.0 / 10.0 );

  end;

end;

end.



