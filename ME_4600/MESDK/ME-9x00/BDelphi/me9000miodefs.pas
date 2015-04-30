unit me9000miodefs;

interface

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                             ME9000mio Interface                               |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                              General consts                                   |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}


// Maximum number of boards supported
const ME9000MIO_MAX_DEVICES = 32;

// Define for the return value from an API function that is executed
// successfully
const ME9000MIO_NO_ERROR = $00000000;

// Define for a pointer or callback-function parameter which is reserved or not
// used in a particular context
const ME9000MIO_POINTER_NOT_USED = nil;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        consts for Error Routines                              |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

const ME9000MIO_ERROR_DEFAULT_PROC_ENABLE	= $00010101;
const ME9000MIO_ERROR_DEFAULT_PROC_DISABLE	= $00010102;

// Typedef for general API error procedure - used in me4000SetErrorFunction
type TME9000MIO_P_ERROR_PROC =
  procedure (pcFunctionName: PChar; iErrorCode: Integer); stdcall;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        consts for DIO Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}

// Bit number for me9000mioDIOConfig - Parameter uiBitNumber
const ME9000MIO_DIO_LINE_0 = 0;
const ME9000MIO_DIO_LINE_1 = 1;
const ME9000MIO_DIO_LINE_2 = 2;
const ME9000MIO_DIO_LINE_3 = 3;
const ME9000MIO_DIO_LINE_4 = 4;
const ME9000MIO_DIO_LINE_5 = 5;
const ME9000MIO_DIO_LINE_6 = 6;
const ME9000MIO_DIO_LINE_7 = 7;

// Direction for me9000mioDIOConfig - Parameter iDirection
const ME9000MIO_DIO_OUTPUT = $00020101;
const ME9000MIO_DIO_INPUT = $00020102;

// Polarity for me9000mioDIOConfig - Parameter iInvert
const ME9000MIO_DIO_INV_DISABLE = $00020201;
const ME9000MIO_DIO_INV_ENABLE = $00020202;

// Interrupt status for me9000mioDIOConfig - Parameter iInterrupt
const ME9000MIO_DIO_INT_DISABLE = $00020301;
const ME9000MIO_DIO_INT_ENABLE = $00020302;

// Output status for me9000mioDIOOutput - Parameter iOutputMode
const ME9000MIO_DIO_OUTPUT_DISABLE = $00020401;
const ME9000MIO_DIO_OUTPUT_ENABLE = $00020402;


// Typedef for DIO callback routine in me9000mioDIOSetCallback - Parameter
// pDIOIrqProc
type TME9000MIO_P_DIO_PROC =
  procedure(pDIOIrqContext: Pointer); stdcall;

{-------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        consts for Counter Routines                            |
|                                                                               |
|-------------------------------------------------------------------------------|
+-------------------------------------------------------------------------------}


// Trigger modus for me9000mioCntConfig - Parameter iRetrigger
const ME9000MIO_CNT_RETRIGGER_DISABLE = $00030101;
const ME9000MIO_CNT_RETRIGGER_ENABLE = $00030102;

// MIO Pin 0 event status for me9000mioCntConfig - Parameter iCntEvent
const ME9000MIO_CNT_EVENT_DISABLE = $00030201;
const ME9000MIO_CNT_EVENT_ENABLE = $00030202;

// Clock source for me9000mioCntConfig - Parameter iClockSource
const ME9000MIO_CNT_CLOCK_INTERNAL = $00030301;
const ME9000MIO_CNT_CLOCK_EXTERNAL = $00030302;

// Interrupt status for me9000mioCntConfig - Parameter iInterrupt
const ME9000MIO_CNT_INT_DISABLE = $00030401;
const ME9000MIO_CNT_INT_ENABLE = $00030402;

// Typedef for Cnt callback routine in me9000mioCntConfig - Parameter 
// pCntIrqProc
type TME9000MIO_P_CNT_PROC =
  procedure(pCntIrqContext: Pointer); stdcall;

implementation

end.

