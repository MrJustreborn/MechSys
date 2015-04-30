/*      ME 8100 Digital Input/Output demo           */
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
void ErrorHandler (int iErrorCode);             // defines the error handler routine


/*  Define Global Variables   */
int iBoardNumber;           // declare the BoardNumber variable
int iErrorCode;             // declare the data type for the returned error code



/* ------------------------  Main Program ------------------------------- */
void main(void)
{
    iBoardNumber = 0 ;      // select board 0
    DWORD dwDLLVersion ;    // declare data type for DLLVersion function  
    int iBoardVersion ; 
    int iPROMVersion ;
    int iBitNo ;
    int iBitValue ;
    int iWordValue ;

    meOpen ();  // calls the initialize function

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
    printf ("PROM Version: %04x \n", iPROMVersion); // Print PROM Version
    printf ("\n");                                      // blank line

    printf ("\n  ***** Press Return to continue *****\n\n");
    getchar ();

    iErrorCode = me8100DIOSetTristateOFF (iBoardNumber, REGISTER_SET_A);
    ErrorHandler (iErrorCode);

    iErrorCode = me8100SetSinkSourceMode (iBoardNumber, REGISTER_SET_A, 
                                                            SOURCE_MODE);
    ErrorHandler (iErrorCode);

    // Set a bit
    iBoardNumber = 0;
    iBitNo = 0;     // select bit number
    iBitValue = 1;  // set to high

    iErrorCode = me8100DOSetBit(iBoardNumber, REGISTER_SET_A, iBitNo, iBitValue);
    ErrorHandler (iErrorCode);
    printf ("Bit number %02d ", iBitNo);
    printf ("set to : %01d\n", iBitValue);

    // Set a Word
    iBoardNumber = 0;
    iWordValue = 43690;  // hex AAAA or binary 1010 1010 1010 1010
    iErrorCode = me8100DOSetWord(iBoardNumber, REGISTER_SET_A, iWordValue);
    ErrorHandler (iErrorCode);
    printf ("Word Value Set to: %04x\n", iWordValue);

    printf ("\n  ***** Press Return to continue *****\n");
    getchar ();

    // To read an input bit
    iBoardNumber = 0;   // choose board 
    iBitNo = 0;         // choose bit 
    iErrorCode = me8100DIGetBit(iBoardNumber, REGISTER_SET_A, iBitNo, &iBitValue);
    ErrorHandler (iErrorCode);
    printf ("Value read for bit %02d ", iBitNo);
    printf (" : %01d\n", iBitValue);

    // To read an input Word (16 bits)
    iErrorCode = me8100DIGetWord(iBoardNumber, REGISTER_SET_A, &iWordValue);
    ErrorHandler (iErrorCode);
    printf ("Word Value read in: %04x\n\n", iWordValue);

    meClose ();

    printf ("Press any key to continue\n");
    getch();
}

/* ------------------------------------------------------------------------ */

/*  This is the error Handler Routine   */
/*  If a DLL function call returns not  */
/*  a "1", an error occurs and this     */
/*  Routine is executed.                */

void ErrorHandler (int iErrorCode) 
{
    if (iErrorCode != 1)
    {
        printf("*** Error Ocurred ***\n");
    }
}

/*  ------------------------------------------------------------ */
