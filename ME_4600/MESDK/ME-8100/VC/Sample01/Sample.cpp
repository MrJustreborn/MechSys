/*      Sample02.cpp : Text based (Console) program */
/*      to get some information                     */
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


#ifdef __BORLANDC__
#include <condefs.h>
USEUNIT("..\DLLInit.cpp");
#endif


#include <stdio.h>
#include <conio.h>
#include <windows.h>

//#include ".\..\me8100.h"
#include ".\..\DLLInit.h"


#define BOARDNUMBER     0


int main(void)
{
    int iDLLVersion;
    int iPROMVersion;
    int iBoardVersion;
    DEVICEINFOSTRUCT DevInfo;


    // calls the initialize function
    meOpen();


    // determine current DLL version
    iDLLVersion = me8100GetDLLVersion();

    printf(
        "DLL version is %04x.%04x\n",
        (iDLLVersion>>16)& 0xFFFF,
        (iDLLVersion)    & 0xFFFF);


    // determine PROM version
    if( me8100PROMVersion(BOARDNUMBER, &iPROMVersion) )
    {
        printf(
            "Board %d has a PROM version of %08x\n",
            BOARDNUMBER,
            iPROMVersion);
    }
    else
    {
        printf(
            "Board %d doesnt exist!\n",
            BOARDNUMBER);

        return(1);
    }


    // determine Board version ==> function dont exist
    if( me8100GetBoardVersion(BOARDNUMBER, &iBoardVersion))
    {
        printf(
            "Board %d has a Board version of %08x\n",
            BOARDNUMBER,
            iBoardVersion);
    }

    

    if( me8100GetDevInfo(BOARDNUMBER, &DevInfo) )
    {
        printf("Board: %2d Device Info\n", BOARDNUMBER);
        printf("----------------------\n\n");

        printf("Vendor ID:          0x%04X\n",  DevInfo.dwVendorID);
        printf("Device ID:          0x%04X\n",  DevInfo.dwDeviceID);
        printf("Bus Number:         %u\n",      DevInfo.dwBusNumber);
        printf("System Slot Number: %u\n",      DevInfo.dwSystemSlotNumber);
        printf("Port Base:          0x%04X\n",  DevInfo.dwPortBase);
        printf("Port Count:         %u\n",      DevInfo.dwPortCount);
        printf("Interrupt Channel:  %u\n",      DevInfo.dwIntChannel);
        printf("PLX Port Base:      0x%04X\n",  DevInfo.dwPortBasePLX);
        printf("PLX Port Count:     %u\n",      DevInfo.dwPortCountPLX);
        printf("Serial Number:      0x%08X\n",  DevInfo.dwSerialNumber);
        printf("Hardware Revision:  0x%04X\n",  DevInfo.dwHWRevision);
        printf("IRQ Count:          %u\n",      DevInfo.dwIrqCnt);
        printf("Version:            0x%04X\n",  DevInfo.dwVersion);
    }
    else
    {
        printf("ERROR!\n\n");
    }


    meClose();

    printf("\nPress any key to continue...\n\n");
    getch();

    return(0);
}
