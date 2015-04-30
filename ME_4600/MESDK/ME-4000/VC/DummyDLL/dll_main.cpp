
#include <windows.h>
#include <stdio.h>

#include "dll.h"




BOOL _stdcall DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        break;

    case DLL_PROCESS_DETACH:
        break;
    }

    return true;
}
