/*------------------------------------------------------------------------------+
|   Source File:    me9000miodefs.h                                             |
|   Destination:    me9000mio - SYS and WDMdrivers, API-DLL and other           |
|                   applications                                                |
|   Compiler:       Visual C++ 6.0                                              |
|   Authors:        KRH (Keith Hartley),                                        |
|   Copyright       (c) 1997-2004  Meilhaus Electronic GmbH                     |
|                                                                               |
|   Description:    Common header file providing #defines to be used in DLL or  |
|                   applications which are connected to the 32-Bit driver       |
|                   running on Windows                                          |
|                                                                               |
|  File History:    Version     Date        Editor  Action                      |
+-------------------------------------------------------------------------------+
|                   1.00.00     041123      KRH     Original version            |
|                                                                               |
+-------------------------------------------------------------------------------+
|                                                                               |
|   Description:                                                                |
|                                                                               |
|       A number of defines and structures which are used both in user mode     |
|       and in kernel mode for all operating systems and are also required by   |
|       the user calling functions in the DLL interface.                        |
|                                                                               |
+------------------------------------------------------------------------------*/


#ifndef DEFS_H
#define DEFS_H

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                             ME9000mio Interface                               |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                              General #defines                                 |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Maximum number of boards supported
#define ME9000MIO_MAX_DEVICES                       32

// Define for the return value from an API function that is executed 
// successfully
#define ME9000MIO_NO_ERROR                          0x00000000

// Define for a pointer or callback-function parameter which is not used in a 
// particular context
#define ME9000MIO_POINTER_NOT_USED					NULL

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        #defines for Error Routines                            |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

#define ME9000MIO_ERROR_DEFAULT_PROC_ENABLE         0x00010101
#define ME9000MIO_ERROR_DEFAULT_PROC_DISABLE        0x00010102

// Typedef for general API error procedure - used in me4000SetErrorFunction 
typedef void (_stdcall * ME9000MIO_P_ERROR_PROC)(char* pcFunctionName,
                                                               int iErrorCode);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                        #defines for DIO Routines                            |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Bit number for me9000mioDIOConfig - Parameter uiBitNumber
#define ME9000MIO_DIO_LINE_0						0
#define ME9000MIO_DIO_LINE_1						1
#define ME9000MIO_DIO_LINE_2						2
#define ME9000MIO_DIO_LINE_3						3
#define ME9000MIO_DIO_LINE_4						4
#define ME9000MIO_DIO_LINE_5						5
#define ME9000MIO_DIO_LINE_6						6
#define ME9000MIO_DIO_LINE_7						7

// Direction for me9000mioDIOConfig - Parameter iDirection
#define ME9000MIO_DIO_OUTPUT						0x00020101
#define ME9000MIO_DIO_INPUT							0x00020102

// Polarity for me9000mioDIOConfig - Parameter iInvert
#define ME9000MIO_DIO_INV_DISABLE					0x00020201
#define ME9000MIO_DIO_INV_ENABLE					0x00020202

// Interrupt status for me9000mioDIOConfig - Parameter iInterrupt
#define ME9000MIO_DIO_INT_DISABLE					0x00020301
#define ME9000MIO_DIO_INT_ENABLE					0x00020302

// Output status for me9000mioDIOOutput - Parameter iOutputMode
#define ME9000MIO_DIO_OUTPUT_DISABLE				0x00020401
#define ME9000MIO_DIO_OUTPUT_ENABLE					0x00020402

// Typedef for DIO callback routine in me9000mioDIOSetCallback - Parameter 
// pDIOIrqProc
typedef void (_stdcall * ME9000MIO_P_DIO_PROC)(void* pDIOIrqContext);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                      #defines for Counter Routines                            |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

// Trigger modus for me9000mioCntConfig - Parameter iRetrigger
#define ME9000MIO_CNT_RETRIGGER_DISABLE				0x00030101
#define ME9000MIO_CNT_RETRIGGER_ENABLE				0x00030102

// MIO Pin 0 event status for me9000mioCntConfig - Parameter iCntEvent
#define ME9000MIO_CNT_EVENT_DISABLE					0x00030201
#define ME9000MIO_CNT_EVENT_ENABLE					0x00030202

// Clock source for me9000mioCntConfig - Parameter iClockSource
#define ME9000MIO_CNT_CLOCK_INTERNAL				0x00030301
#define ME9000MIO_CNT_CLOCK_EXTERNAL				0x00030302

// Interrupt status for me9000mioCntConfig - Parameter iInterrupt
#define ME9000MIO_CNT_INT_DISABLE					0x00030401
#define ME9000MIO_CNT_INT_ENABLE					0x00030402

// Typedef for Cnt callback routine in me9000mioCntConfig - Parameter 
// pCntIrqProc
typedef void (_stdcall * ME9000MIO_P_CNT_PROC)(void* pDIOIrqContext);

#endif