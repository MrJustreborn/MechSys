
#include <stdio.h>
#include <windows.h>

#include ".\me4000dll.h"

#include ".\dll.h"

#include".\error.h"  // Error codes for all modules.


// Default error proc
void _stdcall me4000DefaultErrorProc(char* function_name, int error_code)
{
}


int _declspec(dllexport) me4000ErrorSetDefaultProc(int iDefaultProcStatus)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000ErrorSetUserProc(ME4000_P_ERROR_PROC pErrorProc)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000ErrorGetMessage(int iErrorCode, char* pcMessage, unsigned int uiBufferSize)
{
    return(ME_ERROR_NONE);
}

int _declspec(dllexport) me4000ErrorGetLastMessage(char* pcMessage, unsigned int uiBufferSize)
{
    return(ME_ERROR_NONE);
}

