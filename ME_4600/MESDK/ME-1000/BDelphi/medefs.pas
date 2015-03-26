{ File Name 'medefs.pas'  }
{ Defines for MEILHAUS 32-bit ME-1000 Drivers }


unit medefs;

interface


{Maximum number of ME1000 Boards}
const ME_MAX_DEVICES	= 32;

{ME1000 Device IDs}
const ME1000A_PCI_DEV_ID	= $100A;
const ME1000B_PCI_DEV_ID	= $100B;


{port direction}
const MEINPUT	= 0;
const MEOUTPUT	= 1;

{port identifier}
const PORTA	    = 0;
const PORTB	    = 1;
const PORTC	    = 2;
const PORTD	    = 3;

{word identifier}
const WORD_0	= 0;
const WORD_1	= 1;


{byte identifier}
const BYTE_0  = 0;
const BYTE_1  = 1;
const BYTE_2  = 2;
const BYTE_3  = 3;

// bit identifier
const BIT_0   = 0;
const BIT_1   = 1;
const BIT_2   = 2;
const BIT_3   = 3;
const BIT_4   = 4;
const BIT_5   = 5;
const BIT_6   = 6;
const BIT_7   = 7;
const BIT_8   = 8;
const BIT_9   = 9;
const BIT_10  = 10;
const BIT_11  = 11;
const BIT_12  = 12;
const BIT_13  = 13;
const BIT_14  = 14;
const BIT_15  = 15;
const BIT_16  = 16;
const BIT_17  = 17;
const BIT_18  = 18;
const BIT_19  = 19;
const BIT_20  = 20;
const BIT_21  = 21;
const BIT_22  = 22;
const BIT_23  = 23;
const BIT_24  = 24;
const BIT_25  = 25;
const BIT_26  = 26;
const BIT_27  = 27;
const BIT_28  = 28;
const BIT_29  = 29;
const BIT_30  = 30;
const BIT_31  = 31;

	
implementation

end.
