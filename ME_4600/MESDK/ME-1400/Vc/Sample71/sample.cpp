#include <conio.h>
#include <stdio.h>
#include <windows.h>

#define BOARD_0 0

typedef void (_stdcall *ME_PSERVICE_PROC) (int i_context);
typedef int(__cdecl *PF_ME1400DISABLEEXTERNALINT) (int, int);
typedef int(__cdecl *PF_ME1400ENABLEEXTERNALINT) (int, ME_PSERVICE_PROC, int);

PF_ME1400DISABLEEXTERNALINT				pf_me1400DisableExternalInt;
PF_ME1400ENABLEEXTERNALINT				pf_me1400EnableExternalInt;

HINSTANCE hDll;
long count=0;		// IRQ Counter


void Install(int iBoardNumber, ME_PSERVICE_PROC pCallBack)
{
    hDll = LoadLibrary("me1400.dll");        // Load the Library
    if (hDll == NULL){
        printf ("DLL not Found\n");
        exit(1);
    }

    pf_me1400EnableExternalInt = (PF_ME1400ENABLEEXTERNALINT)
                       (GetProcAddress (hDll,"me1400EnableInt"));

    if (pf_me1400EnableExternalInt)
    {
        (pf_me1400EnableExternalInt)(iBoardNumber, pCallBack, 1);
    }
    else
        printf("Error on call function in line %d\n", __LINE__);
}

void Uninstall(int iBoardNumber)
{
    pf_me1400DisableExternalInt = (PF_ME1400DISABLEEXTERNALINT)
                       (GetProcAddress (hDll,"me1400DisableInt"));

    if (pf_me1400DisableExternalInt)
    {
        (pf_me1400DisableExternalInt)(iBoardNumber, 1);
    }
    else
        printf("Error on call function in line %d\n", __LINE__);

    FreeLibrary (hDll);
}


void _stdcall IrqHandler(int iContext)
{
	count++;
}



void main (void)
{
    Install(BOARD_0, IrqHandler);
    printf("Press any key to stop processing.\n");
    while(!kbhit())
    {
        count=0;
        Sleep(1000);
        printf("Irq per Second: %4d\n", count);
    }
    Uninstall(BOARD_0);
}