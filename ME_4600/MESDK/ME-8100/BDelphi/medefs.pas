{ File Name 'medefs.pas'  }
{ Defines for MEILHAUS 32-bit board drivers }


unit medefs;

interface


{Maximum number of ME8100 Boards}
const ME8100_MAX_DEVICES	= 32;

{ME8100 Device IDs}
const ME8100A_PCI_DEV_ID	= $810A;
const ME8100B_PCI_DEV_ID	= $810B;

{Register sets}
const REGISTER_SET_A	= 0;
const REGISTER_SET_B	= 1;

{Source/Sink Mode}
const SINK_MODE		= 0;
const SOURCE_MODE	= 1;

{Interrupt modes}
const INTERRUPT_ON_PATTERN_COMPARE	= 0;
const INTERRUPT_ON_BIT_CHANGE		= 1;
	
implementation

end.
