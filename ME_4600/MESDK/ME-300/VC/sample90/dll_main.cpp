#include <windows.h>
#include <winioctl.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

HINSTANCE hDllInstance = 0;
int Attached = 0;

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

        default:

			break;
	}

	return true;
}

