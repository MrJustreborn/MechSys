/*      ME8100 demo program for interrupt on        */
/*      pattern match testing.  This program        */
/*      configures the ME8100 board to generate     */
/*      an interrupt when a predefined pattern      */
/*      appears on the digital input lines. The     */
/*      interrupt is serviced by a user defined     */
/*      interrupt service routine.                  */
/*                                                  */
/*      Program for use with Borland C++            */
/*      and Visual C++ programs                     */
/*                                                  */
/*      This Program uses dynamic function calls    */
/*      and Wrappers for all the ME8100 functions   */


/*
dynamic vs. static binding of a DLL:
------------------------------------

static binding:
    - you have to include the me8100.lib file
      in the project workspace
    - then you can use every function in the DDL
      like a locally existing function
      (with the appropriate prototypes)
    - in some cases there are problems with
      different compiler versions !!!

dynamic binding:
    - you have to open a DLL with
      "LoadLibrary"
    - you have to get a function pointer with
      "GetProcAddress"
    - then you can use every DLL exported
      function with its function pointer

In this sample we have done most of the steps
for you:
If you would like to use static binding:
    - include the lib file
    - use the include file me8100.h
    - use the compiler MS Visual C 6.00
If you would like to use dynamic binding:
      (All the following steps are done in 
      this exsample:)
    - use the include file me8100Init.h
    - use the function me8100Open at the
      start of the program
    - use the function me8100Close at the
      end of the program
    - include the source code file 
      "me8100Init.cpp" in the project.  This 
      file contains the "me8100Open" and 
      "me8100Close" functions which must be 
      called from the main program.  The 
      "me8100Open" function opens the library 
      and gets the address of all the DLL 
      functions.  The "me8100Close" function 
      simply closes the library at the end of
      the program.
    - The source code file "me8100Init" also 
      has all of the "Wrapper" functions.  This 
      allows the user to use the full and proper
      function names when calling them from the 
      main program.
*/


/* Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEUNIT("..\DLLInit.cpp");
#endif

/* These are system header files  */
#include <stdio.h>
#include <windows.h>
#include <conio.h>

/* These are the me8100 header files    */
//#include ".\..\me8100.h"
#include ".\..\DLLInit.h"

/* Prototypes   */
void ErrorHandler (int iErrorCode);       // defines the error handler routine
void _stdcall IrqFunc (int iContext);   //user defined interrupt service routine

/*  Define Global Variables   */
int iBoardNumber;           // declare the BoardNumber variable
int iErrorCode;             // declare the data type for the returned error code



/* ------------------------  Main Program ------------------------------- */
void main(void)
{
    iBoardNumber ;      // select board 
    DWORD dwDLLVersion;     // declare data type for DLLVersion function  
    int iBoardVersion ; 
    int iPROMVersion ;

    meOpen ();  // calls the initialize function



/* -------------------------------------------------------------------------
        This section of code checks the current board 
        information and displays it on the screen
--------------------------------------------------------------------------- */

    dwDLLVersion = me8100GetDLLVersion ();         // function call (no parameters)

    iErrorCode = me8100GetBoardVersion (iBoardNumber, &iBoardVersion); 
    ErrorHandler (iErrorCode);                      // check if an error occurred

    iErrorCode = me8100PROMVersion(iBoardNumber, &iPROMVersion);
    ErrorHandler (iErrorCode);


    /*  Print an Introductory Message  */
    printf ("Current Board Information\n");
    printf ("-------------------------\n");

    /*  Print out the Board Information   */
    printf ("Active board #: %01d \n", iBoardNumber);   // active board number
    printf ("Version of DLL: %08x\n", dwDLLVersion);    // print DLL version
    printf ("Board Version: %04x\n", iBoardVersion);    // print Board version
    printf ("PROM Version: %04x \n", iPROMVersion);     // Print PROM Version
    printf ("\n");                                      // blank line

    printf (" ***** Press Return to continue *****\n\n");
    getchar ();

/* ---------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------- */


/*  this section of code will set up the ME8100 with a 
    bit pattern and when the bit pattern appears on the 
    input lines, an interrupt will occur and the interrupt
    service routine "IrqFunc" will be executed. For test
    purposes, the inputs were connected to the outputs.
    When the pattern is set using "me8100DOSetWord", this 
    pattern also appears on the inputs causing an interrupt.  */

    /* variables for function calls */
    int iContext;
    int iPattern;
    int iCnt;   

/*  the following define statements can be found in the header file
    "me8100defs.h".  They are shown again here for clarity

          // Register sets
        #define REGISTER_SET_A  0
        #define REGISTER_SET_B  1

        // Source/Sink Mode
        #define SINK_MODE       0
        #define SOURCE_MODE     1

        // Interrupt modes
        #define INTERRUPT_ON_PATTERN_COMPARE    0
        #define INTERRUPT_ON_BIT_CHANGE         1       */

    iBoardNumber = 0;

    iPattern = 65535; // this is 0xFFFF or binary 1111 1111 1111 1111
                   // when this pattern appears, an interrupt occurs

    iContext = 0;  // iContext is useful only when more than one board
                   // uses the same interrupt service routine. When not
                   // used, set iContext to zero

    // get the initial interrupt count and print
    iErrorCode = me8100GetIrqCnt (iBoardNumber, REGISTER_SET_A, &iCnt);
    ErrorHandler (iErrorCode);
    printf ("Interrupt Count at start: %03d \n", iCnt);

    iErrorCode = me8100DIOSetPattern(iBoardNumber, REGISTER_SET_A, iPattern);
    ErrorHandler (iErrorCode);

    iErrorCode = me8100DIOSetTristateOFF (iBoardNumber, REGISTER_SET_A);
    ErrorHandler (iErrorCode);

    iErrorCode = me8100SetSinkSourceMode (iBoardNumber, REGISTER_SET_A, SOURCE_MODE);
    ErrorHandler (iErrorCode);

    iErrorCode = me8100DIOSetIntMode(iBoardNumber, REGISTER_SET_A,
                                                INTERRUPT_ON_PATTERN_COMPARE);

    iErrorCode = me8100EnableInt (iBoardNumber, REGISTER_SET_A, IrqFunc, iContext);
    ErrorHandler (iErrorCode);

    // write a word to set the inputs to the desired pattern to cause an interrupt
    iErrorCode = me8100DOSetWord(iBoardNumber, REGISTER_SET_A, iPattern);
    ErrorHandler (iErrorCode);

    Sleep (10); // delay to allow the interrupt to be processed by the system

    iErrorCode = me8100DisableInt (iBoardNumber, REGISTER_SET_A);
    ErrorHandler (iErrorCode);

        printf("Press any key to continue... \n");
        getch();

    meClose ();
}

/* ------------------------------------------------------------------------ */

/*  This is the error Handler Routine   */
/*  If a DLL function call returns a    */
/*  "1", an error occurs and this       */
/*  Routine is executed.                */

void ErrorHandler (int iErrorCode)
{
    if (iErrorCode != 1)
    {
        printf("*** Error Ocurred ***\n");
    }
}

/*  ------------------------------------------------------------ */

/*  This is the interrupt service routine that will be executed
    every time an interrupt occurs
                                    */
void _stdcall IrqFunc (int i_context)
{
    int iCnt;

    iErrorCode = me8100GetIrqCnt (iBoardNumber, REGISTER_SET_A, &iCnt);
    ErrorHandler (iErrorCode);

    printf("\n\n******************   INTERRUPT!   *****************\n\n");
    printf ("Interrupt counter: %03d \n", iCnt);
}

// -----------------------------------------------------------------
