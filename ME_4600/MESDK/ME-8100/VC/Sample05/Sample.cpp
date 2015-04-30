/*      ME8100 demo program for timer use.			*/
/*      this program is for use with Borland C++    */
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
USEUNIT("..\me8100Init.cpp");
#endif

/* These are system header files  */
#include <stdio.h>
#include <windows.h>
#include <conio.h>

/* These are the me8100 header files    */
#include ".\..\DLLInit.h"

/* Prototypes   */
void ErrorHandler (int iErrorCode);       // defines the error handler routine

/*  Define Global Variables   */
int iBoardNumber;           // declare the BoardNumber variable
int iErrorCode;             // declare the data type for the returned error code



/* ------------------------  Main Program ------------------------------- */
void main(void)
{
    iBoardNumber = 0;      // select board 
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

/*  This section demonstrates how the counters can be used.
	The program initializes a counter in Mode2 (Asymmetric divider)
	and divides an input signal by the value loaded.  

	The following hardware connections must be made:
	1.  input signal (to be divided) on pin 37 (CLK 0)
	2.  gate set to enabled: 0 Volts on pin 38 (Gate 0)
	3.  Board must be in a powered up state

	For test purposes, a 1KHz input signal was used to allow 
	the counter value to be read out by the program

	The counter will start immediately after calling the 
	function "me8100CntWrite"
*/
	int iCounterNo;
	int iMode;
	int iValue;
	int iCountReadValue;
	
	// initialize the parameter variables
	iBoardNumber = 0;
	iCounterNo = 0;
	iMode = 2;
	iValue = 1000;
	iCountReadValue = 0;

	iErrorCode = me8100CntWrite(iBoardNumber, iCounterNo, iMode, iValue);
    ErrorHandler (iErrorCode);

	// read out the counter value 100 times
	int i;
	for (i=0; i<100;i++)
	{
		iErrorCode = me8100CntRead(iBoardNumber, iCounterNo, &iCountReadValue);
		ErrorHandler (iErrorCode);
		printf ("\nValue for Counter 0: %04x \n", iCountReadValue);
		Sleep (5);
	}

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
