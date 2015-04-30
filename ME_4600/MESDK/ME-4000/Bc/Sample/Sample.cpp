/*  Borland C demo                                  */
/*                                                  */
/*  Please see Visual C samples for more details    */
/*  and Visual C++ programs                         */
/*                                                  */


#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "..\..\VC\me4000defs.h"
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

    unsigned long ulDLLVersion;

    me4000GetDLLVersion(&ulDLLVersion);
    printf(
        "Version of DLL is %04x.%04x\n",
        (ulDLLVersion>>16)& 0xFFFF,
        (ulDLLVersion)    & 0xFFFF);

    meClose();

    printf("Press any key to continue\n");
    getch();
}
