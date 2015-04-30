#include <windows.h>
#include <winioctl.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include ".\dll.h"
#include ".\defs.h"

#pragma data_seg("Shared")
int  Attached                           = 0;
char szAppName[]                        = "ME2600.DLL";
#pragma data_seg()      

#pragma comment(linker,"/section:Shared,rws")

HINSTANCE   hDllInstance                = 0;
DWORD       DLLErrorCode                = 0;
BOARD       Board[ME_MAX_DEVICES]       = { 0, 0, 0, 0, 0, 0, 0, 0, 
											0, 0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0};

BOOL _stdcall DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
    switch (reason) 
    {
        case DLL_PROCESS_ATTACH:

            if (!Attached) 
            {
            }
            Attached++;
            break;

        case DLL_PROCESS_DETACH:
            Attached--;
            if (!Attached) 
            {
            }
            break;
    }

    return true;
}