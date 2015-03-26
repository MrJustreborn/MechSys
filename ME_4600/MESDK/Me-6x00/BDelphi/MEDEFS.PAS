{ File Name 'medefs.pas'  }
{ Defines for MEILHAUS 32-bit board drivers }


unit medefs;

interface


{maximum number of boards}
const ME_MAX_DEVICES    = 32;

{ ME6x00_TRIGGER_MODE }
const    AO6x00_TRIGGER_TIMER    = $00;
const    AO6x00_TRIGGER_EXT_HIGH = $10;
const    AO6x00_TRIGGER_EXT_LOW  = $30;


{ ME6x00_SIGNAL_SHAPE }
const    AO_RECTANGLE   = $00;
const    AO_TRIANGLE    = $01;
const    AO_SINUS       = $02;
const    AO_COSINUS     = $03;
const    AO_POS_RAMP    = $04;
const    AO_NEG_RAMP    = $05;


implementation

end.
