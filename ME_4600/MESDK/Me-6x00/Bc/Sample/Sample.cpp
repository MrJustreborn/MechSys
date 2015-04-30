/*  Borland C demo                                  */
/*                                                  */
/*  Please see Visual C samples for more details    */
/*  and Visual C++ programs                         */
/*                                                  */


#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "..\..\VC\medefs.h"
#include "..\..\VC\DLLInit.h"           // for using with dynamic DLL accessing

#ifdef __BORLANDC__
#include <condefs.h>
USEFILE("..\..\VC\medefs.h");
USEFILE("..\..\VC\DLLInit.h");
USEUNIT("..\..\VC\DLLInit.cpp");
#endif



void main(void)
{
    meOpen();

    int iDLLVersion;
    iDLLVersion = me6x00GetDLLVersion();
    printf(
        "Version of DLL is %04x.%04x\n",
        (iDLLVersion>>16)& 0xFFFF,
        (iDLLVersion)    & 0xFFFF);

    meClose();

    printf("Press any key to continue\n");
    getch();
}
